#pragma once
#include <string_view>
#include <vector>

using Description = std::string_view;
using DescriptionVector = std::vector<Description>;

//Setting descriptions are mostly copied from OoT Randomizer tooltips with minor edits

/*------------------------------
|      RANDOMIZE SETTINGS      |                            *SCREEN WIDTH*
------------------------------*/       /*--------------------------------------------------*/
Description openRandomize             = "Randomize all Open Settings except for Logic rules";
Description worldRandomize            = "Randomize all World Settings except for MQ\n"     //
                                        "dungeons";                                        //
Description shuffleRandomize          = "Randomize all Shuffle Settings";                  //
Description dungeonRandomize          = "Randomize all Dungeon Shuffle Settings";          //
                                                                                           //
/*------------------------------                                                           //
|            LOGIC             |                                                           //
------------------------------*/                                                           //
Description logicGlitchless           = "No glitches are required, but may require some\n" //
                                        "minor tricks. Add minor tricks to consider for\n" //
                                        "logic in Logical Tricks.";                        //
Description logicGlitched             = "The glitches you enable at the set difficulty\n"  //
                                        "or below may be required.\n"                      //
                                        "\n"                                               //
                                        "In development, but still usable.";               //
Description logicNoLogic              = "Maximize randomization, All locations are\n"      //
                                        "considered available. MAY BE IMPOSSIBLE TO BEAT.";//
Description logicVanilla              = "For those who want to play the game normally but\n"
                                        "with the improvements of the randomizer. All\n"   //
                                        "locations will contain their vanilla items. This\n"
                                        "supercedes all item shuffle, logic, hint, and\n"  //
                                        "item pool settings. You can still use non-vanilla\n"
                                        "world settings such as adult start or entrance\n" //
                                        "shuffle, but the game may require glitches to\n"  //
                                        "complete if you do.";                             //
/*------------------------------                                                           //
|           FOREST             |                                                           //
------------------------------*/                                                           //
Description forestOpen                = "Mido no longer blocks the path to the Deku Tree,\n"
                                        "and the Kokiri boy no longer blocks the path out\n"
                                        "of the forest.";                                  //
Description forestClosed              = "Beating Deku Tree is logically required to leave\n"
                                        "the forest area (Kokiri Forest/Lost Woods/Sacred\n"
                                        "Forest Meadow/Deku Tree), while the Kokiri Sword\n"
                                        "and a Deku Shield are required to access the Deku\n"
                                        "Tree. Items needed for this will be guaranteed\n" //
                                        "inside the forest area. This setting is\n"        //
                                        "incompatible with starting as adult.";            //
Description forestClosedDeku          = "The Kokiri boy no longer blocks the path out of\n"//
                                        "the forest, but Mido still blocks the path to the\n"
                                        "Deku Tree, requiring Kokiri Sword and Deku Shield\n"
                                        "to access the Deku Tree.";                        //
/*------------------------------                                                           //
|        KAKARIKO GATE         |                                                           //
------------------------------*/                                                           //
Description kakGateOpen               = "The gate is always open instead of needing\n"     //
                                        "Zelda's Letter. The Happy Mask Shop opens upon\n" //
                                        "obtaining Zelda's Letter without needing to show\n"
                                        "it to the guard.";                                //
Description kakGateClosed             = "The gate and the Happy Mask Shop both remain\n"   //
                                        "closed until showing Zelda's Letter to the guard\n"
                                        "in Kakariko.";                                    //
/*------------------------------                                                           //
|        DOOR OF TIME          |                                                           //
------------------------------*/                                                           //
Description doorOfTimeOpen            = "The Door of Time starts opened instead of needing\n"
                                        "to play the Song of Time.";                       //
Description doorOfTimeClosed          = "Only an Ocarina and the Song of Time need to be\n"//
                                        "found to open the Door of Time.";                 //
Description doorOfTimeIntended        = "The Ocarina of Time, the Song of Time, and\n"     //
                                        "all Spiritual Stones need to be found to\n"       //
                                        "open the Door of Time.";                          //
/*------------------------------                                                           //
|       ZORA'S FOUNTAIN        |                                                           //
------------------------------*/                                                           //
Description fountainNormal            = "King Zora obstructs the way to Zora's Fountain.\n"//
                                        "Ruto's Letter must be shown as child in order to\n"
                                        "move him for both eras.";                         //
Description fountainAdult             = "King Zora is always moved in the adult era. This\n"
                                        "means Ruto's Letter is only required to access\n" //
                                        "Zora's Fountain as child.";                       //
Description fountainOpen              = "King Zora starts as moved in both the child and\n"//
                                        "adult eras. This also removes Ruto's Letter from\n"
                                        "the pool since it can't be used.";                //
/*------------------------------                                                           //
|       GERUDO FORTRESS        |                                                           //
------------------------------*/                                                           //
Description gerudoNormal              = "All 4 carpenters can be rescued.";                //
Description gerudoFast                = "Only the bottom left carpenter must be rescued."; //
Description gerudoOpen                = "The carpenters are rescued from the start of the\n"
                                        "game, and if Shuffle Gerudo Card is disabled,\n"  //
                                        "the player starts with the Gerudo Card in the\n"  //
                                        "inventory allowing access to Gerudo Training\n"   //
                                        "Grounds.";                                        //
/*------------------------------                                                           //
|        RAINBOW BRIDGE        |                                                           //
------------------------------*/                                                           //
Description bridgeOpen                = "The Rainbow Bridge is always present.";           //
Description bridgeVanilla             = "The Rainbow Bridge requires Shadow and Spirit\n"  //
                                        "Medallions as well as Light Arrows.";             //
Description bridgeStones              = "The Rainbow Bridge requires collecting a\n"       //
                                        "configurable number of Spiritual Stones.";        //
Description bridgeMedallions          = "The Rainbow Bridge requires collecting a\n"       //
                                        "configurable number of Medallions.";              //
Description bridgeRewards             = "The Rainbow Bridge requires collecting a\n"       //
                                        "configurable number of Dungeon Rewards.";         //
Description bridgeDungeons            = "The Rainbow Bridge requires completing a\n"       //
                                        "configurable number of Dungeons.\n"               //
                                        "\n"                                               //
                                        "Dungeons are considered complete when Link steps\n"
                                        "into the blue warp at the end of them.";          //
Description bridgeTokens              = "The Rainbow Bridge requires collecting a\n"       //
                                        "configurable number of Gold Skulltula Tokens.";   //
/*------------------------------                                                           //
|      BRIDGE CONDITIONS       |                                                           //
------------------------------*/                                                           //
Description bridgeStoneCountDesc      = "Set the number of Spiritual Stones required to\n" //
                                        "spawn the Rainbow Bridge.";                       //
Description bridgeMedallionCountDesc  = "Set the number of Medallions required to spawn the"
                                        "Rainbow Bridge.";                                 //
Description bridgeRewardCountDesc     = "Set the number of Dungeon Rewards (Spiritual\n"   //
                                        "Stones and Medallions) required to spawn the\n"   //
                                        "Rainbow Bridge.";                                 //
Description bridgeDungeonCountDesc    = "Set the number of completed dungeons required to\n"
                                        "spawn the Rainbow Bridge.";                       //
Description bridgeTokenCountDesc      = "Set the number of Gold Skulltula Tokens required\n"
                                        "to spawn the Rainbow Bridge.";                    //
/*------------------------------                                                           //
|     RANDOM GANONS TRIALS     |                                                           //
------------------------------*/                                                           //
Description randomGanonsTrialsDesc    = "Sets a random number of required trials to enter\n"
                                        "Ganon's Tower.";                                  //
/*------------------------------                                                           //
|     GANON'S TRIAL COUNT      |                                                           //
------------------------------*/                                                           //
Description ganonsTrialCountDesc      = "Set the number of trials required to enter\n"     //
                                        "Ganon's Tower. Trials will be randomly selected.";//
/*------------------------------                                                           //
|         STARTING AGE         |                                                           //
------------------------------*/                                                           //
Description ageDesc                   = "Choose which age Link will start as.\n"           //
                                        "\n"                                               //
                                        "Starting as adult means you start with the Master\n"
                                        "Sword in your inventory.\n"                       //
                                        "\n"                                               //
                                        "Only the child option is compatible with Closed\n"//
                                        "Forest.";                                         //
/*------------------------------                                                           //
|      SHUFFLE ENTRANCES       |                                                           //
------------------------------*/                                                           //
Description shuffleEntrancesDesc      = "Shuffle where the entrances between areas lead to."
                                        "If turned on, select which kinds of entrances you\n"
                                        "want shuffled in the options below.";             //
                                                                                           //
/*------------------------------                                                           //
|       DUNGEON ENTRANCES      |                                                           //
------------------------------*/                                                           //
Description dungeonEntrancesDesc      = "Shuffle the pool of dungeon entrances, including\n"
                                        "Bottom of the Well, Ice Cavern, and Gerudo\n"     //
                                        "Training Grounds. However, Ganon's Castle is not\n"
                                        "shuffled.\n"                                      //
                                        "\n"                                               //
                                        "Additionally, the entrances of Deku Tree, Fire\n" //
                                        "Temple and Bottom of the Well are opened for both\n"
                                        "adult and child.";                                //
/*------------------------------                                                           //
|      OVERWORLD ENTRANCES     |                                                           //
------------------------------*/                                                           //
Description overworldEntrancesDesc    = "Shuffle the pool of Overworld entrances, which\n" //
                                        "corresponds to almost all loading zones between\n"//
                                        "Overworld areas.\n"                               //
                                        "\n"                                               //
                                        "Some entrances are unshuffled to avoid issues:\n" //
                                        "- Hyrule Castle Courtyard and Garden entrance\n"  //
                                        "- Both Market Back Alley entrances\n"             //
                                        "- Gerudo Valley to Lake Hylia (unless entrances\n"//
                                        "  are decoupled)";                               //
/*------------------------------                                                           //
|      BOMBCHUS IN LOGIC       |                                                           //
------------------------------*/                                                           //
Description bombchuLogicDesc          = "Bombchus are properly considered in logic.\n"     //
                                        "They can be replenished in shops, or through\n"   //
                                        "bombchu drops, if those are enabled.\n"           //
                                        "\n"                                               //
                                        "Bombchu Bowling is opened by bombchus.";          //
/*------------------------------                                                           //
|          AMMO DROPS          |                                                           //
------------------------------*/                                                           //
Description defaultAmmoDropsDesc      = "Bombs, arrows, seeds, nuts, sticks and\n"         //
                                        "magic jars appear as normal.\n";                  //
Description bombchuDropsDesc          = "Bombs, arrows, seeds, nuts, sticks and\n"         //
                                        "magic jars appear as normal.\n"                   //
                                        "Bombchus can sometimes replace bomb drops.";      //
Description noAmmoDropsDesc           = "All ammo drops will be replaced by blue rupees,\n"//
                                        "except for Deku Sticks.\n"                        //
                                        "Ammo upgrades will only refill ammo by 10 units.";//
/*------------------------------                                                           //
|    HEART DROPS AND REFILLS   |                                                           //
------------------------------*/                                                           //
Description defaultHeartDropsDesc     = "Heart drops will appear as normal.\n"             //
                                        "Health upgrades fully heal Link when picked up.\n"//
                                        "Fairies heal Link as normal.";                    //
Description noHeartDropsDesc          = "Heart drops will be replaced by green rupees.\n"  //
                                        "Health upgrades fully heal Link when picked up.\n"//
                                        "Fairies heal Link as normal.";                    //
Description noHeartRefillDesc         = "Heart drops will appear as normal.\n"             //
                                        "Health upgrades don't heal Link when picked up.\n"//
                                        "Fairies heal Link by only 3 hearts.";             //
Description scarceHeartsDesc          = "Heart drops will be replaced by green rupees.\n"  //
                                        "Health upgrades don't heal Link when picked up.\n"//
                                        "Fairies heal Link by only 3 hearts.";             //
/*------------------------------                                                           //
|       MQ DUNGEON COUNT       |                                                           //
------------------------------*/                                                           //
Description mqDungeonCountDesc        = "Specify the number of Master Quest dungeons to\n" //
                                        "appear in the game. Which dungeons become Master\n"
                                        "Quest will be chosen at random.";                 //
/*------------------------------                                                           //
|        SET MQ DUNGEONS       |                                                           //
------------------------------*/                                                           //
Description setDungeonTypesDesc       = "If set, you can choose specific dungeons to be\n" //
                                        "vanilla, MQ, or random";                          //
/*------------------------------                                                           //
|   SHUFFLE DUNGEON REWARDS    |                                                           //
------------------------------*/                                                           //
Description shuffleRewardsEndOfDungeon= "Medallions and Spiritual Stones will be given as\n"
                                        "rewards for beating dungeons.\n"                  //
                                        "\n"                                               //
                                        "This setting will force Link's Pocket to be a\n"  //
                                        "Medallion or Spiritual Stone.";                   //
Description shuffleRewardsAnyDungeon  = "Medallions and Spiritual Stones can only appear\n"//
                                        "inside of dungeons.";                             //
Description shuffleRewardsOverworld   = "Medallions and Spiritual Stones can only appear\n"//
                                        "outside of dungeons.";                            //
Description shuffleRewardsAnywhere    = "Medallions and Spiritual Stones can appear\n"     //
                                        "anywhere.";                                       //
/*------------------------------                                                           //
|        LINK'S POCKET         |                                                           //
------------------------------*/                                                           //
Description linksPocketDungeonReward  = "Link will start with a Dungeon Reward in his\n"   //
                                        "inventory.";                                      //
Description linksPocketAdvancement    = "Link will receive a random advancement item at the"
                                        "beginning of the playthrough.";                   //
Description linksPocketAnything       = "Link will receive a random item from the item pool"
                                        "at the beginning of the playthrough.";            //
Description linksPocketNothing        = "Link will start with a very useful green rupee."; //
/*------------------------------                                                           //
|         SONG SHUFFLE         |                                                           //
------------------------------*/                                                           //
Description songsSongLocations        = "Songs will only appear at locations that normally\n"
                                        "teach songs.";                                    //
Description songsDungeonRewards       = "Songs appear at the end of dungeons. For major\n" //
                                        "dungeons, they will be at the boss heart container"
                                        "location. The remaining 4 songs are placed at:\n" //
                                        "- Zelda's Lullaby Location\n"                     //
                                        "- Ice Cavern's Serenade of Water Location\n"      //
                                        "- Bottom of the Well's Lens of Truth Location\n"  //
                                        "- Gerudo Training Ground's Ice Arrow Location";   //
Description songsAllLocations         = "Songs can appear in any location.";               //
                                                                                           //
/*------------------------------                                                           //
|         SHOPSANITY           |                                                           //
------------------------------*/                                                           //
Description shopsOff                  = "All shop items will be the same as vanilla.";     //
Description shopsZero                 = "Vanilla shop items will be shuffled among\n"      //
                                        "different shops.";                                //
Description shopsOne                  = "Vanilla shop items will be shuffled among\n"      //
                                        "different shops, and each shop will contain\n"    //
                                        "one non-vanilla shop item.";                      //
Description shopsTwo                  = "Vanilla shop items will be shuffled among\n"      //
                                        "different shops, and each shop will contain\n"    //
                                        "two non-vanilla shop items.";                     //
Description shopsThree                = "Vanilla shop items will be shuffled among\n"      //
                                        "different shops, and each shop will contain\n"    //
                                        "three non-vanilla shop items.";                   //
Description shopsFour                 = "Vanilla shop items will be shuffled among\n"      //
                                        "different shops, and each shop will contain\n"    //
                                        "four non-vanilla shop items.";                    //
Description shopsRandom               = "Vanilla shop items will be shuffled among\n"      //
                                        "different shops, and each shop will contain\n"    //
                                        "1-4 non-vanilla shop items.";                     //
/*------------------------------                                                           //
|         TOKENSANITY          |                                                           //
------------------------------*/                                                           //
Description tokensOff                 = "GS locations will not be shuffled.";              //
Description tokensDungeon             = "This only shuffles the GS locations that are\n"   //
                                        "within dungeons, increasing the value of most\n"  //
                                        "dungeons and making internal dungeon exploration\n"
                                        "more diverse.";                                   //
Description tokensOverworld           = "This only shuffles the GS locations that are\n"   //
                                        "outside of dungeons.";                            //
Description tokensAllTokens           = "Effectively adds 100 new locations for items to\n"//
                                        "appear.";                                         //
                                                                                           //
/*------------------------------                                                           //
|        SCRUB SHUFFLE         |                                                           //
------------------------------*/                                                           //
Description scrubsOff                 = "Only the 3 Scrubs that give one-time items in the\n"
                                        "vanilla game (PoH, Deku Nut capacity, and Deku\n" //
                                        "Stick capacity) will have random items.";         //
Description scrubsAffordable          = "All Scrub prices will be reduced to 10 rupees each";
Description scrubsExpensive           = "All Scrub prices will be their vanilla prices.\n" //
                                        "This will require spending over 1000 rupees on\n" //
                                        "Scrubs.";                                         //
Description scrubsRandomPrices        = "All Scrub prices will be between 0-95 rupees. This"
                                        "will on average be very, very expensive overall.";//
/*------------------------------                                                           //
|         SHUFFLE COWS         |                                                           //
------------------------------*/                                                           //
Description shuffleCowsDesc           = "Enabling this will let cows give you items upon\n"//
                                        "performing Epona's song in front of them. There\n"//
                                        "are 9 cows, and an extra in MQ Jabu.";            //
                                                                                           //
/*------------------------------                                                           //
|     SHUFFLE KOKIRI SWORD     |                                                           //
------------------------------*/                                                           //
Description kokiriSwordDesc           = "Enabling this shuffles the Kokiri Sword into the\n"
                                        "item pool.\n"                                     //
                                        "\n"                                               //
                                        "This will require extensive use of sticks until\n"//
                                        "the sword is found.";                             //
/*------------------------------                                                           //
|       SHUFFLE OCARINAS       |                                                           //
------------------------------*/                                                           //
Description ocarinasDesc              = "Enabling this shuffles the Fairy Ocarina and the\n"
                                        "Ocarina of Time into the item pool.\n"            //
                                        "\n"                                               //
                                        "This will require finding an Ocarina before being\n"
                                        "able to play songs.";                             //
/*------------------------------                                                           //
|      SHUFFLE WEIRD EGG       |                                                           //
------------------------------*/                                                           //
Description weirdEggDesc              = "Enabling this shuffles the Weird Egg from Malon\n"//
                                        "into the item pool.\n"                            //
                                        "This will require finding the Weird Egg to talk to"
                                        "Zelda in Hyrule Castle, which in turn locks\n"    //
                                        "rewards from Impa, Saria, Malon, and Talon, as\n" //
                                        "well as the Happy Mask Sidequest. The Weird Egg is"
                                        "also required for Zelda's Letter to unlock the\n" //
                                        "Kakariko Gate as child which can lock some\n"     //
                                        "progression";                                     //
/*------------------------------                                                           //
|     SHUFFLE GERUDO TOKEN     |                                                           //
------------------------------*/                                                           //
Description gerudoTokenDesc           = "Enabling this shuffles the Gerudo Token into the\n"
                                        "item pool.\n"                                     //
                                        "\n"                                               //
                                        "The Gerudo Token is required to enter the Gerudo\n"
                                        "Training Ground.";                                //
/*------------------------------                                                           //
|      SHUFFLE MAGIC BEANS     |                                                           //
------------------------------*/                                                           //
Description magicBeansDesc            = "Enabling this adds a pack of 10 beans to the item\n"
                                        "pool and changes the Magic Bean Salesman to sell a"
                                        "random item at a price of 60 rupees.";            //
/*------------------------------                                                           //
|       SHUFFLE MERCHANTS      |                                                           //
------------------------------*/                                                           //
Description merchantsDesc             = "Enabling this adds a Giant's Knife and a pack\n"  //
                                        "of Bombchus to the item pool and changes both\n"  //
                                        "Medigoron and the Haunted Wasteland Carpet\n"     //
                                        "Salesman to sell a random item once at the price\n"
                                        "of 200 rupees.";                                  //
Description merchantsHintsDesc        = "These hints will make Medigoron and the Carpet\n" //
                                        "Salesman tell you which item they're selling.\n"  //
                                        "\n"                                               //
                                        "The Clearer Hints setting will affect how they\n" //
                                        "refer to the item.";                              //
/*------------------------------                                                           //
|      MAPS AND COMPASSES      |                                                           //
------------------------------*/                                                           //
Description mapCompassStartWith       = "Maps and Compasses are given to you from the\n"   //
                                        "start. This will add a small amount of money and\n"
                                        "refill items to the pool.";                       //
Description mapCompassVanilla         = "Maps and Compasses will appear in their vanilla\n"//
                                        "locations.";                                      //
Description mapCompassOwnDungeon      = "Maps and Compasses can only appear in their\n"    //
                                        "respective dungeon.";                             //
Description mapCompassAnyDungeon      = "Maps and Compasses can only appear in a dungeon,\n"
                                        "but not necessarily the dungeon they are for.";   //
Description mapCompassOverworld       = "Maps and Compasses can only appear outside of\n"  //
                                        "dungeons.";                                       //
Description mapCompassAnywhere        = "Maps and Compasses can appear anywhere in the\n"  //
                                        "world.";                                          //
/*------------------------------                                                           //
|         SMALL KEYS           |                                                           //
------------------------------*/                                                           //
Description smallKeyStartWith         = "Small Keys are given to you from the start so you\n"
                                        "won't have to worry about locked doors. An easier\n"
                                        "mode.";                                           //
Description smallKeyVanilla           = "Small Keys will appear in their vanilla locations."
                                        "You start with 3 keys in Spirit Temple MQ because\n"
                                        "the vanilla key layout is not beatable in logic.";//
Description smallKeyOwnDungeon        = "Small Keys can only appear in their respective\n" //
                                        "dungeon. If Fire Temple is not a Master Quest\n"  //
                                        "dungeon, the door to the Boss Key chest will be\n"//
                                        "unlocked.";                                       //
Description smallKeyAnyDungeon        = "Small Keys can only appear inside of any dungeon,\n"
                                        "but won't necessarily be in the dungeon that the\n"
                                        "key is for. A difficult mode since it is more\n"  //
                                        "likely to need to enter a dungeon multiple times.";
Description smallKeyOverworld         = "Small Keys can only appear outside of dungeons.\n"//
                                        "You may need to enter a dungeon multiple times to\n"
                                        "gain items to access the overworld locations with\n"
                                        "the keys required to finish a dungeon.";          //
Description smallKeyAnywhere          = "Small Keys can appear anywhere in the world. A\n" //
                                        "difficult mode since it is more likely to need to\n"
                                        "enter a dungeon multiple times.";                 //
/*------------------------------                                                           //
|     GERUDO FORTRESS KEYS     |                                                           //
------------------------------*/                                                           //
Description gerudoKeysVanilla         = "Gerudo Fortress Keys will appear in their vanilla\n"
                                        "location, dropping from fighting Gerudo guards\n" //
                                        "that attack when trying to free the jailed\n"     //
                                        "carpenters.";                                     //
Description gerudoKeysAnyDungeon      = "Gerudo Fortress Keys can only appear inside of\n" //
                                        "dungeons.";                                       //
Description gerudoKeysOverworld       = "Gerudo Fortress Keys can only appear outside of\n"//
                                        "dungeons.";                                       //
Description gerudoKeysAnywhere        = "Gerudo Fortress Keys can appear anywhere in the\n"//
                                        "world.";                                          //
/*------------------------------                                                           //
|          BOSS KEYS           |                                                           //
------------------------------*/                                                           //
Description bossKeyStartWith          = "Boss Keys are given to you from the start so you\n"
                                        "won't have to worry about boss doors. An easier\n"//
                                        "mode.";                                           //
Description bossKeyVanilla            = "Boss Keys will appear in their vanilla locations.";
Description bossKeyOwnDungeon         = "Boss Keys can only appear in their respective\n"  //
                                        "dungeon.";                                        //
Description bossKeyAnyDungeon         = "Boss Keys can only appear inside of any dungeon,\n"
                                        "but won't necessarily be in the dungeon that the\n"
                                        "key is for. A difficult mode since it is more\n"  //
                                        "likely to need to enter a dungeon multiple times.";
Description bossKeyOverworld          = "Boss Keys can only appear outside of dungeons.\n" //
                                        "You may need to enter a dungeon without the boss\n"
                                        "key to get items required to find the key in the\n"
                                        "overworld.";                                      //
Description bossKeyAnywhere           = "Boss Keys can appear anywhere in the world. A\n"  //
                                        "difficult mode since it is more likely to need to\n"
                                        "enter a dungeon multiple times.";                 //
/*------------------------------                                                           //
|   GANON'S CASTLE BOSS KEY    |                                                           //
------------------------------*/                                                           //
Description ganonKeyStartWith         = "Ganon's Castle Boss Key is given to you from the\n"
                                        "start and you don't have to worry about finding it";
Description ganonKeyVanilla           = "Ganon's Castle Boss Key will appear in the vanilla"
                                        "location.";                                       //
Description ganonKeyOwnDungeon        = "Ganon's Castle Boss Key can only appear inside\n" //
                                        "Ganon's Castle.";                                 //
Description ganonKeyAnyDungeon        = "Ganon's Castle Boss Key can only appear inside of\n"
                                        "a dungeon, but not necessarily Ganon's Castle.";  //
Description ganonKeyOverworld         = "Ganon's Castle Boss Key can only appear outside of"
                                        "dungeons.";                                       //
Description ganonKeyAnywhere          = "Ganon's Castle Boss Key can appear anywhere in the"
                                        "world.";                                          //
Description ganonKeyLACS              = "These settings put the boss key on the Light Arrow"
                                        "Cutscene location, from Zelda in Temple of Time as"
                                        "adult, with differing requirements.";             //
/*------------------------------                                                           //
|        LACS CONDITIONS       |                                                           //
------------------------------*/                                                           //
Description lacsMedallionCountDesc    = "Set the number of Medallions required to trigger\n"
                                        "the Light Arrow Cutscene.";                       //
Description lacsStoneCountDesc        = "Set the number of Spiritual Stones required to\n" //
                                        "trigger the Light Arrow Cutscene.";               //
Description lacsRewardCountDesc       = "Set the number of Dungeon Rewards (Spiritual\n"   //
                                        "Stones and Medallions) required to trigger the\n" //
                                        "Light Arrow Cutscene.";                           //
Description lacsDungeonCountDesc      = "Set the number of completed dungeons required to\n"
                                        "trigger the Light Arrow Cutscene.\n"              //
                                        "\n"                                               //
                                        "Dungeons are considered complete when Link steps\n"
                                        "into the blue warp at the end of them.";          //
Description lacsTokenCountDesc        = "Set the number of Gold Skulltula Tokens required\n"
                                        "to trigger the Light Arrow Cutscene.";            //
/*------------------------------                                                           //
|      SKIP CHILD STEALTH      |                                                           //
------------------------------*/                                                           //
Description childStealthDesc          = "The crawlspace into Hyrule Castle goes straight to"
                                        "Zelda, skipping the guards.";                     //
/*------------------------------                                                           //
|      SKIP TOWER ESCAPE       |                                                           //
------------------------------*/                                                           //
Description skipTowerEscapeDesc       = "The tower escape sequence between Ganondorf and\n"//
                                        "Ganon will be skipped.";                          //
/*------------------------------                                                           //
|       SKIP EPONA RACE        |                                                           //
------------------------------*/                                                           //
Description skipEponaRaceDesc         = "Epona can be summoned with Epona's Song without\n"//
                                        "needing to race Ingo.";                           //
/*------------------------------                                                           //
|     SKIP MINIGAME PHASES     |                                                           //
------------------------------*/                                                           //
Description skipMinigamePhasesDesc    = "Completing the second objective in the Dampe Race\n"
                                        "and Gerudo Archery on the first attempt will give\n"
                                        "both rewards at once for that minigame.";          //
/*------------------------------                                                           //
|        FREE SCARECROW        |                                                           //
------------------------------*/                                                           //
Description freeScarecrowDesc         = "Pulling out the Ocarina near a spot at which\n"   //
                                        "Pierre can spawn will do so, without needing\n"   //
                                        "the song.";                                       //
/*------------------------------                                                           //
|      FOUR POES CUTSCENE      |                                                           //
------------------------------*/                                                           //
Description fourPoesDesc              = "The cutscene with the 4 poes in Forest Temple will"
                                        "be skipped. If the cutscene is not skipped, it can"
                                        "be exploited to reach the basement early.";       //
/*------------------------------                                                           //
|     TEMPLE OF TIME INTRO     |                                                           //
------------------------------*/                                                           //
Description templeOfTimeIntroDesc     = "The introduction cutscene to Temple of Time will\n"
                                        "be skipped. This cutscene is helpful for\n"       //
                                        "performing Door of Time Skip should the Door of\n"//
                                        "Time be closed.";                                 //
/*------------------------------                                                           //
|     BIG POE TARGET COUNT     |                                                           //
------------------------------*/                                                           //
Description bigPoeTargetCountDesc     = "The Poe buyer will give a reward for turning in\n"//
                                        "the chosen number of Big Poes.";                  //
/*------------------------------                                                           //
|     NUM REQUIRED CUCCOS      |                                                           //
------------------------------*/                                                           //
Description numRequiredCuccosDesc     = "The cucco lady will give a reward for returning\n"//
                                        "this many of her cuccos to the pen.";             //
/*------------------------------                                                           //
|        KING ZORA SPEED        |                                                          //
-------------------------------*/                                                          //
Description kingZoraSpeedFast         = "King Zora will move out of the way in 1 shuffle"; //
                                                                                           //
Description kingZoraSpeedVanilla      = "King Zora will move out of the way in 26 shuffles";
                                                                                           //
Description kingZoraSpeedRandom       = "King Zora will move out of the way in 1 to 128\n" //
                                        "shuffles, with lower numbers being more common";  //
/*------------------------------                                                           //
|      COMPLETE MASK QUEST     |                                                           //
------------------------------*/                                                           //
Description completeMaskDesc          = "Once the happy mask shop is opened, all masks\n"  //
                                        "will be available to be borrowed.";               //
/*------------------------------                                                           //
|          QUICK TEXT          |                                                           //
------------------------------*/                                                           //
Description quickTextDesc0            = "Quick text will be unchanged, requiring\n"        //
                                        "frame-perfect inputs like in the vanilla game.";  //
Description quickTextDesc1            = "Every text box will be completable by pressing B\n"
                                        "at any point while it's scrolling.";              //
Description quickTextDesc2            = "Every text box will auto-complete instantly.\n"   //
                                        "No scrolling allowed!";                           //
Description quickTextDesc3            = "Holding B will advance and close text boxes\n"    //
                                        "automatically, except for choice selections.";    //
/*------------------------------                                                           //
|       SKIP SONG REPLAYS      |                                                           //
------------------------------*/                                                           //
Description skipSongReplaysDesc       = "The automatic replay after you play a song will\n"//
                                        "be skipped.\n"                                    //
                                        "You can choose to keep the sfx anyway, but you\n" //
                                        "will have control of Link during it.";            //
/*------------------------------                                                           //
|     GOSSIP STONE HINTS       |                                                           //
------------------------------*/                                                           //
Description gossipStonesHintsDesc     = "Gossip Stones can be made to give hints about\n"  //
                                        "where items can be found.\n"                      //
                                        "Different settings can be chosen to decide which\n"
                                        "item is needed to speak to Gossip Stones. Choosing"
                                        "to stick with the Mask of Truth will make the\n"  //
                                        "hints very difficult to obtain.\n"                //
                                        "Hints for 'on the way of the hero' are locations\n"
                                        "that contain items that are required to beat the\n"
                                        "game.";                                           //
                                                                                           //
/*------------------------------                                                           //
|        CLEARER HINTS         |                                                           //
------------------------------*/                                                           //
Description clearerHintsDesc          = "The hints provided by Gossip Stones will be very\n"
                                        "direct if this option is enabled.";               //
/*------------------------------                                                           //
|      HINT DISTRIBUTION       |                                                           //
------------------------------*/                                                           //
Description uselessHintsDesc          = "Only junk hints.";                                //
Description balancedHintsDesc         = "Recommended hint spread.";                        //
Description strongHintsDesc           = "More useful hints.";                              //
Description veryStrongHintsDesc       = "Many powerful hints.";                            //
                                                                                           //
/*------------------------------                                                           //
|       DAMAGE MULTIPLIER      |                                                           //
------------------------------*/                                                           //
Description damageMultiDesc           = "Changes the amount of damage taken.\n"            //
                                        "\n"                                               //
                                        "If set to OHKO, Link will die in one hit.";       //
/*------------------------------                                                           //
|        STARTING TIME         |                                                           //
------------------------------*/                                                           //
Description startingTimeDesc          = "Change up Link's sleep routine.";                 //
                                                                                           //
/*------------------------------                                                           //
|   ALL LOCATIONS REACHABLE    |                                                           //
------------------------------*/                                                           //
Description locationsReachableDesc    = "When this options is enabled, the randomizer will\n"
                                        "guarantee that every item is obtainable and every\n"
                                        "location is reachable. When disabled, only\n"     //
                                        "required items and locations to beat the game\n"  //
                                        "will be guaranteed reachable.";                   //
/*------------------------------                                                           //
|     NIGHT GS EXPECT SUNS     |                                                           //
------------------------------*/                                                           //
Description nightGSDesc               = "GS Tokens that can only be obtained during the\n" //
                                        "night expect you to have Sun's Song to collect\n" //
                                        "them. This prevents needing to wait until night\n"//
                                        "for some locations.";                             //
                                                                                           //
/*------------------------------                                                           //
|       CHEST ANIMATIONS       |                                                           //
------------------------------*/                                                           //
Description chestAnimDesc             = "Choose if you want the slow animation to play\n"  //
                                        "if a chest contains a major item.\n";             //
                                                                                           //
/*------------------------------                                                           //
|     CHEST SIZE AND COLOR     |                                                           //
------------------------------*/                                                           //
Description chestSizeDesc             = "This option will change the appearance of all\n"  //
                                        "regular chests depending on their contents:\n"    //
                                        "Major Items    =    Big Wooden Chests\n"          //
                                        "Lesser Items   =    Small Wooden Chests\n"        //
                                        "Boss Keys      =    Big Fancy Chests\n"           //
                                        "Small Keys     =    Small Fancy Chests";          //
                                                                                           //
/*------------------------------                                                           //
|        INGAME SPOILERS       |                                                           //
------------------------------*/                                                           //
Description ingameSpoilersShowDesc    = "Every spoiler is shown.";                         //
Description ingameSpoilersHideDesc    = "Hides the spheres page and only shows a\n"        //
                                        "location's item after it has been found.";        //
                                                                                           //
/*------------------------------                                                           //
|      MENU OPENING BUTTON     |                                                           //
------------------------------*/                                                           //
Description menuButtonDesc            = "Choose which button will bring up the Dungeon\n"  //
                                        "Information Menu. You can also use the menu to\n" //
                                        "buffer frame perfect inputs if you choose D-Pad"; //
                                                                                           //
/*------------------------------                                                           //
|     START WITH CONSUMABLES   |                                                           //
------------------------------*/                                                           //
Description startWithConsumablesDesc  = "Start the game with maxed out Deku Sticks and Deku"
                                        "Nuts.";                                           //
                                                                                           //
/*------------------------------                                                           //
|     START WITH MAX RUPEES    |                                                           //
------------------------------*/                                                           //
Description startWithMaxRupeesDesc    = "Start the game with a full wallet.\n"             //
                                        "Wallet upgrades will also fill the wallet.";      //
                                                                                           //
/*------------------------------                                                           //
|          ITEM POOL           |                                                           //
------------------------------*/                                                           //
Description itemPoolPlentiful         = "Extra major items are added to the pool.";        //
Description itemPoolBalanced          = "Original item pool.";                             //
Description itemPoolScarce            = "Some excess items are removed, including health\n"//
                                        "upgrades.";                                       //
Description itemPoolMinimal           = "Most excess items are removed.";                  //
                                                                                           //
/*------------------------------                                                           //
|          ICE TRAPS           |                                                           //
------------------------------*/                                                           //
Description iceTrapsOff               = "All Ice Traps are removed.";                      //
Description iceTrapsNormal            = "Only Ice Traps from the base item pool are placed.";
Description iceTrapsExtra             = "Chance to add extra Ice Traps when junk items are\n"
                                        "added to the itempool.";                          //
Description iceTrapsMayhem            = "All added junk items will be Ice Traps.";         //
Description iceTrapsOnslaught         = "All junk items will be replaced by Ice Traps, even"
                                        "those in the base pool.";                         //
/*------------------------------                                                           //
|    REMOVE DOUBLE DEFENSE     |                                                           //
------------------------------*/                                                           //
Description removeDDDesc              = "If set the double defense item will be removed\n" //
                                        "from the item pool for balanced and plentiful.";  //
/*------------------------------                                                           //
|   PROGRESSSIVE GORON SOWRD   |                                                           //
------------------------------*/                                                           //
Description progGoronSword            = "Giant's Knife will always be found\n"             //
                                        "before Biggoron's Sword. Medigoron only starts\n" //
                                        "selling new knives once the Giant's Knife\n"      //
                                        "has been found and broken.";                      //
/*------------------------------                                                           //
|  USE FARORE'S WIND ANYWHERE  |                                                           //
------------------------------*/                                                           //
Description faroresWindAnywhereDesc   = "Farore's Wind can be used outside of dungeons.\n" //
                                        "\n"                                               //
                                        "This setting will not change the logic.";         //
                                                                                           //
/*------------------------------                                                           //
|    ENABLE ADULT DEKU STICK   |                                                           //
------------------------------*/                                                           //
Description adultStickDesc            = "Adult Link can wield a deku stick. In game Adult\n"
                                        "Link will look like he's holding a Hylian Shield,\n"
                                        "but rest assured it is a deku stick.\n"           //
                                        "\n"                                               //
                                        "This setting will not change the logic.";         //
                                                                                           //
/*------------------------------                                                           //
|    ENABLE ADULT BOOMERANG    |                                                           //
------------------------------*/                                                           //
Description adultBoomerangDesc        = "Adult Link can throw the boomerang.\n"            //
                                        "\n"                                               //
                                        "This setting will not change the logic.";         //
                                                                                           //
/*------------------------------                                                           //
|     ENABLE CHILD HAMMER      |                                                           //
------------------------------*/                                                           //
Description childHammerDesc           = "Child Link can swing the Megaton Hammer.\n"       //
                                        "\n"                                               //
                                        "This setting will not change the logic.";         //
                                                                                           //
/*------------------------------                                                           //
|         GK DURABILITY        |                                                           //
------------------------------*/                                                           //
Description gkDurabilityVanilla       = "The durability will always be set to 8.";         //
Description gkDurabilityRandomRisk    = "Each Giant's Knife will get a random durability\n"//
                                        "between 1 and 128, with low being more common,\n" //
                                        "and with an average of 15.";                      //
Description gkDurabilityRandomSafe    = "Each Giant's Knife will get a random durability\n"//
                                        "between 10 and 50, with an average of 30.";       //
                                                                                           //
/*------------------------------                                                           //
|         COLORED KEYS         |                                                           //
------------------------------*/                                                           //
Description coloredKeysDesc           = "If set, small key models will be colored\n"       //
                                        "differently depending on which dungeon they can be"
                                        "used in. Forest Temple keys are green. Fire Temple"
                                        "keys are red. etc.";                              //
Description coloredBossKeysDesc       = "If set, boss key models will be colored\n"        //
                                        "differently depending on which dungeon they can be"
                                        "used in. The Forest Temple boss key is green. The "
                                        "Fire Temple boss key is red. etc.";               //
/*------------------------------                                                           //
|         MIRROR WORLD         |                                                           //
------------------------------*/                                                           //
Description mirrorWorldDesc           = "If set, the world will be mirrored.";             //
                                                                                           //
/*------------------------------                                                           //
|        SHUFFLE MUSIC         |                                                           //
------------------------------*/                                                           //
Description musicRandoDesc            = "Randomize the music in the game";                 //
Description shuffleBGMDesc            = "Randomize area background music";                 //
Description fanfaresOffDesc           = "Fanfares are not shuffled.";                      //
Description onlyFanfaresDesc          = "Fanfares and ocarina songs are shuffled in\n"     //
                                        "separate pools.";                                 //
Description fanfaresOcarinaDesc       = "Fanfares and ocarina songs are shuffled together\n"
                                        "in the same pool.";                               //
Description shuffleOcaMusicDesc       = "The music that plays back after you play an\n"    //
                                        "ocarina song is randomized";                      //
                                                                                           //
/*------------------------------                                                           //
|    RANDOM TRAP DAMAGE TYPE   |                                                           //
------------------------------*/                                                           //
Description randomTrapDmgDesc         = "All traps will be the base game ice trap";        //
                                                                                           //
Description basicTrapDmgDesc          = "All alternative traps will cause a small damage\n"//
                                        "and no other negative effects";                   //
                                                                                           //
Description advancedTrapDmgDesc       = "Some chest traps will burn your Deku Shield or\n" //
                                        "cause a lot of damage (with one-hit protection)"; //
                                                                                           //--------------//
/*------------------------------                                                                           //
|  DETAILED LOGIC EXPLANATIONS |                                                                           //
------------------------------*/
Description ToggleLogicNoneDesc                       = "Disables all the Detailed Logic tricks.";         //
Description ToggleLogicNoviceDesc                     = "Enables only the easier Detailed Logic tricks";   //
Description ToggleLogicIntermediateDesc               = "Enables all but the harder Detailed Logic tricks.";
Description ToggleLogicExpertDesc                     = "Enables all the Detailed Logic tricks.";          //
                                                                                                           //
Description LogicGrottosWithoutAgonyDesc              = "Difficulty: Novice\n"                             //
                                                        "Grottos can be accessed without Shard of Agony,\n"//
                                                        "simply by knowing where they are located.";       //
Description LogicVisibleCollisionDesc                 = "Difficulty: Novice\n"                             //
                                                        "The closed Kakariko Village Gate can be crossed\n"//
                                                        "when coming from Death Mountain Trail.\n"         //
                                                        "Useful for Entrance Randomiser.";                 //
Description LogicFewerTunicRequirementsDesc           = "Difficulty: Novice\n"                             //
                                                        "Allows the following possible without Tunics:\n"  //
                                                        "- Enter Water Temple.\n"                          //
                                                        "- Enter Fire Temple. Only the first floor\n"      //
                                                        "  is accessible, and not Volvagia.\n"             //
                                                        "- Zora's Fountain Bottom Freestanding PoH.\n"     //
                                                        "- Gerudo Training Grounds Underwater Silver Rupee\n"
                                                        "Chest. May need to make multiple trips.";         //
Description LogicLostWoodsGSBeanDesc                  = "Difficulty: Novice\n"                             //
                                                        "You can collect the token with a precise Hookshot\n"
                                                        "use, as long as you can kill the Skulltula first.\n"
                                                        "It can be killed using Longshot, Bow, Bombchus\n" //
                                                        "or Din's Fire.";                                  //
Description LogicLabDivingDesc                        = "Difficulty: Novice\n"                             //
                                                        "Remove the Iron Boots in the midst of Hookshotting"
                                                        "the underwater crate";                            //
Description LogicLabWallGSDesc                        = "Difficulty: Intermediate\n"                       //
                                                        "The jump slash to actually collect the token is\n"//
                                                        "somewhat precise";                                //
Description LogicGraveyardPoHDesc                     = "Difficulty: Novice\n"                             //
                                                        "Using a precise moving setup you can obtain the\n"//
                                                        "Piece of Heart by having the Boomerang interact\n"//
                                                        "with it along the return path.";                  //
Description LogicChildDampeRacePoHDesc                = "Difficulty: Intermediate\n"                       //
                                                        "It is possible to complete the second dampe race\n"
                                                        "as child in under a minute, but it is a strict\n" //
                                                        "time limit.";                                     //
Description LogicGerudoKitchenDesc                    = "Difficulty: Intermediate\n"                       //
                                                        "The logic normally guarantees one of Bow,\n"      //
                                                        "Hookshot, or Hover Boots.";                       //
Description LogicLensWastelandDesc                    = "Difficulty: Expert\n"                             //
                                                        "By memorizing the path, you can travel through the"
                                                        "Wasteland without using the Lens of Truth to see\n"
                                                        "the Poe. The equivalent trick for going in reverse"
                                                        "through the Wasteland is \"Reverse Wasteland\"."; //
Description LogicReverseWastelandDesc                 = "Difficulty: Expert\n"                             //
                                                        "By memorizing the path, you can travel through the"
                                                        "Wasteland in reverse.";                           //
Description LogicColossusGSDesc                       = "Difficulty: Expert\n"                             //
                                                        "Somewhat precise. If you kill enough Leevers you\n"
                                                        "can get enough of a break to take some time to aim"
                                                        "more carefully.";                                 //
Description LogicOutsideGanonsGSDesc                  = "Difficulty: Intermediate\n"                       //
                                                        "Can be killed with a precise sidehop jumpslash\n" //
                                                        "from the top of the broken arch.";                //
Description LogicManOnRoofDesc                        = "Difficulty: Novice\n"                             //
                                                        "Can be reached by side-hopping off the watchtower.";
Description LogicDMTBombableDesc                      = "Difficulty: Expert\n"                             //
                                                        "Child Link can blow up the wall using a nearby\n" //
                                                        "bomb flower. You must backwalk with the flower and"
                                                        "then quickly throw it toward the wall.";          //
Description LogicDMTSoilGSDesc                        = "Difficulty: Intermediate\n"                       //
                                                        "Bugs will go into the soft soil even while the\n" //
                                                        "boulder is still blocking the entrance. Then,\n"  //
                                                        "using a precise moving setup you can kill the Gold"
                                                        "Skulltula and obtain the token by having the\n"   //
                                                        "Boomerang interact with it along the return path.";
Description LogicLinkGoronDinsDesc                    = "Difficulty: Intermediate\n"                       //
                                                        "The timing is quite awkward.";                    //
Description LogicGoronCityLeftMostDesc                = "Difficulty: Novice\n"                             //
                                                        "A precise backwalk starting from on top of the\n" //
                                                        "crate and ending with a precisely-timed backflip\n"
                                                        "can reach this chest without needing either the\n"//
                                                        "Hammer or Silver Gauntlets.";                     //
Description LogicGoronCityPotDesc                     = "Difficulty: Expert\n"                             //
                                                        "A Bombchu can be used to stop the spinning pot,\n"//
                                                        "but it can be quite finicky to get it to work.";  //
Description LogicGoronCityPotWithStrengthDesc         = "Difficulty: Intermediate\n"                       //
                                                        "Allows for stopping the Goron City Spinning Pot\n"//
                                                        "using a bomb flower alone, requiring strength in\n"
                                                        "lieu of inventory explosives.";                   //
Description LogicChildRollingWithStrengthDesc         = "Difficulty: Expert\n"                             //
                                                        "Use the bombflower on the stairs or near\n"       //
                                                        "Medigoron. Timing is tight, especially without\n" //
                                                        "backwalking.";                                    //
Description LogicCraterUpperToLowerDesc               = "Difficulty: Intermediate\n"                       //
                                                        "With the Hammer, you can jump slash the rock twice"
                                                        "in the same jump in order to destroy it before you"
                                                        "fall into the lava.";                             //
Description LogicCraterBeanPoHWithHoversDesc          = "Difficulty: Expert\n"                             //
                                                        "Hover from the base of the bridge near Goron City\n"
                                                        "and walk up the very steep slope.";               //
Description LogicBiggoronBoleroDesc                   = "Difficulty: Intermediate\n"                       //
                                                        "Playing a warp song normally causes a trade item\n"
                                                        "to spoil immediately, however, it is possible use\n"
                                                        "Bolero to reach Biggoron and still deliver the Eye"
                                                        "Drops before they spoil. If you do not wear the\n"
                                                        "Goron Tunic, the heat timer inside the crater will"
                                                        "override the trade item's timer. When you exit to\n"
                                                        "Death Mountain Trail you will have one second to\n"
                                                        "show the Eye Drops before they expire.";          //
Description LogicZoraRiverLowerDesc                   = "Difficulty: Novice\n"                             //
                                                        "Adult can reach this PoH with a precise jump, no\n"
                                                        "Hover Boots required.";                           //
Description LogicZoraRiverUpperDesc                   = "Difficulty: Novice\n"                             //
                                                        "Adult can reach this PoH with a precise jump, no\n"
                                                        "Hover Boots required.";                           //
Description LogicDekuB1WebsWithBowDesc                = "Difficulty: Novice\n"                             //
                                                        "All spider web walls in the Deku Tree basement can"
                                                        "be burnt as adult with just a bow by shooting\n"  //
                                                        "through torches. This trick only applies to the\n"//
                                                        "circular web leading to Gohma; the two vertical\n"//
                                                        "webs are always in logic. Backflip onto the chest\n"
                                                        "near the torch at the bottom of the vine wall.\n" //
                                                        "With precise positioning you can shoot through the"
                                                        "torch to the right edge of the circular web.";    //
Description LogicDekuB1SkipDesc                       = "Difficulty: Intermediate\n"                       //
                                                        "A precise jump can be used to skip needing to use\n"
                                                        "the Slingshot to go around B1 of the Deku Tree. If"
                                                        "used with the \"Closed Forest\" setting, a\n"     //
                                                        "Slingshot will not be guaranteed to exist\n"      //
                                                        "somewhere inside the Forest. This trick applies to"
                                                        "both Vanilla and Master Quest.";                  //
Description LogicDekuBasementGSDesc                   = "Difficulty: Intermediate\n"                       //
                                                        "Can be defeated by doing a precise jump slash.";  //
Description LogicDCStaircaseDesc                      = "Difficulty: Intermediate\n"                       //
                                                        "The Bow can be used to knock down the stairs with\n"
                                                        "two well-timed shots.";                           //
Description LogicDCJumpDesc                           = "Difficulty: Novice\n"                             //
                                                        "Jump is adult only.";                             //
Description LogicDCSlingshotSkipDesc                  = "Difficulty: Expert\n"                             //
                                                        "With precise platforming, child can cross the\n"  //
                                                        "platforms while the flame circles are there. When\n"
                                                        "enabling this trick, it's recommended that you\n" //
                                                        "also enable the Adult variant: \"Dodongo's Cavern\n"
                                                        "Spike Trap Room Jump without Hover Boots\".";     //
Description LogicDCScarecrowGSDesc                    = "Difficulty: Intermediate\n"                       //
                                                        "You can jump off an Armos Statue to reach the\n"  //
                                                        "alcove with the Gold Skulltula. It takes quite a\n"
                                                        "long time to pull the statue the entire way. The\n"
                                                        "jump to the alcove can be a bit picky when done\n"//
                                                        "as child.";                                       //
Description LogicJabuBossGSAdultDesc                  = "Difficulty: Intermediate\n"                       //
                                                        "You can easily get over to the door to the near\n"//
                                                        "boss area early with Hover Boots. The tricky part\n"
                                                        "is getting through the door without being able to\n"
                                                        "use a box to keep the switch pressed. One way is\n"
                                                        "to quickly roll from the switch and open the door\n"
                                                        "before it closes.";                               //
Description LogicJabuScrubJumpDiveDesc                = "Difficulty: Intermediate\n"                       //
                                                        "Standing above the underwater tunnel leading to\n"//
                                                        "the scrub, jump down and swim through the tunnel.\n"
                                                        "This allows adult to access the scrub with no\n"  //
                                                        "Scale or Iron Boots.";                            //
Description LogicForestOutsideBackdoorDesc            = "Difficulty: Intermediate\n"                       //
                                                        "With a precise jump slash from above, you can\n"  //
                                                        "reach the backdoor to the west courtyard without\n"
                                                        "Hover Boots. Applies to both Vanilla and Master\n"//
                                                        "Quest.";                                          //
Description LogicForestDoorFrameDesc                  = "Difficulty: Intermediate\n"                       //
                                                        "A precise Hover Boots movement from the upper\n"  //
                                                        "balconies in this courtyard can be used to get on\n"
                                                        "top of the door frame. Applies to both Vanilla and"
                                                        "Master Quest. In Vanilla, from on top the door\n" //
                                                        "frame you can summon Pierre, allowing you to\n"   //
                                                        "access the falling ceiling room early. In Master\n"
                                                        "Quest, this allows you to obtain the GS on the\n" //
                                                        "door frame as adult without Hookshot or Song of\n"//
                                                        "Time.";                                           //
Description LogicForestOutdoorEastGSDesc              = "Difficulty: Novice\n"                             //
                                                        "Precise Boomerang throws can allow child to kill\n"
                                                        "the Skulltula and collect the token.";            //
Description LogicFireBossDoorJumpDesc                 = "Difficulty: Intermediate\n"                       //
                                                        "The Fire Temple Boss Door can be reached with a\n"//
                                                        "precise jump. You must be touching the side wall\n"
                                                        "of the room so that Link will grab the ledge from\n"
                                                        "farther away than is normally possible.";         //
Description LogicFireStrengthDesc                     = "Difficulty: Expert\n"                             //
                                                        "A precise jump can be used to skip pushing the\n" //
                                                        "block.";                                          //
Description LogicFireScarecrowDesc                    = "Difficulty: Novice\n"                             //
                                                        "Also known as \"Pixelshot\". The Longshot can\n"  //
                                                        "reach the target on the elevator itself, allowing\n"
                                                        "you to skip needing to spawn the scarecrow.";     //
Description LogicFireFlameMazeDesc                    = "Difficulty: Expert\n"                             //
                                                        "If you move quickly you can sneak past the edge of"
                                                        "a flame wall before it can rise up to block you.\n"
                                                        "To do it without taking damage is more precise.\n"//
                                                        "Allows you to progress without needing either a\n"//
                                                        "Small Key or Hover Boots.";                       //
Description LogicFireSongOfTimeDesc                   = "Difficulty: Intermediate\n"                       //
                                                        "A precise jump can be used to reach this room.";  //
Description LogicWaterTempleTorchLongshotDesc         = "Difficulty: Novice\n"                             //
                                                        "Stand on the eastern side of the central pillar\n"//
                                                        "and longshot the torches on the bottom level.\n"  //
                                                        "Swim through the corridor and float up to the top\n"
                                                        "level. This allows access to this area and lower\n"
                                                        "water levels without Iron Boots. The majority of\n"
                                                        "the tricks that allow you to skip Iron Boots in\n"//
                                                        "the Water Temple are not going to be relevant\n"  //
                                                        "unless this trick is first enabled.";             //
Description LogicWaterTempleUpperBoostDesc            = "Difficulty: Expert\n"                             //
                                                        "Stand on the corner closest to the upper ledge\n" //
                                                        "where you play Zelda's Lullaby to raise the water\n"
                                                        "and put a bomb down behind you. Hold forward when\n"
                                                        "the bomb explodes and Link should jump just far\n"//
                                                        "enough to grab the ledge.";                       //
Description LogicWaterCentralBowDesc                  = "Difficulty: Intermediate\n"                       //
                                                        "A very precise Bow shot can hit the eye switch\n" //
                                                        "from the floor above. Then, you can jump down into"
                                                        "the hallway and make through it before the gate\n"//
                                                        "closes. It can also be done as child, using the\n"//
                                                        "Slingshot instead of the Bow.";                   //
Description LogicWaterCentralGSFWDesc                 = "Difficulty: Novice\n"                             //
                                                        "If you set Farore's Wind inside the central pillar"
                                                        "and then return to that warp point after raising\n"
                                                        "the water to the highest level, you can obtain\n" //
                                                        "this Skulltula Token with Hookshot or Boomerang.";//
Description LogicWaterCrackedWallNothingDesc          = "Difficulty: Expert\n"                             //
                                                        "A precise jump slash (among other methods) will\n"//
                                                        "get you to the cracked wall without needing the\n"//
                                                        "Hover Boots or to raise the water to the middle\n"//
                                                        "level. This trick supersedes \"Water Temple\n"    //
                                                        "Cracked Wall with Hover Boots\".";                //
Description LogicWaterCrackedWallHoversDesc           = "Difficulty: Expert\n"                             //
                                                        "With a midair side-hop while wearing the Hover\n" //
                                                        "Boots, you can reach the cracked wall without\n"  //
                                                        "needing to raise the water up to the middle level.";
Description LogicWaterBossKeyRegionDesc               = "Difficulty: Intermediate\n"                       //
                                                        "With precise Hover Boots movement it is possible\n"
                                                        "to reach the boss key chest's region without\n"   //
                                                        "needing the Longshot. It is not necessary to take\n"
                                                        "damage from the spikes. The Gold Skulltula Token\n"
                                                        "in the following room can also be obtained with\n"//
                                                        "just the Hover Boots.";                           //
Description LogicWaterBKJumpDiveDesc                  = "Difficulty: Intermediate\n"                       //
                                                        "Stand on the very edge of the raised corridor\n"  //
                                                        "leading from the push block room to the rolling\n"//
                                                        "boulder corridor. Face the gold skulltula on the\n"
                                                        "waterfall and jump over the boulder corridor floor"
                                                        "into the pool of water, swimming right once\n"    //
                                                        "underwater. This allows access to the boss key\n" //
                                                        "room without Iron boots.";                        //
Description LogicWaterNorthBasementLedgeJumpDesc      = "Difficulty: Novice\n"                             //
                                                        "In the northern basement there's a ledge from\n"  //
                                                        "where, in vanilla Water Temple, boulders roll out\n"
                                                        "into the room. Normally to jump directly to this\n"
                                                        "ledge logically requires the Hover Boots, but with"
                                                        "precise jump, it can be done without them. This\n"//
                                                        "trick applies to both Vanilla and Master Quest."; //
Description LogicWaterDragonAdultDesc                 = "Difficulty: Expert\n"                             //
                                                        "Normally you need both Hookshot and Iron Boots to\n"
                                                        "hit the switch and swim through the tunnel to get\n"
                                                        "to the chest. But by hitting the switch from dry\n"
                                                        "land, using one of Bombchus, Hookshot, or Bow, it\n"
                                                        "is possible to skip one or both of those\n"       //
                                                        "requirements. After the gate has been opened, a\n"//
                                                        "well-timed dive with at least the Silver Scale\n" //
                                                        "could be used to swim through the tunnel.";       //
Description LogicWaterDragonJumpDiveDesc              = "Difficulty: Expert\n"                             //
                                                        "If you come into the dragon statue room from the\n"
                                                        "serpent river, you can jump down from above and\n"//
                                                        "get into the tunnel without needing either Iron\n"//
                                                        "Boots or a Scale. This trick applies to both\n"   //
                                                        "Vanilla and Master Quest. In Vanilla, you must\n" //
                                                        "shoot the switch from above with the Bow, and then"
                                                        "quickly get through the tunnel before the gate\n" //
                                                        "closes.";                                         //
Description LogicWaterRiverGSDesc                     = "Difficulty: Novice\n"                             //
                                                        "Standing on the exposed ground toward the end of\n"
                                                        "the river, a precise Longshot use can obtain the\n"
                                                        "token.";                                          //
Description LogicWaterFallingPlatformGSDesc           = "Difficulty: Intermediate\n"                       //
                                                        "If you stand on the very edge of the platform,\n" //
                                                        "this Gold Skulltula can be obtained with only the\n"
                                                        "Hookshot.";                                       //
Description LogicSpiritLowerAdultSwitchDesc           = "Difficulty: Novice\n"                             //
                                                        "A bomb can be used to hit the switch on the\n"    //
                                                        "ceiling, but it must be thrown from a particular\n"
                                                        "distance away and with precise timing.";          //
Description LogicSpiritChildBombchuDesc               = "Difficulty: Intermediate\n"                       //
                                                        "A carefully-timed Bombchu can hit the switch.";   //
Description LogicSpiritWallDesc                       = "Difficulty: Expert\n"                             //
                                                        "The logic normally guarantees a way of dealing\n" //
                                                        "with both the Beamos and the Walltula before\n"   //
                                                        "climbing the wall.";                              //
Description LogicSpiritLobbyGSDesc                    = "Difficulty: Intermediate\n"                       //
                                                        "Standing on the highest part of the arm of the\n" //
                                                        "statue, a precise Boomerang throw can kill and\n" //
                                                        "obtain this Gold Skulltula. You must throw the\n" //
                                                        "Boomerang slightly off to the side so that it\n"  //
                                                        "curves into the Skulltula, as aiming directly at\n"
                                                        "it will clank off of the wall in front.";         //
Description LogicSpiritMapChestDesc                   = "Difficulty: Intermediate\n"                       //
                                                        "To get a line of sight from the upper torch to the"
                                                        "map chest torches, you must pull an Armos statue\n"
                                                        "all the way up the stairs.";                      //
Description LogicSpiritSunChestDesc                   = "Difficulty: Expert\n"                             //
                                                        "Using the blocks in the room as platforms you can\n"
                                                        "get lines of sight to all three torches. The timer"
                                                        "on the torches is quite short so you must move\n" //
                                                        "quickly in order to light all three.";            //
Description LogicShadowFireArrowEntryDesc             = "Difficulty: Expert\n"                             //
                                                        "It is possible to light all of the torches to open"
                                                        "the Shadow Temple entrance with just Fire Arrows,\n"
                                                        "but you must be very quick, precise, and strategic"
                                                        "with how you take your shots.";                   //
Description LogicShadowUmbrellaDesc                   = "Difficulty: Expert\n"                             //
                                                        "A very precise Hover Boots movement from off of\n"//
                                                        "the lower chest can get you on top of the crushing\n"
                                                        "spikes without needing to pull the block. Applies\n"
                                                        "to both Vanilla and Master Quest.";               //
Description LogicShadowFreestandingKeyDesc            = "Difficulty: Intermediate\n"                       //
                                                        "Release the Bombchu with good timing so that it\n"//
                                                        "explodes near the bottom of the pot.";            //
Description LogicShadowStatueDesc                     = "Difficulty: Novice\n"                             //
                                                        "By sending a Bombchu around the edge of the gorge,"
                                                        "you can knock down the statue without needing a\n"//
                                                        "Bow. Applies in both vanilla and MQ Shadow.";     //
Description LogicChildDeadhandDesc                    = "Difficulty: Novice\n"                             //
                                                        "Requires 9 sticks or 5 jump slashes.";            //
Description LogicGtgWithoutHookshotDesc               = "Difficulty: Expert\n"                             //
                                                        "The final silver rupee on the ceiling can be\n"   //
                                                        "reached by being pulled up into it by the\n"      //
                                                        "Wallmaster.\n"                                    //
                                                        "Then, you must also reach the exit of the room\n" //
                                                        "without the use of the Hookshot. If you move\n"   //
                                                        "quickly, you can sneak past the edge of a\n"      //
                                                        "flame wall before it can rise up to block you.\n" //
                                                        "To do so without taking damage is more precise";  //
Description LogicGtgFakeWallDesc                      = "Difficulty: Novice\n"                             //
                                                        "A precise Hover Boots use from the top of the\n"  //
                                                        "chest can allow you to grab the ledge without\n"  //
                                                        "needing the usual requirements.";                 //
Description LogicLensSpiritDesc                       = "Difficulty: Novice\n"                             //
                                                        "Removes the requirements for the Lens of Truth in\n"
                                                        "Spirit Temple.";                                  //
Description LogicLensShadowDesc                       = "Difficulty: Novice\n"                             //
                                                        "Removes the requirements for the Lens of Truth in\n"
                                                        "Shadow Temple before the invisible moving platform";
Description LogicLensShadowBackDesc                   = "Difficulty: Intermediate\n"                       //
                                                        "Removes the requirements for the Lens of Truth in\n"
                                                        "Shadow Temple beyond the invisible moving platform";
Description LogicLensBotwDesc                         = "Difficulty: Intermediate\n"                       //
                                                        "Removes the requirements for the Lens of Truth in\n"
                                                        "Bottom of the Well.";                             //
Description LogicLensGtgDesc                          = "Difficulty: Novice\n"                             //
                                                        "Removes the requirements for the Lens of Truth in\n"
                                                        "Gerudo Training Grounds.";                        //
Description LogicLensCastleDesc                       = "Difficulty: Intermediate\n"                       //
                                                        "Removes the requirements for the Lens of Truth in\n"
                                                        "Ganon's Castle.";                                 //
Description LogicLensJabuMQDesc                       = "Difficulty: Novice\n"                             //
                                                        "Removes the requirements for the Lens of Truth in\n"
                                                        "Jabu Jabu's Belly MQ.";                           //
Description LogicLensSpiritMQDesc                     = "Difficulty: Novice\n"                             //
                                                        "Removes the requirements for the Lens of Truth in\n"
                                                        "Spirit Temple MQ.";                               //
Description LogicLensShadowMQDesc                     = "Difficulty: Novice\n"                             //
                                                        "Removes the requirements for the Lens of Truth in\n"
                                                        "Shadow Temple MQ before the invisible moving \n"  //
                                                        "platform";                                        //
Description LogicLensShadowMQBackDesc                 = "Difficulty: Intermediate\n"                       //
                                                        "Removes the requirements for the Lens of Truth in\n"
                                                        "Shadow Temple MQ beyond the invisible moving \n"  //
                                                        "platform";                                        //
Description LogicLensBotwMQDesc                       = "Difficulty: Novice\n"                             //
                                                        "Removes the requirements for the Lens of Truth in\n"
                                                        "Bottom of the Well MQ.";                          //
Description LogicLensGtgMQDesc                        = "Difficulty: Novice\n"                             //
                                                        "Removes the requirements for the Lens of Truth in\n"
                                                        "Gerudo Training Grounds MQ.";                     //
Description LogicLensCastleMQDesc                     = "Difficulty: Intermediate\n"                       //
                                                        "Removes the requirements for the Lens of Truth in\n"
                                                        "Ganon's Castle MQ.";                              //
Description LogicSpiritTrialHookshotDesc              = "Difficulty: Intermediate\n"                       //
                                                        "A precise jump off of an Armos can collect the\n" //
                                                        "highest rupee.";                                  //
                                                                                                           //----//
/*------------------------------                                                                                 //
|           GLITCHES           |                                                                                 //
------------------------------*/                                                                                 //
DescriptionVector GlitchISGDesc                { /*Disabled*/ "Shortened to ISG, allows Link's melee weapon to\n"//
                                                              "be in a constant swinging state. Simply touching\n"
                                                              "objects with this causes them to get hit.\n"      //
                                                              "Putting away the weapon while ISG is on hits\n"   //
                                                              "any object with a spherical hitbox,\n"            //
                                                              "such as small skulltulas. It is initiated by\n"   //
                                                              "interrupting a crouch stab.",                     //
                                                   /*Novice*/ "ISG may be required to kill certain enemies,\n"   //
                                                              "or to Bomb Hover when enabled.",                  //
                                             /*Intermediate*/ "",                                                //
                                                 /*Advanced*/ "",                                                //
                                                   /*Expert*/ "",                                                //
                                                     /*Hero*/ "",};                                              //
DescriptionVector GlitchHoverDesc              { /*Disabled*/ "Hovering allows Link to consecutively backflip\n" //
                                                              "in the air without falling. By shielding\n"       //
                                                              "damage with ISG on, Link will stay in midair.\n"  //
                                                              "While bombs aren't always required, this option\n"//
                                                              "will always expect them to be used.\n"            //
                                                              "\n"                                               //
                                                              "Requires ISG to be enabled.",                     //
                                                   /*Novice*/ "Only bombchus are required for hovering.",        //
                                             /*Intermediate*/ "Some hovers may require that you start from flat\n"
                                                              "terrain, which requires somewhat precise timing.",//
                                                 /*Advanced*/ "Usage of regular bombs will now also be expected,\n"
                                                              "which may require consecutive precise timings.",  //
                                                   /*Expert*/ "",                                                //
                                                     /*Hero*/ "",};                                              //
DescriptionVector GlitchMegaflipDesc           { /*Disabled*/ "A Megaflip is a backflip/sidehop with high speed.\n"
                                                              "This can be done with several methods.",          //
                                                   /*Novice*/ "Only Megaflipping with bombs is required.",       //
                                             /*Intermediate*/ "Some Megaflips where you don't have a lot of room\n"
                                                              "to work with and positioning is more important\n" //
                                                              "may be required.",                                //
                                                 /*Advanced*/ "",                                                //
                                                   /*Expert*/ "",                                                //
                                                     /*Hero*/ "",};                                              //
DescriptionVector GlitchHookshotClipDesc       { /*Disabled*/ "Hookshot Clipping allows Link to hookshot through\n"
                                                              "certain walls, which is useful if a valid\n"      //
                                                              "target is on the other side.",                    //
                                                   /*Novice*/ "Basic Hookshot Clipping may be required.",        //
                                             /*Intermediate*/ "",                                                //
                                                 /*Advanced*/ "",                                                //
                                                   /*Expert*/ "",                                                //
                                                     /*Hero*/ "",};                                              //
DescriptionVector GlitchHookshotJump_BonkDesc  { /*Disabled*/ "A Hookshot Jump is an umbrella term for techniques"
                                                              "that launch Link into the sky using the Hookshot\n"
                                                              "in various ways, sometimes together with\n"       //
                                                              "other items. The bonk method only requires the\n" //
                                                              "Hookshot itself.",                                //
                                                   /*Novice*/ "",                                                //
                                             /*Intermediate*/ "Basic Hookshot-Bonk Jumping may be required.",    //
                                                 /*Advanced*/ "",                                                //
                                                   /*Expert*/ "",                                                //
                                                     /*Hero*/ "",};                                              //
DescriptionVector GlitchHookshotJump_BootsDesc { /*Disabled*/ "This Hookshot Jump technique is one of the easier\n"
                                                              "ones, and require any pair of boots.",            //
                                                   /*Novice*/ "Only relatively short Hookshot-Boot Jumps where\n"//
                                                              "you snap upwards may be required.",               //
                                             /*Intermediate*/ "Higher Hookshot-Boot Jumps where you look further\n"
                                                              "up or snap downwards instead may be required.",   //
                                                 /*Advanced*/ "",                                                //
                                                   /*Expert*/ "",                                                //
                                                     /*Hero*/ "",};                                              //
DescriptionVector GlitchLedgeClipDesc          { /*Disabled*/ "A Ledge Clip allows Link to fall through a floor\n"
                                                              "or pass through an object by facing a wall\n"     //
                                                              "and dropping down to the left in a various ways.\n"
                                                              "These only work as an adult.",                    //
                                                   /*Novice*/ "Basic Ledge Clips may be required.\n"             //
                                                              "Some require that you let go of the ledge with\n" //
                                                              "a specific timing.",                              //
                                             /*Intermediate*/ "Certain harder clips may also be required.",      //
                                                 /*Advanced*/ "",                                                //
                                                   /*Expert*/ "",                                                //
                                                     /*Hero*/ "",};                                              //
DescriptionVector GlitchTripleSlashClipDesc    { /*Disabled*/ "When doing a three-slash-combo with either the\n" //
                                                              "Kokiri Sword or the Master Sword and put it away,\n"
                                                              "Link will be placed back a small distance.\n"     //
                                                              "If, while slashing, you use the recoil of hitting\n"
                                                              "a wall and then put away the sword, Link may clip\n"
                                                              "into a wall behind him if angled correctly.",     //
                                                   /*Novice*/ "Basic Triple Slash Clipping may be required.",    //
                                             /*Intermediate*/ "",                                                //
                                                 /*Advanced*/ "",                                                //
                                                   /*Expert*/ "",                                                //
                                                     /*Hero*/ "",};                                              //
