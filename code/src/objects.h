#ifndef _OBJECTS_H_
#define _OBJECTS_H_

#include "z3D/z3D.h"

typedef enum ObjectId {
    OBJECT_CUSTOM_DOUBLE_DEFENSE     = 0x0004,
    OBJECT_CUSTOM_CHILD_SONGS        = 0x0005,
    OBJECT_CUSTOM_ADULT_SONGS        = 0x0010,
    OBJECT_CUSTOM_SMALL_KEY_FOREST   = 0x0011,
    OBJECT_CUSTOM_SMALL_KEY_FIRE     = 0x003A,
    OBJECT_CUSTOM_SMALL_KEY_WATER    = 0x0078,
    OBJECT_CUSTOM_SMALL_KEY_SHADOW   = 0x0079,
    OBJECT_CUSTOM_SMALL_KEY_BOTW     = 0x007A,
    OBJECT_CUSTOM_SMALL_KEY_SPIRIT   = 0x007B,
    OBJECT_CUSTOM_SMALL_KEY_FORTRESS = 0x007D,
    OBJECT_CUSTOM_SMALL_KEY_GTG      = 0x007E,
    OBJECT_CUSTOM_SMALL_KEY_GANON    = 0x007F,
    OBJECT_CUSTOM_BOSS_KEYS          = 0x0080,
    OBJECT_CUSTOM_RUPOOR             = 0x0083,
    OBJECT_TRIFORCE                  = 0x0095,
    OBJECT_GI_KEY                    = 0x00AA,
    OBJECT_CUSTOM_GENERAL_ASSETS     = 0x00B6,
    OBJECT_GI_BOSSKEY                = 0x00B9,
    OBJECT_GI_HEARTS                 = 0x00BD,
    OBJECT_GI_OCARINA_TIME           = 0x00DE,
    OBJECT_CUSTOM_ENEMY_SOUL         = 0x00E4,
    OBJECT_GI_OCARINA_FAIRY          = 0x010E,
    OBJECT_CUSTOM_OCARINA_BUTTON     = 0x0123,
    OBJECT_GI_SOLD_OUT               = 0x0148,
    OBJECT_CUSTOM_TRIFORCE_PIECE     = 0x016E,
    OBJECT_GI_SHOP_FAIRY             = 0x0177,
    OBJECT_GI_RUPEE                  = 0x017F,
    OBJECT_ID_MAX                    = 0x01A1,
} ObjectId;

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
// Check if this object id is for a rupee model.
u8 Object_IsRupeeObject(u16 objectId);

// Update the extended object context.
void ExtendedObject_UpdateEntries(void);

#endif //_OBJECTS_H_
