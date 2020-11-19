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
} DamageMUltiplierSetting;

typedef enum {
  ZORASFOUNTAIN_NORMAL,
  ZORASFOUNTAIN_ADULT,
  ZORASFOUNTAIN_OPEN,
} ZorasFountainSetting;

typedef enum {
  STARTINGTIME_DAY,
  STARTINGTIME_NIGHT,
} StartingTimeSetting;

typedef enum {
  KEYSANITY_VANILLA,
  KEYSANITY_DUNGEON_ONLY,
  KEYSANITY_ALL_LOCATIONS,
} KeyasnitySetting;

typedef enum {
  BOSSKEYSANITY_VANILLA,
  BOSSKEYSANITY_DUNGEON_ONLY,
  BOSSKEYSANITY_ALL_LOCATIONS,
} BossKeysanitySetting;

typedef enum {
  MAPSANDCOMPASSES_VANILLA,
  MAPSANDCOMPASSES_DUNGEON_ONLY,
  MAPSANDCOMPASSES_ALL_LOCATIONS,
} MapsAndCompassesSetting;

typedef enum {
  TOKENSANITY_VANILLA,
  TOKENSANITY_ALL_LOCATIONS,
} TokensanitySetting;

typedef enum {
  SCRUBSANITY_OFF,
  SCRUBSANITY_AFFORDABLE,
  SCRUBSANITY_EXPENSIVE,
  SCRUBSANITY_RANDOM_PRICES,
} ScrubsanitySetting;

typedef enum {
  AGE_ADULT,
  AGE_CHILD,
} AgeSetting;

typedef struct {
  u8 openForest;
  u8 openKakariko;
  u8 rainbowBridge;
  u8 gerudoFortress;
  u8 damageMultiplier;
  u8 zorasFountain;
  u8 startingAge;
  u8 timeOfDay;
  u8 scrubsanity;
  u8 lacsCondition;

  u8 openDoorOfTime;

  u32 dungeonRewardBitMask;
} SettingsContext;

extern SettingsContext gSettingsContext;

#endif
