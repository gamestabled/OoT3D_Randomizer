#include "hint_list.hpp"

namespace Hints {

  //Big thanks to Lioncache, Gabyelnuevo, Danius88, and Charade for their translations!

  //Text is {english, french, spanish}

  // there are special characters that are read for certain in game commands:
  // ^ is a box break
  // & is a new line
  // @ will print the player name
  // surrounding text with '#' will make it a different color
  // - OoT Randomizer

  /*--------------------------
  |       GENERAL TEXT       |
  ---------------------------*/

  HintText NoHintText   = HintText::Exclude({Text{"","",""}});
  HintText Prefix       = HintText::Exclude({Text{"They say that ",              /*french*/"", /*spanish*/"Según dicen, "}});
  HintText WayOfTheHero = HintText::Exclude({Text{" is on the way of the hero.", /*french*/"", /*spanish*/" aguarda en la senda del héroe."}});
  HintText Plundering   = HintText::Exclude({Text{"plundering ",                 /*french*/"", /*spanish*/"vagar por "}});
  HintText Foolish      = HintText::Exclude({Text{" is a foolish choice.",       /*french*/"", /*spanish*/" no es una sabia decisión."}});

  /*--------------------------
  |      ITEM HINT TEXT      |
  ---------------------------*/

  HintText TriforcePiece = HintText::Item({
                       //obscure text
                       Text{"a triumph fork",  /*french*/"", /*spanish*/"un trígono del triunfo"},
                       Text{"cheese",          /*french*/"", /*spanish*/"un queso"},
                       Text{"a gold fragment", /*french*/"", /*spanish*/"un fragmento dorado"},
                     },
                       //clear text
                       Text{"a Piece of the Triforce", /*french*/"", /*spanish*/"una Pieza de la Trifuerza"}
  );

  HintText ProgressiveMagic = HintText::Item({
                       //obscure text
                       Text{"mystic training",    /*french*/"", /*spanish*/"una maestría mística"},
                       Text{"pixie dust",         /*french*/"", /*spanish*/"un polvo de hada"},
                       Text{"a green rectangle",  /*french*/"", /*spanish*/"una verduzca vasija"},
                     },
                       //clear text
                       Text{"a Magic Meter", /*french*/"", /*spanish*/"una barra de magia"}
  );

  HintText DoubleDefense = HintText::Item({
                       //obscure text
                       Text{"a white outline",   /*french*/"", /*spanish*/"un contorno blanco"},
                       Text{"damage decrease",   /*french*/"", /*spanish*/"una reducción de daño"},
                       Text{"strengthened love", /*french*/"", /*spanish*/"un amor fortalecido"},
                     },
                       //clear text
                       Text{"Double Defense", /*french*/"", /*spanish*/"la doble defensa"}
  );

  HintText ProgressiveBulletBag = HintText::Item({
                       //obscure text
                       Text{"a seed shooter",     /*french*/"", /*spanish*/"un lanzasemillas"},
                       Text{"a rubberband",       /*french*/"", /*spanish*/"una resortera"},
                       Text{"a child's catapult", /*french*/"", /*spanish*/"una catapulta infantil"},
                     },
                       //clear text
                       Text{"a Slingshot", /*french*/"", /*spanish*/"un tirachinas"}
  );

  HintText Boomerang = HintText::Item({
                       //obscure text
                       Text{"a banana",       /*french*/"", /*spanish*/"un plátano"},
                       Text{"a stun stick",   /*french*/"", /*spanish*/"un palo aturdidor"},
                       Text{"a yellow angle", /*french*/"", /*spanish*/"un ángulo amarillo"},
                     },
                       //clear text
                       Text{"the Boomerang", /*french*/"", /*spanish*/"el bumerán"}
  );

  HintText ProgressiveBow = HintText::Item({
                       //obscure text
                       Text{"an archery enabler",     /*french*/"", /*spanish*/"un tiro al blanco"},
                       Text{"a danger dart launcher", /*french*/"", /*spanish*/"un peligroso lanzadardos"},
                     },
                       //clear text
                       Text{"a Bow", /*french*/"", /*spanish*/"un arco"}
  );

  HintText ProgressiveBombBag = HintText::Item({
                       //obscure text
                       Text{"an explosive container", /*french*/"", /*spanish*/"un recipiente explosivo"},
                       Text{"a blast bag", /*french*/"", /*spanish*/"un zurrón de estallidos"},
                     },
                       //clear text
                       Text{"a Bomb Bag", /*french*/"", /*spanish*/"un saco de bombas"}
  );

  HintText ProgressiveHookshot = HintText::Item({
                       //obscure text
                       Text{"Dampé's keepsake", /*french*/"", /*spanish*/"un recuerdo de Dampé"},
                       Text{"the Grapple Beam", /*french*/"", /*spanish*/"una liana de agarre"},
                       Text{"the BOING! chain", /*french*/"", /*spanish*/"una cadena retráctil"},
                     },
                       //clear text
                       Text{"a Hookshot", /*french*/"", /*spanish*/"un gancho"}
  );

  HintText ProgressiveStrength = HintText::Item({
                       //obscure text
                       Text{"power gloves",    /*french*/"", /*spanish*/"unos poderosos guanteletes"},
                       Text{"metal mittens",   /*french*/"", /*spanish*/"unas manoplas metálicas"},
                       Text{"the heavy lifty", /*french*/"", /*spanish*/"un levantamiento pesado"},
                     },
                       //clear text
                       Text{"a Strength Upgrade", /*french*/"", /*spanish*/"un aumento de fuerza"}
  );

  HintText ProgressiveScale = HintText::Item({
                       //obscure text
                       Text{"a deeper dive",   /*french*/"", /*spanish*/"un profundo buceo"},
                       Text{"a piece of Zora", /*french*/"", /*spanish*/"un fragmento de Zora"},
                     },
                       //clear text
                       Text{"a Zora Scale", /*french*/"", /*spanish*/"una escama Zora"}
  );

  HintText MegatonHammer = HintText::Item({
                       //obscure text
                       Text{"the dragon smasher", /*french*/"", /*spanish*/"un destructor de dragones"},
                       Text{"the metal mallet",   /*french*/"", /*spanish*/"un mazo de metal"},
                       Text{"the heavy hitter",   /*french*/"", /*spanish*/"un machacador"},
                     },
                       //clear text
                       Text{"the Megaton Hammer", /*french*/"", /*spanish*/"el martillo Megatón"}
  );

  HintText IronBoots = HintText::Item({
                       //obscure text
                       Text{"sink shoes",   /*french*/"", /*spanish*/"un calzado de las profundidades"},
                       Text{"clank cleats", /*french*/"", /*spanish*/"unas botas férreas"},
                     },
                       //clear text
                       Text{"the Iron Boots", /*french*/"", /*spanish*/"las botas de hierro"}
  );

  HintText HoverBoots = HintText::Item({
                       //obscure text
                       Text{"butter boots",    /*french*/"", /*spanish*/"unas suelas resvaladizas"},
                       Text{"sacred slippers", /*french*/"", /*spanish*/"unos escurridizos botines"},
                       Text{"spacewalkers",    /*french*/"", /*spanish*/"un calzado antigravitatorio"},
                     },
                       //clear text
                       Text{"the Hover Boots", /*french*/"", /*spanish*/"las botas voladoras"}
  );

  HintText KokiriSword = HintText::Item({
                       //obscure text
                       Text{"a butter knife",    /*french*/"", /*spanish*/"un ágil puñal"},
                       Text{"a starter slasher", /*french*/"", /*spanish*/"una hoja de principiantes"},
                       Text{"a switchblade",     /*french*/"", /*spanish*/"un raudo cortador"},
                     },
                       //clear text
                       Text{"the Kokiri Sword", /*french*/"", /*spanish*/"la Espada Kokiri"}
  );

  HintText GiantsKnife = HintText::Item({
                       //obscure text
                       Text{"a fragile blade",     /*french*/"", /*spanish*/"una frágil hoja"},
                       Text{"a breakable cleaver", /*french*/"", /*spanish*/"un rompible acero"},
                     },
                       //clear text
                       Text{"the Giant's Knife", /*french*/"", /*spanish*/"la daga gigante"}
  );

  HintText BiggoronSword = HintText::Item({
                       //obscure text
                       Text{"the biggest blade",  /*french*/"", /*spanish*/"el mayor mandoble"},
                       Text{"a colossal cleaver", /*french*/"", /*spanish*/"un estoque colosal"},
                     },
                       //clear text
                       Text{"the Biggoron Sword", /*french*/"", /*spanish*/"la Espada de Biggoron"}
  );

  HintText MasterSword = HintText::Item({
                       //obscure text
                       Text{"evil's bane",        /*french*/"", /*spanish*/"la destructora del mal"},
                       Text{"a seven year limbo", /*french*/"", /*spanish*/"unos siete años de espera"},
                     },
                       //clear text
                       Text{"the Master Sword", /*french*/"", /*spanish*/"la Espada Maestra"}
  );

  HintText DekuShield = HintText::Item({
                       //obscure text
                       Text{"a wooden ward",      /*french*/"", /*spanish*/"una protección forestal"},
                       Text{"a burnable barrier", /*french*/"", /*spanish*/"una barrera quemable"},
                     },
                       //clear text
                       Text{"a Deku Shield", /*french*/"", /*spanish*/"un escudo deku"}
  );

  HintText HylianShield = HintText::Item({
                       //obscure text
                       Text{"a steel safeguard",      /*french*/"", /*spanish*/"un protección de acero"},
                       Text{"Like Like's metal meal", /*french*/"", /*spanish*/"un metálico plato de Like Like"},
                     },
                       //clear text
                       Text{"a Hylian Shield", /*french*/"", /*spanish*/"un escudo hyliano"}
  );

  HintText MirrorShield = HintText::Item({
                       //obscure text
                       Text{"a reflective rampart", /*french*/"", /*spanish*/"una muralla reflectora"},
                       Text{"Medusa's weakness",    /*french*/"", /*spanish*/"la debilidad de Medusa"},
                       Text{"a silvered surface",   /*french*/"", /*spanish*/"una superficie plateada"},
                     },
                       //clear text
                       Text{"the Mirror Shield", /*french*/"", /*spanish*/"el escudo espejo"}
  );

  HintText FaroresWind = HintText::Item({
                       //obscure text
                       Text{"teleportation",     /*french*/"", /*spanish*/"el teletransporte"},
                       Text{"a relocation rune", /*french*/"", /*spanish*/"una runa de transporte"},
                       Text{"a green ball",      /*french*/"", /*spanish*/"una verde esfera"},
                     },
                       //clear text
                       Text{"Farore's Wind", /*french*/"", /*spanish*/"el Viento de Farore"}
  );

  HintText NayrusLove = HintText::Item({
                       //obscure text
                       Text{"a safe space",        /*french*/"", /*spanish*/"un seguro espacio"},
                       Text{"an impregnable aura", /*french*/"", /*spanish*/"una inexpugnable aura"},
                       Text{"a blue barrier",      /*french*/"", /*spanish*/"una barrera azul"},
                     },
                       //clear text
                       Text{"Nayru's Love", /*french*/"", /*spanish*/"el Amor de Nayru"}
  );

  HintText DinsFire = HintText::Item({
                       //obscure text
                       Text{"an inferno",  /*french*/"", /*spanish*/"un incendio"},
                       Text{"a heat wave", /*french*/"", /*spanish*/"una onda de calor"},
                       Text{"a red ball",  /*french*/"", /*spanish*/"una roja esfera"},
                     },
                       //clear text
                       Text{"Din's Fire", /*french*/"", /*spanish*/"el Fuego de Din"}
  );

  HintText FireArrows = HintText::Item({
                       //obscure text
                       Text{"the furnace firearm" , /*french*/"", /*spanish*/"el aguijón ardiente"},
                       Text{"the burning bolts",    /*french*/"", /*spanish*/"las puntas candentes"},
                       Text{"a magma missile",      /*french*/"", /*spanish*/"el misil abrasador"},
                     },
                       //clear text
                       Text{"the Fire Arrows", /*french*/"", /*spanish*/"las flechas de fuego"}
  );

  HintText IceArrows = HintText::Item({
                       //obscure text
                       Text{"the refrigerator rocket", /*french*/"", /*spanish*/"el misil congelado"},
                       Text{"the frostbite bolts",     /*french*/"", /*spanish*/"las puntas heladas"},
                       Text{"an iceberg maker",        /*french*/"", /*spanish*/"el control de escarcha"},
                     },
                       //clear text
                       Text{"the Ice Arrows", /*french*/"", /*spanish*/"las flechas de hielo"}
  );

  HintText LightArrows = HintText::Item({
                       //obscure text
                       Text{"the shining shot",      /*french*/"", /*spanish*/"el haz de luz"},
                       Text{"the luminous launcher", /*french*/"", /*spanish*/"el disparo luminoso"},
                       Text{"Ganondorf's bane",      /*french*/"", /*spanish*/"el destructor de Ganondorf"},
                       Text{"the lighting bolts",    /*french*/"", /*spanish*/"las puntas resplandecientes"},
                     },
                       //clear text
                       Text{"the Light Arrows", /*french*/"", /*spanish*/"las flechas de luz"}
  );

  HintText LensOfTruth = HintText::Item({
                       //obscure text
                       Text{"a lie detector",     /*french*/"", /*spanish*/"el detector de ilusiones"},
                       Text{"a ghost tracker",    /*french*/"", /*spanish*/"el rastreador paranormal"},
                       Text{"true sight",         /*french*/"", /*spanish*/"el ojo que todo ve"},
                       Text{"a detective's tool", /*french*/"", /*spanish*/"la revelación verdadera"},
                     },
                       //clear text
                       Text{"the Lens of Truth", /*french*/"", /*spanish*/"la Lupa de la Verdad"}
  );

  HintText ProgressiveOcarina = HintText::Item({
                       //obscure text
                       Text{"a flute",       /*french*/"", /*spanish*/"una flauta"},
                       Text{"a music maker", /*french*/"", /*spanish*/"un instrumento"},
                     },
                       //clear text
                       Text{"an Ocarina", /*french*/"", /*spanish*/"una ocarina"}
  );

  HintText GoronTunic = HintText::Item({
                       //obscure text
                       Text{"ruby robes",       /*french*/"", /*spanish*/"una vestimenta rubí"},
                       Text{"fireproof fabric", /*french*/"", /*spanish*/"una ignífuga prenda"},
                       Text{"cooking clothes",  /*french*/"", /*spanish*/"unos abrasantes ropajes"},
                     },
                       //clear text
                       Text{"a Goron Tunic", /*french*/"", /*spanish*/"un sayo goron"}
  );

  HintText ZoraTunic = HintText::Item({
                       //obscure text
                       Text{"a sapphire suit", /*french*/"", /*spanish*/"una vestidura zafiro"},
                       Text{"scuba gear",      /*french*/"", /*spanish*/"un traje de buceo"},
                       Text{"a swimsuit",      /*french*/"", /*spanish*/"un bañador"},
                     },
                       //clear text
                       Text{"a Zora Tunic", /*french*/"", /*spanish*/"un sayo zora"}
  );

  HintText Epona = HintText::Item({
                       //obscure text
                       Text{"a horse",              /*french*/"", /*spanish*/"una yegua"},
                       Text{"a four legged friend", /*french*/"", /*spanish*/"una amiga cuadrúpeda"},
                     },
                       //clear text
                       Text{"Epona", /*french*/"", /*spanish*/"Epona"}
  );

  HintText ZeldasLullaby = HintText::Item({
                       //obscure text
                       Text{"a song of royal slumber", /*french*/"", /*spanish*/"la canción real"},
                       Text{"a triforce tune",         /*french*/"", /*spanish*/"la melodía de la trifuerza"},
                     },
                       //clear text
                       Text{"Zelda's Lullaby", /*french*/"", /*spanish*/"la Nana de Zelda"}
  );

  HintText EponasSong = HintText::Item({
                       //obscure text
                       Text{"an equestrian etude", /*french*/"", /*spanish*/"una copla ecuestre"},
                       Text{"Malon's melody",      /*french*/"", /*spanish*/"la sonata de Malon"},
                       Text{"a ranch song",        /*french*/"", /*spanish*/"una canción rupestre"},
                     },
                       //clear text
                       Text{"Epona's Song", /*french*/"", /*spanish*/"la Canción de Epona"}
  );

  HintText SariasSong = HintText::Item({
                       //obscure text
                       Text{"a song of dancing Gorons", /*french*/"", /*spanish*/"la pegadiza tonada para Gorons"},
                       Text{"Saria's phone number",     /*french*/"", /*spanish*/"la llamada de Saria"},
                     },
                       //clear text
                       Text{"Saria's Song", /*french*/"", /*spanish*/"la Canción de Saria"}
  );

  HintText SunsSong = HintText::Item({
                       //obscure text
                       Text{"Sunny Day",         /*french*/"", /*spanish*/"un día soleado"},
                       Text{"the ReDead's bane", /*french*/"", /*spanish*/"la destructora de Redeads"},
                       Text{"the Gibdo's bane",  /*french*/"", /*spanish*/"la destructora de Gibdos"},
                     },
                       //clear text
                       Text{"the Sun's Song", /*french*/"", /*spanish*/"la Canción del Sol"}
  );

  HintText SongOfTime = HintText::Item({
                       //obscure text
                       Text{"a song 7 years long", /*french*/"", /*spanish*/"la setenada canción"},
                       Text{"the tune of ages",    /*french*/"", /*spanish*/"la melodía eónica"},
                     },
                       //clear text
                       Text{"the Song of Time", /*french*/"", /*spanish*/"la Canción del tiempo"}
  );

  HintText SongOfStorms = HintText::Item({
                       //obscure text
                       Text{"Rain Dance",            /*french*/"", /*spanish*/"la danza de la lluvia"},
                       Text{"a thunderstorm tune",   /*french*/"", /*spanish*/"una sonata tormentosa"},
                       Text{"windmill acceleration", /*french*/"", /*spanish*/"el arranque de molinos"},
                     },
                       //clear text
                       Text{"the Song of Storms", /*french*/"", /*spanish*/"la Canción de la Tormenta"}
  );

  HintText MinuetOfForest = HintText::Item({
                       //obscure text
                       Text{"the song of tall trees", /*french*/"", /*spanish*/"la canción de las copas"},
                       Text{"an arboreal anthem",     /*french*/"", /*spanish*/"el himno forestal"},
                       Text{"a green spark trail",    /*french*/"", /*spanish*/"el sendero esmeralda"},
                     },
                       //clear text
                       Text{"the Minuet of Forest", /*french*/"", /*spanish*/"el Minueto del bosque"}
  );

  HintText BoleroOfFire = HintText::Item({
                       //obscure text
                       Text{"a song of lethal lava", /*french*/"", /*spanish*/"la canción de la lava"},
                       Text{"a red spark trail",     /*french*/"", /*spanish*/"el sendero carmesí"},
                       Text{"a volcanic verse",      /*french*/"", /*spanish*/"el verso volcánico"},
                     },
                       //clear text
                       Text{"the Bolero of Fire", /*french*/"", /*spanish*/"el Bolero del fuego"}
  );

  HintText SerenadeOfWater = HintText::Item({
                       //obscure text
                       Text{"a song of a damp ditch", /*french*/"", /*spanish*/"la canción del estanque"},
                       Text{"a blue spark trail",     /*french*/"", /*spanish*/"el sendero azur"},
                       Text{"the lake's lyric",       /*french*/"", /*spanish*/"la letra del lago"},
                     },
                       //clear text
                       Text{"the Serenade of Water", /*french*/"", /*spanish*/"la Serenata del agua"}
  );

  HintText RequiemOfSpirit = HintText::Item({
                       //obscure text
                       Text{"a song of sandy statues", /*french*/"", /*spanish*/"la canción de estatuas areniscas"},
                       Text{"an orange spark trail",   /*french*/"", /*spanish*/"el sendero ámbar"},
                       Text{"the desert ditty",        /*french*/"", /*spanish*/"la estrofa del desierto"},
                     },
                       //clear text
                       Text{"the Requiem of Spirit", /*french*/"", /*spanish*/"el Réquiem del espíritu"}
  );

  HintText NocturneOfShadow = HintText::Item({
                       //obscure text
                       Text{"a song of spooky spirits", /*french*/"", /*spanish*/"la canción de los espectros"},
                       Text{"a graveyard boogie",       /*french*/"", /*spanish*/"una honra fúnebre"},
                       Text{"a haunted hymn",           /*french*/"", /*spanish*/"una estrofa encantada"},
                       Text{"a purple spark trail",     /*french*/"", /*spanish*/"el sendero malva"},
                     },
                       //clear text
                       Text{"the Nocturne of Shadow", /*french*/"", /*spanish*/"el Nocturno de la sombra"}
  );

  HintText PreludeOfLight = HintText::Item({
                       //obscure text
                       Text{"a luminous prologue melody", /*french*/"", /*spanish*/"la melodía refulgente"},
                       Text{"a yellow spark trail",       /*french*/"", /*spanish*/"el sendero áureo"},
                       Text{"the temple traveler",        /*french*/"", /*spanish*/"la ruta del templo"},
                     },
                       //clear text
                       Text{"the Prelude of Light", /*french*/"", /*spanish*/"el Preludio de la luz"}
  );

  HintText EmptyBottle = HintText::Item({
                       //obscure text
                       Text{"a glass container", /*french*/"", /*spanish*/"un recipiente de cristal"},
                       Text{"an empty jar",      /*french*/"", /*spanish*/"un frasco vacío"},
                       Text{"encased air",       /*french*/"", /*spanish*/"aire a presión"},
                     },
                       //clear text
                       Text{"a Bottle", /*french*/"", /*spanish*/"una botella"}
  );

  HintText RutosLetter = HintText::Item({
                       //obscure text
                       Text{"a call for help",      /*french*/"", /*spanish*/"una llamada de auxilio"},
                       Text{"the note that Mweeps", /*french*/"", /*spanish*/"un mensaje de ayuda"},
                       Text{"an SOS call",          /*french*/"", /*spanish*/"una nota de socorro"},
                       Text{"a fishy stationery",   /*french*/"", /*spanish*/"un escrito urgente"},
                     },
                       //clear text
                       Text{"Ruto's Letter", /*french*/"", /*spanish*/"la carta de Ruto"}
  );

  HintText BottleWithMilk = HintText::Item({
                       //obscure text
                       Text{"cow juice",          /*french*/"", /*spanish*/"un jugo de vaca"},
                       Text{"a white liquid",     /*french*/"", /*spanish*/"una bebida nutritiva"},
                       Text{"a baby's breakfast", /*french*/"", /*spanish*/"un trago para bebés"},
                     },
                       //clear text
                       Text{"a Milk Bottle", /*french*/"", /*spanish*/"una botella de leche"}
  );

  HintText BottleWithRedPotion = HintText::Item({
                       //obscure text
                       Text{"a vitality vial", /*french*/"", /*spanish*/"una pócima vitalicia"},
                       Text{"a red liquid",    /*french*/"", /*spanish*/"un remedio rojizo"},
                     },
                       //clear text
                       Text{"a Red Potion Bottle", /*french*/"", /*spanish*/"una botella de poción roja"}
  );

  HintText BottleWithGreenPotion = HintText::Item({
                       //obscure text
                       Text{"a magic mixture", /*french*/"", /*spanish*/"un potingue mágico"},
                       Text{"a green liquid",  /*french*/"", /*spanish*/"un remedio verduzco"},
                     },
                       //clear text
                       Text{"a Green Potion Bottle", /*french*/"", /*spanish*/"una botella de poción verde"}
  );

  HintText BottleWithBluePotion = HintText::Item({
                       //obscure text
                       Text{"an ailment antidote", /*french*/"", /*spanish*/"un antídoto de dolencias"},
                       Text{"a blue liquid",       /*french*/"", /*spanish*/"un remedio índigo"},
                     },
                       //clear text
                       Text{"a Blue Potion Bottle", /*french*/"", /*spanish*/"una botella de poción azul"}
  );

  HintText BottleWithFairy = HintText::Item({
                       //obscure text
                       Text{"an imprisoned fairy", /*french*/"", /*spanish*/"una hada atrapada"},
                       Text{"an extra life",       /*french*/"", /*spanish*/"una oportunidad más"},
                       Text{"Navi's cousin",       /*french*/"", /*spanish*/"la prima de Navi"},
                     },
                       //clear text
                       Text{"a Fairy Bottle", /*french*/"", /*spanish*/"un hada embotellada"}
  );

  HintText BottleWithFish = HintText::Item({
                       //obscure text
                       Text{"an aquarium",     /*french*/"", /*spanish*/"un escamado ser"},
                       Text{"a deity's snack", /*french*/"", /*spanish*/"el tentempié de cierta deidad"},
                     },
                       //clear text
                       Text{"a Fish Bottle", /*french*/"", /*spanish*/"un pez embotellado"}
  );

  HintText BottleWithBlueFire = HintText::Item({
                       //obscure text
                       Text{"a conflagration canteen", /*french*/"", /*spanish*/"un pequeño incendio"},
                       Text{"an icemelt jar",          /*french*/"", /*spanish*/"unas brasas enfrascadas"},
                     },
                       //clear text
                       Text{"a Blue Fire Bottle", /*french*/"", /*spanish*/"una botella de fuego azul"}
  );

  HintText BottleWithBugs = HintText::Item({
                       //obscure text
                       Text{"an insectarium",    /*french*/"", /*spanish*/"un insectario"},
                       Text{"Skulltula finders", /*french*/"", /*spanish*/"unos rastreadores de skulltulas"},
                     },
                       //clear text
                       Text{"a Bug Bottle", /*french*/"", /*spanish*/"una botella con insectos"}
  );

  HintText BottleWithPoe = HintText::Item({
                       //obscure text
                       Text{"a spooky ghost",    /*french*/"", /*spanish*/"una espantoso espectro"},
                       Text{"a face in the jar", /*french*/"", /*spanish*/"una cara embotellada"},
                     },
                       //clear text
                       Text{"a Poe Bottle", /*french*/"", /*spanish*/"un Poe embotellado"}
  );

  HintText BottleWithBigPoe = HintText::Item({
                       //obscure text
                       Text{"the spookiest ghost", /*french*/"", /*spanish*/"el espectro más espeluznante"},
                       Text{"a sidequest spirit",  /*french*/"", /*spanish*/"un gran espíritu"},
                     },
                       //clear text
                       Text{"a Big Poe Bottle", /*french*/"", /*spanish*/"un Gran Poe embotellado"}
  );

  HintText ShardOfAgony = HintText::Item({
                       //obscure text
                       Text{"the shake shard", /*french*/"", /*spanish*/"el fragmento tintineante"},
                       Text{"a blue alarm",    /*french*/"", /*spanish*/"una azul alarma"},
                     },
                       //clear text
                       Text{"the Shard of Agony", /*french*/"", /*spanish*/"la Piedra de la Agonía"}
  );

  HintText GerudoToken = HintText::Item({
                       //obscure text
                       Text{"a girl club membership", /*french*/"", /*spanish*/"una fémina membresía"},
                       Text{"a desert tribe's pass",  /*french*/"", /*spanish*/"el vale de la tribu del desierto"},
                     },
                       //clear text
                       Text{"the Gerudo Token", /*french*/"", /*spanish*/"el pase de socio gerudo"}
  );

  HintText ProgressiveWallet = HintText::Item({
                       //obscure text
                       Text{"a mo' money holder", /*french*/"", /*spanish*/"una cartera de dinero"},
                       Text{"a gem purse",        /*french*/"", /*spanish*/"un zurrón de gemas"},
                       Text{"a portable bank",    /*french*/"", /*spanish*/"un banco portable"},
                     },
                       //clear text
                       Text{"a Wallet", /*french*/"", /*spanish*/"una bolsa de rupias"}
  );

  HintText ProgressiveStickCapacity = HintText::Item({
                       //obscure text
                       Text{"a lumber rack",        /*french*/"", /*spanish*/"más bastones"},
                       Text{"more flammable twigs", /*french*/"", /*spanish*/"más varas"},
                     },
                       //clear text
                       Text{"Deku Stick Capacity", /*french*/"", /*spanish*/"mayor capacidad de palos deku"}
  );

  HintText ProgressiveNutCapacity = HintText::Item({
                       //obscure text
                       Text{"more nuts",         /*french*/"", /*spanish*/"más semillas de nogal"},
                       Text{"flashbang storage", /*french*/"", /*spanish*/"más frutos de aturdimiento"},
                     },
                       //clear text
                       Text{"Deku Nut Capacity", /*french*/"", /*spanish*/"mayor capacidad de nueces deku"}
  );

  HintText HeartContainer = HintText::Item({
                       //obscure text
                       Text{"a lot of love",      /*french*/"", /*spanish*/"amor por doquier"},
                       Text{"a Valentine's gift", /*french*/"", /*spanish*/"un contenedor de afección"},
                       Text{"a boss's organ",     /*french*/"", /*spanish*/"los órganos de un jefe"},
                     },
                       //clear text
                       Text{"a Heart Container", /*french*/"", /*spanish*/"un contenedor de corazón"}
  );

  HintText PieceOfHeart = HintText::Item({
                       //obscure text
                       Text{"a little love",  /*french*/"", /*spanish*/"una pizca de amor"},
                       Text{"a broken heart", /*french*/"", /*spanish*/"un corazón roto"},
                     },
                       //clear text
                       Text{"a Piece of Heart", /*french*/"", /*spanish*/"una pieza de corazón"}
  );

  HintText TreasureGameHeart = HintText::Item({
                       //obscure text
                       Text{"a victory valentine", /*french*/"", /*spanish*/"el amor victorioso"},
                     },
                       //clear text
                       Text{"a Piece of Heart", /*french*/"", /*spanish*/"una pieza de corazón"}
  );

  HintText RecoveryHeart = HintText::Item({
                       //obscure text
                       Text{"a free heal",   /*french*/"", /*spanish*/"una cura de regalo"},
                       Text{"a hearty meal", /*french*/"", /*spanish*/"una minúscula corazonada"},
                       Text{"a Band-Aid",    /*french*/"", /*spanish*/"un corazoncito sanador"},
                     },
                       //clear text
                       Text{"a Recovery Heart", /*french*/"", /*spanish*/"un corazón"}
  );

  HintText TreasureGameGreenRupee = HintText::Item({
                       //obscure text
                       Text{"the dollar of defeat", /*french*/"", /*spanish*/"la moneda de la derrota"},
                     },
                       //clear text
                       Text{"a Green Rupee", /*french*/"", /*spanish*/"una rupia verde"}
  );

  HintText DekuStick1 = HintText::Item({
                       //obscure text
                       Text{"a breakable branch", /*french*/"", /*spanish*/"un pequeño báculo"},
                     },
                       //clear text
                       Text{"a Deku Stick", /*french*/"", /*spanish*/"un palo deku"}
  );

  HintText GreenRupee = HintText::Item({
                       //obscure text
                       Text{"a unique coin", /*french*/"", /*spanish*/"una singular moneda"},
                       Text{"a penny",       /*french*/"", /*spanish*/"un penique"},
                       Text{"a green gem",   /*french*/"", /*spanish*/"una gema verde"},
                     },
                       //clear text
                       Text{"a Green Rupee", /*french*/"", /*spanish*/"una rupia verde"}
  );

  HintText BlueRupee = HintText::Item({
                       //obscure text
                       Text{"a common coin", /*french*/"", /*spanish*/"una moneda usual"},
                       Text{"a blue gem",    /*french*/"", /*spanish*/"una gema azul"},
                     },
                       //clear text
                       Text{"a Blue Rupee", /*french*/"", /*spanish*/"una rupia azul"}
  );

  HintText RedRupee = HintText::Item({
                       //obscure text
                       Text{"couch cash", /*french*/"", /*spanish*/"una buena moneda"},
                       Text{"a red gem",  /*french*/"", /*spanish*/"una gema roja"},
                     },
                       //clear text
                       Text{"a Red Rupee", /*french*/"", /*spanish*/"una rupia roja"}
  );

  HintText PurpleRupee = HintText::Item({
                       //obscure text
                       Text{"big bucks",    /*french*/"", /*spanish*/"plata de calidad"},
                       Text{"a purple gem", /*french*/"", /*spanish*/"una gema morada"},
                       Text{"wealth",       /*french*/"", /*spanish*/"unos buenos cuartos"},
                     },
                       //clear text
                       Text{"a Purple Rupee", /*french*/"", /*spanish*/"una rupia morada"}
  );

  HintText HugeRupee = HintText::Item({
                       //obscure text
                       Text{"a juicy jackpot", /*french*/"", /*spanish*/"el premio gordo"},
                       Text{"a yellow gem",    /*french*/"", /*spanish*/"una gema amarilla"},
                       Text{"a giant gem",     /*french*/"", /*spanish*/"una gema descomunal"},
                       Text{"great wealth",    /*french*/"", /*spanish*/"dinero a caudales"},
                     },
                       //clear text
                       Text{"a Huge Rupee", /*french*/"", /*spanish*/"una rupia gigante"}
  );

  HintText WeirdEgg = HintText::Item({
                       //obscure text
                       Text{"a chicken dilemma", /*french*/"", /*spanish*/"el dilema de la gallina"},
                     },
                       //clear text
                       Text{"the Weird Egg", /*french*/"", /*spanish*/"el huevo extraño"}
  );

  HintText ZeldasLetter = HintText::Item({
                       //obscure text
                       Text{"an autograph",     /*french*/"", /*spanish*/"un autógrafo"},
                       Text{"royal stationery", /*french*/"", /*spanish*/"un escrito real"},
                       Text{"royal snail mail", /*french*/"", /*spanish*/"correo de la realeza"},
                     },
                       //clear text
                       Text{"Zelda's Letter", /*french*/"", /*spanish*/"la carta de Zelda"}
  );

  HintText PocketEgg = HintText::Item({
                       //obscure text
                       Text{"a Cucco container",   /*french*/"", /*spanish*/"contenedor de cuco"},
                       Text{"a Cucco, eventually", /*french*/"", /*spanish*/"un futuro cuco"},
                       Text{"a fowl youth",        /*french*/"", /*spanish*/"una dulce juventud"},
                     },
                       //clear text
                       Text{"the Pocket Egg", /*french*/"", /*spanish*/"el huevo de bolsillo"}
  );

  HintText PocketCucco = HintText::Item({
                       //obscure text
                       Text{"a little clucker", /*french*/"", /*spanish*/"un pequeñajo pollito"},
                     },
                       //clear text
                       Text{"the Pocket Cucco", /*french*/"", /*spanish*/"el cuco de bolsillo"}
  );

  HintText Cojiro = HintText::Item({
                       //obscure text
                       Text{"a cerulean capon", /*french*/"", /*spanish*/"un cerúleo capón"},
                     },
                       //clear text
                       Text{"Cojiro", /*french*/"", /*spanish*/"Cojiro"}
  );

  HintText OddMushroom = HintText::Item({
                       //obscure text
                       Text{"a powder ingredient", /*french*/"", /*spanish*/"un oloroso ingrediente"},
                     },
                       //clear text
                       Text{"an Odd Mushroom", /*french*/"", /*spanish*/"una seta rara"}
  );

  HintText OddPoultice = HintText::Item({
                       //obscure text
                       Text{"Granny's goodies", /*french*/"", /*spanish*/"la especialidad de la abuela"},
                     },
                       //clear text
                       Text{"an Odd Potion", /*french*/"", /*spanish*/"una medicina rara"}
  );

  HintText PoachersSaw = HintText::Item({
                       //obscure text
                       Text{"a tree killer", /*french*/"", /*spanish*/"un destructor de árboles"},
                     },
                       //clear text
                       Text{"the Poacher's Saw", /*french*/"", /*spanish*/"la sierra del furtivo"}
  );

  HintText BrokenSword = HintText::Item({
                       //obscure text
                       Text{"a shattered slicer", /*french*/"", /*spanish*/"una rebanadora rota"},
                     },
                       //clear text
                       Text{"the Broken Sword", /*french*/"", /*spanish*/"la espada goron rota"}
  );

  HintText Prescription = HintText::Item({
                       //obscure text
                       Text{"a pill pamphlet", /*french*/"", /*spanish*/"un instructivo medicinal"},
                       Text{"a doctor's note", /*french*/"", /*spanish*/"unas notas del doctor"},
                     },
                       //clear text
                       Text{"the Prescription", /*french*/"", /*spanish*/"la receta"}
  );

  HintText EyeballFrog = HintText::Item({
                       //obscure text
                       Text{"a perceiving polliwog", /*french*/"", /*spanish*/"un variopinto batracio"},
                     },
                       //clear text
                       Text{"the Eyeball Frog", /*french*/"", /*spanish*/"la rana de ojos saltones"}
  );

  HintText Eyedrops = HintText::Item({
                       //obscure text
                       Text{"a vision vial", /*french*/"", /*spanish*/"un remedio para la vista"},
                     },
                       //clear text
                       Text{"the Eyedrops", /*french*/"", /*spanish*/"las supergotas oculares"}
  );

  HintText ClaimCheck = HintText::Item({
                       //obscure text
                       Text{"a three day wait", /*french*/"", /*spanish*/"unos tres días de espera"},
                     },
                       //clear text
                       Text{"the Claim Check", /*french*/"", /*spanish*/"el albarán"}
  );

  HintText Map = HintText::Item({
                       //obscure text
                       Text{"a dungeon atlas", /*french*/"", /*spanish*/"el atlas de una mazmorra"},
                       Text{"blueprints",      /*french*/"", /*spanish*/"unos planos"},
                     },
                       //clear text
                       Text{"a Map", /*french*/"", /*spanish*/"un mapa"}
  );

  HintText Compass = HintText::Item({
                       //obscure text
                       Text{"a treasure tracker", /*french*/"", /*spanish*/"un buscatesoros"},
                       Text{"a magnetic needle",  /*french*/"", /*spanish*/"una aguja magnética"},
                     },
                       //clear text
                       Text{"a Compass", /*french*/"", /*spanish*/"una brújula"}
  );

  HintText BossKey = HintText::Item({
                       //obscure text
                       Text{"a master of unlocking",   /*french*/"", /*spanish*/"la clave de un jefe"},
                       Text{"a dungeon's master pass", /*french*/"", /*spanish*/"el pase maestro de una mazmorra"},
                     },
                       //clear text
                       Text{"a Boss Key", /*french*/"", /*spanish*/"una gran llave"}
  );

  HintText GanonsBossKey = HintText::Item({
                       //obscure text
                       Text{"a master of unlocking",   /*french*/"", /*spanish*/"la clave de un jefe"},
                       Text{"a dungeon's master pass", /*french*/"", /*spanish*/"el pase maestro de una mazmorra"},
                     },
                       //clear text
                       Text{"a Boss Key", /*french*/"", /*spanish*/"una gran llave"}
  );

  HintText SmallKey = HintText::Item({
                       //obscure text
                       Text{"a tool for unlocking", /*french*/"", /*spanish*/"una clave de una entrada"},
                       Text{"a dungeon pass",       /*french*/"", /*spanish*/"un pase de una mazmorra"},
                       Text{"a lock remover",       /*french*/"", /*spanish*/"un destructor de cerraduras"},
                       Text{"a lockpick",           /*french*/"", /*spanish*/"una ganzúa"},
                     },
                       //clear text
                       Text{"a Small Key", /*french*/"", /*spanish*/"una llave pequeña"}
  );

  HintText FortressSmallKey = HintText::Item({
                       //obscure text
                       Text{"a get out of jail free card", /*french*/"", /*spanish*/"una clave de una celda"},
                     },
                       //clear text
                       Text{"a Jail Key", /*french*/"", /*spanish*/"una llave de la celda"}
  );

  HintText KokiriEmerald = HintText::Item({
                       //obscure text
                       Text{"a green stone",        /*french*/"", /*spanish*/"una piedra verdemar"},
                       Text{"a gift before death",  /*french*/"", /*spanish*/"un regalo antes de fallecer"},
                     },
                       //clear text
                       Text{"the Kokiri Emerald", /*french*/"", /*spanish*/"la Esmeralda Kokiri"}
  );

  HintText GoronRuby = HintText::Item({
                       //obscure text
                       Text{"a red stone",        /*french*/"", /*spanish*/"una piedra carmín"},
                       Text{"sworn brotherhood",  /*french*/"", /*spanish*/"el juramento de hermanos de sangre"},
                     },
                       //clear text
                       Text{"the Goron Ruby", /*french*/"", /*spanish*/"el Rubí Goron"}
  );

  HintText ZoraSapphire = HintText::Item({
                       //obscure text
                       Text{"a blue stone",        /*french*/"", /*spanish*/"una piedra celeste"},
                       Text{"an engagement gift",  /*french*/"", /*spanish*/"un regalo de compromiso"},
                     },
                       //clear text
                       Text{"the Zora Sapphire", /*french*/"", /*spanish*/"el Zafiro Zora"}
  );

  HintText ForestMedallion = HintText::Item({
                       //obscure text
                       Text{"a green coin",        /*french*/"", /*spanish*/"una moneda esmeralda"},
                       Text{"Saria's friendship",  /*french*/"", /*spanish*/"la amistad de Saria"},
                     },
                       //clear text
                       Text{"the Forest Medallion", /*french*/"", /*spanish*/"el Medallón del Bosque"}
  );

  HintText FireMedallion = HintText::Item({
                       //obscure text
                       Text{"a red coin",      /*french*/"", /*spanish*/"una moneda carmesí"},
                       Text{"Darunia's power", /*french*/"", /*spanish*/"el poder de Darunia"},
                     },
                       //clear text
                       Text{"the Fire Medallion", /*french*/"", /*spanish*/"el Medallón del Fuego"}
  );

  HintText WaterMedallion = HintText::Item({
                       //obscure text
                       Text{"a blue coin",  /*french*/"", /*spanish*/"una moneda azur"},
                       Text{"Ruto's power", /*french*/"", /*spanish*/"el poder de Ruto"},
                     },
                       //clear text
                       Text{"the Water Medallion", /*french*/"", /*spanish*/"el Medallón del Agua"}
  );

  HintText SpiritMedallion = HintText::Item({
                       //obscure text
                       Text{"an orange coin",  /*french*/"", /*spanish*/"una moneda ámbar"},
                       Text{"Nabooru's power", /*french*/"", /*spanish*/"el poder de Nabooru"},
                     },
                       //clear text
                       Text{"the Spirit Medallion", /*french*/"", /*spanish*/"el Medallón del Espíritu"}
  );

  HintText ShadowMedallion = HintText::Item({
                       //obscure text
                       Text{"a purple coin", /*french*/"", /*spanish*/"una moneda malva"},
                       Text{"Impa's power",  /*french*/"", /*spanish*/"el poder de Impa"},
                     },
                       //clear text
                       Text{"the Shadow Medallion", /*french*/"", /*spanish*/"el Medallón de la Sombra"}
  );

  HintText LightMedallion = HintText::Item({
                       //obscure text
                       Text{"a yellow coin", /*french*/"", /*spanish*/"una moneda áurea"},
                       Text{"Rauru's power", /*french*/"", /*spanish*/"el poder de Rauru"},
                     },
                       //clear text
                       Text{"the Light Medallion", /*french*/"", /*spanish*/"el Medallón de la Luz"}
  );

  // HintText HintError = HintText::Item({
  //                      //obscure text
  //                      Text{"something mysterious", /*french*/"", /*spanish*/"algo misterioso"},
  //                      Text{"an unknown treasure",  /*french*/"", /*spanish*/"un desconocido tesoro"},
  //                    },
  //                      //clear text
  //                      Text{"An Error (Please Report This)", /*french*/"", /*spanish*/"Error (Repórtelo si es posible)"}
  // );

  HintText Arrows5 = HintText::Item({
                       //obscure text
                       Text{"a few danger darts", /*french*/"", /*spanish*/"un par de peligrosos dardos"},
                       Text{"a few sharp shafts", /*french*/"", /*spanish*/"un par de puntas afiladas"},
                     },
                       //clear text
                       Text{"Arrows (5 pieces)", /*french*/"", /*spanish*/"unas (5) flechas"}
  );

  HintText Arrows10 = HintText::Item({
                       //obscure text
                       Text{"some danger darts", /*french*/"", /*spanish*/"unos cuantos peligrosos dardos"},
                       Text{"some sharp shafts", /*french*/"", /*spanish*/"unas cuantas puntas afiladas"},
                     },
                       //clear text
                       Text{"Arrows (10 pieces)", /*french*/"", /*spanish*/"unas (10) flechas"}
  );

  HintText Arrows30 = HintText::Item({
                       //obscure text
                       Text{"plenty of danger darts", /*french*/"", /*spanish*/"bastantes peligrosos dardos"},
                       Text{"plenty of sharp shafts", /*french*/"", /*spanish*/"bastantes puntas afiladas"},
                     },
                       //clear text
                       Text{"Arrows (30 pieces)", /*french*/"", /*spanish*/"unas (30) flechas"}
  );

  HintText Bombs5 = HintText::Item({
                       //obscure text
                       Text{"a few explosives",  /*french*/"", /*spanish*/"un par de explosivos"},
                       Text{"a few blast balls", /*french*/"", /*spanish*/"un par de estallidos"},
                     },
                       //clear text
                       Text{"Bombs (5 pieces)", /*french*/"", /*spanish*/"unas (5) bombas"}
  );

  HintText Bombs10 = HintText::Item({
                       //obscure text
                       Text{"some explosives",  /*french*/"", /*spanish*/"unos cuantos explosivos"},
                       Text{"some blast balls", /*french*/"", /*spanish*/"unos cuantos estallidos"},
                     },
                       //clear text
                       Text{"Bombs (10 pieces)", /*french*/"", /*spanish*/"unas (10) bombas"}
  );

  HintText Bombs20 = HintText::Item({
                       //obscure text
                       Text{"lots-o-explosives",     /*french*/"", /*spanish*/"un puñado de explosivos"},
                       Text{"plenty of blast balls", /*french*/"", /*spanish*/"bastantes estallidos"},
                     },
                       //clear text
                       Text{"Bombs (20 pieces)", /*french*/"", /*spanish*/"unas (20) bombas"}
  );

  HintText IceTrap = HintText::Item({
                       //obscure text
                       Text{"a gift from Ganon",    /*french*/"", /*spanish*/"un regalo de Ganon"},
                       Text{"a chilling discovery", /*french*/"", /*spanish*/"un escalofriante hallazgo"},
                       Text{"frosty fun",           /*french*/"", /*spanish*/"una gélida diversión"},
                     },
                       //clear text
                       Text{"an Ice Trap", /*french*/"", /*spanish*/"una trampa de hielo"}
  );

  HintText MagicBean = HintText::Item({
                       //obscure text
                       Text{"a wizardly legume", /*french*/"", /*spanish*/"una legumbre mágica"},
                     },
                       //clear text
                       Text{"a Magic Bean", /*french*/"", /*spanish*/"una judía mágica"}
  );

  HintText MagicBeanPack = HintText::Item({
                       //obscure text
                       Text{"wizardly legumes", /*french*/"", /*spanish*/"unas legumbres mágicas"},
                     },
                       //clear text
                       Text{"Magic Beans", /*french*/"", /*spanish*/"unas judías mágicas"}
  );

  HintText ProgressiveBombchus = HintText::Item({
                       //obscure text
                       Text{"mice bombs",     /*french*/"", /*spanish*/"unas bombas roedoras"},
                       Text{"proximity mice", /*french*/"", /*spanish*/"unos explosivos ratoncitos"},
                       Text{"wall crawlers",  /*french*/"", /*spanish*/"unos trepaparedes"},
                       Text{"trail blazers",  /*french*/"", /*spanish*/"unas ratas propulsadas"},
                     },
                       //clear text
                       Text{"Bombchus", /*french*/"", /*spanish*/"unos bombchus"}
  );

  HintText Bombchus5 = HintText::Item({
                       //obscure text
                       Text{"a few mice bombs",     /*french*/"", /*spanish*/"un par de bombas roedoras"},
                       Text{"a few proximity mice", /*french*/"", /*spanish*/"un par de explosivos ratoncitos"},
                       Text{"a few wall crawlers",  /*french*/"", /*spanish*/"un par de trepaparedes"},
                       Text{"a few trail blazers",  /*french*/"", /*spanish*/"un par de ratas propulsadas"},
                     },
                       //clear text
                       Text{"Bombchus (5 pieces)", /*french*/"", /*spanish*/"unos (5) bombchus"}
  );

  HintText Bombchus10 = HintText::Item({
                       //obscure text
                       Text{"some mice bombs",     /*french*/"", /*spanish*/"unas cuantas bombas roedoras"},
                       Text{"some proximity mice", /*french*/"", /*spanish*/"unos cuantos explosivos ratoncitos"},
                       Text{"some wall crawlers",  /*french*/"", /*spanish*/"unos cuantos trepaparedes"},
                       Text{"some trail blazers",  /*french*/"", /*spanish*/"unas cuantas ratas propulsadas"},
                     },
                       //clear text
                       Text{"Bombchus (10 pieces)", /*french*/"", /*spanish*/"unos (10) bombchus"}
  );

  HintText Bombchus20 = HintText::Item({
                       //obscure text
                       Text{"plenty of mice bombs",     /*french*/"", /*spanish*/"bastantes bombas roedoras"},
                       Text{"plenty of proximity mice", /*french*/"", /*spanish*/"bastantes explosivos ratoncitos"},
                       Text{"plenty of wall crawlers",  /*french*/"", /*spanish*/"bastantes trepaparedes"},
                       Text{"plenty of trail blazers",  /*french*/"", /*spanish*/"bastantes ratas propulsadas"},
                     },
                       //clear text
                       Text{"Bombchus (20 pieces)", /*french*/"", /*spanish*/"unos (20) bombchus"}
  );

  HintText DekuNuts5 = HintText::Item({
                       //obscure text
                       Text{"some nuts",       /*french*/"", /*spanish*/"un par de nueces"},
                       Text{"some flashbangs", /*french*/"", /*spanish*/"un par de semillas de aturdimiento"},
                       Text{"some scrub spit", /*french*/"", /*spanish*/"un par de escupitajos deku"},
                     },
                       //clear text
                       Text{"Deku Nuts (5 pieces)", /*french*/"", /*spanish*/"unas (5) nueces deku"}
  );

  HintText DekuNuts10 = HintText::Item({
                       //obscure text
                       Text{"lots-o-nuts",          /*french*/"", /*spanish*/"un puñado de nueces"},
                       Text{"plenty of flashbangs", /*french*/"", /*spanish*/"unas cuantas semillas de aturdimiento"},
                       Text{"plenty of scrub spit", /*french*/"", /*spanish*/"unos cuantos escupitajos deku"},
                     },
                       //clear text
                       Text{"Deku Nuts (10 pieces)", /*french*/"", /*spanish*/"unas (10) nueces deku"}
  );

  HintText DekuSeeds30 = HintText::Item({
                       //obscure text
                       Text{"catapult ammo", /*french*/"", /*spanish*/"una buena munición infantil"},
                       Text{"lots-o-seeds",  /*french*/"", /*spanish*/"un puñado de semillas"},
                     },
                       //clear text
                       Text{"Deku Seeds (30 pieces)", /*french*/"", /*spanish*/"unas (30) semillas deku"}
  );

  HintText GoldSkulltulaToken = HintText::Item({
                       //obscure text
                       Text{"proof of destruction",   /*french*/"", /*spanish*/"una prueba de la destrucción"},
                       Text{"an arachnid chip",       /*french*/"", /*spanish*/"una figura arácnida"},
                       Text{"spider remains",         /*french*/"", /*spanish*/"los restos de una araña"},
                       Text{"one percent of a curse", /*french*/"", /*spanish*/"un uno por ciento de una maldición"},
                     },
                       //clear text
                       Text{"a Gold Skulltula Token", /*french*/"", /*spanish*/"un símbolo de skulltula dorada"}
  );

  /*--------------------------
  |     ALWAYS HINT TEXT     |
  ---------------------------*/

  HintText ZR_FrogsOcarinaGame = HintText::Always({
                       //obscure text
                       Text{"an #amphibian feast# yields",               /*french*/"", /*spanish*/"una #fiesta anfibia# brinda"},
                       Text{"the #croaking choir's magnum opus# awards", /*french*/"", /*spanish*/"un #coro maestro de ancas# premia"},
                       Text{"the #froggy finale# yields",                /*french*/"", /*spanish*/"el #gran final batracio# brinda"},
                     },
                       //clear text
                       Text{"the final reward from the #Frogs of Zora's River# is", /*french*/"", /*spanish*/"la recompensa final de las #ranas del Río Zora# premia"}
  );

  HintText KF_LinksHouseCow = HintText::Always({
                       //obscure text
                       Text{"the #bovine bounty of a horseback hustle# gifts", /*french*/"", /*spanish*/"la #recompensa bovina de un paseo a caballo# brinda"},
                     },
                       //clear text
                       Text{"#Malon's obstacle course# leads to", /*french*/"", /*spanish*/"la #carrera de obstáculos de Malon# brinda"}
  );

  /*--------------------------
  |    SOMETIMES HINT TEXT   |
  ---------------------------*/

  HintText SongFromOcarinaOfTime = HintText::Sometimes({
                       //obscure text
                       Text{"the #Ocarina of Time# teaches", /*french*/"", /*spanish*/"la #Ocarina del Tiempo# enseña"},
  });

  HintText SongFromComposersGrave = HintText::Sometimes({
                       //obscure text
                       Text{"#ReDead in the Composers' Grave# guard", /*french*/"", /*spanish*/"los #ReDeads del Panteón Real# guardan"},
                       Text{"the #Composer Brothers wrote#",          /*french*/"", /*spanish*/"los #hermanos compositores escribieron#"},
  });

  HintText SheikInForest = HintText::Sometimes({
                       //obscure text
                       Text{"#in a meadow# Sheik teaches", /*french*/"", /*spanish*/"#en la pradera sagrada# Sheik enseña"},
  });

  HintText SheikAtTemple = HintText::Sometimes({
                       //obscure text
                       Text{"Sheik waits at a #monument to time# to teach", /*french*/"", /*spanish*/"Sheik espera en el #momumento del tiempo# para enseñar"},
  });

  HintText SheikInCrater = HintText::Sometimes({
                       //obscure text
                       Text{"the #crater's melody# is", /*french*/"", /*spanish*/"la #melodía del cráter# otorga"},
  });

  HintText SheikInIceCavern = HintText::Sometimes({
                       //obscure text
                       Text{"the #frozen cavern# echoes with", /*french*/"", /*spanish*/"en la #caverna de hielo# retumban los ecos de"},
  });

  HintText SheikInKakariko = HintText::Sometimes({
                       //obscure text
                       Text{"a #ravaged village# mourns with", /*french*/"", /*spanish*/"un #arrasado pueblo# llora"},
  });

  HintText SheikAtColossus = HintText::Sometimes({
                       //obscure text
                       Text{"a hero ventures #beyond the wasteland# to learn", /*french*/"", /*spanish*/"el héroe que se adentre #más allá del desierto encantado# aprenderá"},
  });


  HintText MK_10BigPoes = HintText::Sometimes({
                       //obscure text
                       Text{"#ghost hunters# will be rewarded with", /*french*/"", /*spanish*/"los #cazafantasmas# son premiados con"},
                     },
                       //clear text
                       Text{"catching #Big Poes# leads to", /*french*/"", /*spanish*/"hacerte con #Grandes Poes# conduce a"}
  );

  HintText DekuTheater_SkullMask = HintText::Sometimes({
                       //obscure text
                       Text{"the #Skull Mask# yields", /*french*/"", /*spanish*/"la #máscara de calavera# otorga"},
  });

  HintText DekuTheater_MaskOfTruth = HintText::Sometimes({
                       //obscure text
                       Text{"showing a #truthful eye to the crowd# rewards", /*french*/"", /*spanish*/"#mostrarle el ojo verdadero# a una multitud brinda"},
                     },
                       //clear text
                       Text{"the #Mask of Truth# yields", /*french*/"", /*spanish*/"la #máscara de la verdad# premia"}
  );

  HintText HF_OcarinaOfTimeItem = HintText::Sometimes({
                       //obscure text
                       Text{"the #treasure thrown by Princess Zelda# is", /*french*/"", /*spanish*/"el #tesoro arrojado por la Princesa Zelda# se trata de"},
  });

  HintText DMT_Biggoron = HintText::Sometimes({
                       //obscure text
                       Text{"#Biggoron# crafts", /*french*/"", /*spanish*/"#Biggoron# forja"},
  });

  HintText Kak_50GoldSkulltulaReward = HintText::Sometimes({
                       //obscure text
                       Text{"#50 bug badges# rewards",           /*french*/"", /*spanish*/"#50 medallas de insectos# otorgan"},
                       Text{"#50 spider souls# yields",          /*french*/"", /*spanish*/"#50 almas de araña# otorgan"},
                       Text{"#50 auriferous arachnids# lead to", /*french*/"", /*spanish*/"#50 arácnidos auríferos# otorgan"},
                     },
                       //clear text
                       Text{"slaying #50 Gold Skulltulas# reveals", /*french*/"", /*spanish*/"exterminar #50 skulltulas doradas# revela"}
  );

  HintText Kak_40GoldSkulltulaReward = HintText::Sometimes({
                       //obscure text
                       Text{"#40 bug badges# rewards",           /*french*/"", /*spanish*/"#40 medallas de insectos# otorgan"},
                       Text{"#40 spider souls# yields",          /*french*/"", /*spanish*/"#40 almas de araña# otorgan"},
                       Text{"#40 auriferous arachnids# lead to", /*french*/"", /*spanish*/"#40 arácnidos auríferos# otorgan"},
                     },
                       //clear text
                       Text{"slaying #40 Gold Skulltulas# reveals", /*french*/"", /*spanish*/"exterminar #40 skulltulas doradas# revela"}
  );

  HintText Kak_30GoldSkulltulaReward = HintText::Sometimes({
                       //obscure text
                       Text{"#30 bug badges# rewards",           /*french*/"", /*spanish*/"#30 medallas de insectos# otorgan"},
                       Text{"#30 spider souls# yields",          /*french*/"", /*spanish*/"#30 almas de araña# otorgan"},
                       Text{"#30 auriferous arachnids# lead to", /*french*/"", /*spanish*/"#30 arácnidos auríferos# otorgan"},
                     },
                       //clear text
                       Text{"slaying #30 Gold Skulltulas# reveals", /*french*/"", /*spanish*/"exterminar #30 skulltulas doradas# revela"}
  );

  HintText Kak_20GoldSkulltulaReward = HintText::Sometimes({
                       //obscure text
                       Text{"#20 bug badges# rewards",           /*french*/"", /*spanish*/"#20 medallas de insectos# otorgan"},
                       Text{"#20 spider souls# yields",          /*french*/"", /*spanish*/"#20 almas de araña# otorgan"},
                       Text{"#20 auriferous arachnids# lead to", /*french*/"", /*spanish*/"#20 arácnidos auríferos# otorgan"},
                     },
                       //clear text
                       Text{"slaying #20 Gold Skulltulas# reveals", /*french*/"", /*spanish*/"exterminar #20 skulltulas doradas# revela"}
  );

  HintText Kak_AnjuAsChild = HintText::Sometimes({
                       //obscure text
                       Text{"#wrangling roosters# rewards", /*french*/"", /*spanish*/"#pillar a las gallinas# premia"},
                       Text{"#chucking chickens# gifts",    /*french*/"", /*spanish*/"#reunir a unos emplumados# premia"},
                     },
                       //clear text
                       Text{"#collecting cuccos# rewards", /*french*/"", /*spanish*/"#hacerte con todos los cucos# premia"}
  );

  HintText GC_DaruniasJoy = HintText::Sometimes({
                       //obscure text
                       Text{"a #groovin' goron# gifts", /*french*/"", /*spanish*/"#un gerudo marchoso# otorga"},
                     },
                       //clear text
                       Text{"#Darunia's dance# leads to", /*french*/"", /*spanish*/"#el baile de Darunia# conduce a"}
  );

  HintText LW_SkullKid = HintText::Sometimes({
                       //obscure text
                       Text{"the #Skull Kid# grants", /*french*/"", /*spanish*/"#Skull Kid# otorga"},
  });

  HintText LH_Sun = HintText::Sometimes({
                       //obscure text
                       Text{"staring into #the sun# grants", /*french*/"", /*spanish*/"#mirar al sol# revela"},
                     },
                       //clear text
                       Text{"shooting #the sun# grants", /*french*/"", /*spanish*/"#disparar al sol# revela"}
  );

  HintText MK_TreasureChestGameReward = HintText::Sometimes({
                       //obscure text
                       Text{"#gambling# grants",               /*french*/"", /*spanish*/"#los juegos de azar# revelan"},
                       Text{"there is a #1/32 chance# to win", /*french*/"", /*spanish*/"hay una #probabilidad de 1/32# de ganar"},
                     },
                       //clear text
                       Text{"the #treasure chest game# grants", /*french*/"", /*spanish*/"#el Cofre del Tesoro# premia"}
  );

  HintText GF_HBA1500Points = HintText::Sometimes({
                       //obscure text
                       Text{"mastery of #horseback archery# grants", /*french*/"", /*spanish*/"amaestrar el #tiro con arco a caballo# premia"},
                     },
                       //clear text
                       Text{"scoring 1500 in #horseback archery# grants", /*french*/"", /*spanish*/"conseguir 1500 puntos en el #tiro con arco a caballo# premia"}
  );

  HintText GY_HeartPieceGraveChest = HintText::Sometimes({
                       //obscure text
                       Text{"playing #Sun's Song# in a grave spawns", /*french*/"", /*spanish*/"#tocar la Canción del Sol# en una cripta conduce a"},
  });

  HintText GC_MazeLeftChest = HintText::Sometimes({
                       //obscure text
                       Text{"in #Goron City# the hammer unlocks", /*french*/"", /*spanish*/"en la #Ciudad Goron# el martillo desbloquea"},
  });

  HintText GV_Chest = HintText::Sometimes({
                       //obscure text
                       Text{"in #Gerudo Valley# the hammer unlocks", /*french*/"", /*spanish*/"en el #Valle Gerudo# el martillo desbloquea"},
  });

  HintText GV_Cow = HintText::Sometimes({
                       //obscure text
                       Text{"a #cow in Gerudo Valley# gifts", /*french*/"", /*spanish*/"una #vaca del Valle Gerudo# brinda"},
  });

  HintText HC_GS_StormsGrotto = HintText::Sometimes({
                       //obscure text
                       Text{"a #spider behind a muddy wall# in a grotto holds", /*french*/"", /*spanish*/"una #araña tras una agrietada pared# de una cueva otorga"},
  });

  HintText HF_GS_CowGrotto = HintText::Sometimes({
                       //obscure text
                       Text{"a #spider behind webs# in a grotto holds", /*french*/"", /*spanish*/"una #araña tras una telaraña# de una cueva otorga"},
  });

  HintText HF_CowGrottoCow = HintText::Sometimes({
                       //obscure text
                       Text{"the #cobwebbed cow# gifts", /*french*/"", /*spanish*/"la #vaca tras una telaraña# brinda"},
                     },
                       //clear text
                       Text{"a #cow behind webs# in a grotto gifts", /*french*/"", /*spanish*/"una #vaca tras una telaraña# de una cueva brinda"}
  );

  HintText ZF_GS_HiddenCave = HintText::Sometimes({
                       //obscure text
                       Text{"a spider high #above the icy waters# holds", /*french*/"", /*spanish*/"una araña en lo #alto de las congeladas aguas# otorga"},
  });

  HintText HW_Chest = HintText::Sometimes({
                       //obscure text
                       Text{"#deep in the wasteland# is",         /*french*/"", /*spanish*/"en lo #profundo del desierto encantado# yace"},
                       Text{"beneath #the sands#, flames reveal", /*french*/"", /*spanish*/"tras las #arenas#, unas llamas revelan"},
  });

  HintText HW_GS = HintText::Sometimes({
                       //obscure text
                       Text{"a #spider in the wasteland# holds", /*french*/"", /*spanish*/"una #araña del desierto encantado# otorga"},
  });

  HintText GY_ComposersGraveChest = HintText::Sometimes({
                       //obscure text
                       Text{"#flames in the Composers' Grave# reveal", /*french*/"", /*spanish*/"#las llamas del Panteón Real# revelan"},
                       Text{"the #Composer Brothers hid#",             /*french*/"", /*spanish*/"los #hermanos compositores esconden#"},
  });

  HintText ZF_BottomFreestandingPoH = HintText::Sometimes({
                       //obscure text
                       Text{"#under the icy waters# lies", /*french*/"", /*spanish*/"#bajo las congeladas aguas# yace"},
  });

  HintText GC_PotFreestandingPoH = HintText::Sometimes({
                       //obscure text
                       Text{"spinning #Goron pottery# contains", /*french*/"", /*spanish*/"una #cerámica goron# contiene"},
  });

  HintText ZD_KingZoraThawed = HintText::Sometimes({
                       //obscure text
                       Text{"a #defrosted dignitary# gifts", /*french*/"", /*spanish*/"una #Alteza descongelada# brinda"},
                     },
                       //clear text
                       Text{"unfreezing #King Zora# grants", /*french*/"", /*spanish*/"#descongelar al Rey Zora# conduce a"}
  );

  HintText DMC_DekuScrub = HintText::Sometimes({
                       //obscure text
                       Text{"a single #scrub in the crater# sells", /*french*/"", /*spanish*/"un solitario #deku del cráter# vende"},
  });

  HintText DMC_GS_Crate = HintText::Sometimes({
                       //obscure text
                       Text{"a spider under a #crate in the crater# holds", /*french*/"", /*spanish*/"una araña bajo una #caja del cráter# otorga"},
  });


  HintText DekuTree_MQ_AfterSpinningLogChest = HintText::Sometimes({
                       //obscure text
                       Text{"a #temporal stone within a tree# contains", /*french*/"", /*spanish*/"un #bloque temporal de un árbol# contiene"},
                     },
                       //clear text
                       Text{"a #temporal stone within the Deku Tree# contains", /*french*/"", /*spanish*/"un #bloque temporal del Árbol Deku# contiene"}
  );

  HintText DekuTree_MQ_GS_BasementGravesRoom = HintText::Sometimes({
                       //obscure text
                       Text{"a #spider on a ceiling in a tree# holds", /*french*/"", /*spanish*/"una #araña en el techo de un árbol# otorga"},
                     },
                       //clear text
                       Text{"a #spider on a ceiling in the Deku Tree# holds", /*french*/"", /*spanish*/"una #araña en el techo del Árbol Deku# otorga"}
  );

  HintText DodongosCavern_MQ_GS_SongOfTimeBlockRoom = HintText::Sometimes({
                       //obscure text
                       Text{"a spider under #temporal stones in a cavern# holds", /*french*/"", /*spanish*/"una araña bajo #bloques temporales de una cueva# otorga"},
                     },
                       //clear text
                       Text{"a spider under #temporal stones in Dodongo's Cavern# holds", /*french*/"", /*spanish*/"una araña bajo #bloques temporales de la Cueva de los Dodongos# otorga"}
  );

  HintText JabuJabusBelly_BoomerangChest = HintText::Sometimes({
                       //obscure text
                       Text{"a school of #stingers swallowed by a deity# guard", /*french*/"", /*spanish*/"un puñado de #stingers engullidos por una deidad# guardan"},
                     },
                       //clear text
                       Text{"a school of #stingers swallowed by Jabu Jabu# guard", /*french*/"", /*spanish*/"un puñado de #stingers engullidos por Jabu Jabu# guardan"}
  );

  HintText JabuJabusBelly_MQ_GS_InvisibleEnemiesRoom = HintText::Sometimes({
                       //obscure text
                       Text{"a spider surrounded by #shadows in the belly of a deity# holds", /*french*/"", /*spanish*/"una araña rodeada de #sombras en la tripa de cierta diedad# otorga"},
                     },
                       //clear text
                       Text{"a spider surrounded by #shadows in Jabu Jabu's Belly# holds", /*french*/"", /*spanish*/"una araña rodeada de #sombras en la Tripa de Jabu Jabu# otorga"}
  );

  HintText JabuJabusBelly_MQ_Cow = HintText::Sometimes({
                       //obscure text
                       Text{"a #cow swallowed by a deity# gifts", /*french*/"", /*spanish*/"una #vaca engullida por cierta deidad# brinda"},
                     },
                       //clear text
                       Text{"a #cow swallowed by Jabu Jabu# gifts", /*french*/"", /*spanish*/"una #vaca engullida por Jabu Jabu# brinda"}
  );

  HintText FireTemple_ScarecrowChest = HintText::Sometimes({
                       //obscure text
                       Text{"a #scarecrow atop the volcano# hides", /*french*/"", /*spanish*/"un #espantapájaros en lo alto del volcán# esconde"},
                     },
                       //clear text
                       Text{"#Pierre atop the Fire Temple# hides", /*french*/"", /*spanish*/"#Pierre en lo alto del Templo del Fuego# esconde"}
  );

  HintText FireTemple_MegatonHammerChest = HintText::Sometimes({
                       //obscure text
                       Text{"the #Flare Dancer atop the volcano# guards a chest containing", /*french*/"", /*spanish*/"el #Bailafuego en lo alto del volcán# otorga"},
                     },
                       //clear text
                       Text{"the #Flare Dancer atop the Fire Temple# guards a chest containing", /*french*/"", /*spanish*/"el #Bailaguego en lo alto del Templo del Fuego# otorga"}
  );

  HintText FireTemple_MQ_ChestOnFire = HintText::Sometimes({
                       //obscure text
                       Text{"the #Flare Dancer atop the volcano# guards a chest containing", /*french*/"", /*spanish*/"el #Bailafuego en lo alto del volcán# otorga"},
                     },
                       //clear text
                       Text{"the #Flare Dancer atop the Fire Temple# guards a chest containing", /*french*/"", /*spanish*/"el #Bailafuego en lo alto del Templo del Fuego# otorga"}
  );

  HintText FireTemple_MQ_GS_SkullOnFire = HintText::Sometimes({
                       //obscure text
                       Text{"a #spider under a block in the volcano# holds", /*french*/"", /*spanish*/"una #araña bajo el bloque de un volcán# otorga"},
                     },
                       //clear text
                       Text{"a #spider under a block in the Fire Temple# holds", /*french*/"", /*spanish*/"una #araña bajo un bloque del Templo del Fuego# otorga"}
  );

  HintText WaterTemple_RiverChest = HintText::Sometimes({
                       //obscure text
                       Text{"beyond the #river under the lake# waits", /*french*/"", /*spanish*/"tras el #río bajo el lago# yace"},
                     },
                       //clear text
                       Text{"beyond the #river in the Water Temple# waits", /*french*/"", /*spanish*/"tras el #río del Templo del Agua# yace"}
  );

  HintText WaterTemple_BossKeyChest = HintText::Sometimes({
                       //obscure text
                       Text{"dodging #rolling boulders under the lake# leads to", /*french*/"", /*spanish*/"esquivar #rocas rodantes bajo el lago# conduce a"},
                     },
                       //clear text
                       Text{"dodging #rolling boulders in the Water Temple# leads to", /*french*/"", /*spanish*/"esquivar #rocas rondantes del Templo del Agua# conduce a"}
  );

  HintText WaterTemple_GS_BehindGate = HintText::Sometimes({
                       //obscure text
                       Text{"a spider behind a #gate under the lake# holds", /*french*/"", /*spanish*/"una araña tras #una valla bajo el lago# otorga"},
                     },
                       //clear text
                       Text{"a spider behind a #gate in the Water Temple# holds", /*french*/"", /*spanish*/"una araña tras #una valla del Templo del Agua# otorga"}
  );

  HintText WaterTemple_MQ_FreestandingKey = HintText::Sometimes({
                       //obscure text
                       Text{"hidden in a #box under the lake# lies", /*french*/"", /*spanish*/"en una #caja bajo el lago# yace"},
                     },
                       //clear text
                       Text{"hidden in a #box in the Water Temple# lies", /*french*/"", /*spanish*/"en una #caja del Templo del Agua# yace"}
  );

  HintText WaterTemple_MQ_GS_FreestandingKeyArea = HintText::Sometimes({
                       //obscure text
                       Text{"the #locked spider under the lake# holds", /*french*/"", /*spanish*/"la #araña enjaulada bajo el lago# otorga"},
                     },
                       //clear text
                       Text{"the #locked spider in the Water Temple# holds", /*french*/"", /*spanish*/"la #araña enjaulada del Templo del Agua# otorga"}
  );

  HintText WaterTemple_MQ_GS_TripleWallTorch = HintText::Sometimes({
                       //obscure text
                       Text{"a spider behind a #gate under the lake# holds", /*french*/"", /*spanish*/"una araña tras una #valla bajo el lago# otorga"},
                     },
                       //clear text
                       Text{"a spider behind a #gate in the Water Temple# holds", /*french*/"", /*spanish*/"una araña tras una #valla del Templo del Agua#"}
  );

  HintText GerudoTrainingGrounds_UnderwaterSilverRupeeChest = HintText::Sometimes({
                       //obscure text
                       Text{"those who seek #sunken silver rupees# will find", /*french*/"", /*spanish*/"aquellos que busquen las #rupias plateadas sumergidas# encontrarán"},
                       Text{"the #thieves' underwater training# rewards",      /*french*/"", /*spanish*/"la #instrucción submarina de las ladronas# premia"},
  });

  HintText GerudoTrainingGrounds_MQ_UnderwaterSilverRupeeChest = HintText::Sometimes({
                       //obscure text
                       Text{"those who seek #sunken silver rupees# will find", /*french*/"", /*spanish*/"aquellos que busquen las #rupias plateadas sumergidas# encontrarán"},
                       Text{"the #thieves' underwater training# rewards",      /*french*/"", /*spanish*/"la #instrucción submarina de las ladronas# premia"},
  });

  HintText GerudoTrainingGrounds_MazePathFinalChest = HintText::Sometimes({
                       //obscure text
                       Text{"the final prize of #the thieves' training# is", /*french*/"", /*spanish*/"el premio final de la #instrucción de las ladronas# brinda"},
  });

  HintText GerudoTrainingGrounds_MQ_IceArrowsChest = HintText::Sometimes({
                       //obscure text
                       Text{"the final prize of #the thieves' training# is", /*french*/"", /*spanish*/"el premio final de la #instrucción de las ladronas# brinda"},
  });

  HintText BottomOfTheWell_LensOfTruthChest = HintText::Sometimes({
                       //obscure text
                       Text{"the well's #grasping ghoul# hides",    /*french*/"", /*spanish*/"en la #profundidad del pozo# se esconde"},
                       Text{"a #nether dweller in the well# holds", /*french*/"", /*spanish*/"el #temido morador del pozo# concede"},
                     },
                       //clear text
                       Text{"#Dead Hand in the well# holds", /*french*/"", /*spanish*/"la #Mano Muerta del pozo# concede"}
  );

  HintText BottomOfTheWell_MQ_CompassChest = HintText::Sometimes({
                       //obscure text
                       Text{"the well's #grasping ghoul# hides",    /*french*/"", /*spanish*/"en la #profundidad del pozo# se esconde"},
                       Text{"a #nether dweller in the well# holds", /*french*/"", /*spanish*/"el #temido morador del pozo# concede"},
                     },
                       //clear text
                       Text{"#Dead Hand in the well# holds", /*french*/"", /*spanish*/"la #Mano Muerta del pozo# concede"}
  );

  HintText SpiritTemple_SilverGauntletsChest = HintText::Sometimes({
                       //obscure text
                       Text{"the treasure #sought by Nabooru# is", /*french*/"", /*spanish*/"el #ansiado tesoro de Nabooru# brinda"},
                     },
                       //clear text
                       Text{"upon the #Colossus's right hand# is", /*french*/"", /*spanish*/"en la #mano derecha del Coloso# yace"}
  );

  HintText SpiritTemple_MirrorShieldChest = HintText::Sometimes({
                       //obscure text
                       Text{"upon the #Colossus's left hand# is", /*french*/"", /*spanish*/"en la #mano izquierda del Coloso# yace"},
  });

  HintText SpiritTemple_MQ_ChildHammerSwitchChest = HintText::Sometimes({
                       //obscure text
                       Text{"a #temporal paradox in the Colossus# yields", /*french*/"", /*spanish*/"una #paradoja temporal del Coloso# conduce a"},
                     },
                       //clear text
                       Text{"a #temporal paradox in the Spirit Temple# yields", /*french*/"", /*spanish*/"una #paradoja temporal del Coloso# conduce a"}
  );

  HintText SpiritTemple_MQ_SymphonyRoomChest = HintText::Sometimes({
                       //obscure text
                       Text{"a #symphony in the Colossus# yields", /*french*/"", /*spanish*/"una #sinfonía del Coloso# conduce a"},
                     },
                       //clear text
                       Text{"a #symphony in the Spirit Temple# yields", /*french*/"", /*spanish*/"una #sinfonía del Coloso# conduce a"}
  );

  HintText SpiritTemple_MQ_GS_SymphonyRoom = HintText::Sometimes({
                       //obscure text
                       Text{"a #spider's symphony in the Colossus# yields", /*french*/"", /*spanish*/"la #araña de la sinfonía del Coloso# otorga"},
                     },
                       //clear text
                       Text{"a #spider's symphony in the Spirit Temple# yields", /*french*/"", /*spanish*/"la #araña de la sinfonía del Coloso# otorga"}
  );

  HintText ShadowTemple_InvisibleFloormasterChest = HintText::Sometimes({
                       //obscure text
                       Text{"shadows in an #invisible maze# guard", /*french*/"", /*spanish*/"las sombras del #laberinto misterioso# esconden"},
  });

  HintText ShadowTemple_MQ_BombFlowerChest = HintText::Sometimes({
                       //obscure text
                       Text{"shadows in an #invisible maze# guard", /*french*/"", /*spanish*/"las sombras del #laberinto invisible# esconden"},
  });

  /*--------------------------
  |    EXCLUDE HINT TEXT     |
  ---------------------------*/

  HintText KF_KokiriSwordChest = HintText::Exclude({
                       //obscure text
                       Text{"the #hidden treasure of the Kokiri# is", /*french*/"", /*spanish*/"el #tesoro oculto de los Kokiri# esconde"},
  });

  HintText KF_MidoTopLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"the #leader of the Kokiri# hides", /*french*/"", /*spanish*/"el #líder de los Kokiri# esconde"},
                     },
                       //clear text
                       Text{"#inside Mido's house# is", /*french*/"", /*spanish*/"en la #casa de Mido# yace"}
  );

  HintText KF_MidoTopRightChest = HintText::Exclude({
                       //obscure text
                       Text{"the #leader of the Kokiri# hides", /*french*/"", /*spanish*/"el #líder de los Kokiri# esconde"},
                     },
                       //clear text
                       Text{"#inside Mido's house# is", /*french*/"", /*spanish*/"en la #casa de Mido# yace"}
  );

  HintText KF_MidoBottomLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"the #leader of the Kokiri# hides", /*french*/"", /*spanish*/"el #líder de los Kokiri# esconde"},
                     },
                       //clear text
                       Text{"#inside Mido's house# is", /*french*/"", /*spanish*/"en la #casa de Mido# yace"}
  );

  HintText KF_MidoBottomRightChest = HintText::Exclude({
                       //obscure text
                       Text{"the #leader of the Kokiri# hides", /*french*/"", /*spanish*/"el #líder de los Kokiri# esconde"},
                     },
                       //clear text
                       Text{"#inside Mido's house# is", /*french*/"", /*spanish*/"en la #casa de Mido# yace"}
  );

  HintText GY_ShieldGraveChest = HintText::Exclude({
                       //obscure text
                       Text{"the #treasure of a fallen soldier# is", /*french*/"", /*spanish*/"el #tesoro de un soldado caído# esconde"},
  });

  HintText DMT_Chest = HintText::Exclude({
                       //obscure text
                       Text{"hidden behind a wall on a #mountain trail# is", /*french*/"", /*spanish*/"tras una pared del #sendero de la montaña# otorga"},
  });

  HintText GC_MazeRightChest = HintText::Exclude({
                       //obscure text
                       Text{"in #Goron City# explosives unlock", /*french*/"", /*spanish*/"en la #Ciudad Goron# unos explosivos desbloquean"},
  });

  HintText GC_MazeCenterChest = HintText::Exclude({
                       //obscure text
                       Text{"in #Goron City# explosives unlock", /*french*/"", /*spanish*/"en la #Ciudad Goron# unos explosivos desbloquean"},
  });

  HintText ZD_Chest = HintText::Exclude({
                       //obscure text
                       Text{"fire #beyond a waterfall# reveals", /*french*/"", /*spanish*/"las #llamas tras una una cascada# revelan"},
  });

  HintText GY_HookshotChest = HintText::Exclude({
                       //obscure text
                       Text{"a chest hidden by a #speedy spectre# holds", /*french*/"", /*spanish*/"un cofre custodiado por un #espectro veloz# otorga"},
                     },
                       //clear text
                       Text{"#dead Dampé's first prize# is", /*french*/"", /*spanish*/"el primer premio de #Dampé fallecido# se trata de"}
  );

  HintText GF_Chest = HintText::Exclude({
                       //obscure text
                       Text{"on a #rooftop in the desert# lies", /*french*/"", /*spanish*/"en una #azotea en el desierto# yace"},
  });

  HintText Kak_RedeadGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"#zombies beneath the earth# guard", /*french*/"", /*spanish*/"unos #zombis subterráneos# esconden"},
  });

  HintText SFM_WolfosGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"#wolves beneath the earth# guard", /*french*/"", /*spanish*/"unos #lobos subterráneos# esconden"},
  });

  HintText HF_NearMarketGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"a #hole in a field near a drawbridge# holds", /*french*/"", /*spanish*/"bajo el #hoyo de una llanura cercano a un puente# yace"},
  });

  HintText HF_SoutheastGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"a #hole amongst trees in a field# holds", /*french*/"", /*spanish*/"bajo un #hoyo de una llanura rodeado de árboles# yace"},
  });

  HintText HF_OpenGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"an #open hole in a field# holds", /*french*/"", /*spanish*/"bajo un #hoyo descubierto de una llanura# yace"},
  });

  HintText Kak_OpenGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"an #open hole in a town# holds", /*french*/"", /*spanish*/"bajo un #hoyo descubierto de un pueblo# yace"},
  });

  HintText ZR_OpenGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"a #hole along a river# holds", /*french*/"", /*spanish*/"bajo un #hoyo junto a un río# yace"},
  });

  HintText KF_StormsGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"a #hole in a forest village# holds", /*french*/"", /*spanish*/"bajo un #hoyo de una tribu forestal# yace"},
  });

  HintText LW_NearShortcutsGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"a #hole in a wooded maze# holds", /*french*/"", /*spanish*/"bajo un #hoyo de un laberinto forestal# yace"},
  });

  HintText DMT_StormsGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"#hole flooded with rain on a mountain# holds", /*french*/"", /*spanish*/"bajo un #hoyo de una montaña inundado de lluvia# yace"},
  });

  HintText DMC_UpperGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"a #hole in a volcano# holds", /*french*/"", /*spanish*/"bajo un #hoyo de un volcán# yace"},
  });


  HintText ToT_LightArrowCutscene = HintText::Exclude({
                       //obscure text
                       Text{"the #final gift of a princess# is", /*french*/"", /*spanish*/"el #obsequio final de la princesa# se trata de"},
  });

  HintText LW_GiftFromSaria = HintText::Exclude({
                       //obscure text
                       Text{"a #potato hoarder# holds",           /*french*/"", /*spanish*/"cierta #jovencita verde# concede"},
                       Text{"a rooty tooty #flutey cutey# gifts", /*french*/"", /*spanish*/"una #gran amiga# concede"},
                     },
                       //clear text
                       Text{"#Saria's Gift# is", /*french*/"", /*spanish*/"el #regalo de Saria# se trata de"}
  );

  HintText ZF_GreatFairyReward = HintText::Exclude({
                       //obscure text
                       Text{"the #fairy of winds# holds", /*french*/"", /*spanish*/"el #hada del viento# brinda"},
  });

  HintText HC_GreatFairyReward = HintText::Exclude({
                       //obscure text
                       Text{"the #fairy of fire# holds", /*french*/"", /*spanish*/"el #hada del fuego# brinda"},
  });

  HintText Colossus_GreatFairyReward = HintText::Exclude({
                       //obscure text
                       Text{"the #fairy of love# holds", /*french*/"", /*spanish*/"el #hada del amor# brinda"},
  });

  HintText DMT_GreatFairyReward = HintText::Exclude({
                       //obscure text
                       Text{"a #magical fairy# gifts", /*french*/"", /*spanish*/"una #hada mágica# brinda"},
  });

  HintText DMC_GreatFairyReward = HintText::Exclude({
                       //obscure text
                       Text{"a #magical fairy# gifts", /*french*/"", /*spanish*/"una #hada máfica# brinda"},
  });

  HintText OGC_GreatFairyReward = HintText::Exclude({
                       //obscure text
                       Text{"the #fairy of strength# holds", /*french*/"", /*spanish*/"el #hada de la fuerza# brinda"},
  });


  HintText SongFromImpa = HintText::Exclude({
                       //obscure text
                       Text{"#deep in a castle#, Impa teaches", /*french*/"", /*spanish*/"al #fondo del castillo, Impa enseña#"},
  });

  HintText SongFromMalon = HintText::Exclude({
                       //obscure text
                       Text{"#a farm girl# sings", /*french*/"", /*spanish*/"una #chica rupestre# canta"},
  });

  HintText SongFromSaria = HintText::Exclude({
                       //obscure text
                       Text{"#deep in the forest#, Saria teaches", /*french*/"", /*spanish*/"al #fondo del bosque#, Saria enseña"},
  });

  HintText SongFromWindmill = HintText::Exclude({
                       //obscure text
                       Text{"a man #in a windmill# is obsessed with", /*french*/"", /*spanish*/"el #hombre del molino# está obsesionado con"},
  });


  HintText HC_MalonEgg = HintText::Exclude({
                       //obscure text
                       Text{"a #girl looking for her father# gives", /*french*/"", /*spanish*/"una #chica en busca de su padre# otorga"},
  });

  HintText HC_ZeldasLetter = HintText::Exclude({
                       //obscure text
                       Text{"a #princess in a castle# gifts", /*french*/"", /*spanish*/"la #princesa de un castillo# otorga"},
  });

  HintText ZD_DivingMinigame = HintText::Exclude({
                       //obscure text
                       Text{"an #unsustainable business model# gifts", /*french*/"", /*spanish*/"un #mal modelo de negocio# premia con"},
                     },
                       //clear text
                       Text{"those who #dive for Zora rupees# will find", /*french*/"", /*spanish*/"aquellos que se #sumergan por las rupias Zora# encontrarán"}
  );

  HintText LH_ChildFishing = HintText::Exclude({
                       //obscure text
                       Text{"#fishing in youth# bestows", /*french*/"", /*spanish*/"#pescar en la juventud# conduce a"},
  });

  HintText LH_AdultFishing = HintText::Exclude({
                       //obscure text
                       Text{"#fishing in maturity# bestows", /*french*/"", /*spanish*/"#pescar en la madurez# conduce a"},
  });

  HintText LH_LabDive = HintText::Exclude({
                       //obscure text
                       Text{"a #diving experiment# is rewarded with", /*french*/"", /*spanish*/"#bucear para un experimento# se premia con"},
  });

  HintText GC_RollingGoronAsAdult = HintText::Exclude({
                       //obscure text
                       Text{"#comforting yourself# provides", /*french*/"", /*spanish*/"#confrontarte a ti mismo# otorga"},
                     },
                       //clear text
                       Text{"#reassuring a young Goron# is rewarded with", /*french*/"", /*spanish*/"#calmar a un joven Goron# otorga"}
  );

  HintText MK_BombchuBowlingFirstPrize = HintText::Exclude({
                       //obscure text
                       Text{"the #first explosive prize# is", /*french*/"", /*spanish*/"el #primer premio explosivo# se trata de"},
  });

  HintText MK_BombchuBowlingSecondPrize = HintText::Exclude({
                       //obscure text
                       Text{"the #second explosive prize# is", /*french*/"", /*spanish*/"el #segundo premio explosivo# se trata de"},
  });

  HintText MK_LostDog = HintText::Exclude({
                       //obscure text
                       Text{"#puppy lovers# will find", /*french*/"", /*spanish*/"los #amantes caninos# encontrarán"},
                     },
                       //clear text
                       Text{"#rescuing Richard the Dog# is rewarded with", /*french*/"", /*spanish*/"#rescatar al perro Ricardo# conduce a"}
  );

  HintText LW_OcarinaMemoryGame = HintText::Exclude({
                       //obscure text
                       Text{"the prize for a #game of Simon Says# is", /*french*/"", /*spanish*/"#repetir ciertas melodías# otorga"},
                       Text{"a #child sing-a-long# holds",             /*french*/"", /*spanish*/"#tocar junto a otros# otorga"},
                     },
                       //clear text
                       Text{"#playing an Ocarina in Lost Woods# is rewarded with", /*french*/"", /*spanish*/"#tocar la ocarina en el Bosque Perdido# otorga"}
  );

  HintText Kak_10GoldSkulltulaReward = HintText::Exclude({
                       //obscure text
                       Text{"#10 bug badges# rewards",           /*french*/"", /*spanish*/"#10 medallas de insectos# otorgan"},
                       Text{"#10 spider souls# yields",          /*french*/"", /*spanish*/"#10 almas de araña# otorgan"},
                       Text{"#10 auriferous arachnids# lead to", /*french*/"", /*spanish*/"#10 arácnidos auríferos# otorgan"},
                     },
                       //clear text
                       Text{"slaying #10 Gold Skulltulas# reveals", /*french*/"", /*spanish*/"#exterminar 10 skulltulas doradas# revela"}
  );

  HintText Kak_ManOnRoof = HintText::Exclude({
                       //obscure text
                       Text{"a #rooftop wanderer# holds", /*french*/"", /*spanish*/"#alguien sobre un tejado# otorga"},
  });

  HintText ZR_MagicBeanSalesman = HintText::Exclude({
                       //obscure text
                       Text{"a seller of #colorful crops# has", /*french*/"", /*spanish*/"el vendedor de un #colorido cultivo# ofrece"},
                     },
                       //clear text
                       Text{"a #bean seller# offers", /*french*/"", /*spanish*/"el #vendedor de judías# ofrece"}
  );

  HintText ZR_FrogsInTheRain = HintText::Exclude({
                       //obscure text
                       Text{"#frogs in a storm# gift", /*french*/"", /*spanish*/"las #ancas bajo la tormenta# otorgan"},
  });

  HintText GF_HBA1000Points = HintText::Exclude({
                       //obscure text
                       Text{"scoring 1000 in #horseback archery# grants", /*french*/"", /*spanish*/"conseguir 1000 puntos en el #tiro con arco a caballo# premia"},
  });

  HintText MK_ShootingGalleryReward = HintText::Exclude({
                       //obscure text
                       Text{"#shooting in youth# grants", /*french*/"", /*spanish*/"#disparar en la juventud# otorga"},
  });

  HintText Kak_ShootingGalleryReward = HintText::Exclude({
                       //obscure text
                       Text{"#shooting in maturity# grants", /*french*/"", /*spanish*/"#disparar en la madurez# otorga"},
  });

  HintText LW_TargetInWoods = HintText::Exclude({
                       //obscure text
                       Text{"shooting a #target in the woods# grants", /*french*/"", /*spanish*/"disparar a un #blanco forestal# brinda"},
  });

  HintText Kak_AnjuAsAdult = HintText::Exclude({
                       //obscure text
                       Text{"a #chicken caretaker# offers adults", /*french*/"", /*spanish*/"una #cuidadora de emplumados# le ofrece a los mayores"},
  });

  HintText LLR_TalonsChickens = HintText::Exclude({
                       //obscure text
                       Text{"#finding Super Cuccos# is rewarded with", /*french*/"", /*spanish*/"#hallar los supercucos# conduce a"},
  });

  HintText GC_RollingGoronAsChild = HintText::Exclude({
                       //obscure text
                       Text{"the prize offered by a #large rolling Goron# is", /*french*/"", /*spanish*/"un #gran Goron rodante# otorga"},
  });

  HintText LH_UnderwaterItem = HintText::Exclude({
                       //obscure text
                       Text{"the #sunken treasure in a lake# is", /*french*/"", /*spanish*/"el #tesoro hundido del lago# se trata de"},
  });

  HintText GF_GerudoToken = HintText::Exclude({
                       //obscure text
                       Text{"#rescuing captured carpenters# is rewarded with", /*french*/"", /*spanish*/"#rescatar los apresados carpinteros# se premia con"},
  });

  HintText Wastelan_BombchuSalesman = HintText::Exclude({
                       //obscure text
                       Text{"a #carpet guru# sells", /*french*/"", /*spanish*/"el #genio de una alfombra# vende"},
  });


  HintText Kak_ImpasHouseFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"#imprisoned in a house# lies", /*french*/"", /*spanish*/"#en una casa entre rejas# yace"},
  });

  HintText HF_TektiteGrottoFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"#deep underwater in a hole# is", /*french*/"", /*spanish*/"#en lo hondo bajo un hoyo# yace"},
  });

  HintText Kak_WindmillFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"on a #windmill ledge# lies", /*french*/"", /*spanish*/"al #borde de un molino# yace"},
  });

  HintText GY_DampeRaceFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"#racing a ghost# leads to", /*french*/"", /*spanish*/"#perseguir a un fantasma# conduce a"},
                     },
                       //clear text
                       Text{"#dead Dampé's second# prize is", /*french*/"", /*spanish*/"el segundo premio de #Dampé fallecido# se trata de"}
  );

  HintText LLR_FreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"in a #ranch silo# lies", /*french*/"", /*spanish*/"en un #granero rupestre# yace"},
  });

  HintText GY_FreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"a #crate in a graveyard# hides", /*french*/"", /*spanish*/"bajo la #caja de un cementerio# yace"},
  });

  HintText GY_DampeGravediggingTour = HintText::Exclude({
                       //obscure text
                       Text{"a #gravekeeper digs up#", /*french*/"", /*spanish*/"cierto #sepultero desentierra#"},
  });

  HintText ZR_NearOpenGrottoFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"on top of a #pillar in a river# lies", /*french*/"", /*spanish*/"en lo alto del #pilar de un río# yace"},
  });

  HintText ZR_NearDomainFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"on a #river ledge by a waterfall# lies", /*french*/"", /*spanish*/"al borde #del río con una cascada# yace"},
  });

  HintText LH_FreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"high on a #lab rooftop# one can find", /*french*/"", /*spanish*/"en lo #alto de un laboratorio# yace"},
  });

  HintText ZF_IcebergFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"#floating on ice# is", /*french*/"", /*spanish*/"#flotando sobre hielo# yace"},
  });

  HintText GV_WaterfallFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"behind a #desert waterfall# is", /*french*/"", /*spanish*/"tras una #desierta cascada# yace"},
  });

  HintText GV_CrateFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"a #crate in a valley# hides", /*french*/"", /*spanish*/"bajo la #caja de un valle# yace"},
  });

  HintText Colossus_FreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"on top of an #arch of stone# lies", /*french*/"", /*spanish*/"en lo alto de un #arco de piedra# yace"},
  });

  HintText DMT_FreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"above a #mountain cavern entrance# is", /*french*/"", /*spanish*/"en lo alto de la #entrada de una cueva en la montaña# yace"},
  });

  HintText DMC_WallFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"nestled in a #volcanic wall# is", /*french*/"", /*spanish*/"entre unas #murallas volcánicas# yace"},
  });

  HintText DMC_VolcanoFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"obscured by #volcanic ash# is", /*french*/"", /*spanish*/"bajo la #ceniza volcánica# yace"},
  });

  HintText GF_NorthF1Carpenter = HintText::Exclude({
                       //obscure text
                       Text{"#defeating Gerudo guards# reveals", /*french*/"", /*spanish*/"#derrotar a las guardas Gerudo# revela"},
  });

  HintText GF_NorthF2Carpenter = HintText::Exclude({
                       //obscure text
                       Text{"#defeating Gerudo guards# reveals", /*french*/"", /*spanish*/"#derrotar a las guardas Gerudo# revela"},
  });

  HintText GF_SouthF1Carpenter = HintText::Exclude({
                       //obscure text
                       Text{"#defeating Gerudo guards# reveals", /*french*/"", /*spanish*/"#derrotar a las guardas Gerudo# revela"},
  });

  HintText GF_SouthF2Carpenter = HintText::Exclude({
                       //obscure text
                       Text{"#defeating Gerudo guards# reveals", /*french*/"", /*spanish*/"#derrotar a las guardas Gerudo# revela"},
  });


  HintText DekuTree_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"in the #center of the Deku Tree# lies", /*french*/"", /*spanish*/"al #centro del Árbol Deku# yace"},
  });

  HintText DekuTree_SlingshotChest = HintText::Exclude({
                       //obscure text
                       Text{"the #treasure guarded by a scrub# in the Deku Tree is", /*french*/"", /*spanish*/"un #deku del Árbol Deku# esconde"},
  });

  HintText DekuTree_SlingshotRoomSideChest = HintText::Exclude({
                       //obscure text
                       Text{"the #treasure guarded by a scrub# in the Deku Tree is", /*french*/"", /*spanish*/"un #deku del Árbol Deku# esconde"},
  });

  HintText DekuTree_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#pillars of wood# in the Deku Tree lead to", /*french*/"", /*spanish*/"los #salientes del Árbol Deku# conducen a"},
  });

  HintText DekuTree_CompassRoomSideChest = HintText::Exclude({
                       //obscure text
                       Text{"#pillars of wood# in the Deku Tree lead to", /*french*/"", /*spanish*/"los #salientes del Árbol Deku# conducen a"},
  });

  HintText DekuTree_BasementChest = HintText::Exclude({
                       //obscure text
                       Text{"#webs in the Deku Tree# hide", /*french*/"", /*spanish*/"entre #telarañas del Árbol Deku# yace"},
  });


  HintText DekuTree_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"in the #center of the Deku Tree# lies", /*french*/"", /*spanish*/"al #centro del Árbol Deku# yace"},
  });

  HintText DekuTree_MQ_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"a #treasure guarded by a large spider# in the Deku Tree is", /*french*/"", /*spanish*/"una #araña del Árbol Deku# esconde"},
  });

  HintText DekuTree_MQ_SlingshotChest = HintText::Exclude({
                       //obscure text
                       Text{"#pillars of wood# in the Deku Tree lead to", /*french*/"", /*spanish*/"los #salientes del Árbol Deku# conducen a"},
  });

  HintText DekuTree_MQ_SlingshotRoomBackChest = HintText::Exclude({
                       //obscure text
                       Text{"#pillars of wood# in the Deku Tree lead to", /*french*/"", /*spanish*/"los #salientes del Árbol Deku# conducen a"},
  });

  HintText DekuTree_MQ_BasementChest = HintText::Exclude({
                       //obscure text
                       Text{"#webs in the Deku Tree# hide", /*french*/"", /*spanish*/"entre #telarañas del Árbol Deku# yace"},
  });

  HintText DekuTree_MQ_BeforeSpinningLogChest = HintText::Exclude({
                       //obscure text
                       Text{"#magical fire in the Deku Tree# leads to", /*french*/"", /*spanish*/"el #fuego mágico en el Árbol Deku# conduce a"},
  });


  HintText DodongosCavern_BossRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"#above King Dodongo# lies", /*french*/"", /*spanish*/"#sobre el Rey Dodongo# yace"},
  });


  HintText DodongosCavern_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"a #muddy wall in Dodongo's Cavern# hides", /*french*/"", /*spanish*/"tras una #agrietada pared en la Caverna de los Dodongos# yace"},
  });

  HintText DodongosCavern_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"a #statue in Dodongo's Cavern# guards", /*french*/"", /*spanish*/"una #estatua de la Caverna de los Dodongos# esconde"},
  });

  HintText DodongosCavern_BombFlowerPlatformChest = HintText::Exclude({
                       //obscure text
                       Text{"above a #maze of stone# in Dodongo's Cavern lies", /*french*/"", /*spanish*/"entre un #laberinto de piedra# en la Cueva de los Dodongos# yace"},
  });

  HintText DodongosCavern_BombBagChest = HintText::Exclude({
                       //obscure text
                       Text{"the #second lizard cavern battle# yields", /*french*/"", /*spanish*/"#luchar dos veces contra reptiles en una cueva# conduce a"},
  });

  HintText DodongosCavern_EndOfBridgeChest = HintText::Exclude({
                       //obscure text
                       Text{"a #chest at the end of a bridge# yields", /*french*/"", /*spanish*/"un #cofre al final de un quebrado puente# otorga"},
  });


  HintText DodongosCavern_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"a #muddy wall in Dodongo's Cavern# hides", /*french*/"", /*spanish*/"una #quebrada pared en la Cueva de los Dodongos# esconde"},
  });

  HintText DodongosCavern_MQ_BombBagChest = HintText::Exclude({
                       //obscure text
                       Text{"an #elevated alcove# in Dodongo's Cavern holds", /*french*/"", /*spanish*/"una #elevada alcoba# en la Caverna de los Dongos# brinda"},
  });

  HintText DodongosCavern_MQ_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#fire-breathing lizards# in Dodongo's Cavern guard", /*french*/"", /*spanish*/"unos #lagartos de fuego# en la Cueva de los Dodongos# esconden"},
  });

  HintText DodongosCavern_MQ_LarvaeRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"#baby spiders# in Dodongo's Cavern guard", /*french*/"", /*spanish*/"unas #pequeñas larvas# en la Cueva de los Dodongos esconden"},
  });

  HintText DodongosCavern_MQ_TorchPuzzleRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"above a #maze of stone# in Dodongo's Cavern lies", /*french*/"", /*spanish*/"sobre un #laberinto de piedra# en la Cueva de los Dodongos yace"},
  });

  HintText DodongosCavern_MQ_UnderGraveChest = HintText::Exclude({
                       //obscure text
                       Text{"#beneath a headstone# in Dodongo's Cavern lies", /*french*/"", /*spanish*/"#bajo una lápida# en la Cueva de los Dodongos yace"},
  });


  HintText JabuJabusBelly_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"#tentacle trouble# in a deity's belly guards", /*french*/"", /*spanish*/"un #problema tentaculoso# en la tripa de cierta deidad esconde"},
                     },
                       //clear text
                       Text{"a #slimy thing# guards", /*french*/"", /*spanish*/"un #tentáculo parasitario# protege"}
  );

  HintText JabuJabusBelly_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#bubble trouble# in a deity's belly guards", /*french*/"", /*spanish*/"un #problema burbujesco# en la tripa de cierta deidad esconde"},
                     },
                       //clear text
                       Text{"#bubbles# guard", /*french*/"", /*spanish*/"unas #burbujas# protegen"}
  );


  HintText JabuJabusBelly_MQ_FirstRoomSideChest = HintText::Exclude({
                       //obscure text
                       Text{"shooting a #mouth cow# reveals", /*french*/"", /*spanish*/"#dispararle a una vaca# revela"},
  });

  HintText JabuJabusBelly_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"#pop rocks# hide",            /*french*/"", /*spanish*/"#cepillarse los dientes con explosivos# revela"},
                       Text{"an #explosive palate# holds", /*french*/"", /*spanish*/"un #paladar explosivo# esconde"},
                     },
                       //clear text
                       Text{"a #boulder before cows# hides", /*french*/"", /*spanish*/"cierta #roca con unas vacas# esconde"}
  );

  HintText JabuJabusBelly_MQ_SecondRoomLowerChest = HintText::Exclude({
                       //obscure text
                       Text{"near a #spiked elevator# lies", /*french*/"", /*spanish*/"cerca de un #ascensor puntiagudo# yace"},
  });

  HintText JabuJabusBelly_MQ_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"a #drowning cow# unveils", /*french*/"", /*spanish*/"una #vaca sumergida# revela"},
  });

  HintText JabuJabusBelly_MQ_SecondRoomUpperChest = HintText::Exclude({
                       //obscure text
                       Text{"#moving anatomy# creates a path to", /*french*/"", /*spanish*/"un #ser movedizo entre paredes# conduce a"},
  });

  HintText JabuJabusBelly_MQ_BasementNearSwitchesChest = HintText::Exclude({
                       //obscure text
                       Text{"a #pair of digested cows# hold", /*french*/"", /*spanish*/"un #par de digeridas vacas# otorgan"},
  });

  HintText JabuJabusBelly_MQ_BasementNearVinesChest = HintText::Exclude({
                       //obscure text
                       Text{"a #pair of digested cows# hold", /*french*/"", /*spanish*/"un #par de digeridas vacas# otorgan"},
  });

  HintText JabuJabusBelly_MQ_NearBossChest = HintText::Exclude({
                       //obscure text
                       Text{"the #final cows' reward# in a deity's belly is", /*french*/"", /*spanish*/"las #vacas al final# de la tripa de cierta deidad otorgan"},
  });

  HintText JabuJabusBelly_MQ_FallingLikeLikeRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"#cows protected by falling monsters# in a deity's belly guard", /*french*/"", /*spanish*/"unas #vacas custodiadas por monstruos del techo# de la tripa de cierta deidad otorgan"},
  });

  HintText JabuJabusBelly_MQ_BoomerangRoomSmallChest = HintText::Exclude({
                       //obscure text
                       Text{"a school of #stingers swallowed by a deity# guard", /*french*/"", /*spanish*/"un puñado de #stingers engullidos por cierta deidad# guardan"},
                     },
                       //clear text
                       Text{"a school of #stingers swallowed by Jabu Jabu# guard", /*french*/"", /*spanish*/"un puñado de #stingers engullidos por Jabu Jabu# guardan"}
  );

  HintText JabuJabusBelly_MQ_BoomerangChest = HintText::Exclude({
                       //obscure text
                       Text{"a school of #stingers swallowed by a deity# guard", /*french*/"", /*spanish*/"un puñado de #stingers engullidos por cierta deidad# guardan"},
                     },
                       //clear text
                       Text{"a school of #stingers swallowed by Jabu Jabu# guard", /*french*/"", /*spanish*/"un puñado de #stingers engullidos por Jabu Jabu# guardan"}
  );


  HintText ForestTemple_FirstRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"a #tree in the Forest Temple# supports", /*french*/"", /*spanish*/"sobre un #árbol del Templo del Bosque# yace"},
  });

  HintText ForestTemple_FirstStalfosChest = HintText::Exclude({
                       //obscure text
                       Text{"#defeating enemies beneath a falling ceiling# in Forest Temple yields", /*french*/"", /*spanish*/"#derrotar enemigos caídos de lo alto# del Templo del Bosque revela"},
  });

  HintText ForestTemple_WellChest = HintText::Exclude({
                       //obscure text
                       Text{"a #sunken chest deep in the woods# contains", /*french*/"", /*spanish*/"un #sumergido cofre en lo profundo del bosque# contiene"},
  });

  HintText ForestTemple_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"a #fiery skull# in Forest Temple guards", /*french*/"", /*spanish*/"una #ardiente calavera# del Templo del Bosque esconde"},
  });

  HintText ForestTemple_RaisedIslandCourtyardChest = HintText::Exclude({
                       //obscure text
                       Text{"a #chest on a small island# in the Forest Temple holds", /*french*/"", /*spanish*/"un #cofre sobre una isla# del Templo del Bosque contiene"},
  });

  HintText ForestTemple_FallingCeilingRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"beneath a #checkerboard falling ceiling# lies", /*french*/"", /*spanish*/"tras un #techo de ajedrez# yace"},
  });

  HintText ForestTemple_EyeSwitchChest = HintText::Exclude({
                       //obscure text
                       Text{"a #sharp eye# will spot", /*french*/"", /*spanish*/"un #afilado ojo# revela"},
                     },
                       //clear text
                       Text{"#blocks of stone# in the Forest Temple surround", /*french*/"", /*spanish*/"cerca de unos #bloques de piedra# del Templo del Bosque yace"}
  );

  HintText ForestTemple_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"a #turned trunk# contains", /*french*/"", /*spanish*/"en una #sala con otro punto de vista# se esconde"},
  });

  HintText ForestTemple_FloormasterChest = HintText::Exclude({
                       //obscure text
                       Text{"deep in the forest #shadows guard a chest# containing", /*french*/"", /*spanish*/"en lo profundo del bosque #unas sombras# esconden"},
  });

  HintText ForestTemple_BowChest = HintText::Exclude({
                       //obscure text
                       Text{"an #army of the dead# guards", /*french*/"", /*spanish*/"un #ejército de soldados caídos# guardan"},
                     },
                       //clear text
                       Text{"#Stalfos deep in the Forest Temple# guard", /*french*/"", /*spanish*/"los #Stalfos en lo profundo del Templo del Bosque# guardan"}
  );

  HintText ForestTemple_RedPoeChest = HintText::Exclude({
                       //obscure text
                       Text{"#Joelle# guards", /*french*/"", /*spanish*/"#Joelle# guarda"},
                     },
                       //clear text
                       Text{"a #red ghost# guards", /*french*/"", /*spanish*/"un #espectro rojo# guarda"}
  );

  HintText ForestTemple_BluePoeChest = HintText::Exclude({
                       //obscure text
                       Text{"#Beth# guards", /*french*/"", /*spanish*/"#Beth# guarda"},
                     },
                       //clear text
                       Text{"a #blue ghost# guards", /*french*/"", /*spanish*/"un #espectro azul# guarda"}
  );

  HintText ForestTemple_BasementChest = HintText::Exclude({
                       //obscure text
                       Text{"#revolving walls# in the Forest Temple conceal", /*french*/"", /*spanish*/"las #paredes giratorias# del Templo del Bosque conceden"},
  });


  HintText ForestTemple_MQ_FirstRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"a #tree in the Forest Temple# supports", /*french*/"", /*spanish*/"sobre un #árbol del Templo del Bosque# yace"},
  });

  HintText ForestTemple_MQ_WolfosChest = HintText::Exclude({
                       //obscure text
                       Text{"#defeating enemies beneath a falling ceiling# in Forest Temple yields", /*french*/"", /*spanish*/"#derrotar enemigos caídos de lo alto# del Templo del Bosque revela"},
  });

  HintText ForestTemple_MQ_BowChest = HintText::Exclude({
                       //obscure text
                       Text{"an #army of the dead# guards", /*french*/"", /*spanish*/"un #ejército de soldados caídos# guardan"},
                     },
                       //clear text
                       Text{"#Stalfos deep in the Forest Temple# guard", /*french*/"", /*spanish*/"los #Stalfos en lo profundo del Templo del Bosque# guardan"}
  );

  HintText ForestTemple_MQ_RaisedIslandCourtyardLowerChest = HintText::Exclude({
                       //obscure text
                       Text{"a #chest on a small island# in the Forest Temple holds", /*french*/"", /*spanish*/"un #cofre sobre una isla# del Templo del Bosque contiene"},
  });

  HintText ForestTemple_MQ_RaisedIslandCourtyardUpperChest = HintText::Exclude({
                       //obscure text
                       Text{"#high in a courtyard# within the Forest Temple is", /*french*/"", /*spanish*/"un #cofre en lo alto de un patio# del Templo del Bosque contiene"},
  });

  HintText ForestTemple_MQ_WellChest = HintText::Exclude({
                       //obscure text
                       Text{"a #sunken chest deep in the woods# contains", /*french*/"", /*spanish*/"un #sumergido cofre en lo profundo del bosque# contiene"},
  });

  HintText ForestTemple_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"#Joelle# guards", /*french*/"", /*spanish*/"#Joelle# guarda"},
                     },
                       //clear text
                       Text{"a #red ghost# guards", /*french*/"", /*spanish*/"un #fantasma rojo# guarda"}
  );

  HintText ForestTemple_MQ_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#Beth# guards", /*french*/"", /*spanish*/"#Beth# guarda"},
                     },
                       //clear text
                       Text{"a #blue ghost# guards", /*french*/"", /*spanish*/"un #fantasma azul# guarda"}
  );

  HintText ForestTemple_MQ_FallingCeilingRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"beneath a #checkerboard falling ceiling# lies", /*french*/"", /*spanish*/"tras un #techo de ajedrez# yace"},
  });

  HintText ForestTemple_MQ_BasementChest = HintText::Exclude({
                       //obscure text
                       Text{"#revolving walls# in the Forest Temple conceal", /*french*/"", /*spanish*/"las #paredes giratorias# del Templo del Bosque conceden"},
  });

  HintText ForestTemple_MQ_RedeadChest = HintText::Exclude({
                       //obscure text
                       Text{"deep in the forest #undead guard a chest# containing", /*french*/"", /*spanish*/"en lo profundo del bosque #guardias del más allá# guardan"},
  });

  HintText ForestTemple_MQ_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"a #turned trunk# contains", /*french*/"", /*spanish*/"en una #sala con otro punto de vista# se esconde"},
  });


  HintText FireTemple_NearBossChest = HintText::Exclude({
                       //obscure text
                       Text{"#near a dragon# is", /*french*/"", /*spanish*/"#cerca de un dragón# yace"},
  });

  HintText FireTemple_FlareDancerChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Flare Dancer behind a totem# guards", /*french*/"", /*spanish*/"el #Bailafuego tras unos tótems# esconde"},
  });

  HintText FireTemple_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"a #prison beyond a totem# holds", /*french*/"", /*spanish*/"en una #prisión tras unos tótems# yace"},
  });

  HintText FireTemple_BigLavaRoomBlockedDoorChest = HintText::Exclude({
                       //obscure text
                       Text{"#explosives over a lava pit# unveil", /*french*/"", /*spanish*/"los #explosivos en un mar de llamas# revelan"},
  });

  HintText FireTemple_BigLavaRoomLowerOpenDoorChest = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron trapped near lava# holds", /*french*/"", /*spanish*/"un #goron atrapado cerca de un mar de llamas# guarda"},
  });

  HintText FireTemple_BoulderMazeLowerChest = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron at the end of a maze# holds", /*french*/"", /*spanish*/"un #goron al final de un laberinto# guarda"},
  });

  HintText FireTemple_BoulderMazeUpperChest = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron above a maze# holds", /*french*/"", /*spanish*/"un #goron sobre un laberinto# guarda"},
  });

  HintText FireTemple_BoulderMazeSideRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron hidden near a maze# holds", /*french*/"", /*spanish*/"un #goron escondido tras un laberinto# guarda"},
  });

  HintText FireTemple_BoulderMazeShortcutChest = HintText::Exclude({
                       //obscure text
                       Text{"a #blocked path# in Fire Temple holds", /*french*/"", /*spanish*/"en un #camino bloqueado# del Templo del Fuego yace"},
  });

  HintText FireTemple_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"a #caged chest# in the Fire Temple hoards", /*french*/"", /*spanish*/"un #cofre entre rejas# del Templo del Fuego contiene"},
  });

  HintText FireTemple_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"a #chest in a fiery maze# contains", /*french*/"", /*spanish*/"un #cofre de un ardiente laberinto# contiene"},
  });

  HintText FireTemple_HighestGoronChest = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron atop the Fire Temple# holds", /*french*/"", /*spanish*/"un #goron en lo alto del Templo del Fuego# guarda"},
  });


  HintText FireTemple_MQ_NearBossChest = HintText::Exclude({
                       //obscure text
                       Text{"#near a dragon# is", /*french*/"", /*spanish*/"#cerca de un dragón# yace"},
  });

  HintText FireTemple_MQ_MegatonHammerChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Flare Dancer in the depths of a volcano# guards", /*french*/"", /*spanish*/"el #Bailafuego en lo profundo del volcán# esconde"},
                     },
                       //clear text
                       Text{"the #Flare Dancer in the depths of the Fire Temple# guards", /*french*/"", /*spanish*/"el #Bailafuego en lo profundo del Templo del Fuego# esconde"}
  );

  HintText FireTemple_MQ_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"a #blocked path# in Fire Temple holds", /*french*/"", /*spanish*/"en un #camino bloqueado# del Templo del Fuego yace"},
  });

  HintText FireTemple_MQ_LizalfosMazeLowerChest = HintText::Exclude({
                       //obscure text
                       Text{"#crates in a maze# contain", /*french*/"", /*spanish*/"las #cajas de un laberinto# contienen"},
  });

  HintText FireTemple_MQ_LizalfosMazeUpperChest = HintText::Exclude({
                       //obscure text
                       Text{"#crates in a maze# contain", /*french*/"", /*spanish*/"las #cajas de un laberinto# contienen"},
  });

  HintText FireTemple_MQ_MapRoomSideChest = HintText::Exclude({
                       //obscure text
                       Text{"a #falling slug# in the Fire Temple guards", /*french*/"", /*spanish*/"una #babosa del techo# del Templo del Fuego guarda"},
  });

  HintText FireTemple_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"using a #hammer in the depths of the Fire Temple# reveals", /*french*/"", /*spanish*/"usar el #martillo en lo profundo del Templo del Fuego# revela"},
  });

  HintText FireTemple_MQ_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"#illuminating a lava pit# reveals the path to", /*french*/"", /*spanish*/"#iluminar un mar de llamas# revela"},
  });

  HintText FireTemple_MQ_BigLavaRoomBlockedDoorChest = HintText::Exclude({
                       //obscure text
                       Text{"#explosives over a lava pit# unveil", /*french*/"", /*spanish*/"los #explosivos en un mar de llamas# revelan"},
  });

  HintText FireTemple_MQ_LizalfosMazeSideRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron hidden near a maze# holds", /*french*/"", /*spanish*/"un #goron cerca de un laberinto# guarda"},
  });

  HintText FireTemple_MQ_FreestandingKey = HintText::Exclude({
                       //obscure text
                       Text{"hidden #beneath a block of stone# lies", /*french*/"", /*spanish*/"#bajo unos bloques de piedra# yace"},
  });


  HintText WaterTemple_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"#rolling spikes# in the Water Temple surround", /*french*/"", /*spanish*/"unas #rodantes púas# del Templo del Agua guardan"},
  });

  HintText WaterTemple_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#roaming stingers in the Water Temple# guard", /*french*/"", /*spanish*/"unos #errantes stingers# del Templo del Agua guardan"},
  });

  HintText WaterTemple_TorchesChest = HintText::Exclude({
                       //obscure text
                       Text{"#fire in the Water Temple# reveals", /*french*/"", /*spanish*/"el #fuego en el Templo del Agua# revela"},
  });

  HintText WaterTemple_DragonChest = HintText::Exclude({
                       //obscure text
                       Text{"a #serpent's prize# in the Water Temple is", /*french*/"", /*spanish*/"el #escamado premio# del Templo del Agua se trata de"},
  });

  HintText WaterTemple_CentralBowTargetChest = HintText::Exclude({
                       //obscure text
                       Text{"#blinding an eye# in the Water Temple leads to", /*french*/"", /*spanish*/"#cegar un ojo# del Templo del Agua conduce a"},
  });

  HintText WaterTemple_CentralPillarChest = HintText::Exclude({
                       //obscure text
                       Text{"in the #depths of the Water Temple# lies", /*french*/"", /*spanish*/"en las #profundidades del Templo del Agua yace"},
  });

  HintText WaterTemple_CrackedWallChest = HintText::Exclude({
                       //obscure text
                       Text{"#through a crack# in the Water Temple is", /*french*/"", /*spanish*/"tras una #agrietada pared# del Templo del Agua yace"},
  });

  HintText WaterTemple_LongshotChest = HintText::Exclude({
                       //obscure text
                       Text{"#facing yourself# reveals",              /*french*/"", /*spanish*/"#luchar contra ti mismo# revela"},
                       Text{"a #dark reflection# of yourself guards", /*french*/"", /*spanish*/"el #oscuro reflejo de ti mismo# guarda"},
                     },
                       //clear text
                       Text{"#Dark Link# guards", /*french*/"", /*spanish*/"#Link Oscuro# guarda"}
  );


  HintText WaterTemple_MQ_CentralPillarChest = HintText::Exclude({
                       //obscure text
                       Text{"in the #depths of the Water Temple# lies", /*french*/"", /*spanish*/"en las #profundidades del Templo del Agua# yace"},
  });

  HintText WaterTemple_MQ_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"fire in the Water Temple unlocks a #vast gate# revealing a chest with", /*french*/"", /*spanish*/"el fuego en el Templo del Agua alza una #gran valla#, habiendo dentro"},
  });

  HintText WaterTemple_MQ_LongshotChest = HintText::Exclude({
                       //obscure text
                       Text{"#through a crack# in the Water Temple is", /*french*/"", /*spanish*/"tras una #agrietada pared# del Templo del Agua yace"},
  });

  HintText WaterTemple_MQ_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#fire in the Water Temple# reveals", /*french*/"", /*spanish*/"el #fuego en el Templo del Agua# revela"},
  });

  HintText WaterTemple_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"#sparring soldiers# in the Water Temple guard", /*french*/"", /*spanish*/"#acabar con unos soldados# del Templo del Agua revela"},
  });


  HintText SpiritTemple_ChildBridgeChest = HintText::Exclude({
                       //obscure text
                       Text{"a child conquers a #skull in green fire# in the Spirit Temple to reach", /*french*/"", /*spanish*/"el joven que #acabe con la calavera de verde fuego# del Templo del Espíritu encontrará"},
  });

  HintText SpiritTemple_ChildEarlyTorchesChest = HintText::Exclude({
                       //obscure text
                       Text{"a child can find a #caged chest# in the Spirit Temple with", /*french*/"", /*spanish*/"un joven puede encontrar un #cofre entre rejas# del Templo del Espíritu con"},
  });

  HintText SpiritTemple_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#across a pit of sand# in the Spirit Temple lies", /*french*/"", /*spanish*/"tras un #pozo de arena# del Templo del Espíritu yace"},
  });

  HintText SpiritTemple_EarlyAdultRightChest = HintText::Exclude({
                       //obscure text
                       Text{"#dodging boulders to collect silver rupees# in the Spirit Temple yields", /*french*/"", /*spanish*/"#esquivar rocas y conseguir plateadas rupias# en el Templo del Espíritu conduce a"},
  });

  HintText SpiritTemple_FirstMirrorLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"a #shadow circling reflected light# in the Spirit Temple guards", /*french*/"", /*spanish*/"un #círculo de reflectante luz# del Templo del Espíritu guarda"},
  });

  HintText SpiritTemple_FirstMirrorRightChest = HintText::Exclude({
                       //obscure text
                       Text{"a #shadow circling reflected light# in the Spirit Temple guards", /*french*/"", /*spanish*/"un #círculo de reflectante luz# del Templo del Espíritu guarda"},
  });

  HintText SpiritTemple_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"#before a giant statue# in the Spirit Temple lies", /*french*/"", /*spanish*/"#ante una gran estatua# del Templo del Espíritu aguarda"},
  });

  HintText SpiritTemple_ChildClimbNorthChest = HintText::Exclude({
                       //obscure text
                       Text{"#lizards in the Spirit Temple# guard", /*french*/"", /*spanish*/"los #reptiles del Templo del Espíritu# guardan"},
  });

  HintText SpiritTemple_ChildClimbEastChest = HintText::Exclude({
                       //obscure text
                       Text{"#lizards in the Spirit Temple# guard", /*french*/"", /*spanish*/"los #reptiles del Templo del Espíritu# guardan"},
  });

  HintText SpiritTemple_SunBlockRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"#torchlight among Beamos# in the Spirit Temple reveals", /*french*/"", /*spanish*/"las #antorchas junto a Beamos# del Templo del Espíritu revelan"},
  });

  HintText SpiritTemple_StatueRoomHandChest = HintText::Exclude({
                       //obscure text
                       Text{"a #statue in the Spirit Temple# holds", /*french*/"", /*spanish*/"una #estatua del Templo del Espíritu# esconde"},
  });

  HintText SpiritTemple_StatueRoomNortheastChest = HintText::Exclude({
                       //obscure text
                       Text{"on a #ledge by a statue# in the Spirit Temple rests", /*french*/"", /*spanish*/"al #borde de una estatua# del Templo del Espíritu yace"},
  });

  HintText SpiritTemple_NearFourArmosChest = HintText::Exclude({
                       //obscure text
                       Text{"those who #show the light among statues# in the Spirit Temple find", /*french*/"", /*spanish*/"aquellos que #iluminen ante las estatuas# del Templo del Espíritu encontrarán"},
  });

  HintText SpiritTemple_HallwayRightInvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth in the Spirit Temple# reveals", /*french*/"", /*spanish*/"el #Ojo de la Verdad# en el Templo del Espíritu revela"},
  });

  HintText SpiritTemple_HallwayLeftInvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth in the Spirit Temple# reveals", /*french*/"", /*spanish*/"el #Ojo de la Verdad# en el Templo del Espíritu revela"},
  });

  HintText SpiritTemple_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"a #chest engulfed in flame# in the Spirit Temple holds", /*french*/"", /*spanish*/"un #cofre rodeado de llamas# del Templo del Espíritu contiene"},
  });

  HintText SpiritTemple_TopmostChest = HintText::Exclude({
                       //obscure text
                       Text{"those who #show the light above the Colossus# find", /*french*/"", /*spanish*/"aquellos que #iluminen en lo alto del Coloso# encontrarán"},
  });


  HintText SpiritTemple_MQ_EntranceFrontLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"#lying unguarded# in the Spirit Temple is", /*french*/"", /*spanish*/"en la #entrada del Templo del Espíritu# yace"},
  });

  HintText SpiritTemple_MQ_EntranceBackRightChest = HintText::Exclude({
                       //obscure text
                       Text{"a #switch in a pillar# within the Spirit Temple drops", /*french*/"", /*spanish*/"el #interruptor de un pilar# del Templo del Espíritu revela"},
  });

  HintText SpiritTemple_MQ_EntranceFrontRightChest = HintText::Exclude({
                       //obscure text
                       Text{"#collecting rupees through a water jet# reveals", /*french*/"", /*spanish*/"#hacerte con rupias tras un géiser# revela"},
  });

  HintText SpiritTemple_MQ_EntranceBackLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"an #eye blinded by stone# within the Spirit Temple conceals", /*french*/"", /*spanish*/"#cegar a un ojo# del Templo del Espíritu revela"},
  });

  HintText SpiritTemple_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"surrounded by #fire and wrappings# lies", /*french*/"", /*spanish*/"rodeado de #fuego y vendas# yace"},
  });

  HintText SpiritTemple_MQ_MapRoomEnemyChest = HintText::Exclude({
                       //obscure text
                       Text{"a child defeats a #gauntlet of monsters# within the Spirit Temple to find", /*french*/"", /*spanish*/"el joven que derrote un #puñado de monstruos# del Templo del Espíritu encontrará"},
  });

  HintText SpiritTemple_MQ_ChildClimbNorthChest = HintText::Exclude({
                       //obscure text
                       Text{"#explosive sunlight# within the Spirit Temple uncovers", /*french*/"", /*spanish*/"una #explosiva luz solar# del Templo del Espíritu revela"},
  });

  HintText SpiritTemple_MQ_ChildClimbSouthChest = HintText::Exclude({
                       //obscure text
                       Text{"#trapped by falling enemies# within the Spirit Temple is", /*french*/"", /*spanish*/"#rodeado de enemigos del cielo# del Templo del Espíritu yace"},
  });

  HintText SpiritTemple_MQ_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#blinding the colossus# unveils", /*french*/"", /*spanish*/"#cegar al coloso# revela"},
  });

  HintText SpiritTemple_MQ_StatueRoomLullabyChest = HintText::Exclude({
                       //obscure text
                       Text{"a #royal melody awakens the colossus# to reveal", /*french*/"", /*spanish*/"la #melodía real que despierte al coloso# revelará"},
  });

  HintText SpiritTemple_MQ_StatueRoomInvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth# finds the colossus's hidden", /*french*/"", /*spanish*/"el #Ojo de la Verdad# en el Templo del Espíritu encuentra"},
  });

  HintText SpiritTemple_MQ_SilverBlockHallwayChest = HintText::Exclude({
                       //obscure text
                       Text{"#the old hide what the young find# to reveal", /*french*/"", /*spanish*/"el #adulto esconde lo que el joven anhela# de encontrar"},
  });

  HintText SpiritTemple_MQ_SunBlockRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"#sunlight in a maze of fire# hides", /*french*/"", /*spanish*/"la #luz solar de un ígneo laberinto# esconde"},
  });

  HintText SpiritTemple_MQ_LeeverRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"#across a pit of sand# in the Spirit Temple lies", /*french*/"", /*spanish*/"#a través del pozo de arena# del Templo del Espíritu yace"},
  });

  HintText SpiritTemple_MQ_BeamosRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"where #temporal stone blocks the path# within the Spirit Temple lies", /*french*/"", /*spanish*/"donde los #bloques temporales bloquean# en el Templo del Espíritu yace"},
  });

  HintText SpiritTemple_MQ_ChestSwitchChest = HintText::Exclude({
                       //obscure text
                       Text{"a #chest of double purpose# holds", /*french*/"", /*spanish*/"un #cofre de doble uso# contiene"},
  });

  HintText SpiritTemple_MQ_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"a #temporal stone blocks the light# leading to", /*french*/"", /*spanish*/"un #bloque temporal bloquea la luz# que conduce a"},
  });

  HintText SpiritTemple_MQ_MirrorPuzzleInvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"those who #show the light above the Colossus# find", /*french*/"", /*spanish*/"aquellos que #revelen la luz sobre el Coloso# encontrarán"},
  });


  HintText ShadowTemple_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth# pierces a hall of faces to reveal", /*french*/"", /*spanish*/"el #Ojo de la Verdad# descubre un pasillo de facetas con"},
  });

  HintText ShadowTemple_HoverBootsChest = HintText::Exclude({
                       //obscure text
                       Text{"a #nether dweller in the Shadow Temple# holds", /*french*/"", /*spanish*/"un #temido morador del Templo de las Sombras# guarda"},
                     },
                       //clear text
                       Text{"#Dead Hand in the Shadow Temple# holds", /*french*/"", /*spanish*/"la #Mano Muerta del Templo de las Sombras# guarda"}
  );

  HintText ShadowTemple_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#mummies revealed by the Eye of Truth# guard", /*french*/"", /*spanish*/"las #momias reveladas por el Ojo de la Verdad# guardan"},
  });

  HintText ShadowTemple_EarlySilverRupeeChest = HintText::Exclude({
                       //obscure text
                       Text{"#spinning scythes# protect", /*french*/"", /*spanish*/"las #giratorias guadañas# protegen"},
  });

  HintText ShadowTemple_InvisibleBladesVisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"#invisible blades# guard", /*french*/"", /*spanish*/"las #hojas invisibles# guardan"},
  });

  HintText ShadowTemple_InvisibleBladesInvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"#invisible blades# guard", /*french*/"", /*spanish*/"las #hojas invisibles# guardan"},
  });

  HintText ShadowTemple_FallingSpikesLowerChest = HintText::Exclude({
                       //obscure text
                       Text{"#falling spikes# block the path to", /*french*/"", /*spanish*/"los #pinchos del techo# conducen a"},
  });

  HintText ShadowTemple_FallingSpikesUpperChest = HintText::Exclude({
                       //obscure text
                       Text{"#falling spikes# block the path to", /*french*/"", /*spanish*/"los #pinchos del techo# conducen a"},
  });

  HintText ShadowTemple_FallingSpikesSwitchChest = HintText::Exclude({
                       //obscure text
                       Text{"#falling spikes# block the path to", /*french*/"", /*spanish*/"los #pinchos del techo# conducen a"},
  });

  HintText ShadowTemple_InvisibleSpikesChest = HintText::Exclude({
                       //obscure text
                       Text{"the #dead roam among invisible spikes# guarding", /*french*/"", /*spanish*/"los #muertos que vagan por pinchos invisibles# protegen"},
  });

  HintText ShadowTemple_WindHintChest = HintText::Exclude({
                       //obscure text
                       Text{"an #invisible chest guarded by the dead# holds", /*french*/"", /*spanish*/"un #cofre invisible custodiado por los del más allá# contiene"},
  });

  HintText ShadowTemple_AfterWindEnemyChest = HintText::Exclude({
                       //obscure text
                       Text{"#mummies guarding a ferry# hide", /*french*/"", /*spanish*/"las #momias que protegen un navío# esconden"},
  });

  HintText ShadowTemple_AfterWindHiddenChest = HintText::Exclude({
                       //obscure text
                       Text{"#mummies guarding a ferry# hide", /*french*/"", /*spanish*/"las #momias que protegen un navío# esconden"},
  });

  HintText ShadowTemple_SpikeWallsLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"#walls consumed by a ball of fire# reveal", /*french*/"", /*spanish*/"las #paredes consumidas por una esfera ígnea# revelan"},
  });

  HintText ShadowTemple_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"#walls consumed by a ball of fire# reveal", /*french*/"", /*spanish*/"las #paredes consumidas por una esfera ígnea# revelan"},
  });

  HintText ShadowTemple_FreestandingKey = HintText::Exclude({
                       //obscure text
                       Text{"#inside a burning skull# lies", /*french*/"", /*spanish*/"en el #interior de una calavera en llamas# aguarda"},
  });


  HintText ShadowTemple_MQ_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth# pierces a hall of faces to reveal", /*french*/"", /*spanish*/"el #Ojo de la Verdad# descubre un pasillo de facetas con"},
  });

  HintText ShadowTemple_MQ_HoverBootsChest = HintText::Exclude({
                       //obscure text
                       Text{"#Dead Hand in the Shadow Temple# holds", /*french*/"", /*spanish*/"la #Mano Muerta del Templo de las Sombras# guarda"},
  });

  HintText ShadowTemple_MQ_EarlyGibdosChest = HintText::Exclude({
                       //obscure text
                       Text{"#mummies revealed by the Eye of Truth# guard", /*french*/"", /*spanish*/"las #momias reveladas por el Ojo de la Verdad# guardan"},
  });

  HintText ShadowTemple_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"#spinning scythes# protect", /*french*/"", /*spanish*/"las #giratorias guadañas# protegen"},
  });

  HintText ShadowTemple_MQ_BeamosSilverRupeesChest = HintText::Exclude({
                       //obscure text
                       Text{"#collecting rupees in a vast cavern# with the Shadow Temple unveils", /*french*/"", /*spanish*/"hacerte con las #rupias en una gran caverna# del Templo de las Sombras revela"},
  });

  HintText ShadowTemple_MQ_FallingSpikesSwitchChest = HintText::Exclude({
                       //obscure text
                       Text{"#falling spikes# block the path to", /*french*/"", /*spanish*/"los #pinchos del techo# conducen a"},
  });

  HintText ShadowTemple_MQ_FallingSpikesLowerChest = HintText::Exclude({
                       //obscure text
                       Text{"#falling spikes# block the path to", /*french*/"", /*spanish*/"los #pinchos del techo# conducen a"},
  });

  HintText ShadowTemple_MQ_FallingSpikesUpperChest = HintText::Exclude({
                       //obscure text
                       Text{"#falling spikes# block the path to", /*french*/"", /*spanish*/"los #pinchos del techo# conducen a"},
  });

  HintText ShadowTemple_MQ_InvisibleSpikesChest = HintText::Exclude({
                       //obscure text
                       Text{"the #dead roam among invisible spikes# guarding", /*french*/"", /*spanish*/"los #muertos que vagan por pinchos invisibles# protegen"},
  });

  HintText ShadowTemple_MQ_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"#walls consumed by a ball of fire# reveal", /*french*/"", /*spanish*/"las #paredes consumidas por una esfera ígnea# revelan"},
  });

  HintText ShadowTemple_MQ_SpikeWallsLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"#walls consumed by a ball of fire# reveal", /*french*/"", /*spanish*/"las #paredes consumidas por una esfera ígnea# revelan"},
  });

  HintText ShadowTemple_MQ_StalfosRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"near an #empty pedestal# within the Shadow Temple lies", /*french*/"", /*spanish*/"cerca de un #vacío pedestal# del Templo de las Sombras yace"},
  });

  HintText ShadowTemple_MQ_InvisibleBladesInvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"#invisible blades# guard", /*french*/"", /*spanish*/"las #hojas invisibles# guardan"},
  });

  HintText ShadowTemple_MQ_InvisibleBladesVisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"#invisible blades# guard", /*french*/"", /*spanish*/"las #hojas invisibles# guardan"},
  });

  HintText ShadowTemple_MQ_WindHintChest = HintText::Exclude({
                       //obscure text
                       Text{"an #invisible chest guarded by the dead# holds", /*french*/"", /*spanish*/"un #cofre invisible custodiado por los del más allá# contiene"},
  });

  HintText ShadowTemple_MQ_AfterWindHiddenChest = HintText::Exclude({
                       //obscure text
                       Text{"#mummies guarding a ferry# hide", /*french*/"", /*spanish*/"las #momias que protegen un navío# esconden"},
  });

  HintText ShadowTemple_MQ_AfterWindEnemyChest = HintText::Exclude({
                       //obscure text
                       Text{"#mummies guarding a ferry# hide", /*french*/"", /*spanish*/"las #momias que protegen un navío# esconden"},
  });

  HintText ShadowTemple_MQ_NearShipInvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"#caged near a ship# lies", /*french*/"", /*spanish*/"#entre rejas al lado de un navío# yace"},
  });

  HintText ShadowTemple_MQ_FreestandingKey = HintText::Exclude({
                       //obscure text
                       Text{"#behind three burning skulls# lies", /*french*/"", /*spanish*/"tras #tres ardientes calaveras# yace"},
  });


  HintText BottomOfTheWell_FrontLeftFakeWallChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth in the well# reveals", /*french*/"", /*spanish*/"el #Ojo de la Verdad en el pozo# revela"},
  });

  HintText BottomOfTheWell_FrontCenterBombableChest = HintText::Exclude({
                       //obscure text
                       Text{"#gruesome debris# in the well hides", /*french*/"", /*spanish*/"unos #horripilantes escombros# del pozo esconden"},
  });

  HintText BottomOfTheWell_RightBottomFakeWallChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth in the well# reveals", /*french*/"", /*spanish*/"el #Ojo de la Verdad en el pozo# revela"},
  });

  HintText BottomOfTheWell_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"a #hidden entrance to a cage# in the well leads to", /*french*/"", /*spanish*/"la #entrada oculta de una celda# del pozo conduce a"},
  });

  HintText BottomOfTheWell_CenterSkulltulaChest = HintText::Exclude({
                       //obscure text
                       Text{"a #spider guarding a cage# in the well protects", /*french*/"", /*spanish*/"una #araña protegiendo una celda# del pozo guarda"},
  });

  HintText BottomOfTheWell_BackLeftBombableChest = HintText::Exclude({
                       //obscure text
                       Text{"#gruesome debris# in the well hides", /*french*/"", /*spanish*/"unos #horripilantes escombros# del pozo esconden"},
  });

  HintText BottomOfTheWell_InvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"#Dead Hand's invisible secret# is", /*french*/"", /*spanish*/"el #secreto invisible de la Mano Muerta# se trata de"},
  });

  HintText BottomOfTheWell_UnderwaterFrontChest = HintText::Exclude({
                       //obscure text
                       Text{"a #royal melody in the well# uncovers", /*french*/"", /*spanish*/"una #melodía real en el pozo# revela"},
  });

  HintText BottomOfTheWell_UnderwaterLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"a #royal melody in the well# uncovers", /*french*/"", /*spanish*/"una #melodía real en el pozo# revela"},
  });

  HintText BottomOfTheWell_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"in the #depths of the well# lies", /*french*/"", /*spanish*/"en las #profundidades del pozo# yace"},
  });

  HintText BottomOfTheWell_FireKeeseChest = HintText::Exclude({
                       //obscure text
                       Text{"#perilous pits# in the well guard the path to", /*french*/"", /*spanish*/"#peligrosos fosos# del pozo conducen a"},
  });

  HintText BottomOfTheWell_LikeLikeChest = HintText::Exclude({
                       //obscure text
                       Text{"#locked in a cage# in the well lies", /*french*/"", /*spanish*/"#entre rejas# en el pozo yace"},
  });

  HintText BottomOfTheWell_FreestandingKey = HintText::Exclude({
                       //obscure text
                       Text{"#inside a coffin# hides", /*french*/"", /*spanish*/"en el #interior de un ataúd# yace"},
  });


  HintText BottomOfTheWell_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"a #royal melody in the well# uncovers", /*french*/"", /*spanish*/"una #melodía real en el pozo# revela"},
  });

  HintText BottomOfTheWell_MQ_LensOfTruthChest = HintText::Exclude({
                       //obscure text
                       Text{"an #army of the dead# in the well guards", /*french*/"", /*spanish*/"un #ejército del más allá# del pozo guarda"},
  });

  HintText BottomOfTheWell_MQ_DeadHandFreestandingKey = HintText::Exclude({
                       //obscure text
                       Text{"#Dead Hand's explosive secret# is", /*french*/"", /*spanish*/"el #explosivo secreto de la Mano Muerta# se trata de"},
  });

  HintText BottomOfTheWell_MQ_EastInnerRoomFreestandingKey = HintText::Exclude({
                       //obscure text
                       Text{"an #invisible path in the well# leads to", /*french*/"", /*spanish*/"un #camino invisible del pozo# conduce a"},
  });


  HintText IceCavern_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"#winds of ice# surround", /*french*/"", /*spanish*/"#heladas borrascas# rodean"},
  });

  HintText IceCavern_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"a #wall of ice# protects", /*french*/"", /*spanish*/"una #gélida pared# protege"},
  });

  HintText IceCavern_IronBootsChest = HintText::Exclude({
                       //obscure text
                       Text{"a #monster in a frozen cavern# guards", /*french*/"", /*spanish*/"un #monstruo de una helada caverna# guarda"},
  });

  HintText IceCavern_FreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"a #wall of ice# protects", /*french*/"", /*spanish*/"una #gélida pared# protege"},
  });


  HintText IceCavern_MQ_IronBootsChest = HintText::Exclude({
                       //obscure text
                       Text{"a #monster in a frozen cavern# guards", /*french*/"", /*spanish*/"un #monstruo de una helada caverna# guarda"},
  });

  HintText IceCavern_MQ_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#winds of ice# surround", /*french*/"", /*spanish*/"#heladas borrascas# rodean"},
  });

  HintText IceCavern_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"a #wall of ice# protects", /*french*/"", /*spanish*/"una #gélida pared# protege"},
  });

  HintText IceCavern_MQ_FreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"#winds of ice# surround", /*french*/"", /*spanish*/"#heladas borrascas# rodean"},
  });


  HintText GerudoTrainingGrounds_LobbyLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"a #blinded eye in the Gerudo Training Grounds# drops", /*french*/"", /*spanish*/"#cegar un ojo en el Centro de Instrucción Gerudo# revela"},
  });

  HintText GerudoTrainingGrounds_LobbyRightChest = HintText::Exclude({
                       //obscure text
                       Text{"a #blinded eye in the Gerudo Training Grounds# drops", /*french*/"", /*spanish*/"#cegar un ojo en el Centro de Instrucción Gerudo# revela"},
  });

  HintText GerudoTrainingGrounds_StalfosChest = HintText::Exclude({
                       //obscure text
                       Text{"#soldiers walking on shifting sands# in the Gerudo Training Grounds guard", /*french*/"", /*spanish*/"#soldados en resbaladizas arenas# del Centro de Instrucción Gerudo protegen"},
  });

  HintText GerudoTrainingGrounds_BeamosChest = HintText::Exclude({
                       //obscure text
                       Text{"#reptilian warriors# in the Gerudo Training Grounds protect", /*french*/"", /*spanish*/"#unos escamosos guerreros# del Centro de Instrucción Gerudo protegen"},
  });

  HintText GerudoTrainingGrounds_HiddenCeilingChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth# in the Gerudo Training Grounds reveals", /*french*/"", /*spanish*/"el #Ojo de la Verdad# en el Centro de Instrucción Gerudo revela"},
  });

  HintText GerudoTrainingGrounds_MazePathFirstChest = HintText::Exclude({
                       //obscure text
                       Text{"the first prize of #the thieves' training# is", /*french*/"", /*spanish*/"el primer premio de la #instrucción ladrona# se trata de"},
  });

  HintText GerudoTrainingGrounds_MazePathSecondChest = HintText::Exclude({
                       //obscure text
                       Text{"the second prize of #the thieves' training# is", /*french*/"", /*spanish*/"el segundo premio de la #instrucción ladrona# se trata de"},
  });

  HintText GerudoTrainingGrounds_MazePathThirdChest = HintText::Exclude({
                       //obscure text
                       Text{"the third prize of #the thieves' training# is", /*french*/"", /*spanish*/"el tercer premio de la #instrucción ladrona# se trata de"},
  });

  HintText GerudoTrainingGrounds_MazeRightCentralChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Song of Time# in the Gerudo Training Grounds leads to", /*french*/"", /*spanish*/"la #Canción del Tiempo# en el Centro de Instrucción Gerudo conduce a"},
  });

  HintText GerudoTrainingGrounds_MazeRightSideChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Song of Time# in the Gerudo Training Grounds leads to", /*french*/"", /*spanish*/"la #Canción del Tiempo# en el Centro de Instrucción Gerudo conduce a"},
  });

  HintText GerudoTrainingGrounds_HammerRoomClearChest = HintText::Exclude({
                       //obscure text
                       Text{"#fiery foes# in the Gerudo Training Grounds guard", /*french*/"", /*spanish*/"unos #candentes enemigos# del Centro de Instrucción Gerudo guardan"},
  });

  HintText GerudoTrainingGrounds_HammerRoomSwitchChest = HintText::Exclude({
                       //obscure text
                       Text{"#engulfed in flame# where thieves train lies", /*french*/"", /*spanish*/"donde entrenan las ladronas #entre llamas# yace"},
  });

  HintText GerudoTrainingGrounds_EyeStatueChest = HintText::Exclude({
                       //obscure text
                       Text{"thieves #blind four faces# to find", /*french*/"", /*spanish*/"las ladronas #ciegan cuatro facetas# para hallar"},
  });

  HintText GerudoTrainingGrounds_NearScarecrowChest = HintText::Exclude({
                       //obscure text
                       Text{"thieves #blind four faces# to find", /*french*/"", /*spanish*/"las ladronas #ciegan cuatro facetas# para hallar"},
  });

  HintText GerudoTrainingGrounds_BeforeHeavyBlockChest = HintText::Exclude({
                       //obscure text
                       Text{"#before a block of silver# thieves can find", /*french*/"", /*spanish*/"#ante un plateado bloque# las ladronas hallan"},
  });

  HintText GerudoTrainingGrounds_HeavyBlockFirstChest = HintText::Exclude({
                       //obscure text
                       Text{"a #feat of strength# rewards thieves with", /*french*/"", /*spanish*/"una #hazaña de fuerza# premia a las ladronas con"},
  });

  HintText GerudoTrainingGrounds_HeavyBlockSecondChest = HintText::Exclude({
                       //obscure text
                       Text{"a #feat of strength# rewards thieves with", /*french*/"", /*spanish*/"una #hazaña de fuerza# premia a las ladronas con"},
  });

  HintText GerudoTrainingGrounds_HeavyBlockThirdChest = HintText::Exclude({
                       //obscure text
                       Text{"a #feat of strength# rewards thieves with", /*french*/"", /*spanish*/"una #hazaña de fuerza# premia a las ladronas con"},
  });

  HintText GerudoTrainingGrounds_HeavyBlockFourthChest = HintText::Exclude({
                       //obscure text
                       Text{"a #feat of strength# rewards thieves with", /*french*/"", /*spanish*/"una #hazaña de fuerza# premia a las ladronas con"},
  });

  HintText GerudoTrainingGrounds_FreestandingKey = HintText::Exclude({
                       //obscure text
                       Text{"the #Song of Time# in the Gerudo Training Grounds leads to", /*french*/"", /*spanish*/"la #Canción del Tiempo# en el Centro de Instrucción Gerudo conduce a"},
  });


  HintText GerudoTrainingGrounds_MQ_LobbyRightChest = HintText::Exclude({
                       //obscure text
                       Text{"#thieves prepare for training# with", /*french*/"", /*spanish*/"las #ladronas se instruyen# con"},
  });

  HintText GerudoTrainingGrounds_MQ_LobbyLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"#thieves prepare for training# with", /*french*/"", /*spanish*/"las #ladronas se instruyen# con"},
  });

  HintText GerudoTrainingGrounds_MQ_FirstIronKnuckleChest = HintText::Exclude({
                       //obscure text
                       Text{"#soldiers walking on shifting sands# in the Gerudo Training Grounds guard", /*french*/"", /*spanish*/"#soldados en resbaladizas arenas# del Centro de Instrucción Gerudo protegen"},
  });

  HintText GerudoTrainingGrounds_MQ_BeforeHeavyBlockChest = HintText::Exclude({
                       //obscure text
                       Text{"#before a block of silver# thieves can find", /*french*/"", /*spanish*/"#ante un plateado bloque# las ladronas hallang"},
  });

  HintText GerudoTrainingGrounds_MQ_EyeStatueChest = HintText::Exclude({
                       //obscure text
                       Text{"thieves #blind four faces# to find", /*french*/"", /*spanish*/"las ladronas #ciegan cuatro facetas# para hallar"},
  });

  HintText GerudoTrainingGrounds_MQ_FlameCircleChest = HintText::Exclude({
                       //obscure text
                       Text{"#engulfed in flame# where thieves train lies", /*french*/"", /*spanish*/"donde entrenan las ladronas #entre llamas# yace"},
  });

  HintText GerudoTrainingGrounds_MQ_SecondIronKnuckleChest = HintText::Exclude({
                       //obscure text
                       Text{"#fiery foes# in the Gerudo Training Grounds guard", /*french*/"", /*spanish*/"unos #candentes enemigos# del Centro de Instrucción Gerudo guardan"},
  });

  HintText GerudoTrainingGrounds_MQ_DinolfosChest = HintText::Exclude({
                       //obscure text
                       Text{"#reptilian warriors# in the Gerudo Training Grounds protect", /*french*/"", /*spanish*/"#unos escamosos guerreros# del Centro de Instrucción Gerudo protegen"},
  });

  HintText GerudoTrainingGrounds_MQ_MazeRightCentralChest = HintText::Exclude({
                       //obscure text
                       Text{"a #path of fire# leads thieves to", /*french*/"", /*spanish*/"un #camino de fuego# conduce a las ladronas a"},
  });

  HintText GerudoTrainingGrounds_MQ_MazePathFirstChest = HintText::Exclude({
                       //obscure text
                       Text{"the first prize of #the thieves' training# is", /*french*/"", /*spanish*/"el primer premio de la #instrucción ladrona# se trata de"},
  });

  HintText GerudoTrainingGrounds_MQ_MazeRightSideChest = HintText::Exclude({
                       //obscure text
                       Text{"a #path of fire# leads thieves to", /*french*/"", /*spanish*/"un #camino de fuego# conduce a las ladronas a"},
  });

  HintText GerudoTrainingGrounds_MQ_MazePathThirdChest = HintText::Exclude({
                       //obscure text
                       Text{"the third prize of #the thieves' training# is", /*french*/"", /*spanish*/"el tercer premio de la #instrucción ladrona# se trata de"},
  });

  HintText GerudoTrainingGrounds_MQ_MazePathSecondChest = HintText::Exclude({
                       //obscure text
                       Text{"the second prize of #the thieves' training# is", /*french*/"", /*spanish*/"el segundo premio de la #instrucción ladrona# se trata de"},
  });

  HintText GerudoTrainingGrounds_MQ_HiddenCeilingChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth# in the Gerudo Training Grounds reveals", /*french*/"", /*spanish*/"el #Ojo de la Verdad# en el Centro de Instrucción Gerudo revela"},
  });

  HintText GerudoTrainingGrounds_MQ_HeavyBlockChest = HintText::Exclude({
                       //obscure text
                       Text{"a #feat of strength# rewards thieves with", /*french*/"", /*spanish*/"una #hazaña de fuerza# premia a las ladronas con"},
  });


  HintText GanonsCastle_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Evil King# hoards", /*french*/"", /*spanish*/"el #Rey del Mal# acapara"},
  });


  HintText GanonsCastle_ForestTrialChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the wilds# holds", /*french*/"", /*spanish*/"la #prueba de la naturaleza# brinda"},
  });

  HintText GanonsCastle_WaterTrialLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the seas# holds", /*french*/"", /*spanish*/"la #prueba del mar# brinda"},
  });

  HintText GanonsCastle_WaterTrialRightChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the seas# holds", /*french*/"", /*spanish*/"la #prueba del mar# brinda"},
  });

  HintText GanonsCastle_ShadowTrialFrontChest = HintText::Exclude({
                       //obscure text
                       Text{"#music in the test of darkness# unveils", /*french*/"", /*spanish*/"la #música en la prueba de la oscuridad# revela"},
  });

  HintText GanonsCastle_ShadowTrialGoldenGauntletsChest = HintText::Exclude({
                       //obscure text
                       Text{"#light in the test of darkness# unveils", /*french*/"", /*spanish*/"la #luz en la prueba de la oscuridad# revela"},
  });

  HintText GanonsCastle_SpiritTrialCrystalSwitchChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the sands# holds", /*french*/"", /*spanish*/"la #prueba de las arenas# brinda"},
  });

  HintText GanonsCastle_SpiritTrialInvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the sands# holds", /*french*/"", /*spanish*/"la #prueba de las arenas# brinda"},
  });

  HintText GanonsCastle_LightTrialFirstLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of radiance# holds", /*french*/"", /*spanish*/"la #prueba del resplandor# brinda"},
  });

  HintText GanonsCastle_LightTrialSecondLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of radiance# holds", /*french*/"", /*spanish*/"la #prueba del resplandor# brinda"},
  });

  HintText GanonsCastle_LightTrialThirdLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of radiance# holds", /*french*/"", /*spanish*/"la #prueba del resplandor# brinda"},
  });

  HintText GanonsCastle_LightTrialFirstRightChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of radiance# holds", /*french*/"", /*spanish*/"la #prueba del resplandor# brinda"},
  });

  HintText GanonsCastle_LightTrialSecondRightChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of radiance# holds", /*french*/"", /*spanish*/"la #prueba del resplandor# brinda"},
  });

  HintText GanonsCastle_LightTrialThirdRightChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of radiance# holds", /*french*/"", /*spanish*/"la #prueba del resplandor# brinda"},
  });

  HintText GanonsCastle_LightTrialInvisibleEnemiesChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of radiance# holds", /*french*/"", /*spanish*/"la #prueba del resplandor# brinda"},
  });

  HintText GanonsCastle_LightTrialLullabyChest = HintText::Exclude({
                       //obscure text
                       Text{"#music in the test of radiance# reveals", /*french*/"", /*spanish*/"la #música en la prueba del resplandor# revela"},
  });


  HintText GanonsCastle_MQ_WaterTrialChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the seas# holds", /*french*/"", /*spanish*/"la #prueba del mar# brinda"},
  });

  HintText GanonsCastle_MQ_ForestTrialEyeSwitchChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the wilds# holds", /*french*/"", /*spanish*/"la #prueba de la naturaleza# brinda"},
  });

  HintText GanonsCastle_MQ_ForestTrialFrozenEyeSwitchChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the wilds# holds", /*french*/"", /*spanish*/"la #prueba de la naturaleza# brinda"},
  });

  HintText GanonsCastle_MQ_LightTrialLullabyChest = HintText::Exclude({
                       //obscure text
                       Text{"#music in the test of radiance# reveals", /*french*/"", /*spanish*/"la #música en la prueba del resplandor# revela"},
  });

  HintText GanonsCastle_MQ_ShadowTrialBombFlowerChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of darkness# holds", /*french*/"", /*spanish*/"la #prueba de la oscuridad# brinda"},
  });

  HintText GanonsCastle_MQ_ShadowTrialEyeSwitchChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of darkness# holds", /*french*/"", /*spanish*/"la #prueba de la oscuridad# brinda"},
  });

  HintText GanonsCastle_MQ_SpiritTrialGoldenGauntletsChest = HintText::Exclude({
                       //obscure text
                       Text{"#reflected light in the test of the sands# reveals", /*french*/"", /*spanish*/"#reflejar la luz en la prueba de las arenas# revela"},
  });

  HintText GanonsCastle_MQ_SpiritTrialSunBackRightChest = HintText::Exclude({
                       //obscure text
                       Text{"#reflected light in the test of the sands# reveals", /*french*/"", /*spanish*/"#reflejar la luz en la prueba de las arenas# revela"},
  });

  HintText GanonsCastle_MQ_SpiritTrialSunBackLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"#reflected light in the test of the sands# reveals", /*french*/"", /*spanish*/"#reflejar la luz en la prueba de las arenas# revela"},
  });

  HintText GanonsCastle_MQ_SpiritTrialSunFrontLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"#reflected light in the test of the sands# reveals", /*french*/"", /*spanish*/"#reflejar la luz en la prueba de las arenas# revela"},
  });

  HintText GanonsCastle_MQ_SpiritTrialFirstChest = HintText::Exclude({
                       //obscure text
                       Text{"#reflected light in the test of the sands# reveals", /*french*/"", /*spanish*/"#reflejar la luz en la prueba de las arenas# revela"},
  });

  HintText GanonsCastle_MQ_SpiritTrialInvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"#reflected light in the test of the sands# reveals", /*french*/"", /*spanish*/"#reflejar la luz en la prueba de las arenas# revela"},
  });

  HintText GanonsCastle_MQ_ForestTrialFreestandingKey = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the wilds# holds", /*french*/"", /*spanish*/"la #prueba de la naturaleza# brinda"},
  });


  HintText DekuTree_QueenGohmaHeart = HintText::Exclude({
                       //obscure text
                       Text{"the #Parasitic Armored Arachnid# holds", /*french*/"", /*spanish*/"el #arácnido parasitario acorazado# porta"},
                     },
                       //clear text
                       Text{"#Queen Gohma# holds", /*french*/"", /*spanish*/"la #Reina Goma# porta"}
  );

  HintText DodongosCavern_KingDodongoHeart = HintText::Exclude({
                       //obscure text
                       Text{"the #Infernal Dinosaur# holds", /*french*/"", /*spanish*/"el #dinosaurio infernal# porta"},
                     },
                       //clear text
                       Text{"#King Dodongo# holds", /*french*/"", /*spanish*/"el #Rey Dodongo# porta"}
  );

  HintText JabuJabusBelly_BarinadeHeart = HintText::Exclude({
                       //obscure text
                       Text{"the #Bio-Electric Anemone# holds", /*french*/"", /*spanish*/"la #anémona bioeléctrica# porta"},
                     },
                       //clear text
                       Text{"#Barinade# holds", /*french*/"", /*spanish*/"#Barinade# porta"}
  );

  HintText ForestTemple_PhantomGanonHeart = HintText::Exclude({
                       //obscure text
                       Text{"the #Evil Spirit from Beyond# holds", /*french*/"", /*spanish*/"el #espíritu maligno de ultratumba# porta"},
                     },
                       //clear text
                       Text{"#Phantom Ganon# holds", /*french*/"", /*spanish*/"#Ganon Fantasma# porta"}
  );

  HintText FireTemple_VolvagiaHeart = HintText::Exclude({
                       //obscure text
                       Text{"the #Subterranean Lava Dragon# holds", /*french*/"", /*spanish*/"el #dragón de lava subterráneo# porta"},
                     },
                       //clear text
                       Text{"#Volvagia# holds", /*french*/"", /*spanish*/"#Volvagia# porta"}
  );

  HintText WaterTemple_MorphaHeart = HintText::Exclude({
                       //obscure text
                       Text{"the #Giant Aquatic Amoeba# holds", /*french*/"", /*spanish*/"la #ameba acuática gigante# porta"},
                     },
                       //clear text
                       Text{"#Morpha# holds", /*french*/"", /*spanish*/"#Morpha# porta"}
  );

  HintText SpiritTemple_TwinrovaHeart = HintText::Exclude({
                       //obscure text
                       Text{"the #Sorceress Sisters# hold", /*french*/"", /*spanish*/"las #hermanas hechiceras# portan"},
                     },
                       //clear text
                       Text{"#Twinrova# holds", /*french*/"", /*spanish*/"#Birova# porta"}
  );

  HintText ShadowTemple_BongoBongoHeart = HintText::Exclude({
                       //obscure text
                       Text{"the #Phantom Shadow Beast# holds", /*french*/"", /*spanish*/"la #alimaña oscura espectral# porta"},
                     },
                       //clear text
                       Text{"#Bongo Bongo# holds", /*french*/"", /*spanish*/"#Bongo Bongo# porta"}
  );


  HintText DekuTree_GS_BasementBackRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider deep within the Deku Tree# hides", /*french*/"", /*spanish*/"una #araña en las profundidades del Árbol Deku# otorga"},
  });

  HintText DekuTree_GS_BasementGate = HintText::Exclude({
                       //obscure text
                       Text{"a #web protects a spider# within the Deku Tree holding", /*french*/"", /*spanish*/"una #araña protegida por su tela# del Árbol Deku otorga"},
  });

  HintText DekuTree_GS_BasementVines = HintText::Exclude({
                       //obscure text
                       Text{"a #web protects a spider# within the Deku Tree holding", /*french*/"", /*spanish*/"una #araña protegida por su tela# del Árbol Deku otorga"},
  });

  HintText DekuTree_GS_CompassRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider atop the Deku Tree# holds", /*french*/"", /*spanish*/"una #araña en lo alto del Árbol Deku# otorga"},
  });


  HintText DekuTree_MQ_GS_Lobby = HintText::Exclude({
                       //obscure text
                       Text{"a #spider in a crate# within the Deku Tree hides", /*french*/"", /*spanish*/"una #araña bajo una caja# del Árbol Deku otorga"},
  });

  HintText DekuTree_MQ_GS_CompassRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #wall of rock protects a spider# within the Deku Tree holding", /*french*/"", /*spanish*/"una #araña protegida por una pared rocosa# del Árbol Deku otorga"},
  });

  HintText DekuTree_MQ_GS_BasementBackRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider deep within the Deku Tree# hides", /*french*/"", /*spanish*/"una #araña en las profundidades del Árbol Deku# otorga"},
  });


  HintText DodongosCavern_GS_VinesAboveStairs = HintText::Exclude({
                       //obscure text
                       Text{"a #spider entangled in vines# in Dodongo's Cavern guards", /*french*/"", /*spanish*/"una #araña sobre unas cepas# de la Cueva de los Dodongos otorga"},
  });

  HintText DodongosCavern_GS_Scarecrow = HintText::Exclude({
                       //obscure text
                       Text{"a #spider among explosive slugs# hides", /*french*/"", /*spanish*/"una #araña rodeada de explosivos gusanos# otorga"},
  });

  HintText DodongosCavern_GS_AlcoveAboveStairs = HintText::Exclude({
                       //obscure text
                       Text{"a #spider just out of reach# in Dodongo's Cavern holds", /*french*/"", /*spanish*/"una #araña fuera del alcance# de la Cueva de los Dodongos otorga"},
  });

  HintText DodongosCavern_GS_BackRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider behind a statue# in Dodongo's Cavern holds", /*french*/"", /*spanish*/"una #araña tras una estatua# de la Cueva de los Dodongos otorga"},
  });

  HintText DodongosCavern_GS_SideRoomNearLowerLizalfos = HintText::Exclude({
                       //obscure text
                       Text{"a #spider among bats# in Dodongo's Cavern holds", /*french*/"", /*spanish*/"una #araña rodeada de murciélagos# de la Cueva de los Dodongos otorga"},
  });


  HintText DodongosCavern_MQ_GS_ScrubRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider high on a wall# in Dodongo's Cavern holds", /*french*/"", /*spanish*/"una #araña en lo alto de una pared# de la Cueva de los Dodongos otorga"},
  });

  HintText DodongosCavern_MQ_GS_LizalfosRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider on top of a pillar of rock# in Dodongo's Cavern holds", /*french*/"", /*spanish*/"una #araña en lo alto de un pilar# de la Cueva de los Dodongos otorga"},
  });

  HintText DodongosCavern_MQ_GS_LarvaeRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider in a crate# in Dodongo's Cavern holds", /*french*/"", /*spanish*/"una #araña bajo una caja# de la Cueva de los Dodongos otorga"},
  });

  HintText DodongosCavern_MQ_GS_BackRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider among graves# in Dodongo's Cavern holds", /*french*/"", /*spanish*/"una #araña entre lápidas# en la Cueva de los Dodongos otorga"},
  });


  HintText JabuJabusBelly_GS_LobbyBasementLower = HintText::Exclude({
                       //obscure text
                       Text{"a #spider resting near a princess# in Jabu Jabu's Belly holds", /*french*/"", /*spanish*/"una #araña junto a una princesa# en la Tripa de Jabu Jabu otorga"},
  });

  HintText JabuJabusBelly_GS_LobbyBasementUpper = HintText::Exclude({
                       //obscure text
                       Text{"a #spider resting near a princess# in Jabu Jabu's Belly holds", /*french*/"", /*spanish*/"una #araña junto a una princesa# en la Tripa de Jabu Jabu otorga"},
  });

  HintText JabuJabusBelly_GS_NearBoss = HintText::Exclude({
                       //obscure text
                       Text{"#jellyfish surround a spider# holding", /*french*/"", /*spanish*/"una #araña rodeada de medusas# otorga"},
  });

  HintText JabuJabusBelly_GS_WaterSwitchRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider guarded by a school of stingers# in Jabu Jabu's Belly holds", /*french*/"", /*spanish*/"una #araña rodeada por un puñado de stingers# en la Tripa de Jabu Jabu otorga"},
  });


  HintText JabuJabusBelly_MQ_GS_TailPasaranRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider surrounded by electricity# in Jabu Jabu's Belly holds", /*french*/"", /*spanish*/"una #araña rodeada de electricidad# en la Tripa de Jabu Jabu otorga"},
  });

  HintText JabuJabusBelly_MQ_GS_BoomerangChestRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider guarded by a school of stingers# in Jabu Jabu's Belly holds", /*french*/"", /*spanish*/"una #araña protegida por un puñado de stingers# en la Tripa de Jabu Jabu otorga"},
  });

  HintText JabuJabusBelly_MQ_GS_NearBoss = HintText::Exclude({
                       //obscure text
                       Text{"a #spider in a web within Jabu Jabu's Belly# holds", /*french*/"", /*spanish*/"una #araña sobre una telaraña# en la Tripa de Jabu Jabu otorga"},
  });


  HintText ForestTemple_GS_RaisedIslandCourtyard = HintText::Exclude({
                       //obscure text
                       Text{"a #spider on a small island# in the Forest Temple holds", /*french*/"", /*spanish*/"una #araña sobre una pequeña isla# del Templo del Bosque otorga"},
  });

  HintText ForestTemple_GS_FirstRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider high on a wall of vines# in the Forest Temple holds", /*french*/"", /*spanish*/"una #araña en lo alto de una pared de cepas# del Templo del Bosque otorga"},
  });

  HintText ForestTemple_GS_LevelIslandCourtyard = HintText::Exclude({
                       //obscure text
                       Text{"#stone columns# lead to a spider in the Forest Temple hiding", /*french*/"", /*spanish*/"unas #columnas del Templo del Bosque# conducen a una araña que otorga"},
  });

  HintText ForestTemple_GS_Lobby = HintText::Exclude({
                       //obscure text
                       Text{"a #spider among ghosts# in the Forest Temple guards", /*french*/"", /*spanish*/"una #araña rodeada de fantasmas# del Templo del Bosque otorga"},
  });

  HintText ForestTemple_GS_Basement = HintText::Exclude({
                       //obscure text
                       Text{"a #spider within revolving walls# in the Forest Temple holds", /*french*/"", /*spanish*/"una #araña entre paredes giratorias# del Templo del Bosque otorga"},
  });


  HintText ForestTemple_MQ_GS_FirstHallway = HintText::Exclude({
                       //obscure text
                       Text{"an #ivy-hidden spider# in the Forest Temple hoards", /*french*/"", /*spanish*/"una #araña escondida entre cepas# del Templo del Bosque otorga"},
  });

  HintText ForestTemple_MQ_GS_BlockPushRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider in a hidden nook# within the Forest Temple holds", /*french*/"", /*spanish*/"una #araña en una esquina oculta# del Templo del Bosque otorga"},
  });

  HintText ForestTemple_MQ_GS_RaisedIslandCourtyard = HintText::Exclude({
                       //obscure text
                       Text{"a #spider on an arch# in the Forest Temple holds", /*french*/"", /*spanish*/"una #araña sobre un arco# del Templo del Bosque otorga"},
  });

  HintText ForestTemple_MQ_GS_LevelIslandCourtyard = HintText::Exclude({
                       //obscure text
                       Text{"a #spider on a ledge# in the Forest Temple holds", /*french*/"", /*spanish*/"una #araña en un borde# del Templo del Bosque otorga"},
  });

  HintText ForestTemple_MQ_GS_Well = HintText::Exclude({
                       //obscure text
                       Text{"#draining a well# in Forest Temple uncovers a spider with", /*french*/"", /*spanish*/"#vaciar el pozo# del Templo del Bosque desvela una araña que otorga"},
  });


  HintText FireTemple_GS_SongOfTimeRoom = HintText::Exclude({
                       //obscure text
                       Text{"#eight tiles of malice# guard a spider holding", /*french*/"", /*spanish*/"#ocho baldosas de maldad# custodian una araña que otorga"},
  });

  HintText FireTemple_GS_BossKeyLoop = HintText::Exclude({
                       //obscure text
                       Text{"#five tiles of malice# guard a spider holding", /*french*/"", /*spanish*/"#cinco baldosas de maldad# custodian una araña que otorga"},
  });

  HintText FireTemple_GS_BoulderMaze = HintText::Exclude({
                       //obscure text
                       Text{"#explosives in a maze# unveil a spider hiding", /*french*/"", /*spanish*/"los #explosivos en un laberinto# desvelan una araña que otorga"},
  });

  HintText FireTemple_GS_ScarecrowTop = HintText::Exclude({
                       //obscure text
                       Text{"a #spider-friendly scarecrow# atop a volcano hides", /*french*/"", /*spanish*/"un #espantapájaros en lo alto de un volcán# custodia una araña que otorga"},
                     },
                       //clear text
                       Text{"a #spider-friendly scarecrow# atop the Fire Temple hides", /*french*/"", /*spanish*/"un #espantapájaros del Templo del Fuego# custodia una araña que otorga"}
  );

  HintText FireTemple_GS_ScarecrowClimb = HintText::Exclude({
                       //obscure text
                       Text{"a #spider-friendly scarecrow# atop a volcano hides", /*french*/"", /*spanish*/"un #espantapájaros en lo alto de un volcán# custodia una araña que otorga"},
                     },
                       //clear text
                       Text{"a #spider-friendly scarecrow# atop the Fire Temple hides", /*french*/"", /*spanish*/"un #espantapájaros del Templo del Fuego# custodia una araña que otorga"}
  );


  HintText FireTemple_MQ_GS_AboveFireWallMaze = HintText::Exclude({
                       //obscure text
                       Text{"a #spider above a fiery maze# holds", /*french*/"", /*spanish*/"una #araña sobre un ardiente laberinto# otorga"},
  });

  HintText FireTemple_MQ_GS_FireWallMazeCenter = HintText::Exclude({
                       //obscure text
                       Text{"a #spider within a fiery maze# holds", /*french*/"", /*spanish*/"una #araña en el interior de un ardiente laberinto# otorga"},
  });

  HintText FireTemple_MQ_GS_BigLavaRoomOpenDoor = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron trapped near lava# befriended a spider with", /*french*/"", /*spanish*/"una #araña amiga de un Goron atrapado junto a la lava# otorga"},
  });

  HintText FireTemple_MQ_GS_FireWallMazeSideRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider beside a fiery maze# holds", /*french*/"", /*spanish*/"una #araña junto a un ardiente laberinto# otorga"},
  });


  HintText WaterTemple_GS_FallingPlatformRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider over a waterfall# in the Water Temple holds", /*french*/"", /*spanish*/"una #araña tras una cascada# del Templo del Agua otorga"},
  });

  HintText WaterTemple_GS_CentralPillar = HintText::Exclude({
                       //obscure text
                       Text{"a #spider in the center of the Water Temple# holds", /*french*/"", /*spanish*/"una #araña en el centro del Templo del Agua# otorga"},
  });

  HintText WaterTemple_GS_NearBossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"a spider protected by #rolling boulders under the lake# hides", /*french*/"", /*spanish*/"una #araña protegida por rocas rodantes# bajo el lago otorga"},
                     },
                       //clear text
                       Text{"a spider protected by #rolling boulders in the Water Temple# hides", /*french*/"", /*spanish*/"una #araña protegida por rocas rodantes# del Templo del Agua otorga"}
  );

  HintText WaterTemple_GS_River = HintText::Exclude({
                       //obscure text
                       Text{"a #spider over a river# in the Water Temple holds", /*french*/"", /*spanish*/"una #araña sobre un río# del Templo del Agua otorga"},
  });


  HintText WaterTemple_MQ_GS_BeforeUpperWaterSwitch = HintText::Exclude({
                       //obscure text
                       Text{"#beyond a pit of lizards# is a spider holding", /*french*/"", /*spanish*/"#más allá de un pozo de reptiles# una araña otorga"},
  });

  HintText WaterTemple_MQ_GS_LizalfosHallway = HintText::Exclude({
                       //obscure text
                       Text{"#lizards guard a spider# in the Water Temple with", /*french*/"", /*spanish*/"unos #reptiles custodian una araña# del Templo del Agua que otorga"},
  });

  HintText WaterTemple_MQ_GS_River = HintText::Exclude({
                       //obscure text
                       Text{"a #spider over a river# in the Water Temple holds", /*french*/"", /*spanish*/"una #araña sobre un río# del Templo del Agua otorga"},
  });


  HintText SpiritTemple_GS_HallAfterSunBlockRoom = HintText::Exclude({
                       //obscure text
                       Text{"a spider in the #hall of a knight# guards", /*french*/"", /*spanish*/"una #araña en el salón de un guerrero# otorga"},
  });

  HintText SpiritTemple_GS_BoulderRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider behind a temporal stone# in the Spirit Temple yields", /*french*/"", /*spanish*/"una #araña tras un bloque temporal# del Templo del Espíritu otorga"},
  });

  HintText SpiritTemple_GS_Lobby = HintText::Exclude({
                       //obscure text
                       Text{"a #spider beside a statue# holds", /*french*/"", /*spanish*/"una #araña junto a una estatua# otorga"},
  });

  HintText SpiritTemple_GS_SunOnFloorRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider at the top of a deep shaft# in the Spirit Temple holds", /*french*/"", /*spanish*/"una #araña en lo alto de un gran hueco# del Templo del Espíritu otorga"},
  });

  HintText SpiritTemple_GS_MetalFence = HintText::Exclude({
                       //obscure text
                       Text{"a child defeats a #spider among bats# in the Spirit Temple to gain", /*french*/"", /*spanish*/"el joven que derrote la #araña entre murciélagos# hallará"},
  });


  HintText SpiritTemple_MQ_GS_LeeverRoom = HintText::Exclude({
                       //obscure text
                       Text{"#above a pit of sand# in the Spirit Temple hides", /*french*/"", /*spanish*/"una #araña sobre un pozo de arena# del Templo del Espíritu otorga"},
  });

  HintText SpiritTemple_MQ_GS_NineThronesRoomWest = HintText::Exclude({
                       //obscure text
                       Text{"a spider in the #hall of a knight# guards", /*french*/"", /*spanish*/"una #araña en el salón de un guerrero# otorga"},
  });

  HintText SpiritTemple_MQ_GS_NineThronesRoomNorth = HintText::Exclude({
                       //obscure text
                       Text{"a spider in the #hall of a knight# guards", /*french*/"", /*spanish*/"una #araña en el salón de un guerrero# otorga"},
  });

  HintText SpiritTemple_MQ_GS_SunBlockRoom = HintText::Exclude({
                       //obscure text
                       Text{"#upon a web of glass# in the Spirit Temple sits a spider holding", /*french*/"", /*spanish*/"#sobre una plataforma de cristal# yace una araña que otorga"},
  });


  HintText ShadowTemple_GS_SingleGiantPot = HintText::Exclude({
                       //obscure text
                       Text{"#beyond a burning skull# lies a spider with", /*french*/"", /*spanish*/"#tras una ardiente calavera# yace una araña que otorga"},
  });

  HintText ShadowTemple_GS_FallingSpikesRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider beyond falling spikes# holds", /*french*/"", /*spanish*/"una #araña tras los pinchos del techo# otorga"},
  });

  HintText ShadowTemple_GS_TripleGiantPot = HintText::Exclude({
                       //obscure text
                       Text{"#beyond three burning skulls# lies a spider with", /*french*/"", /*spanish*/"#tras tres ardientes calaveras# yace una araña que otorga"},
  });

  HintText ShadowTemple_GS_LikeLikeRoom = HintText::Exclude({
                       //obscure text
                       Text{"a spider guarded by #invisible blades# holds", /*french*/"", /*spanish*/"una #araña custodiada por hojas invisibles# otorga"},
  });

  HintText ShadowTemple_GS_NearShip = HintText::Exclude({
                       //obscure text
                       Text{"a spider near a #docked ship# hoards", /*french*/"", /*spanish*/"una #araña cercana a un navío# otorga"},
  });


  HintText ShadowTemple_MQ_GS_FallingSpikesRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider beyond falling spikes# holds", /*french*/"", /*spanish*/"una #araña tras los pinchos del techo# otorga"},
  });

  HintText ShadowTemple_MQ_GS_WindHintRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider amidst roaring winds# in the Shadow Temple holds", /*french*/"", /*spanish*/"una #araña entre ventarrones# del Templo de las Sombras otorga"},
  });

  HintText ShadowTemple_MQ_GS_AfterWind = HintText::Exclude({
                       //obscure text
                       Text{"a #spider beneath gruesome debris# in the Shadow Temple hides", /*french*/"", /*spanish*/"una #araña bajo unos horripilantes escombros# del Templo de las Sombras otorga"},
  });

  HintText ShadowTemple_MQ_GS_AfterShip = HintText::Exclude({
                       //obscure text
                       Text{"a #fallen statue# reveals a spider with", /*french*/"", /*spanish*/"una #estatua caída# revelará una araña que otorgue"},
  });

  HintText ShadowTemple_MQ_GS_NearBoss = HintText::Exclude({
                       //obscure text
                       Text{"a #suspended spider# guards", /*french*/"", /*spanish*/"una #araña flotante# otorga"},
  });


  HintText BottomOfTheWell_GS_LikeLikeCage = HintText::Exclude({
                       //obscure text
                       Text{"a #spider locked in a cage# in the well holds", /*french*/"", /*spanish*/"una #araña enjaulada# del pozo otorga"},
  });

  HintText BottomOfTheWell_GS_EastInnerRoom = HintText::Exclude({
                       //obscure text
                       Text{"an #invisible path in the well# leads to", /*french*/"", /*spanish*/"un #camino invisible del pozo# conduce a una araña que otorga"},
  });

  HintText BottomOfTheWell_GS_WestInnerRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider locked in a crypt# within the well guards", /*french*/"", /*spanish*/"una #araña encerrada en una cripta# del pozo otorga"},
  });


  HintText BottomOfTheWell_MQ_GS_Basement = HintText::Exclude({
                       //obscure text
                       Text{"a #gauntlet of invisible spiders# protects", /*french*/"", /*spanish*/"un #puñado de arañas invisibles# custodian una que otorga"},
  });

  HintText BottomOfTheWell_MQ_GS_CoffinRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider crawling near the dead# in the well holds", /*french*/"", /*spanish*/"una #araña bajo los muertos# del pozo otorga"},
  });

  HintText BottomOfTheWell_MQ_GS_WestInnerRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider locked in a crypt# within the well guards", /*french*/"", /*spanish*/"una #araña encerrada en una cripta# del pozo otorga"},
  });


  HintText IceCavern_GS_PushBlockRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider above icy pits# holds", /*french*/"", /*spanish*/"una #araña sobre gélidos vacíos# otorga"},
  });

  HintText IceCavern_GS_SpinningScytheRoom = HintText::Exclude({
                       //obscure text
                       Text{"#spinning ice# guards a spider holding", /*french*/"", /*spanish*/"unos #témpanos giratorios# custodian una araña que otorga"},
  });

  HintText IceCavern_GS_HeartPieceRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider behind a wall of ice# hides", /*french*/"", /*spanish*/"una #araña tras una gélida pared# otorga"},
  });


  HintText IceCavern_MQ_GS_Scarecrow = HintText::Exclude({
                       //obscure text
                       Text{"a #spider above icy pits# holds", /*french*/"", /*spanish*/"una #araña sobre gélidos vacíos# otorga"},
  });

  HintText IceCavern_MQ_GS_IceBlock = HintText::Exclude({
                       //obscure text
                       Text{"a #web of ice# surrounds a spider with", /*french*/"", /*spanish*/"una #gélida telaraña# rodea a una que otorga"},
  });

  HintText IceCavern_MQ_GS_RedIce = HintText::Exclude({
                       //obscure text
                       Text{"a #spider in fiery ice# hoards", /*french*/"", /*spanish*/"una #araña de un ardiente hielo# otorga"},
  });


  HintText HF_GS_NearKakGrotto = HintText::Exclude({
                       //obscure text
                       Text{"a #spider-guarded spider in a hole# hoards", /*french*/"", /*spanish*/"una #araña custodiada por otra# de un hoyo otorga"},
  });


  HintText LLR_GS_BackWall = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider in a ranch# holding", /*french*/"", /*spanish*/"la noche revela una #araña del rancho# que otorga"},
  });

  HintText LLR_GS_RainShed = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider in a ranch# holding", /*french*/"", /*spanish*/"la noche revela una #araña del rancho# que otorga"},
  });

  HintText LLR_GS_HouseWindow = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider in a ranch# holding", /*french*/"", /*spanish*/"la noche revela una #araña del rancho# que otorga"},
  });

  HintText LLR_GS_Tree = HintText::Exclude({
                       //obscure text
                       Text{"a spider hiding in a #ranch tree# holds", /*french*/"", /*spanish*/"una araña escondida en el #árbol de un rancho# otorga"},
  });


  HintText KF_GS_BeanPatch = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried in a forest# holds", /*french*/"", /*spanish*/"una #araña enterrada en un bosque# otorga"},
  });

  HintText KF_GS_KnowItAllHouse = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a forest# holding", /*french*/"", /*spanish*/"la noche revela en el pasado una #araña del bosque# que otorga"},
  });

  HintText KF_GS_HouseOfTwins = HintText::Exclude({
                       //obscure text
                       Text{"night in the future reveals a #spider in a forest# holding", /*french*/"", /*spanish*/"la noche revela en el futuro una #araña del rancho# que otorga"},
  });


  HintText LW_GS_BeanPatchNearBridge = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried deep in a forest maze# holds", /*french*/"", /*spanish*/"una #araña enterrada en un laberinto forestal# otorga"},
  });

  HintText LW_GS_BeanPatchNearTheater = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried deep in a forest maze# holds", /*french*/"", /*spanish*/"una #araña enterrada en un laberinto forestal# otorga"},
  });

  HintText LW_GS_AboveTheater = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider deep in a forest maze# holding", /*french*/"", /*spanish*/"la noche revela una #araña del laberinto forestal# que otorga"},
  });

  HintText SFM_GS = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider in a forest meadow# holding", /*french*/"", /*spanish*/"la noche revela una #araña de la pradera del bosque# que otorga"},
  });


  HintText OGC_GS = HintText::Exclude({
                       //obscure text
                       Text{"a #spider outside a tyrant's tower# holds", /*french*/"", /*spanish*/"una #araña a las afueras de la torre de un tirano# otorga"},
  });

  HintText HC_GS_Tree = HintText::Exclude({
                       //obscure text
                       Text{"a spider hiding in a #tree outside of a castle# holds", /*french*/"", /*spanish*/"una araña escondida en el #árbol de las afueras de un castillo# otorga"},
  });

  HintText MK_GS_GuardHouse = HintText::Exclude({
                       //obscure text
                       Text{"a #spider in a guarded crate# holds", /*french*/"", /*spanish*/"una #araña bajo una custodiada caja# otorga"},
  });


  HintText DMC_GS_BeanPatch = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried in a volcano# holds", /*french*/"", /*spanish*/"una #araña enterrada en un volcán# otorga"},
  });


  HintText DMT_GS_BeanPatch = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried outside a cavern# holds", /*french*/"", /*spanish*/"una #araña enterrada a la entrada de una cueva# otorga"},
  });

  HintText DMT_GS_NearKak = HintText::Exclude({
                       //obscure text
                       Text{"a #spider hidden in a mountain nook# holds", /*french*/"", /*spanish*/"una #araña oculta en el rincón de la montaña# otorga"},
  });

  HintText DMT_GS_AboveDodongosCavern = HintText::Exclude({
                       //obscure text
                       Text{"the hammer reveals a #spider on a mountain# holding", /*french*/"", /*spanish*/"el martillo revela #una araña de la montaña# que otorga"},
  });

  HintText DMT_GS_FallingRocksPath = HintText::Exclude({
                       //obscure text
                       Text{"the hammer reveals a #spider on a mountain# holding", /*french*/"", /*spanish*/"el martillo revela #una araña de la montaña# que otorga"},
  });


  HintText GC_GS_CenterPlatform = HintText::Exclude({
                       //obscure text
                       Text{"a #suspended spider# in Goron City holds", /*french*/"", /*spanish*/"una #araña suspendida# en la Ciudad Goron otorga"},
  });

  HintText GC_GS_BoulderMaze = HintText::Exclude({
                       //obscure text
                       Text{"a spider in a #Goron City crate# holds", /*french*/"", /*spanish*/"una #araña bajo una caja# de la Ciudad Goron otorga"},
  });


  HintText Kak_GS_HouseUnderConstruction = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a town# holding", /*french*/"", /*spanish*/"la noche del pasado revela una #araña del pueblo# que otorga"},
  });

  HintText Kak_GS_SkulltulaHouse = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a town# holding", /*french*/"", /*spanish*/"la noche del pasado revela una #araña del pueblo# que otorga"},
  });

  HintText Kak_GS_GuardsHouse = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a town# holding", /*french*/"", /*spanish*/"la noche del pasado revela una #araña del pueblo# que otorga"},
  });

  HintText Kak_GS_Tree = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a town# holding", /*french*/"", /*spanish*/"la noche del pasado revela una #araña del pueblo# que otorga"},
  });

  HintText Kak_GS_Watchtower = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a town# holding", /*french*/"", /*spanish*/"la noche del pasado revela una #araña del pueblo# que otorga"},
  });

  HintText Kak_GS_AboveImpasHouse = HintText::Exclude({
                       //obscure text
                       Text{"night in the future reveals a #spider in a town# holding", /*french*/"", /*spanish*/"la noche del futuro revela una #araña del pueblo# que otorga"},
  });


  HintText GY_GS_Wall = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider in a graveyard# holding", /*french*/"", /*spanish*/"la noche revela una #araña del cementerio# que otorga"},
  });

  HintText GY_GS_BeanPatch = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried in a graveyard# holds", /*french*/"", /*spanish*/"una #araña enterrada en el cementerio# otorga"},
  });


  HintText ZR_GS_Ladder = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a river# holding", /*french*/"", /*spanish*/"la noche del pasado revela una #araña del río# que otorga"},
  });

  HintText ZR_GS_Tree = HintText::Exclude({
                       //obscure text
                       Text{"a spider hiding in a #tree by a river# holds", /*french*/"", /*spanish*/"una araña escondida en el #árbol de un río# otorga"},
  });

  HintText ZR_GS_AboveBridge = HintText::Exclude({
                       //obscure text
                       Text{"night in the future reveals a #spider in a river# holding", /*french*/"", /*spanish*/"la noche del futuro revela una #araña del río# que otorga"},
  });

  HintText ZR_GS_NearRaisedGrottos = HintText::Exclude({
                       //obscure text
                       Text{"night in the future reveals a #spider in a river# holding", /*french*/"", /*spanish*/"la noche del futuro revela una #araña del río# que otorga"},
  });


  HintText ZD_GS_FrozenWaterfall = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider by a frozen waterfall# holding", /*french*/"", /*spanish*/"la noche revela una #araña junto a una congelada cascada# que otorga"},
  });

  HintText ZF_GS_AboveTheLog = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider near a deity# holding", /*french*/"", /*spanish*/"la noche revela una #araña junto a cierta deidad# que otorga"},
  });

  HintText ZF_GS_Tree = HintText::Exclude({
                       //obscure text
                       Text{"a spider hiding in a #tree near a deity# holds", /*french*/"", /*spanish*/"una araña escondida en el #árbol junto a cierta deidad# otorga"},
  });


  HintText LH_GS_BeanPatch = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried by a lake# holds", /*french*/"", /*spanish*/"una #araña enterrada junto a un lago# otorga"},
  });

  HintText LH_GS_SmallIsland = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider by a lake# holding", /*french*/"", /*spanish*/"la noche revela una #araña junto a un lago# que otorga"},
  });

  HintText LH_GS_LabWall = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider by a lake# holding", /*french*/"", /*spanish*/"la noche revela una #araña junto a un lago# que otorga"},
  });

  HintText LH_GS_LabCrate = HintText::Exclude({
                       //obscure text
                       Text{"a spider deed underwater in a #lab crate# holds", /*french*/"", /*spanish*/"una #araña bajo la sumergida caja de un laboratorio# otorga"},
  });

  HintText LH_GS_Tree = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider by a lake high in a tree# holding", /*french*/"", /*spanish*/"la noche revela #una araña del lago sobre un árbol# que otorga"},
  });


  HintText GV_GS_BeanPatch = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried in a valley# holds", /*french*/"", /*spanish*/"una #araña enterrada en un valle# otorga"},
  });

  HintText GV_GS_SmallBridge = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a valley# holding", /*french*/"", /*spanish*/"la noche del pasado revela una #araña del valle# que otorga"},
  });

  HintText GV_GS_Pillar = HintText::Exclude({
                       //obscure text
                       Text{"night in the future reveals a #spider in a valley# holding", /*french*/"", /*spanish*/"la noche del futuro revela una #araña del valle# que otorga"},
  });

  HintText GV_GS_BehindTent = HintText::Exclude({
                       //obscure text
                       Text{"night in the future reveals a #spider in a valley# holding", /*french*/"", /*spanish*/"la noche del futuro revela una #araña del valle# que otorga"},
  });


  HintText GF_GS_ArcheryRange = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider in a fortress# holding", /*french*/"", /*spanish*/"la noche revela una #araña de una fortaleza# que otorga"},
  });

  HintText GF_GS_TopFloor = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider in a fortress# holding", /*french*/"", /*spanish*/"la noche revela una #araña de una fortaleza# que otorga"},
  });


  HintText Colossus_GS_BeanPatch = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried in the desert# holds", /*french*/"", /*spanish*/"una #enterrada en el desierto# otorga"},
  });

  HintText Colossus_GS_Hill = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider deep in the desert# holding", /*french*/"", /*spanish*/"la noche revela una #araña en las profundidades del desierto# que otorga"},
  });

  HintText Colossus_GS_Tree = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider deep in the desert# holding", /*french*/"", /*spanish*/"la noche revela una #araña en las profundidades del desierto# que otorga"},
  });


  HintText KF_ShopItem1 = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", /*french*/"", /*spanish*/"un #joven dependiente# vende"},
  });

  HintText KF_ShopItem2 = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", /*french*/"", /*spanish*/"un #joven dependiente# vende"},
  });

  HintText KF_ShopItem3 = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", /*french*/"", /*spanish*/"un #joven dependiente# vende"},
  });

  HintText KF_ShopItem4 = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", /*french*/"", /*spanish*/"un #joven dependiente# vende"},
  });

  HintText KF_ShopItem5 = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", /*french*/"", /*spanish*/"un #joven dependiente# vende"},
  });

  HintText KF_ShopItem6 = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", /*french*/"", /*spanish*/"un #joven dependiente# vende"},
  });

  HintText KF_ShopItem7 = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", /*french*/"", /*spanish*/"un #joven dependiente# vende"},
  });

  HintText KF_ShopItem8 = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", /*french*/"", /*spanish*/"un #joven dependiente# vende"},
  });


  HintText Kak_PotionShopItem1 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", /*french*/"", /*spanish*/"la #tienda de pociones de Kakariko# ofrece"}
  );

  HintText Kak_PotionShopItem2 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", /*french*/"", /*spanish*/"la #tienda de pociones de Kakariko# ofrece"}
  );

  HintText Kak_PotionShopItem3 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", /*french*/"", /*spanish*/"la #tienda de pociones de Kakariko# ofrece"}
  );

  HintText Kak_PotionShopItem4 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", /*french*/"", /*spanish*/"la #tienda de pociones de Kakariko# ofrece"}
  );

  HintText Kak_PotionShopItem5 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", /*french*/"", /*spanish*/"la #tienda de pociones de Kakariko# ofrece"}
  );

  HintText Kak_PotionShopItem6 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", /*french*/"", /*spanish*/"la #tienda de pociones de Kakariko# ofrece"}
  );

  HintText Kak_PotionShopItem7 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", /*french*/"", /*spanish*/"la #tienda de pociones de Kakariko# ofrece"}
  );

  HintText Kak_PotionShopItem8 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", /*french*/"", /*spanish*/"la #tienda de pociones de Kakariko# ofrece"}
  );


  HintText MK_BombchuShopItem1 = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", /*french*/"", /*spanish*/"un #mercader de bombchus# vende"},
  });

  HintText MK_BombchuShopItem2 = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", /*french*/"", /*spanish*/"un #mercader de bombchus# vende"},
  });

  HintText MK_BombchuShopItem3 = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", /*french*/"", /*spanish*/"un #mercader de bombchus# vende"},
  });

  HintText MK_BombchuShopItem4 = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", /*french*/"", /*spanish*/"un #mercader de bombchus# vende"},
  });

  HintText MK_BombchuShopItem5 = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", /*french*/"", /*spanish*/"un #mercader de bombchus# vende"},
  });

  HintText MK_BombchuShopItem6 = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", /*french*/"", /*spanish*/"un #mercader de bombchus# vende"},
  });

  HintText MK_BombchuShopItem7 = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", /*french*/"", /*spanish*/"un #mercader de bombchus# vende"},
  });

  HintText MK_BombchuShopItem8 = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", /*french*/"", /*spanish*/"un #mercader de bombchus# vende"},
  });


  HintText MK_PotionShopItem1 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", /*french*/"", /*spanish*/"la #tienda de pociones del mercado# ofrece"}
  );

  HintText MK_PotionShopItem2 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", /*french*/"", /*spanish*/"la #tienda de pociones del mercado# ofrece"}
  );

  HintText MK_PotionShopItem3 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", /*french*/"", /*spanish*/"la #tienda de pociones del mercado# ofrece"}
  );

  HintText MK_PotionShopItem4 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", /*french*/"", /*spanish*/"la #tienda de pociones del mercado# ofrece"}
  );

  HintText MK_PotionShopItem5 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", /*french*/"", /*spanish*/"la #tienda de pociones del mercado# ofrece"}
  );

  HintText MK_PotionShopItem6 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", /*french*/"", /*spanish*/"la #tienda de pociones del mercado# ofrece"}
  );

  HintText MK_PotionShopItem7 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", /*french*/"", /*spanish*/"la #tienda de pociones del mercado# ofrece"}
  );

  HintText MK_PotionShopItem8 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", /*french*/"", /*spanish*/"la #tienda de pociones del mercado# ofrece"}
  );


  HintText MK_BazaarItem1 = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", /*french*/"", /*spanish*/"el #bazar del mercado# ofrece"},
  });

  HintText MK_BazaarItem2 = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", /*french*/"", /*spanish*/"el #bazar del mercado# ofrece"},
  });

  HintText MK_BazaarItem3 = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", /*french*/"", /*spanish*/"el #bazar del mercado# ofrece"},
  });

  HintText MK_BazaarItem4 = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", /*french*/"", /*spanish*/"el #bazar del mercado# ofrece"},
  });

  HintText MK_BazaarItem5 = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", /*french*/"", /*spanish*/"el #bazar del mercado# ofrece"},
  });

  HintText MK_BazaarItem6 = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", /*french*/"", /*spanish*/"el #bazar del mercado# ofrece"},
  });

  HintText MK_BazaarItem7 = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", /*french*/"", /*spanish*/"el #bazar del mercado# ofrece"},
  });

  HintText MK_BazaarItem8 = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", /*french*/"", /*spanish*/"el #bazar del mercado# ofrece"},
  });


  HintText Kak_BazaarItem1 = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", /*french*/"", /*spanish*/"el #bazar de Kakariko# ofrece"},
  });

  HintText Kak_BazaarItem2 = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", /*french*/"", /*spanish*/"el #bazar de Kakariko# ofrece"},
  });

  HintText Kak_BazaarItem3 = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", /*french*/"", /*spanish*/"el #bazar de Kakariko# ofrece"},
  });

  HintText Kak_BazaarItem4 = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", /*french*/"", /*spanish*/"el #bazar de Kakariko# ofrece"},
  });

  HintText Kak_BazaarItem5 = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", /*french*/"", /*spanish*/"el #bazar de Kakariko# ofrece"},
  });

  HintText Kak_BazaarItem6 = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", /*french*/"", /*spanish*/"el #bazar de Kakariko# ofrece"},
  });

  HintText Kak_BazaarItem7 = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", /*french*/"", /*spanish*/"el #bazar de Kakariko# ofrece"},
  });

  HintText Kak_BazaarItem8 = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", /*french*/"", /*spanish*/"el #bazar de Kakariko# ofrece"},
  });


  HintText ZD_ShopItem1 = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", /*french*/"", /*spanish*/"el #dependiente zora# vende"},
  });

  HintText ZD_ShopItem2 = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", /*french*/"", /*spanish*/"el #dependiente zora# vende"},
  });

  HintText ZD_ShopItem3 = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", /*french*/"", /*spanish*/"el #dependiente zora# vende"},
  });

  HintText ZD_ShopItem4 = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", /*french*/"", /*spanish*/"el #dependiente zora# vende"},
  });

  HintText ZD_ShopItem5 = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", /*french*/"", /*spanish*/"el #dependiente zora# vende"},
  });

  HintText ZD_ShopItem6 = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", /*french*/"", /*spanish*/"el #dependiente zora# vende"},
  });

  HintText ZD_ShopItem7 = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", /*french*/"", /*spanish*/"el #dependiente zora# vende"},
  });

  HintText ZD_ShopItem8 = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", /*french*/"", /*spanish*/"el #dependiente zora# vende"},
  });


  HintText GC_ShopItem1 = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", /*french*/"", /*spanish*/"el #dependiente goron# vende"},
  });

  HintText GC_ShopItem2 = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", /*french*/"", /*spanish*/"el #dependiente goron# vende"},
  });

  HintText GC_ShopItem3 = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", /*french*/"", /*spanish*/"el #dependiente goron# vende"},
  });

  HintText GC_ShopItem4 = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", /*french*/"", /*spanish*/"el #dependiente goron# vende"},
  });

  HintText GC_ShopItem5 = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", /*french*/"", /*spanish*/"el #dependiente goron# vende"},
  });

  HintText GC_ShopItem6 = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", /*french*/"", /*spanish*/"el #dependiente goron# vende"},
  });

  HintText GC_ShopItem7 = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", /*french*/"", /*spanish*/"el #dependiente goron# vende"},
  });

  HintText GC_ShopItem8 = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", /*french*/"", /*spanish*/"el #dependiente goron# vende"},
  });


  HintText DekuTree_MQ_DekuScrub = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub in the Deku Tree# sells", /*french*/"", /*spanish*/"un #deku del Árbol Deku# vende"},
  });


  HintText HF_DekuScrubGrotto = HintText::Exclude({
                       //obscure text
                       Text{"a lonely #scrub in a hole# sells", /*french*/"", /*spanish*/"un #singular deku bajo un hoyo# vende"},
  });

  HintText LLR_DekuScrubGrottoLeft = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"", /*spanish*/"un #trío de dekus# vende"},
  });

  HintText LLR_DekuScrubGrottoRight = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"", /*spanish*/"un #trío de dekus# vende"},
  });

  HintText LLR_DekuScrubGrottoCenter = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"", /*spanish*/"un #trío de dekus# vende"},
  });


  HintText LW_DekuScrubNearDekuTheaterRight = HintText::Exclude({
                       //obscure text
                       Text{"a pair of #scrubs in the woods# sells", /*french*/"", /*spanish*/"un par de #dekus del bosque# vende"},
  });

  HintText LW_DekuScrubNearDekuTheaterLeft = HintText::Exclude({
                       //obscure text
                       Text{"a pair of #scrubs in the woods# sells", /*french*/"", /*spanish*/"un par de #dekus del bosque# vende"},
  });

  HintText LW_DekuScrubNearBridge = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub by a bridge# sells", /*french*/"", /*spanish*/"un #deku bajo un puente# vende"},
  });

  HintText LW_DekuScrubGrottoRear = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"", /*spanish*/"un #par de dekus subterráneos# vende"},
  });

  HintText LW_DekuScrubGrottoFront = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"", /*spanish*/"un #par de dekus subterráneos# vende"},
  });


  HintText SFM_DekuScrubGrottoRear = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"", /*spanish*/"un #par de dekus subterráneos# vende"},
  });

  HintText SFM_DekuScrubGrottoFront = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"", /*spanish*/"un #par de dekus subterráneos# vende"},
  });


  HintText GC_DekuScrubGrottoLeft = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"", /*spanish*/"un #trío de dekus# vende"},
  });

  HintText GC_DekuScrubGrottoRight = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"", /*spanish*/"un #trío de dekus# vende"},
  });

  HintText GC_DekuScrubGrottoCenter = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"", /*spanish*/"un #trío de dekus# vende"},
  });


  HintText DodongosCavern_DekuScrubNearBombBagLeft = HintText::Exclude({
                       //obscure text
                       Text{"a pair of #scrubs in Dodongo's Cavern# sells", /*french*/"", /*spanish*/"un #par de dekus en la Cueva de los Dodongos# vende"},
  });

  HintText DodongosCavern_DekuScrubSideRoomNearDodongos = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub guarded by Lizalfos# sells", /*french*/"", /*spanish*/"un #deku custodiado por Lizalfos# vende"},
  });

  HintText DodongosCavern_DekuScrubNearBombBagRight = HintText::Exclude({
                       //obscure text
                       Text{"a pair of #scrubs in Dodongo's Cavern# sells", /*french*/"", /*spanish*/"un #par de dekus en la Cueva de los Dodongos# vende"},
  });

  HintText DodongosCavern_DekuScrubLobby = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub in Dodongo's Cavern# sells", /*french*/"", /*spanish*/"un #deku en la Cueva de los Dodongos# vende"},
  });


  HintText DodongosCavern_MQ_DekuScrubLobbyRear = HintText::Exclude({
                       //obscure text
                       Text{"a pair of #scrubs in Dodongo's Cavern# sells", /*french*/"", /*spanish*/"un #par de dekus en la Cueva de los Dodongos# vende"},
  });

  HintText DodongosCavern_MQ_DekuScrubLobbyFront = HintText::Exclude({
                       //obscure text
                       Text{"a pair of #scrubs in Dodongo's Cavern# sells", /*french*/"", /*spanish*/"un #par de dekus en la Cueva de los Dodongos# vende"},
  });

  HintText DodongosCavern_MQ_DekuScrubStaircase = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub in Dodongo's Cavern# sells", /*french*/"", /*spanish*/"un #deku en la Cueva de los Dodongos# vende"},
  });

  HintText DodongosCavern_MQ_DekuScrubSideRoomNearLowerLizalfos = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub guarded by Lizalfos# sells", /*french*/"", /*spanish*/"un #deku custodiado por Lizalfos# vende"},
  });


  HintText DMC_DekuScrubGrottoLeft = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"", /*spanish*/"un #trío de dekus# vende"},
  });

  HintText DMC_DekuScrubGrottoRight = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"", /*spanish*/"un #trío de dekus# vende"},
  });

  HintText DMC_DekuScrubGrottoCenter = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"", /*spanish*/"un #trío de dekus# vende"},
  });


  HintText ZR_DekuScrubGrottoRear = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"", /*spanish*/"un #par de dekus subterráneos# vende"},
  });

  HintText ZR_DekuScrubGrottoFront = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"", /*spanish*/"un #par de dekus subterráneos# vende"},
  });


  HintText JabuJabusBelly_DekuScrub = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub in a deity# sells", /*french*/"", /*spanish*/"un #deku dentro de cierta deidad# vende"},
  });


  HintText LH_DekuScrubGrottoLeft = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"", /*spanish*/"un #trío de dekus# vende"},
  });

  HintText LH_DekuScrubGrottoRight = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"", /*spanish*/"un #trío de dekus# vende"},
  });

  HintText LH_DekuScrubGrottoCenter = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"", /*spanish*/"un #trío de dekus# vende"},
  });


  HintText GV_DekuScrubGrottoRear = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"", /*spanish*/"un #par de dekus subterráneos# vende"},
  });

  HintText GV_DekuScrubGrottoFront = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"", /*spanish*/"un #par de dekus subterráneos# vende"},
  });


  HintText Colossus_DekuScrubGrottoFront = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"", /*spanish*/"un #par de dekus subterráneos# vende"},
  });

  HintText Colossus_DekuScrubGrottoRear = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"", /*spanish*/"un #par de dekus subterráneos# vende"},
  });


  HintText GanonsCastle_DekuScrubCenterLeft = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", /*french*/"", /*spanish*/"los #dekus del Castillo de Ganondorf# venden"},
  });

  HintText GanonsCastle_DekuScrubCenterRight = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", /*french*/"", /*spanish*/"los #dekus del Castillo de Ganondorf# venden"},
  });

  HintText GanonsCastle_DekuScrubRight = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", /*french*/"", /*spanish*/"los #dekus del Castillo de Ganondorf# venden"},
  });

  HintText GanonsCastle_DekuScrubLeft = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", /*french*/"", /*spanish*/"los #dekus del Castillo de Ganondorf# venden"},
  });


  HintText GanonsCastle_MQ_DekuScrubRight = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", /*french*/"", /*spanish*/"los #dekus del Castillo de Ganondorf# venden"},
  });

  HintText GanonsCastle_MQ_DekuScrubCenterLeft = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", /*french*/"", /*spanish*/"los #dekus del Castillo de Ganondorf# venden"},
  });

  HintText GanonsCastle_MQ_DekuScrubCenter = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", /*french*/"", /*spanish*/"los #dekus del Castillo de Ganondorf# venden"},
  });

  HintText GanonsCastle_MQ_DekuScrubCenterRight = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", /*french*/"", /*spanish*/"los #dekus del Castillo de Ganondorf# venden"},
  });

  HintText GanonsCastle_MQ_DekuScrubLeft = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", /*french*/"", /*spanish*/"los #dekus del Castillo de Ganondorf# venden"},
  });


  HintText LLR_StablesLeftCow = HintText::Exclude({
                       //obscure text
                       Text{"a #cow in a stable# gifts", /*french*/"", /*spanish*/"una #vaca del establo# brinda"},
  });

  HintText LLR_StablesRightCow = HintText::Exclude({
                       //obscure text
                       Text{"a #cow in a stable# gifts", /*french*/"", /*spanish*/"una #vaca del establo# brinda"},
  });

  HintText LLR_TowerRightCow = HintText::Exclude({
                       //obscure text
                       Text{"a #cow in a ranch silo# gifts", /*french*/"", /*spanish*/"una #vaca del granero# brinda"},
  });

  HintText LLR_TowerLeftCow = HintText::Exclude({
                       //obscure text
                       Text{"a #cow in a ranch silo# gifts", /*french*/"", /*spanish*/"una #vaca del granero# brinda"},
  });

  HintText Kak_ImpasHouseCow = HintText::Exclude({
                       //obscure text
                       Text{"a #cow imprisoned in a house# protects", /*french*/"", /*spanish*/"una #vaca enjaulada de una casa# brinda"},
  });

  HintText DMT_CowGrottoCow = HintText::Exclude({
                       //obscure text
                       Text{"a #cow in a luxurious hole# offers", /*french*/"", /*spanish*/"una #vaca de un lujoso hoyo# brinda"},
  });

  /*--------------------------
  |    ENTRANCE HINT TEXT    |
  ---------------------------*/

  HintText DesertColossus_To_ColossusGrotto = HintText::Entrance({
                     //obscure text
                     Text{"lifting a #rock in the desert# reveals", /*french*/"", /*spanish*/"levantar una #roca del desierto# revela"},
  });

  HintText GVGrottoLedge_To_GVOctorokGrotto = HintText::Entrance({
                     //obscure text
                     Text{"a rock on #a ledge in the valley# hides", /*french*/"", /*spanish*/"levantar una #roca al borde del valle# esconde"},
  });

  HintText GCGrottoPlatform_To_GCGrotto = HintText::Entrance({
                     //obscure text
                     Text{"a #pool of lava# in Goron City blocks the way to", /*french*/"", /*spanish*/"un #estanque de lava# en la Ciudad Goron bloquea el paso a"},
  });

  HintText GerudoFortress_To_GFStormsGrotto = HintText::Entrance({
                     //obscure text
                     Text{"a #storm within Gerudo's Fortress# reveals", /*french*/"", /*spanish*/"una #tormenta en la Fortaleza Gerudo# revela"},
  });

  HintText ZorasDomain_To_ZDStormsGrotto = HintText::Entrance({
                     //obscure text
                     Text{"a #storm within Zora's Domain# reveals", /*french*/"", /*spanish*/"una #tormenta en la Región de los Zora# revela"},
  });

  HintText HyruleCastleGrounds_To_HCStormsGrotto = HintText::Entrance({
                     //obscure text
                     Text{"a #storm near the castle# reveals", /*french*/"", /*spanish*/"una #tormenta junto al castillo# revela"},
  });

  HintText GVFortressSide_To_GVStormsGrotto = HintText::Entrance({
                     //obscure text
                     Text{"a #storm in the valley# reveals", /*french*/"", /*spanish*/"una #tormenta en el valle# revela"},
  });

  HintText DesertColossus_To_ColossusGreatFairyFountain = HintText::Entrance({
                     //obscure text
                     Text{"a #fractured desert wall# hides", /*french*/"", /*spanish*/"una #agrietada pared del desierto# esconde"},
  });

  HintText GanonsCastleGrounds_To_OGCGreatFairyFountain = HintText::Entrance({
                     //obscure text
                     Text{"a #heavy pillar# outside the castle obstructs", /*french*/"", /*spanish*/"una #pesada columna# fuera del castillo obstruye"},
  });

  HintText ZorasFountain_To_ZFGreatFairyFountain = HintText::Entrance({
                     //obscure text
                     Text{"a #fountain wall# hides", /*french*/"", /*spanish*/"una #pared de la fuente# esconde"},
  });

  HintText GVFortressSide_To_GVCarpenterTent = HintText::Entrance({
                     //obscure text
                     Text{"a #tent in the valley# covers", /*french*/"", /*spanish*/"una #tienda de campaña del valle# cubre"},
  });

  HintText GYWarpPadRegion_To_ShadowTempleEntryway = HintText::Entrance({
                     //obscure text
                     Text{"at the #back of the Graveyard#, there is", /*french*/"", /*spanish*/"en la #parte trasera del cementerio# se halla"},
  });

  HintText LakeHylia_To_WaterTempleLobby = HintText::Entrance({
                     //obscure text
                     Text{"deep #under a vast lake#, one can find", /*french*/"", /*spanish*/"en las #profundidades de un lago inmenso# se halla"},
  });

  HintText GerudoFortress_To_GerudoTrainingGroundsLobby = HintText::Entrance({
                     //obscure text
                     Text{"paying a #fee to the Gerudos# grants access to", /*french*/"", /*spanish*/"pagarle una #tasa a las gerudo# da acceso a"},
  });

  HintText ZorasFountain_To_JabuJabusBellyBeginning = HintText::Entrance({
                     //obscure text
                     Text{"inside #Jabu Jabu#, one can find", /*french*/"", /*spanish*/"dentro de #Jabu Jabu# se halla"},
  });

  HintText KakarikoVillage_To_BottomOfTheWell = HintText::Entrance({
                     //obscure text
                     Text{"a #village well# leads to", /*french*/"", /*spanish*/"el #pozo de un pueblo# conduce a"},
  });

  /*--------------------------
  |      EXIT HINT TEXT      |
  ---------------------------*/
  //maybe make a new type for this? I'm not sure if it really matters

  HintText LinksPocket = HintText::Exclude({
                     //obscure text
                     Text{"Link's Pocket", /*french*/"", /*spanish*/"el bolsillo de Link"},
  });

  HintText KokiriForest = HintText::Exclude({
                     //obscure text
                     Text{"Kokiri Forest", /*french*/"", /*spanish*/"el Bosque Kokiri"},
  });

  HintText TheLostWoods = HintText::Exclude({
                     //obscure text
                     Text{"the Lost Woods", /*french*/"", /*spanish*/"el Bosque Perdido"},
  });

  HintText SacredForestMeadow = HintText::Exclude({
                     //obscure text
                     Text{"Sacred Forest Meadow", /*french*/"", /*spanish*/"la pradera sagrada del bosque"},
  });

  HintText HyruleField = HintText::Exclude({
                     //obscure text
                     Text{"Hyrule Field", /*french*/"", /*spanish*/"en la Llanura de Hyrule"},
  });

  HintText LakeHylia = HintText::Exclude({
                     //obscure text
                     Text{"Lake Hylia", /*french*/"", /*spanish*/"el Lago Hylia"},
  });

  HintText GerudoValley = HintText::Exclude({
                     //obscure text
                     Text{"Gerudo Valley", /*french*/"", /*spanish*/"el Valle Gerudo"},
  });

  HintText GerudosFortress = HintText::Exclude({
                     //obscure text
                     Text{"Gerudo's Fortress", /*french*/"", /*spanish*/"la fortaleza gerudo"},
  });

  HintText HauntedWasteland = HintText::Exclude({
                     //obscure text
                     Text{"Haunted Wasteland", /*french*/"", /*spanish*/"el desierto encantado"},
  });

  HintText DesertColossus = HintText::Exclude({
                     //obscure text
                     Text{"Desert Colossus", /*french*/"", /*spanish*/"el Coloso del Desierto"},
  });

  HintText TheMarket = HintText::Exclude({
                     //obscure text
                     Text{"the Market", /*french*/"", /*spanish*/"la plaza del mercado"},
  });

  HintText TempleOfTime = HintText::Exclude({
                     //obscure text
                     Text{"Temple of Time", /*french*/"", /*spanish*/"el Templo del Tiempo"},
  });

  HintText HyruleCastle = HintText::Exclude({
                     //obscure text
                     Text{"Hyrule Castle", /*french*/"", /*spanish*/"el Castillo de Hyrule"},
  });

  HintText OutsideGanonsCastle = HintText::Exclude({
                     //obscure text
                     Text{"outside Ganon's Castle", /*french*/"", /*spanish*/"las afueras del Castillo de Ganon"},
  });

  HintText KakarikoVillage = HintText::Exclude({
                     //obscure text
                     Text{"Kakariko Village", /*french*/"", /*spanish*/"Kakariko"},
  });

  HintText TheGraveyard = HintText::Exclude({
                     //obscure text
                     Text{"the Graveyard", /*french*/"", /*spanish*/"el cementerio"},
  });

  HintText DeathMountainTrail = HintText::Exclude({
                     //obscure text
                     Text{"Death Mountain Trail", /*french*/"", /*spanish*/"el sendero de la Montaña de la Muerte"},
  });

  HintText GoronCity = HintText::Exclude({
                     //obscure text
                     Text{"Goron City", /*french*/"", /*spanish*/"la Ciudad Goron"},
  });

  HintText DeathMountainCrater = HintText::Exclude({
                     //obscure text
                     Text{"Death Mountain Crater", /*french*/"", /*spanish*/"el cráter de la Montaña de la Muerte"},
  });

  HintText ZorasRiver = HintText::Exclude({
                     //obscure text
                     Text{"Zora's River", /*french*/"", /*spanish*/"el Río Zora"},
  });

  HintText ZorasDomain = HintText::Exclude({
                     //obscure text
                     Text{"Zora's Domain", /*french*/"", /*spanish*/"la Región de los Zora"},
  });

  HintText ZorasFountain = HintText::Exclude({
                     //obscure text
                     Text{"Zora's Fountain", /*french*/"", /*spanish*/"la Fuente Zora"},
  });

  HintText LonLonRanch = HintText::Exclude({
                     //obscure text
                     Text{"Lon Lon Ranch", /*french*/"", /*spanish*/"el Rancho Lon Lon"},
  });


  /*--------------------------
  |     REGION HINT TEXT     |
  ---------------------------*/

  HintText KF_LinksHouse = HintText::Region({
                     //obscure text
                     Text{"Link's House", /*french*/"", /*spanish*/"la casa de Link"},
  });

  HintText ToT_Main = HintText::Region({
                     //obscure text
                     Text{"the #Temple of Time#", /*french*/"", /*spanish*/"el Templo del Tiempo"},
  });

  HintText KF_MidosHouse = HintText::Region({
                     //obscure text
                     Text{"Mido's house", /*french*/"", /*spanish*/"la casa de Mido"},
  });

  HintText KF_SariasHouse = HintText::Region({
                     //obscure text
                     Text{"Saria's House", /*french*/"", /*spanish*/"la casa de Saria"},
  });

  HintText KF_HouseOfTwins = HintText::Region({
                     //obscure text
                     Text{"the #House of Twins#", /*french*/"", /*spanish*/"la casa de las gemelas"},
  });

  HintText KF_KnowItAllHouse = HintText::Region({
                     //obscure text
                     Text{"Know-It-All Brothers' House", /*french*/"", /*spanish*/"la casa de los hermanos Sabelotodo"},
  });

  HintText KF_KokiriShop = HintText::Region({
                     //obscure text
                     Text{"the #Kokiri Shop#", /*french*/"", /*spanish*/"la Tienda Kokiri"},
  });

  HintText LH_Lab = HintText::Region({
                     //obscure text
                     Text{"the #Lakeside Laboratory#", /*french*/"", /*spanish*/"el laboratorio del lago"},
  });

  HintText LH_FishingHole = HintText::Region({
                     //obscure text
                     Text{"the #Fishing Pond#", /*french*/"", /*spanish*/"el estanque"},
  });

  HintText GV_CarpenterTent = HintText::Region({
                     //obscure text
                     Text{"the #Carpenters' tent#", /*french*/"", /*spanish*/"la #tienda de campaña de los carpinteros#"},
  });

  HintText MK_GuardHouse = HintText::Region({
                     //obscure text
                     Text{"the #Guard House#", /*french*/"", /*spanish*/"la caseta de guardia"},
  });

  HintText MK_MaskShop = HintText::Region({
                     //obscure text
                     Text{"the #Happy Mask Shop#", /*french*/"", /*spanish*/"la Tienda de La Máscara Feliz"},
  });

  HintText MK_BombchuBowling = HintText::Region({
                     //obscure text
                     Text{"the #Bombchu Bowling Alley#", /*french*/"", /*spanish*/"la Bolera Bombchu"},
  });

  HintText MK_PotionShop = HintText::Region({
                     //obscure text
                     Text{"the #Market Potion Shop#", /*french*/"", /*spanish*/"la tienda de pociones de la plaza del mercado"},
  });

  HintText MK_TreasureChestGame = HintText::Region({
                     //obscure text
                     Text{"the #Treasure Box Shop#", /*french*/"", /*spanish*/"el Cofre del Tesoro"},
  });

  HintText MK_BombchuShop = HintText::Region({
                     //obscure text
                     Text{"the #Bombchu Shop#", /*french*/"", /*spanish*/"la Tienda Bombchu"},
  });

  HintText MK_ManInGreenHouse = HintText::Region({
                     //obscure text
                     Text{"Man in Green's House", /*french*/"", /*spanish*/"la casa del hombre de verde"},
  });

  HintText Kak_Windmill = HintText::Region({
                     //obscure text
                     Text{"the #Windmill#", /*french*/"", /*spanish*/"el #molino#"},
  });

  HintText Kak_CarpenterBossHouse = HintText::Region({
                     //obscure text
                     Text{"the #Carpenters' Boss House#", /*french*/"", /*spanish*/"la casa del capataz de los carpinteros"},
  });

  HintText Kak_HouseOfSkulltula = HintText::Region({
                     //obscure text
                     Text{"the #House of Skulltula#", /*french*/"", /*spanish*/"la casa de las skulltulas"},
  });

  HintText Kak_ImpasHouse = HintText::Region({
                     //obscure text
                     Text{"Impa's House", /*french*/"", /*spanish*/"la casa de Impa"},
  });

  HintText Kak_ImpasHouseBack = HintText::Region({
                     //obscure text
                     Text{"Impa's cow cage", /*french*/"", /*spanish*/"la jaula de la vaca de Impa"},
  });

  HintText Kak_OddMedicineBuilding = HintText::Region({
                     //obscure text
                     Text{"Granny's Potion Shop", /*french*/"", /*spanish*/"la tienda de pociones de la abuela"},
  });

  HintText GY_DampesHouse = HintText::Region({
                     //obscure text
                     Text{"Dampé's Hut", /*french*/"", /*spanish*/"la cabaña de Dampé"},
  });

  HintText GC_Shop = HintText::Region({
                     //obscure text
                     Text{"the #Goron Shop#", /*french*/"", /*spanish*/"la #tienda goron"},
  });

  HintText ZD_Shop = HintText::Region({
                     //obscure text
                     Text{"the #Zora Shop#", /*french*/"", /*spanish*/"la #tienda zora"},
  });

  HintText LLR_TalonsHouse = HintText::Region({
                     //obscure text
                     Text{"Talon's House", /*french*/"", /*spanish*/"la casa de Talon"},
  });

  HintText LLR_Stables = HintText::Region({
                     //obscure text
                     Text{"a #stable#", /*french*/"", /*spanish*/"el establo"},
  });

  HintText LLR_Tower = HintText::Region({
                     //obscure text
                     Text{"the #Lon Lon Tower#", /*french*/"", /*spanish*/"la torre Lon Lon"},
  });

  HintText MK_Bazaar = HintText::Region({
                     //obscure text
                     Text{"the #Market Bazaar#", /*french*/"", /*spanish*/"el bazar de la plaza del mercado"},
  });

  HintText MK_ShootingGallery = HintText::Region({
                     //obscure text
                     Text{"a #Slingshot Shooting Gallery#", /*french*/"", /*spanish*/"el Tiro al Blanco con tirachinas"},
  });

  HintText Kak_Bazaar = HintText::Region({
                     //obscure text
                     Text{"the #Kakariko Bazaar#", /*french*/"", /*spanish*/"el bazar de Kakariko"},
  });

  HintText Kak_PotionShopFront = HintText::Region({
                     //obscure text
                     Text{"the #Kakariko Potion Shop#", /*french*/"", /*spanish*/"la tienda de pociones de Kakariko"},
  });

  HintText Kak_PotionShopBack = HintText::Region({
                     //obscure text
                     Text{"the #Kakariko Potion Shop#", /*french*/"", /*spanish*/"la tienda de pociones de Kakariko"},
  });

  HintText Kak_ShootingGallery = HintText::Region({
                     //obscure text
                     Text{"a #Bow Shooting Gallery#", /*french*/"", /*spanish*/"el Tiro al Blanco con arco"},
  });

  HintText Colossus_GreatFairyFountain = HintText::Region({
                     //obscure text
                     Text{"a #Great Fairy Fountain#", /*french*/"", /*spanish*/"una fuente de la Gran Hada"},
  });

  HintText HC_GreatFairyFountain = HintText::Region({
                     //obscure text
                     Text{"a #Great Fairy Fountain#", /*french*/"", /*spanish*/"una fuente de la Gran Hada"},
  });

  HintText OGC_GreatFairyFountain = HintText::Region({
                     //obscure text
                     Text{"a #Great Fairy Fountain#", /*french*/"", /*spanish*/"una fuente de la Gran Hada"},
  });

  HintText DMC_GreatFairyFountain = HintText::Region({
                     //obscure text
                     Text{"a #Great Fairy Fountain#", /*french*/"", /*spanish*/"una fuente de la Gran Hada"},
  });

  HintText DMT_GreatFairyFountain = HintText::Region({
                     //obscure text
                     Text{"a #Great Fairy Fountain#", /*french*/"", /*spanish*/"una fuente de la Gran Hada"},
  });

  HintText ZF_GreatFairyFountain = HintText::Region({
                     //obscure text
                     Text{"a #Great Fairy Fountain#", /*french*/"", /*spanish*/"una fuente de la Gran Hada"},
  });

  HintText GY_ShieldGrave = HintText::Region({
                     //obscure text
                     Text{"a #grave with a free chest#", /*french*/"", /*spanish*/"la #tumba del cofre gratis#"},
  });

  HintText GY_HeartPieceGrave = HintText::Region({
                     //obscure text
                     Text{"a chest spawned by #Sun's Song#", /*french*/"", /*spanish*/"la #tumba de la Canción del Sol#"},
  });

  HintText GY_ComposersGrave = HintText::Region({
                     //obscure text
                     Text{"the #Composers' Grave#", /*french*/"", /*spanish*/"el #Panteón Real#"},
  });

  HintText GY_DampesGrave = HintText::Region({
                     //obscure text
                     Text{"Dampé's Grave", /*french*/"", /*spanish*/"la #tumba de Dampé"},
  });

  HintText DMT_CowGrotto = HintText::Region({
                     //obscure text
                     Text{"a solitary #Cow#", /*french*/"", /*spanish*/"una #vaca# solitaria"},
  });

  HintText HC_StormsGrotto = HintText::Region({
                     //obscure text
                     Text{"a sandy grotto with #fragile walls#", /*french*/"", /*spanish*/"la arenosa gruta de #frágiles paredes#"},
  });

  HintText HF_TektiteGrotto = HintText::Region({
                     //obscure text
                     Text{"a pool guarded by a #Tektite#", /*french*/"", /*spanish*/"un charco custodiado por un #Tektite#"},
  });

  HintText HF_NearKakGrotto = HintText::Region({
                     //obscure text
                     Text{"a #Big Skulltula# guarding a Gold one", /*french*/"", /*spanish*/"un #skulltula# custodiando una dorada"},
  });

  HintText HF_CowGrotto = HintText::Region({
                     //obscure text
                     Text{"a grotto full of #spider webs#", /*french*/"", /*spanish*/"una gruta llena de #telarañas#"},
  });

  HintText Kak_RedeadGrotto = HintText::Region({
                     //obscure text
                     Text{"#ReDeads# guarding a chest", /*french*/"", /*spanish*/"los #ReDeads# que custodian un cofre"},
  });

  HintText SFM_WolfosGrotto = HintText::Region({
                     //obscure text
                     Text{"#Wolfos# guarding a chest", /*french*/"", /*spanish*/"los #Wolfos# que custodian un cofre"},
  });

  HintText GV_OctorokGrotto = HintText::Region({
                     //obscure text
                     Text{"an #Octorok# guarding a rich pool", /*french*/"", /*spanish*/"un #Octorok# que custodia un lujoso charco"},
  });

  HintText DekuTheater = HintText::Region({
                     //obscure text
                     Text{"the #Lost Woods Stage#", /*french*/"", /*spanish*/"el #escenario del Bosque Perdido#"},
  });

  HintText ZR_OpenGrotto = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", /*french*/"", /*spanish*/"una #gruta genérica#"},
  });

  HintText DMC_UpperGrotto = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", /*french*/"", /*spanish*/"una #gruta genérica#"},
  });

  HintText DMT_StormsGrotto = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", /*french*/"", /*spanish*/"una #gruta genérica#"},
  });

  HintText Kak_OpenGrotto = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", /*french*/"", /*spanish*/"una #gruta genérica#"},
  });

  HintText HF_NearMKGrotto = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", /*french*/"", /*spanish*/"una #gruta genérica#"},
  });

  HintText HF_OpenGrotto = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", /*french*/"", /*spanish*/"una #gruta genérica#"},
  });

  HintText HF_SoutheastGrotto = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", /*french*/"", /*spanish*/"una #gruta genérica#"},
  });

  HintText KF_StormsGrotto = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", /*french*/"", /*spanish*/"una #gruta genérica#"},
  });

  HintText LW_NearShortcutsGrotto = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", /*french*/"", /*spanish*/"una #gruta genérica#"},
  });

  HintText HF_InsideFenceGrotto = HintText::Region({
                     //obscure text
                     Text{"a #single Upgrade Deku Scrub#", /*french*/"", /*spanish*/"un #solitario mercader deku de mejora#"},
  });

  HintText LW_ScrubsGrotto = HintText::Region({
                     //obscure text
                     Text{"#2 Deku Scrubs# including an Upgrade one", /*french*/"", /*spanish*/"unos #dos mercaderes deku, incluyendo uno de mejora#"},
  });

  HintText Colossus_Grotto = HintText::Region({
                     //obscure text
                     Text{"2 Deku Scrubs", /*french*/"", /*spanish*/"unos #dos mercaderes deku#"},
  });

  HintText ZR_StormsGrotto = HintText::Region({
                     //obscure text
                     Text{"2 Deku Scrubs", /*french*/"", /*spanish*/"unos #dos mercaderes deku#"},
  });

  HintText SFM_StormsGrotto = HintText::Region({
                     //obscure text
                     Text{"2 Deku Scrubs", /*french*/"", /*spanish*/"unos #dos mercaderes deku#"},
  });

  HintText GV_StormsGrotto = HintText::Region({
                     //obscure text
                     Text{"2 Deku Scrubs", /*french*/"", /*spanish*/"unos #dos mercaderes deku#"},
  });

  HintText LH_Grotto = HintText::Region({
                     //obscure text
                     Text{"3 Deku Scrubs", /*french*/"", /*spanish*/"unos #tres mercaderes deku#"},
  });

  HintText DMC_HammerGrotto = HintText::Region({
                     //obscure text
                     Text{"3 Deku Scrubs", /*french*/"", /*spanish*/"unos #tres mercaderes deku#"},
  });

  HintText GC_Grotto = HintText::Region({
                     //obscure text
                     Text{"3 Deku Scrubs", /*french*/"", /*spanish*/"unos #tres mercaderes deku#"},
  });

  HintText LLR_Grotto = HintText::Region({
                     //obscure text
                     Text{"3 Deku Scrubs", /*french*/"", /*spanish*/"unos #tres mercaderes deku#"},
  });

  HintText ZR_FairyGrotto = HintText::Region({
                     //obscure text
                     Text{"a small #Fairy Fountain#", /*french*/"", /*spanish*/"una pequeña #fuente de las hadas#"},
  });

  HintText HF_FairyGrotto = HintText::Region({
                     //obscure text
                     Text{"a small #Fairy Fountain#", /*french*/"", /*spanish*/"una pequeña #fuente de las hadas#"},
  });

  HintText SFM_FairyGrotto = HintText::Region({
                     //obscure text
                     Text{"a small #Fairy Fountain#", /*french*/"", /*spanish*/"una pequeña #fuente de las hadas#"},
  });

  HintText ZD_StormsGrotto = HintText::Region({
                     //obscure text
                     Text{"a small #Fairy Fountain#", /*french*/"", /*spanish*/"una pequeña #fuente de las hadas#"},
  });

  HintText GF_StormsGrotto = HintText::Region({
                     //obscure text
                     Text{"a small #Fairy Fountain#", /*french*/"", /*spanish*/"una pequeña #fuente de las hadas#"},
  });

  /*--------------------------
  |      JUNK HINT TEXT      |
  ---------------------------*/

  HintText Junk01 = HintText::Junk({
                     //obscure text
                     Text{"Ganondorf 2022!", /*french*/"", /*spanish*/"¡Ganondorf para el 2022!"},
  });

  HintText Junk02 = HintText::Junk({
                     //obscure text
                     Text{"They say that monarchy is a terrible system of governance.", /*french*/"", /*spanish*/"Según dicen, la monarquía es un pésimo modelo político."},
  });

  HintText Junk03 = HintText::Junk({
                     //obscure text
                     Text{"They say that Zelda is a poor leader.", /*french*/"", /*spanish*/"Según dicen, Zelda es mala líder."},
  });

  HintText Junk04 = HintText::Junk({
                     //obscure text
                     Text{"These hints can be quite useful. This is an exception.", /*french*/"", /*spanish*/"Las pistas suelen servir de ayuda. En cambio, esta no."},
  });

  HintText Junk06 = HintText::Junk({
                     //obscure text
                     Text{"They say that all the Zora drowned in Wind Waker.", /*french*/"", /*spanish*/"Según dicen, en Wind Waker todos los zora se ahogaron."},
  });

  HintText Junk08 = HintText::Junk({
                     //obscure text
                     Text{"'Member when Ganon was a blue pig?^I 'member.", /*french*/"", /*spanish*/"¿T'acuerdas cuando Ganon era un cerdo azul?^Yo sí m'acuerdo."},
  });

  HintText Junk09 = HintText::Junk({
                     //obscure text
                     Text{"One who does not have Triforce can't go in.", /*french*/"", /*spanish*/"El que no porte la Trifuerza no podrá pasar."},
  });

  HintText Junk10 = HintText::Junk({
                     //obscure text
                     Text{"Save your future, end the Happy Mask Salesman.", /*french*/"", /*spanish*/"Salva tu futuro, acaba con el dueño de La Máscara Feliz."},
  });

  HintText Junk12 = HintText::Junk({
                     //obscure text
                     Text{"I'm stoned. Get it?", /*french*/"", /*spanish*/"Me he quedado de piedra. ¿Lo pillas?"},
  });

  HintText Junk13 = HintText::Junk({
                     //obscure text
                     Text{"Hoot! Hoot! Would you like me to repeat that?", /*french*/"", /*spanish*/"¡Buuu, buuu! ¿Te lo vuelvo a repetir?"},
  });

  HintText Junk14 = HintText::Junk({
                     //obscure text
                     Text{"Gorons are stupid. They eat rocks.", /*french*/"", /*spanish*/"Los goron son tontos. Se comen las piedras."},
  });

  HintText Junk15 = HintText::Junk({
                     //obscure text
                     Text{"They say that Lon Lon Ranch prospered under Ingo.", /*french*/"", /*spanish*/"Dicen que el Rancho Lon Lon prosperó gracias a Ingo."},
  });

  HintText Junk16 = HintText::Junk({
                     //obscure text
                     Text{"The single rupee is a unique item.", /*french*/"", /*spanish*/"La rupia de uno es un objeto singular."},
  });

  HintText Junk17 = HintText::Junk({
                     //obscure text
                     Text{"Without the Lens of Truth, the Treasure Chest Mini-Game is a 1 out of 32 chance.^Good luck!", /*french*/"", /*spanish*/"Sin la Lupa de la Verdad, ganarías 1 de cada 32 veces en el Cofre del Tesoro.^¡Buena suerte con ello!"},
  });

  HintText Junk18 = HintText::Junk({
                     //obscure text
                     Text{"Use bombs wisely.", /*french*/"", /*spanish*/"No desperdicies las bombas."},
  });

  HintText Junk21 = HintText::Junk({
                     //obscure text
                     Text{"I found you, faker!", /*french*/"", /*spanish*/"¡Ahí estás, impostor!"},
  });

  HintText Junk22 = HintText::Junk({
                     //obscure text
                     Text{"You're comparing yourself to me?^Ha! You're not even good enough to be my fake.", /*french*/"", /*spanish*/"¿Me estás comparando contigo?^¡Ja! No me llegas ni a la suela para ser un impostor mío."},
  });

  HintText Junk23 = HintText::Junk({
                     //obscure text
                     Text{"I'll make you eat those words.", /*french*/"", /*spanish*/"Te tragarás tus propias palabras."},
  });

  HintText Junk24 = HintText::Junk({
                     //obscure text
                     Text{"What happened to Sheik?", /*french*/"", /*spanish*/"¿Qué la habrá pasado a Sheik?"},
  });

  HintText Junk25 = HintText::Junk({
                     //obscure text
                     Text{"L2P @.", /*french*/"", /*spanish*/"Mira que eres novato, @."},
  });

  HintText Junk26 = HintText::Junk({
                     //obscure text
                     Text{"I've heard Sploosh Kaboom is a tricky game.", /*french*/"", /*spanish*/"He oído que el Splas Kapum es un minijuego difícil."},
  });

  HintText Junk27 = HintText::Junk({
                     //obscure text
                     Text{"I'm Lonk from Pennsylvania.", /*french*/"", /*spanish*/"Soy Lonk, de Pensilvania."},
  });

  HintText Junk28 = HintText::Junk({
                     //obscure text
                     Text{"I bet you'd like to have more bombs.", /*french*/"", /*spanish*/"Me apuesto a que quisieras tener más bombas."},
  });

  HintText Junk29 = HintText::Junk({
                     //obscure text
                     Text{"When all else fails, use Fire.", /*french*/"", /*spanish*/"Cuando nada funcione, usa fuego."},
  });

  HintText Junk30 = HintText::Junk({
                     //obscure text
                     Text{"Here's a hint, @. Don't be bad.", /*french*/"", /*spanish*/"Aquí tienes una pista, @. Deja de ser manco."},
  });

  HintText Junk31 = HintText::Junk({
                     //obscure text
                     Text{"Game Over. Return of Ganon.", /*french*/"", /*spanish*/"Fin de la partida. El regreso de Ganon."},
  });

  HintText Junk32 = HintText::Junk({
                     //obscure text
                     Text{"May the way of the Hero lead to the Triforce.", /*french*/"", /*spanish*/"Puede que la senda del héroe te lleve hacia la Trifuerza."},
  });

  HintText Junk33 = HintText::Junk({
                     //obscure text
                     Text{"Can't find an item? Scan an Amiibo.", /*french*/"", /*spanish*/"¿No encuentras algo? Escanea un amiibo."},
  });

  HintText Junk34 = HintText::Junk({
                     //obscure text
                     Text{"They say this game has just a few glitches.", /*french*/"", /*spanish*/"Dicen que este juego solo tiene unos pocos glitches."},
  });

  HintText Junk35 = HintText::Junk({
                     //obscure text
                     Text{"BRRING BRRING This is Ulrira. Wrong number?", /*french*/"", /*spanish*/"¡Ring! ¡Ring! Al habla Ulrira. ¿Me he equivocado de número?"},
  });

  HintText Junk36 = HintText::Junk({
                     //obscure text
                     Text{"Tingle Tingle Kooloo Limpah", /*french*/"", /*spanish*/"Tingle, Tingle, Kululim... ¡Pah!"},
  });

  HintText Junk37 = HintText::Junk({
                     //obscure text
                     Text{"L is real 2041", /*french*/"", /*spanish*/"L es real 2041."},
  });

  HintText Junk38 = HintText::Junk({
                     //obscure text
                     Text{"They say that Ganondorf will appear in the next Mario Tennis.", /*french*/"", /*spanish*/"Según dicen, Ganondorf estará en el próximo Mario Tennis."},
  });

  HintText Junk39 = HintText::Junk({
                     //obscure text
                     Text{"Medigoron sells the earliest Breath of the Wild demo.", /*french*/"", /*spanish*/"Medigoron vende la primera demo del Breath of the Wild."},
  });

  HintText Junk40 = HintText::Junk({
                     //obscure text
                     Text{"There's a reason why I am special inquisitor!", /*french*/"", /*spanish*/"¡Por algo soy una inquisidora especial!"},
  });

  HintText Junk41 = HintText::Junk({
                     //obscure text
                     Text{"You were almost a @ sandwich.", /*french*/"", /*spanish*/"Por poco te conviertes en emparedado de @."},
  });

  HintText Junk42 = HintText::Junk({
                     //obscure text
                     Text{"I'm a helpful hint Gossip Stone!^See, I'm helping.", /*french*/"", /*spanish*/"Soy una Piedra Sheikah muy útil.^¡Mira cómo te ayudo!"},
  });

  HintText Junk43 = HintText::Junk({
                     //obscure text
                     Text{"Dear @, please come to the castle. I've baked a cake for you.&Yours truly, princess Zelda.", /*french*/"", /*spanish*/"Querido @: Por favor, ven al castillo. He hecho una tarta para ti.&Sinceramente tuya: Princesa Zelda."},
  });

  HintText Junk44 = HintText::Junk({
                     //obscure text
                     Text{"They say all toasters toast toast.", /*french*/"", /*spanish*/"Según dicen, todas las tostadoras tostan tostadas."},
  });

  HintText Junk45 = HintText::Junk({
                     //obscure text
                     Text{"They say that Okami is the best Zelda game.", /*french*/"", /*spanish*/"Según dicen, Okami es el mejor juego de Zelda."},
  });

  HintText Junk46 = HintText::Junk({
                     //obscure text
                     Text{"They say that quest guidance can be found at a talking rock.", /*french*/"", /*spanish*/"Según dicen, puedes consultarle ayuda a rocas parlanchinas."},
  });

  HintText Junk47 = HintText::Junk({
                     //obscure text
                     Text{"They say that the final item you're looking for can be found somewhere in Hyrule.", /*french*/"", /*spanish*/"Según dicen, el último objeto que te falte puede estar en cualquier parte de Hyrule."},
  });

  HintText Junk48 = HintText::Junk({
                     //obscure text
                     Text{"Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.", /*french*/"", /*spanish*/"Muip.^Muip.^Muip.^Muip.^Muip.^Muip.^Muip.^Muip.^Muip.^Muip.^Muip.^Muip."},
  });

  HintText Junk49 = HintText::Junk({
                     //obscure text
                     Text{"They say that Barinade fears Deku Nuts.", /*french*/"", /*spanish*/"Según dicen, lo que más teme a Barinade son las nueces deku."},
  });

  HintText Junk50 = HintText::Junk({
                     //obscure text
                     Text{"They say that Flare Dancers do not fear Goron-crafted blades.", /*french*/"", /*spanish*/"Según dicen, los Bailafuegos no le temen a las armas forjadas por gorons."},
  });

  HintText Junk51 = HintText::Junk({
                     //obscure text
                     Text{"They say that Morpha is easily trapped in a corner.", /*french*/"", /*spanish*/"Según dicen, puedes atrapar a Morpha con facilidad en una esquina."},
  });

  HintText Junk52 = HintText::Junk({
                     //obscure text
                     Text{"They say that Bongo Bongo really hates the cold.", /*french*/"", /*spanish*/"Según dicen, Bongo Bongo odia a muerte el frío."},
  });

  HintText Junk53 = HintText::Junk({
                     //obscure text
                     Text{"They say that your sword is most powerful when you put it away.", /*french*/"", /*spanish*/"Según dicen, tu espada se vuelve más poderosa si la guardas."},
  });

  HintText Junk54 = HintText::Junk({
                     //obscure text
                     Text{"They say that bombing the hole Volvagia last flew into can be rewarding.", /*french*/"", /*spanish*/"Según dicen, trae buena suerte colocar una bomba en el último agujero de donde salió Volvagia."},
  });

  HintText Junk55 = HintText::Junk({
                     //obscure text
                     Text{"They say that invisible ghosts can be exposed with Deku Nuts.", /*french*/"", /*spanish*/"Según dicen, puedes exponer a los espectros invisibles con nueces deku."},
  });

  HintText Junk56 = HintText::Junk({
                     //obscure text
                     Text{"They say that the real Phantom Ganon is bright and loud.", /*french*/"", /*spanish*/"Según dicen, el verdadero Ganon Fantasma es brillante y ruidoso."},
  });

  HintText Junk57 = HintText::Junk({
                     //obscure text
                     Text{"They say that walking backwards is very fast.", /*french*/"", /*spanish*/"Según dicen, es más rápido caminar hacia atrás."},
  });

  HintText Junk58 = HintText::Junk({
                     //obscure text
                     Text{"They say that leaping above the Market entrance enriches most children.", /*french*/"", /*spanish*/"Según dicen, saltar por las cadenas a la entrada de la plaza enriquece a muchos chiquillos."},
  });

  HintText Junk59 = HintText::Junk({
                     //obscure text
                     Text{"They say that looking into darkness may find darkness looking back into you.", /*french*/"", /*spanish*/"Según dicen, contemplar la oscuridad puede hacer que ella te contemple a ti."},
  });

  HintText Junk60 = HintText::Junk({
                     //obscure text
                     Text{"You found a spiritual Stone! By which I mean, I worship Nayru.", /*french*/"", /*spanish*/"¡Has encontrado una piedra espiritual! Es que le rindo culto a Nayru..."},
  });

  HintText Junk61 = HintText::Junk({
                     //obscure text
                     Text{"They say that the stick is mightier than the sword...^At least, it used to be...", /*french*/"", /*spanish*/"Según dicen, los palos son más poderosos que las espadas...^O así solía ser..."},
  });

  HintText Junk62 = HintText::Junk({
                     //obscure text
                     Text{"Open your eyes.^Open your eyes.^Wake up, @.", /*french*/"", /*spanish*/"Abre los ojos...^Abre los ojos...^Despierta, @..."},
  });

  HintText Junk63 = HintText::Junk({
                     //obscure text
                     Text{"They say that the Nocturne of Shadow can bring you very close to Ganon.", /*french*/"", /*spanish*/"Según dicen, el Nocturno de la sombra te puede acercar mucho a Ganon."},
  });

  HintText Junk64 = HintText::Junk({
                     //obscure text
                     Text{"They say that Twinrova always casts the same spell the first three times.", /*french*/"", /*spanish*/"Según dicen, Birova siempre lanza el mismo hechizo tres veces."},
  });

  HintText Junk65 = HintText::Junk({
                     //obscure text
                     Text{"They say that the nightly builds may be unstable.", /*french*/"", /*spanish*/"Según dicen, las última nightly puede ser algo inestable."},
  });

  HintText Junk66 = HintText::Junk({
                     //obscure text
                     Text{"You're playing a Randomizer. I'm randomized!^Here's a random number:  #4#.&Enjoy your Randomizer!", /*french*/"", /*spanish*/"¡Estás jugando un Randomizer! ¡Yo también estoy aleatorizada!^Aquí tienes un número aleatorio:  #4#.&¡Disfruta el Randomizer!"},
  });

  HintText Junk67 = HintText::Junk({
                     //obscure text
                     Text{"They say Ganondorf's bolts can be reflected with glass or steel.", /*french*/"", /*spanish*/"Según dicen, puedes reflejar las esferas de energía de Ganondorf con cristal y acero."},
  });

  HintText Junk68 = HintText::Junk({
                     //obscure text
                     Text{"They say Ganon's tail is vulnerable to nuts, arrows, swords, explosives, hammers...^...sticks, seeds, boomerangs...^...rods, shovels, iron balls, angry bees...", /*french*/"", /*spanish*/"Según dicen, la cola de Ganon es vulnerable a nueces, flechas, espadas, explosivos, martillos...^...palos, semillas, bumeráns...^...cetros, palas, bolas de hierro, abejas..."},
  });

  HintText Junk69 = HintText::Junk({
                     //obscure text
                     Text{"They say that you're wasting time reading this hint, but I disagree. Talk to me again!", /*french*/"", /*spanish*/"Según dicen, pierdes el tiempo en leer esta pista, pero no pienso igual. ¡Vuelve a hablarme, ya verás!"},
  });

  HintText Junk70 = HintText::Junk({
                     //obscure text
                     Text{"They say Ganondorf knows where to find the instrument of his doom.", /*french*/"", /*spanish*/"Según dicen, Ganondorf sabe dónde hallar el instrumento de su perdición."},
  });

  HintText Junk71 = HintText::Junk({
                     //obscure text
                     Text{"I heard @ is pretty good at Zelda.", /*french*/"", /*spanish*/"He oído que a @ se le dan muy bien los Zelda."},
  });

  /*--------------------------
  |     DUNGEON HINT TEXT    |
  ---------------------------*/

  HintText DekuTree = HintText::DungeonName({
                     //obscure text
                     Text{"an ancient tree", /*french*/"", /*spanish*/"un ancestral árbol"},
                   },
                     //clear text
                     Text{"Deku Tree", /*french*/"", /*spanish*/"el Árbol Deku"}
  );

  HintText DodongosCavern = HintText::DungeonName({
                     //obscure text
                     Text{"an immense cavern", /*french*/"", /*spanish*/"una descomunal cueva"},
                   },
                     //clear text
                     Text{ "Dodongo's Cavern", /*french*/"", /*spanish*/"la Cueva de los Dodongos"}
  );

  HintText JabuJabusBelly = HintText::DungeonName({
                     //obscure text
                     Text{"the belly of a deity", /*french*/"", /*spanish*/"la tripa de cierta deidad"},
                   },
                     //clear text
                     Text{ "Jabu Jabu's Belly", /*french*/"", /*spanish*/"la tripa de Jabu Jabu"}
  );

  HintText ForestTemple = HintText::DungeonName({
                     //obscure text
                     Text{"a deep forest", /*french*/"", /*spanish*/"un profundo bosque"},
                   },
                     //clear text
                     Text{ "Forest Temple", /*french*/"", /*spanish*/"el Templo del Bosque"}
  );

  HintText FireTemple = HintText::DungeonName({
                     //obscure text
                     Text{"a high mountain", /*french*/"", /*spanish*/"una alta montaña"},
                   },
                     //clear text
                     Text{ "Fire Temple", /*french*/"", /*spanish*/"el Templo del Fuego"}
  );

  HintText WaterTemple = HintText::DungeonName({
                     //obscure text
                     Text{"a vast lake", /*french*/"", /*spanish*/"un lago inmenso"},
                   },
                     //clear text
                     Text{ "Water Temple", /*french*/"", /*spanish*/"el Templo del Agua"}
  );

  HintText ShadowTemple = HintText::DungeonName({
                     //obscure text
                     Text{"the house of the dead", /*french*/"", /*spanish*/"la casa de la muerte"},
                   },
                     //clear text
                     Text{ "Shadow Temple", /*french*/"", /*spanish*/"el Templo de las Sombras"}
  );

  HintText SpiritTemple = HintText::DungeonName({
                     //obscure text
                     Text{"the goddess of the sand", /*french*/"", /*spanish*/"la diosa de la arena"},
                   },
                     //clear text
                     Text{ "Spirit Temple", /*french*/"", /*spanish*/"el Templo del Espíritu"}
  );

  HintText IceCavern = HintText::DungeonName({
                     //obscure text
                     Text{"a frozen maze", /*french*/"", /*spanish*/"un gélido laberinto"},
                   },
                     //clear text
                     Text{ "Ice Cavern", /*french*/"", /*spanish*/"la caverna de hielo"}
  );

  HintText BottomOfTheWell = HintText::DungeonName({
                     //obscure text
                     Text{"a shadow\'s prison", /*french*/"", /*spanish*/"la prisión de las sombras"},
                   },
                     //clear text
                     Text{ "Bottom of the Well", /*french*/"", /*spanish*/"el fondo del pozo"}
  );

  HintText GerudoTrainingGrounds = HintText::DungeonName({
                     //obscure text
                     Text{"the test of thieves", /*french*/"", /*spanish*/"la prueba de las ladronas"},
                   },
                     //clear text
                     Text{ "Gerudo Training Grounds", /*french*/"", /*spanish*/"el Centro de Instrucción Gerudo"}
  );

  HintText GanonsCastle = HintText::DungeonName({
                     //obscure text
                     Text{"a conquered citadel", /*french*/"", /*spanish*/"una conquistada ciudadela"},
                   },
                     //clear text
                     Text{ "Inside Ganon's Castle", /*french*/"", /*spanish*/"el interior del Castillo de Ganondorf"}
  );

  /*--------------------------
  |      BOSS HINT TEXT      |
  ---------------------------*/

  HintText QueenGohma = HintText::Boss({
                     //obscure text
                     Text{"An #ancient tree# rewards", /*french*/"", /*spanish*/"un #ancestral árbol# premia con"},
                   },
                     //clear text
                     Text{"the #Deku Tree# rewards", /*french*/"", /*spanish*/"el #Árbol Deku# premia con"}
  );

  HintText KingDodongo = HintText::Boss({
                     //obscure text
                     Text{"An #immense cavern# rewards", /*french*/"", /*spanish*/"una #descomunal cueva# premia con"},
                   },
                     //clear text
                     Text{"#Dodongo's Cavern# rewards", /*french*/"", /*spanish*/"la #Cueva de los Dodongos# premia con"}
  );

  HintText Barinade = HintText::Boss({
                     //obscure text
                     Text{"the #belly of a deity# rewards", /*french*/"", /*spanish*/"la #tripa de cierta deidad# premia con"},
                   },
                     //clear text
                     Text{"#Jabu Jabu's Belly# rewards", /*french*/"", /*spanish*/"la #Tripa de Jabu Jabu# premia con"}
  );

  HintText PhantomGanon = HintText::Boss({
                     //obscure text
                     Text{"a #deep forest# rewards", /*french*/"", /*spanish*/"un #profundo bosque# premia con"},
                   },
                     //clear text
                     Text{"the #Forest Temple# rewards", /*french*/"", /*spanish*/"el #Templo del Bosque# premia con"}
  );

  HintText Volvagia = HintText::Boss({
                     //obscure text
                     Text{"a #high mountain# rewards", /*french*/"", /*spanish*/"una #alta montaña# premia con"},
                   },
                     //clear text
                     Text{"the #Fire Temple# rewards", /*french*/"", /*spanish*/"el #Templo del Fuego# premia con"}
  );

  HintText Morpha = HintText::Boss({
                     //obscure text
                     Text{"a #vast lake# rewards", /*french*/"", /*spanish*/"un #lago inmenso# premia con"},
                   },
                     //clear text
                     Text{"the #Water Temple# rewards", /*french*/"", /*spanish*/"el #Templo del Agua# premia con"}
  );

  HintText BongoBongo = HintText::Boss({
                     //obscure text
                     Text{"the #house of the dead# rewards", /*french*/"", /*spanish*/"la #casa de la muerte# premia con"},
                   },
                     //clear text
                     Text{"the #Shadow Temple# rewards", /*french*/"", /*spanish*/"el #Templo de las Sombras"}
  );

  HintText Twinrova = HintText::Boss({
                     //obscure text
                     Text{"a #goddess of the sand# rewards", /*french*/"", /*spanish*/"la #diosa de la arena# premia con"},
                   },
                     //clear text
                     Text{ "the #Spirit Temple# rewards", /*french*/"", /*spanish*/"el #Templo del Espíritu# premia con"}
  );

  HintText LinksPocketBoss = HintText::Boss({
                     //obscure text
                     Text{"#@'s pocket# rewards", /*french*/"", /*spanish*/"el #bolsillo de @# premia con"},
                   },
                     //clear text
                     Text{"#@ already has#", /*french*/"", /*spanish*/"el #bolsillo de @ ya tiene#"}
  );

  /*--------------------------
  |     BRIDGE HINT TEXT     |
  ---------------------------*/

  HintText BridgeVanilla = HintText::Bridge({
                     //obscure text
                     Text{"the #Shadow and Spirit Medallions# as well as the #Light Arrows#", /*french*/"", /*spanish*/"tanto el #Medallón de las Sombras y el del Espíritu# junto a las #Flechas de Luz#"},
  });

  HintText BridgeStones = HintText::Bridge({
                     //obscure text
                     Text{"Spiritual Stones", /*french*/"", /*spanish*/"las piedras espirituales"},
  });

  HintText BridgeMedallions = HintText::Bridge({
                     //obscure text
                     Text{"Medallions", /*french*/"", /*spanish*/"los medallones"},
  });

  HintText BridgeRewards = HintText::Bridge({
                     //obscure text
                     Text{"Spiritual Stones and Medallions", /*french*/"", /*spanish*/"las piedras espirituales y los medallones"},
  });

  HintText BridgeDungeons = HintText::Bridge({
                     //obscure text
                     Text{"Completed Dungeons", /*french*/"", /*spanish*/"al completar las mazmorras"},
  });

  HintText BridgeTokens = HintText::Bridge({
                     //obscure text
                     Text{"Gold Skulltula Tokens", /*french*/"", /*spanish*/"al obtener los símbolos de skulltulas doradas"},
  });

  /*--------------------------
  | GANON BOSS KEY HINT TEXT |
  ---------------------------*/

  HintText GanonBKVanilla = HintText::GanonsBossKey({
                     //obscure text
                     Text{"kept in a big chest #inside its tower#", /*french*/"", /*spanish*/"en un gran cofre #de su torre#"},
  });

  HintText GanonBKOwnDungeon = HintText::GanonsBossKey({
                     //obscure text
                     Text{"hidden somewhere #inside its castle#", /*french*/"", /*spanish*/"escondida en #algún lugar de su castillo#"},
  });

  HintText GanonBKOverworld = HintText::GanonsBossKey({
                     //obscure text
                     Text{"hidden #outside of dungeons# in Hyrule", /*french*/"", /*spanish*/"escondida #fuera de las mazmorras# de Hyrule"},
  });

  HintText GanonBKAnyDungeon = HintText::GanonsBossKey({
                     //obscure text
                     Text{"hidden #inside a dungeon# in Hyrule", /*french*/"", /*spanish*/"escondida #en una mazmorra# de Hyrule"},
  });

  HintText GanonBKKeysanity = HintText::GanonsBossKey({
                     //obscure text
                     Text{"hidden somewhere #in Hyrule#", /*french*/"", /*spanish*/"escondida en #cualquier lugar de Hyrule#"},
  });

  HintText GanonBKTriforce = HintText::GanonsBossKey({
                     //obscure text
                     Text{"given to the Hero once the #Triforce# is completed", /*french*/"", /*spanish*/"recibida por el héroe cuando haya completado la #Trifuerza#"},
  });

  /*--------------------------
  |      LACS HINT TEXT      |
  ---------------------------*/

  HintText LACSVanilla = HintText::LACS({
                     //obscure text
                     Text{"the #Shadow and Spirit Medallions#", /*french*/"", /*spanish*/"el #Medallón de las Sombras y el Espíritu#"},
  });

  HintText LACSMedallions = HintText::LACS({
                     //obscure text
                     Text{"Medallions", /*french*/"", /*spanish*/"los #medallones#"},
  });

  HintText LACSStones = HintText::LACS({
                     //obscure text
                     Text{"Spiritual Stones", /*french*/"", /*spanish*/"las #piedras espirituales#"},
  });

  HintText LACSRewards = HintText::LACS({
                     //obscure text
                     Text{"Spiritual Stones and Medallions", /*french*/"", /*spanish*/"las #piedras espirituales y los medallones#"},
  });

  HintText LACSTokens = HintText::LACS({
                     //obscure text
                     Text{"Gold Skulltula Tokens", /*french*/"", /*spanish*/"los #símbolos de skulltulas doradas#"},
  });

  /*--------------------------
  |        ALTAR TEXT        |
  ---------------------------*/

  HintText SpiritualStoneTextStart = HintText::Altar({
                     //obscure text
                     Text{"3 Spiritual Stones found in Hyrule...", /*french*/"", /*spanish*/"Tres piedras espirituales encontradas en Hyrule..."},
  });

  HintText ChildAltarTextEnd = HintText::Altar({
                     //obscure text
                     Text{"\x13\x07Ye who may become a Hero...&Stand with the Ocarina and&play the Song of Time.", /*french*/"", /*spanish*/"Aquel que se convierta en el héroe...&Tomad la ocarina y&entonad la Canción del Tiempo."},
  });

  HintText AdultAltarTextStart = HintText::Altar({
                     //obscure text
                     Text{"When evil rules all, an awakening&voice from the Sacred Realm will&call those destined to be Sages,&who dwell in the #five temples#.", /*french*/"", /*spanish*/"Cuando el mal lo impregne todo, desde el&Reino Sagrado surgirá unz voz que hará&despertar a los sabios que moran en los&#cinco templos#."},
  });

  HintText AdultAltarTextEnd = HintText::Altar({
                     //obscure text
                     Text{"Together with the Hero of Time,&the awakened ones will bind the&evil and return the light of peace&to the world...", /*french*/"", /*spanish*/"Con el héroe del Tiempo, aquellos que&despierten detendrán el mal y volverán&al mundo de luz la paz..."},
  });

  /*--------------------------
  |   VALIDATION LINE TEXT   |
  ---------------------------*/

  HintText ValidationLine = HintText::Validation({
                     //obscure text
                     Text{"Hmph... Since you made it this far,&I'll let you know what glorious&prize of Ganon's you likely&missed out on in my tower.^Behold...^", /*french*/"", /*spanish*/"Mmm... Ya que has llegado hasta aquí,&te diré qué preciado objeto&de Ganon puedes haberte&dejado en mi torre.^He aquí..."},
  });

  /*--------------------------
  | LIGHT ARROW LOCATION TEXT|
  ---------------------------*/

  HintText LightArrowLocation = HintText::LightArrow({
                     //obscure text
                     Text{"Ha ha ha... You'll never beat me by&reflecting my lightning bolts&and unleashing the arrows from&", /*french*/"", /*spanish*/"Ja, ja, ja... Nunca me derrotarás&reflejando mis esferas de energía y&desplegando las flechas de luz de&"},
  });

  /*--------------------------
  |      GANON LINE TEXT     |
  ---------------------------*/

  HintText GanonLine01 = HintText::GanonLine({
                     //obscure text
                     Text{"Oh! It's @.&I was expecting someone called&Sheik. Do you know what&happened to them?", /*french*/"", /*spanish*/"¡Oh! Pero si es @.&Estaba esperando a alguien llamado&Sheik. ¿Sabes qué puede&haberle pasado?"},
  });

  HintText GanonLine02 = HintText::GanonLine({
                     //obscure text
                     Text{"I knew I shouldn't have put the key&on the other side of my door.", /*french*/"", /*spanish*/"Sabía que no tendría que haber&dejado la llave al otro lado de la puerta."},
  });

  HintText GanonLine03 = HintText::GanonLine({
                     //obscure text
                     Text{"Looks like it's time for a&round of tennis.", /*french*/"", /*spanish*/"Parece que es hora de&una partidita de tenis."},
  });

  HintText GanonLine04 = HintText::GanonLine({
                     //obscure text
                     Text{"You'll never deflect my bolts of&energy with your sword,&then shoot me with those Light&Arrows you happen to have.", /*french*/"", /*spanish*/"Nunca reflejarás mis esferas de&energía con tu espada, para después&dispararme con las flechas de luz que tendrás."},
  });

  HintText GanonLine05 = HintText::GanonLine({
                     //obscure text
                     Text{"Why did I leave my trident&back in the desert?", /*french*/"", /*spanish*/"¿Por qué me habré dejado el&tridente en el desierto?"},
  });

  HintText GanonLine06 = HintText::GanonLine({
                     //obscure text
                     Text{"Zelda is probably going to do&something stupid, like send you&back to your own timeline.^So this is quite meaningless.&Do you really want&to save this moron?", /*french*/"", /*spanish*/"Seguro que Zelda trata de hacer&alguna tontería, como enviarte de&vuelta a tu línea temporal.^No tiene ningún sentido alguno.&¿De verdad quieres salvar a esa tonta?"},
  });

  HintText GanonLine07 = HintText::GanonLine({
                     //obscure text
                     Text{"What about Zelda makes you think&she'd be a better ruler than I?^I saved Lon Lon Ranch,&fed the hungry,&and my castle floats.", /*french*/"", /*spanish*/"¿Qué te hace pensar que Zelda&gobierna mejor que yo?^Yo he salvado el Rancho Lon Lon,&he alimentado a los hambrientos&y hasta hago que mi castillo flote."},
  });

  HintText GanonLine08 = HintText::GanonLine({
                     //obscure text
                     Text{"I've learned this spell,&it's really neat,&I'll keep it later&for your treat!", /*french*/"", /*spanish*/"Acabo de aprender este hechizo,&y la verdad es que es&de lo más bueno. ¡Te lo&reservaré como sorpresa!"},
  });

  HintText GanonLine09 = HintText::GanonLine({
                     //obscure text
                     Text{"Many tricks are up my sleeve,&to save yourself&you'd better leave!", /*french*/"", /*spanish*/"Tengo muchos trucos a mi espalda&, si no quieres morir,&¡deshazte de esa hada!"},
  });

  HintText GanonLine10 = HintText::GanonLine({
                     //obscure text
                     Text{"After what you did to&Koholint Island, how can&you call me the bad guy?", /*french*/"", /*spanish*/"Después de lo que le hiciste&a la Isla Koholint, ¿cómo te&atreves a llamarme malvado?"},
  });

  HintText GanonLine11 = HintText::GanonLine({
                     //obscure text
                     Text{"Today, let's begin down&'The Hero is Defeated' timeline.", /*french*/"", /*spanish*/"Hoy daremos lugar a la&línea temporal del Héroe Derrotado."},
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
