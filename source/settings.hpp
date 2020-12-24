#pragma once

#include <3ds.h>
#include <array>
#include <cstdlib>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>
#include "../code/src/settings.h"

class Option {
public:
    static Option Bool(std::string name_, std::vector<std::string> options_, bool defaultOption_ = false) {
        return Option{false, std::move(name_), std::move(options_), static_cast<u8>(defaultOption_)};
    }

    static Option U8(std::string name_, std::vector<std::string> options_, u8 defaultOption_ = 0) {
        return Option{u8{0}, std::move(name_), std::move(options_), defaultOption_};
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

    std::string_view GetName() const {
        return name;
    }

    std::string_view GetSelectedOption() const {
        return options[selectedOption];
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

private:
    Option(u8 var_, std::string name_, std::vector<std::string> options_, u8 defaultOption_ = 0)
          : var(var_), name(std::move(name_)), options(std::move(options_)), selectedOption(defaultOption_) {
        SetVariable();
    }

    Option(bool var_, std::string name_, std::vector<std::string> options_, u8 defaultOption_ = 0)
          : var(var_), name(std::move(name_)),  options(std::move(options_)), selectedOption(defaultOption_) {
        SetVariable();
    }

  std::variant<bool, u8> var;
  std::string name;
  std::vector<std::string> options;
  u8 selectedOption;
};



class Menu {
  public:
    Menu(std::string name_, std::vector<Option *>* settingsList_)
        : name(std::move(name_)), settingsList(std::move(settingsList_)) {}

    std::string name;
    std::vector<Option *>* settingsList;
    int selectedSetting = 0;
};

namespace Settings {
  extern std::string seed;

  // U8 options
  extern Option Logic;
  extern Option OpenForest;
  extern Option OpenKakariko;
  extern Option Bridge;
  extern Option GerudoFortress;
  extern Option DamageMultiplier;
  extern Option ZorasFountain;
  extern Option StartingAge;
  extern Option Keysanity;
  extern Option BossKeysanity;
  extern Option GanonsBossKey;
  extern Option MapsAndCompasses;
  extern Option Skullsanity;
  extern Option Scrubsanity;
  extern Option ItemPoolValue;
  extern u8 LACSCondition;

  // Bool options
  extern Option BombchusInLogic;
  extern Option OpenDoorOfTime;
  extern Option ShuffleWeirdEgg;
  extern Option ShuffleGerudoToken;
  extern Option ShuffleKokiriSword;
  extern Option ShuffleMagicBeans;
  extern Option ShuffleOcarinas;

  extern bool HasNightStart;
  extern bool BombchuDrop;
  extern bool SkippedTrials;
  extern bool ShuffleDungeonEntrances;
  extern bool ShuffleOverworldEntrances;
  extern bool ShuffleInteriorEntrances;
  extern bool ShuffleSpecialIndoorEntrances;
  extern bool ShuffleSongs;
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
  extern bool GerudoTrainingGroundsDungeonMode;
  extern bool GanonsCastleDungeonMode;

  //Logic Settings
  extern bool LogicMidoBackflip;
  extern bool LogicLostWoodsBridge;
  extern bool LogicGrottosWithoutAgony;
  extern bool LogicBiggoronBolero;
  extern bool LogicGerudoKitchen;
  extern bool LogicWaterHookshotEntry;
  extern bool LogicLensWasteland;
  extern bool LogicReverseWasteland;
  extern bool LogicVisibleCollision;
  extern bool LogicManOnRoof;
  extern bool LogicKakarikoTowerGS;
  extern bool LogicDMTBombable;
  extern bool LogicLinkGoronDins;
  extern bool LogicGoronCityLeftMost;
  extern bool LogicGoronCityPot;
  extern bool LogicGoronCityPotWithStrength;
  extern bool LogicChildRollingWithStrength;
  extern bool LogicCraterUpperToLower;
  extern bool LogicCraterBeanPoHWithHovers;
  extern bool LogicFewerTunicRequirements;
  extern bool LogicZoraWithHovers;
  extern bool LogicZoraWithCucco;
  extern bool LogicDekuB1Skip;
  extern bool LogicDekuB1WebsWithBow;
  extern bool LogicDCStaircase;
  extern bool LogicDCJump;
  extern bool LogicDCSlingshotSkip;
  extern bool LogicJabuBossGSAdult;
  extern bool LogicJabuScrubJumpDive;
  extern bool LogicForestVines;
  extern bool LogicForestScarecrow;
  extern bool LogicForestOutsideBackdoor;
  extern bool LogicLabDiving;
  extern bool LogicZoraRiverLower;
  extern bool LogicZoraRiverUpper;
  extern bool LogicGraveyardPoH;
  extern bool LogicChildDampeRacePoH;
  extern bool LogicFireBossDoorJump;
  extern bool LogicFireStrength;
  extern bool LogicFireScarecrow;
  extern bool LogicFireFlameMaze;
  extern bool LogicWaterTempleTorchLongshot;
  extern bool LogicWaterCentralBow;
  extern bool LogicWaterCrackedWallNothing;
  extern bool LogicWaterCrackedWallHovers;
  extern bool LogicWaterBossKeyRegion;
  extern bool LogicWaterDragonBombchu;
  extern bool LogicWaterBKJumpDive;
  extern bool LogicWaterBKChest;
  extern bool LogicWaterNorthBasementLedgeJump;
  extern bool LogicWaterDragonBombchu;
  extern bool LogicWaterDragonJumpDive;
  extern bool LogicWaterNorthBasementLedgeJump;
  extern bool LogicWaterBKChest;
  extern bool LogicWaterDragonJumpDive;
  extern bool LogicSpiritLowerAdultSwitch;
  extern bool LogicSpiritChildBombchu;
  extern bool LogicSpiritWall;
  extern bool LogicSpiritLobbyGS;
  extern bool LogicSpiritMapChest;
  extern bool LogicSpiritSunChest;
  extern bool LogicShadowFireArrowEntry;
  extern bool LogicShadowUmbrella;
  extern bool LogicShadowFreestandingKey;
  extern bool LogicShadowStatue;
  extern bool LogicBotwCageGS;
  extern bool LogicChildDeadhand;
  extern bool LogicGtgWithoutHookshot;
  extern bool LogicGtgFakeWall;
  extern bool LogicLensSpirit;
  extern bool LogicLensShadow;
  extern bool LogicLensShadowBack;
  extern bool LogicLensBotw;
  extern bool LogicLensGtg;
  extern bool LogicLensCastle;
  extern bool LogicSpiritTrialHookshot;
  extern bool LogicLostWoodsGSBean;
  extern bool LogicLabWallGS;
  extern bool LogicColossusGS;
  extern bool LogicDMTSoilGS;
  extern bool LogicDekuBasementGS;
  extern bool LogicDCScarecrowGS;
  extern bool LogicForestOutdoorEastGS;
  extern bool LogicFireSongOfTime;
  extern bool LogicWaterRiverGS;
  extern bool LogicWaterFallingPlatformGS;

  extern u32 LinksPocketRewardBitMask;
  extern std::array<u32, 9> rDungeonRewardOverrides;

  extern std::vector<Option *> excludeLocationsOptions;

  extern void UpdateSettings();
  extern SettingsContext FillContext();

  extern std::vector<Option *> Options;
  extern std::vector<Menu *> mainMenu;
}
