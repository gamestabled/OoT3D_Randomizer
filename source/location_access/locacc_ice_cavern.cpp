#include "location_access.hpp"
#include "logic.hpp"
#include "entrance.hpp"
#include "dungeon.hpp"
#include "enemizer_logic.hpp"

using namespace Logic;
using namespace Settings;

void AreaTable_Init_IceCavern() {
    /*--------------------------
    |    VANILLA/MQ DECIDER    |
    ---------------------------*/
    areaTable[ICE_CAVERN_ENTRYWAY] =
        Area("Ice Cavern Entryway", "Ice Cavern", ICE_CAVERN, NO_DAY_NIGHT_CYCLE, {}, {},
             {
                 // Exits
                 Entrance(ICE_CAVERN_BEGINNING, { [] { return Dungeon::IceCavern.IsVanilla(); } }),
                 Entrance(ICE_CAVERN_MQ_BEGINNING, { [] { return Dungeon::IceCavern.IsMQ() && CanUseProjectile; } }),
                 Entrance(ZORAS_FOUNTAIN, { [] { return true; } }),
             });

    /*--------------------------
    |     VANILLA DUNGEON      |
    ---------------------------*/
    if (Dungeon::IceCavern.IsVanilla()) {
        areaTable[ICE_CAVERN_BEGINNING] =
            Area("Ice Cavern Beginning", "Ice Cavern", ICE_CAVERN, NO_DAY_NIGHT_CYCLE, {},
                 {
                     LocationAccess(ICE_CAVERN_RED_ICE_BLUE_RUPEE, { [] { return BlueFire; } }),
                 },
                 {
                     // Exits
                     Entrance(ICE_CAVERN_ENTRYWAY, { [] { return true; } }),
                     Entrance(ICE_CAVERN_MAIN,
                              { [] { return Here(ICE_CAVERN_BEGINNING, [] { return CanDefeatEnemies(9, 0, 1); }); } }),
                 });

        static constexpr auto ForEachEnemy_Main = [](auto& enemyCheckFn) {
            return enemyCheckFn(9, 0, 3, {}) || enemyCheckFn(9, 0, 5, {}) || enemyCheckFn(9, 0, 8, {}) ||
                   enemyCheckFn(9, 0, 9, {}) || enemyCheckFn(9, 0, 11, {}) || enemyCheckFn(9, 0, 6, { 18 }) ||
                   (CanPassEnemy(9, 0, 6, 18) && enemyCheckFn(9, 0, 6, { 17 }));
        };
        areaTable[ICE_CAVERN_MAIN] = Area(
            "Ice Cavern", "Ice Cavern", ICE_CAVERN, NO_DAY_NIGHT_CYCLE,
            {
                // Events
                EventAccess(&BlueFireAccess, { [] { return BlueFireAccess || (IsAdult && HasBottle); } }),
                // Events
                EventAccess(&DekuBabaSticks,
                            { [] { return DekuBabaSticks || ForEachEnemy_Main(CanGetDekuBabaSticks); } }),
                EventAccess(&DekuBabaNuts, { [] { return DekuBabaNuts || ForEachEnemy_Main(CanGetDekuBabaNuts); } }),

            },
            {
                // Locations
                LocationAccess(ICE_CAVERN_MAP_CHEST, { [] { return BlueFire && IsAdult; } }),
                LocationAccess(ICE_CAVERN_COMPASS_CHEST, { [] { return BlueFire; } }),
                LocationAccess(ICE_CAVERN_IRON_BOOTS_CHEST,
                               { [] { return BlueFire && CanPassEnemy(9, 0, 6, 18) && CanDefeatEnemy(9, 0, 7, 0); } }),
                LocationAccess(SHEIK_IN_ICE_CAVERN, { [] {
                                   return BlueFire && CanPassEnemy(9, 0, 6, 18) && CanDefeatEnemy(9, 0, 7, 0) &&
                                          IsAdult;
                               } }),
                LocationAccess(ICE_CAVERN_FREESTANDING_POH, { [] { return BlueFire; } }),
                LocationAccess(ICE_CAVERN_GS_SPINNING_SCYTHE_ROOM, { [] { return HookshotOrBoomerang; } }),
                LocationAccess(ICE_CAVERN_GS_HEART_PIECE_ROOM, { [] { return BlueFire && HookshotOrBoomerang; } }),
                LocationAccess(ICE_CAVERN_GS_PUSH_BLOCK_ROOM, { [] { return BlueFire && HookshotOrBoomerang; } }),
                LocationAccess(ICE_CAVERN_PUSH_BLOCK_ROOM_RED_RUPEE_1,
                               { [] { return SongOfTime || CanUse(BOOMERANG); } }),
                LocationAccess(ICE_CAVERN_PUSH_BLOCK_ROOM_RED_RUPEE_2,
                               { [] { return SongOfTime || CanUse(BOOMERANG); } }),
                LocationAccess(ICE_CAVERN_PUSH_BLOCK_ROOM_RED_RUPEE_3,
                               { [] { return SongOfTime || CanUse(BOOMERANG); } }),
            },
            {});
    }

    /*---------------------------
    |   MASTER QUEST DUNGEON    |
    ---------------------------*/
    if (Dungeon::IceCavern.IsMQ()) {
        areaTable[ICE_CAVERN_MQ_BEGINNING] =
            Area("Ice Cavern MQ Beginning", "Ice Cavern", ICE_CAVERN, NO_DAY_NIGHT_CYCLE,
                 {
                     // Events
                     EventAccess(&FairyPot, { [] { return true; } }),
                 },
                 {},
                 {
                     // Exits
                     Entrance(ICE_CAVERN_ENTRYWAY, { [] { return true; } }),
                     Entrance(ICE_CAVERN_MQ_MAP_ROOM, { [] {
                                  return CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(DINS_FIRE) ||
                                         (HasExplosives && (CanUse(SLINGSHOT) || CanJumpslash));
                              } }),
                     Entrance(ICE_CAVERN_MQ_COMPASS_ROOM, { [] { return IsAdult && BlueFire; } }),
                     Entrance(ICE_CAVERN_MQ_IRON_BOOTS_REGION, { [] { return BlueFire; } }),
                 });

        areaTable[ICE_CAVERN_MQ_MAP_ROOM] =
            Area("Ice Cavern MQ Map Room", "Ice Cavern", ICE_CAVERN, NO_DAY_NIGHT_CYCLE,
                 {
                     // Events
                     EventAccess(&BlueFireAccess, { [] { return BlueFireAccess || (HasBottle && CanJumpslash); } }),
                 },
                 {
                     // Locations
                     LocationAccess(ICE_CAVERN_MQ_MAP_CHEST,
                                    { [] { return BlueFire && (CanJumpslash || CanUseProjectile); } }),
                 },
                 {});

        areaTable[ICE_CAVERN_MQ_IRON_BOOTS_REGION] = Area(
            "Ice Cavern MQ Iron Boots Region", "Ice Cavern", ICE_CAVERN, NO_DAY_NIGHT_CYCLE, {},
            {
                // Locations
                LocationAccess(ICE_CAVERN_MQ_IRON_BOOTS_CHEST, { [] {
                                   return IsAdult &&
                                          (CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD));
                               } }),
                LocationAccess(SHEIK_IN_ICE_CAVERN, { [] { return IsAdult; } }),
                LocationAccess(ICE_CAVERN_MQ_GS_ICE_BLOCK,
                               { [] { return (IsAdult && CanJumpslash) || CanUseProjectile; } }),
                LocationAccess(ICE_CAVERN_MQ_GS_SCARECROW, { [] {
                                   return IsAdult && (CanUse(SCARECROW) || (CanUse(HOVER_BOOTS) && CanUse(LONGSHOT)));
                               } }),
                // Tricks: (CanUse(SCARECROW) || (HoverBoots && CanUse(LONGSHOT)) || LogicIceMQScarecrow) && IsAdult
            },
            {});

        areaTable[ICE_CAVERN_MQ_COMPASS_ROOM] =
            Area("Ice Cavern MQ Compass Room", "Ice Cavern", ICE_CAVERN, NO_DAY_NIGHT_CYCLE, {},
                 {
                     // Locations
                     LocationAccess(ICE_CAVERN_MQ_COMPASS_CHEST, { [] { return true; } }),
                     LocationAccess(ICE_CAVERN_MQ_FREESTANDING_POH, { [] { return HasExplosives; } }),
                     LocationAccess(ICE_CAVERN_MQ_GS_RED_ICE, { [] { return CanPlay(SongOfTime); } }),
                     // Trick: CanPlay(SongOfTime) || LogicIceMQRedIceGS
                 },
                 {});
    }
}
