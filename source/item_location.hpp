#pragma once
#include <functional>
#include <vector>
#include <unistd.h>
#include <cstdio>
#include <string>
#include "../code/include/z3D/z3D.h"
#include "../code/src/item_override.h"
#include "item_list.hpp"

enum ItemLocationType {
    ITEMLOCATIONTYPE_NPC,
    ITEMLOCATIONTYPE_CHEST,
    ITEMLOCATIONTYPE_COLLECTABLE,
    ITEMLOCATIONTYPE_SONG,
    ITEMLOCATIONTYPE_GROTTO_SCRUB,
};

class ItemLocation {
public:
    ItemLocation(u8 scene_, ItemLocationType type_, u8 flag_, std::string name_)
        : scene(scene_), type(type_), flag(flag_), name(std::move(name_)) {}

    ItemOverride_Key key() const {
        ItemOverride_Key key;
        key.all = 0;

        key.scene = scene;
        key.type = type; //TODO make sure these match up
        key.flag = flag;
        return key;
    }

    void use() {
      used = true;
    }

    bool isUsed() const {
      return used;
    }

    const char * getName() {
      return name.c_str();
    }

    Item placedItem = NoItem;

private:
    u8 scene;
    ItemLocationType type;
    u8 flag;
    bool used = false;

public:
    std::string name;

};

extern std::vector<ItemLocation> LocationPool;

extern ItemLocation LinksPocket;

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

//Dodongos Cavern
extern ItemLocation DodongosCavern_MapChest;
extern ItemLocation DodongosCavern_CompassChest;
extern ItemLocation DodongosCavern_BombFlowerPlatformChest;
extern ItemLocation DodongosCavern_BombBagChest;
extern ItemLocation DodongosCavern_EndOfBridgeChest;
extern ItemLocation DodongosCavern_BossRoomChest;

//Jabu Jabus Belly
extern ItemLocation JabuJabusBelly_MapChest;
extern ItemLocation JabuJabusBelly_CompassChest;
extern ItemLocation JabuJabusBelly_BoomerangChest;

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
