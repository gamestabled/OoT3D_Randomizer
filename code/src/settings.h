#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include "../include/z3D/z3D.h"

typedef enum {
  OFF,
  ON,
} BooleanSetting;

typedef enum {
  DONT_SKIP,
  SKIP,
} SkipSetting;

typedef enum {
  LOGIC_GLITCHLESS,
  LOGIC_NONE,
} LogicSetting;

typedef enum {
  OPENFOREST_CLOSED,
  OPENFOREST_OPEN,
} OpenForestSetting;

typedef enum {
  OPENKAKARIKO_CLOSED,
  OPENKAKARIKO_OPEN,
} OpenKakarikoSetting;

typedef enum {
  ZORASFOUNTAIN_NORMAL,
  ZORASFOUNTAIN_ADULT,
  ZORASFOUNTAIN_OPEN,
} ZorasFountainSetting;

typedef enum {
  GERUDOFORTRESS_NORMAL,
  GERUDOFORTRESS_FAST,
  GERUDOFORTRESS_OPEN,
} GerudoFortressSetting;

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
  AGE_ADULT,
  AGE_CHILD,
} AgeSetting;

typedef enum {
  DUNGEONMODE_VANILLA,
  DUNGEONMODE_MQ,
} DungeonMode;

typedef enum {
  SONGSHUFFLE_SONG_LOCATIONS,
  SONGSHUFFLE_DUNGEON_REWARDS,
  SONGSHUFFLE_ANYWHERE,
} SongShuffleSetting;

typedef enum {
  TOKENSANITY_OFF,
  TOKENSANITY_DUNGEONS,
  TOKENSANITY_OVERWORLD,
  TOKENSANITY_ALL_TOKENS,
} TokensanitySetting;

typedef enum {
  SCRUBSANITY_OFF,
  SCRUBSANITY_AFFORDABLE,
  SCRUBSANITY_EXPENSIVE,
  SCRUBSANITY_RANDOM_PRICES,
} ScrubsanitySetting;

typedef enum {
  MAPSANDCOMPASSES_START_WITH,
  MAPSANDCOMPASSES_VANILLA,
  MAPSANDCOMPASSES_OWN_DUNGEON,
  MAPSANDCOMPASSES_ANYWHERE,
} MapsAndCompassesSetting;

typedef enum {
  KEYSANITY_START_WITH,
  KEYSANITY_VANILLA,
  KEYSANITY_OWN_DUNGEON,
  KEYSANITY_ANYWHERE,
} KeysanitySetting;

typedef enum {
  GERUDOKEYS_VANILLA,
  GERUDOKEYS_ANYWHERE,
} GerudoKeysSetting;

typedef enum {
  BOSSKEYSANITY_START_WITH,
  BOSSKEYSANITY_VANILLA,
  BOSSKEYSANITY_OWN_DUNGEON,
  BOSSKEYSANITY_ANYWHERE,
} BossKeysanitySetting;

typedef enum {
  GANONSBOSSKEY_START_WITH,
  GANONSBOSSKEY_VANILLA,
  GANONSBOSSKEY_OWN_DUNGEON,
  GANONSBOSSKEY_ANYWHERE,
  GANONSBOSSKEY_LACS_VANILLA,
  GANONSBOSSKEY_LACS_MEDALLIONS,
  GANONSBOSSKEY_LACS_STONES,
  GANONSBOSSKEY_LACS_DUNGEONS,
} GanonsBossKeySetting;

typedef enum {
  DAMAGEMULTIPLIER_HALF,
  DAMAGEMULTIPLIER_DEFAULT,
  DAMAGEMULTIPLIER_DOUBLE,
  DAMAGEMULTIPLIER_QUADRUPLE,
  DAMAGEMULTIPLIER_OHKO,
} DamageMultiplierSetting;

typedef enum {
  STARTINGTIME_DAY,
  STARTINGTIME_NIGHT,
} StartingTimeSetting;

typedef enum {
  ITEMPOOL_PLENTIFUL,
  ITEMPOOL_BALANCED,
  ITEMPOOL_SCARCE,
  ITEMPOOL_MINIMAL,
} ItemPoolSetting;

typedef enum {
  ICETRAPS_OFF,
  ICETRAPS_NORMAL,
  ICETRAPS_EXTRA,
  ICETRAPS_MAYHEM,
  ICETRAPS_ONSLAUGHT,
} IceTrapSetting;

typedef struct {
  u8 hashIndexes[5];

  u8 logic;
  u8 openForest;
  u8 openKakariko;
  u8 openDoorOfTime;
  u8 zorasFountain;
  u8 gerudoFortress;
  u8 rainbowBridge;
  u8 bridgeTokenCount;
  u8 randomGanonsTrials;
  u8 ganonsTrialsCount;

  u8 startingAge;
  u8 bombchusInLogic;
  u8 bombchuDrops;
  u8 randomMQDungeons;
  u8 mqDungeonCount;
  u8 mirrorWorld;

  u8 shuffleSongs;
  u8 tokensanity;
  u8 scrubsanity;
  u8 shuffleCows;
  u8 shuffleKokiriSword;
  u8 shuffleOcarinas;
  u8 shuffleWeirdEgg;
  u8 shuffleGerudoToken;
  u8 shuffleMagicBeans;

  u8 mapsAndCompasses;
  u8 keysanity;
  u8 gerudoKeys;
  u8 bossKeysanity;
  u8 ganonsBossKey;
  u8 lacsCondition;

  u8 skipChildStealth;
  u8 skipTowerEscape;
  u8 skipEponaRace;
  u8 fourPoesCutscene;
  u8 templeOfTimeIntro;
  u8 bigPoeTargetCount;
  u8 numRequiredCuccos;

  u8 damageMultiplier;
  u8 startingTime;
  u8 generateSpoilerLog;

  u8 stickAsAdult;
  u8 boomerangAsAdult;
  u8 hammerAsChild;

  u8 itemPoolValue;
  u8 iceTrapValue;

  u8 dekuTreeDungeonMode;
  u8 dodongosCavernDungeonMode;
  u8 jabuJabusBellyDungeonMode;
  u8 forestTempleDungeonMode;
  u8 fireTempleDungeonMode;
  u8 waterTempleDungeonMode;
  u8 spiritTempleDungeonMode;
  u8 shadowTempleDungeonMode;
  u8 bottomOfTheWellDungeonMode;
  u8 iceCavernDungeonMode;
  u8 gerudoTrainingGroundsDungeonMode;
  u8 ganonsCastleDungeonMode;

  u8 forestTrialSkip;
  u8 fireTrialSkip;
  u8 waterTrialSkip;
  u8 spiritTrialSkip;
  u8 shadowTrialSkip;
  u8 lightTrialSkip;

  u32 dungeonRewardBitMask;

  u8 detailedLogic[100];
  u8 excludeLocations[500];

} SettingsContext;

extern SettingsContext gSettingsContext;
extern const char hashIconNames[32][25];

#endif
