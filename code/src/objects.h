#ifndef _OBJECTS_H_
#define _OBJECTS_H_

#include "z3D/z3D.h"

typedef s32 (*Object_proc)(ObjectContext* objectCtx, s16 objectId);

#define Object_Spawn_addr 0x32E21C
#define Object_Spawn ((Object_proc)Object_Spawn_addr)

#define Object_GetIndex_addr 0x363C10
#define Object_GetIndex ((Object_proc)Object_GetIndex_addr)

#define Object_IsLoaded_addr 0x373074
#define Object_IsLoaded ((Object_proc)Object_IsLoaded_addr) // For Object_IsLoaded, second param is bankIndex

typedef void (*Object_UpdateBank_proc)(ObjectContext* objectCtx);
#define Object_UpdateBank_addr 0x2E4EA0
#define Object_UpdateBank ((Object_UpdateBank_proc)Object_UpdateBank_addr)

typedef void (*Object_Clear_proc)(GlobalContext* globalCtx, ObjectContext* objectCtx);
#ifdef Version_EUR
    #define Object_Clear_addr 0x45FDC0
#else
    #define Object_Clear_addr 0x45FDA0
#endif
#define Object_Clear ((Object_Clear_proc)Object_Clear_addr)

typedef void* (*ZAR_Get_proc)(ZARInfo* zarInfo, u32 index);
#define ZAR_GetCMBByIndex_addr 0x358EF8
#define ZAR_GetCMBByIndex ((ZAR_Get_proc)ZAR_GetCMBByIndex_addr)

#define ZAR_GetCMABByIndex_addr 0x372F0C
#define ZAR_GetCMABByIndex ((ZAR_Get_proc)ZAR_GetCMABByIndex_addr)

typedef void (*TexAnim_Spawn_proc)(void*, void*);
#define TexAnim_Spawn_addr 0x372D94
#define TexAnim_Spawn ((TexAnim_Spawn_proc)TexAnim_Spawn_addr)

typedef ObjectContext ExtendedObjectContext;

extern ExtendedObjectContext rExtendedObjectCtx;

s32 ExtendedObject_Spawn(ObjectContext* objectCtx, s16 objectId);
s32 ExtendedObject_GetIndex(ObjectContext* objectCtx, s16 objectId);
ObjectStatus* ExtendedObject_GetStatus(s16 objectId);
s32 ExtendedObject_IsLoaded(ObjectContext* objectCtx, s16 bankIndex);
void ExtendedObject_Clear(GlobalContext* globalCtx, ObjectContext* objectCtx);
void* ExtendedObject_GetCMABByIndex(s16 objectId, u32 objectAnimIdx);

#endif //_OBJECTS_H_
