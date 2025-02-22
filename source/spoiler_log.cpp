#include "spoiler_log.hpp"

#include "dungeon.hpp"
#include "item_list.hpp"
#include "item_location.hpp"
#include "entrance.hpp"
#include "random.hpp"
#include "settings.hpp"
#include "trial.hpp"
#include "tinyxml2.h"
#include "utils.hpp"
#include "shops.hpp"
#include "gold_skulltulas.hpp"

#include <3ds.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

namespace {
std::string placementtxt;

constexpr std::array<std::string_view, 32> hashIcons = {
    "Deku Stick",   "Deku Nut",       "Bow",           "Slingshot",       "Fairy Ocarina",  "Bombchu",
    "Longshot",     "Boomerang",      "Lens of Truth", "Beans",           "Megaton Hammer", "Bottled Fish",
    "Bottled Milk", "Mask of Truth",  "SOLD OUT",      "Cucco",           "Mushroom",       "Saw",
    "Frog",         "Master Sword",   "Mirror Shield", "Kokiri Tunic",    "Hover Boots",    "Silver Gauntlets",
    "Gold Scale",   "Shard of Agony", "Skull Token",   "Heart Container", "Boss Key",       "Compass",
    "Map",          "Big Magic",
};
} // namespace

static RandomizerHash randomizerHash;
static SpoilerData spoilerData;
static std::array<SpoilerDataLocs, SPOILER_LOCDATS> spoilerDataLocs;

void InitLogDirectories(FS_Archive sdmcArchive) {
    std::vector<std::string> dirs = {
        "/OoT3DR/",
        "/OoT3DR/Logs/",
    };

    const char* stylesheetSrc  = "romfs:/spoiler-log.css";
    const char* stylesheetDest = "/OoT3DR/Logs/spoiler-log.css";

    const auto printInfo = [&](int progress) {
        consoleClear();
        printf("\x1b[10;10HCreating Log Directories");
        printf("\x1b[11;10HProgress: %d/%d", progress, dirs.size());
    };

    printInfo(0);
    for (size_t i = 0; i < dirs.size(); i++) {
        FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, dirs[i].c_str()), FS_ATTRIBUTE_DIRECTORY);
        printInfo(i + 1);
    }

    Result rc = romfsInit();
    if (rc) {
        printf("\nromfsInit: %08lX\n", rc);
    }
    CopyFile(sdmcArchive, stylesheetDest, stylesheetSrc);
    romfsExit();
}

void GenerateHash() {
    for (size_t i = 0; i < randomizerHash.size(); i++) {
        const auto iconIndex         = static_cast<u8>(Random(0, hashIcons.size()));
        Settings::hashIconIndexes[i] = iconIndex;
        randomizerHash[i]            = hashIcons[iconIndex];
    }

    // Clear out spoiler log data here, in case we aren't going to re-generate it
    spoilerData     = { 0 };
    spoilerDataLocs = { 0 };
}

const RandomizerHash& GetRandomizerHash() {
    return randomizerHash;
}

// Returns the randomizer hash as concatenated string, separated by comma.
const std::string GetRandomizerHashAsString() {
    std::string hash = "";
    for (const std::string& str : randomizerHash) {
        hash += str + ", ";
    }
    hash.erase(hash.length() - 2); // Erase last comma
    return hash;
}

const SpoilerData* GetSpoilerData() {
    return &spoilerData;
}

const SpoilerDataLocs* GetSpoilerDataLocs(size_t index) {
    return &spoilerDataLocs[index];
}

static auto GetGeneralPath() {
    return "/OoT3DR/Logs/" + Settings::seed + " (" + GetRandomizerHashAsString() + ")";
}

static auto GetSpoilerLogPath() {
    return GetGeneralPath() + "-spoilerlog.xml";
}

static auto GetPlacementLogPath() {
    return GetGeneralPath() + "-placementlog.xml";
}

void WriteIngameSpoilerLog() {
    u16 spoilerTotalItems       = 0;
    u16 spoilerItemIndex        = 0;
    u32 spoilerStringOffset     = 0;
    u16 spoilerSphereItemoffset = 0;
    u16 spoilerGroupOffset      = 0;
    // Intentionally junk value so we trigger the 'new group, record some stuff' code
    u8 currentGroup        = SpoilerCollectionCheckGroup::SPOILER_COLLECTION_GROUP_COUNT;
    bool spoilerOutOfSpace = false;

    // Create map of string data offsets for all _unique_ item locations and names in the playthrough
    // Some item names, like gold skulltula tokens, can appear many times in a playthrough
    std::unordered_map<LocationKey, u16>
        itemLocationsMap; // Map of LocationKey to an index into spoiler data item locations
    itemLocationsMap.reserve(allLocations.size());
    std::unordered_map<std::string, u16>
        stringOffsetMap; // Map of strings to their offset into spoiler string data array
    stringOffsetMap.reserve(allLocations.size() * 2);

    // Sort all locations by their group, so the in-game log can show a group of items by simply starting/ending at
    // certain indices
    std::stable_sort(allLocations.begin(), allLocations.end(), [](const LocationKey& a, const LocationKey& b) {
        auto groupA = Location(a)->GetCollectionCheckGroup();
        auto groupB = Location(b)->GetCollectionCheckGroup();
        return groupA < groupB;
    });

    for (const LocationKey key : allLocations) {
        if (spoilerTotalItems >= SPOILER_ITEMS_MAX * SPOILER_LOCDATS) {
            spoilerOutOfSpace = true;
            break;
        }
        SpoilerDataLocs* splrDatLoc = &spoilerDataLocs[spoilerTotalItems / SPOILER_ITEMS_MAX];

        auto loc = Location(key);

        // Hide excluded locations from ingame tracker
        if (loc->IsExcluded()) {
            continue;
        }
        // Cows
        else if (!Settings::ShuffleCows && loc->IsCategory(Category::cCow)) {
            continue;
        }
        // Merchants
        else if (Settings::ShuffleMerchants.Is(SHUFFLEMERCHANTS_OFF) && loc->IsCategory(Category::cMerchant) &&
                 key != WASTELAND_BOMBCHU_SALESMAN) { // The bombchu salesman is handled below
            continue;
        }
        // Adult Trade
        else if (!Settings::ShuffleAdultTradeQuest && loc->IsCategory(Category::cAdultTrade)) {
            continue;
        }
        // Chest Minigame
        else if (Settings::ShuffleChestMinigame.Is(SHUFFLECHESTMINIGAME_OFF) &&
                 loc->IsCategory(Category::cChestMinigame)) {
            continue;
        }
        // Frog Song Rupees
        else if (!Settings::ShuffleFrogSongRupees && loc->IsCategory(Category::cFrogRupees)) {
            continue;
        }
        // Gerudo Fortress
        else if ((Settings::GerudoFortress.Is(GERUDOFORTRESS_OPEN) &&
                  (loc->IsCategory(Category::cVanillaGFSmallKey) || loc->GetHintKey() == GF_GERUDO_TOKEN)) ||
                 (Settings::GerudoFortress.Is(GERUDOFORTRESS_FAST) && loc->IsCategory(Category::cVanillaGFSmallKey) &&
                  loc->GetHintKey() != GF_NORTH_F1_CARPENTER)) {
            continue;
        }

        // Copy at most 51 chars from the name and location name to avoid issues with names that don't fit on screen
        // Only copy enough characters that can fit on the screen
        const char* locNameFormat  = "%.51s";
        const char* itemNameFormat = "%.49s";

        auto locName = loc->GetName();
        if (stringOffsetMap.find(locName) == stringOffsetMap.end()) {
            if (spoilerStringOffset + locName.size() + 1 >= SPOILER_STRING_DATA_SIZE) {
                spoilerOutOfSpace = true;
                break;
            } else {
                stringOffsetMap[locName] = spoilerStringOffset;
                spoilerStringOffset +=
                    sprintf(&splrDatLoc->StringData[spoilerStringOffset], locNameFormat, locName.c_str()) + 1;
            }
        }

        auto locItem = loc->GetPlacedItemName().GetNAEnglish();
        if (loc->IsCategory(Category::cShop)) {
            if (loc->GetPlacedItemKey() == ICE_TRAP) {
                locItem = NonShopItems[TransformShopIndex(GetShopIndex(key))].Name.GetNAEnglish();
            }
            locItem += ": " + std::to_string(loc->GetPrice()) + " Rupees";
        }
        if (stringOffsetMap.find(locItem) == stringOffsetMap.end()) {
            if (spoilerStringOffset + locItem.size() + 1 >= SPOILER_STRING_DATA_SIZE) {
                spoilerOutOfSpace = true;
                break;
            } else {
                stringOffsetMap[locItem] = spoilerStringOffset;
                spoilerStringOffset +=
                    sprintf(&splrDatLoc->StringData[spoilerStringOffset], itemNameFormat, locItem.c_str()) + 1;
            }
        }

        splrDatLoc->ItemLocations[spoilerItemIndex].LocationStrOffset   = stringOffsetMap[locName];
        splrDatLoc->ItemLocations[spoilerItemIndex].ItemStrOffset       = stringOffsetMap[locItem];
        splrDatLoc->ItemLocations[spoilerItemIndex].CollectionCheckType = loc->GetCollectionCheck().type;
        splrDatLoc->ItemLocations[spoilerItemIndex].LocationScene       = loc->GetCollectionCheck().scene;
        splrDatLoc->ItemLocations[spoilerItemIndex].LocationFlag        = loc->GetCollectionCheck().flag;

        // Collect Type and Reveal Type
        if (key == GANON) {
            splrDatLoc->ItemLocations[spoilerItemIndex].CollectType = COLLECTTYPE_NEVER;
            splrDatLoc->ItemLocations[spoilerItemIndex].RevealType  = REVEALTYPE_ALWAYS;
        } else if (key == TOT_LIGHT_ARROWS_CUTSCENE &&
                   (Settings::GanonsBossKey.Value<u8>() >= GANONSBOSSKEY_LACS_VANILLA)) {
            splrDatLoc->ItemLocations[spoilerItemIndex].RevealType = REVEALTYPE_ALWAYS;
        } else if (key == MARKET_BOMBCHU_BOWLING_BOMBCHUS) {
            splrDatLoc->ItemLocations[spoilerItemIndex].CollectType = COLLECTTYPE_REPEATABLE;
            splrDatLoc->ItemLocations[spoilerItemIndex].RevealType  = REVEALTYPE_ALWAYS;
        } else if (key == ZR_MAGIC_BEAN_SALESMAN && !Settings::ShuffleMagicBeans) {
            splrDatLoc->ItemLocations[spoilerItemIndex].RevealType = REVEALTYPE_ALWAYS;
        } else if (key == WASTELAND_BOMBCHU_SALESMAN && Settings::ShuffleMerchants.Is(SHUFFLEMERCHANTS_OFF)) {
            splrDatLoc->ItemLocations[spoilerItemIndex].CollectType = COLLECTTYPE_REPEATABLE;
            splrDatLoc->ItemLocations[spoilerItemIndex].RevealType  = REVEALTYPE_ALWAYS;
        }
        // Shops
        else if (loc->IsShop()) {
            if (Settings::Shopsanity.Is(SHOPSANITY_OFF)) {
                splrDatLoc->ItemLocations[spoilerItemIndex].RevealType = REVEALTYPE_ALWAYS;
            } else {
                splrDatLoc->ItemLocations[spoilerItemIndex].RevealType = REVEALTYPE_SCENE;
            }
            if (loc->GetPlacedItem().GetItemType() == ITEMTYPE_REFILL ||
                loc->GetPlacedItem().GetItemType() == ITEMTYPE_SHOP ||
                loc->GetPlacedItem().GetHintKey() == PROGRESSIVE_BOMBCHUS) {
                splrDatLoc->ItemLocations[spoilerItemIndex].CollectType = COLLECTTYPE_REPEATABLE;
            }
        }
        // Gold Skulltulas
        else if (loc->IsCategory(Category::cSkulltula) &&
                 ((Settings::Tokensanity.Is(TOKENSANITY_OFF)) ||
                  (Settings::Tokensanity.Is(TOKENSANITY_DUNGEONS) && !loc->IsDungeon()) ||
                  (Settings::Tokensanity.Is(TOKENSANITY_OVERWORLD) && loc->IsDungeon()))) {
            splrDatLoc->ItemLocations[spoilerItemIndex].RevealType = REVEALTYPE_ALWAYS;
        }
        // Deku Scrubs
        else if (loc->IsCategory(Category::cDekuScrub) && !loc->IsCategory(Category::cDekuScrubUpgrades) &&
                 Settings::Scrubsanity.Is(SCRUBSANITY_OFF)) {
            splrDatLoc->ItemLocations[spoilerItemIndex].CollectType = COLLECTTYPE_REPEATABLE;
            splrDatLoc->ItemLocations[spoilerItemIndex].RevealType  = REVEALTYPE_ALWAYS;
        }

        auto checkGroup                                   = loc->GetCollectionCheckGroup();
        splrDatLoc->ItemLocations[spoilerItemIndex].Group = checkGroup;

        // Group setup
        if (checkGroup != currentGroup) {
            currentGroup                           = checkGroup;
            spoilerData.GroupOffsets[currentGroup] = spoilerGroupOffset;
        }
        ++spoilerData.GroupItemCounts[currentGroup];
        ++spoilerGroupOffset;

        itemLocationsMap[key] = spoilerTotalItems++;

        spoilerItemIndex++;
        if (spoilerItemIndex >= SPOILER_ITEMS_MAX) {
            stringOffsetMap.clear();
            spoilerItemIndex    = 0;
            spoilerStringOffset = 0;
        }
    }
    spoilerData.ItemLocationsCount = spoilerTotalItems;

    if (Settings::IngameSpoilers) {
        bool playthroughItemNotFound = false;
        // Write playthrough data to in-game spoiler log
        if (!spoilerOutOfSpace) {
            for (u32 i = 0; i < playthroughLocations.size(); i++) {
                if (i >= SPOILER_SPHERES_MAX) {
                    spoilerOutOfSpace = true;
                    break;
                }
                spoilerData.Spheres[i].ItemLocationsOffset = spoilerSphereItemoffset;
                for (u32 loc = 0; loc < playthroughLocations[i].size(); ++loc) {
                    if (spoilerSphereItemoffset >= SPOILER_ITEMS_MAX) {
                        spoilerOutOfSpace = true;
                        break;
                    }

                    const auto foundItemLoc = itemLocationsMap.find(playthroughLocations[i][loc]);
                    if (foundItemLoc != itemLocationsMap.end()) {
                        spoilerData.SphereItemLocations[spoilerSphereItemoffset++] = foundItemLoc->second;
                    } else {
                        playthroughItemNotFound = true;
                    }
                    ++spoilerData.Spheres[i].ItemCount;
                }
                ++spoilerData.SphereCount;
            }
        }
        if (spoilerOutOfSpace || playthroughItemNotFound) {
            printf("%sError!%s ", YELLOW, WHITE);
        }
    }
}

// Writes the location to the specified node.
static void WriteLocation(tinyxml2::XMLElement* parentNode, const LocationKey locationKey,
                          const bool withPadding = false) {
    ItemLocation* location = Location(locationKey);

    auto node = parentNode->InsertNewChildElement("location");
    node->SetAttribute("name", location->GetName().c_str());
    node->SetText(location->GetPlacedItemName().GetNAEnglish().c_str());

    if (withPadding) {
        constexpr int16_t LONGEST_NAME    = 56; // The longest name of a location.
        constexpr int16_t PRICE_ATTRIBUTE = 12; // Length of a 3-digit price attribute.

        // Insert a padding so we get a kind of table in the XML document.
        int16_t requiredPadding = LONGEST_NAME - location->GetName().length();
        if (location->IsCategory(Category::cShop)) {
            // Shop items have short location names, but come with an additional price attribute.
            requiredPadding -= PRICE_ATTRIBUTE;
        }
        if (requiredPadding >= 0) {
            std::string padding(requiredPadding, ' ');
            node->SetAttribute("_", padding.c_str());
        }
    }

    if (location->IsCategory(Category::cShop)) {
        char price[6];
        sprintf(price, "%03d", location->GetPrice());
        node->SetAttribute("price", price);
    }
    if (!location->IsAddedToPool()) {
#ifdef ENABLE_DEBUG
        node->SetAttribute("not-added", true);
#endif
    }
}

// Writes a shuffled entrance to the specified node
static void WriteShuffledEntrance(tinyxml2::XMLElement* parentNode, Entrance* entrance,
                                  const bool withPadding = false) {
    auto node = parentNode->InsertNewChildElement("entrance");
    node->SetAttribute("name", entrance->GetName().c_str());
    auto text = entrance->GetConnectedRegion()->regionName + " from " +
                entrance->GetReplacement()->GetParentRegion()->regionName;
    node->SetText(text.c_str());

    if (withPadding) {
        constexpr int16_t LONGEST_NAME = 56; // The longest name of a vanilla entrance

        // Insert padding so we get a kind of table in the XML document
        int16_t requiredPadding = LONGEST_NAME - entrance->GetName().length();
        if (requiredPadding > 0) {
            std::string padding(requiredPadding, ' ');
            node->SetAttribute("_", padding.c_str());
        }
    }
}

// Create a checkbox that collapses the next section when checked
static tinyxml2::XMLElement* CreateCollapseCheckbox(tinyxml2::XMLDocument& spoilerLog,
                                                    const bool startCollapsed = true) {
    auto collapseCheckbox = spoilerLog.NewElement("h:input");
    collapseCheckbox->SetAttribute("type", "checkbox");
    collapseCheckbox->SetAttribute("class", "collapse");
    if (startCollapsed) {
        collapseCheckbox->SetAttribute("checked", "");
    }
    return collapseCheckbox;
}

// Writes the settings (without excluded locations, starting inventory and tricks) to the spoilerLog document.
static void WriteSettings(tinyxml2::XMLDocument& spoilerLog, const bool printAll = false) {
    auto parentNode = spoilerLog.NewElement("settings");

    std::vector<Menu*> allMenus = Settings::GetAllOptionMenus();

    for (const Menu* menu : allMenus) {
        // This is a menu of settings, write them
        if (menu->mode == OPTION_MENU && menu->printInSpoiler) {
            for (const Option* setting : *menu->settingsList) {
                if (printAll || (!setting->IsHidden() && setting->IsCategory(OptionCategory::Setting))) {
                    auto node = parentNode->InsertNewChildElement("setting");
                    node->SetAttribute("name", SanitizedString(setting->GetName()).c_str());
                    node->SetText(setting->GetSelectedOptionText().c_str());
                }
            }
        }
    }
    spoilerLog.RootElement()->InsertEndChild(parentNode);
}

// Writes the excluded locations to the spoiler log, if there are any.
static void WriteExcludedLocations(tinyxml2::XMLDocument& spoilerLog) {
    auto parentNode = spoilerLog.NewElement("excluded-locations");

    for (size_t i = 1; i < Settings::excludeLocationsOptionsVector.size(); i++) {
        for (const auto& location : Settings::excludeLocationsOptionsVector[i]) {
            if (location->GetSelectedOptionIndex() == INCLUDE) {
                continue;
            }

            tinyxml2::XMLElement* node = spoilerLog.NewElement("location");
            node->SetAttribute("name", SanitizedString(location->GetName()).c_str());
            parentNode->InsertEndChild(node);
        }
    }

    if (!parentNode->NoChildren()) {
        spoilerLog.RootElement()->InsertEndChild(parentNode);
    }
}

// Writes the starting inventory to the spoiler log, if there is any.
static void WriteStartingInventory(tinyxml2::XMLDocument& spoilerLog, const bool collapsible = false) {
    auto parentNode = spoilerLog.NewElement("starting-inventory");

    std::vector<std::vector<Option*>*> startingInventoryOptions = {
        &Settings::startingItemsOptions,
        &Settings::startingSongsOptions,
        &Settings::startingEquipmentOptions,
        &Settings::startingStonesMedallionsOptions,
    };

    if (Settings::ShuffleEnemySouls) {
        startingInventoryOptions.push_back(&Settings::startingEnemySoulsOptions);
    }

    if (Settings::ShuffleOcarinaButtons) {
        startingInventoryOptions.push_back(&Settings::startingOcarinaButtonsOptions);
    }

    for (std::vector<Option*>* menu : startingInventoryOptions) {
        for (size_t i = 0; i < menu->size(); ++i) {
            const auto setting = menu->at(i);
            // Ignore no starting bottles and the Choose/All On toggles
            if (setting->IsDefaultSelected()) {
                continue;
            }

            auto node = parentNode->InsertNewChildElement("item");
            node->SetAttribute("name", setting->GetName().c_str());
            node->SetText(setting->GetSelectedOptionText().c_str());
        }
    }

    if (!parentNode->NoChildren()) {
        if (collapsible) {
            spoilerLog.RootElement()->InsertEndChild(CreateCollapseCheckbox(spoilerLog));
        }
        spoilerLog.RootElement()->InsertEndChild(parentNode);
    }
}

// Writes the enabled tricks to the spoiler log, if there are any.
static void WriteEnabledTricks(tinyxml2::XMLDocument& spoilerLog) {
    auto parentNode = spoilerLog.NewElement("enabled-tricks");

    for (const auto& setting : Settings::trickOptions) {
        if (setting->GetSelectedOptionIndex() != TRICK_ENABLED || !setting->IsCategory(OptionCategory::Setting)) {
            continue;
        }

        auto node = parentNode->InsertNewChildElement("trick");
        node->SetAttribute("name", SanitizedString(setting->GetName()).c_str());
    }

    if (!parentNode->NoChildren()) {
        spoilerLog.RootElement()->InsertEndChild(parentNode);
    }
}

// Writes the enabled glitches to the spoiler log, if there are any.
static void WriteEnabledGlitches(tinyxml2::XMLDocument& spoilerLog) {
    auto parentNode = spoilerLog.NewElement("enabled-glitches");

    for (const auto& setting : Settings::glitchCategories) {
        if (setting->Value<u8>() == 0) {
            continue;
        }

        auto node = parentNode->InsertNewChildElement("glitch-category");
        node->SetAttribute("name", setting->GetName().c_str());
        node->SetText(setting->GetSelectedOptionText().c_str());
    }

    for (const auto& setting : Settings::miscGlitches) {
        if (!setting->Value<bool>()) {
            continue;
        }

        auto node = parentNode->InsertNewChildElement("misc-glitch");
        node->SetAttribute("name", SanitizedString(setting->GetName()).c_str());
    }

    if (!parentNode->NoChildren()) {
        spoilerLog.RootElement()->InsertEndChild(parentNode);
    }
}

// Writes the Master Quest dungeons to the spoiler log, if there are any.
static void WriteMasterQuestDungeons(tinyxml2::XMLDocument& spoilerLog, const bool collapsible = false) {
    auto parentNode = spoilerLog.NewElement("master-quest-dungeons");

    for (const auto* dungeon : Dungeon::dungeonList) {
        if (dungeon->IsVanilla()) {
            continue;
        }

        auto node = parentNode->InsertNewChildElement("dungeon");
        node->SetAttribute("name", dungeon->GetName().c_str());
    }

    if (!parentNode->NoChildren()) {
        if (collapsible) {
            spoilerLog.RootElement()->InsertEndChild(CreateCollapseCheckbox(spoilerLog));
        }
        spoilerLog.RootElement()->InsertEndChild(parentNode);
    }
}

// Writes the required trails to the spoiler log, if there are any.
static void WriteRequiredTrials(tinyxml2::XMLDocument& spoilerLog) {
    auto parentNode = spoilerLog.NewElement("required-trials");

    for (const auto* trial : Trial::trialList) {
        if (trial->IsSkipped()) {
            continue;
        }

        auto node        = parentNode->InsertNewChildElement("trial");
        std::string name = trial->GetName().GetNAEnglish();
        name[0]          = toupper(name[0]); // Capitalize T in "The"
        node->SetAttribute("name", name.c_str());
    }

    if (!parentNode->NoChildren()) {
        spoilerLog.RootElement()->InsertEndChild(parentNode);
    }
}

// Writes the area and a description of where any moved Gold Skulltulas are.
static void WriteNewGsLocations(tinyxml2::XMLDocument& spoilerLog, const bool collapsible = false) {
    if (!Settings::RandomGsLocations) {
        return;
    }

    auto parentNode = spoilerLog.NewElement("gold-skulltulas");

    for (auto gs : gsTable) {
        if (!gs.second->IsRelevant() || gs.second->GetAssignedLocation() == nullptr) {
            continue;
        }

        auto node = parentNode->InsertNewChildElement("gs");

        node->SetAttribute("name", Location(gs.first)->GetName().c_str());

        constexpr int16_t LONGEST_NAME = 56; // The longest name of a location.
        // Insert a padding so we get a kind of table in the XML document.
        int16_t requiredPadding = LONGEST_NAME - Location(gs.first)->GetName().length();
        if (requiredPadding >= 0) {
            std::string padding(requiredPadding, ' ');
            node->SetAttribute("_", padding.c_str());
        }

        std::string locationStr = AreaTable(gs.second->GetAssignedLocation()->areaKey)->regionName + ": " +
                                  gs.second->GetAssignedLocation()->description.data();
        node->SetText(locationStr.c_str());
    }

    if (collapsible) {
        spoilerLog.RootElement()->InsertEndChild(CreateCollapseCheckbox(spoilerLog));
    }
    spoilerLog.RootElement()->InsertEndChild(parentNode);
}

// Writes the intended playthrough to the spoiler log, separated into spheres.
static void WritePlaythrough(tinyxml2::XMLDocument& spoilerLog, const bool collapsible = false) {
    auto playthroughNode = spoilerLog.NewElement("playthrough");

    for (uint i = 0; i < playthroughLocations.size(); ++i) {
        if (collapsible) {
            playthroughNode->InsertEndChild(CreateCollapseCheckbox(spoilerLog));
        }
        auto sphereNode = playthroughNode->InsertNewChildElement("sphere");
        sphereNode->SetAttribute("level", i + 1);

        for (const LocationKey key : playthroughLocations[i]) {
            WriteLocation(sphereNode, key, true);
        }
    }

    if (collapsible) {
        spoilerLog.RootElement()->InsertEndChild(CreateCollapseCheckbox(spoilerLog));
    }
    spoilerLog.RootElement()->InsertEndChild(playthroughNode);
}

// Write the randomized entrance playthrough to the spoiler log, if applicable
static void WriteShuffledEntrances(tinyxml2::XMLDocument& spoilerLog, const bool collapsible = false) {
    if (!Settings::ShuffleEntrances || noRandomEntrances) {
        return;
    }

    auto playthroughNode = spoilerLog.NewElement("entrance-playthrough");

    for (uint i = 0; i < playthroughEntrances.size(); ++i) {
        if (collapsible) {
            playthroughNode->InsertEndChild(CreateCollapseCheckbox(spoilerLog));
        }
        auto sphereNode = playthroughNode->InsertNewChildElement("sphere");
        sphereNode->SetAttribute("level", i + 1);

        for (Entrance* entrance : playthroughEntrances[i]) {
            WriteShuffledEntrance(sphereNode, entrance, true);
        }
    }

    if (collapsible) {
        spoilerLog.RootElement()->InsertEndChild(CreateCollapseCheckbox(spoilerLog));
    }
    spoilerLog.RootElement()->InsertEndChild(playthroughNode);
}

// Writes the WOTH locations to the spoiler log, if there are any.
static void WriteWayOfTheHeroLocation(tinyxml2::XMLDocument& spoilerLog, const bool collapsible = false) {
    auto parentNode = spoilerLog.NewElement("way-of-the-hero-locations");

    for (const LocationKey key : wothLocations) {
        WriteLocation(parentNode, key, true);
    }

    if (!parentNode->NoChildren()) {
        if (collapsible) {
            spoilerLog.RootElement()->InsertEndChild(CreateCollapseCheckbox(spoilerLog));
        }
        spoilerLog.RootElement()->InsertEndChild(parentNode);
    }
}

// Writes the hints to the spoiler log, if they are enabled.
static void WriteHints(tinyxml2::XMLDocument& spoilerLog) {
    if (Settings::GossipStoneHints.Is(HINTS_NO_HINTS)) {
        return;
    }

    auto parentNode = spoilerLog.NewElement("hints");

    for (const LocationKey key : gossipStoneLocations) {
        ItemLocation* location = Location(key);

        auto node = parentNode->InsertNewChildElement("hint");
        node->SetAttribute("location", location->GetName().c_str());

        auto text = location->GetPlacedItemName().GetNAEnglish();
        std::replace(text.begin(), text.end(), '&', ' ');
        std::replace(text.begin(), text.end(), '^', ' ');
        node->SetText(text.c_str());
    }

    spoilerLog.RootElement()->InsertEndChild(parentNode);
}

static void WriteAllLocations(tinyxml2::XMLDocument& spoilerLog, const bool collapsible = false) {
    auto parentNode = spoilerLog.NewElement("all-locations");

    for (const LocationKey key : allLocations) {
        if (!Location(key)->IsHidden()) {
            WriteLocation(parentNode, key, true);
        }
    }

    if (collapsible) {
        spoilerLog.RootElement()->InsertEndChild(CreateCollapseCheckbox(spoilerLog));
    }
    spoilerLog.RootElement()->InsertEndChild(parentNode);
}

bool SpoilerLog_Write() {
    auto spoilerLog = tinyxml2::XMLDocument(false);
    spoilerLog.InsertEndChild(spoilerLog.NewDeclaration());
    spoilerLog.InsertEndChild(spoilerLog.NewDeclaration("xml-stylesheet href=\"spoiler-log.css\""));

    auto rootNode = spoilerLog.NewElement("spoiler-log");
    spoilerLog.InsertEndChild(rootNode);

    rootNode->SetAttribute("version", Settings::version.c_str());
    rootNode->SetAttribute("seed", Settings::seed.c_str());
    rootNode->SetAttribute("hash", GetRandomizerHashAsString().c_str());
    rootNode->SetAttribute("xmlns:h", "http://www.w3.org/1999/xhtml");

    auto hideSpoilersCheckbox = spoilerLog.NewElement("h:input");
    hideSpoilersCheckbox->SetAttribute("type", "checkbox");
    hideSpoilersCheckbox->SetAttribute("checked", "");
    hideSpoilersCheckbox->SetAttribute("id", "hide-spoilers");
    rootNode->InsertEndChild(hideSpoilersCheckbox);

    WriteSettings(spoilerLog);
    WriteExcludedLocations(spoilerLog);
    WriteStartingInventory(spoilerLog, true);
    WriteEnabledTricks(spoilerLog);
    if (Settings::Logic.Is(LOGIC_GLITCHED)) {
        WriteEnabledGlitches(spoilerLog);
    }
    WriteMasterQuestDungeons(spoilerLog, true);
    WriteRequiredTrials(spoilerLog);
    WriteNewGsLocations(spoilerLog, true);
    WritePlaythrough(spoilerLog, true);
    WriteWayOfTheHeroLocation(spoilerLog, true);

    playthroughLocations.clear();
    playthroughBeatable = false;
    wothLocations.clear();

    WriteHints(spoilerLog);
    WriteShuffledEntrances(spoilerLog, true);
    WriteAllLocations(spoilerLog, true);

    auto e = spoilerLog.SaveFile(GetSpoilerLogPath().c_str());
    return e == tinyxml2::XML_SUCCESS;
}

void PlacementLog_Msg(std::string_view msg) {
    placementtxt += msg;
}

void PlacementLog_Clear() {
    placementtxt = "";
}

bool PlacementLog_Write() {
    auto placementLog = tinyxml2::XMLDocument(false);
    placementLog.InsertEndChild(placementLog.NewDeclaration());

    auto rootNode = placementLog.NewElement("placement-log");
    placementLog.InsertEndChild(rootNode);

    rootNode->SetAttribute("version", Settings::version.c_str());
    rootNode->SetAttribute("seed", Settings::seed.c_str());
    rootNode->SetAttribute("hash", GetRandomizerHashAsString().c_str());

    WriteSettings(placementLog, true); // Include hidden settings.
    WriteExcludedLocations(placementLog);
    WriteStartingInventory(placementLog);
    WriteEnabledTricks(placementLog);
    WriteEnabledGlitches(placementLog);
    WriteMasterQuestDungeons(placementLog);
    WriteRequiredTrials(placementLog);
    WriteNewGsLocations(placementLog);

    placementtxt = "\n" + placementtxt;

    auto node        = rootNode->InsertNewChildElement("log");
    auto contentNode = node->InsertNewText(placementtxt.c_str());
    contentNode->SetCData(true);

    auto e = placementLog.SaveFile(GetPlacementLogPath().c_str());
    return e == tinyxml2::XML_SUCCESS;
}
