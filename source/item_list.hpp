#pragma once
#include "logic.hpp"
#include "random.hpp"
#include <string>
#include <functional>
#include <variant>

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

    Item(std::string name_, ItemType type_, int getItemId_, bool advancement_, bool* logicVar_, u16 price_ = 0)
        : name(std::move(name_)),
          type(type_),
          getItemId(getItemId_),
          advancement(advancement_),
          logicVar(logicVar_),
          price(price_) {}

    Item(std::string name_, ItemType type_, int getItemId_, bool advancement_, u8* logicVar_, u16 price_ = 0)
        : name(std::move(name_)),
          type(type_),
          getItemId(getItemId_),
          advancement(advancement_),
          logicVar(logicVar_),
          price(price_) {}

    void ApplyEffect() {
        if (std::holds_alternative<bool*>(logicVar)) {
          *std::get<bool*>(logicVar) = true;
        } else {
          *std::get<u8*>(logicVar) += 1;
        }
        Logic::UpdateHelpers();
    }

    void UndoEffect() {
        if (std::holds_alternative<bool*>(logicVar)) {
          *std::get<bool*>(logicVar) = false;
        } else {
          *std::get<u8*>(logicVar) -= 1;
        }
        Logic::UpdateHelpers();
    }

    ItemOverride_Value Value() const {
        //just a random list of progression items
        const std::array<u16, 10> items = {
          GI_BOOMERANG,
          GI_HAMMER,
          GI_ARROW_LIGHT,
          0x80,
          0x81,
          0x82,
          0x83,
          0x84,
          0x85,
          0x8A,
        };

        ItemOverride_Value val;
        val.all = 0;
        val.itemId = getItemId;
        if (getItemId == GI_ICE_TRAP) {
            val.looksLikeItemId = items[Random() % items.size()];
        }
        return val;
    }

    std::string_view GetName() const {
        return name;
    }

    bool IsAdvancement() const {
        return advancement;
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

    bool operator== (const Item& right) const {
      return name == right.GetName();
    }

private:
    std::string name;
    ItemType type;
    int  getItemId;
    bool advancement;
    std::variant<bool*, u8*> logicVar;
    u16  price;
};

extern Item NoItem;
extern Item I_Triforce;

//specific advancement items
extern Item I_KokiriSword;
extern Item I_BiggoronSword;
extern Item I_DekuShield;
extern Item I_HylianShield;
extern Item I_MirrorShield;
extern Item I_Boomerang;
extern Item I_ZeldasLetter;
extern Item I_WeirdEgg;
extern Item I_LensOfTruth;
extern Item I_MegatonHammer;
extern Item I_IronBoots;
extern Item I_HoverBoots;
extern Item I_ShardOfAgony;
extern Item I_DinsFire;
extern Item I_FaroresWind;
extern Item I_NayrusLove;
extern Item I_FireArrows;
extern Item I_IceArrows;
extern Item I_LightArrows;
extern Item I_GoronTunic;
extern Item I_ZoraTunic;
extern Item I_GerudoToken;
extern Item I_MagicBean;
extern Item I_MagicBeanPack;
extern Item I_DoubleDefense;

extern Item I_PocketEgg;
extern Item I_PocketCucco;
extern Item I_Cojiro;
extern Item I_OddMushroom;
extern Item I_OddPoultice;
extern Item I_PoachersSaw;
extern Item I_BrokenSword;
extern Item I_Prescription;
extern Item I_EyeballFrog;
extern Item I_Eyedrops;
extern Item I_ClaimCheck;

extern Item GoldSkulltulaToken;

//progressive items
extern Item I_ProgressiveHookshot;
extern Item I_ProgressiveStrength;
extern Item I_ProgressiveBombBag;
extern Item I_ProgressiveBombchus;
extern Item I_ProgressiveBow;
extern Item I_ProgressiveBulletBag;
extern Item I_ProgressiveWallet;
extern Item I_ProgressiveScale;
extern Item I_ProgressiveNutCapacity;
extern Item I_ProgressiveStickCapacity;
extern Item I_ProgressiveMagic;
extern Item I_ProgressiveOcarina;

//bottles
extern Item I_EmptyBottle;
extern Item I_MilkBottle;
extern Item I_RedPotionBottle;
extern Item I_GreenPotionBottle;
extern Item I_BluePotionBottle;
extern Item I_FairyBottle;
extern Item I_FishBottle;
extern Item I_BlueFireBottle;
extern Item I_BugsBottle;
extern Item I_PoeBottle;

//special bottles
extern Item I_RutosLetter;
extern Item I_BigPoeBottle;

//songs
extern Item I_ZeldasLullaby;
extern Item I_EponasSong;
extern Item I_SariasSong;
extern Item I_SunsSong;
extern Item I_SongOfTime;
extern Item I_SongOfStorms;
extern Item I_MinuetOfForest;
extern Item I_BoleroOfFire;
extern Item I_SerenadeOfWater;
extern Item I_RequiemOfSpirit;
extern Item I_NocturneOfShadow;
extern Item I_PreludeOfLight;

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

//boss keys
extern Item ForestTemple_BossKey;
extern Item FireTemple_BossKey;
extern Item WaterTemple_BossKey;
extern Item SpiritTemple_BossKey;
extern Item ShadowTemple_BossKey;
extern Item GanonsCastle_BossKey;

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

//dungeon rewards
extern Item I_KokiriEmerald;
extern Item I_GoronRuby;
extern Item I_ZoraSaphhire;
extern Item I_ForestMedallion;
extern Item I_FireMedallion;
extern Item I_WaterMedallion;
extern Item I_SpiritMedallion;
extern Item I_ShadowMedallion;
extern Item I_LightMedallion;

//generic items
extern Item RecoveryHeart;
extern Item GreenRupee;
extern Item BlueRupee;
extern Item RedRupee;
extern Item PurpleRupee;
extern Item HugeRupee;
extern Item PieceOfHeart;
extern Item HeartContainer;
extern Item IceTrap;
extern Item Milk;
extern Item TreasureGameHeart;
extern Item TreasureGameGreenRupee;

//refills
extern Item Bombs5;
extern Item Bombs10;
extern Item Bombs20;
extern Item Bombchu5;
extern Item Bombchu10;
extern Item Bombchu20;
extern Item Arrows5;
extern Item Arrows10;
extern Item Arrows30;
extern Item DekuNuts5;
extern Item DekuNuts10;
extern Item DekuSeeds30;
extern Item DekuStick1;

//shop items
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
