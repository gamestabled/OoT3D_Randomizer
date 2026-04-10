#include "s_enemy_souls.h"

const char* const smallKeyStringForest  = "Forest Temple Small Key";
const char* const smallKeyStringFire    = "Fire Temple Small Key";
const char* const smallKeyStringWater   = "Water Temple Small Key";
const char* const smallKeyStringSpirit  = "Spirit Temple Small Key";
const char* const smallKeyStringShadow  = "Shadow Temple Small Key";
const char* const smallKeyStringBotW    = "Bottom of the Well Small Key";
const char* const smallKeyStringGTG     = "Training Grounds Small Key";
const char* const smallKeyStringHideout = "Gerudo Fortress Small Key";
const char* const smallKeyStringGanon   = "Ganon's Castle Small Key";
const char* const smallKeyStringGame    = "Chest Game Small Key";

const char* const keyRingStringForest  = "Forest Temple Key Ring";
const char* const keyRingStringFire    = "Fire Temple Key Ring";
const char* const keyRingStringWater   = "Water Temple Key Ring";
const char* const keyRingStringSpirit  = "Spirit Temple Key Ring";
const char* const keyRingStringShadow  = "Shadow Temple Key Ring";
const char* const keyRingStringBotW    = "Bottom of the Well Key Ring";
const char* const keyRingStringGTG     = "Training Grounds Key Ring";
const char* const keyRingStringHideout = "Gerudo Fortress Key Ring";
const char* const keyRingStringGanon   = "Ganon's Castle Key Ring";

// This array is included in the patch side for the enemy souls page in the in-game menu,
// and in the app side for the starting inventory options.
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
