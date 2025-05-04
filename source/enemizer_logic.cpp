#include "enemizer.hpp"
#include "logic.hpp"
#include "location_access.hpp"
#include "settings.hpp"
#include "enemizer_logic.hpp"

using namespace Enemizer;
using namespace Settings;

using EnemyConditionFn = std::function<bool(Enemizer::EnemyLocation&)>;

namespace Logic {

static bool AllEnemiesSatisfy(EnemyConditionFn conditionFn, u8 scene, u8 layer, u8 room,
                              std::vector<u8> actorEntries /*= {}*/) {
    auto& roomMap = enemyLocations[scene][layer][room];
    if (actorEntries.empty()) {
        for (auto& entry : roomMap) {
            if (!conditionFn(entry.second)) {
                return false;
            }
        }
    } else {
        for (auto& entry : actorEntries) {
            if (!conditionFn(roomMap[entry])) {
                return false;
            }
        }
    }
    return true;
}

static bool AnyEnemySatisfies(EnemyConditionFn conditionFn, u8 scene, u8 layer, u8 room,
                              std::vector<u8> actorEntries /*= {}*/) {
    auto flippedConditionFn = [&conditionFn](EnemyLocation& loc) { return !conditionFn(loc); };
    return !AllEnemiesSatisfy(flippedConditionFn, scene, layer, room, actorEntries);
}

bool IsWallmaster(u8 scene, u8 layer, u8 room, u8 actorEntry) {
    return enemyLocations[scene][layer][room][actorEntry].GetEnemyId() == ENEMY_WALLMASTER;
}

bool CanDefeatEnemy(u16 enemyId) {
    if (!enemyTypes[enemyId].HasSoul()) {
        return false;
    }

    switch (enemyId) {
        case ENEMY_POE:
            return CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(STICKS) ||
                   CanUse(MEGATON_HAMMER) || CanUse(BOW) || CanUse(HOOKSHOT) || CanUse(SLINGSHOT) ||
                   CanUse(BOOMERANG) || CanUse(DINS_FIRE) || HasExplosives;
        case ENEMY_STALFOS:
            return CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(MEGATON_HAMMER);
        case ENEMY_OCTOROK:
            return CanUseProjectile;
        case ENEMY_WALLMASTER:
        case ENEMY_FLOORMASTER:
            return CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(STICKS) ||
                   CanUse(MEGATON_HAMMER) || CanUse(BOW) || CanUse(SLINGSHOT) || CanUse(DINS_FIRE) || HasExplosives;
        case ENEMY_DODONGO:
            return CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(STICKS) ||
                   CanUse(MEGATON_HAMMER) || CanUse(BOW) || CanUse(SLINGSHOT) || HasExplosives;
        case ENEMY_KEESE_NORMAL:
        case ENEMY_KEESE_FIRE:
            return CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(STICKS) ||
                   CanUse(MEGATON_HAMMER) || CanUse(BOW) || CanUse(HOOKSHOT) || CanUse(SLINGSHOT) ||
                   CanUse(BOOMERANG) || HasExplosives;
        case ENEMY_KEESE_ICE:
            return CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(STICKS) ||
                   CanUse(MEGATON_HAMMER) || CanUse(BOW) || CanUse(HOOKSHOT) || CanUse(SLINGSHOT) ||
                   CanUse(BOOMERANG) || CanUse(DINS_FIRE) || HasExplosives;
        case ENEMY_TEKTITE_RED:
        case ENEMY_TEKTITE_BLUE:
            return CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(STICKS) ||
                   CanUse(MEGATON_HAMMER) || CanUse(BOW) || CanUse(HOOKSHOT) || CanUse(SLINGSHOT) || HasExplosives;
        case ENEMY_LEEVER:
            return CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(STICKS) ||
                   CanUse(MEGATON_HAMMER) || CanUse(BOW) || CanUse(HOOKSHOT) || CanUse(SLINGSHOT) || HasExplosives;
        case ENEMY_PEAHAT:
            return AtDay && (CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(STICKS) ||
                             CanUse(MEGATON_HAMMER) || CanUse(BOW) || CanUse(HOOKSHOT) || CanUse(SLINGSHOT) ||
                             CanUse(DINS_FIRE) || HasExplosives);
        case ENEMY_PEAHAT_LARVA:
            return true;
        case ENEMY_LIZALFOS:
        case ENEMY_DINOLFOS:
            return CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(STICKS) ||
                   CanUse(MEGATON_HAMMER) || CanUse(BOW) || CanUse(SLINGSHOT) || HasExplosives;
        case ENEMY_GOHMA_LARVA:
            return CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(STICKS) ||
                   CanUse(MEGATON_HAMMER) || CanUse(BOW) || CanUse(HOOKSHOT) || CanUse(SLINGSHOT) ||
                   CanUse(BOOMERANG) || CanUse(DINS_FIRE) || HasExplosives;
        case ENEMY_SHABOM:
            return true;
        case ENEMY_DODONGO_BABY:
            return true;
        case ENEMY_DARK_LINK:
            return Hearts > 0 && (CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD));
        case ENEMY_BIRI:
        case ENEMY_BARI:
            return CanUse(STICKS) || CanUse(MEGATON_HAMMER) || CanUse(BOW) || CanUse(HOOKSHOT) || CanUse(BOOMERANG) ||
                   CanUse(DINS_FIRE) || HasExplosives ||
                   ((Nuts || MagicMeter) && (CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD)));
        case ENEMY_TAILPASARAN:
            return CanUse(STICKS) || CanUse(MEGATON_HAMMER) || CanUse(BOOMERANG) ||
                   (MagicMeter && (CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD)));
        case ENEMY_SKULLTULA:
            return CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(STICKS) ||
                   CanUse(MEGATON_HAMMER) || CanUse(BOW) || CanUse(HOOKSHOT) || CanUse(SLINGSHOT) ||
                   CanUse(DINS_FIRE) || HasExplosives;
        case ENEMY_TORCH_SLUG:
            return CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(MEGATON_HAMMER) ||
                   CanUse(BOW) || HasExplosives;
        case ENEMY_STINGER_FLOOR:
        case ENEMY_STINGER_WATER:
            return CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(STICKS) ||
                   CanUse(MEGATON_HAMMER) || CanUse(BOW) || CanUse(HOOKSHOT) || CanUse(SLINGSHOT) || HasExplosives;
        case ENEMY_MOBLIN_CLUB:
            return CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(STICKS) ||
                   CanUse(MEGATON_HAMMER) || CanUse(BOW) || HasExplosives;
        case ENEMY_MOBLIN_SPEAR:
            return CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(STICKS) ||
                   CanUse(MEGATON_HAMMER) || CanUse(BOW) || CanUse(HOOKSHOT) || CanUse(SLINGSHOT) || HasExplosives;
        case ENEMY_ARMOS:
            return CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(MEGATON_HAMMER) ||
                   CanUse(BOW) || HasExplosives ||
                   ((Nuts || CanUse(HOOKSHOT) || CanUse(BOOMERANG)) && (CanUse(STICKS) || CanUse(SLINGSHOT)));
        case ENEMY_DEKU_BABA_SMALL:
            return CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(STICKS) ||
                   CanUse(MEGATON_HAMMER) || CanUse(BOW) || CanUse(HOOKSHOT) || CanUse(SLINGSHOT) ||
                   CanUse(BOOMERANG) || CanUse(DINS_FIRE) || HasExplosives;
        case ENEMY_DEKU_BABA_BIG:
            return CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(STICKS) ||
                   CanUse(MEGATON_HAMMER) || CanUse(BOW) || CanUse(SLINGSHOT) || CanUse(BOOMERANG) ||
                   CanUse(DINS_FIRE) || HasExplosives;
        case ENEMY_MAD_SCRUB:
            return CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(STICKS) ||
                   CanUse(MEGATON_HAMMER) || CanUse(BOW) || CanUse(HOOKSHOT) || CanUse(SLINGSHOT) ||
                   CanUse(BOOMERANG) || CanUse(DINS_FIRE) || HasExplosives;
        case ENEMY_BUBBLE_BLUE:
            return CanUse(MEGATON_HAMMER) || CanUse(BOW) || HasExplosives ||
                   ((CanShield || Nuts || CanUse(HOOKSHOT) || CanUse(BOOMERANG)) &&
                    ((CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(STICKS) ||
                      CanUse(SLINGSHOT))));
        case ENEMY_BUBBLE_FIRE:
            return CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(BOW);
        // case ENEMY_BUBBLE_WHITE: // Unimplemented
        //     return false;
        case ENEMY_BUBBLE_GREEN:
            return CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(STICKS) ||
                   CanUse(MEGATON_HAMMER) || CanUse(BOW) || CanUse(SLINGSHOT) || HasExplosives;
        case ENEMY_FLYING_FLOOR_TILE:
            return true;
        case ENEMY_BEAMOS:
            return HasExplosives;
        case ENEMY_REDEAD:
        case ENEMY_GIBDO:
            return CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(STICKS) ||
                   CanUse(MEGATON_HAMMER) || CanUse(DINS_FIRE);
        // case ENEMY_POE_SISTER: // Unimplemented
        //     return false;
        case ENEMY_DEAD_HAND_HAND:
            return CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(STICKS) ||
                   CanUse(MEGATON_HAMMER);
        case ENEMY_SKULLWALLTULA:
            return CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(STICKS) ||
                   CanUse(MEGATON_HAMMER) || CanUse(BOW) || CanUse(HOOKSHOT) || CanUse(SLINGSHOT) ||
                   CanUse(BOOMERANG) || CanUse(DINS_FIRE) || HasExplosives;
        case ENEMY_FLARE_DANCER:
            return (CanUse(MEGATON_HAMMER) || CanUse(HOOKSHOT) || HasExplosives) &&
                   (CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(SLINGSHOT) ||
                    CanUse(BOOMERANG));
        // case ENEMY_DEAD_HAND: // Unimplemented
        //     return false;
        case ENEMY_SHELL_BLADE:
            return CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(MEGATON_HAMMER) ||
                   CanUse(BOW) || CanUse(HOOKSHOT) || CanUse(DINS_FIRE);
        // case ENEMY_BIG_OCTO: // Unimplemented
        //     return false;
        case ENEMY_DEKU_BABA_WITHERED:
            return CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(BOOMERANG);
        case ENEMY_LIKE_LIKE:
            return CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(STICKS) ||
                   CanUse(MEGATON_HAMMER) || CanUse(BOW) || CanUse(SLINGSHOT) || CanUse(DINS_FIRE) || HasExplosives;
        // case ENEMY_PARASITIC_TENTACLE: // Unimplemented
        //     return false;
        case ENEMY_SPIKE:
            return CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(MEGATON_HAMMER) || CanUse(BOW) ||
                   CanUse(HOOKSHOT) || CanUse(DINS_FIRE) || HasExplosives;
        case ENEMY_ANUBIS:
            return CanUse(DINS_FIRE) || CanUse(FIRE_ARROWS);
        case ENEMY_IRON_KNUCKLE:
            return CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(STICKS) ||
                   CanUse(MEGATON_HAMMER) || HasExplosives;
        case ENEMY_SKULL_KID:
            return CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(STICKS) ||
                   CanUse(MEGATON_HAMMER) || CanUse(BOW) || CanUse(HOOKSHOT) || CanUse(SLINGSHOT) ||
                   CanUse(BOOMERANG) || CanUse(DINS_FIRE) || HasExplosives || Nuts;
        case ENEMY_FLYING_POT:
            return true;
        case ENEMY_FREEZARD:
            return CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(MEGATON_HAMMER) || CanUse(FIRE_ARROWS) ||
                   CanUse(HOOKSHOT) || CanUse(DINS_FIRE) || HasExplosives;
        // case ENEMY_GERUDO_FIGHTER: // Unimplemented
        //     return false;
        case ENEMY_WOLFOS:
            return CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(STICKS) ||
                   CanUse(MEGATON_HAMMER) || CanUse(BOW) || CanUse(SLINGSHOT) || CanUse(DINS_FIRE) || HasExplosives;
        case ENEMY_STALCHILD:
            return CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(STICKS) ||
                   CanUse(MEGATON_HAMMER) || CanUse(BOW) || CanUse(SLINGSHOT) || CanUse(DINS_FIRE) || HasExplosives;
        case ENEMY_GUAY:
            return CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(STICKS) ||
                   CanUse(MEGATON_HAMMER) || CanUse(BOW) || CanUse(HOOKSHOT) || CanUse(SLINGSHOT) ||
                   CanUse(BOOMERANG) || CanUse(DINS_FIRE) || HasExplosives;
        default:
            return false;
    }
}

static EnemyConditionFn _CanDefeatEnemy([](EnemyLocation& loc) {
    u16 enemyId       = loc.GetEnemyId();
    bool isUnderwater = loc.IsUnderwater();

    if (isUnderwater) {
        return enemyTypes[enemyId].HasSoul() && CanUse(IRON_BOOTS) && CanUse(HOOKSHOT);
    }

    return CanDefeatEnemy(enemyId);
});

bool CanDefeatEnemy(u8 scene, u8 layer, u8 room, u8 actorEntry) {
    return _CanDefeatEnemy(enemyLocations[scene][layer][room][actorEntry]);
}

bool CanDefeatEnemies(u8 scene, u8 layer, u8 room, std::vector<u8> actorEntries /*= {}*/) {
    return AllEnemiesSatisfy(_CanDefeatEnemy, scene, layer, room, actorEntries);
}

static bool _CanPassEnemy(EnemyLocation& loc, SpaceAroundEnemy space = SpaceAroundEnemy::WIDE) {
    u16 enemyId       = loc.GetEnemyId();
    bool isUnderwater = loc.IsUnderwater();

    switch (space) {
        case SpaceAroundEnemy::NONE:
            switch (enemyId) {
                case ENEMY_DEKU_BABA_SMALL:
                case ENEMY_DEKU_BABA_BIG:
                case ENEMY_BARI:
                case ENEMY_BEAMOS:
                case ENEMY_DEAD_HAND_HAND:
                case ENEMY_DEKU_BABA_WITHERED:
                case ENEMY_LIKE_LIKE:
                    return _CanDefeatEnemy(loc);
                case ENEMY_FREEZARD:
                    return loc.randomizedParams != 0 // mobile
                           || _CanDefeatEnemy(loc);
            }
            // fallthrough
        case SpaceAroundEnemy::NARROW:
            switch (enemyId) {
                case ENEMY_PEAHAT:
                case ENEMY_MOBLIN_CLUB:
                case ENEMY_SKULLTULA:
                    return _CanDefeatEnemy(loc);
            }
            // fallthrough
        case SpaceAroundEnemy::WIDE:
            switch (enemyId) {
                case ENEMY_SKULLTULA:
                    return isUnderwater ? CanTakeDamage : ((SoulSkulltula && Nuts) || _CanDefeatEnemy(loc));
            }
    }

    return true;
}

bool CanPassEnemy(u8 scene, u8 layer, u8 room, u8 actorEntry, SpaceAroundEnemy space /*= SpaceAroundEnemy::WIDE*/) {
    return _CanPassEnemy(enemyLocations[scene][layer][room][actorEntry], space);
}

bool CanPassEnemies(u8 scene, u8 layer, u8 room, std::vector<u8> actorEntries /*= {}*/,
                    SpaceAroundEnemy space /*= SpaceAroundEnemy::WIDE*/) {
    return AllEnemiesSatisfy([space](EnemyLocation& loc) { return _CanPassEnemy(loc, space); }, scene, layer, room,
                             actorEntries);
}

bool CanPassAnyEnemy(u8 scene, u8 layer, u8 room, std::vector<u8> actorEntries /*= {}*/,
                     SpaceAroundEnemy space /*= SpaceAroundEnemy::WIDE*/) {
    return AnyEnemySatisfies([space](EnemyLocation& loc) { return _CanPassEnemy(loc, space); }, scene, layer, room,
                             actorEntries);
}

bool CanCrawlNearEnemies(u8 scene, u8 layer, u8 room, std::vector<u8> actorEntries /*= {}*/) {
    return AllEnemiesSatisfy(
        [](EnemyLocation& loc) {
            return loc.GetEnemyId() != ENEMY_DEAD_HAND_HAND || CanDefeatEnemy(ENEMY_DEAD_HAND_HAND);
        },
        scene, layer, room, actorEntries);
}

bool CanHookEnemy(u8 scene, u8 layer, u8 room, u8 actorEntry, bool onLedge /*= false*/) {
    EnemyLocation& loc = enemyLocations[scene][layer][room][actorEntry];
    u16 enemyId        = loc.GetEnemyId();

    if (!enemyTypes[enemyId].HasSoul()) {
        return false;
    }

    switch (enemyId) {
        case ENEMY_LIKE_LIKE:
        case ENEMY_REDEAD:
        case ENEMY_GIBDO:
            return true;
        case ENEMY_FREEZARD:
            return loc.randomizedParams == 0; // immobile, always spawned
        case ENEMY_IRON_KNUCKLE:
        case ENEMY_FLOORMASTER:
            return !onLedge; // these can walk off ledges
    }

    return false;
}

static bool _CanDetonateEnemy(EnemyLocation& loc, bool needLowHeight = false) {
    u16 enemyId = loc.GetEnemyId();

    switch (enemyId) {
        // case ENEMY_BEAMOS: useless to include as it requires an explosion to explode
        case ENEMY_DODONGO:
        case ENEMY_DODONGO_BABY:
        case ENEMY_ARMOS:
        case ENEMY_FLARE_DANCER:
            return CanDefeatEnemy(enemyId);
        case ENEMY_PEAHAT: // explodes up in the air, e.g. it wouldn't open a grotto
            return !needLowHeight && CanDefeatEnemy(enemyId);
    }

    return false;
}

bool CanDetonateEnemy(u8 scene, u8 layer, u8 room, u8 actorEntry, bool needLowHeight /*= false*/) {
    return _CanDetonateEnemy(enemyLocations[scene][layer][room][actorEntry], needLowHeight);
}

bool CanDetonateAnyEnemy(u8 scene, u8 layer, u8 room, std::vector<u8> actorEntries /*= {}*/,
                         bool needLowHeight /*= false*/) {
    return AnyEnemySatisfies([needLowHeight](EnemyLocation& loc) { return _CanDetonateEnemy(loc, needLowHeight); },
                             scene, layer, room, actorEntries);
}

static EnemyConditionFn _CanGetDekuBabaSticks([](EnemyLocation& loc) {
    u16 enemyId = loc.GetEnemyId();
    if (loc.IsUnderwater()) {
        return false;
    }

    switch (enemyId) {
        case ENEMY_DEKU_BABA_BIG:
        case ENEMY_DEKU_BABA_SMALL:
            return SoulDekuBaba &&
                   (CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(BOOMERANG));
        case ENEMY_DEKU_BABA_WITHERED:
            return CanDefeatEnemy(enemyId);
    }

    return false;
});

bool CanGetDekuBabaSticks(u8 scene, u8 layer, u8 room, std::vector<u8> actorEntries /*= {}*/) {
    return AnyEnemySatisfies(_CanGetDekuBabaSticks, scene, layer, room, actorEntries);
}

static EnemyConditionFn _CanGetDekuBabaNuts([](EnemyLocation& loc) {
    u16 enemyId       = loc.GetEnemyId();
    bool isUnderwater = loc.IsUnderwater();

    switch (enemyId) { // same as defeat condition but exclude boomerang
        case ENEMY_DEKU_BABA_BIG:
            return !isUnderwater && SoulDekuBaba &&
                   (CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) || CanUse(STICKS) ||
                    CanUse(MEGATON_HAMMER) || CanUse(BOW) || CanUse(SLINGSHOT) || CanUse(DINS_FIRE) || HasExplosives);
        case ENEMY_DEKU_BABA_SMALL:
            return SoulDekuBaba &&
                   (isUnderwater ? (CanUse(IRON_BOOTS) && CanUse(HOOKSHOT))
                                 : (CanUse(KOKIRI_SWORD) || CanUse(MASTER_SWORD) || CanUse(BIGGORON_SWORD) ||
                                    CanUse(STICKS) || CanUse(MEGATON_HAMMER) || CanUse(BOW) || CanUse(HOOKSHOT) ||
                                    CanUse(SLINGSHOT) || CanUse(DINS_FIRE) || HasExplosives));
    }

    return false;
});

bool CanGetDekuBabaNuts(u8 scene, u8 layer, u8 room, std::vector<u8> actorEntries /*= {}*/) {
    return AnyEnemySatisfies(_CanGetDekuBabaNuts, scene, layer, room, actorEntries);
}
} // namespace Logic
