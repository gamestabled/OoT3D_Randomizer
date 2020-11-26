#include "z3D/z3D.h"

#define EXTENDED_OBJECT_EXCHANGE_BANK_MAX 19

typedef s32 (*Object_proc)(ObjectContext* objectCtx, s16 objectId);

#define Object_Spawn_addr 0x32E21C
#define Object_Spawn ((Object_proc)Object_Spawn_addr)

#define Object_GetIndex_addr 0x363C10
#define Object_GetIndex ((Object_proc)Object_GetIndex_addr)

#define Object_IsLoaded_addr 0x373074
#define Object_IsLoaded ((Object_proc)Object_IsLoaded_addr) //For Object_IsLoaded, second param is bankIndex

typedef void (*Object_UpdateBank_proc)(ObjectContext* objectCtx);

#define Object_UpdateBank_addr 0x2E4EA0
#define Object_UpdateBank ((Object_UpdateBank_proc)Object_UpdateBank_addr)

typedef struct {
    /* 0x000 */ u8 num;
    /* 0x001 */ char unk_01[0x3];
    /* 0x004 */ ObjectStatus status[EXTENDED_OBJECT_EXCHANGE_BANK_MAX];
} ExtendedObjectContext;

extern ExtendedObjectContext rExtendedObjectCtx;

s32 ExtendedObject_Spawn(ObjectContext* objectCtx, s16 objectId);
s32 ExtendedObject_GetIndex(ObjectContext* objectCtx, s16 objectId);
s32 ExtendedObject_IsLoaded(ObjectContext* objectCtx, s16 bankIndex);
