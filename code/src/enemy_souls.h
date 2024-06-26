#ifndef _ENEMYSOULS_H_
#define _ENEMYSOULS_H_

#include "../include/z3D/z3D.h"

typedef enum EnemySoulId {
    SOUL_NONE = -1,
    SOUL_POE,
    SOUL_OCTOROK,
    SOUL_KEESE,
    SOUL_TEKTITE,
    SOUL_LEEVER,
    SOUL_PEAHAT,
    SOUL_LIZALFOS,
    SOUL_SHABOM,
    SOUL_BIRI_BARI,
    SOUL_TAILPASARAN,
    SOUL_SKULLTULA,
    SOUL_TORCH_SLUG,
    SOUL_STINGER,
    SOUL_MOBLIN,
    SOUL_ARMOS,
    SOUL_DEKU_BABA,
    SOUL_BUBBLE,
    SOUL_FLYING_TRAP,
    SOUL_BEAMOS,
    SOUL_WALLMASTER,
    SOUL_REDEAD_GIBDO,
    SOUL_SHELL_BLADE,
    SOUL_LIKE_LIKE,
    SOUL_TENTACLE,
    SOUL_ANUBIS,
    SOUL_SPIKE,
    SOUL_SKULL_KID,
    SOUL_FREEZARD,
    SOUL_DEKU_SCRUB,
    SOUL_WOLFOS,
    SOUL_STALCHILD,
    SOUL_GUAY,
    SOUL_DOOR_MIMIC,
    SOUL_STALFOS,
    SOUL_DARK_LINK,
    SOUL_FLARE_DANCER,
    SOUL_DEAD_HAND,
    SOUL_GERUDO,
    SOUL_GOHMA,
    SOUL_DODONGO,
    SOUL_BARINADE,
    SOUL_PHANTOM_GANON,
    SOUL_VOLVAGIA,
    SOUL_MORPHA,
    SOUL_BONGO_BONGO,
    SOUL_TWINROVA,
    SOUL_GANON,
    SOUL_MAX,
} EnemySoulId;

typedef struct SoulMenuInfo {
    EnemySoulId soulId;
    const char* name;
    const char* altName;
} SoulMenuInfo;

extern SoulMenuInfo SoulMenuNames[SOUL_MAX];

// This array is used in the patch side for the enemy souls page in the in-game menu,
// and in the app side for the starting inventory options.
// So CREATE_SOULMENUNAMES should only be defined in one C file and one CPP file.
#ifdef CREATE_SOULMENUNAMES
SoulMenuInfo SoulMenuNames[SOUL_MAX] = {
    // Normal enemies, ordered alphabetically
    { SOUL_ANUBIS, "Anubis" },
    { SOUL_ARMOS, "Armos" },
    { SOUL_BEAMOS, "Beamos" },
    { SOUL_BIRI_BARI, "Biri, Bari" },
    { SOUL_BUBBLE, "Bubble (all)" },
    { SOUL_DARK_LINK, "Dark Link" },
    { SOUL_DEAD_HAND, "Dead Hand" },
    { SOUL_DEKU_BABA, "Deku Baba (all)" },
    { SOUL_DEKU_SCRUB, "Deku Scrub (all)" },
    { SOUL_DOOR_MIMIC, "Door Mimic" },
    { SOUL_FLARE_DANCER, "Flare Dancer" },
    { SOUL_FLYING_TRAP, "Flying Pot & Tile" },
    { SOUL_FREEZARD, "Freezard" },
    { SOUL_GERUDO, "Gerudo, Iron Knuckles" },
    { SOUL_GUAY, "Guay" },
    { SOUL_KEESE, "Keese (all)" },
    { SOUL_LEEVER, "Leever" },
    { SOUL_LIKE_LIKE, "Like Like" },
    { SOUL_LIZALFOS, "Lizalfos, Dinolfos" },
    { SOUL_MOBLIN, "Moblin, Club Moblin" },
    { SOUL_OCTOROK, "Octorok, Big Octo" },
    { SOUL_TENTACLE, "Parasitic Tentacle" },
    { SOUL_PEAHAT, "Peahat" },
    { SOUL_POE, "Poe (all)" },
    { SOUL_REDEAD_GIBDO, "ReDead, Gibdo" },
    { SOUL_SHABOM, "Shabom" },
    { SOUL_SHELL_BLADE, "Shell Blade" },
    { SOUL_SKULL_KID, "Skull Kid" },
    { SOUL_SKULLTULA, "Skulltula (all)" },
    { SOUL_SPIKE, "Spike" },
    { SOUL_STALCHILD, "Stalchild" },
    { SOUL_STALFOS, "Stalfos" },
    { SOUL_STINGER, "Stinger" },
    { SOUL_TAILPASARAN, "Tailpasaran" },
    { SOUL_TEKTITE, "Tektite" },
    { SOUL_TORCH_SLUG, "Torch Slug" },
    { SOUL_WALLMASTER, "Wallmaster, Floormaster" },
    { SOUL_WOLFOS, "Wolfos (all)" },
    // Bosses
    { SOUL_GOHMA, "Gohma, Gohma Larva", "Queen Gohma" },
    { SOUL_DODONGO, "Dodongo (all)", "King Dodongo" },
    { SOUL_BARINADE, "Barinade" },
    { SOUL_PHANTOM_GANON, "Phantom Ganon" },
    { SOUL_VOLVAGIA, "Volvagia" },
    { SOUL_MORPHA, "Morpha" },
    { SOUL_BONGO_BONGO, "Bongo Bongo" },
    { SOUL_TWINROVA, "Twinrova" },
    { SOUL_GANON, "Ganondorf, Ganon" },
};
#endif

u8 EnemySouls_GetSoulFlag(EnemySoulId soulId);
void EnemySouls_SetSoulFlag(EnemySoulId soulId);
u8 EnemySouls_CheckSoulForActor(Actor* actor);

#endif //_ENEMYSOULS_H_
