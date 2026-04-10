#pragma once

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

typedef enum DungeonReward {
    /* 0x00 */ R_KOKIRI_EMERALD,
    /* 0x01 */ R_GORON_RUBY,
    /* 0x02 */ R_ZORA_SAPPHIRE,
    /* 0x03 */ R_FOREST_MEDALLION,
    /* 0x04 */ R_FIRE_MEDALLION,
    /* 0x05 */ R_WATER_MEDALLION,
    /* 0x06 */ R_SPIRIT_MEDALLION,
    /* 0x07 */ R_SHADOW_MEDALLION,
    /* 0x08 */ R_LIGHT_MEDALLION,
    /* 0x09 */ DUNGEON_REWARDS_COUNT,
} DungeonReward;

typedef enum DungeonId {
    DUNGEON_DEKU_TREE,
    DUNGEON_DODONGOS_CAVERN,
    DUNGEON_JABUJABUS_BELLY,
    DUNGEON_FOREST_TEMPLE,
    DUNGEON_FIRE_TEMPLE,
    DUNGEON_WATER_TEMPLE,
    DUNGEON_SPIRIT_TEMPLE,
    DUNGEON_SHADOW_TEMPLE,
    DUNGEON_BOTTOM_OF_THE_WELL,
    DUNGEON_ICE_CAVERN,
    DUNGEON_GANONS_TOWER,
    DUNGEON_GERUDO_TRAINING_GROUNDS,
    DUNGEON_THIEVES_HIDEOUT,
    DUNGEON_INSIDE_GANONS_CASTLE,
    DUNGEON_GANONS_TOWER_COLLAPSING_INTERIOR,
    DUNGEON_GANONS_CASTLE_COLLAPSING,
    DUNGEON_TREASURE_CHEST_SHOP,
    DUNGEON_DEKU_TREE_BOSS_ROOM,
    DUNGEON_DODONGOS_CAVERN_BOSS_ROOM,
    DUNGEON_JABUJABUS_BELLY_BOSS_ROOM,
    DUNGEON_FOREST_TEMPLE_BOSS_ROOM,
    DUNGEON_FIRE_TEMPLE_BOSS_ROOM,
    DUNGEON_WATER_TEMPLE_BOSS_ROOM,
    DUNGEON_SPIRIT_TEMPLE_BOSS_ROOM,
    DUNGEON_SHADOW_TEMPLE_BOSS_ROOM,
} DungeonId;

extern const char* const smallKeyStringForest;
extern const char* const smallKeyStringFire;
extern const char* const smallKeyStringWater;
extern const char* const smallKeyStringSpirit;
extern const char* const smallKeyStringShadow;
extern const char* const smallKeyStringBotW;
extern const char* const smallKeyStringGTG;
extern const char* const smallKeyStringHideout;
extern const char* const smallKeyStringGanon;
extern const char* const smallKeyStringGame;

extern const char* const keyRingStringForest;
extern const char* const keyRingStringFire;
extern const char* const keyRingStringWater;
extern const char* const keyRingStringSpirit;
extern const char* const keyRingStringShadow;
extern const char* const keyRingStringBotW;
extern const char* const keyRingStringGTG;
extern const char* const keyRingStringHideout;
extern const char* const keyRingStringGanon;
