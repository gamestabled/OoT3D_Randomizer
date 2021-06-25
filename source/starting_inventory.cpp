#include "starting_inventory.hpp"

#include <unistd.h>

#include "debug.hpp"
#include "dungeon.hpp"
#include "item_list.hpp"
#include "settings.hpp"

using namespace Settings;
using namespace Dungeon;

std::vector<ItemKey> StartingInventory;

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

  //Starting Inventory Menu
  //Values are associated so that the count of items matches the index of
  //the option selected. If None is selected, the value will be zero and
  //zero of the item will be added to the starting inventory.
  AddItemToInventory(PROGRESSIVE_STICK_UPGRADE, StartingStickCapacity.Value<u8>());
  AddItemToInventory(PROGRESSIVE_NUT_UPGRADE,   StartingNutCapacity.Value<u8>());
  AddItemToInventory(PROGRESSIVE_BOMB_BAG,      StartingBombBag.Value<u8>());
  AddItemToInventory((BombchusInLogic ? PROGRESSIVE_BOMBCHUS : BOMBCHU_20), StartingBombchus.Value<u8>());
  AddItemToInventory(PROGRESSIVE_BOW,           StartingBow.Value<u8>());
  AddItemToInventory(FIRE_ARROWS,               StartingFireArrows.Value<u8>());
  AddItemToInventory(ICE_ARROWS,                StartingIceArrows.Value<u8>());
  AddItemToInventory(LIGHT_ARROWS,              StartingLightArrows.Value<u8>());
  AddItemToInventory(DINS_FIRE,                 StartingDinsFire.Value<u8>());
  AddItemToInventory(FARORES_WIND,              StartingFaroresWind.Value<u8>());
  AddItemToInventory(NAYRUS_LOVE,               StartingNayrusLove.Value<u8>());
  AddItemToInventory(PROGRESSIVE_SLINGSHOT,     StartingSlingshot.Value<u8>());
  AddItemToInventory(BOOMERANG,                 StartingBoomerang.Value<u8>());
  AddItemToInventory(LENS_OF_TRUTH,             StartingLensOfTruth.Value<u8>());
  AddItemToInventory(MAGIC_BEAN_PACK,           StartingMagicBean.Value<u8>());
  AddItemToInventory(MEGATON_HAMMER,            StartingMegatonHammer.Value<u8>());
  AddItemToInventory(PROGRESSIVE_HOOKSHOT,      StartingHookshot.Value<u8>());
  AddItemToInventory(IRON_BOOTS,                StartingIronBoots.Value<u8>());
  AddItemToInventory(HOVER_BOOTS,               StartingHoverBoots.Value<u8>());
  AddItemToInventory(EMPTY_BOTTLE,              (StartingBottle1.Value<u8>()) ? 1 : 0);
  AddItemToInventory(EMPTY_BOTTLE,              (StartingBottle2.Value<u8>()) ? 1 : 0);
  AddItemToInventory(EMPTY_BOTTLE,              (StartingBottle3.Value<u8>()) ? 1 : 0);
  AddItemToInventory((ZorasFountain.Is(ZORASFOUNTAIN_OPEN) ? EMPTY_BOTTLE : RUTOS_LETTER), StartingRutoBottle.Value<u8>()); //Turn Ruto Bottle into an empty bottle if Open Zora's Fountain
  AddItemToInventory(PROGRESSIVE_OCARINA,       StartingOcarina.Value<u8>());
  AddItemToInventory(ZELDAS_LULLABY,            StartingZeldasLullaby.Value<u8>());
  AddItemToInventory(EPONAS_SONG,               StartingEponasSong.Value<u8>());
  AddItemToInventory(SARIAS_SONG,               StartingSariasSong.Value<u8>());
  AddItemToInventory(SUNS_SONG,                 StartingSunsSong.Value<u8>());
  AddItemToInventory(SONG_OF_TIME,              StartingSongOfTime.Value<u8>());
  AddItemToInventory(SONG_OF_STORMS,            StartingSongOfStorms.Value<u8>());
  AddItemToInventory(MINUET_OF_FOREST,          StartingMinuetOfForest.Value<u8>());
  AddItemToInventory(BOLERO_OF_FIRE,            StartingBoleroOfFire.Value<u8>());
  AddItemToInventory(SERENADE_OF_WATER,         StartingSerenadeOfWater.Value<u8>());
  AddItemToInventory(REQUIEM_OF_SPIRIT,         StartingRequiemOfSpirit.Value<u8>());
  AddItemToInventory(NOCTURNE_OF_SHADOW,        StartingNocturneOfShadow.Value<u8>());
  AddItemToInventory(PRELUDE_OF_LIGHT,          StartingPreludeOfLight.Value<u8>());
  AddItemToInventory(KOKIRI_SWORD,              StartingKokiriSword.Value<u8>());
  AddItemToInventory(BIGGORON_SWORD,            StartingBiggoronSword.Value<u8>());
  AddItemToInventory(DEKU_SHIELD,               StartingDekuShield.Value<u8>());
  AddItemToInventory(HYLIAN_SHIELD,             StartingHylianShield.Value<u8>());
  AddItemToInventory(MIRROR_SHIELD,             StartingMirrorShield.Value<u8>());
  AddItemToInventory(GORON_TUNIC,               StartingGoronTunic.Value<u8>());
  AddItemToInventory(ZORA_TUNIC,                StartingZoraTunic.Value<u8>());
  AddItemToInventory(PROGRESSIVE_MAGIC_METER,   StartingMagicMeter.Value<u8>());
  AddItemToInventory(PROGRESSIVE_STRENGTH,      StartingStrength.Value<u8>());
  AddItemToInventory(PROGRESSIVE_SCALE,         StartingScale.Value<u8>());
  AddItemToInventory(PROGRESSIVE_WALLET,        StartingWallet.Value<u8>());
  AddItemToInventory(SHARD_OF_AGONY,            StartingShardOfAgony.Value<u8>());
  AddItemToInventory(DOUBLE_DEFENSE,            StartingDoubleDefense.Value<u8>());
}

void ApplyStartingInventory() {
  for (ItemKey item : StartingInventory) {
    ItemTable(item).ApplyEffect();
  }
}
