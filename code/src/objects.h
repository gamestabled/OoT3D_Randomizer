#ifndef _OBJECTS_H_
#define _OBJECTS_H_

#include "z3D/z3D.h"

typedef s32 (*Object_proc)(ObjectContext* objectCtx, s16 objectId);

#define Object_Spawn ((Object_proc)GAME_ADDR(0x32E21C))

#define Object_GetSlot ((Object_proc)GAME_ADDR(0x363C10))

typedef void (*Object_UpdateEntries_proc)(ObjectContext* objectCtx);
#define Object_UpdateEntries ((Object_UpdateEntries_proc)GAME_ADDR(0x2E4EA0))

typedef void (*Object_Clear_proc)(GlobalContext* globalCtx, ObjectContext* objectCtx);
#define Object_Clear ((Object_Clear_proc)GAME_ADDR(0x45FDA0))

typedef void* (*ZAR_Get_proc)(ZARInfo* zarInfo, u32 index);
#define ZAR_GetCMBByIndex ((ZAR_Get_proc)GAME_ADDR(0x358EF8))

#define ZAR_GetCMABByIndex ((ZAR_Get_proc)GAME_ADDR(0x372F0C))

typedef void (*ZAR_Destroy_proc)(ZARInfo*);
#define ZAR_Destroy ((ZAR_Destroy_proc)GAME_ADDR(0x2F70C4))

typedef void (*TexAnim_Spawn_proc)(void*, void*);
#define TexAnim_Spawn ((TexAnim_Spawn_proc)GAME_ADDR(0x372D94))

// Get an object entry given the slot.
ObjectEntry* Object_GetEntry(s16 slot);
// Find an object entry for the specified objectId, or spawn it if it's not found.
ObjectEntry* Object_FindEntryOrSpawn(s16 objectId);
// Same as Object_FindEntryOrSpawn but return the object slot
s32 Object_FindSlotOrSpawn(s16 objectId);
// Check if the object in the given slot is loaded.
s32 Object_IsLoaded(ObjectContext* objectCtx, s16 slot);
// Get the CMAB manager from this object, loading it if it's not present.
void* Object_GetCMABByIndex(s16 objectId, u32 objectAnimIdx);

// Update the extended object context.
void ExtendedObject_UpdateEntries(void);

#endif //_OBJECTS_H_
