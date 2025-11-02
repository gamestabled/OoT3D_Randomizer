#pragma once

#include <3ds.h>

#include <array>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <string_view>
#include <type_traits>
#include <variant>
#include <vector>

#include "../code/src/settings.h"
#include "category.hpp"
#include "cosmetics.hpp"
#include "debug.hpp"
#include "menu.hpp"
#include "pool_functions.hpp"
#include "utils.hpp"
#include "glitches.hpp"

class Option {
  public:
    static Option Bool(std::string name_, std::vector<std::string> options_,
                       std::vector<std::string_view> optionDescriptions_,
                       OptionCategory category_ = OptionCategory::Setting, u8 defaultOption_ = 0,
                       bool defaultHidden_ = false) {
        return Option{ false,     u8{ 0 },        std::move(name_), std::move(options_), std::move(optionDescriptions_),
                       category_, defaultOption_, defaultHidden_ };
    }

    static Option U8(std::string name_, std::vector<std::string> options_,
                     std::vector<std::string_view> optionDescriptions_,
                     OptionCategory category_ = OptionCategory::Setting, u8 defaultOption_ = 0,
                     bool defaultHidden_ = false) {
        return Option{ u8{ 0 },   u8{ 0 },        std::move(name_), std::move(options_), std::move(optionDescriptions_),
                       category_, defaultOption_, defaultHidden_ };
    }

    static Option Bool(u8 indent_, std::string name_, std::vector<std::string> options_,
                       std::vector<std::string_view> optionDescriptions_,
                       OptionCategory category_ = OptionCategory::Setting, u8 defaultOption_ = 0,
                       bool defaultHidden_ = false) {
        return Option{ false,     indent_,        std::move(name_), std::move(options_), std::move(optionDescriptions_),
                       category_, defaultOption_, defaultHidden_ };
    }

    static Option U8(u8 indent_, std::string name_, std::vector<std::string> options_,
                     std::vector<std::string_view> optionDescriptions_,
                     OptionCategory category_ = OptionCategory::Setting, u8 defaultOption_ = 0,
                     bool defaultHidden_ = false) {
        return Option{ u8{ 0 },   indent_,        std::move(name_), std::move(options_), std::move(optionDescriptions_),
                       category_, defaultOption_, defaultHidden_ };
    }

    template <typename T> T Value() const {
        return std::get<T>(var);
    }

    template <typename T> bool Is(T other) const {
        static_assert(std::is_integral_v<T> || std::is_enum_v<T>, "T must be an integral type or an enum.");

        if constexpr ((std::is_integral_v<T> && !std::is_same_v<bool, T>) || std::is_enum_v<T>) {
            return Value<u8>() == static_cast<u8>(other);
        } else {
            return Value<bool>() == static_cast<bool>(other);
        }
    }

    template <typename T> bool IsNot(T other) const {
        return !Is(other);
    }

    explicit operator bool() const {
        if (std::holds_alternative<bool>(var)) {
            return Value<bool>();
        } else {
            return Value<u8>() != 0;
        }
    }

    void SetOptions(std::vector<std::string> o) {
        options = std::move(o);
        SetToDefault();
    }

    const std::vector<std::string>& GetOptions() {
        return options;
    }

    size_t GetOptionCount() const {
        return options.size();
    }

    u8 GetIndent() const {
        return indent;
    }

    const std::string& GetName() const {
        return name;
    }

    const std::string& GetSelectedOptionText() const {
        return options[selectedOption];
    }

    void SetSelectedOptionText(std::string newText) {
        options[selectedOption] = std::move(newText);
    }

    bool IsDefaultSelected() {
        return selectedOption == defaultOption;
    }

    void SetToDefault() {
        SetSelectedIndex(defaultOption);
        hidden = defaultHidden;
    }

    std::string_view GetSelectedOptionDescription() const {
        // bounds checking
        if (selectedOption >= optionDescriptions.size()) {
            return optionDescriptions[optionDescriptions.size() - 1];
        }
        return optionDescriptions[selectedOption];
    }

    u8 GetSelectedOptionIndex() const {
        return selectedOption;
    }

    void ScrollOptionIndex(u32 kDown, bool fastScrolling = false) {
        u32 scrollSpeed = (fastScrolling && options.size() > 2) ? 10 : 1;

        if ((kDown & KEY_RIGHT) != 0) {
            selectedOption += scrollSpeed;
            if (selectedOption >= options.size()) {
                selectedOption %= options.size();
            }
        } else if ((kDown & KEY_LEFT) != 0) {
            selectedOption -= scrollSpeed;
            if (selectedOption >= options.size()) {
                selectedOption = (options.size() - 1) - ((UINT8_MAX - selectedOption) % options.size());
            }
        }
    }

    void SetVariable() {
        if (std::holds_alternative<bool>(var)) {
            var.emplace<bool>(selectedOption != 0);
        } else {
            var.emplace<u8>(selectedOption);
        }
    }

    void SetSelectedIndex(size_t idx) {
        selectedOption = idx;
        if (selectedOption >= options.size()) {
            printf("\x1b[30;0HERROR: Incompatible selection for %s\n", name.c_str());
            selectedOption = 0;
        }

        SetVariable();
    }

    void SetSelectedIndexByString(std::string newSetting) {
        using namespace Cosmetics;

        // Special case for custom cosmetic settings
        if (options.size() > CUSTOM_COLOR) {
            if (newSetting.compare(0, 8, CUSTOM_COLOR_PREFIX) == 0 &&
                options[CUSTOM_COLOR].compare(0, 8, CUSTOM_COLOR_PREFIX) == 0) {
                SetSelectedIndex(CUSTOM_COLOR);
                SetSelectedOptionText(newSetting);
                return;
            }
        }

        for (size_t i = 0; i < options.size(); i++) {
            std::string settingName = SanitizedString(options[i]);
            if (settingName == newSetting) {
                SetSelectedIndex(i);
                return;
            }
        }
    }

    void Lock() {
        locked = true;
    }

    void Unlock() {
        locked = false;
    }

    bool IsLocked() const {
        return locked;
    }

    void Hide() {
        hidden = true;
    }

    void Unhide() {
        hidden = false;
    }

    bool IsHidden() const {
        return hidden;
    }

    bool IsCategory(OptionCategory category) const {
        return category == this->category;
    }

  private:
    Option(u8 var_, u8 indent_, std::string name_, std::vector<std::string> options_,
           std::vector<std::string_view> optionDescriptions_, OptionCategory category_, u8 defaultOption_,
           bool defaultHidden_)
        : var(var_), indent(indent_), name(std::move(name_)), options(std::move(options_)),
          optionDescriptions(std::move(optionDescriptions_)), category(category_), defaultOption(defaultOption_),
          defaultHidden(defaultHidden_) {
        selectedOption = defaultOption;
        hidden         = defaultHidden;
        SetVariable();
    }

    Option(bool var_, u8 indent_, std::string name_, std::vector<std::string> options_,
           std::vector<std::string_view> optionDescriptions_, OptionCategory category_, u8 defaultOption_,
           bool defaultHidden_)
        : var(var_), indent(indent_), name(std::move(name_)), options(std::move(options_)),
          optionDescriptions(std::move(optionDescriptions_)), category(category_), defaultOption(defaultOption_),
          defaultHidden(defaultHidden_) {
        selectedOption = defaultOption;
        hidden         = defaultHidden;
        SetVariable();
    }

    std::variant<bool, u8> var;
    u8 indent = 0;
    std::string name;
    std::vector<std::string> options;
    std::vector<std::string_view> optionDescriptions;
    u8 selectedOption = 0;
    bool locked       = false;
    bool hidden       = false;
    OptionCategory category;
    u8 defaultOption   = 0;
    bool defaultHidden = false;
};

enum class MenuType {
    MainMenu,
    SubMenu,
    Action,
};

class Menu {
  public:
    static Menu SubMenu(std::string name_, std::vector<Option*>* settingsList_, std::string_view description_ = "",
                        bool printInSpoiler_ = true) {
        return Menu{ std::move(name_), MenuType::SubMenu,       std::move(settingsList_),
                     OPTION_MENU,      std::move(description_), printInSpoiler_ };
    }

    static Menu SubMenu(std::string name_, std::vector<Menu*>* itemsList_, std::string_view description_ = "",
                        bool printInSpoiler_ = true) {
        return Menu{ std::move(name_), MenuType::SubMenu,       std::move(itemsList_),
                     SUB_MENU,         std::move(description_), printInSpoiler_ };
    }

    static Menu Action(std::string name_, u8 mode_, std::string_view description_ = "") {
        return Menu{ std::move(name_), MenuType::Action, std::move(mode_), std::move(description_) };
    }

    Menu() = default;

    Menu(std::string name_, MenuType type_, std::vector<Option*>* settingsList_, u8 mode_,
         std::string_view description_ = "", bool printInSpoiler_ = true)
        : name(std::move(name_)), type(type_), settingsList(std::move(settingsList_)), mode(mode_),
          description(std::move(description_)), printInSpoiler(printInSpoiler_) {
    }

    Menu(std::string name_, MenuType type_, std::vector<Menu*>* itemsList_, u8 mode_,
         std::string_view description_ = "", bool printInSpoiler_ = true)
        : name(std::move(name_)), type(type_), itemsList(std::move(itemsList_)), mode(mode_),
          description(std::move(description_)), printInSpoiler(printInSpoiler_) {
    }

    Menu(std::string name_, MenuType type_, u8 mode_, std::string_view description_ = "")
        : name(std::move(name_)), type(type_), mode(mode_), description(std::move(description_)) {
    }

    void ResetMenuIndex() {
        if (mode == OPTION_MENU) {
            for (size_t i = 0; i < settingsList->size(); i++) {
                if (!settingsList->at(i)->IsLocked() && !settingsList->at(i)->IsHidden()) {
                    menuIdx      = i;
                    settingBound = i;
                    return;
                }
            }
        }
        menuIdx      = 0;
        settingBound = 0;
    }

    void Lock() {
        locked = true;
    }

    void Unlock() {
        locked = false;
    }

    bool IsLocked() const {
        return locked;
    }

    std::string name;
    MenuType type;
    std::vector<Option*>* settingsList;
    std::vector<Menu*>* itemsList;
    u8 mode;
    u16 menuIdx                  = 0;
    u16 settingBound             = 0;
    int selectedSetting          = 0;
    std::string_view description = "";
    bool printInSpoiler          = true;
    bool locked                  = false;
};

namespace Settings {
void UpdateSettings();
SettingsContext FillContext();
void InitSettings();
void SetDefaultSettings();
void ResolveExcludedLocationConflicts();
void RandomizeAllSettings(const bool selectOptions = false);
void ForceChange(u32 kDown, Option* currentSetting);
const std::vector<Menu*> GetAllOptionMenus();
/// Gives the numerical value of the selected glitch option.
/// Always returns 0 if logic is not set to Glitched.
u8 GlitchValue(Option& glitchOption);
/// Checks if the glitch's set difficulty is the same or higher than the given difficulty.
/// Always returns false if logic is not set to Glitched.
bool GlitchEnabled(Option& glitchOption, GlitchDifficulty glitchDifficulty);
/// Checks if the misc glitch is enabled.
/// Always returns false if logic is not set to Glitched.
bool GlitchEnabled(Option& glitchOption);
/// @brief Checks if incompatible settings are selected and prints error message.
/// @return True if settings are valid.
bool ValidateSettings();
/// Returns the full title id of the selected region.
std::string TitleId();

extern std::string seed;
extern std::string version;
extern std::array<u8, 5> hashIconIndexes;

extern Option OpenForest;
extern Option OpenKakariko;
extern Option OpenDoorOfTime;
extern Option ZorasFountain;
extern Option OpenJabu;
extern Option GerudoFortress;
extern Option Bridge;
extern Option BridgeStoneCount;
extern Option BridgeMedallionCount;
extern Option BridgeRewardCount;
extern Option BridgeDungeonCount;
extern Option BridgeTokenCount;
extern Option BridgeHeartCount;
extern Option RandomGanonsTrials;
extern Option GanonsTrialsCount;

extern Option StartingAge;
extern u8 ResolvedStartingAge;
extern Option ShuffleEntrances;
extern Option ShuffleDungeonEntrances;
extern Option ShuffleBossEntrances;
extern Option ShuffleOverworldEntrances;
extern Option ShuffleInteriorEntrances;
extern Option ShuffleGrottoEntrances;
extern Option ShuffleOwlDrops;
extern Option ShuffleWarpSongs;
extern Option ShuffleOverworldSpawns;
extern Option MixedEntrancePools;
extern Option MixDungeons;
extern Option MixOverworld;
extern Option MixInteriors;
extern Option MixGrottos;
extern Option DecoupleEntrances;
extern Option BombchusInLogic;
extern Option AmmoDrops;
extern Option HeartDropRefill;
extern Option MQDungeonCount;
extern Option SetDungeonTypes;
extern Option TriforceHunt;
extern Option TriforcePiecesTotal;
extern Option TriforcePiecesRequired;
extern Option Enemizer;
extern Option EnemizerListToggle;
extern std::vector<Option*> enemizerListOptions;

extern Option ShuffleRewards;
extern Option LinksPocketItem;
extern Option ShuffleSongs;
extern Option Shopsanity;
extern Option ShopsanityPrices;
extern Option Tokensanity;
extern Option Scrubsanity;
extern Option ShuffleCows;
extern Option ShuffleKokiriSword;
extern Option ShuffleMasterSword;
extern Option ShuffleOcarinas;
extern Option ShuffleWeirdEgg;
extern Option ShuffleZeldasLetter;
extern Option ShuffleGerudoToken;
extern Option ShuffleMagicBeans;
extern Option ShuffleMerchants;
extern Option ShuffleFrogSongRupees;
extern Option ShuffleAdultTradeQuest;
extern Option ShuffleChestMinigame;
extern Option ShuffleEnemySouls;
extern Option ShuffleOcarinaButtons;
extern Option ShuffleRupees;

extern Option MapsAndCompasses;
extern Option Keysanity;
extern Option GerudoKeys;
extern Option BossKeysanity;
extern Option GanonsBossKey;
extern u8 LACSCondition;
extern Option LACSMedallionCount;
extern Option LACSStoneCount;
extern Option LACSRewardCount;
extern Option LACSDungeonCount;
extern Option LACSTokenCount;
extern Option LACSHeartCount;
extern Option KeyRings;
extern Option RingFortress;
extern Option RingForest;
extern Option RingFire;
extern Option RingWater;
extern Option RingSpirit;
extern Option RingShadow;
extern Option RingWell;
extern Option RingGtg;
extern Option RingCastle;

extern Option SkipChildStealth;
extern Option SkipTowerEscape;
extern Option SkipEponaRace;
extern Option SkipMinigamePhases;
extern Option FreeScarecrow;
extern Option FourPoesCutscene;
extern Option LakeHyliaOwl;
extern Option BigPoeTargetCount;
extern Option NumRequiredCuccos;
extern Option KingZoraSpeed;
extern Option ExactZoraSpeed;
extern Option CompleteMaskQuest;
extern Option QuickText;
extern Option SkipSongReplays;
extern Option KeepFWWarpPoint;
extern Option FastBunnyHood;

extern Option Racing;
extern Option GossipStoneHints;
extern Option ClearerHints;
extern Option HintDistribution;
extern Option BonusGossipHints;
extern Option MiscHints;
extern Option ToTAltarHints;
extern Option GanonHints;
extern Option DampeHint;
extern Option SkulltulaHints;
extern Option FishingHints;
extern Option CompassesShowReward;
extern Option CompassesShowWotH;
extern Option MapsShowDungeonMode;
extern Option DamageMultiplier;
extern Option Permadeath;
extern Option GloomMode;
extern Option StartingTime;
extern Option ChestAnimations;
extern Option ChestAppearance;
extern Option ChestAgony;
extern Option GenerateSpoilerLog;
extern Option IngameSpoilers;
extern Option MenuOpeningButton;
extern Option ArrowSwitchButton;
extern Option RandomTrapDmg;
extern Option FireTrap;
extern Option AntiFairyTrap;
extern Option CurseTraps;
extern Option ScreenTraps;
extern Option ExtraArrowEffects;
extern Option HyperActors;
extern Option HyperBosses;
extern Option HyperMiddleBosses;
extern Option HyperEnemies;
extern Option FreeCamera;
extern Option RandomGsLocations;
extern Option GsLocGuaranteeNew;
extern bool HasNightStart;

extern Option FaroresWindAnywhere;
extern Option AgeItemsInLogic;
extern Option StickAsAdult;
extern Option BoomerangAsAdult;
extern Option HammerAsChild;
extern Option SlingshotAsAdult;
extern Option BowAsChild;
extern Option HookshotAsChild;
extern Option IronBootsAsChild;
extern Option HoverBootsAsChild;
extern Option MasksAsAdult;
extern Option KokiriSwordAsAdult;
extern Option MasterSwordAsChild;
extern Option BiggoronSwordAsChild;
extern Option DekuShieldAsAdult;
extern Option MirrorShieldAsChild;
extern Option GoronTunicAsChild;
extern Option ZoraTunicAsChild;
extern Option RestoreISG;
extern Option GkDurability;
extern Option RetroAmmo;

extern Option ItemPoolValue;
extern Option IceTrapValue;
extern Option RemoveDoubleDefense;
extern Option ProgressiveGoronSword;

// Starting Inventory
extern Option StartingConsumables;
extern Option StartingMaxRupees;
extern Option StartingStickCapacity;
extern Option StartingNutCapacity;
extern Option StartingBombBag;
extern Option StartingBombchus;
extern Option StartingBow;
extern Option StartingFireArrows;
extern Option StartingIceArrows;
extern Option StartingLightArrows;
extern Option StartingDinsFire;
extern Option StartingFaroresWind;
extern Option StartingNayrusLove;
extern Option StartingSlingshot;
extern Option StartingBoomerang;
extern Option StartingLensOfTruth;
extern Option StartingMagicBean;
extern Option StartingMegatonHammer;
extern Option StartingHookshot;
extern Option StartingIronBoots;
extern Option StartingHoverBoots;
extern Option StartingBottle1;
extern Option StartingBottle2;
extern Option StartingBottle3;
extern Option StartingBottle4;
extern Option StartingRutoBottle;
extern Option StartingChildTrade;
extern Option StartingOcarina;
extern Option StartingZeldasLullaby;
extern Option StartingEponasSong;
extern Option StartingSariasSong;
extern Option StartingSunsSong;
extern Option StartingSongOfTime;
extern Option StartingSongOfStorms;
extern Option StartingMinuetOfForest;
extern Option StartingBoleroOfFire;
extern Option StartingSerenadeOfWater;
extern Option StartingRequiemOfSpirit;
extern Option StartingNocturneOfShadow;
extern Option StartingPreludeOfLight;
extern Option StartingKokiriSword;
extern Option StartingMasterSword;
extern Option StartingBiggoronSword;
extern Option StartingDekuShield;
extern Option StartingHylianShield;
extern Option StartingMirrorShield;
extern Option StartingGoronTunic;
extern Option StartingZoraTunic;
extern Option StartingMagicMeter;
extern Option StartingStrength;
extern Option StartingScale;
extern Option StartingWallet;
extern Option StartingShardOfAgony;
extern Option StartingDoubleDefense;
extern Option StartingHearts;
extern Option StartingKokiriEmerald;
extern Option StartingGoronRuby;
extern Option StartingZoraSapphire;
extern Option StartingForestMedallion;
extern Option StartingFireMedallion;
extern Option StartingWaterMedallion;
extern Option StartingSpiritMedallion;
extern Option StartingShadowMedallion;
extern Option StartingLightMedallion;
extern Option StartingSkulltulaToken;

extern Option StartingOcarinaButtonL;
extern Option StartingOcarinaButtonR;
extern Option StartingOcarinaButtonX;
extern Option StartingOcarinaButtonY;
extern Option StartingOcarinaButtonA;

// Logic Settings
extern Option Logic;
extern Option LocationsReachable;
extern Option NightGSExpectSuns;

// Trick Settings
extern Option ToggleAllTricks;
extern Option LogicGrottosWithoutAgony;
extern Option LogicVisibleCollision;
extern Option LogicFewerTunicRequirements;
extern Option LogicLostWoodsGSBean;
extern Option LogicLabDiving;
extern Option LogicLabWallGS;
extern Option LogicGraveyardPoH;
extern Option LogicChildDampeRacePoH;
extern Option LogicGVHammerChest;
extern Option LogicGerudoKitchen;
extern Option LogicGerudoChildClimb;
extern Option LogicLensWasteland;
extern Option LogicReverseWasteland;
extern Option LogicColossusGS;
extern Option LogicOutsideGanonsGS;
extern Option LogicManOnRoof;
extern Option LogicWindmillPoHHookshot;
extern Option LogicDMTBombable;
extern Option LogicDMTSoilGS;
extern Option LogicDMTSummitHover;
extern Option LogicLinkGoronDins;
extern Option LogicGoronCityLeftMost;
extern Option LogicGoronCityPot;
extern Option LogicGoronCityPotWithStrength;
extern Option LogicChildRollingWithStrength;
extern Option LogicCraterUpperToLower;
extern Option LogicCraterBeanPoHWithHovers;
extern Option LogicBiggoronBolero;
extern Option LogicZoraRiverLower;
extern Option LogicZoraRiverUpper;
extern Option LogicZFGreatFairy;
extern Option LogicDekuB1WebsWithBow;
extern Option LogicDekuB1Skip;
extern Option LogicDekuBasementGS;
extern Option LogicDCStaircase;
extern Option LogicDCJump;
extern Option LogicDCSlingshotSkip;
extern Option LogicDCScarecrowGS;
extern Option LogicJabuBossGSAdult;
extern Option LogicJabuScrubJumpDive;
extern Option LogicForestOutsideBackdoor;
extern Option LogicForestDoorFrame;
extern Option LogicForestOutdoorEastGS;
extern Option LogicFireBossDoorJump;
extern Option LogicFireStrength;
extern Option LogicFireScarecrow;
extern Option LogicFireFlameMaze;
extern Option LogicFireSongOfTime;
extern Option LogicWaterTempleTorchLongshot;
extern Option LogicWaterTempleUpperBoost;
extern Option LogicWaterCentralBow;
extern Option LogicWaterCentralGSFW;
extern Option LogicWaterCrackedWallNothing;
extern Option LogicWaterCrackedWallHovers;
extern Option LogicWaterBossKeyRegion;
extern Option LogicWaterBKJumpDive;
extern Option LogicWaterNorthBasementLedgeJump;
extern Option LogicWaterDragonJumpDive;
extern Option LogicWaterDragonAdult;
extern Option LogicWaterRiverGS;
extern Option LogicWaterFallingPlatformGS;
extern Option LogicSpiritLowerAdultSwitch;
extern Option LogicSpiritChildBombchu;
extern Option LogicSpiritWall;
extern Option LogicSpiritLobbyGS;
extern Option LogicSpiritMapChest;
extern Option LogicSpiritSunChest;
extern Option LogicShadowFireArrowEntry;
extern Option LogicShadowUmbrella;
extern Option LogicShadowFreestandingKey;
extern Option LogicShadowStatue;
extern Option LogicShadowBongo;
extern Option LogicChildDeadhand;
extern Option LogicGtgWithoutHookshot;
extern Option LogicGtgFakeWall;
extern Option LogicLensSpirit;
extern Option LogicLensShadow;
extern Option LogicLensShadowBack;
extern Option LogicLensBotw;
extern Option LogicLensGtg;
extern Option LogicLensCastle;
extern Option LogicLensJabuMQ;
extern Option LogicLensSpiritMQ;
extern Option LogicLensShadowMQ;
extern Option LogicLensShadowMQBack;
extern Option LogicLensBotwMQ;
extern Option LogicLensGtgMQ;
extern Option LogicLensCastleMQ;
extern Option LogicSpiritTrialHookshot;
extern Option LogicFlamingChests;

// Glitch Settings
extern Option ToggleAllGlitches;
extern Option GlitchRestrictedItems;
extern Option GlitchSuperStab;
extern Option GlitchISG;
extern Option GlitchHover;
extern Option GlitchBombOI;
extern Option GlitchHoverBoost;
extern Option GlitchSuperSlide;
extern Option GlitchMegaflip;
extern Option GlitchASlide;
extern Option GlitchHammerSlide;
extern Option GlitchLedgeCancel;
extern Option GlitchActionSwap;
extern Option GlitchQPA;
extern Option GlitchHookshotClip;
extern Option GlitchHookshotJump_Bonk;
extern Option GlitchHookshotJump_Boots;
extern Option GlitchCutsceneDive;
extern Option GlitchNaviDive_Stick;
extern Option GlitchTripleSlashClip;
extern Option GlitchLedgeClip;
extern Option GlitchSeamWalk;
// Misc Glitch Settings
extern Option GlitchWWTEscape;
extern Option GlitchGVTentAsChild;
extern Option GlitchGFGuardSneak;
extern Option GlitchItemlessWasteland;
extern Option GlitchOccamsStatue;
extern Option GlitchZDOoBJumpSlash;
extern Option GlitchJabuStickRecoil;
extern Option GlitchJabuAdult;
extern Option GlitchBlueFireWall;
extern Option GlitchClassicHalfie;
extern Option GlitchModernHalfie;
extern Option GlitchJabuSwitch;
extern Option GlitchForestBKSkip;
extern Option GlitchFireGrunzClip;

// Multiplayer Settings
extern Option MP_Enabled;
extern Option MP_SharedProgress;
extern Option MP_SyncId;
extern Option MP_SharedHealth;
extern Option MP_SharedRupees;
extern Option MP_SharedAmmo;

// Ingame Default Settings
extern Option ZTargeting;
extern Option CameraControl;
extern Option MotionControl;
extern Option TogglePlayMusic;
extern Option TogglePlaySFX;
extern Option NaviNotifications;
extern Option IgnoreMaskReaction;
extern Option FreeCamControl;

// Cosmetic Settings
extern Option CustomTunicColors;
extern Option ChildTunicColor;
extern Option KokiriTunicColor;
extern Option GoronTunicColor;
extern Option ZoraTunicColor;
extern Option SilverGauntletsColor;
extern Option GoldGauntletsColor;
extern Option CustomNaviColors;
extern Option IdleNaviInnerColor;
extern Option NPCNaviInnerColor;
extern Option EnemyNaviInnerColor;
extern Option PropNaviInnerColor;
extern Option IdleNaviOuterColor;
extern Option NPCNaviOuterColor;
extern Option EnemyNaviOuterColor;
extern Option PropNaviOuterColor;
extern Option CustomTrailEffects;
extern Option SwordTrailInnerColor;
extern Option SwordTrailOuterColor;
extern Option SwordTrailDuration;
extern Option BoomerangTrailColor;
extern Option BoomerangTrailDuration;
extern Option ChosenSimpleMode;
extern Option BombchuTrailInnerColor;
extern Option BombchuTrailOuterColor;
extern Option BombchuTrailDuration;
extern std::string finalChildTunicColor;
extern std::string finalKokiriTunicColor;
extern std::string finalGoronTunicColor;
extern std::string finalZoraTunicColor;
extern std::string finalSilverGauntletsColor;
extern std::string finalGoldGauntletsColor;
extern std::string finalIdleNaviInnerColor;
extern std::string finalNPCNaviInnerColor;
extern std::string finalEnemyNaviInnerColor;
extern std::string finalPropNaviInnerColor;
extern std::string finalIdleNaviOuterColor;
extern std::string finalNPCNaviOuterColor;
extern std::string finalEnemyNaviOuterColor;
extern std::string finalPropNaviOuterColor;
extern std::string finalSwordTrailInnerColor;
extern std::string finalSwordTrailOuterColor;
extern Color_RGBA8 finalBoomerangColor;
extern u8 boomerangTrailColorMode;
extern std::string finalChuTrailInnerColor;
extern std::string finalChuTrailOuterColor;

extern Option ColoredKeys;
extern Option ColoredBossKeys;
extern Option MirrorWorld;
extern Option BetaSoldOut;
extern Option SoullessEnemiesLook;

extern Option ShuffleMusic;
extern Option ShuffleBGM;
extern Option ShuffleMelodies;
extern Option CustomMusic;
extern Option CustomMusicOnly;
extern Option ShuffleSFX;
extern Option ShuffleSFXFootsteps;
extern Option ShuffleSFXLinkVoice;
extern Option ShuffleSFXCategorically;

extern u32 LinksPocketRewardBitMask;
extern std::array<u32, 9> rDungeonRewardOverrides;

extern u8 PlayOption;
extern u8 Region;

extern Menu loadCustomPreset;
extern Menu deleteCustomPreset;

extern std::vector<std::vector<Option*>> excludeLocationsOptionsVector;
extern std::vector<Menu*> excludeLocationsMenus;
extern std::vector<Option*> startingItemsOptions;
extern std::vector<Option*> startingSongsOptions;
extern std::vector<Option*> startingEquipmentOptions;
extern std::vector<Option*> startingStonesMedallionsOptions;
extern std::vector<Option*> startingEnemySoulsOptions;
extern std::vector<Option*> startingOcarinaButtonsOptions;
extern std::vector<Option*> startingOtherOptions;
extern std::vector<Option*> trickOptions;
extern std::vector<Option*> glitchCategories;
extern std::vector<Option*> miscGlitches;

extern std::vector<Menu*> startingInventoryOptions;
extern std::vector<Menu*> detailedLogicOptions;

extern std::vector<Menu*> mainMenu;

extern std::vector<std::pair<Option*, u8>> racingOverrides;
extern std::vector<std::pair<Option*, u8>> vanillaLogicOverrides;
} // namespace Settings
