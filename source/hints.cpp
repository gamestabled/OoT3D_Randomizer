#include "hints.hpp"

#include "custom_messages.hpp"
#include "dungeon.hpp"
#include "item_location.hpp"
#include "item_pool.hpp"
#include "logic.hpp"
#include "random.hpp"
#include "spoiler_log.hpp"
#include "fill.hpp"
#include "hint_list.hpp"
#include "trial.hpp"
#include "entrance.hpp"
#include "settings.hpp"

#include "../code/src/dungeon_rewards.h"

using namespace CustomMessages;
using namespace Logic;
using namespace Settings;
using namespace Trial;

constexpr std::array<HintSetting, 4> hintSettingTable{ {
    // Useless hints
    {
        .dungeonsWothLimit   = 2,
        .dungeonsBarrenLimit = 1,
        .namedItemsRequired  = false,
        .distTable           = { {
                      { .type = HintType::Trial, .order = 1, .weight = 0, .fixed = 0, .copies = 0 },
                      { .type = HintType::Always, .order = 2, .weight = 0, .fixed = 0, .copies = 0 },
                      { .type = HintType::Woth, .order = 3, .weight = 0, .fixed = 0, .copies = 0 },
                      { .type = HintType::Barren, .order = 4, .weight = 0, .fixed = 0, .copies = 0 },
                      { .type = HintType::Entrance, .order = 5, .weight = 0, .fixed = 0, .copies = 0 },
                      { .type = HintType::Sometimes, .order = 6, .weight = 0, .fixed = 0, .copies = 0 },
                      { .type = HintType::Random, .order = 7, .weight = 0, .fixed = 0, .copies = 0 },
                      { .type = HintType::Item, .order = 8, .weight = 0, .fixed = 0, .copies = 0 },
                      { .type = HintType::Song, .order = 9, .weight = 0, .fixed = 0, .copies = 0 },
                      { .type = HintType::Overworld, .order = 10, .weight = 0, .fixed = 0, .copies = 0 },
                      { .type = HintType::Dungeon, .order = 11, .weight = 0, .fixed = 0, .copies = 0 },
                      { .type = HintType::Junk, .order = 12, .weight = 99, .fixed = 0, .copies = 0 },
                      { .type = HintType::NamedItem, .order = 13, .weight = 0, .fixed = 0, .copies = 0 },
        } },
    },

    // Balanced hints
    {
        .dungeonsWothLimit   = 2,
        .dungeonsBarrenLimit = 1,
        .namedItemsRequired  = true,
        .distTable           = { {
                      { .type = HintType::Trial, .order = 1, .weight = 0, .fixed = 0, .copies = 1 },
                      { .type = HintType::Always, .order = 2, .weight = 0, .fixed = 0, .copies = 1 },
                      { .type = HintType::Woth, .order = 3, .weight = 7, .fixed = 0, .copies = 1 },
                      { .type = HintType::Barren, .order = 4, .weight = 4, .fixed = 0, .copies = 1 },
                      { .type = HintType::Entrance, .order = 5, .weight = 6, .fixed = 0, .copies = 1 },
                      { .type = HintType::Sometimes, .order = 6, .weight = 0, .fixed = 0, .copies = 1 },
                      { .type = HintType::Random, .order = 7, .weight = 12, .fixed = 0, .copies = 1 },
                      { .type = HintType::Item, .order = 8, .weight = 10, .fixed = 0, .copies = 1 },
                      { .type = HintType::Song, .order = 9, .weight = 2, .fixed = 0, .copies = 1 },
                      { .type = HintType::Overworld, .order = 10, .weight = 4, .fixed = 0, .copies = 1 },
                      { .type = HintType::Dungeon, .order = 11, .weight = 3, .fixed = 0, .copies = 1 },
                      { .type = HintType::Junk, .order = 12, .weight = 6, .fixed = 0, .copies = 1 },
                      { .type = HintType::NamedItem, .order = 13, .weight = 0, .fixed = 0, .copies = 1 },
        } },
    },

    // Strong hints
    {
        .dungeonsWothLimit   = 2,
        .dungeonsBarrenLimit = 1,
        .namedItemsRequired  = true,
        .distTable           = { {
                      { .type = HintType::Trial, .order = 1, .weight = 0, .fixed = 0, .copies = 1 },
                      { .type = HintType::Always, .order = 2, .weight = 0, .fixed = 0, .copies = 2 },
                      { .type = HintType::Woth, .order = 3, .weight = 12, .fixed = 0, .copies = 2 },
                      { .type = HintType::Barren, .order = 4, .weight = 12, .fixed = 0, .copies = 1 },
                      { .type = HintType::Entrance, .order = 5, .weight = 4, .fixed = 0, .copies = 1 },
                      { .type = HintType::Sometimes, .order = 6, .weight = 0, .fixed = 0, .copies = 1 },
                      { .type = HintType::Random, .order = 7, .weight = 8, .fixed = 0, .copies = 1 },
                      { .type = HintType::Item, .order = 8, .weight = 8, .fixed = 0, .copies = 1 },
                      { .type = HintType::Song, .order = 9, .weight = 4, .fixed = 0, .copies = 1 },
                      { .type = HintType::Overworld, .order = 10, .weight = 6, .fixed = 0, .copies = 1 },
                      { .type = HintType::Dungeon, .order = 11, .weight = 6, .fixed = 0, .copies = 1 },
                      { .type = HintType::Junk, .order = 12, .weight = 0, .fixed = 0, .copies = 1 },
                      { .type = HintType::NamedItem, .order = 13, .weight = 0, .fixed = 0, .copies = 1 },
        } },
    },

    // Very strong hints
    {
        .dungeonsWothLimit   = 40,
        .dungeonsBarrenLimit = 40,
        .namedItemsRequired  = true,
        .distTable           = { {
                      { .type = HintType::Trial, .order = 1, .weight = 0, .fixed = 0, .copies = 1 },
                      { .type = HintType::Always, .order = 2, .weight = 0, .fixed = 0, .copies = 2 },
                      { .type = HintType::Woth, .order = 3, .weight = 15, .fixed = 0, .copies = 2 },
                      { .type = HintType::Barren, .order = 4, .weight = 15, .fixed = 0, .copies = 1 },
                      { .type = HintType::Entrance, .order = 5, .weight = 10, .fixed = 0, .copies = 1 },
                      { .type = HintType::Sometimes, .order = 6, .weight = 0, .fixed = 0, .copies = 1 },
                      { .type = HintType::Random, .order = 7, .weight = 0, .fixed = 0, .copies = 1 },
                      { .type = HintType::Item, .order = 8, .weight = 5, .fixed = 0, .copies = 1 },
                      { .type = HintType::Song, .order = 9, .weight = 2, .fixed = 0, .copies = 1 },
                      { .type = HintType::Overworld, .order = 10, .weight = 7, .fixed = 0, .copies = 1 },
                      { .type = HintType::Dungeon, .order = 11, .weight = 7, .fixed = 0, .copies = 1 },
                      { .type = HintType::Junk, .order = 12, .weight = 0, .fixed = 0, .copies = 1 },
                      { .type = HintType::NamedItem, .order = 13, .weight = 0, .fixed = 0, .copies = 1 },
        } },
    },
} };

std::array<DungeonInfo, 10> dungeonInfoData;

static Area* GetHintRegion(const AreaKey area) {

    std::vector<AreaKey> alreadyChecked = {};
    std::vector<AreaKey> spotQueue      = { area };

    while (!spotQueue.empty()) {
        AreaKey region = spotQueue.back();
        alreadyChecked.push_back(region);
        spotQueue.pop_back();

        if (AreaTable(region)->hintKey != NONE) {
            return AreaTable(region);
        }

        // add unchecked entrances to spot queue
        bool checked = false;
        for (auto& entrance : AreaTable(region)->entrances) {
            for (AreaKey checkedEntrance : alreadyChecked) {
                if (entrance->GetParentRegionKey() == checkedEntrance) {
                    checked = true;
                    break;
                }
            }

            if (!checked) {
                spotQueue.insert(spotQueue.begin(), entrance->GetParentRegionKey());
            }
        }
    }

    return AreaTable(NONE);
}

HintKey GetHintRegionHintKey(const AreaKey area) {
    return GetHintRegion(area)->hintKey;
}

HintKey GetLocationRegionHintKey(const LocationKey location) {
    return GetHintRegion(Location(location)->GetParentRegionKey())->hintKey;
}

static std::vector<LocationKey> GetAccessibleGossipStones(const LocationKey hintedLocation = GANON) {
    // temporarily remove the hinted location's item, and then perform a
    // reachability search for gossip stone locations.
    ItemKey originalItem = Location(hintedLocation)->GetPlacedItemKey();
    Location(hintedLocation)->SetPlacedItem(NONE);

    LogicReset();
    auto accessibleGossipStones = GetAccessibleLocations(gossipStoneLocations);
    // Give the item back to the location
    Location(hintedLocation)->SetPlacedItem(originalItem);

    return accessibleGossipStones;
}

static void AddHint(Text hint, const LocationKey gossipStone, const std::vector<u8>& colors = {}) {
    // save hints as dummy items for writing to the spoiler log
    NewItem(gossipStone, Item{ ITEMTYPE_EVENT, GI_RUPEE_BLUE_LOSE, false, &noVariable, NONE, hint });
    Location(gossipStone)->SetPlacedItem(gossipStone);

    // create the in game message
    u32 messageId      = 0x400 + Location(gossipStone)->GetFlag();
    u32 sariaMessageId = 0xA00 + Location(gossipStone)->GetFlag();
    CreateMessageFromTextObject(messageId, 0, 2, 3, AddColorsAndFormat(hint, colors));
    CreateMessageFromTextObject(sariaMessageId, 0, 2, 3, AddColorsAndFormat(hint + EVENT_TRIGGER(), colors));
}

static void CreateLocationHint(const std::vector<LocationKey>& possibleHintLocations) {
    // return if there aren't any hintable locations or gossip stones available
    if (possibleHintLocations.empty()) {
        PlacementLog_Msg("\tNO LOCATIONS TO HINT\n\n");
        return;
    }

    LocationKey hintedLocation                            = RandomElement(possibleHintLocations);
    const std::vector<LocationKey> accessibleGossipStones = GetAccessibleGossipStones(hintedLocation);

    PlacementLog_Msg("\tLocation: ");
    PlacementLog_Msg(Location(hintedLocation)->GetName());
    PlacementLog_Msg("\n");

    PlacementLog_Msg("\tItem: ");
    PlacementLog_Msg(Location(hintedLocation)->GetPlacedItemName().GetNAEnglish());
    PlacementLog_Msg("\n");

    if (accessibleGossipStones.empty()) {
        PlacementLog_Msg("\tNO GOSSIP STONES TO PLACE HINT\n\n");
        return;
    }

    LocationKey gossipStone = RandomElement(accessibleGossipStones);
    Location(hintedLocation)->SetAsHinted();

    // make hint text
    Text locationHintText = Location(hintedLocation)->GetHint().GetText();
    Text itemHintText     = Location(hintedLocation)->GetPlacedItem().GetHint().GetText();
    Text prefix           = Hint(PREFIX).GetText();

    Text finalHint = prefix + locationHintText + " #" + itemHintText + "#.";
    finalHint.SetFormPerLanguage();
    PlacementLog_Msg("\tMessage: ");
    PlacementLog_Msg(finalHint.NAenglish);
    PlacementLog_Msg("\n\n");

    AddHint(finalHint, gossipStone, { QM_GREEN, QM_RED });
}

static void CreateAreaLocationHint(LocationKey hintedLocation) {
    PlacementLog_Msg("\tLocation: ");
    PlacementLog_Msg(Location(hintedLocation)->GetName());
    PlacementLog_Msg("\n");

    PlacementLog_Msg("\tItem: ");
    PlacementLog_Msg(Location(hintedLocation)->GetPlacedItemName().GetNAEnglish());
    PlacementLog_Msg("\n");

    // return if there aren't any gossip stones available
    const std::vector<LocationKey> accessibleGossipStones = GetAccessibleGossipStones(hintedLocation);
    if (accessibleGossipStones.empty()) {
        PlacementLog_Msg("\tNO GOSSIP STONES TO PLACE HINT\n\n");
        return;
    }

    LocationKey gossipStone = RandomElement(accessibleGossipStones);
    Location(hintedLocation)->SetAsHinted();

    // make hint text
    Text prefix       = Hint(PREFIX).GetText();
    Text itemHintText = Location(hintedLocation)->GetPlacedItem().GetHint().GetText();
    Text foundAt      = Hint(CAN_BE_FOUND_AT).GetText();
    Text areaHintText = Hint(GetLocationRegionHintKey(hintedLocation)).GetText();

    Text finalHint = prefix + "#" + itemHintText + "# " + foundAt + " #" + areaHintText + "#.";
    finalHint.SetFormPerLanguage();
    PlacementLog_Msg("\tMessage: ");
    PlacementLog_Msg(finalHint.NAenglish);
    PlacementLog_Msg("\n\n");

    AddHint(finalHint, gossipStone, { QM_RED, QM_GREEN });
}

static void CreateWothHint(u8* remainingDungeonWothHints) {
    // get locations that are in the current playthrough
    std::vector<LocationKey> possibleHintLocations = {};
    // iterate through playthrough locations by sphere
    std::vector<LocationKey> wothHintLocations =
        FilterFromPool(wothLocations, [remainingDungeonWothHints](LocationKey loc) {
            return Location(loc)->IsHintable() &&    // only filter hintable locations
                   !(Location(loc)->IsHintedAt()) && // only filter locations that haven't been hinted at
                   (Location(loc)->IsOverworld() ||
                    (Location(loc)->IsDungeon() &&
                     (*remainingDungeonWothHints) > 0)); // make sure we haven't surpassed the woth dungeon limit
        });
    AddElementsToPool(possibleHintLocations, wothHintLocations);

    // If no more locations can be hinted at for woth, then just try to get another hint
    if (possibleHintLocations.empty()) {
        PlacementLog_Msg("\tNO LOCATIONS TO HINT\n\n");
        return;
    }
    LocationKey hintedLocation = RandomElement(possibleHintLocations);

    PlacementLog_Msg("\tLocation: ");
    PlacementLog_Msg(Location(hintedLocation)->GetName());
    PlacementLog_Msg("\n");

    PlacementLog_Msg("\tItem: ");
    PlacementLog_Msg(Location(hintedLocation)->GetPlacedItemName().GetNAEnglish());
    PlacementLog_Msg("\n");

    // get an accessible gossip stone
    const std::vector<LocationKey> gossipStoneLocations = GetAccessibleGossipStones(hintedLocation);

    if (gossipStoneLocations.empty()) {
        PlacementLog_Msg("\tNO GOSSIP STONES TO PLACE HINT\n\n");
        return;
    }
    Location(hintedLocation)->SetAsHinted();
    LocationKey gossipStone = RandomElement(gossipStoneLocations);

    if (Location(hintedLocation)->IsDungeon()) {
        *remainingDungeonWothHints -= 1;
    }

    // form hint text
    Text locationText  = GetHintRegion(Location(hintedLocation)->GetParentRegionKey())->GetHint().GetText();
    Text finalWothHint = Hint(PREFIX).GetText() + "#" + locationText + "#" + Hint(WAY_OF_THE_HERO).GetText();
    PlacementLog_Msg("\tMessage: ");
    PlacementLog_Msg(finalWothHint.NAenglish);
    PlacementLog_Msg("\n\n");
    AddHint(finalWothHint, gossipStone, { QM_LBLUE });
}

static void CreateBarrenHint(u8* remainingDungeonBarrenHints, std::vector<LocationKey>& barrenLocations) {
    // remove dungeon locations if necessary
    if (*remainingDungeonBarrenHints < 1) {
        barrenLocations =
            FilterFromPool(barrenLocations, [](const LocationKey loc) { return !(Location(loc)->IsDungeon()); });
    }

    if (barrenLocations.empty()) {
        return;
    }

    LocationKey hintedLocation = RandomElement(barrenLocations, true);

    PlacementLog_Msg("\tLocation: ");
    PlacementLog_Msg(Location(hintedLocation)->GetName());
    PlacementLog_Msg("\n");

    PlacementLog_Msg("\tItem: ");
    PlacementLog_Msg(Location(hintedLocation)->GetPlacedItemName().GetNAEnglish());
    PlacementLog_Msg("\n");

    // get an accessible gossip stone
    const std::vector<LocationKey> gossipStoneLocations = GetAccessibleGossipStones(hintedLocation);
    if (gossipStoneLocations.empty()) {
        PlacementLog_Msg("\tNO GOSSIP STONES TO PLACE HINT\n\n");
        return;
    }
    Location(hintedLocation)->SetAsHinted();
    LocationKey gossipStone = RandomElement(gossipStoneLocations);

    if (Location(hintedLocation)->IsDungeon()) {
        *remainingDungeonBarrenHints -= 1;
    }

    // form hint text
    Text locationText = GetHintRegion(Location(hintedLocation)->GetParentRegionKey())->GetHint().GetText();
    Text finalBarrenHint =
        Hint(PREFIX).GetText() + Hint(PLUNDERING).GetText() + "#" + locationText + "#" + Hint(FOOLISH).GetText();
    PlacementLog_Msg("\tMessage: ");
    PlacementLog_Msg(finalBarrenHint.NAenglish);
    PlacementLog_Msg("\n\n");
    AddHint(finalBarrenHint, gossipStone, { QM_PINK });

    // get rid of all other locations in this same barren region
    barrenLocations = FilterFromPool(barrenLocations, [hintedLocation](LocationKey loc) {
        return GetHintRegion(Location(loc)->GetParentRegionKey())->hintKey !=
               GetHintRegion(Location(hintedLocation)->GetParentRegionKey())->hintKey;
    });
}

static void CreateRandomLocationHint(const bool goodItem = false) {
    const std::vector<LocationKey> possibleHintLocations =
        FilterFromPool(allLocations, [goodItem](const LocationKey loc) {
            return Location(loc)->IsHintable() && !(Location(loc)->IsHintedAt()) &&
                   (!goodItem || Location(loc)->GetPlacedItem().IsMajorItem());
        });
    // If no more locations can be hinted at, then just try to get another hint
    if (possibleHintLocations.empty()) {
        PlacementLog_Msg("\tNO LOCATIONS TO HINT\n\n");
        return;
    }
    LocationKey hintedLocation = RandomElement(possibleHintLocations);

    PlacementLog_Msg("\tLocation: ");
    PlacementLog_Msg(Location(hintedLocation)->GetName());
    PlacementLog_Msg("\n");

    PlacementLog_Msg("\tItem: ");
    PlacementLog_Msg(Location(hintedLocation)->GetPlacedItemName().GetNAEnglish());
    PlacementLog_Msg("\n");

    // get an acessible gossip stone
    const std::vector<LocationKey> gossipStoneLocations = GetAccessibleGossipStones(hintedLocation);
    if (gossipStoneLocations.empty()) {
        PlacementLog_Msg("\tNO GOSSIP STONES TO PLACE HINT\n\n");
        return;
    }
    Location(hintedLocation)->SetAsHinted();
    LocationKey gossipStone = RandomElement(gossipStoneLocations);

    // form hint text
    Text itemText     = Location(hintedLocation)->GetPlacedItem().GetHint().GetText();
    Text locationText = GetHintRegion(Location(hintedLocation)->GetParentRegionKey())->GetHint().GetText();
    // TODO: reconsider dungeon vs non-dungeon item location hints when boss shuffle mixed pools happens
    if (Location(hintedLocation)->IsDungeon()) {
        Text finalHint =
            Hint(PREFIX).GetText() + "#" + locationText + "# " + Hint(HOARDS).GetText() + " #" + itemText + "#.";
        finalHint.SetFormPerLanguage();
        PlacementLog_Msg("\tMessage: ");
        PlacementLog_Msg(finalHint.NAenglish);
        PlacementLog_Msg("\n\n");
        AddHint(finalHint, gossipStone, { QM_GREEN, QM_RED });
    } else {
        Text finalHint = Hint(PREFIX).GetText() + "#" + itemText + "# " + Hint(CAN_BE_FOUND_AT).GetText() + " #" +
                         locationText + "#.";
        finalHint.SetFormPerLanguage();
        PlacementLog_Msg("\tMessage: ");
        PlacementLog_Msg(finalHint.NAenglish);
        PlacementLog_Msg("\n\n");
        AddHint(finalHint, gossipStone, { QM_RED, QM_GREEN });
    }
}

static void CreateGoodItemHint() {
    CreateRandomLocationHint(true);
}

static void CreateJunkHint() {
    // duplicate junk hints are possible for now
    const HintText junkHint = RandomElement(GetHintCategory(HintCategory::Junk));
    LogicReset();
    const std::vector<LocationKey> gossipStones = GetAccessibleLocations(gossipStoneLocations);
    if (gossipStones.empty()) {
        PlacementLog_Msg("\tNO GOSSIP STONES TO PLACE HINT\n\n");
        return;
    }
    LocationKey gossipStone = RandomElement(gossipStones);
    Text hint               = junkHint.GetText();

    PlacementLog_Msg("\tMessage: ");
    PlacementLog_Msg(hint.NAenglish);
    PlacementLog_Msg("\n\n");

    bool tingle = hint.GetNAEnglish().find("Tingle") != std::string::npos;
    u8 color    = tingle ? QM_GREEN : QM_PINK;
    AddHint(hint, gossipStone, { color });
}

static std::vector<LocationKey> CalculateBarrenRegions() {
    std::vector<LocationKey> barrenLocations            = {};
    std::vector<LocationKey> potentiallyUsefulLocations = {};

    for (LocationKey loc : allLocations) {
        // If a location has a major item or is a way of the hero location, it is not barren
        if (Location(loc)->GetPlacedItem().IsMajorItem() || ElementInContainer(loc, wothLocations)) {
            AddElementsToPool(potentiallyUsefulLocations, std::vector{ loc });
        } else {
            if (loc != LINKS_POCKET) { // Nobody cares to know if Link's Pocket is barren
                AddElementsToPool(barrenLocations, std::vector{ loc });
            }
        }
    }

    // Leave only locations at barren regions in the list
    auto finalBarrenLocations = FilterFromPool(barrenLocations, [&potentiallyUsefulLocations](LocationKey loc) {
        for (LocationKey usefulLoc : potentiallyUsefulLocations) {
            HintKey barrenKey = GetLocationRegionHintKey(loc);
            HintKey usefulKey = GetLocationRegionHintKey(usefulLoc);
            if (barrenKey == usefulKey) {
                return false;
            }
        }
        return true;
    });

    return finalBarrenLocations;
}

static void CreateTrialHints() {
    // six trials
    if (RandomGanonsTrials && GanonsTrialsCount.Is(6)) {

        // get a random gossip stone
        auto gossipStones = GetAccessibleGossipStones();
        auto gossipStone  = RandomElement(gossipStones, false);

        // make hint
        auto hint = Hint(PREFIX).GetText() + Hint(SIX_TRIALS).GetText();
        AddHint(hint, gossipStone, { QM_PINK });

        // zero trials
    } else if (RandomGanonsTrials && GanonsTrialsCount.Is(0)) {

        // get a random gossip stone
        auto gossipStones = GetAccessibleGossipStones();
        auto gossipStone  = RandomElement(gossipStones, false);

        // make hint
        auto hint = Hint(PREFIX).GetText() + Hint(ZERO_TRIALS).GetText();
        AddHint(hint, gossipStone, { QM_YELLOW });

        // 4 or 5 required trials
    } else if (GanonsTrialsCount.Is(5) || GanonsTrialsCount.Is(4)) {

        // get skipped trials
        std::vector<TrialInfo*> trials = {};
        trials.assign(trialList.begin(), trialList.end());
        auto skippedTrials = FilterFromPool(trials, [](TrialInfo* trial) { return trial->IsSkipped(); });

        // create a hint for each skipped trial
        for (auto& trial : skippedTrials) {
            // get a random gossip stone
            auto gossipStones = GetAccessibleGossipStones();
            auto gossipStone  = RandomElement(gossipStones, false);

            // make hint
            auto hint = Hint(PREFIX).GetText() + "#" + trial->GetName() + "#" + Hint(FOUR_TO_FIVE_TRIALS).GetText();
            AddHint(hint, gossipStone, { QM_YELLOW });
        }
        // 1 to 3 trials
    } else if (GanonsTrialsCount.Value<u8>() >= 1 && GanonsTrialsCount.Value<u8>() <= 3) {
        // get requried trials
        std::vector<TrialInfo*> trials = {};
        trials.assign(trialList.begin(), trialList.end());
        auto requiredTrials = FilterFromPool(trials, [](TrialInfo* trial) { return trial->IsRequired(); });

        // create a hint for each required trial
        for (auto& trial : requiredTrials) {
            // get a random gossip stone
            auto gossipStones = GetAccessibleGossipStones();
            auto gossipStone  = RandomElement(gossipStones, false);

            // make hint
            auto hint = Hint(PREFIX).GetText() + "#" + trial->GetName() + "#" + Hint(ONE_TO_THREE_TRIALS).GetText();
            AddHint(hint, gossipStone, { QM_PINK });
        }
    }
}

static void CreateGanonText() {

    // funny ganon line
    auto ganonText = RandomElement(GetHintCategory(HintCategory::GanonLine)).GetText();
    CreateMessageFromTextObject(0x70CB, 0, 2, 3, AddColorsAndFormat(ganonText));

    // Get the location of the light arrows
    auto lightArrowLocation = FilterFromPool(
        allLocations, [](const LocationKey loc) { return Location(loc)->GetPlacedItemKey() == LIGHT_ARROWS; });

    Text text;
    // If there is no light arrow location, it was in the player's inventory at the start
    if (lightArrowLocation.empty()) {
        text = Hint(LIGHT_ARROW_LOCATION_HINT).GetText() + Hint(YOUR_POCKET).GetText();
    } else {
        text = Hint(LIGHT_ARROW_LOCATION_HINT).GetText() +
               GetHintRegion(Location(lightArrowLocation[0])->GetParentRegionKey())->GetHint().GetText();
    }
    text = text + "!";

    // Get the location of the master sword
    auto masterSwordLocation = FilterFromPool(
        allLocations, [](const LocationKey loc) { return Location(loc)->GetPlacedItemKey() == MASTER_SWORD; });
    if (ShuffleMasterSword) {
        // Add second text box
        text = text + "^";
        if (masterSwordLocation.empty()) {
            text = text + Hint(MASTER_SWORD_LOCATION_HINT).GetText() + Hint(YOUR_POCKET).GetText();
        } else {
            text = text + Hint(MASTER_SWORD_LOCATION_HINT).GetText() +
                   GetHintRegion(Location(masterSwordLocation[0])->GetParentRegionKey())->GetHint().GetText();
        }
        text = text + "!";
    }

    CreateMessageFromTextObject(0x70CC, 0, 2, 3, AddColorsAndFormat(text));

    // Sheik
    {
        Text sheikText;

        sheikText = Hint(SHEIK_LINE01).GetText();
        CreateMessageFromTextObject(0x9150, 0, 0, 0, AddColorsAndFormat(sheikText, { QM_RED }));

        sheikText = Hint(SHEIK_LINE02).GetText();
        CreateMessageFromTextObject(0x9151, 0, 0, 0, AddColorsAndFormat(sheikText));

        if (lightArrowLocation.empty()) {
            sheikText = Hint(SHEIK_LIGHT_ARROW_LOCATION_HINT).GetText() + "#" + Hint(YOUR_POCKET).GetText() + "#";
        } else {
            sheikText = Hint(SHEIK_LIGHT_ARROW_LOCATION_HINT).GetText() + "#" +
                        GetHintRegion(Location(lightArrowLocation[0])->GetParentRegionKey())->GetHint().GetText() + "#";
        }
        sheikText.EURgerman += " versteckt hat";
        sheikText += ".";
        if (ShuffleMasterSword) {
            // Add second text box
            sheikText += "^";
            if (masterSwordLocation.empty()) {
                sheikText += Hint(SHEIK_MASTER_SWORD_LOCATION_HINT).GetText() + "#" + Hint(YOUR_POCKET).GetText() + "#";
            } else {
                sheikText +=
                    Hint(SHEIK_MASTER_SWORD_LOCATION_HINT).GetText() + "#" +
                    GetHintRegion(Location(masterSwordLocation[0])->GetParentRegionKey())->GetHint().GetText() + "#";
            }
            sheikText.EURgerman += " versteckt";
            sheikText += ".";
        }
        CreateMessageFromTextObject(0x9152, 0, 0, 0,
                                    AddColorsAndFormat(sheikText, { QM_RED, QM_GREEN, QM_RED, QM_GREEN }));

        sheikText = Hint(SHEIK_LINE03).GetText();
        CreateMessageFromTextObject(0x9153, 0, 0, 0, AddColorsAndFormat(sheikText));
    }
}

static void CreateDampeHint() {
    auto hookshotLocation = FilterFromPool(
        allLocations, [](const LocationKey loc) { return Location(loc)->GetPlacedItemKey() == PROGRESSIVE_HOOKSHOT; });

    auto hookLocHint = hookshotLocation.empty()
                           ? Hint(YOUR_POCKET)
                           : GetHintRegion(Location(hookshotLocation[0])->GetParentRegionKey())->GetHint();

    auto dampeText = Hint(DAMPE_DIARY_HINT).GetText();
    dampeText.Replace("%s", hookLocHint.GetText());
    CreateMessageFromTextObject(0x5003, 0, 2, 3, AddColorsAndFormat(dampeText, { QM_PINK, QM_RED }));
}

static void CreateSkulltulaHints() {
    // Create a message for each cursed man that gives a reward.
    for (int i = 0; i < 5; i++) {
        ItemLocation* location = Location(KAK_10_GOLD_SKULLTULA_REWARD + i);
        Text rewardItemText    = location->GetPlacedItem().GetHint().GetTextCopy();
        rewardItemText.Replace("$", "");

        Text hintText = Hint(HOUSE_OF_SKULLTULA_HINT).GetTextCopy();
        hintText.Replace("%d", std::to_string((i + 1) * 10));
        hintText.Replace("%s", rewardItemText);

        CreateMessageFromTextObject(0x9400 + i, 0, 2, 3, AddColorsAndFormat(hintText, { QM_RED, QM_GREEN }));

        location->SetAsHinted();
    }
}

// Find the location which has the given itemKey and create the generic altar text for the reward
static Text BuildDungeonRewardText(ItemID itemID, const ItemKey itemKey) {
    std::vector<LocationKey> itemKeyLocations = FilterFromPool(
        allLocations, [itemKey](const LocationKey loc) { return Location(loc)->GetPlacedItemKey() == itemKey; });
    LocationKey location = itemKeyLocations.empty() ? LINKS_POCKET : itemKeyLocations[0];
    if (Settings::ToTAltarHints || Settings::CompassesShowReward) {
        Location(location)->SetAsHinted();
    }
    // Calling ITEM_OBTAINED draws the passed in itemID to the left side of the textbox
    return Text() + "^" + ITEM_OBTAINED(itemID) + "#" +
           GetHintRegion(Location(location)->GetParentRegionKey())->GetHint().GetText() + "#...";
}

static Text BuildDoorOfTimeText() {
    std::string itemObtained;
    Text doorOfTimeText;

    if (OpenDoorOfTime.Is(OPENDOOROFTIME_OPEN)) {
        itemObtained   = ITEM_OBTAINED(ITEM_SWORD_MASTER);
        doorOfTimeText = Hint(CHILD_ALTAR_TEXT_END_DOTOPEN).GetText();

    } else if (OpenDoorOfTime.Is(OPENDOOROFTIME_CLOSED)) {
        itemObtained   = ITEM_OBTAINED(ITEM_OCARINA_FAIRY);
        doorOfTimeText = Hint(CHILD_ALTAR_TEXT_END_DOTCLOSED).GetText();

    } else if (OpenDoorOfTime.Is(OPENDOOROFTIME_INTENDED)) {
        itemObtained   = ITEM_OBTAINED(ITEM_OCARINA_TIME);
        doorOfTimeText = Hint(CHILD_ALTAR_TEXT_END_DOTINTENDED).GetText();
    }

    return Text() + itemObtained + doorOfTimeText;
}

// insert the required number into the hint and set the singular/plural form
static Text BuildCountReq(const HintKey req, const Option& count) {
    Text requirement = Hint(req).GetTextCopy();
    if (count.Value<u8>() == 1) {
        requirement.SetForm(SINGULAR);
    } else {
        requirement.SetForm(PLURAL);
    }
    requirement.Replace("%d", std::to_string(count.Value<u8>()));
    return requirement;
}

static Text BuildBridgeReqsText() {
    Text bridgeText;

    if (Bridge.Is(RAINBOWBRIDGE_OPEN)) {
        bridgeText = Hint(BRIDGE_OPEN_HINT).GetText();

    } else if (Bridge.Is(RAINBOWBRIDGE_VANILLA)) {
        bridgeText = Hint(BRIDGE_VANILLA_HINT).GetText();

    } else if (Bridge.Is(RAINBOWBRIDGE_STONES)) {
        bridgeText = BuildCountReq(BRIDGE_STONES_HINT, BridgeStoneCount);

    } else if (Bridge.Is(RAINBOWBRIDGE_MEDALLIONS)) {
        bridgeText = BuildCountReq(BRIDGE_MEDALLIONS_HINT, BridgeMedallionCount);

    } else if (Bridge.Is(RAINBOWBRIDGE_REWARDS)) {
        bridgeText = BuildCountReq(BRIDGE_REWARDS_HINT, BridgeRewardCount);

    } else if (Bridge.Is(RAINBOWBRIDGE_DUNGEONS)) {
        bridgeText = BuildCountReq(BRIDGE_DUNGEONS_HINT, BridgeDungeonCount);

    } else if (Bridge.Is(RAINBOWBRIDGE_TOKENS)) {
        bridgeText = BuildCountReq(BRIDGE_TOKENS_HINT, BridgeTokenCount);

    } else if (Bridge.Is(RAINBOWBRIDGE_HEARTS)) {
        bridgeText = BuildCountReq(BRIDGE_HEARTS_HINT, BridgeHeartCount);
    }

    return Text() + ITEM_OBTAINED(ITEM_ARROW_LIGHT) + bridgeText + "^";
}

static Text BuildGanonBossKeyText() {
    Text ganonBossKeyText;

    if (GanonsBossKey.Is(GANONSBOSSKEY_START_WITH)) {
        ganonBossKeyText = Hint(GANON_BK_START_WITH_HINT).GetText();

    } else if (GanonsBossKey.Is(GANONSBOSSKEY_VANILLA)) {
        ganonBossKeyText = Hint(GANON_BK_VANILLA_HINT).GetText();

    } else if (GanonsBossKey.Is(GANONSBOSSKEY_OWN_DUNGEON)) {
        ganonBossKeyText = Hint(GANON_BK_OWN_DUNGEON_HINT).GetText();

    } else if (GanonsBossKey.Is(GANONSBOSSKEY_ANY_DUNGEON)) {
        ganonBossKeyText = Hint(GANON_BK_ANY_DUNGEON_HINT).GetText();

    } else if (GanonsBossKey.Is(GANONSBOSSKEY_OVERWORLD)) {
        ganonBossKeyText = Hint(GANON_BK_OVERWORLD_HINT).GetText();

    } else if (GanonsBossKey.Is(GANONSBOSSKEY_ANYWHERE)) {
        ganonBossKeyText = Hint(GANON_BK_ANYWHERE_HINT).GetText();

    } else if (GanonsBossKey.Is(GANONSBOSSKEY_TRIFORCE)) {
        ganonBossKeyText = Hint(GANON_BK_TRIFORCE_HINT).GetText();

    } else if (GanonsBossKey.Is(GANONSBOSSKEY_LACS_VANILLA)) {
        ganonBossKeyText = Hint(LACS_VANILLA_HINT).GetText();

    } else if (GanonsBossKey.Is(GANONSBOSSKEY_LACS_STONES)) {
        ganonBossKeyText = BuildCountReq(LACS_STONES_HINT, LACSStoneCount);

    } else if (GanonsBossKey.Is(GANONSBOSSKEY_LACS_MEDALLIONS)) {
        ganonBossKeyText = BuildCountReq(LACS_MEDALLIONS_HINT, LACSMedallionCount);

    } else if (GanonsBossKey.Is(GANONSBOSSKEY_LACS_REWARDS)) {
        ganonBossKeyText = BuildCountReq(LACS_REWARDS_HINT, LACSRewardCount);

    } else if (GanonsBossKey.Is(GANONSBOSSKEY_LACS_DUNGEONS)) {
        ganonBossKeyText = BuildCountReq(LACS_DUNGEONS_HINT, LACSDungeonCount);

    } else if (GanonsBossKey.Is(GANONSBOSSKEY_LACS_TOKENS)) {
        ganonBossKeyText = BuildCountReq(LACS_TOKENS_HINT, LACSTokenCount);

    } else if (GanonsBossKey.Is(GANONSBOSSKEY_LACS_HEARTS)) {
        ganonBossKeyText = BuildCountReq(LACS_HEARTS_HINT, LACSHeartCount);
    }

    return Text() + ITEM_OBTAINED(ITEM_KEY_BOSS) + ganonBossKeyText + "^";
}

static void CreateAltarText(const std::vector<Text>& rewardHints) {

    // Child Altar Text
    Text childText = Hint(SPIRITUAL_STONE_TEXT_START).GetText() +
                     // Spiritual Stones areas, skipped if already hinted by compasses.
                     (CompassesShowReward.Is(OFF)
                          ? (StartingKokiriEmerald.Value<u8>() ? Text{ "##" } : rewardHints[R_KOKIRI_EMERALD]) +
                                (StartingGoronRuby.Value<u8>() ? Text{ "##" } : rewardHints[R_GORON_RUBY]) +
                                (StartingZoraSapphire.Value<u8>() ? Text{ "##" } : rewardHints[R_ZORA_SAPPHIRE])
                          : Text{ "######" }) +
                     // How to open Door of Time, the event trigger is necessary to read the altar multiple times
                     "^" + BuildDoorOfTimeText() + EVENT_TRIGGER();

    CreateMessageFromTextObject(0x7040, 0, 2, 3, AddColorsAndFormat(childText, { QM_GREEN, QM_RED, QM_BLUE }));

    // Adult Altar Text
    Text adultText = Hint(ADULT_ALTAR_TEXT_START).GetText() +
                     // Medallions areas, skipped if already hinted by compasses.
                     (CompassesShowReward.Is(OFF)
                          ? (StartingLightMedallion.Value<u8>() ? Text{ "##" } : rewardHints[R_LIGHT_MEDALLION]) +
                                (StartingForestMedallion.Value<u8>() ? Text{ "##" } : rewardHints[R_FOREST_MEDALLION]) +
                                (StartingFireMedallion.Value<u8>() ? Text{ "##" } : rewardHints[R_FIRE_MEDALLION]) +
                                (StartingWaterMedallion.Value<u8>() ? Text{ "##" } : rewardHints[R_WATER_MEDALLION]) +
                                (StartingSpiritMedallion.Value<u8>() ? Text{ "##" } : rewardHints[R_SPIRIT_MEDALLION]) +
                                (StartingShadowMedallion.Value<u8>() ? Text{ "##" } : rewardHints[R_SHADOW_MEDALLION])
                          : Text{ "############" }) +
                     "^" +
                     // Bridge requirement
                     BuildBridgeReqsText() +
                     // Ganons Boss Key requirement
                     BuildGanonBossKeyText() +
                     // End
                     Hint(ADULT_ALTAR_TEXT_END).GetText() + EVENT_TRIGGER();

    CreateMessageFromTextObject(0x7088, 0, 2, 3,
                                AddColorsAndFormat(adultText, { QM_RED, QM_YELLOW, QM_GREEN, QM_RED, QM_BLUE, QM_YELLOW,
                                                                QM_PINK, QM_RED, QM_RED, QM_RED, QM_RED }));
}

static void CreateCompassAndGearMenuHints(const std::vector<Text>& rewardHints) {
    const std::vector<u8>& rewardColors    = { QM_GREEN, QM_RED,    QM_BLUE, QM_GREEN, QM_RED,
                                               QM_BLUE,  QM_YELLOW, QM_PINK, QM_YELLOW };
    std::vector<Text> formattedRewardHints = {};
    for (u32 rewardId = R_KOKIRI_EMERALD; rewardId < DUNGEON_REWARDS_COUNT; rewardId++) {
        formattedRewardHints.push_back(AddColorsAndFormat(rewardHints[rewardId], { rewardColors[rewardId] }));
    }
    std::vector<Text> baseCompassTexts = CreateBaseCompassTexts();

    // Create Compass messages
    for (u32 dungeonId = DUNGEON_DEKU_TREE; dungeonId <= DUNGEON_ICE_CAVERN; dungeonId++) {
        // Add reward hint to compass message if necessary
        if (Settings::CompassesShowReward && dungeonId <= DUNGEON_SHADOW_TEMPLE) {
            // If rewards are at End of Dungeons, the text will reveal what reward is at the end of the dungeon.
            // Otherwise, the text will reveal where the reward from that dungeon is located.
            u32 rewardId = Settings::ShuffleRewards.Is(REWARDSHUFFLE_END_OF_DUNGEON)
                               ? Settings::rDungeonRewardOverrides[dungeonId]
                               : dungeonId;

            baseCompassTexts[dungeonId] = baseCompassTexts[dungeonId] + formattedRewardHints[rewardId];
        } else {
            baseCompassTexts[dungeonId] = baseCompassTexts[dungeonId] + MESSAGE_END();
        }
        CreateMessageFromTextObject(0x9DA + dungeonId, 0, 2, 3, baseCompassTexts[dungeonId]);
    }

    // Create Gear Menu messages
    for (u32 rewardId = R_KOKIRI_EMERALD; rewardId < DUNGEON_REWARDS_COUNT; rewardId++) {
        Text rewardText = formattedRewardHints[rewardId];
        rewardText.Replace(WAIT_FOR_INPUT(), "");
        rewardText.Replace(MESSAGE_END(), SHOP_MESSAGE_BOX());
        rewardText = rewardText + MESSAGE_END();
        CreateMessageFromTextObject(0x7300 + rewardId, 0, 2, 3, rewardText);
    }
}

void CreateMiscHints() {
    const std::vector<Text>& rewardHints = {
        BuildDungeonRewardText(ITEM_KOKIRI_EMERALD, KOKIRI_EMERALD),
        BuildDungeonRewardText(ITEM_GORON_RUBY, GORON_RUBY),
        BuildDungeonRewardText(ITEM_ZORA_SAPPHIRE, ZORA_SAPPHIRE),
        BuildDungeonRewardText(ITEM_MEDALLION_FOREST, FOREST_MEDALLION),
        BuildDungeonRewardText(ITEM_MEDALLION_FIRE, FIRE_MEDALLION),
        BuildDungeonRewardText(ITEM_MEDALLION_WATER, WATER_MEDALLION),
        BuildDungeonRewardText(ITEM_MEDALLION_SPIRIT, SPIRIT_MEDALLION),
        BuildDungeonRewardText(ITEM_MEDALLION_SHADOW, SHADOW_MEDALLION),
        BuildDungeonRewardText(ITEM_MEDALLION_LIGHT, LIGHT_MEDALLION),
    };

    if (GanonHints) {
        CreateGanonText();
    }
    if (DampeHint) {
        CreateDampeHint();
    }
    if (ToTAltarHints) {
        CreateAltarText(rewardHints);
    }
    CreateCompassAndGearMenuHints(rewardHints);

    if (ShuffleMerchants.IsNot(SHUFFLEMERCHANTS_OFF)) {
        CreateMerchantsHints();
    }
    if (SkulltulaHints) {
        CreateSkulltulaHints();
    }
}

void CreateMerchantsHints() {
    Text medigoronItemText, grannyItemText, carpetSalesmanItemText;

    if (ShuffleMerchants.Is(SHUFFLEMERCHANTS_HINTS)) {
        medigoronItemText      = Location(GC_MEDIGORON)->GetPlacedItem().GetHint().GetTextCopy();
        grannyItemText         = Location(KAK_GRANNYS_SHOP)->GetPlacedItem().GetHint().GetTextCopy();
        carpetSalesmanItemText = Location(WASTELAND_BOMBCHU_SALESMAN)->GetPlacedItem().GetHint().GetTextCopy();
    } else {
        medigoronItemText = grannyItemText = carpetSalesmanItemText = hintTable[HINT_MYSTERIOUS].GetTextCopy();
    }
    Text carpetSalesmanItemClearText = Location(WASTELAND_BOMBCHU_SALESMAN)->GetPlacedItem().GetHint().GetClear();

    for (Text* itemText :
         { &medigoronItemText, &grannyItemText, &carpetSalesmanItemText, &carpetSalesmanItemClearText }) {
        itemText->Replace("$", "");
    }

    Text grannyCapitalItemText = grannyItemText.Capitalize();

    Text medigoronText = Hint(MEDIGORON_DIALOG).GetText();
    medigoronText.Replace("%s", medigoronItemText);
    Text grannyText            = grannyCapitalItemText + Hint(GRANNY_DIALOG).GetText();
    Text carpetSalesmanTextOne = Hint(CARPET_SALESMAN_DIALOG_FIRST).GetText();
    carpetSalesmanTextOne.Replace("%s", carpetSalesmanItemText);
    Text carpetSalesmanTextTwo = Hint(CARPET_SALESMAN_DIALOG_SECOND).GetText();
    carpetSalesmanTextTwo.Replace("%s", carpetSalesmanItemClearText);

    CreateMessageFromTextObject(0x9120, 0, 2, 3, AddColorsAndFormat(medigoronText, { QM_RED, QM_GREEN }));
    CreateMessageFromTextObject(0x9121, 0, 2, 3, AddColorsAndFormat(grannyText, { QM_RED, QM_GREEN }));
    CreateMessageFromTextObject(0x6077, 0, 2, 3, AddColorsAndFormat(carpetSalesmanTextOne, { QM_RED, QM_GREEN }));
    CreateMessageFromTextObject(0x6078, 0, 2, 3,
                                AddColorsAndFormat(carpetSalesmanTextTwo, { QM_RED, QM_YELLOW, QM_RED }));
}

void CreateGossipStoneHints() {

    PlacementLog_Msg("\nNOW CREATING HINTS\n");

    if (Settings::HintDistribution.Is(HINTDISTRIBUTION_PLAYTHROUGH)) {
        // Playthrough items that should not be hinted, such as those that are abundant or already hinted
        std::vector<ItemKey> ignoredItems = {
            // Small Collectibles
            GOLD_SKULLTULA_TOKEN, PIECE_OF_HEART, HEART_CONTAINER, TREASURE_GAME_HEART,
            // Small Keys
            FOREST_TEMPLE_SMALL_KEY, FIRE_TEMPLE_SMALL_KEY, WATER_TEMPLE_SMALL_KEY, SPIRIT_TEMPLE_SMALL_KEY,
            SHADOW_TEMPLE_SMALL_KEY, BOTTOM_OF_THE_WELL_SMALL_KEY, GERUDO_TRAINING_GROUNDS_SMALL_KEY,
            GERUDO_FORTRESS_SMALL_KEY, GANONS_CASTLE_SMALL_KEY
        };
        const auto ignore = [&](std::vector<ItemKey> v) {
            ignoredItems.insert(ignoredItems.end(), v.begin(), v.end());
        };
        if (Settings::BossKeysanity.Is(BOSSKEYSANITY_OWN_DUNGEON)) {
            ignore({ FOREST_TEMPLE_BOSS_KEY, FIRE_TEMPLE_BOSS_KEY, WATER_TEMPLE_BOSS_KEY, SPIRIT_TEMPLE_BOSS_KEY,
                     SHADOW_TEMPLE_BOSS_KEY, GANONS_CASTLE_BOSS_KEY });
        }
        if (Settings::ToTAltarHints || Settings::CompassesShowReward) {
            ignore({ KOKIRI_EMERALD, GORON_RUBY, ZORA_SAPPHIRE, FOREST_MEDALLION, FIRE_MEDALLION, WATER_MEDALLION,
                     SPIRIT_MEDALLION, SHADOW_MEDALLION, LIGHT_MEDALLION });
        }
        if (Settings::GanonHints) {
            ignore({ MASTER_SWORD, LIGHT_ARROWS });
        }
        if (Settings::GanonsBossKey.Value<u8>() >= GANONSBOSSKEY_LACS_VANILLA) {
            ignore({ GANONS_CASTLE_BOSS_KEY });
        }

        // Create playthrough hints
        for (auto& sphere : playthroughLocations) {
            for (auto& playthroughLoc : sphere) {
                const auto isIgnoredItem = [&](ItemKey item) {
                    for (auto& ignoredItem : ignoredItems) {
                        if (item == ignoredItem) {
                            return true;
                        }
                    }
                    return false;
                };
                auto& item = Location(playthroughLoc)->GetPlacedItem();
                if (item.IsMajorItem() && !isIgnoredItem(item.GetHintKey())) {
                    CreateAreaLocationHint(playthroughLoc);
                }
            }
        }

        // Bonus Hints
        if (Settings::BonusGossipHints) {
            std::vector<ItemKey> bonusItems = { SUNS_SONG };
            std::vector<ItemKey> warpSongs  = { PRELUDE_OF_LIGHT,  MINUET_OF_FOREST,  BOLERO_OF_FIRE,
                                                SERENADE_OF_WATER, REQUIEM_OF_SPIRIT, NOCTURNE_OF_SHADOW };
            Shuffle(warpSongs);
            bonusItems.insert(bonusItems.end(), warpSongs.begin(), warpSongs.end());

            for (auto& bonusItem : bonusItems) {
                // Skip if item is already in playthrough, so no double hint
                const auto bonusItemAlreadyInPlaythrough = [&] {
                    for (auto& sphere : playthroughLocations) {
                        for (auto& playthroughLoc : sphere) {
                            if (Location(playthroughLoc)->GetPlacedItemKey() == bonusItem) {
                                return true;
                            }
                        }
                    }
                    return false;
                };
                if (bonusItemAlreadyInPlaythrough()) {
                    continue;
                }

                auto bonusLocations = FilterFromPool(allLocations, [&](const LocationKey loc) {
                    return Location(loc)->GetPlacedItemKey() == bonusItem;
                });
                if (bonusLocations.size() > 0) {
                    CreateAreaLocationHint(RandomElement(bonusLocations));
                }
            }
        }
    } else {
        const HintSetting& hintSetting = hintSettingTable[Settings::HintDistribution.Value<u8>()];

        u8 remainingDungeonWothHints   = hintSetting.dungeonsWothLimit;
        u8 remainingDungeonBarrenHints = hintSetting.dungeonsBarrenLimit;

        // Add 'always' location hints
        if (hintSetting.distTable[static_cast<int>(HintType::Always)].copies > 0) {
            // Only filter locations that had a random item placed at them (e.g. don't get cow locations if shuffle cows
            // is off)
            auto alwaysHintLocations = FilterFromPool(allLocations, [](const LocationKey loc) {
                return Location(loc)->GetHint().GetType() == HintCategory::Always && Location(loc)->IsHintable() &&
                       !(Location(loc)->IsHintedAt());
            });

            for (auto& hint : conditionalAlwaysHints) {
                LocationKey loc = hint.first;
                if (hint.second() && Location(loc)->IsHintable() && !Location(loc)->IsHintedAt()) {
                    alwaysHintLocations.push_back(loc);
                }
            }

            for (LocationKey location : alwaysHintLocations) {
                CreateLocationHint({ location });
            }
        }

        // Add 'trial' location hints
        if (hintSetting.distTable[static_cast<int>(HintType::Trial)].copies > 0) {
            CreateTrialHints();
        }

        // create a vector with each hint type proportional to it's weight in the distribution setting.
        // ootr uses a weighted probability function to decide hint types, but selecting randomly from
        // this vector will do for now
        std::vector<HintType> remainingHintTypes = {};
        for (HintDistributionSetting hds : hintSetting.distTable) {
            remainingHintTypes.insert(remainingHintTypes.end(), hds.weight, hds.type);
        }
        Shuffle(remainingHintTypes);

        // get barren regions
        auto barrenLocations = CalculateBarrenRegions();

        // Calculate dungeon woth/barren info

        std::vector<std::string> dungeonNames = { "Deku Tree",     "Dodongos Cavern", "Jabu Jabus Belly",
                                                  "Forest Temple", "Fire Temple",     "Water Temple",
                                                  "Spirit Temple", "Shadow Temple",   "Bottom of the Well",
                                                  "Ice Cavern" };
        // Get list of all barren dungeons
        std::vector<std::string> barrenDungeons;
        for (LocationKey barrenLocation : barrenLocations) {
            std::string barrenRegion = GetHintRegion(Location(barrenLocation)->GetParentRegionKey())->scene;
            bool isDungeon = std::find(dungeonNames.begin(), dungeonNames.end(), barrenRegion) != dungeonNames.end();
            // If it hasn't already been added to the list and is a dungeon, add to list
            if (isDungeon &&
                std::find(barrenDungeons.begin(), barrenDungeons.end(), barrenRegion) == barrenDungeons.end()) {
                barrenDungeons.push_back(barrenRegion);
            }
        }
        PlacementLog_Msg("\nBarren Dungeons:\n");
        for (std::string barrenDungeon : barrenDungeons) {
            PlacementLog_Msg(barrenDungeon + "\n");
        }

        // Get list of all woth dungeons
        std::vector<std::string> wothDungeons;
        for (LocationKey wothLocation : wothLocations) {
            std::string wothRegion = GetHintRegion(Location(wothLocation)->GetParentRegionKey())->scene;
            bool isDungeon = std::find(dungeonNames.begin(), dungeonNames.end(), wothRegion) != dungeonNames.end();
            // If it hasn't already been added to the list and is a dungeon, add to list
            if (isDungeon && std::find(wothDungeons.begin(), wothDungeons.end(), wothRegion) == wothDungeons.end()) {
                wothDungeons.push_back(wothRegion);
            }
        }
        PlacementLog_Msg("\nWoth Dungeons:\n");
        for (std::string wothDungeon : wothDungeons) {
            PlacementLog_Msg(wothDungeon + "\n");
        }

        // Set DungeonInfo array for each dungeon
        for (uint i = 0; i < dungeonInfoData.size(); i++) {
            std::string dungeonName = dungeonNames[i];
            if (std::find(barrenDungeons.begin(), barrenDungeons.end(), dungeonName) != barrenDungeons.end()) {
                dungeonInfoData[i] = DungeonInfo::DUNGEON_BARREN;
            } else if (std::find(wothDungeons.begin(), wothDungeons.end(), dungeonName) != wothDungeons.end()) {
                dungeonInfoData[i] = DungeonInfo::DUNGEON_WOTH;
            } else {
                dungeonInfoData[i] = DungeonInfo::DUNGEON_NEITHER;
            }
        }

        std::array<std::string, 13> hintTypeNames = {
            "Trial", "Always", "WotH",      "Barren",  "Entrance", "Sometimes", "Random",
            "Item",  "Song",   "Overworld", "Dungeon", "Junk",     "NamedItem",
        };

        // while there are still gossip stones remaining
        while (FilterFromPool(gossipStoneLocations, [](const LocationKey loc) {
                   return Location(loc)->GetPlacedItemKey() == NONE;
               }).size() != 0) {
            // TODO: fixed hint types

            if (remainingHintTypes.empty()) {
                break;
            }

            // get a random hint type from the remaining hints
            HintType type = RandomElement(remainingHintTypes, true);

            PlacementLog_Msg("Attempting to make hint of type: ");
            PlacementLog_Msg(hintTypeNames[static_cast<int>(type)]);
            PlacementLog_Msg("\n");

            // create the appropriate hint for the type
            if (type == HintType::Woth) {
                CreateWothHint(&remainingDungeonWothHints);

            } else if (type == HintType::Barren) {
                CreateBarrenHint(&remainingDungeonBarrenHints, barrenLocations);

            } else if (type == HintType::Sometimes) {
                std::vector<LocationKey> sometimesHintLocations =
                    FilterFromPool(allLocations, [](const LocationKey loc) {
                        return Location(loc)->GetHint().GetType() == HintCategory::Sometimes &&
                               Location(loc)->IsHintable() && !(Location(loc)->IsHintedAt());
                    });
                CreateLocationHint(sometimesHintLocations);

            } else if (type == HintType::Random) {
                CreateRandomLocationHint();

            } else if (type == HintType::Item) {
                CreateGoodItemHint();

            } else if (type == HintType::Song) {
                std::vector<LocationKey> songHintLocations = FilterFromPool(allLocations, [](const LocationKey loc) {
                    return Location(loc)->IsCategory(Category::cSong) && Location(loc)->IsHintable() &&
                           !(Location(loc)->IsHintedAt());
                });
                CreateLocationHint(songHintLocations);

            } else if (type == HintType::Overworld) {
                std::vector<LocationKey> overworldHintLocations =
                    FilterFromPool(allLocations, [](const LocationKey loc) {
                        return Location(loc)->IsOverworld() && Location(loc)->IsHintable() &&
                               !(Location(loc)->IsHintedAt());
                    });
                CreateLocationHint(overworldHintLocations);

            } else if (type == HintType::Dungeon) {
                std::vector<LocationKey> dungeonHintLocations = FilterFromPool(allLocations, [](const LocationKey loc) {
                    return Location(loc)->IsDungeon() && Location(loc)->IsHintable() && !(Location(loc)->IsHintedAt());
                });
                CreateLocationHint(dungeonHintLocations);

            } else if (type == HintType::Junk) {
                CreateJunkHint();
            }
        }
    }

    // If any gossip stones failed to have a hint placed on them for some reason, place a junk hint as a failsafe.
    for (LocationKey gossipStone : FilterFromPool(
             gossipStoneLocations, [](const LocationKey loc) { return Location(loc)->GetPlacedItemKey() == NONE; })) {
        const HintText junkHint = RandomElement(GetHintCategory(HintCategory::Junk));
        AddHint(junkHint.GetText(), gossipStone, { QM_PINK });
    }

    // Getting gossip stone locations temporarily sets one location to not be reachable.
    // Call the function one last time to get rid of false positives on locations not
    // being reachable.
    GetAccessibleLocations({});
}
