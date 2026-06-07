#ifndef _OBJECTS_H_
#define _OBJECTS_H_

#include "z3D/z3D.h"

typedef enum ObjectId {
    OBJECT_INVALID                   = 0x0000,
    OBJECT_GAMEPLAY_KEEP             = 0x0001,
    OBJECT_GAMEPLAY_FIELD_KEEP       = 0x0002,
    OBJECT_GAMEPLAY_DUNGEON_KEEP     = 0x0003,
    OBJECT_CUSTOM_DOUBLE_DEFENSE     = 0x0004,
    OBJECT_CUSTOM_CHILD_SONGS        = 0x0005,
    OBJECT_POE                       = 0x0009,
    OBJECT_WALLMASTER                = 0x000B,
    OBJECT_CUSTOM_ADULT_SONGS        = 0x0010,
    OBJECT_CUSTOM_SMALL_KEY_FOREST   = 0x0011,
    OBJECT_TEKTITE                   = 0x0016,
    OBJECT_KING_DODONGO              = 0x0019,
    OBJECT_BIRI                      = 0x0021,
    OBJECT_SKULLTULA                 = 0x0024,
    OBJECT_ARMOS                     = 0x0038,
    OBJECT_CUSTOM_SMALL_KEY_FIRE     = 0x003A,
    OBJECT_BARI                      = 0X0056,
    OBJECT_FLYING_FLOOR_TILE         = 0X005F,
    OBJECT_FIELD_POE                 = 0x006D,
    OBJECT_POE_COMPOSER              = 0x006E,
    OBJECT_CUSTOM_SMALL_KEY_WATER    = 0x0078,
    OBJECT_CUSTOM_SMALL_KEY_SHADOW   = 0x0079,
    OBJECT_CUSTOM_SMALL_KEY_BOTW     = 0x007A,
    OBJECT_CUSTOM_SMALL_KEY_SPIRIT   = 0x007B,
    OBJECT_CUSTOM_SMALL_KEY_FORTRESS = 0x007D,
    OBJECT_CUSTOM_SMALL_KEY_GTG      = 0x007E,
    OBJECT_CUSTOM_SMALL_KEY_GANON    = 0x007F,
    OBJECT_CUSTOM_BOSS_KEYS          = 0x0080,
    OBJECT_CUSTOM_RUPOOR             = 0x0083,
    OBJECT_BARINADE                  = 0x008C,
    OBJECT_TRIFORCE                  = 0x0095,
    OBJECT_REDEAD                    = 0x0098,
    OBJECT_POE_SISTER                = 0x0099,
    OBJECT_VOLVAGIA                  = 0x009C,
    OBJECT_DEAD_HAND                 = 0x00A6,
    OBJECT_GI_KEY                    = 0x00AA,
    OBJECT_MORPHA                    = 0x00B4,
    OBJECT_CUSTOM_GENERAL_ASSETS     = 0x00B6,
    OBJECT_GI_BOSSKEY                = 0x00B9,
    OBJECT_GI_HEARTS                 = 0x00BD,
    OBJECT_GI_DEKU_SHIELD            = 0x00CB,
    OBJECT_TENTACLE                  = 0x00D5,
    OBJECT_ANUBIS                    = 0x00D6,
    OBJECT_GI_HYLIAN_SHIELD          = 0x00DC,
    OBJECT_GI_OCARINA_TIME           = 0x00DE,
    OBJECT_GANONDORF                 = 0x00E1,
    OBJECT_BONGO_BONGO               = 0x00E2,
    OBJECT_CUSTOM_ENEMY_SOUL         = 0x00E4,
    OBJECT_GI_OCARINA_FAIRY          = 0x010E,
    OBJECT_FREEZARD                  = 0x0114,
    OBJECT_CUSTOM_OCARINA_BUTTON     = 0x0123,
    OBJECT_GI_SOLD_OUT               = 0x0148,
    OBJECT_GANON                     = 0x0153,
    OBJECT_CUSTOM_TRIFORCE_PIECE     = 0x016E,
    OBJECT_GI_SHOP_FAIRY             = 0x0177,
    OBJECT_GI_RUPEE                  = 0x017F,
    OBJECT_ID_MAX                    = 0x01A1,
} ObjectId;

s32 Object_Spawn(ObjectContext* objectCtx, s16 objectId);
s32 Object_GetSlot(ObjectContext* objectCtx, s16 objectId);
void Object_UpdateEntries(ObjectContext* objectCtx);
void Object_Clear(GlobalContext* globalCtx, ObjectContext* objectCtx);

// Get an object entry given the slot.
ObjectEntry* Object_GetEntry(s16 slot);
// Find an object entry for the specified objectId, if there is one.
ObjectEntry* Object_FindEntry(s16 objectId);
// Find an object entry for the specified objectId, or spawn it if it's not found.
ObjectEntry* Object_FindEntryOrSpawn(s16 objectId);
// Same as Object_FindEntryOrSpawn but return the object slot.
s32 Object_FindSlotOrSpawn(s16 objectId);
// Find the object entry this ZarInfo comes from.
ObjectEntry* Object_FindEntryByZarInfo(ZARInfo* zarInfo);
// Check if the object in the given slot is loaded.
s32 Object_IsLoaded(ObjectContext* objectCtx, s16 slot);
// Get the CMAB manager from this object, loading it if it's not present.
void* Object_GetCMABByIndex(s16 objectId, u32 objectAnimIdx);
// Check if this object id is for a rupee model.
u8 Object_IsRupeeObject(u16 objectId);

// Update the extended object context.
void ExtendedObject_UpdateEntries(void);

#endif //_OBJECTS_H_
