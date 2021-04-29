#include "starting_inventory.hpp"

#include <unistd.h>

#include "debug.hpp"
#include "dungeon.hpp"
#include "item_list.hpp"
#include "settings.hpp"

using namespace Settings;
using namespace Dungeon;

std::vector<Item> StartingInventory;

static void AddItemToInventory(const Item& item, size_t count = 1) {
  StartingInventory.insert(StartingInventory.end(), count, item);
}

void GenerateStartingInventory() {
  StartingInventory.clear();

  if (MapsAndCompasses.Is(MAPSANDCOMPASSES_START_WITH)) {
    for (auto* dungeon : dungeonList) {
      if (dungeon->GetMap() != NoItem) {
        AddItemToInventory(dungeon->GetMap());
      }

      if (dungeon->GetCompass() != NoItem) {
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
      AddItemToInventory(SpiritTemple_SmallKey, 3);
    }
  }

  if (BossKeysanity.Is(BOSSKEYSANITY_START_WITH)) {
    AddItemToInventory(ForestTemple_BossKey);
    AddItemToInventory(FireTemple_BossKey);
    AddItemToInventory(WaterTemple_BossKey);
    AddItemToInventory(SpiritTemple_BossKey);
    AddItemToInventory(ShadowTemple_BossKey);
  }

  if (GanonsBossKey.Is(GANONSBOSSKEY_START_WITH)) {
    AddItemToInventory(GanonsCastle_BossKey);
  }

  //Starting Inventory Menu
  //Values are associated so that the count of items matches the index of
  //the option selected. If None is selected, the value will be zero and
  //zero of the item will be added to the starting inventory.
  AddItemToInventory(I_ProgressiveStickCapacity, StartingStickCapacity.Value<u8>());
  AddItemToInventory(I_ProgressiveNutCapacity,   StartingNutCapacity.Value<u8>());
  AddItemToInventory(I_ProgressiveBombBag,       StartingBombBag.Value<u8>());
  AddItemToInventory((BombchusInLogic ? I_ProgressiveBombchus : Bombchu20), StartingBombchus.Value<u8>());
  AddItemToInventory(I_ProgressiveBow,           StartingBow.Value<u8>());
  AddItemToInventory(I_FireArrows,               StartingFireArrows.Value<u8>());
  AddItemToInventory(I_IceArrows,                StartingIceArrows.Value<u8>());
  AddItemToInventory(I_LightArrows,              StartingLightArrows.Value<u8>());
  AddItemToInventory(I_DinsFire,                 StartingDinsFire.Value<u8>());
  AddItemToInventory(I_FaroresWind,              StartingFaroresWind.Value<u8>());
  AddItemToInventory(I_NayrusLove,               StartingNayrusLove.Value<u8>());
  AddItemToInventory(I_ProgressiveBulletBag,     StartingSlingshot.Value<u8>());
  AddItemToInventory(I_Boomerang,                StartingBoomerang.Value<u8>());
  AddItemToInventory(I_LensOfTruth,              StartingLensOfTruth.Value<u8>());
  AddItemToInventory(I_MagicBeanPack,            StartingMagicBean.Value<u8>());
  AddItemToInventory(I_MegatonHammer,            StartingMegatonHammer.Value<u8>());
  AddItemToInventory(I_ProgressiveHookshot,      StartingHookshot.Value<u8>());
  AddItemToInventory(I_IronBoots,                StartingIronBoots.Value<u8>());
  AddItemToInventory(I_HoverBoots,               StartingHoverBoots.Value<u8>());
  AddItemToInventory(I_EmptyBottle,              StartingBottle1.Value<u8>());
  AddItemToInventory(I_EmptyBottle,              StartingBottle2.Value<u8>());
  AddItemToInventory(I_EmptyBottle,              StartingBottle3.Value<u8>());
  AddItemToInventory((ZorasFountain.Is(ZORASFOUNTAIN_OPEN) ? I_EmptyBottle : I_RutosLetter), StartingRutoBottle.Value<u8>()); //Turn Ruto Bottle into an empty bottle if Open Zora's Fountain
  AddItemToInventory(I_ProgressiveOcarina,       StartingOcarina.Value<u8>());
  AddItemToInventory(I_ZeldasLullaby,            StartingZeldasLullaby.Value<u8>());
  AddItemToInventory(I_EponasSong,               StartingEponasSong.Value<u8>());
  AddItemToInventory(I_SariasSong,               StartingSariasSong.Value<u8>());
  AddItemToInventory(I_SunsSong,                 StartingSunsSong.Value<u8>());
  AddItemToInventory(I_SongOfTime,               StartingSongOfTime.Value<u8>());
  AddItemToInventory(I_SongOfStorms,             StartingSongOfStorms.Value<u8>());
  AddItemToInventory(I_MinuetOfForest,           StartingMinuetOfForest.Value<u8>());
  AddItemToInventory(I_BoleroOfFire,             StartingBoleroOfFire.Value<u8>());
  AddItemToInventory(I_SerenadeOfWater,          StartingSerenadeOfWater.Value<u8>());
  AddItemToInventory(I_RequiemOfSpirit,          StartingRequiemOfSpirit.Value<u8>());
  AddItemToInventory(I_NocturneOfShadow,         StartingNocturneOfShadow.Value<u8>());
  AddItemToInventory(I_PreludeOfLight,           StartingPreludeOfLight.Value<u8>());
  AddItemToInventory(I_KokiriSword,              StartingKokiriSword.Value<u8>());
  AddItemToInventory(I_BiggoronSword,            StartingBiggoronSword.Value<u8>());
  AddItemToInventory(I_DekuShield,               StartingDekuShield.Value<u8>());
  AddItemToInventory(I_HylianShield,             StartingHylianShield.Value<u8>());
  AddItemToInventory(I_MirrorShield,             StartingMirrorShield.Value<u8>());
  AddItemToInventory(I_GoronTunic,               StartingGoronTunic.Value<u8>());
  AddItemToInventory(I_ZoraTunic,                StartingZoraTunic.Value<u8>());
  AddItemToInventory(I_ProgressiveMagic,         StartingMagicMeter.Value<u8>());
  AddItemToInventory(I_ProgressiveStrength,      StartingStrength.Value<u8>());
  AddItemToInventory(I_ProgressiveScale,         StartingScale.Value<u8>());
  AddItemToInventory(I_ProgressiveWallet,        StartingWallet.Value<u8>());
  AddItemToInventory(I_ShardOfAgony,             StartingShardOfAgony.Value<u8>());
  AddItemToInventory(I_DoubleDefense,            StartingDoubleDefense.Value<u8>());
}

void ApplyStartingInventory() {
  for (Item& item : StartingInventory) {
    item.ApplyEffect();
  }
}
