#include "starting_inventory.hpp"

#include <unistd.h>

#include "debug.hpp"
#include "dungeon.hpp"
#include "item_list.hpp"
#include "settings.hpp"

using namespace Settings;
using namespace Dungeon;

std::vector<ItemKey> StartingInventory;
u8 AdditionalHeartContainers;

static void AddItemToInventory(ItemKey item, size_t count = 1) {
    StartingInventory.insert(StartingInventory.end(), count, item);
}

void GenerateStartingInventory() {
    StartingInventory.clear();

    if (MapsAndCompasses.Is(MAPSANDCOMPASSES_START_WITH)) {
        for (auto* dungeon : dungeonList) {
            if (dungeon->GetMap() != NONE) {
                AddItemToInventory(dungeon->GetMap());
            }

            if (dungeon->GetCompass() != NONE) {
                AddItemToInventory(dungeon->GetCompass());
            }
        }
    }

    if (Keysanity.Is(KEYSANITY_START_WITH)) {
        for (auto* dungeon : dungeonList) {
            if (dungeon->GetSmallKeyCount() > 0) {
                AddItemToInventory(dungeon->GetSmallKey(), dungeon->GetSmallKeyCount());
            }
        }
    } else if (Keysanity.Is(KEYSANITY_VANILLA)) {
        // Logic cannot handle vanilla key layout in some dungeons
        // this is because vanilla expects the dungeon major item to be
        // locked behind the keys, which is not always true in rando.
        // We can resolve this by starting with some extra keys
        // - OoT Randomizer
        if (SpiritTemple.IsMQ()) {
            AddItemToInventory(SPIRIT_TEMPLE_SMALL_KEY, 3);
        }
    }

    if (BossKeysanity.Is(BOSSKEYSANITY_START_WITH)) {
        AddItemToInventory(FOREST_TEMPLE_BOSS_KEY);
        AddItemToInventory(FIRE_TEMPLE_BOSS_KEY);
        AddItemToInventory(WATER_TEMPLE_BOSS_KEY);
        AddItemToInventory(SPIRIT_TEMPLE_BOSS_KEY);
        AddItemToInventory(SHADOW_TEMPLE_BOSS_KEY);
    }

    if (GanonsBossKey.Is(GANONSBOSSKEY_START_WITH)) {
        AddItemToInventory(GANONS_CASTLE_BOSS_KEY);
    }

    if (GerudoFortress.Is(GERUDOFORTRESS_OPEN) && !ShuffleGerudoToken) {
        AddItemToInventory(GERUDO_TOKEN);
    }

    // Starting Inventory Menu
    // Values are associated so that the count of items matches the index of
    // the option selected. If None is selected, the value will be zero and
    // zero of the item will be added to the starting inventory.
    AddItemToInventory(PROGRESSIVE_STICK_UPGRADE, StartingStickCapacity.Value<u8>());
    AddItemToInventory(PROGRESSIVE_NUT_UPGRADE, StartingNutCapacity.Value<u8>());
    AddItemToInventory(PROGRESSIVE_BOMB_BAG, StartingBombBag.Value<u8>());
    AddItemToInventory((BombchusInLogic ? PROGRESSIVE_BOMBCHUS : BOMBCHU_20), StartingBombchus.Value<u8>());
    AddItemToInventory(PROGRESSIVE_BOW, StartingBow.Value<u8>());
    AddItemToInventory(FIRE_ARROWS, StartingFireArrows.Value<u8>());
    AddItemToInventory(ICE_ARROWS, StartingIceArrows.Value<u8>());
    AddItemToInventory(LIGHT_ARROWS, StartingLightArrows.Value<u8>());
    AddItemToInventory(DINS_FIRE, StartingDinsFire.Value<u8>());
    AddItemToInventory(FARORES_WIND, StartingFaroresWind.Value<u8>());
    AddItemToInventory(NAYRUS_LOVE, StartingNayrusLove.Value<u8>());
    AddItemToInventory(PROGRESSIVE_SLINGSHOT, StartingSlingshot.Value<u8>());
    AddItemToInventory(BOOMERANG, StartingBoomerang.Value<u8>());
    AddItemToInventory(LENS_OF_TRUTH, StartingLensOfTruth.Value<u8>());
    AddItemToInventory(MAGIC_BEAN_PACK, StartingMagicBean.Value<u8>());
    AddItemToInventory(MEGATON_HAMMER, StartingMegatonHammer.Value<u8>());
    AddItemToInventory(PROGRESSIVE_HOOKSHOT, StartingHookshot.Value<u8>());
    AddItemToInventory(IRON_BOOTS, StartingIronBoots.Value<u8>());
    AddItemToInventory(HOVER_BOOTS, StartingHoverBoots.Value<u8>());
    // For starting bottles, we need to check if they are a big poe and add that if so
    //  since a big poe bottle is not logically equivalent to an empty bottle.
    if (StartingBottle1.Value<u8>() == STARTINGBOTTLE_BIG_POE) {
        AddItemToInventory(BOTTLE_WITH_BIG_POE, 1);
    } else if (StartingBottle1.Value<u8>()) {
        AddItemToInventory(EMPTY_BOTTLE, 1);
    }
    if (StartingBottle2.Value<u8>() == STARTINGBOTTLE_BIG_POE) {
        AddItemToInventory(BOTTLE_WITH_BIG_POE, 1);
    } else if (StartingBottle2.Value<u8>()) {
        AddItemToInventory(EMPTY_BOTTLE, 1);
    }
    if (StartingBottle3.Value<u8>() == STARTINGBOTTLE_BIG_POE) {
        AddItemToInventory(BOTTLE_WITH_BIG_POE, 1);
    } else if (StartingBottle3.Value<u8>()) {
        AddItemToInventory(EMPTY_BOTTLE, 1);
    }
    if (StartingBottle4.Value<u8>() == STARTINGBOTTLE_BIG_POE) {
        AddItemToInventory(BOTTLE_WITH_BIG_POE, 1);
    } else if (StartingBottle4.Value<u8>()) {
        AddItemToInventory(EMPTY_BOTTLE, 1);
    }
    AddItemToInventory(RUTOS_LETTER, StartingRutoBottle.Value<u8>());
    // AddItemToInventory(BUNNY_HOOD, StartingChildTrade.Value<u8>());

    AddItemToInventory(PROGRESSIVE_OCARINA, StartingOcarina.Value<u8>());
    AddItemToInventory(ZELDAS_LULLABY, StartingZeldasLullaby.Value<u8>());
    AddItemToInventory(EPONAS_SONG, StartingEponasSong.Value<u8>());
    AddItemToInventory(SARIAS_SONG, StartingSariasSong.Value<u8>());
    AddItemToInventory(SUNS_SONG, StartingSunsSong.Value<u8>());
    AddItemToInventory(SONG_OF_TIME, StartingSongOfTime.Value<u8>());
    AddItemToInventory(SONG_OF_STORMS, StartingSongOfStorms.Value<u8>());
    AddItemToInventory(MINUET_OF_FOREST, StartingMinuetOfForest.Value<u8>());
    AddItemToInventory(BOLERO_OF_FIRE, StartingBoleroOfFire.Value<u8>());
    AddItemToInventory(SERENADE_OF_WATER, StartingSerenadeOfWater.Value<u8>());
    AddItemToInventory(REQUIEM_OF_SPIRIT, StartingRequiemOfSpirit.Value<u8>());
    AddItemToInventory(NOCTURNE_OF_SHADOW, StartingNocturneOfShadow.Value<u8>());
    AddItemToInventory(PRELUDE_OF_LIGHT, StartingPreludeOfLight.Value<u8>());
    AddItemToInventory(KOKIRI_SWORD, StartingKokiriSword.Value<u8>());
    AddItemToInventory(MASTER_SWORD, StartingMasterSword.Value<u8>());
    if (ProgressiveGoronSword) {
        AddItemToInventory(PROGRESSIVE_GORONSWORD, StartingBiggoronSword.Value<u8>());
    } else {
        AddItemToInventory(GIANTS_KNIFE, (StartingBiggoronSword.Is(STARTINGBGS_GIANTS_KNIFE)) ? 1 : 0);
        AddItemToInventory(BIGGORON_SWORD, (StartingBiggoronSword.Is(STARTINGBGS_BIGGORON_SWORD)) ? 1 : 0);
    }
    AddItemToInventory(DEKU_SHIELD, StartingDekuShield.Value<u8>());
    AddItemToInventory(HYLIAN_SHIELD, StartingHylianShield.Value<u8>());
    AddItemToInventory(MIRROR_SHIELD, StartingMirrorShield.Value<u8>());
    AddItemToInventory(GORON_TUNIC, StartingGoronTunic.Value<u8>());
    AddItemToInventory(ZORA_TUNIC, StartingZoraTunic.Value<u8>());
    AddItemToInventory(PROGRESSIVE_MAGIC_METER, StartingMagicMeter.Value<u8>());
    AddItemToInventory(PROGRESSIVE_STRENGTH, StartingStrength.Value<u8>());
    AddItemToInventory(PROGRESSIVE_SCALE, StartingScale.Value<u8>());
    AddItemToInventory(PROGRESSIVE_WALLET, StartingWallet.Value<u8>());
    AddItemToInventory(SHARD_OF_AGONY, StartingShardOfAgony.Value<u8>());
    AddItemToInventory(DOUBLE_DEFENSE, StartingDoubleDefense.Value<u8>());
    AddItemToInventory(KOKIRI_EMERALD, StartingKokiriEmerald.Value<u8>());
    AddItemToInventory(GORON_RUBY, StartingGoronRuby.Value<u8>());
    AddItemToInventory(ZORA_SAPPHIRE, StartingZoraSapphire.Value<u8>());
    AddItemToInventory(FOREST_MEDALLION, StartingForestMedallion.Value<u8>());
    AddItemToInventory(FIRE_MEDALLION, StartingFireMedallion.Value<u8>());
    AddItemToInventory(WATER_MEDALLION, StartingWaterMedallion.Value<u8>());
    AddItemToInventory(SPIRIT_MEDALLION, StartingSpiritMedallion.Value<u8>());
    AddItemToInventory(SHADOW_MEDALLION, StartingShadowMedallion.Value<u8>());
    AddItemToInventory(LIGHT_MEDALLION, StartingLightMedallion.Value<u8>());
    AddItemToInventory(GOLD_SKULLTULA_TOKEN, StartingSkulltulaToken.Value<u8>());

    s8 hearts                 = StartingHearts.Value<u8>() - 3;
    AdditionalHeartContainers = 0;
    if (hearts < 0) {
        AddItemToInventory(PIECE_OF_HEART, 4);
        // Plentiful and minimal have less than 4 standard pieces of heart so also replace the winner heart
        if (ItemPoolValue.Is(ITEMPOOL_PLENTIFUL) || ItemPoolValue.Is(ITEMPOOL_MINIMAL)) {
            AddItemToInventory(TREASURE_GAME_HEART);
        }

        AdditionalHeartContainers = 1 - hearts;
    } else if (hearts > 0) {
        // 16 containers in plentiful, 8 in balanced and 0 in the others
        u8 maxContainers = 8 * std::max(0, ItemPoolValue.Value<u8>() - 1);

        if (hearts <= maxContainers) {
            AddItemToInventory(HEART_CONTAINER, hearts);
        } else {
            AddItemToInventory(HEART_CONTAINER, maxContainers);
            AddItemToInventory(PIECE_OF_HEART, (hearts - maxContainers) * 4);
        }

        if (hearts == 17) {
            AddItemToInventory(TREASURE_GAME_HEART);
        }
    }

    AddItemToInventory(OCA_BUTTON_ITEM_L, StartingOcarinaButtonL.Value<u8>());
    AddItemToInventory(OCA_BUTTON_ITEM_R, StartingOcarinaButtonR.Value<u8>());
    AddItemToInventory(OCA_BUTTON_ITEM_X, StartingOcarinaButtonX.Value<u8>());
    AddItemToInventory(OCA_BUTTON_ITEM_Y, StartingOcarinaButtonY.Value<u8>());
    AddItemToInventory(OCA_BUTTON_ITEM_A, StartingOcarinaButtonA.Value<u8>());
}

bool StartingInventoryHasBottle() {
    ItemKey bottle = EMPTY_BOTTLE;
    return ElementInContainer(bottle, StartingInventory);
}

void ApplyStartingInventory() {
    for (ItemKey item : StartingInventory) {
        if (item == PIECE_OF_HEART || item == HEART_CONTAINER || item == TREASURE_GAME_HEART)
            continue;

        ItemTable(item).ApplyEffect();
    }
}
