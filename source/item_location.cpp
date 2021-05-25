#include "item_location.hpp"

#include "dungeon.hpp"
#include "settings.hpp"
#include "spoiler_log.hpp"
#include "hint_list.hpp"
#include "shops.hpp"

//Location definitions
//Kokiri Forest                                                          scene  flag  name                                    hint key (hint_list.cpp)            categories
ItemLocation KF_KokiriSwordChest              = ItemLocation::Chest      (0x55, 0x00, "KF Kokiri Sword Chest",                KF_KOKIRI_SWORD_CHEST,              {Category::cKokiriForest, Category::cForest,});
ItemLocation KF_MidoTopLeftChest              = ItemLocation::Chest      (0x28, 0x00, "KF Mido Top Left Chest",               KF_MIDOS_TOP_LEFT_CHEST,            {Category::cKokiriForest, Category::cForest,});
ItemLocation KF_MidoTopRightChest             = ItemLocation::Chest      (0x28, 0x01, "KF Mido Top Right Chest",              KF_MIDOS_TOP_RIGHT_CHEST,           {Category::cKokiriForest, Category::cForest,});
ItemLocation KF_MidoBottomLeftChest           = ItemLocation::Chest      (0x28, 0x02, "KF Mido Bottom Left Chest",            KF_MIDOS_BOTTOM_LEFT_CHEST,         {Category::cKokiriForest, Category::cForest,});
ItemLocation KF_MidoBottomRightChest          = ItemLocation::Chest      (0x28, 0x03, "KF Mido Bottom Right Chest",           KF_MIDOS_BOTTOM_RIGHT_CHEST,        {Category::cKokiriForest, Category::cForest,});
ItemLocation KF_StormsGrottoChest             = ItemLocation::Chest      (0x3E, 0x0C, "KF Storms Grotto Chest",               KF_STORMS_GROTTO_CHEST,             {Category::cKokiriForest, Category::cForest, Category::cGrotto});

//Lost Woods
ItemLocation LW_NearShortcutsGrottoChest      = ItemLocation::Chest      (0x3E, 0x14, "LW Near Shortcuts Grotto Chest",       LW_NEAR_SHORTCUTS_GROTTO_CHEST,      {Category::cLostWoods, Category::cForest, Category::cGrotto});
ItemLocation LW_SkullKid                      = ItemLocation::Base       (0x5B, 0x3E, "LW Skull Kid",                         LW_SKULL_KID,                      {Category::cLostWoods, Category::cForest,});
ItemLocation LW_OcarinaMemoryGame             = ItemLocation::Base       (0x5B, 0x76, "LW Ocarina Memory Game",               LW_OCARINA_MEMORY_GAME,             {Category::cLostWoods, Category::cForest, Category::cMinigame});
ItemLocation LW_TargetInWoods                 = ItemLocation::Base       (0x5B, 0x60, "LW Target in Woods",                   LW_TARGET_IN_WOODS,                 {Category::cLostWoods, Category::cForest,});
ItemLocation LW_DekuScrubNearDekuTheaterRight = ItemLocation::Base       (0x5B, 0x30, "LW Deku Scrub Near Deku Theater Right",LW_DEKU_SCRUB_NEAR_DEKU_THEATER_RIGHT, {Category::cLostWoods, Category::cForest, Category::cDekuScrub});
ItemLocation LW_DekuScrubNearDekuTheaterLeft  = ItemLocation::Base       (0x5B, 0x31, "LW Deku Scrub Near Deku Theater Left", LW_DEKU_SCRUB_NEAR_DEKU_THEATER_LEFT,  {Category::cLostWoods, Category::cForest, Category::cDekuScrub});
ItemLocation LW_DekuScrubNearBridge           = ItemLocation::Base       (0x5B, 0x77, "LW Deku Scrub Near Bridge",            LW_DEKU_SCRUB_NEAR_BRIDGE,           {Category::cLostWoods, Category::cForest, Category::cDekuScrub, Category::cDekuScrubUpgrades});
ItemLocation LW_DekuScrubGrottoRear           = ItemLocation::GrottoScrub(0xF5, 0x33, "LW Deku Scrub Grotto Rear",            LW_DEKU_SCRUB_GROTTO_REAR,           {Category::cLostWoods, Category::cForest, Category::cDekuScrub, Category::cGrotto});
ItemLocation LW_DekuScrubGrottoFront          = ItemLocation::GrottoScrub(0xF5, 0x79, "LW Deku Scrub Grotto Front",           LW_DEKU_SCRUB_GROTTO_FRONT,          {Category::cLostWoods, Category::cForest, Category::cDekuScrub, Category::cDekuScrubUpgrades, Category::cGrotto});
ItemLocation DekuTheater_SkullMask            = ItemLocation::Base       (0x3E, 0x77, "Deku Theater Skull Mask",              DEKU_THEATER_SKULL_MASK,            {Category::cLostWoods, Category::cForest, Category::cGrotto});
ItemLocation DekuTheater_MaskOfTruth          = ItemLocation::Base       (0x3E, 0x7A, "Deku Theater Mask of Truth",           DEKU_THEATER_MASK_OF_TRUTH,          {Category::cLostWoods, Category::cForest, Category::cNeedSpiritualStones, Category::cGrotto});

//Sacred Forest Meadow
ItemLocation SFM_WolfosGrottoChest            = ItemLocation::Chest      (0x3E, 0x11, "SFM Wolfos Grotto Chest",              SFM_WOLFOS_GROTTO_CHEST,            {Category::cSacredForestMeadow, Category::cForest, Category::cGrotto});
ItemLocation SFM_DekuScrubGrottoRear          = ItemLocation::GrottoScrub(0xEE, 0x39, "SFM Deku Scrub Grotto Rear",           SFM_DEKU_SCRUB_GROTTO_REAR,          {Category::cSacredForestMeadow, Category::cForest, Category::cDekuScrub, Category::cGrotto});
ItemLocation SFM_DekuScrubGrottoFront         = ItemLocation::GrottoScrub(0xEE, 0x3A, "SFM Deku Scrub Grotto Front",          SFM_DEKU_SCRUB_GROTTO_FRONT,         {Category::cSacredForestMeadow, Category::cForest, Category::cDekuScrub, Category::cGrotto});

//Hyrule Field
ItemLocation HF_SoutheastGrottoChest          = ItemLocation::Chest      (0x3E, 0x02, "HF Southeast Grotto Chest",            HF_SOUTHEAST_GROTTO_CHEST,          {Category::cHyruleField, Category::cGrotto,});
ItemLocation HF_OpenGrottoChest               = ItemLocation::Chest      (0x3E, 0x03, "HF Open Grotto Chest",                 HF_OPEN_GROTTO_CHEST,               {Category::cHyruleField, Category::cGrotto,});
ItemLocation HF_NearMarketGrottoChest         = ItemLocation::Chest      (0x3E, 0x00, "HF Near Market Grotto Chest",          HF_NEAR_MARKET_GROTTO_CHEST,         {Category::cHyruleField, Category::cGrotto,});
ItemLocation HF_OcarinaOfTimeItem             = ItemLocation::Base       (0x51, 0x0C, "HF Ocarina of Time Item",              HF_OCARINA_OF_TIME_ITEM,             {Category::cHyruleField, Category::cNeedSpiritualStones,});
ItemLocation HF_TektiteGrottoFreestandingPoH  = ItemLocation::Collectable(0x3E, 0x01, "HF Tektite Grotto Freestanding PoH",   HF_TEKTITE_GROTTO_FREESTANDING_POH,  {Category::cHyruleField, Category::cGrotto,});
ItemLocation HF_DekuScrubGrotto               = ItemLocation::GrottoScrub(0xE6, 0x3E, "HF Deku Scrub Grotto",                 HF_DEKU_SCRUB_GROTTO,               {Category::cHyruleField, Category::cDekuScrub, Category::cDekuScrubUpgrades, Category::cGrotto});

//Lake Hylia
ItemLocation LH_ChildFishing                  = ItemLocation::Base       (0x49, 0x3E, "LH Child Fishing",                     LH_CHILD_FISHING,                  {Category::cLakeHylia, Category::cMinigame,});
ItemLocation LH_AdultFishing                  = ItemLocation::Base       (0x49, 0x38, "LH Adult Fishing",                     LH_ADULT_FISHING,                  {Category::cLakeHylia, Category::cMinigame,});
ItemLocation LH_LabDive                       = ItemLocation::Base       (0x38, 0x3E, "LH Lab Dive",                          LH_LAB_DIVE,                       {Category::cLakeHylia,});
ItemLocation LH_UnderwaterItem                = ItemLocation::Base       (0x57, 0x15, "LH Underwater Item",                   LH_UNDERWATER_ITEM,                {Category::cLakeHylia,});
ItemLocation LH_Sun                           = ItemLocation::Base       (0x57, 0x58, "LH Sun",                               LH_SUN,                           {Category::cLakeHylia,});
ItemLocation LH_FreestandingPoH               = ItemLocation::Collectable(0x57, 0x1E, "LH Freestanding PoH",                  LH_FREESTANDING_POH,               {Category::cLakeHylia,});
ItemLocation LH_DekuScrubGrottoLeft           = ItemLocation::GrottoScrub(0xEF, 0x30, "LH Deku Scrub Grotto Left",            LH_DEKU_SCRUB_GROTTO_LEFT,           {Category::cLakeHylia, Category::cDekuScrub, Category::cGrotto});
ItemLocation LH_DekuScrubGrottoRight          = ItemLocation::GrottoScrub(0xEF, 0x37, "LH Deku Scrub Grotto Right",           LH_DEKU_SCRUB_GROTTO_RIGHT,          {Category::cLakeHylia, Category::cDekuScrub, Category::cGrotto});
ItemLocation LH_DekuScrubGrottoCenter         = ItemLocation::GrottoScrub(0xEF, 0x33, "LH Deku Scrub Grotto Center",          LH_DEKU_SCRUB_GROTTO_CENTER,         {Category::cLakeHylia, Category::cDekuScrub, Category::cGrotto});

//Gerudo Valley
ItemLocation GV_Chest                         = ItemLocation::Chest      (0x5A, 0x00, "GV Chest",                             GV_CHEST,                         {Category::cGerudoValley, Category::cGerudo,});
ItemLocation GV_WaterfallFreestandingPoH      = ItemLocation::Collectable(0x5A, 0x01, "GV Waterfall Freestanding PoH",        GV_WATERFALL_FREESTANDING_POH,      {Category::cGerudoValley, Category::cGerudo,});
ItemLocation GV_CrateFreestandingPoH          = ItemLocation::Collectable(0x5A, 0x02, "GV Crate Freestanding PoH",            GV_CRATE_FREESTANDING_POH,          {Category::cGerudoValley, Category::cGerudo,});
ItemLocation GV_DekuScrubGrottoRear           = ItemLocation::GrottoScrub(0xF0, 0x39, "GV Deku Scrub Grotto Rear",            GV_DEKU_SCRUB_GROTTO_REAR,           {Category::cGerudoValley, Category::cGerudo, Category::cDekuScrub, Category::cGrotto});
ItemLocation GV_DekuScrubGrottoFront          = ItemLocation::GrottoScrub(0xF0, 0x3A, "GV Deku Scrub Grotto Front",           GV_DEKU_SCRUB_GROTTO_FRONT,          {Category::cGerudoValley, Category::cGerudo, Category::cDekuScrub, Category::cGrotto});

//Gerudo Fortress
ItemLocation GF_Chest                         = ItemLocation::Chest      (0x5D, 0x00, "GF Chest",                             GF_CHEST,                         {Category::cGerudoFortress, Category::cGerudo,});
ItemLocation GF_HBA1000Points                 = ItemLocation::Base       (0x5D, 0x3E, "GF HBA 1000 Points",                   GF_HBA_1000_POINTS,                 {Category::cGerudoFortress, Category::cGerudo, Category::cMinigame});
ItemLocation GF_HBA1500Points                 = ItemLocation::Base       (0x5D, 0x30, "GF HBA 1500 Points",                   GF_HBA_1500_POINTS,                 {Category::cGerudoFortress, Category::cGerudo, Category::cMinigame});
ItemLocation GF_GerudoToken                   = ItemLocation::Base       (0x0C, 0x3A, "GF Gerudo Token",                      GF_GERUDO_TOKEN,                   {Category::cGerudoFortress, Category::cGerudo,});
ItemLocation GF_NorthF1Carpenter              = ItemLocation::Collectable(0x0C, 0x0C, "GF North F1 Carpenter",                GF_NORTH_F1_CARPENTER,              {Category::cGerudoFortress, Category::cGerudo, Category::cVanillaGFSmallKey});
ItemLocation GF_NorthF2Carpenter              = ItemLocation::Collectable(0x0C, 0x0A, "GF North F2 Carpenter",                GF_NORTH_F2_CARPENTER,              {Category::cGerudoFortress, Category::cGerudo, Category::cVanillaGFSmallKey});
ItemLocation GF_SouthF1Carpenter              = ItemLocation::Collectable(0x0C, 0x0E, "GF South F1 Carpenter",                GF_SOUTH_F1_CARPENTER,              {Category::cGerudoFortress, Category::cGerudo, Category::cVanillaGFSmallKey});
ItemLocation GF_SouthF2Carpenter              = ItemLocation::Collectable(0x0C, 0x0F, "GF South F2 Carpenter",                GF_SOUTH_F2_CARPENTER,              {Category::cGerudoFortress, Category::cGerudo, Category::cVanillaGFSmallKey});

//Haunted Wasteland
ItemLocation HW_Chest                         = ItemLocation::Chest      (0x5E, 0x00, "HW Chest",                             WASTELAND_CHEST,                    {Category::cHauntedWasteland,});

//Desert Colossus
ItemLocation Colossus_FreestandingPoH         = ItemLocation::Collectable(0x5C, 0x0D, "Colossus Freestanding PoH",            COLOSSUS_FREESTANDING_POH,         {Category::cDesertColossus,});
ItemLocation Colossus_DekuScrubGrottoRear     = ItemLocation::GrottoScrub(0xFD, 0x39, "Colossus Deku Scrub Grotto Rear",      COLOSSUS_DEKU_SCRUB_GROTTO_REAR,     {Category::cDesertColossus, Category::cDekuScrub, Category::cGrotto});
ItemLocation Colossus_DekuScrubGrottoFront    = ItemLocation::GrottoScrub(0xFD, 0x3A, "Colossus Deku Scrub Grotto Front",     COLOSSUS_DEKU_SCRUB_GROTTO_FRONT,    {Category::cDesertColossus, Category::cDekuScrub, Category::cGrotto});

//Market
ItemLocation MK_TreasureChestGameReward       = ItemLocation::Chest      (0x10, 0x0A, "MK Treasure Chest Game Reward",        MARKET_TREASURE_CHEST_GAME_REWARD,       {Category::cInnerMarket, Category::cMarket, Category::cMinigame});
ItemLocation MK_BombchuBowlingFirstPrize      = ItemLocation::Base       (0x4B, 0x33, "MK Bombchu Bowling First Prize",       MARKET_BOMBCHU_BOWLING_FIRST_PRIZE,      {Category::cInnerMarket, Category::cMarket, Category::cMinigame});
ItemLocation MK_BombchuBowlingSecondPrize     = ItemLocation::Base       (0x4B, 0x3E, "MK Bombchu Bowling Second Prize",      MARKET_BOMBCHU_BOWLING_SECOND_PRIZE,     {Category::cInnerMarket, Category::cMarket, Category::cMinigame});
ItemLocation MK_BombchuBowlingBombchus        = ItemLocation::Base       (0x4B, 0xFF, "MK Bombchu Bowling Bombchus",          NONE,                       {Category::cInnerMarket, Category::cMarket, Category::cMinigame});
ItemLocation MK_LostDog                       = ItemLocation::Base       (0x35, 0x3E, "MK Lost Dog",                          MARKET_LOST_DOG,                       {Category::cInnerMarket, Category::cMarket,});
ItemLocation MK_ShootingGalleryReward         = ItemLocation::Base       (0x42, 0x60, "MK Shooting Gallery",                  MARKET_SHOOTING_GALLERY_REWARD,               {Category::cInnerMarket, Category::cMarket, Category::cMinigame});
ItemLocation MK_10BigPoes                     = ItemLocation::Base       (0x4D, 0x0F, "MK 10 Big Poes",                       MARKET_10_BIG_POES,                     {Category::cInnerMarket, Category::cHyruleCastle,});

//Hyrule Castle
ItemLocation HC_MalonEgg                      = ItemLocation::Base       (0x5F, 0x47, "HC Malon Egg",                         HC_MALON_EGG,                      {Category::cHyruleCastle, Category::cMarket,});
ItemLocation HC_ZeldasLetter                  = ItemLocation::Base       (0x4A, 0x0B, "HC Zeldas Letter",                     HC_ZELDAS_LETTER,                  {Category::cHyruleCastle, Category::cMarket,});

//Kakariko
ItemLocation Kak_RedeadGrottoChest            = ItemLocation::Chest      (0x3E, 0x0A, "Kak Redead Grotto Chest",              KAK_REDEAD_GROTTO_CHEST,            {Category::cKakarikoVillage, Category::cKakariko, Category::cGrotto});
ItemLocation Kak_OpenGrottoChest              = ItemLocation::Chest      (0x3E, 0x08, "Kak Open Grotto Chest",                KAK_OPEN_GROTTO_CHEST,              {Category::cKakarikoVillage, Category::cKakariko, Category::cGrotto});
ItemLocation Kak_10GoldSkulltulaReward        = ItemLocation::Base       (0x50, 0x45, "Kak 10 Gold Skulltula Reward",         KAK_10_GOLD_SKULLTULA_REWARD,        {Category::cKakarikoVillage, Category::cKakariko, Category::cSkulltulaHouse});
ItemLocation Kak_20GoldSkulltulaReward        = ItemLocation::Base       (0x50, 0x39, "Kak 20 Gold Skulltula Reward",         KAK_20_GOLD_SKULLTULA_REWARD,        {Category::cKakarikoVillage, Category::cKakariko, Category::cSkulltulaHouse});
ItemLocation Kak_30GoldSkulltulaReward        = ItemLocation::Base       (0x50, 0x46, "Kak 30 Gold Skulltula Reward",         KAK_30_GOLD_SKULLTULA_REWARD,        {Category::cKakarikoVillage, Category::cKakariko, Category::cSkulltulaHouse});
ItemLocation Kak_40GoldSkulltulaReward        = ItemLocation::Base       (0x50, 0x03, "Kak 40 Gold Skulltula Reward",         KAK_40_GOLD_SKULLTULA_REWARD,        {Category::cKakarikoVillage, Category::cKakariko, Category::cSkulltulaHouse});
ItemLocation Kak_50GoldSkulltulaReward        = ItemLocation::Base       (0x50, 0x3E, "Kak 50 Gold Skulltula Reward",         KAK_50_GOLD_SKULLTULA_REWARD,        {Category::cKakarikoVillage, Category::cKakariko, Category::cSkulltulaHouse});
ItemLocation Kak_ManOnRoof                    = ItemLocation::Base       (0x52, 0x3E, "Kak Man on Roof",                      KAK_MAN_ON_ROOF,                    {Category::cKakarikoVillage, Category::cKakariko,});
ItemLocation Kak_ShootingGalleryReward        = ItemLocation::Base       (0x42, 0x30, "Kak Shooting Gallery Reward",          KAK_SHOOTING_GALLERY_REWARD,        {Category::cKakarikoVillage, Category::cKakariko, Category::cMinigame});
ItemLocation Kak_AnjuAsAdult                  = ItemLocation::Base       (0x52, 0x1D, "Kak Anju as Adult",                    KAK_ANJU_AS_ADULT,                  {Category::cKakarikoVillage, Category::cKakariko,});
ItemLocation Kak_AnjuAsChild                  = ItemLocation::Base       (0x52, 0x0F, "Kak Anju as Child",                    KAK_ANJU_AS_CHILD,                  {Category::cKakarikoVillage, Category::cKakariko, Category::cMinigame});
ItemLocation Kak_ImpasHouseFreestandingPoH    = ItemLocation::Collectable(0x37, 0x01, "Kak Impas House Freestanding PoH",     KAK_IMPAS_HOUSE_FREESTANDING_POH,    {Category::cKakarikoVillage, Category::cKakariko,});
ItemLocation Kak_WindmillFreestandingPoH      = ItemLocation::Collectable(0x48, 0x01, "Kak Windmill Freestanding PoH",        KAK_WINDMILL_FREESTANDING_POH,      {Category::cKakarikoVillage, Category::cKakariko,});

//Graveyard
ItemLocation GY_ShieldGraveChest              = ItemLocation::Chest      (0x40, 0x00, "GY Shield Grave Chest",                GRAVEYARD_SHIELD_GRAVE_CHEST,              {Category::cGraveyard, Category::cKakariko,});
ItemLocation GY_HeartPieceGraveChest          = ItemLocation::Chest      (0x3F, 0x00, "GY Heart Piece Grave Chest",           GRAVEYARD_HEART_PIECE_GRAVE_CHEST,          {Category::cGraveyard, Category::cKakariko,});
ItemLocation GY_ComposersGraveChest           = ItemLocation::Chest      (0x41, 0x00, "GY Composers Grave Chest",             GRAVEYARD_COMPOSERS_GRAVE_CHEST,           {Category::cGraveyard, Category::cKakariko,});
ItemLocation GY_HookshotChest                 = ItemLocation::Chest      (0x48, 0x00, "GY Hookshot Chest",                    GRAVEYARD_HOOKSHOT_CHEST,                 {Category::cGraveyard, Category::cKakariko,});
ItemLocation GY_DampeRaceFreestandingPoH      = ItemLocation::Collectable(0x48, 0x07, "GY Dampe Race Freestanding PoH",       GRAVEYARD_DAMPE_RACE_FREESTANDING_POH,      {Category::cGraveyard, Category::cKakariko, Category::cMinigame});
ItemLocation GY_FreestandingPoH               = ItemLocation::Collectable(0x53, 0x04, "GY Freestanding PoH",                  GRAVEYARD_FREESTANDING_POH,               {Category::cGraveyard, Category::cKakariko,});
ItemLocation GY_DampeGravediggingTour         = ItemLocation::Collectable(0x53, 0x08, "GY Dampe Gravedigging Tour",           GRAVEYARD_DAMPE_GRAVEDIGGING_TOUR,         {Category::cGraveyard, Category::cKakariko,});

//Death Mountain
ItemLocation DMT_Chest                        = ItemLocation::Chest      (0x60, 0x01, "DMT Chest",                            DMT_CHEST,                        {Category::cDeathMountainTrail, Category::cDeathMountain,});
ItemLocation DMT_StormsGrottoChest            = ItemLocation::Chest      (0x3E, 0x17, "DMT Storms Grotto Chest",              DMT_STORMS_GROTTO_CHEST,            {Category::cDeathMountainTrail, Category::cDeathMountain, Category::cGrotto});
ItemLocation DMT_Biggoron                     = ItemLocation::Base       (0x60, 0x57, "DMT Biggoron",                         DMT_BIGGORON,                     {Category::cDeathMountainTrail, Category::cDeathMountain,});
ItemLocation DMT_FreestandingPoH              = ItemLocation::Collectable(0x60, 0x1E, "DMT Freestanding PoH",                 DMT_FREESTANDING_POH,              {Category::cDeathMountainTrail, Category::cDeathMountain,});

//Goron City
ItemLocation GC_MazeLeftChest                 = ItemLocation::Chest      (0x62, 0x00, "GC Maze Left Chest",                   GC_MAZE_LEFT_CHEST,                 {Category::cGoronCity,});
ItemLocation GC_MazeRightChest                = ItemLocation::Chest      (0x62, 0x01, "GC Maze Right Chest",                  GC_MAZE_RIGHT_CHEST,                {Category::cGoronCity,});
ItemLocation GC_MazeCenterChest               = ItemLocation::Chest      (0x62, 0x02, "GC Maze Center Chest",                 GC_MAZE_CENTER_CHEST,               {Category::cGoronCity,});
ItemLocation GC_RollingGoronAsChild           = ItemLocation::Base       (0x62, 0x34, "GC Rolling Goron as Child",            GC_ROLLING_GORON_AS_CHILD,           {Category::cGoronCity,});
ItemLocation GC_RollingGoronAsAdult           = ItemLocation::Base       (0x62, 0x2C, "GC Rolling Goron as Adult",            GC_ROLLING_GORON_AS_ADULT,           {Category::cGoronCity,});
ItemLocation GC_DaruniasJoy                   = ItemLocation::Base       (0x62, 0x54, "GC Darunias Joy",                      GC_DARUNIAS_JOY,                   {Category::cGoronCity,});
ItemLocation GC_PotFreestandingPoH            = ItemLocation::Collectable(0x62, 0x1F, "GC Pot Freestanding PoH",              GC_POT_FREESTANDING_POH,            {Category::cGoronCity,});
ItemLocation GC_DekuScrubGrottoLeft           = ItemLocation::GrottoScrub(0xFB, 0x30, "GC Deku Scrub Grotto Left",            GC_DEKU_SCRUB_GROTTO_LEFT,           {Category::cGoronCity, Category::cDekuScrub, Category::cGrotto});
ItemLocation GC_DekuScrubGrottoRight          = ItemLocation::GrottoScrub(0xFB, 0x37, "GC Deku Scrub Grotto Right",           GC_DEKU_SCRUB_GROTTO_RIGHT,          {Category::cGoronCity, Category::cDekuScrub, Category::cGrotto});
ItemLocation GC_DekuScrubGrottoCenter         = ItemLocation::GrottoScrub(0xFB, 0x33, "GC Deku Scrub Grotto Center",          GC_DEKU_SCRUB_GROTTO_CENTER,         {Category::cGoronCity, Category::cDekuScrub, Category::cGrotto});

//Death Mountain Crater
ItemLocation DMC_UpperGrottoChest             = ItemLocation::Chest      (0x3E, 0x1A, "DMC Upper Grotto Chest",               DMC_UPPER_GROTTO_CHEST,             {Category::cDeathMountainCrater, Category::cDeathMountain, Category::cGrotto});
ItemLocation DMC_WallFreestandingPoH          = ItemLocation::Collectable(0x61, 0x02, "DMC Wall Freestanding PoH",            DMC_WALL_FREESTANDING_POH,          {Category::cDeathMountainCrater, Category::cDeathMountain,});
ItemLocation DMC_VolcanoFreestandingPoH       = ItemLocation::Collectable(0x61, 0x08, "DMC Volcano Freestanding PoH",         DMC_VOLCANO_FREESTANDING_POH,       {Category::cDeathMountainCrater, Category::cDeathMountain,});
ItemLocation DMC_DekuScrub                    = ItemLocation::Base       (0x61, 0x37, "DMC Deku Scrub",                       DMC_DEKU_SCRUB,                    {Category::cDeathMountainCrater, Category::cDeathMountain, Category::cDekuScrub});
ItemLocation DMC_DekuScrubGrottoLeft          = ItemLocation::GrottoScrub(0xF9, 0x30, "DMC Deku Scrub Grotto Left",           DMC_DEKU_SCRUB_GROTTO_LEFT,          {Category::cDeathMountainCrater, Category::cDeathMountain, Category::cDekuScrub, Category::cGrotto});
ItemLocation DMC_DekuScrubGrottoRight         = ItemLocation::GrottoScrub(0xF9, 0x37, "DMC Deku Scrub Grotto Right",          DMC_DEKU_SCRUB_GROTTO_RIGHT,         {Category::cDeathMountainCrater, Category::cDeathMountain, Category::cDekuScrub, Category::cGrotto});
ItemLocation DMC_DekuScrubGrottoCenter        = ItemLocation::GrottoScrub(0xF9, 0x33, "DMC Deku Scrub Grotto Center",         DMC_DEKU_SCRUB_GROTTO_CENTER,        {Category::cDeathMountainCrater, Category::cDeathMountain, Category::cDekuScrub, Category::cGrotto});

//Zoras River
ItemLocation ZR_OpenGrottoChest               = ItemLocation::Chest      (0x3E, 0x09, "ZR Open Grotto Chest",                 ZR_OPEN_GROTTO_CHEST,               {Category::cZorasRiver, Category::cGrotto,});
ItemLocation ZR_MagicBeanSalesman             = ItemLocation::Base       (0x54, 0x16, "ZR Magic Bean Salesman",               ZR_MAGIC_BEAN_SALESMAN,             {Category::cZorasRiver,});
ItemLocation ZR_FrogsOcarinaGame              = ItemLocation::Base       (0x54, 0x76, "ZR Frogs Ocarina Game",                ZR_FROGS_OCARINA_GAME,              {Category::cZorasRiver,});
ItemLocation ZR_FrogsInTheRain                = ItemLocation::Base       (0x54, 0x3E, "ZR Frogs in the Rain",                 ZR_FROGS_IN_THE_RAIN,                {Category::cZorasRiver, Category::cMinigame,});
ItemLocation ZR_NearOpenGrottoFreestandingPoH = ItemLocation::Collectable(0x54, 0x04, "ZR Near Open Grotto Freestanding PoH", ZR_NEAR_OPEN_GROTTO_FREESTANDING_POH, {Category::cZorasRiver,});
ItemLocation ZR_NearDomainFreestandingPoH     = ItemLocation::Collectable(0x54, 0x0B, "ZR Near Domain Freestanding PoH",      ZR_NEAR_DOMAIN_FREESTANDING_POH,     {Category::cZorasRiver,});
ItemLocation ZR_DekuScrubGrottoRear           = ItemLocation::GrottoScrub(0xEB, 0x39, "ZR Deku Scrub Grotto Rear",            ZR_DEKU_SCRUB_GROTTO_REAR,           {Category::cZorasRiver, Category::cDekuScrub, Category::cGrotto});
ItemLocation ZR_DekuScrubGrottoFront          = ItemLocation::GrottoScrub(0xEB, 0x3A, "ZR Deku Scrub Grotto Front",           ZR_DEKU_SCRUB_GROTTO_FRONT,          {Category::cZorasRiver, Category::cDekuScrub, Category::cGrotto});

//Zoras Domain
ItemLocation ZD_Chest                         = ItemLocation::Chest      (0x58, 0x00, "ZD Chest",                             ZD_CHEST,                         {Category::cZorasDomain,});
ItemLocation ZD_DivingMinigame                = ItemLocation::Base       (0x58, 0x37, "ZD Diving Minigame",                   ZD_DIVING_MINIGAME,                {Category::cZorasDomain, Category::cMinigame,});
ItemLocation ZD_KingZoraThawed                = ItemLocation::Base       (0x58, 0x2D, "ZD King Zora Thawed",                  ZD_KING_ZORA_THAWED,                {Category::cZorasDomain,});

//Zoras Fountain
ItemLocation ZF_IcebergFreestandingPoH        = ItemLocation::Collectable(0x59, 0x01, "ZF Iceberg Freestanding PoH",          ZF_ICEBERG_FREESTANDING_POH,        {Category::cZorasFountain,});
ItemLocation ZF_BottomFreestandingPoH         = ItemLocation::Collectable(0x59, 0x14, "ZF Bottom Freestanding PoH",           ZF_BOTTOM_FREESTANDING_POH,         {Category::cZorasFountain,});

//Lon Lon Ranch
ItemLocation LLR_TalonsChickens               = ItemLocation::Base       (0x4C, 0x14, "LLR Talons Chickens",                  LLR_TALONS_CHICKENS,               {Category::cLonLonRanch, Category::cMinigame});
ItemLocation LLR_FreestandingPoH              = ItemLocation::Collectable(0x4C, 0x01, "LLR Freestanding PoH",                 LLR_FREESTANDING_POH,              {Category::cLonLonRanch,});
ItemLocation LLR_DekuScrubGrottoLeft          = ItemLocation::GrottoScrub(0xFC, 0x30, "LLR Deku Scrub Grotto Left",           LLR_DEKU_SCRUB_GROTTO_LEFT,          {Category::cLonLonRanch, Category::cDekuScrub, Category::cGrotto});
ItemLocation LLR_DekuScrubGrottoRight         = ItemLocation::GrottoScrub(0xFC, 0x37, "LLR Deku Scrub Grotto Right",          LLR_DEKU_SCRUB_GROTTO_RIGHT,         {Category::cLonLonRanch, Category::cDekuScrub, Category::cGrotto});
ItemLocation LLR_DekuScrubGrottoCenter        = ItemLocation::GrottoScrub(0xFC, 0x33, "LLR Deku Scrub Grotto Center",         LLR_DEKU_SCRUB_GROTTO_CENTER,        {Category::cLonLonRanch, Category::cDekuScrub, Category::cGrotto});

/*-------------------
   --- DUNGEONS ---
  -------------------*/

//Deku Tree Vanilla
ItemLocation DekuTree_MapChest                                = ItemLocation::Chest      (0x00, 0x03, "Deku Tree Map Chest",                                DEKU_TREE_MAP_CHEST,                  {Category::cDekuTree, Category::cVanillaMap,});
ItemLocation DekuTree_CompassChest                            = ItemLocation::Chest      (0x00, 0x02, "Deku Tree Compass Chest",                            DEKU_TREE_COMPASS_CHEST,              {Category::cDekuTree, Category::cVanillaCompass,});
ItemLocation DekuTree_CompassRoomSideChest                    = ItemLocation::Chest      (0x00, 0x06, "Deku Tree Compass Room Side Chest",                  DEKU_TREE_COMPASS_ROOM_SIDE_CHEST,      {Category::cDekuTree,});
ItemLocation DekuTree_BasementChest                           = ItemLocation::Chest      (0x00, 0x04, "Deku Tree Basement Chest",                           DEKU_TREE_BASEMENT_CHEST,             {Category::cDekuTree,});
ItemLocation DekuTree_SlingshotChest                          = ItemLocation::Chest      (0x00, 0x01, "Deku Tree Slingshot Chest",                          DEKU_TREE_SLINGSHOT_CHEST,            {Category::cDekuTree,});
ItemLocation DekuTree_SlingshotRoomSideChest                  = ItemLocation::Chest      (0x00, 0x05, "Deku Tree Slingshot Room Side Chest",                DEKU_TREE_SLINGSHOT_ROOM_SIDE_CHEST,    {Category::cDekuTree,});
//Deku Tree MQ
ItemLocation DekuTree_MQ_MapChest                             = ItemLocation::Chest      (0x00, 0x03, "Deku Tree MQ Map Chest",                             DEKU_TREE_MQ_MAP_CHEST,               {Category::cDekuTree, Category::cVanillaMap,});
ItemLocation DekuTree_MQ_CompassChest                         = ItemLocation::Chest      (0x00, 0x01, "Deku Tree MQ Compass Chest",                         DEKU_TREE_MQ_COMPASS_CHEST,           {Category::cDekuTree, Category::cVanillaCompass,});
ItemLocation DekuTree_MQ_SlingshotChest                       = ItemLocation::Chest      (0x00, 0x06, "Deku Tree MQ Slingshot Chest",                       DEKU_TREE_MQ_SLINGSHOT_CHEST,         {Category::cDekuTree,});
ItemLocation DekuTree_MQ_SlingshotRoomBackChest               = ItemLocation::Chest      (0x00, 0x02, "Deku Tree MQ Slingshot Room Back Chest",             DEKU_TREE_MQ_SLINGSHOT_ROOM_BACK_CHEST, {Category::cDekuTree,});
ItemLocation DekuTree_MQ_BasementChest                        = ItemLocation::Chest      (0x00, 0x04, "Deku Tree MQ Basement Chest",                        DEKU_TREE_MQ_BASEMENT_CHEST,          {Category::cDekuTree,});
ItemLocation DekuTree_MQ_BeforeSpinningLogChest               = ItemLocation::Chest      (0x00, 0x05, "Deku Tree MQ Before Spinning Log Chest",             DEKU_TREE_MQ_BEFORE_SPINNING_LOG_CHEST, {Category::cDekuTree,});
ItemLocation DekuTree_MQ_AfterSpinningLogChest                = ItemLocation::Chest      (0x00, 0x00, "Deku Tree MQ After Spinning Log Chest",              DEKU_TREE_MQ_AFTER_SPINNING_LOG_CHEST,  {Category::cDekuTree,});
ItemLocation DekuTree_MQ_DekuScrub                            = ItemLocation::Base       (0x00, 0x34, "Deku Tree MQ Deku Scrub",                            DEKU_TREE_MQ_DEKU_SCRUB,              {Category::cDekuTree,});

//Dodongos Cavern Shared
ItemLocation DodongosCavern_BossRoomChest                     = ItemLocation::Chest      (0x12, 0x00, "Dodongos Cavern Boss Room Chest",                    DODONGOS_CAVERN_BOSS_ROOM_CHEST,                 {Category::cDodongosCavern,});
//Dodongos Cavern Vanilla
ItemLocation DodongosCavern_MapChest                          = ItemLocation::Chest      (0x01, 0x08, "Dodongos Cavern Map Chest",                          DODONGOS_CAVERN_MAP_CHEST,                      {Category::cDodongosCavern, Category::cVanillaMap,});
ItemLocation DodongosCavern_CompassChest                      = ItemLocation::Chest      (0x01, 0x05, "Dodongos Cavern Compass Chest",                      DODONGOS_CAVERN_COMPASS_CHEST,                  {Category::cDodongosCavern, Category::cVanillaCompass,});
ItemLocation DodongosCavern_BombFlowerPlatformChest           = ItemLocation::Chest      (0x01, 0x06, "Dodongos Cavern Bomb Flower Platform Chest",         DODONGOS_CAVERN_BOMB_FLOWER_PLATFORM_CHEST,       {Category::cDodongosCavern,});
ItemLocation DodongosCavern_BombBagChest                      = ItemLocation::Chest      (0x01, 0x04, "Dodongos Cavern Bomb Bag Chest",                     DODONGOS_CAVERN_BOMB_BAG_CHEST,                  {Category::cDodongosCavern,});
ItemLocation DodongosCavern_EndOfBridgeChest                  = ItemLocation::Chest      (0x01, 0x0A, "Dodongos Cavern End Of Bridge Chest",                DODONGOS_CAVERN_END_OF_BRIDGE_CHEST,              {Category::cDodongosCavern,});
ItemLocation DodongosCavern_DekuScrubNearBombBagLeft          = ItemLocation::Base       (0x01, 0x30, "Dodongos Cavern Deku Scrub Near Bomb Bag Left",      DODONGOS_CAVERN_DEKU_SCRUB_NEAR_BOMB_BAG_LEFT,      {Category::cDodongosCavern, Category::cDekuScrub,});
ItemLocation DodongosCavern_DekuScrubSideRoomNearDodongos     = ItemLocation::Base       (0x01, 0x31, "Dodongos Cavern Deku Scrub Side Room Near Dodongos", DODONGOS_CAVERN_DEKU_SCRUB_SIDE_ROOM_NEAR_DODONGOS, {Category::cDodongosCavern, Category::cDekuScrub,});
ItemLocation DodongosCavern_DekuScrubNearBombBagRight         = ItemLocation::Base       (0x01, 0x33, "Dodongos Cavern Deku Scrub Near Bomb Bag Right",     DODONGOS_CAVERN_DEKU_SCRUB_NEAR_BOMB_BAG_RIGHT,     {Category::cDodongosCavern, Category::cDekuScrub,});
ItemLocation DodongosCavern_DekuScrubLobby                    = ItemLocation::Base       (0x01, 0x34, "Dodongos Cavern Deku Scrub Lobby",                   DODONGOS_CAVERN_DEKU_SCRUB_LOBBY,                {Category::cDodongosCavern, Category::cDekuScrub,});
//Dodongos Cavern MQ
ItemLocation DodongosCavern_MQ_MapChest                       = ItemLocation::Chest      (0x01, 0x00, "Dodongos Cavern MQ Map Chest",                       DODONGOS_CAVERN_MQ_MAP_CHEST,                   {Category::cDodongosCavern, Category::cVanillaMap,});
ItemLocation DodongosCavern_MQ_BombBagChest                   = ItemLocation::Chest      (0x01, 0x04, "Dodongos Cavern MQ Bomb Bag Chest",                  DODONGOS_CAVERN_MQ_BOMB_BAG_CHEST,               {Category::cDodongosCavern,});
ItemLocation DodongosCavern_MQ_CompassChest                   = ItemLocation::Chest      (0x01, 0x05, "Dodongos Cavern MQ Compass Chest",                   DODONGOS_CAVERN_MQ_COMPASS_CHEST,               {Category::cDodongosCavern, Category::cVanillaCompass,});
ItemLocation DodongosCavern_MQ_LarvaeRoomChest                = ItemLocation::Chest      (0x01, 0x02, "Dodongos Cavern MQ Larvae Room Chest",               DODONGOS_CAVERN_MQ_LARVAE_ROOM_CHEST,            {Category::cDodongosCavern,});
ItemLocation DodongosCavern_MQ_TorchPuzzleRoomChest           = ItemLocation::Chest      (0x01, 0x03, "Dodongos Cavern MQ Torch Puzzle Room Chest",         DODONGOS_CAVERN_MQ_TORCH_PUZZLE_ROOM_CHEST,       {Category::cDodongosCavern,});
ItemLocation DodongosCavern_MQ_UnderGraveChest                = ItemLocation::Chest      (0x01, 0x01, "Dodongos Cavern MQ Under Grave Chest",               DODONGOS_CAVERN_MQ_UNDER_GRAVE_CHEST,            {Category::cDodongosCavern,});
ItemLocation DodongosCavern_MQ_DekuScrubLobbyRear             = ItemLocation::Base       (0x01, 0x31, "Dodongos Cavern Deku Scrub Lobby Rear",              DODONGOS_CAVERN_MQ_DEKU_SCRUB_LOBBY_REAR,         {Category::cDodongosCavern, Category::cDekuScrub,});
ItemLocation DodongosCavern_MQ_DekuScrubLobbyFront            = ItemLocation::Base       (0x01, 0x33, "Dodongos Cavern Deku Scrub Lobby Front",             DODONGOS_CAVERN_MQ_DEKU_SCRUB_LOBBY_FRONT,        {Category::cDodongosCavern, Category::cDekuScrub,});
ItemLocation DodongosCavern_MQ_DekuScrubStaircase             = ItemLocation::Base       (0x01, 0x34, "Dodongos Cavern Deku Scrub Staircase",               DODONGOS_CAVERN_MQ_DEKU_SCRUB_STAIRCASE,         {Category::cDodongosCavern, Category::cDekuScrub,});
ItemLocation DodongosCavern_MQ_DekuScrubSideRoomNearLowerLizalfos = ItemLocation::Base   (0x01, 0x39, "Dodongos Cavern Deku Scrub Side Room Near Lower Lizalfos",DODONGOS_CAVERN_MQ_DEKU_SCRUB_SIDE_ROOM_NEAR_LOWER_LIZALFOS,{Category::cDodongosCavern, Category::cDekuScrub,});

//Jabu Jabus Belly Vanilla
ItemLocation JabuJabusBelly_MapChest                          = ItemLocation::Chest      (0x02, 0x02, "Jabu Jabus Belly Map Chest",                         JABU_JABUS_BELLY_MAP_CHEST,                     {Category::cJabuJabusBelly, Category::cVanillaMap,});
ItemLocation JabuJabusBelly_CompassChest                      = ItemLocation::Chest      (0x02, 0x04, "Jabu Jabus Belly Compass Chest",                     JABU_JABUS_BELLY_COMPASS_CHEST,                 {Category::cJabuJabusBelly, Category::cVanillaCompass,});
ItemLocation JabuJabusBelly_BoomerangChest                    = ItemLocation::Chest      (0x02, 0x01, "Jabu Jabus Belly Boomerang Chest",                   JABU_JABUS_BELLY_BOOMERANG_CHEST,               {Category::cJabuJabusBelly,});
ItemLocation JabuJabusBelly_DekuScrub                         = ItemLocation::Base       (0x02, 0x30, "Jabu Jabus Belly Deku Scrub",                        JABU_JABUS_BELLY_DEKU_SCRUB,                    {Category::cJabuJabusBelly, Category::cDekuScrub,});
//Jabu Jabus Belly MQ
ItemLocation JabuJabusBelly_MQ_FirstRoomSideChest             = ItemLocation::Chest      (0x02, 0x05, "Jabu Jabus Belly MQ First Room Side Chest",          JABU_JABUS_BELLY_MQ_FIRST_ROOM_SIDE_CHEST,        {Category::cJabuJabusBelly,});
ItemLocation JabuJabusBelly_MQ_MapChest                       = ItemLocation::Chest      (0x02, 0x03, "Jabu Jabus Belly MQ Map Chest",                      JABU_JABUS_BELLY_MQ_MAP_CHEST,                  {Category::cJabuJabusBelly, Category::cVanillaMap,});
ItemLocation JabuJabusBelly_MQ_SecondRoomLowerChest           = ItemLocation::Chest      (0x02, 0x02, "Jabu Jabus Belly MQ Second Room Lower Chest",        JABU_JABUS_BELLY_MQ_SECOND_ROOM_LOWER_CHEST,      {Category::cJabuJabusBelly,});
ItemLocation JabuJabusBelly_MQ_CompassChest                   = ItemLocation::Chest      (0x02, 0x00, "Jabu Jabus Belly MQ Compass Chest",                  JABU_JABUS_BELLY_MQ_COMPASS_CHEST,              {Category::cJabuJabusBelly, Category::cVanillaCompass,});
ItemLocation JabuJabusBelly_MQ_SecondRoomUpperChest           = ItemLocation::Chest      (0x02, 0x07, "Jabu Jabus Belly MQ Second Room Upper Chest",        JABU_JABUS_BELLY_MQ_SECOND_ROOM_UPPER_CHEST,      {Category::cJabuJabusBelly,});
ItemLocation JabuJabusBelly_MQ_BasementNearSwitchesChest      = ItemLocation::Chest      (0x02, 0x08, "Jabu Jabus Belly MQ Basement Near Switches Chest",   JABU_JABUS_BELLY_MQ_BASEMENT_NEAR_SWITCHES_CHEST, {Category::cJabuJabusBelly,});
ItemLocation JabuJabusBelly_MQ_BasementNearVinesChest         = ItemLocation::Chest      (0x02, 0x04, "Jabu Jabus Belly MQ Basement Near Vines Chest",      JABU_JABUS_BELLY_MQ_BASEMENT_NEAR_VINES_CHEST,    {Category::cJabuJabusBelly,});
ItemLocation JabuJabusBelly_MQ_NearBossChest                  = ItemLocation::Chest      (0x02, 0x0A, "Jabu Jabus Belly MQ Near Boss Chest",                JABU_JABUS_BELLY_MQ_NEAR_BOSS_CHEST,             {Category::cJabuJabusBelly,});
ItemLocation JabuJabusBelly_MQ_FallingLikeLikeRoomChest       = ItemLocation::Chest      (0x02, 0x09, "Jabu Jabus Belly MQ Falling Like Like Room Chest",   JABU_JABUS_BELLY_MQ_FALLING_LIKE_LIKE_ROOM_CHEST,  {Category::cJabuJabusBelly,});
ItemLocation JabuJabusBelly_MQ_BoomerangRoomSmallChest        = ItemLocation::Chest      (0x02, 0x01, "Jabu Jabus Belly MQ Boomerang Room Small Chest",     JABU_JABUS_BELLY_MQ_BOOMERANG_ROOM_SMALL_CHEST,   {Category::cJabuJabusBelly,});
ItemLocation JabuJabusBelly_MQ_BoomerangChest                 = ItemLocation::Chest      (0x02, 0x06, "Jabu Jabus Belly MQ Boomerang Chest",                JABU_JABUS_BELLY_MQ_BOOMERANG_CHEST,            {Category::cJabuJabusBelly,});
//COW

//Forest Temple Vanilla
ItemLocation ForestTemple_FirstRoomChest                      = ItemLocation::Chest      (0x03, 0x03, "Forest Temple First Room Chest",                     FOREST_TEMPLE_FIRST_ROOM_CHEST,             {Category::cForestTemple, Category::cVanillaSmallKey});
ItemLocation ForestTemple_FirstStalfosChest                   = ItemLocation::Chest      (0x03, 0x00, "Forest Temple First Stalfos Chest",                  FOREST_TEMPLE_FIRST_STALFOS_CHEST,          {Category::cForestTemple, Category::cVanillaSmallKey});
ItemLocation ForestTemple_RaisedIslandCourtyardChest          = ItemLocation::Chest      (0x03, 0x05, "Forest Temple Raised Island Courtyard Chest",        FOREST_TEMPLE_RAISED_ISLAND_COURTYARD_CHEST, {Category::cForestTemple,});
ItemLocation ForestTemple_MapChest                            = ItemLocation::Chest      (0x03, 0x01, "Forest Temple Map Chest",                            FOREST_TEMPLE_MAP_CHEST,                   {Category::cForestTemple, Category::cVanillaMap,});
ItemLocation ForestTemple_WellChest                           = ItemLocation::Chest      (0x03, 0x09, "Forest Temple Well Chest",                           FOREST_TEMPLE_WELL_CHEST,                  {Category::cForestTemple, Category::cVanillaSmallKey});
ItemLocation ForestTemple_FallingCeilingRoomChest             = ItemLocation::Chest      (0x03, 0x07, "Forest Temple Falling Ceiling Room Chest",           FOREST_TEMPLE_FALLING_CEILING_ROOM_CHEST,    {Category::cForestTemple,});
ItemLocation ForestTemple_EyeSwitchChest                      = ItemLocation::Chest      (0x03, 0x04, "Forest Temple Eye Switch Chest",                     FOREST_TEMPLE_EYE_SWITCH_CHEST,             {Category::cForestTemple,});
ItemLocation ForestTemple_BossKeyChest                        = ItemLocation::Chest      (0x03, 0x0E, "Forest Temple Boss Key Chest",                       FOREST_TEMPLE_BOSS_KEY_CHEST,               {Category::cForestTemple, Category::cVanillaBossKey});
ItemLocation ForestTemple_FloormasterChest                    = ItemLocation::Chest      (0x03, 0x02, "Forest Temple Floormaster Chest",                    FOREST_TEMPLE_FLOORMASTER_CHEST,           {Category::cForestTemple, Category::cVanillaSmallKey});
ItemLocation ForestTemple_BowChest                            = ItemLocation::Chest      (0x03, 0x0C, "Forest Temple Bow Chest",                            FOREST_TEMPLE_BOW_CHEST,                   {Category::cForestTemple,});
ItemLocation ForestTemple_RedPoeChest                         = ItemLocation::Chest      (0x03, 0x0D, "Forest Temple Red Poe Chest",                        FOREST_TEMPLE_RED_POE_CHEST,                {Category::cForestTemple, Category::cVanillaSmallKey});
ItemLocation ForestTemple_BluePoeChest                        = ItemLocation::Chest      (0x03, 0x0F, "Forest Temple Blue Poe Chest",                       FOREST_TEMPLE_BLUE_POE_CHEST,               {Category::cForestTemple, Category::cVanillaCompass,});
ItemLocation ForestTemple_BasementChest                       = ItemLocation::Chest      (0x03, 0x0B, "Forest Temple Basement Chest",                       FOREST_TEMPLE_BASEMENT_CHEST,              {Category::cForestTemple,});
//Forest Temple MQ
ItemLocation ForestTemple_MQ_FirstRoomChest                   = ItemLocation::Chest      (0x03, 0x03, "Forest Temple MQ First Room Chest",                  FOREST_TEMPLE_MQ_FIRST_ROOM_CHEST,          {Category::cForestTemple, Category::cVanillaSmallKey});
ItemLocation ForestTemple_MQ_WolfosChest                      = ItemLocation::Chest      (0x03, 0x00, "Forest Temple MQ Wolfos Chest",                      FOREST_TEMPLE_MQ_WOLFOS_CHEST,             {Category::cForestTemple, Category::cVanillaSmallKey});
ItemLocation ForestTemple_MQ_BowChest                         = ItemLocation::Chest      (0x03, 0x0C, "Forest Temple MQ Bow Chest",                         FOREST_TEMPLE_MQ_BOW_CHEST,                {Category::cForestTemple,});
ItemLocation ForestTemple_MQ_RaisedIslandCourtyardLowerChest  = ItemLocation::Chest      (0x03, 0x01, "Forest Temple MQ Raised Island Courtyard Lower Chest", FOREST_TEMPLE_MQ_RAISED_ISLAND_COURTYARD_LOWER_CHEST, {Category::cForestTemple, Category::cVanillaSmallKey});
ItemLocation ForestTemple_MQ_RaisedIslandCourtyardUpperChest  = ItemLocation::Chest      (0x03, 0x05, "Forest Temple MQ Raised Island Courtyard Upper Chest", FOREST_TEMPLE_MQ_RAISED_ISLAND_COURTYARD_UPPER_CHEST, {Category::cForestTemple, Category::cVanillaSmallKey});
ItemLocation ForestTemple_MQ_WellChest                        = ItemLocation::Chest      (0x03, 0x09, "Forest Temple MQ Well Chest",                        FOREST_TEMPLE_MQ_WELL_CHEST,               {Category::cForestTemple, Category::cVanillaSmallKey});
ItemLocation ForestTemple_MQ_MapChest                         = ItemLocation::Chest      (0x03, 0x0D, "Forest Temple MQ Map Chest",                         FOREST_TEMPLE_MQ_MAP_CHEST,                {Category::cForestTemple, Category::cVanillaMap,});
ItemLocation ForestTemple_MQ_CompassChest                     = ItemLocation::Chest      (0x03, 0x0F, "Forest Temple MQ Compass Chest",                     FOREST_TEMPLE_MQ_COMPASS_CHEST,            {Category::cForestTemple, Category::cVanillaCompass,});
ItemLocation ForestTemple_MQ_FallingCeilingRoomChest          = ItemLocation::Chest      (0x03, 0x06, "Forest Temple MQ Falling Ceiling Room Chest",        FOREST_TEMPLE_MQ_FALLING_CEILING_ROOM_CHEST, {Category::cForestTemple,});
ItemLocation ForestTemple_MQ_BasementChest                    = ItemLocation::Chest      (0x03, 0x0B, "Forest Temple MQ Basement Chest",                    FOREST_TEMPLE_MQ_BASEMENT_CHEST,           {Category::cForestTemple,});
ItemLocation ForestTemple_MQ_RedeadChest                      = ItemLocation::Chest      (0x03, 0x02, "Forest Temple MQ Redead Chest",                      FOREST_TEMPLE_MQ_REDEAD_CHEST,             {Category::cForestTemple, Category::cVanillaSmallKey});
ItemLocation ForestTemple_MQ_BossKeyChest                     = ItemLocation::Chest      (0x03, 0x0E, "Forest Temple MQ Boss Key Chest",                    FOREST_TEMPLE_MQ_BOSS_KEY_CHEST,            {Category::cForestTemple, Category::cVanillaBossKey});

//Fire Temple Vanilla
ItemLocation FireTemple_NearBossChest                         = ItemLocation::Chest      (0x04, 0x01, "Fire Temple Near Boss Chest",                        FIRE_TEMPLE_NEAR_BOSS_CHEST,                 {Category::cFireTemple, Category::cVanillaSmallKey});
ItemLocation FireTemple_FlareDancerChest                      = ItemLocation::Chest      (0x04, 0x00, "Fire Temple Flare Dancer Chest",                     FIRE_TEMPLE_FLARE_DANCER_CHEST,              {Category::cFireTemple,});
ItemLocation FireTemple_BossKeyChest                          = ItemLocation::Chest      (0x04, 0x0C, "Fire Temple Boss Key Chest",                         FIRE_TEMPLE_BOSS_KEY_CHEST,                  {Category::cFireTemple, Category::cVanillaBossKey});
ItemLocation FireTemple_BigLavaRoomBlockedDoorChest           = ItemLocation::Chest      (0x04, 0x02, "Fire Temple Big Lava Room Blocked Door Chest",       FIRE_TEMPLE_BIG_LAVA_ROOM_BLOCKED_DOOR_CHEST,   {Category::cFireTemple, Category::cVanillaSmallKey});
ItemLocation FireTemple_BigLavaRoomLowerOpenDoorChest         = ItemLocation::Chest      (0x04, 0x04, "Fire Temple Big Lava Room Lower Open Door Chest",    FIRE_TEMPLE_BIG_LAVA_ROOM_LOWER_OPEN_DOOR_CHEST, {Category::cFireTemple, Category::cVanillaSmallKey});
ItemLocation FireTemple_BoulderMazeLowerChest                 = ItemLocation::Chest      (0x04, 0x03, "Fire Temple Boulder Maze Lower Chest",               FIRE_TEMPLE_BOULDER_MAZE_LOWER_CHEST,         {Category::cFireTemple, Category::cVanillaSmallKey});
ItemLocation FireTemple_BoulderMazeUpperChest                 = ItemLocation::Chest      (0x04, 0x06, "Fire Temple Boulder Maze Upper Chest",               FIRE_TEMPLE_BOULDER_MAZE_UPPER_CHEST,         {Category::cFireTemple, Category::cVanillaSmallKey});
ItemLocation FireTemple_BoulderMazeSideRoomChest              = ItemLocation::Chest      (0x04, 0x08, "Fire Temple Boulder Maze Side Room Chest",           FIRE_TEMPLE_BOULDER_MAZE_SIDE_ROOM_CHEST,      {Category::cFireTemple, Category::cVanillaSmallKey});
ItemLocation FireTemple_BoulderMazeShortcutChest              = ItemLocation::Chest      (0x04, 0x0B, "Fire Temple Boulder Maze Shortcut Chest",            FIRE_TEMPLE_BOULDER_MAZE_SHORTCUT_CHEST,      {Category::cFireTemple, Category::cVanillaSmallKey});
ItemLocation FireTemple_ScarecrowChest                        = ItemLocation::Chest      (0x04, 0x0D, "Fire Temple Scarecrow Chest",                        FIRE_TEMPLE_SCARECROW_CHEST,                {Category::cFireTemple,});
ItemLocation FireTemple_MapChest                              = ItemLocation::Chest      (0x04, 0x0A, "Fire Temple Map Chest",                              FIRE_TEMPLE_MAP_CHEST,                      {Category::cFireTemple, Category::cVanillaMap,});
ItemLocation FireTemple_CompassChest                          = ItemLocation::Chest      (0x04, 0x07, "Fire Temple Compass Chest",                          FIRE_TEMPLE_COMPASS_CHEST,                  {Category::cFireTemple, Category::cVanillaCompass,});
ItemLocation FireTemple_HighestGoronChest                     = ItemLocation::Chest      (0x04, 0x09, "Fire Temple Highest Goron Chest",                    FIRE_TEMPLE_HIGHEST_GORON_CHEST,             {Category::cFireTemple, Category::cVanillaSmallKey});
ItemLocation FireTemple_MegatonHammerChest                    = ItemLocation::Chest      (0x04, 0x05, "Fire Temple Megaton Hammer Chest",                   FIRE_TEMPLE_MEGATON_HAMMER_CHEST,            {Category::cFireTemple,});
//Fire Temple MQ
ItemLocation FireTemple_MQ_NearBossChest                      = ItemLocation::Chest      (0x04, 0x07, "Fire Temple MQ Near Boss Chest",                     FIRE_TEMPLE_MQ_NEAR_BOSS_CHEST,               {Category::cFireTemple, Category::cVanillaSmallKey});
ItemLocation FireTemple_MQ_MegatonHammerChest                 = ItemLocation::Chest      (0x04, 0x00, "Fire Temple MQ Megaton Hammer Chest",                FIRE_TEMPLE_MQ_MEGATON_HAMMER_CHEST,          {Category::cFireTemple,});
ItemLocation FireTemple_MQ_CompassChest                       = ItemLocation::Chest      (0x04, 0x0B, "Fire Temple MQ Compass Chest",                       FIRE_TEMPLE_MQ_COMPASS_CHEST,                {Category::cFireTemple, Category::cVanillaCompass,});
ItemLocation FireTemple_MQ_LizalfosMazeLowerChest             = ItemLocation::Chest      (0x04, 0x03, "Fire Temple MQ Lizalfos Maze Lower Chest",           FIRE_TEMPLE_MQ_LIZALFOS_MAZE_LOWER_CHEST,      {Category::cFireTemple,});
ItemLocation FireTemple_MQ_LizalfosMazeUpperChest             = ItemLocation::Chest      (0x04, 0x06, "Fire Temple MQ Lizalfos Maze Upper Chest",           FIRE_TEMPLE_MQ_LIZALFOS_MAZE_UPPER_CHEST,      {Category::cFireTemple,});
ItemLocation FireTemple_MQ_ChestOnFire                        = ItemLocation::Chest      (0x04, 0x05, "Fire Temple MQ Chest on Fire",                       FIRE_TEMPLE_MQ_CHEST_ON_FIRE,                 {Category::cFireTemple, Category::cVanillaSmallKey});
ItemLocation FireTemple_MQ_MapRoomSideChest                   = ItemLocation::Chest      (0x04, 0x02, "Fire Temple MQ Map Room Side Chest",                 FIRE_TEMPLE_MQ_MAP_ROOM_SIDE_CHEST,            {Category::cFireTemple,});
ItemLocation FireTemple_MQ_MapChest                           = ItemLocation::Chest      (0x04, 0x0C, "Fire Temple MQ Map Chest",                           FIRE_TEMPLE_MQ_MAP_CHEST,                    {Category::cFireTemple, Category::cVanillaMap,});
ItemLocation FireTemple_MQ_BossKeyChest                       = ItemLocation::Chest      (0x04, 0x04, "Fire Temple MQ Boss Key Chest",                      FIRE_TEMPLE_MQ_BOSS_KEY_CHEST,                {Category::cFireTemple, Category::cVanillaBossKey});
ItemLocation FireTemple_MQ_BigLavaRoomBlockedDoorChest        = ItemLocation::Chest      (0x04, 0x01, "Fire Temple MQ Big Lava Room Blocked Door Chest",    FIRE_TEMPLE_MQ_BIG_LAVA_ROOM_BLOCKED_DOOR_CHEST, {Category::cFireTemple, Category::cVanillaSmallKey});
ItemLocation FireTemple_MQ_LizalfosMazeSideRoomChest          = ItemLocation::Chest      (0x04, 0x08, "Fire Temple MQ Lizalfos Maze Side Room Chest",       FIRE_TEMPLE_MQ_LIZALFOS_MAZE_SIDE_ROOM_CHEST,   {Category::cFireTemple, Category::cVanillaSmallKey});
ItemLocation FireTemple_MQ_FreestandingKey                    = ItemLocation::Collectable(0x04, 0x1C, "Fire Temple MQ Freestanding Key",                    FIRE_TEMPLE_MQ_FREESTANDING_KEY,             {Category::cFireTemple, Category::cVanillaSmallKey});

//Water Temple Vanilla
ItemLocation WaterTemple_MapChest                             = ItemLocation::Chest      (0x05, 0x02, "Water Temple Map Chest",                             WATER_TEMPLE_MAP_CHEST,              {Category::cWaterTemple, Category::cVanillaMap,});
ItemLocation WaterTemple_CompassChest                         = ItemLocation::Chest      (0x05, 0x09, "Water Temple Compass Chest",                         WATER_TEMPLE_COMPASS_CHEST,          {Category::cWaterTemple, Category::cVanillaCompass,});
ItemLocation WaterTemple_TorchesChest                         = ItemLocation::Chest      (0x05, 0x01, "Water Temple Torches Chest",                         WATER_TEMPLE_TORCHES_CHEST,          {Category::cWaterTemple, Category::cVanillaSmallKey});
ItemLocation WaterTemple_DragonChest                          = ItemLocation::Chest      (0x05, 0x0A, "Water Temple Dragon Chest",                          WATER_TEMPLE_DRAGON_CHEST,           {Category::cWaterTemple, Category::cVanillaSmallKey});
ItemLocation WaterTemple_CentralBowTargetChest                = ItemLocation::Chest      (0x05, 0x08, "Water Temple Central Bow Target Chest",              WATER_TEMPLE_CENTRAL_BOW_TARGET_CHEST, {Category::cWaterTemple, Category::cVanillaSmallKey});
ItemLocation WaterTemple_CentralPillarChest                   = ItemLocation::Chest      (0x05, 0x06, "Water Temple Central Pillar Chest",                  WATER_TEMPLE_CENTRAL_PILLAR_CHEST,    {Category::cWaterTemple, Category::cVanillaSmallKey});
ItemLocation WaterTemple_CrackedWallChest                     = ItemLocation::Chest      (0x05, 0x00, "Water Temple Cracked Wall Chest",                    WATER_TEMPLE_CRACKED_WALL_CHEST,      {Category::cWaterTemple, Category::cVanillaSmallKey});
ItemLocation WaterTemple_BossKeyChest                         = ItemLocation::Chest      (0x05, 0x05, "Water Temple Boss Key Chest",                        WATER_TEMPLE_BOSS_KEY_CHEST,          {Category::cWaterTemple, Category::cVanillaBossKey});
ItemLocation WaterTemple_LongshotChest                        = ItemLocation::Chest      (0x05, 0x07, "Water Temple Longshot Chest",                        WATER_TEMPLE_LONGSHOT_CHEST,         {Category::cWaterTemple,});
ItemLocation WaterTemple_RiverChest                           = ItemLocation::Chest      (0x05, 0x03, "Water Temple River Chest",                           WATER_TEMPLE_RIVER_CHEST,            {Category::cWaterTemple, Category::cVanillaSmallKey});
//Water Temple MQ
ItemLocation WaterTemple_MQ_CentralPillarChest                = ItemLocation::Chest      (0x05, 0x06, "Water Temple MQ Central Pillar Chest",               WATER_TEMPLE_MQ_CENTRAL_PILLAR_CHEST, {Category::cWaterTemple, Category::cVanillaSmallKey});
ItemLocation WaterTemple_MQ_BossKeyChest                      = ItemLocation::Chest      (0x05, 0x05, "Water Temple MQ Boss Key Chest",                     WATER_TEMPLE_MQ_BOSS_KEY_CHEST,       {Category::cWaterTemple, Category::cVanillaBossKey});
ItemLocation WaterTemple_MQ_LongshotChest                     = ItemLocation::Chest      (0x05, 0x00, "Water Temple MQ Longshot Chest",                     WATER_TEMPLE_MQ_LONGSHOT_CHEST,      {Category::cWaterTemple,});
ItemLocation WaterTemple_MQ_CompassChest                      = ItemLocation::Chest      (0x05, 0x01, "Water Temple MQ Compass Chest",                      WATER_TEMPLE_MQ_COMPASS_CHEST,       {Category::cWaterTemple, Category::cVanillaCompass,});
ItemLocation WaterTemple_MQ_MapChest                          = ItemLocation::Chest      (0x05, 0x02, "Water Temple MQ Map Chest",                          WATER_TEMPLE_MQ_MAP_CHEST,           {Category::cWaterTemple, Category::cVanillaMap,});
ItemLocation WaterTemple_MQ_FreestandingKey                   = ItemLocation::Collectable(0x05, 0x01, "Water Temple MQ Freestanding Key",                   WATER_TEMPLE_MQ_FREESTANDING_KEY,    {Category::cWaterTemple, Category::cVanillaSmallKey});

//Spirit Temple Shared
ItemLocation SpiritTemple_SilverGauntletsChest                = ItemLocation::Chest      (0x5C, 0x0B, "Spirit Temple Silver Gauntlets Chest",               SPIRIT_TEMPLE_SILVER_GAUNTLETS_CHEST, {Category::cSpiritTemple, Category::cDesertColossus});
ItemLocation SpiritTemple_MirrorShieldChest                   = ItemLocation::Chest      (0x5C, 0x09, "Spirit Temple Mirror Shield Chest",                  SPIRIT_TEMPLE_MIRROR_SHIELD_CHEST,    {Category::cSpiritTemple, Category::cDesertColossus});
//Spirit Temple Vanilla
ItemLocation SpiritTemple_ChildBridgeChest                    = ItemLocation::Chest      (0x06, 0x08, "Spirit Temple Child Bridge Chest",                   SPIRIT_TEMPLE_CHILD_BRIDGE_CHEST,           {Category::cSpiritTemple,});
ItemLocation SpiritTemple_ChildEarlyTorchesChest              = ItemLocation::Chest      (0x06, 0x00, "Spirit Temple Child Early Torches Chest",            SPIRIT_TEMPLE_CHILD_EARLY_TORCHES_CHEST,     {Category::cSpiritTemple, Category::cVanillaSmallKey});
ItemLocation SpiritTemple_CompassChest                        = ItemLocation::Chest      (0x06, 0x04, "Spirit Temple Compass Chest",                        SPIRIT_TEMPLE_COMPASS_CHEST,               {Category::cSpiritTemple, Category::cVanillaCompass,});
ItemLocation SpiritTemple_EarlyAdultRightChest                = ItemLocation::Chest      (0x06, 0x07, "Spirit Temple Early Adult Right Chest",              SPIRIT_TEMPLE_EARLY_ADULT_RIGHT_CHEST,       {Category::cSpiritTemple, Category::cVanillaSmallKey});
ItemLocation SpiritTemple_FirstMirrorLeftChest                = ItemLocation::Chest      (0x06, 0x0D, "Spirit Temple First Mirror Left Chest",              SPIRIT_TEMPLE_FIRST_MIRROR_LEFT_CHEST,       {Category::cSpiritTemple,});
ItemLocation SpiritTemple_FirstMirrorRightChest               = ItemLocation::Chest      (0x06, 0x0E, "Spirit Temple First Mirror Right Chest",             SPIRIT_TEMPLE_FIRST_MIRROR_RIGHT_CHEST,      {Category::cSpiritTemple,});
ItemLocation SpiritTemple_MapChest                            = ItemLocation::Chest      (0x06, 0x03, "Spirit Temple Map Chest",                            SPIRIT_TEMPLE_MAP_CHEST,                   {Category::cSpiritTemple, Category::cVanillaMap,});
ItemLocation SpiritTemple_ChildClimbNorthChest                = ItemLocation::Chest      (0x06, 0x06, "Spirit Temple Child Climb North Chest",              SPIRIT_TEMPLE_CHILD_CLIMB_NORTH_CHEST,       {Category::cSpiritTemple,});
ItemLocation SpiritTemple_ChildClimbEastChest                 = ItemLocation::Chest      (0x06, 0x0C, "Spirit Temple Child Climb East Chest",               SPIRIT_TEMPLE_CHILD_CLIMB_EAST_CHEST,        {Category::cSpiritTemple,});
ItemLocation SpiritTemple_SunBlockRoomChest                   = ItemLocation::Chest      (0x06, 0x01, "Spirit Temple Sun Block Room Chest",                 SPIRIT_TEMPLE_SUN_BLOCK_ROOM_CHEST,          {Category::cSpiritTemple, Category::cVanillaSmallKey});
ItemLocation SpiritTemple_StatueRoomHandChest                 = ItemLocation::Chest      (0x06, 0x02, "Spirit Temple Statue Room Hand Chest",               SPIRIT_TEMPLE_STATUE_ROOM_HAND_CHEST,        {Category::cSpiritTemple, Category::cVanillaSmallKey});
ItemLocation SpiritTemple_StatueRoomNortheastChest            = ItemLocation::Chest      (0x06, 0x0F, "Spirit Temple Statue Room Northeast Chest",          SPIRIT_TEMPLE_STATUE_ROOM_NORTHEAST_CHEST,   {Category::cSpiritTemple,});
ItemLocation SpiritTemple_NearFourArmosChest                  = ItemLocation::Chest      (0x06, 0x05, "Spirit Temple Near Four Armos Chest",                SPIRIT_TEMPLE_NEAR_FOUR_ARMOS_CHEST,         {Category::cSpiritTemple, Category::cVanillaSmallKey});
ItemLocation SpiritTemple_HallwayRightInvisibleChest          = ItemLocation::Chest      (0x06, 0x14, "Spirit Temple Hallway Right Invisible Chest",        SPIRIT_TEMPLE_HALLWAY_RIGHT_INVISIBLE_CHEST, {Category::cSpiritTemple,});
ItemLocation SpiritTemple_HallwayLeftInvisibleChest           = ItemLocation::Chest      (0x06, 0x15, "Spirit Temple Hallway Left Invisible Chest",         SPIRIT_TEMPLE_HALLWAY_LEFT_INVISIBLE_CHEST,  {Category::cSpiritTemple,});
ItemLocation SpiritTemple_BossKeyChest                        = ItemLocation::Chest      (0x06, 0x0A, "Spirit Temple Boss Key Chest",                       SPIRIT_TEMPLE_BOSS_KEY_CHEST,               {Category::cSpiritTemple, Category::cVanillaBossKey});
ItemLocation SpiritTemple_TopmostChest                        = ItemLocation::Chest      (0x06, 0x12, "Spirit Temple Topmost Chest",                        SPIRIT_TEMPLE_TOPMOST_CHEST,               {Category::cSpiritTemple,});
//Spirit Temple MQ
ItemLocation SpiritTemple_MQ_EntranceFrontLeftChest           = ItemLocation::Chest      (0x06, 0x1A, "Spirit Temple MQ Entrance Front Left Chest",         SPIRIT_TEMPLE_MQ_ENTRANCE_FRONT_LEFT_CHEST,     {Category::cSpiritTemple,});
ItemLocation SpiritTemple_MQ_EntranceBackRightChest           = ItemLocation::Chest      (0x06, 0x1F, "Spirit Temple MQ Entrance Back Right Chest",         SPIRIT_TEMPLE_MQ_ENTRANCE_BACK_RIGHT_CHEST,     {Category::cSpiritTemple,});
ItemLocation SpiritTemple_MQ_EntranceFrontRightChest          = ItemLocation::Chest      (0x06, 0x1B, "Spirit Temple MQ Entrance Front Right Chest",        SPIRIT_TEMPLE_MQ_ENTRANCE_FRONT_RIGHT_CHEST,    {Category::cSpiritTemple, Category::cVanillaSmallKey});
ItemLocation SpiritTemple_MQ_EntranceBackLeftChest            = ItemLocation::Chest      (0x06, 0x1E, "Spirit Temple MQ Entrance Back Left Chest",          SPIRIT_TEMPLE_MQ_ENTRANCE_BACK_LEFT_CHEST,      {Category::cSpiritTemple, Category::cVanillaSmallKey});
ItemLocation SpiritTemple_MQ_ChildHammerSwitchChest           = ItemLocation::Chest      (0x06, 0x1D, "Spirit Temple MQ Child Hammer Switch Chest",         SPIRIT_TEMPLE_MQ_CHILD_HAMMER_SWITCH_CHEST,     {Category::cSpiritTemple, Category::cVanillaSmallKey});
ItemLocation SpiritTemple_MQ_MapChest                         = ItemLocation::Chest      (0x06, 0x00, "Spirit Temple MQ Map Chest",                         SPIRIT_TEMPLE_MQ_MAP_CHEST,                   {Category::cSpiritTemple, Category::cVanillaMap,});
ItemLocation SpiritTemple_MQ_MapRoomEnemyChest                = ItemLocation::Chest      (0x06, 0x08, "Spirit Temple MQ Map Room Enemy Chest",              SPIRIT_TEMPLE_MQ_MAP_ROOM_ENEMY_CHEST,          {Category::cSpiritTemple, Category::cVanillaSmallKey});
ItemLocation SpiritTemple_MQ_ChildClimbNorthChest             = ItemLocation::Chest      (0x06, 0x06, "Spirit Temple MQ Child Climb North Chest",           SPIRIT_TEMPLE_MQ_CHILD_CLIMB_NORTH_CHEST,       {Category::cSpiritTemple,});
ItemLocation SpiritTemple_MQ_ChildClimbSouthChest             = ItemLocation::Chest      (0x06, 0x0C, "Spirit Temple MQ Child Climb South Chest",           SPIRIT_TEMPLE_MQ_CHILD_CLIMB_SOUTH_CHEST,       {Category::cSpiritTemple, Category::cVanillaSmallKey});
ItemLocation SpiritTemple_MQ_CompassChest                     = ItemLocation::Chest      (0x06, 0x03, "Spirit Temple MQ Compass Chest",                     SPIRIT_TEMPLE_MQ_COMPASS_CHEST,               {Category::cSpiritTemple, Category::cVanillaCompass,});
ItemLocation SpiritTemple_MQ_StatueRoomLullabyChest           = ItemLocation::Chest      (0x06, 0x0F, "Spirit Temple MQ Statue Room Lullaby Chest",         SPIRIT_TEMPLE_MQ_STATUE_ROOM_LULLABY_CHEST,     {Category::cSpiritTemple,});
ItemLocation SpiritTemple_MQ_StatueRoomInvisibleChest         = ItemLocation::Chest      (0x06, 0x02, "Spirit Temple MQ Statue Room Invisible Chest",       SPIRIT_TEMPLE_MQ_STATUE_ROOM_INVISIBLE_CHEST,   {Category::cSpiritTemple,});
ItemLocation SpiritTemple_MQ_SilverBlockHallwayChest          = ItemLocation::Chest      (0x06, 0x1C, "Spirit Temple MQ Silver Block Hallway Chest",        SPIRIT_TEMPLE_MQ_SILVER_BLOCK_HALLWAY_CHEST,    {Category::cSpiritTemple, Category::cVanillaSmallKey});
ItemLocation SpiritTemple_MQ_SunBlockRoomChest                = ItemLocation::Chest      (0x06, 0x01, "Spirit Temple MQ Sun Block Room Chest",              SPIRIT_TEMPLE_MQ_SUN_BLOCK_ROOM_CHEST,          {Category::cSpiritTemple,});
ItemLocation SpiritTemple_MQ_SymphonyRoomChest                = ItemLocation::Chest      (0x06, 0x07, "Spirit Temple MQ Symphony Room Chest",               SPIRIT_TEMPLE_MQ_SYMPHONY_ROOM_CHEST,          {Category::cSpiritTemple,});
ItemLocation SpiritTemple_MQ_LeeverRoomChest                  = ItemLocation::Chest      (0x06, 0x04, "Spirit Temple MQ Leever Room Chest",                 SPIRIT_TEMPLE_MQ_LEEVER_ROOM_CHEST,            {Category::cSpiritTemple,});
ItemLocation SpiritTemple_MQ_BeamosRoomChest                  = ItemLocation::Chest      (0x06, 0x19, "Spirit Temple MQ Beamos Room Chest",                 SPIRIT_TEMPLE_MQ_BEAMOS_ROOM_CHEST,            {Category::cSpiritTemple,});
ItemLocation SpiritTemple_MQ_ChestSwitchChest                 = ItemLocation::Chest      (0x06, 0x18, "Spirit Temple MQ Chest Switch Chest",                SPIRIT_TEMPLE_MQ_CHEST_SWITCH_CHEST,           {Category::cSpiritTemple,});
ItemLocation SpiritTemple_MQ_BossKeyChest                     = ItemLocation::Chest      (0x06, 0x05, "Spirit Temple MQ Boss Key Chest",                    SPIRIT_TEMPLE_MQ_BOSS_KEY_CHEST,               {Category::cSpiritTemple, Category::cVanillaBossKey});
ItemLocation SpiritTemple_MQ_MirrorPuzzleInvisibleChest       = ItemLocation::Chest      (0x06, 0x12, "Spirit Temple MQ Mirror Puzzle Invisible Chest",     SPIRIT_TEMPLE_MQ_MIRROR_PUZZLE_INVISIBLE_CHEST, {Category::cSpiritTemple, Category::cVanillaSmallKey});

//Shadow Temple Vanilla
ItemLocation ShadowTemple_MapChest                            = ItemLocation::Chest      (0x07, 0x01, "Shadow Temple Map Chest",                            SHADOW_TEMPLE_MAP_CHEST,                      {Category::cShadowTemple, Category::cVanillaMap,});
ItemLocation ShadowTemple_HoverBootsChest                     = ItemLocation::Chest      (0x07, 0x07, "Shadow Temple Hover Boots Chest",                    SHADOW_TEMPLE_HOVER_BOOTS_CHEST,               {Category::cShadowTemple,});
ItemLocation ShadowTemple_CompassChest                        = ItemLocation::Chest      (0x07, 0x03, "Shadow Temple Compass Chest",                        SHADOW_TEMPLE_COMPASS_CHEST,                  {Category::cShadowTemple, Category::cVanillaCompass,});
ItemLocation ShadowTemple_EarlySilverRupeeChest               = ItemLocation::Chest      (0x07, 0x02, "Shadow Temple Early Silver Rupee Chest",             SHADOW_TEMPLE_EARLY_SILVER_RUPEE_CHEST,         {Category::cShadowTemple, Category::cVanillaSmallKey});
ItemLocation ShadowTemple_InvisibleBladesVisibleChest         = ItemLocation::Chest      (0x07, 0x0C, "Shadow Temple Invisible Blades Visible Chest",       SHADOW_TEMPLE_INVISIBLE_BLADES_VISIBLE_CHEST,   {Category::cShadowTemple,});
ItemLocation ShadowTemple_InvisibleBladesInvisibleChest       = ItemLocation::Chest      (0x07, 0x16, "Shadow Temple Invisible Blades Invisible Chest",     SHADOW_TEMPLE_INVISIBLE_BLADES_INVISIBLE_CHEST, {Category::cShadowTemple,});
ItemLocation ShadowTemple_FallingSpikesLowerChest             = ItemLocation::Chest      (0x07, 0x05, "Shadow Temple Falling Spikes Lower Chest",           SHADOW_TEMPLE_FALLING_SPIKES_LOWER_CHEST,       {Category::cShadowTemple,});
ItemLocation ShadowTemple_FallingSpikesUpperChest             = ItemLocation::Chest      (0x07, 0x06, "Shadow Temple Falling Spikes Upper Chest",           SHADOW_TEMPLE_FALLING_SPIKES_UPPER_CHEST,       {Category::cShadowTemple,});
ItemLocation ShadowTemple_FallingSpikesSwitchChest            = ItemLocation::Chest      (0x07, 0x04, "Shadow Temple Falling Spikes Switch Chest",          SHADOW_TEMPLE_FALLING_SPIKES_SWITCH_CHEST,      {Category::cShadowTemple, Category::cVanillaSmallKey});
ItemLocation ShadowTemple_InvisibleSpikesChest                = ItemLocation::Chest      (0x07, 0x09, "Shadow Temple Invisible Spikes Chest",               SHADOW_TEMPLE_INVISIBLE_SPIKES_CHEST,          {Category::cShadowTemple,});
ItemLocation ShadowTemple_WindHintChest                       = ItemLocation::Chest      (0x07, 0x15, "Shadow Temple Wind Hint Chest",                      SHADOW_TEMPLE_WIND_HINT_CHEST,                 {Category::cShadowTemple,});
ItemLocation ShadowTemple_AfterWindEnemyChest                 = ItemLocation::Chest      (0x07, 0x08, "Shadow Temple After Wind Enemy Chest",               SHADOW_TEMPLE_AFTER_WIND_ENEMY_CHEST,           {Category::cShadowTemple,});
ItemLocation ShadowTemple_AfterWindHiddenChest                = ItemLocation::Chest      (0x07, 0x14, "Shadow Temple After Wind Hidden Chest",              SHADOW_TEMPLE_AFTER_WIND_HIDDEN_CHEST,          {Category::cShadowTemple, Category::cVanillaSmallKey});
ItemLocation ShadowTemple_SpikeWallsLeftChest                 = ItemLocation::Chest      (0x07, 0x0A, "Shadow Temple Spike Walls Left Chest",               SHADOW_TEMPLE_SPIKE_WALLS_LEFT_CHEST,           {Category::cShadowTemple,});
ItemLocation ShadowTemple_BossKeyChest                        = ItemLocation::Chest      (0x07, 0x0B, "Shadow Temple Boss Key Chest",                       SHADOW_TEMPLE_BOSS_KEY_CHEST,                  {Category::cShadowTemple, Category::cVanillaBossKey});
ItemLocation ShadowTemple_InvisibleFloormasterChest           = ItemLocation::Chest      (0x07, 0x0D, "Shadow Temple Invisible Floormaster Chest",          SHADOW_TEMPLE_INVISIBLE_FLOORMASTER_CHEST,     {Category::cShadowTemple, Category::cVanillaSmallKey});
ItemLocation ShadowTemple_FreestandingKey                     = ItemLocation::Collectable(0x07, 0x01, "Shadow Temple Freestanding Key",                     SHADOW_TEMPLE_FREESTANDING_KEY,               {Category::cShadowTemple, Category::cVanillaSmallKey});
//Shadow Temple MQ
ItemLocation ShadowTemple_MQ_CompassChest                     = ItemLocation::Chest      (0x07, 0x01, "Shadow Temple MQ Compass Chest",                     SHADOW_TEMPLE_MQ_COMPASS_CHEST,                  {Category::cShadowTemple, Category::cVanillaCompass,});
ItemLocation ShadowTemple_MQ_HoverBootsChest                  = ItemLocation::Chest      (0x07, 0x07, "Shadow Temple MQ Hover Boots Chest",                 SHADOW_TEMPLE_MQ_HOVER_BOOTS_CHEST,               {Category::cShadowTemple,});
ItemLocation ShadowTemple_MQ_EarlyGibdosChest                 = ItemLocation::Chest      (0x07, 0x03, "Shadow Temple MQ Early Gibdos Chest",                SHADOW_TEMPLE_MQ_EARLY_GIBDOS_CHEST,              {Category::cShadowTemple, Category::cVanillaSmallKey});
ItemLocation ShadowTemple_MQ_MapChest                         = ItemLocation::Chest      (0x07, 0x02, "Shadow Temple MQ Map Chest",                         SHADOW_TEMPLE_MQ_MAP_CHEST,                      {Category::cShadowTemple, Category::cVanillaMap,});
ItemLocation ShadowTemple_MQ_BeamosSilverRupeesChest          = ItemLocation::Chest      (0x07, 0x0F, "Shadow Temple MQ Beamos Silver Rupees Chest",        SHADOW_TEMPLE_MQ_BEAMOS_SILVER_RUPEES_CHEST,       {Category::cShadowTemple,});
ItemLocation ShadowTemple_MQ_FallingSpikesSwitchChest         = ItemLocation::Chest      (0x07, 0x04, "Shadow Temple MQ Falling Spikes Switch Chest",       SHADOW_TEMPLE_MQ_FALLING_SPIKES_SWITCH_CHEST,      {Category::cShadowTemple, Category::cVanillaSmallKey});
ItemLocation ShadowTemple_MQ_FallingSpikesLowerChest          = ItemLocation::Chest      (0x07, 0x05, "Shadow Temple MQ Falling Spikes Lower Chest",        SHADOW_TEMPLE_MQ_FALLING_SPIKES_LOWER_CHEST,       {Category::cShadowTemple,});
ItemLocation ShadowTemple_MQ_FallingSpikesUpperChest          = ItemLocation::Chest      (0x07, 0x06, "Shadow Temple MQ Falling Spikes Upper Chest",        SHADOW_TEMPLE_MQ_FALLING_SPIKES_UPPER_CHEST,       {Category::cShadowTemple,});
ItemLocation ShadowTemple_MQ_InvisibleSpikesChest             = ItemLocation::Chest      (0x07, 0x09, "Shadow Temple MQ Invisible Spikes Chest",            SHADOW_TEMPLE_MQ_INVISIBLE_SPIKES_CHEST,          {Category::cShadowTemple,});
ItemLocation ShadowTemple_MQ_BossKeyChest                     = ItemLocation::Chest      (0x07, 0x0B, "Shadow Temple MQ Boss Key Chest",                    SHADOW_TEMPLE_MQ_BOSS_KEY_CHEST,                  {Category::cShadowTemple, Category::cVanillaBossKey});
ItemLocation ShadowTemple_MQ_SpikeWallsLeftChest              = ItemLocation::Chest      (0x07, 0x0A, "Shadow Temple MQ Spike Walls Left Chest",            SHADOW_TEMPLE_MQ_SPIKE_WALLS_LEFT_CHEST,           {Category::cShadowTemple,});
ItemLocation ShadowTemple_MQ_StalfosRoomChest                 = ItemLocation::Chest      (0x07, 0x10, "Shadow Temple MQ Stalfos Room Chest",                SHADOW_TEMPLE_MQ_STALFOS_ROOM_CHEST,              {Category::cShadowTemple,});
ItemLocation ShadowTemple_MQ_InvisibleBladesInvisibleChest    = ItemLocation::Chest      (0x07, 0x16, "Shadow Temple MQ Invisible Blades Invisible Chest",  SHADOW_TEMPLE_MQ_INVISIBLE_BLADES_INVISIBLE_CHEST, {Category::cShadowTemple, Category::cVanillaSmallKey});
ItemLocation ShadowTemple_MQ_InvisibleBladesVisibleChest      = ItemLocation::Chest      (0x07, 0x0C, "Shadow Temple MQ Invisible Blades Visible Chest",    SHADOW_TEMPLE_MQ_INVISIBLE_BLADES_VISIBLE_CHEST,   {Category::cShadowTemple,});
ItemLocation ShadowTemple_MQ_BombFlowerChest                  = ItemLocation::Chest      (0x07, 0x0D, "Shadow Temple MQ Bomb Flower Chest",                 SHADOW_TEMPLE_MQ_BOMB_FLOWER_CHEST,               {Category::cShadowTemple,});
ItemLocation ShadowTemple_MQ_WindHintChest                    = ItemLocation::Chest      (0x07, 0x15, "Shadow Temple MQ Wind Hint Chest",                   SHADOW_TEMPLE_MQ_WIND_HINT_CHEST,                 {Category::cShadowTemple, Category::cVanillaSmallKey});
ItemLocation ShadowTemple_MQ_AfterWindHiddenChest             = ItemLocation::Chest      (0x07, 0x14, "Shadow Temple MQ After Wind Hidden Chest",           SHADOW_TEMPLE_MQ_AFTER_WIND_HIDDEN_CHEST,          {Category::cShadowTemple,});
ItemLocation ShadowTemple_MQ_AfterWindEnemyChest              = ItemLocation::Chest      (0x07, 0x08, "Shadow Temple MQ After Wind Enemy Chest",            SHADOW_TEMPLE_MQ_AFTER_WIND_ENEMY_CHEST,           {Category::cShadowTemple,});
ItemLocation ShadowTemple_MQ_NearShipInvisibleChest           = ItemLocation::Chest      (0x07, 0x0E, "Shadow Temple MQ Near Ship Invisible Chest",         SHADOW_TEMPLE_MQ_NEAR_SHIP_INVISIBLE_CHEST,        {Category::cShadowTemple, Category::cVanillaSmallKey});
ItemLocation ShadowTemple_MQ_FreestandingKey                  = ItemLocation::Collectable(0x07, 0x06, "Shadow Temple MQ Freestanding Key",                  SHADOW_TEMPLE_MQ_FREESTANDING_KEY,               {Category::cShadowTemple, Category::cVanillaSmallKey});

//Bottom of the Well Vanilla
ItemLocation BottomOfTheWell_FrontLeftFakeWallChest           = ItemLocation::Chest      (0x08, 0x08, "Bottom of the Well Front Left Fake Wall Chest",         BOTTOM_OF_THE_WELL_FRONT_LEFT_FAKE_WALL_CHEST,   {Category::cBottomOfTheWell, Category::cVanillaSmallKey});
ItemLocation BottomOfTheWell_FrontCenterBombableChest         = ItemLocation::Chest      (0x08, 0x02, "Bottom of the Well Front Center Bombable Chest",        BOTTOM_OF_THE_WELL_FRONT_CENTER_BOMBABLE_CHEST, {Category::cBottomOfTheWell,});
ItemLocation BottomOfTheWell_RightBottomFakeWallChest         = ItemLocation::Chest      (0x08, 0x05, "Bottom of the Well Right Bottom Fake Wall Chest",       BOTTOM_OF_THE_WELL_RIGHT_BOTTOM_FAKE_WALL_CHEST, {Category::cBottomOfTheWell, Category::cVanillaSmallKey});
ItemLocation BottomOfTheWell_CompassChest                     = ItemLocation::Chest      (0x08, 0x01, "Bottom of the Well Compass Chest",                      BOTTOM_OF_THE_WELL_COMPASS_CHEST,             {Category::cBottomOfTheWell, Category::cVanillaCompass,});
ItemLocation BottomOfTheWell_CenterSkulltulaChest             = ItemLocation::Chest      (0x08, 0x0E, "Bottom of the Well Center Skulltula Chest",             BOTTOM_OF_THE_WELL_CENTER_SKULLTULA_CHEST,     {Category::cBottomOfTheWell,});
ItemLocation BottomOfTheWell_BackLeftBombableChest            = ItemLocation::Chest      (0x08, 0x04, "Bottom of the Well Back Left Bombable Chest",           BOTTOM_OF_THE_WELL_BACK_LEFT_BOMBABLE_CHEST,    {Category::cBottomOfTheWell,});
ItemLocation BottomOfTheWell_LensOfTruthChest                 = ItemLocation::Chest      (0x08, 0x03, "Bottom of the Well Lens of Truth Chest",                BOTTOM_OF_THE_WELL_LENS_OF_TRUTH_CHEST,         {Category::cBottomOfTheWell, Category::cSongDungeonReward});
ItemLocation BottomOfTheWell_InvisibleChest                   = ItemLocation::Chest      (0x08, 0x14, "Bottom of the Well Invisible Chest",                    BOTTOM_OF_THE_WELL_INVISIBLE_CHEST,           {Category::cBottomOfTheWell,});
ItemLocation BottomOfTheWell_UnderwaterFrontChest             = ItemLocation::Chest      (0x08, 0x10, "Bottom of the Well Underwater Front Chest",             BOTTOM_OF_THE_WELL_UNDERWATER_FRONT_CHEST,     {Category::cBottomOfTheWell,});
ItemLocation BottomOfTheWell_UnderwaterLeftChest              = ItemLocation::Chest      (0x08, 0x09, "Bottom of the Well Underwater Left Chest",              BOTTOM_OF_THE_WELL_UNDERWATER_LEFT_CHEST,      {Category::cBottomOfTheWell,});
ItemLocation BottomOfTheWell_MapChest                         = ItemLocation::Chest      (0x08, 0x07, "Bottom of the Well Map Chest",                          BOTTOM_OF_THE_WELL_MAP_CHEST,                 {Category::cBottomOfTheWell, Category::cVanillaMap,});
ItemLocation BottomOfTheWell_FireKeeseChest                   = ItemLocation::Chest      (0x08, 0x0A, "Bottom of the Well Fire Keese Chest",                   BOTTOM_OF_THE_WELL_FIRE_KEESE_CHEST,           {Category::cBottomOfTheWell,});
ItemLocation BottomOfTheWell_LikeLikeChest                    = ItemLocation::Chest      (0x08, 0x0C, "Bottom of the Well Like Like Chest",                    BOTTOM_OF_THE_WELL_LIKE_LIKE_CHEST,            {Category::cBottomOfTheWell,});
ItemLocation BottomOfTheWell_FreestandingKey                  = ItemLocation::Collectable(0x08, 0x01, "Bottom of the Well Freestanding Key",                   BOTTOM_OF_THE_WELL_FREESTANDING_KEY,          {Category::cBottomOfTheWell, Category::cVanillaSmallKey});
//Bottom of the Well MQBottomOfTheWell,
ItemLocation BottomOfTheWell_MQ_MapChest                      = ItemLocation::Chest      (0x08, 0x03, "Bottom of the Well MQ Map Chest",                       BOTTOM_OF_THE_WELL_MQ_MAP_CHEST,                     {Category::cBottomOfTheWell, Category::cVanillaMap,});
ItemLocation BottomOfTheWell_MQ_LensOfTruthChest              = ItemLocation::Chest      (0x08, 0x01, "Bottom of the Well MQ Lens of Truth Chest",             BOTTOM_OF_THE_WELL_MQ_LENS_OF_TRUTH_CHEST,             {Category::cBottomOfTheWell, Category::cSongDungeonReward});
ItemLocation BottomOfTheWell_MQ_CompassChest                  = ItemLocation::Chest      (0x08, 0x02, "Bottom of the Well MQ Compass Chest",                   BOTTOM_OF_THE_WELL_MQ_COMPASS_CHEST,                 {Category::cBottomOfTheWell, Category::cVanillaCompass,});
ItemLocation BottomOfTheWell_MQ_DeadHandFreestandingKey       = ItemLocation::Collectable(0x08, 0x02, "Bottom of the Well MQ Dead Hand Freestanding Key",      BOTTOM_OF_THE_WELL_MQ_DEAD_HAND_FREESTANDING_KEY,      {Category::cBottomOfTheWell, Category::cVanillaSmallKey});
ItemLocation BottomOfTheWell_MQ_EastInnerRoomFreestandingKey  = ItemLocation::Collectable(0x08, 0x01, "Bottom of the Well MQ East Inner Room Freestanding Key",BOTTOM_OF_THE_WELL_MQ_EAST_INNER_ROOM_FREESTANDING_KEY, {Category::cBottomOfTheWell, Category::cVanillaSmallKey});

//Ice Cavern Vanilla
ItemLocation IceCavern_MapChest                               = ItemLocation::Chest      (0x09, 0x00, "Ice Cavern Map Chest",                                  ICE_CAVERN_MAP_CHEST,           {Category::cIceCavern, Category::cVanillaMap,});
ItemLocation IceCavern_CompassChest                           = ItemLocation::Chest      (0x09, 0x01, "Ice Cavern Compass Chest",                              ICE_CAVERN_COMPASS_CHEST,       {Category::cIceCavern, Category::cVanillaCompass,});
ItemLocation IceCavern_IronBootsChest                         = ItemLocation::Chest      (0x09, 0x02, "Ice Cavern Iron Boots Chest",                           ICE_CAVERN_IRON_BOOTS_CHEST,     {Category::cIceCavern,});
ItemLocation IceCavern_FreestandingPoH                        = ItemLocation::Collectable(0x09, 0x01, "Ice Cavern Freestanding PoH",                           ICE_CAVERN_FREESTANDING_POH,    {Category::cIceCavern,});
//Ice Cavern MQIceCavern,
ItemLocation IceCavern_MQ_IronBootsChest                      = ItemLocation::Chest      (0x09, 0x02, "Ice Cavern MQ Iron Boots Chest",                        ICE_CAVERN_MQ_IRON_BOOTS_CHEST,  {Category::cIceCavern,});
ItemLocation IceCavern_MQ_CompassChest                        = ItemLocation::Chest      (0x09, 0x00, "Ice Cavern MQ Compass Chest",                           ICE_CAVERN_MQ_COMPASS_CHEST,    {Category::cIceCavern, Category::cVanillaCompass,});
ItemLocation IceCavern_MQ_MapChest                            = ItemLocation::Chest      (0x09, 0x01, "Ice Cavern MQ Map Chest",                               ICE_CAVERN_MQ_MAP_CHEST,        {Category::cIceCavern, Category::cVanillaMap,});
ItemLocation IceCavern_MQ_FreestandingPoH                     = ItemLocation::Collectable(0x09, 0x01, "Ice Cavern MQ Freestanding PoH",                        ICE_CAVERN_MQ_FREESTANDING_POH, {Category::cIceCavern,});

//Gerudo Training Ground Vanilla
ItemLocation GerudoTrainingGrounds_LobbyLeftChest             = ItemLocation::Chest      (0x0B, 0x13, "Gerudo Training Grounds Lobby Left Chest",              GERUDO_TRAINING_GROUNDS_LOBBY_LEFT_CHEST,             {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_LobbyRightChest            = ItemLocation::Chest      (0x0B, 0x07, "Gerudo Training Grounds Lobby Right Chest",             GERUDO_TRAINING_GROUNDS_LOBBY_RIGHT_CHEST,            {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_StalfosChest               = ItemLocation::Chest      (0x0B, 0x00, "Gerudo Training Grounds Stalfos Chest",                 GERUDO_TRAINING_GROUNDS_STALFOS_CHEST,               {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
ItemLocation GerudoTrainingGrounds_BeamosChest                = ItemLocation::Chest      (0x0B, 0x01, "Gerudo Training Grounds Beamos Chest",                  GERUDO_TRAINING_GROUNDS_BEAMOS_CHEST,                {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
ItemLocation GerudoTrainingGrounds_HiddenCeilingChest         = ItemLocation::Chest      (0x0B, 0x0B, "Gerudo Training Grounds Hidden Ceiling Chest",          GERUDO_TRAINING_GROUNDS_HIDDEN_CEILING_CHEST,         {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
ItemLocation GerudoTrainingGrounds_MazePathFirstChest         = ItemLocation::Chest      (0x0B, 0x06, "Gerudo Training Grounds Maze Path First Chest",         GERUDO_TRAINING_GROUNDS_MAZE_PATH_FIRST_CHEST,         {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MazePathSecondChest        = ItemLocation::Chest      (0x0B, 0x0A, "Gerudo Training Grounds Maze Path Second Chest",        GERUDO_TRAINING_GROUNDS_MAZE_PATH_SECOND_CHEST,        {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MazePathThirdChest         = ItemLocation::Chest      (0x0B, 0x09, "Gerudo Training Grounds Maze Path Third Chest",         GERUDO_TRAINING_GROUNDS_MAZE_PATH_THIRD_CHEST,         {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MazePathFinalChest         = ItemLocation::Chest      (0x0B, 0x0C, "Gerudo Training Grounds Maze Path Final Chest",         GERUDO_TRAINING_GROUNDS_MAZE_PATH_FINAL_CHEST,         {Category::cGerudoTrainingGrounds, Category::cSongDungeonReward});
ItemLocation GerudoTrainingGrounds_MazeRightCentralChest      = ItemLocation::Chest      (0x0B, 0x05, "Gerudo Training Grounds Maze Right Central Chest",      GERUDO_TRAINING_GROUNDS_MAZE_RIGHT_CENTRAL_CHEST,      {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MazeRightSideChest         = ItemLocation::Chest      (0x0B, 0x08, "Gerudo Training Grounds Maze Right Side Chest",         GERUDO_TRAINING_GROUNDS_MAZE_RIGHT_SIDE_CHEST,         {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_UnderwaterSilverRupeeChest = ItemLocation::Chest      (0x0B, 0x0D, "Gerudo Training Grounds Underwater Silver Rupee Chest", GERUDO_TRAINING_GROUNDS_UNDERWATER_SILVER_RUPEE_CHEST, {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
ItemLocation GerudoTrainingGrounds_HammerRoomClearChest       = ItemLocation::Chest      (0x0B, 0x12, "Gerudo Training Grounds Hammer Room Clear Chest",       GERUDO_TRAINING_GROUNDS_HAMMER_ROOM_CLEAR_CHEST,       {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_HammerRoomSwitchChest      = ItemLocation::Chest      (0x0B, 0x10, "Gerudo Training Grounds Hammer Room Switch Chest",      GERUDO_TRAINING_GROUNDS_HAMMER_ROOM_SWITCH_CHEST,      {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
ItemLocation GerudoTrainingGrounds_EyeStatueChest             = ItemLocation::Chest      (0x0B, 0x03, "Gerudo Training Grounds Eye Statue Chest",              GERUDO_TRAINING_GROUNDS_EYE_STATUE_CHEST,             {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
ItemLocation GerudoTrainingGrounds_NearScarecrowChest         = ItemLocation::Chest      (0x0B, 0x04, "Gerudo Training Grounds Near Scarecrow Chest",          GERUDO_TRAINING_GROUNDS_NEAR_SCARECROW_CHEST,         {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
ItemLocation GerudoTrainingGrounds_BeforeHeavyBlockChest      = ItemLocation::Chest      (0x0B, 0x11, "Gerudo Training Grounds Before Heavy Block Chest",      GERUDO_TRAINING_GROUNDS_BEFORE_HEAVY_BLOCK_CHEST,      {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_HeavyBlockFirstChest       = ItemLocation::Chest      (0x0B, 0x0F, "Gerudo Training Grounds Heavy Block First Chest",       GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_FIRST_CHEST,       {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_HeavyBlockSecondChest      = ItemLocation::Chest      (0x0B, 0x0E, "Gerudo Training Grounds Heavy Block Second Chest",      GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_SECOND_CHEST,      {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_HeavyBlockThirdChest       = ItemLocation::Chest      (0x0B, 0x14, "Gerudo Training Grounds Heavy Block Third Chest",       GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_THIRD_CHEST,       {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
ItemLocation GerudoTrainingGrounds_HeavyBlockFourthChest      = ItemLocation::Chest      (0x0B, 0x02, "Gerudo Training Grounds Heavy Block Fourth Chest",      GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_FOURTH_CHEST,      {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_FreestandingKey            = ItemLocation::Collectable(0x0B, 0x01, "Gerudo Training Grounds Freestanding Key",              GERUDO_TRAINING_GROUNDS_FREESTANDING_KEY,            {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
//Gerudo Training Grounds MQ
ItemLocation GerudoTrainingGrounds_MQ_LobbyRightChest         = ItemLocation::Chest      (0x0B, 0x07, "Gerudo Training Grounds MQ Lobby Right Chest",          GERUDO_TRAINING_GROUNDS_MQ_LOBBY_RIGHT_CHEST,        {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MQ_LobbyLeftChest          = ItemLocation::Chest      (0x0B, 0x13, "Gerudo Training Grounds MQ Lobby Left Chest",           GERUDO_TRAINING_GROUNDS_MQ_LOBBY_LEFT_CHEST,         {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MQ_FirstIronKnuckleChest   = ItemLocation::Chest      (0x0B, 0x00, "Gerudo Training Grounds MQ First Iron Knuckle Chest",   GERUDO_TRAINING_GROUNDS_MQ_FIRST_IRON_KNUCKLE_CHEST,  {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MQ_BeforeHeavyBlockChest   = ItemLocation::Chest      (0x0B, 0x11, "Gerudo Training Grounds MQ Before Heavy Block Chest",   GERUDO_TRAINING_GROUNDS_MQ_BEFORE_HEAVY_BLOCK_CHEST,  {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MQ_EyeStatueChest          = ItemLocation::Chest      (0x0B, 0x03, "Gerudo Training Grounds MQ Eye Statue Chest",           GERUDO_TRAINING_GROUNDS_MQ_EYE_STATUE_CHEST,         {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MQ_FlameCircleChest        = ItemLocation::Chest      (0x0B, 0x0E, "Gerudo Training Grounds MQ Flame Circle Chest",         GERUDO_TRAINING_GROUNDS_MQ_FLAME_CIRCLE_CHEST,       {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
ItemLocation GerudoTrainingGrounds_MQ_SecondIronKnuckleChest  = ItemLocation::Chest      (0x0B, 0x12, "Gerudo Training Grounds MQ Second Iron Knuckle Chest",  GERUDO_TRAINING_GROUNDS_MQ_SECOND_IRON_KNUCKLE_CHEST, {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MQ_DinolfosChest           = ItemLocation::Chest      (0x0B, 0x01, "Gerudo Training Grounds MQ Dinolfos Chest",             GERUDO_TRAINING_GROUNDS_MQ_DINOLFOS_CHEST,          {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
ItemLocation GerudoTrainingGrounds_MQ_IceArrowsChest          = ItemLocation::Chest      (0x0B, 0x04, "Gerudo Training Grounds MQ Ice Arrows Chest",           GERUDO_TRAINING_GROUNDS_MQ_ICE_ARROWS_CHEST,         {Category::cGerudoTrainingGrounds, Category::cSongDungeonReward});
ItemLocation GerudoTrainingGrounds_MQ_MazeRightCentralChest   = ItemLocation::Chest      (0x0B, 0x05, "Gerudo Training Grounds MQ Maze Right Central Chest",   GERUDO_TRAINING_GROUNDS_MQ_MAZE_RIGHT_CENTRAL_CHEST,  {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MQ_MazePathFirstChest      = ItemLocation::Chest      (0x0B, 0x06, "Gerudo Training Grounds MQ Maze Path First Chest",      GERUDO_TRAINING_GROUNDS_MQ_MAZE_PATH_FIRST_CHEST,     {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MQ_MazeRightSideChest      = ItemLocation::Chest      (0x0B, 0x08, "Gerudo Training Grounds MQ Maze Right Side Chest",      GERUDO_TRAINING_GROUNDS_MQ_MAZE_RIGHT_SIDE_CHEST,     {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MQ_MazePathThirdChest      = ItemLocation::Chest      (0x0B, 0x09, "Gerudo Training Grounds MQ Maze Path Third Chest",      GERUDO_TRAINING_GROUNDS_MQ_MAZE_PATH_THIRD_CHEST,     {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MQ_MazePathSecondChest     = ItemLocation::Chest      (0x0B, 0x0A, "Gerudo Training Grounds MQ Maze Path Second Chest",     GERUDO_TRAINING_GROUNDS_MQ_MAZE_PATH_SECOND_CHEST,    {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MQ_HiddenCeilingChest      = ItemLocation::Chest      (0x0B, 0x0B, "Gerudo Training Grounds MQ Hidden Ceiling Chest",       GERUDO_TRAINING_GROUNDS_MQ_HIDDEN_CEILING_CHEST,     {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MQ_UnderwaterSilverRupeeChest = ItemLocation::Chest(0x0B, 0x0D, "Gerudo Training Grounds MQ Underwater Silver Rupee Chest",GERUDO_TRAINING_GROUNDS_MQ_UNDERWATER_SILVER_RUPEE_CHEST,{Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
ItemLocation GerudoTrainingGrounds_MQ_HeavyBlockChest         = ItemLocation::Chest      (0x0B, 0x02, "Gerudo Training Grounds MQ Heavy Block Chest",          GERUDO_TRAINING_GROUNDS_MQ_HEAVY_BLOCK_CHEST,        {Category::cGerudoTrainingGrounds,});

//Ganons Castle Shared
ItemLocation GanonsCastle_BossKeyChest                        = ItemLocation::Chest      (0x0A, 0x0B, "Ganon's Tower Boss Key Chest",                          GANONS_TOWER_BOSS_KEY_CHEST,                    {Category::cGanonsCastle,});
//Ganons Castle Vanilla
ItemLocation GanonsCastle_ForestTrialChest                    = ItemLocation::Chest      (0x0D, 0x09, "Ganon's Castle Forest Trial Chest",                     GANONS_CASTLE_FOREST_TRIAL_CHEST,                {Category::cGanonsCastle,});
ItemLocation GanonsCastle_WaterTrialLeftChest                 = ItemLocation::Chest      (0x0D, 0x07, "Ganon's Castle Water Trial Left Chest",                 GANONS_CASTLE_WATER_TRIAL_LEFT_CHEST,             {Category::cGanonsCastle,});
ItemLocation GanonsCastle_WaterTrialRightChest                = ItemLocation::Chest      (0x0D, 0x06, "Ganon's Castle Water Trial Right Chest",                GANONS_CASTLE_WATER_TRIAL_RIGHT_CHEST,            {Category::cGanonsCastle,});
ItemLocation GanonsCastle_ShadowTrialFrontChest               = ItemLocation::Chest      (0x0D, 0x08, "Ganon's Castle Shadow Trial Front Chest",               GANONS_CASTLE_SHADOW_TRIAL_FRONT_CHEST,           {Category::cGanonsCastle,});
ItemLocation GanonsCastle_ShadowTrialGoldenGauntletsChest     = ItemLocation::Chest      (0x0D, 0x05, "Ganon's Castle Shadow Trial Golden Gauntlets Chest",    GANONS_CASTLE_SHADOW_TRIAL_GOLDEN_GAUNTLETS_CHEST, {Category::cGanonsCastle,});
ItemLocation GanonsCastle_SpiritTrialCrystalSwitchChest       = ItemLocation::Chest      (0x0D, 0x12, "Ganon's Castle Spirit Trial Crystal Switch Chest",      GANONS_CASTLE_SPIRIT_TRIAL_CRYSTAL_SWITCH_CHEST,   {Category::cGanonsCastle,});
ItemLocation GanonsCastle_SpiritTrialInvisibleChest           = ItemLocation::Chest      (0x0D, 0x14, "Ganon's Castle Spirit Trial Invisible Chest",           GANONS_CASTLE_SPIRIT_TRIAL_INVISIBLE_CHEST,       {Category::cGanonsCastle,});
ItemLocation GanonsCastle_LightTrialFirstLeftChest            = ItemLocation::Chest      (0x0D, 0x0C, "Ganon's Castle Light Trial First Left Chest",           GANONS_CASTLE_LIGHT_TRIAL_FIRST_LEFT_CHEST,        {Category::cGanonsCastle,});
ItemLocation GanonsCastle_LightTrialSecondLeftChest           = ItemLocation::Chest      (0x0D, 0x0B, "Ganon's Castle Light Trial Second Left Chest",          GANONS_CASTLE_LIGHT_TRIAL_SECOND_LEFT_CHEST,       {Category::cGanonsCastle,});
ItemLocation GanonsCastle_LightTrialThirdLeftChest            = ItemLocation::Chest      (0x0D, 0x0D, "Ganon's Castle Light Trial Third Left Chest",           GANONS_CASTLE_LIGHT_TRIAL_THIRD_LEFT_CHEST,        {Category::cGanonsCastle,});
ItemLocation GanonsCastle_LightTrialFirstRightChest           = ItemLocation::Chest      (0x0D, 0x0E, "Ganon's Castle Light Trial First Right Chest",          GANONS_CASTLE_LIGHT_TRIAL_FIRST_RIGHT_CHEST,       {Category::cGanonsCastle,});
ItemLocation GanonsCastle_LightTrialSecondRightChest          = ItemLocation::Chest      (0x0D, 0x0A, "Ganon's Castle Light Trial Second Right Chest",         GANONS_CASTLE_LIGHT_TRIAL_SECOND_RIGHT_CHEST,      {Category::cGanonsCastle,});
ItemLocation GanonsCastle_LightTrialThirdRightChest           = ItemLocation::Chest      (0x0D, 0x0F, "Ganon's Castle Light Trial Third Right Chest",          GANONS_CASTLE_LIGHT_TRIAL_THIRD_RIGHT_CHEST,       {Category::cGanonsCastle,});
ItemLocation GanonsCastle_LightTrialInvisibleEnemiesChest     = ItemLocation::Chest      (0x0D, 0x10, "Ganon's Castle Light Trial Invisible Enemies Chest",    GANONS_CASTLE_LIGHT_TRIAL_INVISIBLE_ENEMIES_CHEST, {Category::cGanonsCastle, Category::cVanillaSmallKey});
ItemLocation GanonsCastle_LightTrialLullabyChest              = ItemLocation::Chest      (0x0D, 0x11, "Ganon's Castle Light Trial Lullaby Chest",              GANONS_CASTLE_LIGHT_TRIAL_LULLABY_CHEST,          {Category::cGanonsCastle, Category::cVanillaSmallKey});
ItemLocation GanonsCastle_DekuScrubCenterLeft                 = ItemLocation::Base       (0x0D, 0x37, "Ganon's Castle Deku Scrub Center-Left",                 GANONS_CASTLE_DEKU_SCRUB_CENTER_LEFT,             {Category::cGanonsCastle, Category::cDekuScrub,});
ItemLocation GanonsCastle_DekuScrubCenterRight                = ItemLocation::Base       (0x0D, 0x33, "Ganon's Castle Deku Scrub Center-Right",                GANONS_CASTLE_DEKU_SCRUB_CENTER_RIGHT,            {Category::cGanonsCastle, Category::cDekuScrub,});
ItemLocation GanonsCastle_DekuScrubRight                      = ItemLocation::Base       (0x0D, 0x39, "Ganon's Castle Deku Scrub Right",                       GANONS_CASTLE_DEKU_SCRUB_RIGHT,                  {Category::cGanonsCastle, Category::cDekuScrub,});
ItemLocation GanonsCastle_DekuScrubLeft                       = ItemLocation::Base       (0x0D, 0x3A, "Ganon's Castle Deku Scrub Left",                        GANONS_CASTLE_DEKU_SCRUB_LEFT,                   {Category::cGanonsCastle, Category::cDekuScrub,});
//Ganons Castle MQ
ItemLocation GanonsCastle_MQ_WaterTrialChest                  = ItemLocation::Chest      (0x0D, 0x01, "Ganon's Castle MQ Water Trial Chest",                   GANONS_CASTLE_MQ_WATER_TRIAL_CHEST,                 {Category::cGanonsCastle,});
ItemLocation GanonsCastle_MQ_ForestTrialEyeSwitchChest        = ItemLocation::Chest      (0x0D, 0x02, "Ganon's Castle MQ Forest Trial Eye Switch Chest",       GANONS_CASTLE_MQ_FOREST_TRIAL_EYE_SWITCH_CHEST,       {Category::cGanonsCastle,});
ItemLocation GanonsCastle_MQ_ForestTrialFrozenEyeSwitchChest  = ItemLocation::Chest      (0x0D, 0x03, "Ganon's Castle MQ Forest Trial Frozen Eye Switch Chest",GANONS_CASTLE_MQ_FOREST_TRIAL_FROZEN_EYE_SWITCH_CHEST, {Category::cGanonsCastle,});
ItemLocation GanonsCastle_MQ_LightTrialLullabyChest           = ItemLocation::Chest      (0x0D, 0x04, "Ganon's Castle MQ Light Trial Lullaby Chest",           GANONS_CASTLE_MQ_LIGHT_TRIAL_LULLABY_CHEST,          {Category::cGanonsCastle,});
ItemLocation GanonsCastle_MQ_ShadowTrialBombFlowerChest       = ItemLocation::Chest      (0x0D, 0x00, "Ganon's Castle MQ Shadow Trial Bomb Flower Chest",      GANONS_CASTLE_MQ_SHADOW_TRIAL_BOMB_FLOWER_CHEST,      {Category::cGanonsCastle,});
ItemLocation GanonsCastle_MQ_ShadowTrialEyeSwitchChest        = ItemLocation::Chest      (0x0D, 0x05, "Ganon's Castle MQ Shadow Trial Eye Switch Chest",       GANONS_CASTLE_MQ_SHADOW_TRIAL_EYE_SWITCH_CHEST,       {Category::cGanonsCastle,  Category::cVanillaSmallKey});
ItemLocation GanonsCastle_MQ_SpiritTrialGoldenGauntletsChest  = ItemLocation::Chest      (0x0D, 0x06, "Ganon's Castle MQ Spirit Trial Golden Gauntlets Chest", GANONS_CASTLE_MQ_SPIRIT_TRIAL_GOLDEN_GAUNTLETS_CHEST, {Category::cGanonsCastle,});
ItemLocation GanonsCastle_MQ_SpiritTrialSunBackRightChest     = ItemLocation::Chest      (0x0D, 0x07, "Ganon's Castle MQ Spirit Trial Sun Back Right Chest",   GANONS_CASTLE_MQ_SPIRIT_TRIAL_SUN_BACK_RIGHT_CHEST,    {Category::cGanonsCastle,});
ItemLocation GanonsCastle_MQ_SpiritTrialSunBackLeftChest      = ItemLocation::Chest      (0x0D, 0x08, "Ganon's Castle MQ Spirit Trial Sun Back Left Chest",    GANONS_CASTLE_MQ_SPIRIT_TRIAL_SUN_BACK_LEFT_CHEST,     {Category::cGanonsCastle,  Category::cVanillaSmallKey});
ItemLocation GanonsCastle_MQ_SpiritTrialSunFrontLeftChest     = ItemLocation::Chest      (0x0D, 0x09, "Ganon's Castle MQ Spirit Trial Sun Front Left Chest",   GANONS_CASTLE_MQ_SPIRIT_TRIAL_SUN_FRONT_LEFT_CHEST,    {Category::cGanonsCastle,});
ItemLocation GanonsCastle_MQ_SpiritTrialFirstChest            = ItemLocation::Chest      (0x0D, 0x0A, "Ganon's Castle MQ Spirit Trial First Chest",            GANONS_CASTLE_MQ_SPIRIT_TRIAL_FIRST_CHEST,           {Category::cGanonsCastle,});
ItemLocation GanonsCastle_MQ_SpiritTrialInvisibleChest        = ItemLocation::Chest      (0x0D, 0x14, "Ganon's Castle MQ Spirit Trial Invisible Chest",        GANONS_CASTLE_MQ_SPIRIT_TRIAL_INVISIBLE_CHEST,       {Category::cGanonsCastle,});
ItemLocation GanonsCastle_MQ_ForestTrialFreestandingKey       = ItemLocation::Collectable(0x0D, 0x01, "Ganon's Castle MQ Forest Trial Freestanding Key",       GANONS_CASTLE_MQ_FOREST_TRIAL_FREESTANDING_KEY,      {Category::cGanonsCastle, Category::cVanillaSmallKey});
ItemLocation GanonsCastle_MQ_DekuScrubRight                   = ItemLocation::Base       (0x0D, 0x30, "Ganon's Castle MQ Deku Scrub Right",                    GANONS_CASTLE_MQ_DEKU_SCRUB_RIGHT,                  {Category::cGanonsCastle, Category::cDekuScrub,});
ItemLocation GanonsCastle_MQ_DekuScrubCenterLeft              = ItemLocation::Base       (0x0D, 0x37, "Ganon's Castle MQ Deku Scrub Center-Left",              GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER_LEFT,             {Category::cGanonsCastle, Category::cDekuScrub,});
ItemLocation GanonsCastle_MQ_DekuScrubCenter                  = ItemLocation::Base       (0x0D, 0x33, "Ganon's Castle MQ Deku Scrub Center",                   GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER,                 {Category::cGanonsCastle, Category::cDekuScrub,});
ItemLocation GanonsCastle_MQ_DekuScrubCenterRight             = ItemLocation::Base       (0x0D, 0x39, "Ganon's Castle MQ Deku Scrub Center-Right",             GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER_RIGHT,            {Category::cGanonsCastle, Category::cDekuScrub,});
ItemLocation GanonsCastle_MQ_DekuScrubLeft                    = ItemLocation::Base       (0x0D, 0x3A, "Ganon's Castle MQ Deku Scrub Left",                     GANONS_CASTLE_MQ_DEKU_SCRUB_LEFT,                   {Category::cGanonsCastle, Category::cDekuScrub,});

/*-------------------------------
   --- GOLD SKULLTULA TOKENS ---
  -------------------------------*/

//Dungeons
ItemLocation DekuTree_GS_BasementBackRoom                 = ItemLocation::GSToken(0x00, 0x01, "Deku Tree GS Basement Back Room",                  DEKU_TREE_GS_BASEMENT_BACK_ROOM,                {Category::cDekuTree, Category::cSkulltula,});
ItemLocation DekuTree_GS_BasementGate                     = ItemLocation::GSToken(0x00, 0x02, "Deku Tree GS Basement Gate",                       DEKU_TREE_GS_BASEMENT_GATE,                    {Category::cDekuTree, Category::cSkulltula,});
ItemLocation DekuTree_GS_BasementVines                    = ItemLocation::GSToken(0x00, 0x04, "Deku Tree GS Basement Vines",                      DEKU_TREE_GS_BASEMENT_VINES,                   {Category::cDekuTree, Category::cSkulltula,});
ItemLocation DekuTree_GS_CompassRoom                      = ItemLocation::GSToken(0x00, 0x08, "Deku Tree GS Compass Room",                        DEKU_TREE_GS_COMPASS_ROOM,                     {Category::cDekuTree, Category::cSkulltula,});

ItemLocation DekuTree_MQ_GS_Lobby                         = ItemLocation::GSToken(0x00, 0x02, "Deku Tree MQ GS Lobby",                            DEKU_TREE_MQ_GS_LOBBY,                        {Category::cDekuTree, Category::cSkulltula,});
ItemLocation DekuTree_MQ_GS_CompassRoom                   = ItemLocation::GSToken(0x00, 0x08, "Deku Tree MQ GS Compass Room",                     DEKU_TREE_MQ_GS_COMPASS_ROOM,                  {Category::cDekuTree, Category::cSkulltula,});
ItemLocation DekuTree_MQ_GS_BasementGravesRoom            = ItemLocation::GSToken(0x00, 0x04, "Deku Tree MQ GS Basement Graves Room",             DEKU_TREE_MQ_GS_BASEMENT_GRAVES_ROOM,           {Category::cDekuTree, Category::cSkulltula,});
ItemLocation DekuTree_MQ_GS_BasementBackRoom              = ItemLocation::GSToken(0x00, 0x01, "Deku Tree MQ GS Basement Back Room",               DEKU_TREE_MQ_GS_BASEMENT_BACK_ROOM,             {Category::cDekuTree, Category::cSkulltula,});

ItemLocation DodongosCavern_GS_VinesAboveStairs           = ItemLocation::GSToken(0x01, 0x01, "Dodongos Cavern GS Vines Above Stairs",            DODONGOS_CAVERN_GS_VINES_ABOVE_STAIRS,          {Category::cDodongosCavern, Category::cSkulltula,});
ItemLocation DodongosCavern_GS_Scarecrow                  = ItemLocation::GSToken(0x01, 0x02, "Dodongos Cavern GS Scarecrow",                     DODONGOS_CAVERN_GS_SCARECROW,                 {Category::cDodongosCavern, Category::cSkulltula,});
ItemLocation DodongosCavern_GS_AlcoveAboveStairs          = ItemLocation::GSToken(0x01, 0x04, "Dodongos Cavern GS Alcove Above Stairs",           DODONGOS_CAVERN_GS_ALCOVE_ABOVE_STAIRS,         {Category::cDodongosCavern, Category::cSkulltula,});
ItemLocation DodongosCavern_GS_BackRoom                   = ItemLocation::GSToken(0x01, 0x08, "Dodongos Cavern GS Back Room",                     DODONGOS_CAVERN_GS_BACK_ROOM,                  {Category::cDodongosCavern, Category::cSkulltula,});
ItemLocation DodongosCavern_GS_SideRoomNearLowerLizalfos  = ItemLocation::GSToken(0x01, 0x10, "Dodongos Cavern GS Side Room Near Lower Lizalfos", DODONGOS_CAVERN_GS_SIDE_ROOM_NEAR_LOWER_LIZALFOS, {Category::cDodongosCavern, Category::cSkulltula,});

ItemLocation DodongosCavern_MQ_GS_ScrubRoom               = ItemLocation::GSToken(0x01, 0x02, "Dodongos Cavern MQ GS Scrub Room",                 DODONGOS_CAVERN_MQ_GS_SCRUB_ROOM,              {Category::cDodongosCavern, Category::cSkulltula,});
ItemLocation DodongosCavern_MQ_GS_SongOfTimeBlockRoom     = ItemLocation::GSToken(0x01, 0x08, "Dodongos Cavern MQ GS Song of Time Block Room",    DODONGOS_CAVERN_MQ_GS_SONG_OF_TIME_BLOCK_ROOM,    {Category::cDodongosCavern, Category::cSkulltula,});
ItemLocation DodongosCavern_MQ_GS_LizalfosRoom            = ItemLocation::GSToken(0x01, 0x04, "Dodongos Cavern MQ GS Lizalfos Room",              DODONGOS_CAVERN_MQ_GS_LIZALFOS_ROOM,           {Category::cDodongosCavern, Category::cSkulltula,});
ItemLocation DodongosCavern_MQ_GS_LarvaeRoom              = ItemLocation::GSToken(0x01, 0x10, "Dodongos Cavern MQ GS Larvae Room",                DODONGOS_CAVERN_MQ_GS_LARVAE_ROOM,             {Category::cDodongosCavern, Category::cSkulltula,});
ItemLocation DodongosCavern_MQ_GS_BackRoom                = ItemLocation::GSToken(0x01, 0x01, "Dodongos Cavern MQ GS Back Room",                  DODONGOS_CAVERN_MQ_GS_BACK_AREA,               {Category::cDodongosCavern, Category::cSkulltula,});

ItemLocation JabuJabusBelly_GS_LobbyBasementLower         = ItemLocation::GSToken(0x02, 0x01, "Jabu Jabus Belly GS Lobby Basement Lower",         JABU_JABUS_BELLY_GS_LOBBY_BASEMENT_LOWER,        {Category::cJabuJabusBelly, Category::cSkulltula,});
ItemLocation JabuJabusBelly_GS_LobbyBasementUpper         = ItemLocation::GSToken(0x02, 0x02, "Jabu Jabus Belly GS Lobby Basement Upper",         JABU_JABUS_BELLY_GS_LOBBY_BASEMENT_UPPER,        {Category::cJabuJabusBelly, Category::cSkulltula,});
ItemLocation JabuJabusBelly_GS_NearBoss                   = ItemLocation::GSToken(0x02, 0x04, "Jabu Jabus Belly GS Near Boss",                    JABU_JABUS_BELLY_GS_NEAR_BOSS,                  {Category::cJabuJabusBelly, Category::cSkulltula,});
ItemLocation JabuJabusBelly_GS_WaterSwitchRoom            = ItemLocation::GSToken(0x02, 0x08, "Jabu Jabus Belly GS Water Switch Room",            JABU_JABUS_BELLY_GS_WATER_SWITCH_ROOM,           {Category::cJabuJabusBelly, Category::cSkulltula,});

ItemLocation JabuJabusBelly_MQ_GS_TailPasaranRoom         = ItemLocation::GSToken(0x02, 0x04, "Jabu Jabus Belly MQ GS Tail Parasan Room",         JABU_JABUS_BELLY_MQ_GS_TAILPASARAN_ROOM,        {Category::cJabuJabusBelly, Category::cSkulltula,});
ItemLocation JabuJabusBelly_MQ_GS_InvisibleEnemiesRoom    = ItemLocation::GSToken(0x02, 0x08, "Jabu Jabus Belly MQ GS Invisible Enemies Room",    JABU_JABUS_BELLY_MQ_GS_INVISIBLE_ENEMIES_ROOM,   {Category::cJabuJabusBelly, Category::cSkulltula,});
ItemLocation JabuJabusBelly_MQ_GS_BoomerangChestRoom      = ItemLocation::GSToken(0x02, 0x01, "Jabu Jabus Belly MQ GS Boomerang Chest Room",      JABU_JABUS_BELLY_MQ_GS_BOOMERANG_CHEST_ROOM,     {Category::cJabuJabusBelly, Category::cSkulltula,});
ItemLocation JabuJabusBelly_MQ_GS_NearBoss                = ItemLocation::GSToken(0x02, 0x02, "Jabu Jabus Belly MQ GS Near Boss",                 JABU_JABUS_BELLY_MQ_GS_NEAR_BOSS,               {Category::cJabuJabusBelly, Category::cSkulltula,});

ItemLocation ForestTemple_GS_RaisedIslandCourtyard        = ItemLocation::GSToken(0x03, 0x01, "Forest Temple GS Raised Island Courtyard",         FOREST_TEMPLE_GS_RAISED_ISLAND_COURTYARD,       {Category::cForestTemple, Category::cSkulltula,});
ItemLocation ForestTemple_GS_FirstRoom                    = ItemLocation::GSToken(0x03, 0x02, "Forest Temple GS First Room",                      FOREST_TEMPLE_GS_FIRST_ROOM,                   {Category::cForestTemple, Category::cSkulltula,});
ItemLocation ForestTemple_GS_LevelIslandCourtyard         = ItemLocation::GSToken(0x03, 0x04, "Forest Temple GS Level Island Courtyard",          FOREST_TEMPLE_GS_LEVEL_ISLAND_COURTYARD,        {Category::cForestTemple, Category::cSkulltula,});
ItemLocation ForestTemple_GS_Lobby                        = ItemLocation::GSToken(0x03, 0x08, "Forest Temple GS Lobby",                           FOREST_TEMPLE_GS_LOBBY,                       {Category::cForestTemple, Category::cSkulltula,});
ItemLocation ForestTemple_GS_Basement                     = ItemLocation::GSToken(0x03, 0x10, "Forest Temple GS Basement",                        FOREST_TEMPLE_GS_BASEMENT,                    {Category::cForestTemple, Category::cSkulltula,});

ItemLocation ForestTemple_MQ_GS_FirstHallway              = ItemLocation::GSToken(0x03, 0x02, "Forest Temple MQ GS First Hallway",                FOREST_TEMPLE_MQ_GS_FIRST_HALLWAY,             {Category::cForestTemple, Category::cSkulltula,});
ItemLocation ForestTemple_MQ_GS_BlockPushRoom             = ItemLocation::GSToken(0x03, 0x10, "Forest Temple MQ GS Block Push Room",              FOREST_TEMPLE_MQ_GS_BLOCK_PUSH_ROOM,            {Category::cForestTemple, Category::cSkulltula,});
ItemLocation ForestTemple_MQ_GS_RaisedIslandCourtyard     = ItemLocation::GSToken(0x03, 0x01, "Forest Temple MQ GS Raised Island Courtyard",      FOREST_TEMPLE_MQ_GS_RAISED_ISLAND_COURTYARD,    {Category::cForestTemple, Category::cSkulltula,});
ItemLocation ForestTemple_MQ_GS_LevelIslandCourtyard      = ItemLocation::GSToken(0x03, 0x04, "Forest Temple MQ GS Level Island Courtyard",       FOREST_TEMPLE_MQ_GS_LEVEL_ISLAND_COURTYARD,     {Category::cForestTemple, Category::cSkulltula,});
ItemLocation ForestTemple_MQ_GS_Well                      = ItemLocation::GSToken(0x03, 0x08, "Forest Temple MQ GS Well",                         FOREST_TEMPLE_MQ_GS_WELL,                     {Category::cForestTemple, Category::cSkulltula,});

ItemLocation FireTemple_GS_SongOfTimeRoom                 = ItemLocation::GSToken(0x04, 0x01, "Fire Temple GS Song of Time Room",                 FIRE_TEMPLE_GS_SONG_OF_TIME_ROOM,                {Category::cFireTemple, Category::cSkulltula,});
ItemLocation FireTemple_GS_BossKeyLoop                    = ItemLocation::GSToken(0x04, 0x02, "Fire Temple GS Boss Key Loop",                     FIRE_TEMPLE_GS_BOSS_KEY_LOOP,                   {Category::cFireTemple, Category::cSkulltula,});
ItemLocation FireTemple_GS_BoulderMaze                    = ItemLocation::GSToken(0x04, 0x04, "Fire Temple GS Boulder Maze",                      FIRE_TEMPLE_GS_BOULDER_MAZE,                   {Category::cFireTemple, Category::cSkulltula,});
ItemLocation FireTemple_GS_ScarecrowTop                   = ItemLocation::GSToken(0x04, 0x08, "Fire Temple GS Scarecrow Top",                     FIRE_TEMPLE_GS_SCARECROW_TOP,                  {Category::cFireTemple, Category::cSkulltula,});
ItemLocation FireTemple_GS_ScarecrowClimb                 = ItemLocation::GSToken(0x04, 0x10, "Fire Temple GS Scarecrow Climb",                   FIRE_TEMPLE_GS_SCARECROW_CLIMB,                {Category::cFireTemple, Category::cSkulltula,});

ItemLocation FireTemple_MQ_GS_AboveFireWallMaze           = ItemLocation::GSToken(0x04, 0x02, "Fire Temple MQ GS Above Fire Wall Maze",           FIRE_TEMPLE_MQ_GS_ABOVE_FIRE_WALL_MAZE,          {Category::cFireTemple, Category::cSkulltula,});
ItemLocation FireTemple_MQ_GS_FireWallMazeCenter          = ItemLocation::GSToken(0x04, 0x08, "Fire Temple MQ GS Fire Wall Maze Center",          FIRE_TEMPLE_MQ_GS_FIRE_WALL_MAZE_CENTER,         {Category::cFireTemple, Category::cSkulltula,});
ItemLocation FireTemple_MQ_GS_BigLavaRoomOpenDoor         = ItemLocation::GSToken(0x04, 0x01, "Fire Temple MQ GS Big Lava Room Open Door",        FIRE_TEMPLE_MQ_GS_BIG_LAVA_ROOM_OPEN_DOOR,        {Category::cFireTemple, Category::cSkulltula,});
ItemLocation FireTemple_MQ_GS_FireWallMazeSideRoom        = ItemLocation::GSToken(0x04, 0x10, "Fire Temple MQ GS Fire Wall Maze Side Room",       FIRE_TEMPLE_MQ_GS_FIRE_WALL_MAZE_SIDE_ROOM,       {Category::cFireTemple, Category::cSkulltula,});
ItemLocation FireTemple_MQ_GS_SkullOnFire                 = ItemLocation::GSToken(0x04, 0x04, "Fire Temple MQ GS Skull on Fire",                  FIRE_TEMPLE_MQ_GS_SKULL_ON_FIRE,                {Category::cFireTemple, Category::cSkulltula,});

ItemLocation WaterTemple_GS_BehindGate                    = ItemLocation::GSToken(0x05, 0x01, "Water Temple GS Behind Gate",                      WATER_TEMPLE_GS_BEHIND_GATE,                   {Category::cWaterTemple, Category::cSkulltula,});
ItemLocation WaterTemple_GS_FallingPlatformRoom           = ItemLocation::GSToken(0x05, 0x02, "Water Temple GS Falling Platform Room",            WATER_TEMPLE_GS_FALLING_PLATFORM_ROOM,          {Category::cWaterTemple, Category::cSkulltula,});
ItemLocation WaterTemple_GS_CentralPillar                 = ItemLocation::GSToken(0x05, 0x04, "Water Temple GS Central Pillar",                   WATER_TEMPLE_GS_CENTRAL_PILLAR,                {Category::cWaterTemple, Category::cSkulltula,});
ItemLocation WaterTemple_GS_NearBossKeyChest              = ItemLocation::GSToken(0x05, 0x08, "Water Temple GS Near Boss Key Chest",              WATER_TEMPLE_GS_NEAR_BOSS_KEY_CHEST,             {Category::cWaterTemple, Category::cSkulltula,});
ItemLocation WaterTemple_GS_River                         = ItemLocation::GSToken(0x05, 0x10, "Water Temple GS River",                            WATER_TEMPLE_GS_RIVER,                        {Category::cWaterTemple, Category::cSkulltula,});

ItemLocation WaterTemple_MQ_GS_BeforeUpperWaterSwitch     = ItemLocation::GSToken(0x05, 0x04, "Water Temple MQ GS Before Upper Water Switch",     WATER_TEMPLE_MQ_GS_BEFORE_UPPER_WATER_SWITCH,    {Category::cWaterTemple, Category::cSkulltula,});
ItemLocation WaterTemple_MQ_GS_FreestandingKeyArea        = ItemLocation::GSToken(0x05, 0x08, "Water Temple MQ GS Freestanding Key Area",         WATER_TEMPLE_MQ_GS_FREESTANDING_KEY_AREA,       {Category::cWaterTemple, Category::cSkulltula,});
ItemLocation WaterTemple_MQ_GS_LizalfosHallway            = ItemLocation::GSToken(0x05, 0x01, "Water Temple MQ GS Lizalfos Hallway",              WATER_TEMPLE_MQ_GS_LIZALFOS_HALLWAY,           {Category::cWaterTemple, Category::cSkulltula,});
ItemLocation WaterTemple_MQ_GS_River                      = ItemLocation::GSToken(0x05, 0x02, "Water Temple MQ GS River",                         WATER_TEMPLE_MQ_GS_RIVER,                     {Category::cWaterTemple, Category::cSkulltula,});
ItemLocation WaterTemple_MQ_GS_TripleWallTorch            = ItemLocation::GSToken(0x05, 0x10, "Water Temple MQ GS Triple Wall Torch",             WATER_TEMPLE_MQ_GS_TRIPLE_WALL_TORCH,           {Category::cWaterTemple, Category::cSkulltula,});

ItemLocation SpiritTemple_GS_HallAfterSunBlockRoom        = ItemLocation::GSToken(0x06, 0x01, "Spirit Temple GS Hall After Sun Block Room",       SPIRIT_TEMPLE_GS_HALL_AFTER_SUN_BLOCK_ROOM,       {Category::cSpiritTemple, Category::cSkulltula});
ItemLocation SpiritTemple_GS_BoulderRoom                  = ItemLocation::GSToken(0x06, 0x02, "Spirit Temple GS Boulder Room",                    SPIRIT_TEMPLE_GS_BOULDER_ROOM,                 {Category::cSpiritTemple, Category::cSkulltula});
ItemLocation SpiritTemple_GS_Lobby                        = ItemLocation::GSToken(0x06, 0x04, "Spirit Temple GS Lobby",                           SPIRIT_TEMPLE_GS_LOBBY,                       {Category::cSpiritTemple, Category::cSkulltula});
ItemLocation SpiritTemple_GS_SunOnFloorRoom               = ItemLocation::GSToken(0x06, 0x08, "Spirit Temple GS Sun on Floor Room",               SPIRIT_TEMPLE_GS_SUN_ON_FLOOR_ROOM,              {Category::cSpiritTemple, Category::cSkulltula});
ItemLocation SpiritTemple_GS_MetalFence                   = ItemLocation::GSToken(0x06, 0x10, "Spirit Temple GS Metal Fence",                     SPIRIT_TEMPLE_GS_METAL_FENCE,                  {Category::cSpiritTemple, Category::cSkulltula});

ItemLocation SpiritTemple_MQ_GS_SymphonyRoom              = ItemLocation::GSToken(0x06, 0x08, "Spirit Temple MQ GS Symphony Room",                SPIRIT_TEMPLE_MQ_GS_SYMPHONY_ROOM,             {Category::cSpiritTemple, Category::cSkulltula});
ItemLocation SpiritTemple_MQ_GS_LeeverRoom                = ItemLocation::GSToken(0x06, 0x02, "Spirit Temple MQ GS Leever Room",                  SPIRIT_TEMPLE_MQ_GS_LEEVER_ROOM,               {Category::cSpiritTemple, Category::cSkulltula});
ItemLocation SpiritTemple_MQ_GS_NineThronesRoomWest       = ItemLocation::GSToken(0x06, 0x04, "Spirit Temple MQ GS Nine Thrones Room West",       SPIRIT_TEMPLE_MQ_GS_NINE_THRONES_ROOM_WEST,      {Category::cSpiritTemple, Category::cSkulltula});
ItemLocation SpiritTemple_MQ_GS_NineThronesRoomNorth      = ItemLocation::GSToken(0x06, 0x10, "Spirit Temple MQ GS Nine Thrones Room North",      SPIRIT_TEMPLE_MQ_GS_NINE_THRONES_ROOM_NORTH,     {Category::cSpiritTemple, Category::cSkulltula});
ItemLocation SpiritTemple_MQ_GS_SunBlockRoom              = ItemLocation::GSToken(0x06, 0x01, "Spirit Temple MQ GS Sun Block Room",               SPIRIT_TEMPLE_MQ_GS_SUN_BLOCK_ROOM,             {Category::cSpiritTemple, Category::cSkulltula});

ItemLocation ShadowTemple_GS_SingleGiantPot               = ItemLocation::GSToken(0x07, 0x01, "Shadow Temple GS Single Giant Pot",                SHADOW_TEMPLE_GS_SINGLE_GIANT_POT,              {Category::cShadowTemple, Category::cSkulltula,});
ItemLocation ShadowTemple_GS_FallingSpikesRoom            = ItemLocation::GSToken(0x07, 0x02, "Shadow Temple GS Falling Spikes Room",             SHADOW_TEMPLE_GS_FALLING_SPIKES_ROOM,           {Category::cShadowTemple, Category::cSkulltula,});
ItemLocation ShadowTemple_GS_TripleGiantPot               = ItemLocation::GSToken(0x07, 0x04, "Shadow Temple GS Triple Giant Pot",                SHADOW_TEMPLE_GS_TRIPLE_GIANT_POT,              {Category::cShadowTemple, Category::cSkulltula,});
ItemLocation ShadowTemple_GS_LikeLikeRoom                 = ItemLocation::GSToken(0x07, 0x08, "Shadow Temple GS Like Like Room",                  SHADOW_TEMPLE_GS_LIKE_LIKE_ROOM,                {Category::cShadowTemple, Category::cSkulltula,});
ItemLocation ShadowTemple_GS_NearShip                     = ItemLocation::GSToken(0x07, 0x10, "Shadow Temple GS Near Ship",                       SHADOW_TEMPLE_GS_NEAR_SHIP,                    {Category::cShadowTemple, Category::cSkulltula,});

ItemLocation ShadowTemple_MQ_GS_FallingSpikesRoom         = ItemLocation::GSToken(0x07, 0x02, "Shadow Temple MQ GS Falling Spikes Room",          SHADOW_TEMPLE_MQ_GS_FALLING_SPIKES_ROOM,        {Category::cShadowTemple, Category::cSkulltula,});
ItemLocation ShadowTemple_MQ_GS_WindHintRoom              = ItemLocation::GSToken(0x07, 0x01, "Shadow Temple MQ GS Wind Hint Room",               SHADOW_TEMPLE_MQ_GS_WIND_HINT_ROOM,             {Category::cShadowTemple, Category::cSkulltula,});
ItemLocation ShadowTemple_MQ_GS_AfterWind                 = ItemLocation::GSToken(0x07, 0x08, "Shadow Temple MQ GS After Wind",                   SHADOW_TEMPLE_MQ_GS_AFTER_WIND,                {Category::cShadowTemple, Category::cSkulltula,});
ItemLocation ShadowTemple_MQ_GS_AfterShip                 = ItemLocation::GSToken(0x07, 0x10, "Shadow Temple MQ GS After Ship",                   SHADOW_TEMPLE_MQ_GS_AFTER_SHIP,                {Category::cShadowTemple, Category::cSkulltula,});
ItemLocation ShadowTemple_MQ_GS_NearBoss                  = ItemLocation::GSToken(0x07, 0x04, "Shadow Temple MQ GS Near Boss",                    SHADOW_TEMPLE_MQ_GS_NEAR_BOSS,                 {Category::cShadowTemple, Category::cSkulltula,});

ItemLocation BottomOfTheWell_GS_LikeLikeCage              = ItemLocation::GSToken(0x08, 0x01, "Bottom of the Well GS Like Like Cage",             BOTTOM_OF_THE_WELL_GS_LIKE_LIKE_CAGE,             {Category::cBottomOfTheWell, Category::cSkulltula,});
ItemLocation BottomOfTheWell_GS_EastInnerRoom             = ItemLocation::GSToken(0x08, 0x02, "Bottom of the Well GS East Inner Room",            BOTTOM_OF_THE_WELL_GS_EAST_INNER_ROOM,            {Category::cBottomOfTheWell, Category::cSkulltula,});
ItemLocation BottomOfTheWell_GS_WestInnerRoom             = ItemLocation::GSToken(0x08, 0x04, "Bottom of the Well GS West Inner Room",            BOTTOM_OF_THE_WELL_GS_WEST_INNER_ROOM,            {Category::cBottomOfTheWell, Category::cSkulltula,});

ItemLocation BottomOfTheWell_MQ_GS_Basement               = ItemLocation::GSToken(0x08, 0x01, "Bottom of the Well MQ GS Basement",                BOTTOM_OF_THE_WELL_MQ_GS_BASEMENT,              {Category::cBottomOfTheWell, Category::cSkulltula,});
ItemLocation BottomOfTheWell_MQ_GS_CoffinRoom             = ItemLocation::GSToken(0x08, 0x04, "Bottom of the Well MQ GS Coffin Room",             BOTTOM_OF_THE_WELL_MQ_GS_COFFIN_ROOM,            {Category::cBottomOfTheWell, Category::cSkulltula,});
ItemLocation BottomOfTheWell_MQ_GS_WestInnerRoom          = ItemLocation::GSToken(0x08, 0x02, "Bottom of the Well MQ GS West Inner Room",         BOTTOM_OF_THE_WELL_MQ_GS_WEST_INNER_ROOM,         {Category::cBottomOfTheWell, Category::cSkulltula,});

ItemLocation IceCavern_GS_PushBlockRoom                   = ItemLocation::GSToken(0x09, 0x01, "Ice Cavern GS Push Block Room",                    ICE_CAVERN_GS_PUSH_BLOCK_ROOM,                  {Category::cIceCavern, Category::cSkulltula,});
ItemLocation IceCavern_GS_SpinningScytheRoom              = ItemLocation::GSToken(0x09, 0x02, "Ice Cavern GS Spinning Scythe Room",               ICE_CAVERN_GS_SPINNING_SCYTHE_ROOM,             {Category::cIceCavern, Category::cSkulltula,});
ItemLocation IceCavern_GS_HeartPieceRoom                  = ItemLocation::GSToken(0x09, 0x04, "Ice Cavern GS Heart Piece Room",                   ICE_CAVERN_GS_HEART_PIECE_ROOM,                 {Category::cIceCavern, Category::cSkulltula,});

ItemLocation IceCavern_MQ_GS_Scarecrow                    = ItemLocation::GSToken(0x09, 0x01, "Ice Cavern MQ GS Scarecrow",                       ICE_CAVERN_MQ_GS_SCARECROW,                   {Category::cIceCavern, Category::cSkulltula,});
ItemLocation IceCavern_MQ_GS_IceBlock                     = ItemLocation::GSToken(0x09, 0x04, "Ice Cavern MQ GS Ice Block",                       ICE_CAVERN_MQ_GS_ICE_BLOCK,                    {Category::cIceCavern, Category::cSkulltula,});
ItemLocation IceCavern_MQ_GS_RedIce                       = ItemLocation::GSToken(0x09, 0x02, "Ice Cavern MQ GS Red Ice",                         ICE_CAVERN_MQ_GS_RED_ICE,                      {Category::cIceCavern, Category::cSkulltula,});

//Overworld
ItemLocation KF_GS_BeanPatch                              = ItemLocation::GSToken(0x0C, 0x01, "KF GS Bean Patch",                                 KF_GS_BEAN_PATCH,                             {Category::cKokiriForest, Category::cSkulltula,});
ItemLocation KF_GS_KnowItAllHouse                         = ItemLocation::GSToken(0x0C, 0x02, "KF GS Know It All House",                          KF_GS_KNOW_IT_ALL_HOUSE,                        {Category::cKokiriForest, Category::cSkulltula,});
ItemLocation KF_GS_HouseOfTwins                           = ItemLocation::GSToken(0x0C, 0x04, "KF GS House of Twins",                             KF_GS_HOUSE_OF_TWINS,                          {Category::cKokiriForest, Category::cSkulltula,});

ItemLocation LW_GS_BeanPatchNearBridge                    = ItemLocation::GSToken(0x0D, 0x01, "LW GS Bean Patch Near Bridge",                     LW_GS_BEAN_PATCH_NEAR_BRIDGE,                   {Category::cLostWoods, Category::cSkulltula,});
ItemLocation LW_GS_BeanPatchNearTheater                   = ItemLocation::GSToken(0x0D, 0x02, "LW GS Bean Patch Near Theater",                    LW_GS_BEAN_PATCH_NEAR_THEATER,                  {Category::cLostWoods, Category::cSkulltula,});
ItemLocation LW_GS_AboveTheater                           = ItemLocation::GSToken(0x0D, 0x04, "LW GS Above Theater",                              LW_GS_ABOVE_THEATER,                          {Category::cLostWoods, Category::cSkulltula,});
ItemLocation Meadow_GS                                    = ItemLocation::GSToken(0x0D, 0x08, "SFM GS",                                           SFM_GS,                                      {Category::cSacredForestMeadow, Category::cSkulltula,});

ItemLocation HF_GS_CowGrotto                              = ItemLocation::GSToken(0x0A, 0x01, "HF GS Cow Grotto",                                 HF_GS_COW_GROTTO,                             {Category::cHyruleField, Category::cSkulltula, Category::cGrotto});
ItemLocation HF_GS_NearKakGrotto                          = ItemLocation::GSToken(0x0A, 0x02, "HF GS Near Kak Grotto",                            HF_GS_NEAR_KAK_GROTTO,                         {Category::cHyruleField, Category::cSkulltula, Category::cGrotto});

ItemLocation LH_GS_BeanPatch                              = ItemLocation::GSToken(0x12, 0x01, "LH GS Bean Patch",                                 LH_GS_BEAN_PATCH,                             {Category::cLakeHylia, Category::cSkulltula,});
ItemLocation LH_GS_SmallIsland                            = ItemLocation::GSToken(0x12, 0x02, "LH GS Small Island",                               LH_GS_SMALL_ISLAND,                           {Category::cLakeHylia, Category::cSkulltula,});
ItemLocation LH_GS_LabWall                                = ItemLocation::GSToken(0x12, 0x04, "LH GS Lab Wall",                                   LH_GS_LAB_WALL,                               {Category::cLakeHylia, Category::cSkulltula,});
ItemLocation LH_GS_LabCrate                               = ItemLocation::GSToken(0x12, 0x08, "LH GS Lab Crate",                                  LH_GS_LAB_CRATE,                              {Category::cLakeHylia, Category::cSkulltula,});
ItemLocation LH_GS_Tree                                   = ItemLocation::GSToken(0x12, 0x10, "LH GS Tree",                                       LH_GS_TREE,                                  {Category::cLakeHylia, Category::cSkulltula,});

ItemLocation GV_GS_BeanPatch                              = ItemLocation::GSToken(0x13, 0x01, "GV GS Bean Patch",                                 GV_GS_BEAN_PATCH,                             {Category::cGerudoValley, Category::cSkulltula,});
ItemLocation GV_GS_SmallBridge                            = ItemLocation::GSToken(0x13, 0x02, "GV GS Small Bridge",                               GV_GS_SMALL_BRIDGE,                           {Category::cGerudoValley, Category::cSkulltula,});
ItemLocation GV_GS_Pillar                                 = ItemLocation::GSToken(0x13, 0x04, "GV GS Pillar",                                     GV_GS_PILLAR,                                {Category::cGerudoValley, Category::cSkulltula,});
ItemLocation GV_GS_BehindTent                             = ItemLocation::GSToken(0x13, 0x08, "GV GS Behind Tent",                                GV_GS_BEHIND_TENT,                            {Category::cGerudoValley, Category::cSkulltula,});

ItemLocation GF_GS_ArcheryRange                           = ItemLocation::GSToken(0x14, 0x01, "GF GS Archery Range",                              GF_GS_ARCHERY_RANGE,                          {Category::cGerudoFortress, Category::cSkulltula,});
ItemLocation GF_GS_TopFloor                               = ItemLocation::GSToken(0x14, 0x02, "GF GS Top Floor",                                  GF_GS_TOP_FLOOR,                              {Category::cGerudoFortress, Category::cSkulltula,});

ItemLocation HW_GS                                        = ItemLocation::GSToken(0x15, 0x02, "HW GS",                                            WASTELAND_GS,                                 {Category::cHauntedWasteland, Category::cSkulltula,});
ItemLocation Colossus_GS_BeanPatch                        = ItemLocation::GSToken(0x15, 0x01, "Colossus GS Bean Patch",                           COLOSSUS_GS_BEAN_PATCH,                       {Category::cDesertColossus, Category::cSkulltula,});
ItemLocation Colossus_GS_Hill                             = ItemLocation::GSToken(0x15, 0x04, "Colossus GS Hill",                                 COLOSSUS_GS_HILL,                            {Category::cDesertColossus, Category::cSkulltula,});
ItemLocation Colossus_GS_Tree                             = ItemLocation::GSToken(0x15, 0x08, "Colossus GS Tree",                                 COLOSSUS_GS_TREE,                            {Category::cDesertColossus, Category::cSkulltula,});

ItemLocation outsideGanonsCastle_GS                       = ItemLocation::GSToken(0x0E, 0x01, "OGC GS",                                           OGC_GS,                                      {Category::cOutsideGanonsCastle, Category::cSkulltula,});
ItemLocation HC_GS_StormsGrotto                           = ItemLocation::GSToken(0x0E, 0x02, "HC GS Storms Grotto",                              HC_GS_STORMS_GROTTO,                          {Category::cHyruleCastle, Category::cSkulltula, Category::cGrotto});
ItemLocation HC_GS_Tree                                   = ItemLocation::GSToken(0x0E, 0x04, "HC GS Tree",                                       HC_GS_TREE,                                  {Category::cHyruleCastle, Category::cSkulltula,});
ItemLocation MK_GS_GuardHouse                             = ItemLocation::GSToken(0x0E, 0x08, "Market GS Guard House",                            MARKET_GS_GUARD_HOUSE,                            {Category::cInnerMarket, Category::cSkulltula,});

ItemLocation Kak_GS_HouseUnderConstruction                = ItemLocation::GSToken(0x10, 0x08, "Kak GS House Under Construction",                  KAK_GS_HOUSE_UNDER_CONSTRUCTION,               {Category::cKakarikoVillage, Category::cSkulltula,});
ItemLocation Kak_GS_SkulltulaHouse                        = ItemLocation::GSToken(0x10, 0x10, "Kak GS Skulltula House",                           KAK_GS_SKULLTULA_HOUSE,                       {Category::cKakarikoVillage, Category::cSkulltula,});
ItemLocation Kak_GS_GuardsHouse                           = ItemLocation::GSToken(0x10, 0x02, "Kak GS Guards House",                              KAK_GS_GUARDS_HOUSE,                          {Category::cKakarikoVillage, Category::cSkulltula,});
ItemLocation Kak_GS_Tree                                  = ItemLocation::GSToken(0x10, 0x20, "Kak GS Tree",                                      KAK_GS_TREE,                                 {Category::cKakarikoVillage, Category::cSkulltula,});
ItemLocation Kak_GS_Watchtower                            = ItemLocation::GSToken(0x10, 0x04, "Kak GS Watchtower",                                KAK_GS_WATCHTOWER,                           {Category::cKakarikoVillage, Category::cSkulltula,});
ItemLocation Kak_GS_AboveImpasHouse                       = ItemLocation::GSToken(0x10, 0x40, "Kak GS Above Impas House",                         KAK_GS_ABOVE_IMPAS_HOUSE,                      {Category::cKakarikoVillage, Category::cSkulltula,});

ItemLocation GY_GS_Wall                                   = ItemLocation::GSToken(0x10, 0x80, "Graveyard GS Wall",                                GRAVEYARD_GS_WALL,                                  {Category::cGraveyard, Category::cSkulltula,});
ItemLocation GY_GS_BeanPatch                              = ItemLocation::GSToken(0x10, 0x01, "Graveyard GS Bean Patch",                          GRAVEYARD_GS_BEAN_PATCH,                             {Category::cGraveyard, Category::cSkulltula,});

ItemLocation DMC_GS_BeanPatch                             = ItemLocation::GSToken(0x0F, 0x01, "DMC GS Bean Patch",                                DMC_GS_BEAN_PATCH,                            {Category::cDeathMountainCrater, Category::cSkulltula,});
ItemLocation DMC_GS_Crate                                 = ItemLocation::GSToken(0x0F, 0x80, "DMC GS Crate",                                     DMC_GS_CRATE,                                {Category::cDeathMountainCrater, Category::cSkulltula,});

ItemLocation DMT_GS_BeanPatch                             = ItemLocation::GSToken(0x0F, 0x02, "DMT GS Bean Patch",                                DMT_GS_BEAN_PATCH,                            {Category::cDeathMountainTrail, Category::cSkulltula,});
ItemLocation DMT_GS_NearKak                               = ItemLocation::GSToken(0x0F, 0x04, "DMT GS Near Kak",                                  DMT_GS_NEAR_KAK,                              {Category::cDeathMountainTrail, Category::cSkulltula,});
ItemLocation DMT_GS_AboveDodongosCavern                   = ItemLocation::GSToken(0x0F, 0x08, "DMT GS Above Dodongos Cavern",                     DMT_GS_ABOVE_DODONGOS_CAVERN,                  {Category::cDeathMountainTrail, Category::cSkulltula,});
ItemLocation DMT_GS_FallingRocksPath                      = ItemLocation::GSToken(0x0F, 0x10, "DMT GS Falling Rocks Path",                        DMT_GS_FALLING_ROCKS_PATH,                     {Category::cDeathMountainTrail, Category::cSkulltula,});

ItemLocation GC_GS_CenterPlatform                         = ItemLocation::GSToken(0x0F, 0x20, "GC GS Center Platform",                            GC_GS_CENTER_PLATFORM,                        {Category::cGoronCity, Category::cSkulltula,});
ItemLocation GC_GS_BoulderMaze                            = ItemLocation::GSToken(0x0F, 0x40, "GC GS Boulder Maze",                               GC_GS_BOULDER_MAZE,                           {Category::cGoronCity, Category::cSkulltula,});

ItemLocation ZR_GS_Ladder                                 = ItemLocation::GSToken(0x11, 0x01, "ZR GS Ladder",                                     ZR_GS_LADDER,                                {Category::cZorasRiver, Category::cSkulltula,});
ItemLocation ZR_GS_Tree                                   = ItemLocation::GSToken(0x11, 0x02, "ZR GS Tree",                                       ZR_GS_TREE,                                  {Category::cZorasRiver, Category::cSkulltula,});
ItemLocation ZR_GS_AboveBridge                            = ItemLocation::GSToken(0x11, 0x08, "ZR GS Above Bridge",                               ZR_GS_ABOVE_BRIDGE,                           {Category::cZorasRiver, Category::cSkulltula,});
ItemLocation ZR_GS_NearRaisedGrottos                      = ItemLocation::GSToken(0x11, 0x10, "ZR GS Near Raised Grottos",                        ZR_GS_NEAR_RAISED_GROTTOS,                     {Category::cZorasRiver, Category::cSkulltula,});

ItemLocation ZD_GS_FrozenWaterfall                        = ItemLocation::GSToken(0x11, 0x40, "ZD GS Frozen Waterfall",                           ZD_GS_FROZEN_WATERFALL,                       {Category::cZorasDomain, Category::cSkulltula,});
ItemLocation ZF_GS_AboveTheLog                            = ItemLocation::GSToken(0x11, 0x04, "ZF GS Above The Log",                              ZF_GS_ABOVE_THE_LOG,                           {Category::cZorasFountain, Category::cSkulltula,});
ItemLocation ZF_GS_HiddenCave                             = ItemLocation::GSToken(0x11, 0x20, "ZF GS Hidden Cave",                                ZF_GS_HIDDEN_CAVE,                            {Category::cZorasFountain, Category::cSkulltula,});
ItemLocation ZF_GS_Tree                                   = ItemLocation::GSToken(0x11, 0x80, "ZF GS Tree",                                       ZF_GS_TREE,                                  {Category::cZorasFountain, Category::cSkulltula,});

ItemLocation LLR_GS_BackWall                              = ItemLocation::GSToken(0x0B, 0x01, "LLR GS Back Wall",                                 LLR_GS_BACK_WALL,                             {Category::cLonLonRanch, Category::cSkulltula,});
ItemLocation LLR_GS_RainShed                              = ItemLocation::GSToken(0x0B, 0x02, "LLR GS Rain Shed",                                 LLR_GS_RAIN_SHED,                             {Category::cLonLonRanch, Category::cSkulltula,});
ItemLocation LLR_GS_HouseWindow                           = ItemLocation::GSToken(0x0B, 0x04, "LLR GS House Window",                              LLR_GS_HOUSE_WINDOW,                          {Category::cLonLonRanch, Category::cSkulltula,});
ItemLocation LLR_GS_Tree                                  = ItemLocation::GSToken(0x0B, 0x08, "LLR GS Tree",                                      LLR_GS_TREE,                                 {Category::cLonLonRanch, Category::cSkulltula,});

/*-------------------------------
          --- BOSSES ---
  -------------------------------*/

ItemLocation LinksPocket                                  = ItemLocation::Reward (0xFF, 0xFF,                    "Link's Pocket",               LINKS_POCKET,                     {});
ItemLocation QueenGohma                                   = ItemLocation::Reward (0xFF, DUNGEON_DEKU_TREE,       "Queen Gohma",                 QUEEN_GOHMA,                      {});
ItemLocation KingDodongo                                  = ItemLocation::Reward (0xFF, DUNGEON_DODONGOS_CAVERN, "King Dodongo",                KING_DODONGO,                     {});
ItemLocation Barinade                                     = ItemLocation::Reward (0xFF, DUNGEON_JABUJABUS_BELLY, "Barinade",                    BARINADE,                         {});
ItemLocation PhantomGanon                                 = ItemLocation::Reward (0xFF, DUNGEON_FOREST_TEMPLE,   "Phantom Ganon",               PHANTOM_GANON,                    {});
ItemLocation Volvagia                                     = ItemLocation::Reward (0xFF, DUNGEON_FIRE_TEMPLE,     "Volvagia",                    VOLVAGIA,                         {});
ItemLocation Morpha                                       = ItemLocation::Reward (0xFF, DUNGEON_WATER_TEMPLE,    "Morpha",                      MORPHA,                           {});
ItemLocation Twinrova                                     = ItemLocation::Reward (0xFF, DUNGEON_SPIRIT_TEMPLE,   "Twinrova",                    TWINROVA,                         {});
ItemLocation BongoBongo                                   = ItemLocation::Reward (0xFF, DUNGEON_SHADOW_TEMPLE,   "Bongo Bongo",                 BONGO_BONGO,                      {});
ItemLocation Ganon                                        = ItemLocation::Reward (0xFF, 0xF0,                    "Ganon",                       NONE,                             {});

/*-------------------------------
      ---HEART CONTAINERS ---
  -------------------------------*/

ItemLocation DekuTree_QueenGohmaHeart                     = ItemLocation::Base   (0x11, 0x4F, "Deku Tree Queen Gohma Heart Container",          DEKU_TREE_QUEEN_GOHMA_HEART,        {Category::cDekuTree, Category::cBossHeart, Category::cSongDungeonReward});
ItemLocation DodongosCavern_KingDodongoHeart              = ItemLocation::Base   (0x12, 0x4F, "Dodongos Cavern King Dodongo Heart Container",   DODONGOS_CAVERN_KING_DODONGO_HEART, {Category::cDodongosCavern, Category::cBossHeart, Category::cSongDungeonReward});
ItemLocation JabuJabusBelly_BarinadeHeart                 = ItemLocation::Base   (0x13, 0x4F, "Jabu Jabus Belly Barinade Heart Container",      JABU_JABUS_BELLY_BARINADE_HEART,    {Category::cJabuJabusBelly, Category::cBossHeart, Category::cSongDungeonReward});
ItemLocation ForestTemple_PhantomGanonHeart               = ItemLocation::Base   (0x14, 0x4F, "Forest Temple Phantom Ganon Heart Container",    FOREST_TEMPLE_PHANTOM_GANON_HEART,  {Category::cForestTemple, Category::cBossHeart, Category::cSongDungeonReward});
ItemLocation FireTemple_VolvagiaHeart                     = ItemLocation::Base   (0x15, 0x4F, "Fire Temple Volvagia Heart Container",           FIRE_TEMPLE_VOLVAGIA_HEART,        {Category::cFireTemple, Category::cBossHeart, Category::cSongDungeonReward});
ItemLocation WaterTemple_MorphaHeart                      = ItemLocation::Base   (0x16, 0x4F, "Water Temple Morpha Heart Container",            WATER_TEMPLE_MORPHA_HEART,         {Category::cWaterTemple, Category::cBossHeart, Category::cSongDungeonReward});
ItemLocation SpiritTemple_TwinrovaHeart                   = ItemLocation::Base   (0x17, 0x4F, "Spirit Temple Twinrova Heart Container",         SPIRIT_TEMPLE_TWINROVA_HEART,      {Category::cSpiritTemple, Category::cBossHeart, Category::cSongDungeonReward});
ItemLocation ShadowTemple_BongoBongoHeart                 = ItemLocation::Base   (0x18, 0x4F, "Shadow Temple Bongo Bongo Heart Container",      SHADOW_TEMPLE_BONGO_BONGO_HEART,    {Category::cShadowTemple, Category::cBossHeart, Category::cSongDungeonReward});

/*-------------------------------
        --- CUTSCENES ---
  -------------------------------*/

ItemLocation ToT_LightArrowCutscene                       = ItemLocation::Delayed(0xFF, 0x01, "ToT Light Arrow Cutscene",                       TOT_LIGHT_ARROWS_CUTSCENE,          {Category::cTempleOfTime, Category::cMarket});
ItemLocation LW_GiftFromSaria                             = ItemLocation::Delayed(0xFF, 0x02, "LW Gift From Saria",                             LW_GIFT_FROM_SARIA,                {Category::cLostWoods, Category::cForest});
ItemLocation ZF_GreatFairyReward                          = ItemLocation::Delayed(0xFF, 0x10, "ZF Great Fairy Reward",                          ZF_GREAT_FAIRY_REWARD,             {Category::cZorasFountain, Category::cFairies});
ItemLocation HC_GreatFairyReward                          = ItemLocation::Delayed(0xFF, 0x11, "HC Great Fairy Reward",                          HC_GREAT_FAIRY_REWARD,             {Category::cHyruleCastle, Category::cMarket, Category::cFairies});
ItemLocation Colossus_GreatFairyReward                    = ItemLocation::Delayed(0xFF, 0x12, "Colossus Great Fairy Reward",                    COLOSSUS_GREAT_FAIRY_REWARD,       {Category::cDesertColossus, Category::cFairies});
ItemLocation DMT_GreatFairyReward                         = ItemLocation::Delayed(0xFF, 0x13, "DMT Great Fairy Reward",                         DMT_GREAT_FAIRY_REWARD,            {Category::cDeathMountainTrail, Category::cDeathMountain, Category::cFairies});
ItemLocation DMC_GreatFairyReward                         = ItemLocation::Delayed(0xFF, 0x14, "DMC Great Fairy Reward",                         DMC_GREAT_FAIRY_REWARD,            {Category::cDeathMountainCrater, Category::cDeathMountain, Category::cFairies});
ItemLocation OGC_GreatFairyReward                         = ItemLocation::Delayed(0xFF, 0x15, "OGC Great Fairy Reward",                         OGC_GREAT_FAIRY_REWARD,            {Category::cOutsideGanonsCastle, Category::cMarket, Category::cFairies});

ItemLocation SheikInForest                                = ItemLocation::Delayed(0xFF, 0x20, "Sheik in Forest",                                SHEIK_IN_FOREST,                   {Category::cSacredForestMeadow, Category::cForest, Category::cSong,});
ItemLocation SheikInCrater                                = ItemLocation::Delayed(0xFF, 0x21, "Sheik in Crater",                                SHEIK_IN_CRATER,                   {Category::cDeathMountainCrater, Category::cDeathMountain, Category::cSong,});
ItemLocation SheikInIceCavern                             = ItemLocation::Delayed(0xFF, 0x22, "Sheik in Ice Cavern",                            SHEIK_IN_ICE_CAVERN,                {Category::cIceCavern, Category::cSong, Category::cSongDungeonReward});
ItemLocation SheikAtColossus                              = ItemLocation::Delayed(0xFF, 0x23, "Sheik at Colossus",                              SHEIK_AT_COLOSSUS,                 {Category::cDesertColossus, Category::cSong,});
ItemLocation SheikInKakariko                              = ItemLocation::Delayed(0xFF, 0x24, "Sheik in Kakariko",                              SHEIK_IN_KAKARIKO,                 {Category::cKakarikoVillage, Category::cKakariko, Category::cSong,});
ItemLocation SheikAtTemple                                = ItemLocation::Delayed(0xFF, 0x25, "Sheik at Temple",                                SHEIK_AT_TEMPLE,                   {Category::cTempleOfTime, Category::cMarket, Category::cSong,});
ItemLocation SongFromImpa                                 = ItemLocation::Delayed(0xFF, 0x26, "Song from Impa",                                 SONG_FROM_IMPA,                    {Category::cHyruleCastle, Category::cMarket, Category::cSong, Category::cSongDungeonReward});
ItemLocation SongFromMalon                                = ItemLocation::Delayed(0xFF, 0x27, "Song from Malon",                                SONG_FROM_MALON,                   {Category::cLonLonRanch, Category::cSong,});
ItemLocation SongFromSaria                                = ItemLocation::Delayed(0xFF, 0x28, "Song from Saria",                                SONG_FROM_SARIA,                   {Category::cSacredForestMeadow, Category::cForest, Category::cSong,});
ItemLocation SongFromComposersGrave                       = ItemLocation::Delayed(0xFF, 0x29, "Song from Composers Grave",                      SONG_FROM_COMPOSERS_GRAVE,          {Category::cGraveyard, Category::cKakariko, Category::cSong,});
ItemLocation SongFromOcarinaOfTime                        = ItemLocation::Delayed(0xFF, 0x2A, "Song from Ocarina of Time",                      SONG_FROM_OCARINA_OF_TIME,           {Category::cHyruleField, Category::cSong, Category::cNeedSpiritualStones,});
ItemLocation SongFromWindmill                             = ItemLocation::Delayed(0xFF, 0x2B, "Song from Windmill",                             SONG_FROM_WINDMILL,                {Category::cKakarikoVillage, Category::cKakariko, Category::cSong,});

/*-------------------------------
           --- COWS ---
  -------------------------------*/

ItemLocation KF_LinksHouseCow                             = ItemLocation::Base   (0x34, 0x15, "KF Links House Cow",                             KF_LINKS_HOUSE_COW,                {Category::cForest, Category::cCow, Category::cMinigame});
ItemLocation HF_CowGrottoCow                              = ItemLocation::Base   (0x3E, 0x16, "HF Cow Grotto Cow",                              HF_COW_GROTTO_COW,                 {Category::cHyruleField, Category::cCow, Category::cGrotto});
ItemLocation LLR_StablesLeftCow                           = ItemLocation::Base   (0x36, 0x16, "LLR Stables Left Cow",                           LLR_STABLES_LEFT_COW,              {Category::cLonLonRanch, Category::cCow});
ItemLocation LLR_StablesRightCow                          = ItemLocation::Base   (0x36, 0x15, "LLR Stables Right Cow",                          LLR_STABLES_RIGHT_COW,             {Category::cLonLonRanch, Category::cCow});
ItemLocation LLR_TowerLeftCow                             = ItemLocation::Base   (0x4C, 0x16, "LLR Tower Left Cow",                             LLR_TOWER_LEFT_COW,                {Category::cLonLonRanch, Category::cCow});
ItemLocation LLR_TowerRightCow                            = ItemLocation::Base   (0x4C, 0x15, "LLR Tower Right Cow",                            LLR_TOWER_RIGHT_COW,               {Category::cLonLonRanch, Category::cCow});
ItemLocation Kak_ImpasHouseCow                            = ItemLocation::Base   (0x37, 0x15, "Kak Impas House Cow",                            KAK_IMPAS_HOUSE_COW,               {Category::cKakarikoVillage, Category::cKakariko, Category::cCow});
ItemLocation DMT_CowGrottoCow                             = ItemLocation::Base   (0x3E, 0x15, "DMT Cow Grotto Cow",                             DMT_COW_GROTTO_COW,                {Category::cDeathMountainTrail, Category::cDeathMountain, Category::cCow, Category::cGrotto});
ItemLocation GV_Cow                                       = ItemLocation::Base   (0x5A, 0x15, "GV Cow",                                         GV_COW,                          {Category::cGerudoValley, Category::cGerudo, Category::cCow});
ItemLocation JabuJabusBelly_MQ_Cow                        = ItemLocation::Base   (0x02, 0x15, "Jabu Jabus Belly MQ Cow",                        JABU_JABUS_BELLY_MQ_COW,           {Category::cJabuJabusBelly, Category::cCow});

/*-------------------------------
          --- SHOPS ---
  8     6               2     4

  7     5               1     3
  -------------------------------*/

ItemLocation KF_ShopItem1                                 = ItemLocation::Base(0x2D, 0x30, "KF Shop Item 1",                                   KF_SHOP_ITEM_1,        {Category::cKokiriForest, Category::cForest, Category::cShop});
ItemLocation KF_ShopItem2                                 = ItemLocation::Base(0x2D, 0x31, "KF Shop Item 2",                                   KF_SHOP_ITEM_2,        {Category::cKokiriForest, Category::cForest, Category::cShop});
ItemLocation KF_ShopItem3                                 = ItemLocation::Base(0x2D, 0x32, "KF Shop Item 3",                                   KF_SHOP_ITEM_3,        {Category::cKokiriForest, Category::cForest, Category::cShop});
ItemLocation KF_ShopItem4                                 = ItemLocation::Base(0x2D, 0x33, "KF Shop Item 4",                                   KF_SHOP_ITEM_4,        {Category::cKokiriForest, Category::cForest, Category::cShop});
ItemLocation KF_ShopItem5                                 = ItemLocation::Base(0x2D, 0x34, "KF Shop Item 5",                                   KF_SHOP_ITEM_5,        {Category::cKokiriForest, Category::cForest, Category::cShop});
ItemLocation KF_ShopItem6                                 = ItemLocation::Base(0x2D, 0x35, "KF Shop Item 6",                                   KF_SHOP_ITEM_6,        {Category::cKokiriForest, Category::cForest, Category::cShop});
ItemLocation KF_ShopItem7                                 = ItemLocation::Base(0x2D, 0x36, "KF Shop Item 7",                                   KF_SHOP_ITEM_7,        {Category::cKokiriForest, Category::cForest, Category::cShop});
ItemLocation KF_ShopItem8                                 = ItemLocation::Base(0x2D, 0x37, "KF Shop Item 8",                                   KF_SHOP_ITEM_8,        {Category::cKokiriForest, Category::cForest, Category::cShop});
std::vector<ItemLocation*> KF_ShopLocations = {
  &KF_ShopItem1,
  &KF_ShopItem2,
  &KF_ShopItem3,
  &KF_ShopItem4,
  &KF_ShopItem5,
  &KF_ShopItem6,
  &KF_ShopItem7,
  &KF_ShopItem8,
};

ItemLocation Kak_PotionShopItem1                          = ItemLocation::Base(0x30, 0x30, "Kak Potion Shop Item 1",                           KAK_POTION_SHOP_ITEM_1, {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_PotionShopItem2                          = ItemLocation::Base(0x30, 0x31, "Kak Potion Shop Item 2",                           KAK_POTION_SHOP_ITEM_2, {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_PotionShopItem3                          = ItemLocation::Base(0x30, 0x32, "Kak Potion Shop Item 3",                           KAK_POTION_SHOP_ITEM_3, {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_PotionShopItem4                          = ItemLocation::Base(0x30, 0x33, "Kak Potion Shop Item 4",                           KAK_POTION_SHOP_ITEM_4, {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_PotionShopItem5                          = ItemLocation::Base(0x30, 0x34, "Kak Potion Shop Item 5",                           KAK_POTION_SHOP_ITEM_5, {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_PotionShopItem6                          = ItemLocation::Base(0x30, 0x35, "Kak Potion Shop Item 6",                           KAK_POTION_SHOP_ITEM_6, {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_PotionShopItem7                          = ItemLocation::Base(0x30, 0x36, "Kak Potion Shop Item 7",                           KAK_POTION_SHOP_ITEM_7, {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_PotionShopItem8                          = ItemLocation::Base(0x30, 0x37, "Kak Potion Shop Item 8",                           KAK_POTION_SHOP_ITEM_8, {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
std::vector<ItemLocation*> Kak_PotionShopLocations = {
  &Kak_PotionShopItem1,
  &Kak_PotionShopItem2,
  &Kak_PotionShopItem3,
  &Kak_PotionShopItem4,
  &Kak_PotionShopItem5,
  &Kak_PotionShopItem6,
  &Kak_PotionShopItem7,
  &Kak_PotionShopItem8,
};

ItemLocation MK_BombchuShopItem1                          = ItemLocation::Base(0x32, 0x30, "MK Bombchu Shop Item 1",                           MARKET_BOMBCHU_SHOP_ITEM_1, {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BombchuShopItem2                          = ItemLocation::Base(0x32, 0x31, "MK Bombchu Shop Item 2",                           MARKET_BOMBCHU_SHOP_ITEM_2, {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BombchuShopItem3                          = ItemLocation::Base(0x32, 0x32, "MK Bombchu Shop Item 3",                           MARKET_BOMBCHU_SHOP_ITEM_3, {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BombchuShopItem4                          = ItemLocation::Base(0x32, 0x33, "MK Bombchu Shop Item 4",                           MARKET_BOMBCHU_SHOP_ITEM_4, {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BombchuShopItem5                          = ItemLocation::Base(0x32, 0x34, "MK Bombchu Shop Item 5",                           MARKET_BOMBCHU_SHOP_ITEM_5, {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BombchuShopItem6                          = ItemLocation::Base(0x32, 0x35, "MK Bombchu Shop Item 6",                           MARKET_BOMBCHU_SHOP_ITEM_6, {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BombchuShopItem7                          = ItemLocation::Base(0x32, 0x36, "MK Bombchu Shop Item 7",                           MARKET_BOMBCHU_SHOP_ITEM_7, {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BombchuShopItem8                          = ItemLocation::Base(0x32, 0x37, "MK Bombchu Shop Item 8",                           MARKET_BOMBCHU_SHOP_ITEM_8, {Category::cInnerMarket, Category::cMarket, Category::cShop});
std::vector<ItemLocation*> MK_BombchuShopLocations = {
  &MK_BombchuShopItem1,
  &MK_BombchuShopItem2,
  &MK_BombchuShopItem3,
  &MK_BombchuShopItem4,
  &MK_BombchuShopItem5,
  &MK_BombchuShopItem6,
  &MK_BombchuShopItem7,
  &MK_BombchuShopItem8,
};

ItemLocation MK_PotionShopItem1                           = ItemLocation::Base(0x31, 0x30, "MK Potion Shop Item 1",                            MARKET_POTION_SHOP_ITEM_1,  {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_PotionShopItem2                           = ItemLocation::Base(0x31, 0x31, "MK Potion Shop Item 2",                            MARKET_POTION_SHOP_ITEM_2,  {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_PotionShopItem3                           = ItemLocation::Base(0x31, 0x32, "MK Potion Shop Item 3",                            MARKET_POTION_SHOP_ITEM_3,  {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_PotionShopItem4                           = ItemLocation::Base(0x31, 0x33, "MK Potion Shop Item 4",                            MARKET_POTION_SHOP_ITEM_4,  {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_PotionShopItem5                           = ItemLocation::Base(0x31, 0x34, "MK Potion Shop Item 5",                            MARKET_POTION_SHOP_ITEM_5,  {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_PotionShopItem6                           = ItemLocation::Base(0x31, 0x35, "MK Potion Shop Item 6",                            MARKET_POTION_SHOP_ITEM_6,  {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_PotionShopItem7                           = ItemLocation::Base(0x31, 0x36, "MK Potion Shop Item 7",                            MARKET_POTION_SHOP_ITEM_7,  {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_PotionShopItem8                           = ItemLocation::Base(0x31, 0x37, "MK Potion Shop Item 8",                            MARKET_POTION_SHOP_ITEM_8,  {Category::cInnerMarket, Category::cMarket, Category::cShop});
std::vector<ItemLocation*> MK_PotionShopLocations = {
  &MK_PotionShopItem1,
  &MK_PotionShopItem2,
  &MK_PotionShopItem3,
  &MK_PotionShopItem4,
  &MK_PotionShopItem5,
  &MK_PotionShopItem6,
  &MK_PotionShopItem7,
  &MK_PotionShopItem8,
};

ItemLocation MK_BazaarItem1                               = ItemLocation::Base(0x2C, 0x30, "MK Bazaar Item 1",                                 MARKET_BAZAAR_ITEM_1,      {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BazaarItem2                               = ItemLocation::Base(0x2C, 0x31, "MK Bazaar Item 2",                                 MARKET_BAZAAR_ITEM_2,      {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BazaarItem3                               = ItemLocation::Base(0x2C, 0x32, "MK Bazaar Item 3",                                 MARKET_BAZAAR_ITEM_3,      {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BazaarItem4                               = ItemLocation::Base(0x2C, 0x33, "MK Bazaar Item 4",                                 MARKET_BAZAAR_ITEM_4,      {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BazaarItem5                               = ItemLocation::Base(0x2C, 0x34, "MK Bazaar Item 5",                                 MARKET_BAZAAR_ITEM_5,      {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BazaarItem6                               = ItemLocation::Base(0x2C, 0x35, "MK Bazaar Item 6",                                 MARKET_BAZAAR_ITEM_6,      {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BazaarItem7                               = ItemLocation::Base(0x2C, 0x36, "MK Bazaar Item 7",                                 MARKET_BAZAAR_ITEM_7,      {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BazaarItem8                               = ItemLocation::Base(0x2C, 0x37, "MK Bazaar Item 8",                                 MARKET_BAZAAR_ITEM_8,      {Category::cInnerMarket, Category::cMarket, Category::cShop});
std::vector<ItemLocation*> MK_BazaarLocations = {
  &MK_BazaarItem1,
  &MK_BazaarItem2,
  &MK_BazaarItem3,
  &MK_BazaarItem4,
  &MK_BazaarItem5,
  &MK_BazaarItem6,
  &MK_BazaarItem7,
  &MK_BazaarItem8,
};

ItemLocation Kak_BazaarItem1                              = ItemLocation::Base(0x2C, 0x38, "Kak Bazaar Item 1",                                KAK_BAZAAR_ITEM_1,     {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_BazaarItem2                              = ItemLocation::Base(0x2C, 0x39, "Kak Bazaar Item 2",                                KAK_BAZAAR_ITEM_2,     {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_BazaarItem3                              = ItemLocation::Base(0x2C, 0x3A, "Kak Bazaar Item 3",                                KAK_BAZAAR_ITEM_3,     {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_BazaarItem4                              = ItemLocation::Base(0x2C, 0x3B, "Kak Bazaar Item 4",                                KAK_BAZAAR_ITEM_4,     {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_BazaarItem5                              = ItemLocation::Base(0x2C, 0x3C, "Kak Bazaar Item 5",                                KAK_BAZAAR_ITEM_5,     {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_BazaarItem6                              = ItemLocation::Base(0x2C, 0x3D, "Kak Bazaar Item 6",                                KAK_BAZAAR_ITEM_6,     {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_BazaarItem7                              = ItemLocation::Base(0x2C, 0x3E, "Kak Bazaar Item 7",                                KAK_BAZAAR_ITEM_7,     {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_BazaarItem8                              = ItemLocation::Base(0x2C, 0x3F, "Kak Bazaar Item 8",                                KAK_BAZAAR_ITEM_8,     {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
std::vector<ItemLocation*> Kak_BazaarLocations = {
  &Kak_BazaarItem1,
  &Kak_BazaarItem2,
  &Kak_BazaarItem3,
  &Kak_BazaarItem4,
  &Kak_BazaarItem5,
  &Kak_BazaarItem6,
  &Kak_BazaarItem7,
  &Kak_BazaarItem8,
};

ItemLocation ZD_ShopItem1                                 = ItemLocation::Base(0x2F, 0x30, "ZD Shop Item 1",                                   ZD_SHOP_ITEM_1,        {Category::cZorasDomain, Category::cShop});
ItemLocation ZD_ShopItem2                                 = ItemLocation::Base(0x2F, 0x31, "ZD Shop Item 2",                                   ZD_SHOP_ITEM_2,        {Category::cZorasDomain, Category::cShop});
ItemLocation ZD_ShopItem3                                 = ItemLocation::Base(0x2F, 0x32, "ZD Shop Item 3",                                   ZD_SHOP_ITEM_3,        {Category::cZorasDomain, Category::cShop});
ItemLocation ZD_ShopItem4                                 = ItemLocation::Base(0x2F, 0x33, "ZD Shop Item 4",                                   ZD_SHOP_ITEM_4,        {Category::cZorasDomain, Category::cShop});
ItemLocation ZD_ShopItem5                                 = ItemLocation::Base(0x2F, 0x34, "ZD Shop Item 5",                                   ZD_SHOP_ITEM_5,        {Category::cZorasDomain, Category::cShop});
ItemLocation ZD_ShopItem6                                 = ItemLocation::Base(0x2F, 0x35, "ZD Shop Item 6",                                   ZD_SHOP_ITEM_6,        {Category::cZorasDomain, Category::cShop});
ItemLocation ZD_ShopItem7                                 = ItemLocation::Base(0x2F, 0x36, "ZD Shop Item 7",                                   ZD_SHOP_ITEM_7,        {Category::cZorasDomain, Category::cShop});
ItemLocation ZD_ShopItem8                                 = ItemLocation::Base(0x2F, 0x37, "ZD Shop Item 8",                                   ZD_SHOP_ITEM_8,        {Category::cZorasDomain, Category::cShop});
std::vector<ItemLocation*> ZD_ShopLocations = {
  &ZD_ShopItem1,
  &ZD_ShopItem2,
  &ZD_ShopItem3,
  &ZD_ShopItem4,
  &ZD_ShopItem5,
  &ZD_ShopItem6,
  &ZD_ShopItem7,
  &ZD_ShopItem8,
};

ItemLocation GC_ShopItem1                                 = ItemLocation::Base(0x2E, 0x30, "GC Shop Item 1",                                   GC_SHOP_ITEM_1,        {Category::cGoronCity, Category::cShop});
ItemLocation GC_ShopItem2                                 = ItemLocation::Base(0x2E, 0x31, "GC Shop Item 2",                                   GC_SHOP_ITEM_2,        {Category::cGoronCity, Category::cShop});
ItemLocation GC_ShopItem3                                 = ItemLocation::Base(0x2E, 0x32, "GC Shop Item 3",                                   GC_SHOP_ITEM_3,        {Category::cGoronCity, Category::cShop});
ItemLocation GC_ShopItem4                                 = ItemLocation::Base(0x2E, 0x33, "GC Shop Item 4",                                   GC_SHOP_ITEM_4,        {Category::cGoronCity, Category::cShop});
ItemLocation GC_ShopItem5                                 = ItemLocation::Base(0x2E, 0x34, "GC Shop Item 5",                                   GC_SHOP_ITEM_5,        {Category::cGoronCity, Category::cShop});
ItemLocation GC_ShopItem6                                 = ItemLocation::Base(0x2E, 0x35, "GC Shop Item 6",                                   GC_SHOP_ITEM_6,        {Category::cGoronCity, Category::cShop});
ItemLocation GC_ShopItem7                                 = ItemLocation::Base(0x2E, 0x36, "GC Shop Item 7",                                   GC_SHOP_ITEM_7,        {Category::cGoronCity, Category::cShop});
ItemLocation GC_ShopItem8                                 = ItemLocation::Base(0x2E, 0x37, "GC Shop Item 8",                                   GC_SHOP_ITEM_8,        {Category::cGoronCity, Category::cShop});
std::vector<ItemLocation*> GC_ShopLocations = {
  &GC_ShopItem1,
  &GC_ShopItem2,
  &GC_ShopItem3,
  &GC_ShopItem4,
  &GC_ShopItem5,
  &GC_ShopItem6,
  &GC_ShopItem7,
  &GC_ShopItem8,
};

/*-------------------------------
      --- GOSSIP STONES ---
  -------------------------------*/
// These are not actual locations, but are filler spots used for hint reachability. - OoT Randomizer
//                                                                                        flag + 0x400 = message ID
ItemLocation DMC_GossipStone                              = ItemLocation::HintStone(0x00, 0x05, "DMC Gossip Stone",                            {});
ItemLocation DMT_GossipStone                              = ItemLocation::HintStone(0x00, 0x04, "DMT Gossip Stone",                            {});
ItemLocation Colossus_GossipStone                         = ItemLocation::HintStone(0x00, 0x1A, "Colossus Gossip Stone",                       {});
ItemLocation DodongosCavern_GossipStone                   = ItemLocation::HintStone(0x00, 0x14, "Dodongo's Cavern Gossip Stone",               {});
ItemLocation GV_GossipStone                               = ItemLocation::HintStone(0x00, 0x11, "GV Gossip Stone",                             {});
ItemLocation GC_MazeGossipStone                           = ItemLocation::HintStone(0x00, 0x15, "GC Maze Gossip Stone",                        {});
ItemLocation GC_MedigoronGossipStone                      = ItemLocation::HintStone(0x00, 0x19, "GC Medigoron Gossip Stone",                   {});
ItemLocation GY_GossipStone                               = ItemLocation::HintStone(0x00, 0x0A, "GY Gossip Stone",                             {});
ItemLocation HC_MalonGossipStone                          = ItemLocation::HintStone(0x00, 0x12, "HC Malon Gossip Stone",                       {});
ItemLocation HC_RockWallGossipStone                       = ItemLocation::HintStone(0x00, 0x0B, "HC Rock Wall Gossip Stone",                   {});
ItemLocation HC_StormsGrottoGossipStone                   = ItemLocation::HintStone(0x00, 0x13, "HC Storms Grotto Gossip Stone",               {});
ItemLocation KF_DekuTreeLeftGossipStone                   = ItemLocation::HintStone(0x00, 0x1F, "KF Deku Tree Left Gossip Stone",              {});
ItemLocation KF_DekuTreeRightGossipStone                  = ItemLocation::HintStone(0x00, 0x20, "KF Deku Tree Right Gossip Stone",             {});
ItemLocation KF_GossipStone                               = ItemLocation::HintStone(0x00, 0x1E, "KF Gossip Stone",                             {});
ItemLocation LH_LabGossipStone                            = ItemLocation::HintStone(0x00, 0x03, "LH Lab Gossip Stone",                         {});
ItemLocation LH_SoutheastGossipStone                      = ItemLocation::HintStone(0x00, 0x0F, "LH Southeast Gossip Stone",                   {});
ItemLocation LH_SouthwestGossipStone                      = ItemLocation::HintStone(0x00, 0x08, "LH Southwest Gossip Stone",                   {});
ItemLocation LW_GossipStone                               = ItemLocation::HintStone(0x00, 0x1D, "LW Gossip Stone",                             {});
ItemLocation SFM_MazeLowerGossipStone                     = ItemLocation::HintStone(0x00, 0x16, "SFM Maze Lower Gossip Stone",                 {});
ItemLocation SFM_MazeUpperGossipStone                     = ItemLocation::HintStone(0x00, 0x17, "SFM Maze Upper Gossip Stone",                 {});
ItemLocation SFM_SariaGossipStone                         = ItemLocation::HintStone(0x00, 0x1C, "SFM Saria Gossip Stone",                      {});
ItemLocation ToT_LeftGossipStone                          = ItemLocation::HintStone(0x00, 0x06, "ToT Left Gossip Stone",                       {});
ItemLocation ToT_LeftCenterGossipStone                    = ItemLocation::HintStone(0x00, 0x07, "ToT Left Center Gossip Stone",                {});
ItemLocation ToT_RightCenterGossipStone                   = ItemLocation::HintStone(0x00, 0x10, "ToT Right Center Gossip Stone",               {});
ItemLocation ToT_RightGossipStone                         = ItemLocation::HintStone(0x00, 0x0E, "ToT Right Gossip Stone",                      {});
ItemLocation ZD_GossipStone                               = ItemLocation::HintStone(0x00, 0x09, "ZD Gossip Stone",                             {});
ItemLocation ZF_FairyGossipStone                          = ItemLocation::HintStone(0x00, 0x01, "Fairy Gossip Stone",                          {});
ItemLocation ZF_JabuGossipStone                           = ItemLocation::HintStone(0x00, 0x02, "Jabu Gossip Stone",                           {});
ItemLocation ZR_NearGrottosGossipStone                    = ItemLocation::HintStone(0x00, 0x0D, "ZR Near Grottos Gossip Stone",                {});
ItemLocation ZR_NearDomainGossipStone                     = ItemLocation::HintStone(0x00, 0x0C, "ZR Near Domain Gossip Stone",                 {});
ItemLocation HF_CowGrottoGossipStone                      = ItemLocation::HintStone(0x00, 0x1B, "HF Cow Grotto Gossip Stone",                  {});

ItemLocation HF_NearMarketGrottoGossipStone               = ItemLocation::HintStone(0x00, 0x30, "HF Near Market Gossip Stone",                 {});
ItemLocation HF_SoutheastGrottoGossipStone                = ItemLocation::HintStone(0x00, 0x32, "HF Southeast Gossip Stone",                   {});
ItemLocation HF_OpenGrottoGossipStone                     = ItemLocation::HintStone(0x00, 0x33, "HF Open Grotto Gossip Stone",                 {});
ItemLocation Kak_OpenGrottoGossipStone                    = ItemLocation::HintStone(0x00, 0x38, "Kak Open Grotto Gossip Stone",                {});
ItemLocation ZR_OpenGrottoGossipStone                     = ItemLocation::HintStone(0x00, 0x39, "ZR Open Grotto Gossip Stone",                 {});
ItemLocation KF_StormsGrottoGossipStone                   = ItemLocation::HintStone(0x00, 0x3C, "KF Storms Gossip Stone",                      {});
ItemLocation LW_NearShortcutsGrottoGossipStone            = ItemLocation::HintStone(0x00, 0x34, "LW Near Shortcuts Gossip Stone",              {});
ItemLocation DMT_StormsGrottoGossipStone                  = ItemLocation::HintStone(0x00, 0x37, "DMT Storms Grotto Gossip Stone",              {});
ItemLocation DMC_UpperGrottoGossipStone                   = ItemLocation::HintStone(0x00, 0x3A, "DMC Upper Grotto Gossip Stone",               {});

ItemLocation GanondorfHint                                = ItemLocation::Hint     (0x00, 0x00, "Ganondorf Hint",                              {});

//List of shop location lists, used for shop shuffle
std::vector<std::vector<ItemLocation*>> ShopLocationLists = {
  KF_ShopLocations,
  Kak_PotionShopLocations,
  MK_BombchuShopLocations,
  MK_PotionShopLocations,
  MK_BazaarLocations,
  Kak_BazaarLocations,
  ZD_ShopLocations,
  GC_ShopLocations,
};

//List of gossip stone locations for hints
std::vector<ItemLocation*> gossipStoneLocations = {
  &DMC_GossipStone,
  &DMT_GossipStone,
  &Colossus_GossipStone,
  &DodongosCavern_GossipStone,
  &GV_GossipStone,
  &GC_MazeGossipStone,
  &GC_MedigoronGossipStone,
  &GY_GossipStone,
  &HC_MalonGossipStone,
  &HC_RockWallGossipStone,
  &HC_StormsGrottoGossipStone,
  &KF_DekuTreeLeftGossipStone,
  &KF_DekuTreeRightGossipStone,
  &KF_GossipStone,
  &LH_LabGossipStone,
  &LH_SoutheastGossipStone,
  &LH_SouthwestGossipStone,
  &LW_GossipStone,
  &SFM_MazeLowerGossipStone,
  &SFM_MazeUpperGossipStone,
  &SFM_SariaGossipStone,
  &ToT_LeftGossipStone,
  &ToT_LeftCenterGossipStone,
  &ToT_RightCenterGossipStone,
  &ToT_RightGossipStone,
  &ZD_GossipStone,
  &ZF_FairyGossipStone,
  &ZF_JabuGossipStone,
  &ZR_NearGrottosGossipStone,
  &ZR_NearDomainGossipStone,
  &HF_CowGrottoGossipStone,
  &HF_NearMarketGrottoGossipStone,
  &HF_SoutheastGrottoGossipStone,
  &HF_OpenGrottoGossipStone,
  &Kak_OpenGrottoGossipStone,
  &ZR_OpenGrottoGossipStone,
  &KF_StormsGrottoGossipStone,
  &LW_NearShortcutsGrottoGossipStone,
  &DMT_StormsGrottoGossipStone,
  &DMC_UpperGrottoGossipStone,
};

std::vector<ItemLocation*> dungeonRewardLocations = {
  //Bosses
  &QueenGohma,
  &KingDodongo,
  &Barinade,
  &PhantomGanon,
  &Volvagia,
  &Morpha,
  &Twinrova,
  &BongoBongo,
  &LinksPocket,
};
std::vector<ItemLocation*> overworldLocations = {
  //Kokiri Forest
  &KF_KokiriSwordChest,
  &KF_MidoTopLeftChest,
  &KF_MidoTopRightChest,
  &KF_MidoBottomLeftChest,
  &KF_MidoBottomRightChest,
  &KF_StormsGrottoChest,
  &KF_LinksHouseCow,

  //Shop
  &KF_ShopItem1,
  &KF_ShopItem2,
  &KF_ShopItem3,
  &KF_ShopItem4,
  &KF_ShopItem5,
  &KF_ShopItem6,
  &KF_ShopItem7,
  &KF_ShopItem8,

  //Lost Woods
  &LW_GiftFromSaria,
  &LW_SkullKid,
  &LW_OcarinaMemoryGame,
  &LW_TargetInWoods,
  &LW_DekuScrubNearDekuTheaterRight,
  &LW_DekuScrubNearDekuTheaterLeft,
  &LW_DekuScrubNearBridge,
  &LW_NearShortcutsGrottoChest,
  &LW_DekuScrubGrottoRear,
  &LW_DekuScrubGrottoFront,
  &DekuTheater_SkullMask,
  &DekuTheater_MaskOfTruth,

  //Sacred Forest Meadow
  &SongFromSaria,
  &SheikInForest,
  &SFM_WolfosGrottoChest,
  &SFM_DekuScrubGrottoRear,
  &SFM_DekuScrubGrottoFront,

  //Hyrule Field
  &HF_SoutheastGrottoChest,
  &HF_OpenGrottoChest,
  &HF_NearMarketGrottoChest,
  &HF_OcarinaOfTimeItem,
  &SongFromOcarinaOfTime,
  &HF_TektiteGrottoFreestandingPoH,
  &HF_DekuScrubGrotto,
  &HF_CowGrottoCow,

  //Lake Hylia
  &LH_ChildFishing,
  &LH_AdultFishing,
  &LH_LabDive,
  &LH_UnderwaterItem,
  &LH_Sun,
  &LH_FreestandingPoH,
  &LH_DekuScrubGrottoLeft,
  &LH_DekuScrubGrottoRight,
  &LH_DekuScrubGrottoCenter,

  //Gerudo Valley
  &GV_Chest,
  &GV_WaterfallFreestandingPoH,
  &GV_CrateFreestandingPoH,
  &GV_DekuScrubGrottoRear,
  &GV_DekuScrubGrottoFront,
  &GV_Cow,

  //Gerudo Fortress
  &GF_Chest,
  &GF_HBA1000Points,
  &GF_HBA1500Points,
  &GF_NorthF1Carpenter,
  &GF_NorthF2Carpenter,
  &GF_SouthF1Carpenter,
  &GF_SouthF2Carpenter,
  &GF_GerudoToken,

  //Haunted Wasteland
  &HW_Chest,

  //Desert Colossus
  &SheikAtColossus,
  &Colossus_FreestandingPoH,
  &Colossus_GreatFairyReward,
  &Colossus_DekuScrubGrottoRear,
  &Colossus_DekuScrubGrottoFront,

  //Market
  &MK_TreasureChestGameReward,
  &MK_BombchuBowlingFirstPrize,
  &MK_BombchuBowlingSecondPrize,
  &MK_BombchuBowlingBombchus,
  &MK_LostDog,
  &MK_ShootingGalleryReward,
  &MK_10BigPoes,

  //Market Shops
  &MK_BombchuShopItem1,
  &MK_BombchuShopItem2,
  &MK_BombchuShopItem3,
  &MK_BombchuShopItem4,
  &MK_BombchuShopItem5,
  &MK_BombchuShopItem6,
  &MK_BombchuShopItem7,
  &MK_BombchuShopItem8,
  &MK_PotionShopItem1,
  &MK_PotionShopItem2,
  &MK_PotionShopItem3,
  &MK_PotionShopItem4,
  &MK_PotionShopItem5,
  &MK_PotionShopItem6,
  &MK_PotionShopItem7,
  &MK_PotionShopItem8,
  &MK_BazaarItem1,
  &MK_BazaarItem2,
  &MK_BazaarItem3,
  &MK_BazaarItem4,
  &MK_BazaarItem5,
  &MK_BazaarItem6,
  &MK_BazaarItem7,
  &MK_BazaarItem8,

  //Hyrule Castle
  &HC_MalonEgg,
  &HC_ZeldasLetter,
  &SongFromImpa,
  &HC_GreatFairyReward,
  &OGC_GreatFairyReward,

  //Temple of Time
  &SheikAtTemple,
  &ToT_LightArrowCutscene,

  //Kakariko
  &SheikInKakariko,
  &Kak_RedeadGrottoChest,
  &Kak_OpenGrottoChest,
  &Kak_10GoldSkulltulaReward,
  &Kak_20GoldSkulltulaReward,
  &Kak_30GoldSkulltulaReward,
  &Kak_40GoldSkulltulaReward,
  &Kak_50GoldSkulltulaReward,
  &Kak_ManOnRoof,
  &Kak_ShootingGalleryReward,
  &Kak_AnjuAsChild,
  &Kak_AnjuAsAdult,
  &Kak_ImpasHouseFreestandingPoH,
  &Kak_WindmillFreestandingPoH,
  &SongFromWindmill,
  &Kak_ImpasHouseCow,

  //Kakariko Shops
  &Kak_PotionShopItem1,
  &Kak_PotionShopItem2,
  &Kak_PotionShopItem3,
  &Kak_PotionShopItem4,
  &Kak_PotionShopItem5,
  &Kak_PotionShopItem6,
  &Kak_PotionShopItem7,
  &Kak_PotionShopItem8,
  &Kak_BazaarItem1,
  &Kak_BazaarItem2,
  &Kak_BazaarItem3,
  &Kak_BazaarItem4,
  &Kak_BazaarItem5,
  &Kak_BazaarItem6,
  &Kak_BazaarItem7,
  &Kak_BazaarItem8,

  //Graveyard
  &GY_HookshotChest,
  &GY_ShieldGraveChest,
  &GY_HeartPieceGraveChest,
  &GY_ComposersGraveChest,
  &SongFromComposersGrave,
  &GY_FreestandingPoH,
  &GY_DampeRaceFreestandingPoH,
  &GY_DampeGravediggingTour,

  //Death Mountain Trail
  &DMT_Chest,
  &DMT_StormsGrottoChest,
  &DMT_Biggoron,
  &DMT_GreatFairyReward,
  &DMT_FreestandingPoH,
  &DMT_CowGrottoCow,

  //Goron City
  &GC_MazeLeftChest,
  &GC_MazeCenterChest,
  &GC_MazeRightChest,
  &GC_RollingGoronAsChild,
  &GC_RollingGoronAsAdult,
  &GC_DaruniasJoy,
  &GC_PotFreestandingPoH,
  &GC_DekuScrubGrottoLeft,
  &GC_DekuScrubGrottoRight,
  &GC_DekuScrubGrottoCenter,

  //Goron City Shop
  &GC_ShopItem1,
  &GC_ShopItem2,
  &GC_ShopItem3,
  &GC_ShopItem4,
  &GC_ShopItem5,
  &GC_ShopItem6,
  &GC_ShopItem7,
  &GC_ShopItem8,

  //Death Mountain
  &DMC_UpperGrottoChest,
  &DMC_WallFreestandingPoH,
  &DMC_VolcanoFreestandingPoH,
  &SheikInCrater,
  &DMC_DekuScrub,
  &DMC_GreatFairyReward,
  &DMC_DekuScrubGrottoLeft,
  &DMC_DekuScrubGrottoRight,
  &DMC_DekuScrubGrottoCenter,

  //Zoras River
  &ZR_OpenGrottoChest,
  &ZR_MagicBeanSalesman,
  &ZR_FrogsOcarinaGame,
  &ZR_FrogsInTheRain,
  &ZR_NearOpenGrottoFreestandingPoH,
  &ZR_NearDomainFreestandingPoH,
  &ZR_DekuScrubGrottoRear,
  &ZR_DekuScrubGrottoFront,

  //Zoras Domain
  &ZD_Chest,
  &ZD_DivingMinigame,
  &ZD_KingZoraThawed,

  //Zora's Domain Shop
  &ZD_ShopItem1,
  &ZD_ShopItem2,
  &ZD_ShopItem3,
  &ZD_ShopItem4,
  &ZD_ShopItem5,
  &ZD_ShopItem6,
  &ZD_ShopItem7,
  &ZD_ShopItem8,

  //Zoras Fountain
  &ZF_IcebergFreestandingPoH,
  &ZF_BottomFreestandingPoH,
  &ZF_GreatFairyReward,

  //Lon Lon Ranch
  &SongFromMalon,
  &LLR_TalonsChickens,
  &LLR_FreestandingPoH,
  &LLR_DekuScrubGrottoLeft,
  &LLR_DekuScrubGrottoRight,
  &LLR_DekuScrubGrottoCenter,
  &LLR_StablesLeftCow,
  &LLR_StablesRightCow,
  &LLR_TowerLeftCow,
  &LLR_TowerRightCow,

  /*-------------------------------
     --- GOLD SKULLTULA TOKENS ---
    -------------------------------*/

  //Overworld
  &KF_GS_BeanPatch,
  &KF_GS_KnowItAllHouse,
  &KF_GS_HouseOfTwins,

  &LW_GS_BeanPatchNearBridge,
  &LW_GS_BeanPatchNearTheater,
  &LW_GS_AboveTheater,
  &Meadow_GS,

  &HF_GS_CowGrotto,
  &HF_GS_NearKakGrotto,

  &LH_GS_BeanPatch,
  &LH_GS_SmallIsland,
  &LH_GS_LabWall,
  &LH_GS_LabCrate,
  &LH_GS_Tree,

  &GV_GS_BeanPatch,
  &GV_GS_SmallBridge,
  &GV_GS_Pillar,
  &GV_GS_BehindTent,

  &GF_GS_ArcheryRange,
  &GF_GS_TopFloor,

  &HW_GS,
  &Colossus_GS_BeanPatch,
  &Colossus_GS_Hill,
  &Colossus_GS_Tree,

  &outsideGanonsCastle_GS,
  &HC_GS_StormsGrotto,
  &HC_GS_Tree,
  &MK_GS_GuardHouse,

  &Kak_GS_HouseUnderConstruction,
  &Kak_GS_SkulltulaHouse,
  &Kak_GS_GuardsHouse,
  &Kak_GS_Tree,
  &Kak_GS_Watchtower,
  &Kak_GS_AboveImpasHouse,

  &DMC_GS_BeanPatch,
  &DMC_GS_Crate,

  &DMT_GS_BeanPatch,
  &DMT_GS_NearKak,
  &DMT_GS_AboveDodongosCavern,
  &DMT_GS_FallingRocksPath,

  &GC_GS_CenterPlatform,
  &GC_GS_BoulderMaze,
  &GY_GS_Wall,
  &GY_GS_BeanPatch,

  &ZR_GS_Ladder,
  &ZR_GS_Tree,
  &ZR_GS_AboveBridge,
  &ZR_GS_NearRaisedGrottos,

  &ZD_GS_FrozenWaterfall,
  &ZF_GS_AboveTheLog,
  &ZF_GS_HiddenCave,
  &ZF_GS_Tree,

  &LLR_GS_BackWall,
  &LLR_GS_RainShed,
  &LLR_GS_HouseWindow,
  &LLR_GS_Tree,
};

std::vector<ItemLocation*> allLocations = {};
std::vector<ItemLocation*> everyPossibleLocation = {};

//set of overrides to write to the patch
std::set<ItemOverride, ItemOverride_Compare> overrides = {};

std::vector<std::vector<ItemLocation*>> playthroughLocations;
bool playthroughBeatable = false;

u16 itemsPlaced = 0;

void AddLocation(ItemLocation * loc, std::vector<ItemLocation*>* destination = &allLocations) {
  destination->push_back(loc);
}

template <typename Container>
void AddLocations(const Container& locations, std::vector<ItemLocation*>* destination = &allLocations) {
  destination->insert(destination->end(), std::cbegin(locations), std::cend(locations));
}

//sort through Vanilla and MQ dungeon locations
void GenerateLocationPool() {
  using namespace Settings;

  allLocations.clear();
  AddLocation(&LinksPocket);
  AddLocations(overworldLocations);

  for (auto dungeon : Dungeon::dungeonList) {
    AddLocations(dungeon->GetDungeonLocations());
  }
}

void PlaceItemInLocation(ItemLocation* loc, Item item, bool applyEffectImmediately /*= false*/) {

  PlacementLog_Msg("\n");
  PlacementLog_Msg(item.GetName());
  PlacementLog_Msg(" placed at ");
  PlacementLog_Msg(loc->GetName());
  PlacementLog_Msg("\n\n");

  if (applyEffectImmediately || Settings::Logic.Is(LOGIC_NONE)) {
    item.ApplyEffect();
    loc->Use();
  }

  itemsPlaced++;
  double completion = (double) itemsPlaced / (double)(allLocations.size() + dungeonRewardLocations.size());
  printf("\x1b[8;10HPlacing Items.");
  if (completion > 0.25) printf(".");
  if (completion > 0.50) printf(".");

  //If we're placing a non-shop item in a shop location, we want to record it for custom messages
  if (item.GetItemType() != ITEMTYPE_SHOP && loc->IsCategory(Category::cShop)) {
    ItemAndPrice newpair;
    newpair.Name = item.GetName();
    int index = GetShopIndex(loc);
    newpair.Price = ShopItems[index].GetPrice();
    NonShopItems[TransformShopIndex(index)] = newpair;
  }

  loc->SetPlacedItem(item);
}

//Same as PlaceItemInLocation, except a price is set as well as the item
void PlaceShopItemInLocation(ItemLocation* loc, Item item, u16 price, bool applyEffectImmediately /*= false*/) {

  PlacementLog_Msg("\n");
  PlacementLog_Msg(item.GetName());
  PlacementLog_Msg(" placed at ");
  PlacementLog_Msg(loc->GetName());
  PlacementLog_Msg("\n\n");

  if (applyEffectImmediately || Settings::Logic.Is(LOGIC_NONE)) {
    item.ApplyEffect();
    loc->Use();
  }

  itemsPlaced++;
  double completion = (double) itemsPlaced / (double)(allLocations.size() + dungeonRewardLocations.size());
  printf("\x1b[8;10HPlacing Items.");
  if (completion > 0.25) printf(".");
  if (completion > 0.50) printf(".");

  loc->SetPlacedShopItem(item, price);
}

std::vector<ItemLocation*> GetLocations(const std::vector<ItemLocation*>& locationPool, Category category) {
  std::vector<ItemLocation*> locationsInCategory;
  for (auto* loc : locationPool) {
    if (loc->IsCategory(category)) {
      locationsInCategory.push_back(loc);
    }
  }
  return locationsInCategory;
}

void LocationReset() {
  for (ItemLocation* il : allLocations) {
    il->RemoveFromPool();
  }

  for (ItemLocation * il : dungeonRewardLocations) {
    il->RemoveFromPool();
  }

  for (ItemLocation * il : gossipStoneLocations) {
    il->RemoveFromPool();
  }

  (&GanondorfHint)->RemoveFromPool();
}

void ItemReset() {
  for (ItemLocation* il : allLocations) {
    il->ResetVariables();
  }

  for (ItemLocation* il : dungeonRewardLocations) {
    il->ResetVariables();
  }

  itemsPlaced = 0;
}

void HintReset() {
  for (ItemLocation* il : gossipStoneLocations) {
    il->ResetVariables();
  }
}

//Fills everyPossibleLocation and creates an exclusion option for each location.
//everyPossibleLocation is used in the menu to lock/hide excluding locations
void AddExcludedOptions() {
  AddLocations(overworldLocations, &everyPossibleLocation);

  for (auto dungeon : Dungeon::dungeonList) {
    AddLocations(dungeon->GetEveryLocation(), &everyPossibleLocation);
  }

  for (ItemLocation * il: everyPossibleLocation) {
    il->AddExcludeOption();
  }
}

void CreateOverrides() {
  PlacementLog_Msg("NOW CREATING OVERRIDES\n\n");
  for (ItemLocation* loc : allLocations) {
    ItemOverride_Value val = loc->GetPlacedItem().Value();
    //If this is an ice trap in a shop, change the name based on what the model will look like
    if (loc->GetPlacedItem() == IceTrap && loc->IsCategory(Category::cShop)) {
      NonShopItems[TransformShopIndex(GetShopIndex(loc))].Name = GetIceTrapName(val.looksLikeItemId);
    }
    overrides.insert({
      .key = loc->Key(),
      .value = val,
    });
    PlacementLog_Msg("\tScene: ");
    PlacementLog_Msg(std::to_string(loc->Key().scene));
    PlacementLog_Msg("\tType: ");
    PlacementLog_Msg(std::to_string(loc->Key().type));
    PlacementLog_Msg("\tFlag:  ");
    PlacementLog_Msg(std::to_string(loc->Key().flag));
    PlacementLog_Msg("\t");
    PlacementLog_Msg(loc->GetName());
    PlacementLog_Msg(": ");
    PlacementLog_Msg(loc->GetPlacedItemName());
    PlacementLog_Msg("\n");
  }
  PlacementLog_Msg("Overrides Created: ");
  PlacementLog_Msg(std::to_string(overrides.size()));
}
