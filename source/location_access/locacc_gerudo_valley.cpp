#include "location_access.hpp"
#include "logic.hpp"
#include "entrance.hpp"
#include "enemizer_logic.hpp"

using namespace Logic;
using namespace Settings;

void AreaTable_Init_GerudoValley() {
    areaTable[GERUDO_VALLEY] = Area(
        "Gerudo Valley", "Gerudo Valley", GERUDO_VALLEY, DAY_NIGHT_CYCLE,
        {
            // Events
            EventAccess(&BugRock, { [] { return BugRock || IsChild; } }),
        },
        {},
        {
            // Exits
            Entrance(HYRULE_FIELD, { [] { return true; } }),
            Entrance(GV_UPPER_STREAM, { [] { return true; } }),
            Entrance(GV_CRATE_LEDGE, { [] { return IsChild || CanUse(LONGSHOT); } }),
            Entrance(GV_GROTTO_LEDGE, { [] { return true; } }),
            Entrance(GV_FORTRESS_SIDE,
                     { [] {
                          return (IsAdult && (CanRideEpona || CanUse(LONGSHOT) ||
                                              GerudoFortress.Is(GERUDOFORTRESS_OPEN) || CarpenterRescue)) ||
                                 (IsChild && CanUse(HOOKSHOT));
                      },
                       /*Glitched*/
                       [] {
                           return (HasBombchus && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE)) ||
                                  (IsChild && CanDoGlitch(GlitchType::SeamWalk, GlitchDifficulty::HERO)) ||
                                  (IsAdult &&
                                   (CanDoGlitch(GlitchType::HoverBoost, GlitchDifficulty::NOVICE) ||
                                    CanDoGlitch(GlitchType::HammerSlide, GlitchDifficulty::NOVICE) ||
                                    CanDoGlitch(GlitchType::HookshotJump_Boots, GlitchDifficulty::ADVANCED) ||
                                    (CanUse(HOVER_BOOTS) &&
                                     (CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::INTERMEDIATE) ||
                                      (CanSurviveDamage && (Bombs || HasBombchus) &&
                                       CanDoGlitch(GlitchType::SuperSlide, GlitchDifficulty::NOVICE)) ||
                                      (Bombs && CanDoGlitch(GlitchType::SuperSlide, GlitchDifficulty::ADVANCED))))));
                       } }),
        });

    areaTable[GV_UPPER_STREAM] = Area(
        "GV Upper Stream", "Gerudo Valley", GERUDO_VALLEY, DAY_NIGHT_CYCLE,
        {
            // Events
            EventAccess(&GossipStoneFairy, { [] { return GossipStoneFairy || CanSummonGossipFairy; } }),
            EventAccess(&BeanPlantFairy,
                        { [] { return BeanPlantFairy || (CanPlantBean(GV_UPPER_STREAM) && CanPlay(SongOfStorms)); } }),
        },
        {
            // Locations
            LocationAccess(GV_WATERFALL_FREESTANDING_POH, { [] { return true; } }),
            LocationAccess(GV_COW, { [] { return IsChild && CanPlay(EponasSong); },
                                     /*Glitched*/
                                     [] {
                                         return IsChild && EponasSong &&
                                                (CanDoGlitch(GlitchType::OutdoorBombOI,
                                                             GlitchDifficulty::INTERMEDIATE) ||
                                                 ((Bugs || Fish) && CanShield &&
                                                  CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)) ||
                                                 ((Bugs || Fish) && HasBombchus && CanShield &&
                                                  CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED)));
                                     } }),
            LocationAccess(GV_GOSSIP_STONE, { [] { return true; } }),
        },
        {
            // Exits
            Entrance(GV_LOWER_STREAM, { [] { return true; } }),
        });

    areaTable[GV_LOWER_STREAM] = Area("GV Lower Stream", "Gerudo Valley", GERUDO_VALLEY, DAY_NIGHT_CYCLE, {}, {},
                                      {
                                          // Exits
                                          Entrance(LAKE_HYLIA, { [] { return true; } }),
                                      });

    areaTable[GV_GROTTO_LEDGE] = Area("GV Grotto Ledge", "Gerudo Valley", GERUDO_VALLEY, DAY_NIGHT_CYCLE, {}, {},
                                      {
                                          // Exits
                                          Entrance(GV_LOWER_STREAM, { [] { return true; } }),
                                          Entrance(GV_OCTOROK_GROTTO, { [] { return CanUse(SILVER_GAUNTLETS); } }),
                                          Entrance(GV_CRATE_LEDGE, { [] { return CanUse(LONGSHOT); } }),
                                      });

    areaTable[GV_CRATE_LEDGE] = Area("GV Crate Ledge", "Gerudo Valley", GERUDO_VALLEY, DAY_NIGHT_CYCLE, {},
                                     {
                                         // Locations
                                         LocationAccess(GV_CRATE_FREESTANDING_POH, { [] { return true; } }),
                                     },
                                     {
                                         // Exits
                                         Entrance(GV_LOWER_STREAM, { [] { return true; } }),
                                     });

    areaTable[GV_FORTRESS_SIDE] = Area(
        "GV Fortress Side", "Gerudo Valley", GERUDO_VALLEY, DAY_NIGHT_CYCLE,
        {
            // Events
            EventAccess(&BrokenSwordAccess, { [] { return IsAdult && (PoachersSawAccess || PoachersSaw); } }),
        },
        {
            // Locations
            LocationAccess(GV_CHEST, { [] { return IsAdult && (CanUse(MEGATON_HAMMER) || LogicGVHammerChest); },
                                       /*Glitched*/
                                       [] {
                                           return IsAdult &&
                                                  (CanDoGlitch(GlitchType::LedgeCancel, GlitchDifficulty::NOVICE) ||
                                                   CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) ||
                                                   (CanUse(STICKS) &&
                                                    CanDoGlitch(GlitchType::QPA, GlitchDifficulty::NOVICE) &&
                                                    (CanTakeDamageTwice ||
                                                     CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED))));
                                       } }),
            LocationAccess(GV_TRADE_SAW, { [] { return IsAdult && PoachersSaw; } }),
        },
        {
            // Exits
            Entrance(GERUDO_FORTRESS, { [] { return true; } }),
            Entrance(GV_UPPER_STREAM, { [] { return true; } }),
            Entrance(GERUDO_VALLEY,
                     { [] {
                          return IsChild || CanRideEpona || CanUse(LONGSHOT) ||
                                 GerudoFortress.Is(GERUDOFORTRESS_OPEN) || CarpenterRescue;
                      },
                       /*Glitched*/
                       [] {
                           return (HasBombchus && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE)) ||
                                  CanDoGlitch(GlitchType::HoverBoost, GlitchDifficulty::NOVICE) ||
                                  CanDoGlitch(GlitchType::HammerSlide, GlitchDifficulty::NOVICE) ||
                                  CanDoGlitch(GlitchType::HookshotJump_Boots, GlitchDifficulty::ADVANCED) ||
                                  (CanUse(HOVER_BOOTS) &&
                                   (CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::INTERMEDIATE) ||
                                    (CanSurviveDamage && (Bombs || HasBombchus) &&
                                     CanDoGlitch(GlitchType::SuperSlide, GlitchDifficulty::NOVICE)) ||
                                    (Bombs && CanDoGlitch(GlitchType::SuperSlide, GlitchDifficulty::ADVANCED))));
                       } }),
            Entrance(GV_CARPENTER_TENT, { [] { return IsAdult; },
                                          /*Glitched*/ [] { return GlitchGVTentAsChild.Value<bool>(); } }),
            Entrance(GV_STORMS_GROTTO,
                     { [] { return IsAdult && CanOpenStormGrotto; },
                       /*Glitched*/
                       [] {
                           return (CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::INTERMEDIATE) ||
                                   ((Bugs || Fish) && CanShield &&
                                    CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)) ||
                                   ((Bugs || Fish) && HasBombchus && CanShield &&
                                    CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))) &&
                                  IsAdult && SongOfStorms && (ShardOfAgony || LogicGrottosWithoutAgony);
                       } }),
        });

    areaTable[GV_CARPENTER_TENT] = Area("GV Carpenter Tent", "GV Carpenter Tent", NONE, NO_DAY_NIGHT_CYCLE, {}, {},
                                        {
                                            // Exits
                                            Entrance(GV_FORTRESS_SIDE, { [] { return true; } }),
                                        });

    areaTable[GV_OCTOROK_GROTTO] = Area("GV Octorok Grotto", "GV Octorok Grotto", NONE, NO_DAY_NIGHT_CYCLE, {},
                                        {
                                            LocationAccess(GV_OCTOROCK_GROTTO_BLUE_RUPEE_1, { [] { return true; } }),
                                            LocationAccess(GV_OCTOROCK_GROTTO_BLUE_RUPEE_2, { [] { return true; } }),
                                            LocationAccess(GV_OCTOROCK_GROTTO_BLUE_RUPEE_3, { [] { return true; } }),
                                            LocationAccess(GV_OCTOROCK_GROTTO_GREEN_RUPEE_1, { [] { return true; } }),
                                            LocationAccess(GV_OCTOROCK_GROTTO_GREEN_RUPEE_2, { [] { return true; } }),
                                            LocationAccess(GV_OCTOROCK_GROTTO_GREEN_RUPEE_3, { [] { return true; } }),
                                            LocationAccess(GV_OCTOROCK_GROTTO_GREEN_RUPEE_4, { [] { return true; } }),
                                            LocationAccess(GV_OCTOROCK_GROTTO_RED_RUPEE, { [] { return true; } }),

                                        },
                                        {
                                            // Exits
                                            Entrance(GV_GROTTO_LEDGE, { [] { return true; } }),
                                        });

    areaTable[GV_STORMS_GROTTO] = Area("GV Storms Grotto", "GV Storms Grotto", NONE, NO_DAY_NIGHT_CYCLE, {},
                                       {
                                           // Locations
                                           LocationAccess(GV_DEKU_SCRUB_GROTTO_REAR, { [] { return CanStunDeku; } }),
                                           LocationAccess(GV_DEKU_SCRUB_GROTTO_FRONT, { [] { return CanStunDeku; } }),
                                       },
                                       {
                                           // Exits
                                           Entrance(GV_FORTRESS_SIDE, { [] { return true; } }),
                                       });

    areaTable[GERUDO_FORTRESS] = Area(
        "Gerudo Fortress", "Gerudo Fortress", GERUDO_FORTRESS, NO_DAY_NIGHT_CYCLE,
        {
            // Events
            EventAccess(&CarpenterRescue, { [] { return CanFinishGerudoFortress; } }),
            EventAccess(&GF_GateOpen, { [] { return IsAdult && GerudoToken; } }),
            EventAccess(&GtG_GateOpen, { [] { return GtG_GateOpen || (IsAdult && GerudoToken); } }),
        },
        {
            // Locations
            LocationAccess(GF_CHEST, { [] {
                                          return ((IsAdult || LogicGerudoChildClimb) &&
                                                  (CanUse(HOVER_BOOTS) || CanUse(LONGSHOT))) ||
                                                 (IsAdult && CanUse(SCARECROW));
                                      },
                                       /*Glitched*/
                                       [] {
                                           return (((IsAdult || LogicGerudoChildClimb) &&
                                                    CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::NOVICE)) ||
                                                   (Bombs && HasBombchus &&
                                                    CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::NOVICE))) &&
                                                  (GerudoToken || CanUse(BOW) || CanUse(HOOKSHOT) ||
                                                   CanUse(HOVER_BOOTS) || LogicGerudoKitchen);
                                       } }),
            LocationAccess(GF_NORTH_F1_CARPENTER, { [] { return CanDefeatEnemy(12, 0, 2, 1); },
                                                    /*Glitched*/
                                                    [] {
                                                        return !Settings::Enemizer && SoulGerudo &&
                                                               CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE);
                                                    } }),
            LocationAccess(GF_NORTH_F2_CARPENTER, { [] {
                                                       return CanDefeatEnemy(12, 0, 1, 1) &&
                                                              (GerudoToken || CanUse(BOW) || CanUse(HOOKSHOT) ||
                                                               CanUse(HOVER_BOOTS) || LogicGerudoKitchen);
                                                   },
                                                    /*Glitched*/
                                                    [] {
                                                        return !Settings::Enemizer && SoulGerudo &&
                                                               CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE) &&
                                                               (GerudoToken || CanUse(BOW) || CanUse(HOOKSHOT) ||
                                                                CanUse(HOVER_BOOTS) || LogicGerudoKitchen);
                                                    } }),
            LocationAccess(GF_SOUTH_F1_CARPENTER, { [] { return CanDefeatEnemy(12, 0, 4, 1); },
                                                    /*Glitched*/
                                                    [] {
                                                        return !Settings::Enemizer && SoulGerudo &&
                                                               CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE);
                                                    } }),
            LocationAccess(GF_SOUTH_F2_CARPENTER, { [] { return CanDefeatEnemy(12, 0, 5, 1); },
                                                    /*Glitched*/
                                                    [] {
                                                        return !Settings::Enemizer && SoulGerudo &&
                                                               CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE);
                                                    } }),
            LocationAccess(GF_GERUDO_TOKEN, { [] { return CanFinishGerudoFortress; } }),
        },
        {
            // Exits
            Entrance(GV_FORTRESS_SIDE, { [] { return true; } }),
            Entrance(GF_ARCHERY_RANGE,
                     { [] { return IsChild || GerudoToken; },
                       /*Glitched*/
                       [] { return GlitchGFGuardSneak && (CanUse(BOW) || CanUse(HOOKSHOT) || CanUse(BOOMERANG)); } }),
            Entrance(GF_OUTSIDE_GATE,
                     { [] { return GF_GateOpen; },
                       /*Glitched*/
                       [] {
                           return (IsChild && CanDoGlitch(GlitchType::SeamWalk, GlitchDifficulty::ADVANCED)) ||
                                  ((IsChild ||
                                    ((CanUse(HOOKSHOT) || CanUse(BOW) || CanUse(BOOMERANG)) && GlitchGFGuardSneak)) &&
                                   ((CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE) &&
                                     CanDoGlitch(GlitchType::SeamWalk, GlitchDifficulty::NOVICE)) ||
                                    CanDoGlitch(GlitchType::SeamWalk, GlitchDifficulty::INTERMEDIATE)) &&
                                   (CanUse(STICKS) || CanUse(BIGGORON_SWORD) ||
                                    CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::INTERMEDIATE)));
                       } }),
            Entrance(GERUDO_TRAINING_GROUNDS_ENTRYWAY,
                     { [] { return GtG_GateOpen && (IsAdult || ShuffleDungeonEntrances); },
                       /*Glitched*/
                       [] {
                           return (CanDoGlitch(GlitchType::LedgeClip, GlitchDifficulty::INTERMEDIATE) &&
                                   (HoverBoots || CanDoGlitch(GlitchType::LedgeClip, GlitchDifficulty::ADVANCED))) ||
                                  ((IsChild ||
                                    ((CanUse(HOOKSHOT) || CanUse(BOW) || CanUse(BOOMERANG)) && GlitchGFGuardSneak)) &&
                                   ((CanDoGlitch(GlitchType::ISG, GlitchDifficulty::NOVICE) &&
                                     CanDoGlitch(GlitchType::SeamWalk, GlitchDifficulty::NOVICE)) ||
                                    CanDoGlitch(GlitchType::SeamWalk, GlitchDifficulty::INTERMEDIATE)) &&
                                   (CanUse(STICKS) || CanUse(BIGGORON_SWORD) ||
                                    CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::INTERMEDIATE)));
                       } }),
            Entrance(GF_STORMS_GROTTO,
                     { [] { return IsAdult && CanOpenStormGrotto; },
                       /*Glitched*/
                       [] {
                           return (CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::INTERMEDIATE) ||
                                   ((Bugs || Fish) && CanShield &&
                                    CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)) ||
                                   ((Bugs || Fish) && HasBombchus && CanShield &&
                                    CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))) &&
                                  IsAdult && SongOfStorms && (ShardOfAgony || LogicGrottosWithoutAgony);
                       } }),
        });

    areaTable[GF_ARCHERY_RANGE] =
        Area("GF Archery Range", "Gerudo Fortress", NONE, NO_DAY_NIGHT_CYCLE, {},
             {
                 // Locations
                 LocationAccess(GF_HBA_1000_POINTS, { [] { return GerudoToken && CanRideEpona && Bow && AtDay; } }),
                 LocationAccess(GF_HBA_1500_POINTS, { [] { return GerudoToken && CanRideEpona && Bow && AtDay; } }),
             },
             {
                 // Exits
                 Entrance(GERUDO_FORTRESS, { [] { return IsChild || GerudoToken; } }),
             });

    areaTable[GF_OUTSIDE_GATE] =
        Area("GF Outside Gate", "Gerudo Fortress", NONE, NO_DAY_NIGHT_CYCLE,
             {
                 // Events
                 EventAccess(&GF_GateOpen, { [] {
                     return IsAdult && GerudoToken &&
                            (ShuffleGerudoToken || ShuffleOverworldEntrances /*|| ShuffleSpecialIndoorEntrances*/);
                 } }),
             },
             {},
             {
                 // Exits
                 Entrance(GERUDO_FORTRESS,
                          { [] { return (IsAdult && (Hookshot || !ShuffleOverworldEntrances)) || GF_GateOpen; } }),
                 Entrance(WASTELAND_NEAR_FORTRESS, { [] { return true; } }),
             });

    areaTable[GF_STORMS_GROTTO] = Area("GF Storms Grotto", "GF Storms Grotto", NONE, NO_DAY_NIGHT_CYCLE,
                                       {
                                           // Events
                                           EventAccess(&FreeFairies, { [] { return true; } }),
                                       },
                                       {},
                                       {
                                           // Exits
                                           Entrance(GERUDO_FORTRESS, { [] { return true; } }),
                                       });

    areaTable[WASTELAND_NEAR_FORTRESS] =
        Area("Wasteland Near Fortress", "Haunted Wasteland", HAUNTED_WASTELAND, NO_DAY_NIGHT_CYCLE, {}, {},
             {
                 // Exits
                 Entrance(GF_OUTSIDE_GATE, { [] { return true; } }),
                 Entrance(HAUNTED_WASTELAND,
                          { [] { return CanUse(HOVER_BOOTS) || CanUse(LONGSHOT); },
                            /*Glitched*/
                            [] {
                                return ((Bombs || HasBombchus) && CanSurviveDamage &&
                                        CanDoGlitch(GlitchType::SuperSlide, GlitchDifficulty::NOVICE)) ||
                                       (CanUse(MEGATON_HAMMER) && CanShield &&
                                        CanDoGlitch(GlitchType::SuperSlide, GlitchDifficulty::INTERMEDIATE)) ||
                                       (Bombs && CanDoGlitch(GlitchType::SuperSlide, GlitchDifficulty::ADVANCED)) ||
                                       (Bombs && HasBombchus &&
                                        CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE) &&
                                        CanDoGlitch(GlitchType::ISG, GlitchDifficulty::INTERMEDIATE)) ||
                                       GlitchItemlessWasteland;
                            } }),
             });

    areaTable[HAUNTED_WASTELAND] = Area(
        "Haunted Wasteland", "Haunted Wasteland", HAUNTED_WASTELAND, NO_DAY_NIGHT_CYCLE,
        {
            // Events
            EventAccess(&FairyPot, { [] { return true; } }),
            EventAccess(&NutPot, { [] { return true; } }),
        },
        {
            // Locations
            LocationAccess(WASTELAND_CHEST, { [] { return HasFireSource; },
                                              /*Glitched*/
                                              [] {
                                                  return CanUse(STICKS) &&
                                                         CanDoGlitch(GlitchType::QPA, GlitchDifficulty::INTERMEDIATE);
                                              } }),
            LocationAccess(
                WASTELAND_BOMBCHU_SALESMAN,
                { [] { return AdultsWallet && CanJumpslash; },
                  /*Glitched*/
                  [] { return AdultsWallet && CanDoGlitch(GlitchType::Megaflip, GlitchDifficulty::NOVICE); } }),
        },
        {
            // Exits
            Entrance(WASTELAND_NEAR_COLOSSUS, { [] { return LogicLensWasteland || CanUse(LENS_OF_TRUTH); } }),
            Entrance(WASTELAND_NEAR_FORTRESS,
                     { [] { return CanUse(HOVER_BOOTS) || CanUse(LONGSHOT); },
                       /*Glitched*/
                       [] {
                           return ((Bombs || HasBombchus) && CanSurviveDamage &&
                                   CanDoGlitch(GlitchType::SuperSlide, GlitchDifficulty::NOVICE)) ||
                                  (CanUse(MEGATON_HAMMER) && CanShield &&
                                   CanDoGlitch(GlitchType::SuperSlide, GlitchDifficulty::INTERMEDIATE)) ||
                                  (Bombs && CanDoGlitch(GlitchType::SuperSlide, GlitchDifficulty::ADVANCED)) ||
                                  (HasBombchus && CanDoGlitch(GlitchType::BombHover, GlitchDifficulty::INTERMEDIATE)) ||
                                  GlitchItemlessWasteland;
                       } }),
        });

    areaTable[WASTELAND_NEAR_COLOSSUS] =
        Area("Wasteland Near Colossus", "Haunted Wasteland", NONE, NO_DAY_NIGHT_CYCLE, {}, {},
             {
                 // Exits
                 Entrance(DESERT_COLOSSUS, { [] { return true; } }),
                 Entrance(HAUNTED_WASTELAND, { [] { return LogicReverseWasteland || false; } }),
             });

    static constexpr auto ForEachEnemy_Colossus = [](auto& enemyCheckFn) {
        return (IsChild && enemyCheckFn(92, 0, 0, {})) || (IsAdult && enemyCheckFn(92, 2, 0, {}));
    };
    areaTable[DESERT_COLOSSUS] = Area(
        "Desert Colossus", "Desert Colossus", DESERT_COLOSSUS, DAY_NIGHT_CYCLE,
        {
            // Events
            EventAccess(&DekuBabaSticks,
                        { [] { return DekuBabaSticks || ForEachEnemy_Colossus(CanGetDekuBabaSticks); } }),
            EventAccess(&DekuBabaNuts, { [] { return DekuBabaNuts || ForEachEnemy_Colossus(CanGetDekuBabaNuts); } }),

            EventAccess(&FairyPond, { [] { return FairyPond || CanPlay(SongOfStorms); },
                                      /*Glitched*/
                                      [] {
                                          return (CanDoGlitch(GlitchType::OutdoorBombOI,
                                                              GlitchDifficulty::INTERMEDIATE) ||
                                                  ((Bugs || Fish) && CanShield && Bombs && CanTakeDamage &&
                                                   CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)) ||
                                                  ((Bugs || Fish) && CanShield && HasBombchus &&
                                                   CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))) &&
                                                 SongOfStorms;
                                      } }),
            EventAccess(&BugRock, { [] { return true; } }),
        },
        {
            // Locations
            LocationAccess(COLOSSUS_GOSSIP_STONE, { [] { return true; } }),
        },
        {
            // Exits
            Entrance(COLOSSUS_MEGALITH, { [] { return IsAdult && CanPlantBean(DESERT_COLOSSUS); },
                                          /*Glitched*/
                                          [] {
                                              return HoverBoots && CanDoGlitch(GlitchType::HookshotJump_Boots,
                                                                               GlitchDifficulty::ADVANCED);
                                          } }),
            Entrance(COLOSSUS_GREAT_FAIRY_FOUNTAIN, { [] { return HasExplosives; } }),
            Entrance(SPIRIT_TEMPLE_ENTRYWAY, { [] { return true; } }),
            Entrance(WASTELAND_NEAR_COLOSSUS, { [] { return true; } }),
            Entrance(COLOSSUS_GROTTO, { [] { return CanUse(SILVER_GAUNTLETS); } }),
        });

    areaTable[COLOSSUS_MEGALITH] = Area("Colossus Megalith", "Desert Colossus", DESERT_COLOSSUS, DAY_NIGHT_CYCLE, {},
                                        {
                                            // Locations
                                            LocationAccess(COLOSSUS_FREESTANDING_POH, { [] { return true; } }),
                                        },
                                        {
                                            // Exits
                                            Entrance(DESERT_COLOSSUS, { [] { return true; } }),
                                        });

    areaTable[DESERT_COLOSSUS_FROM_SPIRIT_ENTRYWAY] =
        Area("Desert Colossus From Spirit Entryway", "Desert Colossus", DESERT_COLOSSUS, NO_DAY_NIGHT_CYCLE, {},
             {
                 // Locations
                 LocationAccess(SHEIK_AT_COLOSSUS, { [] { return true; } }),
             },
             {
                 // Exits
                 Entrance(DESERT_COLOSSUS, { [] { return true; } }),
             });

    areaTable[COLOSSUS_GREAT_FAIRY_FOUNTAIN] =
        Area("Colossus Great Fairy Fountain", "Colossus Great Fairy Fountain", NONE, NO_DAY_NIGHT_CYCLE, {},
             {
                 // Locations
                 LocationAccess(COLOSSUS_GREAT_FAIRY_REWARD,
                                { [] { return CanPlay(ZeldasLullaby); },
                                  /*Glitched*/
                                  [] {
                                      return (CanDoGlitch(GlitchType::OutdoorBombOI, GlitchDifficulty::INTERMEDIATE) ||
                                              ((Bugs || Fish) && CanShield && Bombs && CanTakeDamage &&
                                               CanDoGlitch(GlitchType::QPA, GlitchDifficulty::ADVANCED)) ||
                                              ((Bugs || Fish) && HasBombchus && CanShield &&
                                               CanDoGlitch(GlitchType::ActionSwap, GlitchDifficulty::ADVANCED))) &&
                                             ZeldasLullaby;
                                  } }),
             },
             {
                 // Exits
                 Entrance(DESERT_COLOSSUS, { [] { return true; } }),
             });

    areaTable[COLOSSUS_GROTTO] =
        Area("Colossus Grotto", "Colossus Grotto", NONE, NO_DAY_NIGHT_CYCLE, {},
             {
                 // Locations
                 LocationAccess(COLOSSUS_DEKU_SCRUB_GROTTO_REAR, { [] { return CanStunDeku; } }),
                 LocationAccess(COLOSSUS_DEKU_SCRUB_GROTTO_FRONT, { [] { return CanStunDeku; } }),
             },
             {
                 // Exits
                 Entrance(DESERT_COLOSSUS, { [] { return true; } }),
             });
}
