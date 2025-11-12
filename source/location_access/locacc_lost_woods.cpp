#include "location_access.hpp"
#include "logic.hpp"
#include "entrance.hpp"
#include "enemizer_logic.hpp"

using namespace Logic;
using namespace Settings;

void AreaTable_Init_LostWoods() {
    static constexpr auto ForEachEnemy_KokiriForest = [](auto& enemyCheckFn) {
        return IsAdult && !ForestTempleClear && enemyCheckFn(85, 2, 0, {});
    };
    areaTable[KOKIRI_FOREST] = Area(
        "Kokiri Forest", "Kokiri Forest", KOKIRI_FOREST, NO_DAY_NIGHT_CYCLE,
        {
            // Events
            EventAccess(&DekuBabaSticks,
                        { [] { return DekuBabaSticks || ForEachEnemy_KokiriForest(CanGetDekuBabaSticks); } }),
            EventAccess(&DekuBabaNuts,
                        { [] { return DekuBabaNuts || ForEachEnemy_KokiriForest(CanGetDekuBabaNuts); } }),
            EventAccess(&BeanPlantFairy,
                        { [] { return BeanPlantFairy || (CanPlantBean(KOKIRI_FOREST) && CanPlay(SongOfStorms)); } }),
            EventAccess(&GossipStoneFairy, { [] { return GossipStoneFairy || CanSummonGossipFairyWithoutSuns; } }),
            EventAccess(&ShowedMidoSwordAndShield,
                        { [] { return ShowedMidoSwordAndShield || (IsChild && KokiriSword && DekuShield); } }),
        },
        {
            // Locations
            LocationAccess(KF_KOKIRI_SWORD_CHEST, { [] { return IsChild; } }),
            LocationAccess(KF_END_OF_BRIDGE_BLUE_RUPEE, { [] { return IsChild; } }),
            LocationAccess(KF_BEHIND_MIDOS_HOUSE_BLUE_RUPEE, { [] { return IsChild; } }),
            LocationAccess(KF_BOULDER_MAZE_BLUE_RUPEE_1, { [] { return IsChild; } }),
            LocationAccess(KF_BOULDER_MAZE_BLUE_RUPEE_2, { [] { return IsChild; } }),
            LocationAccess(KF_NEAR_RAMP_GREEN_RUPEE_1, { [] { return IsChild; } }),
            LocationAccess(KF_NEAR_RAMP_GREEN_RUPEE_2, { [] { return IsChild; } }),
            LocationAccess(KF_NEAR_MIDOS_HOUSE_GREEN_RUPEE_1, { [] { return IsChild; } }),
            LocationAccess(KF_NEAR_MIDOS_HOUSE_GREEN_RUPEE_2, { [] { return IsChild; } }),
            LocationAccess(KF_RUPEE_CIRCLE_GREEN_RUPEE_1,
                           { [] { return IsAdult && (CanPlantBean(KOKIRI_FOREST) || CanUse(HOVER_BOOTS)); } }),
            LocationAccess(KF_RUPEE_CIRCLE_GREEN_RUPEE_2,
                           { [] { return IsAdult && (CanPlantBean(KOKIRI_FOREST) || CanUse(HOVER_BOOTS)); } }),
            LocationAccess(KF_RUPEE_CIRCLE_GREEN_RUPEE_3,
                           { [] { return IsAdult && (CanPlantBean(KOKIRI_FOREST) || CanUse(HOVER_BOOTS)); } }),
            LocationAccess(KF_RUPEE_CIRCLE_GREEN_RUPEE_4,
                           { [] { return IsAdult && (CanPlantBean(KOKIRI_FOREST) || CanUse(HOVER_BOOTS)); } }),
            LocationAccess(KF_RUPEE_CIRCLE_GREEN_RUPEE_5,
                           { [] { return IsAdult && (CanPlantBean(KOKIRI_FOREST) || CanUse(HOVER_BOOTS)); } }),
            LocationAccess(KF_RUPEE_CIRCLE_GREEN_RUPEE_6,
                           { [] { return IsAdult && (CanPlantBean(KOKIRI_FOREST) || CanUse(HOVER_BOOTS)); } }),
            LocationAccess(KF_RUPEE_CIRCLE_RED_RUPEE,
                           { [] { return IsAdult && (CanPlantBean(KOKIRI_FOREST) || CanUse(HOVER_BOOTS)); } }),
            LocationAccess(KF_GOSSIP_STONE, { [] { return true; } }),
        },
        {
            // Exits
            Entrance(KF_LINKS_HOUSE, { [] { return true; } }),
            Entrance(KF_MIDOS_HOUSE, { [] { return true; } }),
            Entrance(KF_SARIAS_HOUSE, { [] { return true; } }),
            Entrance(KF_HOUSE_OF_TWINS, { [] { return true; } }),
            Entrance(KF_KNOW_IT_ALL_HOUSE, { [] { return true; } }),
            Entrance(KF_KOKIRI_SHOP, { [] { return true; } }),
            Entrance(KF_OUTSIDE_DEKU_TREE,
                     { [] {
                          return (IsAdult && (CanPassEnemy(85, 2, 0, 3) || ForestTempleClear)) ||
                                 (IsChild && CanPassAnyEnemy(85, 0, 1, { 1, 2 }) &&
                                  (OpenForest.Is(OPENFOREST_OPEN) || ShowedMidoSwordAndShield));
                      },
                       /*Glitched*/
                       [] {
                           return CanDoGlitch(GlitchType::LedgeCancel, GlitchDifficulty::NOVICE) ||
                                  CanDoGlitch(GlitchType::ASlide, GlitchDifficulty::INTERMEDIATE) ||
                                  CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE);
                       } }),
            Entrance(THE_LOST_WOODS, { [] { return true; } }),
            Entrance(LW_BRIDGE_FROM_FOREST,
                     { [] { return IsAdult || OpenForest.IsNot(OPENFOREST_CLOSED) || DekuTreeClear; },
                       /*Glitched*/
                       [] {
                           return CanLeaveForest &&
                                  (CanDoGlitch(GlitchType::LedgeCancel, GlitchDifficulty::NOVICE) ||
                                   CanDoGlitch(GlitchType::ASlide, GlitchDifficulty::INTERMEDIATE) ||
                                   CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) ||
                                   GlitchWWTEscape);
                       } }),
            Entrance(KF_STORMS_GROTTO,
                     { [] { return CanOpenStormGrotto; },
                       /*Glitched*/
                       [] {
                           return (CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::INTERMEDIATE) ||
                                   ((Bugs || Fish) && CanShield &&
                                    CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)) ||
                                   ((Bugs || Fish) && HasBombchus && CanShield &&
                                    CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))) &&
                                  SongOfStorms && (ShardOfAgony || LogicGrottosWithoutAgony);
                       } }),
        });

    static constexpr auto ForEachEnemy_OutsideDekuTree = [](auto& enemyCheckFn) {
        return (IsChild && enemyCheckFn(85, 0, 1, {})) || (IsAdult && ShuffleDungeonEntrances.Is(SHUFFLEDUNGEONS_OFF) &&
                                                           !ForestTempleClear && enemyCheckFn(85, 2, 1, {}));
    };
    areaTable[KF_OUTSIDE_DEKU_TREE] =
        Area("KF Outside Deku Tree", "Kokiri Forest", KOKIRI_FOREST, NO_DAY_NIGHT_CYCLE,
             {
                 // Events
                 EventAccess(&DekuBabaSticks,
                             { [] { return DekuBabaSticks || ForEachEnemy_OutsideDekuTree(CanGetDekuBabaSticks); } }),
                 EventAccess(&DekuBabaNuts,
                             { [] { return DekuBabaNuts || ForEachEnemy_OutsideDekuTree(CanGetDekuBabaNuts); } }),
                 EventAccess(&ShowedMidoSwordAndShield,
                             { [] { return ShowedMidoSwordAndShield || (IsChild && KokiriSword && DekuShield); } }),
             },
             {
                 // Locations
                 LocationAccess(KF_DEKU_TREE_GOSSIP_STONE_LEFT, { [] { return true; } }),
                 LocationAccess(KF_DEKU_TREE_GOSSIP_STONE_RIGHT, { [] { return true; } }),
             },
             {
                 // Exits
                 Entrance(DEKU_TREE_ENTRYWAY,
                          { [] {
                               return IsChild || (ShuffleDungeonEntrances.IsNot(SHUFFLEDUNGEONS_OFF) &&
                                                  (OpenForest.Is(OPENFOREST_OPEN) || ShowedMidoSwordAndShield));
                           },
                            /*Glitched*/
                            [] {
                                return CanDoGlitch(GlitchType::HammerSlide, GlitchDifficulty::INTERMEDIATE) ||
                                       CanDoGlitch(GlitchType::HoverBoost, GlitchDifficulty::INTERMEDIATE);
                            } }),
                 Entrance(KOKIRI_FOREST,
                          { [] {
                               return (IsAdult && (CanPassEnemy(85, 2, 0, 3) || ForestTempleClear)) ||
                                      (IsChild && (OpenForest.Is(OPENFOREST_OPEN) || ShowedMidoSwordAndShield));
                           },
                            /*Glitched*/
                            [] {
                                return CanDoGlitch(GlitchType::ASlide, GlitchDifficulty::INTERMEDIATE) ||
                                       CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE);
                            } }),
             });

    areaTable[KF_LINKS_HOUSE] =
        Area("KF Link's House", "KF Link's House", NONE, NO_DAY_NIGHT_CYCLE, {},
             {
                 // Locations
                 LocationAccess(KF_LINKS_HOUSE_COW,
                                { [] { return IsAdult && CanPlay(EponasSong) && LinksCow; },
                                  /*Glitched*/
                                  [] {
                                      return (CanDoGlitch(GlitchType::IndoorBombOI, GlitchDifficulty::EXPERT) ||
                                              ((Bugs || Fish) && CanShield &&
                                               (CanSurviveDamage || (NumBottles >= 2 && Fairy)) &&
                                               CanDoGlitch(GlitchType::QPA, GlitchDifficulty::EXPERT))) &&
                                             CanDoGlitch(GlitchType::RestrictedItems, GlitchDifficulty::NOVICE) &&
                                             Bombs && IsAdult && EponasSong && LinksCow;
                                  } }),
             },
             { // Exits
               Entrance(KOKIRI_FOREST, { [] { return true; } }) });

    areaTable[KF_MIDOS_HOUSE] = Area("KF Mido's House", "KF Mido's House", NONE, NO_DAY_NIGHT_CYCLE, {},
                                     {
                                         // Locations
                                         LocationAccess(KF_MIDOS_TOP_LEFT_CHEST, { [] { return true; } }),
                                         LocationAccess(KF_MIDOS_TOP_RIGHT_CHEST, { [] { return true; } }),
                                         LocationAccess(KF_MIDOS_BOTTOM_LEFT_CHEST, { [] { return true; } }),
                                         LocationAccess(KF_MIDOS_BOTTOM_RIGHT_CHEST, { [] { return true; } }),
                                     },
                                     {
                                         // Exits
                                         Entrance(KOKIRI_FOREST, { [] { return true; } }),
                                     });

    areaTable[KF_SARIAS_HOUSE] = Area("KF Saria's House", "KF Saria's House", NONE, NO_DAY_NIGHT_CYCLE, {}, {},
                                      {
                                          // Exits
                                          Entrance(KOKIRI_FOREST, { [] { return true; } }),
                                      });

    areaTable[KF_HOUSE_OF_TWINS] = Area("KF House of Twins", "KF House of Twins", NONE, NO_DAY_NIGHT_CYCLE, {}, {},
                                        {
                                            // Exits
                                            Entrance(KOKIRI_FOREST, { [] { return true; } }),
                                        });

    areaTable[KF_KNOW_IT_ALL_HOUSE] =
        Area("KF Know It All House", "KF Know It All House", NONE, NO_DAY_NIGHT_CYCLE, {}, {},
             {
                 // Exits
                 Entrance(KOKIRI_FOREST, { [] { return true; } }),
             });

    areaTable[KF_KOKIRI_SHOP] = Area("KF Kokiri Shop", "KF Kokiri Shop", NONE, NO_DAY_NIGHT_CYCLE, {},
                                     {
                                         // Locations
                                         LocationAccess(KF_SHOP_ITEM_1, { [] { return true; } }),
                                         LocationAccess(KF_SHOP_ITEM_2, { [] { return true; } }),
                                         LocationAccess(KF_SHOP_ITEM_3, { [] { return true; } }),
                                         LocationAccess(KF_SHOP_ITEM_4, { [] { return true; } }),
                                         LocationAccess(KF_SHOP_ITEM_5, { [] { return true; } }),
                                         LocationAccess(KF_SHOP_ITEM_6, { [] { return true; } }),
                                         LocationAccess(KF_SHOP_ITEM_7, { [] { return true; } }),
                                         LocationAccess(KF_SHOP_ITEM_8, { [] { return true; } }),
                                     },
                                     {
                                         // Exits
                                         Entrance(KOKIRI_FOREST, { [] { return true; } }),
                                     });

    areaTable[KF_STORMS_GROTTO] = Area("KF Storms Grotto", "KF Storms Grotto", NONE, NO_DAY_NIGHT_CYCLE, grottoEvents,
                                       {
                                           // Locations
                                           LocationAccess(KF_STORMS_GROTTO_CHEST, { [] { return true; } }),
                                           LocationAccess(KF_STORMS_GROTTO_GOSSIP_STONE, { [] { return true; } }),
                                       },
                                       { // Exits
                                         Entrance(KOKIRI_FOREST, { [] { return true; } }) });

    areaTable[LW_FOREST_EXIT] = Area("LW Forest Exit", "Lost Woods", NONE, NO_DAY_NIGHT_CYCLE, {}, {},
                                     { // Exits
                                       Entrance(KOKIRI_FOREST, { [] { return true; } }) });

    areaTable[THE_LOST_WOODS] = Area(
        "Lost Woods", "Lost Woods", THE_LOST_WOODS, NO_DAY_NIGHT_CYCLE,
        {
            // Events
            EventAccess(&OddMushroomAccess,
                        { [] { return OddMushroomAccess || (IsAdult && (CojiroAccess || Cojiro)); } }),
            EventAccess(&PoachersSawAccess, { [] { return PoachersSawAccess || (IsAdult && OddPoulticeAccess); } }),
            EventAccess(&GossipStoneFairy, { [] { return GossipStoneFairy || CanSummonGossipFairyWithoutSuns; } }),
            EventAccess(&BeanPlantFairy, { [] { return BeanPlantFairy || CanPlay(SongOfStorms); } }),
            EventAccess(&BugShrub, { [] { return IsChild && CanCutShrubs; },
                                     /*Glitched*/
                                     [] {
                                         return IsChild && Sticks &&
                                                CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED);
                                     } }),
        },
        { // Locations
          LocationAccess(LW_SKULL_KID, { [] { return IsChild && CanPlay(SariasSong); },
                                         /*Glitched*/
                                         [] {
                                             return IsChild && (Fish || Bugs) && SariasSong && CanShield &&
                                                    (CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED) ||
                                                     (HasBombchus &&
                                                      CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED)));
                                         } }),
          LocationAccess(LW_TRADE_COJIRO, { [] { return IsAdult && Cojiro; } }),
          LocationAccess(LW_TRADE_ODD_POULTICE, { [] { return IsAdult && OddPoultice && Cojiro; } }),
          LocationAccess(LW_OCARINA_MEMORY_GAME,
                         { [] { return IsChild && Ocarina && (OcarinaButtonsCount >= 5); },
                           /*Glitched*/
                           [] {
                               return IsChild &&
                                      (CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::INTERMEDIATE) ||
                                       ((Fish || Bugs) && CanShield &&
                                        CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)) ||
                                       ((Bugs || Fish) && HasBombchus && CanShield &&
                                        CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED)));
                           } }),
          LocationAccess(LW_TARGET_IN_WOODS, { [] { return IsChild && CanUse(SLINGSHOT); } }),
          LocationAccess(LW_DEKU_SCRUB_NEAR_BRIDGE, { [] { return IsChild && CanStunDeku; } }),
          LocationAccess(LW_GOSSIP_STONE, { [] { return true; } }),
          LocationAccess(LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_1, { [] {
                             return IsChild && (CanDive || (CanUse(IRON_BOOTS) && CanSurviveUnderwaterFor(4)) ||
                                                CanUse(BOOMERANG));
                         } }),
          LocationAccess(LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_2, { [] {
                             return IsChild && (CanDive || (CanUse(IRON_BOOTS) && CanSurviveUnderwaterFor(4)) ||
                                                CanUse(BOOMERANG));
                         } }),
          LocationAccess(LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_3, { [] {
                             return IsChild && (CanDive || (CanUse(IRON_BOOTS) && CanSurviveUnderwaterFor(4)) ||
                                                CanUse(BOOMERANG));
                         } }),
          LocationAccess(LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_4, { [] {
                             return IsChild && (CanDive || (CanUse(IRON_BOOTS) && CanSurviveUnderwaterFor(4)) ||
                                                CanUse(BOOMERANG));
                         } }),
          LocationAccess(LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_5, { [] {
                             return IsChild && (CanDive || (CanUse(IRON_BOOTS) && CanSurviveUnderwaterFor(4)) ||
                                                CanUse(BOOMERANG));
                         } }),
          LocationAccess(LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_6, { [] {
                             return IsChild && (CanDive || (CanUse(IRON_BOOTS) && CanSurviveUnderwaterFor(4)) ||
                                                CanUse(BOOMERANG));
                         } }),
          LocationAccess(LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_7, { [] {
                             return IsChild && (CanDive || (CanUse(IRON_BOOTS) && CanSurviveUnderwaterFor(4)) ||
                                                CanUse(BOOMERANG));
                         } }),
          LocationAccess(LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_8, { [] {
                             return IsChild && (CanDive || (CanUse(IRON_BOOTS) && CanSurviveUnderwaterFor(4)) ||
                                                CanUse(BOOMERANG));
                         } }) },
        {
            // Exits
            Entrance(LW_FOREST_EXIT, { [] { return true; } }),
            Entrance(GC_WOODS_WARP, { [] { return true; } }),
            Entrance(LW_BRIDGE,
                     { [] {
                          return CanLeaveForest &&
                                 ((IsAdult && CanPlantBean(THE_LOST_WOODS)) || CanUse(HOVER_BOOTS) || CanUse(LONGSHOT));
                      },
                       /*Glitched*/
                       [] {
                           return CanLeaveForest &&
                                  (CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::NOVICE) ||
                                   (CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE) && HasBombchus) ||
                                   CanDoGlitch(GlitchType::HookshotJump_Boots, GlitchDifficulty::INTERMEDIATE));
                       } }),
            Entrance(ZORAS_RIVER,
                     { [] { return CanLeaveForest && (CanDive || CanUse(IRON_BOOTS)); },
                       /*Glitched*/
                       [] {
                           return CanLeaveForest &&
                                  (CanDoGlitch(GlitchType::TripleSlashClip, GlitchDifficulty::NOVICE) ||
                                   CanDoGlitch(GlitchType::NaviDive_Stick, GlitchDifficulty::ADVANCED) ||
                                   ((Bugs || Fish) && CanUse(HOVER_BOOTS) &&
                                    CanDoGlitch(GlitchType::CutsceneDive, GlitchDifficulty::INTERMEDIATE)) ||
                                   (CanUse(FARORES_WIND) &&
                                    (FaroresWindAnywhere ||
                                     (CanDoGlitch(GlitchType::RestrictedItems, GlitchDifficulty::NOVICE) &&
                                      (HasBottle || (IsAdult && (HasBoots || ClaimCheck)) || (IsChild && WeirdEgg)))) &&
                                    ((CanUse(NAYRUS_LOVE) &&
                                      CanDoGlitch(GlitchType::CutsceneDive, GlitchDifficulty::NOVICE)) ||
                                     (CanUseMagicArrow &&
                                      CanDoGlitch(GlitchType::CutsceneDive, GlitchDifficulty::ADVANCED)))));
                       } }),
            Entrance(LW_BEYOND_MIDO,
                     { [] { return IsChild || CanPlay(SariasSong); },
                       /*Glitched*/
                       [] {
                           return CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) ||
                                  CanDoGlitch(GlitchType::LedgeCancel, GlitchDifficulty::NOVICE) ||
                                  CanDoGlitch(GlitchType::HookshotJump_Boots, GlitchDifficulty::INTERMEDIATE) ||
                                  (CanDoGlitch(GlitchType::HookshotJump_Bonk, GlitchDifficulty::ADVANCED) &&
                                   (CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::INTERMEDIATE) || HoverBoots)) ||
                                  ((CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::INTERMEDIATE) ||
                                    ((Bugs || Fish) && CanShield &&
                                     CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)) ||
                                    ((Bugs || Fish) && HasBombchus && CanShield &&
                                     CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))) &&
                                   SariasSong);
                       } }),
            Entrance(LW_NEAR_SHORTCUTS_GROTTO, { [] { return Here(THE_LOST_WOODS, [] { return CanBlastOrSmash; }); },
                                                 /*Glitched*/
                                                 [] {
                                                     return Here(THE_LOST_WOODS, [] {
                                                         return CanUse(STICKS) &&
                                                                CanDoGlitch(GlitchType::QPA,
                                                                            GlitchDifficulty::ADVANCED);
                                                     });
                                                 } }),
        });

    areaTable[LW_BEYOND_MIDO] =
        Area("LW Beyond Mido", "Lost Woods", THE_LOST_WOODS, NO_DAY_NIGHT_CYCLE,
             {
                 // Events
                 EventAccess(&ButterflyFairy, { [] { return ButterflyFairy || CanUse(STICKS); } }),
             },
             {
                 // Locations
                 LocationAccess(LW_DEKU_SCRUB_NEAR_DEKU_THEATER_RIGHT, { [] { return IsChild && CanStunDeku; } }),
                 LocationAccess(LW_DEKU_SCRUB_NEAR_DEKU_THEATER_LEFT, { [] { return IsChild && CanStunDeku; } }),
                 LocationAccess(LW_IN_BOULDER_BLUE_RUPEE,
                                { [] { return Here(LW_BEYOND_MIDO, [] { return CanBlastOrSmash; }); },
                                  [] {
                                      return Here(LW_BEYOND_MIDO, [] {
                                          return IsChild && CanUse(STICKS) &&
                                                 CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED);
                                      });
                                  } }),
             },
             {
                 // Exits
                 Entrance(LW_FOREST_EXIT, { [] { return true; } }),
                 Entrance(THE_LOST_WOODS,
                          { [] { return IsChild || CanPlay(SariasSong); },
                            /*Glitched*/
                            [] {
                                return CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) ||
                                       CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::NOVICE) ||
                                       ((CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::INTERMEDIATE) ||
                                         ((Bugs || Fish) && CanShield && Bombs &&
                                          (CanSurviveDamage || (NumBottles >= 2 && Fairy)) &&
                                          CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)) ||
                                         ((Bugs || Fish) && HasBombchus && CanShield &&
                                          CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))) &&
                                        SariasSong);
                            } }),
                 Entrance(SFM_ENTRYWAY, { [] { return true; } }),
                 Entrance(DEKU_THEATER, { [] { return true; } }),
                 Entrance(LW_SCRUBS_GROTTO, { [] { return Here(LW_BEYOND_MIDO, [] { return CanBlastOrSmash; }); },
                                              /*Glitched*/
                                              [] {
                                                  return Here(LW_BEYOND_MIDO, [] {
                                                      return IsChild && CanUse(STICKS) &&
                                                             CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED);
                                                  });
                                              } }),
             });

    areaTable[LW_NEAR_SHORTCUTS_GROTTO] =
        Area("LW Near Shortcuts Grotto", "LW Near Shortcuts Grotto", NONE, NO_DAY_NIGHT_CYCLE, grottoEvents,
             {
                 // Locations
                 LocationAccess(LW_NEAR_SHORTCUTS_GROTTO_CHEST, { [] { return true; } }),
                 LocationAccess(LW_NEAR_SHORTCUTS_GROTTO_GOSSIP_STONE, { [] { return true; } }),
             },
             {
                 // Exits
                 Entrance(THE_LOST_WOODS, { [] { return true; } }),
             });

    areaTable[DEKU_THEATER] =
        Area("Deku Theater", "Deku Theater", NONE, NO_DAY_NIGHT_CYCLE, {},
             {
                 // Locations
                 LocationAccess(DEKU_THEATER_SKULL_MASK, { [] { return IsChild && SkullMask; } }),
                 LocationAccess(DEKU_THEATER_MASK_OF_TRUTH, { [] { return IsChild && MaskOfTruth; } }),
             },
             {
                 // Exits
                 Entrance(LW_BEYOND_MIDO, { [] { return true; } }),
             });

    areaTable[LW_SCRUBS_GROTTO] = Area("LW Scrubs Grotto", "LW Scrubs Grotto", NONE, NO_DAY_NIGHT_CYCLE, {},
                                       {
                                           // Locations
                                           LocationAccess(LW_DEKU_SCRUB_GROTTO_REAR, { [] { return CanStunDeku; } }),
                                           LocationAccess(LW_DEKU_SCRUB_GROTTO_FRONT, { [] { return CanStunDeku; } }),
                                       },
                                       {
                                           // Exits
                                           Entrance(LW_BEYOND_MIDO, { [] { return true; } }),
                                       });

    areaTable[SFM_ENTRYWAY] =
        Area("SFM Entryway", "Sacred Forest Meadow", SACRED_FOREST_MEADOW, NO_DAY_NIGHT_CYCLE, {}, {},
             {
                 // Exits
                 Entrance(LW_BEYOND_MIDO, { [] { return true; } }),
                 Entrance(SACRED_FOREST_MEADOW, { [] {
                              return ((IsChild && CanDefeatEnemy(86, 0, 0, 1) &&
                                       CanPassEnemies(86, 0, 0, { 5, 6, 7, 10 }, SpaceAroundEnemy::NARROW) &&
                                       CanPassEnemies(86, 0, 0, { 8, 9 })) ||
                                      (IsAdult && CanPassEnemy(86, 2, 0, 11) &&
                                       (CanUse(SCARECROW) ||
                                        (Settings::Enemizer
                                             ? (CanPassEnemies(86, 2, 0, { 6, 7, 8, 9, 10 }, SpaceAroundEnemy::NARROW))
                                             : CanDefeatEnemy(ENEMY_MOBLIN_SPEAR)))));
                          } }),
                 Entrance(SFM_WOLFOS_GROTTO, { [] { return CanOpenBombGrotto; } }),
             });

    static constexpr auto ForEachEnemy_SacredForestMeadow = [](auto& enemyCheckFn) {
        return (IsChild && enemyCheckFn(86, 0, 0, { 5, 6, 7, 8, 9, 10 })) || (IsAdult && enemyCheckFn(86, 2, 0, {}));
    };
    areaTable[SACRED_FOREST_MEADOW] = Area(
        "Sacred Forest Meadow", "Sacred Forest Meadow", SACRED_FOREST_MEADOW, NO_DAY_NIGHT_CYCLE,
        {
            // Events
            EventAccess(&DekuBabaSticks,
                        { [] { return DekuBabaSticks || ForEachEnemy_SacredForestMeadow(CanGetDekuBabaSticks); } }),
            EventAccess(&DekuBabaNuts,
                        { [] { return DekuBabaNuts || ForEachEnemy_SacredForestMeadow(CanGetDekuBabaNuts); } }),
            EventAccess(&GossipStoneFairy, { [] { return GossipStoneFairy || CanSummonGossipFairyWithoutSuns; } }),
        },
        {
            // Locations
            LocationAccess(SONG_FROM_SARIA, { [] { return IsChild && ChildCanAccess(HC_GARDEN); } }),
            LocationAccess(SHEIK_IN_FOREST, { [] { return IsAdult; } }),
            LocationAccess(SFM_MAZE_GOSSIP_STONE_LOWER, { [] { return true; } }),
            LocationAccess(SFM_MAZE_GOSSIP_STONE_UPPER, { [] { return true; } }),
            LocationAccess(SFM_SARIA_GOSSIP_STONE, { [] { return true; } }),
        },
        {
            // Exits
            Entrance(
                SFM_ENTRYWAY, { [] {
                    return ((IsChild && CanPassEnemies(86, 0, 0, { 8, 9 })) || (IsAdult && CanPassEnemy(86, 2, 0, 11)));
                } }),
            Entrance(
                FOREST_TEMPLE_ENTRYWAY,
                { [] { return CanUse(HOOKSHOT); },
                  /*Glitched*/ [] { return CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE); } }),
            Entrance(
                SFM_FAIRY_GROTTO, { [] {
                    return ((IsChild && CanPassEnemies(86, 0, 0, { 8, 9 })) || (IsAdult && CanPassEnemy(86, 2, 0, 11)));
                } }),
            Entrance(SFM_STORMS_GROTTO,
                     { [] { return CanOpenStormGrotto; },
                       /*Glitched*/
                       [] {
                           return (CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::INTERMEDIATE) ||
                                   ((Bugs || Fish) && CanShield &&
                                    CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)) ||
                                   ((Bugs || Fish) && HasBombchus && CanShield &&
                                    CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))) &&
                                  SongOfStorms && (ShardOfAgony || LogicGrottosWithoutAgony);
                       } }),
        });

    areaTable[SFM_FAIRY_GROTTO] = Area("SFM Fairy Grotto", "SFM Fairy Grotto", NONE, NO_DAY_NIGHT_CYCLE,
                                       {
                                           // Events
                                           EventAccess(&FreeFairies, { [] { return true; } }),
                                       },
                                       {},
                                       {
                                           // Exits
                                           Entrance(SACRED_FOREST_MEADOW, { [] { return true; } }),
                                       });

    areaTable[SFM_WOLFOS_GROTTO] =
        Area("SFM Wolfos Grotto", "SFM Wolfos Grotto", NONE, NO_DAY_NIGHT_CYCLE, {},
             {
                 // Locations
                 LocationAccess(SFM_WOLFOS_GROTTO_CHEST, { [] { return CanDefeatEnemies(62, 0, 7); } }),
             },
             {
                 // Exits
                 Entrance(SFM_ENTRYWAY, { [] { return true; } }),
             });

    areaTable[SFM_STORMS_GROTTO] = Area("SFM Storms Grotto", "SFM Storms Grotto", NONE, NO_DAY_NIGHT_CYCLE, {},
                                        {
                                            // Locations
                                            LocationAccess(SFM_DEKU_SCRUB_GROTTO_REAR, { [] { return CanStunDeku; } }),
                                            LocationAccess(SFM_DEKU_SCRUB_GROTTO_FRONT, { [] { return CanStunDeku; } }),
                                        },
                                        {
                                            // Exits
                                            Entrance(SACRED_FOREST_MEADOW, { [] { return true; } }),
                                        });

    areaTable[LW_BRIDGE_FROM_FOREST] =
        Area("LW Bridge From Forest", "Lost Woods", THE_LOST_WOODS, NO_DAY_NIGHT_CYCLE, {},
             {
                 // Locations
                 LocationAccess(LW_GIFT_FROM_SARIA, { [] { return true; } }),
             },
             {
                 // Exits
                 Entrance(LW_BRIDGE, { [] { return true; } }),
             });

    areaTable[LW_BRIDGE] =
        Area("LW Bridge", "Lost Woods", THE_LOST_WOODS, NO_DAY_NIGHT_CYCLE, {}, {},
             {
                 // Exits
                 Entrance(KOKIRI_FOREST, { [] { return true; } }),
                 Entrance(HYRULE_FIELD, { [] { return true; } }),
                 Entrance(THE_LOST_WOODS,
                          { [] { return CanUse(LONGSHOT); },
                            /*Glitched*/
                            [] {
                                return (CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) && Bombs &&
                                        CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE)) ||
                                       CanDoGlitch(GlitchType::HookshotJump_Boots, GlitchDifficulty::NOVICE) ||
                                       CanDoGlitch(GlitchType::HookshotJump_Bonk, GlitchDifficulty::NOVICE);
                            } }),
             });
}
