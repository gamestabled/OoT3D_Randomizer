#include "hint_list.hpp"

#include <array>

//Big thanks to Lioncache, Gabyelnuevo, Danius88, and Charade for their translations!

//Text is {english, french, spanish}

// there are special characters that are read for certain in game commands:
// ^ is a box break
// & is a new line
// @ will print the player name
// surrounding text with '#' will make it a different color
// - OoT Randomizer

static std::array<HintText, KEY_ENUM_MAX> hintTable;

void HintTable_Init() {
    /*--------------------------
    |       GENERAL TEXT       |
    ---------------------------*/
    hintTable[NONE]            = HintText::Exclude({Text{"No Hint","",""}});
    hintTable[PREFIX]          = HintText::Exclude({Text{"They say that ",              /*french*/"", /*spanish*/"Según dicen, "}});
    hintTable[WAY_OF_THE_HERO] = HintText::Exclude({Text{" is on the way of the hero.", /*french*/"", /*spanish*/" aguarda en la senda del héroe."}});
    hintTable[PLUNDERING]      = HintText::Exclude({Text{"plundering ",                 /*french*/"", /*spanish*/"vagar por "}});
    hintTable[FOOLISH]         = HintText::Exclude({Text{" is a foolish choice.",       /*french*/"", /*spanish*/" no es una sabia decisión."}});


    /*--------------------------
    |      ITEM HINT TEXT      |
    ---------------------------*/
    hintTable[KOKIRI_SWORD] = HintText::Item({
                       //obscure text
                       Text{"a butter knife",    /*french*/"", /*spanish*/"un ágil puñal"},
                       Text{"a starter slasher", /*french*/"", /*spanish*/"una hoja de principiantes"},
                       Text{"a switchblade",     /*french*/"", /*spanish*/"un raudo cortador"},
                     },
                       //clear text
                       Text{"the Kokiri Sword", /*french*/"", /*spanish*/"la Espada Kokiri"}
    );

    hintTable[MASTER_SWORD] = HintText::Item({
                       //obscure text
                       Text{"evil's bane",        /*french*/"", /*spanish*/"la destructora del mal"},
                       Text{"a seven year limbo", /*french*/"", /*spanish*/"unos siete años de espera"},
                     },
                       //clear text
                       Text{"the Master Sword", /*french*/"", /*spanish*/"la Espada Maestra"}
    );

    hintTable[GIANTS_KNIFE] = HintText::Item({
                       //obscure text
                       Text{"a fragile blade",     /*french*/"", /*spanish*/"una frágil hoja"},
                       Text{"a breakable cleaver", /*french*/"", /*spanish*/"un rompible acero"},
                     },
                       //clear text
                       Text{"the Giant's Knife", /*french*/"", /*spanish*/"la daga gigante"}
    );

    hintTable[BIGGORON_SWORD] = HintText::Item({
                       //obscure text
                       Text{"the biggest blade",  /*french*/"", /*spanish*/"el mayor mandoble"},
                       Text{"a colossal cleaver", /*french*/"", /*spanish*/"un estoque colosal"},
                     },
                       //clear text
                       Text{"the Biggoron Sword", /*french*/"", /*spanish*/"la Espada de Biggoron"}
    );

    hintTable[DEKU_SHIELD] = HintText::Item({
                       //obscure text
                       Text{"a wooden ward",      /*french*/"", /*spanish*/"una protección forestal"},
                       Text{"a burnable barrier", /*french*/"", /*spanish*/"una barrera quemable"},
                     },
                       //clear text
                       Text{"a Deku Shield", /*french*/"", /*spanish*/"un escudo deku"}
    );

    hintTable[HYLIAN_SHIELD] = HintText::Item({
                       //obscure text
                       Text{"a steel safeguard",      /*french*/"", /*spanish*/"un protección de acero"},
                       Text{"Like Like's metal meal", /*french*/"", /*spanish*/"un metálico plato de Like Like"},
                     },
                       //clear text
                       Text{"a Hylian Shield", /*french*/"", /*spanish*/"un escudo hyliano"}
    );

    hintTable[MIRROR_SHIELD] = HintText::Item({
                       //obscure text
                       Text{"a reflective rampart", /*french*/"", /*spanish*/"una muralla reflectora"},
                       Text{"Medusa's weakness",    /*french*/"", /*spanish*/"la debilidad de Medusa"},
                       Text{"a silvered surface",   /*french*/"", /*spanish*/"una superficie plateada"},
                     },
                       //clear text
                       Text{"the Mirror Shield", /*french*/"", /*spanish*/"el escudo espejo"}
    );

    hintTable[GORON_TUNIC] = HintText::Item({
                       //obscure text
                       Text{"ruby robes",       /*french*/"", /*spanish*/"una vestimenta rubí"},
                       Text{"fireproof fabric", /*french*/"", /*spanish*/"una ignífuga prenda"},
                       Text{"cooking clothes",  /*french*/"", /*spanish*/"unos abrasantes ropajes"},
                     },
                       //clear text
                       Text{"a Goron Tunic", /*french*/"", /*spanish*/"un sayo goron"}
    );

    hintTable[ZORA_TUNIC] = HintText::Item({
                       //obscure text
                       Text{"a sapphire suit", /*french*/"", /*spanish*/"una vestidura zafiro"},
                       Text{"scuba gear",      /*french*/"", /*spanish*/"un traje de buceo"},
                       Text{"a swimsuit",      /*french*/"", /*spanish*/"un bañador"},
                     },
                       //clear text
                       Text{"a Zora Tunic", /*french*/"", /*spanish*/"un sayo zora"}
    );

    hintTable[IRON_BOOTS] = HintText::Item({
                       //obscure text
                       Text{"sink shoes",   /*french*/"", /*spanish*/"un calzado de las profundidades"},
                       Text{"clank cleats", /*french*/"", /*spanish*/"unas botas férreas"},
                     },
                       //clear text
                       Text{"the Iron Boots", /*french*/"", /*spanish*/"las botas de hierro"}
    );

    hintTable[HOVER_BOOTS] = HintText::Item({
                       //obscure text
                       Text{"butter boots",    /*french*/"", /*spanish*/"unas suelas resvaladizas"},
                       Text{"sacred slippers", /*french*/"", /*spanish*/"unos escurridizos botines"},
                       Text{"spacewalkers",    /*french*/"", /*spanish*/"un calzado antigravitatorio"},
                     },
                       //clear text
                       Text{"the Hover Boots", /*french*/"", /*spanish*/"las botas voladoras"}
    );


    hintTable[ZELDAS_LETTER] = HintText::Item({
                       //obscure text
                       Text{"an autograph",     /*french*/"", /*spanish*/"un autógrafo"},
                       Text{"royal stationery", /*french*/"", /*spanish*/"un escrito real"},
                       Text{"royal snail mail", /*french*/"", /*spanish*/"correo de la realeza"},
                     },
                       //clear text
                       Text{"Zelda's Letter", /*french*/"", /*spanish*/"la carta de Zelda"}
    );

    hintTable[WEIRD_EGG] = HintText::Item({
                       //obscure text
                       Text{"a chicken dilemma", /*french*/"", /*spanish*/"el dilema de la gallina"},
                     },
                       //clear text
                       Text{"the Weird Egg", /*french*/"", /*spanish*/"el huevo extraño"}
    );

    hintTable[BOOMERANG] = HintText::Item({
                       //obscure text
                       Text{"a banana",       /*french*/"", /*spanish*/"un plátano"},
                       Text{"a stun stick",   /*french*/"", /*spanish*/"un palo aturdidor"},
                       Text{"a yellow angle", /*french*/"", /*spanish*/"un ángulo amarillo"},
                     },
                       //clear text
                       Text{"the Boomerang", /*french*/"", /*spanish*/"el bumerán"}
    );

    hintTable[LENS_OF_TRUTH] = HintText::Item({
                       //obscure text
                       Text{"a lie detector",     /*french*/"", /*spanish*/"el detector de ilusiones"},
                       Text{"a ghost tracker",    /*french*/"", /*spanish*/"el rastreador paranormal"},
                       Text{"true sight",         /*french*/"", /*spanish*/"el ojo que todo ve"},
                       Text{"a detective's tool", /*french*/"", /*spanish*/"la revelación verdadera"},
                     },
                       //clear text
                       Text{"the Lens of Truth", /*french*/"", /*spanish*/"la Lupa de la Verdad"}
    );

    hintTable[MEGATON_HAMMER] = HintText::Item({
                       //obscure text
                       Text{"the dragon smasher", /*french*/"", /*spanish*/"un destructor de dragones"},
                       Text{"the metal mallet",   /*french*/"", /*spanish*/"un mazo de metal"},
                       Text{"the heavy hitter",   /*french*/"", /*spanish*/"un machacador"},
                     },
                       //clear text
                       Text{"the Megaton Hammer", /*french*/"", /*spanish*/"el martillo Megatón"}
    );

    hintTable[SHARD_OF_AGONY] = HintText::Item({
                       //obscure text
                       Text{"the shake shard", /*french*/"", /*spanish*/"el fragmento tintineante"},
                       Text{"a blue alarm",    /*french*/"", /*spanish*/"una azul alarma"},
                     },
                       //clear text
                       Text{"the Shard of Agony", /*french*/"", /*spanish*/"la Piedra de la Agonía"}
    );

    hintTable[DINS_FIRE] = HintText::Item({
                       //obscure text
                       Text{"an inferno",  /*french*/"", /*spanish*/"un incendio"},
                       Text{"a heat wave", /*french*/"", /*spanish*/"una onda de calor"},
                       Text{"a red ball",  /*french*/"", /*spanish*/"una roja esfera"},
                     },
                       //clear text
                       Text{"Din's Fire", /*french*/"", /*spanish*/"el Fuego de Din"}
    );

    hintTable[FARORES_WIND] = HintText::Item({
                       //obscure text
                       Text{"teleportation",     /*french*/"", /*spanish*/"el teletransporte"},
                       Text{"a relocation rune", /*french*/"", /*spanish*/"una runa de transporte"},
                       Text{"a green ball",      /*french*/"", /*spanish*/"una verde esfera"},
                     },
                       //clear text
                       Text{"Farore's Wind", /*french*/"", /*spanish*/"el Viento de Farore"}
    );

    hintTable[NAYRUS_LOVE] = HintText::Item({
                       //obscure text
                       Text{"a safe space",        /*french*/"", /*spanish*/"un seguro espacio"},
                       Text{"an impregnable aura", /*french*/"", /*spanish*/"una inexpugnable aura"},
                       Text{"a blue barrier",      /*french*/"", /*spanish*/"una barrera azul"},
                     },
                       //clear text
                       Text{"Nayru's Love", /*french*/"", /*spanish*/"el Amor de Nayru"}
    );

    hintTable[FIRE_ARROWS] = HintText::Item({
                       //obscure text
                       Text{"the furnace firearm" , /*french*/"", /*spanish*/"el aguijón ardiente"},
                       Text{"the burning bolts",    /*french*/"", /*spanish*/"las puntas candentes"},
                       Text{"a magma missile",      /*french*/"", /*spanish*/"el misil abrasador"},
                     },
                       //clear text
                       Text{"the Fire Arrows", /*french*/"", /*spanish*/"las flechas de fuego"}
    );

    hintTable[ICE_ARROWS] = HintText::Item({
                       //obscure text
                       Text{"the refrigerator rocket", /*french*/"", /*spanish*/"el misil congelado"},
                       Text{"the frostbite bolts",     /*french*/"", /*spanish*/"las puntas heladas"},
                       Text{"an iceberg maker",        /*french*/"", /*spanish*/"el control de escarcha"},
                     },
                       //clear text
                       Text{"the Ice Arrows", /*french*/"", /*spanish*/"las flechas de hielo"}
    );

    hintTable[LIGHT_ARROWS] = HintText::Item({
                       //obscure text
                       Text{"the shining shot",      /*french*/"", /*spanish*/"el haz de luz"},
                       Text{"the luminous launcher", /*french*/"", /*spanish*/"el disparo luminoso"},
                       Text{"Ganondorf's bane",      /*french*/"", /*spanish*/"el destructor de Ganondorf"},
                       Text{"the lighting bolts",    /*french*/"", /*spanish*/"las puntas resplandecientes"},
                     },
                       //clear text
                       Text{"the Light Arrows", /*french*/"", /*spanish*/"las flechas de luz"}
    );

    hintTable[GERUDO_TOKEN] = HintText::Item({
                       //obscure text
                       Text{"a girl club membership", /*french*/"", /*spanish*/"una fémina membresía"},
                       Text{"a desert tribe's pass",  /*french*/"", /*spanish*/"el vale de la tribu del desierto"},
                     },
                       //clear text
                       Text{"the Gerudo Token", /*french*/"", /*spanish*/"el pase de socio gerudo"}
    );

    hintTable[MAGIC_BEAN] = HintText::Item({
                       //obscure text
                       Text{"a wizardly legume", /*french*/"", /*spanish*/"una legumbre mágica"},
                     },
                       //clear text
                       Text{"a Magic Bean", /*french*/"", /*spanish*/"una judía mágica"}
    );

    hintTable[MAGIC_BEAN_PACK] = HintText::Item({
                       //obscure text
                       Text{"wizardly legumes", /*french*/"", /*spanish*/"unas legumbres mágicas"},
                     },
                       //clear text
                       Text{"Magic Beans", /*french*/"", /*spanish*/"unas judías mágicas"}
    );

    hintTable[DOUBLE_DEFENSE] = HintText::Item({
                       //obscure text
                       Text{"a white outline",   /*french*/"", /*spanish*/"un contorno blanco"},
                       Text{"damage decrease",   /*french*/"", /*spanish*/"una reducción de daño"},
                       Text{"strengthened love", /*french*/"", /*spanish*/"un amor fortalecido"},
                     },
                       //clear text
                       Text{"Double Defense", /*french*/"", /*spanish*/"la doble defensa"}
    );

    hintTable[GOLD_SKULLTULA_TOKEN] = HintText::Item({
                       //obscure text
                       Text{"proof of destruction",   /*french*/"", /*spanish*/"una prueba de la destrucción"},
                       Text{"an arachnid chip",       /*french*/"", /*spanish*/"una figura arácnida"},
                       Text{"spider remains",         /*french*/"", /*spanish*/"los restos de una araña"},
                       Text{"one percent of a curse", /*french*/"", /*spanish*/"un uno por ciento de una maldición"},
                     },
                       //clear text
                       Text{"a Gold Skulltula Token", /*french*/"", /*spanish*/"un símbolo de skulltula dorada"}
    );

    hintTable[POCKET_EGG] = HintText::Item({
                       //obscure text
                       Text{"a Cucco container",   /*french*/"", /*spanish*/"contenedor de cuco"},
                       Text{"a Cucco, eventually", /*french*/"", /*spanish*/"un futuro cuco"},
                       Text{"a fowl youth",        /*french*/"", /*spanish*/"una dulce juventud"},
                     },
                       //clear text
                       Text{"the Pocket Egg", /*french*/"", /*spanish*/"el huevo de bolsillo"}
    );

    hintTable[POCKET_CUCCO] = HintText::Item({
                       //obscure text
                       Text{"a little clucker", /*french*/"", /*spanish*/"un pequeñajo pollito"},
                     },
                       //clear text
                       Text{"the Pocket Cucco", /*french*/"", /*spanish*/"el cuco de bolsillo"}
    );

    hintTable[COJIRO] = HintText::Item({
                       //obscure text
                       Text{"a cerulean capon", /*french*/"", /*spanish*/"un cerúleo capón"},
                     },
                       //clear text
                       Text{"Cojiro", /*french*/"", /*spanish*/"Cojiro"}
    );

    hintTable[ODD_MUSHROOM] = HintText::Item({
                       //obscure text
                       Text{"a powder ingredient", /*french*/"", /*spanish*/"un oloroso ingrediente"},
                     },
                       //clear text
                       Text{"an Odd Mushroom", /*french*/"", /*spanish*/"una seta rara"}
    );

    hintTable[ODD_POULTICE] = HintText::Item({
                       //obscure text
                       Text{"Granny's goodies", /*french*/"", /*spanish*/"la especialidad de la abuela"},
                     },
                       //clear text
                       Text{"an Odd Potion", /*french*/"", /*spanish*/"una medicina rara"}
    );

    hintTable[POACHERS_SAW] = HintText::Item({
                       //obscure text
                       Text{"a tree killer", /*french*/"", /*spanish*/"un destructor de árboles"},
                     },
                       //clear text
                       Text{"the Poacher's Saw", /*french*/"", /*spanish*/"la sierra del furtivo"}
    );

    hintTable[BROKEN_SWORD] = HintText::Item({
                       //obscure text
                       Text{"a shattered slicer", /*french*/"", /*spanish*/"una rebanadora rota"},
                     },
                       //clear text
                       Text{"the Broken Sword", /*french*/"", /*spanish*/"la espada goron rota"}
    );

    hintTable[PRESCRIPTION] = HintText::Item({
                       //obscure text
                       Text{"a pill pamphlet", /*french*/"", /*spanish*/"un instructivo medicinal"},
                       Text{"a doctor's note", /*french*/"", /*spanish*/"unas notas del doctor"},
                     },
                       //clear text
                       Text{"the Prescription", /*french*/"", /*spanish*/"la receta"}
    );

    hintTable[EYEBALL_FROG] = HintText::Item({
                       //obscure text
                       Text{"a perceiving polliwog", /*french*/"", /*spanish*/"un variopinto batracio"},
                     },
                       //clear text
                       Text{"the Eyeball Frog", /*french*/"", /*spanish*/"la rana de ojos saltones"}
    );

    hintTable[EYEDROPS] = HintText::Item({
                       //obscure text
                       Text{"a vision vial", /*french*/"", /*spanish*/"un remedio para la vista"},
                     },
                       //clear text
                       Text{"the Eyedrops", /*french*/"", /*spanish*/"las supergotas oculares"}
    );

    hintTable[CLAIM_CHECK] = HintText::Item({
                       //obscure text
                       Text{"a three day wait", /*french*/"", /*spanish*/"unos tres días de espera"},
                     },
                       //clear text
                       Text{"the Claim Check", /*french*/"", /*spanish*/"el albarán"}
    );

    hintTable[PROGRESSIVE_HOOKSHOT] = HintText::Item({
                       //obscure text
                       Text{"Dampé's keepsake", /*french*/"", /*spanish*/"un recuerdo de Dampé"},
                       Text{"the Grapple Beam", /*french*/"", /*spanish*/"una liana de agarre"},
                       Text{"the BOING! chain", /*french*/"", /*spanish*/"una cadena retráctil"},
                     },
                       //clear text
                       Text{"a Hookshot", /*french*/"", /*spanish*/"un gancho"}
    );

    hintTable[PROGRESSIVE_STRENGTH] = HintText::Item({
                       //obscure text
                       Text{"power gloves",    /*french*/"", /*spanish*/"unos poderosos guanteletes"},
                       Text{"metal mittens",   /*french*/"", /*spanish*/"unas manoplas metálicas"},
                       Text{"the heavy lifty", /*french*/"", /*spanish*/"un levantamiento pesado"},
                     },
                       //clear text
                       Text{"a Strength Upgrade", /*french*/"", /*spanish*/"un aumento de fuerza"}
    );

    hintTable[PROGRESSIVE_BOMB_BAG] = HintText::Item({
                       //obscure text
                       Text{"an explosive container", /*french*/"", /*spanish*/"un recipiente explosivo"},
                       Text{"a blast bag", /*french*/"", /*spanish*/"un zurrón de estallidos"},
                     },
                       //clear text
                       Text{"a Bomb Bag", /*french*/"", /*spanish*/"un saco de bombas"}
    );

    hintTable[PROGRESSIVE_BOW] = HintText::Item({
                       //obscure text
                       Text{"an archery enabler",     /*french*/"", /*spanish*/"un tiro al blanco"},
                       Text{"a danger dart launcher", /*french*/"", /*spanish*/"un peligroso lanzadardos"},
                     },
                       //clear text
                       Text{"a Bow", /*french*/"", /*spanish*/"un arco"}
    );

    hintTable[PROGRESSIVE_SLINGSHOT] = HintText::Item({
                       //obscure text
                       Text{"a seed shooter",     /*french*/"", /*spanish*/"un lanzasemillas"},
                       Text{"a rubberband",       /*french*/"", /*spanish*/"una resortera"},
                       Text{"a child's catapult", /*french*/"", /*spanish*/"una catapulta infantil"},
                     },
                       //clear text
                       Text{"a Slingshot", /*french*/"", /*spanish*/"un tirachinas"}
    );

    hintTable[PROGRESSIVE_WALLET] = HintText::Item({
                       //obscure text
                       Text{"a mo' money holder", /*french*/"", /*spanish*/"una cartera de dinero"},
                       Text{"a gem purse",        /*french*/"", /*spanish*/"un zurrón de gemas"},
                       Text{"a portable bank",    /*french*/"", /*spanish*/"un banco portable"},
                     },
                       //clear text
                       Text{"a Wallet", /*french*/"", /*spanish*/"una bolsa de rupias"}
    );

    hintTable[PROGRESSIVE_SCALE] = HintText::Item({
                       //obscure text
                       Text{"a deeper dive",   /*french*/"", /*spanish*/"un profundo buceo"},
                       Text{"a piece of Zora", /*french*/"", /*spanish*/"un fragmento de Zora"},
                     },
                       //clear text
                       Text{"a Zora Scale", /*french*/"", /*spanish*/"una escama Zora"}
    );

    hintTable[PROGRESSIVE_NUT_UPGRADE] = HintText::Item({
                       //obscure text
                       Text{"more nuts",         /*french*/"", /*spanish*/"más semillas de nogal"},
                       Text{"flashbang storage", /*french*/"", /*spanish*/"más frutos de aturdimiento"},
                     },
                       //clear text
                       Text{"Deku Nut Capacity", /*french*/"", /*spanish*/"mayor capacidad de nueces deku"}
    );

    hintTable[PROGRESSIVE_STICK_UPGRADE] = HintText::Item({
                       //obscure text
                       Text{"a lumber rack",        /*french*/"", /*spanish*/"más bastones"},
                       Text{"more flammable twigs", /*french*/"", /*spanish*/"más varas"},
                     },
                       //clear text
                       Text{"Deku Stick Capacity", /*french*/"", /*spanish*/"mayor capacidad de palos deku"}
    );

    hintTable[PROGRESSIVE_MAGIC_METER] = HintText::Item({
                       //obscure text
                       Text{"mystic training",    /*french*/"", /*spanish*/"una maestría mística"},
                       Text{"pixie dust",         /*french*/"", /*spanish*/"un polvo de hada"},
                       Text{"a green rectangle",  /*french*/"", /*spanish*/"una verduzca vasija"},
                     },
                       //clear text
                       Text{"a Magic Meter", /*french*/"", /*spanish*/"una barra de magia"}
    );

    hintTable[PROGRESSIVE_OCARINA] = HintText::Item({
                       //obscure text
                       Text{"a flute",       /*french*/"", /*spanish*/"una flauta"},
                       Text{"a music maker", /*french*/"", /*spanish*/"un instrumento"},
                     },
                       //clear text
                       Text{"an Ocarina", /*french*/"", /*spanish*/"una ocarina"}
    );

    hintTable[PROGRESSIVE_BOMBCHUS] = HintText::Item({
                       //obscure text
                       Text{"mice bombs",     /*french*/"", /*spanish*/"unas bombas roedoras"},
                       Text{"proximity mice", /*french*/"", /*spanish*/"unos explosivos ratoncitos"},
                       Text{"wall crawlers",  /*french*/"", /*spanish*/"unos trepaparedes"},
                       Text{"trail blazers",  /*french*/"", /*spanish*/"unas ratas propulsadas"},
                     },
                       //clear text
                       Text{"Bombchus", /*french*/"", /*spanish*/"unos bombchus"}
    );

    hintTable[EMPTY_BOTTLE] = HintText::Item({
                       //obscure text
                       Text{"a glass container", /*french*/"", /*spanish*/"un recipiente de cristal"},
                       Text{"an empty jar",      /*french*/"", /*spanish*/"un frasco vacío"},
                       Text{"encased air",       /*french*/"", /*spanish*/"aire a presión"},
                     },
                       //clear text
                       Text{"a Bottle", /*french*/"", /*spanish*/"una botella"}
    );

    hintTable[BOTTLE_WITH_MILK] = HintText::Item({
                       //obscure text
                       Text{"cow juice",          /*french*/"", /*spanish*/"un jugo de vaca"},
                       Text{"a white liquid",     /*french*/"", /*spanish*/"una bebida nutritiva"},
                       Text{"a baby's breakfast", /*french*/"", /*spanish*/"un trago para bebés"},
                     },
                       //clear text
                       Text{"a Milk Bottle", /*french*/"", /*spanish*/"una botella de leche"}
    );

    hintTable[BOTTLE_WITH_RED_POTION] = HintText::Item({
                       //obscure text
                       Text{"a vitality vial", /*french*/"", /*spanish*/"una pócima vitalicia"},
                       Text{"a red liquid",    /*french*/"", /*spanish*/"un remedio rojizo"},
                     },
                       //clear text
                       Text{"a Red Potion Bottle", /*french*/"", /*spanish*/"una botella de poción roja"}
    );

    hintTable[BOTTLE_WITH_GREEN_POTION] = HintText::Item({
                       //obscure text
                       Text{"a magic mixture", /*french*/"", /*spanish*/"un potingue mágico"},
                       Text{"a green liquid",  /*french*/"", /*spanish*/"un remedio verduzco"},
                     },
                       //clear text
                       Text{"a Green Potion Bottle", /*french*/"", /*spanish*/"una botella de poción verde"}
    );

    hintTable[BOTTLE_WITH_BLUE_POTION] = HintText::Item({
                       //obscure text
                       Text{"an ailment antidote", /*french*/"", /*spanish*/"un antídoto de dolencias"},
                       Text{"a blue liquid",       /*french*/"", /*spanish*/"un remedio índigo"},
                     },
                       //clear text
                       Text{"a Blue Potion Bottle", /*french*/"", /*spanish*/"una botella de poción azul"}
    );

    hintTable[BOTTLE_WITH_FAIRY] = HintText::Item({
                       //obscure text
                       Text{"an imprisoned fairy", /*french*/"", /*spanish*/"una hada atrapada"},
                       Text{"an extra life",       /*french*/"", /*spanish*/"una oportunidad más"},
                       Text{"Navi's cousin",       /*french*/"", /*spanish*/"la prima de Navi"},
                     },
                       //clear text
                       Text{"a Fairy Bottle", /*french*/"", /*spanish*/"un hada embotellada"}
    );

    hintTable[BOTTLE_WITH_FISH] = HintText::Item({
                       //obscure text
                       Text{"an aquarium",     /*french*/"", /*spanish*/"un escamado ser"},
                       Text{"a deity's snack", /*french*/"", /*spanish*/"el tentempié de cierta deidad"},
                     },
                       //clear text
                       Text{"a Fish Bottle", /*french*/"", /*spanish*/"un pez embotellado"}
    );

    hintTable[BOTTLE_WITH_BLUE_FIRE] = HintText::Item({
                       //obscure text
                       Text{"a conflagration canteen", /*french*/"", /*spanish*/"un pequeño incendio"},
                       Text{"an icemelt jar",          /*french*/"", /*spanish*/"unas brasas enfrascadas"},
                     },
                       //clear text
                       Text{"a Blue Fire Bottle", /*french*/"", /*spanish*/"una botella de fuego azul"}
    );

    hintTable[BOTTLE_WITH_BUGS] = HintText::Item({
                       //obscure text
                       Text{"an insectarium",    /*french*/"", /*spanish*/"un insectario"},
                       Text{"Skulltula finders", /*french*/"", /*spanish*/"unos rastreadores de skulltulas"},
                     },
                       //clear text
                       Text{"a Bug Bottle", /*french*/"", /*spanish*/"una botella con insectos"}
    );

    hintTable[BOTTLE_WITH_POE] = HintText::Item({
                       //obscure text
                       Text{"a spooky ghost",    /*french*/"", /*spanish*/"una espantoso espectro"},
                       Text{"a face in the jar", /*french*/"", /*spanish*/"una cara embotellada"},
                     },
                       //clear text
                       Text{"a Poe Bottle", /*french*/"", /*spanish*/"un Poe embotellado"}
    );

    hintTable[BOTTLE_WITH_BIG_POE] = HintText::Item({
                       //obscure text
                       Text{"the spookiest ghost", /*french*/"", /*spanish*/"el espectro más espeluznante"},
                       Text{"a sidequest spirit",  /*french*/"", /*spanish*/"un gran espíritu"},
                     },
                       //clear text
                       Text{"a Big Poe Bottle", /*french*/"", /*spanish*/"un Gran Poe embotellado"}
    );

    hintTable[RUTOS_LETTER] = HintText::Item({
                       //obscure text
                       Text{"a call for help",      /*french*/"", /*spanish*/"una llamada de auxilio"},
                       Text{"the note that Mweeps", /*french*/"", /*spanish*/"un mensaje de ayuda"},
                       Text{"an SOS call",          /*french*/"", /*spanish*/"una nota de socorro"},
                       Text{"a fishy stationery",   /*french*/"", /*spanish*/"un escrito urgente"},
                     },
                       //clear text
                       Text{"Ruto's Letter", /*french*/"", /*spanish*/"la carta de Ruto"}
    );

    hintTable[ZELDAS_LULLABY] = HintText::Item({
                       //obscure text
                       Text{"a song of royal slumber", /*french*/"", /*spanish*/"la canción real"},
                       Text{"a triforce tune",         /*french*/"", /*spanish*/"la melodía de la trifuerza"},
                     },
                       //clear text
                       Text{"Zelda's Lullaby", /*french*/"", /*spanish*/"la Nana de Zelda"}
    );

    hintTable[EPONAS_SONG] = HintText::Item({
                       //obscure text
                       Text{"an equestrian etude", /*french*/"", /*spanish*/"una copla ecuestre"},
                       Text{"Malon's melody",      /*french*/"", /*spanish*/"la sonata de Malon"},
                       Text{"a ranch song",        /*french*/"", /*spanish*/"una canción rupestre"},
                     },
                       //clear text
                       Text{"Epona's Song", /*french*/"", /*spanish*/"la Canción de Epona"}
    );

    hintTable[SARIAS_SONG] = HintText::Item({
                       //obscure text
                       Text{"a song of dancing Gorons", /*french*/"", /*spanish*/"la pegadiza tonada para Gorons"},
                       Text{"Saria's phone number",     /*french*/"", /*spanish*/"la llamada de Saria"},
                     },
                       //clear text
                       Text{"Saria's Song", /*french*/"", /*spanish*/"la Canción de Saria"}
    );

    hintTable[SUNS_SONG] = HintText::Item({
                       //obscure text
                       Text{"Sunny Day",         /*french*/"", /*spanish*/"un día soleado"},
                       Text{"the ReDead's bane", /*french*/"", /*spanish*/"la destructora de Redeads"},
                       Text{"the Gibdo's bane",  /*french*/"", /*spanish*/"la destructora de Gibdos"},
                     },
                       //clear text
                       Text{"the Sun's Song", /*french*/"", /*spanish*/"la Canción del Sol"}
    );

    hintTable[SONG_OF_TIME] = HintText::Item({
                       //obscure text
                       Text{"a song 7 years long", /*french*/"", /*spanish*/"la setenada canción"},
                       Text{"the tune of ages",    /*french*/"", /*spanish*/"la melodía eónica"},
                     },
                       //clear text
                       Text{"the Song of Time", /*french*/"", /*spanish*/"la Canción del tiempo"}
    );

    hintTable[SONG_OF_STORMS] = HintText::Item({
                       //obscure text
                       Text{"Rain Dance",            /*french*/"", /*spanish*/"la danza de la lluvia"},
                       Text{"a thunderstorm tune",   /*french*/"", /*spanish*/"una sonata tormentosa"},
                       Text{"windmill acceleration", /*french*/"", /*spanish*/"el arranque de molinos"},
                     },
                       //clear text
                       Text{"the Song of Storms", /*french*/"", /*spanish*/"la Canción de la Tormenta"}
    );

    hintTable[MINUET_OF_FOREST] = HintText::Item({
                       //obscure text
                       Text{"the song of tall trees", /*french*/"", /*spanish*/"la canción de las copas"},
                       Text{"an arboreal anthem",     /*french*/"", /*spanish*/"el himno forestal"},
                       Text{"a green spark trail",    /*french*/"", /*spanish*/"el sendero esmeralda"},
                     },
                       //clear text
                       Text{"the Minuet of Forest", /*french*/"", /*spanish*/"el Minueto del bosque"}
    );

    hintTable[BOLERO_OF_FIRE] = HintText::Item({
                       //obscure text
                       Text{"a song of lethal lava", /*french*/"", /*spanish*/"la canción de la lava"},
                       Text{"a red spark trail",     /*french*/"", /*spanish*/"el sendero carmesí"},
                       Text{"a volcanic verse",      /*french*/"", /*spanish*/"el verso volcánico"},
                     },
                       //clear text
                       Text{"the Bolero of Fire", /*french*/"", /*spanish*/"el Bolero del fuego"}
    );

    hintTable[SERENADE_OF_WATER] = HintText::Item({
                       //obscure text
                       Text{"a song of a damp ditch", /*french*/"", /*spanish*/"la canción del estanque"},
                       Text{"a blue spark trail",     /*french*/"", /*spanish*/"el sendero azur"},
                       Text{"the lake's lyric",       /*french*/"", /*spanish*/"la letra del lago"},
                     },
                       //clear text
                       Text{"the Serenade of Water", /*french*/"", /*spanish*/"la Serenata del agua"}
    );

    hintTable[REQUIEM_OF_SPIRIT] = HintText::Item({
                       //obscure text
                       Text{"a song of sandy statues", /*french*/"", /*spanish*/"la canción de estatuas areniscas"},
                       Text{"an orange spark trail",   /*french*/"", /*spanish*/"el sendero ámbar"},
                       Text{"the desert ditty",        /*french*/"", /*spanish*/"la estrofa del desierto"},
                     },
                       //clear text
                       Text{"the Requiem of Spirit", /*french*/"", /*spanish*/"el Réquiem del espíritu"}
    );

    hintTable[NOCTURNE_OF_SHADOW] = HintText::Item({
                       //obscure text
                       Text{"a song of spooky spirits", /*french*/"", /*spanish*/"la canción de los espectros"},
                       Text{"a graveyard boogie",       /*french*/"", /*spanish*/"una honra fúnebre"},
                       Text{"a haunted hymn",           /*french*/"", /*spanish*/"una estrofa encantada"},
                       Text{"a purple spark trail",     /*french*/"", /*spanish*/"el sendero malva"},
                     },
                       //clear text
                       Text{"the Nocturne of Shadow", /*french*/"", /*spanish*/"el Nocturno de la sombra"}
    );

    hintTable[PRELUDE_OF_LIGHT] = HintText::Item({
                       //obscure text
                       Text{"a luminous prologue melody", /*french*/"", /*spanish*/"la melodía refulgente"},
                       Text{"a yellow spark trail",       /*french*/"", /*spanish*/"el sendero áureo"},
                       Text{"the temple traveler",        /*french*/"", /*spanish*/"la ruta del templo"},
                     },
                       //clear text
                       Text{"the Prelude of Light", /*french*/"", /*spanish*/"el Preludio de la luz"}
    );

    hintTable[MAP] = HintText::Item({
                       //obscure text
                       Text{"a dungeon atlas", /*french*/"", /*spanish*/"el atlas de una mazmorra"},
                       Text{"blueprints",      /*french*/"", /*spanish*/"unos planos"},
                     },
                       //clear text
                       Text{"a Map", /*french*/"", /*spanish*/"un mapa"}
    );

    hintTable[COMPASS] = HintText::Item({
                       //obscure text
                       Text{"a treasure tracker", /*french*/"", /*spanish*/"un buscatesoros"},
                       Text{"a magnetic needle",  /*french*/"", /*spanish*/"una aguja magnética"},
                     },
                       //clear text
                       Text{"a Compass", /*french*/"", /*spanish*/"una brújula"}
    );

    hintTable[BOSS_KEY] = HintText::Item({
                       //obscure text
                       Text{"a master of unlocking",   /*french*/"", /*spanish*/"la clave de un jefe"},
                       Text{"a dungeon's master pass", /*french*/"", /*spanish*/"el pase maestro de una mazmorra"},
                     },
                       //clear text
                       Text{"a Boss Key", /*french*/"", /*spanish*/"una gran llave"}
    );

    hintTable[GANONS_CASTLE_BOSS_KEY] = HintText::Item({
                       //obscure text
                       Text{"a master of unlocking",   /*french*/"", /*spanish*/"la clave de un jefe"},
                       Text{"a dungeon's master pass", /*french*/"", /*spanish*/"el pase maestro de una mazmorra"},
                     },
                       //clear text
                       Text{"a Boss Key", /*french*/"", /*spanish*/"una gran llave"}
    );

    hintTable[SMALL_KEY] = HintText::Item({
                       //obscure text
                       Text{"a tool for unlocking", /*french*/"", /*spanish*/"una clave de una entrada"},
                       Text{"a dungeon pass",       /*french*/"", /*spanish*/"un pase de una mazmorra"},
                       Text{"a lock remover",       /*french*/"", /*spanish*/"un destructor de cerraduras"},
                       Text{"a lockpick",           /*french*/"", /*spanish*/"una ganzúa"},
                     },
                       //clear text
                       Text{"a Small Key", /*french*/"", /*spanish*/"una llave pequeña"}
    );

    hintTable[GERUDO_FORTRESS_SMALL_KEY] = HintText::Item({
                       //obscure text
                       Text{"a get out of jail free card", /*french*/"", /*spanish*/"una clave de una celda"},
                     },
                       //clear text
                       Text{"a Jail Key", /*french*/"", /*spanish*/"una llave de la celda"}
    );

    hintTable[KOKIRI_EMERALD] = HintText::Item({
                       //obscure text
                       Text{"a green stone",        /*french*/"", /*spanish*/"una piedra verdemar"},
                       Text{"a gift before death",  /*french*/"", /*spanish*/"un regalo antes de fallecer"},
                     },
                       //clear text
                       Text{"the Kokiri Emerald", /*french*/"", /*spanish*/"la Esmeralda Kokiri"}
    );

    hintTable[GORON_RUBY] = HintText::Item({
                       //obscure text
                       Text{"a red stone",        /*french*/"", /*spanish*/"una piedra carmín"},
                       Text{"sworn brotherhood",  /*french*/"", /*spanish*/"el juramento de hermanos de sangre"},
                     },
                       //clear text
                       Text{"the Goron Ruby", /*french*/"", /*spanish*/"el Rubí Goron"}
    );

    hintTable[ZORA_SAPPHIRE] = HintText::Item({
                       //obscure text
                       Text{"a blue stone",        /*french*/"", /*spanish*/"una piedra celeste"},
                       Text{"an engagement gift",  /*french*/"", /*spanish*/"un regalo de compromiso"},
                     },
                       //clear text
                       Text{"the Zora Sapphire", /*french*/"", /*spanish*/"el Zafiro Zora"}
    );

    hintTable[FOREST_MEDALLION] = HintText::Item({
                       //obscure text
                       Text{"a green coin",        /*french*/"", /*spanish*/"una moneda esmeralda"},
                       Text{"Saria's friendship",  /*french*/"", /*spanish*/"la amistad de Saria"},
                     },
                       //clear text
                       Text{"the Forest Medallion", /*french*/"", /*spanish*/"el Medallón del Bosque"}
    );

    hintTable[FIRE_MEDALLION] = HintText::Item({
                       //obscure text
                       Text{"a red coin",      /*french*/"", /*spanish*/"una moneda carmesí"},
                       Text{"Darunia's power", /*french*/"", /*spanish*/"el poder de Darunia"},
                     },
                       //clear text
                       Text{"the Fire Medallion", /*french*/"", /*spanish*/"el Medallón del Fuego"}
    );

    hintTable[WATER_MEDALLION] = HintText::Item({
                       //obscure text
                       Text{"a blue coin",  /*french*/"", /*spanish*/"una moneda azur"},
                       Text{"Ruto's power", /*french*/"", /*spanish*/"el poder de Ruto"},
                     },
                       //clear text
                       Text{"the Water Medallion", /*french*/"", /*spanish*/"el Medallón del Agua"}
    );

    hintTable[SPIRIT_MEDALLION] = HintText::Item({
                       //obscure text
                       Text{"an orange coin",  /*french*/"", /*spanish*/"una moneda ámbar"},
                       Text{"Nabooru's power", /*french*/"", /*spanish*/"el poder de Nabooru"},
                     },
                       //clear text
                       Text{"the Spirit Medallion", /*french*/"", /*spanish*/"el Medallón del Espíritu"}
    );

    hintTable[SHADOW_MEDALLION] = HintText::Item({
                       //obscure text
                       Text{"a purple coin", /*french*/"", /*spanish*/"una moneda malva"},
                       Text{"Impa's power",  /*french*/"", /*spanish*/"el poder de Impa"},
                     },
                       //clear text
                       Text{"the Shadow Medallion", /*french*/"", /*spanish*/"el Medallón de la Sombra"}
    );

    hintTable[LIGHT_MEDALLION] = HintText::Item({
                       //obscure text
                       Text{"a yellow coin", /*french*/"", /*spanish*/"una moneda áurea"},
                       Text{"Rauru's power", /*french*/"", /*spanish*/"el poder de Rauru"},
                     },
                       //clear text
                       Text{"the Light Medallion", /*french*/"", /*spanish*/"el Medallón de la Luz"}
    );

    hintTable[RECOVERY_HEART] = HintText::Item({
                       //obscure text
                       Text{"a free heal",   /*french*/"", /*spanish*/"una cura de regalo"},
                       Text{"a hearty meal", /*french*/"", /*spanish*/"una minúscula corazonada"},
                       Text{"a Band-Aid",    /*french*/"", /*spanish*/"un corazoncito sanador"},
                     },
                       //clear text
                       Text{"a Recovery Heart", /*french*/"", /*spanish*/"un corazón"}
    );

    hintTable[GREEN_RUPEE] = HintText::Item({
                       //obscure text
                       Text{"a unique coin", /*french*/"", /*spanish*/"una singular moneda"},
                       Text{"a penny",       /*french*/"", /*spanish*/"un penique"},
                       Text{"a green gem",   /*french*/"", /*spanish*/"una gema verde"},
                     },
                       //clear text
                       Text{"a Green Rupee", /*french*/"", /*spanish*/"una rupia verde"}
    );

    hintTable[BLUE_RUPEE] = HintText::Item({
                       //obscure text
                       Text{"a common coin", /*french*/"", /*spanish*/"una moneda usual"},
                       Text{"a blue gem",    /*french*/"", /*spanish*/"una gema azul"},
                     },
                       //clear text
                       Text{"a Blue Rupee", /*french*/"", /*spanish*/"una rupia azul"}
    );

    hintTable[RED_RUPEE] = HintText::Item({
                       //obscure text
                       Text{"couch cash", /*french*/"", /*spanish*/"una buena moneda"},
                       Text{"a red gem",  /*french*/"", /*spanish*/"una gema roja"},
                     },
                       //clear text
                       Text{"a Red Rupee", /*french*/"", /*spanish*/"una rupia roja"}
    );

    hintTable[PURPLE_RUPEE] = HintText::Item({
                       //obscure text
                       Text{"big bucks",    /*french*/"", /*spanish*/"plata de calidad"},
                       Text{"a purple gem", /*french*/"", /*spanish*/"una gema morada"},
                       Text{"wealth",       /*french*/"", /*spanish*/"unos buenos cuartos"},
                     },
                       //clear text
                       Text{"a Purple Rupee", /*french*/"", /*spanish*/"una rupia morada"}
    );

    hintTable[HUGE_RUPEE] = HintText::Item({
                       //obscure text
                       Text{"a juicy jackpot", /*french*/"", /*spanish*/"el premio gordo"},
                       Text{"a yellow gem",    /*french*/"", /*spanish*/"una gema amarilla"},
                       Text{"a giant gem",     /*french*/"", /*spanish*/"una gema descomunal"},
                       Text{"great wealth",    /*french*/"", /*spanish*/"dinero a caudales"},
                     },
                       //clear text
                       Text{"a Huge Rupee", /*french*/"", /*spanish*/"una rupia gigante"}
    );

    hintTable[PIECE_OF_HEART] = HintText::Item({
                       //obscure text
                       Text{"a little love",  /*french*/"", /*spanish*/"una pizca de amor"},
                       Text{"a broken heart", /*french*/"", /*spanish*/"un corazón roto"},
                     },
                       //clear text
                       Text{"a Piece of Heart", /*french*/"", /*spanish*/"una pieza de corazón"}
    );

    hintTable[HEART_CONTAINER] = HintText::Item({
                       //obscure text
                       Text{"a lot of love",      /*french*/"", /*spanish*/"amor por doquier"},
                       Text{"a Valentine's gift", /*french*/"", /*spanish*/"un contenedor de afección"},
                       Text{"a boss's organ",     /*french*/"", /*spanish*/"los órganos de un jefe"},
                     },
                       //clear text
                       Text{"a Heart Container", /*french*/"", /*spanish*/"un contenedor de corazón"}
    );

    hintTable[ICE_TRAP] = HintText::Item({
                       //obscure text
                       Text{"a gift from Ganon",    /*french*/"", /*spanish*/"un regalo de Ganon"},
                       Text{"a chilling discovery", /*french*/"", /*spanish*/"un escalofriante hallazgo"},
                       Text{"frosty fun",           /*french*/"", /*spanish*/"una gélida diversión"},
                     },
                       //clear text
                       Text{"an Ice Trap", /*french*/"", /*spanish*/"una trampa de hielo"}
    );

  //MILK

    hintTable[BOMBS_5] = HintText::Item({
                       //obscure text
                       Text{"a few explosives",  /*french*/"", /*spanish*/"un par de explosivos"},
                       Text{"a few blast balls", /*french*/"", /*spanish*/"un par de estallidos"},
                     },
                       //clear text
                       Text{"Bombs (5 pieces)", /*french*/"", /*spanish*/"unas (5) bombas"}
    );

    hintTable[BOMBS_10] = HintText::Item({
                       //obscure text
                       Text{"some explosives",  /*french*/"", /*spanish*/"unos cuantos explosivos"},
                       Text{"some blast balls", /*french*/"", /*spanish*/"unos cuantos estallidos"},
                     },
                       //clear text
                       Text{"Bombs (10 pieces)", /*french*/"", /*spanish*/"unas (10) bombas"}
    );

    hintTable[BOMBS_20] = HintText::Item({
                       //obscure text
                       Text{"lots-o-explosives",     /*french*/"", /*spanish*/"un puñado de explosivos"},
                       Text{"plenty of blast balls", /*french*/"", /*spanish*/"bastantes estallidos"},
                     },
                       //clear text
                       Text{"Bombs (20 pieces)", /*french*/"", /*spanish*/"unas (20) bombas"}
    );

    hintTable[BOMBCHU_5] = HintText::Item({
                       //obscure text
                       Text{"a few mice bombs",     /*french*/"", /*spanish*/"un par de bombas roedoras"},
                       Text{"a few proximity mice", /*french*/"", /*spanish*/"un par de explosivos ratoncitos"},
                       Text{"a few wall crawlers",  /*french*/"", /*spanish*/"un par de trepaparedes"},
                       Text{"a few trail blazers",  /*french*/"", /*spanish*/"un par de ratas propulsadas"},
                     },
                       //clear text
                       Text{"Bombchus (5 pieces)", /*french*/"", /*spanish*/"unos (5) bombchus"}
    );

    hintTable[BOMBCHU_10] = HintText::Item({
                       //obscure text
                       Text{"some mice bombs",     /*french*/"", /*spanish*/"unas cuantas bombas roedoras"},
                       Text{"some proximity mice", /*french*/"", /*spanish*/"unos cuantos explosivos ratoncitos"},
                       Text{"some wall crawlers",  /*french*/"", /*spanish*/"unos cuantos trepaparedes"},
                       Text{"some trail blazers",  /*french*/"", /*spanish*/"unas cuantas ratas propulsadas"},
                     },
                       //clear text
                       Text{"Bombchus (10 pieces)", /*french*/"", /*spanish*/"unos (10) bombchus"}
    );

    hintTable[BOMBCHU_20] = HintText::Item({
                       //obscure text
                       Text{"plenty of mice bombs",     /*french*/"", /*spanish*/"bastantes bombas roedoras"},
                       Text{"plenty of proximity mice", /*french*/"", /*spanish*/"bastantes explosivos ratoncitos"},
                       Text{"plenty of wall crawlers",  /*french*/"", /*spanish*/"bastantes trepaparedes"},
                       Text{"plenty of trail blazers",  /*french*/"", /*spanish*/"bastantes ratas propulsadas"},
                     },
                       //clear text
                       Text{"Bombchus (20 pieces)", /*french*/"", /*spanish*/"unos (20) bombchus"}
    );

  //BOMBCHU_DROP

    hintTable[ARROWS_5] = HintText::Item({
                       //obscure text
                       Text{"a few danger darts", /*french*/"", /*spanish*/"un par de peligrosos dardos"},
                       Text{"a few sharp shafts", /*french*/"", /*spanish*/"un par de puntas afiladas"},
                     },
                       //clear text
                       Text{"Arrows (5 pieces)", /*french*/"", /*spanish*/"unas (5) flechas"}
    );

    hintTable[ARROWS_10] = HintText::Item({
                       //obscure text
                       Text{"some danger darts", /*french*/"", /*spanish*/"unos cuantos peligrosos dardos"},
                       Text{"some sharp shafts", /*french*/"", /*spanish*/"unas cuantas puntas afiladas"},
                     },
                       //clear text
                       Text{"Arrows (10 pieces)", /*french*/"", /*spanish*/"unas (10) flechas"}
    );

    hintTable[ARROWS_30] = HintText::Item({
                       //obscure text
                       Text{"plenty of danger darts", /*french*/"", /*spanish*/"bastantes peligrosos dardos"},
                       Text{"plenty of sharp shafts", /*french*/"", /*spanish*/"bastantes puntas afiladas"},
                     },
                       //clear text
                       Text{"Arrows (30 pieces)", /*french*/"", /*spanish*/"unas (30) flechas"}
    );

    hintTable[DEKU_NUTS_5] = HintText::Item({
                       //obscure text
                       Text{"some nuts",       /*french*/"", /*spanish*/"un par de nueces"},
                       Text{"some flashbangs", /*french*/"", /*spanish*/"un par de semillas de aturdimiento"},
                       Text{"some scrub spit", /*french*/"", /*spanish*/"un par de escupitajos deku"},
                     },
                       //clear text
                       Text{"Deku Nuts (5 pieces)", /*french*/"", /*spanish*/"unas (5) nueces deku"}
    );

    hintTable[DEKU_NUTS_10] = HintText::Item({
                       //obscure text
                       Text{"lots-o-nuts",          /*french*/"", /*spanish*/"un puñado de nueces"},
                       Text{"plenty of flashbangs", /*french*/"", /*spanish*/"unas cuantas semillas de aturdimiento"},
                       Text{"plenty of scrub spit", /*french*/"", /*spanish*/"unos cuantos escupitajos deku"},
                     },
                       //clear text
                       Text{"Deku Nuts (10 pieces)", /*french*/"", /*spanish*/"unas (10) nueces deku"}
    );

    hintTable[DEKU_SEEDS_30] = HintText::Item({
                       //obscure text
                       Text{"catapult ammo", /*french*/"", /*spanish*/"una buena munición infantil"},
                       Text{"lots-o-seeds",  /*french*/"", /*spanish*/"un puñado de semillas"},
                     },
                       //clear text
                       Text{"Deku Seeds (30 pieces)", /*french*/"", /*spanish*/"unas (30) semillas deku"}
    );

    hintTable[DEKU_STICK_1] = HintText::Item({
                       //obscure text
                       Text{"a breakable branch", /*french*/"", /*spanish*/"un pequeño báculo"},
                     },
                       //clear text
                       Text{"a Deku Stick", /*french*/"", /*spanish*/"un palo deku"}
    );

    hintTable[TREASURE_GAME_HEART] = HintText::Item({
                       //obscure text
                       Text{"a victory valentine", /*french*/"", /*spanish*/"el amor victorioso"},
                     },
                       //clear text
                       Text{"a Piece of Heart", /*french*/"", /*spanish*/"una pieza de corazón"}
    );

    hintTable[TREASURE_GAME_GREEN_RUPEE] = HintText::Item({
                       //obscure text
                       Text{"the dollar of defeat", /*french*/"", /*spanish*/"la moneda de la derrota"},
                     },
                       //clear text
                       Text{"a Green Rupee", /*french*/"", /*spanish*/"una rupia verde"}
    );

    hintTable[TRIFORCE_PIECE] = HintText::Item({
                       //obscure text
                       Text{"a triumph fork",  /*french*/"", /*spanish*/"un trígono del triunfo"},
                       Text{"cheese",          /*french*/"", /*spanish*/"un queso"},
                       Text{"a gold fragment", /*french*/"", /*spanish*/"un fragmento dorado"},
                     },
                       //clear text
                       Text{"a Piece of the Triforce", /*french*/"", /*spanish*/"una Pieza de la Trifuerza"}
    );

    hintTable[EPONA] = HintText::Item({
                       //obscure text
                       Text{"a horse",              /*french*/"", /*spanish*/"una yegua"},
                       Text{"a four legged friend", /*french*/"", /*spanish*/"una amiga cuadrúpeda"},
                     },
                       //clear text
                       Text{"Epona", /*french*/"", /*spanish*/"Epona"}
    );

    // {HintError] = HintText::Item({
    //                      //obscure text
    //                      Text{"something mysterious", /*french*/"", /*spanish*/"algo misterioso"},
    //                      Text{"an unknown treasure",  /*french*/"", /*spanish*/"un desconocido tesoro"},
    //                    },
    //                      //clear text
    //                      Text{"An Error (Please Report This)", /*french*/"", /*spanish*/"Error (Repórtelo si es posible)"}
    // );

    /*--------------------------
    |     ALWAYS HINT TEXT     |
    ---------------------------*/

    hintTable[ZR_FROGS_OCARINA_GAME] = HintText::Always({
                       //obscure text
                       Text{"an #amphibian feast# yields",               /*french*/"", /*spanish*/"una #fiesta anfibia# brinda"},
                       Text{"the #croaking choir's magnum opus# awards", /*french*/"", /*spanish*/"un #coro maestro de ancas# premia"},
                       Text{"the #froggy finale# yields",                /*french*/"", /*spanish*/"el #gran final batracio# brinda"},
                     },
                       //clear text
                       Text{"the final reward from the #Frogs of Zora's River# is", /*french*/"", /*spanish*/"la recompensa final de las #ranas del Río Zora# premia"}
    );

    hintTable[KF_LINKS_HOUSE_COW] = HintText::Always({
                       //obscure text
                       Text{"the #bovine bounty of a horseback hustle# gifts", /*french*/"", /*spanish*/"la #recompensa bovina de un paseo a caballo# brinda"},
                     },
                       //clear text
                       Text{"#Malon's obstacle course# leads to", /*french*/"", /*spanish*/"la #carrera de obstáculos de Malon# brinda"}
    );

    /*--------------------------
    |    SOMETIMES HINT TEXT   |
    ---------------------------*/

    hintTable[SONG_FROM_OCARINA_OF_TIME] = HintText::Sometimes({
                       //obscure text
                       Text{"the #Ocarina of Time# teaches", /*french*/"", /*spanish*/"la #Ocarina del Tiempo# enseña"},
    });

    hintTable[SONG_FROM_COMPOSERS_GRAVE] = HintText::Sometimes({
                       //obscure text
                       Text{"#ReDead in the Composers' Grave# guard", /*french*/"", /*spanish*/"los #ReDeads del Panteón Real# guardan"},
                       Text{"the #Composer Brothers wrote#",          /*french*/"", /*spanish*/"los #hermanos compositores escribieron#"},
    });

    hintTable[SHEIK_IN_FOREST] = HintText::Sometimes({
                       //obscure text
                       Text{"#in a meadow# Sheik teaches", /*french*/"", /*spanish*/"#en la pradera sagrada# Sheik enseña"},
    });

    hintTable[SHEIK_AT_TEMPLE] = HintText::Sometimes({
                       //obscure text
                       Text{"Sheik waits at a #monument to time# to teach", /*french*/"", /*spanish*/"Sheik espera en el #momumento del tiempo# para enseñar"},
    });

    hintTable[SHEIK_IN_CRATER] = HintText::Sometimes({
                       //obscure text
                       Text{"the #crater's melody# is", /*french*/"", /*spanish*/"la #melodía del cráter# otorga"},
    });

    hintTable[SHEIK_IN_ICE_CAVERN] = HintText::Sometimes({
                       //obscure text
                       Text{"the #frozen cavern# echoes with", /*french*/"", /*spanish*/"en la #caverna de hielo# retumban los ecos de"},
    });

    hintTable[SHEIK_IN_KAKARIKO] = HintText::Sometimes({
                       //obscure text
                       Text{"a #ravaged village# mourns with", /*french*/"", /*spanish*/"un #arrasado pueblo# llora"},
    });

    hintTable[SHEIK_AT_COLOSSUS] = HintText::Sometimes({
                       //obscure text
                       Text{"a hero ventures #beyond the wasteland# to learn", /*french*/"", /*spanish*/"el héroe que se adentre #más allá del desierto encantado# aprenderá"},
    });


    hintTable[MARKET_10_BIG_POES] = HintText::Sometimes({
                       //obscure text
                       Text{"#ghost hunters# will be rewarded with", /*french*/"", /*spanish*/"los #cazafantasmas# son premiados con"},
                     },
                       //clear text
                       Text{"catching #Big Poes# leads to", /*french*/"", /*spanish*/"hacerte con #Grandes Poes# conduce a"}
    );

    hintTable[DEKU_THEATER_SKULL_MASK] = HintText::Sometimes({
                       //obscure text
                       Text{"the #Skull Mask# yields", /*french*/"", /*spanish*/"la #máscara de calavera# otorga"},
    });

    hintTable[DEKU_THEATER_MASK_OF_TRUTH] = HintText::Sometimes({
                       //obscure text
                       Text{"showing a #truthful eye to the crowd# rewards", /*french*/"", /*spanish*/"#mostrarle el ojo verdadero# a una multitud brinda"},
                     },
                       //clear text
                       Text{"the #Mask of Truth# yields", /*french*/"", /*spanish*/"la #máscara de la verdad# premia"}
    );

    hintTable[HF_OCARINA_OF_TIME_ITEM] = HintText::Sometimes({
                       //obscure text
                       Text{"the #treasure thrown by Princess Zelda# is", /*french*/"", /*spanish*/"el #tesoro arrojado por la Princesa Zelda# se trata de"},
    });

    hintTable[DMT_BIGGORON] = HintText::Sometimes({
                       //obscure text
                       Text{"#Biggoron# crafts", /*french*/"", /*spanish*/"#Biggoron# forja"},
    });

    hintTable[KAK_50_GOLD_SKULLTULA_REWARD] = HintText::Sometimes({
                       //obscure text
                       Text{"#50 bug badges# rewards",           /*french*/"", /*spanish*/"#50 medallas de insectos# otorgan"},
                       Text{"#50 spider souls# yields",          /*french*/"", /*spanish*/"#50 almas de araña# otorgan"},
                       Text{"#50 auriferous arachnids# lead to", /*french*/"", /*spanish*/"#50 arácnidos auríferos# otorgan"},
                     },
                       //clear text
                       Text{"slaying #50 Gold Skulltulas# reveals", /*french*/"", /*spanish*/"exterminar #50 skulltulas doradas# revela"}
    );

    hintTable[KAK_40_GOLD_SKULLTULA_REWARD] = HintText::Sometimes({
                       //obscure text
                       Text{"#40 bug badges# rewards",           /*french*/"", /*spanish*/"#40 medallas de insectos# otorgan"},
                       Text{"#40 spider souls# yields",          /*french*/"", /*spanish*/"#40 almas de araña# otorgan"},
                       Text{"#40 auriferous arachnids# lead to", /*french*/"", /*spanish*/"#40 arácnidos auríferos# otorgan"},
                     },
                       //clear text
                       Text{"slaying #40 Gold Skulltulas# reveals", /*french*/"", /*spanish*/"exterminar #40 skulltulas doradas# revela"}
    );

    hintTable[KAK_30_GOLD_SKULLTULA_REWARD] = HintText::Sometimes({
                       //obscure text
                       Text{"#30 bug badges# rewards",           /*french*/"", /*spanish*/"#30 medallas de insectos# otorgan"},
                       Text{"#30 spider souls# yields",          /*french*/"", /*spanish*/"#30 almas de araña# otorgan"},
                       Text{"#30 auriferous arachnids# lead to", /*french*/"", /*spanish*/"#30 arácnidos auríferos# otorgan"},
                     },
                       //clear text
                       Text{"slaying #30 Gold Skulltulas# reveals", /*french*/"", /*spanish*/"exterminar #30 skulltulas doradas# revela"}
    );

    hintTable[KAK_20_GOLD_SKULLTULA_REWARD] = HintText::Sometimes({
                       //obscure text
                       Text{"#20 bug badges# rewards",           /*french*/"", /*spanish*/"#20 medallas de insectos# otorgan"},
                       Text{"#20 spider souls# yields",          /*french*/"", /*spanish*/"#20 almas de araña# otorgan"},
                       Text{"#20 auriferous arachnids# lead to", /*french*/"", /*spanish*/"#20 arácnidos auríferos# otorgan"},
                     },
                       //clear text
                       Text{"slaying #20 Gold Skulltulas# reveals", /*french*/"", /*spanish*/"exterminar #20 skulltulas doradas# revela"}
    );

    hintTable[KAK_ANJU_AS_CHILD] = HintText::Sometimes({
                       //obscure text
                       Text{"#wrangling roosters# rewards", /*french*/"", /*spanish*/"#pillar a las gallinas# premia"},
                       Text{"#chucking chickens# gifts",    /*french*/"", /*spanish*/"#reunir a unos emplumados# premia"},
                     },
                       //clear text
                       Text{"#collecting cuccos# rewards", /*french*/"", /*spanish*/"#hacerte con todos los cucos# premia"}
    );

    hintTable[GC_DARUNIAS_JOY] = HintText::Sometimes({
                       //obscure text
                       Text{"a #groovin' goron# gifts", /*french*/"", /*spanish*/"#un gerudo marchoso# otorga"},
                     },
                       //clear text
                       Text{"#Darunia's dance# leads to", /*french*/"", /*spanish*/"#el baile de Darunia# conduce a"}
    );

    hintTable[LW_SKULL_KID] = HintText::Sometimes({
                       //obscure text
                       Text{"the #Skull Kid# grants", /*french*/"", /*spanish*/"#Skull Kid# otorga"},
    });

    hintTable[LH_SUN] = HintText::Sometimes({
                       //obscure text
                       Text{"staring into #the sun# grants", /*french*/"", /*spanish*/"#mirar al sol# revela"},
                     },
                       //clear text
                       Text{"shooting #the sun# grants", /*french*/"", /*spanish*/"#disparar al sol# revela"}
    );

    hintTable[MARKET_TREASURE_CHEST_GAME_REWARD] = HintText::Sometimes({
                       //obscure text
                       Text{"#gambling# grants",               /*french*/"", /*spanish*/"#los juegos de azar# revelan"},
                       Text{"there is a #1/32 chance# to win", /*french*/"", /*spanish*/"hay una #probabilidad de 1/32# de ganar"},
                     },
                       //clear text
                       Text{"the #treasure chest game# grants", /*french*/"", /*spanish*/"#el Cofre del Tesoro# premia"}
    );

    hintTable[GF_HBA_1500_POINTS] = HintText::Sometimes({
                       //obscure text
                       Text{"mastery of #horseback archery# grants", /*french*/"", /*spanish*/"amaestrar el #tiro con arco a caballo# premia"},
                     },
                       //clear text
                       Text{"scoring 1500 in #horseback archery# grants", /*french*/"", /*spanish*/"conseguir 1500 puntos en el #tiro con arco a caballo# premia"}
    );

    hintTable[GRAVEYARD_HEART_PIECE_GRAVE_CHEST] = HintText::Sometimes({
                       //obscure text
                       Text{"playing #Sun's Song# in a grave spawns", /*french*/"", /*spanish*/"#tocar la Canción del Sol# en una cripta conduce a"},
    });

    hintTable[GC_MAZE_LEFT_CHEST] = HintText::Sometimes({
                       //obscure text
                       Text{"in #Goron City# the hammer unlocks", /*french*/"", /*spanish*/"en la #Ciudad Goron# el martillo desbloquea"},
    });

    hintTable[GV_CHEST] = HintText::Sometimes({
                       //obscure text
                       Text{"in #Gerudo Valley# the hammer unlocks", /*french*/"", /*spanish*/"en el #Valle Gerudo# el martillo desbloquea"},
    });

    hintTable[GV_COW] = HintText::Sometimes({
                       //obscure text
                       Text{"a #cow in Gerudo Valley# gifts", /*french*/"", /*spanish*/"una #vaca del Valle Gerudo# brinda"},
    });

    hintTable[HC_GS_STORMS_GROTTO] = HintText::Sometimes({
                       //obscure text
                       Text{"a #spider behind a muddy wall# in a grotto holds", /*french*/"", /*spanish*/"una #araña tras una agrietada pared# de una cueva otorga"},
    });

    hintTable[HF_GS_COW_GROTTO] = HintText::Sometimes({
                       //obscure text
                       Text{"a #spider behind webs# in a grotto holds", /*french*/"", /*spanish*/"una #araña tras una telaraña# de una cueva otorga"},
    });

    hintTable[HF_COW_GROTTO_COW] = HintText::Sometimes({
                       //obscure text
                       Text{"the #cobwebbed cow# gifts", /*french*/"", /*spanish*/"la #vaca tras una telaraña# brinda"},
                     },
                       //clear text
                       Text{"a #cow behind webs# in a grotto gifts", /*french*/"", /*spanish*/"una #vaca tras una telaraña# de una cueva brinda"}
    );

    hintTable[ZF_GS_HIDDEN_CAVE] = HintText::Sometimes({
                       //obscure text
                       Text{"a spider high #above the icy waters# holds", /*french*/"", /*spanish*/"una araña en lo #alto de las congeladas aguas# otorga"},
    });

    hintTable[WASTELAND_CHEST] = HintText::Sometimes({
                       //obscure text
                       Text{"#deep in the wasteland# is",         /*french*/"", /*spanish*/"en lo #profundo del desierto encantado# yace"},
                       Text{"beneath #the sands#, flames reveal", /*french*/"", /*spanish*/"tras las #arenas#, unas llamas revelan"},
    });

    hintTable[WASTELAND_GS] = HintText::Sometimes({
                       //obscure text
                       Text{"a #spider in the wasteland# holds", /*french*/"", /*spanish*/"una #araña del desierto encantado# otorga"},
    });

    hintTable[GRAVEYARD_COMPOSERS_GRAVE_CHEST] = HintText::Sometimes({
                       //obscure text
                       Text{"#flames in the Composers' Grave# reveal", /*french*/"", /*spanish*/"#las llamas del Panteón Real# revelan"},
                       Text{"the #Composer Brothers hid#",             /*french*/"", /*spanish*/"los #hermanos compositores esconden#"},
    });

    hintTable[ZF_BOTTOM_FREESTANDING_POH] = HintText::Sometimes({
                       //obscure text
                       Text{"#under the icy waters# lies", /*french*/"", /*spanish*/"#bajo las congeladas aguas# yace"},
    });

    hintTable[GC_POT_FREESTANDING_POH] = HintText::Sometimes({
                       //obscure text
                       Text{"spinning #Goron pottery# contains", /*french*/"", /*spanish*/"una #cerámica goron# contiene"},
    });

    hintTable[ZD_KING_ZORA_THAWED] = HintText::Sometimes({
                       //obscure text
                       Text{"a #defrosted dignitary# gifts", /*french*/"", /*spanish*/"una #Alteza descongelada# brinda"},
                     },
                       //clear text
                       Text{"unfreezing #King Zora# grants", /*french*/"", /*spanish*/"#descongelar al Rey Zora# conduce a"}
    );

    hintTable[DMC_DEKU_SCRUB] = HintText::Sometimes({
                       //obscure text
                       Text{"a single #scrub in the crater# sells", /*french*/"", /*spanish*/"un solitario #deku del cráter# vende"},
    });

    hintTable[DMC_GS_CRATE] = HintText::Sometimes({
                       //obscure text
                       Text{"a spider under a #crate in the crater# holds", /*french*/"", /*spanish*/"una araña bajo una #caja del cráter# otorga"},
    });


    hintTable[DEKU_TREE_MQ_AFTER_SPINNING_LOG_CHEST] = HintText::Sometimes({
                       //obscure text
                       Text{"a #temporal stone within a tree# contains", /*french*/"", /*spanish*/"un #bloque temporal de un árbol# contiene"},
                     },
                       //clear text
                       Text{"a #temporal stone within the Deku Tree# contains", /*french*/"", /*spanish*/"un #bloque temporal del Árbol Deku# contiene"}
    );

    hintTable[DEKU_TREE_MQ_GS_BASEMENT_GRAVES_ROOM] = HintText::Sometimes({
                       //obscure text
                       Text{"a #spider on a ceiling in a tree# holds", /*french*/"", /*spanish*/"una #araña en el techo de un árbol# otorga"},
                     },
                       //clear text
                       Text{"a #spider on a ceiling in the Deku Tree# holds", /*french*/"", /*spanish*/"una #araña en el techo del Árbol Deku# otorga"}
    );

    hintTable[DODONGOS_CAVERN_MQ_GS_SONG_OF_TIME_BLOCK_ROOM] = HintText::Sometimes({
                       //obscure text
                       Text{"a spider under #temporal stones in a cavern# holds", /*french*/"", /*spanish*/"una araña bajo #bloques temporales de una cueva# otorga"},
                     },
                       //clear text
                       Text{"a spider under #temporal stones in Dodongo's Cavern# holds", /*french*/"", /*spanish*/"una araña bajo #bloques temporales de la Cueva de los Dodongos# otorga"}
    );

    hintTable[JABU_JABUS_BELLY_BOOMERANG_CHEST] = HintText::Sometimes({
                       //obscure text
                       Text{"a school of #stingers swallowed by a deity# guard", /*french*/"", /*spanish*/"un puñado de #stingers engullidos por una deidad# guardan"},
                     },
                       //clear text
                       Text{"a school of #stingers swallowed by Jabu Jabu# guard", /*french*/"", /*spanish*/"un puñado de #stingers engullidos por Jabu Jabu# guardan"}
    );

    hintTable[JABU_JABUS_BELLY_MQ_GS_INVISIBLE_ENEMIES_ROOM] = HintText::Sometimes({
                       //obscure text
                       Text{"a spider surrounded by #shadows in the belly of a deity# holds", /*french*/"", /*spanish*/"una araña rodeada de #sombras en la tripa de cierta diedad# otorga"},
                     },
                       //clear text
                       Text{"a spider surrounded by #shadows in Jabu Jabu's Belly# holds", /*french*/"", /*spanish*/"una araña rodeada de #sombras en la Tripa de Jabu Jabu# otorga"}
    );

    hintTable[JABU_JABUS_BELLY_MQ_COW] = HintText::Sometimes({
                       //obscure text
                       Text{"a #cow swallowed by a deity# gifts", /*french*/"", /*spanish*/"una #vaca engullida por cierta deidad# brinda"},
                     },
                       //clear text
                       Text{"a #cow swallowed by Jabu Jabu# gifts", /*french*/"", /*spanish*/"una #vaca engullida por Jabu Jabu# brinda"}
    );

    hintTable[FIRE_TEMPLE_SCARECROW_CHEST] = HintText::Sometimes({
                       //obscure text
                       Text{"a #scarecrow atop the volcano# hides", /*french*/"", /*spanish*/"un #espantapájaros en lo alto del volcán# esconde"},
                     },
                       //clear text
                       Text{"#Pierre atop the Fire Temple# hides", /*french*/"", /*spanish*/"#Pierre en lo alto del Templo del Fuego# esconde"}
    );

    hintTable[FIRE_TEMPLE_MEGATON_HAMMER_CHEST] = HintText::Sometimes({
                       //obscure text
                       Text{"the #Flare Dancer atop the volcano# guards a chest containing", /*french*/"", /*spanish*/"el #Bailafuego en lo alto del volcán# otorga"},
                     },
                       //clear text
                       Text{"the #Flare Dancer atop the Fire Temple# guards a chest containing", /*french*/"", /*spanish*/"el #Bailaguego en lo alto del Templo del Fuego# otorga"}
    );

    hintTable[FIRE_TEMPLE_MQ_CHEST_ON_FIRE] = HintText::Sometimes({
                       //obscure text
                       Text{"the #Flare Dancer atop the volcano# guards a chest containing", /*french*/"", /*spanish*/"el #Bailafuego en lo alto del volcán# otorga"},
                     },
                       //clear text
                       Text{"the #Flare Dancer atop the Fire Temple# guards a chest containing", /*french*/"", /*spanish*/"el #Bailafuego en lo alto del Templo del Fuego# otorga"}
    );

    hintTable[FIRE_TEMPLE_MQ_GS_SKULL_ON_FIRE] = HintText::Sometimes({
                       //obscure text
                       Text{"a #spider under a block in the volcano# holds", /*french*/"", /*spanish*/"una #araña bajo el bloque de un volcán# otorga"},
                     },
                       //clear text
                       Text{"a #spider under a block in the Fire Temple# holds", /*french*/"", /*spanish*/"una #araña bajo un bloque del Templo del Fuego# otorga"}
    );

    hintTable[WATER_TEMPLE_RIVER_CHEST] = HintText::Sometimes({
                       //obscure text
                       Text{"beyond the #river under the lake# waits", /*french*/"", /*spanish*/"tras el #río bajo el lago# yace"},
                     },
                       //clear text
                       Text{"beyond the #river in the Water Temple# waits", /*french*/"", /*spanish*/"tras el #río del Templo del Agua# yace"}
    );

    hintTable[WATER_TEMPLE_BOSS_KEY_CHEST] = HintText::Sometimes({
                       //obscure text
                       Text{"dodging #rolling boulders under the lake# leads to", /*french*/"", /*spanish*/"esquivar #rocas rodantes bajo el lago# conduce a"},
                     },
                       //clear text
                       Text{"dodging #rolling boulders in the Water Temple# leads to", /*french*/"", /*spanish*/"esquivar #rocas rondantes del Templo del Agua# conduce a"}
    );

    hintTable[WATER_TEMPLE_GS_BEHIND_GATE] = HintText::Sometimes({
                       //obscure text
                       Text{"a spider behind a #gate under the lake# holds", /*french*/"", /*spanish*/"una araña tras #una valla bajo el lago# otorga"},
                     },
                       //clear text
                       Text{"a spider behind a #gate in the Water Temple# holds", /*french*/"", /*spanish*/"una araña tras #una valla del Templo del Agua# otorga"}
    );

    hintTable[WATER_TEMPLE_MQ_FREESTANDING_KEY] = HintText::Sometimes({
                       //obscure text
                       Text{"hidden in a #box under the lake# lies", /*french*/"", /*spanish*/"en una #caja bajo el lago# yace"},
                     },
                       //clear text
                       Text{"hidden in a #box in the Water Temple# lies", /*french*/"", /*spanish*/"en una #caja del Templo del Agua# yace"}
    );

    hintTable[WATER_TEMPLE_MQ_GS_FREESTANDING_KEY_AREA] = HintText::Sometimes({
                       //obscure text
                       Text{"the #locked spider under the lake# holds", /*french*/"", /*spanish*/"la #araña enjaulada bajo el lago# otorga"},
                     },
                       //clear text
                       Text{"the #locked spider in the Water Temple# holds", /*french*/"", /*spanish*/"la #araña enjaulada del Templo del Agua# otorga"}
    );

    hintTable[WATER_TEMPLE_MQ_GS_TRIPLE_WALL_TORCH] = HintText::Sometimes({
                       //obscure text
                       Text{"a spider behind a #gate under the lake# holds", /*french*/"", /*spanish*/"una araña tras una #valla bajo el lago# otorga"},
                     },
                       //clear text
                       Text{"a spider behind a #gate in the Water Temple# holds", /*french*/"", /*spanish*/"una araña tras una #valla del Templo del Agua#"}
    );

    hintTable[GERUDO_TRAINING_GROUNDS_UNDERWATER_SILVER_RUPEE_CHEST] = HintText::Sometimes({
                       //obscure text
                       Text{"those who seek #sunken silver rupees# will find", /*french*/"", /*spanish*/"aquellos que busquen las #rupias plateadas sumergidas# encontrarán"},
                       Text{"the #thieves' underwater training# rewards",      /*french*/"", /*spanish*/"la #instrucción submarina de las ladronas# premia"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MQ_UNDERWATER_SILVER_RUPEE_CHEST] = HintText::Sometimes({
                       //obscure text
                       Text{"those who seek #sunken silver rupees# will find", /*french*/"", /*spanish*/"aquellos que busquen las #rupias plateadas sumergidas# encontrarán"},
                       Text{"the #thieves' underwater training# rewards",      /*french*/"", /*spanish*/"la #instrucción submarina de las ladronas# premia"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MAZE_PATH_FINAL_CHEST] = HintText::Sometimes({
                       //obscure text
                       Text{"the final prize of #the thieves' training# is", /*french*/"", /*spanish*/"el premio final de la #instrucción de las ladronas# brinda"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MQ_ICE_ARROWS_CHEST] = HintText::Sometimes({
                       //obscure text
                       Text{"the final prize of #the thieves' training# is", /*french*/"", /*spanish*/"el premio final de la #instrucción de las ladronas# brinda"},
    });

    hintTable[BOTTOM_OF_THE_WELL_LENS_OF_TRUTH_CHEST] = HintText::Sometimes({
                       //obscure text
                       Text{"the well's #grasping ghoul# hides",    /*french*/"", /*spanish*/"en la #profundidad del pozo# se esconde"},
                       Text{"a #nether dweller in the well# holds", /*french*/"", /*spanish*/"el #temido morador del pozo# concede"},
                     },
                       //clear text
                       Text{"#Dead Hand in the well# holds", /*french*/"", /*spanish*/"la #Mano Muerta del pozo# concede"}
    );

    hintTable[BOTTOM_OF_THE_WELL_MQ_COMPASS_CHEST] = HintText::Sometimes({
                       //obscure text
                       Text{"the well's #grasping ghoul# hides",    /*french*/"", /*spanish*/"en la #profundidad del pozo# se esconde"},
                       Text{"a #nether dweller in the well# holds", /*french*/"", /*spanish*/"el #temido morador del pozo# concede"},
                     },
                       //clear text
                       Text{"#Dead Hand in the well# holds", /*french*/"", /*spanish*/"la #Mano Muerta del pozo# concede"}
    );

    hintTable[SPIRIT_TEMPLE_SILVER_GAUNTLETS_CHEST] = HintText::Sometimes({
                       //obscure text
                       Text{"the treasure #sought by Nabooru# is", /*french*/"", /*spanish*/"el #ansiado tesoro de Nabooru# brinda"},
                     },
                       //clear text
                       Text{"upon the #Colossus's right hand# is", /*french*/"", /*spanish*/"en la #mano derecha del Coloso# yace"}
    );

    hintTable[SPIRIT_TEMPLE_MIRROR_SHIELD_CHEST] = HintText::Sometimes({
                       //obscure text
                       Text{"upon the #Colossus's left hand# is", /*french*/"", /*spanish*/"en la #mano izquierda del Coloso# yace"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_CHILD_HAMMER_SWITCH_CHEST] = HintText::Sometimes({
                       //obscure text
                       Text{"a #temporal paradox in the Colossus# yields", /*french*/"", /*spanish*/"una #paradoja temporal del Coloso# conduce a"},
                     },
                       //clear text
                       Text{"a #temporal paradox in the Spirit Temple# yields", /*french*/"", /*spanish*/"una #paradoja temporal del Coloso# conduce a"}
    );

    hintTable[SPIRIT_TEMPLE_MQ_SYMPHONY_ROOM_CHEST] = HintText::Sometimes({
                       //obscure text
                       Text{"a #symphony in the Colossus# yields", /*french*/"", /*spanish*/"una #sinfonía del Coloso# conduce a"},
                     },
                       //clear text
                       Text{"a #symphony in the Spirit Temple# yields", /*french*/"", /*spanish*/"una #sinfonía del Coloso# conduce a"}
    );

    hintTable[SPIRIT_TEMPLE_MQ_GS_SYMPHONY_ROOM] = HintText::Sometimes({
                       //obscure text
                       Text{"a #spider's symphony in the Colossus# yields", /*french*/"", /*spanish*/"la #araña de la sinfonía del Coloso# otorga"},
                     },
                       //clear text
                       Text{"a #spider's symphony in the Spirit Temple# yields", /*french*/"", /*spanish*/"la #araña de la sinfonía del Coloso# otorga"}
    );

    hintTable[SHADOW_TEMPLE_INVISIBLE_FLOORMASTER_CHEST] = HintText::Sometimes({
                       //obscure text
                       Text{"shadows in an #invisible maze# guard", /*french*/"", /*spanish*/"las sombras del #laberinto misterioso# esconden"},
    });

    hintTable[SHADOW_TEMPLE_MQ_BOMB_FLOWER_CHEST] = HintText::Sometimes({
                       //obscure text
                       Text{"shadows in an #invisible maze# guard", /*french*/"", /*spanish*/"las sombras del #laberinto invisible# esconden"},
    });

    /*--------------------------
    |    EXCLUDE HINT TEXT     |
    ---------------------------*/

    hintTable[KF_KOKIRI_SWORD_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #hidden treasure of the Kokiri# is", /*french*/"", /*spanish*/"el #tesoro oculto de los Kokiri# esconde"},
    });

    hintTable[KF_MIDOS_TOP_LEFT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #leader of the Kokiri# hides", /*french*/"", /*spanish*/"el #líder de los Kokiri# esconde"},
                     },
                       //clear text
                       Text{"#inside Mido's house# is", /*french*/"", /*spanish*/"en la #casa de Mido# yace"}
    );

    hintTable[KF_MIDOS_TOP_RIGHT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #leader of the Kokiri# hides", /*french*/"", /*spanish*/"el #líder de los Kokiri# esconde"},
                     },
                       //clear text
                       Text{"#inside Mido's house# is", /*french*/"", /*spanish*/"en la #casa de Mido# yace"}
    );

    hintTable[KF_MIDOS_BOTTOM_LEFT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #leader of the Kokiri# hides", /*french*/"", /*spanish*/"el #líder de los Kokiri# esconde"},
                     },
                       //clear text
                       Text{"#inside Mido's house# is", /*french*/"", /*spanish*/"en la #casa de Mido# yace"}
    );

    hintTable[KF_MIDOS_BOTTOM_RIGHT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #leader of the Kokiri# hides", /*french*/"", /*spanish*/"el #líder de los Kokiri# esconde"},
                     },
                       //clear text
                       Text{"#inside Mido's house# is", /*french*/"", /*spanish*/"en la #casa de Mido# yace"}
    );

    hintTable[GRAVEYARD_SHIELD_GRAVE_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #treasure of a fallen soldier# is", /*french*/"", /*spanish*/"el #tesoro de un soldado caído# esconde"},
    });

    hintTable[DMT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"hidden behind a wall on a #mountain trail# is", /*french*/"", /*spanish*/"tras una pared del #sendero de la montaña# otorga"},
    });

    hintTable[GC_MAZE_RIGHT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"in #Goron City# explosives unlock", /*french*/"", /*spanish*/"en la #Ciudad Goron# unos explosivos desbloquean"},
    });

    hintTable[GC_MAZE_CENTER_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"in #Goron City# explosives unlock", /*french*/"", /*spanish*/"en la #Ciudad Goron# unos explosivos desbloquean"},
    });

    hintTable[ZD_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"fire #beyond a waterfall# reveals", /*french*/"", /*spanish*/"las #llamas tras una una cascada# revelan"},
    });

    hintTable[GRAVEYARD_HOOKSHOT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a chest hidden by a #speedy spectre# holds", /*french*/"", /*spanish*/"un cofre custodiado por un #espectro veloz# otorga"},
                     },
                       //clear text
                       Text{"#dead Dampé's first prize# is", /*french*/"", /*spanish*/"el primer premio de #Dampé fallecido# se trata de"}
    );

    hintTable[GF_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"on a #rooftop in the desert# lies", /*french*/"", /*spanish*/"en una #azotea en el desierto# yace"},
    });

    hintTable[KAK_REDEAD_GROTTO_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#zombies beneath the earth# guard", /*french*/"", /*spanish*/"unos #zombis subterráneos# esconden"},
    });

    hintTable[SFM_WOLFOS_GROTTO_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#wolves beneath the earth# guard", /*french*/"", /*spanish*/"unos #lobos subterráneos# esconden"},
    });

    hintTable[HF_NEAR_MARKET_GROTTO_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #hole in a field near a drawbridge# holds", /*french*/"", /*spanish*/"bajo el #hoyo de una llanura cercano a un puente# yace"},
    });

    hintTable[HF_SOUTHEAST_GROTTO_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #hole amongst trees in a field# holds", /*french*/"", /*spanish*/"bajo un #hoyo de una llanura rodeado de árboles# yace"},
    });

    hintTable[HF_OPEN_GROTTO_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"an #open hole in a field# holds", /*french*/"", /*spanish*/"bajo un #hoyo descubierto de una llanura# yace"},
    });

    hintTable[KAK_OPEN_GROTTO_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"an #open hole in a town# holds", /*french*/"", /*spanish*/"bajo un #hoyo descubierto de un pueblo# yace"},
    });

    hintTable[ZR_OPEN_GROTTO_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #hole along a river# holds", /*french*/"", /*spanish*/"bajo un #hoyo junto a un río# yace"},
    });

    hintTable[KF_STORMS_GROTTO_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #hole in a forest village# holds", /*french*/"", /*spanish*/"bajo un #hoyo de una tribu forestal# yace"},
    });

    hintTable[LW_NEAR_SHORTCUTS_GROTTO_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #hole in a wooded maze# holds", /*french*/"", /*spanish*/"bajo un #hoyo de un laberinto forestal# yace"},
    });

    hintTable[DMT_STORMS_GROTTO_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#hole flooded with rain on a mountain# holds", /*french*/"", /*spanish*/"bajo un #hoyo de una montaña inundado de lluvia# yace"},
    });

    hintTable[DMC_UPPER_GROTTO_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #hole in a volcano# holds", /*french*/"", /*spanish*/"bajo un #hoyo de un volcán# yace"},
    });


    hintTable[TOT_LIGHT_ARROWS_CUTSCENE] = HintText::Exclude({
                       //obscure text
                       Text{"the #final gift of a princess# is", /*french*/"", /*spanish*/"el #obsequio final de la princesa# se trata de"},
    });

    hintTable[LW_GIFT_FROM_SARIA] = HintText::Exclude({
                       //obscure text
                       Text{"a #potato hoarder# holds",           /*french*/"", /*spanish*/"cierta #jovencita verde# concede"},
                       Text{"a rooty tooty #flutey cutey# gifts", /*french*/"", /*spanish*/"una #gran amiga# concede"},
                     },
                       //clear text
                       Text{"#Saria's Gift# is", /*french*/"", /*spanish*/"el #regalo de Saria# se trata de"}
    );

    hintTable[ZF_GREAT_FAIRY_REWARD] = HintText::Exclude({
                       //obscure text
                       Text{"the #fairy of winds# holds", /*french*/"", /*spanish*/"el #hada del viento# brinda"},
    });

    hintTable[HC_GREAT_FAIRY_REWARD] = HintText::Exclude({
                       //obscure text
                       Text{"the #fairy of fire# holds", /*french*/"", /*spanish*/"el #hada del fuego# brinda"},
    });

    hintTable[COLOSSUS_GREAT_FAIRY_REWARD] = HintText::Exclude({
                       //obscure text
                       Text{"the #fairy of love# holds", /*french*/"", /*spanish*/"el #hada del amor# brinda"},
    });

    hintTable[DMT_GREAT_FAIRY_REWARD] = HintText::Exclude({
                       //obscure text
                       Text{"a #magical fairy# gifts", /*french*/"", /*spanish*/"una #hada mágica# brinda"},
    });

    hintTable[DMC_GREAT_FAIRY_REWARD] = HintText::Exclude({
                       //obscure text
                       Text{"a #magical fairy# gifts", /*french*/"", /*spanish*/"una #hada máfica# brinda"},
    });

    hintTable[OGC_GREAT_FAIRY_REWARD] = HintText::Exclude({
                       //obscure text
                       Text{"the #fairy of strength# holds", /*french*/"", /*spanish*/"el #hada de la fuerza# brinda"},
    });


    hintTable[SONG_FROM_IMPA] = HintText::Exclude({
                       //obscure text
                       Text{"#deep in a castle#, Impa teaches", /*french*/"", /*spanish*/"al #fondo del castillo, Impa enseña#"},
    });

    hintTable[SONG_FROM_MALON] = HintText::Exclude({
                       //obscure text
                       Text{"#a farm girl# sings", /*french*/"", /*spanish*/"una #chica rupestre# canta"},
    });

    hintTable[SONG_FROM_SARIA] = HintText::Exclude({
                       //obscure text
                       Text{"#deep in the forest#, Saria teaches", /*french*/"", /*spanish*/"al #fondo del bosque#, Saria enseña"},
    });

    hintTable[SONG_FROM_WINDMILL] = HintText::Exclude({
                       //obscure text
                       Text{"a man #in a windmill# is obsessed with", /*french*/"", /*spanish*/"el #hombre del molino# está obsesionado con"},
    });


    hintTable[HC_MALON_EGG] = HintText::Exclude({
                       //obscure text
                       Text{"a #girl looking for her father# gives", /*french*/"", /*spanish*/"una #chica en busca de su padre# otorga"},
    });

    hintTable[HC_ZELDAS_LETTER] = HintText::Exclude({
                       //obscure text
                       Text{"a #princess in a castle# gifts", /*french*/"", /*spanish*/"la #princesa de un castillo# otorga"},
    });

    hintTable[ZD_DIVING_MINIGAME] = HintText::Exclude({
                       //obscure text
                       Text{"an #unsustainable business model# gifts", /*french*/"", /*spanish*/"un #mal modelo de negocio# premia con"},
                     },
                       //clear text
                       Text{"those who #dive for Zora rupees# will find", /*french*/"", /*spanish*/"aquellos que se #sumergan por las rupias Zora# encontrarán"}
    );

    hintTable[LH_CHILD_FISHING] = HintText::Exclude({
                       //obscure text
                       Text{"#fishing in youth# bestows", /*french*/"", /*spanish*/"#pescar en la juventud# conduce a"},
    });

    hintTable[LH_ADULT_FISHING] = HintText::Exclude({
                       //obscure text
                       Text{"#fishing in maturity# bestows", /*french*/"", /*spanish*/"#pescar en la madurez# conduce a"},
    });

    hintTable[LH_LAB_DIVE] = HintText::Exclude({
                       //obscure text
                       Text{"a #diving experiment# is rewarded with", /*french*/"", /*spanish*/"#bucear para un experimento# se premia con"},
    });

    hintTable[GC_ROLLING_GORON_AS_ADULT] = HintText::Exclude({
                       //obscure text
                       Text{"#comforting yourself# provides", /*french*/"", /*spanish*/"#confrontarte a ti mismo# otorga"},
                     },
                       //clear text
                       Text{"#reassuring a young Goron# is rewarded with", /*french*/"", /*spanish*/"#calmar a un joven Goron# otorga"}
    );

    hintTable[MARKET_BOMBCHU_BOWLING_FIRST_PRIZE] = HintText::Exclude({
                       //obscure text
                       Text{"the #first explosive prize# is", /*french*/"", /*spanish*/"el #primer premio explosivo# se trata de"},
    });

    hintTable[MARKET_BOMBCHU_BOWLING_SECOND_PRIZE] = HintText::Exclude({
                       //obscure text
                       Text{"the #second explosive prize# is", /*french*/"", /*spanish*/"el #segundo premio explosivo# se trata de"},
    });

    hintTable[MARKET_LOST_DOG] = HintText::Exclude({
                       //obscure text
                       Text{"#puppy lovers# will find", /*french*/"", /*spanish*/"los #amantes caninos# encontrarán"},
                     },
                       //clear text
                       Text{"#rescuing Richard the Dog# is rewarded with", /*french*/"", /*spanish*/"#rescatar al perro Ricardo# conduce a"}
    );

    hintTable[LW_OCARINA_MEMORY_GAME] = HintText::Exclude({
                       //obscure text
                       Text{"the prize for a #game of Simon Says# is", /*french*/"", /*spanish*/"#repetir ciertas melodías# otorga"},
                       Text{"a #child sing-a-long# holds",             /*french*/"", /*spanish*/"#tocar junto a otros# otorga"},
                     },
                       //clear text
                       Text{"#playing an Ocarina in Lost Woods# is rewarded with", /*french*/"", /*spanish*/"#tocar la ocarina en el Bosque Perdido# otorga"}
    );

    hintTable[KAK_10_GOLD_SKULLTULA_REWARD] = HintText::Exclude({
                       //obscure text
                       Text{"#10 bug badges# rewards",           /*french*/"", /*spanish*/"#10 medallas de insectos# otorgan"},
                       Text{"#10 spider souls# yields",          /*french*/"", /*spanish*/"#10 almas de araña# otorgan"},
                       Text{"#10 auriferous arachnids# lead to", /*french*/"", /*spanish*/"#10 arácnidos auríferos# otorgan"},
                     },
                       //clear text
                       Text{"slaying #10 Gold Skulltulas# reveals", /*french*/"", /*spanish*/"#exterminar 10 skulltulas doradas# revela"}
    );

    hintTable[KAK_MAN_ON_ROOF] = HintText::Exclude({
                       //obscure text
                       Text{"a #rooftop wanderer# holds", /*french*/"", /*spanish*/"#alguien sobre un tejado# otorga"},
    });

    hintTable[ZR_MAGIC_BEAN_SALESMAN] = HintText::Exclude({
                       //obscure text
                       Text{"a seller of #colorful crops# has", /*french*/"", /*spanish*/"el vendedor de un #colorido cultivo# ofrece"},
                     },
                       //clear text
                       Text{"a #bean seller# offers", /*french*/"", /*spanish*/"el #vendedor de judías# ofrece"}
    );

    hintTable[ZR_FROGS_IN_THE_RAIN] = HintText::Exclude({
                       //obscure text
                       Text{"#frogs in a storm# gift", /*french*/"", /*spanish*/"las #ancas bajo la tormenta# otorgan"},
    });

    hintTable[GF_HBA_1000_POINTS] = HintText::Exclude({
                       //obscure text
                       Text{"scoring 1000 in #horseback archery# grants", /*french*/"", /*spanish*/"conseguir 1000 puntos en el #tiro con arco a caballo# premia"},
    });

    hintTable[MARKET_SHOOTING_GALLERY_REWARD] = HintText::Exclude({
                       //obscure text
                       Text{"#shooting in youth# grants", /*french*/"", /*spanish*/"#disparar en la juventud# otorga"},
    });

    hintTable[KAK_SHOOTING_GALLERY_REWARD] = HintText::Exclude({
                       //obscure text
                       Text{"#shooting in maturity# grants", /*french*/"", /*spanish*/"#disparar en la madurez# otorga"},
    });

    hintTable[LW_TARGET_IN_WOODS] = HintText::Exclude({
                       //obscure text
                       Text{"shooting a #target in the woods# grants", /*french*/"", /*spanish*/"disparar a un #blanco forestal# brinda"},
    });

    hintTable[KAK_ANJU_AS_ADULT] = HintText::Exclude({
                       //obscure text
                       Text{"a #chicken caretaker# offers adults", /*french*/"", /*spanish*/"una #cuidadora de emplumados# le ofrece a los mayores"},
    });

    hintTable[LLR_TALONS_CHICKENS] = HintText::Exclude({
                       //obscure text
                       Text{"#finding Super Cuccos# is rewarded with", /*french*/"", /*spanish*/"#hallar los supercucos# conduce a"},
    });

    hintTable[GC_ROLLING_GORON_AS_CHILD] = HintText::Exclude({
                       //obscure text
                       Text{"the prize offered by a #large rolling Goron# is", /*french*/"", /*spanish*/"un #gran Goron rodante# otorga"},
    });

    hintTable[LH_UNDERWATER_ITEM] = HintText::Exclude({
                       //obscure text
                       Text{"the #sunken treasure in a lake# is", /*french*/"", /*spanish*/"el #tesoro hundido del lago# se trata de"},
    });

    hintTable[GF_GERUDO_TOKEN] = HintText::Exclude({
                       //obscure text
                       Text{"#rescuing captured carpenters# is rewarded with", /*french*/"", /*spanish*/"#rescatar los apresados carpinteros# se premia con"},
    });

    hintTable[WASTELAND_BOMBCHU_SALESMAN] = HintText::Exclude({
                       //obscure text
                       Text{"a #carpet guru# sells", /*french*/"", /*spanish*/"el #genio de una alfombra# vende"},
    });


    hintTable[KAK_IMPAS_HOUSE_FREESTANDING_POH] = HintText::Exclude({
                       //obscure text
                       Text{"#imprisoned in a house# lies", /*french*/"", /*spanish*/"#en una casa entre rejas# yace"},
    });

    hintTable[HF_TEKTITE_GROTTO_FREESTANDING_POH] = HintText::Exclude({
                       //obscure text
                       Text{"#deep underwater in a hole# is", /*french*/"", /*spanish*/"#en lo hondo bajo un hoyo# yace"},
    });

    hintTable[KAK_WINDMILL_FREESTANDING_POH] = HintText::Exclude({
                       //obscure text
                       Text{"on a #windmill ledge# lies", /*french*/"", /*spanish*/"al #borde de un molino# yace"},
    });

    hintTable[GRAVEYARD_DAMPE_RACE_FREESTANDING_POH] = HintText::Exclude({
                       //obscure text
                       Text{"#racing a ghost# leads to", /*french*/"", /*spanish*/"#perseguir a un fantasma# conduce a"},
                     },
                       //clear text
                       Text{"#dead Dampé's second# prize is", /*french*/"", /*spanish*/"el segundo premio de #Dampé fallecido# se trata de"}
    );

    hintTable[LLR_FREESTANDING_POH] = HintText::Exclude({
                       //obscure text
                       Text{"in a #ranch silo# lies", /*french*/"", /*spanish*/"en un #granero rupestre# yace"},
    });

    hintTable[GRAVEYARD_FREESTANDING_POH] = HintText::Exclude({
                       //obscure text
                       Text{"a #crate in a graveyard# hides", /*french*/"", /*spanish*/"bajo la #caja de un cementerio# yace"},
    });

    hintTable[GRAVEYARD_DAMPE_GRAVEDIGGING_TOUR] = HintText::Exclude({
                       //obscure text
                       Text{"a #gravekeeper digs up#", /*french*/"", /*spanish*/"cierto #sepultero desentierra#"},
    });

    hintTable[ZR_NEAR_OPEN_GROTTO_FREESTANDING_POH] = HintText::Exclude({
                       //obscure text
                       Text{"on top of a #pillar in a river# lies", /*french*/"", /*spanish*/"en lo alto del #pilar de un río# yace"},
    });

    hintTable[ZR_NEAR_DOMAIN_FREESTANDING_POH] = HintText::Exclude({
                       //obscure text
                       Text{"on a #river ledge by a waterfall# lies", /*french*/"", /*spanish*/"al borde #del río con una cascada# yace"},
    });

    hintTable[LH_FREESTANDING_POH] = HintText::Exclude({
                       //obscure text
                       Text{"high on a #lab rooftop# one can find", /*french*/"", /*spanish*/"en lo #alto de un laboratorio# yace"},
    });

    hintTable[ZF_ICEBERG_FREESTANDING_POH] = HintText::Exclude({
                       //obscure text
                       Text{"#floating on ice# is", /*french*/"", /*spanish*/"#flotando sobre hielo# yace"},
    });

    hintTable[GV_WATERFALL_FREESTANDING_POH] = HintText::Exclude({
                       //obscure text
                       Text{"behind a #desert waterfall# is", /*french*/"", /*spanish*/"tras una #desierta cascada# yace"},
    });

    hintTable[GV_CRATE_FREESTANDING_POH] = HintText::Exclude({
                       //obscure text
                       Text{"a #crate in a valley# hides", /*french*/"", /*spanish*/"bajo la #caja de un valle# yace"},
    });

    hintTable[COLOSSUS_FREESTANDING_POH] = HintText::Exclude({
                       //obscure text
                       Text{"on top of an #arch of stone# lies", /*french*/"", /*spanish*/"en lo alto de un #arco de piedra# yace"},
    });

    hintTable[DMT_FREESTANDING_POH] = HintText::Exclude({
                       //obscure text
                       Text{"above a #mountain cavern entrance# is", /*french*/"", /*spanish*/"en lo alto de la #entrada de una cueva en la montaña# yace"},
    });

    hintTable[DMC_WALL_FREESTANDING_POH] = HintText::Exclude({
                       //obscure text
                       Text{"nestled in a #volcanic wall# is", /*french*/"", /*spanish*/"entre unas #murallas volcánicas# yace"},
    });

    hintTable[DMC_VOLCANO_FREESTANDING_POH] = HintText::Exclude({
                       //obscure text
                       Text{"obscured by #volcanic ash# is", /*french*/"", /*spanish*/"bajo la #ceniza volcánica# yace"},
    });

    hintTable[GF_NORTH_F1_CARPENTER] = HintText::Exclude({
                       //obscure text
                       Text{"#defeating Gerudo guards# reveals", /*french*/"", /*spanish*/"#derrotar a las guardas Gerudo# revela"},
    });

    hintTable[GF_NORTH_F2_CARPENTER] = HintText::Exclude({
                       //obscure text
                       Text{"#defeating Gerudo guards# reveals", /*french*/"", /*spanish*/"#derrotar a las guardas Gerudo# revela"},
    });

    hintTable[GF_SOUTH_F1_CARPENTER] = HintText::Exclude({
                       //obscure text
                       Text{"#defeating Gerudo guards# reveals", /*french*/"", /*spanish*/"#derrotar a las guardas Gerudo# revela"},
    });

    hintTable[GF_SOUTH_F2_CARPENTER] = HintText::Exclude({
                       //obscure text
                       Text{"#defeating Gerudo guards# reveals", /*french*/"", /*spanish*/"#derrotar a las guardas Gerudo# revela"},
    });


    hintTable[DEKU_TREE_MAP_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"in the #center of the Deku Tree# lies", /*french*/"", /*spanish*/"al #centro del Árbol Deku# yace"},
    });

    hintTable[DEKU_TREE_SLINGSHOT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #treasure guarded by a scrub# in the Deku Tree is", /*french*/"", /*spanish*/"un #deku del Árbol Deku# esconde"},
    });

    hintTable[DEKU_TREE_SLINGSHOT_ROOM_SIDE_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #treasure guarded by a scrub# in the Deku Tree is", /*french*/"", /*spanish*/"un #deku del Árbol Deku# esconde"},
    });

    hintTable[DEKU_TREE_COMPASS_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#pillars of wood# in the Deku Tree lead to", /*french*/"", /*spanish*/"los #salientes del Árbol Deku# conducen a"},
    });

    hintTable[DEKU_TREE_COMPASS_ROOM_SIDE_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#pillars of wood# in the Deku Tree lead to", /*french*/"", /*spanish*/"los #salientes del Árbol Deku# conducen a"},
    });

    hintTable[DEKU_TREE_BASEMENT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#webs in the Deku Tree# hide", /*french*/"", /*spanish*/"entre #telarañas del Árbol Deku# yace"},
    });


    hintTable[DEKU_TREE_MQ_MAP_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"in the #center of the Deku Tree# lies", /*french*/"", /*spanish*/"al #centro del Árbol Deku# yace"},
    });

    hintTable[DEKU_TREE_MQ_COMPASS_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #treasure guarded by a large spider# in the Deku Tree is", /*french*/"", /*spanish*/"una #araña del Árbol Deku# esconde"},
    });

    hintTable[DEKU_TREE_MQ_SLINGSHOT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#pillars of wood# in the Deku Tree lead to", /*french*/"", /*spanish*/"los #salientes del Árbol Deku# conducen a"},
    });

    hintTable[DEKU_TREE_MQ_SLINGSHOT_ROOM_BACK_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#pillars of wood# in the Deku Tree lead to", /*french*/"", /*spanish*/"los #salientes del Árbol Deku# conducen a"},
    });

    hintTable[DEKU_TREE_MQ_BASEMENT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#webs in the Deku Tree# hide", /*french*/"", /*spanish*/"entre #telarañas del Árbol Deku# yace"},
    });

    hintTable[DEKU_TREE_MQ_BEFORE_SPINNING_LOG_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#magical fire in the Deku Tree# leads to", /*french*/"", /*spanish*/"el #fuego mágico en el Árbol Deku# conduce a"},
    });


    hintTable[DODONGOS_CAVERN_BOSS_ROOM_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#above King Dodongo# lies", /*french*/"", /*spanish*/"#sobre el Rey Dodongo# yace"},
    });


    hintTable[DODONGOS_CAVERN_MAP_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #muddy wall in Dodongo's Cavern# hides", /*french*/"", /*spanish*/"tras una #agrietada pared en la Caverna de los Dodongos# yace"},
    });

    hintTable[DODONGOS_CAVERN_COMPASS_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #statue in Dodongo's Cavern# guards", /*french*/"", /*spanish*/"una #estatua de la Caverna de los Dodongos# esconde"},
    });

    hintTable[DODONGOS_CAVERN_BOMB_FLOWER_PLATFORM_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"above a #maze of stone# in Dodongo's Cavern lies", /*french*/"", /*spanish*/"entre un #laberinto de piedra# en la Cueva de los Dodongos# yace"},
    });

    hintTable[DODONGOS_CAVERN_BOMB_BAG_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #second lizard cavern battle# yields", /*french*/"", /*spanish*/"#luchar dos veces contra reptiles en una cueva# conduce a"},
    });

    hintTable[DODONGOS_CAVERN_END_OF_BRIDGE_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #chest at the end of a bridge# yields", /*french*/"", /*spanish*/"un #cofre al final de un quebrado puente# otorga"},
    });


    hintTable[DODONGOS_CAVERN_MQ_MAP_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #muddy wall in Dodongo's Cavern# hides", /*french*/"", /*spanish*/"una #quebrada pared en la Cueva de los Dodongos# esconde"},
    });

    hintTable[DODONGOS_CAVERN_MQ_BOMB_BAG_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"an #elevated alcove# in Dodongo's Cavern holds", /*french*/"", /*spanish*/"una #elevada alcoba# en la Caverna de los Dongos# brinda"},
    });

    hintTable[DODONGOS_CAVERN_MQ_COMPASS_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#fire-breathing lizards# in Dodongo's Cavern guard", /*french*/"", /*spanish*/"unos #lagartos de fuego# en la Cueva de los Dodongos# esconden"},
    });

    hintTable[DODONGOS_CAVERN_MQ_LARVAE_ROOM_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#baby spiders# in Dodongo's Cavern guard", /*french*/"", /*spanish*/"unas #pequeñas larvas# en la Cueva de los Dodongos esconden"},
    });

    hintTable[DODONGOS_CAVERN_MQ_TORCH_PUZZLE_ROOM_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"above a #maze of stone# in Dodongo's Cavern lies", /*french*/"", /*spanish*/"sobre un #laberinto de piedra# en la Cueva de los Dodongos yace"},
    });

    hintTable[DODONGOS_CAVERN_MQ_UNDER_GRAVE_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#beneath a headstone# in Dodongo's Cavern lies", /*french*/"", /*spanish*/"#bajo una lápida# en la Cueva de los Dodongos yace"},
    });


    hintTable[JABU_JABUS_BELLY_MAP_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#tentacle trouble# in a deity's belly guards", /*french*/"", /*spanish*/"un #problema tentaculoso# en la tripa de cierta deidad esconde"},
                     },
                       //clear text
                       Text{"a #slimy thing# guards", /*french*/"", /*spanish*/"un #tentáculo parasitario# protege"}
    );

    hintTable[JABU_JABUS_BELLY_COMPASS_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#bubble trouble# in a deity's belly guards", /*french*/"", /*spanish*/"un #problema burbujesco# en la tripa de cierta deidad esconde"},
                     },
                       //clear text
                       Text{"#bubbles# guard", /*french*/"", /*spanish*/"unas #burbujas# protegen"}
    );


    hintTable[JABU_JABUS_BELLY_MQ_FIRST_ROOM_SIDE_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"shooting a #mouth cow# reveals", /*french*/"", /*spanish*/"#dispararle a una vaca# revela"},
    });

    hintTable[JABU_JABUS_BELLY_MQ_MAP_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#pop rocks# hide",            /*french*/"", /*spanish*/"#cepillarse los dientes con explosivos# revela"},
                       Text{"an #explosive palate# holds", /*french*/"", /*spanish*/"un #paladar explosivo# esconde"},
                     },
                       //clear text
                       Text{"a #boulder before cows# hides", /*french*/"", /*spanish*/"cierta #roca con unas vacas# esconde"}
    );

    hintTable[JABU_JABUS_BELLY_MQ_SECOND_ROOM_LOWER_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"near a #spiked elevator# lies", /*french*/"", /*spanish*/"cerca de un #ascensor puntiagudo# yace"},
    });

    hintTable[JABU_JABUS_BELLY_MQ_COMPASS_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #drowning cow# unveils", /*french*/"", /*spanish*/"una #vaca sumergida# revela"},
    });

    hintTable[JABU_JABUS_BELLY_MQ_SECOND_ROOM_UPPER_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#moving anatomy# creates a path to", /*french*/"", /*spanish*/"un #ser movedizo entre paredes# conduce a"},
    });

    hintTable[JABU_JABUS_BELLY_MQ_BASEMENT_NEAR_SWITCHES_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #pair of digested cows# hold", /*french*/"", /*spanish*/"un #par de digeridas vacas# otorgan"},
    });

    hintTable[JABU_JABUS_BELLY_MQ_BASEMENT_NEAR_VINES_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #pair of digested cows# hold", /*french*/"", /*spanish*/"un #par de digeridas vacas# otorgan"},
    });

    hintTable[JABU_JABUS_BELLY_MQ_NEAR_BOSS_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #final cows' reward# in a deity's belly is", /*french*/"", /*spanish*/"las #vacas al final# de la tripa de cierta deidad otorgan"},
    });

    hintTable[JABU_JABUS_BELLY_MQ_FALLING_LIKE_LIKE_ROOM_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#cows protected by falling monsters# in a deity's belly guard", /*french*/"", /*spanish*/"unas #vacas custodiadas por monstruos del techo# de la tripa de cierta deidad otorgan"},
    });

    hintTable[JABU_JABUS_BELLY_MQ_BOOMERANG_ROOM_SMALL_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a school of #stingers swallowed by a deity# guard", /*french*/"", /*spanish*/"un puñado de #stingers engullidos por cierta deidad# guardan"},
                     },
                       //clear text
                       Text{"a school of #stingers swallowed by Jabu Jabu# guard", /*french*/"", /*spanish*/"un puñado de #stingers engullidos por Jabu Jabu# guardan"}
    );

    hintTable[JABU_JABUS_BELLY_MQ_BOOMERANG_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a school of #stingers swallowed by a deity# guard", /*french*/"", /*spanish*/"un puñado de #stingers engullidos por cierta deidad# guardan"},
                     },
                       //clear text
                       Text{"a school of #stingers swallowed by Jabu Jabu# guard", /*french*/"", /*spanish*/"un puñado de #stingers engullidos por Jabu Jabu# guardan"}
    );

    hintTable[FOREST_TEMPLE_FIRST_ROOM_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #tree in the Forest Temple# supports", /*french*/"", /*spanish*/"sobre un #árbol del Templo del Bosque# yace"},
    });

    hintTable[FOREST_TEMPLE_FIRST_STALFOS_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#defeating enemies beneath a falling ceiling# in Forest Temple yields", /*french*/"", /*spanish*/"#derrotar enemigos caídos de lo alto# del Templo del Bosque revela"},
    });

    hintTable[FOREST_TEMPLE_WELL_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #sunken chest deep in the woods# contains", /*french*/"", /*spanish*/"un #sumergido cofre en lo profundo del bosque# contiene"},
    });

    hintTable[FOREST_TEMPLE_MAP_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #fiery skull# in Forest Temple guards", /*french*/"", /*spanish*/"una #ardiente calavera# del Templo del Bosque esconde"},
    });

    hintTable[FOREST_TEMPLE_RAISED_ISLAND_COURTYARD_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #chest on a small island# in the Forest Temple holds", /*french*/"", /*spanish*/"un #cofre sobre una isla# del Templo del Bosque contiene"},
    });

    hintTable[FOREST_TEMPLE_FALLING_CEILING_ROOM_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"beneath a #checkerboard falling ceiling# lies", /*french*/"", /*spanish*/"tras un #techo de ajedrez# yace"},
    });

    hintTable[FOREST_TEMPLE_EYE_SWITCH_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #sharp eye# will spot", /*french*/"", /*spanish*/"un #afilado ojo# revela"},
                     },
                       //clear text
                       Text{"#blocks of stone# in the Forest Temple surround", /*french*/"", /*spanish*/"cerca de unos #bloques de piedra# del Templo del Bosque yace"}
    );

    hintTable[FOREST_TEMPLE_BOSS_KEY_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #turned trunk# contains", /*french*/"", /*spanish*/"en una #sala con otro punto de vista# se esconde"},
    });

    hintTable[FOREST_TEMPLE_FLOORMASTER_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"deep in the forest #shadows guard a chest# containing", /*french*/"", /*spanish*/"en lo profundo del bosque #unas sombras# esconden"},
    });

    hintTable[FOREST_TEMPLE_BOW_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"an #army of the dead# guards", /*french*/"", /*spanish*/"un #ejército de soldados caídos# guardan"},
                     },
                       //clear text
                       Text{"#Stalfos deep in the Forest Temple# guard", /*french*/"", /*spanish*/"los #Stalfos en lo profundo del Templo del Bosque# guardan"}
    );

    hintTable[FOREST_TEMPLE_RED_POE_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#Joelle# guards", /*french*/"", /*spanish*/"#Joelle# guarda"},
                     },
                       //clear text
                       Text{"a #red ghost# guards", /*french*/"", /*spanish*/"un #espectro rojo# guarda"}
    );

    hintTable[FOREST_TEMPLE_BLUE_POE_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#Beth# guards", /*french*/"", /*spanish*/"#Beth# guarda"},
                     },
                       //clear text
                       Text{"a #blue ghost# guards", /*french*/"", /*spanish*/"un #espectro azul# guarda"}
    );

    hintTable[FOREST_TEMPLE_BASEMENT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#revolving walls# in the Forest Temple conceal", /*french*/"", /*spanish*/"las #paredes giratorias# del Templo del Bosque conceden"},
    });


    hintTable[FOREST_TEMPLE_MQ_FIRST_ROOM_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #tree in the Forest Temple# supports", /*french*/"", /*spanish*/"sobre un #árbol del Templo del Bosque# yace"},
    });

    hintTable[FOREST_TEMPLE_MQ_WOLFOS_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#defeating enemies beneath a falling ceiling# in Forest Temple yields", /*french*/"", /*spanish*/"#derrotar enemigos caídos de lo alto# del Templo del Bosque revela"},
    });

    hintTable[FOREST_TEMPLE_MQ_BOW_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"an #army of the dead# guards", /*french*/"", /*spanish*/"un #ejército de soldados caídos# guardan"},
                     },
                       //clear text
                       Text{"#Stalfos deep in the Forest Temple# guard", /*french*/"", /*spanish*/"los #Stalfos en lo profundo del Templo del Bosque# guardan"}
    );

    hintTable[FOREST_TEMPLE_MQ_RAISED_ISLAND_COURTYARD_LOWER_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #chest on a small island# in the Forest Temple holds", /*french*/"", /*spanish*/"un #cofre sobre una isla# del Templo del Bosque contiene"},
    });

    hintTable[FOREST_TEMPLE_MQ_RAISED_ISLAND_COURTYARD_UPPER_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#high in a courtyard# within the Forest Temple is", /*french*/"", /*spanish*/"un #cofre en lo alto de un patio# del Templo del Bosque contiene"},
    });

    hintTable[FOREST_TEMPLE_MQ_WELL_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #sunken chest deep in the woods# contains", /*french*/"", /*spanish*/"un #sumergido cofre en lo profundo del bosque# contiene"},
    });

    hintTable[FOREST_TEMPLE_MQ_MAP_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#Joelle# guards", /*french*/"", /*spanish*/"#Joelle# guarda"},
                     },
                       //clear text
                       Text{"a #red ghost# guards", /*french*/"", /*spanish*/"un #fantasma rojo# guarda"}
    );

    hintTable[FOREST_TEMPLE_MQ_COMPASS_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#Beth# guards", /*french*/"", /*spanish*/"#Beth# guarda"},
                     },
                       //clear text
                       Text{"a #blue ghost# guards", /*french*/"", /*spanish*/"un #fantasma azul# guarda"}
    );

    hintTable[FOREST_TEMPLE_MQ_FALLING_CEILING_ROOM_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"beneath a #checkerboard falling ceiling# lies", /*french*/"", /*spanish*/"tras un #techo de ajedrez# yace"},
    });

    hintTable[FOREST_TEMPLE_MQ_BASEMENT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#revolving walls# in the Forest Temple conceal", /*french*/"", /*spanish*/"las #paredes giratorias# del Templo del Bosque conceden"},
    });

    hintTable[FOREST_TEMPLE_MQ_REDEAD_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"deep in the forest #undead guard a chest# containing", /*french*/"", /*spanish*/"en lo profundo del bosque #guardias del más allá# guardan"},
    });

    hintTable[FOREST_TEMPLE_MQ_BOSS_KEY_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #turned trunk# contains", /*french*/"", /*spanish*/"en una #sala con otro punto de vista# se esconde"},
    });


    hintTable[FIRE_TEMPLE_NEAR_BOSS_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#near a dragon# is", /*french*/"", /*spanish*/"#cerca de un dragón# yace"},
    });

    hintTable[FIRE_TEMPLE_FLARE_DANCER_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #Flare Dancer behind a totem# guards", /*french*/"", /*spanish*/"el #Bailafuego tras unos tótems# esconde"},
    });

    hintTable[FIRE_TEMPLE_BOSS_KEY_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #prison beyond a totem# holds", /*french*/"", /*spanish*/"en una #prisión tras unos tótems# yace"},
    });

    hintTable[FIRE_TEMPLE_BIG_LAVA_ROOM_BLOCKED_DOOR_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#explosives over a lava pit# unveil", /*french*/"", /*spanish*/"los #explosivos en un mar de llamas# revelan"},
    });

    hintTable[FIRE_TEMPLE_BIG_LAVA_ROOM_LOWER_OPEN_DOOR_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron trapped near lava# holds", /*french*/"", /*spanish*/"un #goron atrapado cerca de un mar de llamas# guarda"},
    });

    hintTable[FIRE_TEMPLE_BOULDER_MAZE_LOWER_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron at the end of a maze# holds", /*french*/"", /*spanish*/"un #goron al final de un laberinto# guarda"},
    });

    hintTable[FIRE_TEMPLE_BOULDER_MAZE_UPPER_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron above a maze# holds", /*french*/"", /*spanish*/"un #goron sobre un laberinto# guarda"},
    });

    hintTable[FIRE_TEMPLE_BOULDER_MAZE_SIDE_ROOM_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron hidden near a maze# holds", /*french*/"", /*spanish*/"un #goron escondido tras un laberinto# guarda"},
    });

    hintTable[FIRE_TEMPLE_BOULDER_MAZE_SHORTCUT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #blocked path# in Fire Temple holds", /*french*/"", /*spanish*/"en un #camino bloqueado# del Templo del Fuego yace"},
    });

    hintTable[FIRE_TEMPLE_MAP_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #caged chest# in the Fire Temple hoards", /*french*/"", /*spanish*/"un #cofre entre rejas# del Templo del Fuego contiene"},
    });

    hintTable[FIRE_TEMPLE_COMPASS_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #chest in a fiery maze# contains", /*french*/"", /*spanish*/"un #cofre de un ardiente laberinto# contiene"},
    });

    hintTable[FIRE_TEMPLE_HIGHEST_GORON_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron atop the Fire Temple# holds", /*french*/"", /*spanish*/"un #goron en lo alto del Templo del Fuego# guarda"},
    });


    hintTable[FIRE_TEMPLE_MQ_NEAR_BOSS_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#near a dragon# is", /*french*/"", /*spanish*/"#cerca de un dragón# yace"},
    });

    hintTable[FIRE_TEMPLE_MQ_MEGATON_HAMMER_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #Flare Dancer in the depths of a volcano# guards", /*french*/"", /*spanish*/"el #Bailafuego en lo profundo del volcán# esconde"},
                     },
                       //clear text
                       Text{"the #Flare Dancer in the depths of the Fire Temple# guards", /*french*/"", /*spanish*/"el #Bailafuego en lo profundo del Templo del Fuego# esconde"}
    );

    hintTable[FIRE_TEMPLE_MQ_COMPASS_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #blocked path# in Fire Temple holds", /*french*/"", /*spanish*/"en un #camino bloqueado# del Templo del Fuego yace"},
    });

    hintTable[FIRE_TEMPLE_MQ_LIZALFOS_MAZE_LOWER_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#crates in a maze# contain", /*french*/"", /*spanish*/"las #cajas de un laberinto# contienen"},
    });

    hintTable[FIRE_TEMPLE_MQ_LIZALFOS_MAZE_UPPER_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#crates in a maze# contain", /*french*/"", /*spanish*/"las #cajas de un laberinto# contienen"},
    });

    hintTable[FIRE_TEMPLE_MQ_MAP_ROOM_SIDE_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #falling slug# in the Fire Temple guards", /*french*/"", /*spanish*/"una #babosa del techo# del Templo del Fuego guarda"},
    });

    hintTable[FIRE_TEMPLE_MQ_MAP_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"using a #hammer in the depths of the Fire Temple# reveals", /*french*/"", /*spanish*/"usar el #martillo en lo profundo del Templo del Fuego# revela"},
    });

    hintTable[FIRE_TEMPLE_MQ_BOSS_KEY_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#illuminating a lava pit# reveals the path to", /*french*/"", /*spanish*/"#iluminar un mar de llamas# revela"},
    });

    hintTable[FIRE_TEMPLE_MQ_BIG_LAVA_ROOM_BLOCKED_DOOR_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#explosives over a lava pit# unveil", /*french*/"", /*spanish*/"los #explosivos en un mar de llamas# revelan"},
    });

    hintTable[FIRE_TEMPLE_MQ_LIZALFOS_MAZE_SIDE_ROOM_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron hidden near a maze# holds", /*french*/"", /*spanish*/"un #goron cerca de un laberinto# guarda"},
    });

    hintTable[FIRE_TEMPLE_MQ_FREESTANDING_KEY] = HintText::Exclude({
                       //obscure text
                       Text{"hidden #beneath a block of stone# lies", /*french*/"", /*spanish*/"#bajo unos bloques de piedra# yace"},
    });


    hintTable[WATER_TEMPLE_MAP_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#rolling spikes# in the Water Temple surround", /*french*/"", /*spanish*/"unas #rodantes púas# del Templo del Agua guardan"},
    });

    hintTable[WATER_TEMPLE_COMPASS_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#roaming stingers in the Water Temple# guard", /*french*/"", /*spanish*/"unos #errantes stingers# del Templo del Agua guardan"},
    });

    hintTable[WATER_TEMPLE_TORCHES_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#fire in the Water Temple# reveals", /*french*/"", /*spanish*/"el #fuego en el Templo del Agua# revela"},
    });

    hintTable[WATER_TEMPLE_DRAGON_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #serpent's prize# in the Water Temple is", /*french*/"", /*spanish*/"el #escamado premio# del Templo del Agua se trata de"},
    });

    hintTable[WATER_TEMPLE_CENTRAL_BOW_TARGET_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#blinding an eye# in the Water Temple leads to", /*french*/"", /*spanish*/"#cegar un ojo# del Templo del Agua conduce a"},
    });

    hintTable[WATER_TEMPLE_CENTRAL_PILLAR_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"in the #depths of the Water Temple# lies", /*french*/"", /*spanish*/"en las #profundidades del Templo del Agua yace"},
    });

    hintTable[WATER_TEMPLE_CRACKED_WALL_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#through a crack# in the Water Temple is", /*french*/"", /*spanish*/"tras una #agrietada pared# del Templo del Agua yace"},
    });

    hintTable[WATER_TEMPLE_LONGSHOT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#facing yourself# reveals",              /*french*/"", /*spanish*/"#luchar contra ti mismo# revela"},
                       Text{"a #dark reflection# of yourself guards", /*french*/"", /*spanish*/"el #oscuro reflejo de ti mismo# guarda"},
                     },
                       //clear text
                       Text{"#Dark Link# guards", /*french*/"", /*spanish*/"#Link Oscuro# guarda"}
    );


    hintTable[WATER_TEMPLE_MQ_CENTRAL_PILLAR_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"in the #depths of the Water Temple# lies", /*french*/"", /*spanish*/"en las #profundidades del Templo del Agua# yace"},
    });

    hintTable[WATER_TEMPLE_MQ_BOSS_KEY_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"fire in the Water Temple unlocks a #vast gate# revealing a chest with", /*french*/"", /*spanish*/"el fuego en el Templo del Agua alza una #gran valla#, habiendo dentro"},
    });

    hintTable[WATER_TEMPLE_MQ_LONGSHOT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#through a crack# in the Water Temple is", /*french*/"", /*spanish*/"tras una #agrietada pared# del Templo del Agua yace"},
    });

    hintTable[WATER_TEMPLE_MQ_COMPASS_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#fire in the Water Temple# reveals", /*french*/"", /*spanish*/"el #fuego en el Templo del Agua# revela"},
    });

    hintTable[WATER_TEMPLE_MQ_MAP_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#sparring soldiers# in the Water Temple guard", /*french*/"", /*spanish*/"#acabar con unos soldados# del Templo del Agua revela"},
    });


    hintTable[SPIRIT_TEMPLE_CHILD_BRIDGE_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a child conquers a #skull in green fire# in the Spirit Temple to reach", /*french*/"", /*spanish*/"el joven que #acabe con la calavera de verde fuego# del Templo del Espíritu encontrará"},
    });

    hintTable[SPIRIT_TEMPLE_CHILD_EARLY_TORCHES_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a child can find a #caged chest# in the Spirit Temple with", /*french*/"", /*spanish*/"un joven puede encontrar un #cofre entre rejas# del Templo del Espíritu con"},
    });

    hintTable[SPIRIT_TEMPLE_COMPASS_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#across a pit of sand# in the Spirit Temple lies", /*french*/"", /*spanish*/"tras un #pozo de arena# del Templo del Espíritu yace"},
    });

    hintTable[SPIRIT_TEMPLE_EARLY_ADULT_RIGHT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#dodging boulders to collect silver rupees# in the Spirit Temple yields", /*french*/"", /*spanish*/"#esquivar rocas y conseguir plateadas rupias# en el Templo del Espíritu conduce a"},
    });

    hintTable[SPIRIT_TEMPLE_FIRST_MIRROR_LEFT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #shadow circling reflected light# in the Spirit Temple guards", /*french*/"", /*spanish*/"un #círculo de reflectante luz# del Templo del Espíritu guarda"},
    });

    hintTable[SPIRIT_TEMPLE_FIRST_MIRROR_RIGHT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #shadow circling reflected light# in the Spirit Temple guards", /*french*/"", /*spanish*/"un #círculo de reflectante luz# del Templo del Espíritu guarda"},
    });

    hintTable[SPIRIT_TEMPLE_MAP_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#before a giant statue# in the Spirit Temple lies", /*french*/"", /*spanish*/"#ante una gran estatua# del Templo del Espíritu aguarda"},
    });

    hintTable[SPIRIT_TEMPLE_CHILD_CLIMB_NORTH_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#lizards in the Spirit Temple# guard", /*french*/"", /*spanish*/"los #reptiles del Templo del Espíritu# guardan"},
    });

    hintTable[SPIRIT_TEMPLE_CHILD_CLIMB_EAST_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#lizards in the Spirit Temple# guard", /*french*/"", /*spanish*/"los #reptiles del Templo del Espíritu# guardan"},
    });

    hintTable[SPIRIT_TEMPLE_SUN_BLOCK_ROOM_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#torchlight among Beamos# in the Spirit Temple reveals", /*french*/"", /*spanish*/"las #antorchas junto a Beamos# del Templo del Espíritu revelan"},
    });

    hintTable[SPIRIT_TEMPLE_STATUE_ROOM_HAND_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #statue in the Spirit Temple# holds", /*french*/"", /*spanish*/"una #estatua del Templo del Espíritu# esconde"},
    });

    hintTable[SPIRIT_TEMPLE_STATUE_ROOM_NORTHEAST_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"on a #ledge by a statue# in the Spirit Temple rests", /*french*/"", /*spanish*/"al #borde de una estatua# del Templo del Espíritu yace"},
    });

    hintTable[SPIRIT_TEMPLE_NEAR_FOUR_ARMOS_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"those who #show the light among statues# in the Spirit Temple find", /*french*/"", /*spanish*/"aquellos que #iluminen ante las estatuas# del Templo del Espíritu encontrarán"},
    });

    hintTable[SPIRIT_TEMPLE_HALLWAY_RIGHT_INVISIBLE_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth in the Spirit Temple# reveals", /*french*/"", /*spanish*/"el #Ojo de la Verdad# en el Templo del Espíritu revela"},
    });

    hintTable[SPIRIT_TEMPLE_HALLWAY_LEFT_INVISIBLE_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth in the Spirit Temple# reveals", /*french*/"", /*spanish*/"el #Ojo de la Verdad# en el Templo del Espíritu revela"},
    });

    hintTable[SPIRIT_TEMPLE_BOSS_KEY_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #chest engulfed in flame# in the Spirit Temple holds", /*french*/"", /*spanish*/"un #cofre rodeado de llamas# del Templo del Espíritu contiene"},
    });

    hintTable[SPIRIT_TEMPLE_TOPMOST_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"those who #show the light above the Colossus# find", /*french*/"", /*spanish*/"aquellos que #iluminen en lo alto del Coloso# encontrarán"},
    });


    hintTable[SPIRIT_TEMPLE_MQ_ENTRANCE_FRONT_LEFT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#lying unguarded# in the Spirit Temple is", /*french*/"", /*spanish*/"en la #entrada del Templo del Espíritu# yace"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_ENTRANCE_BACK_RIGHT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #switch in a pillar# within the Spirit Temple drops", /*french*/"", /*spanish*/"el #interruptor de un pilar# del Templo del Espíritu revela"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_ENTRANCE_FRONT_RIGHT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#collecting rupees through a water jet# reveals", /*french*/"", /*spanish*/"#hacerte con rupias tras un géiser# revela"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_ENTRANCE_BACK_LEFT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"an #eye blinded by stone# within the Spirit Temple conceals", /*french*/"", /*spanish*/"#cegar a un ojo# del Templo del Espíritu revela"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_MAP_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"surrounded by #fire and wrappings# lies", /*french*/"", /*spanish*/"rodeado de #fuego y vendas# yace"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_MAP_ROOM_ENEMY_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a child defeats a #gauntlet of monsters# within the Spirit Temple to find", /*french*/"", /*spanish*/"el joven que derrote un #puñado de monstruos# del Templo del Espíritu encontrará"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_CHILD_CLIMB_NORTH_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#explosive sunlight# within the Spirit Temple uncovers", /*french*/"", /*spanish*/"una #explosiva luz solar# del Templo del Espíritu revela"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_CHILD_CLIMB_SOUTH_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#trapped by falling enemies# within the Spirit Temple is", /*french*/"", /*spanish*/"#rodeado de enemigos del cielo# del Templo del Espíritu yace"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_COMPASS_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#blinding the colossus# unveils", /*french*/"", /*spanish*/"#cegar al coloso# revela"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_STATUE_ROOM_LULLABY_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #royal melody awakens the colossus# to reveal", /*french*/"", /*spanish*/"la #melodía real que despierte al coloso# revelará"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_STATUE_ROOM_INVISIBLE_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth# finds the colossus's hidden", /*french*/"", /*spanish*/"el #Ojo de la Verdad# en el Templo del Espíritu encuentra"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_SILVER_BLOCK_HALLWAY_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#the old hide what the young find# to reveal", /*french*/"", /*spanish*/"el #adulto esconde lo que el joven anhela# de encontrar"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_SUN_BLOCK_ROOM_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#sunlight in a maze of fire# hides", /*french*/"", /*spanish*/"la #luz solar de un ígneo laberinto# esconde"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_LEEVER_ROOM_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#across a pit of sand# in the Spirit Temple lies", /*french*/"", /*spanish*/"#a través del pozo de arena# del Templo del Espíritu yace"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_BEAMOS_ROOM_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"where #temporal stone blocks the path# within the Spirit Temple lies", /*french*/"", /*spanish*/"donde los #bloques temporales bloquean# en el Templo del Espíritu yace"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_CHEST_SWITCH_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #chest of double purpose# holds", /*french*/"", /*spanish*/"un #cofre de doble uso# contiene"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_BOSS_KEY_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #temporal stone blocks the light# leading to", /*french*/"", /*spanish*/"un #bloque temporal bloquea la luz# que conduce a"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_MIRROR_PUZZLE_INVISIBLE_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"those who #show the light above the Colossus# find", /*french*/"", /*spanish*/"aquellos que #revelen la luz sobre el Coloso# encontrarán"},
    });

    hintTable[SHADOW_TEMPLE_MAP_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth# pierces a hall of faces to reveal", /*french*/"", /*spanish*/"el #Ojo de la Verdad# descubre un pasillo de facetas con"},
    });

    hintTable[SHADOW_TEMPLE_HOVER_BOOTS_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #nether dweller in the Shadow Temple# holds", /*french*/"", /*spanish*/"un #temido morador del Templo de las Sombras# guarda"},
                     },
                       //clear text
                       Text{"#Dead Hand in the Shadow Temple# holds", /*french*/"", /*spanish*/"la #Mano Muerta del Templo de las Sombras# guarda"}
    );

    hintTable[SHADOW_TEMPLE_COMPASS_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#mummies revealed by the Eye of Truth# guard", /*french*/"", /*spanish*/"las #momias reveladas por el Ojo de la Verdad# guardan"},
    });

    hintTable[SHADOW_TEMPLE_EARLY_SILVER_RUPEE_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#spinning scythes# protect", /*french*/"", /*spanish*/"las #giratorias guadañas# protegen"},
    });

    hintTable[SHADOW_TEMPLE_INVISIBLE_BLADES_VISIBLE_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#invisible blades# guard", /*french*/"", /*spanish*/"las #hojas invisibles# guardan"},
    });

    hintTable[SHADOW_TEMPLE_INVISIBLE_BLADES_INVISIBLE_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#invisible blades# guard", /*french*/"", /*spanish*/"las #hojas invisibles# guardan"},
    });

    hintTable[SHADOW_TEMPLE_FALLING_SPIKES_LOWER_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#falling spikes# block the path to", /*french*/"", /*spanish*/"los #pinchos del techo# conducen a"},
    });

    hintTable[SHADOW_TEMPLE_FALLING_SPIKES_UPPER_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#falling spikes# block the path to", /*french*/"", /*spanish*/"los #pinchos del techo# conducen a"},
    });

    hintTable[SHADOW_TEMPLE_FALLING_SPIKES_SWITCH_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#falling spikes# block the path to", /*french*/"", /*spanish*/"los #pinchos del techo# conducen a"},
    });

    hintTable[SHADOW_TEMPLE_INVISIBLE_SPIKES_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #dead roam among invisible spikes# guarding", /*french*/"", /*spanish*/"los #muertos que vagan por pinchos invisibles# protegen"},
    });

    hintTable[SHADOW_TEMPLE_WIND_HINT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"an #invisible chest guarded by the dead# holds", /*french*/"", /*spanish*/"un #cofre invisible custodiado por los del más allá# contiene"},
    });

    hintTable[SHADOW_TEMPLE_AFTER_WIND_ENEMY_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#mummies guarding a ferry# hide", /*french*/"", /*spanish*/"las #momias que protegen un navío# esconden"},
    });

    hintTable[SHADOW_TEMPLE_AFTER_WIND_HIDDEN_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#mummies guarding a ferry# hide", /*french*/"", /*spanish*/"las #momias que protegen un navío# esconden"},
    });

    hintTable[SHADOW_TEMPLE_SPIKE_WALLS_LEFT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#walls consumed by a ball of fire# reveal", /*french*/"", /*spanish*/"las #paredes consumidas por una esfera ígnea# revelan"},
    });

    hintTable[SHADOW_TEMPLE_BOSS_KEY_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#walls consumed by a ball of fire# reveal", /*french*/"", /*spanish*/"las #paredes consumidas por una esfera ígnea# revelan"},
    });

    hintTable[SHADOW_TEMPLE_FREESTANDING_KEY] = HintText::Exclude({
                       //obscure text
                       Text{"#inside a burning skull# lies", /*french*/"", /*spanish*/"en el #interior de una calavera en llamas# aguarda"},
    });

    hintTable[SHADOW_TEMPLE_MQ_COMPASS_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth# pierces a hall of faces to reveal", /*french*/"", /*spanish*/"el #Ojo de la Verdad# descubre un pasillo de facetas con"},
    });

    hintTable[SHADOW_TEMPLE_MQ_HOVER_BOOTS_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#Dead Hand in the Shadow Temple# holds", /*french*/"", /*spanish*/"la #Mano Muerta del Templo de las Sombras# guarda"},
    });

    hintTable[SHADOW_TEMPLE_MQ_EARLY_GIBDOS_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#mummies revealed by the Eye of Truth# guard", /*french*/"", /*spanish*/"las #momias reveladas por el Ojo de la Verdad# guardan"},
    });

    hintTable[SHADOW_TEMPLE_MQ_MAP_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#spinning scythes# protect", /*french*/"", /*spanish*/"las #giratorias guadañas# protegen"},
    });

    hintTable[SHADOW_TEMPLE_MQ_BEAMOS_SILVER_RUPEES_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#collecting rupees in a vast cavern# with the Shadow Temple unveils", /*french*/"", /*spanish*/"hacerte con las #rupias en una gran caverna# del Templo de las Sombras revela"},
    });

    hintTable[SHADOW_TEMPLE_MQ_FALLING_SPIKES_SWITCH_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#falling spikes# block the path to", /*french*/"", /*spanish*/"los #pinchos del techo# conducen a"},
    });

    hintTable[SHADOW_TEMPLE_MQ_FALLING_SPIKES_LOWER_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#falling spikes# block the path to", /*french*/"", /*spanish*/"los #pinchos del techo# conducen a"},
    });

    hintTable[SHADOW_TEMPLE_MQ_FALLING_SPIKES_UPPER_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#falling spikes# block the path to", /*french*/"", /*spanish*/"los #pinchos del techo# conducen a"},
    });

    hintTable[SHADOW_TEMPLE_MQ_INVISIBLE_SPIKES_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #dead roam among invisible spikes# guarding", /*french*/"", /*spanish*/"los #muertos que vagan por pinchos invisibles# protegen"},
    });

    hintTable[SHADOW_TEMPLE_MQ_BOSS_KEY_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#walls consumed by a ball of fire# reveal", /*french*/"", /*spanish*/"las #paredes consumidas por una esfera ígnea# revelan"},
    });

    hintTable[SHADOW_TEMPLE_MQ_SPIKE_WALLS_LEFT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#walls consumed by a ball of fire# reveal", /*french*/"", /*spanish*/"las #paredes consumidas por una esfera ígnea# revelan"},
    });

    hintTable[SHADOW_TEMPLE_MQ_STALFOS_ROOM_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"near an #empty pedestal# within the Shadow Temple lies", /*french*/"", /*spanish*/"cerca de un #vacío pedestal# del Templo de las Sombras yace"},
    });

    hintTable[SHADOW_TEMPLE_MQ_INVISIBLE_BLADES_INVISIBLE_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#invisible blades# guard", /*french*/"", /*spanish*/"las #hojas invisibles# guardan"},
    });

    hintTable[SHADOW_TEMPLE_MQ_INVISIBLE_BLADES_VISIBLE_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#invisible blades# guard", /*french*/"", /*spanish*/"las #hojas invisibles# guardan"},
    });

    hintTable[SHADOW_TEMPLE_MQ_WIND_HINT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"an #invisible chest guarded by the dead# holds", /*french*/"", /*spanish*/"un #cofre invisible custodiado por los del más allá# contiene"},
    });

    hintTable[SHADOW_TEMPLE_MQ_AFTER_WIND_HIDDEN_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#mummies guarding a ferry# hide", /*french*/"", /*spanish*/"las #momias que protegen un navío# esconden"},
    });

    hintTable[SHADOW_TEMPLE_MQ_AFTER_WIND_ENEMY_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#mummies guarding a ferry# hide", /*french*/"", /*spanish*/"las #momias que protegen un navío# esconden"},
    });

    hintTable[SHADOW_TEMPLE_MQ_NEAR_SHIP_INVISIBLE_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#caged near a ship# lies", /*french*/"", /*spanish*/"#entre rejas al lado de un navío# yace"},
    });

    hintTable[SHADOW_TEMPLE_MQ_FREESTANDING_KEY] = HintText::Exclude({
                       //obscure text
                       Text{"#behind three burning skulls# lies", /*french*/"", /*spanish*/"tras #tres ardientes calaveras# yace"},
    });

    hintTable[BOTTOM_OF_THE_WELL_FRONT_LEFT_FAKE_WALL_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth in the well# reveals", /*french*/"", /*spanish*/"el #Ojo de la Verdad en el pozo# revela"},
    });

    hintTable[BOTTOM_OF_THE_WELL_FRONT_CENTER_BOMBABLE_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#gruesome debris# in the well hides", /*french*/"", /*spanish*/"unos #horripilantes escombros# del pozo esconden"},
    });

    hintTable[BOTTOM_OF_THE_WELL_RIGHT_BOTTOM_FAKE_WALL_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth in the well# reveals", /*french*/"", /*spanish*/"el #Ojo de la Verdad en el pozo# revela"},
    });

    hintTable[BOTTOM_OF_THE_WELL_COMPASS_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #hidden entrance to a cage# in the well leads to", /*french*/"", /*spanish*/"la #entrada oculta de una celda# del pozo conduce a"},
    });

    hintTable[BOTTOM_OF_THE_WELL_CENTER_SKULLTULA_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider guarding a cage# in the well protects", /*french*/"", /*spanish*/"una #araña protegiendo una celda# del pozo guarda"},
    });

    hintTable[BOTTOM_OF_THE_WELL_BACK_LEFT_BOMBABLE_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#gruesome debris# in the well hides", /*french*/"", /*spanish*/"unos #horripilantes escombros# del pozo esconden"},
    });

    hintTable[BOTTOM_OF_THE_WELL_INVISIBLE_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#Dead Hand's invisible secret# is", /*french*/"", /*spanish*/"el #secreto invisible de la Mano Muerta# se trata de"},
    });

    hintTable[BOTTOM_OF_THE_WELL_UNDERWATER_FRONT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #royal melody in the well# uncovers", /*french*/"", /*spanish*/"una #melodía real en el pozo# revela"},
    });

    hintTable[BOTTOM_OF_THE_WELL_UNDERWATER_LEFT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #royal melody in the well# uncovers", /*french*/"", /*spanish*/"una #melodía real en el pozo# revela"},
    });

    hintTable[BOTTOM_OF_THE_WELL_MAP_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"in the #depths of the well# lies", /*french*/"", /*spanish*/"en las #profundidades del pozo# yace"},
    });

    hintTable[BOTTOM_OF_THE_WELL_FIRE_KEESE_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#perilous pits# in the well guard the path to", /*french*/"", /*spanish*/"#peligrosos fosos# del pozo conducen a"},
    });

    hintTable[BOTTOM_OF_THE_WELL_LIKE_LIKE_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#locked in a cage# in the well lies", /*french*/"", /*spanish*/"#entre rejas# en el pozo yace"},
    });

    hintTable[BOTTOM_OF_THE_WELL_FREESTANDING_KEY] = HintText::Exclude({
                       //obscure text
                       Text{"#inside a coffin# hides", /*french*/"", /*spanish*/"en el #interior de un ataúd# yace"},
    });


    hintTable[BOTTOM_OF_THE_WELL_MQ_MAP_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #royal melody in the well# uncovers", /*french*/"", /*spanish*/"una #melodía real en el pozo# revela"},
    });

    hintTable[BOTTOM_OF_THE_WELL_MQ_LENS_OF_TRUTH_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"an #army of the dead# in the well guards", /*french*/"", /*spanish*/"un #ejército del más allá# del pozo guarda"},
    });

    hintTable[BOTTOM_OF_THE_WELL_MQ_DEAD_HAND_FREESTANDING_KEY] = HintText::Exclude({
                       //obscure text
                       Text{"#Dead Hand's explosive secret# is", /*french*/"", /*spanish*/"el #explosivo secreto de la Mano Muerta# se trata de"},
    });

    hintTable[BOTTOM_OF_THE_WELL_MQ_EAST_INNER_ROOM_FREESTANDING_KEY] = HintText::Exclude({
                       //obscure text
                       Text{"an #invisible path in the well# leads to", /*french*/"", /*spanish*/"un #camino invisible del pozo# conduce a"},
    });


    hintTable[ICE_CAVERN_MAP_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#winds of ice# surround", /*french*/"", /*spanish*/"#heladas borrascas# rodean"},
    });

    hintTable[ICE_CAVERN_COMPASS_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #wall of ice# protects", /*french*/"", /*spanish*/"una #gélida pared# protege"},
    });

    hintTable[ICE_CAVERN_IRON_BOOTS_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #monster in a frozen cavern# guards", /*french*/"", /*spanish*/"un #monstruo de una helada caverna# guarda"},
    });

    hintTable[ICE_CAVERN_FREESTANDING_POH] = HintText::Exclude({
                       //obscure text
                       Text{"a #wall of ice# protects", /*french*/"", /*spanish*/"una #gélida pared# protege"},
    });


    hintTable[ICE_CAVERN_MQ_IRON_BOOTS_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #monster in a frozen cavern# guards", /*french*/"", /*spanish*/"un #monstruo de una helada caverna# guarda"},
    });

    hintTable[ICE_CAVERN_MQ_COMPASS_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#winds of ice# surround", /*french*/"", /*spanish*/"#heladas borrascas# rodean"},
    });

    hintTable[ICE_CAVERN_MQ_MAP_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #wall of ice# protects", /*french*/"", /*spanish*/"una #gélida pared# protege"},
    });

    hintTable[ICE_CAVERN_MQ_FREESTANDING_POH] = HintText::Exclude({
                       //obscure text
                       Text{"#winds of ice# surround", /*french*/"", /*spanish*/"#heladas borrascas# rodean"},
    });


    hintTable[GERUDO_TRAINING_GROUNDS_LOBBY_LEFT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #blinded eye in the Gerudo Training Grounds# drops", /*french*/"", /*spanish*/"#cegar un ojo en el Centro de Instrucción Gerudo# revela"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_LOBBY_RIGHT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #blinded eye in the Gerudo Training Grounds# drops", /*french*/"", /*spanish*/"#cegar un ojo en el Centro de Instrucción Gerudo# revela"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_STALFOS_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#soldiers walking on shifting sands# in the Gerudo Training Grounds guard", /*french*/"", /*spanish*/"#soldados en resbaladizas arenas# del Centro de Instrucción Gerudo protegen"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_BEAMOS_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#reptilian warriors# in the Gerudo Training Grounds protect", /*french*/"", /*spanish*/"#unos escamosos guerreros# del Centro de Instrucción Gerudo protegen"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_HIDDEN_CEILING_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth# in the Gerudo Training Grounds reveals", /*french*/"", /*spanish*/"el #Ojo de la Verdad# en el Centro de Instrucción Gerudo revela"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MAZE_PATH_FIRST_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the first prize of #the thieves' training# is", /*french*/"", /*spanish*/"el primer premio de la #instrucción ladrona# se trata de"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MAZE_PATH_SECOND_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the second prize of #the thieves' training# is", /*french*/"", /*spanish*/"el segundo premio de la #instrucción ladrona# se trata de"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MAZE_PATH_THIRD_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the third prize of #the thieves' training# is", /*french*/"", /*spanish*/"el tercer premio de la #instrucción ladrona# se trata de"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MAZE_RIGHT_CENTRAL_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #Song of Time# in the Gerudo Training Grounds leads to", /*french*/"", /*spanish*/"la #Canción del Tiempo# en el Centro de Instrucción Gerudo conduce a"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MAZE_RIGHT_SIDE_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #Song of Time# in the Gerudo Training Grounds leads to", /*french*/"", /*spanish*/"la #Canción del Tiempo# en el Centro de Instrucción Gerudo conduce a"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_HAMMER_ROOM_CLEAR_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#fiery foes# in the Gerudo Training Grounds guard", /*french*/"", /*spanish*/"unos #candentes enemigos# del Centro de Instrucción Gerudo guardan"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_HAMMER_ROOM_SWITCH_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#engulfed in flame# where thieves train lies", /*french*/"", /*spanish*/"donde entrenan las ladronas #entre llamas# yace"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_EYE_STATUE_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"thieves #blind four faces# to find", /*french*/"", /*spanish*/"las ladronas #ciegan cuatro facetas# para hallar"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_NEAR_SCARECROW_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"thieves #blind four faces# to find", /*french*/"", /*spanish*/"las ladronas #ciegan cuatro facetas# para hallar"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_BEFORE_HEAVY_BLOCK_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#before a block of silver# thieves can find", /*french*/"", /*spanish*/"#ante un plateado bloque# las ladronas hallan"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_FIRST_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #feat of strength# rewards thieves with", /*french*/"", /*spanish*/"una #hazaña de fuerza# premia a las ladronas con"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_SECOND_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #feat of strength# rewards thieves with", /*french*/"", /*spanish*/"una #hazaña de fuerza# premia a las ladronas con"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_THIRD_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #feat of strength# rewards thieves with", /*french*/"", /*spanish*/"una #hazaña de fuerza# premia a las ladronas con"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_FOURTH_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #feat of strength# rewards thieves with", /*french*/"", /*spanish*/"una #hazaña de fuerza# premia a las ladronas con"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_FREESTANDING_KEY] = HintText::Exclude({
                       //obscure text
                       Text{"the #Song of Time# in the Gerudo Training Grounds leads to", /*french*/"", /*spanish*/"la #Canción del Tiempo# en el Centro de Instrucción Gerudo conduce a"},
    });


    hintTable[GERUDO_TRAINING_GROUNDS_MQ_LOBBY_RIGHT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#thieves prepare for training# with", /*french*/"", /*spanish*/"las #ladronas se instruyen# con"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MQ_LOBBY_LEFT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#thieves prepare for training# with", /*french*/"", /*spanish*/"las #ladronas se instruyen# con"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MQ_FIRST_IRON_KNUCKLE_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#soldiers walking on shifting sands# in the Gerudo Training Grounds guard", /*french*/"", /*spanish*/"#soldados en resbaladizas arenas# del Centro de Instrucción Gerudo protegen"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MQ_BEFORE_HEAVY_BLOCK_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#before a block of silver# thieves can find", /*french*/"", /*spanish*/"#ante un plateado bloque# las ladronas hallang"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MQ_EYE_STATUE_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"thieves #blind four faces# to find", /*french*/"", /*spanish*/"las ladronas #ciegan cuatro facetas# para hallar"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MQ_FLAME_CIRCLE_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#engulfed in flame# where thieves train lies", /*french*/"", /*spanish*/"donde entrenan las ladronas #entre llamas# yace"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MQ_SECOND_IRON_KNUCKLE_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#fiery foes# in the Gerudo Training Grounds guard", /*french*/"", /*spanish*/"unos #candentes enemigos# del Centro de Instrucción Gerudo guardan"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MQ_DINOLFOS_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#reptilian warriors# in the Gerudo Training Grounds protect", /*french*/"", /*spanish*/"#unos escamosos guerreros# del Centro de Instrucción Gerudo protegen"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MQ_MAZE_RIGHT_CENTRAL_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #path of fire# leads thieves to", /*french*/"", /*spanish*/"un #camino de fuego# conduce a las ladronas a"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MQ_MAZE_PATH_FIRST_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the first prize of #the thieves' training# is", /*french*/"", /*spanish*/"el primer premio de la #instrucción ladrona# se trata de"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MQ_MAZE_RIGHT_SIDE_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #path of fire# leads thieves to", /*french*/"", /*spanish*/"un #camino de fuego# conduce a las ladronas a"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MQ_MAZE_PATH_THIRD_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the third prize of #the thieves' training# is", /*french*/"", /*spanish*/"el tercer premio de la #instrucción ladrona# se trata de"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MQ_MAZE_PATH_SECOND_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the second prize of #the thieves' training# is", /*french*/"", /*spanish*/"el segundo premio de la #instrucción ladrona# se trata de"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MQ_HIDDEN_CEILING_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #Eye of Truth# in the Gerudo Training Grounds reveals", /*french*/"", /*spanish*/"el #Ojo de la Verdad# en el Centro de Instrucción Gerudo revela"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MQ_HEAVY_BLOCK_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a #feat of strength# rewards thieves with", /*french*/"", /*spanish*/"una #hazaña de fuerza# premia a las ladronas con"},
    });


    hintTable[GANONS_TOWER_BOSS_KEY_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #Evil King# hoards", /*french*/"", /*spanish*/"el #Rey del Mal# acapara"},
    });


    hintTable[GANONS_CASTLE_FOREST_TRIAL_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the wilds# holds", /*french*/"", /*spanish*/"la #prueba de la naturaleza# brinda"},
    });

    hintTable[GANONS_CASTLE_WATER_TRIAL_LEFT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the seas# holds", /*french*/"", /*spanish*/"la #prueba del mar# brinda"},
    });

    hintTable[GANONS_CASTLE_WATER_TRIAL_RIGHT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the seas# holds", /*french*/"", /*spanish*/"la #prueba del mar# brinda"},
    });

    hintTable[GANONS_CASTLE_SHADOW_TRIAL_FRONT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#music in the test of darkness# unveils", /*french*/"", /*spanish*/"la #música en la prueba de la oscuridad# revela"},
    });

    hintTable[GANONS_CASTLE_SHADOW_TRIAL_GOLDEN_GAUNTLETS_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#light in the test of darkness# unveils", /*french*/"", /*spanish*/"la #luz en la prueba de la oscuridad# revela"},
    });

    hintTable[GANONS_CASTLE_SPIRIT_TRIAL_CRYSTAL_SWITCH_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the sands# holds", /*french*/"", /*spanish*/"la #prueba de las arenas# brinda"},
    });

    hintTable[GANONS_CASTLE_SPIRIT_TRIAL_INVISIBLE_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the sands# holds", /*french*/"", /*spanish*/"la #prueba de las arenas# brinda"},
    });

    hintTable[GANONS_CASTLE_LIGHT_TRIAL_FIRST_LEFT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #test of radiance# holds", /*french*/"", /*spanish*/"la #prueba del resplandor# brinda"},
    });

    hintTable[GANONS_CASTLE_LIGHT_TRIAL_SECOND_LEFT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #test of radiance# holds", /*french*/"", /*spanish*/"la #prueba del resplandor# brinda"},
    });

    hintTable[GANONS_CASTLE_LIGHT_TRIAL_THIRD_LEFT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #test of radiance# holds", /*french*/"", /*spanish*/"la #prueba del resplandor# brinda"},
    });

    hintTable[GANONS_CASTLE_LIGHT_TRIAL_FIRST_RIGHT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #test of radiance# holds", /*french*/"", /*spanish*/"la #prueba del resplandor# brinda"},
    });

    hintTable[GANONS_CASTLE_LIGHT_TRIAL_SECOND_RIGHT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #test of radiance# holds", /*french*/"", /*spanish*/"la #prueba del resplandor# brinda"},
    });

    hintTable[GANONS_CASTLE_LIGHT_TRIAL_THIRD_RIGHT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #test of radiance# holds", /*french*/"", /*spanish*/"la #prueba del resplandor# brinda"},
    });

    hintTable[GANONS_CASTLE_LIGHT_TRIAL_INVISIBLE_ENEMIES_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #test of radiance# holds", /*french*/"", /*spanish*/"la #prueba del resplandor# brinda"},
    });

    hintTable[GANONS_CASTLE_LIGHT_TRIAL_LULLABY_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#music in the test of radiance# reveals", /*french*/"", /*spanish*/"la #música en la prueba del resplandor# revela"},
    });


    hintTable[GANONS_CASTLE_MQ_WATER_TRIAL_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the seas# holds", /*french*/"", /*spanish*/"la #prueba del mar# brinda"},
    });

    hintTable[GANONS_CASTLE_MQ_FOREST_TRIAL_EYE_SWITCH_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the wilds# holds", /*french*/"", /*spanish*/"la #prueba de la naturaleza# brinda"},
    });

    hintTable[GANONS_CASTLE_MQ_FOREST_TRIAL_FROZEN_EYE_SWITCH_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the wilds# holds", /*french*/"", /*spanish*/"la #prueba de la naturaleza# brinda"},
    });

    hintTable[GANONS_CASTLE_MQ_LIGHT_TRIAL_LULLABY_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#music in the test of radiance# reveals", /*french*/"", /*spanish*/"la #música en la prueba del resplandor# revela"},
    });

    hintTable[GANONS_CASTLE_MQ_SHADOW_TRIAL_BOMB_FLOWER_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #test of darkness# holds", /*french*/"", /*spanish*/"la #prueba de la oscuridad# brinda"},
    });

    hintTable[GANONS_CASTLE_MQ_SHADOW_TRIAL_EYE_SWITCH_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"the #test of darkness# holds", /*french*/"", /*spanish*/"la #prueba de la oscuridad# brinda"},
    });

    hintTable[GANONS_CASTLE_MQ_SPIRIT_TRIAL_GOLDEN_GAUNTLETS_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#reflected light in the test of the sands# reveals", /*french*/"", /*spanish*/"#reflejar la luz en la prueba de las arenas# revela"},
    });

    hintTable[GANONS_CASTLE_MQ_SPIRIT_TRIAL_SUN_BACK_RIGHT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#reflected light in the test of the sands# reveals", /*french*/"", /*spanish*/"#reflejar la luz en la prueba de las arenas# revela"},
    });

    hintTable[GANONS_CASTLE_MQ_SPIRIT_TRIAL_SUN_BACK_LEFT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#reflected light in the test of the sands# reveals", /*french*/"", /*spanish*/"#reflejar la luz en la prueba de las arenas# revela"},
    });

    hintTable[GANONS_CASTLE_MQ_SPIRIT_TRIAL_SUN_FRONT_LEFT_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#reflected light in the test of the sands# reveals", /*french*/"", /*spanish*/"#reflejar la luz en la prueba de las arenas# revela"},
    });

    hintTable[GANONS_CASTLE_MQ_SPIRIT_TRIAL_FIRST_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#reflected light in the test of the sands# reveals", /*french*/"", /*spanish*/"#reflejar la luz en la prueba de las arenas# revela"},
    });

    hintTable[GANONS_CASTLE_MQ_SPIRIT_TRIAL_INVISIBLE_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"#reflected light in the test of the sands# reveals", /*french*/"", /*spanish*/"#reflejar la luz en la prueba de las arenas# revela"},
    });

    hintTable[GANONS_CASTLE_MQ_FOREST_TRIAL_FREESTANDING_KEY] = HintText::Exclude({
                       //obscure text
                       Text{"the #test of the wilds# holds", /*french*/"", /*spanish*/"la #prueba de la naturaleza# brinda"},
    });


    hintTable[DEKU_TREE_QUEEN_GOHMA_HEART] = HintText::Exclude({
                       //obscure text
                       Text{"the #Parasitic Armored Arachnid# holds", /*french*/"", /*spanish*/"el #arácnido parasitario acorazado# porta"},
                     },
                       //clear text
                       Text{"#Queen Gohma# holds", /*french*/"", /*spanish*/"la #Reina Goma# porta"}
    );

    hintTable[DODONGOS_CAVERN_KING_DODONGO_HEART] = HintText::Exclude({
                       //obscure text
                       Text{"the #Infernal Dinosaur# holds", /*french*/"", /*spanish*/"el #dinosaurio infernal# porta"},
                     },
                       //clear text
                       Text{"#King Dodongo# holds", /*french*/"", /*spanish*/"el #Rey Dodongo# porta"}
    );

    hintTable[JABU_JABUS_BELLY_BARINADE_HEART] = HintText::Exclude({
                       //obscure text
                       Text{"the #Bio-Electric Anemone# holds", /*french*/"", /*spanish*/"la #anémona bioeléctrica# porta"},
                     },
                       //clear text
                       Text{"#Barinade# holds", /*french*/"", /*spanish*/"#Barinade# porta"}
    );

    hintTable[FOREST_TEMPLE_PHANTOM_GANON_HEART] = HintText::Exclude({
                       //obscure text
                       Text{"the #Evil Spirit from Beyond# holds", /*french*/"", /*spanish*/"el #espíritu maligno de ultratumba# porta"},
                     },
                       //clear text
                       Text{"#Phantom Ganon# holds", /*french*/"", /*spanish*/"#Ganon Fantasma# porta"}
    );

    hintTable[FIRE_TEMPLE_VOLVAGIA_HEART] = HintText::Exclude({
                       //obscure text
                       Text{"the #Subterranean Lava Dragon# holds", /*french*/"", /*spanish*/"el #dragón de lava subterráneo# porta"},
                     },
                       //clear text
                       Text{"#Volvagia# holds", /*french*/"", /*spanish*/"#Volvagia# porta"}
    );

    hintTable[WATER_TEMPLE_MORPHA_HEART] = HintText::Exclude({
                       //obscure text
                       Text{"the #Giant Aquatic Amoeba# holds", /*french*/"", /*spanish*/"la #ameba acuática gigante# porta"},
                     },
                       //clear text
                       Text{"#Morpha# holds", /*french*/"", /*spanish*/"#Morpha# porta"}
    );

    hintTable[SPIRIT_TEMPLE_TWINROVA_HEART] = HintText::Exclude({
                       //obscure text
                       Text{"the #Sorceress Sisters# hold", /*french*/"", /*spanish*/"las #hermanas hechiceras# portan"},
                     },
                       //clear text
                       Text{"#Twinrova# holds", /*french*/"", /*spanish*/"#Birova# porta"}
    );

    hintTable[SHADOW_TEMPLE_BONGO_BONGO_HEART] = HintText::Exclude({
                       //obscure text
                       Text{"the #Phantom Shadow Beast# holds", /*french*/"", /*spanish*/"la #alimaña oscura espectral# porta"},
                     },
                       //clear text
                       Text{"#Bongo Bongo# holds", /*french*/"", /*spanish*/"#Bongo Bongo# porta"}
    );


    hintTable[DEKU_TREE_GS_BASEMENT_BACK_ROOM] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider deep within the Deku Tree# hides", /*french*/"", /*spanish*/"una #araña en las profundidades del Árbol Deku# otorga"},
    });

    hintTable[DEKU_TREE_GS_BASEMENT_GATE] = HintText::Exclude({
                       //obscure text
                       Text{"a #web protects a spider# within the Deku Tree holding", /*french*/"", /*spanish*/"una #araña protegida por su tela# del Árbol Deku otorga"},
    });

    hintTable[DEKU_TREE_GS_BASEMENT_VINES] = HintText::Exclude({
                       //obscure text
                       Text{"a #web protects a spider# within the Deku Tree holding", /*french*/"", /*spanish*/"una #araña protegida por su tela# del Árbol Deku otorga"},
    });

    hintTable[DEKU_TREE_GS_COMPASS_ROOM] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider atop the Deku Tree# holds", /*french*/"", /*spanish*/"una #araña en lo alto del Árbol Deku# otorga"},
    });


    hintTable[DEKU_TREE_MQ_GS_LOBBY] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider in a crate# within the Deku Tree hides", /*french*/"", /*spanish*/"una #araña bajo una caja# del Árbol Deku otorga"},
    });

    hintTable[DEKU_TREE_MQ_GS_COMPASS_ROOM] = HintText::Exclude({
                       //obscure text
                       Text{"a #wall of rock protects a spider# within the Deku Tree holding", /*french*/"", /*spanish*/"una #araña protegida por una pared rocosa# del Árbol Deku otorga"},
    });

    hintTable[DEKU_TREE_MQ_GS_BASEMENT_BACK_ROOM] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider deep within the Deku Tree# hides", /*french*/"", /*spanish*/"una #araña en las profundidades del Árbol Deku# otorga"},
    });


    hintTable[DODONGOS_CAVERN_GS_VINES_ABOVE_STAIRS] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider entangled in vines# in Dodongo's Cavern guards", /*french*/"", /*spanish*/"una #araña sobre unas cepas# de la Cueva de los Dodongos otorga"},
    });

    hintTable[DODONGOS_CAVERN_GS_SCARECROW] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider among explosive slugs# hides", /*french*/"", /*spanish*/"una #araña rodeada de explosivos gusanos# otorga"},
    });

    hintTable[DODONGOS_CAVERN_GS_ALCOVE_ABOVE_STAIRS] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider just out of reach# in Dodongo's Cavern holds", /*french*/"", /*spanish*/"una #araña fuera del alcance# de la Cueva de los Dodongos otorga"},
    });

    hintTable[DODONGOS_CAVERN_GS_BACK_ROOM] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider behind a statue# in Dodongo's Cavern holds", /*french*/"", /*spanish*/"una #araña tras una estatua# de la Cueva de los Dodongos otorga"},
    });

    hintTable[DODONGOS_CAVERN_GS_SIDE_ROOM_NEAR_LOWER_LIZALFOS] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider among bats# in Dodongo's Cavern holds", /*french*/"", /*spanish*/"una #araña rodeada de murciélagos# de la Cueva de los Dodongos otorga"},
    });


    hintTable[DODONGOS_CAVERN_MQ_GS_SCRUB_ROOM] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider high on a wall# in Dodongo's Cavern holds", /*french*/"", /*spanish*/"una #araña en lo alto de una pared# de la Cueva de los Dodongos otorga"},
    });

    hintTable[DODONGOS_CAVERN_MQ_GS_LIZALFOS_ROOM] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider on top of a pillar of rock# in Dodongo's Cavern holds", /*french*/"", /*spanish*/"una #araña en lo alto de un pilar# de la Cueva de los Dodongos otorga"},
    });

    hintTable[DODONGOS_CAVERN_MQ_GS_LARVAE_ROOM] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider in a crate# in Dodongo's Cavern holds", /*french*/"", /*spanish*/"una #araña bajo una caja# de la Cueva de los Dodongos otorga"},
    });

    hintTable[DODONGOS_CAVERN_MQ_GS_BACK_AREA] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider among graves# in Dodongo's Cavern holds", /*french*/"", /*spanish*/"una #araña entre lápidas# en la Cueva de los Dodongos otorga"},
    });


    hintTable[JABU_JABUS_BELLY_GS_LOBBY_BASEMENT_LOWER] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider resting near a princess# in Jabu Jabu's Belly holds", /*french*/"", /*spanish*/"una #araña junto a una princesa# en la Tripa de Jabu Jabu otorga"},
    });

    hintTable[JABU_JABUS_BELLY_GS_LOBBY_BASEMENT_UPPER] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider resting near a princess# in Jabu Jabu's Belly holds", /*french*/"", /*spanish*/"una #araña junto a una princesa# en la Tripa de Jabu Jabu otorga"},
    });

    hintTable[JABU_JABUS_BELLY_GS_NEAR_BOSS] = HintText::Exclude({
                       //obscure text
                       Text{"#jellyfish surround a spider# holding", /*french*/"", /*spanish*/"una #araña rodeada de medusas# otorga"},
    });

    hintTable[JABU_JABUS_BELLY_GS_WATER_SWITCH_ROOM] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider guarded by a school of stingers# in Jabu Jabu's Belly holds", /*french*/"", /*spanish*/"una #araña rodeada por un puñado de stingers# en la Tripa de Jabu Jabu otorga"},
    });


    hintTable[JABU_JABUS_BELLY_MQ_GS_TAILPASARAN_ROOM] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider surrounded by electricity# in Jabu Jabu's Belly holds", /*french*/"", /*spanish*/"una #araña rodeada de electricidad# en la Tripa de Jabu Jabu otorga"},
    });

    hintTable[JABU_JABUS_BELLY_MQ_GS_BOOMERANG_CHEST_ROOM] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider guarded by a school of stingers# in Jabu Jabu's Belly holds", /*french*/"", /*spanish*/"una #araña protegida por un puñado de stingers# en la Tripa de Jabu Jabu otorga"},
    });

    hintTable[JABU_JABUS_BELLY_MQ_GS_NEAR_BOSS] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider in a web within Jabu Jabu's Belly# holds", /*french*/"", /*spanish*/"una #araña sobre una telaraña# en la Tripa de Jabu Jabu otorga"},
    });


    hintTable[FOREST_TEMPLE_GS_RAISED_ISLAND_COURTYARD] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider on a small island# in the Forest Temple holds", /*french*/"", /*spanish*/"una #araña sobre una pequeña isla# del Templo del Bosque otorga"},
    });

    hintTable[FOREST_TEMPLE_GS_FIRST_ROOM] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider high on a wall of vines# in the Forest Temple holds", /*french*/"", /*spanish*/"una #araña en lo alto de una pared de cepas# del Templo del Bosque otorga"},
    });

    hintTable[FOREST_TEMPLE_GS_LEVEL_ISLAND_COURTYARD] = HintText::Exclude({
                       //obscure text
                       Text{"#stone columns# lead to a spider in the Forest Temple hiding", /*french*/"", /*spanish*/"unas #columnas del Templo del Bosque# conducen a una araña que otorga"},
    });

    hintTable[FOREST_TEMPLE_GS_LOBBY] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider among ghosts# in the Forest Temple guards", /*french*/"", /*spanish*/"una #araña rodeada de fantasmas# del Templo del Bosque otorga"},
    });

    hintTable[FOREST_TEMPLE_GS_BASEMENT] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider within revolving walls# in the Forest Temple holds", /*french*/"", /*spanish*/"una #araña entre paredes giratorias# del Templo del Bosque otorga"},
    });


    hintTable[FOREST_TEMPLE_MQ_GS_FIRST_HALLWAY] = HintText::Exclude({
                       //obscure text
                       Text{"an #ivy-hidden spider# in the Forest Temple hoards", /*french*/"", /*spanish*/"una #araña escondida entre cepas# del Templo del Bosque otorga"},
    });

    hintTable[FOREST_TEMPLE_MQ_GS_BLOCK_PUSH_ROOM] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider in a hidden nook# within the Forest Temple holds", /*french*/"", /*spanish*/"una #araña en una esquina oculta# del Templo del Bosque otorga"},
    });

    hintTable[FOREST_TEMPLE_MQ_GS_RAISED_ISLAND_COURTYARD] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider on an arch# in the Forest Temple holds", /*french*/"", /*spanish*/"una #araña sobre un arco# del Templo del Bosque otorga"},
    });

    hintTable[FOREST_TEMPLE_MQ_GS_LEVEL_ISLAND_COURTYARD] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider on a ledge# in the Forest Temple holds", /*french*/"", /*spanish*/"una #araña en un borde# del Templo del Bosque otorga"},
    });

    hintTable[FOREST_TEMPLE_MQ_GS_WELL] = HintText::Exclude({
                       //obscure text
                       Text{"#draining a well# in Forest Temple uncovers a spider with", /*french*/"", /*spanish*/"#vaciar el pozo# del Templo del Bosque desvela una araña que otorga"},
    });


    hintTable[FIRE_TEMPLE_GS_SONG_OF_TIME_ROOM] = HintText::Exclude({
                       //obscure text
                       Text{"#eight tiles of malice# guard a spider holding", /*french*/"", /*spanish*/"#ocho baldosas de maldad# custodian una araña que otorga"},
    });

    hintTable[FIRE_TEMPLE_GS_BOSS_KEY_LOOP] = HintText::Exclude({
                       //obscure text
                       Text{"#five tiles of malice# guard a spider holding", /*french*/"", /*spanish*/"#cinco baldosas de maldad# custodian una araña que otorga"},
    });

    hintTable[FIRE_TEMPLE_GS_BOULDER_MAZE] = HintText::Exclude({
                       //obscure text
                       Text{"#explosives in a maze# unveil a spider hiding", /*french*/"", /*spanish*/"los #explosivos en un laberinto# desvelan una araña que otorga"},
    });

    hintTable[FIRE_TEMPLE_GS_SCARECROW_TOP] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider-friendly scarecrow# atop a volcano hides", /*french*/"", /*spanish*/"un #espantapájaros en lo alto de un volcán# custodia una araña que otorga"},
                     },
                       //clear text
                       Text{"a #spider-friendly scarecrow# atop the Fire Temple hides", /*french*/"", /*spanish*/"un #espantapájaros del Templo del Fuego# custodia una araña que otorga"}
    );

    hintTable[FIRE_TEMPLE_GS_SCARECROW_CLIMB] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider-friendly scarecrow# atop a volcano hides", /*french*/"", /*spanish*/"un #espantapájaros en lo alto de un volcán# custodia una araña que otorga"},
                     },
                       //clear text
                       Text{"a #spider-friendly scarecrow# atop the Fire Temple hides", /*french*/"", /*spanish*/"un #espantapájaros del Templo del Fuego# custodia una araña que otorga"}
    );


    hintTable[FIRE_TEMPLE_MQ_GS_ABOVE_FIRE_WALL_MAZE] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider above a fiery maze# holds", /*french*/"", /*spanish*/"una #araña sobre un ardiente laberinto# otorga"},
    });

    hintTable[FIRE_TEMPLE_MQ_GS_FIRE_WALL_MAZE_CENTER] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider within a fiery maze# holds", /*french*/"", /*spanish*/"una #araña en el interior de un ardiente laberinto# otorga"},
    });

    hintTable[FIRE_TEMPLE_MQ_GS_BIG_LAVA_ROOM_OPEN_DOOR] = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron trapped near lava# befriended a spider with", /*french*/"", /*spanish*/"una #araña amiga de un Goron atrapado junto a la lava# otorga"},
    });

    hintTable[FIRE_TEMPLE_MQ_GS_FIRE_WALL_MAZE_SIDE_ROOM] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider beside a fiery maze# holds", /*french*/"", /*spanish*/"una #araña junto a un ardiente laberinto# otorga"},
    });


    hintTable[WATER_TEMPLE_GS_FALLING_PLATFORM_ROOM] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider over a waterfall# in the Water Temple holds", /*french*/"", /*spanish*/"una #araña tras una cascada# del Templo del Agua otorga"},
    });

    hintTable[WATER_TEMPLE_GS_CENTRAL_PILLAR] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider in the center of the Water Temple# holds", /*french*/"", /*spanish*/"una #araña en el centro del Templo del Agua# otorga"},
    });

    hintTable[WATER_TEMPLE_GS_NEAR_BOSS_KEY_CHEST] = HintText::Exclude({
                       //obscure text
                       Text{"a spider protected by #rolling boulders under the lake# hides", /*french*/"", /*spanish*/"una #araña protegida por rocas rodantes# bajo el lago otorga"},
                     },
                       //clear text
                       Text{"a spider protected by #rolling boulders in the Water Temple# hides", /*french*/"", /*spanish*/"una #araña protegida por rocas rodantes# del Templo del Agua otorga"}
    );

    hintTable[WATER_TEMPLE_GS_RIVER] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider over a river# in the Water Temple holds", /*french*/"", /*spanish*/"una #araña sobre un río# del Templo del Agua otorga"},
    });


    hintTable[WATER_TEMPLE_MQ_GS_BEFORE_UPPER_WATER_SWITCH] = HintText::Exclude({
                       //obscure text
                       Text{"#beyond a pit of lizards# is a spider holding", /*french*/"", /*spanish*/"#más allá de un pozo de reptiles# una araña otorga"},
    });

    hintTable[WATER_TEMPLE_MQ_GS_LIZALFOS_HALLWAY] = HintText::Exclude({
                       //obscure text
                       Text{"#lizards guard a spider# in the Water Temple with", /*french*/"", /*spanish*/"unos #reptiles custodian una araña# del Templo del Agua que otorga"},
    });

    hintTable[WATER_TEMPLE_MQ_GS_RIVER] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider over a river# in the Water Temple holds", /*french*/"", /*spanish*/"una #araña sobre un río# del Templo del Agua otorga"},
    });


    hintTable[SPIRIT_TEMPLE_GS_HALL_AFTER_SUN_BLOCK_ROOM] = HintText::Exclude({
                       //obscure text
                       Text{"a spider in the #hall of a knight# guards", /*french*/"", /*spanish*/"una #araña en el salón de un guerrero# otorga"},
    });

    hintTable[SPIRIT_TEMPLE_GS_BOULDER_ROOM] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider behind a temporal stone# in the Spirit Temple yields", /*french*/"", /*spanish*/"una #araña tras un bloque temporal# del Templo del Espíritu otorga"},
    });

    hintTable[SPIRIT_TEMPLE_GS_LOBBY] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider beside a statue# holds", /*french*/"", /*spanish*/"una #araña junto a una estatua# otorga"},
    });

    hintTable[SPIRIT_TEMPLE_GS_SUN_ON_FLOOR_ROOM] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider at the top of a deep shaft# in the Spirit Temple holds", /*french*/"", /*spanish*/"una #araña en lo alto de un gran hueco# del Templo del Espíritu otorga"},
    });

    hintTable[SPIRIT_TEMPLE_GS_METAL_FENCE] = HintText::Exclude({
                       //obscure text
                       Text{"a child defeats a #spider among bats# in the Spirit Temple to gain", /*french*/"", /*spanish*/"el joven que derrote la #araña entre murciélagos# hallará"},
    });


    hintTable[SPIRIT_TEMPLE_MQ_GS_LEEVER_ROOM] = HintText::Exclude({
                       //obscure text
                       Text{"#above a pit of sand# in the Spirit Temple hides", /*french*/"", /*spanish*/"una #araña sobre un pozo de arena# del Templo del Espíritu otorga"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_GS_NINE_THRONES_ROOM_WEST] = HintText::Exclude({
                       //obscure text
                       Text{"a spider in the #hall of a knight# guards", /*french*/"", /*spanish*/"una #araña en el salón de un guerrero# otorga"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_GS_NINE_THRONES_ROOM_NORTH] = HintText::Exclude({
                       //obscure text
                       Text{"a spider in the #hall of a knight# guards", /*french*/"", /*spanish*/"una #araña en el salón de un guerrero# otorga"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_GS_SUN_BLOCK_ROOM] = HintText::Exclude({
                       //obscure text
                       Text{"#upon a web of glass# in the Spirit Temple sits a spider holding", /*french*/"", /*spanish*/"#sobre una plataforma de cristal# yace una araña que otorga"},
    });


    hintTable[SHADOW_TEMPLE_GS_SINGLE_GIANT_POT] = HintText::Exclude({
                       //obscure text
                       Text{"#beyond a burning skull# lies a spider with", /*french*/"", /*spanish*/"#tras una ardiente calavera# yace una araña que otorga"},
    });

    hintTable[SHADOW_TEMPLE_GS_FALLING_SPIKES_ROOM] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider beyond falling spikes# holds", /*french*/"", /*spanish*/"una #araña tras los pinchos del techo# otorga"},
    });

    hintTable[SHADOW_TEMPLE_GS_TRIPLE_GIANT_POT] = HintText::Exclude({
                       //obscure text
                       Text{"#beyond three burning skulls# lies a spider with", /*french*/"", /*spanish*/"#tras tres ardientes calaveras# yace una araña que otorga"},
    });

    hintTable[SHADOW_TEMPLE_GS_LIKE_LIKE_ROOM] = HintText::Exclude({
                       //obscure text
                       Text{"a spider guarded by #invisible blades# holds", /*french*/"", /*spanish*/"una #araña custodiada por hojas invisibles# otorga"},
    });

    hintTable[SHADOW_TEMPLE_GS_NEAR_SHIP] = HintText::Exclude({
                       //obscure text
                       Text{"a spider near a #docked ship# hoards", /*french*/"", /*spanish*/"una #araña cercana a un navío# otorga"},
    });


    hintTable[SHADOW_TEMPLE_MQ_GS_FALLING_SPIKES_ROOM] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider beyond falling spikes# holds", /*french*/"", /*spanish*/"una #araña tras los pinchos del techo# otorga"},
    });

    hintTable[SHADOW_TEMPLE_MQ_GS_WIND_HINT_ROOM] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider amidst roaring winds# in the Shadow Temple holds", /*french*/"", /*spanish*/"una #araña entre ventarrones# del Templo de las Sombras otorga"},
    });

    hintTable[SHADOW_TEMPLE_MQ_GS_AFTER_WIND] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider beneath gruesome debris# in the Shadow Temple hides", /*french*/"", /*spanish*/"una #araña bajo unos horripilantes escombros# del Templo de las Sombras otorga"},
    });

    hintTable[SHADOW_TEMPLE_MQ_GS_AFTER_SHIP] = HintText::Exclude({
                       //obscure text
                       Text{"a #fallen statue# reveals a spider with", /*french*/"", /*spanish*/"una #estatua caída# revelará una araña que otorgue"},
    });

    hintTable[SHADOW_TEMPLE_MQ_GS_NEAR_BOSS] = HintText::Exclude({
                       //obscure text
                       Text{"a #suspended spider# guards", /*french*/"", /*spanish*/"una #araña flotante# otorga"},
    });


    hintTable[BOTTOM_OF_THE_WELL_GS_LIKE_LIKE_CAGE] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider locked in a cage# in the well holds", /*french*/"", /*spanish*/"una #araña enjaulada# del pozo otorga"},
    });

    hintTable[BOTTOM_OF_THE_WELL_GS_EAST_INNER_ROOM] = HintText::Exclude({
                       //obscure text
                       Text{"an #invisible path in the well# leads to", /*french*/"", /*spanish*/"un #camino invisible del pozo# conduce a una araña que otorga"},
    });

    hintTable[BOTTOM_OF_THE_WELL_GS_WEST_INNER_ROOM] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider locked in a crypt# within the well guards", /*french*/"", /*spanish*/"una #araña encerrada en una cripta# del pozo otorga"},
    });


    hintTable[BOTTOM_OF_THE_WELL_MQ_GS_BASEMENT] = HintText::Exclude({
                       //obscure text
                       Text{"a #gauntlet of invisible spiders# protects", /*french*/"", /*spanish*/"un #puñado de arañas invisibles# custodian una que otorga"},
    });

    hintTable[BOTTOM_OF_THE_WELL_MQ_GS_COFFIN_ROOM] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider crawling near the dead# in the well holds", /*french*/"", /*spanish*/"una #araña bajo los muertos# del pozo otorga"},
    });

    hintTable[BOTTOM_OF_THE_WELL_MQ_GS_WEST_INNER_ROOM] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider locked in a crypt# within the well guards", /*french*/"", /*spanish*/"una #araña encerrada en una cripta# del pozo otorga"},
    });


    hintTable[ICE_CAVERN_GS_PUSH_BLOCK_ROOM] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider above icy pits# holds", /*french*/"", /*spanish*/"una #araña sobre gélidos vacíos# otorga"},
    });

    hintTable[ICE_CAVERN_GS_SPINNING_SCYTHE_ROOM] = HintText::Exclude({
                       //obscure text
                       Text{"#spinning ice# guards a spider holding", /*french*/"", /*spanish*/"unos #témpanos giratorios# custodian una araña que otorga"},
    });

    hintTable[ICE_CAVERN_GS_HEART_PIECE_ROOM] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider behind a wall of ice# hides", /*french*/"", /*spanish*/"una #araña tras una gélida pared# otorga"},
    });


    hintTable[ICE_CAVERN_MQ_GS_SCARECROW] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider above icy pits# holds", /*french*/"", /*spanish*/"una #araña sobre gélidos vacíos# otorga"},
    });

    hintTable[ICE_CAVERN_MQ_GS_ICE_BLOCK] = HintText::Exclude({
                       //obscure text
                       Text{"a #web of ice# surrounds a spider with", /*french*/"", /*spanish*/"una #gélida telaraña# rodea a una que otorga"},
    });

    hintTable[ICE_CAVERN_MQ_GS_RED_ICE] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider in fiery ice# hoards", /*french*/"", /*spanish*/"una #araña de un ardiente hielo# otorga"},
    });


    hintTable[HF_GS_NEAR_KAK_GROTTO] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider-guarded spider in a hole# hoards", /*french*/"", /*spanish*/"una #araña custodiada por otra# de un hoyo otorga"},
    });


    hintTable[LLR_GS_BACK_WALL] = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider in a ranch# holding", /*french*/"", /*spanish*/"la noche revela una #araña del rancho# que otorga"},
    });

    hintTable[LLR_GS_RAIN_SHED] = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider in a ranch# holding", /*french*/"", /*spanish*/"la noche revela una #araña del rancho# que otorga"},
    });

    hintTable[LLR_GS_HOUSE_WINDOW] = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider in a ranch# holding", /*french*/"", /*spanish*/"la noche revela una #araña del rancho# que otorga"},
    });

    hintTable[LLR_GS_TREE] = HintText::Exclude({
                       //obscure text
                       Text{"a spider hiding in a #ranch tree# holds", /*french*/"", /*spanish*/"una araña escondida en el #árbol de un rancho# otorga"},
    });


    hintTable[KF_GS_BEAN_PATCH] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried in a forest# holds", /*french*/"", /*spanish*/"una #araña enterrada en un bosque# otorga"},
    });

    hintTable[KF_GS_KNOW_IT_ALL_HOUSE] = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a forest# holding", /*french*/"", /*spanish*/"la noche revela en el pasado una #araña del bosque# que otorga"},
    });

    hintTable[KF_GS_HOUSE_OF_TWINS] = HintText::Exclude({
                       //obscure text
                       Text{"night in the future reveals a #spider in a forest# holding", /*french*/"", /*spanish*/"la noche revela en el futuro una #araña del rancho# que otorga"},
    });


    hintTable[LW_GS_BEAN_PATCH_NEAR_BRIDGE] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried deep in a forest maze# holds", /*french*/"", /*spanish*/"una #araña enterrada en un laberinto forestal# otorga"},
    });

    hintTable[LW_GS_BEAN_PATCH_NEAR_THEATER] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried deep in a forest maze# holds", /*french*/"", /*spanish*/"una #araña enterrada en un laberinto forestal# otorga"},
    });

    hintTable[LW_GS_ABOVE_THEATER] = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider deep in a forest maze# holding", /*french*/"", /*spanish*/"la noche revela una #araña del laberinto forestal# que otorga"},
    });

    hintTable[SFM_GS] = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider in a forest meadow# holding", /*french*/"", /*spanish*/"la noche revela una #araña de la pradera del bosque# que otorga"},
    });


    hintTable[OGC_GS] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider outside a tyrant's tower# holds", /*french*/"", /*spanish*/"una #araña a las afueras de la torre de un tirano# otorga"},
    });

    hintTable[HC_GS_TREE] = HintText::Exclude({
                       //obscure text
                       Text{"a spider hiding in a #tree outside of a castle# holds", /*french*/"", /*spanish*/"una araña escondida en el #árbol de las afueras de un castillo# otorga"},
    });

    hintTable[MARKET_GS_GUARD_HOUSE] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider in a guarded crate# holds", /*french*/"", /*spanish*/"una #araña bajo una custodiada caja# otorga"},
    });


    hintTable[DMC_GS_BEAN_PATCH] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried in a volcano# holds", /*french*/"", /*spanish*/"una #araña enterrada en un volcán# otorga"},
    });


    hintTable[DMT_GS_BEAN_PATCH] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried outside a cavern# holds", /*french*/"", /*spanish*/"una #araña enterrada a la entrada de una cueva# otorga"},
    });

    hintTable[DMT_GS_NEAR_KAK] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider hidden in a mountain nook# holds", /*french*/"", /*spanish*/"una #araña oculta en el rincón de la montaña# otorga"},
    });

    hintTable[DMT_GS_ABOVE_DODONGOS_CAVERN] = HintText::Exclude({
                       //obscure text
                       Text{"the hammer reveals a #spider on a mountain# holding", /*french*/"", /*spanish*/"el martillo revela #una araña de la montaña# que otorga"},
    });

    hintTable[DMT_GS_FALLING_ROCKS_PATH] = HintText::Exclude({
                       //obscure text
                       Text{"the hammer reveals a #spider on a mountain# holding", /*french*/"", /*spanish*/"el martillo revela #una araña de la montaña# que otorga"},
    });


    hintTable[GC_GS_CENTER_PLATFORM] = HintText::Exclude({
                       //obscure text
                       Text{"a #suspended spider# in Goron City holds", /*french*/"", /*spanish*/"una #araña suspendida# en la Ciudad Goron otorga"},
    });

    hintTable[GC_GS_BOULDER_MAZE] = HintText::Exclude({
                       //obscure text
                       Text{"a spider in a #Goron City crate# holds", /*french*/"", /*spanish*/"una #araña bajo una caja# de la Ciudad Goron otorga"},
    });


    hintTable[KAK_GS_HOUSE_UNDER_CONSTRUCTION] = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a town# holding", /*french*/"", /*spanish*/"la noche del pasado revela una #araña del pueblo# que otorga"},
    });

    hintTable[KAK_GS_SKULLTULA_HOUSE] = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a town# holding", /*french*/"", /*spanish*/"la noche del pasado revela una #araña del pueblo# que otorga"},
    });

    hintTable[KAK_GS_GUARDS_HOUSE] = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a town# holding", /*french*/"", /*spanish*/"la noche del pasado revela una #araña del pueblo# que otorga"},
    });

    hintTable[KAK_GS_TREE] = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a town# holding", /*french*/"", /*spanish*/"la noche del pasado revela una #araña del pueblo# que otorga"},
    });

    hintTable[KAK_GS_WATCHTOWER] = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a town# holding", /*french*/"", /*spanish*/"la noche del pasado revela una #araña del pueblo# que otorga"},
    });

    hintTable[KAK_GS_ABOVE_IMPAS_HOUSE] = HintText::Exclude({
                       //obscure text
                       Text{"night in the future reveals a #spider in a town# holding", /*french*/"", /*spanish*/"la noche del futuro revela una #araña del pueblo# que otorga"},
    });


    hintTable[GRAVEYARD_GS_WALL] = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider in a graveyard# holding", /*french*/"", /*spanish*/"la noche revela una #araña del cementerio# que otorga"},
    });

    hintTable[GRAVEYARD_GS_BEAN_PATCH] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried in a graveyard# holds", /*french*/"", /*spanish*/"una #araña enterrada en el cementerio# otorga"},
    });


    hintTable[ZR_GS_LADDER] = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a river# holding", /*french*/"", /*spanish*/"la noche del pasado revela una #araña del río# que otorga"},
    });

    hintTable[ZR_GS_TREE] = HintText::Exclude({
                       //obscure text
                       Text{"a spider hiding in a #tree by a river# holds", /*french*/"", /*spanish*/"una araña escondida en el #árbol de un río# otorga"},
    });

    hintTable[ZR_GS_ABOVE_BRIDGE] = HintText::Exclude({
                       //obscure text
                       Text{"night in the future reveals a #spider in a river# holding", /*french*/"", /*spanish*/"la noche del futuro revela una #araña del río# que otorga"},
    });

    hintTable[ZR_GS_NEAR_RAISED_GROTTOS] = HintText::Exclude({
                       //obscure text
                       Text{"night in the future reveals a #spider in a river# holding", /*french*/"", /*spanish*/"la noche del futuro revela una #araña del río# que otorga"},
    });


    hintTable[ZD_GS_FROZEN_WATERFALL] = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider by a frozen waterfall# holding", /*french*/"", /*spanish*/"la noche revela una #araña junto a una congelada cascada# que otorga"},
    });

    hintTable[ZF_GS_ABOVE_THE_LOG] = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider near a deity# holding", /*french*/"", /*spanish*/"la noche revela una #araña junto a cierta deidad# que otorga"},
    });

    hintTable[ZF_GS_TREE] = HintText::Exclude({
                       //obscure text
                       Text{"a spider hiding in a #tree near a deity# holds", /*french*/"", /*spanish*/"una araña escondida en el #árbol junto a cierta deidad# otorga"},
    });


    hintTable[LH_GS_BEAN_PATCH] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried by a lake# holds", /*french*/"", /*spanish*/"una #araña enterrada junto a un lago# otorga"},
    });

    hintTable[LH_GS_SMALL_ISLAND] = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider by a lake# holding", /*french*/"", /*spanish*/"la noche revela una #araña junto a un lago# que otorga"},
    });

    hintTable[LH_GS_LAB_WALL] = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider by a lake# holding", /*french*/"", /*spanish*/"la noche revela una #araña junto a un lago# que otorga"},
    });

    hintTable[LH_GS_LAB_CRATE] = HintText::Exclude({
                       //obscure text
                       Text{"a spider deed underwater in a #lab crate# holds", /*french*/"", /*spanish*/"una #araña bajo la sumergida caja de un laboratorio# otorga"},
    });

    hintTable[LH_GS_TREE] = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider by a lake high in a tree# holding", /*french*/"", /*spanish*/"la noche revela #una araña del lago sobre un árbol# que otorga"},
    });


    hintTable[GV_GS_BEAN_PATCH] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried in a valley# holds", /*french*/"", /*spanish*/"una #araña enterrada en un valle# otorga"},
    });

    hintTable[GV_GS_SMALL_BRIDGE] = HintText::Exclude({
                       //obscure text
                       Text{"night in the past reveals a #spider in a valley# holding", /*french*/"", /*spanish*/"la noche del pasado revela una #araña del valle# que otorga"},
    });

    hintTable[GV_GS_PILLAR] = HintText::Exclude({
                       //obscure text
                       Text{"night in the future reveals a #spider in a valley# holding", /*french*/"", /*spanish*/"la noche del futuro revela una #araña del valle# que otorga"},
    });

    hintTable[GV_GS_BEHIND_TENT] = HintText::Exclude({
                       //obscure text
                       Text{"night in the future reveals a #spider in a valley# holding", /*french*/"", /*spanish*/"la noche del futuro revela una #araña del valle# que otorga"},
    });


    hintTable[GF_GS_ARCHERY_RANGE] = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider in a fortress# holding", /*french*/"", /*spanish*/"la noche revela una #araña de una fortaleza# que otorga"},
    });

    hintTable[GF_GS_TOP_FLOOR] = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider in a fortress# holding", /*french*/"", /*spanish*/"la noche revela una #araña de una fortaleza# que otorga"},
    });


    hintTable[COLOSSUS_GS_BEAN_PATCH] = HintText::Exclude({
                       //obscure text
                       Text{"a #spider buried in the desert# holds", /*french*/"", /*spanish*/"una #enterrada en el desierto# otorga"},
    });

    hintTable[COLOSSUS_GS_HILL] = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider deep in the desert# holding", /*french*/"", /*spanish*/"la noche revela una #araña en las profundidades del desierto# que otorga"},
    });

    hintTable[COLOSSUS_GS_TREE] = HintText::Exclude({
                       //obscure text
                       Text{"night reveals a #spider deep in the desert# holding", /*french*/"", /*spanish*/"la noche revela una #araña en las profundidades del desierto# que otorga"},
    });


    hintTable[KF_SHOP_ITEM_1] = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", /*french*/"", /*spanish*/"un #joven dependiente# vende"},
    });

    hintTable[KF_SHOP_ITEM_2] = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", /*french*/"", /*spanish*/"un #joven dependiente# vende"},
    });

    hintTable[KF_SHOP_ITEM_3] = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", /*french*/"", /*spanish*/"un #joven dependiente# vende"},
    });

    hintTable[KF_SHOP_ITEM_4] = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", /*french*/"", /*spanish*/"un #joven dependiente# vende"},
    });

    hintTable[KF_SHOP_ITEM_5] = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", /*french*/"", /*spanish*/"un #joven dependiente# vende"},
    });

    hintTable[KF_SHOP_ITEM_6] = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", /*french*/"", /*spanish*/"un #joven dependiente# vende"},
    });

    hintTable[KF_SHOP_ITEM_7] = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", /*french*/"", /*spanish*/"un #joven dependiente# vende"},
    });

    hintTable[KF_SHOP_ITEM_8] = HintText::Exclude({
                       //obscure text
                       Text{"a #child shopkeeper# sells", /*french*/"", /*spanish*/"un #joven dependiente# vende"},
    });


    hintTable[KAK_POTION_SHOP_ITEM_1] = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", /*french*/"", /*spanish*/"la #tienda de pociones de Kakariko# ofrece"}
    );

    hintTable[KAK_POTION_SHOP_ITEM_2] = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", /*french*/"", /*spanish*/"la #tienda de pociones de Kakariko# ofrece"}
    );

    hintTable[KAK_POTION_SHOP_ITEM_3] = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", /*french*/"", /*spanish*/"la #tienda de pociones de Kakariko# ofrece"}
    );

    hintTable[KAK_POTION_SHOP_ITEM_4] = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", /*french*/"", /*spanish*/"la #tienda de pociones de Kakariko# ofrece"}
    );

    hintTable[KAK_POTION_SHOP_ITEM_5] = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", /*french*/"", /*spanish*/"la #tienda de pociones de Kakariko# ofrece"}
    );

    hintTable[KAK_POTION_SHOP_ITEM_6] = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", /*french*/"", /*spanish*/"la #tienda de pociones de Kakariko# ofrece"}
    );

    hintTable[KAK_POTION_SHOP_ITEM_7] = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", /*french*/"", /*spanish*/"la #tienda de pociones de Kakariko# ofrece"}
    );

    hintTable[KAK_POTION_SHOP_ITEM_8] = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", /*french*/"", /*spanish*/"la #tienda de pociones de Kakariko# ofrece"}
    );


    hintTable[MARKET_BOMBCHU_SHOP_ITEM_1] = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", /*french*/"", /*spanish*/"un #mercader de bombchus# vende"},
    });

    hintTable[MARKET_BOMBCHU_SHOP_ITEM_2] = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", /*french*/"", /*spanish*/"un #mercader de bombchus# vende"},
    });

    hintTable[MARKET_BOMBCHU_SHOP_ITEM_3] = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", /*french*/"", /*spanish*/"un #mercader de bombchus# vende"},
    });

    hintTable[MARKET_BOMBCHU_SHOP_ITEM_4] = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", /*french*/"", /*spanish*/"un #mercader de bombchus# vende"},
    });

    hintTable[MARKET_BOMBCHU_SHOP_ITEM_5] = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", /*french*/"", /*spanish*/"un #mercader de bombchus# vende"},
    });

    hintTable[MARKET_BOMBCHU_SHOP_ITEM_6] = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", /*french*/"", /*spanish*/"un #mercader de bombchus# vende"},
    });

    hintTable[MARKET_BOMBCHU_SHOP_ITEM_7] = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", /*french*/"", /*spanish*/"un #mercader de bombchus# vende"},
    });

    hintTable[MARKET_BOMBCHU_SHOP_ITEM_8] = HintText::Exclude({
                       //obscure text
                       Text{"a #Bombchu merchant# sells", /*french*/"", /*spanish*/"un #mercader de bombchus# vende"},
    });


    hintTable[MARKET_POTION_SHOP_ITEM_1] = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", /*french*/"", /*spanish*/"la #tienda de pociones del mercado# ofrece"}
    );

    hintTable[MARKET_POTION_SHOP_ITEM_2] = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", /*french*/"", /*spanish*/"la #tienda de pociones del mercado# ofrece"}
    );

    hintTable[MARKET_POTION_SHOP_ITEM_3] = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", /*french*/"", /*spanish*/"la #tienda de pociones del mercado# ofrece"}
    );

    hintTable[MARKET_POTION_SHOP_ITEM_4] = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", /*french*/"", /*spanish*/"la #tienda de pociones del mercado# ofrece"}
    );

    hintTable[MARKET_POTION_SHOP_ITEM_5] = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", /*french*/"", /*spanish*/"la #tienda de pociones del mercado# ofrece"}
    );

    hintTable[MARKET_POTION_SHOP_ITEM_6] = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", /*french*/"", /*spanish*/"la #tienda de pociones del mercado# ofrece"}
    );

    hintTable[MARKET_POTION_SHOP_ITEM_7] = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", /*french*/"", /*spanish*/"la #tienda de pociones del mercado# ofrece"}
    );

    hintTable[MARKET_POTION_SHOP_ITEM_8] = HintText::Exclude({
                       //obscure text
                       Text{"a #potion seller# offers", /*french*/"", /*spanish*/"un #vendedor de pociones# ofrece"},
                     },
                       //clear text
                       Text{"the #Market Potion Shop# offers", /*french*/"", /*spanish*/"la #tienda de pociones del mercado# ofrece"}
    );


    hintTable[MARKET_BAZAAR_ITEM_1] = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", /*french*/"", /*spanish*/"el #bazar del mercado# ofrece"},
    });

    hintTable[MARKET_BAZAAR_ITEM_2] = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", /*french*/"", /*spanish*/"el #bazar del mercado# ofrece"},
    });

    hintTable[MARKET_BAZAAR_ITEM_3] = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", /*french*/"", /*spanish*/"el #bazar del mercado# ofrece"},
    });

    hintTable[MARKET_BAZAAR_ITEM_4] = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", /*french*/"", /*spanish*/"el #bazar del mercado# ofrece"},
    });

    hintTable[MARKET_BAZAAR_ITEM_5] = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", /*french*/"", /*spanish*/"el #bazar del mercado# ofrece"},
    });

    hintTable[MARKET_BAZAAR_ITEM_6] = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", /*french*/"", /*spanish*/"el #bazar del mercado# ofrece"},
    });

    hintTable[MARKET_BAZAAR_ITEM_7] = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", /*french*/"", /*spanish*/"el #bazar del mercado# ofrece"},
    });

    hintTable[MARKET_BAZAAR_ITEM_8] = HintText::Exclude({
                       //obscure text
                       Text{"the #Market Bazaar# offers", /*french*/"", /*spanish*/"el #bazar del mercado# ofrece"},
    });


    hintTable[KAK_BAZAAR_ITEM_1] = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", /*french*/"", /*spanish*/"el #bazar de Kakariko# ofrece"},
    });

    hintTable[KAK_BAZAAR_ITEM_2] = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", /*french*/"", /*spanish*/"el #bazar de Kakariko# ofrece"},
    });

    hintTable[KAK_BAZAAR_ITEM_3] = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", /*french*/"", /*spanish*/"el #bazar de Kakariko# ofrece"},
    });

    hintTable[KAK_BAZAAR_ITEM_4] = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", /*french*/"", /*spanish*/"el #bazar de Kakariko# ofrece"},
    });

    hintTable[KAK_BAZAAR_ITEM_5] = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", /*french*/"", /*spanish*/"el #bazar de Kakariko# ofrece"},
    });

    hintTable[KAK_BAZAAR_ITEM_6] = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", /*french*/"", /*spanish*/"el #bazar de Kakariko# ofrece"},
    });

    hintTable[KAK_BAZAAR_ITEM_7] = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", /*french*/"", /*spanish*/"el #bazar de Kakariko# ofrece"},
    });

    hintTable[KAK_BAZAAR_ITEM_8] = HintText::Exclude({
                       //obscure text
                       Text{"the #Kakariko Bazaar# offers", /*french*/"", /*spanish*/"el #bazar de Kakariko# ofrece"},
    });


    hintTable[ZD_SHOP_ITEM_1] = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", /*french*/"", /*spanish*/"el #dependiente zora# vende"},
    });

    hintTable[ZD_SHOP_ITEM_2] = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", /*french*/"", /*spanish*/"el #dependiente zora# vende"},
    });

    hintTable[ZD_SHOP_ITEM_3] = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", /*french*/"", /*spanish*/"el #dependiente zora# vende"},
    });

    hintTable[ZD_SHOP_ITEM_4] = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", /*french*/"", /*spanish*/"el #dependiente zora# vende"},
    });

    hintTable[ZD_SHOP_ITEM_5] = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", /*french*/"", /*spanish*/"el #dependiente zora# vende"},
    });

    hintTable[ZD_SHOP_ITEM_6] = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", /*french*/"", /*spanish*/"el #dependiente zora# vende"},
    });

    hintTable[ZD_SHOP_ITEM_7] = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", /*french*/"", /*spanish*/"el #dependiente zora# vende"},
    });

    hintTable[ZD_SHOP_ITEM_8] = HintText::Exclude({
                       //obscure text
                       Text{"a #Zora shopkeeper# sells", /*french*/"", /*spanish*/"el #dependiente zora# vende"},
    });


    hintTable[GC_SHOP_ITEM_1] = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", /*french*/"", /*spanish*/"el #dependiente goron# vende"},
    });

    hintTable[GC_SHOP_ITEM_2] = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", /*french*/"", /*spanish*/"el #dependiente goron# vende"},
    });

    hintTable[GC_SHOP_ITEM_3] = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", /*french*/"", /*spanish*/"el #dependiente goron# vende"},
    });

    hintTable[GC_SHOP_ITEM_4] = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", /*french*/"", /*spanish*/"el #dependiente goron# vende"},
    });

    hintTable[GC_SHOP_ITEM_5] = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", /*french*/"", /*spanish*/"el #dependiente goron# vende"},
    });

    hintTable[GC_SHOP_ITEM_6] = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", /*french*/"", /*spanish*/"el #dependiente goron# vende"},
    });

    hintTable[GC_SHOP_ITEM_7] = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", /*french*/"", /*spanish*/"el #dependiente goron# vende"},
    });

    hintTable[GC_SHOP_ITEM_8] = HintText::Exclude({
                       //obscure text
                       Text{"a #Goron shopkeeper# sells", /*french*/"", /*spanish*/"el #dependiente goron# vende"},
    });


    hintTable[DEKU_TREE_MQ_DEKU_SCRUB] = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub in the Deku Tree# sells", /*french*/"", /*spanish*/"un #deku del Árbol Deku# vende"},
    });


    hintTable[HF_DEKU_SCRUB_GROTTO] = HintText::Exclude({
                       //obscure text
                       Text{"a lonely #scrub in a hole# sells", /*french*/"", /*spanish*/"un #singular deku bajo un hoyo# vende"},
    });

    hintTable[LLR_DEKU_SCRUB_GROTTO_LEFT] = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"", /*spanish*/"un #trío de dekus# vende"},
    });

    hintTable[LLR_DEKU_SCRUB_GROTTO_RIGHT] = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"", /*spanish*/"un #trío de dekus# vende"},
    });

    hintTable[LLR_DEKU_SCRUB_GROTTO_CENTER] = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"", /*spanish*/"un #trío de dekus# vende"},
    });

    hintTable[LW_DEKU_SCRUB_NEAR_DEKU_THEATER_RIGHT] = HintText::Exclude({
                       //obscure text
                       Text{"a pair of #scrubs in the woods# sells", /*french*/"", /*spanish*/"un par de #dekus del bosque# vende"},
    });

    hintTable[LW_DEKU_SCRUB_NEAR_DEKU_THEATER_LEFT] = HintText::Exclude({
                       //obscure text
                       Text{"a pair of #scrubs in the woods# sells", /*french*/"", /*spanish*/"un par de #dekus del bosque# vende"},
    });

    hintTable[LW_DEKU_SCRUB_NEAR_BRIDGE] = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub by a bridge# sells", /*french*/"", /*spanish*/"un #deku bajo un puente# vende"},
    });

    hintTable[LW_DEKU_SCRUB_GROTTO_REAR] = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"", /*spanish*/"un #par de dekus subterráneos# vende"},
    });

    hintTable[LW_DEKU_SCRUB_GROTTO_FRONT] = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"", /*spanish*/"un #par de dekus subterráneos# vende"},
    });


    hintTable[SFM_DEKU_SCRUB_GROTTO_REAR] = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"", /*spanish*/"un #par de dekus subterráneos# vende"},
    });

    hintTable[SFM_DEKU_SCRUB_GROTTO_FRONT] = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"", /*spanish*/"un #par de dekus subterráneos# vende"},
    });


    hintTable[GC_DEKU_SCRUB_GROTTO_LEFT] = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"", /*spanish*/"un #trío de dekus# vende"},
    });

    hintTable[GC_DEKU_SCRUB_GROTTO_RIGHT] = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"", /*spanish*/"un #trío de dekus# vende"},
    });

    hintTable[GC_DEKU_SCRUB_GROTTO_CENTER] = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"", /*spanish*/"un #trío de dekus# vende"},
    });

    hintTable[DODONGOS_CAVERN_DEKU_SCRUB_NEAR_BOMB_BAG_LEFT] = HintText::Exclude({
                       //obscure text
                       Text{"a pair of #scrubs in Dodongo's Cavern# sells", /*french*/"", /*spanish*/"un #par de dekus en la Cueva de los Dodongos# vende"},
    });

    hintTable[DODONGOS_CAVERN_DEKU_SCRUB_SIDE_ROOM_NEAR_DODONGOS] = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub guarded by Lizalfos# sells", /*french*/"", /*spanish*/"un #deku custodiado por Lizalfos# vende"},
    });

    hintTable[DODONGOS_CAVERN_DEKU_SCRUB_NEAR_BOMB_BAG_RIGHT] = HintText::Exclude({
                       //obscure text
                       Text{"a pair of #scrubs in Dodongo's Cavern# sells", /*french*/"", /*spanish*/"un #par de dekus en la Cueva de los Dodongos# vende"},
    });

    hintTable[DODONGOS_CAVERN_DEKU_SCRUB_LOBBY] = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub in Dodongo's Cavern# sells", /*french*/"", /*spanish*/"un #deku en la Cueva de los Dodongos# vende"},
    });


    hintTable[DODONGOS_CAVERN_MQ_DEKU_SCRUB_LOBBY_REAR] = HintText::Exclude({
                       //obscure text
                       Text{"a pair of #scrubs in Dodongo's Cavern# sells", /*french*/"", /*spanish*/"un #par de dekus en la Cueva de los Dodongos# vende"},
    });

    hintTable[DODONGOS_CAVERN_MQ_DEKU_SCRUB_LOBBY_FRONT] = HintText::Exclude({
                       //obscure text
                       Text{"a pair of #scrubs in Dodongo's Cavern# sells", /*french*/"", /*spanish*/"un #par de dekus en la Cueva de los Dodongos# vende"},
    });

    hintTable[DODONGOS_CAVERN_MQ_DEKU_SCRUB_STAIRCASE] = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub in Dodongo's Cavern# sells", /*french*/"", /*spanish*/"un #deku en la Cueva de los Dodongos# vende"},
    });

    hintTable[DODONGOS_CAVERN_MQ_DEKU_SCRUB_SIDE_ROOM_NEAR_LOWER_LIZALFOS] = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub guarded by Lizalfos# sells", /*french*/"", /*spanish*/"un #deku custodiado por Lizalfos# vende"},
    });

    hintTable[DMC_DEKU_SCRUB_GROTTO_LEFT] = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"", /*spanish*/"un #trío de dekus# vende"},
    });

    hintTable[DMC_DEKU_SCRUB_GROTTO_RIGHT] = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"", /*spanish*/"un #trío de dekus# vende"},
    });

    hintTable[DMC_DEKU_SCRUB_GROTTO_CENTER] = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"", /*spanish*/"un #trío de dekus# vende"},
    });


    hintTable[ZR_DEKU_SCRUB_GROTTO_REAR] = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"", /*spanish*/"un #par de dekus subterráneos# vende"},
    });

    hintTable[ZR_DEKU_SCRUB_GROTTO_FRONT] = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"", /*spanish*/"un #par de dekus subterráneos# vende"},
    });


    hintTable[JABU_JABUS_BELLY_DEKU_SCRUB] = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub in a deity# sells", /*french*/"", /*spanish*/"un #deku dentro de cierta deidad# vende"},
    });


    hintTable[LH_DEKU_SCRUB_GROTTO_LEFT] = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"", /*spanish*/"un #trío de dekus# vende"},
    });

    hintTable[LH_DEKU_SCRUB_GROTTO_RIGHT] = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"", /*spanish*/"un #trío de dekus# vende"},
    });

    hintTable[LH_DEKU_SCRUB_GROTTO_CENTER] = HintText::Exclude({
                       //obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"", /*spanish*/"un #trío de dekus# vende"},
    });


    hintTable[GV_DEKU_SCRUB_GROTTO_REAR] = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"", /*spanish*/"un #par de dekus subterráneos# vende"},
    });

    hintTable[GV_DEKU_SCRUB_GROTTO_FRONT] = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"", /*spanish*/"un #par de dekus subterráneos# vende"},
    });


    hintTable[COLOSSUS_DEKU_SCRUB_GROTTO_FRONT] = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"", /*spanish*/"un #par de dekus subterráneos# vende"},
    });

    hintTable[COLOSSUS_DEKU_SCRUB_GROTTO_REAR] = HintText::Exclude({
                       //obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"", /*spanish*/"un #par de dekus subterráneos# vende"},
    });


    hintTable[GANONS_CASTLE_DEKU_SCRUB_CENTER_LEFT] = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", /*french*/"", /*spanish*/"los #dekus del Castillo de Ganondorf# venden"},
    });

    hintTable[GANONS_CASTLE_DEKU_SCRUB_CENTER_RIGHT] = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", /*french*/"", /*spanish*/"los #dekus del Castillo de Ganondorf# venden"},
    });

    hintTable[GANONS_CASTLE_DEKU_SCRUB_RIGHT] = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", /*french*/"", /*spanish*/"los #dekus del Castillo de Ganondorf# venden"},
    });

    hintTable[GANONS_CASTLE_DEKU_SCRUB_LEFT] = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", /*french*/"", /*spanish*/"los #dekus del Castillo de Ganondorf# venden"},
    });


    hintTable[GANONS_CASTLE_MQ_DEKU_SCRUB_RIGHT] = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", /*french*/"", /*spanish*/"los #dekus del Castillo de Ganondorf# venden"},
    });

    hintTable[GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER_LEFT] = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", /*french*/"", /*spanish*/"los #dekus del Castillo de Ganondorf# venden"},
    });

    hintTable[GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER] = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", /*french*/"", /*spanish*/"los #dekus del Castillo de Ganondorf# venden"},
    });

    hintTable[GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER_RIGHT] = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", /*french*/"", /*spanish*/"los #dekus del Castillo de Ganondorf# venden"},
    });

    hintTable[GANONS_CASTLE_MQ_DEKU_SCRUB_LEFT] = HintText::Exclude({
                       //obscure text
                       Text{"#scrubs in Ganon's Castle# sell", /*french*/"", /*spanish*/"los #dekus del Castillo de Ganondorf# venden"},
    });


    hintTable[LLR_STABLES_LEFT_COW] = HintText::Exclude({
                       //obscure text
                       Text{"a #cow in a stable# gifts", /*french*/"", /*spanish*/"una #vaca del establo# brinda"},
    });

    hintTable[LLR_STABLES_RIGHT_COW] = HintText::Exclude({
                       //obscure text
                       Text{"a #cow in a stable# gifts", /*french*/"", /*spanish*/"una #vaca del establo# brinda"},
    });

    hintTable[LLR_TOWER_RIGHT_COW] = HintText::Exclude({
                       //obscure text
                       Text{"a #cow in a ranch silo# gifts", /*french*/"", /*spanish*/"una #vaca del granero# brinda"},
    });

    hintTable[LLR_TOWER_LEFT_COW] = HintText::Exclude({
                       //obscure text
                       Text{"a #cow in a ranch silo# gifts", /*french*/"", /*spanish*/"una #vaca del granero# brinda"},
    });

    hintTable[KAK_IMPAS_HOUSE_COW] = HintText::Exclude({
                       //obscure text
                       Text{"a #cow imprisoned in a house# protects", /*french*/"", /*spanish*/"una #vaca enjaulada de una casa# brinda"},
    });

    hintTable[DMT_COW_GROTTO_COW] = HintText::Exclude({
                       //obscure text
                       Text{"a #cow in a luxurious hole# offers", /*french*/"", /*spanish*/"una #vaca de un lujoso hoyo# brinda"},
    });

    /*--------------------------
    |    ENTRANCE HINT TEXT    |
    ---------------------------*/

    hintTable[DESERT_COLOSSUS_TO_COLOSSUS_GROTTO] = HintText::Entrance({
                     //obscure text
                     Text{"lifting a #rock in the desert# reveals", /*french*/"", /*spanish*/"levantar una #roca del desierto# revela"},
    });

    hintTable[GV_GROTTO_LEDGE_TO_GV_OCTOROK_GROTTO] = HintText::Entrance({
                     //obscure text
                     Text{"a rock on #a ledge in the valley# hides", /*french*/"", /*spanish*/"levantar una #roca al borde del valle# esconde"},
    });

    hintTable[GC_GROTTO_PLATFORM_TO_GC_GROTTO] = HintText::Entrance({
                     //obscure text
                     Text{"a #pool of lava# in Goron City blocks the way to", /*french*/"", /*spanish*/"un #estanque de lava# en la Ciudad Goron bloquea el paso a"},
    });

    hintTable[GERUDO_FORTRESS_TO_GF_STORMS_GROTTO] = HintText::Entrance({
                     //obscure text
                     Text{"a #storm within Gerudo's Fortress# reveals", /*french*/"", /*spanish*/"una #tormenta en la Fortaleza Gerudo# revela"},
    });

    hintTable[ZORAS_DOMAIN_TO_ZD_STORMS_GROTTO] = HintText::Entrance({
                     //obscure text
                     Text{"a #storm within Zora's Domain# reveals", /*french*/"", /*spanish*/"una #tormenta en la Región de los Zora# revela"},
    });

    hintTable[HYRULE_CASTLE_GROUNDS_TO_HC_STORMS_GROTTO] = HintText::Entrance({
                     //obscure text
                     Text{"a #storm near the castle# reveals", /*french*/"", /*spanish*/"una #tormenta junto al castillo# revela"},
    });

    hintTable[GV_FORTRESS_SIDE_TO_GV_STORMS_GROTTO] = HintText::Entrance({
                     //obscure text
                     Text{"a #storm in the valley# reveals", /*french*/"", /*spanish*/"una #tormenta en el valle# revela"},
    });

    hintTable[DESERT_COLOSSUS_TO_COLOSSUS_GREAT_FAIRY_FOUNTAIN] = HintText::Entrance({
                     //obscure text
                     Text{"a #fractured desert wall# hides", /*french*/"", /*spanish*/"una #agrietada pared del desierto# esconde"},
    });

    hintTable[GANONS_CASTLE_GROUNDS_TO_OGC_GREAT_FAIRY_FOUNTAIN] = HintText::Entrance({
                     //obscure text
                     Text{"a #heavy pillar# outside the castle obstructs", /*french*/"", /*spanish*/"una #pesada columna# fuera del castillo obstruye"},
    });

    hintTable[ZORAS_FOUNTAIN_TO_ZF_GREAT_FAIRY_FOUNTAIN] = HintText::Entrance({
                     //obscure text
                     Text{"a #fountain wall# hides", /*french*/"", /*spanish*/"una #pared de la fuente# esconde"},
    });

    hintTable[GV_FORTRESS_SIDE_TO_GV_CARPENTER_TENT] = HintText::Entrance({
                     //obscure text
                     Text{"a #tent in the valley# covers", /*french*/"", /*spanish*/"una #tienda de campaña del valle# cubre"},
    });

    hintTable[GRAVEYARD_WARP_PAD_REGION_TO_SHADOW_TEMPLE_ENTRYWAY] = HintText::Entrance({
                     //obscure text
                     Text{"at the #back of the Graveyard#, there is", /*french*/"", /*spanish*/"en la #parte trasera del cementerio# se halla"},
    });

    hintTable[LAKE_HYLIA_TO_WATER_TEMPLE_LOBBY] = HintText::Entrance({
                     //obscure text
                     Text{"deep #under a vast lake#, one can find", /*french*/"", /*spanish*/"en las #profundidades de un lago inmenso# se halla"},
    });

    hintTable[GERUDO_FORTRESS_TO_GERUDO_TRAINING_GROUNDS_LOBBY] = HintText::Entrance({
                     //obscure text
                     Text{"paying a #fee to the Gerudos# grants access to", /*french*/"", /*spanish*/"pagarle una #tasa a las gerudo# da acceso a"},
    });

    hintTable[ZORAS_FOUNTAIN_TO_JABU_JABUS_BELLY_BEGINNING] = HintText::Entrance({
                     //obscure text
                     Text{"inside #Jabu Jabu#, one can find", /*french*/"", /*spanish*/"dentro de #Jabu Jabu# se halla"},
    });

    hintTable[KAKARIKO_VILLAGE_TO_BOTTOM_OF_THE_WELL] = HintText::Entrance({
                     //obscure text
                     Text{"a #village well# leads to", /*french*/"", /*spanish*/"el #pozo de un pueblo# conduce a"},
    });

    /*--------------------------
    |      EXIT HINT TEXT      |
    ---------------------------*/
    //maybe make a new type for this? I'm not sure if it really matters

    hintTable[LINKS_POCKET] = HintText::Exclude({
                     //obscure text
                     Text{"Link's Pocket", /*french*/"", /*spanish*/"el bolsillo de Link"},
    });

    hintTable[KOKIRI_FOREST] = HintText::Exclude({
                     //obscure text
                     Text{"Kokiri Forest", /*french*/"", /*spanish*/"el Bosque Kokiri"},
    });

    hintTable[THE_LOST_WOODS] = HintText::Exclude({
                     //obscure text
                     Text{"the Lost Woods", /*french*/"", /*spanish*/"el Bosque Perdido"},
    });

    hintTable[SACRED_FOREST_MEADOW] = HintText::Exclude({
                     //obscure text
                     Text{"Sacred Forest Meadow", /*french*/"", /*spanish*/"la pradera sagrada del bosque"},
    });

    hintTable[HYRULE_FIELD] = HintText::Exclude({
                     //obscure text
                     Text{"Hyrule Field", /*french*/"", /*spanish*/"en la Llanura de Hyrule"},
    });

    hintTable[LAKE_HYLIA] = HintText::Exclude({
                     //obscure text
                     Text{"Lake Hylia", /*french*/"", /*spanish*/"el Lago Hylia"},
    });

    hintTable[GERUDO_VALLEY] = HintText::Exclude({
                     //obscure text
                     Text{"Gerudo Valley", /*french*/"", /*spanish*/"el Valle Gerudo"},
    });

    hintTable[GERUDO_FORTRESS] = HintText::Exclude({
                     //obscure text
                     Text{"Gerudo's Fortress", /*french*/"", /*spanish*/"la fortaleza gerudo"},
    });

    hintTable[HAUNTED_WASTELAND] = HintText::Exclude({
                     //obscure text
                     Text{"Haunted Wasteland", /*french*/"", /*spanish*/"el desierto encantado"},
    });

    hintTable[DESERT_COLOSSUS] = HintText::Exclude({
                     //obscure text
                     Text{"Desert Colossus", /*french*/"", /*spanish*/"el Coloso del Desierto"},
    });

    hintTable[THE_MARKET] = HintText::Exclude({
                     //obscure text
                     Text{"the Market", /*french*/"", /*spanish*/"la plaza del mercado"},
    });

    hintTable[TEMPLE_OF_TIME] = HintText::Exclude({
                     //obscure text
                     Text{"Temple of Time", /*french*/"", /*spanish*/"el Templo del Tiempo"},
    });

    hintTable[HYRULE_CASTLE] = HintText::Exclude({
                     //obscure text
                     Text{"Hyrule Castle", /*french*/"", /*spanish*/"el Castillo de Hyrule"},
    });

    hintTable[OUTSIDE_GANONS_CASTLE] = HintText::Exclude({
                     //obscure text
                     Text{"outside Ganon's Castle", /*french*/"", /*spanish*/"las afueras del Castillo de Ganon"},
    });

    hintTable[KAKARIKO_VILLAGE] = HintText::Exclude({
                     //obscure text
                     Text{"Kakariko Village", /*french*/"", /*spanish*/"Kakariko"},
    });

    hintTable[THE_GRAVEYARD] = HintText::Exclude({
                     //obscure text
                     Text{"the Graveyard", /*french*/"", /*spanish*/"el cementerio"},
    });

    hintTable[DEATH_MOUNTAIN_TRAIL] = HintText::Exclude({
                     //obscure text
                     Text{"Death Mountain Trail", /*french*/"", /*spanish*/"el sendero de la Montaña de la Muerte"},
    });

    hintTable[GORON_CITY] = HintText::Exclude({
                     //obscure text
                     Text{"Goron City", /*french*/"", /*spanish*/"la Ciudad Goron"},
    });

    hintTable[DEATH_MOUNTAIN_CRATER] = HintText::Exclude({
                     //obscure text
                     Text{"Death Mountain Crater", /*french*/"", /*spanish*/"el cráter de la Montaña de la Muerte"},
    });

    hintTable[ZORAS_RIVER] = HintText::Exclude({
                     //obscure text
                     Text{"Zora's River", /*french*/"", /*spanish*/"el Río Zora"},
    });

    hintTable[ZORAS_DOMAIN] = HintText::Exclude({
                     //obscure text
                     Text{"Zora's Domain", /*french*/"", /*spanish*/"la Región de los Zora"},
    });

    hintTable[ZORAS_FOUNTAIN] = HintText::Exclude({
                     //obscure text
                     Text{"Zora's Fountain", /*french*/"", /*spanish*/"la Fuente Zora"},
    });

    hintTable[LON_LON_RANCH] = HintText::Exclude({
                     //obscure text
                     Text{"Lon Lon Ranch", /*french*/"", /*spanish*/"el Rancho Lon Lon"},
    });


    /*--------------------------
    |     REGION HINT TEXT     |
    ---------------------------*/

    hintTable[KF_LINKS_HOUSE] = HintText::Region({
                     //obscure text
                     Text{"Link's House", /*french*/"", /*spanish*/"la casa de Link"},
    });

    hintTable[TOT_MAIN] = HintText::Region({
                     //obscure text
                     Text{"the #Temple of Time#", /*french*/"", /*spanish*/"el Templo del Tiempo"},
    });

    hintTable[KF_MIDOS_HOUSE] = HintText::Region({
                     //obscure text
                     Text{"Mido's house", /*french*/"", /*spanish*/"la casa de Mido"},
    });

    hintTable[KF_SARIAS_HOUSE] = HintText::Region({
                     //obscure text
                     Text{"Saria's House", /*french*/"", /*spanish*/"la casa de Saria"},
    });

    hintTable[KF_HOUSE_OF_TWINS] = HintText::Region({
                     //obscure text
                     Text{"the #House of Twins#", /*french*/"", /*spanish*/"la casa de las gemelas"},
    });

    hintTable[KF_KNOW_IT_ALL_HOUSE] = HintText::Region({
                     //obscure text
                     Text{"Know-It-All Brothers' House", /*french*/"", /*spanish*/"la casa de los hermanos Sabelotodo"},
    });

    hintTable[KF_KOKIRI_SHOP] = HintText::Region({
                     //obscure text
                     Text{"the #Kokiri Shop#", /*french*/"", /*spanish*/"la Tienda Kokiri"},
    });

    hintTable[LH_LAB] = HintText::Region({
                     //obscure text
                     Text{"the #Lakeside Laboratory#", /*french*/"", /*spanish*/"el laboratorio del lago"},
    });

    hintTable[LH_FISHING_HOLE] = HintText::Region({
                     //obscure text
                     Text{"the #Fishing Pond#", /*french*/"", /*spanish*/"el estanque"},
    });

    hintTable[GV_CARPENTER_TENT] = HintText::Region({
                     //obscure text
                     Text{"the #Carpenters' tent#", /*french*/"", /*spanish*/"la #tienda de campaña de los carpinteros#"},
    });

    hintTable[MARKET_GUARD_HOUSE] = HintText::Region({
                     //obscure text
                     Text{"the #Guard House#", /*french*/"", /*spanish*/"la caseta de guardia"},
    });

    hintTable[MARKET_MASK_SHOP] = HintText::Region({
                     //obscure text
                     Text{"the #Happy Mask Shop#", /*french*/"", /*spanish*/"la Tienda de La Máscara Feliz"},
    });

    hintTable[MARKET_BOMBCHU_BOWLING] = HintText::Region({
                     //obscure text
                     Text{"the #Bombchu Bowling Alley#", /*french*/"", /*spanish*/"la Bolera Bombchu"},
    });

    hintTable[MARKET_POTION_SHOP] = HintText::Region({
                     //obscure text
                     Text{"the #Market Potion Shop#", /*french*/"", /*spanish*/"la tienda de pociones de la plaza del mercado"},
    });

    hintTable[MARKET_TREASURE_CHEST_GAME] = HintText::Region({
                     //obscure text
                     Text{"the #Treasure Box Shop#", /*french*/"", /*spanish*/"el Cofre del Tesoro"},
    });

    hintTable[MARKET_BOMBCHU_SHOP] = HintText::Region({
                     //obscure text
                     Text{"the #Bombchu Shop#", /*french*/"", /*spanish*/"la Tienda Bombchu"},
    });

    hintTable[MARKET_MAN_IN_GREEN_HOUSE] = HintText::Region({
                     //obscure text
                     Text{"Man in Green's House", /*french*/"", /*spanish*/"la casa del hombre de verde"},
    });

    hintTable[KAK_WINDMILL] = HintText::Region({
                     //obscure text
                     Text{"the #Windmill#", /*french*/"", /*spanish*/"el #molino#"},
    });

    hintTable[KAK_CARPENTER_BOSS_HOUSE] = HintText::Region({
                     //obscure text
                     Text{"the #Carpenters' Boss House#", /*french*/"", /*spanish*/"la casa del capataz de los carpinteros"},
    });

    hintTable[KAK_HOUSE_OF_SKULLTULA] = HintText::Region({
                     //obscure text
                     Text{"the #House of Skulltula#", /*french*/"", /*spanish*/"la casa de las skulltulas"},
    });

    hintTable[KAK_IMPAS_HOUSE] = HintText::Region({
                     //obscure text
                     Text{"Impa's House", /*french*/"", /*spanish*/"la casa de Impa"},
    });

    hintTable[KAK_IMPAS_HOUSE_BACK] = HintText::Region({
                     //obscure text
                     Text{"Impa's cow cage", /*french*/"", /*spanish*/"la jaula de la vaca de Impa"},
    });

    hintTable[KAK_ODD_MEDICINE_BUILDING] = HintText::Region({
                     //obscure text
                     Text{"Granny's Potion Shop", /*french*/"", /*spanish*/"la tienda de pociones de la abuela"},
    });

    hintTable[GRAVEYARD_DAMPES_HOUSE] = HintText::Region({
                     //obscure text
                     Text{"Dampé's Hut", /*french*/"", /*spanish*/"la cabaña de Dampé"},
    });

    hintTable[GC_SHOP] = HintText::Region({
                     //obscure text
                     Text{"the #Goron Shop#", /*french*/"", /*spanish*/"la #tienda goron"},
    });

    hintTable[ZD_SHOP] = HintText::Region({
                     //obscure text
                     Text{"the #Zora Shop#", /*french*/"", /*spanish*/"la #tienda zora"},
    });

    hintTable[LLR_TALONS_HOUSE] = HintText::Region({
                     //obscure text
                     Text{"Talon's House", /*french*/"", /*spanish*/"la casa de Talon"},
    });

    hintTable[LLR_STABLES] = HintText::Region({
                     //obscure text
                     Text{"a #stable#", /*french*/"", /*spanish*/"el establo"},
    });

    hintTable[LLR_TOWER] = HintText::Region({
                     //obscure text
                     Text{"the #Lon Lon Tower#", /*french*/"", /*spanish*/"la torre Lon Lon"},
    });

    hintTable[MARKET_BAZAAR] = HintText::Region({
                     //obscure text
                     Text{"the #Market Bazaar#", /*french*/"", /*spanish*/"el bazar de la plaza del mercado"},
    });

    hintTable[MARKET_SHOOTING_GALLERY] = HintText::Region({
                     //obscure text
                     Text{"a #Slingshot Shooting Gallery#", /*french*/"", /*spanish*/"el Tiro al Blanco con tirachinas"},
    });

    hintTable[KAK_BAZAAR] = HintText::Region({
                     //obscure text
                     Text{"the #Kakariko Bazaar#", /*french*/"", /*spanish*/"el bazar de Kakariko"},
    });

    hintTable[KAK_POTION_SHOP_FRONT] = HintText::Region({
                     //obscure text
                     Text{"the #Kakariko Potion Shop#", /*french*/"", /*spanish*/"la tienda de pociones de Kakariko"},
    });

    hintTable[KAK_POTION_SHOP_BACK] = HintText::Region({
                     //obscure text
                     Text{"the #Kakariko Potion Shop#", /*french*/"", /*spanish*/"la tienda de pociones de Kakariko"},
    });

    hintTable[KAK_SHOOTING_GALLERY] = HintText::Region({
                     //obscure text
                     Text{"a #Bow Shooting Gallery#", /*french*/"", /*spanish*/"el Tiro al Blanco con arco"},
    });

    hintTable[COLOSSUS_GREAT_FAIRY_FOUNTAIN] = HintText::Region({
                     //obscure text
                     Text{"a #Great Fairy Fountain#", /*french*/"", /*spanish*/"una fuente de la Gran Hada"},
    });

    hintTable[HC_GREAT_FAIRY_FOUNTAIN] = HintText::Region({
                     //obscure text
                     Text{"a #Great Fairy Fountain#", /*french*/"", /*spanish*/"una fuente de la Gran Hada"},
    });

    hintTable[OGC_GREAT_FAIRY_FOUNTAIN] = HintText::Region({
                     //obscure text
                     Text{"a #Great Fairy Fountain#", /*french*/"", /*spanish*/"una fuente de la Gran Hada"},
    });

    hintTable[DMC_GREAT_FAIRY_FOUNTAIN] = HintText::Region({
                     //obscure text
                     Text{"a #Great Fairy Fountain#", /*french*/"", /*spanish*/"una fuente de la Gran Hada"},
    });

    hintTable[DMT_GREAT_FAIRY_FOUNTAIN] = HintText::Region({
                     //obscure text
                     Text{"a #Great Fairy Fountain#", /*french*/"", /*spanish*/"una fuente de la Gran Hada"},
    });

    hintTable[ZF_GREAT_FAIRY_FOUNTAIN] = HintText::Region({
                     //obscure text
                     Text{"a #Great Fairy Fountain#", /*french*/"", /*spanish*/"una fuente de la Gran Hada"},
    });

    hintTable[GRAVEYARD_SHIELD_GRAVE] = HintText::Region({
                     //obscure text
                     Text{"a #grave with a free chest#", /*french*/"", /*spanish*/"la #tumba del cofre gratis#"},
    });

    hintTable[GRAVEYARD_HEART_PIECE_GRAVE] = HintText::Region({
                     //obscure text
                     Text{"a chest spawned by #Sun's Song#", /*french*/"", /*spanish*/"la #tumba de la Canción del Sol#"},
    });

    hintTable[GRAVEYARD_COMPOSERS_GRAVE] = HintText::Region({
                     //obscure text
                     Text{"the #Composers' Grave#", /*french*/"", /*spanish*/"el #Panteón Real#"},
    });

    hintTable[GRAVEYARD_DAMPES_GRAVE] = HintText::Region({
                     //obscure text
                     Text{"Dampé's Grave", /*french*/"", /*spanish*/"la #tumba de Dampé"},
    });

    hintTable[DMT_COW_GROTTO] = HintText::Region({
                     //obscure text
                     Text{"a solitary #Cow#", /*french*/"", /*spanish*/"una #vaca# solitaria"},
    });

    hintTable[HC_STORMS_GROTTO] = HintText::Region({
                     //obscure text
                     Text{"a sandy grotto with #fragile walls#", /*french*/"", /*spanish*/"la arenosa gruta de #frágiles paredes#"},
    });

    hintTable[HF_TEKTITE_GROTTO] = HintText::Region({
                     //obscure text
                     Text{"a pool guarded by a #Tektite#", /*french*/"", /*spanish*/"un charco custodiado por un #Tektite#"},
    });

    hintTable[HF_NEAR_KAK_GROTTO] = HintText::Region({
                     //obscure text
                     Text{"a #Big Skulltula# guarding a Gold one", /*french*/"", /*spanish*/"un #skulltula# custodiando una dorada"},
    });

    hintTable[HF_COW_GROTTO] = HintText::Region({
                     //obscure text
                     Text{"a grotto full of #spider webs#", /*french*/"", /*spanish*/"una gruta llena de #telarañas#"},
    });

    hintTable[KAK_REDEAD_GROTTO] = HintText::Region({
                     //obscure text
                     Text{"#ReDeads# guarding a chest", /*french*/"", /*spanish*/"los #ReDeads# que custodian un cofre"},
    });

    hintTable[SFM_WOLFOS_GROTTO] = HintText::Region({
                     //obscure text
                     Text{"#Wolfos# guarding a chest", /*french*/"", /*spanish*/"los #Wolfos# que custodian un cofre"},
    });

    hintTable[GV_OCTOROK_GROTTO] = HintText::Region({
                     //obscure text
                     Text{"an #Octorok# guarding a rich pool", /*french*/"", /*spanish*/"un #Octorok# que custodia un lujoso charco"},
    });

    hintTable[DEKU_THEATER] = HintText::Region({
                     //obscure text
                     Text{"the #Lost Woods Stage#", /*french*/"", /*spanish*/"el #escenario del Bosque Perdido#"},
    });

    hintTable[ZR_OPEN_GROTTO] = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", /*french*/"", /*spanish*/"una #gruta genérica#"},
    });

    hintTable[DMC_UPPER_GROTTO] = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", /*french*/"", /*spanish*/"una #gruta genérica#"},
    });

    hintTable[DMT_STORMS_GROTTO] = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", /*french*/"", /*spanish*/"una #gruta genérica#"},
    });

    hintTable[KAK_OPEN_GROTTO] = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", /*french*/"", /*spanish*/"una #gruta genérica#"},
    });

    hintTable[HF_NEAR_MARKET_GROTTO] = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", /*french*/"", /*spanish*/"una #gruta genérica#"},
    });

    hintTable[HF_OPEN_GROTTO] = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", /*french*/"", /*spanish*/"una #gruta genérica#"},
    });

    hintTable[HF_SOUTHEAST_GROTTO] = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", /*french*/"", /*spanish*/"una #gruta genérica#"},
    });

    hintTable[KF_STORMS_GROTTO] = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", /*french*/"", /*spanish*/"una #gruta genérica#"},
    });

    hintTable[LW_NEAR_SHORTCUTS_GROTTO] = HintText::Region({
                     //obscure text
                     Text{"a #generic grotto#", /*french*/"", /*spanish*/"una #gruta genérica#"},
    });

    hintTable[HF_INSIDE_FENCE_GROTTO] = HintText::Region({
                     //obscure text
                     Text{"a #single Upgrade Deku Scrub#", /*french*/"", /*spanish*/"un #solitario mercader deku de mejora#"},
    });

    hintTable[LW_SCRUBS_GROTTO] = HintText::Region({
                     //obscure text
                     Text{"#2 Deku Scrubs# including an Upgrade one", /*french*/"", /*spanish*/"unos #dos mercaderes deku, incluyendo uno de mejora#"},
    });

    hintTable[COLOSSUS_GROTTO] = HintText::Region({
                     //obscure text
                     Text{"2 Deku Scrubs", /*french*/"", /*spanish*/"unos #dos mercaderes deku#"},
    });

    hintTable[ZR_STORMS_GROTTO] = HintText::Region({
                     //obscure text
                     Text{"2 Deku Scrubs", /*french*/"", /*spanish*/"unos #dos mercaderes deku#"},
    });

    hintTable[SFM_STORMS_GROTTO] = HintText::Region({
                     //obscure text
                     Text{"2 Deku Scrubs", /*french*/"", /*spanish*/"unos #dos mercaderes deku#"},
    });

    hintTable[GV_STORMS_GROTTO] = HintText::Region({
                     //obscure text
                     Text{"2 Deku Scrubs", /*french*/"", /*spanish*/"unos #dos mercaderes deku#"},
    });

    hintTable[LH_GROTTO] = HintText::Region({
                     //obscure text
                     Text{"3 Deku Scrubs", /*french*/"", /*spanish*/"unos #tres mercaderes deku#"},
    });

    hintTable[DMC_HAMMER_GROTTO] = HintText::Region({
                     //obscure text
                     Text{"3 Deku Scrubs", /*french*/"", /*spanish*/"unos #tres mercaderes deku#"},
    });

    hintTable[GC_GROTTO] = HintText::Region({
                     //obscure text
                     Text{"3 Deku Scrubs", /*french*/"", /*spanish*/"unos #tres mercaderes deku#"},
    });

    hintTable[LLR_GROTTO] = HintText::Region({
                     //obscure text
                     Text{"3 Deku Scrubs", /*french*/"", /*spanish*/"unos #tres mercaderes deku#"},
    });

    hintTable[ZR_FAIRY_GROTTO] = HintText::Region({
                     //obscure text
                     Text{"a small #Fairy Fountain#", /*french*/"", /*spanish*/"una pequeña #fuente de las hadas#"},
    });

    hintTable[HF_FAIRY_GROTTO] = HintText::Region({
                     //obscure text
                     Text{"a small #Fairy Fountain#", /*french*/"", /*spanish*/"una pequeña #fuente de las hadas#"},
    });

    hintTable[SFM_FAIRY_GROTTO] = HintText::Region({
                     //obscure text
                     Text{"a small #Fairy Fountain#", /*french*/"", /*spanish*/"una pequeña #fuente de las hadas#"},
    });

    hintTable[ZD_STORMS_GROTTO] = HintText::Region({
                     //obscure text
                     Text{"a small #Fairy Fountain#", /*french*/"", /*spanish*/"una pequeña #fuente de las hadas#"},
    });

    hintTable[GF_STORMS_GROTTO] = HintText::Region({
                     //obscure text
                     Text{"a small #Fairy Fountain#", /*french*/"", /*spanish*/"una pequeña #fuente de las hadas#"},
    });

    /*--------------------------
    |      JUNK HINT TEXT      |
    ---------------------------*/

    hintTable[JUNK01] = HintText::Junk({
                     //obscure text
                     Text{"Ganondorf 2022!", /*french*/"", /*spanish*/"¡Ganondorf para el 2022!"},
    });

    hintTable[JUNK02] = HintText::Junk({
                     //obscure text
                     Text{"They say that monarchy is a terrible system of governance.", /*french*/"", /*spanish*/"Según dicen, la monarquía es un pésimo modelo político."},
    });

    hintTable[JUNK03] = HintText::Junk({
                     //obscure text
                     Text{"They say that Zelda is a poor leader.", /*french*/"", /*spanish*/"Según dicen, Zelda es mala líder."},
    });

    hintTable[JUNK04] = HintText::Junk({
                     //obscure text
                     Text{"These hints can be quite useful. This is an exception.", /*french*/"", /*spanish*/"Las pistas suelen servir de ayuda. En cambio, esta no."},
    });

    hintTable[JUNK06] = HintText::Junk({
                     //obscure text
                     Text{"They say that all the Zora drowned in Wind Waker.", /*french*/"", /*spanish*/"Según dicen, en Wind Waker todos los zora se ahogaron."},
    });

    hintTable[JUNK08] = HintText::Junk({
                     //obscure text
                     Text{"'Member when Ganon was a blue pig?^I 'member.", /*french*/"", /*spanish*/"¿T'acuerdas cuando Ganon era un cerdo azul?^Yo sí m'acuerdo."},
    });

    hintTable[JUNK09] = HintText::Junk({
                     //obscure text
                     Text{"One who does not have Triforce can't go in.", /*french*/"", /*spanish*/"El que no porte la Trifuerza no podrá pasar."},
    });

    hintTable[JUNK10] = HintText::Junk({
                     //obscure text
                     Text{"Save your future, end the Happy Mask Salesman.", /*french*/"", /*spanish*/"Salva tu futuro, acaba con el dueño de La Máscara Feliz."},
    });

    hintTable[JUNK12] = HintText::Junk({
                     //obscure text
                     Text{"I'm stoned. Get it?", /*french*/"", /*spanish*/"Me he quedado de piedra. ¿Lo pillas?"},
    });

    hintTable[JUNK13] = HintText::Junk({
                     //obscure text
                     Text{"Hoot! Hoot! Would you like me to repeat that?", /*french*/"", /*spanish*/"¡Buuu, buuu! ¿Te lo vuelvo a repetir?"},
    });

    hintTable[JUNK14] = HintText::Junk({
                     //obscure text
                     Text{"Gorons are stupid. They eat rocks.", /*french*/"", /*spanish*/"Los goron son tontos. Se comen las piedras."},
    });

    hintTable[JUNK15] = HintText::Junk({
                     //obscure text
                     Text{"They say that Lon Lon Ranch prospered under Ingo.", /*french*/"", /*spanish*/"Dicen que el Rancho Lon Lon prosperó gracias a Ingo."},
    });

    hintTable[JUNK16] = HintText::Junk({
                     //obscure text
                     Text{"The single rupee is a unique item.", /*french*/"", /*spanish*/"La rupia de uno es un objeto singular."},
    });

    hintTable[JUNK17] = HintText::Junk({
                     //obscure text
                     Text{"Without the Lens of Truth, the Treasure Chest Mini-Game is a 1 out of 32 chance.^Good luck!", /*french*/"", /*spanish*/"Sin la Lupa de la Verdad, ganarías 1 de cada 32 veces en el Cofre del Tesoro.^¡Buena suerte con ello!"},
    });

    hintTable[JUNK18] = HintText::Junk({
                     //obscure text
                     Text{"Use bombs wisely.", /*french*/"", /*spanish*/"No desperdicies las bombas."},
    });

    hintTable[JUNK21] = HintText::Junk({
                     //obscure text
                     Text{"I found you, faker!", /*french*/"", /*spanish*/"¡Ahí estás, impostor!"},
    });

    hintTable[JUNK22] = HintText::Junk({
                     //obscure text
                     Text{"You're comparing yourself to me?^Ha! You're not even good enough to be my fake.", /*french*/"", /*spanish*/"¿Me estás comparando contigo?^¡Ja! No me llegas ni a la suela para ser un impostor mío."},
    });

    hintTable[JUNK23] = HintText::Junk({
                     //obscure text
                     Text{"I'll make you eat those words.", /*french*/"", /*spanish*/"Te tragarás tus propias palabras."},
    });

    hintTable[JUNK24] = HintText::Junk({
                     //obscure text
                     Text{"What happened to Sheik?", /*french*/"", /*spanish*/"¿Qué la habrá pasado a Sheik?"},
    });

    hintTable[JUNK25] = HintText::Junk({
                     //obscure text
                     Text{"L2P @.", /*french*/"", /*spanish*/"Mira que eres novato, @."},
    });

    hintTable[JUNK26] = HintText::Junk({
                     //obscure text
                     Text{"I've heard Sploosh Kaboom is a tricky game.", /*french*/"", /*spanish*/"He oído que el Splas Kapum es un minijuego difícil."},
    });

    hintTable[JUNK27] = HintText::Junk({
                     //obscure text
                     Text{"I'm Lonk from Pennsylvania.", /*french*/"", /*spanish*/"Soy Lonk, de Pensilvania."},
    });

    hintTable[JUNK28] = HintText::Junk({
                     //obscure text
                     Text{"I bet you'd like to have more bombs.", /*french*/"", /*spanish*/"Me apuesto a que quisieras tener más bombas."},
    });

    hintTable[JUNK29] = HintText::Junk({
                     //obscure text
                     Text{"When all else fails, use Fire.", /*french*/"", /*spanish*/"Cuando nada funcione, usa fuego."},
    });

    hintTable[JUNK30] = HintText::Junk({
                     //obscure text
                     Text{"Here's a hint, @. Don't be bad.", /*french*/"", /*spanish*/"Aquí tienes una pista, @. Deja de ser manco."},
    });

    hintTable[JUNK31] = HintText::Junk({
                     //obscure text
                     Text{"Game Over. Return of Ganon.", /*french*/"", /*spanish*/"Fin de la partida. El regreso de Ganon."},
    });

    hintTable[JUNK32] = HintText::Junk({
                     //obscure text
                     Text{"May the way of the Hero lead to the Triforce.", /*french*/"", /*spanish*/"Puede que la senda del héroe te lleve hacia la Trifuerza."},
    });

    hintTable[JUNK33] = HintText::Junk({
                     //obscure text
                     Text{"Can't find an item? Scan an Amiibo.", /*french*/"", /*spanish*/"¿No encuentras algo? Escanea un amiibo."},
    });

    hintTable[JUNK34] = HintText::Junk({
                     //obscure text
                     Text{"They say this game has just a few glitches.", /*french*/"", /*spanish*/"Dicen que este juego solo tiene unos pocos glitches."},
    });

    hintTable[JUNK35] = HintText::Junk({
                     //obscure text
                     Text{"BRRING BRRING This is Ulrira. Wrong number?", /*french*/"", /*spanish*/"¡Ring! ¡Ring! Al habla Ulrira. ¿Me he equivocado de número?"},
    });

    hintTable[JUNK36] = HintText::Junk({
                     //obscure text
                     Text{"Tingle Tingle Kooloo Limpah", /*french*/"", /*spanish*/"Tingle, Tingle, Kululim... ¡Pah!"},
    });

    hintTable[JUNK37] = HintText::Junk({
                     //obscure text
                     Text{"L is real 2041", /*french*/"", /*spanish*/"L es real 2041."},
    });

    hintTable[JUNK38] = HintText::Junk({
                     //obscure text
                     Text{"They say that Ganondorf will appear in the next Mario Tennis.", /*french*/"", /*spanish*/"Según dicen, Ganondorf estará en el próximo Mario Tennis."},
    });

    hintTable[JUNK39] = HintText::Junk({
                     //obscure text
                     Text{"Medigoron sells the earliest Breath of the Wild demo.", /*french*/"", /*spanish*/"Medigoron vende la primera demo del Breath of the Wild."},
    });

    hintTable[JUNK40] = HintText::Junk({
                     //obscure text
                     Text{"There's a reason why I am special inquisitor!", /*french*/"", /*spanish*/"¡Por algo soy una inquisidora especial!"},
    });

    hintTable[JUNK41] = HintText::Junk({
                     //obscure text
                     Text{"You were almost a @ sandwich.", /*french*/"", /*spanish*/"Por poco te conviertes en emparedado de @."},
    });

    hintTable[JUNK42] = HintText::Junk({
                     //obscure text
                     Text{"I'm a helpful hint Gossip Stone!^See, I'm helping.", /*french*/"", /*spanish*/"Soy una Piedra Sheikah muy útil.^¡Mira cómo te ayudo!"},
    });

    hintTable[JUNK43] = HintText::Junk({
                     //obscure text
                     Text{"Dear @, please come to the castle. I've baked a cake for you.&Yours truly, princess Zelda.", /*french*/"", /*spanish*/"Querido @: Por favor, ven al castillo. He hecho una tarta para ti.&Sinceramente tuya: Princesa Zelda."},
    });

    hintTable[JUNK44] = HintText::Junk({
                     //obscure text
                     Text{"They say all toasters toast toast.", /*french*/"", /*spanish*/"Según dicen, todas las tostadoras tostan tostadas."},
    });

    hintTable[JUNK45] = HintText::Junk({
                     //obscure text
                     Text{"They say that Okami is the best Zelda game.", /*french*/"", /*spanish*/"Según dicen, Okami es el mejor juego de Zelda."},
    });

    hintTable[JUNK46] = HintText::Junk({
                     //obscure text
                     Text{"They say that quest guidance can be found at a talking rock.", /*french*/"", /*spanish*/"Según dicen, puedes consultarle ayuda a rocas parlanchinas."},
    });

    hintTable[JUNK47] = HintText::Junk({
                     //obscure text
                     Text{"They say that the final item you're looking for can be found somewhere in Hyrule.", /*french*/"", /*spanish*/"Según dicen, el último objeto que te falte puede estar en cualquier parte de Hyrule."},
    });

    hintTable[JUNK48] = HintText::Junk({
                     //obscure text
                     Text{"Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.^Mweep.", /*french*/"", /*spanish*/"Muip.^Muip.^Muip.^Muip.^Muip.^Muip.^Muip.^Muip.^Muip.^Muip.^Muip.^Muip."},
    });

    hintTable[JUNK49] = HintText::Junk({
                     //obscure text
                     Text{"They say that Barinade fears Deku Nuts.", /*french*/"", /*spanish*/"Según dicen, lo que más teme a Barinade son las nueces deku."},
    });

    hintTable[JUNK50] = HintText::Junk({
                     //obscure text
                     Text{"They say that Flare Dancers do not fear Goron-crafted blades.", /*french*/"", /*spanish*/"Según dicen, los Bailafuegos no le temen a las armas forjadas por gorons."},
    });

    hintTable[JUNK51] = HintText::Junk({
                     //obscure text
                     Text{"They say that Morpha is easily trapped in a corner.", /*french*/"", /*spanish*/"Según dicen, puedes atrapar a Morpha con facilidad en una esquina."},
    });

    hintTable[JUNK52] = HintText::Junk({
                     //obscure text
                     Text{"They say that Bongo Bongo really hates the cold.", /*french*/"", /*spanish*/"Según dicen, Bongo Bongo odia a muerte el frío."},
    });

    hintTable[JUNK53] = HintText::Junk({
                     //obscure text
                     Text{"They say that your sword is most powerful when you put it away.", /*french*/"", /*spanish*/"Según dicen, tu espada se vuelve más poderosa si la guardas."},
    });

    hintTable[JUNK54] = HintText::Junk({
                     //obscure text
                     Text{"They say that bombing the hole Volvagia last flew into can be rewarding.", /*french*/"", /*spanish*/"Según dicen, trae buena suerte colocar una bomba en el último agujero de donde salió Volvagia."},
    });

    hintTable[JUNK55] = HintText::Junk({
                     //obscure text
                     Text{"They say that invisible ghosts can be exposed with Deku Nuts.", /*french*/"", /*spanish*/"Según dicen, puedes exponer a los espectros invisibles con nueces deku."},
    });

    hintTable[JUNK56] = HintText::Junk({
                     //obscure text
                     Text{"They say that the real Phantom Ganon is bright and loud.", /*french*/"", /*spanish*/"Según dicen, el verdadero Ganon Fantasma es brillante y ruidoso."},
    });

    hintTable[JUNK57] = HintText::Junk({
                     //obscure text
                     Text{"They say that walking backwards is very fast.", /*french*/"", /*spanish*/"Según dicen, es más rápido caminar hacia atrás."},
    });

    hintTable[JUNK58] = HintText::Junk({
                     //obscure text
                     Text{"They say that leaping above the Market entrance enriches most children.", /*french*/"", /*spanish*/"Según dicen, saltar por las cadenas a la entrada de la plaza enriquece a muchos chiquillos."},
    });

    hintTable[JUNK59] = HintText::Junk({
                     //obscure text
                     Text{"They say that looking into darkness may find darkness looking back into you.", /*french*/"", /*spanish*/"Según dicen, contemplar la oscuridad puede hacer que ella te contemple a ti."},
    });

    hintTable[JUNK60] = HintText::Junk({
                     //obscure text
                     Text{"You found a spiritual Stone! By which I mean, I worship Nayru.", /*french*/"", /*spanish*/"¡Has encontrado una piedra espiritual! Es que le rindo culto a Nayru..."},
    });

    hintTable[JUNK61] = HintText::Junk({
                     //obscure text
                     Text{"They say that the stick is mightier than the sword...^At least, it used to be...", /*french*/"", /*spanish*/"Según dicen, los palos son más poderosos que las espadas...^O así solía ser..."},
    });

    hintTable[JUNK62] = HintText::Junk({
                     //obscure text
                     Text{"Open your eyes.^Open your eyes.^Wake up, @.", /*french*/"", /*spanish*/"Abre los ojos...^Abre los ojos...^Despierta, @..."},
    });

    hintTable[JUNK63] = HintText::Junk({
                     //obscure text
                     Text{"They say that the Nocturne of Shadow can bring you very close to Ganon.", /*french*/"", /*spanish*/"Según dicen, el Nocturno de la sombra te puede acercar mucho a Ganon."},
    });

    hintTable[JUNK64] = HintText::Junk({
                     //obscure text
                     Text{"They say that Twinrova always casts the same spell the first three times.", /*french*/"", /*spanish*/"Según dicen, Birova siempre lanza el mismo hechizo tres veces."},
    });

    hintTable[JUNK65] = HintText::Junk({
                     //obscure text
                     Text{"They say that the nightly builds may be unstable.", /*french*/"", /*spanish*/"Según dicen, las última nightly puede ser algo inestable."},
    });

    hintTable[JUNK66] = HintText::Junk({
                     //obscure text
                     Text{"You're playing a Randomizer. I'm randomized!^Here's a random number:  #4#.&Enjoy your Randomizer!", /*french*/"", /*spanish*/"¡Estás jugando un Randomizer! ¡Yo también estoy aleatorizada!^Aquí tienes un número aleatorio:  #4#.&¡Disfruta el Randomizer!"},
    });

    hintTable[JUNK67] = HintText::Junk({
                     //obscure text
                     Text{"They say Ganondorf's bolts can be reflected with glass or steel.", /*french*/"", /*spanish*/"Según dicen, puedes reflejar las esferas de energía de Ganondorf con cristal y acero."},
    });

    hintTable[JUNK68] = HintText::Junk({
                     //obscure text
                     Text{"They say Ganon's tail is vulnerable to nuts, arrows, swords, explosives, hammers...^...sticks, seeds, boomerangs...^...rods, shovels, iron balls, angry bees...", /*french*/"", /*spanish*/"Según dicen, la cola de Ganon es vulnerable a nueces, flechas, espadas, explosivos, martillos...^...palos, semillas, bumeráns...^...cetros, palas, bolas de hierro, abejas..."},
    });

    hintTable[JUNK69] = HintText::Junk({
                     //obscure text
                     Text{"They say that you're wasting time reading this hint, but I disagree. Talk to me again!", /*french*/"", /*spanish*/"Según dicen, pierdes el tiempo en leer esta pista, pero no pienso igual. ¡Vuelve a hablarme, ya verás!"},
    });

    hintTable[JUNK70] = HintText::Junk({
                     //obscure text
                     Text{"They say Ganondorf knows where to find the instrument of his doom.", /*french*/"", /*spanish*/"Según dicen, Ganondorf sabe dónde hallar el instrumento de su perdición."},
    });

    hintTable[JUNK71] = HintText::Junk({
                     //obscure text
                     Text{"I heard @ is pretty good at Zelda.", /*french*/"", /*spanish*/"He oído que a @ se le dan muy bien los Zelda."},
    });

    /*--------------------------
    |     DUNGEON HINT TEXT    |
    ---------------------------*/

    hintTable[DEKU_TREE] = HintText::DungeonName({
                     //obscure text
                     Text{"an ancient tree", /*french*/"", /*spanish*/"un ancestral árbol"},
                   },
                     //clear text
                     Text{"Deku Tree", /*french*/"", /*spanish*/"el Árbol Deku"}
    );

    hintTable[DODONGOS_CAVERN] = HintText::DungeonName({
                     //obscure text
                     Text{"an immense cavern", /*french*/"", /*spanish*/"una descomunal cueva"},
                   },
                     //clear text
                     Text{ "Dodongo's Cavern", /*french*/"", /*spanish*/"la Cueva de los Dodongos"}
    );

    hintTable[JABU_JABUS_BELLY] = HintText::DungeonName({
                     //obscure text
                     Text{"the belly of a deity", /*french*/"", /*spanish*/"la tripa de cierta deidad"},
                   },
                     //clear text
                     Text{ "Jabu Jabu's Belly", /*french*/"", /*spanish*/"la tripa de Jabu Jabu"}
    );

    hintTable[FOREST_TEMPLE] = HintText::DungeonName({
                     //obscure text
                     Text{"a deep forest", /*french*/"", /*spanish*/"un profundo bosque"},
                   },
                     //clear text
                     Text{ "Forest Temple", /*french*/"", /*spanish*/"el Templo del Bosque"}
    );

    hintTable[FIRE_TEMPLE] = HintText::DungeonName({
                     //obscure text
                     Text{"a high mountain", /*french*/"", /*spanish*/"una alta montaña"},
                   },
                     //clear text
                     Text{ "Fire Temple", /*french*/"", /*spanish*/"el Templo del Fuego"}
    );

    hintTable[WATER_TEMPLE] = HintText::DungeonName({
                     //obscure text
                     Text{"a vast lake", /*french*/"", /*spanish*/"un lago inmenso"},
                   },
                     //clear text
                     Text{ "Water Temple", /*french*/"", /*spanish*/"el Templo del Agua"}
    );

    hintTable[SPIRIT_TEMPLE] = HintText::DungeonName({
                     //obscure text
                     Text{"the goddess of the sand", /*french*/"", /*spanish*/"la diosa de la arena"},
                   },
                     //clear text
                     Text{ "Spirit Temple", /*french*/"", /*spanish*/"el Templo del Espíritu"}
    );

    hintTable[SHADOW_TEMPLE] = HintText::DungeonName({
                     //obscure text
                     Text{"the house of the dead", /*french*/"", /*spanish*/"la casa de la muerte"},
                   },
                     //clear text
                     Text{ "Shadow Temple", /*french*/"", /*spanish*/"el Templo de las Sombras"}
    );

    hintTable[ICE_CAVERN] = HintText::DungeonName({
                     //obscure text
                     Text{"a frozen maze", /*french*/"", /*spanish*/"un gélido laberinto"},
                   },
                     //clear text
                     Text{ "Ice Cavern", /*french*/"", /*spanish*/"la caverna de hielo"}
    );

    hintTable[BOTTOM_OF_THE_WELL] = HintText::DungeonName({
                     //obscure text
                     Text{"a shadow\'s prison", /*french*/"", /*spanish*/"la prisión de las sombras"},
                   },
                     //clear text
                     Text{ "Bottom of the Well", /*french*/"", /*spanish*/"el fondo del pozo"}
    );

    hintTable[GERUDO_TRAINING_GROUNDS] = HintText::DungeonName({
                     //obscure text
                     Text{"the test of thieves", /*french*/"", /*spanish*/"la prueba de las ladronas"},
                   },
                     //clear text
                     Text{ "Gerudo Training Grounds", /*french*/"", /*spanish*/"el Centro de Instrucción Gerudo"}
    );

    hintTable[GANONS_CASTLE] = HintText::DungeonName({
                     //obscure text
                     Text{"a conquered citadel", /*french*/"", /*spanish*/"una conquistada ciudadela"},
                   },
                     //clear text
                     Text{ "Inside Ganon's Castle", /*french*/"", /*spanish*/"el interior del Castillo de Ganondorf"}
    );

    /*--------------------------
    |      BOSS HINT TEXT      |
    ---------------------------*/

    hintTable[QUEEN_GOHMA] = HintText::Boss({
                     //obscure text
                     Text{"An #ancient tree# rewards", /*french*/"", /*spanish*/"un #ancestral árbol# premia con"},
                   },
                     //clear text
                     Text{"the #Deku Tree# rewards", /*french*/"", /*spanish*/"el #Árbol Deku# premia con"}
    );

    hintTable[KING_DODONGO] = HintText::Boss({
                     //obscure text
                     Text{"An #immense cavern# rewards", /*french*/"", /*spanish*/"una #descomunal cueva# premia con"},
                   },
                     //clear text
                     Text{"#Dodongo's Cavern# rewards", /*french*/"", /*spanish*/"la #Cueva de los Dodongos# premia con"}
    );

    hintTable[BARINADE] = HintText::Boss({
                     //obscure text
                     Text{"the #belly of a deity# rewards", /*french*/"", /*spanish*/"la #tripa de cierta deidad# premia con"},
                   },
                     //clear text
                     Text{"#Jabu Jabu's Belly# rewards", /*french*/"", /*spanish*/"la #Tripa de Jabu Jabu# premia con"}
    );

    hintTable[PHANTOM_GANON] = HintText::Boss({
                     //obscure text
                     Text{"a #deep forest# rewards", /*french*/"", /*spanish*/"un #profundo bosque# premia con"},
                   },
                     //clear text
                     Text{"the #Forest Temple# rewards", /*french*/"", /*spanish*/"el #Templo del Bosque# premia con"}
    );

    hintTable[VOLVAGIA] = HintText::Boss({
                     //obscure text
                     Text{"a #high mountain# rewards", /*french*/"", /*spanish*/"una #alta montaña# premia con"},
                   },
                     //clear text
                     Text{"the #Fire Temple# rewards", /*french*/"", /*spanish*/"el #Templo del Fuego# premia con"}
    );

    hintTable[MORPHA] = HintText::Boss({
                     //obscure text
                     Text{"a #vast lake# rewards", /*french*/"", /*spanish*/"un #lago inmenso# premia con"},
                   },
                     //clear text
                     Text{"the #Water Temple# rewards", /*french*/"", /*spanish*/"el #Templo del Agua# premia con"}
    );

    hintTable[BONGO_BONGO] = HintText::Boss({
                     //obscure text
                     Text{"the #house of the dead# rewards", /*french*/"", /*spanish*/"la #casa de la muerte# premia con"},
                   },
                     //clear text
                     Text{"the #Shadow Temple# rewards", /*french*/"", /*spanish*/"el #Templo de las Sombras"}
    );

    hintTable[TWINROVA] = HintText::Boss({
                     //obscure text
                     Text{"a #goddess of the sand# rewards", /*french*/"", /*spanish*/"la #diosa de la arena# premia con"},
                   },
                     //clear text
                     Text{ "the #Spirit Temple# rewards", /*french*/"", /*spanish*/"el #Templo del Espíritu# premia con"}
    );
    //
    // {LINKS_POCKET_BOSS] = HintText::Boss({
    //                    //obscure text
    //                    Text{"#@'s pocket# rewards", /*french*/"", /*spanish*/"el #bolsillo de @# premia con"},
    //                  },
    //                    //clear text
    //                    Text{"#@ already has#", /*french*/"", /*spanish*/"el #bolsillo de @ ya tiene#"}
    // );

    /*--------------------------
    |     BRIDGE HINT TEXT     |
    ---------------------------*/

    hintTable[BRIDGE_VANILLA_HINT] = HintText::Bridge({
                     //obscure text
                     Text{"the #Shadow and Spirit Medallions# as well as the #Light Arrows#", /*french*/"", /*spanish*/"tanto el #Medallón de las Sombras y el del Espíritu# junto a las #Flechas de Luz#"},
    });

    hintTable[BRIDGE_STONES_HINT] = HintText::Bridge({
                     //obscure text
                     Text{"Spiritual Stones", /*french*/"", /*spanish*/"las piedras espirituales"},
    });

    hintTable[BRIDGE_MEDALLIONS_HINT] = HintText::Bridge({
                     //obscure text
                     Text{"Medallions", /*french*/"", /*spanish*/"los medallones"},
    });

    hintTable[BRIDGE_REWARDS_HINT] = HintText::Bridge({
                     //obscure text
                     Text{"Spiritual Stones and Medallions", /*french*/"", /*spanish*/"las piedras espirituales y los medallones"},
    });

    hintTable[BRIDGE_DUNGEONS_HINT] = HintText::Bridge({
                     //obscure text
                     Text{"Completed Dungeons", /*french*/"", /*spanish*/"al completar las mazmorras"},
    });

    hintTable[BRIDGE_TOKENS_HINT] = HintText::Bridge({
                     //obscure text
                     Text{"Gold Skulltula Tokens", /*french*/"", /*spanish*/"al obtener los símbolos de skulltulas doradas"},
    });

    /*--------------------------
    | GANON BOSS KEY HINT TEXT |
    ---------------------------*/

    hintTable[GANON_BK_VANILLA_HINT] = HintText::GanonsBossKey({
                     //obscure text
                     Text{"kept in a big chest #inside its tower#", /*french*/"", /*spanish*/"en un gran cofre #de su torre#"},
    });

    hintTable[GANON_BK_OWN_DUNGEON_HINT] = HintText::GanonsBossKey({
                     //obscure text
                     Text{"hidden somewhere #inside its castle#", /*french*/"", /*spanish*/"escondida en #algún lugar de su castillo#"},
    });

    hintTable[GANON_BK_OVERWORLD_HINT] = HintText::GanonsBossKey({
                     //obscure text
                     Text{"hidden #outside of dungeons# in Hyrule", /*french*/"", /*spanish*/"escondida #fuera de las mazmorras# de Hyrule"},
    });

    hintTable[GANON_BK_ANY_DUNGEON_HINT] = HintText::GanonsBossKey({
                     //obscure text
                     Text{"hidden #inside a dungeon# in Hyrule", /*french*/"", /*spanish*/"escondida #en una mazmorra# de Hyrule"},
    });

    hintTable[GANON_BK_KEYSANITY_HINT] = HintText::GanonsBossKey({
                     //obscure text
                     Text{"hidden somewhere #in Hyrule#", /*french*/"", /*spanish*/"escondida en #cualquier lugar de Hyrule#"},
    });

    hintTable[GANON_BK_TRIFORCE_HINT] = HintText::GanonsBossKey({
                     //obscure text
                     Text{"given to the Hero once the #Triforce# is completed", /*french*/"", /*spanish*/"recibida por el héroe cuando haya completado la #Trifuerza#"},
    });

    /*--------------------------
    |      LACS HINT TEXT      |
    ---------------------------*/

    hintTable[LACS_VANILLA_HINT] = HintText::LACS({
                     //obscure text
                     Text{"the #Shadow and Spirit Medallions#", /*french*/"", /*spanish*/"el #Medallón de las Sombras y el Espíritu#"},
    });

    hintTable[LACS_MEDALLIONS_HINT] = HintText::LACS({
                     //obscure text
                     Text{"Medallions", /*french*/"", /*spanish*/"los #medallones#"},
    });

    hintTable[LACS_STONES_HINT] = HintText::LACS({
                     //obscure text
                     Text{"Spiritual Stones", /*french*/"", /*spanish*/"las #piedras espirituales#"},
    });

    hintTable[LACS_REWARDS_HINT] = HintText::LACS({
                     //obscure text
                     Text{"Spiritual Stones and Medallions", /*french*/"", /*spanish*/"las #piedras espirituales y los medallones#"},
    });

    hintTable[LACS_TOKENS_HINT] = HintText::LACS({
                     //obscure text
                     Text{"Gold Skulltula Tokens", /*french*/"", /*spanish*/"los #símbolos de skulltulas doradas#"},
    });

    /*--------------------------
    |     TRIAL HINT TEXT      |
    ---------------------------*/

    hintTable[SIX_TRIALS] = HintText::Exclude({
                     //obscure text
                     Text{"#Ganon's Tower# is protected by a powerful barrier.", /*french*/"", /*spanish*/""},
    });

    hintTable[ZERO_TRIALS] = HintText::Exclude({
                     //obscure text
                     Text{"Sheik dispelled the barrier around #Ganon's Tower#.", /*french*/"", /*spanish*/""},
    });

    hintTable[FOUR_TO_FIVE_TRIALS] = HintText::Exclude({
                     //obscure text
                     Text{" was dispelled by Sheik.", /*french*/"", /*spanish*/""},
    });

    hintTable[ONE_TO_THREE_TRIALS] = HintText::Exclude({
                     //obscure text
                     Text{" protects Ganons Tower.", /*french*/"", /*spanish*/""},
    });

    /*--------------------------
    |        ALTAR TEXT        |
    ---------------------------*/

    hintTable[SPIRITUAL_STONE_TEXT_START] = HintText::Altar({
                     //obscure text
                     Text{"3 Spiritual Stones found in Hyrule...", /*french*/"", /*spanish*/"Tres piedras espirituales encontradas en Hyrule..."},
    });

    hintTable[CHILD_ALTAR_TEXT_END] = HintText::Altar({
                     //obscure text
                     Text{"Ye who may become a Hero...&Stand with the Ocarina and play the Song of Time.", /*french*/"", /*spanish*/"Aquel que se convierta en el héroe... Tomad la ocarina y entonad la Canción del Tiempo."},
    });

    hintTable[ADULT_ALTAR_TEXT_START] = HintText::Altar({
                     //obscure text
                     Text{"When evil rules all, an awakening voice from the Sacred Realm will call those destined to be Sages, who dwell in the #five temples#.", /*french*/"", /*spanish*/"Cuando el mal lo impregne todo, desde el Reino Sagrado surgirá unz voz que hará despertar a los sabios que moran en los #cinco templos#."},
    });

    hintTable[ADULT_ALTAR_TEXT_END] = HintText::Altar({
                     //obscure text
                     Text{"Together with the Hero of Time, the awakened ones will bind the evil and return the light of peace to the world...", /*french*/"", /*spanish*/"Con el héroe del Tiempo, aquellos que despierten detendrán el mal y volverán al mundo de luz la paz..."},
    });

    /*--------------------------
    |   VALIDATION LINE TEXT   |
    ---------------------------*/

    hintTable[VALIDATION_LINE] = HintText::Validation({
                     //obscure text
                     Text{"Hmph... Since you made it this far, I'll let you know what glorious prize of Ganon's you likely missed out on in my tower.^Behold...^", /*french*/"", /*spanish*/"Mmm... Ya que has llegado hasta aquí, te diré qué preciado objeto de Ganon puedes haberte dejado en mi torre.^He aquí..."},
    });

    /*--------------------------
    | LIGHT ARROW LOCATION TEXT|
    ---------------------------*/

    hintTable[LIGHT_ARROW_LOCATION_HINT] = HintText::LightArrow({
                     //obscure text
                     Text{"Ha ha ha... You'll never beat me by reflecting my lightning bolts and unleashing the arrows from ", /*french*/"", /*spanish*/"Ja, ja, ja... Nunca me derrotarás reflejando mis esferas de energía y desplegando las flechas de luz de "},
    });

    hintTable[YOUR_POCKET] = HintText::Exclude({
                     //obscure text
                     Text{"your pocket", /*french*/"", /*spanish*/""},
    });

    /*--------------------------
    |      GANON LINE TEXT     |
    ---------------------------*/

    hintTable[GANON_LINE01] = HintText::GanonLine({
                     //obscure text
                     Text{"Oh! It's @.&I was expecting someone called Sheik. Do you know what happened to them?", /*french*/"", /*spanish*/"¡Oh! Pero si es @.&Estaba esperando a alguien llamado Sheik. ¿Sabes qué puede haberle pasado?"},
    });

    hintTable[GANON_LINE02] = HintText::GanonLine({
                     //obscure text
                     Text{"I knew I shouldn't have put the key on the other side of my door.", /*french*/"", /*spanish*/"Sabía que no tendría que haber dejado la llave al otro lado de la puerta."},
    });

    hintTable[GANON_LINE03] = HintText::GanonLine({
                     //obscure text
                     Text{"Looks like it's time for a round of tennis.", /*french*/"", /*spanish*/"Parece que es hora de una partidita de tenis."},
    });

    hintTable[GANON_LINE04] = HintText::GanonLine({
                     //obscure text
                     Text{"You'll never deflect my bolts of energy with your sword, then shoot me with those Light Arrows you happen to have.", /*french*/"", /*spanish*/"Nunca reflejarás mis esferas de energía con tu espada, para después dispararme con las flechas de luz que tendrás."},
    });

    hintTable[GANON_LINE05] = HintText::GanonLine({
                     //obscure text
                     Text{"Why did I leave my trident back in the desert?", /*french*/"", /*spanish*/"¿Por qué me habré dejado el tridente en el desierto?"},
    });

    hintTable[GANON_LINE06] = HintText::GanonLine({
                     //obscure text
                     Text{"Zelda is probably going to do something stupid, like send you back to your own timeline.^So this is quite meaningless. Do you really want to save this moron?", /*french*/"", /*spanish*/"Seguro que Zelda trata de hacer alguna tontería, como enviarte de vuelta a tu línea temporal.^No tiene ningún sentido alguno. ¿De verdad quieres salvar a esa tonta?"},
    });

    hintTable[GANON_LINE07] = HintText::GanonLine({
                     //obscure text
                     Text{"What about Zelda makes you think she'd be a better ruler than I?^I saved Lon Lon Ranch,&fed the hungry,&and my castle floats.", /*french*/"", /*spanish*/"¿Qué te hace pensar que Zelda gobierna mejor que yo?^Yo he salvado el Rancho Lon Lon,&he alimentado a los hambrientos&y hasta hago que mi castillo flote."},
    });

    hintTable[GANON_LINE08] = HintText::GanonLine({
                     //obscure text
                     Text{"I've learned this spell,&it's really neat,&I'll keep it later&for your treat!", /*french*/"", /*spanish*/"Acabo de aprender este hechizo,&y la verdad es que es&de lo más bueno. ¡Te lo&reservaré como sorpresa!"},
    });

    hintTable[GANON_LINE09] = HintText::GanonLine({
                     //obscure text
                     Text{"Many tricks are up my sleeve,&to save yourself&you'd better leave!", /*french*/"", /*spanish*/"Tengo muchos trucos a mi espalda&, si no quieres morir,&¡deshazte de esa hada!"},
    });

    hintTable[GANON_LINE10] = HintText::GanonLine({
                     //obscure text
                     Text{"After what you did to Koholint Island, how can you call me the bad guy?", /*french*/"", /*spanish*/"Después de lo que le hiciste a la Isla Koholint, ¿cómo te atreves a llamarme malvado?"},
    });

    hintTable[GANON_LINE11] = HintText::GanonLine({
                     //obscure text
                     Text{"Today, let's begin down&'The Hero is Defeated' timeline.", /*french*/"", /*spanish*/"Hoy daremos lugar a la&línea temporal del Héroe Derrotado."},
    });
}

const HintText& Hint(u32 hintKey) {
    return hintTable[hintKey];
}

std::vector<HintText> GetHintCategory(HintCategory category) {

    std::vector<HintText> hintsInCategory = {};

    for (const auto& hint : hintTable) {
        if (hint.GetType() == category) {
            hintsInCategory.push_back(hint);
        }
    }
    return hintsInCategory;
}
