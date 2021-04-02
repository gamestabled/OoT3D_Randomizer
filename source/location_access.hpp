#pragma once
#include <functional>
#include <tuple>
#include <string>
#include <vector>
#include "item_location.hpp"
#include "item_pool.hpp"
#include "logic.hpp"
#include "settings.hpp"
#include "spoiler_log.hpp"

class Exit;

class EventPairing {
public:
    using ConditionFn = bool (*)();

    explicit EventPairing(bool* event_, ConditionFn conditions_met_)
        : event(event_),
          conditions_met(conditions_met_) {}

    bool ConditionsMet() const {
        return conditions_met();
    }

    void EventOccurred() {
        *event = true;
    }

    bool GetEvent() const {
        return *event;
    }

private:
    bool* event;
    ConditionFn conditions_met;
};

//this class is meant to hold an item location with a boolean function to determine its accessibility from a specific area
class ItemLocationPairing {
public:
    using ConditionFn = bool (*)();

    explicit ItemLocationPairing(ItemLocation* location_, ConditionFn conditions_met_)
         : location(location_),
           conditions_met(conditions_met_) {}

    bool ConditionsMet() const {
        return conditions_met();
    }

    ItemLocation* GetLocation() {
        return location;
    }

    const ItemLocation* GetLocation() const {
        return location;
    }

    bool IsLocationUsed() const {
        return location->IsUsed();
    }

private:
    ItemLocation* location;
    ConditionFn conditions_met;
};

class ExitPairing {
public:
    using ConditionFn = bool (*)();

    enum class Time {
      Day,
      Night,
      Both,
    };

    constexpr ExitPairing(Exit* exit_, ConditionFn conditions_met_, Time time_of_day_ = Time::Both)
        : exit(exit_), conditions_met(conditions_met_), time_of_day(time_of_day_) {}

    constexpr bool IsBoth() const {
        return time_of_day == ExitPairing::Time::Both;
    }

    constexpr bool IsDay() const {
        return time_of_day == ExitPairing::Time::Day;
    }

    constexpr bool IsNight() const {
        return time_of_day == ExitPairing::Time::Night;
    }

    constexpr Time TimeOfDay() const {
        return time_of_day;
    }

    constexpr bool ConditionsMet() const {
        return conditions_met();
    }

    constexpr Exit* GetExit() {
        return exit;
    }

    constexpr const Exit* GetExit() const {
        return exit;
    }

    static constexpr ExitPairing Both(Exit* exit, ConditionFn condition) {
        return ExitPairing{exit, condition, Time::Both};
    }

    static constexpr ExitPairing Day(Exit* exit, ConditionFn condition) {
        return ExitPairing{exit, condition, Time::Day};
    }

    static constexpr ExitPairing Night(Exit* exit, ConditionFn condition) {
        return ExitPairing{exit, condition, Time::Night};
    }

private:
    Exit* exit;
    ConditionFn conditions_met;
    Time time_of_day;
};

class Exit {
public:
    Exit(std::string regionName_, std::string scene_, std::string hint_, bool timePass_, std::vector<EventPairing> events_, std::vector<ItemLocationPairing> locations_, std::vector<ExitPairing> exits_)
        : regionName(std::move(regionName_)),
          scene(std::move(scene_)),
          hint(std::move(hint_)),
          timePass(timePass_),
          events(std::move(events_)),
          locations(std::move(locations_)),
          exits(std::move(exits_)) {}

    std::string regionName;
    std::string scene;
    std::string hint;
    bool        timePass;
    std::vector<EventPairing> events;
    std::vector<ItemLocationPairing> locations;
    std::vector<ExitPairing> exits;

    bool dayChild = false;
    bool nightChild = false;
    bool dayAdult = false;
    bool nightAdult = false;
    bool addedToPool = false;

    void UpdateEvents() {

      if (timePass) {
        if (Logic::Age == AGE_CHILD) {
          dayChild = true;
          nightChild = true;
        } else {
          dayAdult = true;
          nightAdult = true;
        }
      }

      for (size_t i = 0; i < events.size(); i++) {
        EventPairing& eventPair = events[i];

        if (eventPair.ConditionsMet()) {
          eventPair.EventOccurred();
        }
      }
    }

    bool Child() const {
      return dayChild || nightChild;
    }

    bool Adult() const {
      return dayAdult || nightAdult;
    }

    bool BothAges() const {
      return Child() && Adult();
    }

    bool HasAccess() const {
      return Child() || Adult();
    }

    bool AllAccess() const {
      return dayChild && nightChild && dayAdult && nightAdult;
    }

    bool CanPlantBean() const {
      return (Logic::MagicBean || Logic::MagicBeanPack) && BothAges();
    }

    bool AllAccountedFor() const {
      for (const EventPairing& event : events) {
        if (!event.ConditionsMet() || !event.GetEvent()) {
          return false;
        }
      }

      for (const ItemLocationPairing loc : locations) {
        if (!loc.ConditionsMet() || !loc.GetLocation()->IsAddedToPool()) {
          return false;
        }
      }

      for (const ExitPairing& exit : exits) {
        if (!exit.ConditionsMet() || !exit.GetExit()->AllAccess()) {
          return false;
        }
      }

      return AllAccess();
    }

    void ResetVariables() {
      dayChild = false;
      nightChild = false;
      dayAdult = false;
      nightAdult = false;
      addedToPool = false;
    }
};

namespace Exits {

  //Starting Locations
  extern Exit Root;
  extern Exit RootExits;

  //Kokiri Forest
  extern Exit KF_Main;
  extern Exit KF_LinksHouse;
  extern Exit KF_MidosHouse;
  extern Exit KF_SariasHouse;
  extern Exit KF_HouseOfTwins;
  extern Exit KF_KnowItAllHouse;
  extern Exit KF_KokiriShop;
  extern Exit KF_OutsideDekuTree;
  extern Exit KF_StormsGrotto;

  //Lost Woods
  extern Exit LW_Main;
  extern Exit LW_BridgeFromForest;
  extern Exit LW_Bridge;
  extern Exit LW_ForestExit;
  extern Exit LW_BeyondMido;
  extern Exit LW_NearShortcutsGrotto;
  extern Exit LW_DekuTheater;
  extern Exit LW_ScrubsGrotto;

  //Sacred Forest Meadow
  extern Exit SFM_Entryway;
  extern Exit SFM_Main;
  extern Exit SFM_WolfosGrotto;
  extern Exit SFM_FairyGrotto;
  extern Exit SFM_StormsGrotto;

  //Hyrule Field
  extern Exit HF_Main;
  extern Exit HF_SoutheastGrotto;
  extern Exit HF_OpenGrotto;
  extern Exit HF_InsideFenceGrotto;
  extern Exit HF_CowGrotto;
  extern Exit HF_NearMarketGrotto;
  extern Exit HF_NearKakGrotto;
  extern Exit HF_FairyGrotto;
  extern Exit HF_NearKakGrotto;
  extern Exit HF_TektiteGrotto;

  //Lake Hylia
  extern Exit LH_Main;
  extern Exit LH_OwlFlight;
  extern Exit LH_Lab;
  extern Exit LH_FishingHole;
  extern Exit LH_Grotto;

  //Gerudo Valley
  extern Exit GV_Main;
  extern Exit GV_Stream;
  extern Exit GV_CrateLedge;
  extern Exit GV_OctorokGrotto;
  extern Exit GV_FortressSide;
  extern Exit GV_CarpenterTent;
  extern Exit GV_StormsGrotto;

  //Gerudo Fortress
  extern Exit GF_Main;
  extern Exit GF_OutsideGate;
  extern Exit GF_StormsGrotto;

  //Haunted Wasteland
  extern Exit HW_NearFortress;
  extern Exit HW_Main;
  extern Exit HW_NearColossus;

  //Desert Colossus
  extern Exit Colossus_Main;
  extern Exit Colossus_GreatFairyFountain;
  extern Exit Colossus_Grotto;

  //Market
  extern Exit MK_Entrance;
  extern Exit MK_Main;
  extern Exit MK_GuardHouse;
  extern Exit MK_Bazaar;
  extern Exit MK_MaskShop;
  extern Exit MK_ShootingGallery;
  extern Exit MK_BombchuBowling;
  extern Exit MK_TreasureChestGame;
  extern Exit MK_PotionShop;
  extern Exit MK_BombchuShop;
  extern Exit MK_DogLadyHouse;
  extern Exit MK_ManInGreenHouse;

  //Temple of Time
  extern Exit ToT_Entrance;
  extern Exit ToT_Main;
  extern Exit ToT_BeyondDoorOfTime;

  //Hyrule Castle
  extern Exit CastleGrounds;
  extern Exit HC_Grounds;
  extern Exit HC_Garden;
  extern Exit HC_GreatFairyFountain;
  extern Exit HC_StormsGrotto;

  //Outside Ganon's Castle
  extern Exit OGC_Grounds;
  extern Exit OGC_GreatFairyFountain;

  //Kakariko Village
  extern Exit Kak_Main;
  extern Exit Kak_CarpenterBossHouse;
  extern Exit Kak_HouseOfSkulltula;
  extern Exit Kak_ImpasHouse;
  extern Exit Kak_ImpasLedge;
  extern Exit Kak_ImpasHouseBack;
  extern Exit Kak_ImpasHouseNearCow;
  extern Exit Kak_Windmill;
  extern Exit Kak_Bazaar;
  extern Exit Kak_ShootingGallery;
  extern Exit Kak_PotionShopFront;
  extern Exit Kak_PotionShopBack;
  extern Exit Kak_Rooftop;
  extern Exit Kak_BehindGate;
  extern Exit Kak_Backyard;
  extern Exit Kak_OddMedicineBuilding;
  extern Exit Kak_RedeadGrotto;
  extern Exit Kak_OpenGrotto;

  //Graveyard
  extern Exit GY_Main;
  extern Exit GY_DampesGrave;
  extern Exit GY_DampesHouse;
  extern Exit GY_ShieldGrave;
  extern Exit GY_ComposersGrave;
  extern Exit GY_HeartPieceGrave;
  extern Exit GY_WarpPadRegion;

  //Death Mountain
  extern Exit DMT_Main;
  extern Exit DMT_Summit;
  extern Exit DMT_OwlFlight;
  extern Exit DMT_GreatFairyFountain;
  extern Exit DMT_CowGrotto;
  extern Exit DMT_StormsGrotto;

  //Goron City
  extern Exit GC_Main;
  extern Exit GC_WoodsWarp;
  extern Exit GC_DaruniasChamber;
  extern Exit GC_Shop;
  extern Exit GC_Grotto;

  //Death Mountain Crater
  extern Exit DMC_UpperLocal;
  extern Exit DMC_CentralLocal;
  extern Exit DMC_LowerLocal;
  extern Exit DMC_LowerNearby;
  extern Exit DMC_UpperNearby;
  extern Exit DMC_CentralNearby;
  extern Exit DMC_LadderAreaNearby;
  extern Exit DMC_UpperGrotto;
  extern Exit DMC_HammerGrotto;
  extern Exit DMC_GreatFairyFountain;

  //Zoras River
  extern Exit ZR_Front;
  extern Exit ZR_Main;
  extern Exit ZR_BehindWaterfall;
  extern Exit ZR_OpenGrotto;
  extern Exit ZR_FairyGrotto;
  extern Exit ZR_StormsGrotto;

  //Zoras Domain
  extern Exit ZD_Main;
  extern Exit ZD_BehindKingZora;
  extern Exit ZD_Shop;
  extern Exit ZD_StormsGrotto;

  //Zoras Fountain
  extern Exit ZF_Main;
  extern Exit ZF_GreatFairyFountain;

  //Lon Lon Ranch
  extern Exit LLR_Main;
  extern Exit LLR_TalonsHouse;
  extern Exit LLR_Stables;
  extern Exit LLR_Tower;
  extern Exit LLR_Grotto;

  //Deku Tree
  extern Exit DekuTree_Lobby;
  extern Exit DekuTree_SlingshotRoom;
  extern Exit DekuTree_BossRoom;
  //Deku Tree MQ
  extern Exit DekuTree_MQ_Lobby;
  extern Exit DekuTree_MQ_CompassRoom;
  extern Exit DekuTree_MQ_BasementWaterRoom;
  extern Exit DekuTree_MQ_BasementBackRoom;
  extern Exit DekuTree_MQ_BasementLedge;

  //Dodongos Cavern
  extern Exit DodongosCavern_Entryway;
  extern Exit DodongosCavern_Beginning;
  extern Exit DodongosCavern_Lobby;
  extern Exit DodongosCavern_Climb;
  extern Exit DodongosCavern_FarBridge;
  extern Exit DodongosCavern_BossArea;
  //Dodongos Cavern MQ
  extern Exit DodongosCavern_MQ_Beginning;
  extern Exit DodongosCavern_MQ_Lobby;
  extern Exit DodongosCavern_MQ_LowerRightSide;
  extern Exit DodongosCavern_MQ_BombBagArea;
  extern Exit DodongosCavern_MQ_BossArea;

  //Jabu Jabus Belly
  extern Exit JabuJabusBelly_Beginning;
  extern Exit JabuJabusBelly_Main;
  extern Exit JabuJabusBelly_Depths;
  extern Exit JabuJabusBelly_BossArea;
  //Jabu Jabus Belly MQ
  extern Exit JabuJabusBelly_MQ_Beginning;
  extern Exit JabuJabusBelly_MQ_Main;
  extern Exit JabuJabusBelly_MQ_Depths;
  extern Exit JabuJabusBelly_MQ_BossArea;

  //Forest Temple
  extern Exit ForestTemple_Lobby;
  extern Exit ForestTemple_NWOutdoors;
  extern Exit ForestTemple_NEOutdoors;
  extern Exit ForestTemple_OutdoorsHighBalconies;
  extern Exit ForestTemple_FallingRoom;
  extern Exit ForestTemple_BlockPushRoom;
  extern Exit ForestTemple_StraightenedHall;
  extern Exit ForestTemple_OutsideUpperLedge;
  extern Exit ForestTemple_BowRegion;
  extern Exit ForestTemple_BossRegion;
  //Forest Temple MQ
  extern Exit ForestTemple_MQ_Lobby;
  extern Exit ForestTemple_MQ_CentralArea;
  extern Exit ForestTemple_MQ_AfterBlockPuzzle;
  extern Exit ForestTemple_MQ_OutdoorLedge;
  extern Exit ForestTemple_MQ_NWOutdoors;
  extern Exit ForestTemple_MQ_NEOutdoors;
  extern Exit ForestTemple_MQ_OutdoorsTopLedges;
  extern Exit ForestTemple_MQ_NEOutdoorsLedge;
  extern Exit ForestTemple_MQ_BowRegion;
  extern Exit ForestTemple_MQ_FallingRoom;
  extern Exit ForestTemple_MQ_BossRegion;

  //Fire Temple
  extern Exit FireTemple_Entrance;
  extern Exit FireTemple_Lower;
  extern Exit FireTemple_BigLavaRoom;
  extern Exit FireTemple_Middle;
  extern Exit FireTemple_Upper;
  //Fire Temple MQ
  extern Exit FireTemple_MQ_Lower;
  extern Exit FireTemple_MQ_LowerLockedDoor;
  extern Exit FireTemple_MQ_BigLavaRoom;
  extern Exit FireTemple_MQ_LowerMaze;
  extern Exit FireTemple_MQ_UpperMaze;
  extern Exit FireTemple_MQ_Upper;
  extern Exit FireTemple_MQ_BossRoom;

  //Water Temple
  extern Exit WaterTemple_Lobby;
  extern Exit WaterTemple_HighestWaterLevel;
  extern Exit WaterTemple_Dive;
  extern Exit WaterTemple_FallingPlatformRoom;
  extern Exit WaterTemple_CrackedWall;
  extern Exit WaterTemple_NorthBasement;
  extern Exit WaterTemple_DragonStatue;
  extern Exit WaterTemple_MiddleWaterLevel;
  extern Exit WaterTemple_DarkLinkRegion;
  //Water Temple MQ
  extern Exit WaterTemple_MQ_Lobby;
  extern Exit WaterTemple_MQ_Dive;
  extern Exit WaterTemple_MQ_LoweredWaterLevels;
  extern Exit WaterTemple_MQ_DarkLinkRegion;
  extern Exit WaterTemple_MQ_BasementGatedAreas;

  //Spirit Temple
  extern Exit SpiritTemple_Lobby;
  extern Exit SpiritTemple_Child;
  extern Exit SpiritTemple_ChildClimb;
  extern Exit SpiritTemple_EarlyAdult;
  extern Exit SpiritTemple_CentralChamber;
  extern Exit SpiritTemple_OutdoorHands;
  extern Exit SpiritTemple_BeyondCentralLockedDoor;
  extern Exit SpiritTemple_BeyondFinalLockedDoor;

  //Shadow Temple
  extern Exit ShadowTemple_Entryway;
  extern Exit ShadowTemple_Beginning;
  extern Exit ShadowTemple_FirstBeamos;
  extern Exit ShadowTemple_HugePit;
  extern Exit ShadowTemple_WindTunnel;
  extern Exit ShadowTemple_BeyondBoat;

  //Bottom of the Well
  extern Exit BottomOfTheWell;
  extern Exit BottomOfTheWell_MainArea;

  //Ice Cavern
  extern Exit IceCavern_Beginning;
  extern Exit IceCavern_Main;

  //Gerudo Training Grounds
  extern Exit GerudoTrainingGrounds_Lobby;
  extern Exit GerudoTrainingGrounds_CentralMaze;
  extern Exit GerudoTrainingGrounds_CentralMazeRight;
  extern Exit GerudoTrainingGrounds_LavaRoom;
  extern Exit GerudoTrainingGrounds_HammerRoom;
  extern Exit GerudoTrainingGrounds_EyeStatueLower;
  extern Exit GerudoTrainingGrounds_EyeStatueUpper;
  extern Exit GerudoTrainingGrounds_HeavyBlockRoom;
  extern Exit GerudoTrainingGrounds_LikeLikeRoom;

  //Ganon's Castle
  extern Exit GanonsCastle_Lobby;
  extern Exit GanonsCastle_DekuScrubs;
  extern Exit GanonsCastle_ForestTrial;
  extern Exit GanonsCastle_FireTrial;
  extern Exit GanonsCastle_WaterTrial;
  extern Exit GanonsCastle_ShadowTrial;
  extern Exit GanonsCastle_SpiritTrial;
  extern Exit GanonsCastle_LightTrial;
  extern Exit GanonsCastle_Tower;

  extern void AccessReset();
  extern void ResetAllLocations();
} //namespace Exits
