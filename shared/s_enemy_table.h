/**
 * Data table for Enemy Randomizer, to be used following the X-Macro pattern.
 */

#define U16_ARR(...) ((u16[]){ __VA_ARGS__ })

// Required X-Macro arguments: _enemyId, _name, _actorId, _possibleParams, _soulVar, _validLocTypes
#define ENEMY_TABLE                                                                                               \
    X(ENEMY_INVALID, "Invalid Enemy", 0, U16_ARR(), noVariable, ({}))                                             \
    X(ENEMY_STALFOS, "Stalfos", ACTOR_STALFOS,                                                                    \
      U16_ARR(0x0002 /*rises from ground*/, 0x0003 /*drops from above when approached*/), SoulStalfos,            \
      ({ LocType::ABOVE_GROUND, LocType::NARROW_GROUND, LocType::SHALLOW_WATER, LocType::SPAWNER }))              \
    X(ENEMY_STALCHILD, "Stalchild", ACTOR_STALCHILD, U16_ARR(0x0000 /*normal*/, 0x0005 /*big (20 kills)*/),       \
      SoulStalchild, ({ LocType::ABOVE_GROUND, LocType::SHALLOW_WATER, LocType::SPAWNER }))                       \
    X(ENEMY_POE, "Poe", ACTOR_POE, U16_ARR(0x0000 /*normal*/, 0x0002 /*Sharp*/, 0x0003 /*Flat*/), SoulPoe,        \
      ({ LocType::ABOVE_GROUND, LocType::NARROW_GROUND, LocType::ABOVE_VOID, LocType::UNDERWATER,                 \
         LocType::ABOVE_WATER, LocType::SHALLOW_WATER, LocType::SPAWNER }))                                       \
    X(ENEMY_POE_SISTER, "Poe Sister", ACTOR_POE_SISTER, U16_ARR(0x0000), SoulPoe, ({ /* Unimplemented */ }))      \
    X(ENEMY_OCTOROK, "Octorok", ACTOR_OCTOROK, U16_ARR(0x0000), SoulOctorok,                                      \
      ({ LocType::ABOVE_WATER, LocType::SHALLOW_WATER }))                                                         \
    X(ENEMY_DODONGO, "Dodongo (Normal)", ACTOR_DODONGO, U16_ARR(0x0000), SoulDodongo,                             \
      ({ LocType::ABOVE_GROUND, LocType::NARROW_GROUND, LocType::SHALLOW_WATER }))                                \
    X(ENEMY_DODONGO_BABY, "Dodongo (Baby)", ACTOR_BABY_DODONGO, U16_ARR(0x0000), SoulDodongo,                     \
      ({ LocType::ABOVE_GROUND, LocType::NARROW_GROUND, LocType::SHALLOW_WATER, LocType::SPAWNER }))              \
    X(ENEMY_KEESE_NORMAL, "Keese (Normal)", ACTOR_KEESE, U16_ARR(0x0002), SoulKeese,                              \
      ({ LocType::ABOVE_GROUND, LocType::NARROW_GROUND, LocType::ABOVE_VOID, LocType::UNDERWATER,                 \
         LocType::ABOVE_WATER, LocType::SHALLOW_WATER }))                                                         \
    X(ENEMY_KEESE_FIRE, "Keese (Fire)", ACTOR_KEESE, U16_ARR(0x0001), SoulKeese,                                  \
      ({ LocType::ABOVE_GROUND, LocType::NARROW_GROUND, LocType::ABOVE_VOID, LocType::ABOVE_WATER,                \
         LocType::SHALLOW_WATER }))                                                                               \
    X(ENEMY_KEESE_ICE, "Keese (Ice)", ACTOR_KEESE, U16_ARR(0x0004), SoulKeese,                                    \
      ({ LocType::ABOVE_GROUND, LocType::NARROW_GROUND, LocType::ABOVE_VOID, LocType::UNDERWATER,                 \
         LocType::ABOVE_WATER, LocType::SHALLOW_WATER }))                                                         \
    X(ENEMY_TEKTITE_RED, "Tektite (Red)", ACTOR_TEKTITE, U16_ARR(0xFFFF), SoulTektite,                            \
      ({ LocType::ABOVE_GROUND, LocType::SHALLOW_WATER }))                                                        \
    X(ENEMY_TEKTITE_BLUE, "Tektite (Blue)", ACTOR_TEKTITE, U16_ARR(0xFFFE), SoulTektite,                          \
      ({ LocType::ABOVE_GROUND, LocType::ABOVE_WATER, LocType::SHALLOW_WATER }))                                  \
    X(ENEMY_LEEVER, "Leever", ACTOR_LEEVER, U16_ARR(0x0000 /*normal*/, 0x0001 /*big*/), SoulLeever,               \
      ({ LocType::ABOVE_GROUND, LocType::NARROW_GROUND, LocType::SHALLOW_WATER, LocType::SPAWNER }))              \
    X(ENEMY_PEAHAT, "Peahat", ACTOR_PEAHAT, U16_ARR(0xFFFF), SoulPeahat,                                          \
      ({ LocType::ABOVE_GROUND, LocType::NARROW_GROUND, LocType::ABOVE_WATER, LocType::SHALLOW_WATER }))          \
    X(ENEMY_PEAHAT_LARVA, "Peahat Larva", ACTOR_PEAHAT, U16_ARR(0x0001), SoulPeahat,                              \
      ({ LocType::ABOVE_GROUND, LocType::NARROW_GROUND, LocType::ABOVE_VOID, LocType::UNDERWATER,                 \
         LocType::ABOVE_WATER, LocType::SHALLOW_WATER }))                                                         \
    X(ENEMY_LIZALFOS, "Lizalfos", ACTOR_LIZALFOS,                                                                 \
      U16_ARR(0xFF80 /*normal*/, 0xFFFF /*drops from above when approached*/), SoulLizalfosDinolfos,              \
      ({ LocType::ABOVE_GROUND, LocType::SHALLOW_WATER }))                                                        \
    X(ENEMY_DINOLFOS, "Dinolfos", ACTOR_LIZALFOS, U16_ARR(0xFFFE), SoulLizalfosDinolfos,                          \
      ({ LocType::ABOVE_GROUND, LocType::SHALLOW_WATER }))                                                        \
    X(ENEMY_GOHMA_LARVA, "Gohma Larva", ACTOR_GOHMA_LARVA,                                                        \
      U16_ARR(0x0000 /*egg that drops and hatches*/, 0x0007 /*stationary egg*/), SoulGohma,                       \
      ({ LocType::ABOVE_GROUND, LocType::UNDERWATER, LocType::SHALLOW_WATER, LocType::SPAWNER }))                 \
    X(ENEMY_SHABOM, "Shabom", ACTOR_SHABOM, U16_ARR(0x0000), SoulShabom,                                          \
      ({ LocType::ABOVE_GROUND, LocType::ABOVE_WATER, LocType::SHALLOW_WATER, LocType::SPAWNER }))                \
    X(ENEMY_BIRI, "Biri", ACTOR_BIRI, U16_ARR(0xFFFF), SoulBiriBari,                                              \
      ({ LocType::ABOVE_GROUND, LocType::NARROW_GROUND, LocType::ABOVE_VOID, LocType::UNDERWATER,                 \
         LocType::ABOVE_WATER, LocType::SHALLOW_WATER }))                                                         \
    X(ENEMY_BARI, "Bari", ACTOR_BARI, U16_ARR(0xFFFF), SoulBiriBari,                                              \
      ({ LocType::ABOVE_GROUND, LocType::NARROW_GROUND, LocType::UNDERWATER, LocType::SHALLOW_WATER }))           \
    X(ENEMY_TAILPASARAN, "Tailpasaran", ACTOR_TAILPASARAN, U16_ARR(0xFFFF), SoulTailpasaran,                      \
      ({ LocType::ABOVE_GROUND, LocType::NARROW_GROUND, LocType::SHALLOW_WATER }))                                \
    X(ENEMY_BIG_OCTO, "Big Octo", ACTOR_BIG_OCTO, U16_ARR(0x0000), SoulOctorok, ({ /* Unimplemented */ }))        \
    X(ENEMY_PARASITIC_TENTACLE, "Parasitic Tentacle", ACTOR_PARASITIC_TENTACLE, U16_ARR(0x0000),                  \
      SoulParasiticTentacle, ({ /* Unimplemented */ }))                                                           \
    X(ENEMY_STINGER_FLOOR, "Stinger (Floor)", ACTOR_STINGER_FLOOR, U16_ARR(0x000A), SoulStinger,                  \
      ({ LocType::ABOVE_GROUND, LocType::NARROW_GROUND, LocType::UNDERWATER, LocType::SHALLOW_WATER }))           \
    X(ENEMY_STINGER_WATER, "Stinger (Water)", ACTOR_STINGER_WATER, U16_ARR(0x0000), SoulStinger,                  \
      ({ LocType::UNDERWATER, LocType::SHALLOW_WATER }))                                                          \
    X(ENEMY_SHELL_BLADE, "Shell Blade", ACTOR_SHELL_BLADE, U16_ARR(0x0000), SoulShellBlade,                       \
      ({ LocType::ABOVE_GROUND, LocType::UNDERWATER, LocType::SHALLOW_WATER }))                                   \
    X(ENEMY_SPIKE, "Spike", ACTOR_SPIKE, U16_ARR(0x0000), SoulSpike,                                              \
      ({ LocType::ABOVE_GROUND, LocType::UNDERWATER, LocType::SHALLOW_WATER }))                                   \
    X(ENEMY_DARK_LINK, "Dark Link", ACTOR_DARK_LINK, U16_ARR(0x0000), SoulDarkLink,                               \
      ({ LocType::ABOVE_GROUND, LocType::SHALLOW_WATER }))                                                        \
    X(ENEMY_SKULLTULA, "Skulltula", ACTOR_SKULLTULA, U16_ARR(0x0000, 0x0001), SoulSkulltula,                      \
      ({ LocType::ABOVE_GROUND, LocType::NARROW_GROUND, LocType::ABOVE_VOID, LocType::UNDERWATER,                 \
         LocType::ABOVE_WATER, LocType::SHALLOW_WATER }))                                                         \
    X(ENEMY_SKULLWALLTULA, "Skullwalltula", ACTOR_SKULLWALLTULA, U16_ARR(0x0000), SoulSkulltula,                  \
      ({ LocType::ABOVE_GROUND, LocType::NARROW_GROUND, LocType::UNDERWATER, LocType::SHALLOW_WATER }))           \
    X(ENEMY_TORCH_SLUG, "Torch Slug", ACTOR_TORCH_SLUG, U16_ARR(0xFFFF), SoulTorchSlug,                           \
      ({ LocType::ABOVE_GROUND, LocType::NARROW_GROUND }))                                                        \
    X(ENEMY_FLARE_DANCER, "Flare Dancer", ACTOR_FLARE_DANCER, U16_ARR(0x0000), SoulFlareDancer,                   \
      ({ LocType::ABOVE_GROUND }))                                                                                \
    X(ENEMY_FLYING_FLOOR_TILE, "Flying Floor Tile", ACTOR_FLYING_FLOOR_TILE, U16_ARR(0x0000), SoulFlyingTrap,     \
      ({ LocType::ABOVE_GROUND, LocType::NARROW_GROUND, LocType::UNDERWATER, LocType::SHALLOW_WATER }))           \
    X(ENEMY_FLYING_POT, "Flying Pot", ACTOR_FLYING_POT, U16_ARR(0x0000), SoulFlyingTrap,                          \
      ({ LocType::ABOVE_GROUND, LocType::SHALLOW_WATER }))                                                        \
    X(ENEMY_MOBLIN_CLUB, "Moblin (Club)", ACTOR_MOBLIN, U16_ARR(0x0000), SoulMoblin,                              \
      ({ LocType::ABOVE_GROUND, LocType::NARROW_GROUND, LocType::SHALLOW_WATER }))                                \
    X(ENEMY_MOBLIN_SPEAR, "Moblin (Spear)", ACTOR_MOBLIN, U16_ARR(0xFFFF), SoulMoblin,                            \
      ({ LocType::ABOVE_GROUND, LocType::SHALLOW_WATER }))                                                        \
    X(ENEMY_ARMOS, "Armos", ACTOR_ARMOS, U16_ARR(0xFFFF), SoulArmos,                                              \
      ({ LocType::ABOVE_GROUND, LocType::NARROW_GROUND, LocType::SHALLOW_WATER }))                                \
    X(ENEMY_DEKU_BABA_WITHERED, "Deku Baba (Withered)", ACTOR_WITHERED_DEKU_BABA, U16_ARR(0x0000), SoulDekuBaba,  \
      ({ LocType::ABOVE_GROUND, LocType::NARROW_GROUND, LocType::SHALLOW_WATER }))                                \
    X(ENEMY_DEKU_BABA_SMALL, "Deku Baba (Small)", ACTOR_DEKU_BABA, U16_ARR(0x0000), SoulDekuBaba,                 \
      ({ LocType::ABOVE_GROUND, LocType::NARROW_GROUND, LocType::UNDERWATER, LocType::SHALLOW_WATER }))           \
    X(ENEMY_DEKU_BABA_BIG, "Deku Baba (Big)", ACTOR_DEKU_BABA, U16_ARR(0x0001), SoulDekuBaba,                     \
      ({ LocType::ABOVE_GROUND, LocType::NARROW_GROUND, LocType::SHALLOW_WATER }))                                \
    X(ENEMY_HINT_DEKU_SCRUB, "Deku Scrub", ACTOR_HINT_DEKU_SCRUB, U16_ARR(0x0000), SoulDekuScrub,                 \
      ({ LocType::ABOVE_GROUND, LocType::UNDERWATER, LocType::SHALLOW_WATER }))                                   \
    X(ENEMY_MAD_SCRUB, "Mad Scrub", ACTOR_MAD_SCRUB,                                                              \
      U16_ARR(0x0100, 0x0300, 0x0500) /* shoots 1, 3 or 5 nuts in a row */, SoulDekuScrub,                        \
      ({ LocType::ABOVE_GROUND, LocType::UNDERWATER, LocType::SHALLOW_WATER }))                                   \
    X(ENEMY_BUBBLE_BLUE, "Bubble (Blue)", ACTOR_BUBBLE, U16_ARR(0xFFFF), SoulBubble,                              \
      ({ LocType::ABOVE_GROUND, LocType::SHALLOW_WATER }))                                                        \
    X(ENEMY_BUBBLE_FIRE, "Bubble (Fire)", ACTOR_BUBBLE, U16_ARR(0xFFFE), SoulBubble, ({ LocType::ABOVE_GROUND })) \
    X(ENEMY_BUBBLE_GREEN, "Bubble (Green)", ACTOR_BUBBLE, U16_ARR(0x02FC /*small*/, 0x00FB /*big*/), SoulBubble,  \
      ({ LocType::ABOVE_GROUND, LocType::NARROW_GROUND, LocType::ABOVE_VOID, LocType::ABOVE_WATER,                \
         LocType::SHALLOW_WATER }))                                                                               \
    X(ENEMY_BUBBLE_WHITE, "Bubble (White)", ACTOR_BUBBLE, U16_ARR(0x00FD), SoulBubble,                            \
      ({ LocType::ABOVE_GROUND, LocType::NARROW_GROUND, LocType::ABOVE_VOID, LocType::ABOVE_WATER,                \
         LocType::SHALLOW_WATER }))                                                                               \
    X(ENEMY_BEAMOS, "Beamos", ACTOR_BEAMOS, U16_ARR(0x0500 /*big*/, 0x0501 /*small*/), SoulBeamos,                \
      ({ LocType::ABOVE_GROUND, LocType::NARROW_GROUND, LocType::SHALLOW_WATER }))                                \
    X(ENEMY_WALLMASTER, "Wallmaster", ACTOR_WALLMASTER, U16_ARR(0x0000), SoulWallmaster,                          \
      ({ LocType::ABOVE_GROUND, LocType::NARROW_GROUND, LocType::ABOVE_VOID, LocType::ABOVE_WATER,                \
         LocType::SHALLOW_WATER }))                                                                               \
    X(ENEMY_FLOORMASTER, "Floormaster", ACTOR_FLOORMASTER, U16_ARR(0x0000), SoulWallmaster,                       \
      ({ LocType::ABOVE_GROUND, LocType::SHALLOW_WATER }))                                                        \
    X(ENEMY_REDEAD, "Redead", ACTOR_REDEAD, U16_ARR(0x7F01 /*standing*/, 0x7F02 /*crouching*/), SoulRedeadGibdo,  \
      ({ LocType::ABOVE_GROUND, LocType::SHALLOW_WATER }))                                                        \
    X(ENEMY_GIBDO, "Gibdo", ACTOR_REDEAD, U16_ARR(0x7FFE), SoulRedeadGibdo,                                       \
      ({ LocType::ABOVE_GROUND, LocType::SHALLOW_WATER }))                                                        \
    X(ENEMY_DEAD_HAND, "Dead Hand", ACTOR_DEAD_HAND, U16_ARR(0x0000), SoulDeadHand, ({ /* Unimplemented */ }))    \
    X(ENEMY_DEAD_HAND_HAND, "Dead Hand's Hand", ACTOR_DEAD_HAND_HAND, U16_ARR(0x0000), SoulDeadHand,              \
      ({ LocType::ABOVE_GROUND, LocType::NARROW_GROUND, LocType::SHALLOW_WATER }))                                \
    X(ENEMY_LIKE_LIKE, "Like Like", ACTOR_LIKE_LIKE, U16_ARR(0x0000), SoulLikeLike,                               \
      ({ LocType::ABOVE_GROUND, LocType::SHALLOW_WATER }))                                                        \
    X(ENEMY_ANUBIS, "Anubis", ACTOR_ANUBIS_SPAWNER, U16_ARR(0x0003), SoulAnubis,                                  \
      ({ LocType::ABOVE_GROUND, LocType::NARROW_GROUND, LocType::SHALLOW_WATER }))                                \
    X(ENEMY_IRON_KNUCKLE, "Iron Knuckle", ACTOR_IRON_KNUCKLE,                                                     \
      U16_ARR(0xFF01 /*silver*/, 0xFF02 /*black*/, 0xFF03 /*white*/), SoulGerudo,                                 \
      ({ LocType::ABOVE_GROUND, LocType::SHALLOW_WATER }))                                                        \
    X(ENEMY_GERUDO_FIGHTER, "Gerudo Fighter", ACTOR_GERUDO_FIGHTER, U16_ARR(0x0000), SoulGerudo,                  \
      ({ LocType::ABOVE_GROUND, LocType::SHALLOW_WATER }))                                                        \
    X(ENEMY_SKULL_KID, "Skull Kid", ACTOR_SKULL_KID, U16_ARR(0xFFFF), SoulSkullKid,                               \
      ({ LocType::ABOVE_GROUND, LocType::SHALLOW_WATER }))                                                        \
    X(ENEMY_FREEZARD, "Freezard", ACTOR_FREEZARD,                                                                 \
      U16_ARR(0x0000 /*normal*/, 0xFFFF /*appears and moves when approached*/), SoulFreezard,                     \
      ({ LocType::ABOVE_GROUND, LocType::NARROW_GROUND, LocType::UNDERWATER, LocType::SHALLOW_WATER }))           \
    X(ENEMY_WOLFOS, "Wolfos", ACTOR_WOLFOS, U16_ARR(0xFF00 /*normal*/, 0xFF01 /*white*/), SoulWolfos,             \
      ({ LocType::ABOVE_GROUND, LocType::SHALLOW_WATER, LocType::SPAWNER }))                                      \
    X(ENEMY_GUAY, "Guay", ACTOR_GUAY, U16_ARR(0x0000 /*normal*/, 0x0001 /*big*/), SoulGuay,                       \
      ({ LocType::ABOVE_GROUND, LocType::NARROW_GROUND, LocType::ABOVE_VOID, LocType::UNDERWATER,                 \
         LocType::ABOVE_WATER, LocType::SHALLOW_WATER }))
