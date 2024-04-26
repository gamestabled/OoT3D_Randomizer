#ifndef _OBJECTS_H_
#define _OBJECTS_H_

#include "z3D/z3D.h"

typedef s32 (*Object_proc)(ObjectContext* objectCtx, s16 objectId);

#define Object_Spawn ((Object_proc)GAME_ADDR(0x32E21C))

#define Object_GetIndex ((Object_proc)GAME_ADDR(0x363C10))

#define Object_IsLoaded ((Object_proc)GAME_ADDR(0x373074)) // For Object_IsLoaded, second param is bankIndex

typedef void (*Object_UpdateBank_proc)(ObjectContext* objectCtx);
#define Object_UpdateBank ((Object_UpdateBank_proc)GAME_ADDR(0x2E4EA0))

typedef void (*Object_Clear_proc)(GlobalContext* globalCtx, ObjectContext* objectCtx);
#define Object_Clear ((Object_Clear_proc)GAME_ADDR(0x45FDA0))

typedef void* (*ZAR_Get_proc)(ZARInfo* zarInfo, u32 index);
#define ZAR_GetCMBByIndex ((ZAR_Get_proc)GAME_ADDR(0x358EF8))

#define ZAR_GetCMABByIndex ((ZAR_Get_proc)GAME_ADDR(0x372F0C))

typedef void (*TexAnim_Spawn_proc)(void*, void*);
#define TexAnim_Spawn ((TexAnim_Spawn_proc)GAME_ADDR(0x372D94))

typedef ObjectContext ExtendedObjectContext;

extern ExtendedObjectContext rExtendedObjectCtx;

s32 ExtendedObject_Spawn(ObjectContext* objectCtx, s16 objectId);
s32 ExtendedObject_GetIndex(ObjectContext* objectCtx, s16 objectId);
ObjectStatus* ExtendedObject_GetStatus(s16 objectId);
s32 ExtendedObject_IsLoaded(ObjectContext* objectCtx, s16 bankIndex);
void ExtendedObject_Clear(GlobalContext* globalCtx, ObjectContext* objectCtx);
void* ExtendedObject_GetCMABByIndex(s16 objectId, u32 objectAnimIdx);

#endif //_OBJECTS_H_
