#pragma once

#include <3ds.h>
#include <array>
#include <cstdlib>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>
#include "../code/src/settings.h"
#include "menu.hpp"

class Option {
public:
    static Option Bool(std::string name_, std::vector<std::string> options_, std::vector<std::string_view> optionDescriptions_) {
        return Option{false, std::move(name_), std::move(options_), std::move(optionDescriptions_)};
    }

    static Option U8(std::string name_, std::vector<std::string> options_, std::vector<std::string_view> optionDescriptions_) {
        return Option{u8{0}, std::move(name_), std::move(options_), std::move(optionDescriptions_)};
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
      options = o;
    }

    std::string_view GetName() const {
        return name;
    }

    std::string_view GetSelectedOption() const {
        return options[selectedOption];
    }

    std::string_view GetSelectedOptionDescription() const {
      return optionDescriptions[selectedOption];
    }

    u8 GetSelectedOptionIndex() {
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

    void SetSelectedIndex(u8 idx) {
      selectedOption = idx;
      if (selectedOption >= options.size()) {
        printf("\x1b[30;0HERROR: Incomptaible selection for %s\n", name.c_str());
        selectedOption = 0;
      }

      SetVariable();
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

private:
    Option(u8 var_, std::string name_, std::vector<std::string> options_, std::vector<std::string_view> optionDescriptions_)
          : var(var_), name(std::move(name_)), options(std::move(options_)), optionDescriptions(std::move(optionDescriptions_)) {
        SetVariable();
    }

    Option(bool var_, std::string name_, std::vector<std::string> options_, std::vector<std::string_view> optionDescriptions_)
          : var(var_), name(std::move(name_)),  options(std::move(options_)), optionDescriptions(std::move(optionDescriptions_)) {
        SetVariable();
    }

  std::variant<bool, u8> var;
  std::string name;
  std::vector<std::string> options;
  std::vector<std::string_view> optionDescriptions;
  u8 selectedOption = 0;
  bool locked = false;
  bool hidden = false;
};

enum class MenuItemType {
  SubMenu,
  Action,
};

class MenuItem {
  public:

    static MenuItem SubMenu(std::string name_, std::vector<Option *>* settingsList_) {
      return MenuItem{std::move(name_), MenuItemType::SubMenu, std::move(settingsList_), SUB_MENU};
    }

    static MenuItem Action(std::string name_, u8 mode_) {
      return MenuItem{std::move(name_), MenuItemType::Action, {}, std::move(mode_)};
    }

    MenuItem(std::string name_, MenuItemType type_, std::vector<Option *>* settingsList_, u8 mode_)
        : name(std::move(name_)), type(type_), settingsList(std::move(settingsList_)), mode(mode_) {}

    std::string name;
    MenuItemType type;
    std::vector<Option *>* settingsList;
    u8 mode;
    int selectedSetting = 0;
};

namespace Settings {
  extern std::string seed;

  extern Option Logic;
  extern Option OpenForest;
  extern Option OpenKakariko;
  extern Option OpenDoorOfTime;
  extern Option ZorasFountain;
  extern Option GerudoFortress;
  extern Option Bridge;
  extern Option TokenCount;

  extern Option StartingAge;
  extern Option BombchusInLogic;
  extern Option BombchuDrops;
  extern Option RandomMQDungeons;
  extern Option MirrorWorld;

  extern Option ShuffleSongs;
  extern Option Tokensanity;
  extern Option Scrubsanity;
  extern Option ShuffleCows;
  extern Option ShuffleKokiriSword;
  extern Option ShuffleOcarinas;
  extern Option ShuffleWeirdEgg;
  extern Option ShuffleGerudoToken;
  extern Option ShuffleMagicBeans;

  extern Option MapsAndCompasses;
  extern Option Keysanity;
  extern Option GerudoKeys;
  extern Option BossKeysanity;
  extern Option GanonsBossKey;

  extern Option SkipChildStealth;
  extern Option FourPoesCutscene;
  extern Option TempleOfTimeIntro;
  extern Option BigPoeTargetCount;
  extern Option NumRequiredCuccos;

  extern Option DamageMultiplier;
  extern Option StartingTime;
  extern Option GenerateSpoilerLog;

  extern Option StickAsAdult;
  extern Option BoomerangAsAdult;
  extern Option HammerAsChild;

  extern Option ItemPoolValue;
  extern Option IceTrapValue;

  extern u8 LACSCondition;

  extern bool HasNightStart;
  extern bool BombchuDrop;
  extern bool SkippedTrials;
  extern bool ShuffleDungeonEntrances;
  extern bool ShuffleOverworldEntrances;
  extern bool ShuffleInteriorEntrances;
  extern bool ShuffleSpecialIndoorEntrances;
  extern bool Shopsanity;
  extern bool DekuTreeDungeonMode;
  extern bool DodongosCavernDungeonMode;
  extern bool JabuJabusBellyDungeonMode;
  extern bool ForestTempleDungeonMode;
  extern bool FireTempleDungeonMode;
  extern bool WaterTempleDungeonMode;
  extern bool SpiritTempleDungeonMode;
  extern bool ShadowTempleDungeonMode;
  extern bool BottomOfTheWellDungeonMode;
  extern bool IceCavernDungeonMode;
  extern bool GerudoTrainingGroundsDungeonMode;
  extern bool GanonsCastleDungeonMode;

  //Logic Settings
  extern Option ToggleAllDetailedLogic;
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
  extern Option LogicSpiritTrialHookshot;

  extern u32 LinksPocketRewardBitMask;
  extern std::array<u32, 9> rDungeonRewardOverrides;

  extern u8 PlayOption;

  extern std::vector<Option *> excludeLocationsOptions;
  extern std::vector<Option *> detailedLogicOptions;

  extern void UpdateSettings();
  extern SettingsContext FillContext();
  extern void FillSettings(SettingsContext ctx);
  extern void SetDefaultSettings();
  extern void ForceChange(u32 kDown, Option* currentSetting);

  extern std::vector<MenuItem *> mainMenu;
}
