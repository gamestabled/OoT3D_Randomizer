#include "item_location.hpp"

#include "dungeon.hpp"
#include "settings.hpp"
#include "spoiler_log.hpp"
#include "hint_list.hpp"
#include "shops.hpp"

//Location definitions
//Kokiri Forest                                                          scene  flag  name                                     hint text (hint_list.cpp)                 categories
ItemLocation KF_KokiriSwordChest              = ItemLocation::Chest      (0x55, 0x00, "KF Kokiri Sword Chest",                &Hints::KF_KokiriSwordChest,              {Category::cKokiriForest, Category::cForest,});
ItemLocation KF_MidoTopLeftChest              = ItemLocation::Chest      (0x28, 0x00, "KF Mido Top Left Chest",               &Hints::KF_MidoTopLeftChest,              {Category::cKokiriForest, Category::cForest,});
ItemLocation KF_MidoTopRightChest             = ItemLocation::Chest      (0x28, 0x01, "KF Mido Top Right Chest",              &Hints::KF_MidoTopRightChest,             {Category::cKokiriForest, Category::cForest,});
ItemLocation KF_MidoBottomLeftChest           = ItemLocation::Chest      (0x28, 0x02, "KF Mido Bottom Left Chest",            &Hints::KF_MidoBottomLeftChest,           {Category::cKokiriForest, Category::cForest,});
ItemLocation KF_MidoBottomRightChest          = ItemLocation::Chest      (0x28, 0x03, "KF Mido Bottom Right Chest",           &Hints::KF_MidoBottomRightChest,          {Category::cKokiriForest, Category::cForest,});
ItemLocation KF_StormsGrottoChest             = ItemLocation::Chest      (0x3E, 0x0C, "KF Storms Grotto Chest",               &Hints::KF_StormsGrottoChest,             {Category::cKokiriForest, Category::cForest, Category::cGrotto});

//Lost Woods
ItemLocation LW_NearShortcutsGrottoChest      = ItemLocation::Chest      (0x3E, 0x14, "LW Near Shortcuts Grotto Chest",       &Hints::LW_NearShortcutsGrottoChest,      {Category::cLostWoods, Category::cForest, Category::cGrotto});
ItemLocation LW_SkullKid                      = ItemLocation::Base       (0x5B, 0x3E, "LW Skull Kid",                         &Hints::LW_SkullKid,                      {Category::cLostWoods, Category::cForest,});
ItemLocation LW_OcarinaMemoryGame             = ItemLocation::Base       (0x5B, 0x76, "LW Ocarina Memory Game",               &Hints::LW_OcarinaMemoryGame,             {Category::cLostWoods, Category::cForest, Category::cMinigame});
ItemLocation LW_TargetInWoods                 = ItemLocation::Base       (0x5B, 0x60, "LW Target in Woods",                   &Hints::LW_TargetInWoods,                 {Category::cLostWoods, Category::cForest,});
ItemLocation LW_DekuScrubNearDekuTheaterRight = ItemLocation::Base       (0x5B, 0x30, "LW Deku Scrub Near Deku Theater Right",&Hints::LW_DekuScrubNearDekuTheaterRight, {Category::cLostWoods, Category::cForest, Category::cDekuScrub});
ItemLocation LW_DekuScrubNearDekuTheaterLeft  = ItemLocation::Base       (0x5B, 0x31, "LW Deku Scrub Near Deku Theater Left", &Hints::LW_DekuScrubNearDekuTheaterLeft,  {Category::cLostWoods, Category::cForest, Category::cDekuScrub});
ItemLocation LW_DekuScrubNearBridge           = ItemLocation::Base       (0x5B, 0x77, "LW Deku Scrub Near Bridge",            &Hints::LW_DekuScrubNearBridge,           {Category::cLostWoods, Category::cForest, Category::cDekuScrub, Category::cDekuScrubUpgrades});
ItemLocation LW_DekuScrubGrottoRear           = ItemLocation::GrottoScrub(0xF5, 0x33, "LW Deku Scrub Grotto Rear",            &Hints::LW_DekuScrubGrottoRear,           {Category::cLostWoods, Category::cForest, Category::cDekuScrub, Category::cGrotto});
ItemLocation LW_DekuScrubGrottoFront          = ItemLocation::GrottoScrub(0xF5, 0x79, "LW Deku Scrub Grotto Front",           &Hints::LW_DekuScrubGrottoFront,          {Category::cLostWoods, Category::cForest, Category::cDekuScrub, Category::cDekuScrubUpgrades, Category::cGrotto});
ItemLocation DekuTheater_SkullMask            = ItemLocation::Base       (0x3E, 0x77, "Deku Theater Skull Mask",              &Hints::DekuTheater_SkullMask,            {Category::cLostWoods, Category::cForest, Category::cGrotto});
ItemLocation DekuTheater_MaskOfTruth          = ItemLocation::Base       (0x3E, 0x7A, "Deku Theater Mask of Truth",           &Hints::DekuTheater_MaskOfTruth,          {Category::cLostWoods, Category::cForest, Category::cNeedSpiritualStones, Category::cGrotto});

//Sacred Forest Meadow
ItemLocation SFM_WolfosGrottoChest            = ItemLocation::Chest      (0x3E, 0x11, "SFM Wolfos Grotto Chest",              &Hints::SFM_WolfosGrottoChest,            {Category::cSacredForestMeadow, Category::cForest, Category::cGrotto});
ItemLocation SFM_DekuScrubGrottoRear          = ItemLocation::GrottoScrub(0xEE, 0x39, "SFM Deku Scrub Grotto Rear",           &Hints::SFM_DekuScrubGrottoRear,          {Category::cSacredForestMeadow, Category::cForest, Category::cDekuScrub, Category::cGrotto});
ItemLocation SFM_DekuScrubGrottoFront         = ItemLocation::GrottoScrub(0xEE, 0x3A, "SFM Deku Scrub Grotto Front",          &Hints::SFM_DekuScrubGrottoFront,         {Category::cSacredForestMeadow, Category::cForest, Category::cDekuScrub, Category::cGrotto});

//Hyrule Field
ItemLocation HF_SoutheastGrottoChest          = ItemLocation::Chest      (0x3E, 0x02, "HF Southeast Grotto Chest",            &Hints::HF_SoutheastGrottoChest,          {Category::cHyruleField, Category::cGrotto,});
ItemLocation HF_OpenGrottoChest               = ItemLocation::Chest      (0x3E, 0x03, "HF Open Grotto Chest",                 &Hints::HF_OpenGrottoChest,               {Category::cHyruleField, Category::cGrotto,});
ItemLocation HF_NearMarketGrottoChest         = ItemLocation::Chest      (0x3E, 0x00, "HF Near Market Grotto Chest",          &Hints::HF_NearMarketGrottoChest,         {Category::cHyruleField, Category::cGrotto,});
ItemLocation HF_OcarinaOfTimeItem             = ItemLocation::Base       (0x51, 0x0C, "HF Ocarina of Time Item",              &Hints::HF_OcarinaOfTimeItem,             {Category::cHyruleField, Category::cNeedSpiritualStones,});
ItemLocation HF_TektiteGrottoFreestandingPoH  = ItemLocation::Collectable(0x3E, 0x01, "HF Tektite Grotto Freestanding PoH",   &Hints::HF_TektiteGrottoFreestandingPoH,  {Category::cHyruleField, Category::cGrotto,});
ItemLocation HF_DekuScrubGrotto               = ItemLocation::GrottoScrub(0xE6, 0x3E, "HF Deku Scrub Grotto",                 &Hints::HF_DekuScrubGrotto,               {Category::cHyruleField, Category::cDekuScrub, Category::cDekuScrubUpgrades, Category::cGrotto});

//Lake Hylia
ItemLocation LH_ChildFishing                  = ItemLocation::Base       (0x49, 0x3E, "LH Child Fishing",                     &Hints::LH_ChildFishing,                  {Category::cLakeHylia, Category::cMinigame,});
ItemLocation LH_AdultFishing                  = ItemLocation::Base       (0x49, 0x38, "LH Adult Fishing",                     &Hints::LH_AdultFishing,                  {Category::cLakeHylia, Category::cMinigame,});
ItemLocation LH_LabDive                       = ItemLocation::Base       (0x38, 0x3E, "LH Lab Dive",                          &Hints::LH_LabDive,                       {Category::cLakeHylia,});
ItemLocation LH_UnderwaterItem                = ItemLocation::Base       (0x57, 0x15, "LH Underwater Item",                   &Hints::LH_UnderwaterItem,                {Category::cLakeHylia,});
ItemLocation LH_Sun                           = ItemLocation::Base       (0x57, 0x58, "LH Sun",                               &Hints::LH_Sun,                           {Category::cLakeHylia,});
ItemLocation LH_FreestandingPoH               = ItemLocation::Collectable(0x57, 0x1E, "LH Freestanding PoH",                  &Hints::LH_FreestandingPoH,               {Category::cLakeHylia,});
ItemLocation LH_DekuScrubGrottoLeft           = ItemLocation::GrottoScrub(0xEF, 0x30, "LH Deku Scrub Grotto Left",            &Hints::LH_DekuScrubGrottoLeft,           {Category::cLakeHylia, Category::cDekuScrub, Category::cGrotto});
ItemLocation LH_DekuScrubGrottoRight          = ItemLocation::GrottoScrub(0xEF, 0x37, "LH Deku Scrub Grotto Right",           &Hints::LH_DekuScrubGrottoRight,          {Category::cLakeHylia, Category::cDekuScrub, Category::cGrotto});
ItemLocation LH_DekuScrubGrottoCenter         = ItemLocation::GrottoScrub(0xEF, 0x33, "LH Deku Scrub Grotto Center",          &Hints::LH_DekuScrubGrottoCenter,         {Category::cLakeHylia, Category::cDekuScrub, Category::cGrotto});

//Gerudo Valley
ItemLocation GV_Chest                         = ItemLocation::Chest      (0x5A, 0x00, "GV Chest",                             &Hints::GV_Chest,                         {Category::cGerudoValley, Category::cGerudo,});
ItemLocation GV_WaterfallFreestandingPoH      = ItemLocation::Collectable(0x5A, 0x01, "GV Waterfall Freestanding PoH",        &Hints::GV_WaterfallFreestandingPoH,      {Category::cGerudoValley, Category::cGerudo,});
ItemLocation GV_CrateFreestandingPoH          = ItemLocation::Collectable(0x5A, 0x02, "GV Crate Freestanding PoH",            &Hints::GV_CrateFreestandingPoH,          {Category::cGerudoValley, Category::cGerudo,});
ItemLocation GV_DekuScrubGrottoRear           = ItemLocation::GrottoScrub(0xF0, 0x39, "GV Deku Scrub Grotto Rear",            &Hints::GV_DekuScrubGrottoRear,           {Category::cGerudoValley, Category::cGerudo, Category::cDekuScrub, Category::cGrotto});
ItemLocation GV_DekuScrubGrottoFront          = ItemLocation::GrottoScrub(0xF0, 0x3A, "GV Deku Scrub Grotto Front",           &Hints::GV_DekuScrubGrottoFront,          {Category::cGerudoValley, Category::cGerudo, Category::cDekuScrub, Category::cGrotto});

//Gerudo Fortress
ItemLocation GF_Chest                         = ItemLocation::Chest      (0x5D, 0x00, "GF Chest",                             &Hints::GF_Chest,                         {Category::cGerudoFortress, Category::cGerudo,});
ItemLocation GF_HBA1000Points                 = ItemLocation::Base       (0x5D, 0x3E, "GF HBA 1000 Points",                   &Hints::GF_HBA1000Points,                 {Category::cGerudoFortress, Category::cGerudo, Category::cMinigame});
ItemLocation GF_HBA1500Points                 = ItemLocation::Base       (0x5D, 0x30, "GF HBA 1500 Points",                   &Hints::GF_HBA1500Points,                 {Category::cGerudoFortress, Category::cGerudo, Category::cMinigame});
ItemLocation GF_GerudoToken                   = ItemLocation::Base       (0x0C, 0x3A, "GF Gerudo Token",                      &Hints::GF_GerudoToken,                   {Category::cGerudoFortress, Category::cGerudo,});
ItemLocation GF_NorthF1Carpenter              = ItemLocation::Collectable(0x0C, 0x0C, "GF North F1 Carpenter",                &Hints::GF_NorthF1Carpenter,              {Category::cGerudoFortress, Category::cGerudo, Category::cVanillaGFSmallKey});
ItemLocation GF_NorthF2Carpenter              = ItemLocation::Collectable(0x0C, 0x0A, "GF North F2 Carpenter",                &Hints::GF_NorthF2Carpenter,              {Category::cGerudoFortress, Category::cGerudo, Category::cVanillaGFSmallKey});
ItemLocation GF_SouthF1Carpenter              = ItemLocation::Collectable(0x0C, 0x0E, "GF South F1 Carpenter",                &Hints::GF_SouthF1Carpenter,              {Category::cGerudoFortress, Category::cGerudo, Category::cVanillaGFSmallKey});
ItemLocation GF_SouthF2Carpenter              = ItemLocation::Collectable(0x0C, 0x0F, "GF South F2 Carpenter",                &Hints::GF_SouthF2Carpenter,              {Category::cGerudoFortress, Category::cGerudo, Category::cVanillaGFSmallKey});

//Haunted Wasteland
ItemLocation HW_Chest                         = ItemLocation::Chest      (0x5E, 0x00, "HW Chest",                             &Hints::HW_Chest,                         {Category::cHauntedWasteland,});

//Desert Colossus
ItemLocation Colossus_FreestandingPoH         = ItemLocation::Collectable(0x5C, 0x0D, "Colossus Freestanding PoH",            &Hints::Colossus_FreestandingPoH,         {Category::cDesertColossus,});
ItemLocation Colossus_DekuScrubGrottoRear     = ItemLocation::GrottoScrub(0xFD, 0x39, "Colossus Deku Scrub Grotto Rear",      &Hints::Colossus_DekuScrubGrottoRear,     {Category::cDesertColossus, Category::cDekuScrub, Category::cGrotto});
ItemLocation Colossus_DekuScrubGrottoFront    = ItemLocation::GrottoScrub(0xFD, 0x3A, "Colossus Deku Scrub Grotto Front",     &Hints::Colossus_DekuScrubGrottoFront,    {Category::cDesertColossus, Category::cDekuScrub, Category::cGrotto});

//Market
ItemLocation MK_TreasureChestGameReward       = ItemLocation::Chest      (0x10, 0x0A, "MK Treasure Chest Game Reward",        &Hints::MK_TreasureChestGameReward,       {Category::cInnerMarket, Category::cMarket, Category::cMinigame});
ItemLocation MK_BombchuBowlingFirstPrize      = ItemLocation::Base       (0x4B, 0x33, "MK Bombchu Bowling First Prize",       &Hints::MK_BombchuBowlingFirstPrize,      {Category::cInnerMarket, Category::cMarket, Category::cMinigame});
ItemLocation MK_BombchuBowlingSecondPrize     = ItemLocation::Base       (0x4B, 0x3E, "MK Bombchu Bowling Second Prize",      &Hints::MK_BombchuBowlingSecondPrize,     {Category::cInnerMarket, Category::cMarket, Category::cMinigame});
ItemLocation MK_BombchuBowlingBombchus        = ItemLocation::Base       (0x4B, 0xFF, "MK Bombchu Bowling Bombchus",          &Hints::NoHintText,                       {Category::cInnerMarket, Category::cMarket, Category::cMinigame});
ItemLocation MK_LostDog                       = ItemLocation::Base       (0x35, 0x3E, "MK Lost Dog",                          &Hints::MK_LostDog,                       {Category::cInnerMarket, Category::cMarket,});
ItemLocation MK_ShootingGalleryReward         = ItemLocation::Base       (0x42, 0x60, "MK Shooting Gallery",                  &Hints::MK_ShootingGallery,               {Category::cInnerMarket, Category::cMarket, Category::cMinigame});
ItemLocation MK_10BigPoes                     = ItemLocation::Base       (0x4D, 0x0F, "MK 10 Big Poes",                       &Hints::MK_10BigPoes,                     {Category::cInnerMarket, Category::cHyruleCastle,});

//Hyrule Castle
ItemLocation HC_MalonEgg                      = ItemLocation::Base       (0x5F, 0x47, "HC Malon Egg",                         &Hints::HC_MalonEgg,                      {Category::cHyruleCastle, Category::cMarket,});
ItemLocation HC_ZeldasLetter                  = ItemLocation::Base       (0x4A, 0x0B, "HC Zeldas Letter",                     &Hints::HC_ZeldasLetter,                  {Category::cHyruleCastle, Category::cMarket,});

//Kakariko
ItemLocation Kak_RedeadGrottoChest            = ItemLocation::Chest      (0x3E, 0x0A, "Kak Redead Grotto Chest",              &Hints::Kak_RedeadGrottoChest,            {Category::cKakarikoVillage, Category::cKakariko, Category::cGrotto});
ItemLocation Kak_OpenGrottoChest              = ItemLocation::Chest      (0x3E, 0x08, "Kak Open Grotto Chest",                &Hints::Kak_OpenGrottoChest,              {Category::cKakarikoVillage, Category::cKakariko, Category::cGrotto});
ItemLocation Kak_10GoldSkulltulaReward        = ItemLocation::Base       (0x50, 0x45, "Kak 10 Gold Skulltula Reward",         &Hints::Kak_10GoldSkulltulaReward,        {Category::cKakarikoVillage, Category::cKakariko, Category::cSkulltulaHouse});
ItemLocation Kak_20GoldSkulltulaReward        = ItemLocation::Base       (0x50, 0x39, "Kak 20 Gold Skulltula Reward",         &Hints::Kak_20GoldSkulltulaReward,        {Category::cKakarikoVillage, Category::cKakariko, Category::cSkulltulaHouse});
ItemLocation Kak_30GoldSkulltulaReward        = ItemLocation::Base       (0x50, 0x46, "Kak 30 Gold Skulltula Reward",         &Hints::Kak_30GoldSkulltulaReward,        {Category::cKakarikoVillage, Category::cKakariko, Category::cSkulltulaHouse});
ItemLocation Kak_40GoldSkulltulaReward        = ItemLocation::Base       (0x50, 0x03, "Kak 40 Gold Skulltula Reward",         &Hints::Kak_40GoldSkulltulaReward,        {Category::cKakarikoVillage, Category::cKakariko, Category::cSkulltulaHouse});
ItemLocation Kak_50GoldSkulltulaReward        = ItemLocation::Base       (0x50, 0x3E, "Kak 50 Gold Skulltula Reward",         &Hints::Kak_50GoldSkulltulaReward,        {Category::cKakarikoVillage, Category::cKakariko, Category::cSkulltulaHouse});
ItemLocation Kak_ManOnRoof                    = ItemLocation::Base       (0x52, 0x3E, "Kak Man on Roof",                      &Hints::Kak_ManOnRoof,                    {Category::cKakarikoVillage, Category::cKakariko,});
ItemLocation Kak_ShootingGalleryReward        = ItemLocation::Base       (0x42, 0x30, "Kak Shooting Gallery Reward",          &Hints::Kak_ShootingGalleryReward,        {Category::cKakarikoVillage, Category::cKakariko, Category::cMinigame});
ItemLocation Kak_AnjuAsAdult                  = ItemLocation::Base       (0x52, 0x1D, "Kak Anju as Adult",                    &Hints::Kak_AnjuAsAdult,                  {Category::cKakarikoVillage, Category::cKakariko,});
ItemLocation Kak_AnjuAsChild                  = ItemLocation::Base       (0x52, 0x0F, "Kak Anju as Child",                    &Hints::Kak_AnjuAsChild,                  {Category::cKakarikoVillage, Category::cKakariko, Category::cMinigame});
ItemLocation Kak_ImpasHouseFreestandingPoH    = ItemLocation::Collectable(0x37, 0x01, "Kak Impas House Freestanding PoH",     &Hints::Kak_ImpasHouseFreestandingPoH,    {Category::cKakarikoVillage, Category::cKakariko,});
ItemLocation Kak_WindmillFreestandingPoH      = ItemLocation::Collectable(0x48, 0x01, "Kak Windmill Freestanding PoH",        &Hints::Kak_WindmillFreestandingPoH,      {Category::cKakarikoVillage, Category::cKakariko,});

//Graveyard
ItemLocation GY_ShieldGraveChest              = ItemLocation::Chest      (0x40, 0x00, "GY Shield Grave Chest",                &Hints::GY_ShieldGraveChest,              {Category::cGraveyard, Category::cKakariko,});
ItemLocation GY_HeartPieceGraveChest          = ItemLocation::Chest      (0x3F, 0x00, "GY Heart Piece Grave Chest",           &Hints::GY_HeartPieceGraveChest,          {Category::cGraveyard, Category::cKakariko,});
ItemLocation GY_ComposersGraveChest           = ItemLocation::Chest      (0x41, 0x00, "GY Composers Grave Chest",             &Hints::GY_ComposersGraveChest,           {Category::cGraveyard, Category::cKakariko,});
ItemLocation GY_HookshotChest                 = ItemLocation::Chest      (0x48, 0x00, "GY Hookshot Chest",                    &Hints::GY_HookshotChest,                 {Category::cGraveyard, Category::cKakariko,});
ItemLocation GY_DampeRaceFreestandingPoH      = ItemLocation::Collectable(0x48, 0x07, "GY Dampe Race Freestanding PoH",       &Hints::GY_DampeRaceFreestandingPoH,      {Category::cGraveyard, Category::cKakariko, Category::cMinigame});
ItemLocation GY_FreestandingPoH               = ItemLocation::Collectable(0x53, 0x04, "GY Freestanding PoH",                  &Hints::GY_FreestandingPoH,               {Category::cGraveyard, Category::cKakariko,});
ItemLocation GY_DampeGravediggingTour         = ItemLocation::Collectable(0x53, 0x08, "GY Dampe Gravedigging Tour",           &Hints::GY_DampeGravediggingTour,         {Category::cGraveyard, Category::cKakariko,});

//Death Mountain
ItemLocation DMT_Chest                        = ItemLocation::Chest      (0x60, 0x01, "DMT Chest",                            &Hints::DMT_Chest,                        {Category::cDeathMountainTrail, Category::cDeathMountain,});
ItemLocation DMT_StormsGrottoChest            = ItemLocation::Chest      (0x3E, 0x17, "DMT Storms Grotto Chest",              &Hints::DMT_StormsGrottoChest,            {Category::cDeathMountainTrail, Category::cDeathMountain, Category::cGrotto});
ItemLocation DMT_Biggoron                     = ItemLocation::Base       (0x60, 0x57, "DMT Biggoron",                         &Hints::DMT_Biggoron,                     {Category::cDeathMountainTrail, Category::cDeathMountain,});
ItemLocation DMT_FreestandingPoH              = ItemLocation::Collectable(0x60, 0x1E, "DMT Freestanding PoH",                 &Hints::DMT_FreestandingPoH,              {Category::cDeathMountainTrail, Category::cDeathMountain,});

//Goron City
ItemLocation GC_MazeLeftChest                 = ItemLocation::Chest      (0x62, 0x00, "GC Maze Left Chest",                   &Hints::GC_MazeLeftChest,                 {Category::cGoronCity,});
ItemLocation GC_MazeRightChest                = ItemLocation::Chest      (0x62, 0x01, "GC Maze Right Chest",                  &Hints::GC_MazeRightChest,                {Category::cGoronCity,});
ItemLocation GC_MazeCenterChest               = ItemLocation::Chest      (0x62, 0x02, "GC Maze Center Chest",                 &Hints::GC_MazeCenterChest,               {Category::cGoronCity,});
ItemLocation GC_RollingGoronAsChild           = ItemLocation::Base       (0x62, 0x34, "GC Rolling Goron as Child",            &Hints::GC_RollingGoronAsChild,           {Category::cGoronCity,});
ItemLocation GC_RollingGoronAsAdult           = ItemLocation::Base       (0x62, 0x2C, "GC Rolling Goron as Adult",            &Hints::GC_RollingGoronAsAdult,           {Category::cGoronCity,});
ItemLocation GC_DaruniasJoy                   = ItemLocation::Base       (0x62, 0x54, "GC Darunias Joy",                      &Hints::GC_DaruniasJoy,                   {Category::cGoronCity,});
ItemLocation GC_PotFreestandingPoH            = ItemLocation::Collectable(0x62, 0x1F, "GC Pot Freestanding PoH",              &Hints::GC_PotFreestandingPoH,            {Category::cGoronCity,});
ItemLocation GC_DekuScrubGrottoLeft           = ItemLocation::GrottoScrub(0xFB, 0x30, "GC Deku Scrub Grotto Left",            &Hints::GC_DekuScrubGrottoLeft,           {Category::cGoronCity, Category::cDekuScrub, Category::cGrotto});
ItemLocation GC_DekuScrubGrottoRight          = ItemLocation::GrottoScrub(0xFB, 0x37, "GC Deku Scrub Grotto Right",           &Hints::GC_DekuScrubGrottoRight,          {Category::cGoronCity, Category::cDekuScrub, Category::cGrotto});
ItemLocation GC_DekuScrubGrottoCenter         = ItemLocation::GrottoScrub(0xFB, 0x33, "GC Deku Scrub Grotto Center",          &Hints::GC_DekuScrubGrottoCenter,         {Category::cGoronCity, Category::cDekuScrub, Category::cGrotto});

//Death Mountain Crater
ItemLocation DMC_UpperGrottoChest             = ItemLocation::Chest      (0x3E, 0x1A, "DMC Upper Grotto Chest",               &Hints::DMC_UpperGrottoChest,             {Category::cDeathMountainCrater, Category::cDeathMountain, Category::cGrotto});
ItemLocation DMC_WallFreestandingPoH          = ItemLocation::Collectable(0x61, 0x02, "DMC Wall Freestanding PoH",            &Hints::DMC_WallFreestandingPoH,          {Category::cDeathMountainCrater, Category::cDeathMountain,});
ItemLocation DMC_VolcanoFreestandingPoH       = ItemLocation::Collectable(0x61, 0x08, "DMC Volcano Freestanding PoH",         &Hints::DMC_VolcanoFreestandingPoH,       {Category::cDeathMountainCrater, Category::cDeathMountain,});
ItemLocation DMC_DekuScrub                    = ItemLocation::Base       (0x61, 0x37, "DMC Deku Scrub",                       &Hints::DMC_DekuScrub,                    {Category::cDeathMountainCrater, Category::cDeathMountain, Category::cDekuScrub});
ItemLocation DMC_DekuScrubGrottoLeft          = ItemLocation::GrottoScrub(0xF9, 0x30, "DMC Deku Scrub Grotto Left",           &Hints::DMC_DekuScrubGrottoLeft,          {Category::cDeathMountainCrater, Category::cDeathMountain, Category::cDekuScrub, Category::cGrotto});
ItemLocation DMC_DekuScrubGrottoRight         = ItemLocation::GrottoScrub(0xF9, 0x37, "DMC Deku Scrub Grotto Right",          &Hints::DMC_DekuScrubGrottoRight,         {Category::cDeathMountainCrater, Category::cDeathMountain, Category::cDekuScrub, Category::cGrotto});
ItemLocation DMC_DekuScrubGrottoCenter        = ItemLocation::GrottoScrub(0xF9, 0x33, "DMC Deku Scrub Grotto Center",         &Hints::DMC_DekuScrubGrottoCenter,        {Category::cDeathMountainCrater, Category::cDeathMountain, Category::cDekuScrub, Category::cGrotto});

//Zoras River
ItemLocation ZR_OpenGrottoChest               = ItemLocation::Chest      (0x3E, 0x09, "ZR Open Grotto Chest",                 &Hints::ZR_OpenGrottoChest,               {Category::cZorasRiver, Category::cGrotto,});
ItemLocation ZR_MagicBeanSalesman             = ItemLocation::Base       (0x54, 0x16, "ZR Magic Bean Salesman",               &Hints::ZR_MagicBeanSalesman,             {Category::cZorasRiver,});
ItemLocation ZR_FrogsOcarinaGame              = ItemLocation::Base       (0x54, 0x76, "ZR Frogs Ocarina Game",                &Hints::ZR_FrogsOcarinaGame,              {Category::cZorasRiver,});
ItemLocation ZR_FrogsInTheRain                = ItemLocation::Base       (0x54, 0x3E, "ZR Frogs in the Rain",                 &Hints::ZR_FrogsInTheRain,                {Category::cZorasRiver, Category::cMinigame,});
ItemLocation ZR_NearOpenGrottoFreestandingPoH = ItemLocation::Collectable(0x54, 0x04, "ZR Near Open Grotto Freestanding PoH", &Hints::ZR_NearOpenGrottoFreestandingPoH, {Category::cZorasRiver,});
ItemLocation ZR_NearDomainFreestandingPoH     = ItemLocation::Collectable(0x54, 0x0B, "ZR Near Domain Freestanding PoH",      &Hints::ZR_NearDomainFreestandingPoH,     {Category::cZorasRiver,});
ItemLocation ZR_DekuScrubGrottoRear           = ItemLocation::GrottoScrub(0xEB, 0x39, "ZR Deku Scrub Grotto Rear",            &Hints::ZR_DekuScrubGrottoRear,           {Category::cZorasRiver, Category::cDekuScrub, Category::cGrotto});
ItemLocation ZR_DekuScrubGrottoFront          = ItemLocation::GrottoScrub(0xEB, 0x3A, "ZR Deku Scrub Grotto Front",           &Hints::ZR_DekuScrubGrottoFront,          {Category::cZorasRiver, Category::cDekuScrub, Category::cGrotto});

//Zoras Domain
ItemLocation ZD_Chest                         = ItemLocation::Chest      (0x58, 0x00, "ZD Chest",                             &Hints::ZD_Chest,                         {Category::cZorasDomain,});
ItemLocation ZD_DivingMinigame                = ItemLocation::Base       (0x58, 0x37, "ZD Diving Minigame",                   &Hints::ZD_DivingMinigame,                {Category::cZorasDomain, Category::cMinigame,});
ItemLocation ZD_KingZoraThawed                = ItemLocation::Base       (0x58, 0x2D, "ZD King Zora Thawed",                  &Hints::ZD_KingZoraThawed,                {Category::cZorasDomain,});

//Zoras Fountain
ItemLocation ZF_IcebergFreestandingPoH        = ItemLocation::Collectable(0x59, 0x01, "ZF Iceberg Freestanding PoH",          &Hints::ZF_IcebergFreestandingPoH,        {Category::cZorasFountain,});
ItemLocation ZF_BottomFreestandingPoH         = ItemLocation::Collectable(0x59, 0x14, "ZF Bottom Freestanding PoH",           &Hints::ZF_BottomFreestandingPoH,         {Category::cZorasFountain,});

//Lon Lon Ranch
ItemLocation LLR_TalonsChickens               = ItemLocation::Base       (0x4C, 0x14, "LLR Talons Chickens",                  &Hints::LLR_TalonsChickens,               {Category::cLonLonRanch, Category::cMinigame});
ItemLocation LLR_FreestandingPoH              = ItemLocation::Collectable(0x4C, 0x01, "LLR Freestanding PoH",                 &Hints::LLR_FreestandingPoH,              {Category::cLonLonRanch,});
ItemLocation LLR_DekuScrubGrottoLeft          = ItemLocation::GrottoScrub(0xFC, 0x30, "LLR Deku Scrub Grotto Left",           &Hints::LLR_DekuScrubGrottoLeft,          {Category::cLonLonRanch, Category::cDekuScrub, Category::cGrotto});
ItemLocation LLR_DekuScrubGrottoRight         = ItemLocation::GrottoScrub(0xFC, 0x37, "LLR Deku Scrub Grotto Right",          &Hints::LLR_DekuScrubGrottoRight,         {Category::cLonLonRanch, Category::cDekuScrub, Category::cGrotto});
ItemLocation LLR_DekuScrubGrottoCenter        = ItemLocation::GrottoScrub(0xFC, 0x33, "LLR Deku Scrub Grotto Center",         &Hints::LLR_DekuScrubGrottoCenter,        {Category::cLonLonRanch, Category::cDekuScrub, Category::cGrotto});

/*-------------------
   --- DUNGEONS ---
  -------------------*/

//Deku Tree Vanilla
ItemLocation DekuTree_MapChest                                = ItemLocation::Chest      (0x00, 0x03, "Deku Tree Map Chest",                                &Hints::DekuTree_MapChest,                  {Category::cDekuTree, Category::cVanillaMap,});
ItemLocation DekuTree_CompassChest                            = ItemLocation::Chest      (0x00, 0x02, "Deku Tree Compass Chest",                            &Hints::DekuTree_CompassChest,              {Category::cDekuTree, Category::cVanillaCompass,});
ItemLocation DekuTree_CompassRoomSideChest                    = ItemLocation::Chest      (0x00, 0x06, "Deku Tree Compass Room Side Chest",                  &Hints::DekuTree_CompassRoomSideChest,      {Category::cDekuTree,});
ItemLocation DekuTree_BasementChest                           = ItemLocation::Chest      (0x00, 0x04, "Deku Tree Basement Chest",                           &Hints::DekuTree_BasementChest,             {Category::cDekuTree,});
ItemLocation DekuTree_SlingshotChest                          = ItemLocation::Chest      (0x00, 0x01, "Deku Tree Slingshot Chest",                          &Hints::DekuTree_SlingshotChest,            {Category::cDekuTree,});
ItemLocation DekuTree_SlingshotRoomSideChest                  = ItemLocation::Chest      (0x00, 0x05, "Deku Tree Slingshot Room Side Chest",                &Hints::DekuTree_SlingshotRoomSideChest,    {Category::cDekuTree,});
//Deku Tree MQ
ItemLocation DekuTree_MQ_MapChest                             = ItemLocation::Chest      (0x00, 0x03, "Deku Tree MQ Map Chest",                             &Hints::DekuTree_MQ_MapChest,               {Category::cDekuTree, Category::cVanillaMap,});
ItemLocation DekuTree_MQ_CompassChest                         = ItemLocation::Chest      (0x00, 0x01, "Deku Tree MQ Compass Chest",                         &Hints::DekuTree_MQ_CompassChest,           {Category::cDekuTree, Category::cVanillaCompass,});
ItemLocation DekuTree_MQ_SlingshotChest                       = ItemLocation::Chest      (0x00, 0x06, "Deku Tree MQ Slingshot Chest",                       &Hints::DekuTree_MQ_SlingshotChest,         {Category::cDekuTree,});
ItemLocation DekuTree_MQ_SlingshotRoomBackChest               = ItemLocation::Chest      (0x00, 0x02, "Deku Tree MQ Slingshot Room Back Chest",             &Hints::DekuTree_MQ_SlingshotRoomBackChest, {Category::cDekuTree,});
ItemLocation DekuTree_MQ_BasementChest                        = ItemLocation::Chest      (0x00, 0x04, "Deku Tree MQ Basement Chest",                        &Hints::DekuTree_MQ_BasementChest,          {Category::cDekuTree,});
ItemLocation DekuTree_MQ_BeforeSpinningLogChest               = ItemLocation::Chest      (0x00, 0x05, "Deku Tree MQ Before Spinning Log Chest",             &Hints::DekuTree_MQ_BeforeSpinningLogChest, {Category::cDekuTree,});
ItemLocation DekuTree_MQ_AfterSpinningLogChest                = ItemLocation::Chest      (0x00, 0x00, "Deku Tree MQ After Spinning Log Chest",              &Hints::DekuTree_MQ_AfterSpinningLogChest,  {Category::cDekuTree,});
ItemLocation DekuTree_MQ_DekuScrub                            = ItemLocation::Base       (0x00, 0x34, "Deku Tree MQ Deku Scrub",                            &Hints::DekuTree_MQ_DekuScrub,              {Category::cDekuTree,});

//Dodongos Cavern Shared
ItemLocation DodongosCavern_BossRoomChest                     = ItemLocation::Chest      (0x12, 0x00, "Dodongos Cavern Boss Room Chest",                    &Hints::DodongosCavern_BossRoomChest,                 {Category::cDodongosCavern,});
//Dodongos Cavern Vanilla
ItemLocation DodongosCavern_MapChest                          = ItemLocation::Chest      (0x01, 0x08, "Dodongos Cavern Map Chest",                          &Hints::DodongosCavern_MapChest,                      {Category::cDodongosCavern, Category::cVanillaMap,});
ItemLocation DodongosCavern_CompassChest                      = ItemLocation::Chest      (0x01, 0x05, "Dodongos Cavern Compass Chest",                      &Hints::DodongosCavern_CompassChest,                  {Category::cDodongosCavern, Category::cVanillaCompass,});
ItemLocation DodongosCavern_BombFlowerPlatformChest           = ItemLocation::Chest      (0x01, 0x06, "Dodongos Cavern Bomb Flower Platform Chest",         &Hints::DodongosCavern_BombFlowerPlatformChest,       {Category::cDodongosCavern,});
ItemLocation DodongosCavern_BombBagChest                      = ItemLocation::Chest      (0x01, 0x04, "Dodongos Cavern Bomb Bag Chest",                     &Hints::DodongosCavern_BombBagChest,                  {Category::cDodongosCavern,});
ItemLocation DodongosCavern_EndOfBridgeChest                  = ItemLocation::Chest      (0x01, 0x0A, "Dodongos Cavern End Of Bridge Chest",                &Hints::DodongosCavern_EndOfBridgeChest,              {Category::cDodongosCavern,});
ItemLocation DodongosCavern_DekuScrubNearBombBagLeft          = ItemLocation::Base       (0x01, 0x30, "Dodongos Cavern Deku Scrub Near Bomb Bag Left",      &Hints::DodongosCavern_DekuScrubNearBombBagLeft,      {Category::cDodongosCavern, Category::cDekuScrub,});
ItemLocation DodongosCavern_DekuScrubSideRoomNearDodongos     = ItemLocation::Base       (0x01, 0x31, "Dodongos Cavern Deku Scrub Side Room Near Dodongos", &Hints::DodongosCavern_DekuScrubSideRoomNearDodongos, {Category::cDodongosCavern, Category::cDekuScrub,});
ItemLocation DodongosCavern_DekuScrubNearBombBagRight         = ItemLocation::Base       (0x01, 0x33, "Dodongos Cavern Deku Scrub Near Bomb Bag Right",     &Hints::DodongosCavern_DekuScrubNearBombBagRight,     {Category::cDodongosCavern, Category::cDekuScrub,});
ItemLocation DodongosCavern_DekuScrubLobby                    = ItemLocation::Base       (0x01, 0x34, "Dodongos Cavern Deku Scrub Lobby",                   &Hints::DodongosCavern_DekuScrubLobby,                {Category::cDodongosCavern, Category::cDekuScrub,});
//Dodongos Cavern MQ
ItemLocation DodongosCavern_MQ_MapChest                       = ItemLocation::Chest      (0x01, 0x00, "Dodongos Cavern MQ Map Chest",                       &Hints::DodongosCavern_MQ_MapChest,                   {Category::cDodongosCavern, Category::cVanillaMap,});
ItemLocation DodongosCavern_MQ_BombBagChest                   = ItemLocation::Chest      (0x01, 0x04, "Dodongos Cavern MQ Bomb Bag Chest",                  &Hints::DodongosCavern_MQ_BombBagChest,               {Category::cDodongosCavern,});
ItemLocation DodongosCavern_MQ_CompassChest                   = ItemLocation::Chest      (0x01, 0x05, "Dodongos Cavern MQ Compass Chest",                   &Hints::DodongosCavern_MQ_CompassChest,               {Category::cDodongosCavern, Category::cVanillaCompass,});
ItemLocation DodongosCavern_MQ_LarvaeRoomChest                = ItemLocation::Chest      (0x01, 0x02, "Dodongos Cavern MQ Larvae Room Chest",               &Hints::DodongosCavern_MQ_LarvaeRoomChest,            {Category::cDodongosCavern,});
ItemLocation DodongosCavern_MQ_TorchPuzzleRoomChest           = ItemLocation::Chest      (0x01, 0x03, "Dodongos Cavern MQ Torch Puzzle Room Chest",         &Hints::DodongosCavern_MQ_TorchPuzzleRoomChest,       {Category::cDodongosCavern,});
ItemLocation DodongosCavern_MQ_UnderGraveChest                = ItemLocation::Chest      (0x01, 0x01, "Dodongos Cavern MQ Under Grave Chest",               &Hints::DodongosCavern_MQ_UnderGraveChest,            {Category::cDodongosCavern,});
ItemLocation DodongosCavern_MQ_DekuScrubLobbyRear             = ItemLocation::Base       (0x01, 0x31, "Dodongos Cavern Deku Scrub Lobby Rear",              &Hints::DodongosCavern_MQ_DekuScrubLobbyRear,         {Category::cDodongosCavern, Category::cDekuScrub,});
ItemLocation DodongosCavern_MQ_DekuScrubLobbyFront            = ItemLocation::Base       (0x01, 0x33, "Dodongos Cavern Deku Scrub Lobby Front",             &Hints::DodongosCavern_MQ_DekuScrubLobbyFront,        {Category::cDodongosCavern, Category::cDekuScrub,});
ItemLocation DodongosCavern_MQ_DekuScrubStaircase             = ItemLocation::Base       (0x01, 0x34, "Dodongos Cavern Deku Scrub Staircase",               &Hints::DodongosCavern_MQ_DekuScrubStaircase,         {Category::cDodongosCavern, Category::cDekuScrub,});
ItemLocation DodongosCavern_MQ_DekuScrubSideRoomNearLowerLizalfos = ItemLocation::Base   (0x01, 0x39, "Dodongos Cavern Deku Scrub Side Room Near Lower Lizalfos",&Hints::DodongosCavern_MQ_DekuScrubSideRoomNearLowerLizalfos,{Category::cDodongosCavern, Category::cDekuScrub,});

//Jabu Jabus Belly Vanilla
ItemLocation JabuJabusBelly_MapChest                          = ItemLocation::Chest      (0x02, 0x02, "Jabu Jabus Belly Map Chest",                         &Hints::JabuJabusBelly_MapChest,                     {Category::cJabuJabusBelly, Category::cVanillaMap,});
ItemLocation JabuJabusBelly_CompassChest                      = ItemLocation::Chest      (0x02, 0x04, "Jabu Jabus Belly Compass Chest",                     &Hints::JabuJabusBelly_CompassChest,                 {Category::cJabuJabusBelly, Category::cVanillaCompass,});
ItemLocation JabuJabusBelly_BoomerangChest                    = ItemLocation::Chest      (0x02, 0x01, "Jabu Jabus Belly Boomerang Chest",                   &Hints::JabuJabusBelly_BoomerangChest,               {Category::cJabuJabusBelly,});
ItemLocation JabuJabusBelly_DekuScrub                         = ItemLocation::Base       (0x02, 0x30, "Jabu Jabus Belly Deku Scrub",                        &Hints::JabuJabusBelly_DekuScrub,                    {Category::cJabuJabusBelly, Category::cDekuScrub,});
//Jabu Jabus Belly MQ
ItemLocation JabuJabusBelly_MQ_FirstRoomSideChest             = ItemLocation::Chest      (0x02, 0x05, "Jabu Jabus Belly MQ First Room Side Chest",          &Hints::JabuJabusBelly_MQ_FirstRoomSideChest,        {Category::cJabuJabusBelly,});
ItemLocation JabuJabusBelly_MQ_MapChest                       = ItemLocation::Chest      (0x02, 0x03, "Jabu Jabus Belly MQ Map Chest",                      &Hints::JabuJabusBelly_MQ_MapChest,                  {Category::cJabuJabusBelly, Category::cVanillaMap,});
ItemLocation JabuJabusBelly_MQ_SecondRoomLowerChest           = ItemLocation::Chest      (0x02, 0x02, "Jabu Jabus Belly MQ Second Room Lower Chest",        &Hints::JabuJabusBelly_MQ_SecondRoomLowerChest,      {Category::cJabuJabusBelly,});
ItemLocation JabuJabusBelly_MQ_CompassChest                   = ItemLocation::Chest      (0x02, 0x00, "Jabu Jabus Belly MQ Compass Chest",                  &Hints::JabuJabusBelly_MQ_CompassChest,              {Category::cJabuJabusBelly, Category::cVanillaCompass,});
ItemLocation JabuJabusBelly_MQ_SecondRoomUpperChest           = ItemLocation::Chest      (0x02, 0x07, "Jabu Jabus Belly MQ Second Room Upper Chest",        &Hints::JabuJabusBelly_MQ_SecondRoomUpperChest,      {Category::cJabuJabusBelly,});
ItemLocation JabuJabusBelly_MQ_BasementNearSwitchesChest      = ItemLocation::Chest      (0x02, 0x08, "Jabu Jabus Belly MQ Basement Near Switches Chest",   &Hints::JabuJabusBelly_MQ_BasementNearSwitchesChest, {Category::cJabuJabusBelly,});
ItemLocation JabuJabusBelly_MQ_BasementNearVinesChest         = ItemLocation::Chest      (0x02, 0x04, "Jabu Jabus Belly MQ Basement Near Vines Chest",      &Hints::JabuJabusBelly_MQ_BasementNearVinesChest,    {Category::cJabuJabusBelly,});
ItemLocation JabuJabusBelly_MQ_NearBossChest                  = ItemLocation::Chest      (0x02, 0x0A, "Jabu Jabus Belly MQ Near Boss Chest",                &Hints::JabuJabusBelly_MQ_NearBossChest,             {Category::cJabuJabusBelly,});
ItemLocation JabuJabusBelly_MQ_FallingLikeLikeRoomChest       = ItemLocation::Chest      (0x02, 0x09, "Jabu Jabus Belly MQ Falling Like Like Room Chest",   &Hints::JabuJabusBelly_MQ_FallingLikeLikeRoomChest,  {Category::cJabuJabusBelly,});
ItemLocation JabuJabusBelly_MQ_BoomerangRoomSmallChest        = ItemLocation::Chest      (0x02, 0x01, "Jabu Jabus Belly MQ Boomerang Room Small Chest",     &Hints::JabuJabusBelly_MQ_BoomerangRoomSmallChest,   {Category::cJabuJabusBelly,});
ItemLocation JabuJabusBelly_MQ_BoomerangChest                 = ItemLocation::Chest      (0x02, 0x06, "Jabu Jabus Belly MQ Boomerang Chest",                &Hints::JabuJabusBelly_MQ_BoomerangChest,            {Category::cJabuJabusBelly,});
//COW

//Forest Temple Vanilla
ItemLocation ForestTemple_FirstRoomChest                      = ItemLocation::Chest      (0x03, 0x03, "Forest Temple First Room Chest",                     &Hints::ForestTemple_FirstRoomChest,             {Category::cForestTemple, Category::cVanillaSmallKey});
ItemLocation ForestTemple_FirstStalfosChest                   = ItemLocation::Chest      (0x03, 0x00, "Forest Temple First Stalfos Chest",                  &Hints::ForestTemple_FirstStalfosChest,          {Category::cForestTemple, Category::cVanillaSmallKey});
ItemLocation ForestTemple_RaisedIslandCourtyardChest          = ItemLocation::Chest      (0x03, 0x05, "Forest Temple Raised Island Courtyard Chest",        &Hints::ForestTemple_RaisedIslandCourtyardChest, {Category::cForestTemple,});
ItemLocation ForestTemple_MapChest                            = ItemLocation::Chest      (0x03, 0x01, "Forest Temple Map Chest",                            &Hints::ForestTemple_MapChest,                   {Category::cForestTemple, Category::cVanillaMap,});
ItemLocation ForestTemple_WellChest                           = ItemLocation::Chest      (0x03, 0x09, "Forest Temple Well Chest",                           &Hints::ForestTemple_WellChest,                  {Category::cForestTemple, Category::cVanillaSmallKey});
ItemLocation ForestTemple_FallingCeilingRoomChest             = ItemLocation::Chest      (0x03, 0x07, "Forest Temple Falling Ceiling Room Chest",           &Hints::ForestTemple_FallingCeilingRoomChest,    {Category::cForestTemple,});
ItemLocation ForestTemple_EyeSwitchChest                      = ItemLocation::Chest      (0x03, 0x04, "Forest Temple Eye Switch Chest",                     &Hints::ForestTemple_EyeSwitchChest,             {Category::cForestTemple,});
ItemLocation ForestTemple_BossKeyChest                        = ItemLocation::Chest      (0x03, 0x0E, "Forest Temple Boss Key Chest",                       &Hints::ForestTemple_BossKeyChest,               {Category::cForestTemple, Category::cVanillaBossKey});
ItemLocation ForestTemple_FloormasterChest                    = ItemLocation::Chest      (0x03, 0x02, "Forest Temple Floormaster Chest",                    &Hints::ForestTemple_FloormasterChest,           {Category::cForestTemple, Category::cVanillaSmallKey});
ItemLocation ForestTemple_BowChest                            = ItemLocation::Chest      (0x03, 0x0C, "Forest Temple Bow Chest",                            &Hints::ForestTemple_BowChest,                   {Category::cForestTemple,});
ItemLocation ForestTemple_RedPoeChest                         = ItemLocation::Chest      (0x03, 0x0D, "Forest Temple Red Poe Chest",                        &Hints::ForestTemple_RedPoeChest,                {Category::cForestTemple, Category::cVanillaSmallKey});
ItemLocation ForestTemple_BluePoeChest                        = ItemLocation::Chest      (0x03, 0x0F, "Forest Temple Blue Poe Chest",                       &Hints::ForestTemple_BluePoeChest,               {Category::cForestTemple, Category::cVanillaCompass,});
ItemLocation ForestTemple_BasementChest                       = ItemLocation::Chest      (0x03, 0x0B, "Forest Temple Basement Chest",                       &Hints::ForestTemple_BasementChest,              {Category::cForestTemple,});
//Forest Temple MQ
ItemLocation ForestTemple_MQ_FirstRoomChest                   = ItemLocation::Chest      (0x03, 0x03, "Forest Temple MQ First Room Chest",                  &Hints::ForestTemple_MQ_FirstRoomChest,          {Category::cForestTemple, Category::cVanillaSmallKey});
ItemLocation ForestTemple_MQ_WolfosChest                      = ItemLocation::Chest      (0x03, 0x00, "Forest Temple MQ Wolfos Chest",                      &Hints::ForestTemple_MQ_WolfosChest,             {Category::cForestTemple, Category::cVanillaSmallKey});
ItemLocation ForestTemple_MQ_BowChest                         = ItemLocation::Chest      (0x03, 0x0C, "Forest Temple MQ Bow Chest",                         &Hints::ForestTemple_MQ_BowChest,                {Category::cForestTemple,});
ItemLocation ForestTemple_MQ_RaisedIslandCourtyardLowerChest  = ItemLocation::Chest      (0x03, 0x01, "Forest Temple MQ Raised Island Courtyard Lower Chest", &Hints::ForestTemple_MQ_RaisedIslandCourtyardLowerChest, {Category::cForestTemple, Category::cVanillaSmallKey});
ItemLocation ForestTemple_MQ_RaisedIslandCourtyardUpperChest  = ItemLocation::Chest      (0x03, 0x05, "Forest Temple MQ Raised Island Courtyard Upper Chest", &Hints::ForestTemple_MQ_RaisedIslandCourtyardUpperChest, {Category::cForestTemple, Category::cVanillaSmallKey});
ItemLocation ForestTemple_MQ_WellChest                        = ItemLocation::Chest      (0x03, 0x09, "Forest Temple MQ Well Chest",                        &Hints::ForestTemple_MQ_WellChest,               {Category::cForestTemple, Category::cVanillaSmallKey});
ItemLocation ForestTemple_MQ_MapChest                         = ItemLocation::Chest      (0x03, 0x0D, "Forest Temple MQ Map Chest",                         &Hints::ForestTemple_MQ_MapChest,                {Category::cForestTemple, Category::cVanillaMap,});
ItemLocation ForestTemple_MQ_CompassChest                     = ItemLocation::Chest      (0x03, 0x0F, "Forest Temple MQ Compass Chest",                     &Hints::ForestTemple_MQ_CompassChest,            {Category::cForestTemple, Category::cVanillaCompass,});
ItemLocation ForestTemple_MQ_FallingCeilingRoomChest          = ItemLocation::Chest      (0x03, 0x06, "Forest Temple MQ Falling Ceiling Room Chest",        &Hints::ForestTemple_MQ_FallingCeilingRoomChest, {Category::cForestTemple,});
ItemLocation ForestTemple_MQ_BasementChest                    = ItemLocation::Chest      (0x03, 0x0B, "Forest Temple MQ Basement Chest",                    &Hints::ForestTemple_MQ_BasementChest,           {Category::cForestTemple,});
ItemLocation ForestTemple_MQ_RedeadChest                      = ItemLocation::Chest      (0x03, 0x02, "Forest Temple MQ Redead Chest",                      &Hints::ForestTemple_MQ_RedeadChest,             {Category::cForestTemple, Category::cVanillaSmallKey});
ItemLocation ForestTemple_MQ_BossKeyChest                     = ItemLocation::Chest      (0x03, 0x0E, "Forest Temple MQ Boss Key Chest",                    &Hints::ForestTemple_MQ_BossKeyChest,            {Category::cForestTemple, Category::cVanillaBossKey});

//Fire Temple Vanilla
ItemLocation FireTemple_NearBossChest                         = ItemLocation::Chest      (0x04, 0x01, "Fire Temple Near Boss Chest",                        &Hints::FireTemple_NearBossChest,                 {Category::cFireTemple, Category::cVanillaSmallKey});
ItemLocation FireTemple_FlareDancerChest                      = ItemLocation::Chest      (0x04, 0x00, "Fire Temple Flare Dancer Chest",                     &Hints::FireTemple_FlareDancerChest,              {Category::cFireTemple,});
ItemLocation FireTemple_BossKeyChest                          = ItemLocation::Chest      (0x04, 0x0C, "Fire Temple Boss Key Chest",                         &Hints::FireTemple_BossKeyChest,                  {Category::cFireTemple, Category::cVanillaBossKey});
ItemLocation FireTemple_BigLavaRoomBlockedDoorChest           = ItemLocation::Chest      (0x04, 0x02, "Fire Temple Big Lava Room Blocked Door Chest",       &Hints::FireTemple_BigLavaRoomBlockedDoorChest,   {Category::cFireTemple, Category::cVanillaSmallKey});
ItemLocation FireTemple_BigLavaRoomLowerOpenDoorChest         = ItemLocation::Chest      (0x04, 0x04, "Fire Temple Big Lava Room Lower Open Door Chest",    &Hints::FireTemple_BigLavaRoomLowerOpenDoorChest, {Category::cFireTemple, Category::cVanillaSmallKey});
ItemLocation FireTemple_BoulderMazeLowerChest                 = ItemLocation::Chest      (0x04, 0x03, "Fire Temple Boulder Maze Lower Chest",               &Hints::FireTemple_BoulderMazeLowerChest,         {Category::cFireTemple, Category::cVanillaSmallKey});
ItemLocation FireTemple_BoulderMazeUpperChest                 = ItemLocation::Chest      (0x04, 0x06, "Fire Temple Boulder Maze Upper Chest",               &Hints::FireTemple_BoulderMazeUpperChest,         {Category::cFireTemple, Category::cVanillaSmallKey});
ItemLocation FireTemple_BoulderMazeSideRoomChest              = ItemLocation::Chest      (0x04, 0x08, "Fire Temple Boulder Maze Side Room Chest",           &Hints::FireTemple_BoulderMazeSideRoomChest,      {Category::cFireTemple, Category::cVanillaSmallKey});
ItemLocation FireTemple_BoulderMazeShortcutChest              = ItemLocation::Chest      (0x04, 0x0B, "Fire Temple Boulder Maze Shortcut Chest",            &Hints::FireTemple_BoulderMazeShortcutChest,      {Category::cFireTemple, Category::cVanillaSmallKey});
ItemLocation FireTemple_ScarecrowChest                        = ItemLocation::Chest      (0x04, 0x0D, "Fire Temple Scarecrow Chest",                        &Hints::FireTemple_ScarecrowChest,                {Category::cFireTemple,});
ItemLocation FireTemple_MapChest                              = ItemLocation::Chest      (0x04, 0x0A, "Fire Temple Map Chest",                              &Hints::FireTemple_MapChest,                      {Category::cFireTemple, Category::cVanillaMap,});
ItemLocation FireTemple_CompassChest                          = ItemLocation::Chest      (0x04, 0x07, "Fire Temple Compass Chest",                          &Hints::FireTemple_CompassChest,                  {Category::cFireTemple, Category::cVanillaCompass,});
ItemLocation FireTemple_HighestGoronChest                     = ItemLocation::Chest      (0x04, 0x09, "Fire Temple Highest Goron Chest",                    &Hints::FireTemple_HighestGoronChest,             {Category::cFireTemple, Category::cVanillaSmallKey});
ItemLocation FireTemple_MegatonHammerChest                    = ItemLocation::Chest      (0x04, 0x05, "Fire Temple Megaton Hammer Chest",                   &Hints::FireTemple_MegatonHammerChest,            {Category::cFireTemple,});
//Fire Temple MQ
ItemLocation FireTemple_MQ_NearBossChest                      = ItemLocation::Chest      (0x04, 0x07, "Fire Temple MQ Near Boss Chest",                     &Hints::FireTemple_MQ_NearBossChest,               {Category::cFireTemple, Category::cVanillaSmallKey});
ItemLocation FireTemple_MQ_MegatonHammerChest                 = ItemLocation::Chest      (0x04, 0x00, "Fire Temple MQ Megaton Hammer Chest",                &Hints::FireTemple_MQ_MegatonHammerChest,          {Category::cFireTemple,});
ItemLocation FireTemple_MQ_CompassChest                       = ItemLocation::Chest      (0x04, 0x0B, "Fire Temple MQ Compass Chest",                       &Hints::FireTemple_MQ_CompassChest,                {Category::cFireTemple, Category::cVanillaCompass,});
ItemLocation FireTemple_MQ_LizalfosMazeLowerChest             = ItemLocation::Chest      (0x04, 0x03, "Fire Temple MQ Lizalfos Maze Lower Chest",           &Hints::FireTemple_MQ_LizalfosMazeLowerChest,      {Category::cFireTemple,});
ItemLocation FireTemple_MQ_LizalfosMazeUpperChest             = ItemLocation::Chest      (0x04, 0x06, "Fire Temple MQ Lizalfos Maze Upper Chest",           &Hints::FireTemple_MQ_LizalfosMazeUpperChest,      {Category::cFireTemple,});
ItemLocation FireTemple_MQ_ChestOnFire                        = ItemLocation::Chest      (0x04, 0x05, "Fire Temple MQ Chest on Fire",                       &Hints::FireTemple_MQ_ChestOnFire,                 {Category::cFireTemple, Category::cVanillaSmallKey});
ItemLocation FireTemple_MQ_MapRoomSideChest                   = ItemLocation::Chest      (0x04, 0x02, "Fire Temple MQ Map Room Side Chest",                 &Hints::FireTemple_MQ_MapRoomSideChest,            {Category::cFireTemple,});
ItemLocation FireTemple_MQ_MapChest                           = ItemLocation::Chest      (0x04, 0x0C, "Fire Temple MQ Map Chest",                           &Hints::FireTemple_MQ_MapChest,                    {Category::cFireTemple, Category::cVanillaMap,});
ItemLocation FireTemple_MQ_BossKeyChest                       = ItemLocation::Chest      (0x04, 0x04, "Fire Temple MQ Boss Key Chest",                      &Hints::FireTemple_MQ_BossKeyChest,                {Category::cFireTemple, Category::cVanillaBossKey});
ItemLocation FireTemple_MQ_BigLavaRoomBlockedDoorChest        = ItemLocation::Chest      (0x04, 0x01, "Fire Temple MQ Big Lava Room Blocked Door Chest",    &Hints::FireTemple_MQ_BigLavaRoomBlockedDoorChest, {Category::cFireTemple, Category::cVanillaSmallKey});
ItemLocation FireTemple_MQ_LizalfosMazeSideRoomChest          = ItemLocation::Chest      (0x04, 0x08, "Fire Temple MQ Lizalfos Maze Side Room Chest",       &Hints::FireTemple_MQ_LizalfosMazeSideRoomChest,   {Category::cFireTemple, Category::cVanillaSmallKey});
ItemLocation FireTemple_MQ_FreestandingKey                    = ItemLocation::Collectable(0x04, 0x1C, "Fire Temple MQ Freestanding Key",                    &Hints::FireTemple_MQ_FreestandingKey,             {Category::cFireTemple, Category::cVanillaSmallKey});

//Water Temple Vanilla
ItemLocation WaterTemple_MapChest                             = ItemLocation::Chest      (0x05, 0x02, "Water Temple Map Chest",                             &Hints::WaterTemple_MapChest,              {Category::cWaterTemple, Category::cVanillaMap,});
ItemLocation WaterTemple_CompassChest                         = ItemLocation::Chest      (0x05, 0x09, "Water Temple Compass Chest",                         &Hints::WaterTemple_CompassChest,          {Category::cWaterTemple, Category::cVanillaCompass,});
ItemLocation WaterTemple_TorchesChest                         = ItemLocation::Chest      (0x05, 0x01, "Water Temple Torches Chest",                         &Hints::WaterTemple_TorchesChest,          {Category::cWaterTemple, Category::cVanillaSmallKey});
ItemLocation WaterTemple_DragonChest                          = ItemLocation::Chest      (0x05, 0x0A, "Water Temple Dragon Chest",                          &Hints::WaterTemple_DragonChest,           {Category::cWaterTemple, Category::cVanillaSmallKey});
ItemLocation WaterTemple_CentralBowTargetChest                = ItemLocation::Chest      (0x05, 0x08, "Water Temple Central Bow Target Chest",              &Hints::WaterTemple_CentralBowTargetChest, {Category::cWaterTemple, Category::cVanillaSmallKey});
ItemLocation WaterTemple_CentralPillarChest                   = ItemLocation::Chest      (0x05, 0x06, "Water Temple Central Pillar Chest",                  &Hints::WaterTemple_CentralPillarChest,    {Category::cWaterTemple, Category::cVanillaSmallKey});
ItemLocation WaterTemple_CrackedWallChest                     = ItemLocation::Chest      (0x05, 0x00, "Water Temple Cracked Wall Chest",                    &Hints::WaterTemple_CrackedWallChest,      {Category::cWaterTemple, Category::cVanillaSmallKey});
ItemLocation WaterTemple_BossKeyChest                         = ItemLocation::Chest      (0x05, 0x05, "Water Temple Boss Key Chest",                        &Hints::WaterTemple_BossKeyChest,          {Category::cWaterTemple, Category::cVanillaBossKey});
ItemLocation WaterTemple_LongshotChest                        = ItemLocation::Chest      (0x05, 0x07, "Water Temple Longshot Chest",                        &Hints::WaterTemple_LongshotChest,         {Category::cWaterTemple,});
ItemLocation WaterTemple_RiverChest                           = ItemLocation::Chest      (0x05, 0x03, "Water Temple River Chest",                           &Hints::WaterTemple_RiverChest,            {Category::cWaterTemple, Category::cVanillaSmallKey});
//Water Temple MQ
ItemLocation WaterTemple_MQ_CentralPillarChest                = ItemLocation::Chest      (0x05, 0x06, "Water Temple MQ Central Pillar Chest",               &Hints::WaterTemple_MQ_CentralPillarChest, {Category::cWaterTemple, Category::cVanillaSmallKey});
ItemLocation WaterTemple_MQ_BossKeyChest                      = ItemLocation::Chest      (0x05, 0x05, "Water Temple MQ Boss Key Chest",                     &Hints::WaterTemple_MQ_BossKeyChest,       {Category::cWaterTemple, Category::cVanillaBossKey});
ItemLocation WaterTemple_MQ_LongshotChest                     = ItemLocation::Chest      (0x05, 0x00, "Water Temple MQ Longshot Chest",                     &Hints::WaterTemple_MQ_LongshotChest,      {Category::cWaterTemple,});
ItemLocation WaterTemple_MQ_CompassChest                      = ItemLocation::Chest      (0x05, 0x01, "Water Temple MQ Compass Chest",                      &Hints::WaterTemple_MQ_CompassChest,       {Category::cWaterTemple, Category::cVanillaCompass,});
ItemLocation WaterTemple_MQ_MapChest                          = ItemLocation::Chest      (0x05, 0x02, "Water Temple MQ Map Chest",                          &Hints::WaterTemple_MQ_MapChest,           {Category::cWaterTemple, Category::cVanillaMap,});
ItemLocation WaterTemple_MQ_FreestandingKey                   = ItemLocation::Collectable(0x05, 0x01, "Water Temple MQ Freestanding Key",                   &Hints::WaterTemple_MQ_FreestandingKey,    {Category::cWaterTemple, Category::cVanillaSmallKey});

//Spirit Temple Shared
ItemLocation SpiritTemple_SilverGauntletsChest                = ItemLocation::Chest      (0x5C, 0x0B, "Spirit Temple Silver Gauntlets Chest",               &Hints::SpiritTemple_SilverGauntletsChest, {Category::cSpiritTemple, Category::cDesertColossus});
ItemLocation SpiritTemple_MirrorShieldChest                   = ItemLocation::Chest      (0x5C, 0x09, "Spirit Temple Mirror Shield Chest",                  &Hints::SpiritTemple_MirrorShieldChest,    {Category::cSpiritTemple, Category::cDesertColossus});
//Spirit Temple Vanilla
ItemLocation SpiritTemple_ChildBridgeChest                    = ItemLocation::Chest      (0x06, 0x08, "Spirit Temple Child Bridge Chest",                   &Hints::SpiritTemple_ChildBridgeChest,           {Category::cSpiritTemple,});
ItemLocation SpiritTemple_ChildEarlyTorchesChest              = ItemLocation::Chest      (0x06, 0x00, "Spirit Temple Child Early Torches Chest",            &Hints::SpiritTemple_ChildEarlyTorchesChest,     {Category::cSpiritTemple, Category::cVanillaSmallKey});
ItemLocation SpiritTemple_CompassChest                        = ItemLocation::Chest      (0x06, 0x04, "Spirit Temple Compass Chest",                        &Hints::SpiritTemple_CompassChest,               {Category::cSpiritTemple, Category::cVanillaCompass,});
ItemLocation SpiritTemple_EarlyAdultRightChest                = ItemLocation::Chest      (0x06, 0x07, "Spirit Temple Early Adult Right Chest",              &Hints::SpiritTemple_EarlyAdultRightChest,       {Category::cSpiritTemple, Category::cVanillaSmallKey});
ItemLocation SpiritTemple_FirstMirrorLeftChest                = ItemLocation::Chest      (0x06, 0x0D, "Spirit Temple First Mirror Left Chest",              &Hints::SpiritTemple_FirstMirrorLeftChest,       {Category::cSpiritTemple,});
ItemLocation SpiritTemple_FirstMirrorRightChest               = ItemLocation::Chest      (0x06, 0x0E, "Spirit Temple First Mirror Right Chest",             &Hints::SpiritTemple_FirstMirrorRightChest,      {Category::cSpiritTemple,});
ItemLocation SpiritTemple_MapChest                            = ItemLocation::Chest      (0x06, 0x03, "Spirit Temple Map Chest",                            &Hints::SpiritTemple_MapChest,                   {Category::cSpiritTemple, Category::cVanillaMap,});
ItemLocation SpiritTemple_ChildClimbNorthChest                = ItemLocation::Chest      (0x06, 0x06, "Spirit Temple Child Climb North Chest",              &Hints::SpiritTemple_ChildClimbNorthChest,       {Category::cSpiritTemple,});
ItemLocation SpiritTemple_ChildClimbEastChest                 = ItemLocation::Chest      (0x06, 0x0C, "Spirit Temple Child Climb East Chest",               &Hints::SpiritTemple_ChildClimbEastChest,        {Category::cSpiritTemple,});
ItemLocation SpiritTemple_SunBlockRoomChest                   = ItemLocation::Chest      (0x06, 0x01, "Spirit Temple Sun Block Room Chest",                 &Hints::SpiritTemple_SunBlockRoomChest,          {Category::cSpiritTemple, Category::cVanillaSmallKey});
ItemLocation SpiritTemple_StatueRoomHandChest                 = ItemLocation::Chest      (0x06, 0x02, "Spirit Temple Statue Room Hand Chest",               &Hints::SpiritTemple_StatueRoomHandChest,        {Category::cSpiritTemple, Category::cVanillaSmallKey});
ItemLocation SpiritTemple_StatueRoomNortheastChest            = ItemLocation::Chest      (0x06, 0x0F, "Spirit Temple Statue Room Northeast Chest",          &Hints::SpiritTemple_StatueRoomNortheastChest,   {Category::cSpiritTemple,});
ItemLocation SpiritTemple_NearFourArmosChest                  = ItemLocation::Chest      (0x06, 0x05, "Spirit Temple Near Four Armos Chest",                &Hints::SpiritTemple_NearFourArmosChest,         {Category::cSpiritTemple, Category::cVanillaSmallKey});
ItemLocation SpiritTemple_HallwayRightInvisibleChest          = ItemLocation::Chest      (0x06, 0x14, "Spirit Temple Hallway Right Invisible Chest",        &Hints::SpiritTemple_HallwayRightInvisibleChest, {Category::cSpiritTemple,});
ItemLocation SpiritTemple_HallwayLeftInvisibleChest           = ItemLocation::Chest      (0x06, 0x15, "Spirit Temple Hallway Left Invisible Chest",         &Hints::SpiritTemple_HallwayLeftInvisibleChest,  {Category::cSpiritTemple,});
ItemLocation SpiritTemple_BossKeyChest                        = ItemLocation::Chest      (0x06, 0x0A, "Spirit Temple Boss Key Chest",                       &Hints::SpiritTemple_BossKeyChest,               {Category::cSpiritTemple, Category::cVanillaBossKey});
ItemLocation SpiritTemple_TopmostChest                        = ItemLocation::Chest      (0x06, 0x12, "Spirit Temple Topmost Chest",                        &Hints::SpiritTemple_TopmostChest,               {Category::cSpiritTemple,});
//Spirit Temple MQ
ItemLocation SpiritTemple_MQ_EntranceFrontLeftChest           = ItemLocation::Chest      (0x06, 0x1A, "Spirit Temple MQ Entrance Front Left Chest",         &Hints::SpiritTemple_MQ_EntranceFrontLeftChest,     {Category::cSpiritTemple,});
ItemLocation SpiritTemple_MQ_EntranceBackRightChest           = ItemLocation::Chest      (0x06, 0x1F, "Spirit Temple MQ Entrance Back Right Chest",         &Hints::SpiritTemple_MQ_EntranceBackRightChest,     {Category::cSpiritTemple,});
ItemLocation SpiritTemple_MQ_EntranceFrontRightChest          = ItemLocation::Chest      (0x06, 0x1B, "Spirit Temple MQ Entrance Front Right Chest",        &Hints::SpiritTemple_MQ_EntranceFrontRightChest,    {Category::cSpiritTemple, Category::cVanillaSmallKey});
ItemLocation SpiritTemple_MQ_EntranceBackLeftChest            = ItemLocation::Chest      (0x06, 0x1E, "Spirit Temple MQ Entrance Back Left Chest",          &Hints::SpiritTemple_MQ_EntranceBackLeftChest,      {Category::cSpiritTemple, Category::cVanillaSmallKey});
ItemLocation SpiritTemple_MQ_ChildHammerSwitchChest           = ItemLocation::Chest      (0x06, 0x1D, "Spirit Temple MQ Child Hammer Switch Chest",         &Hints::SpiritTemple_MQ_ChildHammerSwitchChest,     {Category::cSpiritTemple, Category::cVanillaSmallKey});
ItemLocation SpiritTemple_MQ_MapChest                         = ItemLocation::Chest      (0x06, 0x00, "Spirit Temple MQ Map Chest",                         &Hints::SpiritTemple_MQ_MapChest,                   {Category::cSpiritTemple, Category::cVanillaMap,});
ItemLocation SpiritTemple_MQ_MapRoomEnemyChest                = ItemLocation::Chest      (0x06, 0x08, "Spirit Temple MQ Map Room Enemy Chest",              &Hints::SpiritTemple_MQ_MapRoomEnemyChest,          {Category::cSpiritTemple, Category::cVanillaSmallKey});
ItemLocation SpiritTemple_MQ_ChildClimbNorthChest             = ItemLocation::Chest      (0x06, 0x06, "Spirit Temple MQ Child Climb North Chest",           &Hints::SpiritTemple_MQ_ChildClimbNorthChest,       {Category::cSpiritTemple,});
ItemLocation SpiritTemple_MQ_ChildClimbSouthChest             = ItemLocation::Chest      (0x06, 0x0C, "Spirit Temple MQ Child Climb South Chest",           &Hints::SpiritTemple_MQ_ChildClimbSouthChest,       {Category::cSpiritTemple, Category::cVanillaSmallKey});
ItemLocation SpiritTemple_MQ_CompassChest                     = ItemLocation::Chest      (0x06, 0x03, "Spirit Temple MQ Compass Chest",                     &Hints::SpiritTemple_MQ_CompassChest,               {Category::cSpiritTemple, Category::cVanillaCompass,});
ItemLocation SpiritTemple_MQ_StatueRoomLullabyChest           = ItemLocation::Chest      (0x06, 0x0F, "Spirit Temple MQ Statue Room Lullaby Chest",         &Hints::SpiritTemple_MQ_StatueRoomLullabyChest,     {Category::cSpiritTemple,});
ItemLocation SpiritTemple_MQ_StatueRoomInvisibleChest         = ItemLocation::Chest      (0x06, 0x02, "Spirit Temple MQ Statue Room Invisible Chest",       &Hints::SpiritTemple_MQ_StatueRoomInvisibleChest,   {Category::cSpiritTemple,});
ItemLocation SpiritTemple_MQ_SilverBlockHallwayChest          = ItemLocation::Chest      (0x06, 0x1C, "Spirit Temple MQ Silver Block Hallway Chest",        &Hints::SpiritTemple_MQ_SilverBlockHallwayChest,    {Category::cSpiritTemple, Category::cVanillaSmallKey});
ItemLocation SpiritTemple_MQ_SunBlockRoomChest                = ItemLocation::Chest      (0x06, 0x01, "Spirit Temple MQ Sun Block Room Chest",              &Hints::SpiritTemple_MQ_SunBlockRoomChest,          {Category::cSpiritTemple,});
ItemLocation SpiritTemple_MQ_SymphonyRoomChest                = ItemLocation::Chest      (0x06, 0x07, "Spirit Temple MQ Symphony Room Chest",               &Hints::SpiritTemple_MQ_SymphonyRoomChest,          {Category::cSpiritTemple,});
ItemLocation SpiritTemple_MQ_LeeverRoomChest                  = ItemLocation::Chest      (0x06, 0x04, "Spirit Temple MQ Leever Room Chest",                 &Hints::SpiritTemple_MQ_LeeverRoomChest,            {Category::cSpiritTemple,});
ItemLocation SpiritTemple_MQ_BeamosRoomChest                  = ItemLocation::Chest      (0x06, 0x19, "Spirit Temple MQ Beamos Room Chest",                 &Hints::SpiritTemple_MQ_BeamosRoomChest,            {Category::cSpiritTemple,});
ItemLocation SpiritTemple_MQ_ChestSwitchChest                 = ItemLocation::Chest      (0x06, 0x18, "Spirit Temple MQ Chest Switch Chest",                &Hints::SpiritTemple_MQ_ChestSwitchChest,           {Category::cSpiritTemple,});
ItemLocation SpiritTemple_MQ_BossKeyChest                     = ItemLocation::Chest      (0x06, 0x05, "Spirit Temple MQ Boss Key Chest",                    &Hints::SpiritTemple_MQ_BossKeyChest,               {Category::cSpiritTemple, Category::cVanillaBossKey});
ItemLocation SpiritTemple_MQ_MirrorPuzzleInvisibleChest       = ItemLocation::Chest      (0x06, 0x12, "Spirit Temple MQ Mirror Puzzle Invisible Chest",     &Hints::SpiritTemple_MQ_MirrorPuzzleInvisibleChest, {Category::cSpiritTemple, Category::cVanillaSmallKey});

//Shadow Temple Vanilla
ItemLocation ShadowTemple_MapChest                            = ItemLocation::Chest      (0x07, 0x01, "Shadow Temple Map Chest",                            &Hints::ShadowTemple_MapChest,                      {Category::cShadowTemple, Category::cVanillaMap,});
ItemLocation ShadowTemple_HoverBootsChest                     = ItemLocation::Chest      (0x07, 0x07, "Shadow Temple Hover Boots Chest",                    &Hints::ShadowTemple_HoverBootsChest,               {Category::cShadowTemple,});
ItemLocation ShadowTemple_CompassChest                        = ItemLocation::Chest      (0x07, 0x03, "Shadow Temple Compass Chest",                        &Hints::ShadowTemple_CompassChest,                  {Category::cShadowTemple, Category::cVanillaCompass,});
ItemLocation ShadowTemple_EarlySilverRupeeChest               = ItemLocation::Chest      (0x07, 0x02, "Shadow Temple Early Silver Rupee Chest",             &Hints::ShadowTemple_EarlySilverRupeeChest,         {Category::cShadowTemple, Category::cVanillaSmallKey});
ItemLocation ShadowTemple_InvisibleBladesVisibleChest         = ItemLocation::Chest      (0x07, 0x0C, "Shadow Temple Invisible Blades Visible Chest",       &Hints::ShadowTemple_InvisibleBladesVisibleChest,   {Category::cShadowTemple,});
ItemLocation ShadowTemple_InvisibleBladesInvisibleChest       = ItemLocation::Chest      (0x07, 0x16, "Shadow Temple Invisible Blades Invisible Chest",     &Hints::ShadowTemple_InvisibleBladesInvisibleChest, {Category::cShadowTemple,});
ItemLocation ShadowTemple_FallingSpikesLowerChest             = ItemLocation::Chest      (0x07, 0x05, "Shadow Temple Falling Spikes Lower Chest",           &Hints::ShadowTemple_FallingSpikesLowerChest,       {Category::cShadowTemple,});
ItemLocation ShadowTemple_FallingSpikesUpperChest             = ItemLocation::Chest      (0x07, 0x06, "Shadow Temple Falling Spikes Upper Chest",           &Hints::ShadowTemple_FallingSpikesUpperChest,       {Category::cShadowTemple,});
ItemLocation ShadowTemple_FallingSpikesSwitchChest            = ItemLocation::Chest      (0x07, 0x04, "Shadow Temple Falling Spikes Switch Chest",          &Hints::ShadowTemple_FallingSpikesSwitchChest,      {Category::cShadowTemple, Category::cVanillaSmallKey});
ItemLocation ShadowTemple_InvisibleSpikesChest                = ItemLocation::Chest      (0x07, 0x09, "Shadow Temple Invisible Spikes Chest",               &Hints::ShadowTemple_InvisibleSpikesChest,          {Category::cShadowTemple,});
ItemLocation ShadowTemple_WindHintChest                       = ItemLocation::Chest      (0x07, 0x15, "Shadow Temple Wind Hint Chest",                      &Hints::ShadowTemple_WindHintChest,                 {Category::cShadowTemple,});
ItemLocation ShadowTemple_AfterWindEnemyChest                 = ItemLocation::Chest      (0x07, 0x08, "Shadow Temple After Wind Enemy Chest",               &Hints::ShadowTemple_AfterWindEnemyChest,           {Category::cShadowTemple,});
ItemLocation ShadowTemple_AfterWindHiddenChest                = ItemLocation::Chest      (0x07, 0x14, "Shadow Temple After Wind Hidden Chest",              &Hints::ShadowTemple_AfterWindHiddenChest,          {Category::cShadowTemple, Category::cVanillaSmallKey});
ItemLocation ShadowTemple_SpikeWallsLeftChest                 = ItemLocation::Chest      (0x07, 0x0A, "Shadow Temple Spike Walls Left Chest",               &Hints::ShadowTemple_SpikeWallsLeftChest,           {Category::cShadowTemple,});
ItemLocation ShadowTemple_BossKeyChest                        = ItemLocation::Chest      (0x07, 0x0B, "Shadow Temple Boss Key Chest",                       &Hints::ShadowTemple_BossKeyChest,                  {Category::cShadowTemple, Category::cVanillaBossKey});
ItemLocation ShadowTemple_InvisibleFloormasterChest           = ItemLocation::Chest      (0x07, 0x0D, "Shadow Temple Invisible Floormaster Chest",          &Hints::ShadowTemple_InvisibleFloormasterChest,     {Category::cShadowTemple, Category::cVanillaSmallKey});
ItemLocation ShadowTemple_FreestandingKey                     = ItemLocation::Collectable(0x07, 0x01, "Shadow Temple Freestanding Key",                     &Hints::ShadowTemple_FreestandingKey,               {Category::cShadowTemple, Category::cVanillaSmallKey});
//Shadow Temple MQ
ItemLocation ShadowTemple_MQ_CompassChest                     = ItemLocation::Chest      (0x07, 0x01, "Shadow Temple MQ Compass Chest",                     &Hints::ShadowTemple_MQ_CompassChest,                  {Category::cShadowTemple, Category::cVanillaCompass,});
ItemLocation ShadowTemple_MQ_HoverBootsChest                  = ItemLocation::Chest      (0x07, 0x07, "Shadow Temple MQ Hover Boots Chest",                 &Hints::ShadowTemple_MQ_HoverBootsChest,               {Category::cShadowTemple,});
ItemLocation ShadowTemple_MQ_EarlyGibdosChest                 = ItemLocation::Chest      (0x07, 0x03, "Shadow Temple MQ Early Gibdos Chest",                &Hints::ShadowTemple_MQ_EarlyGibdosChest,              {Category::cShadowTemple, Category::cVanillaSmallKey});
ItemLocation ShadowTemple_MQ_MapChest                         = ItemLocation::Chest      (0x07, 0x02, "Shadow Temple MQ Map Chest",                         &Hints::ShadowTemple_MQ_MapChest,                      {Category::cShadowTemple, Category::cVanillaMap,});
ItemLocation ShadowTemple_MQ_BeamosSilverRupeesChest          = ItemLocation::Chest      (0x07, 0x0F, "Shadow Temple MQ Beamos Silver Rupees Chest",        &Hints::ShadowTemple_MQ_BeamosSilverRupeesChest,       {Category::cShadowTemple,});
ItemLocation ShadowTemple_MQ_FallingSpikesSwitchChest         = ItemLocation::Chest      (0x07, 0x04, "Shadow Temple MQ Falling Spikes Switch Chest",       &Hints::ShadowTemple_MQ_FallingSpikesSwitchChest,      {Category::cShadowTemple, Category::cVanillaSmallKey});
ItemLocation ShadowTemple_MQ_FallingSpikesLowerChest          = ItemLocation::Chest      (0x07, 0x05, "Shadow Temple MQ Falling Spikes Lower Chest",        &Hints::ShadowTemple_MQ_FallingSpikesLowerChest,       {Category::cShadowTemple,});
ItemLocation ShadowTemple_MQ_FallingSpikesUpperChest          = ItemLocation::Chest      (0x07, 0x06, "Shadow Temple MQ Falling Spikes Upper Chest",        &Hints::ShadowTemple_MQ_FallingSpikesUpperChest,       {Category::cShadowTemple,});
ItemLocation ShadowTemple_MQ_InvisibleSpikesChest             = ItemLocation::Chest      (0x07, 0x09, "Shadow Temple MQ Invisible Spikes Chest",            &Hints::ShadowTemple_MQ_InvisibleSpikesChest,          {Category::cShadowTemple,});
ItemLocation ShadowTemple_MQ_BossKeyChest                     = ItemLocation::Chest      (0x07, 0x0B, "Shadow Temple MQ Boss Key Chest",                    &Hints::ShadowTemple_MQ_BossKeyChest,                  {Category::cShadowTemple, Category::cVanillaBossKey});
ItemLocation ShadowTemple_MQ_SpikeWallsLeftChest              = ItemLocation::Chest      (0x07, 0x0A, "Shadow Temple MQ Spike Walls Left Chest",            &Hints::ShadowTemple_MQ_SpikeWallsLeftChest,           {Category::cShadowTemple,});
ItemLocation ShadowTemple_MQ_StalfosRoomChest                 = ItemLocation::Chest      (0x07, 0x10, "Shadow Temple MQ Stalfos Room Chest",                &Hints::ShadowTemple_MQ_StalfosRoomChest,              {Category::cShadowTemple,});
ItemLocation ShadowTemple_MQ_InvisibleBladesInvisibleChest    = ItemLocation::Chest      (0x07, 0x16, "Shadow Temple MQ Invisible Blades Invisible Chest",  &Hints::ShadowTemple_MQ_InvisibleBladesInvisibleChest, {Category::cShadowTemple, Category::cVanillaSmallKey});
ItemLocation ShadowTemple_MQ_InvisibleBladesVisibleChest      = ItemLocation::Chest      (0x07, 0x0C, "Shadow Temple MQ Invisible Blades Visible Chest",    &Hints::ShadowTemple_MQ_InvisibleBladesVisibleChest,   {Category::cShadowTemple,});
ItemLocation ShadowTemple_MQ_BombFlowerChest                  = ItemLocation::Chest      (0x07, 0x0D, "Shadow Temple MQ Bomb Flower Chest",                 &Hints::ShadowTemple_MQ_BombFlowerChest,               {Category::cShadowTemple,});
ItemLocation ShadowTemple_MQ_WindHintChest                    = ItemLocation::Chest      (0x07, 0x15, "Shadow Temple MQ Wind Hint Chest",                   &Hints::ShadowTemple_MQ_WindHintChest,                 {Category::cShadowTemple, Category::cVanillaSmallKey});
ItemLocation ShadowTemple_MQ_AfterWindHiddenChest             = ItemLocation::Chest      (0x07, 0x14, "Shadow Temple MQ After Wind Hidden Chest",           &Hints::ShadowTemple_MQ_AfterWindHiddenChest,          {Category::cShadowTemple,});
ItemLocation ShadowTemple_MQ_AfterWindEnemyChest              = ItemLocation::Chest      (0x07, 0x08, "Shadow Temple MQ After Wind Enemy Chest",            &Hints::ShadowTemple_MQ_AfterWindEnemyChest,           {Category::cShadowTemple,});
ItemLocation ShadowTemple_MQ_NearShipInvisibleChest           = ItemLocation::Chest      (0x07, 0x0E, "Shadow Temple MQ Near Ship Invisible Chest",         &Hints::ShadowTemple_MQ_NearShipInvisibleChest,        {Category::cShadowTemple, Category::cVanillaSmallKey});
ItemLocation ShadowTemple_MQ_FreestandingKey                  = ItemLocation::Collectable(0x07, 0x06, "Shadow Temple MQ Freestanding Key",                  &Hints::ShadowTemple_MQ_FreestandingKey,               {Category::cShadowTemple, Category::cVanillaSmallKey});

//Bottom of the Well Vanilla
ItemLocation BottomOfTheWell_FrontLeftFakeWallChest           = ItemLocation::Chest      (0x08, 0x08, "Bottom of the Well Front Left Fake Wall Chest",         &Hints::BottomOfTheWell_FrontLeftFakeWallChest,   {Category::cBottomOfTheWell, Category::cVanillaSmallKey});
ItemLocation BottomOfTheWell_FrontCenterBombableChest         = ItemLocation::Chest      (0x08, 0x02, "Bottom of the Well Front Center Bombable Chest",        &Hints::BottomOfTheWell_FrontCenterBombableChest, {Category::cBottomOfTheWell,});
ItemLocation BottomOfTheWell_RightBottomFakeWallChest         = ItemLocation::Chest      (0x08, 0x05, "Bottom of the Well Right Bottom Fake Wall Chest",       &Hints::BottomOfTheWell_RightBottomFakeWallChest, {Category::cBottomOfTheWell, Category::cVanillaSmallKey});
ItemLocation BottomOfTheWell_CompassChest                     = ItemLocation::Chest      (0x08, 0x01, "Bottom of the Well Compass Chest",                      &Hints::BottomOfTheWell_CompassChest,             {Category::cBottomOfTheWell, Category::cVanillaCompass,});
ItemLocation BottomOfTheWell_CenterSkulltulaChest             = ItemLocation::Chest      (0x08, 0x0E, "Bottom of the Well Center Skulltula Chest",             &Hints::BottomOfTheWell_CenterSkulltulaChest,     {Category::cBottomOfTheWell,});
ItemLocation BottomOfTheWell_BackLeftBombableChest            = ItemLocation::Chest      (0x08, 0x04, "Bottom of the Well Back Left Bombable Chest",           &Hints::BottomOfTheWell_BackLeftBombableChest,    {Category::cBottomOfTheWell,});
ItemLocation BottomOfTheWell_LensOfTruthChest                 = ItemLocation::Chest      (0x08, 0x03, "Bottom of the Well Lens of Truth Chest",                &Hints::BottomOfTheWell_LensOfTruthChest,         {Category::cBottomOfTheWell, Category::cSongDungeonReward});
ItemLocation BottomOfTheWell_InvisibleChest                   = ItemLocation::Chest      (0x08, 0x14, "Bottom of the Well Invisible Chest",                    &Hints::BottomOfTheWell_InvisibleChest,           {Category::cBottomOfTheWell,});
ItemLocation BottomOfTheWell_UnderwaterFrontChest             = ItemLocation::Chest      (0x08, 0x10, "Bottom of the Well Underwater Front Chest",             &Hints::BottomOfTheWell_UnderwaterFrontChest,     {Category::cBottomOfTheWell,});
ItemLocation BottomOfTheWell_UnderwaterLeftChest              = ItemLocation::Chest      (0x08, 0x09, "Bottom of the Well Underwater Left Chest",              &Hints::BottomOfTheWell_UnderwaterLeftChest,      {Category::cBottomOfTheWell,});
ItemLocation BottomOfTheWell_MapChest                         = ItemLocation::Chest      (0x08, 0x07, "Bottom of the Well Map Chest",                          &Hints::BottomOfTheWell_MapChest,                 {Category::cBottomOfTheWell, Category::cVanillaMap,});
ItemLocation BottomOfTheWell_FireKeeseChest                   = ItemLocation::Chest      (0x08, 0x0A, "Bottom of the Well Fire Keese Chest",                   &Hints::BottomOfTheWell_FireKeeseChest,           {Category::cBottomOfTheWell,});
ItemLocation BottomOfTheWell_LikeLikeChest                    = ItemLocation::Chest      (0x08, 0x0C, "Bottom of the Well Like Like Chest",                    &Hints::BottomOfTheWell_LikeLikeChest,            {Category::cBottomOfTheWell,});
ItemLocation BottomOfTheWell_FreestandingKey                  = ItemLocation::Collectable(0x08, 0x01, "Bottom of the Well Freestanding Key",                   &Hints::BottomOfTheWell_FreestandingKey,          {Category::cBottomOfTheWell, Category::cVanillaSmallKey});
//Bottom of the Well MQ&Hints::BottomOfTheWell_,
ItemLocation BottomOfTheWell_MQ_MapChest                      = ItemLocation::Chest      (0x08, 0x03, "Bottom of the Well MQ Map Chest",                       &Hints::BottomOfTheWell_MQ_MapChest,                     {Category::cBottomOfTheWell, Category::cVanillaMap,});
ItemLocation BottomOfTheWell_MQ_LensOfTruthChest              = ItemLocation::Chest      (0x08, 0x01, "Bottom of the Well MQ Lens of Truth Chest",             &Hints::BottomOfTheWell_MQ_LensOfTruthChest,             {Category::cBottomOfTheWell, Category::cSongDungeonReward});
ItemLocation BottomOfTheWell_MQ_CompassChest                  = ItemLocation::Chest      (0x08, 0x02, "Bottom of the Well MQ Compass Chest",                   &Hints::BottomOfTheWell_MQ_CompassChest,                 {Category::cBottomOfTheWell, Category::cVanillaCompass,});
ItemLocation BottomOfTheWell_MQ_DeadHandFreestandingKey       = ItemLocation::Collectable(0x08, 0x02, "Bottom of the Well MQ Dead Hand Freestanding Key",      &Hints::BottomOfTheWell_MQ_DeadHandFreestandingKey,      {Category::cBottomOfTheWell, Category::cVanillaSmallKey});
ItemLocation BottomOfTheWell_MQ_EastInnerRoomFreestandingKey  = ItemLocation::Collectable(0x08, 0x01, "Bottom of the Well MQ East Inner Room Freestanding Key",&Hints::BottomOfTheWell_MQ_EastInnerRoomFreestandingKey, {Category::cBottomOfTheWell, Category::cVanillaSmallKey});

//Ice Cavern Vanilla
ItemLocation IceCavern_MapChest                               = ItemLocation::Chest      (0x09, 0x00, "Ice Cavern Map Chest",                                  &Hints::IceCavern_MapChest,           {Category::cIceCavern, Category::cVanillaMap,});
ItemLocation IceCavern_CompassChest                           = ItemLocation::Chest      (0x09, 0x01, "Ice Cavern Compass Chest",                              &Hints::IceCavern_CompassChest,       {Category::cIceCavern, Category::cVanillaCompass,});
ItemLocation IceCavern_IronBootsChest                         = ItemLocation::Chest      (0x09, 0x02, "Ice Cavern Iron Boots Chest",                           &Hints::IceCavern_IronBootsChest,     {Category::cIceCavern,});
ItemLocation IceCavern_FreestandingPoH                        = ItemLocation::Collectable(0x09, 0x01, "Ice Cavern Freestanding PoH",                           &Hints::IceCavern_FreestandingPoH,    {Category::cIceCavern,});
//Ice Cavern MQ&Hints::IceCavern_,
ItemLocation IceCavern_MQ_IronBootsChest                      = ItemLocation::Chest      (0x09, 0x02, "Ice Cavern MQ Iron Boots Chest",                        &Hints::IceCavern_MQ_IronBootsChest,  {Category::cIceCavern,});
ItemLocation IceCavern_MQ_CompassChest                        = ItemLocation::Chest      (0x09, 0x00, "Ice Cavern MQ Compass Chest",                           &Hints::IceCavern_MQ_CompassChest,    {Category::cIceCavern, Category::cVanillaCompass,});
ItemLocation IceCavern_MQ_MapChest                            = ItemLocation::Chest      (0x09, 0x01, "Ice Cavern MQ Map Chest",                               &Hints::IceCavern_MQ_MapChest,        {Category::cIceCavern, Category::cVanillaMap,});
ItemLocation IceCavern_MQ_FreestandingPoH                     = ItemLocation::Collectable(0x09, 0x01, "Ice Cavern MQ Freestanding PoH",                        &Hints::IceCavern_MQ_FreestandingPoH, {Category::cIceCavern,});

//Gerudo Training Ground Vanilla
ItemLocation GerudoTrainingGrounds_LobbyLeftChest             = ItemLocation::Chest      (0x0B, 0x13, "Gerudo Training Grounds Lobby Left Chest",              &Hints::GerudoTrainingGrounds_LobbyLeftChest,             {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_LobbyRightChest            = ItemLocation::Chest      (0x0B, 0x07, "Gerudo Training Grounds Lobby Right Chest",             &Hints::GerudoTrainingGrounds_LobbyRightChest,            {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_StalfosChest               = ItemLocation::Chest      (0x0B, 0x00, "Gerudo Training Grounds Stalfos Chest",                 &Hints::GerudoTrainingGrounds_StalfosChest,               {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
ItemLocation GerudoTrainingGrounds_BeamosChest                = ItemLocation::Chest      (0x0B, 0x01, "Gerudo Training Grounds Beamos Chest",                  &Hints::GerudoTrainingGrounds_BeamosChest,                {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
ItemLocation GerudoTrainingGrounds_HiddenCeilingChest         = ItemLocation::Chest      (0x0B, 0x0B, "Gerudo Training Grounds Hidden Ceiling Chest",          &Hints::GerudoTrainingGrounds_HiddenCeilingChest,         {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
ItemLocation GerudoTrainingGrounds_MazePathFirstChest         = ItemLocation::Chest      (0x0B, 0x06, "Gerudo Training Grounds Maze Path First Chest",         &Hints::GerudoTrainingGrounds_MazePathFirstChest,         {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MazePathSecondChest        = ItemLocation::Chest      (0x0B, 0x0A, "Gerudo Training Grounds Maze Path Second Chest",        &Hints::GerudoTrainingGrounds_MazePathSecondChest,        {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MazePathThirdChest         = ItemLocation::Chest      (0x0B, 0x09, "Gerudo Training Grounds Maze Path Third Chest",         &Hints::GerudoTrainingGrounds_MazePathThirdChest,         {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MazePathFinalChest         = ItemLocation::Chest      (0x0B, 0x0C, "Gerudo Training Grounds Maze Path Final Chest",         &Hints::GerudoTrainingGrounds_MazePathFinalChest,         {Category::cGerudoTrainingGrounds, Category::cSongDungeonReward});
ItemLocation GerudoTrainingGrounds_MazeRightCentralChest      = ItemLocation::Chest      (0x0B, 0x05, "Gerudo Training Grounds Maze Right Central Chest",      &Hints::GerudoTrainingGrounds_MazeRightCentralChest,      {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MazeRightSideChest         = ItemLocation::Chest      (0x0B, 0x08, "Gerudo Training Grounds Maze Right Side Chest",         &Hints::GerudoTrainingGrounds_MazeRightSideChest,         {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_UnderwaterSilverRupeeChest = ItemLocation::Chest      (0x0B, 0x0D, "Gerudo Training Grounds Underwater Silver Rupee Chest", &Hints::GerudoTrainingGrounds_UnderwaterSilverRupeeChest, {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
ItemLocation GerudoTrainingGrounds_HammerRoomClearChest       = ItemLocation::Chest      (0x0B, 0x12, "Gerudo Training Grounds Hammer Room Clear Chest",       &Hints::GerudoTrainingGrounds_HammerRoomClearChest,       {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_HammerRoomSwitchChest      = ItemLocation::Chest      (0x0B, 0x10, "Gerudo Training Grounds Hammer Room Switch Chest",      &Hints::GerudoTrainingGrounds_HammerRoomSwitchChest,      {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
ItemLocation GerudoTrainingGrounds_EyeStatueChest             = ItemLocation::Chest      (0x0B, 0x03, "Gerudo Training Grounds Eye Statue Chest",              &Hints::GerudoTrainingGrounds_EyeStatueChest,             {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
ItemLocation GerudoTrainingGrounds_NearScarecrowChest         = ItemLocation::Chest      (0x0B, 0x04, "Gerudo Training Grounds Near Scarecrow Chest",          &Hints::GerudoTrainingGrounds_NearScarecrowChest,         {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
ItemLocation GerudoTrainingGrounds_BeforeHeavyBlockChest      = ItemLocation::Chest      (0x0B, 0x11, "Gerudo Training Grounds Before Heavy Block Chest",      &Hints::GerudoTrainingGrounds_BeforeHeavyBlockChest,      {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_HeavyBlockFirstChest       = ItemLocation::Chest      (0x0B, 0x0F, "Gerudo Training Grounds Heavy Block First Chest",       &Hints::GerudoTrainingGrounds_HeavyBlockFirstChest,       {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_HeavyBlockSecondChest      = ItemLocation::Chest      (0x0B, 0x0E, "Gerudo Training Grounds Heavy Block Second Chest",      &Hints::GerudoTrainingGrounds_HeavyBlockSecondChest,      {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_HeavyBlockThirdChest       = ItemLocation::Chest      (0x0B, 0x14, "Gerudo Training Grounds Heavy Block Third Chest",       &Hints::GerudoTrainingGrounds_HeavyBlockThirdChest,       {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
ItemLocation GerudoTrainingGrounds_HeavyBlockFourthChest      = ItemLocation::Chest      (0x0B, 0x02, "Gerudo Training Grounds Heavy Block Fourth Chest",      &Hints::GerudoTrainingGrounds_HeavyBlockFourthChest,      {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_FreestandingKey            = ItemLocation::Collectable(0x0B, 0x01, "Gerudo Training Grounds Freestanding Key",              &Hints::GerudoTrainingGrounds_FreestandingKey,            {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
//Gerudo Training Grounds MQ
ItemLocation GerudoTrainingGrounds_MQ_LobbyRightChest         = ItemLocation::Chest      (0x0B, 0x07, "Gerudo Training Grounds MQ Lobby Right Chest",          &Hints::GerudoTrainingGrounds_MQ_LobbyRightChest,        {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MQ_LobbyLeftChest          = ItemLocation::Chest      (0x0B, 0x13, "Gerudo Training Grounds MQ Lobby Left Chest",           &Hints::GerudoTrainingGrounds_MQ_LobbyLeftChest,         {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MQ_FirstIronKnuckleChest   = ItemLocation::Chest      (0x0B, 0x00, "Gerudo Training Grounds MQ First Iron Knuckle Chest",   &Hints::GerudoTrainingGrounds_MQ_FirstIronKnuckleChest,  {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MQ_BeforeHeavyBlockChest   = ItemLocation::Chest      (0x0B, 0x11, "Gerudo Training Grounds MQ Before Heavy Block Chest",   &Hints::GerudoTrainingGrounds_MQ_BeforeHeavyBlockChest,  {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MQ_EyeStatueChest          = ItemLocation::Chest      (0x0B, 0x03, "Gerudo Training Grounds MQ Eye Statue Chest",           &Hints::GerudoTrainingGrounds_MQ_EyeStatueChest,         {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MQ_FlameCircleChest        = ItemLocation::Chest      (0x0B, 0x0E, "Gerudo Training Grounds MQ Flame Circle Chest",         &Hints::GerudoTrainingGrounds_MQ_FlameCircleChest,       {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
ItemLocation GerudoTrainingGrounds_MQ_SecondIronKnuckleChest  = ItemLocation::Chest      (0x0B, 0x12, "Gerudo Training Grounds MQ Second Iron Knuckle Chest",  &Hints::GerudoTrainingGrounds_MQ_SecondIronKnuckleChest, {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MQ_DinolfosChest           = ItemLocation::Chest      (0x0B, 0x01, "Gerudo Training Grounds MQ Dinolfos Chest",             &Hints::GerudoTrainingGrounds_MQ_DinolfosChest,          {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
ItemLocation GerudoTrainingGrounds_MQ_IceArrowsChest          = ItemLocation::Chest      (0x0B, 0x04, "Gerudo Training Grounds MQ Ice Arrows Chest",           &Hints::GerudoTrainingGrounds_MQ_IceArrowsChest,         {Category::cGerudoTrainingGrounds, Category::cSongDungeonReward});
ItemLocation GerudoTrainingGrounds_MQ_MazeRightCentralChest   = ItemLocation::Chest      (0x0B, 0x05, "Gerudo Training Grounds MQ Maze Right Central Chest",   &Hints::GerudoTrainingGrounds_MQ_MazeRightCentralChest,  {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MQ_MazePathFirstChest      = ItemLocation::Chest      (0x0B, 0x06, "Gerudo Training Grounds MQ Maze Path First Chest",      &Hints::GerudoTrainingGrounds_MQ_MazePathFirstChest,     {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MQ_MazeRightSideChest      = ItemLocation::Chest      (0x0B, 0x08, "Gerudo Training Grounds MQ Maze Right Side Chest",      &Hints::GerudoTrainingGrounds_MQ_MazeRightSideChest,     {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MQ_MazePathThirdChest      = ItemLocation::Chest      (0x0B, 0x09, "Gerudo Training Grounds MQ Maze Path Third Chest",      &Hints::GerudoTrainingGrounds_MQ_MazePathThirdChest,     {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MQ_MazePathSecondChest     = ItemLocation::Chest      (0x0B, 0x0A, "Gerudo Training Grounds MQ Maze Path Second Chest",     &Hints::GerudoTrainingGrounds_MQ_MazePathSecondChest,    {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MQ_HiddenCeilingChest      = ItemLocation::Chest      (0x0B, 0x0B, "Gerudo Training Grounds MQ Hidden Ceiling Chest",       &Hints::GerudoTrainingGrounds_MQ_HiddenCeilingChest,     {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MQ_UnderwaterSilverRupeeChest = ItemLocation::Chest   (0x0B, 0x0D, "Gerudo Training Grounds MQ Underwater Silver Rupee Chest", &Hints::GerudoTrainingGrounds_MQ_UnderwaterSilverRupeeChest, {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
ItemLocation GerudoTrainingGrounds_MQ_HeavyBlockChest         = ItemLocation::Chest      (0x0B, 0x02, "Gerudo Training Grounds MQ Heavy Block Chest",          &Hints::GerudoTrainingGrounds_MQ_HeavyBlockChest,        {Category::cGerudoTrainingGrounds,});

//Ganons Castle Shared
ItemLocation GanonsCastle_BossKeyChest                        = ItemLocation::Chest      (0x0A, 0x0B, "Ganon's Castle Boss Key Chest",                         &Hints::GanonsCastle_BossKeyChest,                    {Category::cGanonsCastle,});
//Ganons Castle Vanilla
ItemLocation GanonsCastle_ForestTrialChest                    = ItemLocation::Chest      (0x0D, 0x09, "Ganon's Castle Forest Trial Chest",                     &Hints::GanonsCastle_ForestTrialChest,                {Category::cGanonsCastle,});
ItemLocation GanonsCastle_WaterTrialLeftChest                 = ItemLocation::Chest      (0x0D, 0x07, "Ganon's Castle Water Trial Left Chest",                 &Hints::GanonsCastle_WaterTrialLeftChest,             {Category::cGanonsCastle,});
ItemLocation GanonsCastle_WaterTrialRightChest                = ItemLocation::Chest      (0x0D, 0x06, "Ganon's Castle Water Trial Right Chest",                &Hints::GanonsCastle_WaterTrialRightChest,            {Category::cGanonsCastle,});
ItemLocation GanonsCastle_ShadowTrialFrontChest               = ItemLocation::Chest      (0x0D, 0x08, "Ganon's Castle Shadow Trial Front Chest",               &Hints::GanonsCastle_ShadowTrialFrontChest,           {Category::cGanonsCastle,});
ItemLocation GanonsCastle_ShadowTrialGoldenGauntletsChest     = ItemLocation::Chest      (0x0D, 0x05, "Ganon's Castle Shadow Trial Golden Gauntlets Chest",    &Hints::GanonsCastle_ShadowTrialGoldenGauntletsChest, {Category::cGanonsCastle,});
ItemLocation GanonsCastle_SpiritTrialCrystalSwitchChest       = ItemLocation::Chest      (0x0D, 0x12, "Ganon's Castle Spirit Trial Crystal Switch Chest",      &Hints::GanonsCastle_SpiritTrialCrystalSwitchChest,   {Category::cGanonsCastle,});
ItemLocation GanonsCastle_SpiritTrialInvisibleChest           = ItemLocation::Chest      (0x0D, 0x14, "Ganon's Castle Spirit Trial Invisible Chest",           &Hints::GanonsCastle_SpiritTrialInvisibleChest,       {Category::cGanonsCastle,});
ItemLocation GanonsCastle_LightTrialFirstLeftChest            = ItemLocation::Chest      (0x0D, 0x0C, "Ganon's Castle Light Trial First Left Chest",           &Hints::GanonsCastle_LightTrialFirstLeftChest,        {Category::cGanonsCastle,});
ItemLocation GanonsCastle_LightTrialSecondLeftChest           = ItemLocation::Chest      (0x0D, 0x0B, "Ganon's Castle Light Trial Second Left Chest",          &Hints::GanonsCastle_LightTrialSecondLeftChest,       {Category::cGanonsCastle,});
ItemLocation GanonsCastle_LightTrialThirdLeftChest            = ItemLocation::Chest      (0x0D, 0x0D, "Ganon's Castle Light Trial Third Left Chest",           &Hints::GanonsCastle_LightTrialThirdLeftChest,        {Category::cGanonsCastle,});
ItemLocation GanonsCastle_LightTrialFirstRightChest           = ItemLocation::Chest      (0x0D, 0x0E, "Ganon's Castle Light Trial First Right Chest",          &Hints::GanonsCastle_LightTrialFirstRightChest,       {Category::cGanonsCastle,});
ItemLocation GanonsCastle_LightTrialSecondRightChest          = ItemLocation::Chest      (0x0D, 0x0A, "Ganon's Castle Light Trial Second Right Chest",         &Hints::GanonsCastle_LightTrialSecondRightChest,      {Category::cGanonsCastle,});
ItemLocation GanonsCastle_LightTrialThirdRightChest           = ItemLocation::Chest      (0x0D, 0x0F, "Ganon's Castle Light Trial Third Right Chest",          &Hints::GanonsCastle_LightTrialThirdRightChest,       {Category::cGanonsCastle,});
ItemLocation GanonsCastle_LightTrialInvisibleEnemiesChest     = ItemLocation::Chest      (0x0D, 0x10, "Ganon's Castle Light Trial Invisible Enemies Chest",    &Hints::GanonsCastle_LightTrialInvisibleEnemiesChest, {Category::cGanonsCastle, Category::cVanillaSmallKey});
ItemLocation GanonsCastle_LightTrialLullabyChest              = ItemLocation::Chest      (0x0D, 0x11, "Ganon's Castle Light Trial Lullaby Chest",              &Hints::GanonsCastle_LightTrialLullabyChest,          {Category::cGanonsCastle, Category::cVanillaSmallKey});
ItemLocation GanonsCastle_DekuScrubCenterLeft                 = ItemLocation::Base       (0x0D, 0x37, "Ganon's Castle Deku Scrub Center-Left",                 &Hints::GanonsCastle_DekuScrubCenterLeft,             {Category::cGanonsCastle, Category::cDekuScrub,});
ItemLocation GanonsCastle_DekuScrubCenterRight                = ItemLocation::Base       (0x0D, 0x33, "Ganon's Castle Deku Scrub Center-Right",                &Hints::GanonsCastle_DekuScrubCenterRight,            {Category::cGanonsCastle, Category::cDekuScrub,});
ItemLocation GanonsCastle_DekuScrubRight                      = ItemLocation::Base       (0x0D, 0x39, "Ganon's Castle Deku Scrub Right",                       &Hints::GanonsCastle_DekuScrubRight,                  {Category::cGanonsCastle, Category::cDekuScrub,});
ItemLocation GanonsCastle_DekuScrubLeft                       = ItemLocation::Base       (0x0D, 0x3A, "Ganon's Castle Deku Scrub Left",                        &Hints::GanonsCastle_DekuScrubLeft,                   {Category::cGanonsCastle, Category::cDekuScrub,});
//Ganons Castle MQ
ItemLocation GanonsCastle_MQ_WaterTrialChest                  = ItemLocation::Chest      (0x0D, 0x01, "Ganon's Castle MQ Water Trial Chest",                   &Hints::GanonsCastle_MQ_WaterTrialChest,                 {Category::cGanonsCastle,});
ItemLocation GanonsCastle_MQ_ForestTrialEyeSwitchChest        = ItemLocation::Chest      (0x0D, 0x02, "Ganon's Castle MQ Forest Trial Eye Switch Chest",       &Hints::GanonsCastle_MQ_ForestTrialEyeSwitchChest,       {Category::cGanonsCastle,});
ItemLocation GanonsCastle_MQ_ForestTrialFrozenEyeSwitchChest  = ItemLocation::Chest      (0x0D, 0x03, "Ganon's Castle MQ Forest Trial Frozen Eye Switch Chest",&Hints::GanonsCastle_MQ_ForestTrialFrozenEyeSwitchChest, {Category::cGanonsCastle,});
ItemLocation GanonsCastle_MQ_LightTrialLullabyChest           = ItemLocation::Chest      (0x0D, 0x04, "Ganon's Castle MQ Light Trial Lullaby Chest",           &Hints::GanonsCastle_MQ_LightTrialLullabyChest,          {Category::cGanonsCastle,});
ItemLocation GanonsCastle_MQ_ShadowTrialBombFlowerChest       = ItemLocation::Chest      (0x0D, 0x00, "Ganon's Castle MQ Shadow Trial Bomb Flower Chest",      &Hints::GanonsCastle_MQ_ShadowTrialBombFlowerChest,      {Category::cGanonsCastle,});
ItemLocation GanonsCastle_MQ_ShadowTrialEyeSwitchChest        = ItemLocation::Chest      (0x0D, 0x05, "Ganon's Castle MQ Shadow Trial Eye Switch Chest",       &Hints::GanonsCastle_MQ_ShadowTrialEyeSwitchChest,       {Category::cGanonsCastle,  Category::cVanillaSmallKey});
ItemLocation GanonsCastle_MQ_SpiritTrialGoldenGauntletsChest  = ItemLocation::Chest      (0x0D, 0x06, "Ganon's Castle MQ Spirit Trial Golden Gauntlets Chest", &Hints::GanonsCastle_MQ_SpiritTrialGoldenGauntletsChest, {Category::cGanonsCastle,});
ItemLocation GanonsCastle_MQ_SpiritTrialSunBackRightChest     = ItemLocation::Chest      (0x0D, 0x07, "Ganon's Castle MQ Spirit Trial Sun Back Right Chest",   &Hints::GanonsCastle_MQ_SpiritTrialSunBackRightChest,    {Category::cGanonsCastle,});
ItemLocation GanonsCastle_MQ_SpiritTrialSunBackLeftChest      = ItemLocation::Chest      (0x0D, 0x08, "Ganon's Castle MQ Spirit Trial Sun Back Left Chest",    &Hints::GanonsCastle_MQ_SpiritTrialSunBackLeftChest,     {Category::cGanonsCastle,  Category::cVanillaSmallKey});
ItemLocation GanonsCastle_MQ_SpiritTrialSunFrontLeftChest     = ItemLocation::Chest      (0x0D, 0x09, "Ganon's Castle MQ Spirit Trial Sun Front Left Chest",   &Hints::GanonsCastle_MQ_SpiritTrialSunFrontLeftChest,    {Category::cGanonsCastle,});
ItemLocation GanonsCastle_MQ_SpiritTrialFirstChest            = ItemLocation::Chest      (0x0D, 0x0A, "Ganon's Castle MQ Spirit Trial First Chest",            &Hints::GanonsCastle_MQ_SpiritTrialFirstChest,           {Category::cGanonsCastle,});
ItemLocation GanonsCastle_MQ_SpiritTrialInvisibleChest        = ItemLocation::Chest      (0x0D, 0x14, "Ganon's Castle MQ Spirit Trial Invisible Chest",        &Hints::GanonsCastle_MQ_SpiritTrialInvisibleChest,       {Category::cGanonsCastle,});
ItemLocation GanonsCastle_MQ_ForestTrialFreestandingKey       = ItemLocation::Collectable(0x0D, 0x01, "Ganon's Castle MQ Forest Trial Freestanding Key",       &Hints::GanonsCastle_MQ_ForestTrialFreestandingKey,      {Category::cGanonsCastle, Category::cVanillaSmallKey});
ItemLocation GanonsCastle_MQ_DekuScrubRight                   = ItemLocation::Base       (0x0D, 0x30, "Ganon's Castle MQ Deku Scrub Right",                    &Hints::GanonsCastle_MQ_DekuScrubRight,                  {Category::cGanonsCastle, Category::cDekuScrub,});
ItemLocation GanonsCastle_MQ_DekuScrubCenterLeft              = ItemLocation::Base       (0x0D, 0x37, "Ganon's Castle MQ Deku Scrub Center-Left",              &Hints::GanonsCastle_MQ_DekuScrubCenterLeft,             {Category::cGanonsCastle, Category::cDekuScrub,});
ItemLocation GanonsCastle_MQ_DekuScrubCenter                  = ItemLocation::Base       (0x0D, 0x33, "Ganon's Castle MQ Deku Scrub Center",                   &Hints::GanonsCastle_MQ_DekuScrubCenter,                 {Category::cGanonsCastle, Category::cDekuScrub,});
ItemLocation GanonsCastle_MQ_DekuScrubCenterRight             = ItemLocation::Base       (0x0D, 0x39, "Ganon's Castle MQ Deku Scrub Center-Right",             &Hints::GanonsCastle_MQ_DekuScrubCenterRight,            {Category::cGanonsCastle, Category::cDekuScrub,});
ItemLocation GanonsCastle_MQ_DekuScrubLeft                    = ItemLocation::Base       (0x0D, 0x3A, "Ganon's Castle MQ Deku Scrub Left",                     &Hints::GanonsCastle_MQ_DekuScrubLeft,                   {Category::cGanonsCastle, Category::cDekuScrub,});

/*-------------------------------
   --- GOLD SKULLTULA TOKENS ---
  -------------------------------*/

//Dungeons
ItemLocation DekuTree_GS_BasementBackRoom                 = ItemLocation::GSToken(0x00, 0x01, "Deku Tree GS Basement Back Room",                  &Hints::DekuTree_GS_BasementBackRoom,                {Category::cDekuTree, Category::cSkulltula,});
ItemLocation DekuTree_GS_BasementGate                     = ItemLocation::GSToken(0x00, 0x02, "Deku Tree GS Basement Gate",                       &Hints::DekuTree_GS_BasementGate,                    {Category::cDekuTree, Category::cSkulltula,});
ItemLocation DekuTree_GS_BasementVines                    = ItemLocation::GSToken(0x00, 0x04, "Deku Tree GS Basement Vines",                      &Hints::DekuTree_GS_BasementVines,                   {Category::cDekuTree, Category::cSkulltula,});
ItemLocation DekuTree_GS_CompassRoom                      = ItemLocation::GSToken(0x00, 0x08, "Deku Tree GS Compass Room",                        &Hints::DekuTree_GS_CompassRoom,                     {Category::cDekuTree, Category::cSkulltula,});

ItemLocation DekuTree_MQ_GS_Lobby                         = ItemLocation::GSToken(0x00, 0x02, "Deku Tree MQ GS Lobby",                            &Hints::DekuTree_MQ_GS_Lobby,                        {Category::cDekuTree, Category::cSkulltula,});
ItemLocation DekuTree_MQ_GS_CompassRoom                   = ItemLocation::GSToken(0x00, 0x08, "Deku Tree MQ GS Compass Room",                     &Hints::DekuTree_MQ_GS_CompassRoom,                  {Category::cDekuTree, Category::cSkulltula,});
ItemLocation DekuTree_MQ_GS_BasementGravesRoom            = ItemLocation::GSToken(0x00, 0x04, "Deku Tree MQ GS Basement Graves Room",             &Hints::DekuTree_MQ_GS_BasementGravesRoom,           {Category::cDekuTree, Category::cSkulltula,});
ItemLocation DekuTree_MQ_GS_BasementBackRoom              = ItemLocation::GSToken(0x00, 0x01, "Deku Tree MQ GS Basement Back Room",               &Hints::DekuTree_MQ_GS_BasementBackRoom,             {Category::cDekuTree, Category::cSkulltula,});

ItemLocation DodongosCavern_GS_VinesAboveStairs           = ItemLocation::GSToken(0x01, 0x01, "Dodongos Cavern GS Vines Above Stairs",            &Hints::DodongosCavern_GS_VinesAboveStairs,          {Category::cDodongosCavern, Category::cSkulltula,});
ItemLocation DodongosCavern_GS_Scarecrow                  = ItemLocation::GSToken(0x01, 0x02, "Dodongos Cavern GS Scarecrow",                     &Hints::DodongosCavern_GS_Scarecrow,                 {Category::cDodongosCavern, Category::cSkulltula,});
ItemLocation DodongosCavern_GS_AlcoveAboveStairs          = ItemLocation::GSToken(0x01, 0x04, "Dodongos Cavern GS Alcove Above Stairs",           &Hints::DodongosCavern_GS_AlcoveAboveStairs,         {Category::cDodongosCavern, Category::cSkulltula,});
ItemLocation DodongosCavern_GS_BackRoom                   = ItemLocation::GSToken(0x01, 0x08, "Dodongos Cavern GS Back Room",                     &Hints::DodongosCavern_GS_BackRoom,                  {Category::cDodongosCavern, Category::cSkulltula,});
ItemLocation DodongosCavern_GS_SideRoomNearLowerLizalfos  = ItemLocation::GSToken(0x01, 0x10, "Dodongos Cavern GS Side Room Near Lower Lizalfos", &Hints::DodongosCavern_GS_SideRoomNearLowerLizalfos, {Category::cDodongosCavern, Category::cSkulltula,});

ItemLocation DodongosCavern_MQ_GS_ScrubRoom               = ItemLocation::GSToken(0x01, 0x02, "Dodongos Cavern MQ GS Scrub Room",                 &Hints::DodongosCavern_MQ_GS_ScrubRoom,              {Category::cDodongosCavern, Category::cSkulltula,});
ItemLocation DodongosCavern_MQ_GS_SongOfTimeBlockRoom     = ItemLocation::GSToken(0x01, 0x08, "Dodongos Cavern MQ GS Song of Time Block Room",    &Hints::DodongosCavern_MQ_GS_SongOfTimeBlockRoom,    {Category::cDodongosCavern, Category::cSkulltula,});
ItemLocation DodongosCavern_MQ_GS_LizalfosRoom            = ItemLocation::GSToken(0x01, 0x04, "Dodongos Cavern MQ GS Lizalfos Room",              &Hints::DodongosCavern_MQ_GS_LizalfosRoom,           {Category::cDodongosCavern, Category::cSkulltula,});
ItemLocation DodongosCavern_MQ_GS_LarvaeRoom              = ItemLocation::GSToken(0x01, 0x10, "Dodongos Cavern MQ GS Larvae Room",                &Hints::DodongosCavern_MQ_GS_LarvaeRoom,             {Category::cDodongosCavern, Category::cSkulltula,});
ItemLocation DodongosCavern_MQ_GS_BackRoom                = ItemLocation::GSToken(0x01, 0x01, "Dodongos Cavern MQ GS Back Room",                  &Hints::DodongosCavern_MQ_GS_BackRoom,               {Category::cDodongosCavern, Category::cSkulltula,});

ItemLocation JabuJabusBelly_GS_LobbyBasementLower         = ItemLocation::GSToken(0x02, 0x01, "Jabu Jabus Belly GS Lobby Basement Lower",         &Hints::JabuJabusBelly_GS_LobbyBasementLower,        {Category::cJabuJabusBelly, Category::cSkulltula,});
ItemLocation JabuJabusBelly_GS_LobbyBasementUpper         = ItemLocation::GSToken(0x02, 0x02, "Jabu Jabus Belly GS Lobby Basement Upper",         &Hints::JabuJabusBelly_GS_LobbyBasementUpper,        {Category::cJabuJabusBelly, Category::cSkulltula,});
ItemLocation JabuJabusBelly_GS_NearBoss                   = ItemLocation::GSToken(0x02, 0x04, "Jabu Jabus Belly GS Near Boss",                    &Hints::JabuJabusBelly_GS_NearBoss,                  {Category::cJabuJabusBelly, Category::cSkulltula,});
ItemLocation JabuJabusBelly_GS_WaterSwitchRoom            = ItemLocation::GSToken(0x02, 0x08, "Jabu Jabus Belly GS Water Switch Room",            &Hints::JabuJabusBelly_GS_WaterSwitchRoom,           {Category::cJabuJabusBelly, Category::cSkulltula,});

ItemLocation JabuJabusBelly_MQ_GS_TailPasaranRoom         = ItemLocation::GSToken(0x02, 0x04, "Jabu Jabus Belly MQ GS Tail Parasan Room",         &Hints::JabuJabusBelly_MQ_GS_TailPasaranRoom,        {Category::cJabuJabusBelly, Category::cSkulltula,});
ItemLocation JabuJabusBelly_MQ_GS_InvisibleEnemiesRoom    = ItemLocation::GSToken(0x02, 0x08, "Jabu Jabus Belly MQ GS Invisible Enemies Room",    &Hints::JabuJabusBelly_MQ_GS_InvisibleEnemiesRoom,   {Category::cJabuJabusBelly, Category::cSkulltula,});
ItemLocation JabuJabusBelly_MQ_GS_BoomerangChestRoom      = ItemLocation::GSToken(0x02, 0x01, "Jabu Jabus Belly MQ GS Boomerang Chest Room",      &Hints::JabuJabusBelly_MQ_GS_BoomerangChestRoom,     {Category::cJabuJabusBelly, Category::cSkulltula,});
ItemLocation JabuJabusBelly_MQ_GS_NearBoss                = ItemLocation::GSToken(0x02, 0x02, "Jabu Jabus Belly MQ GS Near Boss",                 &Hints::JabuJabusBelly_MQ_GS_NearBoss,               {Category::cJabuJabusBelly, Category::cSkulltula,});

ItemLocation ForestTemple_GS_RaisedIslandCourtyard        = ItemLocation::GSToken(0x03, 0x01, "Forest Temple GS Raised Island Courtyard",         &Hints::ForestTemple_GS_RaisedIslandCourtyard,       {Category::cForestTemple, Category::cSkulltula,});
ItemLocation ForestTemple_GS_FirstRoom                    = ItemLocation::GSToken(0x03, 0x02, "Forest Temple GS First Room",                      &Hints::ForestTemple_GS_FirstRoom,                   {Category::cForestTemple, Category::cSkulltula,});
ItemLocation ForestTemple_GS_LevelIslandCourtyard         = ItemLocation::GSToken(0x03, 0x04, "Forest Temple GS Level Island Courtyard",          &Hints::ForestTemple_GS_LevelIslandCourtyard,        {Category::cForestTemple, Category::cSkulltula,});
ItemLocation ForestTemple_GS_Lobby                        = ItemLocation::GSToken(0x03, 0x08, "Forest Temple GS Lobby",                           &Hints::ForestTemple_GS_Lobby,                       {Category::cForestTemple, Category::cSkulltula,});
ItemLocation ForestTemple_GS_Basement                     = ItemLocation::GSToken(0x03, 0x10, "Forest Temple GS Basement",                        &Hints::ForestTemple_GS_Basement,                    {Category::cForestTemple, Category::cSkulltula,});

ItemLocation ForestTemple_MQ_GS_FirstHallway              = ItemLocation::GSToken(0x03, 0x02, "Forest Temple MQ GS First Hallway",                &Hints::ForestTemple_MQ_GS_FirstHallway,             {Category::cForestTemple, Category::cSkulltula,});
ItemLocation ForestTemple_MQ_GS_BlockPushRoom             = ItemLocation::GSToken(0x03, 0x10, "Forest Temple MQ GS Block Push Room",              &Hints::ForestTemple_MQ_GS_BlockPushRoom,            {Category::cForestTemple, Category::cSkulltula,});
ItemLocation ForestTemple_MQ_GS_RaisedIslandCourtyard     = ItemLocation::GSToken(0x03, 0x01, "Forest Temple MQ GS Raised Island Courtyard",      &Hints::ForestTemple_MQ_GS_RaisedIslandCourtyard,    {Category::cForestTemple, Category::cSkulltula,});
ItemLocation ForestTemple_MQ_GS_LevelIslandCourtyard      = ItemLocation::GSToken(0x03, 0x04, "Forest Temple MQ GS Level Island Courtyard",       &Hints::ForestTemple_MQ_GS_LevelIslandCourtyard,     {Category::cForestTemple, Category::cSkulltula,});
ItemLocation ForestTemple_MQ_GS_Well                      = ItemLocation::GSToken(0x03, 0x08, "Forest Temple MQ GS Well",                         &Hints::ForestTemple_MQ_GS_Well,                     {Category::cForestTemple, Category::cSkulltula,});

ItemLocation FireTemple_GS_SongOfTimeRoom                 = ItemLocation::GSToken(0x04, 0x01, "Fire Temple GS Song of Time Room",                 &Hints::FireTemple_GS_SongOfTimeRoom,                {Category::cFireTemple, Category::cSkulltula,});
ItemLocation FireTemple_GS_BossKeyLoop                    = ItemLocation::GSToken(0x04, 0x02, "Fire Temple GS Boss Key Loop",                     &Hints::FireTemple_GS_BossKeyLoop,                   {Category::cFireTemple, Category::cSkulltula,});
ItemLocation FireTemple_GS_BoulderMaze                    = ItemLocation::GSToken(0x04, 0x04, "Fire Temple GS Boulder Maze",                      &Hints::FireTemple_GS_BoulderMaze,                   {Category::cFireTemple, Category::cSkulltula,});
ItemLocation FireTemple_GS_ScarecrowTop                   = ItemLocation::GSToken(0x04, 0x08, "Fire Temple GS Scarecrow Top",                     &Hints::FireTemple_GS_ScarecrowTop,                  {Category::cFireTemple, Category::cSkulltula,});
ItemLocation FireTemple_GS_ScarecrowClimb                 = ItemLocation::GSToken(0x04, 0x10, "Fire Temple GS Scarecrow Climb",                   &Hints::FireTemple_GS_ScarecrowClimb,                {Category::cFireTemple, Category::cSkulltula,});

ItemLocation FireTemple_MQ_GS_AboveFireWallMaze           = ItemLocation::GSToken(0x04, 0x02, "Fire Temple MQ GS Above Fire Wall Maze",           &Hints::FireTemple_MQ_GS_AboveFireWallMaze,          {Category::cFireTemple, Category::cSkulltula,});
ItemLocation FireTemple_MQ_GS_FireWallMazeCenter          = ItemLocation::GSToken(0x04, 0x08, "Fire Temple MQ GS Fire Wall Maze Center",          &Hints::FireTemple_MQ_GS_FireWallMazeCenter,         {Category::cFireTemple, Category::cSkulltula,});
ItemLocation FireTemple_MQ_GS_BigLavaRoomOpenDoor         = ItemLocation::GSToken(0x04, 0x01, "Fire Temple MQ GS Big Lava Room Open Door",        &Hints::FireTemple_MQ_GS_BigLavaRoomOpenDoor,        {Category::cFireTemple, Category::cSkulltula,});
ItemLocation FireTemple_MQ_GS_FireWallMazeSideRoom        = ItemLocation::GSToken(0x04, 0x10, "Fire Temple MQ GS Fire Wall Maze Side Room",       &Hints::FireTemple_MQ_GS_FireWallMazeSideRoom,       {Category::cFireTemple, Category::cSkulltula,});
ItemLocation FireTemple_MQ_GS_SkullOnFire                 = ItemLocation::GSToken(0x04, 0x04, "Fire Temple MQ GS Skull on Fire",                  &Hints::FireTemple_MQ_GS_SkullOnFire,                {Category::cFireTemple, Category::cSkulltula,});

ItemLocation WaterTemple_GS_BehindGate                    = ItemLocation::GSToken(0x05, 0x01, "Water Temple GS Behind Gate",                      &Hints::WaterTemple_GS_BehindGate,                   {Category::cWaterTemple, Category::cSkulltula,});
ItemLocation WaterTemple_GS_FallingPlatformRoom           = ItemLocation::GSToken(0x05, 0x02, "Water Temple GS Falling Platform Room",            &Hints::WaterTemple_GS_FallingPlatformRoom,          {Category::cWaterTemple, Category::cSkulltula,});
ItemLocation WaterTemple_GS_CentralPillar                 = ItemLocation::GSToken(0x05, 0x04, "Water Temple GS Central Pillar",                   &Hints::WaterTemple_GS_CentralPillar,                {Category::cWaterTemple, Category::cSkulltula,});
ItemLocation WaterTemple_GS_NearBossKeyChest              = ItemLocation::GSToken(0x05, 0x08, "Water Temple GS Near Boss Key Chest",              &Hints::WaterTemple_GS_NearBossKeyChest,             {Category::cWaterTemple, Category::cSkulltula,});
ItemLocation WaterTemple_GS_River                         = ItemLocation::GSToken(0x05, 0x10, "Water Temple GS River",                            &Hints::WaterTemple_GS_River,                        {Category::cWaterTemple, Category::cSkulltula,});

ItemLocation WaterTemple_MQ_GS_BeforeUpperWaterSwitch     = ItemLocation::GSToken(0x05, 0x04, "Water Temple MQ GS Before Upper Water Switch",     &Hints::WaterTemple_MQ_GS_BeforeUpperWaterSwitch,    {Category::cWaterTemple, Category::cSkulltula,});
ItemLocation WaterTemple_MQ_GS_FreestandingKeyArea        = ItemLocation::GSToken(0x05, 0x08, "Water Temple MQ GS Freestanding Key Area",         &Hints::WaterTemple_MQ_GS_FreestandingKeyArea,       {Category::cWaterTemple, Category::cSkulltula,});
ItemLocation WaterTemple_MQ_GS_LizalfosHallway            = ItemLocation::GSToken(0x05, 0x01, "Water Temple MQ GS Lizalfos Hallway",              &Hints::WaterTemple_MQ_GS_LizalfosHallway,           {Category::cWaterTemple, Category::cSkulltula,});
ItemLocation WaterTemple_MQ_GS_River                      = ItemLocation::GSToken(0x05, 0x02, "Water Temple MQ GS River",                         &Hints::WaterTemple_MQ_GS_River,                     {Category::cWaterTemple, Category::cSkulltula,});
ItemLocation WaterTemple_MQ_GS_TripleWallTorch            = ItemLocation::GSToken(0x05, 0x10, "Water Temple MQ GS Triple Wall Torch",             &Hints::WaterTemple_MQ_GS_TripleWallTorch,           {Category::cWaterTemple, Category::cSkulltula,});

ItemLocation SpiritTemple_GS_HallAfterSunBlockRoom        = ItemLocation::GSToken(0x06, 0x01, "Spirit Temple GS Hall After Sun Block Room",       &Hints::SpiritTemple_GS_HallAfterSunBlockRoom,       {Category::cSpiritTemple, Category::cSkulltula});
ItemLocation SpiritTemple_GS_BoulderRoom                  = ItemLocation::GSToken(0x06, 0x02, "Spirit Temple GS Boulder Room",                    &Hints::SpiritTemple_GS_BoulderRoom,                 {Category::cSpiritTemple, Category::cSkulltula});
ItemLocation SpiritTemple_GS_Lobby                        = ItemLocation::GSToken(0x06, 0x04, "Spirit Temple GS Lobby",                           &Hints::SpiritTemple_GS_Lobby,                       {Category::cSpiritTemple, Category::cSkulltula});
ItemLocation SpiritTemple_GS_SunOnFloorRoom               = ItemLocation::GSToken(0x06, 0x08, "Spirit Temple GS Sun on Floor Room",               &Hints::SpiritTemple_GS_SunOnFloorRoom,              {Category::cSpiritTemple, Category::cSkulltula});
ItemLocation SpiritTemple_GS_MetalFence                   = ItemLocation::GSToken(0x06, 0x10, "Spirit Temple GS Metal Fence",                     &Hints::SpiritTemple_GS_MetalFence,                  {Category::cSpiritTemple, Category::cSkulltula});

ItemLocation SpiritTemple_MQ_GS_SymphonyRoom              = ItemLocation::GSToken(0x06, 0x08, "Spirit Temple MQ GS Symphony Room",                &Hints::SpiritTemple_MQ_GS_SymphonyRoom,             {Category::cSpiritTemple, Category::cSkulltula});
ItemLocation SpiritTemple_MQ_GS_LeeverRoom                = ItemLocation::GSToken(0x06, 0x02, "Spirit Temple MQ GS Leever Room",                  &Hints::SpiritTemple_MQ_GS_LeeverRoom,               {Category::cSpiritTemple, Category::cSkulltula});
ItemLocation SpiritTemple_MQ_GS_NineThronesRoomWest       = ItemLocation::GSToken(0x06, 0x04, "Spirit Temple MQ GS Nine Thrones Room West",       &Hints::SpiritTemple_MQ_GS_NineThronesRoomWest,      {Category::cSpiritTemple, Category::cSkulltula});
ItemLocation SpiritTemple_MQ_GS_NineThronesRoomNorth      = ItemLocation::GSToken(0x06, 0x10, "Spirit Temple MQ GS Nine Thrones Room North",      &Hints::SpiritTemple_MQ_GS_NineThronesRoomNorth,     {Category::cSpiritTemple, Category::cSkulltula});
ItemLocation SpiritTemple_MQ_GS_SunBlockRoom              = ItemLocation::GSToken(0x06, 0x01, "Spirit Temple MQ GS Sun Block Room",               &Hints::SpiritTemple_MQ_GS_SunBlockRoom,             {Category::cSpiritTemple, Category::cSkulltula});

ItemLocation ShadowTemple_GS_SingleGiantPot               = ItemLocation::GSToken(0x07, 0x01, "Shadow Temple GS Single Giant Pot",                &Hints::ShadowTemple_GS_SingleGiantPot,              {Category::cShadowTemple, Category::cSkulltula,});
ItemLocation ShadowTemple_GS_FallingSpikesRoom            = ItemLocation::GSToken(0x07, 0x02, "Shadow Temple GS Falling Spikes Room",             &Hints::ShadowTemple_GS_FallingSpikesRoom,           {Category::cShadowTemple, Category::cSkulltula,});
ItemLocation ShadowTemple_GS_TripleGiantPot               = ItemLocation::GSToken(0x07, 0x04, "Shadow Temple GS Triple Giant Pot",                &Hints::ShadowTemple_GS_TripleGiantPot,              {Category::cShadowTemple, Category::cSkulltula,});
ItemLocation ShadowTemple_GS_LikeLikeRoom                 = ItemLocation::GSToken(0x07, 0x08, "Shadow Temple GS Like Like Room",                  &Hints::ShadowTemple_GS_LikeLikeRoom,                {Category::cShadowTemple, Category::cSkulltula,});
ItemLocation ShadowTemple_GS_NearShip                     = ItemLocation::GSToken(0x07, 0x10, "Shadow Temple GS Near Ship",                       &Hints::ShadowTemple_GS_NearShip,                    {Category::cShadowTemple, Category::cSkulltula,});

ItemLocation ShadowTemple_MQ_GS_FallingSpikesRoom         = ItemLocation::GSToken(0x07, 0x02, "Shadow Temple MQ GS Falling Spikes Room",          &Hints::ShadowTemple_MQ_GS_FallingSpikesRoom,        {Category::cShadowTemple, Category::cSkulltula,});
ItemLocation ShadowTemple_MQ_GS_WindHintRoom              = ItemLocation::GSToken(0x07, 0x01, "Shadow Temple MQ GS Wind Hint Room",               &Hints::ShadowTemple_MQ_GS_WindHintRoom,             {Category::cShadowTemple, Category::cSkulltula,});
ItemLocation ShadowTemple_MQ_GS_AfterWind                 = ItemLocation::GSToken(0x07, 0x08, "Shadow Temple MQ GS After Wind",                   &Hints::ShadowTemple_MQ_GS_AfterWind,                {Category::cShadowTemple, Category::cSkulltula,});
ItemLocation ShadowTemple_MQ_GS_AfterShip                 = ItemLocation::GSToken(0x07, 0x10, "Shadow Temple MQ GS After Ship",                   &Hints::ShadowTemple_MQ_GS_AfterShip,                {Category::cShadowTemple, Category::cSkulltula,});
ItemLocation ShadowTemple_MQ_GS_NearBoss                  = ItemLocation::GSToken(0x07, 0x04, "Shadow Temple MQ GS Near Boss",                    &Hints::ShadowTemple_MQ_GS_NearBoss,                 {Category::cShadowTemple, Category::cSkulltula,});

ItemLocation BottomOfTheWell_GS_LikeLikeCage              = ItemLocation::GSToken(0x08, 0x01, "Bottom of the Well GS Like Like Cage",             &Hints::BottomOfTheWell_GS_LikeLikeCage,             {Category::cBottomOfTheWell, Category::cSkulltula,});
ItemLocation BottomOfTheWell_GS_EastInnerRoom             = ItemLocation::GSToken(0x08, 0x02, "Bottom of the Well GS East Inner Room",            &Hints::BottomOfTheWell_GS_EastInnerRoom,            {Category::cBottomOfTheWell, Category::cSkulltula,});
ItemLocation BottomOfTheWell_GS_WestInnerRoom             = ItemLocation::GSToken(0x08, 0x04, "Bottom of the Well GS West Inner Room",            &Hints::BottomOfTheWell_GS_WestInnerRoom,            {Category::cBottomOfTheWell, Category::cSkulltula,});

ItemLocation BottomOfTheWell_MQ_GS_Basement               = ItemLocation::GSToken(0x08, 0x01, "Bottom of the Well MQ GS Basement",                &Hints::BottomOfTheWell_MQ_GS_Basement,              {Category::cBottomOfTheWell, Category::cSkulltula,});
ItemLocation BottomOfTheWell_MQ_GS_CoffinRoom             = ItemLocation::GSToken(0x08, 0x04, "Bottom of the Well MQ GS Coffin Room",             &Hints::BottomOfTheWell_MQ_GS_CoffinRoom,            {Category::cBottomOfTheWell, Category::cSkulltula,});
ItemLocation BottomOfTheWell_MQ_GS_WestInnerRoom          = ItemLocation::GSToken(0x08, 0x02, "Bottom of the Well MQ GS West Inner Room",         &Hints::BottomOfTheWell_MQ_GS_WestInnerRoom,         {Category::cBottomOfTheWell, Category::cSkulltula,});

ItemLocation IceCavern_GS_PushBlockRoom                   = ItemLocation::GSToken(0x09, 0x01, "Ice Cavern GS Push Block Room",                    &Hints::IceCavern_GS_PushBlockRoom,                  {Category::cIceCavern, Category::cSkulltula,});
ItemLocation IceCavern_GS_SpinningScytheRoom              = ItemLocation::GSToken(0x09, 0x02, "Ice Cavern GS Spinning Scythe Room",               &Hints::IceCavern_GS_SpinningScytheRoom,             {Category::cIceCavern, Category::cSkulltula,});
ItemLocation IceCavern_GS_HeartPieceRoom                  = ItemLocation::GSToken(0x09, 0x04, "Ice Cavern GS Heart Piece Room",                   &Hints::IceCavern_GS_HeartPieceRoom,                 {Category::cIceCavern, Category::cSkulltula,});

ItemLocation IceCavern_MQ_GS_Scarecrow                    = ItemLocation::GSToken(0x09, 0x01, "Ice Cavern MQ GS Scarecrow",                       &Hints::IceCavern_MQ_GS_Scarecrow,                   {Category::cIceCavern, Category::cSkulltula,});
ItemLocation IceCavern_MQ_GS_IceBlock                     = ItemLocation::GSToken(0x09, 0x04, "Ice Cavern MQ GS Ice Block",                       &Hints::IceCavern_MQ_GS_IceBlock,                    {Category::cIceCavern, Category::cSkulltula,});
ItemLocation IceCavern_MQ_GS_RedIce                       = ItemLocation::GSToken(0x09, 0x02, "Ice Cavern MQ GS Red Ice",                         &Hints::IceCavern_MQ_GS_RedIce,                      {Category::cIceCavern, Category::cSkulltula,});

//Overworld
ItemLocation KF_GS_BeanPatch                              = ItemLocation::GSToken(0x0C, 0x01, "KF GS Bean Patch",                                 &Hints::KF_GS_BeanPatch,                             {Category::cKokiriForest, Category::cSkulltula,});
ItemLocation KF_GS_KnowItAllHouse                         = ItemLocation::GSToken(0x0C, 0x02, "KF GS Know It All House",                          &Hints::KF_GS_KnowItAllHouse,                        {Category::cKokiriForest, Category::cSkulltula,});
ItemLocation KF_GS_HouseOfTwins                           = ItemLocation::GSToken(0x0C, 0x04, "KF GS House of Twins",                             &Hints::KF_GS_HouseOfTwins,                          {Category::cKokiriForest, Category::cSkulltula,});

ItemLocation LW_GS_BeanPatchNearBridge                    = ItemLocation::GSToken(0x0D, 0x01, "LW GS Bean Patch Near Bridge",                     &Hints::LW_GS_BeanPatchNearBridge,                   {Category::cLostWoods, Category::cSkulltula,});
ItemLocation LW_GS_BeanPatchNearTheater                   = ItemLocation::GSToken(0x0D, 0x02, "LW GS Bean Patch Near Theater",                    &Hints::LW_GS_BeanPatchNearTheater,                  {Category::cLostWoods, Category::cSkulltula,});
ItemLocation LW_GS_AboveTheater                           = ItemLocation::GSToken(0x0D, 0x04, "LW GS Above Theater",                              &Hints::LW_GS_AboveTheater,                          {Category::cLostWoods, Category::cSkulltula,});
ItemLocation SFM_GS                                       = ItemLocation::GSToken(0x0D, 0x08, "SFM GS",                                           &Hints::SFM_GS,                                      {Category::cSacredForestMeadow, Category::cSkulltula,});

ItemLocation HF_GS_CowGrotto                              = ItemLocation::GSToken(0x0A, 0x01, "HF GS Cow Grotto",                                 &Hints::HF_GS_CowGrotto,                             {Category::cHyruleField, Category::cSkulltula, Category::cGrotto});
ItemLocation HF_GS_NearKakGrotto                          = ItemLocation::GSToken(0x0A, 0x02, "HF GS Near Kak Grotto",                            &Hints::HF_GS_NearKakGrotto,                         {Category::cHyruleField, Category::cSkulltula, Category::cGrotto});

ItemLocation LH_GS_BeanPatch                              = ItemLocation::GSToken(0x12, 0x01, "LH GS Bean Patch",                                 &Hints::LH_GS_BeanPatch,                             {Category::cLakeHylia, Category::cSkulltula,});
ItemLocation LH_GS_SmallIsland                            = ItemLocation::GSToken(0x12, 0x02, "LH GS Small Island",                               &Hints::LH_GS_SmallIsland,                           {Category::cLakeHylia, Category::cSkulltula,});
ItemLocation LH_GS_LabWall                                = ItemLocation::GSToken(0x12, 0x04, "LH GS Lab Wall",                                   &Hints::LH_GS_LabWall,                               {Category::cLakeHylia, Category::cSkulltula,});
ItemLocation LH_GS_LabCrate                               = ItemLocation::GSToken(0x12, 0x08, "LH GS Lab Crate",                                  &Hints::LH_GS_LabCrate,                              {Category::cLakeHylia, Category::cSkulltula,});
ItemLocation LH_GS_Tree                                   = ItemLocation::GSToken(0x12, 0x10, "LH GS Tree",                                       &Hints::LH_GS_Tree,                                  {Category::cLakeHylia, Category::cSkulltula,});

ItemLocation GV_GS_BeanPatch                              = ItemLocation::GSToken(0x13, 0x01, "GV GS Bean Patch",                                 &Hints::GV_GS_BeanPatch,                             {Category::cGerudoValley, Category::cSkulltula,});
ItemLocation GV_GS_SmallBridge                            = ItemLocation::GSToken(0x13, 0x02, "GV GS Small Bridge",                               &Hints::GV_GS_SmallBridge,                           {Category::cGerudoValley, Category::cSkulltula,});
ItemLocation GV_GS_Pillar                                 = ItemLocation::GSToken(0x13, 0x04, "GV GS Pillar",                                     &Hints::GV_GS_Pillar,                                {Category::cGerudoValley, Category::cSkulltula,});
ItemLocation GV_GS_BehindTent                             = ItemLocation::GSToken(0x13, 0x08, "GV GS Behind Tent",                                &Hints::GV_GS_BehindTent,                            {Category::cGerudoValley, Category::cSkulltula,});

ItemLocation GF_GS_ArcheryRange                           = ItemLocation::GSToken(0x14, 0x01, "GF GS Archery Range",                              &Hints::GF_GS_ArcheryRange,                          {Category::cGerudoFortress, Category::cSkulltula,});
ItemLocation GF_GS_TopFloor                               = ItemLocation::GSToken(0x14, 0x02, "GF GS Top Floor",                                  &Hints::GF_GS_TopFloor,                              {Category::cGerudoFortress, Category::cSkulltula,});

ItemLocation HW_GS                                        = ItemLocation::GSToken(0x15, 0x02, "HW GS",                                            &Hints::HW_GS,                                       {Category::cHauntedWasteland, Category::cSkulltula,});
ItemLocation Colossus_GS_BeanPatch                        = ItemLocation::GSToken(0x15, 0x01, "Colossus GS Bean Patch",                           &Hints::Colossus_GS_BeanPatch,                       {Category::cDesertColossus, Category::cSkulltula,});
ItemLocation Colossus_GS_Hill                             = ItemLocation::GSToken(0x15, 0x04, "Colossus GS Hill",                                 &Hints::Colossus_GS_Hill,                            {Category::cDesertColossus, Category::cSkulltula,});
ItemLocation Colossus_GS_Tree                             = ItemLocation::GSToken(0x15, 0x08, "Colossus GS Tree",                                 &Hints::Colossus_GS_Tree,                            {Category::cDesertColossus, Category::cSkulltula,});

ItemLocation OGC_GS                                       = ItemLocation::GSToken(0x0E, 0x01, "OGC GS",                                           &Hints::OGC_GS,                                      {Category::cOutsideGanonsCastle, Category::cSkulltula,});
ItemLocation HC_GS_StormsGrotto                           = ItemLocation::GSToken(0x0E, 0x02, "HC GS Storms Grotto",                              &Hints::HC_GS_StormsGrotto,                          {Category::cHyruleCastle, Category::cSkulltula, Category::cGrotto});
ItemLocation HC_GS_Tree                                   = ItemLocation::GSToken(0x0E, 0x04, "HC GS Tree",                                       &Hints::HC_GS_Tree,                                  {Category::cHyruleCastle, Category::cSkulltula,});
ItemLocation MK_GS_GuardHouse                             = ItemLocation::GSToken(0x0E, 0x08, "Market GS Guard House",                            &Hints::MK_GS_GuardHouse,                            {Category::cInnerMarket, Category::cSkulltula,});

ItemLocation Kak_GS_HouseUnderConstruction                = ItemLocation::GSToken(0x10, 0x08, "Kak GS House Under Construction",                  &Hints::Kak_GS_HouseUnderConstruction,               {Category::cKakarikoVillage, Category::cSkulltula,});
ItemLocation Kak_GS_SkulltulaHouse                        = ItemLocation::GSToken(0x10, 0x10, "Kak GS Skulltula House",                           &Hints::Kak_GS_SkulltulaHouse,                       {Category::cKakarikoVillage, Category::cSkulltula,});
ItemLocation Kak_GS_GuardsHouse                           = ItemLocation::GSToken(0x10, 0x02, "Kak GS Guards House",                              &Hints::Kak_GS_GuardsHouse,                          {Category::cKakarikoVillage, Category::cSkulltula,});
ItemLocation Kak_GS_Tree                                  = ItemLocation::GSToken(0x10, 0x20, "Kak GS Tree",                                      &Hints::Kak_GS_Tree,                                 {Category::cKakarikoVillage, Category::cSkulltula,});
ItemLocation Kak_GS_Watchtower                            = ItemLocation::GSToken(0x10, 0x04, "Kak GS Watchtower",                                &Hints::Kak_GS_Watchtower,                           {Category::cKakarikoVillage, Category::cSkulltula,});
ItemLocation Kak_GS_AboveImpasHouse                       = ItemLocation::GSToken(0x10, 0x40, "Kak GS Above Impas House",                         &Hints::Kak_GS_AboveImpasHouse,                      {Category::cKakarikoVillage, Category::cSkulltula,});

ItemLocation GY_GS_Wall                                   = ItemLocation::GSToken(0x10, 0x80, "Graveyard GS Wall",                                &Hints::GY_GS_Wall,                                  {Category::cGraveyard, Category::cSkulltula,});
ItemLocation GY_GS_BeanPatch                              = ItemLocation::GSToken(0x10, 0x01, "Graveyard GS Bean Patch",                          &Hints::GY_GS_BeanPatch,                             {Category::cGraveyard, Category::cSkulltula,});

ItemLocation DMC_GS_BeanPatch                             = ItemLocation::GSToken(0x0F, 0x01, "DMC GS Bean Patch",                                &Hints::DMC_GS_BeanPatch,                            {Category::cDeathMountainCrater, Category::cSkulltula,});
ItemLocation DMC_GS_Crate                                 = ItemLocation::GSToken(0x0F, 0x80, "DMC GS Crate",                                     &Hints::DMC_GS_Crate,                                {Category::cDeathMountainCrater, Category::cSkulltula,});

ItemLocation DMT_GS_BeanPatch                             = ItemLocation::GSToken(0x0F, 0x02, "DMT GS Bean Patch",                                &Hints::DMT_GS_BeanPatch,                            {Category::cDeathMountainTrail, Category::cSkulltula,});
ItemLocation DMT_GS_NearKak                               = ItemLocation::GSToken(0x0F, 0x04, "DMT GS Near Kak",                                  &Hints::DMT_GS_NearKak,                              {Category::cDeathMountainTrail, Category::cSkulltula,});
ItemLocation DMT_GS_AboveDodongosCavern                   = ItemLocation::GSToken(0x0F, 0x08, "DMT GS Above Dodongos Cavern",                     &Hints::DMT_GS_AboveDodongosCavern,                  {Category::cDeathMountainTrail, Category::cSkulltula,});
ItemLocation DMT_GS_FallingRocksPath                      = ItemLocation::GSToken(0x0F, 0x10, "DMT GS Falling Rocks Path",                        &Hints::DMT_GS_FallingRocksPath,                     {Category::cDeathMountainTrail, Category::cSkulltula,});

ItemLocation GC_GS_CenterPlatform                         = ItemLocation::GSToken(0x0F, 0x20, "GC GS Center Platform",                            &Hints::GC_GS_CenterPlatform,                        {Category::cGoronCity, Category::cSkulltula,});
ItemLocation GC_GS_BoulderMaze                            = ItemLocation::GSToken(0x0F, 0x40, "GC GS Boulder Maze",                               &Hints::GC_GS_BoulderMaze,                           {Category::cGoronCity, Category::cSkulltula,});

ItemLocation ZR_GS_Ladder                                 = ItemLocation::GSToken(0x11, 0x01, "ZR GS Ladder",                                     &Hints::ZR_GS_Ladder,                                {Category::cZorasRiver, Category::cSkulltula,});
ItemLocation ZR_GS_Tree                                   = ItemLocation::GSToken(0x11, 0x02, "ZR GS Tree",                                       &Hints::ZR_GS_Tree,                                  {Category::cZorasRiver, Category::cSkulltula,});
ItemLocation ZR_GS_AboveBridge                            = ItemLocation::GSToken(0x11, 0x08, "ZR GS Above Bridge",                               &Hints::ZR_GS_AboveBridge,                           {Category::cZorasRiver, Category::cSkulltula,});
ItemLocation ZR_GS_NearRaisedGrottos                      = ItemLocation::GSToken(0x11, 0x10, "ZR GS Near Raised Grottos",                        &Hints::ZR_GS_NearRaisedGrottos,                     {Category::cZorasRiver, Category::cSkulltula,});

ItemLocation ZD_GS_FrozenWaterfall                        = ItemLocation::GSToken(0x11, 0x40, "ZD GS Frozen Waterfall",                           &Hints::ZD_GS_FrozenWaterfall,                       {Category::cZorasDomain, Category::cSkulltula,});
ItemLocation ZF_GS_AboveTheLog                            = ItemLocation::GSToken(0x11, 0x04, "ZF GS Above The Log",                              &Hints::ZF_GS_AboveTheLog,                           {Category::cZorasFountain, Category::cSkulltula,});
ItemLocation ZF_GS_HiddenCave                             = ItemLocation::GSToken(0x11, 0x20, "ZF GS Hidden Cave",                                &Hints::ZF_GS_HiddenCave,                            {Category::cZorasFountain, Category::cSkulltula,});
ItemLocation ZF_GS_Tree                                   = ItemLocation::GSToken(0x11, 0x80, "ZF GS Tree",                                       &Hints::ZF_GS_Tree,                                  {Category::cZorasFountain, Category::cSkulltula,});

ItemLocation LLR_GS_BackWall                              = ItemLocation::GSToken(0x0B, 0x01, "LLR GS Back Wall",                                 &Hints::LLR_GS_BackWall,                             {Category::cLonLonRanch, Category::cSkulltula,});
ItemLocation LLR_GS_RainShed                              = ItemLocation::GSToken(0x0B, 0x02, "LLR GS Rain Shed",                                 &Hints::LLR_GS_RainShed,                             {Category::cLonLonRanch, Category::cSkulltula,});
ItemLocation LLR_GS_HouseWindow                           = ItemLocation::GSToken(0x0B, 0x04, "LLR GS House Window",                              &Hints::LLR_GS_HouseWindow,                          {Category::cLonLonRanch, Category::cSkulltula,});
ItemLocation LLR_GS_Tree                                  = ItemLocation::GSToken(0x0B, 0x08, "LLR GS Tree",                                      &Hints::LLR_GS_Tree,                                 {Category::cLonLonRanch, Category::cSkulltula,});

/*-------------------------------
          --- BOSSES ---
  -------------------------------*/

ItemLocation LinksPocket                                  = ItemLocation::Reward (0xFF, 0xFF,                    "Link's Pocket",               &Hints::LinksPocket,                     {});
ItemLocation QueenGohma                                   = ItemLocation::Reward (0xFF, DUNGEON_DEKU_TREE,       "Queen Gohma",                 &Hints::QueenGohma,                      {});
ItemLocation KingDodongo                                  = ItemLocation::Reward (0xFF, DUNGEON_DODONGOS_CAVERN, "King Dodongo",                &Hints::KingDodongo,                     {});
ItemLocation Barinade                                     = ItemLocation::Reward (0xFF, DUNGEON_JABUJABUS_BELLY, "Barinade",                    &Hints::Barinade,                        {});
ItemLocation PhantomGanon                                 = ItemLocation::Reward (0xFF, DUNGEON_FOREST_TEMPLE,   "Phantom Ganon",               &Hints::PhantomGanon,                    {});
ItemLocation Volvagia                                     = ItemLocation::Reward (0xFF, DUNGEON_FIRE_TEMPLE,     "Volvagia",                    &Hints::Volvagia,                        {});
ItemLocation Morpha                                       = ItemLocation::Reward (0xFF, DUNGEON_WATER_TEMPLE,    "Morpha",                      &Hints::Morpha,                          {});
ItemLocation Twinrova                                     = ItemLocation::Reward (0xFF, DUNGEON_SPIRIT_TEMPLE,   "Twinrova",                    &Hints::Twinrova,                        {});
ItemLocation BongoBongo                                   = ItemLocation::Reward (0xFF, DUNGEON_SHADOW_TEMPLE,   "Bongo Bongo",                 &Hints::BongoBongo,                      {});
ItemLocation Ganon                                        = ItemLocation::Reward (0xFF, 0xF0,                    "Ganon",                       &Hints::NoHintText,                      {});

/*-------------------------------
      ---HEART CONTAINERS ---
  -------------------------------*/

ItemLocation DekuTree_QueenGohmaHeart                     = ItemLocation::Base   (0x11, 0x4F, "Deku Tree Queen Gohma Heart Container",          &Hints::DekuTree_QueenGohmaHeart,        {Category::cDekuTree, Category::cBossHeart, Category::cSongDungeonReward});
ItemLocation DodongosCavern_KingDodongoHeart              = ItemLocation::Base   (0x12, 0x4F, "Dodongos Cavern King Dodongo Heart Container",   &Hints::DodongosCavern_KingDodongoHeart, {Category::cDodongosCavern, Category::cBossHeart, Category::cSongDungeonReward});
ItemLocation JabuJabusBelly_BarinadeHeart                 = ItemLocation::Base   (0x13, 0x4F, "Jabu Jabus Belly Barinade Heart Container",      &Hints::JabuJabusBelly_BarinadeHeart,    {Category::cJabuJabusBelly, Category::cBossHeart, Category::cSongDungeonReward});
ItemLocation ForestTemple_PhantomGanonHeart               = ItemLocation::Base   (0x14, 0x4F, "Forest Temple Phantom Ganon Heart Container",    &Hints::ForestTemple_PhantomGanonHeart,  {Category::cForestTemple, Category::cBossHeart, Category::cSongDungeonReward});
ItemLocation FireTemple_VolvagiaHeart                     = ItemLocation::Base   (0x15, 0x4F, "Fire Temple Volvagia Heart Container",           &Hints::FireTemple_VolvagiaHeart,        {Category::cFireTemple, Category::cBossHeart, Category::cSongDungeonReward});
ItemLocation WaterTemple_MorphaHeart                      = ItemLocation::Base   (0x16, 0x4F, "Water Temple Morpha Heart Container",            &Hints::WaterTemple_MorphaHeart,         {Category::cWaterTemple, Category::cBossHeart, Category::cSongDungeonReward});
ItemLocation SpiritTemple_TwinrovaHeart                   = ItemLocation::Base   (0x17, 0x4F, "Spirit Temple Twinrova Heart Container",         &Hints::SpiritTemple_TwinrovaHeart,      {Category::cSpiritTemple, Category::cBossHeart, Category::cSongDungeonReward});
ItemLocation ShadowTemple_BongoBongoHeart                 = ItemLocation::Base   (0x18, 0x4F, "Shadow Temple Bongo Bongo Heart Container",      &Hints::ShadowTemple_BongoBongoHeart,    {Category::cShadowTemple, Category::cBossHeart, Category::cSongDungeonReward});

/*-------------------------------
        --- CUTSCENES ---
  -------------------------------*/

ItemLocation ToT_LightArrowCutscene                       = ItemLocation::Delayed(0xFF, 0x01, "ToT Light Arrow Cutscene",                       &Hints::ToT_LightArrowCutscene,          {Category::cTempleOfTime, Category::cMarket});
ItemLocation LW_GiftFromSaria                             = ItemLocation::Delayed(0xFF, 0x02, "LW Gift From Saria",                             &Hints::LW_GiftFromSaria,                {Category::cLostWoods, Category::cForest});
ItemLocation ZF_GreatFairyReward                          = ItemLocation::Delayed(0xFF, 0x10, "ZF Great Fairy Reward",                          &Hints::ZF_GreatFairyReward,             {Category::cZorasFountain, Category::cFairies});
ItemLocation HC_GreatFairyReward                          = ItemLocation::Delayed(0xFF, 0x11, "HC Great Fairy Reward",                          &Hints::HC_GreatFairyReward,             {Category::cHyruleCastle, Category::cMarket, Category::cFairies});
ItemLocation Colossus_GreatFairyReward                    = ItemLocation::Delayed(0xFF, 0x12, "Colossus Great Fairy Reward",                    &Hints::Colossus_GreatFairyReward,       {Category::cDesertColossus, Category::cFairies});
ItemLocation DMT_GreatFairyReward                         = ItemLocation::Delayed(0xFF, 0x13, "DMT Great Fairy Reward",                         &Hints::DMT_GreatFairyReward,            {Category::cDeathMountainTrail, Category::cDeathMountain, Category::cFairies});
ItemLocation DMC_GreatFairyReward                         = ItemLocation::Delayed(0xFF, 0x14, "DMC Great Fairy Reward",                         &Hints::DMC_GreatFairyReward,            {Category::cDeathMountainCrater, Category::cDeathMountain, Category::cFairies});
ItemLocation OGC_GreatFairyReward                         = ItemLocation::Delayed(0xFF, 0x15, "OGC Great Fairy Reward",                         &Hints::OGC_GreatFairyReward,            {Category::cOutsideGanonsCastle, Category::cMarket, Category::cFairies});

ItemLocation SheikInForest                                = ItemLocation::Delayed(0xFF, 0x20, "Sheik in Forest",                                &Hints::SheikInForest,                   {Category::cSacredForestMeadow, Category::cForest, Category::cSong,});
ItemLocation SheikInCrater                                = ItemLocation::Delayed(0xFF, 0x21, "Sheik in Crater",                                &Hints::SheikInCrater,                   {Category::cDeathMountainCrater, Category::cDeathMountain, Category::cSong,});
ItemLocation SheikInIceCavern                             = ItemLocation::Delayed(0xFF, 0x22, "Sheik in Ice Cavern",                            &Hints::SheikInIceCavern,                {Category::cIceCavern, Category::cSong, Category::cSongDungeonReward});
ItemLocation SheikAtColossus                              = ItemLocation::Delayed(0xFF, 0x23, "Sheik at Colossus",                              &Hints::SheikAtColossus,                 {Category::cDesertColossus, Category::cSong,});
ItemLocation SheikInKakariko                              = ItemLocation::Delayed(0xFF, 0x24, "Sheik in Kakariko",                              &Hints::SheikInKakariko,                 {Category::cKakarikoVillage, Category::cKakariko, Category::cSong,});
ItemLocation SheikAtTemple                                = ItemLocation::Delayed(0xFF, 0x25, "Sheik at Temple",                                &Hints::SheikAtTemple,                   {Category::cTempleOfTime, Category::cMarket, Category::cSong,});
ItemLocation SongFromImpa                                 = ItemLocation::Delayed(0xFF, 0x26, "Song from Impa",                                 &Hints::SongFromImpa,                    {Category::cHyruleCastle, Category::cMarket, Category::cSong, Category::cSongDungeonReward});
ItemLocation SongFromMalon                                = ItemLocation::Delayed(0xFF, 0x27, "Song from Malon",                                &Hints::SongFromMalon,                   {Category::cLonLonRanch, Category::cSong,});
ItemLocation SongFromSaria                                = ItemLocation::Delayed(0xFF, 0x28, "Song from Saria",                                &Hints::SongFromSaria,                   {Category::cSacredForestMeadow, Category::cForest, Category::cSong,});
ItemLocation SongFromComposersGrave                       = ItemLocation::Delayed(0xFF, 0x29, "Song from Composers Grave",                      &Hints::SongFromComposersGrave,          {Category::cGraveyard, Category::cKakariko, Category::cSong,});
ItemLocation SongFromOcarinaOfTime                        = ItemLocation::Delayed(0xFF, 0x2A, "Song from Ocarina of Time",                      &Hints::SongFromOcarinaOfTime,           {Category::cHyruleField, Category::cSong, Category::cNeedSpiritualStones,});
ItemLocation SongFromWindmill                             = ItemLocation::Delayed(0xFF, 0x2B, "Song from Windmill",                             &Hints::SongFromWindmill,                {Category::cKakarikoVillage, Category::cKakariko, Category::cSong,});

/*-------------------------------
           --- COWS ---
  -------------------------------*/

ItemLocation KF_LinksHouseCow                             = ItemLocation::Base   (0x34, 0x15, "KF Links House Cow",                             &Hints::KF_LinksHouseCow,                {Category::cForest, Category::cCow, Category::cMinigame});
ItemLocation HF_CowGrottoCow                              = ItemLocation::Base   (0x3E, 0x16, "HF Cow Grotto Cow",                              &Hints::HF_CowGrottoCow,                 {Category::cHyruleField, Category::cCow, Category::cGrotto});
ItemLocation LLR_StablesLeftCow                           = ItemLocation::Base   (0x36, 0x16, "LLR Stables Left Cow",                           &Hints::LLR_StablesLeftCow,              {Category::cLonLonRanch, Category::cCow});
ItemLocation LLR_StablesRightCow                          = ItemLocation::Base   (0x36, 0x15, "LLR Stables Right Cow",                          &Hints::LLR_StablesRightCow,             {Category::cLonLonRanch, Category::cCow});
ItemLocation LLR_TowerLeftCow                             = ItemLocation::Base   (0x4C, 0x16, "LLR Tower Left Cow",                             &Hints::LLR_TowerLeftCow,                {Category::cLonLonRanch, Category::cCow});
ItemLocation LLR_TowerRightCow                            = ItemLocation::Base   (0x4C, 0x15, "LLR Tower Right Cow",                            &Hints::LLR_TowerRightCow,               {Category::cLonLonRanch, Category::cCow});
ItemLocation Kak_ImpasHouseCow                            = ItemLocation::Base   (0x37, 0x15, "Kak Impas House Cow",                            &Hints::Kak_ImpasHouseCow,               {Category::cKakarikoVillage, Category::cKakariko, Category::cCow});
ItemLocation DMT_CowGrottoCow                             = ItemLocation::Base   (0x3E, 0x15, "DMT Cow Grotto Cow",                             &Hints::DMT_CowGrottoCow,                {Category::cDeathMountainTrail, Category::cDeathMountain, Category::cCow, Category::cGrotto});
ItemLocation GV_Cow                                       = ItemLocation::Base   (0x5A, 0x15, "GV Cow",                                         &Hints::GV_Cow,                          {Category::cGerudoValley, Category::cGerudo, Category::cCow});
ItemLocation JabuJabusBelly_MQ_Cow                        = ItemLocation::Base   (0x02, 0x15, "Jabu Jabus Belly MQ Cow",                        &Hints::JabuJabusBelly_MQ_Cow,           {Category::cJabuJabusBelly, Category::cCow});

/*-------------------------------
          --- SHOPS ---
  8     6               2     4

  7     5               1     3
  -------------------------------*/

ItemLocation KF_ShopItem1                                 = ItemLocation::Base(0x2D, 0x30, "KF Shop Item 1",                                   &Hints::KF_ShopItem1,        {Category::cKokiriForest, Category::cForest, Category::cShop});
ItemLocation KF_ShopItem2                                 = ItemLocation::Base(0x2D, 0x31, "KF Shop Item 2",                                   &Hints::KF_ShopItem2,        {Category::cKokiriForest, Category::cForest, Category::cShop});
ItemLocation KF_ShopItem3                                 = ItemLocation::Base(0x2D, 0x32, "KF Shop Item 3",                                   &Hints::KF_ShopItem3,        {Category::cKokiriForest, Category::cForest, Category::cShop});
ItemLocation KF_ShopItem4                                 = ItemLocation::Base(0x2D, 0x33, "KF Shop Item 4",                                   &Hints::KF_ShopItem4,        {Category::cKokiriForest, Category::cForest, Category::cShop});
ItemLocation KF_ShopItem5                                 = ItemLocation::Base(0x2D, 0x34, "KF Shop Item 5",                                   &Hints::KF_ShopItem5,        {Category::cKokiriForest, Category::cForest, Category::cShop});
ItemLocation KF_ShopItem6                                 = ItemLocation::Base(0x2D, 0x35, "KF Shop Item 6",                                   &Hints::KF_ShopItem6,        {Category::cKokiriForest, Category::cForest, Category::cShop});
ItemLocation KF_ShopItem7                                 = ItemLocation::Base(0x2D, 0x36, "KF Shop Item 7",                                   &Hints::KF_ShopItem7,        {Category::cKokiriForest, Category::cForest, Category::cShop});
ItemLocation KF_ShopItem8                                 = ItemLocation::Base(0x2D, 0x37, "KF Shop Item 8",                                   &Hints::KF_ShopItem8,        {Category::cKokiriForest, Category::cForest, Category::cShop});
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

ItemLocation Kak_PotionShopItem1                          = ItemLocation::Base(0x30, 0x30, "Kak Potion Shop Item 1",                           &Hints::Kak_PotionShopItem1, {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_PotionShopItem2                          = ItemLocation::Base(0x30, 0x31, "Kak Potion Shop Item 2",                           &Hints::Kak_PotionShopItem2, {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_PotionShopItem3                          = ItemLocation::Base(0x30, 0x32, "Kak Potion Shop Item 3",                           &Hints::Kak_PotionShopItem3, {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_PotionShopItem4                          = ItemLocation::Base(0x30, 0x33, "Kak Potion Shop Item 4",                           &Hints::Kak_PotionShopItem4, {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_PotionShopItem5                          = ItemLocation::Base(0x30, 0x34, "Kak Potion Shop Item 5",                           &Hints::Kak_PotionShopItem5, {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_PotionShopItem6                          = ItemLocation::Base(0x30, 0x35, "Kak Potion Shop Item 6",                           &Hints::Kak_PotionShopItem6, {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_PotionShopItem7                          = ItemLocation::Base(0x30, 0x36, "Kak Potion Shop Item 7",                           &Hints::Kak_PotionShopItem7, {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_PotionShopItem8                          = ItemLocation::Base(0x30, 0x37, "Kak Potion Shop Item 8",                           &Hints::Kak_PotionShopItem8, {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
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

ItemLocation MK_BombchuShopItem1                          = ItemLocation::Base(0x32, 0x30, "MK Bombchu Shop Item 1",                           &Hints::MK_BombchuShopItem1, {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BombchuShopItem2                          = ItemLocation::Base(0x32, 0x31, "MK Bombchu Shop Item 2",                           &Hints::MK_BombchuShopItem2, {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BombchuShopItem3                          = ItemLocation::Base(0x32, 0x32, "MK Bombchu Shop Item 3",                           &Hints::MK_BombchuShopItem3, {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BombchuShopItem4                          = ItemLocation::Base(0x32, 0x33, "MK Bombchu Shop Item 4",                           &Hints::MK_BombchuShopItem4, {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BombchuShopItem5                          = ItemLocation::Base(0x32, 0x34, "MK Bombchu Shop Item 5",                           &Hints::MK_BombchuShopItem5, {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BombchuShopItem6                          = ItemLocation::Base(0x32, 0x35, "MK Bombchu Shop Item 6",                           &Hints::MK_BombchuShopItem6, {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BombchuShopItem7                          = ItemLocation::Base(0x32, 0x36, "MK Bombchu Shop Item 7",                           &Hints::MK_BombchuShopItem7, {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BombchuShopItem8                          = ItemLocation::Base(0x32, 0x37, "MK Bombchu Shop Item 8",                           &Hints::MK_BombchuShopItem8, {Category::cInnerMarket, Category::cMarket, Category::cShop});
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

ItemLocation MK_PotionShopItem1                           = ItemLocation::Base(0x31, 0x30, "MK Potion Shop Item 1",                            &Hints::MK_PotionShopItem1,  {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_PotionShopItem2                           = ItemLocation::Base(0x31, 0x31, "MK Potion Shop Item 2",                            &Hints::MK_PotionShopItem2,  {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_PotionShopItem3                           = ItemLocation::Base(0x31, 0x32, "MK Potion Shop Item 3",                            &Hints::MK_PotionShopItem3,  {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_PotionShopItem4                           = ItemLocation::Base(0x31, 0x33, "MK Potion Shop Item 4",                            &Hints::MK_PotionShopItem4,  {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_PotionShopItem5                           = ItemLocation::Base(0x31, 0x34, "MK Potion Shop Item 5",                            &Hints::MK_PotionShopItem5,  {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_PotionShopItem6                           = ItemLocation::Base(0x31, 0x35, "MK Potion Shop Item 6",                            &Hints::MK_PotionShopItem6,  {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_PotionShopItem7                           = ItemLocation::Base(0x31, 0x36, "MK Potion Shop Item 7",                            &Hints::MK_PotionShopItem7,  {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_PotionShopItem8                           = ItemLocation::Base(0x31, 0x37, "MK Potion Shop Item 8",                            &Hints::MK_PotionShopItem8,  {Category::cInnerMarket, Category::cMarket, Category::cShop});
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

ItemLocation MK_BazaarItem1                               = ItemLocation::Base(0x2C, 0x30, "MK Bazaar Item 1",                                 &Hints::MK_BazaarItem1,      {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BazaarItem2                               = ItemLocation::Base(0x2C, 0x31, "MK Bazaar Item 2",                                 &Hints::MK_BazaarItem2,      {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BazaarItem3                               = ItemLocation::Base(0x2C, 0x32, "MK Bazaar Item 3",                                 &Hints::MK_BazaarItem3,      {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BazaarItem4                               = ItemLocation::Base(0x2C, 0x33, "MK Bazaar Item 4",                                 &Hints::MK_BazaarItem4,      {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BazaarItem5                               = ItemLocation::Base(0x2C, 0x34, "MK Bazaar Item 5",                                 &Hints::MK_BazaarItem5,      {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BazaarItem6                               = ItemLocation::Base(0x2C, 0x35, "MK Bazaar Item 6",                                 &Hints::MK_BazaarItem6,      {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BazaarItem7                               = ItemLocation::Base(0x2C, 0x36, "MK Bazaar Item 7",                                 &Hints::MK_BazaarItem7,      {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BazaarItem8                               = ItemLocation::Base(0x2C, 0x37, "MK Bazaar Item 8",                                 &Hints::MK_BazaarItem8,      {Category::cInnerMarket, Category::cMarket, Category::cShop});
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

ItemLocation Kak_BazaarItem1                              = ItemLocation::Base(0x2C, 0x38, "Kak Bazaar Item 1",                                &Hints::Kak_BazaarItem1,     {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_BazaarItem2                              = ItemLocation::Base(0x2C, 0x39, "Kak Bazaar Item 2",                                &Hints::Kak_BazaarItem2,     {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_BazaarItem3                              = ItemLocation::Base(0x2C, 0x3A, "Kak Bazaar Item 3",                                &Hints::Kak_BazaarItem3,     {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_BazaarItem4                              = ItemLocation::Base(0x2C, 0x3B, "Kak Bazaar Item 4",                                &Hints::Kak_BazaarItem4,     {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_BazaarItem5                              = ItemLocation::Base(0x2C, 0x3C, "Kak Bazaar Item 5",                                &Hints::Kak_BazaarItem5,     {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_BazaarItem6                              = ItemLocation::Base(0x2C, 0x3D, "Kak Bazaar Item 6",                                &Hints::Kak_BazaarItem6,     {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_BazaarItem7                              = ItemLocation::Base(0x2C, 0x3E, "Kak Bazaar Item 7",                                &Hints::Kak_BazaarItem7,     {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_BazaarItem8                              = ItemLocation::Base(0x2C, 0x3F, "Kak Bazaar Item 8",                                &Hints::Kak_BazaarItem8,     {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
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

ItemLocation ZD_ShopItem1                                 = ItemLocation::Base(0x2F, 0x30, "ZD Shop Item 1",                                   &Hints::ZD_ShopItem1,        {Category::cZorasDomain, Category::cShop});
ItemLocation ZD_ShopItem2                                 = ItemLocation::Base(0x2F, 0x31, "ZD Shop Item 2",                                   &Hints::ZD_ShopItem2,        {Category::cZorasDomain, Category::cShop});
ItemLocation ZD_ShopItem3                                 = ItemLocation::Base(0x2F, 0x32, "ZD Shop Item 3",                                   &Hints::ZD_ShopItem3,        {Category::cZorasDomain, Category::cShop});
ItemLocation ZD_ShopItem4                                 = ItemLocation::Base(0x2F, 0x33, "ZD Shop Item 4",                                   &Hints::ZD_ShopItem4,        {Category::cZorasDomain, Category::cShop});
ItemLocation ZD_ShopItem5                                 = ItemLocation::Base(0x2F, 0x34, "ZD Shop Item 5",                                   &Hints::ZD_ShopItem5,        {Category::cZorasDomain, Category::cShop});
ItemLocation ZD_ShopItem6                                 = ItemLocation::Base(0x2F, 0x35, "ZD Shop Item 6",                                   &Hints::ZD_ShopItem6,        {Category::cZorasDomain, Category::cShop});
ItemLocation ZD_ShopItem7                                 = ItemLocation::Base(0x2F, 0x36, "ZD Shop Item 7",                                   &Hints::ZD_ShopItem7,        {Category::cZorasDomain, Category::cShop});
ItemLocation ZD_ShopItem8                                 = ItemLocation::Base(0x2F, 0x37, "ZD Shop Item 8",                                   &Hints::ZD_ShopItem8,        {Category::cZorasDomain, Category::cShop});
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

ItemLocation GC_ShopItem1                                 = ItemLocation::Base(0x2E, 0x30, "GC Shop Item 1",                                   &Hints::GC_ShopItem1,        {Category::cGoronCity, Category::cShop});
ItemLocation GC_ShopItem2                                 = ItemLocation::Base(0x2E, 0x31, "GC Shop Item 2",                                   &Hints::GC_ShopItem2,        {Category::cGoronCity, Category::cShop});
ItemLocation GC_ShopItem3                                 = ItemLocation::Base(0x2E, 0x32, "GC Shop Item 3",                                   &Hints::GC_ShopItem3,        {Category::cGoronCity, Category::cShop});
ItemLocation GC_ShopItem4                                 = ItemLocation::Base(0x2E, 0x33, "GC Shop Item 4",                                   &Hints::GC_ShopItem4,        {Category::cGoronCity, Category::cShop});
ItemLocation GC_ShopItem5                                 = ItemLocation::Base(0x2E, 0x34, "GC Shop Item 5",                                   &Hints::GC_ShopItem5,        {Category::cGoronCity, Category::cShop});
ItemLocation GC_ShopItem6                                 = ItemLocation::Base(0x2E, 0x35, "GC Shop Item 6",                                   &Hints::GC_ShopItem6,        {Category::cGoronCity, Category::cShop});
ItemLocation GC_ShopItem7                                 = ItemLocation::Base(0x2E, 0x36, "GC Shop Item 7",                                   &Hints::GC_ShopItem7,        {Category::cGoronCity, Category::cShop});
ItemLocation GC_ShopItem8                                 = ItemLocation::Base(0x2E, 0x37, "GC Shop Item 8",                                   &Hints::GC_ShopItem8,        {Category::cGoronCity, Category::cShop});
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
  &SFM_GS,

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

  &OGC_GS,
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
