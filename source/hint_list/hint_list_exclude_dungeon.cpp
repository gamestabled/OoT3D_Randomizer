#include "hint_list.hpp"
// clang-format off
void HintTable_Init_Exclude_Dungeon() {
    /*--------------------------
    |        DEKU TREE         |
    ---------------------------*/
    hintTable[DEKU_TREE_MAP_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"in the #center of the Deku Tree# lies", /*french*/"#le cœur de l'arbre Mojo# recèle", /*spanish*/"al #centro del Gran Árbol Deku# yace", /*italian*/"al #centro dell'Albero Deku# puoi trovare", /*german*/"im #Zentrum des Deku-Baumes#, |wäre|wären|"},
    });

    hintTable[DEKU_TREE_SLINGSHOT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #treasure guarded by a scrub# in the Deku Tree is", /*french*/"le #trésor protégé par une peste# dans l'arbre Mojo est", /*spanish*/"un #deku del Gran Árbol Deku# esconde", /*italian*/"il #forziere custodito da un Deku# nell'omonimo albero contiene", /*german*/"ein #Schatz, beschützt von einem Laubkerl# des Deku-Baumes, |wäre|wären|"},
    });

    hintTable[DEKU_TREE_SLINGSHOT_ROOM_SIDE_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #treasure guarded by a scrub# in the Deku Tree is", /*french*/"le #trésor protégé par une peste# dans l'arbre Mojo est", /*spanish*/"un #deku del Gran Árbol Deku# esconde", /*italian*/"il #forziere custodito da un Deku# nell'omonimo albero contiene", /*german*/"ein #Schatz, beschützt von einem Laubkerl# des Deku-Baumes, |wäre|wären|"},
    });

    hintTable[DEKU_TREE_COMPASS_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#pillars of wood# in the Deku Tree lead to", /*french*/"les #piliers de bois# dans l'arbre Mojo indiquent", /*spanish*/"los #salientes del Gran Árbol Deku# conducen a", /*italian*/"dei #pilastri di legno# nell'Albero Deku conducono verso", /*german*/"nahe #hölzerner Säulen# des Deku-Baumes, |wäre|wären|"},
    });

    hintTable[DEKU_TREE_COMPASS_ROOM_SIDE_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#pillars of wood# in the Deku Tree lead to", /*french*/"les #piliers de bois# dans l'arbre Mojo indiquent", /*spanish*/"los #salientes del Gran Árbol Deku# conducen a", /*italian*/"dei #pilastri di legno# nell'Albero Deku conducono verso", /*german*/"nahe #hölzerner Säulen# des Deku-Baumes, |wäre|wären|"},
    });

    hintTable[DEKU_TREE_BASEMENT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#webs in the Deku Tree# hide", /*french*/"les #toiles dans l'arbre Mojo# cachent", /*spanish*/"entre #telarañas del Gran Árbol Deku# yace", /*italian*/"una #ragnatela nell'Albero Deku# copre", /*german*/"unterhalb von #Spinnenweben# des Deku-Baumes, |wäre|wären|"},
    });


    hintTable[DEKU_TREE_MQ_MAP_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"in the #center of the Deku Tree# lies", /*french*/"#le cœur de l'arbre Mojo# recèle", /*spanish*/"al #centro del Gran Árbol Deku# yace", /*italian*/"al #centro dell'Albero Deku# puoi trovare", /*german*/"im #Zentrum des Deku-Baumes#, |wäre|wären|"},
    });

    hintTable[DEKU_TREE_MQ_COMPASS_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #treasure guarded by a large spider# in the Deku Tree is", /*french*/"le #trésor protégé par une grosse araignée# dans l'arbre Mojo est", /*spanish*/"una #gran araña del Gran Árbol Deku# esconde", /*italian*/"il #tesoro protetto da un grosso ragno# nell'Albero Deku è", /*german*/"ein #Schatz, beschützt von einer großen Spinne# des Deku-Baumes, |wäre|wären|"},
    });

    hintTable[DEKU_TREE_MQ_SLINGSHOT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#pillars of wood# in the Deku Tree lead to", /*french*/"les #piliers de bois# dans l'arbre Mojo indiquent", /*spanish*/"los #salientes del Gran Árbol Deku# conducen a", /*italian*/"dei #pilastri di legno# nell'Albero Deku conducono verso", /*german*/"nahe #hölzerner Säulen# des Deku-Baumes, |wäre|wären|"},
    });

    hintTable[DEKU_TREE_MQ_SLINGSHOT_ROOM_BACK_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#pillars of wood# in the Deku Tree lead to", /*french*/"les #piliers de bois# dans l'arbre Mojo indiquent", /*spanish*/"los #salientes del Gran Árbol Deku# conducen a", /*italian*/"dei #pilastri di legno# nell'Albero Deku conducono verso", /*german*/"nahe #hölzerner Säulen# des Deku-Baumes, |wäre|wären|"},
    });

    hintTable[DEKU_TREE_MQ_BASEMENT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#webs in the Deku Tree# hide", /*french*/"les #toiles dans l'arbre Mojo# cachent", /*spanish*/"entre #telarañas del Gran Árbol Deku# yace", /*italian*/"una #ragnatela nell'Albero Deku# copre", /*german*/"unterhalb von #Spinnenweben# des Deku-Baumes, |wäre|wären|"},
    });

    hintTable[DEKU_TREE_MQ_BEFORE_SPINNING_LOG_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#magical fire in the Deku Tree# leads to", /*french*/"le #feu magique dans l'arbre Mojo# éclaire", /*spanish*/"el #fuego mágico en el Gran Árbol Deku# conduce a", /*italian*/"con del #fuoco magico nell'Albero Deku# si |può|possono| ottenere", /*german*/"nahe eines #drehenden Stammes# des Deku-Baumes, |wäre|wären|"},
    });

    hintTable[DEKU_TREE_QUEEN_GOHMA_HEART] = HintText::Exclude({
                       // obscure text
                       Text{"the #Parasitic Armored Arachnid# holds", /*french*/"le #monstre insectoïde géant# possède", /*spanish*/"el #arácnido parasitario acorazado# porta", /*italian*/"il #parassita corazzato# possiede", /*german*/"nahe dem #gepanzerten Spinnenparasiten#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"#Queen Gohma# holds", /*french*/"la #Reine Gohma# possède", /*spanish*/"la #Reina Goma# porta", /*italian*/"#Gohma# possiede", /*german*/"nahe der #Spinnenkönigin Gohma#, |wäre|wären|"}
    );

    hintTable[DEKU_TREE_GS_BASEMENT_BACK_ROOM] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider deep within the Deku Tree# hides", /*french*/"une #Skulltula au cœur de l'arbre Mojo# a", /*spanish*/"una #Skulltula en las profundidades del Árbol Deku# otorga", /*italian*/"un #ragno nelle profondità dell'Albero Deku# nasconde", /*german*/"in einer #Spinne, tief im Deku-Baum#, |wäre|wären|"},
    });

    hintTable[DEKU_TREE_GS_BASEMENT_GATE] = HintText::Exclude({
                       // obscure text
                       Text{"a #web protects a spider# within the Deku Tree holding", /*french*/"une #Skulltula derrière une toile dans l'arbre Mojo# a", /*spanish*/"una #Skulltula protegida por su tela# del Árbol Deku otorga", /*italian*/"un #ragno vicino all'acqua# nell'Albero Deku nasconde", /*german*/"in einer #Spinne, geschützt von einem Netz# des Deku-Baumes, |wäre|wären|"},
    });

    hintTable[DEKU_TREE_GS_BASEMENT_VINES] = HintText::Exclude({
                       // obscure text
                       Text{"a #web protects a spider# within the Deku Tree holding", /*french*/"une #Skulltula derrière une toile dans l'arbre Mojo# a", /*spanish*/"una #Skulltula protegida por su tela# del Árbol Deku otorga", /*italian*/"un #ragno vicino all'acqua# nell'Albero Deku nasconde", /*german*/"in einer #Spinne, geschützt von einem Netz# des Deku-Baumes, |wäre|wären|"},
    });

    hintTable[DEKU_TREE_GS_COMPASS_ROOM] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider atop the Deku Tree# holds", /*french*/"une #Skulltula au sommet de l'arbre Mojo# a", /*spanish*/"una #Skulltula en lo alto del Árbol Deku# otorga", /*italian*/"un #ragno in cima all'Albero Deku# nasconde", /*german*/"in einer #Spinne, im oberen Teil des Deku-Baumes#, |wäre|wären|"},
    });


    hintTable[DEKU_TREE_MQ_GS_LOBBY] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider in a crate# within the Deku Tree hides", /*french*/"une #Skulltula dans une boîte dans l'arbre Mojo# a", /*spanish*/"una #Skulltula bajo una caja# del Árbol Deku otorga", /*italian*/"un #ragno in una cassa# nell'Albero Deku nasconde", /*german*/"in der #Spinne, in einer Kiste# des Deku-Baumes, |wäre|wären|"},
    });

    hintTable[DEKU_TREE_MQ_GS_COMPASS_ROOM] = HintText::Exclude({
                       // obscure text
                       Text{"a #wall of rock protects a spider# within the Deku Tree holding", /*french*/"une #Skulltula derrière des rochers dans l'arbre Mojo# a", /*spanish*/"una #Skulltula protegida por una pared rocosa# del Árbol Deku otorga", /*italian*/"un #ragno dietro dei massi# nell'Albero Deku nasconde", /*german*/"in einer #Spinne, geschützt von einer Felswand# des Deku-Baumes, |wäre|wären|"},
    });

    hintTable[DEKU_TREE_MQ_GS_BASEMENT_BACK_ROOM] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider deep within the Deku Tree# hides", /*french*/"une #Skulltula au cœur de l'arbre Mojo# a", /*spanish*/"una #Skulltula en las profundidades del Árbol Deku# otorga", /*italian*/"un #ragno nelle profondità dell'Albero Deku# nasconde", /*german*/"in einer #Spinne, tief im Deku-Baum#, |wäre|wären|"},
    });

    hintTable[DEKU_TREE_MQ_DEKU_SCRUB] = HintText::Exclude({
                       // obscure text
                       Text{"a #scrub in the Deku Tree# sells", /*french*/"la #peste Mojo dans l'arbre Mojo# vend", /*spanish*/"un #deku del Gran Árbol Deku# vende", /*italian*/"un #cespuglio nell'Albero Deku# vende", /*german*/"die Ware, eines #Deku-Händlers des Deku-Baumes#, |wäre|wären|"},
    });

    /*--------------------------
    |     DODONGOS CAVERN      |
    ---------------------------*/
    hintTable[DODONGOS_CAVERN_BOSS_ROOM_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#above King Dodongo# lies", /*french*/"#par dessus le Roi Dodongo# gît", /*spanish*/"#sobre el Rey Dodongo# yace", /*italian*/"#sopra il Mega Dodongo# puoi trovare", /*german*/"#überhalb von King Dodongo#, |wäre|wären|"},
    });

    hintTable[DODONGOS_CAVERN_MAP_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #muddy wall in Dodongo's Cavern# hides", /*french*/"le #mur fragile dans la caverne Dodongo# recèle", /*spanish*/"tras una #agrietada pared en la Cueva de los Dodongos# yace", /*italian*/"una #parete friabile nella caverna dei Dodongo# nasconde", /*german*/"hinter einer #brüchigen Wand in Dodongos Höhle#, |wäre|wären|"},
    });

    hintTable[DODONGOS_CAVERN_COMPASS_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #statue in Dodongo's Cavern# guards", /*french*/"la #statue dans la caverne Dodongo# protège", /*spanish*/"una #estatua de la Cueva de los Dodongos# esconde", /*italian*/"una #statua nella caverna dei Dodongo# protegge", /*german*/"nahe einer #Statue in Dodongos Höhle#, |wäre|wären|"},
    });

    hintTable[DODONGOS_CAVERN_BOMB_FLOWER_PLATFORM_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"above a #maze of stone# in Dodongo's Cavern lies", /*french*/"sur #un labyrinthe de pierre# dans la caverne Dodongo gît", /*spanish*/"entre un #laberinto de piedra# en la Cueva de los Dodongos yace", /*italian*/"sopra #un dedalo di pietra nella caverna dei Dodongo# puoi trovare", /*german*/"überhalb eines #steinernen Irrgartens# in Dodongos Höhle, |wäre|wären|"},
    });

    hintTable[DODONGOS_CAVERN_BOMB_BAG_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #second lizard cavern battle# yields", /*french*/"le #deuxième duel de lézards de caverne# octroie", /*spanish*/"#luchar dos veces contra reptiles en una cueva# conduce a", /*italian*/"il #secondo gruppo di lucertole di caverna# protegge", /*german*/"nahe des #zweiten Höhlenkampfes mit Echsen#, |wäre|wären|"},
    });

    hintTable[DODONGOS_CAVERN_END_OF_BRIDGE_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #chest at the end of a bridge# yields", /*french*/"le #trésor à l'extrémité d'un pont# contient", /*spanish*/"un #cofre al final de un quebrado puente# contiene", /*italian*/"un #forziere alla fine di un ponte# contiene", /*german*/"in einer #Truhe, am Ende einer Brücke#, |wäre|wären|"},
    });


    hintTable[DODONGOS_CAVERN_MQ_MAP_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #muddy wall in Dodongo's Cavern# hides", /*french*/"le #mur fragile dans la caverne Dodongo# recèle", /*spanish*/"una #agrietada pared en la Cueva de los Dodongos# esconde", /*italian*/"una #parete friabile nella caverna dei Dodongo# nasconde", /*german*/"hinter einer #brüchigen Wand in Dodongos Höhle#, |wäre|wären|"},
    });

    hintTable[DODONGOS_CAVERN_MQ_BOMB_BAG_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"an #elevated alcove# in Dodongo's Cavern holds", /*french*/"l'#alcove haut perchée# dans la caverne Dodongo cache", /*spanish*/"una #elevada alcoba# en la Cueva de los Dodongos brinda", /*italian*/"dal #centro della caverna dei Dodongo# puoi vedere un forziere contenente", /*german*/"in einer #erhöhten Nische# in Dodongos Höhle, |wäre|wären|"},
    });

    hintTable[DODONGOS_CAVERN_MQ_COMPASS_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#fire-breathing lizards# in Dodongo's Cavern guard", /*french*/"les #lézards cracheurs de feu# dans la caverne Dodongo protègent", /*spanish*/"unos #flamígeros reptiles# en la Cueva de los Dodongos esconden", /*italian*/"#lucertole sputafuoco nella caverna dei Dodongo# proteggono", /*german*/"nahe #feuerspuckender Echsen# in Dodongos Höhle, |wäre|wären|"},
    });

    hintTable[DODONGOS_CAVERN_MQ_LARVAE_ROOM_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#baby spiders# in Dodongo's Cavern guard", /*french*/"les #petites araignées dans la caverne Dodongo# protègent", /*spanish*/"unas #pequeñas larvas# en la Cueva de los Dodongos esconden", /*italian*/"#piccoli parassiti# nella caverna dei Dodongo proteggono", /*german*/"nahe #Babyspinnen# in Dodongos Höhle, |wäre|wären|"},
    });

    hintTable[DODONGOS_CAVERN_MQ_TORCH_PUZZLE_ROOM_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"above a #maze of stone# in Dodongo's Cavern lies", /*french*/"sur #un labyrinthe de pierre# dans la caverne Dodongo gît", /*spanish*/"sobre un #laberinto de piedra# en la Cueva de los Dodongos yace", /*italian*/"sopra #un dedalo di pietra nella caverna dei Dodongo# puoi trovare", /*german*/"über einem #steinernen Irrgarten# in Dodongos Höhle, |wäre|wären|"},
    });

    hintTable[DODONGOS_CAVERN_MQ_UNDER_GRAVE_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#beneath a headstone# in Dodongo's Cavern lies", /*french*/"#sous une pierre tombale# dans la caverne Dodongo gît", /*spanish*/"#bajo una lápida# en la Cueva de los Dodongos yace", /*italian*/"#sotto una lapide# nella caverna dei Dodongo |giace|giacciono|", /*german*/"#unter einem Grabstein# in Dodongos Höhle, |wäre|wären|"},
    });

    hintTable[DODONGOS_CAVERN_KING_DODONGO_HEART] = HintText::Exclude({
                       // obscure text
                       Text{"the #Infernal Dinosaur# holds", /*french*/"le #dinosaure infernal# possède", /*spanish*/"el #dinosaurio infernal# porta", /*italian*/"il #dinosauro degli inferi# possiede", /*german*/"nahe dem #Infernosaurus#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"#King Dodongo# holds", /*french*/"le #Roi Dodongo# possède", /*spanish*/"el #Rey Dodongo# porta", /*italian*/"il #Mega Dodongo# possiede", /*german*/"nahe #King Dodongo#, |wäre|wären|"}
    );

    hintTable[DODONGOS_CAVERN_GS_VINES_ABOVE_STAIRS] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider entangled in vines# in Dodongo's Cavern guards", /*french*/"une #Skulltula sur les vignes dans la caverne Dodongo# a", /*spanish*/"una #Skulltula sobre unas cepas# de la Cueva de los Dodongos otorga", /*italian*/"un #ragno su dei rampicanti# nella caverna dei Dodongo nasconde", /*german*/"in einer, #in Reben verstrickten Spinne# in Dodongos Höhle, |wäre|wären|"},
    });

    hintTable[DODONGOS_CAVERN_GS_SCARECROW] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider among explosive slugs# hides", /*french*/"une #Skulltula dans l'alcove du couloir dans la caverne Dodongo# a", /*spanish*/"una #Skulltula rodeada de explosivos gusanos# otorga", /*italian*/"un #ragno fra lumache esplosive# nella caverna dei Dodongo protegge", /*german*/"in einer, #außer Reichweite liegenden Spinne# in Dodongos Höhle, |wäre|wären|"},
    });

    hintTable[DODONGOS_CAVERN_GS_ALCOVE_ABOVE_STAIRS] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider just out of reach# in Dodongo's Cavern holds", /*french*/"une #Skulltula au haut des escaliers de la caverne Dodongo# a", /*spanish*/"una #Skulltula fuera del alcance# de la Cueva de los Dodongos otorga", /*italian*/"un #ragno in cima alle scale mobili# possiede", /*german*/"in einer, #außer Reichweite liegenden Spinne# in Dodongos Höhle, |wäre|wären|"},
    });

    hintTable[DODONGOS_CAVERN_GS_BACK_ROOM] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider behind a statue# in Dodongo's Cavern holds", /*french*/"une #Skulltula au cœur de la caverne Dodongo# a", /*spanish*/"una #Skulltula tras una estatua# de la Cueva de los Dodongos otorga", /*italian*/"un #ragno si nasconde dietro una statua# nella caverna dei Dodongo con", /*german*/"in einer, #hinter einer Statue versteckten Spinne# in Dodongos Höhle, |wäre|wären|"},
    });

    hintTable[DODONGOS_CAVERN_GS_SIDE_ROOM_NEAR_LOWER_LIZALFOS] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider among bats# in Dodongo's Cavern holds", /*french*/"une #Skulltula entourée de Saigneurs dans la caverne Dodongo# a", /*spanish*/"una #Skulltula rodeada de murciélagos# de la Cueva de los Dodongos otorga", /*italian*/"un #ragno in mezzo ai pipistrelli# nella caverna dei Dodongo nasconde", /*german*/"in einer, #von Fledermäusen umgebenen Spinne# in Dodongos Höhle, |wäre|wären|"},
    });


    hintTable[DODONGOS_CAVERN_MQ_GS_SCRUB_ROOM] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider high on a wall# in Dodongo's Cavern holds", /*french*/"une #Skulltula haut perchée dans la caverne Dodongo# a", /*spanish*/"una #Skulltula en lo alto de una pared# de la Cueva de los Dodongos otorga", /*italian*/"un #ragno in alto su un muro# nella caverna dei Dodongo protegge", /*german*/"in einer, #an einer hohen Wand krabbelnden Spinne# in Dodongos Höhle, |wäre|wären|"},
    });

    hintTable[DODONGOS_CAVERN_MQ_GS_LIZALFOS_ROOM] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider on top of a pillar of rock# in Dodongo's Cavern holds", /*french*/"une #Skulltula sur l'énorme pilier de roc de la caverne Dodongo# a", /*spanish*/"una #Skulltula en lo alto de un pilar# de la Cueva de los Dodongos otorga", /*italian*/"un #ragno sopra una colonna di pietra# nella caverna dei Dodongo nasconde", /*german*/"in einer, #auf einer Steinsäule krabbelnden Spinne# in Dodongos Höhle, |wäre|wären|"},
    });

    hintTable[DODONGOS_CAVERN_MQ_GS_LARVAE_ROOM] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider in a crate# in Dodongo's Cavern holds", /*french*/"une #Skulltula dans une boîte de la caverne Dodongo# a", /*spanish*/"una #Skulltula bajo una caja# de la Cueva de los Dodongos otorga", /*italian*/"un #ragno in una cassa# nella caverna dei Dodongo nasconde", /*german*/"in der #Spinne, einer Kiste# in Dodongos Höhle, |wäre|wären|"},
    });

    hintTable[DODONGOS_CAVERN_MQ_GS_BACK_AREA] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider among graves# in Dodongo's Cavern holds", /*french*/"une #Skulltula parmi les tombes de la caverne Dodongo# a", /*spanish*/"una #Skulltula entre lápidas# en la Cueva de los Dodongos otorga", /*italian*/"un #ragno fra le lapidi# nella caverna dei Dodongo nasconde", /*german*/"in einer #Spinne, nahe Gräbern# in Dodongos Höhle, |wäre|wären|"},
    });

    hintTable[DODONGOS_CAVERN_DEKU_SCRUB_NEAR_BOMB_BAG_LEFT] = HintText::Exclude({
                       // obscure text
                       Text{"a pair of #scrubs in Dodongo's Cavern# sells", /*french*/"le #duo de peste Mojo dans la caverne Dodongo# vend", /*spanish*/"un #par de dekus en la Cueva de los Dodongos# venden", /*italian*/"una #coppia di cespugli# nella caverna dei Dodongo vende", /*german*/"die Ware, eines #Deku-Händler-Duos in Dodongos Höhle#, |wäre|wären|"},
    });

    hintTable[DODONGOS_CAVERN_DEKU_SCRUB_SIDE_ROOM_NEAR_DODONGOS] = HintText::Exclude({
                       // obscure text
                       Text{"a #scrub guarded by Lizalfos# sells", /*french*/"la #peste Mojo au cœur de la caverne Dodongo# vend", /*spanish*/"un #deku custodiado por Lizalfos# vende", /*italian*/"un #cespuglio solitario vicino ai Dodongo# nell'omonima caverna vende", /*german*/"die Ware, eines #von Lizalfos beschützten Deku-Händlers#, |wäre|wären|"},
    });

    hintTable[DODONGOS_CAVERN_DEKU_SCRUB_NEAR_BOMB_BAG_RIGHT] = HintText::Exclude({
                       // obscure text
                       Text{"a pair of #scrubs in Dodongo's Cavern# sells", /*french*/"le #duo de peste Mojo dans la caverne Dodongo# vend", /*spanish*/"un #par de dekus en la Cueva de los Dodongos# venden", /*italian*/"una #coppia di cespugli# nella caverna dei Dodongo vende", /*german*/"die Ware, eines #Deku-Händler-Duos in Dodongos Höhle#, |wäre|wären|"},
    });

    hintTable[DODONGOS_CAVERN_DEKU_SCRUB_LOBBY] = HintText::Exclude({
                       // obscure text
                       Text{"a #scrub in Dodongo's Cavern# sells", /*french*/"la #peste Mojo dans l'entrée de la caverne Dodongo# vend", /*spanish*/"un #deku en la Cueva de los Dodongos# vende", /*italian*/"un #cespuglio solitario# vicino all'ingresso della caverna dei Dodongo vende", /*german*/"die Ware, eines #Deku-Händlers in Dodongos Höhle#, |wäre|wären|"},
    });


    hintTable[DODONGOS_CAVERN_MQ_DEKU_SCRUB_LOBBY_REAR] = HintText::Exclude({
                       // obscure text
                       Text{"a pair of #scrubs in Dodongo's Cavern# sells", /*french*/"le #duo de peste Mojo dans l'entrée de la caverne Dodongo# vend", /*spanish*/"un #par de dekus en la Cueva de los Dodongos# venden", /*italian*/"una #coppia di cespugli# nella caverna dei Dodongo vende", /*german*/"die Ware, eines #Deku-Händler-Duos in Dodongos Höhle#, |wäre|wären|"},
    });

    hintTable[DODONGOS_CAVERN_MQ_DEKU_SCRUB_LOBBY_FRONT] = HintText::Exclude({
                       // obscure text
                       Text{"a pair of #scrubs in Dodongo's Cavern# sells", /*french*/"le #duo de peste Mojo dans l'entrée de la caverne Dodongo# vend", /*spanish*/"un #par de dekus en la Cueva de los Dodongos# venden", /*italian*/"una #coppia di cespugli# nella caverna dei Dodongo vende", /*german*/"die Ware, eines #Deku-Händler-Duos in Dodongos Höhle#, |wäre|wären|"},
    });

    hintTable[DODONGOS_CAVERN_MQ_DEKU_SCRUB_STAIRCASE] = HintText::Exclude({
                       // obscure text
                       Text{"a #scrub in Dodongo's Cavern# sells", /*french*/"la #peste Mojo au sommet des escaliers dans la caverne Dodongo# vend", /*spanish*/"un #deku en la Cueva de los Dodongos# vende", /*italian*/"un #cespuglio in cima alle scale mobili# vende", /*german*/"die Ware, eines #Deku-Händlers in Dodongos Höhle#, |wäre|wären|"},
    });

    hintTable[DODONGOS_CAVERN_MQ_DEKU_SCRUB_SIDE_ROOM_NEAR_LOWER_LIZALFOS] = HintText::Exclude({
                       // obscure text
                       Text{"a #scrub guarded by Lizalfos# sells", /*french*/"la #peste Mojo au cœur de la caverne Dodongo# vend", /*spanish*/"un #deku custodiado por Lizalfos# vende", /*italian*/"un #cespuglio vicino ai Lizalfos# della caverna dei Dodongo vende", /*german*/"die Ware, eines #von Lizalfos beschützten Deku-Händlers#, |wäre|wären|"},
    });

    /*--------------------------
    |     JABU JABUS BELLY     |
    ---------------------------*/
    hintTable[JABU_JABUS_BELLY_MAP_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#tentacle trouble# in a deity's belly guards", /*french*/"la #membrane# dans le ventre du gardien protège", /*spanish*/"un #problema tentaculoso# en la tripa de cierta deidad esconde", /*italian*/"bisogna risolvere un #problema di tentacoli# per ottenere", /*german*/"nahe eines #Tentakelproblems# im Bauche einer Gottheit, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"a #slimy thing# guards", /*french*/"la #chose gluante# gardien protège", /*spanish*/"un #tentáculo parasitario# protege", /*italian*/"un #coso rosso# protegge", /*german*/"nahe eines #schleimigen Dings#, |wäre|wären|"}
    );

    hintTable[JABU_JABUS_BELLY_COMPASS_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#bubble trouble# in a deity's belly guards", /*french*/"un #horde de bulles# dans le ventre du gardien protègent", /*spanish*/"un #problema burbujesco# en la tripa de cierta deidad esconde", /*italian*/"bisogna risolvere un #problema di bolle# per ottenere", /*german*/"nahe eines #Blubberblasenproblems# im Bauche einer Gottheit, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"#bubbles# guard", /*french*/"des #bulles# entourent", /*spanish*/"unas #burbujas# protegen", /*italian*/"gli #shabom# proteggono", /*german*/"nahe #Blubberblasen#, |wäre|wären|"}
    );


    hintTable[JABU_JABUS_BELLY_MQ_FIRST_ROOM_SIDE_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"shooting a #mouth cow# reveals", /*french*/"tirer sur une #vache# révèle", /*spanish*/"#dispararle a una vaca# revela", /*italian*/"sparare a una #mucca in bocca# rivela", /*german*/"nahe einer #Kuh im Maule# einer Gottheit, |wäre|wären|"},
    });

    hintTable[JABU_JABUS_BELLY_MQ_MAP_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#pop rocks# hide",            /*french*/"des #pierres aux reins# cachent",     /*spanish*/"#cepillarse los dientes con explosivos# revela", /*italian*/"#gargarismi esplosivi# rivelano", /*german*/"eine #prickelnde Entdeckung# einer Gottheit, |wäre|wären|"},
                       Text{"an #explosive palate# holds", /*french*/"des #gargouillis explosifs# cachent", /*spanish*/"un #paladar explosivo# esconde",                 /*italian*/"un #groppo in gola# nasconde",    /*german*/"ein #explosiver Geschmack#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"a #boulder before cows# hides", /*french*/"des #rochers près des vaches# cachent", /*spanish*/"cierta #roca rodeada de vacas# esconde", /*italian*/"un #macigno nella bocca di Jabu Jabu# nasconde", /*german*/"unter einem #Felsen im Maule# einer Gottheit, |wäre|wären|"}
    );

    hintTable[JABU_JABUS_BELLY_MQ_SECOND_ROOM_LOWER_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"near a #spiked elevator# lies", /*french*/"près d'un #ascenseur visqueux# gît", /*spanish*/"cerca de un #ascensor puntiagudo# yace", /*italian*/"un forziere sotto un #ascensore spinoso# contiene", /*german*/"nahe eines #stacheligen Aufzugs#, |wäre|wären|"},
    });

    hintTable[JABU_JABUS_BELLY_MQ_COMPASS_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #drowning cow# unveils", /*french*/"une #vache à l'eau# a", /*spanish*/"una #vaca sumergida# revela", /*italian*/"una #mucca sommozzatrice# fa apparire", /*german*/"nahe einer #ertrinkenden Kuh#, |wäre|wären|"},
    });

    hintTable[JABU_JABUS_BELLY_MQ_SECOND_ROOM_UPPER_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#moving anatomy# creates a path to", /*french*/"un #organe descendant# mène à", /*spanish*/"un #ser movedizo entre paredes# conduce a", /*italian*/"un #intervento chirurgico# apre la via per", /*german*/"nahe sich #bewegender Anatomie#, |wäre|wären|"},
    });

    hintTable[JABU_JABUS_BELLY_MQ_BASEMENT_NEAR_SWITCHES_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #pair of digested cows# hold", /*french*/"#deux bœufs digérés# détiennent", /*spanish*/"un #par de digeridas vacas# otorgan", /*italian*/"una #coppia di mucche digerite# nasconde", /*german*/"nahe #zwei halb-verdauten Kühen#, |wäre|wären|"},
    });

    hintTable[JABU_JABUS_BELLY_MQ_BASEMENT_NEAR_VINES_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #pair of digested cows# hold", /*french*/"#deux bœufs digérés# détiennent", /*spanish*/"un #par de digeridas vacas# otorgan", /*italian*/"una #coppia di mucche digerite# nasconde", /*german*/"nahe #zwei halb-verdauten Kühen#, |wäre|wären|"},
    });

    hintTable[JABU_JABUS_BELLY_MQ_NEAR_BOSS_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #final cows' reward# in a deity's belly is", /*french*/"le #cadeau des dernières vaches# estomacales est", /*spanish*/"las #vacas al final# de la tripa de cierta deidad otorgan", /*italian*/"il #premio dell'ultima mucca inghiottita# è", /*german*/"nahe #den letzten Kühen# im Bauche einer Gottheit, |wäre|wären|"},
    });

    hintTable[JABU_JABUS_BELLY_MQ_FALLING_LIKE_LIKE_ROOM_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#cows protected by falling monsters# in a deity's belly guard", /*french*/"des #vaches protégées par des monstres tombants# cachent", /*spanish*/"unas #vacas custodiadas por monstruos del techo# de la tripa de cierta deidad otorgan", /*italian*/"delle #mucche inghiottite liberano dei mostri# per difendere", /*german*/"nahe, von #herabfallenden Monstern beschützten Kühen#, |wäre|wären|"},
    });

    hintTable[JABU_JABUS_BELLY_MQ_BOOMERANG_ROOM_SMALL_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a school of #stingers swallowed by a deity# guard", /*french*/"les #raies avallées par le gardien# protègent", /*spanish*/"unos #stingers engullidos por cierta deidad# guardan", /*italian*/"una divinità ha inghiottito #un banco di trigoni volanti# con", /*german*/"nahe eines #verschluckten Fischschwarms#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"a school of #stingers swallowed by Jabu-Jabu# guard", /*french*/"les #raies avallées par Jabu-Jabu# protègent", /*spanish*/"unos #stingers engullidos por Jabu-Jabu# guardan", /*italian*/"#un banco di trigoni volanti# nella pancia di Jabu Jabu protegge", /*german*/"nahe #Fischen in Jabu-Jabus Bauch#, |wäre|wären|"}
    );

    hintTable[JABU_JABUS_BELLY_MQ_BOOMERANG_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a school of #stingers swallowed by a deity# guard", /*french*/"les #raies avallées par le gardien# protègent", /*spanish*/"unos #stingers engullidos por cierta deidad# guardan", /*italian*/"una divinità ha inghiottito #un banco di trigoni volanti# con", /*german*/"nahe eines #verschluckten Fischschwarms#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"a school of #stingers swallowed by Jabu-Jabu# guard", /*french*/"les #raies avallées par Jabu-Jabu# protègent", /*spanish*/"unos #stingers engullidos por Jabu-Jabu# guardan", /*italian*/"#un banco di trigoni volanti# nella pancia di Jabu Jabu protegge", /*german*/"nahe #Fischen in Jabu-Jabus Bauch#, |wäre|wären|"}
    );

    hintTable[JABU_JABUS_BELLY_BARINADE_HEART] = HintText::Exclude({
                       // obscure text
                       Text{"the #Bio-Electric Anemone# holds", /*french*/"l'#anémone bioélectrique# possède", /*spanish*/"la #anémona bioeléctrica# porta", /*italian*/"l'#anemone bio-elettrico# possiede", /*german*/"nahe dem #elektroterrestrischen Biotentakel#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"#Barinade# holds", /*french*/"#Barinade# possède", /*spanish*/"#Barinade# porta", /*italian*/"#Cnidade# possiede", /*german*/"nahe #Barinade#, |wäre|wären|"}
    );

    hintTable[JABU_JABUS_BELLY_GS_LOBBY_BASEMENT_LOWER] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider resting near a princess# in Jabu-Jabu's Belly holds", /*french*/"une #Skulltula près de la princesse dans le ventre de Jabu-Jabu# a", /*spanish*/"una #Skulltula junto a una princesa# en la Tripa de Jabu-Jabu otorga", /*italian*/"un #ragno vicino a una principessa# nella pancia di Jabu Jabu ha", /*german*/"in einer #Spinne, nahe einer Prinzessin# in Jabu-Jabus Bauch, |wäre|wären|"},
    });

    hintTable[JABU_JABUS_BELLY_GS_LOBBY_BASEMENT_UPPER] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider resting near a princess# in Jabu-Jabu's Belly holds", /*french*/"une #Skulltula près de la princesse dans le ventre de Jabu-Jabu# a", /*spanish*/"una #Skulltula junto a una princesa# en la Tripa de Jabu-Jabu otorga", /*italian*/"un #ragno vicino a una principessa# nella pancia di Jabu Jabu ha", /*german*/"in einer #Spinne, nahe einer Prinzessin# in Jabu-Jabus Bauch, |wäre|wären|"},
    });

    hintTable[JABU_JABUS_BELLY_GS_NEAR_BOSS] = HintText::Exclude({
                       // obscure text
                       Text{"#jellyfish surround a spider# holding", /*french*/"une #Skulltula entourée de méduses dans le ventre de Jabu-Jabu# a", /*spanish*/"una #Skulltula rodeada de medusas# otorga", /*italian*/"un #ragno circondato da meduse# possiede", /*german*/"in einer #Spinne nahe Quallen#, |wäre|wären|"},
    });

    hintTable[JABU_JABUS_BELLY_GS_WATER_SWITCH_ROOM] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider guarded by a school of stingers# in Jabu-Jabu's Belly holds", /*french*/"une #Skulltula protégée par des raies dans le ventre de Jabu-Jabu# a", /*spanish*/"una #Skulltula rodeada por unos stingers# en la Tripa de Jabu-Jabu otorga", /*italian*/"un #ragno protetto da trigoni volanti# nasconde", /*german*/"in einer #Spinne, nahe eines Fischschwarms# in Jabu-Jabus Bauch"},
    });


    hintTable[JABU_JABUS_BELLY_MQ_GS_TAILPASARAN_ROOM] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider surrounded by electricity# in Jabu-Jabu's Belly holds", /*french*/"une #Skulltula entourée d'électricité dans le ventre de Jabu-Jabu# a", /*spanish*/"una #Skulltula rodeada de electricidad# en la Tripa de Jabu-Jabu otorga", /*italian*/"un #ragno circondato da trivolt# nasconde", /*german*/"in einer, #von Elektrizität umgebenen Spinne# in Jabu-Jabus Bauch, |wäre|wären|"},
    });

    hintTable[JABU_JABUS_BELLY_MQ_GS_BOOMERANG_CHEST_ROOM] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider guarded by a school of stingers# in Jabu-Jabu's Belly holds", /*french*/"une #Skulltula protégée par des raies dans le ventre de Jabu-Jabu# a", /*spanish*/"una #Skulltula protegida por unos stingers# en la Tripa de Jabu-Jabu otorga", /*italian*/"un #ragno protetto da trigoni volanti# nasconde", /*german*/"in einer #Spinne, nahe eines Fischschwarms# in Jabu-Jabus Bauch"},
    });

    hintTable[JABU_JABUS_BELLY_MQ_GS_NEAR_BOSS] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider in a web within Jabu-Jabu's Belly# holds", /*french*/"une #Skulltula sur une toile dans le ventre de Jabu-Jabu# a", /*spanish*/"una #Skulltula sobre una red# en la Tripa de Jabu-Jabu otorga", /*italian*/"un #ragno sopra una rete# nella pancia di Jabu Jabu nasconde", /*german*/"in einer, #Spinne in einem Netz in Jabu-Jabus Bauch#, |wäre|wären|"},
    });

    hintTable[JABU_JABUS_BELLY_DEKU_SCRUB] = HintText::Exclude({
                       // obscure text
                       Text{"a #scrub in a deity# sells", /*french*/"la #peste Mojo dans le ventre du gardien# vend", /*spanish*/"un #deku dentro de cierta deidad# vende", /*italian*/"un #cespuglio inghiottito# vende", /*german*/"die Ware, eines #Deku-Händlers in einer Gottheit#, |wäre|wären|"},
    });

    /*--------------------------
    |      FOREST TEMPLE       |
    ---------------------------*/
    hintTable[FOREST_TEMPLE_FIRST_ROOM_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #tree in the Forest Temple# supports", /*french*/"sur l'#arbre dans le temple de la forêt# gît", /*spanish*/"sobre un #árbol del Templo del Bosque# yace", /*italian*/"un #albero nel Santuario della Foresta# sostiene", /*german*/"auf einem #Baum des Waldtempels#, |wäre|wären|"},
    });

    hintTable[FOREST_TEMPLE_FIRST_STALFOS_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#defeating enemies beneath a falling ceiling# in Forest Temple yields", /*french*/"#deux squelettes# dans le temple de la forêt protègent", /*spanish*/"#derrotar enemigos caídos de lo alto# del Templo del Bosque revela", /*italian*/"dei #mostri sotto un ottagono mobile# nel Santuario della Foresta difendono", /*german*/"unterhalb einer #fallenden Decke# des Waldtempels, |wäre|wären|"},
    });

    hintTable[FOREST_TEMPLE_WELL_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #sunken chest deep in the woods# contains", /*french*/"le #coffre submergé dans la forêt# contient", /*spanish*/"un #sumergido cofre en lo profundo del bosque# contiene", /*italian*/"un #forziere sommerso nel cuore della foresta# contiene", /*german*/"in einer #versunkenen Truhe tief im Wald#, |wäre|wären|"},
    });

    hintTable[FOREST_TEMPLE_MAP_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #fiery skull# in Forest Temple guards", /*french*/"le #crâne enflammé# dans le temple de la forêt protège", /*spanish*/"una #ardiente calavera# del Templo del Bosque esconde", /*italian*/"un #teschio focoso# nel Santuario della Foresta protegge", /*german*/"nahe eines #feurigen Schädels# des Waldtempels, |wäre|wären|"},
    });

    hintTable[FOREST_TEMPLE_RAISED_ISLAND_COURTYARD_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #chest on a small island# in the Forest Temple holds", /*french*/"le #coffre sur l'îlot# du temple de la forêt contient", /*spanish*/"un #cofre sobre una isla# del Templo del Bosque contiene", /*italian*/"un #forziere su una piccola isola# nel Santuario della Foresta contiene", /*german*/"in einer #Truhe, auf einer kleinen Insel# des Waldtempels, |wäre|wären|"},
    });

    hintTable[FOREST_TEMPLE_FALLING_CEILING_ROOM_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"beneath a #checkerboard falling ceiling# lies", /*french*/"sous #l'échiquier tombant# gît", /*spanish*/"tras un #techo de ajedrez# yace", /*italian*/"sotto una #scacchiera che cade# puoi trovare", /*german*/"unter einem #fallenden Schachbrett#, |wäre|wären|"},
    });

    hintTable[FOREST_TEMPLE_EYE_SWITCH_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #sharp eye# will spot", /*french*/"l'#oeil perçant# dans la forêt verra", /*spanish*/"un #afilado ojo# revela", /*italian*/"un #occhio acuto# nella foresta vede", /*german*/"nahe eines #geblendeten Auges# des Waldtempels, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"#blocks of stone# in the Forest Temple surround", /*french*/"les #blocs dans le temple de la forêt# entourent", /*spanish*/"cerca de unos #bloques de piedra# del Templo del Bosque yace", /*italian*/"#blocchi di pietra# nel Santuario della Foresta circondano", /*german*/"nahe #steinerner Blöcke# des Waldtempels, |wäre|wären|"}
    );

    hintTable[FOREST_TEMPLE_BOSS_KEY_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #turned trunk# contains", /*french*/"le #coffre pivoté# contient", /*spanish*/"en una #sala con otro punto de vista# se esconde", /*italian*/"un #baule basculante# contiene", /*german*/"in einem #verdrehten Baumstamm#, |wäre|wären|"},
    });

    hintTable[FOREST_TEMPLE_FLOORMASTER_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"deep in the forest #shadows guard a chest# containing", /*french*/"l'#ombre de la forêt# protège un coffre contenant", /*spanish*/"en lo profundo del bosque #unas sombras# esconden", /*italian*/"nel profondo della foresta una #mano mozza# protegge", /*german*/"nahe eines #Schattens, tief im Walde#, |wäre|wären|"},
    });

    hintTable[FOREST_TEMPLE_BOW_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"an #army of the dead# guards", /*french*/"des #squelettes sylvestres# protègent", /*spanish*/"un #ejército de soldados caídos# guarda", /*italian*/"un #esercito di morti# protegge", /*german*/"nahe der #Armee der Toten# des Waldtempels, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"#Stalfos deep in the Forest Temple# guard", /*french*/"#trois squelettes dans le temple de la forêt# protègent", /*spanish*/"los #Stalfos en lo profundo del Templo del Bosque# guardan", /*italian*/"#tre Stalfos# nel Santuario della Foresta proteggono", /*german*/"nahe #Stalfos, tief im Walde#, |wäre|wären|"}
    );

    hintTable[FOREST_TEMPLE_RED_POE_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#Joelle# guards", /*french*/"#Joelle# protège", /*spanish*/"#Joelle# guarda", /*italian*/"#Jo# protegge", /*german*/"nahe #Hetti#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"a #red ghost# guards", /*french*/"le #fantôme rouge# protège", /*spanish*/"un #espectro rojo# guarda", /*italian*/"uno #spettro rosso# protegge", /*german*/"nahe eines #roten Irrlichts#, |wäre|wären|"}
    );

    hintTable[FOREST_TEMPLE_BLUE_POE_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#Beth# guards", /*french*/"#Beth# protège", /*spanish*/"#Beth# guarda", /*italian*/"#Beth# protegge", /*german*/"nahe #Netti#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"a #blue ghost# guards", /*french*/"le #fantôme bleu# protège", /*spanish*/"un #espectro azul# guarda", /*italian*/"uno #spettro blu# protegge", /*german*/"nahe eines #blauen Irrlichts#, |wäre|wären|"}
    );

    hintTable[FOREST_TEMPLE_BASEMENT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#revolving walls# in the Forest Temple conceal", /*french*/"des #murs rotatifs dans la forêt# recèlent", /*spanish*/"las #paredes giratorias# del Templo del Bosque conceden", /*italian*/"#muri rotanti# nel Santuario della Foresta nascondono", /*german*/"nahe #drehbarer Wände# des Waldtempels, |wäre|wären|"},
    });


    hintTable[FOREST_TEMPLE_MQ_FIRST_ROOM_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #tree in the Forest Temple# supports", /*french*/"sur l'#arbre dans le temple de la forêt# gît", /*spanish*/"sobre un #árbol del Templo del Bosque# yace", /*italian*/"un #albero nel Santuario della Foresta# sostiene", /*german*/"auf einem #Baum des Waldtempels#, |wäre|wären|"},
    });

    hintTable[FOREST_TEMPLE_MQ_WOLFOS_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#defeating enemies beneath a falling ceiling# in Forest Temple yields", /*french*/"#deux squelettes# dans le temple de la forêt protègent", /*spanish*/"#derrotar enemigos caídos de lo alto# del Templo del Bosque revela", /*italian*/"dei #mostri sotto un ottagono mobile# nel Santuario della Foresta difendono", /*german*/"unterhalb einer #fallenden Decke# des Waldtempels, |wäre|wären|"},
    });

    hintTable[FOREST_TEMPLE_MQ_BOW_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"an #army of the dead# guards", /*french*/"des #squelettes sylvestres# protègent", /*spanish*/"un #ejército de soldados caídos# guarda", /*italian*/"un #esercito di morti# protegge", /*german*/"nahe der #Armee der Toten# des Waldtempels, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"#Stalfos deep in the Forest Temple# guard", /*french*/"#trois squelettes dans le temple de la forêt# protègent", /*spanish*/"los #Stalfos en lo profundo del Templo del Bosque# guardan", /*italian*/"#tre Stalfos# nel Santuario della Foresta proteggono", /*german*/"nahe #Stalfos, tief im Walde#, |wäre|wären|"}
    );

    hintTable[FOREST_TEMPLE_MQ_RAISED_ISLAND_COURTYARD_LOWER_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #chest on a small island# in the Forest Temple holds", /*french*/"le #coffre sur l'îlot# du temple de la forêt contient", /*spanish*/"un #cofre sobre una isla# del Templo del Bosque contiene", /*italian*/"un #forziere su una piccola isola# nel Santuario della Foresta contiene", /*german*/"in einer #Truhe, auf einer kleinen Insel# des Waldtempels, |wäre|wären|"},
    });

    hintTable[FOREST_TEMPLE_MQ_RAISED_ISLAND_COURTYARD_UPPER_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#high in a courtyard# within the Forest Temple is", /*french*/"#haut perché dans le jardin# du temple de la forêt gît", /*spanish*/"un #cofre en lo alto de un patio# del Templo del Bosque contiene", /*italian*/"un #forziere su un balcone# nel Santuario della Foresta contiene", /*german*/"#hoch oben im Innenhof# des Waldtempels, |wäre|wären|"},
    });

    hintTable[FOREST_TEMPLE_MQ_WELL_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #sunken chest deep in the woods# contains", /*french*/"le #coffre submergé dans la forêt# contient", /*spanish*/"un #sumergido cofre en lo profundo del bosque# contiene", /*italian*/"un #forziere sommerso nel cuore della foresta# contiene", /*german*/"in einer #versunkenen Truhe, tief im Walde#, |wäre|wären|"},
    });

    hintTable[FOREST_TEMPLE_MQ_MAP_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#Joelle# guards", /*french*/"#Joelle# protège", /*spanish*/"#Joelle# guarda", /*italian*/"#Jo# protegge", /*german*/"nahe #Hetti#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"a #red ghost# guards", /*french*/"le #fantôme rouge# protège", /*spanish*/"un #fantasma rojo# guarda", /*italian*/"uno #spettro rosso# protegge", /*german*/"nahe eines #roten Irrlichts#, |wäre|wären|"}
    );

    hintTable[FOREST_TEMPLE_MQ_COMPASS_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#Beth# guards", /*french*/"#Beth# protège", /*spanish*/"#Beth# guarda", /*italian*/"#Beth# protegge", /*german*/"nahe #Netti#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"a #blue ghost# guards", /*french*/"le #fantôme bleu# protège", /*spanish*/"un #fantasma azul# guarda", /*italian*/"uno #spettro blu# protegge", /*german*/"nahe eines #blauen Irrlichts#, |wäre|wären|"}
    );

    hintTable[FOREST_TEMPLE_MQ_FALLING_CEILING_ROOM_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"beneath a #checkerboard falling ceiling# lies", /*french*/"sous #l'échiquier tombant# gît", /*spanish*/"tras un #techo de ajedrez# yace", /*italian*/"sotto una #scacchiera che cade# puoi trovare", /*german*/"unter einem #fallenden Schachbrett#, |wäre|wären|"},
    });

    hintTable[FOREST_TEMPLE_MQ_BASEMENT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#revolving walls# in the Forest Temple conceal", /*french*/"des #murs rotatifs dans la forêt# recèlent", /*spanish*/"las #paredes giratorias# del Templo del Bosque conceden", /*italian*/"#muri rotanti# nel Santuario della Foresta nascondono", /*german*/"nahe #drehbarer Wände# des Waldtempels, |wäre|wären|"},
    });

    hintTable[FOREST_TEMPLE_MQ_REDEAD_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"deep in the forest #undead guard a chest# containing", /*french*/"des #revenants dans le temple de la forêt# protègent", /*spanish*/"en lo profundo del bosque #guardias del más allá# guardan", /*italian*/"nel profondo della foresta i #non morti# difendono", /*german*/"nahe eines #Zombies, tief im Walde#, |wäre|wären|"},
    });

    hintTable[FOREST_TEMPLE_MQ_BOSS_KEY_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #turned trunk# contains", /*french*/"le #coffre pivoté# contient", /*spanish*/"en una #sala con otro punto de vista# se esconde", /*italian*/"un #baule basculante# contiene", /*german*/"in einem #verdrehten Baumstamm#, |wäre|wären|"},
    });

    hintTable[FOREST_TEMPLE_PHANTOM_GANON_HEART] = HintText::Exclude({
                       // obscure text
                       Text{"the #Evil Spirit from Beyond# holds", /*french*/"l'#esprit maléfique de l'au-delà# possède", /*spanish*/"el #espíritu maligno de ultratumba# porta", /*italian*/"lo #spirito del male# possiede", /*german*/"nahe dem #reitenden Unheil#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"#Phantom Ganon# holds", /*french*/"#Ganon Spectral# possède", /*spanish*/"#Ganon Fantasma# porta", /*italian*/"#Spettro Ganon# possiede", /*german*/"nahe #Phantom-Ganon#, |wäre|wären|"}
    );

    hintTable[FOREST_TEMPLE_GS_RAISED_ISLAND_COURTYARD] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider on a small island# in the Forest Temple holds", /*french*/"une #Skulltula sur l'îlot du temple de la forêt# a", /*spanish*/"una #Skulltula sobre una pequeña isla# del Templo del Bosque otorga", /*italian*/"un #ragno su una piccola isola# nel Santuario della Foresta nasconde", /*german*/"in einer #Spinne, auf einer kleinen Insel# des Waldtempels, |wäre|wären|"},
    });

    hintTable[FOREST_TEMPLE_GS_FIRST_ROOM] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider high on a wall of vines# in the Forest Temple holds", /*french*/"une #Skulltula sur un mur de vignes du temple de la forêt# a", /*spanish*/"una #Skulltula en lo alto de una pared de cepas# del Templo del Bosque otorga", /*italian*/"un #ragno sull'edera# nel Santuario della Foresta tiene", /*german*/"in einer #Spinne des Waldtempels, hoch oben an einer Wand voller Reben#, |wäre|wären|"},
    });

    hintTable[FOREST_TEMPLE_GS_LEVEL_ISLAND_COURTYARD] = HintText::Exclude({
                       // obscure text
                       Text{"#stone columns# lead to a spider in the Forest Temple hiding", /*french*/"une #Skulltula haut perchée dans le jardin du temple de la forêt# a", /*spanish*/"unas #columnas del Templo del Bosque# conducen a una Skulltula que otorga", /*italian*/"un #ragno sopra colonne di pietra# nel Santuario della Foresta conserva", /*german*/"in einer Spinne, überhalb von #Steinsäulen# des Waldtempels, |wäre|wären|"},
    });

    hintTable[FOREST_TEMPLE_GS_LOBBY] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider among ghosts# in the Forest Temple guards", /*french*/"une #Skulltula dans la grande salle du temple de la forêt# a", /*spanish*/"una #Skulltula rodeada de fantasmas# del Templo del Bosque otorga", /*italian*/"un #ragno fra gli spettri# al centro del Santuario della Foresta custodisce", /*german*/"in einer #Spinne, nahe Irrlichtern# des Waldtempels, |wäre|wären|"},
    });

    hintTable[FOREST_TEMPLE_GS_BASEMENT] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider within revolving walls# in the Forest Temple holds", /*french*/"une #Skulltula derrière les murs pivotants du temple de la forêt# a", /*spanish*/"una #Skulltula entre paredes giratorias# del Templo del Bosque otorga", /*italian*/"un #ragno fra muri rotanti# nel Santuario della Foresta nasconde", /*german*/"in einer #Spinne, nahe drehbarer Wände# des Waldtempels, |wäre|wären|"},
    });


    hintTable[FOREST_TEMPLE_MQ_GS_FIRST_HALLWAY] = HintText::Exclude({
                       // obscure text
                       Text{"an #ivy-hidden spider# in the Forest Temple hoards", /*french*/"une #Skulltula près de l'entrée du temple de la forêt# a", /*spanish*/"una #Skulltula escondida entre cepas# del Templo del Bosque otorga", /*italian*/"un #ragno dopo altri tre# nel Santuario della Foresta protegge", /*german*/"in einer, #in Efeu versteckten Spinne# des Waldtempels, |wäre|wären|"},
    });

    hintTable[FOREST_TEMPLE_MQ_GS_BLOCK_PUSH_ROOM] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider in a hidden nook# within the Forest Temple holds", /*french*/"une #Skulltula dans un recoin caché du temple de la forêt# a", /*spanish*/"una #Skulltula en una esquina oculta# del Templo del Bosque otorga", /*italian*/"un #ragno in una nicchia laterale# nel Santuario della Foresta nasconde", /*german*/"in einer #Spinne, einer geheimen Nische# des Waldtempels, |wäre|wären|"},
    });

    hintTable[FOREST_TEMPLE_MQ_GS_RAISED_ISLAND_COURTYARD] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider on an arch# in the Forest Temple holds", /*french*/"une #Skulltula sur une arche du temple de la forêt# a", /*spanish*/"una #Skulltula sobre un arco# del Templo del Bosque otorga", /*italian*/"un #ragno su un'architrave# nel Santuario della Foresta custodisce", /*german*/"in einer #Spinne, eines Torbogens# des Waldtempels, |wäre|wären|"},
    });

    hintTable[FOREST_TEMPLE_MQ_GS_LEVEL_ISLAND_COURTYARD] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider on a ledge# in the Forest Temple holds", /*french*/"une #Skulltula dans le jardin du temple de la forêt# a", /*spanish*/"una #Skulltula en un borde# del Templo del Bosque otorga", /*italian*/"un #ragno sopra un pozzo# nel Santuario della Foresta nasconde", /*german*/"in einer #Spinne, eines Vorsprungs# des Waldtempels, |wäre|wären|"},
    });

    hintTable[FOREST_TEMPLE_MQ_GS_WELL] = HintText::Exclude({
                       // obscure text
                       Text{"#draining a well# in Forest Temple uncovers a spider with", /*french*/"une #Skulltula au fond du puits du temple de la forêt# a", /*spanish*/"#vaciar el pozo# del Templo del Bosque desvela una Skulltula que otorga", /*italian*/"un #ragno dentro un pozzo# nel Santuario della Foresta nasconde", /*german*/"in einer #Spinne, eines ausgetrockneten Brunnens# des Waldtempels, |wäre|wären|"},
    });

    /*--------------------------
    |       FIRE TEMPLE        |
    ---------------------------*/
    hintTable[FIRE_TEMPLE_NEAR_BOSS_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#near a dragon# is", /*french*/"#près d'un dragon# gît", /*spanish*/"#cerca de un dragón# yace", /*italian*/"#vicino a un drago# un forziere contiene", /*german*/"in der Nähe eines #Drachens#, |wäre|wären|"},
    });

    hintTable[FIRE_TEMPLE_FLARE_DANCER_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #Flare Dancer behind a totem# guards", /*french*/"le #Danse-Flamme derrière un totem# protège", /*spanish*/"el #Bailafuego tras unos tótems# esconde", /*italian*/"il #Fiammerino dietro un totem# protegge", /*german*/"nahe dem #Flammenderwisch, jenseits eines Totems#, |wäre|wären|"},
    });

    hintTable[FIRE_TEMPLE_BOSS_KEY_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #prison beyond a totem# holds", /*french*/"la #prison derrière un totem# contient", /*spanish*/"en una #prisión tras unos tótems# yace", /*italian*/"una #cella dietro un totem# contiene", /*german*/"in einer #Zelle jenseits eines Totems#, |wäre|wären|"},
    });

    hintTable[FIRE_TEMPLE_BIG_LAVA_ROOM_BLOCKED_DOOR_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#explosives over a lava pit# unveil", /*french*/"des #explosifs dans un lac de lave# révèlent", /*spanish*/"los #explosivos en un mar de llamas# revelan", /*italian*/"#esplosioni presso un lago di lava# rivelano", /*german*/"hinter einer #verdächtigen Wand einer Lavagrube#, |wäre|wären|"},
    });

    hintTable[FIRE_TEMPLE_BIG_LAVA_ROOM_LOWER_OPEN_DOOR_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #Goron trapped near lava# holds", /*french*/"le #Goron emprisonné près de la lave# a", /*spanish*/"un #goron atrapado cerca de un mar de llamas# guarda", /*italian*/"un #Goron prigioniero vicino a un lago di lava# possiede", /*german*/"nahe eines, #bei Lava eingesperrten Goronen#, |wäre|wären|"},
    });

    hintTable[FIRE_TEMPLE_BOULDER_MAZE_LOWER_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #Goron at the end of a maze# holds", /*french*/"le #Goron dans le labyrinthe# a", /*spanish*/"un #goron al final de un laberinto# guarda", /*italian*/"un #Goron all'estremità di un labirinto# possiede", /*german*/"nahe eines #Goronen, am Ende eines Irrgartens#, |wäre|wären|"},
    });

    hintTable[FIRE_TEMPLE_BOULDER_MAZE_UPPER_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #Goron above a maze# holds", /*french*/"le #Goron au dessus du labyrinthe# a", /*spanish*/"un #goron sobre un laberinto# guarda", /*italian*/"un #Goron sopra un labirinto# possiede", /*german*/"nahe eines #Goronen, überhalb eines Irrgartens#, |wäre|wären|"},
    });

    hintTable[FIRE_TEMPLE_BOULDER_MAZE_SIDE_ROOM_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #Goron hidden near a maze# holds", /*french*/"le #Goron caché près du labyrinthe# a", /*spanish*/"un #goron escondido tras un laberinto# guarda", /*italian*/"un #Goron vicino a un labirinto# possiede", /*german*/"nahe eines #Goronen bei einem Irrgarten#, |wäre|wären|"},
    });

    hintTable[FIRE_TEMPLE_BOULDER_MAZE_SHORTCUT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #blocked path# in Fire Temple holds", /*french*/"un #sol fragile dans le temple du feu# contient", /*spanish*/"en un #camino bloqueado# del Templo del Fuego yace", /*italian*/"#sotto un pavimento crepato# nel Santuario del Fuoco c'è un Goron con", /*german*/"in einer #nützlichen Abkürzung# des Feuertempels, |wäre|wären|"},
    });

    hintTable[FIRE_TEMPLE_MAP_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #caged chest# in the Fire Temple hoards", /*french*/"un #coffre emprisonné# dans le temple du feu contient", /*spanish*/"un #cofre entre rejas# del Templo del Fuego contiene", /*italian*/"un #forziere in una gabbia senza soffitto# nel Santuario del Fuoco contiene", /*german*/"in einer #eingekerkerten Truhe im Feuertempel#, |wäre|wären|"},
    });

    hintTable[FIRE_TEMPLE_COMPASS_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #chest in a fiery maze# contains", /*french*/"un #coffre dans un labyrinthe enflammé# contient", /*spanish*/"un #cofre de un ardiente laberinto# contiene", /*italian*/"un #forziere presso un labirinto di fiamme# contiene", /*german*/"in einer #Truhe eines feurigen Irrgartens#, |wäre|wären|"},
    });

    hintTable[FIRE_TEMPLE_HIGHEST_GORON_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #Goron atop the Fire Temple# holds", /*french*/"le #Goron au sommet du temple du feu# a", /*spanish*/"un #goron en lo alto del Templo del Fuego# guarda", /*italian*/"un #Goron in cima al Santuario del Fuoco# possiede", /*german*/"nahe eines #Goronen, im oberen Teil des Feuertempels#, |wäre|wären|"},
    });


    hintTable[FIRE_TEMPLE_MQ_NEAR_BOSS_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#near a dragon# is", /*french*/"#près d'un dragon# gît", /*spanish*/"#cerca de un dragón# yace", /*italian*/"#vicino a un drago# un forziere contiene", /*german*/"in der Nähe eines #Drachens#, |wäre|wären|"},
    });

    hintTable[FIRE_TEMPLE_MQ_MEGATON_HAMMER_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #Flare Dancer in the depths of a volcano# guards", /*french*/"le #Danse-Flamme au cœur du volcan# a", /*spanish*/"el #Bailafuego en lo profundo del volcán# esconde", /*italian*/"il #Fiammerino nelle profondità di un vulcano# protegge", /*german*/"nahe dem #Flammenderwisch, in den Tiefen eines Vulkans#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"the #Flare Dancer in the depths of the Fire Temple# guards", /*french*/"le #Danse-Flamme au cœur du volcan# a", /*spanish*/"el #Bailafuego en lo profundo del Templo del Fuego# esconde", /*italian*/"il #Fiammerino nelle profondità del Santuario del Fuoco# protegge", /*german*/"nahe dem #Flammenderwisch, in den Tiefen des Feuertempels#, |wäre|wären|"}
    );

    hintTable[FIRE_TEMPLE_MQ_COMPASS_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #blocked path# in Fire Temple holds", /*french*/"le #chemin scellé# dans le temple du feu contient", /*spanish*/"en un #camino bloqueado# del Templo del Fuego yace", /*italian*/"#sotto un pavimento crepato# nel Santuario del Fuoco puoi trovare", /*german*/"in einer #nützlichen Abkürzung# des Feuertempels, |wäre|wären|"},
    });

    hintTable[FIRE_TEMPLE_MQ_LIZALFOS_MAZE_LOWER_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#crates in a maze# contain", /*french*/"des #boîtes dans le labyrinthe# contiennent", /*spanish*/"las #cajas de un laberinto# contienen", /*italian*/"delle #casse in un labirinto# nel Santuario del Fuoco contengono", /*german*/"in einer #Kiste eines Irrgartens#, |wäre|wären|"},
    });

    hintTable[FIRE_TEMPLE_MQ_LIZALFOS_MAZE_UPPER_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#crates in a maze# contain", /*french*/"des #boîtes dans le labyrinthe# contiennent", /*spanish*/"las #cajas de un laberinto# contienen", /*italian*/"delle #casse in un labirinto# nel Santuario del Fuoco contengono", /*german*/"in einer #Kiste eines Irrgartens#, |wäre|wären|"},
    });

    hintTable[FIRE_TEMPLE_MQ_MAP_ROOM_SIDE_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #falling slug# in the Fire Temple guards", /*french*/"la #limace tombante# dans le temple du feu protège", /*spanish*/"una #babosa del techo# del Templo del Fuego guarda", /*italian*/"una #lumaca grigia# nel Santuario del Fuoco protegge", /*german*/"nahe eines #fallenden, sehr hungrigen Monsters# des Feuertempels, |wäre|wären|"},
    });

    hintTable[FIRE_TEMPLE_MQ_MAP_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"using a #hammer in the depths of the Fire Temple# reveals", "frapper du #marteau au cœur du volcan# révèle", /*spanish*/"usar el #martillo en lo profundo del Templo del Fuego# revela", /*italian*/"usare il #martello nel profondo del Santuario del Fuoco# rivela", /*german*/"nahe eines #rostigen Schalters#, im unteren Teil des Feuertempels, |wäre|wären|"},
    });

    hintTable[FIRE_TEMPLE_MQ_BOSS_KEY_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#illuminating a lava pit# reveals the path to", /*french*/"#éclairer le lac de lave# révèle", /*spanish*/"#iluminar un mar de llamas# revela", /*italian*/"#illuminare un lago di lava# apre la via per", /*german*/"hinter #brennenden Fackeln einer Lavagrube#, |wäre|wären|"},
    });

    hintTable[FIRE_TEMPLE_MQ_BIG_LAVA_ROOM_BLOCKED_DOOR_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#explosives over a lava pit# unveil", /*french*/"des #explosifs dans un lac de lave# révèlent", /*spanish*/"los #explosivos en un mar de llamas# revelan", /*italian*/"#esplosioni presso un lago di lava# rivelano", /*german*/"hinter einer #verdächtigen Wand einer Lavagrube#, |wäre|wären|"},
    });

    hintTable[FIRE_TEMPLE_MQ_LIZALFOS_MAZE_SIDE_ROOM_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #Goron hidden near a maze# holds", /*french*/"le #Goron caché près du labyrinthe# a", /*spanish*/"un #goron cerca de un laberinto# guarda", /*italian*/"un #Goron vicino a un labirinto# possiede", /*german*/"nahe eines #Goronen bei einem Irrgarten#, |wäre|wären|"},
    });

    hintTable[FIRE_TEMPLE_MQ_FREESTANDING_KEY] = HintText::Exclude({
                       // obscure text
                       Text{"hidden #beneath a block of stone# lies", /*french*/"caché #derrière un bloc de pierre# gît", /*spanish*/"#bajo unos bloques de piedra# yace", /*italian*/"#sotto un blocco di pietra# puoi scoprire", /*german*/"unterhalb eines #steinernen Blocks# des Feuertempels, |wäre|wären|"},
    });

    hintTable[FIRE_TEMPLE_VOLVAGIA_HEART] = HintText::Exclude({
                       // obscure text
                       Text{"the #Subterranean Lava Dragon# holds", /*french*/"le #dragon des profondeurs# possède", /*spanish*/"el #dragón de lava subterráneo# porta", /*italian*/"il #drago di magma# possiede", /*german*/"nahe dem #subterranen Lavadrachoiden#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"#Volvagia# holds", /*french*/"#Volvagia# possède", /*spanish*/"#Volvagia# porta", /*italian*/"#Varubaja# possiede", /*german*/"nahe #Volvagia#, |wäre|wären|"}
    );

    hintTable[FIRE_TEMPLE_GS_SONG_OF_TIME_ROOM] = HintText::Exclude({
                       // obscure text
                       Text{"#eight tiles of malice# guard a spider holding", /*french*/"une #Skulltula protégée par huit tuiles dans le temple du feu# a", /*spanish*/"#ocho baldosas de maldad# custodian una Skulltula que otorga", /*italian*/"#otto piastrelle# proteggono un ragno che ha", /*german*/"in einer Spinne, nahe #acht feindlich gesinnter Fliesen#, |wäre|wären|"},
    });

    hintTable[FIRE_TEMPLE_GS_BOSS_KEY_LOOP] = HintText::Exclude({
                       // obscure text
                       Text{"#five tiles of malice# guard a spider holding", /*french*/"une #Skulltula protégée par cinq tuiles dans le temple du feu# a", /*spanish*/"#cinco baldosas de maldad# custodian una Skulltula que otorga", /*italian*/"#cinque piastrelle# proteggono un ragno che ha", /*german*/"in einer Spinne, nahe #fünf feindlich gesinnter Fliesen#, |wäre|wären|"},
    });

    hintTable[FIRE_TEMPLE_GS_BOULDER_MAZE] = HintText::Exclude({
                       // obscure text
                       Text{"#explosives in a maze# unveil a spider hiding", /*french*/"une #Skulltula derrière un mur fragile du temple du feu# a", /*spanish*/"los #explosivos en un laberinto# desvelan una Skulltula que otorga", /*italian*/"#esplosioni in un labirinto# nel Santuario del Fuoco rivelano un ragno che nasconde", /*german*/"in einer Spinne, hinter einer #brüchigen Wand eines Irrgartens#, |wäre|wären|"},
    });

    hintTable[FIRE_TEMPLE_GS_SCARECROW_TOP] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider-friendly scarecrow# atop a volcano hides", /*french*/"une #Skulltula repérée par l'épouvantail du volcan# a", /*spanish*/"un #espantapájaros en lo alto de un volcán# custodia una Skulltula que otorga", /*italian*/"uno #spaventapasseri in cima al vulcano# indica un ragno che ha", /*german*/"in einer #Spinne über einer Vogelscheuche#, im oberen Teil eines Vulkans, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"a #spider-friendly scarecrow# atop the Fire Temple hides", /*french*/"une #Skulltula repérée par l'épouvantail du temple du feu# a", /*spanish*/"un #espantapájaros del Templo del Fuego# custodia una Skulltula que otorga", /*italian*/"uno #spaventapasseri nel Santuario del Fuoco# indica un ragno che ha", /*german*/"in einer #Spinne über einer Vogelscheuche#, im oberen Teil des Feuertempels, |wäre|wären|"}
    );

    hintTable[FIRE_TEMPLE_GS_SCARECROW_CLIMB] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider-friendly scarecrow# atop a volcano hides", /*french*/"une #Skulltula repérée par l'épouvantail du volcan# a", /*spanish*/"un #espantapájaros en lo alto de un volcán# custodia una Skulltula que otorga", /*italian*/"uno #spaventapasseri in cima al vulcano# indica un ragno che ha", /*german*/"in einer #Spinne über einer Vogelscheuche#, im oberen Teil eines Vulkans, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"a #spider-friendly scarecrow# atop the Fire Temple hides", /*french*/"une #Skulltula repérée par l'épouvantail du temple du feu# a", /*spanish*/"un #espantapájaros del Templo del Fuego# custodia una Skulltula que otorga", /*italian*/"uno #spaventapasseri nel Santuario del Fuoco# indica un ragno che ha", /*german*/"in einer #Spinne über einer Vogelscheuche#, im oberen Teil des Feuertempels, |wäre|wären|"}
    );


    hintTable[FIRE_TEMPLE_MQ_GS_ABOVE_FIRE_WALL_MAZE] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider above a fiery maze# holds", /*french*/"une #Skulltula au dessus du labyrinthe enflammé du temple du feu# a", /*spanish*/"una #Skulltula sobre un ardiente laberinto# otorga", /*italian*/"un #ragno sopra un labirinto di fiamme# nasconde", /*german*/"in einer #Spinne über einem feurigen Irrgarten#, |wäre|wären|"},
    });

    hintTable[FIRE_TEMPLE_MQ_GS_FIRE_WALL_MAZE_CENTER] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider within a fiery maze# holds", /*french*/"une #Skulltula dans le labyrinthe enflammé du temple du feu# a", /*spanish*/"una #Skulltula en el interior de un ardiente laberinto# otorga", /*italian*/"un #ragno dentro un labirinto di fiamme# nasconde", /*german*/"in einer #Spinne eines feurigen Irrgartens#, |wäre|wären|"},
    });

    hintTable[FIRE_TEMPLE_MQ_GS_BIG_LAVA_ROOM_OPEN_DOOR] = HintText::Exclude({
                       // obscure text
                       Text{"a #Goron trapped near lava# befriended a spider with", /*french*/"une #Skulltula emprisonnée près du lac de lave du temple du feu# a", /*spanish*/"una #Skulltula amiga de un Goron atrapado junto a la lava# otorga", /*italian*/"un #Goron prigioniero vicino a un lago di lava# è insieme a un ragno con", /*german*/"nahe eines, #bei Lava eingesperrten Goronen#, |wäre|wären|"},
    });

    hintTable[FIRE_TEMPLE_MQ_GS_FIRE_WALL_MAZE_SIDE_ROOM] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider beside a fiery maze# holds", /*french*/"une #Skulltula près du labyrinthe enflammé du temple du feu# a", /*spanish*/"una #Skulltula junto a un ardiente laberinto# otorga", /*italian*/"un #ragno presso un labirinto di fiamme# nasconde", /*german*/"in einer #Spinne, nahe eines feurigen Irrgartens#, |wäre|wären|"},
    });

    /*--------------------------
    |       WATER TEMPLE       |
    ---------------------------*/
    hintTable[WATER_TEMPLE_MAP_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#rolling spikes# in the Water Temple surround", /*french*/"des #Spikes# dans le temple de l'eau entourent", /*spanish*/"unas #rodantes púas# del Templo del Agua guardan", /*italian*/"dei #ricci di ferro# nel Santuario dell'Acqua proteggono", /*german*/"nahe #rollender Stacheln# des Wassertempels, |wäre|wären|"},
    });

    hintTable[WATER_TEMPLE_COMPASS_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#roaming stingers in the Water Temple# guard", /*french*/"des #raies dans le temple de l'eau# protègent", /*spanish*/"unos #errantes stingers# del Templo del Agua guardan", /*italian*/"dei #trigoni volanti nel Santuario dell'Acqua# proteggono", /*german*/"in einer, gut-gewässerten Truhe des Wassertempels, |wäre|wären|"},
    });

    hintTable[WATER_TEMPLE_TORCHES_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#fire in the Water Temple# reveals", /*french*/"des #flammes dans le temple de l'eau# révèlent", /*spanish*/"el #fuego en el Templo del Agua# revela", /*italian*/"#fuochi nel Santuario dell'Acqua# rivelano", /*german*/"nahe #brennender Fackeln# des Wassertempels, |wäre|wären|"},
    });

    hintTable[WATER_TEMPLE_DRAGON_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #serpent's prize# in the Water Temple is", /*french*/"la #récompense du dragon submergé# est", /*spanish*/"el #escamado premio# del Templo del Agua se trata de", /*italian*/"il #premio di un dragone# nel Santuario dell'Acqua è", /*german*/"der #Preis einer Schlange# des Wassertempels, |wäre|wären|"},
    });

    hintTable[WATER_TEMPLE_CENTRAL_BOW_TARGET_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#blinding an eye# in the Water Temple leads to", /*french*/"#l'oeil# du temple de l'eau voit", /*spanish*/"#cegar un ojo# del Templo del Agua conduce a", /*italian*/"#accecare un occhio# nel Santuario dell'Acqua apre la via per", /*german*/"nahe eines #geblendeten Auges# des Wassertempels, |wäre|wären|"},
    });

    hintTable[WATER_TEMPLE_CENTRAL_PILLAR_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"in the #depths of the Water Temple# lies", /*french*/"le #cœur du temple de l'eau# cache", /*spanish*/"en las #profundidades del Templo del Agua# yace", /*italian*/"#nel più profondo del Santuario dell'Acqua# puoi recuperare", /*german*/"in #den Tiefen# des Wassertempels, |wäre|wären|"},
    });

    hintTable[WATER_TEMPLE_CRACKED_WALL_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#through a crack# in the Water Temple is", /*french*/"le #mur fragile# du temple de l'eau cache", /*spanish*/"tras una #agrietada pared# del Templo del Agua yace", /*italian*/"#oltre una crepa#, nel Santuario dell'Acqua, un forziere contiene", /*german*/"#hinter einer brüchigen Wand# des Wassertempels, |wäre|wären|"},
    });

    hintTable[WATER_TEMPLE_LONGSHOT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#facing yourself# reveals",              /*french*/"se #vaincre soi-même# révèle", /*spanish*/"#luchar contra ti mismo# revela",        /*italian*/"#affrontare sè stessi# procura", /*german*/"hinter einer #Selbstreflexion#, |wäre|wären|"},
                       Text{"a #dark reflection# of yourself guards", /*french*/"son #propre reflet# cache",    /*spanish*/"el #oscuro reflejo de ti mismo# guarda", /*italian*/"la #tua ombra# difende",         /*german*/"nahe eines #dunklen Spiegelbilds#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"#Dark @# guards", /*french*/"l'#Ombre de @# protège", /*spanish*/"#@ Oscuro# guarda", /*italian*/"#@ oscuro# protegge", /*german*/"nahe #dem schwarzen @#, |wäre|wären|"}
    );


    hintTable[WATER_TEMPLE_MQ_CENTRAL_PILLAR_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"in the #depths of the Water Temple# lies", /*french*/"le #cœur du temple de l'eau# cache", /*spanish*/"en las #profundidades del Templo del Agua# yace", /*italian*/"#nel più profondo del Santuario dell'Acqua# puoi recuperare", /*german*/"in #den Tiefen# des Wassertempels, |wäre|wären|"},
    });

    hintTable[WATER_TEMPLE_MQ_BOSS_KEY_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"fire in the Water Temple unlocks a #vast gate# revealing a chest with", /*french*/"des #flammes au cœur du temple de l'eau# révèlent", /*spanish*/"el fuego en el Templo del Agua alza una #gran valla# con", /*italian*/"fuochi nel Santuario dell'Acqua aprono un #grande cancello# davanti a un forziere con", /*german*/"nahe #brennender Fackeln#, hinter einem #riesigen Gatter# des Wassertempels, |wäre|wären|"},
    });

    hintTable[WATER_TEMPLE_MQ_LONGSHOT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#through a crack# in the Water Temple is", /*french*/"le #mur fragile# du temple de l'eau cache", /*spanish*/"tras una #agrietada pared# del Templo del Agua yace", /*italian*/"#oltre una crepa#, nel Santuario dell'Acqua, un forziere contiene", /*german*/"#hinter einer gebrochenen Wand# des Wassertempels, |wäre|wären|"},
    });

    hintTable[WATER_TEMPLE_MQ_COMPASS_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#fire in the Water Temple# reveals", /*french*/"des #flammes dans le temple de l'eau# révèlent", /*spanish*/"el #fuego en el Templo del Agua# revela", /*italian*/"#fuochi nel Santuario dell'Acqua# rivelano", /*german*/"nahe #brennender Fackeln# des Wassertempels, |wäre|wären|"},
    });

    hintTable[WATER_TEMPLE_MQ_MAP_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#sparring soldiers# in the Water Temple guard", /*french*/"les #soldats du temple de l'eau# protègent", /*spanish*/"#acabar con unos soldados# del Templo del Agua revela", /*italian*/"#tre soldati# nel Santuario dell'Acqua difendono", /*german*/"nahe der #Armee der Toten# des Wassertempels, |wäre|wären|"},
    });

    hintTable[WATER_TEMPLE_MORPHA_HEART] = HintText::Exclude({
                       // obscure text
                       Text{"the #Giant Aquatic Amoeba# holds", /*french*/"l'#amibe aquatique géante# possède", /*spanish*/"la #ameba acuática gigante# porta", /*italian*/"l'#ameba gigante# possiede", /*german*/"nahe dem #aquamöben Wassertentakel#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"#Morpha# holds", /*french*/"#Morpha# possède", /*spanish*/"#Morpha# porta", /*italian*/"#Morpha# possiede", /*german*/"nahe #Morpha#, |wäre|wären|"}
    );

    hintTable[WATER_TEMPLE_GS_FALLING_PLATFORM_ROOM] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider over a waterfall# in the Water Temple holds", /*french*/"une #Skulltula au dessus d'une cascade du temple de l'eau# a", /*spanish*/"una #Skulltula tras una cascada# del Templo del Agua otorga", /*italian*/"un #ragno di fianco a una cascata# nel Santuario dell'Acqua nasconde", /*german*/"in einer #Spinne, über einem Wasserfall# des Wassertempels, |wäre|wären|"},
    });

    hintTable[WATER_TEMPLE_GS_CENTRAL_PILLAR] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider in the center of the Water Temple# holds", /*french*/"une #Skulltula au centre du temple de l'eau# a", /*spanish*/"una #Skulltula en el centro del Templo del Agua# otorga", /*italian*/"un #ragno al centro del Santuario dell'Acqua# possiede", /*german*/"in einer #Spinne, im Zentrum# des Wassertempels, |wäre|wären|"},
    });

    hintTable[WATER_TEMPLE_GS_NEAR_BOSS_KEY_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a spider protected by #rolling boulders under the lake# hides", /*french*/"une #Skulltula derrière les rochers roulants sous le lac# a", /*spanish*/"una #Skulltula protegida por rocas rodantes# bajo el lago otorga", /*italian*/"un ragno protetto da #macigni rotolanti sotto il lago# nasconde", /*german*/"in einer Spinne, nahe #rollender Felsen am Grund des Sees#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"a spider protected by #rolling boulders in the Water Temple# hides", /*french*/"une #Skulltula derrière les rochers roulants du temple de l'eau# a", /*spanish*/"una #Skulltula protegida por rocas rodantes# del Templo del Agua otorga", /*italian*/"un ragno protetto da #macigni rotolanti nel Santuario dell'Acqua# nasconde", /*german*/"in einer Spinne, nahe #rollender Felsen des Wassertempels#, |wäre|wären|"}
    );

    hintTable[WATER_TEMPLE_GS_RIVER] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider over a river# in the Water Temple holds", /*french*/"une #Skulltula au dessus de la rivière du temple de l'eau# a", /*spanish*/"una #Skulltula sobre un río# del Templo del Agua otorga", /*italian*/"un #ragno sopra un fiume# nel Santuario dell'Acqua nasconde", /*german*/"in einer #Spinne, oberhalb eines Flusses# des Wassertempels, |wäre|wären|"},
    });


    hintTable[WATER_TEMPLE_MQ_GS_BEFORE_UPPER_WATER_SWITCH] = HintText::Exclude({
                       // obscure text
                       Text{"#beyond a pit of lizards# is a spider holding", /*french*/"une #Skulltula près des lézards du temple de l'eau# a", /*spanish*/"#más allá de un pozo de reptiles# una Skulltula otorga", /*italian*/"un #ragno sopra una lucertola# nel Santuario dell'Acqua difende", /*german*/"in einer Spinne, nahe eines #Triforce-Symbols# des Wassertempels, |wäre|wären|"},
    });

    hintTable[WATER_TEMPLE_MQ_GS_LIZALFOS_HALLWAY] = HintText::Exclude({
                       // obscure text
                       Text{"#lizards guard a spider# in the Water Temple with", /*french*/"une #Skulltula dans les couloirs croisés du temple de l'eau# a", /*spanish*/"unos #reptiles custodian una Skulltula# del Templo del Agua que otorga", /*italian*/"un #ragno protetto da lucertole# nel Santuario dell'Acqua nasconde", /*german*/"in einer, #von Echsen beschützten Spinne# des Wassertempels, |wäre|wären|"},
    });

    hintTable[WATER_TEMPLE_MQ_GS_RIVER] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider over a river# in the Water Temple holds", /*french*/"une #Skulltula au dessus de la rivière du temple de l'eau# a", /*spanish*/"una #Skulltula sobre un río# del Templo del Agua otorga", /*italian*/"un #ragno sopra un fiume# nel Santuario dell'Acqua nasconde", /*german*/"in einer #Spinne, oberhalb eines Flusses# des Wassertempels, |wäre|wären|"},
    });

    /*--------------------------
    |      SPIRIT TEMPLE       |
    ---------------------------*/
    hintTable[SPIRIT_TEMPLE_CHILD_BRIDGE_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a child conquers a #skull in green fire# in the Spirit Temple to reach", /*french*/"le #crâne au halo vert dans le colosse# cache", /*spanish*/"el joven que #baje el puente# del Templo del Espíritu encontrará", /*italian*/"se un bambino oltrepassa un #teschio verde# nel Santuario dello Spirito raggiungerà", /*german*/"hinter einem #grünen, brennenden Schädel# des Geistertempels der Vergangenhei, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_CHILD_EARLY_TORCHES_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a child can find a #caged chest# in the Spirit Temple with", /*french*/"le #coffre embarré dans le colosse# contient", /*spanish*/"un joven puede encontrar un #cofre entre rejas# del Templo del Espíritu con", /*italian*/"nel Santuario dello Spirito un bambino può trovare un #forziere ingabbiato# contenente", /*german*/"in einer #eingekerkerten Truhe# des Geistertempels der Vergangenheit, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_COMPASS_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#across a pit of sand# in the Spirit Temple lies", /*french*/"le #trou sableux dans le colosse# a", /*spanish*/"tras un #pozo de arena# del Templo del Espíritu yace", /*italian*/"#oltre una fossa sabbiosa# nel Santuario dello Spirito puoi trovare", /*german*/"#hinter einer Sandgrube# des Geistertempels, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_EARLY_ADULT_RIGHT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#dodging boulders to collect silver rupees# in the Spirit Temple yields", /*french*/"les #pièces argentées entourées de rochers dans le colosse# révèlent", /*spanish*/"#esquivar rocas y conseguir plateadas rupias# en el Templo del Espíritu conduce a", /*italian*/"chi #raccoglie rupie schivando macigni# nel Santuario dello Spirito otterrà", /*german*/"nahe #Silber, umgeben von rollenden Felsen# des Geistertempels, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_FIRST_MIRROR_LEFT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #shadow circling reflected light# in the Spirit Temple guards", /*french*/"l'#ombre près d'un miroir# protège", /*spanish*/"un #círculo de reflectante luz# del Templo del Espíritu guarda", /*italian*/"una #mano mozza attorno a luce riflessa# nel Santuario dello Spirito protegge", /*german*/"nahe eines #Schattens, bei reflektiertem Licht# des Geistertempels, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_FIRST_MIRROR_RIGHT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #shadow circling reflected light# in the Spirit Temple guards", /*french*/"l'#ombre près d'un miroir# protège", /*spanish*/"un #círculo de reflectante luz# del Templo del Espíritu guarda", /*italian*/"una #mano mozza attorno a luce riflessa# nel Santuario dello Spirito protegge", /*german*/"nahe eines #Schattens, bei reflektiertem Licht# des Geistertempels, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_MAP_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#before a giant statue# in the Spirit Temple lies", /*french*/"#devant la statue# dans le colosse gît", /*spanish*/"#ante una gran estatua# del Templo del Espíritu aguarda", /*italian*/"#ai piedi di una statua gigante# nel Santuario dello Spirito puoi trovare", /*german*/"#vor der riesigen Statue# des Geistertempels, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_CHILD_CLIMB_NORTH_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#lizards in the Spirit Temple# guard", /*french*/"les #lézards dans le colosse# protègent", /*spanish*/"los #reptiles del Templo del Espíritu# guardan", /*italian*/"delle #lucertole nel Santuario dello Spirito# proteggono", /*german*/"nahe #Echsen des Geistertempels#, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_CHILD_CLIMB_EAST_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#lizards in the Spirit Temple# guard", /*french*/"les #lézards dans le colosse# protègent", /*spanish*/"los #reptiles del Templo del Espíritu# guardan", /*italian*/"delle #lucertole nel Santuario dello Spirito# proteggono", /*german*/"nahe #Echsen des Geistertempels#, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_SUN_BLOCK_ROOM_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#torchlight among Beamos# in the Spirit Temple reveals", /*french*/"les #torches autour des Sentinelles# éclairent", /*spanish*/"las #antorchas junto a Beamos# del Templo del Espíritu revelan", /*italian*/"le #torce attorno ai Laseros# nel Santuario dello Spirito illuminano", /*german*/"nahe #brennender Fackeln, bei Beamos# des Geistertempels, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_STATUE_ROOM_HAND_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #statue in the Spirit Temple# holds", /*french*/"la #statue dans le colosse# tient", /*spanish*/"una #estatua del Templo del Espíritu# esconde", /*italian*/"una #statua gigante# nel Santuario dello Spirito tiene in mano", /*german*/"auf einer Hand, der #riesigen Statue des Geistertempels#, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_STATUE_ROOM_NORTHEAST_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"on a #ledge by a statue# in the Spirit Temple rests", /*french*/"#haut perché près de la statue# dans le colosse gît", /*spanish*/"al #borde de una estatua# del Templo del Espíritu yace", /*italian*/"#accanto a una statua# nel Santuario dello Spirito puoi trovare", /*german*/"auf einem #Vorsprung, nahe der riesigen Statue# des Geistertempels, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_NEAR_FOUR_ARMOS_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"those who #show the light among statues# in the Spirit Temple find", /*french*/"le #soleil près des statues# cache", /*spanish*/"aquellos que #iluminen ante las estatuas# del Templo del Espíritu encontrarán", /*italian*/"#riflettendo vicino a 4 statue# nel Santuario dello Spirito puoi scoprire", /*german*/"nahe einer #lichtbedürftigen Sonne, bei Statuen# des Geistertempels, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_HALLWAY_RIGHT_INVISIBLE_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #Eye of Truth in the Spirit Temple# reveals", /*french*/"le #trésor invisible près du Hache-Viande# contient", /*spanish*/"el #Ojo de la Verdad# en el Templo del Espíritu revela", /*italian*/"l'#occhio della verità nel Santuario dello Spirito# rivela", /*german*/"ein, vom #Auge der Wahrheit# aufgedecktes Geheimnis des #Geistertempels#, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_HALLWAY_LEFT_INVISIBLE_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #Eye of Truth in the Spirit Temple# reveals", /*french*/"le #trésor invisible près du Hache-Viande# contient", /*spanish*/"el #Ojo de la Verdad# en el Templo del Espíritu revela", /*italian*/"l'#occhio della verità nel Santuario dello Spirito# rivela", /*german*/"ein, vom #Auge der Wahrheit# aufgedecktes Geheimnis des #Geistertempels#, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_BOSS_KEY_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #chest engulfed in flame# in the Spirit Temple holds", /*french*/"le #coffre enflammé dans le colosse# contient", /*spanish*/"un #cofre rodeado de llamas# del Templo del Espíritu contiene", /*italian*/"un #forziere scottante# nel Santuario dello Spirito contiene", /*german*/"in einer #flammenden Truhe# des Geistertempels, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_TOPMOST_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"those who #show the light above the Colossus# find", /*french*/"le #soleil au sommet du colosse# révèle", /*spanish*/"aquellos que #iluminen en lo alto del Coloso# encontrarán", /*italian*/"#chi sa riflettere bene# in cima al colosso può trovare", /*german*/"nahe einer #lichtbedürftigen Sonne, an der Spitze des Kolosses#, |wäre|wären|"},
    });


    hintTable[SPIRIT_TEMPLE_MQ_ENTRANCE_FRONT_LEFT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#lying unguarded# in the Spirit Temple is", /*french*/"dans #l'entrée du colosse# se trouve", /*spanish*/"en la #entrada del Templo del Espíritu# yace", /*italian*/"un forziere #incustodito# all'ingresso del Santuario dello Spirito contiene", /*german*/"in einer #unbewachten Truhe# des Geistertempels, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_ENTRANCE_BACK_RIGHT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #switch in a pillar# within the Spirit Temple drops", /*french*/"l'#interrupteur dans un pilier# du colosse cache", /*spanish*/"el #interruptor de un pilar# del Templo del Espíritu revela", /*italian*/"un #interruttore in un pilastro# nel Santuario dello Spirito fa cadere", /*german*/"nahe eines Schalters, an einer Säule des Geistertempels, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_ENTRANCE_FRONT_RIGHT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#collecting rupees through a water jet# reveals", /*french*/"les #pièces argentées dans le jet d'eau# du colosse révèlent", /*spanish*/"#hacerte con rupias tras un géiser# revela", /*italian*/"#raccogliere rupie attraversando un geyser# rivela", /*german*/"nahe #Silber bei einem Wasserstrahl#, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_ENTRANCE_BACK_LEFT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"an #eye blinded by stone# within the Spirit Temple conceals", /*french*/"#l'oeil derrière le rocher# dans le colosse voit", /*spanish*/"#cegar a un ojo# del Templo del Espíritu revela", /*italian*/"un #occhio coperto di pietra# nel Santuario dello Spirito nasconde", /*german*/"nahe eines #geblendeten Auges# des Geistertempels, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_MAP_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"surrounded by #fire and wrappings# lies", /*french*/"près des #pierres tombales dans le colosse# gît", /*spanish*/"rodeado de #fuego y vendas# yace", /*italian*/"un #Anubi# sta appollaiato su un forziere contenente", /*german*/"hinter #feurigen Schnecken# des Geistertempels, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_MAP_ROOM_ENEMY_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a child defeats a #gauntlet of monsters# within the Spirit Temple to find", /*french*/"l'enfant qui vainc #plusieurs monstres# dans le colosse trouvera", /*spanish*/"el joven que derrote #unos monstruos# del Templo del Espíritu encontrará", /*italian*/"se un bambino sconfigge #molti mostri# nel Santuario dello Spirito otterrà", /*german*/"hinter einem #Spießrutenlauf der Jugend# des Geistertempels, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_CHILD_CLIMB_NORTH_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#explosive sunlight# within the Spirit Temple uncovers", /*french*/"le #rayon de lumière explosif dans le colosse# révèle", /*spanish*/"una #explosiva luz solar# del Templo del Espíritu revela", /*italian*/"un #raggio di sole esplosivo# nel Santuario dello Spirito fa apparire", /*german*/"nahe #explosivem Sonnenlicht# des Geistertempels, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_CHILD_CLIMB_SOUTH_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#trapped by falling enemies# within the Spirit Temple is", /*french*/"des #ennemis tombants# dans le colosse protègent", /*spanish*/"#rodeado de enemigos del cielo# del Templo del Espíritu yace", /*italian*/"un #mostro che aspetta di caderti in testa# nel Santuario dello Spirito protegge", /*german*/"nahe eines #fallenden, sehr hungrigen Monsters# des Geistertempels, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_COMPASS_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#blinding the colossus# unveils", /*french*/"#l'oeil dans le colosse# voit", /*spanish*/"#cegar al coloso# revela", /*italian*/"#accecare il ginocchio del colosso# rivela", /*german*/"nahe eines #geblendeten Auges# des Kolosses, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_STATUE_ROOM_LULLABY_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #royal melody awakens the colossus# to reveal", /*french*/"la #mélodie royale éveille le colosse# et révèle", /*spanish*/"la #melodía real que despierte al coloso# revelará", /*italian*/"una #melodia reale risveglia il colosso# e rivela", /*german*/"nach #hoheitlicher Musik im Koloss#, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_STATUE_ROOM_INVISIBLE_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #Eye of Truth# finds the colossus's hidden", /*french*/"#l'oeil de vérité# verra dans le colosse", /*spanish*/"el #Ojo de la Verdad# en el Templo del Espíritu encontrará", /*italian*/"l'#occhio della verità# nel Santuario dello Spirito rivela", /*german*/"ein, vom #Auge der Wahrheit# aufgedecktes Geheimnis des #Geistertempels#, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_SILVER_BLOCK_HALLWAY_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#the old hide what the young find# to reveal", /*french*/"l'#oeil dans le trou du bloc argent# dans le colosse voit", /*spanish*/"el #adulto esconde lo que el joven anhela#, revelando", /*italian*/"#ciò che gli adulti nascondono e i bambini trovano# è", /*german*/"nahe eines, #im Alter blockierten geblendeten Auges# des Geistertempels, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_SUN_BLOCK_ROOM_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#sunlight in a maze of fire# hides", /*french*/"#la lumière dans le labyrinthe de feu# du colosse révèle", /*spanish*/"la #luz solar de un ígneo laberinto# esconde", /*italian*/"un #raggio di sole fra teschi infuocati# rivela", /*german*/"nahe #Sonnenlicht eines feurigen Irrgartens#, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_LEEVER_ROOM_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#across a pit of sand# in the Spirit Temple lies", /*french*/"le #trou sableux# dans le colosse a", /*spanish*/"#a través del pozo de arena# del Templo del Espíritu yace", /*italian*/"#oltre una fossa sabbiosa# nel Santuario dello Spirito puoi trovare", /*german*/"#hinter einer Sandgrube# des Geistertempels, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_BEAMOS_ROOM_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"where #temporal stone blocks the path# within the Spirit Temple lies", /*french*/"les #pierres temporelles# dans le colosse cachent", /*spanish*/"donde los #bloques temporales bloquean# en el Templo del Espíritu yace", /*italian*/"laddove #pietre temporali bloccano la via# nel Santuario dello Spirito puoi trovare", /*german*/"hinter #Zeitportal-Steinen# des Geistertempels, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_CHEST_SWITCH_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #chest of double purpose# holds", /*french*/"le #coffre à usage double# du colosse contient", /*spanish*/"un #cofre de doble uso# contiene", /*italian*/"un #forziere a duplice uso# nel Santuario dello Spirito contiene", /*german*/"in einer #Truhe mit mehreren Verwendungszwecken#, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_BOSS_KEY_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #temporal stone blocks the light# leading to", /*french*/"la #pierre temporelle# le colosse fait ombre sur", /*spanish*/"un #bloque temporal bloquea la luz# que conduce a", /*italian*/"una #pietra temporale blocca la luce# che apre la via per", /*german*/"nahe eines, #im Licht stehenden Zeitportal-Steins#, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_MIRROR_PUZZLE_INVISIBLE_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"those who #show the light above the Colossus# find", /*french*/"le trésor invisible #au sommet du colosse# contient", /*spanish*/"aquellos que #revelen la luz sobre el Coloso# encontrarán", /*italian*/"#chi sa riflettere bene# in cima al colosso può trovare", /*german*/"nahe einer #lichtbedürftigen Sonne, an der Spitze des Kolosses#, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_TWINROVA_HEART] = HintText::Exclude({
                       // obscure text
                       Text{"the #Sorceress Sisters# hold", /*french*/"#les sorcières jumelles# possède", /*spanish*/"las #hermanas hechiceras# portan", /*italian*/"le #sorelle megere# possiedono", /*german*/"nahe der #höllischen Hexenarmada#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"#Twinrova# holds", /*french*/"#Twinrova# possède", /*spanish*/"#Birova# porta", /*italian*/"#Duerova# possiede", /*german*/"nahe #Twinrova#, |wäre|wären|"}
    );

    hintTable[SPIRIT_TEMPLE_GS_HALL_AFTER_SUN_BLOCK_ROOM] = HintText::Exclude({
                       // obscure text
                       Text{"a spider in the #hall of a knight# guards", /*french*/"une #Skulltula au dessus d'un escalier du temple de l'esprit# a", /*spanish*/"una #Skulltula en el salón de un guerrero# otorga", /*italian*/"un #ragno vicino a un possente guerriero# protegge", /*german*/"in einer Spinne der #Halle eines Ritters#, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_GS_BOULDER_ROOM] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider behind a temporal stone# in the Spirit Temple yields", /*french*/"une #Skulltula derrière une pierre temporelle du temple de l'esprit# a", /*spanish*/"una #Skulltula tras un bloque temporal# del Templo del Espíritu otorga", /*italian*/"un ragno #dietro una pietra temporale# nel Santuario dello Spirito nasconde", /*german*/"in einer #Spinne, hinter einem Zeitportal-Stein# des Geistertempels, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_GS_LOBBY] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider beside a statue# holds", /*french*/"une #Skulltula dans la grande salle du temple de l'esprit# a", /*spanish*/"una #Skulltula junto a una estatua# del Templo del Espíritu otorga", /*italian*/"un ragno #di fianco a una statua gigante# nasconde", /*german*/"in einer #Spinne, nahe einer riesigen Statue#, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_GS_SUN_ON_FLOOR_ROOM] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider at the top of a deep shaft# in the Spirit Temple holds", /*french*/"une #Skulltula près d'un mur d'escalade du temple de l'esprit# a", /*spanish*/"una #Skulltula en lo alto de un gran hueco# del Templo del Espíritu otorga", /*italian*/"un ragno #in cima a un condotto scalabile# nel Santuario dello Spirito nasconde", /*german*/"in einer Spinne, #an der Spitze eines tiefen Schachts# des Geistertempels, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_GS_METAL_FENCE] = HintText::Exclude({
                       // obscure text
                       Text{"a child defeats a #spider among bats# in the Spirit Temple to gain", /*french*/"une #Skulltula sur le grillage du temple de l'esprit# a", /*spanish*/"el joven que derrote la #Skulltula entre murciélagos# del Templo del Espíritu hallará", /*italian*/"un bambino può sconfiggere #un ragno fra i pipistrelli# nel Santuario dello Spirito per ottenere", /*german*/"in einer, #von Fledermäusen umgebenen Spinne# des Geistertempels, |wäre|wären|"},
    });


    hintTable[SPIRIT_TEMPLE_MQ_GS_LEEVER_ROOM] = HintText::Exclude({
                       // obscure text
                       Text{"#above a pit of sand# in the Spirit Temple hides", /*french*/"une #Skulltula au dessus du trou sableux du temple de l'esprit# a", /*spanish*/"una #Skulltula sobre un pozo de arena# del Templo del Espíritu otorga", /*italian*/"#sopra una fossa sabbiosa# nel Santuario dello Spirito si nasconde un ragno con", /*german*/"in einer Spinne, #über einer Sandgrube# des Geistertempels, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_GS_NINE_THRONES_ROOM_WEST] = HintText::Exclude({
                       // obscure text
                       Text{"a spider in the #hall of a knight# guards", /*french*/"une #Skulltula dans la salle aux neuf trônes du temple de l'esprit# a", /*spanish*/"una #Skulltula en el salón de un guerrero# otorga", /*italian*/"un #ragno nella sala di un guerriero# nasconde", /*german*/"in einer Spinne der #Halle eines Ritters#, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_GS_NINE_THRONES_ROOM_NORTH] = HintText::Exclude({
                       // obscure text
                       Text{"a spider in the #hall of a knight# guards", /*french*/"une #Skulltula dans la salle aux neuf trônes du temple de l'esprit# a", /*spanish*/"una #Skulltula en el salón de un guerrero# otorga", /*italian*/"un #ragno nella sala di un guerriero# nasconde", /*german*/"in einer Spinne der #Halle eines Ritters#, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_GS_SUN_BLOCK_ROOM] = HintText::Exclude({
                       // obscure text
                       Text{"#upon a web of glass# in the Spirit Temple sits a spider holding", /*french*/"une #Skulltula sur une paroi de verre du temple de l'esprit# a", /*spanish*/"#sobre una plataforma de cristal# yace una Skulltula que otorga", /*italian*/"#sopra una tela di vetro# nel Santuario dello Spirito un ragno nasconde", /*german*/"in einer Spinne, eines #gläsernen Netzes# des Geistertempels, |wäre|wären|"},
    });

    /*--------------------------
    |      SHADOW TEMPLE       |
    ---------------------------*/
    hintTable[SHADOW_TEMPLE_MAP_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #Eye of Truth# pierces a hall of faces to reveal", /*french*/"l'#oeil de vérité# voit dans les couloirs du temple de l'ombre", /*spanish*/"el #Ojo de la Verdad# descubrirá un pasillo de facetas con", /*italian*/"l'#occhio della verità# penetra corridoi di facce per rivelare", /*german*/"hinter der Halle der Gesichter, vom #Auge der Wahrheit# aufgedeckt, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_HOVER_BOOTS_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #nether dweller in the Shadow Temple# holds", /*french*/"le #spectre du temple de l'ombre# a", /*spanish*/"un #temido morador del Templo de las Sombras# guarda", /*italian*/"un #tipo manesco nel Santuario dell'Ombra# possiede", /*german*/"nahe dem #unterirdischen Bewohner des Schattentempels#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"#Dead Hand in the Shadow Temple# holds", /*french*/"le #Poigneur dans le temple de l'ombre# cache", /*spanish*/"la #Mano Muerta del Templo de las Sombras# guarda", /*italian*/"lo #Smaniosso nel Santuario dell'Ombra# possiede", /*german*/"nahe dem #Hirnsauger des Schattentempels#, |wäre|wären|"}
    );

    hintTable[SHADOW_TEMPLE_COMPASS_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#mummies revealed by the Eye of Truth# guard", /*french*/"les #Gibdos dans les couloirs# du temple de l'ombre protègent", /*spanish*/"las #momias reveladas por el Ojo de la Verdad# guardan", /*italian*/"delle #mummie oltre un muro finto# nel Santuario dell'Ombra difendono", /*german*/"nahe, vom #Auge der Wahrheit# aufgedeckten Mumien, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_EARLY_SILVER_RUPEE_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#spinning scythes# protect", /*french*/"les #faucheurs danseurs# du temple de l'ombre protègent", /*spanish*/"las #giratorias guadañas# protegen", /*italian*/"delle #falci rotanti# nel Santuario dell'Ombra proteggono", /*german*/"nahe #rotierender Sensen#, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_INVISIBLE_BLADES_VISIBLE_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#invisible blades# guard", /*french*/"les #faucheurs invisibles# du temple de l'ombre protègent", /*spanish*/"las #hojas invisibles# guardan", /*italian*/"delle #falci invisibili# nel Santuario dell'Ombra proteggono", /*german*/"nahe #unsichtbarer Klingen#, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_INVISIBLE_BLADES_INVISIBLE_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#invisible blades# guard", /*french*/"les #faucheurs invisibles# du temple de l'ombre protègent", /*spanish*/"las #hojas invisibles# guardan", /*italian*/"delle #falci invisibili# nel Santuario dell'Ombra proteggono", /*german*/"nahe #unsichtbarer Klingen#, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_FALLING_SPIKES_LOWER_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#falling spikes# block the path to", /*french*/"la #pluie de clous# surplombe", /*spanish*/"los #pinchos de un techo# conducen a", /*italian*/"la #pioggia d'acciaio# blocca la via per", /*german*/"hinter #fallenden Stacheln#, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_FALLING_SPIKES_UPPER_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#falling spikes# block the path to", /*french*/"la #pluie de clous# surplombe", /*spanish*/"los #pinchos de un techo# conducen a", /*italian*/"la #pioggia d'acciaio# blocca la via per", /*german*/"hinter #fallenden Stacheln#, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_FALLING_SPIKES_SWITCH_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#falling spikes# block the path to", /*french*/"la #pluie de clous# surplombe", /*spanish*/"los #pinchos de un techo# conducen a", /*italian*/"la #pioggia d'acciaio# blocca la via per", /*german*/"hinter #fallenden Stacheln#, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_INVISIBLE_SPIKES_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #dead roam among invisible spikes# guarding", /*french*/"#parmi les clous invisibles# du temple de l'ombre se cache", /*spanish*/"los #muertos que vagan por pinchos invisibles# protegen", /*italian*/"i #morti vaganti fra spine invisibili# possiedono", /*german*/"in einer, #von den Toten beschützten Truhe# nahe unsichtbarer Stacheln, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_WIND_HINT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"an #invisible chest guarded by the dead# holds", /*french*/"le #trésor invisible du cul-de-sac# du temple de l'ombre contient", /*spanish*/"un #cofre invisible custodiado por los del más allá# contiene", /*italian*/"un #forziere invisibile in una strada chiusa# nel Santuario dell'Ombra contiene", /*german*/"in einer #unsichtbaren, von den Toten beschützten Truhe#, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_AFTER_WIND_ENEMY_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#mummies guarding a ferry# hide", /*french*/"les #Gibdos qui bloquent le traversier# cachent", /*spanish*/"las #momias que protegen un navío# esconden", /*italian*/"delle #mummie presso un traghetto infernale# nascondono", /*german*/"nahe #Mumien, die eine Fähre# bewachen, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_AFTER_WIND_HIDDEN_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#mummies guarding a ferry# hide", /*french*/"les #Gibdos qui bloquent le traversier# cachent", /*spanish*/"las #momias que protegen un navío# esconden", /*italian*/"delle #mummie presso un traghetto infernale# nascondono", /*german*/"nahe #Mumien, die eine Fähre# bewachen, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_SPIKE_WALLS_LEFT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#walls consumed by a ball of fire# reveal", /*french*/"le #piège de bois# du temple de l'ombre cache", /*spanish*/"las #paredes consumidas por una esfera ígnea# revelan", /*italian*/"#pareti lignee deboli alla sfera ignea# coprono", /*german*/"hinter #feueranfälligen Wänden#, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_BOSS_KEY_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#walls consumed by a ball of fire# reveal", /*french*/"le #piège de bois# du temple de l'ombre cache", /*spanish*/"las #paredes consumidas por una esfera ígnea# revelan", /*italian*/"#pareti lignee deboli alla sfera ignea# coprono", /*german*/"hinter #feueranfälligen Wänden#, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_FREESTANDING_KEY] = HintText::Exclude({
                       // obscure text
                       Text{"#inside a burning skull# lies", /*french*/"#dans un crâne enflammé# gît", /*spanish*/"en el #interior de una calavera en llamas# aguarda", /*italian*/"da un #vaso a forma di teschio# |salta|saltano| fuori", /*german*/"#in einem brennenden Schädel#, |wäre|wären|"},
    });


    hintTable[SHADOW_TEMPLE_MQ_COMPASS_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #Eye of Truth# pierces a hall of faces to reveal", /*french*/"l'#oeil de vérité# voit dans les couloirs du temple de l'ombre", /*spanish*/"el #Ojo de la Verdad# descubre un pasillo de facetas con", /*italian*/"l'#occhio della verità# penetra corridoi di facce per rivelare", /*german*/"hinter der Halle der Gesichter, vom #Auge der Wahrheit# aufgedeckt, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_MQ_HOVER_BOOTS_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #nether dweller in the Shadow Temple# holds", /*french*/"le #spectre du temple de l'ombre# a", /*spanish*/"un #temido morador del Templo de las Sombras# guarda", /*italian*/"un #tipo manesco nel Santuario dell'Ombra# possiede", /*german*/"nahe dem #unterirdischen Bewohner des Schattentempels#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"#Dead Hand in the Shadow Temple# holds", /*french*/"le #Poigneur dans le temple de l'ombre# cache", /*spanish*/"la #Mano Muerta del Templo de las Sombras# guarda", /*italian*/"lo #Smaniosso nel Santuario dell'Ombra# possiede", /*german*/"nahe dem #Hirnsauger des Schattentempels#, |wäre|wären|"}
    );

    hintTable[SHADOW_TEMPLE_MQ_EARLY_GIBDOS_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#mummies revealed by the Eye of Truth# guard", /*french*/"les #Gibdos dans les couloirs# du temple de l'ombre protègent", /*spanish*/"las #momias reveladas por el Ojo de la Verdad# guardan", /*italian*/"delle #mummie oltre un muro finto# nel Santuario dell'Ombra difendono", /*german*/"nahe, vom #Auge der Wahrheit# aufgedeckten Mumien, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_MQ_MAP_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#spinning scythes# protect", /*french*/"les #faucheurs danseurs# du temple de l'ombre protègent", /*spanish*/"las #giratorias guadañas# protegen", /*italian*/"delle #falci rotanti# nel Santuario dell'Ombra proteggono", /*german*/"nahe #rotierender Sensen#, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_MQ_BEAMOS_SILVER_RUPEES_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#collecting rupees in a vast cavern# within the Shadow Temple unveils", /*french*/"les #pièces argentées dans le temple de l'ombre# révèlent", /*spanish*/"hacerte con las #rupias en una gran caverna# del Templo de las Sombras revela", /*italian*/"#raccogliere rupie in una vasta caverna# nel Santuario dell'Ombra rivela", /*german*/"nahe Silber, einer weitläufigen Höhle des Schattentempels, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_MQ_FALLING_SPIKES_SWITCH_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#falling spikes# block the path to", /*french*/"la #pluie de clous# surplombe", /*spanish*/"los #pinchos de un techo# conducen a", /*italian*/"la #pioggia d'acciaio# blocca la via per", /*german*/"hinter #fallenden Stacheln#, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_MQ_FALLING_SPIKES_LOWER_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#falling spikes# block the path to", /*french*/"la #pluie de clous# surplombe", /*spanish*/"los #pinchos de un techo# conducen a", /*italian*/"la #pioggia d'acciaio# blocca la via per", /*german*/"hinter #fallenden Stacheln#, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_MQ_FALLING_SPIKES_UPPER_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#falling spikes# block the path to", /*french*/"la #pluie de clous# surplombe", /*spanish*/"los #pinchos de un techo# conducen a", /*italian*/"la #pioggia d'acciaio# blocca la via per", /*german*/"hinter #fallenden Stacheln#, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_MQ_INVISIBLE_SPIKES_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #dead roam among invisible spikes# guarding", /*french*/"#parmi les clous invisibles# du temple de l'ombre se cache", /*spanish*/"los #muertos que vagan por pinchos invisibles# protegen", /*italian*/"i #morti vaganti fra spine invisibili# possiedono", /*german*/"in einer, #von den Toten beschützten Truhe#, nahe unsichtbarer Stacheln, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_MQ_BOSS_KEY_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#walls consumed by a ball of fire# reveal", /*french*/"le #piège de bois# du temple de l'ombre cache", /*spanish*/"las #paredes consumidas por una esfera ígnea# revelan", /*italian*/"#pareti lignee deboli alla sfera ignea# coprono", /*german*/"hinter #feueranfälligen Wänden#, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_MQ_SPIKE_WALLS_LEFT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#walls consumed by a ball of fire# reveal", /*french*/"le #piège de bois# du temple de l'ombre cache", /*spanish*/"las #paredes consumidas por una esfera ígnea# revelan", /*italian*/"#pareti lignee deboli alla sfera ignea# coprono", /*german*/"hinter #feueranfälligen Wänden#, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_MQ_STALFOS_ROOM_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"near an #empty pedestal# within the Shadow Temple lies", /*french*/"#près d'un pédestal vide du temple de l'ombre# gît", /*spanish*/"cerca de un #vacío pedestal# del Templo de las Sombras yace", /*italian*/"vicino a un #piedistallo vuoto# nel Santuario dell'Ombra puoi trovare", /*german*/"nahe eines #leeren Podests# des Schattentempels, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_MQ_INVISIBLE_BLADES_INVISIBLE_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#invisible blades# guard", /*french*/"les #faucheurs invisibles# du temple de l'ombre protègent", /*spanish*/"unas #hojas invisibles# guardan", /*italian*/"delle #falci invisibili# nel Santuario dell'Ombra proteggono", /*german*/"nahe #unsichtbarer Klingen#, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_MQ_INVISIBLE_BLADES_VISIBLE_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#invisible blades# guard", /*french*/"les #faucheurs invisibles# du temple de l'ombre protègent", /*spanish*/"unas #hojas invisibles# guardan", /*italian*/"delle #falci invisibili# nel Santuario dell'Ombra proteggono", /*german*/"nahe #unsichtbarer Klingen#, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_MQ_WIND_HINT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"an #invisible chest guarded by the dead# holds", /*french*/"le #trésor invisible du cul-de-sac# du temple de l'ombre contient", /*spanish*/"un #cofre invisible custodiado por los del más allá# contiene", /*italian*/"un #forziere invisibile in una strada chiusa# nel Santuario dell'Ombra contiene", /*german*/"in einer #unsichtbaren, von den Toten beschützten Truhe#, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_MQ_AFTER_WIND_HIDDEN_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#mummies guarding a ferry# hide", /*french*/"les #Gibdos qui bloquent le traversier# cachent", /*spanish*/"las #momias que protegen un navío# esconden", /*italian*/"delle #mummie presso un traghetto infernale# nascondono", /*german*/"nahe #Mumien, die eine Fähre# bewachen, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_MQ_AFTER_WIND_ENEMY_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#mummies guarding a ferry# hide", /*french*/"les #Gibdos qui bloquent le traversier# cachent", /*spanish*/"las #momias que protegen un navío# esconden", /*italian*/"delle #mummie presso un traghetto infernale# nascondono", /*german*/"nahe #Mumien, die eine Fähre# bewachen, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_MQ_NEAR_SHIP_INVISIBLE_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#caged near a ship# lies", /*french*/"#dans une cage près du traversier# gît", /*spanish*/"#entre rejas al lado de un navío# yace", /*italian*/"#in una gabbia vicino a un traghetto infernale# puoi trovare", /*german*/"in einem #Käfig, nahe eines Schiffes#, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_MQ_FREESTANDING_KEY] = HintText::Exclude({
                       // obscure text
                       Text{"#behind three burning skulls# lies", /*french*/"#derrière trois crânes enflammés# gît", /*spanish*/"tras #tres ardientes calaveras# yace", /*italian*/"#dietro tre vasi a forma di teschio# puoi trovare", /*german*/"hinter #drei brennenden Schädeln#, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_BONGO_BONGO_HEART] = HintText::Exclude({
                       // obscure text
                       Text{"the #Phantom Shadow Beast# holds", /*french*/"le #monstre de l'ombre# possède", /*spanish*/"la #alimaña oscura espectral# porta", /*italian*/"la #bestia delle tenebre# possiede", /*german*/"nahe der #bestialischen Schattenmonstrosität#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"#Bongo Bongo# holds", /*french*/"#Bongo Bongo# possède", /*spanish*/"#Bongo Bongo# porta", /*italian*/"#Bongo Bongo# possiede", /*german*/"nahe #Bongo Bongo#, |wäre|wären|"}
    );

    hintTable[SHADOW_TEMPLE_GS_SINGLE_GIANT_POT] = HintText::Exclude({
                       // obscure text
                       Text{"#beyond a burning skull# lies a spider with", /*french*/"une #Skulltula derrière un crâne enflammé du temple de l'ombre# a", /*spanish*/"#tras una ardiente calavera# yace una Skulltula que otorga", /*italian*/"#dietro un vaso a forma di teschio# si nasconde un ragno con", /*german*/"in einer Spinne hinter #einem brennenden Schädel#, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_GS_FALLING_SPIKES_ROOM] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider beyond falling spikes# holds", /*french*/"une #Skulltula au delà de la pluie de clous du temple de l'ombre# a", /*spanish*/"una #Skulltula tras los pinchos del techo# otorga", /*italian*/"un #ragno oltre la pioggia d'acciaio# nasconde", /*german*/"in einer #Spinne hinter fallenden Stacheln#, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_GS_TRIPLE_GIANT_POT] = HintText::Exclude({
                       // obscure text
                       Text{"#beyond three burning skulls# lies a spider with", /*french*/"une #Skulltula derrière trois crânes enflammés du temple de l'ombre# a", /*spanish*/"#tras tres ardientes calaveras# yace una Skulltula que otorga", /*italian*/"#oltre tre vasi a forma di teschio# si nasconde un ragno con", /*german*/"in einer Spinne hinter #drei brennenden Schädeln#, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_GS_LIKE_LIKE_ROOM] = HintText::Exclude({
                       // obscure text
                       Text{"a spider guarded by #invisible blades# holds", /*french*/"une #Skulltula protégée par les faucheurs invisibles du temple de l'ombre# a", /*spanish*/"una #Skulltula custodiada por hojas invisibles# otorga", /*italian*/"un ragno protetto da #falci invisibili# nel Santuario dell'Ombra nasconde", /*german*/"in einer Spinne, nahe #unsichtbarer Klingen#, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_GS_NEAR_SHIP] = HintText::Exclude({
                       // obscure text
                       Text{"a spider near a #docked ship# hoards", /*french*/"une #Skulltula près du traversier du temple de l'ombre# a", /*spanish*/"una #Skulltula cercana a un navío# otorga", /*italian*/"un ragno vicino a un #traghetto infernale# nasconde", /*german*/"in einer Spinne, nahe eines #anlegenden Schiffes#, |wäre|wären|"},
    });


    hintTable[SHADOW_TEMPLE_MQ_GS_FALLING_SPIKES_ROOM] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider beyond falling spikes# holds", /*french*/"une #Skulltula au delà de la pluie de clous du temple de l'ombre# a", /*spanish*/"una #Skulltula tras los pinchos del techo# otorga", /*italian*/"un #ragno oltre la pioggia d'acciaio# nasconde", /*german*/"in einer #Spinne hinter fallenden Stacheln#, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_MQ_GS_WIND_HINT_ROOM] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider amidst roaring winds# in the Shadow Temple holds", /*french*/"une #Skulltula près des vents du temple de l'ombre# a", /*spanish*/"una #Skulltula entre ventarrones# del Templo de las Sombras otorga", /*italian*/"un ragno #oltre i 20# nel Santuario dell'Ombra nasconde", /*german*/"in einer #Spinne, nahe tosenden Winden# des Schattentempels, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_MQ_GS_AFTER_WIND] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider beneath gruesome debris# in the Shadow Temple hides", /*french*/"une #Skulltula sous des débris du temple de l'ombre# a", /*spanish*/"una #Skulltula bajo unos horripilantes escombros# del Templo de las Sombras otorga", /*italian*/"un ragno si nasconde #sotto i detriti# nel Santuario dell'Ombra tenendo", /*german*/"in einer #Spinne unter grausigen Trümmern# des Schattentempels, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_MQ_GS_AFTER_SHIP] = HintText::Exclude({
                       // obscure text
                       Text{"a #fallen statue# reveals a spider with", /*french*/"une #Skulltula près de la statue écroulée du temple de l'ombre# a", /*spanish*/"una #estatua caída# revelará una Skulltula que otorgue", /*italian*/"nel Santuario dell'Ombra una #statua cade# vicino a un ragno con", /*german*/"in einer Spinne, nahe einer #umgefallenen Statue#, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_MQ_GS_NEAR_BOSS] = HintText::Exclude({
                       // obscure text
                       Text{"a #suspended spider# guards", /*french*/"une #Skulltula près du repère du temple de l'ombre# a", /*spanish*/"una #Skulltula flotante# del Templo de las Sombras otorga", /*italian*/"un #ragno fluttuante# nel Santuario dell'Ombra nasconde", /*german*/"in der #einsamen Spinne# des Schattentempels, |wäre|wären|"},
    });

    /*--------------------------
    |    BOTTOM OF THE WELL    |
    ---------------------------*/
    hintTable[BOTTOM_OF_THE_WELL_FRONT_LEFT_FAKE_WALL_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #Eye of Truth in the well# reveals", /*french*/"l'#oeil de vérité dans le puits# révèle", /*spanish*/"el #Ojo de la Verdad en el pozo# revela", /*italian*/"l'#occhio della verità nel pozzo# rivela", /*german*/"ein, vom #Auge der Wahrheit# aufgedecktes Geheimnis des Brunnens, |wäre|wären|"},
    });

    hintTable[BOTTOM_OF_THE_WELL_FRONT_CENTER_BOMBABLE_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#gruesome debris# in the well hides", /*french*/"des #débris dans le puits# cachent", /*spanish*/"unos #horripilantes escombros# del pozo esconden", /*italian*/"#dei detriti nel pozzo# coprono", /*german*/"unter #grausigen Trümmern# des Brunnens, |wäre|wären|"},
    });

    hintTable[BOTTOM_OF_THE_WELL_RIGHT_BOTTOM_FAKE_WALL_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #Eye of Truth in the well# reveals", /*french*/"l'#oeil de vérité dans le puits# révèle", /*spanish*/"el #Ojo de la Verdad en el pozo# revela", /*italian*/"l'#occhio della verità nel pozzo# rivela", /*german*/"ein, vom #Auge der Wahrheit# aufgedecktes Geheimnis des Brunnens, |wäre|wären|"},
    });

    hintTable[BOTTOM_OF_THE_WELL_COMPASS_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #hidden entrance to a cage# in the well leads to", /*french*/"dans un #chemin caché dans le puits# gît", /*spanish*/"la #entrada oculta de una celda# del pozo conduce a", /*italian*/"una #gabbia con un ingresso nascosto# nel pozzo contiene", /*german*/"in einem #Käfig# des Brunnens, #mit verstecktem Eingang#, |wäre|wären|"},
    });

    hintTable[BOTTOM_OF_THE_WELL_CENTER_SKULLTULA_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider guarding a cage# in the well protects", /*french*/"l'#araignée dans la cage du puits# protège", /*spanish*/"una #araña protegiendo una celda# del pozo guarda", /*italian*/"un #ragno in una gabbia# nel pozzo protegge", /*german*/"in einem, #von einer Spinne beschützten Käfig# des Brunnens, |wäre|wären|"},
    });

    hintTable[BOTTOM_OF_THE_WELL_BACK_LEFT_BOMBABLE_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#gruesome debris# in the well hides", /*french*/"des #débris dans le puits# cachent", /*spanish*/"unos #horripilantes escombros# del pozo esconden", /*italian*/"#dei detriti nel pozzo# coprono", /*german*/"unter #grausigen Trümmern# des Brunnens, |wäre|wären|"},
    });

    hintTable[BOTTOM_OF_THE_WELL_INVISIBLE_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#Dead Hand's invisible secret# is", /*french*/"le #trésor invisible du Poigneur# est", /*spanish*/"el #secreto invisible de la Mano Muerta# esconde", /*italian*/"il #segreto invisibile dello Smaniosso# è", /*german*/"#Hirnsaugers unsichtbares Geheimnis#, |wäre|wären|"},
    });

    hintTable[BOTTOM_OF_THE_WELL_UNDERWATER_FRONT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #royal melody in the well# uncovers", /*french*/"la #mélodie royale révèle dans le puits#", /*spanish*/"una #melodía real en el pozo# revela", /*italian*/"una #melodia regale# nel pozzo asciuga", /*german*/"nach #hoheitlicher Musik im Brunnen#, |wäre|wären|"},
    });

    hintTable[BOTTOM_OF_THE_WELL_UNDERWATER_LEFT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #royal melody in the well# uncovers", /*french*/"la #mélodie royale révèle dans le puits#", /*spanish*/"una #melodía real en el pozo# revela", /*italian*/"una #melodia regale# nel pozzo asciuga", /*german*/"nach #hoheitlicher Musik im Brunnen#, |wäre|wären|"},
    });

    hintTable[BOTTOM_OF_THE_WELL_MAP_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"in the #depths of the well# lies", /*french*/"#dans le cœur du puits# gît", /*spanish*/"en las #profundidades del pozo# yace", /*italian*/"nelle #profondità del pozzo# puoi trovare", /*german*/"in den #Tiefen des Brunnens#, |wäre|wären|"},
    });

    hintTable[BOTTOM_OF_THE_WELL_FIRE_KEESE_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#perilous pits# in the well guard the path to", /*french*/"#trois trous# dans le puits protègent", /*spanish*/"#peligrosos fosos# del pozo conducen a", /*italian*/"fra #pericolose fosse# nel pozzo puoi trovare", /*german*/"nahe #gefährlicher Schächte# des Brunnens, |wäre|wären|"},
    });

    hintTable[BOTTOM_OF_THE_WELL_LIKE_LIKE_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#locked in a cage# in the well lies", /*french*/"#dans une cage# du puits gît", /*spanish*/"#entre rejas# en el pozo yace", /*italian*/"una #gabbia chiusa# nel pozzo contiene", /*german*/"in einem #verschlossenen Käfig# des Brunnens, |wäre|wären|"},
    });

    hintTable[BOTTOM_OF_THE_WELL_FREESTANDING_KEY] = HintText::Exclude({
                       // obscure text
                       Text{"#inside a coffin# hides", /*french*/"dans #un cercueil# gît", /*spanish*/"en el #interior de un ataúd# yace", /*italian*/"#dentro una bara# puoi trovare", /*german*/"in einem #Sarg#, |wäre|wären|"},
    });

            hintTable[BOTTOM_OF_THE_WELL_CENTER_ROOM_PIT_FALL_BLUE_RUPEE_1] = HintText::Exclude({
                       // obscure text
                       Text{"EN: BOTTOM_OF_THE_WELL_CENTER_ROOM_PIT_FALL_BLUE_RUPEE_1 Hint", /*french*/"FR: BOTTOM_OF_THE_WELL_CENTER_ROOM_PIT_FALL_BLUE_RUPEE_1 Hint", /*spanish*/"ES: BOTTOM_OF_THE_WELL_CENTER_ROOM_PIT_FALL_BLUE_RUPEE_1 Hint", /*italian*/"IT: BOTTOM_OF_THE_WELL_CENTER_ROOM_PIT_FALL_BLUE_RUPEE_1 Hint", /*german*/"DE: BOTTOM_OF_THE_WELL_CENTER_ROOM_PIT_FALL_BLUE_RUPEE_1 Hint"},
                     }
    );
            hintTable[BOTTOM_OF_THE_WELL_CENTER_ROOM_PIT_FALL_BLUE_RUPEE_2] = HintText::Exclude({
                       // obscure text
                       Text{"EN: BOTTOM_OF_THE_WELL_CENTER_ROOM_PIT_FALL_BLUE_RUPEE_2 Hint", /*french*/"FR: BOTTOM_OF_THE_WELL_CENTER_ROOM_PIT_FALL_BLUE_RUPEE_2 Hint", /*spanish*/"ES: BOTTOM_OF_THE_WELL_CENTER_ROOM_PIT_FALL_BLUE_RUPEE_2 Hint", /*italian*/"IT: BOTTOM_OF_THE_WELL_CENTER_ROOM_PIT_FALL_BLUE_RUPEE_2 Hint", /*german*/"DE: BOTTOM_OF_THE_WELL_CENTER_ROOM_PIT_FALL_BLUE_RUPEE_2 Hint"},
                     }
    );
            hintTable[BOTTOM_OF_THE_WELL_CENTER_ROOM_PIT_FALL_BLUE_RUPEE_3] = HintText::Exclude({
                       // obscure text
                       Text{"EN: BOTTOM_OF_THE_WELL_CENTER_ROOM_PIT_FALL_BLUE_RUPEE_3 Hint", /*french*/"FR: BOTTOM_OF_THE_WELL_CENTER_ROOM_PIT_FALL_BLUE_RUPEE_3 Hint", /*spanish*/"ES: BOTTOM_OF_THE_WELL_CENTER_ROOM_PIT_FALL_BLUE_RUPEE_3 Hint", /*italian*/"IT: BOTTOM_OF_THE_WELL_CENTER_ROOM_PIT_FALL_BLUE_RUPEE_3 Hint", /*german*/"DE: BOTTOM_OF_THE_WELL_CENTER_ROOM_PIT_FALL_BLUE_RUPEE_3 Hint"},
                     }
    );
            hintTable[BOTTOM_OF_THE_WELL_CENTER_ROOM_PIT_FALL_BLUE_RUPEE_4] = HintText::Exclude({
                       // obscure text
                       Text{"EN: BOTTOM_OF_THE_WELL_CENTER_ROOM_PIT_FALL_BLUE_RUPEE_4 Hint", /*french*/"FR: BOTTOM_OF_THE_WELL_CENTER_ROOM_PIT_FALL_BLUE_RUPEE_4 Hint", /*spanish*/"ES: BOTTOM_OF_THE_WELL_CENTER_ROOM_PIT_FALL_BLUE_RUPEE_4 Hint", /*italian*/"IT: BOTTOM_OF_THE_WELL_CENTER_ROOM_PIT_FALL_BLUE_RUPEE_4 Hint", /*german*/"DE: BOTTOM_OF_THE_WELL_CENTER_ROOM_PIT_FALL_BLUE_RUPEE_4 Hint"},
                     }
    );
            hintTable[BOTTOM_OF_THE_WELL_CENTER_ROOM_PIT_FALL_BLUE_RUPEE_5] = HintText::Exclude({
                       // obscure text
                       Text{"EN: BOTTOM_OF_THE_WELL_CENTER_ROOM_PIT_FALL_BLUE_RUPEE_5 Hint", /*french*/"FR: BOTTOM_OF_THE_WELL_CENTER_ROOM_PIT_FALL_BLUE_RUPEE_5 Hint", /*spanish*/"ES: BOTTOM_OF_THE_WELL_CENTER_ROOM_PIT_FALL_BLUE_RUPEE_5 Hint", /*italian*/"IT: BOTTOM_OF_THE_WELL_CENTER_ROOM_PIT_FALL_BLUE_RUPEE_5 Hint", /*german*/"DE: BOTTOM_OF_THE_WELL_CENTER_ROOM_PIT_FALL_BLUE_RUPEE_5 Hint"},
                     }
    );


    hintTable[BOTTOM_OF_THE_WELL_MQ_MAP_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #royal melody in the well# uncovers", /*french*/"la #mélodie royale révèle dans le puits#", /*spanish*/"una #melodía real en el pozo# revela", /*italian*/"una #melodia regale# nel pozzo sblocca", /*german*/"nach #hoheitlicher Musik im Brunnen#, |wäre|wären|"},
    });

    hintTable[BOTTOM_OF_THE_WELL_MQ_LENS_OF_TRUTH_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"an #army of the dead# in the well guards", /*french*/"l'#armée des morts# dans le puits protège", /*spanish*/"un #ejército del más allá# del pozo guarda", /*italian*/"una #famiglia di morti# nel pozzo protegge", /*german*/"nahe der #Armee der Toten# des Brunnens, |wäre|wären|"},
    });

    hintTable[BOTTOM_OF_THE_WELL_MQ_DEAD_HAND_FREESTANDING_KEY] = HintText::Exclude({
                       // obscure text
                       Text{"#Dead Hand's explosive secret# is", /*french*/"le #secret explosif du Poigneur# est", /*spanish*/"el #explosivo secreto de la Mano Muerta# esconde", /*italian*/"il #segreto sepolto dello Smaniosso# è", /*german*/"#Hirnsaugers explosives Geheimnis#, |wäre|wären|"},
    });

    hintTable[BOTTOM_OF_THE_WELL_MQ_EAST_INNER_ROOM_FREESTANDING_KEY] = HintText::Exclude({
                       // obscure text
                       Text{"an #invisible path in the well# leads to", /*french*/"dans un #chemin caché dans le puits# gît", /*spanish*/"un #camino invisible del pozo# conduce a", /*italian*/"un #sentiero invisibile# nel pozzo porta verso", /*german*/"hinter einem #unsichtbaren Pfad des Brunnens#, |wäre|wären|"},
    });

    hintTable[BOTTOM_OF_THE_WELL_GS_LIKE_LIKE_CAGE] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider locked in a cage# in the well holds", /*french*/"une #Skulltula dans une cage au fonds du puits# a", /*spanish*/"una #Skulltula enjaulada# del pozo otorga", /*italian*/"un #ragno prigioniero# nel pozzo possiede", /*german*/"in der #Spinne, eines verschlossenen Käfigs# des Brunnens#, |wäre|wären|"},
    });

    hintTable[BOTTOM_OF_THE_WELL_GS_EAST_INNER_ROOM] = HintText::Exclude({
                       // obscure text
                       Text{"an #invisible path in the well# leads to", /*french*/"une #Skulltula dans le chemin invisible au fonds du puits# a", /*spanish*/"un #camino invisible del pozo# conduce a una Skulltula que otorga", /*italian*/"un #sentiero invisibile# nel pozzo porta verso un ragno con", /*german*/"hinter einem #unsichtbaren Pfad des Brunnens#, |wäre|wären|"},
    });

    hintTable[BOTTOM_OF_THE_WELL_GS_WEST_INNER_ROOM] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider locked in a crypt# within the well guards", /*french*/"une #Skulltula embarrée dans la crypte au fonds du puits# a", /*spanish*/"una #Skulltula encerrada en una cripta# del pozo otorga", /*italian*/"un #ragno in una cripta# nel pozzo possiede", /*german*/"in der #Spinne, einer verschlossenen Krypta# des Brunnens, |wäre|wären|"},
    });


    hintTable[BOTTOM_OF_THE_WELL_MQ_GS_BASEMENT] = HintText::Exclude({
                       // obscure text
                       Text{"a #gauntlet of invisible spiders# protects", /*french*/"une #Skulltula protégée par les araignées invisibles au fonds du puits# a", /*spanish*/"unas #arañas invisibles# custodian una Skulltula que otorga", /*italian*/"un #ragno protetto da una sfilza di simili invisibili# nel pozzo possiede", /*german*/"in der Spinne hinter einem #arachniden Spießrutenlauf#, |wäre|wären|"},
    });

    hintTable[BOTTOM_OF_THE_WELL_MQ_GS_COFFIN_ROOM] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider crawling near the dead# in the well holds", /*french*/"une #Skulltula près des cercueils au fonds du puits# a", /*spanish*/"una #Skulltula junto a los muertos# del pozo otorga", /*italian*/"un #ragno dietro alle bare# nel pozzo nasconde", /*german*/"in der #Spinne, nahe Särgen# des Brunnens, |wäre|wären|"},
    });

    hintTable[BOTTOM_OF_THE_WELL_MQ_GS_WEST_INNER_ROOM] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider locked in a crypt# within the well guards", /*french*/"une #Skulltula embarrée dans la crypte au fonds du puits# a", /*spanish*/"una #Skulltula encerrada en una cripta# del pozo otorga", /*italian*/"un #ragno in una cripta# nel pozzo possiede", /*german*/"in der #Spinne, einer verschlossenen Krypta# des Brunnens, |wäre|wären|"},
    });

    /*--------------------------
    |        ICE CAVERN        |
    ---------------------------*/
    hintTable[ICE_CAVERN_MAP_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#winds of ice# surround", /*french*/"#figé dans la glace rouge# gît", /*spanish*/"#heladas borrascas# rodean", /*italian*/"dei #soffi gelati# circondano", /*german*/"von #eisigen Winden umgeben#, |wäre|wären|"},
    });

    hintTable[ICE_CAVERN_COMPASS_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #wall of ice# protects", /*french*/"#un mur de glace rouge# cache", /*spanish*/"una #gélida pared# protege", /*italian*/"un #muro di ghiaccio# cela", /*german*/"hinter einer #Wand aus Eis#, |wäre|wären|"},
    });

    hintTable[ICE_CAVERN_IRON_BOOTS_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #monster in a frozen cavern# guards", /*french*/"le #monstre de la caverne de glace# protège", /*spanish*/"un #monstruo de una helada caverna# guarda", /*italian*/"un #guardiano in una caverna ghiacciata# protegge", /*german*/"nahe eines #Monsters einer gefrorenen Höhle#, |wäre|wären|"},
    });

    hintTable[ICE_CAVERN_FREESTANDING_POH] = HintText::Exclude({
                       // obscure text
                       Text{"a #wall of ice# protects", /*french*/"un #mur de glace rouge# cache", /*spanish*/"una #gélida pared# protege", /*italian*/"un #muro di ghiaccio# cela", /*german*/"hinter einer #Wand aus Eis#, |wäre|wären|"},
    });
    hintTable[ICE_CAVERN_RED_ICE_BLUE_RUPEE] = HintText::Exclude({
                       // obscure text
                       Text{"EN: ICE_CAVERN_RED_ICE_BLUE_RUPEE Hint", /*french*/"FR: ICE_CAVERN_RED_ICE_BLUE_RUPEE Hint", /*spanish*/"ES: ICE_CAVERN_RED_ICE_BLUE_RUPEE Hint", /*italian*/"IT: ICE_CAVERN_RED_ICE_BLUE_RUPEE Hint", /*german*/"DE: ICE_CAVERN_RED_ICE_BLUE_RUPEE Hint"},
                     }
    );
        hintTable[ICE_CAVERN_PUSH_BLOCK_ROOM_RED_RUPEE_1] = HintText::Exclude({
                       // obscure text
                       Text{"EN: ICE_CAVERN_PUSH_BLOCK_ROOM_RED_RUPEE_1 Hint", /*french*/"FR: ICE_CAVERN_PUSH_BLOCK_ROOM_RED_RUPEE_1 Hint", /*spanish*/"ES: ICE_CAVERN_PUSH_BLOCK_ROOM_RED_RUPEE_1 Hint", /*italian*/"IT: ICE_CAVERN_PUSH_BLOCK_ROOM_RED_RUPEE_1 Hint", /*german*/"DE: ICE_CAVERN_PUSH_BLOCK_ROOM_RED_RUPEE_1 Hint"},
                     }
    );
        hintTable[ICE_CAVERN_PUSH_BLOCK_ROOM_RED_RUPEE_2] = HintText::Exclude({
                       // obscure text
                       Text{"EN: ICE_CAVERN_PUSH_BLOCK_ROOM_RED_RUPEE_2 Hint", /*french*/"FR: ICE_CAVERN_PUSH_BLOCK_ROOM_RED_RUPEE_2 Hint", /*spanish*/"ES: ICE_CAVERN_PUSH_BLOCK_ROOM_RED_RUPEE_2 Hint", /*italian*/"IT: ICE_CAVERN_PUSH_BLOCK_ROOM_RED_RUPEE_2 Hint", /*german*/"DE: ICE_CAVERN_PUSH_BLOCK_ROOM_RED_RUPEE_2 Hint"},
                     }
    );

        hintTable[ICE_CAVERN_PUSH_BLOCK_ROOM_RED_RUPEE_3] = HintText::Exclude({
                       // obscure text
                       Text{"EN: ICE_CAVERN_PUSH_BLOCK_ROOM_RED_RUPEE_3 Hint", /*french*/"FR: ICE_CAVERN_PUSH_BLOCK_ROOM_RED_RUPEE_3 Hint", /*spanish*/"ES: ICE_CAVERN_PUSH_BLOCK_ROOM_RED_RUPEE_3 Hint", /*italian*/"IT: ICE_CAVERN_PUSH_BLOCK_ROOM_RED_RUPEE_3 Hint", /*german*/"DE: ICE_CAVERN_PUSH_BLOCK_ROOM_RED_RUPEE_3 Hint"},
                     }
    );
    

    hintTable[ICE_CAVERN_MQ_IRON_BOOTS_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #monster in a frozen cavern# guards", /*french*/"le #monstre de la caverne de glace# protège", /*spanish*/"un #monstruo de una helada caverna# guarda", /*italian*/"un #guardiano in una caverna ghiacciata# protegge", /*german*/"nahe eines #Monsters einer gefrorenen Höhle#, |wäre|wären|"},
    });

    hintTable[ICE_CAVERN_MQ_COMPASS_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#winds of ice# surround", /*french*/"#entouré de vent glacial# gît", /*spanish*/"#heladas borrascas# rodean", /*italian*/"dei #soffi gelati# circondano", /*german*/"von #eisigen Winden umgeben#, |wäre|wären|"},
    });

    hintTable[ICE_CAVERN_MQ_MAP_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #wall of ice# protects", /*french*/"#un mur de glace rouge# cache", /*spanish*/"una #gélida pared# protege", /*italian*/"un #muro di ghiaccio# cela", /*german*/"hinter einer #Wand aus Eis#, |wäre|wären|"},
    });

    hintTable[ICE_CAVERN_MQ_FREESTANDING_POH] = HintText::Exclude({
                       // obscure text
                       Text{"#winds of ice# surround", /*french*/"#entouré de vent glacial# gît", /*spanish*/"#heladas borrascas# rodean", /*italian*/"dei #soffi gelati# circondano", /*german*/"von #eisigen Winden umgeben#, |wäre|wären|"},
    });

    hintTable[ICE_CAVERN_GS_PUSH_BLOCK_ROOM] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider above icy pits# holds", /*french*/"une #Skulltula au dessus d'un goufre glacial# a", /*spanish*/"una #Skulltula sobre gélidos vacíos# otorga", /*italian*/"un ragno #sopra un crepaccio nel ghiaccio# cela", /*german*/"in einer #Spinne über eisigen Abgründen#, |wäre|wären|"},
    });

    hintTable[ICE_CAVERN_GS_SPINNING_SCYTHE_ROOM] = HintText::Exclude({
                       // obscure text
                       Text{"#spinning ice# guards a spider holding", /*french*/"une #Skulltula près de deux lames de glace# a", /*spanish*/"unos #témpanos giratorios# custodian una Skulltula que otorga", /*italian*/"un ragno #sopra un tritaghiaccio# nasconde", /*german*/"in einer, von #rotierendem Eis# geschützten Spinne, |wäre|wären|"},
    });

    hintTable[ICE_CAVERN_GS_HEART_PIECE_ROOM] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider behind a wall of ice# hides", /*french*/"une #Skulltula derrière un mur de glace# a", /*spanish*/"una #Skulltula tras una gélida pared# otorga", /*italian*/"un #ragno dietro un muro di ghiaccio# cela", /*german*/"in einer #Spinne hinter einer Wand aus Eis#, |wäre|wären|"},
    });


    hintTable[ICE_CAVERN_MQ_GS_SCARECROW] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider above icy pits# holds", /*french*/"une #Skulltula au dessus d'un goufre glacial# a", /*spanish*/"una #Skulltula sobre gélidos vacíos# otorga", /*italian*/"un ragno #presso un crepaccio nel ghiaccio# cela", /*german*/"in einer #Spinne über eisigen Abgründen#, |wäre|wären|"},
    });

    hintTable[ICE_CAVERN_MQ_GS_ICE_BLOCK] = HintText::Exclude({
                       // obscure text
                       Text{"a #web of ice# surrounds a spider with", /*french*/"une #Skulltula protégée d'une toile glacée# a", /*spanish*/"una #gélida red# rodea a una Skulltula que otorga", /*italian*/"un #ragno in una tela di ghiaccio# si nasconde con", /*german*/"in einer Spinne in #eisigen Spinnenweben#, |wäre|wären|"},
    });

    hintTable[ICE_CAVERN_MQ_GS_RED_ICE] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider in fiery ice# hoards", /*french*/"une #Skulltula figée dans la glace rouge# a", /*spanish*/"una #Skulltula tras un ardiente hielo# otorga", /*italian*/"un ragno nel #fuoco ghiacciato# ha", /*german*/"in einer #Spinne in feurigem Eis#, |wäre|wären|"},
    });

    /*--------------------------
    | GERUDO TRAINING GROUNDS  |
    ---------------------------*/
    hintTable[GERUDO_TRAINING_GROUNDS_LOBBY_LEFT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #blinded eye in the Gerudo Training Grounds# drops", /*french*/"l'#Oeil dans le gymnase Gerudo# voit", /*spanish*/"#cegar un ojo en el Centro de Instrucción Gerudo# revela", /*italian*/"un #occhio accecato nella zona di addestramento Gerudo# mostra", /*german*/"nahe eines #geblendeten Auges# des Trainings der Diebe, |wäre|wären|"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_LOBBY_RIGHT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #blinded eye in the Gerudo Training Grounds# drops", /*french*/"l'#Oeil dans le gymnase Gerudo# voit", /*spanish*/"#cegar un ojo en el Centro de Instrucción Gerudo# revela", /*italian*/"un #occhio accecato nella zona di addestramento Gerudo# mostra", /*german*/"nahe eines #geblendeten Auges# des Trainings der Diebe, |wäre|wären|"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_STALFOS_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#soldiers walking on shifting sands# in the Gerudo Training Grounds guard", /*french*/"les #squelettes# du gymnase Gerudo protègent", /*spanish*/"#soldados en resbaladizas arenas# del Centro de Instrucción Gerudo protegen", /*italian*/"addestrarsi combattendo #soldati sulla sabbia# procura", /*german*/"nahe, auf #Treibsand laufenden Soldaten# des Training der Diebe, |wäre|wären|"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_BEAMOS_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#reptilian warriors# in the Gerudo Training Grounds protect", /*french*/"les #lézards# dans le gymnase Gerudo protègent", /*spanish*/"#unos escamosos guerreros# del Centro de Instrucción Gerudo protegen", /*italian*/"addestrarsi combattendo #rettili guerrieri# procura", /*german*/"nahe #reptilen Kriegern# des Trainings der Diebe, |wäre|wären|"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_HIDDEN_CEILING_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #Eye of Truth# in the Gerudo Training Grounds reveals", /*french*/"#bien caché# dans le gymnase Gerudo gît", /*spanish*/"el #Ojo de la Verdad# en el Centro de Instrucción Gerudo revela", /*italian*/"l'#occhio della verità nella zona di addestramento Gerudo# mostra la via per", /*german*/"ein, vom #Auge der Wahrheit# aufgedecktes Geheimnis des Trainings der Diebe, |wäre|wären|"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MAZE_PATH_FIRST_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the first prize of #the thieves' training# is", /*french*/"le #premier trésor du gymnase Gerudo# est", /*spanish*/"el primer premio de la #instrucción bandida# se trata de", /*italian*/"la prima ricompensa dell'#allenamento dei ladri# è", /*german*/"der #erste Preis# des Trainings der Diebe, |wäre|wären|"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MAZE_PATH_SECOND_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the second prize of #the thieves' training# is", /*french*/"le #deuxième trésor du gymnase Gerudo# est", /*spanish*/"el segundo premio de la #instrucción bandida# se trata de", /*italian*/"la seconda ricompensa dell'#allenamento dei ladri# è", /*german*/"der #zweite Preis# des Trainings der Diebe, |wäre|wären|"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MAZE_PATH_THIRD_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the third prize of #the thieves' training# is", /*french*/"le #troisième trésor du gymnase Gerudo# est", /*spanish*/"el tercer premio de la #instrucción bandida# se trata de", /*italian*/"la terza ricompensa dell'#allenamento dei ladri# è", /*german*/"der #dritte Preis# des Trainings der Diebe, |wäre|wären|"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MAZE_RIGHT_CENTRAL_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #Song of Time# in the Gerudo Training Grounds leads to", /*french*/"le #chant du temps# révèle dans le gymnase Gerudo", /*spanish*/"la #Canción del Tiempo# en el Centro de Instrucción Gerudo conduce a", /*italian*/"la #Canzone del tempo# nella zona di addestramento Gerudo apre la via per", /*german*/"nach der #Hymne der Zeit# beim Training der Diebe, |wäre|wären|"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MAZE_RIGHT_SIDE_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #Song of Time# in the Gerudo Training Grounds leads to", /*french*/"le #chant du temps# révèle dans le gymnase Gerudo", /*spanish*/"la #Canción del Tiempo# en el Centro de Instrucción Gerudo conduce a", /*italian*/"la #Canzone del tempo# nella zona di addestramento Gerudo apre la via per", /*german*/"nach der #Hymne der Zeit# beim Training der Diebe, |wäre|wären|"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_HAMMER_ROOM_CLEAR_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#fiery foes# in the Gerudo Training Grounds guard", /*french*/"les #limaces de feu# du gymnase Gerudo protègent", /*spanish*/"unos #flamígeros enemigos# del Centro de Instrucción Gerudo guardan", /*italian*/"addestrarsi #combattendo nemici di fuoco# procura", /*german*/"nahe #feurigen Feinden# des Trainings der Diebe, |wäre|wären|"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_HAMMER_ROOM_SWITCH_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#engulfed in flame# where thieves train lies", /*french*/"le #trésor enflammé# du gymnase Gerudo est", /*spanish*/"donde entrenan las bandidas #entre llamas# yace", /*italian*/"un forziere #circondato di fiamme# dove i ladri si addestrano contiene", /*german*/"in einer #flammenden Truhe# des Trainings der Diebe, |wäre|wären|"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_EYE_STATUE_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"thieves #blind four faces# to find", /*french*/"l'#épreuve d'archerie# du gymnase Gerudo donne", /*spanish*/"las bandidas #ciegan cuatro bustos# para hallar", /*italian*/"addestrarsi #accecando statue# procura", /*german*/"nahe #vier geblendeter Augen#, |wäre|wären|"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_NEAR_SCARECROW_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"thieves #blind four faces# to find", /*french*/"l'#épreuve d'archerie# du gymnase Gerudo donne", /*spanish*/"las bandidas #ciegan cuatro bustos# para hallar", /*italian*/"addestrarsi #accecando statue# procura", /*german*/"nahe #vier geblendeter Augen#, |wäre|wären|"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_BEFORE_HEAVY_BLOCK_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#before a block of silver# thieves can find", /*french*/"#près d'un bloc argent# dans le gymnase Gerudo gît", /*spanish*/"#ante un plateado bloque# las bandidas hallan", /*italian*/"addestrarsi #di fronte a un blocco d'argento# procura", /*german*/"vor einem #silbernen Block# des Trainings der Diebe, |wäre|wären|"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_FIRST_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #feat of strength# rewards thieves with", /*french*/"#derrière un bloc argent# dans le gymnase Gerudo gît", /*spanish*/"una #hazaña de fuerza# premia a las bandidas con", /*italian*/"addestrarsi #spingendo un blocco d'argento# procura", /*german*/"hinter einem #Kraftakt# des Trainings der Diebe, |wäre|wären|"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_SECOND_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #feat of strength# rewards thieves with", /*french*/"#derrière un bloc argent# dans le gymnase Gerudo gît", /*spanish*/"una #hazaña de fuerza# premia a las bandidas con", /*italian*/"addestrarsi #spingendo un blocco d'argento# procura", /*german*/"hinter einem #Kraftakt# des Trainings der Diebe, |wäre|wären|"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_THIRD_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #feat of strength# rewards thieves with", /*french*/"#derrière un bloc argent# dans le gymnase Gerudo gît", /*spanish*/"una #hazaña de fuerza# premia a las bandidas con", /*italian*/"addestrarsi #spingendo un blocco d'argento# procura", /*german*/"hinter einem #Kraftakt# des Trainings der Diebe, |wäre|wären|"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_FOURTH_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #feat of strength# rewards thieves with", /*french*/"#derrière un bloc argent# dans le gymnase Gerudo gît", /*spanish*/"una #hazaña de fuerza# premia a las bandidas con", /*italian*/"addestrarsi #spingendo un blocco d'argento# procura", /*german*/"hinter einem #Kraftakt# des Trainings der Diebe, |wäre|wären|"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_FREESTANDING_KEY] = HintText::Exclude({
                       // obscure text
                       Text{"the #Song of Time# in the Gerudo Training Grounds leads to", /*french*/"le #chant du temps# révèle dans le gymnase Gerudo", /*spanish*/"la #Canción del Tiempo# en el Centro de Instrucción Gerudo conduce a", /*italian*/"la #Canzone del tempo# nella zona di addestramento Gerudo apre la via per", /*german*/"nach der #Hymne der Zeit# beim Training der Diebe, |wäre|wären|"},
    });


    hintTable[GERUDO_TRAINING_GROUNDS_MQ_LOBBY_RIGHT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#thieves prepare for training# with", /*french*/"dans #l'entrée du gymnase Gerudo# gît", /*spanish*/"las #bandidas se instruyen# con", /*italian*/"i #ladri si preparano all'addestramento# con", /*german*/"vor dem Training der Diebe, |wäre|wären|"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MQ_LOBBY_LEFT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#thieves prepare for training# with", /*french*/"dans #l'entrée du gymnase Gerudo# gît", /*spanish*/"las #bandidas se instruyen# con", /*italian*/"i #ladri si preparano all'addestramento# con", /*german*/"vor dem Training der Diebe, |wäre|wären|"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MQ_FIRST_IRON_KNUCKLE_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#soldiers walking on shifting sands# in the Gerudo Training Grounds guard", /*french*/"les #squelettes# du gymnase Gerudo protègent", /*spanish*/"#soldados en resbaladizas arenas# del Centro de Instrucción Gerudo protegen", /*italian*/"addestrarsi combattendo un #soldato sulla sabbia# procura", /*german*/"nahe, auf #Treibsand laufenden Soldaten# des Trainings der Diebe, |wäre|wären|"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MQ_BEFORE_HEAVY_BLOCK_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#before a block of silver# thieves can find", /*french*/"#près d'un bloc argent# dans le gymnase Gerudo gît", /*spanish*/"#ante un plateado bloque# las bandidas hallan", /*italian*/"addestrarsi #di fronte a un blocco d'argento# procura", /*german*/"vor einem #silbernen Block# des Trainings der Diebe, |wäre|wären|"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MQ_EYE_STATUE_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"thieves #blind four faces# to find", /*french*/"l'#épreuve d'archerie# du gymnase Gerudo donne", /*spanish*/"las bandidas #ciegan cuatro bustos# para hallar", /*italian*/"addestrarsi #accecando statue# procura", /*german*/"nahe #vier geblendeter Augen#, |wäre|wären|"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MQ_FLAME_CIRCLE_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#engulfed in flame# where thieves train lies", /*french*/"le #trésor enflammé# du gymnase Gerudo est", /*spanish*/"donde entrenan las bandidas #entre llamas# yace", /*italian*/"un forziere #circondato di fiamme# dove i ladri si addestrano contiene", /*german*/"in einer #flammenden Truhe# des Trainings der Diebe, |wäre|wären|"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MQ_SECOND_IRON_KNUCKLE_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#fiery foes# in the Gerudo Training Grounds guard", /*french*/"les #ennemis de feu# du gymnase Gerudo protègent", /*spanish*/"unos #flamígeros enemigos# del Centro de Instrucción Gerudo guardan", /*italian*/"addestrarsi #combattendo nemici di fuoco# procura", /*german*/"nahe #feurigen Feinden# des Trainings der Diebe, |wäre|wären|"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MQ_DINOLFOS_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#reptilian warriors# in the Gerudo Training Grounds protect", /*french*/"les #lézards# dans le gymnase Gerudo protègent", /*spanish*/"#unos escamosos guerreros# del Centro de Instrucción Gerudo protegen", /*italian*/"addestrarsi combattendo #rettili guerrieri# procura", /*german*/"nahe #reptilen Kriegern# des Trainings der Diebe, |wäre|wären|"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MQ_MAZE_RIGHT_CENTRAL_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #path of fire# leads thieves to", /*french*/"dans le #chemin enflammé# dans le gymnase Gerudo gît", /*spanish*/"un #camino de fuego# conduce a las bandidas a", /*italian*/"il #mare di fuoco# porta i ladri verso", /*german*/"hinter einem #feurigen Pfad# des Trainings der Diebe, |wäre|wären|"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MQ_MAZE_PATH_FIRST_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the first prize of #the thieves' training# is", /*french*/"le #premier trésor du gymnase Gerudo# est", /*spanish*/"el primer premio de la #instrucción bandida# se trata de", /*italian*/"la prima ricompensa dell'#allenamento dei ladri# è", /*german*/"der #erste Preis# des Trainings der Diebe, |wäre|wären|"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MQ_MAZE_RIGHT_SIDE_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #path of fire# leads thieves to", /*french*/"dans le #chemin enflammé# dans le gymnase Gerudo gît", /*spanish*/"un #camino de fuego# conduce a las bandidas a", /*italian*/"il #mare di fuoco# porta i ladri verso", /*german*/"hinter einem #feurigen Pfad# des Trainings der Diebe, |wäre|wären|"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MQ_MAZE_PATH_THIRD_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the third prize of #the thieves' training# is", /*french*/"le #troisième trésor du gymnase Gerudo# est", /*spanish*/"el tercer premio de la #instrucción bandida# se trata de", /*italian*/"la terza ricompensa dell'#allenamento dei ladri# è", /*german*/"der #dritte Preis# des Trainings der Diebe, |wäre|wären|"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MQ_MAZE_PATH_SECOND_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the second prize of #the thieves' training# is", /*french*/"le #deuxième trésor du gymnase Gerudo# est", /*spanish*/"el segundo premio de la #instrucción bandida# se trata de", /*italian*/"la seconda ricompensa dell'#allenamento dei ladri# è", /*german*/"der #zweite Preis# des Trainings der Diebe, |wäre|wären|"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MQ_HIDDEN_CEILING_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #Eye of Truth# in the Gerudo Training Grounds reveals", /*french*/"#bien caché# dans le gymnase Gerudo gît", /*spanish*/"el #Ojo de la Verdad# en el Centro de Instrucción Gerudo revela", /*italian*/"l'#occhio della verità nella zona di addestramento Gerudo# mostra la via per", /*german*/"ein, vom #Auge der Wahrheit# aufgedecktes Geheimnis des Trainings der Diebe, |wäre|wären|"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MQ_HEAVY_BLOCK_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #feat of strength# rewards thieves with", /*french*/"#derrière un bloc argent# dans le gymnase Gerudo gît", /*spanish*/"una #hazaña de fuerza# premia a las bandidas con", /*italian*/"addestrarsi #spingendo un blocco d'argento# procura", /*german*/"hinter einem #Kraftakt# des Trainings der Diebe, |wäre|wären|"},
    });

    /*--------------------------
    |      GANONS CASTLE       |
    ---------------------------*/
    hintTable[GANONS_TOWER_BOSS_KEY_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #Evil King# hoards", /*french*/"le #Roi du Mal# possède", /*spanish*/"el #Rey del Mal# acapara", /*italian*/"il #re del male# custodisce", /*german*/"der Schatz vom #Großmeister des Bösen#, |wäre|wären|"},
    });


    hintTable[GANONS_CASTLE_FOREST_TRIAL_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #test of the wilds# holds", /*french*/"l'#épreuve des bois# contient", /*spanish*/"la #prueba de la naturaleza# brinda", /*italian*/"la #prova della natura# cela", /*german*/"in der #Prüfung der Wildnis#, |wäre|wären|"},
    });

    hintTable[GANONS_CASTLE_WATER_TRIAL_LEFT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #test of the seas# holds", /*french*/"l'#épreuve des mers# contient", /*spanish*/"la #prueba del mar# brinda", /*italian*/"la #prova del mare# cela", /*german*/"in der #Prüfung des Meeres#, |wäre|wären|"},
    });

    hintTable[GANONS_CASTLE_WATER_TRIAL_RIGHT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #test of the seas# holds", /*french*/"l'#épreuve des mers# contient", /*spanish*/"la #prueba del mar# brinda", /*italian*/"la #prova del mare# cela", /*german*/"in der #Prüfung des Meeres#, |wäre|wären|"},
    });

    hintTable[GANONS_CASTLE_SHADOW_TRIAL_FRONT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#music in the test of darkness# unveils", /*french*/"la #musique dans l'épreuve des ténèbres# révèle", /*spanish*/"la #música en la prueba de la oscuridad# revela", /*italian*/"#musica nella prova dell'oscurità# apre la via per", /*german*/"nahe #Musik in der Prüfung der Dunkelheit#, |wäre|wären|"},
    });

    hintTable[GANONS_CASTLE_SHADOW_TRIAL_GOLDEN_GAUNTLETS_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#light in the test of darkness# unveils", /*french*/"la #lumière dans l'épreuve des ténèbres# révèle", /*spanish*/"la #luz en la prueba de la oscuridad# revela", /*italian*/"#luce nella prova dell'oscurità# apre la via per", /*german*/"nahe #Licht in der Prüfung der Dunkelheit#, |wäre|wären|"},
    });

    hintTable[GANONS_CASTLE_SPIRIT_TRIAL_CRYSTAL_SWITCH_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #test of the sands# holds", /*french*/"l'#épreuve des sables# contient", /*spanish*/"la #prueba de las arenas# brinda", /*italian*/"la #prova delle sabbie# cela", /*german*/"in der #Prüfung des Sandes#, |wäre|wären|"},
    });

    hintTable[GANONS_CASTLE_SPIRIT_TRIAL_INVISIBLE_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #test of the sands# holds", /*french*/"l'#épreuve des sables# contient", /*spanish*/"la #prueba de las arenas# brinda", /*italian*/"la #prova delle sabbie# cela", /*german*/"in der #Prüfung des Sandes#, |wäre|wären|"},
    });

    hintTable[GANONS_CASTLE_LIGHT_TRIAL_FIRST_LEFT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #test of radiance# holds", /*french*/"l'#épreuve du ciel# contient", /*spanish*/"la #prueba del resplandor# brinda", /*italian*/"la #prova dello splendore# cela", /*german*/"in der #Prüfung der Strahlen#, |wäre|wären|"},
    });

    hintTable[GANONS_CASTLE_LIGHT_TRIAL_SECOND_LEFT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #test of radiance# holds", /*french*/"l'#épreuve du ciel# contient", /*spanish*/"la #prueba del resplandor# brinda", /*italian*/"la #prova dello splendore# cela", /*german*/"in der #Prüfung der Strahlen#, |wäre|wären|"},
    });

    hintTable[GANONS_CASTLE_LIGHT_TRIAL_THIRD_LEFT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #test of radiance# holds", /*french*/"l'#épreuve du ciel# contient", /*spanish*/"la #prueba del resplandor# brinda", /*italian*/"la #prova dello splendore# cela", /*german*/"in der #Prüfung der Strahlen#, |wäre|wären|"},
    });

    hintTable[GANONS_CASTLE_LIGHT_TRIAL_FIRST_RIGHT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #test of radiance# holds", /*french*/"l'#épreuve du ciel# contient", /*spanish*/"la #prueba del resplandor# brinda", /*italian*/"la #prova dello splendore# cela", /*german*/"in der #Prüfung der Strahlen#, |wäre|wären|"},
    });

    hintTable[GANONS_CASTLE_LIGHT_TRIAL_SECOND_RIGHT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #test of radiance# holds", /*french*/"l'#épreuve du ciel# contient", /*spanish*/"la #prueba del resplandor# brinda", /*italian*/"la #prova dello splendore# cela", /*german*/"in der #Prüfung der Strahlen#, |wäre|wären|"},
    });

    hintTable[GANONS_CASTLE_LIGHT_TRIAL_THIRD_RIGHT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #test of radiance# holds", /*french*/"l'#épreuve du ciel# contient", /*spanish*/"la #prueba del resplandor# brinda", /*italian*/"la #prova dello splendore# cela", /*german*/"in der #Prüfung der Strahlen#, |wäre|wären|"},
    });

    hintTable[GANONS_CASTLE_LIGHT_TRIAL_INVISIBLE_ENEMIES_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #test of radiance# holds", /*french*/"l'#épreuve du ciel# contient", /*spanish*/"la #prueba del resplandor# brinda", /*italian*/"la #prova dello splendore# cela", /*german*/"in der #Prüfung der Strahlen#, |wäre|wären|"},
    });

    hintTable[GANONS_CASTLE_LIGHT_TRIAL_LULLABY_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#music in the test of radiance# reveals", /*french*/"la #musique dans l'épreuve du ciel# révèle", /*spanish*/"la #música en la prueba del resplandor# revela", /*italian*/"#musica nella prova dello splendore# cela", /*german*/"nahe #Musik in der Prüfung der Strahlen#, |wäre|wären|"},
    });


    hintTable[GANONS_CASTLE_MQ_WATER_TRIAL_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #test of the seas# holds", /*french*/"l'#épreuve des mers# contient", /*spanish*/"la #prueba del mar# brinda", /*italian*/"la #prova del mare# cela", /*german*/"in der #Prüfung des Meeres#, |wäre|wären|"},
    });

    hintTable[GANONS_CASTLE_MQ_FOREST_TRIAL_EYE_SWITCH_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #test of the wilds# holds", /*french*/"l'#épreuve des bois# contient", /*spanish*/"la #prueba de la naturaleza# brinda", /*italian*/"la #prova della natura# cela", /*german*/"in der #Prüfung der Wildnis#, |wäre|wären|"},
    });

    hintTable[GANONS_CASTLE_MQ_FOREST_TRIAL_FROZEN_EYE_SWITCH_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #test of the wilds# holds", /*french*/"l'#épreuve des bois# contient", /*spanish*/"la #prueba de la naturaleza# brinda", /*italian*/"la #prova della natura# cela", /*german*/"in der #Prüfung der Wildnis#, |wäre|wären|"},
    });

    hintTable[GANONS_CASTLE_MQ_LIGHT_TRIAL_LULLABY_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#music in the test of radiance# reveals", /*french*/"la #musique dans l'épreuve du ciel# révèle", /*spanish*/"la #música en la prueba del resplandor# revela", /*italian*/"#musica nella prova dello splendore# cela", /*german*/"nahe #Musik in der Prüfung der Strahlen#, |wäre|wären|"},
    });

    hintTable[GANONS_CASTLE_MQ_SHADOW_TRIAL_BOMB_FLOWER_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #test of darkness# holds", /*french*/"l'#épreuve des ténèbres# contient", /*spanish*/"la #prueba de la oscuridad# brinda", /*italian*/"la #prova dell'oscurità# cela", /*german*/"in der #Prüfung der Dunkelheit#, |wäre|wären|"},
    });

    hintTable[GANONS_CASTLE_MQ_SHADOW_TRIAL_EYE_SWITCH_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #test of darkness# holds", /*french*/"l'#épreuve des ténèbres# contient", /*spanish*/"la #prueba de la oscuridad# brinda", /*italian*/"la #prova dell'oscurità# cela", /*german*/"in der #Prüfung der Dunkelheit#, |wäre|wären|"},
    });

    hintTable[GANONS_CASTLE_MQ_SPIRIT_TRIAL_GOLDEN_GAUNTLETS_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#reflected light in the test of the sands# reveals", /*french*/"le #soleil dans l'épreuve des sables# révèle", /*spanish*/"#reflejar la luz en la prueba de las arenas# revela", /*italian*/"#riflettendo nella prova delle sabbie# si |ottiene|ottengono|", /*german*/"nahe #reflektiertem Licht der Prüfung des Sandes#, |wäre|wären|"},
    });

    hintTable[GANONS_CASTLE_MQ_SPIRIT_TRIAL_SUN_BACK_RIGHT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#reflected light in the test of the sands# reveals", /*french*/"le #soleil dans l'épreuve des sables# révèle", /*spanish*/"#reflejar la luz en la prueba de las arenas# revela", /*italian*/"#riflettendo nella prova delle sabbie# si |ottiene|ottengono|", /*german*/"nahe #reflektiertem Licht der Prüfung des Sandes#, |wäre|wären|"},
    });

    hintTable[GANONS_CASTLE_MQ_SPIRIT_TRIAL_SUN_BACK_LEFT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#reflected light in the test of the sands# reveals", /*french*/"le #soleil dans l'épreuve des sables# révèle", /*spanish*/"#reflejar la luz en la prueba de las arenas# revela", /*italian*/"#riflettendo nella prova delle sabbie# si |ottiene|ottengono|", /*german*/"nahe #reflektiertem Licht der Prüfung des Sandes#, |wäre|wären|"},
    });

    hintTable[GANONS_CASTLE_MQ_SPIRIT_TRIAL_SUN_FRONT_LEFT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#reflected light in the test of the sands# reveals", /*french*/"le #soleil dans l'épreuve des sables# révèle", /*spanish*/"#reflejar la luz en la prueba de las arenas# revela", /*italian*/"#riflettendo nella prova delle sabbie# si |ottiene|ottengono|", /*german*/"nahe #reflektiertem Licht der Prüfung des Sandes#, |wäre|wären|"},
    });

    hintTable[GANONS_CASTLE_MQ_SPIRIT_TRIAL_FIRST_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#reflected light in the test of the sands# reveals", /*french*/"le #soleil dans l'épreuve des sables# révèle", /*spanish*/"#reflejar la luz en la prueba de las arenas# revela", /*italian*/"#riflettendo nella prova delle sabbie# si |ottiene|ottengono|", /*german*/"nahe #reflektiertem Licht der Prüfung des Sandes#, |wäre|wären|"},
    });

    hintTable[GANONS_CASTLE_MQ_SPIRIT_TRIAL_INVISIBLE_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#reflected light in the test of the sands# reveals", /*french*/"le #soleil dans l'épreuve des sables# révèle", /*spanish*/"#reflejar la luz en la prueba de las arenas# revela", /*italian*/"#riflettendo nella prova delle sabbie# si |ottiene|ottengono|", /*german*/"nahe #reflektiertem Licht der Prüfung des Sandes#, |wäre|wären|"},
    });

    hintTable[GANONS_CASTLE_MQ_FOREST_TRIAL_FREESTANDING_KEY] = HintText::Exclude({
                       // obscure text
                       Text{"the #test of the wilds# holds", /*french*/"l'#épreuve des bois# révèle", /*spanish*/"la #prueba de la naturaleza# brinda", /*italian*/"la #prova della natura# cela", /*german*/"in der #Prüfung der Wildnis#, |wäre|wären|"},
    });

    hintTable[GANONS_CASTLE_DEKU_SCRUB_CENTER_LEFT] = HintText::Exclude({
                       // obscure text
                       Text{"#scrubs in Ganon's Castle# sell", /*french*/"les #pestes Mojo dans le château de Ganon# vendent", /*spanish*/"los #dekus del Castillo de Ganon# venden", /*italian*/"un #cespuglio nel castello di Ganon# vende", /*german*/"die Ware, eines #Deku-Händlers in Ganons Schloss#, |wäre|wären|"},
    });

    hintTable[GANONS_CASTLE_DEKU_SCRUB_CENTER_RIGHT] = HintText::Exclude({
                       // obscure text
                       Text{"#scrubs in Ganon's Castle# sell", /*french*/"les #pestes Mojo dans le château de Ganon# vendent", /*spanish*/"los #dekus del Castillo de Ganon# venden", /*italian*/"un #cespuglio nel castello di Ganon# vende", /*german*/"die Ware, eines #Deku-Händlers in Ganons Schloss#, |wäre|wären|"},
    });

    hintTable[GANONS_CASTLE_DEKU_SCRUB_RIGHT] = HintText::Exclude({
                       // obscure text
                       Text{"#scrubs in Ganon's Castle# sell", /*french*/"les #pestes Mojo dans le château de Ganon# vendent", /*spanish*/"los #dekus del Castillo de Ganon# venden", /*italian*/"un #cespuglio nel castello di Ganon# vende", /*german*/"die Ware, eines #Deku-Händlers in Ganons Schloss#, |wäre|wären|"},
    });

    hintTable[GANONS_CASTLE_DEKU_SCRUB_LEFT] = HintText::Exclude({
                       // obscure text
                       Text{"#scrubs in Ganon's Castle# sell", /*french*/"les #pestes Mojo dans le château de Ganon# vendent", /*spanish*/"los #dekus del Castillo de Ganon# venden", /*italian*/"un #cespuglio nel castello di Ganon# vende", /*german*/"die Ware, eines #Deku-Händlers in Ganons Schloss#, |wäre|wären|"},
    });


    hintTable[GANONS_CASTLE_MQ_DEKU_SCRUB_RIGHT] = HintText::Exclude({
                       // obscure text
                       Text{"#scrubs in Ganon's Castle# sell", /*french*/"les #pestes Mojo dans le château de Ganon# vendent", /*spanish*/"los #dekus del Castillo de Ganon# venden", /*italian*/"un #cespuglio nel castello di Ganon# vende", /*german*/"die Ware, eines #Deku-Händlers in Ganons Schloss#, |wäre|wären|"},
    });

    hintTable[GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER_LEFT] = HintText::Exclude({
                       // obscure text
                       Text{"#scrubs in Ganon's Castle# sell", /*french*/"les #pestes Mojo dans le château de Ganon# vendent", /*spanish*/"los #dekus del Castillo de Ganon# venden", /*italian*/"un #cespuglio nel castello di Ganon# vende", /*german*/"die Ware, eines #Deku-Händlers in Ganons Schloss#, |wäre|wären|"},
    });

    hintTable[GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER] = HintText::Exclude({
                       // obscure text
                       Text{"#scrubs in Ganon's Castle# sell", /*french*/"les #pestes Mojo dans le château de Ganon# vendent", /*spanish*/"los #dekus del Castillo de Ganon# venden", /*italian*/"un #cespuglio nel castello di Ganon# vende", /*german*/"die Ware, eines #Deku-Händlers in Ganons Schloss#, |wäre|wären|"},
    });

    hintTable[GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER_RIGHT] = HintText::Exclude({
                       // obscure text
                       Text{"#scrubs in Ganon's Castle# sell", /*french*/"les #pestes Mojo dans le château de Ganon# vendent", /*spanish*/"los #dekus del Castillo de Ganon# venden", /*italian*/"un #cespuglio nel castello di Ganon# vende", /*german*/"die Ware, eines #Deku-Händlers in Ganons Schloss#, |wäre|wären|"},
    });

    hintTable[GANONS_CASTLE_MQ_DEKU_SCRUB_LEFT] = HintText::Exclude({
                       // obscure text
                       Text{"#scrubs in Ganon's Castle# sell", /*french*/"les #pestes Mojo dans le château de Ganon# vendent", /*spanish*/"los #dekus del Castillo de Ganon# venden", /*italian*/"un #cespuglio nel castello di Ganon# vende", /*german*/"die Ware, eines #Deku-Händlers in Ganons Schloss#, |wäre|wären|"},
    });
}
// clang-format on
