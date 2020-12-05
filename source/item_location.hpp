#pragma once

#include <array>
#include <cstdio>
#include <functional>
#include <string>
#include <unistd.h>
#include <vector>

#include "../code/include/z3D/z3D.h"
#include "../code/src/item_override.h"
#include "item_list.hpp"

enum class ItemLocationType {
    Base,
    Chest,
    Collectable,
    GSToken,
    GrottoScrub,
    Delayed,
    TempleReward,
};

class ItemLocation {
public:
    explicit ItemLocation(u8 scene_, ItemLocationType type_, u8 flag_, std::string name_, std::vector<std::string> categories_)
        : scene(scene_), type(type_), flag(flag_), name(std::move(name_)), categories(std::move(categories_)) {}

    ItemOverride_Key Key() const {
        ItemOverride_Key key;
        key.all = 0;

        key.scene = scene;
        key.type = static_cast<u8>(type); //TODO make sure these match up
        key.flag = flag;
        return key;
    }

    void Use() {
      used = true;
    }

    bool IsUsed() const {
      return used;
    }

    bool IsAddedToPool() const {
      return addedToPool;
    }

    void AddToPool() {
      addedToPool = true;
    }

    std::string_view GetName() const {
      return name;
    }

    std::string_view GetPlacedItemName() const {
      return placedItem.GetName();
    }

    Item GetPlacedItem() const {
      return placedItem;
    }

    void SetPlacedItem(Item item) {
      placedItem = std::move(item);
    }

    void ApplyPlacedItemEffect() {
      placedItem.ApplyEffect();
    }

    static auto Base(u8 scene, u8 flag, std::string&& name, std::vector<std::string>&& categories) {
        return ItemLocation{scene, ItemLocationType::Base, flag, std::move(name), std::move(categories)};
    }

    static auto Chest(u8 scene, u8 flag, std::string&& name, std::vector<std::string>&& categories) {
        return ItemLocation{scene, ItemLocationType::Chest, flag, std::move(name), std::move(categories)};
    }

    static auto Collectable(u8 scene, u8 flag, std::string&& name, std::vector<std::string>&& categories) {
        return ItemLocation{scene, ItemLocationType::Collectable, flag, std::move(name), std::move(categories)};
    }

    static auto GSToken(u8 scene, u8 flag, std::string&& name, std::vector<std::string>&& categories) {
        return ItemLocation{scene, ItemLocationType::GSToken, flag, std::move(name), std::move(categories)};
    }

    static auto GrottoScrub(u8 scene, u8 flag, std::string&& name, std::vector<std::string>&& categories) {
        return ItemLocation{scene, ItemLocationType::GrottoScrub, flag, std::move(name), std::move(categories)};
    }

    static auto Delayed(u8 scene, u8 flag, std::string&& name, std::vector<std::string>&& categories) {
        return ItemLocation{scene, ItemLocationType::Delayed, flag, std::move(name), std::move(categories)};
    }

    static auto Reward(u8 scene, u8 flag, std::string&& name, std::vector<std::string>&& categories) {
        return ItemLocation{scene, ItemLocationType::TempleReward, flag, std::move(name), std::move(categories)};
    }

private:
    u8 scene;
    ItemLocationType type;
    u8 flag;
    bool used = false;

    std::string name;
    std::vector<std::string> categories;
    bool addedToPool = false;
    Item placedItem = NoItem;

};

class ItemLocationKeyPairing {
public:
  constexpr ItemLocationKeyPairing(ItemLocation* loc_, u8 keysRequired_)
  : loc(loc_), keysRequired(keysRequired_) {}

  ItemLocation* loc;
  u8 keysRequired;
};

//Kokiri Forest
extern ItemLocation KF_KokiriSwordChest;
extern ItemLocation KF_MidoTopLeftChest;
extern ItemLocation KF_MidoTopRightChest;
extern ItemLocation KF_MidoBottomLeftChest;
extern ItemLocation KF_MidoBottomRightChest;
extern ItemLocation KF_GSKNowItAllHouse;
extern ItemLocation KF_GSBeanPatch;
extern ItemLocation KF_GSHouseOfTwins;
extern ItemLocation KF_GossipStone;
extern ItemLocation KF_StormsGrottoChest;

//Lost Woods
extern ItemLocation LW_SkullKid;
extern ItemLocation LW_OcarinaMemoryGame;
extern ItemLocation LW_TargetInWoods;
extern ItemLocation LW_DekuScrubNearDekuTheaterRight;
extern ItemLocation LW_DekuScrubNearDekuTheaterLeft;
extern ItemLocation LW_DekuScrubNearBridge;
extern ItemLocation LW_GSBeanPatchNearBridge;
extern ItemLocation LW_GossipStone;
extern ItemLocation LW_NearShortcutsGrottoChest;
extern ItemLocation LW_DekuScrubGrottoRear;
extern ItemLocation LW_DekuScrubGrottoFront;
extern ItemLocation DekuTheater_SkullMask;
extern ItemLocation DekuTheater_MaskOfTruth;

//Sacred Forest Meadow
extern ItemLocation SFM_WolfosGrottoChest;
extern ItemLocation SFM_DekuScrubGrottoRear;
extern ItemLocation SFM_DekuScrubGrottoFront;

//Hyrule Field
extern ItemLocation HF_SoutheastGrottoChest;
extern ItemLocation HF_OpenGrottoChest;
extern ItemLocation HF_NearMarketGrottoChest;
extern ItemLocation HF_OcarinaOfTimeItem;
extern ItemLocation HF_TektiteGrottoFreestandingPoH;
extern ItemLocation HF_DekuScrubGrotto;

//Lake Hylia
extern ItemLocation LH_ChildFishing;
extern ItemLocation LH_AdultFishing;
extern ItemLocation LH_LabDive;
extern ItemLocation LH_UnderwaterItem;
extern ItemLocation LH_Sun;
extern ItemLocation LH_FreestandingPoH;
extern ItemLocation LH_DekuScrubGrottoLeft;
extern ItemLocation LH_DekuScrubGrottoRight;
extern ItemLocation LH_DekuScrubGrottoCenter;

//Gerudo Valley
extern ItemLocation GV_Chest;
extern ItemLocation GV_WaterfallFreestandingPoH;
extern ItemLocation GV_CrateFreestandingPoH;
extern ItemLocation GV_DekuScrubGrottoRear;
extern ItemLocation GV_DekuScrubGrottoFront;

//Gerudo Fortress
extern ItemLocation GF_Chest;
extern ItemLocation GF_HBA1000Points;
extern ItemLocation GF_HBA1500Points;
extern ItemLocation GF_GerudoToken;
extern ItemLocation GF_NorthF1Carpenter;
extern ItemLocation GF_NorthF2Carpenter;
extern ItemLocation GF_SouthF1Carpenter;
extern ItemLocation GF_SouthF2Carpenter;

//Haunted Wasteland
extern ItemLocation HW_Chest;

//Desert Colossus
extern ItemLocation Colossus_FreestandingPoH;
extern ItemLocation Colossus_DekuScrubGrottoRear;
extern ItemLocation Colossus_DekuScrubGrottoFront;

//Market
extern ItemLocation MK_TreasureChestGameReward;
extern ItemLocation MK_BombchuBowlingFirstPrize;
extern ItemLocation MK_BombchuBowlingSecondPrize;
extern ItemLocation MK_LostDog;
extern ItemLocation MK_ShootingGalleryReward;
extern ItemLocation MK_10BigPoes;

//Hyrule Castle
extern ItemLocation HC_ZeldasLetter;
extern ItemLocation HC_MalonEgg;

//Kakariko
extern ItemLocation Kak_RedeadGrottoChest;
extern ItemLocation Kak_OpenGrottoChest;
extern ItemLocation Kak_10GoldSkulltulaReward;
extern ItemLocation Kak_20GoldSkulltulaReward;
extern ItemLocation Kak_30GoldSkulltulaReward;
extern ItemLocation Kak_40GoldSkulltulaReward;
extern ItemLocation Kak_50GoldSkulltulaReward;
extern ItemLocation Kak_ManOnRoof;
extern ItemLocation Kak_ShootingGalleryReward;
extern ItemLocation Kak_AnjuAsChild;
extern ItemLocation Kak_AnjuAsAdult;
extern ItemLocation Kak_ImpasHouseFreestandingPoH;
extern ItemLocation Kak_WindmillFreestandingPoH;

//Graveyard
extern ItemLocation GY_HookshotChest;
extern ItemLocation GY_ShieldGraveChest;
extern ItemLocation GY_HeartPieceGraveChest;
extern ItemLocation GY_ComposersGraveChest;
extern ItemLocation GY_FreestandingPoH;
extern ItemLocation GY_DampeRaceFreestandingPoH;
extern ItemLocation GY_DampeGravediggingTour;

//Death Mountain Trail
extern ItemLocation DMT_Chest;
extern ItemLocation DMT_StormsGrottoChest;
extern ItemLocation DMT_Biggoron;
extern ItemLocation DMT_GreatFairyReward;
extern ItemLocation DMT_FreestandingPoH;

//Goron City
extern ItemLocation GC_MazeLeftChest;
extern ItemLocation GC_MazeCenterChest;
extern ItemLocation GC_MazeRightChest;
extern ItemLocation GC_RollingGoronAsChild;
extern ItemLocation GC_RollingGoronAsAdult;
extern ItemLocation GC_DaruniasJoy;
extern ItemLocation GC_PotFreestandingPoH;
extern ItemLocation GC_DekuScrubGrottoLeft;
extern ItemLocation GC_DekuScrubGrottoRight;
extern ItemLocation GC_DekuScrubGrottoCenter;

//Death Mountain
extern ItemLocation DMC_UpperGrottoChest;
extern ItemLocation DMC_WallFreestandingPoH;
extern ItemLocation DMC_VolcanoFreestandingPoH;
extern ItemLocation DMC_DekuScrubGrottoLeft;
extern ItemLocation DMC_DekuScrubGrottoRight;
extern ItemLocation DMC_DekuScrubGrottoCenter;

//Zoras River
extern ItemLocation ZR_OpenGrottoChest;
extern ItemLocation ZR_MagicBeanSalesman;
extern ItemLocation ZR_FrogsOcarinaGame;
extern ItemLocation ZR_FrogsInTheRain;
extern ItemLocation ZR_NearOpenGrottoFreestandingPoH;
extern ItemLocation ZR_NearDomainFreestandingPoH;
extern ItemLocation ZR_DekuScrubGrottoRear;
extern ItemLocation ZR_DekuScrubGrottoFront;

//Zoras Domain
extern ItemLocation ZD_Chest;
extern ItemLocation ZD_DivingMinigame;
extern ItemLocation ZD_KingZoraThawed;

//Zoras Fountain
extern ItemLocation ZF_IcebergFreestandingPoH;
extern ItemLocation ZF_BottomFreestandingPoH;

//Lon Lon Ranch
extern ItemLocation LLR_TalonsChickens;
extern ItemLocation LLR_FreestandingPoH;
extern ItemLocation LLR_DekuScrubGrottoLeft;
extern ItemLocation LLR_DekuScrubGrottoRight;
extern ItemLocation LLR_DekuScrubGrottoCenter;

//Deku Tree
extern ItemLocation DekuTree_MapChest;
extern ItemLocation DekuTree_CompassChest;
extern ItemLocation DekuTree_CompassRoomSideChest;
extern ItemLocation DekuTree_BasementChest;
extern ItemLocation DekuTree_SlingshotChest;
extern ItemLocation DekuTree_SlingshotRoomSideChest;
extern ItemLocation DekuTree_QueenGohmaHeart;

//Dodongos Cavern
extern ItemLocation DodongosCavern_MapChest;
extern ItemLocation DodongosCavern_CompassChest;
extern ItemLocation DodongosCavern_BombFlowerPlatformChest;
extern ItemLocation DodongosCavern_BombBagChest;
extern ItemLocation DodongosCavern_EndOfBridgeChest;
extern ItemLocation DodongosCavern_BossRoomChest;
extern ItemLocation DodongosCavern_DekuScrubNearBombBagLeft;
extern ItemLocation DodongosCavern_DekuScrubSideRoomNearDodongos;
extern ItemLocation DodongosCavern_DekuScrubNearBombBagRight;
extern ItemLocation DodongosCavern_DekuScrubLobby;
extern ItemLocation DodongosCavern_KingDodongoHeart;

//Jabu Jabus Belly
extern ItemLocation JabuJabusBelly_MapChest;
extern ItemLocation JabuJabusBelly_CompassChest;
extern ItemLocation JabuJabusBelly_BoomerangChest;
extern ItemLocation JabuJabusBelly_DekuScrub;
extern ItemLocation JabuJabusBelly_BarinadeHeart;

//Forest Temple
extern ItemLocation ForestTemple_FirstRoomChest;
extern ItemLocation ForestTemple_FirstStalfosChest;
extern ItemLocation ForestTemple_RaisedIslandCourtyardChest;
extern ItemLocation ForestTemple_MapChest;
extern ItemLocation ForestTemple_WellChest;
extern ItemLocation ForestTemple_FallingCeilingRoomChest;
extern ItemLocation ForestTemple_EyeSwitchChest;
extern ItemLocation ForestTemple_BossKeyChest;
extern ItemLocation ForestTemple_FloormasterChest;
extern ItemLocation ForestTemple_BowChest;
extern ItemLocation ForestTemple_RedPoeChest;
extern ItemLocation ForestTemple_BluePoeChest;
extern ItemLocation ForestTemple_BasementChest;
extern ItemLocation ForestTemple_PhantomGanonHeart;

//Fire Temple
extern ItemLocation FireTemple_NearBossChest;
extern ItemLocation FireTemple_FlareDancerChest;
extern ItemLocation FireTemple_BossKeyChest;
extern ItemLocation FireTemple_BigLavaRoomBlockedDoorChest;
extern ItemLocation FireTemple_BigLavaRoomLowerOpenDoorChest;
extern ItemLocation FireTemple_BoulderMazeLowerChest;
extern ItemLocation FireTemple_BoulderMazeUpperChest;
extern ItemLocation FireTemple_BoulderMazeSideRoomChest;
extern ItemLocation FireTemple_BoulderMazeShortcutChest;
extern ItemLocation FireTemple_ScarecrowChest;
extern ItemLocation FireTemple_MapChest;
extern ItemLocation FireTemple_CompassChest;
extern ItemLocation FireTemple_HighestGoronChest;
extern ItemLocation FireTemple_MegatonHammerChest;
extern ItemLocation FireTemple_VolvagiaHeart;

//Water Temple
extern ItemLocation WaterTemple_MapChest;
extern ItemLocation WaterTemple_CompassChest;
extern ItemLocation WaterTemple_TorchesChest;
extern ItemLocation WaterTemple_DragonChest;
extern ItemLocation WaterTemple_CentralBowTargetChest;
extern ItemLocation WaterTemple_CentralPillarChest;
extern ItemLocation WaterTemple_CrackedWallChest;
extern ItemLocation WaterTemple_BossKeyChest;
extern ItemLocation WaterTemple_LongshotChest;
extern ItemLocation WaterTemple_RiverChest;
extern ItemLocation WaterTemple_MorphaHeart;

//Spirit Temple
extern ItemLocation SpiritTemple_SilverGauntletsChest;
extern ItemLocation SpiritTemple_MirrorShieldChest;
extern ItemLocation SpiritTemple_ChildBridgeChest;
extern ItemLocation SpiritTemple_ChildEarlyTorchesChest;
extern ItemLocation SpiritTemple_CompassChest;
extern ItemLocation SpiritTemple_EarlyAdultRightChest;
extern ItemLocation SpiritTemple_FirstMirrorLeftChest;
extern ItemLocation SpiritTemple_FirstMirrorRightChest;
extern ItemLocation SpiritTemple_MapChest;
extern ItemLocation SpiritTemple_ChildClimbNorthChest;
extern ItemLocation SpiritTemple_ChildClimbEastChest;
extern ItemLocation SpiritTemple_SunBlockRoomChest;
extern ItemLocation SpiritTemple_StatueRoomHandChest;
extern ItemLocation SpiritTemple_StatueRoomNortheastChest;
extern ItemLocation SpiritTemple_NearFourArmosChest;
extern ItemLocation SpiritTemple_HallwayLeftInvisibleChest;
extern ItemLocation SpiritTemple_HallwayRightInvisibleChest;
extern ItemLocation SpiritTemple_BossKeyChest;
extern ItemLocation SpiritTemple_TopmostChest;
extern ItemLocation SpiritTemple_TwinrovaHeart;

//Shadow Temple
extern ItemLocation ShadowTemple_MapChest;
extern ItemLocation ShadowTemple_HoverBootsChest;
extern ItemLocation ShadowTemple_CompassChest;
extern ItemLocation ShadowTemple_EarlySilverRupeeChest;
extern ItemLocation ShadowTemple_InvisibleBladesVisibleChest;
extern ItemLocation ShadowTemple_InvisibleBladesInvisibleChest;
extern ItemLocation ShadowTemple_FallingSpikesLowerChest;
extern ItemLocation ShadowTemple_FallingSpikesUpperChest;
extern ItemLocation ShadowTemple_FallingSpikesSwitchChest;
extern ItemLocation ShadowTemple_InvisibleSpikesChest;
extern ItemLocation ShadowTemple_WindHintChest;
extern ItemLocation ShadowTemple_AfterWindEnemyChest;
extern ItemLocation ShadowTemple_AfterWindHiddenChest;
extern ItemLocation ShadowTemple_SpikeWallsLeftChest;
extern ItemLocation ShadowTemple_BossKeyChest;
extern ItemLocation ShadowTemple_InvisibleFloormasterChest;
extern ItemLocation ShadowTemple_FreestandingKey;
extern ItemLocation ShadowTemple_BongoBongoHeart;

//Bottom of the Well
extern ItemLocation BottomOfTheWell_FrontLeftFakeWallChest;
extern ItemLocation BottomOfTheWell_FrontCenterBombableChest;
extern ItemLocation BottomOfTheWell_RightBottomFakeWallChest;
extern ItemLocation BottomOfTheWell_CompassChest;
extern ItemLocation BottomOfTheWell_CenterSkulltulaChest;
extern ItemLocation BottomOfTheWell_BackLeftBombableChest;
extern ItemLocation BottomOfTheWell_LensOfTruthChest;
extern ItemLocation BottomOfTheWell_InvisibleChest;
extern ItemLocation BottomOfTheWell_UnderwaterFrontChest;
extern ItemLocation BottomOfTheWell_UnderwaterLeftChest;
extern ItemLocation BottomOfTheWell_MapChest;
extern ItemLocation BottomOfTheWell_FireKeeseChest;
extern ItemLocation BottomOfTheWell_LikeLikeChest;
extern ItemLocation BottomOfTheWell_FreestandingKey;

//Ice Cavern
extern ItemLocation IceCavern_MapChest;
extern ItemLocation IceCavern_CompassChest;
extern ItemLocation IceCavern_IronBootsChest;
extern ItemLocation IceCavern_FreestandingPoH;

//Gerudo Training Grounds
extern ItemLocation GerudoTrainingGrounds_LobbyLeftChest;
extern ItemLocation GerudoTrainingGrounds_LobbyRightChest;
extern ItemLocation GerudoTrainingGrounds_StalfosChest;
extern ItemLocation GerudoTrainingGrounds_BeamosChest;
extern ItemLocation GerudoTrainingGrounds_HiddenCeilingChest;
extern ItemLocation GerudoTrainingGrounds_MazePathFirstChest;
extern ItemLocation GerudoTrainingGrounds_MazePathSecondChest;
extern ItemLocation GerudoTrainingGrounds_MazePathThirdChest;
extern ItemLocation GerudoTrainingGrounds_MazePathFinalChest;
extern ItemLocation GerudoTrainingGrounds_MazeRightCentralChest;
extern ItemLocation GerudoTrainingGrounds_MazeRightSideChest;
extern ItemLocation GerudoTrainingGrounds_UnderwaterSilverRupeeChest;
extern ItemLocation GerudoTrainingGrounds_HammerRoomClearChest;
extern ItemLocation GerudoTrainingGrounds_HammerRoomSwitchChest;
extern ItemLocation GerudoTrainingGrounds_EyeStatueChest;
extern ItemLocation GerudoTrainingGrounds_NearScarecrowChest;
extern ItemLocation GerudoTrainingGrounds_BeforeHeavyBlockChest;
extern ItemLocation GerudoTrainingGrounds_HeavyBlockFirstChest;
extern ItemLocation GerudoTrainingGrounds_HeavyBlockSecondChest;
extern ItemLocation GerudoTrainingGrounds_HeavyBlockThirdChest;
extern ItemLocation GerudoTrainingGrounds_HeavyBlockFourthChest;
extern ItemLocation GerudoTrainingGrounds_FreestandingKey;

//Ganon's Castle
extern ItemLocation GanonsCastle_BossKeyChest;
extern ItemLocation GanonsCastle_ForestTrialChest;
extern ItemLocation GanonsCastle_WaterTrialLeftChest;
extern ItemLocation GanonsCastle_WaterTrialRightChest;
extern ItemLocation GanonsCastle_ShadowTrialFrontChest;
extern ItemLocation GanonsCastle_ShadowTrialGoldenGauntletsChest;
extern ItemLocation GanonsCastle_SpiritTrialCrystalSwitchChest;
extern ItemLocation GanonsCastle_SpiritTrialInvisibleChest;
extern ItemLocation GanonsCastle_LightTrialFirstLeftChest;
extern ItemLocation GanonsCastle_LightTrialSecondLeftChest;
extern ItemLocation GanonsCastle_LightTrialThirdLeftChest;
extern ItemLocation GanonsCastle_LightTrialFirstRightChest;
extern ItemLocation GanonsCastle_LightTrialSecondRightChest;
extern ItemLocation GanonsCastle_LightTrialThirdRightChest;
extern ItemLocation GanonsCastle_LightTrialInvisibleEnemiesChest;
extern ItemLocation GanonsCastle_LightTrialLullabyChest;
extern ItemLocation GanonsCastle_DekuScrubCenterLeft;
extern ItemLocation GanonsCastle_DekuScrubCenterRight;
extern ItemLocation GanonsCastle_DekuScrubRight;
extern ItemLocation GanonsCastle_DekuScrubLeft;

/*-------------------------------
   --- GOLD SKULLTULA TOKENS ---
  -------------------------------*/

//Deku Tree
extern ItemLocation DekuTree_GS_BasementBackRoom;
extern ItemLocation DekuTree_GS_BasementGate;
extern ItemLocation DekuTree_GS_BasementVines;
extern ItemLocation DekuTree_GS_CompassRoom;

//Dodongos Cavern
extern ItemLocation DodongosCavern_GS_VinesAboveStairs;
extern ItemLocation DodongosCavern_GS_Scarecrow;
extern ItemLocation DodongosCavern_GS_AlcoveAboveStairs;
extern ItemLocation DodongosCavern_GS_BackRoom;
extern ItemLocation DodongosCavern_GS_SideRoomNearLowerLizalfos;

//Jabu Jabus Belly
extern ItemLocation JabuJabusBelly_GS_LobbyBasementLower;
extern ItemLocation JabuJabusBelly_GS_LobbyBasementUpper;
extern ItemLocation JabuJabusBelly_GS_NearBoss;
extern ItemLocation JabuJabusBelly_GS_WaterSwitchRoom;

//Forest Temple
extern ItemLocation ForestTemple_GS_RaisedIslandCourtyard;
extern ItemLocation ForestTemple_GS_FirstRoom;
extern ItemLocation ForestTemple_GS_LevelIslandCourtyard;
extern ItemLocation ForestTemple_GS_Lobby;
extern ItemLocation ForestTemple_GS_Basement;

//Fire Temple
extern ItemLocation FireTemple_GS_SongOfTimeRoom;
extern ItemLocation FireTemple_GS_BossKeyLoop;
extern ItemLocation FireTemple_GS_BoulderMaze;
extern ItemLocation FireTemple_GS_ScarecrowTop;
extern ItemLocation FireTemple_GS_ScarecrowClimb;

//Water Temple
extern ItemLocation WaterTemple_GS_BehindGate;
extern ItemLocation WaterTemple_GS_FallingPlatformRoom;
extern ItemLocation WaterTemple_GS_CentralPillar;
extern ItemLocation WaterTemple_GS_NearBossKeyChest;
extern ItemLocation WaterTemple_GS_River;

//Spirit Temple
extern ItemLocation SpiritTemple_GS_HallAfterSunBlockRoom;
extern ItemLocation SpiritTemple_GS_BoulderRoom;
extern ItemLocation SpiritTemple_GS_Lobby;
extern ItemLocation SpiritTemple_GS_SunOnFloorRoom;
extern ItemLocation SpiritTemple_GS_MetalFence;

//Shadow Temple
extern ItemLocation ShadowTemple_GS_SingleGiantPot;
extern ItemLocation ShadowTemple_GS_FallingSpikesRoom;
extern ItemLocation ShadowTemple_GS_TripleGiantPot;
extern ItemLocation ShadowTemple_GS_LikeLikeRoom;
extern ItemLocation ShadowTemple_GS_NearShip;

//Bottom of the Well
extern ItemLocation BottomOfTheWell_GS_LikeLikeCage;
extern ItemLocation BottomOfTheWell_GS_EastInnerRoom;
extern ItemLocation BottomOfTheWell_GS_WestInnerRoom;

//Ice Cavern
extern ItemLocation IceCavern_GS_PushBlockRoom;
extern ItemLocation IceCavern_GS_SpinningScytheRoom;
extern ItemLocation IceCavern_GS_HeartPieceRoom;

//Overworld
extern ItemLocation KF_GS_BeanPatch;
extern ItemLocation KF_GS_KnowItAllHouse;
extern ItemLocation KF_GS_HouseOfTwins;

extern ItemLocation LW_GS_BeanPatchNearBridge;
extern ItemLocation LW_GS_BeanPatchNearTheater;
extern ItemLocation LW_GS_AboveTheater;
extern ItemLocation SFM_GS;

extern ItemLocation HF_GS_CowGrotto;
extern ItemLocation HF_GS_NearKakGrotto;

extern ItemLocation LH_GS_BeanPatch;
extern ItemLocation LH_GS_SmallIsland;
extern ItemLocation LH_GS_LabWall;
extern ItemLocation LH_GS_LabCrate;
extern ItemLocation LH_GS_Tree;

extern ItemLocation GV_GS_BeanPatch;
extern ItemLocation GV_GS_SmallBridge;
extern ItemLocation GV_GS_Pillar;
extern ItemLocation GV_GS_BehindTent;

extern ItemLocation GF_GS_ArcheryRange;
extern ItemLocation GF_GS_TopFloor;

extern ItemLocation HW_GS;
extern ItemLocation Colossus_GS_BeanPatch;
extern ItemLocation Colossus_GS_Hill;
extern ItemLocation Colossus_GS_Tree;

extern ItemLocation OGC_GS;
extern ItemLocation HC_GS_StormsGrotto;
extern ItemLocation HC_GS_Tree;
extern ItemLocation MK_GS_GuardHouse;

extern ItemLocation Kak_GS_HouseUnderConstruction;
extern ItemLocation Kak_GS_SkulltulaHouse;
extern ItemLocation Kak_GS_GuardsHouse;
extern ItemLocation Kak_GS_Tree;
extern ItemLocation Kak_GS_Watchtower;
extern ItemLocation Kak_GS_AboveImpasHouse;

extern ItemLocation DMC_GS_BeanPatch;
extern ItemLocation DMC_GS_Crate;

extern ItemLocation DMT_GS_BeanPatch;
extern ItemLocation DMT_GS_NearKak;
extern ItemLocation DMT_GS_AboveDodongosCavern;
extern ItemLocation DMT_GS_FallingRocksPath;

extern ItemLocation GC_GS_CenterPlatform;
extern ItemLocation GC_GS_BoulderMaze;
extern ItemLocation GY_GS_Wall;
extern ItemLocation GY_GS_BeanPatch;

extern ItemLocation ZR_GS_Ladder;
extern ItemLocation ZR_GS_Tree;
extern ItemLocation ZR_GS_AboveBridge;
extern ItemLocation ZR_GS_NearRaisedGrottos;

extern ItemLocation ZD_GS_FrozenWaterfall;
extern ItemLocation ZF_GS_AboveTheLog;
extern ItemLocation ZF_GS_HiddenCave;
extern ItemLocation ZF_GS_Tree;

extern ItemLocation LLR_GS_BackWall;
extern ItemLocation LLR_GS_RainShed;
extern ItemLocation LLR_GS_HouseWindow;
extern ItemLocation LLR_GS_Tree;

/*-------------------------------
          --- BOSSES ---
  -------------------------------*/

extern ItemLocation LinksPocket;
extern ItemLocation QueenGohma;
extern ItemLocation KingDodongo;
extern ItemLocation PhantomGanon;
extern ItemLocation Barinade;
extern ItemLocation Volvagia;
extern ItemLocation Twinrova;
extern ItemLocation Morpha;
extern ItemLocation BongoBongo;

/*-------------------------------
        --- CUTSCENES ---
  -------------------------------*/

extern ItemLocation SheikInForest;
extern ItemLocation SheikInCrater;
extern ItemLocation SheikInIceCavern;
extern ItemLocation SheikAtColossus;
extern ItemLocation SheikInKakariko;
extern ItemLocation SheikAtTemple;
extern ItemLocation SongFromImpa;
extern ItemLocation SongFromMalon;
extern ItemLocation SongFromSaria;
extern ItemLocation SongFromComposersGrave;
extern ItemLocation SongFromOcarinaOfTime;
extern ItemLocation SongFromWindmill;

extern ItemLocation ToT_LightArrowCutscene;
extern ItemLocation LW_GiftFromSaria;
extern ItemLocation ZF_GreatFairyReward;
extern ItemLocation HC_GreatFairyReward;
extern ItemLocation Colossus_GreatFairyReward;
extern ItemLocation DMT_GreatFairyReward;
extern ItemLocation DMC_GreatFairyReward;
extern ItemLocation OGC_GreatFairyReward;

/*-------------------------------
          --- SHOPS ---
  -------------------------------*/

extern ItemLocation KF_ShopItem1;
extern ItemLocation KF_ShopItem2;
extern ItemLocation KF_ShopItem3;
extern ItemLocation KF_ShopItem4;
extern ItemLocation KF_ShopItem5;
extern ItemLocation KF_ShopItem6;
extern ItemLocation KF_ShopItem7;
extern ItemLocation KF_ShopItem8;

extern ItemLocation Kak_PotionShopItem1;
extern ItemLocation Kak_PotionShopItem2;
extern ItemLocation Kak_PotionShopItem3;
extern ItemLocation Kak_PotionShopItem4;
extern ItemLocation Kak_PotionShopItem5;
extern ItemLocation Kak_PotionShopItem6;
extern ItemLocation Kak_PotionShopItem7;
extern ItemLocation Kak_PotionShopItem8;

extern ItemLocation MK_BombchuShopItem1;
extern ItemLocation MK_BombchuShopItem2;
extern ItemLocation MK_BombchuShopItem3;
extern ItemLocation MK_BombchuShopItem4;
extern ItemLocation MK_BombchuShopItem5;
extern ItemLocation MK_BombchuShopItem6;
extern ItemLocation MK_BombchuShopItem7;
extern ItemLocation MK_BombchuShopItem8;

extern ItemLocation MK_PotionShopItem1;
extern ItemLocation MK_PotionShopItem2;
extern ItemLocation MK_PotionShopItem3;
extern ItemLocation MK_PotionShopItem4;
extern ItemLocation MK_PotionShopItem5;
extern ItemLocation MK_PotionShopItem6;
extern ItemLocation MK_PotionShopItem7;
extern ItemLocation MK_PotionShopItem8;

extern ItemLocation MK_BazaarItem1;
extern ItemLocation MK_BazaarItem2;
extern ItemLocation MK_BazaarItem3;
extern ItemLocation MK_BazaarItem4;
extern ItemLocation MK_BazaarItem5;
extern ItemLocation MK_BazaarItem6;
extern ItemLocation MK_BazaarItem7;
extern ItemLocation MK_BazaarItem8;

extern ItemLocation Kak_BazaarItem1;
extern ItemLocation Kak_BazaarItem2;
extern ItemLocation Kak_BazaarItem3;
extern ItemLocation Kak_BazaarItem4;
extern ItemLocation Kak_BazaarItem5;
extern ItemLocation Kak_BazaarItem6;
extern ItemLocation Kak_BazaarItem7;
extern ItemLocation Kak_BazaarItem8;

extern ItemLocation ZD_ShopItem1;
extern ItemLocation ZD_ShopItem2;
extern ItemLocation ZD_ShopItem3;
extern ItemLocation ZD_ShopItem4;
extern ItemLocation ZD_ShopItem5;
extern ItemLocation ZD_ShopItem6;
extern ItemLocation ZD_ShopItem7;
extern ItemLocation ZD_ShopItem8;

extern ItemLocation GC_ShopItem1;
extern ItemLocation GC_ShopItem2;
extern ItemLocation GC_ShopItem3;
extern ItemLocation GC_ShopItem4;
extern ItemLocation GC_ShopItem5;
extern ItemLocation GC_ShopItem6;
extern ItemLocation GC_ShopItem7;
extern ItemLocation GC_ShopItem8;

extern const std::array<ItemLocationKeyPairing, 10> DekuTreeKeyRequirements;
extern const std::array<ItemLocationKeyPairing, 11> DodongosCavernKeyRequirements;
extern const std::array<ItemLocationKeyPairing, 7>  JabuJabusBellyKeyRequirements;
extern const std::array<ItemLocationKeyPairing, 19> ForestTempleKeyRequirements;
extern const std::array<ItemLocationKeyPairing, 20> FireTempleKeyRequirements;
extern const std::array<ItemLocationKeyPairing, 16> WaterTempleKeyRequirements;
extern const std::array<ItemLocationKeyPairing, 26> SpiritTempleKeyRequirements;
extern const std::array<ItemLocationKeyPairing, 23> ShadowTempleKeyRequirements;
extern const std::array<ItemLocationKeyPairing, 17> BottomOfTheWellKeyRequirements;
extern const std::array<ItemLocationKeyPairing, 7>  IceCavernKeyRequirements;
extern const std::array<ItemLocationKeyPairing, 22> GerudoTrainingGroundsKeyRequirements;
extern const std::array<ItemLocationKeyPairing, 16> GanonsCastleKeyRequirements;

extern std::vector<ItemLocation *> advancementLocations;
extern std::array<ItemLocation *, 9> dungeonRewardLocations;
extern std::array<ItemLocation *, 354> allLocations;
