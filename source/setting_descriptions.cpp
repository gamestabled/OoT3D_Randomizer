#include "setting_descriptions.hpp"

//Setting descriptions are mostly copied from OoT Randomizer tooltips with minor edits

/*------------------------------
|      RANDOMIZE SETTINGS      |                            *SCREEN WIDTH*
------------------------------*/       /*--------------------------------------------------*/
string_view openRandomize             = "Randomize all Open Settings except for Logic rules";
string_view worldRandomize            = "Randomize all World Settings except for MQ\n"     //
                                        "dungeons";                                        //
string_view shuffleRandomize          = "Randomize all Shuffle Settings";                  //
string_view dungeonRandomize          = "Randomize all Dungeon Shuffle Settings";          //
                                                                                           //
/*------------------------------                                                           //
|            LOGIC             |                                                           //
------------------------------*/                                                           //
string_view logicGlitchless           = "No glitches are required, but may require some\n" //
                                        "minor tricks. Add minor tricks to consider for\n" //
                                        "logic in Detailed Logic Settings.";               //
string_view logicNoLogic              = "Maximize randomization, All locations are\n"      //
                                        "considered available. MAY BE IMPOSSIBLE TO BEAT.";//
/*------------------------------                                                           //
|           FOREST             |                                                           //
------------------------------*/                                                           //
string_view forestOpen                = "Mido no longer blocks the path to the Deku Tree,\n"
                                        "and the Kokiri boy no longer blocks the path out\n"
                                        "of the forest.";                                  //
string_view forestClosed              = "Beating Deku Tree is logically required to leave\n"
                                        "the forest area (Kokiri Forest/Lost Woods/Sacred\n"
                                        "Forest Meadow/Deku Tree), while the Kokiri Sword\n"
                                        "and a Deku Shield are required to access the Deku\n"
                                        "Tree. Items needed for this will be guaranteed\n" //
                                        "inside the forest area. This setting is\n"        //
                                        "incompatible with starting as adult.";            //
string_view forestClosedDeku          = "The Kokiri boy no longer blocks the path out of\n"//
                                        "the forest, but Mido still blocks the path to the\n"
                                        "Deku Tree, requiring Kokiri Sword and Deku Shield\n"
                                        "to access the Deku Tree.";                        //
/*------------------------------                                                           //
|        KAKARIKO GATE         |                                                           //
------------------------------*/                                                           //
string_view kakGateOpen               = "The gate is always open instead of needing\n"     //
                                        "Zelda's Letter. The Happy Mask Shop opens upon\n" //
                                        "obtaining Zelda's Letter without needing to show\n"
                                        "it to the guard.";                                //
string_view kakGateClosed             = "The gate and the Happy Mask Shop both remain\n"   //
                                        "closed until showing Zelda's Letter to the guard\n"
                                        "in Kakariko.";                                    //
/*------------------------------                                                           //
|        DOOR OF TIME          |                                                           //
------------------------------*/                                                           //
string_view doorOfTimeDesc            = "The Door of Time starts opened instead of needing\n"
                                        "to play the Song of Time. If closed, only an\n"   //
                                        "Ocarina and the Song of Time need to be found to\n"
                                        "open the Door of Time.";                          //
/*------------------------------                                                           //
|       ZORA'S FOUNTAIN        |                                                           //
------------------------------*/                                                           //
string_view fountainNormal            = "King Zora obstructs the way to Zora's Fountain.\n"//
                                        "Ruto's Letter must be shown as child in order to\n"
                                        "move him for both eras.";                         //
string_view fountainAdult             = "King Zora is always moved in the adult era. This\n"
                                        "means Ruto's Letter is only required to access\n" //
                                        "Zora's Fountain as child.";                       //
string_view fountainOpen              = "King Zora starts as moved in both the child and\n"//
                                        "adult eras. This also removes Ruto's Letter from\n"
                                        "the pool since it can't be used.";                //
/*------------------------------                                                           //
|       GERUDO FORTRESS        |                                                           //
------------------------------*/                                                           //
string_view gerudoNormal              = "All 4 carpenters can be rescued.";                //
string_view gerudoFast                = "Only the bottom left carpenter must be rescued."; //
string_view gerudoOpen                = "The carpenters are rescued from the start of the\n"
                                        "game, and if Shuffle Gerudo Card is disabled,\n"  //
                                        "the player starts with the Gerudo Card in the\n"  //
                                        "inventory allowing access to Gerudo Training\n"   //
                                        "Grounds.";                                        //
/*------------------------------                                                           //
|        RAINBOW BRIDGE        |                                                           //
------------------------------*/                                                           //
string_view bridgeOpen                = "The Rainbow Bridge is always present.";           //
string_view bridgeVanilla             = "The Rainbow Bridge requires Shadow and Spirit\n"  //
                                        "Medallions as well as Light Arrows.";             //
string_view bridgeStones              = "The Rainbow Bridge requires collecting a\n"       //
                                        "configurable number of Spiritual Stones.";        //
string_view bridgeMedallions          = "The Rainbow Bridge requires collecting a\n"       //
                                        "configurable number of Medallions.";              //
string_view bridgeRewards             = "The Rainbow Bridge requires collecting a\n"       //
                                        "configurable number of Dungeon Rewards.";         //
string_view bridgeDungeons            = "The Rainbow Bridge requires completing a\n"       //
                                        "configurable number of Dungeons.\n"               //
                                        "\n"                                               //
                                        "Dungeons are considered complete when Link steps\n"
                                        "into the blue warp at the end of them.";          //
string_view bridgeTokens              = "The Rainbow Bridge requires collecting a\n"       //
                                        "configurable number of Gold Skulltula Tokens.";   //
/*------------------------------                                                           //
|      BRIDGE CONDITIONS       |                                                           //
------------------------------*/                                                           //
string_view bridgeStoneCountDesc      = "Set the number of Spiritual Stones required to\n" //
                                        "spawn the Rainbow Bridge.";                       //
string_view bridgeMedallionCountDesc  = "Set the number of Medallions required to spawn the"
                                        "Rainbow Bridge.";                                 //
string_view bridgeRewardCountDesc     = "Set the number of Dungeon Rewards (Spiritual\n"   //
                                        "Stones and Medallions) required to spawn the\n"   //
                                        "Rainbow Bridge.";                                 //
string_view bridgeDungeonCountDesc    = "Set the number of completed dungeons required to\n"
                                        "spawn the Rainbow Bridge.";                       //
string_view bridgeTokenCountDesc      = "Set the number of Gold Skulltula Tokens required\n"
                                        "to spawn the Rainbow Bridge.";                    //
/*------------------------------                                                           //
|     RANDOM GANONS TRIALS     |                                                           //
------------------------------*/                                                           //
string_view randomGanonsTrialsDesc    = "Sets a random number of required trials to enter\n"
                                        "Ganon's Tower.";                                  //
/*------------------------------                                                           //
|     GANON'S TRIAL COUNT      |                                                           //
------------------------------*/                                                           //
string_view ganonsTrialCountDesc      = "Set the number of trials required to enter\n"     //
                                        "Ganon's Tower. Trials will be randomly selected.";//
/*------------------------------                                                           //
|         STARTING AGE         |                                                           //
------------------------------*/                                                           //
string_view ageDesc                   = "Choose which age Link will start as.\n"           //
                                        "\n"                                               //
                                        "Starting as adult means you start with the Master\n"
                                        "Sword in your inventory.\n"                       //
                                        "\n"                                               //
                                        "Only the child option is compatible with Closed\n"//
                                        "Forest.";                                         //
/*------------------------------                                                           //
|      SHUFFLE ENTRANCES       |                                                           //
------------------------------*/                                                           //
string_view shuffleEntrancesDesc      = "Shuffle where the entrances between areas lead to."
                                        "If turned on, select which kinds of entrances you\n"
                                        "want shuffled in the options below.";             //
                                                                                           //
/*------------------------------                                                           //
|       DUNGEON ENTRANCES      |                                                           //
------------------------------*/                                                           //
string_view dungeonEntrancesDesc      = "Shuffle the pool of dungeon entrances, including\n"
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
string_view overworldEntrancesDesc    = "Shuffle the pool of Overworld entrances, which\n" //
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
string_view bombchuLogicDesc          = "Bombchus are properly considered in logic.\n"     //
                                        "They can be replenished in shops, or through\n"   //
                                        "bombchu drops, if those are enabled.\n"           //
                                        "\n"                                               //
                                        "Bombchu Bowling is opened by bombchus.";          //
/*------------------------------                                                           //
|          AMMO DROPS          |                                                           //
------------------------------*/                                                           //
string_view defaultAmmoDropsDesc      = "Bombs, arrows, seeds, nuts, sticks and\n"         //
                                        "magic jars appear as normal.\n";                  //
string_view bombchuDropsDesc          = "Bombs, arrows, seeds, nuts, sticks and\n"         //
                                        "magic jars appear as normal.\n"                   //
                                        "Bombchus can sometimes replace bomb drops.";      //
string_view noAmmoDropsDesc           = "All ammo drops will be replaced by blue rupees,\n"//
                                        "except for Deku Sticks.\n"                        //
                                        "Ammo upgrades will only refill ammo by 10 units.";//
/*------------------------------                                                           //
|    HEART DROPS AND REFILLS   |                                                           //
------------------------------*/                                                           //
string_view defaultHeartDropsDesc     = "Heart drops will appear as normal.\n"             //
                                        "Health upgrades fully heal Link when picked up.\n"//
                                        "Fairies heal Link as normal.";                    //
string_view noHeartDropsDesc          = "Heart drops will be replaced by green rupees.\n"  //
                                        "Health upgrades fully heal Link when picked up.\n"//
                                        "Fairies heal Link as normal.";                    //
string_view noHeartRefillDesc         = "Heart drops will appear as normal.\n"             //
                                        "Health upgrades don't heal Link when picked up.\n"//
                                        "Fairies heal Link by only 3 hearts.";             //
string_view scarceHeartsDesc          = "Heart drops will be replaced by green rupees.\n"  //
                                        "Health upgrades don't heal Link when picked up.\n"//
                                        "Fairies heal Link by only 3 hearts.";             //
/*------------------------------                                                           //
|      RANDOM MQ DUNGEONS      |                                                           //
------------------------------*/                                                           //
string_view randomMQDungeonsDesc      = "If set, a random number of dungeons will have\n"  //
                                        "Master Quest designs.";                           //
                                                                                           //
/*------------------------------                                                           //
|       MQ DUNGEON COUNT       |                                                           //
------------------------------*/                                                           //
string_view mqDungeonCountDesc        = "Specify the number of Master Quest dungeons to\n"
                                        "appear in the game. Which dungeons become Master\n"
                                        "Quest will be chosen at random.";                 //
/*------------------------------                                                           //
|   SHUFFLE DUNGEON REWARDS    |                                                           //
------------------------------*/                                                           //
string_view shuffleRewardsEndOfDungeon= "Medallions and Spiritual Stones will be given as\n"
                                        "rewards for beating dungeons.\n"                  //
                                        "\n"                                               //
                                        "This setting will force Link's Pocket to be a\n"  //
                                        "Medallion or Spiritual Stone.";                   //
string_view shuffleRewardsAnyDungeon  = "Medallions and Spiritual Stones can only appear\n"//
                                        "inside of dungeons.";                             //
string_view shuffleRewardsOverworld   = "Medallions and Spiritual Stones can only appear\n"//
                                        "outside of dungeons.";                            //
string_view shuffleRewardsAnywhere    = "Medallions and Spiritual Stones can appear\n"     //
                                        "anywhere.";                                       //
/*------------------------------                                                           //
|        LINK'S POCKET         |                                                           //
------------------------------*/                                                           //
string_view linksPocketDungeonReward  = "Link will start with a Dungeon Reward in his\n"   //
                                        "inventory.";                                      //
string_view linksPocketAdvancement    = "Link will receive a random advancement item at the"
                                        "beginning of the playthrough.";                   //
string_view linksPocketAnything       = "Link will receive a random item from the item pool"
                                        "at the beginning of the playthrough.";            //
string_view linksPocketNothing        = "Link will start with a very useful green rupee."; //
/*------------------------------                                                           //
|         SONG SHUFFLE         |                                                           //
------------------------------*/                                                           //
string_view songsSongLocations        = "Songs will only appear at locations that normally\n"
                                        "teach songs.";                                    //
string_view songsDungeonRewards       = "Songs appear at the end of dungeons. For major\n" //
                                        "dungeons, they will be at the boss heart container"
                                        "location. The remaining 4 songs are placed at:\n" //
                                        "- Zelda's Lullaby Location\n"                     //
                                        "- Ice Cavern's Serenade of Water Location\n"      //
                                        "- Bottom of the Well's Lens of Truth Location\n"  //
                                        "- Gerudo Training Ground's Ice Arrow Location";   //
string_view songsAllLocations         = "Songs can appear in any location.";               //
                                                                                           //
/*------------------------------                                                           //
|         SHOPSANITY           |                                                           //
------------------------------*/                                                           //
string_view shopsOff                  = "All shop items will be the same as vanilla.";     //
string_view shopsZero                 = "Vanilla shop items will be shuffled among\n"      //
                                        "different shops.";                                //
string_view shopsOne                  = "Vanilla shop items will be shuffled among\n"      //
                                        "different shops, and each shop will contain\n"    //
                                        "one non-vanilla shop item.";                      //
string_view shopsTwo                  = "Vanilla shop items will be shuffled among\n"      //
                                        "different shops, and each shop will contain\n"    //
                                        "two non-vanilla shop items.";                     //
string_view shopsThree                = "Vanilla shop items will be shuffled among\n"      //
                                        "different shops, and each shop will contain\n"    //
                                        "three non-vanilla shop items.";                   //
string_view shopsFour                 = "Vanilla shop items will be shuffled among\n"      //
                                        "different shops, and each shop will contain\n"    //
                                        "four non-vanilla shop items.";                    //
string_view shopsRandom               = "Vanilla shop items will be shuffled among\n"      //
                                        "different shops, and each shop will contain\n"    //
                                        "1-4 non-vanilla shop items.";                     //
/*------------------------------                                                           //
|         TOKENSANITY          |                                                           //
------------------------------*/                                                           //
string_view tokensOff                 = "GS locations will not be shuffled.";              //
string_view tokensDungeon             = "This only shuffles the GS locations that are\n"   //
                                        "within dungeons, increasing the value of most\n"  //
                                        "dungeons and making internal dungeon exploration\n"
                                        "more diverse.";                                   //
string_view tokensOverworld           = "This only shuffles the GS locations that are\n"   //
                                        "outside of dungeons.";                            //
string_view tokensAllTokens           = "Effectively adds 100 new locations for items to\n"//
                                        "appear.";                                         //
                                                                                           //
/*------------------------------                                                           //
|        SCRUB SHUFFLE         |                                                           //
------------------------------*/                                                           //
string_view scrubsOff                 = "Only the 3 Scrubs that give one-time items in the\n"
                                        "vanilla game (PoH, Deku Nut capacity, and Deku\n" //
                                        "Stick capacity) will have random items.";         //
string_view scrubsAffordable          = "All Scrub prices will be reduced to 10 rupees each";
string_view scrubsExpensive           = "All Scrub prices will be their vanilla prices.\n" //
                                        "This will require spending over 1000 rupees on\n" //
                                        "Scrubs.";                                         //
string_view scrubsRandomPrices        = "All Scrub prices will be between 0-95 rupees. This"
                                        "will on average be very, very expensive overall.";//
/*------------------------------                                                           //
|         SHUFFLE COWS         |                                                           //
------------------------------*/                                                           //
string_view shuffleCowsDesc           = "Enabling this will let cows give you items upon\n"//
                                        "performing Epona's song in front of them. There\n"//
                                        "are 9 cows, and an extra in MQ Jabu.";            //
                                                                                           //
/*------------------------------                                                           //
|     SHUFFLE KOKIRI SWORD     |                                                           //
------------------------------*/                                                           //
string_view kokiriSwordDesc           = "Enabling this shuffles the Kokiri Sword into the\n"
                                        "item pool.\n"                                     //
                                        "\n"                                               //
                                        "This will require extensive use of sticks until\n"//
                                        "the sword is found.";                             //
/*------------------------------                                                           //
|       SHUFFLE OCARINAS       |                                                           //
------------------------------*/                                                           //
string_view ocarinasDesc              = "Enabling this shuffles the Fairy Ocarina and the\n"
                                        "Ocarina of Time into the item pool.\n"            //
                                        "\n"                                               //
                                        "This will require finding an Ocarina before being\n"
                                        "able to play songs.";                             //
/*------------------------------                                                           //
|      SHUFFLE WEIRD EGG       |                                                           //
------------------------------*/                                                           //
string_view weirdEggDesc              = "Enabling this shuffles the Weird Egg from Malon\n"//
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
string_view gerudoTokenDesc           = "Enabling this shuffles the Gerudo Token into the\n"
                                        "item pool.\n"                                     //
                                        "\n"                                               //
                                        "The Gerudo Token is required to enter the Gerudo\n"
                                        "Training Ground.";                                //
/*------------------------------                                                           //
|      SHUFFLE MAGIC BEANS     |                                                           //
------------------------------*/                                                           //
string_view magicBeansDesc            = "Enabling this adds a pack of 10 beans to the item\n"
                                        "pool and changes the Magic Bean Salesman to sell a"
                                        "random item at a price of 60 rupees.";            //
/*------------------------------                                                           //
|       SHUFFLE MERCHANTS      |                                                           //
------------------------------*/                                                           //
string_view merchantsDesc             = "Enabling this adds a Giant's Knife and a pack\n"  //
                                        "of Bombchus to the item pool and changes both\n"  //
                                        "Medigoron and the Haunted Wasteland Carpet\n"     //
                                        "Salesman to sell a random item once at the price\n"
                                        "of 200 rupees.";                                  //
string_view merchantsHintsDesc        = "These hints will make Medigoron and the Carpet\n" //
                                        "Salesman tell you which item they're selling.\n"  //
                                        "\n"                                               //
                                        "The Clearer Hints setting will affect how they\n" //
                                        "refer to the item.";                              //
/*------------------------------                                                           //
|      MAPS AND COMPASSES      |                                                           //
------------------------------*/                                                           //
string_view mapCompassStartWith       = "Maps and Compasses are given to you from the\n"   //
                                        "start. This will add a small amount of money and\n"
                                        "refill items to the pool.";                       //
string_view mapCompassVanilla         = "Maps and Compasses will appear in their vanilla\n"//
                                        "locations.";                                      //
string_view mapCompassOwnDungeon      = "Maps and Compasses can only appear in their\n"    //
                                        "respective dungeon.";                             //
string_view mapCompassAnyDungeon      = "Maps and Compasses can only appear in a dungeon,\n"
                                        "but not necessarily the dungeon they are for.";   //
string_view mapCompassOverworld       = "Maps and Compasses can only appear outside of\n"  //
                                        "dungeons.";                                       //
string_view mapCompassAnywhere        = "Maps and Compasses can appear anywhere in the\n"  //
                                        "world.";                                          //
/*------------------------------                                                           //
|         SMALL KEYS           |                                                           //
------------------------------*/                                                           //
string_view smallKeyStartWith         = "Small Keys are given to you from the start so you\n"
                                        "won't have to worry about locked doors. An easier\n"
                                        "mode.";                                           //
string_view smallKeyVanilla           = "Small Keys will appear in their vanilla locations."
                                        "You start with 3 keys in Spirit Temple MQ because\n"
                                        "the vanilla key layout is not beatable in logic.";//
string_view smallKeyOwnDungeon        = "Small Keys can only appear in their respective\n" //
                                        "dungeon. If Fire Temple is not a Master Quest\n"  //
                                        "dungeon, the door to the Boss Key chest will be\n"//
                                        "unlocked.";                                       //
string_view smallKeyAnyDungeon        = "Small Keys can only appear inside of any dungeon,\n"
                                        "but won't necessarily be in the dungeon that the\n"
                                        "key is for. A difficult mode since it is more\n"  //
                                        "likely to need to enter a dungeon multiple times.";
string_view smallKeyOverworld         = "Small Keys can only appear outside of dungeons.\n"//
                                        "You may need to enter a dungeon multiple times to\n"
                                        "gain items to access the overworld locations with\n"
                                        "the keys required to finish a dungeon.";          //
string_view smallKeyAnywhere          = "Small Keys can appear anywhere in the world. A\n" //
                                        "difficult mode since it is more likely to need to\n"
                                        "enter a dungeon multiple times.";                 //
/*------------------------------                                                           //
|     GERUDO FORTRESS KEYS     |                                                           //
------------------------------*/                                                           //
string_view gerudoKeysVanilla         = "Gerudo Fortress Keys will appear in their vanilla\n"
                                        "location, dropping from fighting Gerudo guards\n" //
                                        "that attack when trying to free the jailed\n"     //
                                        "carpenters.";                                     //
string_view gerudoKeysAnyDungeon      = "Gerudo Fortress Keys can only appear inside of\n" //
                                        "dungeons.";                                       //
string_view gerudoKeysOverworld       = "Gerudo Fortress Keys can only appear outside of\n"//
                                        "dungeons.";                                       //
string_view gerudoKeysAnywhere        = "Gerudo Fortress Keys can appear anywhere in the\n"//
                                        "world.";                                          //
/*------------------------------                                                           //
|          BOSS KEYS           |                                                           //
------------------------------*/                                                           //
string_view bossKeyStartWith          = "Boss Keys are given to you from the start so you\n"
                                        "won't have to worry about boss doors. An easier\n"//
                                        "mode.";                                           //
string_view bossKeyVanilla            = "Boss Keys will appear in their vanilla locations.";
string_view bossKeyOwnDungeon         = "Boss Keys can only appear in their respective\n"  //
                                        "dungeon.";                                        //
string_view bossKeyAnyDungeon         = "Boss Keys can only appear inside of any dungeon,\n"
                                        "but won't necessarily be in the dungeon that the\n"
                                        "key is for. A difficult mode since it is more\n"  //
                                        "likely to need to enter a dungeon multiple times.";
string_view bossKeyOverworld          = "Boss Keys can only appear outside of dungeons.\n" //
                                        "You may need to enter a dungeon without the boss\n"
                                        "key to get items required to find the key in the\n"
                                        "overworld.";                                      //
string_view bossKeyAnywhere           = "Boss Keys can appear anywhere in the world. A\n"  //
                                        "difficult mode since it is more likely to need to\n"
                                        "enter a dungeon multiple times.";                 //
/*------------------------------                                                           //
|   GANON'S CASTLE BOSS KEY    |                                                           //
------------------------------*/                                                           //
string_view ganonKeyStartWith         = "Ganon's Castle Boss Key is given to you from the\n"
                                        "start and you don't have to worry about finding it";
string_view ganonKeyVanilla           = "Ganon's Castle Boss Key will appear in the vanilla"
                                        "location.";                                       //
string_view ganonKeyOwnDungeon        = "Ganon's Castle Boss Key can only appear inside\n" //
                                        "Ganon's Castle.";                                 //
string_view ganonKeyAnyDungeon        = "Ganon's Castle Boss Key can only appear inside of\n"
                                        "a dungeon, but not necessarily Ganon's Castle.";  //
string_view ganonKeyOverworld         = "Ganon's Castle Boss Key can only appear outside of"
                                        "dungeons.";                                       //
string_view ganonKeyAnywhere          = "Ganon's Castle Boss Key can appear anywhere in the"
                                        "world.";                                          //
string_view ganonKeyLACS              = "These settings put the boss key on the Light Arrow"
                                        "Cutscene location, from Zelda in Temple of Time as"
                                        "adult, with differing requirements.";             //
/*------------------------------                                                           //
|        LACS CONDITIONS       |                                                           //
------------------------------*/                                                           //
string_view lacsMedallionCountDesc    = "Set the number of Medallions required to trigger\n"
                                        "the Light Arrow Cutscene.";                       //
string_view lacsStoneCountDesc        = "Set the number of Spiritual Stones required to\n" //
                                        "trigger the Light Arrow Cutscene.";               //
string_view lacsRewardCountDesc       = "Set the number of Dungeon Rewards (Spiritual\n"   //
                                        "Stones and Medallions) required to trigger the\n" //
                                        "Light Arrow Cutscene.";                           //
string_view lacsDungeonCountDesc      = "Set the number of completed dungeons required to\n"
                                        "trigger the Light Arrow Cutscene.\n"              //
                                        "\n"                                               //
                                        "Dungeons are considered complete when Link steps\n"
                                        "into the blue warp at the end of them.";          //
string_view lacsTokenCountDesc        = "Set the number of Gold Skulltula Tokens required\n"
                                        "to trigger the Light Arrow Cutscene.";            //
/*------------------------------                                                           //
|      SKIP CHILD STEALTH      |                                                           //
------------------------------*/                                                           //
string_view childStealthDesc          = "The crawlspace into Hyrule Castle goes straight to"
                                        "Zelda, skipping the guards.";                     //
/*------------------------------                                                           //
|      SKIP TOWER ESCAPE       |                                                           //
------------------------------*/                                                           //
string_view skipTowerEscapeDesc       = "The tower escape sequence between Ganondorf and\n"//
                                        "Ganon will be skipped.";                          //
/*------------------------------                                                           //
|       SKIP EPONA RACE        |                                                           //
------------------------------*/                                                           //
string_view skipEponaRaceDesc         = "Epona can be summoned with Epona's Song without\n"//
                                        "needing to race Ingo.";                           //
/*------------------------------                                                           //
|     SKIP MINIGAME PHASES     |                                                           //
------------------------------*/                                                           //
string_view skipMinigamePhasesDesc    = "Completing the second objective in the Dampe Race\n"
                                        "and Gerudo Archery on the first attempt will give\n"
                                        "both rewards at once for that minigame.";          //
/*------------------------------                                                           //
|        FREE SCARECROW        |                                                           //
------------------------------*/                                                           //
string_view freeScarecrowDesc         = "Pulling out the Ocarina near a spot at which\n"   //
                                        "Pierre can spawn will do so, without needing\n"   //
                                        "the song.";                                       //
/*------------------------------                                                           //
|      FOUR POES CUTSCENE      |                                                           //
------------------------------*/                                                           //
string_view fourPoesDesc              = "The cutscene with the 4 poes in Forest Temple will"
                                        "be skipped. If the cutscene is not skipped, it can"
                                        "be exploited to reach the basement early.";       //
/*------------------------------                                                           //
|     TEMPLE OF TIME INTRO     |                                                           //
------------------------------*/                                                           //
string_view templeOfTimeIntroDesc     = "The introduction cutscene to Temple of Time will\n"
                                        "be skipped. This cutscene is helpful for\n"       //
                                        "performing Door of Time Skip should the Door of\n"//
                                        "Time be closed.";                                 //
/*------------------------------                                                           //
|     BIG POE TARGET COUNT     |                                                           //
------------------------------*/                                                           //
string_view bigPoeTargetCountDesc     = "The Poe buyer will give a reward for turning in\n"//
                                        "the chosen number of Big Poes.";                  //
/*------------------------------                                                           //
|     NUM REQUIRED CUCCOS      |                                                           //
------------------------------*/                                                           //
string_view numRequiredCuccosDesc     = "The cucco lady will give a reward for returning\n"//
                                        "this many of her cuccos to the pen.";             //
/*------------------------------                                                           //
|     GOSSIP STONE HINTS       |                                                           //
------------------------------*/                                                           //
string_view gossipStonesHintsDesc     = "Gossip Stones can be made to give hints about\n"  //
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
string_view clearerHintsDesc          = "The hints provided by Gossip Stones will be very\n"
                                        "direct if this option is enabled.";               //
/*------------------------------                                                           //
|      HINT DISTRIBUTION       |                                                           //
------------------------------*/                                                           //
string_view uselessHintsDesc          = "Only junk hints.";                                //
string_view balancedHintsDesc         = "Recommended hint spread.";                        //
string_view strongHintsDesc           = "More useful hints.";                              //
string_view veryStrongHintsDesc       = "Many powerful hints.";                            //
                                                                                           //
/*------------------------------                                                           //
|       DAMAGE MULTIPLIER      |                                                           //
------------------------------*/                                                           //
string_view damageMultiDesc           = "Changes the amount of damage taken.\n"            //
                                        "\n"                                               //
                                        "If set to OHKO, Link will die in one hit.";       //
/*------------------------------                                                           //
|        STARTING TIME         |                                                           //
------------------------------*/                                                           //
string_view startingTimeDesc          = "Change up Link's sleep routine.";                 //
                                                                                           //
/*------------------------------                                                           //
|     NIGHT GS EXPECT SUNS     |                                                           //
------------------------------*/                                                           //
string_view nightGSDesc               = "GS Tokens that can only be obtained during the\n" //
                                        "night expect you to have Sun's Song to collect\n" //
                                        "them. This prevents needing to wait until night\n"//
                                        "for some locations.";                             //
                                                                                           //
/*------------------------------                                                           //
|       CHEST ANIMATIONS       |                                                           //
------------------------------*/                                                           //
string_view chestAnimDesc             = "Choose if you want the slow animation to play\n"  //
                                        "if a chest contains a major item.\n";             //
                                                                                           //
/*------------------------------                                                           //
|     CHEST SIZE AND COLOR     |                                                           //
------------------------------*/                                                           //
string_view chestSizeDesc             = "This option will change the appearance of all\n"  //
                                        "regular chests depending on their contents:\n"    //
                                        "Major Items    =    Big Wooden Chests\n"          //
                                        "Lesser Items   =    Small Wooden Chests\n"        //
                                        "Boss Keys      =    Big Fancy Chests\n"           //
                                        "Small Keys     =    Small Fancy Chests";          //
                                                                                           //
/*------------------------------                                                           //
|        INGAME SPOILERS       |                                                           //
------------------------------*/                                                           //
string_view ingameSpoilersShowDesc    = "Every spoiler is shown.";                         //
string_view ingameSpoilersHideDesc    = "Hides the spheres page and only shows a\n"        //
                                        "location's item after it has been found.";        //
                                                                                           //
/*------------------------------                                                           //
|      MENU OPENING BUTTON     |                                                           //
------------------------------*/                                                           //
string_view menuButtonDesc            = "Choose which button will bring up the Dungeon\n"  //
                                        "Information Menu. You can also use the menu to\n" //
                                        "buffer frame perfect inputs if you choose D-Pad"; //
                                                                                           //
/*------------------------------                                                           //
|     START WITH CONSUMABLES   |                                                           //
------------------------------*/                                                           //
string_view startWithConsumablesDesc  = "Start the game with maxed out Deku Sticks and Deku"
                                        "Nuts.";                                           //
                                                                                           //
/*------------------------------                                                           //
|     START WITH MAX RUPEES    |                                                           //
------------------------------*/                                                           //
string_view startWithMaxRupeesDesc    = "Start the game with a full wallet.\n"             //
                                        "Wallet upgrades will also fill the wallet.";      //
                                                                                           //
/*------------------------------                                                           //
|          ITEM POOL           |                                                           //
------------------------------*/                                                           //
string_view itemPoolPlentiful         = "Extra major items are added to the pool.";        //
string_view itemPoolBalanced          = "Original item pool.";                             //
string_view itemPoolScarce            = "Some excess items are removed, including health\n"//
                                        "upgrades.";                                       //
string_view itemPoolMinimal           = "Most excess items are removed.";                  //
                                                                                           //
/*------------------------------                                                           //
|          ICE TRAPS           |                                                           //
------------------------------*/                                                           //
string_view iceTrapsOff               = "All Ice Traps are removed.";                      //
string_view iceTrapsNormal            = "Only Ice Traps from the base item pool are placed.";
string_view iceTrapsExtra             = "Chance to add extra Ice Traps when junk items are\n"
                                        "added to the itempool.";                          //
string_view iceTrapsMayhem            = "All added junk items will be Ice Traps.";         //
string_view iceTrapsOnslaught         = "All junk items will be replaced by Ice Traps, even"
                                        "those in the base pool.";                         //
/*------------------------------                                                           //
|  USE FARORE'S WIND ANYWHERE  |                                                           //
------------------------------*/                                                           //
string_view faroresWindAnywhereDesc   = "Farore's Wind can be used outside of dungeons.\n" //
                                        "\n"                                               //
                                        "This setting will not change the logic.";         //
                                                                                           //
/*------------------------------                                                           //
|    ENABLE ADULT DEKU STICK   |                                                           //
------------------------------*/                                                           //
string_view adultStickDesc            = "Adult Link can wield a deku stick. In game Adult\n"
                                        "Link will look like he's holding a Hylian Shield,\n"
                                        "but rest assured it is a deku stick.\n"           //
                                        "\n"                                               //
                                        "This setting will not change the logic.";         //
                                                                                           //
/*------------------------------                                                           //
|    ENABLE ADULT BOOMERANG    |                                                           //
------------------------------*/                                                           //
string_view adultBoomerangDesc        = "Adult Link can throw the boomerang.\n"            //
                                        "\n"                                               //
                                        "This setting will not change the logic.";         //
                                                                                           //
/*------------------------------                                                           //
|     ENABLE CHILD HAMMER      |                                                           //
------------------------------*/                                                           //
string_view childHammerDesc           = "Child Link can swing the Megaton Hammer.\n"       //
                                        "\n"                                               //
                                        "This setting will not change the logic.";         //
                                                                                           //
/*------------------------------                                                           //
|         COLORED KEYS         |                                                           //
------------------------------*/                                                           //
string_view coloredKeysDesc           = "If set, small key models will be colored\n"       //
                                        "differently depending on which dungeon they can be"
                                        "used in. Forest Temple keys are green. Fire Temple"
                                        "keys are red. etc.";                              //
string_view coloredBossKeysDesc       = "If set, boss key models will be colored\n"        //
                                        "differently depending on which dungeon they can be"
                                        "used in. The Forest Temple boss key is green. The "
                                        "Fire Temple boss key is red. etc.";               //
/*------------------------------                                                           //
|         MIRROR WORLD         |                                                           //
------------------------------*/                                                           //
string_view mirrorWorldDesc           = "If set, the world will be mirrored.";             //
                                                                                           //
/*------------------------------                                                           //
|    RANDOM TRAP DAMAGE TYPE   |                                                           //
------------------------------*/                                                           //
string_view randomTrapDmgDesc         = "If set, ice traps will sometimes damage Link and\n"
                                        "knock him back or electrocute him instead of\n"   //
                                        "freezing him.";                                   //
                                                                                           //
string_view basicTrapDmgDesc          = "All alternative traps will cause a small damage\n"
                                        "and no other negative effects\n";                 //
                                                                                           //
string_view advancedTrapDmgDesc       = "Some chest traps will burn your Deku Shield or\n" //
                                        "cause a lot of damage (with one-hit protection)"; //
                                                                                           //--------------//
/*------------------------------                                                                           //
|  DETAILED LOGIC EXPLANATIONS |                                                                           //
------------------------------*/                                                                           //
string_view ToggleAllDetailedLogicDesc                = "Enable or Disable all Detailed Logic tricks at\n" //
                                                        "once.";                                           //
string_view LogicGrottosWithoutAgonyDesc              = "Allows entering hidden grottos without the Shard\n"
                                                        "of Agony.";                                       //
string_view LogicVisibleCollisionDesc                 = "Allows going through the Kakariko Village Gate as\n"
                                                        "child when coming from the Mountain Trail side."; //
string_view LogicFewerTunicRequirementsDesc           = "Allows the following possible without Tunics:\n"  //
                                                        "- Enter Water Temple.\n"                          //
                                                        "- Enter Fire Temple. Only the first floor\n"      //
                                                        "  is accessible, and not Volvagia.\n"             //
                                                        "- Zora's Fountain Bottom Freestanding PoH.\n"     //
                                                        "- Gerudo Training Grounds Underwater Silver Rupee\n"
                                                        "Chest. May need to make multiple trips.";         //
string_view LogicLostWoodsGSBeanDesc                  = "You can collect the token with a precise Hookshot\n"
                                                        "use, as long as you can kill the Skulltula somehow"
                                                        "first. It can be killed using Longshot, Bow,\n"   //
                                                        "Bombchus or Din's Fire.";                         //
string_view LogicLabDivingDesc                        = "Remove the Iron Boots in the midst of Hookshotting"
                                                        "the underwater crate";                            //
string_view LogicLabWallGSDesc                        = "The jump slash to actually collect the token is\n"//
                                                        "somewhat precise";                                //
string_view LogicGraveyardPoHDesc                     = "Using a precise moving setup you can obtain the\n"//
                                                        "Piece of Heart by having the Boomerang interact\n"//
                                                        "with it along the return path.";                  //
string_view LogicChildDampeRacePoHDesc                = "It is possible to complete the second dampe race\n"
                                                        "as child in under a minute, but it is a strict\n" //
                                                        "time limit.";                                     //
string_view LogicGerudoKitchenDesc                    = "The logic normally guarantees one of Bow,\n"      //
                                                        "Hookshot, or Hover Boots.";                       //
string_view LogicLensWastelandDesc                    = "By memorizing the path, you can travel through the"
                                                        "Wasteland without using the Lens of Truth to see\n"
                                                        "the Poe. The equivalent trick for going in reverse"
                                                        "through the Wasteland is \"Reverse Wasteland\"."; //
string_view LogicReverseWastelandDesc                 = "By memorizing the path, you can travel through the"
                                                        "Wasteland in reverse.";                           //
string_view LogicColossusGSDesc                       = "Somewhat precise. If you kill enough Leevers you\n"
                                                        "can get enough of a break to take some time to aim"
                                                        "more carefully.";                                 //
string_view LogicOutsideGanonsGSDesc                  = "Can be killed with a precise sidehop jumpslash\n" //
                                                        "from the top of the broken arch.";                //
string_view LogicManOnRoofDesc                        = "Can be reached by side-hopping off the watchtower.";
string_view LogicDMTBombableDesc                      = "Child Link can blow up the wall using a nearby\n" //
                                                        "bomb flower. You must backwalk with the flower and"
                                                        "then quickly throw it toward the wall.";          //
string_view LogicDMTSoilGSDesc                        = "Bugs will go into the soft soil even while the\n" //
                                                        "boulder is still blocking the entrance. Then,\n"  //
                                                        "using a precise moving setup you can kill the Gold"
                                                        "Skulltula and obtain the token by having the\n"   //
                                                        "Boomerang interact with it along the return path.";
string_view LogicLinkGoronDinsDesc                    = "The timing is quite awkward.";                    //
string_view LogicGoronCityLeftMostDesc                = "A precise backwalk starting from on top of the\n" //
                                                        "crate and ending with a precisely-timed backflip\n"
                                                        "can reach this chest without needing either the\n"//
                                                        "Hammer or Silver Gauntlets.";                     //
string_view LogicGoronCityPotDesc                     = "A Bombchu can be used to stop the spinning pot,\n"//
                                                        "but it can be quite finicky to get it to work.";  //
string_view LogicGoronCityPotWithStrengthDesc         = "Allows for stopping the Goron City Spinning Pot\n"//
                                                        "using a bomb flower alone, requiring strength in\n"
                                                        "lieu of inventory explosives.";                   //
string_view LogicChildRollingWithStrengthDesc         = "Use the bombflower on the stairs or near\n"       //
                                                        "Medigoron. Timing is tight, especially without\n" //
                                                        "backwalking.";                                    //
string_view LogicCraterUpperToLowerDesc               = "With the Hammer, you can jump slash the rock twice"
                                                        "in the same jump in order to destroy it before you"
                                                        "fall into the lava.";                             //
string_view LogicCraterBeanPoHWithHoversDesc          = "Hover from the base of the bridge near Goron City\n"
                                                        "and walk up the very steep slope.";               //
string_view LogicBiggoronBoleroDesc                   = "Playing a warp song normally causes a trade item\n"
                                                        "to spoil immediately, however, it is possible use\n"
                                                        "Bolero to reach Biggoron and still deliver the Eye"
                                                        "Drops before they spoil. If you do not wear the\n"
                                                        "Goron Tunic, the heat timer inside the crater will"
                                                        "override the trade item's timer. When you exit to\n"
                                                        "Death Mountain Trail you will have one second to\n"
                                                        "show the Eye Drops before they expire.";          //
string_view LogicZoraRiverLowerDesc                   = "Adult can reach this PoH with a precise jump, no\n"
                                                        "Hover Boots required.";                           //
string_view LogicZoraRiverUpperDesc                   = "Adult can reach this PoH with a precise jump, no\n"
                                                        "Hover Boots required.";                           //
string_view LogicDekuB1WebsWithBowDesc                = "All spider web walls in the Deku Tree basement can"
                                                        "be burnt as adult with just a bow by shooting\n"  //
                                                        "through torches. This trick only applies to the\n"//
                                                        "circular web leading to Gohma; the two vertical\n"//
                                                        "webs are always in logic. Backflip onto the chest\n"
                                                        "near the torch at the bottom of the vine wall.\n" //
                                                        "With precise positioning you can shoot through the"
                                                        "torch to the right edge of the circular web.";    //
string_view LogicDekuB1SkipDesc                       = "A precise jump can be used to skip needing to use\n"
                                                        "the Slingshot to go around B1 of the Deku Tree. If"
                                                        "used with the \"Closed Forest\" setting, a\n"     //
                                                        "Slingshot will not be guaranteed to exist\n"      //
                                                        "somewhere inside the Forest. This trick applies to"
                                                        "both Vanilla and Master Quest.";                  //
string_view LogicDekuBasementGSDesc                   = "Can be defeated by doing a precise jump slash.";  //
string_view LogicDCStaircaseDesc                      = "The Bow can be used to knock down the stairs with\n"
                                                        "two well-timed shots.";                           //
string_view LogicDCJumpDesc                           = "Jump is adult only.";                             //
string_view LogicDCSlingshotSkipDesc                  = "With precise platforming, child can cross the\n"  //
                                                        "platforms while the flame circles are there. When\n"
                                                        "enabling this trick, it's recommended that you\n" //
                                                        "also enable the Adult variant: \"Dodongo's Cavern\n"
                                                        "Spike Trap Room Jump without Hover Boots\".";     //
string_view LogicDCScarecrowGSDesc                    = "You can jump off an Armos Statue to reach the\n"  //
                                                        "alcove with the Gold Skulltula. It takes quite a\n"
                                                        "long time to pull the statue the entire way. The\n"
                                                        "jump to the alcove can be a bit picky when done\n"//
                                                        "as child.";                                       //
string_view LogicJabuBossGSAdultDesc                  = "You can easily get over to the door to the near\n"//
                                                        "boss area early with Hover Boots. The tricky part\n"
                                                        "is getting through the door without being able to\n"
                                                        "use a box to keep the switch pressed. One way is\n"
                                                        "to quickly roll from the switch and open the door\n"
                                                        "before it closes.";                               //
string_view LogicJabuScrubJumpDiveDesc                = "Standing above the underwater tunnel leading to\n"//
                                                        "the scrub, jump down and swim through the tunnel.\n"
                                                        "This allows adult to access the scrub with no\n"  //
                                                        "Scale or Iron Boots.";                            //
string_view LogicForestOutsideBackdoorDesc            = "With a precise jump slash from above, you can\n"  //
                                                        "reach the backdoor to the west courtyard without\n"
                                                        "Hover Boots. Applies to both Vanilla and Master\n"//
                                                        "Quest.";                                          //
string_view LogicForestDoorFrameDesc                  = "A precise Hover Boots movement from the upper\n"  //
                                                        "balconies in this courtyard can be used to get on\n"
                                                        "top of the door frame. Applies to both Vanilla and"
                                                        "Master Quest. In Vanilla, from on top the door\n" //
                                                        "frame you can summon Pierre, allowing you to\n"   //
                                                        "access the falling ceiling room early. In Master\n"
                                                        "Quest, this allows you to obtain the GS on the\n" //
                                                        "door frame as adult without Hookshot or Song of\n"//
                                                        "Time.";                                           //
string_view LogicForestOutdoorEastGSDesc              = "Precise Boomerang throws can allow child to kill\n"
                                                        "the Skulltula and collect the token.";            //
string_view LogicFireBossDoorJumpDesc                 = "The Fire Temple Boss Door can be reached with a\n"//
                                                        "precise jump. You must be touching the side wall\n"
                                                        "of the room so that Link will grab the ledge from\n"
                                                        "farther away than is normally possible.";         //
string_view LogicFireStrengthDesc                     = "A precise jump can be used to skip pushing the\n" //
                                                        "block.";                                          //
string_view LogicFireScarecrowDesc                    = "Also known as \"Pixelshot\". The Longshot can\n"  //
                                                        "reach the target on the elevator itself, allowing\n"
                                                        "you to skip needing to spawn the scarecrow.";     //
string_view LogicFireFlameMazeDesc                    = "If you move quickly you can sneak past the edge of"
                                                        "a flame wall before it can rise up to block you.\n"
                                                        "To do it without taking damage is more precise.\n"//
                                                        "Allows you to progress without needing either a\n"//
                                                        "Small Key or Hover Boots.";                       //
string_view LogicFireSongOfTimeDesc                   = "A precise jump can be used to reach this room.";  //
string_view LogicWaterTempleTorchLongshotDesc         = "Stand on the eastern side of the central pillar\n"//
                                                        "and longshot the torches on the bottom level.\n"  //
                                                        "Swim through the corridor and float up to the top\n"
                                                        "level. This allows access to this area and lower\n"
                                                        "water levels without Iron Boots. The majority of\n"
                                                        "the tricks that allow you to skip Iron Boots in\n"//
                                                        "the Water Temple are not going to be relevant\n"  //
                                                        "unless this trick is first enabled.";             //
string_view LogicWaterTempleUpperBoostDesc            = "Stand on the corner closest to the upper ledge\n" //
                                                        "where you play Zelda's Lullaby to raise the water\n"
                                                        "and put a bomb down behind you. Hold forward when\n"
                                                        "the bomb explodes and Link should jump just far\n"//
                                                        "enough to grab the ledge.";                       //
string_view LogicWaterCentralBowDesc                  = "A very precise Bow shot can hit the eye switch\n" //
                                                        "from the floor above. Then, you can jump down into"
                                                        "the hallway and make through it before the gate\n"//
                                                        "closes. It can also be done as child, using the\n"//
                                                        "Slingshot instead of the Bow.";                   //
string_view LogicWaterCentralGSFWDesc                 = "If you set Farore's Wind inside the central pillar"
                                                        "and then return to that warp point after raising\n"
                                                        "the water to the highest level, you can obtain\n" //
                                                        "this Skulltula Token with Hookshot or Boomerang.";//
string_view LogicWaterCrackedWallNothingDesc          = "A precise jump slash (among other methods) will\n"//
                                                        "get you to the cracked wall without needing the\n"//
                                                        "Hover Boots or to raise the water to the middle\n"//
                                                        "level. This trick supersedes \"Water Temple\n"    //
                                                        "Cracked Wall with Hover Boots\".";                //
string_view LogicWaterCrackedWallHoversDesc           = "With a midair side-hop while wearing the Hover\n" //
                                                        "Boots, you can reach the cracked wall without\n"  //
                                                        "needing to raise the water up to the middle level.";
string_view LogicWaterBossKeyRegionDesc               = "With precise Hover Boots movement it is possible\n"
                                                        "to reach the boss key chest's region without\n"   //
                                                        "needing the Longshot. It is not necessary to take\n"
                                                        "damage from the spikes. The Gold Skulltula Token\n"
                                                        "in the following room can also be obtained with\n"//
                                                        "just the Hover Boots.";                           //
string_view LogicWaterBKJumpDiveDesc                  = "Stand on the very edge of the raised corridor\n"  //
                                                        "leading from the push block room to the rolling\n"//
                                                        "boulder corridor. Face the gold skulltula on the\n"
                                                        "waterfall and jump over the boulder corridor floor"
                                                        "into the pool of water, swimming right once\n"    //
                                                        "underwater. This allows access to the boss key\n" //
                                                        "room without Iron boots.";                        //
string_view LogicWaterNorthBasementLedgeJumpDesc      = "In the northern basement there's a ledge from\n"  //
                                                        "where, in vanilla Water Temple, boulders roll out\n"
                                                        "into the room. Normally to jump directly to this\n"
                                                        "ledge logically requires the Hover Boots, but with"
                                                        "precise jump, it can be done without them. This\n"//
                                                        "trick applies to both Vanilla and Master Quest."; //
string_view LogicWaterDragonAdultDesc                 = "Normally you need both Hookshot and Iron Boots to\n"
                                                        "hit the switch and swim through the tunnel to get\n"
                                                        "to the chest. But by hitting the switch from dry\n"
                                                        "land, using one of Bombchus, Hookshot, or Bow, it\n"
                                                        "is possible to skip one or both of those\n"       //
                                                        "requirements. After the gate has been opened, a\n"//
                                                        "well-timed dive with at least the Silver Scale\n" //
                                                        "could be used to swim through the tunnel.";       //
string_view LogicWaterDragonJumpDiveDesc              = "If you come into the dragon statue room from the\n"
                                                        "serpent river, you can jump down from above and\n"//
                                                        "get into the tunnel without needing either Iron\n"//
                                                        "Boots or a Scale. This trick applies to both\n"   //
                                                        "Vanilla and Master Quest. In Vanilla, you must\n" //
                                                        "shoot the switch from above with the Bow, and then"
                                                        "quickly get through the tunnel before the gate\n" //
                                                        "closes.";                                         //
string_view LogicWaterRiverGSDesc                     = "Standing on the exposed ground toward the end of\n"
                                                        "the river, a precise Longshot use can obtain the\n"
                                                        "token.";                                          //
string_view LogicWaterFallingPlatformGSDesc           = "If you stand on the very edge of the platform,\n" //
                                                        "this Gold Skulltula can be obtained with only the\n"
                                                        "Hookshot.";                                       //
string_view LogicSpiritLowerAdultSwitchDesc           = "A bomb can be used to hit the switch on the\n"    //
                                                        "ceiling, but it must be thrown from a particular\n"
                                                        "distance away and with precise timing.";          //
string_view LogicSpiritChildBombchuDesc               = "A carefully-timed Bombchu can hit the switch.";   //
string_view LogicSpiritWallDesc                       = "The logic normally guarantees a way of dealing\n" //
                                                        "with both the Beamos and the Walltula before\n"   //
                                                        "climbing the wall.";                              //
string_view LogicSpiritLobbyGSDesc                    = "Standing on the highest part of the arm of the\n" //
                                                        "statue, a precise Boomerang throw can kill and\n" //
                                                        "obtain this Gold Skulltula. You must throw the\n" //
                                                        "Boomerang slightly off to the side so that it\n"  //
                                                        "curves into the Skulltula, as aiming directly at\n"
                                                        "it will clank off of the wall in front.";         //
string_view LogicSpiritMapChestDesc                   = "To get a line of sight from the upper torch to the"
                                                        "map chest torches, you must pull an Armos statue\n"
                                                        "all the way up the stairs.";                      //
string_view LogicSpiritSunChestDesc                   = "Using the blocks in the room as platforms you can\n"
                                                        "get lines of sight to all three torches. The timer"
                                                        "on the torches is quite short so you must move\n" //
                                                        "quickly in order to light all three.";            //
string_view LogicShadowFireArrowEntryDesc             = "It is possible to light all of the torches to open"
                                                        "the Shadow Temple entrance with just Fire Arrows,\n"
                                                        "but you must be very quick, precise, and strategic"
                                                        "with how you take your shots.";                   //
string_view LogicShadowUmbrellaDesc                   = "A very precise Hover Boots movement from off of\n"//
                                                        "the lower chest can get you on top of the crushing\n"
                                                        "spikes without needing to pull the block. Applies\n"
                                                        "to both Vanilla and Master Quest.";               //
string_view LogicShadowFreestandingKeyDesc            = "Release the Bombchu with good timing so that it\n"//
                                                        "explodes near the bottom of the pot.";            //
string_view LogicShadowStatueDesc                     = "By sending a Bombchu around the edge of the gorge,"
                                                        "you can knock down the statue without needing a\n"//
                                                        "Bow. Applies in both vanilla and MQ Shadow.";     //
string_view LogicChildDeadhandDesc                    = "Requires 9 sticks or 5 jump slashes.";            //
string_view LogicGtgWithoutHookshotDesc               = "After collecting the rest of the silver rupees in\n"
                                                        "the room, you can reach the final silver rupee on\n"
                                                        "the ceiling by being pulled up into it after\n"   //
                                                        "getting grabbed by the Wallmaster. Then, you must\n"
                                                        "also reach the exit of the room without the use of"
                                                        "the Hookshot. If you move quickly you can sneak\n"//
                                                        "past the edge of a flame wall before it can rise\n"
                                                        "up to block you. To do so without taking damage is"
                                                        "more precise.";                                   //
string_view LogicGtgFakeWallDesc                      = "A precise Hover Boots use from the top of the\n"  //
                                                        "chest can allow you to grab the ledge without\n"  //
                                                        "needing the usual requirements.";                 //
string_view LogicLensSpiritDesc                       = "Removes the requirements for the Lens of Truth in\n"
                                                        "Spirit Temple.";                                  //
string_view LogicLensShadowDesc                       = "Removes the requirements for the Lens of Truth in\n"
                                                        "Shadow Temple before the invisible moving platform";
string_view LogicLensShadowBackDesc                   = "Removes the requirements for the Lens of Truth in\n"
                                                        "Shadow Temple beyond the invisible moving platform";
string_view LogicLensBotwDesc                         = "Removes the requirements for the Lens of Truth in\n"
                                                        "Bottom of the Well.";                             //
string_view LogicLensGtgDesc                          = "Removes the requirements for the Lens of Truth in\n"
                                                        "Gerudo Training Grounds.";                        //
string_view LogicLensCastleDesc                       = "Removes the requirements for the Lens of Truth in\n"
                                                        "Ganon's Castle.";                                 //
string_view LogicLensJabuMQDesc                       = "Removes the requirements for the Lens of Truth in\n"
                                                        "Jabu Jabu's Belly MQ.";                           //
string_view LogicLensSpiritMQDesc                     = "Removes the requirements for the Lens of Truth in\n"
                                                        "Spirit Temple MQ.";                               //
string_view LogicLensShadowMQDesc                     = "Removes the requirements for the Lens of Truth in\n"
                                                        "Shadow Temple MQ before the invisible moving \n"  //
                                                        "platform";                                        //
string_view LogicLensShadowMQBackDesc                 = "Removes the requirements for the Lens of Truth in\n"
                                                        "Shadow Temple MQ beyond the invisible moving \n"  //
                                                        "platform";                                        //
string_view LogicLensBotwMQDesc                       = "Removes the requirements for the Lens of Truth in\n"
                                                        "Bottom of the Well MQ.";                          //
string_view LogicLensGtgMQDesc                        = "Removes the requirements for the Lens of Truth in\n"
                                                        "Gerudo Training Grounds MQ.";                     //
string_view LogicLensCastleMQDesc                     = "Removes the requirements for the Lens of Truth in\n"
                                                        "Ganon's Castle MQ.";                              //
string_view LogicSpiritTrialHookshotDesc              = "A precise jump off of an Armos can collect the\n" //
                                                        "highest rupee.";                                  //
