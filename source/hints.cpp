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
#include "hint_list.hpp"
#include "trial.hpp"

using namespace CustomMessages;
using namespace Logic;
using namespace Settings;
using namespace Trial;

constexpr std::array<HintSetting, 4> hintSettingTable{{
  // Useless hints
  {
    .dungeonsWothLimit = 2,
    .dungeonsBarrenLimit = 1,
    .namedItemsRequired = false,
    .distTable = {{
      {.type = HintType::Trial,     .order =  1, .weight =  0, .fixed = 0, .copies = 0},
      {.type = HintType::Always,    .order =  2, .weight =  0, .fixed = 0, .copies = 0},
      {.type = HintType::Woth,      .order =  3, .weight =  0, .fixed = 0, .copies = 0},
      {.type = HintType::Barren,    .order =  4, .weight =  0, .fixed = 0, .copies = 0},
      {.type = HintType::Entrance,  .order =  5, .weight =  0, .fixed = 0, .copies = 0},
      {.type = HintType::Sometimes, .order =  6, .weight =  0, .fixed = 0, .copies = 0},
      {.type = HintType::Random,    .order =  7, .weight =  0, .fixed = 0, .copies = 0},
      {.type = HintType::Item,      .order =  8, .weight =  0, .fixed = 0, .copies = 0},
      {.type = HintType::Song,      .order =  9, .weight =  0, .fixed = 0, .copies = 0},
      {.type = HintType::Overworld, .order = 10, .weight =  0, .fixed = 0, .copies = 0},
      {.type = HintType::Dungeon,   .order = 11, .weight =  0, .fixed = 0, .copies = 0},
      {.type = HintType::Junk,      .order = 12, .weight = 99, .fixed = 0, .copies = 0},
      {.type = HintType::NamedItem, .order = 13, .weight =  0, .fixed = 0, .copies = 0},
    }},
  },

  // Balanced hints
  {
    .dungeonsWothLimit = 2,
    .dungeonsBarrenLimit = 1,
    .namedItemsRequired = true,
    .distTable = {{
      {.type = HintType::Trial,     .order =  1, .weight =  0, .fixed = 0, .copies = 1},
      {.type = HintType::Always,    .order =  2, .weight =  0, .fixed = 0, .copies = 1},
      {.type = HintType::Woth,      .order =  3, .weight =  7, .fixed = 0, .copies = 1},
      {.type = HintType::Barren,    .order =  4, .weight =  4, .fixed = 0, .copies = 1},
      {.type = HintType::Entrance,  .order =  5, .weight =  6, .fixed = 0, .copies = 1},
      {.type = HintType::Sometimes, .order =  6, .weight =  0, .fixed = 0, .copies = 1},
      {.type = HintType::Random,    .order =  7, .weight = 12, .fixed = 0, .copies = 1},
      {.type = HintType::Item,      .order =  8, .weight = 10, .fixed = 0, .copies = 1},
      {.type = HintType::Song,      .order =  9, .weight =  2, .fixed = 0, .copies = 1},
      {.type = HintType::Overworld, .order = 10, .weight =  4, .fixed = 0, .copies = 1},
      {.type = HintType::Dungeon,   .order = 11, .weight =  3, .fixed = 0, .copies = 1},
      {.type = HintType::Junk,      .order = 12, .weight =  6, .fixed = 0, .copies = 1},
      {.type = HintType::NamedItem, .order = 13, .weight =  0, .fixed = 0, .copies = 1},
    }},
  },

  // Strong hints
  {
    .dungeonsWothLimit = 2,
    .dungeonsBarrenLimit = 1,
    .namedItemsRequired = true,
    .distTable = {{
      {.type = HintType::Trial,     .order =  1, .weight =  0, .fixed = 0, .copies = 1},
      {.type = HintType::Always,    .order =  2, .weight =  0, .fixed = 0, .copies = 2},
      {.type = HintType::Woth,      .order =  3, .weight = 12, .fixed = 0, .copies = 2},
      {.type = HintType::Barren,    .order =  4, .weight = 12, .fixed = 0, .copies = 1},
      {.type = HintType::Entrance,  .order =  5, .weight =  4, .fixed = 0, .copies = 1},
      {.type = HintType::Sometimes, .order =  6, .weight =  0, .fixed = 0, .copies = 1},
      {.type = HintType::Random,    .order =  7, .weight =  8, .fixed = 0, .copies = 1},
      {.type = HintType::Item,      .order =  8, .weight =  8, .fixed = 0, .copies = 1},
      {.type = HintType::Song,      .order =  9, .weight =  4, .fixed = 0, .copies = 1},
      {.type = HintType::Overworld, .order = 10, .weight =  6, .fixed = 0, .copies = 1},
      {.type = HintType::Dungeon,   .order = 11, .weight =  6, .fixed = 0, .copies = 1},
      {.type = HintType::Junk,      .order = 12, .weight =  0, .fixed = 0, .copies = 1},
      {.type = HintType::NamedItem, .order = 13, .weight =  0, .fixed = 0, .copies = 1},
    }},
  },

  // Very strong hints
  {
    .dungeonsWothLimit = 40,
    .dungeonsBarrenLimit = 40,
    .namedItemsRequired = true,
    .distTable = {{
      {.type = HintType::Trial,     .order =  1, .weight =  0, .fixed = 0, .copies = 1},
      {.type = HintType::Always,    .order =  2, .weight =  0, .fixed = 0, .copies = 2},
      {.type = HintType::Woth,      .order =  3, .weight = 15, .fixed = 0, .copies = 2},
      {.type = HintType::Barren,    .order =  4, .weight = 15, .fixed = 0, .copies = 1},
      {.type = HintType::Entrance,  .order =  5, .weight = 10, .fixed = 0, .copies = 1},
      {.type = HintType::Sometimes, .order =  6, .weight =  0, .fixed = 0, .copies = 1},
      {.type = HintType::Random,    .order =  7, .weight =  0, .fixed = 0, .copies = 1},
      {.type = HintType::Item,      .order =  8, .weight =  5, .fixed = 0, .copies = 1},
      {.type = HintType::Song,      .order =  9, .weight =  2, .fixed = 0, .copies = 1},
      {.type = HintType::Overworld, .order = 10, .weight =  7, .fixed = 0, .copies = 1},
      {.type = HintType::Dungeon,   .order = 11, .weight =  7, .fixed = 0, .copies = 1},
      {.type = HintType::Junk,      .order = 12, .weight =  0, .fixed = 0, .copies = 1},
      {.type = HintType::NamedItem, .order = 13, .weight =  0, .fixed = 0, .copies = 1},
    }},
  },
}};

static Exit* GetHintRegion(Exit* exit) {

  std::vector<Exit*> alreadyChecked = {};
  std::vector<Exit*> spotQueue = {exit};

  while (!spotQueue.empty()) {
    Exit* region = spotQueue.back();
    alreadyChecked.push_back(region);
    spotQueue.pop_back();

    if (region->hintKey != NONE) {
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

static std::vector<LocationKey> GetAccessibleGossipStones(const LocationKey hintedLocation = GANON) {
  //temporarily remove the hinted location's item, and then perform a
  //reachability search for gossip stone locations.
  ItemKey originalItem = Location(hintedLocation)->GetPlacedItemKey();
  Location(hintedLocation)->SetPlacedItem(NONE);

  LogicReset();
  auto accessibleGossipStones = GetAccessibleLocations(gossipStoneLocations);
  //Give the item back to the location
  Location(hintedLocation)->SetPlacedItem(originalItem);

  return accessibleGossipStones;
}

static void AddHint(Text hint, const LocationKey gossipStone, const std::vector<u8>& colors = {}) {
  //save hints as dummy items for writing to the spoiler log
  NewItem(gossipStone, Item{hint.english, ITEMTYPE_EVENT, GI_RUPEE_BLUE_LOSE, false, &noVariable, NONE});
  Location(gossipStone)->SetPlacedItem(gossipStone);

  //create the in game message
  u32 messageId = 0x400 + Location(gossipStone)->GetFlag();
  CreateMessageFromTextObject(messageId, 0, 2, 3, AddColorsAndFormat(hint, colors));
}

static void CreateLocationHint(const std::vector<LocationKey>& possibleHintLocations) {
  //return if there aren't any hintable locations or gossip stones available
  if (possibleHintLocations.empty()) {
    PlacementLog_Msg("\tNO LOCATIONS TO HINT\n\n");
    return;
  }

  LocationKey hintedLocation = RandomElement(possibleHintLocations);
  const std::vector<LocationKey> accessibleGossipStones = GetAccessibleGossipStones(hintedLocation);

  PlacementLog_Msg("\tLocation: ");
  PlacementLog_Msg(Location(hintedLocation)->GetName());
  PlacementLog_Msg("\n");

  PlacementLog_Msg("\tItem: ");
  PlacementLog_Msg(Location(hintedLocation)->GetPlacedItemName());
  PlacementLog_Msg("\n");

  if (accessibleGossipStones.empty()) {
    PlacementLog_Msg("\tNO GOSSIP STONES TO PLACE HINT\n\n");
    return;
  }

  LocationKey gossipStone = RandomElement(accessibleGossipStones);
  Location(hintedLocation)->SetAsHinted();

  //make hint text
  Text locationHintText = Location(hintedLocation)->GetHint().GetText();
  Text itemHintText = Location(hintedLocation)->GetPlacedItem().GetHint().GetText();
  Text prefix = Hint(PREFIX).GetText();

  Text finalHint = prefix + locationHintText + " #"+itemHintText+"#.";
  PlacementLog_Msg("\tMessage: ");
  PlacementLog_Msg(finalHint.english);
  PlacementLog_Msg("\n\n");

  AddHint(finalHint, gossipStone, {QM_GREEN, QM_RED});
}

static void CreateWothHint(u8* remainingDungeonWothHints) {
  //get locations that are in the current playthrough
  std::vector<LocationKey> possibleHintLocations = {};
  //iterate through playthrough locations by sphere
  for (std::vector<LocationKey> sphere : playthroughLocations) {
    std::vector<LocationKey> sphereHintLocations = FilterFromPool(sphere, [remainingDungeonWothHints](LocationKey loc){
      return Location(loc)->IsHintable()    && //only filter hintable locations
            !(Location(loc)->IsHintedAt())  && //only filter locations that haven't been hinted at
            (Location(loc)->IsOverworld() || (Location(loc)->IsDungeon() && (*remainingDungeonWothHints) > 0)); //make sure we haven't surpassed the woth dungeon limit
    });
    AddElementsToPool(possibleHintLocations, sphereHintLocations);
  }

  //If no more locations can be hinted at for woth, then just try to get another hint
  if (possibleHintLocations.empty()) {
    PlacementLog_Msg("\tNO LOCATIONS TO HINT\n\n");
    return;
  }
  LocationKey hintedLocation = RandomElement(possibleHintLocations);

  PlacementLog_Msg("\tLocation: ");
  PlacementLog_Msg(Location(hintedLocation)->GetName());
  PlacementLog_Msg("\n");

  PlacementLog_Msg("\tItem: ");
  PlacementLog_Msg(Location(hintedLocation)->GetPlacedItemName());
  PlacementLog_Msg("\n");

  //get an accessible gossip stone
  const std::vector<LocationKey> gossipStoneLocations = GetAccessibleGossipStones(hintedLocation);

  if (gossipStoneLocations.empty()) {
    PlacementLog_Msg("\tNO GOSSIP STONES TO PLACE HINT\n\n");
    return;
  }
  Location(hintedLocation)->SetAsHinted();
  LocationKey gossipStone = RandomElement(gossipStoneLocations);

  //form hint text
  Text locationText;
  if (Location(hintedLocation)->IsDungeon()) {
    *remainingDungeonWothHints -= 1;
    locationText = Location(hintedLocation)->GetParentRegion()->GetHint().GetText();
  } else {
    locationText = GetHintRegion(Location(hintedLocation)->GetParentRegion())->GetHint().GetText();
  }
  Text finalWothHint = Hint(PREFIX).GetText()+"#"+locationText+"#"+Hint(WAY_OF_THE_HERO).GetText();
  PlacementLog_Msg("\tMessage: ");
  PlacementLog_Msg(finalWothHint.english);
  PlacementLog_Msg("\n\n");
  AddHint(finalWothHint, gossipStone, {QM_LBLUE});
}

static void CreateBarrenHint(u8* remainingDungeonBarrenHints, std::vector<LocationKey>& barrenLocations) {
  //remove dungeon locations if necessary
  if (*remainingDungeonBarrenHints < 1) {
    barrenLocations = FilterFromPool(barrenLocations, [](const LocationKey loc){return !(Location(loc)->IsDungeon());});
  }

  if (barrenLocations.empty()) {
    return;
  }

  LocationKey hintedLocation = RandomElement(barrenLocations, true);

  PlacementLog_Msg("\tLocation: ");
  PlacementLog_Msg(Location(hintedLocation)->GetName());
  PlacementLog_Msg("\n");

  PlacementLog_Msg("\tItem: ");
  PlacementLog_Msg(Location(hintedLocation)->GetPlacedItemName());
  PlacementLog_Msg("\n");

  //get an accessible gossip stone
  const std::vector<LocationKey> gossipStoneLocations = GetAccessibleGossipStones(hintedLocation);
  if (gossipStoneLocations.empty()) {
    PlacementLog_Msg("\tNO GOSSIP STONES TO PLACE HINT\n\n");
    return;
  }
  Location(hintedLocation)->SetAsHinted();
  LocationKey gossipStone = RandomElement(gossipStoneLocations);

  //form hint text
  Text locationText;
  if (Location(hintedLocation)->IsDungeon()) {
    *remainingDungeonBarrenHints -= 1;
    locationText = Hint(Location(hintedLocation)->GetParentRegion()->hintKey).GetText();
  } else {
    locationText = Hint(GetHintRegion(Location(hintedLocation)->GetParentRegion())->hintKey).GetText();
  }
  Text finalBarrenHint = Hint(PREFIX).GetText()+Hint(PLUNDERING).GetText()+"#"+locationText+"#"+Hint(FOOLISH).GetText();
  PlacementLog_Msg("\tMessage: ");
  PlacementLog_Msg(finalBarrenHint.english);
  PlacementLog_Msg("\n\n");
  AddHint(finalBarrenHint, gossipStone, {QM_PINK});

  //get rid of all other locations in this same barren region
  barrenLocations = FilterFromPool(barrenLocations, [hintedLocation](LocationKey loc){
    return GetHintRegion(Location(loc)->GetParentRegion())->hintKey != GetHintRegion(Location(hintedLocation)->GetParentRegion())->hintKey;
  });

}

static void CreateRandomLocationHint(const bool goodItem = false) {
  const std::vector<LocationKey> possibleHintLocations = FilterFromPool(allLocations, [goodItem](const LocationKey loc) {
    return Location(loc)->IsHintable() && !(Location(loc)->IsHintedAt()) && (!goodItem || Location(loc)->GetPlacedItem().IsMajorItem());
  });
  //If no more locations can be hinted at, then just try to get another hint
  if (possibleHintLocations.empty()) {
    PlacementLog_Msg("\tNO LOCATIONS TO HINT\n\n");
    return;
  }
  LocationKey hintedLocation = RandomElement(possibleHintLocations);

  PlacementLog_Msg("\tLocation: ");
  PlacementLog_Msg(Location(hintedLocation)->GetName());
  PlacementLog_Msg("\n");

  PlacementLog_Msg("\tItem: ");
  PlacementLog_Msg(Location(hintedLocation)->GetPlacedItemName());
  PlacementLog_Msg("\n");

  //get an acessible gossip stone
  const std::vector<LocationKey> gossipStoneLocations = GetAccessibleGossipStones(hintedLocation);
  if (gossipStoneLocations.empty()) {
    PlacementLog_Msg("\tNO GOSSIP STONES TO PLACE HINT\n\n");
    return;
  }
  Location(hintedLocation)->SetAsHinted();
  LocationKey gossipStone = RandomElement(gossipStoneLocations);

  //form hint text
  Text itemText = Location(hintedLocation)->GetPlacedItem().GetHint().GetText();
  if (Location(hintedLocation)->IsDungeon()) {
    Text locationText = Location(hintedLocation)->GetParentRegion()->GetHint().GetText();
    Text finalHint = Hint(PREFIX).GetText()+"#"+locationText+"# "+Hint(HOARDS).GetText()+" #"+itemText+"#.";
    PlacementLog_Msg("\tMessage: ");
    PlacementLog_Msg(finalHint.english);
    PlacementLog_Msg("\n\n");
    AddHint(finalHint, gossipStone, {QM_GREEN, QM_RED});
  } else {
    Text locationText = GetHintRegion(Location(hintedLocation)->GetParentRegion())->GetHint().GetText();
    Text finalHint = Hint(PREFIX).GetText()+"#"+itemText+"# "+Hint(CAN_BE_FOUND_AT).GetText()+" #"+locationText+"#.";
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
  const HintText junkHint = RandomElement(GetHintCategory(HintCategory::Junk));
  LogicReset();
  const std::vector<LocationKey> gossipStones = GetAccessibleLocations(gossipStoneLocations);
  if (gossipStones.empty()) {
    PlacementLog_Msg("\tNO GOSSIP STONES TO PLACE HINT\n\n");
    return;
  }
  LocationKey gossipStone = RandomElement(gossipStones);
  Text hint = junkHint.GetText();

  PlacementLog_Msg("\tMessage: ");
  PlacementLog_Msg(hint.english);
  PlacementLog_Msg("\n\n");

  AddHint(hint, gossipStone);
}

static std::vector<LocationKey> CalculateBarrenRegions() {
  std::vector<LocationKey> barrenLocations = {};
  std::vector<LocationKey> potentiallyUsefulLocations = {};

  for (LocationKey loc : allLocations) {
    if (Location(loc)->GetPlacedItem().IsMajorItem()) {
      AddElementsToPool(potentiallyUsefulLocations, std::vector{loc});
    } else {
      if (loc != LINKS_POCKET) { //Nobody cares to know if Link's Pocket is barren
        AddElementsToPool(barrenLocations, std::vector{loc});
      }
    }
  }

  //leave only locations at barren regions in the list
  auto finalBarrenLocations = FilterFromPool(barrenLocations, [&potentiallyUsefulLocations](LocationKey loc){
    for (LocationKey usefulLoc : potentiallyUsefulLocations) {
      HintKey barrenKey = GetHintRegion(Location(loc)->GetParentRegion())->hintKey;
      HintKey usefulKey = GetHintRegion(Location(usefulLoc)->GetParentRegion())->hintKey;
      if (barrenKey == usefulKey) {
        return false;
      }
    }
    return true;
  });

  return finalBarrenLocations;
}

static void CreateTrialHints() {
    //six trials
  if (RandomGanonsTrials && GanonsTrialsCount.Is(6)) {

    //get a random gossip stone
    auto gossipStones = GetAccessibleGossipStones();
    auto gossipStone = RandomElement(gossipStones, false);

    //make hint
    auto hint = Hint(PREFIX).GetText() + Hint(SIX_TRIALS).GetText();
    AddHint(hint, gossipStone, {QM_PINK});

    //zero trials
  } else if (RandomGanonsTrials && GanonsTrialsCount.Is(0)) {

    //get a random gossip stone
    auto gossipStones = GetAccessibleGossipStones();
    auto gossipStone = RandomElement(gossipStones, false);

    //make hint
    auto hint = Hint(PREFIX).GetText() + Hint(ZERO_TRIALS).GetText();
    AddHint(hint, gossipStone, {QM_YELLOW});

    //4 or 5 required trials
  } else if (GanonsTrialsCount.Is(5) || GanonsTrialsCount.Is(4)) {

    //get skipped trials
    std::vector<TrialInfo*> trials = {};
    trials.assign(trialList.begin(), trialList.end());
    auto skippedTrials = FilterFromPool(trials, [](TrialInfo* trial){return trial->IsSkipped();});

    //create a hint for each skipped trial
    for (auto& trial : skippedTrials) {
      //get a random gossip stone
      auto gossipStones = GetAccessibleGossipStones();
      auto gossipStone = RandomElement(gossipStones, false);

      //make hint
      auto hint = Hint(PREFIX).GetText()+"#"+trial->GetName()+"#"+Hint(FOUR_TO_FIVE_TRIALS).GetText();
      AddHint(hint, gossipStone, {QM_YELLOW});
    }
    //1 to 3 trials
  } else if (GanonsTrialsCount.Value<u8>() >= 1 && GanonsTrialsCount.Value<u8>() <= 3) {
    //get requried trials
    std::vector<TrialInfo*> trials = {};
    trials.assign(trialList.begin(), trialList.end());
    auto requiredTrials = FilterFromPool(trials, [](TrialInfo* trial){return trial->IsRequired();});

    //create a hint for each required trial
    for (auto& trial : requiredTrials) {
      //get a random gossip stone
      auto gossipStones = GetAccessibleGossipStones();
      auto gossipStone = RandomElement(gossipStones, false);

      //make hint
      auto hint = Hint(PREFIX).GetText()+"#"+trial->GetName()+"#"+Hint(ONE_TO_THREE_TRIALS).GetText();
      AddHint(hint, gossipStone, {QM_PINK});
    }
  }
}

static void CreateGanonText() {


  //funny ganon line
  auto ganonText = RandomElement(GetHintCategory(HintCategory::GanonLine)).GetText();
  CreateMessageFromTextObject(0x70CB, 0, 2, 3, AddColorsAndFormat(ganonText));

  //Get the location of the light arrows
  auto lightArrowLocation = FilterFromPool(allLocations, [](const LocationKey loc){return Location(loc)->GetPlacedItemKey() == LIGHT_ARROWS;});

  Text text;
  //If there is no light arrow location, it was in the player's inventory at the start
  if (lightArrowLocation.empty()) {
    text = Hint(LIGHT_ARROW_LOCATION_HINT).GetText()+Hint(YOUR_POCKET).GetText();
  } else {
    text = Hint(LIGHT_ARROW_LOCATION_HINT).GetText()+GetHintRegion(Location(lightArrowLocation[0])->GetParentRegion())->GetHint().GetText();
  }
  text = text + "!";

  CreateMessageFromTextObject(0x70CC, 0, 2, 3, AddColorsAndFormat(text));
}

void CreateAllHints() {

  CreateGanonText();

  PlacementLog_Msg("\nNOW CREATING HINTS\n");
  const HintSetting& hintSetting = hintSettingTable[Settings::HintDistribution.Value<u8>()];

  u8 remainingDungeonWothHints = hintSetting.dungeonsWothLimit;
  u8 remainingDungeonBarrenHints = hintSetting.dungeonsBarrenLimit;

  // Add 'always' location hints
  if (hintSetting.distTable[static_cast<int>(HintType::Always)].copies > 0) {
    // Only filter locations that had a random item placed at them (e.g. don't get cow locations if shuffle cows is off)
    const auto alwaysHintLocations = FilterFromPool(allLocations, [](const LocationKey loc){
        return Location(loc)->GetHint().GetType() == HintCategory::Always &&
               Location(loc)->IsHintable()        && !(Location(loc)->IsHintedAt());
    });
    for (LocationKey location : alwaysHintLocations) {
      CreateLocationHint({location});
    }
  }

  //Add 'trial' location hints
  if (hintSetting.distTable[static_cast<int>(HintType::Trial)].copies > 0) {
    CreateTrialHints();
  }

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
  while (FilterFromPool(gossipStoneLocations, [](const LocationKey loc){return Location(loc)->GetPlacedItemKey() == NONE;}).size() != 0) {
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
      std::vector<LocationKey> sometimesHintLocations = FilterFromPool(allLocations, [](const LocationKey loc){return Location(loc)->GetHint().GetType() == HintCategory::Sometimes && Location(loc)->IsHintable() && !(Location(loc)->IsHintedAt());});
      CreateLocationHint(sometimesHintLocations);

    } else if (type == HintType::Random) {
      CreateRandomLocationHint();

    } else if (type == HintType::Item) {
      CreateGoodItemHint();

    } else if (type == HintType::Song){
      std::vector<LocationKey> songHintLocations = FilterFromPool(allLocations, [](const LocationKey loc){return Location(loc)->IsCategory(Category::cSong) && Location(loc)->IsHintable() && !(Location(loc)->IsHintedAt());});
      CreateLocationHint(songHintLocations);

    } else if (type == HintType::Overworld){
      std::vector<LocationKey> overworldHintLocations = FilterFromPool(allLocations, [](const LocationKey loc){return Location(loc)->IsOverworld() && Location(loc)->IsHintable() && !(Location(loc)->IsHintedAt());});
      CreateLocationHint(overworldHintLocations);

    } else if (type == HintType::Dungeon){
      std::vector<LocationKey> dungeonHintLocations = FilterFromPool(allLocations, [](const LocationKey loc){return Location(loc)->IsDungeon() && Location(loc)->IsHintable() && !(Location(loc)->IsHintedAt());});
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
