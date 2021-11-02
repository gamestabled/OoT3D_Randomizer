#include "open_settings.hpp"

OpenSettings::OpenSettings() :
        randomizeSettings(std::move(Setting::Bool("Randomize Settings", "Randomize all Open settings except for Logic rules", {
            Setting::Option("No", "" ),
            Setting::Option("Yes", "" ),
        }))),
        forest(std::move(Setting::Int("Forest", "", {
            Setting::Option("Closed", "Beating Deku Tree is logically required to leave"
                                        "the forest area (Kokiri Forest/Lost Woods/Sacred"
                                        "Forest Meadow/Deku Tree), while the Kokiri Sword"
                                        "and a Deku Shield are required to access the Deku"
                                        "Tree. Items needed for this will be guaranteed"
                                        "inside the forest area. This setting is"
                                        "incompatible with starting as adult."),
            Setting::Option("Open", "Mido no longer blocks the path to the Deku Tree,"
                                        "and the Kokiri boy no longer blocks the path out"
                                        "of the forest."),
            Setting::Option("Closed Deku", "The Kokiri boy no longer blocks the path out of"
                                        "the forest, but Mido still blocks the path to the"
                                        "Deku Tree, requiring Kokiri Sword and Deku Shield"
                                        "to access the Deku Tree."),
        }, Setting::Category::NonCosmetic, (size_t)OpenForest::Open))),
        kakarikoGate(std::move(Setting::Int("Kakariko Gate", "", {
            Setting::Option("Closed", "The gate and the Happy Mask Shop both remain"
                                        "closed until showing Zelda's Letter to the guard"
                                        "in Kakariko."),
            Setting::Option("Open", "The gate is always open instead of needing"
                                        "Zelda's Letter. The Happy Mask Shop opens upon"
                                        "obtaining Zelda's Letter without needing to show"
                                        "it to the guard."),
        }))),
        doorOfTime(std::move(Setting::Int("Door of Time", "", {
            Setting::Option("Open", "The Door of Time starts opened instead of needing"
                                        "to play the Song of Time."),
            Setting::Option("Closed", "Only an Ocarina and the Song of Time need to be"
                                        "found to open the Door of Time."),
            Setting::Option("Closed Deku", "The Ocarina of Time, the Song of Time, and"
                                        "all Spiritual Stones need to be found to"
                                        "open the Door of Time."),
        }))),
        zorasFountain(std::move(Setting::Int("Zora's Fountain", "", {
            Setting::Option("Normal", "King Zora obstructs the way to Zora's Fountain."
                                        "Ruto's Letter must be shown as child in order to"
                                        "move him for both eras."),
            Setting::Option("Adult", "King Zora is always moved in the adult era. This"
                                        "means Ruto's Letter is only required to access"
                                        "Zora's Fountain as child."),
            Setting::Option("Open", "King Zora starts as moved in both the child and"
                                        "adult eras. This also removes Ruto's Letter from"
                                        "the pool since it can't be used."),
        }))),
        gerudoFortress(std::move(Setting::Int("Gerudo Fortress", "", {
            Setting::Option("Normal", "All 4 carpenters can be rescued."),
            Setting::Option("Fast", "Only the bottom left carpenter must be rescued."),
            Setting::Option("Open", "The carpenters are rescued from the start of the"
                                        "game, and if Shuffle Gerudo Card is disabled,"
                                        "the player starts with the Gerudo Card in the"
                                        "inventory allowing access to Gerudo Training"
                                        "Grounds."),
        }))),
        rainbowBridge(std::move(Setting::Int("Rainbow Bridge", "", {
            Setting::Option("Open", "The Rainbow Bridge is always present."),
            Setting::Option("Vanilla", "The Rainbow Bridge requires Shadow and Spirit"
                                        "Medallions as well as Light Arrows."),
            Setting::Option("Stones", "The Rainbow Bridge requires collecting a"
                                        "configurable number of Spiritual Stones."),
            Setting::Option("Medallions", "The Rainbow Bridge requires collecting a"
                                        "configurable number of Medallions."),
            Setting::Option("Rewards", "The Rainbow Bridge requires collecting a"
                                        "configurable number of Dungeon Rewards."),
            Setting::Option("Dungeons", "The Rainbow Bridge requires completing a"
                                        "configurable number of Dungeons."
                                        "\n\n"
                                        "Dungeons are considered complete when Link steps"
                                        "into the blue warp at the end of them."),
            Setting::Option("Tokens", "The Rainbow Bridge requires collecting a"
                                        "configurable number of Gold Skulltula Tokens."),
        }, Setting::Category::NonCosmetic, (size_t)RainbowBridge::Vanilla))),
        stoneCount(std::move(Setting::Range("  Stone Count", "Set the number of Spiritual Stones required to spawn the Rainbow Bridge", 0, 4,
            Setting::Category::NonCosmetic, 1, true))),
        medallionCount(std::move(Setting::Range("  Medallion Count", "Set the number of Medallions required to spawn the Rainbow Bridge", 0, 7,
            Setting::Category::NonCosmetic, 1, true))),
        rewardCount(std::move(Setting::Range("  Reward Count", "Set the number of Dungeon Rewards (Spiritual Stones and Medallions) required to spawn the Rainbow Bridge", 0, 10,
            Setting::Category::NonCosmetic, 1, true))),
        dungeonCount(std::move(Setting::Range("  Dungeon Count", "Set the number of completed dungeons required to spawn the Rainbow Bridge", 0, 9,
            Setting::Category::NonCosmetic, 1, true))),
        tokenCount(std::move(Setting::Range("  Token Count", "Set the number of Gold Skulltula Tokens required to spawn the Rainbow Bridge", 0, 101,
            Setting::Category::NonCosmetic, 1, true))),
        randomGanonsTrials(std::move(Setting::Bool("Random Ganon's Trials", "Sets a random number of required trials to enter Ganon's Tower", {
                Setting::Option("Off", ""),
                Setting::Option("On", ""),
        }, Setting::Category::NonCosmetic, Setting::On))),
        trialCount(std::move(Setting::Range("  Trial Count", "Set the number of trials required to enter Ganon's Tower. Trials will be randomly selected.", 0, 7,
            Setting::Category::NonCosmetic, 1, true))) {
    push_back(&randomizeSettings);
    push_back(&forest);
    push_back(&kakarikoGate);
    push_back(&doorOfTime);
    push_back(&zorasFountain);
    push_back(&gerudoFortress);
    push_back(&rainbowBridge);
    push_back(&stoneCount);
    push_back(&medallionCount);
    push_back(&rewardCount);
    push_back(&dungeonCount);
    push_back(&tokenCount);
    push_back(&randomGanonsTrials);
    push_back(&trialCount);
}

void OpenSettings::update() {
    if (rainbowBridge.is(RainbowBridge::Stones)) {
        stoneCount.unhide();
    } else {
        stoneCount.setSelectedIndex(3);
        stoneCount.hide();
    }
    
    if (rainbowBridge.is(RainbowBridge::Medallions)) {
        medallionCount.unhide();
    } else {
        medallionCount.setSelectedIndex(6);
        medallionCount.hide();
    }

    if (rainbowBridge.is(RainbowBridge::Rewards)) {
        rewardCount.unhide();
    } else {
        rewardCount.setSelectedIndex(9);
        rewardCount.hide();
    }

    if (rainbowBridge.is(RainbowBridge::Dungeons)) {
        dungeonCount.unhide();
    } else {
        dungeonCount.setSelectedIndex(8);
        dungeonCount.hide();
    }

    if (rainbowBridge.is(RainbowBridge::Tokens)) {
        tokenCount.unhide();
    } else {
        tokenCount.setSelectedIndex(8);
        tokenCount.hide();
    }

    if (randomGanonsTrials) {
        trialCount.setSelectedIndex(6);
        trialCount.hide();
    } else {
        trialCount.unhide();
    }
}
