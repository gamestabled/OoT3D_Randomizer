#include "z3D/z3D.h"
#include "settings.h"
#include "item_override.h"
#include "item_table.h"

typedef enum {
    SHOP_BAZAAR,
    SHOP_KOKIRI,
    SHOP_GORON,
    SHOP_ZORA,
    SHOP_KAKARIKO_POTION,
    SHOP_MARKET_POTION,
    SHOP_BOMBCHU,
    SHOP_HAPPY_MASK,
} Shops;

#define SHOP_MARKET_BAZAAR SHOP_BAZAAR
#define SHOP_KAKARIKO_BAZAAR SHOP_HAPPY_MASK

#define SCENE_BAZAAR 44

typedef enum {
    /* 00 */ SI_DEKU_NUTS_5,
    /* 01 */ SI_ARROWS_30,
    /* 02 */ SI_ARROWS_50,
    /* 03 */ SI_BOMBS_5_R25,
    /* 04 */ SI_DEKU_NUTS_10,
    /* 05 */ SI_DEKU_STICK,
    /* 06 */ SI_BOMBS_10,
    /* 07 */ SI_FISH,
    /* 08 */ SI_RED_POTION_R30,
    /* 09 */ SI_GREEN_POITION,
    /* 10 */ SI_BLUE_POTION,
    /* 11 */ SI_LONGSWORD,
    /* 12 */ SI_HYLIAN_SHIELD,
    /* 13 */ SI_DEKU_SHIELD,
    /* 14 */ SI_GORON_TUNIC,
    /* 15 */ SI_ZORA_TUNIC,
    /* 16 */ SI_HEART,
    /* 17 */ SI_MILK_BOTTLE,
    /* 18 */ SI_WEIRD_EGG,
    /* 19 */ SI_19,
    /* 20 */ SI_20,
    /* 21 */ SI_BOMBCHU_10_1,
    /* 22 */ SI_BOMBCHU_20_1,
    /* 23 */ SI_BOMBCHU_20_2,
    /* 24 */ SI_BOMBCHU_10_2,
    /* 25 */ SI_BOMBCHU_10_3,
    /* 26 */ SI_BOMBCHU_20_3,
    /* 27 */ SI_BOMBCHU_20_4,
    /* 28 */ SI_BOMBCHU_10_4,
    /* 29 */ SI_DEKU_SEEDS_30,
    /* 30 */ SI_KEATON_MASK,
    /* 31 */ SI_SPOOKY_MASK,
    /* 32 */ SI_SKULL_MASK,
    /* 33 */ SI_BUNNY_HOOD,
    /* 34 */ SI_MASK_OF_TRUTH,
    /* 35 */ SI_ZORA_MASK,
    /* 36 */ SI_GORON_MASK,
    /* 37 */ SI_GERUDO_MASK,
    /* 38 */ SI_SOLD_OUT,
    /* 39 */ SI_BLUE_FIRE,
    /* 40 */ SI_BUGS,
    /* 41 */ SI_BIG_POE,
    /* 42 */ SI_POE,
    /* 43 */ SI_FAIRY,
    /* 44 */ SI_ARROWS_10,
    /* 45 */ SI_BOMBS_20,
    /* 46 */ SI_BOMBS_30,
    /* 47 */ SI_BOMBS_5_R35,
    /* 48 */ SI_RED_POTION_R40,
    /* 49 */ SI_RED_POTION_R50,
    SI_MAX
} EnGirlA_ShopItems;

struct EnGirlA;
typedef void (*EnGirlAActionFunc)(struct EnGirlA*, GlobalContext*);

typedef struct EnGirlA {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ EnGirlAActionFunc actionFunc;
    /* 0x1A8 */ s8 objectSlot;
    /* 0x1A9 */ char unk_1A9[0x3];
    /* 0x1AC */ EnGirlAActionFunc actionFunc2;
    /* 0x1B0 */ s32 unk_1B0;
    /* 0x1B4 */ s16 itemBuyPromptTextId;
    /* 0x1B6 */ char unk_1B6[0x2];
    /* 0x1B8 */ s32 getItemId;
    /* 0x1BC */ s16 isInvisible;
    /* 0x1BE */ char unk_1BE[0x6];
    /* 0x1C4 */ void (*unk_1C4)(GlobalContext*, struct EnGirlA*);
    /* 0x1C8 */ s16 unk_1C8;
    /* 0x1CA */ s16 unk_1CA;
    /* 0x1CC */ s16 yRotation;
    /* 0x1CE */ char unk_1CE[0x2];
    /* 0x1D0 */ s32 (*canBuyFunc)(GlobalContext*, struct EnGirlA*);
    /* 0x1D4 */ void (*itemGiveFunc)(GlobalContext*, struct EnGirlA*);
    /* 0x1D8 */ void (*buyEventFunc)(GlobalContext*, struct EnGirlA*);
    /* 0x1DC */ s16 basePrice;
    /* 0x1DE */ s16 itemCount;
    /* 0x1E0 */ s16 cmbIndex;
    /* 0x1E2 */ char unk_1E2[0x6];
    /* 0x1E8 */ SkeletonAnimationModel* model;
    /* 0x1EC */ SkeletonAnimationModel* model2;
    /* 0x1F0 */ Vec3f modelPositionOffsets;
    /* 0x1FC */ f32 unk_1FC;
} EnGirlA; // size 0x200

typedef enum {
    CANBUY_RESULT_0,
    CANBUY_RESULT_1,
    CANBUY_RESULT_CANT_GET_NOW,
    CANBUY_RESULT_NEED_BOTTLE,
    CANBUY_RESULT_NEED_RUPEES,
    CANBUY_RESULT_CANT_GET_NOW_5
} EnGirlA_CanBuyResult;

typedef struct {
    EnGirlA super;
    s32 shopItemPosition;
    s32 getItemId; // or shop item ID for regular shop items
    ItemRow* itemRow;
    s16 rObjectSlot;
} ShopsanityItem;

typedef struct {
    /* 0x00 */ s16 objId;
    /* 0x02 */ s16 objModelIdx;
    /* 0x04 */ s16 objModelIdx2; // -1 if none
    /* 0x06 */ s16 cmabIndex;    // -1 if none
    /* 0x08 */ s16 cmabIndex2;   // -1 if none
    /* 0x0A */ s16 price;
    /* 0x0C */ s16 count;
    /* 0x0E */ u16 itemDescTextId;
    /* 0x10 */ u16 itemBuyPromptTextId;
    /* 0x14 */ s32 getItemId;
    /* 0x18 */ s32 (*canBuyFunc)(GlobalContext*, struct EnGirlA*);
    /* 0x1C */ void (*itemGiveFunc)(GlobalContext*, struct EnGirlA*);
    /* 0x20 */ void (*buyEventFunc)(GlobalContext*, struct EnGirlA*);
    /* 0x24 */ Vec3f modelPositionOffsets;
} ShopItemEntry; // size 0x30

#define EnGirlA_ShopItemEntries ((ShopItemEntry*)GAME_ADDR(0x524F50))

void ShopsanityItem_Init(Actor* itemx, GlobalContext* globalCtx);
void ShopsanityItem_SellOut(Actor* itemx, u16 index); // Used for multiplayer
void EnOssan_rDestroy(Actor* shopkeeperx, GlobalContext* globalCtx);
