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
  OPENFOREST_CLOSED_DEKU,
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
  RAINBOWBRIDGE_REWARDS,
  RAINBOWBRIDGE_DUNGEONS,
  RAINBOWBRIDGE_TOKENS,
} RainbowBridgeSetting;

typedef enum {
  LACSCONDITION_VANILLA,
  LACSCONDITION_STONES,
  LACSCONDITION_MEDALLIONS,
  LACSCONDITION_REWARDS,
  LACSCONDITION_DUNGEONS,
  LACSCONDITION_TOKENS,
} LACSConditionSetting;

typedef enum {
  AGE_ADULT,
  AGE_CHILD,
  AGE_RANDOM,
} AgeSetting;

typedef enum {
  AMMODROPS_VANILLA,
  AMMODROPS_BOMBCHU,
  AMMODROPS_NONE,
} AmmoDropsSetting;

typedef enum {
  HEARTDROPREFILL_VANILLA,
  HEARTDROPREFILL_NODROP,
  HEARTDROPREFILL_NOREFILL,
  HEARTDROPREFILL_NODROPREFILL,
} HeartDropRefillSetting;

typedef enum {
  DUNGEONMODE_VANILLA,
  DUNGEONMODE_MQ,
} DungeonMode;

typedef enum {
  REWARDSHUFFLE_END_OF_DUNGEON,
  REWARDSHUFFLE_ANY_DUNGEON,
  REWARDSHUFFLE_OVERWORLD,
  REWARDSHUFFLE_ANYWHERE,
} RewardShuffleSetting;

typedef enum {
  LINKSPOCKETITEM_DUNGEON_REWARD,
  LINKSPOCKETITEM_ADVANCEMENT,
  LINKSPOCKETITEM_ANYTHING,
  LINKSPOCKETITEM_NOTHING,
} LinksPocketSetting;

typedef enum {
  SONGSHUFFLE_SONG_LOCATIONS,
  SONGSHUFFLE_DUNGEON_REWARDS,
  SONGSHUFFLE_ANYWHERE,
} SongShuffleSetting;

typedef enum {
  SHOPSANITY_OFF,
  SHOPSANITY_ZERO,
  SHOPSANITY_ONE,
  SHOPSANITY_TWO,
  SHOPSANITY_THREE,
  SHOPSANITY_FOUR,
  SHOPSANITY_RANDOM,
} ShopsanitySetting;

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
  SHUFFLEMERCHANTS_OFF,
  SHUFFLEMERCHANTS_NO_HINTS,
  SHUFFLEMERCHANTS_HINTS,
} ShuffleMerchantsSetting;

typedef enum {
  MAPSANDCOMPASSES_START_WITH,
  MAPSANDCOMPASSES_VANILLA,
  MAPSANDCOMPASSES_OWN_DUNGEON,
  MAPSANDCOMPASSES_ANY_DUNGEON,
  MAPSANDCOMPASSES_OVERWORLD,
  MAPSANDCOMPASSES_ANYWHERE,
} MapsAndCompassesSetting;

typedef enum {
  KEYSANITY_START_WITH,
  KEYSANITY_VANILLA,
  KEYSANITY_OWN_DUNGEON,
  KEYSANITY_ANY_DUNGEON,
  KEYSANITY_OVERWORLD,
  KEYSANITY_ANYWHERE,
} KeysanitySetting;

typedef enum {
  GERUDOKEYS_VANILLA,
  GERUDOKEYS_ANY_DUNGEON,
  GERUDOKEYS_OVERWORLD,
  GERUDOKEYS_ANYWHERE,
} GerudoKeysSetting;

typedef enum {
  BOSSKEYSANITY_START_WITH,
  BOSSKEYSANITY_VANILLA,
  BOSSKEYSANITY_OWN_DUNGEON,
  BOSSKEYSANITY_ANY_DUNGEON,
  BOSSKEYSANITY_OVERWORLD,
  BOSSKEYSANITY_ANYWHERE,
} BossKeysanitySetting;

typedef enum {
  GANONSBOSSKEY_START_WITH,
  GANONSBOSSKEY_VANILLA,
  GANONSBOSSKEY_OWN_DUNGEON,
  GANONSBOSSKEY_ANY_DUNGEON,
  GANONSBOSSKEY_OVERWORLD,
  GANONSBOSSKEY_ANYWHERE,
  GANONSBOSSKEY_LACS_VANILLA,
  GANONSBOSSKEY_LACS_MEDALLIONS,
  GANONSBOSSKEY_LACS_STONES,
  GANONSBOSSKEY_LACS_REWARDS,
  GANONSBOSSKEY_LACS_DUNGEONS,
  GANONSBOSSKEY_LACS_TOKENS,
} GanonsBossKeySetting;

typedef enum {
  INCLUDE,
  EXCLUDE,
} ExcludeLocationSetting;

typedef enum {
  STARTINGINVENTORY_NONE,
} StartingInventorySetting;

typedef enum {
  TRICK_DISABLED,
  TRICK_ENABLED,
} LogicTrickSetting;

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
  HINTS_NO_HINTS,
  HINTS_NEED_NOTHING,
  HINTS_MASK_OF_TRUTH,
  HINTS_SHARD_OF_AGONY,
} GossipStoneHintsSetting;

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

typedef enum {
  GKDURABILITY_VANILLA,
  GKDURABILITY_RANDOMRISK,
  GKDURABILITY_RANDOMSAFE,
} GkDurabilitySetting;

typedef enum {
  STARTINGBOTTLE_NONE,
  STARTINGBOTTLE_EMPTY_BOTTLE,
  STARTINGBOTTLE_RED_POTION,
  STARTINGBOTTLE_GREEN_POTION,
  STARTINGBOTTLE_BLUE_POTION,
  STARTINGBOTTLE_FAIRY,
  STARTINGBOTTLE_FISH,
  STARTINGBOTTLE_MILK,
  STARTINGBOTTLE_BLUE_FIRE,
  STARTINGBOTTLE_BUGS,
  STARTINGBOTTLE_BIG_POE,
  STARTINGBOTTLE_HALF_MILK,
  STARTINGBOTTLE_POE,
} StartingBottleSetting;

typedef struct {
  u8 hashIndexes[5];

  u8 logic;
  u8 openForest;
  u8 openKakariko;
  u8 openDoorOfTime;
  u8 zorasFountain;
  u8 gerudoFortress;
  u8 rainbowBridge;
  u8 bridgeStoneCount;
  u8 bridgeMedallionCount;
  u8 bridgeRewardCount;
  u8 bridgeDungeonCount;
  u8 bridgeTokenCount;
  u8 randomGanonsTrials;
  u8 ganonsTrialsCount;

  u8 startingAge;
  u8 resolvedStartingAge;
  u8 shuffleDungeonEntrances;
  u8 bombchusInLogic;
  u8 ammoDrops;
  u8 heartDropRefill;
  u8 randomMQDungeons;
  u8 mqDungeonCount;

  u8 shuffleRewards;
  u8 linksPocketItem;
  u8 shuffleSongs;
  u8 tokensanity;
  u8 scrubsanity;
  u8 shopsanity;
  u8 shuffleCows;
  u8 shuffleKokiriSword;
  u8 shuffleOcarinas;
  u8 shuffleWeirdEgg;
  u8 shuffleGerudoToken;
  u8 shuffleMagicBeans;
  u8 shuffleMerchants;

  u8 mapsAndCompasses;
  u8 keysanity;
  u8 gerudoKeys;
  u8 bossKeysanity;
  u8 ganonsBossKey;
  u8 lacsCondition;
  u8 lacsMedallionCount;
  u8 lacsStoneCount;
  u8 lacsRewardCount;
  u8 lacsDungeonCount;
  u8 lacsTokenCount;

  u8 skipChildStealth;
  u8 skipTowerEscape;
  u8 skipEponaRace;
  u8 skipMinigamePhases;
  u8 freeScarecrow;
  u8 fourPoesCutscene;
  u8 templeOfTimeIntro;
  u8 bigPoeTargetCount;
  u8 numRequiredCuccos;
  u8 kingZoraSpeed;
  u8 completeMaskQuest;

  u8 damageMultiplier;
  u8 startingTime;
  u8 gossipStoneHints;
  u8 chestAnimations;
  u8 chestSize;
  u8 generateSpoilerLog;
  u8 ingameSpoilers;
  u8 menuOpeningButton;
  u8 randomTrapDmg;

  u8 faroresWindAnywhere;
  u8 stickAsAdult;
  u8 boomerangAsAdult;
  u8 hammerAsChild;
  u8 gkDurability;

  u8 itemPoolValue;
  u8 iceTrapValue;

  u8 customTunicColors;
  u8 coloredKeys;
  u8 coloredBossKeys;
  u8 mirrorWorld;

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

  u32 linksPocketRewardBitMask;

  u8 startingConsumables;
  u8 startingMaxRupees;
  u8 startingStickCapacity;
  u8 startingNutCapacity;
  u8 startingBombBag;
  u8 startingBombchus;
  u8 startingBow;
  u8 startingFireArrows;
  u8 startingIceArrows;
  u8 startingLightArrows;
  u8 startingDinsFire;
  u8 startingFaroresWind;
  u8 startingNayrusLove;
  u8 startingSlingshot;
  u8 startingBoomerang;
  u8 startingLensOfTruth;
  u8 startingMagicBean;
  u8 startingMegatonHammer;
  u8 startingHookshot;
  u8 startingIronBoots;
  u8 startingHoverBoots;
  u8 startingBottle1;
  u8 startingBottle2;
  u8 startingBottle3;
  u8 startingRutoBottle;
  u8 startingOcarina;
  u8 startingKokiriSword;
  u8 startingBiggoronSword;
  u8 startingMagicMeter;
  u8 startingDoubleDefense;
  u8 startingHealth;

  u32 startingQuestItems;
  u32 startingEquipment;
  u32 startingUpgrades;

} SettingsContext;

extern SettingsContext gSettingsContext;
extern const char hashIconNames[32][25];

s32 Settings_ApplyDamageMultiplier(GlobalContext*, s32);
u32 Hash(u32);
u8  Bias(u32);

#endif
