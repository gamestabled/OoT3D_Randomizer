#include "z3D/z3D.h"
#include "objects.h"
#include "common.h"
#include "models.h"
#include "custom_models.h"
#include "oot_malloc.h"
#include "enemizer.h"

#include <stddef.h>

#define EXTENDED_OBJECT_SLOT_MAX 30

// Copy of ObjectContext with more object slots.
typedef struct ExtendedObjectContext {
    /* 0x000 */ u8 numEntries;           // total amount of used entries
    /* 0x001 */ u8 numPersistentEntries; // amount of entries that won't be reused when loading a new room
    /* 0x002 */ u8 unused_02;
    /* 0x003 */ u8 unused_03;
    /* 0x004 */ ObjectEntry slots[EXTENDED_OBJECT_SLOT_MAX];
} ExtendedObjectContext;

static ExtendedObjectContext rExtendedObjectCtx = { 0 };

void ExtendedObject_UpdateEntries(void) {
    Object_UpdateEntries((ObjectContext*)&rExtendedObjectCtx);
}

void ExtendedObject_Clear(void) {
    Object_Clear(gGlobalContext, (ObjectContext*)&rExtendedObjectCtx);
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
        // Note: Player_Init has already run by this point, so whatever objects it
        // spawned in the extended context will also be marked as persistent here.
        Object_FindSlotOrSpawn(OBJECT_CUSTOM_GENERAL_ASSETS);
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
        slot = Object_Spawn((ObjectContext*)&rExtendedObjectCtx, objectId);
        return &rExtendedObjectCtx.slots[slot];
    }
}

s32 Object_FindSlotOrSpawn(s16 objectId) {
    s32 objectSlot = Object_GetSlot(&gGlobalContext->objectCtx, objectId);
    if (objectSlot < 0) {
        objectSlot = Object_Spawn((ObjectContext*)&rExtendedObjectCtx, objectId) + OBJECT_SLOT_MAX;
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
