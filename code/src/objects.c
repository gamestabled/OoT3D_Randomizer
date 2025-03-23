#include "z3D/z3D.h"
#include "objects.h"
#include "common.h"
#include "models.h"
#include "custom_models.h"
#include "oot_malloc.h"
#include <stddef.h>

static ExtendedObjectContext rExtendedObjectCtx = { 0 };

static s32 ExtendedObject_Spawn(s16 objectId) {
    return Object_Spawn(&rExtendedObjectCtx, objectId) + OBJECT_SLOT_MAX;
}

void ExtendedObject_UpdateEntries(void) {
    Object_UpdateEntries(&rExtendedObjectCtx);
}

void ExtendedObject_Clear(void) {
    Object_Clear(gGlobalContext, &rExtendedObjectCtx);
}

// Copy of Object_Clear but only for non-persistent objects.
void ExtendedObject_ClearNonPersistent(void) {
    // CitraPrint("ExtendedObject_ClearNonPersistent enter %d", rExtendedObjectCtx.numPersistentEntries);
    for (s32 i = rExtendedObjectCtx.numPersistentEntries; i < OBJECT_SLOT_MAX; i++) {
        ObjectEntry* entry = &rExtendedObjectCtx.slots[i];
        if (entry->id > 0) {
            // CitraPrint("deleting object %X", entry->id);
            if (entry->size != 0) {
                ZAR_Destroy(&entry->zarInfo);
                entry->size = 0;
            }
            SystemArena_Free(entry->buf);
            entry->buf = NULL;
            entry->id  = 0;
        }
    }
    rExtendedObjectCtx.numEntries = rExtendedObjectCtx.numPersistentEntries;
}

void ExtendedObject_AfterObjectListCommand(void) {
    if (gGlobalContext->state.running == 1) { // Loading scene
        // Spawn objects that will not unload on room transitions.
        ExtendedObject_Spawn(OBJECT_CUSTOM_GENERAL_ASSETS);
        Object_FindSlotOrSpawn(3); // zelda_dangeon_keep (main dungeon object)
        rExtendedObjectCtx.numPersistentEntries = rExtendedObjectCtx.numEntries;
    } else { // (state.running == 2) Loading room
        ExtendedObject_ClearNonPersistent();
        Actor_KillAllWithMissingObject(gGlobalContext, &gGlobalContext->actorCtx);
        Model_DestroyAll();
    }
}

s32 ExtendedObject_GetSlot(s16 objectId) {
    for (s32 i = 0; i < rExtendedObjectCtx.numEntries; ++i) {
        s32 id = ABS(rExtendedObjectCtx.slots[i].id);
        if (id == objectId) {
            return i + OBJECT_SLOT_MAX;
        }
    }
    return -1;
}

ObjectEntry* Object_GetEntry(s16 slot) {
    if (slot >= OBJECT_SLOT_MAX) {
        return &rExtendedObjectCtx.slots[slot - OBJECT_SLOT_MAX];
    }
    if (slot >= 0) {
        return &gGlobalContext->objectCtx.slots[slot];
    }
    return NULL;
}

ObjectEntry* Object_FindEntryOrSpawn(s16 objectId) {
    ObjectEntry* obj;
    s32 slot = Object_GetSlot(&gGlobalContext->objectCtx, objectId);
    if (slot >= 0) {
        if (slot >= OBJECT_SLOT_MAX) {
            obj = &rExtendedObjectCtx.slots[slot - OBJECT_SLOT_MAX];
        } else {
            obj = &gGlobalContext->objectCtx.slots[slot];
        }
        return obj;
    } else {
        slot = Object_Spawn(&rExtendedObjectCtx, objectId);
        return &rExtendedObjectCtx.slots[slot];
    }
}

s32 Object_FindSlotOrSpawn(s16 objectId) {
    s32 objectSlot = Object_GetSlot(&gGlobalContext->objectCtx, objectId);
    if (objectSlot < 0) {
        objectSlot = ExtendedObject_Spawn(objectId);
    }
    return objectSlot;
}

s32 Object_IsLoaded(ObjectContext* objectCtx, s16 slot) {
    if (slot < OBJECT_SLOT_MAX) {
        return (objectCtx->slots[slot].id > 0);
    }

    return (rExtendedObjectCtx.slots[slot - OBJECT_SLOT_MAX].id > 0);
}

void* Object_GetCMABByIndex(s16 objectId, u32 objectAnimIdx) {
    ObjectEntry* obj = Object_FindEntryOrSpawn(objectId);
    return ZAR_GetCMABByIndex(&obj->zarInfo, objectAnimIdx);
}
