#ifndef _DUNGEON_H_
#define _DUNGEON_H_

#include "../include/z3D/z3D.h"

static const char* const smallKeyStringForest  = "Forest Temple Small Key";
static const char* const smallKeyStringFire    = "Fire Temple Small Key";
static const char* const smallKeyStringWater   = "Water Temple Small Key";
static const char* const smallKeyStringSpirit  = "Spirit Temple Small Key";
static const char* const smallKeyStringShadow  = "Shadow Temple Small Key";
static const char* const smallKeyStringBotW    = "Bottom of the Well Small Key";
static const char* const smallKeyStringGTG     = "Training Grounds Small Key";
static const char* const smallKeyStringHideout = "Gerudo Fortress Small Key";
static const char* const smallKeyStringGanon   = "Ganon's Castle Small Key";
static const char* const smallKeyStringGame    = "Chest Game Small Key";

static const char* const keyRingStringForest  = "Forest Temple Key Ring";
static const char* const keyRingStringFire    = "Fire Temple Key Ring";
static const char* const keyRingStringWater   = "Water Temple Key Ring";
static const char* const keyRingStringSpirit  = "Spirit Temple Key Ring";
static const char* const keyRingStringShadow  = "Shadow Temple Key Ring";
static const char* const keyRingStringBotW    = "Bottom of the Well Key Ring";
static const char* const keyRingStringGTG     = "Training Grounds Key Ring";
static const char* const keyRingStringHideout = "Gerudo Fortress Key Ring";
static const char* const keyRingStringGanon   = "Ganon's Castle Key Ring";

#define FOREST_KEY_COUNT 5
#define FOREST_MQ_KEY_COUNT 6
#define FIRE_KEY_COUNT 8
#define FIRE_MQ_KEY_COUNT 5
#define WATER_KEY_COUNT 6
#define WATER_MQ_KEY_COUNT 2
#define SPIRIT_KEY_COUNT 5
#define SPIRIT_MQ_KEY_COUNT 7
#define SHADOW_KEY_COUNT 5
#define SHADOW_MQ_KEY_COUNT 6
#define BOTW_KEY_COUNT 3
#define BOTW_MQ_KEY_COUNT 2
#define GTG_KEY_COUNT 9
#define GTG_MQ_KEY_COUNT 3
#define GANON_KEY_COUNT 2
#define GANON_MQ_KEY_COUNT 3
#define HIDEOUT_KEY_COUNT 4

u8 Dungeon_KeyAmount(DungeonId id);
u8 Dungeon_FoundSmallKeys(DungeonId id);

#endif //_DUNGEON_H_
