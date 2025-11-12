#include "hint_list.hpp"
// clang-format off
void HintTable_Init_Exclude_Overworld() {
    hintTable[KF_KOKIRI_SWORD_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #hidden treasure of the Kokiri# is", /*french*/"le #trésor des Kokiri# est", /*spanish*/"el #tesoro oculto de los Kokiri# esconde", /*italian*/"il #tesoro nascosto dei Kokiri# è", /*german*/"der #geheime Schatz der Kokiri#, |wäre|wären|"},
    });

    hintTable[KF_MIDOS_TOP_LEFT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #leader of the Kokiri# hides", /*french*/"le #chef des Kokiri# possède", /*spanish*/"el #líder de los Kokiri# esconde", /*italian*/"il #capo dei Kokiri# nasconde", /*german*/"beim #Anführer der Kokiri#, |wäre|wären|"},
                     }, {},
                       //clear text
                       Text{"#inside Mido's house# is", /*french*/"#dans la maison de Mido# gît", /*spanish*/"en la #casa de Mido# yace", /*italian*/"nella #casa di Mido# puoi trovare", /*german*/"#in Midos Haus#, |wäre|wären|"}
    );

    hintTable[KF_MIDOS_TOP_RIGHT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #leader of the Kokiri# hides", /*french*/"le #chef des Kokiri# possède", /*spanish*/"el #líder de los Kokiri# esconde", /*italian*/"il #capo dei Kokiri# nasconde", /*german*/"beim #Anführer der Kokiri#, |wäre|wären|"},
                     }, {},
                       //clear text
                       Text{"#inside Mido's house# is", /*french*/"#dans la maison de Mido# gît", /*spanish*/"en la #casa de Mido# yace", /*italian*/"nella #casa di Mido# puoi trovare", /*german*/"#in Midos Haus#, |wäre|wären|"}
    );

    hintTable[KF_MIDOS_BOTTOM_LEFT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #leader of the Kokiri# hides", /*french*/"le #chef des Kokiri# possède", /*spanish*/"el #líder de los Kokiri# esconde", /*italian*/"il #capo dei Kokiri# nasconde", /*german*/"beim #Anführer der Kokiri#, |wäre|wären|"},
                     }, {},
                       //clear text
                       Text{"#inside Mido's house# is", /*french*/"#dans la maison de Mido# gît", /*spanish*/"en la #casa de Mido# yace", /*italian*/"nella #casa di Mido# puoi trovare", /*german*/"#in Midos Haus#, |wäre|wären|"}
    );

    hintTable[KF_MIDOS_BOTTOM_RIGHT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #leader of the Kokiri# hides", /*french*/"le #chef des Kokiri# possède", /*spanish*/"el #líder de los Kokiri# esconde", /*italian*/"il #capo dei Kokiri# nasconde", /*german*/"beim #Anführer der Kokiri#, |wäre|wären|"},
                     }, {},
                       //clear text
                       Text{"#inside Mido's house# is", /*french*/"#dans la maison de Mido# gît", /*spanish*/"en la #casa de Mido# yace", /*italian*/"nella #casa di Mido# puoi trovare", /*german*/"#in Midos Haus#, |wäre|wären|"}
    );
    hintTable[KF_END_OF_BRIDGE_BLUE_RUPEE] = HintText::Exclude({
                       // obscure text
                       Text{"EN: KF_END_OF_BRIDGE_BLUE_RUPEE HINT", /*french*/"FR: KF_END_OF_BRIDGE_BLUE_RUPEE HINT", /*spanish*/"ES: KF_END_OF_BRIDGE_BLUE_RUPEE HINT", /*italian*/"IT: KF_END_OF_BRIDGE_BLUE_RUPEE HINT", /*german*/"DE: KF_END_OF_BRIDGE_BLUE_RUPEE HINT"},
    });

    hintTable[KF_BEHIND_MIDOS_HOUSE_BLUE_RUPEE] = HintText::Exclude({
                       // obscure text
                       Text{"EN: KF_BEHIND_MIDOS_HOUSE_BLUE_RUPEE HINT", /*french*/"FR: KF_BEHIND_MIDOS_HOUSE_BLUE_RUPEE HINT", /*spanish*/"ES: KF_BEHIND_MIDOS_HOUSE_BLUE_RUPEE HINT", /*italian*/"IT: KF_BEHIND_MIDOS_HOUSE_BLUE_RUPEE HINT", /*german*/"DE: KF_BEHIND_MIDOS_HOUSE_BLUE_RUPEE HINT"},
    });

    hintTable[KF_BOULDER_MAZE_BLUE_RUPEE_1] = HintText::Exclude({
                       // obscure text
                       Text{"EN: KF_BOULDER_MAZE_BLUE_RUPEE_1 HINT", /*french*/"FR: KF_BOULDER_MAZE_BLUE_RUPEE_1 HINT", /*spanish*/"ES: KF_BOULDER_MAZE_BLUE_RUPEE_1 HINT", /*italian*/"IT: KF_BOULDER_MAZE_BLUE_RUPEE_1 HINT", /*german*/"DE: KF_BOULDER_MAZE_BLUE_RUPEE_1 HINT"},
    });

    hintTable[KF_BOULDER_MAZE_BLUE_RUPEE_2] = HintText::Exclude({
                       // obscure text
                       Text{"EN: KF_BOULDER_MAZE_BLUE_RUPEE_2 HINT", /*french*/"FR: KF_BOULDER_MAZE_BLUE_RUPEE_2 HINT", /*spanish*/"ES: KF_BOULDER_MAZE_BLUE_RUPEE_2 HINT", /*italian*/"IT: KF_BOULDER_MAZE_BLUE_RUPEE_2 HINT", /*german*/"DE: KF_BOULDER_MAZE_BLUE_RUPEE_2 HINT"},
    });
    hintTable[KF_NEAR_RAMP_GREEN_RUPEE_1] = HintText::Exclude({
                       // obscure text
                       Text{"EN: KF_NEAR_RAMP_GREEN_RUPEE_1 HINT", /*french*/"FR: KF_NEAR_RAMP_GREEN_RUPEE_1 HINT", /*spanish*/"ES: KF_NEAR_RAMP_GREEN_RUPEE_1 HINT", /*italian*/"IT: KF_NEAR_RAMP_GREEN_RUPEE_1 HINT", /*german*/"DE: KF_NEAR_RAMP_GREEN_RUPEE_1 HINT"},
    });
        hintTable[KF_NEAR_RAMP_GREEN_RUPEE_2] = HintText::Exclude({
                       // obscure text
                       Text{"EN: KF_NEAR_RAMP_GREEN_RUPEE_2 HINT", /*french*/"FR: KF_NEAR_RAMP_GREEN_RUPEE_2 HINT", /*spanish*/"ES: KF_NEAR_RAMP_GREEN_RUPEE_2 HINT", /*italian*/"IT: KF_NEAR_RAMP_GREEN_RUPEE_2 HINT", /*german*/"DE: KF_NEAR_RAMP_GREEN_RUPEE_2 HINT"},
    });

        hintTable[KF_NEAR_MIDOS_HOUSE_GREEN_RUPEE_1] = HintText::Exclude({
                       // obscure text
                       Text{"EN: KF_NEAR_MIDOS_HOUSE_GREEN_RUPEE_1 HINT", /*french*/"FR: KF_NEAR_MIDOS_HOUSE_GREEN_RUPEE_1 HINT", /*spanish*/"ES: KF_NEAR_MIDOS_HOUSE_GREEN_RUPEE_1 HINT", /*italian*/"IT: KF_NEAR_MIDOS_HOUSE_GREEN_RUPEE_1 HINT", /*german*/"DE: KF_NEAR_MIDOS_HOUSE_GREEN_RUPEE_1 HINT"},
    });
        hintTable[KF_NEAR_MIDOS_HOUSE_GREEN_RUPEE_2] = HintText::Exclude({
                       // obscure text
                       Text{"EN: KF_NEAR_MIDOS_HOUSE_GREEN_RUPEE_2 HINT", /*french*/"FR: KF_NEAR_MIDOS_HOUSE_GREEN_RUPEE_2 HINT", /*spanish*/"ES: KF_NEAR_MIDOS_HOUSE_GREEN_RUPEE_2 HINT", /*italian*/"IT: KF_NEAR_MIDOS_HOUSE_GREEN_RUPEE_2 HINT", /*german*/"DE: KF_NEAR_MIDOS_HOUSE_GREEN_RUPEE_2 HINT"},
    });

    hintTable[KF_RUPEE_CIRCLE_GREEN_RUPEE_1] = HintText::Exclude({
                       // obscure text
                       Text{"EN: KF_RUPEE_CIRCLE_GREEN_RUPEE_1 HINT", /*french*/"FR: KF_RUPEE_CIRCLE_GREEN_RUPEE_1 HINT", /*spanish*/"ES: KF_RUPEE_CIRCLE_GREEN_RUPEE_1 HINT", /*italian*/"IT: KF_RUPEE_CIRCLE_GREEN_RUPEE_1 HINT", /*german*/"DE: KF_RUPEE_CIRCLE_GREEN_RUPEE_1 HINT"},
    });
    hintTable[KF_RUPEE_CIRCLE_GREEN_RUPEE_2] = HintText::Exclude({
                       // obscure text
                       Text{"EN: KF_RUPEE_CIRCLE_GREEN_RUPEE_2 HINT", /*french*/"FR: KF_RUPEE_CIRCLE_GREEN_RUPEE_2 HINT", /*spanish*/"ES: KF_RUPEE_CIRCLE_GREEN_RUPEE_2 HINT", /*italian*/"IT: KF_RUPEE_CIRCLE_GREEN_RUPEE_2 HINT", /*german*/"DE: KF_RUPEE_CIRCLE_GREEN_RUPEE_2 HINT"},
    });
    hintTable[KF_RUPEE_CIRCLE_GREEN_RUPEE_3] = HintText::Exclude({
                       // obscure text
                       Text{"EN: KF_RUPEE_CIRCLE_GREEN_RUPEE_3 HINT", /*french*/"FR: KF_RUPEE_CIRCLE_GREEN_RUPEE_3 HINT", /*spanish*/"ES: KF_RUPEE_CIRCLE_GREEN_RUPEE_3 HINT", /*italian*/"IT: KF_RUPEE_CIRCLE_GREEN_RUPEE_3 HINT", /*german*/"DE: KF_RUPEE_CIRCLE_GREEN_RUPEE_3 HINT"},
    });
    hintTable[KF_RUPEE_CIRCLE_GREEN_RUPEE_4] = HintText::Exclude({
                       // obscure text
                       Text{"EN: KF_RUPEE_CIRCLE_GREEN_RUPEE_4 HINT", /*french*/"FR: KF_RUPEE_CIRCLE_GREEN_RUPEE_4 HINT", /*spanish*/"ES: KF_RUPEE_CIRCLE_GREEN_RUPEE_4 HINT", /*italian*/"IT: KF_RUPEE_CIRCLE_GREEN_RUPEE_4 HINT", /*german*/"DE: KF_RUPEE_CIRCLE_GREEN_RUPEE_4 HINT"},
    });
    hintTable[KF_RUPEE_CIRCLE_GREEN_RUPEE_5] = HintText::Exclude({
                       // obscure text
                       Text{"EN: KF_RUPEE_CIRCLE_GREEN_RUPEE_5 HINT", /*french*/"FR: KF_RUPEE_CIRCLE_GREEN_RUPEE_5 HINT", /*spanish*/"ES: KF_RUPEE_CIRCLE_GREEN_RUPEE_5 HINT", /*italian*/"IT: KF_RUPEE_CIRCLE_GREEN_RUPEE_5 HINT", /*german*/"DE: KF_RUPEE_CIRCLE_GREEN_RUPEE_5 HINT"},
    });
    hintTable[KF_RUPEE_CIRCLE_GREEN_RUPEE_6] = HintText::Exclude({
                       // obscure text
                       Text{"EN: KF_RUPEE_CIRCLE_GREEN_RUPEE_6 HINT", /*french*/"FR: KF_RUPEE_CIRCLE_GREEN_RUPEE_6 HINT", /*spanish*/"ES: KF_RUPEE_CIRCLE_GREEN_RUPEE_6 HINT", /*italian*/"IT: KF_RUPEE_CIRCLE_GREEN_RUPEE_6 HINT", /*german*/"DE: KF_RUPEE_CIRCLE_GREEN_RUPEE_6 HINT"},
    });
    hintTable[KF_RUPEE_CIRCLE_RED_RUPEE] = HintText::Exclude({
                       // obscure text
                       Text{"EN: KF_RUPEE_CIRCLE_RED_RUPEE HINT", /*french*/"FR: KF_RUPEE_CIRCLE_RED_RUPEE HINT", /*spanish*/"ES: KF_RUPEE_CIRCLE_RED_RUPEE HINT", /*italian*/"IT: KF_RUPEE_CIRCLE_RED_RUPEE HINT", /*german*/"DE: KF_RUPEE_CIRCLE_RED_RUPEE HINT"},
    });

    hintTable[GRAVEYARD_SHIELD_GRAVE_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"the #treasure of a fallen soldier# is", /*french*/"le #trésor du soldat mort# est", /*spanish*/"el #tesoro de un soldado caído# esconde", /*italian*/"il #tesoro di un soldato caduto# è", /*german*/"der #Schatz eines gefallenen Soldaten#, |wäre|wären|"},
    });

    hintTable[DMT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"hidden behind a wall on a #mountain trail# is", /*french*/"derrière une façade du #chemin montagneux# est", /*spanish*/"tras una pared del #sendero de la montaña# yace", /*italian*/"dietro una parete su un #sentiero di montagna# puoi trovare", /*german*/"hinter einer Wand eines #Gebirgspfades#, |wäre|wären|"},
    });

    hintTable[GC_MAZE_RIGHT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"in #Goron City# explosives unlock", /*french*/"des explosions dans le #village Goron# révèlent", /*spanish*/"en la #Ciudad Goron# unos explosivos desbloquean", /*italian*/"nella #città dei Goron# gli esplosivi sbloccano", /*german*/"hinter Felsen #Goronias#, |wäre|wären|"},
    });

    hintTable[GC_MAZE_CENTER_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"in #Goron City# explosives unlock", /*french*/"des explosions dans le #village Goron# révèlent", /*spanish*/"en la #Ciudad Goron# unos explosivos desbloquean", /*italian*/"nella #città dei Goron# gli esplosivi sbloccano", /*german*/"hinter Felsen #Goronias#, |wäre|wären|"},
    });

    hintTable[ZD_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"fire #beyond a waterfall# reveals", /*french*/"du feu #derrière la cascade# éclaire", /*spanish*/"las #llamas tras una una cascada# revelan", /*italian*/"#fuoco oltre una cascata# rivela", /*german*/"hinter einem #Wasserfall#, |wäre|wären|"},
    });

    hintTable[GRAVEYARD_HOOKSHOT_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a chest hidden by a #speedy spectre# holds", /*french*/"le #coffre du rapide revenant# contient", /*spanish*/"un cofre custodiado por un #espectro veloz# contiene", /*italian*/"un forziere nascosto da uno #svelto spettro# contiene", /*german*/"bei einem #flinken Gespenst#, |wäre|wären|"},
                     }, {},
                       //clear text
                       Text{"#dead Dampé's first prize# is", /*french*/"la #première course d'Igor# donne", /*spanish*/"el primer premio de #la carrera de Dampé# se trata de", /*italian*/"la prima ricompensa del #fantasma di Danpei# è", /*german*/"#Boris' erster Preis#, |wäre|wären|"}
    );

    hintTable[GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_2] = HintText::Exclude({
                       // obscure text
                       Text{"EN: GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_2 Hint", /*french*/"FR: GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_2 Hint", /*spanish*/"ES: GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_2 Hint", /*italian*/"IT: GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_2 Hint", /*german*/"DE: GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_2 Hint"},
                     }
    );

    hintTable[GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_3] = HintText::Exclude({
                       // obscure text
                       Text{"EN: GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_3 Hint", /*french*/"FR: GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_3 Hint", /*spanish*/"ES: GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_3 Hint", /*italian*/"IT: GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_3 Hint", /*german*/"DE: GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_3 Hint"},
                     }
    );

    hintTable[GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_4] = HintText::Exclude({
                       // obscure text
                       Text{"EN: GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_4 Hint", /*french*/"FR: GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_4 Hint", /*spanish*/"ES: GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_4 Hint", /*italian*/"IT: GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_4 Hint", /*german*/"DE: GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_4 Hint"},
                     }
    );

    hintTable[GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_5] = HintText::Exclude({
                       // obscure text
                       Text{"EN: GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_5 Hint", /*french*/"FR: GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_5 Hint", /*spanish*/"ES: GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_5 Hint", /*italian*/"IT: GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_5 Hint", /*german*/"DE: GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_5 Hint"},
                     }
    );

    hintTable[GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_6] = HintText::Exclude({
                       // obscure text
                       Text{"EN: GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_6 Hint", /*french*/"FR: GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_6 Hint", /*spanish*/"ES: GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_6 Hint", /*italian*/"IT: GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_6 Hint", /*german*/"DE: GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_6 Hint"},
                     }
    );

    hintTable[GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_7] = HintText::Exclude({
                       // obscure text
                       Text{"EN: GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_7 Hint", /*french*/"FR: GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_7 Hint", /*spanish*/"ES: GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_7 Hint", /*italian*/"IT: GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_7 Hint", /*german*/"DE: GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_7 Hint"},
                     }
    );

    hintTable[GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_8] = HintText::Exclude({
                       // obscure text
                       Text{"EN: GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_8 Hint", /*french*/"FR: GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_8 Hint", /*spanish*/"ES: GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_8 Hint", /*italian*/"IT: GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_8 Hint", /*german*/"DE: GRAVEYARD_DAMPE_RACE_GREEN_RUPEE_8 Hint"},
                     }
    );

    hintTable[GF_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"on a #rooftop in the desert# lies", /*french*/"sur un #toit du désert# gît", /*spanish*/"en una #azotea del desierto# yace", /*italian*/"sopra un #tetto in un deserto# puoi trovare", /*german*/"auf einem #Dach der Wüste#, |wäre|wären|"},
    });

    hintTable[KAK_REDEAD_GROTTO_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#zombies beneath the earth# guard", /*french*/"les #revenants sous terre# protègent", /*spanish*/"unos #zombis subterráneos# esconden", /*italian*/"dei #ri-morti sottoterra# proteggono", /*german*/"in einem #Erdloch mit zwei Zombies#, |wäre|wären|"},
    });

    hintTable[SFM_WOLFOS_GROTTO_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"#wolves beneath the earth# guard", /*french*/"les #loups sous terre# protègent", /*spanish*/"unos #lobos subterráneos# esconden", /*italian*/"dei #lupi sottoterra# proteggono", /*german*/"in einem #Erdloch mit zwei Wolfos#"},
    });

    hintTable[HF_NEAR_MARKET_GROTTO_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #hole in a field near a drawbridge# holds", /*french*/"la #grotte près d'un pont# contient", /*spanish*/"bajo el #hoyo de una llanura cercano a un puente# yace", /*italian*/"#vicino al ponte levatoio# qualcuno ha sepolto", /*german*/"in einem #Erdloch nahe einer Zugbrücke#, |wäre|wären|"},
    });

    hintTable[HF_SOUTHEAST_GROTTO_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #hole amongst trees in a field# holds", /*french*/"la #grotte près des arbres# contient", /*spanish*/"bajo el #hoyo de una llanura rodeado de árboles# yace", /*italian*/"#in mezzo a degli alberi# in una pianura qualcuno ha sepolto", /*german*/"in einem, #von Bäumen umgebenen Erdloch einer Ebene#, |wäre|wären|"},
    });

    hintTable[HF_OPEN_GROTTO_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"an #open hole in a field# holds", /*french*/"la #grotte dans les plaines# contient", /*spanish*/"bajo el #hoyo descubierto de una llanura# yace", /*italian*/"una #buca aperta nella pianura# contiene", /*german*/"in einem #offenstehenden Erdloch einer Ebene#, |wäre|wären|"},
    });

    hintTable[KAK_OPEN_GROTTO_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"an #open hole in a town# holds", /*french*/"la #grotte dans le village# contient", /*spanish*/"bajo el #hoyo descubierto de un pueblo# yace", /*italian*/"una #buca aperta in un villaggio# contiene", /*german*/"in einem #offenstehenden Erdloch eines Dorfes#, |wäre|wären|"},
    });

    hintTable[ZR_OPEN_GROTTO_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #hole along a river# holds", /*french*/"la #grotte près du fleuve# contient", /*spanish*/"bajo un #hoyo junto a un río# yace", /*italian*/"una #buca aperta in riva al fiume# contiene", /*german*/"in einem #Erdloch nahe eines Flusses#, |wäre|wären|"},
    });

    hintTable[KF_STORMS_GROTTO_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #hole in a forest village# holds", /*french*/"la #grotte inondée de pluie dans le Village Kokiri# révèle", /*spanish*/"bajo el #hoyo de una tribu del bosque# yace", /*italian*/"nella #foresta dei Kokiri# qualcuno ha sepolto", /*german*/"in einem #Erdloch eines Walddorfes#, |wäre|wären|"},
    });

    hintTable[LW_NEAR_SHORTCUTS_GROTTO_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #hole in a wooded maze# holds", /*french*/"la #grotte dans le labyrinthe sylvestre# contient", /*spanish*/"bajo un #hoyo de un laberinto forestal# yace", /*italian*/"#in un dedalo silvestre# qualcuno ha sepolto", /*german*/"in einem #Erdloch eines hölzernen Irrgartens#, |wäre|wären|"},
    });

    hintTable[DMT_STORMS_GROTTO_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #hole flooded with rain on a mountain# holds", /*french*/"la #grotte inondée de pluie sur la montagne# contient", /*spanish*/"bajo un #hoyo de una montaña inundado de lluvia# yace", /*italian*/"#all'ingresso di una città rocciosa# qualcuno ha sepolto", /*german*/"in einem #stürmischen Erdloch eines Berges#, |wäre|wären|"},
    });

    hintTable[DMC_UPPER_GROTTO_CHEST] = HintText::Exclude({
                       // obscure text
                       Text{"a #hole in a volcano# holds", /*french*/"la #grotte dans le volcan# contient", /*spanish*/"bajo el #hoyo de un volcán# yace", /*italian*/"#in un vulcano# qualcuno ha sepolto", /*german*/"in einem #Erdloch eines Vulkans#, |wäre|wären|"},
    });

    hintTable[TOT_MASTER_SWORD] = HintText::Exclude({
                       // obscure text
                       Text{"a #pedestal in a temple# holds", /*french*/"un #piédestal dans un temple# contient", /*spanish*/"un #pedestal en un templo# sostiene", /*italian*/"su #un piedistallo in un santuario# puoi ammirare", /*german*/"auf einem #Podest eines Tempels#, |wäre|wären|"},
    });

    hintTable[TOT_LIGHT_ARROWS_CUTSCENE] = HintText::Exclude({
                       // obscure text
                       Text{"the #final gift of a princess# is", /*french*/"le #cadeau d'adieu de la princesse# est", /*spanish*/"el #obsequio final de la princesa# se trata de", /*italian*/"l'#ultimo dono della principessa# è", /*german*/"das #finale Geschenk einer Prinzessin#, |wäre|wären|"},
    });

    hintTable[LW_GIFT_FROM_SARIA] = HintText::Exclude({
                       // obscure text
                       Text{"a #potato hoarder# holds",           /*french*/"le #panini mélodieux# est en fait", /*spanish*/"cierta #jovencita verde# concede", /*italian*/"#chi esce dalla foresta proibita# riceve", /*german*/"das Geschenk einer #Kindheitsfreundin#, |wäre|wären|"},
                       Text{"a rooty tooty #flutey cutey# gifts", /*french*/"la #patate musicale# est en fait",  /*spanish*/"una #gran amiga# concede",         /*italian*/"una #piccola pifferaia# dona",             /*german*/"ein #Abschiedsgeschenk auf einer Brücke#, |wäre|wären|"},
                     }, {},
                       //clear text
                       Text{"#Saria's Gift# is", /*french*/"le #cadeau de Saria# est", /*spanish*/"el #regalo de Saria# se trata de", /*italian*/"il #regalo di Saria# è", /*german*/"#Salias Geschenk#, |wäre|wären|"}
    );

    hintTable[ZF_GREAT_FAIRY_REWARD] = HintText::Exclude({
                       // obscure text
                       Text{"the #fairy of winds# holds", /*french*/"la #fée du vent# a", /*spanish*/"el #hada del viento# brinda", /*italian*/"la #fata del vento# consegna", /*german*/"in der #Feen-Quelle des Sturmes#, |wäre|wären|"},
    });

                hintTable[ZF_UNDERWATER_GREEN_RUPEE_1] = HintText::Exclude({
                       // obscure text
                       Text{"EN: ZF_UNDERWATER_GREEN_RUPEE_1 HINT", /*french*/"FR: ZF_UNDERWATER_GREEN_RUPEE_1 HINT", /*spanish*/"ES: ZF_UNDERWATER_GREEN_RUPEE_1 HINT", /*italian*/"IT: ZF_UNDERWATER_GREEN_RUPEE_1 HINT", /*german*/"DE: ZF_UNDERWATER_GREEN_RUPEE_1 HINT"},
    });
                    hintTable[ZF_UNDERWATER_GREEN_RUPEE_2] = HintText::Exclude({
                       // obscure text
                       Text{"EN: ZF_UNDERWATER_GREEN_RUPEE_2 HINT", /*french*/"FR: ZF_UNDERWATER_GREEN_RUPEE_2 HINT", /*spanish*/"ES: ZF_UNDERWATER_GREEN_RUPEE_2 HINT", /*italian*/"IT: ZF_UNDERWATER_GREEN_RUPEE_2 HINT", /*german*/"DE: ZF_UNDERWATER_GREEN_RUPEE_2 HINT"},
    });

                    hintTable[ZF_UNDERWATER_GREEN_RUPEE_3] = HintText::Exclude({
                       // obscure text
                       Text{"EN: ZF_UNDERWATER_GREEN_RUPEE_3 HINT", /*french*/"FR: ZF_UNDERWATER_GREEN_RUPEE_3 HINT", /*spanish*/"ES: ZF_UNDERWATER_GREEN_RUPEE_3 HINT", /*italian*/"IT: ZF_UNDERWATER_GREEN_RUPEE_3 HINT", /*german*/"DE: ZF_UNDERWATER_GREEN_RUPEE_3 HINT"},
    });

                    hintTable[ZF_UNDERWATER_GREEN_RUPEE_4] = HintText::Exclude({
                       // obscure text
                       Text{"EN: ZF_UNDERWATER_GREEN_RUPEE_4 HINT", /*french*/"FR: ZF_UNDERWATER_GREEN_RUPEE_4 HINT", /*spanish*/"ES: ZF_UNDERWATER_GREEN_RUPEE_4 HINT", /*italian*/"IT: ZF_UNDERWATER_GREEN_RUPEE_4 HINT", /*german*/"DE: ZF_UNDERWATER_GREEN_RUPEE_4 HINT"},
    });

                    hintTable[ZF_UNDERWATER_GREEN_RUPEE_5] = HintText::Exclude({
                       // obscure text
                       Text{"EN: ZF_UNDERWATER_GREEN_RUPEE_5 HINT", /*french*/"FR: ZF_UNDERWATER_GREEN_RUPEE_5 HINT", /*spanish*/"ES: ZF_UNDERWATER_GREEN_RUPEE_5 HINT", /*italian*/"IT: ZF_UNDERWATER_GREEN_RUPEE_5 HINT", /*german*/"DE: ZF_UNDERWATER_GREEN_RUPEE_5 HINT"},
    });

                    hintTable[ZF_UNDERWATER_GREEN_RUPEE_6] = HintText::Exclude({
                       // obscure text
                       Text{"EN: ZF_UNDERWATER_GREEN_RUPEE_6 HINT", /*french*/"FR: ZF_UNDERWATER_GREEN_RUPEE_6 HINT", /*spanish*/"ES: ZF_UNDERWATER_GREEN_RUPEE_6 HINT", /*italian*/"IT: ZF_UNDERWATER_GREEN_RUPEE_6 HINT", /*german*/"DE: ZF_UNDERWATER_GREEN_RUPEE_6 HINT"},
    });

                    hintTable[ZF_UNDERWATER_GREEN_RUPEE_7] = HintText::Exclude({
                       // obscure text
                       Text{"EN: ZF_UNDERWATER_GREEN_RUPEE_7 HINT", /*french*/"FR: ZF_UNDERWATER_GREEN_RUPEE_7 HINT", /*spanish*/"ES: ZF_UNDERWATER_GREEN_RUPEE_7 HINT", /*italian*/"IT: ZF_UNDERWATER_GREEN_RUPEE_7 HINT", /*german*/"DE: ZF_UNDERWATER_GREEN_RUPEE_7 HINT"},
    });

                    hintTable[ZF_UNDERWATER_GREEN_RUPEE_8] = HintText::Exclude({
                       // obscure text
                       Text{"EN: ZF_UNDERWATER_GREEN_RUPEE_8 HINT", /*french*/"FR: ZF_UNDERWATER_GREEN_RUPEE_8 HINT", /*spanish*/"ES: ZF_UNDERWATER_GREEN_RUPEE_8 HINT", /*italian*/"IT: ZF_UNDERWATER_GREEN_RUPEE_8 HINT", /*german*/"DE: ZF_UNDERWATER_GREEN_RUPEE_8 HINT"},
    });

                    hintTable[ZF_UNDERWATER_GREEN_RUPEE_9] = HintText::Exclude({
                       // obscure text
                       Text{"EN: ZF_UNDERWATER_GREEN_RUPEE_9 HINT", /*french*/"FR: ZF_UNDERWATER_GREEN_RUPEE_9 HINT", /*spanish*/"ES: ZF_UNDERWATER_GREEN_RUPEE_9 HINT", /*italian*/"IT: ZF_UNDERWATER_GREEN_RUPEE_9 HINT", /*german*/"DE: ZF_UNDERWATER_GREEN_RUPEE_9 HINT"},
    });

                    hintTable[ZF_UNDERWATER_GREEN_RUPEE_10] = HintText::Exclude({
                       // obscure text
                       Text{"EN: ZF_UNDERWATER_GREEN_RUPEE_10 HINT", /*french*/"FR: ZF_UNDERWATER_GREEN_RUPEE_10 HINT", /*spanish*/"ES: ZF_UNDERWATER_GREEN_RUPEE_10 HINT", /*italian*/"IT: ZF_UNDERWATER_GREEN_RUPEE_10 HINT", /*german*/"DE: ZF_UNDERWATER_GREEN_RUPEE_10 HINT"},
    });

                    hintTable[ZF_UNDERWATER_GREEN_RUPEE_11] = HintText::Exclude({
                       // obscure text
                       Text{"EN: ZF_UNDERWATER_GREEN_RUPEE_11 HINT", /*french*/"FR: ZF_UNDERWATER_GREEN_RUPEE_11 HINT", /*spanish*/"ES: ZF_UNDERWATER_GREEN_RUPEE_11 HINT", /*italian*/"IT: ZF_UNDERWATER_GREEN_RUPEE_11 HINT", /*german*/"DE: ZF_UNDERWATER_GREEN_RUPEE_11 HINT"},
    });

                    hintTable[ZF_UNDERWATER_GREEN_RUPEE_12] = HintText::Exclude({
                       // obscure text
                       Text{"EN: ZF_UNDERWATER_GREEN_RUPEE_12 HINT", /*french*/"FR: ZF_UNDERWATER_GREEN_RUPEE_12 HINT", /*spanish*/"ES: ZF_UNDERWATER_GREEN_RUPEE_12 HINT", /*italian*/"IT: ZF_UNDERWATER_GREEN_RUPEE_12 HINT", /*german*/"DE: ZF_UNDERWATER_GREEN_RUPEE_12 HINT"},
    });

                    hintTable[ZF_UNDERWATER_GREEN_RUPEE_13] = HintText::Exclude({
                       // obscure text
                       Text{"EN: ZF_UNDERWATER_GREEN_RUPEE_13 HINT", /*french*/"FR: ZF_UNDERWATER_GREEN_RUPEE_13 HINT", /*spanish*/"ES: ZF_UNDERWATER_GREEN_RUPEE_13 HINT", /*italian*/"IT: ZF_UNDERWATER_GREEN_RUPEE_13 HINT", /*german*/"DE: ZF_UNDERWATER_GREEN_RUPEE_13 HINT"},
    });

                    hintTable[ZF_UNDERWATER_GREEN_RUPEE_14] = HintText::Exclude({
                       // obscure text
                       Text{"EN: ZF_UNDERWATER_GREEN_RUPEE_14 HINT", /*french*/"FR: ZF_UNDERWATER_GREEN_RUPEE_14 HINT", /*spanish*/"ES: ZF_UNDERWATER_GREEN_RUPEE_14 HINT", /*italian*/"IT: ZF_UNDERWATER_GREEN_RUPEE_14 HINT", /*german*/"DE: ZF_UNDERWATER_GREEN_RUPEE_14 HINT"},
    });

                    hintTable[ZF_UNDERWATER_GREEN_RUPEE_15] = HintText::Exclude({
                       // obscure text
                       Text{"EN: ZF_UNDERWATER_GREEN_RUPEE_15 HINT", /*french*/"FR: ZF_UNDERWATER_GREEN_RUPEE_15 HINT", /*spanish*/"ES: ZF_UNDERWATER_GREEN_RUPEE_15 HINT", /*italian*/"IT: ZF_UNDERWATER_GREEN_RUPEE_15 HINT", /*german*/"DE: ZF_UNDERWATER_GREEN_RUPEE_15 HINT"},
    });

                    hintTable[ZF_UNDERWATER_GREEN_RUPEE_16] = HintText::Exclude({
                       // obscure text
                       Text{"EN: ZF_UNDERWATER_GREEN_RUPEE_16 HINT", /*french*/"FR: ZF_UNDERWATER_GREEN_RUPEE_16 HINT", /*spanish*/"ES: ZF_UNDERWATER_GREEN_RUPEE_16 HINT", /*italian*/"IT: ZF_UNDERWATER_GREEN_RUPEE_16 HINT", /*german*/"DE: ZF_UNDERWATER_GREEN_RUPEE_16 HINT"},
    });

                    hintTable[ZF_UNDERWATER_GREEN_RUPEE_17] = HintText::Exclude({
                       // obscure text
                       Text{"EN: ZF_UNDERWATER_GREEN_RUPEE_17 HINT", /*french*/"FR: ZF_UNDERWATER_GREEN_RUPEE_17 HINT", /*spanish*/"ES: ZF_UNDERWATER_GREEN_RUPEE_17 HINT", /*italian*/"IT: ZF_UNDERWATER_GREEN_RUPEE_17 HINT", /*german*/"DE: ZF_UNDERWATER_GREEN_RUPEE_17 HINT"},
    });

                    hintTable[ZF_UNDERWATER_GREEN_RUPEE_18] = HintText::Exclude({
                       // obscure text
                       Text{"EN: ZF_UNDERWATER_GREEN_RUPEE_18 HINT", /*french*/"FR: ZF_UNDERWATER_GREEN_RUPEE_18 HINT", /*spanish*/"ES: ZF_UNDERWATER_GREEN_RUPEE_18 HINT", /*italian*/"IT: ZF_UNDERWATER_GREEN_RUPEE_18 HINT", /*german*/"DE: ZF_UNDERWATER_GREEN_RUPEE_18 HINT"},
    });



    hintTable[HC_GREAT_FAIRY_REWARD] = HintText::Exclude({
                       // obscure text
                       Text{"the #fairy of fire# holds", /*french*/"la #fée du feu# a", /*spanish*/"el #hada del fuego# brinda", /*italian*/"la #fata del fuoco# consegna", /*german*/"in der #Feen-Quelle des Feuers#, |wäre|wären|"},
    });

    hintTable[COLOSSUS_GREAT_FAIRY_REWARD] = HintText::Exclude({
                       // obscure text
                       Text{"the #fairy of love# holds", /*french*/"la #fée de l'amour# a", /*spanish*/"el #hada del amor# brinda", /*italian*/"la #fata dell'amore# consegna", /*german*/"in der #Feen-Quelle der Liebe#, |wäre|wären|"},
    });

    hintTable[DMT_GREAT_FAIRY_REWARD] = HintText::Exclude({
                       // obscure text
                       Text{"the #Great Fairy of Power# gifts", /*french*/"la #grande fée de la force# a", /*spanish*/"la #Gran Hada del Poder# brinda", /*italian*/"la #Fata radiosa della Forza# consegna", /*german*/"in der #Feen-Quelle der Fähigkeiten#, |wäre|wären|"},
    });

    hintTable[DMC_GREAT_FAIRY_REWARD] = HintText::Exclude({
                       // obscure text
                       Text{"the #Great Fairy of Wisdom# gifts", /*french*/"la #grande fée de la sagesse# a", /*spanish*/"la #Gran Hada de la Sabiduría# brinda", /*italian*/"la #Fata radiosa della Saggezza# consegna", /*german*/"in der #Feen-Quelle der Weisheit#, |wäre|wären|"},
    });

    hintTable[OGC_GREAT_FAIRY_REWARD] = HintText::Exclude({
                       // obscure text
                       Text{"the #Great Fairy of Courage# holds", /*french*/"la #grande fée du courage# a", /*spanish*/"la #Gran Hada del Valor# brinda", /*italian*/"la #Fata radiosa del Coraggio# consegna", /*german*/"in der #Feen-Quelle des Mutes#, |wäre|wären|"},
    });


    hintTable[SONG_FROM_IMPA] = HintText::Exclude({
                       // obscure text
                       Text{"#deep in a castle#, Impa teaches", /*french*/"#la gardienne de la princesse# donne", /*spanish*/"en el #jardín del castillo Impa enseña#", /*italian*/"#tra le mura del castello#, Impa insegna", /*german*/"ein, #in einem Schloss# von Impa gelehrtes Lied, |wäre|wären|"},
    });

    hintTable[SONG_FROM_MALON] = HintText::Exclude({
                       // obscure text
                       Text{"#a farm girl# sings", /*french*/"la #fillette de la ferme# donne", /*spanish*/"una #chica rupestre# canta", /*italian*/"una #ragazza di campagna# canta", /*german*/"ein, von einem #Bauernmädchen gesungenes Lied#, |wäre|wären|"},
    });

    hintTable[SONG_FROM_SARIA] = HintText::Exclude({
                       // obscure text
                       Text{"#deep in the forest#, Saria teaches", /*french*/"la #fille de la forêt# donne", /*spanish*/"al #fondo del bosque# Saria enseña", /*italian*/"#in fondo al bosco#, Saria insegna", /*german*/"ein, #im tiefen Wald# von Salia gelehrtes Lied, |wäre|wären|"},
    });

    hintTable[SONG_FROM_WINDMILL] = HintText::Exclude({
                       // obscure text
                       Text{"a man #in a windmill# is obsessed with", /*french*/"l'#homme du moulin# donne", /*spanish*/"el #hombre del molino# está obsesionado con", /*italian*/"#l'uomo del mulino# ha un'ossessione per", /*german*/"ein, #in einer Windmühle# gelehres Lied, |wäre|wären|"},
    });


    hintTable[HC_MALON_EGG] = HintText::Exclude({
                       // obscure text
                       Text{"a #girl looking for her father# gives", /*french*/"la #fillette qui cherche son père# donne", /*spanish*/"una #chica en busca de su padre# otorga", /*italian*/"una #ragazza in cerca di suo padre# dona", /*german*/"der Gegenstand eines #besorgten Mädchens#, |wäre|wären|"},
    });

    hintTable[HC_ZELDAS_LETTER] = HintText::Exclude({
                       // obscure text
                       Text{"a #princess in a castle# gifts", /*french*/"la #princesse dans le château# donne", /*spanish*/"la #princesa de un castillo# otorga", /*italian*/"la #principessa nel castello# consegna", /*german*/"#Zeldas hoheitlicher Auftrag#, |wäre|wären|"},
    });

    hintTable[ZD_DIVING_MINIGAME] = HintText::Exclude({
                       // obscure text
                       Text{"an #unsustainable business model# gifts", /*french*/"le #mauvais modèle d'affaires# donne", /*spanish*/"un #mal modelo de negocio# premia con", /*italian*/"una #pessima strategia commerciale# elargisce", /*german*/"beim #nicht aufrechtzuerhaltenen Geschäftsmodell#, |wäre|wären|"},
                     }, {},
                       //clear text
                       Text{"those who #dive for Zora rupees# will find", /*french*/"ceux qui #plongent pour des rubis Zora# trouveront", /*spanish*/"aquellos que se #sumergan por las rupias zora# encontrarán", /*italian*/"chi #si immerge per recuperare rupie fra gli Zora# riceve", /*german*/"beim #Tauchspiel#, |wäre|wären|"}
    );

    hintTable[LH_CHILD_FISHING] = HintText::Exclude({
                       // obscure text
                       Text{"#fishing in youth# bestows", /*french*/"#pêcher dans sa jeunesse# promet", /*spanish*/"#pescar en la juventud# conduce a", /*italian*/"#pescare in gioventù# procura", /*german*/"der #Fang der Jugend#, |wäre|wären|"},
    });

    hintTable[LH_ADULT_FISHING] = HintText::Exclude({
                       // obscure text
                       Text{"#fishing in maturity# bestows", /*french*/"#pêcher dans sa maturité# promet", /*spanish*/"#pescar en la madurez# conduce a", /*italian*/"#pescare dopo la maturità# procura", /*german*/"der #Fang des Alters#, |wäre|wären|"},
    });

    hintTable[LH_LAB_DIVE] = HintText::Exclude({
                       // obscure text
                       Text{"a #diving experiment# is rewarded with", /*french*/"l'#expérience de plongée# donne", /*spanish*/"#bucear para un experimento# se premia con", /*italian*/"una #prova di immersione# è ricompensata con", /*german*/"beim #Tauchexperiment#, |wäre|wären|"},
    });

    hintTable[GC_ROLLING_GORON_AS_ADULT] = HintText::Exclude({
                       // obscure text
                       Text{"#comforting yourself# provides", /*french*/"se #réconforter soi-même# donne", /*spanish*/"#confrontarte a ti mismo# otorga", /*italian*/"#confortare se stessi# procura", /*german*/"bei einer #goronischen Geschichtsstunde#, |wäre|wären|"},
                     }, {},
                       //clear text
                       Text{"#reassuring a young Goron# is rewarded with", /*french*/"#rassurer un jeune Goron# donne", /*spanish*/"#calmar a un joven Goron# otorga", /*italian*/"#calmare un giovane Goron# procura", /*german*/"der Dank fürs #Beruhigen eines jungen Goronen#, |wäre|wären|"}
    );

    hintTable[MARKET_BOMBCHU_BOWLING_FIRST_PRIZE] = HintText::Exclude({
                       // obscure text
                       Text{"the #first explosive prize# is", /*french*/"le #premier prix explosif# est", /*spanish*/"el #primer premio explosivo# se trata de", /*italian*/"il #primo premio esplosivo# è", /*german*/"der #erste explosive Preis#, |wäre|wären|"},
    });

    hintTable[MARKET_BOMBCHU_BOWLING_SECOND_PRIZE] = HintText::Exclude({
                       // obscure text
                       Text{"the #second explosive prize# is", /*french*/"le #deuxième prix explosif# est", /*spanish*/"el #segundo premio explosivo# se trata de", /*italian*/"il #secondo premio esplosivo# è", /*german*/"der #zweite explosive Preis#, |wäre|wären|"},
    });

    hintTable[MARKET_LOST_DOG] = HintText::Exclude({
                       // obscure text
                       Text{"#puppy lovers# will find", /*french*/"les #amoureux canins# trouveront", /*spanish*/"los #amantes caninos# encontrarán", /*italian*/"i #cinofili# riceveranno", /*german*/"bei einer #Hundeliebhaberin#, |wäre|wären|"},
                     }, {},
                       //clear text
                       Text{"#rescuing Richard the Dog# is rewarded with", /*french*/"#retrouver Kiki le chien# promet", /*spanish*/"#rescatar al perrito Ricardo# conduce a", /*italian*/"#salvare Richard il cane# viene ricompensato con", /*german*/"der Finderlohn des #Hundes Richard#, |wäre|wären|"}
    );

    hintTable[LW_OCARINA_MEMORY_GAME] = HintText::Exclude({
                       // obscure text
                       Text{"the prize for a #game of Simon Says# is", /*french*/"la #récompense de Jean Dit# est", /*spanish*/"#repetir ciertas melodías# otorga", /*italian*/"serve #buona memoria# per vincere", /*german*/"der Preis für eine Runde #Simon Says#, |wäre|wären|"},
                       Text{"a #child sing-a-long# holds",             /*french*/"les #jeunes flûtistes# donnent",  /*spanish*/"#tocar junto a otros# otorga",      /*italian*/"#imitare melodie# procura",         /*german*/"bei einer #kindlichen Musikprobe#, |wäre|wären|"},
                     }, {},
                       //clear text
                       Text{"#playing an Ocarina in Lost Woods# is rewarded with", /*french*/"#jouer l'ocarina dans la forêt des méandres# donne", /*spanish*/"#tocar la ocarina en el Bosque Perdido# otorga", /*italian*/"#suonare l'ocarina nel bosco perduto# procura", /*german*/"die Belohnung, fürs #Spielen der Okarina in den verlorenen Wäldern#, |wäre|wären|"}
    );

    hintTable[KAK_10_GOLD_SKULLTULA_REWARD] = HintText::Exclude({
                       // obscure text
                       Text{"#10 bug badges# rewards",           /*french*/"#10 écussons# donnent",             /*spanish*/"#10 medallas de insectos# otorgan", /*italian*/"#10 spille d'insetto# sono premiate con", /*german*/"die Entschädigung für #10 Insekten-Abzeichen#, |wäre|wären|"},
                       Text{"#10 spider souls# yields",          /*french*/"#10 âmes# donnent",                 /*spanish*/"#10 almas de araña# otorgan",       /*italian*/"#10 anime di ragno# forniscono",          /*german*/"der Lohn für #10 Spinnenseelen#, |wäre|wären|"},
                       Text{"#10 auriferous arachnids# lead to", /*french*/"#10 arachnides aurifères# donnent", /*spanish*/"#10 arácnidos auríferos# otorgan",  /*italian*/"#10 artropodi aurei# forniscono",         /*german*/"die Bezahlung für #10 goldhaltige Arachniden#, |wäre|wären|"},
                     }, {},
                       //clear text
                       Text{"slaying #10 Gold Skulltulas# reveals", /*french*/"détruire #10 Skulltulas d'or# donne", /*spanish*/"#exterminar 10 skulltulas doradas# revela", /*italian*/"eliminare #10 Aracnule d'oro# rivela", /*german*/"die Belohnung, fürs Zerstören von #10 goldenen Skulltulas#, |wäre|wären|"}
    );

    hintTable[KAK_MAN_ON_ROOF] = HintText::Exclude({
                       // obscure text
                       Text{"a #rooftop wanderer# holds", /*french*/"une #rencontre sur un toit# donne", /*spanish*/"#alguien sobre un tejado# otorga", /*italian*/"#un tizio su un tetto# possiede", /*german*/"bei einem #Dachgespräch#, |wäre|wären|"},
    });

    hintTable[ZR_MAGIC_BEAN_SALESMAN] = HintText::Exclude({
                       // obscure text
                       Text{"a seller of #colorful crops# has", /*french*/"le #marchand de légumes# vend", /*spanish*/"el vendedor de un #colorido cultivo# ofrece", /*italian*/"un #mercante di ortaggi colorati# vende", /*german*/"die Ware eines #Verkäufers bunter Pflanzen#, |wäre|wären|"},
                     }, {},
                       //clear text
                       Text{"a #bean seller# offers", /*french*/"le #marchand de haricots magiques# vend en fait", /*spanish*/"el #vendedor de judías# ofrece", /*italian*/"il #venditore di fagioli# ha finito i fagioli, quindi ora vende", /*german*/"die Ware des #Erbsenverkäufers#, |wäre|wären|"}
    );

    hintTable[ZR_FROGS_IN_THE_RAIN] = HintText::Exclude({
                       // obscure text
                       Text{"#frogs in a storm# gift", /*french*/"#les grenouilles mouillées# donnent", /*spanish*/"las #ranas bajo la tormenta# regalan", /*italian*/"delle #rane in una tempesta# regalano", /*german*/"bei #stürmischen Fröschen#, |wäre|wären|"},
    });

    hintTable[ZR_FROGS_ZELDAS_LULLABY] = HintText::Exclude({
                       // obscure text
                       Text{"#sleepy frogs# gift",                         /*french*/"#les grenouilles somnolentes# donnent",            /*spanish*/"las #ranas somnolientas# regalan",                  /*italian*/"delle #rane assonnate# regalano",                /*german*/"bei #schläfrigen Fröschen#, |wäre|wären|"},
                       Text{"#the Froggish Tenor in the back-left# gifts", /*french*/"#le ténor grenouillesque au fond à gauche# donne", /*spanish*/"el #Sapo Tenore al fondo, a la izquierda#, regala", /*italian*/"il #musico batrace in fondo a sinistra# regala", /*german*/"beim #quakenden Tenor hinten-links#, |wäre|wären|"},
                       }, {},
                       //clear text
                       Text{"after hearing #Zelda's Lullaby, the frogs# gift", /*french*/"à l'écoute de #la berceuse de Zelda, les grenouilles# donnent", /*spanish*/"después de escuchar #la Nana de Zelda, las ranas# regalan", /*italian*/"dopo aver ascoltato #la Ninna nanna di Zelda, le rane# regalano", /*german*/"bei #Fröschen die Zeldas Wiegenlied gehört# haben, |wäre|wären|"}
    );

    hintTable[ZR_FROGS_EPONAS_SONG] = HintText::Exclude({
                       // obscure text
                       Text{"#equine frogs# gift",                          /*french*/"#les grenouilles équestres# donnent",              /*spanish*/"las #ranas equinas# regalan",                     /*italian*/"delle #rane equine# regalano",                 /*german*/"bei #pferdeartigen Fröschen#, |wäre|wären|"},
                       Text{"#the Froggish Tenor in the back-right# gifts", /*french*/"#le ténor grenouillesque au fond à droite# donne", /*spanish*/"el #Sapo Tenore al fondo, a la derecha#, regala", /*italian*/"il #musico batrace in fondo a destra# regala", /*german*/"beim #quakenden Tenor hinten-rechts#, |wäre|wären|"},
                       }, {},
                       //clear text
                       Text{"after hearing #Epona's Song, the frogs# gift", /*french*/"à l'écoute du #chant d'Epona, les grenouilles# donnent", /*spanish*/"después de escuchar #la Canción de Epona, las ranas# regalan", /*italian*/"dopo aver ascoltato #la Canzone di Epona, le rane# regalano", /*german*/"bei #Fröschen die Eponas Lied gehört# haben, |wäre|wären|"}
    );

    hintTable[ZR_FROGS_SARIAS_SONG] = HintText::Exclude({
                       // obscure text
                       Text{"#sylvan frogs# gift",                      /*french*/"#les grenouilles sylvestres# donnent",           /*spanish*/"las #ranas silvestres# regalan",       /*italian*/"delle #rane silvestri# regalano",      /*german*/"bei #sylvanen Fröschen#, |wäre|wären|"},
                       Text{"#the Froggish Tenor in the center# gifts", /*french*/"#le ténor grenouillesque dans le centre# donne", /*spanish*/"el #Sapo Tenore en el centro# regala", /*italian*/"il #musico batrace al centro# regala", /*german*/"beim #quakenden Tenor in der Mitte#, |wäre|wären|"},
                       }, {},
                       //clear text
                       Text{"after hearing #Saria's Song, the frogs# gift", /*french*/"à l'écoute du #chant de Saria, les grenouilles# donnent", /*spanish*/"después de escuchar #la Canción de Saria, las ranas# regalan", /*italian*/"dopo aver ascoltato #la Canzone di Saria, le rane# regalano", /*german*/"bei #Fröschen die Salias Lied gehört# haben, |wäre|wären|"}
    );

    hintTable[ZR_FROGS_SUNS_SONG] = HintText::Exclude({
                       // obscure text
                       Text{"#enlightened frogs# gift",                     /*french*/"#les grenouilles éclairées# donnent",              /*spanish*/"las #ranas alumbradas# regalan",                     /*italian*/"delle #rane illuminate# regalano",              /*german*/"bei #erleuchteten Fröschen#, |wäre|wären|"},
                       Text{"#the Froggish Tenor in the front-left# gifts", /*french*/"#le ténor grenouillesque à l'avant gauche# donne", /*spanish*/"el #Sapo Tenore al frente, a la izquierda#, regala", /*italian*/"il #musico batrace davanti a sinistra# regala", /*german*/"beim #quakenden Tenor vorne-links#, |wäre|wären|"},
                       }, {},
                       //clear text
                       Text{"after hearing #the Sun's Song, the frogs# gift", /*french*/"à l'écoute du #chant du soleil, les grenouilles# donnent", /*spanish*/"después de escuchar #la Canción del Sol, las ranas# regalan", /*italian*/"dopo aver ascoltato #il Canto del sole, le rane# regalano", /*german*/"bei #Fröschen die die Hymne der Sonne gehört# haben, |wäre|wären|"}
    );

    hintTable[ZR_FROGS_SONG_OF_TIME] = HintText::Exclude({
                       // obscure text
                       Text{"#time-traveling frogs# gift",                   /*french*/"#les grenouilles voyageuses dans le temps# donnent", /*spanish*/"las #ranas viajeras del tiempo# regalan",          /*italian*/"delle #rane che viaggiano nel tempo# regalano", /*german*/"bei #zeitreisenden Fröschen#, |wäre|wären|"},
                       Text{"#the Froggish Tenor in the front-right# gifts", /*french*/"#le ténor grenouillesque à l'avant droite# donne",   /*spanish*/"el #Sapo Tenore al frente, a la derecha#, regala", /*italian*/"il #musico batrace davanti a destra# regala",   /*german*/"beim #quakenden Tenor vorne-rechts#, |wäre|wären|"},
                       }, {},
                       //clear text
                       Text{"after hearing #the Song of Time, the frogs# gift", /*french*/"à l'écoute du #chant du temps, les grenouilles# donnent", /*spanish*/"después de escuchar #la Canción del tiempo, las ranas# regalan", /*italian*/"dopo aver ascoltato #la Canzone del tempo, le rane# regalano", /*german*/"bei #Fröschen die die Hymne der Zeit gehört# haben, |wäre|wären|"}
    );

    hintTable[GF_HBA_1000_POINTS] = HintText::Exclude({
                       // obscure text
                       Text{"scoring 1000 in #horseback archery# grants", /*french*/"obtenir 1000 points dans l'#archerie équestre# donne", /*spanish*/"conseguir 1000 puntos en el #tiro con arco a caballo# premia", /*italian*/"se totalizzi almeno 1000 punti al #tiro con l'arco a cavallo# riceverai", /*german*/"1.000 Punkte beim #berittenen Bogenschießen#, |wäre|wären|"},
    });

    hintTable[MARKET_SHOOTING_GALLERY_REWARD] = HintText::Exclude({
                       // obscure text
                       Text{"#shooting in youth# grants", /*french*/"#faire du tir dans sa jeunesse# donne", /*spanish*/"#disparar en la juventud# otorga", /*italian*/"#sparare ai soldi# in gioventù procura", /*german*/"bei einer #Schießübung der Jugend#, |wäre|wären|"},
    });

    hintTable[KAK_SHOOTING_GALLERY_REWARD] = HintText::Exclude({
                       // obscure text
                       Text{"#shooting in maturity# grants", /*french*/"#faire du tir dans sa maturité# donne", /*spanish*/"#disparar en la madurez# otorga", /*italian*/"#sparare ai soldi# da adulti procura", /*german*/"bei einer #Schießübung des Alters#, |wäre|wären|"},
    });

    hintTable[LW_TARGET_IN_WOODS] = HintText::Exclude({
                       // obscure text
                       Text{"shooting a #target in the woods# grants", /*french*/"#tirer une cible dans les bois# donne", /*spanish*/"disparar a un #blanco forestal# brinda", /*italian*/"#centrare un ceppo# ti fa sputare in faccia", /*german*/"bei einer #Schießübung des Waldes#, |wäre|wären|"},
    });

    hintTable[KAK_ANJU_AS_ADULT] = HintText::Exclude({
                       // obscure text
                       Text{"a #chicken caretaker# offers adults", /*french*/"devenir un #éleveur de Cocottes# donne", /*spanish*/"una #cuidadora de emplumados# le ofrece a los mayores", /*italian*/"un'#allevatrice di polli# affida agli adulti", /*german*/"die Belohnung für #Hühnersitter#, |wäre|wären|"},
    });

    hintTable[LLR_TALONS_CHICKENS] = HintText::Exclude({
                       // obscure text
                       Text{"#finding Super Cuccos# is rewarded with", /*french*/"#trouver des Super Cocottes# donne", /*spanish*/"#hallar los supercucos# conduce a", /*italian*/"il premio per chi trova #i super coccò# è", /*german*/"bei gefundenen #Super-Hühnern#, |wäre|wären|"},
    });

    hintTable[GC_ROLLING_GORON_AS_CHILD] = HintText::Exclude({
                       // obscure text
                       Text{"the prize offered by a #large rolling Goron# is", /*french*/"la récompense d'un #gros Goron roulant# est", /*spanish*/"un #gran Goron rodante# otorga", /*italian*/"il premio offerto da un #grosso Goron rotolante# è", /*german*/"bei einem #großen, rollenden Goronen#, |wäre|wären|"},
    });

    hintTable[LH_UNDERWATER_ITEM] = HintText::Exclude({
                       // obscure text
                       Text{"the #sunken treasure in a lake# is", /*french*/"le #trésor au fond du lac# est", /*spanish*/"el #tesoro hundido del lago# se trata de", /*italian*/"il #tesoro sommerso nel lago# è", /*german*/"der #versunkene Schatz eines Sees#, |wäre|wären|"},
    });

        hintTable[LH_UNDER_WATER_GREEN_RUPEE_1] = HintText::Exclude({
                       // obscure text
                       Text{"EN: LH_UNDER_WATER_GREEN_RUPEE_1 HINT", /*french*/"FR: LH_UNDER_WATER_GREEN_RUPEE_1 HINT", /*spanish*/"ES: LH_UNDER_WATER_GREEN_RUPEE_1 HINT", /*italian*/"IT: LH_UNDER_WATER_GREEN_RUPEE_1 HINT", /*german*/"DE: LH_UNDER_WATER_GREEN_RUPEE_1 HINT"},
    });

        hintTable[LH_UNDER_WATER_GREEN_RUPEE_2] = HintText::Exclude({
                       // obscure text
                       Text{"EN: LH_UNDER_WATER_GREEN_RUPEE_2 HINT", /*french*/"FR: LH_UNDER_WATER_GREEN_RUPEE_2 HINT", /*spanish*/"ES: LH_UNDER_WATER_GREEN_RUPEE_2 HINT", /*italian*/"IT: LH_UNDER_WATER_GREEN_RUPEE_2 HINT", /*german*/"DE: LH_UNDER_WATER_GREEN_RUPEE_2 HINT"},
    });

        hintTable[LH_UNDER_WATER_GREEN_RUPEE_3] = HintText::Exclude({
                       // obscure text
                       Text{"EN: LH_UNDER_WATER_GREEN_RUPEE_3 HINT", /*french*/"FR: LH_UNDER_WATER_GREEN_RUPEE_3 HINT", /*spanish*/"ES: LH_UNDER_WATER_GREEN_RUPEE_3 HINT", /*italian*/"IT: LH_UNDER_WATER_GREEN_RUPEE_3 HINT", /*german*/"DE: LH_UNDER_WATER_GREEN_RUPEE_3 HINT"},
    });


    hintTable[GF_GERUDO_TOKEN] = HintText::Exclude({
                       // obscure text
                       Text{"#rescuing captured carpenters# is rewarded with", /*french*/"#secourir les charpentiers capturés# assure", /*spanish*/"#rescatar los apresados carpinteros# se premia con", /*italian*/"chi salverà i #carpentieri prigionieri# riceverà", /*german*/"bei #geretteten Zimmerleuten#, |wäre|wären|"},
    });

    hintTable[WASTELAND_BOMBCHU_SALESMAN] = HintText::Exclude({
                       // obscure text
                       Text{"a #carpet guru# sells", /*french*/"#un marchand du désert# vend", /*spanish*/"el #genio de una alfombra# vende", /*italian*/"il #mercante volante# vende", /*german*/"die Ware des #fliegenden Einsiedlers#, |wäre|wären|"},
    });

    hintTable[GC_MEDIGORON] = HintText::Exclude({
                       //obscure text
                       Text{"#Medigoron# sells", /*french*/"#Medigoron# vend", /*spanish*/"#Medigoron# vende", /*italian*/"#Medigoron# vende", /*german*/"#Medigoron#, |wäre|wären|"},
    });

    hintTable[KAK_GRANNYS_SHOP] = HintText::Exclude({
                       // obscure text
                       Text{"the #potion shop lady# sells", /*french*/"la #gribiche du magasin de potion# vend", /*spanish*/"la #señora de la tienda de pociones# vende", /*italian*/"la #vecchietta del negozio di pozioni# vende", /*german*/"#Omas Allerlei#, |wäre|wären|"},
    });

    hintTable[KAK_IMPAS_HOUSE_FREESTANDING_POH] = HintText::Exclude({
                       // obscure text
                       Text{"#imprisoned in a house# lies", /*french*/"#encagé dans une maison# gît", /*spanish*/"#en una casa entre rejas# yace", /*italian*/"in una #cella casalinga# puoi trovare", /*german*/"#in einem Hause eingesperrt#, |wäre|wären|"},
    });

    hintTable[HF_TEKTITE_GROTTO_FREESTANDING_POH] = HintText::Exclude({
                       // obscure text
                       Text{"#deep underwater in a hole# is", /*french*/"#dans les profondeurs d'une grotte# gît", /*spanish*/"#en lo hondo bajo un hoyo# yace", /*italian*/"in una #pozza sotterranea# puoi trovare", /*german*/"tief #versunken in einem Erdloch#, |wäre|wären|"},
    });

    hintTable[KAK_WINDMILL_FREESTANDING_POH] = HintText::Exclude({
                       // obscure text
                       Text{"on a #windmill ledge# lies", /*french*/"#haut perché dans le moulin# gît", /*spanish*/"al #borde de un molino# yace", /*italian*/"#nel mulino, in alto#, puoi trovare", /*german*/"auf einem #Vorsprung einer Windmühle#, |wäre|wären|"},
    });

    hintTable[GRAVEYARD_DAMPE_RACE_FREESTANDING_POH] = HintText::Exclude({
                       // obscure text
                       Text{"#racing a ghost# leads to", /*french*/"le défi du #revenant rapide# donne", /*spanish*/"#perseguir a un fantasma# conduce a", /*italian*/"#gareggiare contro un fantasma# fa vincere", /*german*/"bei einem #geisterhaften Rennen#, |wäre|wären|"},
                     }, {},
                       //clear text
                       Text{"#dead Dampe's second# prize is", /*french*/"la #deuxième course d'Igor# donne", /*spanish*/"el segundo premio de #la carrera de Dampé# se trata de", /*italian*/"la seconda ricompensa del #fantasma di Danpei# è", /*german*/"#Boris' zweiter Preis#, |wäre|wären|"}
    );

    hintTable[LLR_FREESTANDING_POH] = HintText::Exclude({
                       // obscure text
                       Text{"in a #ranch silo# lies", /*french*/"#dans l'entrepôt de la ferme# gît", /*spanish*/"en un #granero rupestre# yace", /*italian*/"nel #granaio della fattoria# puoi trovare", /*german*/"im #Silo der Farm#, |wäre|wären|"},
    });

    hintTable[GRAVEYARD_FREESTANDING_POH] = HintText::Exclude({
                       // obscure text
                       Text{"a #crate in a graveyard# hides", /*french*/"#la boîte dans le cimetière# contient", /*spanish*/"bajo la #caja de un cementerio# yace", /*italian*/"una #cassa nel cimitero# contiene", /*german*/"in einer #Kiste des Friedhofs#, |wäre|wären|"},
    });

    hintTable[GRAVEYARD_DAMPE_GRAVEDIGGING_TOUR] = HintText::Exclude({
                       // obscure text
                       Text{"a #gravekeeper digs up#", /*french*/"#le jeu du fossoyeur# cache", /*spanish*/"cierto #sepultero desentierra#", /*italian*/"un #becchino dissotterra#", /*german*/"#Boris' Ausgrabung#, |wäre|wären|"},
    });

    hintTable[ZR_NEAR_OPEN_GROTTO_FREESTANDING_POH] = HintText::Exclude({
                       // obscure text
                       Text{"on top of a #pillar in a river# lies", /*french*/"#sur un pilier au dessus du fleuve# gît", /*spanish*/"en lo alto del #pilar de un río# yace", /*italian*/"in cima a una #colonna sul fiume# puoi trovare", /*german*/"auf einer #Säule eines Flusses#, |wäre|wären|"},
    });

    hintTable[ZR_NEAR_DOMAIN_FREESTANDING_POH] = HintText::Exclude({
                       // obscure text
                       Text{"on a #river ledge by a waterfall# lies", /*french*/"#sur la falaise au dessus du fleuve# gît", /*spanish*/"al borde de #la entrada a una cascada# yace", /*italian*/"su una sporgenza #vicino alle cascate insonni# puoi trovare", /*german*/"auf einem #Vorsprung nahe eines Wasserfalls#, |wäre|wären|"},
    });

    hintTable[LH_FREESTANDING_POH] = HintText::Exclude({
                       // obscure text
                       Text{"high on a #lab rooftop# one can find", /*french*/"#la tour d'observation du lac# cache", /*spanish*/"en lo #alto de un laboratorio# yace", /*italian*/"sopra il #tetto di un laboratorio# qualcuno ha messo", /*german*/"auf dem #Dach eines Labors#, |wäre|wären|"},
    });

    hintTable[ZF_ICEBERG_FREESTANDING_POH] = HintText::Exclude({
                       // obscure text
                       Text{"#floating on ice# is", /*french*/"#gisant sur la glace# gît", /*spanish*/"#flotando sobre hielo# yace", /*italian*/"#saltare fra gli iceberg# porta verso", /*german*/"auf einer #Eisscholle#, |wäre|wären|"},
    });

    hintTable[GV_WATERFALL_FREESTANDING_POH] = HintText::Exclude({
                       // obscure text
                       Text{"behind a #desert waterfall# is", /*french*/"#derrière la cascade du désert# se cache", /*spanish*/"tras una #desierta cascada# yace", /*italian*/"#dietro una cascata# c'è una nicchia con", /*german*/"hinter einem #Wasserfall des Tals#, |wäre|wären|"},
    });

    hintTable[GV_CRATE_FREESTANDING_POH] = HintText::Exclude({
                       // obscure text
                       Text{"a #crate in a valley# hides", /*french*/"la #boîte dans la vallée# contient", /*spanish*/"bajo la #caja de un valle# yace", /*italian*/"una #cassa nella valle# contiene", /*german*/"in einer #Kiste des Tals#, |wäre|wären|"},
    });

    hintTable[COLOSSUS_FREESTANDING_POH] = HintText::Exclude({
                       // obscure text
                       Text{"on top of an #arch of stone# lies", /*french*/"#gisant sur une arche de pierre# gît", /*spanish*/"en lo alto de un #arco de piedra# yace", /*italian*/"in cima a #un arco di pietra# puoi trovare", /*german*/"auf einem #steinernen Torbogen#, |wäre|wären|"},
    });

    hintTable[DMT_FREESTANDING_POH] = HintText::Exclude({
                       // obscure text
                       Text{"above a #mountain cavern entrance# is", /*french*/"gisant #au dessus de la caverne montagneuse# gît", /*spanish*/"en lo alto de la #entrada de una cueva en la montaña# yace", /*italian*/"sopra #l'ingresso di una caverna montana# puoi trovare", /*german*/"über einem #Höhleneingang des Berges#, |wäre|wären|"},
    });
    hintTable[DMT_ROCK_BLUE_RUPEE] = HintText::Exclude({
                       // obscure text
                       Text{"EN: DMT_ROCK_BLUE_RUPEE Hint", /*french*/"FR: DMT_ROCK_BLUE_RUPEE Hint", /*spanish*/"ES: DMT_ROCK_BLUE_RUPEE Hint", /*italian*/"IT: DMT_ROCK_BLUE_RUPEE Hint", /*german*/"DE: DMT_ROCK_BLUE_RUPEE Hint"},
                     }
    );

    hintTable[DMT_ROCK_RED_RUPEE] = HintText::Exclude({
                       // obscure text
                       Text{"EN: DMT_ROCK_RED_RUPEE Hint", /*french*/"FR: DMT_ROCK_RED_RUPEE Hint", /*spanish*/"ES: DMT_ROCK_RED_RUPEE Hint", /*italian*/"IT: DMT_ROCK_RED_RUPEE Hint", /*german*/"DE: DMT_ROCK_RED_RUPEE Hint"},
                     }
    );

    
    hintTable[DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_1] = HintText::Exclude({
                       // obscure text
                       Text{"EN: DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_1 Hint", /*french*/"FR: DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_1 Hint", /*spanish*/"ES: DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_1 Hint", /*italian*/"IT: DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_1 Hint", /*german*/"DE: DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_1 Hint"},
                     }
    );
    
    hintTable[DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_2] = HintText::Exclude({
                       // obscure text
                       Text{"EN: DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_2 Hint", /*french*/"FR: DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_2 Hint", /*spanish*/"ES: DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_2 Hint", /*italian*/"IT: DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_2 Hint", /*german*/"DE: DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_2 Hint"},
                     }
    );
    
    hintTable[DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_3] = HintText::Exclude({
                       // obscure text
                       Text{"EN: DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_3 Hint", /*french*/"FR: DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_3 Hint", /*spanish*/"ES: DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_3 Hint", /*italian*/"IT: DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_3 Hint", /*german*/"DE: DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_3 Hint"},
                     }
    );
    
    hintTable[DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_4] = HintText::Exclude({
                       // obscure text
                       Text{"EN: DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_4 Hint", /*french*/"FR: DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_4 Hint", /*spanish*/"ES: DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_4 Hint", /*italian*/"IT: DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_4 Hint", /*german*/"DE: DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_4 Hint"},
                     }
    );
    
    hintTable[DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_5] = HintText::Exclude({
                       // obscure text
                       Text{"EN: DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_5 Hint", /*french*/"FR: DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_5 Hint", /*spanish*/"ES: DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_5 Hint", /*italian*/"IT: DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_5 Hint", /*german*/"DE: DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_5 Hint"},
                     }
    );
    
    hintTable[DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_6] = HintText::Exclude({
                       // obscure text
                       Text{"EN: DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_6 Hint", /*french*/"FR: DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_6 Hint", /*spanish*/"ES: DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_6 Hint", /*italian*/"IT: DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_6 Hint", /*german*/"DE: DMT_COW_GROTTO_RUPEE_CIRCLE_GREEN_RUPEE_6 Hint"},
                     }
    );
    
    hintTable[DMT_COW_GROTTO_RUPEE_CIRCLE_RED_RUPEE] = HintText::Exclude({
                       // obscure text
                       Text{"EN: DMT_COW_GROTTO_RUPEE_CIRCLE_RED_RUPEE Hint", /*french*/"FR: DMT_COW_GROTTO_RUPEE_CIRCLE_RED_RUPEE Hint", /*spanish*/"ES: DMT_COW_GROTTO_RUPEE_CIRCLE_RED_RUPEE Hint", /*italian*/"IT: DMT_COW_GROTTO_RUPEE_CIRCLE_RED_RUPEE Hint", /*german*/"DE: DMT_COW_GROTTO_RUPEE_CIRCLE_RED_RUPEE Hint"},
                     }
    );

    hintTable[DMC_WALL_FREESTANDING_POH] = HintText::Exclude({
                       // obscure text
                       Text{"nestled in a #volcanic wall# is", /*french*/"dans une #alcove volcanique# gît", /*spanish*/"entre unas #murallas volcánicas# yace", /*italian*/"in una #nicchia vulcanica# puoi trovare", /*german*/"in einer #vulkanischen Wand#, |wäre|wären|"},
    });

    hintTable[DMC_VOLCANO_FREESTANDING_POH] = HintText::Exclude({
                       // obscure text
                       Text{"obscured by #volcanic ash# is", /*french*/"#recouvert de cendres volcaniques# gît", /*spanish*/"bajo la #ceniza volcánica# yace", /*italian*/"il #fumo di un vulcano# cela", /*german*/"auf einem #dampfenden Vulkan#, |wäre|wären|"},
    });
        hintTable[DMC_LOWER_RED_RUPEE_1] = HintText::Exclude({
                       // obscure text
                       Text{"EN: DMC_LOWER_RED_RUPEE_1 Hint", /*french*/"FR: DMC_LOWER_RED_RUPEE_1 Hint", /*spanish*/"ES: DMC_LOWER_RED_RUPEE_1 Hint", /*italian*/"IT: DMC_LOWER_RED_RUPEE_1 Hint", /*german*/"DE: DMC_LOWER_RED_RUPEE_1 Hint"},
                     }
    );
            hintTable[DMC_LOWER_RED_RUPEE_2] = HintText::Exclude({
                       // obscure text
                       Text{"EN: DMC_LOWER_RED_RUPEE_2 Hint", /*french*/"FR: DMC_LOWER_RED_RUPEE_2 Hint", /*spanish*/"ES: DMC_LOWER_RED_RUPEE_2 Hint", /*italian*/"IT: DMC_LOWER_RED_RUPEE_2 Hint", /*german*/"DE: DMC_LOWER_RED_RUPEE_2 Hint"},
                     }
    );
            hintTable[DMC_LOWER_BLUE_RUPEE_1] = HintText::Exclude({
                       // obscure text
                       Text{"EN: DMC_LOWER_BLUE_RUPEE_1 Hint", /*french*/"FR: DMC_LOWER_BLUE_RUPEE_1 Hint", /*spanish*/"ES: DMC_LOWER_BLUE_RUPEE_1 Hint", /*italian*/"IT: DMC_LOWER_BLUE_RUPEE_1 Hint", /*german*/"DE: DMC_LOWER_BLUE_RUPEE_1 Hint"},
                     }
    );
            hintTable[DMC_LOWER_BLUE_RUPEE_2] = HintText::Exclude({
                       // obscure text
                       Text{"EN: DMC_LOWER_BLUE_RUPEE_2 Hint", /*french*/"FR: DMC_LOWER_BLUE_RUPEE_2 Hint", /*spanish*/"ES: DMC_LOWER_BLUE_RUPEE_2 Hint", /*italian*/"IT: DMC_LOWER_BLUE_RUPEE_2 Hint", /*german*/"DE: DMC_LOWER_BLUE_RUPEE_2 Hint"},
                     }
    );
            hintTable[DMC_LOWER_BLUE_RUPEE_3] = HintText::Exclude({
                       // obscure text
                       Text{"EN: DMC_LOWER_BLUE_RUPEE_3 Hint", /*french*/"FR: DMC_LOWER_BLUE_RUPEE_3 Hint", /*spanish*/"ES: DMC_LOWER_BLUE_RUPEE_3 Hint", /*italian*/"IT: DMC_LOWER_BLUE_RUPEE_3 Hint", /*german*/"DE: DMC_LOWER_BLUE_RUPEE_3 Hint"},
                     }
    );
            hintTable[DMC_LOWER_BLUE_RUPEE_4] = HintText::Exclude({
                       // obscure text
                       Text{"EN: DMC_LOWER_BLUE_RUPEE_4 Hint", /*french*/"FR: DMC_LOWER_BLUE_RUPEE_4 Hint", /*spanish*/"ES: DMC_LOWER_BLUE_RUPEE_4 Hint", /*italian*/"IT: DMC_LOWER_BLUE_RUPEE_4 Hint", /*german*/"DE: DMC_LOWER_BLUE_RUPEE_4 Hint"},
                     }
    );
            hintTable[DMC_LOWER_BLUE_RUPEE_5] = HintText::Exclude({
                       // obscure text
                       Text{"EN: DMC_LOWER_BLUE_RUPEE_5 Hint", /*french*/"FR: DMC_LOWER_BLUE_RUPEE_5 Hint", /*spanish*/"ES: DMC_LOWER_BLUE_RUPEE_5 Hint", /*italian*/"IT: DMC_LOWER_BLUE_RUPEE_5 Hint", /*german*/"DE: DMC_LOWER_BLUE_RUPEE_5 Hint"},
                     }
    );
            hintTable[DMC_LOWER_BLUE_RUPEE_6] = HintText::Exclude({
                       // obscure text
                       Text{"EN: DMC_LOWER_BLUE_RUPEE_6 Hint", /*french*/"FR: DMC_LOWER_BLUE_RUPEE_6 Hint", /*spanish*/"ES: DMC_LOWER_BLUE_RUPEE_6 Hint", /*italian*/"IT: DMC_LOWER_BLUE_RUPEE_6 Hint", /*german*/"DE: DMC_LOWER_BLUE_RUPEE_6 Hint"},
                     }
    );

    hintTable[DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_1] = HintText::Exclude({
                       // obscure text
                       Text{"EN: DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_1 Hint", /*french*/"FR: DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_1 Hint", /*spanish*/"ES: DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_1 Hint", /*italian*/"IT: DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_1 Hint", /*german*/"DE: DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_1 Hint"},
                     }
    );
        hintTable[DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_2] = HintText::Exclude({
                       // obscure text
                       Text{"EN: DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_2 Hint", /*french*/"FR: DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_2 Hint", /*spanish*/"ES: DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_2 Hint", /*italian*/"IT: DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_2 Hint", /*german*/"DE: DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_2 Hint"},
                     }
    );

        hintTable[DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_3] = HintText::Exclude({
                       // obscure text
                       Text{"EN: DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_3 Hint", /*french*/"FR: DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_3 Hint", /*spanish*/"ES: DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_3 Hint", /*italian*/"IT: DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_3 Hint", /*german*/"DE: DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_3 Hint"},
                     }
    );

        hintTable[DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_4] = HintText::Exclude({
                       // obscure text
                       Text{"EN: DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_4 Hint", /*french*/"FR: DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_4 Hint", /*spanish*/"ES: DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_4 Hint", /*italian*/"IT: DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_4 Hint", /*german*/"DE: DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_4 Hint"},
                     }
    );

        hintTable[DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_5] = HintText::Exclude({
                       // obscure text
                       Text{"EN: DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_5 Hint", /*french*/"FR: DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_5 Hint", /*spanish*/"ES: DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_5 Hint", /*italian*/"IT: DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_5 Hint", /*german*/"DE: DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_5 Hint"},
                     }
    );

        hintTable[DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_6] = HintText::Exclude({
                       // obscure text
                       Text{"EN: DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_6 Hint", /*french*/"FR: DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_6 Hint", /*spanish*/"ES: DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_6 Hint", /*italian*/"IT: DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_6 Hint", /*german*/"DE: DMC_SCARE_CROW_RUPEE_CIRCLE_GREEN_RUPEE_6 Hint"},
                     }
    );

        hintTable[DMC_SCARE_CROW_RUPEE_CIRCLE_RED_RUPEE] = HintText::Exclude({
                       // obscure text
                       Text{"EN: DMC_SCARE_CROW_RUPEE_CIRCLE_RED_RUPEE Hint", /*french*/"FR: DMC_SCARE_CROW_RUPEE_CIRCLE_RED_RUPEE Hint", /*spanish*/"ES: DMC_SCARE_CROW_RUPEE_CIRCLE_RED_RUPEE Hint", /*italian*/"IT: DMC_SCARE_CROW_RUPEE_CIRCLE_RED_RUPEE Hint", /*german*/"DE: DMC_SCARE_CROW_RUPEE_CIRCLE_RED_RUPEE Hint"},
                     }
    );


    hintTable[GF_NORTH_F1_CARPENTER] = HintText::Exclude({
                       // obscure text
                       Text{"#defeating Gerudo guards# reveals", /*french*/"les #geôliers Gerudo# détiennent", /*spanish*/"#derrotar a las guardas Gerudo# revela", /*italian*/"una #guardia Gerudo# possiede", /*german*/"nahe einer #Gerudo-Wächterin#, |wäre|wären|"},
    });

    hintTable[GF_NORTH_F2_CARPENTER] = HintText::Exclude({
                       // obscure text
                       Text{"#defeating Gerudo guards# reveals", /*french*/"les #geôliers Gerudo# détiennent", /*spanish*/"#derrotar a las guardas Gerudo# revela", /*italian*/"una #guardia Gerudo# possiede", /*german*/"nahe einer #Gerudo-Wächterin#, |wäre|wären|"},
    });

    hintTable[GF_SOUTH_F1_CARPENTER] = HintText::Exclude({
                       // obscure text
                       Text{"#defeating Gerudo guards# reveals", /*french*/"les #geôliers Gerudo# détiennent", /*spanish*/"#derrotar a las guardas Gerudo# revela", /*italian*/"una #guardia Gerudo# possiede", /*german*/"nahe einer #Gerudo-Wächterin#, |wäre|wären|"},
    });

    hintTable[GF_SOUTH_F2_CARPENTER] = HintText::Exclude({
                       // obscure text
                       Text{"#defeating Gerudo guards# reveals", /*french*/"les #geôliers Gerudo# détiennent", /*spanish*/"#derrotar a las guardas Gerudo# revela", /*italian*/"una #guardia Gerudo# possiede", /*german*/"nahe einer #Gerudo-Wächterin#, |wäre|wären|"},
    });


    hintTable[HF_GS_NEAR_KAK_GROTTO] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider-guarded spider in a hole# hoards", /*french*/"une #Skulltula dans un trou d'arachnides# a", /*spanish*/"una #Skulltula custodiada por otra# de un hoyo otorga", /*italian*/"in una grotta un #ragno protegge un'altro ragno# con", /*german*/"in einem Erdloch mit #zwei Spinnen#, |wäre|wären|"},
    });


    hintTable[LLR_GS_BACK_WALL] = HintText::Exclude({
                       // obscure text
                       Text{"night reveals a #spider in a ranch# holding", /*french*/"une #Skulltula sur la façade de la ferme# a", /*spanish*/"la noche revela una #Skulltula del rancho# que otorga", /*italian*/"#nella fattoria di notte# esce un ragno con", /*german*/"in einer nachtaktiven #Spinne einer Farm#, |wäre|wären|"},
    });

    hintTable[LLR_GS_RAIN_SHED] = HintText::Exclude({
                       // obscure text
                       Text{"night reveals a #spider in a ranch# holding", /*french*/"une #Skulltula sur le mur de l'enclos# a", /*spanish*/"la noche revela una #Skulltula del rancho# que otorga", /*italian*/"#nella fattoria di notte# esce un ragno con", /*german*/"in einer nachtaktiven #Spinne einer Farm#, |wäre|wären|"},
    });

    hintTable[LLR_GS_HOUSE_WINDOW] = HintText::Exclude({
                       // obscure text
                       Text{"night reveals a #spider in a ranch# holding", /*french*/"une #Skulltula sur la maison de ferme# a", /*spanish*/"la noche revela una #Skulltula del rancho# que otorga", /*italian*/"#nella fattoria di notte# esce un ragno con", /*german*/"in einer nachtaktiven #Spinne einer Farm#, |wäre|wären|"},
    });

    hintTable[LLR_GS_TREE] = HintText::Exclude({
                       // obscure text
                       Text{"a spider hiding in a #ranch tree# holds", /*french*/"une #Skulltula dans l'arbre de la ferme# a", /*spanish*/"una Skulltula escondida en el #árbol de un rancho# otorga", /*italian*/"#su un albero nella fattoria# si nasconde un ragno con", /*german*/"in der Spinne im #Baum einer Farm#, |wäre|wären|"},
    });


    hintTable[KF_GS_BEAN_PATCH] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider buried in a forest# holds", /*french*/"une #Skulltula enterrée dans la forêt# a", /*spanish*/"una #Skulltula enterrada en un bosque# otorga", /*italian*/"un #ragno sepolto nella foresta# nasconde", /*german*/"in einer, #im Wald vergrabenen Spinne#, |wäre|wären|"},
    });

    hintTable[KF_GS_KNOW_IT_ALL_HOUSE] = HintText::Exclude({
                       // obscure text
                       Text{"night in the past reveals a #spider in a forest# holding", /*french*/"une #Skulltula derrière une cabane de la forêt# a", /*spanish*/"la noche revela en el pasado una #Skulltula del bosque# que otorga", /*italian*/"un ragno #dietro una casa di saccenti# ha", /*german*/"in einer nachtaktiven #Spinne eines Waldes#, |wäre|wären|"},
    });

    hintTable[KF_GS_HOUSE_OF_TWINS] = HintText::Exclude({
                       // obscure text
                       Text{"night in the future reveals a #spider in a forest# holding", /*french*/"une #Skulltula sur une cabane de la forêt# a", /*spanish*/"la noche revela en el futuro una #Skulltula del bosque# que otorga", /*italian*/"un ragno #sopra una casa nella foresta# ha", /*german*/"in einer nachtaktiven #Spinne eines Waldes#, |wäre|wären|"},
    });


    hintTable[LW_GS_BEAN_PATCH_NEAR_BRIDGE] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider buried deep in a forest maze# holds", /*french*/"une #Skulltula enterrée dans les bois# a", /*spanish*/"una #Skulltula enterrada en un laberinto forestal# otorga", /*italian*/"un #ragno sepolto in un dedalo silvestre# ha", /*german*/"in einer, #im Wald vergrabenen Spinne#, |wäre|wären|"},
    });

    hintTable[LW_GS_BEAN_PATCH_NEAR_THEATER] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider buried deep in a forest maze# holds", /*french*/"une #Skulltula enterrée dans les bois# a", /*spanish*/"una #Skulltula enterrada en un laberinto forestal# otorga", /*italian*/"un #ragno sepolto in un dedalo silvestre# ha", /*german*/"in einer, #im Wald vergrabenen Spinne#, |wäre|wären|"},
    });

    hintTable[LW_GS_ABOVE_THEATER] = HintText::Exclude({
                       // obscure text
                       Text{"night reveals a #spider deep in a forest maze# holding", /*french*/"une #Skulltula haut perchée dans les bois# a", /*spanish*/"la noche revela una #Skulltula del laberinto forestal# que otorga", /*italian*/"#in un dedalo silvestre di notte# esce un ragno con", /*german*/"in einer nachtaktiven #Spinne eines Waldes#, |wäre|wären|"},
    });

    hintTable[SFM_GS] = HintText::Exclude({
                       // obscure text
                       Text{"night reveals a #spider in a forest meadow# holding", /*french*/"une #Skulltula dans le sanctuaire des bois# a", /*spanish*/"la noche revela una #Skulltula de la pradera del bosque# que otorga", /*italian*/"#in una radura di notte# esce un ragno con", /*german*/"in einer nachtaktiven #Spinne einer Lichtung#, |wäre|wären|"},
    });


    hintTable[OGC_GS] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider outside a tyrant's tower# holds", /*french*/"une #Skulltula parmi les ruines du château# a", /*spanish*/"una #Skulltula a las afueras de la torre de un tirano# otorga", /*italian*/"un ragno #vicino alla torre di un tiranno# ha", /*german*/"in einer #Spinne am Turm des Tyrannen#, |wäre|wären|"},
    });

    hintTable[HC_GS_TREE] = HintText::Exclude({
                       // obscure text
                       Text{"a spider hiding in a #tree outside of a castle# holds", /*french*/"une #Skulltula dans l'arbre près du château# a", /*spanish*/"una Skulltula escondida en el #árbol de las afueras de un castillo# otorga", /*italian*/"un #ragno arboreo presso un castello# nasconde", /*german*/"in der Spinne, im #Baum eines Schlosses#, |wäre|wären|"},
    });

    hintTable[MARKET_GS_GUARD_HOUSE] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider in a guarded crate# holds", /*french*/"une #Skulltula dans une boîte en ville# a", /*spanish*/"una #Skulltula bajo una custodiada caja# otorga", /*italian*/"un #ragno sotto una cassa custodita# ha", /*german*/"in der #Spinne einer streng bewachten Kiste#, |wäre|wären|"},
    });


    hintTable[DMC_GS_BEAN_PATCH] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider buried in a volcano# holds", /*french*/"une #Skulltula enterrée dans un volcan# a", /*spanish*/"una #Skulltula enterrada en un volcán# otorga", /*italian*/"un #ragno sepolto in un vulcano# ha", /*german*/"in einer, #im Krater vergrabenen Spinne#, |wäre|wären|"},
    });


    hintTable[DMT_GS_BEAN_PATCH] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider buried outside a cavern# holds", /*french*/"une #Skulltula enterrée près d'une caverne# a", /*spanish*/"una #Skulltula enterrada a la entrada de una cueva# otorga", /*italian*/"un #ragno sepolto all'ingresso di una caverna# ha", /*german*/"in einer, #am Gebirgspfad vergrabenen Spinne#, |wäre|wären|"},
    });

    hintTable[DMT_GS_NEAR_KAK] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider hidden in a mountain nook# holds", /*french*/"une #Skulltula cachée dans le flanc d'une montagne# a", /*spanish*/"una #Skulltula oculta en el rincón de la montaña# otorga", /*italian*/"un #ragno in una nicchia montana# si nasconde con", /*german*/"in einer #Spinne einer Bergnische#, |wäre|wären|"},
    });

    hintTable[DMT_GS_ABOVE_DODONGOS_CAVERN] = HintText::Exclude({
                       // obscure text
                       Text{"the hammer reveals a #spider on a mountain# holding", /*french*/"une #Skulltula derrière un rocher massif près d'une caverne# a", /*spanish*/"el martillo revela #una Skulltula de la montaña# que otorga", /*italian*/"il martello rivela un #ragno in montagna# con", /*german*/"in einer, hinter #braunen Felsen# krabbelnden Spinne, |wäre|wären|"},
    });

    hintTable[DMT_GS_FALLING_ROCKS_PATH] = HintText::Exclude({
                       // obscure text
                       Text{"the hammer reveals a #spider on a mountain# holding", /*french*/"une #Skulltula derrière un rocher massif près du sommet d'un volcan# a", /*spanish*/"el martillo revela #una Skulltula de la montaña# que otorga", /*italian*/"il martello rivela un #ragno in montagna# con", /*german*/"in einer, hinter #braunen Felsen# krabbelnden Spinne, |wäre|wären|"},
    });


    hintTable[GC_GS_CENTER_PLATFORM] = HintText::Exclude({
                       // obscure text
                       Text{"a #suspended spider# in Goron City holds", /*french*/"une #Skulltula perchée dans le village Goron# a", /*spanish*/"una #Skulltula suspendida# en la Ciudad Goron otorga", /*italian*/"un #ragno sospeso# nella città dei Goron ha", /*german*/"in der #einsamen Spinne# Goronias, |wäre|wären|"},
    });

    hintTable[GC_GS_BOULDER_MAZE] = HintText::Exclude({
                       // obscure text
                       Text{"a spider in a #Goron City crate# holds", /*french*/"une #Skulltula dans une boîte du village Goron# a", /*spanish*/"una #Skulltula bajo una caja# de la Ciudad Goron otorga", /*italian*/"in una #cassa nella città dei Goron# si nasconde un ragno con", /*german*/"in der Spinne einer #Kiste Goronias#, |wäre|wären|"},
    });


    hintTable[KAK_GS_HOUSE_UNDER_CONSTRUCTION] = HintText::Exclude({
                       // obscure text
                       Text{"night in the past reveals a #spider in a town# holding", /*french*/"une #Skulltula dans le chantier de construction# a", /*spanish*/"la noche del pasado revela una #Skulltula del pueblo# que otorga", /*italian*/"la notte nel passato rivela un #ragno in un villaggio# con", /*german*/"in einer nachtaktiven #Spinne eines Dorfes#, |wäre|wären|"},
    });

    hintTable[KAK_GS_SKULLTULA_HOUSE] = HintText::Exclude({
                       // obscure text
                       Text{"night in the past reveals a #spider in a town# holding", /*french*/"une #Skulltula sur une maison maudite# a", /*spanish*/"la noche del pasado revela una #Skulltula del pueblo# que otorga", /*italian*/"la notte nel passato rivela un #ragno in un villaggio# con", /*german*/"in einer nachtaktiven #Spinne eines Dorfes#, |wäre|wären|"},
    });

    hintTable[KAK_GS_GUARDS_HOUSE] = HintText::Exclude({
                       // obscure text
                       Text{"night in the past reveals a #spider in a town# holding", /*french*/"une #Skulltula sur une maison de village# a", /*spanish*/"la noche del pasado revela una #Skulltula del pueblo# que otorga", /*italian*/"la notte nel passato rivela un #ragno in un villaggio# con", /*german*/"in einer nachtaktiven #Spinne eines Dorfes#, |wäre|wären|"},
    });

    hintTable[KAK_GS_TREE] = HintText::Exclude({
                       // obscure text
                       Text{"night in the past reveals a #spider in a town# holding", /*french*/"une #Skulltula dans un arbre de village# a", /*spanish*/"la noche del pasado revela una #Skulltula del pueblo# que otorga", /*italian*/"la notte nel passato rivela un #ragno in un villaggio# con", /*german*/"in einer nachtaktiven #Spinne eines Dorfes#, |wäre|wären|"},
    });

    hintTable[KAK_GS_WATCHTOWER] = HintText::Exclude({
                       // obscure text
                       Text{"night in the past reveals a #spider in a town# holding", /*french*/"une #Skulltula sur une échelle dans un village# a", /*spanish*/"la noche del pasado revela una #Skulltula del pueblo# que otorga", /*italian*/"la notte nel passato rivela un #ragno in un villaggio# con", /*german*/"in einer nachtaktiven #Spinne eines Dorfes#, |wäre|wären|"},
    });

    hintTable[KAK_GS_ABOVE_IMPAS_HOUSE] = HintText::Exclude({
                       // obscure text
                       Text{"night in the future reveals a #spider in a town# holding", /*french*/"une #Skulltula au dessus d'une grande maison# a", /*spanish*/"la noche del futuro revela una #Skulltula del pueblo# que otorga", /*italian*/"la notte nel futuro rivela un #ragno in un villaggio# con", /*german*/"in einer nachtaktiven #Spinne eines Dorfes#, |wäre|wären|"},
    });


    hintTable[GRAVEYARD_GS_WALL] = HintText::Exclude({
                       // obscure text
                       Text{"night reveals a #spider in a graveyard# holding", /*french*/"une #Skulltula sur une façade du cimetière# a", /*spanish*/"la noche revela una #Skulltula del cementerio# que otorga", /*italian*/"di notte appare un #ragno nel cimitero# con", /*german*/"in einer nachtaktiven #Spinne eines Friedhofs#, |wäre|wären|"},
    });

    hintTable[GRAVEYARD_GS_BEAN_PATCH] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider buried in a graveyard# holds", /*french*/"une #Skulltula enterrée dans le cimetière# a", /*spanish*/"una #Skulltula enterrada en el cementerio# otorga", /*italian*/"un #ragno sepolto nel cimitero# ha", /*german*/"in einer, #am Friedhof vergrabenen Spinne#, |wäre|wären|"},
    });


    hintTable[ZR_GS_LADDER] = HintText::Exclude({
                       // obscure text
                       Text{"night in the past reveals a #spider in a river# holding", /*french*/"une #Skulltula sur une échelle près d'une cascade# a", /*spanish*/"la noche del pasado revela una #Skulltula del río# que otorga", /*italian*/"di notte nel passato appare un #ragno nel fiume# con", /*german*/"in einer nachtaktiven #Spinne eines Flusses#, |wäre|wären|"},
    });

    hintTable[ZR_GS_TREE] = HintText::Exclude({
                       // obscure text
                       Text{"a spider hiding in a #tree by a river# holds", /*french*/"une #Skulltula dans un arbre près du fleuve# a", /*spanish*/"una Skulltula escondida en el #árbol de un río# otorga", /*italian*/"un ragno in un #albero presso il fiume# ha", /*german*/"in der Spinne im #Baum nahe eines Flusses#, |wäre|wären|"},
    });

    hintTable[ZR_GS_ABOVE_BRIDGE] = HintText::Exclude({
                       // obscure text
                       Text{"night in the future reveals a #spider in a river# holding", /*french*/"une #Skulltula sur une façade près d'une cascade# a", /*spanish*/"la noche del futuro revela una #Skulltula del río# que otorga", /*italian*/"di notte nel futuro appare un #ragno nel fiume# con", /*german*/"in einer nachtaktiven #Spinne eines Flusses#, |wäre|wären|"},
    });

    hintTable[ZR_GS_NEAR_RAISED_GROTTOS] = HintText::Exclude({
                       // obscure text
                       Text{"night in the future reveals a #spider in a river# holding", /*french*/"une #Skulltula sur une façade près d'une grotte du fleuve# a", /*spanish*/"la noche del futuro revela una #Skulltula del río# que otorga", /*italian*/"di notte nel futuro appare un #ragno nel fiume# con", /*german*/"in einer nachtaktiven #Spinne eines Flusses#, |wäre|wären|"},
    });


    hintTable[ZD_GS_FROZEN_WATERFALL] = HintText::Exclude({
                       // obscure text
                       Text{"night reveals a #spider by a frozen waterfall# holding", /*french*/"une #Skulltula près d'une cascade gelée# a", /*spanish*/"la noche revela una #Skulltula junto a una congelada cascada# que otorga", /*italian*/"di notte appare un #ragno presso una cascata congelata# con", /*german*/"in einer nachtaktiven #Spinne eines gefrorenen Wasserfalls#, |wäre|wären|"},
    });

    hintTable[ZF_GS_ABOVE_THE_LOG] = HintText::Exclude({
                       // obscure text
                       Text{"night reveals a #spider near a deity# holding", /*french*/"une #Skulltula près du gardien aquatique# a", /*spanish*/"la noche revela una #Skulltula junto a cierta deidad# que otorga", /*italian*/"di notte appare un #ragno presso una divinità# con", /*german*/"in einer nachtaktiven #Spinne nahe einer Gottheit#, |wäre|wären|"},
    });

    hintTable[ZF_GS_TREE] = HintText::Exclude({
                       // obscure text
                       Text{"a spider hiding in a #tree near a deity# holds", /*french*/"une #Skulltula dans un arbre dans un réservoir# a", /*spanish*/"una Skulltula escondida en el #árbol junto a cierta deidad# otorga", /*italian*/"un ragno su un #albero presso una divinità# ha", /*german*/"in der Spinne am #Baum nahe einer Gottheit#, |wäre|wären|"},
    });


    hintTable[LH_GS_BEAN_PATCH] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider buried by a lake# holds", /*french*/"une #Skulltula enterrée près d'un lac# a", /*spanish*/"una #Skulltula enterrada junto a un lago# otorga", /*italian*/"un #ragno sepolto presso un lago# ha", /*german*/"in einer, #am See vergrabenen Spinne#, |wäre|wären|"},
    });

    hintTable[LH_GS_SMALL_ISLAND] = HintText::Exclude({
                       // obscure text
                       Text{"night reveals a #spider by a lake# holding", /*french*/"une #Skulltula sur un îlot du lac# a", /*spanish*/"la noche revela una #Skulltula junto a un lago# que otorga", /*italian*/"di notte appare un #ragno lacustre# che ha", /*german*/"in einer nachtaktiven #Spinne eines Sees#, |wäre|wären|"},
    });

    hintTable[LH_GS_LAB_WALL] = HintText::Exclude({
                       // obscure text
                       Text{"night reveals a #spider by a lake# holding", /*french*/"une #Skulltula sur le mur d'un centre de recherche# a", /*spanish*/"la noche revela una #Skulltula junto a un lago# que otorga", /*italian*/"di notte appare un #ragno lacustre# che ha", /*german*/"in einer nachtaktiven #Spinne eines Sees#, |wäre|wären|"},
    });

    hintTable[LH_GS_LAB_CRATE] = HintText::Exclude({
                       // obscure text
                       Text{"a spider deed underwater in a #lab crate# holds", /*french*/"une #Skulltula dans une boîte au fond d'une cuve d'eau# a", /*spanish*/"una #Skulltula bajo la sumergida caja de un laboratorio# otorga", /*italian*/"un #ragno subacqueo in un laboratorio# ha", /*german*/"in der Spinne einer #versunkenen Kiste#, |wäre|wären|"},
    });

    hintTable[LH_GS_TREE] = HintText::Exclude({
                       // obscure text
                       Text{"night reveals a #spider by a lake high in a tree# holding", /*french*/"une #Skulltula dans un grand arbre du lac# a", /*spanish*/"la noche revela #una Skulltula del lago sobre un árbol# que otorga", /*italian*/"di notte appare un #ragno arboreo lacustre# che ha", /*german*/"in einer nachtaktiven #Spinne eines Sees#, |wäre|wären|"},
    });


    hintTable[GV_GS_BEAN_PATCH] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider buried in a valley# holds", /*french*/"une #Skulltula enterré dans une vallée# a", /*spanish*/"una #Skulltula enterrada en un valle# otorga", /*italian*/"un #ragno sepolto nella valle# nasconde", /*german*/"in einer, #im Tal vergrabenen Spinne#, |wäre|wären|"},
    });

    hintTable[GV_GS_SMALL_BRIDGE] = HintText::Exclude({
                       // obscure text
                       Text{"night in the past reveals a #spider in a valley# holding", /*french*/"une #Skulltula au dessus d'une petite cascade# a", /*spanish*/"la noche del pasado revela una #Skulltula del valle# que otorga", /*italian*/"di notte nel passato appare un #ragno in una valle# con", /*german*/"in einer nachtaktiven #Spinne des Tals#, |wäre|wären|"},
    });

    hintTable[GV_GS_PILLAR] = HintText::Exclude({
                       // obscure text
                       Text{"night in the future reveals a #spider in a valley# holding", /*french*/"une #Skulltula sur une arche de pierre dans une vallée# a", /*spanish*/"la noche del futuro revela una #Skulltula del valle# que otorga", /*italian*/"di notte nel futuro appare un #ragno in una valle# con", /*german*/"in einer nachtaktiven #Spinne des Tals#, |wäre|wären|"},
    });

    hintTable[GV_GS_BEHIND_TENT] = HintText::Exclude({
                       // obscure text
                       Text{"night in the future reveals a #spider in a valley# holding", /*french*/"une #Skulltula derrière une tente# a", /*spanish*/"la noche del futuro revela una #Skulltula del valle# que otorga", /*italian*/"di notte nel futuro appare un #ragno in una valle# con", /*german*/"in einer nachtaktiven #Spinne des Tals#, |wäre|wären|"},
    });


    hintTable[GF_GS_ARCHERY_RANGE] = HintText::Exclude({
                       // obscure text
                       Text{"night reveals a #spider in a fortress# holding", /*french*/"une #Skulltula sur une cible de tir# a", /*spanish*/"la noche revela una #Skulltula de una fortaleza# que otorga", /*italian*/"di notte appare un #ragno in una fortezza# con", /*german*/"in einer nachtaktiven #Spinne einer Festung#, |wäre|wären|"},
    });

    hintTable[GF_GS_TOP_FLOOR] = HintText::Exclude({
                       // obscure text
                       Text{"night reveals a #spider in a fortress# holding", /*french*/"une #Skulltula au sommet d'une forteresse# a", /*spanish*/"la noche revela una #Skulltula de una fortaleza# que otorga", /*italian*/"di notte appare un #ragno in una fortezza# con", /*german*/"in einer nachtaktiven #Spinne einer Festung#, |wäre|wären|"},
    });


    hintTable[COLOSSUS_GS_BEAN_PATCH] = HintText::Exclude({
                       // obscure text
                       Text{"a #spider buried in the desert# holds", /*french*/"une #Skulltula enterrée au pied du colosse# a", /*spanish*/"una #Skulltula enterrada en el desierto# otorga", /*italian*/"un #ragno sepolto nel deserto# nasconde", /*german*/"in einer, #in der Wüste vergrabenen Spinne#, |wäre|wären|"},
    });

    hintTable[COLOSSUS_GS_HILL] = HintText::Exclude({
                       // obscure text
                       Text{"night reveals a #spider deep in the desert# holding", /*french*/"une #Skulltula sur une colline dans le désert# a", /*spanish*/"la noche revela una #Skulltula en las profundidades del desierto# que otorga", /*italian*/"di notte appare un #ragno nel cuore del deserto# con", /*german*/"in einer nachtaktiven #Spinne der Wüste#, |wäre|wären|"},
    });

    hintTable[COLOSSUS_GS_TREE] = HintText::Exclude({
                       // obscure text
                       Text{"night reveals a #spider deep in the desert# holding", /*french*/"une #Skulltula dans un arbre du désert# a", /*spanish*/"la noche revela una #Skulltula en las profundidades del desierto# que otorga", /*italian*/"di notte appare un #ragno nel cuore del deserto# con", /*german*/"in einer nachtaktiven #Spinne der Wüste#, |wäre|wären|"},
    });


    hintTable[KF_SHOP_ITEM_1] = HintText::Exclude({
                       // obscure text
                       Text{"a #child shopkeeper# sells", /*french*/"la #boutique Kokiri# vend", /*spanish*/"un #joven dependiente# vende", /*italian*/"un #commerciante bambino# vende", /*german*/"die Ware eines #jungen Ladenbesitzers#, |wäre|wären|"},
    });

    hintTable[KF_SHOP_ITEM_2] = HintText::Exclude({
                       // obscure text
                       Text{"a #child shopkeeper# sells", /*french*/"la #boutique Kokiri# vend", /*spanish*/"un #joven dependiente# vende", /*italian*/"un #commerciante bambino# vende", /*german*/"die Ware eines #jungen Ladenbesitzers#, |wäre|wären|"},
    });

    hintTable[KF_SHOP_ITEM_3] = HintText::Exclude({
                       // obscure text
                       Text{"a #child shopkeeper# sells", /*french*/"la #boutique Kokiri# vend", /*spanish*/"un #joven dependiente# vende", /*italian*/"un #commerciante bambino# vende", /*german*/"die Ware eines #jungen Ladenbesitzers#, |wäre|wären|"},
    });

    hintTable[KF_SHOP_ITEM_4] = HintText::Exclude({
                       // obscure text
                       Text{"a #child shopkeeper# sells", /*french*/"la #boutique Kokiri# vend", /*spanish*/"un #joven dependiente# vende", /*italian*/"un #commerciante bambino# vende", /*german*/"die Ware eines #jungen Ladenbesitzers#, |wäre|wären|"},
    });

    hintTable[KF_SHOP_ITEM_5] = HintText::Exclude({
                       // obscure text
                       Text{"a #child shopkeeper# sells", /*french*/"la #boutique Kokiri# vend", /*spanish*/"un #joven dependiente# vende", /*italian*/"un #commerciante bambino# vende", /*german*/"die Ware eines #jungen Ladenbesitzers#, |wäre|wären|"},
    });

    hintTable[KF_SHOP_ITEM_6] = HintText::Exclude({
                       // obscure text
                       Text{"a #child shopkeeper# sells", /*french*/"la #boutique Kokiri# vend", /*spanish*/"un #joven dependiente# vende", /*italian*/"un #commerciante bambino# vende", /*german*/"die Ware eines #jungen Ladenbesitzers#, |wäre|wären|"},
    });

    hintTable[KF_SHOP_ITEM_7] = HintText::Exclude({
                       // obscure text
                       Text{"a #child shopkeeper# sells", /*french*/"la #boutique Kokiri# vend", /*spanish*/"un #joven dependiente# vende", /*italian*/"un #commerciante bambino# vende", /*german*/"die Ware eines #jungen Ladenbesitzers#, |wäre|wären|"},
    });

    hintTable[KF_SHOP_ITEM_8] = HintText::Exclude({
                       // obscure text
                       Text{"a #child shopkeeper# sells", /*french*/"la #boutique Kokiri# vend", /*spanish*/"un #joven dependiente# vende", /*italian*/"un #commerciante bambino# vende", /*german*/"die Ware eines #jungen Ladenbesitzers#, |wäre|wären|"},
    });


    hintTable[KAK_POTION_SHOP_ITEM_1] = HintText::Exclude({
                       // obscure text
                       Text{"a #potion seller# offers", /*french*/"l'#apothicaire# vend", /*spanish*/"un #vendedor de pociones# ofrece", /*italian*/"un #farmacista# vende", /*german*/"die Ware eines #Elixierverkäufers#, |wäre|wären|"},
                     }, {},
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", /*french*/"l'#apothicaire de Kakariko# vend", /*spanish*/"la #tienda de pociones de Kakariko# ofrece", /*italian*/"il #negozio di pozioni di Calbarico# offre", /*german*/"die Ware vom #Magie-Laden von Kakariko#, |wäre|wären|"}
    );

    hintTable[KAK_POTION_SHOP_ITEM_2] = HintText::Exclude({
                       // obscure text
                       Text{"a #potion seller# offers", /*french*/"l'#apothicaire# vend", /*spanish*/"un #vendedor de pociones# ofrece", /*italian*/"un #farmacista# vende", /*german*/"die Ware eines #Elixierverkäufers#, |wäre|wären|"},
                     }, {},
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", /*french*/"l'#apothicaire de Kakariko# vend", /*spanish*/"la #tienda de pociones de Kakariko# ofrece", /*italian*/"il #negozio di pozioni di Calbarico# offre", /*german*/"die Ware vom #Magie-Laden von Kakariko#, |wäre|wären|"}
    );

    hintTable[KAK_POTION_SHOP_ITEM_3] = HintText::Exclude({
                       // obscure text
                       Text{"a #potion seller# offers", /*french*/"l'#apothicaire# vend", /*spanish*/"un #vendedor de pociones# ofrece", /*italian*/"un #farmacista# vende", /*german*/"die Ware eines #Elixierverkäufers#, |wäre|wären|"},
                     }, {},
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", /*french*/"l'#apothicaire de Kakariko# vend", /*spanish*/"la #tienda de pociones de Kakariko# ofrece", /*italian*/"il #negozio di pozioni di Calbarico# offre", /*german*/"die Ware vom #Magie-Laden von Kakariko#, |wäre|wären|"}
    );

    hintTable[KAK_POTION_SHOP_ITEM_4] = HintText::Exclude({
                       // obscure text
                       Text{"a #potion seller# offers", /*french*/"l'#apothicaire# vend", /*spanish*/"un #vendedor de pociones# ofrece", /*italian*/"un #farmacista# vende", /*german*/"die Ware eines #Elixierverkäufers#, |wäre|wären|"},
                     }, {},
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", /*french*/"l'#apothicaire de Kakariko# vend", /*spanish*/"la #tienda de pociones de Kakariko# ofrece", /*italian*/"il #negozio di pozioni di Calbarico# offre", /*german*/"die Ware vom #Magie-Laden von Kakariko#, |wäre|wären|"}
    );

    hintTable[KAK_POTION_SHOP_ITEM_5] = HintText::Exclude({
                       // obscure text
                       Text{"a #potion seller# offers", /*french*/"l'#apothicaire# vend", /*spanish*/"un #vendedor de pociones# ofrece", /*italian*/"un #farmacista# vende", /*german*/"die Ware eines #Elixierverkäufers#, |wäre|wären|"},
                     }, {},
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", /*french*/"l'#apothicaire de Kakariko# vend", /*spanish*/"la #tienda de pociones de Kakariko# ofrece", /*italian*/"il #negozio di pozioni di Calbarico# offre", /*german*/"die Ware vom #Magie-Laden von Kakariko#, |wäre|wären|"}
    );

    hintTable[KAK_POTION_SHOP_ITEM_6] = HintText::Exclude({
                       // obscure text
                       Text{"a #potion seller# offers", /*french*/"l'#apothicaire# vend", /*spanish*/"un #vendedor de pociones# ofrece", /*italian*/"un #farmacista# vende", /*german*/"die Ware eines #Elixierverkäufers#, |wäre|wären|"},
                     }, {},
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", /*french*/"l'#apothicaire de Kakariko# vend", /*spanish*/"la #tienda de pociones de Kakariko# ofrece", /*italian*/"il #negozio di pozioni di Calbarico# offre", /*german*/"die Ware vom #Magie-Laden von Kakariko#, |wäre|wären|"}
    );

    hintTable[KAK_POTION_SHOP_ITEM_7] = HintText::Exclude({
                       // obscure text
                       Text{"a #potion seller# offers", /*french*/"l'#apothicaire# vend", /*spanish*/"un #vendedor de pociones# ofrece", /*italian*/"un #farmacista# vende", /*german*/"die Ware eines #Elixierverkäufers#, |wäre|wären|"},
                     }, {},
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", /*french*/"l'#apothicaire de Kakariko# vend", /*spanish*/"la #tienda de pociones de Kakariko# ofrece", /*italian*/"il #negozio di pozioni di Calbarico# offre", /*german*/"die Ware vom #Magie-Laden von Kakariko#, |wäre|wären|"}
    );

    hintTable[KAK_POTION_SHOP_ITEM_8] = HintText::Exclude({
                       // obscure text
                       Text{"a #potion seller# offers", /*french*/"l'#apothicaire# vend", /*spanish*/"un #vendedor de pociones# ofrece", /*italian*/"un #farmacista# vende", /*german*/"die Ware eines #Elixierverkäufers#, |wäre|wären|"},
                     }, {},
                       //clear text
                       Text{"the #Kakariko Potion Shop# offers", /*french*/"l'#apothicaire de Kakariko# vend", /*spanish*/"la #tienda de pociones de Kakariko# ofrece", /*italian*/"il #negozio di pozioni di Calbarico# offre", /*german*/"die Ware vom #Magie-Laden von Kakariko#, |wäre|wären|"}
    );


    hintTable[MARKET_BOMBCHU_SHOP_ITEM_1] = HintText::Exclude({
                       // obscure text
                       Text{"a #Bombchu merchant# sells", /*french*/"le #marchand de missiles# vend", /*spanish*/"un #mercader de bombchus# vende", /*italian*/"un #commerciante di radiomine# vende", /*german*/"die Ware eines #Krabbelminenhändlers#, |wäre|wären|"},
    });

    hintTable[MARKET_BOMBCHU_SHOP_ITEM_2] = HintText::Exclude({
                       // obscure text
                       Text{"a #Bombchu merchant# sells", /*french*/"le #marchand de missiles# vend", /*spanish*/"un #mercader de bombchus# vende", /*italian*/"un #commerciante di radiomine# vende", /*german*/"die Ware eines #Krabbelminenhändlers#, |wäre|wären|"},
    });

    hintTable[MARKET_BOMBCHU_SHOP_ITEM_3] = HintText::Exclude({
                       // obscure text
                       Text{"a #Bombchu merchant# sells", /*french*/"le #marchand de missiles# vend", /*spanish*/"un #mercader de bombchus# vende", /*italian*/"un #commerciante di radiomine# vende", /*german*/"die Ware eines #Krabbelminenhändlers#, |wäre|wären|"},
    });

    hintTable[MARKET_BOMBCHU_SHOP_ITEM_4] = HintText::Exclude({
                       // obscure text
                       Text{"a #Bombchu merchant# sells", /*french*/"le #marchand de missiles# vend", /*spanish*/"un #mercader de bombchus# vende", /*italian*/"un #commerciante di radiomine# vende", /*german*/"die Ware eines #Krabbelminenhändlers#, |wäre|wären|"},
    });

    hintTable[MARKET_BOMBCHU_SHOP_ITEM_5] = HintText::Exclude({
                       // obscure text
                       Text{"a #Bombchu merchant# sells", /*french*/"le #marchand de missiles# vend", /*spanish*/"un #mercader de bombchus# vende", /*italian*/"un #commerciante di radiomine# vende", /*german*/"die Ware eines #Krabbelminenhändlers#, |wäre|wären|"},
    });

    hintTable[MARKET_BOMBCHU_SHOP_ITEM_6] = HintText::Exclude({
                       // obscure text
                       Text{"a #Bombchu merchant# sells", /*french*/"le #marchand de missiles# vend", /*spanish*/"un #mercader de bombchus# vende", /*italian*/"un #commerciante di radiomine# vende", /*german*/"die Ware eines #Krabbelminenhändlers#, |wäre|wären|"},
    });

    hintTable[MARKET_BOMBCHU_SHOP_ITEM_7] = HintText::Exclude({
                       // obscure text
                       Text{"a #Bombchu merchant# sells", /*french*/"le #marchand de missiles# vend", /*spanish*/"un #mercader de bombchus# vende", /*italian*/"un #commerciante di radiomine# vende", /*german*/"die Ware eines #Krabbelminenhändlers#, |wäre|wären|"},
    });

    hintTable[MARKET_BOMBCHU_SHOP_ITEM_8] = HintText::Exclude({
                       // obscure text
                       Text{"a #Bombchu merchant# sells", /*french*/"le #marchand de missiles# vend", /*spanish*/"un #mercader de bombchus# vende", /*italian*/"un #commerciante di radiomine# vende", /*german*/"die Ware eines #Krabbelminenhändlers#, |wäre|wären|"},
    });


    hintTable[MARKET_POTION_SHOP_ITEM_1] = HintText::Exclude({
                       // obscure text
                       Text{"a #potion seller# offers", /*french*/"l'#apothicaire# vend", /*spanish*/"un #vendedor de pociones# ofrece", /*italian*/"un #farmacista# vende", /*german*/"die Ware eines #Elixierverkäufers#, |wäre|wären|"},
                     }, {},
                       //clear text
                       Text{"the #Market Potion Shop# offers", /*french*/"l'#apothicaire dans la place du marché# vend", /*spanish*/"la #tienda de pociones del mercado# ofrece", /*italian*/"il #negozio di pozioni del mercato# offre", /*german*/"die Ware vom #Magie-Laden des Marktplatzes#, |wäre|wären|"}
    );

    hintTable[MARKET_POTION_SHOP_ITEM_2] = HintText::Exclude({
                       // obscure text
                       Text{"a #potion seller# offers", /*french*/"l'#apothicaire# vend", /*spanish*/"un #vendedor de pociones# ofrece", /*italian*/"un #farmacista# vende", /*german*/"die Ware eines #Elixierverkäufers#, |wäre|wären|"},
                     }, {},
                       //clear text
                       Text{"the #Market Potion Shop# offers", /*french*/"l'#apothicaire dans la place du marché# vend", /*spanish*/"la #tienda de pociones del mercado# ofrece", /*italian*/"il #negozio di pozioni del mercato# offre", /*german*/"die Ware vom #Magie-Laden des Marktplatzes#, |wäre|wären|"}
    );

    hintTable[MARKET_POTION_SHOP_ITEM_3] = HintText::Exclude({
                       // obscure text
                       Text{"a #potion seller# offers", /*french*/"l'#apothicaire# vend", /*spanish*/"un #vendedor de pociones# ofrece", /*italian*/"un #farmacista# vende", /*german*/"die Ware eines #Elixierverkäufers#, |wäre|wären|"},
                     }, {},
                       //clear text
                       Text{"the #Market Potion Shop# offers", /*french*/"l'#apothicaire dans la place du marché# vend", /*spanish*/"la #tienda de pociones del mercado# ofrece", /*italian*/"il #negozio di pozioni del mercato# offre", /*german*/"die Ware vom #Magie-Laden des Marktplatzes#, |wäre|wären|"}
    );

    hintTable[MARKET_POTION_SHOP_ITEM_4] = HintText::Exclude({
                       // obscure text
                       Text{"a #potion seller# offers", /*french*/"l'#apothicaire# vend", /*spanish*/"un #vendedor de pociones# ofrece", /*italian*/"un #farmacista# vende", /*german*/"die Ware eines #Elixierverkäufers#, |wäre|wären|"},
                     }, {},
                       //clear text
                       Text{"the #Market Potion Shop# offers", /*french*/"l'#apothicaire dans la place du marché# vend", /*spanish*/"la #tienda de pociones del mercado# ofrece", /*italian*/"il #negozio di pozioni del mercato# offre", /*german*/"die Ware vom #Magie-Laden des Marktplatzes#, |wäre|wären|"}
    );

    hintTable[MARKET_POTION_SHOP_ITEM_5] = HintText::Exclude({
                       // obscure text
                       Text{"a #potion seller# offers", /*french*/"l'#apothicaire# vend", /*spanish*/"un #vendedor de pociones# ofrece", /*italian*/"un #farmacista# vende", /*german*/"die Ware eines #Elixierverkäufers#, |wäre|wären|"},
                     }, {},
                       //clear text
                       Text{"the #Market Potion Shop# offers", /*french*/"l'#apothicaire dans la place du marché# vend", /*spanish*/"la #tienda de pociones del mercado# ofrece", /*italian*/"il #negozio di pozioni del mercato# offre", /*german*/"die Ware vom #Magie-Laden des Marktplatzes#, |wäre|wären|"}
    );

    hintTable[MARKET_POTION_SHOP_ITEM_6] = HintText::Exclude({
                       // obscure text
                       Text{"a #potion seller# offers", /*french*/"l'#apothicaire# vend", /*spanish*/"un #vendedor de pociones# ofrece", /*italian*/"un #farmacista# vende", /*german*/"die Ware eines #Elixierverkäufers#, |wäre|wären|"},
                     }, {},
                       //clear text
                       Text{"the #Market Potion Shop# offers", /*french*/"l'#apothicaire dans la place du marché# vend", /*spanish*/"la #tienda de pociones del mercado# ofrece", /*italian*/"il #negozio di pozioni del mercato# offre", /*german*/"die Ware vom #Magie-Laden des Marktplatzes#, |wäre|wären|"}
    );

    hintTable[MARKET_POTION_SHOP_ITEM_7] = HintText::Exclude({
                       // obscure text
                       Text{"a #potion seller# offers", /*french*/"l'#apothicaire# vend", /*spanish*/"un #vendedor de pociones# ofrece", /*italian*/"un #farmacista# vende", /*german*/"die Ware eines #Elixierverkäufers#, |wäre|wären|"},
                     }, {},
                       //clear text
                       Text{"the #Market Potion Shop# offers", /*french*/"l'#apothicaire dans la place du marché# vend", /*spanish*/"la #tienda de pociones del mercado# ofrece", /*italian*/"il #negozio di pozioni del mercato# offre", /*german*/"die Ware vom #Magie-Laden des Marktplatzes#, |wäre|wären|"}
    );

    hintTable[MARKET_POTION_SHOP_ITEM_8] = HintText::Exclude({
                       // obscure text
                       Text{"a #potion seller# offers", /*french*/"l'#apothicaire# vend", /*spanish*/"un #vendedor de pociones# ofrece", /*italian*/"un #farmacista# vende", /*german*/"die Ware eines #Elixierverkäufers#, |wäre|wären|"},
                     }, {},
                       //clear text
                       Text{"the #Market Potion Shop# offers", /*french*/"l'#apothicaire dans la place du marché# vend", /*spanish*/"la #tienda de pociones del mercado# ofrece", /*italian*/"il #negozio di pozioni del mercato# offre", /*german*/"die Ware vom #Magie-Laden des Marktplatzes#, |wäre|wären|"}
    );


    hintTable[MARKET_BAZAAR_ITEM_1] = HintText::Exclude({
                       // obscure text
                       Text{"the #Market Bazaar# offers", /*french*/"le #bazar de la place du marché# vend", /*spanish*/"el #bazar del mercado# ofrece", /*italian*/"il #bazar del mercato# offre", /*german*/"die Ware des #Basars des Marktplatzes#, |wäre|wären|"},
    });

    hintTable[MARKET_BAZAAR_ITEM_2] = HintText::Exclude({
                       // obscure text
                       Text{"the #Market Bazaar# offers", /*french*/"le #bazar de la place du marché# vend", /*spanish*/"el #bazar del mercado# ofrece", /*italian*/"il #bazar del mercato# offre", /*german*/"die Ware des #Basars des Marktplatzes#, |wäre|wären|"},
    });

    hintTable[MARKET_BAZAAR_ITEM_3] = HintText::Exclude({
                       // obscure text
                       Text{"the #Market Bazaar# offers", /*french*/"le #bazar de la place du marché# vend", /*spanish*/"el #bazar del mercado# ofrece", /*italian*/"il #bazar del mercato# offre", /*german*/"die Ware des #Basars des Marktplatzes#, |wäre|wären|"},
    });

    hintTable[MARKET_BAZAAR_ITEM_4] = HintText::Exclude({
                       // obscure text
                       Text{"the #Market Bazaar# offers", /*french*/"le #bazar de la place du marché# vend", /*spanish*/"el #bazar del mercado# ofrece", /*italian*/"il #bazar del mercato# offre", /*german*/"die Ware des #Basars des Marktplatzes#, |wäre|wären|"},
    });

    hintTable[MARKET_BAZAAR_ITEM_5] = HintText::Exclude({
                       // obscure text
                       Text{"the #Market Bazaar# offers", /*french*/"le #bazar de la place du marché# vend", /*spanish*/"el #bazar del mercado# ofrece", /*italian*/"il #bazar del mercato# offre", /*german*/"die Ware des #Basars des Marktplatzes#, |wäre|wären|"},
    });

    hintTable[MARKET_BAZAAR_ITEM_6] = HintText::Exclude({
                       // obscure text
                       Text{"the #Market Bazaar# offers", /*french*/"le #bazar de la place du marché# vend", /*spanish*/"el #bazar del mercado# ofrece", /*italian*/"il #bazar del mercato# offre", /*german*/"die Ware des #Basars des Marktplatzes#, |wäre|wären|"},
    });

    hintTable[MARKET_BAZAAR_ITEM_7] = HintText::Exclude({
                       // obscure text
                       Text{"the #Market Bazaar# offers", /*french*/"le #bazar de la place du marché# vend", /*spanish*/"el #bazar del mercado# ofrece", /*italian*/"il #bazar del mercato# offre", /*german*/"die Ware des #Basars des Marktplatzes#, |wäre|wären|"},
    });

    hintTable[MARKET_BAZAAR_ITEM_8] = HintText::Exclude({
                       // obscure text
                       Text{"the #Market Bazaar# offers", /*french*/"le #bazar de la place du marché# vend", /*spanish*/"el #bazar del mercado# ofrece", /*italian*/"il #bazar del mercato# offre", /*german*/"die Ware des #Basars des Marktplatzes#, |wäre|wären|"},
    });


    hintTable[KAK_BAZAAR_ITEM_1] = HintText::Exclude({
                       // obscure text
                       Text{"the #Kakariko Bazaar# offers", /*french*/"le #bazar de Kakariko# vend", /*spanish*/"el #bazar de Kakariko# ofrece", /*italian*/"il #bazar di Calbarico# offre", /*german*/"die Ware des #Basars von Kakariko#, |wäre|wären|"},
    });

    hintTable[KAK_BAZAAR_ITEM_2] = HintText::Exclude({
                       // obscure text
                       Text{"the #Kakariko Bazaar# offers", /*french*/"le #bazar de Kakariko# vend", /*spanish*/"el #bazar de Kakariko# ofrece", /*italian*/"il #bazar di Calbarico# offre", /*german*/"die Ware des #Basars von Kakariko#, |wäre|wären|"},
    });

    hintTable[KAK_BAZAAR_ITEM_3] = HintText::Exclude({
                       // obscure text
                       Text{"the #Kakariko Bazaar# offers", /*french*/"le #bazar de Kakariko# vend", /*spanish*/"el #bazar de Kakariko# ofrece", /*italian*/"il #bazar di Calbarico# offre", /*german*/"die Ware des #Basars von Kakariko#, |wäre|wären|"},
    });

    hintTable[KAK_BAZAAR_ITEM_4] = HintText::Exclude({
                       // obscure text
                       Text{"the #Kakariko Bazaar# offers", /*french*/"le #bazar de Kakariko# vend", /*spanish*/"el #bazar de Kakariko# ofrece", /*italian*/"il #bazar di Calbarico# offre", /*german*/"die Ware des #Basars von Kakariko#, |wäre|wären|"},
    });

    hintTable[KAK_BAZAAR_ITEM_5] = HintText::Exclude({
                       // obscure text
                       Text{"the #Kakariko Bazaar# offers", /*french*/"le #bazar de Kakariko# vend", /*spanish*/"el #bazar de Kakariko# ofrece", /*italian*/"il #bazar di Calbarico# offre", /*german*/"die Ware des #Basars von Kakariko#, |wäre|wären|"},
    });

    hintTable[KAK_BAZAAR_ITEM_6] = HintText::Exclude({
                       // obscure text
                       Text{"the #Kakariko Bazaar# offers", /*french*/"le #bazar de Kakariko# vend", /*spanish*/"el #bazar de Kakariko# ofrece", /*italian*/"il #bazar di Calbarico# offre", /*german*/"die Ware des #Basars von Kakariko#, |wäre|wären|"},
    });

    hintTable[KAK_BAZAAR_ITEM_7] = HintText::Exclude({
                       // obscure text
                       Text{"the #Kakariko Bazaar# offers", /*french*/"le #bazar de Kakariko# vend", /*spanish*/"el #bazar de Kakariko# ofrece", /*italian*/"il #bazar di Calbarico# offre", /*german*/"die Ware des #Basars von Kakariko#, |wäre|wären|"},
    });

    hintTable[KAK_BAZAAR_ITEM_8] = HintText::Exclude({
                       // obscure text
                       Text{"the #Kakariko Bazaar# offers", /*french*/"le #bazar de Kakariko# vend", /*spanish*/"el #bazar de Kakariko# ofrece", /*italian*/"il #bazar di Calbarico# offre", /*german*/"die Ware des #Basars von Kakariko#, |wäre|wären|"},
    });


    hintTable[ZD_SHOP_ITEM_1] = HintText::Exclude({
                       // obscure text
                       Text{"a #Zora shopkeeper# sells", /*french*/"la #boutique Zora# vend", /*spanish*/"el #dependiente Zora# vende", /*italian*/"un #commerciante Zora# vende", /*german*/"die Ware eines #Ladenbesitzers der Zora#, |wäre|wären|"},
    });

    hintTable[ZD_SHOP_ITEM_2] = HintText::Exclude({
                       // obscure text
                       Text{"a #Zora shopkeeper# sells", /*french*/"la #boutique Zora# vend", /*spanish*/"el #dependiente Zora# vende", /*italian*/"un #commerciante Zora# vende", /*german*/"die Ware eines #Ladenbesitzers der Zora#, |wäre|wären|"},
    });

    hintTable[ZD_SHOP_ITEM_3] = HintText::Exclude({
                       // obscure text
                       Text{"a #Zora shopkeeper# sells", /*french*/"la #boutique Zora# vend", /*spanish*/"el #dependiente Zora# vende", /*italian*/"un #commerciante Zora# vende", /*german*/"die Ware eines #Ladenbesitzers der Zora#, |wäre|wären|"},
    });

    hintTable[ZD_SHOP_ITEM_4] = HintText::Exclude({
                       // obscure text
                       Text{"a #Zora shopkeeper# sells", /*french*/"la #boutique Zora# vend", /*spanish*/"el #dependiente Zora# vende", /*italian*/"un #commerciante Zora# vende", /*german*/"die Ware eines #Ladenbesitzers der Zora#, |wäre|wären|"},
    });

    hintTable[ZD_SHOP_ITEM_5] = HintText::Exclude({
                       // obscure text
                       Text{"a #Zora shopkeeper# sells", /*french*/"la #boutique Zora# vend", /*spanish*/"el #dependiente Zora# vende", /*italian*/"un #commerciante Zora# vende", /*german*/"die Ware eines #Ladenbesitzers der Zora#, |wäre|wären|"},
    });

    hintTable[ZD_SHOP_ITEM_6] = HintText::Exclude({
                       // obscure text
                       Text{"a #Zora shopkeeper# sells", /*french*/"la #boutique Zora# vend", /*spanish*/"el #dependiente Zora# vende", /*italian*/"un #commerciante Zora# vende", /*german*/"die Ware eines #Ladenbesitzers der Zora#, |wäre|wären|"},
    });

    hintTable[ZD_SHOP_ITEM_7] = HintText::Exclude({
                       // obscure text
                       Text{"a #Zora shopkeeper# sells", /*french*/"la #boutique Zora# vend", /*spanish*/"el #dependiente Zora# vende", /*italian*/"un #commerciante Zora# vende", /*german*/"die Ware eines #Ladenbesitzers der Zora#, |wäre|wären|"},
    });

    hintTable[ZD_SHOP_ITEM_8] = HintText::Exclude({
                       // obscure text
                       Text{"a #Zora shopkeeper# sells", /*french*/"la #boutique Zora# vend", /*spanish*/"el #dependiente Zora# vende", /*italian*/"un #commerciante Zora# vende", /*german*/"die Ware eines #Ladenbesitzers der Zora#, |wäre|wären|"},
    });


    hintTable[GC_SHOP_ITEM_1] = HintText::Exclude({
                       // obscure text
                       Text{"a #Goron shopkeeper# sells", /*french*/"la #boutique Goron# vend", /*spanish*/"el #dependiente Goron# vende", /*italian*/"un #commerciante Goron# vende", /*german*/"die Ware eines #Ladenbesitzers der Goronen#, |wäre|wären|"},
    });

    hintTable[GC_SHOP_ITEM_2] = HintText::Exclude({
                       // obscure text
                       Text{"a #Goron shopkeeper# sells", /*french*/"la #boutique Goron# vend", /*spanish*/"el #dependiente Goron# vende", /*italian*/"un #commerciante Goron# vende", /*german*/"die Ware eines #Ladenbesitzers der Goronen#, |wäre|wären|"},
    });

    hintTable[GC_SHOP_ITEM_3] = HintText::Exclude({
                       // obscure text
                       Text{"a #Goron shopkeeper# sells", /*french*/"la #boutique Goron# vend", /*spanish*/"el #dependiente Goron# vende", /*italian*/"un #commerciante Goron# vende", /*german*/"die Ware eines #Ladenbesitzers der Goronen#, |wäre|wären|"},
    });

    hintTable[GC_SHOP_ITEM_4] = HintText::Exclude({
                       // obscure text
                       Text{"a #Goron shopkeeper# sells", /*french*/"la #boutique Goron# vend", /*spanish*/"el #dependiente Goron# vende", /*italian*/"un #commerciante Goron# vende", /*german*/"die Ware eines #Ladenbesitzers der Goronen#, |wäre|wären|"},
    });

    hintTable[GC_SHOP_ITEM_5] = HintText::Exclude({
                       // obscure text
                       Text{"a #Goron shopkeeper# sells", /*french*/"la #boutique Goron# vend", /*spanish*/"el #dependiente Goron# vende", /*italian*/"un #commerciante Goron# vende", /*german*/"die Ware eines #Ladenbesitzers der Goronen#, |wäre|wären|"},
    });

    hintTable[GC_SHOP_ITEM_6] = HintText::Exclude({
                       // obscure text
                       Text{"a #Goron shopkeeper# sells", /*french*/"la #boutique Goron# vend", /*spanish*/"el #dependiente Goron# vende", /*italian*/"un #commerciante Goron# vende", /*german*/"die Ware eines #Ladenbesitzers der Goronen#, |wäre|wären|"},
    });

    hintTable[GC_SHOP_ITEM_7] = HintText::Exclude({
                       // obscure text
                       Text{"a #Goron shopkeeper# sells", /*french*/"la #boutique Goron# vend", /*spanish*/"el #dependiente Goron# vende", /*italian*/"un #commerciante Goron# vende", /*german*/"die Ware eines #Ladenbesitzers der Goronen#, |wäre|wären|"},
    });

    hintTable[GC_SHOP_ITEM_8] = HintText::Exclude({
                       // obscure text
                       Text{"a #Goron shopkeeper# sells", /*french*/"la #boutique Goron# vend", /*spanish*/"el #dependiente Goron# vende", /*italian*/"un #commerciante Goron# vende", /*german*/"die Ware eines #Ladenbesitzers der Goronen#, |wäre|wären|"},
    });


    hintTable[HF_DEKU_SCRUB_GROTTO] = HintText::Exclude({
                       // obscure text
                       Text{"a lonely #scrub in a hole# sells", /*french*/"la #peste Mojo dans une grotte de la plaine# vend", /*spanish*/"un #singular deku bajo un hoyo# de la llanura vende", /*italian*/"un #cespuglio solitario in una grotta# vende", /*german*/"die Ware, des #einsamen Deku-Händlers eines Erdlochs#, |wäre|wären|"},
    });

    hintTable[LLR_DEKU_SCRUB_GROTTO_LEFT] = HintText::Exclude({
                       // obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"le #trio de peste Mojo à la ferme# vend", /*spanish*/"un #trío de dekus# de una granja venden", /*italian*/"un #trio di cespugli fattori# vende", /*german*/"die Ware eines #Deku-Händler-Trios#, |wäre|wären|"},
    });

    hintTable[LLR_DEKU_SCRUB_GROTTO_RIGHT] = HintText::Exclude({
                       // obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"le #trio de peste Mojo à la ferme# vend", /*spanish*/"un #trío de dekus# de una granja venden", /*italian*/"un #trio di cespugli fattori# vende", /*german*/"die Ware eines #Deku-Händler-Trios#, |wäre|wären|"},
    });

    hintTable[LLR_DEKU_SCRUB_GROTTO_CENTER] = HintText::Exclude({
                       // obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"le #trio de peste Mojo à la ferme# vend", /*spanish*/"un #trío de dekus# de una granja venden", /*italian*/"un #trio di cespugli fattori# vende", /*german*/"die Ware eines #Deku-Händler-Trios#, |wäre|wären|"},
    });


    hintTable[LW_DEKU_SCRUB_NEAR_DEKU_THEATER_RIGHT] = HintText::Exclude({
                       // obscure text
                       Text{"a pair of #scrubs in the woods# sells", /*french*/"le #duo de peste Mojo près du théâtre# vend", /*spanish*/"un par de #dekus del bosque# venden", /*italian*/"un #cespuglio vicino a un teatro# vende", /*german*/"die Ware, eines #Deku-Händler-Duos der Wälder#, |wäre|wären|"},
    });

    hintTable[LW_DEKU_SCRUB_NEAR_DEKU_THEATER_LEFT] = HintText::Exclude({
                       // obscure text
                       Text{"a pair of #scrubs in the woods# sells", /*french*/"le #duo de peste Mojo près du théâtre# vend", /*spanish*/"un par de #dekus del bosque# venden", /*italian*/"un #cespuglio vicino a un teatro# vende", /*german*/"die Ware, eines #Deku-Händler-Duos der Wälder#, |wäre|wären|"},
    });

    hintTable[LW_DEKU_SCRUB_NEAR_BRIDGE] = HintText::Exclude({
                       // obscure text
                       Text{"a #scrub by a bridge# sells", /*french*/"la #peste Mojo près du pont dans les bois# vend", /*spanish*/"un #deku bajo un puente# del bosque venden", /*italian*/"un #cespuglio vicino a un ponte# vende", /*german*/"die Ware, des #Deku-Händlers nahe einer Brücke#, |wäre|wären|"},
    });
            hintTable[LW_IN_BOULDER_BLUE_RUPEE] = HintText::Exclude({
                       // obscure text
                       Text{"EN: LW_IN_BOULDER_BLUE_RUPEE HINT", /*french*/"FR: LW_IN_BOULDER_BLUE_RUPEE HINT", /*spanish*/"ES: LW_IN_BOULDER_BLUE_RUPEE HINT", /*italian*/"IT: LW_IN_BOULDER_BLUE_RUPEE HINT", /*german*/"DE: LW_IN_BOULDER_BLUE_RUPEE HINT"},
    });

    hintTable[LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_1] = HintText::Exclude({
                       // obscure text
                       Text{"EN: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_1 HINT", /*french*/"FR: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_1 HINT", /*spanish*/"ES: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_1 HINT", /*italian*/"IT: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_1 HINT", /*german*/"DE: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_1 HINT"},
    });

    hintTable[LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_2] = HintText::Exclude({
                       // obscure text
                       Text{"EN: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_2 HINT", /*french*/"FR: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_2 HINT", /*spanish*/"ES: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_2 HINT", /*italian*/"IT: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_2 HINT", /*german*/"DE: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_2 HINT"},
    });
    hintTable[LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_3] = HintText::Exclude({
                       // obscure text
                       Text{"EN: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_3 HINT", /*french*/"FR: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_3 HINT", /*spanish*/"ES: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_3 HINT", /*italian*/"IT: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_3 HINT", /*german*/"DE: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_3 HINT"},
    });
    hintTable[LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_4] = HintText::Exclude({
                       // obscure text
                       Text{"EN: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_4 HINT", /*french*/"FR: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_4 HINT", /*spanish*/"ES: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_4 HINT", /*italian*/"IT: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_4 HINT", /*german*/"DE: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_4 HINT"},
    });
    hintTable[LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_5] = HintText::Exclude({
                       // obscure text
                       Text{"EN: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_5 HINT", /*french*/"FR: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_5 HINT", /*spanish*/"ES: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_5 HINT", /*italian*/"IT: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_5 HINT", /*german*/"DE: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_5 HINT"},
    });
    hintTable[LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_6] = HintText::Exclude({
                       // obscure text
                       Text{"EN: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_6 HINT", /*french*/"FR: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_6 HINT", /*spanish*/"ES: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_6 HINT", /*italian*/"IT: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_6 HINT", /*german*/"DE: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_6 HINT"},
    });
    hintTable[LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_7] = HintText::Exclude({
                       // obscure text
                       Text{"EN: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_7 HINT", /*french*/"FR: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_7 HINT", /*spanish*/"ES: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_7 HINT", /*italian*/"IT: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_7 HINT", /*german*/"DE: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_7 HINT"},
    });
    hintTable[LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_8] = HintText::Exclude({
                       // obscure text
                       Text{"EN: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_8 HINT", /*french*/"FR: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_8 HINT", /*spanish*/"ES: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_8 HINT", /*italian*/"IT: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_8 HINT", /*german*/"DE: LW_IN_WATER_NEAR_ZR_SHORTCUT_GREEN_RUPEE_8 HINT"},
    });


    hintTable[LW_DEKU_SCRUB_GROTTO_REAR] = HintText::Exclude({
                       // obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"le #duo de peste Mojo dans les sous-bois# vend", /*spanish*/"un #par de dekus subterráneos# del bosque venden", /*italian*/"una #coppia di cespugli nascosti nel bosco# vende", /*german*/"die Ware, des #Deku-Händler-Duos eines Erdlochs#, |wäre|wären|"},
    });

    hintTable[LW_DEKU_SCRUB_GROTTO_FRONT] = HintText::Exclude({
                       // obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"le #duo de peste Mojo dans les sous-bois# vend", /*spanish*/"un #par de dekus subterráneos# del bosque venden", /*italian*/"una #coppia di cespugli nascosti nel bosco# vende", /*german*/"die Ware, des #Deku-Händler-Duos eines Erdlochs#, |wäre|wären|"},
    });


    hintTable[SFM_DEKU_SCRUB_GROTTO_REAR] = HintText::Exclude({
                       // obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"le #duo de peste Mojo au cœur du sanctuaire sylvestre# vend", /*spanish*/"un #par de dekus subterráneos# de la pradera sagrada venden", /*italian*/"una #coppia di cespugli nel cuore della foresta# vende", /*german*/"die Ware, des #Deku-Händler-Duos eines Erdlochs#, |wäre|wären|"},
    });

    hintTable[SFM_DEKU_SCRUB_GROTTO_FRONT] = HintText::Exclude({
                       // obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"le #duo de peste Mojo au cœur du sanctuaire sylvestre# vend", /*spanish*/"un #par de dekus subterráneos# de la pradera sagrada venden", /*italian*/"una #coppia di cespugli nel cuore della foresta# vende", /*german*/"die Ware, des #Deku-Händler-Duos eines Erdlochs#, |wäre|wären|"},
    });


    hintTable[GC_DEKU_SCRUB_GROTTO_LEFT] = HintText::Exclude({
                       // obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"le #trio de peste Mojo dans le village Goron# vend", /*spanish*/"un #trío de dekus# de la Ciudad Goron venden", /*italian*/"un #trio di cespugli fra i Goron# vende", /*german*/"die Ware eines #Deku-Händler-Trios#, |wäre|wären|"},
    });

    hintTable[GC_DEKU_SCRUB_GROTTO_RIGHT] = HintText::Exclude({
                       // obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"le #trio de peste Mojo dans le village Goron# vend", /*spanish*/"un #trío de dekus# de la Ciudad Goron venden", /*italian*/"un #trio di cespugli fra i Goron# vende", /*german*/"die Ware eines #Deku-Händler-Trios#, |wäre|wären|"},
    });

    hintTable[GC_DEKU_SCRUB_GROTTO_CENTER] = HintText::Exclude({
                       // obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"le #trio de peste Mojo dans le village Goron# vend", /*spanish*/"un #trío de dekus# de la Ciudad Goron venden", /*italian*/"un #trio di cespugli fra i Goron# vende", /*german*/"die Ware eines #Deku-Händler-Trios#, |wäre|wären|"},
    });


    hintTable[DMC_DEKU_SCRUB_GROTTO_LEFT] = HintText::Exclude({
                       // obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"le #trio de peste Mojo dans le volcan# vend", /*spanish*/"un #trío de dekus# del volcán venden", /*italian*/"un #trio di cespugli sotto un macigno# vende", /*german*/"die Ware eines #Deku-Händler-Trios#, |wäre|wären|"},
    });

    hintTable[DMC_DEKU_SCRUB_GROTTO_RIGHT] = HintText::Exclude({
                       // obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"le #trio de peste Mojo dans le volcan# vend", /*spanish*/"un #trío de dekus# del volcán venden", /*italian*/"un #trio di cespugli sotto un macigno# vende", /*german*/"die Ware eines #Deku-Händler-Trios#, |wäre|wären|"},
    });

    hintTable[DMC_DEKU_SCRUB_GROTTO_CENTER] = HintText::Exclude({
                       // obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"le #trio de peste Mojo dans le volcan# vend", /*spanish*/"un #trío de dekus# del volcán venden", /*italian*/"un #trio di cespugli sotto un macigno# vende", /*german*/"die Ware eines #Deku-Händler-Trios#, |wäre|wären|"},
    });


    hintTable[ZR_DEKU_SCRUB_GROTTO_REAR] = HintText::Exclude({
                       // obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"le #duo de peste Mojo près du fleuve# vend", /*spanish*/"un #par de dekus subterráneos# del río venden", /*italian*/"una #coppia di cespugli vicino al fiume# vende", /*german*/"die Ware, des #Deku-Händler-Duos eines Erdlochs#, |wäre|wären|"},
    });

    hintTable[ZR_DEKU_SCRUB_GROTTO_FRONT] = HintText::Exclude({
                       // obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"le #duo de peste Mojo près du fleuve# vend", /*spanish*/"un #par de dekus subterráneos# del río venden", /*italian*/"una #coppia di cespugli vicino al fiume# vende", /*german*/"die Ware, des #Deku-Händler-Duos eines Erdlochs#, |wäre|wären|"},
    });

        hintTable[ZR_WATERFALL_RED_RUPEE_1] = HintText::Exclude({
                       // obscure text
                       Text{"EN: ZR_WATERFALL_RED_RUPEE_1 HINT", /*french*/"FR: ZR_WATERFALL_RED_RUPEE_1 HINT", /*spanish*/"ES: ZR_WATERFALL_RED_RUPEE_1 HINT", /*italian*/"IT: ZR_WATERFALL_RED_RUPEE_1 HINT", /*german*/"DE: ZR_WATERFALL_RED_RUPEE_1 HINT"},
    });
            hintTable[ZR_WATERFALL_RED_RUPEE_2] = HintText::Exclude({
                       // obscure text
                       Text{"EN: ZR_WATERFALL_RED_RUPEE_2 HINT", /*french*/"FR: ZR_WATERFALL_RED_RUPEE_2 HINT", /*spanish*/"ES: ZR_WATERFALL_RED_RUPEE_2 HINT", /*italian*/"IT: ZR_WATERFALL_RED_RUPEE_2 HINT", /*german*/"DE: ZR_WATERFALL_RED_RUPEE_2 HINT"},
    });

            hintTable[ZR_WATERFALL_RED_RUPEE_3] = HintText::Exclude({
                       // obscure text
                       Text{"EN: ZR_WATERFALL_RED_RUPEE_3 HINT", /*french*/"FR: ZR_WATERFALL_RED_RUPEE_3 HINT", /*spanish*/"ES: ZR_WATERFALL_RED_RUPEE_3 HINT", /*italian*/"IT: ZR_WATERFALL_RED_RUPEE_3 HINT", /*german*/"DE: ZR_WATERFALL_RED_RUPEE_3 HINT"},
    });

            hintTable[ZR_WATERFALL_RED_RUPEE_4] = HintText::Exclude({
                       // obscure text
                       Text{"EN: ZR_WATERFALL_RED_RUPEE_4 HINT", /*french*/"FR: ZR_WATERFALL_RED_RUPEE_4 HINT", /*spanish*/"ES: ZR_WATERFALL_RED_RUPEE_4 HINT", /*italian*/"IT: ZR_WATERFALL_RED_RUPEE_4 HINT", /*german*/"DE: ZR_WATERFALL_RED_RUPEE_4 HINT"},
    });



    hintTable[LH_DEKU_SCRUB_GROTTO_LEFT] = HintText::Exclude({
                       // obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"le #trio de peste Mojo près du lac# vend", /*spanish*/"un #trío de dekus# del lago venden", /*italian*/"un #trio di cespugli sotto una lapide# vende", /*german*/"die Ware eines #Deku-Händler-Trios#, |wäre|wären|"},
    });

    hintTable[LH_DEKU_SCRUB_GROTTO_RIGHT] = HintText::Exclude({
                       // obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"le #trio de peste Mojo près du lac# vend", /*spanish*/"un #trío de dekus# del lago venden", /*italian*/"un #trio di cespugli sotto una lapide# vende", /*german*/"die Ware eines #Deku-Händler-Trios#, |wäre|wären|"},
    });

    hintTable[LH_DEKU_SCRUB_GROTTO_CENTER] = HintText::Exclude({
                       // obscure text
                       Text{"a #trio of scrubs# sells", /*french*/"le #trio de peste Mojo près du lac# vend", /*spanish*/"un #trío de dekus# del lago venden", /*italian*/"un #trio di cespugli sotto una lapide# vende", /*german*/"die Ware eines #Deku-Händler-Trios#, |wäre|wären|"},
    });


    hintTable[GV_DEKU_SCRUB_GROTTO_REAR] = HintText::Exclude({
                       // obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"le #duo de peste Mojo près de la vallée# vend", /*spanish*/"un #par de dekus subterráneos# del valle venden", /*italian*/"una #coppia di cespugli da canyon# vende", /*german*/"die Ware, des #Deku-Händler-Duos eines Erdlochs#, |wäre|wären|"},
    });

    hintTable[GV_DEKU_SCRUB_GROTTO_FRONT] = HintText::Exclude({
                       // obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"le #duo de peste Mojo près de la vallée# vend", /*spanish*/"un #par de dekus subterráneos# del valle venden", /*italian*/"una #coppia di cespugli da canyon# vende", /*german*/"die Ware, des #Deku-Händler-Duos eines Erdlochs#, |wäre|wären|"},
    });

        hintTable[GV_OCTOROCK_GROTTO_GREEN_RUPEE_1] = HintText::Exclude({
                       // obscure text
                       Text{"EN: GV_OCTOROCK_GROTTO_GREEN_RUPEE_1 Hint", /*french*/"FR: GV_OCTOROCK_GROTTO_GREEN_RUPEE_1 Hint", /*spanish*/"ES: GV_OCTOROCK_GROTTO_GREEN_RUPEE_1 Hint", /*italian*/"IT: GV_OCTOROCK_GROTTO_GREEN_RUPEE_1 Hint", /*german*/"DE: GV_OCTOROCK_GROTTO_GREEN_RUPEE_1 Hint"},
                     }
    );
        hintTable[GV_OCTOROCK_GROTTO_GREEN_RUPEE_2] = HintText::Exclude({
                       // obscure text
                       Text{"EN: GV_OCTOROCK_GROTTO_GREEN_RUPEE_2 Hint", /*french*/"FR: GV_OCTOROCK_GROTTO_GREEN_RUPEE_2 Hint", /*spanish*/"ES: GV_OCTOROCK_GROTTO_GREEN_RUPEE_2 Hint", /*italian*/"IT: GV_OCTOROCK_GROTTO_GREEN_RUPEE_2 Hint", /*german*/"DE: GV_OCTOROCK_GROTTO_GREEN_RUPEE_2 Hint"},
                     }
    );
        hintTable[GV_OCTOROCK_GROTTO_GREEN_RUPEE_3] = HintText::Exclude({
                       // obscure text
                       Text{"EN: GV_OCTOROCK_GROTTO_GREEN_RUPEE_3 Hint", /*french*/"FR: GV_OCTOROCK_GROTTO_GREEN_RUPEE_3 Hint", /*spanish*/"ES: GV_OCTOROCK_GROTTO_GREEN_RUPEE_3 Hint", /*italian*/"IT: GV_OCTOROCK_GROTTO_GREEN_RUPEE_3 Hint", /*german*/"DE: GV_OCTOROCK_GROTTO_GREEN_RUPEE_3 Hint"},
                     }
    );
        hintTable[GV_OCTOROCK_GROTTO_GREEN_RUPEE_4] = HintText::Exclude({
                       // obscure text
                       Text{"EN: GV_OCTOROCK_GROTTO_GREEN_RUPEE_4 Hint", /*french*/"FR: GV_OCTOROCK_GROTTO_GREEN_RUPEE_4 Hint", /*spanish*/"ES: GV_OCTOROCK_GROTTO_GREEN_RUPEE_4 Hint", /*italian*/"IT: GV_OCTOROCK_GROTTO_GREEN_RUPEE_4 Hint", /*german*/"DE: GV_OCTOROCK_GROTTO_GREEN_RUPEE_4 Hint"},
                     }
    );
        hintTable[GV_OCTOROCK_GROTTO_BLUE_RUPEE_1] = HintText::Exclude({
                       // obscure text
                       Text{"EN: GV_OCTOROCK_GROTTO_BLUE_RUPEE_1 Hint", /*french*/"FR: GV_OCTOROCK_GROTTO_BLUE_RUPEE_1 Hint", /*spanish*/"ES: GV_OCTOROCK_GROTTO_BLUE_RUPEE_1 Hint", /*italian*/"IT: GV_OCTOROCK_GROTTO_BLUE_RUPEE_1 Hint", /*german*/"DE: GV_OCTOROCK_GROTTO_BLUE_RUPEE_1 Hint"},
                     }
    );
        hintTable[GV_OCTOROCK_GROTTO_BLUE_RUPEE_2] = HintText::Exclude({
                       // obscure text
                       Text{"EN: GV_OCTOROCK_GROTTO_BLUE_RUPEE_2 Hint", /*french*/"FR: GV_OCTOROCK_GROTTO_BLUE_RUPEE_2 Hint", /*spanish*/"ES: GV_OCTOROCK_GROTTO_BLUE_RUPEE_2 Hint", /*italian*/"IT: GV_OCTOROCK_GROTTO_BLUE_RUPEE_2 Hint", /*german*/"DE: GV_OCTOROCK_GROTTO_BLUE_RUPEE_2 Hint"},
                     }
    );
        hintTable[GV_OCTOROCK_GROTTO_BLUE_RUPEE_3] = HintText::Exclude({
                       // obscure text
                       Text{"EN: GV_OCTOROCK_GROTTO_BLUE_RUPEE_3 Hint", /*french*/"FR: GV_OCTOROCK_GROTTO_BLUE_RUPEE_3 Hint", /*spanish*/"ES: GV_OCTOROCK_GROTTO_BLUE_RUPEE_3 Hint", /*italian*/"IT: GV_OCTOROCK_GROTTO_BLUE_RUPEE_3 Hint", /*german*/"DE: GV_OCTOROCK_GROTTO_BLUE_RUPEE_3 Hint"},
                     }
    );
        hintTable[GV_OCTOROCK_GROTTO_RED_RUPEE] = HintText::Exclude({
                       // obscure text
                       Text{"EN: GV_OCTOROCK_GROTTO_RED_RUPEE Hint", /*french*/"FR: GV_OCTOROCK_GROTTO_RED_RUPEE Hint", /*spanish*/"ES: GV_OCTOROCK_GROTTO_RED_RUPEE Hint", /*italian*/"IT: GV_OCTOROCK_GROTTO_RED_RUPEE Hint", /*german*/"DE: GV_OCTOROCK_GROTTO_RED_RUPEE Hint"},
                     }
    );


    hintTable[COLOSSUS_DEKU_SCRUB_GROTTO_FRONT] = HintText::Exclude({
                       // obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"le #duo de peste Mojo dans le désert# vend", /*spanish*/"un #par de dekus subterráneos# del desierto venden", /*italian*/"una #coppia di cespugli sotto la sabbia# vende", /*german*/"die Ware, des #Deku-Händler-Duos eines Erdlochs#, |wäre|wären|"},
    });

    hintTable[COLOSSUS_DEKU_SCRUB_GROTTO_REAR] = HintText::Exclude({
                       // obscure text
                       Text{"a #scrub underground duo# sells", /*french*/"le #duo de peste Mojo dans le désert# vend", /*spanish*/"un #par de dekus subterráneos# del desierto venden", /*italian*/"una #coppia di cespugli sotto la sabbia# vende", /*german*/"die Ware, des #Deku-Händler-Duos eines Erdlochs#, |wäre|wären|"},
    });


    hintTable[LLR_STABLES_LEFT_COW] = HintText::Exclude({
                       // obscure text
                       Text{"a #cow in a stable# gifts", /*french*/"la #vache dans l'étable# donne", /*spanish*/"una #vaca del establo# brinda", /*italian*/"una #mucca nella stalla# regala", /*german*/"die Milch einer #Kuh, im Stall der Farm#, |wäre|wären|"},
    });

    hintTable[LLR_STABLES_RIGHT_COW] = HintText::Exclude({
                       // obscure text
                       Text{"a #cow in a stable# gifts", /*french*/"la #vache dans l'étable# donne", /*spanish*/"una #vaca del establo# brinda", /*italian*/"una #mucca nella stalla# regala", /*german*/"die Milch einer #Kuh, im Stall der Farm#, |wäre|wären|"},
    });

    hintTable[LLR_TOWER_RIGHT_COW] = HintText::Exclude({
                       // obscure text
                       Text{"a #cow in a ranch silo# gifts", /*french*/"la #vache dans le silo de la ferme# donne", /*spanish*/"una #vaca del granero# brinda", /*italian*/"una #mucca in un granaio# regala", /*german*/"die Milch einer #Kuh, im Silo der Farm#, |wäre|wären|"},
    });

    hintTable[LLR_TOWER_LEFT_COW] = HintText::Exclude({
                       // obscure text
                       Text{"a #cow in a ranch silo# gifts", /*french*/"la #vache dans le silo de la ferme# donne", /*spanish*/"una #vaca del granero# brinda", /*italian*/"una #mucca in un granaio# regala", /*german*/"die Milch einer #Kuh, im Silo der Farm#, |wäre|wären|"},
    });

    hintTable[KAK_IMPAS_HOUSE_COW] = HintText::Exclude({
                       // obscure text
                       Text{"a #cow imprisoned in a house# protects", /*french*/"la #vache en cage# donne", /*spanish*/"una #vaca enjaulada de una casa# brinda", /*italian*/"una #mucca in gabbia# regala", /*german*/"die Milch, der in einem #Haus eingesperrten Kuh#, |wäre|wären|"},
    });

    hintTable[DMT_COW_GROTTO_COW] = HintText::Exclude({
                       // obscure text
                       Text{"a #cow in a luxurious hole# offers", /*french*/"la #vache dans une grotte luxueuse# donne", /*spanish*/"una #vaca de un lujoso hoyo# brinda", /*italian*/"una #mucca in una grotta lussuosa# regala", /*german*/"die Milch einer #wohlhabenden Kuh#, |wäre|wären|"},
    });
}
// clang-format on
