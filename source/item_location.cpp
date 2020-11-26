#include "item_location.hpp"

//Kokiri Forest
ItemLocation KF_KokiriSwordChest                          = ItemLocation(0x55, ITEMLOCATIONTYPE_CHEST,        0x00, "KF Kokiri Sword Chest",                {"Kokiri Forest", "Forest",});
ItemLocation KF_MidoTopLeftChest                          = ItemLocation(0x28, ITEMLOCATIONTYPE_CHEST,        0x00, "KF Mido Top Left Chest",               {"Kokiri Forest", "Forest",});
ItemLocation KF_MidoTopRightChest                         = ItemLocation(0x28, ITEMLOCATIONTYPE_CHEST,        0x01, "KF Mido Top Right Chest",              {"Kokiri Forest", "Forest",});
ItemLocation KF_MidoBottomLeftChest                       = ItemLocation(0x28, ITEMLOCATIONTYPE_CHEST,        0x02, "KF Mido Bottom Left Chest",            {"Kokiri Forest", "Forest",});
ItemLocation KF_MidoBottomRightChest                      = ItemLocation(0x28, ITEMLOCATIONTYPE_CHEST,        0x03, "KF Mido Bottom Right Chest",           {"Kokiri Forest", "Forest",});
ItemLocation KF_StormsGrottoChest                         = ItemLocation(0x3E, ITEMLOCATIONTYPE_CHEST,        0x0C, "KF Storms Grotto Chest",               {"Kokiri Forest", "Forest", "Grottos"});

//Lost Woods
ItemLocation LW_NearShortcutsGrottoChest                  = ItemLocation(0x3E, ITEMLOCATIONTYPE_CHEST,        0x14, "LW Near Shortcuts Grotto Chest",       {"the Lost Woods", "Forest", "Grottos"});
ItemLocation LW_SkullKid                                  = ItemLocation(0x5B, ITEMLOCATIONTYPE_BASE,         0x3E, "LW Skull Kid",                         {"the Lost Woods", "Forest",});
ItemLocation LW_OcarinaMemoryGame                         = ItemLocation(0x5B, ITEMLOCATIONTYPE_BASE,         0x76, "LW Ocarina Memory Game",               {"the Lost Woods", "Forest", "Minigames"});//Gives wrong item
ItemLocation LW_TargetInWoods                             = ItemLocation(0x5B, ITEMLOCATIONTYPE_BASE,         0x60, "LW Target in Woods",                   {"the Lost Woods", "Forest",});
ItemLocation LW_DekuScrubNearDekuTheaterRight             = ItemLocation(0x5B, ITEMLOCATIONTYPE_BASE,         0x30, "LW Deku Scrub Near Deku Theater Right",{"the Lost Woods", "Forest", "Deku Scrub"});//doesnt work
ItemLocation LW_DekuScrubNearDekuTheaterLeft              = ItemLocation(0x5B, ITEMLOCATIONTYPE_BASE,         0x31, "LW Deku Scrub Near Deku Theater Left", {"the Lost Woods", "Forest", "Deku Scrub"}); //doesnt work
ItemLocation LW_DekuScrubNearBridge                       = ItemLocation(0x5B, ITEMLOCATIONTYPE_BASE,         0x77, "LW Deku Scrub Near Bridge",            {"the Lost Woods", "Forest", "Deku Scrub", "Deku Scrub Upgrades"});
ItemLocation LW_DekuScrubGrottoRear                       = ItemLocation(0xF5, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x33, "LW Deku Scrub Grotto Rear",            {"the Lost Woods", "Forest", "Deku Scrub", "Grottos"});
ItemLocation LW_DekuScrubGrottoFront                      = ItemLocation(0xF5, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x79, "LW Deku Scrub Grotto Front",           {"the Lost Woods", "Forest", "Deku Scrub", "Deku Scrub Upgrades", "Grottos"});
ItemLocation DekuTheater_SkullMask                        = ItemLocation(0x3E, ITEMLOCATIONTYPE_BASE,         0x77, "Deku Theater Skull Mask",              {"the Lost Woods", "Forest", "Grottos"});
ItemLocation DekuTheater_MaskOfTruth                      = ItemLocation(0x3E, ITEMLOCATIONTYPE_BASE,         0x7A, "Deku Theater Mask of Truth",           {"the Lost Woods", "Forest", "Need Spiritual Stones", "Grottos"});

//Sacred Forest Meadow
ItemLocation SFM_WolfosGrottoChest                        = ItemLocation(0x3E, ITEMLOCATIONTYPE_CHEST,        0x11, "SFM Wolfos Grotto Chest",              {"Sacred Forest Meadow", "Forest", "Grottos"});
ItemLocation SFM_DekuScrubGrottoRear                      = ItemLocation(0xEE, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x39, "SFM Deku Scrub Grotto Rear",           {"Sacred Forest Meadow", "Forest", "Deku Scrub", "Grottos"});
ItemLocation SFM_DekuScrubGrottoFront                     = ItemLocation(0xEE, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x3A, "SFM Deku Scrub Grotto Front",          {"Sacred Forest Meadow", "Forest", "Deku Scrub", "Grottos"});

//Hyrule Field
ItemLocation HF_SoutheastGrottoChest                      = ItemLocation(0x3E, ITEMLOCATIONTYPE_CHEST,        0x02, "HF Southeast Grotto Chest",            {"Hyrule Field", "Grottos",});
ItemLocation HF_OpenGrottoChest                           = ItemLocation(0x3E, ITEMLOCATIONTYPE_CHEST,        0x03, "HF Open Grotto Chest",                 {"Hyrule Field", "Grottos",});
ItemLocation HF_NearMarketGrottoChest                     = ItemLocation(0x3E, ITEMLOCATIONTYPE_CHEST,        0x00, "HF Near Market Grotto Chest",          {"Hyrule Field", "Grottos",});
ItemLocation HF_OcarinaOfTimeItem                         = ItemLocation(0x51, ITEMLOCATIONTYPE_BASE,         0x0C, "HF Ocarina of Time Item",              {"Hyrule Field", "Need Spiritual Stones",});
ItemLocation HF_TektiteGrottoFreestandingPoH              = ItemLocation(0x3E, ITEMLOCATIONTYPE_COLLECTABLE,  0x01, "HF Tektite Grotto Freestanding PoH",   {"Hyrule Field", "Grottos",});
ItemLocation HF_DekuScrubGrotto                           = ItemLocation(0xE6, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x3E, "HF Deku Scrub Grotto",                 {"Hyrule Field", "Deku Scrub", "Deku Scrub Upgrades", "Grottos"});

//Lake Hylia
ItemLocation LH_ChildFishing                              = ItemLocation(0x49, ITEMLOCATIONTYPE_BASE,         0x3E, "LH Child Fishing",                     {"Lake Hylia", "Minigames",});
ItemLocation LH_AdultFishing                              = ItemLocation(0x49, ITEMLOCATIONTYPE_BASE,         0x38, "LH Adult Fishing",                     {"Lake Hylia", "Minigames",});
ItemLocation LH_LabDive                                   = ItemLocation(0x38, ITEMLOCATIONTYPE_BASE,         0x3E, "LH Lab Dive",                          {"Lake Hylia",});
ItemLocation LH_UnderwaterItem                            = ItemLocation(0x57, ITEMLOCATIONTYPE_BASE,         0x15, "LH Underwater Item",                   {"Lake Hylia",});
ItemLocation LH_Sun                                       = ItemLocation(0x57, ITEMLOCATIONTYPE_BASE,         0x58, "LH Sun",                               {"Lake Hylia",});
ItemLocation LH_FreestandingPoH                           = ItemLocation(0x57, ITEMLOCATIONTYPE_COLLECTABLE,  0x1E, "LH Freestanding PoH",                  {"Lake Hylia",});
ItemLocation LH_DekuScrubGrottoLeft                       = ItemLocation(0xEF, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x30, "LH Deku Scrub Grotto Left",            {"Lake Hylia", "Deku Scrub", "Grottos"});
ItemLocation LH_DekuScrubGrottoRight                      = ItemLocation(0xEF, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x37, "LH Deku Scrub Grotto Right",           {"Lake Hylia", "Deku Scrub", "Grottos"});
ItemLocation LH_DekuScrubGrottoCenter                     = ItemLocation(0xEF, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x33, "LH Deku Scrub Grotto Center",          {"Lake Hylia", "Deku Scrub", "Grottos"});

//Gerudo Valley
ItemLocation GV_Chest                                     = ItemLocation(0x5A, ITEMLOCATIONTYPE_CHEST,        0x00, "GV Chest",                             {"Gerudo Valley", "Gerudo",});
ItemLocation GV_WaterfallFreestandingPoH                  = ItemLocation(0x5A, ITEMLOCATIONTYPE_COLLECTABLE,  0x01, "GV Waterfall Freestanding PoH",        {"Gerudo Valley", "Gerudo",});
ItemLocation GV_CrateFreestandingPoH                      = ItemLocation(0x5A, ITEMLOCATIONTYPE_COLLECTABLE,  0x02, "GV Crate Freestanding PoH",            {"Gerudo Valley", "Gerudo",});
ItemLocation GV_DekuScrubGrottoRear                       = ItemLocation(0xF0, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x39, "GV Deku Scrub Grotto Rear",            {"Gerudo Valley", "Gerudo", "Deku Scrub", "Grottos"});
ItemLocation GV_DekuScrubGrottoFront                      = ItemLocation(0xF0, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x3A, "GV Deku Scrub Grotto Front",           {"Gerudo Valley", "Gerudo", "Deku Scrub", "Grottos"});

//Gerudo Fortress
ItemLocation GF_Chest                                     = ItemLocation(0x5D, ITEMLOCATIONTYPE_CHEST,        0x00, "GF Chest",                             {"Gerudo's Fortress", "Gerudo",});
ItemLocation GF_HBA1000Points                             = ItemLocation(0x5D, ITEMLOCATIONTYPE_BASE,         0x3E, "GF HBA 1000 Points",                   {"Gerudo's Fortress", "Gerudo", "Minigames"});
ItemLocation GF_HBA1500Points                             = ItemLocation(0x5D, ITEMLOCATIONTYPE_BASE,         0x30, "GF HBA 1500 Points",                   {"Gerudo's Fortress", "Gerudo", "Minigames"});
ItemLocation GF_GerudoToken                               = ItemLocation(0x0C, ITEMLOCATIONTYPE_BASE,         0x3A, "GF Gerudo Token",                      {"Gerudo's Fortress", "Gerudo",});
ItemLocation GF_NorthF1Carpenter                          = ItemLocation(0x0C, ITEMLOCATIONTYPE_COLLECTABLE,  0x0C, "GF North F1 Carpenter",                {"Gerudo's Fortress", "Gerudo",});
ItemLocation GF_NorthF2Carpenter                          = ItemLocation(0x0C, ITEMLOCATIONTYPE_COLLECTABLE,  0x0A, "GF North F2 Carpenter",                {"Gerudo's Fortress", "Gerudo",});
ItemLocation GF_SouthF1Carpenter                          = ItemLocation(0x0C, ITEMLOCATIONTYPE_COLLECTABLE,  0x0E, "GF South F1 Carpenter",                {"Gerudo's Fortress", "Gerudo",});
ItemLocation GF_SouthF2Carpenter                          = ItemLocation(0x0C, ITEMLOCATIONTYPE_COLLECTABLE,  0x0F, "GF South F2 Carpenter",                {"Gerudo's Fortress", "Gerudo",});

//Haunted Wasteland
ItemLocation HW_Chest                                     = ItemLocation(0x5E, ITEMLOCATIONTYPE_CHEST,        0x00, "HW Chest",                             {"Haunted Wasteland",});

//Desert Colossus
ItemLocation Colossus_FreestandingPoH                     = ItemLocation(0x5C, ITEMLOCATIONTYPE_COLLECTABLE,  0x0D, "Colossus Freestanding PoH",            {"Desert Colossus",});
ItemLocation Colossus_DekuScrubGrottoRear                 = ItemLocation(0xFD, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x39, "Colossus Deku Scrub Grotto Rear",      {"Desert Colossus", "Deku Scrub", "Grottos"});
ItemLocation Colossus_DekuScrubGrottoFront                = ItemLocation(0xFD, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x3A, "Colossus Deku Scrub Grotto Front",     {"Desert Colossus", "Deku Scrub", "Grottos"});

//Market
ItemLocation MK_TreasureChestGameReward                   = ItemLocation(0x10, ITEMLOCATIONTYPE_CHEST,        0x0A, "MK Treasure Chest Game Reward",        {"the Market", "Market", "Minigames"});
ItemLocation MK_BombchuBowlingFirstPrize                  = ItemLocation(0x4B, ITEMLOCATIONTYPE_BASE,         0x34, "MK Bombchu Bowling First Prize",       {"the Market", "Market", "Minigames"});
ItemLocation MK_BombchuBowlingSecondPrize                 = ItemLocation(0x4B, ITEMLOCATIONTYPE_BASE,         0x3E, "MK Bombchu Bowling Second Prize",      {"the Market", "Market", "Minigames"});
ItemLocation MK_LostDog                                   = ItemLocation(0x35, ITEMLOCATIONTYPE_BASE,         0x3E, "MK Lost Dog",                          {"the Market", "Market",});
ItemLocation MK_ShootingGalleryReward                     = ItemLocation(0x42, ITEMLOCATIONTYPE_BASE,         0x60, "MK Shooting Gallery",                  {"the Market", "Market", "Minigames"});
ItemLocation MK_10BigPoes                                 = ItemLocation(0x4D, ITEMLOCATIONTYPE_BASE,         0x0F, "MK 10 Big Poes",                       {"the Market", "Hyrule Castle",});

//Hyrule Castle
ItemLocation HC_MalonEgg                                  = ItemLocation(0x5F, ITEMLOCATIONTYPE_BASE,         0x47, "HC Malon Egg",                         {"Hyrule Castle", "Market",});
ItemLocation HC_ZeldasLetter                              = ItemLocation(0x4A, ITEMLOCATIONTYPE_BASE,         0x0B, "HC Zeldas Letter",                     {"Hyrule Castle", "Market",});

//Kakariko
ItemLocation Kak_RedeadGrottoChest                        = ItemLocation(0x3E, ITEMLOCATIONTYPE_CHEST,        0x0A, "Kak Redead Grotto Chest",              {"Kakariko Village", "Kakariko", "Grottos"});
ItemLocation Kak_OpenGrottoChest                          = ItemLocation(0x3E, ITEMLOCATIONTYPE_CHEST,        0x08, "Kak Open Grotto Chest",                {"Kakariko Village", "Kakariko", "Grottos"});
ItemLocation Kak_10GoldSkulltulaReward                    = ItemLocation(0x50, ITEMLOCATIONTYPE_BASE,         0x45, "Kak 10 Gold Skulltula Reward",         {"Kakariko Village", "Kakariko", "Skulltula House"});
ItemLocation Kak_20GoldSkulltulaReward                    = ItemLocation(0x50, ITEMLOCATIONTYPE_BASE,         0x39, "Kak 20 Gold Skulltula Reward",         {"Kakariko Village", "Kakariko", "Skulltula House"});
ItemLocation Kak_30GoldSkulltulaReward                    = ItemLocation(0x50, ITEMLOCATIONTYPE_BASE,         0x46, "Kak 30 Gold Skulltula Reward",         {"Kakariko Village", "Kakariko", "Skulltula House"});
ItemLocation Kak_40GoldSkulltulaReward                    = ItemLocation(0x50, ITEMLOCATIONTYPE_BASE,         0x03, "Kak 40 Gold Skulltula Reward",         {"Kakariko Village", "Kakariko", "Skulltula House"});
ItemLocation Kak_50GoldSkulltulaReward                    = ItemLocation(0x50, ITEMLOCATIONTYPE_BASE,         0x3E, "Kak 50 Gold Skulltula Reward",         {"Kakariko Village", "Kakariko", "Skulltula House"});
ItemLocation Kak_ManOnRoof                                = ItemLocation(0x52, ITEMLOCATIONTYPE_BASE,         0x3E, "Kak Man on Roof",                      {"Kakariko Village", "Kakariko",});
ItemLocation Kak_ShootingGalleryReward                    = ItemLocation(0x42, ITEMLOCATIONTYPE_BASE,         0x30, "Kak Shooting Gallery Reward",          {"Kakariko Village", "Kakariko", "Minigames"});
ItemLocation Kak_AnjuAsAdult                              = ItemLocation(0x52, ITEMLOCATIONTYPE_BASE,         0x1D, "Kak Anju as Adult",                    {"Kakariko Village", "Kakariko",});
ItemLocation Kak_AnjuAsChild                              = ItemLocation(0x52, ITEMLOCATIONTYPE_BASE,         0x0F, "Kak Anju as Child",                    {"Kakariko Village", "Kakariko", "Minigames"});
ItemLocation Kak_ImpasHouseFreestandingPoH                = ItemLocation(0x37, ITEMLOCATIONTYPE_COLLECTABLE,  0x01, "Kak Impas House Freestanding PoH",     {"Kakariko Village", "Kakariko",});
ItemLocation Kak_WindmillFreestandingPoH                  = ItemLocation(0x48, ITEMLOCATIONTYPE_COLLECTABLE,  0x01, "Kak Windmill Freestanding PoH",        {"Kakariko Village", "Kakariko",});

//Graveyard
ItemLocation GY_ShieldGraveChest                          = ItemLocation(0x40, ITEMLOCATIONTYPE_CHEST,        0x00, "GY Shield Grave Chest",                {"the Graveyard", "Kakariko",});
ItemLocation GY_HeartPieceGraveChest                      = ItemLocation(0x3F, ITEMLOCATIONTYPE_CHEST,        0x00, "GY Heart Piece Grave Chest",           {"the Graveyard", "Kakariko",});
ItemLocation GY_ComposersGraveChest                       = ItemLocation(0x41, ITEMLOCATIONTYPE_CHEST,        0x00, "GY Composers Grave Chest",             {"the Graveyard", "Kakariko",});
ItemLocation GY_HookshotChest                             = ItemLocation(0x48, ITEMLOCATIONTYPE_CHEST,        0x00, "GY Hookshot Chest",                    {"the Graveyard", "Kakariko",});
ItemLocation GY_DampeRaceFreestandingPoH                  = ItemLocation(0x48, ITEMLOCATIONTYPE_COLLECTABLE,  0x07, "GY Dampe Race Freestanding PoH",       {"the Graveyard", "Kakariko", "Minigames"});
ItemLocation GY_FreestandingPoH                           = ItemLocation(0x53, ITEMLOCATIONTYPE_COLLECTABLE,  0x04, "GY Freestanding PoH",                  {"the Graveyard", "Kakariko",});
ItemLocation GY_DampeGravediggingTour                     = ItemLocation(0x53, ITEMLOCATIONTYPE_COLLECTABLE,  0x08, "GY Dampe Gravedigging Tour",           {"the Graveyard", "Kakariko",});

//Death Mountain
ItemLocation DMT_Chest                                    = ItemLocation(0x60, ITEMLOCATIONTYPE_CHEST,        0x01, "DMT Chest",                            {"Death Mountain Trail", "Death Mountain",});
ItemLocation DMT_StormsGrottoChest                        = ItemLocation(0x3E, ITEMLOCATIONTYPE_CHEST,        0x17, "DMT Storms Grotto Chest",              {"Death Mountain Trail", "Death Mountain", "Grottos"});
ItemLocation DMT_Biggoron                                 = ItemLocation(0x60, ITEMLOCATIONTYPE_BASE,         0x57, "DMT Biggoron",                         {"Death Mountain Trail", "Death Mountain",});
ItemLocation DMT_FreestandingPoH                          = ItemLocation(0x60, ITEMLOCATIONTYPE_COLLECTABLE,  0x1E, "DMT Freestanding PoH",                 {"Death Mountain Trail", "Death Mountain",});

//Goron City
ItemLocation GC_MazeLeftChest                             = ItemLocation(0x62, ITEMLOCATIONTYPE_CHEST,        0x00, "GC Maze Left Chest",                   {"Goron City",});
ItemLocation GC_MazeRightChest                            = ItemLocation(0x62, ITEMLOCATIONTYPE_CHEST,        0x01, "GC Maze Right Chest",                  {"Goron City",});
ItemLocation GC_MazeCenterChest                           = ItemLocation(0x62, ITEMLOCATIONTYPE_CHEST,        0x02, "GC Maze Center Chest",                 {"Goron City",});
ItemLocation GC_RollingGoronAsChild                       = ItemLocation(0x62, ITEMLOCATIONTYPE_BASE,         0x34, "GC Rolling Goron as Child",            {"Goron City",});
ItemLocation GC_RollingGoronAsAdult                       = ItemLocation(0x62, ITEMLOCATIONTYPE_BASE,         0x2C, "GC Rolling Goron as Adult",            {"Goron City",});
ItemLocation GC_DaruniasJoy                               = ItemLocation(0x62, ITEMLOCATIONTYPE_BASE,         0x54, "GC Darunias Joy",                      {"Goron City",});
ItemLocation GC_PotFreestandingPoH                        = ItemLocation(0x62, ITEMLOCATIONTYPE_COLLECTABLE,  0x1F, "GC Pot Freestanding PoH",              {"Goron City", "Goron City",});
ItemLocation GC_DekuScrubGrottoLeft                       = ItemLocation(0xFB, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x30, "GC Deku Scrub Grotto Left",            {"Goron City", "Deku Scrub", "Grottos"});
ItemLocation GC_DekuScrubGrottoRight                      = ItemLocation(0xFB, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x37, "GC Deku Scrub Grotto Right",           {"Goron City", "Deku Scrub", "Grottos"});
ItemLocation GC_DekuScrubGrottoCenter                     = ItemLocation(0xFB, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x33, "GC Deku Scrub Grotto Center",          {"Goron City", "Deku Scrub", "Grottos"});

//Death Mountain Crater
ItemLocation DMC_UpperGrottoChest                         = ItemLocation(0x3E, ITEMLOCATIONTYPE_CHEST,        0x1A, "DMC Upper Grotto Chest",               {"Death Mountain Crater", "Death Mountain", "Grottos"});
ItemLocation DMC_WallFreestandingPoH                      = ItemLocation(0x61, ITEMLOCATIONTYPE_COLLECTABLE,  0x02, "DMC Wall Freestanding PoH",            {"Death Mountain Crater", "Death Mountain",});
ItemLocation DMC_VolcanoFreestandingPoH                   = ItemLocation(0x61, ITEMLOCATIONTYPE_COLLECTABLE,  0x08, "DMC Volcano Freestanding PoH",         {"Death Mountain Crater", "Death Mountain",});
ItemLocation DMC_DekuScrub                                = ItemLocation(0x61, ITEMLOCATIONTYPE_BASE,         0x37, "DMC Deku Scrub",                       {"Death Mountain Crater", "Death Mountain", "Deku Scrub"});
ItemLocation DMC_DekuScrubGrottoLeft                      = ItemLocation(0xF9, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x30, "DMC Deku Scrub Grotto Left",           {"Death Mountain Crater", "Death Mountain", "Deku Scrub", "Grottos"});
ItemLocation DMC_DekuScrubGrottoRight                     = ItemLocation(0xF9, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x37, "DMC Deku Scrub Grotto Right",          {"Death Mountain Crater", "Death Mountain", "Deku Scrub", "Grottos"});
ItemLocation DMC_DekuScrubGrottoCenter                    = ItemLocation(0xF9, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x33, "DMC Deku Scrub Grotto Center",         {"Death Mountain Crater", "Death Mountain", "Deku Scrub", "Grottos"});

//Zoras River
ItemLocation ZR_OpenGrottoChest                           = ItemLocation(0x3E, ITEMLOCATIONTYPE_CHEST,        0x09, "ZR Open Grotto Chest",                 {"Zora's River", "Grottos",});
ItemLocation ZR_MagicBeanSalesman                         = ItemLocation(0x54, ITEMLOCATIONTYPE_BASE,         0x16, "ZR Magic Bean Salesman",               {"Zora's River",});
ItemLocation ZR_FrogsOcarinaGame                          = ItemLocation(0x54, ITEMLOCATIONTYPE_BASE,         0x76, "ZR Frogs Ocarina Game",                {"Zora's River",});
ItemLocation ZR_FrogsInTheRain                            = ItemLocation(0x54, ITEMLOCATIONTYPE_BASE,         0x3E, "ZR Frogs in the Rain",                 {"Zora's River", "Minigames",});
ItemLocation ZR_NearOpenGrottoFreestandingPoH             = ItemLocation(0x54, ITEMLOCATIONTYPE_COLLECTABLE,  0x04, "ZR Near Open Grotto Freestanding PoH", {"Zora's River",});
ItemLocation ZR_NearDomainFreestandingPoH                 = ItemLocation(0x54, ITEMLOCATIONTYPE_COLLECTABLE,  0x0B, "ZR Near Domain Freestanding PoH",      {"Zora's River",});
ItemLocation ZR_DekuScrubGrottoRear                       = ItemLocation(0xEB, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x39, "ZR Deku Scrub Grotto Rear",            {"Zora's River", "Deku Scrub", "Grottos"});
ItemLocation ZR_DekuScrubGrottoFront                      = ItemLocation(0xEB, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x3A, "ZR Deku Scrub Grotto Front",           {"Zora's River", "Deku Scrub", "Grottos"});

//Zoras Domain
ItemLocation ZD_Chest                                     = ItemLocation(0x58, ITEMLOCATIONTYPE_CHEST,        0x00, "ZD Chest",                             {"Zora's Domain",});
ItemLocation ZD_DivingMinigame                            = ItemLocation(0x58, ITEMLOCATIONTYPE_BASE,         0x37, "ZD Diving Minigame",                   {"Zora's Domain", "Minigames",});
ItemLocation ZD_KingZoraThawed                            = ItemLocation(0x58, ITEMLOCATIONTYPE_BASE,         0x2D, "ZD King Zora Thawed",                  {"Zora's Domain",});

//Zoras Fountain
ItemLocation ZF_IcebergFreestandingPoH                    = ItemLocation(0x59, ITEMLOCATIONTYPE_COLLECTABLE,  0x01, "ZF Iceberg Freestanding PoH",          {"Zora's Fountain",});
ItemLocation ZF_BottomFreestandingPoH                     = ItemLocation(0x59, ITEMLOCATIONTYPE_COLLECTABLE,  0x14, "ZF Bottom Freestanding PoH",           {"Zora's Fountain",});

//Lon Lon Ranch
ItemLocation LLR_TalonsChickens                           = ItemLocation(0x4C, ITEMLOCATIONTYPE_BASE,         0x14, "LLR Talons Chickens",                  {"Lon Lon Ranch", "Minigames"});
ItemLocation LLR_FreestandingPoH                          = ItemLocation(0x4C, ITEMLOCATIONTYPE_COLLECTABLE,  0x01, "LLR Freestanding PoH",                 {"Lon Lon Ranch",});
ItemLocation LLR_DekuScrubGrottoLeft                      = ItemLocation(0xFC, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x30, "LLR Deku Scrub Grotto Left",           {"Lon Lon Ranch", "Deku Scrub", "Grottos"});
ItemLocation LLR_DekuScrubGrottoRight                     = ItemLocation(0xFC, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x37, "LLR Deku Scrub Grotto Right",          {"Lon Lon Ranch", "Deku Scrub", "Grottos"});
ItemLocation LLR_DekuScrubGrottoCenter                    = ItemLocation(0xFC, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x33, "LLR Deku Scrub Grotto Center",         {"Lon Lon Ranch", "Deku Scrub", "Grottos"});

/*-------------------
   --- DUNGEONS ---
  -------------------*/

//Deku Tree
ItemLocation DekuTree_MapChest                            = ItemLocation(0x00, ITEMLOCATIONTYPE_CHEST,        0x03, "Deku Tree Map Chest",                                {"Deku Tree",});
ItemLocation DekuTree_CompassChest                        = ItemLocation(0x00, ITEMLOCATIONTYPE_CHEST,        0x02, "Deku Tree Compass Chest",                            {"Deku Tree",});
ItemLocation DekuTree_CompassRoomSideChest                = ItemLocation(0x00, ITEMLOCATIONTYPE_CHEST,        0x06, "Deku Tree Compass Room Side Chest",                  {"Deku Tree",});
ItemLocation DekuTree_BasementChest                       = ItemLocation(0x00, ITEMLOCATIONTYPE_CHEST,        0x04, "Deku Tree Basement Chest",                           {"Deku Tree",});
ItemLocation DekuTree_SlingshotChest                      = ItemLocation(0x00, ITEMLOCATIONTYPE_CHEST,        0x01, "Deku Tree Slingshot Chest",                          {"Deku Tree",});
ItemLocation DekuTree_SlingshotRoomSideChest              = ItemLocation(0x00, ITEMLOCATIONTYPE_CHEST,        0x05, "Deku Tree Slingshot Room Side Chest",                {"Deku Tree",});
ItemLocation DekuTree_QueenGohmaHeart                     = ItemLocation(0x11, ITEMLOCATIONTYPE_BASE,         0x4F, "Deku Tree Queen Gohma Heart",                        {"Deku Tree",});

//Dodongos Cavern
ItemLocation DodongosCavern_MapChest                      = ItemLocation(0x01, ITEMLOCATIONTYPE_CHEST,        0x08, "Dodongos Cavern Map Chest",                          {"Dodongo's Cavern",});
ItemLocation DodongosCavern_CompassChest                  = ItemLocation(0x01, ITEMLOCATIONTYPE_CHEST,        0x05, "Dodongos Cavern Compass Chest",                      {"Dodongo's Cavern",});
ItemLocation DodongosCavern_BombFlowerPlatformChest       = ItemLocation(0x01, ITEMLOCATIONTYPE_CHEST,        0x06, "Dodongos Cavern Bomb Flower Platform Chest",         {"Dodongo's Cavern",});
ItemLocation DodongosCavern_BombBagChest                  = ItemLocation(0x01, ITEMLOCATIONTYPE_CHEST,        0x04, "Dodongos Cavern Bomb Bag Chest",                     {"Dodongo's Cavern",});
ItemLocation DodongosCavern_EndOfBridgeChest              = ItemLocation(0x01, ITEMLOCATIONTYPE_CHEST,        0x0A, "Dodongos Cavern End Of Bridge Chest",                {"Dodongo's Cavern",});
ItemLocation DodongosCavern_BossRoomChest                 = ItemLocation(0x12, ITEMLOCATIONTYPE_CHEST,        0x00, "Dodongos Cavern Boss Room Chest",                    {"Dodongo's Cavern",});
ItemLocation DodongosCavern_DekuScrubNearBombBagLeft      = ItemLocation(0x01, ITEMLOCATIONTYPE_BASE,         0x30, "Dodongos Cavern Deku Scrub Near Bomb Bag Left",      {"Dodongo's Cavern", "Deku Scrub",});
ItemLocation DodongosCavern_DekuScrubSideRoomNearDodongos = ItemLocation(0x01, ITEMLOCATIONTYPE_BASE,         0x31, "Dodongos Cavern Deku Scrub Side Room Near Dodongos", {"Dodongo's Cavern", "Deku Scrub",});
ItemLocation DodongosCavern_DekuScrubNearBombBagRight     = ItemLocation(0x01, ITEMLOCATIONTYPE_BASE,         0x33, "Dodongos Cavern Deku Scrub Near Bomb Bag Right",     {"Dodongo's Cavern", "Deku Scrub",});
ItemLocation DodongosCavern_DekuScrubLobby                = ItemLocation(0x01, ITEMLOCATIONTYPE_BASE,         0x34, "Dodongos Cavern Deku Scrub Lobby",                   {"Dodongo's Cavern", "Deku Scrub",});
ItemLocation DodongosCavern_KingDodongoHeart              = ItemLocation(0x12, ITEMLOCATIONTYPE_BASE,         0x4F, "Dodongos Cavern King Dodongo Heart",                 {"Dodongo's Cavern",});

//Jabu Jabus Belly
ItemLocation JabuJabusBelly_MapChest                      = ItemLocation(0x02, ITEMLOCATIONTYPE_CHEST,        0x02, "Jabu Jabus Belly Map Chest",                         {"Jabu Jabu's Belly",});
ItemLocation JabuJabusBelly_CompassChest                  = ItemLocation(0x02, ITEMLOCATIONTYPE_CHEST,        0x04, "Jabu Jabus Belly Compass Chest",                     {"Jabu Jabu's Belly",});
ItemLocation JabuJabusBelly_BoomerangChest                = ItemLocation(0x02, ITEMLOCATIONTYPE_CHEST,        0x01, "Jabu Jabus Belly Boomerang Chest",                   {"Jabu Jabu's Belly",});
ItemLocation JabuJabusBelly_DekuScrub                     = ItemLocation(0x02, ITEMLOCATIONTYPE_BASE,         0x30, "Jabu Jabus Belly Deku Scrub",                        {"Jabu Jabu's Belly", "Deku Scrub",});
ItemLocation JabuJabusBelly_BarinadeHeart                 = ItemLocation(0x13, ITEMLOCATIONTYPE_BASE,         0x4F, "Jabu Jabus Belly Barinade Heart",                    {"Jabu Jabu's Belly",});

//Forest Temple
ItemLocation ForestTemple_FirstRoomChest                  = ItemLocation(0x03, ITEMLOCATIONTYPE_CHEST,        0x03, "Forest Temple First Room Chest",                     {"Forest Temple",});
ItemLocation ForestTemple_FirstStalfosChest               = ItemLocation(0x03, ITEMLOCATIONTYPE_CHEST,        0x00, "Forest Temple First Stalfos Chest",                  {"Forest Temple",});
ItemLocation ForestTemple_RaisedIslandCourtyardChest      = ItemLocation(0x03, ITEMLOCATIONTYPE_CHEST,        0x05, "Forest Temple Raised Island Courtyard Chest",        {"Forest Temple",});
ItemLocation ForestTemple_MapChest                        = ItemLocation(0x03, ITEMLOCATIONTYPE_CHEST,        0x01, "Forest Temple Map Chest",                            {"Forest Temple",});
ItemLocation ForestTemple_WellChest                       = ItemLocation(0x03, ITEMLOCATIONTYPE_CHEST,        0x09, "Forest Temple Well Chest",                           {"Forest Temple",});
ItemLocation ForestTemple_FallingCeilingRoomChest         = ItemLocation(0x03, ITEMLOCATIONTYPE_CHEST,        0x07, "Forest Temple Falling Ceiling Room Chest",           {"Forest Temple",});
ItemLocation ForestTemple_EyeSwitchChest                  = ItemLocation(0x03, ITEMLOCATIONTYPE_CHEST,        0x04, "Forest Temple Eye Switch Chest",                     {"Forest Temple",});
ItemLocation ForestTemple_BossKeyChest                    = ItemLocation(0x03, ITEMLOCATIONTYPE_CHEST,        0x0E, "Forest Temple Boss Key Chest",                       {"Forest Temple",});
ItemLocation ForestTemple_FloormasterChest                = ItemLocation(0x03, ITEMLOCATIONTYPE_CHEST,        0x02, "Forest Temple Floormaster Chest",                    {"Forest Temple",});
ItemLocation ForestTemple_BowChest                        = ItemLocation(0x03, ITEMLOCATIONTYPE_CHEST,        0x0C, "Forest Temple Bow Chest",                            {"Forest Temple",});
ItemLocation ForestTemple_RedPoeChest                     = ItemLocation(0x03, ITEMLOCATIONTYPE_CHEST,        0x0D, "Forest Temple Red Poe Chest",                        {"Forest Temple",});
ItemLocation ForestTemple_BluePoeChest                    = ItemLocation(0x03, ITEMLOCATIONTYPE_CHEST,        0x0F, "Forest Temple Blue Poe Chest",                       {"Forest Temple",});
ItemLocation ForestTemple_BasementChest                   = ItemLocation(0x03, ITEMLOCATIONTYPE_CHEST,        0x0B, "Forest Temple Basement Chest",                       {"Forest Temple",});
ItemLocation ForestTemple_PhantomGanonHeart               = ItemLocation(0x14, ITEMLOCATIONTYPE_BASE,         0x4F, "Forest Temple Phantom Ganon Heart",                  {"Forest Temple",});

//Fire Temple
ItemLocation FireTemple_NearBossChest                     = ItemLocation(0x04, ITEMLOCATIONTYPE_CHEST,        0x01, "Fire Temple Near Boss Chest",                        {"Fire Temple",});
ItemLocation FireTemple_FlareDancerChest                  = ItemLocation(0x04, ITEMLOCATIONTYPE_CHEST,        0x00, "Fire Temple Flare Dancer Chest",                     {"Fire Temple",});
ItemLocation FireTemple_BossKeyChest                      = ItemLocation(0x04, ITEMLOCATIONTYPE_CHEST,        0x0C, "Fire Temple Boss Key Chest",                         {"Fire Temple",});
ItemLocation FireTemple_BigLavaRoomBlockedDoorChest       = ItemLocation(0x04, ITEMLOCATIONTYPE_CHEST,        0x02, "Fire Temple Big Lava Room Blocked Door Chest",       {"Fire Temple",});
ItemLocation FireTemple_BigLavaRoomLowerOpenDoorChest     = ItemLocation(0x04, ITEMLOCATIONTYPE_CHEST,        0x04, "Fire Temple Big Lava Room Lower Open Door Chest",    {"Fire Temple",});
ItemLocation FireTemple_BoulderMazeLowerChest             = ItemLocation(0x04, ITEMLOCATIONTYPE_CHEST,        0x03, "Fire Temple Boulder Maze Lower Chest",               {"Fire Temple",});
ItemLocation FireTemple_BoulderMazeUpperChest             = ItemLocation(0x04, ITEMLOCATIONTYPE_CHEST,        0x06, "Fire Temple Boulder Maze Upper Chest",               {"Fire Temple",});
ItemLocation FireTemple_BoulderMazeSideRoomChest          = ItemLocation(0x04, ITEMLOCATIONTYPE_CHEST,        0x08, "Fire Temple Boulder Maze Side Room Chest",           {"Fire Temple",});
ItemLocation FireTemple_BoulderMazeShortcutChest          = ItemLocation(0x04, ITEMLOCATIONTYPE_CHEST,        0x0B, "Fire Temple Boulder Maze Shortcut Chest",            {"Fire Temple",});
ItemLocation FireTemple_ScarecrowChest                    = ItemLocation(0x04, ITEMLOCATIONTYPE_CHEST,        0x0D, "Fire Temple Scarecrow Chest",                        {"Fire Temple",});
ItemLocation FireTemple_MapChest                          = ItemLocation(0x04, ITEMLOCATIONTYPE_CHEST,        0x0A, "Fire Temple Map Chest",                              {"Fire Temple",});
ItemLocation FireTemple_CompassChest                      = ItemLocation(0x04, ITEMLOCATIONTYPE_CHEST,        0x07, "Fire Temple Compass Chest",                          {"Fire Temple",});
ItemLocation FireTemple_HighestGoronChest                 = ItemLocation(0x04, ITEMLOCATIONTYPE_CHEST,        0x09, "Fire Temple Highest Goron Chest",                    {"Fire Temple",});
ItemLocation FireTemple_MegatonHammerChest                = ItemLocation(0x04, ITEMLOCATIONTYPE_CHEST,        0x05, "Fire Temple Megaton Hammer Chest",                   {"Fire Temple",});
ItemLocation FireTemple_VolvagiaHeart                     = ItemLocation(0x15, ITEMLOCATIONTYPE_BASE,         0x4F, "Fire Temple Volvagia Heart",                         {"Fire Temple",});

//Water Temple
ItemLocation WaterTemple_MapChest                         = ItemLocation(0x05, ITEMLOCATIONTYPE_CHEST,        0x02, "Water Temple Map Chest",                             {"Water Temple",});
ItemLocation WaterTemple_CompassChest                     = ItemLocation(0x05, ITEMLOCATIONTYPE_CHEST,        0x09, "Water Temple Compass Chest",                         {"Water Temple",});
ItemLocation WaterTemple_TorchesChest                     = ItemLocation(0x05, ITEMLOCATIONTYPE_CHEST,        0x01, "Water Temple Torches Chest",                         {"Water Temple",});
ItemLocation WaterTemple_DragonChest                      = ItemLocation(0x05, ITEMLOCATIONTYPE_CHEST,        0x0A, "Water Temple Dragon Chest",                          {"Water Temple",});
ItemLocation WaterTemple_CentralBowTargetChest            = ItemLocation(0x05, ITEMLOCATIONTYPE_CHEST,        0x08, "Water Temple Central Bow Target Chest",              {"Water Temple",});
ItemLocation WaterTemple_CentralPillarChest               = ItemLocation(0x05, ITEMLOCATIONTYPE_CHEST,        0x06, "Water Temple Central Pillar Chest",                  {"Water Temple",});
ItemLocation WaterTemple_CrackedWallChest                 = ItemLocation(0x05, ITEMLOCATIONTYPE_CHEST,        0x00, "Water Temple Cracked Wall Chest",                    {"Water Temple",});
ItemLocation WaterTemple_BossKeyChest                     = ItemLocation(0x05, ITEMLOCATIONTYPE_CHEST,        0x05, "Water Temple Boss Key Chest",                        {"Water Temple",});
ItemLocation WaterTemple_LongshotChest                    = ItemLocation(0x05, ITEMLOCATIONTYPE_CHEST,        0x07, "Water Temple Longshot Chest",                        {"Water Temple",});
ItemLocation WaterTemple_RiverChest                       = ItemLocation(0x05, ITEMLOCATIONTYPE_CHEST,        0x03, "Water Temple River Chest",                           {"Water Temple",});
ItemLocation WaterTemple_MorphaHeart                      = ItemLocation(0x16, ITEMLOCATIONTYPE_BASE,         0x4F, "Water Temple Morpha Heart",                          {"Water Temple",});

//Spirit Temple Outside
ItemLocation SpiritTemple_SilverGauntletsChest            = ItemLocation(0x5C, ITEMLOCATIONTYPE_CHEST,        0x0B, "Spirit Temple Silver Gauntlets Chest",               {"Spirit Temple", "Desert Colossus"});
ItemLocation SpiritTemple_MirrorShieldChest               = ItemLocation(0x5C, ITEMLOCATIONTYPE_CHEST,        0x09, "Spirit Temple Mirror Shield Chest",                  {"Spirit Temple", "Desert Colossus"});
//Spirit Temple
ItemLocation SpiritTemple_ChildBridgeChest                = ItemLocation(0x06, ITEMLOCATIONTYPE_CHEST,        0x08, "Spirit Temple Child Bridge Chest",                   {"Spirit Temple",});
ItemLocation SpiritTemple_ChildEarlyTorchesChest          = ItemLocation(0x06, ITEMLOCATIONTYPE_CHEST,        0x00, "Spirit Temple Child Early Torches Chest",            {"Spirit Temple",});
ItemLocation SpiritTemple_CompassChest                    = ItemLocation(0x06, ITEMLOCATIONTYPE_CHEST,        0x04, "Spirit Temple Compass Chest",                        {"Spirit Temple",});
ItemLocation SpiritTemple_EarlyAdultRightChest            = ItemLocation(0x06, ITEMLOCATIONTYPE_CHEST,        0x07, "Spirit Temple Early Adult Right Chest",              {"Spirit Temple",});
ItemLocation SpiritTemple_FirstMirrorLeftChest            = ItemLocation(0x06, ITEMLOCATIONTYPE_CHEST,        0x0D, "Spirit Temple First Mirror Left Chest",              {"Spirit Temple",});
ItemLocation SpiritTemple_FirstMirrorRightChest           = ItemLocation(0x06, ITEMLOCATIONTYPE_CHEST,        0x0E, "Spirit Temple First Mirror Right Chest",             {"Spirit Temple",});
ItemLocation SpiritTemple_MapChest                        = ItemLocation(0x06, ITEMLOCATIONTYPE_CHEST,        0x03, "Spirit Temple Map Chest",                            {"Spirit Temple",});
ItemLocation SpiritTemple_ChildClimbNorthChest            = ItemLocation(0x06, ITEMLOCATIONTYPE_CHEST,        0x06, "Spirit Temple Child Climb North Chest",              {"Spirit Temple",});
ItemLocation SpiritTemple_ChildClimbEastChest             = ItemLocation(0x06, ITEMLOCATIONTYPE_CHEST,        0x0C, "Spirit Temple Child Climb East Chest",               {"Spirit Temple",});
ItemLocation SpiritTemple_SunBlockRoomChest               = ItemLocation(0x06, ITEMLOCATIONTYPE_CHEST,        0x01, "Spirit Temple Sun Block Room Chest",                 {"Spirit Temple",});
ItemLocation SpiritTemple_StatueRoomHandChest             = ItemLocation(0x06, ITEMLOCATIONTYPE_CHEST,        0x02, "Spirit Temple Statue Room Hand Chest",               {"Spirit Temple",});
ItemLocation SpiritTemple_StatueRoomNortheastChest        = ItemLocation(0x06, ITEMLOCATIONTYPE_CHEST,        0x0F, "Spirit Temple Statue Room Northeast Chest",          {"Spirit Temple",});
ItemLocation SpiritTemple_NearFourArmosChest              = ItemLocation(0x06, ITEMLOCATIONTYPE_CHEST,        0x05, "Spirit Temple Near Four Armos Chest",                {"Spirit Temple",});
ItemLocation SpiritTemple_HallwayRightInvisibleChest      = ItemLocation(0x06, ITEMLOCATIONTYPE_CHEST,        0x14, "Spirit Temple Hallway Right Invisible Chest",        {"Spirit Temple",});
ItemLocation SpiritTemple_HallwayLeftInvisibleChest       = ItemLocation(0x06, ITEMLOCATIONTYPE_CHEST,        0x15, "Spirit Temple Hallway Left Invisible Chest",         {"Spirit Temple",});
ItemLocation SpiritTemple_BossKeyChest                    = ItemLocation(0x06, ITEMLOCATIONTYPE_CHEST,        0x0A, "Spirit Temple Boss Key Chest",                       {"Spirit Temple",});
ItemLocation SpiritTemple_TopmostChest                    = ItemLocation(0x06, ITEMLOCATIONTYPE_CHEST,        0x12, "Spirit Temple Topmost Chest",                        {"Spirit Temple",});
ItemLocation SpiritTemple_TwinrovaHeart                   = ItemLocation(0x17, ITEMLOCATIONTYPE_BASE,         0x4F, "Spirit Temple Twinrova Heart",                       {"Spirit Temple",});

//Shadow Temple
ItemLocation ShadowTemple_MapChest                        = ItemLocation(0x07, ITEMLOCATIONTYPE_CHEST,        0x01, "Shadow Temple Map Chest",                            {"Shadow Temple",});
ItemLocation ShadowTemple_HoverBootsChest                 = ItemLocation(0x07, ITEMLOCATIONTYPE_CHEST,        0x07, "Shadow Temple Hover Boots Chest",                    {"Shadow Temple",});
ItemLocation ShadowTemple_CompassChest                    = ItemLocation(0x07, ITEMLOCATIONTYPE_CHEST,        0x03, "Shadow Temple Compass Chest",                        {"Shadow Temple",});
ItemLocation ShadowTemple_EarlySilverRupeeChest           = ItemLocation(0x07, ITEMLOCATIONTYPE_CHEST,        0x02, "Shadow Temple Early Silver Rupee Chest",             {"Shadow Temple",});
ItemLocation ShadowTemple_InvisibleBladesVisibleChest     = ItemLocation(0x07, ITEMLOCATIONTYPE_CHEST,        0x0C, "Shadow Temple Invisible Blades Visible Chest",       {"Shadow Temple",});
ItemLocation ShadowTemple_InvisibleBladesInvisibleChest   = ItemLocation(0x07, ITEMLOCATIONTYPE_CHEST,        0x16, "Shadow Temple Invisible Blades Invisible Chest",     {"Shadow Temple",});
ItemLocation ShadowTemple_FallingSpikesLowerChest         = ItemLocation(0x07, ITEMLOCATIONTYPE_CHEST,        0x05, "Shadow Temple Falling Spikes Lower Chest",           {"Shadow Temple",});
ItemLocation ShadowTemple_FallingSpikesUpperChest         = ItemLocation(0x07, ITEMLOCATIONTYPE_CHEST,        0x06, "Shadow Temple Falling Spikes Upper Chest",           {"Shadow Temple",});
ItemLocation ShadowTemple_FallingSpikesSwitchChest        = ItemLocation(0x07, ITEMLOCATIONTYPE_CHEST,        0x04, "Shadow Temple Falling Spikes Switch Chest",          {"Shadow Temple",});
ItemLocation ShadowTemple_InvisibleSpikesChest            = ItemLocation(0x07, ITEMLOCATIONTYPE_CHEST,        0x09, "Shadow Temple Invisible Spikes Chest",               {"Shadow Temple",});
ItemLocation ShadowTemple_WindHintChest                   = ItemLocation(0x07, ITEMLOCATIONTYPE_CHEST,        0x15, "Shadow Temple Wind Hint Chest",                      {"Shadow Temple",});
ItemLocation ShadowTemple_AfterWindEnemyChest             = ItemLocation(0x07, ITEMLOCATIONTYPE_CHEST,        0x08, "Shadow Temple After Wind Enemey Chest",              {"Shadow Temple",});
ItemLocation ShadowTemple_AfterWindHiddenChest            = ItemLocation(0x07, ITEMLOCATIONTYPE_CHEST,        0x14, "Shadow Temple After Wind Hidden Chest",              {"Shadow Temple",});
ItemLocation ShadowTemple_SpikeWallsLeftChest             = ItemLocation(0x07, ITEMLOCATIONTYPE_CHEST,        0x0A, "Shadow Temple Spike Walls Left Chest",               {"Shadow Temple",});
ItemLocation ShadowTemple_BossKeyChest                    = ItemLocation(0x07, ITEMLOCATIONTYPE_CHEST,        0x0B, "Shadow Temple Boss Key Chest",                       {"Shadow Temple",});
ItemLocation ShadowTemple_InvisibleFloormasterChest       = ItemLocation(0x07, ITEMLOCATIONTYPE_CHEST,        0x0D, "Shadow Temple Invisible Floormaster Chest",          {"Shadow Temple",});
ItemLocation ShadowTemple_FreestandingKey                 = ItemLocation(0x07, ITEMLOCATIONTYPE_COLLECTABLE,  0x01, "Shadow Temple Freestanding Key",                     {"Shadow Temple",});
ItemLocation ShadowTemple_BongoBongoHeart                 = ItemLocation(0x13, ITEMLOCATIONTYPE_BASE,         0x4F, "Shadow Temple Bongo Bongo Heart",                    {"Shadow Temple",});

//Bottom of the Well
ItemLocation BottomOfTheWell_FrontLeftFakeWallChest       = ItemLocation(0x08, ITEMLOCATIONTYPE_CHEST,        0x08, "Bottom of the Well Front Left Fake Wall Chest",      {"Bottom of the Well",});
ItemLocation BottomOfTheWell_FrontCenterBombableChest     = ItemLocation(0x08, ITEMLOCATIONTYPE_CHEST,        0x02, "Bottom of the Well Front Center Bombable Chest",     {"Bottom of the Well",});
ItemLocation BottomOfTheWell_RightBottomFakeWallChest     = ItemLocation(0x08, ITEMLOCATIONTYPE_CHEST,        0x05, "Bottom of the Well Right Bottom Fake Wall Chest",    {"Bottom of the Well",});
ItemLocation BottomOfTheWell_CompassChest                 = ItemLocation(0x08, ITEMLOCATIONTYPE_CHEST,        0x01, "Bottom of the Well Compass Chest",                   {"Bottom of the Well",});
ItemLocation BottomOfTheWell_CenterSkulltulaChest         = ItemLocation(0x08, ITEMLOCATIONTYPE_CHEST,        0x0E, "Bottom of the Well Center Skulltula Chest",          {"Bottom of the Well",});
ItemLocation BottomOfTheWell_BackLeftBombableChest        = ItemLocation(0x08, ITEMLOCATIONTYPE_CHEST,        0x04, "Bottom of the Well Back Left Bombable Chest",        {"Bottom of the Well",});
ItemLocation BottomOfTheWell_LensOfTruthChest             = ItemLocation(0x08, ITEMLOCATIONTYPE_CHEST,        0x03, "Bottom of the Well Lens of Truth Chest",             {"Bottom of the Well",});
ItemLocation BottomOfTheWell_InvisibleChest               = ItemLocation(0x08, ITEMLOCATIONTYPE_CHEST,        0x14, "Bottom of the Well Invisible Chest",                 {"Bottom of the Well",});
ItemLocation BottomOfTheWell_UnderwaterFrontChest         = ItemLocation(0x08, ITEMLOCATIONTYPE_CHEST,        0x10, "Bottom of the Well Underwater Front Chest",          {"Bottom of the Well",});
ItemLocation BottomOfTheWell_UnderwaterLeftChest          = ItemLocation(0x08, ITEMLOCATIONTYPE_CHEST,        0x09, "Bottom of the Well Underwater Left Chest",           {"Bottom of the Well",});
ItemLocation BottomOfTheWell_MapChest                     = ItemLocation(0x08, ITEMLOCATIONTYPE_CHEST,        0x07, "Bottom of the Well Map Chest",                       {"Bottom of the Well",});
ItemLocation BottomOfTheWell_FireKeeseChest               = ItemLocation(0x08, ITEMLOCATIONTYPE_CHEST,        0x0A, "Bottom of the Well Fire Keese Chest",                {"Bottom of the Well",});
ItemLocation BottomOfTheWell_LikeLikeChest                = ItemLocation(0x08, ITEMLOCATIONTYPE_CHEST,        0x0C, "Bottom of the Well Like Like Chest",                 {"Bottom of the Well",});
ItemLocation BottomOfTheWell_FreestandingKey              = ItemLocation(0x08, ITEMLOCATIONTYPE_COLLECTABLE,  0x01, "Bottom of the Well Freestanding Key",                {"Bottom of the Well",});

//Ice Cavern
ItemLocation IceCavern_MapChest                           = ItemLocation(0x09, ITEMLOCATIONTYPE_CHEST,        0x00, "Ice Cavern Map Chest",                               {"Ice Cavern",});
ItemLocation IceCavern_CompassChest                       = ItemLocation(0x09, ITEMLOCATIONTYPE_CHEST,        0x01, "Ice Cavern Compass Chest",                           {"Ice Cavern",});
ItemLocation IceCavern_IronBootsChest                     = ItemLocation(0x09, ITEMLOCATIONTYPE_CHEST,        0x02, "Ice Cavern Iron Boots Chest",                        {"Ice Cavern",});
ItemLocation IceCavern_FreestandingPoH                    = ItemLocation(0x09, ITEMLOCATIONTYPE_COLLECTABLE,  0x01, "Ice Cavern Freestanding PoH",                        {"Ice Cavern",});

//Gerudo Training Ground
ItemLocation GerudoTrainingGrounds_LobbyLeftChest             = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x13, "Gerudo Training Grounds Lobby Left Chest",              {"Gerudo Training Grounds",});
ItemLocation GerudoTrainingGrounds_LobbyRightChest            = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x07, "Gerudo Training Grounds Lobby Right Chest",             {"Gerudo Training Grounds",});
ItemLocation GerudoTrainingGrounds_StalfosChest               = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x00, "Gerudo Training Grounds Stalfos Chest",                 {"Gerudo Training Grounds",});
ItemLocation GerudoTrainingGrounds_BeamosChest                = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x01, "Gerudo Training Grounds Beamos Chest",                  {"Gerudo Training Grounds",});
ItemLocation GerudoTrainingGrounds_HiddenCeilingChest         = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x0B, "Gerudo Training Grounds Hidden Ceiling Chest",          {"Gerudo Training Grounds",});
ItemLocation GerudoTrainingGrounds_MazePathFirstChest         = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x06, "Gerudo Training Grounds Maze Path First Chest",         {"Gerudo Training Grounds",});
ItemLocation GerudoTrainingGrounds_MazePathSecondChest        = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x0A, "Gerudo Training Grounds Maze Path Second Chest",        {"Gerudo Training Grounds",});
ItemLocation GerudoTrainingGrounds_MazePathThirdChest         = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x09, "Gerudo Training Grounds Maze Path Third Chest",         {"Gerudo Training Grounds",});
ItemLocation GerudoTrainingGrounds_MazePathFinalChest         = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x0C, "Gerudo Training Grounds Maze Path Final Chest",         {"Gerudo Training Grounds",});
ItemLocation GerudoTrainingGrounds_MazeRightCentralChest      = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x05, "Gerudo Training Grounds Maze Right Central Chest",      {"Gerudo Training Grounds",});
ItemLocation GerudoTrainingGrounds_MazeRightSideChest         = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x08, "Gerudo Training Grounds Maze Right Side Chest",         {"Gerudo Training Grounds",});
ItemLocation GerudoTrainingGrounds_UnderwaterSilverRupeeChest = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x0D, "Gerudo Training Grounds Underwater Silver Rupee Chest", {"Gerudo Training Grounds",});
ItemLocation GerudoTrainingGrounds_HammerRoomClearChest       = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x12, "Gerudo Training Grounds Hammer Room Clear Chest",       {"Gerudo Training Grounds",});
ItemLocation GerudoTrainingGrounds_HammerRoomSwitchChest      = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x10, "Gerudo Training Grounds Hammer Room Switch Chest",      {"Gerudo Training Grounds",});
ItemLocation GerudoTrainingGrounds_EyeStatueChest             = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x03, "Gerudo Training Grounds Eye Statue Chest",              {"Gerudo Training Grounds",});
ItemLocation GerudoTrainingGrounds_NearScarecrowChest         = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x04, "Gerudo Training Grounds Near Scarecrow Chest",          {"Gerudo Training Grounds",});
ItemLocation GerudoTrainingGrounds_BeforeHeavyBlockChest      = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x11, "Gerudo Training Grounds Before Heavy Block Chest",      {"Gerudo Training Grounds",});
ItemLocation GerudoTrainingGrounds_HeavyBlockFirstChest       = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x0F, "Gerudo Training Grounds Heavy Block First Chest",       {"Gerudo Training Grounds",});
ItemLocation GerudoTrainingGrounds_HeavyBlockSecondChest      = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x0E, "Gerudo Training Grounds Heavy Block Second Chest",      {"Gerudo Training Grounds",});
ItemLocation GerudoTrainingGrounds_HeavyBlockThirdChest       = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x14, "Gerudo Training Grounds Heavy Block Third Chest",       {"Gerudo Training Grounds",});
ItemLocation GerudoTrainingGrounds_HeavyBlockFourthChest      = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x02, "Gerudo Training Grounds Heavy Block Fourth Chest",      {"Gerudo Training Grounds",});
ItemLocation GerudoTrainingGrounds_FreestandingKey            = ItemLocation(0x0B, ITEMLOCATIONTYPE_COLLECTABLE,  0x01, "Gerudo Training Grounds Freestanding Key",              {"Gerudo Training Grounds",});

//Ganons Castle
ItemLocation GanonsCastle_BossKeyChest                    = ItemLocation(0x0A, ITEMLOCATIONTYPE_CHEST,         0x0B, "Ganon's Castle Boss Key Chest",                      {"Ganon's Castle",});
ItemLocation GanonsCastle_ForestTrialChest                = ItemLocation(0x0D, ITEMLOCATIONTYPE_CHEST,         0x09, "Ganon's Castle Forest Trial Chest",                  {"Ganon's Castle",});
ItemLocation GanonsCastle_WaterTrialLeftChest             = ItemLocation(0x0D, ITEMLOCATIONTYPE_CHEST,         0x07, "Ganon's Castle Water Trial Left Chest",              {"Ganon's Castle",});
ItemLocation GanonsCastle_WaterTrialRightChest            = ItemLocation(0x0D, ITEMLOCATIONTYPE_CHEST,         0x06, "Ganon's Castle Water Trial Right Chest",             {"Ganon's Castle",});
ItemLocation GanonsCastle_ShadowTrialFrontChest           = ItemLocation(0x0D, ITEMLOCATIONTYPE_CHEST,         0x08, "Ganon's Castle Shadow Trial Front Chest",            {"Ganon's Castle",});
ItemLocation GanonsCastle_ShadowTrialGoldenGauntletsChest = ItemLocation(0x0D, ITEMLOCATIONTYPE_CHEST,         0x05, "Ganon's Castle Shadow Trial Golden Gauntlets Chest", {"Ganon's Castle",});
ItemLocation GanonsCastle_SpiritTrialCrystalSwitchChest   = ItemLocation(0x0D, ITEMLOCATIONTYPE_CHEST,         0x12, "Ganon's Castle Spirit Trial Crystal Switch Chest",   {"Ganon's Castle",});
ItemLocation GanonsCastle_SpiritTrialInvisibleChest       = ItemLocation(0x0D, ITEMLOCATIONTYPE_CHEST,         0x14, "Ganon's Castle Spirit Trial Invisible Chest",        {"Ganon's Castle",});
ItemLocation GanonsCastle_LightTrialFirstLeftChest        = ItemLocation(0x0D, ITEMLOCATIONTYPE_CHEST,         0x0C, "Ganon's Castle Light Trial First Left Chest",        {"Ganon's Castle",});
ItemLocation GanonsCastle_LightTrialSecondLeftChest       = ItemLocation(0x0D, ITEMLOCATIONTYPE_CHEST,         0x0B, "Ganon's Castle Light Trial Second Left Chest",       {"Ganon's Castle",});
ItemLocation GanonsCastle_LightTrialThirdLeftChest        = ItemLocation(0x0D, ITEMLOCATIONTYPE_CHEST,         0x0D, "Ganon's Castle Light Trial Third Left Chest",        {"Ganon's Castle",});
ItemLocation GanonsCastle_LightTrialFirstRightChest       = ItemLocation(0x0D, ITEMLOCATIONTYPE_CHEST,         0x0E, "Ganon's Castle Light Trial First Right Chest",       {"Ganon's Castle",});
ItemLocation GanonsCastle_LightTrialSecondRightChest      = ItemLocation(0x0D, ITEMLOCATIONTYPE_CHEST,         0x0A, "Ganon's Castle Light Trial Second Right Chest",      {"Ganon's Castle",});
ItemLocation GanonsCastle_LightTrialThirdRightChest       = ItemLocation(0x0D, ITEMLOCATIONTYPE_CHEST,         0x0F, "Ganon's Castle Light Trial Third Right Chest",       {"Ganon's Castle",});
ItemLocation GanonsCastle_LightTrialInvisibleEnemiesChest = ItemLocation(0x0D, ITEMLOCATIONTYPE_CHEST,         0x10, "Ganon's Castle Light Trial Invisible Enemies Chest", {"Ganon's Castle",});
ItemLocation GanonsCastle_LightTrialLullabyChest          = ItemLocation(0x0D, ITEMLOCATIONTYPE_CHEST,         0x11, "Ganon's Castle Light Trial Lullaby Chest",           {"Ganon's Castle",});
ItemLocation GanonsCastle_DekuScrubCenterLeft             = ItemLocation(0x0D, ITEMLOCATIONTYPE_BASE,           0x37, "Ganon's Castle Deku Scrub Center-Left",              {"Ganon's Castle", "Deku Scrub",});
ItemLocation GanonsCastle_DekuScrubCenterRight            = ItemLocation(0x0D, ITEMLOCATIONTYPE_BASE,           0x33, "Ganon's Castle Deku Scrub Center-Right",             {"Ganon's Castle", "Deku Scrub",});
ItemLocation GanonsCastle_DekuScrubRight                  = ItemLocation(0x0D, ITEMLOCATIONTYPE_BASE,           0x39, "Ganon's Castle Deku Scrub Right",                    {"Ganon's Castle", "Deku Scrub",});
ItemLocation GanonsCastle_DekuScrubLeft                   = ItemLocation(0x0D, ITEMLOCATIONTYPE_BASE,           0x3A, "Ganon's Castle Deku Scrub Left",                     {"Ganon's Castle", "Deku Scrub",});

/*-------------------------------
   --- GOLD SKULLTULA TOKENS ---
  -------------------------------*/

//Dungeons
ItemLocation DekuTree_GS_BasementBackRoom                 = ItemLocation(0x00, ITEMLOCATIONTYPE_GS_TOKEN,      0x01, "Deku Tree GS Basement Back Room",                  {"Deku Tree", "Skulltulas",});
ItemLocation DekuTree_GS_BasementGate                     = ItemLocation(0x00, ITEMLOCATIONTYPE_GS_TOKEN,      0x02, "Deku Tree GS Basement Gate",                       {"Deku Tree", "Skulltulas",});
ItemLocation DekuTree_GS_BasementVines                    = ItemLocation(0x00, ITEMLOCATIONTYPE_GS_TOKEN,      0x04, "Deku Tree GS Basement Vines",                      {"Deku Tree", "Skulltulas",});
ItemLocation DekuTree_GS_CompassRoom                      = ItemLocation(0x00, ITEMLOCATIONTYPE_GS_TOKEN,      0x08, "Deku Tree GS Compass Room",                        {"Deku Tree", "Skulltulas",});

ItemLocation DodongosCavern_GS_VinesAboveStairs           = ItemLocation(0x01, ITEMLOCATIONTYPE_GS_TOKEN,      0x01, "Dodongos Cavern GS Vines Above Stairs",            {"Dodongo's Cavern", "Skulltulas",});
ItemLocation DodongosCavern_GS_Scarecrow                  = ItemLocation(0x01, ITEMLOCATIONTYPE_GS_TOKEN,      0x02, "Dodongos Cavern GS Scarecrow",                     {"Dodongo's Cavern", "Skulltulas",});
ItemLocation DodongosCavern_GS_AlcoveAboveStairs          = ItemLocation(0x01, ITEMLOCATIONTYPE_GS_TOKEN,      0x04, "Dodongos Cavern GS Alcove Above Stairs",           {"Dodongo's Cavern", "Skulltulas",});
ItemLocation DodongosCavern_GS_BackRoom                   = ItemLocation(0x01, ITEMLOCATIONTYPE_GS_TOKEN,      0x08, "Dodongos Cavern GS Back Room",                     {"Dodongo's Cavern", "Skulltulas",});
ItemLocation DodongosCavern_GS_SideRoomNearLowerLizalfos  = ItemLocation(0x01, ITEMLOCATIONTYPE_GS_TOKEN,      0x10, "Dodongos Cavern GS Side Room Near Lower Lizalfos", {"Dodongo's Cavern", "Skulltulas",});

ItemLocation JabuJabusBelly_GS_LobbyBasementLower         = ItemLocation(0x02, ITEMLOCATIONTYPE_GS_TOKEN,      0x01, "Jabu Jabus Belly GS Lobby Basement Lower",         {"Jabu Jabu's Belly", "Skulltulas",});
ItemLocation JabuJabusBelly_GS_LobbyBasementUpper         = ItemLocation(0x02, ITEMLOCATIONTYPE_GS_TOKEN,      0x02, "Jabu Jabus Belly GS Lobby Basement Upper",         {"Jabu Jabu's Belly", "Skulltulas",});
ItemLocation JabuJabusBelly_GS_NearBoss                   = ItemLocation(0x02, ITEMLOCATIONTYPE_GS_TOKEN,      0x04, "Jabu Jabus Belly GS Near Boss",                    {"Jabu Jabu's Belly", "Skulltulas",});
ItemLocation JabuJabusBelly_GS_WaterSwitchRoom            = ItemLocation(0x02, ITEMLOCATIONTYPE_GS_TOKEN,      0x08, "Jabu Jabus Belly GS Water Switch Room",            {"Jabu Jabu's Belly", "Skulltulas",});

ItemLocation ForestTemple_GS_RaisedIslandCourtyard        = ItemLocation(0x03, ITEMLOCATIONTYPE_GS_TOKEN,      0x01, "Forest Temple GS Raised Island Courtyard",         {"Forest Temple", "Skulltulas",});
ItemLocation ForestTemple_GS_FirstRoom                    = ItemLocation(0x03, ITEMLOCATIONTYPE_GS_TOKEN,      0x02, "Forest Temple GS First Room",                      {"Forest Temple", "Skulltulas",});
ItemLocation ForestTemple_GS_LevelIslandCourtyard         = ItemLocation(0x03, ITEMLOCATIONTYPE_GS_TOKEN,      0x04, "Forest Temple GS Level Island Courtyard",          {"Forest Temple", "Skulltulas",});
ItemLocation ForestTemple_GS_Lobby                        = ItemLocation(0x03, ITEMLOCATIONTYPE_GS_TOKEN,      0x08, "Forest Temple GS Lobby",                           {"Forest Temple", "Skulltulas",});
ItemLocation ForestTemple_GS_Basement                     = ItemLocation(0x03, ITEMLOCATIONTYPE_GS_TOKEN,      0x10, "Forest Temple GS Basement",                        {"Forest Temple", "Skulltulas",});

ItemLocation FireTemple_GS_SongOfTimeRoom                 = ItemLocation(0x04, ITEMLOCATIONTYPE_GS_TOKEN,      0x01, "Fire Temple GS Song of Time Room",                 {"Fire Temple", "Skulltulas",});
ItemLocation FireTemple_GS_BossKeyLoop                    = ItemLocation(0x04, ITEMLOCATIONTYPE_GS_TOKEN,      0x02, "Fire Temple GS Boss Key Loop",                     {"Fire Temple", "Skulltulas",});
ItemLocation FireTemple_GS_BoulderMaze                    = ItemLocation(0x04, ITEMLOCATIONTYPE_GS_TOKEN,      0x04, "Fire Temple GS Boulder Maze",                      {"Fire Temple", "Skulltulas",});
ItemLocation FireTemple_GS_ScarecrowTop                   = ItemLocation(0x04, ITEMLOCATIONTYPE_GS_TOKEN,      0x08, "Fire Temple GS Scarecrow Top",                     {"Fire Temple", "Skulltulas",});
ItemLocation FireTemple_GS_ScarecrowClimb                 = ItemLocation(0x04, ITEMLOCATIONTYPE_GS_TOKEN,      0x10, "Fire Temple GS Scarecrow Climb",                   {"Fire Temple", "Skulltulas",});

ItemLocation WaterTemple_GS_BehindGate                    = ItemLocation(0x05, ITEMLOCATIONTYPE_GS_TOKEN,      0x01, "Water Temple GS Behind Gate",                      {"Water Temple", "Skulltulas",});
ItemLocation WaterTemple_GS_FallingPlatformRoom           = ItemLocation(0x05, ITEMLOCATIONTYPE_GS_TOKEN,      0x02, "Water Temple GS Falling Platform Room",            {"Water Temple", "Skulltulas",});
ItemLocation WaterTemple_GS_CentralPillar                 = ItemLocation(0x05, ITEMLOCATIONTYPE_GS_TOKEN,      0x04, "Water Temple GS Central Pillar",                   {"Water Temple", "Skulltulas",});
ItemLocation WaterTemple_GS_NearBossKeyChest              = ItemLocation(0x05, ITEMLOCATIONTYPE_GS_TOKEN,      0x08, "Water Temple GS Near Boss Key Chest",              {"Water Temple", "Skulltulas",});
ItemLocation WaterTemple_GS_River                         = ItemLocation(0x05, ITEMLOCATIONTYPE_GS_TOKEN,      0x10, "Water Temple GS River",                            {"Water Temple", "Skulltulas",});

ItemLocation SpiritTemple_GS_HallAfterSunBlockRoom        = ItemLocation(0x06, ITEMLOCATIONTYPE_GS_TOKEN,      0x01, "Spirit Temple GS Hall After Sun Block Room",       {"Spirit Temple", "Skulltulas"});
ItemLocation SpiritTemple_GS_BoulderRoom                  = ItemLocation(0x06, ITEMLOCATIONTYPE_GS_TOKEN,      0x02, "Spirit Temple GS Boulder Room",                    {"Spirit Temple", "Skulltulas"});
ItemLocation SpiritTemple_GS_Lobby                        = ItemLocation(0x06, ITEMLOCATIONTYPE_GS_TOKEN,      0x04, "Spirit Temple GS Lobby",                           {"Spirit Temple", "Skulltulas"});
ItemLocation SpiritTemple_GS_SunOnFloorRoom               = ItemLocation(0x06, ITEMLOCATIONTYPE_GS_TOKEN,      0x08, "Spirit Temple GS Sun on Floor Room",               {"Spirit Temple", "Skulltulas"});
ItemLocation SpiritTemple_GS_MetalFence                   = ItemLocation(0x06, ITEMLOCATIONTYPE_GS_TOKEN,      0x10, "Spirit Temple GS Metal Fence",                     {"Spirit Temple", "Skulltulas"});

ItemLocation ShadowTemple_GS_SingleGiantPot               = ItemLocation(0x07, ITEMLOCATIONTYPE_GS_TOKEN,      0x01, "Shadow Temple GS Single Giant Pot",                {"Shadow Temple", "Skulltulas",});
ItemLocation ShadowTemple_GS_FallingSpikesRoom            = ItemLocation(0x07, ITEMLOCATIONTYPE_GS_TOKEN,      0x02, "Shadow Temple GS Falling Spikes Room",             {"Shadow Temple", "Skulltulas",});
ItemLocation ShadowTemple_GS_TripleGiantPot               = ItemLocation(0x07, ITEMLOCATIONTYPE_GS_TOKEN,      0x04, "Shadow Temple GS Triple Giant Pot",                {"Shadow Temple", "Skulltulas",});
ItemLocation ShadowTemple_GS_LikeLikeRoom                 = ItemLocation(0x07, ITEMLOCATIONTYPE_GS_TOKEN,      0x08, "Shadow Temple GS Like Like Room",                  {"Shadow Temple", "Skulltulas",});
ItemLocation ShadowTemple_GS_NearShip                     = ItemLocation(0x07, ITEMLOCATIONTYPE_GS_TOKEN,      0x10, "Shadow Temple GS Near Ship",                       {"Shadow Temple", "Skulltulas",});

ItemLocation BottomOfTheWell_GS_LikeLikeCage              = ItemLocation(0x08, ITEMLOCATIONTYPE_GS_TOKEN,      0x01, "Bottom of the Well GS Like Like Cage",             {"Bottom of the Well", "Skulltulas",});
ItemLocation BottomOfTheWell_GS_EastInnerRoom             = ItemLocation(0x08, ITEMLOCATIONTYPE_GS_TOKEN,      0x02, "Bottom of the Well GS East Inner Room",            {"Bottom of the Well", "Skulltulas",});
ItemLocation BottomOfTheWell_GS_WestInnerRoom             = ItemLocation(0x08, ITEMLOCATIONTYPE_GS_TOKEN,      0x04, "Bottom of the Well GS West Inner Room",            {"Bottom of the Well", "Skulltulas",});

ItemLocation IceCavern_GS_PushBlockRoom                   = ItemLocation(0x09, ITEMLOCATIONTYPE_GS_TOKEN,      0x01, "Ice Cavern GS Push Block Room",                    {"Ice Cavern", "Skulltulas",});
ItemLocation IceCavern_GS_SpinningScytheRoom              = ItemLocation(0x09, ITEMLOCATIONTYPE_GS_TOKEN,      0x02, "Ice Cavern GS Spinning Scythe Room",               {"Ice Cavern", "Skulltulas",});
ItemLocation IceCavern_GS_HeartPieceRoom                  = ItemLocation(0x09, ITEMLOCATIONTYPE_GS_TOKEN,      0x04, "Ice Cavern GS Heart Piece Room",                   {"Ice Cavern", "Skulltulas",});

//Overworld
ItemLocation KF_GS_BeanPatch                              = ItemLocation(0x0C, ITEMLOCATIONTYPE_GS_TOKEN,      0x01, "KF GS Bean Patch",                                 {"Kokiri Forest", "Skulltulas",});
ItemLocation KF_GS_KnowItAllHouse                         = ItemLocation(0x0C, ITEMLOCATIONTYPE_GS_TOKEN,      0x02, "KF GS Know It All House",                          {"Kokiri Forest", "Skulltulas",});
ItemLocation KF_GS_HouseOfTwins                           = ItemLocation(0x0C, ITEMLOCATIONTYPE_GS_TOKEN,      0x04, "KF GS House of Twins",                             {"Kokiri Forest", "Skulltulas",});

ItemLocation LW_GS_BeanPatchNearBridge                    = ItemLocation(0x0D, ITEMLOCATIONTYPE_GS_TOKEN,      0x01, "LW GS Bean Patch Near Bridge",                     {"the Lost Woods", "Skulltulas",});
ItemLocation LW_GS_BeanPatchNearTheater                   = ItemLocation(0x0D, ITEMLOCATIONTYPE_GS_TOKEN,      0x02, "LW GS Bean Patch Near Theater",                    {"the Lost Woods", "Skulltulas",});
ItemLocation LW_GS_AboveTheater                           = ItemLocation(0x0D, ITEMLOCATIONTYPE_GS_TOKEN,      0x04, "LW GS Above Theater",                              {"the Lost Woods", "Skulltulas",});
ItemLocation SFM_GS                                       = ItemLocation(0x0D, ITEMLOCATIONTYPE_GS_TOKEN,      0x08, "SFM GS",                                           {"Sacred Forest Meadow", "Skulltulas",});

ItemLocation HF_GS_CowGrotto                              = ItemLocation(0x0A, ITEMLOCATIONTYPE_GS_TOKEN,      0x01, "HF GS Cow Grotto",                                 {"Hyrule Field", "Skulltulas", "Grottos"});
ItemLocation HF_GS_NearKakGrotto                          = ItemLocation(0x0A, ITEMLOCATIONTYPE_GS_TOKEN,      0x02, "HF GS Near Kak Grotto",                            {"Hyrule Field", "Skulltulas", "Grottos"});

ItemLocation LH_GS_BeanPatch                              = ItemLocation(0x12, ITEMLOCATIONTYPE_GS_TOKEN,      0x01, "LH GS Bean Patch",                                 {"Lake Hylia", "Skulltulas",});
ItemLocation LH_GS_SmallIsland                            = ItemLocation(0x12, ITEMLOCATIONTYPE_GS_TOKEN,      0x02, "LH GS Small Island",                               {"Lake Hylia", "Skulltulas",});
ItemLocation LH_GS_LabWall                                = ItemLocation(0x12, ITEMLOCATIONTYPE_GS_TOKEN,      0x04, "LH GS Lab Wall",                                   {"Lake Hylia", "Skulltulas",});
ItemLocation LH_GS_LabCrate                               = ItemLocation(0x12, ITEMLOCATIONTYPE_GS_TOKEN,      0x08, "LH GS Lab Crate",                                  {"Lake Hylia", "Skulltulas",});
ItemLocation LH_GS_Tree                                   = ItemLocation(0x12, ITEMLOCATIONTYPE_GS_TOKEN,      0x10, "LH GS Tree",                                       {"Lake Hylia", "Skulltulas",});

ItemLocation GV_GS_BeanPatch                              = ItemLocation(0x13, ITEMLOCATIONTYPE_GS_TOKEN,      0x01, "GV GS Bean Patch",                                 {"Gerudo Valley", "Skulltulas",});
ItemLocation GV_GS_SmallBridge                            = ItemLocation(0x13, ITEMLOCATIONTYPE_GS_TOKEN,      0x02, "GV GS Small Bridge",                               {"Gerudo Valley", "Skulltulas",});
ItemLocation GV_GS_Pillar                                 = ItemLocation(0x13, ITEMLOCATIONTYPE_GS_TOKEN,      0x04, "GV GS Pillar",                                     {"Gerudo Valley", "Skulltulas",});
ItemLocation GV_GS_BehindTent                             = ItemLocation(0x13, ITEMLOCATIONTYPE_GS_TOKEN,      0x08, "GV GS Behind Tent",                                {"Gerudo Valley", "Skulltulas",});

ItemLocation GF_GS_ArcheryRange                           = ItemLocation(0x14, ITEMLOCATIONTYPE_GS_TOKEN,      0x01, "GF GS Archery Range",                              {"Gerudo's Fortress", "Skulltulas",});
ItemLocation GF_GS_TopFloor                               = ItemLocation(0x14, ITEMLOCATIONTYPE_GS_TOKEN,      0x02, "GF GS Top Floor",                                  {"Gerudo's Fortress", "Skulltulas",});

ItemLocation HW_GS                                        = ItemLocation(0x15, ITEMLOCATIONTYPE_GS_TOKEN,      0x02, "HW GS",                                            {"Haunted Wasteland", "Skulltulas",});
ItemLocation Colossus_GS_BeanPatch                        = ItemLocation(0x15, ITEMLOCATIONTYPE_GS_TOKEN,      0x01, "Colossus GS Bean Patch",                           {"Desert Colossus", "Skulltulas",});
ItemLocation Colossus_GS_Hill                             = ItemLocation(0x15, ITEMLOCATIONTYPE_GS_TOKEN,      0x04, "Colossus GS Hill",                                 {"Desert Colossus", "Skulltulas",});
ItemLocation Colossus_GS_Tree                             = ItemLocation(0x15, ITEMLOCATIONTYPE_GS_TOKEN,      0x08, "Colossus GS Tree",                                 {"Desert Colossus", "Skulltulas",});

ItemLocation OGC_GS                                       = ItemLocation(0x0E, ITEMLOCATIONTYPE_GS_TOKEN,      0x01, "OGC GS",                                           {"outside Ganon's Castle", "Skulltulas",});
ItemLocation HC_GS_StormsGrotto                           = ItemLocation(0x0E, ITEMLOCATIONTYPE_GS_TOKEN,      0x02, "HC GS Storms Grotto",                              {"Hyrule Castle", "Skulltulas", "Grottos"});
ItemLocation HC_GS_Tree                                   = ItemLocation(0x0E, ITEMLOCATIONTYPE_GS_TOKEN,      0x04, "HC GS Tree",                                       {"Hyrule Castle", "Skulltulas",});
ItemLocation MK_GS_GuardHouse                             = ItemLocation(0x0E, ITEMLOCATIONTYPE_GS_TOKEN,      0x08, "Market GS Guard House",                            {"the Market", "Skulltulas",});

ItemLocation Kak_GS_HouseUnderConstruction                = ItemLocation(0x10, ITEMLOCATIONTYPE_GS_TOKEN,      0x08, "Kak GS House Under Construction",                  {"Kakariko Village", "Skulltulas",});
ItemLocation Kak_GS_SkulltulaHouse                        = ItemLocation(0x10, ITEMLOCATIONTYPE_GS_TOKEN,      0x10, "Kak GS Skulltula House",                           {"Kakariko Village", "Skulltulas",});
ItemLocation Kak_GS_GuardsHouse                           = ItemLocation(0x10, ITEMLOCATIONTYPE_GS_TOKEN,      0x02, "Kak GS Guards House",                              {"Kakariko Village", "Skulltulas",});
ItemLocation Kak_GS_Tree                                  = ItemLocation(0x10, ITEMLOCATIONTYPE_GS_TOKEN,      0x20, "Kak GS Tree",                                      {"Kakariko Village", "Skulltulas",});
ItemLocation Kak_GS_Watchtower                            = ItemLocation(0x10, ITEMLOCATIONTYPE_GS_TOKEN,      0x04, "Kak GS Watchtower",                                {"Kakariko Village", "Skulltulas",});
ItemLocation Kak_GS_AboveImpasHouse                       = ItemLocation(0x10, ITEMLOCATIONTYPE_GS_TOKEN,      0x40, "Kak GS Above Impas House",                         {"Kakariko Village", "Skulltulas",});

ItemLocation GY_GS_Wall                                   = ItemLocation(0x10, ITEMLOCATIONTYPE_GS_TOKEN,      0x80, "Graveyard GS Wall",                                {"the Graveyard", "Skulltulas",});
ItemLocation GY_GS_BeanPatch                              = ItemLocation(0x10, ITEMLOCATIONTYPE_GS_TOKEN,      0x01, "Graveyard GS Bean Patch",                          {"the Graveyard", "Skulltulas",});

ItemLocation DMC_GS_BeanPatch                             = ItemLocation(0x0F, ITEMLOCATIONTYPE_GS_TOKEN,      0x01, "DMC GS Bean Patch",                                {"Death Mountain Crater", "Skulltulas",});
ItemLocation DMC_GS_Crate                                 = ItemLocation(0x0F, ITEMLOCATIONTYPE_GS_TOKEN,      0x80, "DMC GS Crate",                                     {"Death Mountain Crater", "Skulltulas",});

ItemLocation DMT_GS_BeanPatch                             = ItemLocation(0x0F, ITEMLOCATIONTYPE_GS_TOKEN,      0x02, "DMT GS Bean Patch",                                {"Death Mountain Trail", "Skulltulas",});
ItemLocation DMT_GS_NearKak                               = ItemLocation(0x0F, ITEMLOCATIONTYPE_GS_TOKEN,      0x04, "DMT GS Near Kak",                                  {"Death Mountain Trail", "Skulltulas",});
ItemLocation DMT_GS_AboveDodongosCavern                   = ItemLocation(0x0F, ITEMLOCATIONTYPE_GS_TOKEN,      0x08, "DMT GS Above Dodongos Cavern",                     {"Death Mountain Trail", "Skulltulas",});
ItemLocation DMT_GS_FallingRocksPath                      = ItemLocation(0x0F, ITEMLOCATIONTYPE_GS_TOKEN,      0x10, "DMT GS Falling Rocks Path",                        {"Death Mountain Trail", "Skulltulas",});

ItemLocation GC_GS_CenterPlatform                         = ItemLocation(0x0F, ITEMLOCATIONTYPE_GS_TOKEN,      0x20, "GC GS Center Platform",                            {"Goron City", "Skulltulas",});
ItemLocation GC_GS_BoulderMaze                            = ItemLocation(0x0F, ITEMLOCATIONTYPE_GS_TOKEN,      0x40, "GC GS Boulder Maze",                               {"Goron City", "Skulltulas",});

ItemLocation ZR_GS_Ladder                                 = ItemLocation(0x11, ITEMLOCATIONTYPE_GS_TOKEN,      0x01, "ZR GS Ladder",                                     {"Zora's River", "Skulltulas",});
ItemLocation ZR_GS_Tree                                   = ItemLocation(0x11, ITEMLOCATIONTYPE_GS_TOKEN,      0x02, "ZR GS Tree",                                       {"Zora's River", "Skulltulas",});
ItemLocation ZR_GS_AboveBridge                            = ItemLocation(0x11, ITEMLOCATIONTYPE_GS_TOKEN,      0x08, "ZR GS Above Bridge",                               {"Zora's River", "Skulltulas",});
ItemLocation ZR_GS_NearRaisedGrottos                      = ItemLocation(0x11, ITEMLOCATIONTYPE_GS_TOKEN,      0x10, "ZR GS Near Raised Grottos",                        {"Zora's River", "Skulltulas",});

ItemLocation ZD_GS_FrozenWaterfall                        = ItemLocation(0x11, ITEMLOCATIONTYPE_GS_TOKEN,      0x40, "ZD GS Frozen Waterfall",                           {"Zora's Domain", "Skulltulas",});
ItemLocation ZF_GS_AboveTheLog                            = ItemLocation(0x11, ITEMLOCATIONTYPE_GS_TOKEN,      0x04, "ZF GS Above The Log",                              {"Zora's Fountain", "Skulltulas",});
ItemLocation ZF_GS_HiddenCave                             = ItemLocation(0x11, ITEMLOCATIONTYPE_GS_TOKEN,      0x20, "ZF GS Hidden Cave",                                {"Zora's Fountain", "Skulltulas",});
ItemLocation ZF_GS_Tree                                   = ItemLocation(0x11, ITEMLOCATIONTYPE_GS_TOKEN,      0x80, "ZF GS Tree",                                       {"Zora's Fountain", "Skulltulas",});

ItemLocation LLR_GS_BackWall                              = ItemLocation(0x0B, ITEMLOCATIONTYPE_GS_TOKEN,      0x01, "LLR GS Back Wall",                                 {"Lon Lon Ranch", "Skulltulas",});
ItemLocation LLR_GS_RainShed                              = ItemLocation(0x0B, ITEMLOCATIONTYPE_GS_TOKEN,      0x02, "LLR GS Rain Shed",                                 {"Lon Lon Ranch", "Skulltulas",});
ItemLocation LLR_GS_HouseWindow                           = ItemLocation(0x0B, ITEMLOCATIONTYPE_GS_TOKEN,      0x04, "LLR GS House Window",                              {"Lon Lon Ranch", "Skulltulas",});
ItemLocation LLR_GS_Tree                                  = ItemLocation(0x0B, ITEMLOCATIONTYPE_GS_TOKEN,      0x08, "LLR GS Tree",                                      {"Lon Lon Ranch", "Skulltulas",});

/*-------------------------------
          --- BOSSES ---
  -------------------------------*/

ItemLocation LinksPocket                                  = ItemLocation(0xFF, ITEMLOCATIONTYPE_TEMPLE_REWARD, 0xFF, "Link's Pocket",                                    {});
ItemLocation QueenGohma                                   = ItemLocation(0xFF, ITEMLOCATIONTYPE_TEMPLE_REWARD, 0xFF, "Queen Gohma",                                      {});
ItemLocation KingDodongo                                  = ItemLocation(0xFF, ITEMLOCATIONTYPE_TEMPLE_REWARD, 0xFF, "King Dodongo",                                     {});
ItemLocation Barinade                                     = ItemLocation(0xFF, ITEMLOCATIONTYPE_TEMPLE_REWARD, 0xFF, "Barinade",                                         {});
ItemLocation PhantomGanon                                 = ItemLocation(0xFF, ITEMLOCATIONTYPE_TEMPLE_REWARD, 0xFF, "Phantom Ganon",                                    {});
ItemLocation Volvagia                                     = ItemLocation(0xFF, ITEMLOCATIONTYPE_TEMPLE_REWARD, 0xFF, "Volvagia",                                         {});
ItemLocation Morpha                                       = ItemLocation(0xFF, ITEMLOCATIONTYPE_TEMPLE_REWARD, 0xFF, "Morpha",                                           {});
ItemLocation Twinrova                                     = ItemLocation(0xFF, ITEMLOCATIONTYPE_TEMPLE_REWARD, 0xFF, "Twinrova",                                         {});
ItemLocation BongoBongo                                   = ItemLocation(0xFF, ITEMLOCATIONTYPE_TEMPLE_REWARD, 0xFF, "Bongo Bongo",                                      {});

/*-------------------------------
        --- CUTSCENES ---
  -------------------------------*/

ItemLocation ToT_LightArrowCutscene                       = ItemLocation(0xFF, ITEMLOCATIONTYPE_DELAYED,       0x01, "ToT Light Arrow Cutscene",                         {"Temple of Time", "Market"});
ItemLocation LW_GiftFromSaria                             = ItemLocation(0xFF, ITEMLOCATIONTYPE_DELAYED,       0x02, "LW Gift From Saria",                               {"the Lost Woods", "Forest"});
ItemLocation ZF_GreatFairyReward                          = ItemLocation(0xFF, ITEMLOCATIONTYPE_DELAYED,       0x10, "ZF Great Fairy Reward",                            {"Zora's Fountain", "Fairies"});
ItemLocation HC_GreatFairyReward                          = ItemLocation(0xFF, ITEMLOCATIONTYPE_DELAYED,       0x11, "HC Great Fairy Reward",                            {"Hyrule Castle", "Market", "Fairies"});
ItemLocation Colossus_GreatFairyReward                    = ItemLocation(0xFF, ITEMLOCATIONTYPE_DELAYED,       0x12, "Colossus Great Fairy Reward",                      {"Desert Colossus", "Fairies"});
ItemLocation DMT_GreatFairyReward                         = ItemLocation(0xFF, ITEMLOCATIONTYPE_DELAYED,       0x13, "DMT Great Fairy Reward",                           {"Death Mountain Trail", "Death Mountain", "Fairies"});
ItemLocation DMC_GreatFairyReward                         = ItemLocation(0xFF, ITEMLOCATIONTYPE_DELAYED,       0x14, "DMC Great Fairy Reward",                           {"Death Mountain Crater", "Death Mountain", "Fairies"});
ItemLocation OGC_GreatFairyReward                         = ItemLocation(0xFF, ITEMLOCATIONTYPE_DELAYED,       0x15, "OGC Great Fairy Reward",                           {"outside Ganon's Castle", "Market", "Fairies"});

//key requirements for placing randomized keys and other items in dungeons
const std::array<ItemLocationKeyPairing, 10> DekuTreeKeyRequirements{{
  ItemLocationKeyPairing(&DekuTree_MapChest,               0),
  ItemLocationKeyPairing(&DekuTree_CompassChest,           0),
  ItemLocationKeyPairing(&DekuTree_CompassRoomSideChest,   0),
  ItemLocationKeyPairing(&DekuTree_BasementChest,          0),
  ItemLocationKeyPairing(&DekuTree_SlingshotChest,         0),
  ItemLocationKeyPairing(&DekuTree_SlingshotRoomSideChest, 0),
  ItemLocationKeyPairing(&DekuTree_GS_CompassRoom,         0),
  ItemLocationKeyPairing(&DekuTree_GS_BasementVines,       0),
  ItemLocationKeyPairing(&DekuTree_GS_BasementGate,        0),
  ItemLocationKeyPairing(&DekuTree_GS_BasementBackRoom,    0),
}};
const std::array<ItemLocationKeyPairing, 11> DodongosCavernKeyRequirements{{
  ItemLocationKeyPairing(&DodongosCavern_MapChest,                     0),
  ItemLocationKeyPairing(&DodongosCavern_CompassChest,                 0),
  ItemLocationKeyPairing(&DodongosCavern_GS_SideRoomNearLowerLizalfos, 0),
  ItemLocationKeyPairing(&DodongosCavern_GS_Scarecrow,                 0),
  ItemLocationKeyPairing(&DodongosCavern_BombFlowerPlatformChest,      0),
  ItemLocationKeyPairing(&DodongosCavern_GS_VinesAboveStairs,          0),
  ItemLocationKeyPairing(&DodongosCavern_BombBagChest,                 0),
  ItemLocationKeyPairing(&DodongosCavern_EndOfBridgeChest,             0),
  ItemLocationKeyPairing(&DodongosCavern_GS_AlcoveAboveStairs,         0),
  ItemLocationKeyPairing(&DodongosCavern_BossRoomChest,                0),
  ItemLocationKeyPairing(&DodongosCavern_GS_BackRoom,                  0),
}};
const std::array<ItemLocationKeyPairing, 7> JabuJabusBellyKeyRequirements{{
  ItemLocationKeyPairing(&JabuJabusBelly_BoomerangChest,        0),
  ItemLocationKeyPairing(&JabuJabusBelly_MapChest,              0),
  ItemLocationKeyPairing(&JabuJabusBelly_CompassChest,          0),
  ItemLocationKeyPairing(&JabuJabusBelly_GS_WaterSwitchRoom,    0),
  ItemLocationKeyPairing(&JabuJabusBelly_GS_LobbyBasementLower, 0),
  ItemLocationKeyPairing(&JabuJabusBelly_GS_LobbyBasementUpper, 0),
  ItemLocationKeyPairing(&JabuJabusBelly_GS_NearBoss,           0),
}};
const std::array<ItemLocationKeyPairing, 19> ForestTempleKeyRequirements{{
  ItemLocationKeyPairing(&ForestTemple_FirstRoomChest,             0),
  ItemLocationKeyPairing(&ForestTemple_FirstStalfosChest,          0),
  ItemLocationKeyPairing(&ForestTemple_GS_FirstRoom,               0),
  ItemLocationKeyPairing(&ForestTemple_GS_Lobby,                   0),
  ItemLocationKeyPairing(&ForestTemple_RaisedIslandCourtyardChest, 0),
  ItemLocationKeyPairing(&ForestTemple_GS_RaisedIslandCourtyard,   0),
  ItemLocationKeyPairing(&ForestTemple_GS_LevelIslandCourtyard,    0),
  ItemLocationKeyPairing(&ForestTemple_MapChest,                   0),
  ItemLocationKeyPairing(&ForestTemple_WellChest,                  0),
  ItemLocationKeyPairing(&ForestTemple_EyeSwitchChest,             1),
  ItemLocationKeyPairing(&ForestTemple_FloormasterChest,           1),
  ItemLocationKeyPairing(&ForestTemple_BossKeyChest,               2),
  ItemLocationKeyPairing(&ForestTemple_BowChest,                   3),
  ItemLocationKeyPairing(&ForestTemple_RedPoeChest,                3),
  ItemLocationKeyPairing(&ForestTemple_BluePoeChest,               3),
  ItemLocationKeyPairing(&ForestTemple_FallingCeilingRoomChest,    5),
  ItemLocationKeyPairing(&ForestTemple_BasementChest,              5),
  ItemLocationKeyPairing(&ForestTemple_GS_Basement,                5),
  ItemLocationKeyPairing(&ForestTemple_PhantomGanonHeart,          5),
}};
const std::array<ItemLocationKeyPairing, 20> FireTempleKeyRequirements{{
  ItemLocationKeyPairing(&FireTemple_NearBossChest,                 0),
  ItemLocationKeyPairing(&FireTemple_VolvagiaHeart,                 0),
  ItemLocationKeyPairing(&FireTemple_FlareDancerChest,              0),
  ItemLocationKeyPairing(&FireTemple_BossKeyChest,                  0),
  ItemLocationKeyPairing(&FireTemple_GS_BossKeyLoop,                0),
  ItemLocationKeyPairing(&FireTemple_BigLavaRoomLowerOpenDoorChest, 1),
  ItemLocationKeyPairing(&FireTemple_BigLavaRoomBlockedDoorChest,   1),
  ItemLocationKeyPairing(&FireTemple_GS_SongOfTimeRoom,             1),
  ItemLocationKeyPairing(&FireTemple_BoulderMazeLowerChest,         4),
  ItemLocationKeyPairing(&FireTemple_BoulderMazeSideRoomChest,      4),
  ItemLocationKeyPairing(&FireTemple_GS_BoulderMaze,                4),
  ItemLocationKeyPairing(&FireTemple_MapChest,                      5),
  ItemLocationKeyPairing(&FireTemple_BoulderMazeUpperChest,         6),
  ItemLocationKeyPairing(&FireTemple_BoulderMazeShortcutChest,      6),
  ItemLocationKeyPairing(&FireTemple_ScarecrowChest,                6),
  ItemLocationKeyPairing(&FireTemple_CompassChest,                  6),
  ItemLocationKeyPairing(&FireTemple_GS_ScarecrowClimb,             6),
  ItemLocationKeyPairing(&FireTemple_GS_ScarecrowTop,               6),
  ItemLocationKeyPairing(&FireTemple_HighestGoronChest,             7),
  ItemLocationKeyPairing(&FireTemple_MegatonHammerChest,            7),
}};
const std::array<ItemLocationKeyPairing, 16> WaterTempleKeyRequirements{{
  ItemLocationKeyPairing(&WaterTemple_MorphaHeart,            0),
  ItemLocationKeyPairing(&WaterTemple_MapChest,               0),
  ItemLocationKeyPairing(&WaterTemple_CompassChest,           0),
  ItemLocationKeyPairing(&WaterTemple_TorchesChest,           0),
  ItemLocationKeyPairing(&WaterTemple_CentralBowTargetChest,  0),
  ItemLocationKeyPairing(&WaterTemple_GS_BehindGate,          0),
  ItemLocationKeyPairing(&WaterTemple_CrackedWallChest,       0),
  ItemLocationKeyPairing(&WaterTemple_DragonChest,            0),
  ItemLocationKeyPairing(&WaterTemple_CentralPillarChest,     0),
  ItemLocationKeyPairing(&WaterTemple_GS_CentralPillar,       0),
  ItemLocationKeyPairing(&WaterTemple_GS_NearBossKeyChest,    4),
  ItemLocationKeyPairing(&WaterTemple_GS_FallingPlatformRoom, 4),
  ItemLocationKeyPairing(&WaterTemple_LongshotChest,          5),
  ItemLocationKeyPairing(&WaterTemple_RiverChest,             5),
  ItemLocationKeyPairing(&WaterTemple_GS_River,               5),
  ItemLocationKeyPairing(&WaterTemple_BossKeyChest,           5),
}};
const std::array<ItemLocationKeyPairing, 26> SpiritTempleKeyRequirements{{
  ItemLocationKeyPairing(&SpiritTemple_ChildBridgeChest,           0),
  ItemLocationKeyPairing(&SpiritTemple_ChildEarlyTorchesChest,     0),
  ItemLocationKeyPairing(&SpiritTemple_GS_MetalFence,              0),
  ItemLocationKeyPairing(&SpiritTemple_CompassChest,               0),
  ItemLocationKeyPairing(&SpiritTemple_EarlyAdultRightChest,       0),
  ItemLocationKeyPairing(&SpiritTemple_GS_BoulderRoom,             0),
  ItemLocationKeyPairing(&SpiritTemple_ChildClimbNorthChest,       1),
  ItemLocationKeyPairing(&SpiritTemple_ChildClimbEastChest,        1),
  ItemLocationKeyPairing(&SpiritTemple_GS_SunOnFloorRoom,          3),
  ItemLocationKeyPairing(&SpiritTemple_MapChest,                   3),
  ItemLocationKeyPairing(&SpiritTemple_SunBlockRoomChest,          3),
  ItemLocationKeyPairing(&SpiritTemple_StatueRoomHandChest,        3),
  ItemLocationKeyPairing(&SpiritTemple_FirstMirrorLeftChest,       3),
  ItemLocationKeyPairing(&SpiritTemple_FirstMirrorRightChest,      3),
  ItemLocationKeyPairing(&SpiritTemple_StatueRoomHandChest,        3),
  ItemLocationKeyPairing(&SpiritTemple_StatueRoomNortheastChest,   3),
  ItemLocationKeyPairing(&SpiritTemple_GS_HallAfterSunBlockRoom,   3),
  ItemLocationKeyPairing(&SpiritTemple_GS_Lobby,                   3),
  ItemLocationKeyPairing(&SpiritTemple_SilverGauntletsChest,       3),
  ItemLocationKeyPairing(&SpiritTemple_MirrorShieldChest,          4),
  ItemLocationKeyPairing(&SpiritTemple_NearFourArmosChest,         4),
  ItemLocationKeyPairing(&SpiritTemple_HallwayLeftInvisibleChest,  4),
  ItemLocationKeyPairing(&SpiritTemple_HallwayRightInvisibleChest, 4),
  ItemLocationKeyPairing(&SpiritTemple_BossKeyChest,               5),
  ItemLocationKeyPairing(&SpiritTemple_TopmostChest,               5),
  ItemLocationKeyPairing(&SpiritTemple_TwinrovaHeart,              5),
}};
const std::array<ItemLocationKeyPairing, 23> ShadowTempleKeyRequirements = {
  ItemLocationKeyPairing(&ShadowTemple_MapChest,                      0),
  ItemLocationKeyPairing(&ShadowTemple_HoverBootsChest,               0),
  ItemLocationKeyPairing(&ShadowTemple_CompassChest,                  0),
  ItemLocationKeyPairing(&ShadowTemple_EarlySilverRupeeChest,         0),
  ItemLocationKeyPairing(&ShadowTemple_InvisibleBladesVisibleChest,   1),
  ItemLocationKeyPairing(&ShadowTemple_InvisibleBladesInvisibleChest, 1),
  ItemLocationKeyPairing(&ShadowTemple_FallingSpikesLowerChest,       1),
  ItemLocationKeyPairing(&ShadowTemple_FallingSpikesUpperChest,       1),
  ItemLocationKeyPairing(&ShadowTemple_FallingSpikesSwitchChest,      1),
  ItemLocationKeyPairing(&ShadowTemple_GS_LikeLikeRoom,               1),
  ItemLocationKeyPairing(&ShadowTemple_GS_FallingSpikesRoom,          1),
  ItemLocationKeyPairing(&ShadowTemple_InvisibleSpikesChest,          2),
  ItemLocationKeyPairing(&ShadowTemple_FreestandingKey,               2),
  ItemLocationKeyPairing(&ShadowTemple_GS_SingleGiantPot,             2),
  ItemLocationKeyPairing(&ShadowTemple_WindHintChest,                 3),
  ItemLocationKeyPairing(&ShadowTemple_AfterWindEnemyChest,           3),
  ItemLocationKeyPairing(&ShadowTemple_AfterWindHiddenChest,          3),
  ItemLocationKeyPairing(&ShadowTemple_GS_NearShip,                   4),
  ItemLocationKeyPairing(&ShadowTemple_SpikeWallsLeftChest,           4),
  ItemLocationKeyPairing(&ShadowTemple_BossKeyChest,                  4),
  ItemLocationKeyPairing(&ShadowTemple_InvisibleFloormasterChest,     4),
  ItemLocationKeyPairing(&ShadowTemple_GS_TripleGiantPot,             4),
  ItemLocationKeyPairing(&ShadowTemple_BongoBongoHeart,               5),
};
const std::array<ItemLocationKeyPairing, 17> BottomOfTheWellKeyRequirements{{
  ItemLocationKeyPairing(&BottomOfTheWell_FrontLeftFakeWallChest,   0),
  ItemLocationKeyPairing(&BottomOfTheWell_FrontCenterBombableChest, 0),
  ItemLocationKeyPairing(&BottomOfTheWell_RightBottomFakeWallChest, 0),
  ItemLocationKeyPairing(&BottomOfTheWell_CompassChest,             0),
  ItemLocationKeyPairing(&BottomOfTheWell_CenterSkulltulaChest,     0),
  ItemLocationKeyPairing(&BottomOfTheWell_BackLeftBombableChest,    0),
  ItemLocationKeyPairing(&BottomOfTheWell_FreestandingKey,          0),
  ItemLocationKeyPairing(&BottomOfTheWell_LensOfTruthChest,         0),
  ItemLocationKeyPairing(&BottomOfTheWell_InvisibleChest,           0),
  ItemLocationKeyPairing(&BottomOfTheWell_UnderwaterFrontChest,     0),
  ItemLocationKeyPairing(&BottomOfTheWell_UnderwaterLeftChest,      0),
  ItemLocationKeyPairing(&BottomOfTheWell_MapChest,                 0),
  ItemLocationKeyPairing(&BottomOfTheWell_FireKeeseChest,           3),
  ItemLocationKeyPairing(&BottomOfTheWell_LikeLikeChest,            3),
  ItemLocationKeyPairing(&BottomOfTheWell_GS_WestInnerRoom,         3),
  ItemLocationKeyPairing(&BottomOfTheWell_GS_EastInnerRoom,         3),
  ItemLocationKeyPairing(&BottomOfTheWell_GS_LikeLikeCage,          3),
}};
const std::array<ItemLocationKeyPairing, 7> IceCavernKeyRequirements = {
  ItemLocationKeyPairing(&IceCavern_MapChest,              0),
  ItemLocationKeyPairing(&IceCavern_CompassChest,          0),
  ItemLocationKeyPairing(&IceCavern_IronBootsChest,        0),
  ItemLocationKeyPairing(&IceCavern_FreestandingPoH,       0),
  ItemLocationKeyPairing(&IceCavern_GS_SpinningScytheRoom, 0),
  ItemLocationKeyPairing(&IceCavern_GS_HeartPieceRoom,     0),
  ItemLocationKeyPairing(&IceCavern_GS_PushBlockRoom,      0),
};
const std::array<ItemLocationKeyPairing, 22> GerudoTrainingGroundsKeyRequirements = {
  ItemLocationKeyPairing(&GerudoTrainingGrounds_LobbyLeftChest,             0),
  ItemLocationKeyPairing(&GerudoTrainingGrounds_LobbyRightChest,            0),
  ItemLocationKeyPairing(&GerudoTrainingGrounds_StalfosChest,               0),
  ItemLocationKeyPairing(&GerudoTrainingGrounds_BeamosChest,                0),
  ItemLocationKeyPairing(&GerudoTrainingGrounds_MazeRightCentralChest,      0),
  ItemLocationKeyPairing(&GerudoTrainingGrounds_MazeRightSideChest,         0),
  ItemLocationKeyPairing(&GerudoTrainingGrounds_FreestandingKey,            0),
  ItemLocationKeyPairing(&GerudoTrainingGrounds_UnderwaterSilverRupeeChest, 0),
  ItemLocationKeyPairing(&GerudoTrainingGrounds_HammerRoomClearChest,       0),
  ItemLocationKeyPairing(&GerudoTrainingGrounds_HammerRoomSwitchChest,      0),
  ItemLocationKeyPairing(&GerudoTrainingGrounds_EyeStatueChest,             0),
  ItemLocationKeyPairing(&GerudoTrainingGrounds_NearScarecrowChest,         0),
  ItemLocationKeyPairing(&GerudoTrainingGrounds_BeforeHeavyBlockChest,      0),
  ItemLocationKeyPairing(&GerudoTrainingGrounds_HeavyBlockFirstChest,       0),
  ItemLocationKeyPairing(&GerudoTrainingGrounds_HeavyBlockSecondChest,      0),
  ItemLocationKeyPairing(&GerudoTrainingGrounds_HeavyBlockThirdChest,       0),
  ItemLocationKeyPairing(&GerudoTrainingGrounds_HeavyBlockFourthChest,      0),
  ItemLocationKeyPairing(&GerudoTrainingGrounds_HiddenCeilingChest,         3),
  ItemLocationKeyPairing(&GerudoTrainingGrounds_MazePathFirstChest,         4),
  ItemLocationKeyPairing(&GerudoTrainingGrounds_MazePathSecondChest,        6),
  ItemLocationKeyPairing(&GerudoTrainingGrounds_MazePathThirdChest,         7),
  ItemLocationKeyPairing(&GerudoTrainingGrounds_MazePathFinalChest,         9),
};
const std::array<ItemLocationKeyPairing, 16> GanonsCastleKeyRequirements{{
  ItemLocationKeyPairing(&GanonsCastle_ForestTrialChest,                0),
  ItemLocationKeyPairing(&GanonsCastle_WaterTrialLeftChest,             0),
  ItemLocationKeyPairing(&GanonsCastle_WaterTrialRightChest,            0),
  ItemLocationKeyPairing(&GanonsCastle_ShadowTrialFrontChest,           0),
  ItemLocationKeyPairing(&GanonsCastle_ShadowTrialGoldenGauntletsChest, 0),
  ItemLocationKeyPairing(&GanonsCastle_SpiritTrialCrystalSwitchChest,   0),
  ItemLocationKeyPairing(&GanonsCastle_SpiritTrialInvisibleChest,       0),
  ItemLocationKeyPairing(&GanonsCastle_LightTrialFirstLeftChest,        0),
  ItemLocationKeyPairing(&GanonsCastle_LightTrialSecondLeftChest,       0),
  ItemLocationKeyPairing(&GanonsCastle_LightTrialThirdLeftChest,        0),
  ItemLocationKeyPairing(&GanonsCastle_LightTrialFirstRightChest,       0),
  ItemLocationKeyPairing(&GanonsCastle_LightTrialSecondRightChest,      0),
  ItemLocationKeyPairing(&GanonsCastle_LightTrialThirdRightChest,       0),
  ItemLocationKeyPairing(&GanonsCastle_LightTrialInvisibleEnemiesChest, 0),
  ItemLocationKeyPairing(&GanonsCastle_LightTrialLullabyChest,          1),
  ItemLocationKeyPairing(&GanonsCastle_BossKeyChest,                    2),
}};

std::vector<ItemLocation *> advancementLocations = {};
std::array<ItemLocation*, 9> dungeonRewardLocations = {
  //Bosses
  &LinksPocket,
  &QueenGohma,
  &KingDodongo,
  &Barinade,
  &PhantomGanon,
  &Volvagia,
  &Morpha,
  &Twinrova,
  &BongoBongo,
};
std::array<ItemLocation*, 338> allLocations = {

  //Kokiri Forest
  &KF_KokiriSwordChest,
  &KF_MidoTopLeftChest,
  &KF_MidoTopRightChest,
  &KF_MidoBottomLeftChest,
  &KF_MidoBottomRightChest,
  &KF_StormsGrottoChest,

  //Lost Woods
  &LW_SkullKid,
  //&LW_OcarinaMemoryGame,
  &LW_TargetInWoods,
  //&LW_DekuScrubNearDekuTheaterRight,
  //&LW_DekuScrubNearDekuTheaterLeft,
  //&LW_DekuScrubNearBridge,
  //&LW_GossipStone,
  &LW_NearShortcutsGrottoChest,
  //&LW_DekuScrubGrottoRear,
  //&LW_DekuScrubGrottoFront,
  //&DekuTheater_SkullMask,
  //&DekuTheater_MaskOfTruth,

  //Sacred Forest Meadow
  &SFM_WolfosGrottoChest,
  //&SFM_DekuScrubGrottoRear,
  //&SFM_DekuScrubGrottoFront,

  //Hyrule Field
  &HF_SoutheastGrottoChest,
  &HF_OpenGrottoChest,
  &HF_NearMarketGrottoChest,
  &HF_OcarinaOfTimeItem,
  &HF_TektiteGrottoFreestandingPoH,
  &HF_DekuScrubGrotto,

  //Lake Hylia
  &LH_ChildFishing,
  &LH_AdultFishing,
  &LH_LabDive,
  &LH_UnderwaterItem,
  &LH_Sun,
  &LH_FreestandingPoH,
  //&LH_DekuScrubGrottoLeft,
  //&LH_DekuScrubGrottoRight,
  //&LH_DekuScrubGrottoCenter,

  //Gerudo Valley
  &GV_Chest,
  &GV_WaterfallFreestandingPoH,
  &GV_CrateFreestandingPoH,
  //&GV_DekuScrubGrottoRear,
  //&GV_DekuScrubGrottoFront,

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
  &Colossus_FreestandingPoH,
  //&Colossus_DekuScrubGrottoRear,
  //&Colossus_DekuScrubGrottoFront,

  //Market
  &MK_TreasureChestGameReward,
  //&MK_BombchuBowlingFirstPrize,
  //&MK_BombchuBowlingSecondPrize,
  &MK_LostDog,
  &MK_ShootingGalleryReward,
  //&MK_10BigPoes,

  //Hyrule Castle
  &HC_ZeldasLetter,
  &HC_MalonEgg,

  //Kakariko
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

  //Graveyard
  &GY_HookshotChest,
  &GY_ShieldGraveChest,
  &GY_HeartPieceGraveChest,
  &GY_ComposersGraveChest,
  &GY_FreestandingPoH,
  &GY_DampeRaceFreestandingPoH,
  &GY_DampeGravediggingTour,

  //Death Mountain Trail
  &DMT_Chest,
  &DMT_StormsGrottoChest,
  //&DMT_Biggoron,
  //&DMT_GreatFairyReward,
  &DMT_FreestandingPoH,

  //Goron City
  &GC_MazeLeftChest,
  &GC_MazeCenterChest,
  &GC_MazeRightChest,
  &GC_RollingGoronAsChild,
  &GC_RollingGoronAsAdult,
  &GC_DaruniasJoy,
  &GC_PotFreestandingPoH,
  //&GC_DekuScrubGrottoLeft,
  //&GC_DekuScrubGrottoRight,
  //&GC_DekuScrubGrottoCenter,

  //Death Mountain
  &DMC_UpperGrottoChest,
  &DMC_WallFreestandingPoH,
  &DMC_VolcanoFreestandingPoH,
  //&DMC_DekuScrubGrottoLeft,
  //&DMC_DekuScrubGrottoRight,
  //&DMC_DekuScrubGrottoCenter,

  //Zoras River
  &ZR_OpenGrottoChest,
  &ZR_MagicBeanSalesman,
  &ZR_FrogsOcarinaGame,
  &ZR_FrogsInTheRain,
  &ZR_NearOpenGrottoFreestandingPoH,
  &ZR_NearDomainFreestandingPoH,
  //&ZR_DekuScrubGrottoRear,
  //&ZR_DekuScrubGrottoFront,

  //Zoras Domain
  &ZD_Chest,
  &ZD_DivingMinigame,
  &ZD_KingZoraThawed,

  //Zoras Fountain
  &ZF_IcebergFreestandingPoH,
  &ZF_BottomFreestandingPoH,

  //Lon Lon Ranch
  &LLR_TalonsChickens,
  &LLR_FreestandingPoH,
  //&LLR_DekuScrubGrottoLeft,
  //&LLR_DekuScrubGrottoRight,
  //&LLR_DekuScrubGrottoCenter,

  //Deku Tree
  &DekuTree_MapChest,
  &DekuTree_CompassChest,
  &DekuTree_CompassRoomSideChest,
  &DekuTree_BasementChest,
  &DekuTree_SlingshotChest,
  &DekuTree_SlingshotRoomSideChest,
  &DekuTree_QueenGohmaHeart,

  //Dodongos Cavern
  &DodongosCavern_MapChest,
  &DodongosCavern_CompassChest,
  &DodongosCavern_BombFlowerPlatformChest,
  &DodongosCavern_BombBagChest,
  &DodongosCavern_EndOfBridgeChest,
  &DodongosCavern_BossRoomChest,
  &DodongosCavern_KingDodongoHeart,

  //Jabu Jabus Belly
  &JabuJabusBelly_MapChest,
  &JabuJabusBelly_CompassChest,
  &JabuJabusBelly_BoomerangChest,
  &JabuJabusBelly_BarinadeHeart,

  //Forest Temple
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
  &ForestTemple_PhantomGanonHeart,

  //Fire Temple
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
  &FireTemple_VolvagiaHeart,

  //Water Temple
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
  &WaterTemple_MorphaHeart,

  //Spirit Temple
  &SpiritTemple_SilverGauntletsChest,
  &SpiritTemple_MirrorShieldChest,
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
  &SpiritTemple_TwinrovaHeart,

  //Shadow Temple
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
  &ShadowTemple_BongoBongoHeart,

  //Bottom of the Well
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

  //Ice Cavern
  &IceCavern_MapChest,
  &IceCavern_CompassChest,
  &IceCavern_IronBootsChest,
  &IceCavern_FreestandingPoH,

  //Gerudo Training Grounds
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

  //Ganon's Castle
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
  &GanonsCastle_BossKeyChest,

  /*-------------------------------
     --- GOLD SKULLTULA TOKENS ---
    -------------------------------*/

  //Deku Tree
  &DekuTree_GS_BasementBackRoom,
  &DekuTree_GS_BasementGate,
  &DekuTree_GS_BasementVines,
  &DekuTree_GS_CompassRoom,

  //Dodongos Cavern
  &DodongosCavern_GS_VinesAboveStairs,
  &DodongosCavern_GS_Scarecrow,
  &DodongosCavern_GS_AlcoveAboveStairs,
  &DodongosCavern_GS_BackRoom,
  &DodongosCavern_GS_SideRoomNearLowerLizalfos,

  //Jabu Jabus Belly
  &JabuJabusBelly_GS_LobbyBasementLower,
  &JabuJabusBelly_GS_LobbyBasementUpper,
  &JabuJabusBelly_GS_NearBoss,
  &JabuJabusBelly_GS_WaterSwitchRoom,

  //Forest Temple
  &ForestTemple_GS_RaisedIslandCourtyard,
  &ForestTemple_GS_FirstRoom,
  &ForestTemple_GS_LevelIslandCourtyard,
  &ForestTemple_GS_Lobby,
  &ForestTemple_GS_Basement,

  //Fire Temple
  &FireTemple_GS_SongOfTimeRoom,
  &FireTemple_GS_BossKeyLoop,
  &FireTemple_GS_BoulderMaze,
  &FireTemple_GS_ScarecrowTop,
  &FireTemple_GS_ScarecrowClimb,

  //Water Temple
  &WaterTemple_GS_BehindGate,
  &WaterTemple_GS_FallingPlatformRoom,
  &WaterTemple_GS_CentralPillar,
  &WaterTemple_GS_NearBossKeyChest,
  &WaterTemple_GS_River,

  //Spirit Temple
  &SpiritTemple_GS_HallAfterSunBlockRoom,
  &SpiritTemple_GS_BoulderRoom,
  &SpiritTemple_GS_Lobby,
  &SpiritTemple_GS_SunOnFloorRoom,
  &SpiritTemple_GS_MetalFence,

  //Shadow Temple
  &ShadowTemple_GS_SingleGiantPot,
  &ShadowTemple_GS_FallingSpikesRoom,
  &ShadowTemple_GS_TripleGiantPot,
  &ShadowTemple_GS_LikeLikeRoom,
  &ShadowTemple_GS_NearShip,

  //Bottom of the Well
  &BottomOfTheWell_GS_LikeLikeCage,
  &BottomOfTheWell_GS_EastInnerRoom,
  &BottomOfTheWell_GS_WestInnerRoom,

  //Ice Cavern
  &IceCavern_GS_PushBlockRoom,
  &IceCavern_GS_SpinningScytheRoom,
  &IceCavern_GS_HeartPieceRoom,

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
