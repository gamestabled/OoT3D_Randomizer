#include "setting_descriptions.hpp"

//Setting descriptions are mostly copied from OoT Randomizer tooltips with minor edits

/*------------------------------
|            LOGIC             |                           *SCREEN WIDTH*
------------------------------*/       /*--------------------------------------------------*/
std::string_view logicGlitchless      = "No glitches are required, but may require some\n" //
                                        "minor tricks. Add minor tricks to consider for\n" //
                                        "logic in Detailed Logic Settings.";               //
std::string_view logicNoLogic         = "Maximize randomization, All locations are\n"      //
                                        "considered available. MAY BE IMPOSSIBLE TO BEAT.";//
/*------------------------------                                                           //
|           FOREST             |                                                           //
------------------------------*/                                                           //
std::string_view forestOpen           = "Mido no longer blocks the path to the Deku Tree,\n"
                                        "and the Kokiri boy no longer blocks the path out\n"
                                        "of the forest.";                                  //
std::string_view forestClosed         = "Beating Deku Tree is logically required to leave\n"
                                        "the forest area (Kokiri Forest/Lost Woods/Sacred\n"
                                        "Forest Meadow/Deku Tree), while the Kokiri Sword\n"
                                        "and a Deku Shield are required to access the Deku\n"
                                        "Tree. Items needed for this will be guaranteed\n" //
                                        "inside the forest area. This setting is\n"        //
                                        "incompatible with starting as adult.";            //
/*------------------------------                                                           //
|        KAKARIKO GATE         |                                                           //
------------------------------*/                                                           //
std::string_view kakGateOpen          = "The gate is always open instead of needing\n"     //
                                        "Zelda's Letter. The Happy Mask Shop opens upon\n" //
                                        "obtaining Zelda's Letter without needing to show\n"
                                        "it to the guard.";                                //
std::string_view kakGateClosed        = "The gate and the Happy Mask Shop both remain\n"   //
                                        "closed until showing Zelda's Letter to the guard\n"
                                        "in Kakariko.";                                    //
/*------------------------------                                                           //
|        DOOR OF TIME          |                                                           //
------------------------------*/                                                           //
std::string_view doorOfTimeDesc       = "The Door of Time starts opened instead of needing\n"
                                        "to play the Song of Time. If closed, only an\n"   //
                                        "Ocarina and the Song of Time need to be found to\n"
                                        "open the Door of Time";                           //
/*------------------------------                                                           //
|       ZORA'S FOUNTAIN        |                                                           //
------------------------------*/                                                           //
std::string_view fountainNormal       = "King Zora obstructs the way to Zora's Fountain.\n"//
                                        "Ruto's Letter must be shown as child in order to\n"
                                        "move him for both eras.";                         //
std::string_view fountainOpen         = "King Zora starts as moved in both the child and\n"//
                                        "adult eras. This also removes Ruto's Letter from\n"
                                        "the pool since it can't be used.";                //
/*------------------------------                                                           //
|       GERUDO FORTRESS        |                                                           //
------------------------------*/                                                           //
std::string_view gerudoNormal         = "All 4 carpenters can be rescued.";                //
std::string_view gerudoFast           = "Only the bottom left carpenter must be rescued."; //
std::string_view gerudoOpen           = "The carpenters are rescued from the start of the\n"
                                        "game, and if Shuffle Gerudo Card is disabled,\n"  //
                                        "the player starts with the Gerudo Card in the\n"  //
                                        "inventory allowing access to Gerudo Training\n"   //
                                        "Grounds.";                                        //
/*------------------------------                                                           //
|        RAINBOW BRIDGE        |                                                           //
------------------------------*/                                                           //
std::string_view bridgeOpen           = "The Rainbow Bridge is always present.";           //
std::string_view bridgeVanilla        = "The Rainbow Bridge requires Shadow and Spirit\n"  //
                                        "Medallions.";                                     //
std::string_view bridgeStones         = "The Rainbow Bridge requires the Kokiri's Emerald,\n"
                                        "Goron's Ruby and Zora's Sapphire.";               //
std::string_view bridgeMedallions     = "The Rainbow Bridge requires Forest, Fire, Water,\n"
                                        "Shadow, Spirit, and Light Medallions";            //
std::string_view bridgeDungeons       = "The Rainbow Bridge requires beating every dungeon.";
                                                                                           //
/*------------------------------                                                           //
|         STARTING AGE         |                                                           //
------------------------------*/                                                           //
std::string_view ageDesc              = "Choose which age Link will start as.\n"           //
                                        "\n"                                               //
                                        "Starting as adult means you start with the Master\n"
                                        "Sword in your inventory.\n"                       //
                                        "\n"                                               //
                                        "Only the child option is compatible with Closed\n"//
                                        "Forest.";                                         //
/*------------------------------                                                           //
|      BOMBCHUS IN LOGIC       |                                                           //
------------------------------*/                                                           //
std::string_view bombchuLogicDesc     = "Bombchus are properly considered in logic and\n"  //
                                        "bombchu drops can appear similar to bomb drops.\n"//
                                        "\n"                                               //
                                        "Bombchu Bowling is opened by bombchus.";          //
/*------------------------------                                                           //
|      RANDOM MQ DUNGEONS      |                                                           //
------------------------------*/                                                           //
std::string_view randomMQDungeonsDesc = "If set, a random number of dungeons will have\n"  //
                                        "Master Quest designs";                            //
                                                                                           //
/*------------------------------                                                           //
|         SONG SHUFFLE         |                                                           //
------------------------------*/                                                           //
std::string_view songsSongLocations   = "Songs will only appear at locations that normally\n"
                                        "teach songs.";                                    //
std::string_view songsAllLocations    = "Songs can appear in any location.";               //
                                                                                           //
/*------------------------------                                                           //
|         TOKENSANITY          |                                                           //
------------------------------*/                                                           //
std::string_view tokensVanilla        = "Gold Skulltula Tokens will appear after defeating\n"
                                        "Gold Skulltulas.";                                //
std::string_view tokensAllLocations   = "Gold Skulltula Tokens can appear anywhere.";      //
                                                                                           //
/*------------------------------                                                           //
|        SCRUB SHUFFLE         |                                                           //
------------------------------*/                                                           //
std::string_view scrubsOff            = "Only the 3 Scrubs that give one-time items in the\n"
                                        "vanilla game (PoH, Deku Nut capacity, and Deku\n" //
                                        "Stick capacity) will have random items.";         //
std::string_view scrubsAffordable     = "All Scrub prices will be reduced to 10 rupees each";
std::string_view scrubsExpensive      = "All Scrub prices will be their vanilla prices.\n" //
                                        "This will require spending over 1000 rupees on\n" //
                                        "Scrubs.";                                         //
std::string_view scrubsRandomPrices   = "All Scrub prices will be between 0-99 rupees. This"
                                        "will on average be very, very expensive overall.";//
/*------------------------------                                                           //
|     SHUFFLE KOKIRI SWORD     |                                                           //
------------------------------*/                                                           //
std::string_view kokiriSwordDesc      = "Enabling this shuffles the Kokiri Sword into the\n"
                                        "item pool.\n"                                     //
                                        "\n"                                               //
                                        "This will require extensive use of sticks until\n"//
                                        "the sword is found.";                             //
/*------------------------------                                                           //
|       SHUFFLE OCARINAS       |                                                           //
------------------------------*/                                                           //
std::string_view ocarinasDesc         = "Enabling this shuffles the Fairy Ocarina and the\n"
                                        "Ocarina of Time into the item pool.\n"            //
                                        "\n"                                               //
                                        "This will require finding an Ocarina before being\n"
                                        "able to play songs.";                             //
/*------------------------------                                                           //
|      SHUFFLE WEIRD EGG       |                                                           //
------------------------------*/                                                           //
std::string_view weirdEggDesc         = "Enabling this shuffles the Weird Egg from Malon\n"//
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
std::string_view gerudoTokenDesc      = "Enabling this shuffles the Gerudo Token into the\n"
                                        "item pool.\n"                                     //
                                        "\n"                                               //
                                        "The Gerudo Token is required to enter the Gerudo\n"
                                        "Training Ground.";                                //
/*------------------------------                                                           //
|      SHUFFLE MAGIC BEANS     |                                                           //
------------------------------*/                                                           //
std::string_view magicBeansDesc       = "Enabling this adds a pack of 10 beans to the item\n"
                                        "pool and changes the Magic Bean Salesman to sell a"
                                        "random item at a price of 10 rupees.";            //
/*------------------------------                                                           //
|      MAPS AND COMPASSES      |                                                           //
------------------------------*/                                                           //
std::string_view mapCompassStartWith  = "Maps and Compasses are given to you from the\n"   //
                                        "start. This will add a small amount of money and\n"
                                        "refill items to the pool.";                       //
std::string_view mapCompassVanilla    = "Maps and Compasses will appear in their vanilla\n"//
                                        "locations.";                                      //
std::string_view mapCompassOwnDungeon = "Maps and Compasses can only appear in their\n"    //
                                        "respective dungeon.";                             //
std::string_view mapCompassAnywhere   = "Maps and Compasses can appear anywhere in th\n"   //
                                        "world.";                                          //
/*------------------------------                                                           //
|         SMALL KEYS           |                                                           //
------------------------------*/                                                           //
std::string_view smallKeyVanilla      = "Small Keys will appear in their vanilla locations."
                                        "You start with 3 keys in Spirit Temple MQ because\n"
                                        "the vanilla key layout is not beatable in logic.";//
std::string_view smallKeyOwnDungeon   = "Small Keys can only appear in their respective\n" //
                                        "dungeon. If Fire Temple is not a Master Quest\n"  //
                                        "dungeon, the door to the Boss Key chest will be\n"//
                                        "unlocked.";                                       //
std::string_view smallKeyAnywhere     = "Small Keys can appear anywhere in the world. A\n" //
                                        "difficult mode since it is more likely to need to\n"
                                        "enter a dungeon multiple times.";                 //
/*------------------------------                                                           //
|          BOSS KEYS           |                                                           //
------------------------------*/                                                           //
std::string_view bossKeyVanilla       = "Boss Keys will appear in their vanilla locations.";
std::string_view bossKeyOwnDungeon    = "Boss Keys can only appear in their respective\n"  //
                                        "dungeon.";                                        //
std::string_view bossKeyAnywhere      = "Boss Keys can appear anywhere in the world. A\n"  //
                                        "difficult mode since it is more likely to need to\n"
                                        "enter a dungeon multiple times.";                 //
/*------------------------------                                                           //
|   GANON'S CASTLE BOSS KEY    |                                                           //
------------------------------*/                                                           //
std::string_view ganonKeyVanilla      = "Ganon's Castle Boss Key will appear in the vanilla"
                                        "location.";                                       //
std::string_view ganonKeyOwnDungeon   = "Ganon's Castle Boss Key can only appear inside\n" //
                                        "Ganon's Castle.";                                 //
std::string_view ganonKeyAnywhere     = "Ganon's Castle Boss Key can appear anywhere in the"
                                        "world.";                                          //
std::string_view ganonKeyLACS         = "These settings put the boss key on the Light Arrow"
                                        "Cutscene location, from Zelda in Temple of Time as"
                                        "adult, with differing requirements.";             //
/*------------------------------                                                           //
|      SKIP CHILD STEALTH      |                                                           //
------------------------------*/                                                           //
std::string_view childStealthDesc     = "The crawlspace into Hyrule Castle goes straight to"
                                        "Zelda, skipping the guards.";                     //
/*------------------------------                                                           //
|      FOUR POES CUTSCENE      |                                                           //
------------------------------*/                                                           //
std::string_view fourPoesDesc         = "The cutscene with the 4 poes in Forest Temple will"
                                        "be skipped. If the cutscene is not skipped, it can"
                                        "be exploited to reach the basement early.";       //
/*------------------------------                                                           //
|       DAMAGE MULTIPLIER      |                                                           //
------------------------------*/                                                           //
std::string_view damageMultiDesc      = "Changes the amount of damage taken.\n"            //
                                        "\n"                                               //
                                        "If set to OHKO, Link will die in one hit.";       //
/*------------------------------                                                           //
|        STARTING TIME         |                                                           //
------------------------------*/                                                           //
std::string_view startingTimeDesc     = "Change up Link's sleep routine.";                 //
                                                                                           //
/*------------------------------                                                           //
|          ITEM POOL           |                                                           //
------------------------------*/                                                           //
std::string_view itemPoolPlentiful = "Extra major items are added to the pool.";           //
std::string_view itemPoolBalanced  = "Original item pool.";                                //
std::string_view itemPoolScarce    = "Some excess items are removed, including health\n"   //
                                     "upgrades.";                                          //
std::string_view itemPoolMinimal   = "Most excess items are removed.";                     //
                                                                                           //
/*------------------------------                                                           //
|    ENABLE ADULT BOOMERANG    |                                                           //
------------------------------*/                                                           //
std::string_view adultBoomerangDesc   = "Adult Link can throw the boomerang.";             //
                                                                                           //
/*------------------------------                                                           //
|     ENABLE CHILD HAMMER      |                                                           //
------------------------------*/                                                           //
std::string_view childHammerDesc      = "Child Link can swing the Megaton Hammer.";        //
