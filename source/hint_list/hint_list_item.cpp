#include "hint_list.hpp"

void HintTable_Init_Item() {
    hintTable[KOKIRI_SWORD] = HintText::Item({
                       //obscure text
                       Text{"a butter knife",    /*french*/"un couteau à beurre",  /*spanish*/"un ágil puñal",             /*italian*/"un coltello da burro",   /*german*/"Deutsch"},
                       Text{"a starter slasher", /*french*/"une arme de débutant", /*spanish*/"una hoja de principiantes", /*italian*/"un pugnale iniziale",    /*german*/"Deutsch"},
                       Text{"a switchblade",     /*french*/"un canif",             /*spanish*/"una navaja",                /*italian*/"un coltellino svizzero", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a sword", /*french*/"une épée", /*spanish*/"una espada", /*italian*/"una spada", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Kokiri Sword", /*french*/"l'épée Kokiri", /*spanish*/"la Espada Kokiri", /*italian*/"la spada dei Kokiri", /*german*/"Deutsch"}
    );

    hintTable[MASTER_SWORD] = HintText::Item({
                       //obscure text
                       Text{"evil's bane",        /*french*/"le fléau du mal",       /*spanish*/"la destructora del mal",    /*italian*/"il potere dell'esorcismo", /*german*/"Deutsch"},
                       Text{"a seven year limbo", /*french*/"une stase de sept ans", /*spanish*/"unos siete años de espera", /*italian*/"un sonno di sette anni",   /*german*/"Deutsch"},
                       Text{"Fi",                 /*french*/"Fay",                   /*spanish*/"Fay",                       /*italian*/"Faih",                     /*german*/"Phai"},
                     }, {
                       //ambiguous text
                       Text{"a sword", /*french*/"une épée", /*spanish*/"una espada", /*italian*/"una spada", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Master Sword", /*french*/"l'épée de légende", /*spanish*/"la Espada Maestra", /*italian*/"la spada suprema", /*german*/"Deutsch"}
    );

    hintTable[GIANTS_KNIFE] = HintText::Item({
                       //obscure text
                       Text{"a fragile blade",     /*french*/"une lame fragile",    /*spanish*/"una frágil hoja",   /*italian*/"una lama fragile",  /*german*/"Deutsch"},
                       Text{"a breakable cleaver", /*french*/"un espadon de verre", /*spanish*/"un rompible acero", /*italian*/"un'arma deludente", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a sword", /*french*/"une épée", /*spanish*/"una espada", /*italian*/"una spada", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Giant's Knife", /*french*/"la lame des géants", /*spanish*/"la daga gigante", /*italian*/"la spada del gigante", /*german*/"Deutsch"}
    );

    hintTable[BIGGORON_SWORD] = HintText::Item({
                       //obscure text
                       Text{"the biggest blade",  /*french*/"une lame gigantesque", /*spanish*/"el mayor mandoble",  /*italian*/"la lama più forte", /*german*/"Deutsch"},
                       Text{"a colossal cleaver", /*french*/"un espadon colossal",  /*spanish*/"un estoque colosal", /*italian*/"un'arma robusta",   /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a sword", /*french*/"une épée", /*spanish*/"una espada", /*italian*/"una spada", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Biggoron Sword", /*french*/"l'épée de Grogoron", /*spanish*/"la Espada de Biggoron", /*italian*/"la spada di Grande Goron", /*german*/"Deutsch"}
    );

    hintTable[DEKU_SHIELD] = HintText::Item({
                       //obscure text
                       Text{"a wooden ward",      /*french*/"un écu d'écorce",            /*spanish*/"una protección del bosque", /*italian*/"una difesa legnosa",        /*german*/"Deutsch"},
                       Text{"a burnable barrier", /*french*/"une protection inflammable", /*spanish*/"una barrera quemable",      /*italian*/"una barriera infiammabile", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a shield", /*french*/"un bouclier", /*spanish*/"un escudo", /*italian*/"uno scudo", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Deku Shield", /*french*/"un bouclier Mojo", /*spanish*/"un escudo deku", /*italian*/"uno scudo Deku", /*german*/"Deutsch"}
    );

    hintTable[HYLIAN_SHIELD] = HintText::Item({
                       //obscure text
                       Text{"a steel safeguard",      /*french*/"une carapace d'acier",       /*spanish*/"una protección de acero",  /*italian*/"una difesa metallica",    /*german*/"Deutsch"},
                       Text{"Like Like's metal meal", /*french*/"un amuse-gueule de Pudding", /*spanish*/"un alimento de Like Like", /*italian*/"cibo duro per Like-Like", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a shield", /*french*/"un bouclier", /*spanish*/"un escudo", /*italian*/"uno scudo", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Hylian Shield", /*french*/"un bouclier hylien", /*spanish*/"un escudo hyliano", /*italian*/"uno scudo Hylia", /*german*/"Deutsch"}
    );

    hintTable[MIRROR_SHIELD] = HintText::Item({
                       //obscure text
                       Text{"a reflective rampart", /*french*/"un capteur de lumière",  /*spanish*/"una muralla reflectora",  /*italian*/"una difesa riflettente",      /*german*/"Deutsch"},
                       Text{"Medusa's weakness",    /*french*/"la faiblesse de Méduse", /*spanish*/"la debilidad de Medusa",  /*italian*/"il punto debole di Medusa",   /*german*/"Deutsch"},
                       Text{"a silvered surface",   /*french*/"une surface argentée",   /*spanish*/"una superficie plateada", /*italian*/"una superficie scintillante", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a shield", /*french*/"un bouclier", /*spanish*/"un escudo", /*italian*/"uno scudo", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Mirror Shield", /*french*/"le bouclier miroir", /*spanish*/"el escudo espejo", /*italian*/"lo scudo specchio", /*german*/"Deutsch"}
    );

    hintTable[GORON_TUNIC] = HintText::Item({
                       //obscure text
                       Text{"ruby robes",       /*french*/"un pigment rouge",      /*spanish*/"una vestimenta rubí",     /*italian*/"un abito amaranto",     /*german*/"Deutsch"},
                       Text{"fireproof fabric", /*french*/"un trésor anti-flamme", /*spanish*/"una ignífuga prenda",     /*italian*/"un indumento ignifugo", /*german*/"Deutsch"},
                       Text{"cooking clothes",  /*french*/"une tenue de cuisine",  /*spanish*/"unos abrasantes ropajes", /*italian*/"una tuta da pompieri",  /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a tunic", /*french*/"une tunique", /*spanish*/"un sayo", /*italian*/"una veste", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Goron Tunic", /*french*/"une tunique Goron", /*spanish*/"un sayo goron", /*italian*/"una veste dei Goron", /*german*/"Deutsch"}
    );

    hintTable[ZORA_TUNIC] = HintText::Item({
                       //obscure text
                       Text{"a sapphire suit", /*french*/"un pigment bleuté",      /*spanish*/"una vestidura zafiro",     /*italian*/"un indumento indaco",      /*german*/"Deutsch"},
                       Text{"scuba gear",      /*french*/"un habit de plongée",    /*spanish*/"un traje impermeable",     /*italian*/"una muta da sommozzatore", /*german*/"Deutsch"},
                       Text{"a swimsuit",      /*french*/"un costume de baignade", /*spanish*/"unos ropajes sumergibles", /*italian*/"un costume da bagno",      /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a tunic",             /*french*/"une tunique",            /*spanish*/"un sayo",   /*italian*/"una veste",           /*german*/"Deutsch"},
                       Text{"something expensive", /*french*/"une chose dispendieuse", /*spanish*/"algo caro", /*italian*/"qualcosa di costoso", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Zora Tunic", /*french*/"une tunique Zora", /*spanish*/"un sayo zora", /*italian*/"una veste degli Zora", /*german*/"Deutsch"}
    );

    hintTable[IRON_BOOTS] = HintText::Item({
                       //obscure text
                       Text{"sink shoes",   /*french*/"un boulet de fer",             /*spanish*/"un calzado de las profundidades", /*italian*/"scarpe sprofondanti", /*german*/"Deutsch"},
                       Text{"clank cleats", /*french*/"une paire de talons bruyants", /*spanish*/"unas suelas férreas",             /*italian*/"ciabatte chiassose",  /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"some boots",                    /*french*/"une paire de bottes",                  /*spanish*/"un par de botas",                     /*italian*/"un paio di stivali",                         /*german*/"Deutsch"},
                       Text{"a feature of the Water Temple", /*french*/"une particularité du temple de l'eau", /*spanish*/"algo particular del Templo del Agua", /*italian*/"qualcosa da usare nel Santuario dell'Acqua", /*german*/"Deutsch"},
                       Text{"something heavy",               /*french*/"une chose pesante",                    /*spanish*/"algo de lo más pesado",               /*italian*/"uno strumento per immersioni",               /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Iron Boots", /*french*/"une paire de bottes de plomb", /*spanish*/"las botas de hierro", /*italian*/"gli stivali di ferro", /*german*/"Deutsch"}
    );

    hintTable[HOVER_BOOTS] = HintText::Item({
                       //obscure text
                       Text{"butter boots",    /*french*/"une paire de patins de beurre",   /*spanish*/"unas suelas resvaladizas",    /*italian*/"babbuccie burrose",  /*german*/"Deutsch"},
                       Text{"sacred slippers", /*french*/"une paire de pantoufles sacrées", /*spanish*/"unos escurridizos botines",   /*italian*/"scarpe scivolose",   /*german*/"Deutsch"},
                       Text{"spacewalkers",    /*french*/"une paire de bottes spatiales",   /*spanish*/"un calzado antigravitatorio", /*italian*/"elisori di gravità", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"some boots", /*french*/"une paire de bottes", /*spanish*/"un par de botas", /*italian*/"un paio di stivali", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Hover Boots", /*french*/"une paire de bottes des airs", /*spanish*/"las botas voladoras", /*italian*/"gli stivali alati", /*german*/"Deutsch"}
    );


    hintTable[ZELDAS_LETTER] = HintText::Item({
                       //obscure text
                       Text{"an autograph",     /*french*/"un autographe",        /*spanish*/"un autógrafo",         /*italian*/"un autografo",            /*german*/"Deutsch"},
                       Text{"royal stationery", /*french*/"du papier royal",      /*spanish*/"un escrito real",      /*italian*/"cancelleria regale",      /*german*/"Deutsch"},
                       Text{"royal snail mail", /*french*/"une enveloppe royale", /*spanish*/"correo de la realeza", /*italian*/"un regale lasciapassare", /*german*/"Deutsch"},
                     }, {},
                       //clear text
                       Text{"Zelda's Letter", /*french*/"la Lettre de Zelda", /*spanish*/"la carta de Zelda", /*italian*/"la lettera di Zelda", /*german*/"Deutsch"}
    );

    hintTable[WEIRD_EGG] = HintText::Item({
                       //obscure text
                       Text{"a chicken dilemma", /*french*/"un drôle d'ovale", /*spanish*/"el dilema de la gallina", /*italian*/"un ovale incognito", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"an egg", /*french*/"un oeuf", /*spanish*/"un huevo", /*italian*/"un uovo", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Weird Egg", /*french*/"l'œuf curieux", /*spanish*/"el huevo extraño", /*italian*/"l'uovo misterioso", /*german*/"Deutsch"}
    );

    hintTable[BOOMERANG] = HintText::Item({
                       //obscure text
                       Text{"a banana",       /*french*/"une banane",            /*spanish*/"un plátano",         /*italian*/"una banana",         /*german*/"Deutsch"},
                       Text{"a stun stick",   /*french*/"un bâton étourdissant", /*spanish*/"un palo aturdidor",  /*italian*/"un bastone rotante", /*german*/"Deutsch"},
                       Text{"a yellow angle", /*french*/"un angle jaune",        /*spanish*/"un ángulo amarillo", /*italian*/"un angolo giallo",   /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"something that can grab things", /*french*/"une chose qui peut attraper",  /*spanish*/"algo que pueda agarrar cosas", /*italian*/"uno strumento per afferrare",  /*german*/"Deutsch"},
                       Text{"something that can stun",        /*french*/"une chose qui peut paralyser", /*spanish*/"algo que pueda paralizar",     /*italian*/"qualcosa che può paralizzare", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Boomerang", /*french*/"le boomerang", /*spanish*/"el bumerán", /*italian*/"il boomerang", /*german*/"Deutsch"}
    );

    hintTable[LENS_OF_TRUTH] = HintText::Item({
                       //obscure text
                       Text{"a lie detector",     /*french*/"un détecteur de mensonges", /*spanish*/"el detector de ilusiones", /*italian*/"un rivelatore di illusioni", /*german*/"Deutsch"},
                       Text{"a ghost tracker",    /*french*/"un trouve-fantôme",         /*spanish*/"el rastreador paranormal", /*italian*/"un trova-fantasmi",          /*german*/"Deutsch"},
                       Text{"true sight",         /*french*/"le troisième œil",          /*spanish*/"el ojo que todo ve",       /*italian*/"un monocolo",                /*german*/"Deutsch"},
                       Text{"a detective's tool", /*french*/"un trésor Sheikah",         /*spanish*/"la revelación verdadera",  /*italian*/"uno strumento da detective", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a secret-finding tool", /*french*/"un cherche-secrets", /*spanish*/"un instrumento para hallar objetos", /*italian*/"uno strumento Sheikah", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Lens of Truth", /*french*/"le monocle de Vérité", /*spanish*/"la Lupa de la Verdad", /*italian*/"la lente della verità", /*german*/"Deutsch"}
    );

    hintTable[MEGATON_HAMMER] = HintText::Item({
                       //obscure text
                       Text{"the dragon smasher", /*french*/"le tueur de dragons",      /*spanish*/"un destructor de dragones", /*italian*/"l'ammazzadraghi",                     /*german*/"Deutsch"},
                       Text{"the metal mallet",   /*french*/"un outil de construction", /*spanish*/"un mazo de metal",          /*italian*/"un maglio in metallo",                /*german*/"Deutsch"},
                       Text{"the heavy hitter",   /*french*/"un poids lourd",           /*spanish*/"un machacador",             /*italian*/"una misura di energia termonucleare", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"something that can remove boulders", /*french*/"une chose qui enlève les rochers", /*spanish*/"algo que pueda quitar rocas", /*italian*/"qualcosa per rimuovere macigni", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Megaton Hammer", /*french*/"la masse des titans", /*spanish*/"el martillo Megatón", /*italian*/"il martello megaton", /*german*/"Deutsch"}
    );

    hintTable[SHARD_OF_AGONY] = HintText::Item({
                       //obscure text
                       Text{"the shake shard", /*french*/"le fragment vibrant", /*spanish*/"el fragmento tintineante", /*italian*/"un tesoro sonoro",   /*german*/"Deutsch"},
                       Text{"a blue alarm",    /*french*/"une alerte bleue",    /*spanish*/"una azul alarma",          /*italian*/"una sirena azzurra", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a prize of the House of Skulltulas", /*french*/"un prix de la maison des Skulltulas", /*spanish*/"un obsequio de la Casa Skulltula",   /*italian*/"un premio delle Aracnule", /*german*/"Deutsch"},
                       Text{"a secret-finding tool",              /*french*/"un cherche-secrets",                  /*spanish*/"un instrumento para hallar objetos", /*italian*/"uno strumento Sheikah",    /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Shard of Agony", /*french*/"le fragment de souffrance", /*spanish*/"la Piedra de la Agonía", /*italian*/"il cristallo sonoro", /*german*/"Deutsch"}
    );

    hintTable[DINS_FIRE] = HintText::Item({
                       //obscure text
                       Text{"an inferno",  /*french*/"un brasier",               /*spanish*/"un incendio",       /*italian*/"un incendio",        /*german*/"Deutsch"},
                       Text{"a heat wave", /*french*/"une vague de chaleur",     /*spanish*/"una onda de calor", /*italian*/"un'ondata di caldo", /*german*/"Deutsch"},
                       Text{"a red ball",  /*french*/"une explosion de flammes", /*spanish*/"una roja esfera",   /*italian*/"una sfera rossa",    /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a Great Fairy's power", /*french*/"le pouvoir d'une grande fée", /*spanish*/"el poder de una Gran Hada", /*italian*/"il potere di una Fata radiosa", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"Din's Fire", /*french*/"le feu de Din", /*spanish*/"el Fuego de Din", /*italian*/"il fuoco di Din", /*german*/"Deutsch"}
    );

    hintTable[FARORES_WIND] = HintText::Item({
                       //obscure text
                       Text{"teleportation",     /*french*/"la téléportation",       /*spanish*/"un teletransportador",   /*italian*/"il teletrasporto", /*german*/"Deutsch"},
                       Text{"a relocation rune", /*french*/"une rune de relocation", /*spanish*/"una runa de transporte", /*italian*/"la Runa Warp",     /*german*/"Deutsch"},
                       Text{"a green ball",      /*french*/"une boule verte",        /*spanish*/"una verde esfera",       /*italian*/"una sfera verde",  /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a Great Fairy's power", /*french*/"le pouvoir d'une grande fée", /*spanish*/"el poder de una Gran Hada", /*italian*/"il potere di una Fata radiosa", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"Farore's Wind", /*french*/"le vent de Farore", /*spanish*/"el Viento de Farore", /*italian*/"il vento di Farore", /*german*/"Deutsch"}
    );

    hintTable[NAYRUS_LOVE] = HintText::Item({
                       //obscure text
                       Text{"a safe space",        /*french*/"une bulle de cristal", /*spanish*/"una seguridad temporal", /*italian*/"un minuto di sicurezza", /*german*/"Deutsch"},
                       Text{"an impregnable aura", /*french*/"un aura impénétrable", /*spanish*/"un aura impenetrable",   /*italian*/"un'aura impenetrabile",  /*german*/"Deutsch"},
                       Text{"a blue barrier",      /*french*/"une toison bleu",      /*spanish*/"una barrera azul",       /*italian*/"una barriera azzurra",   /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a Great Fairy's power", /*french*/"le pouvoir d'une grande fée", /*spanish*/"el poder de una Gran Hada", /*italian*/"il potere di una Fata radiosa", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"Nayru's Love", /*french*/"l'amour de Nayru", /*spanish*/"el Amor de Nayru", /*italian*/"l'amore di Nayru", /*german*/"Deutsch"}
    );

    hintTable[FIRE_ARROWS] = HintText::Item({
                       //obscure text
                       Text{"the furnace firearm" , /*french*/"une fusée solaire",     /*spanish*/"el ardiente aguijón", /*italian*/"il dardo ardente",    /*german*/"Deutsch"},
                       Text{"the burning bolts",    /*french*/"un obus enflammé",      /*spanish*/"las puntas ígneas",   /*italian*/"i legni ignei",       /*german*/"Deutsch"},
                       Text{"a magma missile",      /*french*/"un missile volcanique", /*spanish*/"el misil abrasador",  /*italian*/"un missile di magma", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a magic arrow", /*french*/"une flèche magique", /*spanish*/"una flecha mágica", /*italian*/"una freccia magica", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Fire Arrows", /*french*/"la flèche de feu", /*spanish*/"la flecha de fuego", /*italian*/"la freccia di fuoco", /*german*/"Deutsch"}
    );

    hintTable[ICE_ARROWS] = HintText::Item({
                       //obscure text
                       Text{"the refrigerator rocket", /*french*/"un missile pétrifiant", /*spanish*/"el misil congelador",    /*italian*/"una freccia fredda",  /*german*/"Deutsch"},
                       Text{"the frostbite bolts",     /*french*/"un froid mordant",      /*spanish*/"las puntas gélidas",     /*italian*/"un'arma assiderante", /*german*/"Deutsch"},
                       Text{"an iceberg maker",        /*french*/"une aiguille glaciale", /*spanish*/"el control de escarcha", /*italian*/"un ghiacciolo",       /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a magic arrow",           /*french*/"une flèche magique",           /*spanish*/"una flecha mágica",        /*italian*/"una freccia magica",           /*german*/"Deutsch"},
                       Text{"something that can stun", /*french*/"une chose qui peut paralyser", /*spanish*/"algo que pueda paralizar", /*italian*/"qualcosa che può paralizzare", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Ice Arrows", /*french*/"la flèche de glace", /*spanish*/"la flecha de hielo", /*italian*/"la freccia di ghiaccio", /*german*/"Deutsch"}
    );

    hintTable[LIGHT_ARROWS] = HintText::Item({
                       //obscure text
                       Text{"the shining shot",      /*french*/"l'arme brillante",      /*spanish*/"el haz de luz",               /*italian*/"un'arma splendente",     /*german*/"Deutsch"},
                       Text{"the luminous launcher", /*french*/"un jet de lumière",     /*spanish*/"el disparo luminoso",         /*italian*/"luce da lancio",         /*german*/"Deutsch"},
                       Text{"Ganondorf's bane",      /*french*/"le fléau de Ganondorf", /*spanish*/"la perdición de Ganondorf",   /*italian*/"la rovina di Ganondorf", /*german*/"Deutsch"},
                       Text{"the lighting bolts",    /*french*/"l'éclair sacré",        /*spanish*/"las puntas resplandecientes", /*italian*/"saette sfolgoranti",     /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a magic arrow", /*french*/"une flèche magique", /*spanish*/"una flecha mágica", /*italian*/"una freccia magica", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Light Arrows", /*french*/"la flèche de lumière", /*spanish*/"la flecha de luz", /*italian*/"la freccia di luce", /*german*/"Deutsch"}
    );

    hintTable[GERUDO_TOKEN] = HintText::Item({
                       //obscure text
                       Text{"a girl club membership", /*french*/"une carte de membre", /*spanish*/"una fémina membresía", /*italian*/"un'iscrizione ad un club",   /*german*/"Deutsch"},
                       Text{"a desert tribe's pass",  /*french*/"un laissez-passer",   /*spanish*/"el vale del desierto", /*italian*/"la tessera delle amazzoni",  /*german*/"Deutsch"},
                     }, {
                       Text{"a token of recognition", /*french*/"une preuve de reconnaissance", /*spanish*/"una prueba de reconocimiento", /*italian*/"un simbolo di riconoscimento", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Gerudo Token", /*french*/"la carte Gerudo", /*spanish*/"el pase de socio gerudo", /*italian*/"la Gerudo Card", /*german*/"Deutsch"}
    );

    hintTable[MAGIC_BEAN] = HintText::Item({
                       //obscure text
                       Text{"a wizardly legume", /*french*/"un légume ensorcelé", /*spanish*/"una legumbre hechizada", /*italian*/"un legume miracoloso", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"something sometimes buried", /*french*/"une chose parfois enterrée", /*spanish*/"algo a veces enterrado", /*italian*/"qualcosa a volte sotterrato", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Magic Bean", /*french*/"un haricot magique", /*spanish*/"una judía mágica", /*italian*/"un fagiolo magico", /*german*/"Deutsch"}
    );

    hintTable[MAGIC_BEAN_PACK] = HintText::Item({
                       //obscure text
                       Text{"wizardly legumes", /*french*/"un paquet de légumes ensorcelés", /*spanish*/"unas legumbres hechizadas", /*italian*/"legumi miracolosi", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"something sometimes buried", /*french*/"une chose parfois enterrée", /*spanish*/"algo a veces enterrado", /*italian*/"qualcosa a volte sotterrato", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"Magic Beans", /*french*/"un paquet de haricots magiques", /*spanish*/"unas judías mágicas", /*italian*/"un pacco di fagioli magici", /*german*/"Deutsch"}
    );

    hintTable[DOUBLE_DEFENSE] = HintText::Item({
                       //obscure text
                       Text{"a white outline",   /*french*/"un rebord blanc",               /*spanish*/"un contorno blanco",    /*italian*/"un contorno bianco",       /*german*/"Deutsch"},
                       Text{"damage decrease",   /*french*/"une protection supplémentaire", /*spanish*/"una reducción de daño", /*italian*/"una diminuzione di danno", /*german*/"Deutsch"},
                       Text{"strengthened love", /*french*/"un amour coriace",              /*spanish*/"un amor fortalecido",   /*italian*/"amore rafforzato",         /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a Great Fairy's power", /*french*/"le pouvoir d'une grande fée", /*spanish*/"el poder de una Gran Hada", /*italian*/"il potere di una Fata radiosa", /*german*/"Deutsch"},
                       Text{"something heart-shaped", /*french*/"une chose en forme de cœur", /*spanish*/"algo con forma de corazón", /*italian*/"qualcosa a forma di cuore",     /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"Double Defense", /*french*/"la double défence", /*spanish*/"la doble defensa", /*italian*/"la doppia difesa", /*german*/"Deutsch"}
    );

    hintTable[GOLD_SKULLTULA_TOKEN] = HintText::Item({
                       //obscure text
                       Text{"proof of destruction",   /*french*/"un certificat d'élimination", /*spanish*/"una prueba de la destrucción",   /*italian*/"la prova di un'eliminazione", /*german*/"Deutsch"},
                       Text{"an arachnid chip",       /*french*/"un symbole cranien",          /*spanish*/"una figura arácnida",            /*italian*/"un pezzetto di aracnide",     /*german*/"Deutsch"},
                       Text{"spider remains",         /*french*/"une dépouille dorée",         /*spanish*/"unos restos dorados",            /*italian*/"spoglie di ragno",            /*german*/"Deutsch"},
                       Text{"one percent of a curse", /*french*/"un centième de malédiction",  /*spanish*/"una centésima de una maldición", /*italian*/"un centesimo di maledizione", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a token of recognition",     /*french*/"une preuve de reconnaissance", /*spanish*/"una prueba de reconocimiento", /*italian*/"un simbolo di riconoscimento", /*german*/"Deutsch"},
                       Text{"something sometimes buried", /*french*/"une chose parfois enterrée",   /*spanish*/"algo a veces enterrado",       /*italian*/"qualcosa a volte sotterrato",  /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Gold Skulltula Token", /*french*/"un jeton de Skulltula d'or", /*spanish*/"un símbolo de skulltula dorada", /*italian*/"un teschio d'oro", /*german*/"Deutsch"}
    );

    hintTable[POCKET_EGG] = HintText::Item({
                       //obscure text
                       Text{"a Cucco container",   /*french*/"un réservoir à Cocotte", /*spanish*/"cuco contenido",     /*italian*/"una noce di coccò",     /*german*/"Deutsch"},
                       Text{"a Cucco, eventually", /*french*/"un poussin éventuel",    /*spanish*/"un futuro cuco",     /*italian*/"un coccò (fra un po')", /*german*/"Deutsch"},
                       Text{"a fowl youth",        /*french*/"une omelette crue",      /*spanish*/"una dulce juventud", /*italian*/"una frittata cruda",    /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a trade quest item", /*french*/"un objet de quête d'échanges", /*spanish*/"un objeto de una misión secundaria", /*italian*/"un oggetto da scambiare", /*german*/"Deutsch"},
                       Text{"an egg",             /*french*/"un oeuf",                      /*spanish*/"un huevo",                           /*italian*/"un uovo",                 /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Pocket Egg", /*french*/"l'œuf de poche", /*spanish*/"el huevo de bolsillo", /*italian*/"l'uovo tascabile", /*german*/"Deutsch"}
    );

    hintTable[POCKET_CUCCO] = HintText::Item({
                       //obscure text
                       Text{"a little clucker", /*french*/"un petit glousseur", /*spanish*/"un pollito chiquito", /*italian*/"una piccola chioccia", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a trade quest item", /*french*/"un objet de quête d'échanges", /*spanish*/"un objeto de una misión secundaria", /*italian*/"un oggetto da scambiare", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Pocket Cucco", /*french*/"le Cocotte de poche", /*spanish*/"el cuco de bolsillo", /*italian*/"il coccò tascabile", /*german*/"Deutsch"}
    );

    hintTable[COJIRO] = HintText::Item({
                       //obscure text
                       Text{"a cerulean capon", /*french*/"un paon azur", /*spanish*/"un cerúleo capón", /*italian*/"un cappone ceruleo", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a trade quest item", /*french*/"un objet de quête d'échanges", /*spanish*/"un objeto de una misión secundaria", /*italian*/"un oggetto da scambiare", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"Cojiro", /*french*/"le p'tit poulet", /*spanish*/"a Cojiro", /*italian*/"Coblù", /*german*/"Deutsch"}
    );

    hintTable[ODD_MUSHROOM] = HintText::Item({
                       //obscure text
                       Text{"a powder ingredient", /*french*/"un ingrédient à poudre", /*spanish*/"un oloroso ingrediente", /*italian*/"un ingrediente medicinale", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a trade quest item", /*french*/"un objet de quête d'échanges", /*spanish*/"un objeto de una misión secundaria", /*italian*/"un oggetto da scambiare", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"an Odd Mushroom", /*french*/"un champignon suspect", /*spanish*/"un champiñón extraño", /*italian*/"un fungo strano", /*german*/"Deutsch"}
    );

    hintTable[ODD_POULTICE] = HintText::Item({
                       //obscure text
                       Text{"Granny's goodies", /*french*/"la confiserie de mamie", /*spanish*/"la especialidad de la abuela", /*italian*/"la conserva della nonna", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"something that contains medicine", /*french*/"une chose médicamenteuse",     /*spanish*/"algo que contenga medicina",         /*italian*/"una medicina",            /*german*/"Deutsch"},
                       Text{"something with a strange smell",   /*french*/"une chose qui sent bizarre",   /*spanish*/"algo con un olor extraño",           /*italian*/"una cosa strana",         /*german*/"Deutsch"},
                       Text{"a trade quest item",               /*french*/"un objet de quête d'échanges", /*spanish*/"un objeto de una misión secundaria", /*italian*/"un oggetto da scambiare", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"an Odd Poultice", /*french*/"une mixture suspecte", /*spanish*/"una medicina rara", /*italian*/"una medicina strana", /*german*/"Deutsch"}
    );

    hintTable[POACHERS_SAW] = HintText::Item({
                       //obscure text
                       Text{"a tree killer", /*french*/"un coupeur d'arbres", /*spanish*/"un destructor de árboles", /*italian*/"un distruttore d'alberi", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a trade quest item", /*french*/"un objet de quête d'échanges", /*spanish*/"un objeto de una misión secundaria", /*italian*/"un oggetto da scambiare", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Poacher's Saw", /*french*/"la scie du chasseur", /*spanish*/"la sierra del furtivo", /*italian*/"la sega del bracconiere", /*german*/"Deutsch"}
    );

    hintTable[BROKEN_SWORD] = HintText::Item({
                       //obscure text
                       Text{"a shattered slicer", /*french*/"une arme cassée", /*spanish*/"una rebanadora rota", /*italian*/"una spada spaccata", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a trade quest item", /*french*/"un objet de quête d'échanges", /*spanish*/"un objeto de una misión secundaria", /*italian*/"un oggetto da scambiare", /*german*/"Deutsch"},
                       Text{"a sword",            /*french*/"une épée",                     /*spanish*/"una espada",                         /*italian*/"una spada",               /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Broken Goron's Sword", /*french*/"l'épée brisée de Goron", /*spanish*/"la espada goron rota", /*italian*/"la spada rotta dei Goron", /*german*/"Deutsch"}
    );

    hintTable[PRESCRIPTION] = HintText::Item({
                       //obscure text
                       Text{"a pill pamphlet", /*french*/"un document urgent", /*spanish*/"un instructivo medicinal", /*italian*/"un foglietto illustrativo", /*german*/"Deutsch"},
                       Text{"a doctor's note", /*french*/"un papier médical",  /*spanish*/"unas notas del doctor",    /*italian*/"la nota del dottore",       /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a trade quest item", /*french*/"un objet de quête d'échanges", /*spanish*/"un objeto de una misión secundaria", /*italian*/"un oggetto da scambiare", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Prescription", /*french*/"une ordonnance", /*spanish*/"la receta", /*italian*/"la ricetta", /*german*/"Deutsch"}
    );

    hintTable[EYEBALL_FROG] = HintText::Item({
                       //obscure text
                       Text{"a perceiving polliwog", /*french*/"un amphibien", /*spanish*/"un variopinto batracio", /*italian*/"una raganella", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a trade quest item", /*french*/"un objet de quête d'échanges", /*spanish*/"un objeto de una misión secundaria", /*italian*/"un oggetto da scambiare", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Eyeball Frog", /*french*/"le crapaud-qui-louche", /*spanish*/"la rana de ojos saltones", /*italian*/"la rana occhiuta", /*german*/"Deutsch"}
    );

    hintTable[EYEDROPS] = HintText::Item({
                       //obscure text
                       Text{"a vision vial", /*french*/"une solution oculaire", /*spanish*/"un remedio para la vista", /*italian*/"un medicinale oculare", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a trade quest item", /*french*/"un objet de quête d'échanges", /*spanish*/"un objeto de una misión secundaria", /*italian*/"un oggetto da scambiare", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Eyedrops", /*french*/"une phiole de super gouttes", /*spanish*/"las supergotas oculares", /*italian*/"il miglior collirio del mondo", /*german*/"Deutsch"}
    );

    hintTable[CLAIM_CHECK] = HintText::Item({
                       //obscure text
                       Text{"a three day wait", /*french*/"un rendez-vous dans trois jours", /*spanish*/"unos tres días de espera", /*italian*/"un'attesa di tre giorni", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a trade quest item", /*french*/"un objet de quête d'échanges", /*spanish*/"un objeto de una misión secundaria", /*italian*/"un oggetto da scambiare", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Claim Check", /*french*/"un certificat", /*spanish*/"el recibo", /*italian*/"il buono", /*german*/"Deutsch"}
    );

    hintTable[PROGRESSIVE_HOOKSHOT] = HintText::Item({
                       //obscure text
                       Text{"Dampé's keepsake", /*french*/"l'héritage d'Igor",   /*spanish*/"un recuerdo de Dampé", /*italian*/"l'eredità di Danpei",   /*german*/"Deutsch"},
                       Text{"the Grapple Beam", /*french*/"le rayon grippeur",   /*spanish*/"una garra metálica",   /*italian*/"il Raggio Gancio",      /*german*/"Deutsch"},
                       Text{"the BOING! chain", /*french*/"la chaîne de BOING!", /*spanish*/"una cadena retráctil", /*italian*/"il tesoro BOING BOING", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"something that can grab things", /*french*/"une chose qui peut attraper",  /*spanish*/"algo que pueda agarrar cosas", /*italian*/"uno strumento per afferrare",  /*german*/"Deutsch"},
                       Text{"something that can stun",        /*french*/"une chose qui peut paralyser", /*spanish*/"algo que pueda paralizar",     /*italian*/"qualcosa che può paralizzare", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Hookshot", /*french*/"un grappin", /*spanish*/"un gancho", /*italian*/"un arpione", /*german*/"Deutsch"}
    );

    hintTable[PROGRESSIVE_STRENGTH] = HintText::Item({
                       //obscure text
                       Text{"power gloves",    /*french*/"une paire de gants de travail", /*spanish*/"unos poderosos guanteletes", /*italian*/"i guanti della forza",           /*german*/"Deutsch"},
                       Text{"metal mittens",   /*french*/"une paire de mitaines",         /*spanish*/"unas manoplas metálicas",    /*italian*/"un paio di manopole metalliche", /*german*/"Deutsch"},
                       Text{"the heavy lifty", /*french*/"la puissance de dix hommes",    /*spanish*/"un levantamiento pesado",    /*italian*/"un sollevatore di pesi",         /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"something that can remove boulders", /*french*/"une chose qui enlève les rochers", /*spanish*/"algo que pueda quitar rocas", /*italian*/"qualcosa per rimuovere macigni", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Strength Upgrade", /*french*/"une amélioration de force", /*spanish*/"un aumento de fuerza", /*italian*/"un potenziamento di forza", /*german*/"Deutsch"}
    );

    hintTable[PROGRESSIVE_BOMB_BAG] = HintText::Item({
                       //obscure text
                       Text{"an explosive container", /*french*/"un porte-grenade",      /*spanish*/"un recipiente explosivo", /*italian*/"un contenitore deflagratore", /*german*/"Deutsch"},
                       Text{"a blast bag",            /*french*/"un estomac de Dodongo", /*spanish*/"un zurrón de estallidos", /*italian*/"pelle di Dodongo",            /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"explosives",                         /*french*/"un paquet d'explosifs",            /*spanish*/"un montón de explosivos",     /*italian*/"un pacchetto di esplosivi",      /*german*/"Deutsch"},
                       Text{"something that can remove boulders", /*french*/"une chose qui enlève les rochers", /*spanish*/"algo que pueda quitar rocas", /*italian*/"qualcosa per rimuovere macigni", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Bomb Bag", /*french*/"un sac de bombes", /*spanish*/"un saco de bombas", /*italian*/"un portabombe", /*german*/"Deutsch"}
    );

    hintTable[PROGRESSIVE_BOW] = HintText::Item({
                       //obscure text
                       Text{"an archery enabler",     /*french*/"un facilitateur de tir", /*spanish*/"un tiro al blanco",        /*italian*/"un'arma da arciere",              /*german*/"Deutsch"},
                       Text{"a danger dart launcher", /*french*/"un tire-fléchette",      /*spanish*/"un peligroso lanzadardos", /*italian*/"un lanciatore di punte pungenti", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a projectile shooter", /*french*/"un tire-projectile", /*spanish*/"un arma de proyectil", /*italian*/"un'arma che spara", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Bow", /*french*/"l'arc des fées", /*spanish*/"un arco de las hadas", /*italian*/"un arco", /*german*/"Deutsch"}
    );

    hintTable[PROGRESSIVE_SLINGSHOT] = HintText::Item({
                       //obscure text
                       Text{"a seed shooter",     /*french*/"un lance-noix",     /*spanish*/"un lanzasemillas",       /*italian*/"uno sparasemi",             /*german*/"Deutsch"},
                       Text{"a rubberband",       /*french*/"un élastique",      /*spanish*/"un tirachinas",          /*italian*/"un elastico",               /*german*/"Deutsch"},
                       Text{"a child's catapult", /*french*/"un jouet d'enfant", /*spanish*/"una catapulta infantil", /*italian*/"una catapulta per bambini", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a projectile shooter", /*french*/"un tire-projectile", /*spanish*/"un arma de proyectil", /*italian*/"un'arma che spara", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Slingshot", /*french*/"un lance-pierre", /*spanish*/"una resortera de las hadas", /*italian*/"una fionda", /*german*/"Deutsch"}
    );

    hintTable[PROGRESSIVE_WALLET] = HintText::Item({
                       //obscure text
                       Text{"a mo' money holder", /*french*/"un sac à sous",     /*spanish*/"una cartera de dinero", /*italian*/"un sacco di grana",  /*german*/"Deutsch"},
                       Text{"a gem purse",        /*french*/"une sacoche",       /*spanish*/"un zurrón de gemas",    /*italian*/"una borsa di gemme", /*german*/"Deutsch"},
                       Text{"a portable bank",    /*french*/"une petite banque", /*spanish*/"un banco portable",     /*italian*/"un salvadanaio",     /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a prize of the House of Skulltulas", /*french*/"un prix de la maison des Skulltulas", /*spanish*/"un obsequio de la Casa Skulltula", /*italian*/"un premio delle Aracnule", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Wallet", /*french*/"une bourse", /*spanish*/"una bolsa de rupias", /*italian*/"un portarupie", /*german*/"Deutsch"}
    );

    hintTable[PROGRESSIVE_SCALE] = HintText::Item({
                       //obscure text
                       Text{"a deeper dive",   /*french*/"une bulle de plongée", /*spanish*/"un profundo buceo",    /*italian*/"un'immensa immersione", /*german*/"Deutsch"},
                       Text{"a piece of Zora", /*french*/"un morceau de Zora",   /*spanish*/"un fragmento de Zora", /*italian*/"un pezzetto di Zora",   /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a diving tool", /*french*/"un outil de plongée", /*spanish*/"un instrumento de buceo", /*italian*/"uno strumento per immersioni", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Zora Scale", /*french*/"une écaille Zora", /*spanish*/"una escama Zora", /*italian*/"una squama Zora", /*german*/"Deutsch"}
    );

    hintTable[PROGRESSIVE_NUT_UPGRADE] = HintText::Item({
                       //obscure text
                       Text{"more nuts",         /*french*/"encore plus de noix", /*spanish*/"más semillas de nogal",  /*italian*/"più noci",                             /*german*/"Deutsch"},
                       Text{"flashbang storage", /*french*/"un sac à noix",       /*spanish*/"más frutos aturdidores", /*italian*/"una tasca piena di granate stordenti", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"some Deku munitions", /*french*/"un paquet de munitions Mojo", /*spanish*/"un montón de municiones Deku",  /*italian*/"un pacchetto di munizioni Deku", /*german*/"Deutsch"},
                       Text{"something that can stun", /*french*/"une chose qui peut paralyser", /*spanish*/"algo que pueda paralizar", /*italian*/"qualcosa che può paralizzare",   /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"Deku Nut Capacity", /*french*/"une augmentation de noix Mojo", /*spanish*/"un aumento de nueces deku", /*italian*/"un'espansione per le noci Deku", /*german*/"Deutsch"}
    );

    hintTable[PROGRESSIVE_STICK_UPGRADE] = HintText::Item({
                       //obscure text
                       Text{"a lumber rack",        /*french*/"un paquet de bois",    /*spanish*/"más bastones", /*italian*/"una tasca piena di stuzzicadenti", /*german*/"Deutsch"},
                       Text{"more flammable twigs", /*french*/"beaucoup de branches", /*spanish*/"más varas",    /*italian*/"più ramaglie infiammabili",        /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"some Deku munitions", /*french*/"un paquet de munitions Mojo", /*spanish*/"un montón de municiones Deku", /*italian*/"un pacchetto di munizioni Deku", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"Deku Stick Capacity", /*french*/"une augmentation de bâtons Mojo", /*spanish*/"un aumento de palos deku", /*italian*/"un'espansione per i rami Deku", /*german*/"Deutsch"}
    );

    hintTable[PROGRESSIVE_MAGIC_METER] = HintText::Item({
                       //obscure text
                       Text{"mystic training",    /*french*/"un potentiel magique", /*spanish*/"una maestría mística", /*italian*/"un addestramento mistico", /*german*/"Deutsch"},
                       Text{"pixie dust",         /*french*/"de la poudre de fée",  /*spanish*/"un polvo de hada",     /*italian*/"polvere di fata",          /*german*/"Deutsch"},
                       Text{"a green rectangle",  /*french*/"un rectangle vert",    /*spanish*/"una verduzca barra",   /*italian*/"un rettangolo verde",      /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a Great Fairy's power", /*french*/"le pouvoir d'une grande fée", /*spanish*/"el poder de una Gran Hada", /*italian*/"il potere di una Fata radiosa", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Magic Meter", /*french*/"une jauge de magie", /*spanish*/"un aumento de poder mágico", /*italian*/"una barra della magia", /*german*/"Deutsch"}
    );

    hintTable[PROGRESSIVE_OCARINA] = HintText::Item({
                       //obscure text
                       Text{"a flute",       /*french*/"un bec musical",         /*spanish*/"un utensilio musical", /*italian*/"una piccola oca",   /*german*/"Deutsch"},
                       Text{"a music maker", /*french*/"un porteur de chansons", /*spanish*/"un instrumento",       /*italian*/"una patata bucata", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"something given by Saria",           /*french*/"un cadeau de Saria",     /*spanish*/"un obsequio de Saria",              /*italian*/"una cosa di Saria",             /*german*/"Deutsch"},
                       Text{"something kept by the royal family", /*french*/"une chose qui paralyse", /*spanish*/"algo guardado por la familia real", /*italian*/"una cosa della famiglia reale", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"an Ocarina", /*french*/"un ocarina", /*spanish*/"una ocarina", /*italian*/"un'ocarina", /*german*/"Deutsch"}
    );

    hintTable[PROGRESSIVE_BOMBCHUS] = HintText::Item({
                       //obscure text
                       Text{"mice bombs",     /*french*/"un adorable explosif",  /*spanish*/"unas bombas roedoras",       /*italian*/"sorci esplosivi",   /*german*/"Deutsch"},
                       Text{"proximity mice", /*french*/"une mine anti-rongeur", /*spanish*/"unos explosivos ratoncitos", /*italian*/"topi a orologeria", /*german*/"Deutsch"},
                       Text{"wall crawlers",  /*french*/"un rapide grimpeur",    /*spanish*/"unos trepaparedes",          /*italian*/"arrampicamuri",     /*german*/"Deutsch"},
                       Text{"trail blazers",  /*french*/"un zigzag éclatant",    /*spanish*/"unas ratas propulsadas",     /*italian*/"scie a zig-zag",    /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a prize of the House of Skulltulas", /*french*/"un prix de la maison des Skulltulas", /*spanish*/"un obsequio de la Casa Skulltula", /*italian*/"un premio delle Aracnule",  /*german*/"Deutsch"},
                       Text{"explosives",                         /*french*/"un paquet d'explosifs",               /*spanish*/"un montón de explosivos",          /*italian*/"un pacchetto di esplosivi", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"Bombchus", /*french*/"un paquet de Bombchus", /*spanish*/"unos bombchus", /*italian*/"alcune radiomine", /*german*/"Deutsch"}
    );

    hintTable[PROGRESSIVE_GORONSWORD] = HintText::Item({
                       //obscure text
                       Text{"a long blade",   /*french*/"une longue lame", /*spanish*/"una gran hoja", /*italian*/"una lunga lama", /*german*/"Deutsch"},
                       Text{"a Goron weapon", /*french*/"une arme Goron",  /*spanish*/"un arma goron", /*italian*/"un'arma Goron", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a sword", /*french*/"une épée", /*spanish*/"una espada", /*italian*/"una spada", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Goron Sword", /*french*/"une épée Goron", /*spanish*/"una espada goron", /*italian*/"una spada Goron", /*german*/"Deutsch"}
    );

    hintTable[EMPTY_BOTTLE] = HintText::Item({
                       //obscure text
                       Text{"a glass container", /*french*/"un cylindre de cristal", /*spanish*/"un recipiente de cristal", /*italian*/"un vaso di cristallo", /*german*/"Deutsch"},
                       Text{"an empty jar",      /*french*/"une jarre incassable",   /*spanish*/"un frasco vacío",          /*italian*/"una bottiglia",        /*german*/"Deutsch"},
                       Text{"encased air",       /*french*/"un bocal d'air",         /*spanish*/"aire a presión",           /*italian*/"aria rinchiusa",       /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a bottle", /*french*/"un flacon", /*spanish*/"una botella", /*italian*/"un'ampolla", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Bottle", /*french*/"un flacon vide", /*spanish*/"una botella", /*italian*/"un'ampolla", /*german*/"Deutsch"}
    );

    hintTable[BOTTLE_WITH_MILK] = HintText::Item({
                       //obscure text
                       Text{"cow juice",          /*french*/"une source de calcium", /*spanish*/"una fuente de calcio", /*italian*/"una fonte di calcio", /*german*/"Deutsch"},
                       Text{"a white liquid",     /*french*/"un liquide blanc",      /*spanish*/"una bebida nutritiva", /*italian*/"un liquido bianco",   /*german*/"Deutsch"},
                       Text{"a baby's breakfast", /*french*/"du jus pour bébé",      /*spanish*/"un trago para bebés",  /*italian*/"cibo per cuccioli",   /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a bottle", /*french*/"un flacon", /*spanish*/"una botella", /*italian*/"un'ampolla", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Milk Bottle", /*french*/"un flacon de lait", /*spanish*/"una botella de leche", /*italian*/"un'ampolla di latte", /*german*/"Deutsch"}
    );

    hintTable[BOTTLE_WITH_RED_POTION] = HintText::Item({
                       //obscure text
                       Text{"a vitality vial", /*french*/"un mélange de vitalité", /*spanish*/"una pócima vitalicia", /*italian*/"un succo d'arancia",  /*german*/"Deutsch"},
                       Text{"a red liquid",    /*french*/"un liquide rouge",       /*spanish*/"un remedio rojizo",    /*italian*/"un liquido rosso",    /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a bottle", /*french*/"un flacon", /*spanish*/"una botella", /*italian*/"un'ampolla", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Red Potion Bottle", /*french*/"un flacon de potion rouge", /*spanish*/"una botella de poción roja", /*italian*/"un'ampolla di pozione vita", /*german*/"Deutsch"}
    );

    hintTable[BOTTLE_WITH_GREEN_POTION] = HintText::Item({
                       //obscure text
                       Text{"a magic mixture", /*french*/"une réserve magique", /*spanish*/"un potingue mágico",  /*italian*/"un succo di kiwi", /*german*/"Deutsch"},
                       Text{"a green liquid",  /*french*/"un liquide vert",     /*spanish*/"un remedio verduzco", /*italian*/"un liquido verde", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a bottle", /*french*/"un flacon", /*spanish*/"una botella", /*italian*/"un'ampolla", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Green Potion Bottle", /*french*/"un flacon de potion verte", /*spanish*/"una botella de poción verde", /*italian*/"un'ampolla di pozione magica", /*german*/"Deutsch"}
    );

    hintTable[BOTTLE_WITH_BLUE_POTION] = HintText::Item({
                       //obscure text
                       Text{"an ailment antidote", /*french*/"l'élixir ultime", /*spanish*/"un antídoto para el dolor", /*italian*/"uno sciroppo di anice", /*german*/"Deutsch"},
                       Text{"a blue liquid",       /*french*/"un liquide bleu", /*spanish*/"un remedio índigo",         /*italian*/"un liquido blu",        /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a bottle", /*french*/"un flacon", /*spanish*/"una botella", /*italian*/"un'ampolla", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Blue Potion Bottle", /*french*/"un flacon de potion bleue", /*spanish*/"una botella de poción azul", /*italian*/"un'ampolla di pozione curatutto", /*german*/"Deutsch"}
    );

    hintTable[BOTTLE_WITH_FAIRY] = HintText::Item({
                       //obscure text
                       Text{"an imprisoned fairy", /*french*/"une fée emprisonnée", /*spanish*/"un hada atrapada",    /*italian*/"una fata imprigionata", /*german*/"Deutsch"},
                       Text{"an extra life",       /*french*/"une vie de rechange", /*spanish*/"una oportunidad más", /*italian*/"un 1-UP", /*german*/"Deutsch"},
                       Text{"Navi's cousin",       /*french*/"le cousin de Navi",   /*spanish*/"una prima de Navi",   /*italian*/"una cugina di Navi", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a bottle", /*french*/"un flacon", /*spanish*/"una botella", /*italian*/"un'ampolla", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Fairy Bottle", /*french*/"une fée en flacon", /*spanish*/"un hada en una botella", /*italian*/"una fata in un'ampolla", /*german*/"Deutsch"}
    );

    hintTable[BOTTLE_WITH_FISH] = HintText::Item({
                       //obscure text
                       Text{"an aquarium",     /*french*/"un aquarium",              /*spanish*/"un escamado ser",               /*italian*/"un acquario",                /*german*/"Deutsch"},
                       Text{"a deity's snack", /*french*/"le repas d'un dieu marin", /*spanish*/"un tentempié de cierta deidad", /*italian*/"la merenda di una divinità", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a bottle", /*french*/"un flacon", /*spanish*/"una botella", /*italian*/"un'ampolla", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Fish Bottle", /*french*/"un poisson en flacon", /*spanish*/"un pez en una botella", /*italian*/"un pesce in un'ampolla", /*german*/"Deutsch"}
    );

    hintTable[BOTTLE_WITH_BLUE_FIRE] = HintText::Item({
                       //obscure text
                       Text{"a conflagration canteen", /*french*/"une mystérieuse flamme", /*spanish*/"un incendio retenido",    /*italian*/"una fiasca di fiamme", /*german*/"Deutsch"},
                       Text{"an icemelt jar",          /*french*/"un brasier glacial",     /*spanish*/"unas brasas enfrascadas", /*italian*/"freddezza portatile",  /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a bottle", /*french*/"un flacon", /*spanish*/"una botella", /*italian*/"un'ampolla", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Blue Fire Bottle", /*french*/"une flamme bleue en flacon", /*spanish*/"una botella de fuego azul", /*italian*/"un'ampolla di fuoco blu", /*german*/"Deutsch"}
    );

    hintTable[BOTTLE_WITH_BUGS] = HintText::Item({
                       //obscure text
                       Text{"an insectarium",    /*french*/"un insectarium",                  /*spanish*/"unos invertebrados seres",        /*italian*/"un artropode in vetro", /*german*/"Deutsch"},
                       Text{"Skulltula finders", /*french*/"une poignée de trouve-Skulltula", /*spanish*/"unos rastreadores de skulltulas", /*italian*/"cercatori di Aracnule", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a bottle", /*french*/"un flacon", /*spanish*/"una botella", /*italian*/"un'ampolla", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Bug Bottle", /*french*/"un insecte en flacon", /*spanish*/"unos insectos en una botella", /*italian*/"un insetto in un'ampolla", /*german*/"Deutsch"}
    );

    hintTable[BOTTLE_WITH_POE] = HintText::Item({
                       //obscure text
                       Text{"a spooky ghost",    /*french*/"un effroyable fantôme",   /*spanish*/"un espantoso espectro",    /*italian*/"un sinistro spirito",         /*german*/"Deutsch"},
                       Text{"a face in the jar", /*french*/"un visage dans un bocal", /*spanish*/"una expresión enfrascada", /*italian*/"una faccia in una borraccia", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a bottle", /*french*/"un flacon", /*spanish*/"una botella", /*italian*/"un'ampolla", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Poe Bottle", /*french*/"un Esprit en flacon", /*spanish*/"un Poe en una botella", /*italian*/"un Poo in un'ampolla", /*german*/"Deutsch"}
    );

    hintTable[BOTTLE_WITH_BIG_POE] = HintText::Item({
                       //obscure text
                       Text{"the spookiest ghost", /*french*/"un épouvantable spectre", /*spanish*/"el espectro más espeluznante", /*italian*/"un destro spettro",      /*german*/"Deutsch"},
                       Text{"a sidequest spirit",  /*french*/"un précieux esprit",      /*spanish*/"un buen valorado espíritu",    /*italian*/"un fantasma che scappa", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a bottle", /*french*/"un flacon", /*spanish*/"una botella", /*italian*/"un'ampolla", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Big Poe Bottle", /*french*/"une Ame en flacon", /*spanish*/"un Gran Poe en una botella", /*italian*/"un Grande Poo in un'ampolla", /*german*/"Deutsch"}
    );

    hintTable[RUTOS_LETTER] = HintText::Item({
                       //obscure text
                       Text{"a call for help",      /*french*/"un appel au secours",       /*spanish*/"una llamada de auxilio", /*italian*/"una chiamata d'aiuto",   /*german*/"Deutsch"},
                       Text{"the note that Mweeps", /*french*/"un message qui fait mwip",  /*spanish*/"un escrito mweep",       /*italian*/"la causa dei \"mweep\"", /*german*/"Deutsch"},
                       Text{"an SOS call",          /*french*/"un signal SOS",             /*spanish*/"una nota de socorro",    /*italian*/"un segnale SOS",         /*german*/"Deutsch"},
                       Text{"a fishy stationery",   /*french*/"un papier mouillé",         /*spanish*/"un mensaje de ayuda",    /*italian*/"carta bagnata",          /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a bottle", /*french*/"un flacon", /*spanish*/"una botella", /*italian*/"un'ampolla", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"Ruto's Letter", /*french*/"la lettre de Ruto", /*spanish*/"la carta de Ruto", /*italian*/"la lettera di Ruto", /*german*/"Deutsch"}
    );

    hintTable[ZELDAS_LULLABY] = HintText::Item({
                       //obscure text
                       Text{"a song of royal slumber", /*french*/"une chanson royale", /*spanish*/"la canción real",            /*italian*/"un legame con la famiglia reale", /*german*/"Deutsch"},
                       Text{"a triforce tune",         /*french*/"la musique sacrée",  /*spanish*/"la melodía de la trifuerza", /*italian*/"la prima melodia",                /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a regular song",                     /*french*/"une chanson normale",    /*spanish*/"una cancion normal",                /*italian*/"una canzone semplice",          /*german*/"Deutsch"},
                       Text{"something kept by the royal family", /*french*/"une chose qui paralyse", /*spanish*/"algo guardado por la familia real", /*italian*/"una cosa della famiglia reale", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"Zelda's Lullaby", /*french*/"la berceuse de Zelda", /*spanish*/"la Nana de Zelda", /*italian*/"la ninna nanna di Zelda", /*german*/"Deutsch"}
    );

    hintTable[EPONAS_SONG] = HintText::Item({
                       //obscure text
                       Text{"an equestrian etude", /*french*/"une hymne équestre",    /*spanish*/"una copla ecuestre", /*italian*/"un richiamo per cavalli", /*german*/"Deutsch"},
                       Text{"Malon's melody",      /*french*/"la mélodie des vaches", /*spanish*/"la sonata de Malon", /*italian*/"la melodia di Malon",     /*german*/"Deutsch"},
                       Text{"a ranch song",        /*french*/"le chant des champs",   /*spanish*/"un canto rupestre",  /*italian*/"il tema della fattoria",  /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a regular song", /*french*/"une chanson normale", /*spanish*/"una cancion normal", /*italian*/"una canzone semplice", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"Epona's Song", /*french*/"le chant d'Epona", /*spanish*/"la Canción de Epona", /*italian*/"la Canzone di Epona", /*german*/"Deutsch"}
    );

    hintTable[SARIAS_SONG] = HintText::Item({
                       //obscure text
                       Text{"a song of dancing Gorons", /*french*/"une chanson danceuse",    /*spanish*/"un pegadizo tono goron",     /*italian*/"un \"ritmo infuocato\"", /*german*/"Deutsch"},
                       Text{"Saria's phone number",     /*french*/"le téléphone d'une amie", /*spanish*/"una consulta de asistencia", /*italian*/"il numero di Saria",     /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a regular song",           /*french*/"une chanson normale", /*spanish*/"una cancion normal",   /*italian*/"una canzone semplice", /*german*/"Deutsch"},
                       Text{"something given by Saria", /*french*/"un cadeau de Saria",  /*spanish*/"un obsequio de Saria", /*italian*/"una cosa di Saria",    /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"Saria's Song", /*french*/"le chant de Saria", /*spanish*/"la Canción de Saria", /*italian*/"la Canzone di Saria", /*german*/"Deutsch"}
    );

    hintTable[SUNS_SONG] = HintText::Item({
                       //obscure text
                       Text{"Sunny Day",         /*french*/"Zénith",               /*spanish*/"un día soleado",            /*italian*/"il canto del gallo", /*german*/"Deutsch"},
                       Text{"the ReDead's bane", /*french*/"le fléau des Remorts", /*spanish*/"la destructora de Redeads", /*italian*/"veleno per Zombie",  /*german*/"Deutsch"},
                       Text{"the Gibdo's bane",  /*french*/"le fléau des Gibdo",   /*spanish*/"la destructora de Gibdos",  /*italian*/"veleno per Ghibdo",  /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a regular song",          /*french*/"une chanson normale",          /*spanish*/"una cancion normal",       /*italian*/"una canzone semplice",         /*german*/"Deutsch"},
                       Text{"something that can stun", /*french*/"une chose qui peut paralyser", /*spanish*/"algo que pueda paralizar", /*italian*/"qualcosa che può paralizzare", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Sun's Song", /*french*/"le chant du soleil", /*spanish*/"la Canción del Sol", /*italian*/"il Canto del sole", /*german*/"Deutsch"}
    );

    hintTable[SONG_OF_TIME] = HintText::Item({
                       //obscure text
                       Text{"a song 7 years long", /*french*/"le flot du temps",  /*spanish*/"la setenada canción", /*italian*/"una melodia settenaria", /*german*/"Deutsch"},
                       Text{"the tune of ages",    /*french*/"le Chant des Âges", /*spanish*/"la melodía eónica",   /*italian*/"le Note del Tempo",      /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a regular song", /*french*/"une chanson normale", /*spanish*/"una cancion normal", /*italian*/"una canzone semplice", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Song of Time", /*french*/"le chant du temps", /*spanish*/"la Canción del tiempo", /*italian*/"la Canzone del tempo", /*german*/"Deutsch"}
    );

    hintTable[SONG_OF_STORMS] = HintText::Item({
                       //obscure text
                       Text{"Rain Dance",            /*french*/"Danse Pluie",               /*spanish*/"la danza de la lluvia",  /*italian*/"la danza della pioggia", /*german*/"Deutsch"},
                       Text{"a thunderstorm tune",   /*french*/"une hymne foudroyante",     /*spanish*/"una sonata tormentosa",  /*italian*/"il suono di un tuono",   /*german*/"Deutsch"},
                       Text{"windmill acceleration", /*french*/"l'accélérateur de moulins", /*spanish*/"el arranque de molinos", /*italian*/"propulsione per mulini", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a regular song", /*french*/"une chanson normale", /*spanish*/"una cancion normal", /*italian*/"una canzone semplice", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Song of Storms", /*french*/"le chant des tempêtes", /*spanish*/"la Canción de la Tormenta", /*italian*/"la Canzone della tempesta", /*german*/"Deutsch"}
    );

    hintTable[MINUET_OF_FOREST] = HintText::Item({
                       //obscure text
                       Text{"the song of tall trees", /*french*/"le bruit des arbres", /*spanish*/"la canción de las copas", /*italian*/"un monologo sui ricordi",        /*german*/"Deutsch"},
                       Text{"an arboreal anthem",     /*french*/"l'hymne sylvestre",   /*spanish*/"el himno forestal",       /*italian*/"un'aria arborea",                /*german*/"Deutsch"},
                       Text{"a green spark trail",    /*french*/"une comète verte",    /*spanish*/"el sendero esmeralda",    /*italian*/"una scia di scintille smeraldo", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a warp song", /*french*/"une chanson de téléportation", /*spanish*/"una canción de teletransportación", /*italian*/"una melodia complessa", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Minuet of Forest", /*french*/"le menuet de la forêt", /*spanish*/"el Minueto del bosque", /*italian*/"il Minuetto della foresta", /*german*/"Deutsch"}
    );

    hintTable[BOLERO_OF_FIRE] = HintText::Item({
                       //obscure text
                       Text{"a song of lethal lava", /*french*/"une musique enflammée", /*spanish*/"la canción de la lava", /*italian*/"un monologo sull'amicizia",       /*german*/"Deutsch"},
                       Text{"a red spark trail",     /*french*/"une comète rouge",      /*spanish*/"el sendero rubí",       /*italian*/"una scia di scintille scarlatte", /*german*/"Deutsch"},
                       Text{"a volcanic verse",      /*french*/"le souffle du volcan",  /*spanish*/"el verso volcánico",    /*italian*/"il verso vulcanico",              /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a warp song", /*french*/"une chanson de téléportation", /*spanish*/"una canción de teletransportación", /*italian*/"una melodia complessa", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Bolero of Fire", /*french*/"le boléro du feu", /*spanish*/"el Bolero del fuego", /*italian*/"il Bolero del fuoco", /*german*/"Deutsch"}
    );

    hintTable[SERENADE_OF_WATER] = HintText::Item({
                       //obscure text
                       Text{"a song of a damp ditch", /*french*/"le calme de l'eau", /*spanish*/"la canción del estanque", /*italian*/"un monologo sul diventare adulti", /*german*/"Deutsch"},
                       Text{"a blue spark trail",     /*french*/"une comète bleue",  /*spanish*/"el sendero zafiro",       /*italian*/"una scia di scintille celesti",    /*german*/"Deutsch"},
                       Text{"the lake's lyric",       /*french*/"la voix du lac",    /*spanish*/"la letra del lago",       /*italian*/"la lirica del lago",               /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a warp song", /*french*/"une chanson de téléportation", /*spanish*/"una canción de teletransportación", /*italian*/"una melodia complessa", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Serenade of Water", /*french*/"la sérénade de l'eau", /*spanish*/"la Serenata del agua", /*italian*/"la Serenata dell'acqua", /*german*/"Deutsch"}
    );

    hintTable[REQUIEM_OF_SPIRIT] = HintText::Item({
                       //obscure text
                       Text{"a song of sandy statues", /*french*/"la mélodie d'une grande statue", /*spanish*/"la canción de la gran estatua", /*italian*/"un monologo sul viaggio nel tempo", /*german*/"Deutsch"},
                       Text{"an orange spark trail",   /*french*/"une comète orange",              /*spanish*/"el sendero ámbar",              /*italian*/"una scia di scintille ambrate",     /*german*/"Deutsch"},
                       Text{"the desert ditty",        /*french*/"le vent du désert",              /*spanish*/"la estrofa del desierto",       /*italian*/"un duetto desertico",               /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a warp song", /*french*/"une chanson de téléportation", /*spanish*/"una canción de teletransportación", /*italian*/"una melodia complessa", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Requiem of Spirit", /*french*/"le requiem des esprits", /*spanish*/"el Réquiem del espíritu", /*italian*/"il Requiem dello spirito", /*german*/"Deutsch"}
    );

    hintTable[NOCTURNE_OF_SHADOW] = HintText::Item({
                       //obscure text
                       Text{"a song of spooky spirits", /*french*/"une hymne de chair de poule", /*spanish*/"la canción de los espectros", /*italian*/"un monologo sull'oscurità di Calbarico", /*german*/"Deutsch"},
                       Text{"a graveyard boogie",       /*french*/"un boogie de fantômes",       /*spanish*/"una honra fúnebre",           /*italian*/"una melodia non diurna",                 /*german*/"Deutsch"},
                       Text{"a haunted hymn",           /*french*/"une chanson lugubre",         /*spanish*/"una estrofa encantada",       /*italian*/"la sinfonia dei sepolcri",               /*german*/"Deutsch"},
                       Text{"a purple spark trail",     /*french*/"une comète mauve",            /*spanish*/"el sendero malva",            /*italian*/"una scia di scintille lavanda",          /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a warp song", /*french*/"une chanson de téléportation", /*spanish*/"una canción de teletransportación", /*italian*/"una melodia complessa", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Nocturne of Shadow", /*french*/"le nocturne de l'ombre", /*spanish*/"el Nocturno de la sombra", /*italian*/"il Notturno delle ombre", /*german*/"Deutsch"}
    );

    hintTable[PRELUDE_OF_LIGHT] = HintText::Item({
                       //obscure text
                       Text{"a luminous prologue melody", /*french*/"une matine illuminée",   /*spanish*/"la melodía refulgente",      /*italian*/"un monologo sulle sfide future", /*german*/"Deutsch"},
                       Text{"a yellow spark trail",       /*french*/"une comète jaune",       /*spanish*/"el sendero resplandeciente", /*italian*/"una scia di scintille dorate",   /*german*/"Deutsch"},
                       Text{"the temple traveler",        /*french*/"un chant de sanctuaire", /*spanish*/"la ruta del templo",         /*italian*/"un viaggio nel tempio",          /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a warp song", /*french*/"une chanson de téléportation", /*spanish*/"una canción de teletransportación", /*italian*/"una melodia complessa", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Prelude of Light", /*french*/"le prélude de la lumière", /*spanish*/"el Preludio de la luz", /*italian*/"il Preludio della luce", /*german*/"Deutsch"}
    );
    hintTable[DEKU_TREE_MAP] = HintText::Item({
                        //obscure text
                        Text{"a mossy atlas",         /*french*/"un atlas boisé", /*spanish*/"un atlas musgoso",     /*italian*/"una pianta muschiosa",      /*german*/"Deutsch"},
                        Text{"some mossy blueprints", /*french*/"un plan boisé",  /*spanish*/"unos planos musgosos", /*italian*/"una planimetria muschiosa", /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a dungeon map", /*french*/"une carte", /*spanish*/"un mapa", /*italian*/"una mappa", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"the Deku Tree Map", /*french*/"la carte de l'arbre Mojo", /*spanish*/"el mapa del Gran Árbol Deku", /*italian*/"la mappa del Grande Albero Deku", /*german*/"Deutsch"}
     );
    hintTable[DODONGOS_CAVERN_MAP] = HintText::Item({
                        //obscure text
                        Text{"a rocky atlas",         /*french*/"un atlas rocheux",  /*spanish*/"un atlas rocoso",     /*italian*/"una pianta rocciosa",      /*german*/"Deutsch"},
                        Text{"some rocky blueprints", /*french*/"un plan rocheux",   /*spanish*/"unos planos rocosos", /*italian*/"una planimetria rocciosa", /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a dungeon map", /*french*/"une carte", /*spanish*/"un mapa", /*italian*/"una mappa", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"the Dodongo's Cavern Map", /*french*/"la carte de la caverne Dodongo", /*spanish*/"el mapa de la Cueva de los Dodongos", /*italian*/"la mappa della caverna dei Dodongo", /*german*/"Deutsch"}
     );
    hintTable[JABU_JABUS_BELLY_MAP] = HintText::Item({
                        //obscure text
                        Text{"a fishy atlas",         /*french*/"un atlas digéré", /*spanish*/"un atlas digesto",     /*italian*/"una pianta anatomica",      /*german*/"Deutsch"},
                        Text{"some fishy blueprints", /*french*/"un plan digéré",  /*spanish*/"unos planos digestos", /*italian*/"una planimetria anatomica", /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a dungeon map", /*french*/"une carte", /*spanish*/"un mapa", /*italian*/"una mappa", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"the Jabu-Jabu's Belly Map", /*french*/"la carte de Jabu-Jabu", /*spanish*/"el mapa de la Tripa de Jabu-Jabu", /*italian*/"la mappa della pancia di Jabu Jabu", /*german*/"Deutsch"}
     );
    hintTable[FOREST_TEMPLE_MAP] = HintText::Item({
                        //obscure text
                        Text{"a sylvan atlas",         /*french*/"un atlas sylvestre", /*spanish*/"un atlas enselvado",     /*italian*/"una pianta silvestre",      /*german*/"Deutsch"},
                        Text{"some sylvan blueprints", /*french*/"un plan sylvestre",  /*spanish*/"unos planos enselvados", /*italian*/"una planimetria silvestre", /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a dungeon map", /*french*/"une carte", /*spanish*/"un mapa", /*italian*/"una mappa", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"the Forest Temple Map", /*french*/"la carte du temple de la forêt", /*spanish*/"el mapa del Templo del Bosque", /*italian*/"la mappa del Santuario della Foresta", /*german*/"Deutsch"}
     );
    hintTable[FIRE_TEMPLE_MAP] = HintText::Item({
                        //obscure text
                        Text{"a molten atlas",         /*french*/"un atlas fondu", /*spanish*/"un atlas fundido",     /*italian*/"una pianta bollente",      /*german*/"Deutsch"},
                        Text{"some molten blueprints", /*french*/"un plan fondu",  /*spanish*/"unos planos fundidos", /*italian*/"una planimetria bollente", /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a dungeon map", /*french*/"une carte", /*spanish*/"un mapa", /*italian*/"una mappa", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"the Fire Temple Map", /*french*/"la carte du temple du feu", /*spanish*/"el mapa del Templo del Fuego", /*italian*/"la mappa del Santuario del Fuoco", /*german*/"Deutsch"}
     );
    hintTable[WATER_TEMPLE_MAP] = HintText::Item({
                        //obscure text
                        Text{"a wet atlas",         /*french*/"un atlas humide", /*spanish*/"un atlas mojado",     /*italian*/"una pianta idraulica",      /*german*/"Deutsch"},
                        Text{"some wet blueprints", /*french*/"un plan humide",  /*spanish*/"unos planos mojados", /*italian*/"una planimetria idraulica", /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a dungeon map", /*french*/"une carte", /*spanish*/"un mapa", /*italian*/"una mappa", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"the Water Temple Map", /*french*/"la carte du temple de l'eau", /*spanish*/"el mapa del Templo del Agua", /*italian*/"la mappa del Santuario dell'Acqua", /*german*/"Deutsch"}
     );
    hintTable[SPIRIT_TEMPLE_MAP] = HintText::Item({
                        //obscure text
                        Text{"a sandy atlas",         /*french*/"un atlas sableux", /*spanish*/"un atlas arenoso",     /*italian*/"una pianta sabbiosa",      /*german*/"Deutsch"},
                        Text{"some sandy blueprints", /*french*/"un plan sableux",  /*spanish*/"unos planos arenosos", /*italian*/"una planimetria sabbiosa", /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a dungeon map", /*french*/"une carte", /*spanish*/"un mapa", /*italian*/"una mappa", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"the Spirit Temple Map", /*french*/"la carte du temple de l'esprit", /*spanish*/"el mapa del Templo del Espíritu", /*italian*/"la mappa del Santuario dello Spirito", /*german*/"Deutsch"}
     );
    hintTable[SHADOW_TEMPLE_MAP] = HintText::Item({
                        //obscure text
                        Text{"a creepy atlas",         /*french*/"un atlas sinistre", /*spanish*/"un atlas siniestra",     /*italian*/"una pianta patibolare",      /*german*/"Deutsch"},
                        Text{"some creepy blueprints", /*french*/"un plan sinistre",  /*spanish*/"unos planos siniestras", /*italian*/"una planimetria patibolare", /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a dungeon map", /*french*/"une carte", /*spanish*/"un mapa", /*italian*/"una mappa", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"the Shadow Temple Map", /*french*/"la carte du temple de l'ombre", /*spanish*/"el mapa del Templo de las Sombras", /*italian*/"la mappa del Santuario dell'Ombra", /*german*/"Deutsch"}
     );
    hintTable[BOTTOM_OF_THE_WELL_MAP] = HintText::Item({
                        //obscure text
                        Text{"a moldy atlas",         /*french*/"un atlas moisi", /*spanish*/"un atlas mohoso",     /*italian*/"una pianta ammuffita",      /*german*/"Deutsch"},
                        Text{"some moldy blueprints", /*french*/"un plan moisi",  /*spanish*/"unos planos mohosos", /*italian*/"una planimetria ammuffita", /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a dungeon map", /*french*/"une carte", /*spanish*/"un mapa", /*italian*/"una mappa", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"the Bottom of the Well Map", /*french*/"la carte du fond du puits", /*spanish*/"el mapa del Fondo del pozo", /*italian*/"la mappa del fondo del pozzo", /*german*/"Deutsch"}
     );
    hintTable[ICE_CAVERN_MAP] = HintText::Item({
                        //obscure text
                        Text{"a polar atlas",         /*french*/"un atlas polaire", /*spanish*/"un atlas polar",     /*italian*/"una pianta artica",      /*german*/"Deutsch"},
                        Text{"some polar blueprints", /*french*/"un plan polaire",  /*spanish*/"unos planos polars", /*italian*/"una planimetria artica", /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a dungeon map", /*french*/"une carte", /*spanish*/"un mapa", /*italian*/"una mappa", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"the Ice Cavern Map", /*french*/"la carte de la caverne polaire", /*spanish*/"el mapa de la Caverna de hielo", /*italian*/"la mappa della caverna di ghiaccio", /*german*/"Deutsch"}
     );
    hintTable[DEKU_TREE_COMPASS] = HintText::Item({
                        //obscure text
                        Text{"a mossy treasure tracker", /*french*/"un cherche-trésor boisé", /*spanish*/"un zahorí musgoso", /*italian*/"una sonda muschiosa",  /*german*/"Deutsch"},
                        Text{"a mossy magnetic needle",  /*french*/"une aimant boisée",       /*spanish*/"un imán musgoso",   /*italian*/"un magnete muschioso", /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a compass", /*french*/"une boussole", /*spanish*/"una brújula", /*italian*/"una bussola", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"the Deku Tree Compass", /*french*/"la boussole de l'arbre Mojo", /*spanish*/"la brújula del Gran Árbol Deku", /*italian*/"la bussola del Grande Albero Deku", /*german*/"Deutsch"}
     );
    hintTable[DODONGOS_CAVERN_COMPASS] = HintText::Item({
                        //obscure text
                        Text{"a rocky treasure tracker", /*french*/"un cherche-trésor rocheux", /*spanish*/"un zahorí rocoso", /*italian*/"una sonda rocciosa",  /*german*/"Deutsch"},
                        Text{"a rocky magnetic needle",  /*french*/"une aimant rocheux",        /*spanish*/"un imán rocoso",   /*italian*/"un magnete roccioso", /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a compass", /*french*/"une boussole", /*spanish*/"una brújula", /*italian*/"una bussola", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"the Dodongo's Cavern Compass", /*french*/"la boussole de la caverne Dodongo", /*spanish*/"la brújula de la Cueva de los Dodongos", /*italian*/"la bussola della caverna dei Dodongo", /*german*/"Deutsch"}
     );
    hintTable[JABU_JABUS_BELLY_COMPASS] = HintText::Item({
                        //obscure text
                        Text{"a fishy treasure tracker", /*french*/"un cherche-trésor digéré", /*spanish*/"un zahorí digesto", /*italian*/"una sonda anatomica",  /*german*/"Deutsch"},
                        Text{"a fishy magnetic needle",  /*french*/"une aimant digéré",        /*spanish*/"un imán digesto",   /*italian*/"un magnete anatomico", /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a compass", /*french*/"une boussole", /*spanish*/"una brújula", /*italian*/"una bussola", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"the Jabu-Jabu's Belly Compass", /*french*/"la boussole de Jabu-Jabu", /*spanish*/"la brújula de la Tripa de Jabu-Jabu", /*italian*/"la bussola della pancia di Jabu Jabu", /*german*/"Deutsch"}
     );
    hintTable[FOREST_TEMPLE_COMPASS] = HintText::Item({
                        //obscure text
                        Text{"a sylvan treasure tracker", /*french*/"un cherche-trésor sylvestre", /*spanish*/"un zahorí enselvado", /*italian*/"una sonda silvestre",  /*german*/"Deutsch"},
                        Text{"a sylvan magnetic needle",  /*french*/"une aimant sylvestre",        /*spanish*/"un imán enselvado",   /*italian*/"un magnete silvestre", /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a compass", /*french*/"une boussole", /*spanish*/"una brújula", /*italian*/"una bussola", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"the Forest Temple Compass", /*french*/"la boussole du temple de la forêt", /*spanish*/"la brújula del Templo del Bosque", /*italian*/"la bussola del Santuario della Foresta", /*german*/"Deutsch"}
     );
    hintTable[FIRE_TEMPLE_COMPASS] = HintText::Item({
                        //obscure text
                        Text{"a molten treasure tracker", /*french*/"un cherche-trésor fondu", /*spanish*/"un zahorí fundido", /*italian*/"una sonda bollente",  /*german*/"Deutsch"},
                        Text{"a molten magnetic needle",  /*french*/"une aimant fondu",        /*spanish*/"un imán fundido",   /*italian*/"un magnete bollente", /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a compass", /*french*/"une boussole", /*spanish*/"una brújula", /*italian*/"una bussola", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"the Fire Temple Compass", /*french*/"la boussole du temple du feu", /*spanish*/"la brújula del Templo del Fuego", /*italian*/"la bussola del Santuario del Fuoco", /*german*/"Deutsch"}
     );
    hintTable[WATER_TEMPLE_COMPASS] = HintText::Item({
                        //obscure text
                        Text{"a wet treasure tracker", /*french*/"un cherche-trésor humide", /*spanish*/"un zahorí mojado", /*italian*/"una sonda idraulica",  /*german*/"Deutsch"},
                        Text{"a wet magnetic needle",  /*french*/"une aimant humide",        /*spanish*/"un imán mojado",   /*italian*/"un magnete idraulico", /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a compass", /*french*/"une boussole", /*spanish*/"una brújula", /*italian*/"una bussola", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"the Water Temple Compass", /*french*/"la boussole du temple de l'eau", /*spanish*/"la brújula del Templo del Agua", /*italian*/"la bussola del Santuario dell'Acqua", /*german*/"Deutsch"}
     );
    hintTable[SPIRIT_TEMPLE_COMPASS] = HintText::Item({
                        //obscure text
                        Text{"a sandy treasure tracker", /*french*/"un cherche-trésor sableux", /*spanish*/"un zahorí arenoso", /*italian*/"una sonda sabbiosa",  /*german*/"Deutsch"},
                        Text{"a sandy magnetic needle",  /*french*/"une aimant sableux",        /*spanish*/"un imán arenoso",   /*italian*/"un magnete sabbioso", /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a compass", /*french*/"une boussole", /*spanish*/"una brújula", /*italian*/"una bussola", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"the Spirit Temple Compass", /*french*/"la boussole du temple de l'esprit", /*spanish*/"la brújula del Templo del Espíritu", /*italian*/"la bussola del Santuario dello Spirito", /*german*/"Deutsch"}
     );
    hintTable[SHADOW_TEMPLE_COMPASS] = HintText::Item({
                        //obscure text
                        Text{"a creepy treasure tracker", /*french*/"un cherche-trésor sinistre", /*spanish*/"un zahorí siniestra", /*italian*/"una sonda patibolare",  /*german*/"Deutsch"},
                        Text{"a creepy magnetic needle",  /*french*/"une aimant sinistre",        /*spanish*/"un imán siniestra",   /*italian*/"un magnete patibolare", /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a compass", /*french*/"une boussole", /*spanish*/"una brújula", /*italian*/"una bussola", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"the Shadow Temple Compass", /*french*/"la boussole du temple de l'ombre", /*spanish*/"la brújula del Templo de las Sombras", /*italian*/"la bussola del Santuario dell'Ombra", /*german*/"Deutsch"}
     );
    hintTable[BOTTOM_OF_THE_WELL_COMPASS] = HintText::Item({
                        //obscure text
                        Text{"a dank treasure tracker", /*french*/"un cherche-trésor moisi",  /*spanish*/"un zahorí mohoso", /*italian*/"una sonda ammuffita",  /*german*/"Deutsch"},
                        Text{"a dank magnetic needle",  /*french*/"une aimant moisi",         /*spanish*/"un imán mohoso",   /*italian*/"un magnete ammuffito", /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a compass", /*french*/"une boussole", /*spanish*/"una brújula", /*italian*/"una bussola", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"the Bottom of the Well Compass", /*french*/"la boussole du fond du puits", /*spanish*/"la brújula del Fondo del pozo", /*italian*/"la bussola del fondo del pozzo", /*german*/"Deutsch"}
     );
    hintTable[ICE_CAVERN_COMPASS] = HintText::Item({
                        //obscure text
                        Text{"a polar treasure tracker", /*french*/"un cherche-trésor polaire", /*spanish*/"un zahorí polar", /*italian*/"una sonda artica",  /*german*/"Deutsch"},
                        Text{"a polar magnetic needle",  /*french*/"une aimant polaire",        /*spanish*/"un imán polar",   /*italian*/"un magnete artico", /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a compass", /*french*/"une boussole", /*spanish*/"una brújula", /*italian*/"una bussola", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"the Ice Cavern Compass", /*french*/"la boussole de la caverne polaire", /*spanish*/"la brújula de la Caverna de hielo", /*italian*/"la bussola della caverna di ghiaccio", /*german*/"Deutsch"}
     );
    hintTable[FOREST_TEMPLE_BOSS_KEY] = HintText::Item({
                        //obscure text
                        Text{"a sylvan master of unlocking",   /*french*/"un anti-grosse porte sylvestre", /*spanish*/"la clave enselvada de un jefe", /*italian*/"lo sbloccatore del traguardo silvestre", /*german*/"Deutsch"},
                        Text{"a sylvan dungeon's master pass", /*french*/"une clé maléfique sylvestree",   /*spanish*/"el pase maestro enselvado",     /*italian*/"un permesso silvestre del capo",         /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a boss key", /*french*/"une clé d'or", /*spanish*/"una gran llave", /*italian*/"una grande chiave", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"the Forest Temple Boss Key", /*french*/"la clé d'or du temple de la forêt", /*spanish*/"la gran llave del Templo del Bosque", /*italian*/"la grande chiave del Santuario della Foresta", /*german*/"Deutsch"}
     );
    hintTable[FIRE_TEMPLE_BOSS_KEY] = HintText::Item({
                        //obscure text
                        Text{"a molten master of unlocking",   /*french*/"un anti-grosse porte fondu", /*spanish*/"la clave fundido de un jefe", /*italian*/"lo sbloccatore del traguardo bollente", /*german*/"Deutsch"},
                        Text{"a molten dungeon's master pass", /*french*/"une clé maléfique fondu",    /*spanish*/"el pase maestro fundido",     /*italian*/"un permesso bollente del capo",         /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a boss key", /*french*/"une clé d'or", /*spanish*/"una gran llave", /*italian*/"una grande chiave", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"the Fire Temple Boss Key", /*french*/"la clé d'or du temple du feu", /*spanish*/"la gran llave del Templo del Fuego", /*italian*/"la grande chiave del Santuario del Fuoco", /*german*/"Deutsch"}
     );
    hintTable[WATER_TEMPLE_BOSS_KEY] = HintText::Item({
                        //obscure text
                        Text{"a wet master of unlocking",   /*french*/"un anti-grosse porte humide", /*spanish*/"la clave mojado de un jefe", /*italian*/"lo sbloccatore del traguardo idraulico", /*german*/"Deutsch"},
                        Text{"a wet dungeon's master pass", /*french*/"une clé maléfique humide",    /*spanish*/"el pase maestro mojado",     /*italian*/"un permesso idraulico del capo",         /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a boss key", /*french*/"une clé d'or", /*spanish*/"una gran llave", /*italian*/"una grande chiave", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"the Water Temple Boss Key", /*french*/"la clé d'or du temple de l'eau", /*spanish*/"la gran llave del Templo del Agua", /*italian*/"la grande chiave del Santuario dell'Acqua", /*german*/"Deutsch"}
     );
    hintTable[SPIRIT_TEMPLE_BOSS_KEY] = HintText::Item({
                        //obscure text
                        Text{"a sandy master of unlocking",   /*french*/"un anti-grosse porte sableux", /*spanish*/"la clave arenoso de un jefe", /*italian*/"lo sbloccatore del traguardo sabbioso", /*german*/"Deutsch"},
                        Text{"a sandy dungeon's master pass", /*french*/"une clé maléfique sableux",    /*spanish*/"el pase maestro arenoso",     /*italian*/"un permesso sabbioso del capo",         /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a boss key", /*french*/"une clé d'or", /*spanish*/"una gran llave", /*italian*/"una grande chiave", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"the Spirit Temple Boss Key", /*french*/"la clé d'or du temple de l'esprit", /*spanish*/"la gran llave del Templo del Espíritu", /*italian*/"la grande chiave del Santuario dello Spirito", /*german*/"Deutsch"}
     );
    hintTable[SHADOW_TEMPLE_BOSS_KEY] = HintText::Item({
                        //obscure text
                        Text{"a creepy master of unlocking",   /*french*/"un anti-grosse porte sinistre", /*spanish*/"la clave siniestra de un jefe", /*italian*/"lo sbloccatore del traguardo patibolare", /*german*/"Deutsch"},
                        Text{"a creepy dungeon's master pass", /*french*/"une clé maléfique sinistre",    /*spanish*/"el pase maestro siniestra",     /*italian*/"un permesso patibolare del capo",         /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a boss key", /*french*/"une clé d'or", /*spanish*/"una gran llave", /*italian*/"una grande chiave", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"the Shadow Temple Boss Key", /*french*/"la clé d'or du temple de l'ombre", /*spanish*/"la gran llave del Templo de las Sombras", /*italian*/"la grande chiave del Santuario dell'Ombra", /*german*/"Deutsch"}
     );
    hintTable[GANONS_CASTLE_BOSS_KEY] = HintText::Item({
                        //obscure text
                        Text{"a final master of unlocking",   /*french*/"un anti-grosse porte final", /*spanish*/"la clave final de un jefe", /*italian*/"lo sbloccatore del traguardo finale", /*german*/"Deutsch"},
                        Text{"a final dungeon's master pass", /*french*/"une clé maléfique final",    /*spanish*/"el pase maestro final",     /*italian*/"un permesso finale del capo",         /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a boss key", /*french*/"une clé d'or", /*spanish*/"una gran llave", /*italian*/"una grande chiave", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"the Ganon's Castle Boss Key", /*french*/"la clé d'or du château de Ganon", /*spanish*/"la gran llave del Castillo de Ganon", /*italian*/"la grande chiave del castello di Ganon", /*german*/"Deutsch"}
     );
    hintTable[FOREST_TEMPLE_SMALL_KEY] = HintText::Item({
                        //obscure text
                        Text{"a sylvan tool for unlocking", /*french*/"un anti-porte sylvestre",            /*spanish*/"una clave de una entrada enselvada",     /*italian*/"uno sbloccatore silvestre",          /*german*/"Deutsch"},
                        Text{"a sylvan dungeon pass",       /*french*/"le rêve sylvestre d'un prisonnier",  /*spanish*/"un pase de una mazmorra enselvada",      /*italian*/"un permesso silvestre",              /*german*/"Deutsch"},
                        Text{"a sylvan lock remover",       /*french*/"un efface-serrure sylvestre",        /*spanish*/"un destructor de cerraduras enselvadas", /*italian*/"un dissolutore di catene silvestri", /*german*/"Deutsch"},
                        Text{"a sylvan lockpick",           /*french*/"un crochet à porte sylvestre",       /*spanish*/"una apertura portentosa enselvada",      /*italian*/"un grimaldello silvestre",           /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a small key", /*french*/"une petite clé", /*spanish*/"una llave pequeña", /*italian*/"una piccola chiave", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"a Forest Temple Small Key", /*french*/"une petite clé du temple de la forêt", /*spanish*/"una llave pequeña del Templo del Bosque", /*italian*/"una piccola chiave del Santuario della Foresta", /*german*/"Deutsch"}
     );
    hintTable[FIRE_TEMPLE_SMALL_KEY] = HintText::Item({
                        //obscure text
                        Text{"a molten tool for unlocking", /*french*/"un anti-porte fondu",            /*spanish*/"una clave de una entrada fundida",     /*italian*/"uno sbloccatore bollente",          /*german*/"Deutsch"},
                        Text{"a molten dungeon pass",       /*french*/"le rêve fondu d'un prisonnier",  /*spanish*/"un pase de una mazmorra fundida",      /*italian*/"un permesso bollente",              /*german*/"Deutsch"},
                        Text{"a molten lock remover",       /*french*/"un efface-serrure fondu",        /*spanish*/"un destructor de cerraduras fundidas", /*italian*/"un dissolutore di catene bollenti", /*german*/"Deutsch"},
                        Text{"a molten lockpick",           /*french*/"un crochet à porte fondu",       /*spanish*/"una apertura portentosa fundida",      /*italian*/"un grimaldello bollente",           /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a small key", /*french*/"une petite clé", /*spanish*/"una llave pequeña", /*italian*/"una piccola chiave", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"a Fire Temple Small Key", /*french*/"une petite clé du temple du feu", /*spanish*/"una llave pequeña del Templo del Fuego", /*italian*/"una piccola chiave del Santuario del Fuoco", /*german*/"Deutsch"}
     );
    hintTable[WATER_TEMPLE_SMALL_KEY] = HintText::Item({
                        //obscure text
                        Text{"a wet tool for unlocking", /*french*/"un anti-porte humide",            /*spanish*/"una clave de una entrada mojada",     /*italian*/"uno sbloccatore idraulico",           /*german*/"Deutsch"},
                        Text{"a wet dungeon pass",       /*french*/"le rêve humide d'un prisonnier",  /*spanish*/"un pase de una mazmorra mojada",      /*italian*/"un permesso idraulico",               /*german*/"Deutsch"},
                        Text{"a wet lock remover",       /*french*/"un efface-serrure humide",        /*spanish*/"un destructor de cerraduras mojadas", /*italian*/"un dissolutore di catene idrauliche", /*german*/"Deutsch"},
                        Text{"a wet lockpick",           /*french*/"un crochet à porte humide",       /*spanish*/"una apertura portentosa mojada",      /*italian*/"un grimaldello idraulico",            /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a small key", /*french*/"une petite clé", /*spanish*/"una llave pequeña", /*italian*/"una piccola chiave", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"a Water Temple Small Key", /*french*/"une petite clé du temple de l'eau", /*spanish*/"una llave pequeña del Templo del Agua", /*italian*/"una piccola chiave del Santuario dell'Acqua", /*german*/"Deutsch"}
     );
    hintTable[SPIRIT_TEMPLE_SMALL_KEY] = HintText::Item({
                        //obscure text
                        Text{"a sandy tool for unlocking", /*french*/"un anti-porte sableux",            /*spanish*/"una clave de una entrada arenosa",     /*italian*/"uno sbloccatore sabbioso",          /*german*/"Deutsch"},
                        Text{"a sandy dungeon pass",       /*french*/"le rêve sableux d'un prisonnier",  /*spanish*/"un pase de una mazmorra arenosa",      /*italian*/"un permesso sabbioso",              /*german*/"Deutsch"},
                        Text{"a sandy lock remover",       /*french*/"un efface-serrure sableux",        /*spanish*/"un destructor de cerraduras arenosas", /*italian*/"un dissolutore di catene sabbiose", /*german*/"Deutsch"},
                        Text{"a sandy lockpick",           /*french*/"un crochet à porte sableux",       /*spanish*/"una apertura portentosa arenosa",      /*italian*/"un grimaldello sabbioso",           /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a small key", /*french*/"une petite clé", /*spanish*/"una llave pequeña", /*italian*/"una piccola chiave", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"a Spirit Temple Small Key", /*french*/"une petite clé du temple de l'esprit", /*spanish*/"una llave pequeña del Templo del Espíritu", /*italian*/"una piccola chiave del Santuario dello Spirito", /*german*/"Deutsch"}
     );
    hintTable[SHADOW_TEMPLE_SMALL_KEY] = HintText::Item({
                        //obscure text
                        Text{"a creepy tool for unlocking", /*french*/"un anti-porte sinistre",            /*spanish*/"una clave de una entrada siniestra",     /*italian*/"uno sbloccatore patibolare",          /*german*/"Deutsch"},
                        Text{"a creepy dungeon pass",       /*french*/"le rêve sinistre d'un prisonnier",  /*spanish*/"un pase de una mazmorra siniestra",      /*italian*/"un permesso patibolare",              /*german*/"Deutsch"},
                        Text{"a creepy lock remover",       /*french*/"un efface-serrure sinistre",        /*spanish*/"un destructor de cerraduras siniestras", /*italian*/"un dissolutore di catene patibolari", /*german*/"Deutsch"},
                        Text{"a creepy lockpick",           /*french*/"un crochet à porte sinistre",       /*spanish*/"una apertura portentosa siniestra",      /*italian*/"un grimaldello patibolare",           /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a small key", /*french*/"une petite clé", /*spanish*/"una llave pequeña", /*italian*/"una piccola chiave", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"a Shadow Temple Small Key", /*french*/"une petite clé du temple de l'ombre", /*spanish*/"una llave pequeña del Templo de las Sombras", /*italian*/"una piccola chiave del Santuario dell'Ombra", /*german*/"Deutsch"}
     );
    hintTable[GERUDO_TRAINING_GROUNDS_SMALL_KEY] = HintText::Item({
                        //obscure text
                        Text{"a labyrinthian tool for unlocking", /*french*/"un anti-porte labyrinthique",            /*spanish*/"una clave de una entrada laberíntica",     /*italian*/"uno sbloccatore labirintico",           /*german*/"Deutsch"},
                        Text{"a labyrinthian dungeon pass",       /*french*/"le rêve labyrinthique d'un prisonnier",  /*spanish*/"un pase de una mazmorra laberíntica",      /*italian*/"un permesso labirintico",               /*german*/"Deutsch"},
                        Text{"a labyrinthian lock remover",       /*french*/"un efface-serrure labyrinthique",        /*spanish*/"un destructor de cerraduras laberínticas", /*italian*/"un dissolutore di catene labirintiche", /*german*/"Deutsch"},
                        Text{"a labyrinthian lockpick",           /*french*/"un crochet à porte labyrinthique",       /*spanish*/"una apertura portentosa laberíntica",      /*italian*/"un grimaldello labirintico",            /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a small key", /*french*/"une petite clé", /*spanish*/"una llave pequeña", /*italian*/"una piccola chiave", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"a Gerudo Training Ground Small Key", /*french*/"une petite clé du gymnase Gerudo", /*spanish*/"una llave pequeña del Centro de Instrucción Gerudo", /*italian*/"una piccola chiave della zona di addestramento Gerudo", /*german*/"Deutsch"}
     );
    hintTable[GERUDO_FORTRESS_SMALL_KEY] = HintText::Item({
                        //obscure text
                        Text{"an imprisoned tool for unlocking", /*french*/"un anti-porte emprisonné",            /*spanish*/"una clave de una entrada encarcelada",     /*italian*/"uno sbloccatore per prigionieri",          /*german*/"Deutsch"},
                        Text{"an imprisoned dungeon pass",       /*french*/"le rêve emprisonné d'un prisonnier",  /*spanish*/"un pase de una mazmorra encarcelada",      /*italian*/"un permesso per prigionieri",              /*german*/"Deutsch"},
                        Text{"an imprisoned lock remover",       /*french*/"un efface-serrure emprisonné",        /*spanish*/"un destructor de cerraduras encarceladas", /*italian*/"un dissolutore di catene per prigionieri", /*german*/"Deutsch"},
                        Text{"an imprisoned lockpick",           /*french*/"un crochet à porte emprisonné",       /*spanish*/"una apertura portentosa encarcelada",      /*italian*/"un grimaldello per prigionieri",           /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a small key", /*french*/"une petite clé", /*spanish*/"una llave pequeña", /*italian*/"una piccola chiave", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"a Gerudo Fortress Small Key", /*french*/"une petite clé de la forteresse Gerudo", /*spanish*/"una llave pequeña de la Fortaleza Gerudo", /*italian*/"una piccola chiave della fortezza Gerudo", /*german*/"Deutsch"}
     );
    hintTable[BOTTOM_OF_THE_WELL_SMALL_KEY] = HintText::Item({
                        //obscure text
                        Text{"a moldy tool for unlocking", /*french*/"un anti-porte moisi",            /*spanish*/"una clave de una entrada mohosa",     /*italian*/"uno sbloccatore ammuffito",          /*german*/"Deutsch"},
                        Text{"a moldy dungeon pass",       /*french*/"le rêve moisi d'un prisonnier",  /*spanish*/"un pase de una mazmorra mohosa",      /*italian*/"un permesso ammuffito",              /*german*/"Deutsch"},
                        Text{"a moldy lock remover",       /*french*/"un efface-serrure moisi",        /*spanish*/"un destructor de cerraduras mohosas", /*italian*/"un dissolutore di catene ammuffite", /*german*/"Deutsch"},
                        Text{"a moldy lockpick",           /*french*/"un crochet à porte moisi",       /*spanish*/"una apertura portentosa mohosa",      /*italian*/"un grimaldello ammuffito",           /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a small key", /*french*/"une petite clé", /*spanish*/"una llave pequeña", /*italian*/"una piccola chiave", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"a Bottom of the Well Small Key", /*french*/"une petite clé du fond du puits", /*spanish*/"una llave pequeña del Fondo del pozo", /*italian*/"una piccola chiave del fondo del pozzo", /*german*/"Deutsch"}
     );
    hintTable[GANONS_CASTLE_SMALL_KEY] = HintText::Item({
                        //obscure text
                        Text{"a final tool for unlocking", /*french*/"un anti-porte final",            /*spanish*/"una clave de una entrada final",    /*italian*/"uno sbloccatore finale",          /*german*/"Deutsch"},
                        Text{"a final dungeon pass",       /*french*/"le rêve final d'un prisonnier",  /*spanish*/"un pase de una mazmorra final",     /*italian*/"un permesso finale",              /*german*/"Deutsch"},
                        Text{"a final lock remover",       /*french*/"un efface-serrure final",        /*spanish*/"un destructor de cerraduras final", /*italian*/"un dissolutore di catene finali", /*german*/"Deutsch"},
                        Text{"a final lockpick",           /*french*/"un crochet à porte final",       /*spanish*/"una apertura portentosa final",     /*italian*/"un grimaldello finale",           /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a small key", /*french*/"une petite clé", /*spanish*/"una llave pequeña", /*italian*/"una piccola chiave", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"a Ganon's Castle Small Key", /*french*/"une petite clé du château de Ganon", /*spanish*/"una llave pequeña del Castillo de Ganon", /*italian*/"una piccola chiave del castello di Ganon", /*german*/"Deutsch"}
     );
     hintTable[FOREST_TEMPLE_KEY_RING] = HintText::Item({
                        //obscure text
                        Text{"a sylvan toolbox for unlocking", /*french*/"des anti-portes sylvestres",            /*spanish*/"un conjunto silvestre de cerrajero",  /*italian*/"un inesauribile sbloccatore silvestre", /*german*/"Deutsch"},
                        Text{"a sylvan dungeon season pass",   /*french*/"les rêves sylvestres d'un prisonnier",  /*spanish*/"un pase vip de mazmorras silvestre",  /*italian*/"un passe-partout silvestre",            /*german*/"Deutsch"},
                        Text{"a sylvan jingling ring",         /*french*/"des efface-serrures sylvestres",        /*spanish*/"una cadena multiusos silvestre",      /*italian*/"un anello silvestre",                   /*german*/"Deutsch"},
                        Text{"a sylvan skeleton key",          /*french*/"des crochets à porte sylvestres",       /*spanish*/"un anillo silvestre contra cerrojos", /*italian*/"una chiave magica silvestre",           /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a key ring", /*french*/"un trousseau de clés", /*spanish*/"un llavero", /*italian*/"un mazzo di chiavi", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"a Forest Temple Key Ring", /*french*/"un trousseau de clés du temple de la forêt", /*spanish*/"un llavero del Templo del Bosque", /*italian*/"un mazzo di chiavi del Santuario della Foresta", /*german*/"Deutsch"}
     );
    hintTable[FIRE_TEMPLE_KEY_RING] = HintText::Item({
                        //obscure text
                        Text{"a molten toolbox for unlocking", /*french*/"des anti-portes fondus",            /*spanish*/"un conjunto fundido de cerrajero",  /*italian*/"un inesauribile sbloccatore bollente", /*german*/"Deutsch"},
                        Text{"a molten dungeon season pass",   /*french*/"les rêves fondus d'un prisonnier",  /*spanish*/"un pase vip de mazmorras fundido",  /*italian*/"un passe-partout bollente",            /*german*/"Deutsch"},
                        Text{"a molten jingling ring",         /*french*/"des efface-serrures fondus",        /*spanish*/"una cadena multiusos fundida",      /*italian*/"un anello bollente",                   /*german*/"Deutsch"},
                        Text{"a molten skeleton key",          /*french*/"des crochets à porte fondus",       /*spanish*/"un anillo fundido contra cerrojos", /*italian*/"una chiave magica bollente",           /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a key ring", /*french*/"un trousseau de clés", /*spanish*/"un llavero", /*italian*/"un mazzo di chiavi", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"a Fire Temple Key Ring", /*french*/"un trousseau de clés du temple du feu", /*spanish*/"un llavero del Templo del Fuego", /*italian*/"un mazzo di chiavi del Santuario del Fuoco", /*german*/"Deutsch"}
     );
    hintTable[WATER_TEMPLE_KEY_RING] = HintText::Item({
                        //obscure text
                        Text{"a wet toolbox for unlocking", /*french*/"des anti-portes humides",            /*spanish*/"un conjunto abisal de cerrajero",  /*italian*/"un inesauribile sbloccatore idraulico", /*german*/"Deutsch"},
                        Text{"a wet dungeon season pass",   /*french*/"les rêves humides d'un prisonnier",  /*spanish*/"un pase vip de mazmorras abisal",  /*italian*/"un passe-partout idraulico",            /*german*/"Deutsch"},
                        Text{"a wet jingling ring",         /*french*/"des efface-serrures humides",        /*spanish*/"una cadena multiusos abisal",      /*italian*/"un anello idraulico",                   /*german*/"Deutsch"},
                        Text{"a wet skeleton key",          /*french*/"des crochets à porte humides",       /*spanish*/"un anillo abisal contra cerrojos", /*italian*/"una chiave magica idraulica",           /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a key ring", /*french*/"un trousseau de clés", /*spanish*/"un llavero", /*italian*/"un mazzo di chiavi", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"a Water Temple Key Ring", /*french*/"un trousseau de clés du temple de l'eau", /*spanish*/"un llavero del Templo del Agua", /*italian*/"un mazzo di chiavi del Santuario dell'Acqua", /*german*/"Deutsch"}
     );
    hintTable[SPIRIT_TEMPLE_KEY_RING] = HintText::Item({
                        //obscure text
                        Text{"a sandy toolbox for unlocking", /*french*/"des anti-portes sableux",            /*spanish*/"un conjunto arenoso de cerrajero",  /*italian*/"un inesauribile sbloccatore sabbioso", /*german*/"Deutsch"},
                        Text{"a sandy dungeon season pass",   /*french*/"les rêves sableux d'un prisonnier",  /*spanish*/"un pase vip de mazmorras arenoso",  /*italian*/"un passe-partout sabbioso",            /*german*/"Deutsch"},
                        Text{"a sandy jingling ring",         /*french*/"des efface-serrures sableux",        /*spanish*/"una cadena multiusos arenosa",      /*italian*/"un anello sabbioso",                   /*german*/"Deutsch"},
                        Text{"a sandy skeleton key",          /*french*/"des crochets à porte sableux",       /*spanish*/"un anillo arenoso contra cerrojos", /*italian*/"una chiave magica sabbiosa",           /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a key ring", /*french*/"un trousseau de clés", /*spanish*/"un llavero", /*italian*/"un mazzo di chiavi", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"a Spirit Temple Key Ring", /*french*/"un trousseau de clés du temple de l'esprit", /*spanish*/"un llavero del Templo del Espíritu", /*italian*/"un mazzo di chiavi del Santuario dello Spirito", /*german*/"Deutsch"}
     );
    hintTable[SHADOW_TEMPLE_KEY_RING] = HintText::Item({
                        //obscure text
                        Text{"a creepy toolbox for unlocking", /*french*/"des anti-portes sinistres",            /*spanish*/"un conjunto tenebroso de cerrajero",  /*italian*/"un inesauribile sbloccatore patibolare", /*german*/"Deutsch"},
                        Text{"a creepy dungeon season pass",   /*french*/"les rêves sinistres d'un prisonnier",  /*spanish*/"un pase vip de mazmorras tenebroso",  /*italian*/"un passe-partout patibolare",            /*german*/"Deutsch"},
                        Text{"a creepy jingling ring",         /*french*/"des efface-serrures sinistres",        /*spanish*/"una cadena multiusos tenebrosa",      /*italian*/"un anello patibolare",                   /*german*/"Deutsch"},
                        Text{"a creepy skeleton key",          /*french*/"des crochets à porte sinistres",       /*spanish*/"un anillo tenebroso contra cerrojos", /*italian*/"una chiave magica patibolare",           /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a key ring", /*french*/"un trousseau de clés", /*spanish*/"un llavero", /*italian*/"un mazzo di chiavi", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"a Shadow Temple Key Ring", /*french*/"un trousseau de clés du temple de l'ombre", /*spanish*/"un llavero del Templo de las Sombras", /*italian*/"un mazzo di chiavi del Santuario dell'Ombra", /*german*/"Deutsch"}
     );
    hintTable[GERUDO_TRAINING_GROUNDS_KEY_RING] = HintText::Item({
                        //obscure text
                        Text{"a labyrinthian toolbox for unlocking", /*french*/"des anti-portes labyrinthiques",            /*spanish*/"un conjunto laberíntico de cerrajero",  /*italian*/"un inesauribile sbloccatore labirintico", /*german*/"Deutsch"},
                        Text{"a labyrinthian dungeon season pass",   /*french*/"les rêves labyrinthiques d'un prisonnier",  /*spanish*/"un pase vip de mazmorras laberíntico",  /*italian*/"un passe-partout labirintico",            /*german*/"Deutsch"},
                        Text{"a labyrinthian jingling ring",         /*french*/"des efface-serrures labyrinthiques",        /*spanish*/"una cadena multiusos laberíntica",      /*italian*/"un anello labirintico",                   /*german*/"Deutsch"},
                        Text{"a labyrinthian skeleton key",          /*french*/"des crochets à porte labyrinthiques",       /*spanish*/"un anillo laberíntico contra cerrojos", /*italian*/"una chiave magica labirintica",           /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a key ring", /*french*/"un trousseau de clés", /*spanish*/"un llavero", /*italian*/"un mazzo di chiavi", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"a Gerudo Training Ground Key Ring", /*french*/"un trousseau de clés du gymnase Gerudo", /*spanish*/"un llavero del Centro de Instrucción Gerudo", /*italian*/"un mazzo di chiavi della zona di addestramento", /*german*/"Deutsch"}
     );
    hintTable[GERUDO_FORTRESS_KEY_RING] = HintText::Item({
                        //obscure text
                        Text{"an imprisoned toolbox for unlocking", /*french*/"des anti-portes emprisonnés",            /*spanish*/"un conjunto enjaulado de cerrajero",    /*italian*/"un inesauribile sbloccatore per prigionieri", /*german*/"Deutsch"},
                        Text{"an imprisoned dungeon season pass",   /*french*/"les rêves emprisonnés d'un prisonnier",  /*spanish*/"un pase vip de una mazmorra enjaulado", /*italian*/"un passe-partout per prigionieri",            /*german*/"Deutsch"},
                        Text{"an imprisoned jingling ring",         /*french*/"des efface-serrures emprisonnés",        /*spanish*/"una cadena multiusos enjaulada",        /*italian*/"un anello per prigionieri",                   /*german*/"Deutsch"},
                        Text{"an imprisoned skeleton key",          /*french*/"des crochets à porte emprisonnés",       /*spanish*/"un anillo enjaulado contra cerrojos",   /*italian*/"una chiave magica per prigionieri",           /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a key ring", /*french*/"un trousseau de clés", /*spanish*/"un llavero", /*italian*/"un mazzo di chiavi", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"a Gerudo Fortress Key Ring", /*french*/"un trousseau de clés de la forteresse Gerudo", /*spanish*/"un llavero de la Fortaleza Gerudo", /*italian*/"un mazzo di chiavi della fortezza Gerudo", /*german*/"Deutsch"}
     );
    hintTable[BOTTOM_OF_THE_WELL_KEY_RING] = HintText::Item({
                        //obscure text
                        Text{"a moldy toolbox for unlocking", /*french*/"des anti-portes moisis",            /*spanish*/"un conjunto subterráneo de cerrajero",    /*italian*/"un inesauribile sbloccatore ammuffito", /*german*/"Deutsch"},
                        Text{"a moldy dungeon season pass",   /*french*/"les rêves moisis d'un prisonnier",  /*spanish*/"un pase vip de una mazmorra subterráneo", /*italian*/"un passe-partout ammuffito",            /*german*/"Deutsch"},
                        Text{"a moldy jingling ring",         /*french*/"des efface-serrures moisis",        /*spanish*/"una cadena multiusos subterránea",        /*italian*/"un anello ammuffito",                   /*german*/"Deutsch"},
                        Text{"a moldy skeleton key",          /*french*/"des crochets à porte moisis",       /*spanish*/"un anillo subterráneo contra cerrojos",   /*italian*/"una chiave magica ammuffita",           /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a key ring", /*french*/"un trousseau de clés", /*spanish*/"un llavero", /*italian*/"un mazzo di chiavi", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"a Bottom of the Well Key Ring", /*french*/"un trousseau de clés du fond du puits", /*spanish*/"un llavero del Fondo del pozo", /*italian*/"un mazzo di chiavi del fondo del pozzo", /*german*/"Deutsch"}
     );
    hintTable[GANONS_CASTLE_KEY_RING] = HintText::Item({
                        //obscure text
                        Text{"a final toolbox for unlocking", /*french*/"des anti-portes finaux",            /*spanish*/"un conjunto decisivo de cerrajero",    /*italian*/"un inesauribile sbloccatore finale", /*german*/"Deutsch"},
                        Text{"a final dungeon season pass",   /*french*/"les rêves finaux d'un prisonnier",  /*spanish*/"un pase vip de una mazmorra decisivo", /*italian*/"un passe-partout finale",            /*german*/"Deutsch"},
                        Text{"a final jingling ring",         /*french*/"des efface-serrures finaux",        /*spanish*/"una cadena multiusos decisiva",        /*italian*/"un anello finale",                   /*german*/"Deutsch"},
                        Text{"a final skeleton key",          /*french*/"des crochets à porte finaux",       /*spanish*/"un anillo decisivo multiusos",         /*italian*/"una chiave magica finale",           /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a key ring", /*french*/"un trousseau de clés", /*spanish*/"un llavero", /*italian*/"un mazzo di chiavi", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"a Ganon's Castle Key Ring", /*french*/"un trousseau de clés du château de Ganon", /*spanish*/"un llavero del Castillo de Ganon", /*italian*/"un mazzo di chiavi del castello di Ganon", /*german*/"Deutsch"}
     );

    hintTable[TREASURE_GAME_SMALL_KEY] = HintText::Item({
                        //obscure text
                        Text{"a gambler's tool for unlocking", /*french*/"un anti-porte de parieur",        /*spanish*/"una clave de un juego de azar",                 /*italian*/"uno sbloccatore fortuito",          /*german*/"Deutsch"},
                        Text{"a gambler's dungeon pass",       /*french*/"le rêve d'un prisonnier parieur", /*spanish*/"un pase de un juego de azar",                   /*italian*/"un permesso fortuito",              /*german*/"Deutsch"},
                        Text{"a gambler's lock remover",       /*french*/"un efface-serrure de parieur",    /*spanish*/"un destructor de cerraduras del juego de azar", /*italian*/"un dissolutore di catene fortuite", /*german*/"Deutsch"},
                        Text{"a gambler's lockpick",           /*french*/"un crochet à serrure de parieur", /*spanish*/"una apertura portentosa del juego de azar",     /*italian*/"un grimaldello fortuito",           /*german*/"Deutsch"},
                      }, {
                        //ambiguous text
                        Text{"a small key", /*french*/"une petite clé", /*spanish*/"una llave pequeña", /*italian*/"una piccola chiave", /*german*/"Deutsch"},
                      },
                        //clear text
                        Text{"a Treasure Chest Shop Small Key", /*french*/"une petite clé de la chasse aux trésors", /*spanish*/"una llave pequeña del Cofre del Tesoro", /*italian*/"una piccola chiave della sala della fortuna", /*german*/"Deutsch"}
    );

    hintTable[KOKIRI_EMERALD] = HintText::Item({
                       //obscure text
                       Text{"a green stone",       /*french*/"une pierre verte",              /*spanish*/"una piedra verde",          /*italian*/"una pietra verde",           /*german*/"Deutsch"},
                       Text{"a gift before death", /*french*/"le dernier souffle d'un arbre", /*spanish*/"un obsequio testamentario", /*italian*/"un dono dal letto di morte", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a spiritual stone", /*french*/"une pierre spirituelle", /*spanish*/"una piedra espiritual", /*italian*/"una pietra spirituale", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Kokiri Emerald", /*french*/"l'émeraude Kokiri", /*spanish*/"la Esmeralda de los Kokiri", /*italian*/"lo smeraldo dei Kokiri", /*german*/"Deutsch"}
    );

    hintTable[GORON_RUBY] = HintText::Item({
                       //obscure text
                       Text{"a red stone",       /*french*/"une pierre rouge",         /*spanish*/"una piedra carmín",                  /*italian*/"una pietra rossa",     /*german*/"Deutsch"},
                       Text{"sworn brotherhood", /*french*/"un serment de fraternité", /*spanish*/"el juramento de hermanos de sangre", /*italian*/"fratellanza rocciosa", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a spiritual stone", /*french*/"une pierre spirituelle", /*spanish*/"una piedra espiritual", /*italian*/"una pietra spirituale", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Goron Ruby", /*french*/"le rubis Goron", /*spanish*/"el Rubí de los Goron", /*italian*/"il rubino dei Goron", /*german*/"Deutsch"}
    );

    hintTable[ZORA_SAPPHIRE] = HintText::Item({
                       //obscure text
                       Text{"a blue stone",       /*french*/"une pierre bleue",     /*spanish*/"una piedra celeste",      /*italian*/"una pietra azzurra",        /*german*/"Deutsch"},
                       Text{"an engagement gift", /*french*/"un cadeau de mariage", /*spanish*/"un regalo de compromiso", /*italian*/"un regalo di fidanzamento", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a spiritual stone", /*french*/"une pierre spirituelle", /*spanish*/"una piedra espiritual", /*italian*/"una pietra spirituale", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Zora Sapphire", /*french*/"le saphir Zora", /*spanish*/"el Zafiro de los Zora", /*italian*/"lo zaffiro degli Zora", /*german*/"Deutsch"}
    );

    hintTable[FOREST_MEDALLION] = HintText::Item({
                       //obscure text
                       Text{"a green coin",       /*french*/"une pièce verte",   /*spanish*/"una moneda esmeralda", /*italian*/"un disco verde",     /*german*/"Deutsch"},
                       Text{"Saria's friendship", /*french*/"l'amitié de Saria", /*spanish*/"la amistad de Saria",  /*italian*/"il potere di Saria", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a medallion", /*french*/"un médaillon", /*spanish*/"un medallón", /*italian*/"un medaglione", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Forest Medallion", /*french*/"le médaillon de la forêt", /*spanish*/"el Medallón del Bosque", /*italian*/"il medaglione della Foresta", /*german*/"Deutsch"}
    );

    hintTable[FIRE_MEDALLION] = HintText::Item({
                       //obscure text
                       Text{"a red coin",      /*french*/"une pièce rouge",          /*spanish*/"una moneda rubí",           /*italian*/"un disco rosso",       /*german*/"Deutsch"},
                       Text{"Darunia's power", /*french*/"la fraternité de Darunia", /*spanish*/"la fraternidad de Darunia", /*italian*/"il potere di Darunia", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a medallion", /*french*/"un médaillon", /*spanish*/"un medallón", /*italian*/"un medaglione", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Fire Medallion", /*french*/"le médaillon du feu", /*spanish*/"el Medallón del Fuego", /*italian*/"il medaglione del Fuoco", /*german*/"Deutsch"}
    );

    hintTable[WATER_MEDALLION] = HintText::Item({
                       //obscure text
                       Text{"a blue coin",  /*french*/"une pièce bleue", /*spanish*/"una moneda zafiro", /*italian*/"un disco blu",      /*german*/"Deutsch"},
                       Text{"Ruto's power", /*french*/"l'amour de Ruto", /*spanish*/"el amor de Ruto",   /*italian*/"il potere di Ruto", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a medallion", /*french*/"un médaillon", /*spanish*/"un medallón", /*italian*/"un medaglione", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Water Medallion", /*french*/"le médaillon de l'eau", /*spanish*/"el Medallón del Agua", /*italian*/"il medaglione dell'Acqua", /*german*/"Deutsch"}
    );

    hintTable[SPIRIT_MEDALLION] = HintText::Item({
                       //obscure text
                       Text{"an orange coin",  /*french*/"une pièce orange",      /*spanish*/"una moneda ámbar",      /*italian*/"un disco arancione",  /*german*/"Deutsch"},
                       Text{"Nabooru's power", /*french*/"le respect de Nabooru", /*spanish*/"el respeto de Nabooru", /*italian*/"il potere di Naburu", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a medallion", /*french*/"un médaillon", /*spanish*/"un medallón", /*italian*/"un medaglione", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Spirit Medallion", /*french*/"le médaillon de l'esprit", /*spanish*/"el Medallón del Espíritu", /*italian*/"il medaglione dello Spirito", /*german*/"Deutsch"}
    );

    hintTable[SHADOW_MEDALLION] = HintText::Item({
                       //obscure text
                       Text{"a purple coin", /*french*/"une pièce pourpre",   /*spanish*/"una moneda malva",     /*italian*/"un disco viola",    /*german*/"Deutsch"},
                       Text{"Impa's power",  /*french*/"la confiance d'Impa", /*spanish*/"la confianza de Impa", /*italian*/"il potere di Impa", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a medallion", /*french*/"un médaillon", /*spanish*/"un medallón", /*italian*/"un medaglione", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Shadow Medallion", /*french*/"le médaillon de l'ombre", /*spanish*/"el Medallón de la Sombra", /*italian*/"il medaglione dell'Ombra", /*german*/"Deutsch"}
    );

    hintTable[LIGHT_MEDALLION] = HintText::Item({
                       //obscure text
                       Text{"a yellow coin", /*french*/"une pièce jaune", /*spanish*/"una moneda resplandeciente", /*italian*/"un disco giallo",   /*german*/"Deutsch"},
                       Text{"Rauru's power", /*french*/"la foi de Rauru", /*spanish*/"la fe de Rauru",             /*italian*/"il potere di Raul", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a medallion", /*french*/"un médaillon", /*spanish*/"un medallón", /*italian*/"un medaglione", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"the Light Medallion", /*french*/"le médaillon de la lumière", /*spanish*/"el Medallón de la Luz", /*italian*/"il medaglione della Luce", /*german*/"Deutsch"}
    );

    hintTable[RECOVERY_HEART] = HintText::Item({
                       //obscure text
                       Text{"a free heal",   /*french*/"un bec-au-bobo", /*spanish*/"una cura de regalo",     /*italian*/"una cura rincuorante", /*german*/"Deutsch"},
                       Text{"a hearty meal", /*french*/"un petit amour", /*spanish*/"una sanación romántica", /*italian*/"un bacino",            /*german*/"Deutsch"},
                       Text{"a Band-Aid",    /*french*/"un diachylon",   /*spanish*/"un corazoncito sanador", /*italian*/"un cerotto",           /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"something heart-shaped", /*french*/"une chose en forme de cœur", /*spanish*/"algo con forma de corazón", /*italian*/"qualcosa a forma di cuore", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Recovery Heart", /*french*/"un cœur de vie", /*spanish*/"un corazón", /*italian*/"un cuore", /*german*/"Deutsch"}
    );

    hintTable[GREEN_RUPEE] = HintText::Item({
                       //obscure text
                       Text{"a unique coin", /*french*/"un rubis bien mérité", /*spanish*/"una singular moneda", /*italian*/"una moneta più unica che rara", /*german*/"Deutsch"},
                       Text{"a penny",       /*french*/"un sou",               /*spanish*/"un peso hyliano",     /*italian*/"un nichelino",                  /*german*/"Deutsch"},
                       Text{"a green gem",   /*french*/"un joyau vert",        /*spanish*/"una gema verde",      /*italian*/"una gemma verde",               /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"some rupees", /*french*/"une quantité de rubis", /*spanish*/"una cantidad de rupias", /*italian*/"un po' di rupie", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Green Rupee", /*french*/"un rubis vert", /*spanish*/"una rupia verde", /*italian*/"una rupia verde", /*german*/"Deutsch"}
    );

    hintTable[BLUE_RUPEE] = HintText::Item({
                       //obscure text
                       Text{"a common coin", /*french*/"quelques sous", /*spanish*/"una moneda usual", /*italian*/"il solito soldo",   /*german*/"Deutsch"},
                       Text{"a blue gem",    /*french*/"un joyau bleu",  /*spanish*/"una gema azul",   /*italian*/"una gemma azzurra", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"some rupees", /*french*/"une quantité de rubis", /*spanish*/"una cantidad de rupias", /*italian*/"un po' di rupie", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Blue Rupee", /*french*/"un rubis bleu", /*spanish*/"una rupia azul", /*italian*/"una rupia blu", /*german*/"Deutsch"}
    );

    hintTable[RED_RUPEE] = HintText::Item({
                       //obscure text
                       Text{"couch cash", /*french*/"un peu de fric", /*spanish*/"una buena moneda", /*italian*/"una paghetta",    /*german*/"Deutsch"},
                       Text{"a red gem",  /*french*/"un joyau rouge", /*spanish*/"una gema roja",    /*italian*/"una gemma rossa", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"some rupees", /*french*/"une quantité de rubis", /*spanish*/"una cantidad de rupias", /*italian*/"un po' di rupie", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Red Rupee", /*french*/"un rubis rouge", /*spanish*/"una rupia roja", /*italian*/"una rupia rossa", /*german*/"Deutsch"}
    );

    hintTable[PURPLE_RUPEE] = HintText::Item({
                       //obscure text
                       Text{"big bucks",    /*french*/"plein de fric",  /*spanish*/"plata de calidad",  /*italian*/"un bel gruzzolo", /*german*/"Deutsch"},
                       Text{"a purple gem", /*french*/"un joyau mauve", /*spanish*/"una gema morada",   /*italian*/"una gemma viola", /*german*/"Deutsch"},
                       Text{"wealth",       /*french*/"la richesse",    /*spanish*/"una buena riqueza", /*italian*/"mezzo centone",   /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"some rupees", /*french*/"une quantité de rubis", /*spanish*/"una cantidad de rupias", /*italian*/"un po' di rupie", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Purple Rupee", /*french*/"un rubis pourpre", /*spanish*/"una rupia morada", /*italian*/"una rupia viola", /*german*/"Deutsch"}
    );

    hintTable[HUGE_RUPEE] = HintText::Item({
                       //obscure text
                       Text{"a juicy jackpot", /*french*/"le jackpot",           /*spanish*/"el premio gordo",     /*italian*/"un jackpot",           /*german*/"Deutsch"},
                       Text{"a yellow gem",    /*french*/"un joyau doré",        /*spanish*/"una gema amarilla",   /*italian*/"una gemma d'oro",      /*german*/"Deutsch"},
                       Text{"a giant gem",     /*french*/"un gros joyau",        /*spanish*/"una gema descomunal", /*italian*/"una gemma gigante",    /*german*/"Deutsch"},
                       Text{"great wealth",    /*french*/"l'aisance financière", /*spanish*/"dinero a caudales",   /*italian*/"una grande ricchezza", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"some rupees", /*french*/"une quantité de rubis", /*spanish*/"una cantidad de rupias", /*italian*/"un po' di rupie", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Huge Rupee", /*french*/"un énorme rubis", /*spanish*/"una rupia gigante", /*italian*/"una rupia gigante", /*german*/"Deutsch"}
    );

    hintTable[PIECE_OF_HEART] = HintText::Item({
                       //obscure text
                       Text{"a little love",  /*french*/"un peu plus d'amour", /*spanish*/"un cuarto de amor", /*italian*/"un po' di amore",   /*german*/"Deutsch"},
                       Text{"a broken heart", /*french*/"un cœur brisé",       /*spanish*/"un corazón roto",   /*italian*/"un cuore spezzato", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"something heart-shaped", /*french*/"une chose en forme de cœur", /*spanish*/"algo con forma de corazón", /*italian*/"qualcosa a forma di cuore", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Piece of Heart", /*french*/"un quart de cœur", /*spanish*/"una pieza de corazón", /*italian*/"un frammento di cuore", /*german*/"Deutsch"}
    );

    hintTable[HEART_CONTAINER] = HintText::Item({
                       //obscure text
                       Text{"a lot of love",      /*french*/"le grand amour",              /*spanish*/"amor por doquier",          /*italian*/"un grande amore",          /*german*/"Deutsch"},
                       Text{"a Valentine's gift", /*french*/"un cadeau de Saint-Valentin", /*spanish*/"un contenedor de afección", /*italian*/"un dono di San Valentino", /*german*/"Deutsch"},
                       Text{"a boss's organ",     /*french*/"un organe de monstre",        /*spanish*/"los órganos de un jefe",    /*italian*/"le spoglie di un boss",    /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"something heart-shaped", /*french*/"une chose en forme de cœur", /*spanish*/"algo con forma de corazón", /*italian*/"qualcosa a forma di cuore", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Heart Container", /*french*/"un cœur d'énergie", /*spanish*/"un contenedor de corazón", /*italian*/"un portacuori", /*german*/"Deutsch"}
    );

    hintTable[ICE_TRAP] = HintText::Item({
                       //obscure text
                       Text{"a gift from Ganon",    /*french*/"un cadeau de Ganon",         /*spanish*/"un regalo de Ganon",        /*italian*/"un regalo di Ganon",         /*german*/"Deutsch"},
                       Text{"a chilling discovery", /*french*/"une frissonante découverte", /*spanish*/"un escalofriante hallazgo", /*italian*/"una scoperta agghiacciante", /*german*/"Deutsch"},
                       Text{"frosty fun",           /*french*/"une engelure",               /*spanish*/"una gélida diversión",      /*italian*/"il cugino di Geronimo",      /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a Great Fairy's power",   /*french*/"le pouvoir d'une grande fée",  /*spanish*/"el poder de una Gran Hada", /*italian*/"il potere di una Grande Fata", /*german*/"Deutsch"},
                       Text{"a magic arrow",           /*french*/"une flèche magique",           /*spanish*/"una flecha mágica",         /*italian*/"una freccia incantata",        /*german*/"Deutsch"},
                       Text{"a medallion",             /*french*/"un médaillon",                 /*spanish*/"un medallón",               /*italian*/"un Medaglione",                /*german*/"Deutsch"},
                       Text{"a spiritual stone",       /*french*/"une pierre spirituelle",       /*spanish*/"una piedra espiritual",     /*italian*/"una Pietra Spirituale",        /*german*/"Deutsch"},
                       Text{"something that can stun", /*french*/"une chose qui peut paralyser", /*spanish*/"algo que pueda paralizar",  /*italian*/"qualcosa che può paralizzare", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"an Ice Trap", /*french*/"un piège de glace", /*spanish*/"una trampa de hielo", /*italian*/"una trappola", /*german*/"Deutsch"}
    );

  //MILK

    hintTable[BOMBS_5] = HintText::Item({
                       //obscure text
                       Text{"a few explosives",  /*french*/"une poignée de pétards",       /*spanish*/"un par de explosivos", /*italian*/"un po' di esplosivi", /*german*/"Deutsch"},
                       Text{"a few blast balls", /*french*/"une poignée de boules bleues", /*spanish*/"un par de estallidos", /*italian*/"un po' di scoppi",    /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"explosives", /*french*/"un paquet d'explosifs", /*spanish*/"un montón de explosivos", /*italian*/"un pacchetto di esplosivi", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"Bombs (5 pieces)", /*french*/"une demi-dizaine de bombes", /*spanish*/"unas (5) bombas", /*italian*/"5 bombe", /*german*/"Deutsch"}
    );

    hintTable[BOMBS_10] = HintText::Item({
                       //obscure text
                       Text{"some explosives",  /*french*/"un paquet de pétards",       /*spanish*/"unos cuantos explosivos", /*italian*/"una decina di esplosivi", /*german*/"Deutsch"},
                       Text{"some blast balls", /*french*/"un paquet de boules bleues", /*spanish*/"unos cuantos estallidos", /*italian*/"una decina di scoppi",    /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"explosives", /*french*/"un paquet d'explosifs", /*spanish*/"un montón de explosivos", /*italian*/"un pacchetto di esplosivi", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"Bombs (10 pieces)", /*french*/"une dizaine de bombes", /*spanish*/"unas (10) bombas", /*italian*/"10 bombe", /*german*/"Deutsch"}
    );

    hintTable[BOMBS_20] = HintText::Item({
                       //obscure text
                       Text{"lots-o-explosives",     /*french*/"une abondance de pétards",       /*spanish*/"un puñado de explosivos", /*italian*/"un mucchio di esplosivi", /*german*/"Deutsch"},
                       Text{"plenty of blast balls", /*french*/"une abondance de boules bleues", /*spanish*/"bastantes estallidos",    /*italian*/"un mucchio di scoppi",    /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"explosives", /*french*/"un paquet d'explosifs", /*spanish*/"un montón de explosivos", /*italian*/"un pacchetto di esplosivi", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"Bombs (20 pieces)", /*french*/"une vingtaine de bombes", /*spanish*/"unas (20) bombas", /*italian*/"20 bombe", /*german*/"Deutsch"}
    );

    hintTable[BOMBCHU_5] = HintText::Item({
                       //obscure text
                       Text{"a few mice bombs",     /*french*/"une poignée de mignons explosifs", /*spanish*/"un par de bombas roedoras",       /*italian*/"un po' di sorci esplosivi",   /*german*/"Deutsch"},
                       Text{"a few proximity mice", /*french*/"une poignée de jouets à remonter", /*spanish*/"un par de explosivos ratoncitos", /*italian*/"un po' di topi a orologeria", /*german*/"Deutsch"},
                       Text{"a few wall crawlers",  /*french*/"une poignée de rapides grimpeurs", /*spanish*/"un par de trepaparedes",          /*italian*/"un po' di arrampicamuri",     /*german*/"Deutsch"},
                       Text{"a few trail blazers",  /*french*/"une poignée de zigzags éclatants", /*spanish*/"un par de ratas propulsadas",     /*italian*/"un po' di scie a zig-zag",    /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a prize of the House of Skulltulas", /*french*/"un prix de la maison des Skulltulas", /*spanish*/"un obsequio de la Casa Skulltula", /*italian*/"un premio delle Aracnule",  /*german*/"Deutsch"},
                       Text{"explosives",                         /*french*/"un paquet d'explosifs",               /*spanish*/"un montón de explosivos",          /*italian*/"un pacchetto di esplosivi", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"Bombchus (5 pieces)", /*french*/"une demi-dizaine de Bombchus", /*spanish*/"unos (5) bombchus", /*italian*/"5 radiomine", /*german*/"Deutsch"}
    );

    hintTable[BOMBCHU_10] = HintText::Item({
                       //obscure text
                       Text{"some mice bombs",     /*french*/"un paquet de mignons explosifs", /*spanish*/"unas cuantas bombas roedoras",       /*italian*/"una decina di sorci esplosivi",   /*german*/"Deutsch"},
                       Text{"some proximity mice", /*french*/"un paquet de jouets à remonter", /*spanish*/"unos cuantos explosivos ratoncitos", /*italian*/"una decina di topi a orologeria", /*german*/"Deutsch"},
                       Text{"some wall crawlers",  /*french*/"un paquet de rapides grimpeurs", /*spanish*/"unos cuantos trepaparedes",          /*italian*/"una decina di arrampicamuri",     /*german*/"Deutsch"},
                       Text{"some trail blazers",  /*french*/"un paquet de zigzags éclatants", /*spanish*/"unas cuantas ratas propulsadas",     /*italian*/"una decina di scie a zig-zag",    /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a prize of the House of Skulltulas", /*french*/"un prix de la maison des Skulltulas", /*spanish*/"un obsequio de la Casa Skulltula", /*italian*/"un premio delle Aracnule",  /*german*/"Deutsch"},
                       Text{"explosives",                         /*french*/"un paquet d'explosifs",               /*spanish*/"un montón de explosivos",          /*italian*/"un pacchetto di esplosivi", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"Bombchus (10 pieces)", /*french*/"une dizaine de Bombchus", /*spanish*/"unos (10) bombchus", /*italian*/"10 radiomine", /*german*/"Deutsch"}
    );

    hintTable[BOMBCHU_20] = HintText::Item({
                       //obscure text
                       Text{"plenty of mice bombs",     /*french*/"une abondance de mignons explosifs", /*spanish*/"bastantes bombas roedoras",       /*italian*/"un mucchio di sorci esplosivi",   /*german*/"Deutsch"},
                       Text{"plenty of proximity mice", /*french*/"une abondance de jouets à remonter", /*spanish*/"bastantes explosivos ratoncitos", /*italian*/"un mucchio di topi a orologeria", /*german*/"Deutsch"},
                       Text{"plenty of wall crawlers",  /*french*/"une abondance de rapides grimpeurs", /*spanish*/"bastantes trepaparedes",          /*italian*/"un mucchio di arrampicamuri",     /*german*/"Deutsch"},
                       Text{"plenty of trail blazers",  /*french*/"une abondance de zigzags éclatants", /*spanish*/"bastantes ratas propulsadas",     /*italian*/"un mucchio di scie a zig-zag",    /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a prize of the House of Skulltulas", /*french*/"un prix de la maison des Skulltulas", /*spanish*/"un obsequio de la Casa Skulltula", /*italian*/"un premio delle Aracnule",  /*german*/"Deutsch"},
                       Text{"explosives",                         /*french*/"un paquet d'explosifs",               /*spanish*/"un montón de explosivos",          /*italian*/"un pacchetto di esplosivi", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"Bombchus (20 pieces)", /*french*/"une vingtaine de Bombchus", /*spanish*/"unos (20) bombchus", /*italian*/"20 radiomine", /*german*/"Deutsch"}
    );

  //BOMBCHU_DROP

    hintTable[ARROWS_5] = HintText::Item({
                       //obscure text
                       Text{"a few danger darts", /*french*/"une poignée d'obus",     /*spanish*/"un par de peligrosos dardos", /*italian*/"un po' di punte pungenti",      /*german*/"Deutsch"},
                       Text{"a few sharp shafts", /*french*/"une poignée de piquets", /*spanish*/"un par de puntas afiladas",   /*italian*/"un po' di indicatori dolorosi", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a projectile", /*french*/"un projectile", /*spanish*/"un proyectil", /*italian*/"un proiettile", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"Arrows (5 pieces)", /*french*/"une demi-dizaine de flèches", /*spanish*/"unas (5) flechas", /*italian*/"5 frecce", /*german*/"Deutsch"}
    );

    hintTable[ARROWS_10] = HintText::Item({
                       //obscure text
                       Text{"some danger darts", /*french*/"un paquet d'obus",     /*spanish*/"unos cuantos peligrosos dardos", /*italian*/"una decina di punte pungenti",      /*german*/"Deutsch"},
                       Text{"some sharp shafts", /*french*/"un paquet de piquets", /*spanish*/"unas cuantas puntas afiladas",   /*italian*/"una decina di indicatori dolorosi", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a projectile", /*french*/"un projectile", /*spanish*/"un proyectil", /*italian*/"un proiettile", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"Arrows (10 pieces)", /*french*/"une dizaine de flèches", /*spanish*/"unas (10) flechas", /*italian*/"10 frecce", /*german*/"Deutsch"}
    );

    hintTable[ARROWS_30] = HintText::Item({
                       //obscure text
                       Text{"plenty of danger darts", /*french*/"une abondance d'obus",     /*spanish*/"bastantes peligrosos dardos", /*italian*/"un mucchio di punte pungenti",      /*german*/"Deutsch"},
                       Text{"plenty of sharp shafts", /*french*/"une abondance de piquets", /*spanish*/"bastantes puntas afiladas",   /*italian*/"un mucchio di indicatori dolorosi", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a projectile", /*french*/"un projectile", /*spanish*/"un proyectil", /*italian*/"un proiettile", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"Arrows (30 pieces)", /*french*/"une trentaine de flèches", /*spanish*/"unas (30) flechas", /*italian*/"30 frecce", /*german*/"Deutsch"}
    );

    hintTable[DEKU_NUTS_5] = HintText::Item({
                       //obscure text
                       Text{"some nuts",       /*french*/"une poignée de noisettes",     /*spanish*/"un par de nueces",               /*italian*/"un po' di noci",              /*german*/"Deutsch"},
                       Text{"some flashbangs", /*french*/"une poignée d'éclats",         /*spanish*/"un par de semillas aturdidoras", /*italian*/"un po' di granate stordenti", /*german*/"Deutsch"},
                       Text{"some scrub spit", /*french*/"une poignée de crachats Mojo", /*spanish*/"un par de escupitajos deku",     /*italian*/"un po' di sputi di Deku",     /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"some Deku munitions",     /*french*/"un paquet de munitions Mojo",  /*spanish*/"un montón de municiones Deku",  /*italian*/"un pacchetto di munizioni Deku", /*german*/"Deutsch"},
                       Text{"something that can stun", /*french*/"une chose qui peut paralyser", /*spanish*/"algo que pueda paralizar",      /*italian*/"qualcosa che può paralizzare",   /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"Deku Nuts (5 pieces)", /*french*/"une demi-dizaine de noix Mojo", /*spanish*/"unas (5) nueces deku", /*italian*/"5 noci Deku", /*german*/"Deutsch"}
    );

    hintTable[DEKU_NUTS_10] = HintText::Item({
                       //obscure text
                       Text{"lots-o-nuts",          /*french*/"un paquet de noisettes",     /*spanish*/"un puñado de nueces",               /*italian*/"un mucchio di noci",              /*german*/"Deutsch"},
                       Text{"plenty of flashbangs", /*french*/"un paquet d'éclats",         /*spanish*/"unas cuantas semillas aturdidoras", /*italian*/"un mucchio di granate stordenti", /*german*/"Deutsch"},
                       Text{"plenty of scrub spit", /*french*/"un paquet de crachats Mojo", /*spanish*/"unos cuantos escupitajos deku",     /*italian*/"un mucchio di sputi di Deku",     /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"some Deku munitions",     /*french*/"un paquet de munitions Mojo",  /*spanish*/"un montón de municiones Deku", /*italian*/"un pacchetto di munizioni Deku", /*german*/"Deutsch"},
                       Text{"something that can stun", /*french*/"une chose qui peut paralyser", /*spanish*/"algo que pueda paralizar",     /*italian*/"qualcosa che può paralizzare",   /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"Deku Nuts (10 pieces)", /*french*/"une dizaine de noix Mojo", /*spanish*/"unas (10) nueces deku", /*italian*/"10 noci Deku", /*german*/"Deutsch"}
    );

    hintTable[DEKU_SEEDS_30] = HintText::Item({
                       //obscure text
                       Text{"catapult ammo", /*french*/"un paquet de délicieuses munitions", /*spanish*/"un par de munición infantil", /*italian*/"munizioni per catapulte", /*german*/"Deutsch"},
                       Text{"lots-o-seeds",  /*french*/"un paquet de germes séchés",         /*spanish*/"un puñado de semillas",       /*italian*/"un mucchio di semi",      /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"a projectile",        /*french*/"un projectile",               /*spanish*/"un proyectil",                 /*italian*/"un proiettile",                  /*german*/"Deutsch"},
                       Text{"some Deku munitions", /*french*/"un paquet de munitions Mojo", /*spanish*/"un montón de municiones Deku", /*italian*/"un pacchetto di munizioni Deku", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"Deku Seeds (30 pieces)", /*french*/"une trentaine de graines Mojo", /*spanish*/"unas (30) semillas deku", /*italian*/"30 semi Deku", /*german*/"Deutsch"}
    );

    hintTable[DEKU_STICK_1] = HintText::Item({
                       //obscure text
                       Text{"a breakable branch", /*french*/"un bout de bois", /*spanish*/"un pequeño báculo", /*italian*/"un legno lungo", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"some Deku munitions", /*french*/"un paquet de munitions Mojo", /*spanish*/"un montón de municiones Deku", /*italian*/"un pacchetto di munizioni Deku", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Deku Stick", /*french*/"un bâton Mojo", /*spanish*/"un palo deku", /*italian*/"un ramo Deku", /*german*/"Deutsch"}
    );

    hintTable[TREASURE_GAME_HEART] = HintText::Item({
                       //obscure text
                       Text{"a victory valentine", /*french*/"un amour gagnant", /*spanish*/"el amor victorioso", /*italian*/"amore vincitore", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"something heart-shaped", /*french*/"une chose en forme de cœur", /*spanish*/"algo con forma de corazón", /*italian*/"qualcosa a forma di cuore", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Piece of Heart", /*french*/"un quart de cœur", /*spanish*/"el amor de la victoria", /*italian*/"un frammento di cuore", /*german*/"Deutsch"}
    );

    hintTable[TREASURE_GAME_GREEN_RUPEE] = HintText::Item({
                       //obscure text
                       Text{"the dollar of defeat", /*french*/"le rubis de la défaite", /*spanish*/"el peso de la derrota", /*italian*/"la moneta della sconfitta", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"some rupees", /*french*/"une quantité de rubis", /*spanish*/"una cantidad de rupias", /*italian*/"un po' di rupie", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"a Green Rupee", /*french*/"un rubis vert", /*spanish*/"una rupia verde", /*italian*/"una rupia verde", /*german*/"Deutsch"}
    );

    hintTable[TRIFORCE_PIECE] = HintText::Item({
                       //obscure text
                       Text{"a triumph fork",  /*french*/"la Tribosse",      /*spanish*/"un trígono del triunfo", /*italian*/"una triporta dorata", /*german*/"Deutsch"},
                       Text{"cheese",          /*french*/"du fromage",       /*spanish*/"un porción de queso",    /*italian*/"del formaggio",       /*german*/"Deutsch"},
                       Text{"a gold fragment", /*french*/"un fragment d'or", /*spanish*/"un fragmento dorado",    /*italian*/"un frammento dorato", /*german*/"Deutsch"},
                     }, {},
                       //clear text
                       Text{"a Piece of the Triforce", /*french*/"un fragment de la Triforce", /*spanish*/"un fragmento de la Trifuerza", /*italian*/"un frammento di Triforza", /*german*/"Deutsch"}
    );

    hintTable[EPONA] = HintText::Item({
                       //obscure text
                       Text{"a horse",              /*french*/"un fidèle destrier", /*spanish*/"una yegua",            /*italian*/"una cavalla",              /*german*/"Deutsch"},
                       Text{"a four legged friend", /*french*/"un puissant animal", /*spanish*/"una amiga cuadrúpeda", /*italian*/"un'amica a quattro zampe", /*german*/"Deutsch"},
                     }, {
                       //ambiguous text
                       Text{"something from Malon",               /*french*/"un cadeau de Malon",                     /*spanish*/"un obsequio de Malon",            /*italian*/"un dono di Malon",                         /*german*/"Deutsch"},
                       Text{"a song sung by frogs",               /*french*/"une chanson aimée des grenouilles",      /*spanish*/"una melodía de ranas",            /*italian*/"un animale",                               /*german*/"Deutsch"},
                       Text{"something to cross a broken bridge", /*french*/"une chose pour traverser un pont brisé", /*spanish*/"algo para cruzar un puente roto", /*italian*/"qualcosa per oltrepassare un ponte rotto", /*german*/"Deutsch"},
                     },
                       //clear text
                       Text{"Epona", /*french*/"Epona", /*spanish*/"a Epona", /*italian*/"Epona", /*german*/"Deutsch"}
    );

    // [HINT_ERROR] = HintText::Item({
    //                      //obscure text
    //                      Text{"something mysterious", /*french*/"un sacré mystère",  /*spanish*/"algo misterioso",       /*italian*/"qualcosa di misterioso", /*german*/"Deutsch"},
    //                      Text{"an unknown treasure",  /*french*/"un trésor inconnu", /*spanish*/"un desconocido tesoro", /*italian*/"un tesoro incognito",    /*german*/"Deutsch"},
    //                    },
    //                      //clear text
    //                      Text{"An Error (Please Report This)", /*french*/"une erreur (signaler S.V.P.)", /*spanish*/"un error (repórtelo si es posible)", /*italian*/"un errore (segnalalo per favore)", /*german*/"Deutsch"}
    // );
}
