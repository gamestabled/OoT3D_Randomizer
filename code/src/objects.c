#include "z3D/z3D.h"
#include "objects.h"
#include <stddef.h>

ExtendedObjectContext rExtendedObjectCtx = { 0 };

s32 ExtendedObject_Spawn(ObjectContext* objectCtx, s16 objectId) {
    return Object_Spawn(&rExtendedObjectCtx, objectId) + OBJECT_EXCHANGE_BANK_MAX;
}

void ExtendedObject_Clear(GlobalContext* globalCtx, ObjectContext* objectCtx) {
    Object_Clear(globalCtx, objectCtx);
    Object_Clear(globalCtx, &rExtendedObjectCtx);
}

s32 ExtendedObject_GetIndex(ObjectContext* objectCtx, s16 objectId) {
    s32 index = Object_GetIndex(objectCtx, objectId);
    if (index < 0) {
        s32 i;
        for (i = 0; i < OBJECT_EXCHANGE_BANK_MAX; ++i) {
            s32 id = rExtendedObjectCtx.status[i].id;
            id = (id < 0 ? -id : id);
            if (id == objectId) {
                return i + OBJECT_EXCHANGE_BANK_MAX;
            }
        }
    }
    return index;
}

s32 ExtendedObject_IsLoaded(ObjectContext* objectCtx, s16 bankIndex) {
    if (bankIndex < OBJECT_EXCHANGE_BANK_MAX) {
        return Object_IsLoaded(objectCtx, bankIndex);
    } else {
        return (rExtendedObjectCtx.status[bankIndex - OBJECT_EXCHANGE_BANK_MAX].id >= 0);
    }
}

ObjectStatus* ExtendedObject_GetStatus(s16 objectId) {
    s32 i;
    for (i = 0; i < rExtendedObjectCtx.num; ++i) {
        s32 id = rExtendedObjectCtx.status[i].id;
        id = (id < 0 ? -id : id);
        if (id == objectId) {
            return &rExtendedObjectCtx.status[i];
        }
    }
    return NULL;
}

void* ExtendedObject_GetCMABByIndex(s16 objectId, u32 objectAnimIdx) {
    s16 objectBankIdx = ExtendedObject_GetIndex(&gGlobalContext->objectCtx, objectId);
    void* cmabMan;

    if (objectBankIdx < OBJECT_EXCHANGE_BANK_MAX) {
        cmabMan = ZAR_GetCMABByIndex(&gGlobalContext->objectCtx.status[objectBankIdx].zarInfo, objectAnimIdx);
    } else {
        cmabMan = ZAR_GetCMABByIndex(&rExtendedObjectCtx.status[objectBankIdx - OBJECT_EXCHANGE_BANK_MAX].zarInfo,
                                     objectAnimIdx);
    }

    return cmabMan;
}
