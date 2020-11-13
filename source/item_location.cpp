#include "item_location.hpp"

//ItemLocation LinksPocket = ItemLocation(0xFF, ITEMLOCATIONTYPE_NPC, 0x0);

//Kokiri Forest
ItemLocation KF_KokiriSwordChest                        = ItemLocation(0x55, ITEMLOCATIONTYPE_CHEST,        0x00, "KF Kokiri Sword Chest");
ItemLocation KF_MidoTopLeftChest                        = ItemLocation(0x28, ITEMLOCATIONTYPE_CHEST,        0x00, "KF Mido Top Left Chest");
ItemLocation KF_MidoTopRightChest                       = ItemLocation(0x28, ITEMLOCATIONTYPE_CHEST,        0x01, "KF Mido Top Right Chest");
ItemLocation KF_MidoBottomLeftChest                     = ItemLocation(0x28, ITEMLOCATIONTYPE_CHEST,        0x02, "KF Mido Bottom Left Chest");
ItemLocation KF_MidoBottomRightChest                    = ItemLocation(0x28, ITEMLOCATIONTYPE_CHEST,        0x03, "KF Mido Bottom Right Chest");
ItemLocation KF_StormsGrottoChest                       = ItemLocation(0x3E, ITEMLOCATIONTYPE_CHEST,        0x0C, "KF Storms Grotto Chest");

//Lost Woods
ItemLocation LW_NearShortcutsGrottoChest                = ItemLocation(0x3E, ITEMLOCATIONTYPE_CHEST,        0x14, "LW Near Shortcuts Grotto Chest");
ItemLocation LW_SkullKid                                = ItemLocation(0x5B, ITEMLOCATIONTYPE_NPC,          0x3E, "LW Skull Kid");
ItemLocation LW_OcarinaMemoryGame                       = ItemLocation(0x5B, ITEMLOCATIONTYPE_NPC,          0x76, "LW Ocarina Memory Game");//Gives wrong item
ItemLocation LW_TargetInWoods                           = ItemLocation(0x5B, ITEMLOCATIONTYPE_NPC,          0x60, "LW Target in Woods");
ItemLocation LW_DekuScrubNearDekuTheaterRight           = ItemLocation(0x5B, ITEMLOCATIONTYPE_NPC,          0x30, "LW Deku Scrub Near Deku Theater Right");//doesnt work
ItemLocation LW_DekuScrubNearDekuTheaterLeft            = ItemLocation(0x5B, ITEMLOCATIONTYPE_NPC,          0x31, "LW Deku Scrub Near Deku Theater Left"); //doesnt work
ItemLocation LW_DekuScrubNearBridge                     = ItemLocation(0x5B, ITEMLOCATIONTYPE_NPC,          0x77, "LW Deku Scrub Near Bridge");
ItemLocation LW_DekuScrubGrottoRear                     = ItemLocation(0xF5, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x33, "LW Deku Scrub Grotto Rear");
ItemLocation LW_DekuScrubGrottoFront                    = ItemLocation(0xF5, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x79, "LW Deku Scrub Grotto Front");
ItemLocation DekuTheater_SkullMask                      = ItemLocation(0x3E, ITEMLOCATIONTYPE_NPC,          0x77, "Deku Theater Skull Mask");
ItemLocation DekuTheater_MaskOfTruth                    = ItemLocation(0x3E, ITEMLOCATIONTYPE_NPC,          0x7A, "Deku Theater Mask of Truth");

//Sacred Forest Meadow
ItemLocation SFM_WolfosGrottoChest                      = ItemLocation(0x3E, ITEMLOCATIONTYPE_CHEST,        0x11, "SFM Wolfos Grotto Chest");
ItemLocation SFM_DekuScrubGrottoRear                    = ItemLocation(0xEE, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x39, "SFM Deku Scrub Grotto Rear");
ItemLocation SFM_DekuScrubGrottoFront                   = ItemLocation(0xEE, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x3A, "SFM Deku Scrub Grotto Front");

//Hyrule Field
ItemLocation HF_SoutheastGrottoChest                    = ItemLocation(0x3E, ITEMLOCATIONTYPE_CHEST,        0x02, "HF Southeast Grotto Chest");
ItemLocation HF_OpenGrottoChest                         = ItemLocation(0x3E, ITEMLOCATIONTYPE_CHEST,        0x03, "HF Open Grotto Chest");
ItemLocation HF_NearMarketGrottoChest                   = ItemLocation(0x3E, ITEMLOCATIONTYPE_CHEST,        0x00, "HF Near Market Grotto Chest");
ItemLocation HF_OcarinaOfTimeItem                       = ItemLocation(0x51, ITEMLOCATIONTYPE_NPC,          0x0C, "HF Ocarina of Time Item");
ItemLocation HF_TektiteGrottoFreestandingPoH            = ItemLocation(0x3E, ITEMLOCATIONTYPE_COLLECTABLE,  0x01, "HF Tektite Grotto Freestanding PoH");
ItemLocation HF_DekuScrubGrotto                         = ItemLocation(0xE6, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x3E, "HF Deku Scrub Grotto");

//Lake Hylia
ItemLocation LH_ChildFishing                            = ItemLocation(0x49, ITEMLOCATIONTYPE_NPC,          0x3E, "LH Child Fishing");
ItemLocation LH_AdultFishing                            = ItemLocation(0x49, ITEMLOCATIONTYPE_NPC,          0x38, "LH Adult Fishing");
ItemLocation LH_LabDive                                 = ItemLocation(0x38, ITEMLOCATIONTYPE_NPC,          0x3E, "LH Lab Dive");
ItemLocation LH_UnderwaterItem                          = ItemLocation(0x57, ITEMLOCATIONTYPE_NPC,          0x15, "LH Underwater Item");
ItemLocation LH_Sun                                     = ItemLocation(0x57, ITEMLOCATIONTYPE_NPC,          0x58, "LH Sun");
ItemLocation LH_FreestandingPoH                         = ItemLocation(0x57, ITEMLOCATIONTYPE_COLLECTABLE,  0x1E, "LH Freestanding PoH");
ItemLocation LH_DekuScrubGrottoLeft                     = ItemLocation(0xEF, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x30, "LH Deku Scrub Grotto Left");
ItemLocation LH_DekuScrubGrottoRight                    = ItemLocation(0xEF, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x37, "LH Deku Scrub Grotto Right");
ItemLocation LH_DekuScrubGrottoCenter                   = ItemLocation(0xEF, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x33, "LH Deku Scrub Grotto Center");

//Gerudo Valley
ItemLocation GV_Chest                                   = ItemLocation(0x5A, ITEMLOCATIONTYPE_CHEST,        0x00, "GV Chest");
ItemLocation GV_WaterfallFreestandingPoH                = ItemLocation(0x5A, ITEMLOCATIONTYPE_COLLECTABLE,  0x01, "GV Waterfall Freestanding PoH");
ItemLocation GV_CrateFreestandingPoH                    = ItemLocation(0x5A, ITEMLOCATIONTYPE_COLLECTABLE,  0x02, "GV Crate Freestanding PoH");
ItemLocation GV_DekuScrubGrottoRear                     = ItemLocation(0xF0, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x39, "GV Deku Scrub Grotto Rear");
ItemLocation GV_DekuScrubGrottoFront                    = ItemLocation(0xF0, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x3A, "GV Deku Scrub Grotto Front");

//Gerudo Fortress
ItemLocation GF_Chest                                   = ItemLocation(0x5D, ITEMLOCATIONTYPE_CHEST,        0x00, "GF Chest");
ItemLocation GF_HBA1000Points                           = ItemLocation(0x5D, ITEMLOCATIONTYPE_NPC,          0x3E, "GF HBA 1000 Points");//This is probably broken
ItemLocation GF_HBA1500Points                           = ItemLocation(0x5D, ITEMLOCATIONTYPE_NPC,          0x30, "GF HBA 1500 Points");
ItemLocation GF_GerudoToken                             = ItemLocation(0x0C, ITEMLOCATIONTYPE_NPC,          0x3A, "GF Gerudo Token");
ItemLocation GF_NorthF1Carpenter                        = ItemLocation(0x0C, ITEMLOCATIONTYPE_COLLECTABLE,  0x0C, "GF North F1 Carpenter");
ItemLocation GF_NorthF2Carpenter                        = ItemLocation(0x0C, ITEMLOCATIONTYPE_COLLECTABLE,  0x0A, "GF North F2 Carpenter");
ItemLocation GF_SouthF1Carpenter                        = ItemLocation(0x0C, ITEMLOCATIONTYPE_COLLECTABLE,  0x0E, "GF South F1 Carpenter");
ItemLocation GF_SouthF2Carpenter                        = ItemLocation(0x0C, ITEMLOCATIONTYPE_COLLECTABLE,  0x0F, "GF South F2 Carpenter");

//Haunted Wasteland
ItemLocation HW_Chest                                   = ItemLocation(0x5E, ITEMLOCATIONTYPE_CHEST,        0x00, "HW Chest");

//Desert Colossus
ItemLocation Colossus_FreestandingPoH                   = ItemLocation(0x5C, ITEMLOCATIONTYPE_COLLECTABLE,  0x0D, "Colossus Freestanding PoH");
ItemLocation Colossus_DekuScrubGrottoRear               = ItemLocation(0xFD, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x39, "Colossus Deku Scrub Grotto Rear");
ItemLocation Colossus_DekuScrubGrottoFront              = ItemLocation(0xFD, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x3A, "Colossus Deku Scrub Grotto Front");

//Market
ItemLocation MK_TreasureChestGameReward                 = ItemLocation(0x10, ITEMLOCATIONTYPE_CHEST,        0x0A, "MK Treasure Chest Game Reward");
ItemLocation MK_BombchuBowlingFirstPrize                = ItemLocation(0x4B, ITEMLOCATIONTYPE_NPC,          0x34, "MK Bombchu Bowling First Prize");
ItemLocation MK_BombchuBowlingSecondPrize               = ItemLocation(0x4B, ITEMLOCATIONTYPE_NPC,          0x3E, "MK Bombchu Bowling Second Prize");
ItemLocation MK_LostDog                                 = ItemLocation(0x35, ITEMLOCATIONTYPE_NPC,          0x3E, "MK Lost Dog");
ItemLocation MK_ShootingGalleryReward                   = ItemLocation(0x42, ITEMLOCATIONTYPE_NPC,          0x60, "MK Shooting Gallery");
ItemLocation MK_10BigPoes                               = ItemLocation(0x4D, ITEMLOCATIONTYPE_NPC,          0x0F, "MK 10 Big Poes");

//Hyrule Castle
ItemLocation HC_MalonEgg                                = ItemLocation(0x5F, ITEMLOCATIONTYPE_NPC,          0x47, "HC Malon Egg");
ItemLocation HC_ZeldasLetter                            = ItemLocation(0x4A, ITEMLOCATIONTYPE_NPC,          0x0B, "HC Zeldas Letter");

//Kakariko
ItemLocation Kak_RedeadGrottoChest                      = ItemLocation(0x3E, ITEMLOCATIONTYPE_CHEST,        0x0A, "Kak Redead Grotto Chest");
ItemLocation Kak_OpenGrottoChest                        = ItemLocation(0x3E, ITEMLOCATIONTYPE_CHEST,        0x08, "Kak Open Grotto Chest");
ItemLocation Kak_10GoldSkulltulaReward                  = ItemLocation(0x50, ITEMLOCATIONTYPE_NPC,          0x45, "Kak 10 Gold Skulltula Reward");
ItemLocation Kak_20GoldSkulltulaReward                  = ItemLocation(0x50, ITEMLOCATIONTYPE_NPC,          0x39, "Kak 20 Gold Skulltula Reward");
ItemLocation Kak_30GoldSkulltulaReward                  = ItemLocation(0x50, ITEMLOCATIONTYPE_NPC,          0x46, "Kak 30 Gold Skulltula Reward");
ItemLocation Kak_40GoldSkulltulaReward                  = ItemLocation(0x50, ITEMLOCATIONTYPE_NPC,          0x03, "Kak 40 Gold Skulltula Reward");
ItemLocation Kak_50GoldSkulltulaReward                  = ItemLocation(0x50, ITEMLOCATIONTYPE_NPC,          0x3E, "Kak 50 Gold Skulltula Reward");
ItemLocation Kak_ManOnRoof                              = ItemLocation(0x52, ITEMLOCATIONTYPE_NPC,          0x3E, "Kak Man on Roof");
ItemLocation Kak_ShootingGalleryReward                  = ItemLocation(0x42, ITEMLOCATIONTYPE_NPC,          0x30, "Kak Shooting Gallery Reward");
ItemLocation Kak_AnjuAsAdult                            = ItemLocation(0x52, ITEMLOCATIONTYPE_NPC,          0x1D, "Kak Anju as Adult");
ItemLocation Kak_AnjuAsChild                            = ItemLocation(0x52, ITEMLOCATIONTYPE_NPC,          0x0F, "Kak Anju as Child");
ItemLocation Kak_ImpasHouseFreestandingPoH              = ItemLocation(0x37, ITEMLOCATIONTYPE_COLLECTABLE,  0x01, "Kak Impas House Freestanding PoH");
ItemLocation Kak_WindmillFreestandingPoH                = ItemLocation(0x48, ITEMLOCATIONTYPE_COLLECTABLE,  0x01, "Kak Windmill Freestanding PoH");

//Graveyard
ItemLocation GY_ShieldGraveChest                        = ItemLocation(0x40, ITEMLOCATIONTYPE_CHEST,        0x00, "GY Shield Grave Chest");
ItemLocation GY_HeartPieceGraveChest                    = ItemLocation(0x3F, ITEMLOCATIONTYPE_CHEST,        0x00, "GY Heart Piece Grave Chest");
ItemLocation GY_ComposersGraveChest                     = ItemLocation(0x41, ITEMLOCATIONTYPE_CHEST,        0x00, "GY Composers Grave Chest");
ItemLocation GY_HookshotChest                           = ItemLocation(0x48, ITEMLOCATIONTYPE_CHEST,        0x00, "GY Hookshot Chest");
ItemLocation GY_DampeRaceFreestandingPoH                = ItemLocation(0x48, ITEMLOCATIONTYPE_COLLECTABLE,  0x07, "GY Dampe Race Freestanding PoH");
ItemLocation GY_FreestandingPoH                         = ItemLocation(0x53, ITEMLOCATIONTYPE_COLLECTABLE,  0x04, "GY Freestanding PoH");
ItemLocation GY_DampeGravediggingTour                   = ItemLocation(0x53, ITEMLOCATIONTYPE_COLLECTABLE,  0x08, "GY Dampe Gravedigging Tour");

//Death Mountain
ItemLocation DMT_Chest                                  = ItemLocation(0x60, ITEMLOCATIONTYPE_CHEST,        0x01, "DMT Chest");
ItemLocation DMT_StormsGrottoChest                      = ItemLocation(0x3E, ITEMLOCATIONTYPE_CHEST,        0x17, "DMT Storms Grotto Chest");
ItemLocation DMT_Biggoron                               = ItemLocation(0x60, ITEMLOCATIONTYPE_NPC,          0x57, "DMT Biggoron");
ItemLocation DMT_FreestandingPoH                        = ItemLocation(0x60, ITEMLOCATIONTYPE_COLLECTABLE,  0x1E, "DMT Freestanding PoH");

//Goron City
ItemLocation GC_MazeLeftChest                           = ItemLocation(0x62, ITEMLOCATIONTYPE_CHEST,        0x00, "GC Maze Left Chest");
ItemLocation GC_MazeRightChest                          = ItemLocation(0x62, ITEMLOCATIONTYPE_CHEST,        0x01, "GC Maze Right Chest");
ItemLocation GC_MazeCenterChest                         = ItemLocation(0x62, ITEMLOCATIONTYPE_CHEST,        0x02, "GC Maze Center Chest");
ItemLocation GC_RollingGoronAsChild                     = ItemLocation(0x62, ITEMLOCATIONTYPE_NPC,          0x34, "GC Rolling Goron as Child");
ItemLocation GC_RollingGoronAsAdult                     = ItemLocation(0x62, ITEMLOCATIONTYPE_NPC,          0x2C, "GC Rolling Goron as Adult");
ItemLocation GC_DaruniasJoy                             = ItemLocation(0x62, ITEMLOCATIONTYPE_NPC,          0x54, "GC Darunias Joy");
ItemLocation GC_PotFreestandingPoH                      = ItemLocation(0x62, ITEMLOCATIONTYPE_COLLECTABLE,  0x1F, "GC Pot Freestanding PoH");
ItemLocation GC_DekuScrubGrottoLeft                     = ItemLocation(0xFB, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x30, "GC Deku Scrub Grotto Left");
ItemLocation GC_DekuScrubGrottoRight                    = ItemLocation(0xFB, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x37, "GC Deku Scrub Grotto Right");
ItemLocation GC_DekuScrubGrottoCenter                   = ItemLocation(0xFB, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x33, "GC Deku Scrub Grotto Center");

//Death Mountain Crater
ItemLocation DMC_UpperGrottoChest                       = ItemLocation(0x3E, ITEMLOCATIONTYPE_CHEST,        0x1A, "DMC Upper Grotto Chest");
ItemLocation DMC_WallFreestandingPoH                    = ItemLocation(0x61, ITEMLOCATIONTYPE_COLLECTABLE,  0x02, "DMC Wall Freestanding PoH");
ItemLocation DMC_VolcanoFreestandingPoH                 = ItemLocation(0x61, ITEMLOCATIONTYPE_COLLECTABLE,  0x08, "DMC Volcano Freestanding PoH");
ItemLocation DMC_DekuScrubGrottoLeft                    = ItemLocation(0xF9, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x30, "DMC Deku Scrub Grotto Left");
ItemLocation DMC_DekuScrubGrottoRight                   = ItemLocation(0xF9, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x37, "DMC Deku Scrub Grotto Right");
ItemLocation DMC_DekuScrubGrottoCenter                  = ItemLocation(0xF9, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x33, "DMC Deku Scrub Grotto Center");

//Zoras River
ItemLocation ZR_OpenGrottoChest                         = ItemLocation(0x3E, ITEMLOCATIONTYPE_CHEST,        0x09, "ZR Open Grotto Chest");
ItemLocation ZR_MagicBeanSalesman                       = ItemLocation(0x54, ITEMLOCATIONTYPE_NPC,          0x16, "ZR Magic Bean Salesman");
ItemLocation ZR_FrogsOcarinaGame                        = ItemLocation(0x54, ITEMLOCATIONTYPE_NPC,          0x76, "ZR Frogs Ocarina Game");
ItemLocation ZR_FrogsInTheRain                          = ItemLocation(0x54, ITEMLOCATIONTYPE_NPC,          0x3E, "ZR Frogs in the Rain");
ItemLocation ZR_NearOpenGrottoFreestandingPoH           = ItemLocation(0x54, ITEMLOCATIONTYPE_COLLECTABLE,  0x04, "ZR Near Open Grotto Freestanding PoH");
ItemLocation ZR_NearDomainFreestandingPoH               = ItemLocation(0x54, ITEMLOCATIONTYPE_COLLECTABLE,  0x0B, "ZR Near Domain Freestanding PoH");
ItemLocation ZR_DekuScrubGrottoRear                     = ItemLocation(0xEB, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x39, "ZR Deku Scrub Grotto Rear");
ItemLocation ZR_DekuScrubGrottoFront                    = ItemLocation(0xEB, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x3A, "ZR Deku Scrub Grotto Front");

//Zoras Domain
ItemLocation ZD_Chest                                   = ItemLocation(0x58, ITEMLOCATIONTYPE_CHEST,        0x00, "ZD Chest");
ItemLocation ZD_DivingMinigame                          = ItemLocation(0x58, ITEMLOCATIONTYPE_NPC,          0x37, "ZD Diving Minigame");
ItemLocation ZD_KingZoraThawed                          = ItemLocation(0x58, ITEMLOCATIONTYPE_NPC,          0x2D, "ZD King Zora Thawed");

//Zoras Fountain
ItemLocation ZF_IcebergFreestandingPoH                  = ItemLocation(0x59, ITEMLOCATIONTYPE_COLLECTABLE,  0x01, "ZF Iceberg Freestanding PoH");
ItemLocation ZF_BottomFreestandingPoH                   = ItemLocation(0x59, ITEMLOCATIONTYPE_COLLECTABLE,  0x14, "ZF Bottom Freestanding PoH");

//Lon Lon Ranch
ItemLocation LLR_TalonsChickens                         = ItemLocation(0x4C, ITEMLOCATIONTYPE_NPC,          0x14, "LLR Talons Chickens");
ItemLocation LLR_FreestandingPoH                        = ItemLocation(0x4C, ITEMLOCATIONTYPE_COLLECTABLE,  0x01, "LLR Freestanding PoH");
ItemLocation LLR_DekuScrubGrottoLeft                    = ItemLocation(0xFC, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x30, "LLR Deku Scrub Grotto Left");
ItemLocation LLR_DekuScrubGrottoRight                   = ItemLocation(0xFC, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x37, "LLR Deku Scrub Grotto Right");
ItemLocation LLR_DekuScrubGrottoCenter                  = ItemLocation(0xFC, ITEMLOCATIONTYPE_GROTTO_SCRUB, 0x33, "LLR Deku Scrub Grotto Center");

//Deku Tree
ItemLocation DekuTree_MapChest                          = ItemLocation(0x00, ITEMLOCATIONTYPE_CHEST,        0x03, "Deku Tree Map Chest");
ItemLocation DekuTree_CompassChest                      = ItemLocation(0x00, ITEMLOCATIONTYPE_CHEST,        0x02, "Deku Tree Compass Chest");
ItemLocation DekuTree_CompassRoomSideChest              = ItemLocation(0x00, ITEMLOCATIONTYPE_CHEST,        0x06, "Deku Tree Compass Room Side Chest");
ItemLocation DekuTree_BasementChest                     = ItemLocation(0x00, ITEMLOCATIONTYPE_CHEST,        0x04, "Deku Tree Basement Chest");
ItemLocation DekuTree_SlingshotChest                    = ItemLocation(0x00, ITEMLOCATIONTYPE_CHEST,        0x01, "Deku Tree Slingshot Chest");
ItemLocation DekuTree_SlingshotRoomSideChest            = ItemLocation(0x00, ITEMLOCATIONTYPE_CHEST,        0x05, "Deku Tree Slingshot Room Side Chest");

//Dodongos Cavern
ItemLocation DodongosCavern_MapChest                    = ItemLocation(0x01, ITEMLOCATIONTYPE_CHEST,        0x08, "Dodongos Cavern Map Chest");
ItemLocation DodongosCavern_CompassChest                = ItemLocation(0x01, ITEMLOCATIONTYPE_CHEST,        0x05, "Dodongos Cavern Compass Chest");
ItemLocation DodongosCavern_BombFlowerPlatformChest     = ItemLocation(0x01, ITEMLOCATIONTYPE_CHEST,        0x06, "Dodongos Cavern Bomb Flower Platform Chest");
ItemLocation DodongosCavern_BombBagChest                = ItemLocation(0x01, ITEMLOCATIONTYPE_CHEST,        0x04, "Dodongos Cavern Bomb Bag Chest");
ItemLocation DodongosCavern_EndOfBridgeChest            = ItemLocation(0x01, ITEMLOCATIONTYPE_CHEST,        0x0A, "Dodongos Cavern End Of Bridge Chest");
ItemLocation DodongosCavern_BossRoomChest               = ItemLocation(0x12, ITEMLOCATIONTYPE_CHEST,        0x00, "Dodongos Cavern Boss Room Chest");

//Jabu Jabus Belly
ItemLocation JabuJabusBelly_MapChest                    = ItemLocation(0x02, ITEMLOCATIONTYPE_CHEST,        0x02, "Jabu Jabus Belly Map Chest");
ItemLocation JabuJabusBelly_CompassChest                = ItemLocation(0x02, ITEMLOCATIONTYPE_CHEST,        0x04, "Jabu Jabus Belly Compass Chest");
ItemLocation JabuJabusBelly_BoomerangChest              = ItemLocation(0x02, ITEMLOCATIONTYPE_CHEST,        0x01, "Jabu Jabus Belly Boomerang Chest");

//Forest Temple
ItemLocation ForestTemple_FirstRoomChest                = ItemLocation(0x03, ITEMLOCATIONTYPE_CHEST,        0x03, "Forest Temple First Room Chest");
ItemLocation ForestTemple_FirstStalfosChest             = ItemLocation(0x03, ITEMLOCATIONTYPE_CHEST,        0x00, "Forest Temple First Stalfos Chest");
ItemLocation ForestTemple_RaisedIslandCourtyardChest    = ItemLocation(0x03, ITEMLOCATIONTYPE_CHEST,        0x05, "Forest Temple Raised Island Courtyard Chest");
ItemLocation ForestTemple_MapChest                      = ItemLocation(0x03, ITEMLOCATIONTYPE_CHEST,        0x01, "Forest Temple Map Chest");
ItemLocation ForestTemple_WellChest                     = ItemLocation(0x03, ITEMLOCATIONTYPE_CHEST,        0x09, "Forest Temple Well Chest");
ItemLocation ForestTemple_FallingCeilingRoomChest       = ItemLocation(0x03, ITEMLOCATIONTYPE_CHEST,        0x07, "Forest Temple Falling Ceiling Room Chest");
ItemLocation ForestTemple_EyeSwitchChest                = ItemLocation(0x03, ITEMLOCATIONTYPE_CHEST,        0x04, "Forest Temple Eye Switch Chest");
ItemLocation ForestTemple_BossKeyChest                  = ItemLocation(0x03, ITEMLOCATIONTYPE_CHEST,        0x0E, "Forest Temple Boss Key Chest");
ItemLocation ForestTemple_FloormasterChest              = ItemLocation(0x03, ITEMLOCATIONTYPE_CHEST,        0x02, "Forest Temple Floormaster Chest");
ItemLocation ForestTemple_BowChest                      = ItemLocation(0x03, ITEMLOCATIONTYPE_CHEST,        0x0C, "Forest Temple Bow Chest");
ItemLocation ForestTemple_RedPoeChest                   = ItemLocation(0x03, ITEMLOCATIONTYPE_CHEST,        0x0D, "Forest Temple Red Poe Chest");
ItemLocation ForestTemple_BluePoeChest                  = ItemLocation(0x03, ITEMLOCATIONTYPE_CHEST,        0x0F, "Forest Temple Blue Poe Chest");
ItemLocation ForestTemple_BasementChest                 = ItemLocation(0x03, ITEMLOCATIONTYPE_CHEST,        0x0B, "Forest Temple Basement Chest");

//Fire Temple
ItemLocation FireTemple_NearBossChest                   = ItemLocation(0x04, ITEMLOCATIONTYPE_CHEST,        0x01, "Fire Temple Near Boss Chest");
ItemLocation FireTemple_FlareDancerChest                = ItemLocation(0x04, ITEMLOCATIONTYPE_CHEST,        0x00, "Fire Temple Flare Dancer Chest");
ItemLocation FireTemple_BossKeyChest                    = ItemLocation(0x04, ITEMLOCATIONTYPE_CHEST,        0x0C, "Fire Temple Boss Key Chest");
ItemLocation FireTemple_BigLavaRoomBlockedDoorChest     = ItemLocation(0x04, ITEMLOCATIONTYPE_CHEST,        0x02, "Fire Temple Big Lava Room Blocked Door Chest");
ItemLocation FireTemple_BigLavaRoomLowerOpenDoorChest   = ItemLocation(0x04, ITEMLOCATIONTYPE_CHEST,        0x04, "Fire Temple Big Lava Room Lower Open Door Chest");
ItemLocation FireTemple_BoulderMazeLowerChest           = ItemLocation(0x04, ITEMLOCATIONTYPE_CHEST,        0x03, "Fire Temple Boulder Maze Lower Chest");
ItemLocation FireTemple_BoulderMazeUpperChest           = ItemLocation(0x04, ITEMLOCATIONTYPE_CHEST,        0x06, "Fire Temple Boulder Maze Upper Chest");
ItemLocation FireTemple_BoulderMazeSideRoomChest        = ItemLocation(0x04, ITEMLOCATIONTYPE_CHEST,        0x08, "Fire Temple Boulder Maze Side Room Chest");
ItemLocation FireTemple_BoulderMazeShortcutChest        = ItemLocation(0x04, ITEMLOCATIONTYPE_CHEST,        0x0B, "Fire Temple Boulder Maze Shortcut Chest");
ItemLocation FireTemple_ScarecrowChest                  = ItemLocation(0x04, ITEMLOCATIONTYPE_CHEST,        0x0D, "Fire Temple Scarecrow Chest");
ItemLocation FireTemple_MapChest                        = ItemLocation(0x04, ITEMLOCATIONTYPE_CHEST,        0x0A, "Fire Temple Map Chest");
ItemLocation FireTemple_CompassChest                    = ItemLocation(0x04, ITEMLOCATIONTYPE_CHEST,        0x07, "Fire Temple Compass Chest");
ItemLocation FireTemple_HighestGoronChest               = ItemLocation(0x04, ITEMLOCATIONTYPE_CHEST,        0x09, "Fire Temple Highest Goron Chest");
ItemLocation FireTemple_MegatonHammerChest              = ItemLocation(0x04, ITEMLOCATIONTYPE_CHEST,        0x05, "Fire Temple Megaton Hammer Chest");

//Water Temple
ItemLocation WaterTemple_MapChest                       = ItemLocation(0x05, ITEMLOCATIONTYPE_CHEST,        0x02, "Water Temple Map Chest");
ItemLocation WaterTemple_CompassChest                   = ItemLocation(0x05, ITEMLOCATIONTYPE_CHEST,        0x09, "Water Temple Compass Chest");
ItemLocation WaterTemple_TorchesChest                   = ItemLocation(0x05, ITEMLOCATIONTYPE_CHEST,        0x01, "Water Temple Torches Chest");
ItemLocation WaterTemple_DragonChest                    = ItemLocation(0x05, ITEMLOCATIONTYPE_CHEST,        0x0A, "Water Temple Dragon Chest");
ItemLocation WaterTemple_CentralBowTargetChest          = ItemLocation(0x05, ITEMLOCATIONTYPE_CHEST,        0x08, "Water Temple Central Bow Target Chest");
ItemLocation WaterTemple_CentralPillarChest             = ItemLocation(0x05, ITEMLOCATIONTYPE_CHEST,        0x06, "Water Temple Central Pillar Chest");
ItemLocation WaterTemple_CrackedWallChest               = ItemLocation(0x05, ITEMLOCATIONTYPE_CHEST,        0x00, "Water Temple Cracked Wall Chest");
ItemLocation WaterTemple_BossKeyChest                   = ItemLocation(0x05, ITEMLOCATIONTYPE_CHEST,        0x05, "Water Temple Boss Key Chest");
ItemLocation WaterTemple_LongshotChest                  = ItemLocation(0x05, ITEMLOCATIONTYPE_CHEST,        0x07, "Water Temple Longshot Chest");
ItemLocation WaterTemple_RiverChest                     = ItemLocation(0x05, ITEMLOCATIONTYPE_CHEST,        0x03, "Water Temple River Chest");

//Spirit Temple Outside
ItemLocation SpiritTemple_SilverGauntletsChest          = ItemLocation(0x5C, ITEMLOCATIONTYPE_CHEST,        0x0B, "Spirit Temple Silver Gauntlets Chest");
ItemLocation SpiritTemple_MirrorShieldChest             = ItemLocation(0x5C, ITEMLOCATIONTYPE_CHEST,        0x09, "Spirit Temple Mirror Shield Chest");
//Spirit Temple
ItemLocation SpiritTemple_ChildBridgeChest              = ItemLocation(0x06, ITEMLOCATIONTYPE_CHEST,        0x08, "Spirit Temple Child Bridge Chest");
ItemLocation SpiritTemple_ChildEarlyTorchesChest        = ItemLocation(0x06, ITEMLOCATIONTYPE_CHEST,        0x00, "Spirit Temple Child Early Torches Chest");
ItemLocation SpiritTemple_CompassChest                  = ItemLocation(0x06, ITEMLOCATIONTYPE_CHEST,        0x04, "Spirit Temple Compass Chest");
ItemLocation SpiritTemple_EarlyAdultRightChest          = ItemLocation(0x06, ITEMLOCATIONTYPE_CHEST,        0x07, "Spirit Temple Early Adult Right Chest");
ItemLocation SpiritTemple_FirstMirrorLeftChest          = ItemLocation(0x06, ITEMLOCATIONTYPE_CHEST,        0x0D, "Spirit Temple First Mirror Left Chest");
ItemLocation SpiritTemple_FirstMirrorRightChest         = ItemLocation(0x06, ITEMLOCATIONTYPE_CHEST,        0x0E, "Spirit Temple First Mirror Right Chest");
ItemLocation SpiritTemple_MapChest                      = ItemLocation(0x06, ITEMLOCATIONTYPE_CHEST,        0x03, "Spirit Temple Map Chest");
ItemLocation SpiritTemple_ChildClimbNorthChest          = ItemLocation(0x06, ITEMLOCATIONTYPE_CHEST,        0x06, "Spirit Temple Child Climb North Chest");
ItemLocation SpiritTemple_ChildClimbEastChest           = ItemLocation(0x06, ITEMLOCATIONTYPE_CHEST,        0x0C, "Spirit Temple Child Climb East Chest");
ItemLocation SpiritTemple_SunBlockRoomChest             = ItemLocation(0x06, ITEMLOCATIONTYPE_CHEST,        0x01, "Spirit Temple Sun Block Room Chest");
ItemLocation SpiritTemple_StatueRoomHandChest           = ItemLocation(0x06, ITEMLOCATIONTYPE_CHEST,        0x02, "Spirit Temple Statue Room Hand Chest");
ItemLocation SpiritTemple_StatueRoomNortheastChest      = ItemLocation(0x06, ITEMLOCATIONTYPE_CHEST,        0x0F, "Spirit Temple Statue Room Northeast Chest");
ItemLocation SpiritTemple_NearFourArmosChest            = ItemLocation(0x06, ITEMLOCATIONTYPE_CHEST,        0x05, "Spirit Temple Near Four Armos Chest");
ItemLocation SpiritTemple_HallwayRightInvisibleChest    = ItemLocation(0x06, ITEMLOCATIONTYPE_CHEST,        0x14, "Spirit Temple Hallway Right Invisible Chest");
ItemLocation SpiritTemple_HallwayLeftInvisibleChest     = ItemLocation(0x06, ITEMLOCATIONTYPE_CHEST,        0x15, "Spirit Temple Hallway Left Invisible Chest");
ItemLocation SpiritTemple_BossKeyChest                  = ItemLocation(0x06, ITEMLOCATIONTYPE_CHEST,        0x0A, "Spirit Temple Boss Key Chest");
ItemLocation SpiritTemple_TopmostChest                  = ItemLocation(0x06, ITEMLOCATIONTYPE_CHEST,        0x12, "Spirit Temple Topmost Chest");

//Shadow Temple
ItemLocation ShadowTemple_MapChest                      = ItemLocation(0x07, ITEMLOCATIONTYPE_CHEST,        0x01, "Shadow Temple Map Chest");
ItemLocation ShadowTemple_HoverBootsChest               = ItemLocation(0x07, ITEMLOCATIONTYPE_CHEST,        0x07, "Shadow Temple Hover Boots Chest");
ItemLocation ShadowTemple_CompassChest                  = ItemLocation(0x07, ITEMLOCATIONTYPE_CHEST,        0x03, "Shadow Temple Compass Chest");
ItemLocation ShadowTemple_EarlySilverRupeeChest         = ItemLocation(0x07, ITEMLOCATIONTYPE_CHEST,        0x02, "Shadow Temple Early Silver Rupee Chest");
ItemLocation ShadowTemple_InvisibleBladesVisibleChest   = ItemLocation(0x07, ITEMLOCATIONTYPE_CHEST,        0x0C, "Shadow Temple Invisible Blades Visible Chest");
ItemLocation ShadowTemple_InvisibleBladesInvisibleChest = ItemLocation(0x07, ITEMLOCATIONTYPE_CHEST,        0x16, "Shadow Temple Invisible Blades Invisible Chest");
ItemLocation ShadowTemple_FallingSpikesLowerChest       = ItemLocation(0x07, ITEMLOCATIONTYPE_CHEST,        0x05, "Shadow Temple Falling Spikes Lower Chest");
ItemLocation ShadowTemple_FallingSpikesUpperChest       = ItemLocation(0x07, ITEMLOCATIONTYPE_CHEST,        0x06, "Shadow Temple Falling Spikes Upper Chest");
ItemLocation ShadowTemple_FallingSpikesSwitchChest      = ItemLocation(0x07, ITEMLOCATIONTYPE_CHEST,        0x04, "Shadow Temple Falling Spikes Switch Chest");
ItemLocation ShadowTemple_InvisibleSpikesChest          = ItemLocation(0x07, ITEMLOCATIONTYPE_CHEST,        0x09, "Shadow Temple Invisible Spikes Chest");
ItemLocation ShadowTemple_WindHintChest                 = ItemLocation(0x07, ITEMLOCATIONTYPE_CHEST,        0x15, "Shadow Temple Wind Hint Chest");
ItemLocation ShadowTemple_AfterWindEnemyChest           = ItemLocation(0x07, ITEMLOCATIONTYPE_CHEST,        0x08, "Shadow Temple After Wind Enemey Chest");
ItemLocation ShadowTemple_AfterWindHiddenChest          = ItemLocation(0x07, ITEMLOCATIONTYPE_CHEST,        0x14, "Shadow Temple After Wind Hidden Chest");
ItemLocation ShadowTemple_SpikeWallsLeftChest           = ItemLocation(0x07, ITEMLOCATIONTYPE_CHEST,        0x0A, "Shadow Temple Spike Walls Left Chest");
ItemLocation ShadowTemple_BossKeyChest                  = ItemLocation(0x07, ITEMLOCATIONTYPE_CHEST,        0x0B, "Shadow Temple Boss Key Chest");
ItemLocation ShadowTemple_InvisibleFloormasterChest     = ItemLocation(0x07, ITEMLOCATIONTYPE_CHEST,        0x0D, "Shadow Temple Invisible Floormaster Chest");
ItemLocation ShadowTemple_FreestandingKey               = ItemLocation(0x07, ITEMLOCATIONTYPE_COLLECTABLE,  0x01, "Shadow Temple Freestanding Key");

//Bottom of the Well
ItemLocation BottomOfTheWell_FrontLeftFakeWallChest     = ItemLocation(0x08, ITEMLOCATIONTYPE_CHEST,        0x08, "Bottom of the Well Front Left Fake Wall Chest");
ItemLocation BottomOfTheWell_FrontCenterBombableChest   = ItemLocation(0x08, ITEMLOCATIONTYPE_CHEST,        0x02, "Bottom of the Well Front Center Bombable Chest");
ItemLocation BottomOfTheWell_RightBottomFakeWallChest   = ItemLocation(0x08, ITEMLOCATIONTYPE_CHEST,        0x05, "Bottom of the Well Right Bottom Fake Wall Chest");
ItemLocation BottomOfTheWell_CompassChest               = ItemLocation(0x08, ITEMLOCATIONTYPE_CHEST,        0x01, "Bottom of the Well Compass Chest");
ItemLocation BottomOfTheWell_CenterSkulltulaChest       = ItemLocation(0x08, ITEMLOCATIONTYPE_CHEST,        0x0E, "Bottom of the Well Center Skulltula Chest");
ItemLocation BottomOfTheWell_BackLeftBombableChest      = ItemLocation(0x08, ITEMLOCATIONTYPE_CHEST,        0x04, "Bottom of the Well Back Left Bombable Chest");
ItemLocation BottomOfTheWell_LensOfTruthChest           = ItemLocation(0x08, ITEMLOCATIONTYPE_CHEST,        0x03, "Bottom of the Well Lens of Truth Chest");
ItemLocation BottomOfTheWell_InvisibleChest             = ItemLocation(0x08, ITEMLOCATIONTYPE_CHEST,        0x14, "Bottom of the Well Invisible Chest");
ItemLocation BottomOfTheWell_UnderwaterFrontChest       = ItemLocation(0x08, ITEMLOCATIONTYPE_CHEST,        0x10, "Bottom of the Well Underwater Front Chest");
ItemLocation BottomOfTheWell_UnderwaterLeftChest        = ItemLocation(0x08, ITEMLOCATIONTYPE_CHEST,        0x09, "Bottom of the Well Underwater Left Chest");
ItemLocation BottomOfTheWell_MapChest                   = ItemLocation(0x08, ITEMLOCATIONTYPE_CHEST,        0x07, "Bottom of the Well Map Chest");
ItemLocation BottomOfTheWell_FireKeeseChest             = ItemLocation(0x08, ITEMLOCATIONTYPE_CHEST,        0x0A, "Bottom of the Well Fire Keese Chest");
ItemLocation BottomOfTheWell_LikeLikeChest              = ItemLocation(0x08, ITEMLOCATIONTYPE_CHEST,        0x0C, "Bottom of the Well Like Like Chest");
ItemLocation BottomOfTheWell_FreestandingKey            = ItemLocation(0x08, ITEMLOCATIONTYPE_COLLECTABLE,  0x01, "Bottom of the Well Freestanding Key");

//Ice Cavern
ItemLocation IceCavern_MapChest                         = ItemLocation(0x09, ITEMLOCATIONTYPE_CHEST,        0x00, "Ice Cavern Map Chest");
ItemLocation IceCavern_CompassChest                     = ItemLocation(0x09, ITEMLOCATIONTYPE_CHEST,        0x01, "Ice Cavern Compass Chest");
ItemLocation IceCavern_IronBootsChest                   = ItemLocation(0x09, ITEMLOCATIONTYPE_CHEST,        0x02, "Ice Cavern Iron Boots Chest");
ItemLocation IceCavern_FreestandingPoH                  = ItemLocation(0x09, ITEMLOCATIONTYPE_COLLECTABLE,  0x01, "Ice Cavern Freestanding PoH");

//Gerudo Training Ground
ItemLocation GerudoTrainingGrounds_LobbyLeftChest             = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x13, "Gerudo Training Grounds Lobby Left Chest");
ItemLocation GerudoTrainingGrounds_LobbyRightChest            = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x07, "Gerudo Training Grounds Lobby Right Chest");
ItemLocation GerudoTrainingGrounds_StalfosChest               = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x00, "Gerudo Training Grounds Stalfos Chest");
ItemLocation GerudoTrainingGrounds_BeamosChest                = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x01, "Gerudo Training Grounds Beamos Chest");
ItemLocation GerudoTrainingGrounds_HiddenCeilingChest         = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x0B, "Gerudo Training Grounds Hidden Ceiling Chest");
ItemLocation GerudoTrainingGrounds_MazePathFirstChest         = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x06, "Gerudo Training Grounds Maze Path First Chest");
ItemLocation GerudoTrainingGrounds_MazePathSecondChest        = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x0A, "Gerudo Training Grounds Maze Path Second Chest");
ItemLocation GerudoTrainingGrounds_MazePathThirdChest         = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x09, "Gerudo Training Grounds Maze Path Third Chest");
ItemLocation GerudoTrainingGrounds_MazePathFinalChest         = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x0C, "Gerudo Training Grounds Maze Path Final Chest");
ItemLocation GerudoTrainingGrounds_MazeRightCentralChest      = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x05, "Gerudo Training Grounds Maze Right Central Chest");
ItemLocation GerudoTrainingGrounds_MazeRightSideChest         = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x08, "Gerudo Training Grounds Maze Right Side Chest");
ItemLocation GerudoTrainingGrounds_UnderwaterSilverRupeeChest = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x0D, "Gerudo Training Grounds Underwater Silver Rupee Chest");
ItemLocation GerudoTrainingGrounds_HammerRoomClearChest       = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x12, "Gerudo Training Grounds Hammer Room Clear Chest");
ItemLocation GerudoTrainingGrounds_HammerRoomSwitchChest      = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x10, "Gerudo Training Grounds Hammer Room Switch Chest");
ItemLocation GerudoTrainingGrounds_EyeStatueChest             = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x03, "Gerudo Training Grounds Eye Statue Chest");
ItemLocation GerudoTrainingGrounds_NearScarecrowChest         = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x04, "Gerudo Training Grounds Near Scarecrow Chest");
ItemLocation GerudoTrainingGrounds_BeforeHeavyBlockChest      = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x11, "Gerudo Training Grounds Before Heavy Block Chest");
ItemLocation GerudoTrainingGrounds_HeavyBlockFirstChest       = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x0F, "Gerudo Training Grounds Heavy Block First Chest");
ItemLocation GerudoTrainingGrounds_HeavyBlockSecondChest      = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x0E, "Gerudo Training Grounds Heavy Block Second Chest");
ItemLocation GerudoTrainingGrounds_HeavyBlockThirdChest       = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x14, "Gerudo Training Grounds Heavy Block Third Chest");
ItemLocation GerudoTrainingGrounds_HeavyBlockFourthChest      = ItemLocation(0x0B, ITEMLOCATIONTYPE_CHEST,        0x02, "Gerudo Training Grounds Heavy Block Fourth Chest");
ItemLocation GerudoTrainingGrounds_FreestandingKey            = ItemLocation(0x0B, ITEMLOCATIONTYPE_COLLECTABLE,  0x01, "Gerudo Training Grounds Freestanding Key");

//Ganons Castle
ItemLocation GanonsCastle_BossKeyChest                    = ItemLocation(0x0A, ITEMLOCATIONTYPE_CHEST,        0x0B, "Ganons Castle Boss Key Chest");
ItemLocation GanonsCastle_ForestTrialChest                = ItemLocation(0x0D, ITEMLOCATIONTYPE_CHEST,        0x09, "Ganons Castle Forest Trial Chest");
ItemLocation GanonsCastle_WaterTrialLeftChest             = ItemLocation(0x0D, ITEMLOCATIONTYPE_CHEST,        0x07, "Ganons Castle Water Trial Left Chest");
ItemLocation GanonsCastle_WaterTrialRightChest            = ItemLocation(0x0D, ITEMLOCATIONTYPE_CHEST,        0x06, "Ganons Castle Water Trial Right Chest");
ItemLocation GanonsCastle_ShadowTrialFrontChest           = ItemLocation(0x0D, ITEMLOCATIONTYPE_CHEST,        0x08, "Ganons Castle Shadow Trial Front Chest");
ItemLocation GanonsCastle_ShadowTrialGoldenGauntletsChest = ItemLocation(0x0D, ITEMLOCATIONTYPE_CHEST,        0x05, "Ganons Castle Shadow Trial Golden Gauntlets Chest");
ItemLocation GanonsCastle_SpiritTrialCrystalSwitchChest   = ItemLocation(0x0D, ITEMLOCATIONTYPE_CHEST,        0x12, "Ganons Castle Spirit Trial Crystal Switch Chest");
ItemLocation GanonsCastle_SpiritTrialInvisibleChest       = ItemLocation(0x0D, ITEMLOCATIONTYPE_CHEST,        0x14, "Ganons Castle Spirit Trial Invisible Chest");
ItemLocation GanonsCastle_LightTrialFirstLeftChest        = ItemLocation(0x0D, ITEMLOCATIONTYPE_CHEST,        0x0C, "Ganons Castle Light Trial First Left Chest");
ItemLocation GanonsCastle_LightTrialSecondLeftChest       = ItemLocation(0x0D, ITEMLOCATIONTYPE_CHEST,        0x0B, "Ganons Castle Light Trial Second Left Chest");
ItemLocation GanonsCastle_LightTrialThirdLeftChest        = ItemLocation(0x0D, ITEMLOCATIONTYPE_CHEST,        0x0D, "Ganons Castle Light Trial Third Left Chest");
ItemLocation GanonsCastle_LightTrialFirstRightChest       = ItemLocation(0x0D, ITEMLOCATIONTYPE_CHEST,        0x0E, "Ganons Castle Light Trial First Right Chest");
ItemLocation GanonsCastle_LightTrialSecondRightChest      = ItemLocation(0x0D, ITEMLOCATIONTYPE_CHEST,        0x0A, "Ganons Castle Light Trial Second Right Chest");
ItemLocation GanonsCastle_LightTrialThirdRightChest       = ItemLocation(0x0D, ITEMLOCATIONTYPE_CHEST,        0x0F, "Ganons Castle Light Trial Third Right Chest");
ItemLocation GanonsCastle_LightTrialInvisibleEnemiesChest = ItemLocation(0x0D, ITEMLOCATIONTYPE_CHEST,        0x10, "Ganons Castle Light Trial Invisible Enemies Chest");
ItemLocation GanonsCastle_LightTrialLullabyChest          = ItemLocation(0x0D, ITEMLOCATIONTYPE_CHEST,        0x11, "Ganons Castle Light Trial Lullaby Chest");

std::vector<ItemLocation> LocationPool = {};
