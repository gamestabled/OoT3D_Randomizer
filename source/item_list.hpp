#pragma once
#include "logic.hpp"
#include <string>
#include <functional>
#include <vector>

#include "../code/src/item_override.h"

enum ItemType {
    ITEMTYPE_ITEM,
    ITEMTYPE_MAP,
    ITEMTYPE_COMPASS,
    ITEMTYPE_BOSSKEY,
    ITEMTYPE_SMALLKEY,
    ITEMTYPE_TOKEN,
    ITEMTYPE_FORTRESS_SMALLKEY,
    ITEMTYPE_EVENT,
    ITEMTYPE_DROP,
    ITEMTYPE_REFILL,
    ITEMTYPE_SONG,
    ITEMTYPE_SHOP,
    ITEMTYPE_DUNGEONREWARD
};

class Item {
public:
    using EffectFn = void (*)();

    Item(std::string name_, ItemType type_, int getItemId_, bool progressive_, EffectFn effect_, u16 price_ = 0)
        : name(std::move(name_)),
          type(type_),
          getItemId(getItemId_),
          progressive(progressive_),
          effect(effect_),
          price(price_) {}

    void ApplyEffect() {
        effect();
        Logic::UpdateHelpers();
        return;
    }

    ItemOverride_Value Value() const {
        ItemOverride_Value val;
        val.itemId = getItemId;
        return val;
    }

    std::string_view GetName() const {
        return name;
    }

    bool IsProgressive() const {
        return progressive;
    }

    int GetItemID() const {
        return getItemId;
    }

    ItemType GetItemType() const {
        return type;
    }

    u16 GetPrice() const {
        return price;
    }

private:
    std::string name;
    ItemType type;
    int  getItemId;
    bool progressive;
    EffectFn effect;
    u16  price;
};

//specific advancement items
extern Item A_KokiriSword;
extern Item A_BiggoronSword;
extern Item A_DekuShield;
extern Item A_HylianShield;
extern Item A_MirrorShield;
extern Item A_Boomerang;
extern Item A_ZeldasLetter;
extern Item A_WeirdEgg;
extern Item A_LensOfTruth;
extern Item A_MegatonHammer;
extern Item A_IronBoots;
extern Item A_HoverBoots;
extern Item A_ShardOfAgony;
extern Item A_DinsFire;
extern Item A_FaroresWind;
extern Item A_NayrusLove;
extern Item A_FireArrows;
extern Item A_IceArrows;
extern Item A_LightArrows;
extern Item A_GoronTunic;
extern Item A_ZoraTunic;
extern Item A_GerudoToken;
extern Item A_MagicBean;
extern Item A_MagicBeanPack;
extern Item A_DoubleDefense;

extern Item A_PocketEgg;
extern Item A_PocketCucco;
extern Item A_Cojiro;
extern Item A_OddMushroom;
extern Item A_OddPoultice;
extern Item A_PoachersSaw;
extern Item A_BrokenSword;
extern Item A_Prescription;
extern Item A_EyeballFrog;
extern Item A_Eyedrops;
extern Item A_ClaimCheck;

extern Item GoldSkulltulaToken;

//progressive items
extern Item A_ProgressiveHookshot;
extern Item A_ProgressiveStrength;
extern Item A_ProgressiveBombBag;
extern Item A_ProgressiveBombchus;
extern Item A_ProgressiveBow;
extern Item A_ProgressiveBulletBag;
extern Item A_ProgressiveWallet;
extern Item A_ProgressiveScale;
extern Item A_ProgressiveNutCapacity;
extern Item A_ProgressiveStickCapacity;
extern Item A_ProgressiveMagic;
extern Item A_ProgressiveOcarina;

//bottles
extern Item A_EmptyBottle;
extern Item A_MilkBottle;
extern Item A_RedPotionBottle;
extern Item A_GreenPotionBottle;
extern Item A_BluePotionBottle;
extern Item A_FairyBottle;
extern Item A_FishBottle;
extern Item A_BlueFireBottle;
extern Item A_BugsBottle;
extern Item A_PoeBottle;

//special bottles
extern Item A_RutosLetter;
extern Item A_BigPoeBottle;

//songs
extern Item A_ZeldasLullaby;
extern Item A_EponasSong;
extern Item A_SariasSong;
extern Item A_SunsSong;
extern Item A_SongOfTime;
extern Item A_SongOfStorms;
extern Item A_MinuetOfForest;
extern Item A_BoleroOfFire;
extern Item A_SerenadeOfWater;
extern Item A_RequiemOfSpirit;
extern Item A_NocturneOfShadow;
extern Item A_PreludeOfLight;

extern Item BuyDekuNut5;
extern Item BuyArrows30;
extern Item BuyArrows50;
extern Item BuyBombs525;
extern Item BuyDekuNut10;
extern Item BuyDekuStick1;
extern Item BuyBombs10;
extern Item BuyFish;
extern Item BuyRedPotion30;
extern Item BuyGreenPotion;
extern Item BuyBluePotion;
extern Item BuyHylianShield;
extern Item BuyDekuShield;
extern Item BuyGoronTunic;
extern Item BuyZoraTunic;
extern Item BuyHeart;
extern Item BuyBombchu10;
extern Item BuyBombchu20;
extern Item BuyBombchu5;
extern Item BuyDekuSeeds30;
extern Item SoldOut;
extern Item BuyBlueFire;
extern Item BuyBottleBug;
extern Item BuyPoe;
extern Item BuyFairysSpirit;
extern Item BuyArrows10;
extern Item BuyBombs20;
extern Item BuyBombs30;
extern Item BuyBombs535;
extern Item BuyRedPotion40;
extern Item BuyRedPotion50;

//maps and compasses
extern Item DekuTree_Map;
extern Item DodongosCavern_Map;
extern Item JabuJabusBelly_Map;
extern Item ForestTemple_Map;
extern Item FireTemple_Map;
extern Item WaterTemple_Map;
extern Item SpiritTemple_Map;
extern Item ShadowTemple_Map;
extern Item BottomOfTheWell_Map;
extern Item IceCavern_Map;

extern Item DekuTree_Compass;
extern Item DodongosCavern_Compass;
extern Item JabuJabusBelly_Compass;
extern Item ForestTemple_Compass;
extern Item FireTemple_Compass;
extern Item WaterTemple_Compass;
extern Item SpiritTemple_Compass;
extern Item ShadowTemple_Compass;
extern Item BottomOfTheWell_Compass;
extern Item IceCavern_Compass;

//small keys
extern Item ForestTemple_SmallKey;
extern Item FireTemple_SmallKey;
extern Item WaterTemple_SmallKey;
extern Item SpiritTemple_SmallKey;
extern Item ShadowTemple_SmallKey;
extern Item BottomOfTheWell_SmallKey;
extern Item GerudoTrainingGrounds_SmallKey;
extern Item GerudoFortress_SmallKey;
extern Item GanonsCastle_SmallKey;

//boss keys
extern Item ForestTemple_BossKey;
extern Item FireTemple_BossKey;
extern Item WaterTemple_BossKey;
extern Item SpiritTemple_BossKey;
extern Item ShadowTemple_BossKey;
extern Item GanonsCastle_BossKey;

extern Item A_KokiriEmerald;
extern Item A_GoronRuby;
extern Item A_ZoraSaphhire;
extern Item A_ForestMedallion;
extern Item A_FireMedallion;
extern Item A_WaterMedallion;
extern Item A_SpiritMedallion;
extern Item A_ShadowMedallion;
extern Item A_LightMedallion;

extern Item NoItem;
extern Item HeartContainer;

extern std::vector<Item *> PrePlacedItems;
extern std::vector<Item>   AdvancementItemPool;
extern std::vector<Item>   ItemPool;
extern std::array<Item, 9> dungeonRewards;
extern void GenerateItemPool();
extern void AddGreenRupee();
