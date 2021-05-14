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
  HintText Prefix       = HintText::Exclude({Text{"They say that ", /*french*/"", /*spanish*/""}});
  HintText WayOfTheHero = HintText::Exclude({Text{" is on the way of the hero.",  /*french*/"", /*spanish*/""}});
  HintText Plundering   = HintText::Exclude({Text{"plundering ", /*french*/"", /*spanish*/""}});
  HintText Foolish      = HintText::Exclude({Text{" is a foolish choice.", /*french*/"", /*spanish*/""}});

  /*--------------------------
  |      ITEM HINT TEXT      |
  ---------------------------*/

  HintText TriforcePiece = HintText::Item({
                       //obscure text
                       Text{"a triumph fork",  /*french*/"", /*spanish*/""},
                       Text{"cheese",          /*french*/"", /*spanish*/""},
                       Text{"a gold fragment", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Piece of the Triforce", /*french*/"", /*spanish*/""}
  );

  HintText ProgressiveMagic = HintText::Item({
                       //obscure text
                       Text{"mystic training",    /*french*/"", /*spanish*/""},
                       Text{"pixie dust",         /*french*/"", /*spanish*/""},
                       Text{"a green reactangle", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Magic Meter", /*french*/"", /*spanish*/""}
  );

  HintText DoubleDefense = HintText::Item({
                       //obscure text
                       Text{"a white outline",   /*french*/"", /*spanish*/""},
                       Text{"damage decrease",   /*french*/"", /*spanish*/""},
                       Text{"strengthened love", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"Double Defense", /*french*/"", /*spanish*/""}
  );

  HintText ProgressiveBulletBag = HintText::Item({
                       //obscure text
                       Text{"a seed shooter",     /*french*/"", /*spanish*/""},
                       Text{"a rubberband",       /*french*/"", /*spanish*/""},
                       Text{"a child's catapult", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Slingshot", /*french*/"", /*spanish*/""}
  );

  HintText Boomerang = HintText::Item({
                       //obscure text
                       Text{"a banana",       /*french*/"", /*spanish*/""},
                       Text{"a stun stick",   /*french*/"", /*spanish*/""},
                       Text{"a yellow angle", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Boomerang", /*french*/"", /*spanish*/""}
  );

  HintText ProgressiveBow = HintText::Item({
                       //obscure text
                       Text{"an archery enabler",     /*french*/"", /*spanish*/""},
                       Text{"a danger dart launcher", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Bow", /*french*/"", /*spanish*/""}
  );

  HintText ProgressiveBombBag = HintText::Item({
                       //obscure text
                       Text{"an explosive container", /*french*/"", /*spanish*/""},
                       Text{"a blast bag", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Bomb Bag", /*french*/"", /*spanish*/""}
  );

  HintText ProgressiveHookshot = HintText::Item({
                       //obscure text
                       Text{"Dampe's keepsake", /*french*/"", /*spanish*/""},
                       Text{"the Grapple Beam", /*french*/"", /*spanish*/""},
                       Text{"the BOING! chain", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Hookshot", /*french*/"", /*spanish*/""}
  );

  HintText ProgressiveStrength = HintText::Item({
                       //obscure text
                       Text{"power gloves",    /*french*/"", /*spanish*/""},
                       Text{"metal mittens",   /*french*/"", /*spanish*/""},
                       Text{"the heavy lifty", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Strength Upgrade", /*french*/"", /*spanish*/""}
  );

  HintText ProgressiveScale = HintText::Item({
                       //obscure text
                       Text{"a deeper dive",   /*french*/"", /*spanish*/""},
                       Text{"a piece of Zora", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Zora Scale", /*french*/"", /*spanish*/""}
  );

  HintText MegatonHammer = HintText::Item({
                       //obscure text
                       Text{"the dragon smasher", /*french*/"", /*spanish*/""},
                       Text{"the metal mallet",   /*french*/"", /*spanish*/""},
                       Text{"the heavy hitter",   /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Megaton Hammer", /*french*/"", /*spanish*/""}
  );

  HintText IronBoots = HintText::Item({
                       //obscure text
                       Text{"sink shoes",   /*french*/"", /*spanish*/""},
                       Text{"clank cleats", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Iron Boots", /*french*/"", /*spanish*/""}
  );

  HintText HoverBoots = HintText::Item({
                       //obscure text
                       Text{"butter boots",    /*french*/"", /*spanish*/""},
                       Text{"sacred slippers", /*french*/"", /*spanish*/""},
                       Text{"spacewalkers",    /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Hover Boots", /*french*/"", /*spanish*/""}
  );

  HintText KokiriSword = HintText::Item({
                       //obscure text
                       Text{"a butter knife",    /*french*/"", /*spanish*/""},
                       Text{"a starter slasher", /*french*/"", /*spanish*/""},
                       Text{"a switchblade",     /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Kokiri Sword", /*french*/"", /*spanish*/""}
  );

  HintText GiantsKnife = HintText::Item({
                       //obscure text
                       Text{"a fragile blade",     /*french*/"", /*spanish*/""},
                       Text{"a breakable cleaver", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Giant's Knife", /*french*/"", /*spanish*/""}
  );

  HintText BiggoronSword = HintText::Item({
                       //obscure text
                       Text{"the biggest blade",  /*french*/"", /*spanish*/""},
                       Text{"a colossal cleaver", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Biggoron Sword", /*french*/"", /*spanish*/""}
  );

  HintText MasterSword = HintText::Item({
                       //obscure text
                       Text{"evil's bane",        /*french*/"", /*spanish*/""},
                       Text{"a seven year limbo", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Master Sword", /*french*/"", /*spanish*/""}
  );

  HintText DekuShield = HintText::Item({
                       //obscure text
                       Text{"a wooden ward",      /*french*/"", /*spanish*/""},
                       Text{"a burnable barrier", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Deku Shield", /*french*/"", /*spanish*/""}
  );

  HintText HylianShield = HintText::Item({
                       //obscure text
                       Text{"a steel safeguard",      /*french*/"", /*spanish*/""},
                       Text{"Like Like's metal meal", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Hylian Shield", /*french*/"", /*spanish*/""}
  );

  HintText MirrorShield = HintText::Item({
                       //obscure text
                       Text{"a reflective rampart", /*french*/"", /*spanish*/""},
                       Text{"Medusa's weakness",    /*french*/"", /*spanish*/""},
                       Text{"a silvered surface",   /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Mirror Shield", /*french*/"", /*spanish*/""}
  );

  HintText FaroresWind = HintText::Item({
                       //obscure text
                       Text{"teleportation",     /*french*/"", /*spanish*/""},
                       Text{"a relocation rune", /*french*/"", /*spanish*/""},
                       Text{"a green ball",      /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"Farore's Wind", /*french*/"", /*spanish*/""}
  );

  HintText NayrusLove = HintText::Item({
                       //obscure text
                       Text{"a safe space",        /*french*/"", /*spanish*/""},
                       Text{"an impregnable aura", /*french*/"", /*spanish*/""},
                       Text{"a blue barrier",      /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"Nayru's Love", /*french*/"", /*spanish*/""}
  );

  HintText DinsFire = HintText::Item({
                       //obscure text
                       Text{"an inferno",  /*french*/"", /*spanish*/""},
                       Text{"a heat wave", /*french*/"", /*spanish*/""},
                       Text{"a red ball",  /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"Din's Fire", /*french*/"", /*spanish*/""}
  );

  HintText FireArrows = HintText::Item({
                       //obscure text
                       Text{"the furnace firearm" , /*french*/"", /*spanish*/""},
                       Text{"the burning bolts",    /*french*/"", /*spanish*/""},
                       Text{"a magma missile",      /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Fire Arrows", /*french*/"", /*spanish*/""}
  );

  HintText IceArrows = HintText::Item({
                       //obscure text
                       Text{"the refrigerator rocket", /*french*/"", /*spanish*/""},
                       Text{"the frostbite bolts",     /*french*/"", /*spanish*/""},
                       Text{"an iceberg maker",        /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Ice Arrows", /*french*/"", /*spanish*/""}
  );

  HintText LightArrows = HintText::Item({
                       //obscure text
                       Text{"the shining shot",      /*french*/"", /*spanish*/""},
                       Text{"the luminous launcher", /*french*/"", /*spanish*/""},
                       Text{"Ganondorf's bane",      /*french*/"", /*spanish*/""},
                       Text{"the lighting bolts",    /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Light Arrows", /*french*/"", /*spanish*/""}
  );

  HintText LensOfTruth = HintText::Item({
                       //obscure text
                       Text{"a lie detector",     /*french*/"", /*spanish*/""},
                       Text{"a ghost tracker",    /*french*/"", /*spanish*/""},
                       Text{"true sight", "       ", ""},
                       Text{"a detective's tool", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Lens of Truth", /*french*/"", /*spanish*/""}
  );

  HintText ProgressiveOcarina = HintText::Item({
                       //obscure text
                       Text{"a flute",       /*french*/"", /*spanish*/""},
                       Text{"a music maker", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"an Ocarina", /*french*/"", /*spanish*/""}
  );

  HintText GoronTunic = HintText::Item({
                       //obscure text
                       Text{"ruby robes",       /*french*/"", /*spanish*/""},
                       Text{"fireproof fabric", /*french*/"", /*spanish*/""},
                       Text{"cooking clothes",  /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Goron Tunic", /*french*/"", /*spanish*/""}
  );

  HintText ZoraTunic = HintText::Item({
                       //obscure text
                       Text{"a sapphire suit", /*french*/"", /*spanish*/""},
                       Text{"scuba gear",      /*french*/"", /*spanish*/""},
                       Text{"a swimsuit",      /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Zora Tunic", /*french*/"", /*spanish*/""}
  );

  HintText Epona = HintText::Item({
                       //obscure text
                       Text{"a horse",              /*french*/"", /*spanish*/""},
                       Text{"a four legged friend", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"Epona", /*french*/"", /*spanish*/""}
  );

  HintText ZeldasLullaby = HintText::Item({
                       //obscure text
                       Text{"a song of royal slumber", /*french*/"", /*spanish*/""},
                       Text{"a triforce tune",         /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"Zelda's Lullaby", /*french*/"", /*spanish*/""}
  );

  HintText EponasSong = HintText::Item({
                       //obscure text
                       Text{"an equestrian etude", /*french*/"", /*spanish*/""},
                       Text{"Malon's melody",      /*french*/"", /*spanish*/""},
                       Text{"a ranch song",        /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"Epona's Song", /*french*/"", /*spanish*/""}
  );

  HintText SariasSong = HintText::Item({
                       //obscure text
                       Text{"a song of dancing Gorons", /*french*/"", /*spanish*/""},
                       Text{"Saria's phone number",     /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"Saria's Song", /*french*/"", /*spanish*/""}
  );

  HintText SunsSong = HintText::Item({
                       //obscure text
                       Text{"Sunny Day",         /*french*/"", /*spanish*/""},
                       Text{"the ReDead's bane", /*french*/"", /*spanish*/""},
                       Text{"the Gibdo's bane",  /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Sun's Song", /*french*/"", /*spanish*/""}
  );

  HintText SongOfTime = HintText::Item({
                       //obscure text
                       Text{"a song 7 years long", /*french*/"", /*spanish*/""},
                       Text{"the tune of ages",    /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Song of Time", /*french*/"", /*spanish*/""}
  );

  HintText SongOfStorms = HintText::Item({
                       //obscure text
                       Text{"Rain Dance",            /*french*/"", /*spanish*/""},
                       Text{"a thunderstorm tune",   /*french*/"", /*spanish*/""},
                       Text{"windmill acceleration", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Song of Storms", /*french*/"", /*spanish*/""}
  );

  HintText MinuetOfForest = HintText::Item({
                       //obscure text
                       Text{"the song of tall trees", /*french*/"", /*spanish*/""},
                       Text{"an arboreal anthem",     /*french*/"", /*spanish*/""},
                       Text{"a green spark trail",    /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Minuet of Forest", /*french*/"", /*spanish*/""}
  );

  HintText BoleroOfFire = HintText::Item({
                       //obscure text
                       Text{"a song of lethal lava", /*french*/"", /*spanish*/""},
                       Text{"a red spark trail",     /*french*/"", /*spanish*/""},
                       Text{"a volcanic verse",      /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Bolero of Fire", /*french*/"", /*spanish*/""}
  );

  HintText SerenadeOfWater = HintText::Item({
                       //obscure text
                       Text{"a song of a damp ditch", /*french*/"", /*spanish*/""},
                       Text{"a blue spark trail",     /*french*/"", /*spanish*/""},
                       Text{"the lake's lyric",       /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Serenade of Water", /*french*/"", /*spanish*/""}
  );

  HintText RequiemOfSpirit = HintText::Item({
                       //obscure text
                       Text{"a song of sandy statues", /*french*/"", /*spanish*/""},
                       Text{"an orange spark trail",   /*french*/"", /*spanish*/""},
                       Text{"the desert ditty",        /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Requiem of Spirit", /*french*/"", /*spanish*/""}
  );

  HintText NocturneOfShadow = HintText::Item({
                       //obscure text
                       Text{"a song of spooky spirits", /*french*/"", /*spanish*/""},
                       Text{"a graveyard boogie",       /*french*/"", /*spanish*/""},
                       Text{"a haunted hymn",           /*french*/"", /*spanish*/""},
                       Text{"a purple spark trail",     /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Nocturne of Shadow", /*french*/"", /*spanish*/""}
  );

  HintText PreludeOfLight = HintText::Item({
                       //obscure text
                       Text{"a luminous prologue melody", /*french*/"", /*spanish*/""},
                       Text{"a yellow spark trail",       /*french*/"", /*spanish*/""},
                       Text{"the temple traveler",        /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Prelude of Light", /*french*/"", /*spanish*/""}
  );

  HintText EmptyBottle = HintText::Item({
                       //obscure text
                       Text{"a glass container", /*french*/"", /*spanish*/""},
                       Text{"an empty jar",      /*french*/"", /*spanish*/""},
                       Text{"encased air",       /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Bottle", /*french*/"", /*spanish*/""}
  );

  HintText RutosLetter = HintText::Item({
                       //obscure text
                       Text{"a call for help",      /*french*/"", /*spanish*/""},
                       Text{"the note that Mweeps", /*french*/"", /*spanish*/""},
                       Text{"an SOS call",          /*french*/"", /*spanish*/""},
                       Text{"a fishy stationery",   /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"Ruto's Letter", /*french*/"", /*spanish*/""}
  );

  HintText BottleWithMilk = HintText::Item({
                       //obscure text
                       Text{"cow juice",          /*french*/"", /*spanish*/""},
                       Text{"a white liquid",     /*french*/"", /*spanish*/""},
                       Text{"a baby's breakfast", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Milk Bottle", /*french*/"", /*spanish*/""}
  );

  HintText BottleWithRedPotion = HintText::Item({
                       //obscure text
                       Text{"a vitality vial", /*french*/"", /*spanish*/""},
                       Text{"a red liquid",    /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Red Potion Bottle", /*french*/"", /*spanish*/""}
  );

  HintText BottleWithGreenPotion = HintText::Item({
                       //obscure text
                       Text{"a magic mixture", /*french*/"", /*spanish*/""},
                       Text{"a green liquid",  /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Green Potion Bottle", /*french*/"", /*spanish*/""}
  );

  HintText BottleWithBluePotion = HintText::Item({
                       //obscure text
                       Text{"an ailment antidote", /*french*/"", /*spanish*/""},
                       Text{"a blue liquid",       /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Blue Potion Bottle", /*french*/"", /*spanish*/""}
  );

  HintText BottleWithFairy = HintText::Item({
                       //obscure text
                       Text{"an imprisoned fairy", /*french*/"", /*spanish*/""},
                       Text{"an extra life",       /*french*/"", /*spanish*/""},
                       Text{"Navi's cousin",       /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Fairy Bottle", /*french*/"", /*spanish*/""}
  );

  HintText BottleWithFish = HintText::Item({
                       //obscure text
                       Text{"an aquarium",     /*french*/"", /*spanish*/""},
                       Text{"a deity's snack", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Fish Bottle", /*french*/"", /*spanish*/""}
  );

  HintText BottleWithBlueFire = HintText::Item({
                       //obscure text
                       Text{"a conflagration canteen", /*french*/"", /*spanish*/""},
                       Text{"an icemelt jar",          /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Blue Fire Bottle", /*french*/"", /*spanish*/""}
  );

  HintText BottleWithBugs = HintText::Item({
                       //obscure text
                       Text{"an insectarium",    /*french*/"", /*spanish*/""},
                       Text{"Skulltula finders", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Bug Bottle", /*french*/"", /*spanish*/""}
  );

  HintText BottleWithPoe = HintText::Item({
                       //obscure text
                       Text{"a spooky ghost",    /*french*/"", /*spanish*/""},
                       Text{"a face in the jar", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Poe Bottle", /*french*/"", /*spanish*/""}
  );

  HintText BottleWithBigPoe = HintText::Item({
                       //obscure text
                       Text{"the spookiest ghost", /*french*/"", /*spanish*/""},
                       Text{"a sidequest spirit",  /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Big Poe Bottle", /*french*/"", /*spanish*/""}
  );

  HintText ShardOfAgony = HintText::Item({
                       //obscure text
                       Text{"the shake shard", /*french*/"", /*spanish*/""},
                       Text{"a blue alarm",    /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Shard of Agony", /*french*/"", /*spanish*/""}
  );

  HintText GerudoToken = HintText::Item({
                       //obscure text
                       Text{"a girl club membership", /*french*/"", /*spanish*/""},
                       Text{"a desert tribe's pass",  /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Gerudo Token", /*french*/"", /*spanish*/""}
  );

  HintText ProgressiveWallet = HintText::Item({
                       //obscure text
                       Text{"a mo' money holder", /*french*/"", /*spanish*/""},
                       Text{"a gem purse",        /*french*/"", /*spanish*/""},
                       Text{"a portable bank",    /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Wallet", /*french*/"", /*spanish*/""}
  );

  HintText ProgressiveStickCapacity = HintText::Item({
                       //obscure text
                       Text{"a lumber rack",        /*french*/"", /*spanish*/""},
                       Text{"more flammable twigs", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"Deku Stick Capacity", /*french*/"", /*spanish*/""}
  );

  HintText ProgressiveNutCapacity = HintText::Item({
                       //obscure text
                       Text{"more nuts",         /*french*/"", /*spanish*/""},
                       Text{"flashbang storage", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"Deku Nut Capacity", /*french*/"", /*spanish*/""}
  );

  HintText HeartContainer = HintText::Item({
                       //obscure text
                       Text{"a lot of love",      /*french*/"", /*spanish*/""},
                       Text{"a Valentine's gift", /*french*/"", /*spanish*/""},
                       Text{"a boss's organ",     /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Heart Container", /*french*/"", /*spanish*/""}
  );

  HintText PieceOfHeart = HintText::Item({
                       //obscure text
                       Text{"a little love",  /*french*/"", /*spanish*/""},
                       Text{"a broken heart", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Piece of Heart", /*french*/"", /*spanish*/""}
  );

  HintText TreasureGameHeart = HintText::Item({
                       //obscure text
                       Text{"a victory valentine", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Piece of Heart", /*french*/"", /*spanish*/""}
  );

  HintText RecoveryHeart = HintText::Item({
                       //obscure text
                       Text{"a free heal",   /*french*/"", /*spanish*/""},
                       Text{"a hearty meal", /*french*/"", /*spanish*/""},
                       Text{"a Band-Aid",    /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Recovery Heart", /*french*/"", /*spanish*/""}
  );

  HintText TreasureGameGreenRupee = HintText::Item({
                       //obscure text
                       Text{"the dollar of defeat", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Green Rupee", /*french*/"", /*spanish*/""}
  );

  HintText DekuStick1 = HintText::Item({
                       //obscure text
                       Text{"a breakable branch", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Deku Stick", /*french*/"", /*spanish*/""}
  );

  HintText GreenRupee = HintText::Item({
                       //obscure text
                       Text{"a unique coin", /*french*/"", /*spanish*/""},
                       Text{"a penny",       /*french*/"", /*spanish*/""},
                       Text{"a green gem",   /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Green Rupee", /*french*/"", /*spanish*/""}
  );

  HintText BlueRupee = HintText::Item({
                       //obscure text
                       Text{"a common coin", /*french*/"", /*spanish*/""},
                       Text{"a blue gem",    /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Blue Rupee", /*french*/"", /*spanish*/""}
  );

  HintText RedRupee = HintText::Item({
                       //obscure text
                       Text{"couch cash", /*french*/"", /*spanish*/""},
                       Text{"a red gem",  /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Red Rupee", /*french*/"", /*spanish*/""}
  );

  HintText PurpleRupee = HintText::Item({
                       //obscure text
                       Text{"big bucks",    /*french*/"", /*spanish*/""},
                       Text{"a purple gem", /*french*/"", /*spanish*/""},
                       Text{"wealth",       /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Purple Rupee", /*french*/"", /*spanish*/""}
  );

  HintText HugeRupee = HintText::Item({
                       //obscure text
                       Text{"a juicy jackpot", /*french*/"", /*spanish*/""},
                       Text{"a yellow gem",    /*french*/"", /*spanish*/""},
                       Text{"a giant gem",     /*french*/"", /*spanish*/""},
                       Text{"great wealth",    /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Huge Rupee", /*french*/"", /*spanish*/""}
  );

  HintText WeirdEgg = HintText::Item({
                       //obscure text
                       Text{"a chicken dilemma", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Weird Egg", /*french*/"", /*spanish*/""}
  );

  HintText ZeldasLetter = HintText::Item({
                       //obscure text
                       Text{"an autograph",     /*french*/"", /*spanish*/""},
                       Text{"royal stationery", /*french*/"", /*spanish*/""},
                       Text{"royal snail mail", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"Zelda's Letter", /*french*/"", /*spanish*/""}
  );

  HintText PocketEgg = HintText::Item({
                       //obscure text
                       Text{"a Cucco container",   /*french*/"", /*spanish*/""},
                       Text{"a Cucco, eventually", /*french*/"", /*spanish*/""},
                       Text{"a fowl youth",        /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Pocket Egg", /*french*/"", /*spanish*/""}
  );

  HintText PocketCucco = HintText::Item({
                       //obscure text
                       Text{"a little clucker", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Pocket Cucco", /*french*/"", /*spanish*/""}
  );

  HintText Cojiro = HintText::Item({
                       //obscure text
                       Text{"a cerulean capon", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"Cojiro", /*french*/"", /*spanish*/""}
  );

  HintText OddMushroom = HintText::Item({
                       //obscure text
                       Text{"a powder ingredient", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"an Odd Mushroom", /*french*/"", /*spanish*/""}
  );

  HintText OddPoultice = HintText::Item({
                       //obscure text
                       Text{"Granny's goodies", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"an Odd Potion", /*french*/"", /*spanish*/""}
  );

  HintText PoachersSaw = HintText::Item({
                       //obscure text
                       Text{"a tree killer", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Poacher's Saw", /*french*/"", /*spanish*/""}
  );

  HintText BrokenSword = HintText::Item({
                       //obscure text
                       Text{"a shattered slicer", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Broken Sword", /*french*/"", /*spanish*/""}
  );

  HintText Prescription = HintText::Item({
                       //obscure text
                       Text{"a pill pamphlet", /*french*/"", /*spanish*/""},
                       Text{"a doctor's note", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Prescription", /*french*/"", /*spanish*/""}
  );

  HintText EyeballFrog = HintText::Item({
                       //obscure text
                       Text{"a perceiving polliwog", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Eyeball Frog", /*french*/"", /*spanish*/""}
  );

  HintText Eyedrops = HintText::Item({
                       //obscure text
                       Text{"a vision vial", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Eyedrops", /*french*/"", /*spanish*/""}
  );

  HintText ClaimCheck = HintText::Item({
                       //obscure text
                       Text{"a three day wait", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Claim Check", /*french*/"", /*spanish*/""}
  );

  HintText Map = HintText::Item({
                       //obscure text
                       Text{"a dungeon atlas", /*french*/"", /*spanish*/""},
                       Text{"blueprints",      /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Map", /*french*/"", /*spanish*/""}
  );

  HintText Compass = HintText::Item({
                       //obscure text
                       Text{"a treasure tracker", /*french*/"", /*spanish*/""},
                       Text{"a magnetic needle",  /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Compass", /*french*/"", /*spanish*/""}
  );

  HintText BossKey = HintText::Item({
                       //obscure text
                       Text{"a master of unlocking",   /*french*/"", /*spanish*/""},
                       Text{"a dungeon's master pass", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Boss Key", /*french*/"", /*spanish*/""}
  );

  HintText GanonsBossKey = HintText::Item({
                       //obscure text
                       Text{"a master of unlocking",   /*french*/"", /*spanish*/""},
                       Text{"a dungeon's master pass", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Boss Key", /*french*/"", /*spanish*/""}
  );

  HintText SmallKey = HintText::Item({
                       //obscure text
                       Text{"a tool for unlocking", /*french*/"", /*spanish*/""},
                       Text{"a dungeon pass",       /*french*/"", /*spanish*/""},
                       Text{"a lock remover",       /*french*/"", /*spanish*/""},
                       Text{"a lockpick",           /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Small Key", /*french*/"", /*spanish*/""}
  );

  HintText FortressSmallKey = HintText::Item({
                       //obscure text
                       Text{"a get out of jail free card", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Jail Key", /*french*/"", /*spanish*/""}
  );

  HintText KokiriEmerald = HintText::Item({
                       //obscure text
                       Text{"a green stone", /*french*/"", /*spanish*/""},
                       Text{"a gift before death",  /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Kokiri Emerald", /*french*/"", /*spanish*/""}
  );

  HintText GoronRuby = HintText::Item({
                       //obscure text
                       Text{"a red stone", /*french*/"", /*spanish*/""},
                       Text{"sworn brotherhood",  /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Goron Ruby", /*french*/"", /*spanish*/""}
  );

  HintText ZoraSapphire = HintText::Item({
                       //obscure text
                       Text{"a blue stone", /*french*/"", /*spanish*/""},
                       Text{"an engagement gift",  /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Zora Sapphire", /*french*/"", /*spanish*/""}
  );

  HintText ForestMedallion = HintText::Item({
                       //obscure text
                       Text{"a green coin", /*french*/"", /*spanish*/""},
                       Text{"Saria's friendship",  /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Forest Medallion", /*french*/"", /*spanish*/""}
  );

  HintText FireMedallion = HintText::Item({
                       //obscure text
                       Text{"a red coin", /*french*/"", /*spanish*/""},
                       Text{"Darunia's power",  /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Fire Medallion", /*french*/"", /*spanish*/""}
  );

  HintText WaterMedallion = HintText::Item({
                       //obscure text
                       Text{"a blue coin", /*french*/"", /*spanish*/""},
                       Text{"Ruto's power",  /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Water Medallion", /*french*/"", /*spanish*/""}
  );

  HintText SpiritMedallion = HintText::Item({
                       //obscure text
                       Text{"an orange coin", /*french*/"", /*spanish*/""},
                       Text{"Nabooru's power",  /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Spirit Medallion", /*french*/"", /*spanish*/""}
  );

  HintText ShadowMedallion = HintText::Item({
                       //obscure text
                       Text{"a purple coin", /*french*/"", /*spanish*/""},
                       Text{"Impa's power",  /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Shadow Medallion", /*french*/"", /*spanish*/""}
  );

  HintText LightMedallion = HintText::Item({
                       //obscure text
                       Text{"a yellow coin", /*french*/"", /*spanish*/""},
                       Text{"Rauru's power",  /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the Light Medallion", /*french*/"", /*spanish*/""}
  );

  // HintText HintError = HintText::Item({
  //                      //obscure text
  //                      Text{"something mysterious", /*french*/"", /*spanish*/""},
  //                      Text{"an unknown treasure",  /*french*/"", /*spanish*/""},
  //                    },
  //                      //clear text
  //                      Text{"An Error (Please Report This)", /*french*/"", /*spanish*/""}
  // );

  HintText Arrows5 = HintText::Item({
                       //obscure text
                       Text{"a few danger darts", /*french*/"", /*spanish*/""},
                       Text{"a few sharp shafts", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"Arrows (5 pieces)", /*french*/"", /*spanish*/""}
  );

  HintText Arrows10 = HintText::Item({
                       //obscure text
                       Text{"some danger darts", /*french*/"", /*spanish*/""},
                       Text{"some sharp shafts", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"Arrows (10 pieces)", /*french*/"", /*spanish*/""}
  );

  HintText Arrows30 = HintText::Item({
                       //obscure text
                       Text{"plenty of danger darts", /*french*/"", /*spanish*/""},
                       Text{"plenty of sharp shafts", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"Arrows (30 pieces)", /*french*/"", /*spanish*/""}
  );

  HintText Bombs5 = HintText::Item({
                       //obscure text
                       Text{"a few explosives",  /*french*/"", /*spanish*/""},
                       Text{"a few blast balls", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"Bombs (5 pieces)", /*french*/"", /*spanish*/""}
  );

  HintText Bombs10 = HintText::Item({
                       //obscure text
                       Text{"some explosives",  /*french*/"", /*spanish*/""},
                       Text{"some blast balls", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"Bombs (10 pieces)", /*french*/"", /*spanish*/""}
  );

  HintText Bombs20 = HintText::Item({
                       //obscure text
                       Text{"lots-o-explosives",     /*french*/"", /*spanish*/""},
                       Text{"plenty of blast balls", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"Bombs (20 pieces)", /*french*/"", /*spanish*/""}
  );

  HintText IceTrap = HintText::Item({
                       //obscure text
                       Text{"a gift from Ganon",    /*french*/"", /*spanish*/""},
                       Text{"a chilling discovery", /*french*/"", /*spanish*/""},
                       Text{"frosty fun", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"an Ice Trap", /*french*/"", /*spanish*/""}
  );

  HintText MagicBean = HintText::Item({
                       //obscure text
                       Text{"a wizardly legume", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Magic Bean", /*french*/"", /*spanish*/""}
  );

  HintText MagicBeanPack = HintText::Item({
                       //obscure text
                       Text{"wizardly legumes", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"Magic Beans", /*french*/"", /*spanish*/""}
  );

  HintText ProgressiveBombchus = HintText::Item({
                       //obscure text
                       Text{"mice bombs",     /*french*/"", /*spanish*/""},
                       Text{"proximity mice", /*french*/"", /*spanish*/""},
                       Text{"wall crawlers",  /*french*/"", /*spanish*/""},
                       Text{"trail blazers",  /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"Bombchus", /*french*/"", /*spanish*/""}
  );

  HintText Bombchus5 = HintText::Item({
                       //obscure text
                       Text{"a few mice bombs",     /*french*/"", /*spanish*/""},
                       Text{"a few proximity mice", /*french*/"", /*spanish*/""},
                       Text{"a few wall crawlers",  /*french*/"", /*spanish*/""},
                       Text{"a few trail blazers",  /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"Bombchus (5 pieces)", /*french*/"", /*spanish*/""}
  );

  HintText Bombchus10 = HintText::Item({
                       //obscure text
                       Text{"some mice bombs",     /*french*/"", /*spanish*/""},
                       Text{"some proximity mice", /*french*/"", /*spanish*/""},
                       Text{"some wall crawlers",  /*french*/"", /*spanish*/""},
                       Text{"some trail blazers",  /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"Bombchus (10 pieces)", /*french*/"", /*spanish*/""}
  );

  HintText Bombchus20 = HintText::Item({
                       //obscure text
                       Text{"plenty of mice bombs",     /*french*/"", /*spanish*/""},
                       Text{"plenty of proximity mice", /*french*/"", /*spanish*/""},
                       Text{"plenty of wall crawlers",  /*french*/"", /*spanish*/""},
                       Text{"plenty of trail blazers",  /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"Bombchus (20 pieces)", /*french*/"", /*spanish*/""}
  );

  HintText DekuNuts5 = HintText::Item({
                       //obscure text
                       Text{"some nuts",       /*french*/"", /*spanish*/""},
                       Text{"some flashbangs", /*french*/"", /*spanish*/""},
                       Text{"some scrub spit", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"Deku Nuts (5 pieces)", /*french*/"", /*spanish*/""}
  );

  HintText DekuNuts10 = HintText::Item({
                       //obscure text
                       Text{"lots-o-nuts",          /*french*/"", /*spanish*/""},
                       Text{"plenty of flashbangs", /*french*/"", /*spanish*/""},
                       Text{"plenty of scrub spit", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"Deku Nuts (10 pieces)", /*french*/"", /*spanish*/""}
  );

  HintText DekuSeeds30 = HintText::Item({
                       //obscure text
                       Text{"catapult ammo", /*french*/"", /*spanish*/""},
                       Text{"lots-o-seeds",  /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"Deku Seeds (30 pieces)", /*french*/"", /*spanish*/""}
  );

  HintText GoldSkulltulaToken = HintText::Item({
                       //obscure text
                       Text{"proof of destruction",   /*french*/"", /*spanish*/""},
                       Text{"an arachnid chip",       /*french*/"", /*spanish*/""},
                       Text{"spider remains",         /*french*/"", /*spanish*/""},
                       Text{"one percent of a curse", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a Gold Skulltula Token", /*french*/"", /*spanish*/""}
  );

  /*--------------------------
  |     ALWAYS HINT TEXT     |
  ---------------------------*/

  HintText ZR_FrogsOcarinaGame = HintText::Always({
                       //obscure text
                       Text{"an #amphibian feast# yields",               /*french*/"", /*spanish*/""},
                       Text{"the #croaking choir's magnum opus# awards", /*french*/"", /*spanish*/""},
                       Text{"the #froggy finale# yields",                /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the final reward from the #Frogs of Zora's River# is", /*french*/"", /*spanish*/""}
  );

  HintText KF_LinksHouseCow = HintText::Always({
                       //obscure text
                       Text{"the #bovine bounty of a horseback hustle# gifts", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"#Malon's obstacle course# leads to", /*french*/"", /*spanish*/""}
  );

  /*--------------------------
  |    SOMETIMES HINT TEXT   |
  ---------------------------*/

  HintText SongFromOcarinaOfTime = HintText::Sometimes({
                       //obscure text
                       Text{"the #Ocarina of Time# teaches", /*french*/"", /*spanish*/""},
  });

  HintText SongFromComposersGrave = HintText::Sometimes({
                       //obscure text
                       Text{"#ReDead in the Composers' Grave# guard", /*french*/"", /*spanish*/""},
                       Text{"the #Composer Brothers wrote#",          /*french*/"", /*spanish*/""},
  });

  HintText SheikInForest = HintText::Sometimes({
                       //obscure text
                       Text{"#in a meadow# Sheik teaches", /*french*/"", /*spanish*/""},
  });

  HintText SheikAtTemple = HintText::Sometimes({
                       //obscure text
                       Text{"Sheik waits at a #monument to time# to teach", /*french*/"", /*spanish*/""},
  });

  HintText SheikInCrater = HintText::Sometimes({
                       //obscure text
                       Text{"the #crater's melody# is", /*french*/"", /*spanish*/""},
  });

  HintText SheikInIceCavern = HintText::Sometimes({
                       //obscure text
                       Text{"the #frozen cavern# echoes with", /*french*/"", /*spanish*/""},
  });

  HintText SheikInKakariko = HintText::Sometimes({
                       //obscure text
                       Text{"a #ravaged village# mourns with", /*french*/"", /*spanish*/""},
  });

  HintText SheikAtColossus = HintText::Sometimes({
                       //obscure text
                       Text{"a hero ventures #beyond the wasteland# to learn", /*french*/"", /*spanish*/""},
  });


  HintText MK_10BigPoes = HintText::Sometimes({
                       //obscure text
                       Text{"#ghost hunters# will be rewarded with", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"catching #Big Poes# leads to", /*french*/"", /*spanish*/""}
  );

  HintText DekuTheater_SkullMask = HintText::Sometimes({
                       //obscure text
                       Text{"the #Skull Mask# yields", /*french*/"", /*spanish*/""},
  });

  HintText DekuTheater_MaskOfTruth = HintText::Sometimes({
                       //obscure text
                       Text{"showing a #truthful eye to the crowd# rewards", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the #Mask of Truth# yields", /*french*/"", /*spanish*/""}
  );

  HintText HF_OcarinaOfTimeItem = HintText::Sometimes({
                       //obscure text
                       Text{"the #treasure thrown by Princess Zelda# is", /*french*/"", /*spanish*/""},
  });

  HintText DMT_Biggoron = HintText::Sometimes({
                       //obscure text
                       Text{"#Biggoron# crafts", /*french*/"", /*spanish*/""},
  });

  HintText Kak_50GoldSkulltulaReward = HintText::Sometimes({
                       //obscure text
                       Text{"#50 bug badges# rewards",           /*french*/"", /*spanish*/""},
                       Text{"#50 spider souls# yields",          /*french*/"", /*spanish*/""},
                       Text{"#50 auriferous arachnids# lead to", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"slaying #50 Gold Skulltulas# reveals", /*french*/"", /*spanish*/""}
  );

  HintText Kak_40GoldSkulltulaReward = HintText::Sometimes({
                       //obscure text
                       Text{"#40 bug badges# rewards",           /*french*/"", /*spanish*/""},
                       Text{"#40 spider souls# yields",          /*french*/"", /*spanish*/""},
                       Text{"#40 auriferous arachnids# lead to", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"slaying #40 Gold Skulltulas# reveals", /*french*/"", /*spanish*/""}
  );

  HintText Kak_30GoldSkulltulaReward = HintText::Sometimes({
                       //obscure text
                       Text{"#30 bug badges# rewards",           /*french*/"", /*spanish*/""},
                       Text{"#30 spider souls# yields",          /*french*/"", /*spanish*/""},
                       Text{"#30 auriferous arachnids# lead to", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"slaying #30 Gold Skulltulas# reveals", /*french*/"", /*spanish*/""}
  );

  HintText Kak_20GoldSkulltulaReward = HintText::Sometimes({
                       //obscure text
                       Text{"#20 bug badges# rewards",           /*french*/"", /*spanish*/""},
                       Text{"#20 spider souls# yields",          /*french*/"", /*spanish*/""},
                       Text{"#20 auriferous arachnids# lead to", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"slaying #20 Gold Skulltulas# reveals", /*french*/"", /*spanish*/""}
  );

  HintText Kak_AnjuAsChild = HintText::Sometimes({
                       //obscure text
                       Text{"#wrangling roosters# rewards", /*french*/"", /*spanish*/""},
                       Text{"#chucking chickens# gifts",    /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"#collecting cuccos# rewards", /*french*/"", /*spanish*/""}
  );

  HintText GC_DaruniasJoy = HintText::Sometimes({
                       //obscure text
                       Text{"a #groovin' goron# gifts", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"#Darunia's dance# leads to", /*french*/"", /*spanish*/""}
  );

  HintText LW_SkullKid = HintText::Sometimes({
                       //obscure text
                       Text{"the #Skull Kid# grants", /*french*/"", /*spanish*/""},
  });

  HintText LH_Sun = HintText::Sometimes({
                       //obscure text
                       Text{"staring into #the sun# grants", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"shooting #the sun# grants", /*french*/"", /*spanish*/""}
  );

  HintText MK_TreasureChestGameReward = HintText::Sometimes({
                       //obscure text
                       Text{"#gambling# grants",               /*french*/"", /*spanish*/""},
                       Text{"there is a #1/32 chance# to win", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the #treasure chest game# grants", /*french*/"", /*spanish*/""}
  );

  HintText GF_HBA1500Points = HintText::Sometimes({
                       //obscure text
                       Text{"mastery of #horseback archery# grants", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"scoring 1500 in #horseback archery# grants", /*french*/"", /*spanish*/""}
  );

  HintText GY_HeartPieceGraveChest = HintText::Sometimes({
                       //obscure text
                       Text{"playing #Sun's Song# in a grave spawns", /*french*/"", /*spanish*/""},
  });

  HintText GC_MazeLeftChest = HintText::Sometimes({
                       //obscure text
                       Text{"in #Goron City# the hammer unlocks", /*french*/"", /*spanish*/""},
  });

  HintText GV_Chest = HintText::Sometimes({
                       //obscure text
                       Text{"in #Gerudo Valley# the hammer unlocks", /*french*/"", /*spanish*/""},
  });

  HintText GV_Cow = HintText::Sometimes({
                       //obscure text
                       Text{"a #cow in Gerudo Valley# gifts", /*french*/"", /*spanish*/""},
  });

  HintText HC_GS_StormsGrotto = HintText::Sometimes({
                       //obscure text
                       Text{"a #spider behind a muddy wall# in a grotto holds", /*french*/"", /*spanish*/""},
  });

  HintText HF_GS_CowGrotto = HintText::Sometimes({
                       //obscure text
                       Text{"a #spider behind webs# in a grotto holds", /*french*/"", /*spanish*/""},
  });

  HintText HF_CowGrottoCow = HintText::Sometimes({
                       //obscure text
                       Text{"the #cobwebbed cow# gifts", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a #cow behind webs# in a grotto gifts", /*french*/"", /*spanish*/""}
  );

  HintText ZF_GS_HiddenCave = HintText::Sometimes({
                       //obscure text
                       Text{"a spider high #above the icy waters# holds", /*french*/"", /*spanish*/""},
  });

  HintText HW_Chest = HintText::Sometimes({
                       //obscure text
                       Text{"#deep in the wasteland# is",         /*french*/"", /*spanish*/""},
                       Text{"beneath #the sands#, flames reveal", /*french*/"", /*spanish*/""},
  });

  HintText HW_GS = HintText::Sometimes({
                       //obscure text
                       Text{"a #spider in the wasteland# holds", /*french*/"", /*spanish*/""},
  });

  HintText GY_ComposersGraveChest = HintText::Sometimes({
                       //obscure text
                       Text{"#flames in the Composers' Grave# reveal", /*french*/"", /*spanish*/""},
                       Text{"the #Composer Brothers hid#",             /*french*/"", /*spanish*/""},
  });

  HintText ZF_BottomFreestandingPoH = HintText::Sometimes({
                       //obscure text
                       Text{"#under the icy waters# lies", /*french*/"", /*spanish*/""},
  });

  HintText GC_PotFreestandingPoH = HintText::Sometimes({
                       //obscure text
                       Text{"spinning #Goron pottery# contains", /*french*/"", /*spanish*/""},
  });

  HintText ZD_KingZoraThawed = HintText::Sometimes({
                       //obscure text
                       Text{"a #defrosted dignitary# gifts", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"unfreezing #King Zora# grants", /*french*/"", /*spanish*/""}
  );

  HintText DMC_DekuScrub = HintText::Sometimes({
                       //obscure text
                       Text{"a single #scrub in the crater# sells", /*french*/"", /*spanish*/""},
  });

  HintText DMC_GS_Crate = HintText::Sometimes({
                       //obscure text
                       Text{"a spider under a #crate in the crater# holds", /*french*/"", /*spanish*/""},
  });


  HintText DekuTree_MQ_AfterSpinningLogChest = HintText::Sometimes({
                       //obscure text
                       Text{"a #temporal stone within a tree# contains", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a #temporal stone within the Deku Tree# contains", /*french*/"", /*spanish*/""}
  );

  HintText DekuTree_MQ_GS_BasementGravesRoom = HintText::Sometimes({
                       //obscure text
                       Text{"a #spider on a ceiling in a tree# holds", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a #spider on a ceiling in the Deku Tree# holds", /*french*/"", /*spanish*/""}
  );

  HintText DodongosCavern_MQ_GS_SongOfTimeBlockRoom = HintText::Sometimes({
                       //obscure text
                       Text{"a spider under #temporal stones in a cavern# holds", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a spider under #temporal stones in Dodongo's Cavern# holds", /*french*/"", /*spanish*/""}
  );

  HintText JabuJabusBelly_BoomerangChest = HintText::Sometimes({
                       //obscure text
                       Text{"a school of #stingers swallowed by a deity# guard", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a school of #stingers swallowed by Jabu Jabu# guard", /*french*/"", /*spanish*/""}
  );

  HintText JabuJabusBelly_MQ_GS_InvisibleEnemiesRoom = HintText::Sometimes({
                       //obscure text
                       Text{"a spider surrounded by #shadows in the belly of a deity# holds", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a spider surrounded by #shadows in Jabu Jabu's Belly# holds", /*french*/"", /*spanish*/""}
  );

  HintText JabuJabusBelly_MQ_Cow = HintText::Sometimes({
                       //obscure text
                       Text{"a #cow swallowed by a deity# gifts", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a #cow swallowed by Jabu Jabu# gifts", /*french*/"", /*spanish*/""}
  );

  HintText FireTemple_ScarecrowChest = HintText::Sometimes({
                       //obscure text
                       Text{"a #scarecrow atop the volcano# hides", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"#Pierre atop the Fire Temple# hides", /*french*/"", /*spanish*/""}
  );

  HintText FireTemple_MegatonHammerChest = HintText::Sometimes({
                       //obscure text
                       Text{"the #Flare Dancer atop the volcano# guards a chest containing", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the #Flare Dancer atop the Fire Temple# guards a chest containing", /*french*/"", /*spanish*/""}
  );

  HintText FireTemple_MQ_ChestOnFire = HintText::Sometimes({
                       //obscure text
                       Text{"the #Flare Dancer atop the volcano# guards a chest containing", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the #Flare Dancer atop the Fire Temple# guards a chest containing", /*french*/"", /*spanish*/""}
  );

  HintText FireTemple_MQ_GS_SkullOnFire = HintText::Sometimes({
                       //obscure text
                       Text{"a #spider under a block in the volcano# holds", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a #spider under a block in the Fire Temple# holds", /*french*/"", /*spanish*/""}
  );

  HintText WaterTemple_RiverChest = HintText::Sometimes({
                       //obscure text
                       Text{"beyond the #river under the lake# waits", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"beyond the #river in the Water Temple# waits", /*french*/"", /*spanish*/""}
  );

  HintText WaterTemple_BossKeyChest = HintText::Sometimes({
                       //obscure text
                       Text{"dodging #rolling boulders under the lake# leads to", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"dodging #rolling boulders in the Water Temple# leads to", /*french*/"", /*spanish*/""}
  );

  HintText WaterTemple_GS_BehindGate = HintText::Sometimes({
                       //obscure text
                       Text{"a spider behind a #gate under the lake# holds", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a spider behind a #gate in the Water Temple# holds", /*french*/"", /*spanish*/""}
  );

  HintText WaterTemple_MQ_FreestandingKey = HintText::Sometimes({
                       //obscure text
                       Text{"hidden in a #box under the lake# lies", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"hidden in a #box in the Water Temple# lies", /*french*/"", /*spanish*/""}
  );

  HintText WaterTemple_MQ_GS_FreestandingKeyArea = HintText::Sometimes({
                       //obscure text
                       Text{"the #locked spider under the lake# holds", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the #locked spider in the Water Temple# holds", /*french*/"", /*spanish*/""}
  );

  HintText WaterTemple_MQ_GS_TripleWallTorch = HintText::Sometimes({
                       //obscure text
                       Text{"a spider behind a #gate under the lake# holds", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a spider behind a #gate in the Water Temple# holds", /*french*/"", /*spanish*/""}
  );

  HintText GerudoTrainingGrounds_UnderwaterSilverRupeeChest = HintText::Sometimes({
                       //obscure text
                       Text{"those who seek #sunken silver rupees# will find", /*french*/"", /*spanish*/""},
                       Text{"the #thieves' underwater training# rewards",      /*french*/"", /*spanish*/""},
  });

  HintText GerudoTrainingGrounds_MQ_UnderwaterSilverRupeeChest = HintText::Sometimes({
                       //obscure text
                       Text{"those who seek #sunken silver rupees# will find", /*french*/"", /*spanish*/""},
                       Text{"the #thieves' underwater training# rewards",      /*french*/"", /*spanish*/""},
  });

  HintText GerudoTrainingGrounds_MazePathFinalChest = HintText::Sometimes({
                       //obscure text
                       Text{"the final prize of #the thieves' training# is", /*french*/"", /*spanish*/""},
  });

  HintText GerudoTrainingGrounds_MQ_IceArrowsChest = HintText::Sometimes({
                       //obscure text
                       Text{"the final prize of #the thieves' training# is", /*french*/"", /*spanish*/""},
  });

  HintText BottomOfTheWell_LensOfTruthChest = HintText::Sometimes({
                       //obscure text
                       Text{"the well's #grasping ghoul# hides",    /*french*/"", /*spanish*/""},
                       Text{"a #nether dweller in the well# holds", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"#Dead Hand in the well# holds", /*french*/"", /*spanish*/""}
  );

  HintText BottomOfTheWell_MQ_CompassChest = HintText::Sometimes({
                       //obscure text
                       Text{"the well's #grasping ghoul# hides",    /*french*/"", /*spanish*/""},
                       Text{"a #nether dweller in the well# holds", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"#Dead Hand in the well# holds", /*french*/"", /*spanish*/""}
  );

  HintText SpiritTemple_SilverGauntletsChest = HintText::Sometimes({
                       //obscure text
                       Text{"the treasure #sought by Nabooru# is", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"upon the #Colossus's right hand# is", /*french*/"", /*spanish*/""}
  );

  HintText SpiritTemple_MirrorShieldChest = HintText::Sometimes({
                       //obscure text
                       Text{"upon the #Colossus's left hand# is", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_MQ_ChildHammerSwitchChest = HintText::Sometimes({
                       //obscure text
                       Text{"a #temporal paradox in the Colossus# yields", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a #temporal paradox in the Spirit Temple# yields", /*french*/"", /*spanish*/""}
  );

  HintText SpiritTemple_MQ_SymphonyRoomChest = HintText::Sometimes({
                       //obscure text
                       Text{"a #symphony in the Colossus# yields", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a #symphony in the Spirit Temple# yields", /*french*/"", /*spanish*/""}
  );

  HintText SpiritTemple_MQ_GS_SymphonyRoom = HintText::Sometimes({
                       //obscure text
                       Text{"a #spider's symphony in the Colossus# yields", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a #spider's symphony in the Spirit Temple# yields", /*french*/"", /*spanish*/""}
  );

  HintText ShadowTemple_InvisibleFloormasterChest = HintText::Sometimes({
                       //obscure text
                       Text{"shadows in an #invisible maze# guard", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_MQ_BombFlowerChest = HintText::Sometimes({
                       //obscure text
                       Text{"shadows in an #invisible maze# guard", /*french*/"", /*spanish*/""},
  });

  /*--------------------------
  |    EXCLUDE HINT TEXT     |
  ---------------------------*/

  HintText KF_KokiriSwordChest = HintText::Exclude({
                       //obscure text
                       Text{"the #hidden treasure of the Kokiri# is", /*french*/"", /*spanish*/""},
  });

  HintText KF_MidoTopLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"the #leader of the Kokiri# hides", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"#inside Mido's house# is", /*french*/"", /*spanish*/""}
  );

  HintText KF_MidoTopRightChest = HintText::Exclude({
                       //obscure text
                       Text{"the #leader of the Kokiri# hides", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"#inside Mido's house# is", /*french*/"", /*spanish*/""}
  );

  HintText KF_MidoBottomLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"the #leader of the Kokiri# hides", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"#inside Mido's house# is", /*french*/"", /*spanish*/""}
  );

  HintText KF_MidoBottomRightChest = HintText::Exclude({
                       //obscure text
                       Text{"the #leader of the Kokiri# hides", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"#inside Mido's house# is", /*french*/"", /*spanish*/""}
  );

  HintText GY_ShieldGraveChest = HintText::Exclude({
                       //obscure text
                       Text{"the #treasure of a fallen soldier# is", /*french*/"", /*spanish*/""},
  });

  HintText DMT_Chest = HintText::Exclude({
                       //obscure text
                       Text{"hidden behind a wall on a #mountain trail# is", /*french*/"", /*spanish*/""},
  });

  HintText GC_MazeRightChest = HintText::Exclude({
                       //obscure text
                       Text{"in #Goron City# explosives unlock", /*french*/"", /*spanish*/""},
  });

  HintText GC_MazeCenterChest = HintText::Exclude({
                       //obscure text
                       Text{"in #Goron City# explosives unlock", /*french*/"", /*spanish*/""},
  });

  HintText ZD_Chest = HintText::Exclude({
                       //obscure text
                       Text{"fire #beyond a waterfall# reveals", /*french*/"", /*spanish*/""},
  });

  HintText GY_HookshotChest = HintText::Exclude({
                       //obscure text
                       Text{"a chest hidden by a #speedy spectre# holds", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"#dead Dampe's first prize# is", /*french*/"", /*spanish*/""}
  );

  HintText GF_Chest = HintText::Exclude({
                       //obscure text
                       Text{"on a #rooftop in the desert# lies", /*french*/"", /*spanish*/""},
  });

  HintText Kak_RedeadGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"#zombies beneath the earth# guard", /*french*/"", /*spanish*/""},
  });

  HintText SFM_WolfosGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"#wolves beneath the earth# guard", /*french*/"", /*spanish*/""},
  });

  HintText HF_NearMarketGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"a #hole in a field near a drawbridge# holds", /*french*/"", /*spanish*/""},
  });

  HintText HF_SoutheastGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"a #hole amongst trees in a field# holds", /*french*/"", /*spanish*/""},
  });

  HintText HF_OpenGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"an #open hole in a field# holds", /*french*/"", /*spanish*/""},
  });

  HintText Kak_OpenGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"an #open hole in a town# holds", /*french*/"", /*spanish*/""},
  });

  HintText ZR_OpenGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"a #hole along a river# holds", /*french*/"", /*spanish*/""},
  });

  HintText KF_StormsGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"a #hole in a forest village# holds", /*french*/"", /*spanish*/""},
  });

  HintText LW_NearShortcutsGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"a #hole in a wooded maze# holds", /*french*/"", /*spanish*/""},
  });

  HintText DMT_StormsGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"#hole flooded with rain on a mountain# holds", /*french*/"", /*spanish*/""},
  });

  HintText DMC_UpperGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"a #hole in a volcano# holds", /*french*/"", /*spanish*/""},
  });


  HintText ToT_LightArrowCutscene = HintText::Exclude({
                       //obscure text
                       Text{"the #final gift of a princess# is", /*french*/"", /*spanish*/""},
  });

  HintText LW_GiftFromSaria = HintText::Exclude({
                       //obscure text
                       Text{"a #potato hoarder# holds",           /*french*/"", /*spanish*/""},
                       Text{"a rooty tooty #flutey cutey# gifts", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"#Saria's Gift# is", /*french*/"", /*spanish*/""}
  );

  HintText ZF_GreatFairyReward = HintText::Exclude({
                       //obscure text
                       Text{"the #fairy of winds# holds", /*french*/"", /*spanish*/""},
  });

  HintText HC_GreatFairyReward = HintText::Exclude({
                       //obscure text
                       Text{"the #fairy of fire# holds", /*french*/"", /*spanish*/""},
  });

  HintText Colossus_GreatFairyReward = HintText::Exclude({
                       //obscure text
                       Text{"the #fairy of love# holds", /*french*/"", /*spanish*/""},
  });

  HintText DMT_GreatFairyReward = HintText::Exclude({
                       //obscure text
                       Text{"a #magical fairy# gifts", /*french*/"", /*spanish*/""},
  });

  HintText DMC_GreatFairyReward = HintText::Exclude({
                       //obscure text
                       Text{"a #magical fairy# gifts", /*french*/"", /*spanish*/""},
  });

  HintText OGC_GreatFairyReward = HintText::Exclude({
                       //obscure text
                       Text{"the #fairy of strength# holds", /*french*/"", /*spanish*/""},
  });


  HintText SongFromImpa = HintText::Exclude({
                       //obscure text
                       Text{"#deep in a castle#, Impa teaches", /*french*/"", /*spanish*/""},
  });

  HintText SongFromMalon = HintText::Exclude({
                       //obscure text
                       Text{"#a farm girl# sings", /*french*/"", /*spanish*/""},
  });

  HintText SongFromSaria = HintText::Exclude({
                       //obscure text
                       Text{"#deep in the forest#, Saria teaches", /*french*/"", /*spanish*/""},
  });

  HintText SongFromWindmill = HintText::Exclude({
                       //obscure text
                       Text{"a man #in a windmill# is obsessed with", /*french*/"", /*spanish*/""},
  });


  HintText HC_MalonEgg = HintText::Exclude({
                       //obscure text
                       Text{"a #girl looking for her father# gives", /*french*/"", /*spanish*/""},
  });

  HintText HC_ZeldasLetter = HintText::Exclude({
                       //obscure text
                       Text{"a #princess in a castle# gifts", /*french*/"", /*spanish*/""},
  });

  HintText ZD_DivingMinigame = HintText::Exclude({
                       //obscure text
                       Text{"an #unsustainable business model# gifts", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"those who #dive for Zora rupees# will find", /*french*/"", /*spanish*/""}
  );

  HintText LH_ChildFishing = HintText::Exclude({
                       //obscure text
                       Text{"#fishing in youth# bestows", /*french*/"", /*spanish*/""},
  });

  HintText LH_AdultFishing = HintText::Exclude({
                       //obscure text
                       Text{"#fishing in maturity# bestows", /*french*/"", /*spanish*/""},
  });

  HintText LH_LabDive = HintText::Exclude({
                       //obscure text
                       Text{"a #diving experiment# is rewarded with", /*french*/"", /*spanish*/""},
  });

  HintText GC_RollingGoronAsAdult = HintText::Exclude({
                       //obscure text
                       Text{"#comforting yourself# provides", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"#reassuring a young Goron# is rewarded with", /*french*/"", /*spanish*/""}
  );

  HintText MK_BombchuBowlingFirstPrize = HintText::Exclude({
                       //obscure text
                       Text{"the #first explosive prize# is", /*french*/"", /*spanish*/""},
  });

  HintText MK_BombchuBowlingSecondPrize = HintText::Exclude({
                       //obscure text
                       Text{"the #second explosive prize# is", /*french*/"", /*spanish*/""},
  });

  HintText MK_LostDog = HintText::Exclude({
                       //obscure text
                       Text{"#puppy lovers# will find", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"#rescuing Richard the Dog# is rewarded with", /*french*/"", /*spanish*/""}
  );

  HintText LW_OcarinaMemoryGame = HintText::Exclude({
                       //obscure text
                       Text{"the prize for a #game of Simon Says# is", /*french*/"", /*spanish*/""},
                       Text{"a #child sing-a-long# holds",             /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"#playing an Ocarina in Lost Woods# is rewarded with", /*french*/"", /*spanish*/""}
  );

  HintText Kak_10GoldSkulltulaReward = HintText::Exclude({
                       //obscure text
                       Text{"#10 bug badges# rewards",           /*french*/"", /*spanish*/""},
                       Text{"#10 spider souls# yields",          /*french*/"", /*spanish*/""},
                       Text{"#10 auriferous arachnids# lead to", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"slaying #10 Gold Skulltulas# reveals", /*french*/"", /*spanish*/""}
  );

  HintText Kak_ManOnRoof = HintText::Exclude({
                       //obscure text
                       Text{"a #rooftop wanderer# holds", /*french*/"", /*spanish*/""},
  });

  HintText ZR_MagicBeanSalesman = HintText::Exclude({
                       //obscure text
                       Text{"a seller of #colorful crops# has", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a #bean seller# offers", /*french*/"", /*spanish*/""}
  );

  HintText ZR_FrogsInTheRain = HintText::Exclude({
                       //obscure text
                       Text{"#frogs in a storm# gift", /*french*/"", /*spanish*/""},
  });

  HintText GF_HBA1000Points = HintText::Exclude({
                       //obscure text
                       Text{"scoring 1000 in #horseback archery# grants", /*french*/"", /*spanish*/""},
  });

  HintText MK_ShootingGalleryReward = HintText::Exclude({
                       //obscure text
                       Text{"#shooting in youth# grants", /*french*/"", /*spanish*/""},
  });

  HintText Kak_ShootingGalleryReward = HintText::Exclude({
                       //obscure text
                       Text{"#shooting in maturity# grants", /*french*/"", /*spanish*/""},
  });

  HintText LW_TargetInWoods = HintText::Exclude({
                       //obscure text
                       Text{"shooting a #target in the woods# grants", /*french*/"", /*spanish*/""},
  });

  HintText Kak_AnjuAsAdult = HintText::Exclude({
                       //obscure text
                       Text{"a #chicken caretaker# offers adults", /*french*/"", /*spanish*/""},
  });

  HintText LLR_TalonsChickens = HintText::Exclude({
                       //obscure text
                       Text{"#finding Super Cuccos# is rewarded with", /*french*/"", /*spanish*/""},
  });

  HintText GC_RollingGoronAsChild = HintText::Exclude({
                       //obscure text
                       Text{"the prize offered by a #large rolling Goron# is", /*french*/"", /*spanish*/""},
  });

  HintText LH_UnderwaterItem = HintText::Exclude({
                       //obscure text
                       Text{"the #sunken treasure in a lake# is", /*french*/"", /*spanish*/""},
  });

  HintText GF_GerudoToken = HintText::Exclude({
                       //obscure text
                       Text{"#rescuing captured carpenters# is rewarded with", /*french*/"", /*spanish*/""},
  });

  HintText Wastelan_BombchuSalesman = HintText::Exclude({
                       //obscure text
                       Text{"a #carpet guru# sells", /*french*/"", /*spanish*/""},
  });


  HintText Kak_ImpasHouseFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"#imprisoned in a house# lies", /*french*/"", /*spanish*/""},
  });

  HintText HF_TektiteGrottoFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"#deep underwater in a hole# is", /*french*/"", /*spanish*/""},
  });

  HintText Kak_WindmillFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"on a #windmill ledge# lies", /*french*/"", /*spanish*/""},
  });

  HintText GY_DampeRaceFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"#racing a ghost# leads to", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"#dead Dampe's second# prize is", /*french*/"", /*spanish*/""}
  );

  HintText LLR_FreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"in a #ranch silo# lies", /*french*/"", /*spanish*/""},
  });

  HintText GY_FreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"a #crate in a graveyard# hides", /*french*/"", /*spanish*/""},
  });

  HintText GY_DampeGravediggingTour = HintText::Exclude({
                       //obscure text
                       Text{"a #gravekeeper digs up#", /*french*/"", /*spanish*/""},
  });

  HintText ZR_NearOpenGrottoFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"on top of a #pillar in a river# lies", /*french*/"", /*spanish*/""},
  });

  HintText ZR_NearDomainFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"on a #river ledge by a waterfall# lies", /*french*/"", /*spanish*/""},
  });

  HintText LH_FreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"high on a #lab rooftop# one can find", /*french*/"", /*spanish*/""},
  });

  HintText ZF_IcebergFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"#floating on ice# is", /*french*/"", /*spanish*/""},
  });

  HintText GV_WaterfallFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"behind a #desert waterfall# is", /*french*/"", /*spanish*/""},
  });

  HintText GV_CrateFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"a #crate in a valley# hides", /*french*/"", /*spanish*/""},
  });

  HintText Colossus_FreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"on top of an #arch of stone# lies", /*french*/"", /*spanish*/""},
  });

  HintText DMT_FreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"above a #mountain cavern entrance# is", /*french*/"", /*spanish*/""},
  });

  HintText DMC_WallFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"nestled in a #volcanic wall# is", /*french*/"", /*spanish*/""},
  });

  HintText DMC_VolcanoFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"obscured by #volcanic ash# is", /*french*/"", /*spanish*/""},
  });

  HintText GF_NorthF1Carpenter = HintText::Exclude({
                       //obscure text
                       Text{"#defeating Gerudo guards# reveals", /*french*/"", /*spanish*/""},
  });

  HintText GF_NorthF2Carpenter = HintText::Exclude({
                       //obscure text
                       Text{"#defeating Gerudo guards# reveals", /*french*/"", /*spanish*/""},
  });

  HintText GF_SouthF1Carpenter = HintText::Exclude({
                       //obscure text
                       Text{"#defeating Gerudo guards# reveals", /*french*/"", /*spanish*/""},
  });

  HintText GF_SouthF2Carpenter = HintText::Exclude({
                       //obscure text
                       Text{"#defeating Gerudo guards# reveals", /*french*/"", /*spanish*/""},
  });


  HintText DekuTree_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"in the #center of the Deku Tree# lies", /*french*/"", /*spanish*/""},
  });

  HintText DekuTree_SlingshotChest = HintText::Exclude({
                       //obscure text
                       Text{"the #treasure guarded by a scrub# in the Deku Tree is", /*french*/"", /*spanish*/""},
  });

  HintText DekuTree_SlingshotRoomSideChest = HintText::Exclude({
                       //obscure text
                       Text{"the #treasure guarded by a scrub# in the Deku Tree is", /*french*/"", /*spanish*/""},
  });

  HintText DekuTree_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#pillars of wood# in the Deku Tree lead to", /*french*/"", /*spanish*/""},
  });

  HintText DekuTree_CompassRoomSideChest = HintText::Exclude({
                       //obscure text
                       Text{"#pillars of wood# in the Deku Tree lead to", /*french*/"", /*spanish*/""},
  });

  HintText DekuTree_BasementChest = HintText::Exclude({
                       //obscure text
                       Text{"#webs in the Deku Tree# hide", /*french*/"", /*spanish*/""},
  });


  HintText DekuTree_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"in the #center of the Deku Tree# lies", /*french*/"", /*spanish*/""},
  });

  HintText DekuTree_MQ_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"a #treasure guarded by a large spider# in the Deku Tree is", /*french*/"", /*spanish*/""},
  });

  HintText DekuTree_MQ_SlingshotChest = HintText::Exclude({
                       //obscure text
                       Text{"#pillars of wood# in the Deku Tree lead to", /*french*/"", /*spanish*/""},
  });

  HintText DekuTree_MQ_SlingshotRoomBackChest = HintText::Exclude({
                       //obscure text
                       Text{"#pillars of wood# in the Deku Tree lead to", /*french*/"", /*spanish*/""},
  });

  HintText DekuTree_MQ_BasementChest = HintText::Exclude({
                       //obscure text
                       Text{"#webs in the Deku Tree# hide", /*french*/"", /*spanish*/""},
  });

  HintText DekuTree_MQ_BeforeSpinningLogChest = HintText::Exclude({
                       //obscure text
                       Text{"#magical fire in the Deku Tree# leads to", /*french*/"", /*spanish*/""},
  });


  HintText DodongosCavern_BossRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"#above King Dodongo# lies", /*french*/"", /*spanish*/""},
  });


  HintText DodongosCavern_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"a #muddy wall in Dodongo's Cavern# hides", /*french*/"", /*spanish*/""},
  });

  HintText DodongosCavern_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"a #statue in Dodongo's Cavern# guards", /*french*/"", /*spanish*/""},
  });

  HintText DodongosCavern_BombFlowerPlatformChest = HintText::Exclude({
                       //obscure text
                       Text{"above a #maze of stone# in Dodongo's Cavern lies", /*french*/"", /*spanish*/""},
  });

  HintText DodongosCavern_BombBagChest = HintText::Exclude({
                       //obscure text
                       Text{"the #second lizard cavern battle# yields", /*french*/"", /*spanish*/""},
  });

  HintText DodongosCavern_EndOfBridgeChest = HintText::Exclude({
                       //obscure text
                       Text{"a #chest at the end of a bridge# yields", /*french*/"", /*spanish*/""},
  });


  HintText DodongosCavern_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"a #muddy wall in Dodongo's Cavern# hides", /*french*/"", /*spanish*/""},
  });

  HintText DodongosCavern_MQ_BombBagChest = HintText::Exclude({
                       //obscure text
                       Text{"an #elevated alcove# in Dodongo's Cavern holds", /*french*/"", /*spanish*/""},
  });

  HintText DodongosCavern_MQ_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#fire-breathing lizards# in Dodongo's Cavern guard", /*french*/"", /*spanish*/""},
  });

  HintText DodongosCavern_MQ_LarvaeRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"#baby spiders# in Dodongo's Cavern guard", /*french*/"", /*spanish*/""},
  });

  HintText DodongosCavern_MQ_TorchPuzzleRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"above a #maze of stone# in Dodongo's Cavern lies", /*french*/"", /*spanish*/""},
  });

  HintText DodongosCavern_MQ_UnderGraveChest = HintText::Exclude({
                       //obscure text
                       Text{"#beneath a headstone# in Dodongo's Cavern lies", /*french*/"", /*spanish*/""},
  });


  HintText JabuJabusBelly_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"#tentacle trouble# in a deity's belly guards", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a #slimy thing# guards", /*french*/"", /*spanish*/""}
  );

  HintText JabuJabusBelly_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#bubble trouble# in a deity's belly guards", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"#bubbles# guard", /*french*/"", /*spanish*/""}
  );


  HintText JabuJabusBelly_MQ_FirstRoomSideChest = HintText::Exclude({
                       //obscure text
                       Text{"shooting a #mouth cow# reveals", /*french*/"", /*spanish*/""},
  });

  HintText JabuJabusBelly_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"#pop rocks# hide",            /*french*/"", /*spanish*/""},
                       Text{"an #explosive palate# holds", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a #boulder before cows# hides", /*french*/"", /*spanish*/""}
  );

  HintText JabuJabusBelly_MQ_SecondRoomLowerChest = HintText::Exclude({
                       //obscure text
                       Text{"near a #spiked elevator# lies", /*french*/"", /*spanish*/""},
  });

  HintText JabuJabusBelly_MQ_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"a #drowning cow# unveils", /*french*/"", /*spanish*/""},
  });

  HintText JabuJabusBelly_MQ_SecondRoomUpperChest = HintText::Exclude({
                       //obscure text
                       Text{"#moving anatomy# creates a path to", /*french*/"", /*spanish*/""},
  });

  HintText JabuJabusBelly_MQ_BasementNearSwitchesChest = HintText::Exclude({
                       //obscure text
                       Text{"a #pair of digested cows# hold", /*french*/"", /*spanish*/""},
  });

  HintText JabuJabusBelly_MQ_BasementNearVinesChest = HintText::Exclude({
                       //obscure text
                       Text{"a #pair of digested cows# hold", /*french*/"", /*spanish*/""},
  });

  HintText JabuJabusBelly_MQ_NearBossChest = HintText::Exclude({
                       //obscure text
                       Text{"the #final cows' reward# in a deity's belly is", /*french*/"", /*spanish*/""},
  });

  HintText JabuJabusBelly_MQ_FallingLikeLikeRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"#cows protected by falling monsters# in a deity's belly guard", /*french*/"", /*spanish*/""},
  });

  HintText JabuJabusBelly_MQ_BoomerangRoomSmallChest = HintText::Exclude({
                       //obscure text
                       Text{"a school of #stingers swallowed by a deity# guard", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a school of #stingers swallowed by Jabu Jabu# guard", /*french*/"", /*spanish*/""}
  );

  HintText JabuJabusBelly_MQ_BoomerangChest = HintText::Exclude({
                       //obscure text
                       Text{"a school of #stingers swallowed by a deity# guard", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a school of #stingers swallowed by Jabu Jabu# guard", /*french*/"", /*spanish*/""}
  );


  HintText ForestTemple_FirstRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"a #tree in the Forest Temple# supports", /*french*/"", /*spanish*/""},
  });

  HintText ForestTemple_FirstStalfosChest = HintText::Exclude({
                       //obscure text
                       Text{"#defeating enemies beneath a falling ceiling# in Forest Temple yields", /*french*/"", /*spanish*/""},
  });

  HintText ForestTemple_WellChest = HintText::Exclude({
                       //obscure text
                       Text{"a #sunken chest deep in the woods# contains", /*french*/"", /*spanish*/""},
  });

  HintText ForestTemple_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"a #fiery skull# in Forest Temple guards", /*french*/"", /*spanish*/""},
  });

  HintText ForestTemple_RaisedIslandCourtyardChest = HintText::Exclude({
                       //obscure text
                       Text{"a #chest on a small island# in the Forest Temple holds", /*french*/"", /*spanish*/""},
  });

  HintText ForestTemple_FallingCeilingRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"beneath a #checkerboard falling ceiling# lies", /*french*/"", /*spanish*/""},
  });

  HintText ForestTemple_EyeSwitchChest = HintText::Exclude({
                       //obscure text
                       Text{"a #sharp eye# will spot", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"#blocks of stone# in the Forest Temple surround", /*french*/"", /*spanish*/""}
  );

  HintText ForestTemple_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"a #turned trunk# contains", /*french*/"", /*spanish*/""},
  });

  HintText ForestTemple_FloormasterChest = HintText::Exclude({
                       //obscure text
                       Text{"deep in the forest #shadows guard a chest# containing", /*french*/"", /*spanish*/""},
  });

  HintText ForestTemple_BowChest = HintText::Exclude({
                       //obscure text
                       Text{"an #army of the dead# guards", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"#Stalfos deep in the Forest Temple# guard", /*french*/"", /*spanish*/""}
  );

  HintText ForestTemple_RedPoeChest = HintText::Exclude({
                       //obscure text
                       Text{"#Joelle# guards", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a #red ghost# guards", /*french*/"", /*spanish*/""}
  );

  HintText ForestTemple_BluePoeChest = HintText::Exclude({
                       //obscure text
                       Text{"#Beth# guards", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a #blue ghost# guards", /*french*/"", /*spanish*/""}
  );

  HintText ForestTemple_BasementChest = HintText::Exclude({
                       //obscure text
                       Text{"#revolving walls# in the Forest Temple conceal", /*french*/"", /*spanish*/""},
  });


  HintText ForestTemple_MQ_FirstRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"a #tree in the Forest Temple# supports", /*french*/"", /*spanish*/""},
  });

  HintText ForestTemple_MQ_WolfosChest = HintText::Exclude({
                       //obscure text
                       Text{"#defeating enemies beneath a falling ceiling# in Forest Temple yields", /*french*/"", /*spanish*/""},
  });

  HintText ForestTemple_MQ_BowChest = HintText::Exclude({
                       //obscure text
                       Text{"an #army of the dead# guards", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"#Stalfos deep in the Forest Temple# guard", /*french*/"", /*spanish*/""}
  );

  HintText ForestTemple_MQ_RaisedIslandCourtyardLowerChest = HintText::Exclude({
                       //obscure text
                       Text{"a #chest on a small island# in the Forest Temple holds", /*french*/"", /*spanish*/""},
  });

  HintText ForestTemple_MQ_RaisedIslandCourtyardUpperChest = HintText::Exclude({
                       //obscure text
                       Text{"#high in a courtyard# within the Forest Temple is", /*french*/"", /*spanish*/""},
  });

  HintText ForestTemple_MQ_WellChest = HintText::Exclude({
                       //obscure text
                       Text{"a #sunken chest deep in the woods# contains", /*french*/"", /*spanish*/""},
  });

  HintText ForestTemple_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"#Joelle# guards", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a #red ghost# guards", /*french*/"", /*spanish*/""}
  );

  HintText ForestTemple_MQ_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#Beth# guards", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a #blue ghost# guards", /*french*/"", /*spanish*/""}
  );

  HintText ForestTemple_MQ_FallingCeilingRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"beneath a #checkerboard falling ceiling# lies", /*french*/"", /*spanish*/""},
  });

  HintText ForestTemple_MQ_BasementChest = HintText::Exclude({
                       //obscure text
                       Text{"#revolving walls# in the Forest Temple conceal", /*french*/"", /*spanish*/""},
  });

  HintText ForestTemple_MQ_RedeadChest = HintText::Exclude({
                       //obscure text
                       Text{"deep in the forest #undead guard a chest# containing", /*french*/"", /*spanish*/""},
  });

  HintText ForestTemple_MQ_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"a #turned trunk# contains", /*french*/"", /*spanish*/""},
  });


  HintText FireTemple_NearBossChest = HintText::Exclude({
                       //obscure text
                       Text{"#near a dragon# is", /*french*/"", /*spanish*/""},
  });

  HintText FireTemple_FlareDancerChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Flare Dancer behind a totem# guards", /*french*/"", /*spanish*/""},
  });

  HintText FireTemple_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"a #prison beyond a totem# holds", /*french*/"", /*spanish*/""},
  });

  HintText FireTemple_BigLavaRoomBlockedDoorChest = HintText::Exclude({
                       //obscure text
                       Text{"#explosives over a lava pit# unveil", /*french*/"", /*spanish*/""},
  });

  HintText FireTemple_BigLavaRoomLowerOpenDoorChest = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron trapped near lava# holds", /*french*/"", /*spanish*/""},
  });

  HintText FireTemple_BoulderMazeLowerChest = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron at the end of a maze# holds", /*french*/"", /*spanish*/""},
  });

  HintText FireTemple_BoulderMazeUpperChest = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron above a maze# holds", /*french*/"", /*spanish*/""},
  });

  HintText FireTemple_BoulderMazeSideRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron hidden near a maze# holds", /*french*/"", /*spanish*/""},
  });

  HintText FireTemple_BoulderMazeShortcutChest = HintText::Exclude({
                       //obscure text
                       Text{"a #blocked path# in Fire Temple holds", /*french*/"", /*spanish*/""},
  });

  HintText FireTemple_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"a #caged chest# in the Fire Temple hoards", /*french*/"", /*spanish*/""},
  });

  HintText FireTemple_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"a #chest in a fiery maze# contains", /*french*/"", /*spanish*/""},
  });

  HintText FireTemple_HighestGoronChest = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron atop the Fire Temple# holds", /*french*/"", /*spanish*/""},
  });


  HintText FireTemple_MQ_NearBossChest = HintText::Exclude({
                       //obscure text
                       Text{"#near a dragon# is", /*french*/"", /*spanish*/""},
  });

  HintText FireTemple_MQ_MegatonHammerChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Flare Dancer in the depths of a volcano# guards", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the #Flare Dancer in the depths of the Fire Temple# guards", /*french*/"", /*spanish*/""}
  );

  HintText FireTemple_MQ_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"a #blocked path# in Fire Temple holds", /*french*/"", /*spanish*/""},
  });

  HintText FireTemple_MQ_LizalfosMazeLowerChest = HintText::Exclude({
                       //obscure text
                       Text{"#crates in a maze# contain", /*french*/"", /*spanish*/""},
  });

  HintText FireTemple_MQ_LizalfosMazeUpperChest = HintText::Exclude({
                       //obscure text
                       Text{"#crates in a maze# contain", /*french*/"", /*spanish*/""},
  });

  HintText FireTemple_MQ_MapRoomSideChest = HintText::Exclude({
                       //obscure text
                       Text{"a #falling slug# in the Fire Temple guards", /*french*/"", /*spanish*/""},
  });

  HintText FireTemple_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"using a #hammer in the depths of the Fire Temple# reveals", /*french*/"", /*spanish*/""},
  });

  HintText FireTemple_MQ_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"#illuminating a lava pit# reveals the path to", /*french*/"", /*spanish*/""},
  });

  HintText FireTemple_MQ_BigLavaRoomBlockedDoorChest = HintText::Exclude({
                       //obscure text
                       Text{"#explosives over a lava pit# unveil", /*french*/"", /*spanish*/""},
  });

  HintText FireTemple_MQ_LizalfosMazeSideRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron hidden near a maze# holds", /*french*/"", /*spanish*/""},
  });

  HintText FireTemple_MQ_FreestandingKey = HintText::Exclude({
                       //obscure text
                       Text{"hidden #beneath a block of stone# lies", /*french*/"", /*spanish*/""},
  });


  HintText WaterTemple_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"#rolling spikes# in the Water Temple surround", /*french*/"", /*spanish*/""},
  });

  HintText WaterTemple_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#roaming stingers in the Water Temple# guard", /*french*/"", /*spanish*/""},
  });

  HintText WaterTemple_TorchesChest = HintText::Exclude({
                       //obscure text
                       Text{"#fire in the Water Temple# reveals", /*french*/"", /*spanish*/""},
  });

  HintText WaterTemple_DragonChest = HintText::Exclude({
                       //obscure text
                       Text{"a #serpent's prize# in the Water Temple is", /*french*/"", /*spanish*/""},
  });

  HintText WaterTemple_CentralBowTargetChest = HintText::Exclude({
                       //obscure text
                       Text{"#blinding an eye# in the Water Temple leads to", /*french*/"", /*spanish*/""},
  });

  HintText WaterTemple_CentralPillarChest = HintText::Exclude({
                       //obscure text
                       Text{"in the #depths of the Water Temple# lies", /*french*/"", /*spanish*/""},
  });

  HintText WaterTemple_CrackedWallChest = HintText::Exclude({
                       //obscure text
                       Text{"#through a crack# in the Water Temple is", /*french*/"", /*spanish*/""},
  });

  HintText WaterTemple_LongshotChest = HintText::Exclude({
                       //obscure text
                       Text{"#facing yourself# reveals",              /*french*/"", /*spanish*/""},
                       Text{"a #dark reflection# of yourself guards", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"#Dark Link# guards", /*french*/"", /*spanish*/""}
  );


  HintText WaterTemple_MQ_CentralPillarChest = HintText::Exclude({
                       //obscure text
                       Text{"in the #depths of the Water Temple# lies", /*french*/"", /*spanish*/""},
  });

  HintText WaterTemple_MQ_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"fire in the Water Temple unlocks a #vast gate# revealing a chest with", /*french*/"", /*spanish*/""},
  });

  HintText WaterTemple_MQ_LongshotChest = HintText::Exclude({
                       //obscure text
                       Text{"#through a crack# in the Water Temple is", /*french*/"", /*spanish*/""},
  });

  HintText WaterTemple_MQ_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#fire in the Water Temple# reveals", /*french*/"", /*spanish*/""},
  });

  HintText WaterTemple_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"#sparring soldiers# in the Water Temple guard", /*french*/"", /*spanish*/""},
  });


  HintText SpiritTemple_ChildBridgeChest = HintText::Exclude({
                       //obscure text
                       Text{"a child conquers a #skull in green fire# in the Spirit Temple to reach", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_ChildEarlyTorchesChest = HintText::Exclude({
                       //obscure text
                       Text{"a child can find a #caged chest# in the Spirit Temple with", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#across a pit of sand# in the Spirit Temple lies", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_EarlyAdultRightChest = HintText::Exclude({
                       //obscure text
                       Text{"#dodging boulders to collect silver rupees# in the Spirit Temple yields", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_FirstMirrorLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"a #shadow circling reflected light# in the Spirit Temple guards", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_FirstMirrorRightChest = HintText::Exclude({
                       //obscure text
                       Text{"a #shadow circling reflected light# in the Spirit Temple guards", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"#before a giant statue# in the Spirit Temple lies", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_ChildClimbNorthChest = HintText::Exclude({
                       //obscure text
                       Text{"#lizards in the Spirit Temple# guard", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_ChildClimbEastChest = HintText::Exclude({
                       //obscure text
                       Text{"#lizards in the Spirit Temple# guard", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_SunBlockRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"#torchlight among Beamos# in the Spirit Temple reveals", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_StatueRoomHandChest = HintText::Exclude({
                       //obscure text
                       Text{"a #statue in the Spirit Temple# holds", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_StatueRoomNortheastChest = HintText::Exclude({
                       //obscure text
                       Text{"on a #ledge by a statue# in the Spirit Temple rests", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_NearFourArmosChest = HintText::Exclude({
                       //obscure text
                       Text{"those who #show the light among statues# in the Spirit Temple find", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_HallwayRightInvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth in the Spirit Temple# reveals", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_HallwayLeftInvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth in the Spirit Temple# reveals", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"a #chest engulfed in flame# in the Spirit Temple holds", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_TopmostChest = HintText::Exclude({
                       //obscure text
                       Text{"those who #show the light above the Colossus# find", /*french*/"", /*spanish*/""},
  });


  HintText SpiritTemple_MQ_EntranceFrontLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"#lying unguarded# in the Spirit Temple is", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_MQ_EntranceBackRightChest = HintText::Exclude({
                       //obscure text
                       Text{"a #switch in a pillar# within the Spirit Temple drops", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_MQ_EntranceFrontRightChest = HintText::Exclude({
                       //obscure text
                       Text{"#collecting rupees through a water jet# reveals", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_MQ_EntranceBackLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"an #eye blinded by stone# within the Spirit Temple conceals", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"surrounded by #fire and wrappings# lies", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_MQ_MapRoomEnemyChest = HintText::Exclude({
                       //obscure text
                       Text{"a child defeats a #gauntlet of monsters# within the Spirit Temple to find", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_MQ_ChildClimbNorthChest = HintText::Exclude({
                       //obscure text
                       Text{"#explosive sunlight# within the Spirit Temple uncovers", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_MQ_ChildClimbSouthChest = HintText::Exclude({
                       //obscure text
                       Text{"#trapped by falling enemies# within the Spirit Temple is", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_MQ_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#blinding the colossus# unveils", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_MQ_StatueRoomLullabyChest = HintText::Exclude({
                       //obscure text
                       Text{"a #royal melody awakens the colossus# to reveal", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_MQ_StatueRoomInvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth# finds the colossus's hidden", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_MQ_SilverBlockHallwayChest = HintText::Exclude({
                       //obscure text
                       Text{"#the old hide what the young find# to reveal", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_MQ_SunBlockRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"#sunlight in a maze of fire# hides", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_MQ_LeeverRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"#across a pit of sand# in the Spirit Temple lies", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_MQ_BeamosRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"where #temporal stone blocks the path# within the Spirit Temple lies", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_MQ_ChestSwitchChest = HintText::Exclude({
                       //obscure text
                       Text{"a #chest of double purpose# holds", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_MQ_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"a #temporal stone blocks the light# leading to", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_MQ_MirrorPuzzleInvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"those who #show the light above the Colossus# find", /*french*/"", /*spanish*/""},
  });


  HintText ShadowTemple_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth# pierces a hall of faces to reveal", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_HoverBootsChest = HintText::Exclude({
                       //obscure text
                       Text{"a #nether dweller in the Shadow Temple# holds", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"#Dead Hand in the Shadow Temple# holds", /*french*/"", /*spanish*/""}
  );

  HintText ShadowTemple_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#mummies revealed by the Eye of Truth# guard", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_EarlySilverRupeeChest = HintText::Exclude({
                       //obscure text
                       Text{"#spinning scythes# protect", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_InvisibleBladesVisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"#invisible blades# guard", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_InvisibleBladesInvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"#invisible blades# guard", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_FallingSpikesLowerChest = HintText::Exclude({
                       //obscure text
                       Text{"#falling spikes# block the path to", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_FallingSpikesUpperChest = HintText::Exclude({
                       //obscure text
                       Text{"#falling spikes# block the path to", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_FallingSpikesSwitchChest = HintText::Exclude({
                       //obscure text
                       Text{"#falling spikes# block the path to", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_InvisibleSpikesChest = HintText::Exclude({
                       //obscure text
                       Text{"the #dead roam among invisible spikes# guarding", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_WindHintChest = HintText::Exclude({
                       //obscure text
                       Text{"an #invisible chest guarded by the dead# holds", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_AfterWindEnemyChest = HintText::Exclude({
                       //obscure text
                       Text{"#mummies guarding a ferry# hide", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_AfterWindHiddenChest = HintText::Exclude({
                       //obscure text
                       Text{"#mummies guarding a ferry# hide", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_SpikeWallsLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"#walls consumed by a ball of fire# reveal", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"#walls consumed by a ball of fire# reveal", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_FreestandingKey = HintText::Exclude({
                       //obscure text
                       Text{"#inside a burning skull# lies", /*french*/"", /*spanish*/""},
  });


  HintText ShadowTemple_MQ_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth# pierces a hall of faces to reveal", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_MQ_HoverBootsChest = HintText::Exclude({
                       //obscure text
                       Text{"#Dead Hand in the Shadow Temple# holds", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_MQ_EarlyGibdosChest = HintText::Exclude({
                       //obscure text
                       Text{"#mummies revealed by the Eye of Truth# guard", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"#spinning scythes# protect", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_MQ_BeamosSilverRupeesChest = HintText::Exclude({
                       //obscure text
                       Text{"#collecting rupees in a vast cavern# with the Shadow Temple unveils", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_MQ_FallingSpikesSwitchChest = HintText::Exclude({
                       //obscure text
                       Text{"#falling spikes# block the path to", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_MQ_FallingSpikesLowerChest = HintText::Exclude({
                       //obscure text
                       Text{"#falling spikes# block the path to", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_MQ_FallingSpikesUpperChest = HintText::Exclude({
                       //obscure text
                       Text{"#falling spikes# block the path to", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_MQ_InvisibleSpikesChest = HintText::Exclude({
                       //obscure text
                       Text{"the #dead roam among invisible spikes# guarding", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_MQ_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"#walls consumed by a ball of fire# reveal", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_MQ_SpikeWallsLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"#walls consumed by a ball of fire# reveal", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_MQ_StalfosRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"near an #empty pedestal# within the Shadow Temple lies", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_MQ_InvisibleBladesInvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"#invisible blades# guard", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_MQ_InvisibleBladesVisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"#invisible blades# guard", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_MQ_WindHintChest = HintText::Exclude({
                       //obscure text
                       Text{"an #invisible chest guarded by the dead# holds", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_MQ_AfterWindHiddenChest = HintText::Exclude({
                       //obscure text
                       Text{"#mummies guarding a ferry# hide", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_MQ_AfterWindEnemyChest = HintText::Exclude({
                       //obscure text
                       Text{"#mummies guarding a ferry# hide", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_MQ_NearShipInvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"#caged near a ship# lies", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_MQ_FreestandingKey = HintText::Exclude({
                       //obscure text
                       Text{"#behind three burning skulls# lies", /*french*/"", /*spanish*/""},
  });


  HintText BottomOfTheWell_FrontLeftFakeWallChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth in the well# reveals", /*french*/"", /*spanish*/""},
  });

  HintText BottomOfTheWell_FrontCenterBombableChest = HintText::Exclude({
                       //obscure text
                       Text{"#gruesome debris# in the well hides", /*french*/"", /*spanish*/""},
  });

  HintText BottomOfTheWell_RightBottomFakeWallChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth in the well# reveals", /*french*/"", /*spanish*/""},
  });

  HintText BottomOfTheWell_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"a #hidden entrance to a cage# in the well leads to", /*french*/"", /*spanish*/""},
  });

  HintText BottomOfTheWell_CenterSkulltulaChest = HintText::Exclude({
                       //obscure text
                       Text{"a #spider guarding a cage# in the well protects", /*french*/"", /*spanish*/""},
  });

  HintText BottomOfTheWell_BackLeftBombableChest = HintText::Exclude({
                       //obscure text
                       Text{"#gruesome debris# in the well hides", /*french*/"", /*spanish*/""},
  });

  HintText BottomOfTheWell_InvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"#Dead Hand's invisible secret# is", /*french*/"", /*spanish*/""},
  });

  HintText BottomOfTheWell_UnderwaterFrontChest = HintText::Exclude({
                       //obscure text
                       Text{"a #royal melody in the well# uncovers", /*french*/"", /*spanish*/""},
  });

  HintText BottomOfTheWell_UnderwaterLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"a #royal melody in the well# uncovers", /*french*/"", /*spanish*/""},
  });

  HintText BottomOfTheWell_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"in the #depths of the well# lies", /*french*/"", /*spanish*/""},
  });

  HintText BottomOfTheWell_FireKeeseChest = HintText::Exclude({
                       //obscure text
                       Text{"#perilous pits# in the well guard the path to", /*french*/"", /*spanish*/""},
  });

  HintText BottomOfTheWell_LikeLikeChest = HintText::Exclude({
                       //obscure text
                       Text{"#locked in a cage# in the well lies", /*french*/"", /*spanish*/""},
  });

  HintText BottomOfTheWell_FreestandingKey = HintText::Exclude({
                       //obscure text
                       Text{"#inside a coffin# hides", /*french*/"", /*spanish*/""},
  });


  HintText BottomOfTheWell_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"a #royal melody in the well# uncovers", /*french*/"", /*spanish*/""},
  });

  HintText BottomOfTheWell_MQ_LensOfTruthChest = HintText::Exclude({
                       //obscure text
                       Text{"an #army of the dead# in the well guards", /*french*/"", /*spanish*/""},
  });

  HintText BottomOfTheWell_MQ_DeadHandFreestandingKey = HintText::Exclude({
                       //obscure text
                       Text{"#Dead Hand's explosive secret# is", /*french*/"", /*spanish*/""},
  });

  HintText BottomOfTheWell_MQ_EastInnerRoomFreestandingKey = HintText::Exclude({
                       //obscure text
                       Text{"an #invisible path in the well# leads to", /*french*/"", /*spanish*/""},
  });


  HintText IceCavern_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"#winds of ice# surround", /*french*/"", /*spanish*/""},
  });

  HintText IceCavern_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"a #wall of ice# protects", /*french*/"", /*spanish*/""},
  });

  HintText IceCavern_IronBootsChest = HintText::Exclude({
                       //obscure text
                       Text{"a #monster in a frozen cavern# guards", /*french*/"", /*spanish*/""},
  });

  HintText IceCavern_FreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"a #wall of ice# protects", /*french*/"", /*spanish*/""},
  });


  HintText IceCavern_MQ_IronBootsChest = HintText::Exclude({
                       //obscure text
                       Text{"a #monster in a frozen cavern# guards", /*french*/"", /*spanish*/""},
  });

  HintText IceCavern_MQ_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#winds of ice# surround", /*french*/"", /*spanish*/""},
  });

  HintText IceCavern_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"a #wall of ice# protects", /*french*/"", /*spanish*/""},
  });

  HintText IceCavern_MQ_FreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"#winds of ice# surround", /*french*/"", /*spanish*/""},
  });


  HintText GerudoTrainingGrounds_LobbyLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"a #blinded eye in the Gerudo Training Grounds# drops", /*french*/"", /*spanish*/""},
  });

  HintText GerudoTrainingGrounds_LobbyRightChest = HintText::Exclude({
                       //obscure text
                       Text{"a #blinded eye in the Gerudo Training Grounds# drops", /*french*/"", /*spanish*/""},
  });

  HintText GerudoTrainingGrounds_StalfosChest = HintText::Exclude({
                       //obscure text
                       Text{"#soldiers walking on shifting sands# in the Gerudo Training Grounds guard", /*french*/"", /*spanish*/""},
  });

  HintText GerudoTrainingGrounds_BeamosChest = HintText::Exclude({
                       //obscure text
                       Text{"#reptilian warriors# in the Gerudo Training Grounds protect", /*french*/"", /*spanish*/""},
  });

  HintText GerudoTrainingGrounds_HiddenCeilingChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth# in the Gerudo Training Grounds reveals", /*french*/"", /*spanish*/""},
  });

  HintText GerudoTrainingGrounds_MazePathFirstChest = HintText::Exclude({
                       //obscure text
                       Text{"the first prize of #the thieves' training# is", /*french*/"", /*spanish*/""},
  });

  HintText GerudoTrainingGrounds_MazePathSecondChest = HintText::Exclude({
                       //obscure text
                       Text{"the second prize of #the thieves' training# is", /*french*/"", /*spanish*/""},
  });

  HintText GerudoTrainingGrounds_MazePathThirdChest = HintText::Exclude({
                       //obscure text
                       Text{"the third prize of #the thieves' training# is", /*french*/"", /*spanish*/""},
  });

  HintText GerudoTrainingGrounds_MazeRightCentralChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Song of Time# in the Gerudo Training Grounds leads to", /*french*/"", /*spanish*/""},
  });

  HintText GerudoTrainingGrounds_MazeRightSideChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Song of Time# in the Gerudo Training Grounds leads to", /*french*/"", /*spanish*/""},
  });

  HintText GerudoTrainingGrounds_HammerRoomClearChest = HintText::Exclude({
                       //obscure text
                       Text{"#fiery foes# in the Gerudo Training Grounds guard", /*french*/"", /*spanish*/""},
  });

  HintText GerudoTrainingGrounds_HammerRoomSwitchChest = HintText::Exclude({
                       //obscure text
                       Text{"#engulfed in flame# where thieves train lies", /*french*/"", /*spanish*/""},
  });

  HintText GerudoTrainingGrounds_EyeStatueChest = HintText::Exclude({
                       //obscure text
                       Text{"thieves #blind four faces# to find", /*french*/"", /*spanish*/""},
  });

  HintText GerudoTrainingGrounds_NearScarecrowChest = HintText::Exclude({
                       //obscure text
                       Text{"thieves #blind four faces# to find", /*french*/"", /*spanish*/""},
  });

  HintText GerudoTrainingGrounds_BeforeHeavyBlockChest = HintText::Exclude({
                       //obscure text
                       Text{"#before a block of silver# thieves can find", /*french*/"", /*spanish*/""},
  });

  HintText GerudoTrainingGrounds_HeavyBlockFirstChest = HintText::Exclude({
                       //obscure text
                       Text{"a #feat of strength# rewards thieves with", /*french*/"", /*spanish*/""},
  });

  HintText GerudoTrainingGrounds_HeavyBlockSecondChest = HintText::Exclude({
                       //obscure text
                       Text{"a #feat of strength# rewards thieves with", /*french*/"", /*spanish*/""},
  });

  HintText GerudoTrainingGrounds_HeavyBlockThirdChest = HintText::Exclude({
                       //obscure text
                       Text{"a #feat of strength# rewards thieves with", /*french*/"", /*spanish*/""},
  });

  HintText GerudoTrainingGrounds_HeavyBlockFourthChest = HintText::Exclude({
                       //obscure text
                       Text{"a #feat of strength# rewards thieves with", /*french*/"", /*spanish*/""},
  });

  HintText GerudoTrainingGrounds_FreestandingKey = HintText::Exclude({
                       //obscure text
                       Text{"the #Song of Time# in the Gerudo Training Grounds leads to", /*french*/"", /*spanish*/""},
  });


  HintText GerudoTrainingGrounds_MQ_LobbyRightChest = HintText::Exclude({
                       //obscure text
                       Text{"#thieves prepare for training# with", /*french*/"", /*spanish*/""},
  });

  HintText GerudoTrainingGrounds_MQ_LobbyLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"#thieves prepare for training# with", /*french*/"", /*spanish*/""},
  });

  HintText GerudoTrainingGrounds_MQ_FirstIronKnuckleChest = HintText::Exclude({
                       //obscure text
                       Text{"#soldiers walking on shifting sands# in the Gerudo Training Grounds guard", /*french*/"", /*spanish*/""},
  });

  HintText GerudoTrainingGrounds_MQ_BeforeHeavyBlockChest = HintText::Exclude({
                       //obscure text
                       Text{"#before a block of silver# thieves can find", /*french*/"", /*spanish*/""},
  });

  HintText GerudoTrainingGrounds_MQ_EyeStatueChest = HintText::Exclude({
                       //obscure text
                       Text{"thieves #blind four faces# to find", /*french*/"", /*spanish*/""},
  });

  HintText GerudoTrainingGrounds_MQ_FlameCircleChest = HintText::Exclude({
                       //obscure text
                       Text{"#engulfed in flame# where thieves train lies", /*french*/"", /*spanish*/""},
  });

  HintText GerudoTrainingGrounds_MQ_SecondIronKnuckleChest = HintText::Exclude({
                       //obscure text
                       Text{"#fiery foes# in the Gerudo Training Grounds guard", /*french*/"", /*spanish*/""},
  });

  HintText GerudoTrainingGrounds_MQ_DinolfosChest = HintText::Exclude({
                       //obscure text
                       Text{"#reptilian warriors# in the Gerudo Training Grounds protect", /*french*/"", /*spanish*/""},
  });

  HintText GerudoTrainingGrounds_MQ_MazeRightCentralChest = HintText::Exclude({
                       //obscure text
                       Text{"a #path of fire# leads thieves to", /*french*/"", /*spanish*/""},
  });

  HintText GerudoTrainingGrounds_MQ_MazePathFirstChest = HintText::Exclude({
                       //obscure text
                       Text{"the first prize of #the thieves' training# is", /*french*/"", /*spanish*/""},
  });

  HintText GerudoTrainingGrounds_MQ_MazeRightSideChest = HintText::Exclude({
                       //obscure text
                       Text{"a #path of fire# leads thieves to", /*french*/"", /*spanish*/""},
  });

  HintText GerudoTrainingGrounds_MQ_MazePathThirdChest = HintText::Exclude({
                       //obscure text
                       Text{"the third prize of #the thieves' training# is", /*french*/"", /*spanish*/""},
  });

  HintText GerudoTrainingGrounds_MQ_MazePathSecondChest = HintText::Exclude({
                       //obscure text
                       Text{"the second prize of #the thieves' training# is", /*french*/"", /*spanish*/""},
  });

  HintText GerudoTrainingGrounds_MQ_HiddenCeilingChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth# in the Gerudo Training Grounds reveals", /*french*/"", /*spanish*/""},
  });

  HintText GerudoTrainingGrounds_MQ_HeavyBlockChest = HintText::Exclude({
                       //obscure text
                       Text{"a #feat of strength# rewards thieves with", /*french*/"", /*spanish*/""},
  });


  HintText GanonsCastle_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Evil King# hoards", /*french*/"", /*spanish*/""},
  });


  HintText GanonsCastle_ForestTrialChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the wilds# holds", /*french*/"", /*spanish*/""},
  });

  HintText GanonsCastle_WaterTrialLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the seas# holds", /*french*/"", /*spanish*/""},
  });

  HintText GanonsCastle_WaterTrialRightChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the seas# holds", /*french*/"", /*spanish*/""},
  });

  HintText GanonsCastle_ShadowTrialFrontChest = HintText::Exclude({
                       //obscure text
                       Text{"#music in the test of darkness# unveils", /*french*/"", /*spanish*/""},
  });

  HintText GanonsCastle_ShadowTrialGoldenGauntletsChest = HintText::Exclude({
                       //obscure text
                       Text{"#light in the test of darkness# unveils", /*french*/"", /*spanish*/""},
  });

  HintText GanonsCastle_SpiritTrialCrystalSwitchChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the sands# holds", /*french*/"", /*spanish*/""},
  });

  HintText GanonsCastle_SpiritTrialInvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the sands# holds", /*french*/"", /*spanish*/""},
  });

  HintText GanonsCastle_LightTrialFirstLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of radiance# holds", /*french*/"", /*spanish*/""},
  });

  HintText GanonsCastle_LightTrialSecondLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of radiance# holds", /*french*/"", /*spanish*/""},
  });

  HintText GanonsCastle_LightTrialThirdLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of radiance# holds", /*french*/"", /*spanish*/""},
  });

  HintText GanonsCastle_LightTrialFirstRightChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of radiance# holds", /*french*/"", /*spanish*/""},
  });

  HintText GanonsCastle_LightTrialSecondRightChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of radiance# holds", /*french*/"", /*spanish*/""},
  });

  HintText GanonsCastle_LightTrialThirdRightChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of radiance# holds", /*french*/"", /*spanish*/""},
  });

  HintText GanonsCastle_LightTrialInvisibleEnemiesChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of radiance# holds", /*french*/"", /*spanish*/""},
  });

  HintText GanonsCastle_LightTrialLullabyChest = HintText::Exclude({
                       //obscure text
                       Text{"#music in the test of radiance# reveals", /*french*/"", /*spanish*/""},
  });


  HintText GanonsCastle_MQ_WaterTrialChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the seas# holds", /*french*/"", /*spanish*/""},
  });

  HintText GanonsCastle_MQ_ForestTrialEyeSwitchChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the wilds# holds", /*french*/"", /*spanish*/""},
  });

  HintText GanonsCastle_MQ_ForestTrialFrozenEyeSwitchChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the wilds# holds", /*french*/"", /*spanish*/""},
  });

  HintText GanonsCastle_MQ_LightTrialLullabyChest = HintText::Exclude({
                       //obscure text
                       Text{"#music in the test of radiance# reveals", /*french*/"", /*spanish*/""},
  });

  HintText GanonsCastle_MQ_ShadowTrialBombFlowerChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of darkness# holds", /*french*/"", /*spanish*/""},
  });

  HintText GanonsCastle_MQ_ShadowTrialEyeSwitchChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of darkness# holds", /*french*/"", /*spanish*/""},
  });

  HintText GanonsCastle_MQ_SpiritTrialGoldenGauntletsChest = HintText::Exclude({
                       //obscure text
                       Text{"#reflected light in the test of the sands# reveals", /*french*/"", /*spanish*/""},
  });

  HintText GanonsCastle_MQ_SpiritTrialSunBackRightChest = HintText::Exclude({
                       //obscure text
                       Text{"#reflected light in the test of the sands# reveals", /*french*/"", /*spanish*/""},
  });

  HintText GanonsCastle_MQ_SpiritTrialSunBackLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"#reflected light in the test of the sands# reveals", /*french*/"", /*spanish*/""},
  });

  HintText GanonsCastle_MQ_SpiritTrialSunFrontLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"#reflected light in the test of the sands# reveals", /*french*/"", /*spanish*/""},
  });

  HintText GanonsCastle_MQ_SpiritTrialFirstChest = HintText::Exclude({
                       //obscure text
                       Text{"#reflected light in the test of the sands# reveals", /*french*/"", /*spanish*/""},
  });

  HintText GanonsCastle_MQ_SpiritTrialInvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"#reflected light in the test of the sands# reveals", /*french*/"", /*spanish*/""},
  });

  HintText GanonsCastle_MQ_ForestTrialFreestandingKey = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the wilds# holds", /*french*/"", /*spanish*/""},
  });


  HintText DekuTree_QueenGohmaHeart = HintText::Exclude({
                       //obscure text
                       Text{"the #Parasitic Armored Arachnid# holds", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"#Queen Gohma# holds", /*french*/"", /*spanish*/""}
  );

  HintText DodongosCavern_KingDodongoHeart = HintText::Exclude({
                       //obscure text
                       Text{"the #Infernal Dinosaur# holds", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"#King Dodongo# holds", /*french*/"", /*spanish*/""}
  );

  HintText JabuJabusBelly_BarinadeHeart = HintText::Exclude({
                       //obscure text
                       Text{"the #Bio-Electric Anemone# holds", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"#Barinade# holds", /*french*/"", /*spanish*/""}
  );

  HintText ForestTemple_PhantomGanonHeart = HintText::Exclude({
                       //obscure text
                       Text{"the #Evil Spirit from Beyond# holds", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"#Phantom Ganon# holds", /*french*/"", /*spanish*/""}
  );

  HintText FireTemple_VolvagiaHeart = HintText::Exclude({
                       //obscure text
                       Text{"the #Subterranean Lava Dragon# holds", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"#Volvagia# holds", /*french*/"", /*spanish*/""}
  );

  HintText WaterTemple_MorphaHeart = HintText::Exclude({
                       //obscure text
                       Text{"the #Giant Aquatic Amoeba# holds", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"#Morpha# holds", /*french*/"", /*spanish*/""}
  );

  HintText SpiritTemple_TwinrovaHeart = HintText::Exclude({
                       //obscure text
                       Text{"the #Sorceress Sisters# hold", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"#Twinrova# holds", /*french*/"", /*spanish*/""}
  );

  HintText ShadowTemple_BongoBongoHeart = HintText::Exclude({
                       //obscure text
                       Text{"the #Phantom Shadow Beast# holds", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"#Bongo Bongo# holds", /*french*/"", /*spanish*/""}
  );


  HintText DekuTree_GS_BasementBackRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider deep within the Deku Tree# hides", /*french*/"", /*spanish*/""},
  });

  HintText DekuTree_GS_BasementGate = HintText::Exclude({
                       //obscure text
                       Text{"a #web protects a spider# within the Deku Tree holding", /*french*/"", /*spanish*/""},
  });

  HintText DekuTree_GS_BasementVines = HintText::Exclude({
                       //obscure text
                       Text{"a #web protects a spider# within the Deku Tree holding", /*french*/"", /*spanish*/""},
  });

  HintText DekuTree_GS_CompassRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider atop the Deku Tree# holds", /*french*/"", /*spanish*/""},
  });


  HintText DekuTree_MQ_GS_Lobby = HintText::Exclude({
                       //obscure text
                       Text{"a #spider in a crate# within the Deku Tree hides", /*french*/"", /*spanish*/""},
  });

  HintText DekuTree_MQ_GS_CompassRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #wall of rock protects a spider# within the Deku Tree holding", /*french*/"", /*spanish*/""},
  });

  HintText DekuTree_MQ_GS_BasementBackRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider deep within the Deku Tree# hides", /*french*/"", /*spanish*/""},
  });


  HintText DodongosCavern_GS_VinesAboveStairs = HintText::Exclude({
                       //obscure text
                       Text{"a #spider entangled in vines# in Dodongo's Cavern guards", /*french*/"", /*spanish*/""},
  });

  HintText DodongosCavern_GS_Scarecrow = HintText::Exclude({
                       //obscure text
                       Text{"a #spider among explosive slugs# hides", /*french*/"", /*spanish*/""},
  });

  HintText DodongosCavern_GS_AlcoveAboveStairs = HintText::Exclude({
                       //obscure text
                       Text{"a #spider just out of reach# in Dodongo's Cavern holds", /*french*/"", /*spanish*/""},
  });

  HintText DodongosCavern_GS_BackRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider behind a statue# in Dodongo's Cavern holds", /*french*/"", /*spanish*/""},
  });

  HintText DodongosCavern_GS_SideRoomNearLowerLizalfos = HintText::Exclude({
                       //obscure text
                       Text{"a #spider among bats# in Dodongo's Cavern holds", /*french*/"", /*spanish*/""},
  });


  HintText DodongosCavern_MQ_GS_ScrubRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider high on a wall# in Dodongo's Cavern holds", /*french*/"", /*spanish*/""},
  });

  HintText DodongosCavern_MQ_GS_LizalfosRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider on top of a pillar of rock# in Dodongo's Cavern holds", /*french*/"", /*spanish*/""},
  });

  HintText DodongosCavern_MQ_GS_LarvaeRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider in a crate# in Dodongo's Cavern holds", /*french*/"", /*spanish*/""},
  });

  HintText DodongosCavern_MQ_GS_BackRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider among graves# in Dodongo's Cavern holds", /*french*/"", /*spanish*/""},
  });


  HintText JabuJabusBelly_GS_LobbyBasementLower = HintText::Exclude({
                       //obscure text
                       Text{"a #spider resting near a princess# in Jabu Jabu's Belly holds", /*french*/"", /*spanish*/""},
  });

  HintText JabuJabusBelly_GS_LobbyBasementUpper = HintText::Exclude({
                       //obscure text
                       Text{"a #spider resting near a princess# in Jabu Jabu's Belly holds", /*french*/"", /*spanish*/""},
  });

  HintText JabuJabusBelly_GS_NearBoss = HintText::Exclude({
                       //obscure text
                       Text{"#jellyfish surround a spider# holding", /*french*/"", /*spanish*/""},
  });

  HintText JabuJabusBelly_GS_WaterSwitchRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider guarded by a school of stingers# in Jabu Jabu's Belly holds", /*french*/"", /*spanish*/""},
  });


  HintText JabuJabusBelly_MQ_GS_TailPasaranRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider surrounded by electricity# in Jabu Jabu's Belly holds", /*french*/"", /*spanish*/""},
  });

  HintText JabuJabusBelly_MQ_GS_BoomerangChestRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider guarded by a school of stingers# in Jabu Jabu's Belly holds", /*french*/"", /*spanish*/""},
  });

  HintText JabuJabusBelly_MQ_GS_NearBoss = HintText::Exclude({
                       //obscure text
                       Text{"a #spider in a web within Jabu Jabu's Belly# holds", /*french*/"", /*spanish*/""},
  });


  HintText ForestTemple_GS_RaisedIslandCourtyard = HintText::Exclude({
                       //obscure text
                       Text{"a #spider on a small island# in the Forest Temple holds", /*french*/"", /*spanish*/""},
  });

  HintText ForestTemple_GS_FirstRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider high on a wall of vines# in the Forest Temple holds", /*french*/"", /*spanish*/""},
  });

  HintText ForestTemple_GS_LevelIslandCourtyard = HintText::Exclude({
                       //obscure text
                       Text{"#stone columns# lead to a spider in the Forest Temple hiding", /*french*/"", /*spanish*/""},
  });

  HintText ForestTemple_GS_Lobby = HintText::Exclude({
                       //obscure text
                       Text{"a #spider among ghosts# in the Forest Temple guards", /*french*/"", /*spanish*/""},
  });

  HintText ForestTemple_GS_Basement = HintText::Exclude({
                       //obscure text
                       Text{"a #spider within revolving walls# in the Forest Temple holds", /*french*/"", /*spanish*/""},
  });


  HintText ForestTemple_MQ_GS_FirstHallway = HintText::Exclude({
                       //obscure text
                       Text{"an #ivy-hidden spider# in the Forest Temple hoards", /*french*/"", /*spanish*/""},
  });

  HintText ForestTemple_MQ_GS_BlockPushRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider in a hidden nook# within the Forest Temple holds", /*french*/"", /*spanish*/""},
  });

  HintText ForestTemple_MQ_GS_RaisedIslandCourtyard = HintText::Exclude({
                       //obscure text
                       Text{"a #spider on an arch# in the Forest Temple holds", /*french*/"", /*spanish*/""},
  });

  HintText ForestTemple_MQ_GS_LevelIslandCourtyard = HintText::Exclude({
                       //obscure text
                       Text{"a #spider on a ledge# in the Forest Temple holds", /*french*/"", /*spanish*/""},
  });

  HintText ForestTemple_MQ_GS_Well = HintText::Exclude({
                       //obscure text
                       Text{"#draining a well# in Forest Temple uncovers a spider with", /*french*/"", /*spanish*/""},
  });


  HintText FireTemple_GS_SongOfTimeRoom = HintText::Exclude({
                       //obscure text
                       Text{"#eight tiles of malice# guard a spider holding", /*french*/"", /*spanish*/""},
  });

  HintText FireTemple_GS_BossKeyLoop = HintText::Exclude({
                       //obscure text
                       Text{"#five tiles of malice# guard a spider holding", /*french*/"", /*spanish*/""},
  });

  HintText FireTemple_GS_BoulderMaze = HintText::Exclude({
                       //obscure text
                       Text{"#explosives in a maze# unveil a spider hiding", /*french*/"", /*spanish*/""},
  });

  HintText FireTemple_GS_ScarecrowTop = HintText::Exclude({
                       //obscure text
                       Text{"a #spider-friendly scarecrow# atop a volcano hides", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a #spider-friendly scarecrow# atop the Fire Temple hides", /*french*/"", /*spanish*/""}
  );

  HintText FireTemple_GS_ScarecrowClimb = HintText::Exclude({
                       //obscure text
                       Text{"a #spider-friendly scarecrow# atop a volcano hides", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a #spider-friendly scarecrow# atop the Fire Temple hides", /*french*/"", /*spanish*/""}
  );


  HintText FireTemple_MQ_GS_AboveFireWallMaze = HintText::Exclude({
                       //obscure text
                       Text{"a #spider above a fiery maze# holds", /*french*/"", /*spanish*/""},
  });

  HintText FireTemple_MQ_GS_FireWallMazeCenter = HintText::Exclude({
                       //obscure text
                       Text{"a #spider within a fiery maze# holds", /*french*/"", /*spanish*/""},
  });

  HintText FireTemple_MQ_GS_BigLavaRoomOpenDoor = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron trapped near lava# befriended a spider with", /*french*/"", /*spanish*/""},
  });

  HintText FireTemple_MQ_GS_FireWallMazeSideRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider beside a fiery maze# holds", /*french*/"", /*spanish*/""},
  });


  HintText WaterTemple_GS_FallingPlatformRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider over a waterfall# in the Water Temple holds", /*french*/"", /*spanish*/""},
  });

  HintText WaterTemple_GS_CentralPillar = HintText::Exclude({
                       //obscure text
                       Text{"a #spider in the center of the Water Temple# holds", /*french*/"", /*spanish*/""},
  });

  HintText WaterTemple_GS_NearBossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"a spider protected by #rolling boulders under the lake# hides", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"a spider protected by #rolling boulders in the Water Temple# hides", /*french*/"", /*spanish*/""}
  );

  HintText WaterTemple_GS_River = HintText::Exclude({
                       //obscure text
                       Text{"a #spider over a river# in the Water Temple holds", /*french*/"", /*spanish*/""},
  });


  HintText WaterTemple_MQ_GS_BeforeUpperWaterSwitch = HintText::Exclude({
                       //obscure text
                       Text{"#beyond a pit of lizards# is a spider holding", /*french*/"", /*spanish*/""},
  });

  HintText WaterTemple_MQ_GS_LizalfosHallway = HintText::Exclude({
                       //obscure text
                       Text{"#lizards guard a spider# in the Water Temple with", /*french*/"", /*spanish*/""},
  });

  HintText WaterTemple_MQ_GS_River = HintText::Exclude({
                       //obscure text
                       Text{"a #spider over a river# in the Water Temple holds", /*french*/"", /*spanish*/""},
  });


  HintText SpiritTemple_GS_HallAfterSunBlockRoom = HintText::Exclude({
                       //obscure text
                       Text{"a spider in the #hall of a knight# guards", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_GS_BoulderRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider behind a temporal stone# in the Spirit Temple yields", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_GS_Lobby = HintText::Exclude({
                       //obscure text
                       Text{"a #spider beside a statue# holds", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_GS_SunOnFloorRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider at the top of a deep shaft# in the Spirit Temple holds", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_GS_MetalFence = HintText::Exclude({
                       //obscure text
                       Text{"a child defeats a #spider among bats# in the Spirit Temple to gain", /*french*/"", /*spanish*/""},
  });


  HintText SpiritTemple_MQ_GS_LeeverRoom = HintText::Exclude({
                       //obscure text
                       Text{"#above a pit of sand# in the Spirit Temple hides", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_MQ_GS_NineThronesRoomWest = HintText::Exclude({
                       //obscure text
                       Text{"a spider in the #hall of a knight# guards", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_MQ_GS_NineThronesRoomNorth = HintText::Exclude({
                       //obscure text
                       Text{"a spider in the #hall of a knight# guards", /*french*/"", /*spanish*/""},
  });

  HintText SpiritTemple_MQ_GS_SunBlockRoom = HintText::Exclude({
                       //obscure text
                       Text{"#upon a web of glass# in the Spirit Temple sits a spider holding", /*french*/"", /*spanish*/""},
  });


  HintText ShadowTemple_GS_SingleGiantPot = HintText::Exclude({
                       //obscure text
                       Text{"#beyond a burning skull# lies a spider with", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_GS_FallingSpikesRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider beyond falling spikes# holds", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_GS_TripleGiantPot = HintText::Exclude({
                       //obscure text
                       Text{"#beyond three burning skulls# lies a spider with", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_GS_LikeLikeRoom = HintText::Exclude({
                       //obscure text
                       Text{"a spider guarded by #invisible blades# holds", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_GS_NearShip = HintText::Exclude({
                       //obscure text
                       Text{"a spider near a #docked ship# hoards", /*french*/"", /*spanish*/""},
  });


  HintText ShadowTemple_MQ_GS_FallingSpikesRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider beyond falling spikes# holds", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_MQ_GS_WindHintRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider amidst roaring winds# in the Shadow Temple holds", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_MQ_GS_AfterWind = HintText::Exclude({
                       //obscure text
                       Text{"a #spider beneath gruesome debris# in the Shadow Temple hides", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_MQ_GS_AfterShip = HintText::Exclude({
                       //obscure text
                       Text{"a #fallen statue# reveals a spider with", /*french*/"", /*spanish*/""},
  });

  HintText ShadowTemple_MQ_GS_NearBoss = HintText::Exclude({
                       //obscure text
                       Text{"a #suspended spider# guards", /*french*/"", /*spanish*/""},
  });


  HintText BottomOfTheWell_GS_LikeLikeCage = HintText::Exclude({
                       //obscure text
                       Text{"a #spider locked in a cage# in the well holds", /*french*/"", /*spanish*/""},
  });

  HintText BottomOfTheWell_GS_EastInnerRoom = HintText::Exclude({
                       //obscure text
                       Text{"an #invisible path in the well# leads to", /*french*/"", /*spanish*/""},
  });

  HintText BottomOfTheWell_GS_WestInnerRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider locked in a crypt# within the well guards", /*french*/"", /*spanish*/""},
  });


  HintText BottomOfTheWell_MQ_GS_Basement = HintText::Exclude({
                       //obscure text
                       Text{"a #gauntlet of invisible spiders# protects", /*french*/"", /*spanish*/""},
  });

  HintText BottomOfTheWell_MQ_GS_CoffinRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider crawling near the dead# in the well holds", /*french*/"", /*spanish*/""},
  });

  HintText BottomOfTheWell_MQ_GS_WestInnerRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider locked in a crypt# within the well guards", /*french*/"", /*spanish*/""},
  });


  HintText IceCavern_GS_PushBlockRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider above icy pits# holds", /*french*/"", /*spanish*/""},
  });

  HintText IceCavern_GS_SpinningScytheRoom = HintText::Exclude({
                       //obscure text
                       Text{"#spinning ice# guards a spider holding", /*french*/"", /*spanish*/""},
  });

  HintText IceCavern_GS_HeartPieceRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider behind a wall of ice# hides", /*french*/"", /*spanish*/""},
  });


  HintText IceCavern_MQ_GS_Scarecrow = HintText::Exclude({
                       //obscure text
                       Text{"a #spider above icy pits# holds", /*french*/"", /*spanish*/""},
  });

  HintText IceCavern_MQ_GS_IceBlock = HintText::Exclude({
                       //obscure text
                       Text{"a #web of ice# surrounds a spider with", /*french*/"", /*spanish*/""},
  });

  HintText IceCavern_MQ_GS_RedIce = HintText::Exclude({
                       //obscure text
                       Text{"a #spider in fiery ice# hoards", /*french*/"", /*spanish*/""},
  });


  HintText HF_GS_NearKakGrotto = HintText::Exclude({
                       //obscure text
                       Text{"a #spider-guarded spider in a hole# hoards", /*french*/"", /*spanish*/""},
  });


  HintText LLR_GS_BackWall = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider in a ranch# holding", /*french*/"", /*spanish*/""},
  });

  HintText LLR_GS_RainShed = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider in a ranch# holding", /*french*/"", /*spanish*/""},
  });

  HintText LLR_GS_HouseWindow = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider in a ranch# holding", /*french*/"", /*spanish*/""},
  });

  HintText LLR_GS_Tree = HintText::Exclude({
                       //obscure text
                       Text{"a spider hiding in a #ranch tree# holds", /*french*/"", /*spanish*/""},
  });


  HintText KF_GS_BeanPatch = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried in a forest# holds", /*french*/"", /*spanish*/""},
  });

  HintText KF_GS_KnowItAllHouse = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a forest# holding", /*french*/"", /*spanish*/""},
  });

  HintText KF_GS_HouseOfTwins = HintText::Exclude({
                       //obscure text
                       Text{"night in the future reveals a #spider in a forest# holding", /*french*/"", /*spanish*/""},
  });


  HintText LW_GS_BeanPatchNearBridge = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried deep in a forest maze# holds", /*french*/"", /*spanish*/""},
  });

  HintText LW_GS_BeanPatchNearTheater = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried deep in a forest maze# holds", /*french*/"", /*spanish*/""},
  });

  HintText LW_GS_AboveTheater = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider deep in a forest maze# holding", /*french*/"", /*spanish*/""},
  });

  HintText SFM_GS = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider in a forest meadow# holding", /*french*/"", /*spanish*/""},
  });


  HintText OGC_GS = HintText::Exclude({
                       //obscure text
                       Text{"a #spider outside a tyrant's tower# holds", /*french*/"", /*spanish*/""},
  });

  HintText HC_GS_Tree = HintText::Exclude({
                       //obscure text
                       Text{"a spider hiding in a #tree outside of a castle# holds", /*french*/"", /*spanish*/""},
  });

  HintText MK_GS_GuardHouse = HintText::Exclude({
                       //obscure text
                       Text{"a #spider in a guarded crate# holds", /*french*/"", /*spanish*/""},
  });


  HintText DMC_GS_BeanPatch = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried in a volcano# holds", /*french*/"", /*spanish*/""},
  });


  HintText DMT_GS_BeanPatch = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried outside a cavern# holds", /*french*/"", /*spanish*/""},
  });

  HintText DMT_GS_NearKak = HintText::Exclude({
                       //obscure text
                       Text{"a #spider hidden in a mountain nook# holds", /*french*/"", /*spanish*/""},
  });

  HintText DMT_GS_AboveDodongosCavern = HintText::Exclude({
                       //obscure text
                       Text{"the hammer reveals a #spider on a mountain# holding", /*french*/"", /*spanish*/""},
  });

  HintText DMT_GS_FallingRocksPath = HintText::Exclude({
                       //obscure text
                       Text{"the hammer reveals a #spider on a mountain# holding", /*french*/"", /*spanish*/""},
  });


  HintText GC_GS_CenterPlatform = HintText::Exclude({
                       //obscure text
                       Text{"a #suspended spider# in Goron City holds", /*french*/"", /*spanish*/""},
  });

  HintText GC_GS_BoulderMaze = HintText::Exclude({
                       //obscure text
                       Text{"a spider in a #Goron City crate# holds", /*french*/"", /*spanish*/""},
  });


  HintText Kak_GS_HouseUnderConstruction = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a town# holding", /*french*/"", /*spanish*/""},
  });

  HintText Kak_GS_SkulltulaHouse = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a town# holding", /*french*/"", /*spanish*/""},
  });

  HintText Kak_GS_GuardsHouse = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a town# holding", /*french*/"", /*spanish*/""},
  });

  HintText Kak_GS_Tree = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a town# holding", /*french*/"", /*spanish*/""},
  });

  HintText Kak_GS_Watchtower = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a town# holding", /*french*/"", /*spanish*/""},
  });

  HintText Kak_GS_AboveImpasHouse = HintText::Exclude({
                       //obscure text
                       Text{"night in the future reveals a #spider in a town# holding", /*french*/"", /*spanish*/""},
  });


  HintText GY_GS_Wall = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider in a graveyard# holding", /*french*/"", /*spanish*/""},
  });

  HintText GY_GS_BeanPatch = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried in a graveyard# holds", /*french*/"", /*spanish*/""},
  });


  HintText ZR_GS_Ladder = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a river# holding", /*french*/"", /*spanish*/""},
  });

  HintText ZR_GS_Tree = HintText::Exclude({
                       //obscure text
                       Text{"a spider hiding in a #tree by a river# holds", /*french*/"", /*spanish*/""},
  });

  HintText ZR_GS_AboveBridge = HintText::Exclude({
                       //obscure text
                       Text{"night in the future reveals a #spider in a river# holding", /*french*/"", /*spanish*/""},
  });

  HintText ZR_GS_NearRaisedGrottos = HintText::Exclude({
                       //obscure text
                       Text{"night in the future reveals a #spider in a river# holding", /*french*/"", /*spanish*/""},
  });


  HintText ZD_GS_FrozenWaterfall = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider by a frozen waterfall# holding", /*french*/"", /*spanish*/""},
  });

  HintText ZF_GS_AboveTheLog = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider near a deity# holding", /*french*/"", /*spanish*/""},
  });

  HintText ZF_GS_Tree = HintText::Exclude({
                       //obscure text
                       Text{"a spider hiding in a #tree near a deity# holds", /*french*/"", /*spanish*/""},
  });


  HintText LH_GS_BeanPatch = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried by a lake# holds", /*french*/"", /*spanish*/""},
  });

  HintText LH_GS_SmallIsland = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider by a lake# holding", /*french*/"", /*spanish*/""},
  });

  HintText LH_GS_LabWall = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider by a lake# holding", /*french*/"", /*spanish*/""},
  });

  HintText LH_GS_LabCrate = HintText::Exclude({
                       //obscure text
                       Text{"a spider deed underwater in a #lab crate# holds", /*french*/"", /*spanish*/""},
  });

  HintText LH_GS_Tree = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider by a lake high in a tree# holding", /*french*/"", /*spanish*/""},
  });


  HintText GV_GS_BeanPatch = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried in a valley# holds", /*french*/"", /*spanish*/""},
  });

  HintText GV_GS_SmallBridge = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a valley# holding", /*french*/"", /*spanish*/""},
  });

  HintText GV_GS_Pillar = HintText::Exclude({
                       //obscure text
                       Text{"night in the future reveals a #spider in a valley# holding", /*french*/"", /*spanish*/""},
  });

  HintText GV_GS_BehindTent = HintText::Exclude({
                       //obscure text
                       Text{"night in the future reveals a #spider in a valley# holding", /*french*/"", /*spanish*/""},
  });


  HintText GF_GS_ArcheryRange = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider in a fortress# holding", /*french*/"", /*spanish*/""},
  });

  HintText GF_GS_TopFloor = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider in a fortress# holding", /*french*/"", /*spanish*/""},
  });


  HintText Colossus_GS_BeanPatch = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried in the desert# holds", /*french*/"", /*spanish*/""},
  });

  HintText Colossus_GS_Hill = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider deep in the desert# holding", /*french*/"", /*spanish*/""},
  });

  HintText Colossus_GS_Tree = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider deep in the desert# holding", /*french*/"", /*spanish*/""},
  });


  HintText KF_ShopItem1 = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", /*french*/"", /*spanish*/""},
  });

  HintText KF_ShopItem2 = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", /*french*/"", /*spanish*/""},
  });

  HintText KF_ShopItem3 = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", /*french*/"", /*spanish*/""},
  });

  HintText KF_ShopItem4 = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", /*french*/"", /*spanish*/""},
  });

  HintText KF_ShopItem5 = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", /*french*/"", /*spanish*/""},
  });

  HintText KF_ShopItem6 = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", /*french*/"", /*spanish*/""},
  });

  HintText KF_ShopItem7 = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", /*french*/"", /*spanish*/""},
  });

  HintText KF_ShopItem8 = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", /*french*/"", /*spanish*/""},
  });


  HintText Kak_PotionShopItem1 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", /*french*/"", /*spanish*/""}
  );

  HintText Kak_PotionShopItem2 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", /*french*/"", /*spanish*/""}
  );

  HintText Kak_PotionShopItem3 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", /*french*/"", /*spanish*/""}
  );

  HintText Kak_PotionShopItem4 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", /*french*/"", /*spanish*/""}
  );

  HintText Kak_PotionShopItem5 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", /*french*/"", /*spanish*/""}
  );

  HintText Kak_PotionShopItem6 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", /*french*/"", /*spanish*/""}
  );

  HintText Kak_PotionShopItem7 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", /*french*/"", /*spanish*/""}
  );

  HintText Kak_PotionShopItem8 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", /*french*/"", /*spanish*/""}
  );


  HintText MK_BombchuShopItem1 = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", /*french*/"", /*spanish*/""},
  });

  HintText MK_BombchuShopItem2 = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", /*french*/"", /*spanish*/""},
  });

  HintText MK_BombchuShopItem3 = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", /*french*/"", /*spanish*/""},
  });

  HintText MK_BombchuShopItem4 = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", /*french*/"", /*spanish*/""},
  });

  HintText MK_BombchuShopItem5 = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", /*french*/"", /*spanish*/""},
  });

  HintText MK_BombchuShopItem6 = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", /*french*/"", /*spanish*/""},
  });

  HintText MK_BombchuShopItem7 = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", /*french*/"", /*spanish*/""},
  });

  HintText MK_BombchuShopItem8 = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", /*french*/"", /*spanish*/""},
  });


  HintText MK_PotionShopItem1 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", /*french*/"", /*spanish*/""}
  );

  HintText MK_PotionShopItem2 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", /*french*/"", /*spanish*/""}
  );

  HintText MK_PotionShopItem3 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", /*french*/"", /*spanish*/""}
  );

  HintText MK_PotionShopItem4 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", /*french*/"", /*spanish*/""}
  );

  HintText MK_PotionShopItem5 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", /*french*/"", /*spanish*/""}
  );

  HintText MK_PotionShopItem6 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", /*french*/"", /*spanish*/""}
  );

  HintText MK_PotionShopItem7 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", /*french*/"", /*spanish*/""}
  );

  HintText MK_PotionShopItem8 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/""},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", /*french*/"", /*spanish*/""}
  );


  HintText MK_BazaarItem1 = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", /*french*/"", /*spanish*/""},
  });

  HintText MK_BazaarItem2 = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", /*french*/"", /*spanish*/""},
  });

  HintText MK_BazaarItem3 = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", /*french*/"", /*spanish*/""},
  });

  HintText MK_BazaarItem4 = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", /*french*/"", /*spanish*/""},
  });

  HintText MK_BazaarItem5 = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", /*french*/"", /*spanish*/""},
  });

  HintText MK_BazaarItem6 = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", /*french*/"", /*spanish*/""},
  });

  HintText MK_BazaarItem7 = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", /*french*/"", /*spanish*/""},
  });

  HintText MK_BazaarItem8 = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", /*french*/"", /*spanish*/""},
  });


  HintText Kak_BazaarItem1 = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", /*french*/"", /*spanish*/""},
  });

  HintText Kak_BazaarItem2 = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", /*french*/"", /*spanish*/""},
  });

  HintText Kak_BazaarItem3 = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", /*french*/"", /*spanish*/""},
  });

  HintText Kak_BazaarItem4 = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", /*french*/"", /*spanish*/""},
  });

  HintText Kak_BazaarItem5 = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", /*french*/"", /*spanish*/""},
  });

  HintText Kak_BazaarItem6 = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", /*french*/"", /*spanish*/""},
  });

  HintText Kak_BazaarItem7 = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", /*french*/"", /*spanish*/""},
  });

  HintText Kak_BazaarItem8 = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", /*french*/"", /*spanish*/""},
  });


  HintText ZD_ShopItem1 = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", /*french*/"", /*spanish*/""},
  });

  HintText ZD_ShopItem2 = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", /*french*/"", /*spanish*/""},
  });

  HintText ZD_ShopItem3 = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", /*french*/"", /*spanish*/""},
  });

  HintText ZD_ShopItem4 = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", /*french*/"", /*spanish*/""},
  });

  HintText ZD_ShopItem5 = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", /*french*/"", /*spanish*/""},
  });

  HintText ZD_ShopItem6 = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", /*french*/"", /*spanish*/""},
  });

  HintText ZD_ShopItem7 = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", /*french*/"", /*spanish*/""},
  });

  HintText ZD_ShopItem8 = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", /*french*/"", /*spanish*/""},
  });


  HintText GC_ShopItem1 = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", /*french*/"", /*spanish*/""},
  });

  HintText GC_ShopItem2 = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", /*french*/"", /*spanish*/""},
  });

  HintText GC_ShopItem3 = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", /*french*/"", /*spanish*/""},
  });

  HintText GC_ShopItem4 = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", /*french*/"", /*spanish*/""},
  });

  HintText GC_ShopItem5 = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", /*french*/"", /*spanish*/""},
  });

  HintText GC_ShopItem6 = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", /*french*/"", /*spanish*/""},
  });

  HintText GC_ShopItem7 = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", /*french*/"", /*spanish*/""},
  });

  HintText GC_ShopItem8 = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", /*french*/"", /*spanish*/""},
  });


  HintText DekuTree_MQ_DekuScrub = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub in the Deku Tree# sells", /*french*/"", /*spanish*/""},
  });


  HintText HF_DekuScrubGrotto = HintText::Exclude({
                       //obscure text
                       Text{"a lonely #scrub in a hole# sells", /*french*/"", /*spanish*/""},
  });

  HintText LLR_DekuScrubGrottoLeft = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"", /*spanish*/""},
  });

  HintText LLR_DekuScrubGrottoRight = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"", /*spanish*/""},
  });

  HintText LLR_DekuScrubGrottoCenter = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"", /*spanish*/""},
  });


  HintText LW_DekuScrubNearDekuTheaterRight = HintText::Exclude({
                       //obscure text
                       Text{"a pair of #scrubs in the woods# sells", /*french*/"", /*spanish*/""},
  });

  HintText LW_DekuScrubNearDekuTheaterLeft = HintText::Exclude({
                       //obscure text
                       Text{"a pair of #scrubs in the woods# sells", /*french*/"", /*spanish*/""},
  });

  HintText LW_DekuScrubNearBridge = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub by a bridge# sells", /*french*/"", /*spanish*/""},
  });

  HintText LW_DekuScrubGrottoRear = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"", /*spanish*/""},
  });

  HintText LW_DekuScrubGrottoFront = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"", /*spanish*/""},
  });


  HintText SFM_DekuScrubGrottoRear = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"", /*spanish*/""},
  });

  HintText SFM_DekuScrubGrottoFront = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"", /*spanish*/""},
  });


  HintText GC_DekuScrubGrottoLeft = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"", /*spanish*/""},
  });

  HintText GC_DekuScrubGrottoRight = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"", /*spanish*/""},
  });

  HintText GC_DekuScrubGrottoCenter = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"", /*spanish*/""},
  });


  HintText DodongosCavern_DekuScrubNearBombBagLeft = HintText::Exclude({
                       //obscure text
                       Text{"a pair of #scrubs in Dodongo's Cavern# sells", /*french*/"", /*spanish*/""},
  });

  HintText DodongosCavern_DekuScrubSideRoomNearDodongos = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub guarded by Lizalfos# sells", /*french*/"", /*spanish*/""},
  });

  HintText DodongosCavern_DekuScrubNearBombBagRight = HintText::Exclude({
                       //obscure text
                       Text{"a pair of #scrubs in Dodongo's Cavern# sells", /*french*/"", /*spanish*/""},
  });

  HintText DodongosCavern_DekuScrubLobby = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub in Dodongo's Cavern# sells", /*french*/"", /*spanish*/""},
  });


  HintText DodongosCavern_MQ_DekuScrubLobbyRear = HintText::Exclude({
                       //obscure text
                       Text{"a pair of #scrubs in Dodongo's Cavern# sells", /*french*/"", /*spanish*/""},
  });

  HintText DodongosCavern_MQ_DekuScrubLobbyFront = HintText::Exclude({
                       //obscure text
                       Text{"a pair of #scrubs in Dodongo's Cavern# sells", /*french*/"", /*spanish*/""},
  });

  HintText DodongosCavern_MQ_DekuScrubStaircase = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub in Dodongo's Cavern# sells", /*french*/"", /*spanish*/""},
  });

  HintText DodongosCavern_MQ_DekuScrubSideRoomNearLowerLizalfos = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub guarded by Lizalfos# sells", /*french*/"", /*spanish*/""},
  });


  HintText DMC_DekuScrubGrottoLeft = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"", /*spanish*/""},
  });

  HintText DMC_DekuScrubGrottoRight = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"", /*spanish*/""},
  });

  HintText DMC_DekuScrubGrottoCenter = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"", /*spanish*/""},
  });


  HintText ZR_DekuScrubGrottoRear = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"", /*spanish*/""},
  });

  HintText ZR_DekuScrubGrottoFront = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"", /*spanish*/""},
  });


  HintText JabuJabusBelly_DekuScrub = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub in a deity# sells", /*french*/"", /*spanish*/""},
  });


  HintText LH_DekuScrubGrottoLeft = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"", /*spanish*/""},
  });

  HintText LH_DekuScrubGrottoRight = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"", /*spanish*/""},
  });

  HintText LH_DekuScrubGrottoCenter = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"", /*spanish*/""},
  });


  HintText GV_DekuScrubGrottoRear = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"", /*spanish*/""},
  });

  HintText GV_DekuScrubGrottoFront = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"", /*spanish*/""},
  });


  HintText Colossus_DekuScrubGrottoFront = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"", /*spanish*/""},
  });

  HintText Colossus_DekuScrubGrottoRear = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"", /*spanish*/""},
  });


  HintText GanonsCastle_DekuScrubCenterLeft = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", /*french*/"", /*spanish*/""},
  });

  HintText GanonsCastle_DekuScrubCenterRight = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", /*french*/"", /*spanish*/""},
  });

  HintText GanonsCastle_DekuScrubRight = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", /*french*/"", /*spanish*/""},
  });

  HintText GanonsCastle_DekuScrubLeft = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", /*french*/"", /*spanish*/""},
  });


  HintText GanonsCastle_MQ_DekuScrubRight = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", /*french*/"", /*spanish*/""},
  });

  HintText GanonsCastle_MQ_DekuScrubCenterLeft = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", /*french*/"", /*spanish*/""},
  });

  HintText GanonsCastle_MQ_DekuScrubCenter = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", /*french*/"", /*spanish*/""},
  });

  HintText GanonsCastle_MQ_DekuScrubCenterRight = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", /*french*/"", /*spanish*/""},
  });

  HintText GanonsCastle_MQ_DekuScrubLeft = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", /*french*/"", /*spanish*/""},
  });


  HintText LLR_StablesLeftCow = HintText::Exclude({
                       //obscure text
                       Text{"a #cow in a stable# gifts", /*french*/"", /*spanish*/""},
  });

  HintText LLR_StablesRightCow = HintText::Exclude({
                       //obscure text
                       Text{"a #cow in a stable# gifts", /*french*/"", /*spanish*/""},
  });

  HintText LLR_TowerRightCow = HintText::Exclude({
                       //obscure text
                       Text{"a #cow in a ranch silo# gifts", /*french*/"", /*spanish*/""},
  });

  HintText LLR_TowerLeftCow = HintText::Exclude({
                       //obscure text
                       Text{"a #cow in a ranch silo# gifts", /*french*/"", /*spanish*/""},
  });

  HintText Kak_ImpasHouseCow = HintText::Exclude({
                       //obscure text
                       Text{"a #cow imprisoned in a house# protects", /*french*/"", /*spanish*/""},
  });

  HintText DMT_CowGrottoCow = HintText::Exclude({
                       //obscure text
                       Text{"a #cow in a luxurious hole# offers", /*french*/"", /*spanish*/""},
  });

  /*--------------------------
  |    ENTRANCE HINT TEXT    |
  ---------------------------*/

  HintText DesertColossus_To_ColossusGrotto = HintText::Entrance({
                     //obscure text
                     Text{"lifting a #rock in the desert# reveals", /*french*/"", /*spanish*/""},
  });

  HintText GVGrottoLedge_To_GVOctorokGrotto = HintText::Entrance({
                     //obscure text
                     Text{"a rock on #a ledge in the valley# hides", /*french*/"", /*spanish*/""},
  });

  HintText GCGrottoPlatform_To_GCGrotto = HintText::Entrance({
                     //obscure text
                     Text{"a #pool of lava# in Goron City blocks the way to", /*french*/"", /*spanish*/""},
  });

  HintText GerudoFortress_To_GFStormsGrotto = HintText::Entrance({
                     //obscure text
                     Text{"a #storm within Gerudo's Fortress# reveals", /*french*/"", /*spanish*/""},
  });

  HintText ZorasDomain_To_ZDStormsGrotto = HintText::Entrance({
                     //obscure text
                     Text{"a #storm within Zora's Domain# reveals", /*french*/"", /*spanish*/""},
  });

  HintText HyruleCastleGrounds_To_HCStormsGrotto = HintText::Entrance({
                     //obscure text
                     Text{"a #storm near the castle# reveals", /*french*/"", /*spanish*/""},
  });

  HintText GVFortressSide_To_GVStormsGrotto = HintText::Entrance({
                     //obscure text
                     Text{"a #storm in the valley# reveals", /*french*/"", /*spanish*/""},
  });

  HintText DesertColossus_To_ColossusGreatFairyFountain = HintText::Entrance({
                     //obscure text
                     Text{"a #fractured desert wall# hides", /*french*/"", /*spanish*/""},
  });

  HintText GanonsCastleGrounds_To_OGCGreatFairyFountain = HintText::Entrance({
                     //obscure text
                     Text{"a #heavy pillar# outside the castle obstructs", /*french*/"", /*spanish*/""},
  });

  HintText ZorasFountain_To_ZFGreatFairyFountain = HintText::Entrance({
                     //obscure text
                     Text{"a #fountain wall# hides", /*french*/"", /*spanish*/""},
  });

  HintText GVFortressSide_To_GVCarpenterTent = HintText::Entrance({
                     //obscure text
                     Text{"a #tent in the valley# covers", /*french*/"", /*spanish*/""},
  });

  HintText GYWarpPadRegion_To_ShadowTempleEntryway = HintText::Entrance({
                     //obscure text
                     Text{"at the #back of the Graveyard#, there is", /*french*/"", /*spanish*/""},
  });

  HintText LakeHylia_To_WaterTempleLobby = HintText::Entrance({
                     //obscure text
                     Text{"deep #under a vast lake#, one can find", /*french*/"", /*spanish*/""},
  });

  HintText GerudoFortress_To_GerudoTrainingGroundsLobby = HintText::Entrance({
                     //obscure text
                     Text{"paying a #fee to the Gerudos# grants access to", /*french*/"", /*spanish*/""},
  });

  HintText ZorasFountain_To_JabuJabusBellyBeginning = HintText::Entrance({
                     //obscure text
                     Text{"inside #Jabu Jabu#, one can find", /*french*/"", /*spanish*/""},
  });

  HintText KakarikoVillage_To_BottomOfTheWell = HintText::Entrance({
                     //obscure text
                     Text{"a #village well# leads to", /*french*/"", /*spanish*/""},
  });

  /*--------------------------
  |      EXIT HINT TEXT      |
  ---------------------------*/
  //maybe make a new type for this? I'm not sure if it really matters

  HintText LinksPocket = HintText::Exclude({
                     //obscure text
                     Text{"Link's Pocket", /*french*/"", /*spanish*/""},
  });

  HintText KokiriForest = HintText::Exclude({
                     //obscure text
                     Text{"Kokiri Forest", /*french*/"", /*spanish*/""},
  });

  HintText TheLostWoods = HintText::Exclude({
                     //obscure text
                     Text{"the Lost Woods", /*french*/"", /*spanish*/""},
  });

  HintText SacredForestMeadow = HintText::Exclude({
                     //obscure text
                     Text{"Sacred Forest Meadow", /*french*/"", /*spanish*/""},
  });

  HintText HyruleField = HintText::Exclude({
                     //obscure text
                     Text{"Hyrule Field", /*french*/"", /*spanish*/""},
  });

  HintText LakeHylia = HintText::Exclude({
                     //obscure text
                     Text{"Lake Hylia", /*french*/"", /*spanish*/""},
  });

  HintText GerudoValley = HintText::Exclude({
                     //obscure text
                     Text{"Gerudo Valley", /*french*/"", /*spanish*/""},
  });

  HintText GerudosFortress = HintText::Exclude({
                     //obscure text
                     Text{"Gerudo's Fortress", /*french*/"", /*spanish*/""},
  });

  HintText HauntedWasteland = HintText::Exclude({
                     //obscure text
                     Text{"Haunted Wasteland", /*french*/"", /*spanish*/""},
  });

  HintText DesertColossus = HintText::Exclude({
                     //obscure text
                     Text{"Desert Colossus", /*french*/"", /*spanish*/""},
  });

  HintText TheMarket = HintText::Exclude({
                     //obscure text
                     Text{"the Market", /*french*/"", /*spanish*/""},
  });

  HintText TempleOfTime = HintText::Exclude({
                     //obscure text
                     Text{"Temple of Time", /*french*/"", /*spanish*/""},
  });

  HintText HyruleCastle = HintText::Exclude({
                     //obscure text
                     Text{"Hyrule Castle", /*french*/"", /*spanish*/""},
  });

  HintText OutsideGanonsCastle = HintText::Exclude({
                     //obscure text
                     Text{"outside Ganon's Castle", /*french*/"", /*spanish*/""},
  });

  HintText KakarikoVillage = HintText::Exclude({
                     //obscure text
                     Text{"Kakariko Village", /*french*/"", /*spanish*/""},
  });

  HintText TheGraveyard = HintText::Exclude({
                     //obscure text
                     Text{"the Graveyard", /*french*/"", /*spanish*/""},
  });

  HintText DeathMountainTrail = HintText::Exclude({
                     //obscure text
                     Text{"Death Mountain Trail", /*french*/"", /*spanish*/""},
  });

  HintText GoronCity = HintText::Exclude({
                     //obscure text
                     Text{"Goron City", /*french*/"", /*spanish*/""},
  });

  HintText DeathMountainCrater = HintText::Exclude({
                     //obscure text
                     Text{"Death Mountain Crater", /*french*/"", /*spanish*/""},
  });

  HintText ZorasRiver = HintText::Exclude({
                     //obscure text
                     Text{"Zora's River", /*french*/"", /*spanish*/""},
  });

  HintText ZorasDomain = HintText::Exclude({
                     //obscure text
                     Text{"Zora's Domain", /*french*/"", /*spanish*/""},
  });

  HintText ZorasFountain = HintText::Exclude({
                     //obscure text
                     Text{"Zora's Fountain", /*french*/"", /*spanish*/""},
  });

  HintText LonLonRanch = HintText::Exclude({
                     //obscure text
                     Text{"Lon Lon Ranch", /*french*/"", /*spanish*/""},
  });


  /*--------------------------
  |     REGION HINT TEXT     |
  ---------------------------*/

  HintText KF_LinksHouse = HintText::Region({
                     //obscure text
                     Text{"Link's House", /*french*/"", /*spanish*/""},
  });

  HintText ToT_Main = HintText::Region({
                     //obscure text
                     Text{"the #Temple of Time#", /*french*/"", /*spanish*/""},
  });

  HintText KF_MidosHouse = HintText::Region({
                     //obscure text
                     Text{"Mido's house", /*french*/"", /*spanish*/""},
  });

  HintText KF_SariasHouse = HintText::Region({
                     //obscure text
                     Text{"Saria's House", /*french*/"", /*spanish*/""},
  });

  HintText KF_HouseOfTwins = HintText::Region({
                     //obscure text
                     Text{"the #House of Twins#", /*french*/"", /*spanish*/""},
  });

  HintText KF_KnowItAllHouse = HintText::Region({
                     //obscure text
                     Text{"Know-It-All Brothers' House", /*french*/"", /*spanish*/""},
  });

  HintText KF_KokiriShop = HintText::Region({
                     //obscure text
                     Text{"the #Kokiri Shop#", /*french*/"", /*spanish*/""},
  });

  HintText LH_Lab = HintText::Region({
                     //obscure text
                     Text{"the #Lakeside Laboratory#", /*french*/"", /*spanish*/""},
  });

  HintText LH_FishingHole = HintText::Region({
                     //obscure text
                     Text{"the #Fishing Pond#", /*french*/"", /*spanish*/""},
  });

  HintText GV_CarpenterTent = HintText::Region({
                     //obscure text
                     Text{"the #Carpenters' tent#", /*french*/"", /*spanish*/""},
  });

  HintText MK_GuardHouse = HintText::Region({
                     //obscure text
                     Text{"the #Guard House#", /*french*/"", /*spanish*/""},
  });

  HintText MK_MaskShop = HintText::Region({
                     //obscure text
                     Text{"the #Happy Mask Shop#", /*french*/"", /*spanish*/""},
  });

  HintText MK_BombchuBowling = HintText::Region({
                     //obscure text
                     Text{"the #Bombchu Bowling Alley#", /*french*/"", /*spanish*/""},
  });

  HintText MK_PotionShop = HintText::Region({
                     //obscure text
                     Text{"the #Market Potion Shop#", /*french*/"", /*spanish*/""},
  });

  HintText MK_TreasureChestGame = HintText::Region({
                     //obscure text
                     Text{"the #Treasure Box Shop#", /*french*/"", /*spanish*/""},
  });

  HintText MK_BombchuShop = HintText::Region({
                     //obscure text
                     Text{"the #Bombchu Shop#", /*french*/"", /*spanish*/""},
  });

  HintText MK_ManInGreenHouse = HintText::Region({
                     //obscure text
                     Text{"Man in Green's House", /*french*/"", /*spanish*/""},
  });

  HintText Kak_Windmill = HintText::Region({
                     //obscure text
                     Text{"the #Windmill#", /*french*/"", /*spanish*/""},
  });

  HintText Kak_CarpenterBossHouse = HintText::Region({
                     //obscure text
                     Text{"the #Carpenters' Boss House#", /*french*/"", /*spanish*/""},
  });

  HintText Kak_HouseOfSkulltula = HintText::Region({
                     //obscure text
                     Text{"the #House of Skulltula#", /*french*/"", /*spanish*/""},
  });

  HintText Kak_ImpasHouse = HintText::Region({
                     //obscure text
                     Text{"Impa's House", /*french*/"", /*spanish*/""},
  });

  HintText Kak_ImpasHouseBack = HintText::Region({
                     //obscure text
                     Text{"Impa's cow cage", /*french*/"", /*spanish*/""},
  });

  HintText Kak_OddMedicineBuilding = HintText::Region({
                     //obscure text
                     Text{"Granny's Potion Shop", /*french*/"", /*spanish*/""},
  });

  HintText GY_DampesHouse = HintText::Region({
                     //obscure text
                     Text{"Dampe's Hut", /*french*/"", /*spanish*/""},
  });

  HintText GC_Shop = HintText::Region({
                     //obscure text
                     Text{"the #Goron Shop#", /*french*/"", /*spanish*/""},
  });

  HintText ZD_Shop = HintText::Region({
                     //obscure text
                     Text{"the #Zora Shop#", /*french*/"", /*spanish*/""},
  });

  HintText LLR_TalonsHouse = HintText::Region({
                     //obscure text
                     Text{"Talon's House", /*french*/"", /*spanish*/""},
  });

  HintText LLR_Stables = HintText::Region({
                     //obscure text
                     Text{"a #stable#", /*french*/"", /*spanish*/""},
  });

  HintText LLR_Tower = HintText::Region({
                     //obscure text
                     Text{"the #Lon Lon Tower#", /*french*/"", /*spanish*/""},
  });

  HintText MK_Bazaar = HintText::Region({
                     //obscure text
                     Text{"the #Market Bazaar#", /*french*/"", /*spanish*/""},
  });

  HintText MK_ShootingGallery = HintText::Region({
                     //obscure text
                     Text{"a #Slingshot Shooting Gallery#", /*french*/"", /*spanish*/""},
  });

  HintText Kak_Bazaar = HintText::Region({
                     //obscure text
                     Text{"the #Kakariko Bazaar#", /*french*/"", /*spanish*/""},
  });

  HintText Kak_PotionShopFront = HintText::Region({
                     //obscure text
                     Text{"the #Kakariko Potion Shop#", /*french*/"", /*spanish*/""},
  });

  HintText Kak_PotionShopBack = HintText::Region({
                     //obscure text
                     Text{"the #Kakariko Potion Shop#", /*french*/"", /*spanish*/""},
  });

  HintText Kak_ShootingGallery = HintText::Region({
                     //obscure text
                     Text{"a #Bow Shooting Gallery#", /*french*/"", /*spanish*/""},
  });

  HintText Colossus_GreatFairyFountain = HintText::Region({
                     //obscure text
                     Text{"a #Great Fairy Fountain#", /*french*/"", /*spanish*/""},
  });

  HintText HC_GreatFairyFountain = HintText::Region({
                     //obscure text
                     Text{"a #Great Fairy Fountain#", /*french*/"", /*spanish*/""},
  });

  HintText OGC_GreatFairyFountain = HintText::Region({
                     //obscure text
                     Text{"a #Great Fairy Fountain#", /*french*/"", /*spanish*/""},
  });

  HintText DMC_GreatFairyFountain = HintText::Region({
                     //obscure text
                     Text{"a #Great Fairy Fountain#", /*french*/"", /*spanish*/""},
  });

  HintText DMT_GreatFairyFountain = HintText::Region({
                     //obscure text
                     Text{"a #Great Fairy Fountain#", /*french*/"", /*spanish*/""},
  });

  HintText ZF_GreatFairyFountain = HintText::Region({
                     //obscure text
                     Text{"a #Great Fairy Fountain#", /*french*/"", /*spanish*/""},
  });

  HintText GY_ShieldGrave = HintText::Region({
                     //obscure text
                     Text{"a #grave with a free chest#", /*french*/"", /*spanish*/""},
  });

  HintText GY_HeartPieceGrave = HintText::Region({
                     //obscure text
                     Text{"a chest spawned by #Sun's Song#", /*french*/"", /*spanish*/""},
  });

  HintText GY_ComposersGrave = HintText::Region({
                     //obscure text
                     Text{"the #Composers' Grave#", /*french*/"", /*spanish*/""},
  });

  HintText GY_DampesGrave = HintText::Region({
                     //obscure text
                     Text{"Dampe's Grave", /*french*/"", /*spanish*/""},
  });

  HintText DMT_CowGrotto = HintText::Region({
                     //obscure text
                     Text{"a solitary #Cow#", /*french*/"", /*spanish*/""},
  });

  HintText HC_StormsGrotto = HintText::Region({
                     //obscure text
                     Text{"a sandy grotto with #fragile walls#", /*french*/"", /*spanish*/""},
  });

  HintText HF_TektiteGrotto = HintText::Region({
                     //obscure text
                     Text{"a pool guarded by a #Tektite#", /*french*/"", /*spanish*/""},
  });

  HintText HF_NearKakGrotto = HintText::Region({
                     //obscure text
                     Text{"a #Big Skulltula# guarding a Gold one", /*french*/"", /*spanish*/""},
  });

  HintText HF_CowGrotto = HintText::Region({
                     //obscure text
                     Text{"a grotto full of #spider webs#", /*french*/"", /*spanish*/""},
  });

  HintText Kak_RedeadGrotto = HintText::Region({
                     //obscure text
                     Text{"#ReDeads# guarding a chest", /*french*/"", /*spanish*/""},
  });

  HintText SFM_WolfosGrotto = HintText::Region({
                     //obscure text
                     Text{"#Wolfos# guarding a chest", /*french*/"", /*spanish*/""},
  });

  HintText GV_OctorokGrotto = HintText::Region({
                     //obscure text
                     Text{"an #Octorok# guarding a rich pool", /*french*/"", /*spanish*/""},
  });

  HintText DekuTheater = HintText::Region({
                     //obscure text
                     Text{"the #Lost Woods Stage#", /*french*/"", /*spanish*/""},
  });

  HintText ZR_OpenGrotto = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", /*french*/"", /*spanish*/""},
  });

  HintText DMC_UpperGrotto = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", /*french*/"", /*spanish*/""},
  });

  HintText DMT_StormsGrotto = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", /*french*/"", /*spanish*/""},
  });

  HintText Kak_OpenGrotto = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", /*french*/"", /*spanish*/""},
  });

  HintText HF_NearMKGrotto = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", /*french*/"", /*spanish*/""},
  });

  HintText HF_OpenGrotto = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", /*french*/"", /*spanish*/""},
  });

  HintText HF_SoutheastGrotto = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", /*french*/"", /*spanish*/""},
  });

  HintText KF_StormsGrotto = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", /*french*/"", /*spanish*/""},
  });

  HintText LW_NearShortcutsGrotto = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", /*french*/"", /*spanish*/""},
  });

  HintText HF_InsideFenceGrotto = HintText::Region({
                     //obscure text
                     Text{"a #single Upgrade Deku Scrub#", /*french*/"", /*spanish*/""},
  });

  HintText LW_ScrubsGrotto = HintText::Region({
                     //obscure text
                     Text{"#2 Deku Scrubs# including an Upgrade one", /*french*/"", /*spanish*/""},
  });

  HintText Colossus_Grotto = HintText::Region({
                     //obscure text
                     Text{"2 Deku Scrubs", /*french*/"", /*spanish*/""},
  });

  HintText ZR_StormsGrotto = HintText::Region({
                     //obscure text
                     Text{"2 Deku Scrubs", /*french*/"", /*spanish*/""},
  });

  HintText SFM_StormsGrotto = HintText::Region({
                     //obscure text
                     Text{"2 Deku Scrubs", /*french*/"", /*spanish*/""},
  });

  HintText GV_StormsGrotto = HintText::Region({
                     //obscure text
                     Text{"2 Deku Scrubs", /*french*/"", /*spanish*/""},
  });

  HintText LH_Grotto = HintText::Region({
                     //obscure text
                     Text{"3 Deku Scrubs", /*french*/"", /*spanish*/""},
  });

  HintText DMC_HammerGrotto = HintText::Region({
                     //obscure text
                     Text{"3 Deku Scrubs", /*french*/"", /*spanish*/""},
  });

  HintText GC_Grotto = HintText::Region({
                     //obscure text
                     Text{"3 Deku Scrubs", /*french*/"", /*spanish*/""},
  });

  HintText LLR_Grotto = HintText::Region({
                     //obscure text
                     Text{"3 Deku Scrubs", /*french*/"", /*spanish*/""},
  });

  HintText ZR_FairyGrotto = HintText::Region({
                     //obscure text
                     Text{"a small #Fairy Fountain#", /*french*/"", /*spanish*/""},
  });

  HintText HF_FairyGrotto = HintText::Region({
                     //obscure text
                     Text{"a small #Fairy Fountain#", /*french*/"", /*spanish*/""},
  });

  HintText SFM_FairyGrotto = HintText::Region({
                     //obscure text
                     Text{"a small #Fairy Fountain#", /*french*/"", /*spanish*/""},
  });

  HintText ZD_StormsGrotto = HintText::Region({
                     //obscure text
                     Text{"a small #Fairy Fountain#", /*french*/"", /*spanish*/""},
  });

  HintText GF_StormsGrotto = HintText::Region({
                     //obscure text
                     Text{"a small #Fairy Fountain#", /*french*/"", /*spanish*/""},
  });

  /*--------------------------
  |      JUNK HINT TEXT      |
  ---------------------------*/

  HintText Junk01 = HintText::Junk({
                     //obscure text
                     Text{"Ganondorf 2022!", /*french*/"", /*spanish*/""},
  });

  HintText Junk02 = HintText::Junk({
                     //obscure text
                     Text{"They say that monarchy is a terrible system of governance.", /*french*/"", /*spanish*/""},
  });

  HintText Junk03 = HintText::Junk({
                     //obscure text
                     Text{"They say that Zelda is a poor leader.", /*french*/"", /*spanish*/""},
  });

  HintText Junk04 = HintText::Junk({
                     //obscure text
                     Text{"These hints can be quite useful. This is an exception.", /*french*/"", /*spanish*/""},
  });

  HintText Junk06 = HintText::Junk({
                     //obscure text
                     Text{"They say that all the Zora drowned in Wind Waker.", /*french*/"", /*spanish*/""},
  });

  HintText Junk08 = HintText::Junk({
                     //obscure text
                     Text{"'Member when Ganon was a blue pig?^I 'member.", /*french*/"", /*spanish*/""},
  });

  HintText Junk09 = HintText::Junk({
                     //obscure text
                     Text{"One who does not have Triforce can't go in.", /*french*/"", /*spanish*/""},
  });

  HintText Junk10 = HintText::Junk({
                     //obscure text
                     Text{"Save your future, end the Happy Mask Salesman.", /*french*/"", /*spanish*/""},
  });

  HintText Junk12 = HintText::Junk({
                     //obscure text
                     Text{"I'm stoned. Get it?", /*french*/"", /*spanish*/""},
  });

  HintText Junk13 = HintText::Junk({
                     //obscure text
                     Text{"Hoot! Hoot! Would you like me to repeat that?", /*french*/"", /*spanish*/""},
  });

  HintText Junk14 = HintText::Junk({
                     //obscure text
                     Text{"Gorons are stupid. They eat rocks.", /*french*/"", /*spanish*/""},
  });

  HintText Junk15 = HintText::Junk({
                     //obscure text
                     Text{"They say that Lon Lon Ranch prospered under Ingo.", /*french*/"", /*spanish*/""},
  });

  HintText Junk16 = HintText::Junk({
                     //obscure text
                     Text{"The single rupee is a unique item.", /*french*/"", /*spanish*/""},
  });

  HintText Junk17 = HintText::Junk({
                     //obscure text
                     Text{"Without the Lens of Truth, the Treasure Chest Mini-Game is a 1 out of 32 chance.^Good luck!", /*french*/"", /*spanish*/""},
  });

  HintText Junk18 = HintText::Junk({
                     //obscure text
                     Text{"Use bombs wisely.", /*french*/"", /*spanish*/""},
  });

  HintText Junk21 = HintText::Junk({
                     //obscure text
                     Text{"I found you, faker!", /*french*/"", /*spanish*/""},
  });

  HintText Junk22 = HintText::Junk({
                     //obscure text
                     Text{"You're comparing yourself to me?^Ha! You're not even good enough to be my fake.", /*french*/"", /*spanish*/""},
  });

  HintText Junk23 = HintText::Junk({
                     //obscure text
                     Text{"I'll make you eat those words.", /*french*/"", /*spanish*/""},
  });

  HintText Junk24 = HintText::Junk({
                     //obscure text
                     Text{"What happened to Sheik?", /*french*/"", /*spanish*/""},
  });

  HintText Junk25 = HintText::Junk({
                     //obscure text
                     Text{"L2P @.", /*french*/"", /*spanish*/""},
  });

  HintText Junk26 = HintText::Junk({
                     //obscure text
                     Text{"I've heard Sploosh Kaboom is a tricky game.", /*french*/"", /*spanish*/""},
  });

  HintText Junk27 = HintText::Junk({
                     //obscure text
                     Text{"I'm Lonk from Pennsylvania.", /*french*/"", /*spanish*/""},
  });

  HintText Junk28 = HintText::Junk({
                     //obscure text
                     Text{"I bet you'd like to have more bombs.", /*french*/"", /*spanish*/""},
  });

  HintText Junk29 = HintText::Junk({
                     //obscure text
                     Text{"When all else fails, use Fire.", /*french*/"", /*spanish*/""},
  });

  HintText Junk30 = HintText::Junk({
                     //obscure text
                     Text{"Here's a hint, @. Don't be bad.", /*french*/"", /*spanish*/""},
  });

  HintText Junk31 = HintText::Junk({
                     //obscure text
                     Text{"Game Over. Return of Ganon.", /*french*/"", /*spanish*/""},
  });

  HintText Junk32 = HintText::Junk({
                     //obscure text
                     Text{"May the way of the Hero lead to the Triforce.", /*french*/"", /*spanish*/""},
  });

  HintText Junk33 = HintText::Junk({
                     //obscure text
                     Text{"Can't find an item? Scan an Amiibo.", /*french*/"", /*spanish*/""},
  });

  HintText Junk34 = HintText::Junk({
                     //obscure text
                     Text{"They say this game has just a few glitches.", /*french*/"", /*spanish*/""},
  });

  HintText Junk35 = HintText::Junk({
                     //obscure text
                     Text{"BRRING BRRING This is Ulrira. Wrong number?", /*french*/"", /*spanish*/""},
  });

  HintText Junk36 = HintText::Junk({
                     //obscure text
                     Text{"Tingle Tingle Kooloo Limpah", /*french*/"", /*spanish*/""},
  });

  HintText Junk37 = HintText::Junk({
                     //obscure text
                     Text{"L is real 2041", /*french*/"", /*spanish*/""},
  });

  HintText Junk38 = HintText::Junk({
                     //obscure text
                     Text{"They say that Ganondorf will appear in the next Mario Tennis.", /*french*/"", /*spanish*/""},
  });

  HintText Junk39 = HintText::Junk({
                     //obscure text
                     Text{"Medigoron sells the earliest Breath of the Wild demo.", /*french*/"", /*spanish*/""},
  });

  HintText Junk40 = HintText::Junk({
                     //obscure text
                     Text{"There's a reason why I am special inquisitor!", /*french*/"", /*spanish*/""},
  });

  HintText Junk41 = HintText::Junk({
                     //obscure text
                     Text{"You were almost a @ sandwich.", /*french*/"", /*spanish*/""},
  });

  HintText Junk42 = HintText::Junk({
                     //obscure text
                     Text{"I'm a helpful hint Gossip Stone!^See, I'm helping.", /*french*/"", /*spanish*/""},
  });

  HintText Junk43 = HintText::Junk({
                     //obscure text
                     Text{"Dear @, please come to the castle. I've baked a cake for you.&Yours truly, princess Zelda.", /*french*/"", /*spanish*/""},
  });

  HintText Junk44 = HintText::Junk({
                     //obscure text
                     Text{"They say all toasters toast toast.", /*french*/"", /*spanish*/""},
  });

  HintText Junk45 = HintText::Junk({
                     //obscure text
                     Text{"They say that Okami is the best Zelda game.", /*french*/"", /*spanish*/""},
  });

  HintText Junk46 = HintText::Junk({
                     //obscure text
                     Text{"They say that quest guidance can be found at a talking rock.", /*french*/"", /*spanish*/""},
  });

  HintText Junk47 = HintText::Junk({
                     //obscure text
                     Text{"They say that the final item you're looking for can be found somewhere in Hyrule.", /*french*/"", /*spanish*/""},
  });

  HintText Junk48 = HintText::Junk({
                     //obscure text
                     Text{"Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.", /*french*/"", /*spanish*/""},
  });

  HintText Junk49 = HintText::Junk({
                     //obscure text
                     Text{"They say that Barinade fears Deku Nuts.", /*french*/"", /*spanish*/""},
  });

  HintText Junk50 = HintText::Junk({
                     //obscure text
                     Text{"They say that Flare Dancers do not fear Goron-crafted blades.", /*french*/"", /*spanish*/""},
  });

  HintText Junk51 = HintText::Junk({
                     //obscure text
                     Text{"They say that Morpha is easily trapped in a corner.", /*french*/"", /*spanish*/""},
  });

  HintText Junk52 = HintText::Junk({
                     //obscure text
                     Text{"They say that Bongo Bongo really hates the cold.", /*french*/"", /*spanish*/""},
  });

  HintText Junk53 = HintText::Junk({
                     //obscure text
                     Text{"They say that your sword is most powerful when you put it away.", /*french*/"", /*spanish*/""},
  });

  HintText Junk54 = HintText::Junk({
                     //obscure text
                     Text{"They say that bombing the hole Volvagia last flew into can be rewarding.", /*french*/"", /*spanish*/""},
  });

  HintText Junk55 = HintText::Junk({
                     //obscure text
                     Text{"They say that invisible ghosts can be exposed with Deku Nuts.", /*french*/"", /*spanish*/""},
  });

  HintText Junk56 = HintText::Junk({
                     //obscure text
                     Text{"They say that the real Phantom Ganon is bright and loud.", /*french*/"", /*spanish*/""},
  });

  HintText Junk57 = HintText::Junk({
                     //obscure text
                     Text{"They say that walking backwards is very fast.", /*french*/"", /*spanish*/""},
  });

  HintText Junk58 = HintText::Junk({
                     //obscure text
                     Text{"They say that leaping above the Market entrance enriches most children.", /*french*/"", /*spanish*/""},
  });

  HintText Junk59 = HintText::Junk({
                     //obscure text
                     Text{"They say that looking into darkness may find darkness looking back into you.", /*french*/"", /*spanish*/""},
  });

  HintText Junk60 = HintText::Junk({
                     //obscure text
                     Text{"You found a spiritual Stone! By which I mean, I worship Nayru.", /*french*/"", /*spanish*/""},
  });

  HintText Junk61 = HintText::Junk({
                     //obscure text
                     Text{"They say that the stick is mightier than the sword...^At least, it used to be...", /*french*/"", /*spanish*/""},
  });

  HintText Junk62 = HintText::Junk({
                     //obscure text
                     Text{"Open your eyes.^Open your eyes.^Wake up, @.", /*french*/"", /*spanish*/""},
  });

  HintText Junk63 = HintText::Junk({
                     //obscure text
                     Text{"They say that the Nocturne of Shadow can bring you very close to Ganon.", /*french*/"", /*spanish*/""},
  });

  HintText Junk64 = HintText::Junk({
                     //obscure text
                     Text{"They say that Twinrova always casts the same spell the first three times.", /*french*/"", /*spanish*/""},
  });

  HintText Junk65 = HintText::Junk({
                     //obscure text
                     Text{"They say that the nightly builds may be unstable.", /*french*/"", /*spanish*/""},
  });

  HintText Junk66 = HintText::Junk({
                     //obscure text
                     Text{"You're playing a Randomizer. I'm randomized!^Here's a random number:  #4#.&Enjoy your Randomizer!", /*french*/"", /*spanish*/""},
  });

  HintText Junk67 = HintText::Junk({
                     //obscure text
                     Text{"They say Ganondorf's bolts can be reflected with glass or steel.", /*french*/"", /*spanish*/""},
  });

  HintText Junk68 = HintText::Junk({
                     //obscure text
                     Text{"They say Ganon's tail is vulnerable to nuts, arrows, swords, explosives, hammers...^...sticks, seeds, boomerangs...^...rods, shovels, iron balls, angry bees...", /*french*/"", /*spanish*/""},
  });

  HintText Junk69 = HintText::Junk({
                     //obscure text
                     Text{"They say that you're wasting time reading this hint, but I disagree. Talk to me again!", /*french*/"", /*spanish*/""},
  });

  HintText Junk70 = HintText::Junk({
                     //obscure text
                     Text{"They say Ganondorf knows where to find the instrument of his doom.", /*french*/"", /*spanish*/""},
  });

  HintText Junk71 = HintText::Junk({
                     //obscure text
                     Text{"I heard @ is pretty good at Zelda.", /*french*/"", /*spanish*/""},
  });

  /*--------------------------
  |     DUNGEON HINT TEXT    |
  ---------------------------*/

  HintText DekuTree = HintText::DungeonName({
                     //obscure text
                     Text{"an ancient tree", /*french*/"", /*spanish*/""},
                   },
                     //clear text
                     Text{"Deku Tree", /*french*/"", /*spanish*/""}
  );

  HintText DodongosCavern = HintText::DungeonName({
                     //obscure text
                     Text{"an immense cavern", /*french*/"", /*spanish*/""},
                   },
                     //clear text
                     Text{ "Dodongo's Cavern", /*french*/"", /*spanish*/""}
  );

  HintText JabuJabusBelly = HintText::DungeonName({
                     //obscure text
                     Text{"the belly of a deity", /*french*/"", /*spanish*/""},
                   },
                     //clear text
                     Text{ "Jabu Jabu's Belly", /*french*/"", /*spanish*/""}
  );

  HintText ForestTemple = HintText::DungeonName({
                     //obscure text
                     Text{"a deep forest", /*french*/"", /*spanish*/""},
                   },
                     //clear text
                     Text{ "Forest Temple", /*french*/"", /*spanish*/""}
  );

  HintText FireTemple = HintText::DungeonName({
                     //obscure text
                     Text{"a high mountain", /*french*/"", /*spanish*/""},
                   },
                     //clear text
                     Text{ "Fire Temple", /*french*/"", /*spanish*/""}
  );

  HintText WaterTemple = HintText::DungeonName({
                     //obscure text
                     Text{"a vast lake", /*french*/"", /*spanish*/""},
                   },
                     //clear text
                     Text{ "Water Temple", /*french*/"", /*spanish*/""}
  );

  HintText ShadowTemple = HintText::DungeonName({
                     //obscure text
                     Text{"the house of the dead", /*french*/"", /*spanish*/""},
                   },
                     //clear text
                     Text{ "Shadow Temple", /*french*/"", /*spanish*/""}
  );

  HintText SpiritTemple = HintText::DungeonName({
                     //obscure text
                     Text{"the goddess of the sand", /*french*/"", /*spanish*/""},
                   },
                     //clear text
                     Text{ "Spirit Temple", /*french*/"", /*spanish*/""}
  );

  HintText IceCavern = HintText::DungeonName({
                     //obscure text
                     Text{"a frozen maze", /*french*/"", /*spanish*/""},
                   },
                     //clear text
                     Text{ "Ice Cavern", /*french*/"", /*spanish*/""}
  );

  HintText BottomOfTheWell = HintText::DungeonName({
                     //obscure text
                     Text{"a shadow\'s prison", /*french*/"", /*spanish*/""},
                   },
                     //clear text
                     Text{ "Bottom of the Well", /*french*/"", /*spanish*/""}
  );

  HintText GerudoTrainingGrounds = HintText::DungeonName({
                     //obscure text
                     Text{"the test of thieves", /*french*/"", /*spanish*/""},
                   },
                     //clear text
                     Text{ "Gerudo Training Grounds", /*french*/"", /*spanish*/""}
  );

  HintText GanonsCastle = HintText::DungeonName({
                     //obscure text
                     Text{"a conquered citadel", /*french*/"", /*spanish*/""},
                   },
                     //clear text
                     Text{ "Inside Ganon's Castle", /*french*/"", /*spanish*/""}
  );

  /*--------------------------
  |      BOSS HINT TEXT      |
  ---------------------------*/

  HintText QueenGohma = HintText::Boss({
                     //obscure text
                     Text{"An #ancient tree# rewards", /*french*/"", /*spanish*/""},
                   },
                     //clear text
                     Text{"the #Deku Tree# rewards", /*french*/"", /*spanish*/""}
  );

  HintText KingDodongo = HintText::Boss({
                     //obscure text
                     Text{"An #immense cavern# rewards", /*french*/"", /*spanish*/""},
                   },
                     //clear text
                     Text{"#Dodongo's Cavern# rewards", /*french*/"", /*spanish*/""}
  );

  HintText Barinade = HintText::Boss({
                     //obscure text
                     Text{"the #belly of a deity# rewards", /*french*/"", /*spanish*/""},
                   },
                     //clear text
                     Text{"#Jabu Jabu's Belly# rewards", /*french*/"", /*spanish*/""}
  );

  HintText PhantomGanon = HintText::Boss({
                     //obscure text
                     Text{"a #deep forest# rewards", /*french*/"", /*spanish*/""},
                   },
                     //clear text
                     Text{"the #Forest Temple# rewards", /*french*/"", /*spanish*/""}
  );

  HintText Volvagia = HintText::Boss({
                     //obscure text
                     Text{"a #high mountain# rewards", /*french*/"", /*spanish*/""},
                   },
                     //clear text
                     Text{"the #Fire Temple# rewards", /*french*/"", /*spanish*/""}
  );

  HintText Morpha = HintText::Boss({
                     //obscure text
                     Text{"a #vast lake# rewards", /*french*/"", /*spanish*/""},
                   },
                     //clear text
                     Text{"the #Water Temple# rewards", /*french*/"", /*spanish*/""}
  );

  HintText BongoBongo = HintText::Boss({
                     //obscure text
                     Text{"the #house of the dead# rewards", /*french*/"", /*spanish*/""},
                   },
                     //clear text
                     Text{"the #Shadow Temple# rewards", /*french*/"", /*spanish*/""}
  );

  HintText Twinrova = HintText::Boss({
                     //obscure text
                     Text{"a #goddess of the sand# rewards", /*french*/"", /*spanish*/""},
                   },
                     //clear text
                     Text{ "the #Spirit Temple# rewards", /*french*/"", /*spanish*/""}
  );

  HintText LinksPocketBoss = HintText::Boss({
                     //obscure text
                     Text{"#@'s pocket# rewards", /*french*/"", /*spanish*/""},
                   },
                     //clear text
                     Text{"#@ already has#", /*french*/"", /*spanish*/""}
  );

  /*--------------------------
  |     BRIDGE HINT TEXT     |
  ---------------------------*/

  HintText BridgeVanilla = HintText::Bridge({
                     //obscure text
                     Text{"the #Shadow and Spirit Medallions# as well as the #Light Arrows#", /*french*/"", /*spanish*/""},
  });

  HintText BridgeStones = HintText::Bridge({
                     //obscure text
                     Text{"Spiritual Stones", /*french*/"", /*spanish*/""},
  });

  HintText BridgeMedallions = HintText::Bridge({
                     //obscure text
                     Text{"Medallions", /*french*/"", /*spanish*/""},
  });

  HintText BridgeRewards = HintText::Bridge({
                     //obscure text
                     Text{"Spiritual Stones and Medallions", /*french*/"", /*spanish*/""},
  });

  HintText BridgeDungeons = HintText::Bridge({
                     //obscure text
                     Text{"Completed Dungeons", /*french*/"", /*spanish*/""},
  });

  HintText BridgeTokens = HintText::Bridge({
                     //obscure text
                     Text{"Gold Skulltula Tokens", /*french*/"", /*spanish*/""},
  });

  /*--------------------------
  | GANON BOSS KEY HINT TEXT |
  ---------------------------*/

  HintText GanonBKVanilla = HintText::GanonsBossKey({
                     //obscure text
                     Text{"kept in a big chest #inside its tower#", /*french*/"", /*spanish*/""},
  });

  HintText GanonBKOwnDungeon = HintText::GanonsBossKey({
                     //obscure text
                     Text{"hidden somewhere #inside its castle#", /*french*/"", /*spanish*/""},
  });

  HintText GanonBKOverworld = HintText::GanonsBossKey({
                     //obscure text
                     Text{"hidden #outside of dungeons# in Hyrule", /*french*/"", /*spanish*/""},
  });

  HintText GanonBKAnyDungeon = HintText::GanonsBossKey({
                     //obscure text
                     Text{"hidden #inside a dungeon# in Hyrule", /*french*/"", /*spanish*/""},
  });

  HintText GanonBKKeysanity = HintText::GanonsBossKey({
                     //obscure text
                     Text{"hidden somewhere #in Hyrule#", /*french*/"", /*spanish*/""},
  });

  HintText GanonBKTriforce = HintText::GanonsBossKey({
                     //obscure text
                     Text{"given to the Hero once the #Triforce# is completed", /*french*/"", /*spanish*/""},
  });

  /*--------------------------
  |      LACS HINT TEXT      |
  ---------------------------*/

  HintText LACSVanilla = HintText::LACS({
                     //obscure text
                     Text{"the #Shadow and Spirit Medallions#", /*french*/"", /*spanish*/""},
  });

  HintText LACSMedallions = HintText::LACS({
                     //obscure text
                     Text{"Medallions", /*french*/"", /*spanish*/""},
  });

  HintText LACSStones = HintText::LACS({
                     //obscure text
                     Text{"Spiritual Stones", /*french*/"", /*spanish*/""},
  });

  HintText LACSRewards = HintText::LACS({
                     //obscure text
                     Text{"Spiritual Stones and Medallions", /*french*/"", /*spanish*/""},
  });

  HintText LACSTokens = HintText::LACS({
                     //obscure text
                     Text{"Gold Skulltula Tokens", /*french*/"", /*spanish*/""},
  });

  /*--------------------------
  |        ALTAR TEXT        |
  ---------------------------*/

  HintText SpiritualStoneTextStart = HintText::Altar({
                     //obscure text
                     Text{"3 Spiritual Stones found in Hyrule...", /*french*/"", /*spanish*/""},
  });

  HintText ChildAltarTextEnd = HintText::Altar({
                     //obscure text
                     Text{"\x13\x07Ye who may become a Hero...&Stand with the Ocarina and&play the Song of Time.", /*french*/"", /*spanish*/""},
  });

  HintText AdultAltarTextStart = HintText::Altar({
                     //obscure text
                     Text{"When evil rules all, an awakening&voice from the Sacred Realm will&call those destined to be Sages,&who dwell in the #five temples#.", /*french*/"", /*spanish*/""},
  });

  HintText AdultAltarTextEnd = HintText::Altar({
                     //obscure text
                     Text{"Together with the Hero of Time,&the awakened ones will bind the&evil and return the light of peace&to the world...", /*french*/"", /*spanish*/""},
  });

  /*--------------------------
  |   VALIDATION LINE TEXT   |
  ---------------------------*/

  HintText ValidationLine = HintText::Validation({
                     //obscure text
                     Text{"Hmph... Since you made it this far,&I'll let you know what glorious&prize of Ganon's you likely&missed out on in my tower.^Behold...^", /*french*/"", /*spanish*/""},
  });

  /*--------------------------
  | LIGHT ARROW LOCATION TEXT|
  ---------------------------*/

  HintText LightArrowLocation = HintText::LightArrow({
                     //obscure text
                     Text{"Ha ha ha... You'll never beat me by&reflecting my lightning bolts&and unleashing the arrows from&", /*french*/"", /*spanish*/""},
  });

  /*--------------------------
  |      GANON LINE TEXT     |
  ---------------------------*/

  HintText GanonLine01 = HintText::GanonLine({
                     //obscure text
                     Text{"Oh! It's @.&I was expecting someone called&Sheik. Do you know what&happened to them?", /*french*/"", /*spanish*/""},
  });

  HintText GanonLine02 = HintText::GanonLine({
                     //obscure text
                     Text{"I knew I shouldn't have put the key&on the other side of my door.", /*french*/"", /*spanish*/""},
  });

  HintText GanonLine03 = HintText::GanonLine({
                     //obscure text
                     Text{"Looks like it's time for a&round of tennis.", /*french*/"", /*spanish*/""},
  });

  HintText GanonLine04 = HintText::GanonLine({
                     //obscure text
                     Text{"You'll never deflect my bolts of&energy with your sword,&then shoot me with those Light&Arrows you happen to have.", /*french*/"", /*spanish*/""},
  });

  HintText GanonLine05 = HintText::GanonLine({
                     //obscure text
                     Text{"Why did I leave my trident&back in the desert?", /*french*/"", /*spanish*/""},
  });

  HintText GanonLine06 = HintText::GanonLine({
                     //obscure text
                     Text{"Zelda is probably going to do&something stupid, like send you&back to your own timeline.^So this is quite meaningless.&Do you really want&to save this moron?", /*french*/"", /*spanish*/""},
  });

  HintText GanonLine07 = HintText::GanonLine({
                     //obscure text
                     Text{"What about Zelda makes you think&she'd be a better ruler than I?^I saved Lon Lon Ranch,&fed the hungry,&and my castle floats.", /*french*/"", /*spanish*/""},
  });

  HintText GanonLine08 = HintText::GanonLine({
                     //obscure text
                     Text{"I've learned this spell,&it's really neat,&I'll keep it later&for your treat!", /*french*/"", /*spanish*/""},
  });

  HintText GanonLine09 = HintText::GanonLine({
                     //obscure text
                     Text{"Many tricks are up my sleeve,&to save yourself&you'd better leave!", /*french*/"", /*spanish*/""},
  });

  HintText GanonLine10 = HintText::GanonLine({
                     //obscure text
                     Text{"After what you did to&Koholint Island, how can&you call me the bad guy?", /*french*/"", /*spanish*/""},
  });

  HintText GanonLine11 = HintText::GanonLine({
                     //obscure text
                     Text{"Today, let's begin down&'The Hero is Defeated' timeline.", /*french*/"", /*spanish*/""},
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
