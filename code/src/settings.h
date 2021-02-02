#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include "../include/z3D/z3D.h"

typedef enum {
  LOGIC_GLITCHLESS,
  LOGIC_NONE,
} LogicSetting;

typedef enum {
  OPENFOREST_OPEN,
  OPENFOREST_CLOSED,
} OpenForestSetting;

typedef enum {
  OPENKAKARIKO_OPEN,
  OPENKAKARIKO_CLOSED,
} OpenKakarikoSetting;

typedef enum {
  RAINBOWBRIDGE_OPEN,
  RAINBOWBRIDGE_VANILLA,
  RAINBOWBRIDGE_STONES,
  RAINBOWBRIDGE_MEDALLIONS,
  RAINBOWBRIDGE_DUNGEONS,
  RAINBOWBRIDGE_TOKENS,
} RainbowBridgeSetting;

typedef enum {
  LACSCONDITION_VANILLA,
  LACSCONDITION_STONES,
  LACSCONDITION_MEDALLIONS,
  LACSCONDITION_DUNGEONS,
} LACSConditionSetting;

typedef enum {
  GERUDOFORTRESS_NORMAL,
  GERUDOFORTRESS_FAST,
  GERUDOFORTRESS_OPEN,
} GerudoFortressSetting;

typedef enum {
  DAMAGEMULTIPLIER_HALF,
  DAMAGEMULTIPLIER_DEFAULT,
  DAMAGEMULTIPLIER_DOUBLE,
  DAMAGEMULTIPLIER_QUADRUPLE,
  DAMAGEMULTIPLIER_OHKO,
} DamageMultiplierSetting;

typedef enum {
  ZORASFOUNTAIN_NORMAL,
  //ZORASFOUNTAIN_ADULT,
  ZORASFOUNTAIN_OPEN,
} ZorasFountainSetting;

typedef enum {
  STARTINGTIME_DAY,
  STARTINGTIME_NIGHT,
} StartingTimeSetting;

typedef enum {
  KEYSANITY_VANILLA,
  KEYSANITY_OWN_DUNGEON,
  KEYSANITY_ANYWHERE,
} KeysanitySetting;

typedef enum {
  BOSSKEYSANITY_VANILLA,
  BOSSKEYSANITY_OWN_DUNGEON,
  BOSSKEYSANITY_ANYWHERE,
} BossKeysanitySetting;

typedef enum {
  GANONSBOSSKEY_VANILLA,
  GANONSBOSSKEY_OWN_DUNGEON,
  GANONSBOSSKEY_ANYWHERE,
  GANONSBOSSKEY_LACS_VANILLA,
  GANONSBOSSKEY_LACS_MEDALLIONS,
  GANONSBOSSKEY_LACS_STONES,
  GANONSBOSSKEY_LACS_DUNGEONS,
} GanonsBossKeySetting;

typedef enum {
  MAPSANDCOMPASSES_START_WITH,
  MAPSANDCOMPASSES_VANILLA,
  MAPSANDCOMPASSES_OWN_DUNGEON,
  MAPSANDCOMPASSES_ANYWHERE,
} MapsAndCompassesSetting;

typedef enum {
  SONGSHUFFLE_SONG_LOCATIONS,
  SONGSHUFFLE_ANYWHERE,
} SongShuffleSetting;

typedef enum {
  TOKENSANITY_VANILLA,
  TOKENSANITY_ANYWHERE,
} TokensanitySetting;

typedef enum {
  SCRUBSANITY_OFF,
  SCRUBSANITY_AFFORDABLE,
  SCRUBSANITY_EXPENSIVE,
  SCRUBSANITY_RANDOM_PRICES,
} ScrubsanitySetting;

typedef enum {
  DUNGEONMODE_VANILLA,
  DUNGEONMODE_MQ,
} DungeonMode;

typedef enum {
  ITEMPOOL_PLENTIFUL,
  ITEMPOOL_BALANCED,
  ITEMPOOL_SCARCE,
  ITEMPOOL_MINIMAL,
} ItemPoolSetting;

typedef enum {
  AGE_ADULT,
  AGE_CHILD,
} AgeSetting;

typedef struct {
  u8 logic : 1;
  u8 openForest : 2;
  u8 openKakariko : 2;
  u8 openDoorOfTime : 1;
  u8 zorasFountain : 2;
  u8 gerudoFortress : 2;
  u8 rainbowBridge : 3;

  u8 startingAge : 1;
  u8 bombchusInLogic : 1;
  u8 randomMQDungeons : 1;

  u8 shuffleSongs : 2;
  u8 tokensanity : 2;
  u8 scrubsanity : 2;
  u8 shuffleKokiriSword : 1;
  u8 shuffleOcarinas : 1;
  u8 shuffleWeirdEgg : 1;
  u8 shuffleGerudoToken : 1;
  u8 shuffleMagicBeans : 1;

  u8 keysanity : 3;
  u8 bossKeysanity : 3;
  u8 ganonsBossKey : 4;
  u8 mapsAndCompasses : 3;
  u8 lacsCondition : 3;

  u8 skipChildStealth : 1;
  u8 fourPoesCutscene : 1;
  u8 bigPoeTargetCount : 4;

  u8 damageMultiplier : 3;
  u8 startingTime : 3;

  u8 boomerangAsAdult : 1;
  u8 hammerAsChild : 1;

  u8 itemPoolValue : 3;

  u8 dekuTreeDungeonMode : 1;
  u8 dodongosCavernDungeonMode : 1;
  u8 jabuJabusBellyDungeonMode : 1;
  u8 forestTempleDungeonMode : 1;
  u8 fireTempleDungeonMode : 1;
  u8 waterTempleDungeonMode : 1;
  u8 spiritTempleDungeonMode : 1;
  u8 shadowTempleDungeonMode : 1;
  u8 bottomOfTheWellDungeonMode : 1;
  u8 gerudoTrainingGroundsDungeonMode : 1;
  u8 ganonsCastleDungeonMode : 1;

  u32 dungeonRewardBitMask;

} SettingsContext;

extern SettingsContext gSettingsContext;

#endif
