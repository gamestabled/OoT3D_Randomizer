#include "shuffle_settings.hpp"

ShuffleSettings::ShuffleSettings() :
        randomizeShuffle(std::move(Setting::Bool("Randomize Settings", "Randomize all Shuffle settings", {
            Setting::Option("No", ""),
            Setting::Option("Yes", ""),
        }))),
        shuffleRewards(std::move(Setting::Int("Shuffle Dungeon Rewards", "", {
            Setting::Option("End of Dungeons", "Medallions and Spiritual Stones will be given as rewards for beating dungeons.\n\n"
                                        "This setting will force Link's Pocket to be a Medallion or Spiritual Stone"),
            Setting::Option("Any Dungeon", "Medallions and Spiritual Stones can only appear inside of dungeons"),
            Setting::Option("Overworld", "Medallions and Spiritual Stones can only appear outside of dungeons"),
            Setting::Option("Anywhere", "Medallions and Spiritual Stones can appear anywhere"),
        }))),
        linksPocketItem(std::move(Setting::Int("Link's Pocket", "", {
            Setting::Option("Dungeon Reward", "Link will start with a Dungeon Reward in his inventory"),
            Setting::Option("Advancement", "Link will receive a random advancement item at the beginning of the playthrough"),
            Setting::Option("Anything", "Link will receive a random item from the item pool at the beginning of the playthrough"),
            Setting::Option("Nothing", "Link will start with a very useful green rupee"),
        }))),
        shuffleSongs(std::move(Setting::Int("Shuffle Songs", "", {
            Setting::Option("Song Locations", "Songs will only appear at locations that normally teach songs"),
            Setting::Option("Dungeon Rewards", "Songs appear at the end of dungeons. For major dungeons, they will be at the boss heart container"
                                        " location. The remaining 4 songs are placed at:\n"
                                        "- Zelda's Lullaby Location\n"
                                        "- Ice Cavern's Serenade of Water Location\n"
                                        "- Bottom of the Well's Lens of Truth Location\n"
                                        "- Gerudo Training Ground's Ice Arrow Location"),
            Setting::Option("Anywhere", "Songs can appear in any location"),
        }))),
        shuffleShops(std::move(Setting::Int("Shuffle Shops", "", {
            Setting::Option("Off", "All shop items will be the same as vanilla"),
            Setting::Option("0", "Vanilla shop items will be shuffled among different shops"),
            Setting::Option("1", "Vanilla shop items will be shuffled among different shops, and each shop will contain one non-vanilla shop item"),
            Setting::Option("2", "Vanilla shop items will be shuffled among different shops, and each shop will contain two non-vanilla shop items"),
            Setting::Option("3", "Vanilla shop items will be shuffled among different shops, and each shop will contain three non-vanilla shop items"),
            Setting::Option("4", "Vanilla shop items will be shuffled among different shops, and each shop will contain four non-vanilla shop items"),
            Setting::Option("Random", "Vanilla shop items will be shuffled among different shops, and each shop will contain 1-4 non-vanilla shop items"),
        }))),
        shuffleTokens(std::move(Setting::Int("Shuffle Tokens", "", {
            Setting::Option("Off", "GS locations will not be shuffled"),
            Setting::Option("Dungeons", "This only shuffles the GS locations that are within dungeons, increasing the value of most dungeons"
                                        " and making internal dungeon exploration more diverse"),
            Setting::Option("Overworld", "This only shuffles the GS locations that are outside of dungeons"),
            Setting::Option("All Tokens", "Effectively adds 100 new locations for items to appear"),
        }))),
        shuffleScrubs(std::move(Setting::Int("Shuffle Scrubs", "", {
            Setting::Option("Off", "Only the 3 Scrubs that give one-time items in the vanilla game (PoH, Deku Nut capacity, and Deku"
                                        " Stick capacity) will have random items."),
            Setting::Option("Affordable", "All Scrub prices will be reduced to 10 rupees each"),
            Setting::Option("Expensive", "All Scrub prices will be their vanilla prices. This will require spending over 1000 rupees on Scrubs"),
            Setting::Option("Random Prices", "All Scrub prices will be between 0-95 rupees. This will on average be very, very expensive overall"),
        }))),
        shuffleCows(std::move(Setting::Bool("Shuffle Cows", "Enabling this will let cows give you items upon performing Epona's song in front of them. There"
                                        " are 9 cows, and an extra in MQ Jabu", {
            Setting::Option("Off", ""),
            Setting::Option("On", ""),
        }))),
        shuffleKokiriSword(std::move(Setting::Bool("Shuffle Kokiri Sword", "Enabling this shuffles the Kokiri Sword into the item pool.\n\n"
                                        "This will require extensive use of sticks until the sword is found", {
            Setting::Option("Off", ""),
            Setting::Option("On", ""),
        }))),
        shuffleOcarinas(std::move(Setting::Bool("Shuffle Ocarinas", "Enabling this shuffles the Fairy Ocarina and the Ocarina of Time into the item pool.\n\n"
                                        "This will require finding an Ocarina before being able to play songs", {
            Setting::Option("Off", ""),
            Setting::Option("On", ""),
        }))),
        shuffleWeirdEgg(std::move(Setting::Bool("Shuffle Weird Egg", "Enabling this shuffles the Weird Egg from Malon into the item pool.\n"
                                        "This will require finding the Weird Egg to talk to Zelda in Hyrule Castle, which in turn locks rewards from Impa,"
                                        " Saria, Malon, and Talon, as well as the Happy Mask Sidequest. The Weird Egg is also required for Zelda's Letter"
                                        " to unlock the Kakariko Gate as child which can lock some progression", {
            Setting::Option("Off", ""),
            Setting::Option("On", ""),
        }))),
        shuffleGerudoToken(std::move(Setting::Bool("Shuffle Gerudo Token", "Enabling this shuffles the Gerudo Token into the item pool.\n\n"
                                        "The Gerudo Token is required to enter the Gerudo Training Ground", {
            Setting::Option("Off", ""),
            Setting::Option("On", ""),
        }))),
        shuffleMagicBeans(std::move(Setting::Bool("Shuffle Magic Beans", "Enabling this adds a Giant's Knife and a pack of Bombchus to the item pool and"
                                        " changes both Medigoron and the Haunted Wasteland Carpet Salesman to sell a random item once at the price of 200 rupees", {
            Setting::Option("Off", ""),
            Setting::Option("On (No Hints)", ""),
            Setting::Option("On (With Hints)", "These hints will make Medigoron and the Carpet Salesman tell you which item they're selling.\n\n"
                                        "The Clearer Hints setting will affect how they refer to the item"),
        }))),
        shuffleMerchants(std::move(Setting::Int("Shuffle Merchants", "Enabling this adds a pack of 10 beans to the item pool and changes the Magic Bean"
                                        " Salesman to sell a random item at a price of 60 rupees", {
            Setting::Option("Off", ""),
            Setting::Option("On", ""),
        }))),
        shuffleAdultTradeQuest(std::move(Setting::Bool("Shuffle Adult Trade", "Enabling this adds all of the adult trade quest items to the pool, each of which"
                                        " can be traded for a unique reward. You will be able to choose which of your owned adult trade items is visible"
                                        " in the inventory by selecting the item and using the L and R buttons. If disabled, only the Claim Check will be found in the pool", {
            Setting::Option("Off", ""),
            Setting::Option("On", ""),
        }))) {
    push_back(&randomizeShuffle);
    push_back(&shuffleRewards);
    push_back(&linksPocketItem);
    push_back(&shuffleSongs);
    push_back(&shuffleShops);
    push_back(&shuffleTokens);
    push_back(&shuffleScrubs);
    push_back(&shuffleCows);
    push_back(&shuffleKokiriSword);
    push_back(&shuffleOcarinas);
    push_back(&shuffleWeirdEgg);
    push_back(&shuffleGerudoToken);
    push_back(&shuffleMagicBeans);
    push_back(&shuffleMerchants);
    push_back(&shuffleAdultTradeQuest);
}

void ShuffleSettings::update() {
    if (shuffleRewards.is(RewardSetting::EndOfDungeon)) {
        // TODO
        // LinksPocketItem.lock();
        // LinksPocketItem.setSelectedIndex(DungeonReward);
        if (randomizeShuffle) {
            //TODO
            // LinksPocketItem.unlock();
            // LinksPocketItem.hide();
        }
    } else {
        // TODO
        // LinksPocketItem.unlock();
    }
}
