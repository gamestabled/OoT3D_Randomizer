#include "hints.hpp"

#include "custom_messages.hpp"
#include "dungeon.hpp"
#include "item_location.hpp"
#include "item_pool.hpp"
#include "location_access.hpp"
#include "logic.hpp"
#include "random.hpp"
#include "spoiler_log.hpp"
#include "fill.hpp"
#include "hints.hpp"
#include "hint_list.hpp"

using namespace CustomMessages;
using namespace Logic;
using namespace Settings;

static Exit* GetHintRegion(Exit* exit) {
  std::vector<Exit*> alreadyChecked = {};
  std::vector<Exit*> spotQueue = {exit};

  while (!spotQueue.empty()) {
    Exit* region = spotQueue.back();
    alreadyChecked.push_back(region);
    spotQueue.pop_back();

    if (region->hintText != &Hints::NoHintText) {
      return region;
    }

    //add unchecked exits to spot queue
    bool checked = false;
    for (auto exitPair : region->exits) {
      Exit* e = exitPair.GetExit();

      for (Exit* checkedExit : alreadyChecked) {
        if (e == checkedExit) {
          checked = true;
          break;
        }
      }

      if (!checked) {
        spotQueue.insert(spotQueue.begin(), e);
      }
    }
  }

  return &Exits::NoExit;
}

static std::vector<ItemLocation*> GetAccessibleGossipStones(ItemLocation** hintedLocation) {
  //temporarily remove the hinted location's item, and then perform a
  //reachability search for gossip stone locations. Also for some reason
  //the address of the hinted location reference is necessary for this
  //code to work correctly
  Item originalItem = (*hintedLocation)->GetPlacedItem();
  (*hintedLocation)->SetPlacedItem(NoItem);
  (*hintedLocation)->SetDelayedItem(originalItem);

  LogicReset();
  std::vector<ItemLocation*> accessibleGossipStones = GetAccessibleLocations(gossipStoneLocations);

  return accessibleGossipStones;
}

static void AddHint(Text hint, ItemLocation* gossipStone, const std::vector<u8>& colors = {}) {
  //save hints as dummy items to gossip stone locations for writing to the spoiler log
  bool none = false;
  gossipStone->SetPlacedItem(Item{hint.GetEnglish(), ITEMTYPE_EVENT, GI_RUPEE_BLUE_LOSE, false, &none, &Hints::NoHintText});

  //create the in game message
  u32 messageId = 0x400 + gossipStone->GetFlag();
  CreateMessageFromTextObject(messageId, 0, 2, 3, AddColorsAndFormat(hint, colors));
}

static void CreateLocationHint(std::vector<ItemLocation*> possibleHintLocations) {
  //return if there aren't any hintable locations or gossip stones available
  if (possibleHintLocations.empty()) {
    PlacementLog_Msg("\tNO LOCATIONS TO HINT\n\n");
    return;
  }

  ItemLocation* hintedLocation = RandomElement(possibleHintLocations, false);
  std::vector<ItemLocation*> accessibleGossipStones = GetAccessibleGossipStones(&hintedLocation);
  hintedLocation->SaveDelayedItem();

  PlacementLog_Msg("\tLocation: ");
  PlacementLog_Msg(hintedLocation->GetName());
  PlacementLog_Msg("\n");

  PlacementLog_Msg("\tItem: ");
  PlacementLog_Msg(hintedLocation->GetPlacedItemName());
  PlacementLog_Msg("\n");

  if (accessibleGossipStones.empty()) {
    PlacementLog_Msg("\tNO GOSSIP STONES TO PLACE HINT\n\n");
    return;
  }

  ItemLocation* gossipStone = RandomElement(accessibleGossipStones, false);
  hintedLocation->SetAsHinted();

  //make hint text
  Text locationHintText = hintedLocation->GetHintText().GetText();
  Text itemHintText = hintedLocation->GetPlacedItem().GetHintText().GetText();
  Text prefix = Hints::Prefix.GetText();

  Text finalHint = prefix + locationHintText + " #"+itemHintText+"#.";
  PlacementLog_Msg("\tMessage: ");
  PlacementLog_Msg(finalHint.english);
  PlacementLog_Msg("\n\n");
  AddHint(finalHint, gossipStone, {QM_GREEN, QM_RED});
}

static void CreateWothHint(u8* remainingDungeonWothHints) {
  //get locations that are in the current playthrough
  std::vector<ItemLocation*> possibleHintLocations = {};
  //iterate through playthrough locations by sphere
  for (std::vector<ItemLocation*> sphere : playthroughLocations) {
    std::vector<ItemLocation*> sphereHintLocations = FilterFromPool(sphere, [remainingDungeonWothHints](ItemLocation* loc){
      return loc->IsHintable()  && //only filter hintable locations
            !loc->IsHintedAt()  && //only filter locations that haven't been hinted at
            (loc->IsOverworld() || (loc->IsDungeon() && (*remainingDungeonWothHints) > 0)); //make sure we haven't surpassed the woth dungeon limit
    });
    AddElementsToPool(possibleHintLocations, sphereHintLocations);
  }

  //If no more locations can be hinted at for woth, then just try to get another hint
  if (possibleHintLocations.empty()) {
    PlacementLog_Msg("\tNO LOCATIONS TO HINT\n\n");
    return;
  }
  ItemLocation* hintedLocation = RandomElement(possibleHintLocations, false);

  PlacementLog_Msg("\tLocation: ");
  PlacementLog_Msg(hintedLocation->GetName());
  PlacementLog_Msg("\n");

  PlacementLog_Msg("\tItem: ");
  PlacementLog_Msg(hintedLocation->GetPlacedItemName());
  PlacementLog_Msg("\n");

  //get an accessible gossip stone
  std::vector<ItemLocation*> gossipStoneLocations = GetAccessibleGossipStones(&hintedLocation);
  hintedLocation->SaveDelayedItem();
  if (gossipStoneLocations.empty()) {
    PlacementLog_Msg("\tNO GOSSIP STONES TO PLACE HINT\n\n");
    return;
  }
  hintedLocation->SetAsHinted();
  ItemLocation* gossipStone = RandomElement(gossipStoneLocations, false);

  //form hint text
  Text locationText = Text{"","",""};
  if (hintedLocation->IsDungeon()) {
    *remainingDungeonWothHints -= 1;
    locationText = hintedLocation->GetParentRegion()->hintText->GetText();
  } else {
    locationText = GetHintRegion(hintedLocation->GetParentRegion())->hintText->GetText();
  }
  Text finalWothHint = Hints::Prefix.GetText()+"#"+locationText+"#"+Hints::WayOfTheHero.GetText();
  PlacementLog_Msg("\tMessage: ");
  PlacementLog_Msg(finalWothHint.english);
  PlacementLog_Msg("\n\n");
  AddHint(finalWothHint, gossipStone, {QM_LBLUE});
}

static void CreateBarrenHint(u8* remainingDungeonBarrenHints, std::vector<ItemLocation*>& barrenLocations) {
  //remove dungeon locations if necessary
  if (*remainingDungeonBarrenHints < 1) {
    barrenLocations = FilterFromPool(barrenLocations, [](ItemLocation* loc){return !loc->IsDungeon();});
  }

  if (barrenLocations.empty()) {
    return;
  }

  ItemLocation* hintedLocation = RandomElement(barrenLocations, true);

  PlacementLog_Msg("\tLocation: ");
  PlacementLog_Msg(hintedLocation->GetName());
  PlacementLog_Msg("\n");

  PlacementLog_Msg("\tItem: ");
  PlacementLog_Msg(hintedLocation->GetPlacedItemName());
  PlacementLog_Msg("\n");

  //get an accessible gossip stone
  std::vector<ItemLocation*> gossipStoneLocations = GetAccessibleGossipStones(&hintedLocation);
  hintedLocation->SaveDelayedItem();
  if (gossipStoneLocations.empty()) {
    PlacementLog_Msg("\tNO GOSSIP STONES TO PLACE HINT\n\n");
    return;
  }
  hintedLocation->SetAsHinted();
  ItemLocation* gossipStone = RandomElement(gossipStoneLocations, false);

  //form hint text
  Text locationText = Text{"","",""};
  if (hintedLocation->IsDungeon()) {
    *remainingDungeonBarrenHints -= 1;
    locationText = hintedLocation->GetParentRegion()->hintText->GetText();
  } else {
    locationText = GetHintRegion(hintedLocation->GetParentRegion())->hintText->GetText();
  }
  Text finalBarrenHint = Hints::Prefix.GetText()+Hints::Plundering.GetText()+"#"+locationText+"#"+Hints::Foolish.GetText();
  PlacementLog_Msg("\tMessage: ");
  PlacementLog_Msg(finalBarrenHint.english);
  PlacementLog_Msg("\n\n");
  AddHint(finalBarrenHint, gossipStone, {QM_PINK});

  //get rid of all other locations in this same barren region
  barrenLocations = FilterFromPool(barrenLocations, [hintedLocation](ItemLocation* loc){
    return GetHintRegion(loc->GetParentRegion())->hintText != GetHintRegion(hintedLocation->GetParentRegion())->hintText;
  });

}

static void CreateRandomLocationHint(bool goodItem = false){
  std::vector<ItemLocation*> possibleHintLocations = FilterFromPool(allLocations, [goodItem](ItemLocation* loc){return loc->IsHintable() && !loc->IsHintedAt() && (!goodItem || loc->GetPlacedItem().IsMajorItem());});
  //If no more locations can be hinted at, then just try to get another hint
  if (possibleHintLocations.empty()) {
    PlacementLog_Msg("\tNO LOCATIONS TO HINT\n\n");
    return;
  }
  ItemLocation* hintedLocation = RandomElement(possibleHintLocations, false);

  PlacementLog_Msg("\tLocation: ");
  PlacementLog_Msg(hintedLocation->GetName());
  PlacementLog_Msg("\n");

  PlacementLog_Msg("\tItem: ");
  PlacementLog_Msg(hintedLocation->GetPlacedItemName());
  PlacementLog_Msg("\n");

  //get an acessible gossip stone
  std::vector<ItemLocation*> gossipStoneLocations = GetAccessibleGossipStones(&hintedLocation);
  hintedLocation->SaveDelayedItem();
  if (gossipStoneLocations.empty()) {
    PlacementLog_Msg("\tNO GOSSIP STONES TO PLACE HINT\n\n");
    return;
  }
  hintedLocation->SetAsHinted();
  ItemLocation* gossipStone = RandomElement(gossipStoneLocations, false);


  //form hint text
  Text itemText = hintedLocation->GetPlacedItem().GetHintText().GetText();
  if (hintedLocation->IsDungeon()) {
    Text locationText = hintedLocation->GetParentRegion()->hintText->GetText();
    Text finalHint = Hints::Prefix.GetText()+"#"+locationText+"# hoards #"+itemText+"#.";
    PlacementLog_Msg("\tMessage: ");
    PlacementLog_Msg(finalHint.english);
    PlacementLog_Msg("\n\n");
    AddHint(finalHint, gossipStone, {QM_GREEN, QM_RED});
  } else {
    Text locationText = GetHintRegion(hintedLocation->GetParentRegion())->hintText->GetText();
    Text finalHint = Hints::Prefix.GetText()+"#"+itemText+"# can be found at #"+locationText+"#.";
    PlacementLog_Msg("\tMessage: ");
    PlacementLog_Msg(finalHint.english);
    PlacementLog_Msg("\n\n");
    AddHint(finalHint, gossipStone, {QM_RED, QM_GREEN});
  }
}

static void CreateGoodItemHint() {
  CreateRandomLocationHint(true);
}

static void CreateJunkHint() {
  //duplicate junk hints are possible for now
  HintText* junkHint = RandomElement(Hints::junkHints);
  LogicReset();
  std::vector<ItemLocation*> gossipStones = GetAccessibleLocations(gossipStoneLocations);
  if (gossipStones.empty()) {
    PlacementLog_Msg("\tNO GOSSIP STONES TO PLACE HINT\n\n");
    return;
  }
  ItemLocation* gossipStone = RandomElement(gossipStones, false);
  Text hintText = junkHint->GetText();

  PlacementLog_Msg("\tMessage: ");
  PlacementLog_Msg(hintText.english);
  PlacementLog_Msg("\n\n");

  AddHint(hintText, gossipStone);
}

static std::vector<ItemLocation*> CalculateBarrenRegions() {
  std::vector<ItemLocation*> barrenLocations = {};
  std::vector<ItemLocation*> potentiallyUsefulLocations = {};

  for (ItemLocation* location : allLocations) {
    if (location->GetPlacedItem().IsMajorItem()) {
      AddElementsToPool(potentiallyUsefulLocations, std::vector<ItemLocation*>{location});
    } else {
      if (location != &LinksPocket) { //Nobody cares to know if Link's Pocket is barren
        AddElementsToPool(barrenLocations, std::vector<ItemLocation*>{location});
      }
    }
  }

  //leave only locations at barren regions in the list
  auto finalBarrenLocations = FilterFromPool(barrenLocations, [potentiallyUsefulLocations](ItemLocation* loc){
    for (ItemLocation* usefulLoc : potentiallyUsefulLocations) {
      HintText* barren = GetHintRegion(loc->GetParentRegion())->hintText;
      HintText* useful = GetHintRegion(usefulLoc->GetParentRegion())->hintText;
      if (barren == useful) {
        return false;
      }
    }
    return true;
  });

  return finalBarrenLocations;
}

void CreateAllHints() {
  PlacementLog_Msg("\nNOW CREATING HINTS\n");
  HintSetting hintSetting = hintSettingTable[Settings::HintDistribution.Value<u8>()];

  u8 remainingDungeonWothHints = hintSetting.dungeonsWothLimit;
  u8 remainingDungeonBarrenHints = hintSetting.dungeonsBarrenLimit;

  //Add 'always' location hints
  if (hintSetting.distTable[static_cast<int>(HintType::Always)].copies > 0) {

    //only filter locations that had a random item placed at them (e.g. don't get cow locations if shuffle cows is off)
    std::vector<ItemLocation*> alwaysHintLocations = FilterFromPool(allLocations, [](ItemLocation* loc){return loc->GetHintCategory() == HintCategory::Always &&
                                                                                                               loc->IsHintable()      && !loc->IsHintedAt();});
    for (ItemLocation* location : alwaysHintLocations) {
      CreateLocationHint({location});
    }
  }

  //TODO: Trial Hint locations

  //create a vector with each hint type proportional to it's weight in the distribution setting.
  //ootr uses a weighted probability function to decide hint types, but selecting randomly from
  //this vector will do for now
  std::vector<HintType> remainingHintTypes = {};
  for (HintDistributionSetting hds : hintSetting.distTable) {
    remainingHintTypes.insert(remainingHintTypes.end(), hds.weight, hds.type);
  }
  Shuffle(remainingHintTypes);

  //get barren regions
  auto barrenLocations = CalculateBarrenRegions();

  //while there are still gossip stones remaining
  while (FilterFromPool(gossipStoneLocations, [](ItemLocation* loc){return loc->GetPlacedItem() == NoItem;}).size() != 0) {
    //TODO: fixed hint types

    if (remainingHintTypes.empty()) {
      break;
    }

    //get a random hint type from the remaining hints
    HintType type = RandomElement(remainingHintTypes, true);

    PlacementLog_Msg("Attempting to make hint of type: ");
    PlacementLog_Msg(std::to_string(static_cast<int>(type)));
    PlacementLog_Msg("\n");

    //create the appropriate hint for the type
    if (type == HintType::Woth) {
      CreateWothHint(&remainingDungeonWothHints);

    } else if (type == HintType::Barren) {
      CreateBarrenHint(&remainingDungeonBarrenHints, barrenLocations);

    } else if (type == HintType::Sometimes){
      std::vector<ItemLocation*> sometimesHintLocations = FilterFromPool(allLocations, [](ItemLocation* loc){return loc->GetHintCategory() == HintCategory::Sometimes && loc->IsHintable() && !loc->IsHintedAt();});
      CreateLocationHint(sometimesHintLocations);

    } else if (type == HintType::Random) {
      CreateRandomLocationHint();

    } else if (type == HintType::Item) {
      CreateGoodItemHint();

    } else if (type == HintType::Song){
      std::vector<ItemLocation*> songHintLocations = FilterFromPool(allLocations, [](ItemLocation* loc){return loc->IsCategory(Category::cSong) && loc->IsHintable() && !loc->IsHintedAt();});
      CreateLocationHint(songHintLocations);

    } else if (type == HintType::Overworld){
      std::vector<ItemLocation*> overworldHintLocations = FilterFromPool(allLocations, [](ItemLocation* loc){return loc->IsOverworld() && loc->IsHintable() && !loc->IsHintedAt();});
      CreateLocationHint(overworldHintLocations);

    } else if (type == HintType::Dungeon){
      std::vector<ItemLocation*> dungeonHintLocations = FilterFromPool(allLocations, [](ItemLocation* loc){return loc->IsDungeon() && loc->IsHintable() && !loc->IsHintedAt();});
      CreateLocationHint(dungeonHintLocations);

    } else if (type == HintType::Junk) {
      CreateJunkHint();
    }
  }

  //Getting gossip stone locations temporarily sets one location to not be reachable.
  //Call the function one last time to get rid of false positives on locations not
  //being reachable.
  GetAccessibleLocations({});
}
