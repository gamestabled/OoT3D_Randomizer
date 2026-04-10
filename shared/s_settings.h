#pragma once
#include "s_types.h"
#include "s_colors.h"
#include "s_enemizer.h"

typedef enum BooleanSetting {
    OFF,
    ON,
} BooleanSetting;

typedef enum SkipSetting {
    DONT_SKIP,
    SKIP,
} SkipSetting;

typedef enum ToggleSetting {
    TOGGLE_ALL_DISABLED,
    TOGGLE_ALL_ENABLED,
    TOGGLE_CHOOSE,
} ToggleSetting;

typedef enum LogicSetting {
    LOGIC_GLITCHLESS,
    LOGIC_GLITCHED,
    LOGIC_NONE,
    LOGIC_VANILLA,
} LogicSetting;

typedef enum OpenForestSetting {
    OPENFOREST_CLOSED,
    OPENFOREST_OPEN,
    OPENFOREST_CLOSED_DEKU,
} OpenForestSetting;

typedef enum OpenKakarikoSetting {
    OPENKAKARIKO_CLOSED,
    OPENKAKARIKO_OPEN,
} OpenKakarikoSetting;

typedef enum OpenDoorOfTimeSetting {
    OPENDOOROFTIME_OPEN,
    OPENDOOROFTIME_CLOSED,
    OPENDOOROFTIME_INTENDED,
} OpenDoorOfTimeSetting;

typedef enum ZorasFountainSetting {
    ZORASFOUNTAIN_NORMAL,
    ZORASFOUNTAIN_ADULT,
    ZORASFOUNTAIN_OPEN,
} ZorasFountainSetting;

typedef enum JabuJabuSetting {
    JABUJABU_CLOSED,
    JABUJABU_OPEN,
} JabuJabuSetting;

typedef enum GerudoFortressSetting {
    GERUDOFORTRESS_NORMAL,
    GERUDOFORTRESS_FAST,
    GERUDOFORTRESS_OPEN,
} GerudoFortressSetting;

typedef enum RainbowBridgeSetting {
    RAINBOWBRIDGE_OPEN,
    RAINBOWBRIDGE_VANILLA,
    RAINBOWBRIDGE_STONES,
    RAINBOWBRIDGE_MEDALLIONS,
    RAINBOWBRIDGE_REWARDS,
    RAINBOWBRIDGE_DUNGEONS,
    RAINBOWBRIDGE_TOKENS,
    RAINBOWBRIDGE_HEARTS,
} RainbowBridgeSetting;

typedef enum LACSConditionSetting {
    LACSCONDITION_VANILLA,
    LACSCONDITION_STONES,
    LACSCONDITION_MEDALLIONS,
    LACSCONDITION_REWARDS,
    LACSCONDITION_DUNGEONS,
    LACSCONDITION_TOKENS,
    LACSCONDITION_HEARTS,
} LACSConditionSetting;

typedef enum EnemyModeSetting {
    ENEMYMODE_RANDOMIZED,
    ENEMYMODE_VANILLA,
    ENEMYMODE_REMOVED,
} EnemyModeSetting;

typedef enum AgeSetting {
    AGE_ADULT,
    AGE_CHILD,
    AGE_RANDOM,
} AgeSetting;

typedef enum ShuffleDungeonEntrancesSetting {
    SHUFFLEDUNGEONS_OFF,
    SHUFFLEDUNGEONS_ON,
    SHUFFLEDUNGEONS_GANON,
} ShuffleDungeonEntrancesSetting;

typedef enum ShuffleBossEntrancesSetting {
    SHUFFLEBOSSES_OFF,
    SHUFFLEBOSSES_AGE_RESTRICTED,
    SHUFFLEBOSSES_FULL,
} ShuffleBossEntrancesSetting;

typedef enum ShuffleInteriorEntrancesSetting {
    SHUFFLEINTERIORS_OFF,
    SHUFFLEINTERIORS_SIMPLE,
    SHUFFLEINTERIORS_ALL,
} ShuffleInteriorEntrancesSetting;

typedef enum AmmoDropsSetting {
    AMMODROPS_VANILLA,
    AMMODROPS_BOMBCHU,
    AMMODROPS_NONE,
} AmmoDropsSetting;

typedef enum HeartDropRefillSetting {
    HEARTDROPREFILL_VANILLA,
    HEARTDROPREFILL_NODROP,
    HEARTDROPREFILL_NOREFILL,
    HEARTDROPREFILL_NODROPREFILL,
} HeartDropRefillSetting;

typedef enum DungeonMode {
    DUNGEONMODE_VANILLA,
    DUNGEONMODE_MQ,
} DungeonMode;

typedef enum RewardShuffleSetting {
    REWARDSHUFFLE_END_OF_DUNGEON,
    REWARDSHUFFLE_ANY_DUNGEON,
    REWARDSHUFFLE_OVERWORLD,
    REWARDSHUFFLE_ANYWHERE,
} RewardShuffleSetting;

typedef enum LinksPocketSetting {
    LINKSPOCKETITEM_DUNGEON_REWARD,
    LINKSPOCKETITEM_ADVANCEMENT,
    LINKSPOCKETITEM_ANYTHING,
    LINKSPOCKETITEM_NOTHING,
} LinksPocketSetting;

typedef enum SongShuffleSetting {
    SONGSHUFFLE_SONG_LOCATIONS,
    SONGSHUFFLE_DUNGEON_REWARDS,
    SONGSHUFFLE_ANYWHERE,
} SongShuffleSetting;

typedef enum ShopsanitySetting {
    SHOPSANITY_OFF,
    SHOPSANITY_ZERO,
    SHOPSANITY_ONE,
    SHOPSANITY_TWO,
    SHOPSANITY_THREE,
    SHOPSANITY_FOUR,
    SHOPSANITY_RANDOM,
} ShopsanitySetting;

typedef enum ShopsanityPriceSetting {
    SHOPSANITY_PRICE_RANDOM,
    SHOPSANITY_PRICE_AFFORDABLE,
    SHOPSANITY_PRICE_CHILD,
    SHOPSANITY_PRICE_ADULT,
    SHOPSANITY_PRICE_GIANT,
    SHOPSANITY_PRICE_TYCOON,
} ShopsanityPriceSetting;

typedef enum TokensanitySetting {
    TOKENSANITY_OFF,
    TOKENSANITY_DUNGEONS,
    TOKENSANITY_OVERWORLD,
    TOKENSANITY_ALL_TOKENS,
} TokensanitySetting;

typedef enum ScrubsanitySetting {
    SCRUBSANITY_OFF,
    SCRUBSANITY_AFFORDABLE,
    SCRUBSANITY_EXPENSIVE,
    SCRUBSANITY_RANDOM_PRICES,
} ScrubsanitySetting;

typedef enum ShuffleMerchantsSetting {
    SHUFFLEMERCHANTS_OFF,
    SHUFFLEMERCHANTS_NO_HINTS,
    SHUFFLEMERCHANTS_HINTS,
} ShuffleMerchantsSetting;

typedef enum ShuffleFrogSongRupeesSetting {
    SHUFFLEFROGSONGRUPEES_OFF,
    SHUFFLEFROGSONGRUPEES_ON,
} ShuffleFrogSongRupeesSetting;

typedef enum ShuffleAdultTradeQuestSetting {
    SHUFFLEADULTTRADEQUEST_OFF,
    SHUFFLEADULTTRADEQUEST_ON,
} ShuffleAdultTradeQuestSetting;

typedef enum ShuffleChestMinigameSetting {
    SHUFFLECHESTMINIGAME_OFF,
    SHUFFLECHESTMINIGAME_SINGLE_KEYS,
    SHUFFLECHESTMINIGAME_PACK,
} ShuffleChestMinigameSetting;

typedef enum ShuffleEnemySoulsSetting {
    SHUFFLEENEMYSOULS_OFF,
    SHUFFLEENEMYSOULS_ALL,
    SHUFFLEENEMYSOULS_BOSSES,
} ShuffleEnemySoulsSetting;

typedef enum SoullessEnemiesLookSetting {
    SOULLESSLOOK_PURPLE_FLAME,
    SOULLESSLOOK_FLASHING,
} SoullessEnemiesLookSetting;

typedef enum MapsAndCompassesSetting {
    MAPSANDCOMPASSES_START_WITH,
    MAPSANDCOMPASSES_VANILLA,
    MAPSANDCOMPASSES_OWN_DUNGEON,
    MAPSANDCOMPASSES_ANY_DUNGEON,
    MAPSANDCOMPASSES_OVERWORLD,
    MAPSANDCOMPASSES_ANYWHERE,
} MapsAndCompassesSetting;

typedef enum KeysanitySetting {
    KEYSANITY_START_WITH,
    KEYSANITY_VANILLA,
    KEYSANITY_OWN_DUNGEON,
    KEYSANITY_ANY_DUNGEON,
    KEYSANITY_OVERWORLD,
    KEYSANITY_ANYWHERE,
} KeysanitySetting;

typedef enum GerudoKeysSetting {
    GERUDOKEYS_VANILLA,
    GERUDOKEYS_ANY_DUNGEON,
    GERUDOKEYS_OVERWORLD,
    GERUDOKEYS_ANYWHERE,
} GerudoKeysSetting;

typedef enum BossKeysanitySetting {
    BOSSKEYSANITY_START_WITH,
    BOSSKEYSANITY_VANILLA,
    BOSSKEYSANITY_OWN_DUNGEON,
    BOSSKEYSANITY_ANY_DUNGEON,
    BOSSKEYSANITY_OVERWORLD,
    BOSSKEYSANITY_ANYWHERE,
} BossKeysanitySetting;

typedef enum GanonsBossKeySetting {
    GANONSBOSSKEY_START_WITH,
    GANONSBOSSKEY_VANILLA,
    GANONSBOSSKEY_OWN_DUNGEON,
    GANONSBOSSKEY_ANY_DUNGEON,
    GANONSBOSSKEY_OVERWORLD,
    GANONSBOSSKEY_ANYWHERE,
    GANONSBOSSKEY_TRIFORCE, // Unselectable option, set automatically for Triforce Hunt
    GANONSBOSSKEY_LACS_VANILLA,
    GANONSBOSSKEY_LACS_MEDALLIONS,
    GANONSBOSSKEY_LACS_STONES,
    GANONSBOSSKEY_LACS_REWARDS,
    GANONSBOSSKEY_LACS_DUNGEONS,
    GANONSBOSSKEY_LACS_TOKENS,
    GANONSBOSSKEY_LACS_HEARTS,
} GanonsBossKeySetting;

typedef enum KeyRingsSetting {
    KEYRINGS_OFF,
    KEYRINGS_ON,
    KEYRINGS_CHOOSE,
    KEYRINGS_RANDOM,
} KeyRingsSetting;

typedef enum KingZoraSpeedSetting {
    KINGZORASPEED_FAST,
    KINGZORASPEED_VANILLA,
    KINGZORASPEED_RANDOM,
    KINGZORASPEED_CUSTOM,
} KingZoraSpeedSetting;

typedef enum QuickTextSetting {
    QUICKTEXT_VANILLA,
    QUICKTEXT_SKIPPABLE,
    QUICKTEXT_INSTANT,
    QUICKTEXT_TURBO,
} QuickTextSetting;

typedef enum SkipSongReplaysSetting {
    SONGREPLAYS_DONT_SKIP,
    SONGREPLAYS_SKIP_NO_SFX,
    SONGREPLAYS_SKIP_KEEP_SFX,
} SkipSongReplaysSetting;

typedef enum NaviNotificationsSetting {
    NAVINOTIFS_SILENCED,
    NAVINOTIFS_NORMAL,
    NAVINOTIFS_CONSTANT,
} NaviNotificationsSetting;

typedef enum ExcludeLocationSetting {
    INCLUDE,
    EXCLUDE,
} ExcludeLocationSetting;

typedef enum StartingInventorySetting {
    STARTINGINVENTORY_NONE,
} StartingInventorySetting;

typedef enum LogicTrickSetting {
    TRICK_DISABLED,
    TRICK_ENABLED,
} LogicTrickSetting;

typedef enum GossipStoneHintsSetting {
    HINTS_NO_HINTS,
    HINTS_NEED_NOTHING,
    HINTS_MASK_OF_TRUTH,
    HINTS_SHARD_OF_AGONY,
} GossipStoneHintsSetting;

typedef enum HintModeSetting {
    HINTMODE_OBSCURE,
    HINTMODE_AMBIGUOUS,
    HINTMODE_CLEAR,
} HintModeSetting;

typedef enum HintDistributionSettings {
    HINTDISTRIBUTION_USELESS,
    HINTDISTRIBUTION_BALANCED,
    HINTDISTRIBUTION_STRONG,
    HINTDISTRIBUTION_VERYSTRONG,
    HINTDISTRIBUTION_PLAYTHROUGH,
} HintDistributionSettings;

typedef enum DamageMultiplierSetting {
    DAMAGEMULTIPLIER_HALF,
    DAMAGEMULTIPLIER_DEFAULT,
    DAMAGEMULTIPLIER_DOUBLE,
    DAMAGEMULTIPLIER_QUADRUPLE,
    DAMAGEMULTIPLIER_OCTUPLE,
    DAMAGEMULTIPLIER_SEXDECUPLE,
    DAMAGEMULTIPLIER_OHKO,
} DamageMultiplierSetting;

typedef enum BonkDamageSetting {
    BONKDAMAGE_NONE,
    BONKDAMAGE_QUARTER,
    BONKDAMAGE_HALF,
    BONKDAMAGE_ONE,
    BONKDAMAGE_TWO,
    BONKDAMAGE_FOUR,
    BONKDAMAGE_OHKO,
} BonkDamageSetting;

typedef enum GloomModeSetting {
    GLOOMMODE_OFF,
    GLOOMMODE_DEATH,
    GLOOMMODE_DAMAGE,
    GLOOMMODE_COLLISION,
    GLOOMMODE_EMPTY,
} GloomModeSetting;

typedef enum StartingTimeSetting {
    STARTINGTIME_DAY,
    STARTINGTIME_NIGHT,
} StartingTimeSetting;

typedef enum ChestAnimationsSetting {
    CHESTANIMATIONS_ALWAYSFAST,
    CHESTANIMATIONS_MATCHCONTENT,
} ChestAnimationsSetting;

typedef enum ChestAppearanceSetting {
    CHESTAPPEARANCE_VANILLA,
    CHESTAPPEARANCE_TEXTURE,
    CHESTAPPEARANCE_SIZE_AND_TEXTURE,
    CHESTAPPEARANCE_CLASSIC,
} ChestAppearanceSetting;

typedef enum RandomTrapDamageSetting {
    RANDOMTRAPS_OFF,
    RANDOMTRAPS_BASIC,
    RANDOMTRAPS_ADVANCED,
} RandomTrapDamageSetting;

typedef enum RupoorTrapSeveritySetting {
    RUPOORTRAPSEVERITY_TEN,
    RUPOORTRAPSEVERITY_RANDOMRATIO,
    RUPOORTRAPSEVERITY_BANKRUPTCY,
} RupoorTrapSeveritySetting;

typedef enum HyperActorsSetting {
    HYPERACTORS_OFF,
    HYPERACTORS_ON,
    HYPERACTORS_CHOOSE,
} HyperActorsSetting;

typedef enum ItemPoolSetting {
    ITEMPOOL_MINIMAL,
    ITEMPOOL_SCARCE,
    ITEMPOOL_BALANCED,
    ITEMPOOL_PLENTIFUL,
} ItemPoolSetting;

typedef enum ArrowSwitchSetting {
    ARROWSWITCH_RIGHT,
    ARROWSWITCH_LEFT,
    ARROWSWITCH_UP,
    ARROWSWITCH_DOWN,
    ARROWSWITCH_TOUCH,
} ArrowSwitchSetting;

typedef enum IceTrapSetting {
    ICETRAPS_OFF,
    ICETRAPS_NORMAL,
    ICETRAPS_EXTRA,
    ICETRAPS_MAYHEM,
    ICETRAPS_ONSLAUGHT,
} IceTrapSetting;

typedef enum GkDurabilitySetting {
    GKDURABILITY_VANILLA,
    GKDURABILITY_RANDOMRISK,
    GKDURABILITY_RANDOMSAFE,
} GkDurabilitySetting;

typedef enum StartingBottleSetting {
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

typedef enum StartingBiggoronSwordSetting {
    STARTINGBGS_NONE,
    STARTINGBGS_GIANTS_KNIFE,
    STARTINGBGS_BIGGORON_SWORD,
} StartingBiggoronSwordSetting;

typedef enum ShuffleMusicSetting {
    SHUFFLEMUSIC_OFF,
    SHUFFLEMUSIC_MIXED,
    SHUFFLEMUSIC_GROUPED,
    SHUFFLEMUSIC_OWN,
} ShuffleMusicSetting;

typedef enum ShuffleSFXSetting {
    SHUFFLESFX_OFF,
    SHUFFLESFX_ALL,
    SHUFFLESFX_SCENESPECIFIC,
    SHUFFLESFX_CHAOS,
} ShuffleSFXSetting;

typedef enum OcarinaNoteInstrumentSetting {
    OCARINA_INSTR_SETTING_RANDOM_CHOICE,
    OCARINA_INSTR_SETTING_SCENE_SPECIFIC,
    OCARINA_INSTR_SETTING_DEFAULT,
} OcarinaNoteInstrumentSetting;

typedef enum DungeonInfo {
    DUNGEON_NEITHER,
    DUNGEON_BARREN,
    DUNGEON_WOTH,
} DungeonInfo;

typedef enum TrailColorMode {
    TRAILCOLOR_VANILLAMODE,
    TRAILCOLOR_FORCEDSIMPLEMODE,
    TRAILCOLOR_RAINBOW,
    TRAILCOLOR_RAINBOW_SIMPLEMODE,
} TrailColorMode;

typedef enum TrailDuration {
    TRAILDURATION_DISABLED,
    TRAILDURATION_VERYSHORT,
    TRAILDURATION_VANILLA,
    TRAILDURATION_LONG,
    TRAILDURATION_VERYLONG,
    TRAILDURATION_LIGHTSABER,
} TrailDuration;

typedef enum MirrorWorld {
    MIRRORWORLD_OFF,
    MIRRORWORLD_ON,
    MIRRORWORLD_SCENESPECIFIC,
    MIRRORWORLD_ENTRANCESPECIFIC,
    MIRRORWORLD_RANDOM,
} MirrorWorld;

typedef enum Region {
    REGION_NA,
    REGION_EUR
} Region;

typedef struct SettingsContext {
    u8 hashIndexes[5];
    u8 region;

    u8 logic;
    u8 openForest;
    u8 openKakariko;
    u8 openDoorOfTime;
    u8 openJabu;
    u8 zorasFountain;
    u8 gerudoFortress;
    u8 rainbowBridge;
    u8 bridgeStoneCount;
    u8 bridgeMedallionCount;
    u8 bridgeRewardCount;
    u8 bridgeDungeonCount;
    u8 bridgeTokenCount;
    u8 bridgeHeartCount;
    u8 randomGanonsTrials;
    u8 ganonsTrialsCount;

    u8 startingAge;
    u8 resolvedStartingAge;
    u8 shuffleDungeonEntrances;
    u8 shuffleBossEntrances;
    u8 shuffleOverworldEntrances;
    u8 shuffleInteriorEntrances;
    u8 shuffleGrottoEntrances;
    u8 shuffleOwlDrops;
    u8 shuffleWarpSongs;
    u8 shuffleOverworldSpawns;
    u8 mixedEntrancePools;
    u8 mixDungeons;
    u8 mixOverworld;
    u8 mixInteriors;
    u8 mixGrottos;
    u8 decoupleEntrances;
    u8 bombchusInLogic;
    u8 ammoDrops;
    u8 heartDropRefill;
    u8 randomMQDungeons;
    u8 mqDungeonCount;
    u8 dungeonModesKnown[12]; // 12 dungeons which can be set Vanilla or MQ
    u8 triforceHunt;
    u8 triforcePiecesTotal;
    u8 triforcePiecesRequired;
    u8 enemizer;
    u8 enemizerList[ENEMY_MAX];

    u8 shuffleRewards;
    u8 linksPocketItem;
    u8 shuffleSongs;
    u8 tokensanity;
    u8 scrubsanity;
    u8 shopsanity;
    u8 shuffleCows;
    u8 shuffleKokiriSword;
    u8 shuffleMasterSword;
    u8 shuffleOcarinas;
    u8 shuffleWeirdEgg;
    u8 shuffleGerudoToken;
    u8 shuffleMagicBeans;
    u8 shuffleMerchants;
    u8 shuffleFrogSongRupees;
    u8 shuffleAdultTradeQuest;
    u8 shuffleChestMinigame;
    u8 shuffleEnemySouls;
    u8 shuffleOcarinaButtons;

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
    u8 lacsHeartCount;

    u8 ringFortress;
    u8 ringForest;
    u8 ringFire;
    u8 ringWater;
    u8 ringSpirit;
    u8 ringShadow;
    u8 ringWell;
    u8 ringGtg;
    u8 ringCastle;

    u8 skipChildStealth;
    u8 skipTowerEscape;
    u8 skipEponaRace;
    u8 skipMinigamePhases;
    u8 freeScarecrow;
    u8 fourPoesCutscene;
    u8 lakeHyliaOwl;
    u8 bigPoeTargetCount;
    u8 numRequiredCuccos;
    u8 kingZoraSpeed;
    u8 exactZoraSpeed;
    u8 completeMaskQuest;
    u8 quickText;
    u8 skipSongReplays;
    u8 keepFWWarpPoint;
    u8 fastBunnyHood;

    u8 damageMultiplier;
    u8 bonkDamage;
    u8 permadeath;
    u8 gloomMode;
    u8 startingTime;
    u8 gossipStoneHints;
    u8 totAltarHints;
    u8 ganonHints;
    u8 sheikHints;
    u8 dampeHint;
    u8 skulltulaHints;
    u8 fishingHints;
    u8 compassesShowReward;
    u8 compassesShowWotH;
    u8 mapsShowDungeonMode;
    u8 chestAnimations;
    u8 chestAppearance;
    u8 chestAgony;
    u8 generateSpoilerLog;
    u8 ingameSpoilers;
    u8 menuOpeningButton;
    u8 arrowSwitchButton;
    u8 randomTrapDmg;
    u8 fireTrap;
    u8 antiFairyTrap;
    u8 rupoorTrap;
    u8 rupoorTrapSeverity;
    u8 curseTraps;
    u8 screenTraps;
    u8 extraArrowEffects;
    u8 hyperBosses;
    u8 hyperMiddleBosses;
    u8 hyperEnemies;
    u8 freeCamera;
    u8 randomGsLocations;
    u8 randomSongNotes;

    u8 faroresWindAnywhere;
    u8 stickAsAdult;
    u8 boomerangAsAdult;
    u8 hammerAsChild;
    u8 slingshotAsAdult;
    u8 bowAsChild;
    u8 hookshotAsChild;
    u8 ironbootsAsChild;
    u8 hoverbootsAsChild;
    u8 masksAsAdult;
    u8 kokiriSwordAsAdult;
    u8 masterSwordAsChild;
    u8 biggoronSwordAsChild;
    u8 dekuShieldAsAdult;
    u8 mirrorShieldAsChild;
    u8 goronTunicAsChild;
    u8 zoraTunicAsChild;
    u8 restoreISG;
    u8 gkDurability;
    u8 retroAmmo;

    u8 itemPoolValue;
    u8 iceTrapValue;
    u8 progressiveGoronSword;

    u8 mp_Enabled;
    u8 mp_SharedProgress;
    u8 mp_SyncId;
    u8 mp_SharedHealth;
    u8 mp_SharedRupees;
    u8 mp_SharedAmmo;

    u8 zTargeting;
    u8 cameraControl;
    u8 motionControl;
    u8 playMusic;
    u8 playSFX;
    u8 naviNotifications;
    u8 ignoreMaskReaction;
    u8 freeCamControl;

    u8 customTunicColors;
    u8 rainbowChildTunic;
    u8 rainbowKokiriTunic;
    u8 rainbowGoronTunic;
    u8 rainbowZoraTunic;
    u8 customNaviColors;
    u8 rainbowIdleNaviInnerColor;
    u8 rainbowNPCNaviInnerColor;
    u8 rainbowEnemyNaviInnerColor;
    u8 rainbowPropNaviInnerColor;
    u8 rainbowIdleNaviOuterColor;
    u8 rainbowNPCNaviOuterColor;
    u8 rainbowEnemyNaviOuterColor;
    u8 rainbowPropNaviOuterColor;
    u8 customTrailEffects;
    u8 rainbowSwordTrailInnerColor;
    u8 rainbowSwordTrailOuterColor;
    Color_RGBA8 boomerangTrailColor;
    u8 boomerangTrailColorMode;
    u8 boomerangTrailDuration;
    u8 rainbowChuTrailInnerColor;
    u8 rainbowChuTrailOuterColor;
    u8 bombchuTrailDuration;

    u8 coloredKeys;
    u8 coloredBossKeys;
    u8 mirrorWorld;
    u8 soullessEnemiesLook;

    u8 shuffleSFX;
    u8 shuffleSFXFootsteps;
    u8 shuffleSFXLinkVoice;
    u8 shuffleSFXCategorically;

    u8 ocarinaNoteInstrument;

    union {
        u8 dungeonModes[12];
        struct {
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
            u8 ganonsCastleDungeonMode;
            u8 gerudoTrainingGroundsDungeonMode;
        };
    };

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
    u8 startingBottle4;
    u8 startingRutoBottle;
    u8 startingChildTrade;
    u8 startingOcarina;
    u8 startingKokiriSword;
    u8 startingBiggoronSword;
    u8 startingMagicMeter;
    u8 startingDoubleDefense;
    u8 startingHearts;

    u32 startingQuestItems;
    u32 startingDungeonReward;
    u32 startingEquipment;
    u32 startingUpgrades;

    u8 startingEnemySouls[8];
    u8 startingOcarinaButtons;

    u8 startingTokens;

} SettingsContext;
