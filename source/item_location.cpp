#include "item_location.hpp"
#include "spoiler_log.hpp"
#include "settings.hpp"

//Location definitions
//Kokiri Forest
ItemLocation KF_KokiriSwordChest              = ItemLocation::Chest      (0x55, 0x00, "KF Kokiri Sword Chest",                {Category::cKokiriForest, Category::cForest,});
ItemLocation KF_MidoTopLeftChest              = ItemLocation::Chest      (0x28, 0x00, "KF Mido Top Left Chest",               {Category::cKokiriForest, Category::cForest,});
ItemLocation KF_MidoTopRightChest             = ItemLocation::Chest      (0x28, 0x01, "KF Mido Top Right Chest",              {Category::cKokiriForest, Category::cForest,});
ItemLocation KF_MidoBottomLeftChest           = ItemLocation::Chest      (0x28, 0x02, "KF Mido Bottom Left Chest",            {Category::cKokiriForest, Category::cForest,});
ItemLocation KF_MidoBottomRightChest          = ItemLocation::Chest      (0x28, 0x03, "KF Mido Bottom Right Chest",           {Category::cKokiriForest, Category::cForest,});
ItemLocation KF_StormsGrottoChest             = ItemLocation::Chest      (0x3E, 0x0C, "KF Storms Grotto Chest",               {Category::cKokiriForest, Category::cForest, Category::cGrotto});

//Lost Woods
ItemLocation LW_NearShortcutsGrottoChest      = ItemLocation::Chest      (0x3E, 0x14, "LW Near Shortcuts Grotto Chest",       {Category::cLostWoods, Category::cForest, Category::cGrotto});
ItemLocation LW_SkullKid                      = ItemLocation::Base       (0x5B, 0x3E, "LW Skull Kid",                         {Category::cLostWoods, Category::cForest,});
ItemLocation LW_OcarinaMemoryGame             = ItemLocation::Base       (0x5B, 0x76, "LW Ocarina Memory Game",               {Category::cLostWoods, Category::cForest, Category::cMinigame});
ItemLocation LW_TargetInWoods                 = ItemLocation::Base       (0x5B, 0x60, "LW Target in Woods",                   {Category::cLostWoods, Category::cForest,});
ItemLocation LW_DekuScrubNearDekuTheaterRight = ItemLocation::Base       (0x5B, 0x30, "LW Deku Scrub Near Deku Theater Right",{Category::cLostWoods, Category::cForest, Category::cDekuScrub});
ItemLocation LW_DekuScrubNearDekuTheaterLeft  = ItemLocation::Base       (0x5B, 0x31, "LW Deku Scrub Near Deku Theater Left", {Category::cLostWoods, Category::cForest, Category::cDekuScrub});
ItemLocation LW_DekuScrubNearBridge           = ItemLocation::Base       (0x5B, 0x77, "LW Deku Scrub Near Bridge",            {Category::cLostWoods, Category::cForest, Category::cDekuScrub, Category::cDekuScrubUpgrades});
ItemLocation LW_DekuScrubGrottoRear           = ItemLocation::GrottoScrub(0xF5, 0x33, "LW Deku Scrub Grotto Rear",            {Category::cLostWoods, Category::cForest, Category::cDekuScrub, Category::cGrotto});
ItemLocation LW_DekuScrubGrottoFront          = ItemLocation::GrottoScrub(0xF5, 0x79, "LW Deku Scrub Grotto Front",           {Category::cLostWoods, Category::cForest, Category::cDekuScrub, Category::cDekuScrubUpgrades, Category::cGrotto});
ItemLocation DekuTheater_SkullMask            = ItemLocation::Base       (0x3E, 0x77, "Deku Theater Skull Mask",              {Category::cLostWoods, Category::cForest, Category::cGrotto});
ItemLocation DekuTheater_MaskOfTruth          = ItemLocation::Base       (0x3E, 0x7A, "Deku Theater Mask of Truth",           {Category::cLostWoods, Category::cForest, Category::cNeedSpiritualStones, Category::cGrotto});

//Sacred Forest Meadow
ItemLocation SFM_WolfosGrottoChest            = ItemLocation::Chest      (0x3E, 0x11, "SFM Wolfos Grotto Chest",              {Category::cSacredForestMeadow, Category::cForest, Category::cGrotto});
ItemLocation SFM_DekuScrubGrottoRear          = ItemLocation::GrottoScrub(0xEE, 0x39, "SFM Deku Scrub Grotto Rear",           {Category::cSacredForestMeadow, Category::cForest, Category::cDekuScrub, Category::cGrotto});
ItemLocation SFM_DekuScrubGrottoFront         = ItemLocation::GrottoScrub(0xEE, 0x3A, "SFM Deku Scrub Grotto Front",          {Category::cSacredForestMeadow, Category::cForest, Category::cDekuScrub, Category::cGrotto});

//Hyrule Field
ItemLocation HF_SoutheastGrottoChest          = ItemLocation::Chest      (0x3E, 0x02, "HF Southeast Grotto Chest",            {Category::cHyruleField, Category::cGrotto,});
ItemLocation HF_OpenGrottoChest               = ItemLocation::Chest      (0x3E, 0x03, "HF Open Grotto Chest",                 {Category::cHyruleField, Category::cGrotto,});
ItemLocation HF_NearMarketGrottoChest         = ItemLocation::Chest      (0x3E, 0x00, "HF Near Market Grotto Chest",          {Category::cHyruleField, Category::cGrotto,});
ItemLocation HF_OcarinaOfTimeItem             = ItemLocation::Base       (0x51, 0x0C, "HF Ocarina of Time Item",              {Category::cHyruleField, Category::cNeedSpiritualStones,});
ItemLocation HF_TektiteGrottoFreestandingPoH  = ItemLocation::Collectable(0x3E, 0x01, "HF Tektite Grotto Freestanding PoH",   {Category::cHyruleField, Category::cGrotto,});
ItemLocation HF_DekuScrubGrotto               = ItemLocation::GrottoScrub(0xE6, 0x3E, "HF Deku Scrub Grotto",                 {Category::cHyruleField, Category::cDekuScrub, Category::cDekuScrubUpgrades, Category::cGrotto});

//Lake Hylia
ItemLocation LH_ChildFishing                  = ItemLocation::Base       (0x49, 0x3E, "LH Child Fishing",                     {Category::cLakeHylia, Category::cMinigame,});
ItemLocation LH_AdultFishing                  = ItemLocation::Base       (0x49, 0x38, "LH Adult Fishing",                     {Category::cLakeHylia, Category::cMinigame,});
ItemLocation LH_LabDive                       = ItemLocation::Base       (0x38, 0x3E, "LH Lab Dive",                          {Category::cLakeHylia,});
ItemLocation LH_UnderwaterItem                = ItemLocation::Base       (0x57, 0x15, "LH Underwater Item",                   {Category::cLakeHylia,});
ItemLocation LH_Sun                           = ItemLocation::Base       (0x57, 0x58, "LH Sun",                               {Category::cLakeHylia,});
ItemLocation LH_FreestandingPoH               = ItemLocation::Collectable(0x57, 0x1E, "LH Freestanding PoH",                  {Category::cLakeHylia,});
ItemLocation LH_DekuScrubGrottoLeft           = ItemLocation::GrottoScrub(0xEF, 0x30, "LH Deku Scrub Grotto Left",            {Category::cLakeHylia, Category::cDekuScrub, Category::cGrotto});
ItemLocation LH_DekuScrubGrottoRight          = ItemLocation::GrottoScrub(0xEF, 0x37, "LH Deku Scrub Grotto Right",           {Category::cLakeHylia, Category::cDekuScrub, Category::cGrotto});
ItemLocation LH_DekuScrubGrottoCenter         = ItemLocation::GrottoScrub(0xEF, 0x33, "LH Deku Scrub Grotto Center",          {Category::cLakeHylia, Category::cDekuScrub, Category::cGrotto});

//Gerudo Valley
ItemLocation GV_Chest                         = ItemLocation::Chest      (0x5A, 0x00, "GV Chest",                             {Category::cGerudoValley, Category::cGerudo,});
ItemLocation GV_WaterfallFreestandingPoH      = ItemLocation::Collectable(0x5A, 0x01, "GV Waterfall Freestanding PoH",        {Category::cGerudoValley, Category::cGerudo,});
ItemLocation GV_CrateFreestandingPoH          = ItemLocation::Collectable(0x5A, 0x02, "GV Crate Freestanding PoH",            {Category::cGerudoValley, Category::cGerudo,});
ItemLocation GV_DekuScrubGrottoRear           = ItemLocation::GrottoScrub(0xF0, 0x39, "GV Deku Scrub Grotto Rear",            {Category::cGerudoValley, Category::cGerudo, Category::cDekuScrub, Category::cGrotto});
ItemLocation GV_DekuScrubGrottoFront          = ItemLocation::GrottoScrub(0xF0, 0x3A, "GV Deku Scrub Grotto Front",           {Category::cGerudoValley, Category::cGerudo, Category::cDekuScrub, Category::cGrotto});

//Gerudo Fortress
ItemLocation GF_Chest                         = ItemLocation::Chest      (0x5D, 0x00, "GF Chest",                             {Category::cGerudoFortress, Category::cGerudo,});
ItemLocation GF_HBA1000Points                 = ItemLocation::Base       (0x5D, 0x3E, "GF HBA 1000 Points",                   {Category::cGerudoFortress, Category::cGerudo, Category::cMinigame});
ItemLocation GF_HBA1500Points                 = ItemLocation::Base       (0x5D, 0x30, "GF HBA 1500 Points",                   {Category::cGerudoFortress, Category::cGerudo, Category::cMinigame});
ItemLocation GF_GerudoToken                   = ItemLocation::Base       (0x0C, 0x3A, "GF Gerudo Token",                      {Category::cGerudoFortress, Category::cGerudo,});
ItemLocation GF_NorthF1Carpenter              = ItemLocation::Collectable(0x0C, 0x0C, "GF North F1 Carpenter",                {Category::cGerudoFortress, Category::cGerudo, Category::cVanillaGFSmallKey});
ItemLocation GF_NorthF2Carpenter              = ItemLocation::Collectable(0x0C, 0x0A, "GF North F2 Carpenter",                {Category::cGerudoFortress, Category::cGerudo, Category::cVanillaGFSmallKey});
ItemLocation GF_SouthF1Carpenter              = ItemLocation::Collectable(0x0C, 0x0E, "GF South F1 Carpenter",                {Category::cGerudoFortress, Category::cGerudo, Category::cVanillaGFSmallKey});
ItemLocation GF_SouthF2Carpenter              = ItemLocation::Collectable(0x0C, 0x0F, "GF South F2 Carpenter",                {Category::cGerudoFortress, Category::cGerudo, Category::cVanillaGFSmallKey});

//Haunted Wasteland
ItemLocation HW_Chest                         = ItemLocation::Chest      (0x5E, 0x00, "HW Chest",                             {Category::cHauntedWasteland,});

//Desert Colossus
ItemLocation Colossus_FreestandingPoH         = ItemLocation::Collectable(0x5C, 0x0D, "Colossus Freestanding PoH",            {Category::cDesertColossus,});
ItemLocation Colossus_DekuScrubGrottoRear     = ItemLocation::GrottoScrub(0xFD, 0x39, "Colossus Deku Scrub Grotto Rear",      {Category::cDesertColossus, Category::cDekuScrub, Category::cGrotto});
ItemLocation Colossus_DekuScrubGrottoFront    = ItemLocation::GrottoScrub(0xFD, 0x3A, "Colossus Deku Scrub Grotto Front",     {Category::cDesertColossus, Category::cDekuScrub, Category::cGrotto});

//Market
ItemLocation MK_TreasureChestGameReward       = ItemLocation::Chest      (0x10, 0x0A, "MK Treasure Chest Game Reward",        {Category::cInnerMarket, Category::cMarket, Category::cMinigame});
ItemLocation MK_BombchuBowlingFirstPrize      = ItemLocation::Base       (0x4B, 0x33, "MK Bombchu Bowling First Prize",       {Category::cInnerMarket, Category::cMarket, Category::cMinigame});
ItemLocation MK_BombchuBowlingSecondPrize     = ItemLocation::Base       (0x4B, 0x3E, "MK Bombchu Bowling Second Prize",      {Category::cInnerMarket, Category::cMarket, Category::cMinigame});
ItemLocation MK_BombchuBowlingBombchus        = ItemLocation::Base       (0x4B, 0xFF, "MK Bombchu Bowling Bombchus",          {Category::cInnerMarket, Category::cMarket, Category::cMinigame});
ItemLocation MK_LostDog                       = ItemLocation::Base       (0x35, 0x3E, "MK Lost Dog",                          {Category::cInnerMarket, Category::cMarket,});
ItemLocation MK_ShootingGalleryReward         = ItemLocation::Base       (0x42, 0x60, "MK Shooting Gallery",                  {Category::cInnerMarket, Category::cMarket, Category::cMinigame});
ItemLocation MK_10BigPoes                     = ItemLocation::Base       (0x4D, 0x0F, "MK 10 Big Poes",                       {Category::cInnerMarket, Category::cHyruleCastle,});

//Hyrule Castle
ItemLocation HC_MalonEgg                      = ItemLocation::Base       (0x5F, 0x47, "HC Malon Egg",                         {Category::cHyruleCastle, Category::cMarket,});
ItemLocation HC_ZeldasLetter                  = ItemLocation::Base       (0x4A, 0x0B, "HC Zeldas Letter",                     {Category::cHyruleCastle, Category::cMarket,});

//Kakariko
ItemLocation Kak_RedeadGrottoChest            = ItemLocation::Chest      (0x3E, 0x0A, "Kak Redead Grotto Chest",              {Category::cKakarikoVillage, Category::cKakariko, Category::cGrotto});
ItemLocation Kak_OpenGrottoChest              = ItemLocation::Chest      (0x3E, 0x08, "Kak Open Grotto Chest",                {Category::cKakarikoVillage, Category::cKakariko, Category::cGrotto});
ItemLocation Kak_10GoldSkulltulaReward        = ItemLocation::Base       (0x50, 0x45, "Kak 10 Gold Skulltula Reward",         {Category::cKakarikoVillage, Category::cKakariko, Category::cSkulltulaHouse});
ItemLocation Kak_20GoldSkulltulaReward        = ItemLocation::Base       (0x50, 0x39, "Kak 20 Gold Skulltula Reward",         {Category::cKakarikoVillage, Category::cKakariko, Category::cSkulltulaHouse});
ItemLocation Kak_30GoldSkulltulaReward        = ItemLocation::Base       (0x50, 0x46, "Kak 30 Gold Skulltula Reward",         {Category::cKakarikoVillage, Category::cKakariko, Category::cSkulltulaHouse});
ItemLocation Kak_40GoldSkulltulaReward        = ItemLocation::Base       (0x50, 0x03, "Kak 40 Gold Skulltula Reward",         {Category::cKakarikoVillage, Category::cKakariko, Category::cSkulltulaHouse});
ItemLocation Kak_50GoldSkulltulaReward        = ItemLocation::Base       (0x50, 0x3E, "Kak 50 Gold Skulltula Reward",         {Category::cKakarikoVillage, Category::cKakariko, Category::cSkulltulaHouse});
ItemLocation Kak_ManOnRoof                    = ItemLocation::Base       (0x52, 0x3E, "Kak Man on Roof",                      {Category::cKakarikoVillage, Category::cKakariko,});
ItemLocation Kak_ShootingGalleryReward        = ItemLocation::Base       (0x42, 0x30, "Kak Shooting Gallery Reward",          {Category::cKakarikoVillage, Category::cKakariko, Category::cMinigame});
ItemLocation Kak_AnjuAsAdult                  = ItemLocation::Base       (0x52, 0x1D, "Kak Anju as Adult",                    {Category::cKakarikoVillage, Category::cKakariko,});
ItemLocation Kak_AnjuAsChild                  = ItemLocation::Base       (0x52, 0x0F, "Kak Anju as Child",                    {Category::cKakarikoVillage, Category::cKakariko, Category::cMinigame});
ItemLocation Kak_ImpasHouseFreestandingPoH    = ItemLocation::Collectable(0x37, 0x01, "Kak Impas House Freestanding PoH",     {Category::cKakarikoVillage, Category::cKakariko,});
ItemLocation Kak_WindmillFreestandingPoH      = ItemLocation::Collectable(0x48, 0x01, "Kak Windmill Freestanding PoH",        {Category::cKakarikoVillage, Category::cKakariko,});

//Graveyard
ItemLocation GY_ShieldGraveChest              = ItemLocation::Chest      (0x40, 0x00, "GY Shield Grave Chest",                {Category::cGraveyard, Category::cKakariko,});
ItemLocation GY_HeartPieceGraveChest          = ItemLocation::Chest      (0x3F, 0x00, "GY Heart Piece Grave Chest",           {Category::cGraveyard, Category::cKakariko,});
ItemLocation GY_ComposersGraveChest           = ItemLocation::Chest      (0x41, 0x00, "GY Composers Grave Chest",             {Category::cGraveyard, Category::cKakariko,});
ItemLocation GY_HookshotChest                 = ItemLocation::Chest      (0x48, 0x00, "GY Hookshot Chest",                    {Category::cGraveyard, Category::cKakariko,});
ItemLocation GY_DampeRaceFreestandingPoH      = ItemLocation::Collectable(0x48, 0x07, "GY Dampe Race Freestanding PoH",       {Category::cGraveyard, Category::cKakariko, Category::cMinigame});
ItemLocation GY_FreestandingPoH               = ItemLocation::Collectable(0x53, 0x04, "GY Freestanding PoH",                  {Category::cGraveyard, Category::cKakariko,});
ItemLocation GY_DampeGravediggingTour         = ItemLocation::Collectable(0x53, 0x08, "GY Dampe Gravedigging Tour",           {Category::cGraveyard, Category::cKakariko,});

//Death Mountain
ItemLocation DMT_Chest                        = ItemLocation::Chest      (0x60, 0x01, "DMT Chest",                            {Category::cDeathMountainTrail, Category::cDeathMountain,});
ItemLocation DMT_StormsGrottoChest            = ItemLocation::Chest      (0x3E, 0x17, "DMT Storms Grotto Chest",              {Category::cDeathMountainTrail, Category::cDeathMountain, Category::cGrotto});
ItemLocation DMT_Biggoron                     = ItemLocation::Base       (0x60, 0x57, "DMT Biggoron",                         {Category::cDeathMountainTrail, Category::cDeathMountain,});
ItemLocation DMT_FreestandingPoH              = ItemLocation::Collectable(0x60, 0x1E, "DMT Freestanding PoH",                 {Category::cDeathMountainTrail, Category::cDeathMountain,});

//Goron City
ItemLocation GC_MazeLeftChest                 = ItemLocation::Chest      (0x62, 0x00, "GC Maze Left Chest",                   {Category::cGoronCity,});
ItemLocation GC_MazeRightChest                = ItemLocation::Chest      (0x62, 0x01, "GC Maze Right Chest",                  {Category::cGoronCity,});
ItemLocation GC_MazeCenterChest               = ItemLocation::Chest      (0x62, 0x02, "GC Maze Center Chest",                 {Category::cGoronCity,});
ItemLocation GC_RollingGoronAsChild           = ItemLocation::Base       (0x62, 0x34, "GC Rolling Goron as Child",            {Category::cGoronCity,});
ItemLocation GC_RollingGoronAsAdult           = ItemLocation::Base       (0x62, 0x2C, "GC Rolling Goron as Adult",            {Category::cGoronCity,});
ItemLocation GC_DaruniasJoy                   = ItemLocation::Base       (0x62, 0x54, "GC Darunias Joy",                      {Category::cGoronCity,});
ItemLocation GC_PotFreestandingPoH            = ItemLocation::Collectable(0x62, 0x1F, "GC Pot Freestanding PoH",              {Category::cGoronCity,});
ItemLocation GC_DekuScrubGrottoLeft           = ItemLocation::GrottoScrub(0xFB, 0x30, "GC Deku Scrub Grotto Left",            {Category::cGoronCity, Category::cDekuScrub, Category::cGrotto});
ItemLocation GC_DekuScrubGrottoRight          = ItemLocation::GrottoScrub(0xFB, 0x37, "GC Deku Scrub Grotto Right",           {Category::cGoronCity, Category::cDekuScrub, Category::cGrotto});
ItemLocation GC_DekuScrubGrottoCenter         = ItemLocation::GrottoScrub(0xFB, 0x33, "GC Deku Scrub Grotto Center",          {Category::cGoronCity, Category::cDekuScrub, Category::cGrotto});

//Death Mountain Crater
ItemLocation DMC_UpperGrottoChest             = ItemLocation::Chest      (0x3E, 0x1A, "DMC Upper Grotto Chest",               {Category::cDeathMountainCrater, Category::cDeathMountain, Category::cGrotto});
ItemLocation DMC_WallFreestandingPoH          = ItemLocation::Collectable(0x61, 0x02, "DMC Wall Freestanding PoH",            {Category::cDeathMountainCrater, Category::cDeathMountain,});
ItemLocation DMC_VolcanoFreestandingPoH       = ItemLocation::Collectable(0x61, 0x08, "DMC Volcano Freestanding PoH",         {Category::cDeathMountainCrater, Category::cDeathMountain,});
ItemLocation DMC_DekuScrub                    = ItemLocation::Base       (0x61, 0x37, "DMC Deku Scrub",                       {Category::cDeathMountainCrater, Category::cDeathMountain, Category::cDekuScrub});
ItemLocation DMC_DekuScrubGrottoLeft          = ItemLocation::GrottoScrub(0xF9, 0x30, "DMC Deku Scrub Grotto Left",           {Category::cDeathMountainCrater, Category::cDeathMountain, Category::cDekuScrub, Category::cGrotto});
ItemLocation DMC_DekuScrubGrottoRight         = ItemLocation::GrottoScrub(0xF9, 0x37, "DMC Deku Scrub Grotto Right",          {Category::cDeathMountainCrater, Category::cDeathMountain, Category::cDekuScrub, Category::cGrotto});
ItemLocation DMC_DekuScrubGrottoCenter        = ItemLocation::GrottoScrub(0xF9, 0x33, "DMC Deku Scrub Grotto Center",         {Category::cDeathMountainCrater, Category::cDeathMountain, Category::cDekuScrub, Category::cGrotto});

//Zoras River
ItemLocation ZR_OpenGrottoChest               = ItemLocation::Chest      (0x3E, 0x09, "ZR Open Grotto Chest",                 {Category::cZorasRiver, Category::cGrotto,});
ItemLocation ZR_MagicBeanSalesman             = ItemLocation::Base       (0x54, 0x16, "ZR Magic Bean Salesman",               {Category::cZorasRiver,});
ItemLocation ZR_FrogsOcarinaGame              = ItemLocation::Base       (0x54, 0x76, "ZR Frogs Ocarina Game",                {Category::cZorasRiver,});
ItemLocation ZR_FrogsInTheRain                = ItemLocation::Base       (0x54, 0x3E, "ZR Frogs in the Rain",                 {Category::cZorasRiver, Category::cMinigame,});
ItemLocation ZR_NearOpenGrottoFreestandingPoH = ItemLocation::Collectable(0x54, 0x04, "ZR Near Open Grotto Freestanding PoH", {Category::cZorasRiver,});
ItemLocation ZR_NearDomainFreestandingPoH     = ItemLocation::Collectable(0x54, 0x0B, "ZR Near Domain Freestanding PoH",      {Category::cZorasRiver,});
ItemLocation ZR_DekuScrubGrottoRear           = ItemLocation::GrottoScrub(0xEB, 0x39, "ZR Deku Scrub Grotto Rear",            {Category::cZorasRiver, Category::cDekuScrub, Category::cGrotto});
ItemLocation ZR_DekuScrubGrottoFront          = ItemLocation::GrottoScrub(0xEB, 0x3A, "ZR Deku Scrub Grotto Front",           {Category::cZorasRiver, Category::cDekuScrub, Category::cGrotto});

//Zoras Domain
ItemLocation ZD_Chest                         = ItemLocation::Chest      (0x58, 0x00, "ZD Chest",                             {Category::cZorasDomain,});
ItemLocation ZD_DivingMinigame                = ItemLocation::Base       (0x58, 0x37, "ZD Diving Minigame",                   {Category::cZorasDomain, Category::cMinigame,});
ItemLocation ZD_KingZoraThawed                = ItemLocation::Base       (0x58, 0x2D, "ZD King Zora Thawed",                  {Category::cZorasDomain,});

//Zoras Fountain
ItemLocation ZF_IcebergFreestandingPoH        = ItemLocation::Collectable(0x59, 0x01, "ZF Iceberg Freestanding PoH",          {Category::cZorasFountain,});
ItemLocation ZF_BottomFreestandingPoH         = ItemLocation::Collectable(0x59, 0x14, "ZF Bottom Freestanding PoH",           {Category::cZorasFountain,});

//Lon Lon Ranch
ItemLocation LLR_TalonsChickens               = ItemLocation::Base       (0x4C, 0x14, "LLR Talons Chickens",                  {Category::cLonLonRanch, Category::cMinigame});
ItemLocation LLR_FreestandingPoH              = ItemLocation::Collectable(0x4C, 0x01, "LLR Freestanding PoH",                 {Category::cLonLonRanch,});
ItemLocation LLR_DekuScrubGrottoLeft          = ItemLocation::GrottoScrub(0xFC, 0x30, "LLR Deku Scrub Grotto Left",           {Category::cLonLonRanch, Category::cDekuScrub, Category::cGrotto});
ItemLocation LLR_DekuScrubGrottoRight         = ItemLocation::GrottoScrub(0xFC, 0x37, "LLR Deku Scrub Grotto Right",          {Category::cLonLonRanch, Category::cDekuScrub, Category::cGrotto});
ItemLocation LLR_DekuScrubGrottoCenter        = ItemLocation::GrottoScrub(0xFC, 0x33, "LLR Deku Scrub Grotto Center",         {Category::cLonLonRanch, Category::cDekuScrub, Category::cGrotto});

/*-------------------
   --- DUNGEONS ---
  -------------------*/

//Deku Tree Vanilla
ItemLocation DekuTree_MapChest                                = ItemLocation::Chest      (0x00, 0x03, "Deku Tree Map Chest",                                {Category::cDekuTree, Category::cVanillaMap,});
ItemLocation DekuTree_CompassChest                            = ItemLocation::Chest      (0x00, 0x02, "Deku Tree Compass Chest",                            {Category::cDekuTree, Category::cVanillaCompass,});
ItemLocation DekuTree_CompassRoomSideChest                    = ItemLocation::Chest      (0x00, 0x06, "Deku Tree Compass Room Side Chest",                  {Category::cDekuTree,});
ItemLocation DekuTree_BasementChest                           = ItemLocation::Chest      (0x00, 0x04, "Deku Tree Basement Chest",                           {Category::cDekuTree,});
ItemLocation DekuTree_SlingshotChest                          = ItemLocation::Chest      (0x00, 0x01, "Deku Tree Slingshot Chest",                          {Category::cDekuTree,});
ItemLocation DekuTree_SlingshotRoomSideChest                  = ItemLocation::Chest      (0x00, 0x05, "Deku Tree Slingshot Room Side Chest",                {Category::cDekuTree,});
//Deku Tree MQ
ItemLocation DekuTree_MQ_MapChest                             = ItemLocation::Chest      (0x00, 0x03, "Deku Tree MQ Map Chest",                             {Category::cDekuTree, Category::cVanillaMap,});
ItemLocation DekuTree_MQ_CompassChest                         = ItemLocation::Chest      (0x00, 0x01, "Deku Tree MQ Compass Chest",                         {Category::cDekuTree, Category::cVanillaCompass,});
ItemLocation DekuTree_MQ_SlingshotChest                       = ItemLocation::Chest      (0x00, 0x06, "Deku Tree MQ Slingshot Chest",                       {Category::cDekuTree,});
ItemLocation DekuTree_MQ_SlingshotRoomBackChest               = ItemLocation::Chest      (0x00, 0x02, "Deku Tree MQ Slingshot Room Back Chest",             {Category::cDekuTree,});
ItemLocation DekuTree_MQ_BasementChest                        = ItemLocation::Chest      (0x00, 0x04, "Deku Tree MQ Basement Chest",                        {Category::cDekuTree,});
ItemLocation DekuTree_MQ_BeforeSpinningLogChest               = ItemLocation::Chest      (0x00, 0x05, "Deku Tree MQ Before Spinning Log Chest",             {Category::cDekuTree,});
ItemLocation DekuTree_MQ_AfterSpinningLowChest                = ItemLocation::Chest      (0x00, 0x00, "Deku Tree MQ After Spinning Log Chest",              {Category::cDekuTree,});
ItemLocation DekuTree_MQ_DekuScrub                            = ItemLocation::Base       (0x00, 0x34, "Deku Tree MQ Deku Scrub",                            {Category::cDekuTree,});

//Dodongos Cavern Shared
ItemLocation DodongosCavern_BossRoomChest                     = ItemLocation::Chest      (0x12, 0x00, "Dodongos Cavern Boss Room Chest",                    {Category::cDodongosCavern,});
//Dodongos Cavern Vanilla
ItemLocation DodongosCavern_MapChest                          = ItemLocation::Chest      (0x01, 0x08, "Dodongos Cavern Map Chest",                          {Category::cDodongosCavern, Category::cVanillaMap,});
ItemLocation DodongosCavern_CompassChest                      = ItemLocation::Chest      (0x01, 0x05, "Dodongos Cavern Compass Chest",                      {Category::cDodongosCavern, Category::cVanillaCompass,});
ItemLocation DodongosCavern_BombFlowerPlatformChest           = ItemLocation::Chest      (0x01, 0x06, "Dodongos Cavern Bomb Flower Platform Chest",         {Category::cDodongosCavern,});
ItemLocation DodongosCavern_BombBagChest                      = ItemLocation::Chest      (0x01, 0x04, "Dodongos Cavern Bomb Bag Chest",                     {Category::cDodongosCavern,});
ItemLocation DodongosCavern_EndOfBridgeChest                  = ItemLocation::Chest      (0x01, 0x0A, "Dodongos Cavern End Of Bridge Chest",                {Category::cDodongosCavern,});
ItemLocation DodongosCavern_DekuScrubNearBombBagLeft          = ItemLocation::Base       (0x01, 0x30, "Dodongos Cavern Deku Scrub Near Bomb Bag Left",      {Category::cDodongosCavern, Category::cDekuScrub,});
ItemLocation DodongosCavern_DekuScrubSideRoomNearDodongos     = ItemLocation::Base       (0x01, 0x31, "Dodongos Cavern Deku Scrub Side Room Near Dodongos", {Category::cDodongosCavern, Category::cDekuScrub,});
ItemLocation DodongosCavern_DekuScrubNearBombBagRight         = ItemLocation::Base       (0x01, 0x33, "Dodongos Cavern Deku Scrub Near Bomb Bag Right",     {Category::cDodongosCavern, Category::cDekuScrub,});
ItemLocation DodongosCavern_DekuScrubLobby                    = ItemLocation::Base       (0x01, 0x34, "Dodongos Cavern Deku Scrub Lobby",                   {Category::cDodongosCavern, Category::cDekuScrub,});
//Dodongos Cavern MQ
ItemLocation DodongosCavern_MQ_MapChest                       = ItemLocation::Chest      (0x01, 0x00, "Dodongos Cavern MQ Map Chest",                       {Category::cDodongosCavern, Category::cVanillaMap,});
ItemLocation DodongosCavern_MQ_BombBagChest                   = ItemLocation::Chest      (0x01, 0x04, "Dodongos Cavern MQ Bomb Bag Chest",                  {Category::cDodongosCavern,});
ItemLocation DodongosCavern_MQ_CompassChest                   = ItemLocation::Chest      (0x01, 0x05, "Dodongos Cavern MQ Compass Chest",                   {Category::cDodongosCavern, Category::cVanillaCompass,});
ItemLocation DodongosCavern_MQ_LarvaeRoomChest                = ItemLocation::Chest      (0x01, 0x02, "Dodongos Cavern MQ Larvae Room Chest",               {Category::cDodongosCavern,});
ItemLocation DodongosCavern_MQ_TorchPuzzleRoomChest           = ItemLocation::Chest      (0x01, 0x03, "Dodongos Cavern MQ Torch Puzzle Room Chest",         {Category::cDodongosCavern,});
ItemLocation DodongosCavern_MQ_UnderGraveChest                = ItemLocation::Chest      (0x01, 0x01, "Dodongos Cavern MQ Under Grave Chest",               {Category::cDodongosCavern,});
ItemLocation DodongosCavern_MQ_DekuScrubLobbyRear             = ItemLocation::Base       (0x01, 0x31, "Dodongos Cavern Deku Scrub Lobby Rear",              {Category::cDodongosCavern, Category::cDekuScrub,});
ItemLocation DodongosCavern_MQ_DekuScrubLobbyFront            = ItemLocation::Base       (0x01, 0x33, "Dodongos Cavern Deku Scrub Lobby Front",             {Category::cDodongosCavern, Category::cDekuScrub,});
ItemLocation DodongosCavern_MQ_DekuScrubStaircase             = ItemLocation::Base       (0x01, 0x34, "Dodongos Cavern Deku Scrub Staircase",               {Category::cDodongosCavern, Category::cDekuScrub,});
ItemLocation DodongosCavern_MQ_DekuScrubSideRoomNearLowerLizalfos = ItemLocation::Base   (0x01, 0x39, "Dodongos Cavern Deku Scrub Side Room Near Lower Lizalfos", {Category::cDodongosCavern, Category::cDekuScrub,});

//Jabu Jabus Belly Vanilla
ItemLocation JabuJabusBelly_MapChest                          = ItemLocation::Chest      (0x02, 0x02, "Jabu Jabus Belly Map Chest",                         {Category::cJabuJabusBelly, Category::cVanillaMap,});
ItemLocation JabuJabusBelly_CompassChest                      = ItemLocation::Chest      (0x02, 0x04, "Jabu Jabus Belly Compass Chest",                     {Category::cJabuJabusBelly, Category::cVanillaCompass,});
ItemLocation JabuJabusBelly_BoomerangChest                    = ItemLocation::Chest      (0x02, 0x01, "Jabu Jabus Belly Boomerang Chest",                   {Category::cJabuJabusBelly,});
ItemLocation JabuJabusBelly_DekuScrub                         = ItemLocation::Base       (0x02, 0x30, "Jabu Jabus Belly Deku Scrub",                        {Category::cJabuJabusBelly, Category::cDekuScrub,});
//Jabu Jabus Belly MQ
ItemLocation JabuJabusBelly_MQ_FirstRoomSideChest             = ItemLocation::Chest      (0x02, 0x05, "Jabu Jabus Belly MQ First Room Side Chest",          {Category::cJabuJabusBelly,});
ItemLocation JabuJabusBelly_MQ_MapChest                       = ItemLocation::Chest      (0x02, 0x03, "Jabu Jabus Belly MQ Map Chest",                      {Category::cJabuJabusBelly, Category::cVanillaMap,});
ItemLocation JabuJabusBelly_MQ_SecondRoomLowerChest           = ItemLocation::Chest      (0x02, 0x02, "Jabu Jabus Belly MQ Second Room Lower Chest",        {Category::cJabuJabusBelly,});
ItemLocation JabuJabusBelly_MQ_CompassChest                   = ItemLocation::Chest      (0x02, 0x00, "Jabu Jabus Belly MQ Compass Chest",                  {Category::cJabuJabusBelly, Category::cVanillaCompass,});
ItemLocation JabuJabusBelly_MQ_SecondRoomUpperChest           = ItemLocation::Chest      (0x02, 0x07, "Jabu Jabus Belly MQ Second Room Upper Chest",        {Category::cJabuJabusBelly,});
ItemLocation JabuJabusBelly_MQ_BasementNearSwitchesChest      = ItemLocation::Chest      (0x02, 0x08, "Jabu Jabus Belly MQ Basement Near Switches Chest",   {Category::cJabuJabusBelly,});
ItemLocation JabuJabusBelly_MQ_BasementNearVinesChest         = ItemLocation::Chest      (0x02, 0x04, "Jabu Jabus Belly MQ Basement Near Vines Chest",      {Category::cJabuJabusBelly,});
ItemLocation JabuJabusBelly_MQ_NearBossChest                  = ItemLocation::Chest      (0x02, 0x0A, "Jabu Jabus Belly MQ Near Boss Chest",                {Category::cJabuJabusBelly,});
ItemLocation JabuJabusBelly_MQ_FallingLikeLikeRoomChest       = ItemLocation::Chest      (0x02, 0x09, "Jabu Jabus Belly MQ Falling Like Like Room Chest",   {Category::cJabuJabusBelly,});
ItemLocation JabuJabusBelly_MQ_BoomerangRoomSmallChest        = ItemLocation::Chest      (0x02, 0x01, "Jabu Jabus Belly MQ Boomerang Room Small Chest",     {Category::cJabuJabusBelly,});
ItemLocation JabuJabusBelly_MQ_BoomerangChest                 = ItemLocation::Chest      (0x02, 0x06, "Jabu Jabus Belly MQ Boomerang Chest",                {Category::cJabuJabusBelly,});
//COW

//Forest Temple Vanilla
ItemLocation ForestTemple_FirstRoomChest                      = ItemLocation::Chest      (0x03, 0x03, "Forest Temple First Room Chest",                     {Category::cForestTemple, Category::cVanillaSmallKey});
ItemLocation ForestTemple_FirstStalfosChest                   = ItemLocation::Chest      (0x03, 0x00, "Forest Temple First Stalfos Chest",                  {Category::cForestTemple, Category::cVanillaSmallKey});
ItemLocation ForestTemple_RaisedIslandCourtyardChest          = ItemLocation::Chest      (0x03, 0x05, "Forest Temple Raised Island Courtyard Chest",        {Category::cForestTemple,});
ItemLocation ForestTemple_MapChest                            = ItemLocation::Chest      (0x03, 0x01, "Forest Temple Map Chest",                            {Category::cForestTemple, Category::cVanillaMap,});
ItemLocation ForestTemple_WellChest                           = ItemLocation::Chest      (0x03, 0x09, "Forest Temple Well Chest",                           {Category::cForestTemple, Category::cVanillaSmallKey});
ItemLocation ForestTemple_FallingCeilingRoomChest             = ItemLocation::Chest      (0x03, 0x07, "Forest Temple Falling Ceiling Room Chest",           {Category::cForestTemple,});
ItemLocation ForestTemple_EyeSwitchChest                      = ItemLocation::Chest      (0x03, 0x04, "Forest Temple Eye Switch Chest",                     {Category::cForestTemple,});
ItemLocation ForestTemple_BossKeyChest                        = ItemLocation::Chest      (0x03, 0x0E, "Forest Temple Boss Key Chest",                       {Category::cForestTemple, Category::cVanillaBossKey});
ItemLocation ForestTemple_FloormasterChest                    = ItemLocation::Chest      (0x03, 0x02, "Forest Temple Floormaster Chest",                    {Category::cForestTemple, Category::cVanillaSmallKey});
ItemLocation ForestTemple_BowChest                            = ItemLocation::Chest      (0x03, 0x0C, "Forest Temple Bow Chest",                            {Category::cForestTemple,});
ItemLocation ForestTemple_RedPoeChest                         = ItemLocation::Chest      (0x03, 0x0D, "Forest Temple Red Poe Chest",                        {Category::cForestTemple, Category::cVanillaSmallKey});
ItemLocation ForestTemple_BluePoeChest                        = ItemLocation::Chest      (0x03, 0x0F, "Forest Temple Blue Poe Chest",                       {Category::cForestTemple, Category::cVanillaCompass,});
ItemLocation ForestTemple_BasementChest                       = ItemLocation::Chest      (0x03, 0x0B, "Forest Temple Basement Chest",                       {Category::cForestTemple,});
//Forest Temple MQ
ItemLocation ForestTemple_MQ_FirstRoomChest                   = ItemLocation::Chest      (0x03, 0x03, "Forest Temple MQ First Room Chest",                  {Category::cForestTemple, Category::cVanillaSmallKey});
ItemLocation ForestTemple_MQ_WolfosChest                      = ItemLocation::Chest      (0x03, 0x00, "Forest Temple MQ Wolfos Chest",                      {Category::cForestTemple, Category::cVanillaSmallKey});
ItemLocation ForestTemple_MQ_BowChest                         = ItemLocation::Chest      (0x03, 0x0C, "Forest Temple MQ Bow Chest",                         {Category::cForestTemple,});
ItemLocation ForestTemple_MQ_RaisedIslandCourtyardLowerChest  = ItemLocation::Chest      (0x03, 0x01, "Forest Temple MQ Raised Island Courtyard Lower Chest", {Category::cForestTemple, Category::cVanillaSmallKey});
ItemLocation ForestTemple_MQ_RaisedIslandCourtyardUpperChest  = ItemLocation::Chest      (0x03, 0x05, "Forest Temple MQ Raised Island Courtyard Upper Chest", {Category::cForestTemple, Category::cVanillaSmallKey});
ItemLocation ForestTemple_MQ_WellChest                        = ItemLocation::Chest      (0x03, 0x09, "Forest Temple MQ Well Chest",                        {Category::cForestTemple, Category::cVanillaSmallKey});
ItemLocation ForestTemple_MQ_MapChest                         = ItemLocation::Chest      (0x03, 0x0D, "Forest Temple MQ Map Chest",                         {Category::cForestTemple, Category::cVanillaMap,});
ItemLocation ForestTemple_MQ_CompassChest                     = ItemLocation::Chest      (0x03, 0x0F, "Forest Temple MQ Compass Chest",                     {Category::cForestTemple, Category::cVanillaCompass,});
ItemLocation ForestTemple_MQ_FallingCeilingRoomChest          = ItemLocation::Chest      (0x03, 0x06, "Forest Temple MQ Falling Ceiling Room Chest",        {Category::cForestTemple,});
ItemLocation ForestTemple_MQ_BasementChest                    = ItemLocation::Chest      (0x03, 0x0B, "Forest Temple MQ Basement Chest",                    {Category::cForestTemple,});
ItemLocation ForestTemple_MQ_RedeadChest                      = ItemLocation::Chest      (0x03, 0x02, "Forest Temple MQ Redead Chest",                      {Category::cForestTemple, Category::cVanillaSmallKey});
ItemLocation ForestTemple_MQ_BossKeyChest                     = ItemLocation::Chest      (0x03, 0x0E, "Forest Temple MQ Boss Key Chest",                    {Category::cForestTemple, Category::cVanillaBossKey});

//Fire Temple Vanilla
ItemLocation FireTemple_NearBossChest                         = ItemLocation::Chest      (0x04, 0x01, "Fire Temple Near Boss Chest",                        {Category::cFireTemple, Category::cVanillaSmallKey});
ItemLocation FireTemple_FlareDancerChest                      = ItemLocation::Chest      (0x04, 0x00, "Fire Temple Flare Dancer Chest",                     {Category::cFireTemple,});
ItemLocation FireTemple_BossKeyChest                          = ItemLocation::Chest      (0x04, 0x0C, "Fire Temple Boss Key Chest",                         {Category::cFireTemple, Category::cVanillaBossKey});
ItemLocation FireTemple_BigLavaRoomBlockedDoorChest           = ItemLocation::Chest      (0x04, 0x02, "Fire Temple Big Lava Room Blocked Door Chest",       {Category::cFireTemple, Category::cVanillaSmallKey});
ItemLocation FireTemple_BigLavaRoomLowerOpenDoorChest         = ItemLocation::Chest      (0x04, 0x04, "Fire Temple Big Lava Room Lower Open Door Chest",    {Category::cFireTemple, Category::cVanillaSmallKey});
ItemLocation FireTemple_BoulderMazeLowerChest                 = ItemLocation::Chest      (0x04, 0x03, "Fire Temple Boulder Maze Lower Chest",               {Category::cFireTemple, Category::cVanillaSmallKey});
ItemLocation FireTemple_BoulderMazeUpperChest                 = ItemLocation::Chest      (0x04, 0x06, "Fire Temple Boulder Maze Upper Chest",               {Category::cFireTemple, Category::cVanillaSmallKey});
ItemLocation FireTemple_BoulderMazeSideRoomChest              = ItemLocation::Chest      (0x04, 0x08, "Fire Temple Boulder Maze Side Room Chest",           {Category::cFireTemple, Category::cVanillaSmallKey});
ItemLocation FireTemple_BoulderMazeShortcutChest              = ItemLocation::Chest      (0x04, 0x0B, "Fire Temple Boulder Maze Shortcut Chest",            {Category::cFireTemple, Category::cVanillaSmallKey});
ItemLocation FireTemple_ScarecrowChest                        = ItemLocation::Chest      (0x04, 0x0D, "Fire Temple Scarecrow Chest",                        {Category::cFireTemple,});
ItemLocation FireTemple_MapChest                              = ItemLocation::Chest      (0x04, 0x0A, "Fire Temple Map Chest",                              {Category::cFireTemple, Category::cVanillaMap,});
ItemLocation FireTemple_CompassChest                          = ItemLocation::Chest      (0x04, 0x07, "Fire Temple Compass Chest",                          {Category::cFireTemple, Category::cVanillaCompass,});
ItemLocation FireTemple_HighestGoronChest                     = ItemLocation::Chest      (0x04, 0x09, "Fire Temple Highest Goron Chest",                    {Category::cFireTemple, Category::cVanillaSmallKey});
ItemLocation FireTemple_MegatonHammerChest                    = ItemLocation::Chest      (0x04, 0x05, "Fire Temple Megaton Hammer Chest",                   {Category::cFireTemple,});
//Fire Temple MQ
ItemLocation FireTemple_MQ_NearBossChest                      = ItemLocation::Chest      (0x04, 0x07, "Fire Temple MQ Near Boss Chest",                     {Category::cFireTemple, Category::cVanillaSmallKey});
ItemLocation FireTemple_MQ_MegatonHammerChest                 = ItemLocation::Chest      (0x04, 0x00, "Fire Temple MQ Megaton Hammer Chest",                {Category::cFireTemple,});
ItemLocation FireTemple_MQ_CompassChest                       = ItemLocation::Chest      (0x04, 0x0B, "Fire Temple MQ Compass Chest",                       {Category::cFireTemple, Category::cVanillaCompass,});
ItemLocation FireTemple_MQ_LizalfosMazeLowerChest             = ItemLocation::Chest      (0x04, 0x03, "Fire Temple MQ Lizalfos Maze Lower Chest",           {Category::cFireTemple,});
ItemLocation FireTemple_MQ_LizalfosMazeUpperChest             = ItemLocation::Chest      (0x04, 0x06, "Fire Temple MQ Lizalfos Maze Upper Chest",           {Category::cFireTemple,});
ItemLocation FireTemple_MQ_ChestOnFire                        = ItemLocation::Chest      (0x04, 0x05, "Fire Temple MQ Chest on Fire",                       {Category::cFireTemple, Category::cVanillaSmallKey});
ItemLocation FireTemple_MQ_MapRoomSideChest                   = ItemLocation::Chest      (0x04, 0x02, "Fire Temple MQ Map Room Side Chest",                 {Category::cFireTemple,});
ItemLocation FireTemple_MQ_MapChest                           = ItemLocation::Chest      (0x04, 0x0C, "Fire Temple MQ Map Chest",                           {Category::cFireTemple, Category::cVanillaMap,});
ItemLocation FireTemple_MQ_BossKeyChest                       = ItemLocation::Chest      (0x04, 0x04, "Fire Temple MQ Boss Key Chest",                      {Category::cFireTemple, Category::cVanillaBossKey});
ItemLocation FireTemple_MQ_BigLavaRoomBlockedDoorChest        = ItemLocation::Chest      (0x04, 0x01, "Fire Temple MQ Big Lava Room Blocked Door Chest",    {Category::cFireTemple, Category::cVanillaSmallKey});
ItemLocation FireTemple_MQ_LizalfosMazeSideRoomChest          = ItemLocation::Chest      (0x04, 0x08, "Fire Temple MQ Lizalfos Maze Side Room Chest",       {Category::cFireTemple, Category::cVanillaSmallKey});
ItemLocation FireTemple_MQ_FreestandingKey                    = ItemLocation::Collectable(0x04, 0x1C, "Fire Temple MQ Freestanding Key",                    {Category::cFireTemple, Category::cVanillaSmallKey});

//Water Temple Vanilla
ItemLocation WaterTemple_MapChest                             = ItemLocation::Chest      (0x05, 0x02, "Water Temple Map Chest",                             {Category::cWaterTemple, Category::cVanillaMap,});
ItemLocation WaterTemple_CompassChest                         = ItemLocation::Chest      (0x05, 0x09, "Water Temple Compass Chest",                         {Category::cWaterTemple, Category::cVanillaCompass,});
ItemLocation WaterTemple_TorchesChest                         = ItemLocation::Chest      (0x05, 0x01, "Water Temple Torches Chest",                         {Category::cWaterTemple, Category::cVanillaSmallKey});
ItemLocation WaterTemple_DragonChest                          = ItemLocation::Chest      (0x05, 0x0A, "Water Temple Dragon Chest",                          {Category::cWaterTemple, Category::cVanillaSmallKey});
ItemLocation WaterTemple_CentralBowTargetChest                = ItemLocation::Chest      (0x05, 0x08, "Water Temple Central Bow Target Chest",              {Category::cWaterTemple, Category::cVanillaSmallKey});
ItemLocation WaterTemple_CentralPillarChest                   = ItemLocation::Chest      (0x05, 0x06, "Water Temple Central Pillar Chest",                  {Category::cWaterTemple, Category::cVanillaSmallKey});
ItemLocation WaterTemple_CrackedWallChest                     = ItemLocation::Chest      (0x05, 0x00, "Water Temple Cracked Wall Chest",                    {Category::cWaterTemple, Category::cVanillaSmallKey});
ItemLocation WaterTemple_BossKeyChest                         = ItemLocation::Chest      (0x05, 0x05, "Water Temple Boss Key Chest",                        {Category::cWaterTemple, Category::cVanillaBossKey});
ItemLocation WaterTemple_LongshotChest                        = ItemLocation::Chest      (0x05, 0x07, "Water Temple Longshot Chest",                        {Category::cWaterTemple,});
ItemLocation WaterTemple_RiverChest                           = ItemLocation::Chest      (0x05, 0x03, "Water Temple River Chest",                           {Category::cWaterTemple, Category::cVanillaSmallKey});
//Water Temple MQ
ItemLocation WaterTemple_MQ_CentralPillarChest                = ItemLocation::Chest      (0x05, 0x06, "Water Temple MQ Central Pillar Chest",               {Category::cWaterTemple, Category::cVanillaSmallKey});
ItemLocation WaterTemple_MQ_BossKeyChest                      = ItemLocation::Chest      (0x05, 0x05, "Water Temple MQ Boss Key Chest",                     {Category::cWaterTemple, Category::cVanillaBossKey});
ItemLocation WaterTemple_MQ_LongshotChest                     = ItemLocation::Chest      (0x05, 0x00, "Water Temple MQ Longshot Chest",                     {Category::cWaterTemple,});
ItemLocation WaterTemple_MQ_CompassChest                      = ItemLocation::Chest      (0x05, 0x01, "Water Temple MQ Compass Chest",                      {Category::cWaterTemple, Category::cVanillaCompass,});
ItemLocation WaterTemple_MQ_MapChest                          = ItemLocation::Chest      (0x05, 0x02, "Water Temple MQ Map Chest",                          {Category::cWaterTemple, Category::cVanillaMap,});
ItemLocation WaterTemple_MQ_FreestandingKey                   = ItemLocation::Collectable(0x05, 0x01, "Water Temple MQ Freestanding Key",                   {Category::cWaterTemple, Category::cVanillaSmallKey});

//Spirit Temple Shared
ItemLocation SpiritTemple_SilverGauntletsChest                = ItemLocation::Chest      (0x5C, 0x0B, "Spirit Temple Silver Gauntlets Chest",               {Category::cSpiritTemple, Category::cDesertColossus});
ItemLocation SpiritTemple_MirrorShieldChest                   = ItemLocation::Chest      (0x5C, 0x09, "Spirit Temple Mirror Shield Chest",                  {Category::cSpiritTemple, Category::cDesertColossus});
//Spirit Temple Vanilla
ItemLocation SpiritTemple_ChildBridgeChest                    = ItemLocation::Chest      (0x06, 0x08, "Spirit Temple Child Bridge Chest",                   {Category::cSpiritTemple,});
ItemLocation SpiritTemple_ChildEarlyTorchesChest              = ItemLocation::Chest      (0x06, 0x00, "Spirit Temple Child Early Torches Chest",            {Category::cSpiritTemple, Category::cVanillaSmallKey});
ItemLocation SpiritTemple_CompassChest                        = ItemLocation::Chest      (0x06, 0x04, "Spirit Temple Compass Chest",                        {Category::cSpiritTemple, Category::cVanillaCompass,});
ItemLocation SpiritTemple_EarlyAdultRightChest                = ItemLocation::Chest      (0x06, 0x07, "Spirit Temple Early Adult Right Chest",              {Category::cSpiritTemple, Category::cVanillaSmallKey});
ItemLocation SpiritTemple_FirstMirrorLeftChest                = ItemLocation::Chest      (0x06, 0x0D, "Spirit Temple First Mirror Left Chest",              {Category::cSpiritTemple,});
ItemLocation SpiritTemple_FirstMirrorRightChest               = ItemLocation::Chest      (0x06, 0x0E, "Spirit Temple First Mirror Right Chest",             {Category::cSpiritTemple,});
ItemLocation SpiritTemple_MapChest                            = ItemLocation::Chest      (0x06, 0x03, "Spirit Temple Map Chest",                            {Category::cSpiritTemple, Category::cVanillaMap,});
ItemLocation SpiritTemple_ChildClimbNorthChest                = ItemLocation::Chest      (0x06, 0x06, "Spirit Temple Child Climb North Chest",              {Category::cSpiritTemple,});
ItemLocation SpiritTemple_ChildClimbEastChest                 = ItemLocation::Chest      (0x06, 0x0C, "Spirit Temple Child Climb East Chest",               {Category::cSpiritTemple,});
ItemLocation SpiritTemple_SunBlockRoomChest                   = ItemLocation::Chest      (0x06, 0x01, "Spirit Temple Sun Block Room Chest",                 {Category::cSpiritTemple, Category::cVanillaSmallKey});
ItemLocation SpiritTemple_StatueRoomHandChest                 = ItemLocation::Chest      (0x06, 0x02, "Spirit Temple Statue Room Hand Chest",               {Category::cSpiritTemple, Category::cVanillaSmallKey});
ItemLocation SpiritTemple_StatueRoomNortheastChest            = ItemLocation::Chest      (0x06, 0x0F, "Spirit Temple Statue Room Northeast Chest",          {Category::cSpiritTemple,});
ItemLocation SpiritTemple_NearFourArmosChest                  = ItemLocation::Chest      (0x06, 0x05, "Spirit Temple Near Four Armos Chest",                {Category::cSpiritTemple, Category::cVanillaSmallKey});
ItemLocation SpiritTemple_HallwayRightInvisibleChest          = ItemLocation::Chest      (0x06, 0x14, "Spirit Temple Hallway Right Invisible Chest",        {Category::cSpiritTemple,});
ItemLocation SpiritTemple_HallwayLeftInvisibleChest           = ItemLocation::Chest      (0x06, 0x15, "Spirit Temple Hallway Left Invisible Chest",         {Category::cSpiritTemple,});
ItemLocation SpiritTemple_BossKeyChest                        = ItemLocation::Chest      (0x06, 0x0A, "Spirit Temple Boss Key Chest",                       {Category::cSpiritTemple, Category::cVanillaBossKey});
ItemLocation SpiritTemple_TopmostChest                        = ItemLocation::Chest      (0x06, 0x12, "Spirit Temple Topmost Chest",                        {Category::cSpiritTemple,});
//Spirit Temple MQ
ItemLocation SpiritTemple_MQ_EntranceFrontLeftChest           = ItemLocation::Chest      (0x06, 0x1A, "Spirit Temple MQ Entrance Front Left Chest",         {Category::cSpiritTemple,});
ItemLocation SpiritTemple_MQ_EntranceBackRightChest           = ItemLocation::Chest      (0x06, 0x1F, "Spirit Temple MQ Entrance Back Right Chest",         {Category::cSpiritTemple,});
ItemLocation SpiritTemple_MQ_EntranceFrontRightChest          = ItemLocation::Chest      (0x06, 0x1B, "Spirit Temple MQ Entrance Front Right Chest",        {Category::cSpiritTemple, Category::cVanillaSmallKey});
ItemLocation SpiritTemple_MQ_EntranceBackLeftChest            = ItemLocation::Chest      (0x06, 0x1E, "Spirit Temple MQ Entrance Back Left Chest",          {Category::cSpiritTemple, Category::cVanillaSmallKey});
ItemLocation SpiritTemple_MQ_ChildHammerSwitchChest           = ItemLocation::Chest      (0x06, 0x1D, "Spirit Temple MQ Child Hammer Switch Chest",         {Category::cSpiritTemple, Category::cVanillaSmallKey});
ItemLocation SpiritTemple_MQ_MapChest                         = ItemLocation::Chest      (0x06, 0x00, "Spirit Temple MQ Map Chest",                         {Category::cSpiritTemple, Category::cVanillaMap,});
ItemLocation SpiritTemple_MQ_MapRoomEnemyChest                = ItemLocation::Chest      (0x06, 0x08, "Spirit Temple MQ Map Room Enemy Chest",              {Category::cSpiritTemple, Category::cVanillaSmallKey});
ItemLocation SpiritTemple_MQ_ChildClimbNorthChest             = ItemLocation::Chest      (0x06, 0x06, "Spirit Temple MQ Child Climb North Chest",           {Category::cSpiritTemple,});
ItemLocation SpiritTemple_MQ_ChildClimbSouthChest             = ItemLocation::Chest      (0x06, 0x0C, "Spirit Temple MQ Child Climb South Chest",           {Category::cSpiritTemple, Category::cVanillaSmallKey});
ItemLocation SpiritTemple_MQ_CompassChest                     = ItemLocation::Chest      (0x06, 0x03, "Spirit Temple MQ Compass Chest",                     {Category::cSpiritTemple, Category::cVanillaCompass,});
ItemLocation SpiritTemple_MQ_StatueRoomLullabyChest           = ItemLocation::Chest      (0x06, 0x0F, "Spirit Temple MQ Statue Room Lullaby Chest",         {Category::cSpiritTemple,});
ItemLocation SpiritTemple_MQ_StatueRoomInvisibleChest         = ItemLocation::Chest      (0x06, 0x02, "Spirit Temple MQ Statue Room Invisible Chest",       {Category::cSpiritTemple,});
ItemLocation SpiritTemple_MQ_SilverBlockHallwayChest          = ItemLocation::Chest      (0x06, 0x1C, "Spirit Temple MQ Silver Block Hallway Chest",        {Category::cSpiritTemple, Category::cVanillaSmallKey});
ItemLocation SpiritTemple_MQ_SunBlockRoomChest                = ItemLocation::Chest      (0x06, 0x01, "Spirit Temple MQ Sun Block Room Chest",              {Category::cSpiritTemple,});
ItemLocation SpiritTemple_MQ_SymphonyRoomChest                = ItemLocation::Chest      (0x06, 0x07, "Spirit Temple MQ Symphony Room Chest",               {Category::cSpiritTemple,});
ItemLocation SpiritTemple_MQ_LeeverRoomChest                  = ItemLocation::Chest      (0x06, 0x04, "Spirit Temple MQ Leever Room Chest",                 {Category::cSpiritTemple,});
ItemLocation SpiritTemple_MQ_BeamosRoomChest                  = ItemLocation::Chest      (0x06, 0x19, "Spirit Temple MQ Beamos Room Chest",                 {Category::cSpiritTemple,});
ItemLocation SpiritTemple_MQ_ChestSwitchChest                 = ItemLocation::Chest      (0x06, 0x18, "Spirit Temple MQ Chest Switch Chest",                {Category::cSpiritTemple,});
ItemLocation SpiritTemple_MQ_BossKeyChest                     = ItemLocation::Chest      (0x06, 0x05, "Spirit Temple MQ Boss Key Chest",                    {Category::cSpiritTemple, Category::cVanillaBossKey});
ItemLocation SpiritTemple_MQ_MirrorPuzzleInvisibleChest       = ItemLocation::Chest      (0x06, 0x12, "Spirit Temple MQ Mirror Puzzle Invisible Chest",     {Category::cSpiritTemple, Category::cVanillaSmallKey});

//Shadow Temple Vanilla
ItemLocation ShadowTemple_MapChest                            = ItemLocation::Chest      (0x07, 0x01, "Shadow Temple Map Chest",                            {Category::cShadowTemple, Category::cVanillaMap,});
ItemLocation ShadowTemple_HoverBootsChest                     = ItemLocation::Chest      (0x07, 0x07, "Shadow Temple Hover Boots Chest",                    {Category::cShadowTemple,});
ItemLocation ShadowTemple_CompassChest                        = ItemLocation::Chest      (0x07, 0x03, "Shadow Temple Compass Chest",                        {Category::cShadowTemple, Category::cVanillaCompass,});
ItemLocation ShadowTemple_EarlySilverRupeeChest               = ItemLocation::Chest      (0x07, 0x02, "Shadow Temple Early Silver Rupee Chest",             {Category::cShadowTemple, Category::cVanillaSmallKey});
ItemLocation ShadowTemple_InvisibleBladesVisibleChest         = ItemLocation::Chest      (0x07, 0x0C, "Shadow Temple Invisible Blades Visible Chest",       {Category::cShadowTemple,});
ItemLocation ShadowTemple_InvisibleBladesInvisibleChest       = ItemLocation::Chest      (0x07, 0x16, "Shadow Temple Invisible Blades Invisible Chest",     {Category::cShadowTemple,});
ItemLocation ShadowTemple_FallingSpikesLowerChest             = ItemLocation::Chest      (0x07, 0x05, "Shadow Temple Falling Spikes Lower Chest",           {Category::cShadowTemple,});
ItemLocation ShadowTemple_FallingSpikesUpperChest             = ItemLocation::Chest      (0x07, 0x06, "Shadow Temple Falling Spikes Upper Chest",           {Category::cShadowTemple,});
ItemLocation ShadowTemple_FallingSpikesSwitchChest            = ItemLocation::Chest      (0x07, 0x04, "Shadow Temple Falling Spikes Switch Chest",          {Category::cShadowTemple, Category::cVanillaSmallKey});
ItemLocation ShadowTemple_InvisibleSpikesChest                = ItemLocation::Chest      (0x07, 0x09, "Shadow Temple Invisible Spikes Chest",               {Category::cShadowTemple,});
ItemLocation ShadowTemple_WindHintChest                       = ItemLocation::Chest      (0x07, 0x15, "Shadow Temple Wind Hint Chest",                      {Category::cShadowTemple,});
ItemLocation ShadowTemple_AfterWindEnemyChest                 = ItemLocation::Chest      (0x07, 0x08, "Shadow Temple After Wind Enemy Chest",               {Category::cShadowTemple,});
ItemLocation ShadowTemple_AfterWindHiddenChest                = ItemLocation::Chest      (0x07, 0x14, "Shadow Temple After Wind Hidden Chest",              {Category::cShadowTemple, Category::cVanillaSmallKey});
ItemLocation ShadowTemple_SpikeWallsLeftChest                 = ItemLocation::Chest      (0x07, 0x0A, "Shadow Temple Spike Walls Left Chest",               {Category::cShadowTemple,});
ItemLocation ShadowTemple_BossKeyChest                        = ItemLocation::Chest      (0x07, 0x0B, "Shadow Temple Boss Key Chest",                       {Category::cShadowTemple, Category::cVanillaBossKey});
ItemLocation ShadowTemple_InvisibleFloormasterChest           = ItemLocation::Chest      (0x07, 0x0D, "Shadow Temple Invisible Floormaster Chest",          {Category::cShadowTemple, Category::cVanillaSmallKey});
ItemLocation ShadowTemple_FreestandingKey                     = ItemLocation::Collectable(0x07, 0x01, "Shadow Temple Freestanding Key",                     {Category::cShadowTemple, Category::cVanillaSmallKey});
//Shadow Temple MQ
ItemLocation ShadowTemple_MQ_CompassChest                     = ItemLocation::Chest      (0x07, 0x01, "Shadow Temple MQ Compass Chest",                     {Category::cShadowTemple, Category::cVanillaCompass,});
ItemLocation ShadowTemple_MQ_HoverBootsChest                  = ItemLocation::Chest      (0x07, 0x07, "Shadow Temple MQ Hover Boots Chest",                 {Category::cShadowTemple,});
ItemLocation ShadowTemple_MQ_EarlyGibdosChest                 = ItemLocation::Chest      (0x07, 0x03, "Shadow Temple MQ Early Gibdos Chest",                {Category::cShadowTemple, Category::cVanillaSmallKey});
ItemLocation ShadowTemple_MQ_MapChest                         = ItemLocation::Chest      (0x07, 0x02, "Shadow Temple MQ Map Chest",                         {Category::cShadowTemple, Category::cVanillaMap,});
ItemLocation ShadowTemple_MQ_BeamosSilverRupeesChest          = ItemLocation::Chest      (0x07, 0x0F, "Shadow Temple MQ Beamos Silver Rupees Chest",        {Category::cShadowTemple,});
ItemLocation ShadowTemple_MQ_FallingSpikesSwitchChest         = ItemLocation::Chest      (0x07, 0x04, "Shadow Temple MQ Falling Spikes Switch Chest",       {Category::cShadowTemple, Category::cVanillaSmallKey});
ItemLocation ShadowTemple_MQ_FallingSpikesLowerChest          = ItemLocation::Chest      (0x07, 0x05, "Shadow Temple MQ Falling Spikes Lower Chest",        {Category::cShadowTemple,});
ItemLocation ShadowTemple_MQ_FallingSpikesUpperChest          = ItemLocation::Chest      (0x07, 0x06, "Shadow Temple MQ Falling Spikes Upper Chest",        {Category::cShadowTemple,});
ItemLocation ShadowTemple_MQ_InvisibleSpikesChest             = ItemLocation::Chest      (0x07, 0x09, "Shadow Temple MQ Invisible Spikes Chest",            {Category::cShadowTemple,});
ItemLocation ShadowTemple_MQ_BossKeyChest                     = ItemLocation::Chest      (0x07, 0x0B, "Shadow Temple MQ Boss Key Chest",                    {Category::cShadowTemple, Category::cVanillaBossKey});
ItemLocation ShadowTemple_MQ_SpikeWallsLeftChest              = ItemLocation::Chest      (0x07, 0x0A, "Shadow Temple MQ Spike Walls Left Chest",            {Category::cShadowTemple,});
ItemLocation ShadowTemple_MQ_StalfosRoomChest                 = ItemLocation::Chest      (0x07, 0x10, "Shadow Temple MQ Stalfos Room Chest",                {Category::cShadowTemple,});
ItemLocation ShadowTemple_MQ_InvisibleBladesInvisibleChest    = ItemLocation::Chest      (0x07, 0x16, "Shadow Temple MQ Invisible Blades Invisible Chest",  {Category::cShadowTemple, Category::cVanillaSmallKey});
ItemLocation ShadowTemple_MQ_InvisibleBladesVisibleChest      = ItemLocation::Chest      (0x07, 0x0C, "Shadow Temple MQ Invisible Blades Visible Chest",    {Category::cShadowTemple,});
ItemLocation ShadowTemple_MQ_BombFlowerChest                  = ItemLocation::Chest      (0x07, 0x0D, "Shadow Temple MQ Bomb Flower Chest",                 {Category::cShadowTemple,});
ItemLocation ShadowTemple_MQ_WindHintChest                    = ItemLocation::Chest      (0x07, 0x15, "Shadow Temple MQ Wind Hint Chest",                   {Category::cShadowTemple, Category::cVanillaSmallKey});
ItemLocation ShadowTemple_MQ_AfterWindHiddenChest             = ItemLocation::Chest      (0x07, 0x14, "Shadow Temple MQ After Wind Hidden Chest",           {Category::cShadowTemple,});
ItemLocation ShadowTemple_MQ_AfterWindEnemyChest              = ItemLocation::Chest      (0x07, 0x08, "Shadow Temple MQ After Wind Enemy Chest",            {Category::cShadowTemple,});
ItemLocation ShadowTemple_MQ_NearShipInvisibleChest           = ItemLocation::Chest      (0x07, 0x0E, "Shadow Temple MQ Near Ship Invisible Chest",         {Category::cShadowTemple, Category::cVanillaSmallKey});
ItemLocation ShadowTemple_MQ_FreestandingKey                  = ItemLocation::Collectable(0x07, 0x06, "Shadow Temple MQ Freestanding Key",                  {Category::cShadowTemple, Category::cVanillaSmallKey});

//Bottom of the Well Vanilla
ItemLocation BottomOfTheWell_FrontLeftFakeWallChest           = ItemLocation::Chest      (0x08, 0x08, "Bottom of the Well Front Left Fake Wall Chest",         {Category::cBottomOfTheWell, Category::cVanillaSmallKey});
ItemLocation BottomOfTheWell_FrontCenterBombableChest         = ItemLocation::Chest      (0x08, 0x02, "Bottom of the Well Front Center Bombable Chest",        {Category::cBottomOfTheWell,});
ItemLocation BottomOfTheWell_RightBottomFakeWallChest         = ItemLocation::Chest      (0x08, 0x05, "Bottom of the Well Right Bottom Fake Wall Chest",       {Category::cBottomOfTheWell, Category::cVanillaSmallKey});
ItemLocation BottomOfTheWell_CompassChest                     = ItemLocation::Chest      (0x08, 0x01, "Bottom of the Well Compass Chest",                      {Category::cBottomOfTheWell, Category::cVanillaCompass,});
ItemLocation BottomOfTheWell_CenterSkulltulaChest             = ItemLocation::Chest      (0x08, 0x0E, "Bottom of the Well Center Skulltula Chest",             {Category::cBottomOfTheWell,});
ItemLocation BottomOfTheWell_BackLeftBombableChest            = ItemLocation::Chest      (0x08, 0x04, "Bottom of the Well Back Left Bombable Chest",           {Category::cBottomOfTheWell,});
ItemLocation BottomOfTheWell_LensOfTruthChest                 = ItemLocation::Chest      (0x08, 0x03, "Bottom of the Well Lens of Truth Chest",                {Category::cBottomOfTheWell, Category::cSongDungeonReward});
ItemLocation BottomOfTheWell_InvisibleChest                   = ItemLocation::Chest      (0x08, 0x14, "Bottom of the Well Invisible Chest",                    {Category::cBottomOfTheWell,});
ItemLocation BottomOfTheWell_UnderwaterFrontChest             = ItemLocation::Chest      (0x08, 0x10, "Bottom of the Well Underwater Front Chest",             {Category::cBottomOfTheWell,});
ItemLocation BottomOfTheWell_UnderwaterLeftChest              = ItemLocation::Chest      (0x08, 0x09, "Bottom of the Well Underwater Left Chest",              {Category::cBottomOfTheWell,});
ItemLocation BottomOfTheWell_MapChest                         = ItemLocation::Chest      (0x08, 0x07, "Bottom of the Well Map Chest",                          {Category::cBottomOfTheWell, Category::cVanillaMap,});
ItemLocation BottomOfTheWell_FireKeeseChest                   = ItemLocation::Chest      (0x08, 0x0A, "Bottom of the Well Fire Keese Chest",                   {Category::cBottomOfTheWell,});
ItemLocation BottomOfTheWell_LikeLikeChest                    = ItemLocation::Chest      (0x08, 0x0C, "Bottom of the Well Like Like Chest",                    {Category::cBottomOfTheWell,});
ItemLocation BottomOfTheWell_FreestandingKey                  = ItemLocation::Collectable(0x08, 0x01, "Bottom of the Well Freestanding Key",                   {Category::cBottomOfTheWell, Category::cVanillaSmallKey});
//Bottom of the Well MQ
ItemLocation BottomOfTheWell_MQ_MapChest                      = ItemLocation::Chest      (0x08, 0x03, "Bottom of the Well MQ Map Chest",                       {Category::cBottomOfTheWell, Category::cVanillaMap,});
ItemLocation BottomOfTheWell_MQ_LensOfTruthChest              = ItemLocation::Chest      (0x08, 0x01, "Bottom of the Well MQ Lens of Truth Chest",             {Category::cBottomOfTheWell, Category::cSongDungeonReward});
ItemLocation BottomOfTheWell_MQ_CompassChest                  = ItemLocation::Chest      (0x08, 0x02, "Bottom of the Well MQ Compass Chest",                   {Category::cBottomOfTheWell, Category::cVanillaCompass,});
ItemLocation BottomOfTheWell_MQ_DeadHandFreestandingKey       = ItemLocation::Collectable(0x08, 0x02, "Bottom of the Well MQ Dead Hand Freestanding Key",      {Category::cBottomOfTheWell, Category::cVanillaSmallKey});
ItemLocation BottomOfTheWell_MQ_EastInnerRoomFreestandingKey  = ItemLocation::Collectable(0x08, 0x01, "Bottom of the Well MQ East Inner Room Freestanding Key",{Category::cBottomOfTheWell, Category::cVanillaSmallKey});

//Ice Cavern Vanilla
ItemLocation IceCavern_MapChest                               = ItemLocation::Chest      (0x09, 0x00, "Ice Cavern Map Chest",                                  {Category::cIceCavern, Category::cVanillaMap,});
ItemLocation IceCavern_CompassChest                           = ItemLocation::Chest      (0x09, 0x01, "Ice Cavern Compass Chest",                              {Category::cIceCavern, Category::cVanillaCompass,});
ItemLocation IceCavern_IronBootsChest                         = ItemLocation::Chest      (0x09, 0x02, "Ice Cavern Iron Boots Chest",                           {Category::cIceCavern,});
ItemLocation IceCavern_FreestandingPoH                        = ItemLocation::Collectable(0x09, 0x01, "Ice Cavern Freestanding PoH",                           {Category::cIceCavern,});
//Ice Cavern MQ
ItemLocation IceCavern_MQ_IronBootsChest                      = ItemLocation::Chest      (0x09, 0x02, "Ice Cavern MQ Iron Boots Chest",                        {Category::cIceCavern,});
ItemLocation IceCavern_MQ_CompassChest                        = ItemLocation::Chest      (0x09, 0x00, "Ice Cavern MQ Compass Chest",                           {Category::cIceCavern, Category::cVanillaCompass,});
ItemLocation IceCavern_MQ_MapChest                            = ItemLocation::Chest      (0x09, 0x01, "Ice Cavern MQ Map Chest",                               {Category::cIceCavern, Category::cVanillaMap,});
ItemLocation IceCavern_MQ_FreestandingPoH                     = ItemLocation::Collectable(0x09, 0x01, "Ice Cavern MQ Freestanding PoH",                        {Category::cIceCavern,});

//Gerudo Training Ground Vanilla
ItemLocation GerudoTrainingGrounds_LobbyLeftChest             = ItemLocation::Chest      (0x0B, 0x13, "Gerudo Training Grounds Lobby Left Chest",              {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_LobbyRightChest            = ItemLocation::Chest      (0x0B, 0x07, "Gerudo Training Grounds Lobby Right Chest",             {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_StalfosChest               = ItemLocation::Chest      (0x0B, 0x00, "Gerudo Training Grounds Stalfos Chest",                 {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
ItemLocation GerudoTrainingGrounds_BeamosChest                = ItemLocation::Chest      (0x0B, 0x01, "Gerudo Training Grounds Beamos Chest",                  {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
ItemLocation GerudoTrainingGrounds_HiddenCeilingChest         = ItemLocation::Chest      (0x0B, 0x0B, "Gerudo Training Grounds Hidden Ceiling Chest",          {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
ItemLocation GerudoTrainingGrounds_MazePathFirstChest         = ItemLocation::Chest      (0x0B, 0x06, "Gerudo Training Grounds Maze Path First Chest",         {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MazePathSecondChest        = ItemLocation::Chest      (0x0B, 0x0A, "Gerudo Training Grounds Maze Path Second Chest",        {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MazePathThirdChest         = ItemLocation::Chest      (0x0B, 0x09, "Gerudo Training Grounds Maze Path Third Chest",         {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MazePathFinalChest         = ItemLocation::Chest      (0x0B, 0x0C, "Gerudo Training Grounds Maze Path Final Chest",         {Category::cGerudoTrainingGrounds, Category::cSongDungeonReward});
ItemLocation GerudoTrainingGrounds_MazeRightCentralChest      = ItemLocation::Chest      (0x0B, 0x05, "Gerudo Training Grounds Maze Right Central Chest",      {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MazeRightSideChest         = ItemLocation::Chest      (0x0B, 0x08, "Gerudo Training Grounds Maze Right Side Chest",         {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_UnderwaterSilverRupeeChest = ItemLocation::Chest      (0x0B, 0x0D, "Gerudo Training Grounds Underwater Silver Rupee Chest", {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
ItemLocation GerudoTrainingGrounds_HammerRoomClearChest       = ItemLocation::Chest      (0x0B, 0x12, "Gerudo Training Grounds Hammer Room Clear Chest",       {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_HammerRoomSwitchChest      = ItemLocation::Chest      (0x0B, 0x10, "Gerudo Training Grounds Hammer Room Switch Chest",      {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
ItemLocation GerudoTrainingGrounds_EyeStatueChest             = ItemLocation::Chest      (0x0B, 0x03, "Gerudo Training Grounds Eye Statue Chest",              {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
ItemLocation GerudoTrainingGrounds_NearScarecrowChest         = ItemLocation::Chest      (0x0B, 0x04, "Gerudo Training Grounds Near Scarecrow Chest",          {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
ItemLocation GerudoTrainingGrounds_BeforeHeavyBlockChest      = ItemLocation::Chest      (0x0B, 0x11, "Gerudo Training Grounds Before Heavy Block Chest",      {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_HeavyBlockFirstChest       = ItemLocation::Chest      (0x0B, 0x0F, "Gerudo Training Grounds Heavy Block First Chest",       {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_HeavyBlockSecondChest      = ItemLocation::Chest      (0x0B, 0x0E, "Gerudo Training Grounds Heavy Block Second Chest",      {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_HeavyBlockThirdChest       = ItemLocation::Chest      (0x0B, 0x14, "Gerudo Training Grounds Heavy Block Third Chest",       {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
ItemLocation GerudoTrainingGrounds_HeavyBlockFourthChest      = ItemLocation::Chest      (0x0B, 0x02, "Gerudo Training Grounds Heavy Block Fourth Chest",      {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_FreestandingKey            = ItemLocation::Collectable(0x0B, 0x01, "Gerudo Training Grounds Freestanding Key",              {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
//Gerudo Training Grounds MQ
ItemLocation GerudoTrainingGrounds_MQ_LobbyRightChest         = ItemLocation::Chest      (0x0B, 0x07, "Gerudo Training Grounds MQ Lobby Right Chest",          {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MQ_LobbyLeftChest          = ItemLocation::Chest      (0x0B, 0x13, "Gerudo Training Grounds MQ Lobby Left Chest",           {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MQ_FirstIronKnuckleChest   = ItemLocation::Chest      (0x0B, 0x00, "Gerudo Training Grounds MQ First Iron Knuckle Chest",   {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MQ_BeforeHeavyBlockChest   = ItemLocation::Chest      (0x0B, 0x11, "Gerudo Training Grounds MQ Before Heavy Block Chest",   {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MQ_EyeStatueChest          = ItemLocation::Chest      (0x0B, 0x03, "Gerudo Training Grounds MQ Eye Statue Chest",           {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MQ_FlameCircleChest        = ItemLocation::Chest      (0x0B, 0x0E, "Gerudo Training Grounds MQ Flame Circle Chest",         {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
ItemLocation GerudoTrainingGrounds_MQ_SecondIronKnuckleChest  = ItemLocation::Chest      (0x0B, 0x12, "Gerudo Training Grounds MQ Second Iron Knuckle Chest",  {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MQ_DinolfosChest           = ItemLocation::Chest      (0x0B, 0x01, "Gerudo Training Grounds MQ Dinolfos Chest",             {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
ItemLocation GerudoTrainingGrounds_MQ_IceArrowsChest          = ItemLocation::Chest      (0x0B, 0x04, "Gerudo Training Grounds MQ Ice Arrows Chest",           {Category::cGerudoTrainingGrounds, Category::cSongDungeonReward});
ItemLocation GerudoTrainingGrounds_MQ_MazeRightCentralChest   = ItemLocation::Chest      (0x0B, 0x05, "Gerudo Training Grounds MQ Maze Right Central Chest",   {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MQ_MazePathFirstChest      = ItemLocation::Chest      (0x0B, 0x06, "Gerudo Training Grounds MQ Maze Path First Chest",      {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MQ_MazeRightSideChest      = ItemLocation::Chest      (0x0B, 0x08, "Gerudo Training Grounds MQ Maze Right Side Chest",      {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MQ_MazePathThirdChest      = ItemLocation::Chest      (0x0B, 0x09, "Gerudo Training Grounds MQ Maze Path Third Chest",      {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MQ_MazePathSecondChest     = ItemLocation::Chest      (0x0B, 0x0A, "Gerudo Training Grounds MQ Maze Path Second Chest",     {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MQ_HiddenCeilingChest      = ItemLocation::Chest      (0x0B, 0x0B, "Gerudo Training Grounds MQ Hidden Ceiling Chest",       {Category::cGerudoTrainingGrounds,});
ItemLocation GerudoTrainingGrounds_MQ_UnderwaterSilverRupeeChest = ItemLocation::Chest   (0x0B, 0x0D, "Gerudo Training Grounds MQ Underwater Silver Rupee Chest", {Category::cGerudoTrainingGrounds, Category::cVanillaSmallKey});
ItemLocation GerudoTrainingGrounds_MQ_HeavyBlockChest         = ItemLocation::Chest      (0x0B, 0x02, "Gerudo Training Grounds MQ Heavy Block Chest",          {Category::cGerudoTrainingGrounds,});

//Ganons Castle Shared
ItemLocation GanonsCastle_BossKeyChest                        = ItemLocation::Chest      (0x0A, 0x0B, "Ganon's Castle Boss Key Chest",                         {Category::cGanonsCastle,});
//Ganons Castle Vanilla
ItemLocation GanonsCastle_ForestTrialChest                    = ItemLocation::Chest      (0x0D, 0x09, "Ganon's Castle Forest Trial Chest",                     {Category::cGanonsCastle,});
ItemLocation GanonsCastle_WaterTrialLeftChest                 = ItemLocation::Chest      (0x0D, 0x07, "Ganon's Castle Water Trial Left Chest",                 {Category::cGanonsCastle,});
ItemLocation GanonsCastle_WaterTrialRightChest                = ItemLocation::Chest      (0x0D, 0x06, "Ganon's Castle Water Trial Right Chest",                {Category::cGanonsCastle,});
ItemLocation GanonsCastle_ShadowTrialFrontChest               = ItemLocation::Chest      (0x0D, 0x08, "Ganon's Castle Shadow Trial Front Chest",               {Category::cGanonsCastle,});
ItemLocation GanonsCastle_ShadowTrialGoldenGauntletsChest     = ItemLocation::Chest      (0x0D, 0x05, "Ganon's Castle Shadow Trial Golden Gauntlets Chest",    {Category::cGanonsCastle,});
ItemLocation GanonsCastle_SpiritTrialCrystalSwitchChest       = ItemLocation::Chest      (0x0D, 0x12, "Ganon's Castle Spirit Trial Crystal Switch Chest",      {Category::cGanonsCastle,});
ItemLocation GanonsCastle_SpiritTrialInvisibleChest           = ItemLocation::Chest      (0x0D, 0x14, "Ganon's Castle Spirit Trial Invisible Chest",           {Category::cGanonsCastle,});
ItemLocation GanonsCastle_LightTrialFirstLeftChest            = ItemLocation::Chest      (0x0D, 0x0C, "Ganon's Castle Light Trial First Left Chest",           {Category::cGanonsCastle,});
ItemLocation GanonsCastle_LightTrialSecondLeftChest           = ItemLocation::Chest      (0x0D, 0x0B, "Ganon's Castle Light Trial Second Left Chest",          {Category::cGanonsCastle,});
ItemLocation GanonsCastle_LightTrialThirdLeftChest            = ItemLocation::Chest      (0x0D, 0x0D, "Ganon's Castle Light Trial Third Left Chest",           {Category::cGanonsCastle,});
ItemLocation GanonsCastle_LightTrialFirstRightChest           = ItemLocation::Chest      (0x0D, 0x0E, "Ganon's Castle Light Trial First Right Chest",          {Category::cGanonsCastle,});
ItemLocation GanonsCastle_LightTrialSecondRightChest          = ItemLocation::Chest      (0x0D, 0x0A, "Ganon's Castle Light Trial Second Right Chest",         {Category::cGanonsCastle,});
ItemLocation GanonsCastle_LightTrialThirdRightChest           = ItemLocation::Chest      (0x0D, 0x0F, "Ganon's Castle Light Trial Third Right Chest",          {Category::cGanonsCastle,});
ItemLocation GanonsCastle_LightTrialInvisibleEnemiesChest     = ItemLocation::Chest      (0x0D, 0x10, "Ganon's Castle Light Trial Invisible Enemies Chest",    {Category::cGanonsCastle, Category::cVanillaSmallKey});
ItemLocation GanonsCastle_LightTrialLullabyChest              = ItemLocation::Chest      (0x0D, 0x11, "Ganon's Castle Light Trial Lullaby Chest",              {Category::cGanonsCastle, Category::cVanillaSmallKey});
ItemLocation GanonsCastle_DekuScrubCenterLeft                 = ItemLocation::Base       (0x0D, 0x37, "Ganon's Castle Deku Scrub Center-Left",                 {Category::cGanonsCastle, Category::cDekuScrub,});
ItemLocation GanonsCastle_DekuScrubCenterRight                = ItemLocation::Base       (0x0D, 0x33, "Ganon's Castle Deku Scrub Center-Right",                {Category::cGanonsCastle, Category::cDekuScrub,});
ItemLocation GanonsCastle_DekuScrubRight                      = ItemLocation::Base       (0x0D, 0x39, "Ganon's Castle Deku Scrub Right",                       {Category::cGanonsCastle, Category::cDekuScrub,});
ItemLocation GanonsCastle_DekuScrubLeft                       = ItemLocation::Base       (0x0D, 0x3A, "Ganon's Castle Deku Scrub Left",                        {Category::cGanonsCastle, Category::cDekuScrub,});
//Ganons Castle MQ
ItemLocation GanonsCastle_MQ_WaterTrialChest                  = ItemLocation::Chest      (0x0D, 0x01, "Ganon's Castle MQ Water Trial Chest",                   {Category::cGanonsCastle,});
ItemLocation GanonsCastle_MQ_ForestTrialEyeSwitchChest        = ItemLocation::Chest      (0x0D, 0x02, "Ganon's Castle MQ Forest Trial Eye Switch Chest",       {Category::cGanonsCastle,});
ItemLocation GanonsCastle_MQ_ForestTrialFrozenEyeSwitchChest  = ItemLocation::Chest      (0x0D, 0x03, "Ganon's Castle MQ Forest Trial Frozen Eye Switch Chest",{Category::cGanonsCastle,});
ItemLocation GanonsCastle_MQ_LightTrialLullabyChest           = ItemLocation::Chest      (0x0D, 0x04, "Ganon's Castle MQ Light Trial Lullaby Chest",           {Category::cGanonsCastle,});
ItemLocation GanonsCastle_MQ_ShadowTrialBombFlowerChest       = ItemLocation::Chest      (0x0D, 0x00, "Ganon's Castle MQ Shadow Trial Bomb Flower Chest",      {Category::cGanonsCastle,});
ItemLocation GanonsCastle_MQ_ShadowTrialEyeSwitchChest        = ItemLocation::Chest      (0x0D, 0x05, "Ganon's Castle MQ Shadow Trial Eye Switch Chest",       {Category::cGanonsCastle,  Category::cVanillaSmallKey});
ItemLocation GanonsCastle_MQ_SpiritTrialGoldenGauntletsChest  = ItemLocation::Chest      (0x0D, 0x06, "Ganon's Castle MQ Spirit Trial Golden Gauntlets Chest", {Category::cGanonsCastle,});
ItemLocation GanonsCastle_MQ_SpiritTrialSunBackRightChest     = ItemLocation::Chest      (0x0D, 0x07, "Ganon's Castle MQ Spirit Trial Sun Back Right Chest",   {Category::cGanonsCastle,});
ItemLocation GanonsCastle_MQ_SpiritTrialSunBackLeftChest      = ItemLocation::Chest      (0x0D, 0x08, "Ganon's Castle MQ Spirit Trial Sun Back Left Chest",    {Category::cGanonsCastle,  Category::cVanillaSmallKey});
ItemLocation GanonsCastle_MQ_SpiritTrialSunFrontLeftChest     = ItemLocation::Chest      (0x0D, 0x09, "Ganon's Castle MQ Spirit Trial Sun Front Left Chest",   {Category::cGanonsCastle,});
ItemLocation GanonsCastle_MQ_SpiritTrialFirstChest            = ItemLocation::Chest      (0x0D, 0x0A, "Ganon's Castle MQ Spirit Trial First Chest",            {Category::cGanonsCastle,});
ItemLocation GanonsCastle_MQ_SpiritTrialInvisibleChest        = ItemLocation::Chest      (0x0D, 0x14, "Ganon's Castle MQ Spirit Trial Invisible Chest",        {Category::cGanonsCastle,});
ItemLocation GanonsCastle_MQ_ForestTrialFreestandingKey       = ItemLocation::Collectable(0x0D, 0x01, "Ganon's Castle MQ Forest Trial Freestanding Key",       {Category::cGanonsCastle,  Category::cVanillaSmallKey});
ItemLocation GanonsCastle_MQ_DekuScrubRight                   = ItemLocation::Base       (0x0D, 0x30, "Ganon's Castle MQ Deku Scrub Right",                    {Category::cGanonsCastle, Category::cDekuScrub,});
ItemLocation GanonsCastle_MQ_DekuScrubCenterLeft              = ItemLocation::Base       (0x0D, 0x37, "Ganon's Castle MQ Deku Scrub Center-Left",              {Category::cGanonsCastle, Category::cDekuScrub,});
ItemLocation GanonsCastle_MQ_DekuScrubCenter                  = ItemLocation::Base       (0x0D, 0x33, "Ganon's Castle MQ Deku Scrub Center",                   {Category::cGanonsCastle, Category::cDekuScrub,});
ItemLocation GanonsCastle_MQ_DekuScrubCenterRight             = ItemLocation::Base       (0x0D, 0x39, "Ganon's Castle MQ Deku Scrub Center-Right",             {Category::cGanonsCastle, Category::cDekuScrub,});
ItemLocation GanonsCastle_MQ_DekuScrubLeft                    = ItemLocation::Base       (0x0D, 0x3A, "Ganon's Castle MQ Deku Scrub Left",                     {Category::cGanonsCastle, Category::cDekuScrub,});

/*-------------------------------
   --- GOLD SKULLTULA TOKENS ---
  -------------------------------*/

//Dungeons
ItemLocation DekuTree_GS_BasementBackRoom                 = ItemLocation::GSToken(0x00, 0x01, "Deku Tree GS Basement Back Room",                  {Category::cDekuTree, Category::cSkulltula,});
ItemLocation DekuTree_GS_BasementGate                     = ItemLocation::GSToken(0x00, 0x02, "Deku Tree GS Basement Gate",                       {Category::cDekuTree, Category::cSkulltula,});
ItemLocation DekuTree_GS_BasementVines                    = ItemLocation::GSToken(0x00, 0x04, "Deku Tree GS Basement Vines",                      {Category::cDekuTree, Category::cSkulltula,});
ItemLocation DekuTree_GS_CompassRoom                      = ItemLocation::GSToken(0x00, 0x08, "Deku Tree GS Compass Room",                        {Category::cDekuTree, Category::cSkulltula,});

ItemLocation DekuTree_MQ_GS_Lobby                         = ItemLocation::GSToken(0x00, 0x02, "Deku Tree MQ GS Lobby",                            {Category::cDekuTree, Category::cSkulltula,});
ItemLocation DekuTree_MQ_GS_CompassRoom                   = ItemLocation::GSToken(0x00, 0x08, "Deku Tree MQ GS Compass Room",                     {Category::cDekuTree, Category::cSkulltula,});
ItemLocation DekuTree_MQ_GS_BasementGravesRoom            = ItemLocation::GSToken(0x00, 0x04, "Deku Tree MQ GS Basement Graves Room",             {Category::cDekuTree, Category::cSkulltula,});
ItemLocation DekuTree_MQ_GS_BasementBackRoom              = ItemLocation::GSToken(0x00, 0x01, "Deku Tree MQ GS Basement Back Room",               {Category::cDekuTree, Category::cSkulltula,});

ItemLocation DodongosCavern_GS_VinesAboveStairs           = ItemLocation::GSToken(0x01, 0x01, "Dodongos Cavern GS Vines Above Stairs",            {Category::cDodongosCavern, Category::cSkulltula,});
ItemLocation DodongosCavern_GS_Scarecrow                  = ItemLocation::GSToken(0x01, 0x02, "Dodongos Cavern GS Scarecrow",                     {Category::cDodongosCavern, Category::cSkulltula,});
ItemLocation DodongosCavern_GS_AlcoveAboveStairs          = ItemLocation::GSToken(0x01, 0x04, "Dodongos Cavern GS Alcove Above Stairs",           {Category::cDodongosCavern, Category::cSkulltula,});
ItemLocation DodongosCavern_GS_BackRoom                   = ItemLocation::GSToken(0x01, 0x08, "Dodongos Cavern GS Back Room",                     {Category::cDodongosCavern, Category::cSkulltula,});
ItemLocation DodongosCavern_GS_SideRoomNearLowerLizalfos  = ItemLocation::GSToken(0x01, 0x10, "Dodongos Cavern GS Side Room Near Lower Lizalfos", {Category::cDodongosCavern, Category::cSkulltula,});

ItemLocation DodongosCavern_MQ_GS_ScrubRoom               = ItemLocation::GSToken(0x01, 0x02, "Dodongos Cavern MQ GS Scrub Room",                 {Category::cDodongosCavern, Category::cSkulltula,});
ItemLocation DodongosCavern_MQ_GS_SongOfTimeBlockRoom     = ItemLocation::GSToken(0x01, 0x08, "Dodongos Cavern MQ GS Song of Time Block Room",    {Category::cDodongosCavern, Category::cSkulltula,});
ItemLocation DodongosCavern_MQ_GS_LizalfosRoom            = ItemLocation::GSToken(0x01, 0x04, "Dodongos Cavern MQ GS Lizalfos Room",              {Category::cDodongosCavern, Category::cSkulltula,});
ItemLocation DodongosCavern_MQ_GS_LarvaeRoom              = ItemLocation::GSToken(0x01, 0x10, "Dodongos Cavern MQ GS Larvae Room",                {Category::cDodongosCavern, Category::cSkulltula,});
ItemLocation DodongosCavern_MQ_GS_BackRoom                = ItemLocation::GSToken(0x01, 0x01, "Dodongos Cavern MQ GS Back Room",                  {Category::cDodongosCavern, Category::cSkulltula,});

ItemLocation JabuJabusBelly_GS_LobbyBasementLower         = ItemLocation::GSToken(0x02, 0x01, "Jabu Jabus Belly GS Lobby Basement Lower",         {Category::cJabuJabusBelly, Category::cSkulltula,});
ItemLocation JabuJabusBelly_GS_LobbyBasementUpper         = ItemLocation::GSToken(0x02, 0x02, "Jabu Jabus Belly GS Lobby Basement Upper",         {Category::cJabuJabusBelly, Category::cSkulltula,});
ItemLocation JabuJabusBelly_GS_NearBoss                   = ItemLocation::GSToken(0x02, 0x04, "Jabu Jabus Belly GS Near Boss",                    {Category::cJabuJabusBelly, Category::cSkulltula,});
ItemLocation JabuJabusBelly_GS_WaterSwitchRoom            = ItemLocation::GSToken(0x02, 0x08, "Jabu Jabus Belly GS Water Switch Room",            {Category::cJabuJabusBelly, Category::cSkulltula,});

ItemLocation JabuJabusBelly_MQ_GS_TailPasaranRoom         = ItemLocation::GSToken(0x02, 0x04, "Jabu Jabus Belly MQ GS Tail Parasan Room",         {Category::cJabuJabusBelly, Category::cSkulltula,});
ItemLocation JabuJabusBelly_MQ_GS_InvisibleEnemiesRoom    = ItemLocation::GSToken(0x02, 0x08, "Jabu Jabus Belly MQ GS Invisible Enemies Room",    {Category::cJabuJabusBelly, Category::cSkulltula,});
ItemLocation JabuJabusBelly_MQ_GS_BoomerangChestRoom      = ItemLocation::GSToken(0x02, 0x01, "Jabu Jabus Belly MQ GS Boomerang Chest Room",      {Category::cJabuJabusBelly, Category::cSkulltula,});
ItemLocation JabuJabusBelly_MQ_GS_NearBoss                = ItemLocation::GSToken(0x02, 0x02, "Jabu Jabus Belly MQ GS Near Boss",                 {Category::cJabuJabusBelly, Category::cSkulltula,});

ItemLocation ForestTemple_GS_RaisedIslandCourtyard        = ItemLocation::GSToken(0x03, 0x01, "Forest Temple GS Raised Island Courtyard",         {Category::cForestTemple, Category::cSkulltula,});
ItemLocation ForestTemple_GS_FirstRoom                    = ItemLocation::GSToken(0x03, 0x02, "Forest Temple GS First Room",                      {Category::cForestTemple, Category::cSkulltula,});
ItemLocation ForestTemple_GS_LevelIslandCourtyard         = ItemLocation::GSToken(0x03, 0x04, "Forest Temple GS Level Island Courtyard",          {Category::cForestTemple, Category::cSkulltula,});
ItemLocation ForestTemple_GS_Lobby                        = ItemLocation::GSToken(0x03, 0x08, "Forest Temple GS Lobby",                           {Category::cForestTemple, Category::cSkulltula,});
ItemLocation ForestTemple_GS_Basement                     = ItemLocation::GSToken(0x03, 0x10, "Forest Temple GS Basement",                        {Category::cForestTemple, Category::cSkulltula,});

ItemLocation ForestTemple_MQ_GS_FirstHallway              = ItemLocation::GSToken(0x03, 0x02, "Forest Temple MQ GS First Hallway",                {Category::cForestTemple, Category::cSkulltula,});
ItemLocation ForestTemple_MQ_GS_BlockPushRoom             = ItemLocation::GSToken(0x03, 0x10, "Forest Temple MQ GS Block Push Room",              {Category::cForestTemple, Category::cSkulltula,});
ItemLocation ForestTemple_MQ_GS_RaisedIslandCourtyard     = ItemLocation::GSToken(0x03, 0x01, "Forest Temple MQ GS Raised Island Courtyard",      {Category::cForestTemple, Category::cSkulltula,});
ItemLocation ForestTemple_MQ_GS_LevelIslandCourtyard      = ItemLocation::GSToken(0x03, 0x04, "Forest Temple MQ GS Level Island Courtyard",       {Category::cForestTemple, Category::cSkulltula,});
ItemLocation ForestTemple_MQ_GS_Well                      = ItemLocation::GSToken(0x03, 0x08, "Forest Temple MQ GS Well",                         {Category::cForestTemple, Category::cSkulltula,});

ItemLocation FireTemple_GS_SongOfTimeRoom                 = ItemLocation::GSToken(0x04, 0x01, "Fire Temple GS Song of Time Room",                 {Category::cFireTemple, Category::cSkulltula,});
ItemLocation FireTemple_GS_BossKeyLoop                    = ItemLocation::GSToken(0x04, 0x02, "Fire Temple GS Boss Key Loop",                     {Category::cFireTemple, Category::cSkulltula,});
ItemLocation FireTemple_GS_BoulderMaze                    = ItemLocation::GSToken(0x04, 0x04, "Fire Temple GS Boulder Maze",                      {Category::cFireTemple, Category::cSkulltula,});
ItemLocation FireTemple_GS_ScarecrowTop                   = ItemLocation::GSToken(0x04, 0x08, "Fire Temple GS Scarecrow Top",                     {Category::cFireTemple, Category::cSkulltula,});
ItemLocation FireTemple_GS_ScarecrowClimb                 = ItemLocation::GSToken(0x04, 0x10, "Fire Temple GS Scarecrow Climb",                   {Category::cFireTemple, Category::cSkulltula,});

ItemLocation FireTemple_MQ_GS_AboveFireWallMaze           = ItemLocation::GSToken(0x04, 0x02, "Fire Temple MQ GS Above Fire Wall Maze",           {Category::cFireTemple, Category::cSkulltula,});
ItemLocation FireTemple_MQ_GS_FireWallMazeCenter          = ItemLocation::GSToken(0x04, 0x08, "Fire Temple MQ GS Fire Wall Maze Center",          {Category::cFireTemple, Category::cSkulltula,});
ItemLocation FireTemple_MQ_GS_BigLavaRoomOpenDoor         = ItemLocation::GSToken(0x04, 0x01, "Fire Temple MQ GS Big Lava Room Open Door",        {Category::cFireTemple, Category::cSkulltula,});
ItemLocation FireTemple_MQ_GS_FireWallMazeSideRoom        = ItemLocation::GSToken(0x04, 0x10, "Fire Temple MQ GS Fire Wall Maze Side Room",       {Category::cFireTemple, Category::cSkulltula,});
ItemLocation FireTemple_MQ_GS_SkullOnFire                 = ItemLocation::GSToken(0x04, 0x04, "Fire Temple MQ GS Skull on Fire",                  {Category::cFireTemple, Category::cSkulltula,});

ItemLocation WaterTemple_GS_BehindGate                    = ItemLocation::GSToken(0x05, 0x01, "Water Temple GS Behind Gate",                      {Category::cWaterTemple, Category::cSkulltula,});
ItemLocation WaterTemple_GS_FallingPlatformRoom           = ItemLocation::GSToken(0x05, 0x02, "Water Temple GS Falling Platform Room",            {Category::cWaterTemple, Category::cSkulltula,});
ItemLocation WaterTemple_GS_CentralPillar                 = ItemLocation::GSToken(0x05, 0x04, "Water Temple GS Central Pillar",                   {Category::cWaterTemple, Category::cSkulltula,});
ItemLocation WaterTemple_GS_NearBossKeyChest              = ItemLocation::GSToken(0x05, 0x08, "Water Temple GS Near Boss Key Chest",              {Category::cWaterTemple, Category::cSkulltula,});
ItemLocation WaterTemple_GS_River                         = ItemLocation::GSToken(0x05, 0x10, "Water Temple GS River",                            {Category::cWaterTemple, Category::cSkulltula,});

ItemLocation WaterTemple_MQ_GS_BeforeUpperWaterSwitch     = ItemLocation::GSToken(0x05, 0x04, "Water Temple MQ GS Before Upper Water Switch",     {Category::cWaterTemple, Category::cSkulltula,});
ItemLocation WaterTemple_MQ_GS_FreestandingKeyArea        = ItemLocation::GSToken(0x05, 0x08, "Water Temple MQ GS Freestanding Key Area",         {Category::cWaterTemple, Category::cSkulltula,});
ItemLocation WaterTemple_MQ_GS_LizalfosHallway            = ItemLocation::GSToken(0x05, 0x01, "Water Temple MQ GS Lizalfos Hallway",              {Category::cWaterTemple, Category::cSkulltula,});
ItemLocation WaterTemple_MQ_GS_River                      = ItemLocation::GSToken(0x05, 0x02, "Water Temple MQ GS River",                         {Category::cWaterTemple, Category::cSkulltula,});
ItemLocation WaterTemple_MQ_GS_TripleWallTorch            = ItemLocation::GSToken(0x05, 0x10, "Water Temple MQ GS Triple Wall Torch",             {Category::cWaterTemple, Category::cSkulltula,});

ItemLocation SpiritTemple_GS_HallAfterSunBlockRoom        = ItemLocation::GSToken(0x06, 0x01, "Spirit Temple GS Hall After Sun Block Room",       {Category::cSpiritTemple, Category::cSkulltula});
ItemLocation SpiritTemple_GS_BoulderRoom                  = ItemLocation::GSToken(0x06, 0x02, "Spirit Temple GS Boulder Room",                    {Category::cSpiritTemple, Category::cSkulltula});
ItemLocation SpiritTemple_GS_Lobby                        = ItemLocation::GSToken(0x06, 0x04, "Spirit Temple GS Lobby",                           {Category::cSpiritTemple, Category::cSkulltula});
ItemLocation SpiritTemple_GS_SunOnFloorRoom               = ItemLocation::GSToken(0x06, 0x08, "Spirit Temple GS Sun on Floor Room",               {Category::cSpiritTemple, Category::cSkulltula});
ItemLocation SpiritTemple_GS_MetalFence                   = ItemLocation::GSToken(0x06, 0x10, "Spirit Temple GS Metal Fence",                     {Category::cSpiritTemple, Category::cSkulltula});

ItemLocation SpiritTemple_MQ_GS_SymphonyRoom              = ItemLocation::GSToken(0x06, 0x08, "Spirit Temple MQ GS Symphony Room",                {Category::cSpiritTemple, Category::cSkulltula});
ItemLocation SpiritTemple_MQ_GS_LeeverRoom                = ItemLocation::GSToken(0x06, 0x02, "Spirit Temple MQ GS Leever Room",                  {Category::cSpiritTemple, Category::cSkulltula});
ItemLocation SpiritTemple_MQ_GS_NineThronesRoomWest       = ItemLocation::GSToken(0x06, 0x04, "Spirit Temple MQ GS Nine Thrones Room West",       {Category::cSpiritTemple, Category::cSkulltula});
ItemLocation SpiritTemple_MQ_GS_NineThronesRoomNorth      = ItemLocation::GSToken(0x06, 0x10, "Spirit Temple MQ GS Nine Thrones Room North",      {Category::cSpiritTemple, Category::cSkulltula});
ItemLocation SpiritTemple_MQ_GS_SunBlockRoom              = ItemLocation::GSToken(0x06, 0x01, "Spirit Temple MQ GS Sun Block Room",               {Category::cSpiritTemple, Category::cSkulltula});

ItemLocation ShadowTemple_GS_SingleGiantPot               = ItemLocation::GSToken(0x07, 0x01, "Shadow Temple GS Single Giant Pot",                {Category::cShadowTemple, Category::cSkulltula,});
ItemLocation ShadowTemple_GS_FallingSpikesRoom            = ItemLocation::GSToken(0x07, 0x02, "Shadow Temple GS Falling Spikes Room",             {Category::cShadowTemple, Category::cSkulltula,});
ItemLocation ShadowTemple_GS_TripleGiantPot               = ItemLocation::GSToken(0x07, 0x04, "Shadow Temple GS Triple Giant Pot",                {Category::cShadowTemple, Category::cSkulltula,});
ItemLocation ShadowTemple_GS_LikeLikeRoom                 = ItemLocation::GSToken(0x07, 0x08, "Shadow Temple GS Like Like Room",                  {Category::cShadowTemple, Category::cSkulltula,});
ItemLocation ShadowTemple_GS_NearShip                     = ItemLocation::GSToken(0x07, 0x10, "Shadow Temple GS Near Ship",                       {Category::cShadowTemple, Category::cSkulltula,});

ItemLocation ShadowTemple_MQ_GS_FallingSpikesRoom         = ItemLocation::GSToken(0x07, 0x02, "Shadow Temple MQ GS Falling Spikes Room",          {Category::cShadowTemple, Category::cSkulltula,});
ItemLocation ShadowTemple_MQ_GS_WindHintRoom              = ItemLocation::GSToken(0x07, 0x01, "Shadow Temple MQ GS Wind Hint Room",               {Category::cShadowTemple, Category::cSkulltula,});
ItemLocation ShadowTemple_MQ_GS_AfterWind                 = ItemLocation::GSToken(0x07, 0x08, "Shadow Temple MQ GS After Wind",                   {Category::cShadowTemple, Category::cSkulltula,});
ItemLocation ShadowTemple_MQ_GS_AfterShip                 = ItemLocation::GSToken(0x07, 0x10, "Shadow Temple MQ GS After Ship",                   {Category::cShadowTemple, Category::cSkulltula,});
ItemLocation ShadowTemple_MQ_GS_NearBoss                  = ItemLocation::GSToken(0x07, 0x04, "Shadow Temple MQ GS Near Boss",                    {Category::cShadowTemple, Category::cSkulltula,});

ItemLocation BottomOfTheWell_GS_LikeLikeCage              = ItemLocation::GSToken(0x08, 0x01, "Bottom of the Well GS Like Like Cage",             {Category::cBottomOfTheWell, Category::cSkulltula,});
ItemLocation BottomOfTheWell_GS_EastInnerRoom             = ItemLocation::GSToken(0x08, 0x02, "Bottom of the Well GS East Inner Room",            {Category::cBottomOfTheWell, Category::cSkulltula,});
ItemLocation BottomOfTheWell_GS_WestInnerRoom             = ItemLocation::GSToken(0x08, 0x04, "Bottom of the Well GS West Inner Room",            {Category::cBottomOfTheWell, Category::cSkulltula,});

ItemLocation BottomOfTheWell_MQ_GS_Basement               = ItemLocation::GSToken(0x08, 0x01, "Bottom of the Well MQ GS Basement",                {Category::cBottomOfTheWell, Category::cSkulltula,});
ItemLocation BottomOfTheWell_MQ_GS_CoffinRoom             = ItemLocation::GSToken(0x08, 0x04, "Bottom of the Well MQ GS Coffin Room",             {Category::cBottomOfTheWell, Category::cSkulltula,});
ItemLocation BottomOfTheWell_MQ_GS_WestInnerRoom          = ItemLocation::GSToken(0x08, 0x02, "Bottom of the Well MQ GS West Inner Room",         {Category::cBottomOfTheWell, Category::cSkulltula,});

ItemLocation IceCavern_GS_PushBlockRoom                   = ItemLocation::GSToken(0x09, 0x01, "Ice Cavern GS Push Block Room",                    {Category::cIceCavern, Category::cSkulltula,});
ItemLocation IceCavern_GS_SpinningScytheRoom              = ItemLocation::GSToken(0x09, 0x02, "Ice Cavern GS Spinning Scythe Room",               {Category::cIceCavern, Category::cSkulltula,});
ItemLocation IceCavern_GS_HeartPieceRoom                  = ItemLocation::GSToken(0x09, 0x04, "Ice Cavern GS Heart Piece Room",                   {Category::cIceCavern, Category::cSkulltula,});

ItemLocation IceCavern_MQ_GS_Scarecrow                    = ItemLocation::GSToken(0x09, 0x01, "Ice Cavern MQ GS Scarecrow",                       {Category::cIceCavern, Category::cSkulltula,});
ItemLocation IceCavern_MQ_GS_IceBlock                     = ItemLocation::GSToken(0x09, 0x04, "Ice Cavern MQ GS Ice Block",                       {Category::cIceCavern, Category::cSkulltula,});
ItemLocation IceCavern_MQ_GS_RedIce                       = ItemLocation::GSToken(0x09, 0x02, "Ice Cavern MQ GS Red Ice",                         {Category::cIceCavern, Category::cSkulltula,});

//Overworld
ItemLocation KF_GS_BeanPatch                              = ItemLocation::GSToken(0x0C, 0x01, "KF GS Bean Patch",                                 {Category::cKokiriForest, Category::cSkulltula,});
ItemLocation KF_GS_KnowItAllHouse                         = ItemLocation::GSToken(0x0C, 0x02, "KF GS Know It All House",                          {Category::cKokiriForest, Category::cSkulltula,});
ItemLocation KF_GS_HouseOfTwins                           = ItemLocation::GSToken(0x0C, 0x04, "KF GS House of Twins",                             {Category::cKokiriForest, Category::cSkulltula,});

ItemLocation LW_GS_BeanPatchNearBridge                    = ItemLocation::GSToken(0x0D, 0x01, "LW GS Bean Patch Near Bridge",                     {Category::cLostWoods, Category::cSkulltula,});
ItemLocation LW_GS_BeanPatchNearTheater                   = ItemLocation::GSToken(0x0D, 0x02, "LW GS Bean Patch Near Theater",                    {Category::cLostWoods, Category::cSkulltula,});
ItemLocation LW_GS_AboveTheater                           = ItemLocation::GSToken(0x0D, 0x04, "LW GS Above Theater",                              {Category::cLostWoods, Category::cSkulltula,});
ItemLocation SFM_GS                                       = ItemLocation::GSToken(0x0D, 0x08, "SFM GS",                                           {Category::cSacredForestMeadow, Category::cSkulltula,});

ItemLocation HF_GS_CowGrotto                              = ItemLocation::GSToken(0x0A, 0x01, "HF GS Cow Grotto",                                 {Category::cHyruleField, Category::cSkulltula, Category::cGrotto});
ItemLocation HF_GS_NearKakGrotto                          = ItemLocation::GSToken(0x0A, 0x02, "HF GS Near Kak Grotto",                            {Category::cHyruleField, Category::cSkulltula, Category::cGrotto});

ItemLocation LH_GS_BeanPatch                              = ItemLocation::GSToken(0x12, 0x01, "LH GS Bean Patch",                                 {Category::cLakeHylia, Category::cSkulltula,});
ItemLocation LH_GS_SmallIsland                            = ItemLocation::GSToken(0x12, 0x02, "LH GS Small Island",                               {Category::cLakeHylia, Category::cSkulltula,});
ItemLocation LH_GS_LabWall                                = ItemLocation::GSToken(0x12, 0x04, "LH GS Lab Wall",                                   {Category::cLakeHylia, Category::cSkulltula,});
ItemLocation LH_GS_LabCrate                               = ItemLocation::GSToken(0x12, 0x08, "LH GS Lab Crate",                                  {Category::cLakeHylia, Category::cSkulltula,});
ItemLocation LH_GS_Tree                                   = ItemLocation::GSToken(0x12, 0x10, "LH GS Tree",                                       {Category::cLakeHylia, Category::cSkulltula,});

ItemLocation GV_GS_BeanPatch                              = ItemLocation::GSToken(0x13, 0x01, "GV GS Bean Patch",                                 {Category::cGerudoValley, Category::cSkulltula,});
ItemLocation GV_GS_SmallBridge                            = ItemLocation::GSToken(0x13, 0x02, "GV GS Small Bridge",                               {Category::cGerudoValley, Category::cSkulltula,});
ItemLocation GV_GS_Pillar                                 = ItemLocation::GSToken(0x13, 0x04, "GV GS Pillar",                                     {Category::cGerudoValley, Category::cSkulltula,});
ItemLocation GV_GS_BehindTent                             = ItemLocation::GSToken(0x13, 0x08, "GV GS Behind Tent",                                {Category::cGerudoValley, Category::cSkulltula,});

ItemLocation GF_GS_ArcheryRange                           = ItemLocation::GSToken(0x14, 0x01, "GF GS Archery Range",                              {Category::cGerudoFortress, Category::cSkulltula,});
ItemLocation GF_GS_TopFloor                               = ItemLocation::GSToken(0x14, 0x02, "GF GS Top Floor",                                  {Category::cGerudoFortress, Category::cSkulltula,});

ItemLocation HW_GS                                        = ItemLocation::GSToken(0x15, 0x02, "HW GS",                                            {Category::cHauntedWasteland, Category::cSkulltula,});
ItemLocation Colossus_GS_BeanPatch                        = ItemLocation::GSToken(0x15, 0x01, "Colossus GS Bean Patch",                           {Category::cDesertColossus, Category::cSkulltula,});
ItemLocation Colossus_GS_Hill                             = ItemLocation::GSToken(0x15, 0x04, "Colossus GS Hill",                                 {Category::cDesertColossus, Category::cSkulltula,});
ItemLocation Colossus_GS_Tree                             = ItemLocation::GSToken(0x15, 0x08, "Colossus GS Tree",                                 {Category::cDesertColossus, Category::cSkulltula,});

ItemLocation OGC_GS                                       = ItemLocation::GSToken(0x0E, 0x01, "OGC GS",                                           {Category::cOutsideGanonsCastle, Category::cSkulltula,});
ItemLocation HC_GS_StormsGrotto                           = ItemLocation::GSToken(0x0E, 0x02, "HC GS Storms Grotto",                              {Category::cHyruleCastle, Category::cSkulltula, Category::cGrotto});
ItemLocation HC_GS_Tree                                   = ItemLocation::GSToken(0x0E, 0x04, "HC GS Tree",                                       {Category::cHyruleCastle, Category::cSkulltula,});
ItemLocation MK_GS_GuardHouse                             = ItemLocation::GSToken(0x0E, 0x08, "Market GS Guard House",                            {Category::cInnerMarket, Category::cSkulltula,});

ItemLocation Kak_GS_HouseUnderConstruction                = ItemLocation::GSToken(0x10, 0x08, "Kak GS House Under Construction",                  {Category::cKakarikoVillage, Category::cSkulltula,});
ItemLocation Kak_GS_SkulltulaHouse                        = ItemLocation::GSToken(0x10, 0x10, "Kak GS Skulltula House",                           {Category::cKakarikoVillage, Category::cSkulltula,});
ItemLocation Kak_GS_GuardsHouse                           = ItemLocation::GSToken(0x10, 0x02, "Kak GS Guards House",                              {Category::cKakarikoVillage, Category::cSkulltula,});
ItemLocation Kak_GS_Tree                                  = ItemLocation::GSToken(0x10, 0x20, "Kak GS Tree",                                      {Category::cKakarikoVillage, Category::cSkulltula,});
ItemLocation Kak_GS_Watchtower                            = ItemLocation::GSToken(0x10, 0x04, "Kak GS Watchtower",                                {Category::cKakarikoVillage, Category::cSkulltula,});
ItemLocation Kak_GS_AboveImpasHouse                       = ItemLocation::GSToken(0x10, 0x40, "Kak GS Above Impas House",                         {Category::cKakarikoVillage, Category::cSkulltula,});

ItemLocation GY_GS_Wall                                   = ItemLocation::GSToken(0x10, 0x80, "Graveyard GS Wall",                                {Category::cGraveyard, Category::cSkulltula,});
ItemLocation GY_GS_BeanPatch                              = ItemLocation::GSToken(0x10, 0x01, "Graveyard GS Bean Patch",                          {Category::cGraveyard, Category::cSkulltula,});

ItemLocation DMC_GS_BeanPatch                             = ItemLocation::GSToken(0x0F, 0x01, "DMC GS Bean Patch",                                {Category::cDeathMountainCrater, Category::cSkulltula,});
ItemLocation DMC_GS_Crate                                 = ItemLocation::GSToken(0x0F, 0x80, "DMC GS Crate",                                     {Category::cDeathMountainCrater, Category::cSkulltula,});

ItemLocation DMT_GS_BeanPatch                             = ItemLocation::GSToken(0x0F, 0x02, "DMT GS Bean Patch",                                {Category::cDeathMountainTrail, Category::cSkulltula,});
ItemLocation DMT_GS_NearKak                               = ItemLocation::GSToken(0x0F, 0x04, "DMT GS Near Kak",                                  {Category::cDeathMountainTrail, Category::cSkulltula,});
ItemLocation DMT_GS_AboveDodongosCavern                   = ItemLocation::GSToken(0x0F, 0x08, "DMT GS Above Dodongos Cavern",                     {Category::cDeathMountainTrail, Category::cSkulltula,});
ItemLocation DMT_GS_FallingRocksPath                      = ItemLocation::GSToken(0x0F, 0x10, "DMT GS Falling Rocks Path",                        {Category::cDeathMountainTrail, Category::cSkulltula,});

ItemLocation GC_GS_CenterPlatform                         = ItemLocation::GSToken(0x0F, 0x20, "GC GS Center Platform",                            {Category::cGoronCity, Category::cSkulltula,});
ItemLocation GC_GS_BoulderMaze                            = ItemLocation::GSToken(0x0F, 0x40, "GC GS Boulder Maze",                               {Category::cGoronCity, Category::cSkulltula,});

ItemLocation ZR_GS_Ladder                                 = ItemLocation::GSToken(0x11, 0x01, "ZR GS Ladder",                                     {Category::cZorasRiver, Category::cSkulltula,});
ItemLocation ZR_GS_Tree                                   = ItemLocation::GSToken(0x11, 0x02, "ZR GS Tree",                                       {Category::cZorasRiver, Category::cSkulltula,});
ItemLocation ZR_GS_AboveBridge                            = ItemLocation::GSToken(0x11, 0x08, "ZR GS Above Bridge",                               {Category::cZorasRiver, Category::cSkulltula,});
ItemLocation ZR_GS_NearRaisedGrottos                      = ItemLocation::GSToken(0x11, 0x10, "ZR GS Near Raised Grottos",                        {Category::cZorasRiver, Category::cSkulltula,});

ItemLocation ZD_GS_FrozenWaterfall                        = ItemLocation::GSToken(0x11, 0x40, "ZD GS Frozen Waterfall",                           {Category::cZorasDomain, Category::cSkulltula,});
ItemLocation ZF_GS_AboveTheLog                            = ItemLocation::GSToken(0x11, 0x04, "ZF GS Above The Log",                              {Category::cZorasFountain, Category::cSkulltula,});
ItemLocation ZF_GS_HiddenCave                             = ItemLocation::GSToken(0x11, 0x20, "ZF GS Hidden Cave",                                {Category::cZorasFountain, Category::cSkulltula,});
ItemLocation ZF_GS_Tree                                   = ItemLocation::GSToken(0x11, 0x80, "ZF GS Tree",                                       {Category::cZorasFountain, Category::cSkulltula,});

ItemLocation LLR_GS_BackWall                              = ItemLocation::GSToken(0x0B, 0x01, "LLR GS Back Wall",                                 {Category::cLonLonRanch, Category::cSkulltula,});
ItemLocation LLR_GS_RainShed                              = ItemLocation::GSToken(0x0B, 0x02, "LLR GS Rain Shed",                                 {Category::cLonLonRanch, Category::cSkulltula,});
ItemLocation LLR_GS_HouseWindow                           = ItemLocation::GSToken(0x0B, 0x04, "LLR GS House Window",                              {Category::cLonLonRanch, Category::cSkulltula,});
ItemLocation LLR_GS_Tree                                  = ItemLocation::GSToken(0x0B, 0x08, "LLR GS Tree",                                      {Category::cLonLonRanch, Category::cSkulltula,});

/*-------------------------------
          --- BOSSES ---
  -------------------------------*/

ItemLocation LinksPocket                                  = ItemLocation::Reward (0xFF, 0xFF,                    "Link's Pocket",               {});
ItemLocation QueenGohma                                   = ItemLocation::Reward (0xFF, DUNGEON_DEKU_TREE,       "Queen Gohma",                 {});
ItemLocation KingDodongo                                  = ItemLocation::Reward (0xFF, DUNGEON_DODONGOS_CAVERN, "King Dodongo",                {});
ItemLocation Barinade                                     = ItemLocation::Reward (0xFF, DUNGEON_JABUJABUS_BELLY, "Barinade",                    {});
ItemLocation PhantomGanon                                 = ItemLocation::Reward (0xFF, DUNGEON_FOREST_TEMPLE,   "Phantom Ganon",               {});
ItemLocation Volvagia                                     = ItemLocation::Reward (0xFF, DUNGEON_FIRE_TEMPLE,     "Volvagia",                    {});
ItemLocation Morpha                                       = ItemLocation::Reward (0xFF, DUNGEON_WATER_TEMPLE,    "Morpha",                      {});
ItemLocation Twinrova                                     = ItemLocation::Reward (0xFF, DUNGEON_SPIRIT_TEMPLE,   "Twinrova",                    {});
ItemLocation BongoBongo                                   = ItemLocation::Reward (0xFF, DUNGEON_SHADOW_TEMPLE,   "Bongo Bongo",                 {});
ItemLocation Ganon                                        = ItemLocation::Reward (0xFF, 0xF0,                    "Ganon",                       {});

/*-------------------------------
      ---HEART CONTAINERS ---
  -------------------------------*/

ItemLocation DekuTree_QueenGohmaHeart                     = ItemLocation::Base   (0x11, 0x4F, "Deku Tree Queen Gohma Heart Container",          {Category::cDekuTree, Category::cBossHeart, Category::cSongDungeonReward});
ItemLocation DodongosCavern_KingDodongoHeart              = ItemLocation::Base   (0x12, 0x4F, "Dodongos Cavern King Dodongo Heart Container",   {Category::cDodongosCavern, Category::cBossHeart, Category::cSongDungeonReward});
ItemLocation JabuJabusBelly_BarinadeHeart                 = ItemLocation::Base   (0x13, 0x4F, "Jabu Jabus Belly Barinade Heart Container",      {Category::cJabuJabusBelly, Category::cBossHeart, Category::cSongDungeonReward});
ItemLocation ForestTemple_PhantomGanonHeart               = ItemLocation::Base   (0x14, 0x4F, "Forest Temple Phantom Ganon Heart Container",    {Category::cForestTemple, Category::cBossHeart, Category::cSongDungeonReward});
ItemLocation FireTemple_VolvagiaHeart                     = ItemLocation::Base   (0x15, 0x4F, "Fire Temple Volvagia Heart Container",           {Category::cFireTemple, Category::cBossHeart, Category::cSongDungeonReward});
ItemLocation WaterTemple_MorphaHeart                      = ItemLocation::Base   (0x16, 0x4F, "Water Temple Morpha Heart Container",            {Category::cWaterTemple, Category::cBossHeart, Category::cSongDungeonReward});
ItemLocation SpiritTemple_TwinrovaHeart                   = ItemLocation::Base   (0x17, 0x4F, "Spirit Temple Twinrova Heart Container",         {Category::cSpiritTemple, Category::cBossHeart, Category::cSongDungeonReward});
ItemLocation ShadowTemple_BongoBongoHeart                 = ItemLocation::Base   (0x18, 0x4F, "Shadow Temple Bongo Bongo Heart Container",      {Category::cShadowTemple, Category::cBossHeart, Category::cSongDungeonReward});

/*-------------------------------
        --- CUTSCENES ---
  -------------------------------*/

ItemLocation ToT_LightArrowCutscene                       = ItemLocation::Delayed(0xFF, 0x01, "ToT Light Arrow Cutscene",                       {Category::cTempleOfTime, Category::cMarket});
ItemLocation LW_GiftFromSaria                             = ItemLocation::Delayed(0xFF, 0x02, "LW Gift From Saria",                             {Category::cLostWoods, Category::cForest});
ItemLocation ZF_GreatFairyReward                          = ItemLocation::Delayed(0xFF, 0x10, "ZF Great Fairy Reward",                          {Category::cZorasFountain, Category::cFairies});
ItemLocation HC_GreatFairyReward                          = ItemLocation::Delayed(0xFF, 0x11, "HC Great Fairy Reward",                          {Category::cHyruleCastle, Category::cMarket, Category::cFairies});
ItemLocation Colossus_GreatFairyReward                    = ItemLocation::Delayed(0xFF, 0x12, "Colossus Great Fairy Reward",                    {Category::cDesertColossus, Category::cFairies});
ItemLocation DMT_GreatFairyReward                         = ItemLocation::Delayed(0xFF, 0x13, "DMT Great Fairy Reward",                         {Category::cDeathMountainTrail, Category::cDeathMountain, Category::cFairies});
ItemLocation DMC_GreatFairyReward                         = ItemLocation::Delayed(0xFF, 0x14, "DMC Great Fairy Reward",                         {Category::cDeathMountainCrater, Category::cDeathMountain, Category::cFairies});
ItemLocation OGC_GreatFairyReward                         = ItemLocation::Delayed(0xFF, 0x15, "OGC Great Fairy Reward",                         {Category::cOutsideGanonsCastle, Category::cMarket, Category::cFairies});

ItemLocation SheikInForest                                = ItemLocation::Delayed(0xFF, 0x20, "Sheik in Forest",                                {Category::cSacredForestMeadow, Category::cForest, Category::cSong,});
ItemLocation SheikInCrater                                = ItemLocation::Delayed(0xFF, 0x21, "Sheik in Crater",                                {Category::cDeathMountainCrater, Category::cDeathMountain, Category::cSong,});
ItemLocation SheikInIceCavern                             = ItemLocation::Delayed(0xFF, 0x22, "Sheik in Ice Cavern",                            {Category::cIceCavern, Category::cSong, Category::cSongDungeonReward});
ItemLocation SheikAtColossus                              = ItemLocation::Delayed(0xFF, 0x23, "Sheik at Colossus",                              {Category::cDesertColossus, Category::cSong,});
ItemLocation SheikInKakariko                              = ItemLocation::Delayed(0xFF, 0x24, "Sheik in Kakariko",                              {Category::cKakarikoVillage, Category::cKakariko, Category::cSong,});
ItemLocation SheikAtTemple                                = ItemLocation::Delayed(0xFF, 0x25, "Sheik at Temple",                                {Category::cTempleOfTime, Category::cMarket, Category::cSong,});
ItemLocation SongFromImpa                                 = ItemLocation::Delayed(0xFF, 0x26, "Song from Impa",                                 {Category::cHyruleCastle, Category::cMarket, Category::cSong, Category::cSongDungeonReward});
ItemLocation SongFromMalon                                = ItemLocation::Delayed(0xFF, 0x27, "Song from Malon",                                {Category::cLonLonRanch, Category::cSong,});
ItemLocation SongFromSaria                                = ItemLocation::Delayed(0xFF, 0x28, "Song from Saria",                                {Category::cSacredForestMeadow, Category::cForest, Category::cSong,});
ItemLocation SongFromComposersGrave                       = ItemLocation::Delayed(0xFF, 0x29, "Song from Composers Grave",                      {Category::cGraveyard, Category::cKakariko, Category::cSong,});
ItemLocation SongFromOcarinaOfTime                        = ItemLocation::Delayed(0xFF, 0x2A, "Song from Ocarina of Time",                      {Category::cHyruleField, Category::cSong, Category::cNeedSpiritualStones,});
ItemLocation SongFromWindmill                             = ItemLocation::Delayed(0xFF, 0x2B, "Song from Windmill",                             {Category::cKakarikoVillage, Category::cKakariko, Category::cSong,});

/*-------------------------------
           --- COWS ---
  -------------------------------*/

ItemLocation KF_LinksHouseCow                             = ItemLocation::Base   (0x34, 0x15, "KF Links House Cow",                             {Category::cForest, Category::cCow, Category::cMinigame});
ItemLocation HF_CowGrottoCow                              = ItemLocation::Base   (0x3E, 0x16, "HF Cow Grotto Cow",                              {Category::cHyruleField, Category::cCow, Category::cGrotto});
ItemLocation LLR_StablesLeftCow                           = ItemLocation::Base   (0x36, 0x16, "LLR Stables Left Cow",                           {Category::cLonLonRanch, Category::cCow});
ItemLocation LLR_StablesRightCow                          = ItemLocation::Base   (0x36, 0x15, "LLR Stables Right Cow",                          {Category::cLonLonRanch, Category::cCow});
ItemLocation LLR_TowerLeftCow                             = ItemLocation::Base   (0x4C, 0x16, "LLR Tower Left Cow",                             {Category::cLonLonRanch, Category::cCow});
ItemLocation LLR_TowerRightCow                            = ItemLocation::Base   (0x4C, 0x15, "LLR Tower Right Cow",                            {Category::cLonLonRanch, Category::cCow});
ItemLocation Kak_ImpasHouseCow                            = ItemLocation::Base   (0x37, 0x15, "Kak Impas House Cow",                            {Category::cKakarikoVillage, Category::cKakariko, Category::cCow});
ItemLocation DMT_CowGrottoCow                             = ItemLocation::Base   (0x3E, 0x15, "DMT Cow Grotto Cow",                             {Category::cDeathMountainTrail, Category::cDeathMountain, Category::cCow, Category::cGrotto});
ItemLocation GV_Cow                                       = ItemLocation::Base   (0x5A, 0x15, "GV Cow",                                         {Category::cGerudoValley, Category::cGerudo, Category::cCow});
ItemLocation JabuJabusBelly_MQ_Cow                        = ItemLocation::Base   (0x02, 0x15, "Jabu Jabus Belly MQ Cow",                        {Category::cJabuJabusBelly, Category::cCow});

/*-------------------------------
          --- SHOPS ---
  8     6               2     4

  7     5               1     3
  -------------------------------*/

ItemLocation KF_ShopItem1                                 = ItemLocation::Base(0x2D, 0x30, "KF Shop Item 1",                                   {Category::cKokiriForest, Category::cForest, Category::cShop});
ItemLocation KF_ShopItem2                                 = ItemLocation::Base(0x2D, 0x31, "KF Shop Item 2",                                   {Category::cKokiriForest, Category::cForest, Category::cShop});
ItemLocation KF_ShopItem3                                 = ItemLocation::Base(0x2D, 0x32, "KF Shop Item 3",                                   {Category::cKokiriForest, Category::cForest, Category::cShop});
ItemLocation KF_ShopItem4                                 = ItemLocation::Base(0x2D, 0x33, "KF Shop Item 4",                                   {Category::cKokiriForest, Category::cForest, Category::cShop});
ItemLocation KF_ShopItem5                                 = ItemLocation::Base(0x2D, 0x34, "KF Shop Item 5",                                   {Category::cKokiriForest, Category::cForest, Category::cShop});
ItemLocation KF_ShopItem6                                 = ItemLocation::Base(0x2D, 0x35, "KF Shop Item 6",                                   {Category::cKokiriForest, Category::cForest, Category::cShop});
ItemLocation KF_ShopItem7                                 = ItemLocation::Base(0x2D, 0x36, "KF Shop Item 7",                                   {Category::cKokiriForest, Category::cForest, Category::cShop});
ItemLocation KF_ShopItem8                                 = ItemLocation::Base(0x2D, 0x37, "KF Shop Item 8",                                   {Category::cKokiriForest, Category::cForest, Category::cShop});

ItemLocation Kak_PotionShopItem1                          = ItemLocation::Base(0x30, 0x30, "Kak Potion Shop Item 1",                           {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_PotionShopItem2                          = ItemLocation::Base(0x30, 0x31, "Kak Potion Shop Item 2",                           {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_PotionShopItem3                          = ItemLocation::Base(0x30, 0x32, "Kak Potion Shop Item 3",                           {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_PotionShopItem4                          = ItemLocation::Base(0x30, 0x33, "Kak Potion Shop Item 4",                           {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_PotionShopItem5                          = ItemLocation::Base(0x30, 0x34, "Kak Potion Shop Item 5",                           {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_PotionShopItem6                          = ItemLocation::Base(0x30, 0x35, "Kak Potion Shop Item 6",                           {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_PotionShopItem7                          = ItemLocation::Base(0x30, 0x36, "Kak Potion Shop Item 7",                           {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_PotionShopItem8                          = ItemLocation::Base(0x30, 0x37, "Kak Potion Shop Item 8",                           {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});

ItemLocation MK_BombchuShopItem1                          = ItemLocation::Base(0x32, 0x30, "MK Bombchu Shop Item 1",                           {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BombchuShopItem2                          = ItemLocation::Base(0x32, 0x31, "MK Bombchu Shop Item 2",                           {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BombchuShopItem3                          = ItemLocation::Base(0x32, 0x32, "MK Bombchu Shop Item 3",                           {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BombchuShopItem4                          = ItemLocation::Base(0x32, 0x33, "MK Bombchu Shop Item 4",                           {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BombchuShopItem5                          = ItemLocation::Base(0x32, 0x34, "MK Bombchu Shop Item 5",                           {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BombchuShopItem6                          = ItemLocation::Base(0x32, 0x35, "MK Bombchu Shop Item 6",                           {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BombchuShopItem7                          = ItemLocation::Base(0x32, 0x36, "MK Bombchu Shop Item 7",                           {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BombchuShopItem8                          = ItemLocation::Base(0x32, 0x37, "MK Bombchu Shop Item 8",                           {Category::cInnerMarket, Category::cMarket, Category::cShop});

ItemLocation MK_PotionShopItem1                           = ItemLocation::Base(0x31, 0x30, "MK Potion Shop Item 1",                            {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_PotionShopItem2                           = ItemLocation::Base(0x31, 0x31, "MK Potion Shop Item 2",                            {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_PotionShopItem3                           = ItemLocation::Base(0x31, 0x32, "MK Potion Shop Item 3",                            {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_PotionShopItem4                           = ItemLocation::Base(0x31, 0x33, "MK Potion Shop Item 4",                            {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_PotionShopItem5                           = ItemLocation::Base(0x31, 0x34, "MK Potion Shop Item 5",                            {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_PotionShopItem6                           = ItemLocation::Base(0x31, 0x35, "MK Potion Shop Item 6",                            {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_PotionShopItem7                           = ItemLocation::Base(0x31, 0x36, "MK Potion Shop Item 7",                            {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_PotionShopItem8                           = ItemLocation::Base(0x31, 0x37, "MK Potion Shop Item 8",                            {Category::cInnerMarket, Category::cMarket, Category::cShop});

ItemLocation MK_BazaarItem1                               = ItemLocation::Base(0x2C, 0x30, "MK Bazaar Item 1",                                 {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BazaarItem2                               = ItemLocation::Base(0x2C, 0x31, "MK Bazaar Item 2",                                 {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BazaarItem3                               = ItemLocation::Base(0x2C, 0x32, "MK Bazaar Item 3",                                 {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BazaarItem4                               = ItemLocation::Base(0x2C, 0x33, "MK Bazaar Item 4",                                 {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BazaarItem5                               = ItemLocation::Base(0x2C, 0x34, "MK Bazaar Item 5",                                 {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BazaarItem6                               = ItemLocation::Base(0x2C, 0x35, "MK Bazaar Item 6",                                 {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BazaarItem7                               = ItemLocation::Base(0x2C, 0x36, "MK Bazaar Item 7",                                 {Category::cInnerMarket, Category::cMarket, Category::cShop});
ItemLocation MK_BazaarItem8                               = ItemLocation::Base(0x2C, 0x37, "MK Bazaar Item 8",                                 {Category::cInnerMarket, Category::cMarket, Category::cShop});

ItemLocation Kak_BazaarItem1                              = ItemLocation::Base(0x2C, 0x38, "Kak Bazaar Item 1",                                {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_BazaarItem2                              = ItemLocation::Base(0x2C, 0x39, "Kak Bazaar Item 2",                                {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_BazaarItem3                              = ItemLocation::Base(0x2C, 0x3A, "Kak Bazaar Item 3",                                {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_BazaarItem4                              = ItemLocation::Base(0x2C, 0x3B, "Kak Bazaar Item 4",                                {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_BazaarItem5                              = ItemLocation::Base(0x2C, 0x3D, "Kak Bazaar Item 5",                                {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_BazaarItem6                              = ItemLocation::Base(0x2C, 0x3E, "Kak Bazaar Item 6",                                {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_BazaarItem7                              = ItemLocation::Base(0x2C, 0x3F, "Kak Bazaar Item 7",                                {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});
ItemLocation Kak_BazaarItem8                              = ItemLocation::Base(0x2C, 0x40, "Kak Bazaar Item 8",                                {Category::cKakarikoVillage, Category::cKakariko, Category::cShop});

ItemLocation ZD_ShopItem1                                 = ItemLocation::Base(0x2F, 0x30, "ZD Shop Item 1",                                   {Category::cZorasDomain, Category::cShop});
ItemLocation ZD_ShopItem2                                 = ItemLocation::Base(0x2F, 0x31, "ZD Shop Item 2",                                   {Category::cZorasDomain, Category::cShop});
ItemLocation ZD_ShopItem3                                 = ItemLocation::Base(0x2F, 0x32, "ZD Shop Item 3",                                   {Category::cZorasDomain, Category::cShop});
ItemLocation ZD_ShopItem4                                 = ItemLocation::Base(0x2F, 0x33, "ZD Shop Item 4",                                   {Category::cZorasDomain, Category::cShop});
ItemLocation ZD_ShopItem5                                 = ItemLocation::Base(0x2F, 0x34, "ZD Shop Item 5",                                   {Category::cZorasDomain, Category::cShop});
ItemLocation ZD_ShopItem6                                 = ItemLocation::Base(0x2F, 0x35, "ZD Shop Item 6",                                   {Category::cZorasDomain, Category::cShop});
ItemLocation ZD_ShopItem7                                 = ItemLocation::Base(0x2F, 0x36, "ZD Shop Item 7",                                   {Category::cZorasDomain, Category::cShop});
ItemLocation ZD_ShopItem8                                 = ItemLocation::Base(0x2F, 0x37, "ZD Shop Item 8",                                   {Category::cZorasDomain, Category::cShop});

ItemLocation GC_ShopItem1                                 = ItemLocation::Base(0x2E, 0x30, "GC Shop Item 1",                                   {Category::cGoronCity, Category::cShop});
ItemLocation GC_ShopItem2                                 = ItemLocation::Base(0x2E, 0x31, "GC Shop Item 2",                                   {Category::cGoronCity, Category::cShop});
ItemLocation GC_ShopItem3                                 = ItemLocation::Base(0x2E, 0x32, "GC Shop Item 3",                                   {Category::cGoronCity, Category::cShop});
ItemLocation GC_ShopItem4                                 = ItemLocation::Base(0x2E, 0x33, "GC Shop Item 4",                                   {Category::cGoronCity, Category::cShop});
ItemLocation GC_ShopItem5                                 = ItemLocation::Base(0x2E, 0x34, "GC Shop Item 5",                                   {Category::cGoronCity, Category::cShop});
ItemLocation GC_ShopItem6                                 = ItemLocation::Base(0x2E, 0x35, "GC Shop Item 6",                                   {Category::cGoronCity, Category::cShop});
ItemLocation GC_ShopItem7                                 = ItemLocation::Base(0x2E, 0x36, "GC Shop Item 7",                                   {Category::cGoronCity, Category::cShop});
ItemLocation GC_ShopItem8                                 = ItemLocation::Base(0x2E, 0x37, "GC Shop Item 8",                                   {Category::cGoronCity, Category::cShop});

const std::vector<ItemLocation*> DT_Vanilla = {
  &DekuTree_MapChest,
  &DekuTree_CompassChest,
  &DekuTree_CompassRoomSideChest,
  &DekuTree_BasementChest,
  &DekuTree_SlingshotChest,
  &DekuTree_SlingshotRoomSideChest,
  &DekuTree_GS_BasementBackRoom,
  &DekuTree_GS_BasementGate,
  &DekuTree_GS_BasementVines,
  &DekuTree_GS_CompassRoom,
};
const std::vector<ItemLocation*> DT_MQ = {
  &DekuTree_MQ_MapChest,
  &DekuTree_MQ_CompassChest,
  &DekuTree_MQ_SlingshotChest,
  &DekuTree_MQ_SlingshotRoomBackChest,
  &DekuTree_MQ_BasementChest,
  &DekuTree_MQ_BeforeSpinningLogChest,
  &DekuTree_MQ_AfterSpinningLowChest,
  &DekuTree_MQ_DekuScrub,
  &DekuTree_MQ_GS_Lobby,
  &DekuTree_MQ_GS_CompassRoom,
  &DekuTree_MQ_GS_BasementGravesRoom,
  &DekuTree_MQ_GS_BasementBackRoom,
};
const std::vector<ItemLocation*> DC_Vanilla = {
  &DodongosCavern_MapChest,
  &DodongosCavern_CompassChest,
  &DodongosCavern_BombFlowerPlatformChest,
  &DodongosCavern_BombBagChest,
  &DodongosCavern_EndOfBridgeChest,
  &DodongosCavern_DekuScrubLobby,
  &DodongosCavern_DekuScrubSideRoomNearDodongos,
  &DodongosCavern_DekuScrubNearBombBagLeft,
  &DodongosCavern_DekuScrubNearBombBagRight,
  &DodongosCavern_GS_VinesAboveStairs,
  &DodongosCavern_GS_Scarecrow,
  &DodongosCavern_GS_AlcoveAboveStairs,
  &DodongosCavern_GS_BackRoom,
  &DodongosCavern_GS_SideRoomNearLowerLizalfos,
};
const std::vector<ItemLocation*> DC_MQ = {
  &DodongosCavern_MQ_MapChest,
  &DodongosCavern_MQ_BombBagChest,
  &DodongosCavern_MQ_CompassChest,
  &DodongosCavern_MQ_LarvaeRoomChest,
  &DodongosCavern_MQ_TorchPuzzleRoomChest,
  &DodongosCavern_MQ_UnderGraveChest,
  &DodongosCavern_MQ_DekuScrubLobbyRear,
  &DodongosCavern_MQ_DekuScrubLobbyFront,
  &DodongosCavern_MQ_DekuScrubStaircase,
  &DodongosCavern_MQ_DekuScrubSideRoomNearLowerLizalfos,
  &DodongosCavern_MQ_GS_ScrubRoom,
  &DodongosCavern_MQ_GS_SongOfTimeBlockRoom,
  &DodongosCavern_MQ_GS_LizalfosRoom,
  &DodongosCavern_MQ_GS_LarvaeRoom,
  &DodongosCavern_MQ_GS_BackRoom,
};
const std::vector<ItemLocation*> Jabu_Vanilla = {
  &JabuJabusBelly_MapChest,
  &JabuJabusBelly_CompassChest,
  &JabuJabusBelly_BoomerangChest,
  &JabuJabusBelly_DekuScrub,
  &JabuJabusBelly_GS_LobbyBasementLower,
  &JabuJabusBelly_GS_LobbyBasementUpper,
  &JabuJabusBelly_GS_NearBoss,
  &JabuJabusBelly_GS_WaterSwitchRoom,
};
const std::vector<ItemLocation*> Jabu_MQ = {
  &JabuJabusBelly_MQ_FirstRoomSideChest,
  &JabuJabusBelly_MQ_MapChest,
  &JabuJabusBelly_MQ_SecondRoomLowerChest,
  &JabuJabusBelly_MQ_CompassChest,
  &JabuJabusBelly_MQ_SecondRoomUpperChest,
  &JabuJabusBelly_MQ_BasementNearSwitchesChest,
  &JabuJabusBelly_MQ_BasementNearVinesChest,
  &JabuJabusBelly_MQ_NearBossChest,
  &JabuJabusBelly_MQ_FallingLikeLikeRoomChest,
  &JabuJabusBelly_MQ_BoomerangRoomSmallChest,
  &JabuJabusBelly_MQ_BoomerangChest,
  &JabuJabusBelly_MQ_GS_TailPasaranRoom,
  &JabuJabusBelly_MQ_GS_InvisibleEnemiesRoom,
  &JabuJabusBelly_MQ_GS_BoomerangChestRoom,
  &JabuJabusBelly_MQ_GS_NearBoss,
};
const std::vector<ItemLocation*> FoT_Vanilla = {
  &ForestTemple_FirstRoomChest,
  &ForestTemple_FirstStalfosChest,
  &ForestTemple_RaisedIslandCourtyardChest,
  &ForestTemple_MapChest,
  &ForestTemple_WellChest,
  &ForestTemple_FallingCeilingRoomChest,
  &ForestTemple_EyeSwitchChest,
  &ForestTemple_BossKeyChest,
  &ForestTemple_FloormasterChest,
  &ForestTemple_BowChest,
  &ForestTemple_RedPoeChest,
  &ForestTemple_BluePoeChest,
  &ForestTemple_BasementChest,
  &ForestTemple_GS_RaisedIslandCourtyard,
  &ForestTemple_GS_FirstRoom,
  &ForestTemple_GS_LevelIslandCourtyard,
  &ForestTemple_GS_Lobby,
  &ForestTemple_GS_Basement,
};
const std::vector<ItemLocation*> FoT_MQ = {
  &ForestTemple_MQ_FirstRoomChest,
  &ForestTemple_MQ_WolfosChest,
  &ForestTemple_MQ_BowChest,
  &ForestTemple_MQ_RaisedIslandCourtyardLowerChest,
  &ForestTemple_MQ_RaisedIslandCourtyardUpperChest,
  &ForestTemple_MQ_WellChest,
  &ForestTemple_MQ_MapChest,
  &ForestTemple_MQ_CompassChest,
  &ForestTemple_MQ_FallingCeilingRoomChest,
  &ForestTemple_MQ_BasementChest,
  &ForestTemple_MQ_RedeadChest,
  &ForestTemple_MQ_BossKeyChest,
  &ForestTemple_MQ_GS_FirstHallway,
  &ForestTemple_MQ_GS_BlockPushRoom,
  &ForestTemple_MQ_GS_RaisedIslandCourtyard,
  &ForestTemple_MQ_GS_LevelIslandCourtyard,
  &ForestTemple_MQ_GS_Well,
};
const std::vector<ItemLocation*> FiT_Vanilla = {
  &FireTemple_NearBossChest,
  &FireTemple_FlareDancerChest,
  &FireTemple_BossKeyChest,
  &FireTemple_BigLavaRoomBlockedDoorChest,
  &FireTemple_BigLavaRoomLowerOpenDoorChest,
  &FireTemple_BoulderMazeLowerChest,
  &FireTemple_BoulderMazeUpperChest,
  &FireTemple_BoulderMazeSideRoomChest,
  &FireTemple_BoulderMazeShortcutChest,
  &FireTemple_ScarecrowChest,
  &FireTemple_MapChest,
  &FireTemple_CompassChest,
  &FireTemple_HighestGoronChest,
  &FireTemple_MegatonHammerChest,
  &FireTemple_GS_SongOfTimeRoom,
  &FireTemple_GS_BossKeyLoop,
  &FireTemple_GS_BoulderMaze,
  &FireTemple_GS_ScarecrowTop,
  &FireTemple_GS_ScarecrowClimb,
};
const std::vector<ItemLocation*> FiT_MQ = {
  &FireTemple_MQ_NearBossChest,
  &FireTemple_MQ_MegatonHammerChest,
  &FireTemple_MQ_CompassChest,
  &FireTemple_MQ_LizalfosMazeLowerChest,
  &FireTemple_MQ_LizalfosMazeUpperChest,
  &FireTemple_MQ_ChestOnFire,
  &FireTemple_MQ_MapRoomSideChest,
  &FireTemple_MQ_MapChest,
  &FireTemple_MQ_BossKeyChest,
  &FireTemple_MQ_BigLavaRoomBlockedDoorChest,
  &FireTemple_MQ_LizalfosMazeSideRoomChest,
  &FireTemple_MQ_FreestandingKey,
  &FireTemple_MQ_GS_AboveFireWallMaze,
  &FireTemple_MQ_GS_FireWallMazeCenter,
  &FireTemple_MQ_GS_BigLavaRoomOpenDoor,
  &FireTemple_MQ_GS_FireWallMazeSideRoom,
  &FireTemple_MQ_GS_SkullOnFire,
};
const std::vector<ItemLocation*> WaT_Vanilla = {
  &WaterTemple_MapChest,
  &WaterTemple_CompassChest,
  &WaterTemple_TorchesChest,
  &WaterTemple_DragonChest,
  &WaterTemple_CentralBowTargetChest,
  &WaterTemple_CentralPillarChest,
  &WaterTemple_CrackedWallChest,
  &WaterTemple_BossKeyChest,
  &WaterTemple_LongshotChest,
  &WaterTemple_RiverChest,
  &WaterTemple_GS_BehindGate,
  &WaterTemple_GS_FallingPlatformRoom,
  &WaterTemple_GS_CentralPillar,
  &WaterTemple_GS_NearBossKeyChest,
  &WaterTemple_GS_River,
};
const std::vector<ItemLocation*> WaT_MQ = {
  &WaterTemple_MQ_CentralPillarChest,
  &WaterTemple_MQ_BossKeyChest,
  &WaterTemple_MQ_LongshotChest,
  &WaterTemple_MQ_CompassChest,
  &WaterTemple_MQ_MapChest,
  &WaterTemple_MQ_FreestandingKey,
  &WaterTemple_MQ_GS_BeforeUpperWaterSwitch,
  &WaterTemple_MQ_GS_FreestandingKeyArea,
  &WaterTemple_MQ_GS_LizalfosHallway,
  &WaterTemple_MQ_GS_River,
  &WaterTemple_MQ_GS_TripleWallTorch,
};
const std::vector<ItemLocation*> SpT_Vanilla = {
  &SpiritTemple_ChildBridgeChest,
  &SpiritTemple_ChildEarlyTorchesChest,
  &SpiritTemple_CompassChest,
  &SpiritTemple_EarlyAdultRightChest,
  &SpiritTemple_FirstMirrorLeftChest,
  &SpiritTemple_FirstMirrorRightChest,
  &SpiritTemple_MapChest,
  &SpiritTemple_ChildClimbNorthChest,
  &SpiritTemple_ChildClimbEastChest,
  &SpiritTemple_SunBlockRoomChest,
  &SpiritTemple_StatueRoomHandChest,
  &SpiritTemple_StatueRoomNortheastChest,
  &SpiritTemple_NearFourArmosChest,
  &SpiritTemple_HallwayLeftInvisibleChest,
  &SpiritTemple_HallwayRightInvisibleChest,
  &SpiritTemple_BossKeyChest,
  &SpiritTemple_TopmostChest,
  &SpiritTemple_GS_HallAfterSunBlockRoom,
  &SpiritTemple_GS_BoulderRoom,
  &SpiritTemple_GS_Lobby,
  &SpiritTemple_GS_SunOnFloorRoom,
  &SpiritTemple_GS_MetalFence,
};
const std::vector<ItemLocation*> SpT_MQ = {
  &SpiritTemple_MQ_EntranceFrontLeftChest,
  &SpiritTemple_MQ_EntranceBackRightChest,
  &SpiritTemple_MQ_EntranceFrontRightChest,
  &SpiritTemple_MQ_EntranceBackLeftChest,
  &SpiritTemple_MQ_ChildHammerSwitchChest,
  &SpiritTemple_MQ_MapChest,
  &SpiritTemple_MQ_MapRoomEnemyChest,
  &SpiritTemple_MQ_ChildClimbNorthChest,
  &SpiritTemple_MQ_ChildClimbSouthChest,
  &SpiritTemple_MQ_CompassChest,
  &SpiritTemple_MQ_StatueRoomLullabyChest,
  &SpiritTemple_MQ_StatueRoomInvisibleChest,
  &SpiritTemple_MQ_SilverBlockHallwayChest,
  &SpiritTemple_MQ_SunBlockRoomChest,
  &SpiritTemple_MQ_SymphonyRoomChest,
  &SpiritTemple_MQ_LeeverRoomChest,
  &SpiritTemple_MQ_BeamosRoomChest,
  &SpiritTemple_MQ_ChestSwitchChest,
  &SpiritTemple_MQ_BossKeyChest,
  &SpiritTemple_MQ_MirrorPuzzleInvisibleChest,
  &SpiritTemple_MQ_GS_SymphonyRoom,
  &SpiritTemple_MQ_GS_LeeverRoom,
  &SpiritTemple_MQ_GS_NineThronesRoomWest,
  &SpiritTemple_MQ_GS_NineThronesRoomNorth,
  &SpiritTemple_MQ_GS_SunBlockRoom,
};
const std::vector<ItemLocation*> ShT_Vanilla = {
  &ShadowTemple_MapChest,
  &ShadowTemple_HoverBootsChest,
  &ShadowTemple_CompassChest,
  &ShadowTemple_EarlySilverRupeeChest,
  &ShadowTemple_InvisibleBladesVisibleChest,
  &ShadowTemple_InvisibleBladesInvisibleChest,
  &ShadowTemple_FallingSpikesLowerChest,
  &ShadowTemple_FallingSpikesUpperChest,
  &ShadowTemple_FallingSpikesSwitchChest,
  &ShadowTemple_InvisibleSpikesChest,
  &ShadowTemple_WindHintChest,
  &ShadowTemple_AfterWindEnemyChest,
  &ShadowTemple_AfterWindHiddenChest,
  &ShadowTemple_SpikeWallsLeftChest,
  &ShadowTemple_BossKeyChest,
  &ShadowTemple_InvisibleFloormasterChest,
  &ShadowTemple_FreestandingKey,
  &ShadowTemple_GS_SingleGiantPot,
  &ShadowTemple_GS_FallingSpikesRoom,
  &ShadowTemple_GS_TripleGiantPot,
  &ShadowTemple_GS_LikeLikeRoom,
  &ShadowTemple_GS_NearShip,
};
const std::vector<ItemLocation*> ShT_MQ = {
  &ShadowTemple_MQ_CompassChest,
  &ShadowTemple_MQ_HoverBootsChest,
  &ShadowTemple_MQ_EarlyGibdosChest,
  &ShadowTemple_MQ_MapChest,
  &ShadowTemple_MQ_BeamosSilverRupeesChest,
  &ShadowTemple_MQ_FallingSpikesSwitchChest,
  &ShadowTemple_MQ_FallingSpikesLowerChest,
  &ShadowTemple_MQ_FallingSpikesUpperChest,
  &ShadowTemple_MQ_InvisibleSpikesChest,
  &ShadowTemple_MQ_BossKeyChest,
  &ShadowTemple_MQ_SpikeWallsLeftChest,
  &ShadowTemple_MQ_StalfosRoomChest,
  &ShadowTemple_MQ_InvisibleBladesInvisibleChest,
  &ShadowTemple_MQ_InvisibleBladesVisibleChest,
  &ShadowTemple_MQ_BombFlowerChest,
  &ShadowTemple_MQ_WindHintChest,
  &ShadowTemple_MQ_AfterWindHiddenChest,
  &ShadowTemple_MQ_AfterWindEnemyChest,
  &ShadowTemple_MQ_NearShipInvisibleChest,
  &ShadowTemple_MQ_FreestandingKey,
  &ShadowTemple_MQ_GS_FallingSpikesRoom,
  &ShadowTemple_MQ_GS_WindHintRoom,
  &ShadowTemple_MQ_GS_AfterWind,
  &ShadowTemple_MQ_GS_AfterShip,
  &ShadowTemple_MQ_GS_NearBoss,
};
const std::vector<ItemLocation*> BotW_Vanilla = {
  &BottomOfTheWell_FrontLeftFakeWallChest,
  &BottomOfTheWell_FrontCenterBombableChest,
  &BottomOfTheWell_RightBottomFakeWallChest,
  &BottomOfTheWell_CompassChest,
  &BottomOfTheWell_CenterSkulltulaChest,
  &BottomOfTheWell_BackLeftBombableChest,
  &BottomOfTheWell_LensOfTruthChest,
  &BottomOfTheWell_InvisibleChest,
  &BottomOfTheWell_UnderwaterFrontChest,
  &BottomOfTheWell_UnderwaterLeftChest,
  &BottomOfTheWell_MapChest,
  &BottomOfTheWell_FireKeeseChest,
  &BottomOfTheWell_LikeLikeChest,
  &BottomOfTheWell_FreestandingKey,
  &BottomOfTheWell_GS_LikeLikeCage,
  &BottomOfTheWell_GS_EastInnerRoom,
  &BottomOfTheWell_GS_WestInnerRoom,
};
const std::vector<ItemLocation*> BotW_MQ = {
  &BottomOfTheWell_MQ_MapChest,
  &BottomOfTheWell_MQ_LensOfTruthChest,
  &BottomOfTheWell_MQ_CompassChest,
  &BottomOfTheWell_MQ_DeadHandFreestandingKey,
  &BottomOfTheWell_MQ_EastInnerRoomFreestandingKey,
  &BottomOfTheWell_MQ_GS_Basement,
  &BottomOfTheWell_MQ_GS_CoffinRoom,
  &BottomOfTheWell_MQ_GS_WestInnerRoom,
};
const std::vector<ItemLocation*> IC_Vanilla = {
  &IceCavern_MapChest,
  &IceCavern_CompassChest,
  &IceCavern_IronBootsChest,
  &IceCavern_FreestandingPoH,
  &IceCavern_GS_PushBlockRoom,
  &IceCavern_GS_SpinningScytheRoom,
  &IceCavern_GS_HeartPieceRoom,
};
const std::vector<ItemLocation*> IC_MQ = {
  &IceCavern_MQ_IronBootsChest,
  &IceCavern_MQ_CompassChest,
  &IceCavern_MQ_MapChest,
  &IceCavern_MQ_FreestandingPoH,
  &IceCavern_MQ_GS_Scarecrow,
  &IceCavern_MQ_GS_IceBlock,
  &IceCavern_MQ_GS_RedIce,
};
const std::vector<ItemLocation*> GTG_Vanilla = {
  &GerudoTrainingGrounds_LobbyLeftChest,
  &GerudoTrainingGrounds_LobbyRightChest,
  &GerudoTrainingGrounds_StalfosChest,
  &GerudoTrainingGrounds_BeamosChest,
  &GerudoTrainingGrounds_HiddenCeilingChest,
  &GerudoTrainingGrounds_MazePathFirstChest,
  &GerudoTrainingGrounds_MazePathSecondChest,
  &GerudoTrainingGrounds_MazePathThirdChest,
  &GerudoTrainingGrounds_MazePathFinalChest,
  &GerudoTrainingGrounds_MazeRightCentralChest,
  &GerudoTrainingGrounds_MazeRightSideChest,
  &GerudoTrainingGrounds_UnderwaterSilverRupeeChest,
  &GerudoTrainingGrounds_HammerRoomClearChest,
  &GerudoTrainingGrounds_HammerRoomSwitchChest,
  &GerudoTrainingGrounds_EyeStatueChest,
  &GerudoTrainingGrounds_NearScarecrowChest,
  &GerudoTrainingGrounds_BeforeHeavyBlockChest,
  &GerudoTrainingGrounds_HeavyBlockFirstChest,
  &GerudoTrainingGrounds_HeavyBlockSecondChest,
  &GerudoTrainingGrounds_HeavyBlockThirdChest,
  &GerudoTrainingGrounds_HeavyBlockFourthChest,
  &GerudoTrainingGrounds_FreestandingKey,
};
const std::vector<ItemLocation*> GTG_MQ = {
  &GerudoTrainingGrounds_MQ_LobbyRightChest,
  &GerudoTrainingGrounds_MQ_LobbyLeftChest,
  &GerudoTrainingGrounds_MQ_FirstIronKnuckleChest,
  &GerudoTrainingGrounds_MQ_BeforeHeavyBlockChest,
  &GerudoTrainingGrounds_MQ_EyeStatueChest,
  &GerudoTrainingGrounds_MQ_FlameCircleChest,
  &GerudoTrainingGrounds_MQ_SecondIronKnuckleChest,
  &GerudoTrainingGrounds_MQ_DinolfosChest,
  &GerudoTrainingGrounds_MQ_IceArrowsChest,
  &GerudoTrainingGrounds_MQ_MazeRightCentralChest,
  &GerudoTrainingGrounds_MQ_MazePathFirstChest,
  &GerudoTrainingGrounds_MQ_MazeRightSideChest,
  &GerudoTrainingGrounds_MQ_MazePathThirdChest,
  &GerudoTrainingGrounds_MQ_MazePathSecondChest,
  &GerudoTrainingGrounds_MQ_HiddenCeilingChest,
  &GerudoTrainingGrounds_MQ_UnderwaterSilverRupeeChest,
  &GerudoTrainingGrounds_MQ_HeavyBlockChest,
};
const std::vector<ItemLocation*> GC_Vanilla = {
  &GanonsCastle_ForestTrialChest,
  &GanonsCastle_WaterTrialLeftChest,
  &GanonsCastle_WaterTrialRightChest,
  &GanonsCastle_ShadowTrialFrontChest,
  &GanonsCastle_ShadowTrialGoldenGauntletsChest,
  &GanonsCastle_SpiritTrialCrystalSwitchChest,
  &GanonsCastle_SpiritTrialInvisibleChest,
  &GanonsCastle_LightTrialFirstLeftChest,
  &GanonsCastle_LightTrialSecondLeftChest,
  &GanonsCastle_LightTrialThirdLeftChest,
  &GanonsCastle_LightTrialFirstRightChest,
  &GanonsCastle_LightTrialSecondRightChest,
  &GanonsCastle_LightTrialThirdRightChest,
  &GanonsCastle_LightTrialInvisibleEnemiesChest,
  &GanonsCastle_LightTrialLullabyChest,
  &GanonsCastle_DekuScrubLeft,
  &GanonsCastle_DekuScrubCenterLeft,
  &GanonsCastle_DekuScrubCenterRight,
  &GanonsCastle_DekuScrubRight,
};
const std::vector<ItemLocation*> GC_MQ = {
  &GanonsCastle_MQ_WaterTrialChest,
  &GanonsCastle_MQ_ForestTrialEyeSwitchChest,
  &GanonsCastle_MQ_ForestTrialFrozenEyeSwitchChest,
  &GanonsCastle_MQ_LightTrialLullabyChest,
  &GanonsCastle_MQ_ShadowTrialBombFlowerChest,
  &GanonsCastle_MQ_ShadowTrialEyeSwitchChest,
  &GanonsCastle_MQ_SpiritTrialGoldenGauntletsChest,
  &GanonsCastle_MQ_SpiritTrialSunBackRightChest,
  &GanonsCastle_MQ_SpiritTrialSunBackLeftChest,
  &GanonsCastle_MQ_SpiritTrialSunFrontLeftChest,
  &GanonsCastle_MQ_SpiritTrialFirstChest,
  &GanonsCastle_MQ_SpiritTrialInvisibleChest,
  &GanonsCastle_MQ_ForestTrialFreestandingKey,
  &GanonsCastle_MQ_DekuScrubRight,
  &GanonsCastle_MQ_DekuScrubCenterLeft,
  &GanonsCastle_MQ_DekuScrubCenter,
  &GanonsCastle_MQ_DekuScrubCenterRight,
  &GanonsCastle_MQ_DekuScrubLeft,
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

  //Deku Tree
  AddLocations((DekuTreeDungeonMode) ? DT_MQ : DT_Vanilla);
  AddLocation(&DekuTree_QueenGohmaHeart);
  AddLocation(&QueenGohma);

  //Dodongos Cavern
  AddLocations((DodongosCavernDungeonMode) ? DC_MQ : DC_Vanilla);
  AddLocation(&DodongosCavern_BossRoomChest);
  AddLocation(&DodongosCavern_KingDodongoHeart);
  AddLocation(&KingDodongo);

  //Jabu Jabu's Belly
  AddLocations((JabuJabusBellyDungeonMode) ? Jabu_MQ : Jabu_Vanilla);
  AddLocation(&JabuJabusBelly_BarinadeHeart);
  AddLocation(&Barinade);

  //Forest Temple
  AddLocations((ForestTempleDungeonMode) ? FoT_MQ : FoT_Vanilla);
  AddLocation(&ForestTemple_PhantomGanonHeart);
  AddLocation(&PhantomGanon);

  //Fire Temple
  AddLocations((FireTempleDungeonMode) ? FiT_MQ : FiT_Vanilla);
  AddLocation(&FireTemple_VolvagiaHeart);
  AddLocation(&Volvagia);

  //Water Temple
  AddLocations((WaterTempleDungeonMode) ? WaT_MQ : WaT_Vanilla);
  AddLocation(&WaterTemple_MorphaHeart);
  AddLocation(&Morpha);

  //Spirit Temple
  AddLocation(&SpiritTemple_SilverGauntletsChest);
  AddLocation(&SpiritTemple_MirrorShieldChest);
  AddLocations((SpiritTempleDungeonMode) ? SpT_MQ : SpT_Vanilla);
  AddLocation(&SpiritTemple_TwinrovaHeart);
  AddLocation(&Twinrova);

  //Shadow Temple
  AddLocations((ShadowTempleDungeonMode) ? ShT_MQ : ShT_Vanilla);
  AddLocation(&ShadowTemple_BongoBongoHeart);
  AddLocation(&BongoBongo);

  //Bottom of the Well
  AddLocations((BottomOfTheWellDungeonMode) ? BotW_MQ : BotW_Vanilla);

  //Ice Cavern
  AddLocations((IceCavernDungeonMode) ? IC_MQ : IC_Vanilla);
  AddLocation(&SheikInIceCavern);

  //Gerudo Training Grounds
  AddLocations((GerudoTrainingGroundsDungeonMode) ? GTG_MQ : GTG_Vanilla);

  //Ganons Castle
  AddLocations((GanonsCastleDungeonMode) ? GC_MQ : GC_Vanilla);
  AddLocation(&GanonsCastle_BossKeyChest);
  AddLocation(&Ganon);
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

    loc->SetPlacedItem(item);
}

std::vector<ItemLocation*> GetLocations(std::vector<ItemLocation*> locationPool, Category category) {
  std::vector<ItemLocation*> locationsInCategory = {};
  for (auto& loc : locationPool) {
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

//Fills everyPossibleLocation and creates an exclusion option for each location
//everyPossibleLocation is used in the menu to lock/hide excluding locations
void AddExcludedOptions() {
  AddLocations(overworldLocations, &everyPossibleLocation);

  AddLocations(DT_MQ, &everyPossibleLocation);
  AddLocations(DT_Vanilla, &everyPossibleLocation);
  AddLocation(&DekuTree_QueenGohmaHeart, &everyPossibleLocation);

  AddLocations(DC_MQ, &everyPossibleLocation);
  AddLocations(DC_Vanilla, &everyPossibleLocation);
  AddLocation(&DodongosCavern_BossRoomChest, &everyPossibleLocation);
  AddLocation(&DodongosCavern_KingDodongoHeart, &everyPossibleLocation);

  AddLocations(Jabu_MQ, &everyPossibleLocation);
  AddLocations(Jabu_Vanilla, &everyPossibleLocation);
  AddLocation(&JabuJabusBelly_BarinadeHeart, &everyPossibleLocation);

  AddLocations(FoT_MQ, &everyPossibleLocation);
  AddLocations(FoT_Vanilla, &everyPossibleLocation);
  AddLocation(&ForestTemple_PhantomGanonHeart, &everyPossibleLocation);

  AddLocations(FiT_MQ, &everyPossibleLocation);
  AddLocations(FiT_Vanilla, &everyPossibleLocation);
  AddLocation(&FireTemple_VolvagiaHeart, &everyPossibleLocation);

  AddLocations(WaT_MQ, &everyPossibleLocation);
  AddLocations(WaT_Vanilla, &everyPossibleLocation);
  AddLocation(&WaterTemple_MorphaHeart, &everyPossibleLocation);

  AddLocation(&SpiritTemple_SilverGauntletsChest, &everyPossibleLocation);
  AddLocation(&SpiritTemple_MirrorShieldChest, &everyPossibleLocation);
  AddLocations(SpT_MQ, &everyPossibleLocation);
  AddLocations(SpT_Vanilla, &everyPossibleLocation);
  AddLocation(&SpiritTemple_TwinrovaHeart, &everyPossibleLocation);

  AddLocations(ShT_MQ, &everyPossibleLocation);
  AddLocations(ShT_Vanilla, &everyPossibleLocation);
  AddLocation(&ShadowTemple_BongoBongoHeart, &everyPossibleLocation);

  AddLocations(BotW_MQ, &everyPossibleLocation);
  AddLocations(BotW_Vanilla, &everyPossibleLocation);

  AddLocations(IC_MQ, &everyPossibleLocation);
  AddLocations(IC_Vanilla, &everyPossibleLocation);
  AddLocation(&SheikInIceCavern, &everyPossibleLocation);

  AddLocations(GTG_MQ, &everyPossibleLocation);
  AddLocations(GTG_Vanilla, &everyPossibleLocation);

  AddLocations(GC_MQ, &everyPossibleLocation);
  AddLocations(GC_Vanilla, &everyPossibleLocation);
  AddLocation(&GanonsCastle_BossKeyChest, &everyPossibleLocation);

  for (ItemLocation * il: everyPossibleLocation) {
    il->AddExcludeOption();
  }
}

void CreateOverrides() {
  PlacementLog_Msg("NOW CREATING OVERRIDES\n\n");
  for (ItemLocation* loc : allLocations) {
    overrides.insert({
      .key = loc->Key(),
      .value = loc->GetPlacedItem().Value(),
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
