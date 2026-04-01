// clang-format off
#include "item_location.hpp"

#include "dungeon.hpp"
#include "settings.hpp"
#include "spoiler_log.hpp"
#include "shops.hpp"
#include "debug.hpp"
#include "keys.hpp"

std::array<ItemLocation, KEY_ENUM_MAX> locationTable;

std::vector<LocationKey> KF_ShopLocations = {
    KF_SHOP_ITEM_1,
    KF_SHOP_ITEM_2,
    KF_SHOP_ITEM_3,
    KF_SHOP_ITEM_4,
    KF_SHOP_ITEM_5,
    KF_SHOP_ITEM_6,
    KF_SHOP_ITEM_7,
    KF_SHOP_ITEM_8,
};
std::vector<LocationKey> Kak_PotionShopLocations = {
    KAK_POTION_SHOP_ITEM_1,
    KAK_POTION_SHOP_ITEM_2,
    KAK_POTION_SHOP_ITEM_3,
    KAK_POTION_SHOP_ITEM_4,
    KAK_POTION_SHOP_ITEM_5,
    KAK_POTION_SHOP_ITEM_6,
    KAK_POTION_SHOP_ITEM_7,
    KAK_POTION_SHOP_ITEM_8,
};
std::vector<LocationKey> MK_BombchuShopLocations = {
    MARKET_BOMBCHU_SHOP_ITEM_1,
    MARKET_BOMBCHU_SHOP_ITEM_2,
    MARKET_BOMBCHU_SHOP_ITEM_3,
    MARKET_BOMBCHU_SHOP_ITEM_4,
    MARKET_BOMBCHU_SHOP_ITEM_5,
    MARKET_BOMBCHU_SHOP_ITEM_6,
    MARKET_BOMBCHU_SHOP_ITEM_7,
    MARKET_BOMBCHU_SHOP_ITEM_8,
};
std::vector<LocationKey> MK_PotionShopLocations = {
    MARKET_POTION_SHOP_ITEM_1,
    MARKET_POTION_SHOP_ITEM_2,
    MARKET_POTION_SHOP_ITEM_3,
    MARKET_POTION_SHOP_ITEM_4,
    MARKET_POTION_SHOP_ITEM_5,
    MARKET_POTION_SHOP_ITEM_6,
    MARKET_POTION_SHOP_ITEM_7,
    MARKET_POTION_SHOP_ITEM_8,
};
std::vector<LocationKey> MK_BazaarLocations = {
    MARKET_BAZAAR_ITEM_1,
    MARKET_BAZAAR_ITEM_2,
    MARKET_BAZAAR_ITEM_3,
    MARKET_BAZAAR_ITEM_4,
    MARKET_BAZAAR_ITEM_5,
    MARKET_BAZAAR_ITEM_6,
    MARKET_BAZAAR_ITEM_7,
    MARKET_BAZAAR_ITEM_8,
};
std::vector<LocationKey> Kak_BazaarLocations = {
    KAK_BAZAAR_ITEM_1,
    KAK_BAZAAR_ITEM_2,
    KAK_BAZAAR_ITEM_3,
    KAK_BAZAAR_ITEM_4,
    KAK_BAZAAR_ITEM_5,
    KAK_BAZAAR_ITEM_6,
    KAK_BAZAAR_ITEM_7,
    KAK_BAZAAR_ITEM_8,
};
std::vector<LocationKey> ZD_ShopLocations = {
    ZD_SHOP_ITEM_1,
    ZD_SHOP_ITEM_2,
    ZD_SHOP_ITEM_3,
    ZD_SHOP_ITEM_4,
    ZD_SHOP_ITEM_5,
    ZD_SHOP_ITEM_6,
    ZD_SHOP_ITEM_7,
    ZD_SHOP_ITEM_8,
};
std::vector<LocationKey> GC_ShopLocations = {
    GC_SHOP_ITEM_1,
    GC_SHOP_ITEM_2,
    GC_SHOP_ITEM_3,
    GC_SHOP_ITEM_4,
    GC_SHOP_ITEM_5,
    GC_SHOP_ITEM_6,
    GC_SHOP_ITEM_7,
    GC_SHOP_ITEM_8,
};
// List of shop location lists, used for shop shuffle
std::vector<std::vector<LocationKey>> ShopLocationLists = {
    KF_ShopLocations,
    Kak_PotionShopLocations,
    MK_BombchuShopLocations,
    MK_PotionShopLocations,
    MK_BazaarLocations,
    Kak_BazaarLocations,
    ZD_ShopLocations,
    GC_ShopLocations,
};

// List of gossip stone locations for hints
std::vector<LocationKey> gossipStoneLocations = {
    DMC_GOSSIP_STONE,
    DMT_GOSSIP_STONE,
    COLOSSUS_GOSSIP_STONE,
    DODONGOS_CAVERN_GOSSIP_STONE,
    GV_GOSSIP_STONE,
    GC_MAZE_GOSSIP_STONE,
    GC_MEDIGORON_GOSSIP_STONE,
    GRAVEYARD_GOSSIP_STONE,
    HC_MALON_GOSSIP_STONE,
    HC_ROCK_WALL_GOSSIP_STONE,
    HC_STORMS_GROTTO_GOSSIP_STONE,
    KF_DEKU_TREE_GOSSIP_STONE_LEFT,
    KF_DEKU_TREE_GOSSIP_STONE_RIGHT,
    KF_GOSSIP_STONE,
    LH_LAB_GOSSIP_STONE,
    LH_GOSSIP_STONE_SOUTHEAST,
    LH_GOSSIP_STONE_SOUTHWEST,
    LW_GOSSIP_STONE,
    SFM_MAZE_GOSSIP_STONE_LOWER,
    SFM_MAZE_GOSSIP_STONE_UPPER,
    SFM_SARIA_GOSSIP_STONE,
    TOT_GOSSIP_STONE_LEFT,
    TOT_GOSSIP_STONE_RIGHT,
    TOT_GOSSIP_STONE_RIGHT_CENTER,
    TOT_GOSSIP_STONE_LEFT_CENTER,
    ZD_GOSSIP_STONE,
    ZF_FAIRY_GOSSIP_STONE,
    ZF_JABU_GOSSIP_STONE,
    ZR_NEAR_GROTTOS_GOSSIP_STONE,
    ZR_NEAR_DOMAIN_GOSSIP_STONE,
    HF_COW_GROTTO_GOSSIP_STONE,
    HF_NEAR_MARKET_GROTTO_GOSSIP_STONE,
    HF_SOUTHEAST_GROTTO_GOSSIP_STONE,
    HF_OPEN_GROTTO_GOSSIP_STONE,
    KAK_OPEN_GROTTO_GOSSIP_STONE,
    ZR_OPEN_GROTTO_GOSSIP_STONE,
    KF_STORMS_GROTTO_GOSSIP_STONE,
    LW_NEAR_SHORTCUTS_GROTTO_GOSSIP_STONE,
    DMT_STORMS_GROTTO_GOSSIP_STONE,
    DMC_UPPER_GROTTO_GOSSIP_STONE,
};

std::vector<LocationKey> dungeonRewardLocations = {
    // Bosses
    QUEEN_GOHMA,
    KING_DODONGO,
    BARINADE,
    PHANTOM_GANON,
    VOLVAGIA,
    MORPHA,
    TWINROVA,
    BONGO_BONGO,
    LINKS_POCKET,
};
std::vector<LocationKey> overworldLocations = {
  // Kokiri Forest
  KF_KOKIRI_SWORD_CHEST,
  KF_MIDOS_TOP_LEFT_CHEST,
  KF_MIDOS_TOP_RIGHT_CHEST,
  KF_MIDOS_BOTTOM_LEFT_CHEST,
  KF_MIDOS_BOTTOM_RIGHT_CHEST,
  KF_STORMS_GROTTO_CHEST,
  KF_LINKS_HOUSE_COW,
  KF_END_OF_BRIDGE_BLUE_RUPEE,
  KF_BEHIND_MIDOS_HOUSE_BLUE_RUPEE,
  KF_BOULDER_MAZE_BLUE_RUPEE_1,
  KF_BOULDER_MAZE_BLUE_RUPEE_2,
  KF_NEAR_RAMP_GREEN_RUPEE_1,
  KF_NEAR_RAMP_GREEN_RUPEE_2,
  KF_NEAR_MIDOS_HOUSE_GREEN_RUPEE_1,
  KF_NEAR_MIDOS_HOUSE_GREEN_RUPEE_2,
  KF_RUPEE_CIRCLE_GREEN_RUPEE_1,
  KF_RUPEE_CIRCLE_GREEN_RUPEE_2,
  KF_RUPEE_CIRCLE_GREEN_RUPEE_3,
  KF_RUPEE_CIRCLE_GREEN_RUPEE_4,
  KF_RUPEE_CIRCLE_GREEN_RUPEE_5,
  KF_RUPEE_CIRCLE_GREEN_RUPEE_6,
  KF_RUPEE_CIRCLE_RED_RUPEE,

  // Shop
  KF_SHOP_ITEM_1,
  KF_SHOP_ITEM_2,
  KF_SHOP_ITEM_3,
  KF_SHOP_ITEM_4,
  KF_SHOP_ITEM_5,
  KF_SHOP_ITEM_6,
  KF_SHOP_ITEM_7,
  KF_SHOP_ITEM_8,

  // Lost Woods
  LW_GIFT_FROM_SARIA,
  LW_SKULL_KID,
  LW_TRADE_COJIRO,
  LW_TRADE_ODD_POULTICE,
  LW_OCARINA_MEMORY_GAME,
  LW_TARGET_IN_WOODS,
  LW_DEKU_SCRUB_NEAR_DEKU_THEATER_RIGHT,
  LW_DEKU_SCRUB_NEAR_DEKU_THEATER_LEFT,
  LW_DEKU_SCRUB_NEAR_BRIDGE,
  LW_IN_BOULDER_BLUE_RUPEE,
  LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_1,
  LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_2,
  LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_3,
  LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_4,
  LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_5,
  LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_6,
  LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_7,
  LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_8,
  LW_NEAR_SHORTCUTS_GROTTO_CHEST,
  LW_DEKU_SCRUB_GROTTO_REAR,
  LW_DEKU_SCRUB_GROTTO_FRONT,
  DEKU_THEATER_SKULL_MASK,
  DEKU_THEATER_MASK_OF_TRUTH,

  // Sacred Forest Meadow
  SONG_FROM_SARIA,
  SHEIK_IN_FOREST,
  SFM_WOLFOS_GROTTO_CHEST,
  SFM_DEKU_SCRUB_GROTTO_REAR,
  SFM_DEKU_SCRUB_GROTTO_FRONT,

  // Hyrule Field
  HF_SOUTHEAST_GROTTO_CHEST,
  HF_OPEN_GROTTO_CHEST,
  HF_NEAR_MARKET_GROTTO_CHEST,
  HF_OCARINA_OF_TIME_ITEM,
  SONG_FROM_OCARINA_OF_TIME,
  HF_TEKTITE_GROTTO_FREESTANDING_POH,
  HF_DEKU_SCRUB_GROTTO,
  HF_COW_GROTTO_COW,

  // Lake Hylia
  LH_CHILD_FISHING,
  LH_ADULT_FISHING,
  LH_LAB_DIVE,
  LH_TRADE_FROG,
  LH_UNDERWATER_ITEM,
  LH_SUN,
  LH_FREESTANDING_POH,
  LH_UNDER_WATER_GREEN_RUPEE_1,
  LH_UNDER_WATER_GREEN_RUPEE_2,
  LH_UNDER_WATER_GREEN_RUPEE_3,
  LH_LAB_DIVE_RED_RUPEE_1,
  LH_LAB_DIVE_RED_RUPEE_2,
  LH_LAB_DIVE_RED_RUPEE_3,
  LH_DEKU_SCRUB_GROTTO_LEFT,
  LH_DEKU_SCRUB_GROTTO_RIGHT,
  LH_DEKU_SCRUB_GROTTO_CENTER,

  // Gerudo Valley
  GV_CHEST,
  GV_TRADE_SAW,
  GV_WATERFALL_FREESTANDING_POH,
  GV_CRATE_FREESTANDING_POH,
  GV_DEKU_SCRUB_GROTTO_REAR,
  GV_DEKU_SCRUB_GROTTO_FRONT,
  GV_COW,
  GV_OCTOROCK_GROTTO_GREEN_RUPEE_1,
  GV_OCTOROCK_GROTTO_GREEN_RUPEE_2,
  GV_OCTOROCK_GROTTO_GREEN_RUPEE_3,
  GV_OCTOROCK_GROTTO_GREEN_RUPEE_4,
  GV_OCTOROCK_GROTTO_BLUE_RUPEE_1,
  GV_OCTOROCK_GROTTO_BLUE_RUPEE_2,
  GV_OCTOROCK_GROTTO_BLUE_RUPEE_3,
  GV_OCTOROCK_GROTTO_RED_RUPEE,

  // Gerudo Fortress
  GF_CHEST,
  GF_HBA_1000_POINTS,
  GF_HBA_1500_POINTS,
  GF_NORTH_F1_CARPENTER,
  GF_NORTH_F2_CARPENTER,
  GF_SOUTH_F1_CARPENTER,
  GF_SOUTH_F2_CARPENTER,
  GF_GERUDO_TOKEN,

  // Haunted Wasteland
  WASTELAND_CHEST,
  WASTELAND_BOMBCHU_SALESMAN,

  // Desert Colossus
  SHEIK_AT_COLOSSUS,
  COLOSSUS_FREESTANDING_POH,
  COLOSSUS_GREAT_FAIRY_REWARD,
  COLOSSUS_DEKU_SCRUB_GROTTO_REAR,
  COLOSSUS_DEKU_SCRUB_GROTTO_FRONT,

  // Market
  MARKET_TREASURE_CHEST_GAME_REWARD,
  MARKET_BOMBCHU_BOWLING_FIRST_PRIZE,
  MARKET_BOMBCHU_BOWLING_SECOND_PRIZE,
  MARKET_BOMBCHU_BOWLING_BOMBCHUS,
  MARKET_LOST_DOG,
  MARKET_SHOOTING_GALLERY_REWARD,
  MARKET_10_BIG_POES,
  MARKET_TREASURE_CHEST_GAME_ITEM_1,
  MARKET_TREASURE_CHEST_GAME_ITEM_2,
  MARKET_TREASURE_CHEST_GAME_ITEM_3,
  MARKET_TREASURE_CHEST_GAME_ITEM_4,
  MARKET_TREASURE_CHEST_GAME_ITEM_5,

  // Market Shops
  MARKET_BOMBCHU_SHOP_ITEM_1,
  MARKET_BOMBCHU_SHOP_ITEM_2,
  MARKET_BOMBCHU_SHOP_ITEM_3,
  MARKET_BOMBCHU_SHOP_ITEM_4,
  MARKET_BOMBCHU_SHOP_ITEM_5,
  MARKET_BOMBCHU_SHOP_ITEM_6,
  MARKET_BOMBCHU_SHOP_ITEM_7,
  MARKET_BOMBCHU_SHOP_ITEM_8,
  MARKET_POTION_SHOP_ITEM_1,
  MARKET_POTION_SHOP_ITEM_2,
  MARKET_POTION_SHOP_ITEM_3,
  MARKET_POTION_SHOP_ITEM_4,
  MARKET_POTION_SHOP_ITEM_5,
  MARKET_POTION_SHOP_ITEM_6,
  MARKET_POTION_SHOP_ITEM_7,
  MARKET_POTION_SHOP_ITEM_8,
  MARKET_BAZAAR_ITEM_1,
  MARKET_BAZAAR_ITEM_2,
  MARKET_BAZAAR_ITEM_3,
  MARKET_BAZAAR_ITEM_4,
  MARKET_BAZAAR_ITEM_5,
  MARKET_BAZAAR_ITEM_6,
  MARKET_BAZAAR_ITEM_7,
  MARKET_BAZAAR_ITEM_8,

  // Hyrule Castle
  HC_MALON_EGG,
  HC_ZELDAS_LETTER,
  SONG_FROM_IMPA,
  HC_GREAT_FAIRY_REWARD,
  OGC_GREAT_FAIRY_REWARD,

  // Temple of Time
  SHEIK_AT_TEMPLE,
  TOT_MASTER_SWORD,
  TOT_LIGHT_ARROWS_CUTSCENE,

  // Kakariko
  SHEIK_IN_KAKARIKO,
  KAK_REDEAD_GROTTO_CHEST,
  KAK_OPEN_GROTTO_CHEST,
  KAK_10_GOLD_SKULLTULA_REWARD,
  KAK_20_GOLD_SKULLTULA_REWARD,
  KAK_30_GOLD_SKULLTULA_REWARD,
  KAK_40_GOLD_SKULLTULA_REWARD,
  KAK_50_GOLD_SKULLTULA_REWARD,
  KAK_MAN_ON_ROOF,
  KAK_SHOOTING_GALLERY_REWARD,
  KAK_TRADE_ODD_MUSHROOM,
  KAK_GRANNYS_SHOP,
  KAK_ANJU_AS_CHILD,
  KAK_ANJU_AS_ADULT,
  KAK_TRADE_POCKET_CUCCO,
  KAK_IMPAS_HOUSE_FREESTANDING_POH,
  KAK_WINDMILL_FREESTANDING_POH,
  SONG_FROM_WINDMILL,
  KAK_IMPAS_HOUSE_COW,

  // Kakariko Shops
  KAK_POTION_SHOP_ITEM_1,
  KAK_POTION_SHOP_ITEM_2,
  KAK_POTION_SHOP_ITEM_3,
  KAK_POTION_SHOP_ITEM_4,
  KAK_POTION_SHOP_ITEM_5,
  KAK_POTION_SHOP_ITEM_6,
  KAK_POTION_SHOP_ITEM_7,
  KAK_POTION_SHOP_ITEM_8,
  KAK_BAZAAR_ITEM_1,
  KAK_BAZAAR_ITEM_2,
  KAK_BAZAAR_ITEM_3,
  KAK_BAZAAR_ITEM_4,
  KAK_BAZAAR_ITEM_5,
  KAK_BAZAAR_ITEM_6,
  KAK_BAZAAR_ITEM_7,
  KAK_BAZAAR_ITEM_8,

  // Graveyard
  GRAVEYARD_HOOKSHOT_CHEST,
  GRAVEYARD_SHIELD_GRAVE_CHEST,
  GRAVEYARD_HEART_PIECE_GRAVE_CHEST,
  GRAVEYARD_COMPOSERS_GRAVE_CHEST,
  SONG_FROM_COMPOSERS_GRAVE,
  GRAVEYARD_FREESTANDING_POH,
  GRAVEYARD_DAMPE_RACE_FREESTANDING_POH,
  GRAVEYARD_DAMPE_GRAVEDIGGING_TOUR,
  GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_1,
  GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_2,
  GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_3,
  GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_4,
  GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_5,
  GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_6,
  GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_7,
  GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_8,

  // Death Mountain Trail
  DMT_CHEST,
  DMT_STORMS_GROTTO_CHEST,
  DMT_TRADE_BROKEN_SWORD,
  DMT_TRADE_EYEDROPS,
  DMT_TRADE_CLAIM_CHECK,
  DMT_GREAT_FAIRY_REWARD,
  DMT_FREESTANDING_POH,
  DMT_COW_GROTTO_COW,
  DMT_ROCK_BLUE_RUPEE,
  DMT_ROCK_RED_RUPEE,
  DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_1,
  DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_2,
  DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_3,
  DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_4,
  DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_5,
  DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_6,
  DMT_COW_GROTTO_RUPEE_CIRCLE_RED_RUPEE,

  // Goron City
  GC_MAZE_LEFT_CHEST,
  GC_MAZE_CENTER_CHEST,
  GC_MAZE_RIGHT_CHEST,
  GC_ROLLING_GORON_AS_CHILD,
  GC_ROLLING_GORON_AS_ADULT,
  GC_DARUNIAS_JOY,
  GC_POT_FREESTANDING_POH,
  GC_DEKU_SCRUB_GROTTO_LEFT,
  GC_DEKU_SCRUB_GROTTO_RIGHT,
  GC_DEKU_SCRUB_GROTTO_CENTER,
  GC_MEDIGORON,

  // Goron City Shop
  GC_SHOP_ITEM_1,
  GC_SHOP_ITEM_2,
  GC_SHOP_ITEM_3,
  GC_SHOP_ITEM_4,
  GC_SHOP_ITEM_5,
  GC_SHOP_ITEM_6,
  GC_SHOP_ITEM_7,
  GC_SHOP_ITEM_8,

  // Death Mountain
  DMC_UPPER_GROTTO_CHEST,
  DMC_WALL_FREESTANDING_POH,
  DMC_VOLCANO_FREESTANDING_POH,
  SHEIK_IN_CRATER,
  DMC_DEKU_SCRUB,
  DMC_GREAT_FAIRY_REWARD,
  DMC_DEKU_SCRUB_GROTTO_LEFT,
  DMC_DEKU_SCRUB_GROTTO_RIGHT,
  DMC_DEKU_SCRUB_GROTTO_CENTER,
  DMC_LOWER_RED_RUPEE_1,
  DMC_LOWER_RED_RUPEE_2,
  DMC_LOWER_BLUE_RUPEE_1,
  DMC_LOWER_BLUE_RUPEE_2,
  DMC_LOWER_BLUE_RUPEE_3,
  DMC_LOWER_BLUE_RUPEE_4,
  DMC_LOWER_BLUE_RUPEE_5,
  DMC_LOWER_BLUE_RUPEE_6,
  DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_1,
  DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_2,
  DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_3,
  DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_4,
  DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_5,
  DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_6,
  DMC_SCARE_CROW_RUPEE_CIRCLE_RED_RUPEE,

  // Zoras River
  ZR_OPEN_GROTTO_CHEST,
  ZR_MAGIC_BEAN_SALESMAN,
  ZR_FROGS_ZELDAS_LULLABY,
  ZR_FROGS_EPONAS_SONG,
  ZR_FROGS_SARIAS_SONG,
  ZR_FROGS_SUNS_SONG,
  ZR_FROGS_SONG_OF_TIME,
  ZR_FROGS_IN_THE_RAIN,
  ZR_FROGS_OCARINA_GAME,
  ZR_NEAR_OPEN_GROTTO_FREESTANDING_POH,
  ZR_NEAR_DOMAIN_FREESTANDING_POH,
  ZR_DEKU_SCRUB_GROTTO_REAR,
  ZR_DEKU_SCRUB_GROTTO_FRONT,
  ZR_WATERFALL_RED_RUPEE_1,
  ZR_WATERFALL_RED_RUPEE_2,
  ZR_WATERFALL_RED_RUPEE_3,
  ZR_WATERFALL_RED_RUPEE_4,

  // Zoras Domain
  ZD_CHEST,
  ZD_DIVING_MINIGAME,
  ZD_KING_ZORA_THAWED,
  ZD_TRADE_PRESCRIPTION,

  // Zora's Domain Shop
  ZD_SHOP_ITEM_1,
  ZD_SHOP_ITEM_2,
  ZD_SHOP_ITEM_3,
  ZD_SHOP_ITEM_4,
  ZD_SHOP_ITEM_5,
  ZD_SHOP_ITEM_6,
  ZD_SHOP_ITEM_7,
  ZD_SHOP_ITEM_8,

  // Zoras Fountain
  ZF_ICEBERG_FREESTANDING_POH,
  ZF_BOTTOM_FREESTANDING_POH,
  ZF_GREAT_FAIRY_REWARD,
  ZF_UNDERWATER_GREEN_RUPEE_1,
  ZF_UNDERWATER_GREEN_RUPEE_2,
  ZF_UNDERWATER_GREEN_RUPEE_3,
  ZF_UNDERWATER_GREEN_RUPEE_4,
  ZF_UNDERWATER_GREEN_RUPEE_5,
  ZF_UNDERWATER_GREEN_RUPEE_6,
  ZF_UNDERWATER_GREEN_RUPEE_7,
  ZF_UNDERWATER_GREEN_RUPEE_8,
  ZF_UNDERWATER_GREEN_RUPEE_9,
  ZF_UNDERWATER_GREEN_RUPEE_10,
  ZF_UNDERWATER_GREEN_RUPEE_11,
  ZF_UNDERWATER_GREEN_RUPEE_12,
  ZF_UNDERWATER_GREEN_RUPEE_13,
  ZF_UNDERWATER_GREEN_RUPEE_14,
  ZF_UNDERWATER_GREEN_RUPEE_15,
  ZF_UNDERWATER_GREEN_RUPEE_16,
  ZF_UNDERWATER_GREEN_RUPEE_17,
  ZF_UNDERWATER_GREEN_RUPEE_18,

  // Lon Lon Ranch
  SONG_FROM_MALON,
  LLR_TALONS_CHICKENS,
  LLR_FREESTANDING_POH,
  LLR_DEKU_SCRUB_GROTTO_LEFT,
  LLR_DEKU_SCRUB_GROTTO_RIGHT,
  LLR_DEKU_SCRUB_GROTTO_CENTER,
  LLR_STABLES_LEFT_COW,
  LLR_STABLES_RIGHT_COW,
  LLR_TOWER_LEFT_COW,
  LLR_TOWER_RIGHT_COW,

  /*-------------------------------
     --- GOLD SKULLTULA TOKENS ---
    -------------------------------*/

  // Overworld
  KF_GS_BEAN_PATCH,
  KF_GS_KNOW_IT_ALL_HOUSE,
  KF_GS_HOUSE_OF_TWINS,

  LW_GS_BEAN_PATCH_NEAR_BRIDGE,
  LW_GS_BEAN_PATCH_NEAR_THEATER,
  LW_GS_ABOVE_THEATER,
  SFM_GS,

  HF_GS_COW_GROTTO,
  HF_GS_NEAR_KAK_GROTTO,

  LH_GS_BEAN_PATCH,
  LH_GS_SMALL_ISLAND,
  LH_GS_LAB_WALL,
  LH_GS_LAB_CRATE,
  LH_GS_TREE,

  GV_GS_BEAN_PATCH,
  GV_GS_SMALL_BRIDGE,
  GV_GS_PILLAR,
  GV_GS_BEHIND_TENT,

  GF_GS_ARCHERY_RANGE,
  GF_GS_TOP_FLOOR,

  WASTELAND_GS,
  COLOSSUS_GS_BEAN_PATCH,
  COLOSSUS_GS_HILL,
  COLOSSUS_GS_TREE,

  OGC_GS,
  HC_GS_STORMS_GROTTO,
  HC_GS_TREE,
  MARKET_GS_GUARD_HOUSE,

  KAK_GS_HOUSE_UNDER_CONSTRUCTION,
  KAK_GS_SKULLTULA_HOUSE,
  KAK_GS_GUARDS_HOUSE,
  KAK_GS_TREE,
  KAK_GS_WATCHTOWER,
  KAK_GS_ABOVE_IMPAS_HOUSE,

  DMC_GS_BEAN_PATCH,
  DMC_GS_CRATE,

  DMT_GS_BEAN_PATCH,
  DMT_GS_NEAR_KAK,
  DMT_GS_ABOVE_DODONGOS_CAVERN,
  DMT_GS_FALLING_ROCKS_PATH,

  GC_GS_CENTER_PLATFORM,
  GC_GS_BOULDER_MAZE,
  GRAVEYARD_GS_WALL,
  GRAVEYARD_GS_BEAN_PATCH,

  ZR_GS_LADDER,
  ZR_GS_TREE,
  ZR_GS_ABOVE_BRIDGE,
  ZR_GS_NEAR_RAISED_GROTTOS,

  ZD_GS_FROZEN_WATERFALL,
  ZF_GS_ABOVE_THE_LOG,
  ZF_GS_HIDDEN_CAVE,
  ZF_GS_TREE,

  LLR_GS_BACK_WALL,
  LLR_GS_RAIN_SHED,
  LLR_GS_HOUSE_WINDOW,
  LLR_GS_TREE,
};

std::vector<LocationKey> childOnlyHotLocations = {
    DMC_DEKU_SCRUB,
    DMC_GS_CRATE,
    DMC_GS_BEAN_PATCH,
    DMC_LOWER_RED_RUPEE_1,
    DMC_LOWER_RED_RUPEE_2,
    DMC_LOWER_BLUE_RUPEE_1,
    DMC_LOWER_BLUE_RUPEE_2,
    DMC_LOWER_BLUE_RUPEE_3,
    DMC_LOWER_BLUE_RUPEE_4,
    DMC_LOWER_BLUE_RUPEE_5,
    DMC_LOWER_BLUE_RUPEE_6,
};
// clang-format on

ItemLocation* Location(LocationKey locKey) {
    return &(locationTable[locKey]);
}

std::vector<LocationKey> allLocations          = {};
std::vector<LocationKey> everyPossibleLocation = {};

// set of overrides to write to the patch
std::set<ItemOverride, ItemOverride_Compare> overrides = {};

std::vector<std::vector<LocationKey>> playthroughLocations;
std::vector<LocationKey> wothLocations;
bool playthroughBeatable   = false;
bool allLocationsReachable = false;
bool showItemProgress      = false;

u16 itemsPlaced = 0;

void AddLocation(LocationKey loc, std::vector<LocationKey>* destination = &allLocations) {
    destination->push_back(loc);
}

template <typename Container>
void AddLocations(const Container& locations, std::vector<LocationKey>* destination = &allLocations) {
    destination->insert(destination->end(), std::cbegin(locations), std::cend(locations));
}

// sort through Vanilla and MQ dungeon locations
void GenerateLocationPool() {

    allLocations.clear();
    AddLocation(LINKS_POCKET);
    AddLocations(overworldLocations);

    if (Settings::TriforceHunt) {
        AddLocation(TRIFORCE_HUNT_GOAL);
    }

    for (auto dungeon : Dungeon::dungeonList) {
        AddLocations(dungeon->GetDungeonLocations());
    }
}

void PlaceItemInLocation(LocationKey locKey, ItemKey item, bool applyEffectImmediately /*= false*/,
                         bool setHidden /*= false*/) {
    auto loc = Location(locKey);
    PlacementLog_Msg("\n");
    PlacementLog_Msg(ItemTable(item).GetName().GetNAEnglish());
    PlacementLog_Msg(" placed at ");
    PlacementLog_Msg(loc->GetName());
    PlacementLog_Msg("\n\n");

    if (applyEffectImmediately || Settings::Logic.Is(LOGIC_NONE) || Settings::Logic.Is(LOGIC_VANILLA)) {
        ItemTable(item).ApplyEffect();
    }

    itemsPlaced++;
    if (showItemProgress) {
        double completion   = (double)itemsPlaced / (double)(allLocations.size() + dungeonRewardLocations.size());
        std::string message = "\x1b[8;10HPlacing Items.";
        message += completion > 0.25 ? "." : " ";
        message += completion > 0.50 ? "." : " ";
        printf("%s", message.c_str());
    }

    // If we're placing a non-shop item in a shop location, we want to record it for custom messages
    if (ItemTable(item).GetItemType() != ITEMTYPE_SHOP && loc->IsCategory(Category::cShop)) {
        int index                = TransformShopIndex(GetShopIndex(locKey));
        NonShopItems[index].Name = ItemTable(item).GetName();
        NonShopItems[index].Repurchaseable =
            ItemTable(item).GetItemType() == ITEMTYPE_REFILL || ItemTable(item).GetHintKey() == PROGRESSIVE_BOMBCHUS;
    }

    loc->SetPlacedItem(item);
    if (setHidden) {
        loc->SetHidden(true);
    }
}

std::vector<LocationKey> GetLocations(const std::vector<LocationKey>& locationPool, Category categoryInclude,
                                      Category categoryExclude /*= Category::cNull*/) {
    std::vector<LocationKey> locationsInCategory;
    for (LocationKey locKey : locationPool) {
        if (Location(locKey)->IsCategory(categoryInclude) && !Location(locKey)->IsCategory(categoryExclude)) {
            locationsInCategory.push_back(locKey);
        }
    }
    return locationsInCategory;
}

void LocationReset() {
    for (LocationKey il : allLocations) {
        Location(il)->RemoveFromPool();
    }

    for (LocationKey il : dungeonRewardLocations) {
        Location(il)->RemoveFromPool();
    }

    for (LocationKey il : gossipStoneLocations) {
        Location(il)->RemoveFromPool();
    }

    Location(GANONDORF_HINT)->RemoveFromPool();
}

void ItemReset() {
    for (LocationKey il : allLocations) {
        Location(il)->ResetVariables();
    }

    for (LocationKey il : dungeonRewardLocations) {
        Location(il)->ResetVariables();
    }

    itemsPlaced = 0;
}

void HintReset() {
    for (LocationKey il : gossipStoneLocations) {
        Location(il)->ResetVariables();
    }
}

// Fills everyPossibleLocation and creates an exclusion option for each location.
// everyPossibleLocation is used in the menu to lock/hide excluding locations
void AddExcludedOptions() {
    AddLocations(overworldLocations, &everyPossibleLocation);

    for (auto dungeon : Dungeon::dungeonList) {
        AddLocations(dungeon->GetEveryLocation(), &everyPossibleLocation);
    }

    for (LocationKey il : everyPossibleLocation) {
        Location(il)->AddExcludeOption();
    }
}

void CreateItemOverrides() {
    PlacementLog_Msg("NOW CREATING OVERRIDES\n\n");
    for (LocationKey locKey : allLocations) {
        auto loc               = Location(locKey);
        ItemOverride_Value val = ItemTable(loc->GetPlacedItemKey()).Value();
        // If this is an ice trap in a shop, change the name based on what the model will look like
        if (loc->GetPlacedItemKey() == ICE_TRAP && loc->IsCategory(Category::cShop)) {
            NonShopItems[TransformShopIndex(GetShopIndex(locKey))].Name = GetIceTrapName(val.looksLikeItemId);
        }
        overrides.insert({
            .key   = loc->Key(),
            .value = val,
        });
        PlacementLog_Msg("\tScene: ");
        PlacementLog_Msg(std::to_string(loc->Key().scene));
        PlacementLog_Msg("\tType: ");
        PlacementLog_Msg(std::to_string(loc->Key().type));
        PlacementLog_Msg("\tFlag:  ");
        PlacementLog_Msg(std::to_string(loc->Key().flag));
        PlacementLog_Msg("\t");
        PlacementLog_Msg(loc->GetName());
        PlacementLog_Msg(": ");
        PlacementLog_Msg(loc->GetPlacedItemName().GetNAEnglish());
        PlacementLog_Msg("\n");
    }
    PlacementLog_Msg("Overrides Created: ");
    PlacementLog_Msg(std::to_string(overrides.size()));
}
