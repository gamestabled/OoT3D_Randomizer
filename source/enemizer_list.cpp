#include "enemizer.hpp"
#include "dungeon.hpp"
#include "logic.hpp"

using namespace Logic;

namespace Enemizer {

EnemyType enemyTypes[ENEMY_MAX]  = {};
EnemyLocationsMap enemyLocations = {};

// clang-format off
void InitEnemyTypes(void) {
    enemyTypes[ENEMY_INVALID] = EnemyType("Invalid Enemy", &noVariable, 0, { 0 }, {});
    enemyTypes[ENEMY_POE] = EnemyType("Poe", &SoulPoe, ACTOR_POE, { 0x0000, 0x0002, 0x0003 }, // normal, Sharp, Flat
        { LocType::ABOVE_GROUND, LocType::ABOVE_VOID, LocType::UNDERWATER, LocType::ABOVE_WATER, LocType::SHALLOW_WATER, LocType::SPAWNER });
    enemyTypes[ENEMY_STALFOS] = EnemyType("Stalfos", &SoulStalfos, ACTOR_STALFOS, { 0x0002, 0x0003 }, // rises from ground / drops from above when approached
        { LocType::ABOVE_GROUND, LocType::SHALLOW_WATER, LocType::SPAWNER });
    enemyTypes[ENEMY_OCTOROK] = EnemyType("Octorok", &SoulOctorok, ACTOR_OCTOROK, { 0x0000 },
        { LocType::ABOVE_WATER, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_WALLMASTER] = EnemyType("Wallmaster", &SoulWallmaster, ACTOR_WALLMASTER, { 0x0000 },
        { LocType::ABOVE_GROUND, LocType::ABOVE_VOID, LocType::ABOVE_WATER, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_DODONGO] = EnemyType("Dodongo (Normal)", &SoulDodongo, ACTOR_DODONGO, { 0x0000 },
        { LocType::ABOVE_GROUND, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_KEESE_NORMAL] = EnemyType("Keese (Normal)", &SoulKeese, ACTOR_KEESE, { 0x0002 },
        { LocType::ABOVE_GROUND, LocType::ABOVE_VOID, LocType::UNDERWATER, LocType::ABOVE_WATER, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_KEESE_FIRE] = EnemyType("Keese (Fire)", &SoulKeese, ACTOR_KEESE, { 0x0001 },
        { LocType::ABOVE_GROUND, LocType::ABOVE_VOID, LocType::ABOVE_WATER, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_KEESE_ICE] = EnemyType("Keese (Ice)", &SoulKeese, ACTOR_KEESE, { 0x0004 },
        { LocType::ABOVE_GROUND, LocType::ABOVE_VOID, LocType::UNDERWATER, LocType::ABOVE_WATER, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_TEKTITE_RED] = EnemyType("Tektite (Red)", &SoulTektite, ACTOR_TEKTITE, { 0xFFFF },
        { LocType::ABOVE_GROUND, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_TEKTITE_BLUE] = EnemyType("Tektite (Blue)", &SoulTektite, ACTOR_TEKTITE, { 0xFFFE },
        { LocType::ABOVE_GROUND, LocType::ABOVE_WATER, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_LEEVER] = EnemyType("Leever", &SoulLeever, ACTOR_LEEVER, { 0x0000, 0x0001 }, // normal / big
        { LocType::ABOVE_GROUND, LocType::SHALLOW_WATER, LocType::SPAWNER });
    enemyTypes[ENEMY_PEAHAT] = EnemyType("Peahat", &SoulPeahat, ACTOR_PEAHAT, { 0xFFFF },
        { LocType::ABOVE_GROUND, LocType::ABOVE_WATER, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_PEAHAT_LARVA] = EnemyType("Peahat Larva", &SoulPeahat, ACTOR_PEAHAT, { 0x0001 },
        { LocType::ABOVE_GROUND, LocType::ABOVE_VOID, LocType::UNDERWATER, LocType::ABOVE_WATER, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_LIZALFOS] = EnemyType("Lizalfos", &SoulLizalfosDinolfos, ACTOR_LIZALFOS, { 0xFF80, 0xFFFF }, // normal / drops from above when approached
        { LocType::ABOVE_GROUND, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_DINOLFOS] = EnemyType("Dinolfos", &SoulLizalfosDinolfos, ACTOR_LIZALFOS, { 0xFFFE },
        { LocType::ABOVE_GROUND, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_GOHMA_LARVA] = EnemyType("Gohma Larva", &SoulGohma, ACTOR_GOHMA_LARVA, { 0x0000, 0x0007 }, // egg that drops and hatches / stationary egg
        { LocType::ABOVE_GROUND, LocType::UNDERWATER, LocType::SHALLOW_WATER, LocType::SPAWNER });
    enemyTypes[ENEMY_SHABOM] = EnemyType("Shabom", &SoulShabom, ACTOR_SHABOM, { 0x0000 },
        { LocType::ABOVE_GROUND, LocType::ABOVE_WATER, LocType::SHALLOW_WATER, LocType::SPAWNER });
    enemyTypes[ENEMY_DODONGO_BABY] = EnemyType("Dodongo (Baby)", &SoulDodongo, ACTOR_BABY_DODONGO, { 0x0000 },
        { LocType::ABOVE_GROUND, LocType::SHALLOW_WATER, LocType::SPAWNER });
    enemyTypes[ENEMY_DARK_LINK] = EnemyType("Dark Link", &SoulDarkLink, ACTOR_DARK_LINK, { 0x0000 },
        { LocType::ABOVE_GROUND, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_BIRI] = EnemyType("Biri", &SoulBiriBari, ACTOR_BIRI, { 0xFFFF },
        { LocType::ABOVE_GROUND, LocType::ABOVE_VOID, LocType::UNDERWATER, LocType::ABOVE_WATER, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_TAILPASARAN] = EnemyType("Tailpasaran", &SoulTailpasaran, ACTOR_TAILPASARAN, { 0xFFFF },
        { LocType::ABOVE_GROUND, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_SKULLTULA] = EnemyType("Skulltula", &SoulSkulltula, ACTOR_SKULLTULA, { 0x0000, 0x0001 },
        { LocType::ABOVE_GROUND, LocType::ABOVE_VOID, LocType::UNDERWATER, LocType::ABOVE_WATER, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_TORCH_SLUG] = EnemyType("Torch Slug", &SoulTorchSlug, ACTOR_TORCH_SLUG, { 0xFFFF },
        { LocType::ABOVE_GROUND });
    enemyTypes[ENEMY_STINGER_FLOOR] = EnemyType("Stinger (Floor)", &SoulStinger, ACTOR_STINGER_FLOOR, { 0x000A },
        { LocType::ABOVE_GROUND, LocType::UNDERWATER, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_MOBLIN_CLUB] = EnemyType("Moblin (Club)", &SoulMoblin, ACTOR_MOBLIN, { 0x0000 },
        { LocType::ABOVE_GROUND, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_MOBLIN_SPEAR] = EnemyType("Moblin (Spear)", &SoulMoblin, ACTOR_MOBLIN, { 0xFFFF },
        { LocType::ABOVE_GROUND, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_ARMOS] = EnemyType("Armos", &SoulArmos, ACTOR_ARMOS, { 0xFFFF },
        { LocType::ABOVE_GROUND, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_DEKU_BABA_SMALL] = EnemyType("Deku Baba (Small)", &SoulDekuBaba, ACTOR_DEKU_BABA, { 0x0000 },
        { LocType::ABOVE_GROUND, LocType::UNDERWATER, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_DEKU_BABA_BIG] = EnemyType("Deku Baba (Big)", &SoulDekuBaba, ACTOR_DEKU_BABA, { 0x0001 },
        { LocType::ABOVE_GROUND, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_MAD_SCRUB] = EnemyType("Mad Scrub", &SoulDekuScrub, ACTOR_MAD_SCRUB, { 0x0100, 0x0300, 0x0500 }, // shoots 1, 3 or 5 nuts in a row
        { LocType::ABOVE_GROUND, LocType::UNDERWATER, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_BARI] = EnemyType("Bari", &SoulBiriBari, ACTOR_BARI, { 0xFFFF },
        { LocType::ABOVE_GROUND, LocType::UNDERWATER, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_BUBBLE_BLUE] = EnemyType("Bubble (Blue)", &SoulBubble, ACTOR_BUBBLE, { 0xFFFF },
        { LocType::ABOVE_GROUND, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_BUBBLE_FIRE] = EnemyType("Bubble (Fire)", &SoulBubble, ACTOR_BUBBLE, { 0xFFFE },
        { LocType::ABOVE_GROUND });
    enemyTypes[ENEMY_BUBBLE_GREEN] = EnemyType("Bubble (Green)", &SoulBubble, ACTOR_BUBBLE, { 0x02FC, 0x00FB }, // small / big
        { LocType::ABOVE_GROUND, LocType::ABOVE_VOID, LocType::ABOVE_WATER, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_BUBBLE_WHITE] = EnemyType("Bubble (White)", &SoulBubble, ACTOR_BUBBLE, { 0x00FD },
        { LocType::ABOVE_GROUND, LocType::ABOVE_VOID, LocType::ABOVE_WATER, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_FLYING_FLOOR_TILE] = EnemyType("Flying Floor Tile", &SoulFlyingTrap, ACTOR_FLYING_FLOOR_TILE, { 0x0000 },
        { LocType::ABOVE_GROUND, LocType::UNDERWATER, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_BEAMOS] = EnemyType("Beamos", &SoulBeamos, ACTOR_BEAMOS, { 0x0500, 0x0501 }, // big / small
        { LocType::ABOVE_GROUND, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_FLOORMASTER] = EnemyType("Floormaster", &SoulWallmaster, ACTOR_FLOORMASTER, { 0x0000 },
        { LocType::ABOVE_GROUND, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_REDEAD] = EnemyType("Redead", &SoulRedeadGibdo, ACTOR_REDEAD, { 0x7F01, 0x7F02 }, // standing / crouching
        { LocType::ABOVE_GROUND, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_GIBDO] = EnemyType("Gibdo", &SoulRedeadGibdo, ACTOR_REDEAD, { 0x7FFE },
        { LocType::ABOVE_GROUND, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_POE_SISTER] = EnemyType("Poe Sister", &SoulPoe, ACTOR_POE_SISTER, { 0x0000 },
        { /* Unimplemented */ });
    enemyTypes[ENEMY_DEAD_HAND_HAND] = EnemyType("Dead Hand's Hand", &SoulDeadHand, ACTOR_DEAD_HAND_HAND, { 0x0000 },
        { LocType::ABOVE_GROUND, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_SKULLWALLTULA] = EnemyType("Skullwalltula", &SoulSkulltula, ACTOR_SKULLWALLTULA, { 0x0000 },
        { LocType::ABOVE_GROUND, LocType::UNDERWATER, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_FLARE_DANCER] = EnemyType("Flare Dancer", &SoulFlareDancer, ACTOR_FLARE_DANCER, { 0x0000 },
        { LocType::ABOVE_GROUND });
    enemyTypes[ENEMY_DEAD_HAND] = EnemyType("Dead Hand", &SoulDeadHand, ACTOR_DEAD_HAND, { 0x0000 },
        { /* Unimplemented */ });
    enemyTypes[ENEMY_SHELL_BLADE] = EnemyType("Shell Blade", &SoulShellBlade, ACTOR_SHELL_BLADE, { 0x0000 },
        { LocType::ABOVE_GROUND, LocType::UNDERWATER, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_BIG_OCTO] = EnemyType("Big Octo", &SoulOctorok, ACTOR_BIG_OCTO, { 0x0000 },
        { /* Unimplemented */ });
    enemyTypes[ENEMY_DEKU_BABA_WITHERED] = EnemyType("Deku Baba (Withered)", &SoulDekuBaba, ACTOR_WITHERED_DEKU_BABA, { 0x0000 },
        { LocType::ABOVE_GROUND, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_LIKE_LIKE] = EnemyType("Like Like", &SoulLikeLike, ACTOR_LIKE_LIKE, { 0x0000 },
        { LocType::ABOVE_GROUND, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_PARASITIC_TENTACLE] = EnemyType("Parasitic Tentacle", &SoulParasiticTentacle, ACTOR_PARASITIC_TENTACLE, { 0x0000 },
        { /* Unimplemented */ });
    enemyTypes[ENEMY_SPIKE] = EnemyType("Spike", &SoulSpike, ACTOR_SPIKE, { 0x0000 },
        { LocType::ABOVE_GROUND, LocType::UNDERWATER, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_ANUBIS] = EnemyType("Anubis", &SoulAnubis, ACTOR_ANUBIS_SPAWNER, { 0x0003 },
        { LocType::ABOVE_GROUND, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_IRON_KNUCKLE] = EnemyType("Iron Knuckle", &SoulGerudo, ACTOR_IRON_KNUCKLE, { 0xFF01, 0xFF02, 0xFF03 }, // silver / black / white
        { LocType::ABOVE_GROUND, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_SKULL_KID] = EnemyType("Skull Kid", &SoulSkullKid, ACTOR_SKULL_KID, { 0xFFFF },
        { LocType::ABOVE_GROUND, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_FLYING_POT] = EnemyType("Flying Pot", &SoulFlyingTrap, ACTOR_FLYING_POT, { 0x0000 },
        { LocType::ABOVE_GROUND, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_FREEZARD] = EnemyType("Freezard", &SoulFreezard, ACTOR_FREEZARD, { 0x0000, 0xFFFF }, // normal / appears and moves when approached
        { LocType::ABOVE_GROUND, LocType::UNDERWATER, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_STINGER_WATER] = EnemyType("Stinger (Water)", &SoulStinger, ACTOR_STINGER_WATER, { 0x0000 },
        { LocType::UNDERWATER, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_HINT_DEKU_SCRUB] = EnemyType("Deku Scrub", &SoulDekuScrub, ACTOR_HINT_DEKU_SCRUB, { 0x0000 },
        { LocType::ABOVE_GROUND, LocType::UNDERWATER, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_GERUDO_FIGHTER] = EnemyType("Gerudo Fighter", &SoulGerudo, ACTOR_GERUDO_FIGHTER, { 0x0000 },
        { LocType::ABOVE_GROUND, LocType::SHALLOW_WATER });
    enemyTypes[ENEMY_WOLFOS] = EnemyType("Wolfos", &SoulWolfos, ACTOR_WOLFOS, { 0xFF00, 0xFF01 }, // normal / white
        { LocType::ABOVE_GROUND, LocType::SHALLOW_WATER, LocType::SPAWNER });
    enemyTypes[ENEMY_STALCHILD] = EnemyType("Stalchild", &SoulStalchild, ACTOR_STALCHILD, { 0x0000, 0x0005 }, // normal / big (20 kills)
        { LocType::ABOVE_GROUND, LocType::SHALLOW_WATER, LocType::SPAWNER });
    enemyTypes[ENEMY_GUAY] = EnemyType("Guay", &SoulGuay, ACTOR_GUAY, { 0x0000, 0x0001 }, // normal / big
        { LocType::ABOVE_GROUND, LocType::ABOVE_VOID, LocType::UNDERWATER, LocType::ABOVE_WATER, LocType::SHALLOW_WATER });
};

void InitEnemyLocations(void) {
    enemyLocations.clear();

    // Overworld locations
    enemyLocations[10][0][0][1]      = EnemyLocation(ENEMY_DINOLFOS,           LocType::ABOVE_GROUND);
    enemyLocations[10][0][0][2]      = EnemyLocation(ENEMY_DINOLFOS,           LocType::ABOVE_GROUND);
    enemyLocations[10][0][2][5]      = EnemyLocation(ENEMY_STALFOS,            LocType::ABOVE_GROUND);
    enemyLocations[10][0][2][6]      = EnemyLocation(ENEMY_STALFOS,            LocType::ABOVE_GROUND);
    enemyLocations[10][0][4][1]      = EnemyLocation(ENEMY_IRON_KNUCKLE,       LocType::ABOVE_GROUND);
    enemyLocations[10][0][4][2]      = EnemyLocation(ENEMY_IRON_KNUCKLE,       LocType::ABOVE_GROUND);
    enemyLocations[10][0][7][1]      = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
    enemyLocations[10][0][7][2]      = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
    enemyLocations[10][0][7][3]      = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
    enemyLocations[10][0][7][4]      = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
    enemyLocations[10][0][7][5]      = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
    enemyLocations[10][0][7][6]      = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
    enemyLocations[12][0][1][1]      = EnemyLocation(ENEMY_GERUDO_FIGHTER,     LocType::ABOVE_GROUND);
    enemyLocations[12][0][2][1]      = EnemyLocation(ENEMY_GERUDO_FIGHTER,     LocType::ABOVE_GROUND);
    enemyLocations[12][0][4][1]      = EnemyLocation(ENEMY_GERUDO_FIGHTER,     LocType::ABOVE_GROUND);
    enemyLocations[12][0][5][1]      = EnemyLocation(ENEMY_GERUDO_FIGHTER,     LocType::ABOVE_GROUND);
    enemyLocations[10][0][7][7]      = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
    enemyLocations[15][0][0][4]      = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
    enemyLocations[23][0][1][0]      = EnemyLocation(ENEMY_IRON_KNUCKLE,       LocType::ABOVE_GROUND);
    enemyLocations[34][0][0][0]      = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
    enemyLocations[34][0][0][1]      = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
    enemyLocations[34][0][0][2]      = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
    enemyLocations[34][0][0][3]      = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
    enemyLocations[34][0][0][4]      = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
    enemyLocations[34][0][0][5]      = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
    enemyLocations[34][0][0][6]      = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
    enemyLocations[34][0][0][7]      = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
    enemyLocations[62][0][2][0]      = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
    enemyLocations[62][0][2][1]      = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
    enemyLocations[62][0][4][0]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
    enemyLocations[62][0][5][0]      = EnemyLocation(ENEMY_OCTOROK,            LocType::ABOVE_WATER);
    enemyLocations[62][0][7][0]      = EnemyLocation(ENEMY_WOLFOS,             LocType::ABOVE_GROUND);
    enemyLocations[62][0][7][1]      = EnemyLocation(ENEMY_WOLFOS,             LocType::ABOVE_GROUND);
    enemyLocations[62][0][8][0]      = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
    enemyLocations[62][0][8][1]      = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
    enemyLocations[62][0][10][2]     = EnemyLocation(ENEMY_TEKTITE_BLUE,       LocType::ABOVE_WATER);
    enemyLocations[62][0][13][0]     = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
    enemyLocations[63][0][0][1]      = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
    enemyLocations[65][0][1][0]      = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
    enemyLocations[65][0][1][1]      = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
    enemyLocations[65][0][1][2]      = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
    enemyLocations[65][0][3][0]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
    enemyLocations[65][0][3][1]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
    enemyLocations[65][0][3][3]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
    enemyLocations[65][0][3][4]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
    enemyLocations[72][0][2][3]      = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
    enemyLocations[72][0][2][4]      = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
    enemyLocations[72][0][3][2]      = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
    enemyLocations[72][0][3][3]      = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
    enemyLocations[81][0][0][8]      = EnemyLocation(ENEMY_PEAHAT,             LocType::ABOVE_GROUND);
    enemyLocations[81][0][0][9]      = EnemyLocation(ENEMY_PEAHAT,             LocType::ABOVE_GROUND);
    enemyLocations[81][0][0][10]     = EnemyLocation(ENEMY_PEAHAT,             LocType::ABOVE_GROUND);
    enemyLocations[81][0][0][11]     = EnemyLocation(ENEMY_PEAHAT,             LocType::ABOVE_GROUND);
    enemyLocations[81][0][0][12]     = EnemyLocation(ENEMY_PEAHAT,             LocType::ABOVE_GROUND);
    enemyLocations[81][0][0][13]     = EnemyLocation(ENEMY_PEAHAT,             LocType::ABOVE_GROUND);
    enemyLocations[81][0][0][14]     = EnemyLocation(ENEMY_PEAHAT,             LocType::ABOVE_GROUND);
    enemyLocations[81][0][0][0xFF]   = EnemyLocation(ENEMY_STALCHILD,          LocType::SPAWNER);
    // Graveyard: don't randomize enemies that don't appear in the base game due to missing object.
    // enemyLocations[83][2][1][2]   = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
    // enemyLocations[83][2][1][3]   = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
    // enemyLocations[83][2][1][4]   = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
    // enemyLocations[83][2][1][5]   = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
    // enemyLocations[83][2][1][6]   = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
    // enemyLocations[83][2][1][7]   = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
    // enemyLocations[83][2][1][8]   = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
    enemyLocations[83][2][1][12]     = EnemyLocation(ENEMY_POE,                LocType::ABOVE_GROUND);
    enemyLocations[83][2][1][13]     = EnemyLocation(ENEMY_POE,                LocType::ABOVE_GROUND);
    enemyLocations[83][2][1][14]     = EnemyLocation(ENEMY_POE,                LocType::ABOVE_GROUND);
    enemyLocations[84][0][0][4]      = EnemyLocation(ENEMY_OCTOROK,            LocType::ABOVE_WATER);
    enemyLocations[84][0][0][5]      = EnemyLocation(ENEMY_OCTOROK,            LocType::ABOVE_WATER);
    enemyLocations[84][0][0][42]     = EnemyLocation(ENEMY_TEKTITE_BLUE,       LocType::ABOVE_WATER);
    enemyLocations[84][0][0][43]     = EnemyLocation(ENEMY_TEKTITE_BLUE,       LocType::ABOVE_WATER);
    enemyLocations[84][2][0][2]      = EnemyLocation(ENEMY_OCTOROK,            LocType::ABOVE_WATER);
    enemyLocations[84][2][0][3]      = EnemyLocation(ENEMY_OCTOROK,            LocType::ABOVE_WATER);
    enemyLocations[84][2][0][4]      = EnemyLocation(ENEMY_OCTOROK,            LocType::ABOVE_WATER);
    enemyLocations[84][2][0][5]      = EnemyLocation(ENEMY_OCTOROK,            LocType::ABOVE_WATER);
    enemyLocations[84][2][0][6]      = EnemyLocation(ENEMY_OCTOROK,            LocType::ABOVE_WATER);
    enemyLocations[84][2][0][7]      = EnemyLocation(ENEMY_OCTOROK,            LocType::ABOVE_WATER);
    enemyLocations[84][2][0][8]      = EnemyLocation(ENEMY_OCTOROK,            LocType::ABOVE_WATER);
    enemyLocations[84][2][0][9]      = EnemyLocation(ENEMY_OCTOROK,            LocType::ABOVE_WATER);
    enemyLocations[85][0][1][1]      = EnemyLocation(ENEMY_DEKU_BABA_WITHERED, LocType::ABOVE_GROUND);
    enemyLocations[85][0][1][2]      = EnemyLocation(ENEMY_DEKU_BABA_WITHERED, LocType::ABOVE_GROUND);
    enemyLocations[85][0][1][3]      = EnemyLocation(ENEMY_DEKU_BABA_WITHERED, LocType::ABOVE_GROUND);
    enemyLocations[85][0][1][4]      = EnemyLocation(ENEMY_DEKU_BABA_WITHERED, LocType::ABOVE_GROUND);
    enemyLocations[85][0][1][5]      = EnemyLocation(ENEMY_DEKU_BABA_WITHERED, LocType::ABOVE_GROUND);
    enemyLocations[85][2][0][1]      = EnemyLocation(ENEMY_OCTOROK,            LocType::ABOVE_WATER);
    enemyLocations[85][2][0][2]      = EnemyLocation(ENEMY_OCTOROK,            LocType::ABOVE_WATER);
    enemyLocations[85][2][0][3]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
    enemyLocations[85][2][0][4]      = EnemyLocation(ENEMY_MAD_SCRUB,          LocType::ABOVE_GROUND);
    enemyLocations[85][2][0][5]      = EnemyLocation(ENEMY_MAD_SCRUB,          LocType::ABOVE_GROUND);
    enemyLocations[85][2][0][6]      = EnemyLocation(ENEMY_MAD_SCRUB,          LocType::ABOVE_GROUND);
    enemyLocations[85][2][0][7]      = EnemyLocation(ENEMY_DEKU_BABA_BIG,      LocType::ABOVE_GROUND);
    enemyLocations[85][2][0][8]      = EnemyLocation(ENEMY_DEKU_BABA_BIG,      LocType::ABOVE_GROUND);
    enemyLocations[85][2][0][9]      = EnemyLocation(ENEMY_DEKU_BABA_BIG,      LocType::ABOVE_GROUND);
    enemyLocations[85][2][0][10]     = EnemyLocation(ENEMY_DEKU_BABA_BIG,      LocType::ABOVE_GROUND);
    enemyLocations[85][2][1][2]      = EnemyLocation(ENEMY_DEKU_BABA_BIG,      LocType::ABOVE_GROUND);
    enemyLocations[85][2][1][3]      = EnemyLocation(ENEMY_DEKU_BABA_BIG,      LocType::ABOVE_GROUND);
    enemyLocations[85][2][1][4]      = EnemyLocation(ENEMY_DEKU_BABA_BIG,      LocType::ABOVE_GROUND);
    enemyLocations[85][2][1][5]      = EnemyLocation(ENEMY_DEKU_BABA_BIG,      LocType::ABOVE_GROUND);
    enemyLocations[85][2][1][6]      = EnemyLocation(ENEMY_DEKU_BABA_BIG,      LocType::ABOVE_GROUND);
    enemyLocations[85][2][1][7]      = EnemyLocation(ENEMY_DEKU_BABA_BIG,      LocType::ABOVE_GROUND);
    enemyLocations[86][0][0][1]      = EnemyLocation(ENEMY_WOLFOS,             LocType::ABOVE_GROUND);
    enemyLocations[86][0][0][5]      = EnemyLocation(ENEMY_MAD_SCRUB,          LocType::ABOVE_GROUND);
    enemyLocations[86][0][0][6]      = EnemyLocation(ENEMY_MAD_SCRUB,          LocType::ABOVE_GROUND);
    enemyLocations[86][0][0][7]      = EnemyLocation(ENEMY_MAD_SCRUB,          LocType::ABOVE_GROUND);
    enemyLocations[86][0][0][8]      = EnemyLocation(ENEMY_MAD_SCRUB,          LocType::ABOVE_GROUND);
    enemyLocations[86][0][0][9]      = EnemyLocation(ENEMY_MAD_SCRUB,          LocType::ABOVE_GROUND);
    enemyLocations[86][0][0][10]     = EnemyLocation(ENEMY_MAD_SCRUB,          LocType::ABOVE_GROUND);
    // Idk what this extra Moblin is, it's out of bounds behind the ladder
    // enemyLocations[86][2][0][5]   = EnemyLocation(ENEMY_MOBLIN_SPEAR,       LocType::ABOVE_GROUND);
    enemyLocations[86][2][0][6]      = EnemyLocation(ENEMY_MOBLIN_SPEAR,       LocType::ABOVE_GROUND);
    enemyLocations[86][2][0][7]      = EnemyLocation(ENEMY_MOBLIN_SPEAR,       LocType::ABOVE_GROUND);
    enemyLocations[86][2][0][8]      = EnemyLocation(ENEMY_MOBLIN_SPEAR,       LocType::ABOVE_GROUND);
    enemyLocations[86][2][0][9]      = EnemyLocation(ENEMY_MOBLIN_SPEAR,       LocType::ABOVE_GROUND);
    enemyLocations[86][2][0][10]     = EnemyLocation(ENEMY_MOBLIN_SPEAR,       LocType::ABOVE_GROUND);
    enemyLocations[86][2][0][11]     = EnemyLocation(ENEMY_MOBLIN_CLUB,        LocType::ABOVE_GROUND);
    enemyLocations[87][0][0][3]      = EnemyLocation(ENEMY_OCTOROK,            LocType::ABOVE_WATER);
    enemyLocations[87][0][0][4]      = EnemyLocation(ENEMY_OCTOROK,            LocType::ABOVE_WATER);
    enemyLocations[87][0][0][5]      = EnemyLocation(ENEMY_OCTOROK,            LocType::ABOVE_WATER);
    enemyLocations[87][0][0][19]     = EnemyLocation(ENEMY_TEKTITE_BLUE,       LocType::ABOVE_WATER);
    enemyLocations[87][0][0][20]     = EnemyLocation(ENEMY_TEKTITE_BLUE,       LocType::ABOVE_WATER);
    enemyLocations[87][0][0][21]     = EnemyLocation(ENEMY_TEKTITE_BLUE,       LocType::ABOVE_WATER);
    enemyLocations[87][2][0][15]     = EnemyLocation(ENEMY_GUAY,               { LocType::ABOVE_GROUND, LocType::ABOVE_WATER });
    enemyLocations[87][2][0][16]     = EnemyLocation(ENEMY_GUAY,               LocType::ABOVE_GROUND);
    enemyLocations[87][2][0][17]     = EnemyLocation(ENEMY_GUAY,               { LocType::ABOVE_GROUND, LocType::ABOVE_WATER });
    enemyLocations[87][2][0][18]     = EnemyLocation(ENEMY_GUAY,               LocType::ABOVE_WATER);
    enemyLocations[87][2][0][22]     = EnemyLocation(ENEMY_TEKTITE_BLUE,       LocType::ABOVE_GROUND);
    enemyLocations[87][2][0][23]     = EnemyLocation(ENEMY_TEKTITE_BLUE,       { LocType::ABOVE_GROUND, LocType::UNDERWATER });
    enemyLocations[87][2][0][24]     = EnemyLocation(ENEMY_TEKTITE_BLUE,       { LocType::ABOVE_GROUND, LocType::UNDERWATER });
    enemyLocations[87][2][0][25]     = EnemyLocation(ENEMY_TEKTITE_BLUE,       { LocType::ABOVE_GROUND, LocType::UNDERWATER });
    enemyLocations[87][2][0][26]     = EnemyLocation(ENEMY_TEKTITE_BLUE,       LocType::ABOVE_GROUND);
    enemyLocations[87][2][0][27]     = EnemyLocation(ENEMY_TEKTITE_BLUE,       { LocType::ABOVE_GROUND, LocType::UNDERWATER });
    enemyLocations[87][2][0][28]     = EnemyLocation(ENEMY_TEKTITE_BLUE,       { LocType::ABOVE_GROUND, LocType::UNDERWATER });
    enemyLocations[87][2][0][29]     = EnemyLocation(ENEMY_TEKTITE_BLUE,       { LocType::ABOVE_GROUND, LocType::UNDERWATER });
    enemyLocations[89][2][0][18]     = EnemyLocation(ENEMY_OCTOROK,            LocType::ABOVE_WATER);
    enemyLocations[89][2][0][19]     = EnemyLocation(ENEMY_OCTOROK,            LocType::ABOVE_WATER);
    enemyLocations[89][2][0][20]     = EnemyLocation(ENEMY_OCTOROK,            LocType::ABOVE_WATER);
    enemyLocations[89][2][0][21]     = EnemyLocation(ENEMY_OCTOROK,            LocType::ABOVE_WATER);
    enemyLocations[89][2][0][24]     = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
    enemyLocations[89][2][0][25]     = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
    enemyLocations[89][2][0][26]     = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
    enemyLocations[89][2][0][27]     = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
    enemyLocations[89][2][0][28]     = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
    enemyLocations[89][2][0][50]     = EnemyLocation(ENEMY_TEKTITE_BLUE,       LocType::SHALLOW_WATER);
    enemyLocations[90][2][0][3]      = EnemyLocation(ENEMY_OCTOROK,            LocType::ABOVE_WATER);
    enemyLocations[90][2][0][4]      = EnemyLocation(ENEMY_OCTOROK,            LocType::ABOVE_WATER);
    enemyLocations[90][2][0][5]      = EnemyLocation(ENEMY_OCTOROK,            LocType::ABOVE_WATER);
    enemyLocations[90][2][0][6]      = EnemyLocation(ENEMY_OCTOROK,            LocType::ABOVE_WATER);
    enemyLocations[90][2][0][7]      = EnemyLocation(ENEMY_OCTOROK,            LocType::ABOVE_WATER);
    // Lost Woods: don't randomize enemies that don't appear in the base game due to missing object.
    // enemyLocations[91][0][3][2]   = EnemyLocation(ENEMY_OCTOROK,            LocType::ABOVE_WATER);
    enemyLocations[91][2][1][1]      = EnemyLocation(ENEMY_SKULL_KID,          LocType::ABOVE_GROUND);
    enemyLocations[91][2][1][2]      = EnemyLocation(ENEMY_SKULL_KID,          LocType::ABOVE_GROUND);
    // enemyLocations[91][2][3][2]   = EnemyLocation(ENEMY_OCTOROK,            LocType::ABOVE_WATER);
    enemyLocations[91][2][9][1]      = EnemyLocation(ENEMY_SKULL_KID,          LocType::ABOVE_GROUND);
    enemyLocations[92][0][0][7]      = EnemyLocation(ENEMY_GUAY,               LocType::ABOVE_GROUND);
    enemyLocations[92][0][0][8]      = EnemyLocation(ENEMY_GUAY,               LocType::ABOVE_GROUND);
    enemyLocations[92][0][0][9]      = EnemyLocation(ENEMY_GUAY,               LocType::ABOVE_GROUND);
    enemyLocations[92][0][0][0xFF]   = EnemyLocation(ENEMY_LEEVER,             LocType::SPAWNER);
    enemyLocations[92][2][0][7]      = EnemyLocation(ENEMY_GUAY,               LocType::ABOVE_GROUND);
    enemyLocations[92][2][0][8]      = EnemyLocation(ENEMY_GUAY,               LocType::ABOVE_GROUND);
    enemyLocations[92][2][0][9]      = EnemyLocation(ENEMY_GUAY,               LocType::ABOVE_GROUND);
    enemyLocations[92][2][0][10]     = EnemyLocation(ENEMY_GUAY,               LocType::ABOVE_GROUND);
    enemyLocations[92][2][0][11]     = EnemyLocation(ENEMY_GUAY,               LocType::ABOVE_GROUND);
    enemyLocations[92][2][0][0xFF]   = EnemyLocation(ENEMY_LEEVER,             LocType::SPAWNER);
    enemyLocations[94][0][1][0xFF]   = EnemyLocation(ENEMY_LEEVER,             LocType::SPAWNER);
    enemyLocations[96][0][0][6]      = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
    enemyLocations[96][0][0][7]      = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
    enemyLocations[96][0][0][8]      = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
    enemyLocations[96][0][0][9]      = EnemyLocation(ENEMY_TEKTITE_RED,        LocType::ABOVE_GROUND);
    enemyLocations[96][0][0][10]     = EnemyLocation(ENEMY_TEKTITE_RED,        LocType::ABOVE_GROUND);
    enemyLocations[96][0][0][11]     = EnemyLocation(ENEMY_TEKTITE_RED,        LocType::ABOVE_GROUND);
    enemyLocations[96][0][0][12]     = EnemyLocation(ENEMY_TEKTITE_RED,        LocType::ABOVE_GROUND);
    enemyLocations[96][2][0][2]      = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
    enemyLocations[96][2][0][3]      = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
    enemyLocations[96][2][0][4]      = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
    enemyLocations[96][2][0][6]      = EnemyLocation(ENEMY_TEKTITE_RED,        LocType::ABOVE_GROUND);
    enemyLocations[96][2][0][7]      = EnemyLocation(ENEMY_TEKTITE_RED,        LocType::ABOVE_GROUND);
    enemyLocations[96][2][0][8]      = EnemyLocation(ENEMY_TEKTITE_RED,        LocType::ABOVE_GROUND);
    enemyLocations[97][2][1][8]      = EnemyLocation(ENEMY_BUBBLE_FIRE,        LocType::ABOVE_VOID);
    enemyLocations[97][2][1][9]      = EnemyLocation(ENEMY_BUBBLE_FIRE,        LocType::ABOVE_VOID);
    enemyLocations[97][2][1][10]     = EnemyLocation(ENEMY_BUBBLE_FIRE,        LocType::ABOVE_VOID);
    enemyLocations[97][2][1][11]     = EnemyLocation(ENEMY_BUBBLE_FIRE,        LocType::ABOVE_VOID);
    enemyLocations[97][2][1][12]     = EnemyLocation(ENEMY_BUBBLE_FIRE,        LocType::ABOVE_VOID);
    enemyLocations[99][1][0][10]     = EnemyLocation(ENEMY_GUAY,               LocType::ABOVE_GROUND);
    enemyLocations[99][1][0][11]     = EnemyLocation(ENEMY_GUAY,               LocType::ABOVE_GROUND);
    enemyLocations[99][1][0][12]     = EnemyLocation(ENEMY_GUAY,               LocType::ABOVE_GROUND);
    enemyLocations[99][1][0][13]     = EnemyLocation(ENEMY_GUAY,               LocType::ABOVE_GROUND);
    enemyLocations[99][1][0][14]     = EnemyLocation(ENEMY_GUAY,               LocType::ABOVE_GROUND);
    enemyLocations[99][1][0][15]     = EnemyLocation(ENEMY_GUAY,               LocType::ABOVE_GROUND);
    enemyLocations[99][1][0][16]     = EnemyLocation(ENEMY_GUAY,               LocType::ABOVE_GROUND);
    enemyLocations[99][1][0][17]     = EnemyLocation(ENEMY_GUAY,               LocType::ABOVE_GROUND);
    enemyLocations[99][1][0][18]     = EnemyLocation(ENEMY_GUAY,               LocType::ABOVE_GROUND);
    enemyLocations[99][1][0][19]     = EnemyLocation(ENEMY_GUAY,               LocType::ABOVE_GROUND);
    enemyLocations[99][1][0][20]     = EnemyLocation(ENEMY_GUAY,               LocType::ABOVE_GROUND);
    enemyLocations[99][1][0][21]     = EnemyLocation(ENEMY_GUAY,               LocType::ABOVE_GROUND);
    enemyLocations[99][1][0][22]     = EnemyLocation(ENEMY_GUAY,               LocType::ABOVE_GROUND);
    enemyLocations[99][1][0][23]     = EnemyLocation(ENEMY_GUAY,               LocType::ABOVE_GROUND);
    enemyLocations[99][1][0][24]     = EnemyLocation(ENEMY_GUAY,               LocType::ABOVE_GROUND);

    // Vanilla dungeons
    if (Dungeon::DekuTree.IsVanilla()) {
        enemyLocations[0][0][0][0]       = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
        enemyLocations[0][0][0][1]       = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
        enemyLocations[0][0][0][2]       = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
        enemyLocations[0][0][0][3]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[0][0][0][4]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[0][0][0][5]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[0][0][0][11]      = EnemyLocation(ENEMY_DEKU_BABA_SMALL,    LocType::ABOVE_GROUND);
        enemyLocations[0][0][0][12]      = EnemyLocation(ENEMY_DEKU_BABA_SMALL,    LocType::ABOVE_GROUND);
        enemyLocations[0][0][0][13]      = EnemyLocation(ENEMY_DEKU_BABA_SMALL,    LocType::ABOVE_GROUND);
        enemyLocations[0][0][1][0]       = EnemyLocation(ENEMY_HINT_DEKU_SCRUB,    LocType::ABOVE_GROUND);
        enemyLocations[0][0][3][0]       = EnemyLocation(ENEMY_DEKU_BABA_WITHERED, LocType::ABOVE_GROUND);
        enemyLocations[0][0][3][3]       = EnemyLocation(ENEMY_DEKU_BABA_SMALL,    LocType::ABOVE_GROUND);
        enemyLocations[0][0][3][4]       = EnemyLocation(ENEMY_DEKU_BABA_SMALL,    LocType::ABOVE_GROUND);
        enemyLocations[0][0][3][5]       = EnemyLocation(ENEMY_DEKU_BABA_SMALL,    LocType::ABOVE_GROUND);
        enemyLocations[0][0][4][4]       = EnemyLocation(ENEMY_HINT_DEKU_SCRUB,    LocType::ABOVE_GROUND);
        enemyLocations[0][0][5][0]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[0][0][6][0]       = EnemyLocation(ENEMY_DEKU_BABA_WITHERED, LocType::ABOVE_GROUND);
        enemyLocations[0][0][6][1]       = EnemyLocation(ENEMY_DEKU_BABA_WITHERED, LocType::ABOVE_GROUND);
        enemyLocations[0][0][6][4]       = EnemyLocation(ENEMY_DEKU_BABA_SMALL,    LocType::ABOVE_GROUND);
        enemyLocations[0][0][7][0]       = EnemyLocation(ENEMY_DEKU_BABA_WITHERED, LocType::ABOVE_GROUND);
        enemyLocations[0][0][7][1]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[0][0][7][4]       = EnemyLocation(ENEMY_DEKU_BABA_SMALL,    LocType::ABOVE_GROUND);
        enemyLocations[0][0][7][5]       = EnemyLocation(ENEMY_GOHMA_LARVA,        LocType::ABOVE_GROUND);
        enemyLocations[0][0][7][6]       = EnemyLocation(ENEMY_GOHMA_LARVA,        LocType::ABOVE_GROUND);
        enemyLocations[0][0][7][7]       = EnemyLocation(ENEMY_GOHMA_LARVA,        LocType::ABOVE_GROUND);
        enemyLocations[0][0][8][0]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[0][0][9][3]       = EnemyLocation(ENEMY_HINT_DEKU_SCRUB,    LocType::ABOVE_GROUND);
        enemyLocations[0][0][9][4]       = EnemyLocation(ENEMY_HINT_DEKU_SCRUB,    LocType::ABOVE_GROUND);
        enemyLocations[0][0][9][5]       = EnemyLocation(ENEMY_HINT_DEKU_SCRUB,    LocType::ABOVE_GROUND);
        enemyLocations[0][0][10][0]      = EnemyLocation(ENEMY_DEKU_BABA_WITHERED, LocType::ABOVE_GROUND);
        enemyLocations[0][0][10][1]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[0][0][10][4]      = EnemyLocation(ENEMY_DEKU_BABA_SMALL,    LocType::ABOVE_GROUND);
    }
    if (Dungeon::DodongosCavern.IsVanilla()) {
        enemyLocations[1][0][0][5]       = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[1][0][0][6]       = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[1][0][0][7]       = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[1][0][0][8]       = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[1][0][0][9]       = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[1][0][1][0]       = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[1][0][1][1]       = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[1][0][1][2]       = EnemyLocation(ENEMY_DODONGO_BABY,       LocType::ABOVE_GROUND);
        enemyLocations[1][0][1][3]       = EnemyLocation(ENEMY_DODONGO_BABY,       LocType::ABOVE_GROUND);
        enemyLocations[1][0][1][4]       = EnemyLocation(ENEMY_DODONGO_BABY,       LocType::ABOVE_GROUND);
        enemyLocations[1][0][1][5]       = EnemyLocation(ENEMY_DODONGO_BABY,       LocType::ABOVE_GROUND);
        enemyLocations[1][0][1][6]       = EnemyLocation(ENEMY_DODONGO_BABY,       LocType::ABOVE_GROUND);
        enemyLocations[1][0][1][7]       = EnemyLocation(ENEMY_DODONGO_BABY,       LocType::ABOVE_GROUND);
        enemyLocations[1][0][2][0]       = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
        enemyLocations[1][0][3][0]       = EnemyLocation(ENEMY_LIZALFOS,           LocType::ABOVE_GROUND);
        enemyLocations[1][0][3][1]       = EnemyLocation(ENEMY_LIZALFOS,           LocType::ABOVE_GROUND);
        enemyLocations[1][0][3][2]       = EnemyLocation(ENEMY_LIZALFOS,           LocType::ABOVE_GROUND);
        enemyLocations[1][0][3][3]       = EnemyLocation(ENEMY_LIZALFOS,           LocType::ABOVE_GROUND);
        enemyLocations[1][0][4][0]       = EnemyLocation(ENEMY_DODONGO,            LocType::ABOVE_GROUND);
        enemyLocations[1][0][4][1]       = EnemyLocation(ENEMY_DODONGO,            LocType::ABOVE_GROUND);
        enemyLocations[1][0][4][2]       = EnemyLocation(ENEMY_DODONGO,            LocType::ABOVE_GROUND);
        enemyLocations[1][0][5][0]       = EnemyLocation(ENEMY_ARMOS,              LocType::ABOVE_GROUND);
        enemyLocations[1][0][5][1]       = EnemyLocation(ENEMY_ARMOS,              LocType::ABOVE_GROUND);
        enemyLocations[1][0][5][2]       = EnemyLocation(ENEMY_ARMOS,              LocType::ABOVE_GROUND);
        enemyLocations[1][0][5][3]       = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[1][0][5][4]       = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[1][0][7][1]       = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[1][0][7][2]       = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[1][0][8][0]       = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[1][0][8][1]       = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[1][0][10][1]      = EnemyLocation(ENEMY_DODONGO_BABY,       LocType::ABOVE_GROUND);
        enemyLocations[1][0][10][2]      = EnemyLocation(ENEMY_DODONGO_BABY,       LocType::ABOVE_GROUND);
        enemyLocations[1][0][10][3]      = EnemyLocation(ENEMY_DODONGO_BABY,       LocType::ABOVE_GROUND);
        enemyLocations[1][0][11][0]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[1][0][11][1]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[1][0][11][2]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[1][0][14][0]      = EnemyLocation(ENEMY_ARMOS,              LocType::ABOVE_GROUND);
        enemyLocations[1][0][15][0]      = EnemyLocation(ENEMY_ARMOS,              LocType::ABOVE_GROUND);
    }
    if (Dungeon::JabuJabusBelly.IsVanilla()) {
        enemyLocations[2][0][0][0]       = EnemyLocation(ENEMY_OCTOROK,            LocType::SHALLOW_WATER);
        enemyLocations[2][0][0][1]       = EnemyLocation(ENEMY_OCTOROK,            LocType::SHALLOW_WATER);
        enemyLocations[2][0][0][3]       = EnemyLocation(ENEMY_SHABOM,             LocType::ABOVE_GROUND);
        enemyLocations[2][0][0][4]       = EnemyLocation(ENEMY_SHABOM,             LocType::ABOVE_GROUND);
        enemyLocations[2][0][1][0]       = EnemyLocation(ENEMY_OCTOROK,            LocType::ABOVE_WATER);
        enemyLocations[2][0][1][1]       = EnemyLocation(ENEMY_BIRI,               LocType::ABOVE_GROUND);
        enemyLocations[2][0][2][1]       = EnemyLocation(ENEMY_BARI,               LocType::ABOVE_GROUND);
        enemyLocations[2][0][2][2]       = EnemyLocation(ENEMY_BARI,               LocType::ABOVE_GROUND);
        enemyLocations[2][0][2][4]       = EnemyLocation(ENEMY_BIRI,               LocType::ABOVE_GROUND);
        enemyLocations[2][0][2][5]       = EnemyLocation(ENEMY_BIRI,               LocType::ABOVE_GROUND);
        enemyLocations[2][0][2][6]       = EnemyLocation(ENEMY_BIRI,               LocType::ABOVE_GROUND);
        enemyLocations[2][0][3][1]       = EnemyLocation(ENEMY_BIRI,               LocType::SHALLOW_WATER);
        enemyLocations[2][0][3][2]       = EnemyLocation(ENEMY_BIRI,               LocType::SHALLOW_WATER);
        enemyLocations[2][0][3][3]       = EnemyLocation(ENEMY_BIRI,               LocType::SHALLOW_WATER);
        enemyLocations[2][0][3][4]       = EnemyLocation(ENEMY_BIRI,               LocType::SHALLOW_WATER);
        enemyLocations[2][0][4][0]       = EnemyLocation(ENEMY_OCTOROK,            LocType::SHALLOW_WATER);
        enemyLocations[2][0][5][1]       = EnemyLocation(ENEMY_BIRI,               LocType::ABOVE_GROUND);
        enemyLocations[2][0][5][2]       = EnemyLocation(ENEMY_BIRI,               LocType::ABOVE_GROUND);
        enemyLocations[2][0][5][3]       = EnemyLocation(ENEMY_BIRI,               LocType::ABOVE_GROUND);
        enemyLocations[2][0][5][4]       = EnemyLocation(ENEMY_BIRI,               LocType::ABOVE_GROUND);
        enemyLocations[2][0][5][5]       = EnemyLocation(ENEMY_BIRI,               LocType::ABOVE_GROUND);
        enemyLocations[2][0][6][0]       = EnemyLocation(ENEMY_BIRI,               LocType::ABOVE_GROUND);
        enemyLocations[2][0][6][1]       = EnemyLocation(ENEMY_BIRI,               LocType::ABOVE_GROUND);
        enemyLocations[2][0][7][0]       = EnemyLocation(ENEMY_TAILPASARAN,        LocType::ABOVE_GROUND);
        enemyLocations[2][0][7][1]       = EnemyLocation(ENEMY_TAILPASARAN,        LocType::ABOVE_GROUND);
        enemyLocations[2][0][7][2]       = EnemyLocation(ENEMY_TAILPASARAN,        LocType::ABOVE_GROUND);
        enemyLocations[2][0][7][3]       = EnemyLocation(ENEMY_TAILPASARAN,        LocType::ABOVE_GROUND);
        enemyLocations[2][0][7][4]       = EnemyLocation(ENEMY_TAILPASARAN,        LocType::ABOVE_GROUND);
        enemyLocations[2][0][8][1]       = EnemyLocation(ENEMY_BIRI,               LocType::ABOVE_GROUND);
        enemyLocations[2][0][8][2]       = EnemyLocation(ENEMY_BIRI,               LocType::ABOVE_GROUND);
        enemyLocations[2][0][8][3]       = EnemyLocation(ENEMY_BIRI,               LocType::ABOVE_GROUND);
        enemyLocations[2][0][8][4]       = EnemyLocation(ENEMY_BIRI,               LocType::ABOVE_GROUND);
        enemyLocations[2][0][9][0]       = EnemyLocation(ENEMY_STINGER_FLOOR,      LocType::ABOVE_GROUND);
        enemyLocations[2][0][9][1]       = EnemyLocation(ENEMY_STINGER_FLOOR,      LocType::ABOVE_GROUND);
        enemyLocations[2][0][9][2]       = EnemyLocation(ENEMY_STINGER_FLOOR,      LocType::ABOVE_GROUND);
        enemyLocations[2][0][12][2]      = EnemyLocation(ENEMY_SHABOM,             LocType::ABOVE_GROUND);
        enemyLocations[2][0][12][3]      = EnemyLocation(ENEMY_SHABOM,             LocType::ABOVE_GROUND);
        enemyLocations[2][0][12][4]      = EnemyLocation(ENEMY_SHABOM,             LocType::ABOVE_GROUND);
        enemyLocations[2][0][12][5]      = EnemyLocation(ENEMY_SHABOM,             LocType::ABOVE_GROUND);
        enemyLocations[2][0][12][6]      = EnemyLocation(ENEMY_SHABOM,             LocType::ABOVE_GROUND);
        enemyLocations[2][0][12][7]      = EnemyLocation(ENEMY_SHABOM,             LocType::ABOVE_GROUND);
        enemyLocations[2][0][12][8]      = EnemyLocation(ENEMY_SHABOM,             LocType::ABOVE_GROUND);
        enemyLocations[2][0][12][9]      = EnemyLocation(ENEMY_SHABOM,             LocType::ABOVE_GROUND);
        enemyLocations[2][0][12][10]     = EnemyLocation(ENEMY_SHABOM,             LocType::ABOVE_GROUND);
        enemyLocations[2][0][13][0]      = EnemyLocation(ENEMY_OCTOROK,            LocType::ABOVE_WATER);
        enemyLocations[2][0][13][1]      = EnemyLocation(ENEMY_OCTOROK,            LocType::ABOVE_WATER);
        enemyLocations[2][0][14][0]      = EnemyLocation(ENEMY_STINGER_FLOOR,      LocType::SHALLOW_WATER);
        enemyLocations[2][0][14][1]      = EnemyLocation(ENEMY_STINGER_FLOOR,      LocType::SHALLOW_WATER);
        enemyLocations[2][0][14][2]      = EnemyLocation(ENEMY_STINGER_FLOOR,      LocType::SHALLOW_WATER);
        enemyLocations[2][0][14][10]     = EnemyLocation(ENEMY_SHABOM,             LocType::ABOVE_GROUND);
        enemyLocations[2][0][14][11]     = EnemyLocation(ENEMY_SHABOM,             LocType::ABOVE_GROUND);
        enemyLocations[2][0][14][12]     = EnemyLocation(ENEMY_SHABOM,             LocType::ABOVE_GROUND);
        enemyLocations[2][0][14][13]     = EnemyLocation(ENEMY_SHABOM,             LocType::ABOVE_GROUND);
        enemyLocations[2][0][14][14]     = EnemyLocation(ENEMY_SHABOM,             LocType::ABOVE_GROUND);
        enemyLocations[2][0][14][15]     = EnemyLocation(ENEMY_SHABOM,             LocType::ABOVE_GROUND);
        enemyLocations[2][0][14][16]     = EnemyLocation(ENEMY_SHABOM,             LocType::ABOVE_GROUND);
    }
    if (Dungeon::ForestTemple.IsVanilla()) {
        enemyLocations[3][0][0][0]       = EnemyLocation(ENEMY_WOLFOS,             LocType::ABOVE_GROUND);
        enemyLocations[3][0][0][1]       = EnemyLocation(ENEMY_WOLFOS,             LocType::ABOVE_GROUND);
        enemyLocations[3][0][1][0]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[3][0][3][4]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[3][0][4][0]       = EnemyLocation(ENEMY_BUBBLE_BLUE,        LocType::ABOVE_GROUND);
        enemyLocations[3][0][5][4]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[3][0][6][0]       = EnemyLocation(ENEMY_STALFOS,            LocType::ABOVE_GROUND);
        enemyLocations[3][0][6][1]       = EnemyLocation(ENEMY_STALFOS,            LocType::ABOVE_GROUND);
        enemyLocations[3][0][7][2]       = EnemyLocation(ENEMY_OCTOROK,            LocType::ABOVE_WATER);
        enemyLocations[3][0][7][3]       = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
        enemyLocations[3][0][7][4]       = EnemyLocation(ENEMY_DEKU_BABA_SMALL,    LocType::ABOVE_GROUND);
        enemyLocations[3][0][7][5]       = EnemyLocation(ENEMY_DEKU_BABA_BIG,      LocType::ABOVE_GROUND);
        enemyLocations[3][0][8][0]       = EnemyLocation(ENEMY_OCTOROK,            LocType::ABOVE_WATER);
        enemyLocations[3][0][8][1]       = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
        enemyLocations[3][0][8][2]       = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
        enemyLocations[3][0][8][3]       = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
        enemyLocations[3][0][8][4]       = EnemyLocation(ENEMY_DEKU_BABA_BIG,      LocType::ABOVE_GROUND);
        enemyLocations[3][0][8][5]       = EnemyLocation(ENEMY_DEKU_BABA_BIG,      LocType::ABOVE_GROUND);
        enemyLocations[3][0][10][0]      = EnemyLocation(ENEMY_BUBBLE_BLUE,        LocType::ABOVE_GROUND);
        enemyLocations[3][0][11][0]      = EnemyLocation(ENEMY_BUBBLE_BLUE,        LocType::ABOVE_GROUND);
        enemyLocations[3][0][11][1]      = EnemyLocation(ENEMY_BUBBLE_BLUE,        LocType::ABOVE_GROUND);
        enemyLocations[3][0][11][2]      = EnemyLocation(ENEMY_BUBBLE_BLUE,        LocType::ABOVE_GROUND);
        enemyLocations[3][0][15][0]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[3][0][15][1]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[3][0][15][2]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[3][0][17][0]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[3][0][18][0]      = EnemyLocation(ENEMY_FLOORMASTER,        LocType::ABOVE_GROUND);
        enemyLocations[3][0][19][0]      = EnemyLocation(ENEMY_WALLMASTER,         LocType::ABOVE_VOID);
        enemyLocations[3][0][20][0]      = EnemyLocation(ENEMY_BUBBLE_GREEN,       LocType::ABOVE_VOID);
        enemyLocations[3][0][20][1]      = EnemyLocation(ENEMY_BUBBLE_GREEN,       LocType::ABOVE_VOID);
        enemyLocations[3][0][20][2]      = EnemyLocation(ENEMY_WALLMASTER,         LocType::ABOVE_VOID);
        enemyLocations[3][0][21][0]      = EnemyLocation(ENEMY_BUBBLE_BLUE,        LocType::ABOVE_GROUND);
        enemyLocations[3][0][21][1]      = EnemyLocation(ENEMY_BUBBLE_BLUE,        LocType::ABOVE_GROUND);
    }
    if (Dungeon::FireTemple.IsVanilla()) {
        enemyLocations[4][0][0][0]       = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[4][0][0][4]       = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[4][0][1][1]       = EnemyLocation(ENEMY_BUBBLE_FIRE,        LocType::ABOVE_GROUND);
        enemyLocations[4][0][1][3]       = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[4][0][1][5]       = EnemyLocation(ENEMY_BUBBLE_FIRE,        LocType::ABOVE_GROUND);
        enemyLocations[4][0][1][6]       = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[4][0][1][8]       = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[4][0][1][11]      = EnemyLocation(ENEMY_BUBBLE_FIRE,        LocType::ABOVE_GROUND);
        enemyLocations[4][0][1][12]      = EnemyLocation(ENEMY_BUBBLE_FIRE,        LocType::ABOVE_GROUND);
        enemyLocations[4][0][1][13]      = EnemyLocation(ENEMY_BUBBLE_FIRE,        LocType::ABOVE_GROUND);
        enemyLocations[4][0][1][14]      = EnemyLocation(ENEMY_BUBBLE_FIRE,        LocType::ABOVE_GROUND);
        enemyLocations[4][0][1][15]      = EnemyLocation(ENEMY_BUBBLE_FIRE,        LocType::ABOVE_GROUND);
        enemyLocations[4][0][1][16]      = EnemyLocation(ENEMY_BUBBLE_FIRE,        LocType::ABOVE_GROUND);
        enemyLocations[4][0][1][17]      = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[4][0][1][22]      = EnemyLocation(ENEMY_BUBBLE_FIRE,        LocType::ABOVE_GROUND);
        enemyLocations[4][0][3][0]       = EnemyLocation(ENEMY_FLARE_DANCER,       LocType::ABOVE_GROUND);
        enemyLocations[4][0][4][0]       = EnemyLocation(ENEMY_TORCH_SLUG,         LocType::ABOVE_GROUND);
        enemyLocations[4][0][4][3]       = EnemyLocation(ENEMY_TORCH_SLUG,         LocType::ABOVE_GROUND);
        enemyLocations[4][0][5][4]       = EnemyLocation(ENEMY_TORCH_SLUG,         LocType::ABOVE_GROUND);
        enemyLocations[4][0][5][6]       = EnemyLocation(ENEMY_TORCH_SLUG,         LocType::ABOVE_GROUND);
        enemyLocations[4][0][5][11]      = EnemyLocation(ENEMY_TORCH_SLUG,         LocType::ABOVE_GROUND);
        enemyLocations[4][0][10][14]     = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[4][0][10][25]     = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[4][0][10][44]     = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[4][0][13][2]      = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[4][0][13][8]      = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[4][0][13][9]      = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[4][0][14][0]      = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[4][0][14][1]      = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[4][0][14][6]      = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_VOID);
        enemyLocations[4][0][14][7]      = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_VOID);
        enemyLocations[4][0][15][0]      = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[4][0][15][1]      = EnemyLocation(ENEMY_TORCH_SLUG,         LocType::ABOVE_GROUND);
        enemyLocations[4][0][15][2]      = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[4][0][15][3]      = EnemyLocation(ENEMY_TORCH_SLUG,         LocType::ABOVE_GROUND);
        enemyLocations[4][0][15][5]      = EnemyLocation(ENEMY_TORCH_SLUG,         LocType::ABOVE_GROUND);
        enemyLocations[4][0][15][6]      = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[4][0][15][7]      = EnemyLocation(ENEMY_TORCH_SLUG,         LocType::ABOVE_GROUND);
        enemyLocations[4][0][16][0]      = EnemyLocation(ENEMY_BUBBLE_FIRE,        LocType::ABOVE_GROUND);
        enemyLocations[4][0][16][1]      = EnemyLocation(ENEMY_BUBBLE_FIRE,        LocType::ABOVE_GROUND);
        enemyLocations[4][0][16][2]      = EnemyLocation(ENEMY_BUBBLE_FIRE,        LocType::ABOVE_GROUND);
        enemyLocations[4][0][16][3]      = EnemyLocation(ENEMY_BUBBLE_FIRE,        LocType::ABOVE_GROUND);
        enemyLocations[4][0][16][4]      = EnemyLocation(ENEMY_BUBBLE_FIRE,        LocType::ABOVE_GROUND);
        enemyLocations[4][0][18][0]      = EnemyLocation(ENEMY_LIKE_LIKE,          LocType::ABOVE_GROUND);
        enemyLocations[4][0][18][1]      = EnemyLocation(ENEMY_FLYING_FLOOR_TILE,  LocType::ABOVE_GROUND);
        enemyLocations[4][0][18][2]      = EnemyLocation(ENEMY_FLYING_FLOOR_TILE,  LocType::ABOVE_GROUND);
        enemyLocations[4][0][18][3]      = EnemyLocation(ENEMY_FLYING_FLOOR_TILE,  LocType::ABOVE_GROUND);
        enemyLocations[4][0][18][4]      = EnemyLocation(ENEMY_FLYING_FLOOR_TILE,  LocType::ABOVE_GROUND);
        enemyLocations[4][0][18][5]      = EnemyLocation(ENEMY_FLYING_FLOOR_TILE,  LocType::ABOVE_GROUND);
        enemyLocations[4][0][19][0]      = EnemyLocation(ENEMY_LIKE_LIKE,          LocType::ABOVE_GROUND);
        enemyLocations[4][0][19][1]      = EnemyLocation(ENEMY_FLYING_FLOOR_TILE,  LocType::ABOVE_GROUND);
        enemyLocations[4][0][19][2]      = EnemyLocation(ENEMY_FLYING_FLOOR_TILE,  LocType::ABOVE_GROUND);
        enemyLocations[4][0][19][3]      = EnemyLocation(ENEMY_FLYING_FLOOR_TILE,  LocType::ABOVE_GROUND);
        enemyLocations[4][0][19][4]      = EnemyLocation(ENEMY_FLYING_FLOOR_TILE,  LocType::ABOVE_GROUND);
        enemyLocations[4][0][19][5]      = EnemyLocation(ENEMY_FLYING_FLOOR_TILE,  LocType::ABOVE_GROUND);
        enemyLocations[4][0][19][6]      = EnemyLocation(ENEMY_FLYING_FLOOR_TILE,  LocType::ABOVE_GROUND);
        enemyLocations[4][0][19][7]      = EnemyLocation(ENEMY_FLYING_FLOOR_TILE,  LocType::ABOVE_GROUND);
        enemyLocations[4][0][19][8]      = EnemyLocation(ENEMY_FLYING_FLOOR_TILE,  LocType::ABOVE_GROUND);
        enemyLocations[4][0][21][0]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[4][0][21][1]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[4][0][21][3]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[4][0][21][4]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[4][0][24][0]      = EnemyLocation(ENEMY_FLARE_DANCER,       LocType::ABOVE_GROUND);
    }
    if (Dungeon::WaterTemple.IsVanilla()) {
        // Idk why these exist
        // enemyLocations[5][0][0][2]    = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        // enemyLocations[5][0][0][3]    = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[5][0][0][4]       = EnemyLocation(ENEMY_SPIKE,              LocType::UNDERWATER);
        enemyLocations[5][0][0][5]       = EnemyLocation(ENEMY_SPIKE,              LocType::UNDERWATER);
        enemyLocations[5][0][0][12]      = EnemyLocation(ENEMY_TEKTITE_BLUE,       LocType::ABOVE_GROUND);
        enemyLocations[5][0][0][13]      = EnemyLocation(ENEMY_TEKTITE_BLUE,       LocType::ABOVE_GROUND);
        enemyLocations[5][0][2][0]       = EnemyLocation(ENEMY_SHELL_BLADE,        LocType::UNDERWATER);
        enemyLocations[5][0][2][1]       = EnemyLocation(ENEMY_SHELL_BLADE,        LocType::UNDERWATER);
        enemyLocations[5][0][2][2]       = EnemyLocation(ENEMY_SPIKE,              LocType::UNDERWATER);
        enemyLocations[5][0][2][3]       = EnemyLocation(ENEMY_SPIKE,              LocType::UNDERWATER);
        enemyLocations[5][0][2][4]       = EnemyLocation(ENEMY_SPIKE,              LocType::UNDERWATER);
        enemyLocations[5][0][2][5]       = EnemyLocation(ENEMY_SPIKE,              LocType::UNDERWATER);
        enemyLocations[5][0][2][6]       = EnemyLocation(ENEMY_SPIKE,              LocType::UNDERWATER);
        enemyLocations[5][0][3][0]       = EnemyLocation(ENEMY_SHELL_BLADE,        LocType::UNDERWATER);
        enemyLocations[5][0][3][2]       = EnemyLocation(ENEMY_TEKTITE_BLUE,       LocType::ABOVE_GROUND);
        enemyLocations[5][0][3][3]       = EnemyLocation(ENEMY_TEKTITE_BLUE,       LocType::ABOVE_GROUND);
        enemyLocations[5][0][4][1]       = EnemyLocation(ENEMY_STINGER_WATER,      { LocType::ABOVE_GROUND, LocType::UNDERWATER });
        enemyLocations[5][0][4][2]       = EnemyLocation(ENEMY_STINGER_WATER,      { LocType::ABOVE_GROUND, LocType::UNDERWATER });
        enemyLocations[5][0][4][3]       = EnemyLocation(ENEMY_STINGER_WATER,      { LocType::ABOVE_GROUND, LocType::UNDERWATER });
        enemyLocations[5][0][4][4]       = EnemyLocation(ENEMY_STINGER_WATER,      { LocType::ABOVE_GROUND, LocType::UNDERWATER });
        enemyLocations[5][0][5][3]       = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[5][0][5][4]       = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[5][0][6][0]       = EnemyLocation(ENEMY_LIKE_LIKE,          LocType::ABOVE_GROUND);
        enemyLocations[5][0][6][1]       = EnemyLocation(ENEMY_TEKTITE_BLUE,       LocType::ABOVE_WATER);
        enemyLocations[5][0][6][2]       = EnemyLocation(ENEMY_TEKTITE_BLUE,       LocType::ABOVE_WATER);
        enemyLocations[5][0][6][3]       = EnemyLocation(ENEMY_TEKTITE_BLUE,       LocType::ABOVE_GROUND);
        enemyLocations[5][0][6][4]       = EnemyLocation(ENEMY_TEKTITE_BLUE,       LocType::ABOVE_GROUND);
        enemyLocations[5][0][6][5]       = EnemyLocation(ENEMY_TEKTITE_BLUE,       LocType::ABOVE_WATER);
        enemyLocations[5][0][8][2]       = EnemyLocation(ENEMY_SHELL_BLADE,        LocType::UNDERWATER);
        enemyLocations[5][0][8][3]       = EnemyLocation(ENEMY_SHELL_BLADE,        LocType::UNDERWATER);
        enemyLocations[5][0][9][0]       = EnemyLocation(ENEMY_TEKTITE_BLUE,       LocType::ABOVE_GROUND);
        enemyLocations[5][0][10][1]      = EnemyLocation(ENEMY_TEKTITE_BLUE,       LocType::ABOVE_GROUND);
        enemyLocations[5][0][12][0]      = EnemyLocation(ENEMY_SHELL_BLADE,        LocType::UNDERWATER);
        enemyLocations[5][0][12][3]      = EnemyLocation(ENEMY_TEKTITE_BLUE,       LocType::ABOVE_WATER);
        enemyLocations[5][0][12][4]      = EnemyLocation(ENEMY_TEKTITE_BLUE,       LocType::ABOVE_GROUND);
        enemyLocations[5][0][12][5]      = EnemyLocation(ENEMY_TEKTITE_BLUE,       LocType::ABOVE_WATER);
        enemyLocations[5][0][12][6]      = EnemyLocation(ENEMY_TEKTITE_BLUE,       LocType::ABOVE_GROUND);
        enemyLocations[5][0][12][7]      = EnemyLocation(ENEMY_TEKTITE_BLUE,       LocType::ABOVE_WATER);
        enemyLocations[5][0][12][8]      = EnemyLocation(ENEMY_TEKTITE_BLUE,       LocType::ABOVE_WATER);
        enemyLocations[5][0][13][0xFF]   = EnemyLocation(ENEMY_DARK_LINK,          LocType::ABOVE_GROUND);
        enemyLocations[5][0][14][0]      = EnemyLocation(ENEMY_STINGER_WATER,      LocType::UNDERWATER);
        enemyLocations[5][0][14][1]      = EnemyLocation(ENEMY_STINGER_WATER,      LocType::UNDERWATER);
        enemyLocations[5][0][14][2]      = EnemyLocation(ENEMY_STINGER_WATER,      LocType::UNDERWATER);
        enemyLocations[5][0][14][3]      = EnemyLocation(ENEMY_STINGER_WATER,      LocType::UNDERWATER);
        enemyLocations[5][0][14][4]      = EnemyLocation(ENEMY_STINGER_WATER,      LocType::UNDERWATER);
        enemyLocations[5][0][15][0]      = EnemyLocation(ENEMY_TEKTITE_BLUE,       LocType::ABOVE_GROUND);
        enemyLocations[5][0][15][1]      = EnemyLocation(ENEMY_TEKTITE_BLUE,       LocType::ABOVE_GROUND);
        enemyLocations[5][0][18][0]      = EnemyLocation(ENEMY_SHELL_BLADE,        LocType::ABOVE_GROUND);
        enemyLocations[5][0][18][1]      = EnemyLocation(ENEMY_SHELL_BLADE,        LocType::ABOVE_GROUND);
        enemyLocations[5][0][18][2]      = EnemyLocation(ENEMY_SHELL_BLADE,        LocType::ABOVE_GROUND);
        enemyLocations[5][0][19][0]      = EnemyLocation(ENEMY_SPIKE,              LocType::ABOVE_GROUND);
        enemyLocations[5][0][19][1]      = EnemyLocation(ENEMY_SPIKE,              LocType::ABOVE_GROUND);
        enemyLocations[5][0][19][2]      = EnemyLocation(ENEMY_SPIKE,              LocType::ABOVE_GROUND);
        enemyLocations[5][0][19][3]      = EnemyLocation(ENEMY_SPIKE,              LocType::ABOVE_GROUND);
    }
    if (Dungeon::SpiritTemple.IsVanilla()) {
        enemyLocations[6][0][0][0]       = EnemyLocation(ENEMY_ARMOS,              LocType::ABOVE_GROUND);
        enemyLocations[6][0][0][1]       = EnemyLocation(ENEMY_ARMOS,              LocType::ABOVE_GROUND);
        enemyLocations[6][0][0][2]       = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[6][0][0][12]      = EnemyLocation(ENEMY_FLYING_POT,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][0][13]      = EnemyLocation(ENEMY_FLYING_POT,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][1][0]       = EnemyLocation(ENEMY_ARMOS,              LocType::ABOVE_GROUND);
        enemyLocations[6][0][1][1]       = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[6][0][1][2]       = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[6][0][1][3]       = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][1][4]       = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][2][0]       = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_VOID);
        enemyLocations[6][0][2][1]       = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_VOID);
        enemyLocations[6][0][2][2]       = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_VOID);
        enemyLocations[6][0][2][3]       = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_VOID);
        enemyLocations[6][0][2][5]       = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][2][6]       = EnemyLocation(ENEMY_WALLMASTER,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][3][0]       = EnemyLocation(ENEMY_BUBBLE_GREEN,       LocType::ABOVE_VOID);
        enemyLocations[6][0][3][3]       = EnemyLocation(ENEMY_STALFOS,            LocType::ABOVE_GROUND);
        enemyLocations[6][0][3][4]       = EnemyLocation(ENEMY_FLYING_POT,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][3][5]       = EnemyLocation(ENEMY_FLYING_POT,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][4][0]       = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
        enemyLocations[6][0][4][1]       = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
        enemyLocations[6][0][4][2]       = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
        enemyLocations[6][0][4][3]       = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
        enemyLocations[6][0][4][4]       = EnemyLocation(ENEMY_LIZALFOS,           LocType::ABOVE_GROUND);
        enemyLocations[6][0][4][5]       = EnemyLocation(ENEMY_LIZALFOS,           LocType::ABOVE_GROUND);
        enemyLocations[6][0][5][1]       = EnemyLocation(ENEMY_ARMOS,              LocType::ABOVE_GROUND);
        enemyLocations[6][0][5][19]      = EnemyLocation(ENEMY_FLYING_POT,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][5][20]      = EnemyLocation(ENEMY_FLYING_POT,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][8][4]       = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[6][0][8][5]       = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[6][0][8][6]       = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[6][0][10][0]      = EnemyLocation(ENEMY_IRON_KNUCKLE,       LocType::ABOVE_GROUND);
        enemyLocations[6][0][12][0]      = EnemyLocation(ENEMY_LIKE_LIKE,          LocType::ABOVE_GROUND);
        enemyLocations[6][0][14][0]      = EnemyLocation(ENEMY_WOLFOS,             LocType::ABOVE_GROUND);
        enemyLocations[6][0][15][0]      = EnemyLocation(ENEMY_WALLMASTER,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][15][1]      = EnemyLocation(ENEMY_FLOORMASTER,        LocType::ABOVE_GROUND);
        enemyLocations[6][0][15][2]      = EnemyLocation(ENEMY_LIKE_LIKE,          LocType::ABOVE_GROUND);
        enemyLocations[6][0][15][11]     = EnemyLocation(ENEMY_FLYING_POT,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][15][12]     = EnemyLocation(ENEMY_FLYING_POT,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][16][0]      = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[6][0][17][0]      = EnemyLocation(ENEMY_ANUBIS,             LocType::ABOVE_GROUND);
        enemyLocations[6][0][17][1]      = EnemyLocation(ENEMY_ANUBIS,             LocType::ABOVE_GROUND);
        enemyLocations[6][0][17][2]      = EnemyLocation(ENEMY_ANUBIS,             LocType::ABOVE_GROUND);
        enemyLocations[6][0][17][3]      = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[6][0][18][0]      = EnemyLocation(ENEMY_ARMOS,              LocType::ABOVE_GROUND);
        enemyLocations[6][0][18][1]      = EnemyLocation(ENEMY_ARMOS,              LocType::ABOVE_GROUND);
        enemyLocations[6][0][18][2]      = EnemyLocation(ENEMY_ARMOS,              LocType::ABOVE_GROUND);
        // Leave one armos so we can press the switch
        // enemyLocations[6][0][18][3]   = EnemyLocation(ENEMY_ARMOS,              LocType::ABOVE_GROUND);
        enemyLocations[6][0][20][0]      = EnemyLocation(ENEMY_IRON_KNUCKLE,       LocType::ABOVE_GROUND);
        enemyLocations[6][0][22][10]     = EnemyLocation(ENEMY_TORCH_SLUG,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][22][11]     = EnemyLocation(ENEMY_TORCH_SLUG,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][22][12]     = EnemyLocation(ENEMY_TORCH_SLUG,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][22][13]     = EnemyLocation(ENEMY_TORCH_SLUG,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][23][1]      = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
        enemyLocations[6][0][23][4]      = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[6][0][23][5]      = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[6][0][23][6]      = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[6][0][23][7]      = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[6][0][25][4]      = EnemyLocation(ENEMY_FLYING_POT,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][25][5]      = EnemyLocation(ENEMY_FLYING_POT,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][25][6]      = EnemyLocation(ENEMY_FLYING_POT,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][25][7]      = EnemyLocation(ENEMY_FLYING_POT,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][25][8]      = EnemyLocation(ENEMY_FLYING_POT,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][25][9]      = EnemyLocation(ENEMY_FLYING_POT,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][26][0]      = EnemyLocation(ENEMY_BUBBLE_WHITE,       LocType::ABOVE_GROUND);
        enemyLocations[6][0][26][1]      = EnemyLocation(ENEMY_BUBBLE_WHITE,       LocType::ABOVE_GROUND);
        enemyLocations[6][0][26][2]      = EnemyLocation(ENEMY_BUBBLE_WHITE,       LocType::ABOVE_GROUND);
        enemyLocations[6][0][26][3]      = EnemyLocation(ENEMY_LIZALFOS,           LocType::ABOVE_GROUND);
        enemyLocations[6][0][26][4]      = EnemyLocation(ENEMY_LIZALFOS,           LocType::ABOVE_GROUND);
        enemyLocations[6][0][27][0]      = EnemyLocation(ENEMY_ANUBIS,             LocType::ABOVE_GROUND);
    }
    if (Dungeon::ShadowTemple.IsVanilla()) {
        enemyLocations[7][0][0][5]       = EnemyLocation(ENEMY_FLYING_POT,         LocType::ABOVE_GROUND);
        enemyLocations[7][0][1][0]       = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[7][0][1][1]       = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[7][0][1][2]       = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
        enemyLocations[7][0][4][0]       = EnemyLocation(ENEMY_DEAD_HAND_HAND,     LocType::ABOVE_GROUND);
        enemyLocations[7][0][4][1]       = EnemyLocation(ENEMY_DEAD_HAND_HAND,     LocType::ABOVE_GROUND);
        enemyLocations[7][0][4][2]       = EnemyLocation(ENEMY_DEAD_HAND_HAND,     LocType::ABOVE_GROUND);
        enemyLocations[7][0][4][3]       = EnemyLocation(ENEMY_DEAD_HAND_HAND,     LocType::ABOVE_GROUND);
        enemyLocations[7][0][4][4]       = EnemyLocation(ENEMY_DEAD_HAND_HAND,     LocType::ABOVE_GROUND);
        // Leave Dead Hand and one of its hands to lure it out.
        // enemyLocations[7][0][4][5]    = EnemyLocation(ENEMY_DEAD_HAND_HAND,     LocType::ABOVE_GROUND);
        // enemyLocations[7][0][4][6]    = EnemyLocation(ENEMY_DEAD_HAND,          LocType::ABOVE_GROUND);
        enemyLocations[7][0][5][0]       = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[7][0][7][0]       = EnemyLocation(ENEMY_GIBDO,              LocType::ABOVE_GROUND);
        enemyLocations[7][0][7][1]       = EnemyLocation(ENEMY_GIBDO,              LocType::ABOVE_GROUND);
        enemyLocations[7][0][8][0]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[7][0][8][1]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[7][0][8][2]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[7][0][8][3]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[7][0][9][1]       = EnemyLocation(ENEMY_BUBBLE_FIRE,        LocType::ABOVE_VOID);
        enemyLocations[7][0][9][2]       = EnemyLocation(ENEMY_WALLMASTER,         LocType::ABOVE_GROUND);
        enemyLocations[7][0][9][5]       = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[7][0][9][12]      = EnemyLocation(ENEMY_STALFOS,            LocType::ABOVE_GROUND);
        enemyLocations[7][0][11][0]      = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
        enemyLocations[7][0][11][1]      = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
        enemyLocations[7][0][13][0]      = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
        enemyLocations[7][0][13][1]      = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
        enemyLocations[7][0][14][0]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[7][0][14][1]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[7][0][14][2]      = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[7][0][14][3]      = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[7][0][15][0]      = EnemyLocation(ENEMY_FLOORMASTER,        LocType::ABOVE_GROUND);
        enemyLocations[7][0][15][1]      = EnemyLocation(ENEMY_FLOORMASTER,        LocType::ABOVE_GROUND);
        enemyLocations[7][0][16][0]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[7][0][16][1]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[7][0][16][2]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[7][0][16][3]      = EnemyLocation(ENEMY_LIKE_LIKE,          LocType::ABOVE_GROUND);
        enemyLocations[7][0][17][0]      = EnemyLocation(ENEMY_FLOORMASTER,        LocType::ABOVE_GROUND);
        enemyLocations[7][0][18][0]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[7][0][19][0]      = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
        enemyLocations[7][0][19][1]      = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
        enemyLocations[7][0][20][0]      = EnemyLocation(ENEMY_GIBDO,              LocType::ABOVE_GROUND);
        enemyLocations[7][0][20][1]      = EnemyLocation(ENEMY_GIBDO,              LocType::ABOVE_GROUND);
        enemyLocations[7][0][20][4]      = EnemyLocation(ENEMY_FLYING_POT,         LocType::ABOVE_GROUND);
        enemyLocations[7][0][20][5]      = EnemyLocation(ENEMY_FLYING_POT,         LocType::ABOVE_GROUND);
        enemyLocations[7][0][21][13]     = EnemyLocation(ENEMY_STALFOS,            LocType::ABOVE_GROUND);
        enemyLocations[7][0][21][14]     = EnemyLocation(ENEMY_STALFOS,            LocType::ABOVE_GROUND);
    }
    if (Dungeon::BottomOfTheWell.IsVanilla()) {
        enemyLocations[8][0][0][0]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[8][0][0][1]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[8][0][0][2]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[8][0][0][3]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[8][0][0][4]       = EnemyLocation(ENEMY_WALLMASTER,         LocType::ABOVE_GROUND);
        enemyLocations[8][0][0][5]       = EnemyLocation(ENEMY_LIKE_LIKE,          LocType::ABOVE_GROUND);
        enemyLocations[8][0][0][33]      = EnemyLocation(ENEMY_BUBBLE_GREEN,       LocType::ABOVE_GROUND);
        enemyLocations[8][0][1][13]      = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
        enemyLocations[8][0][1][14]      = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
        enemyLocations[8][0][2][0]       = EnemyLocation(ENEMY_GIBDO,              LocType::ABOVE_GROUND);
        enemyLocations[8][0][3][0]       = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[8][0][3][1]       = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[8][0][3][2]       = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[8][0][3][4]       = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[8][0][4][0]       = EnemyLocation(ENEMY_DEAD_HAND_HAND,     LocType::ABOVE_GROUND);
        enemyLocations[8][0][4][1]       = EnemyLocation(ENEMY_DEAD_HAND_HAND,     LocType::ABOVE_GROUND);
        enemyLocations[8][0][4][2]       = EnemyLocation(ENEMY_DEAD_HAND_HAND,     LocType::ABOVE_GROUND);
        // Leave Dead Hand and one of its hands to lure it out.
        // enemyLocations[8][0][4][3]    = EnemyLocation(ENEMY_DEAD_HAND_HAND,     LocType::ABOVE_GROUND);
        // enemyLocations[8][0][4][4]    = EnemyLocation(ENEMY_DEAD_HAND,          LocType::ABOVE_GROUND);
        enemyLocations[8][0][5][0]       = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[8][0][5][1]       = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[8][0][5][2]       = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[8][0][5][3]       = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[8][0][6][0]       = EnemyLocation(ENEMY_DEKU_BABA_SMALL,    LocType::ABOVE_GROUND);
        enemyLocations[8][0][6][2]       = EnemyLocation(ENEMY_FLYING_POT,         LocType::ABOVE_GROUND);
        enemyLocations[8][0][6][3]       = EnemyLocation(ENEMY_FLYING_POT,         LocType::ABOVE_GROUND);
        enemyLocations[8][0][6][4]       = EnemyLocation(ENEMY_FLYING_POT,         LocType::ABOVE_GROUND);
    }
    if (Dungeon::IceCavern.IsVanilla()) {
        enemyLocations[9][0][1][1]       = EnemyLocation(ENEMY_FREEZARD,           LocType::ABOVE_GROUND);
        enemyLocations[9][0][1][10]      = EnemyLocation(ENEMY_FREEZARD,           LocType::ABOVE_GROUND);
        enemyLocations[9][0][1][11]      = EnemyLocation(ENEMY_FREEZARD,           LocType::ABOVE_GROUND);
        enemyLocations[9][0][1][12]      = EnemyLocation(ENEMY_FREEZARD,           LocType::ABOVE_GROUND);
        enemyLocations[9][0][3][11]      = EnemyLocation(ENEMY_FLYING_POT,         LocType::ABOVE_GROUND);
        enemyLocations[9][0][5][3]       = EnemyLocation(ENEMY_KEESE_ICE,          LocType::ABOVE_GROUND);
        enemyLocations[9][0][5][4]       = EnemyLocation(ENEMY_KEESE_ICE,          LocType::ABOVE_GROUND);
        enemyLocations[9][0][5][5]       = EnemyLocation(ENEMY_KEESE_ICE,          LocType::ABOVE_GROUND);
        enemyLocations[9][0][6][17]      = EnemyLocation(ENEMY_FREEZARD,           LocType::ABOVE_GROUND);
        enemyLocations[9][0][6][18]      = EnemyLocation(ENEMY_FREEZARD,           LocType::ABOVE_GROUND);
        enemyLocations[9][0][7][0]       = EnemyLocation(ENEMY_WOLFOS,             LocType::ABOVE_GROUND);
        enemyLocations[9][0][8][8]       = EnemyLocation(ENEMY_FREEZARD,           LocType::ABOVE_GROUND);
        enemyLocations[9][0][9][0]       = EnemyLocation(ENEMY_KEESE_ICE,          LocType::ABOVE_GROUND);
        enemyLocations[9][0][9][1]       = EnemyLocation(ENEMY_KEESE_ICE,          LocType::ABOVE_GROUND);
        enemyLocations[9][0][9][2]       = EnemyLocation(ENEMY_KEESE_ICE,          LocType::ABOVE_GROUND);
        enemyLocations[9][0][9][4]       = EnemyLocation(ENEMY_FREEZARD,           LocType::ABOVE_GROUND);
        enemyLocations[9][0][9][13]      = EnemyLocation(ENEMY_FREEZARD,           LocType::ABOVE_GROUND);
        enemyLocations[9][0][9][14]      = EnemyLocation(ENEMY_FREEZARD,           LocType::ABOVE_GROUND);
        enemyLocations[9][0][11][0]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[9][0][11][1]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[9][0][11][2]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
    }
    if (Dungeon::GerudoTrainingGrounds.IsVanilla()) {
        enemyLocations[11][0][1][0]      = EnemyLocation(ENEMY_STALFOS,            LocType::ABOVE_GROUND);
        enemyLocations[11][0][1][1]      = EnemyLocation(ENEMY_STALFOS,            LocType::ABOVE_GROUND);
        // Don't randomize out of bounds wallmaster, it exists only to prevent setting the clear flag.
        // enemyLocations[11][0][2][4]   = EnemyLocation(ENEMY_WALLMASTER,         LocType::ABOVE_GROUND);
        enemyLocations[11][0][2][5]      = EnemyLocation(ENEMY_WALLMASTER,         LocType::ABOVE_GROUND);
        enemyLocations[11][0][3][1]      = EnemyLocation(ENEMY_WOLFOS,             LocType::ABOVE_GROUND);
        enemyLocations[11][0][3][2]      = EnemyLocation(ENEMY_WOLFOS,             LocType::ABOVE_GROUND);
        enemyLocations[11][0][3][4]      = EnemyLocation(ENEMY_WOLFOS,             LocType::ABOVE_GROUND);
        enemyLocations[11][0][3][5]      = EnemyLocation(ENEMY_WOLFOS,             LocType::ABOVE_GROUND);
        enemyLocations[11][0][5][1]      = EnemyLocation(ENEMY_TORCH_SLUG,         LocType::ABOVE_GROUND);
        enemyLocations[11][0][5][2]      = EnemyLocation(ENEMY_TORCH_SLUG,         LocType::ABOVE_GROUND);
        enemyLocations[11][0][5][3]      = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[11][0][5][4]      = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[11][0][6][2]      = EnemyLocation(ENEMY_BUBBLE_FIRE,        LocType::ABOVE_VOID);
        enemyLocations[11][0][6][3]      = EnemyLocation(ENEMY_BUBBLE_FIRE,        LocType::ABOVE_VOID);
        enemyLocations[11][0][7][0]      = EnemyLocation(ENEMY_DINOLFOS,           LocType::ABOVE_GROUND);
        enemyLocations[11][0][7][1]      = EnemyLocation(ENEMY_DINOLFOS,           LocType::ABOVE_GROUND);
        enemyLocations[11][0][7][13]     = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[11][0][9][4]      = EnemyLocation(ENEMY_SHELL_BLADE,        LocType::UNDERWATER);
        enemyLocations[11][0][9][5]      = EnemyLocation(ENEMY_SHELL_BLADE,        LocType::UNDERWATER);
        enemyLocations[11][0][9][6]      = EnemyLocation(ENEMY_SHELL_BLADE,        LocType::UNDERWATER);
        enemyLocations[11][0][9][7]      = EnemyLocation(ENEMY_SHELL_BLADE,        LocType::UNDERWATER);
        enemyLocations[11][0][10][0]     = EnemyLocation(ENEMY_LIKE_LIKE,          LocType::ABOVE_GROUND);
        enemyLocations[11][0][10][1]     = EnemyLocation(ENEMY_LIKE_LIKE,          LocType::ABOVE_GROUND);
        enemyLocations[11][0][10][2]     = EnemyLocation(ENEMY_LIKE_LIKE,          LocType::ABOVE_GROUND);
    }
    if (Dungeon::GanonsCastle.IsVanilla()) {
        enemyLocations[13][0][0][0]      = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[13][0][0][1]      = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[13][0][2][0]      = EnemyLocation(ENEMY_FREEZARD,           LocType::ABOVE_GROUND);
        enemyLocations[13][0][2][1]      = EnemyLocation(ENEMY_FREEZARD,           LocType::ABOVE_GROUND);
        // Don't randomize out of bounds wallmaster, it exists only to manage the clear flag.
        // enemyLocations[13][0][3][6]   = EnemyLocation(ENEMY_WALLMASTER,         LocType::ABOVE_GROUND);
        enemyLocations[13][0][5][0]      = EnemyLocation(ENEMY_WOLFOS,             LocType::ABOVE_GROUND);
        enemyLocations[13][0][6][1]      = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        // Don't randomize out of bounds wallmaster, it exists only to manage the clear flag.
        // enemyLocations[13][0][8][11]  = EnemyLocation(ENEMY_WALLMASTER,         LocType::ABOVE_GROUND);
        enemyLocations[13][0][9][6]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[13][0][9][7]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[13][0][9][8]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[13][0][9][9]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[13][0][10][1]     = EnemyLocation(ENEMY_WALLMASTER,         LocType::ABOVE_GROUND);
        enemyLocations[13][0][12][0]     = EnemyLocation(ENEMY_BUBBLE_GREEN,       LocType::ABOVE_VOID);
        enemyLocations[13][0][12][3]     = EnemyLocation(ENEMY_LIKE_LIKE,          LocType::ABOVE_GROUND);
        enemyLocations[13][0][14][3]     = EnemyLocation(ENEMY_TORCH_SLUG,         LocType::ABOVE_GROUND);
        enemyLocations[13][0][14][4]     = EnemyLocation(ENEMY_BUBBLE_FIRE,        LocType::ABOVE_VOID);
        enemyLocations[13][0][14][5]     = EnemyLocation(ENEMY_BUBBLE_FIRE,        LocType::ABOVE_VOID);
        enemyLocations[13][0][14][6]     = EnemyLocation(ENEMY_BUBBLE_FIRE,        LocType::ABOVE_VOID);
        enemyLocations[13][0][14][7]     = EnemyLocation(ENEMY_BUBBLE_FIRE,        LocType::ABOVE_VOID);
        enemyLocations[13][0][17][10]    = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[13][0][18][6]     = EnemyLocation(ENEMY_TORCH_SLUG,         LocType::ABOVE_GROUND);
        enemyLocations[13][0][18][7]     = EnemyLocation(ENEMY_TORCH_SLUG,         LocType::ABOVE_GROUND);
        enemyLocations[13][0][18][18]    = EnemyLocation(ENEMY_WALLMASTER,         LocType::ABOVE_GROUND);
        enemyLocations[13][0][18][20]    = EnemyLocation(ENEMY_WALLMASTER,         LocType::ABOVE_GROUND);
        enemyLocations[13][0][18][22]    = EnemyLocation(ENEMY_WALLMASTER,         LocType::ABOVE_GROUND);
    }

    // MQ dungeons
    if (Dungeon::DekuTree.IsMQ()) {
        enemyLocations[0][0][0][0]       = EnemyLocation(ENEMY_DEKU_BABA_WITHERED, LocType::ABOVE_GROUND);
        enemyLocations[0][0][0][1]       = EnemyLocation(ENEMY_DEKU_BABA_WITHERED, LocType::ABOVE_GROUND);
        enemyLocations[0][0][0][2]       = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[0][0][0][3]       = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[0][0][0][4]       = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
        enemyLocations[0][0][0][10]      = EnemyLocation(ENEMY_DEKU_BABA_SMALL,    LocType::ABOVE_GROUND);
        enemyLocations[0][0][0][11]      = EnemyLocation(ENEMY_DEKU_BABA_SMALL,    LocType::ABOVE_GROUND);
        enemyLocations[0][0][0][22]      = EnemyLocation(ENEMY_GOHMA_LARVA,        LocType::ABOVE_GROUND);
        enemyLocations[0][0][0][23]      = EnemyLocation(ENEMY_GOHMA_LARVA,        LocType::ABOVE_GROUND);
        enemyLocations[0][0][1][3]       = EnemyLocation(ENEMY_DEKU_BABA_BIG,      LocType::ABOVE_GROUND);
        enemyLocations[0][0][1][9]       = EnemyLocation(ENEMY_GOHMA_LARVA,        LocType::ABOVE_GROUND);
        enemyLocations[0][0][1][10]      = EnemyLocation(ENEMY_GOHMA_LARVA,        LocType::ABOVE_GROUND);
        enemyLocations[0][0][2][0]       = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
        enemyLocations[0][0][2][1]       = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
        enemyLocations[0][0][2][2]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[0][0][2][13]      = EnemyLocation(ENEMY_GOHMA_LARVA,        LocType::ABOVE_GROUND);
        enemyLocations[0][0][2][14]      = EnemyLocation(ENEMY_GOHMA_LARVA,        LocType::ABOVE_GROUND);
        enemyLocations[0][0][3][0]       = EnemyLocation(ENEMY_DEKU_BABA_WITHERED, LocType::ABOVE_GROUND);
        enemyLocations[0][0][3][6]       = EnemyLocation(ENEMY_DEKU_BABA_SMALL,    LocType::ABOVE_GROUND);
        enemyLocations[0][0][3][7]       = EnemyLocation(ENEMY_DEKU_BABA_SMALL,    LocType::ABOVE_GROUND);
        enemyLocations[0][0][3][8]       = EnemyLocation(ENEMY_DEKU_BABA_BIG,      LocType::ABOVE_GROUND);
        enemyLocations[0][0][4][4]       = EnemyLocation(ENEMY_MAD_SCRUB,          LocType::ABOVE_GROUND);
        enemyLocations[0][0][4][5]       = EnemyLocation(ENEMY_GOHMA_LARVA,        LocType::ABOVE_GROUND);
        enemyLocations[0][0][4][6]       = EnemyLocation(ENEMY_GOHMA_LARVA,        LocType::ABOVE_GROUND);
        enemyLocations[0][0][4][7]       = EnemyLocation(ENEMY_GOHMA_LARVA,        LocType::ABOVE_GROUND);
        enemyLocations[0][0][5][0]       = EnemyLocation(ENEMY_DEKU_BABA_WITHERED, LocType::ABOVE_GROUND);
        enemyLocations[0][0][5][1]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[0][0][5][7]       = EnemyLocation(ENEMY_GOHMA_LARVA,        LocType::ABOVE_WATER);
        enemyLocations[0][0][6][0]       = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[0][0][6][3]       = EnemyLocation(ENEMY_MAD_SCRUB,          LocType::ABOVE_GROUND);
        enemyLocations[0][0][6][4]       = EnemyLocation(ENEMY_GOHMA_LARVA,        LocType::ABOVE_GROUND);
        enemyLocations[0][0][6][5]       = EnemyLocation(ENEMY_GOHMA_LARVA,        LocType::ABOVE_GROUND);
        enemyLocations[0][0][6][6]       = EnemyLocation(ENEMY_GOHMA_LARVA,        LocType::ABOVE_GROUND);
        enemyLocations[0][0][6][7]       = EnemyLocation(ENEMY_GOHMA_LARVA,        LocType::ABOVE_GROUND);
        enemyLocations[0][0][6][8]       = EnemyLocation(ENEMY_GOHMA_LARVA,        LocType::ABOVE_GROUND);
        enemyLocations[0][0][6][9]       = EnemyLocation(ENEMY_GOHMA_LARVA,        LocType::ABOVE_GROUND);
        enemyLocations[0][0][6][10]      = EnemyLocation(ENEMY_GOHMA_LARVA,        LocType::ABOVE_GROUND);
        enemyLocations[0][0][6][11]      = EnemyLocation(ENEMY_GOHMA_LARVA,        LocType::ABOVE_GROUND);
        enemyLocations[0][0][7][0]       = EnemyLocation(ENEMY_DEKU_BABA_WITHERED, LocType::ABOVE_GROUND);
        enemyLocations[0][0][7][1]       = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[0][0][7][2]       = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[0][0][7][3]       = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[0][0][7][4]       = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[0][0][7][6]       = EnemyLocation(ENEMY_DEKU_BABA_SMALL,    LocType::ABOVE_GROUND);
        enemyLocations[0][0][7][7]       = EnemyLocation(ENEMY_DEKU_BABA_SMALL,    LocType::ABOVE_GROUND);
        enemyLocations[0][0][8][2]       = EnemyLocation(ENEMY_DEKU_BABA_BIG,      LocType::ABOVE_GROUND);
        enemyLocations[0][0][8][7]       = EnemyLocation(ENEMY_GOHMA_LARVA,        LocType::ABOVE_GROUND);
        enemyLocations[0][0][8][8]       = EnemyLocation(ENEMY_GOHMA_LARVA,        LocType::ABOVE_GROUND);
        enemyLocations[0][0][8][9]       = EnemyLocation(ENEMY_GOHMA_LARVA,        LocType::ABOVE_GROUND);
        enemyLocations[0][0][8][10]      = EnemyLocation(ENEMY_GOHMA_LARVA,        LocType::ABOVE_GROUND);
        enemyLocations[0][0][9][3]       = EnemyLocation(ENEMY_HINT_DEKU_SCRUB,    LocType::ABOVE_GROUND);
        enemyLocations[0][0][9][4]       = EnemyLocation(ENEMY_HINT_DEKU_SCRUB,    LocType::ABOVE_GROUND);
        enemyLocations[0][0][9][5]       = EnemyLocation(ENEMY_HINT_DEKU_SCRUB,    LocType::ABOVE_GROUND);
        enemyLocations[0][0][10][4]      = EnemyLocation(ENEMY_DEKU_BABA_SMALL,    LocType::ABOVE_GROUND);
        enemyLocations[0][0][10][6]      = EnemyLocation(ENEMY_GOHMA_LARVA,        LocType::ABOVE_GROUND);
        enemyLocations[0][0][10][7]      = EnemyLocation(ENEMY_GOHMA_LARVA,        LocType::ABOVE_GROUND);
        enemyLocations[0][0][10][8]      = EnemyLocation(ENEMY_GOHMA_LARVA,        LocType::ABOVE_GROUND);
        enemyLocations[0][0][10][9]      = EnemyLocation(ENEMY_GOHMA_LARVA,        LocType::ABOVE_GROUND);
        enemyLocations[0][0][10][10]     = EnemyLocation(ENEMY_GOHMA_LARVA,        LocType::ABOVE_GROUND);
        enemyLocations[0][0][10][11]     = EnemyLocation(ENEMY_GOHMA_LARVA,        LocType::ABOVE_GROUND);
    }
    if (Dungeon::DodongosCavern.IsMQ()) {
        enemyLocations[1][0][1][2]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[1][0][1][4]       = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[1][0][1][5]       = EnemyLocation(ENEMY_DODONGO_BABY,       LocType::ABOVE_GROUND);
        enemyLocations[1][0][1][6]       = EnemyLocation(ENEMY_DODONGO_BABY,       LocType::ABOVE_GROUND);
        enemyLocations[1][0][2][1]       = EnemyLocation(ENEMY_DEKU_BABA_WITHERED, LocType::ABOVE_GROUND);
        enemyLocations[1][0][2][2]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[1][0][2][3]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[1][0][2][7]       = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[1][0][2][8]       = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[1][0][3][1]       = EnemyLocation(ENEMY_LIZALFOS,           LocType::ABOVE_GROUND);
        enemyLocations[1][0][3][2]       = EnemyLocation(ENEMY_LIZALFOS,           LocType::ABOVE_GROUND);
        enemyLocations[1][0][3][3]       = EnemyLocation(ENEMY_LIZALFOS,           LocType::ABOVE_GROUND);
        enemyLocations[1][0][3][4]       = EnemyLocation(ENEMY_LIZALFOS,           LocType::ABOVE_GROUND);
        enemyLocations[1][0][4][0]       = EnemyLocation(ENEMY_POE,                LocType::ABOVE_GROUND);
        enemyLocations[1][0][4][1]       = EnemyLocation(ENEMY_POE,                LocType::ABOVE_GROUND);
        enemyLocations[1][0][4][2]       = EnemyLocation(ENEMY_POE,                LocType::ABOVE_GROUND);
        enemyLocations[1][0][5][4]       = EnemyLocation(ENEMY_DODONGO,            LocType::ABOVE_GROUND);
        enemyLocations[1][0][5][5]       = EnemyLocation(ENEMY_DODONGO,            LocType::ABOVE_GROUND);
        enemyLocations[1][0][5][6]       = EnemyLocation(ENEMY_DODONGO,            LocType::ABOVE_GROUND);
        enemyLocations[1][0][6][1]       = EnemyLocation(ENEMY_GOHMA_LARVA,        LocType::ABOVE_GROUND);
        enemyLocations[1][0][6][2]       = EnemyLocation(ENEMY_GOHMA_LARVA,        LocType::ABOVE_GROUND);
        enemyLocations[1][0][6][3]       = EnemyLocation(ENEMY_GOHMA_LARVA,        LocType::ABOVE_GROUND);
        enemyLocations[1][0][6][4]       = EnemyLocation(ENEMY_GOHMA_LARVA,        LocType::ABOVE_GROUND);
        enemyLocations[1][0][6][5]       = EnemyLocation(ENEMY_GOHMA_LARVA,        LocType::ABOVE_GROUND);
        enemyLocations[1][0][7][0]       = EnemyLocation(ENEMY_DODONGO_BABY,       LocType::ABOVE_GROUND);
        enemyLocations[1][0][7][1]       = EnemyLocation(ENEMY_DODONGO_BABY,       LocType::ABOVE_GROUND);
        enemyLocations[1][0][8][0]       = EnemyLocation(ENEMY_ARMOS,              LocType::ABOVE_GROUND);
        enemyLocations[1][0][8][1]       = EnemyLocation(ENEMY_ARMOS,              LocType::ABOVE_GROUND);
        enemyLocations[1][0][8][2]       = EnemyLocation(ENEMY_ARMOS,              LocType::ABOVE_GROUND);
        enemyLocations[1][0][8][3]       = EnemyLocation(ENEMY_ARMOS,              LocType::ABOVE_GROUND);
        enemyLocations[1][0][8][4]       = EnemyLocation(ENEMY_ARMOS,              LocType::ABOVE_GROUND);
        enemyLocations[1][0][8][5]       = EnemyLocation(ENEMY_ARMOS,              LocType::ABOVE_GROUND);
        enemyLocations[1][0][8][6]       = EnemyLocation(ENEMY_ARMOS,              LocType::ABOVE_GROUND);
        enemyLocations[1][0][8][13]      = EnemyLocation(ENEMY_DODONGO_BABY,       LocType::ABOVE_GROUND);
        enemyLocations[1][0][8][14]      = EnemyLocation(ENEMY_DODONGO_BABY,       LocType::ABOVE_GROUND);
        enemyLocations[1][0][8][15]      = EnemyLocation(ENEMY_LIZALFOS,           LocType::ABOVE_GROUND);
        enemyLocations[1][0][10][0]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[1][0][10][1]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[1][0][10][2]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[1][0][10][3]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[1][0][10][4]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[1][0][10][5]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[1][0][10][8]      = EnemyLocation(ENEMY_DODONGO_BABY,       LocType::ABOVE_GROUND);
        enemyLocations[1][0][10][9]      = EnemyLocation(ENEMY_DODONGO_BABY,       LocType::ABOVE_GROUND);
        enemyLocations[1][0][10][10]     = EnemyLocation(ENEMY_DODONGO_BABY,       LocType::ABOVE_GROUND);
        enemyLocations[1][0][12][0]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[1][0][12][1]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[1][0][13][2]      = EnemyLocation(ENEMY_MAD_SCRUB,          LocType::ABOVE_GROUND);
        enemyLocations[1][0][13][3]      = EnemyLocation(ENEMY_MAD_SCRUB,          LocType::ABOVE_GROUND);
        enemyLocations[1][0][13][4]      = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[1][0][14][1]      = EnemyLocation(ENEMY_POE,                LocType::ABOVE_GROUND);
        enemyLocations[1][0][15][0]      = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
        enemyLocations[1][0][15][1]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[1][0][15][2]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[1][0][15][3]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
    }
    if (Dungeon::JabuJabusBelly.IsMQ()) {
        enemyLocations[2][0][0][0]       = EnemyLocation(ENEMY_OCTOROK,            LocType::SHALLOW_WATER);
        enemyLocations[2][0][0][7]       = EnemyLocation(ENEMY_SHABOM,             LocType::SHALLOW_WATER);
        enemyLocations[2][0][0][8]       = EnemyLocation(ENEMY_SHABOM,             LocType::ABOVE_GROUND);
        enemyLocations[2][0][0][9]       = EnemyLocation(ENEMY_SHABOM,             LocType::ABOVE_GROUND);
        enemyLocations[2][0][1][3]       = EnemyLocation(ENEMY_BIRI,               LocType::ABOVE_WATER);
        enemyLocations[2][0][1][4]       = EnemyLocation(ENEMY_BIRI,               LocType::ABOVE_GROUND);
        enemyLocations[2][0][1][16]      = EnemyLocation(ENEMY_STINGER_WATER,      LocType::UNDERWATER);
        enemyLocations[2][0][2][2]       = EnemyLocation(ENEMY_BIRI,               LocType::ABOVE_GROUND);
        enemyLocations[2][0][2][3]       = EnemyLocation(ENEMY_BIRI,               LocType::ABOVE_GROUND);
        enemyLocations[2][0][3][3]       = EnemyLocation(ENEMY_BIRI,               LocType::ABOVE_GROUND);
        enemyLocations[2][0][3][10]      = EnemyLocation(ENEMY_SHABOM,             LocType::ABOVE_GROUND);
        enemyLocations[2][0][4][7]       = EnemyLocation(ENEMY_LIZALFOS,           LocType::SHALLOW_WATER);
        enemyLocations[2][0][5][3]       = EnemyLocation(ENEMY_LIKE_LIKE,          LocType::SHALLOW_WATER);
        enemyLocations[2][0][5][4]       = EnemyLocation(ENEMY_LIKE_LIKE,          LocType::SHALLOW_WATER);
        enemyLocations[2][0][6][0]       = EnemyLocation(ENEMY_BARI,               LocType::ABOVE_GROUND);
        enemyLocations[2][0][7][0]       = EnemyLocation(ENEMY_LIZALFOS,           LocType::ABOVE_GROUND);
        enemyLocations[2][0][11][5]      = EnemyLocation(ENEMY_LIKE_LIKE,          LocType::ABOVE_GROUND);
        enemyLocations[2][0][11][6]      = EnemyLocation(ENEMY_LIKE_LIKE,          LocType::ABOVE_GROUND);
        enemyLocations[2][0][12][0]      = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
        enemyLocations[2][0][12][1]      = EnemyLocation(ENEMY_TAILPASARAN,        LocType::ABOVE_GROUND);
        enemyLocations[2][0][12][2]      = EnemyLocation(ENEMY_TAILPASARAN,        LocType::ABOVE_GROUND);
        enemyLocations[2][0][12][3]      = EnemyLocation(ENEMY_TAILPASARAN,        LocType::ABOVE_GROUND);
        enemyLocations[2][0][12][9]      = EnemyLocation(ENEMY_SHABOM,             LocType::ABOVE_GROUND);
        enemyLocations[2][0][12][10]     = EnemyLocation(ENEMY_SHABOM,             LocType::ABOVE_GROUND);
        enemyLocations[2][0][13][1]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[2][0][13][2]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[2][0][13][3]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_WATER);
        enemyLocations[2][0][13][5]      = EnemyLocation(ENEMY_STINGER_WATER,      LocType::UNDERWATER);
        enemyLocations[2][0][13][6]      = EnemyLocation(ENEMY_STINGER_WATER,      LocType::UNDERWATER);
        enemyLocations[2][0][14][0]      = EnemyLocation(ENEMY_STINGER_FLOOR,      LocType::SHALLOW_WATER);
        enemyLocations[2][0][14][1]      = EnemyLocation(ENEMY_STINGER_FLOOR,      LocType::SHALLOW_WATER);
        enemyLocations[2][0][14][3]      = EnemyLocation(ENEMY_LIKE_LIKE,          LocType::SHALLOW_WATER);
        enemyLocations[2][0][14][4]      = EnemyLocation(ENEMY_LIZALFOS,           LocType::ABOVE_GROUND);
    }
    if (Dungeon::ForestTemple.IsMQ()) {
        enemyLocations[3][0][0][0]       = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
        enemyLocations[3][0][0][1]       = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
        enemyLocations[3][0][0][2]       = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
        enemyLocations[3][0][0][3]       = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
        enemyLocations[3][0][0][4]       = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
        enemyLocations[3][0][0][5]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[3][0][1][0]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[3][0][1][1]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[3][0][1][2]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[3][0][5][4]       = EnemyLocation(ENEMY_STALFOS,            LocType::ABOVE_GROUND);
        enemyLocations[3][0][6][0]       = EnemyLocation(ENEMY_WOLFOS,             LocType::ABOVE_GROUND);
        enemyLocations[3][0][6][1]       = EnemyLocation(ENEMY_WOLFOS,             LocType::ABOVE_GROUND);
        enemyLocations[3][0][7][2]       = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
        enemyLocations[3][0][7][3]       = EnemyLocation(ENEMY_DEKU_BABA_SMALL,    LocType::ABOVE_GROUND);
        enemyLocations[3][0][7][4]       = EnemyLocation(ENEMY_DEKU_BABA_BIG,      LocType::ABOVE_GROUND);
        enemyLocations[3][0][7][5]       = EnemyLocation(ENEMY_DEKU_BABA_BIG,      LocType::ABOVE_GROUND);
        enemyLocations[3][0][8][0]       = EnemyLocation(ENEMY_OCTOROK,            LocType::ABOVE_WATER);
        enemyLocations[3][0][8][1]       = EnemyLocation(ENEMY_OCTOROK,            LocType::ABOVE_WATER);
        enemyLocations[3][0][8][2]       = EnemyLocation(ENEMY_OCTOROK,            LocType::ABOVE_WATER);
        enemyLocations[3][0][8][3]       = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
        enemyLocations[3][0][8][4]       = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
        enemyLocations[3][0][8][5]       = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
        enemyLocations[3][0][8][6]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[3][0][10][0]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[3][0][11][1]      = EnemyLocation(ENEMY_BUBBLE_BLUE,        LocType::ABOVE_GROUND);
        enemyLocations[3][0][11][2]      = EnemyLocation(ENEMY_BUBBLE_BLUE,        LocType::ABOVE_GROUND);
        enemyLocations[3][0][15][0]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[3][0][15][1]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[3][0][15][2]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[3][0][15][3]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[3][0][15][4]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[3][0][15][5]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[3][0][15][6]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[3][0][17][0]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[3][0][17][1]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[3][0][18][0]      = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
        enemyLocations[3][0][19][0]      = EnemyLocation(ENEMY_WALLMASTER,         LocType::ABOVE_VOID);
        enemyLocations[3][0][20][0]      = EnemyLocation(ENEMY_BUBBLE_GREEN,       LocType::ABOVE_VOID);
        enemyLocations[3][0][20][1]      = EnemyLocation(ENEMY_BUBBLE_GREEN,       LocType::ABOVE_VOID);
        enemyLocations[3][0][20][2]      = EnemyLocation(ENEMY_WALLMASTER,         LocType::ABOVE_VOID);
        enemyLocations[3][0][21][0]      = EnemyLocation(ENEMY_FLOORMASTER,        LocType::ABOVE_GROUND);
    }
    if (Dungeon::FireTemple.IsMQ()) {
        enemyLocations[4][0][3][0]       = EnemyLocation(ENEMY_FLARE_DANCER,       LocType::ABOVE_GROUND);
        enemyLocations[4][0][4][3]       = EnemyLocation(ENEMY_LIZALFOS,           LocType::ABOVE_GROUND);
        enemyLocations[4][0][5][6]       = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
        enemyLocations[4][0][5][8]       = EnemyLocation(ENEMY_LIZALFOS,           LocType::ABOVE_GROUND);
        enemyLocations[4][0][5][9]       = EnemyLocation(ENEMY_LIZALFOS,           LocType::ABOVE_GROUND);
        enemyLocations[4][0][5][10]      = EnemyLocation(ENEMY_LIZALFOS,           LocType::ABOVE_GROUND);
        enemyLocations[4][0][5][11]      = EnemyLocation(ENEMY_LIZALFOS,           LocType::ABOVE_GROUND);
        enemyLocations[4][0][7][2]       = EnemyLocation(ENEMY_TORCH_SLUG,         LocType::ABOVE_GROUND);
        enemyLocations[4][0][7][3]       = EnemyLocation(ENEMY_TORCH_SLUG,         LocType::ABOVE_GROUND);
        enemyLocations[4][0][14][2]      = EnemyLocation(ENEMY_STALFOS,            LocType::ABOVE_GROUND);
        enemyLocations[4][0][14][3]      = EnemyLocation(ENEMY_STALFOS,            LocType::ABOVE_GROUND);
        enemyLocations[4][0][15][0]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[4][0][15][2]      = EnemyLocation(ENEMY_STALFOS,            LocType::ABOVE_GROUND);
        enemyLocations[4][0][15][3]      = EnemyLocation(ENEMY_STALFOS,            LocType::ABOVE_GROUND);
        enemyLocations[4][0][17][2]      = EnemyLocation(ENEMY_LIKE_LIKE,          LocType::ABOVE_GROUND);
        enemyLocations[4][0][18][0]      = EnemyLocation(ENEMY_IRON_KNUCKLE,       LocType::ABOVE_GROUND);
        enemyLocations[4][0][18][1]      = EnemyLocation(ENEMY_FLYING_FLOOR_TILE,  LocType::ABOVE_GROUND);
        enemyLocations[4][0][18][2]      = EnemyLocation(ENEMY_FLYING_FLOOR_TILE,  LocType::ABOVE_GROUND);
        enemyLocations[4][0][18][3]      = EnemyLocation(ENEMY_FLYING_FLOOR_TILE,  LocType::ABOVE_GROUND);
        enemyLocations[4][0][18][4]      = EnemyLocation(ENEMY_FLYING_FLOOR_TILE,  LocType::ABOVE_GROUND);
        enemyLocations[4][0][18][5]      = EnemyLocation(ENEMY_FLYING_FLOOR_TILE,  LocType::ABOVE_GROUND);
        enemyLocations[4][0][19][0]      = EnemyLocation(ENEMY_FLYING_FLOOR_TILE,  LocType::ABOVE_GROUND);
        enemyLocations[4][0][19][1]      = EnemyLocation(ENEMY_FLYING_FLOOR_TILE,  LocType::ABOVE_GROUND);
        enemyLocations[4][0][19][2]      = EnemyLocation(ENEMY_FLYING_FLOOR_TILE,  LocType::ABOVE_GROUND);
        enemyLocations[4][0][19][3]      = EnemyLocation(ENEMY_FLYING_FLOOR_TILE,  LocType::ABOVE_GROUND);
        enemyLocations[4][0][19][4]      = EnemyLocation(ENEMY_FLYING_FLOOR_TILE,  LocType::ABOVE_GROUND);
        enemyLocations[4][0][19][5]      = EnemyLocation(ENEMY_FLYING_FLOOR_TILE,  LocType::ABOVE_GROUND);
        enemyLocations[4][0][19][6]      = EnemyLocation(ENEMY_FLYING_FLOOR_TILE,  LocType::ABOVE_GROUND);
        enemyLocations[4][0][19][7]      = EnemyLocation(ENEMY_FLYING_FLOOR_TILE,  LocType::ABOVE_GROUND);
        enemyLocations[4][0][24][0]      = EnemyLocation(ENEMY_FLARE_DANCER,       LocType::ABOVE_GROUND);
        enemyLocations[4][0][25][0]      = EnemyLocation(ENEMY_LIZALFOS,           LocType::ABOVE_GROUND);
    }
    if (Dungeon::WaterTemple.IsMQ()) {
        enemyLocations[5][0][2][1]       = EnemyLocation(ENEMY_SPIKE,              LocType::UNDERWATER);
        enemyLocations[5][0][3][5]       = EnemyLocation(ENEMY_STALFOS,            LocType::ABOVE_GROUND);
        enemyLocations[5][0][3][6]       = EnemyLocation(ENEMY_STALFOS,            LocType::ABOVE_GROUND);
        enemyLocations[5][0][6][2]       = EnemyLocation(ENEMY_STALFOS,            LocType::SHALLOW_WATER);
        enemyLocations[5][0][6][3]       = EnemyLocation(ENEMY_STALFOS,            LocType::SHALLOW_WATER);
        enemyLocations[5][0][6][4]       = EnemyLocation(ENEMY_STALFOS,            LocType::SHALLOW_WATER);
        enemyLocations[5][0][10][0]      = EnemyLocation(ENEMY_LIZALFOS,           LocType::ABOVE_GROUND);
        enemyLocations[5][0][13][0xFF]   = EnemyLocation(ENEMY_DARK_LINK,          LocType::ABOVE_GROUND);
        enemyLocations[5][0][14][1]      = EnemyLocation(ENEMY_DODONGO,            LocType::ABOVE_GROUND);
        enemyLocations[5][0][14][2]      = EnemyLocation(ENEMY_DODONGO,            LocType::SHALLOW_WATER);
        enemyLocations[5][0][14][3]      = EnemyLocation(ENEMY_DODONGO,            LocType::SHALLOW_WATER);
        enemyLocations[5][0][14][4]      = EnemyLocation(ENEMY_DODONGO,            LocType::SHALLOW_WATER);
        enemyLocations[5][0][14][5]      = EnemyLocation(ENEMY_DODONGO,            LocType::ABOVE_GROUND);
        enemyLocations[5][0][14][6]      = EnemyLocation(ENEMY_DODONGO,            LocType::SHALLOW_WATER);
        enemyLocations[5][0][14][7]      = EnemyLocation(ENEMY_DODONGO,            LocType::SHALLOW_WATER);
        enemyLocations[5][0][16][1]      = EnemyLocation(ENEMY_STALFOS,            LocType::ABOVE_GROUND);
        enemyLocations[5][0][18][0]      = EnemyLocation(ENEMY_SPIKE,              LocType::ABOVE_GROUND);
        enemyLocations[5][0][18][1]      = EnemyLocation(ENEMY_LIZALFOS,           LocType::ABOVE_GROUND);
        enemyLocations[5][0][18][2]      = EnemyLocation(ENEMY_LIZALFOS,           LocType::ABOVE_GROUND);
        enemyLocations[5][0][19][0]      = EnemyLocation(ENEMY_STALFOS,            LocType::ABOVE_GROUND);
        enemyLocations[5][0][19][1]      = EnemyLocation(ENEMY_STALFOS,            LocType::ABOVE_GROUND);
        enemyLocations[5][0][19][2]      = EnemyLocation(ENEMY_STALFOS,            LocType::ABOVE_GROUND);
        enemyLocations[5][0][20][0]      = EnemyLocation(ENEMY_LIZALFOS,           LocType::ABOVE_GROUND);
        enemyLocations[5][0][20][1]      = EnemyLocation(ENEMY_LIZALFOS,           LocType::ABOVE_GROUND);
    }
    if (Dungeon::SpiritTemple.IsMQ()) {
        enemyLocations[6][0][1][0]       = EnemyLocation(ENEMY_TORCH_SLUG,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][1][1]       = EnemyLocation(ENEMY_TORCH_SLUG,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][1][2]       = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[6][0][1][3]       = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[6][0][2][0]       = EnemyLocation(ENEMY_GIBDO,              LocType::ABOVE_GROUND);
        enemyLocations[6][0][2][1]       = EnemyLocation(ENEMY_GIBDO,              LocType::ABOVE_GROUND);
        enemyLocations[6][0][2][2]       = EnemyLocation(ENEMY_GIBDO,              LocType::ABOVE_GROUND);
        enemyLocations[6][0][3][0]       = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_VOID);
        enemyLocations[6][0][3][1]       = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_VOID);
        enemyLocations[6][0][3][2]       = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[6][0][3][3]       = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[6][0][3][4]       = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_VOID);
        enemyLocations[6][0][3][12]      = EnemyLocation(ENEMY_ANUBIS,             LocType::ABOVE_GROUND);
        enemyLocations[6][0][4][0]       = EnemyLocation(ENEMY_DODONGO_BABY,       LocType::ABOVE_GROUND);
        enemyLocations[6][0][4][1]       = EnemyLocation(ENEMY_DODONGO_BABY,       LocType::ABOVE_GROUND);
        enemyLocations[6][0][4][2]       = EnemyLocation(ENEMY_DODONGO_BABY,       LocType::ABOVE_GROUND);
        enemyLocations[6][0][4][3]       = EnemyLocation(ENEMY_DODONGO_BABY,       LocType::ABOVE_GROUND);
        enemyLocations[6][0][4][4]       = EnemyLocation(ENEMY_LIKE_LIKE,          LocType::ABOVE_GROUND);
        enemyLocations[6][0][4][11]      = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[6][0][5][0]       = EnemyLocation(ENEMY_WALLMASTER,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][5][1]       = EnemyLocation(ENEMY_FLOORMASTER,        LocType::ABOVE_GROUND);
        enemyLocations[6][0][5][18]      = EnemyLocation(ENEMY_FLYING_POT,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][5][19]      = EnemyLocation(ENEMY_FLYING_POT,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][5][20]      = EnemyLocation(ENEMY_WALLMASTER,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][5][22]      = EnemyLocation(ENEMY_FLYING_POT,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][8][2]       = EnemyLocation(ENEMY_BUBBLE_FIRE,        LocType::ABOVE_GROUND);
        enemyLocations[6][0][8][3]       = EnemyLocation(ENEMY_BUBBLE_FIRE,        LocType::ABOVE_GROUND);
        enemyLocations[6][0][8][4]       = EnemyLocation(ENEMY_BUBBLE_FIRE,        LocType::ABOVE_GROUND);
        enemyLocations[6][0][8][18]      = EnemyLocation(ENEMY_WALLMASTER,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][8][20]      = EnemyLocation(ENEMY_WALLMASTER,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][9][0]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[6][0][10][5]      = EnemyLocation(ENEMY_IRON_KNUCKLE,       LocType::ABOVE_GROUND);
        enemyLocations[6][0][12][0]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[6][0][12][1]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[6][0][12][2]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[6][0][12][3]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[6][0][12][4]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[6][0][12][5]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[6][0][12][6]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[6][0][12][7]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[6][0][12][8]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[6][0][13][1]      = EnemyLocation(ENEMY_MOBLIN_CLUB,        LocType::ABOVE_GROUND);
        enemyLocations[6][0][15][0]      = EnemyLocation(ENEMY_STALFOS,            LocType::ABOVE_GROUND);
        enemyLocations[6][0][15][1]      = EnemyLocation(ENEMY_STALFOS,            LocType::ABOVE_GROUND);
        enemyLocations[6][0][15][2]      = EnemyLocation(ENEMY_WALLMASTER,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][15][7]      = EnemyLocation(ENEMY_WALLMASTER,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][15][9]      = EnemyLocation(ENEMY_WALLMASTER,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][15][11]     = EnemyLocation(ENEMY_WALLMASTER,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][17][6]      = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[6][0][17][7]      = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[6][0][17][8]      = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[6][0][17][9]      = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[6][0][18][0]      = EnemyLocation(ENEMY_DINOLFOS,           LocType::ABOVE_GROUND);
        enemyLocations[6][0][18][1]      = EnemyLocation(ENEMY_DINOLFOS,           LocType::ABOVE_GROUND);
        enemyLocations[6][0][19][0]      = EnemyLocation(ENEMY_FLOORMASTER,        LocType::ABOVE_GROUND);
        enemyLocations[6][0][20][5]      = EnemyLocation(ENEMY_IRON_KNUCKLE,       LocType::ABOVE_GROUND);
        enemyLocations[6][0][21][0]      = EnemyLocation(ENEMY_GIBDO,              LocType::ABOVE_GROUND);
        // Don't randomize Iron Knuckle needed to destroy thrones.
        // enemyLocations[6][0][22][0]   = EnemyLocation(ENEMY_IRON_KNUCKLE,       LocType::ABOVE_GROUND);
        enemyLocations[6][0][23][0]      = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
        enemyLocations[6][0][23][1]      = EnemyLocation(ENEMY_TORCH_SLUG,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][23][2]      = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][23][3]      = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][23][4]      = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][23][5]      = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][26][0]      = EnemyLocation(ENEMY_TORCH_SLUG,         LocType::ABOVE_GROUND);
        enemyLocations[6][0][26][1]      = EnemyLocation(ENEMY_DINOLFOS,           LocType::ABOVE_GROUND);
        enemyLocations[6][0][26][6]      = EnemyLocation(ENEMY_BUBBLE_GREEN,       LocType::ABOVE_GROUND);
        enemyLocations[6][0][26][7]      = EnemyLocation(ENEMY_BUBBLE_GREEN,       LocType::ABOVE_GROUND);
        enemyLocations[6][0][27][7]      = EnemyLocation(ENEMY_STALFOS,            LocType::ABOVE_GROUND);
    }
    if (Dungeon::ShadowTemple.IsMQ()) {
        enemyLocations[7][0][0][6]       = EnemyLocation(ENEMY_FLYING_POT,         LocType::ABOVE_GROUND);
        enemyLocations[7][0][0][7]       = EnemyLocation(ENEMY_FLYING_POT,         LocType::ABOVE_GROUND);
        enemyLocations[7][0][0][8]       = EnemyLocation(ENEMY_FLYING_POT,         LocType::ABOVE_GROUND);
        enemyLocations[7][0][0][9]       = EnemyLocation(ENEMY_FLYING_POT,         LocType::ABOVE_GROUND);
        enemyLocations[7][0][1][0]       = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
        enemyLocations[7][0][1][1]       = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
        enemyLocations[7][0][1][2]       = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
        enemyLocations[7][0][1][3]       = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
        enemyLocations[7][0][4][0]       = EnemyLocation(ENEMY_DEAD_HAND_HAND,     LocType::ABOVE_GROUND);
        enemyLocations[7][0][4][1]       = EnemyLocation(ENEMY_DEAD_HAND_HAND,     LocType::ABOVE_GROUND);
        enemyLocations[7][0][4][2]       = EnemyLocation(ENEMY_DEAD_HAND_HAND,     LocType::ABOVE_GROUND);
        enemyLocations[7][0][4][3]       = EnemyLocation(ENEMY_DEAD_HAND_HAND,     LocType::ABOVE_GROUND);
        enemyLocations[7][0][4][4]       = EnemyLocation(ENEMY_DEAD_HAND_HAND,     LocType::ABOVE_GROUND);
        // Leave Dead Hand and one of its hands to lure it out.
        // enemyLocations[7][0][4][5]    = EnemyLocation(ENEMY_DEAD_HAND_HAND,     LocType::ABOVE_GROUND);
        // enemyLocations[7][0][4][6]    = EnemyLocation(ENEMY_DEAD_HAND,          LocType::ABOVE_GROUND);
        enemyLocations[7][0][5][0]       = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[7][0][6][0]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[7][0][6][1]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[7][0][6][2]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[7][0][6][3]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[7][0][7][0]       = EnemyLocation(ENEMY_GIBDO,              LocType::ABOVE_GROUND);
        enemyLocations[7][0][7][1]       = EnemyLocation(ENEMY_GIBDO,              LocType::ABOVE_GROUND);
        enemyLocations[7][0][8][1]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[7][0][8][2]       = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[7][0][8][3]       = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[7][0][9][5]       = EnemyLocation(ENEMY_BUBBLE_FIRE,        LocType::ABOVE_VOID);
        enemyLocations[7][0][9][6]       = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[7][0][9][7]       = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[7][0][9][10]      = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[7][0][11][8]      = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
        enemyLocations[7][0][11][9]      = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
        enemyLocations[7][0][13][0]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[7][0][13][1]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[7][0][13][2]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[7][0][13][3]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[7][0][13][4]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[7][0][13][5]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[7][0][13][6]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[7][0][13][7]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[7][0][14][4]      = EnemyLocation(ENEMY_STALFOS,            LocType::ABOVE_GROUND);
        enemyLocations[7][0][14][5]      = EnemyLocation(ENEMY_STALFOS,            LocType::ABOVE_GROUND);
        enemyLocations[7][0][15][0]      = EnemyLocation(ENEMY_BUBBLE_BLUE,        LocType::ABOVE_GROUND);
        enemyLocations[7][0][15][1]      = EnemyLocation(ENEMY_BUBBLE_BLUE,        LocType::ABOVE_GROUND);
        enemyLocations[7][0][15][2]      = EnemyLocation(ENEMY_LIKE_LIKE,          LocType::ABOVE_GROUND);
        enemyLocations[7][0][16][0]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[7][0][16][1]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[7][0][16][2]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[7][0][16][3]      = EnemyLocation(ENEMY_LIKE_LIKE,          LocType::ABOVE_GROUND);
        enemyLocations[7][0][18][0]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[7][0][19][0]      = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
        enemyLocations[7][0][19][1]      = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
        enemyLocations[7][0][19][2]      = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
        enemyLocations[7][0][19][3]      = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
        enemyLocations[7][0][20][0]      = EnemyLocation(ENEMY_GIBDO,              LocType::ABOVE_GROUND);
        enemyLocations[7][0][20][1]      = EnemyLocation(ENEMY_GIBDO,              LocType::ABOVE_GROUND);
        enemyLocations[7][0][20][5]      = EnemyLocation(ENEMY_FLYING_POT,         LocType::ABOVE_GROUND);
        enemyLocations[7][0][20][6]      = EnemyLocation(ENEMY_FLYING_POT,         LocType::ABOVE_GROUND);
        enemyLocations[7][0][21][3]      = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
        enemyLocations[7][0][21][4]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[7][0][21][16]     = EnemyLocation(ENEMY_STALFOS,            LocType::ABOVE_GROUND);
        enemyLocations[7][0][21][17]     = EnemyLocation(ENEMY_STALFOS,            LocType::ABOVE_GROUND);
    }
    if (Dungeon::BottomOfTheWell.IsMQ()) {
        enemyLocations[8][0][0][0]       = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
        enemyLocations[8][0][0][1]       = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
        enemyLocations[8][0][0][2]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[8][0][0][3]       = EnemyLocation(ENEMY_WALLMASTER,         LocType::ABOVE_GROUND);
        enemyLocations[8][0][0][4]       = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
        enemyLocations[8][0][1][1]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[8][0][1][2]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[8][0][1][3]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[8][0][1][4]       = EnemyLocation(ENEMY_WALLMASTER,         LocType::ABOVE_GROUND);
        enemyLocations[8][0][1][5]       = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
        enemyLocations[8][0][1][6]       = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
        enemyLocations[8][0][1][7]       = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
        enemyLocations[8][0][1][8]       = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
        enemyLocations[8][0][1][9]       = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
        enemyLocations[8][0][2][0]       = EnemyLocation(ENEMY_GIBDO,              LocType::ABOVE_GROUND);
        enemyLocations[8][0][2][1]       = EnemyLocation(ENEMY_POE,                LocType::ABOVE_GROUND);
        enemyLocations[8][0][3][0]       = EnemyLocation(ENEMY_WALLMASTER,         LocType::ABOVE_GROUND);
        enemyLocations[8][0][3][1]       = EnemyLocation(ENEMY_FLOORMASTER,        LocType::ABOVE_GROUND);
        enemyLocations[8][0][4][4]       = EnemyLocation(ENEMY_DEAD_HAND_HAND,     LocType::ABOVE_GROUND);
        enemyLocations[8][0][4][5]       = EnemyLocation(ENEMY_DEAD_HAND_HAND,     LocType::ABOVE_GROUND);
        enemyLocations[8][0][4][6]       = EnemyLocation(ENEMY_DEAD_HAND_HAND,     LocType::ABOVE_GROUND);
        // Leave Dead Hand and one of its hands to lure it out.
        // enemyLocations[8][0][4][7]    = EnemyLocation(ENEMY_DEAD_HAND_HAND,     LocType::ABOVE_GROUND);
        // enemyLocations[8][0][4][8]    = EnemyLocation(ENEMY_DEAD_HAND,          LocType::ABOVE_GROUND);
        enemyLocations[8][0][6][0]       = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[8][0][6][1]       = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[8][0][6][2]       = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[8][0][6][3]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[8][0][6][4]       = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
    }
    if (Dungeon::IceCavern.IsMQ()) {
        enemyLocations[9][0][1][0]       = EnemyLocation(ENEMY_FREEZARD,           LocType::ABOVE_GROUND);
        enemyLocations[9][0][1][1]       = EnemyLocation(ENEMY_TEKTITE_BLUE,       LocType::ABOVE_GROUND);
        enemyLocations[9][0][1][2]       = EnemyLocation(ENEMY_TEKTITE_BLUE,       LocType::ABOVE_GROUND);
        enemyLocations[9][0][3][5]       = EnemyLocation(ENEMY_WOLFOS,             LocType::ABOVE_GROUND);
        enemyLocations[9][0][3][6]       = EnemyLocation(ENEMY_FREEZARD,           LocType::ABOVE_GROUND);
        enemyLocations[9][0][3][7]       = EnemyLocation(ENEMY_FREEZARD,           LocType::ABOVE_GROUND);
        enemyLocations[9][0][5][3]       = EnemyLocation(ENEMY_WOLFOS,             LocType::ABOVE_GROUND);
        enemyLocations[9][0][5][4]       = EnemyLocation(ENEMY_WOLFOS,             LocType::ABOVE_GROUND);
        enemyLocations[9][0][5][5]       = EnemyLocation(ENEMY_KEESE_ICE,          LocType::ABOVE_GROUND);
        enemyLocations[9][0][5][6]       = EnemyLocation(ENEMY_KEESE_ICE,          LocType::ABOVE_GROUND);
        enemyLocations[9][0][6][3]       = EnemyLocation(ENEMY_KEESE_ICE,          LocType::ABOVE_GROUND);
        enemyLocations[9][0][6][4]       = EnemyLocation(ENEMY_KEESE_ICE,          LocType::ABOVE_GROUND);
        enemyLocations[9][0][7][3]       = EnemyLocation(ENEMY_STALFOS,            LocType::ABOVE_GROUND);
        enemyLocations[9][0][8][0]       = EnemyLocation(ENEMY_FREEZARD,           LocType::ABOVE_GROUND);
        enemyLocations[9][0][8][1]       = EnemyLocation(ENEMY_FREEZARD,           LocType::ABOVE_GROUND);
        enemyLocations[9][0][9][0]       = EnemyLocation(ENEMY_FREEZARD,           LocType::ABOVE_GROUND);
        enemyLocations[9][0][9][1]       = EnemyLocation(ENEMY_FREEZARD,           LocType::ABOVE_GROUND);
        enemyLocations[9][0][9][5]       = EnemyLocation(ENEMY_FREEZARD,           LocType::ABOVE_GROUND);
        enemyLocations[9][0][11][11]     = EnemyLocation(ENEMY_WOLFOS,             LocType::ABOVE_GROUND);
        enemyLocations[9][0][11][12]     = EnemyLocation(ENEMY_WOLFOS,             LocType::ABOVE_GROUND);
        enemyLocations[9][0][11][13]     = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
    }
    if (Dungeon::GerudoTrainingGrounds.IsMQ()) {
        enemyLocations[11][0][1][0]      = EnemyLocation(ENEMY_IRON_KNUCKLE,       LocType::ABOVE_GROUND);
        enemyLocations[11][0][2][0]      = EnemyLocation(ENEMY_FREEZARD,           LocType::ABOVE_GROUND);
        enemyLocations[11][0][2][17]     = EnemyLocation(ENEMY_WALLMASTER,         LocType::ABOVE_GROUND);
        enemyLocations[11][0][2][21]     = EnemyLocation(ENEMY_WALLMASTER,         LocType::ABOVE_GROUND);
        enemyLocations[11][0][3][4]      = EnemyLocation(ENEMY_STALFOS,            LocType::ABOVE_GROUND);
        enemyLocations[11][0][3][5]      = EnemyLocation(ENEMY_STALFOS,            LocType::ABOVE_GROUND);
        enemyLocations[11][0][3][6]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[11][0][3][7]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[11][0][3][8]      = EnemyLocation(ENEMY_SKULLTULA,          LocType::ABOVE_GROUND);
        enemyLocations[11][0][5][0]      = EnemyLocation(ENEMY_IRON_KNUCKLE,       LocType::ABOVE_GROUND);
        enemyLocations[11][0][5][1]      = EnemyLocation(ENEMY_TORCH_SLUG,         LocType::ABOVE_GROUND);
        enemyLocations[11][0][5][2]      = EnemyLocation(ENEMY_TORCH_SLUG,         LocType::ABOVE_GROUND);
        enemyLocations[11][0][6][1]      = EnemyLocation(ENEMY_BUBBLE_FIRE,        LocType::ABOVE_VOID);
        enemyLocations[11][0][6][2]      = EnemyLocation(ENEMY_BUBBLE_FIRE,        LocType::ABOVE_VOID);
        enemyLocations[11][0][6][3]      = EnemyLocation(ENEMY_BUBBLE_FIRE,        LocType::ABOVE_VOID);
        enemyLocations[11][0][7][0]      = EnemyLocation(ENEMY_DINOLFOS,           LocType::ABOVE_GROUND);
        enemyLocations[11][0][7][1]      = EnemyLocation(ENEMY_DINOLFOS,           LocType::ABOVE_GROUND);
        enemyLocations[11][0][7][2]      = EnemyLocation(ENEMY_LIZALFOS,           LocType::ABOVE_GROUND);
        enemyLocations[11][0][7][3]      = EnemyLocation(ENEMY_DODONGO,            LocType::ABOVE_GROUND);
        enemyLocations[11][0][7][4]      = EnemyLocation(ENEMY_DODONGO,            LocType::ABOVE_GROUND);
        enemyLocations[11][0][7][5]      = EnemyLocation(ENEMY_ARMOS,              LocType::ABOVE_GROUND);
        enemyLocations[11][0][9][0]      = EnemyLocation(ENEMY_STINGER_WATER,      LocType::UNDERWATER);
        enemyLocations[11][0][9][1]      = EnemyLocation(ENEMY_STINGER_WATER,      LocType::UNDERWATER);
        enemyLocations[11][0][9][3]      = EnemyLocation(ENEMY_BARI,               LocType::ABOVE_GROUND);
        enemyLocations[11][0][9][4]      = EnemyLocation(ENEMY_SHELL_BLADE,        LocType::UNDERWATER);
        enemyLocations[11][0][10][0]     = EnemyLocation(ENEMY_FREEZARD,           LocType::ABOVE_GROUND);
        enemyLocations[11][0][10][1]     = EnemyLocation(ENEMY_FREEZARD,           LocType::ABOVE_GROUND);
        enemyLocations[11][0][10][2]     = EnemyLocation(ENEMY_SPIKE,              LocType::ABOVE_GROUND);
        enemyLocations[11][0][10][3]     = EnemyLocation(ENEMY_SPIKE,              LocType::ABOVE_GROUND);
        enemyLocations[11][0][10][4]     = EnemyLocation(ENEMY_SPIKE,              LocType::ABOVE_GROUND);
    }
    if (Dungeon::GanonsCastle.IsMQ()) {
        enemyLocations[13][0][0][0]      = EnemyLocation(ENEMY_ARMOS,              LocType::ABOVE_GROUND);
        enemyLocations[13][0][0][1]      = EnemyLocation(ENEMY_ARMOS,              LocType::ABOVE_GROUND);
        enemyLocations[13][0][0][2]      = EnemyLocation(ENEMY_IRON_KNUCKLE,       LocType::ABOVE_GROUND);
        enemyLocations[13][0][0][9]      = EnemyLocation(ENEMY_BUBBLE_GREEN,       LocType::ABOVE_GROUND);
        enemyLocations[13][0][0][10]     = EnemyLocation(ENEMY_BUBBLE_GREEN,       LocType::ABOVE_GROUND);
        enemyLocations[13][0][2][0]      = EnemyLocation(ENEMY_DEAD_HAND_HAND,     LocType::ABOVE_GROUND);
        enemyLocations[13][0][2][1]      = EnemyLocation(ENEMY_FREEZARD,           LocType::ABOVE_GROUND);
        enemyLocations[13][0][2][2]      = EnemyLocation(ENEMY_FREEZARD,           LocType::ABOVE_GROUND);
        enemyLocations[13][0][2][3]      = EnemyLocation(ENEMY_FREEZARD,           LocType::ABOVE_GROUND);
        enemyLocations[13][0][3][0]      = EnemyLocation(ENEMY_KEESE_ICE,          LocType::ABOVE_GROUND);
        enemyLocations[13][0][3][3]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[13][0][3][4]      = EnemyLocation(ENEMY_KEESE_NORMAL,       LocType::ABOVE_GROUND);
        enemyLocations[13][0][3][5]      = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[13][0][5][1]      = EnemyLocation(ENEMY_STALFOS,            LocType::ABOVE_GROUND);
        enemyLocations[13][0][5][2]      = EnemyLocation(ENEMY_STALFOS,            LocType::ABOVE_GROUND);
        enemyLocations[13][0][6][1]      = EnemyLocation(ENEMY_ARMOS,              LocType::ABOVE_GROUND);
        enemyLocations[13][0][6][8]      = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[13][0][6][9]      = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[13][0][6][10]     = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[13][0][6][11]     = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[13][0][6][12]     = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[13][0][6][13]     = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[13][0][8][3]      = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[13][0][9][6]      = EnemyLocation(ENEMY_TORCH_SLUG,         LocType::ABOVE_GROUND);
        enemyLocations[13][0][9][7]      = EnemyLocation(ENEMY_TORCH_SLUG,         LocType::ABOVE_GROUND);
        enemyLocations[13][0][9][8]      = EnemyLocation(ENEMY_DINOLFOS,           LocType::ABOVE_GROUND);
        enemyLocations[13][0][10][3]     = EnemyLocation(ENEMY_SKULLWALLTULA,      LocType::ABOVE_GROUND);
        enemyLocations[13][0][12][5]     = EnemyLocation(ENEMY_BUBBLE_GREEN,       LocType::ABOVE_VOID);
        enemyLocations[13][0][12][6]     = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[13][0][12][7]     = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[13][0][12][8]     = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[13][0][12][9]     = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[13][0][14][1]     = EnemyLocation(ENEMY_TORCH_SLUG,         LocType::ABOVE_GROUND);
        enemyLocations[13][0][14][2]     = EnemyLocation(ENEMY_TORCH_SLUG,         LocType::ABOVE_GROUND);
        enemyLocations[13][0][14][16]    = EnemyLocation(ENEMY_BEAMOS,             LocType::ABOVE_GROUND);
        enemyLocations[13][0][17][9]     = EnemyLocation(ENEMY_TORCH_SLUG,         LocType::ABOVE_GROUND);
        enemyLocations[13][0][17][10]    = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        enemyLocations[13][0][17][11]    = EnemyLocation(ENEMY_KEESE_FIRE,         LocType::ABOVE_GROUND);
        // Don't randomize Iron Knuckle needed to destroy thrones.
        // enemyLocations[13][0][17][12] = EnemyLocation(ENEMY_IRON_KNUCKLE,       LocType::ABOVE_GROUND);
        enemyLocations[13][0][18][6]     = EnemyLocation(ENEMY_GIBDO,              LocType::ABOVE_GROUND);
        enemyLocations[13][0][18][7]     = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
        enemyLocations[13][0][18][8]     = EnemyLocation(ENEMY_REDEAD,             LocType::ABOVE_GROUND);
        enemyLocations[13][0][18][9]     = EnemyLocation(ENEMY_BUBBLE_GREEN,       LocType::ABOVE_GROUND);
        enemyLocations[13][0][18][10]    = EnemyLocation(ENEMY_BUBBLE_GREEN,       LocType::ABOVE_GROUND);
        enemyLocations[13][0][18][24]    = EnemyLocation(ENEMY_WALLMASTER,         LocType::ABOVE_GROUND);
    }
}
// clang-format on

void AddDuplicateLocations(void) {
    // Enemies in Hyrule Field as child should stay the same in OoT layer
    enemyLocations[81][1][0][4]    = enemyLocations[81][0][0][8];
    enemyLocations[81][1][0][5]    = enemyLocations[81][0][0][9];
    enemyLocations[81][1][0][6]    = enemyLocations[81][0][0][10];
    enemyLocations[81][1][0][7]    = enemyLocations[81][0][0][11];
    enemyLocations[81][1][0][8]    = enemyLocations[81][0][0][12];
    enemyLocations[81][1][0][9]    = enemyLocations[81][0][0][13];
    enemyLocations[81][1][0][10]   = enemyLocations[81][0][0][14];
    enemyLocations[81][1][0][0xFF] = enemyLocations[81][0][0][0xFF];

    // Enemies in Graveyard as adult should stay the same at night
    enemyLocations[83][3][1][12] = enemyLocations[83][2][1][12];
    enemyLocations[83][3][1][13] = enemyLocations[83][2][1][13];
    enemyLocations[83][3][1][14] = enemyLocations[83][2][1][14];

    // A Beamos in Shadow Temple is duplicated in 2 rooms to hide the transition
    // (only in the vanilla dungeon, even though it appears in MQ too)
    if (Dungeon::ShadowTemple.IsVanilla()) {
        enemyLocations[7][0][2][0] = enemyLocations[7][0][5][0];
    }
}

} // namespace Enemizer
