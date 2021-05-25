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
  HintText Prefix       = HintText::Exclude({Text{"They say that ", "Ils disent que ", /*spanish*/"Según dicen, "}});
  HintText WayOfTheHero = HintText::Exclude({Text{" is on the way of the hero.", " est sur le chemin du héros.", /*spanish*/" aguarda en la senda del héroe."}});
  HintText Plundering   = HintText::Exclude({Text{"plundering ", "piller ", /*spanish*/"vagar por "}});
  HintText Foolish      = HintText::Exclude({Text{" is a foolish choice.", " est futile.", /*spanish*/" no es una sabia decisión."}});

  /*--------------------------
  |      ITEM HINT TEXT      |
  ---------------------------*/

  HintText TriforcePiece = HintText::Item({
                       //obscure text
                       Text{"a triumph fork", "la Tribosse", /*spanish*/"un trígono del triunfo"},
                       Text{"cheese", "du fromage", /*spanish*/"un queso"},
                       Text{"a gold fragment", "un fragment d'or", /*spanish*/"un fragmento dorado"},
                     },
                       //clear text
                       Text{"a Piece of the Triforce", "un fragment de la Triforce", /*spanish*/"una Pieza de la Trifuerza"}
  );

  HintText ProgressiveMagic = HintText::Item({
                       //obscure text
                       Text{"mystic training", "un potentiel magique", /*spanish*/"una maestría mística"},
                       Text{"pixie dust", "de la poudre de fée", /*spanish*/"un polvo de hada"},
                       Text{"a green rectangle", "un rectangle vert", /*spanish*/"una verduzca vasija"},
                     },
                       //clear text
                       Text{"a Magic Meter", "une jauge de magie", /*spanish*/"una barra de magia"}
  );

  HintText DoubleDefense = HintText::Item({
                       //obscure text
                       Text{"a white outline", "un rebord blanc", /*spanish*/"un contorno blanco"},
                       Text{"damage decrease", "une protection supplémentaire", /*spanish*/"una reducción de daño"},
                       Text{"strengthened love", "un amour coriace", /*spanish*/"un amor fortalecido"},
                     },
                       //clear text
                       Text{"Double Defense", "la double défence", /*spanish*/"la doble defensa"}
  );

  HintText ProgressiveBulletBag = HintText::Item({
                       //obscure text
                       Text{"a seed shooter", "un lance-noix", /*spanish*/"un lanzasemillas"},
                       Text{"a rubberband", "un élastique", /*spanish*/"una resortera"},
                       Text{"a child's catapult", "un jouet d'enfant", /*spanish*/"una catapulta infantil"},
                     },
                       //clear text
                       Text{"a Slingshot", "un lance-pierre", /*spanish*/"un tirachinas"}
  );

  HintText Boomerang = HintText::Item({
                       //obscure text
                       Text{"a banana", "une banane", /*spanish*/"un plátano"},
                       Text{"a stun stick", "un bâton étourdissant", /*spanish*/"un palo aturdidor"},
                       Text{"a yellow angle", "un angle jaune", /*spanish*/"un ángulo amarillo"},
                     },
                       //clear text
                       Text{"the Boomerang", "le boomerang", /*spanish*/"el bumerán"}
  );

  HintText ProgressiveBow = HintText::Item({
                       //obscure text
                       Text{"an archery enabler", "un facilitateur de tir", /*spanish*/"un tiro al blanco"},
                       Text{"a danger dart launcher", "un tire-fléchette", /*spanish*/"un peligroso lanzadardos"},
                     },
                       //clear text
                       Text{"a Bow", "un arc", /*spanish*/"un arco"}
  );

  HintText ProgressiveBombBag = HintText::Item({
                       //obscure text
                       Text{"an explosive container", "un porte-grenade", /*spanish*/"un recipiente explosivo"},
                       Text{"a blast bag", "un estomac de Dodongo", /*spanish*/"un zurrón de estallidos"},
                     },
                       //clear text
                       Text{"a Bomb Bag", "un sac de bombes", /*spanish*/"un saco de bombas"}
  );

  HintText ProgressiveHookshot = HintText::Item({
                       //obscure text
                       Text{"Dampé's keepsake", "l'héritage d'Igor", /*spanish*/"un recuerdo de Dampé"},
                       Text{"the Grapple Beam", "le rayon grippeur", /*spanish*/"una liana de agarre"},
                       Text{"the BOING! chain", "la chaîne de BOING!", /*spanish*/"una cadena retráctil"},
                     },
                       //clear text
                       Text{"a Hookshot", "un grappin", /*spanish*/"un gancho"}
  );

  HintText ProgressiveStrength = HintText::Item({
                       //obscure text
                       Text{"power gloves", "des gants de travail", /*spanish*/"unos poderosos guanteletes"},
                       Text{"metal mittens", "des mitaines", /*spanish*/"unas manoplas metálicas"},
                       Text{"the heavy lifty", "la puissance de dix hommes", /*spanish*/"un levantamiento pesado"},
                     },
                       //clear text
                       Text{"a Strength Upgrade", "une amélioration de force", /*spanish*/"un aumento de fuerza"}
  );

  HintText ProgressiveScale = HintText::Item({
                       //obscure text
                       Text{"a deeper dive", "une bulle de plongée", /*spanish*/"un profundo buceo"},
                       Text{"a piece of Zora", "un morceau de Zora", /*spanish*/"un fragmento de Zora"},
                     },
                       //clear text
                       Text{"a Zora Scale", "une écaille Zora", /*spanish*/"una escama Zora"}
  );

  HintText MegatonHammer = HintText::Item({
                       //obscure text
                       Text{"the dragon smasher", "le tueur de dragons", /*spanish*/"un destructor de dragones"},
                       Text{"the metal mallet", "un outil de construction", /*spanish*/"un mazo de metal"},
                       Text{"the heavy hitter", "un poids lourd", /*spanish*/"un machacador"},
                     },
                       //clear text
                       Text{"the Megaton Hammer", "la masse des titans", /*spanish*/"el martillo Megatón"}
  );

  HintText IronBoots = HintText::Item({
                       //obscure text
                       Text{"sink shoes", "deux boulets de fer", /*spanish*/"un calzado de las profundidades"},
                       Text{"clank cleats", "des talons bruyants", /*spanish*/"unas botas férreas"},
                     },
                       //clear text
                       Text{"the Iron Boots", "les bottes de plomb", /*spanish*/"las botas de hierro"}
  );

  HintText HoverBoots = HintText::Item({
                       //obscure text
                       Text{"butter boots", "des patins de beurre", /*spanish*/"unas suelas resvaladizas"},
                       Text{"sacred slippers", "des pantoufles sacrées", /*spanish*/"unos escurridizos botines"},
                       Text{"spacewalkers", "des bottes spatiales", /*spanish*/"un calzado antigravitatorio"},
                     },
                       //clear text
                       Text{"the Hover Boots", "les bottes des airs", /*spanish*/"las botas voladoras"}
  );

  HintText KokiriSword = HintText::Item({
                       //obscure text
                       Text{"a butter knife", "couteau à beurre", /*spanish*/"un ágil puñal"},
                       Text{"a starter slasher", "une arme de débutant", /*spanish*/"una hoja de principiantes"},
                       Text{"a switchblade", "un canif", /*spanish*/"un raudo cortador"},
                     },
                       //clear text
                       Text{"the Kokiri Sword", "l'épée Kokiri", /*spanish*/"la Espada Kokiri"}
  );

  HintText GiantsKnife = HintText::Item({
                       //obscure text
                       Text{"a fragile blade", "une lame fragile", /*spanish*/"una frágil hoja"},
                       Text{"a breakable cleaver", "un espadon de verre", /*spanish*/"un rompible acero"},
                     },
                       //clear text
                       Text{"the Giant's Knife", "la lame des géants", /*spanish*/"la daga gigante"}
  );

  HintText BiggoronSword = HintText::Item({
                       //obscure text
                       Text{"the biggest blade", "une lame gigantesque", /*spanish*/"el mayor mandoble"},
                       Text{"a colossal cleaver", "un espadon colossal", /*spanish*/"un estoque colosal"},
                     },
                       //clear text
                       Text{"the Biggoron Sword", "l'épée de Biggoron", /*spanish*/"la Espada de Biggoron"}
  );

  HintText MasterSword = HintText::Item({
                       //obscure text
                       Text{"evil's bane", "le fléau du mal", /*spanish*/"la destructora del mal"},
                       Text{"a seven year limbo", "une stase de sept ans", /*spanish*/"unos siete años de espera"},
                     },
                       //clear text
                       Text{"the Master Sword", "l'épée de légende", /*spanish*/"la Espada Maestra"}
  );

  HintText DekuShield = HintText::Item({
                       //obscure text
                       Text{"a wooden ward", "un écu d'écorce", /*spanish*/"una protección forestal"},
                       Text{"a burnable barrier", "une protection inflammable", /*spanish*/"una barrera quemable"},
                     },
                       //clear text
                       Text{"a Deku Shield", "un bouclier Mojo", /*spanish*/"un escudo deku"}
  );

  HintText HylianShield = HintText::Item({
                       //obscure text
                       Text{"a steel safeguard", "une carapace d'acier", /*spanish*/"un protección de acero"},
                       Text{"Like Like's metal meal", "un amuse-gueule de Pudding", /*spanish*/"un metálico plato de Like Like"},
                     },
                       //clear text
                       Text{"a Hylian Shield", "un bouclier hylien", /*spanish*/"un escudo hyliano"}
  );

  HintText MirrorShield = HintText::Item({
                       //obscure text
                       Text{"a reflective rampart", "un capteur de lumière", /*spanish*/"una muralla reflectora"},
                       Text{"Medusa's weakness", "la faiblesse de Méduse", /*spanish*/"la debilidad de Medusa"},
                       Text{"a silvered surface", "une surface argentée", /*spanish*/"una superficie plateada"},
                     },
                       //clear text
                       Text{"the Mirror Shield", "le bouclier miroir", /*spanish*/"el escudo espejo"}
  );

  HintText FaroresWind = HintText::Item({
                       //obscure text
                       Text{"teleportation", "la téléportation", /*spanish*/"el teletransporte"},
                       Text{"a relocation rune", "une rune de relocation", /*spanish*/"una runa de transporte"},
                       Text{"a green ball", "une boule verte", /*spanish*/"una verde esfera"},
                     },
                       //clear text
                       Text{"Farore's Wind", "le vent de Farore", /*spanish*/"el Viento de Farore"}
  );

  HintText NayrusLove = HintText::Item({
                       //obscure text
                       Text{"a safe space", "une bulle de cristal", /*spanish*/"un seguro espacio"},
                       Text{"an impregnable aura", "un aura impénétrable", /*spanish*/"una inexpugnable aura"},
                       Text{"a blue barrier", "une toison bleu", /*spanish*/"una barrera azul"},
                     },
                       //clear text
                       Text{"Nayru's Love", "l'amour de Nayru", /*spanish*/"el Amor de Nayru"}
  );

  HintText DinsFire = HintText::Item({
                       //obscure text
                       Text{"an inferno", "un brasier", /*spanish*/"un incendio"},
                       Text{"a heat wave", "une vague de chaleur", /*spanish*/"una onda de calor"},
                       Text{"a red ball", "une explosion de flammes", /*spanish*/"una roja esfera"},
                     },
                       //clear text
                       Text{"Din's Fire", "le feu de Din", /*spanish*/"el Fuego de Din"}
  );

  HintText FireArrows = HintText::Item({
                       //obscure text
                       Text{"the furnace firearm" , "une fusée solaire", /*spanish*/"el aguijón ardiente"},
                       Text{"the burning bolts", "un obus enflammé", /*spanish*/"las puntas candentes"},
                       Text{"a magma missile", "un missile volcanique", /*spanish*/"el misil abrasador"},
                     },
                       //clear text
                       Text{"the Fire Arrows", "la flèche de feu", /*spanish*/"las flechas de fuego"}
  );

  HintText IceArrows = HintText::Item({
                       //obscure text
                       Text{"the refrigerator rocket", "un missile pétrifiant", /*spanish*/"el misil congelado"},
                       Text{"the frostbite bolts", "un froid mordant", /*spanish*/"las puntas heladas"},
                       Text{"an iceberg maker", "une aiguille glaciale", /*spanish*/"el control de escarcha"},
                     },
                       //clear text
                       Text{"the Ice Arrows", "la flèche de glace", /*spanish*/"las flechas de hielo"}
  );

  HintText LightArrows = HintText::Item({
                       //obscure text
                       Text{"the shining shot", "l'arme brillante", /*spanish*/"el haz de luz"},
                       Text{"the luminous launcher", "un jet de lumière", /*spanish*/"el disparo luminoso"},
                       Text{"Ganondorf's bane", "le fléau de Ganondorf", /*spanish*/"el destructor de Ganondorf"},
                       Text{"the lighting bolts", "l'éclair sacré", /*spanish*/"las puntas resplandecientes"},
                     },
                       //clear text
                       Text{"the Light Arrows", "la flèche de lumière", /*spanish*/"las flechas de luz"}
  );

  HintText LensOfTruth = HintText::Item({
                       //obscure text
                       Text{"a lie detector", "un détecteur de mensonges", /*spanish*/"el detector de ilusiones"},
                       Text{"a ghost tracker", "un trouve-fantôme", /*spanish*/"el rastreador paranormal"},
                       Text{"true sight", "le troisième œil", /*spanish*/"el ojo que todo ve"},
                       Text{"a detective's tool", "un trésor Sheikah", /*spanish*/"la revelación verdadera"},
                     },
                       //clear text
                       Text{"the Lens of Truth", "le monocle de Vérité", /*spanish*/"la Lupa de la Verdad"}
  );

  HintText ProgressiveOcarina = HintText::Item({
                       //obscure text
                       Text{"a flute", "un bec musical", /*spanish*/"una flauta"},
                       Text{"a music maker", "un porteur de chansons", /*spanish*/"un instrumento"},
                     },
                       //clear text
                       Text{"an Ocarina", "un ocarina", /*spanish*/"una ocarina"}
  );

  HintText GoronTunic = HintText::Item({
                       //obscure text
                       Text{"ruby robes", "un pigment rouge", /*spanish*/"una vestimenta rubí"},
                       Text{"fireproof fabric", "un trésor anti-flamme", /*spanish*/"una ignífuga prenda"},
                       Text{"cooking clothes", "une tenue de cuisine", /*spanish*/"unos abrasantes ropajes"},
                     },
                       //clear text
                       Text{"a Goron Tunic", "une tunique Goron", /*spanish*/"un sayo goron"}
  );

  HintText ZoraTunic = HintText::Item({
                       //obscure text
                       Text{"a sapphire suit", "un pigment bleuté", /*spanish*/"una vestidura zafiro"},
                       Text{"scuba gear", "un habit de plongée", /*spanish*/"un traje de buceo"},
                       Text{"a swimsuit", "un costume de baignade", /*spanish*/"un bañador"},
                     },
                       //clear text
                       Text{"a Zora Tunic", "une tunique Zora", /*spanish*/"un sayo zora"}
  );

  HintText Epona = HintText::Item({
                       //obscure text
                       Text{"a horse", "un fidèle destrier", /*spanish*/"una yegua"},
                       Text{"a four legged friend", "un puissant animal", /*spanish*/"una amiga cuadrúpeda"},
                     },
                       //clear text
                       Text{"Epona", "Epona", /*spanish*/"Epona"}
  );

  HintText ZeldasLullaby = HintText::Item({
                       //obscure text
                       Text{"a song of royal slumber", "une chanson royale", /*spanish*/"la canción real"},
                       Text{"a triforce tune", "la musique sacrée", /*spanish*/"la melodía de la trifuerza"},
                     },
                       //clear text
                       Text{"Zelda's Lullaby", "la berceuse de Zelda", /*spanish*/"la Nana de Zelda"}
  );

  HintText EponasSong = HintText::Item({
                       //obscure text
                       Text{"an equestrian etude", "une hymne équestre", /*spanish*/"una copla ecuestre"},
                       Text{"Malon's melody", "la mélodie des vaches", /*spanish*/"la sonata de Malon"},
                       Text{"a ranch song", "le chant des champs", /*spanish*/"una canción rupestre"},
                     },
                       //clear text
                       Text{"Epona's Song", "le chant d'Epona", /*spanish*/"la Canción de Epona"}
  );

  HintText SariasSong = HintText::Item({
                       //obscure text
                       Text{"a song of dancing Gorons", "une chanson danceuse", /*spanish*/"la pegadiza tonada para Gorons"},
                       Text{"Saria's phone number", "le téléphone d'une amie", /*spanish*/"la llamada de Saria"},
                     },
                       //clear text
                       Text{"Saria's Song", "le chant de Saria", /*spanish*/"la Canción de Saria"}
  );

  HintText SunsSong = HintText::Item({
                       //obscure text
                       Text{"Sunny Day", "Zénith", /*spanish*/"un día soleado"},
                       Text{"the ReDead's bane", "le fléau des Effrois", /*spanish*/"la destructora de Redeads"},
                       Text{"the Gibdo's bane", "le fléau des Gibdo", /*spanish*/"la destructora de Gibdos"},
                     },
                       //clear text
                       Text{"the Sun's Song", "le chant du soleil", /*spanish*/"la Canción del Sol"}
  );

  HintText SongOfTime = HintText::Item({
                       //obscure text
                       Text{"a song 7 years long", "les flots du temps", /*spanish*/"la setenada canción"},
                       Text{"the tune of ages", "le Chant des Âges", /*spanish*/"la melodía eónica"},
                     },
                       //clear text
                       Text{"the Song of Time", "le chant du temps", /*spanish*/"la Canción del tiempo"}
  );

  HintText SongOfStorms = HintText::Item({
                       //obscure text
                       Text{"Rain Dance", "Danse Pluie", /*spanish*/"la danza de la lluvia"},
                       Text{"a thunderstorm tune", "une hymne foudroyante", /*spanish*/"una sonata tormentosa"},
                       Text{"windmill acceleration", "l'accélérateur de moulins", /*spanish*/"el arranque de molinos"},
                     },
                       //clear text
                       Text{"the Song of Storms", "le chant des tempêtes", /*spanish*/"la Canción de la Tormenta"}
  );

  HintText MinuetOfForest = HintText::Item({
                       //obscure text
                       Text{"the song of tall trees", "le bruit des arbres", /*spanish*/"la canción de las copas"},
                       Text{"an arboreal anthem", "l'hymne sylvestre", /*spanish*/"el himno forestal"},
                       Text{"a green spark trail", "une comète verte", /*spanish*/"el sendero esmeralda"},
                     },
                       //clear text
                       Text{"the Minuet of Forest", "le minuet de la forêt", /*spanish*/"el Minueto del bosque"}
  );

  HintText BoleroOfFire = HintText::Item({
                       //obscure text
                       Text{"a song of lethal lava", "les cloches", /*spanish*/"la canción de la lava"},
                       Text{"a red spark trail", "une comète rouge", /*spanish*/"el sendero carmesí"},
                       Text{"a volcanic verse", "le souffle du volcan", /*spanish*/"el verso volcánico"},
                     },
                       //clear text
                       Text{"the Bolero of Fire", "le boléro du feu", /*spanish*/"el Bolero del fuego"}
  );

  HintText SerenadeOfWater = HintText::Item({
                       //obscure text
                       Text{"a song of a damp ditch", "le calme de l'eau", /*spanish*/"la canción del estanque"},
                       Text{"a blue spark trail", "une comète bleue", /*spanish*/"el sendero azur"},
                       Text{"the lake's lyric", "la voix du lac", /*spanish*/"la letra del lago"},
                     },
                       //clear text
                       Text{"the Serenade of Water", "la sérénade de l'eau", /*spanish*/"la Serenata del agua"}
  );

  HintText RequiemOfSpirit = HintText::Item({
                       //obscure text
                       Text{"a song of sandy statues", "la mélodie d'une grande statue", /*spanish*/"la canción de estatuas areniscas"},
                       Text{"an orange spark trail", "une comète orange", /*spanish*/"el sendero ámbar"},
                       Text{"the desert ditty", "le vent du désert", /*spanish*/"la estrofa del desierto"},
                     },
                       //clear text
                       Text{"the Requiem of Spirit", "le requiem des esprits", /*spanish*/"el Réquiem del espíritu"}
  );

  HintText NocturneOfShadow = HintText::Item({
                       //obscure text
                       Text{"a song of spooky spirits", "une hymne de chair de poule", /*spanish*/"la canción de los espectros"},
                       Text{"a graveyard boogie", "un boogie de fantômes", /*spanish*/"una honra fúnebre"},
                       Text{"a haunted hymn", "une chanson lugubre", /*spanish*/"una estrofa encantada"},
                       Text{"a purple spark trail", "une comète mauve", /*spanish*/"el sendero malva"},
                     },
                       //clear text
                       Text{"the Nocturne of Shadow", "le nocturne de l'ombre", /*spanish*/"el Nocturno de la sombra"}
  );

  HintText PreludeOfLight = HintText::Item({
                       //obscure text
                       Text{"a luminous prologue melody", "les matines illuminées", /*spanish*/"la melodía refulgente"},
                       Text{"a yellow spark trail", "une comète jaune", /*spanish*/"el sendero áureo"},
                       Text{"the temple traveler", "un chant de sanctuaire", /*spanish*/"la ruta del templo"},
                     },
                       //clear text
                       Text{"the Prelude of Light", "le prélude de la lumière", /*spanish*/"el Preludio de la luz"}
  );

  HintText EmptyBottle = HintText::Item({
                       //obscure text
                       Text{"a glass container", "un cylindre de cristal", /*spanish*/"un recipiente de cristal"},
                       Text{"an empty jar", "une jarre incassable", /*spanish*/"un frasco vacío"},
                       Text{"encased air", "un bocal d'air", /*spanish*/"aire a presión"},
                     },
                       //clear text
                       Text{"a Bottle", "une bouteille vide", /*spanish*/"una botella"}
  );

  HintText RutosLetter = HintText::Item({
                       //obscure text
                       Text{"a call for help", "un appel au secours", /*spanish*/"una llamada de auxilio"},
                       Text{"the note that Mweeps", "les Mweep", /*spanish*/"un mensaje de ayuda"},
                       Text{"an SOS call", "un signal SOS", /*spanish*/"una nota de socorro"},
                       Text{"a fishy stationery", "une papier mouillé", /*spanish*/"un escrito urgente"},
                     },
                       //clear text
                       Text{"Ruto's Letter", "la lettre de Ruto", /*spanish*/"la carta de Ruto"}
  );

  HintText BottleWithMilk = HintText::Item({
                       //obscure text
                       Text{"cow juice", "une source de calcium", /*spanish*/"un jugo de vaca"},
                       Text{"a white liquid", "un liquide blanc", /*spanish*/"una bebida nutritiva"},
                       Text{"a baby's breakfast", "du jus pour bébé", /*spanish*/"un trago para bebés"},
                     },
                       //clear text
                       Text{"a Milk Bottle", "une bouteille de lait", /*spanish*/"una botella de leche"}
  );

  HintText BottleWithRedPotion = HintText::Item({
                       //obscure text
                       Text{"a vitality vial", "un mélange de vitalité", /*spanish*/"una pócima vitalicia"},
                       Text{"a red liquid", "un liquide rouge", /*spanish*/"un remedio rojizo"},
                     },
                       //clear text
                       Text{"a Red Potion Bottle", "une bouteille de potion rouge", /*spanish*/"una botella de poción roja"}
  );

  HintText BottleWithGreenPotion = HintText::Item({
                       //obscure text
                       Text{"a magic mixture", "une réserve magique", /*spanish*/"un potingue mágico"},
                       Text{"a green liquid", "un liquide vert", /*spanish*/"un remedio verduzco"},
                     },
                       //clear text
                       Text{"a Green Potion Bottle", "une bouteille de potion verte", /*spanish*/"una botella de poción verde"}
  );

  HintText BottleWithBluePotion = HintText::Item({
                       //obscure text
                       Text{"an ailment antidote", "l'élixir ultime", /*spanish*/"un antídoto de dolencias"},
                       Text{"a blue liquid", "un liquide bleu", /*spanish*/"un remedio índigo"},
                     },
                       //clear text
                       Text{"a Blue Potion Bottle", "une bouteille de potion bleue", /*spanish*/"una botella de poción azul"}
  );

  HintText BottleWithFairy = HintText::Item({
                       //obscure text
                       Text{"an imprisoned fairy", "une fée emprisonnée", /*spanish*/"una hada atrapada"},
                       Text{"an extra life", "une vie de rechange", /*spanish*/"una oportunidad más"},
                       Text{"Navi's cousin", "le cousin de Navi", /*spanish*/"la prima de Navi"},
                     },
                       //clear text
                       Text{"a Fairy Bottle", "une fée en bouteille", /*spanish*/"un hada embotellada"}
  );

  HintText BottleWithFish = HintText::Item({
                       //obscure text
                       Text{"an aquarium", "un aquarium", /*spanish*/"un escamado ser"},
                       Text{"a deity's snack", "le repas d'un dieu marin", /*spanish*/"el tentempié de cierta deidad"},
                     },
                       //clear text
                       Text{"a Fish Bottle", "un poisson en bouteille", /*spanish*/"un pez embotellado"}
  );

  HintText BottleWithBlueFire = HintText::Item({
                       //obscure text
                       Text{"a conflagration canteen", "une mystérieuse flamme", /*spanish*/"un pequeño incendio"},
                       Text{"an icemelt jar", "un brasier glacial", /*spanish*/"unas brasas enfrascadas"},
                     },
                       //clear text
                       Text{"a Blue Fire Bottle", "une flamme bleue en bouteille", /*spanish*/"una botella de fuego azul"}
  );

  HintText BottleWithBugs = HintText::Item({
                       //obscure text
                       Text{"an insectarium", "un insectarium", /*spanish*/"un insectario"},
                       Text{"Skulltula finders", "des trouve-Skulltula", /*spanish*/"unos rastreadores de skulltulas"},
                     },
                       //clear text
                       Text{"a Bug Bottle", "un insecte en bouteille", /*spanish*/"una botella con insectos"}
  );

  HintText BottleWithPoe = HintText::Item({
                       //obscure text
                       Text{"a spooky ghost", "un effroyable fantôme", /*spanish*/"una espantoso espectro"},
                       Text{"a face in the jar", "un visage dans un bocal", /*spanish*/"una cara embotellada"},
                     },
                       //clear text
                       Text{"a Poe Bottle", "un Esprit en bouteille", /*spanish*/"un Poe embotellado"}
  );

  HintText BottleWithBigPoe = HintText::Item({
                       //obscure text
                       Text{"the spookiest ghost", "un épouvantable spectre", /*spanish*/"el espectro más espeluznante"},
                       Text{"a sidequest spirit", "un précieux esprit", /*spanish*/"un gran espíritu"},
                     },
                       //clear text
                       Text{"a Big Poe Bottle", "une Ame en bouteille", /*spanish*/"un Gran Poe embotellado"}
  );

  HintText ShardOfAgony = HintText::Item({
                       //obscure text
                       Text{"the shake shard", "le fragment vibrant", /*spanish*/"el fragmento tintineante"},
                       Text{"a blue alarm", "une alerte bleue", /*spanish*/"una azul alarma"},
                     },
                       //clear text
                       Text{"the Shard of Agony", "le fragment de souffrance", /*spanish*/"la Piedra de la Agonía"}
  );

  HintText GerudoToken = HintText::Item({
                       //obscure text
                       Text{"a girl club membership", "une carte de membre", /*spanish*/"una fémina membresía"},
                       Text{"a desert tribe's pass", "un laissez-passer", /*spanish*/"el vale de la tribu del desierto"},
                     },
                       //clear text
                       Text{"the Gerudo Token", "la carte Gerudo", /*spanish*/"el pase de socio gerudo"}
  );

  HintText ProgressiveWallet = HintText::Item({
                       //obscure text
                       Text{"a mo' money holder", "un sac à sous", /*spanish*/"una cartera de dinero"},
                       Text{"a gem purse", "une sacoche", /*spanish*/"un zurrón de gemas"},
                       Text{"a portable bank", "une petite banque", /*spanish*/"un banco portable"},
                     },
                       //clear text
                       Text{"a Wallet", "une bourse", /*spanish*/"una bolsa de rupias"}
  );

  HintText ProgressiveStickCapacity = HintText::Item({
                       //obscure text
                       Text{"a lumber rack", "un paquet de bois", /*spanish*/"más bastones"},
                       Text{"more flammable twigs", "beaucoup de branches", /*spanish*/"más varas"},
                     },
                       //clear text
                       Text{"Deku Stick Capacity", "une augmentation de bâtons Mojo", /*spanish*/"mayor capacidad de palos deku"}
  );

  HintText ProgressiveNutCapacity = HintText::Item({
                       //obscure text
                       Text{"more nuts", "encore plus de noix", /*spanish*/"más semillas de nogal"},
                       Text{"flashbang storage", "un sac à noix", /*spanish*/"más frutos de aturdimiento"},
                     },
                       //clear text
                       Text{"Deku Nut Capacity", "une augmentation de noix Mojo", /*spanish*/"mayor capacidad de nueces deku"}
  );

  HintText HeartContainer = HintText::Item({
                       //obscure text
                       Text{"a lot of love", "le grand amour", /*spanish*/"amor por doquier"},
                       Text{"a Valentine's gift", "un cadeau de Saint-Valentin", /*spanish*/"un contenedor de afección"},
                       Text{"a boss's organ", "un organe de monstre", /*spanish*/"los órganos de un jefe"},
                     },
                       //clear text
                       Text{"a Heart Container", "un coeur d'énergie", /*spanish*/"un contenedor de corazón"}
  );

  HintText PieceOfHeart = HintText::Item({
                       //obscure text
                       Text{"a little love", "un peu plus d'amour", /*spanish*/"una pizca de amor"},
                       Text{"a broken heart", "un coeur brisé", /*spanish*/"un corazón roto"},
                     },
                       //clear text
                       Text{"a Piece of Heart", "un quart de coeur", /*spanish*/"una pieza de corazón"}
  );

  HintText TreasureGameHeart = HintText::Item({
                       //obscure text
                       Text{"a victory valentine", "un amour gagnant", /*spanish*/"el amor victorioso"},
                     },
                       //clear text
                       Text{"a Piece of Heart", "un quart de coeur", /*spanish*/"una pieza de corazón"}
  );

  HintText RecoveryHeart = HintText::Item({
                       //obscure text
                       Text{"a free heal", "de petits soins", /*spanish*/"una cura de regalo"},
                       Text{"a hearty meal", "un petit amour", /*spanish*/"una minúscula corazonada"},
                       Text{"a Band-Aid", "un diachylon", /*spanish*/"un corazoncito sanador"},
                     },
                       //clear text
                       Text{"a Recovery Heart", "un coeur de vie", /*spanish*/"un corazón"}
  );

  HintText TreasureGameGreenRupee = HintText::Item({
                       //obscure text
                       Text{"the dollar of defeat", "le rubis de la défaite", /*spanish*/"la moneda de la derrota"},
                     },
                       //clear text
                       Text{"a Green Rupee", "un rubis vert", /*spanish*/"una rupia verde"}
  );

  HintText DekuStick1 = HintText::Item({
                       //obscure text
                       Text{"a breakable branch", "une bout de bois", /*spanish*/"un pequeño báculo"},
                     },
                       //clear text
                       Text{"a Deku Stick", "un bâton Mojo", /*spanish*/"un palo deku"}
  );

  HintText GreenRupee = HintText::Item({
                       //obscure text
                       Text{"a unique coin", "un rubis bien mérité", /*spanish*/"una singular moneda"},
                       Text{"a penny", "un sou", /*spanish*/"un penique"},
                       Text{"a green gem", "un joyau vert", /*spanish*/"una gema verde"},
                     },
                       //clear text
                       Text{"a Green Rupee", "un rubis vert", /*spanish*/"una rupia verde"}
  );

  HintText BlueRupee = HintText::Item({
                       //obscure text
                       Text{"a common coin", "quelques sous", /*spanish*/"una moneda usual"},
                       Text{"a blue gem", "un joyau bleu", /*spanish*/"una gema azul"},
                     },
                       //clear text
                       Text{"a Blue Rupee", "un rubis bleu", /*spanish*/"una rupia azul"}
  );

  HintText RedRupee = HintText::Item({
                       //obscure text
                       Text{"couch cash", "un peu de fric", /*spanish*/"una buena moneda"},
                       Text{"a red gem", "un joyau rouge", /*spanish*/"una gema roja"},
                     },
                       //clear text
                       Text{"a Red Rupee", "un rubis rouge", /*spanish*/"una rupia roja"}
  );

  HintText PurpleRupee = HintText::Item({
                       //obscure text
                       Text{"big bucks", "plein de fric", /*spanish*/"plata de calidad"},
                       Text{"a purple gem", "un joyau mauve", /*spanish*/"una gema morada"},
                       Text{"wealth", "la richesse", /*spanish*/"unos buenos cuartos"},
                     },
                       //clear text
                       Text{"a Purple Rupee", "un rubis pourpre", /*spanish*/"una rupia morada"}
  );

  HintText HugeRupee = HintText::Item({
                       //obscure text
                       Text{"a juicy jackpot", "le jackpot", /*spanish*/"el premio gordo"},
                       Text{"a yellow gem", "un joyau doré", /*spanish*/"una gema amarilla"},
                       Text{"a giant gem", "un gros joyau", /*spanish*/"una gema descomunal"},
                       Text{"great wealth", "l'aisance financière", /*spanish*/"dinero a caudales"},
                     },
                       //clear text
                       Text{"a Huge Rupee", "un énorme rubis", /*spanish*/"una rupia gigante"}
  );

  HintText WeirdEgg = HintText::Item({
                       //obscure text
                       Text{"a chicken dilemma", "un drôle d'ovale", /*spanish*/"el dilema de la gallina"},
                     },
                       //clear text
                       Text{"the Weird Egg", "l'oeuf curieux", /*spanish*/"el huevo extraño"}
  );

  HintText ZeldasLetter = HintText::Item({
                       //obscure text
                       Text{"an autograph", "un autographe", /*spanish*/"un autógrafo"},
                       Text{"royal stationery", "du papier royal", /*spanish*/"un escrito real"},
                       Text{"royal snail mail", "une enveloppe royale", /*spanish*/"correo de la realeza"},
                     },
                       //clear text
                       Text{"Zelda's Letter", "la Lettre de Zelda", /*spanish*/"la carta de Zelda"}
  );

  HintText PocketEgg = HintText::Item({
                       //obscure text
                       Text{"a Cucco container", "un réservoir à Cocotte", /*spanish*/"contenedor de cuco"},
                       Text{"a Cucco, eventually", "un poussin éventuel", /*spanish*/"un futuro cuco"},
                       Text{"a fowl youth", "une omelette crue", /*spanish*/"una dulce juventud"},
                     },
                       //clear text
                       Text{"the Pocket Egg", "l'oeuf de poche", /*spanish*/"el huevo de bolsillo"}
  );

  HintText PocketCucco = HintText::Item({
                       //obscure text
                       Text{"a little clucker", "un petit glousseur", /*spanish*/"un pequeñajo pollito"},
                     },
                       //clear text
                       Text{"the Pocket Cucco", "le Cocotte de poche", /*spanish*/"el cuco de bolsillo"}
  );

  HintText Cojiro = HintText::Item({
                       //obscure text
                       Text{"a cerulean capon", "un paon azur", /*spanish*/"un cerúleo capón"},
                     },
                       //clear text
                       Text{"Cojiro", "le p'tit poulet", /*spanish*/"Cojiro"}
  );

  HintText OddMushroom = HintText::Item({
                       //obscure text
                       Text{"a powder ingredient", "un ingrédient à poudre", /*spanish*/"un oloroso ingrediente"},
                     },
                       //clear text
                       Text{"an Odd Mushroom", "un champignon suspect", /*spanish*/"una seta rara"}
  );

  HintText OddPoultice = HintText::Item({
                       //obscure text
                       Text{"Granny's goodies", "les confiseries de mamie", /*spanish*/"la especialidad de la abuela"},
                     },
                       //clear text
                       Text{"an Odd Potion", "une mixture suspecte", /*spanish*/"una medicina rara"}
  );

  HintText PoachersSaw = HintText::Item({
                       //obscure text
                       Text{"a tree killer", "un coupeur d'arbres", /*spanish*/"un destructor de árboles"},
                     },
                       //clear text
                       Text{"the Poacher's Saw", "la scie du chasseur", /*spanish*/"la sierra del furtivo"}
  );

  HintText BrokenSword = HintText::Item({
                       //obscure text
                       Text{"a shattered slicer", "une arme cassée", /*spanish*/"una rebanadora rota"},
                     },
                       //clear text
                       Text{"the Broken Sword", "l'épée brisée de Goron", /*spanish*/"la espada goron rota"}
  );

  HintText Prescription = HintText::Item({
                       //obscure text
                       Text{"a pill pamphlet", "un document urgent", /*spanish*/"un instructivo medicinal"},
                       Text{"a doctor's note", "un papier médical", /*spanish*/"unas notas del doctor"},
                     },
                       //clear text
                       Text{"the Prescription", "une ordonnance", /*spanish*/"la receta"}
  );

  HintText EyeballFrog = HintText::Item({
                       //obscure text
                       Text{"a perceiving polliwog", "un amphibien", /*spanish*/"un variopinto batracio"},
                     },
                       //clear text
                       Text{"the Eyeball Frog", "le crapaud-qui-louche", /*spanish*/"la rana de ojos saltones"}
  );

  HintText Eyedrops = HintText::Item({
                       //obscure text
                       Text{"a vision vial", "une solution oculaire", /*spanish*/"un remedio para la vista"},
                     },
                       //clear text
                       Text{"the Eyedrops", "les super gouttes", /*spanish*/"las supergotas oculares"}
  );

  HintText ClaimCheck = HintText::Item({
                       //obscure text
                       Text{"a three day wait", "un rendez-vous dans trois jours", /*spanish*/"unos tres días de espera"},
                     },
                       //clear text
                       Text{"the Claim Check", "un certificat", /*spanish*/"el albarán"}
  );

  HintText Map = HintText::Item({
                       //obscure text
                       Text{"a dungeon atlas", "un atlas sous-terrain", /*spanish*/"el atlas de una mazmorra"},
                       Text{"blueprints", "des plans", /*spanish*/"unos planos"},
                     },
                       //clear text
                       Text{"a Map", "une carte", /*spanish*/"un mapa"}
  );

  HintText Compass = HintText::Item({
                       //obscure text
                       Text{"a treasure tracker", "un cherche-trésor", /*spanish*/"un buscatesoros"},
                       Text{"a magnetic needle", "une aiguille magnétique", /*spanish*/"una aguja magnética"},
                     },
                       //clear text
                       Text{"a Compass", "une Boussole", /*spanish*/"una brújula"}
  );

  HintText BossKey = HintText::Item({
                       //obscure text
                       Text{"a master of unlocking", "un anti-grosse porte", /*spanish*/"la clave de un jefe"},
                       Text{"a dungeon's master pass", "une clé maléfique", /*spanish*/"el pase maestro de una mazmorra"},
                     },
                       //clear text
                       Text{"a Boss Key", "une clé d'or", /*spanish*/"una gran llave"}
  );

  HintText GanonsBossKey = HintText::Item({
                       //obscure text
                       Text{"a master of unlocking", "un anti-grosse porte", /*spanish*/"la clave de un jefe"},
                       Text{"a dungeon's master pass", "une clé maléfique", /*spanish*/"el pase maestro de una mazmorra"},
                     },
                       //clear text
                       Text{"a Boss Key", "une clé d'or", /*spanish*/"una gran llave"}
  );

  HintText SmallKey = HintText::Item({
                       //obscure text
                       Text{"a tool for unlocking", "un anti-porte", /*spanish*/"una clave de una entrada"},
                       Text{"a dungeon pass", "le rêve d'un prisonnier", /*spanish*/"un pase de una mazmorra"},
                       Text{"a lock remover", "un efface-serrure", /*spanish*/"un destructor de cerraduras"},
                       Text{"a lockpick", "un crochet à porte", /*spanish*/"una ganzúa"},
                     },
                       //clear text
                       Text{"a Small Key", "une petite clé", /*spanish*/"una llave pequeña"}
  );

  HintText FortressSmallKey = HintText::Item({
                       //obscure text
                       Text{"a get out of jail free card", "le rêve des charpentiers", /*spanish*/"una clave de una celda"},
                     },
                       //clear text
                       Text{"a Jail Key", "une clé de prison", /*spanish*/"una llave de la celda"}
  );

  HintText KokiriEmerald = HintText::Item({
                       //obscure text
                       Text{"a green stone", "une pierre verte", /*spanish*/"una piedra verdemar"},
                       Text{"a gift before death", "le dernier souffle d'un arbre", /*spanish*/"un regalo antes de fallecer"},
                     },
                       //clear text
                       Text{"the Kokiri Emerald", "l'émeraude Kokiri", /*spanish*/"la Esmeralda Kokiri"}
  );

  HintText GoronRuby = HintText::Item({
                       //obscure text
                       Text{"a red stone", "une pierre rouge", /*spanish*/"una piedra carmín"},
                       Text{"sworn brotherhood", "un serment de fraternité", /*spanish*/"el juramento de hermanos de sangre"},
                     },
                       //clear text
                       Text{"the Goron Ruby", "le rubis Goron", /*spanish*/"el Rubí Goron"}
  );

  HintText ZoraSapphire = HintText::Item({
                       //obscure text
                       Text{"a blue stone", "une pierre bleue", /*spanish*/"una piedra celeste"},
                       Text{"an engagement gift", "un cadeau de mariage", /*spanish*/"un regalo de compromiso"},
                     },
                       //clear text
                       Text{"the Zora Sapphire", "le saphir Zora", /*spanish*/"el Zafiro Zora"}
  );

  HintText ForestMedallion = HintText::Item({
                       //obscure text
                       Text{"a green coin", "une pièce verte", /*spanish*/"una moneda esmeralda"},
                       Text{"Saria's friendship", "l'amitié de Saria", /*spanish*/"la amistad de Saria"},
                     },
                       //clear text
                       Text{"the Forest Medallion", "le médaillon de la forêt", /*spanish*/"el Medallón del Bosque"}
  );

  HintText FireMedallion = HintText::Item({
                       //obscure text
                       Text{"a red coin", "une pièce rouge", /*spanish*/"una moneda carmesí"},
                       Text{"Darunia's power", "la fraternité de Darunia", /*spanish*/"el poder de Darunia"},
                     },
                       //clear text
                       Text{"the Fire Medallion", "le médaillon du feu", /*spanish*/"el Medallón del Fuego"}
  );

  HintText WaterMedallion = HintText::Item({
                       //obscure text
                       Text{"a blue coin", "une pièce bleue", /*spanish*/"una moneda azur"},
                       Text{"Ruto's power", "l'amour de Ruto", /*spanish*/"el poder de Ruto"},
                     },
                       //clear text
                       Text{"the Water Medallion", "le médaillon de l'eau", /*spanish*/"el Medallón del Agua"}
  );

  HintText SpiritMedallion = HintText::Item({
                       //obscure text
                       Text{"an orange coin", "une pièce orange", /*spanish*/"una moneda ámbar"},
                       Text{"Nabooru's power", "le respect de Nabooru", /*spanish*/"el poder de Nabooru"},
                     },
                       //clear text
                       Text{"the Spirit Medallion", "le médaillon de l'esprit", /*spanish*/"el Medallón del Espíritu"}
  );

  HintText ShadowMedallion = HintText::Item({
                       //obscure text
                       Text{"a purple coin", "une pièce pourpre", /*spanish*/"una moneda malva"},
                       Text{"Impa's power", "la confiance d'Impa", /*spanish*/"el poder de Impa"},
                     },
                       //clear text
                       Text{"the Shadow Medallion", "le médaillon de l'ombre", /*spanish*/"el Medallón de la Sombra"}
  );

  HintText LightMedallion = HintText::Item({
                       //obscure text
                       Text{"a yellow coin", "une pièce jaune", /*spanish*/"una moneda áurea"},
                       Text{"Rauru's power", "la foi de Rauru", /*spanish*/"el poder de Rauru"},
                     },
                       //clear text
                       Text{"the Light Medallion", "le médaillon de la lumière", /*spanish*/"el Medallón de la Luz"}
  );

  // HintText HintError = HintText::Item({
  //                      //obscure text
  //                      Text{"something mysterious", "un sacré mystère", /*spanish*/"algo misterioso"},
  //                      Text{"an unknown treasure", "un trésor inconnu", /*spanish*/"un desconocido tesoro"},
  //                    },
  //                      //clear text
  //                      Text{"An Error (Please Report This)", "une erreur (signaler S.V.P.)", /*spanish*/"Error (Repórtelo si es posible)"}
  // );

  HintText Arrows5 = HintText::Item({
                       //obscure text
                       Text{"a few danger darts", "quelques obus", /*spanish*/"un par de peligrosos dardos"},
                       Text{"a few sharp shafts", "quelques piquets", /*spanish*/"un par de puntas afiladas"},
                     },
                       //clear text
                       Text{"Arrows (5 pieces)", "5 flèches", /*spanish*/"unas (5) flechas"}
  );

  HintText Arrows10 = HintText::Item({
                       //obscure text
                       Text{"some danger darts", "un paquet d'obus", /*spanish*/"unos cuantos peligrosos dardos"},
                       Text{"some sharp shafts", "un paquet de piquets", /*spanish*/"unas cuantas puntas afiladas"},
                     },
                       //clear text
                       Text{"Arrows (10 pieces)", "10 flèches", /*spanish*/"unas (10) flechas"}
  );

  HintText Arrows30 = HintText::Item({
                       //obscure text
                       Text{"plenty of danger darts", "beaucoup d'obus", /*spanish*/"bastantes peligrosos dardos"},
                       Text{"plenty of sharp shafts", "beaucoup de piquets", /*spanish*/"bastantes puntas afiladas"},
                     },
                       //clear text
                       Text{"Arrows (30 pieces)", "30 flèches", /*spanish*/"unas (30) flechas"}
  );

  HintText Bombs5 = HintText::Item({
                       //obscure text
                       Text{"a few explosives", "quelques pétards", /*spanish*/"un par de explosivos"},
                       Text{"a few blast balls", "quelques boules bleues", /*spanish*/"un par de estallidos"},
                     },
                       //clear text
                       Text{"Bombs (5 pieces)", "5 bombes", /*spanish*/"unas (5) bombas"}
  );

  HintText Bombs10 = HintText::Item({
                       //obscure text
                       Text{"some explosives", "un paquet de pétards", /*spanish*/"unos cuantos explosivos"},
                       Text{"some blast balls", "un paquet de boules bleues", /*spanish*/"unos cuantos estallidos"},
                     },
                       //clear text
                       Text{"Bombs (10 pieces)", "10 bombes", /*spanish*/"unas (10) bombas"}
  );

  HintText Bombs20 = HintText::Item({
                       //obscure text
                       Text{"lots-o-explosives", "beaucoup de pétards", /*spanish*/"un puñado de explosivos"},
                       Text{"plenty of blast balls", "beaucoup de boules bleues", /*spanish*/"bastantes estallidos"},
                     },
                       //clear text
                       Text{"Bombs (20 pieces)", "20 bombes", /*spanish*/"unas (20) bombas"}
  );

  HintText IceTrap = HintText::Item({
                       //obscure text
                       Text{"a gift from Ganon", "un cadeau de Ganon", /*spanish*/"un regalo de Ganon"},
                       Text{"a chilling discovery", "une frissonante découverte", /*spanish*/"un escalofriante hallazgo"},
                       Text{"frosty fun", "une engelure", /*spanish*/"una gélida diversión"},
                     },
                       //clear text
                       Text{"an Ice Trap", "un piège de glace", /*spanish*/"una trampa de hielo"}
  );

  HintText MagicBean = HintText::Item({
                       //obscure text
                       Text{"a wizardly legume", "un légume ensorcelé", /*spanish*/"una legumbre mágica"},
                     },
                       //clear text
                       Text{"a Magic Bean", "des haricots magiques", /*spanish*/"una judía mágica"}
  );

  HintText MagicBeanPack = HintText::Item({
                       //obscure text
                       Text{"wizardly legumes", "des légumes ensorcelés", /*spanish*/"unas legumbres mágicas"},
                     },
                       //clear text
                       Text{"Magic Beans", "plein de haricots magiques", /*spanish*/"unas judías mágicas"}
  );

  HintText ProgressiveBombchus = HintText::Item({
                       //obscure text
                       Text{"mice bombs", "de mignons explosifs", /*spanish*/"unas bombas roedoras"},
                       Text{"proximity mice", "un jouet à remonter", /*spanish*/"unos explosivos ratoncitos"},
                       Text{"wall crawlers", "de rapides grimpeurs", /*spanish*/"unos trepaparedes"},
                       Text{"trail blazers", "des zigzags éclatants", /*spanish*/"unas ratas propulsadas"},
                     },
                       //clear text
                       Text{"Bombchus", "un missile", /*spanish*/"unos bombchus"}
  );

  HintText Bombchus5 = HintText::Item({
                       //obscure text
                       Text{"a few mice bombs", "quelques mignons explosifs", /*spanish*/"un par de bombas roedoras"},
                       Text{"a few proximity mice", "quelques jouets à remonter", /*spanish*/"un par de explosivos ratoncitos"},
                       Text{"a few wall crawlers", "quelques rapides grimpeurs", /*spanish*/"un par de trepaparedes"},
                       Text{"a few trail blazers", "quelques zigzags éclatants", /*spanish*/"un par de ratas propulsadas"},
                     },
                       //clear text
                       Text{"Bombchus (5 pieces)", "5 missiles", /*spanish*/"unos (5) bombchus"}
  );

  HintText Bombchus10 = HintText::Item({
                       //obscure text
                       Text{"some mice bombs", "un paquet de mignons explosifs", /*spanish*/"unas cuantas bombas roedoras"},
                       Text{"some proximity mice", "un paquet de jouets à remonter", /*spanish*/"unos cuantos explosivos ratoncitos"},
                       Text{"some wall crawlers", "un paquet de rapides grimpeurs", /*spanish*/"unos cuantos trepaparedes"},
                       Text{"some trail blazers", "un paquet de zigzags éclatants", /*spanish*/"unas cuantas ratas propulsadas"},
                     },
                       //clear text
                       Text{"Bombchus (10 pieces)", "10 missiles", /*spanish*/"unos (10) bombchus"}
  );

  HintText Bombchus20 = HintText::Item({
                       //obscure text
                       Text{"plenty of mice bombs", "beaucoup de mignons explosifs", /*spanish*/"bastantes bombas roedoras"},
                       Text{"plenty of proximity mice", "beaucoup de jouets à remonter", /*spanish*/"bastantes explosivos ratoncitos"},
                       Text{"plenty of wall crawlers", "beaucoup de rapides grimpeurs", /*spanish*/"bastantes trepaparedes"},
                       Text{"plenty of trail blazers", "beaucoup de zigzags éclatants", /*spanish*/"bastantes ratas propulsadas"},
                     },
                       //clear text
                       Text{"Bombchus (20 pieces)", "20 missiles", /*spanish*/"unos (20) bombchus"}
  );

  HintText DekuNuts5 = HintText::Item({
                       //obscure text
                       Text{"some nuts", "quelques noisettes", /*spanish*/"un par de nueces"},
                       Text{"some flashbangs", "quelques éclats", /*spanish*/"un par de semillas de aturdimiento"},
                       Text{"some scrub spit", "quelques crachats Mojo", /*spanish*/"un par de escupitajos deku"},
                     },
                       //clear text
                       Text{"Deku Nuts (5 pieces)", "5 noix Mojo", /*spanish*/"unas (5) nueces deku"}
  );

  HintText DekuNuts10 = HintText::Item({
                       //obscure text
                       Text{"lots-o-nuts", "un paquet de noisettes", /*spanish*/"un puñado de nueces"},
                       Text{"plenty of flashbangs", "un paquet d'éclats", /*spanish*/"unas cuantas semillas de aturdimiento"},
                       Text{"plenty of scrub spit", "un paquet de crachats Mojo", /*spanish*/"unos cuantos escupitajos deku"},
                     },
                       //clear text
                       Text{"Deku Nuts (10 pieces)", "10 noix Mojo", /*spanish*/"unas (10) nueces deku"}
  );

  HintText DekuSeeds30 = HintText::Item({
                       //obscure text
                       Text{"catapult ammo", "de délicieuses munitions", /*spanish*/"una buena munición infantil"},
                       Text{"lots-o-seeds", "quelques germes séchés", /*spanish*/"un puñado de semillas"},
                     },
                       //clear text
                       Text{"Deku Seeds (30 pieces)", "30 graines Mojo", /*spanish*/"unas (30) semillas deku"}
  );

  HintText GoldSkulltulaToken = HintText::Item({
                       //obscure text
                       Text{"proof of destruction", "un certificat d'élimination", /*spanish*/"una prueba de la destrucción"},
                       Text{"an arachnid chip", "un jeton cranien", /*spanish*/"una figura arácnida"},
                       Text{"spider remains", "une dépouille dorée", /*spanish*/"los restos de una araña"},
                       Text{"one percent of a curse", "un centième de malédiction", /*spanish*/"un uno por ciento de una maldición"},
                     },
                       //clear text
                       Text{"a Gold Skulltula Token", "un symbole de Skulltula d'or", /*spanish*/"un símbolo de skulltula dorada"}
  );

  /*--------------------------
  |     ALWAYS HINT TEXT     |
  ---------------------------*/

  HintText ZR_FrogsOcarinaGame = HintText::Always({
                       //obscure text
                       Text{"an #amphibian feast# yields", "le #festin d'amphibiens# donne", /*spanish*/"una #fiesta anfibia# brinda"},
                       Text{"the #croaking choir's magnum opus# awards", "la #chorale coassante# donne", /*spanish*/"un #coro maestro de ancas# premia"},
                       Text{"the #froggy finale# yields", "la #finale amphibienne# donne", /*spanish*/"el #gran final batracio# brinda"},
                     },
                       //clear text
                       Text{"the final reward from the #Frogs of Zora's River# is", "la dernière récompense des #grenouilles du fleuve zora# est", /*spanish*/"la recompensa final de las #ranas del Río Zora# premia"}
  );

  HintText KF_LinksHouseCow = HintText::Always({
                       //obscure text
                       Text{"the #bovine bounty of a horseback hustle# gifts", "le cadeau #qui découle d'une réussite équestre# est", /*spanish*/"la #recompensa bovina de un paseo a caballo# brinda"},
                     },
                       //clear text
                       Text{"#Malon's obstacle course# leads to", "la #course à obstacle de Malon# amène à", /*spanish*/"la #carrera de obstáculos de Malon# brinda"}
  );

  /*--------------------------
  |    SOMETIMES HINT TEXT   |
  ---------------------------*/

  HintText SongFromOcarinaOfTime = HintText::Sometimes({
                       //obscure text
                       Text{"the #Ocarina of Time# teaches", "l'#ocarina du temps# est accompagné par", /*spanish*/"la #Ocarina del Tiempo# enseña"},
  });

  HintText SongFromComposersGrave = HintText::Sometimes({
                       //obscure text
                       Text{"#ReDead in the Composers' Grave# guard", "les #Effrois du tombeau des compositeurs# protègent", /*spanish*/"los #ReDeads del Panteón Real# guardan"},
                       Text{"the #Composer Brothers wrote#", "le #trésor des compositeurs# est", /*spanish*/"los #hermanos compositores escribieron#"},
  });

  HintText SheikInForest = HintText::Sometimes({
                       //obscure text
                       Text{"#in a meadow# Sheik teaches", "Sheik confiera, #dans une clairière#,", /*spanish*/"#en la pradera sagrada# Sheik enseña"},
  });

  HintText SheikAtTemple = HintText::Sometimes({
                       //obscure text
                       Text{"Sheik waits at a #monument to time# to teach", "Sheik confiera, #au pied de l'épée légendaire#,", /*spanish*/"Sheik espera en el #momumento del tiempo# para enseñar"},
  });

  HintText SheikInCrater = HintText::Sometimes({
                       //obscure text
                       Text{"the #crater's melody# is", "Sheik confiera, #entouré de lave#,", /*spanish*/"la #melodía del cráter# otorga"},
  });

  HintText SheikInIceCavern = HintText::Sometimes({
                       //obscure text
                       Text{"the #frozen cavern# echoes with", "Sheik confiera, #dans une caverne étoilée#,", /*spanish*/"en la #caverna de hielo# retumban los ecos de"},
  });

  HintText SheikInKakariko = HintText::Sometimes({
                       //obscure text
                       Text{"a #ravaged village# mourns with", "Sheik confirera, #au coeur d'un village ravagé#,", /*spanish*/"un #arrasado pueblo# llora"},
  });

  HintText SheikAtColossus = HintText::Sometimes({
                       //obscure text
                       Text{"a hero ventures #beyond the wasteland# to learn", "Sheik confiera, #au bout d'un chemin sableux#,", /*spanish*/"el héroe que se adentre #más allá del desierto encantado# aprenderá"},
  });


  HintText MK_10BigPoes = HintText::Sometimes({
                       //obscure text
                       Text{"#ghost hunters# will be rewarded with", "#les chasseurs de fantômes# sont récompensés avec", /*spanish*/"los #cazafantasmas# son premiados con"},
                     },
                       //clear text
                       Text{"catching #Big Poes# leads to", "#d'attraper des fantômes# donne", /*spanish*/"hacerte con #Grandes Poes# conduce a"}
  );

  HintText DekuTheater_SkullMask = HintText::Sometimes({
                       //obscure text
                       Text{"the #Skull Mask# yields", "le #masque de mort# donne", /*spanish*/"la #máscara de calavera# otorga"},
  });

  HintText DekuTheater_MaskOfTruth = HintText::Sometimes({
                       //obscure text
                       Text{"showing a #truthful eye to the crowd# rewards", "montrer #l'oeil de vérité à la foule# donne", /*spanish*/"#mostrarle el ojo verdadero# a una multitud brinda"},
                     },
                       //clear text
                       Text{"the #Mask of Truth# yields", "le #masque de vérité# donne", /*spanish*/"la #máscara de la verdad# premia"}
  );

  HintText HF_OcarinaOfTimeItem = HintText::Sometimes({
                       //obscure text
                       Text{"the #treasure thrown by Princess Zelda# is", "le trésor #laissé par la princesse# est", /*spanish*/"el #tesoro arrojado por la Princesa Zelda# se trata de"},
  });

  HintText DMT_Biggoron = HintText::Sometimes({
                       //obscure text
                       Text{"#Biggoron# crafts", "#Biggoron# fabrique", /*spanish*/"#Biggoron# forja"},
  });

  HintText Kak_50GoldSkulltulaReward = HintText::Sometimes({
                       //obscure text
                       Text{"#50 bug badges# rewards", "#50 écussons# donnent", /*spanish*/"#50 medallas de insectos# otorgan"},
                       Text{"#50 spider souls# yields", "#50 âmes# donnent", /*spanish*/"#50 almas de araña# otorgan"},
                       Text{"#50 auriferous arachnids# lead to", "#50 arachnides aurifères# donnent", /*spanish*/"#50 arácnidos auríferos# otorgan"},
                     },
                       //clear text
                       Text{"slaying #50 Gold Skulltulas# reveals", "détruire #50 Skulltulas d'or# donne", /*spanish*/"exterminar #50 skulltulas doradas# revela"}
  );

  HintText Kak_40GoldSkulltulaReward = HintText::Sometimes({
                       //obscure text
                       Text{"#40 bug badges# rewards", "#40 écussons# donnent", /*spanish*/"#40 medallas de insectos# otorgan"},
                       Text{"#40 spider souls# yields", "#40 âmes# donnent", /*spanish*/"#40 almas de araña# otorgan"},
                       Text{"#40 auriferous arachnids# lead to", "#40 arachnides aurifères# donnent", /*spanish*/"#40 arácnidos auríferos# otorgan"},
                     },
                       //clear text
                       Text{"slaying #40 Gold Skulltulas# reveals", "détruire #40 Skulltulas d'or# donne", /*spanish*/"exterminar #40 skulltulas doradas# revela"}
  );

  HintText Kak_30GoldSkulltulaReward = HintText::Sometimes({
                       //obscure text
                       Text{"#30 bug badges# rewards", "#30 écussons# donnent", /*spanish*/"#30 medallas de insectos# otorgan"},
                       Text{"#30 spider souls# yields", "#30 âmes# donnent", /*spanish*/"#30 almas de araña# otorgan"},
                       Text{"#30 auriferous arachnids# lead to", "#30 arachnides aurifères# donnent", /*spanish*/"#30 arácnidos auríferos# otorgan"},
                     },
                       //clear text
                       Text{"slaying #30 Gold Skulltulas# reveals", "détruire #30 Skulltulas d'or# donne", /*spanish*/"exterminar #30 skulltulas doradas# revela"}
  );

  HintText Kak_20GoldSkulltulaReward = HintText::Sometimes({
                       //obscure text
                       Text{"#20 bug badges# rewards", "#20 écussons# donnent", /*spanish*/"#20 medallas de insectos# otorgan"},
                       Text{"#20 spider souls# yields", "#20 âmes# donnent", /*spanish*/"#20 almas de araña# otorgan"},
                       Text{"#20 auriferous arachnids# lead to", "#20 arachnides aurifères# donnent", /*spanish*/"#20 arácnidos auríferos# otorgan"},
                     },
                       //clear text
                       Text{"slaying #20 Gold Skulltulas# reveals", "détruire #20 Skulltulas d'or# donne", /*spanish*/"exterminar #20 skulltulas doradas# revela"}
  );

  HintText Kak_AnjuAsChild = HintText::Sometimes({
                       //obscure text
                       Text{"#wrangling roosters# rewards", "#plumer des poulets# donne", /*spanish*/"#pillar a las gallinas# premia"},
                       Text{"#chucking chickens# gifts", "#lancer des poulets# donne", /*spanish*/"#reunir a unos emplumados# premia"},
                     },
                       //clear text
                       Text{"#collecting cuccos# rewards", "#rapporter les Cocottes# donne", /*spanish*/"#hacerte con todos los cucos# premia"}
  );

  HintText GC_DaruniasJoy = HintText::Sometimes({
                       //obscure text
                       Text{"a #groovin' goron# gifts", "#le Goron joyeux# donne", /*spanish*/"#un gerudo marchoso# otorga"},
                     },
                       //clear text
                       Text{"#Darunia's dance# leads to", "#la dance de Darunia# donne", /*spanish*/"#el baile de Darunia# conduce a"}
  );

  HintText LW_SkullKid = HintText::Sometimes({
                       //obscure text
                       Text{"the #Skull Kid# grants", "le #Skull Kid# donne", /*spanish*/"#Skull Kid# otorga"},
  });

  HintText LH_Sun = HintText::Sometimes({
                       //obscure text
                       Text{"staring into #the sun# grants", "regarder #le soleil# donne", /*spanish*/"#mirar al sol# revela"},
                     },
                       //clear text
                       Text{"shooting #the sun# grants", "tirer une flèche dans #sur le soleil# donne", /*spanish*/"#disparar al sol# revela"}
  );

  HintText MK_TreasureChestGameReward = HintText::Sometimes({
                       //obscure text
                       Text{"#gambling# grants", "#parier# donne", /*spanish*/"#los juegos de azar# revelan"},
                       Text{"there is a #1/32 chance# to win", "d'être #le gagnant parmi 32# donne", /*spanish*/"hay una #probabilidad de 1/32# de ganar"},
                     },
                       //clear text
                       Text{"the #treasure chest game# grants", "la #chasse aux trésors# donne", /*spanish*/"#el Cofre del Tesoro# premia"}
  );

  HintText GF_HBA1500Points = HintText::Sometimes({
                       //obscure text
                       Text{"mastery of #horseback archery# grants", "de maîtriser l'#archerie équestre# donne", /*spanish*/"amaestrar el #tiro con arco a caballo# premia"},
                     },
                       //clear text
                       Text{"scoring 1500 in #horseback archery# grants", "d'obtenir 1500 points dans l'#archerie équestre# donne", /*spanish*/"conseguir 1500 puntos en el #tiro con arco a caballo# premia"}
  );

  HintText GY_HeartPieceGraveChest = HintText::Sometimes({
                       //obscure text
                       Text{"playing #Sun's Song# in a grave spawns", "jouer le #chant du soleil# dans un tombeau donne", /*spanish*/"#tocar la Canción del Sol# en una cripta conduce a"},
  });

  HintText GC_MazeLeftChest = HintText::Sometimes({
                       //obscure text
                       Text{"in #Goron City# the hammer unlocks", "dans le #village Goron#, le marteau donne accès à", /*spanish*/"en la #Ciudad Goron# el martillo desbloquea"},
  });

  HintText GV_Chest = HintText::Sometimes({
                       //obscure text
                       Text{"in #Gerudo Valley# the hammer unlocks", "dans la #vallée Gerudo#, le marteau donne accès à", /*spanish*/"en el #Valle Gerudo# el martillo desbloquea"},
  });

  HintText GV_Cow = HintText::Sometimes({
                       //obscure text
                       Text{"a #cow in Gerudo Valley# gifts", "la #vache de la vallée Gerudo# donne", /*spanish*/"una #vaca del Valle Gerudo# brinda"},
  });

  HintText HC_GS_StormsGrotto = HintText::Sometimes({
                       //obscure text
                       Text{"a #spider behind a muddy wall# in a grotto holds", "l'#araignée derrière un mur de boue# dans une grotte donne", /*spanish*/"una #araña tras una agrietada pared# de una cueva otorga"},
  });

  HintText HF_GS_CowGrotto = HintText::Sometimes({
                       //obscure text
                       Text{"a #spider behind webs# in a grotto holds", "l'#araignée derrière une toile# dans une grotte donne", /*spanish*/"una #araña tras una telaraña# de una cueva otorga"},
  });

  HintText HF_CowGrottoCow = HintText::Sometimes({
                       //obscure text
                       Text{"the #cobwebbed cow# gifts", "la #vache prisonnière d'araignées# donne", /*spanish*/"la #vaca tras una telaraña# brinda"},
                     },
                       //clear text
                       Text{"a #cow behind webs# in a grotto gifts", "la #vache derrière les toiles# d'une grotte donne", /*spanish*/"una #vaca tras una telaraña# de una cueva brinda"}
  );

  HintText ZF_GS_HiddenCave = HintText::Sometimes({
                       //obscure text
                       Text{"a spider high #above the icy waters# holds", "l'araignée #en haut des eaux glacées# donne", /*spanish*/"una araña en lo #alto de las congeladas aguas# otorga"},
  });

  HintText HW_Chest = HintText::Sometimes({
                       //obscure text
                       Text{"#deep in the wasteland# is", "#loin dans le désert# gît", /*spanish*/"en lo #profundo del desierto encantado# yace"},
                       Text{"beneath #the sands#, flames reveal", "#sous le désert#, les flammes font apparaître", /*spanish*/"tras las #arenas#, unas llamas revelan"},
  });

  HintText HW_GS = HintText::Sometimes({
                       //obscure text
                       Text{"a #spider in the wasteland# holds", "#l'araignée dans le désert# donne", /*spanish*/"una #araña del desierto encantado# otorga"},
  });

  HintText GY_ComposersGraveChest = HintText::Sometimes({
                       //obscure text
                       Text{"#flames in the Composers' Grave# reveal", "#les flammes dans le tombeau des compositeurs# cachent", /*spanish*/"#las llamas del Panteón Real# revelan"},
                       Text{"the #Composer Brothers hid#", "#les Frères compositeurs on caché#", /*spanish*/"los #hermanos compositores esconden#"},
  });

  HintText ZF_BottomFreestandingPoH = HintText::Sometimes({
                       //obscure text
                       Text{"#under the icy waters# lies", "#sous les eaux glacées# se cache", /*spanish*/"#bajo las congeladas aguas# yace"},
  });

  HintText GC_PotFreestandingPoH = HintText::Sometimes({
                       //obscure text
                       Text{"spinning #Goron pottery# contains", "la #potterie Goron# contient", /*spanish*/"una #cerámica goron# contiene"},
  });

  HintText ZD_KingZoraThawed = HintText::Sometimes({
                       //obscure text
                       Text{"a #defrosted dignitary# gifts", "le #monarque libéré# donne", /*spanish*/"una #Alteza descongelada# brinda"},
                     },
                       //clear text
                       Text{"unfreezing #King Zora# grants", "dégeler # le Roi Zora# donne", /*spanish*/"#descongelar al Rey Zora# conduce a"}
  );

  HintText DMC_DekuScrub = HintText::Sometimes({
                       //obscure text
                       Text{"a single #scrub in the crater# sells", "la #peste Mojo dans le cratère# vend", /*spanish*/"un solitario #deku del cráter# vende"},
  });

  HintText DMC_GS_Crate = HintText::Sometimes({
                       //obscure text
                       Text{"a spider under a #crate in the crater# holds", "la Skulltula dans une #boîte volcanique# a", /*spanish*/"una araña bajo una #caja del cráter# otorga"},
  });


  HintText DekuTree_MQ_AfterSpinningLogChest = HintText::Sometimes({
                       //obscure text
                       Text{"a #temporal stone within a tree# contains", "la #pierre bleue dans un arbre# mène à", /*spanish*/"un #bloque temporal de un árbol# contiene"},
                     },
                       //clear text
                       Text{"a #temporal stone within the Deku Tree# contains", "la #pierre temporelle dans l'arbre Mojo# cache", /*spanish*/"un #bloque temporal del Árbol Deku# contiene"}
  );

  HintText DekuTree_MQ_GS_BasementGravesRoom = HintText::Sometimes({
                       //obscure text
                       Text{"a #spider on a ceiling in a tree# holds", "l'#araignée haut-perchée dans un arbre# a", /*spanish*/"una #araña en el techo de un árbol# otorga"},
                     },
                       //clear text
                       Text{"a #spider on a ceiling in the Deku Tree# holds", "la#Skulltula dans le cimetière de l'arbre Mojo# a", /*spanish*/"una #araña en el techo del Árbol Deku# otorga"}
  );

  HintText DodongosCavern_MQ_GS_SongOfTimeBlockRoom = HintText::Sometimes({
                       //obscure text
                       Text{"a spider under #temporal stones in a cavern# holds", "l'araignée sous #une pierre bleue dans une caverne# a", /*spanish*/"una araña bajo #bloques temporales de una cueva# otorga"},
                     },
                       //clear text
                       Text{"a spider under #temporal stones in Dodongo's Cavern# holds", "la Skulltula sous #la pierre temporelle dans la caverne Dodongo# a", /*spanish*/"una araña bajo #bloques temporales de la Cueva de los Dodongos# otorga"}
  );

  HintText JabuJabusBelly_BoomerangChest = HintText::Sometimes({
                       //obscure text
                       Text{"a school of #stingers swallowed by a deity# guard", "les #raies dans un gardien# protègent", /*spanish*/"un puñado de #stingers engullidos por una deidad# guardan"},
                     },
                       //clear text
                       Text{"a school of #stingers swallowed by Jabu Jabu# guard", "les #raies dans Jabu-Jabu# protègent", /*spanish*/"un puñado de #stingers engullidos por Jabu Jabu# guardan"}
  );

  HintText JabuJabusBelly_MQ_GS_InvisibleEnemiesRoom = HintText::Sometimes({
                       //obscure text
                       Text{"a spider surrounded by #shadows in the belly of a deity# holds", "l'araignée entourée d'#ombres dans le ventre du gardien# possède", /*spanish*/"una araña rodeada de #sombras en la tripa de cierta diedad# otorga"},
                     },
                       //clear text
                       Text{"a spider surrounded by #shadows in Jabu Jabu's Belly# holds", "la Skulltula entourée d'#ombres dans Jabu-Jabu# possède", /*spanish*/"una araña rodeada de #sombras en la Tripa de Jabu Jabu# otorga"}
  );

  HintText JabuJabusBelly_MQ_Cow = HintText::Sometimes({
                       //obscure text
                       Text{"a #cow swallowed by a deity# gifts", "la #vache dans le gardien# donne", /*spanish*/"una #vaca engullida por cierta deidad# brinda"},
                     },
                       //clear text
                       Text{"a #cow swallowed by Jabu Jabu# gifts", "la #vache avallée par Jabu-Jabu# donne", /*spanish*/"una #vaca engullida por Jabu Jabu# brinda"}
  );

  HintText FireTemple_ScarecrowChest = HintText::Sometimes({
                       //obscure text
                       Text{"a #scarecrow atop the volcano# hides", "l'#épouvantail au sommet d'un volcan# donne", /*spanish*/"un #espantapájaros en lo alto del volcán# esconde"},
                     },
                       //clear text
                       Text{"#Pierre atop the Fire Temple# hides", "#Pierre au sommet du temple du feu# donne", /*spanish*/"#Pierre en lo alto del Templo del Fuego# esconde"}
  );

  HintText FireTemple_MegatonHammerChest = HintText::Sometimes({
                       //obscure text
                       Text{"the #Flare Dancer atop the volcano# guards a chest containing", "le #danseur au sommet du volcan# protège", /*spanish*/"el #Bailafuego en lo alto del volcán# otorga"},
                     },
                       //clear text
                       Text{"the #Flare Dancer atop the Fire Temple# guards a chest containing", "le #Danse-Flamme au sommet du temple du feu# protège", /*spanish*/"el #Bailaguego en lo alto del Templo del Fuego# otorga"}
  );

  HintText FireTemple_MQ_ChestOnFire = HintText::Sometimes({
                       //obscure text
                       Text{"the #Flare Dancer atop the volcano# guards a chest containing", "le #danseur au sommet du volcan# protège", /*spanish*/"el #Bailafuego en lo alto del volcán# otorga"},
                     },
                       //clear text
                       Text{"the #Flare Dancer atop the Fire Temple# guards a chest containing", "le #Danse-Flamme au sommet du temple du feu# protège", /*spanish*/"el #Bailafuego en lo alto del Templo del Fuego# otorga"}
  );

  HintText FireTemple_MQ_GS_SkullOnFire = HintText::Sometimes({
                       //obscure text
                       Text{"a #spider under a block in the volcano# holds", "l'#araignée sous un bloc dans le volcan# a", /*spanish*/"una #araña bajo el bloque de un volcán# otorga"},
                     },
                       //clear text
                       Text{"a #spider under a block in the Fire Temple# holds", "la #Skulltula sous un bloc dans le temple du feu# a", /*spanish*/"una #araña bajo un bloque del Templo del Fuego# otorga"}
  );

  HintText WaterTemple_RiverChest = HintText::Sometimes({
                       //obscure text
                       Text{"beyond the #river under the lake# waits", "au delà de #la rivière sous le lac# se cache", /*spanish*/"tras el #río bajo el lago# yace"},
                     },
                       //clear text
                       Text{"beyond the #river in the Water Temple# waits", "au delà de #la rivière dans le temple de l'eau# se cache", /*spanish*/"tras el #río del Templo del Agua# yace"}
  );

  HintText WaterTemple_BossKeyChest = HintText::Sometimes({
                       //obscure text
                       Text{"dodging #rolling boulders under the lake# leads to", "d'éviter des #rochers roulants sous le lac# mène à", /*spanish*/"esquivar #rocas rodantes bajo el lago# conduce a"},
                     },
                       //clear text
                       Text{"dodging #rolling boulders in the Water Temple# leads to", "d'éviter des #rochers roulants dans le temple de l'eau# mène à", /*spanish*/"esquivar #rocas rondantes del Templo del Agua# conduce a"}
  );

  HintText WaterTemple_GS_BehindGate = HintText::Sometimes({
                       //obscure text
                       Text{"a spider behind a #gate under the lake# holds", "l'araignée derrière une #barrière sous le lac# a", /*spanish*/"una araña tras #una valla bajo el lago# otorga"},
                     },
                       //clear text
                       Text{"a spider behind a #gate in the Water Temple# holds", "la Skulltula derrière une #barrière dans le temple de l'eau# a", /*spanish*/"una araña tras #una valla del Templo del Agua# otorga"}
  );

  HintText WaterTemple_MQ_FreestandingKey = HintText::Sometimes({
                       //obscure text
                       Text{"hidden in a #box under the lake# lies", "dans une #boîte sous le lac# gît", /*spanish*/"en una #caja bajo el lago# yace"},
                     },
                       //clear text
                       Text{"hidden in a #box in the Water Temple# lies", "dans une #boîte dans le temple de l'eau# gît", /*spanish*/"en una #caja del Templo del Agua# yace"}
  );

  HintText WaterTemple_MQ_GS_FreestandingKeyArea = HintText::Sometimes({
                       //obscure text
                       Text{"the #locked spider under the lake# holds", "l'#araignée emprisonnée sous le lac# a", /*spanish*/"la #araña enjaulada bajo el lago# otorga"},
                     },
                       //clear text
                       Text{"the #locked spider in the Water Temple# holds", "la #Skulltula emprisonnée dans le temple de l'eau# a", /*spanish*/"la #araña enjaulada del Templo del Agua# otorga"}
  );

  HintText WaterTemple_MQ_GS_TripleWallTorch = HintText::Sometimes({
                       //obscure text
                       Text{"a spider behind a #gate under the lake# holds", "l'#araignée derrière une barrière sous le lac# a", /*spanish*/"una araña tras una #valla bajo el lago# otorga"},
                     },
                       //clear text
                       Text{"a spider behind a #gate in the Water Temple# holds", "la #Skulltula derrière une barrière dans le temple de l'eau# a", /*spanish*/"una araña tras una #valla del Templo del Agua#"}
  );

  HintText GerudoTrainingGrounds_UnderwaterSilverRupeeChest = HintText::Sometimes({
                       //obscure text
                       Text{"those who seek #sunken silver rupees# will find", "ceux qui pêchent les #joyaux argentés# trouveront", /*spanish*/"aquellos que busquen las #rupias plateadas sumergidas# encontrarán"},
                       Text{"the #thieves' underwater training# rewards", "l'#épreuve de plongée des voleurs# recèle", /*spanish*/"la #instrucción submarina de las ladronas# premia"},
  });

  HintText GerudoTrainingGrounds_MQ_UnderwaterSilverRupeeChest = HintText::Sometimes({
                       //obscure text
                       Text{"those who seek #sunken silver rupees# will find", "ceux qui pêchent les #joyaux argentés# trouveront", /*spanish*/"aquellos que busquen las #rupias plateadas sumergidas# encontrarán"},
                       Text{"the #thieves' underwater training# rewards", "l'#épreuve de plongée des voleurs# recèle", /*spanish*/"la #instrucción submarina de las ladronas# premia"},
  });

  HintText GerudoTrainingGrounds_MazePathFinalChest = HintText::Sometimes({
                       //obscure text
                       Text{"the final prize of #the thieves' training# is", "la récompense ultime de #l'épreuve des voleurs# est", /*spanish*/"el premio final de la #instrucción de las ladronas# brinda"},
  });

  HintText GerudoTrainingGrounds_MQ_IceArrowsChest = HintText::Sometimes({
                       //obscure text
                       Text{"the final prize of #the thieves' training# is", "la récompense ultime de #l'épreuve des voleurs# est", /*spanish*/"el premio final de la #instrucción de las ladronas# brinda"},
  });

  HintText BottomOfTheWell_LensOfTruthChest = HintText::Sometimes({
                       //obscure text
                       Text{"the well's #grasping ghoul# hides", "la #terreur du puits# cache", /*spanish*/"en la #profundidad del pozo# se esconde"},
                       Text{"a #nether dweller in the well# holds", "le #spectre qui réside dans le puits# a", /*spanish*/"el #temido morador del pozo# concede"},
                     },
                       //clear text
                       Text{"#Dead Hand in the well# holds", "le #Poigneur dans le puits# cache", /*spanish*/"la #Mano Muerta del pozo# concede"}
  );

  HintText BottomOfTheWell_MQ_CompassChest = HintText::Sometimes({
                       //obscure text
                       Text{"the well's #grasping ghoul# hides", "la #terreur du puits# cache", /*spanish*/"en la #profundidad del pozo# se esconde"},
                       Text{"a #nether dweller in the well# holds", "le #spectre qui réside dans le puits# a", /*spanish*/"el #temido morador del pozo# concede"},
                     },
                       //clear text
                       Text{"#Dead Hand in the well# holds", "le #Poigneur dans le puits# cache", /*spanish*/"la #Mano Muerta del pozo# concede"}
  );

  HintText SpiritTemple_SilverGauntletsChest = HintText::Sometimes({
                       //obscure text
                       Text{"the treasure #sought by Nabooru# is", "le trésor que #recherche Nabooru# est", /*spanish*/"el #ansiado tesoro de Nabooru# brinda"},
                     },
                       //clear text
                       Text{"upon the #Colossus's right hand# is", "sur la #main droite du colosse# repose", /*spanish*/"en la #mano derecha del Coloso# yace"}
  );

  HintText SpiritTemple_MirrorShieldChest = HintText::Sometimes({
                       //obscure text
                       Text{"upon the #Colossus's left hand# is", "sur la #main gauche du colosse# repose", /*spanish*/"en la #mano izquierda del Coloso# yace"},
  });

  HintText SpiritTemple_MQ_ChildHammerSwitchChest = HintText::Sometimes({
                       //obscure text
                       Text{"a #temporal paradox in the Colossus# yields", "un #paradoxe temporel dans le colosse# révèle", /*spanish*/"una #paradoja temporal del Coloso# conduce a"},
                     },
                       //clear text
                       Text{"a #temporal paradox in the Spirit Temple# yields", "le #paradoxe temporel dans le temple de l'esprit# révèle", /*spanish*/"una #paradoja temporal del Coloso# conduce a"}
  );

  HintText SpiritTemple_MQ_SymphonyRoomChest = HintText::Sometimes({
                       //obscure text
                       Text{"a #symphony in the Colossus# yields", "la #symphonie du colosse# révèle", /*spanish*/"una #sinfonía del Coloso# conduce a"},
                     },
                       //clear text
                       Text{"a #symphony in the Spirit Temple# yields", "les #cinq chansons du temple de l'esprit# révèlent", /*spanish*/"una #sinfonía del Coloso# conduce a"}
  );

  HintText SpiritTemple_MQ_GS_SymphonyRoom = HintText::Sometimes({
                       //obscure text
                       Text{"a #spider's symphony in the Colossus# yields", "la #mélodie de l'araignée du colosse# révèle", /*spanish*/"la #araña de la sinfonía del Coloso# otorga"},
                     },
                       //clear text
                       Text{"a #spider's symphony in the Spirit Temple# yields", "la #mélodie de la Skulltula du temple de l'esprit# révèle", /*spanish*/"la #araña de la sinfonía del Coloso# otorga"}
  );

  HintText ShadowTemple_InvisibleFloormasterChest = HintText::Sometimes({
                       //obscure text
                       Text{"shadows in an #invisible maze# guard", "les ombres dans le #labyrinthe invisible# protègent", /*spanish*/"las sombras del #laberinto misterioso# esconden"},
  });

  HintText ShadowTemple_MQ_BombFlowerChest = HintText::Sometimes({
                       //obscure text
                       Text{"shadows in an #invisible maze# guard", "les ombres dans le #labyrinthe invisible# protègent", /*spanish*/"las sombras del #laberinto invisible# esconden"},
  });

  /*--------------------------
  |    EXCLUDE HINT TEXT     |
  ---------------------------*/

  HintText KF_KokiriSwordChest = HintText::Exclude({
                       //obscure text
                       Text{"the #hidden treasure of the Kokiri# is", "le #trésor des Kokiri# est", /*spanish*/"el #tesoro oculto de los Kokiri# esconde"},
  });

  HintText KF_MidoTopLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"the #leader of the Kokiri# hides", "le #chef des Kokiri# possède", /*spanish*/"el #líder de los Kokiri# esconde"},
                     },
                       //clear text
                       Text{"#inside Mido's house# is", "#dans la maison de Mido# gît", /*spanish*/"en la #casa de Mido# yace"}
  );

  HintText KF_MidoTopRightChest = HintText::Exclude({
                       //obscure text
                       Text{"the #leader of the Kokiri# hides", "le #chef des Kokiri# possède", /*spanish*/"el #líder de los Kokiri# esconde"},
                     },
                       //clear text
                       Text{"#inside Mido's house# is", "#dans la maison de Mido# gît", /*spanish*/"en la #casa de Mido# yace"}
  );

  HintText KF_MidoBottomLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"the #leader of the Kokiri# hides", "le #chef des Kokiri# possède", /*spanish*/"el #líder de los Kokiri# esconde"},
                     },
                       //clear text
                       Text{"#inside Mido's house# is", "#dans la maison de Mido# gît", /*spanish*/"en la #casa de Mido# yace"}
  );

  HintText KF_MidoBottomRightChest = HintText::Exclude({
                       //obscure text
                       Text{"the #leader of the Kokiri# hides", "le #chef des Kokiri# possède", /*spanish*/"el #líder de los Kokiri# esconde"},
                     },
                       //clear text
                       Text{"#inside Mido's house# is", "#dans la maison de Mido# gît", /*spanish*/"en la #casa de Mido# yace"}
  );

  HintText GY_ShieldGraveChest = HintText::Exclude({
                       //obscure text
                       Text{"the #treasure of a fallen soldier# is", "le #trésor du soldat mort# est", /*spanish*/"el #tesoro de un soldado caído# esconde"},
  });

  HintText DMT_Chest = HintText::Exclude({
                       //obscure text
                       Text{"hidden behind a wall on a #mountain trail# is", "derrière une façade du #chemin montagneux# est", /*spanish*/"tras una pared del #sendero de la montaña# otorga"},
  });

  HintText GC_MazeRightChest = HintText::Exclude({
                       //obscure text
                       Text{"in #Goron City# explosives unlock", "des explosions dans le #village Goron# révèlent", /*spanish*/"en la #Ciudad Goron# unos explosivos desbloquean"},
  });

  HintText GC_MazeCenterChest = HintText::Exclude({
                       //obscure text
                       Text{"in #Goron City# explosives unlock", "des explosions dans le #village Goron# révèlent", /*spanish*/"en la #Ciudad Goron# unos explosivos desbloquean"},
  });

  HintText ZD_Chest = HintText::Exclude({
                       //obscure text
                       Text{"fire #beyond a waterfall# reveals", "du feu #derrière la cascade# éclaire", /*spanish*/"las #llamas tras una una cascada# revelan"},
  });

  HintText GY_HookshotChest = HintText::Exclude({
                       //obscure text
                       Text{"a chest hidden by a #speedy spectre# holds", "le #coffre du rapide revenant# contient", /*spanish*/"un cofre custodiado por un #espectro veloz# otorga"},
                     },
                       //clear text
                       Text{"#dead Dampé's first prize# is", "la #première course d'Igor# donne", /*spanish*/"el primer premio de #Dampé fallecido# se trata de"}
  );

  HintText GF_Chest = HintText::Exclude({
                       //obscure text
                       Text{"on a #rooftop in the desert# lies", "sur un #toit du désert# gît", /*spanish*/"en una #azotea en el desierto# yace"},
  });

  HintText Kak_RedeadGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"#zombies beneath the earth# guard", "les #revenants sous terre# protègent", /*spanish*/"unos #zombis subterráneos# esconden"},
  });

  HintText SFM_WolfosGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"#wolves beneath the earth# guard", "les #loups sous terre# protègent", /*spanish*/"unos #lobos subterráneos# esconden"},
  });

  HintText HF_NearMarketGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"a #hole in a field near a drawbridge# holds", "la #grotte près d'un pont# contient", /*spanish*/"bajo el #hoyo de una llanura cercano a un puente# yace"},
  });

  HintText HF_SoutheastGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"a #hole amongst trees in a field# holds", "la #grotte près des arbres# contient", /*spanish*/"bajo un #hoyo de una llanura rodeado de árboles# yace"},
  });

  HintText HF_OpenGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"an #open hole in a field# holds", "la #grotte dans les plaines# contient", /*spanish*/"bajo un #hoyo descubierto de una llanura# yace"},
  });

  HintText Kak_OpenGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"an #open hole in a town# holds", "la #grotte dans le village# contient", /*spanish*/"bajo un #hoyo descubierto de un pueblo# yace"},
  });

  HintText ZR_OpenGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"a #hole along a river# holds", "la #grotte près du fleuve# contient", /*spanish*/"bajo un #hoyo junto a un río# yace"},
  });

  HintText KF_StormsGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"a #hole in a forest village# holds", "la #grotte inondée de pluie dans le Village Kokiri# révèle", /*spanish*/"bajo un #hoyo de una tribu forestal# yace"},
  });

  HintText LW_NearShortcutsGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"a #hole in a wooded maze# holds", "la #grotte dans le labyrinthe sylvestre# contient", /*spanish*/"bajo un #hoyo de un laberinto forestal# yace"},
  });

  HintText DMT_StormsGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"#hole flooded with rain on a mountain# holds", "la #grotte inondée de pluie sur la montagne# contient", /*spanish*/"bajo un #hoyo de una montaña inundado de lluvia# yace"},
  });

  HintText DMC_UpperGrottoChest = HintText::Exclude({
                       //obscure text
                       Text{"a #hole in a volcano# holds", "la #grotte dans le volcan# contient", /*spanish*/"bajo un #hoyo de un volcán# yace"},
  });


  HintText ToT_LightArrowCutscene = HintText::Exclude({
                       //obscure text
                       Text{"the #final gift of a princess# is", "le #cadeau d'adieu de la princesse# est", /*spanish*/"el #obsequio final de la princesa# se trata de"},
  });

  HintText LW_GiftFromSaria = HintText::Exclude({
                       //obscure text
                       Text{"a #potato hoarder# holds", "le #panini mélodieux# est en fait", /*spanish*/"cierta #jovencita verde# concede"},
                       Text{"a rooty tooty #flutey cutey# gifts", "la #patate musicale# est en fait", /*spanish*/"una #gran amiga# concede"},
                     },
                       //clear text
                       Text{"#Saria's Gift# is", "le #cadeau de Saria# est", /*spanish*/"el #regalo de Saria# se trata de"}
  );

  HintText ZF_GreatFairyReward = HintText::Exclude({
                       //obscure text
                       Text{"the #fairy of winds# holds", "la #fée du vent# a", /*spanish*/"el #hada del viento# brinda"},
  });

  HintText HC_GreatFairyReward = HintText::Exclude({
                       //obscure text
                       Text{"the #fairy of fire# holds", "la #fée du feu# a", /*spanish*/"el #hada del fuego# brinda"},
  });

  HintText Colossus_GreatFairyReward = HintText::Exclude({
                       //obscure text
                       Text{"the #fairy of love# holds", "la #fée de l'amour# a", /*spanish*/"el #hada del amor# brinda"},
  });

  HintText DMT_GreatFairyReward = HintText::Exclude({
                       //obscure text
                       Text{"a #magical fairy# gifts", "la #fée de la magie# a", /*spanish*/"una #hada mágica# brinda"},
  });

  HintText DMC_GreatFairyReward = HintText::Exclude({
                       //obscure text
                       Text{"a #magical fairy# gifts", "la #fée de la magie# a", /*spanish*/"una #hada máfica# brinda"},
  });

  HintText OGC_GreatFairyReward = HintText::Exclude({
                       //obscure text
                       Text{"the #fairy of strength# holds", "la #fée de la force# a", /*spanish*/"el #hada de la fuerza# brinda"},
  });


  HintText SongFromImpa = HintText::Exclude({
                       //obscure text
                       Text{"#deep in a castle#, Impa teaches", "#la gardienne de la princesse# donne", /*spanish*/"al #fondo del castillo, Impa enseña#"},
  });

  HintText SongFromMalon = HintText::Exclude({
                       //obscure text
                       Text{"#a farm girl# sings", "la #fillette de la ferme# donne", /*spanish*/"una #chica rupestre# canta"},
  });

  HintText SongFromSaria = HintText::Exclude({
                       //obscure text
                       Text{"#deep in the forest#, Saria teaches", "la #fille de la forêt# donne", /*spanish*/"al #fondo del bosque#, Saria enseña"},
  });

  HintText SongFromWindmill = HintText::Exclude({
                       //obscure text
                       Text{"a man #in a windmill# is obsessed with", "l'#homme du moulin# donne", /*spanish*/"el #hombre del molino# está obsesionado con"},
  });


  HintText HC_MalonEgg = HintText::Exclude({
                       //obscure text
                       Text{"a #girl looking for her father# gives", "la #fillette qui cherche son père# donne", /*spanish*/"una #chica en busca de su padre# otorga"},
  });

  HintText HC_ZeldasLetter = HintText::Exclude({
                       //obscure text
                       Text{"a #princess in a castle# gifts", "la #princesse dans le château# donne", /*spanish*/"la #princesa de un castillo# otorga"},
  });

  HintText ZD_DivingMinigame = HintText::Exclude({
                       //obscure text
                       Text{"an #unsustainable business model# gifts", "le #mauvais modèle d'affaires# donne", /*spanish*/"un #mal modelo de negocio# premia con"},
                     },
                       //clear text
                       Text{"those who #dive for Zora rupees# will find", "ceux qui #plongent pour des rubis Zora# trouveront", /*spanish*/"aquellos que se #sumergan por las rupias Zora# encontrarán"}
  );

  HintText LH_ChildFishing = HintText::Exclude({
                       //obscure text
                       Text{"#fishing in youth# bestows", "#pêcher dans sa jeunesse# promet", /*spanish*/"#pescar en la juventud# conduce a"},
  });

  HintText LH_AdultFishing = HintText::Exclude({
                       //obscure text
                       Text{"#fishing in maturity# bestows", "#pêcher dans sa maturité# promet", /*spanish*/"#pescar en la madurez# conduce a"},
  });

  HintText LH_LabDive = HintText::Exclude({
                       //obscure text
                       Text{"a #diving experiment# is rewarded with", "l'#expérience de plongée# donne", /*spanish*/"#bucear para un experimento# se premia con"},
  });

  HintText GC_RollingGoronAsAdult = HintText::Exclude({
                       //obscure text
                       Text{"#comforting yourself# provides", "se #réconforter soi-même# donne", /*spanish*/"#confrontarte a ti mismo# otorga"},
                     },
                       //clear text
                       Text{"#reassuring a young Goron# is rewarded with", "#rassurer un jeune Goron# donne", /*spanish*/"#calmar a un joven Goron# otorga"}
  );

  HintText MK_BombchuBowlingFirstPrize = HintText::Exclude({
                       //obscure text
                       Text{"the #first explosive prize# is", "le #premier prix explosif# est", /*spanish*/"el #primer premio explosivo# se trata de"},
  });

  HintText MK_BombchuBowlingSecondPrize = HintText::Exclude({
                       //obscure text
                       Text{"the #second explosive prize# is", "le #deuxième prix explosif# est", /*spanish*/"el #segundo premio explosivo# se trata de"},
  });

  HintText MK_LostDog = HintText::Exclude({
                       //obscure text
                       Text{"#puppy lovers# will find", "les #amoureux canins# trouveront", /*spanish*/"los #amantes caninos# encontrarán"},
                     },
                       //clear text
                       Text{"#rescuing Richard the Dog# is rewarded with", "#retrouver Kiki le chien# promet", /*spanish*/"#rescatar al perro Ricardo# conduce a"}
  );

  HintText LW_OcarinaMemoryGame = HintText::Exclude({
                       //obscure text
                       Text{"the prize for a #game of Simon Says# is", "la #récompense de Jean Dit# est", /*spanish*/"#repetir ciertas melodías# otorga"},
                       Text{"a #child sing-a-long# holds", "les #jeunes flûtistes# donnent", /*spanish*/"#tocar junto a otros# otorga"},
                     },
                       //clear text
                       Text{"#playing an Ocarina in Lost Woods# is rewarded with", "#jouer l'ocarina dans les bois perdus# donne", /*spanish*/"#tocar la ocarina en el Bosque Perdido# otorga"}
  );

  HintText Kak_10GoldSkulltulaReward = HintText::Exclude({
                       //obscure text
                       Text{"#10 bug badges# rewards", "#10 écussons# donnent", /*spanish*/"#10 medallas de insectos# otorgan"},
                       Text{"#10 spider souls# yields", "#10 âmes# donnent", /*spanish*/"#10 almas de araña# otorgan"},
                       Text{"#10 auriferous arachnids# lead to", "#10 arachnides aurifères# donnent", /*spanish*/"#10 arácnidos auríferos# otorgan"},
                     },
                       //clear text
                       Text{"slaying #10 Gold Skulltulas# reveals", "détruire #10 Skulltulas d'or# donne", /*spanish*/"#exterminar 10 skulltulas doradas# revela"}
  );

  HintText Kak_ManOnRoof = HintText::Exclude({
                       //obscure text
                       Text{"a #rooftop wanderer# holds", "une #rencontre sur un toit# donne", /*spanish*/"#alguien sobre un tejado# otorga"},
  });

  HintText ZR_MagicBeanSalesman = HintText::Exclude({
                       //obscure text
                       Text{"a seller of #colorful crops# has", "le #marchand de légumes# vend", /*spanish*/"el vendedor de un #colorido cultivo# ofrece"},
                     },
                       //clear text
                       Text{"a #bean seller# offers", "le #marchand de haricots magiques# vend en fait", /*spanish*/"el #vendedor de judías# ofrece"}
  );

  HintText ZR_FrogsInTheRain = HintText::Exclude({
                       //obscure text
                       Text{"#frogs in a storm# gift", "#des grenouilles mouillées# donnent", /*spanish*/"las #ancas bajo la tormenta# otorgan"},
  });

  HintText GF_HBA1000Points = HintText::Exclude({
                       //obscure text
                       Text{"scoring 1000 in #horseback archery# grants", "d'obtenir 1000 points dans l'#archerie équestre# donne", /*spanish*/"conseguir 1000 puntos en el #tiro con arco a caballo# premia"},
  });

  HintText MK_ShootingGalleryReward = HintText::Exclude({
                       //obscure text
                       Text{"#shooting in youth# grants", "#faire du tir dans sa jeunesse# donne", /*spanish*/"#disparar en la juventud# otorga"},
  });

  HintText Kak_ShootingGalleryReward = HintText::Exclude({
                       //obscure text
                       Text{"#shooting in maturity# grants", "#faire du tir dans sa maturité# donne", /*spanish*/"#disparar en la madurez# otorga"},
  });

  HintText LW_TargetInWoods = HintText::Exclude({
                       //obscure text
                       Text{"shooting a #target in the woods# grants", "#tirer une cible dans les bois# donne", /*spanish*/"disparar a un #blanco forestal# brinda"},
  });

  HintText Kak_AnjuAsAdult = HintText::Exclude({
                       //obscure text
                       Text{"a #chicken caretaker# offers adults", "devenir un éleveur de Cocottes# donne", /*spanish*/"una #cuidadora de emplumados# le ofrece a los mayores"},
  });

  HintText LLR_TalonsChickens = HintText::Exclude({
                       //obscure text
                       Text{"#finding Super Cuccos# is rewarded with", "#trouver des Super Cocottes# donne", /*spanish*/"#hallar los supercucos# conduce a"},
  });

  HintText GC_RollingGoronAsChild = HintText::Exclude({
                       //obscure text
                       Text{"the prize offered by a #large rolling Goron# is", "la récompense d'un #gros Goron roulant# est", /*spanish*/"un #gran Goron rodante# otorga"},
  });

  HintText LH_UnderwaterItem = HintText::Exclude({
                       //obscure text
                       Text{"the #sunken treasure in a lake# is", "le #trésor au fond du lac# est", /*spanish*/"el #tesoro hundido del lago# se trata de"},
  });

  HintText GF_GerudoToken = HintText::Exclude({
                       //obscure text
                       Text{"#rescuing captured carpenters# is rewarded with", "#secourir les charpentiers capturés# assure", /*spanish*/"#rescatar los apresados carpinteros# se premia con"},
  });

  HintText Wastelan_BombchuSalesman = HintText::Exclude({
                       //obscure text
                       Text{"a #carpet guru# sells", "#un marchand du désert# vend", /*spanish*/"el #genio de una alfombra# vende"},
  });


  HintText Kak_ImpasHouseFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"#imprisoned in a house# lies", "#encagé dans une maison# gît", /*spanish*/"#en una casa entre rejas# yace"},
  });

  HintText HF_TektiteGrottoFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"#deep underwater in a hole# is", "#dans les profondeurs d'une grotte# gît", /*spanish*/"#en lo hondo bajo un hoyo# yace"},
  });

  HintText Kak_WindmillFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"on a #windmill ledge# lies", "#haut perché dans le moulin# gît", /*spanish*/"al #borde de un molino# yace"},
  });

  HintText GY_DampeRaceFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"#racing a ghost# leads to", "le défi du #revenant rapide# donne", /*spanish*/"#perseguir a un fantasma# conduce a"},
                     },
                       //clear text
                       Text{"#dead Dampe's second# prize is", "la #deuxième course d'Igor# donne", /*spanish*/"el segundo premio de #Dampé fallecido# se trata de"}
  );

  HintText LLR_FreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"in a #ranch silo# lies", "#dans l'entrepôt de la ferme# gît", /*spanish*/"en un #granero rupestre# yace"},
  });

  HintText GY_FreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"a #crate in a graveyard# hides", "#la boîte dans le cimetière# contient", /*spanish*/"bajo la #caja de un cementerio# yace"},
  });

  HintText GY_DampeGravediggingTour = HintText::Exclude({
                       //obscure text
                       Text{"a #gravekeeper digs up#", "#le jeu du fossoyeur# cache", /*spanish*/"cierto #sepultero desentierra#"},
  });

  HintText ZR_NearOpenGrottoFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"on top of a #pillar in a river# lies", "#sur un pilier au dessus du fleuve# gît", /*spanish*/"en lo alto del #pilar de un río# yace"},
  });

  HintText ZR_NearDomainFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"on a #river ledge by a waterfall# lies", "#sur la falaise au dessus du fleuve# gît", /*spanish*/"al borde #del río con una cascada# yace"},
  });

  HintText LH_FreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"high on a #lab rooftop# one can find", "#la tour d'observation du lac# cache", /*spanish*/"en lo #alto de un laboratorio# yace"},
  });

  HintText ZF_IcebergFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"#floating on ice# is", "#gisant sur la glace# gît", /*spanish*/"#flotando sobre hielo# yace"},
  });

  HintText GV_WaterfallFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"behind a #desert waterfall# is", "#derrière la cascade du désert# se cache", /*spanish*/"tras una #desierta cascada# yace"},
  });

  HintText GV_CrateFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"a #crate in a valley# hides", "la #boîte dans la vallée# contient", /*spanish*/"bajo la #caja de un valle# yace"},
  });

  HintText Colossus_FreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"on top of an #arch of stone# lies", "#gisant sur une arche de pierre# gît", /*spanish*/"en lo alto de un #arco de piedra# yace"},
  });

  HintText DMT_FreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"above a #mountain cavern entrance# is", "gisant #au dessus de la caverne montagneuse# gît", /*spanish*/"en lo alto de la #entrada de una cueva en la montaña# yace"},
  });

  HintText DMC_WallFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"nestled in a #volcanic wall# is", "dans une #alcove volcanique# gît", /*spanish*/"entre unas #murallas volcánicas# yace"},
  });

  HintText DMC_VolcanoFreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"obscured by #volcanic ash# is", "#recouvert de cendres volcaniques# gît", /*spanish*/"bajo la #ceniza volcánica# yace"},
  });

  HintText GF_NorthF1Carpenter = HintText::Exclude({
                       //obscure text
                       Text{"#defeating Gerudo guards# reveals", "les #geôliers Gerudo# détiennent", /*spanish*/"#derrotar a las guardas Gerudo# revela"},
  });

  HintText GF_NorthF2Carpenter = HintText::Exclude({
                       //obscure text
                       Text{"#defeating Gerudo guards# reveals", "les #geôliers Gerudo# détiennent", /*spanish*/"#derrotar a las guardas Gerudo# revela"},
  });

  HintText GF_SouthF1Carpenter = HintText::Exclude({
                       //obscure text
                       Text{"#defeating Gerudo guards# reveals", "les #geôliers Gerudo# détiennent", /*spanish*/"#derrotar a las guardas Gerudo# revela"},
  });

  HintText GF_SouthF2Carpenter = HintText::Exclude({
                       //obscure text
                       Text{"#defeating Gerudo guards# reveals", "les #geôliers Gerudo# détiennent", /*spanish*/"#derrotar a las guardas Gerudo# revela"},
  });


  HintText DekuTree_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"in the #center of the Deku Tree# lies", "#le coeur de l'arbre Mojo# recèle", /*spanish*/"al #centro del Árbol Deku# yace"},
  });

  HintText DekuTree_SlingshotChest = HintText::Exclude({
                       //obscure text
                       Text{"the #treasure guarded by a scrub# in the Deku Tree is", "le #trésor protégé par une peste# dans l'arbre Mojo est", /*spanish*/"un #deku del Árbol Deku# esconde"},
  });

  HintText DekuTree_SlingshotRoomSideChest = HintText::Exclude({
                       //obscure text
                       Text{"the #treasure guarded by a scrub# in the Deku Tree is", "le #trésor protégé par une peste# dans l'arbre Mojo est", /*spanish*/"un #deku del Árbol Deku# esconde"},
  });

  HintText DekuTree_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#pillars of wood# in the Deku Tree lead to", "les #piliers de bois# dans l'arbre Mojo indiquent", /*spanish*/"los #salientes del Árbol Deku# conducen a"},
  });

  HintText DekuTree_CompassRoomSideChest = HintText::Exclude({
                       //obscure text
                       Text{"#pillars of wood# in the Deku Tree lead to", "les #piliers de bois# dans l'arbre Mojo indiquent", /*spanish*/"los #salientes del Árbol Deku# conducen a"},
  });

  HintText DekuTree_BasementChest = HintText::Exclude({
                       //obscure text
                       Text{"#webs in the Deku Tree# hide", "les #toiles dans l'arbre Mojo# cachent", /*spanish*/"entre #telarañas del Árbol Deku# yace"},
  });


  HintText DekuTree_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"in the #center of the Deku Tree# lies", "#le coeur de l'arbre Mojo# recèle", /*spanish*/"al #centro del Árbol Deku# yace"},
  });

  HintText DekuTree_MQ_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"a #treasure guarded by a large spider# in the Deku Tree is", "le #trésor protégé par une grosse araignée# dans l'arbre Mojo est", /*spanish*/"una #araña del Árbol Deku# esconde"},
  });

  HintText DekuTree_MQ_SlingshotChest = HintText::Exclude({
                       //obscure text
                       Text{"#pillars of wood# in the Deku Tree lead to", "les #piliers de bois# dans l'arbre Mojo indiquent", /*spanish*/"los #salientes del Árbol Deku# conducen a"},
  });

  HintText DekuTree_MQ_SlingshotRoomBackChest = HintText::Exclude({
                       //obscure text
                       Text{"#pillars of wood# in the Deku Tree lead to", "les #piliers de bois# dans l'arbre Mojo indiquent", /*spanish*/"los #salientes del Árbol Deku# conducen a"},
  });

  HintText DekuTree_MQ_BasementChest = HintText::Exclude({
                       //obscure text
                       Text{"#webs in the Deku Tree# hide", "les #toiles dans l'arbre Mojo# cachent", /*spanish*/"entre #telarañas del Árbol Deku# yace"},
  });

  HintText DekuTree_MQ_BeforeSpinningLogChest = HintText::Exclude({
                       //obscure text
                       Text{"#magical fire in the Deku Tree# leads to", "le #feu magique dans l'arbre Mojo# éclaire", /*spanish*/"el #fuego mágico en el Árbol Deku# conduce a"},
  });


  HintText DodongosCavern_BossRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"#above King Dodongo# lies", "#par dessus le Roi Dodongo# gît", /*spanish*/"#sobre el Rey Dodongo# yace"},
  });


  HintText DodongosCavern_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"a #muddy wall in Dodongo's Cavern# hides", "le #mur fragile dans la caverne Dodongo# recèle", /*spanish*/"tras una #agrietada pared en la Caverna de los Dodongos# yace"},
  });

  HintText DodongosCavern_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"a #statue in Dodongo's Cavern# guards", "la #statue dans la caverne Dodongo# protège", /*spanish*/"una #estatua de la Caverna de los Dodongos# esconde"},
  });

  HintText DodongosCavern_BombFlowerPlatformChest = HintText::Exclude({
                       //obscure text
                       Text{"above a #maze of stone# in Dodongo's Cavern lies", "sur #un labyrinthe de pierre# dans la caverne Dodongo gît", /*spanish*/"entre un #laberinto de piedra# en la Cueva de los Dodongos# yace"},
  });

  HintText DodongosCavern_BombBagChest = HintText::Exclude({
                       //obscure text
                       Text{"the #second lizard cavern battle# yields", "le #deuxième duel de lézards de caverne# octroie", /*spanish*/"#luchar dos veces contra reptiles en una cueva# conduce a"},
  });

  HintText DodongosCavern_EndOfBridgeChest = HintText::Exclude({
                       //obscure text
                       Text{"a #chest at the end of a bridge# yields", "le #trésor à l'extrémité d'un pont# contient", /*spanish*/"un #cofre al final de un quebrado puente# otorga"},
  });


  HintText DodongosCavern_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"a #muddy wall in Dodongo's Cavern# hides", "le #mur fragile dans la caverne Dodongo# recèle", /*spanish*/"una #quebrada pared en la Cueva de los Dodongos# esconde"},
  });

  HintText DodongosCavern_MQ_BombBagChest = HintText::Exclude({
                       //obscure text
                       Text{"an #elevated alcove# in Dodongo's Cavern holds", "l'#alcove haut perchée# dans la caverne Dodongo cache", /*spanish*/"una #elevada alcoba# en la Caverna de los Dongos# brinda"},
  });

  HintText DodongosCavern_MQ_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#fire-breathing lizards# in Dodongo's Cavern guard", "les #lézards cracheurs de feu# dans la caverne Dodongo protègent", /*spanish*/"unos #lagartos de fuego# en la Cueva de los Dodongos# esconden"},
  });

  HintText DodongosCavern_MQ_LarvaeRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"#baby spiders# in Dodongo's Cavern guard", "les #petites araignées dans la caverne Dodongo# protègent", /*spanish*/"unas #pequeñas larvas# en la Cueva de los Dodongos esconden"},
  });

  HintText DodongosCavern_MQ_TorchPuzzleRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"above a #maze of stone# in Dodongo's Cavern lies", "sur #un labyrinthe de pierre# dans la caverne Dodongo gît", /*spanish*/"sobre un #laberinto de piedra# en la Cueva de los Dodongos yace"},
  });

  HintText DodongosCavern_MQ_UnderGraveChest = HintText::Exclude({
                       //obscure text
                       Text{"#beneath a headstone# in Dodongo's Cavern lies", "#sous une pierre tombale# dans la caverne Dodongo gît", /*spanish*/"#bajo una lápida# en la Cueva de los Dodongos yace"},
  });


  HintText JabuJabusBelly_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"#tentacle trouble# in a deity's belly guards", "la #membrane# dans le ventre du gardien protège", /*spanish*/"un #problema tentaculoso# en la tripa de cierta deidad esconde"},
                     },
                       //clear text
                       Text{"a #slimy thing# guards", "la #chose gluante# gardien protège", /*spanish*/"un #tentáculo parasitario# protege"}
  );

  HintText JabuJabusBelly_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#bubble trouble# in a deity's belly guards", "un #horde de bulles# dans le ventre du gardien protègent", /*spanish*/"un #problema burbujesco# en la tripa de cierta deidad esconde"},
                     },
                       //clear text
                       Text{"#bubbles# guard", "des #bulles# entourent", /*spanish*/"unas #burbujas# protegen"}
  );


  HintText JabuJabusBelly_MQ_FirstRoomSideChest = HintText::Exclude({
                       //obscure text
                       Text{"shooting a #mouth cow# reveals", "tirer sur une #vache# révèle", /*spanish*/"#dispararle a una vaca# revela"},
  });

  HintText JabuJabusBelly_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"#pop rocks# hide", "des #pierres aux reins# cachent", /*spanish*/"#cepillarse los dientes con explosivos# revela"},
                       Text{"an #explosive palate# holds", "des #gargouillis explosifs# cachent", /*spanish*/"un #paladar explosivo# esconde"},
                     },
                       //clear text
                       Text{"a #boulder before cows# hides", "des #rochers près des vaches# cachent", /*spanish*/"cierta #roca con unas vacas# esconde"}
  );

  HintText JabuJabusBelly_MQ_SecondRoomLowerChest = HintText::Exclude({
                       //obscure text
                       Text{"near a #spiked elevator# lies", "près d'un #ascenseur visqueux# gît", /*spanish*/"cerca de un #ascensor puntiagudo# yace"},
  });

  HintText JabuJabusBelly_MQ_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"a #drowning cow# unveils", "une #vache à l'eau# a", /*spanish*/"una #vaca sumergida# revela"},
  });

  HintText JabuJabusBelly_MQ_SecondRoomUpperChest = HintText::Exclude({
                       //obscure text
                       Text{"#moving anatomy# creates a path to", "un #organe descendant# mène à", /*spanish*/"un #ser movedizo entre paredes# conduce a"},
  });

  HintText JabuJabusBelly_MQ_BasementNearSwitchesChest = HintText::Exclude({
                       //obscure text
                       Text{"a #pair of digested cows# hold", "#deux boeufs digérés# détiennent", /*spanish*/"un #par de digeridas vacas# otorgan"},
  });

  HintText JabuJabusBelly_MQ_BasementNearVinesChest = HintText::Exclude({
                       //obscure text
                       Text{"a #pair of digested cows# hold", "#deux boeufs digérés# détiennent", /*spanish*/"un #par de digeridas vacas# otorgan"},
  });

  HintText JabuJabusBelly_MQ_NearBossChest = HintText::Exclude({
                       //obscure text
                       Text{"the #final cows' reward# in a deity's belly is", "le #cadeau des dernières vaches# estomacales est", /*spanish*/"las #vacas al final# de la tripa de cierta deidad otorgan"},
  });

  HintText JabuJabusBelly_MQ_FallingLikeLikeRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"#cows protected by falling monsters# in a deity's belly guard", "des #vaches protégées par des monstres tombants# cachent", /*spanish*/"unas #vacas custodiadas por monstruos del techo# de la tripa de cierta deidad otorgan"},
  });

  HintText JabuJabusBelly_MQ_BoomerangRoomSmallChest = HintText::Exclude({
                       //obscure text
                       Text{"a school of #stingers swallowed by a deity# guard", "les #raies avallées par le gardien# protègent", /*spanish*/"un puñado de #stingers engullidos por cierta deidad# guardan"},
                     },
                       //clear text
                       Text{"a school of #stingers swallowed by Jabu Jabu# guard", "les #raies avallées par Jabu-Jabu# protègent", /*spanish*/"un puñado de #stingers engullidos por Jabu Jabu# guardan"}
  );

  HintText JabuJabusBelly_MQ_BoomerangChest = HintText::Exclude({
                       //obscure text
                       Text{"a school of #stingers swallowed by a deity# guard", "les #raies avallées par le gardien# protègent", /*spanish*/"un puñado de #stingers engullidos por cierta deidad# guardan"},
                     },
                       //clear text
                       Text{"a school of #stingers swallowed by Jabu Jabu# guard", "les #raies avallées par Jabu-Jabu# protègent", /*spanish*/"un puñado de #stingers engullidos por Jabu Jabu# guardan"}
  );


  HintText ForestTemple_FirstRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"a #tree in the Forest Temple# supports", "sur l'#arbre dans le temple de la forêt# gît", /*spanish*/"sobre un #árbol del Templo del Bosque# yace"},
  });

  HintText ForestTemple_FirstStalfosChest = HintText::Exclude({
                       //obscure text
                       Text{"#defeating enemies beneath a falling ceiling# in Forest Temple yields", "#deux squelettes# dans le temple de la forêt protègent", /*spanish*/"#derrotar enemigos caídos de lo alto# del Templo del Bosque revela"},
  });

  HintText ForestTemple_WellChest = HintText::Exclude({
                       //obscure text
                       Text{"a #sunken chest deep in the woods# contains", "le #coffre submergé dans la forêt# contient", /*spanish*/"un #sumergido cofre en lo profundo del bosque# contiene"},
  });

  HintText ForestTemple_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"a #fiery skull# in Forest Temple guards", "le #crâne enflammé# dans le temple de la forêt protège", /*spanish*/"una #ardiente calavera# del Templo del Bosque esconde"},
  });

  HintText ForestTemple_RaisedIslandCourtyardChest = HintText::Exclude({
                       //obscure text
                       Text{"a #chest on a small island# in the Forest Temple holds", "le #coffre sur l'îlot# du temple de la forêt contient", /*spanish*/"un #cofre sobre una isla# del Templo del Bosque contiene"},
  });

  HintText ForestTemple_FallingCeilingRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"beneath a #checkerboard falling ceiling# lies", "sous #l'échiquier tombant# gît", /*spanish*/"tras un #techo de ajedrez# yace"},
  });

  HintText ForestTemple_EyeSwitchChest = HintText::Exclude({
                       //obscure text
                       Text{"a #sharp eye# will spot", "l'#oeil perçant# dans la forêt verra", /*spanish*/"un #afilado ojo# revela"},
                     },
                       //clear text
                       Text{"#blocks of stone# in the Forest Temple surround", "les #blocs dans le temple de la forêt# entourent", /*spanish*/"cerca de unos #bloques de piedra# del Templo del Bosque yace"}
  );

  HintText ForestTemple_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"a #turned trunk# contains", "le #coffre pivoté# contient", /*spanish*/"en una #sala con otro punto de vista# se esconde"},
  });

  HintText ForestTemple_FloormasterChest = HintText::Exclude({
                       //obscure text
                       Text{"deep in the forest #shadows guard a chest# containing", "l'#ombre de la forêt# protège un coffre contenant", /*spanish*/"en lo profundo del bosque #unas sombras# esconden"},
  });

  HintText ForestTemple_BowChest = HintText::Exclude({
                       //obscure text
                       Text{"an #army of the dead# guards", "des #squelettes sylvestres# protègent", /*spanish*/"un #ejército de soldados caídos# guardan"},
                     },
                       //clear text
                       Text{"#Stalfos deep in the Forest Temple# guard", "#trois squelettes dans le temple de la forêt# protègent", /*spanish*/"los #Stalfos en lo profundo del Templo del Bosque# guardan"}
  );

  HintText ForestTemple_RedPoeChest = HintText::Exclude({
                       //obscure text
                       Text{"#Joelle# guards", "#Joelle# protège", /*spanish*/"#Joelle# guarda"},
                     },
                       //clear text
                       Text{"a #red ghost# guards", "le #fantôme rouge# protège", /*spanish*/"un #espectro rojo# guarda"}
  );

  HintText ForestTemple_BluePoeChest = HintText::Exclude({
                       //obscure text
                       Text{"#Beth# guards", "#Beth# protège", /*spanish*/"#Beth# guarda"},
                     },
                       //clear text
                       Text{"a #blue ghost# guards", "le #fantôme bleu# protège", /*spanish*/"un #espectro azul# guarda"}
  );

  HintText ForestTemple_BasementChest = HintText::Exclude({
                       //obscure text
                       Text{"#revolving walls# in the Forest Temple conceal", "des #murs rotatifs dans la forêt# recèlent", /*spanish*/"las #paredes giratorias# del Templo del Bosque conceden"},
  });


  HintText ForestTemple_MQ_FirstRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"a #tree in the Forest Temple# supports", "sur l'#arbre dans le temple de la forêt# gît", /*spanish*/"sobre un #árbol del Templo del Bosque# yace"},
  });

  HintText ForestTemple_MQ_WolfosChest = HintText::Exclude({
                       //obscure text
                       Text{"#defeating enemies beneath a falling ceiling# in Forest Temple yields", "#deux squelettes# dans le temple de la forêt protègent", /*spanish*/"#derrotar enemigos caídos de lo alto# del Templo del Bosque revela"},
  });

  HintText ForestTemple_MQ_BowChest = HintText::Exclude({
                       //obscure text
                       Text{"an #army of the dead# guards", "des #squelettes sylvestres# protègent", /*spanish*/"un #ejército de soldados caídos# guardan"},
                     },
                       //clear text
                       Text{"#Stalfos deep in the Forest Temple# guard", "#trois squelettes dans le temple de la forêt# protègent", /*spanish*/"los #Stalfos en lo profundo del Templo del Bosque# guardan"}
  );

  HintText ForestTemple_MQ_RaisedIslandCourtyardLowerChest = HintText::Exclude({
                       //obscure text
                       Text{"a #chest on a small island# in the Forest Temple holds", "le #coffre sur l'îlot# du temple de la forêt contient", /*spanish*/"un #cofre sobre una isla# del Templo del Bosque contiene"},
  });

  HintText ForestTemple_MQ_RaisedIslandCourtyardUpperChest = HintText::Exclude({
                       //obscure text
                       Text{"#high in a courtyard# within the Forest Temple is", "#haut perché dans le jardin# du temple de la forêt gît", /*spanish*/"un #cofre en lo alto de un patio# del Templo del Bosque contiene"},
  });

  HintText ForestTemple_MQ_WellChest = HintText::Exclude({
                       //obscure text
                       Text{"a #sunken chest deep in the woods# contains", "le #coffre submergé dans la forêt# contient", /*spanish*/"un #sumergido cofre en lo profundo del bosque# contiene"},
  });

  HintText ForestTemple_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"#Joelle# guards", "#Joelle# protège", /*spanish*/"#Joelle# guarda"},
                     },
                       //clear text
                       Text{"a #red ghost# guards", "le #fantôme rouge# protège", /*spanish*/"un #fantasma rojo# guarda"}
  );

  HintText ForestTemple_MQ_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#Beth# guards", "#Beth# protège", /*spanish*/"#Beth# guarda"},
                     },
                       //clear text
                       Text{"a #blue ghost# guards", "le #fantôme bleu# protège", /*spanish*/"un #fantasma azul# guarda"}
  );

  HintText ForestTemple_MQ_FallingCeilingRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"beneath a #checkerboard falling ceiling# lies", "sous #l'échiquier tombant# gît", /*spanish*/"tras un #techo de ajedrez# yace"},
  });

  HintText ForestTemple_MQ_BasementChest = HintText::Exclude({
                       //obscure text
                       Text{"#revolving walls# in the Forest Temple conceal", "des #murs rotatifs dans la forêt# recèlent", /*spanish*/"las #paredes giratorias# del Templo del Bosque conceden"},
  });

  HintText ForestTemple_MQ_RedeadChest = HintText::Exclude({
                       //obscure text
                       Text{"deep in the forest #undead guard a chest# containing", "des #revenants dans le temple de la forêt# protègent", /*spanish*/"en lo profundo del bosque #guardias del más allá# guardan"},
  });

  HintText ForestTemple_MQ_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"a #turned trunk# contains", "le #coffre pivoté# contient", /*spanish*/"en una #sala con otro punto de vista# se esconde"},
  });


  HintText FireTemple_NearBossChest = HintText::Exclude({
                       //obscure text
                       Text{"#near a dragon# is", "#près d'un dragon# gît", /*spanish*/"#cerca de un dragón# yace"},
  });

  HintText FireTemple_FlareDancerChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Flare Dancer behind a totem# guards", "le #Danse-Flamme derrière un totem# protège", /*spanish*/"el #Bailafuego tras unos tótems# esconde"},
  });

  HintText FireTemple_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"a #prison beyond a totem# holds", "la #prison derrière un totem# contient", /*spanish*/"en una #prisión tras unos tótems# yace"},
  });

  HintText FireTemple_BigLavaRoomBlockedDoorChest = HintText::Exclude({
                       //obscure text
                       Text{"#explosives over a lava pit# unveil", "des #explosifs dans un lac de lave# révèlent", /*spanish*/"los #explosivos en un mar de llamas# revelan"},
  });

  HintText FireTemple_BigLavaRoomLowerOpenDoorChest = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron trapped near lava# holds", "le #Goron emprisonné près de la lave# a", /*spanish*/"un #goron atrapado cerca de un mar de llamas# guarda"},
  });

  HintText FireTemple_BoulderMazeLowerChest = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron at the end of a maze# holds", "le #Goron dans le labyrinthe# a", /*spanish*/"un #goron al final de un laberinto# guarda"},
  });

  HintText FireTemple_BoulderMazeUpperChest = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron above a maze# holds", "le #Goron au dessus du labyrinthe# a", /*spanish*/"un #goron sobre un laberinto# guarda"},
  });

  HintText FireTemple_BoulderMazeSideRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron hidden near a maze# holds", "le #Goron caché près du labyrinthe# a", /*spanish*/"un #goron escondido tras un laberinto# guarda"},
  });

  HintText FireTemple_BoulderMazeShortcutChest = HintText::Exclude({
                       //obscure text
                       Text{"a #blocked path# in Fire Temple holds", "un #sol fragile dans le temple du feu# contient", /*spanish*/"en un #camino bloqueado# del Templo del Fuego yace"},
  });

  HintText FireTemple_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"a #caged chest# in the Fire Temple hoards", "un #coffre emprisonné# dans le temple du feu contient", /*spanish*/"un #cofre entre rejas# del Templo del Fuego contiene"},
  });

  HintText FireTemple_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"a #chest in a fiery maze# contains", "un #coffre dans un labyrinthe enflammé# contient", /*spanish*/"un #cofre de un ardiente laberinto# contiene"},
  });

  HintText FireTemple_HighestGoronChest = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron atop the Fire Temple# holds", "le #Goron au sommet du temple du feu# a", /*spanish*/"un #goron en lo alto del Templo del Fuego# guarda"},
  });


  HintText FireTemple_MQ_NearBossChest = HintText::Exclude({
                       //obscure text
                       Text{"#near a dragon# is", "#près d'un dragon# gît", /*spanish*/"#cerca de un dragón# yace"},
  });

  HintText FireTemple_MQ_MegatonHammerChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Flare Dancer in the depths of a volcano# guards", "le #Danse-Flamme au coeur du volcan# a", /*spanish*/"el #Bailafuego en lo profundo del volcán# esconde"},
                     },
                       //clear text
                       Text{"the #Flare Dancer in the depths of the Fire Temple# guards", "le #Danse-Flamme au coeur du volcan# a", /*spanish*/"el #Bailafuego en lo profundo del Templo del Fuego# esconde"}
  );

  HintText FireTemple_MQ_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"a #blocked path# in Fire Temple holds", "le #chemin scellé# dans le temple du feu contient", /*spanish*/"en un #camino bloqueado# del Templo del Fuego yace"},
  });

  HintText FireTemple_MQ_LizalfosMazeLowerChest = HintText::Exclude({
                       //obscure text
                       Text{"#crates in a maze# contain", "des #boîtes dans le labyrinthe# contiennent", /*spanish*/"las #cajas de un laberinto# contienen"},
  });

  HintText FireTemple_MQ_LizalfosMazeUpperChest = HintText::Exclude({
                       //obscure text
                       Text{"#crates in a maze# contain", "des #boîtes dans le labyrinthe# contiennent", /*spanish*/"las #cajas de un laberinto# contienen"},
  });

  HintText FireTemple_MQ_MapRoomSideChest = HintText::Exclude({
                       //obscure text
                       Text{"a #falling slug# in the Fire Temple guards", "la #limace tombante# dans le temple du feu protège", /*spanish*/"una #babosa del techo# del Templo del Fuego guarda"},
  });

  HintText FireTemple_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"using a #hammer in the depths of the Fire Temple# reveals", "frapper du #marteau au coeur du volcan# révèle", /*spanish*/"usar el #martillo en lo profundo del Templo del Fuego# revela"},
  });

  HintText FireTemple_MQ_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"#illuminating a lava pit# reveals the path to", "#éclairer le lac de lave# révèle", /*spanish*/"#iluminar un mar de llamas# revela"},
  });

  HintText FireTemple_MQ_BigLavaRoomBlockedDoorChest = HintText::Exclude({
                       //obscure text
                       Text{"#explosives over a lava pit# unveil", "des #explosifs dans un lac de lave# révèlent", /*spanish*/"los #explosivos en un mar de llamas# revelan"},
  });

  HintText FireTemple_MQ_LizalfosMazeSideRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron hidden near a maze# holds", "le #Goron caché près du labyrinthe# a", /*spanish*/"un #goron cerca de un laberinto# guarda"},
  });

  HintText FireTemple_MQ_FreestandingKey = HintText::Exclude({
                       //obscure text
                       Text{"hidden #beneath a block of stone# lies", "caché #derrière un bloc de pierre# gît", /*spanish*/"#bajo unos bloques de piedra# yace"},
  });


  HintText WaterTemple_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"#rolling spikes# in the Water Temple surround", "des #Spikes# dans le temple de l'eau entourent", /*spanish*/"unas #rodantes púas# del Templo del Agua guardan"},
  });

  HintText WaterTemple_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#roaming stingers in the Water Temple# guard", "des #raies dans le temple de l'eau# protègent", /*spanish*/"unos #errantes stingers# del Templo del Agua guardan"},
  });

  HintText WaterTemple_TorchesChest = HintText::Exclude({
                       //obscure text
                       Text{"#fire in the Water Temple# reveals", "des #flammes dans le temple de l'eau# révèlent", /*spanish*/"el #fuego en el Templo del Agua# revela"},
  });

  HintText WaterTemple_DragonChest = HintText::Exclude({
                       //obscure text
                       Text{"a #serpent's prize# in the Water Temple is", "la #récompense du dragon submergé# est", /*spanish*/"el #escamado premio# del Templo del Agua se trata de"},
  });

  HintText WaterTemple_CentralBowTargetChest = HintText::Exclude({
                       //obscure text
                       Text{"#blinding an eye# in the Water Temple leads to", "#l'oeil# du temple de l'eau voit", /*spanish*/"#cegar un ojo# del Templo del Agua conduce a"},
  });

  HintText WaterTemple_CentralPillarChest = HintText::Exclude({
                       //obscure text
                       Text{"in the #depths of the Water Temple# lies", "le #coeur du temple de l'eau# cache", /*spanish*/"en las #profundidades del Templo del Agua yace"},
  });

  HintText WaterTemple_CrackedWallChest = HintText::Exclude({
                       //obscure text
                       Text{"#through a crack# in the Water Temple is", "le #mur fragile# du temple de l'eau cache", /*spanish*/"tras una #agrietada pared# del Templo del Agua yace"},
  });

  HintText WaterTemple_LongshotChest = HintText::Exclude({
                       //obscure text
                       Text{"#facing yourself# reveals", "se #vaincre soi-même# révèle", /*spanish*/"#luchar contra ti mismo# revela"},
                       Text{"a #dark reflection# of yourself guards", "son #propre reflet# cache", /*spanish*/"el #oscuro reflejo de ti mismo# guarda"},
                     },
                       //clear text
                       Text{"#Dark Link# guards", "l'#Ombre de @# protège", /*spanish*/"#Link Oscuro# guarda"}
  );


  HintText WaterTemple_MQ_CentralPillarChest = HintText::Exclude({
                       //obscure text
                       Text{"in the #depths of the Water Temple# lies", "le #coeur du temple de l'eau# cache", /*spanish*/"en las #profundidades del Templo del Agua# yace"},
  });

  HintText WaterTemple_MQ_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"fire in the Water Temple unlocks a #vast gate# revealing a chest with", "des #flammes au coeur du temple de l'eau# révèlent", /*spanish*/"el fuego en el Templo del Agua alza una #gran valla#, habiendo dentro"},
  });

  HintText WaterTemple_MQ_LongshotChest = HintText::Exclude({
                       //obscure text
                       Text{"#through a crack# in the Water Temple is", "le #mur fragile# du temple de l'eau cache", /*spanish*/"tras una #agrietada pared# del Templo del Agua yace"},
  });

  HintText WaterTemple_MQ_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#fire in the Water Temple# reveals", "des #flammes dans le temple de l'eau# révèlent", /*spanish*/"el #fuego en el Templo del Agua# revela"},
  });

  HintText WaterTemple_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"#sparring soldiers# in the Water Temple guard", "les #soldats du temple de l'eau# protègent", /*spanish*/"#acabar con unos soldados# del Templo del Agua revela"},
  });


  HintText SpiritTemple_ChildBridgeChest = HintText::Exclude({
                       //obscure text
                       Text{"a child conquers a #skull in green fire# in the Spirit Temple to reach", "le #crâne au halo vert dans le colosse# cache", /*spanish*/"el joven que #acabe con la calavera de verde fuego# del Templo del Espíritu encontrará"},
  });

  HintText SpiritTemple_ChildEarlyTorchesChest = HintText::Exclude({
                       //obscure text
                       Text{"a child can find a #caged chest# in the Spirit Temple with", "le #coffre embarré dans le colosse# contient", /*spanish*/"un joven puede encontrar un #cofre entre rejas# del Templo del Espíritu con"},
  });

  HintText SpiritTemple_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#across a pit of sand# in the Spirit Temple lies", "le #trou sableux dans le colosse# a", /*spanish*/"tras un #pozo de arena# del Templo del Espíritu yace"},
  });

  HintText SpiritTemple_EarlyAdultRightChest = HintText::Exclude({
                       //obscure text
                       Text{"#dodging boulders to collect silver rupees# in the Spirit Temple yields", "les #pièces argentées entourées de rochers dans le colosse# révèlent", /*spanish*/"#esquivar rocas y conseguir plateadas rupias# en el Templo del Espíritu conduce a"},
  });

  HintText SpiritTemple_FirstMirrorLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"a #shadow circling reflected light# in the Spirit Temple guards", "l'#ombre près d'un miroir# protège", /*spanish*/"un #círculo de reflectante luz# del Templo del Espíritu guarda"},
  });

  HintText SpiritTemple_FirstMirrorRightChest = HintText::Exclude({
                       //obscure text
                       Text{"a #shadow circling reflected light# in the Spirit Temple guards", "l'#ombre près d'un miroir# protège", /*spanish*/"un #círculo de reflectante luz# del Templo del Espíritu guarda"},
  });

  HintText SpiritTemple_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"#before a giant statue# in the Spirit Temple lies", "#devant la statue# dans le colosse gît", /*spanish*/"#ante una gran estatua# del Templo del Espíritu aguarda"},
  });

  HintText SpiritTemple_ChildClimbNorthChest = HintText::Exclude({
                       //obscure text
                       Text{"#lizards in the Spirit Temple# guard", "les #lézards dans le colosse# protègent", /*spanish*/"los #reptiles del Templo del Espíritu# guardan"},
  });

  HintText SpiritTemple_ChildClimbEastChest = HintText::Exclude({
                       //obscure text
                       Text{"#lizards in the Spirit Temple# guard", "les #lézards dans le colosse# protègent", /*spanish*/"los #reptiles del Templo del Espíritu# guardan"},
  });

  HintText SpiritTemple_SunBlockRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"#torchlight among Beamos# in the Spirit Temple reveals", "les #torches autour des Sentinelles# éclairent", /*spanish*/"las #antorchas junto a Beamos# del Templo del Espíritu revelan"},
  });

  HintText SpiritTemple_StatueRoomHandChest = HintText::Exclude({
                       //obscure text
                       Text{"a #statue in the Spirit Temple# holds", "la #statue dans le colosse# tient", /*spanish*/"una #estatua del Templo del Espíritu# esconde"},
  });

  HintText SpiritTemple_StatueRoomNortheastChest = HintText::Exclude({
                       //obscure text
                       Text{"on a #ledge by a statue# in the Spirit Temple rests", "#haut perché près de la statue# dans le colosse gît", /*spanish*/"al #borde de una estatua# del Templo del Espíritu yace"},
  });

  HintText SpiritTemple_NearFourArmosChest = HintText::Exclude({
                       //obscure text
                       Text{"those who #show the light among statues# in the Spirit Temple find", "le #soleil près des statues# cache", /*spanish*/"aquellos que #iluminen ante las estatuas# del Templo del Espíritu encontrarán"},
  });

  HintText SpiritTemple_HallwayRightInvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth in the Spirit Temple# reveals", "le #trésor invisible près du Hache-Viande# contient", /*spanish*/"el #Ojo de la Verdad# en el Templo del Espíritu revela"},
  });

  HintText SpiritTemple_HallwayLeftInvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth in the Spirit Temple# reveals", "le #trésor invisible près du Hache-Viande# contient", /*spanish*/"el #Ojo de la Verdad# en el Templo del Espíritu revela"},
  });

  HintText SpiritTemple_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"a #chest engulfed in flame# in the Spirit Temple holds", "le #coffre enflammé dans le colosse# contient", /*spanish*/"un #cofre rodeado de llamas# del Templo del Espíritu contiene"},
  });

  HintText SpiritTemple_TopmostChest = HintText::Exclude({
                       //obscure text
                       Text{"those who #show the light above the Colossus# find", "le #soleil au sommet du colosse# révèle", /*spanish*/"aquellos que #iluminen en lo alto del Coloso# encontrarán"},
  });


  HintText SpiritTemple_MQ_EntranceFrontLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"#lying unguarded# in the Spirit Temple is", "dans #l'entrée du colosse# se trouve", /*spanish*/"en la #entrada del Templo del Espíritu# yace"},
  });

  HintText SpiritTemple_MQ_EntranceBackRightChest = HintText::Exclude({
                       //obscure text
                       Text{"a #switch in a pillar# within the Spirit Temple drops", "l'#interrupteur dans un pilier# du colosse cache", /*spanish*/"el #interruptor de un pilar# del Templo del Espíritu revela"},
  });

  HintText SpiritTemple_MQ_EntranceFrontRightChest = HintText::Exclude({
                       //obscure text
                       Text{"#collecting rupees through a water jet# reveals", "les #pièces argentées dans le jet d'eau# du colosse révèlent", /*spanish*/"#hacerte con rupias tras un géiser# revela"},
  });

  HintText SpiritTemple_MQ_EntranceBackLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"an #eye blinded by stone# within the Spirit Temple conceals", "#l'oeil derrière le rocher# dans le colosse voit", /*spanish*/"#cegar a un ojo# del Templo del Espíritu revela"},
  });

  HintText SpiritTemple_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"surrounded by #fire and wrappings# lies", "près des #pierres tombales dans le colosse# gît", /*spanish*/"rodeado de #fuego y vendas# yace"},
  });

  HintText SpiritTemple_MQ_MapRoomEnemyChest = HintText::Exclude({
                       //obscure text
                       Text{"a child defeats a #gauntlet of monsters# within the Spirit Temple to find", "l'enfant qui vainc #plusieurs monstres# dans le colosse trouvera", /*spanish*/"el joven que derrote un #puñado de monstruos# del Templo del Espíritu encontrará"},
  });

  HintText SpiritTemple_MQ_ChildClimbNorthChest = HintText::Exclude({
                       //obscure text
                       Text{"#explosive sunlight# within the Spirit Temple uncovers", "le #rayon de lumière explosif dans le colosse# révèle", /*spanish*/"una #explosiva luz solar# del Templo del Espíritu revela"},
  });

  HintText SpiritTemple_MQ_ChildClimbSouthChest = HintText::Exclude({
                       //obscure text
                       Text{"#trapped by falling enemies# within the Spirit Temple is", "des #ennemis tombants# dans le colosse protègent", /*spanish*/"#rodeado de enemigos del cielo# del Templo del Espíritu yace"},
  });

  HintText SpiritTemple_MQ_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#blinding the colossus# unveils", "#l'oeil dans le colosse# voit", /*spanish*/"#cegar al coloso# revela"},
  });

  HintText SpiritTemple_MQ_StatueRoomLullabyChest = HintText::Exclude({
                       //obscure text
                       Text{"a #royal melody awakens the colossus# to reveal", "la #mélodie royale éveille le colosse# et révèle", /*spanish*/"la #melodía real que despierte al coloso# revelará"},
  });

  HintText SpiritTemple_MQ_StatueRoomInvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth# finds the colossus's hidden", "#l'oeil de vérité# verra dans le colosse", /*spanish*/"el #Ojo de la Verdad# en el Templo del Espíritu encuentra"},
  });

  HintText SpiritTemple_MQ_SilverBlockHallwayChest = HintText::Exclude({
                       //obscure text
                       Text{"#the old hide what the young find# to reveal", "l'#oeil dans le trou du bloc argent# dans le colosse voit", /*spanish*/"el #adulto esconde lo que el joven anhela# de encontrar"},
  });

  HintText SpiritTemple_MQ_SunBlockRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"#sunlight in a maze of fire# hides", "la lumière dans le labyrinthe de feu# du colosse révèle", /*spanish*/"la #luz solar de un ígneo laberinto# esconde"},
  });

  HintText SpiritTemple_MQ_LeeverRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"#across a pit of sand# in the Spirit Temple lies", "le #trou sableux# dans le colosse a", /*spanish*/"#a través del pozo de arena# del Templo del Espíritu yace"},
  });

  HintText SpiritTemple_MQ_BeamosRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"where #temporal stone blocks the path# within the Spirit Temple lies", "les #pierres temporelles# dans le colosse cachent", /*spanish*/"donde los #bloques temporales bloquean# en el Templo del Espíritu yace"},
  });

  HintText SpiritTemple_MQ_ChestSwitchChest = HintText::Exclude({
                       //obscure text
                       Text{"a #chest of double purpose# holds", "le #coffre à usage double# du colosse contient", /*spanish*/"un #cofre de doble uso# contiene"},
  });

  HintText SpiritTemple_MQ_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"a #temporal stone blocks the light# leading to", "la #pierre temporelle# le colosse fait ombre sur", /*spanish*/"un #bloque temporal bloquea la luz# que conduce a"},
  });

  HintText SpiritTemple_MQ_MirrorPuzzleInvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"those who #show the light above the Colossus# find", "le trésor invisible #au sommet du colosse# contient", /*spanish*/"aquellos que #revelen la luz sobre el Coloso# encontrarán"},
  });


  HintText ShadowTemple_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth# pierces a hall of faces to reveal", "l'#oeil de vérité# voit dans les couloirs du temple de l'ombre", /*spanish*/"el #Ojo de la Verdad# descubre un pasillo de facetas con"},
  });

  HintText ShadowTemple_HoverBootsChest = HintText::Exclude({
                       //obscure text
                       Text{"a #nether dweller in the Shadow Temple# holds", "le #spectre du temple de l'ombre# a", /*spanish*/"un #temido morador del Templo de las Sombras# guarda"},
                     },
                       //clear text
                       Text{"#Dead Hand in the Shadow Temple# holds", "le #Poigneur dans le temple de l'ombre# cache", /*spanish*/"la #Mano Muerta del Templo de las Sombras# guarda"}
  );

  HintText ShadowTemple_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#mummies revealed by the Eye of Truth# guard", "les #Gibdos dans les couloirs# du temple de l'ombre protègent", /*spanish*/"las #momias reveladas por el Ojo de la Verdad# guardan"},
  });

  HintText ShadowTemple_EarlySilverRupeeChest = HintText::Exclude({
                       //obscure text
                       Text{"#spinning scythes# protect", "les #faucheurs danseurs# du temple de l'ombre protègent", /*spanish*/"las #giratorias guadañas# protegen"},
  });

  HintText ShadowTemple_InvisibleBladesVisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"#invisible blades# guard", "les #faucheurs invisibles# du temple de l'ombre protègent", /*spanish*/"las #hojas invisibles# guardan"},
  });

  HintText ShadowTemple_InvisibleBladesInvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"#invisible blades# guard", "les #faucheurs invisibles# du temple de l'ombre protègent", /*spanish*/"las #hojas invisibles# guardan"},
  });

  HintText ShadowTemple_FallingSpikesLowerChest = HintText::Exclude({
                       //obscure text
                       Text{"#falling spikes# block the path to", "la #pluie de clous# surplombe", /*spanish*/"los #pinchos del techo# conducen a"},
  });

  HintText ShadowTemple_FallingSpikesUpperChest = HintText::Exclude({
                       //obscure text
                       Text{"#falling spikes# block the path to", "la #pluie de clous# surplombe", /*spanish*/"los #pinchos del techo# conducen a"},
  });

  HintText ShadowTemple_FallingSpikesSwitchChest = HintText::Exclude({
                       //obscure text
                       Text{"#falling spikes# block the path to", "la #pluie de clous# surplombe", /*spanish*/"los #pinchos del techo# conducen a"},
  });

  HintText ShadowTemple_InvisibleSpikesChest = HintText::Exclude({
                       //obscure text
                       Text{"the #dead roam among invisible spikes# guarding", "#parmi les clous invisibles# du temple de l'ombre se cache", /*spanish*/"los #muertos que vagan por pinchos invisibles# protegen"},
  });

  HintText ShadowTemple_WindHintChest = HintText::Exclude({
                       //obscure text
                       Text{"an #invisible chest guarded by the dead# holds", "le #trésor invisible du cul-de-sac# du temple de l'ombre contient", /*spanish*/"un #cofre invisible custodiado por los del más allá# contiene"},
  });

  HintText ShadowTemple_AfterWindEnemyChest = HintText::Exclude({
                       //obscure text
                       Text{"#mummies guarding a ferry# hide", "les #Gibdos qui bloquent le traversier# cachent", /*spanish*/"las #momias que protegen un navío# esconden"},
  });

  HintText ShadowTemple_AfterWindHiddenChest = HintText::Exclude({
                       //obscure text
                       Text{"#mummies guarding a ferry# hide", "les #Gibdos qui bloquent le traversier# cachent", /*spanish*/"las #momias que protegen un navío# esconden"},
  });

  HintText ShadowTemple_SpikeWallsLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"#walls consumed by a ball of fire# reveal", "le #piège de bois# du temple de l'ombre cache", /*spanish*/"las #paredes consumidas por una esfera ígnea# revelan"},
  });

  HintText ShadowTemple_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"#walls consumed by a ball of fire# reveal", "le #piège de bois# du temple de l'ombre cache", /*spanish*/"las #paredes consumidas por una esfera ígnea# revelan"},
  });

  HintText ShadowTemple_FreestandingKey = HintText::Exclude({
                       //obscure text
                       Text{"#inside a burning skull# lies", "#dans un crâne enflammé# gît", /*spanish*/"en el #interior de una calavera en llamas# aguarda"},
  });


  HintText ShadowTemple_MQ_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth# pierces a hall of faces to reveal", "l'#oeil de vérité# voit dans les couloirs du temple de l'ombre", /*spanish*/"el #Ojo de la Verdad# descubre un pasillo de facetas con"},
  });

  HintText ShadowTemple_MQ_HoverBootsChest = HintText::Exclude({
                       //obscure text
                       Text{"#Dead Hand in the Shadow Temple# holds", "le #Poigneur dans le temple de l'ombre# cache", /*spanish*/"la #Mano Muerta del Templo de las Sombras# guarda"},
  });

  HintText ShadowTemple_MQ_EarlyGibdosChest = HintText::Exclude({
                       //obscure text
                       Text{"#mummies revealed by the Eye of Truth# guard", "les #Gibdos dans les couloirs# du temple de l'ombre protègent", /*spanish*/"las #momias reveladas por el Ojo de la Verdad# guardan"},
  });

  HintText ShadowTemple_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"#spinning scythes# protect", "les #faucheurs danseurs# du temple de l'ombre protègent", /*spanish*/"las #giratorias guadañas# protegen"},
  });

  HintText ShadowTemple_MQ_BeamosSilverRupeesChest = HintText::Exclude({
                       //obscure text
                       Text{"#collecting rupees in a vast cavern# with the Shadow Temple unveils", "les #pièces argentées dans le temple de l'ombre# révèlent", /*spanish*/"hacerte con las #rupias en una gran caverna# del Templo de las Sombras revela"},
  });

  HintText ShadowTemple_MQ_FallingSpikesSwitchChest = HintText::Exclude({
                       //obscure text
                       Text{"#falling spikes# block the path to", "la #pluie de clous# surplombe", /*spanish*/"los #pinchos del techo# conducen a"},
  });

  HintText ShadowTemple_MQ_FallingSpikesLowerChest = HintText::Exclude({
                       //obscure text
                       Text{"#falling spikes# block the path to", "la #pluie de clous# surplombe", /*spanish*/"los #pinchos del techo# conducen a"},
  });

  HintText ShadowTemple_MQ_FallingSpikesUpperChest = HintText::Exclude({
                       //obscure text
                       Text{"#falling spikes# block the path to", "la #pluie de clous# surplombe", /*spanish*/"los #pinchos del techo# conducen a"},
  });

  HintText ShadowTemple_MQ_InvisibleSpikesChest = HintText::Exclude({
                       //obscure text
                       Text{"the #dead roam among invisible spikes# guarding", "#parmi les clous invisibles# du temple de l'ombre se cache", /*spanish*/"los #muertos que vagan por pinchos invisibles# protegen"},
  });

  HintText ShadowTemple_MQ_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"#walls consumed by a ball of fire# reveal", "le #piège de bois# du temple de l'ombre cache", /*spanish*/"las #paredes consumidas por una esfera ígnea# revelan"},
  });

  HintText ShadowTemple_MQ_SpikeWallsLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"#walls consumed by a ball of fire# reveal", "le #piège de bois# du temple de l'ombre cache", /*spanish*/"las #paredes consumidas por una esfera ígnea# revelan"},
  });

  HintText ShadowTemple_MQ_StalfosRoomChest = HintText::Exclude({
                       //obscure text
                       Text{"near an #empty pedestal# within the Shadow Temple lies", "#près d'un pédestal vide du temple de l'ombre# gît", /*spanish*/"cerca de un #vacío pedestal# del Templo de las Sombras yace"},
  });

  HintText ShadowTemple_MQ_InvisibleBladesInvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"#invisible blades# guard", "les #faucheurs invisibles# du temple de l'ombre protègent", /*spanish*/"las #hojas invisibles# guardan"},
  });

  HintText ShadowTemple_MQ_InvisibleBladesVisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"#invisible blades# guard", "les #faucheurs invisibles# du temple de l'ombre protègent", /*spanish*/"las #hojas invisibles# guardan"},
  });

  HintText ShadowTemple_MQ_WindHintChest = HintText::Exclude({
                       //obscure text
                       Text{"an #invisible chest guarded by the dead# holds", "le #trésor invisible du cul-de-sac# du temple de l'ombre contient", /*spanish*/"un #cofre invisible custodiado por los del más allá# contiene"},
  });

  HintText ShadowTemple_MQ_AfterWindHiddenChest = HintText::Exclude({
                       //obscure text
                       Text{"#mummies guarding a ferry# hide", "les #Gibdos qui bloquent le traversier# cachent", /*spanish*/"las #momias que protegen un navío# esconden"},
  });

  HintText ShadowTemple_MQ_AfterWindEnemyChest = HintText::Exclude({
                       //obscure text
                       Text{"#mummies guarding a ferry# hide", "les #Gibdos qui bloquent le traversier# cachent", /*spanish*/"las #momias que protegen un navío# esconden"},
  });

  HintText ShadowTemple_MQ_NearShipInvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"#caged near a ship# lies", "#dans une cage près du traversier# gît", /*spanish*/"#entre rejas al lado de un navío# yace"},
  });

  HintText ShadowTemple_MQ_FreestandingKey = HintText::Exclude({
                       //obscure text
                       Text{"#behind three burning skulls# lies", "#derrière trois crânes enflammés# gît", /*spanish*/"tras #tres ardientes calaveras# yace"},
  });


  HintText BottomOfTheWell_FrontLeftFakeWallChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth in the well# reveals", "l'#oeil de vérité dans le puits# révèle", /*spanish*/"el #Ojo de la Verdad en el pozo# revela"},
  });

  HintText BottomOfTheWell_FrontCenterBombableChest = HintText::Exclude({
                       //obscure text
                       Text{"#gruesome debris# in the well hides", "des #débris dans le puits# cachent", /*spanish*/"unos #horripilantes escombros# del pozo esconden"},
  });

  HintText BottomOfTheWell_RightBottomFakeWallChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth in the well# reveals", "l'#oeil de vérité dans le puits# révèle", /*spanish*/"el #Ojo de la Verdad en el pozo# revela"},
  });

  HintText BottomOfTheWell_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"a #hidden entrance to a cage# in the well leads to", "dans un #chemin caché dans le puits# gît", /*spanish*/"la #entrada oculta de una celda# del pozo conduce a"},
  });

  HintText BottomOfTheWell_CenterSkulltulaChest = HintText::Exclude({
                       //obscure text
                       Text{"a #spider guarding a cage# in the well protects", "l'#araignée dans la cage du puits# protège", /*spanish*/"una #araña protegiendo una celda# del pozo guarda"},
  });

  HintText BottomOfTheWell_BackLeftBombableChest = HintText::Exclude({
                       //obscure text
                       Text{"#gruesome debris# in the well hides", "des #débris dans le puits# cachent", /*spanish*/"unos #horripilantes escombros# del pozo esconden"},
  });

  HintText BottomOfTheWell_InvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"#Dead Hand's invisible secret# is", "le #trésor invisible du Poigneur# est", /*spanish*/"el #secreto invisible de la Mano Muerta# se trata de"},
  });

  HintText BottomOfTheWell_UnderwaterFrontChest = HintText::Exclude({
                       //obscure text
                       Text{"a #royal melody in the well# uncovers", "la #mélodie royale révèle dans le puits#", /*spanish*/"una #melodía real en el pozo# revela"},
  });

  HintText BottomOfTheWell_UnderwaterLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"a #royal melody in the well# uncovers", "la #mélodie royale révèle dans le puits#", /*spanish*/"una #melodía real en el pozo# revela"},
  });

  HintText BottomOfTheWell_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"in the #depths of the well# lies", "#dans le coeur du puits# gît", /*spanish*/"en las #profundidades del pozo# yace"},
  });

  HintText BottomOfTheWell_FireKeeseChest = HintText::Exclude({
                       //obscure text
                       Text{"#perilous pits# in the well guard the path to", "#trois trous# dans le puits protègent", /*spanish*/"#peligrosos fosos# del pozo conducen a"},
  });

  HintText BottomOfTheWell_LikeLikeChest = HintText::Exclude({
                       //obscure text
                       Text{"#locked in a cage# in the well lies", "#dans une cage# du puits gît", /*spanish*/"#entre rejas# en el pozo yace"},
  });

  HintText BottomOfTheWell_FreestandingKey = HintText::Exclude({
                       //obscure text
                       Text{"#inside a coffin# hides", "dans #un cercueil# gît", /*spanish*/"en el #interior de un ataúd# yace"},
  });


  HintText BottomOfTheWell_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"a #royal melody in the well# uncovers", "la #mélodie royale révèle dans le puits#", /*spanish*/"una #melodía real en el pozo# revela"},
  });

  HintText BottomOfTheWell_MQ_LensOfTruthChest = HintText::Exclude({
                       //obscure text
                       Text{"an #army of the dead# in the well guards", "l'#armée des morts# dans le puits protège", /*spanish*/"un #ejército del más allá# del pozo guarda"},
  });

  HintText BottomOfTheWell_MQ_DeadHandFreestandingKey = HintText::Exclude({
                       //obscure text
                       Text{"#Dead Hand's explosive secret# is", "le #secret explosif du Poigneur# est", /*spanish*/"el #explosivo secreto de la Mano Muerta# se trata de"},
  });

  HintText BottomOfTheWell_MQ_EastInnerRoomFreestandingKey = HintText::Exclude({
                       //obscure text
                       Text{"an #invisible path in the well# leads to", "dans un #chemin caché dans le puits# gît", /*spanish*/"un #camino invisible del pozo# conduce a"},
  });


  HintText IceCavern_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"#winds of ice# surround", "#figé dans la glace rouge# gît", /*spanish*/"#heladas borrascas# rodean"},
  });

  HintText IceCavern_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"a #wall of ice# protects", "#un mur de glace rouge# cache", /*spanish*/"una #gélida pared# protege"},
  });

  HintText IceCavern_IronBootsChest = HintText::Exclude({
                       //obscure text
                       Text{"a #monster in a frozen cavern# guards", "le #monstre de la caverne de glace# protège", /*spanish*/"un #monstruo de una helada caverna# guarda"},
  });

  HintText IceCavern_FreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"a #wall of ice# protects", "un mur de glace rouge# cache", /*spanish*/"una #gélida pared# protege"},
  });


  HintText IceCavern_MQ_IronBootsChest = HintText::Exclude({
                       //obscure text
                       Text{"a #monster in a frozen cavern# guards", "le #monstre de la caverne de glace# protège", /*spanish*/"un #monstruo de una helada caverna# guarda"},
  });

  HintText IceCavern_MQ_CompassChest = HintText::Exclude({
                       //obscure text
                       Text{"#winds of ice# surround", "#entouré de vent glacial# gît", /*spanish*/"#heladas borrascas# rodean"},
  });

  HintText IceCavern_MQ_MapChest = HintText::Exclude({
                       //obscure text
                       Text{"a #wall of ice# protects", "#un mur de glace rouge# cache", /*spanish*/"una #gélida pared# protege"},
  });

  HintText IceCavern_MQ_FreestandingPoH = HintText::Exclude({
                       //obscure text
                       Text{"#winds of ice# surround", "#entouré de vent glacial# gît", /*spanish*/"#heladas borrascas# rodean"},
  });


  HintText GerudoTrainingGrounds_LobbyLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"a #blinded eye in the Gerudo Training Grounds# drops", "l'#Oeil dans le gymnase Gerudo# voit", /*spanish*/"#cegar un ojo en el Centro de Instrucción Gerudo# revela"},
  });

  HintText GerudoTrainingGrounds_LobbyRightChest = HintText::Exclude({
                       //obscure text
                       Text{"a #blinded eye in the Gerudo Training Grounds# drops", "l'#Oeil dans le gymnase Gerudo# voit", /*spanish*/"#cegar un ojo en el Centro de Instrucción Gerudo# revela"},
  });

  HintText GerudoTrainingGrounds_StalfosChest = HintText::Exclude({
                       //obscure text
                       Text{"#soldiers walking on shifting sands# in the Gerudo Training Grounds guard", "les #squelettes# du gymnase Gerudo protègent", /*spanish*/"#soldados en resbaladizas arenas# del Centro de Instrucción Gerudo protegen"},
  });

  HintText GerudoTrainingGrounds_BeamosChest = HintText::Exclude({
                       //obscure text
                       Text{"#reptilian warriors# in the Gerudo Training Grounds protect", "les #lézards# dans le gymnase Gerudo protègent", /*spanish*/"#unos escamosos guerreros# del Centro de Instrucción Gerudo protegen"},
  });

  HintText GerudoTrainingGrounds_HiddenCeilingChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth# in the Gerudo Training Grounds reveals", "#bien caché# dans le gymnase Gerudo gît", /*spanish*/"el #Ojo de la Verdad# en el Centro de Instrucción Gerudo revela"},
  });

  HintText GerudoTrainingGrounds_MazePathFirstChest = HintText::Exclude({
                       //obscure text
                       Text{"the first prize of #the thieves' training# is", "le #premier trésor du gymnase Gerudo# est", /*spanish*/"el primer premio de la #instrucción ladrona# se trata de"},
  });

  HintText GerudoTrainingGrounds_MazePathSecondChest = HintText::Exclude({
                       //obscure text
                       Text{"the second prize of #the thieves' training# is", "le #deuxième trésor du gymnase Gerudo# est", /*spanish*/"el segundo premio de la #instrucción ladrona# se trata de"},
  });

  HintText GerudoTrainingGrounds_MazePathThirdChest = HintText::Exclude({
                       //obscure text
                       Text{"the third prize of #the thieves' training# is", "le #troisième trésor du gymnase Gerudo# est", /*spanish*/"el tercer premio de la #instrucción ladrona# se trata de"},
  });

  HintText GerudoTrainingGrounds_MazeRightCentralChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Song of Time# in the Gerudo Training Grounds leads to", "le #chant du temps# révèle dans le gymnase Gerudo", /*spanish*/"la #Canción del Tiempo# en el Centro de Instrucción Gerudo conduce a"},
  });

  HintText GerudoTrainingGrounds_MazeRightSideChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Song of Time# in the Gerudo Training Grounds leads to", "le #chant du temps# révèle dans le gymnase Gerudo", /*spanish*/"la #Canción del Tiempo# en el Centro de Instrucción Gerudo conduce a"},
  });

  HintText GerudoTrainingGrounds_HammerRoomClearChest = HintText::Exclude({
                       //obscure text
                       Text{"#fiery foes# in the Gerudo Training Grounds guard", "les #limaces de feu# du gymnase Gerudo protègent", /*spanish*/"unos #candentes enemigos# del Centro de Instrucción Gerudo guardan"},
  });

  HintText GerudoTrainingGrounds_HammerRoomSwitchChest = HintText::Exclude({
                       //obscure text
                       Text{"#engulfed in flame# where thieves train lies", "le #trésor enflammé# du gymnase Gerudo est", /*spanish*/"donde entrenan las ladronas #entre llamas# yace"},
  });

  HintText GerudoTrainingGrounds_EyeStatueChest = HintText::Exclude({
                       //obscure text
                       Text{"thieves #blind four faces# to find", "l'#épreuve d'archerie# du gymnase Gerudo donne", /*spanish*/"las ladronas #ciegan cuatro facetas# para hallar"},
  });

  HintText GerudoTrainingGrounds_NearScarecrowChest = HintText::Exclude({
                       //obscure text
                       Text{"thieves #blind four faces# to find", "l'#épreuve d'archerie# du gymnase Gerudo donne", /*spanish*/"las ladronas #ciegan cuatro facetas# para hallar"},
  });

  HintText GerudoTrainingGrounds_BeforeHeavyBlockChest = HintText::Exclude({
                       //obscure text
                       Text{"#before a block of silver# thieves can find", "#près d'un bloc argent# dans le gymnase Gerudo gît", /*spanish*/"#ante un plateado bloque# las ladronas hallan"},
  });

  HintText GerudoTrainingGrounds_HeavyBlockFirstChest = HintText::Exclude({
                       //obscure text
                       Text{"a #feat of strength# rewards thieves with", "#derrière un bloc argent# dans le gymnase Gerudo gît", /*spanish*/"una #hazaña de fuerza# premia a las ladronas con"},
  });

  HintText GerudoTrainingGrounds_HeavyBlockSecondChest = HintText::Exclude({
                       //obscure text
                       Text{"a #feat of strength# rewards thieves with", "#derrière un bloc argent# dans le gymnase Gerudo gît", /*spanish*/"una #hazaña de fuerza# premia a las ladronas con"},
  });

  HintText GerudoTrainingGrounds_HeavyBlockThirdChest = HintText::Exclude({
                       //obscure text
                       Text{"a #feat of strength# rewards thieves with", "#derrière un bloc argent# dans le gymnase Gerudo gît", /*spanish*/"una #hazaña de fuerza# premia a las ladronas con"},
  });

  HintText GerudoTrainingGrounds_HeavyBlockFourthChest = HintText::Exclude({
                       //obscure text
                       Text{"a #feat of strength# rewards thieves with", "#derrière un bloc argent# dans le gymnase Gerudo gît", /*spanish*/"una #hazaña de fuerza# premia a las ladronas con"},
  });

  HintText GerudoTrainingGrounds_FreestandingKey = HintText::Exclude({
                       //obscure text
                       Text{"the #Song of Time# in the Gerudo Training Grounds leads to", "le #chant du temps# révèle dans le gymnase Gerudo", /*spanish*/"la #Canción del Tiempo# en el Centro de Instrucción Gerudo conduce a"},
  });


  HintText GerudoTrainingGrounds_MQ_LobbyRightChest = HintText::Exclude({
                       //obscure text
                       Text{"#thieves prepare for training# with", "dans #l'entrée du gymnase Gerudo# gît", /*spanish*/"las #ladronas se instruyen# con"},
  });

  HintText GerudoTrainingGrounds_MQ_LobbyLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"#thieves prepare for training# with", "dans #l'entrée du gymnase Gerudo# gît", /*spanish*/"las #ladronas se instruyen# con"},
  });

  HintText GerudoTrainingGrounds_MQ_FirstIronKnuckleChest = HintText::Exclude({
                       //obscure text
                       Text{"#soldiers walking on shifting sands# in the Gerudo Training Grounds guard", "les #squelettes# du gymnase Gerudo protègent", /*spanish*/"#soldados en resbaladizas arenas# del Centro de Instrucción Gerudo protegen"},
  });

  HintText GerudoTrainingGrounds_MQ_BeforeHeavyBlockChest = HintText::Exclude({
                       //obscure text
                       Text{"#before a block of silver# thieves can find", "#près d'un bloc argent# dans le gymnase Gerudo gît", /*spanish*/"#ante un plateado bloque# las ladronas hallang"},
  });

  HintText GerudoTrainingGrounds_MQ_EyeStatueChest = HintText::Exclude({
                       //obscure text
                       Text{"thieves #blind four faces# to find", "l'#épreuve d'archerie# du gymnase Gerudo donne", /*spanish*/"las ladronas #ciegan cuatro facetas# para hallar"},
  });

  HintText GerudoTrainingGrounds_MQ_FlameCircleChest = HintText::Exclude({
                       //obscure text
                       Text{"#engulfed in flame# where thieves train lies", "le #trésor enflammé# du gymnase Gerudo est", /*spanish*/"donde entrenan las ladronas #entre llamas# yace"},
  });

  HintText GerudoTrainingGrounds_MQ_SecondIronKnuckleChest = HintText::Exclude({
                       //obscure text
                       Text{"#fiery foes# in the Gerudo Training Grounds guard", "les #ennemis de feu# du gymnase Gerudo protègent", /*spanish*/"unos #candentes enemigos# del Centro de Instrucción Gerudo guardan"},
  });

  HintText GerudoTrainingGrounds_MQ_DinolfosChest = HintText::Exclude({
                       //obscure text
                       Text{"#reptilian warriors# in the Gerudo Training Grounds protect", "les #lézards# dans le gymnase Gerudo protègent", /*spanish*/"#unos escamosos guerreros# del Centro de Instrucción Gerudo protegen"},
  });

  HintText GerudoTrainingGrounds_MQ_MazeRightCentralChest = HintText::Exclude({
                       //obscure text
                       Text{"a #path of fire# leads thieves to", "dans le #chemin enflammé# dans le gymnase Gerudo gît", /*spanish*/"un #camino de fuego# conduce a las ladronas a"},
  });

  HintText GerudoTrainingGrounds_MQ_MazePathFirstChest = HintText::Exclude({
                       //obscure text
                       Text{"the first prize of #the thieves' training# is", "le #premier trésor du gymnase Gerudo# est", /*spanish*/"el primer premio de la #instrucción ladrona# se trata de"},
  });

  HintText GerudoTrainingGrounds_MQ_MazeRightSideChest = HintText::Exclude({
                       //obscure text
                       Text{"a #path of fire# leads thieves to", "dans le #chemin enflammé# dans le gymnase Gerudo gît", /*spanish*/"un #camino de fuego# conduce a las ladronas a"},
  });

  HintText GerudoTrainingGrounds_MQ_MazePathThirdChest = HintText::Exclude({
                       //obscure text
                       Text{"the third prize of #the thieves' training# is", "le #troisième trésor du gymnase Gerudo# est", /*spanish*/"el tercer premio de la #instrucción ladrona# se trata de"},
  });

  HintText GerudoTrainingGrounds_MQ_MazePathSecondChest = HintText::Exclude({
                       //obscure text
                       Text{"the second prize of #the thieves' training# is", "le #deuxième trésor du gymnase Gerudo# est", /*spanish*/"el segundo premio de la #instrucción ladrona# se trata de"},
  });

  HintText GerudoTrainingGrounds_MQ_HiddenCeilingChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth# in the Gerudo Training Grounds reveals", "#bien caché# dans le gymnase Gerudo gît", /*spanish*/"el #Ojo de la Verdad# en el Centro de Instrucción Gerudo revela"},
  });

  HintText GerudoTrainingGrounds_MQ_HeavyBlockChest = HintText::Exclude({
                       //obscure text
                       Text{"a #feat of strength# rewards thieves with", "#derrière un bloc argent# dans le gymnase Gerudo gît", /*spanish*/"una #hazaña de fuerza# premia a las ladronas con"},
  });


  HintText GanonsCastle_BossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"the #Evil King# hoards", "le #Roi du Mal# possède", /*spanish*/"el #Rey del Mal# acapara"},
  });


  HintText GanonsCastle_ForestTrialChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the wilds# holds", "l'#épreuve des bois# contient", /*spanish*/"la #prueba de la naturaleza# brinda"},
  });

  HintText GanonsCastle_WaterTrialLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the seas# holds", "l'#épreuve des mers# contient", /*spanish*/"la #prueba del mar# brinda"},
  });

  HintText GanonsCastle_WaterTrialRightChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the seas# holds", "l'#épreuve des mers# contient", /*spanish*/"la #prueba del mar# brinda"},
  });

  HintText GanonsCastle_ShadowTrialFrontChest = HintText::Exclude({
                       //obscure text
                       Text{"#music in the test of darkness# unveils", "la #musique dans l'épreuve des ténèbres# révèle", /*spanish*/"la #música en la prueba de la oscuridad# revela"},
  });

  HintText GanonsCastle_ShadowTrialGoldenGauntletsChest = HintText::Exclude({
                       //obscure text
                       Text{"#light in the test of darkness# unveils", "la #lumière dans l'épreuve des ténèbres# révèle", /*spanish*/"la #luz en la prueba de la oscuridad# revela"},
  });

  HintText GanonsCastle_SpiritTrialCrystalSwitchChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the sands# holds", "l'#épreuve des sables# contient", /*spanish*/"la #prueba de las arenas# brinda"},
  });

  HintText GanonsCastle_SpiritTrialInvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the sands# holds", "l'#épreuve des sables# contient", /*spanish*/"la #prueba de las arenas# brinda"},
  });

  HintText GanonsCastle_LightTrialFirstLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of radiance# holds", "l'#épreuve du ciel# contient", /*spanish*/"la #prueba del resplandor# brinda"},
  });

  HintText GanonsCastle_LightTrialSecondLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of radiance# holds", "l'#épreuve du ciel# contient", /*spanish*/"la #prueba del resplandor# brinda"},
  });

  HintText GanonsCastle_LightTrialThirdLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of radiance# holds", "l'#épreuve du ciel# contient", /*spanish*/"la #prueba del resplandor# brinda"},
  });

  HintText GanonsCastle_LightTrialFirstRightChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of radiance# holds", "l'#épreuve du ciel# contient", /*spanish*/"la #prueba del resplandor# brinda"},
  });

  HintText GanonsCastle_LightTrialSecondRightChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of radiance# holds", "l'#épreuve du ciel# contient", /*spanish*/"la #prueba del resplandor# brinda"},
  });

  HintText GanonsCastle_LightTrialThirdRightChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of radiance# holds", "l'#épreuve du ciel# contient", /*spanish*/"la #prueba del resplandor# brinda"},
  });

  HintText GanonsCastle_LightTrialInvisibleEnemiesChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of radiance# holds", "l'#épreuve du ciel# contient", /*spanish*/"la #prueba del resplandor# brinda"},
  });

  HintText GanonsCastle_LightTrialLullabyChest = HintText::Exclude({
                       //obscure text
                       Text{"#music in the test of radiance# reveals", "la #musique dans l'épreuve du ciel# révèle", /*spanish*/"la #música en la prueba del resplandor# revela"},
  });


  HintText GanonsCastle_MQ_WaterTrialChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the seas# holds", "l'#épreuve des mers# contient", /*spanish*/"la #prueba del mar# brinda"},
  });

  HintText GanonsCastle_MQ_ForestTrialEyeSwitchChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the wilds# holds", "l'#épreuve des bois# contient", /*spanish*/"la #prueba de la naturaleza# brinda"},
  });

  HintText GanonsCastle_MQ_ForestTrialFrozenEyeSwitchChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the wilds# holds", "l'#épreuve des bois# contient", /*spanish*/"la #prueba de la naturaleza# brinda"},
  });

  HintText GanonsCastle_MQ_LightTrialLullabyChest = HintText::Exclude({
                       //obscure text
                       Text{"#music in the test of radiance# reveals", "la #musique dans l'épreuve du ciel# révèle", /*spanish*/"la #música en la prueba del resplandor# revela"},
  });

  HintText GanonsCastle_MQ_ShadowTrialBombFlowerChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of darkness# holds", "l'#épreuve des ténèbres# contient", /*spanish*/"la #prueba de la oscuridad# brinda"},
  });

  HintText GanonsCastle_MQ_ShadowTrialEyeSwitchChest = HintText::Exclude({
                       //obscure text
                       Text{"the #test of darkness# holds", "l'#épreuve des ténèbres# contient", /*spanish*/"la #prueba de la oscuridad# brinda"},
  });

  HintText GanonsCastle_MQ_SpiritTrialGoldenGauntletsChest = HintText::Exclude({
                       //obscure text
                       Text{"#reflected light in the test of the sands# reveals", "le #soleil dans l'épreuve des sables# révèle", /*spanish*/"#reflejar la luz en la prueba de las arenas# revela"},
  });

  HintText GanonsCastle_MQ_SpiritTrialSunBackRightChest = HintText::Exclude({
                       //obscure text
                       Text{"#reflected light in the test of the sands# reveals", "le #soleil dans l'épreuve des sables# révèle", /*spanish*/"#reflejar la luz en la prueba de las arenas# revela"},
  });

  HintText GanonsCastle_MQ_SpiritTrialSunBackLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"#reflected light in the test of the sands# reveals", "le #soleil dans l'épreuve des sables# révèle", /*spanish*/"#reflejar la luz en la prueba de las arenas# revela"},
  });

  HintText GanonsCastle_MQ_SpiritTrialSunFrontLeftChest = HintText::Exclude({
                       //obscure text
                       Text{"#reflected light in the test of the sands# reveals", "le #soleil dans l'épreuve des sables# révèle", /*spanish*/"#reflejar la luz en la prueba de las arenas# revela"},
  });

  HintText GanonsCastle_MQ_SpiritTrialFirstChest = HintText::Exclude({
                       //obscure text
                       Text{"#reflected light in the test of the sands# reveals", "le #soleil dans l'épreuve des sables# révèle", /*spanish*/"#reflejar la luz en la prueba de las arenas# revela"},
  });

  HintText GanonsCastle_MQ_SpiritTrialInvisibleChest = HintText::Exclude({
                       //obscure text
                       Text{"#reflected light in the test of the sands# reveals", "le #soleil dans l'épreuve des sables# révèle", /*spanish*/"#reflejar la luz en la prueba de las arenas# revela"},
  });

  HintText GanonsCastle_MQ_ForestTrialFreestandingKey = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the wilds# holds", "l'#épreuve des bois# révèle", /*spanish*/"la #prueba de la naturaleza# brinda"},
  });


  HintText DekuTree_QueenGohmaHeart = HintText::Exclude({
                       //obscure text
                       Text{"the #Parasitic Armored Arachnid# holds", "le #monstre insectoïde géant# possède", /*spanish*/"el #arácnido parasitario acorazado# porta"},
                     },
                       //clear text
                       Text{"#Queen Gohma# holds", "la #Reine Gohma# possède", /*spanish*/"la #Reina Goma# porta"}
  );

  HintText DodongosCavern_KingDodongoHeart = HintText::Exclude({
                       //obscure text
                       Text{"the #Infernal Dinosaur# holds", "le #dinosaure infernal# possède", /*spanish*/"el #dinosaurio infernal# porta"},
                     },
                       //clear text
                       Text{"#King Dodongo# holds", "le #Roi Dodongo# possède", /*spanish*/"el #Rey Dodongo# porta"}
  );

  HintText JabuJabusBelly_BarinadeHeart = HintText::Exclude({
                       //obscure text
                       Text{"the #Bio-Electric Anemone# holds", "l'#anémone bioélectrique# possède", /*spanish*/"la #anémona bioeléctrica# porta"},
                     },
                       //clear text
                       Text{"#Barinade# holds", "#Barinade# possède", /*spanish*/"#Barinade# porta"}
  );

  HintText ForestTemple_PhantomGanonHeart = HintText::Exclude({
                       //obscure text
                       Text{"the #Evil Spirit from Beyond# holds", "l'#esprit maléfique de l'au-delà# possède", /*spanish*/"el #espíritu maligno de ultratumba# porta"},
                     },
                       //clear text
                       Text{"#Phantom Ganon# holds", "#Ganon Spectral# possède", /*spanish*/"#Ganon Fantasma# porta"}
  );

  HintText FireTemple_VolvagiaHeart = HintText::Exclude({
                       //obscure text
                       Text{"the #Subterranean Lava Dragon# holds", "le #dragon des profondeurs# possède", /*spanish*/"el #dragón de lava subterráneo# porta"},
                     },
                       //clear text
                       Text{"#Volvagia# holds", "#Volvagia# possède", /*spanish*/"#Volvagia# porta"}
  );

  HintText WaterTemple_MorphaHeart = HintText::Exclude({
                       //obscure text
                       Text{"the #Giant Aquatic Amoeba# holds", "l'#amibe aquatique géante# possède", /*spanish*/"la #ameba acuática gigante# porta"},
                     },
                       //clear text
                       Text{"#Morpha# holds", "#Morpha# possède", /*spanish*/"#Morpha# porta"}
  );

  HintText SpiritTemple_TwinrovaHeart = HintText::Exclude({
                       //obscure text
                       Text{"the #Sorceress Sisters# hold", "#les sorcières jumelles# possède", /*spanish*/"las #hermanas hechiceras# portan"},
                     },
                       //clear text
                       Text{"#Twinrova# holds", /*#Twinrova# possède*/"", /*spanish*/"#Birova# porta"}
  );

  HintText ShadowTemple_BongoBongoHeart = HintText::Exclude({
                       //obscure text
                       Text{"the #Phantom Shadow Beast# holds", "le #monstre de l'ombre# possède", /*spanish*/"la #alimaña oscura espectral# porta"},
                     },
                       //clear text
                       Text{"#Bongo Bongo# holds", /*#Bongo Bongo# possède*/"", /*spanish*/"#Bongo Bongo# porta"}
  );


  HintText DekuTree_GS_BasementBackRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider deep within the Deku Tree# hides", "la #Skulltula au coeur de l'arbre Mojo# a", /*spanish*/"una #araña en las profundidades del Árbol Deku# otorga"},
  });

  HintText DekuTree_GS_BasementGate = HintText::Exclude({
                       //obscure text
                       Text{"a #web protects a spider# within the Deku Tree holding", "la #Skulltula derrière une toile dans l'arbre Mojo# a", /*spanish*/"una #araña protegida por su tela# del Árbol Deku otorga"},
  });

  HintText DekuTree_GS_BasementVines = HintText::Exclude({
                       //obscure text
                       Text{"a #web protects a spider# within the Deku Tree holding", "la #Skulltula derrière une toile dans l'arbre Mojo# a", /*spanish*/"una #araña protegida por su tela# del Árbol Deku otorga"},
  });

  HintText DekuTree_GS_CompassRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider atop the Deku Tree# holds", "la #Skulltula au sommet de l'arbre Mojo# a", /*spanish*/"una #araña en lo alto del Árbol Deku# otorga"},
  });


  HintText DekuTree_MQ_GS_Lobby = HintText::Exclude({
                       //obscure text
                       Text{"a #spider in a crate# within the Deku Tree hides", "la #Skulltula dans une boîte dans l'arbre Mojo# a", /*spanish*/"una #araña bajo una caja# del Árbol Deku otorga"},
  });

  HintText DekuTree_MQ_GS_CompassRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #wall of rock protects a spider# within the Deku Tree holding", "la #Skulltula derrière des rochers dans l'arbre Mojo# a", /*spanish*/"una #araña protegida por una pared rocosa# del Árbol Deku otorga"},
  });

  HintText DekuTree_MQ_GS_BasementBackRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider deep within the Deku Tree# hides", "la #Skulltula au coeur de l'arbre Mojo# a", /*spanish*/"una #araña en las profundidades del Árbol Deku# otorga"},
  });


  HintText DodongosCavern_GS_VinesAboveStairs = HintText::Exclude({
                       //obscure text
                       Text{"a #spider entangled in vines# in Dodongo's Cavern guards", "la #Skulltula sur les vignes dans la caverne Dodongo# a", /*spanish*/"una #araña sobre unas cepas# de la Cueva de los Dodongos otorga"},
  });

  HintText DodongosCavern_GS_Scarecrow = HintText::Exclude({
                       //obscure text
                       Text{"a #spider among explosive slugs# hides", "la #Skulltula dans l'alcove du couloir dans la caverne Dodongo# a", /*spanish*/"una #araña rodeada de explosivos gusanos# otorga"},
  });

  HintText DodongosCavern_GS_AlcoveAboveStairs = HintText::Exclude({
                       //obscure text
                       Text{"a #spider just out of reach# in Dodongo's Cavern holds", "la #Skulltula au haut des escaliers de la caverne Dodongo# a", /*spanish*/"una #araña fuera del alcance# de la Cueva de los Dodongos otorga"},
  });

  HintText DodongosCavern_GS_BackRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider behind a statue# in Dodongo's Cavern holds", "la #Skulltula au coeur de la caverne Dodongo# a", /*spanish*/"una #araña tras una estatua# de la Cueva de los Dodongos otorga"},
  });

  HintText DodongosCavern_GS_SideRoomNearLowerLizalfos = HintText::Exclude({
                       //obscure text
                       Text{"a #spider among bats# in Dodongo's Cavern holds", "la #Skulltula entourée de Saigneurs dans la caverne Dodongo# a", /*spanish*/"una #araña rodeada de murciélagos# de la Cueva de los Dodongos otorga"},
  });


  HintText DodongosCavern_MQ_GS_ScrubRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider high on a wall# in Dodongo's Cavern holds", "la #Skulltula haut perchée dans la caverne Dodongo# a", /*spanish*/"una #araña en lo alto de una pared# de la Cueva de los Dodongos otorga"},
  });

  HintText DodongosCavern_MQ_GS_LizalfosRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider on top of a pillar of rock# in Dodongo's Cavern holds", "la #Skulltula sur l'énorme pilier de roc de la caverne Dodongo# a", /*spanish*/"una #araña en lo alto de un pilar# de la Cueva de los Dodongos otorga"},
  });

  HintText DodongosCavern_MQ_GS_LarvaeRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider in a crate# in Dodongo's Cavern holds", "la #Skulltula dans une boîte de la caverne Dodongo# a", /*spanish*/"una #araña bajo una caja# de la Cueva de los Dodongos otorga"},
  });

  HintText DodongosCavern_MQ_GS_BackRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider among graves# in Dodongo's Cavern holds", "la #Skulltula parmi les tombes de la caverne Dodongo# a", /*spanish*/"una #araña entre lápidas# en la Cueva de los Dodongos otorga"},
  });


  HintText JabuJabusBelly_GS_LobbyBasementLower = HintText::Exclude({
                       //obscure text
                       Text{"a #spider resting near a princess# in Jabu Jabu's Belly holds", "la #Skulltula près de la princesse dans le ventre de Jabu-Jabu# a", /*spanish*/"una #araña junto a una princesa# en la Tripa de Jabu Jabu otorga"},
  });

  HintText JabuJabusBelly_GS_LobbyBasementUpper = HintText::Exclude({
                       //obscure text
                       Text{"a #spider resting near a princess# in Jabu Jabu's Belly holds", "la #Skulltula près de la princesse dans le ventre de Jabu-Jabu# a", /*spanish*/"una #araña junto a una princesa# en la Tripa de Jabu Jabu otorga"},
  });

  HintText JabuJabusBelly_GS_NearBoss = HintText::Exclude({
                       //obscure text
                       Text{"#jellyfish surround a spider# holding", "la #Skulltula entourée de méduses dans le ventre de Jabu-Jabu# a", /*spanish*/"una #araña rodeada de medusas# otorga"},
  });

  HintText JabuJabusBelly_GS_WaterSwitchRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider guarded by a school of stingers# in Jabu Jabu's Belly holds", "la #Skulltula protégée par des raies dans le ventre de Jabu-Jabu# a", /*spanish*/"una #araña rodeada por un puñado de stingers# en la Tripa de Jabu Jabu otorga"},
  });


  HintText JabuJabusBelly_MQ_GS_TailPasaranRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider surrounded by electricity# in Jabu Jabu's Belly holds", "la #Skulltula entourée d'électricité dans le ventre de Jabu-Jabu# a", /*spanish*/"una #araña rodeada de electricidad# en la Tripa de Jabu Jabu otorga"},
  });

  HintText JabuJabusBelly_MQ_GS_BoomerangChestRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider guarded by a school of stingers# in Jabu Jabu's Belly holds", "la #Skulltula protégée par des raies dans le ventre de Jabu-Jabu# a", /*spanish*/"una #araña protegida por un puñado de stingers# en la Tripa de Jabu Jabu otorga"},
  });

  HintText JabuJabusBelly_MQ_GS_NearBoss = HintText::Exclude({
                       //obscure text
                       Text{"a #spider in a web within Jabu Jabu's Belly# holds", "la #Skulltula sur une toile dans le ventre de Jabu-Jabu# a", /*spanish*/"una #araña sobre una telaraña# en la Tripa de Jabu Jabu otorga"},
  });


  HintText ForestTemple_GS_RaisedIslandCourtyard = HintText::Exclude({
                       //obscure text
                       Text{"a #spider on a small island# in the Forest Temple holds", "la #Skulltula sur l'îlot du temple de la forêt# a", /*spanish*/"una #araña sobre una pequeña isla# del Templo del Bosque otorga"},
  });

  HintText ForestTemple_GS_FirstRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider high on a wall of vines# in the Forest Temple holds", "la #Skulltula sur un mur de vignes du temple de la forêt# a", /*spanish*/"una #araña en lo alto de una pared de cepas# del Templo del Bosque otorga"},
  });

  HintText ForestTemple_GS_LevelIslandCourtyard = HintText::Exclude({
                       //obscure text
                       Text{"#stone columns# lead to a spider in the Forest Temple hiding", "la #Skulltula haut perchée dans le jardin du temple de la forêt# a", /*spanish*/"unas #columnas del Templo del Bosque# conducen a una araña que otorga"},
  });

  HintText ForestTemple_GS_Lobby = HintText::Exclude({
                       //obscure text
                       Text{"a #spider among ghosts# in the Forest Temple guards", "la #Skulltula dans la grande salle du temple de la forêt# a", /*spanish*/"una #araña rodeada de fantasmas# del Templo del Bosque otorga"},
  });

  HintText ForestTemple_GS_Basement = HintText::Exclude({
                       //obscure text
                       Text{"a #spider within revolving walls# in the Forest Temple holds", "la #Skulltula derrière les murs pivotants du temple de la forêt# a", /*spanish*/"una #araña entre paredes giratorias# del Templo del Bosque otorga"},
  });


  HintText ForestTemple_MQ_GS_FirstHallway = HintText::Exclude({
                       //obscure text
                       Text{"an #ivy-hidden spider# in the Forest Temple hoards", "la #Skulltula près de l'entrée du temple de la forêt# a", /*spanish*/"una #araña escondida entre cepas# del Templo del Bosque otorga"},
  });

  HintText ForestTemple_MQ_GS_BlockPushRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider in a hidden nook# within the Forest Temple holds", "la #Skulltula dans un recoin caché du temple de la forêt# a", /*spanish*/"una #araña en una esquina oculta# del Templo del Bosque otorga"},
  });

  HintText ForestTemple_MQ_GS_RaisedIslandCourtyard = HintText::Exclude({
                       //obscure text
                       Text{"a #spider on an arch# in the Forest Temple holds", "la #Skulltula sur une arche du temple de la forêt# a", /*spanish*/"una #araña sobre un arco# del Templo del Bosque otorga"},
  });

  HintText ForestTemple_MQ_GS_LevelIslandCourtyard = HintText::Exclude({
                       //obscure text
                       Text{"a #spider on a ledge# in the Forest Temple holds", "la #Skulltula dans le jardin du temple de la forêt# a", /*spanish*/"una #araña en un borde# del Templo del Bosque otorga"},
  });

  HintText ForestTemple_MQ_GS_Well = HintText::Exclude({
                       //obscure text
                       Text{"#draining a well# in Forest Temple uncovers a spider with", "la #Skulltula au fond du puits du temple de la forêt# a", /*spanish*/"#vaciar el pozo# del Templo del Bosque desvela una araña que otorga"},
  });


  HintText FireTemple_GS_SongOfTimeRoom = HintText::Exclude({
                       //obscure text
                       Text{"#eight tiles of malice# guard a spider holding", "la #Skulltula protégée par huit tuiles dans le temple du feu# a", /*spanish*/"#ocho baldosas de maldad# custodian una araña que otorga"},
  });

  HintText FireTemple_GS_BossKeyLoop = HintText::Exclude({
                       //obscure text
                       Text{"#five tiles of malice# guard a spider holding", "la #Skulltula protégée par cinq tuiles dans le temple du feu# a", /*spanish*/"#cinco baldosas de maldad# custodian una araña que otorga"},
  });

  HintText FireTemple_GS_BoulderMaze = HintText::Exclude({
                       //obscure text
                       Text{"#explosives in a maze# unveil a spider hiding", "la #Skulltula derrière un mur fragile du temple du feu# a", /*spanish*/"los #explosivos en un laberinto# desvelan una araña que otorga"},
  });

  HintText FireTemple_GS_ScarecrowTop = HintText::Exclude({
                       //obscure text
                       Text{"a #spider-friendly scarecrow# atop a volcano hides", "la #Skulltula repérée par l'épouvantail du volcan# a", /*spanish*/"un #espantapájaros en lo alto de un volcán# custodia una araña que otorga"},
                     },
                       //clear text
                       Text{"a #spider-friendly scarecrow# atop the Fire Temple hides", "la #Skulltula repérée par l'épouvantail du temple du feu# a", /*spanish*/"un #espantapájaros del Templo del Fuego# custodia una araña que otorga"}
  );

  HintText FireTemple_GS_ScarecrowClimb = HintText::Exclude({
                       //obscure text
                       Text{"a #spider-friendly scarecrow# atop a volcano hides", "la #Skulltula repérée par l'épouvantail du volcan# a", /*spanish*/"un #espantapájaros en lo alto de un volcán# custodia una araña que otorga"},
                     },
                       //clear text
                       Text{"a #spider-friendly scarecrow# atop the Fire Temple hides", "la #Skulltula repérée par l'épouvantail du temple du feu# a", /*spanish*/"un #espantapájaros del Templo del Fuego# custodia una araña que otorga"}
  );


  HintText FireTemple_MQ_GS_AboveFireWallMaze = HintText::Exclude({
                       //obscure text
                       Text{"a #spider above a fiery maze# holds", "la #Skulltula au dessus du labyrinthe enflammé du temple du feu# a", /*spanish*/"una #araña sobre un ardiente laberinto# otorga"},
  });

  HintText FireTemple_MQ_GS_FireWallMazeCenter = HintText::Exclude({
                       //obscure text
                       Text{"a #spider within a fiery maze# holds", "la #Skulltula dans le labyrinthe enflammé du temple du feu# a", /*spanish*/"una #araña en el interior de un ardiente laberinto# otorga"},
  });

  HintText FireTemple_MQ_GS_BigLavaRoomOpenDoor = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron trapped near lava# befriended a spider with", "la #Skulltula emprisonnée près du lac de lave du temple du feu# a", /*spanish*/"una #araña amiga de un Goron atrapado junto a la lava# otorga"},
  });

  HintText FireTemple_MQ_GS_FireWallMazeSideRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider beside a fiery maze# holds", "la #Skulltula près du labyrinthe enflammé du temple du feu# a", /*spanish*/"una #araña junto a un ardiente laberinto# otorga"},
  });


  HintText WaterTemple_GS_FallingPlatformRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider over a waterfall# in the Water Temple holds", "la #Skulltula au dessus d'une cascade du temple de l'eau# a", /*spanish*/"una #araña tras una cascada# del Templo del Agua otorga"},
  });

  HintText WaterTemple_GS_CentralPillar = HintText::Exclude({
                       //obscure text
                       Text{"a #spider in the center of the Water Temple# holds", "la #Skulltula au centre du temple de l'eau# a", /*spanish*/"una #araña en el centro del Templo del Agua# otorga"},
  });

  HintText WaterTemple_GS_NearBossKeyChest = HintText::Exclude({
                       //obscure text
                       Text{"a spider protected by #rolling boulders under the lake# hides", "la #Skulltula derrière les rochers roulants sous le lac# a", /*spanish*/"una #araña protegida por rocas rodantes# bajo el lago otorga"},
                     },
                       //clear text
                       Text{"a spider protected by #rolling boulders in the Water Temple# hides", "la #Skulltula derrière les rochers roulants du temple de l'eau# a", /*spanish*/"una #araña protegida por rocas rodantes# del Templo del Agua otorga"}
  );

  HintText WaterTemple_GS_River = HintText::Exclude({
                       //obscure text
                       Text{"a #spider over a river# in the Water Temple holds", "la #Skulltula au dessus de la rivière du temple de l'eau# a", /*spanish*/"una #araña sobre un río# del Templo del Agua otorga"},
  });


  HintText WaterTemple_MQ_GS_BeforeUpperWaterSwitch = HintText::Exclude({
                       //obscure text
                       Text{"#beyond a pit of lizards# is a spider holding", "la #Skulltula près des lézards du temple de l'eau# a", /*spanish*/"#más allá de un pozo de reptiles# una araña otorga"},
  });

  HintText WaterTemple_MQ_GS_LizalfosHallway = HintText::Exclude({
                       //obscure text
                       Text{"#lizards guard a spider# in the Water Temple with", "la #Skulltula dans les couloirs croisés du temple de l'eau# a", /*spanish*/"unos #reptiles custodian una araña# del Templo del Agua que otorga"},
  });

  HintText WaterTemple_MQ_GS_River = HintText::Exclude({
                       //obscure text
                       Text{"a #spider over a river# in the Water Temple holds", "la #Skulltula au dessus de la rivière du temple de l'eau# a", /*spanish*/"una #araña sobre un río# del Templo del Agua otorga"},
  });


  HintText SpiritTemple_GS_HallAfterSunBlockRoom = HintText::Exclude({
                       //obscure text
                       Text{"a spider in the #hall of a knight# guards", "la #Skulltula au dessus d'un escalier du temple de l'esprit# a", /*spanish*/"una #araña en el salón de un guerrero# otorga"},
  });

  HintText SpiritTemple_GS_BoulderRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider behind a temporal stone# in the Spirit Temple yields", "la #Skulltula derrière une pierre temporelle du temple de l'esprit# a", /*spanish*/"una #araña tras un bloque temporal# del Templo del Espíritu otorga"},
  });

  HintText SpiritTemple_GS_Lobby = HintText::Exclude({
                       //obscure text
                       Text{"a #spider beside a statue# holds", "la #Skulltula dans la grande salle du temple de l'esprit# a", /*spanish*/"una #araña junto a una estatua# otorga"},
  });

  HintText SpiritTemple_GS_SunOnFloorRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider at the top of a deep shaft# in the Spirit Temple holds", "la #Skulltula près d'un mur d'escalade du temple de l'esprit# a", /*spanish*/"una #araña en lo alto de un gran hueco# del Templo del Espíritu otorga"},
  });

  HintText SpiritTemple_GS_MetalFence = HintText::Exclude({
                       //obscure text
                       Text{"a child defeats a #spider among bats# in the Spirit Temple to gain", "la #Skulltula sur le grillage du temple de l'esprit# a", /*spanish*/"el joven que derrote la #araña entre murciélagos# hallará"},
  });


  HintText SpiritTemple_MQ_GS_LeeverRoom = HintText::Exclude({
                       //obscure text
                       Text{"#above a pit of sand# in the Spirit Temple hides", "la #Skulltula au dessus du trou sableux du temple de l'esprit# a", /*spanish*/"una #araña sobre un pozo de arena# del Templo del Espíritu otorga"},
  });

  HintText SpiritTemple_MQ_GS_NineThronesRoomWest = HintText::Exclude({
                       //obscure text
                       Text{"a spider in the #hall of a knight# guards", "la #Skulltula dans la salle aux neuf trônes du temple de l'esprit# a", /*spanish*/"una #araña en el salón de un guerrero# otorga"},
  });

  HintText SpiritTemple_MQ_GS_NineThronesRoomNorth = HintText::Exclude({
                       //obscure text
                       Text{"a spider in the #hall of a knight# guards", "la #Skulltula dans la salle aux neuf trônes du temple de l'esprit# a", /*spanish*/"una #araña en el salón de un guerrero# otorga"},
  });

  HintText SpiritTemple_MQ_GS_SunBlockRoom = HintText::Exclude({
                       //obscure text
                       Text{"#upon a web of glass# in the Spirit Temple sits a spider holding", "la #Skulltula sur une paroi de verre du temple de l'esprit# a", /*spanish*/"#sobre una plataforma de cristal# yace una araña que otorga"},
  });


  HintText ShadowTemple_GS_SingleGiantPot = HintText::Exclude({
                       //obscure text
                       Text{"#beyond a burning skull# lies a spider with", "la #Skulltula derrière un crâne enflammé du temple de l'ombre# a", /*spanish*/"#tras una ardiente calavera# yace una araña que otorga"},
  });

  HintText ShadowTemple_GS_FallingSpikesRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider beyond falling spikes# holds", "la #Skulltula au delà de la pluie de clous du temple de l'ombre# a", /*spanish*/"una #araña tras los pinchos del techo# otorga"},
  });

  HintText ShadowTemple_GS_TripleGiantPot = HintText::Exclude({
                       //obscure text
                       Text{"#beyond three burning skulls# lies a spider with", "la #Skulltula derrière trois crânes enflammés du temple de l'ombre# a", /*spanish*/"#tras tres ardientes calaveras# yace una araña que otorga"},
  });

  HintText ShadowTemple_GS_LikeLikeRoom = HintText::Exclude({
                       //obscure text
                       Text{"a spider guarded by #invisible blades# holds", "la #Skulltula protégée par les faucheurs invisibles du temple de l'ombre# a", /*spanish*/"una #araña custodiada por hojas invisibles# otorga"},
  });

  HintText ShadowTemple_GS_NearShip = HintText::Exclude({
                       //obscure text
                       Text{"a spider near a #docked ship# hoards", "la #Skulltula près du traversier du temple de l'ombre# a", /*spanish*/"una #araña cercana a un navío# otorga"},
  });


  HintText ShadowTemple_MQ_GS_FallingSpikesRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider beyond falling spikes# holds", "la #Skulltula au delà de la pluie de clous du temple de l'ombre# a", /*spanish*/"una #araña tras los pinchos del techo# otorga"},
  });

  HintText ShadowTemple_MQ_GS_WindHintRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider amidst roaring winds# in the Shadow Temple holds", "la #Skulltula près des vents du temple de l'ombre# a", /*spanish*/"una #araña entre ventarrones# del Templo de las Sombras otorga"},
  });

  HintText ShadowTemple_MQ_GS_AfterWind = HintText::Exclude({
                       //obscure text
                       Text{"a #spider beneath gruesome debris# in the Shadow Temple hides", "la #Skulltula sous des débris du temple de l'ombre# a", /*spanish*/"una #araña bajo unos horripilantes escombros# del Templo de las Sombras otorga"},
  });

  HintText ShadowTemple_MQ_GS_AfterShip = HintText::Exclude({
                       //obscure text
                       Text{"a #fallen statue# reveals a spider with", "la #Skulltula près de la statue écroulée du temple de l'ombre# a", /*spanish*/"una #estatua caída# revelará una araña que otorgue"},
  });

  HintText ShadowTemple_MQ_GS_NearBoss = HintText::Exclude({
                       //obscure text
                       Text{"a #suspended spider# guards", "la #Skulltula près du repère du temple de l'ombre# a", /*spanish*/"una #araña flotante# otorga"},
  });


  HintText BottomOfTheWell_GS_LikeLikeCage = HintText::Exclude({
                       //obscure text
                       Text{"a #spider locked in a cage# in the well holds", "la #Skulltula dans une cage au fonds du puits# a", /*spanish*/"una #araña enjaulada# del pozo otorga"},
  });

  HintText BottomOfTheWell_GS_EastInnerRoom = HintText::Exclude({
                       //obscure text
                       Text{"an #invisible path in the well# leads to", "la #Skulltula dans le chemin invisible au fonds du puits# a", /*spanish*/"un #camino invisible del pozo# conduce a una araña que otorga"},
  });

  HintText BottomOfTheWell_GS_WestInnerRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider locked in a crypt# within the well guards", "la #Skulltula embarrée dans la crypte au fonds du puits# a", /*spanish*/"una #araña encerrada en una cripta# del pozo otorga"},
  });


  HintText BottomOfTheWell_MQ_GS_Basement = HintText::Exclude({
                       //obscure text
                       Text{"a #gauntlet of invisible spiders# protects", "la #Skulltula protégée par les araignées invisibles au fonds du puits# a", /*spanish*/"un #puñado de arañas invisibles# custodian una que otorga"},
  });

  HintText BottomOfTheWell_MQ_GS_CoffinRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider crawling near the dead# in the well holds", "la #Skulltula près des cercueils au fonds du puits# a", /*spanish*/"una #araña bajo los muertos# del pozo otorga"},
  });

  HintText BottomOfTheWell_MQ_GS_WestInnerRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider locked in a crypt# within the well guards", "la #Skulltula embarrée dans la crypte au fonds du puits# a", /*spanish*/"una #araña encerrada en una cripta# del pozo otorga"},
  });


  HintText IceCavern_GS_PushBlockRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider above icy pits# holds", "la #Skulltula au dessus d'un goufre glacial# a", /*spanish*/"una #araña sobre gélidos vacíos# otorga"},
  });

  HintText IceCavern_GS_SpinningScytheRoom = HintText::Exclude({
                       //obscure text
                       Text{"#spinning ice# guards a spider holding", "la #Skulltula près de deux lames de glace# a", /*spanish*/"unos #témpanos giratorios# custodian una araña que otorga"},
  });

  HintText IceCavern_GS_HeartPieceRoom = HintText::Exclude({
                       //obscure text
                       Text{"a #spider behind a wall of ice# hides", "la #Skulltula derrière un mur de glace# a", /*spanish*/"una #araña tras una gélida pared# otorga"},
  });


  HintText IceCavern_MQ_GS_Scarecrow = HintText::Exclude({
                       //obscure text
                       Text{"a #spider above icy pits# holds", "la #Skulltula au dessus d'un goufre glacial# a", /*spanish*/"una #araña sobre gélidos vacíos# otorga"},
  });

  HintText IceCavern_MQ_GS_IceBlock = HintText::Exclude({
                       //obscure text
                       Text{"a #web of ice# surrounds a spider with", "la #Skulltula protégée d'une toile glacée# a", /*spanish*/"una #gélida telaraña# rodea a una que otorga"},
  });

  HintText IceCavern_MQ_GS_RedIce = HintText::Exclude({
                       //obscure text
                       Text{"a #spider in fiery ice# hoards", "la #Skulltula figée dans la glace rouge# a", /*spanish*/"una #araña de un ardiente hielo# otorga"},
  });


  HintText HF_GS_NearKakGrotto = HintText::Exclude({
                       //obscure text
                       Text{"a #spider-guarded spider in a hole# hoards", "la #Skulltula dans un trou d'arachnides# a", /*spanish*/"una #araña custodiada por otra# de un hoyo otorga"},
  });


  HintText LLR_GS_BackWall = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider in a ranch# holding", "la #Skulltula sur la façade de la ferme# a", /*spanish*/"la noche revela una #araña del rancho# que otorga"},
  });

  HintText LLR_GS_RainShed = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider in a ranch# holding", "la #Skulltula sur le mur de l'enclos# a", /*spanish*/"la noche revela una #araña del rancho# que otorga"},
  });

  HintText LLR_GS_HouseWindow = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider in a ranch# holding", "la #Skulltula sur la maison de ferme# a", /*spanish*/"la noche revela una #araña del rancho# que otorga"},
  });

  HintText LLR_GS_Tree = HintText::Exclude({
                       //obscure text
                       Text{"a spider hiding in a #ranch tree# holds", "la #Skulltula dans l'arbre de la ferme# a", /*spanish*/"una araña escondida en el #árbol de un rancho# otorga"},
  });


  HintText KF_GS_BeanPatch = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried in a forest# holds", "la #Skulltula enterrée dans la forêt# a", /*spanish*/"una #araña enterrada en un bosque# otorga"},
  });

  HintText KF_GS_KnowItAllHouse = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a forest# holding", "la #Skulltula derrière une cabane de la forêt# a", /*spanish*/"la noche revela en el pasado una #araña del bosque# que otorga"},
  });

  HintText KF_GS_HouseOfTwins = HintText::Exclude({
                       //obscure text
                       Text{"night in the future reveals a #spider in a forest# holding", "la #Skulltula sur une cabane de la forêt# a", /*spanish*/"la noche revela en el futuro una #araña del rancho# que otorga"},
  });


  HintText LW_GS_BeanPatchNearBridge = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried deep in a forest maze# holds", "la #Skulltula enterrée dans les bois# a", /*spanish*/"una #araña enterrada en un laberinto forestal# otorga"},
  });

  HintText LW_GS_BeanPatchNearTheater = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried deep in a forest maze# holds", "la #Skulltula enterrée dans les bois# a", /*spanish*/"una #araña enterrada en un laberinto forestal# otorga"},
  });

  HintText LW_GS_AboveTheater = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider deep in a forest maze# holding", "la #Skulltula haut perchée dans les bois# a", /*spanish*/"la noche revela una #araña del laberinto forestal# que otorga"},
  });

  HintText SFM_GS = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider in a forest meadow# holding", "la #Skulltula dans le sanctuaire des bois# a", /*spanish*/"la noche revela una #araña de la pradera del bosque# que otorga"},
  });


  HintText OGC_GS = HintText::Exclude({
                       //obscure text
                       Text{"a #spider outside a tyrant's tower# holds", "la #Skulltula parmi les ruines du château# a", /*spanish*/"una #araña a las afueras de la torre de un tirano# otorga"},
  });

  HintText HC_GS_Tree = HintText::Exclude({
                       //obscure text
                       Text{"a spider hiding in a #tree outside of a castle# holds", "la #Skulltula dans l'arbre près du château# a", /*spanish*/"una araña escondida en el #árbol de las afueras de un castillo# otorga"},
  });

  HintText MK_GS_GuardHouse = HintText::Exclude({
                       //obscure text
                       Text{"a #spider in a guarded crate# holds", "la #Skulltula dans une boîte en ville# a", /*spanish*/"una #araña bajo una custodiada caja# otorga"},
  });


  HintText DMC_GS_BeanPatch = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried in a volcano# holds", "la #Skulltula enterrée dans un volcan# a", /*spanish*/"una #araña enterrada en un volcán# otorga"},
  });


  HintText DMT_GS_BeanPatch = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried outside a cavern# holds", "la #Skulltula enterrée près d'une caverne# a", /*spanish*/"una #araña enterrada a la entrada de una cueva# otorga"},
  });

  HintText DMT_GS_NearKak = HintText::Exclude({
                       //obscure text
                       Text{"a #spider hidden in a mountain nook# holds", "la #Skulltula cachée dans le flanc d'une montagne# a", /*spanish*/"una #araña oculta en el rincón de la montaña# otorga"},
  });

  HintText DMT_GS_AboveDodongosCavern = HintText::Exclude({
                       //obscure text
                       Text{"the hammer reveals a #spider on a mountain# holding", "la #Skulltula derrière un rocher massif près d'une caverne# a", /*spanish*/"el martillo revela #una araña de la montaña# que otorga"},
  });

  HintText DMT_GS_FallingRocksPath = HintText::Exclude({
                       //obscure text
                       Text{"the hammer reveals a #spider on a mountain# holding", "la #Skulltula derrière un rocher massif près du sommet d'un volcan# a", /*spanish*/"el martillo revela #una araña de la montaña# que otorga"},
  });


  HintText GC_GS_CenterPlatform = HintText::Exclude({
                       //obscure text
                       Text{"a #suspended spider# in Goron City holds", "la #Skulltula perchée dans le village Goron# a", /*spanish*/"una #araña suspendida# en la Ciudad Goron otorga"},
  });

  HintText GC_GS_BoulderMaze = HintText::Exclude({
                       //obscure text
                       Text{"a spider in a #Goron City crate# holds", "la #Skulltula dans une boîte du village Goron# a", /*spanish*/"una #araña bajo una caja# de la Ciudad Goron otorga"},
  });


  HintText Kak_GS_HouseUnderConstruction = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a town# holding", "la #Skulltula dans le chantier de construction# a", /*spanish*/"la noche del pasado revela una #araña del pueblo# que otorga"},
  });

  HintText Kak_GS_SkulltulaHouse = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a town# holding", "la #Skulltula sur une maison maudite# a", /*spanish*/"la noche del pasado revela una #araña del pueblo# que otorga"},
  });

  HintText Kak_GS_GuardsHouse = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a town# holding", "la #Skulltula sur une maison de village# a", /*spanish*/"la noche del pasado revela una #araña del pueblo# que otorga"},
  });

  HintText Kak_GS_Tree = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a town# holding", "la #Skulltula dans un arbre de village# a", /*spanish*/"la noche del pasado revela una #araña del pueblo# que otorga"},
  });

  HintText Kak_GS_Watchtower = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a town# holding", "la #Skulltula sur une échelle dans un village# a", /*spanish*/"la noche del pasado revela una #araña del pueblo# que otorga"},
  });

  HintText Kak_GS_AboveImpasHouse = HintText::Exclude({
                       //obscure text
                       Text{"night in the future reveals a #spider in a town# holding", "la #Skulltula au dessus d'une grande maison# a", /*spanish*/"la noche del futuro revela una #araña del pueblo# que otorga"},
  });


  HintText GY_GS_Wall = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider in a graveyard# holding", "la #Skulltula sur une façade du cimetière# a", /*spanish*/"la noche revela una #araña del cementerio# que otorga"},
  });

  HintText GY_GS_BeanPatch = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried in a graveyard# holds", "la #Skulltula enterrée dans le cimetière# a", /*spanish*/"una #araña enterrada en el cementerio# otorga"},
  });


  HintText ZR_GS_Ladder = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a river# holding", "la #Skulltula sur une échelle près d'une cascade# a", /*spanish*/"la noche del pasado revela una #araña del río# que otorga"},
  });

  HintText ZR_GS_Tree = HintText::Exclude({
                       //obscure text
                       Text{"a spider hiding in a #tree by a river# holds", "la #Skulltula dans un arbre près du fleuve# a", /*spanish*/"una araña escondida en el #árbol de un río# otorga"},
  });

  HintText ZR_GS_AboveBridge = HintText::Exclude({
                       //obscure text
                       Text{"night in the future reveals a #spider in a river# holding", "la #Skulltula sur une façade près d'une cascade# a", /*spanish*/"la noche del futuro revela una #araña del río# que otorga"},
  });

  HintText ZR_GS_NearRaisedGrottos = HintText::Exclude({
                       //obscure text
                       Text{"night in the future reveals a #spider in a river# holding", "la #Skulltula sur une façade près d'une grotte du fleuve# a", /*spanish*/"la noche del futuro revela una #araña del río# que otorga"},
  });


  HintText ZD_GS_FrozenWaterfall = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider by a frozen waterfall# holding", "la #Skulltula près d'une cascade gelée# a", /*spanish*/"la noche revela una #araña junto a una congelada cascada# que otorga"},
  });

  HintText ZF_GS_AboveTheLog = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider near a deity# holding", "la #Skulltula près du gardien aquatique# a", /*spanish*/"la noche revela una #araña junto a cierta deidad# que otorga"},
  });

  HintText ZF_GS_Tree = HintText::Exclude({
                       //obscure text
                       Text{"a spider hiding in a #tree near a deity# holds", "la #Skulltula dans un arbre dans un réservoir# a", /*spanish*/"una araña escondida en el #árbol junto a cierta deidad# otorga"},
  });


  HintText LH_GS_BeanPatch = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried by a lake# holds", "la #Skulltula enterrée près d'un lac# a", /*spanish*/"una #araña enterrada junto a un lago# otorga"},
  });

  HintText LH_GS_SmallIsland = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider by a lake# holding", "la #Skulltula sur un îlot du lac# a", /*spanish*/"la noche revela una #araña junto a un lago# que otorga"},
  });

  HintText LH_GS_LabWall = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider by a lake# holding", "la #Skulltula sur le mur d'un centre de recherche# a", /*spanish*/"la noche revela una #araña junto a un lago# que otorga"},
  });

  HintText LH_GS_LabCrate = HintText::Exclude({
                       //obscure text
                       Text{"a spider deed underwater in a #lab crate# holds", "la #Skulltula dans une boîte au fond d'une cuve d'eau# a", /*spanish*/"una #araña bajo la sumergida caja de un laboratorio# otorga"},
  });

  HintText LH_GS_Tree = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider by a lake high in a tree# holding", "la #Skulltula dans un grand arbre du lac# a", /*spanish*/"la noche revela #una araña del lago sobre un árbol# que otorga"},
  });


  HintText GV_GS_BeanPatch = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried in a valley# holds", "la #Skulltula enterré dans une vallée# a", /*spanish*/"una #araña enterrada en un valle# otorga"},
  });

  HintText GV_GS_SmallBridge = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a valley# holding", "la #Skulltula au dessus d'une petite cascade# a", /*spanish*/"la noche del pasado revela una #araña del valle# que otorga"},
  });

  HintText GV_GS_Pillar = HintText::Exclude({
                       //obscure text
                       Text{"night in the future reveals a #spider in a valley# holding", "la #Skulltula sur une arche de pierre dans une vallée# a", /*spanish*/"la noche del futuro revela una #araña del valle# que otorga"},
  });

  HintText GV_GS_BehindTent = HintText::Exclude({
                       //obscure text
                       Text{"night in the future reveals a #spider in a valley# holding", "la #Skulltula derrière une tente# a", /*spanish*/"la noche del futuro revela una #araña del valle# que otorga"},
  });


  HintText GF_GS_ArcheryRange = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider in a fortress# holding", "la #Skulltula sur une cible de tir# a", /*spanish*/"la noche revela una #araña de una fortaleza# que otorga"},
  });

  HintText GF_GS_TopFloor = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider in a fortress# holding", "la #Skulltula au sommet d'une forteresse# a", /*spanish*/"la noche revela una #araña de una fortaleza# que otorga"},
  });


  HintText Colossus_GS_BeanPatch = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried in the desert# holds", "la #Skulltula enterrée au pied du colosse# a", /*spanish*/"una #enterrada en el desierto# otorga"},
  });

  HintText Colossus_GS_Hill = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider deep in the desert# holding", "la #Skulltula sur une colline dans le désert# a", /*spanish*/"la noche revela una #araña en las profundidades del desierto# que otorga"},
  });

  HintText Colossus_GS_Tree = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider deep in the desert# holding", "la #Skulltula dans un arbre du désert# a", /*spanish*/"la noche revela una #araña en las profundidades del desierto# que otorga"},
  });


  HintText KF_ShopItem1 = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", "la #boutique Kokiri# vend", /*spanish*/"un #joven dependiente# vende"},
  });

  HintText KF_ShopItem2 = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", "la #boutique Kokiri# vend", /*spanish*/"un #joven dependiente# vende"},
  });

  HintText KF_ShopItem3 = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", "la #boutique Kokiri# vend", /*spanish*/"un #joven dependiente# vende"},
  });

  HintText KF_ShopItem4 = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", "la #boutique Kokiri# vend", /*spanish*/"un #joven dependiente# vende"},
  });

  HintText KF_ShopItem5 = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", "la #boutique Kokiri# vend", /*spanish*/"un #joven dependiente# vende"},
  });

  HintText KF_ShopItem6 = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", "la #boutique Kokiri# vend", /*spanish*/"un #joven dependiente# vende"},
  });

  HintText KF_ShopItem7 = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", "la #boutique Kokiri# vend", /*spanish*/"un #joven dependiente# vende"},
  });

  HintText KF_ShopItem8 = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", "la #boutique Kokiri# vend", /*spanish*/"un #joven dependiente# vende"},
  });


  HintText Kak_PotionShopItem1 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", "le #apothicaire# vend", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", "le #apothicaire de Kakariko# vend", /*spanish*/"la #tienda de pociones de Kakariko# ofrece"}
  );

  HintText Kak_PotionShopItem2 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", "le #apothicaire# vend", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", "le #apothicaire de Kakariko# vend", /*spanish*/"la #tienda de pociones de Kakariko# ofrece"}
  );

  HintText Kak_PotionShopItem3 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", "le #apothicaire# vend", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", "le #apothicaire de Kakariko# vend", /*spanish*/"la #tienda de pociones de Kakariko# ofrece"}
  );

  HintText Kak_PotionShopItem4 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", "le #apothicaire# vend", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", "le #apothicaire de Kakariko# vend", /*spanish*/"la #tienda de pociones de Kakariko# ofrece"}
  );

  HintText Kak_PotionShopItem5 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", "le #apothicaire# vend", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", "le #apothicaire de Kakariko# vend", /*spanish*/"la #tienda de pociones de Kakariko# ofrece"}
  );

  HintText Kak_PotionShopItem6 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", "le #apothicaire# vend", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", "le #apothicaire de Kakariko# vend", /*spanish*/"la #tienda de pociones de Kakariko# ofrece"}
  );

  HintText Kak_PotionShopItem7 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", "le #apothicaire# vend", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", "le #apothicaire de Kakariko# vend", /*spanish*/"la #tienda de pociones de Kakariko# ofrece"}
  );

  HintText Kak_PotionShopItem8 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", "le #apothicaire# vend", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", "le #apothicaire de Kakariko# vend", /*spanish*/"la #tienda de pociones de Kakariko# ofrece"}
  );


  HintText MK_BombchuShopItem1 = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", "le #marchand de missiles# vend", /*spanish*/"un #mercader de bombchus# vende"},
  });

  HintText MK_BombchuShopItem2 = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", "le #marchand de missiles# vend", /*spanish*/"un #mercader de bombchus# vende"},
  });

  HintText MK_BombchuShopItem3 = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", "le #marchand de missiles# vend", /*spanish*/"un #mercader de bombchus# vende"},
  });

  HintText MK_BombchuShopItem4 = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", "le #marchand de missiles# vend", /*spanish*/"un #mercader de bombchus# vende"},
  });

  HintText MK_BombchuShopItem5 = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", "le #marchand de missiles# vend", /*spanish*/"un #mercader de bombchus# vende"},
  });

  HintText MK_BombchuShopItem6 = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", "le #marchand de missiles# vend", /*spanish*/"un #mercader de bombchus# vende"},
  });

  HintText MK_BombchuShopItem7 = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", "le #marchand de missiles# vend", /*spanish*/"un #mercader de bombchus# vende"},
  });

  HintText MK_BombchuShopItem8 = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", "le #marchand de missiles# vend", /*spanish*/"un #mercader de bombchus# vende"},
  });


  HintText MK_PotionShopItem1 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", "le #apothicaire# vend", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", "le #apothicaire dans la place du marché# vend", /*spanish*/"la #tienda de pociones del mercado# ofrece"}
  );

  HintText MK_PotionShopItem2 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", "le #apothicaire# vend", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", "le #apothicaire dans la place du marché# vend", /*spanish*/"la #tienda de pociones del mercado# ofrece"}
  );

  HintText MK_PotionShopItem3 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", "le #apothicaire# vend", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", "le #apothicaire dans la place du marché# vend", /*spanish*/"la #tienda de pociones del mercado# ofrece"}
  );

  HintText MK_PotionShopItem4 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", "le #apothicaire# vend", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", "le #apothicaire dans la place du marché# vend", /*spanish*/"la #tienda de pociones del mercado# ofrece"}
  );

  HintText MK_PotionShopItem5 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", "le #apothicaire# vend", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", "le #apothicaire dans la place du marché# vend", /*spanish*/"la #tienda de pociones del mercado# ofrece"}
  );

  HintText MK_PotionShopItem6 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", "le #apothicaire# vend", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", "le #apothicaire dans la place du marché# vend", /*spanish*/"la #tienda de pociones del mercado# ofrece"}
  );

  HintText MK_PotionShopItem7 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", "le #apothicaire# vend", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", "le #apothicaire dans la place du marché# vend", /*spanish*/"la #tienda de pociones del mercado# ofrece"}
  );

  HintText MK_PotionShopItem8 = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", "le #apothicaire# vend", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", "le #apothicaire dans la place du marché# vend", /*spanish*/"la #tienda de pociones del mercado# ofrece"}
  );


  HintText MK_BazaarItem1 = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", "le #bazar de la place du marché# vend", /*spanish*/"el #bazar del mercado# ofrece"},
  });

  HintText MK_BazaarItem2 = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", "le #bazar de la place du marché# vend", /*spanish*/"el #bazar del mercado# ofrece"},
  });

  HintText MK_BazaarItem3 = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", "le #bazar de la place du marché# vend", /*spanish*/"el #bazar del mercado# ofrece"},
  });

  HintText MK_BazaarItem4 = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", "le #bazar de la place du marché# vend", /*spanish*/"el #bazar del mercado# ofrece"},
  });

  HintText MK_BazaarItem5 = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", "le #bazar de la place du marché# vend", /*spanish*/"el #bazar del mercado# ofrece"},
  });

  HintText MK_BazaarItem6 = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", "le #bazar de la place du marché# vend", /*spanish*/"el #bazar del mercado# ofrece"},
  });

  HintText MK_BazaarItem7 = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", "le #bazar de la place du marché# vend", /*spanish*/"el #bazar del mercado# ofrece"},
  });

  HintText MK_BazaarItem8 = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", "le #bazar de la place du marché# vend", /*spanish*/"el #bazar del mercado# ofrece"},
  });


  HintText Kak_BazaarItem1 = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", "le #bazar de Kakariko# vend", /*spanish*/"el #bazar de Kakariko# ofrece"},
  });

  HintText Kak_BazaarItem2 = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", "le #bazar de Kakariko# vend", /*spanish*/"el #bazar de Kakariko# ofrece"},
  });

  HintText Kak_BazaarItem3 = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", "le #bazar de Kakariko# vend", /*spanish*/"el #bazar de Kakariko# ofrece"},
  });

  HintText Kak_BazaarItem4 = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", "le #bazar de Kakariko# vend", /*spanish*/"el #bazar de Kakariko# ofrece"},
  });

  HintText Kak_BazaarItem5 = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", "le #bazar de Kakariko# vend", /*spanish*/"el #bazar de Kakariko# ofrece"},
  });

  HintText Kak_BazaarItem6 = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", "le #bazar de Kakariko# vend", /*spanish*/"el #bazar de Kakariko# ofrece"},
  });

  HintText Kak_BazaarItem7 = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", "le #bazar de Kakariko# vend", /*spanish*/"el #bazar de Kakariko# ofrece"},
  });

  HintText Kak_BazaarItem8 = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", "le #bazar de Kakariko# vend", /*spanish*/"el #bazar de Kakariko# ofrece"},
  });


  HintText ZD_ShopItem1 = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", "la #boutique Zora# vend", /*spanish*/"el #dependiente zora# vende"},
  });

  HintText ZD_ShopItem2 = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", "la #boutique Zora# vend", /*spanish*/"el #dependiente zora# vende"},
  });

  HintText ZD_ShopItem3 = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", "la #boutique Zora# vend", /*spanish*/"el #dependiente zora# vende"},
  });

  HintText ZD_ShopItem4 = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", "la #boutique Zora# vend", /*spanish*/"el #dependiente zora# vende"},
  });

  HintText ZD_ShopItem5 = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", "la #boutique Zora# vend", /*spanish*/"el #dependiente zora# vende"},
  });

  HintText ZD_ShopItem6 = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", "la #boutique Zora# vend", /*spanish*/"el #dependiente zora# vende"},
  });

  HintText ZD_ShopItem7 = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", "la #boutique Zora# vend", /*spanish*/"el #dependiente zora# vende"},
  });

  HintText ZD_ShopItem8 = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", "la #boutique Zora# vend", /*spanish*/"el #dependiente zora# vende"},
  });


  HintText GC_ShopItem1 = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", "la #boutique Goron# vend", /*spanish*/"el #dependiente goron# vende"},
  });

  HintText GC_ShopItem2 = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", "la #boutique Goron# vend", /*spanish*/"el #dependiente goron# vende"},
  });

  HintText GC_ShopItem3 = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", "la #boutique Goron# vend", /*spanish*/"el #dependiente goron# vende"},
  });

  HintText GC_ShopItem4 = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", "la #boutique Goron# vend", /*spanish*/"el #dependiente goron# vende"},
  });

  HintText GC_ShopItem5 = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", "la #boutique Goron# vend", /*spanish*/"el #dependiente goron# vende"},
  });

  HintText GC_ShopItem6 = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", "la #boutique Goron# vend", /*spanish*/"el #dependiente goron# vende"},
  });

  HintText GC_ShopItem7 = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", "la #boutique Goron# vend", /*spanish*/"el #dependiente goron# vende"},
  });

  HintText GC_ShopItem8 = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", "la #boutique Goron# vend", /*spanish*/"el #dependiente goron# vende"},
  });


  HintText DekuTree_MQ_DekuScrub = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub in the Deku Tree# sells", "la #peste Mojo dans l'arbre Mojo# vend", /*spanish*/"un #deku del Árbol Deku# vende"},
  });


  HintText HF_DekuScrubGrotto = HintText::Exclude({
                       //obscure text
                       Text{"a lonely #scrub in a hole# sells", "la #peste Mojo dans une grotte de la plaine# vend", /*spanish*/"un #singular deku bajo un hoyo# vende"},
  });

  HintText LLR_DekuScrubGrottoLeft = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", "le #trio de peste Mojo à la ferme# vend", /*spanish*/"un #trío de dekus# vende"},
  });

  HintText LLR_DekuScrubGrottoRight = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", "le #trio de peste Mojo à la ferme# vend", /*spanish*/"un #trío de dekus# vende"},
  });

  HintText LLR_DekuScrubGrottoCenter = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", "le #trio de peste Mojo à la ferme# vend", /*spanish*/"un #trío de dekus# vende"},
  });


  HintText LW_DekuScrubNearDekuTheaterRight = HintText::Exclude({
                       //obscure text
                       Text{"a pair of #scrubs in the woods# sells", "le #duo de peste Mojo près du théâtre# vend", /*spanish*/"un par de #dekus del bosque# vende"},
  });

  HintText LW_DekuScrubNearDekuTheaterLeft = HintText::Exclude({
                       //obscure text
                       Text{"a pair of #scrubs in the woods# sells", "le #duo de peste Mojo près du théâtre# vend", /*spanish*/"un par de #dekus del bosque# vende"},
  });

  HintText LW_DekuScrubNearBridge = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub by a bridge# sells", "la #peste Mojo près du pont dans les bois# vend", /*spanish*/"un #deku bajo un puente# vende"},
  });

  HintText LW_DekuScrubGrottoRear = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", "le #duo de peste Mojo dans les sous-bois# vend", /*spanish*/"un #par de dekus subterráneos# vende"},
  });

  HintText LW_DekuScrubGrottoFront = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", "le #duo de peste Mojo dans les sous-bois# vend", /*spanish*/"un #par de dekus subterráneos# vende"},
  });


  HintText SFM_DekuScrubGrottoRear = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", "le #duo de peste Mojo au coeur du sanctuaire sylvestre# vend", /*spanish*/"un #par de dekus subterráneos# vende"},
  });

  HintText SFM_DekuScrubGrottoFront = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", "le #duo de peste Mojo au coeur du sanctuaire sylvestre# vend", /*spanish*/"un #par de dekus subterráneos# vende"},
  });


  HintText GC_DekuScrubGrottoLeft = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", "le #trio de peste Mojo dans le village Goron# vend", /*spanish*/"un #trío de dekus# vende"},
  });

  HintText GC_DekuScrubGrottoRight = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", "le #trio de peste Mojo dans le village Goron# vend", /*spanish*/"un #trío de dekus# vende"},
  });

  HintText GC_DekuScrubGrottoCenter = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", "le #trio de peste Mojo dans le village Goron# vend", /*spanish*/"un #trío de dekus# vende"},
  });


  HintText DodongosCavern_DekuScrubNearBombBagLeft = HintText::Exclude({
                       //obscure text
                       Text{"a pair of #scrubs in Dodongo's Cavern# sells", "le #duo de peste Mojo dans la caverne Dodongo# vend", /*spanish*/"un #par de dekus en la Cueva de los Dodongos# vende"},
  });

  HintText DodongosCavern_DekuScrubSideRoomNearDodongos = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub guarded by Lizalfos# sells", "la #peste Mojo au coeur de la caverne Dodongo# vend", /*spanish*/"un #deku custodiado por Lizalfos# vende"},
  });

  HintText DodongosCavern_DekuScrubNearBombBagRight = HintText::Exclude({
                       //obscure text
                       Text{"a pair of #scrubs in Dodongo's Cavern# sells", "le #duo de peste Mojo dans la caverne Dodongo# vend", /*spanish*/"un #par de dekus en la Cueva de los Dodongos# vende"},
  });

  HintText DodongosCavern_DekuScrubLobby = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub in Dodongo's Cavern# sells", "la #peste Mojo dans l'entrée de la caverne Dodongo# vend", /*spanish*/"un #deku en la Cueva de los Dodongos# vende"},
  });


  HintText DodongosCavern_MQ_DekuScrubLobbyRear = HintText::Exclude({
                       //obscure text
                       Text{"a pair of #scrubs in Dodongo's Cavern# sells", "le #duo de peste Mojo dans l'entrée de la caverne Dodongo# vend", /*spanish*/"un #par de dekus en la Cueva de los Dodongos# vende"},
  });

  HintText DodongosCavern_MQ_DekuScrubLobbyFront = HintText::Exclude({
                       //obscure text
                       Text{"a pair of #scrubs in Dodongo's Cavern# sells", "le #duo de peste Mojo dans l'entrée de la caverne Dodongo# vend", /*spanish*/"un #par de dekus en la Cueva de los Dodongos# vende"},
  });

  HintText DodongosCavern_MQ_DekuScrubStaircase = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub in Dodongo's Cavern# sells", "la #peste Mojo au sommet des escaliers dans la caverne Dodongo# vend", /*spanish*/"un #deku en la Cueva de los Dodongos# vende"},
  });

  HintText DodongosCavern_MQ_DekuScrubSideRoomNearLowerLizalfos = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub guarded by Lizalfos# sells", "la #peste Mojo au coeur de la caverne Dodongo# vend", /*spanish*/"un #deku custodiado por Lizalfos# vende"},
  });


  HintText DMC_DekuScrubGrottoLeft = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", "le #trio de peste Mojo dans le volcan# vend", /*spanish*/"un #trío de dekus# vende"},
  });

  HintText DMC_DekuScrubGrottoRight = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", "le #trio de peste Mojo dans le volcan# vend", /*spanish*/"un #trío de dekus# vende"},
  });

  HintText DMC_DekuScrubGrottoCenter = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", "le #trio de peste Mojo dans le volcan# vend", /*spanish*/"un #trío de dekus# vende"},
  });


  HintText ZR_DekuScrubGrottoRear = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", "le #duo de peste Mojo près du fleuve# vend", /*spanish*/"un #par de dekus subterráneos# vende"},
  });

  HintText ZR_DekuScrubGrottoFront = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", "le #duo de peste Mojo près du fleuve# vend", /*spanish*/"un #par de dekus subterráneos# vende"},
  });


  HintText JabuJabusBelly_DekuScrub = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub in a deity# sells", "la #peste Mojo dans le ventre du gardien# vend", /*spanish*/"un #deku dentro de cierta deidad# vende"},
  });


  HintText LH_DekuScrubGrottoLeft = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", "le #trio de peste Mojo près du lac# vend", /*spanish*/"un #trío de dekus# vende"},
  });

  HintText LH_DekuScrubGrottoRight = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", "le #trio de peste Mojo près du lac# vend", /*spanish*/"un #trío de dekus# vende"},
  });

  HintText LH_DekuScrubGrottoCenter = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", "le #trio de peste Mojo près du lac# vend", /*spanish*/"un #trío de dekus# vende"},
  });


  HintText GV_DekuScrubGrottoRear = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", "le #duo de peste Mojo près de la vallée# vend", /*spanish*/"un #par de dekus subterráneos# vende"},
  });

  HintText GV_DekuScrubGrottoFront = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", "le #duo de peste Mojo près de la vallée# vend", /*spanish*/"un #par de dekus subterráneos# vende"},
  });


  HintText Colossus_DekuScrubGrottoFront = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", "le #duo de peste Mojo dans le désert# vend", /*spanish*/"un #par de dekus subterráneos# vende"},
  });

  HintText Colossus_DekuScrubGrottoRear = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", "le #duo de peste Mojo dans le désert# vend", /*spanish*/"un #par de dekus subterráneos# vende"},
  });


  HintText GanonsCastle_DekuScrubCenterLeft = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", "les #pestes Mojo dans le château de Ganon# vendent", /*spanish*/"los #dekus del Castillo de Ganondorf# venden"},
  });

  HintText GanonsCastle_DekuScrubCenterRight = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", "les #pestes Mojo dans le château de Ganon# vendent", /*spanish*/"los #dekus del Castillo de Ganondorf# venden"},
  });

  HintText GanonsCastle_DekuScrubRight = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", "les #pestes Mojo dans le château de Ganon# vendent", /*spanish*/"los #dekus del Castillo de Ganondorf# venden"},
  });

  HintText GanonsCastle_DekuScrubLeft = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", "les #pestes Mojo dans le château de Ganon# vendent", /*spanish*/"los #dekus del Castillo de Ganondorf# venden"},
  });


  HintText GanonsCastle_MQ_DekuScrubRight = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", "les #pestes Mojo dans le château de Ganon# vendent", /*spanish*/"los #dekus del Castillo de Ganondorf# venden"},
  });

  HintText GanonsCastle_MQ_DekuScrubCenterLeft = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", "les #pestes Mojo dans le château de Ganon# vendent", /*spanish*/"los #dekus del Castillo de Ganondorf# venden"},
  });

  HintText GanonsCastle_MQ_DekuScrubCenter = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", "les #pestes Mojo dans le château de Ganon# vendent", /*spanish*/"los #dekus del Castillo de Ganondorf# venden"},
  });

  HintText GanonsCastle_MQ_DekuScrubCenterRight = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", "les #pestes Mojo dans le château de Ganon# vendent", /*spanish*/"los #dekus del Castillo de Ganondorf# venden"},
  });

  HintText GanonsCastle_MQ_DekuScrubLeft = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", "les #pestes Mojo dans le château de Ganon# vendent", /*spanish*/"los #dekus del Castillo de Ganondorf# venden"},
  });


  HintText LLR_StablesLeftCow = HintText::Exclude({
                       //obscure text
                       Text{"a #cow in a stable# gifts", "la #vache dans l'étable# donne", /*spanish*/"una #vaca del establo# brinda"},
  });

  HintText LLR_StablesRightCow = HintText::Exclude({
                       //obscure text
                       Text{"a #cow in a stable# gifts", "la #vache dans l'étable# donne", /*spanish*/"una #vaca del establo# brinda"},
  });

  HintText LLR_TowerRightCow = HintText::Exclude({
                       //obscure text
                       Text{"a #cow in a ranch silo# gifts", "la #vache dans le silo de la ferme# donne", /*spanish*/"una #vaca del granero# brinda"},
  });

  HintText LLR_TowerLeftCow = HintText::Exclude({
                       //obscure text
                       Text{"a #cow in a ranch silo# gifts", "la #vache dans le silo de la ferme# donne", /*spanish*/"una #vaca del granero# brinda"},
  });

  HintText Kak_ImpasHouseCow = HintText::Exclude({
                       //obscure text
                       Text{"a #cow imprisoned in a house# protects", "la #vache en cage# donne", /*spanish*/"una #vaca enjaulada de una casa# brinda"},
  });

  HintText DMT_CowGrottoCow = HintText::Exclude({
                       //obscure text
                       Text{"a #cow in a luxurious hole# offers", "la #vache dans une grotte luxueuse# donne", /*spanish*/"una #vaca de un lujoso hoyo# brinda"},
  });

  /*--------------------------
  |    ENTRANCE HINT TEXT    |
  ---------------------------*/

  HintText DesertColossus_To_ColossusGrotto = HintText::Entrance({
                     //obscure text
                     Text{"lifting a #rock in the desert# reveals", "soulever une #roche dans le désert# révèle", /*spanish*/"levantar una #roca del desierto# revela"},
  });

  HintText GVGrottoLedge_To_GVOctorokGrotto = HintText::Entrance({
                     //obscure text
                     Text{"a rock on #a ledge in the valley# hides", "soulever une #roche dans la vallée# révèle", /*spanish*/"levantar una #roca al borde del valle# esconde"},
  });

  HintText GCGrottoPlatform_To_GCGrotto = HintText::Entrance({
                     //obscure text
                     Text{"a #pool of lava# in Goron City blocks the way to", "l'#étang de lave# dans le village Goron renferme", /*spanish*/"un #estanque de lava# en la Ciudad Goron bloquea el paso a"},
  });

  HintText GerudoFortress_To_GFStormsGrotto = HintText::Entrance({
                     //obscure text
                     Text{"a #storm within Gerudo's Fortress# reveals", "la #tempête dans la forteresse# révèle", /*spanish*/"una #tormenta en la Fortaleza Gerudo# revela"},
  });

  HintText ZorasDomain_To_ZDStormsGrotto = HintText::Entrance({
                     //obscure text
                     Text{"a #storm within Zora's Domain# reveals", "la #tempête dans le Domaine Zora# révèle", /*spanish*/"una #tormenta en la Región de los Zora# revela"},
  });

  HintText HyruleCastleGrounds_To_HCStormsGrotto = HintText::Entrance({
                     //obscure text
                     Text{"a #storm near the castle# reveals", "la #tempête près du château# révèle", /*spanish*/"una #tormenta junto al castillo# revela"},
  });

  HintText GVFortressSide_To_GVStormsGrotto = HintText::Entrance({
                     //obscure text
                     Text{"a #storm in the valley# reveals", "la #tempête dans la vallée# révèle", /*spanish*/"una #tormenta en el valle# revela"},
  });

  HintText DesertColossus_To_ColossusGreatFairyFountain = HintText::Entrance({
                     //obscure text
                     Text{"a #fractured desert wall# hides", "le #mur fragile du désert# cache", /*spanish*/"una #agrietada pared del desierto# esconde"},
  });

  HintText GanonsCastleGrounds_To_OGCGreatFairyFountain = HintText::Entrance({
                     //obscure text
                     Text{"a #heavy pillar# outside the castle obstructs", "le #rocher fragile près du château# cache", /*spanish*/"una #pesada columna# fuera del castillo obstruye"},
  });

  HintText ZorasFountain_To_ZFGreatFairyFountain = HintText::Entrance({
                     //obscure text
                     Text{"a #fountain wall# hides", "le #mur fragile du réservoir# cache", /*spanish*/"una #pared de la fuente# esconde"},
  });

  HintText GVFortressSide_To_GVCarpenterTent = HintText::Entrance({
                     //obscure text
                     Text{"a #tent in the valley# covers", "la #tente dans la vallée# recouvre", /*spanish*/"una #tienda de campaña del valle# cubre"},
  });

  HintText GYWarpPadRegion_To_ShadowTempleEntryway = HintText::Entrance({
                     //obscure text
                     Text{"at the #back of the Graveyard#, there is", "#derrière le cimetière# gît", /*spanish*/"en la #parte trasera del cementerio# se halla"},
  });

  HintText LakeHylia_To_WaterTempleLobby = HintText::Entrance({
                     //obscure text
                     Text{"deep #under a vast lake#, one can find", "#sous le lac# gît", /*spanish*/"en las #profundidades de un lago inmenso# se halla"},
  });

  HintText GerudoFortress_To_GerudoTrainingGroundsLobby = HintText::Entrance({
                     //obscure text
                     Text{"paying a #fee to the Gerudos# grants access to", "l'#entrée payante des Gerudo# donne accès à", /*spanish*/"pagarle una #tasa a las gerudo# da acceso a"},
  });

  HintText ZorasFountain_To_JabuJabusBellyBeginning = HintText::Entrance({
                     //obscure text
                     Text{"inside #Jabu Jabu#, one can find", "#dans Jabu-Jabu# se trouve", /*spanish*/"dentro de #Jabu Jabu# se halla"},
  });

  HintText KakarikoVillage_To_BottomOfTheWell = HintText::Entrance({
                     //obscure text
                     Text{"a #village well# leads to", "dans le fonds du #puits du village# gît", /*spanish*/"el #pozo de un pueblo# conduce a"},
  });

  /*--------------------------
  |      EXIT HINT TEXT      |
  ---------------------------*/
  //maybe make a new type for this? I'm not sure if it really matters

  HintText LinksPocket = HintText::Exclude({
                     //obscure text
                     Text{"Link's Pocket", "les poches de @", /*spanish*/"el bolsillo de Link"},
  });

  HintText KokiriForest = HintText::Exclude({
                     //obscure text
                     Text{"Kokiri Forest", "la forêt Kokiri", /*spanish*/"el Bosque Kokiri"},
  });

  HintText TheLostWoods = HintText::Exclude({
                     //obscure text
                     Text{"the Lost Woods", "les bois perdus", /*spanish*/"el Bosque Perdido"},
  });

  HintText SacredForestMeadow = HintText::Exclude({
                     //obscure text
                     Text{"Sacred Forest Meadow", "le bosquet sacré", /*spanish*/"la pradera sagrada del bosque"},
  });

  HintText HyruleField = HintText::Exclude({
                     //obscure text
                     Text{"Hyrule Field", "la plaine d'Hyrule", /*spanish*/"en la Llanura de Hyrule"},
  });

  HintText LakeHylia = HintText::Exclude({
                     //obscure text
                     Text{"Lake Hylia", "le lac Hylia", /*spanish*/"el Lago Hylia"},
  });

  HintText GerudoValley = HintText::Exclude({
                     //obscure text
                     Text{"Gerudo Valley", "la vallée Gerudo", /*spanish*/"el Valle Gerudo"},
  });

  HintText GerudosFortress = HintText::Exclude({
                     //obscure text
                     Text{"Gerudo's Fortress", "la forteresse Gerudo", /*spanish*/"la fortaleza gerudo"},
  });

  HintText HauntedWasteland = HintText::Exclude({
                     //obscure text
                     Text{"Haunted Wasteland", "le désert hanté", /*spanish*/"el desierto encantado"},
  });

  HintText DesertColossus = HintText::Exclude({
                     //obscure text
                     Text{"Desert Colossus", "le colosse du désert", /*spanish*/"el Coloso del Desierto"},
  });

  HintText TheMarket = HintText::Exclude({
                     //obscure text
                     Text{"the Market", "la place du marché", /*spanish*/"la plaza del mercado"},
  });

  HintText TempleOfTime = HintText::Exclude({
                     //obscure text
                     Text{"Temple of Time", "le temple du temps", /*spanish*/"el Templo del Tiempo"},
  });

  HintText HyruleCastle = HintText::Exclude({
                     //obscure text
                     Text{"Hyrule Castle", "le château d'Hyrule", /*spanish*/"el Castillo de Hyrule"},
  });

  HintText OutsideGanonsCastle = HintText::Exclude({
                     //obscure text
                     Text{"outside Ganon's Castle", "le château de Ganon", /*spanish*/"las afueras del Castillo de Ganon"},
  });

  HintText KakarikoVillage = HintText::Exclude({
                     //obscure text
                     Text{"Kakariko Village", "le village Cocorico", /*spanish*/"Kakariko"},
  });

  HintText TheGraveyard = HintText::Exclude({
                     //obscure text
                     Text{"the Graveyard", "le cimetière", /*spanish*/"el cementerio"},
  });

  HintText DeathMountainTrail = HintText::Exclude({
                     //obscure text
                     Text{"Death Mountain Trail", "le chemin du péril", /*spanish*/"el sendero de la Montaña de la Muerte"},
  });

  HintText GoronCity = HintText::Exclude({
                     //obscure text
                     Text{"Goron City", "le village Goron", /*spanish*/"la Ciudad Goron"},
  });

  HintText DeathMountainCrater = HintText::Exclude({
                     //obscure text
                     Text{"Death Mountain Crater", "le cratère du péril", /*spanish*/"el cráter de la Montaña de la Muerte"},
  });

  HintText ZorasRiver = HintText::Exclude({
                     //obscure text
                     Text{"Zora's River", "le fleuve zora", /*spanish*/"el Río Zora"},
  });

  HintText ZorasDomain = HintText::Exclude({
                     //obscure text
                     Text{"Zora's Domain", "le domaine Zora", /*spanish*/"la Región de los Zora"},
  });

  HintText ZorasFountain = HintText::Exclude({
                     //obscure text
                     Text{"Zora's Fountain", "la fontaine Zora", /*spanish*/"la Fuente Zora"},
  });

  HintText LonLonRanch = HintText::Exclude({
                     //obscure text
                     Text{"Lon Lon Ranch", "le ranch Lon Lon", /*spanish*/"el Rancho Lon Lon"},
  });


  /*--------------------------
  |     REGION HINT TEXT     |
  ---------------------------*/

  HintText KF_LinksHouse = HintText::Region({
                     //obscure text
                     Text{"Link's House", "la #maison de @#", /*spanish*/"la casa de Link"},
  });

  HintText ToT_Main = HintText::Region({
                     //obscure text
                     Text{"the #Temple of Time#", "le #temple du temps#", /*spanish*/"el Templo del Tiempo"},
  });

  HintText KF_MidosHouse = HintText::Region({
                     //obscure text
                     Text{"Mido's house", "la #cabane du Grand Mido#", /*spanish*/"la casa de Mido"},
  });

  HintText KF_SariasHouse = HintText::Region({
                     //obscure text
                     Text{"Saria's House", "la #cabane de Saria#", /*spanish*/"la casa de Saria"},
  });

  HintText KF_HouseOfTwins = HintText::Region({
                     //obscure text
                     Text{"the #House of Twins#", "la #cabane des jumelles#", /*spanish*/"la casa de las gemelas"},
  });

  HintText KF_KnowItAllHouse = HintText::Region({
                     //obscure text
                     Text{"Know-It-All Brothers' House", "la #cabane des frères Je-Sais-Tout#", /*spanish*/"la casa de los hermanos Sabelotodo"},
  });

  HintText KF_KokiriShop = HintText::Region({
                     //obscure text
                     Text{"the #Kokiri Shop#", "le #magasin Kokiri#", /*spanish*/"la Tienda Kokiri"},
  });

  HintText LH_Lab = HintText::Region({
                     //obscure text
                     Text{"the #Lakeside Laboratory#", "le #laboratoire du lac#", /*spanish*/"el laboratorio del lago"},
  });

  HintText LH_FishingHole = HintText::Region({
                     //obscure text
                     Text{"the #Fishing Pond#", "l'#étang#", /*spanish*/"el estanque"},
  });

  HintText GV_CarpenterTent = HintText::Region({
                     //obscure text
                     Text{"the #Carpenters' tent#", "la #tente des charpentiers#", /*spanish*/"la #tienda de campaña de los carpinteros#"},
  });

  HintText MK_GuardHouse = HintText::Region({
                     //obscure text
                     Text{"the #Guard House#", "le #poste de garde#", /*spanish*/"la caseta de guardia"},
  });

  HintText MK_MaskShop = HintText::Region({
                     //obscure text
                     Text{"the #Happy Mask Shop#", "la #foire aux masques#", /*spanish*/"la Tienda de La Máscara Feliz"},
  });

  HintText MK_BombchuBowling = HintText::Region({
                     //obscure text
                     Text{"the #Bombchu Bowling Alley#", "le #bowling teigneux#", /*spanish*/"la Bolera Bombchu"},
  });

  HintText MK_PotionShop = HintText::Region({
                     //obscure text
                     Text{"the #Market Potion Shop#", "l'#apothicaire de la place du marché#", /*spanish*/"la tienda de pociones de la plaza del mercado"},
  });

  HintText MK_TreasureChestGame = HintText::Region({
                     //obscure text
                     Text{"the #Treasure Box Shop#", "la #chasse aux trésors#", /*spanish*/"el Cofre del Tesoro"},
  });

  HintText MK_BombchuShop = HintText::Region({
                     //obscure text
                     Text{"the #Bombchu Shop#", "le #magasin de missiles#", /*spanish*/"la Tienda Bombchu"},
  });

  HintText MK_ManInGreenHouse = HintText::Region({
                     //obscure text
                     Text{"Man in Green's House", "la #maison de l'homme en vert#", /*spanish*/"la casa del hombre de verde"},
  });

  HintText Kak_Windmill = HintText::Region({
                     //obscure text
                     Text{"the #Windmill#", "le #moulin#", /*spanish*/"el #molino#"},
  });

  HintText Kak_CarpenterBossHouse = HintText::Region({
                     //obscure text
                     Text{"the #Carpenters' Boss House#", "la #maison du chef des ouvriers#", /*spanish*/"la casa del capataz de los carpinteros"},
  });

  HintText Kak_HouseOfSkulltula = HintText::Region({
                     //obscure text
                     Text{"the #House of Skulltula#", "la #maison des Skulltulas#", /*spanish*/"la casa de las skulltulas"},
  });

  HintText Kak_ImpasHouse = HintText::Region({
                     //obscure text
                     Text{"Impa's House", "la #maison d'Impa#", /*spanish*/"la casa de Impa"},
  });

  HintText Kak_ImpasHouseBack = HintText::Region({
                     //obscure text
                     Text{"Impa's cow cage", "la #cage à vache d'Impa#", /*spanish*/"la jaula de la vaca de Impa"},
  });

  HintText Kak_OddMedicineBuilding = HintText::Region({
                     //obscure text
                     Text{"Granny's Potion Shop", "la #maison bleue de Cocorico#", /*spanish*/"la tienda de pociones de la abuela"},
  });

  HintText GY_DampesHouse = HintText::Region({
                     //obscure text
                     Text{"Dampé's Hut", "la #cabane du fossoyeur#", /*spanish*/"la cabaña de Dampé"},
  });

  HintText GC_Shop = HintText::Region({
                     //obscure text
                     Text{"the #Goron Shop#", "la #boutique Goron#", /*spanish*/"la #tienda goron"},
  });

  HintText ZD_Shop = HintText::Region({
                     //obscure text
                     Text{"the #Zora Shop#", "la #boutique Zora#", /*spanish*/"la #tienda zora"},
  });

  HintText LLR_TalonsHouse = HintText::Region({
                     //obscure text
                     Text{"Talon's House", "la #maison de Talon#", /*spanish*/"la casa de Talon"},
  });

  HintText LLR_Stables = HintText::Region({
                     //obscure text
                     Text{"a #stable#", "l'#étable#", /*spanish*/"el establo"},
  });

  HintText LLR_Tower = HintText::Region({
                     //obscure text
                     Text{"the #Lon Lon Tower#", "le #silo du ranch Lon Lon#", /*spanish*/"la torre Lon Lon"},
  });

  HintText MK_Bazaar = HintText::Region({
                     //obscure text
                     Text{"the #Market Bazaar#", "le #bazar de la place du marché#", /*spanish*/"el bazar de la plaza del mercado"},
  });

  HintText MK_ShootingGallery = HintText::Region({
                     //obscure text
                     Text{"a #Slingshot Shooting Gallery#", "le #jeu d'adresse de la place du marché#", /*spanish*/"el Tiro al Blanco con tirachinas"},
  });

  HintText Kak_Bazaar = HintText::Region({
                     //obscure text
                     Text{"the #Kakariko Bazaar#", "le #bazar de Cocorico#", /*spanish*/"el bazar de Kakariko"},
  });

  HintText Kak_PotionShopFront = HintText::Region({
                     //obscure text
                     Text{"the #Kakariko Potion Shop#", "l'#apothicaire de Cocorico#", /*spanish*/"la tienda de pociones de Kakariko"},
  });

  HintText Kak_PotionShopBack = HintText::Region({
                     //obscure text
                     Text{"the #Kakariko Potion Shop#", "l'#apothicaire de Cocorico#", /*spanish*/"la tienda de pociones de Kakariko"},
  });

  HintText Kak_ShootingGallery = HintText::Region({
                     //obscure text
                     Text{"a #Bow Shooting Gallery#", "le #jeu d'adresse de Cocorico#", /*spanish*/"el Tiro al Blanco con arco"},
  });

  HintText Colossus_GreatFairyFountain = HintText::Region({
                     //obscure text
                     Text{"a #Great Fairy Fountain#", "la #grande fée du colosse#", /*spanish*/"una fuente de la Gran Hada"},
  });

  HintText HC_GreatFairyFountain = HintText::Region({
                     //obscure text
                     Text{"a #Great Fairy Fountain#", "la #grande fée du château#", /*spanish*/"una fuente de la Gran Hada"},
  });

  HintText OGC_GreatFairyFountain = HintText::Region({
                     //obscure text
                     Text{"a #Great Fairy Fountain#", "la #grande fée des ruines#", /*spanish*/"una fuente de la Gran Hada"},
  });

  HintText DMC_GreatFairyFountain = HintText::Region({
                     //obscure text
                     Text{"a #Great Fairy Fountain#", "la #grande fée du volcan#", /*spanish*/"una fuente de la Gran Hada"},
  });

  HintText DMT_GreatFairyFountain = HintText::Region({
                     //obscure text
                     Text{"a #Great Fairy Fountain#", "la #grande fée de la montagne#", /*spanish*/"una fuente de la Gran Hada"},
  });

  HintText ZF_GreatFairyFountain = HintText::Region({
                     //obscure text
                     Text{"a #Great Fairy Fountain#", "la #grande fée de la fontaine#", /*spanish*/"una fuente de la Gran Hada"},
  });

  HintText GY_ShieldGrave = HintText::Region({
                     //obscure text
                     Text{"a #grave with a free chest#", "le #tombeau avec un trésor#", /*spanish*/"la #tumba del cofre gratis#"},
  });

  HintText GY_HeartPieceGrave = HintText::Region({
                     //obscure text
                     Text{"a chest spawned by #Sun's Song#", "le #tombeau avec un mort#", /*spanish*/"la #tumba de la Canción del Sol#"},
  });

  HintText GY_ComposersGrave = HintText::Region({
                     //obscure text
                     Text{"the #Composers' Grave#", "la #tombe royale#", /*spanish*/"el #Panteón Real#"},
  });

  HintText GY_DampesGrave = HintText::Region({
                     //obscure text
                     Text{"Dampé's Grave", "la #tombe d'Igor#", /*spanish*/"la #tumba de Dampé"},
  });

  HintText DMT_CowGrotto = HintText::Region({
                     //obscure text
                     Text{"a solitary #Cow#", "la #grotte avec une vache#", /*spanish*/"una #vaca# solitaria"},
  });

  HintText HC_StormsGrotto = HintText::Region({
                     //obscure text
                     Text{"a sandy grotto with #fragile walls#", "la #grotte avec des murs fragiles#", /*spanish*/"la arenosa gruta de #frágiles paredes#"},
  });

  HintText HF_TektiteGrotto = HintText::Region({
                     //obscure text
                     Text{"a pool guarded by a #Tektite#", "l'#étang sous-terrain avec un Araknon#", /*spanish*/"un charco custodiado por un #Tektite#"},
  });

  HintText HF_NearKakGrotto = HintText::Region({
                     //obscure text
                     Text{"a #Big Skulltula# guarding a Gold one", "la #grotte d'araignées#", /*spanish*/"un #skulltula# custodiando una dorada"},
  });

  HintText HF_CowGrotto = HintText::Region({
                     //obscure text
                     Text{"a grotto full of #spider webs#", "la #grotte couverte de toiles d'araignées#", /*spanish*/"una gruta llena de #telarañas#"},
  });

  HintText Kak_RedeadGrotto = HintText::Region({
                     //obscure text
                     Text{"#ReDeads# guarding a chest", "#deux morts enterrés#", /*spanish*/"los #ReDeads# que custodian un cofre"},
  });

  HintText SFM_WolfosGrotto = HintText::Region({
                     //obscure text
                     Text{"#Wolfos# guarding a chest", "la #grotte iridescente#", /*spanish*/"los #Wolfos# que custodian un cofre"},
  });

  HintText GV_OctorokGrotto = HintText::Region({
                     //obscure text
                     Text{"an #Octorok# guarding a rich pool", "un #étang sous-terrain avec un Octorok#", /*spanish*/"un #Octorok# que custodia un lujoso charco"},
  });

  HintText DekuTheater = HintText::Region({
                     //obscure text
                     Text{"the #Lost Woods Stage#", "le théâtre sylvestre#", /*spanish*/"el #escenario del Bosque Perdido#"},
  });

  HintText ZR_OpenGrotto = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", "une #grotte avec un trésor#", /*spanish*/"una #gruta genérica#"},
  });

  HintText DMC_UpperGrotto = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", "une #grotte avec un trésor#", /*spanish*/"una #gruta genérica#"},
  });

  HintText DMT_StormsGrotto = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", "une #grotte avec un trésor#", /*spanish*/"una #gruta genérica#"},
  });

  HintText Kak_OpenGrotto = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", "une #grotte avec un trésor#", /*spanish*/"una #gruta genérica#"},
  });

  HintText HF_NearMKGrotto = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", "une #grotte avec un trésor#", /*spanish*/"una #gruta genérica#"},
  });

  HintText HF_OpenGrotto = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", "une #grotte avec un trésor#", /*spanish*/"una #gruta genérica#"},
  });

  HintText HF_SoutheastGrotto = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", "une #grotte avec un trésor#", /*spanish*/"una #gruta genérica#"},
  });

  HintText KF_StormsGrotto = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", "une #grotte avec un trésor#", /*spanish*/"una #gruta genérica#"},
  });

  HintText LW_NearShortcutsGrotto = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", "une #grotte avec un trésor#", /*spanish*/"una #gruta genérica#"},
  });

  HintText HF_InsideFenceGrotto = HintText::Region({
                     //obscure text
                     Text{"a #single Upgrade Deku Scrub#", "une #grotte avec une peste Mojo#", /*spanish*/"un #solitario mercader deku de mejora#"},
  });

  HintText LW_ScrubsGrotto = HintText::Region({
                     //obscure text
                     Text{"#2 Deku Scrubs# including an Upgrade one", "une #grotte avec deux pestes Mojo#", /*spanish*/"unos #dos mercaderes deku, incluyendo uno de mejora#"},
  });

  HintText Colossus_Grotto = HintText::Region({
                     //obscure text
                     Text{"2 Deku Scrubs", "une #grotte avec deux pestes Mojo#", /*spanish*/"unos #dos mercaderes deku#"},
  });

  HintText ZR_StormsGrotto = HintText::Region({
                     //obscure text
                     Text{"2 Deku Scrubs", "une #grotte avec deux pestes Mojo#", /*spanish*/"unos #dos mercaderes deku#"},
  });

  HintText SFM_StormsGrotto = HintText::Region({
                     //obscure text
                     Text{"2 Deku Scrubs", "une #grotte avec deux pestes Mojo#", /*spanish*/"unos #dos mercaderes deku#"},
  });

  HintText GV_StormsGrotto = HintText::Region({
                     //obscure text
                     Text{"2 Deku Scrubs", "une #grotte avec deux pestes Mojo#", /*spanish*/"unos #dos mercaderes deku#"},
  });

  HintText LH_Grotto = HintText::Region({
                     //obscure text
                     Text{"3 Deku Scrubs", "une #grotte avec trois pestes Mojo#", /*spanish*/"unos #tres mercaderes deku#"},
  });

  HintText DMC_HammerGrotto = HintText::Region({
                     //obscure text
                     Text{"3 Deku Scrubs", "une #grotte avec trois pestes Mojo#", /*spanish*/"unos #tres mercaderes deku#"},
  });

  HintText GC_Grotto = HintText::Region({
                     //obscure text
                     Text{"3 Deku Scrubs", "une #grotte avec trois pestes Mojo#", /*spanish*/"unos #tres mercaderes deku#"},
  });

  HintText LLR_Grotto = HintText::Region({
                     //obscure text
                     Text{"3 Deku Scrubs", "une #grotte avec trois pestes Mojo#", /*spanish*/"unos #tres mercaderes deku#"},
  });

  HintText ZR_FairyGrotto = HintText::Region({
                     //obscure text
                     Text{"a small #Fairy Fountain#", "une #fontaine de fées#", /*spanish*/"una pequeña #fuente de las hadas#"},
  });

  HintText HF_FairyGrotto = HintText::Region({
                     //obscure text
                     Text{"a small #Fairy Fountain#", "une #fontaine de fées#", /*spanish*/"una pequeña #fuente de las hadas#"},
  });

  HintText SFM_FairyGrotto = HintText::Region({
                     //obscure text
                     Text{"a small #Fairy Fountain#", "une #fontaine de fées#", /*spanish*/"una pequeña #fuente de las hadas#"},
  });

  HintText ZD_StormsGrotto = HintText::Region({
                     //obscure text
                     Text{"a small #Fairy Fountain#", "une #fontaine de fées#", /*spanish*/"una pequeña #fuente de las hadas#"},
  });

  HintText GF_StormsGrotto = HintText::Region({
                     //obscure text
                     Text{"a small #Fairy Fountain#", "une #fontaine de fées#", /*spanish*/"una pequeña #fuente de las hadas#"},
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
                     Text{"an ancient tree", "le vieil arbre", /*spanish*/"un ancestral árbol"},
                   },
                     //clear text
                     Text{"Deku Tree", "l'arbre Mojo", /*spanish*/"el Árbol Deku"}
  );

  HintText DodongosCavern = HintText::DungeonName({
                     //obscure text
                     Text{"an immense cavern", "l'immense caverne", /*spanish*/"una descomunal cueva"},
                   },
                     //clear text
                     Text{ "Dodongo's Cavern", "la caverne Dodongo", /*spanish*/"la Cueva de los Dodongos"}
  );

  HintText JabuJabusBelly = HintText::DungeonName({
                     //obscure text
                     Text{"the belly of a deity", "le ventre d'un gardien", /*spanish*/"la tripa de cierta deidad"},
                   },
                     //clear text
                     Text{ "Jabu Jabu's Belly", "le ventre de Jabu-Jabu", /*spanish*/"la tripa de Jabu Jabu"}
  );

  HintText ForestTemple = HintText::DungeonName({
                     //obscure text
                     Text{"a deep forest", "la profonde forêt", /*spanish*/"un profundo bosque"},
                   },
                     //clear text
                     Text{ "Forest Temple", "le temple de la forêt", /*spanish*/"el Templo del Bosque"}
  );

  HintText FireTemple = HintText::DungeonName({
                     //obscure text
                     Text{"a high mountain", "la grande montagne", /*spanish*/"una alta montaña"},
                   },
                     //clear text
                     Text{ "Fire Temple", "le temple du feu", /*spanish*/"el Templo del Fuego"}
  );

  HintText WaterTemple = HintText::DungeonName({
                     //obscure text
                     Text{"a vast lake", "le vaste lac", /*spanish*/"un lago inmenso"},
                   },
                     //clear text
                     Text{ "Water Temple", "le temple de l'eau", /*spanish*/"el Templo del Agua"}
  );

  HintText ShadowTemple = HintText::DungeonName({
                     //obscure text
                     Text{"the house of the dead", "la maison des morts", /*spanish*/"la casa de la muerte"},
                   },
                     //clear text
                     Text{ "Shadow Temple", "le temple de l'ombre", /*spanish*/"el Templo de las Sombras"}
  );

  HintText SpiritTemple = HintText::DungeonName({
                     //obscure text
                     Text{"the goddess of the sand", "la déesse des sables", /*spanish*/"la diosa de la arena"},
                   },
                     //clear text
                     Text{ "Spirit Temple", "le temple de l'esprit", /*spanish*/"el Templo del Espíritu"}
  );

  HintText IceCavern = HintText::DungeonName({
                     //obscure text
                     Text{"a frozen maze", "le dédale glacé", /*spanish*/"un gélido laberinto"},
                   },
                     //clear text
                     Text{ "Ice Cavern", "la caverne de glace", /*spanish*/"la caverna de hielo"}
  );

  HintText BottomOfTheWell = HintText::DungeonName({
                     //obscure text
                     Text{"a shadow\'s prison", "la prison d'une ombre", /*spanish*/"la prisión de las sombras"},
                   },
                     //clear text
                     Text{ "Bottom of the Well", "le fonds du puits", /*spanish*/"el fondo del pozo"}
  );

  HintText GerudoTrainingGrounds = HintText::DungeonName({
                     //obscure text
                     Text{"the test of thieves", "l'épreuve des voleurs", /*spanish*/"la prueba de las ladronas"},
                   },
                     //clear text
                     Text{ "Gerudo Training Grounds", "le gymnase Gerudo", /*spanish*/"el Centro de Instrucción Gerudo"}
  );

  HintText GanonsCastle = HintText::DungeonName({
                     //obscure text
                     Text{"a conquered citadel", "la citadelle assiégée", /*spanish*/"una conquistada ciudadela"},
                   },
                     //clear text
                     Text{ "Inside Ganon's Castle", "l'intérieur du château de Ganon", /*spanish*/"el interior del Castillo de Ganondorf"}
  );

  /*--------------------------
  |      BOSS HINT TEXT      |
  ---------------------------*/

  HintText QueenGohma = HintText::Boss({
                     //obscure text
                     Text{"An #ancient tree# rewards", "le #vieil arbre# octroie", /*spanish*/"un #ancestral árbol# premia con"},
                   },
                     //clear text
                     Text{"the #Deku Tree# rewards", "l'#arbre Mojo# octroie", /*spanish*/"el #Árbol Deku# premia con"}
  );

  HintText KingDodongo = HintText::Boss({
                     //obscure text
                     Text{"An #immense cavern# rewards", "l'#immense caverne# octroie", /*spanish*/"una #descomunal cueva# premia con"},
                   },
                     //clear text
                     Text{"#Dodongo's Cavern# rewards", "la #caverne Dodongo# octroie", /*spanish*/"la #Cueva de los Dodongos# premia con"}
  );

  HintText Barinade = HintText::Boss({
                     //obscure text
                     Text{"the #belly of a deity# rewards", "le #ventre du gardien# octroie", /*spanish*/"la #tripa de cierta deidad# premia con"},
                   },
                     //clear text
                     Text{"#Jabu Jabu's Belly# rewards", "le #ventre de Jabu-Jabu# octroie", /*spanish*/"la #Tripa de Jabu Jabu# premia con"}
  );

  HintText PhantomGanon = HintText::Boss({
                     //obscure text
                     Text{"a #deep forest# rewards", "la #profonde forêt# octroie", /*spanish*/"un #profundo bosque# premia con"},
                   },
                     //clear text
                     Text{"the #Forest Temple# rewards", "le #temple de la forêt# octroie", /*spanish*/"el #Templo del Bosque# premia con"}
  );

  HintText Volvagia = HintText::Boss({
                     //obscure text
                     Text{"a #high mountain# rewards", "la #grande montagne# octroie", /*spanish*/"una #alta montaña# premia con"},
                   },
                     //clear text
                     Text{"the #Fire Temple# rewards", "le #temple du feu# octroie", /*spanish*/"el #Templo del Fuego# premia con"}
  );

  HintText Morpha = HintText::Boss({
                     //obscure text
                     Text{"a #vast lake# rewards", "le #vaste lac# octroie", /*spanish*/"un #lago inmenso# premia con"},
                   },
                     //clear text
                     Text{"the #Water Temple# rewards", "le #temple de l'eau# octroie", /*spanish*/"el #Templo del Agua# premia con"}
  );

  HintText BongoBongo = HintText::Boss({
                     //obscure text
                     Text{"the #house of the dead# rewards", "la #maison des morts# octroie", /*spanish*/"la #casa de la muerte# premia con"},
                   },
                     //clear text
                     Text{"the #Shadow Temple# rewards", "le #temple de l'ombre# octroie", /*spanish*/"el #Templo de las Sombras"}
  );

  HintText Twinrova = HintText::Boss({
                     //obscure text
                     Text{"a #goddess of the sand# rewards", "la #déesse des sables# octroie", /*spanish*/"la #diosa de la arena# premia con"},
                   },
                     //clear text
                     Text{ "the #Spirit Temple# rewards", "le #temple de l'esprit# octroie", /*spanish*/"el #Templo del Espíritu# premia con"}
  );

  HintText LinksPocketBoss = HintText::Boss({
                     //obscure text
                     Text{"#@'s pocket# rewards", "#@ débute avec#", /*spanish*/"el #bolsillo de @# premia con"},
                   },
                     //clear text
                     Text{"#@ already has#", "#@ a déjà#", /*spanish*/"el #bolsillo de @ ya tiene#"}
  );

  /*--------------------------
  |     BRIDGE HINT TEXT     |
  ---------------------------*/

  HintText BridgeVanilla = HintText::Bridge({
                     //obscure text
                     Text{"the #Shadow and Spirit Medallions# as well as the #Light Arrows#", "les #médaillons de l'ombre et de l'esprit#, ainsi que les #flèches de lumière#", /*spanish*/"tanto el #Medallón de las Sombras y el del Espíritu# junto a las #Flechas de Luz#"},
  });

  HintText BridgeStones = HintText::Bridge({
                     //obscure text
                     Text{"Spiritual Stones", "pierres spirituelles", /*spanish*/"las piedras espirituales"},
  });

  HintText BridgeMedallions = HintText::Bridge({
                     //obscure text
                     Text{"Medallions", "médaillons", /*spanish*/"los medallones"},
  });

  HintText BridgeRewards = HintText::Bridge({
                     //obscure text
                     Text{"Spiritual Stones and Medallions", "pierres spirituelles et médaillons", /*spanish*/"las piedras espirituales y los medallones"},
  });

  HintText BridgeDungeons = HintText::Bridge({
                     //obscure text
                     Text{"Completed Dungeons", "donjons complétés", /*spanish*/"al completar las mazmorras"},
  });

  HintText BridgeTokens = HintText::Bridge({
                     //obscure text
                     Text{"Gold Skulltula Tokens", "symboles de Skulltula d'or", /*spanish*/"al obtener los símbolos de skulltulas doradas"},
  });

  /*--------------------------
  | GANON BOSS KEY HINT TEXT |
  ---------------------------*/

  HintText GanonBKVanilla = HintText::GanonsBossKey({
                     //obscure text
                     Text{"kept in a big chest #inside its tower#", "dans un grand coffre #dans sa tour#", /*spanish*/"en un gran cofre #de su torre#"},
  });

  HintText GanonBKOwnDungeon = HintText::GanonsBossKey({
                     //obscure text
                     Text{"hidden somewhere #inside its castle#", "quelque part #dans son château#", /*spanish*/"escondida en #algún lugar de su castillo#"},
  });

  HintText GanonBKOverworld = HintText::GanonsBossKey({
                     //obscure text
                     Text{"hidden #outside of dungeons# in Hyrule", "quelque part dans Hyrule, #hors des donjons#", /*spanish*/"escondida #fuera de las mazmorras# de Hyrule"},
  });

  HintText GanonBKAnyDungeon = HintText::GanonsBossKey({
                     //obscure text
                     Text{"hidden #inside a dungeon# in Hyrule", "#dans un des donjons# d'Hyrule", /*spanish*/"escondida #en una mazmorra# de Hyrule"},
  });

  HintText GanonBKKeysanity = HintText::GanonsBossKey({
                     //obscure text
                     Text{"hidden somewhere #in Hyrule#", "quelque part #dans Hyrule#", /*spanish*/"escondida en #cualquier lugar de Hyrule#"},
  });

  HintText GanonBKTriforce = HintText::GanonsBossKey({
                     //obscure text
                     Text{"given to the Hero once the #Triforce# is completed", "dans la #Triforce#, quand celle-ci sera complétée", /*spanish*/"recibida por el héroe cuando haya completado la #Trifuerza#"},
  });

  /*--------------------------
  |      LACS HINT TEXT      |
  ---------------------------*/

  HintText LACSVanilla = HintText::LACS({
                     //obscure text
                     Text{"the #Shadow and Spirit Medallions#", "les #médaillons de l'ombre et de l'esprit#", /*spanish*/"el #Medallón de las Sombras y el Espíritu#"},
  });

  HintText LACSMedallions = HintText::LACS({
                     //obscure text
                     Text{"Medallions", "les médaillons", /*spanish*/"los #medallones#"},
  });

  HintText LACSStones = HintText::LACS({
                     //obscure text
                     Text{"Spiritual Stones", "les pierres spirituelles", /*spanish*/"las #piedras espirituales#"},
  });

  HintText LACSRewards = HintText::LACS({
                     //obscure text
                     Text{"Spiritual Stones and Medallions", "les pierres spirituelles et les médaillons", /*spanish*/"las #piedras espirituales y los medallones#"},
  });

  HintText LACSTokens = HintText::LACS({
                     //obscure text
                     Text{"Gold Skulltula Tokens", "les symboles de Skulltula d'or", /*spanish*/"los #símbolos de skulltulas doradas#"},
  });

  /*--------------------------
  |     TRIAL HINT TEXT      |
  ---------------------------*/

  HintText SixTrials = HintText::Exclude({
                     //obscure text
                     Text{"#Ganon's Tower# is protected by a powerful barrier.", "#la tour de Ganon# est protégée par une puissante barrière", /*spanish*/""},
  });

  HintText ZeroTrials = HintText::Exclude({
                     //obscure text
                     Text{"Sheik dispelled the barrier around #Ganon's Tower#.", "Sheik a dissipé la barrière autour de #la tour de Ganon#", /*spanish*/""},
  });

  HintText FourToFiveTrials = HintText::Exclude({
                     //obscure text
                     Text{" was dispelled by Sheik.", " a été dissipée par Sheik.", /*spanish*/""},
  });

  HintText OneToThreeTrials = HintText::Exclude({
                     //obscure text
                     Text{" protects Ganons Tower.", " protège la tour de Ganon.", /*spanish*/""},
  });

  /*--------------------------
  |        ALTAR TEXT        |
  ---------------------------*/

  HintText SpiritualStoneTextStart = HintText::Altar({
                     //obscure text
                     Text{"3 Spiritual Stones found in Hyrule...", "Les trois pierres spirituelles cachées dans Hyrule...", /*spanish*/"Tres piedras espirituales encontradas en Hyrule..."},
  });

  HintText ChildAltarTextEnd = HintText::Altar({
                     //obscure text
                     Text{"Ye who may become a Hero...&Stand with the Ocarina and play the Song of Time.", "À celui qui a quête de devenir héros...&Portez l'Ocarina et jouez le chant du temps.", /*spanish*/"Aquel que se convierta en el héroe... Tomad la ocarina y entonad la Canción del Tiempo."},
  });

  HintText AdultAltarTextStart = HintText::Altar({
                     //obscure text
                     Text{"When evil rules all, an awakening voice from the Sacred Realm will call those destined to be Sages, who dwell in the #five temples#.", "Quand le mal aura triomphé, une voix du Saint Royaume appellera ceux cachés dans les #cinq temples#, destinés à être Sages.", /*spanish*/"Cuando el mal lo impregne todo, desde el Reino Sagrado surgirá unz voz que hará despertar a los sabios que moran en los #cinco templos#."},
  });

  HintText AdultAltarTextEnd = HintText::Altar({
                     //obscure text
                     Text{"Together with the Hero of Time, the awakened ones will bind the evil and return the light of peace to the world...", "Ensemble avec le Héros du Temps, ces Sages emprisonneront le mal et réinstaureront la lumière de paix dans le monde...", /*spanish*/"Con el héroe del Tiempo, aquellos que despierten detendrán el mal y volverán al mundo de luz la paz..."},
  });

  /*--------------------------
  |   VALIDATION LINE TEXT   |
  ---------------------------*/

  HintText ValidationLine = HintText::Validation({
                     //obscure text
                     Text{"Hmph... Since you made it this far, I'll let you know what glorious prize of Ganon's you likely missed out on in my tower.^Behold...^", "Pah! Puisque tu t'es rendu ici, je te dirai quel trésor tu as manqué dans ma tour.^Et c'est...^", /*spanish*/"Mmm... Ya que has llegado hasta aquí, te diré qué preciado objeto de Ganon puedes haberte dejado en mi torre.^He aquí..."},
  });

  /*--------------------------
  | LIGHT ARROW LOCATION TEXT|
  ---------------------------*/

  HintText LightArrowLocation = HintText::LightArrow({
                     //obscure text
                     Text{"Ha ha ha... You'll never beat me by reflecting my lightning bolts and unleashing the arrows from ", "Ha ha ha... Pauvre fou! Tu ne pourras jamais me vaincre sans les flèches que j'ai caché dans ", /*spanish*/"Ja, ja, ja... Nunca me derrotarás reflejando mis esferas de energía y desplegando las flechas de luz de "},
  });

  HintText YourPocket = HintText::Exclude({
                     //obscure text
                     Text{"your pocket", "tes poches", /*spanish*/""},
  });

  /*--------------------------
  |      GANON LINE TEXT     |
  ---------------------------*/

  HintText GanonLine01 = HintText::GanonLine({
                     //obscure text
                     Text{"Oh! It's @.&I was expecting someone called Sheik. Do you know what happened to them?", "Ah, c'est @.&J'attendais un certain Sheik. Tu sais ce qui lui est arrivé?", /*spanish*/"¡Oh! Pero si es @.&Estaba esperando a alguien llamado Sheik. ¿Sabes qué puede haberle pasado?"},
  });

  HintText GanonLine02 = HintText::GanonLine({
                     //obscure text
                     Text{"I knew I shouldn't have put the key on the other side of my door.", "J'aurais dû garder la clé ici. Hélas...", /*spanish*/"Sabía que no tendría que haber dejado la llave al otro lado de la puerta."},
  });

  HintText GanonLine03 = HintText::GanonLine({
                     //obscure text
                     Text{"Looks like it's time for a round of tennis.", "C'est l'heure de jouer au tennis.", /*spanish*/"Parece que es hora de una partidita de tenis."},
  });

  HintText GanonLine04 = HintText::GanonLine({
                     //obscure text
                     Text{"You'll never deflect my bolts of energy with your sword, then shoot me with those Light Arrows you happen to have.", "Ne perds pas ton temps à frapper mes éclairs d'énergie avec ton épée et me tirer avec tes flèches de Lumière!", /*spanish*/"Nunca reflejarás mis esferas de energía con tu espada, para después dispararme con las flechas de luz que tendrás."},
  });

  HintText GanonLine05 = HintText::GanonLine({
                     //obscure text
                     Text{"Why did I leave my trident back in the desert?", "Sale bêtise... Et j'ai oublié mon trident dans le désert!", /*spanish*/"¿Por qué me habré dejado el tridente en el desierto?"},
  });

  HintText GanonLine06 = HintText::GanonLine({
                     //obscure text
                     Text{"Zelda is probably going to do something stupid, like send you back to your own timeline.^So this is quite meaningless. Do you really want to save this moron?", "Même si je suis vaincu... Zelda te renverra dans ton ère, et je reviendrai conquérir!^Telle est la prophécie d'Hyrule Historia!", /*spanish*/"Seguro que Zelda trata de hacer alguna tontería, como enviarte de vuelta a tu línea temporal.^No tiene ningún sentido alguno. ¿De verdad quieres salvar a esa tonta?"},
  });

  HintText GanonLine07 = HintText::GanonLine({
                     //obscure text
                     Text{"What about Zelda makes you think she'd be a better ruler than I?^I saved Lon Lon Ranch,&fed the hungry,&and my castle floats.", "Zelda ne sera jamais un meilleur monarque que moi!^J'ai un château volant, mes sujets sont des belles amazones... et mes Moblins sont clairement plus puissants que jamais!", /*spanish*/"¿Qué te hace pensar que Zelda gobierna mejor que yo?^Yo he salvado el Rancho Lon Lon,&he alimentado a los hambrientos&y hasta hago que mi castillo flote."},
  });

  HintText GanonLine08 = HintText::GanonLine({
                     //obscure text
                     Text{"I've learned this spell,&it's really neat,&I'll keep it later&for your treat!", "Gamin, ton destin achève,&sous mon sort tu périras!&Cette partie ne fut pas brève,&et cette mort, tu subiras!...^... Bordel, je suis roi, pas poète.", /*spanish*/"Acabo de aprender este hechizo,&y la verdad es que es&de lo más bueno. ¡Te lo&reservaré como sorpresa!"},
  });

  HintText GanonLine09 = HintText::GanonLine({
                     //obscure text
                     Text{"Many tricks are up my sleeve,&to save yourself&you'd better leave!", "Sale petit garnement,&tu fais erreur!&C'est maintenant que marque&ta dernière heure!", /*spanish*/"Tengo muchos trucos a mi espalda&, si no quieres morir,&¡deshazte de esa hada!"},
  });

  HintText GanonLine10 = HintText::GanonLine({
                     //obscure text
                     Text{"After what you did to Koholint Island, how can you call me the bad guy?", "J'admire ce que tu as fait à l'Île Koholint... Toi et moi, nous devrions faire équipe!", /*spanish*/"Después de lo que le hiciste a la Isla Koholint, ¿cómo te atreves a llamarme malvado?"},
  });

  HintText GanonLine11 = HintText::GanonLine({
                     //obscure text
                     Text{"Today, let's begin down&'The Hero is Defeated' timeline.", "Si tu me vaincs, Hyrule sera englouti... mais si tu meurs, on aura A Link to the Past, le meilleur opus de la série!", /*spanish*/"Hoy daremos lugar a la&línea temporal del Héroe Derrotado."},
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
  std::array<HintText*, 12> ganonLines = {
    &GanonLine01,
    &GanonLine02,
    &GanonLine03,
    &GanonLine04,
    &GanonLine05,
    &GanonLine06,
    &GanonLine07,
    &GanonLine08,
    &GanonLine09,
    &GanonLine10,
    &GanonLine11,
  };
} //namespace Hints
