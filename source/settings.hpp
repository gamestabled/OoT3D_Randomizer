#pragma once

#include <3ds.h>

#include <array>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>

#include "../code/src/settings.h"
#include "category.hpp"
#include "cosmetics.hpp"
#include "debug.hpp"
#include "menu.hpp"
#include "pool_functions.hpp"

class Option {
public:
    static Option Bool(std::string name_, std::vector<std::string> options_, std::vector<std::string_view> optionDescriptions_, OptionCategory category_ = OptionCategory::Setting) {
        return Option{false, std::move(name_), std::move(options_), std::move(optionDescriptions_), category_};
    }

    static Option U8(std::string name_, std::vector<std::string> options_, std::vector<std::string_view> optionDescriptions_, OptionCategory category_  = OptionCategory::Setting) {
        return Option{u8{0}, std::move(name_), std::move(options_), std::move(optionDescriptions_), category_};
    }

    template <typename T>
    T Value() const {
        return std::get<T>(var);
    }

    template <typename T>
    bool Is(T other) const {
        static_assert(std::is_integral_v<T> || std::is_enum_v<T>,
                      "T must be an integral type or an enum.");

        if constexpr ((std::is_integral_v<T> && !std::is_same_v<bool, T>) || std::is_enum_v<T>) {
            return Value<u8>() == static_cast<u8>(other);
        } else {
            return Value<bool>() == static_cast<bool>(other);
        }
    }

    template <typename T>
    bool IsNot(T other) const {
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
    }

    size_t GetOptionCount() const {
        return options.size();
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

    std::string_view GetSelectedOptionDescription() const {
      //bounds checking
      if (selectedOption >= optionDescriptions.size()) {
        return optionDescriptions[optionDescriptions.size()-1];
      }
      return optionDescriptions[selectedOption];
    }

    u8 GetSelectedOptionIndex() const {
      return selectedOption;
    }

    void NextOptionIndex() {
        ++selectedOption;
    }

    void PrevOptionIndex() {
        --selectedOption;
    }

    void SanitizeSelectedOptionIndex() {
        if (selectedOption == options.size()) {
            selectedOption = 0;
        } else if (selectedOption == 0xFF) {
            selectedOption = static_cast<u8>(options.size() - 1);
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

      //Special case for custom cosmetic settings
      if (options.size() > CUSTOM_COLOR) {
        if (newSetting.compare(0, 8, CUSTOM_COLOR_PREFIX) == 0 && options[CUSTOM_COLOR].compare(0, 8, CUSTOM_COLOR_PREFIX) == 0) {
          SetSelectedIndex(CUSTOM_COLOR);
          SetSelectedOptionText(newSetting);
          return;
        }
      }

      for (size_t i = 0; i < options.size(); i++) {
        std::string settingName = options[i];
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
    Option(u8 var_, std::string name_, std::vector<std::string> options_, std::vector<std::string_view> optionDescriptions_, OptionCategory category_)
          : var(var_), name(std::move(name_)), options(std::move(options_)), optionDescriptions(std::move(optionDescriptions_)), category(category_) {
        SetVariable();
    }

    Option(bool var_, std::string name_, std::vector<std::string> options_, std::vector<std::string_view> optionDescriptions_, OptionCategory category_)
          : var(var_), name(std::move(name_)),  options(std::move(options_)), optionDescriptions(std::move(optionDescriptions_)), category(category_) {
        SetVariable();
    }

  std::variant<bool, u8> var;
  std::string name;
  std::vector<std::string> options;
  std::vector<std::string_view> optionDescriptions;
  u8 selectedOption = 0;
  bool locked = false;
  bool hidden = false;
  OptionCategory category;
};

enum class MenuType {
  MainMenu,
  SubMenu,
  Action,
};

class Menu {
  public:

    static Menu SubMenu(std::string name_, std::vector<Option *>* settingsList_) {
      return Menu{std::move(name_), MenuType::SubMenu, std::move(settingsList_), OPTION_SUB_MENU};
    }

    static Menu SubMenu(std::string name_, std::vector<Menu *>* itemsList_) {
      return Menu{std::move(name_), MenuType::SubMenu, std::move(itemsList_), SUB_MENU};
    }

    static Menu Action(std::string name_, u8 mode_) {
      return Menu{std::move(name_), MenuType::Action, std::move(mode_)};
    }

    Menu(std::string name_, MenuType type_, std::vector<Option *>* settingsList_, u8 mode_)
        : name(std::move(name_)), type(type_), settingsList(std::move(settingsList_)), mode(mode_) {}

    Menu(std::string name_, MenuType type_, std::vector<Menu *>* itemsList_, u8 mode_)
        : name(std::move(name_)), type(type_), itemsList(std::move(itemsList_)), mode(mode_) {}

    Menu(std::string name_, MenuType type_, u8 mode_)
        : name(std::move(name_)), type(type_), mode(mode_) {}

    std::string name;
    MenuType type;
    std::vector<Option *>* settingsList;
    std::vector<Menu *>* itemsList;
    u8 mode;
    u16 menuIdx = 0;
    int selectedSetting = 0;
};

namespace Settings {
  void UpdateSettings();
  SettingsContext FillContext();
  void SetDefaultSettings();
  void RandomizeAllSettings(const bool selectOptions = false);
  void ForceChange(u32 kDown, Option* currentSetting);

  extern std::string seed;
  extern std::string version;
  extern std::array<u8, 5> hashIconIndexes;

  extern Option OpenForest;
  extern Option OpenKakariko;
  extern Option OpenDoorOfTime;
  extern Option ZorasFountain;
  extern Option GerudoFortress;
  extern Option Bridge;
  extern Option BridgeStoneCount;
  extern Option BridgeMedallionCount;
  extern Option BridgeRewardCount;
  extern Option BridgeDungeonCount;
  extern Option BridgeTokenCount;
  extern Option RandomGanonsTrials;
  extern Option GanonsTrialsCount;

  extern Option StartingAge;
  extern u8 ResolvedStartingAge;
  extern Option ShuffleEntrances;
  extern Option ShuffleDungeonEntrances;
  extern Option ShuffleOverworldEntrances;
  extern Option BombchusInLogic;
  extern Option AmmoDrops;
  extern Option HeartDropRefill;
  extern Option RandomMQDungeons;
  extern Option MQDungeonCount;

  extern Option ShuffleRewards;
  extern Option LinksPocketItem;
  extern Option ShuffleSongs;
  extern Option Shopsanity;
  extern Option Tokensanity;
  extern Option Scrubsanity;
  extern Option ShuffleCows;
  extern Option ShuffleKokiriSword;
  extern Option ShuffleOcarinas;
  extern Option ShuffleWeirdEgg;
  extern Option ShuffleGerudoToken;
  extern Option ShuffleMagicBeans;
  extern Option ShuffleMerchants;

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

  extern Option SkipChildStealth;
  extern Option SkipTowerEscape;
  extern Option SkipEponaRace;
  extern Option SkipMinigamePhases;
  extern Option FreeScarecrow;
  extern Option FourPoesCutscene;
  extern Option TempleOfTimeIntro;
  extern Option BigPoeTargetCount;
  extern Option NumRequiredCuccos;
  extern Option KingZoraSpeed;

  extern Option GossipStoneHints;
  extern Option ClearerHints;
  extern Option HintDistribution;
  extern Option DamageMultiplier;
  extern Option StartingTime;
  extern Option ChestAnimations;
  extern Option ChestSize;
  extern Option GenerateSpoilerLog;
  extern Option IngameSpoilers;
  extern Option MenuOpeningButton;
  extern Option RandomTrapDmg;
  extern bool HasNightStart;
  extern Option CompleteMaskQuest;

  extern Option StickAsAdult;
  extern Option BoomerangAsAdult;
  extern Option HammerAsChild;

  extern Option ItemPoolValue;
  extern Option IceTrapValue;
  extern Option RemoveDoubleDefense;

  extern bool ShuffleInteriorEntrances;
  extern bool ShuffleSpecialIndoorEntrances;

  //Starting Inventory
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
  extern Option StartingRutoBottle;
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
  extern Option StartingHealth;

  //Logic Settings
  extern Option Logic;
  extern Option NightGSExpectSuns;

  //Trick Settings
  extern Option ToggleAllTricks;
  extern Option LogicGrottosWithoutAgony;
  extern Option LogicVisibleCollision;
  extern Option LogicFewerTunicRequirements;
  extern Option LogicLostWoodsGSBean;
  extern Option LogicLabDiving;
  extern Option LogicLabWallGS;
  extern Option LogicGraveyardPoH;
  extern Option LogicChildDampeRacePoH;
  extern Option LogicGerudoKitchen;
  extern Option LogicLensWasteland;
  extern Option LogicReverseWasteland;
  extern Option LogicColossusGS;
  extern Option LogicOutsideGanonsGS;
  extern Option LogicManOnRoof;
  extern Option LogicDMTBombable;
  extern Option LogicDMTSoilGS;
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

  extern Option CustomTunicColors;
  extern Option ChildTunicColor;
  extern Option KokiriTunicColor;
  extern Option GoronTunicColor;
  extern Option ZoraTunicColor;
  extern Option SilverGauntletsColor;
  extern Option GoldGauntletsColor;
  extern std::string finalChildTunicColor;
  extern std::string finalKokiriTunicColor;
  extern std::string finalGoronTunicColor;
  extern std::string finalZoraTunicColor;
  extern std::string finalSilverGauntletsColor;
  extern std::string finalGoldGauntletsColor;

  extern Option ColoredKeys;
  extern Option ColoredBossKeys;
  extern Option MirrorWorld;

  extern u32 LinksPocketRewardBitMask;
  extern std::array<u32, 9> rDungeonRewardOverrides;

  extern u8 PlayOption;

  extern std::vector<Option *> excludeLocationsOptions;
  extern std::vector<Option *> startingInventoryOptions;
  extern std::vector<Option *> trickOptions;

  extern std::vector<Menu *> detailedLogicOptions;

  extern std::vector<Menu *> mainMenu;
}
