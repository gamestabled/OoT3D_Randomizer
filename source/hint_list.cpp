#include "hint_list.hpp"

namespace Hints {

  //Text is {english, french, spanish}

  // there are special characters that are read for certain in game commands:
  // ^ is a box break
  // & is a new line
  // @ will print the player name
  // surrounding text with '#' will make it a different color
  // - OoT Randomizer

  HintText NoHintText   = HintText::Exclude({Text{"","",""}});
  HintText Prefix       = HintText::Exclude({Text{"They say that ", "", ""}});
  HintText WayOfTheHero = HintText::Exclude({Text{" is on the way of the hero.",  "", ""}});
  HintText Plundering   = HintText::Exclude({Text{"plundering ", "", ""}});
  HintText Foolish      = HintText::Exclude({Text{" is a foolish choice.", "", ""}});

  /*--------------------------
  |      ITEM HINT TEXT      |
  ---------------------------*/

  HintText TriforcePiece = HintText::Item({
                       //obscure text
                       Text{"a triumph fork",  "", ""},
                       Text{"cheese",          "", ""},
                       Text{"a gold fragment", "", ""},
                     },
                       //clear text
                       Text{"a Piece of the Triforce", "", ""}
  );

  HintText ProgressiveMagic = HintText::Item({
                       //obscure text
                       Text{"mystic training",    "", ""},
                       Text{"pixie dust",         "", ""},
                       Text{"a green reactangle", "", ""},
                     },
                       //clear text
                       Text{"a Magic Meter", "", ""}
  );

  HintText DoubleDefense = HintText::Item({
                       //obscure text
                       Text{"a white outline",   "", ""},
                       Text{"damage decrease",   "", ""},
                       Text{"strengthened love", "", ""},
                     },
                       //clear text
                       Text{"Double Defense", "", ""}
  );

  HintText ProgressiveBulletBag = HintText::Item({
                       //obscure text
                       Text{"a seed shooter",     "", ""},
                       Text{"a rubberband",       "", ""},
                       Text{"a child's catapult", "", ""},
                     },
                       //clear text
                       Text{"a Slingshot", "", ""}
  );

  HintText Boomerang = HintText::Item({
                       //obscure text
                       Text{"a banana",       "", ""},
                       Text{"a stun stick",   "", ""},
                       Text{"a yellow angle", "", ""},
                     },
                       //clear text
                       Text{"the Boomerang", "", ""}
  );

  HintText ProgressiveBow = HintText::Item({
                       //obscure text
                       Text{"an archery enabler",     "", ""},
                       Text{"a danger dart launcher", "", ""},
                     },
                       //clear text
                       Text{"a Bow", "", ""}
  );

  HintText ProgressiveBombBag = HintText::Item({
                       //obscure text
                       Text{"an explosive container", "", ""},
                       Text{"a blast bag", "", ""},
                     },
                       //clear text
                       Text{"a Bomb Bag", "", ""}
  );

  HintText ProgressiveHookshot = HintText::Item({
                       //obscure text
                       Text{"Dampe's keepsake", "", ""},
                       Text{"the Grapple Beam", "", ""},
                       Text{"the BOING! chain", "", ""},
                     },
                       //clear text
                       Text{"a Hookshot", "", ""}
  );

  HintText ProgressiveStrength = HintText::Item({
                       //obscure text
                       Text{"power gloves",    "", ""},
                       Text{"metal mittens",   "", ""},
                       Text{"the heavy lifty", "", ""},
                     },
                       //clear text
                       Text{"a Strength Upgrade", "", ""}
  );

  HintText ProgressiveScale = HintText::Item({
                       //obscure text
                       Text{"a deeper dive",   "", ""},
                       Text{"a piece of Zora", "", ""},
                     },
                       //clear text
                       Text{"a Zora Scale", "", ""}
  );

  HintText MegatonHammer = HintText::Item({
                       //obscure text
                       Text{"the dragon smasher", "", ""},
                       Text{"the metal mallet",   "", ""},
                       Text{"the heavy hitter",   "", ""},
                     },
                       //clear text
                       Text{"the Megaton Hammer", "", ""}
  );

  HintText IronBoots = HintText::Item({
                       //obscure text
                       Text{"sink shoes",   "", ""},
                       Text{"clank cleats", "", ""},
                     },
                       //clear text
                       Text{"the Iron Boots", "", ""}
  );

  HintText HoverBoots = HintText::Item({
                       //obscure text
                       Text{"butter boots",    "", ""},
                       Text{"sacred slippers", "", ""},
                       Text{"spacewalkers",    "", ""},
                     },
                       //clear text
                       Text{"the Hover Boots", "", ""}
  );

  HintText KokiriSword = HintText::Item({
                       //obscure text
                       Text{"a butter knife",    "", ""},
                       Text{"a starter slasher", "", ""},
                       Text{"a switchblade",     "", ""},
                     },
                       //clear text
                       Text{"the Kokiri Sword", "", ""}
  );

  HintText GiantsKnife = HintText::Item({
                       //obscure text
                       Text{"a fragile blade",     "", ""},
                       Text{"a breakable cleaver", "", ""},
                     },
                       //clear text
                       Text{"the Giant's Knife", "", ""}
  );

  HintText BiggoronSword = HintText::Item({
                       //obscure text
                       Text{"the biggest blade",  "", ""},
                       Text{"a colossal cleaver", "", ""},
                     },
                       //clear text
                       Text{"the Biggoron Sword", "", ""}
  );

  HintText MasterSword = HintText::Item({
                       //obscure text
                       Text{"evil's bane",        "", ""},
                       Text{"a seven year limbo", "", ""},
                     },
                       //clear text
                       Text{"the Master Sword", "", ""}
  );

  HintText DekuShield = HintText::Item({
                       //obscure text
                       Text{"a wooden ward",      "", ""},
                       Text{"a burnable barrier", "", ""},
                     },
                       //clear text
                       Text{"a Deku Shield", "", ""}
  );

  HintText HylianShield = HintText::Item({
                       //obscure text
                       Text{"a steel safeguard",      "", ""},
                       Text{"Like Like's metal meal", "", ""},
                     },
                       //clear text
                       Text{"a Hylian Shield", "", ""}
  );

  HintText MirrorShield = HintText::Item({
                       //obscure text
                       Text{"a reflective rampart", "", ""},
                       Text{"Medusa's weakness",    "", ""},
                       Text{"a silvered surface",   "", ""},
                     },
                       //clear text
                       Text{"the Mirror Shield", "", ""}
  );

  HintText FaroresWind = HintText::Item({
                       //obscure text
                       Text{"teleportation",     "", ""},
                       Text{"a relocation rune", "", ""},
                       Text{"a green ball",      "", ""},
                     },
                       //clear text
                       Text{"Farore's Wind", "", ""}
  );

  HintText NayrusLove = HintText::Item({
                       //obscure text
                       Text{"a safe space",        "", ""},
                       Text{"an impregnable aura", "", ""},
                       Text{"a blue barrier",      "", ""},
                     },
                       //clear text
                       Text{"Nayru's Love", "", ""}
  );

  HintText DinsFire = HintText::Item({
                       //obscure text
                       Text{"an inferno",  "", ""},
                       Text{"a heat wave", "", ""},
                       Text{"a red ball",  "", ""},
                     },
                       //clear text
                       Text{"Din's Fire", "", ""}
  );

  HintText FireArrows = HintText::Item({
                       //obscure text
                       Text{"the furnace firearm" , "", ""},
                       Text{"the burning bolts",    "", ""},
                       Text{"a magma missile",      "", ""},
                     },
                       //clear text
                       Text{"the Fire Arrows", "", ""}
  );

  HintText IceArrows = HintText::Item({
                       //obscure text
                       Text{"the refrigerator rocket", "", ""},
                       Text{"the frostbite bolts",     "", ""},
                       Text{"an iceberg maker",        "", ""},
                     },
                       //clear text
                       Text{"the Ice Arrows", "", ""}
  );

  HintText LightArrows = HintText::Item({
                       //obscure text
                       Text{"the shining shot",      "", ""},
                       Text{"the luminous launcher", "", ""},
                       Text{"Ganondorf's bane",      "", ""},
                       Text{"the lighting bolts",    "", ""},
                     },
                       //clear text
                       Text{"the Light Arrows", "", ""}
  );

  HintText LensOfTruth = HintText::Item({
                       //obscure text
                       Text{"a lie detector",     "", ""},
                       Text{"a ghost tracker",    "", ""},
                       Text{"true sight", "       ", ""},
                       Text{"a detective's tool", "", ""},
                     },
                       //clear text
                       Text{"the Lens of Truth", "", ""}
  );

  HintText ProgressiveOcarina = HintText::Item({
                       //obscure text
                       Text{"a flute",       "", ""},
                       Text{"a music maker", "", ""},
                     },
                       //clear text
                       Text{"an Ocarina", "", ""}
  );

  HintText GoronTunic = HintText::Item({
                       //obscure text
                       Text{"ruby robes",       "", ""},
                       Text{"fireproof fabric", "", ""},
                       Text{"cooking clothes",  "", ""},
                     },
                       //clear text
                       Text{"a Goron Tunic", "", ""}
  );

  HintText ZoraTunic = HintText::Item({
                       //obscure text
                       Text{"a sapphire suit", "", ""},
                       Text{"scuba gear",      "", ""},
                       Text{"a swimsuit",      "", ""},
                     },
                       //clear text
                       Text{"a Zora Tunic", "", ""}
  );

  HintText Epona = HintText::Item({
                       //obscure text
                       Text{"a horse",              "", ""},
                       Text{"a four legged friend", "", ""},
                     },
                       //clear text
                       Text{"Epona", "", ""}
  );

  HintText ZeldasLullaby = HintText::Item({
                       //obscure text
                       Text{"a song of royal slumber", "", ""},
                       Text{"a triforce tune",         "", ""},
                     },
                       //clear text
                       Text{"Zelda's Lullaby", "", ""}
  );

  HintText EponasSong = HintText::Item({
                       //obscure text
                       Text{"an equestrian etude", "", ""},
                       Text{"Malon's melody",      "", ""},
                       Text{"a ranch song",        "", ""},
                     },
                       //clear text
                       Text{"Epona's Song", "", ""}
  );

  HintText SariasSong = HintText::Item({
                       //obscure text
                       Text{"a song of dancing Gorons", "", ""},
                       Text{"Saria's phone number",     "", ""},
                     },
                       //clear text
                       Text{"Saria's Song", "", ""}
  );

  HintText SunsSong = HintText::Item({
                       //obscure text
                       Text{"Sunny Day",         "", ""},
                       Text{"the ReDead's bane", "", ""},
                       Text{"the Gibdo's bane",  "", ""},
                     },
                       //clear text
                       Text{"the Sun's Song", "", ""}
  );

  HintText SongOfTime = HintText::Item({
                       //obscure text
                       Text{"a song 7 years long", "", ""},
                       Text{"the tune of ages",    "", ""},
                     },
                       //clear text
                       Text{"the Song of Time", "", ""}
  );

  HintText SongOfStorms = HintText::Item({
                       //obscure text
                       Text{"Rain Dance",            "", ""},
                       Text{"a thunderstorm tune",   "", ""},
                       Text{"windmill acceleration", "", ""},
                     },
                       //clear text
                       Text{"the Song of Storms", "", ""}
  );

  HintText MinuetOfForest = HintText::Item({
                       //obscure text
                       Text{"the song of tall trees", "", ""},
                       Text{"an arboreal anthem",     "", ""},
                       Text{"a green spark trail",    "", ""},
                     },
                       //clear text
                       Text{"the Minuet of Forest", "", ""}
  );

  HintText BoleroOfFire = HintText::Item({
                       //obscure text
                       Text{"a song of lethal lava", "", ""},
                       Text{"a red spark trail",     "", ""},
                       Text{"a volcanic verse",      "", ""},
                     },
                       //clear text
                       Text{"the Bolero of Fire", "", ""}
  );

  HintText SerenadeOfWater = HintText::Item({
                       //obscure text
                       Text{"a song of a damp ditch", "", ""},
                       Text{"a blue spark trail",     "", ""},
                       Text{"the lake's lyric",       "", ""},
                     },
                       //clear text
                       Text{"the Serenade of Water", "", ""}
  );

  HintText RequiemOfSpirit = HintText::Item({
                       //obscure text
                       Text{"a song of sandy statues", "", ""},
                       Text{"an orange spark trail",   "", ""},
                       Text{"the desert ditty",        "", ""},
                     },
                       //clear text
                       Text{"the Requiem of Spirit", "", ""}
  );

  HintText NocturneOfShadow = HintText::Item({
                       //obscure text
                       Text{"a song of spooky spirits", "", ""},
                       Text{"a graveyard boogie",       "", ""},
                       Text{"a haunted hymn",           "", ""},
                       Text{"a purple spark trail",     "", ""},
                     },
                       //clear text
                       Text{"the Nocturne of Shadow", "", ""}
  );

  HintText PreludeOfLight = HintText::Item({
                       //obscure text
                       Text{"a luminous prologue melody", "", ""},
                       Text{"a yellow spark trail",       "", ""},
                       Text{"the temple traveler",        "", ""},
                     },
                       //clear text
                       Text{"the Prelude of Light", "", ""}
  );

  HintText EmptyBottle = HintText::Item({
                       //obscure text
                       Text{"a glass container", "", ""},
                       Text{"an empty jar",      "", ""},
                       Text{"encased air",       "", ""},
                     },
                       //clear text
                       Text{"a Bottle", "", ""}
  );

  HintText RutosLetter = HintText::Item({
                       //obscure text
                       Text{"a call for help",      "", ""},
                       Text{"the note that Mweeps", "", ""},
                       Text{"an SOS call",          "", ""},
                       Text{"a fishy stationery",   "", ""},
                     },
                       //clear text
                       Text{"Ruto's Letter", "", ""}
  );

  HintText BottleWithMilk = HintText::Item({
                       //obscure text
                       Text{"cow juice",          "", ""},
                       Text{"a white liquid",     "", ""},
                       Text{"a baby's breakfast", "", ""},
                     },
                       //clear text
                       Text{"a Milk Bottle", "", ""}
  );

  HintText BottleWithRedPotion = HintText::Item({
                       //obscure text
                       Text{"a vitality vial", "", ""},
                       Text{"a red liquid",    "", ""},
                     },
                       //clear text
                       Text{"a Red Potion Bottle", "", ""}
  );

  HintText BottleWithGreenPotion = HintText::Item({
                       //obscure text
                       Text{"a magic mixture", "", ""},
                       Text{"a green liquid",  "", ""},
                     },
                       //clear text
                       Text{"a Green Potion Bottle", "", ""}
  );

  HintText BottleWithBluePotion = HintText::Item({
                       //obscure text
                       Text{"an ailment antidote", "", ""},
                       Text{"a blue liquid",       "", ""},
                     },
                       //clear text
                       Text{"a Blue Potion Bottle", "", ""}
  );

  HintText BottleWithFairy = HintText::Item({
                       //obscure text
                       Text{"an imprisoned fairy", "", ""},
                       Text{"an extra life",       "", ""},
                       Text{"Navi's cousin",       "", ""},
                     },
                       //clear text
                       Text{"a Fairy Bottle", "", ""}
  );

  HintText BottleWithFish = HintText::Item({
                       //obscure text
                       Text{"an aquarium",     "", ""},
                       Text{"a deity's snack", "", ""},
                     },
                       //clear text
                       Text{"a Fish Bottle", "", ""}
  );

  HintText BottleWithBlueFire = HintText::Item({
                       //obscure text
                       Text{"a conflagration canteen", "", ""},
                       Text{"an icemelt jar",          "", ""},
                     },
                       //clear text
                       Text{"a Blue Fire Bottle", "", ""}
  );

  HintText BottleWithBugs = HintText::Item({
                       //obscure text
                       Text{"an insectarium",    "", ""},
                       Text{"Skulltula finders", "", ""},
                     },
                       //clear text
                       Text{"a Bug Bottle", "", ""}
  );

  HintText BottleWithPoe = HintText::Item({
                       //obscure text
                       Text{"a spooky ghost",    "", ""},
                       Text{"a face in the jar", "", ""},
                     },
                       //clear text
                       Text{"a Poe Bottle", "", ""}
  );

  HintText BottleWithBigPoe = HintText::Item({
                       //obscure text
                       Text{"the spookiest ghost", "", ""},
                       Text{"a sidequest spirit",  "", ""},
                     },
                       //clear text
                       Text{"a Big Poe Bottle", "", ""}
  );

  HintText ShardOfAgony = HintText::Item({
                       //obscure text
                       Text{"the shake shard", "", ""},
                       Text{"a blue alarm",    "", ""},
                     },
                       //clear text
                       Text{"the Shard of Agony", "", ""}
  );

  HintText GerudoToken = HintText::Item({
                       //obscure text
                       Text{"a girl club membership", "", ""},
                       Text{"a desert tribe's pass",  "", ""},
                     },
                       //clear text
                       Text{"the Gerudo Token", "", ""}
  );

  HintText ProgressiveWallet = HintText::Item({
                       //obscure text
                       Text{"a mo' money holder", "", ""},
                       Text{"a gem purse",        "", ""},
                       Text{"a portable bank",    "", ""},
                     },
                       //clear text
                       Text{"a Wallet", "", ""}
  );

  HintText ProgressiveStickCapacity = HintText::Item({
                       //obscure text
                       Text{"a lumber rack",        "", ""},
                       Text{"more flammable twigs", "", ""},
                     },
                       //clear text
                       Text{"Deku Stick Capacity", "", ""}
  );

  HintText ProgressiveNutCapacity = HintText::Item({
                       //obscure text
                       Text{"more nuts",         "", ""},
                       Text{"flashbang storage", "", ""},
                     },
                       //clear text
                       Text{"Deku Nut Capacity", "", ""}
  );

  HintText HeartContainer = HintText::Item({
                       //obscure text
                       Text{"a lot of love",      "", ""},
                       Text{"a Valentine's gift", "", ""},
                       Text{"a boss's organ",     "", ""},
                     },
                       //clear text
                       Text{"a Heart Container", "", ""}
  );

  HintText PieceOfHeart = HintText::Item({
                       //obscure text
                       Text{"a little love",  "", ""},
                       Text{"a broken heart", "", ""},
                     },
                       //clear text
                       Text{"a Piece of Heart", "", ""}
  );

  HintText TreasureGameHeart = HintText::Item({
                       //obscure text
                       Text{"a victory valentine", "", ""},
                     },
                       //clear text
                       Text{"a Piece of Heart", "", ""}
  );

  HintText RecoveryHeart = HintText::Item({
                       //obscure text
                       Text{"a free heal",   "", ""},
                       Text{"a hearty meal", "", ""},
                       Text{"a Band-Aid",    "", ""},
                     },
                       //clear text
                       Text{"a Recovery Heart", "", ""}
  );

  HintText TreasureGameGreenRupee = HintText::Item({
                       //obscure text
                       Text{"the dollar of defeat", "", ""},
                     },
                       //clear text
                       Text{"a Green Rupee", "", ""}
  );

  HintText DekuStick1 = HintText::Item({
                       //obscure text
                       Text{"a breakable branch", "", ""},
                     },
                       //clear text
                       Text{"a Deku Stick", "", ""}
  );

  HintText GreenRupee = HintText::Item({
                       //obscure text
                       Text{"a unique coin", "", ""},
                       Text{"a penny",       "", ""},
                       Text{"a green gem",   "", ""},
                     },
                       //clear text
                       Text{"a Green Rupee", "", ""}
  );

  HintText BlueRupee = HintText::Item({
                       //obscure text
                       Text{"a common coin", "", ""},
                       Text{"a blue gem",    "", ""},
                     },
                       //clear text
                       Text{"a Blue Rupee", "", ""}
  );

  HintText RedRupee = HintText::Item({
                       //obscure text
                       Text{"couch cash", "", ""},
                       Text{"a red gem",  "", ""},
                     },
                       //clear text
                       Text{"a Red Rupee", "", ""}
  );

  HintText PurpleRupee = HintText::Item({
                       //obscure text
                       Text{"big bucks",    "", ""},
                       Text{"a purple gem", "", ""},
                       Text{"wealth",       "", ""},
                     },
                       //clear text
                       Text{"a Purple Rupee", "", ""}
  );

  HintText HugeRupee = HintText::Item({
                       //obscure text
                       Text{"a juicy jackpot", "", ""},
                       Text{"a yellow gem",    "", ""},
                       Text{"a giant gem",     "", ""},
                       Text{"great wealth",    "", ""},
                     },
                       //clear text
                       Text{"a Huge Rupee", "", ""}
  );

  HintText WeirdEgg = HintText::Item({
                       //obscure text
                       Text{"a chicken dilemma", "", ""},
                     },
                       //clear text
                       Text{"the Weird Egg", "", ""}
  );

  HintText ZeldasLetter = HintText::Item({
                       //obscure text
                       Text{"an autograph",     "", ""},
                       Text{"royal stationery", "", ""},
                       Text{"royal snail mail", "", ""},
                     },
                       //clear text
                       Text{"Zelda's Letter", "", ""}
  );

  HintText PocketEgg = HintText::Item({
                       //obscure text
                       Text{"a Cucco container",   "", ""},
                       Text{"a Cucco, eventually", "", ""},
                       Text{"a fowl youth",        "", ""},
                     },
                       //clear text
                       Text{"the Pocket Egg", "", ""}
  );

  HintText PocketCucco = HintText::Item({
                       //obscure text
                       Text{"a little clucker", "", ""},
                     },
                       //clear text
                       Text{"the Pocket Cucco", "", ""}
  );

  HintText Cojiro = HintText::Item({
                       //obscure text
                       Text{"a cerulean capon", "", ""},
                     },
                       //clear text
                       Text{"Cojiro", "", ""}
  );

  HintText OddMushroom = HintText::Item({
                       //obscure text
                       Text{"a powder ingredient", "", ""},
                     },
                       //clear text
                       Text{"an Odd Mushroom", "", ""}
  );

  HintText OddPoultice = HintText::Item({
                       //obscure text
                       Text{"Granny's goodies", "", ""},
                     },
                       //clear text
                       Text{"an Odd Potion", "", ""}
  );

  HintText PoachersSaw = HintText::Item({
                       //obscure text
                       Text{"a tree killer", "", ""},
                     },
                       //clear text
                       Text{"the Poacher's Saw", "", ""}
  );

  HintText BrokenSword = HintText::Item({
                       //obscure text
                       Text{"a shattered slicer", "", ""},
                     },
                       //clear text
                       Text{"the Broken Sword", "", ""}
  );

  HintText Prescription = HintText::Item({
                       //obscure text
                       Text{"a pill pamphlet", "", ""},
                       Text{"a doctor's note", "", ""},
                     },
                       //clear text
                       Text{"the Prescription", "", ""}
  );

  HintText EyeballFrog = HintText::Item({
                       //obscure text
                       Text{"a perceiving polliwog", "", ""},
                     },
                       //clear text
                       Text{"the Eyeball Frog", "", ""}
  );

  HintText Eyedrops = HintText::Item({
                       //obscure text
                       Text{"a vision vial", "", ""},
                     },
                       //clear text
                       Text{"the Eyedrops", "", ""}
  );

  HintText ClaimCheck = HintText::Item({
                       //obscure text
                       Text{"a three day wait", "", ""},
                     },
                       //clear text
                       Text{"the Claim Check", "", ""}
  );

  HintText Map = HintText::Item({
                       //obscure text
                       Text{"a dungeon atlas", "", ""},
                       Text{"blueprints",      "", ""},
                     },
                       //clear text
                       Text{"a Map", "", ""}
  );

  HintText Compass = HintText::Item({
                       //obscure text
                       Text{"a treasure tracker", "", ""},
                       Text{"a magnetic needle",  "", ""},
                     },
                       //clear text
                       Text{"a Compass", "", ""}
  );

  HintText BossKey = HintText::Item({
                       //obscure text
                       Text{"a master of unlocking",   "", ""},
                       Text{"a dungeon's master pass", "", ""},
                     },
                       //clear text
                       Text{"a Boss Key", "", ""}
  );

  HintText GanonsBossKey = HintText::Item({
                       //obscure text
                       Text{"a master of unlocking",   "", ""},
                       Text{"a dungeon's master pass", "", ""},
                     },
                       //clear text
                       Text{"a Boss Key", "", ""}
  );

  HintText SmallKey = HintText::Item({
                       //obscure text
                       Text{"a tool for unlocking", "", ""},
                       Text{"a dungeon pass",       "", ""},
                       Text{"a lock remover",       "", ""},
                       Text{"a lockpick",           "", ""},
                     },
                       //clear text
                       Text{"a Small Key", "", ""}
  );

  HintText FortressSmallKey = HintText::Item({
                       //obscure text
                       Text{"a get out of jail free card", "", ""},
                     },
                       //clear text
                       Text{"a Jail Key", "", ""}
  );

  HintText KokiriEmerald = HintText::Item({
                       //obscure text
                       Text{"a green stone", "", ""},
                       Text{"a gift before death",  "", ""},
                     },
                       //clear text
                       Text{"the Kokiri Emerald", "", ""}
  );

  HintText GoronRuby = HintText::Item({
                       //obscure text
                       Text{"a red stone", "", ""},
                       Text{"sworn brotherhood",  "", ""},
                     },
                       //clear text
                       Text{"the Goron Ruby", "", ""}
  );

  HintText ZoraSapphire = HintText::Item({
                       //obscure text
                       Text{"a blue stone", "", ""},
                       Text{"an engagement gift",  "", ""},
                     },
                       //clear text
                       Text{"the Zora Sapphire", "", ""}
  );

  HintText ForestMedallion = HintText::Item({
                       //obscure text
                       Text{"a green coin", "", ""},
                       Text{"Saria's friendship",  "", ""},
                     },
                       //clear text
                       Text{"the Forest Medallion", "", ""}
  );

  HintText FireMedallion = HintText::Item({
                       //obscure text
                       Text{"a red coin", "", ""},
                       Text{"Darunia's power",  "", ""},
                     },
                       //clear text
                       Text{"the Fire Medallion", "", ""}
  );

  HintText WaterMedallion = HintText::Item({
                       //obscure text
                       Text{"a blue coin", "", ""},
                       Text{"Ruto's power",  "", ""},
                     },
                       //clear text
                       Text{"the Water Medallion", "", ""}
  );

  HintText SpiritMedallion = HintText::Item({
                       //obscure text
                       Text{"an orange coin", "", ""},
                       Text{"Nabooru's power",  "", ""},
                     },
                       //clear text
                       Text{"the Spirit Medallion", "", ""}
  );

  HintText ShadowMedallion = HintText::Item({
                       //obscure text
                       Text{"a purple coin", "", ""},
                       Text{"Impa's power",  "", ""},
                     },
                       //clear text
                       Text{"the Shadow Medallion", "", ""}
  );

  HintText LightMedallion = HintText::Item({
                       //obscure text
                       Text{"a yellow coin", "", ""},
                       Text{"Rauru's power",  "", ""},
                     },
                       //clear text
                       Text{"the Light Medallion", "", ""}
  );

  // HintText HintError = HintText::Item({
  //                      //obscure text
  //                      Text{"something mysterious", "", ""},
  //                      Text{"an unknown treasure",  "", ""},
  //                    },
  //                      //clear text
  //                      Text{"An Error (Please Report This)", "", ""}
  // );

  HintText Arrows5 = HintText::Item({
                       //obscure text
                       Text{"a few danger darts", "", ""},
                       Text{"a few sharp shafts", "", ""},
                     },
                       //clear text
                       Text{"Arrows (5 pieces)", "", ""}
  );

  HintText Arrows10 = HintText::Item({
                       //obscure text
                       Text{"some danger darts", "", ""},
                       Text{"some sharp shafts", "", ""},
                     },
                       //clear text
                       Text{"Arrows (10 pieces)", "", ""}
  );

  HintText Arrows30 = HintText::Item({
                       //obscure text
                       Text{"plenty of danger darts", "", ""},
                       Text{"plenty of sharp shafts", "", ""},
                     },
                       //clear text
                       Text{"Arrows (30 pieces)", "", ""}
  );

  HintText Bombs5 = HintText::Item({
                       //obscure text
                       Text{"a few explosives",  "", ""},
                       Text{"a few blast balls", "", ""},
                     },
                       //clear text
                       Text{"Bombs (5 pieces)", "", ""}
  );

  HintText Bombs10 = HintText::Item({
                       //obscure text
                       Text{"some explosives",  "", ""},
                       Text{"some blast balls", "", ""},
                     },
                       //clear text
                       Text{"Bombs (10 pieces)", "", ""}
  );

  HintText Bombs20 = HintText::Item({
                       //obscure text
                       Text{"lots-o-explosives",     "", ""},
                       Text{"plenty of blast balls", "", ""},
                     },
                       //clear text
                       Text{"Bombs (20 pieces)", "", ""}
  );

  HintText IceTrap = HintText::Item({
                       //obscure text
                       Text{"a gift from Ganon",    "", ""},
                       Text{"a chilling discovery", "", ""},
                       Text{"frosty fun", "", ""},
                     },
                       //clear text
                       Text{"an Ice Trap", "", ""}
  );

  HintText MagicBean = HintText::Item({
                       //obscure text
                       Text{"a wizardly legume", "", ""},
                     },
                       //clear text
                       Text{"a Magic Bean", "", ""}
  );

  HintText MagicBeanPack = HintText::Item({
                       //obscure text
                       Text{"wizardly legumes", "", ""},
                     },
                       //clear text
                       Text{"Magic Beans", "", ""}
  );

  HintText ProgressiveBombchus = HintText::Item({
                       //obscure text
                       Text{"mice bombs",     "", ""},
                       Text{"proximity mice", "", ""},
                       Text{"wall crawlers",  "", ""},
                       Text{"trail blazers",  "", ""},
                     },
                       //clear text
                       Text{"Bombchus", "", ""}
  );

  HintText Bombchus5 = HintText::Item({
                       //obscure text
                       Text{"a few mice bombs",     "", ""},
                       Text{"a few proximity mice", "", ""},
                       Text{"a few wall crawlers",  "", ""},
                       Text{"a few trail blazers",  "", ""},
                     },
                       //clear text
                       Text{"Bombchus (5 pieces)", "", ""}
  );

  HintText Bombchus10 = HintText::Item({
                       //obscure text
                       Text{"some mice bombs",     "", ""},
                       Text{"some proximity mice", "", ""},
                       Text{"some wall crawlers",  "", ""},
                       Text{"some trail blazers",  "", ""},
                     },
                       //clear text
                       Text{"Bombchus (10 pieces)", "", ""}
  );

  HintText Bombchus20 = HintText::Item({
                       //obscure text
                       Text{"plenty of mice bombs",     "", ""},
                       Text{"plenty of proximity mice", "", ""},
                       Text{"plenty of wall crawlers",  "", ""},
                       Text{"plenty of trail blazers",  "", ""},
                     },
                       //clear text
                       Text{"Bombchus (20 pieces)", "", ""}
  );

  HintText DekuNuts5 = HintText::Item({
                       //obscure text
                       Text{"some nuts",       "", ""},
                       Text{"some flashbangs", "", ""},
                       Text{"some scrub spit", "", ""},
                     },
                       //clear text
                       Text{"Deku Nuts (5 pieces)", "", ""}
  );

  HintText DekuNuts10 = HintText::Item({
                       //obscure text
                       Text{"lots-o-nuts",          "", ""},
                       Text{"plenty of flashbangs", "", ""},
                       Text{"plenty of scrub spit", "", ""},
                     },
                       //clear text
                       Text{"Deku Nuts (10 pieces)", "", ""}
  );

  HintText DekuSeeds30 = HintText::Item({
                       //obscure text
                       Text{"catapult ammo", "", ""},
                       Text{"lots-o-seeds",  "", ""},
                     },
                       //clear text
                       Text{"Deku Seeds (30 pieces)", "", ""}
  );

  HintText GoldSkulltulaToken = HintText::Item({
                       //obscure text
                       Text{"proof of destruction",   "", ""},
                       Text{"an arachnid chip",       "", ""},
                       Text{"spider remains",         "", ""},
                       Text{"one percent of a curse", "", ""},
                     },
                       //clear text
                       Text{"a Gold Skulltula Token", "", ""}
  );

  /*--------------------------
  |     ALWAYS HINT TEXT     |
  ---------------------------*/

  HintText ZR_FrogsOcarinaGame = HintText::Always({
                       //obscure text
                       Text{"an #amphibian feast# yields",               "", ""},
                       Text{"the #croaking choir's magnum opus# awards", "", ""},
                       Text{"the #froggy finale# yields",                "", ""},
                     },
                       //clear text
                       Text{"the final reward from the #Frogs of Zora's River# is", "", ""}
  );

  HintText KF_LinksHouseCow = HintText::Always({
                       //obscure text
                       Text{"the #bovine bounty of a horseback hustle# gifts", "", ""},
                     },
                       //clear text
                       Text{"#Malon's obstacle course# leads to", "", ""}
  );

  /*--------------------------
  |    SOMETIMES HINT TEXT   |
  ---------------------------*/

  HintText SongFromOcarinaOfTime = HintText::Sometimes({
                       //obscure text
                       Text{"the #Ocarina of Time# teaches", "", ""},
  });

  HintText SongFromComposersGrave = HintText::Sometimes({
                       //obscure text
                       Text{"#ReDead in the Composers' Grave# guard", "", ""},
                       Text{"the #Composer Brothers wrote#",          "", ""},
  });

  HintText SheikInForest = HintText::Sometimes({
                       //obscure text
                       Text{"#in a meadow# Sheik teaches", "", ""},
  });

  HintText SheikAtTemple = HintText::Sometimes({
                       //obscure text
                       Text{"Sheik waits at a #monument to time# to teach", "", ""},
  });

  HintText SheikInCrater = HintText::Sometimes({
                       //obscure text
                       Text{"the #crater's melody# is", "", ""},
  });

  HintText SheikInIceCavern = HintText::Sometimes({
                       //obscure text
                       Text{"the #frozen cavern# echoes with", "", ""},
  });

  HintText SheikInKakariko = HintText::Sometimes({
                       //obscure text
                       Text{"a #ravaged village# mourns with", "", ""},
  });

  HintText SheikAtColossus = HintText::Sometimes({
                       //obscure text
                       Text{"a hero ventures #beyond the wasteland# to learn", "", ""},
  });


  HintText MK_10BigPoes = HintText::Sometimes({
                       //obscure text
                       Text{"#ghost hunters# will be rewarded with", "", ""},
                     },
                       //clear text
                       Text{"catching #Big Poes# leads to", "", ""}
  );

  HintText DekuTheater_SkullMask = HintText::Sometimes({
                       //obscure text
                       Text{"the #Skull Mask# yields", "", ""},
  });

  HintText DekuTheater_MaskOfTruth = HintText::Sometimes({
                       //obscure text
                       Text{"showing a #truthful eye to the crowd# rewards", "", ""},
                     },
                       //clear text
                       Text{"the #Mask of Truth# yields", "", ""}
  );

  HintText HF_OcarinaOfTimeItem = HintText::Sometimes({
                       //obscure text
                       Text{"the #treasure thrown by Princess Zelda# is", "", ""},
  });

  HintText DMT_Biggoron = HintText::Sometimes({
                       //obscure text
                       Text{"#Biggoron# crafts", "", ""},
  });

  HintText Kak_50GoldSkulltulaReward = HintText::Sometimes({
                       //obscure text
                       Text{"#50 bug badges# rewards",           "", ""},
                       Text{"#50 spider souls# yields",          "", ""},
                       Text{"#50 auriferous arachnids# lead to", "", ""},
                     },
                       //clear text
                       Text{"slaying #50 Gold Skulltulas# reveals", "", ""}
  );

  HintText Kak_40GoldSkulltulaReward = HintText::Sometimes({
                       //obscure text
                       Text{"#40 bug badges# rewards",           "", ""},
                       Text{"#40 spider souls# yields",          "", ""},
                       Text{"#40 auriferous arachnids# lead to", "", ""},
                     },
                       //clear text
                       Text{"slaying #40 Gold Skulltulas# reveals", "", ""}
  );

  HintText Kak_30GoldSkulltulaReward = HintText::Sometimes({
                       //obscure text
                       Text{"#30 bug badges# rewards",           "", ""},
                       Text{"#30 spider souls# yields",          "", ""},
                       Text{"#30 auriferous arachnids# lead to", "", ""},
                     },
                       //clear text
                       Text{"slaying #30 Gold Skulltulas# reveals", "", ""}
  );

  HintText Kak_20GoldSkulltulaReward = HintText::Sometimes({
                       //obscure text
                       Text{"#20 bug badges# rewards",           "", ""},
                       Text{"#20 spider souls# yields",          "", ""},
                       Text{"#20 auriferous arachnids# lead to", "", ""},
                     },
                       //clear text
                       Text{"slaying #20 Gold Skulltulas# reveals", "", ""}
  );

  HintText Kak_AnjuAsChild = HintText::Sometimes({
                       //obscure text
                       Text{"#wrangling roosters# rewards", "", ""},
                       Text{"#chucking chickens# gifts",    "", ""},
                     },
                       //clear text
                       Text{"#collecting cuccos# rewards", "", ""}
  );

  HintText GC_DaruniasJoy = HintText::Sometimes({
                       //obscure text
                       Text{"a #groovin' goron# gifts", "", ""},
                     },
                       //clear text
                       Text{"#Darunia's dance# leads to", "", ""}
  );

  HintText LW_SkullKid = HintText::Sometimes({
                       //obscure text
                       Text{"the #Skull Kid# grants", "", ""},
  });

  HintText LH_Sun = HintText::Sometimes({
                       //obscure text
                       Text{"staring into #the sun# grants", "", ""},
                     },
                       //clear text
                       Text{"shooting #the sun# grants", "", ""}
  );

  HintText MK_TreasureChestGameReward = HintText::Sometimes({
                       //obscure text
                       Text{"#gambling# grants",               "", ""},
                       Text{"there is a #1/32 chance# to win", "", ""},
                     },
                       //clear text
                       Text{"the #treasure chest game# grants", "", ""}
  );

  HintText GF_HBA1500Points = HintText::Sometimes({
                       //obscure text
                       Text{"mastery of #horseback archery# grants", "", ""},
                     },
                       //clear text
                       Text{"scoring 1500 in #horseback archery# grants", "", ""}
  );

  HintText GY_HeartPieceGraveChest = HintText::Sometimes({
                       //obscure text
                       Text{"playing #Sun's Song# in a grave spawns", "", ""},
  });

  HintText GC_MazeLeftChest = HintText::Sometimes({
                       //obscure text
                       Text{"in #Goron City# the hammer unlocks", "", ""},
  });

  HintText GV_Chest = HintText::Sometimes({
                       //obscure text
                       Text{"in #Gerudo Valley# the hammer unlocks", "", ""},
  });

  HintText GV_Cow = HintText::Sometimes({
                       //obscure text
                       Text{"a #cow in Gerudo Valley# gifts", "", ""},
  });

  HintText HC_GS_StormsGrotto = HintText::Sometimes({
                       //obscure text
                       Text{"a #spider behind a muddy wall# in a grotto holds", "", ""},
  });

  HintText HF_GS_CowGrotto = HintText::Sometimes({
                       //obscure text
                       Text{"a #spider behind webs# in a grotto holds", "", ""},
  });

  HintText HF_CowGrottoCow = HintText::Sometimes({
                       //obscure text
                       Text{"the #cobwebbed cow# gifts", "", ""},
                     },
                       //clear text
                       Text{"a #cow behind webs# in a grotto gifts", "", ""}
  );

  HintText ZF_GS_HiddenCave = HintText::Sometimes({
                       //obscure text
                       Text{"a spider high #above the icy waters# holds", "", ""},
  });

  HintText HW_Chest = HintText::Sometimes({
                       //obscure text
                       Text{"#deep in the wasteland# is",         "", ""},
                       Text{"beneath #the sands#, flames reveal", "", ""},
  });

  HintText HW_GS = HintText::Sometimes({
                       //obscure text
                       Text{"a #spider in the wasteland# holds", "", ""},
  });

  HintText GY_ComposersGraveChest = HintText::Sometimes({
                       //obscure text
                       Text{"#flames in the Composers' Grave# reveal", "", ""},
                       Text{"the #Composer Brothers hid#",             "", ""},
  });

  HintText ZF_BottomFreestandingPoH = HintText::Sometimes({
                       //obscure text
                       Text{"#under the icy waters# lies", "", ""},
  });

  HintText GC_PotFreestandingPoH = HintText::Sometimes({
                       //obscure text
                       Text{"spinning #Goron pottery# contains", "", ""},
  });

  HintText ZD_KingZoraThawed = HintText::Sometimes({
                       //obscure text
                       Text{"a #defrosted dignitary# gifts", "", ""},
                     },
                       //clear text
                       Text{"unfreezing #King Zora# grants", "", ""}
  );

  HintText DMC_DekuScrub = HintText::Sometimes({
                       //obscure text
                       Text{"a single #scrub in the crater# sells", "", ""},
  });

  HintText DMC_GS_Crate = HintText::Sometimes({
                       //obscure text
                       Text{"a spider under a #crate in the crater# holds", "", ""},
  });


  HintText DekuTree_MQ_AfterSpinningLogChest = HintText::Sometimes({
                       //obscure text
                       Text{"a #temporal stone within a tree# contains", "", ""},
                     },
                       //clear text
                       Text{"a #temporal stone within the Deku Tree# contains", "", ""}
  );

  HintText DekuTree_MQ_GS_BasementGravesRoom = HintText::Sometimes({
                       //obscure text
                       Text{"a #spider on a ceiling in a tree# holds", "", ""},
                     },
                       //clear text
                       Text{"a #spider on a ceiling in the Deku Tree# holds", "", ""}
  );

  HintText DodongosCavern_MQ_GS_SongOfTimeBlockRoom = HintText::Sometimes({
                       //obscure text
                       Text{"a spider under #temporal stones in a cavern# holds", "", ""},
                     },
                       //clear text
                       Text{"a spider under #temporal stones in Dodongo's Cavern# holds", "", ""}
  );

  HintText JabuJabusBelly_BoomerangChest = HintText::Sometimes({
                       //obscure text
                       Text{"a school of #stingers swallowed by a deity# guard", "", ""},
                     },
                       //clear text
                       Text{"a school of #stingers swallowed by Jabu Jabu# guard", "", ""}
  );

  HintText JabuJabusBelly_MQ_GS_InvisibleEnemiesRoom = HintText::Sometimes({
                       //obscure text
                       Text{"a spider surrounded by #shadows in the belly of a deity# holds", "", ""},
                     },
                       //clear text
                       Text{"a spider surrounded by #shadows in Jabu Jabu's Belly# holds", "", ""}
  );

  HintText JabuJabusBelly_MQ_Cow = HintText::Sometimes({
                       //obscure text
                       Text{"a #cow swallowed by a deity# gifts", "", ""},
                     },
                       //clear text
                       Text{"a #cow swallowed by Jabu Jabu# gifts", "", ""}
  );

  HintText FireTemple_ScarecrowChest = HintText::Sometimes({
                       //obscure text
                       Text{"a #scarecrow atop the volcano# hides", "", ""},
                     },
                       //clear text
                       Text{"#Pierre atop the Fire Temple# hides", "", ""}
  );

  HintText FireTemple_MegatonHammerChest = HintText::Sometimes({
                       //obscure text
                       Text{"the #Flare Dancer atop the volcano# guards a chest containing", "", ""},
                     },
                       //clear text
                       Text{"the #Flare Dancer atop the Fire Temple# guards a chest containing", "", ""}
  );

  HintText FireTemple_MQ_ChestOnFire = HintText::Sometimes({
                       //obscure text
                       Text{"the #Flare Dancer atop the volcano# guards a chest containing", "", ""},
                     },
                       //clear text
                       Text{"the #Flare Dancer atop the Fire Temple# guards a chest containing", "", ""}
  );

  HintText FireTemple_MQ_GS_SkullOnFire = HintText::Sometimes({
                       //obscure text
                       Text{"a #spider under a block in the volcano# holds", "", ""},
                     },
                       //clear text
                       Text{"a #spider under a block in the Fire Temple# holds", "", ""}
  );

  HintText WaterTemple_RiverChest = HintText::Sometimes({
                       //obscure text
                       Text{"beyond the #river under the lake# waits", "", ""},
                     },
                       //clear text
                       Text{"beyond the #river in the Water Temple# waits", "", ""}
  );

  HintText WaterTemple_BossKeyChest = HintText::Sometimes({
                       //obscure text
                       Text{"dodging #rolling boulders under the lake# leads to", "", ""},
                     },
                       //clear text
                       Text{"dodging #rolling boulders in the Water Temple# leads to", "", ""}
  );

  HintText WaterTemple_GS_BehindGate = HintText::Sometimes({
                       //obscure text
                       Text{"a spider behind a #gate under the lake# holds", "", ""},
                     },
                       //clear text
                       Text{"a spider behind a #gate in the Water Temple# holds", "", ""}
  );

  HintText WaterTemple_MQ_FreestandingKey = HintText::Sometimes({
                       //obscure text
                       Text{"hidden in a #box under the lake# lies", "", ""},
                     },
                       //clear text
                       Text{"hidden in a #box in the Water Temple# lies", "", ""}
  );

  HintText WaterTemple_MQ_GS_FreestandingKeyArea = HintText::Sometimes({
                       //obscure text
                       Text{"the #locked spider under the lake# holds", "", ""},
                     },
                       //clear text
                       Text{"the #locked spider in the Water Temple# holds", "", ""}
  );

  HintText WaterTemple_MQ_GS_TripleWallTorch = HintText::Sometimes({
                       //obscure text
                       Text{"a spider behind a #gate under the lake# holds", "", ""},
                     },
                       //clear text
                       Text{"a spider behind a #gate in the Water Temple# holds", "", ""}
  );

  HintText GerudoTrainingGrounds_UnderwaterSilverRupeeChest = HintText::Sometimes({
                       //obscure text
                       Text{"those who seek #sunken silver rupees# will find", "", ""},
                       Text{"the #thieves' underwater training# rewards",      "", ""},
  });

  HintText GerudoTrainingGrounds_MQ_UnderwaterSilverRupeeChest = HintText::Sometimes({
                       //obscure text
                       Text{"those who seek #sunken silver rupees# will find", "", ""},
                       Text{"the #thieves' underwater training# rewards",      "", ""},
  });

  HintText GerudoTrainingGrounds_MazePathFinalChest = HintText::Sometimes({
                       //obscure text
                       Text{"the final prize of #the thieves' training# is", "", ""},
  });

  HintText GerudoTrainingGrounds_MQ_IceArrowsChest = HintText::Sometimes({
                       //obscure text
                       Text{"the final prize of #the thieves' training# is", "", ""},
  });

  HintText BottomOfTheWell_LensOfTruthChest = HintText::Sometimes({
                       //obscure text
                       Text{"the well's #grasping ghoul# hides",    "", ""},
                       Text{"a #nether dweller in the well# holds", "", ""},
                     },
                       //clear text
                       Text{"#Dead Hand in the well# holds", "", ""}
  );

  HintText BottomOfTheWell_MQ_CompassChest = HintText::Sometimes({
                       //obscure text
                       Text{"the well's #grasping ghoul# hides",    "", ""},
                       Text{"a #nether dweller in the well# holds", "", ""},
                     },
                       //clear text
                       Text{"#Dead Hand in the well# holds", "", ""}
  );

  HintText SpiritTemple_SilverGauntletsChest = HintText::Sometimes({
                       //obscure text
                       Text{"the treasure #sought by Nabooru# is", "", ""},
                     },
                       //clear text
                       Text{"upon the #Colossus's right hand# is", "", ""}
  );

  HintText SpiritTemple_MirrorShieldChest = HintText::Sometimes({
                       //obscure text
                       Text{"upon the #Colossus's left hand# is", "", ""},
  });

  HintText SpiritTemple_MQ_ChildHammerSwitchChest = HintText::Sometimes({
                       //obscure text
                       Text{"a #temporal paradox in the Colossus# yields", "", ""},
                     },
                       //clear text
                       Text{"a #temporal paradox in the Spirit Temple# yields", "", ""}
  );

  HintText SpiritTemple_MQ_SymphonyRoomChest = HintText::Sometimes({
                       //obscure text
                       Text{"a #symphony in the Colossus# yields", "", ""},
                     },
                       //clear text
                       Text{"a #symphony in the Spirit Temple# yields", "", ""}
  );

  HintText SpiritTemple_MQ_GS_SymphonyRoom = HintText::Sometimes({
                       //obscure text
                       Text{"a #spider's symphony in the Colossus# yields", "", ""},
                     },
                       //clear text
                       Text{"a #spider's symphony in the Spirit Temple# yields", "", ""}
  );

  HintText ShadowTemple_InvisibleFloormasterChest = HintText::Sometimes({
                       //obscure text
                       Text{"shadows in an #invisible maze# guard", "", ""},
  });

  HintText ShadowTemple_MQ_BombFlowerChest = HintText::Sometimes({
                       //obscure text
                       Text{"shadows in an #invisible maze# guard", "", ""},
  });

  /*--------------------------
  |    EXCLUDE HINT TEXT     |
  ---------------------------*/

  HintText KF_KokiriSwordChest = HintText::Exclude({
                       //obscure text
                       Text{"the #hidden treasure of the Kokiri# is", "", ""},
  });

  HintText KF_MidoTopLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"the #leader of the Kokiri# hides", "", ""},
                     },
                       //clear text
                       Text{"#inside Mido's house# is", "", ""}
  );

  HintText KF_MidoTopRightChest = HintText::Exclude({
                       //obscure text
                       Text{"the #leader of the Kokiri# hides", "", ""},
                     },
                       //clear text
                       Text{"#inside Mido's house# is", "", ""}
  );

  HintText KF_MidoBottomLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"the #leader of the Kokiri# hides", "", ""},
                     },
                       //clear text
                       Text{"#inside Mido's house# is", "", ""}
  );

  HintText KF_MidoBottomRightChest = HintText::Exclude({
                       //obscure text
                       Text{"the #leader of the Kokiri# hides", "", ""},
                     },
                       //clear text
                       Text{"#inside Mido's house# is", "", ""}
  );

  HintText GY_ShieldGraveChest = HintText::Exclude({
                       //obscure text
                       Text{"the #treasure of a fallen soldier# is", "", ""},
  });

  HintText DMT_Chest = HintText::Exclude({
                       //obscure text
                       Text{"hidden behind a wall on a #mountain trail# is", "", ""},
  });

  HintText GC_MazeRightChest = HintText::Exclude({
                       //obscure text
                       Text{"in #Goron City# explosives unlock", "", ""},
  });

  HintText GC_MazeCenterChest = HintText::Exclude({
                       //obscure text
                       Text{"in #Goron City# explosives unlock", "", ""},
  });

  HintText ZD_Chest = HintText::Exclude({
                       //obscure text
                       Text{"fire #beyond a waterfall# reveals", "", ""},
  });

  HintText GY_HookshotChest = HintText::Exclude({
                       //obscure text
                       Text{"a chest hidden by a #speedy spectre# holds", "", ""},
                     },
                       //clear text
                       Text{"#dead Dampe's first prize# is", "", ""}
  );

  HintText GF_Chest = HintText::Exclude({
                       //obscure text
                       Text{"on a #rooftop in the desert# lies", "", ""},
  });

  HintText Kak_RedeadGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"#zombies beneath the earth# guard", "", ""},
  });

  HintText SFM_WolfosGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"#wolves beneath the earth# guard", "", ""},
  });

  HintText HF_NearMarketGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"a #hole in a field near a drawbridge# holds", "", ""},
  });

  HintText HF_SoutheastGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"a #hole amongst trees in a field# holds", "", ""},
  });

  HintText HF_OpenGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"an #open hole in a field# holds", "", ""},
  });

  HintText Kak_OpenGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"an #open hole in a town# holds", "", ""},
  });

  HintText ZR_OpenGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"a #hole along a river# holds", "", ""},
  });

  HintText KF_StormsGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"a #hole in a forest village# holds", "", ""},
  });

  HintText LW_NearShortcutsGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"a #hole in a wooded maze# holds", "", ""},
  });

  HintText DMT_StormsGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"#hole flooded with rain on a mountain# holds", "", ""},
  });

  HintText DMC_UpperGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"a #hole in a volcano# holds", "", ""},
  });


  HintText ToT_LightArrowCutscene = HintText::Exclude({
                       //obscure text
                       Text{"the #final gift of a princess# is", "", ""},
  });

  HintText LW_GiftFromSaria = HintText::Exclude({
                       //obscure text
                       Text{"a #potato hoarder# holds",           "", ""},
                       Text{"a rooty tooty #flutey cutey# gifts", "", ""},
                     },
                       //clear text
                       Text{"#Saria's Gift# is", "", ""}
  );

  HintText ZF_GreatFairyReward = HintText::Exclude({
                       //obscure text
                       Text{"the #fairy of winds# holds", "", ""},
  });

  HintText HC_GreatFairyReward = HintText::Exclude({
                       //obscure text
                       Text{"the #fairy of fire# holds", "", ""},
  });

  HintText Colossus_GreatFairyReward = HintText::Exclude({
                       //obscure text
                       Text{"the #fairy of love# holds", "", ""},
  });

  HintText DMT_GreatFairyReward = HintText::Exclude({
                       //obscure text
                       Text{"a #magical fairy# gifts", "", ""},
  });

  HintText DMC_GreatFairyReward = HintText::Exclude({
                       //obscure text
                       Text{"a #magical fairy# gifts", "", ""},
  });

  HintText OGC_GreatFairyReward = HintText::Exclude({
                       //obscure text
                       Text{"the #fairy of strength# holds", "", ""},
  });


  HintText SongFromImpa = HintText::Exclude({
                       //obscure text
                       Text{"#deep in a castle#, Impa teaches", "", ""},
  });

  HintText SongFromMalon = HintText::Exclude({
                       //obscure text
                       Text{"#a farm girl# sings", "", ""},
  });

  HintText SongFromSaria = HintText::Exclude({
                       //obscure text
                       Text{"#deep in the forest#, Saria teaches", "", ""},
  });

  HintText SongFromWindmill = HintText::Exclude({
                       //obscure text
                       Text{"a man #in a windmill# is obsessed with", "", ""},
  });


  HintText HC_MalonEgg = HintText::Exclude({
                       //obscure text
                       Text{"a #girl looking for her father# gives", "", ""},
  });

  HintText HC_ZeldasLetter = HintText::Exclude({
                       //obscure text
                       Text{"a #princess in a castle# gifts", "", ""},
  });

  HintText ZD_DivingMinigame = HintText::Exclude({
                       //obscure text
                       Text{"an #unsustainable business model# gifts", "", ""},
                     },
                       //clear text
                       Text{"those who #dive for Zora rupees# will find", "", ""}
  );

  HintText LH_ChildFishing = HintText::Exclude({
                       //obscure text
                       Text{"#fishing in youth# bestows", "", ""},
  });

  HintText LH_AdultFishing = HintText::Exclude({
                       //obscure text
                       Text{"#fishing in maturity# bestows", "", ""},
  });

  HintText LH_LabDive = HintText::Exclude({
                       //obscure text
                       Text{"a #diving experiment# is rewarded with", "", ""},
  });

  HintText GC_RollingGoronAsAdult = HintText::Exclude({
                       //obscure text
                       Text{"#comforting yourself# provides", "", ""},
                     },
                       //clear text
                       Text{"#reassuring a young Goron# is rewarded with", "", ""}
  );

  HintText MK_BombchuBowlingFirstPrize = HintText::Exclude({
                       //obscure text
                       Text{"the #first explosive prize# is", "", ""},
  });

  HintText MK_BombchuBowlingSecondPrize = HintText::Exclude({
                       //obscure text
                       Text{"the #second explosive prize# is", "", ""},
  });

  HintText MK_LostDog = HintText::Exclude({
                       //obscure text
                       Text{"#puppy lovers# will find", "", ""},
                     },
                       //clear text
                       Text{"#rescuing Richard the Dog# is rewarded with", "", ""}
  );

  HintText LW_OcarinaMemoryGame = HintText::Exclude({
                       //obscure text
                       Text{"the prize for a #game of Simon Says# is", "", ""},
                       Text{"a #child sing-a-long# holds",             "", ""},
                     },
                       //clear text
                       Text{"#playing an Ocarina in Lost Woods# is rewarded with", "", ""}
  );

  HintText Kak_10GoldSkulltulaReward = HintText::Exclude({
                       //obscure text
                       Text{"#10 bug badges# rewards",           "", ""},
                       Text{"#10 spider souls# yields",          "", ""},
                       Text{"#10 auriferous arachnids# lead to", "", ""},
                     },
                       //clear text
                       Text{"slaying #10 Gold Skulltulas# reveals", "", ""}
  );

  HintText Kak_ManOnRoof = HintText::Exclude({
                       //obscure text
                       Text{"a #rooftop wanderer# holds", "", ""},
  });

  HintText ZR_MagicBeanSalesman = HintText::Exclude({
                       //obscure text
                       Text{"a seller of #colorful crops# has", "", ""},
                     },
                       //clear text
                       Text{"a #bean seller# offers", "", ""}
  );

  HintText ZR_FrogsInTheRain = HintText::Exclude({
                       //obscure text
                       Text{"#frogs in a storm# gift", "", ""},
  });

  HintText GF_HBA1000Points = HintText::Exclude({
                       //obscure text
                       Text{"scoring 1000 in #horseback archery# grants", "", ""},
  });

  HintText MK_ShootingGalleryReward = HintText::Exclude({
                       //obscure text
                       Text{"#shooting in youth# grants", "", ""},
  });

  HintText Kak_ShootingGalleryReward = HintText::Exclude({
                       //obscure text
                       Text{"#shooting in maturity# grants", "", ""},
  });

  HintText LW_TargetInWoods = HintText::Exclude({
                       //obscure text
                       Text{"shooting a #target in the woods# grants", "", ""},
  });

  HintText Kak_AnjuAsAdult = HintText::Exclude({
                       //obscure text
                       Text{"a #chicken caretaker# offers adults", "", ""},
  });

  HintText LLR_TalonsChickens = HintText::Exclude({
                       //obscure text
                       Text{"#finding Super Cuccos# is rewarded with", "", ""},
  });

  HintText GC_RollingGoronAsChild = HintText::Exclude({
                       //obscure text
                       Text{"the prize offered by a #large rolling Goron# is", "", ""},
  });

  HintText LH_UnderwaterItem = HintText::Exclude({
                       //obscure text
                       Text{"the #sunken treasure in a lake# is", "", ""},
  });

  HintText GF_GerudoToken = HintText::Exclude({
                       //obscure text
                       Text{"#rescuing captured carpenters# is rewarded with", "", ""},
  });

  HintText Wastelan_BombchuSalesman = HintText::Exclude({
                       //obscure text
                       Text{"a #carpet guru# sells", "", ""},
  });


  HintText Kak_ImpasHouseFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"#imprisoned in a house# lies", "", ""},
  });

  HintText HF_TektiteGrottoFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"#deep underwater in a hole# is", "", ""},
  });

  HintText Kak_WindmillFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"on a #windmill ledge# lies", "", ""},
  });

  HintText GY_DampeRaceFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"#racing a ghost# leads to", "", ""},
                     },
                       //clear text
                       Text{"#dead Dampe's second# prize is", "", ""}
  );

  HintText LLR_FreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"in a #ranch silo# lies", "", ""},
  });

  HintText GY_FreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"a #crate in a graveyard# hides", "", ""},
  });

  HintText GY_DampeGravediggingTour = HintText::Exclude({
                       //obscure text
                       Text{"a #gravekeeper digs up#", "", ""},
  });

  HintText ZR_NearOpenGrottoFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"on top of a #pillar in a river# lies", "", ""},
  });

  HintText ZR_NearDomainFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"on a #river ledge by a waterfall# lies", "", ""},
  });

  HintText LH_FreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"high on a #lab rooftop# one can find", "", ""},
  });

  HintText ZF_IcebergFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"#floating on ice# is", "", ""},
  });

  HintText GV_WaterfallFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"behind a #desert waterfall# is", "", ""},
  });

  HintText GV_CrateFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"a #crate in a valley# hides", "", ""},
  });

  HintText Colossus_FreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"on top of an #arch of stone# lies", "", ""},
  });

  HintText DMT_FreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"above a #mountain cavern entrance# is", "", ""},
  });

  HintText DMC_WallFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"nestled in a #volcanic wall# is", "", ""},
  });

  HintText DMC_VolcanoFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"obscured by #volcanic ash# is", "", ""},
  });

  HintText GF_NorthF1Carpenter = HintText::Exclude({
                       //obscure text
                       Text{"#defeating Gerudo guards# reveals", "", ""},
  });

  HintText GF_NorthF2Carpenter = HintText::Exclude({
                       //obscure text
                       Text{"#defeating Gerudo guards# reveals", "", ""},
  });

  HintText GF_SouthF1Carpenter = HintText::Exclude({
                       //obscure text
                       Text{"#defeating Gerudo guards# reveals", "", ""},
  });

  HintText GF_SouthF2Carpenter = HintText::Exclude({
                       //obscure text
                       Text{"#defeating Gerudo guards# reveals", "", ""},
  });


  HintText DekuTree_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"in the #center of the Deku Tree# lies", "", ""},
  });

  HintText DekuTree_SlingshotChest = HintText::Exclude({
                       //obscure text
                       Text{"the #treasure guarded by a scrub# in the Deku Tree is", "", ""},
  });

  HintText DekuTree_SlingshotRoomSideChest = HintText::Exclude({
                       //obscure text
                       Text{"the #treasure guarded by a scrub# in the Deku Tree is", "", ""},
  });

  HintText DekuTree_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#pillars of wood# in the Deku Tree lead to", "", ""},
  });

  HintText DekuTree_CompassRoomSideChest = HintText::Exclude({
                       //obscure text
                       Text{"#pillars of wood# in the Deku Tree lead to", "", ""},
  });

  HintText DekuTree_BasementChest = HintText::Exclude({
                       //obscure text
                       Text{"#webs in the Deku Tree# hide", "", ""},
  });


  HintText DekuTree_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"in the #center of the Deku Tree# lies", "", ""},
  });

  HintText DekuTree_MQ_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"a #treasure guarded by a large spider# in the Deku Tree is", "", ""},
  });

  HintText DekuTree_MQ_SlingshotChest = HintText::Exclude({
                       //obscure text
                       Text{"#pillars of wood# in the Deku Tree lead to", "", ""},
  });

  HintText DekuTree_MQ_SlingshotRoomBackChest = HintText::Exclude({
                       //obscure text
                       Text{"#pillars of wood# in the Deku Tree lead to", "", ""},
  });

  HintText DekuTree_MQ_BasementChest = HintText::Exclude({
                       //obscure text
                       Text{"#webs in the Deku Tree# hide", "", ""},
  });

  HintText DekuTree_MQ_BeforeSpinningLogChest = HintText::Exclude({
                       //obscure text
                       Text{"#magical fire in the Deku Tree# leads to", "", ""},
  });


  HintText DodongosCavern_BossRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"#above King Dodongo# lies", "", ""},
  });


  HintText DodongosCavern_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"a #muddy wall in Dodongo's Cavern# hides", "", ""},
  });

  HintText DodongosCavern_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"a #statue in Dodongo's Cavern# guards", "", ""},
  });

  HintText DodongosCavern_BombFlowerPlatformChest = HintText::Exclude({
                       //obscure text
                       Text{"above a #maze of stone# in Dodongo's Cavern lies", "", ""},
  });

  HintText DodongosCavern_BombBagChest = HintText::Exclude({
                       //obscure text
                       Text{"the #second lizard cavern battle# yields", "", ""},
  });

  HintText DodongosCavern_EndOfBridgeChest = HintText::Exclude({
                       //obscure text
                       Text{"a #chest at the end of a bridge# yields", "", ""},
  });


  HintText DodongosCavern_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"a #muddy wall in Dodongo's Cavern# hides", "", ""},
  });

  HintText DodongosCavern_MQ_BombBagChest = HintText::Exclude({
                       //obscure text
                       Text{"an #elevated alcove# in Dodongo's Cavern holds", "", ""},
  });

  HintText DodongosCavern_MQ_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#fire-breathing lizards# in Dodongo's Cavern guard", "", ""},
  });

  HintText DodongosCavern_MQ_LarvaeRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"#baby spiders# in Dodongo's Cavern guard", "", ""},
  });

  HintText DodongosCavern_MQ_TorchPuzzleRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"above a #maze of stone# in Dodongo's Cavern lies", "", ""},
  });

  HintText DodongosCavern_MQ_UnderGraveChest = HintText::Exclude({
                       //obscure text
                       Text{"#beneath a headstone# in Dodongo's Cavern lies", "", ""},
  });


  HintText JabuJabusBelly_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"#tentacle trouble# in a deity's belly guards", "", ""},
                     },
                       //clear text
                       Text{"a #slimy thing# guards", "", ""}
  );

  HintText JabuJabusBelly_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#bubble trouble# in a deity's belly guards", "", ""},
                     },
                       //clear text
                       Text{"#bubbles# guard", "", ""}
  );


  HintText JabuJabusBelly_MQ_FirstRoomSideChest = HintText::Exclude({
                       //obscure text
                       Text{"shooting a #mouth cow# reveals", "", ""},
  });

  HintText JabuJabusBelly_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"#pop rocks# hide",            "", ""},
                       Text{"an #explosive palate# holds", "", ""},
                     },
                       //clear text
                       Text{"a #boulder before cows# hides", "", ""}
  );

  HintText JabuJabusBelly_MQ_SecondRoomLowerChest = HintText::Exclude({
                       //obscure text
                       Text{"near a #spiked elevator# lies", "", ""},
  });

  HintText JabuJabusBelly_MQ_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"a #drowning cow# unveils", "", ""},
  });

  HintText JabuJabusBelly_MQ_SecondRoomUpperChest = HintText::Exclude({
                       //obscure text
                       Text{"#moving anatomy# creates a path to", "", ""},
  });

  HintText JabuJabusBelly_MQ_BasementNearSwitchesChest = HintText::Exclude({
                       //obscure text
                       Text{"a #pair of digested cows# hold", "", ""},
  });

  HintText JabuJabusBelly_MQ_BasementNearVinesChest = HintText::Exclude({
                       //obscure text
                       Text{"a #pair of digested cows# hold", "", ""},
  });

  HintText JabuJabusBelly_MQ_NearBossChest = HintText::Exclude({
                       //obscure text
                       Text{"the #final cows' reward# in a deity's belly is", "", ""},
  });

  HintText JabuJabusBelly_MQ_FallingLikeLikeRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"#cows protected by falling monsters# in a deity's belly guard", "", ""},
  });

  HintText JabuJabusBelly_MQ_BoomerangRoomSmallChest = HintText::Exclude({
                       //obscure text
                       Text{"a school of #stingers swallowed by a deity# guard", "", ""},
                     },
                       //clear text
                       Text{"a school of #stingers swallowed by Jabu Jabu# guard", "", ""}
  );

  HintText JabuJabusBelly_MQ_BoomerangChest = HintText::Exclude({
                       //obscure text
                       Text{"a school of #stingers swallowed by a deity# guard", "", ""},
                     },
                       //clear text
                       Text{"a school of #stingers swallowed by Jabu Jabu# guard", "", ""}
  );


  HintText ForestTemple_FirstRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"a #tree in the Forest Temple# supports", "", ""},
  });

  HintText ForestTemple_FirstStalfosChest = HintText::Exclude({
                       //obscure text
                       Text{"#defeating enemies beneath a falling ceiling# in Forest Temple yields", "", ""},
  });

  HintText ForestTemple_WellChest = HintText::Exclude({
                       //obscure text
                       Text{"a #sunken chest deep in the woods# contains", "", ""},
  });

  HintText ForestTemple_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"a #fiery skull# in Forest Temple guards", "", ""},
  });

  HintText ForestTemple_RaisedIslandCourtyardChest = HintText::Exclude({
                       //obscure text
                       Text{"a #chest on a small island# in the Forest Temple holds", "", ""},
  });

  HintText ForestTemple_FallingCeilingRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"beneath a #checkerboard falling ceiling# lies", "", ""},
  });

  HintText ForestTemple_EyeSwitchChest = HintText::Exclude({
                       //obscure text
                       Text{"a #sharp eye# will spot", "", ""},
                     },
                       //clear text
                       Text{"#blocks of stone# in the Forest Temple surround", "", ""}
  );

  HintText ForestTemple_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"a #turned trunk# contains", "", ""},
  });

  HintText ForestTemple_FloormasterChest = HintText::Exclude({
                       //obscure text
                       Text{"deep in the forest #shadows guard a chest# containing", "", ""},
  });

  HintText ForestTemple_BowChest = HintText::Exclude({
                       //obscure text
                       Text{"an #army of the dead# guards", "", ""},
                     },
                       //clear text
                       Text{"#Stalfos deep in the Forest Temple# guard", "", ""}
  );

  HintText ForestTemple_RedPoeChest = HintText::Exclude({
                       //obscure text
                       Text{"#Joelle# guards", "", ""},
                     },
                       //clear text
                       Text{"a #red ghost# guards", "", ""}
  );

  HintText ForestTemple_BluePoeChest = HintText::Exclude({
                       //obscure text
                       Text{"#Beth# guards", "", ""},
                     },
                       //clear text
                       Text{"a #blue ghost# guards", "", ""}
  );

  HintText ForestTemple_BasementChest = HintText::Exclude({
                       //obscure text
                       Text{"#revolving walls# in the Forest Temple conceal", "", ""},
  });


  HintText ForestTemple_MQ_FirstRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"a #tree in the Forest Temple# supports", "", ""},
  });

  HintText ForestTemple_MQ_WolfosChest = HintText::Exclude({
                       //obscure text
                       Text{"#defeating enemies beneath a falling ceiling# in Forest Temple yields", "", ""},
  });

  HintText ForestTemple_MQ_BowChest = HintText::Exclude({
                       //obscure text
                       Text{"an #army of the dead# guards", "", ""},
                     },
                       //clear text
                       Text{"#Stalfos deep in the Forest Temple# guard", "", ""}
  );

  HintText ForestTemple_MQ_RaisedIslandCourtyardLowerChest = HintText::Exclude({
                       //obscure text
                       Text{"a #chest on a small island# in the Forest Temple holds", "", ""},
  });

  HintText ForestTemple_MQ_RaisedIslandCourtyardUpperChest = HintText::Exclude({
                       //obscure text
                       Text{"#high in a courtyard# within the Forest Temple is", "", ""},
  });

  HintText ForestTemple_MQ_WellChest = HintText::Exclude({
                       //obscure text
                       Text{"a #sunken chest deep in the woods# contains", "", ""},
  });

  HintText ForestTemple_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"#Joelle# guards", "", ""},
                     },
                       //clear text
                       Text{"a #red ghost# guards", "", ""}
  );

  HintText ForestTemple_MQ_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#Beth# guards", "", ""},
                     },
                       //clear text
                       Text{"a #blue ghost# guards", "", ""}
  );

  HintText ForestTemple_MQ_FallingCeilingRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"beneath a #checkerboard falling ceiling# lies", "", ""},
  });

  HintText ForestTemple_MQ_BasementChest = HintText::Exclude({
                       //obscure text
                       Text{"#revolving walls# in the Forest Temple conceal", "", ""},
  });

  HintText ForestTemple_MQ_RedeadChest = HintText::Exclude({
                       //obscure text
                       Text{"deep in the forest #undead guard a chest# containing", "", ""},
  });

  HintText ForestTemple_MQ_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"a #turned trunk# contains", "", ""},
  });


  HintText FireTemple_NearBossChest = HintText::Exclude({
                       //obscure text
                       Text{"#near a dragon# is", "", ""},
  });

  HintText FireTemple_FlareDancerChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Flare Dancer behind a totem# guards", "", ""},
  });

  HintText FireTemple_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"a #prison beyond a totem# holds", "", ""},
  });

  HintText FireTemple_BigLavaRoomBlockedDoorChest = HintText::Exclude({
                       //obscure text
                       Text{"#explosives over a lava pit# unveil", "", ""},
  });

  HintText FireTemple_BigLavaRoomLowerOpenDoorChest = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron trapped near lava# holds", "", ""},
  });

  HintText FireTemple_BoulderMazeLowerChest = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron at the end of a maze# holds", "", ""},
  });

  HintText FireTemple_BoulderMazeUpperChest = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron above a maze# holds", "", ""},
  });

  HintText FireTemple_BoulderMazeSideRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron hidden near a maze# holds", "", ""},
  });

  HintText FireTemple_BoulderMazeShortcutChest = HintText::Exclude({
                       //obscure text
                       Text{"a #blocked path# in Fire Temple holds", "", ""},
  });

  HintText FireTemple_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"a #caged chest# in the Fire Temple hoards", "", ""},
  });

  HintText FireTemple_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"a #chest in a fiery maze# contains", "", ""},
  });

  HintText FireTemple_HighestGoronChest = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron atop the Fire Temple# holds", "", ""},
  });


  HintText FireTemple_MQ_NearBossChest = HintText::Exclude({
                       //obscure text
                       Text{"#near a dragon# is", "", ""},
  });

  HintText FireTemple_MQ_MegatonHammerChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Flare Dancer in the depths of a volcano# guards", "", ""},
                     },
                       //clear text
                       Text{"the #Flare Dancer in the depths of the Fire Temple# guards", "", ""}
  );

  HintText FireTemple_MQ_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"a #blocked path# in Fire Temple holds", "", ""},
  });

  HintText FireTemple_MQ_LizalfosMazeLowerChest = HintText::Exclude({
                       //obscure text
                       Text{"#crates in a maze# contain", "", ""},
  });

  HintText FireTemple_MQ_LizalfosMazeUpperChest = HintText::Exclude({
                       //obscure text
                       Text{"#crates in a maze# contain", "", ""},
  });

  HintText FireTemple_MQ_MapRoomSideChest = HintText::Exclude({
                       //obscure text
                       Text{"a #falling slug# in the Fire Temple guards", "", ""},
  });

  HintText FireTemple_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"using a #hammer in the depths of the Fire Temple# reveals", "", ""},
  });

  HintText FireTemple_MQ_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"#illuminating a lava pit# reveals the path to", "", ""},
  });

  HintText FireTemple_MQ_BigLavaRoomBlockedDoorChest = HintText::Exclude({
                       //obscure text
                       Text{"#explosives over a lava pit# unveil", "", ""},
  });

  HintText FireTemple_MQ_LizalfosMazeSideRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron hidden near a maze# holds", "", ""},
  });

  HintText FireTemple_MQ_FreestandingKey = HintText::Exclude({
                       //obscure text
                       Text{"hidden #beneath a block of stone# lies", "", ""},
  });


  HintText WaterTemple_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"#rolling spikes# in the Water Temple surround", "", ""},
  });

  HintText WaterTemple_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#roaming stingers in the Water Temple# guard", "", ""},
  });

  HintText WaterTemple_TorchesChest = HintText::Exclude({
                       //obscure text
                       Text{"#fire in the Water Temple# reveals", "", ""},
  });

  HintText WaterTemple_DragonChest = HintText::Exclude({
                       //obscure text
                       Text{"a #serpent's prize# in the Water Temple is", "", ""},
  });

  HintText WaterTemple_CentralBowTargetChest = HintText::Exclude({
                       //obscure text
                       Text{"#blinding an eye# in the Water Temple leads to", "", ""},
  });

  HintText WaterTemple_CentralPillarChest = HintText::Exclude({
                       //obscure text
                       Text{"in the #depths of the Water Temple# lies", "", ""},
  });

  HintText WaterTemple_CrackedWallChest = HintText::Exclude({
                       //obscure text
                       Text{"#through a crack# in the Water Temple is", "", ""},
  });

  HintText WaterTemple_LongshotChest = HintText::Exclude({
                       //obscure text
                       Text{"#facing yourself# reveals",              "", ""},
                       Text{"a #dark reflection# of yourself guards", "", ""},
                     },
                       //clear text
                       Text{"#Dark Link# guards", "", ""}
  );


  HintText WaterTemple_MQ_CentralPillarChest = HintText::Exclude({
                       //obscure text
                       Text{"in the #depths of the Water Temple# lies", "", ""},
  });

  HintText WaterTemple_MQ_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"fire in the Water Temple unlocks a #vast gate# revealing a chest with", "", ""},
  });

  HintText WaterTemple_MQ_LongshotChest = HintText::Exclude({
                       //obscure text
                       Text{"#through a crack# in the Water Temple is", "", ""},
  });

  HintText WaterTemple_MQ_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#fire in the Water Temple# reveals", "", ""},
  });

  HintText WaterTemple_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"#sparring soldiers# in the Water Temple guard", "", ""},
  });


  HintText SpiritTemple_ChildBridgeChest = HintText::Exclude({
                       //obscure text
                       Text{"a child conquers a #skull in green fire# in the Spirit Temple to reach", "", ""},
  });

  HintText SpiritTemple_ChildEarlyTorchesChest = HintText::Exclude({
                       //obscure text
                       Text{"a child can find a #caged chest# in the Spirit Temple with", "", ""},
  });

  HintText SpiritTemple_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#across a pit of sand# in the Spirit Temple lies", "", ""},
  });

  HintText SpiritTemple_EarlyAdultRightChest = HintText::Exclude({
                       //obscure text
                       Text{"#dodging boulders to collect silver rupees# in the Spirit Temple yields", "", ""},
  });

  HintText SpiritTemple_FirstMirrorLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"a #shadow circling reflected light# in the Spirit Temple guards", "", ""},
  });

  HintText SpiritTemple_FirstMirrorRightChest = HintText::Exclude({
                       //obscure text
                       Text{"a #shadow circling reflected light# in the Spirit Temple guards", "", ""},
  });

  HintText SpiritTemple_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"#before a giant statue# in the Spirit Temple lies", "", ""},
  });

  HintText SpiritTemple_ChildClimbNorthChest = HintText::Exclude({
                       //obscure text
                       Text{"#lizards in the Spirit Temple# guard", "", ""},
  });

  HintText SpiritTemple_ChildClimbEastChest = HintText::Exclude({
                       //obscure text
                       Text{"#lizards in the Spirit Temple# guard", "", ""},
  });

  HintText SpiritTemple_SunBlockRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"#torchlight among Beamos# in the Spirit Temple reveals", "", ""},
  });

  HintText SpiritTemple_StatueRoomHandChest = HintText::Exclude({
                       //obscure text
                       Text{"a #statue in the Spirit Temple# holds", "", ""},
  });

  HintText SpiritTemple_StatueRoomNortheastChest = HintText::Exclude({
                       //obscure text
                       Text{"on a #ledge by a statue# in the Spirit Temple rests", "", ""},
  });

  HintText SpiritTemple_NearFourArmosChest = HintText::Exclude({
                       //obscure text
                       Text{"those who #show the light among statues# in the Spirit Temple find", "", ""},
  });

  HintText SpiritTemple_HallwayRightInvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth in the Spirit Temple# reveals", "", ""},
  });

  HintText SpiritTemple_HallwayLeftInvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth in the Spirit Temple# reveals", "", ""},
  });

  HintText SpiritTemple_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"a #chest engulfed in flame# in the Spirit Temple holds", "", ""},
  });

  HintText SpiritTemple_TopmostChest = HintText::Exclude({
                       //obscure text
                       Text{"those who #show the light above the Colossus# find", "", ""},
  });


  HintText SpiritTemple_MQ_EntranceFrontLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"#lying unguarded# in the Spirit Temple is", "", ""},
  });

  HintText SpiritTemple_MQ_EntranceBackRightChest = HintText::Exclude({
                       //obscure text
                       Text{"a #switch in a pillar# within the Spirit Temple drops", "", ""},
  });

  HintText SpiritTemple_MQ_EntranceFrontRightChest = HintText::Exclude({
                       //obscure text
                       Text{"#collecting rupees through a water jet# reveals", "", ""},
  });

  HintText SpiritTemple_MQ_EntranceBackLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"an #eye blinded by stone# within the Spirit Temple conceals", "", ""},
  });

  HintText SpiritTemple_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"surrounded by #fire and wrappings# lies", "", ""},
  });

  HintText SpiritTemple_MQ_MapRoomEnemyChest = HintText::Exclude({
                       //obscure text
                       Text{"a child defeats a #gauntlet of monsters# within the Spirit Temple to find", "", ""},
  });

  HintText SpiritTemple_MQ_ChildClimbNorthChest = HintText::Exclude({
                       //obscure text
                       Text{"#explosive sunlight# within the Spirit Temple uncovers", "", ""},
  });

  HintText SpiritTemple_MQ_ChildClimbSouthChest = HintText::Exclude({
                       //obscure text
                       Text{"#trapped by falling enemies# within the Spirit Temple is", "", ""},
  });

  HintText SpiritTemple_MQ_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#blinding the colossus# unveils", "", ""},
  });

  HintText SpiritTemple_MQ_StatueRoomLullabyChest = HintText::Exclude({
                       //obscure text
                       Text{"a #royal melody awakens the colossus# to reveal", "", ""},
  });

  HintText SpiritTemple_MQ_StatueRoomInvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth# finds the colossus's hidden", "", ""},
  });

  HintText SpiritTemple_MQ_SilverBlockHallwayChest = HintText::Exclude({
                       //obscure text
                       Text{"#the old hide what the young find# to reveal", "", ""},
  });

  HintText SpiritTemple_MQ_SunBlockRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"#sunlight in a maze of fire# hides", "", ""},
  });

  HintText SpiritTemple_MQ_LeeverRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"#across a pit of sand# in the Spirit Temple lies", "", ""},
  });

  HintText SpiritTemple_MQ_BeamosRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"where #temporal stone blocks the path# within the Spirit Temple lies", "", ""},
  });

  HintText SpiritTemple_MQ_ChestSwitchChest = HintText::Exclude({
                       //obscure text
                       Text{"a #chest of double purpose# holds", "", ""},
  });

  HintText SpiritTemple_MQ_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"a #temporal stone blocks the light# leading to", "", ""},
  });

  HintText SpiritTemple_MQ_MirrorPuzzleInvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"those who #show the light above the Colossus# find", "", ""},
  });


  HintText ShadowTemple_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth# pierces a hall of faces to reveal", "", ""},
  });

  HintText ShadowTemple_HoverBootsChest = HintText::Exclude({
                       //obscure text
                       Text{"a #nether dweller in the Shadow Temple# holds", "", ""},
                     },
                       //clear text
                       Text{"#Dead Hand in the Shadow Temple# holds", "", ""}
  );

  HintText ShadowTemple_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#mummies revealed by the Eye of Truth# guard", "", ""},
  });

  HintText ShadowTemple_EarlySilverRupeeChest = HintText::Exclude({
                       //obscure text
                       Text{"#spinning scythes# protect", "", ""},
  });

  HintText ShadowTemple_InvisibleBladesVisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"#invisible blades# guard", "", ""},
  });

  HintText ShadowTemple_InvisibleBladesInvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"#invisible blades# guard", "", ""},
  });

  HintText ShadowTemple_FallingSpikesLowerChest = HintText::Exclude({
                       //obscure text
                       Text{"#falling spikes# block the path to", "", ""},
  });

  HintText ShadowTemple_FallingSpikesUpperChest = HintText::Exclude({
                       //obscure text
                       Text{"#falling spikes# block the path to", "", ""},
  });

  HintText ShadowTemple_FallingSpikesSwitchChest = HintText::Exclude({
                       //obscure text
                       Text{"#falling spikes# block the path to", "", ""},
  });

  HintText ShadowTemple_InvisibleSpikesChest = HintText::Exclude({
                       //obscure text
                       Text{"the #dead roam among invisible spikes# guarding", "", ""},
  });

  HintText ShadowTemple_WindHintChest = HintText::Exclude({
                       //obscure text
                       Text{"an #invisible chest guarded by the dead# holds", "", ""},
  });

  HintText ShadowTemple_AfterWindEnemyChest = HintText::Exclude({
                       //obscure text
                       Text{"#mummies guarding a ferry# hide", "", ""},
  });

  HintText ShadowTemple_AfterWindHiddenChest = HintText::Exclude({
                       //obscure text
                       Text{"#mummies guarding a ferry# hide", "", ""},
  });

  HintText ShadowTemple_SpikeWallsLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"#walls consumed by a ball of fire# reveal", "", ""},
  });

  HintText ShadowTemple_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"#walls consumed by a ball of fire# reveal", "", ""},
  });

  HintText ShadowTemple_FreestandingKey = HintText::Exclude({
                       //obscure text
                       Text{"#inside a burning skull# lies", "", ""},
  });


  HintText ShadowTemple_MQ_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth# pierces a hall of faces to reveal", "", ""},
  });

  HintText ShadowTemple_MQ_HoverBootsChest = HintText::Exclude({
                       //obscure text
                       Text{"#Dead Hand in the Shadow Temple# holds", "", ""},
  });

  HintText ShadowTemple_MQ_EarlyGibdosChest = HintText::Exclude({
                       //obscure text
                       Text{"#mummies revealed by the Eye of Truth# guard", "", ""},
  });

  HintText ShadowTemple_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"#spinning scythes# protect", "", ""},
  });

  HintText ShadowTemple_MQ_BeamosSilverRupeesChest = HintText::Exclude({
                       //obscure text
                       Text{"#collecting rupees in a vast cavern# with the Shadow Temple unveils", "", ""},
  });

  HintText ShadowTemple_MQ_FallingSpikesSwitchChest = HintText::Exclude({
                       //obscure text
                       Text{"#falling spikes# block the path to", "", ""},
  });

  HintText ShadowTemple_MQ_FallingSpikesLowerChest = HintText::Exclude({
                       //obscure text
                       Text{"#falling spikes# block the path to", "", ""},
  });

  HintText ShadowTemple_MQ_FallingSpikesUpperChest = HintText::Exclude({
                       //obscure text
                       Text{"#falling spikes# block the path to", "", ""},
  });

  HintText ShadowTemple_MQ_InvisibleSpikesChest = HintText::Exclude({
                       //obscure text
                       Text{"the #dead roam among invisible spikes# guarding", "", ""},
  });

  HintText ShadowTemple_MQ_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"#walls consumed by a ball of fire# reveal", "", ""},
  });

  HintText ShadowTemple_MQ_SpikeWallsLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"#walls consumed by a ball of fire# reveal", "", ""},
  });

  HintText ShadowTemple_MQ_StalfosRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"near an #empty pedestal# within the Shadow Temple lies", "", ""},
  });

  HintText ShadowTemple_MQ_InvisibleBladesInvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"#invisible blades# guard", "", ""},
  });

  HintText ShadowTemple_MQ_InvisibleBladesVisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"#invisible blades# guard", "", ""},
  });

  HintText ShadowTemple_MQ_WindHintChest = HintText::Exclude({
                       //obscure text
                       Text{"an #invisible chest guarded by the dead# holds", "", ""},
  });

  HintText ShadowTemple_MQ_AfterWindHiddenChest = HintText::Exclude({
                       //obscure text
                       Text{"#mummies guarding a ferry# hide", "", ""},
  });

  HintText ShadowTemple_MQ_AfterWindEnemyChest = HintText::Exclude({
                       //obscure text
                       Text{"#mummies guarding a ferry# hide", "", ""},
  });

  HintText ShadowTemple_MQ_NearShipInvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"#caged near a ship# lies", "", ""},
  });

  HintText ShadowTemple_MQ_FreestandingKey = HintText::Exclude({
                       //obscure text
                       Text{"#behind three burning skulls# lies", "", ""},
  });


  HintText BottomOfTheWell_FrontLeftFakeWallChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth in the well# reveals", "", ""},
  });

  HintText BottomOfTheWell_FrontCenterBombableChest = HintText::Exclude({
                       //obscure text
                       Text{"#gruesome debris# in the well hides", "", ""},
  });

  HintText BottomOfTheWell_RightBottomFakeWallChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth in the well# reveals", "", ""},
  });

  HintText BottomOfTheWell_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"a #hidden entrance to a cage# in the well leads to", "", ""},
  });

  HintText BottomOfTheWell_CenterSkulltulaChest = HintText::Exclude({
                       //obscure text
                       Text{"a #spider guarding a cage# in the well protects", "", ""},
  });

  HintText BottomOfTheWell_BackLeftBombableChest = HintText::Exclude({
                       //obscure text
                       Text{"#gruesome debris# in the well hides", "", ""},
  });

  HintText BottomOfTheWell_InvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"#Dead Hand's invisible secret# is", "", ""},
  });

  HintText BottomOfTheWell_UnderwaterFrontChest = HintText::Exclude({
                       //obscure text
                       Text{"a #royal melody in the well# uncovers", "", ""},
  });

  HintText BottomOfTheWell_UnderwaterLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"a #royal melody in the well# uncovers", "", ""},
  });

  HintText BottomOfTheWell_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"in the #depths of the well# lies", "", ""},
  });

  HintText BottomOfTheWell_FireKeeseChest = HintText::Exclude({
                       //obscure text
                       Text{"#perilous pits# in the well guard the path to", "", ""},
  });

  HintText BottomOfTheWell_LikeLikeChest = HintText::Exclude({
                       //obscure text
                       Text{"#locked in a cage# in the well lies", "", ""},
  });

  HintText BottomOfTheWell_FreestandingKey = HintText::Exclude({
                       //obscure text
                       Text{"#inside a coffin# hides", "", ""},
  });


  HintText BottomOfTheWell_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"a #royal melody in the well# uncovers", "", ""},
  });

  HintText BottomOfTheWell_MQ_LensOfTruthChest = HintText::Exclude({
                       //obscure text
                       Text{"an #army of the dead# in the well guards", "", ""},
  });

  HintText BottomOfTheWell_MQ_DeadHandFreestandingKey = HintText::Exclude({
                       //obscure text
                       Text{"#Dead Hand's explosive secret# is", "", ""},
  });

  HintText BottomOfTheWell_MQ_EastInnerRoomFreestandingKey = HintText::Exclude({
                       //obscure text
                       Text{"an #invisible path in the well# leads to", "", ""},
  });


  HintText IceCavern_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"#winds of ice# surround", "", ""},
  });

  HintText IceCavern_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"a #wall of ice# protects", "", ""},
  });

  HintText IceCavern_IronBootsChest = HintText::Exclude({
                       //obscure text
                       Text{"a #monster in a frozen cavern# guards", "", ""},
  });

  HintText IceCavern_FreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"a #wall of ice# protects", "", ""},
  });


  HintText IceCavern_MQ_IronBootsChest = HintText::Exclude({
                       //obscure text
                       Text{"a #monster in a frozen cavern# guards", "", ""},
  });

  HintText IceCavern_MQ_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#winds of ice# surround", "", ""},
  });

  HintText IceCavern_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"a #wall of ice# protects", "", ""},
  });

  HintText IceCavern_MQ_FreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"#winds of ice# surround", "", ""},
  });


  HintText GerudoTrainingGrounds_LobbyLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"a #blinded eye in the Gerudo Training Grounds# drops", "", ""},
  });

  HintText GerudoTrainingGrounds_LobbyRightChest = HintText::Exclude({
                       //obscure text
                       Text{"a #blinded eye in the Gerudo Training Grounds# drops", "", ""},
  });

  HintText GerudoTrainingGrounds_StalfosChest = HintText::Exclude({
                       //obscure text
                       Text{"#soldiers walking on shifting sands# in the Gerudo Training Grounds guard", "", ""},
  });

  HintText GerudoTrainingGrounds_BeamosChest = HintText::Exclude({
                       //obscure text
                       Text{"#reptilian warriors# in the Gerudo Training Grounds protect", "", ""},
  });

  HintText GerudoTrainingGrounds_HiddenCeilingChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth# in the Gerudo Training Grounds reveals", "", ""},
  });

  HintText GerudoTrainingGrounds_MazePathFirstChest = HintText::Exclude({
                       //obscure text
                       Text{"the first prize of #the thieves' training# is", "", ""},
  });

  HintText GerudoTrainingGrounds_MazePathSecondChest = HintText::Exclude({
                       //obscure text
                       Text{"the second prize of #the thieves' training# is", "", ""},
  });

  HintText GerudoTrainingGrounds_MazePathThirdChest = HintText::Exclude({
                       //obscure text
                       Text{"the third prize of #the thieves' training# is", "", ""},
  });

  HintText GerudoTrainingGrounds_MazeRightCentralChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Song of Time# in the Gerudo Training Grounds leads to", "", ""},
  });

  HintText GerudoTrainingGrounds_MazeRightSideChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Song of Time# in the Gerudo Training Grounds leads to", "", ""},
  });

  HintText GerudoTrainingGrounds_HammerRoomClearChest = HintText::Exclude({
                       //obscure text
                       Text{"#fiery foes# in the Gerudo Training Grounds guard", "", ""},
  });

  HintText GerudoTrainingGrounds_HammerRoomSwitchChest = HintText::Exclude({
                       //obscure text
                       Text{"#engulfed in flame# where thieves train lies", "", ""},
  });

  HintText GerudoTrainingGrounds_EyeStatueChest = HintText::Exclude({
                       //obscure text
                       Text{"thieves #blind four faces# to find", "", ""},
  });

  HintText GerudoTrainingGrounds_NearScarecrowChest = HintText::Exclude({
                       //obscure text
                       Text{"thieves #blind four faces# to find", "", ""},
  });

  HintText GerudoTrainingGrounds_BeforeHeavyBlockChest = HintText::Exclude({
                       //obscure text
                       Text{"#before a block of silver# thieves can find", "", ""},
  });

  HintText GerudoTrainingGrounds_HeavyBlockFirstChest = HintText::Exclude({
                       //obscure text
                       Text{"a #feat of strength# rewards thieves with", "", ""},
  });

  HintText GerudoTrainingGrounds_HeavyBlockSecondChest = HintText::Exclude({
                       //obscure text
                       Text{"a #feat of strength# rewards thieves with", "", ""},
  });

  HintText GerudoTrainingGrounds_HeavyBlockThirdChest = HintText::Exclude({
                       //obscure text
                       Text{"a #feat of strength# rewards thieves with", "", ""},
  });

  HintText GerudoTrainingGrounds_HeavyBlockFourthChest = HintText::Exclude({
                       //obscure text
                       Text{"a #feat of strength# rewards thieves with", "", ""},
  });

  HintText GerudoTrainingGrounds_FreestandingKey = HintText::Exclude({
                       //obscure text
                       Text{"the #Song of Time# in the Gerudo Training Grounds leads to", "", ""},
  });


  HintText GerudoTrainingGrounds_MQ_LobbyRightChest = HintText::Exclude({
                       //obscure text
                       Text{"#thieves prepare for training# with", "", ""},
  });

  HintText GerudoTrainingGrounds_MQ_LobbyLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"#thieves prepare for training# with", "", ""},
  });

  HintText GerudoTrainingGrounds_MQ_FirstIronKnuckleChest = HintText::Exclude({
                       //obscure text
                       Text{"#soldiers walking on shifting sands# in the Gerudo Training Grounds guard", "", ""},
  });

  HintText GerudoTrainingGrounds_MQ_BeforeHeavyBlockChest = HintText::Exclude({
                       //obscure text
                       Text{"#before a block of silver# thieves can find", "", ""},
  });

  HintText GerudoTrainingGrounds_MQ_EyeStatueChest = HintText::Exclude({
                       //obscure text
                       Text{"thieves #blind four faces# to find", "", ""},
  });

  HintText GerudoTrainingGrounds_MQ_FlameCircleChest = HintText::Exclude({
                       //obscure text
                       Text{"#engulfed in flame# where thieves train lies", "", ""},
  });

  HintText GerudoTrainingGrounds_MQ_SecondIronKnuckleChest = HintText::Exclude({
                       //obscure text
                       Text{"#fiery foes# in the Gerudo Training Grounds guard", "", ""},
  });

  HintText GerudoTrainingGrounds_MQ_DinolfosChest = HintText::Exclude({
                       //obscure text
                       Text{"#reptilian warriors# in the Gerudo Training Grounds protect", "", ""},
  });

  HintText GerudoTrainingGrounds_MQ_MazeRightCentralChest = HintText::Exclude({
                       //obscure text
                       Text{"a #path of fire# leads thieves to", "", ""},
  });

  HintText GerudoTrainingGrounds_MQ_MazePathFirstChest = HintText::Exclude({
                       //obscure text
                       Text{"the first prize of #the thieves' training# is", "", ""},
  });

  HintText GerudoTrainingGrounds_MQ_MazeRightSideChest = HintText::Exclude({
                       //obscure text
                       Text{"a #path of fire# leads thieves to", "", ""},
  });

  HintText GerudoTrainingGrounds_MQ_MazePathThirdChest = HintText::Exclude({
                       //obscure text
                       Text{"the third prize of #the thieves' training# is", "", ""},
  });

  HintText GerudoTrainingGrounds_MQ_MazePathSecondChest = HintText::Exclude({
                       //obscure text
                       Text{"the second prize of #the thieves' training# is", "", ""},
  });

  HintText GerudoTrainingGrounds_MQ_HiddenCeilingChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth# in the Gerudo Training Grounds reveals", "", ""},
  });

  HintText GerudoTrainingGrounds_MQ_HeavyBlockChest = HintText::Exclude({
                       //obscure text
                       Text{"a #feat of strength# rewards thieves with", "", ""},
  });


  HintText GanonsCastle_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Evil King# hoards", "", ""},
  });


  HintText GanonsCastle_ForestTrialChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the wilds# holds", "", ""},
  });

  HintText GanonsCastle_WaterTrialLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the seas# holds", "", ""},
  });

  HintText GanonsCastle_WaterTrialRightChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the seas# holds", "", ""},
  });

  HintText GanonsCastle_ShadowTrialFrontChest = HintText::Exclude({
                       //obscure text
                       Text{"#music in the test of darkness# unveils", "", ""},
  });

  HintText GanonsCastle_ShadowTrialGoldenGauntletsChest = HintText::Exclude({
                       //obscure text
                       Text{"#light in the test of darkness# unveils", "", ""},
  });

  HintText GanonsCastle_SpiritTrialCrystalSwitchChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the sands# holds", "", ""},
  });

  HintText GanonsCastle_SpiritTrialInvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the sands# holds", "", ""},
  });

  HintText GanonsCastle_LightTrialFirstLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of radiance# holds", "", ""},
  });

  HintText GanonsCastle_LightTrialSecondLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of radiance# holds", "", ""},
  });

  HintText GanonsCastle_LightTrialThirdLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of radiance# holds", "", ""},
  });

  HintText GanonsCastle_LightTrialFirstRightChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of radiance# holds", "", ""},
  });

  HintText GanonsCastle_LightTrialSecondRightChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of radiance# holds", "", ""},
  });

  HintText GanonsCastle_LightTrialThirdRightChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of radiance# holds", "", ""},
  });

  HintText GanonsCastle_LightTrialInvisibleEnemiesChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of radiance# holds", "", ""},
  });

  HintText GanonsCastle_LightTrialLullabyChest = HintText::Exclude({
                       //obscure text
                       Text{"#music in the test of radiance# reveals", "", ""},
  });


  HintText GanonsCastle_MQ_WaterTrialChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the seas# holds", "", ""},
  });

  HintText GanonsCastle_MQ_ForestTrialEyeSwitchChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the wilds# holds", "", ""},
  });

  HintText GanonsCastle_MQ_ForestTrialFrozenEyeSwitchChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the wilds# holds", "", ""},
  });

  HintText GanonsCastle_MQ_LightTrialLullabyChest = HintText::Exclude({
                       //obscure text
                       Text{"#music in the test of radiance# reveals", "", ""},
  });

  HintText GanonsCastle_MQ_ShadowTrialBombFlowerChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of darkness# holds", "", ""},
  });

  HintText GanonsCastle_MQ_ShadowTrialEyeSwitchChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of darkness# holds", "", ""},
  });

  HintText GanonsCastle_MQ_SpiritTrialGoldenGauntletsChest = HintText::Exclude({
                       //obscure text
                       Text{"#reflected light in the test of the sands# reveals", "", ""},
  });

  HintText GanonsCastle_MQ_SpiritTrialSunBackRightChest = HintText::Exclude({
                       //obscure text
                       Text{"#reflected light in the test of the sands# reveals", "", ""},
  });

  HintText GanonsCastle_MQ_SpiritTrialSunBackLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"#reflected light in the test of the sands# reveals", "", ""},
  });

  HintText GanonsCastle_MQ_SpiritTrialSunFrontLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"#reflected light in the test of the sands# reveals", "", ""},
  });

  HintText GanonsCastle_MQ_SpiritTrialFirstChest = HintText::Exclude({
                       //obscure text
                       Text{"#reflected light in the test of the sands# reveals", "", ""},
  });

  HintText GanonsCastle_MQ_SpiritTrialInvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"#reflected light in the test of the sands# reveals", "", ""},
  });

  HintText GanonsCastle_MQ_ForestTrialFreestandingKey = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the wilds# holds", "", ""},
  });


  HintText DekuTree_QueenGohmaHeart = HintText::Exclude({
                       //obscure text
                       Text{"the #Parasitic Armored Arachnid# holds", "", ""},
                     },
                       //clear text
                       Text{"#Queen Gohma# holds", "", ""}
  );

  HintText DodongosCavern_KingDodongoHeart = HintText::Exclude({
                       //obscure text
                       Text{"the #Infernal Dinosaur# holds", "", ""},
                     },
                       //clear text
                       Text{"#King Dodongo# holds", "", ""}
  );

  HintText JabuJabusBelly_BarinadeHeart = HintText::Exclude({
                       //obscure text
                       Text{"the #Bio-Electric Anemone# holds", "", ""},
                     },
                       //clear text
                       Text{"#Barinade# holds", "", ""}
  );

  HintText ForestTemple_PhantomGanonHeart = HintText::Exclude({
                       //obscure text
                       Text{"the #Evil Spirit from Beyond# holds", "", ""},
                     },
                       //clear text
                       Text{"#Phantom Ganon# holds", "", ""}
  );

  HintText FireTemple_VolvagiaHeart = HintText::Exclude({
                       //obscure text
                       Text{"the #Subterranean Lava Dragon# holds", "", ""},
                     },
                       //clear text
                       Text{"#Volvagia# holds", "", ""}
  );

  HintText WaterTemple_MorphaHeart = HintText::Exclude({
                       //obscure text
                       Text{"the #Giant Aquatic Amoeba# holds", "", ""},
                     },
                       //clear text
                       Text{"#Morpha# holds", "", ""}
  );

  HintText SpiritTemple_TwinrovaHeart = HintText::Exclude({
                       //obscure text
                       Text{"the #Sorceress Sisters# hold", "", ""},
                     },
                       //clear text
                       Text{"#Twinrova# holds", "", ""}
  );

  HintText ShadowTemple_BongoBongoHeart = HintText::Exclude({
                       //obscure text
                       Text{"the #Phantom Shadow Beast# holds", "", ""},
                     },
                       //clear text
                       Text{"#Bongo Bongo# holds", "", ""}
  );


  HintText DekuTree_GS_BasementBackRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider deep within the Deku Tree# hides", "", ""},
  });

  HintText DekuTree_GS_BasementGate = HintText::Exclude({
                       //obscure text
                       Text{"a #web protects a spider# within the Deku Tree holding", "", ""},
  });

  HintText DekuTree_GS_BasementVines = HintText::Exclude({
                       //obscure text
                       Text{"a #web protects a spider# within the Deku Tree holding", "", ""},
  });

  HintText DekuTree_GS_CompassRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider atop the Deku Tree# holds", "", ""},
  });


  HintText DekuTree_MQ_GS_Lobby = HintText::Exclude({
                       //obscure text
                       Text{"a #spider in a crate# within the Deku Tree hides", "", ""},
  });

  HintText DekuTree_MQ_GS_CompassRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #wall of rock protects a spider# within the Deku Tree holding", "", ""},
  });

  HintText DekuTree_MQ_GS_BasementBackRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider deep within the Deku Tree# hides", "", ""},
  });


  HintText DodongosCavern_GS_VinesAboveStairs = HintText::Exclude({
                       //obscure text
                       Text{"a #spider entangled in vines# in Dodongo's Cavern guards", "", ""},
  });

  HintText DodongosCavern_GS_Scarecrow = HintText::Exclude({
                       //obscure text
                       Text{"a #spider among explosive slugs# hides", "", ""},
  });

  HintText DodongosCavern_GS_AlcoveAboveStairs = HintText::Exclude({
                       //obscure text
                       Text{"a #spider just out of reach# in Dodongo's Cavern holds", "", ""},
  });

  HintText DodongosCavern_GS_BackRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider behind a statue# in Dodongo's Cavern holds", "", ""},
  });

  HintText DodongosCavern_GS_SideRoomNearLowerLizalfos = HintText::Exclude({
                       //obscure text
                       Text{"a #spider among bats# in Dodongo's Cavern holds", "", ""},
  });


  HintText DodongosCavern_MQ_GS_ScrubRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider high on a wall# in Dodongo's Cavern holds", "", ""},
  });

  HintText DodongosCavern_MQ_GS_LizalfosRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider on top of a pillar of rock# in Dodongo's Cavern holds", "", ""},
  });

  HintText DodongosCavern_MQ_GS_LarvaeRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider in a crate# in Dodongo's Cavern holds", "", ""},
  });

  HintText DodongosCavern_MQ_GS_BackRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider among graves# in Dodongo's Cavern holds", "", ""},
  });


  HintText JabuJabusBelly_GS_LobbyBasementLower = HintText::Exclude({
                       //obscure text
                       Text{"a #spider resting near a princess# in Jabu Jabu's Belly holds", "", ""},
  });

  HintText JabuJabusBelly_GS_LobbyBasementUpper = HintText::Exclude({
                       //obscure text
                       Text{"a #spider resting near a princess# in Jabu Jabu's Belly holds", "", ""},
  });

  HintText JabuJabusBelly_GS_NearBoss = HintText::Exclude({
                       //obscure text
                       Text{"#jellyfish surround a spider# holding", "", ""},
  });

  HintText JabuJabusBelly_GS_WaterSwitchRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider guarded by a school of stingers# in Jabu Jabu's Belly holds", "", ""},
  });


  HintText JabuJabusBelly_MQ_GS_TailPasaranRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider surrounded by electricity# in Jabu Jabu's Belly holds", "", ""},
  });

  HintText JabuJabusBelly_MQ_GS_BoomerangChestRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider guarded by a school of stingers# in Jabu Jabu's Belly holds", "", ""},
  });

  HintText JabuJabusBelly_MQ_GS_NearBoss = HintText::Exclude({
                       //obscure text
                       Text{"a #spider in a web within Jabu Jabu's Belly# holds", "", ""},
  });


  HintText ForestTemple_GS_RaisedIslandCourtyard = HintText::Exclude({
                       //obscure text
                       Text{"a #spider on a small island# in the Forest Temple holds", "", ""},
  });

  HintText ForestTemple_GS_FirstRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider high on a wall of vines# in the Forest Temple holds", "", ""},
  });

  HintText ForestTemple_GS_LevelIslandCourtyard = HintText::Exclude({
                       //obscure text
                       Text{"#stone columns# lead to a spider in the Forest Temple hiding", "", ""},
  });

  HintText ForestTemple_GS_Lobby = HintText::Exclude({
                       //obscure text
                       Text{"a #spider among ghosts# in the Forest Temple guards", "", ""},
  });

  HintText ForestTemple_GS_Basement = HintText::Exclude({
                       //obscure text
                       Text{"a #spider within revolving walls# in the Forest Temple holds", "", ""},
  });


  HintText ForestTemple_MQ_GS_FirstHallway = HintText::Exclude({
                       //obscure text
                       Text{"an #ivy-hidden spider# in the Forest Temple hoards", "", ""},
  });

  HintText ForestTemple_MQ_GS_BlockPushRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider in a hidden nook# within the Forest Temple holds", "", ""},
  });

  HintText ForestTemple_MQ_GS_RaisedIslandCourtyard = HintText::Exclude({
                       //obscure text
                       Text{"a #spider on an arch# in the Forest Temple holds", "", ""},
  });

  HintText ForestTemple_MQ_GS_LevelIslandCourtyard = HintText::Exclude({
                       //obscure text
                       Text{"a #spider on a ledge# in the Forest Temple holds", "", ""},
  });

  HintText ForestTemple_MQ_GS_Well = HintText::Exclude({
                       //obscure text
                       Text{"#draining a well# in Forest Temple uncovers a spider with", "", ""},
  });


  HintText FireTemple_GS_SongOfTimeRoom = HintText::Exclude({
                       //obscure text
                       Text{"#eight tiles of malice# guard a spider holding", "", ""},
  });

  HintText FireTemple_GS_BossKeyLoop = HintText::Exclude({
                       //obscure text
                       Text{"#five tiles of malice# guard a spider holding", "", ""},
  });

  HintText FireTemple_GS_BoulderMaze = HintText::Exclude({
                       //obscure text
                       Text{"#explosives in a maze# unveil a spider hiding", "", ""},
  });

  HintText FireTemple_GS_ScarecrowTop = HintText::Exclude({
                       //obscure text
                       Text{"a #spider-friendly scarecrow# atop a volcano hides", "", ""},
                     },
                       //clear text
                       Text{"a #spider-friendly scarecrow# atop the Fire Temple hides", "", ""}
  );

  HintText FireTemple_GS_ScarecrowClimb = HintText::Exclude({
                       //obscure text
                       Text{"a #spider-friendly scarecrow# atop a volcano hides", "", ""},
                     },
                       //clear text
                       Text{"a #spider-friendly scarecrow# atop the Fire Temple hides", "", ""}
  );


  HintText FireTemple_MQ_GS_AboveFireWallMaze = HintText::Exclude({
                       //obscure text
                       Text{"a #spider above a fiery maze# holds", "", ""},
  });

  HintText FireTemple_MQ_GS_FireWallMazeCenter = HintText::Exclude({
                       //obscure text
                       Text{"a #spider within a fiery maze# holds", "", ""},
  });

  HintText FireTemple_MQ_GS_BigLavaRoomOpenDoor = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron trapped near lava# befriended a spider with", "", ""},
  });

  HintText FireTemple_MQ_GS_FireWallMazeSideRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider beside a fiery maze# holds", "", ""},
  });


  HintText WaterTemple_GS_FallingPlatformRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider over a waterfall# in the Water Temple holds", "", ""},
  });

  HintText WaterTemple_GS_CentralPillar = HintText::Exclude({
                       //obscure text
                       Text{"a #spider in the center of the Water Temple# holds", "", ""},
  });

  HintText WaterTemple_GS_NearBossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"a spider protected by #rolling boulders under the lake# hides", "", ""},
                     },
                       //clear text
                       Text{"a spider protected by #rolling boulders in the Water Temple# hides", "", ""}
  );

  HintText WaterTemple_GS_River = HintText::Exclude({
                       //obscure text
                       Text{"a #spider over a river# in the Water Temple holds", "", ""},
  });


  HintText WaterTemple_MQ_GS_BeforeUpperWaterSwitch = HintText::Exclude({
                       //obscure text
                       Text{"#beyond a pit of lizards# is a spider holding", "", ""},
  });

  HintText WaterTemple_MQ_GS_LizalfosHallway = HintText::Exclude({
                       //obscure text
                       Text{"#lizards guard a spider# in the Water Temple with", "", ""},
  });

  HintText WaterTemple_MQ_GS_River = HintText::Exclude({
                       //obscure text
                       Text{"a #spider over a river# in the Water Temple holds", "", ""},
  });


  HintText SpiritTemple_GS_HallAfterSunBlockRoom = HintText::Exclude({
                       //obscure text
                       Text{"a spider in the #hall of a knight# guards", "", ""},
  });

  HintText SpiritTemple_GS_BoulderRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider behind a temporal stone# in the Spirit Temple yields", "", ""},
  });

  HintText SpiritTemple_GS_Lobby = HintText::Exclude({
                       //obscure text
                       Text{"a #spider beside a statue# holds", "", ""},
  });

  HintText SpiritTemple_GS_SunOnFloorRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider at the top of a deep shaft# in the Spirit Temple holds", "", ""},
  });

  HintText SpiritTemple_GS_MetalFence = HintText::Exclude({
                       //obscure text
                       Text{"a child defeats a #spider among bats# in the Spirit Temple to gain", "", ""},
  });


  HintText SpiritTemple_MQ_GS_LeeverRoom = HintText::Exclude({
                       //obscure text
                       Text{"#above a pit of sand# in the Spirit Temple hides", "", ""},
  });

  HintText SpiritTemple_MQ_GS_NineThronesRoomWest = HintText::Exclude({
                       //obscure text
                       Text{"a spider in the #hall of a knight# guards", "", ""},
  });

  HintText SpiritTemple_MQ_GS_NineThronesRoomNorth = HintText::Exclude({
                       //obscure text
                       Text{"a spider in the #hall of a knight# guards", "", ""},
  });

  HintText SpiritTemple_MQ_GS_SunBlockRoom = HintText::Exclude({
                       //obscure text
                       Text{"#upon a web of glass# in the Spirit Temple sits a spider holding", "", ""},
  });


  HintText ShadowTemple_GS_SingleGiantPot = HintText::Exclude({
                       //obscure text
                       Text{"#beyond a burning skull# lies a spider with", "", ""},
  });

  HintText ShadowTemple_GS_FallingSpikesRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider beyond falling spikes# holds", "", ""},
  });

  HintText ShadowTemple_GS_TripleGiantPot = HintText::Exclude({
                       //obscure text
                       Text{"#beyond three burning skulls# lies a spider with", "", ""},
  });

  HintText ShadowTemple_GS_LikeLikeRoom = HintText::Exclude({
                       //obscure text
                       Text{"a spider guarded by #invisible blades# holds", "", ""},
  });

  HintText ShadowTemple_GS_NearShip = HintText::Exclude({
                       //obscure text
                       Text{"a spider near a #docked ship# hoards", "", ""},
  });


  HintText ShadowTemple_MQ_GS_FallingSpikesRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider beyond falling spikes# holds", "", ""},
  });

  HintText ShadowTemple_MQ_GS_WindHintRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider amidst roaring winds# in the Shadow Temple holds", "", ""},
  });

  HintText ShadowTemple_MQ_GS_AfterWind = HintText::Exclude({
                       //obscure text
                       Text{"a #spider beneath gruesome debris# in the Shadow Temple hides", "", ""},
  });

  HintText ShadowTemple_MQ_GS_AfterShip = HintText::Exclude({
                       //obscure text
                       Text{"a #fallen statue# reveals a spider with", "", ""},
  });

  HintText ShadowTemple_MQ_GS_NearBoss = HintText::Exclude({
                       //obscure text
                       Text{"a #suspended spider# guards", "", ""},
  });


  HintText BottomOfTheWell_GS_LikeLikeCage = HintText::Exclude({
                       //obscure text
                       Text{"a #spider locked in a cage# in the well holds", "", ""},
  });

  HintText BottomOfTheWell_GS_EastInnerRoom = HintText::Exclude({
                       //obscure text
                       Text{"an #invisible path in the well# leads to", "", ""},
  });

  HintText BottomOfTheWell_GS_WestInnerRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider locked in a crypt# within the well guards", "", ""},
  });


  HintText BottomOfTheWell_MQ_GS_Basement = HintText::Exclude({
                       //obscure text
                       Text{"a #gauntlet of invisible spiders# protects", "", ""},
  });

  HintText BottomOfTheWell_MQ_GS_CoffinRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider crawling near the dead# in the well holds", "", ""},
  });

  HintText BottomOfTheWell_MQ_GS_WestInnerRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider locked in a crypt# within the well guards", "", ""},
  });


  HintText IceCavern_GS_PushBlockRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider above icy pits# holds", "", ""},
  });

  HintText IceCavern_GS_SpinningScytheRoom = HintText::Exclude({
                       //obscure text
                       Text{"#spinning ice# guards a spider holding", "", ""},
  });

  HintText IceCavern_GS_HeartPieceRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider behind a wall of ice# hides", "", ""},
  });


  HintText IceCavern_MQ_GS_Scarecrow = HintText::Exclude({
                       //obscure text
                       Text{"a #spider above icy pits# holds", "", ""},
  });

  HintText IceCavern_MQ_GS_IceBlock = HintText::Exclude({
                       //obscure text
                       Text{"a #web of ice# surrounds a spider with", "", ""},
  });

  HintText IceCavern_MQ_GS_RedIce = HintText::Exclude({
                       //obscure text
                       Text{"a #spider in fiery ice# hoards", "", ""},
  });


  HintText HF_GS_NearKakGrotto = HintText::Exclude({
                       //obscure text
                       Text{"a #spider-guarded spider in a hole# hoards", "", ""},
  });


  HintText LLR_GS_BackWall = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider in a ranch# holding", "", ""},
  });

  HintText LLR_GS_RainShed = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider in a ranch# holding", "", ""},
  });

  HintText LLR_GS_HouseWindow = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider in a ranch# holding", "", ""},
  });

  HintText LLR_GS_Tree = HintText::Exclude({
                       //obscure text
                       Text{"a spider hiding in a #ranch tree# holds", "", ""},
  });


  HintText KF_GS_BeanPatch = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried in a forest# holds", "", ""},
  });

  HintText KF_GS_KnowItAllHouse = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a forest# holding", "", ""},
  });

  HintText KF_GS_HouseOfTwins = HintText::Exclude({
                       //obscure text
                       Text{"night in the future reveals a #spider in a forest# holding", "", ""},
  });


  HintText LW_GS_BeanPatchNearBridge = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried deep in a forest maze# holds", "", ""},
  });

  HintText LW_GS_BeanPatchNearTheater = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried deep in a forest maze# holds", "", ""},
  });

  HintText LW_GS_AboveTheater = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider deep in a forest maze# holding", "", ""},
  });

  HintText SFM_GS = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider in a forest meadow# holding", "", ""},
  });


  HintText OGC_GS = HintText::Exclude({
                       //obscure text
                       Text{"a #spider outside a tyrant's tower# holds", "", ""},
  });

  HintText HC_GS_Tree = HintText::Exclude({
                       //obscure text
                       Text{"a spider hiding in a #tree outside of a castle# holds", "", ""},
  });

  HintText MK_GS_GuardHouse = HintText::Exclude({
                       //obscure text
                       Text{"a #spider in a guarded crate# holds", "", ""},
  });


  HintText DMC_GS_BeanPatch = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried in a volcano# holds", "", ""},
  });


  HintText DMT_GS_BeanPatch = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried outside a cavern# holds", "", ""},
  });

  HintText DMT_GS_NearKak = HintText::Exclude({
                       //obscure text
                       Text{"a #spider hidden in a mountain nook# holds", "", ""},
  });

  HintText DMT_GS_AboveDodongosCavern = HintText::Exclude({
                       //obscure text
                       Text{"the hammer reveals a #spider on a mountain# holding", "", ""},
  });

  HintText DMT_GS_FallingRocksPath = HintText::Exclude({
                       //obscure text
                       Text{"the hammer reveals a #spider on a mountain# holding", "", ""},
  });


  HintText GC_GS_CenterPlatform = HintText::Exclude({
                       //obscure text
                       Text{"a #suspended spider# in Goron City holds", "", ""},
  });

  HintText GC_GS_BoulderMaze = HintText::Exclude({
                       //obscure text
                       Text{"a spider in a #Goron City crate# holds", "", ""},
  });


  HintText Kak_GS_HouseUnderConstruction = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a town# holding", "", ""},
  });

  HintText Kak_GS_SkulltulaHouse = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a town# holding", "", ""},
  });

  HintText Kak_GS_GuardsHouse = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a town# holding", "", ""},
  });

  HintText Kak_GS_Tree = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a town# holding", "", ""},
  });

  HintText Kak_GS_Watchtower = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a town# holding", "", ""},
  });

  HintText Kak_GS_AboveImpasHouse = HintText::Exclude({
                       //obscure text
                       Text{"night in the future reveals a #spider in a town# holding", "", ""},
  });


  HintText GY_GS_Wall = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider in a graveyard# holding", "", ""},
  });

  HintText GY_GS_BeanPatch = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried in a graveyard# holds", "", ""},
  });


  HintText ZR_GS_Ladder = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a river# holding", "", ""},
  });

  HintText ZR_GS_Tree = HintText::Exclude({
                       //obscure text
                       Text{"a spider hiding in a #tree by a river# holds", "", ""},
  });

  HintText ZR_GS_AboveBridge = HintText::Exclude({
                       //obscure text
                       Text{"night in the future reveals a #spider in a river# holding", "", ""},
  });

  HintText ZR_GS_NearRaisedGrottos = HintText::Exclude({
                       //obscure text
                       Text{"night in the future reveals a #spider in a river# holding", "", ""},
  });


  HintText ZD_GS_FrozenWaterfall = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider by a frozen waterfall# holding", "", ""},
  });

  HintText ZF_GS_AboveTheLog = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider near a deity# holding", "", ""},
  });

  HintText ZF_GS_Tree = HintText::Exclude({
                       //obscure text
                       Text{"a spider hiding in a #tree near a deity# holds", "", ""},
  });


  HintText LH_GS_BeanPatch = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried by a lake# holds", "", ""},
  });

  HintText LH_GS_SmallIsland = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider by a lake# holding", "", ""},
  });

  HintText LH_GS_LabWall = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider by a lake# holding", "", ""},
  });

  HintText LH_GS_LabCrate = HintText::Exclude({
                       //obscure text
                       Text{"a spider deed underwater in a #lab crate# holds", "", ""},
  });

  HintText LH_GS_Tree = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider by a lake high in a tree# holding", "", ""},
  });


  HintText GV_GS_BeanPatch = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried in a valley# holds", "", ""},
  });

  HintText GV_GS_SmallBridge = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a valley# holding", "", ""},
  });

  HintText GV_GS_Pillar = HintText::Exclude({
                       //obscure text
                       Text{"night in the future reveals a #spider in a valley# holding", "", ""},
  });

  HintText GV_GS_BehindTent = HintText::Exclude({
                       //obscure text
                       Text{"night in the future reveals a #spider in a valley# holding", "", ""},
  });


  HintText GF_GS_ArcheryRange = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider in a fortress# holding", "", ""},
  });

  HintText GF_GS_TopFloor = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider in a fortress# holding", "", ""},
  });


  HintText Colossus_GS_BeanPatch = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried in the desert# holds", "", ""},
  });

  HintText Colossus_GS_Hill = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider deep in the desert# holding", "", ""},
  });

  HintText Colossus_GS_Tree = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider deep in the desert# holding", "", ""},
  });


  HintText KF_ShopItem1 = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", "", ""},
  });

  HintText KF_ShopItem2 = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", "", ""},
  });

  HintText KF_ShopItem3 = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", "", ""},
  });

  HintText KF_ShopItem4 = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", "", ""},
  });

  HintText KF_ShopItem5 = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", "", ""},
  });

  HintText KF_ShopItem6 = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", "", ""},
  });

  HintText KF_ShopItem7 = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", "", ""},
  });

  HintText KF_ShopItem8 = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", "", ""},
  });


  HintText Kak_PotionShopItem1 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", "", ""},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", "", ""}
  );

  HintText Kak_PotionShopItem2 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", "", ""},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", "", ""}
  );

  HintText Kak_PotionShopItem3 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", "", ""},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", "", ""}
  );

  HintText Kak_PotionShopItem4 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", "", ""},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", "", ""}
  );

  HintText Kak_PotionShopItem5 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", "", ""},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", "", ""}
  );

  HintText Kak_PotionShopItem6 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", "", ""},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", "", ""}
  );

  HintText Kak_PotionShopItem7 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", "", ""},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", "", ""}
  );

  HintText Kak_PotionShopItem8 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", "", ""},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", "", ""}
  );


  HintText MK_BombchuShopItem1 = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", "", ""},
  });

  HintText MK_BombchuShopItem2 = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", "", ""},
  });

  HintText MK_BombchuShopItem3 = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", "", ""},
  });

  HintText MK_BombchuShopItem4 = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", "", ""},
  });

  HintText MK_BombchuShopItem5 = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", "", ""},
  });

  HintText MK_BombchuShopItem6 = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", "", ""},
  });

  HintText MK_BombchuShopItem7 = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", "", ""},
  });

  HintText MK_BombchuShopItem8 = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", "", ""},
  });


  HintText MK_PotionShopItem1 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", "", ""},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", "", ""}
  );

  HintText MK_PotionShopItem2 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", "", ""},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", "", ""}
  );

  HintText MK_PotionShopItem3 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", "", ""},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", "", ""}
  );

  HintText MK_PotionShopItem4 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", "", ""},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", "", ""}
  );

  HintText MK_PotionShopItem5 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", "", ""},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", "", ""}
  );

  HintText MK_PotionShopItem6 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", "", ""},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", "", ""}
  );

  HintText MK_PotionShopItem7 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", "", ""},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", "", ""}
  );

  HintText MK_PotionShopItem8 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", "", ""},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", "", ""}
  );


  HintText MK_BazaarItem1 = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", "", ""},
  });

  HintText MK_BazaarItem2 = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", "", ""},
  });

  HintText MK_BazaarItem3 = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", "", ""},
  });

  HintText MK_BazaarItem4 = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", "", ""},
  });

  HintText MK_BazaarItem5 = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", "", ""},
  });

  HintText MK_BazaarItem6 = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", "", ""},
  });

  HintText MK_BazaarItem7 = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", "", ""},
  });

  HintText MK_BazaarItem8 = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", "", ""},
  });


  HintText Kak_BazaarItem1 = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", "", ""},
  });

  HintText Kak_BazaarItem2 = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", "", ""},
  });

  HintText Kak_BazaarItem3 = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", "", ""},
  });

  HintText Kak_BazaarItem4 = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", "", ""},
  });

  HintText Kak_BazaarItem5 = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", "", ""},
  });

  HintText Kak_BazaarItem6 = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", "", ""},
  });

  HintText Kak_BazaarItem7 = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", "", ""},
  });

  HintText Kak_BazaarItem8 = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", "", ""},
  });


  HintText ZD_ShopItem1 = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", "", ""},
  });

  HintText ZD_ShopItem2 = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", "", ""},
  });

  HintText ZD_ShopItem3 = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", "", ""},
  });

  HintText ZD_ShopItem4 = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", "", ""},
  });

  HintText ZD_ShopItem5 = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", "", ""},
  });

  HintText ZD_ShopItem6 = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", "", ""},
  });

  HintText ZD_ShopItem7 = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", "", ""},
  });

  HintText ZD_ShopItem8 = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", "", ""},
  });


  HintText GC_ShopItem1 = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", "", ""},
  });

  HintText GC_ShopItem2 = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", "", ""},
  });

  HintText GC_ShopItem3 = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", "", ""},
  });

  HintText GC_ShopItem4 = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", "", ""},
  });

  HintText GC_ShopItem5 = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", "", ""},
  });

  HintText GC_ShopItem6 = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", "", ""},
  });

  HintText GC_ShopItem7 = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", "", ""},
  });

  HintText GC_ShopItem8 = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", "", ""},
  });


  HintText DekuTree_MQ_DekuScrub = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub in the Deku Tree# sells", "", ""},
  });


  HintText HF_DekuScrubGrotto = HintText::Exclude({
                       //obscure text
                       Text{"a lonely #scrub in a hole# sells", "", ""},
  });

  HintText LLR_DekuScrubGrottoLeft = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", "", ""},
  });

  HintText LLR_DekuScrubGrottoRight = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", "", ""},
  });

  HintText LLR_DekuScrubGrottoCenter = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", "", ""},
  });


  HintText LW_DekuScrubNearDekuTheaterRight = HintText::Exclude({
                       //obscure text
                       Text{"a pair of #scrubs in the woods# sells", "", ""},
  });

  HintText LW_DekuScrubNearDekuTheaterLeft = HintText::Exclude({
                       //obscure text
                       Text{"a pair of #scrubs in the woods# sells", "", ""},
  });

  HintText LW_DekuScrubNearBridge = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub by a bridge# sells", "", ""},
  });

  HintText LW_DekuScrubGrottoRear = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", "", ""},
  });

  HintText LW_DekuScrubGrottoFront = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", "", ""},
  });


  HintText SFM_DekuScrubGrottoRear = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", "", ""},
  });

  HintText SFM_DekuScrubGrottoFront = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", "", ""},
  });


  HintText GC_DekuScrubGrottoLeft = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", "", ""},
  });

  HintText GC_DekuScrubGrottoRight = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", "", ""},
  });

  HintText GC_DekuScrubGrottoCenter = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", "", ""},
  });


  HintText DodongosCavern_DekuScrubNearBombBagLeft = HintText::Exclude({
                       //obscure text
                       Text{"a pair of #scrubs in Dodongo's Cavern# sells", "", ""},
  });

  HintText DodongosCavern_DekuScrubSideRoomNearDodongos = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub guarded by Lizalfos# sells", "", ""},
  });

  HintText DodongosCavern_DekuScrubNearBombBagRight = HintText::Exclude({
                       //obscure text
                       Text{"a pair of #scrubs in Dodongo's Cavern# sells", "", ""},
  });

  HintText DodongosCavern_DekuScrubLobby = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub in Dodongo's Cavern# sells", "", ""},
  });


  HintText DodongosCavern_MQ_DekuScrubLobbyRear = HintText::Exclude({
                       //obscure text
                       Text{"a pair of #scrubs in Dodongo's Cavern# sells", "", ""},
  });

  HintText DodongosCavern_MQ_DekuScrubLobbyFront = HintText::Exclude({
                       //obscure text
                       Text{"a pair of #scrubs in Dodongo's Cavern# sells", "", ""},
  });

  HintText DodongosCavern_MQ_DekuScrubStaircase = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub in Dodongo's Cavern# sells", "", ""},
  });

  HintText DodongosCavern_MQ_DekuScrubSideRoomNearLowerLizalfos = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub guarded by Lizalfos# sells", "", ""},
  });


  HintText DMC_DekuScrubGrottoLeft = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", "", ""},
  });

  HintText DMC_DekuScrubGrottoRight = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", "", ""},
  });

  HintText DMC_DekuScrubGrottoCenter = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", "", ""},
  });


  HintText ZR_DekuScrubGrottoRear = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", "", ""},
  });

  HintText ZR_DekuScrubGrottoFront = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", "", ""},
  });


  HintText JabuJabusBelly_DekuScrub = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub in a deity# sells", "", ""},
  });


  HintText LH_DekuScrubGrottoLeft = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", "", ""},
  });

  HintText LH_DekuScrubGrottoRight = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", "", ""},
  });

  HintText LH_DekuScrubGrottoCenter = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", "", ""},
  });


  HintText GV_DekuScrubGrottoRear = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", "", ""},
  });

  HintText GV_DekuScrubGrottoFront = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", "", ""},
  });


  HintText Colossus_DekuScrubGrottoFront = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", "", ""},
  });

  HintText Colossus_DekuScrubGrottoRear = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", "", ""},
  });


  HintText GanonsCastle_DekuScrubCenterLeft = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", "", ""},
  });

  HintText GanonsCastle_DekuScrubCenterRight = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", "", ""},
  });

  HintText GanonsCastle_DekuScrubRight = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", "", ""},
  });

  HintText GanonsCastle_DekuScrubLeft = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", "", ""},
  });


  HintText GanonsCastle_MQ_DekuScrubRight = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", "", ""},
  });

  HintText GanonsCastle_MQ_DekuScrubCenterLeft = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", "", ""},
  });

  HintText GanonsCastle_MQ_DekuScrubCenter = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", "", ""},
  });

  HintText GanonsCastle_MQ_DekuScrubCenterRight = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", "", ""},
  });

  HintText GanonsCastle_MQ_DekuScrubLeft = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", "", ""},
  });


  HintText LLR_StablesLeftCow = HintText::Exclude({
                       //obscure text
                       Text{"a #cow in a stable# gifts", "", ""},
  });

  HintText LLR_StablesRightCow = HintText::Exclude({
                       //obscure text
                       Text{"a #cow in a stable# gifts", "", ""},
  });

  HintText LLR_TowerRightCow = HintText::Exclude({
                       //obscure text
                       Text{"a #cow in a ranch silo# gifts", "", ""},
  });

  HintText LLR_TowerLeftCow = HintText::Exclude({
                       //obscure text
                       Text{"a #cow in a ranch silo# gifts", "", ""},
  });

  HintText Kak_ImpasHouseCow = HintText::Exclude({
                       //obscure text
                       Text{"a #cow imprisoned in a house# protects", "", ""},
  });

  HintText DMT_CowGrottoCow = HintText::Exclude({
                       //obscure text
                       Text{"a #cow in a luxurious hole# offers", "", ""},
  });

  /*--------------------------
  |    ENTRANCE HINT TEXT    |
  ---------------------------*/

  HintText DesertColossus_To_ColossusGrotto = HintText::Entrance({
                     //obscure text
                     Text{"lifting a #rock in the desert# reveals", "", ""},
  });

  HintText GVGrottoLedge_To_GVOctorokGrotto = HintText::Entrance({
                     //obscure text
                     Text{"a rock on #a ledge in the valley# hides", "", ""},
  });

  HintText GCGrottoPlatform_To_GCGrotto = HintText::Entrance({
                     //obscure text
                     Text{"a #pool of lava# in Goron City blocks the way to", "", ""},
  });

  HintText GerudoFortress_To_GFStormsGrotto = HintText::Entrance({
                     //obscure text
                     Text{"a #storm within Gerudo's Fortress# reveals", "", ""},
  });

  HintText ZorasDomain_To_ZDStormsGrotto = HintText::Entrance({
                     //obscure text
                     Text{"a #storm within Zora's Domain# reveals", "", ""},
  });

  HintText HyruleCastleGrounds_To_HCStormsGrotto = HintText::Entrance({
                     //obscure text
                     Text{"a #storm near the castle# reveals", "", ""},
  });

  HintText GVFortressSide_To_GVStormsGrotto = HintText::Entrance({
                     //obscure text
                     Text{"a #storm in the valley# reveals", "", ""},
  });

  HintText DesertColossus_To_ColossusGreatFairyFountain = HintText::Entrance({
                     //obscure text
                     Text{"a #fractured desert wall# hides", "", ""},
  });

  HintText GanonsCastleGrounds_To_OGCGreatFairyFountain = HintText::Entrance({
                     //obscure text
                     Text{"a #heavy pillar# outside the castle obstructs", "", ""},
  });

  HintText ZorasFountain_To_ZFGreatFairyFountain = HintText::Entrance({
                     //obscure text
                     Text{"a #fountain wall# hides", "", ""},
  });

  HintText GVFortressSide_To_GVCarpenterTent = HintText::Entrance({
                     //obscure text
                     Text{"a #tent in the valley# covers", "", ""},
  });

  HintText GYWarpPadRegion_To_ShadowTempleEntryway = HintText::Entrance({
                     //obscure text
                     Text{"at the #back of the Graveyard#, there is", "", ""},
  });

  HintText LakeHylia_To_WaterTempleLobby = HintText::Entrance({
                     //obscure text
                     Text{"deep #under a vast lake#, one can find", "", ""},
  });

  HintText GerudoFortress_To_GerudoTrainingGroundsLobby = HintText::Entrance({
                     //obscure text
                     Text{"paying a #fee to the Gerudos# grants access to", "", ""},
  });

  HintText ZorasFountain_To_JabuJabusBellyBeginning = HintText::Entrance({
                     //obscure text
                     Text{"inside #Jabu Jabu#, one can find", "", ""},
  });

  HintText KakarikoVillage_To_BottomOfTheWell = HintText::Entrance({
                     //obscure text
                     Text{"a #village well# leads to", "", ""},
  });

  /*--------------------------
  |      EXIT HINT TEXT      |
  ---------------------------*/
  //maybe make a new type for this? I'm not sure if it really matters

  HintText LinksPocket = HintText::Exclude({
                     //obscure text
                     Text{"Link's Pocket", "", ""},
  });

  HintText KokiriForest = HintText::Exclude({
                     //obscure text
                     Text{"Kokiri Forest", "", ""},
  });

  HintText TheLostWoods = HintText::Exclude({
                     //obscure text
                     Text{"the Lost Woods", "", ""},
  });

  HintText SacredForestMeadow = HintText::Exclude({
                     //obscure text
                     Text{"Sacred Forest Meadow", "", ""},
  });

  HintText HyruleField = HintText::Exclude({
                     //obscure text
                     Text{"Hyrule Field", "", ""},
  });

  HintText LakeHylia = HintText::Exclude({
                     //obscure text
                     Text{"Lake Hylia", "", ""},
  });

  HintText GerudoValley = HintText::Exclude({
                     //obscure text
                     Text{"Gerudo Valley", "", ""},
  });

  HintText GerudosFortress = HintText::Exclude({
                     //obscure text
                     Text{"Gerudo's Fortress", "", ""},
  });

  HintText HauntedWasteland = HintText::Exclude({
                     //obscure text
                     Text{"Haunted Wasteland", "", ""},
  });

  HintText DesertColossus = HintText::Exclude({
                     //obscure text
                     Text{"Desert Colossus", "", ""},
  });

  HintText TheMarket = HintText::Exclude({
                     //obscure text
                     Text{"the Market", "", ""},
  });

  HintText TempleOfTime = HintText::Exclude({
                     //obscure text
                     Text{"Temple of Time", "", ""},
  });

  HintText HyruleCastle = HintText::Exclude({
                     //obscure text
                     Text{"Hyrule Castle", "", ""},
  });

  HintText OutsideGanonsCastle = HintText::Exclude({
                     //obscure text
                     Text{"outside Ganon's Castle", "", ""},
  });

  HintText KakarikoVillage = HintText::Exclude({
                     //obscure text
                     Text{"Kakariko Village", "", ""},
  });

  HintText TheGraveyard = HintText::Exclude({
                     //obscure text
                     Text{"the Graveyard", "", ""},
  });

  HintText DeathMountainTrail = HintText::Exclude({
                     //obscure text
                     Text{"Death Mountain Trail", "", ""},
  });

  HintText GoronCity = HintText::Exclude({
                     //obscure text
                     Text{"Goron City", "", ""},
  });

  HintText DeathMountainCrater = HintText::Exclude({
                     //obscure text
                     Text{"Death Mountain Crater", "", ""},
  });

  HintText ZorasRiver = HintText::Exclude({
                     //obscure text
                     Text{"Zora's River", "", ""},
  });

  HintText ZorasDomain = HintText::Exclude({
                     //obscure text
                     Text{"Zora's Domain", "", ""},
  });

  HintText ZorasFountain = HintText::Exclude({
                     //obscure text
                     Text{"Zora's Fountain", "", ""},
  });

  HintText LonLonRanch = HintText::Exclude({
                     //obscure text
                     Text{"Lon Lon Ranch", "", ""},
  });


  /*--------------------------
  |     REGION HINT TEXT     |
  ---------------------------*/

  HintText KF_LinksHouse = HintText::Region({
                     //obscure text
                     Text{"Link's House", "", ""},
  });

  HintText ToT_Main = HintText::Region({
                     //obscure text
                     Text{"the #Temple of Time#", "", ""},
  });

  HintText KF_MidosHouse = HintText::Region({
                     //obscure text
                     Text{"Mido's house", "", ""},
  });

  HintText KF_SariasHouse = HintText::Region({
                     //obscure text
                     Text{"Saria's House", "", ""},
  });

  HintText KF_HouseOfTwins = HintText::Region({
                     //obscure text
                     Text{"the #House of Twins#", "", ""},
  });

  HintText KF_KnowItAllHouse = HintText::Region({
                     //obscure text
                     Text{"Know-It-All Brothers' House", "", ""},
  });

  HintText KF_KokiriShop = HintText::Region({
                     //obscure text
                     Text{"the #Kokiri Shop#", "", ""},
  });

  HintText LH_Lab = HintText::Region({
                     //obscure text
                     Text{"the #Lakeside Laboratory#", "", ""},
  });

  HintText LH_FishingHole = HintText::Region({
                     //obscure text
                     Text{"the #Fishing Pond#", "", ""},
  });

  HintText GV_CarpenterTent = HintText::Region({
                     //obscure text
                     Text{"the #Carpenters' tent#", "", ""},
  });

  HintText MK_GuardHouse = HintText::Region({
                     //obscure text
                     Text{"the #Guard House#", "", ""},
  });

  HintText MK_MaskShop = HintText::Region({
                     //obscure text
                     Text{"the #Happy Mask Shop#", "", ""},
  });

  HintText MK_BombchuBowling = HintText::Region({
                     //obscure text
                     Text{"the #Bombchu Bowling Alley#", "", ""},
  });

  HintText MK_PotionShop = HintText::Region({
                     //obscure text
                     Text{"the #Market Potion Shop#", "", ""},
  });

  HintText MK_TreasureChestGame = HintText::Region({
                     //obscure text
                     Text{"the #Treasure Box Shop#", "", ""},
  });

  HintText MK_BombchuShop = HintText::Region({
                     //obscure text
                     Text{"the #Bombchu Shop#", "", ""},
  });

  HintText MK_ManInGreenHouse = HintText::Region({
                     //obscure text
                     Text{"Man in Green's House", "", ""},
  });

  HintText Kak_Windmill = HintText::Region({
                     //obscure text
                     Text{"the #Windmill#", "", ""},
  });

  HintText Kak_CarpenterBossHouse = HintText::Region({
                     //obscure text
                     Text{"the #Carpenters' Boss House#", "", ""},
  });

  HintText Kak_HouseOfSkulltula = HintText::Region({
                     //obscure text
                     Text{"the #House of Skulltula#", "", ""},
  });

  HintText Kak_ImpasHouse = HintText::Region({
                     //obscure text
                     Text{"Impa's House", "", ""},
  });

  HintText Kak_ImpasHouseBack = HintText::Region({
                     //obscure text
                     Text{"Impa's cow cage", "", ""},
  });

  HintText Kak_OddMedicineBuilding = HintText::Region({
                     //obscure text
                     Text{"Granny's Potion Shop", "", ""},
  });

  HintText GY_DampesHouse = HintText::Region({
                     //obscure text
                     Text{"Dampe's Hut", "", ""},
  });

  HintText GC_Shop = HintText::Region({
                     //obscure text
                     Text{"the #Goron Shop#", "", ""},
  });

  HintText ZD_Shop = HintText::Region({
                     //obscure text
                     Text{"the #Zora Shop#", "", ""},
  });

  HintText LLR_TalonsHouse = HintText::Region({
                     //obscure text
                     Text{"Talon's House", "", ""},
  });

  HintText LLR_Stables = HintText::Region({
                     //obscure text
                     Text{"a #stable#", "", ""},
  });

  HintText LLR_Tower = HintText::Region({
                     //obscure text
                     Text{"the #Lon Lon Tower#", "", ""},
  });

  HintText MK_Bazaar = HintText::Region({
                     //obscure text
                     Text{"the #Market Bazaar#", "", ""},
  });

  HintText MK_ShootingGallery = HintText::Region({
                     //obscure text
                     Text{"a #Slingshot Shooting Gallery#", "", ""},
  });

  HintText Kak_Bazaar = HintText::Region({
                     //obscure text
                     Text{"the #Kakariko Bazaar#", "", ""},
  });

  HintText Kak_PotionShopFront = HintText::Region({
                     //obscure text
                     Text{"the #Kakariko Potion Shop#", "", ""},
  });

  HintText Kak_PotionShopBack = HintText::Region({
                     //obscure text
                     Text{"the #Kakariko Potion Shop#", "", ""},
  });

  HintText Kak_ShootingGallery = HintText::Region({
                     //obscure text
                     Text{"a #Bow Shooting Gallery#", "", ""},
  });

  HintText Colossus_GreatFairyFountain = HintText::Region({
                     //obscure text
                     Text{"a #Great Fairy Fountain#", "", ""},
  });

  HintText HC_GreatFairyFountain = HintText::Region({
                     //obscure text
                     Text{"a #Great Fairy Fountain#", "", ""},
  });

  HintText OGC_GreatFairyFountain = HintText::Region({
                     //obscure text
                     Text{"a #Great Fairy Fountain#", "", ""},
  });

  HintText DMC_GreatFairyFountain = HintText::Region({
                     //obscure text
                     Text{"a #Great Fairy Fountain#", "", ""},
  });

  HintText DMT_GreatFairyFountain = HintText::Region({
                     //obscure text
                     Text{"a #Great Fairy Fountain#", "", ""},
  });

  HintText ZF_GreatFairyFountain = HintText::Region({
                     //obscure text
                     Text{"a #Great Fairy Fountain#", "", ""},
  });

  HintText GY_ShieldGrave = HintText::Region({
                     //obscure text
                     Text{"a #grave with a free chest#", "", ""},
  });

  HintText GY_HeartPieceGrave = HintText::Region({
                     //obscure text
                     Text{"a chest spawned by #Sun's Song#", "", ""},
  });

  HintText GY_ComposersGrave = HintText::Region({
                     //obscure text
                     Text{"the #Composers' Grave#", "", ""},
  });

  HintText GY_DampesGrave = HintText::Region({
                     //obscure text
                     Text{"Dampe's Grave", "", ""},
  });

  HintText DMT_CowGrotto = HintText::Region({
                     //obscure text
                     Text{"a solitary #Cow#", "", ""},
  });

  HintText HC_StormsGrotto = HintText::Region({
                     //obscure text
                     Text{"a sandy grotto with #fragile walls#", "", ""},
  });

  HintText HF_TektiteGrotto = HintText::Region({
                     //obscure text
                     Text{"a pool guarded by a #Tektite#", "", ""},
  });

  HintText HF_NearKakGrotto = HintText::Region({
                     //obscure text
                     Text{"a #Big Skulltula# guarding a Gold one", "", ""},
  });

  HintText HF_CowGrotto = HintText::Region({
                     //obscure text
                     Text{"a grotto full of #spider webs#", "", ""},
  });

  HintText Kak_RedeadGrotto = HintText::Region({
                     //obscure text
                     Text{"#ReDeads# guarding a chest", "", ""},
  });

  HintText SFM_WolfosGrotto = HintText::Region({
                     //obscure text
                     Text{"#Wolfos# guarding a chest", "", ""},
  });

  HintText GV_OctorokGrotto = HintText::Region({
                     //obscure text
                     Text{"an #Octorok# guarding a rich pool", "", ""},
  });

  HintText DekuTheater = HintText::Region({
                     //obscure text
                     Text{"the #Lost Woods Stage#", "", ""},
  });

  HintText ZR_OpenGrotto = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", "", ""},
  });

  HintText DMC_UpperGrotto = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", "", ""},
  });

  HintText DMT_StormsGrotto = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", "", ""},
  });

  HintText Kak_OpenGrotto = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", "", ""},
  });

  HintText HF_NearMKGrotto = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", "", ""},
  });

  HintText HF_OpenGrotto = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", "", ""},
  });

  HintText HF_SoutheastGrotto = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", "", ""},
  });

  HintText KF_StormsGrotto = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", "", ""},
  });

  HintText LW_NearShortcutsGrotto = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", "", ""},
  });

  HintText HF_InsideFenceGrotto = HintText::Region({
                     //obscure text
                     Text{"a #single Upgrade Deku Scrub#", "", ""},
  });

  HintText LW_ScrubsGrotto = HintText::Region({
                     //obscure text
                     Text{"#2 Deku Scrubs# including an Upgrade one", "", ""},
  });

  HintText Colossus_Grotto = HintText::Region({
                     //obscure text
                     Text{"2 Deku Scrubs", "", ""},
  });

  HintText ZR_StormsGrotto = HintText::Region({
                     //obscure text
                     Text{"2 Deku Scrubs", "", ""},
  });

  HintText SFM_StormsGrotto = HintText::Region({
                     //obscure text
                     Text{"2 Deku Scrubs", "", ""},
  });

  HintText GV_StormsGrotto = HintText::Region({
                     //obscure text
                     Text{"2 Deku Scrubs", "", ""},
  });

  HintText LH_Grotto = HintText::Region({
                     //obscure text
                     Text{"3 Deku Scrubs", "", ""},
  });

  HintText DMC_HammerGrotto = HintText::Region({
                     //obscure text
                     Text{"3 Deku Scrubs", "", ""},
  });

  HintText GC_Grotto = HintText::Region({
                     //obscure text
                     Text{"3 Deku Scrubs", "", ""},
  });

  HintText LLR_Grotto = HintText::Region({
                     //obscure text
                     Text{"3 Deku Scrubs", "", ""},
  });

  HintText ZR_FairyGrotto = HintText::Region({
                     //obscure text
                     Text{"a small #Fairy Fountain#", "", ""},
  });

  HintText HF_FairyGrotto = HintText::Region({
                     //obscure text
                     Text{"a small #Fairy Fountain#", "", ""},
  });

  HintText SFM_FairyGrotto = HintText::Region({
                     //obscure text
                     Text{"a small #Fairy Fountain#", "", ""},
  });

  HintText ZD_StormsGrotto = HintText::Region({
                     //obscure text
                     Text{"a small #Fairy Fountain#", "", ""},
  });

  HintText GF_StormsGrotto = HintText::Region({
                     //obscure text
                     Text{"a small #Fairy Fountain#", "", ""},
  });

  /*--------------------------
  |      JUNK HINT TEXT      |
  ---------------------------*/

  HintText Junk01 = HintText::Junk({
                     //obscure text
                     Text{"Ganondorf 2022!", "", ""},
  });

  HintText Junk02 = HintText::Junk({
                     //obscure text
                     Text{"They say that monarchy is a terrible system of governance.", "", ""},
  });

  HintText Junk03 = HintText::Junk({
                     //obscure text
                     Text{"They say that Zelda is a poor leader.", "", ""},
  });

  HintText Junk04 = HintText::Junk({
                     //obscure text
                     Text{"These hints can be quite useful. This is an exception.", "", ""},
  });

  HintText Junk06 = HintText::Junk({
                     //obscure text
                     Text{"They say that all the Zora drowned in Wind Waker.", "", ""},
  });

  HintText Junk08 = HintText::Junk({
                     //obscure text
                     Text{"'Member when Ganon was a blue pig?^I 'member.", "", ""},
  });

  HintText Junk09 = HintText::Junk({
                     //obscure text
                     Text{"One who does not have Triforce can't go in.", "", ""},
  });

  HintText Junk10 = HintText::Junk({
                     //obscure text
                     Text{"Save your future, end the Happy Mask Salesman.", "", ""},
  });

  HintText Junk12 = HintText::Junk({
                     //obscure text
                     Text{"I'm stoned. Get it?", "", ""},
  });

  HintText Junk13 = HintText::Junk({
                     //obscure text
                     Text{"Hoot! Hoot! Would you like me to repeat that?", "", ""},
  });

  HintText Junk14 = HintText::Junk({
                     //obscure text
                     Text{"Gorons are stupid. They eat rocks.", "", ""},
  });

  HintText Junk15 = HintText::Junk({
                     //obscure text
                     Text{"They say that Lon Lon Ranch prospered under Ingo.", "", ""},
  });

  HintText Junk16 = HintText::Junk({
                     //obscure text
                     Text{"The single rupee is a unique item.", "", ""},
  });

  HintText Junk17 = HintText::Junk({
                     //obscure text
                     Text{"Without the Lens of Truth, the Treasure Chest Mini-Game is a 1 out of 32 chance.^Good luck!", "", ""},
  });

  HintText Junk18 = HintText::Junk({
                     //obscure text
                     Text{"Use bombs wisely.", "", ""},
  });

  HintText Junk21 = HintText::Junk({
                     //obscure text
                     Text{"I found you, faker!", "", ""},
  });

  HintText Junk22 = HintText::Junk({
                     //obscure text
                     Text{"You're comparing yourself to me?^Ha! You're not even good enough to be my fake.", "", ""},
  });

  HintText Junk23 = HintText::Junk({
                     //obscure text
                     Text{"I'll make you eat those words.", "", ""},
  });

  HintText Junk24 = HintText::Junk({
                     //obscure text
                     Text{"What happened to Sheik?", "", ""},
  });

  HintText Junk25 = HintText::Junk({
                     //obscure text
                     Text{"L2P @.", "", ""},
  });

  HintText Junk26 = HintText::Junk({
                     //obscure text
                     Text{"I've heard Sploosh Kaboom is a tricky game.", "", ""},
  });

  HintText Junk27 = HintText::Junk({
                     //obscure text
                     Text{"I'm Lonk from Pennsylvania.", "", ""},
  });

  HintText Junk28 = HintText::Junk({
                     //obscure text
                     Text{"I bet you'd like to have more bombs.", "", ""},
  });

  HintText Junk29 = HintText::Junk({
                     //obscure text
                     Text{"When all else fails, use Fire.", "", ""},
  });

  HintText Junk30 = HintText::Junk({
                     //obscure text
                     Text{"Here's a hint, @. Don't be bad.", "", ""},
  });

  HintText Junk31 = HintText::Junk({
                     //obscure text
                     Text{"Game Over. Return of Ganon.", "", ""},
  });

  HintText Junk32 = HintText::Junk({
                     //obscure text
                     Text{"May the way of the Hero lead to the Triforce.", "", ""},
  });

  HintText Junk33 = HintText::Junk({
                     //obscure text
                     Text{"Can't find an item? Scan an Amiibo.", "", ""},
  });

  HintText Junk34 = HintText::Junk({
                     //obscure text
                     Text{"They say this game has just a few glitches.", "", ""},
  });

  HintText Junk35 = HintText::Junk({
                     //obscure text
                     Text{"BRRING BRRING This is Ulrira. Wrong number?", "", ""},
  });

  HintText Junk36 = HintText::Junk({
                     //obscure text
                     Text{"Tingle Tingle Kooloo Limpah", "", ""},
  });

  HintText Junk37 = HintText::Junk({
                     //obscure text
                     Text{"L is real 2041", "", ""},
  });

  HintText Junk38 = HintText::Junk({
                     //obscure text
                     Text{"They say that Ganondorf will appear in the next Mario Tennis.", "", ""},
  });

  HintText Junk39 = HintText::Junk({
                     //obscure text
                     Text{"Medigoron sells the earliest Breath of the Wild demo.", "", ""},
  });

  HintText Junk40 = HintText::Junk({
                     //obscure text
                     Text{"There's a reason why I am special inquisitor!", "", ""},
  });

  HintText Junk41 = HintText::Junk({
                     //obscure text
                     Text{"You were almost a @ sandwich.", "", ""},
  });

  HintText Junk42 = HintText::Junk({
                     //obscure text
                     Text{"I'm a helpful hint Gossip Stone!^See, I'm helping.", "", ""},
  });

  HintText Junk43 = HintText::Junk({
                     //obscure text
                     Text{"Dear @, please come to the castle. I've baked a cake for you.&Yours truly, princess Zelda.", "", ""},
  });

  HintText Junk44 = HintText::Junk({
                     //obscure text
                     Text{"They say all toasters toast toast.", "", ""},
  });

  HintText Junk45 = HintText::Junk({
                     //obscure text
                     Text{"They say that Okami is the best Zelda game.", "", ""},
  });

  HintText Junk46 = HintText::Junk({
                     //obscure text
                     Text{"They say that quest guidance can be found at a talking rock.", "", ""},
  });

  HintText Junk47 = HintText::Junk({
                     //obscure text
                     Text{"They say that the final item you're looking for can be found somewhere in Hyrule.", "", ""},
  });

  HintText Junk48 = HintText::Junk({
                     //obscure text
                     Text{"Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.", "", ""},
  });

  HintText Junk49 = HintText::Junk({
                     //obscure text
                     Text{"They say that Barinade fears Deku Nuts.", "", ""},
  });

  HintText Junk50 = HintText::Junk({
                     //obscure text
                     Text{"They say that Flare Dancers do not fear Goron-crafted blades.", "", ""},
  });

  HintText Junk51 = HintText::Junk({
                     //obscure text
                     Text{"They say that Morpha is easily trapped in a corner.", "", ""},
  });

  HintText Junk52 = HintText::Junk({
                     //obscure text
                     Text{"They say that Bongo Bongo really hates the cold.", "", ""},
  });

  HintText Junk53 = HintText::Junk({
                     //obscure text
                     Text{"They say that your sword is most powerful when you put it away.", "", ""},
  });

  HintText Junk54 = HintText::Junk({
                     //obscure text
                     Text{"They say that bombing the hole Volvagia last flew into can be rewarding.", "", ""},
  });

  HintText Junk55 = HintText::Junk({
                     //obscure text
                     Text{"They say that invisible ghosts can be exposed with Deku Nuts.", "", ""},
  });

  HintText Junk56 = HintText::Junk({
                     //obscure text
                     Text{"They say that the real Phantom Ganon is bright and loud.", "", ""},
  });

  HintText Junk57 = HintText::Junk({
                     //obscure text
                     Text{"They say that walking backwards is very fast.", "", ""},
  });

  HintText Junk58 = HintText::Junk({
                     //obscure text
                     Text{"They say that leaping above the Market entrance enriches most children.", "", ""},
  });

  HintText Junk59 = HintText::Junk({
                     //obscure text
                     Text{"They say that looking into darkness may find darkness looking back into you.", "", ""},
  });

  HintText Junk60 = HintText::Junk({
                     //obscure text
                     Text{"You found a spiritual Stone! By which I mean, I worship Nayru.", "", ""},
  });

  HintText Junk61 = HintText::Junk({
                     //obscure text
                     Text{"They say that the stick is mightier than the sword...^At least, it used to be...", "", ""},
  });

  HintText Junk62 = HintText::Junk({
                     //obscure text
                     Text{"Open your eyes.^Open your eyes.^Wake up, @.", "", ""},
  });

  HintText Junk63 = HintText::Junk({
                     //obscure text
                     Text{"They say that the Nocturne of Shadow can bring you very close to Ganon.", "", ""},
  });

  HintText Junk64 = HintText::Junk({
                     //obscure text
                     Text{"They say that Twinrova always casts the same spell the first three times.", "", ""},
  });

  HintText Junk65 = HintText::Junk({
                     //obscure text
                     Text{"They say that the nightly builds may be unstable.", "", ""},
  });

  HintText Junk66 = HintText::Junk({
                     //obscure text
                     Text{"You're playing a Randomizer. I'm randomized!^Here's a random number:  #4#.&Enjoy your Randomizer!", "", ""},
  });

  HintText Junk67 = HintText::Junk({
                     //obscure text
                     Text{"They say Ganondorf's bolts can be reflected with glass or steel.", "", ""},
  });

  HintText Junk68 = HintText::Junk({
                     //obscure text
                     Text{"They say Ganon's tail is vulnerable to nuts, arrows, swords, explosives, hammers...^...sticks, seeds, boomerangs...^...rods, shovels, iron balls, angry bees...", "", ""},
  });

  HintText Junk69 = HintText::Junk({
                     //obscure text
                     Text{"They say that you're wasting time reading this hint, but I disagree. Talk to me again!", "", ""},
  });

  HintText Junk70 = HintText::Junk({
                     //obscure text
                     Text{"They say Ganondorf knows where to find the instrument of his doom.", "", ""},
  });

  HintText Junk71 = HintText::Junk({
                     //obscure text
                     Text{"I heard @ is pretty good at Zelda.", "", ""},
  });

  /*--------------------------
  |     DUNGEON HINT TEXT    |
  ---------------------------*/

  HintText DekuTree = HintText::DungeonName({
                     //obscure text
                     Text{"an ancient tree", "", ""},
                   },
                     //clear text
                     Text{"Deku Tree", "", ""}
  );

  HintText DodongosCavern = HintText::DungeonName({
                     //obscure text
                     Text{"an immense cavern", "", ""},
                   },
                     //clear text
                     Text{ "Dodongo's Cavern", "", ""}
  );

  HintText JabuJabusBelly = HintText::DungeonName({
                     //obscure text
                     Text{"the belly of a deity", "", ""},
                   },
                     //clear text
                     Text{ "Jabu Jabu's Belly", "", ""}
  );

  HintText ForestTemple = HintText::DungeonName({
                     //obscure text
                     Text{"a deep forest", "", ""},
                   },
                     //clear text
                     Text{ "Forest Temple", "", ""}
  );

  HintText FireTemple = HintText::DungeonName({
                     //obscure text
                     Text{"a high mountain", "", ""},
                   },
                     //clear text
                     Text{ "Fire Temple", "", ""}
  );

  HintText WaterTemple = HintText::DungeonName({
                     //obscure text
                     Text{"a vast lake", "", ""},
                   },
                     //clear text
                     Text{ "Water Temple", "", ""}
  );

  HintText ShadowTemple = HintText::DungeonName({
                     //obscure text
                     Text{"the house of the dead", "", ""},
                   },
                     //clear text
                     Text{ "Shadow Temple", "", ""}
  );

  HintText SpiritTemple = HintText::DungeonName({
                     //obscure text
                     Text{"the goddess of the sand", "", ""},
                   },
                     //clear text
                     Text{ "Spirit Temple", "", ""}
  );

  HintText IceCavern = HintText::DungeonName({
                     //obscure text
                     Text{"a frozen maze", "", ""},
                   },
                     //clear text
                     Text{ "Ice Cavern", "", ""}
  );

  HintText BottomOfTheWell = HintText::DungeonName({
                     //obscure text
                     Text{"a shadow\'s prison", "", ""},
                   },
                     //clear text
                     Text{ "Bottom of the Well", "", ""}
  );

  HintText GerudoTrainingGrounds = HintText::DungeonName({
                     //obscure text
                     Text{"the test of thieves", "", ""},
                   },
                     //clear text
                     Text{ "Gerudo Training Grounds", "", ""}
  );

  HintText GanonsCastle = HintText::DungeonName({
                     //obscure text
                     Text{"a conquered citadel", "", ""},
                   },
                     //clear text
                     Text{ "Inside Ganon's Castle", "", ""}
  );

  /*--------------------------
  |      BOSS HINT TEXT      |
  ---------------------------*/

  HintText QueenGohma = HintText::Boss({
                     //obscure text
                     Text{"One inside an #ancient tree#...", "", ""},
                   },
                     //clear text
                     Text{ "One in the #Deku Tree#...", "", ""}
  );

  HintText KingDodongo = HintText::Boss({
                     //obscure text
                     Text{"One within an #immense cavern#...", "", ""},
                   },
                     //clear text
                     Text{ "One in #Dodongo's Cavern#...", "", ""}
  );

  HintText Barinade = HintText::Boss({
                     //obscure text
                     Text{"One in the #belly of a deity#...", "", ""},
                   },
                     //clear text
                     Text{ "One in #Jabu Jabu's Belly#...", "", ""}
  );

  HintText PhantomGanon = HintText::Boss({
                     //obscure text
                     Text{"One in a #deep forest#...", "", ""},
                   },
                     //clear text
                     Text{ "One in the #Forest Temple#...", "", ""}
  );

  HintText Volvagia = HintText::Boss({
                     //obscure text
                     Text{"One on a #high mountain#...", "", ""},
                   },
                     //clear text
                     Text{ "One in the #Fire Temple#...", "", ""}
  );

  HintText Morpha = HintText::Boss({
                     //obscure text
                     Text{"One under a #vast lake#...", "", ""},
                   },
                     //clear text
                     Text{ "One in the #Water Temple#...", "", ""}
  );

  HintText BongoBongo = HintText::Boss({
                     //obscure text
                     Text{"One within the #house of the dead#...", "", ""},
                   },
                     //clear text
                     Text{ "One in the #Shadow Temple#...", "", ""}
  );

  HintText Twinrova = HintText::Boss({
                     //obscure text
                     Text{"One inside a #goddess of the sand#...", "", ""},
                   },
                     //clear text
                     Text{ "One in the #Spirit Temple#...", "", ""}
  );

  HintText LinksPocketBoss = HintText::Boss({
                     //obscure text
                     Text{"One in #@'s pocket#...", "", ""},
                   },
                     //clear text
                     Text{ "One #@ already has#...", "", ""}
  );

  /*--------------------------
  |     BRIDGE HINT TEXT     |
  ---------------------------*/

  HintText BridgeVanilla = HintText::Bridge({
                     //obscure text
                     Text{"the #Shadow and Spirit Medallions# as well as the #Light Arrows#", "", ""},
  });

  HintText BridgeStones = HintText::Bridge({
                     //obscure text
                     Text{"Spiritual Stones", "", ""},
  });

  HintText BridgeMedallions = HintText::Bridge({
                     //obscure text
                     Text{"Medallions", "", ""},
  });

  HintText BridgeRewards = HintText::Bridge({
                     //obscure text
                     Text{"Spiritual Stones and Medallions", "", ""},
  });

  HintText BridgeDungeons = HintText::Bridge({
                     //obscure text
                     Text{"Completed Dungeons", "", ""},
  });

  HintText BridgeTokens = HintText::Bridge({
                     //obscure text
                     Text{"Gold Skulltula Tokens", "", ""},
  });

  /*--------------------------
  | GANON BOSS KEY HINT TEXT |
  ---------------------------*/

  HintText GanonBKVanilla = HintText::GanonsBossKey({
                     //obscure text
                     Text{"kept in a big chest #inside its tower#", "", ""},
  });

  HintText GanonBKOwnDungeon = HintText::GanonsBossKey({
                     //obscure text
                     Text{"hidden somewhere #inside its castle#", "", ""},
  });

  HintText GanonBKOverworld = HintText::GanonsBossKey({
                     //obscure text
                     Text{"hidden #outside of dungeons# in Hyrule", "", ""},
  });

  HintText GanonBKAnyDungeon = HintText::GanonsBossKey({
                     //obscure text
                     Text{"hidden #inside a dungeon# in Hyrule", "", ""},
  });

  HintText GanonBKKeysanity = HintText::GanonsBossKey({
                     //obscure text
                     Text{"hidden somewhere #in Hyrule#", "", ""},
  });

  HintText GanonBKTriforce = HintText::GanonsBossKey({
                     //obscure text
                     Text{"given to the Hero once the #Triforce# is completed", "", ""},
  });

  /*--------------------------
  |      LACS HINT TEXT      |
  ---------------------------*/

  HintText LACSVanilla = HintText::LACS({
                     //obscure text
                     Text{"the #Shadow and Spirit Medallions#", "", ""},
  });

  HintText LACSMedallions = HintText::LACS({
                     //obscure text
                     Text{"Medallions", "", ""},
  });

  HintText LACSStones = HintText::LACS({
                     //obscure text
                     Text{"Spiritual Stones", "", ""},
  });

  HintText LACSRewards = HintText::LACS({
                     //obscure text
                     Text{"Spiritual Stones and Medallions", "", ""},
  });

  HintText LACSTokens = HintText::LACS({
                     //obscure text
                     Text{"Gold Skulltula Tokens", "", ""},
  });

  /*--------------------------
  |        ALTAR TEXT        |
  ---------------------------*/

  HintText SpiritualStoneTextStart = HintText::Altar({
                     //obscure text
                     Text{"3 Spiritual Stones found in Hyrule...", "", ""},
  });

  HintText ChildAltarTextEnd = HintText::Altar({
                     //obscure text
                     Text{"\x13\x07Ye who may become a Hero...&Stand with the Ocarina and&play the Song of Time.", "", ""},
  });

  HintText AdultAltarTextStart = HintText::Altar({
                     //obscure text
                     Text{"When evil rules all, an awakening&voice from the Sacred Realm will&call those destined to be Sages,&who dwell in the #five temples#.", "", ""},
  });

  HintText AdultAltarTextEnd = HintText::Altar({
                     //obscure text
                     Text{"Together with the Hero of Time,&the awakened ones will bind the&evil and return the light of peace&to the world...", "", ""},
  });

  /*--------------------------
  |   VALIDATION LINE TEXT   |
  ---------------------------*/

  HintText ValidationLine = HintText::Validation({
                     //obscure text
                     Text{"Hmph... Since you made it this far,&I'll let you know what glorious&prize of Ganon's you likely&missed out on in my tower.^Behold...^", "", ""},
  });

  /*--------------------------
  | LIGHT ARROW LOCATION TEXT|
  ---------------------------*/

  HintText LightArrowLocation = HintText::LightArrow({
                     //obscure text
                     Text{"Ha ha ha... You'll never beat me by&reflecting my lightning bolts&and unleashing the arrows from&", "", ""},
  });

  /*--------------------------
  |      GANON LINE TEXT     |
  ---------------------------*/

  HintText GanonLine01 = HintText::GanonLine({
                     //obscure text
                     Text{"Oh! It's @.&I was expecting someone called&Sheik. Do you know what&happened to them?", "", ""},
  });

  HintText GanonLine02 = HintText::GanonLine({
                     //obscure text
                     Text{"I knew I shouldn't have put the key&on the other side of my door.", "", ""},
  });

  HintText GanonLine03 = HintText::GanonLine({
                     //obscure text
                     Text{"Looks like it's time for a&round of tennis.", "", ""},
  });

  HintText GanonLine04 = HintText::GanonLine({
                     //obscure text
                     Text{"You'll never deflect my bolts of&energy with your sword,&then shoot me with those Light&Arrows you happen to have.", "", ""},
  });

  HintText GanonLine05 = HintText::GanonLine({
                     //obscure text
                     Text{"Why did I leave my trident&back in the desert?", "", ""},
  });

  HintText GanonLine06 = HintText::GanonLine({
                     //obscure text
                     Text{"Zelda is probably going to do&something stupid, like send you&back to your own timeline.^So this is quite meaningless.&Do you really want&to save this moron?", "", ""},
  });

  HintText GanonLine07 = HintText::GanonLine({
                     //obscure text
                     Text{"What about Zelda makes you think&she'd be a better ruler than I?^I saved Lon Lon Ranch,&fed the hungry,&and my castle floats.", "", ""},
  });

  HintText GanonLine08 = HintText::GanonLine({
                     //obscure text
                     Text{"I've learned this spell,&it's really neat,&I'll keep it later&for your treat!", "", ""},
  });

  HintText GanonLine09 = HintText::GanonLine({
                     //obscure text
                     Text{"Many tricks are up my sleeve,&to save yourself&you'd better leave!", "", ""},
  });

  HintText GanonLine10 = HintText::GanonLine({
                     //obscure text
                     Text{"After what you did to&Koholint Island, how can&you call me the bad guy?", "", ""},
  });

  HintText GanonLine11 = HintText::GanonLine({
                     //obscure text
                     Text{"Today, let's begin down&'The Hero is Defeated' timeline.", "", ""},
  });

  std::array<HintText*, 66> junkHints = {
    &Junk01,
    &Junk02,
    &Junk03,
    &Junk04,
    //&Junk05,
    &Junk06,
    //&Junk07,
    &Junk08,
    &Junk09,
    &Junk10,
    //&Junk11,
    &Junk12,
    &Junk13,
    &Junk14,
    &Junk15,
    &Junk16,
    &Junk17,
    &Junk18,
    //&Junk19,
    //&Junk20,
    &Junk21,
    &Junk22,
    &Junk23,
    &Junk24,
    &Junk25,
    &Junk26,
    &Junk27,
    &Junk28,
    &Junk29,
    &Junk30,
    &Junk31,
    &Junk32,
    &Junk33,
    &Junk34,
    &Junk35,
    &Junk36,
    &Junk37,
    &Junk38,
    &Junk39,
    &Junk40,
    &Junk41,
    &Junk42,
    &Junk43,
    &Junk44,
    &Junk45,
    &Junk46,
    &Junk47,
    &Junk48,
    &Junk49,
    &Junk50,
    &Junk51,
    &Junk52,
    &Junk53,
    &Junk54,
    &Junk55,
    &Junk56,
    &Junk57,
    &Junk58,
    &Junk59,
    &Junk60,
    &Junk61,
    &Junk62,
    &Junk63,
    &Junk64,
    &Junk65,
    &Junk66,
    &Junk67,
    &Junk68,
    &Junk69,
    &Junk70,
    &Junk71,
  };

} //namespace Hints

/*
HintText  = HintText::Type({
                     //obscure text
                     Text{"", "", ""},
                     Text{"", "", ""},
                     Text{"", "", ""},
                   },
                     //clear text
                     Text{"", "", ""}
);
*/
