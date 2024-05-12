#include "hint_list.hpp"
#include "custom_messages.hpp"

#include <array>

using namespace CustomMessages;

// Big thanks to Lioncache, Gabyelnuevo, Danius88, and Charade for their translations!

// Text is {english, french, spanish, italian, german}

// there are special characters that are read for certain in game commands:
// ^ is a box break
// & is a new line
// @ will print the player name
// surrounding text with '#' will make it a different color
// - OoT Randomizer

// '%d' indicates a number will be placed there.
// '$' at the end of an item name indicates that it's plural.
// '|' separates singular and plural form.
// '{}' indicate sound effect IDs in hex.

std::array<HintText, KEY_ENUM_MAX> hintTable;
// clang-format off
void HintTable_Init() {
    /*--------------------------
    |       GENERAL TEXT       |
    ---------------------------*/
    hintTable[NONE]            = HintText::Exclude({Text{"No Hint"}});
    hintTable[PREFIX]          = HintText::Exclude({Text{"They say that ",              /*french*/"Selon moi, ",                  /*spanish*/"Según dicen, ",                  /*italian*/"Ho sentito dire che ",         /*german*/"Man erzählt sich, "}});
    hintTable[WAY_OF_THE_HERO] = HintText::Exclude({Text{" is on the way of the hero.", /*french*/" est sur le chemin du héros.", /*spanish*/" conduce a la senda del héroe.", /*italian*/" è sul cammino dell'eroe.",    /*german*/" verlaufe der Weg des Helden."}});
    hintTable[PLUNDERING]      = HintText::Exclude({Text{"plundering ",                 /*french*/"explorer ",                    /*spanish*/"inspeccionar ",                  /*italian*/"saccheggiare ",                /*german*/"es sei eine törichte Wahl, "}});
    hintTable[FOOLISH]         = HintText::Exclude({Text{" is a foolish choice.",       /*french*/" est futile.",                 /*spanish*/" no es una sabia decisión.",     /*italian*/" è una perdita di tempo.",     /*german*/" nach Schätzen zu suchen."}});
    hintTable[CAN_BE_FOUND_AT] = HintText::Exclude({Text{"can be found at",             /*french*/"se trouve dans",               /*spanish*/"aguarda en",                     /*italian*/"si |trova|trovano| presso",    /*german*/"|sei|seien|"}});
    hintTable[HOARDS]          = HintText::Exclude({Text{"hoards",                      /*french*/"recèle",                       /*spanish*/"acapara",                        /*italian*/"nasconde",                     /*german*/"|befände sich|befänden sich|"}});

    HintTable_Init_Item();
    HintTable_Init_Exclude_Overworld();
    HintTable_Init_Exclude_Dungeon();

    /*--------------------------
    |     ALWAYS HINT TEXT     |
    ---------------------------*/

    hintTable[ZR_FROGS_OCARINA_GAME] = HintText::Always({
                       // obscure text
                       Text{"an #amphibian feast# yields",               /*french*/"un #festin d'amphibiens# donne", /*spanish*/"una #fiesta anfibia# brinda",       /*italian*/"un #banchetto di anfibi# fornisce",                  /*german*/"beim #amphibischen Festmahl#, |wäre|wären|"},
                       Text{"the #croaking choir's magnum opus# awards", /*french*/"la #chorale coassante# donne",   /*spanish*/"un #coro maestro de ancas# premia", /*italian*/"l'#opera magna del coro gracidante# è premiata con", /*german*/"das #Meisterwerk des quakenden Chors#, |wäre|wären|"},
                       Text{"the #froggy finale# yields",                /*french*/"la #finale amphibienne# donne",  /*spanish*/"el #gran final batracio# brinda",   /*italian*/"il #gran finale dei batraci# fornisce",              /*german*/"beim #froschigen Finale#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"the final reward from the #Frogs of Zora's River# is", /*french*/"la dernière récompense des #grenouilles du fleuve zora# est", /*spanish*/"la recompensa final de las #ranas del Río Zora# premia", /*italian*/"la ricompensa finale delle #rane del fiume Zora# è", /*german*/"die finale Belohnung der #Frösche des Zora-Flusses#, |wäre|wären|"}
    );

    hintTable[KF_LINKS_HOUSE_COW] = HintText::Always({
                       // obscure text
                       Text{"the #bovine bounty of a horseback hustle# gifts", /*french*/"le cadeau #qui découle d'une réussite équestre# est", /*spanish*/"la #recompensa bovina de un paseo a caballo# brinda", /*italian*/"la #ricompensa bovina di un'impresa equestre# dona", /*german*/"die #Rinderprämie des eiligen Rittes#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"#Malon's obstacle course# leads to", /*french*/"la #course à obstacle de Malon# amène à", /*spanish*/"la #carrera de obstáculos de Malon# brinda", /*italian*/"se vinci la #corsa ad ostacoli di Malon# ti |arriva|arrivano| a casa", /*german*/"bei #Malons Pferderennen#, |wäre|wären|"}
    );

    /*--------------------------
    |    SOMETIMES HINT TEXT   |
    ---------------------------*/

    hintTable[SONG_FROM_OCARINA_OF_TIME] = HintText::Sometimes({
                       // obscure text
                       Text{"the #Ocarina of Time# teaches", /*french*/"l'#ocarina du temps# est accompagné par", /*spanish*/"la #Ocarina del Tiempo# enseña", /*italian*/"l'#Ocarina del Tempo# insegna", /*german*/"das, von der #Okarina der Zeit gelehrte Lied#, |wäre|wären|"},
    });

    hintTable[SONG_FROM_COMPOSERS_GRAVE] = HintText::Sometimes({
                       // obscure text
                       Text{"#ReDead in the Composers' Grave# guard", /*french*/"les #Remorts du tombeau des compositeurs# protègent", /*spanish*/"los #ReDeads del Panteón Real# guardan",  /*italian*/"gli #zombie nella tomba della famiglia reale# proteggono", /*german*/"#nahe Zombies im Königsgrab#, |wäre|wären|"},
                       Text{"the #Composer Brothers wrote#",          /*french*/"le #trésor des compositeurs# est",                    /*spanish*/"los #hermanos compositores escribieron#", /*italian*/"i #fratelli Mortaldi scrissero#",                          /*german*/"das, von den #Gebrüder Brahmstein komponierte Lied#, |wäre|wären|"},
    });

    hintTable[SHEIK_IN_FOREST] = HintText::Sometimes({
                       // obscure text
                       Text{"#in a meadow# Sheik teaches", /*french*/"Sheik confiera, #dans une clairière#,", /*spanish*/"#en la pradera sagrada# Sheik enseña", /*italian*/"#in una radura# Sheik insegna", /*german*/"das von Shiek, #auf einer Lichtung gelehrte Lied#, |wäre|wären|"},
    });

    hintTable[SHEIK_AT_TEMPLE] = HintText::Sometimes({
                       // obscure text
                       Text{"Sheik waits at a #monument to time# to teach", /*french*/"Sheik confiera, #au pied de l'épée légendaire#,", /*spanish*/"Sheik espera en el #momumento del tiempo# para enseñar", /*italian*/"Sheik aspetta in un #tempio del tempo# per insegnare", /*german*/"das von Shiek, #an einem zeitlichen Denkmal gelehrte Lied#, |wäre|wären|"},
    });

    hintTable[SHEIK_IN_CRATER] = HintText::Sometimes({
                       // obscure text
                       Text{"the #crater's melody# is", /*french*/"Sheik confiera, #entouré de lave#,", /*spanish*/"la #melodía del cráter# otorga", /*italian*/"la #melodia del cratere# è", /*german*/"die #Melodie des Kraters# |wäre|wären|"},
    });

    hintTable[SHEIK_IN_ICE_CAVERN] = HintText::Sometimes({
                       // obscure text
                       Text{"the #frozen cavern# echoes with", /*french*/"Sheik confiera, #dans une caverne étoilée#,", /*spanish*/"en la #caverna de hielo# retumban los ecos de", /*italian*/"nella #caverna ghiacciata# |riecheggia|riecheggiano|", /*german*/"das #Echo der gefrorenen Höhlen#, |wäre|wären|"},
    });

    hintTable[SHEIK_IN_KAKARIKO] = HintText::Sometimes({
                       // obscure text
                       Text{"a #ravaged village# mourns with", /*french*/"Sheik confirera, #au cœur d'un village ravagé#,", /*spanish*/"un #arrasado pueblo# llora", /*italian*/"un #villaggio devastato# piange con", /*german*/"das #Trauern des verwüsteten Dorfes#, |wäre|wären|"},
    });

    hintTable[SHEIK_AT_COLOSSUS] = HintText::Sometimes({
                       // obscure text
                       Text{"a hero ventures #beyond the wasteland# to learn", /*french*/"Sheik confiera, #au bout d'un chemin sableux#,", /*spanish*/"el héroe que se adentre #más allá del desierto# aprenderá", /*italian*/"un eroe si avventurerà #oltre il deserto# per imparare", /*german*/"das, #fürs Durchqueren der Einöde gelehrte Lied#, |wäre|wären|"},
    });


    hintTable[MARKET_10_BIG_POES] = HintText::Sometimes({
                       // obscure text
                       Text{"#ghost hunters# will be rewarded with", /*french*/"#les chasseurs de fantômes# sont récompensés avec", /*spanish*/"los #cazafantasmas# son premiados con", /*italian*/"gli #acchiappafantasmi# saranno ricompensati con", /*german*/"das Kopfgeld der #Geisterjäger#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"catching #Big Poes# leads to", /*french*/"#d'attraper des fantômes# donne", /*spanish*/"hacerte con #Grandes Poes# conduce a", /*italian*/"chi cattura #Grandi Poo# viene ripagato con", /*german*/"bei #gefangenen Nachtschwärmern#, |wäre|wären|"}
    );

    hintTable[DEKU_THEATER_SKULL_MASK] = HintText::Sometimes({
                       // obscure text
                       Text{"the #Skull Mask# yields", /*french*/"le #masque de mort# donne", /*spanish*/"la #máscara de calavera# otorga", /*italian*/"la #maschera teschio# procura", /*german*/"bei einer #knochigen Vorführung#, |wäre|wären|"},
    });

    hintTable[DEKU_THEATER_MASK_OF_TRUTH] = HintText::Sometimes({
                       // obscure text
                       Text{"showing a #truthful eye to the crowd# rewards", /*french*/"montrer #l'oeil de vérité à la foule# donne", /*spanish*/"#mostrarle el ojo verdadero# a una multitud brinda", /*italian*/"#mostrare la verità a una grande folla# viene ricompensato con", /*german*/"bei einer #wissensträchtigen Präsentation#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"the #Mask of Truth# yields", /*french*/"le #masque de vérité# donne", /*spanish*/"la #máscara de la verdad# premia", /*italian*/"la #maschera della verità# procura", /*german*/"die Belohnung der #Maske des Wissens#, |wäre|wären|"}
    );

    hintTable[HF_OCARINA_OF_TIME_ITEM] = HintText::Sometimes({
                       // obscure text
                       Text{"the #treasure thrown by Princess Zelda# is", /*french*/"le trésor #laissé par la princesse# est", /*spanish*/"el #tesoro arrojado por la Princesa Zelda# se trata de", /*italian*/"il #tesoro lanciato dalla Principessa Zelda# è", /*german*/"#Prinzessin Zeldas geworfener Schatz#, |wäre|wären|"},
    });

    hintTable[DMT_TRADE_BROKEN_SWORD] = HintText::Sometimes({
                       // obscure text
                       Text{"a #blinded Biggoron# entrusts", /*french*/"un #Grogoron aveuglé# confie", /*spanish*/"un #miope Biggoron# otorga", /*italian*/"un #Grande Goron accecato# consegna", /*german*/"bei einem #erblindeten Goronen#, |wäre|wären|"},
    });

    hintTable[DMT_TRADE_EYEDROPS] = HintText::Sometimes({
                       // obscure text
                       Text{"while you wait, #Biggoron# gives", /*french*/"pendant que tu attends, #Grogoron# donne", /*spanish*/"#Biggoron# está a la espera de otorgar", /*italian*/"#Grande Goron# paga il suo oculista con", /*german*/"#Biggorons# Entschädigung fürs Warten, |wäre|wären|"},
    });

    hintTable[DMT_TRADE_CLAIM_CHECK] = HintText::Sometimes({
                       // obscure text
                       Text{"#Biggoron# crafts", /*french*/"#Grogoron# fabrique", /*spanish*/"#Biggoron# forja", /*italian*/"#Grande Goron# forgia", /*german*/"#Biggorons# Meisterwerk, |wäre|wären|"},
    });

    hintTable[KAK_50_GOLD_SKULLTULA_REWARD] = HintText::Sometimes({
                       // obscure text
                       Text{"#50 bug badges# rewards",           /*french*/"#50 écussons# donnent",             /*spanish*/"#50 medallas de insectos# otorgan", /*italian*/"#50 spille d'insetto# sono premiate con", /*german*/"die Entschädigung für #50 Insekten-Abzeichen#, |wäre|wären|"},
                       Text{"#50 spider souls# yields",          /*french*/"#50 âmes# donnent",                 /*spanish*/"#50 almas de araña# otorgan",       /*italian*/"#50 anime di ragno# forniscono",          /*german*/"der Lohn für #50 Spinnenseelen#, |wäre|wären|"},
                       Text{"#50 auriferous arachnids# lead to", /*french*/"#50 arachnides aurifères# donnent", /*spanish*/"#50 arácnidos auríferos# otorgan",  /*italian*/"#50 artropodi aurei# forniscono",         /*german*/"die Bezahlung für #50 goldhaltige Arachniden#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"slaying #50 Gold Skulltulas# reveals", /*french*/"détruire #50 Skulltulas d'or# donne", /*spanish*/"exterminar #50 skulltulas doradas# revela", /*italian*/"eliminare #50 Aracnule d'oro# rivela", /*german*/"die Belohnung, fürs Zerstören von #50 goldenen Skulltulas#, |wäre|wären|"}
    );

    hintTable[KAK_40_GOLD_SKULLTULA_REWARD] = HintText::Sometimes({
                       // obscure text
                       Text{"#40 bug badges# rewards",           /*french*/"#40 écussons# donnent",             /*spanish*/"#40 medallas de insectos# otorgan", /*italian*/"#40 spille d'insetto# sono premiate con", /*german*/"die Entschädigung für #40 Insekten-Abzeichen#, |wäre|wären|"},
                       Text{"#40 spider souls# yields",          /*french*/"#40 âmes# donnent",                 /*spanish*/"#40 almas de araña# otorgan",       /*italian*/"#40 anime di ragno# forniscono",          /*german*/"der Lohn für #40 Spinnenseelen#, |wäre|wären|"},
                       Text{"#40 auriferous arachnids# lead to", /*french*/"#40 arachnides aurifères# donnent", /*spanish*/"#40 arácnidos auríferos# otorgan",  /*italian*/"#40 artropodi aurei# forniscono",         /*german*/"die Bezahlung für #40 goldhaltige Arachniden#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"slaying #40 Gold Skulltulas# reveals", /*french*/"détruire #40 Skulltulas d'or# donne", /*spanish*/"exterminar #40 skulltulas doradas# revela", /*italian*/"eliminare #40 Aracnule d'oro# rivela", /*german*/"die Belohnung, fürs Zerstören von #40 goldenen Skulltulas#, |wäre|wären|"}
    );

    hintTable[KAK_30_GOLD_SKULLTULA_REWARD] = HintText::Sometimes({
                       // obscure text
                       Text{"#30 bug badges# rewards",           /*french*/"#30 écussons# donnent",             /*spanish*/"#30 medallas de insectos# otorgan", /*italian*/"#30 spille d'insetto# sono premiate con", /*german*/"die Entschädigung für #30 Insekten-Abzeichen#, |wäre|wären|"},
                       Text{"#30 spider souls# yields",          /*french*/"#30 âmes# donnent",                 /*spanish*/"#30 almas de araña# otorgan",       /*italian*/"#30 anime di ragno# forniscono",          /*german*/"der Lohn für #30 Spinnenseelen#, |wäre|wären|"},
                       Text{"#30 auriferous arachnids# lead to", /*french*/"#30 arachnides aurifères# donnent", /*spanish*/"#30 arácnidos auríferos# otorgan",  /*italian*/"#30 artropodi aurei# forniscono",         /*german*/"die Bezahlung für #30 goldhaltige Arachniden#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"slaying #30 Gold Skulltulas# reveals", /*french*/"détruire #30 Skulltulas d'or# donne", /*spanish*/"exterminar #30 skulltulas doradas# revela", /*italian*/"eliminare #30 Aracnule d'oro# rivela", /*german*/"die Belohnung, fürs Zerstören von #30 goldenen Skulltulas#, |wäre|wären|"}
    );

    hintTable[KAK_20_GOLD_SKULLTULA_REWARD] = HintText::Sometimes({
                       // obscure text
                       Text{"#20 bug badges# rewards",           /*french*/"#20 écussons# donnent",             /*spanish*/"#20 medallas de insectos# otorgan", /*italian*/"#20 spille d'insetto# sono premiate con", /*german*/"die Entschädigung für #20 Insekten-Abzeichen#, |wäre|wären|"},
                       Text{"#20 spider souls# yields",          /*french*/"#20 âmes# donnent",                 /*spanish*/"#20 almas de araña# otorgan",       /*italian*/"#20 anime di ragno# forniscono",          /*german*/"der Lohn für #20 Spinnenseelen#, |wäre|wären|"},
                       Text{"#20 auriferous arachnids# lead to", /*french*/"#20 arachnides aurifères# donnent", /*spanish*/"#20 arácnidos auríferos# otorgan",  /*italian*/"#20 artropodi aurei# forniscono",         /*german*/"die Bezahlung für #20 goldhaltige Arachniden#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"slaying #20 Gold Skulltulas# reveals", /*french*/"détruire #20 Skulltulas d'or# donne", /*spanish*/"exterminar #20 skulltulas doradas# revela", /*italian*/"eliminare #20 Aracnule d'oro# rivela", /*german*/"die Belohnung, fürs Zerstören von #20 goldenen Skulltulas#, |wäre|wären|"}
    );

    hintTable[KAK_ANJU_AS_CHILD] = HintText::Sometimes({
                       // obscure text
                       Text{"#wrangling roosters# rewards", /*french*/"#plumer des poulets# donne", /*spanish*/"#atrapar a las gallinas# premia",   /*italian*/"#accalappiare galline# procura", /*german*/"bei einer #Hahnrangelei#, |wäre|wären|"},
                       Text{"#chucking chickens# gifts",    /*french*/"#lancer des poulets# donne", /*spanish*/"#reunir a unos emplumados# premia", /*italian*/"#lanciare pollame# procura",     /*german*/"nach einer #Huhneinzäunung#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"#collecting cuccos# rewards", /*french*/"#rapporter les Cocottes# donne", /*spanish*/"#hacerte con todos los cucos# premia", /*italian*/"#ritrovare coccò# procura", /*german*/"Anjus Belohnung fürs #Einfangen ihrer Hühner#, |wäre|wären|"}
    );

    hintTable[KAK_TRADE_POCKET_CUCCO] = HintText::Sometimes({
                       // obscure text
                       Text{"an adult's #happy Cucco# awards", /*french*/"un adulte avec une #poulette joyeuse# obtient", /*spanish*/"un #alegre cuco# en la madurez otorga", /*italian*/"un adulto con un #coccò felice# otterrà", /*german*/"ein Geschenk #glücklicher Hühner#, |wäre|wären|"},
    });

    hintTable[KAK_TRADE_ODD_MUSHROOM] = HintText::Sometimes({
                       // obscure text
                       Text{"the #potion shop lady# entrusts", /*french*/"la #gribiche du magasin de potion# confie", /*spanish*/"la #señora de la tienda de pociones# otorga", /*italian*/"la #vecchietta del negozio di pozioni# consegna", /*german*/"#Omas Allerlei#, |wäre|wären|"},
    });

    hintTable[GC_DARUNIAS_JOY] = HintText::Sometimes({
                       // obscure text
                       Text{"a #groovin' goron# gifts", /*french*/"#le Goron joyeux# donne", /*spanish*/"#un goron marchoso# otorga", /*italian*/"un #Goron scatenato# regala", /*german*/"bei #groovenden Goronen#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"#Darunia's dance# leads to", /*french*/"#la dance de Darunia# donne", /*spanish*/"#el baile de Darunia# conduce a", /*italian*/"#il ballo di Darunia# fornisce", /*german*/"#Darunias# Gastgeschenk für eine #Tanzstunde#, |wäre|wären|"}
    );

    hintTable[LW_SKULL_KID] = HintText::Sometimes({
                       // obscure text
                       Text{"the #Skull Kid# grants", /*french*/"le #Skull Kid# donne", /*spanish*/"#Skull Kid# otorga", /*italian*/"il #bimbo perduto# consegna", /*german*/"#Horror-Kids# Dank für eine #Musikstunde#, |wäre|wären|"},
    });

    hintTable[LW_TRADE_COJIRO] = HintText::Sometimes({
                       // obscure text
                       Text{"returning a #special Cucco# awards", /*french*/"ramener une #poulette précieuse# donne", /*spanish*/"quien devuelva un #cuco especial# encontrará", /*italian*/"se restituisci un #coccò speciale# al suo proprietario riceverai", /*german*/"der Lohn fürs Überbringen eines #besonderen Huhns#, |wäre|wären|"},
    });

    hintTable[LW_TRADE_ODD_POULTICE] = HintText::Sometimes({
                       // obscure text
                       Text{"a #Kokiri girl in the woods# leaves", /*french*/"la #fillette Kokiri dans les bois# laisse", /*spanish*/"una #chica kokiri del bosque# otorga", /*italian*/"una #ragazza Kokiri nel bosco# baratta", /*german*/"die Tauschware eines #Kokiri-Mädchens der Wälder#, |wäre|wären|"},
    });

    hintTable[LH_SUN] = HintText::Sometimes({
                       // obscure text
                       Text{"staring into #the sun# grants", /*french*/"regarder #le soleil# donne", /*spanish*/"#mirar al sol# revela", /*italian*/"#guardare il sole# rivela", /*german*/"ein #Blick in die Sonne#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"shooting #the sun# grants", /*french*/"tirer une flèche dans #sur le soleil# donne", /*spanish*/"#disparar al sol# revela", /*italian*/"scoccare #una freccia verso il sole# rivela", /*german*/"ein #sonniger Schuss#, |wäre|wären|"}
    );

    hintTable[LH_TRADE_FROG] = HintText::Sometimes({
                       // obscure text
                       Text{"#Lake Hylia's scientist# hurriedly entrusts", /*french*/"le #scientifique du lac# confie rapidement", /*spanish*/"el #científico del Lago Hylia# otorga con prisa", /*italian*/"#lo scienziato del Lago Hylia# produce", /*german*/"die Tauschware des #Forschers am Hylia-See#, |wäre|wären|"},
    });

    hintTable[MARKET_TREASURE_CHEST_GAME_REWARD] = HintText::Sometimes({
                       // obscure text
                       Text{"#gambling# grants",               /*french*/"#parier# donne",                   /*spanish*/"#los juegos de azar# revelan",            /*italian*/"se #giochi d'azzardo# puoi vincere",   /*german*/"#Glücksspiel zahle sich aus#, denn es |wäre|wären|"},
                       Text{"there is a #1/32 chance# to win", /*french*/"être #le gagnant parmi 32# donne", /*spanish*/"hay una #probabilidad de 1/32# de ganar", /*italian*/"c'è #1 possibilità su 32# di vincere", /*german*/"eine #1/32stel Erfolgsquote#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"the #treasure chest game# grants", /*french*/"la #chasse aux trésors# donne", /*spanish*/"#el Cofre del Tesoro# premia", /*italian*/"il premio della #sala della fortuna# è", /*german*/"im #letzten Raum# der Truhenlotterie, |wäre|wären|"}
    );

    hintTable[MARKET_TREASURE_CHEST_GAME_ITEM_1] = HintText::Sometimes({
                       // obscure text
                       Text{"#gambling once# grants",                    /*french*/"#parier une fois# donne",                        /*spanish*/"#apostar solo una vez# revelará",             /*italian*/"#scommettere una volta# fa vincere",        /*german*/"ein #einmaliger Gewinn# beim Glücksspiel, |wäre|wären|"},
                       Text{"the #first or second game chest# contains", /*french*/"le #premier ou deuxième coffre à jeu# contient", /*spanish*/"#el primer o segundo cofre del azar# revela", /*italian*/"#il primo o il secondo# forziere contiene", /*german*/"in der #ersten oder zweiten Spieltruhe#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"the #first locked room# in the chest game contains", /*french*/"la #première salle# de la chasse aux trésors contient", /*spanish*/"#en la primera sala del Cofre del Tesoro# aguarda", /*italian*/"nella sala della fortuna la #prima stanza chiusa# nasconde", /*german*/"im #ersten Raum# der Truhenlotterie, |wäre|wären|"}
    );

    hintTable[MARKET_TREASURE_CHEST_GAME_ITEM_2] = HintText::Sometimes({
                       // obscure text
                       Text{"#gambling twice# grants",                   /*french*/"#parier deux fois# donne",                          /*spanish*/"#apostar dos veces# revelará",               /*italian*/"#scommettere due volte# fa vincere",       /*german*/"ein #zweifacher Gewinn# beim Glücksspiel, |wäre|wären|"},
                       Text{"the #third or fourth game chest# contains", /*french*/"le #troisième ou quatrième coffre à jeu# contient", /*spanish*/"#el tercer o cuarto cofre del azar# revela", /*italian*/"#il terzo o il quarto# forziere contiene", /*german*/"in der #dritten oder vierten Spieltruhe#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"the #second locked room# in the chest game contains", /*french*/"la #deuxième salle# de la chasse aux trésors contient", /*spanish*/"#en la segunda sala del Cofre del Tesoro# aguarda", /*italian*/"nella sala della fortuna la #seconda stanza chiusa# nasconde", /*german*/"im #zweiten Raum# der Truhenlotterie, |wäre|wären|"}
    );

    hintTable[MARKET_TREASURE_CHEST_GAME_ITEM_3] = HintText::Sometimes({
                       // obscure text
                       Text{"#gambling 3 times# grants",                /*french*/"#parier trois fois# donne",                       /*spanish*/"#apostar tres veces# revelará",             /*italian*/"#scommettere tre volte# fa vincere",       /*german*/"ein #dreifacher Gewinn# beim Glücksspiel, |wäre|wären|"},
                       Text{"the #fifth or sixth game chest# contains", /*french*/"le #cinquième ou sixième coffre à jeu# contient", /*spanish*/"#el quinto o sexto cofre del azar# revela", /*italian*/"#il quinto o il sesto# forziere contiene", /*german*/"in der #fünften oder sechsten Spieltruhe#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"the #third locked room# in the chest game contains", /*french*/"la #troisième salle# de la chasse aux trésors contient", /*spanish*/"#en la tercera sala del Cofre del Tesoro# aguarda", /*italian*/"nella sala della fortuna la #terza stanza chiusa# nasconde", /*german*/"im #dritten Raum# der Truhenlotterie, |wäre|wären|"}
    );

    hintTable[MARKET_TREASURE_CHEST_GAME_ITEM_4] = HintText::Sometimes({
                       // obscure text
                       Text{"#gambling 4 times# grants",                   /*french*/"#parier quatre fois# donne",                      /*spanish*/"#apostar cuatro veces# revelará",             /*italian*/"#scommettere quattro volte# fa vincere",    /*german*/"ein #vierfacher Gewinn# beim Glücksspiel, |wäre|wären|"},
                       Text{"the #seventh or eighth game chest# contains", /*french*/"le #septième ou huitième coffre à jeu# contient", /*spanish*/"#el séptimo u octavo cofre del azar# revela", /*italian*/"#il settimo o l'ottavo# forziere contiene", /*german*/"in der #siebten oder achten Spieltruhe#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"the #fourth locked room# in the chest game contains", /*french*/"la #quatrième salle# de la chasse aux trésors contient", /*spanish*/"#en la cuarta sala del Cofre del Tesoro# aguarda", /*italian*/"nella sala della fortuna la #quarta stanza chiusa# nasconde", /*german*/"im #vierten Raum# der Truhenlotterie, |wäre|wären|"}
    );

    hintTable[MARKET_TREASURE_CHEST_GAME_ITEM_5] = HintText::Sometimes({
                       // obscure text
                       Text{"#gambling 5 times# grants",                /*french*/"#parier cinq fois# donne",                       /*spanish*/"#apostar cinco veces# revelará",             /*italian*/"#scommettere cinque volte# fa vincere",   /*german*/"ein #fünffacher Gewinn# beim Glücksspiel, |wäre|wären|"},
                       Text{"the #ninth or tenth game chest# contains", /*french*/"le #neuvième ou dixième coffre à jeu# contient", /*spanish*/"#el noveno o décimo cofre del azar# revela", /*italian*/"#il nono o il decimo# forziere contiene", /*german*/"in der #neunten oder zehnten Spieltruhe#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"the #fifth locked room# in the chest game contains", /*french*/"la #cinquième salle# de la chasse aux trésors contient", /*spanish*/"#en la quinta sala del Cofre del Tesoro# aguarda", /*italian*/"nella sala della fortuna la #quinta stanza chiusa# nasconde", /*german*/"im #fünften Raum# der Truhenlotterie, |wäre|wären|"}
    );

    hintTable[GF_HBA_1500_POINTS] = HintText::Sometimes({
                       // obscure text
                       Text{"mastery of #horseback archery# grants", /*french*/"maîtriser l'#archerie équestre# donne", /*spanish*/"dominar el #tiro con arco a caballo# premia con", /*italian*/"se stravinci al #tiro con l'arco a cavallo# riceverai", /*german*/"eine Meisterleistung beim #berittenen Bogenschießen#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"scoring 1500 in #horseback archery# grants", /*french*/"obtenir 1500 points dans l'#archerie équestre# donne", /*spanish*/"conseguir 1500 puntos en el #tiro con arco a caballo# premia", /*italian*/"se totalizzi almeno 1500 punti al #tiro con l'arco a cavallo# riceverai", /*german*/"1.500 Punkte beim #berittenen Bogenschießen#, |wäre|wären|"}
    );

    hintTable[GRAVEYARD_HEART_PIECE_GRAVE_CHEST] = HintText::Sometimes({
                       // obscure text
                       Text{"playing #Sun's Song# in a grave spawns", /*french*/"jouer le #chant du soleil# dans un tombeau donne", /*spanish*/"#tocar la Canción del Sol# en una cripta conduce a", /*italian*/"suonare il #Canto del sole# in una tomba fa apparire", /*german*/"in einem Grabe die #Hymne der Sonne# zu spielen, |wäre|wären|"},
    });

    hintTable[GC_MAZE_LEFT_CHEST] = HintText::Sometimes({
                       // obscure text
                       Text{"in #Goron City# the hammer unlocks", /*french*/"dans le #village Goron#, le marteau donne accès à", /*spanish*/"en la #Ciudad Goron# el martillo desbloquea", /*italian*/"nella #città dei Goron# il martello sblocca", /*german*/"hinter #braunen Felsen# Goronias, |wäre|wären|"},
    });

    hintTable[GV_CHEST] = HintText::Sometimes({
                       // obscure text
                       Text{"in #Gerudo Valley# the hammer unlocks", /*french*/"dans la #vallée Gerudo#, le marteau donne accès à", /*spanish*/"en el #Valle Gerudo# el martillo desbloquea", /*italian*/"nella #valle Gerudo# il martello sblocca", /*german*/"hinter #braunen Felsen# des Gerudotals, |wäre|wären|"},
    });

    hintTable[GV_TRADE_SAW] = HintText::Sometimes({
                       // obscure text
                       Text{"the #boss of the carpenters# leaves", /*french*/"le #patron des ouvriers# laisse", /*spanish*/"el #capataz de los carpinteros# otorga", /*italian*/"il #capo dei carpentieri# ha", /*german*/"die Tauschware des #Chefs der Zimmerleute#, |wäre|wären|"},
    });

    hintTable[GV_COW] = HintText::Sometimes({
                       // obscure text
                       Text{"a #cow in Gerudo Valley# gifts", /*french*/"la #vache de la vallée Gerudo# donne", /*spanish*/"una #vaca del Valle Gerudo# brinda", /*italian*/"una #mucca nella valle Gerudo# regala", /*german*/"die Milch einer #Kuh des Gerudotals#, |wäre|wären|"},
    });

    hintTable[HC_GS_STORMS_GROTTO] = HintText::Sometimes({
                       // obscure text
                       Text{"a #spider behind a muddy wall# in a grotto holds", /*french*/"l'#araignée derrière un mur de boue# dans une grotte donne", /*spanish*/"una #Skulltula tras la agrietada pared# de una cueva otorga", /*italian*/"un #ragno dietro la parete friabile di una grotta# si nasconde con", /*german*/"in einer #Spinne, hinter der brüchigen Wand# eines Erdlochs, |wäre|wären|"},
    });

    hintTable[HF_GS_COW_GROTTO] = HintText::Sometimes({
                       // obscure text
                       Text{"a #spider behind webs# in a grotto holds", /*french*/"l'#araignée derrière une toile# dans une grotte donne", /*spanish*/"una #Skulltula tras la telaraña# de una cueva otorga", /*italian*/"un #ragno dietro una ragnatela# in una grotta si nasconde con", /*german*/"in einer #Spinne, hinter den Spinnenweben# eines Erdlochs, |wäre|wären|"},
    });

    hintTable[HF_COW_GROTTO_COW] = HintText::Sometimes({
                       // obscure text
                       Text{"the #cobwebbed cow# gifts", /*french*/"la #vache prisonnière d'araignées# donne", /*spanish*/"una #vaca tras una telaraña# brinda", /*italian*/"un #ungulato nella prigione di un araneide# dona", /*german*/"die Milch, einer #von Spinnenweben bedeckten Kuh#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"a #cow behind webs# in a grotto gifts", /*french*/"la #vache derrière les toiles# d'une grotte donne", /*spanish*/"una #vaca tras la telaraña# de una cueva brinda", /*italian*/"una #mucca dietro una ragnatela# in una grotta regala", /*german*/"die Milch einer #Kuh, hinter den Spinnenweben# eines Erdlochs, |wäre|wären|"}
    );

    hintTable[ZF_GS_HIDDEN_CAVE] = HintText::Sometimes({
                       // obscure text
                       Text{"a spider high #above the icy waters# holds", /*french*/"l'araignée #en haut des eaux glacées# donne", /*spanish*/"una Skulltula en lo #alto de las congeladas aguas# otorga", /*italian*/"un ragno #sopra acque congelate# nasconde", /*german*/"in einer Spinne, #über eisigen Gewässern#, |wäre|wären|"},
    });

    hintTable[WASTELAND_CHEST] = HintText::Sometimes({
                       // obscure text
                       Text{"#deep in the wasteland# is",         /*french*/"#loin dans le désert# gît",                     /*spanish*/"en lo #profundo del desierto encantado# yace", /*italian*/"#nel profondo del deserto stregato# si |cela|celano|", /*german*/"#tief in der Einöde#, |wäre|wären|"},
                       Text{"beneath #the sands#, flames reveal", /*french*/"#sous le désert#, les flammes font apparaître", /*spanish*/"tras las #arenas# unas llamas revelan",        /*italian*/"#sotto la sabbia#, delle fiamme rivelano",             /*german*/"ein flammendes #Geheimnis des Sandes#, |wäre|wären|"},
    });

    hintTable[WASTELAND_GS] = HintText::Sometimes({
                       // obscure text
                       Text{"a #spider in the wasteland# holds", /*french*/"#l'araignée dans le désert# donne", /*spanish*/"una #Skulltula del desierto encantado# otorga", /*italian*/"un #ragno nel deserto stregato# tiene", /*german*/"in einer #Spinne der Einöde#, |wäre|wären|"},
    });

    hintTable[GRAVEYARD_COMPOSERS_GRAVE_CHEST] = HintText::Sometimes({
                       // obscure text
                       Text{"#flames in the Composers' Grave# reveal", /*french*/"#les flammes dans le tombeau des compositeurs# cachent", /*spanish*/"#las llamas del Panteón Real# revelan", /*italian*/"nella #tomba della famiglia reale, le fiamme# rivelano", /*german*/"ein #flammendes Geheimnis des Königsgrabes#, |wäre|wären|"},
                       Text{"the #Composer Brothers hid#",             /*french*/"#les Frères compositeurs on caché#",                     /*spanish*/"los #hermanos compositores esconden#",  /*italian*/"i #fratelli Mortaldi# chiusero in un forziere",          /*german*/"im Versteck der #Gebrüder Brahmstein#, |wäre|wären|"},
    });

    hintTable[ZF_BOTTOM_FREESTANDING_POH] = HintText::Sometimes({
                       // obscure text
                       Text{"#under the icy waters# lies", /*french*/"#sous les eaux glacées# se cache", /*spanish*/"#bajo las congeladas aguas# yace", /*italian*/"sotto le #acque ghiacciate# puoi trovare", /*german*/"#unter eisigen Gewässern#, |wäre|wären|"},
    });

    hintTable[GC_POT_FREESTANDING_POH] = HintText::Sometimes({
                       // obscure text
                       Text{"spinning #Goron pottery# contains", /*french*/"la #potterie Goron# contient", /*spanish*/"una #cerámica goron# contiene", /*italian*/"della #ceramica Goron# roteante contiene", /*german*/"in rotierender, #goronischer Keramik#, |wäre|wären|"},
    });

    hintTable[ZD_KING_ZORA_THAWED] = HintText::Sometimes({
                       // obscure text
                       Text{"a #defrosted dignitary# gifts", /*french*/"le #monarque libéré# donne", /*spanish*/"una #liberación monárquica# brinda", /*italian*/"un #pesce scongelato# fornisce", /*german*/"der Dank eines #enteisten Monarchen#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"unfreezing #King Zora# grants", /*french*/"dégeler # le Roi Zora# donne", /*spanish*/"#descongelar al Rey Zora# conduce a", /*italian*/"chi #scongela Re Zora# riceverà", /*german*/"die Belohnung fürs Auftauen von #König Zora#, |wäre|wären|"}
    );

    hintTable[ZD_TRADE_PRESCRIPTION] = HintText::Sometimes({
                       // obscure text
                       Text{"#King Zora# hurriedly entrusts", /*french*/"le #roi Zora# confie rapidement", /*spanish*/"el #Rey Zora# otorga con prisa", /*italian*/"#Re Zora# affida frettolosamente", /*german*/"#König Zoras# Tauschware, |wäre|wären|"},
    });

    hintTable[DMC_DEKU_SCRUB] = HintText::Sometimes({
                       // obscure text
                       Text{"a single #scrub in the crater# sells", /*french*/"la #peste Mojo dans le cratère# vend", /*spanish*/"un solitario #deku del cráter# vende", /*italian*/"l'unico #cespuglio nel cratere# vende", /*german*/"die Ware eines #Deku-Händlers des Kraters#, |wäre|wären|"},
    });

    hintTable[DMC_GS_CRATE] = HintText::Sometimes({
                       // obscure text
                       Text{"a spider under a #crate in the crater# holds", /*french*/"la Skulltula dans une #boîte volcanique# a", /*spanish*/"una Skulltula bajo una #caja del cráter# otorga", /*italian*/"un ragno sotto una #cassa nel cratere# possiede", /*german*/"in #einer Kiste des Kraters#, |wäre|wären|"},
    });


    hintTable[DEKU_TREE_MQ_AFTER_SPINNING_LOG_CHEST] = HintText::Sometimes({
                       // obscure text
                       Text{"a #temporal stone within a tree# contains", /*french*/"la #pierre bleue dans un arbre# mène à", /*spanish*/"un #bloque temporal de un árbol# contiene", /*italian*/"una #pietra temporale in un albero# nasconde", /*german*/"unter einem #flüchtigen Stein eines Baumes#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"a #temporal stone within the Deku Tree# contains", /*french*/"la #pierre temporelle dans l'arbre Mojo# cache", /*spanish*/"un #bloque temporal del Gran Árbol Deku# contiene", /*italian*/"un #blocco del tempo nell'Albero Deku# nasconde", /*german*/"unter einem #Zeitportal-Stein des Deku-Baumes#, |wäre|wären|"}
    );

    hintTable[DEKU_TREE_MQ_GS_BASEMENT_GRAVES_ROOM] = HintText::Sometimes({
                       // obscure text
                       Text{"a #spider on a ceiling in a tree# holds", /*french*/"l'#araignée haut-perchée dans un arbre# a", /*spanish*/"una #Skulltula en el techo de un árbol# otorga", /*italian*/"#un ragno su un soffitto in un albero# possiede", /*german*/"in der #Spinne, an einer Decke eines Baumes#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"a #spider on a ceiling in the Deku Tree# holds", /*french*/"la#Skulltula dans le cimetière de l'arbre Mojo# a", /*spanish*/"una #Skulltula en el techo del Gran Árbol Deku# otorga", /*italian*/"#un ragno sopra delle tombe nell'Albero Deku# possiede", /*german*/"in der #Spinne, an einer Decke des Deku-Baumes#, |wäre|wären|"}
    );

    hintTable[DODONGOS_CAVERN_MQ_GS_SONG_OF_TIME_BLOCK_ROOM] = HintText::Sometimes({
                       // obscure text
                       Text{"a spider under #temporal stones in a cavern# holds", /*french*/"l'araignée sous #une pierre bleue dans une caverne# a", /*spanish*/"una Skulltula bajo #bloques temporales de una cueva# otorga", /*italian*/"un ragno protetto da #pietre temporali in una caverna# nasconde", /*german*/"in der Spinne, unter einem #flüchtigen Stein einer Höhle#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"a spider under #temporal stones in Dodongo's Cavern# holds", /*french*/"la Skulltula sous #la pierre temporelle dans la caverne Dodongo# a", /*spanish*/"una Skulltula bajo #bloques temporales de la Cueva de los Dodongos# otorga", /*italian*/"un ragno protetto da #blocchi del tempo nella caverna dei Dodongo# nasconde", /*german*/"in der Spinne, unter #Zeitportal-Steinen von Dodongos Höhle#, |wäre|wären|"}
    );

    hintTable[JABU_JABUS_BELLY_BOOMERANG_CHEST] = HintText::Sometimes({
                       // obscure text
                       Text{"a school of #stingers swallowed by a deity# guard", /*french*/"les #raies dans un gardien# protègent", /*spanish*/"unos de #stingers engullidos por cierta deidad# guardan", /*italian*/"una divinità ha inghiottito #un banco di trigoni volanti# con", /*german*/"nahe eines #verschluckten Fischschwarms#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"a school of #stingers swallowed by Jabu-Jabu# guard", /*french*/"les #raies dans Jabu-Jabu# protègent", /*spanish*/"unos #stingers engullidos por Jabu-Jabu# guardan", /*italian*/"#un banco di trigoni volanti# nella pancia di Jabu Jabu protegge", /*german*/"#nahe Fischen in Jabu-Jabus Bauch#, |wäre|wären|"}
    );

    hintTable[JABU_JABUS_BELLY_MQ_GS_INVISIBLE_ENEMIES_ROOM] = HintText::Sometimes({
                       // obscure text
                       Text{"a spider surrounded by #shadows in the belly of a deity# holds", /*french*/"l'araignée entourée d'#ombres dans le ventre du gardien# possède", /*spanish*/"una Skulltula rodeada de #sombras en la tripa de cierta diedad# otorga", /*italian*/"un ragno circondato da #ombre nella pancia di una divinità# tiene", /*german*/"in einer, #von Schatten umgebenen# Spinne des #Bauches einer Gottheit#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"a spider surrounded by #shadows in Jabu-Jabu's Belly# holds", /*french*/"la Skulltula entourée d'#ombres dans Jabu-Jabu# possède", /*spanish*/"una Skulltula rodeada de #sombras en la Tripa de Jabu-Jabu# otorga", /*italian*/"un ragno circondato da #creature invisibili nella pancia di Jabu Jabu# tiene", /*german*/"in einer, #von Schatten umgebenen# Spinne in #Jabu-Jabus Bauch#, |wäre|wären|"}
    );

    hintTable[JABU_JABUS_BELLY_MQ_COW] = HintText::Sometimes({
                       // obscure text
                       Text{"a #cow swallowed by a deity# gifts", /*french*/"la #vache dans le gardien# donne", /*spanish*/"una #vaca engullida por cierta deidad# brinda", /*italian*/"una #mucca inghiottita da una divinità# dona", /*german*/"die Milch, einer #von einer Gottheit verschluckten Kuh#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"a #cow swallowed by Jabu-Jabu# gifts", /*french*/"la #vache avallée par Jabu-Jabu# donne", /*spanish*/"una #vaca engullida por Jabu-Jabu# brinda", /*italian*/"una #mucca inghiottita da Jabu Jabu# dona", /*german*/"die Milch einer #Kuh in Jabu-Jabus Bauch#, |wäre|wären|"}
    );

    hintTable[FIRE_TEMPLE_SCARECROW_CHEST] = HintText::Sometimes({
                       // obscure text
                       Text{"a #scarecrow atop the volcano# hides", /*french*/"l'#épouvantail au sommet d'un volcan# donne", /*spanish*/"un #espantapájaros en lo alto del volcán# esconde", /*italian*/"un #fantoccio in cima al vulcano# nasconde", /*german*/"über einer #Vogelscheuche im oberen Teil des Vulkans#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"#Pierre atop the Fire Temple# hides", /*french*/"#Pierre au sommet du temple du feu# donne", /*spanish*/"#Pierre en lo alto del Templo del Fuego# esconde", /*italian*/"#Pierre in cima al Santuario del Fuoco# nasconde", /*german*/"über #Peter im oberen Teil des Feuertempels#, |wäre|wären|"}
    );

    hintTable[FIRE_TEMPLE_MEGATON_HAMMER_CHEST] = HintText::Sometimes({
                       // obscure text
                       Text{"the #Flare Dancer atop the volcano# guards a chest containing", /*french*/"le #danseur au sommet du volcan# protège", /*spanish*/"el #Bailafuego en lo alto del volcán# otorga", /*italian*/"il #ballerino in cima al vulcano# protegge un forziere contenente", /*german*/"nahe dem #Flammenderwisch, im oberen Teil des Vulkans#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"the #Flare Dancer atop the Fire Temple# guards a chest containing", /*french*/"le #Danse-Flamme au sommet du temple du feu# protège", /*spanish*/"el #Bailafuego en lo alto del Templo del Fuego# otorga", /*italian*/"il #Fiammerino in cima al Santuario del Fuoco# protegge un forziere contenente", /*german*/"nahe dem #Flammenderwisch, im oberen Teil des Feuertempels#, |wäre|wären|"}
    );

    hintTable[FIRE_TEMPLE_MQ_CHEST_ON_FIRE] = HintText::Sometimes({
                       // obscure text
                       Text{"the #Flare Dancer atop the volcano# guards a chest containing", /*french*/"le #danseur au sommet du volcan# protège", /*spanish*/"el #Bailafuego en lo alto del volcán# otorga", /*italian*/"il #ballerino in cima al vulcano# protegge un forziere contenente", /*german*/"nahe dem #Flammenderwisch, im oberen Teil des Vulkans#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"the #Flare Dancer atop the Fire Temple# guards a chest containing", /*french*/"le #Danse-Flamme au sommet du temple du feu# protège", /*spanish*/"el #Bailafuego en lo alto del Templo del Fuego# otorga", /*italian*/"il #Fiammerino in cima al Santuario del Fuoco# protegge un forziere contenente", /*german*/"nahe dem #Flammenderwisch, im oberen Teil des Feuertempels#, |wäre|wären|"}
    );

    hintTable[FIRE_TEMPLE_MQ_GS_SKULL_ON_FIRE] = HintText::Sometimes({
                       // obscure text
                       Text{"a #spider under a block in the volcano# holds", /*french*/"l'#araignée sous un bloc dans le volcan# a", /*spanish*/"una #Skulltula bajo el bloque de un volcán# otorga", /*italian*/"un #ragno sotto un blocco nel vulcano# ha", /*german*/"in der #Spinne, unter einem Block des Vulkans#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"a #spider under a block in the Fire Temple# holds", /*french*/"une #Skulltula sous un bloc dans le temple du feu# a", /*spanish*/"una #Skulltula bajo un bloque del Templo del Fuego# otorga", /*italian*/"un #ragno sotto un blocco nel Santuario del Fuoco# ha", /*german*/"in der #Spinne, unter einem Block des Feuertempels#, |wäre|wären|"}
    );

    hintTable[WATER_TEMPLE_RIVER_CHEST] = HintText::Sometimes({
                       // obscure text
                       Text{"beyond the #river under the lake# waits", /*french*/"au delà de #la rivière sous le lac# se cache", /*spanish*/"tras el #río bajo el lago# yace", /*italian*/"oltre il #fiume sotto il lago# un forziere contiene", /*german*/"hinter dem #Fluss unterhalb des Sees#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"beyond the #river in the Water Temple# waits", /*french*/"au delà de #la rivière dans le temple de l'eau# se cache", /*spanish*/"tras el #río del Templo del Agua# yace", /*italian*/"oltre il #fiume nel Santuario dell'Acqua# un forziere contiene", /*german*/"hinter dem #Fluss des Wassertempels#, |wäre|wären|"}
    );

    hintTable[WATER_TEMPLE_BOSS_KEY_CHEST] = HintText::Sometimes({
                       // obscure text
                       Text{"dodging #rolling boulders under the lake# leads to", /*french*/"éviter des #rochers roulants sous le lac# mène à", /*spanish*/"esquivar #rocas rodantes bajo el lago# conduce a", /*italian*/"schivare #massi rotolanti sotto il lago# porta verso", /*german*/"hinter #rollenden Felsen unterhalb des Sees#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"dodging #rolling boulders in the Water Temple# leads to", /*french*/"éviter des #rochers roulants dans le temple de l'eau# mène à", /*spanish*/"esquivar #rocas rondantes del Templo del Agua# conduce a", /*italian*/"schivare #massi rotolanti nel Santuario dell'Acqua# porta verso", /*german*/"hinter #rollenden Felsen des Wassertempels#, |wäre|wären|"}
    );

    hintTable[WATER_TEMPLE_GS_BEHIND_GATE] = HintText::Sometimes({
                       // obscure text
                       Text{"a spider behind a #gate under the lake# holds", /*french*/"l'araignée derrière une #barrière sous le lac# a", /*spanish*/"una Skulltula tras #una valla bajo el lago# otorga", /*italian*/"un ragno dietro un #cancello sotto il lago# ha", /*german*/"in der Spinne, hinter einem #Gatter unterhalb des Sees#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"a spider behind a #gate in the Water Temple# holds", /*french*/"la Skulltula derrière une #barrière dans le temple de l'eau# a", /*spanish*/"una Skulltula tras #una valla del Templo del Agua# otorga", /*italian*/"un ragno dietro un #cancello nel Santuario dell'Acqua# ha", /*german*/"in der Spinne, hinter einem #Gatter des Wassertempels#, |wäre|wären|"}
    );

    hintTable[WATER_TEMPLE_MQ_FREESTANDING_KEY] = HintText::Sometimes({
                       // obscure text
                       Text{"hidden in a #box under the lake# lies", /*french*/"dans une #boîte sous le lac# gît", /*spanish*/"en una #caja bajo el lago# yace", /*italian*/"in una #cassa sotto il lago# puoi trovare", /*german*/"in einer #Kiste am Grund des Sees#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"hidden in a #box in the Water Temple# lies", /*french*/"dans une #boîte dans le temple de l'eau# gît", /*spanish*/"en una #caja del Templo del Agua# yace", /*italian*/"in una #cassa nel Santuario dell'Acqua# puoi trovare", /*german*/"in einer #Kiste des Wassertempels#, |wäre|wären|"}
    );

    hintTable[WATER_TEMPLE_MQ_GS_FREESTANDING_KEY_AREA] = HintText::Sometimes({
                       // obscure text
                       Text{"the #locked spider under the lake# holds", /*french*/"l'#araignée emprisonnée sous le lac# a", /*spanish*/"la #Skulltula enjaulada bajo el lago# otorga", /*italian*/"il ragno #chiuso a chiave sotto il lago# ha", /*german*/"in einer #eingesperrten Spinne unterhalb des Sees#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"the #locked spider in the Water Temple# holds", /*french*/"une #Skulltula emprisonnée dans le temple de l'eau# a", /*spanish*/"la #Skulltula enjaulada del Templo del Agua# otorga", /*italian*/"il ragno #chiuso a chiave nel Santuario dell'Acqua# ha", /*german*/"in einer #eingesperrten Spinne des Wassertempels#, |wäre|wären|"}
    );

    hintTable[WATER_TEMPLE_MQ_GS_TRIPLE_WALL_TORCH] = HintText::Sometimes({
                       // obscure text
                       Text{"a spider behind a #gate under the lake# holds", /*french*/"l'#araignée derrière une barrière sous le lac# a", /*spanish*/"una Skulltula tras una #valla bajo el lago# otorga", /*italian*/"un ragno dietro un #cancello sotto il lago# ha", /*german*/"in der Spinne, hinter einem #Gatter unterhalb des Sees#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"a spider behind a #gate in the Water Temple# holds", /*french*/"une #Skulltula derrière une barrière dans le temple de l'eau# a", /*spanish*/"una Skulltula tras una #valla del Templo del Agua#", /*italian*/"un ragno dietro un #cancello nel Santuario dell'Acqua# ha", /*german*/"in der Spinne, hinter einem #Gatter des Wassertempels#, |wäre|wären|"}
    );

    hintTable[GERUDO_TRAINING_GROUNDS_UNDERWATER_SILVER_RUPEE_CHEST] = HintText::Sometimes({
                       // obscure text
                       Text{"those who seek #sunken silver rupees# will find", /*french*/"ceux qui pêchent les #joyaux argentés# trouveront", /*spanish*/"aquellos que busquen las #rupias plateadas sumergidas# encontrarán", /*italian*/"coloro che cercano #rupie d'argento sommerse# troveranno", /*german*/"#geborgenes Silber#, |wäre|wären|"},
                       Text{"the #thieves' underwater training# rewards",      /*french*/"l'#épreuve de plongée des voleurs# recèle",         /*spanish*/"la #instrucción submarina de las bandidas# premia",                  /*italian*/"l'#addestramento subacqueo dei ladri# è premiato con",     /*german*/"beim #Tauchtraining der Diebe#, |wäre|wären|"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MQ_UNDERWATER_SILVER_RUPEE_CHEST] = HintText::Sometimes({
                       // obscure text
                       Text{"those who seek #sunken silver rupees# will find", /*french*/"ceux qui pêchent les #joyaux argentés# trouveront", /*spanish*/"aquellos que busquen las #rupias plateadas sumergidas# encontrarán", /*italian*/"coloro che cercano #rupie d'argento sommerse# troveranno", /*german*/"#geborgenes Silber#, |wäre|wären|"},
                       Text{"the #thieves' underwater training# rewards",      /*french*/"l'#épreuve de plongée des voleurs# recèle",         /*spanish*/"la #instrucción submarina de las bandidas# premia",                  /*italian*/"l'#addestramento subacqueo dei ladri# è premiato con",     /*german*/"beim #Tauchtraining der Diebe#, |wäre|wären|"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MAZE_PATH_FINAL_CHEST] = HintText::Sometimes({
                       // obscure text
                       Text{"the final prize of #the thieves' training# is", /*french*/"la récompense ultime de #l'épreuve des voleurs# est", /*spanish*/"el premio final de la #instrucción de las bandidas# brinda", /*italian*/"il premio finale dell'#addestramento dei ladri# è", /*german*/"der #Hauptpreis# des Trainings der Diebe, |wäre|wären|"},
    });

    hintTable[GERUDO_TRAINING_GROUNDS_MQ_ICE_ARROWS_CHEST] = HintText::Sometimes({
                       // obscure text
                       Text{"the final prize of #the thieves' training# is", /*french*/"la récompense ultime de #l'épreuve des voleurs# est", /*spanish*/"el premio final de la #instrucción de las bandidas# brinda", /*italian*/"il premio finale dell'#addestramento dei ladri# è", /*german*/"der #Hauptpreis# des Trainings der Diebe, |wäre|wären|"},
    });

    hintTable[BOTTOM_OF_THE_WELL_LENS_OF_TRUTH_CHEST] = HintText::Sometimes({
                       // obscure text
                       Text{"the well's #grasping ghoul# hides",    /*french*/"la #terreur du puits# cache",             /*spanish*/"en las #profundidades del pozo# se esconde", /*italian*/"l'#incubo del pozzo# possiede",         /*german*/"nahe dem #ergreifenden Ghul# des Brunnens, |wäre|wären|"},
                       Text{"a #nether dweller in the well# holds", /*french*/"le #spectre qui réside dans le puits# a", /*spanish*/"el #temido morador del pozo# concede",       /*italian*/"un #tipo manesco sottoterra# possiede", /*german*/"nahe dem #unterirdischen Bewohner des Brunnens#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"#Dead Hand in the well# holds", /*french*/"le #Poigneur dans le puits# cache", /*spanish*/"la #Mano Muerta del pozo# concede", /*italian*/"lo #Smaniosso nel pozzo# possiede", /*german*/"nahe dem #Todesgrapscher des Brunnens#, |wäre|wären|"}
    );

    hintTable[BOTTOM_OF_THE_WELL_MQ_COMPASS_CHEST] = HintText::Sometimes({
                       // obscure text
                       Text{"the well's #grasping ghoul# hides",    /*french*/"la #terreur du puits# cache",             /*spanish*/"en las #profundidades del pozo# se esconde", /*italian*/"l'#incubo del pozzo# possiede",         /*german*/"nahe dem #ergreifenden Ghul# des Brunnens, |wäre|wären|"},
                       Text{"a #nether dweller in the well# holds", /*french*/"le #spectre qui réside dans le puits# a", /*spanish*/"el #temido morador del pozo# concede",       /*italian*/"un #tipo manesco sottoterra# possiede", /*german*/"nahe dem #unterirdischen Bewohner des Brunnens#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"#Dead Hand in the well# holds", /*french*/"le #Poigneur dans le puits# cache", /*spanish*/"la #Mano Muerta del pozo# concede", /*italian*/"lo #Smaniosso nel pozzo# possiede", /*german*/"nahe dem #Todesgrapscher des Brunnens#, |wäre|wären|"}
    );

    hintTable[SPIRIT_TEMPLE_SILVER_GAUNTLETS_CHEST] = HintText::Sometimes({
                       // obscure text
                       Text{"the treasure #sought by Nabooru# is", /*french*/"le trésor que #recherche Nabooru# est", /*spanish*/"el #ansiado tesoro de Nabooru# brinda", /*italian*/"il tesoro che #Naburu cerca# è", /*german*/"der Schatz, nachdem #Naboru sich sehnt#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"upon the #Colossus's right hand# is", /*french*/"sur la #main droite du colosse# repose", /*spanish*/"en la #mano derecha del Coloso# yace", /*italian*/"sulla #mano destra del colosso# puoi trovare", /*german*/"auf der #rechten Hand des Kolosses#, |wäre|wären|"}
    );

    hintTable[SPIRIT_TEMPLE_MIRROR_SHIELD_CHEST] = HintText::Sometimes({
                       // obscure text
                       Text{"upon the #Colossus's left hand# is", /*french*/"sur la #main gauche du colosse# repose", /*spanish*/"en la #mano izquierda del Coloso# yace", /*italian*/"sulla #mano sinistra del colosso# puoi trovare", /*german*/"auf der #linken Hand des Kolosses#, |wäre|wären|"},
    });

    hintTable[SPIRIT_TEMPLE_MQ_CHILD_HAMMER_SWITCH_CHEST] = HintText::Sometimes({
                       // obscure text
                       Text{"a #temporal paradox in the Colossus# yields", /*french*/"un #paradoxe temporel dans le colosse# révèle", /*spanish*/"una #paradoja temporal del Coloso# conduce a", /*italian*/"un #paradosso temporale nel colosso# rivela", /*german*/"ein #Zeitparadoxon des Kolosses#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"a #temporal paradox in the Spirit Temple# yields", /*french*/"le #paradoxe temporel dans le temple de l'esprit# révèle", /*spanish*/"una #paradoja temporal del Coloso# conduce a", /*italian*/"un #paradosso temporale nel Santuario dello Spirito# rivela", /*german*/"ein #Zeitparadoxon des Geistertempels#, |wäre|wären|"}
    );

    hintTable[SPIRIT_TEMPLE_MQ_SYMPHONY_ROOM_CHEST] = HintText::Sometimes({
                       // obscure text
                       Text{"a #symphony in the Colossus# yields", /*french*/"la #symphonie du colosse# révèle", /*spanish*/"una #sinfonía del Coloso# conduce a", /*italian*/"una #sinfonia nel colosso# rivela", /*german*/"eine #Symphonie des Kolosses#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"a #symphony in the Spirit Temple# yields", /*french*/"les #cinq chansons du temple de l'esprit# révèlent", /*spanish*/"una #sinfonía del Coloso# conduce a", /*italian*/"una #sinfonia nel Santuario dello Spirito# rivela", /*german*/"eine #Symphonie des Geistertempels#, |wäre|wären|"}
    );

    hintTable[SPIRIT_TEMPLE_MQ_GS_SYMPHONY_ROOM] = HintText::Sometimes({
                       // obscure text
                       Text{"a #spider's symphony in the Colossus# yields", /*french*/"la #mélodie de l'araignée du colosse# révèle", /*spanish*/"la #Skulltula de la sinfonía del Coloso# otorga", /*italian*/"un #ragno musicofilo nel colosso# ha", /*german*/"in der #Spinne, nahe der Symphonie des Kolosses#, |wäre|wären|"},
                     }, {},
                       // clear text
                       Text{"a #spider's symphony in the Spirit Temple# yields", /*french*/"la #mélodie de la Skulltula du temple de l'esprit# révèle", /*spanish*/"la #Skulltula de la sinfonía del Coloso# otorga", /*italian*/"un #ragno musicofilo nel Santuario dello Spirito# ha", /*german*/"in der #Spinne, nahe der Symphonie des Geistertempels#, |wäre|wären|"}
    );

    hintTable[SHADOW_TEMPLE_INVISIBLE_FLOORMASTER_CHEST] = HintText::Sometimes({
                       // obscure text
                       Text{"shadows in an #invisible maze# guard", /*french*/"les ombres dans le #labyrinthe invisible# protègent", /*spanish*/"las sombras del #laberinto invisible# esconden", /*italian*/"ombre vicino a #un labirinto invisibile# nascondono", /*german*/"nahe Schatten des #unsichtbaren Irrgartens#, |wäre|wären|"},
    });

    hintTable[SHADOW_TEMPLE_MQ_BOMB_FLOWER_CHEST] = HintText::Sometimes({
                       // obscure text
                       Text{"shadows in an #invisible maze# guard", /*french*/"les ombres dans le #labyrinthe invisible# protègent", /*spanish*/"las sombras del #laberinto invisible# esconden", /*italian*/"ombre vicino a #un labirinto invisibile# nascondono", /*german*/"nahe Schatten des #unsichtbaren Irrgartens#, |wäre|wären|"},
    });

    /*--------------------------
    |    ENTRANCE HINT TEXT    |
    ---------------------------*/

    hintTable[DESERT_COLOSSUS_TO_COLOSSUS_GROTTO] = HintText::Entrance({
                     // obscure text
                     Text{"lifting a #rock in the desert# reveals", /*french*/"soulever une #roche dans le désert# révèle", /*spanish*/"levantar una #roca del desierto# revela", /*italian*/"sollevare una #roccia nel deserto# rivela", /*german*/"unter einem #silbernen Felsen# der Wüste, |wäre|wären|"},
    });

    hintTable[GV_GROTTO_LEDGE_TO_GV_OCTOROK_GROTTO] = HintText::Entrance({
                     // obscure text
                     Text{"a rock on #a ledge in the valley# hides", /*french*/"soulever une #roche dans la vallée# révèle", /*spanish*/"levantar una #roca al borde del valle# esconde", /*italian*/"una #roccia su una sporgenza nella valle# nasconde", /*german*/"unter einem #silbernen Felsen# des Tals, |wäre|wären|"},
    });

    hintTable[GC_GROTTO_PLATFORM_TO_GC_GROTTO] = HintText::Entrance({
                     // obscure text
                     Text{"a #pool of lava# in Goron City blocks the way to", /*french*/"l'#étang de lave# dans le village Goron renferme", /*spanish*/"un #estanque de lava# en la Ciudad Goron bloquea el paso a", /*italian*/"una #pozza di lava# nella città dei Goron blocca il passaggio per", /*german*/"hinter einem #Lavasee# Goronias, |wäre|wären|"},
    });

    hintTable[GERUDO_FORTRESS_TO_GF_STORMS_GROTTO] = HintText::Entrance({
                     // obscure text
                     Text{"a #storm within Gerudo's Fortress# reveals", /*french*/"la #tempête dans la forteresse# révèle", /*spanish*/"una #tormenta en la Fortaleza Gerudo# revela", /*italian*/"una #tempesta nella fortezza Gerudo# rivela", /*german*/"in einem #stürmischen Erdloch der Gerudo-Festung#, |wäre|wären|"},
    });

    hintTable[ZORAS_DOMAIN_TO_ZD_STORMS_GROTTO] = HintText::Entrance({
                     // obscure text
                     Text{"a #storm within Zora's Domain# reveals", /*french*/"la #tempête dans le domaine des Zoras# révèle", /*spanish*/"una #tormenta en la Región de los Zora# revela", /*italian*/"una #tempesta nel villaggio degli Zora# rivela", /*german*/"in einem #stürmischen Erdloch von Zoras Reich#, |wäre|wären|"},
    });

    hintTable[HYRULE_CASTLE_GROUNDS_TO_HC_STORMS_GROTTO] = HintText::Entrance({
                     // obscure text
                     Text{"a #storm near the castle# reveals", /*french*/"la #tempête près du château# révèle", /*spanish*/"una #tormenta junto al castillo# revela", /*italian*/"una #tempesta vicino al castello# rivela", /*german*/"in einem #stürmischen Erdloch nahe eines Schlosses#, |wäre|wären|"},
    });

    hintTable[GV_FORTRESS_SIDE_TO_GV_STORMS_GROTTO] = HintText::Entrance({
                     // obscure text
                     Text{"a #storm in the valley# reveals", /*french*/"la #tempête dans la vallée# révèle", /*spanish*/"una #tormenta en el valle# revela", /*italian*/"una #tempesta nella valle# rivela", /*german*/"in einem #stürmischen Erdloch des Gerudotals#, |wäre|wären|"},
    });

    hintTable[DESERT_COLOSSUS_TO_COLOSSUS_GREAT_FAIRY_FOUNTAIN] = HintText::Entrance({
                     // obscure text
                     Text{"a #fractured desert wall# hides", /*french*/"le #mur fragile du désert# cache", /*spanish*/"una #agrietada pared del desierto# esconde", /*italian*/"una #parete friabile nel deserto# nasconde", /*german*/"hinter einer #brüchigen Wand# der Wüste, |wäre|wären|"},
    });

    hintTable[GANONS_CASTLE_GROUNDS_TO_OGC_GREAT_FAIRY_FOUNTAIN] = HintText::Entrance({
                     // obscure text
                     Text{"a #heavy pillar# outside the castle obstructs", /*french*/"le #rocher fragile près du château# cache", /*spanish*/"una #pesada columna# fuera del castillo obstruye", /*italian*/"un #pesante pilastro# fuori dal castello ostruisce", /*german*/"hinter einer #schweren Säule# nahe eines Schlosses, |wäre|wären|"},
    });

    hintTable[ZORAS_FOUNTAIN_TO_ZF_GREAT_FAIRY_FOUNTAIN] = HintText::Entrance({
                     // obscure text
                     Text{"a #fountain wall# hides", /*french*/"le #mur fragile du réservoir# cache", /*spanish*/"una #pared de la fuente# esconde", /*italian*/"una #parete della sorgente# nasconde", /*german*/"hinter einer #Wand einer Quelle#, |wäre|wären|"},
    });

    hintTable[GV_FORTRESS_SIDE_TO_GV_CARPENTER_TENT] = HintText::Entrance({
                     // obscure text
                     Text{"a #tent in the valley# covers", /*french*/"la #tente dans la vallée# recouvre", /*spanish*/"una #tienda de campaña del valle# cubre", /*italian*/"una #tenda nella valle# copre", /*german*/"in einem #Zelt des Tals#, |wäre|wären|"},
    });

    hintTable[GRAVEYARD_WARP_PAD_REGION_TO_SHADOW_TEMPLE_ENTRYWAY] = HintText::Entrance({
                     // obscure text
                     Text{"at the #back of the Graveyard#, there is", /*french*/"#derrière le cimetière# gît", /*spanish*/"en la #parte trasera del cementerio# se halla", /*italian*/"#in fondo al cimitero# si trova", /*german*/"am #hinteren Ende des Friedhofs#, |wäre|wären|"},
    });

    hintTable[LAKE_HYLIA_TO_WATER_TEMPLE_LOBBY] = HintText::Entrance({
                     // obscure text
                     Text{"deep #under a vast lake#, one can find", /*french*/"#sous le lac# gît", /*spanish*/"en las #profundidades de un lago inmenso# se halla", /*italian*/"#sotto le acque di un lago# puoi trovare", /*german*/"am #Grund eines tiefen Sees#, |wäre|wären|"},
    });

    hintTable[GERUDO_FORTRESS_TO_GERUDO_TRAINING_GROUNDS_LOBBY] = HintText::Entrance({
                     // obscure text
                     Text{"paying a #fee to the Gerudos# grants access to", /*french*/"l'#entrée payante des Gerudo# donne accès à", /*spanish*/"pagarle una #tasa a las gerudo# da acceso a", /*italian*/"pagando una #quota alle Gerudo# si può raggiungere", /*german*/"in einem #Gebäude mit Eintrittskosten#, |wäre|wären|"},
    });

    hintTable[ZORAS_FOUNTAIN_TO_JABU_JABUS_BELLY_BEGINNING] = HintText::Entrance({
                     // obscure text
                     Text{"inside #Jabu-Jabu#, one can find", /*french*/"#dans Jabu-Jabu# se trouve", /*spanish*/"dentro de #Jabu-Jabu# se halla", /*italian*/"dentro #Jabu Jabu# si trova", /*german*/"in #Jabu-Jabu, |wäre|wären|"},
    });

    hintTable[KAKARIKO_VILLAGE_TO_BOTTOM_OF_THE_WELL] = HintText::Entrance({
                     // obscure text
                     Text{"a #village well# leads to", /*french*/"dans le fond du #puits du village# gît", /*spanish*/"el #pozo de un pueblo# conduce a", /*italian*/"il #pozzo del villaggio# è costruito sopra", /*german*/"in einem #Dorfbrunnen#, |wäre|wären|"},
    });

    /*--------------------------
    |      EXIT HINT TEXT      |
    ---------------------------*/
    //maybe make a new type for this? I'm not sure if it really matters

    hintTable[LINKS_POCKET] = HintText::Exclude({
                     // obscure text
                     Text{"Link's Pocket", /*french*/"les poches de @", /*spanish*/"el bolsillo de @", /*italian*/"la tasca di @", /*german*/"in @s Tasche"},
    });

    hintTable[KOKIRI_FOREST] = HintText::Exclude({
                     // obscure text
                     Text{"Kokiri Forest", /*french*/"la forêt Kokiri", /*spanish*/"el Bosque Kokiri", /*italian*/"la foresta dei Kokiri", /*german*/"im Kokiri-Wald"},
    });

    hintTable[THE_LOST_WOODS] = HintText::Exclude({
                     // obscure text
                     Text{"the Lost Woods", /*french*/"la forêt des méandres", /*spanish*/"el Bosque Perdido", /*italian*/"il bosco perduto", /*german*/"in den Verlorenen Wäldern"},
    });

    hintTable[SACRED_FOREST_MEADOW] = HintText::Exclude({
                     // obscure text
                     Text{"Sacred Forest Meadow", /*french*/"le bosquet sacré", /*spanish*/"la pradera sagrada del bosque", /*italian*/"la radura sacra", /*german*/"auf der Heiligen Lichtung"},
    });

    hintTable[HYRULE_FIELD] = HintText::Exclude({
                     // obscure text
                     Text{"Hyrule Field", /*french*/"la plaine d'Hyrule", /*spanish*/"la Llanura de Hyrule", /*italian*/"la piana di Hyrule", /*german*/"auf den Ebenen Hyrules"},
    });

    hintTable[LAKE_HYLIA] = HintText::Exclude({
                     // obscure text
                     Text{"Lake Hylia", /*french*/"le lac Hylia", /*spanish*/"el Lago Hylia", /*italian*/"il Lago Hylia", /*german*/"am Hylia-See"},
    });

    hintTable[GERUDO_VALLEY] = HintText::Exclude({
                     // obscure text
                     Text{"Gerudo Valley", /*french*/"la vallée Gerudo", /*spanish*/"el Valle Gerudo", /*italian*/"la Valle Gerudo", /*german*/"im Gerudotal"},
    });

    hintTable[GERUDO_FORTRESS] = HintText::Exclude({
                     // obscure text
                     Text{"Gerudo's Fortress", /*french*/"la forteresse Gerudo", /*spanish*/"la Fortaleza Gerudo", /*italian*/"la fortezza Gerudo", /*german*/"in der Gerudo-Festung"},
    });

    hintTable[HAUNTED_WASTELAND] = HintText::Exclude({
                     // obscure text
                     Text{"Haunted Wasteland", /*french*/"le désert hanté", /*spanish*/"el desierto encantado", /*italian*/"il deserto stregato", /*german*/"in der Gespensterwüste"},
    });

    hintTable[DESERT_COLOSSUS] = HintText::Exclude({
                     // obscure text
                     Text{"Desert Colossus", /*french*/"le colosse du désert", /*spanish*/"el Coloso del Desierto", /*italian*/"il colosso del deserto", /*german*/"am Wüstenkoloss"},
    });

    hintTable[THE_MARKET] = HintText::Exclude({
                     // obscure text
                     Text{"the Market", /*french*/"la place du marché", /*spanish*/"la plaza del mercado", /*italian*/"il mercato", /*german*/"auf dem Marktplatz"},
    });

    hintTable[TEMPLE_OF_TIME] = HintText::Exclude({
                     // obscure text
                     Text{"Temple of Time", /*french*/"le temple du temps", /*spanish*/"el Templo del Tiempo", /*italian*/"il Santuario del Tempo", /*german*/"in der Zitadelle der Zeit"},
    });

    hintTable[HYRULE_CASTLE] = HintText::Exclude({
                     // obscure text
                     Text{"Hyrule Castle", /*french*/"le château d'Hyrule", /*spanish*/"el Castillo de Hyrule", /*italian*/"il castello di Hyrule", /*german*/"vor Schloss Hyrule"},
    });

    hintTable[OUTSIDE_GANONS_CASTLE] = HintText::Exclude({
                     // obscure text
                     Text{"outside Ganon's Castle", /*french*/"les alentours du château de Ganon", /*spanish*/"el exterior del Castillo de Ganon", /*italian*/"l'esterno del castello di Ganon", /*german*/"vor Ganons Schloss"},
    });

    hintTable[KAKARIKO_VILLAGE] = HintText::Exclude({
                     // obscure text
                     Text{"Kakariko Village", /*french*/"le village Cocorico", /*spanish*/"Kakariko", /*italian*/"il villaggio Calbarico", /*german*/"in Kakariko"},
    });

    hintTable[THE_GRAVEYARD] = HintText::Exclude({
                     // obscure text
                     Text{"the Graveyard", /*french*/"le cimetière", /*spanish*/"el cementerio", /*italian*/"il cimitero", /*german*/"auf dem Friedhof"},
    });

    hintTable[DEATH_MOUNTAIN_TRAIL] = HintText::Exclude({
                     // obscure text
                     Text{"Death Mountain Trail", /*french*/"le chemin du mont de la Mort", /*spanish*/"el sendero de la Montaña de la Muerte", /*italian*/"il sentiero del Monte Morte", /*german*/"auf dem Gebirgspfad"},
    });

    hintTable[GORON_CITY] = HintText::Exclude({
                     // obscure text
                     Text{"Goron City", /*french*/"le village Goron", /*spanish*/"la Ciudad Goron", /*italian*/"la città dei Goron", /*german*/"in Goronia"},
    });

    hintTable[DEATH_MOUNTAIN_CRATER] = HintText::Exclude({
                     // obscure text
                     Text{"Death Mountain Crater", /*french*/"le cratère du mont de la Mort", /*spanish*/"el cráter de la Montaña de la Muerte", /*italian*/"il cratere del Monte Morte", /*german*/"im Todeskrater"},
    });

    hintTable[ZORAS_RIVER] = HintText::Exclude({
                     // obscure text
                     Text{"Zora's River", /*french*/"le fleuve Zora", /*spanish*/"el Río Zora", /*italian*/"il Fiume Zora", /*german*/"am Zora-Fluss"},
    });

    hintTable[ZORAS_DOMAIN] = HintText::Exclude({
                     // obscure text
                     Text{"Zora's Domain", /*french*/"le domaine des Zoras", /*spanish*/"la Región de los Zora", /*italian*/"il villaggio degli Zora", /*german*/"in Zoras Reich"},
    });

    hintTable[ZORAS_FOUNTAIN] = HintText::Exclude({
                     // obscure text
                     Text{"Zora's Fountain", /*french*/"la fontaine Zora", /*spanish*/"la Fuente Zora", /*italian*/"la sorgente Zora", /*german*/"an Zoras Quelle"},
    });

    hintTable[LON_LON_RANCH] = HintText::Exclude({
                     // obscure text
                     Text{"Lon Lon Ranch", /*french*/"le ranch Lon Lon", /*spanish*/"el Rancho Lon Lon", /*italian*/"la Fattoria Lon Lon", /*german*/"auf der Lon Lon-Farm"},
    });


    /*--------------------------
    |     REGION HINT TEXT     |
    ---------------------------*/

    hintTable[KF_LINKS_HOUSE] = HintText::Region({
                     // obscure text
                     Text{"Link's House", /*french*/"la #maison de @#", /*spanish*/"la casa de @", /*italian*/"la #casa di @#", /*german*/"in #@s Haus#"},
    });

    // hintTable[TOT_MAIN] = HintText::Region({
    //                    // obscure text
    //                    Text{"the #Temple of Time#", /*french*/"le #temple du temps#", /*spanish*/"el Templo del Tiempo", /*italian*/"il #Santuario del Tempo#", /*german*/"in der #Zitadelle der Zeit#"},
    // });

    hintTable[KF_MIDOS_HOUSE] = HintText::Region({
                     // obscure text
                     Text{"Mido's house", /*french*/"la #cabane du Grand Mido#", /*spanish*/"la casa de Mido", /*italian*/"la #casa di Mido#", /*german*/"in #Midos Haus#"},
    });

    hintTable[KF_SARIAS_HOUSE] = HintText::Region({
                     // obscure text
                     Text{"Saria's House", /*french*/"la #cabane de Saria#", /*spanish*/"la casa de Saria", /*italian*/"la #casa di Saria#", /*german*/"in #Salias Haus#"},
    });

    hintTable[KF_HOUSE_OF_TWINS] = HintText::Region({
                     // obscure text
                     Text{"the #House of Twins#", /*french*/"la #cabane des jumelles#", /*spanish*/"la casa de las gemelas", /*italian*/"la #casa delle gemelle#", /*german*/"im #Haus der Zwillinge#"},
    });

    hintTable[KF_KNOW_IT_ALL_HOUSE] = HintText::Region({
                     // obscure text
                     Text{"Know-It-All Brothers' House", /*french*/"la #cabane des frères Je-Sais-Tout#", /*spanish*/"la casa de los hermanos Sabelotodo", /*italian*/"la #casa dei fratelli So-tutto-io#", /*german*/"im #Haus der Allwissenden Brüder#"},
    });

    hintTable[KF_KOKIRI_SHOP] = HintText::Region({
                     // obscure text
                     Text{"the #Kokiri Shop#", /*french*/"le #magasin Kokiri#", /*spanish*/"la tienda kokiri", /*italian*/"il #negozio dei Kokiri#", /*german*/"im #Kokiri-Laden#"},
    });

    hintTable[LH_LAB] = HintText::Region({
                     // obscure text
                     Text{"the #Lakeside Laboratory#", /*french*/"le #laboratoire du lac#", /*spanish*/"el laboratorio del lago", /*italian*/"il #laboratorio sul lago#", /*german*/"im #Labor am See#"},
    });

    hintTable[LH_FISHING_HOLE] = HintText::Region({
                     // obscure text
                     Text{"the #Fishing Pond#", /*french*/"l'#étang#", /*spanish*/"el estanque", /*italian*/"il #lago di pesca#", /*german*/"am #Fischweiher#"},
    });

    hintTable[GV_CARPENTER_TENT] = HintText::Region({
                     // obscure text
                     Text{"the #Carpenters' tent#", /*french*/"la #tente des charpentiers#", /*spanish*/"la #tienda de campaña de los carpinteros#", /*italian*/"la #tenda dei carpentieri#", /*german*/"im #Zelt der Zimmerleute#"},
    });

    hintTable[MARKET_GUARD_HOUSE] = HintText::Region({
                     // obscure text
                     Text{"the #Guard House#", /*french*/"le #poste de garde#", /*spanish*/"la caseta de guardia", /*italian*/"la #guardiola#", /*german*/"im #Wachhaus#"},
    });

    hintTable[MARKET_MASK_SHOP] = HintText::Region({
                     // obscure text
                     Text{"the #Happy Mask Shop#", /*french*/"la #foire aux masques#", /*spanish*/"la tienda de La Máscara Feliz", /*italian*/"il #negozio delle maschere della felicità#", /*german*/"beim #Maskenhändler#"},
    });

    hintTable[MARKET_BOMBCHU_BOWLING] = HintText::Region({
                     // obscure text
                     Text{"the #Bombchu Bowling Alley#", /*french*/"le #bowling teigneux#", /*spanish*/"la Bolera Bombchu", /*italian*/"la #sala da bowling#", /*german*/"auf der #Minenbowlingbahn#"},
    });

    hintTable[MARKET_POTION_SHOP] = HintText::Region({
                     // obscure text
                     Text{"the #Market Potion Shop#", /*french*/"l'#apothicaire de la place du marché#", /*spanish*/"la tienda de pociones de la plaza del mercado", /*italian*/"il #negozio di pozioni del mercato#", /*german*/"im #Magie-Laden des Marktplatzes#"},
    });

    hintTable[MARKET_TREASURE_CHEST_GAME] = HintText::Region({
                     // obscure text
                     Text{"the #Treasure Chest Shop#", /*french*/"la #chasse aux trésors#", /*spanish*/"el Cofre del Tesoro", /*italian*/"la #sala della fortuna#", /*german*/"in der #Truhenlotterie#"},
    });

    hintTable[MARKET_BOMBCHU_SHOP] = HintText::Region({
                     // obscure text
                     Text{"the #Bombchu Shop#", /*french*/"le #magasin de Bombchus#", /*spanish*/"la Tienda Bombchu", /*italian*/"il #negozio di radiomine#", /*german*/"im #Krabbelminenladen#"},
    });

    hintTable[MARKET_MAN_IN_GREEN_HOUSE] = HintText::Region({
                     // obscure text
                     Text{"Man in Green's House", /*french*/"la #maison de l'homme en vert#", /*spanish*/"la casa del hombre de verde", /*italian*/"la #casa del tipo in verde#", /*german*/"im #Haus des grün gekleideten Mannes#"},
    });

    hintTable[KAK_WINDMILL] = HintText::Region({
                     // obscure text
                     Text{"the #Windmill#", /*french*/"le #moulin#", /*spanish*/"el #molino#", /*italian*/"il #mulino#", /*german*/"in der #Windmühle#"},
    });

    hintTable[KAK_CARPENTER_BOSS_HOUSE] = HintText::Region({
                     // obscure text
                     Text{"the #Carpenters' Boss House#", /*french*/"la #maison du chef des ouvriers#", /*spanish*/"la casa del capataz de los carpinteros", /*italian*/"la #casa del capo dei carpentieri#", /*german*/"im #Haus des Chefs der Zimmerleute#"},
    });

    hintTable[KAK_HOUSE_OF_SKULLTULA] = HintText::Region({
                     // obscure text
                     Text{"the #House of Skulltula#", /*french*/"la #maison des Skulltulas#", /*spanish*/"la casa de las Skulltulas", /*italian*/"la #casa delle Aracnule#", /*german*/"im #Haus der Skulltula#"},
    });

    hintTable[KAK_IMPAS_HOUSE] = HintText::Region({
                     // obscure text
                     Text{"Impa's House", /*french*/"la #maison d'Impa#", /*spanish*/"la casa de Impa", /*italian*/"la #casa di Impa#", /*german*/"in #Impas Haus#"},
    });

    hintTable[KAK_IMPAS_HOUSE_BACK] = HintText::Region({
                     // obscure text
                     Text{"Impa's cow cage", /*french*/"la #cage à vache d'Impa#", /*spanish*/"la jaula de la vaca de Impa", /*italian*/"la #gabbia della mucca di Impa#", /*german*/"in #Impas Kuhkäfig#"},
    });

    hintTable[KAK_ODD_POULTICE_BUILDING] = HintText::Region({
                     // obscure text
                     Text{"Granny's Potion Shop", /*french*/"la #maison bleue de Cocorico#", /*spanish*/"la tienda de pociones de la abuela", /*italian*/"il #negozio della nonna#", /*german*/"in #Omas Magie-Laden#"},
    });

    hintTable[GRAVEYARD_DAMPES_HOUSE] = HintText::Region({
                     // obscure text
                     Text{"Dampé's Hut", /*french*/"la #cabane du fossoyeur#", /*spanish*/"la cabaña de Dampé", /*italian*/"la #capanna del becchino#", /*german*/"in der #Hütte des Totengräbers#"},
    });

    hintTable[GC_SHOP] = HintText::Region({
                     // obscure text
                     Text{"the #Goron Shop#", /*french*/"la #boutique Goron#", /*spanish*/"la #tienda goron#", /*italian*/"il #negozio dei Goron#", /*german*/"im #Goronen-Laden#"},
    });

    hintTable[ZD_SHOP] = HintText::Region({
                     // obscure text
                     Text{"the #Zora Shop#", /*french*/"la #boutique Zora#", /*spanish*/"la #tienda zora#", /*italian*/"il #negozio degli Zora#", /*german*/"im #Zora-Laden#"},
    });

    hintTable[LLR_TALONS_HOUSE] = HintText::Region({
                     // obscure text
                     Text{"Talon's House", /*french*/"la #maison de Talon#", /*spanish*/"la casa de Talon", /*italian*/"la #casa di Talon#", /*german*/"in #Talons Haus#"},
    });

    hintTable[LLR_STABLES] = HintText::Region({
                     // obscure text
                     Text{"a #stable#", /*french*/"l'#étable#", /*spanish*/"el establo", /*italian*/"la #stalla#", /*german*/"in einem #Stall#"},
    });

    hintTable[LLR_TOWER] = HintText::Region({
                     // obscure text
                     Text{"the #Lon Lon Tower#", /*french*/"le #silo du ranch Lon Lon#", /*spanish*/"la torre Lon Lon", /*italian*/"la #torre della fattoria#", /*german*/"im #Turm der Lon Lon-Farm#"},
    });

    hintTable[MARKET_BAZAAR] = HintText::Region({
                     // obscure text
                     Text{"the #Market Bazaar#", /*french*/"le #bazar de la place du marché#", /*spanish*/"el bazar de la plaza del mercado", /*italian*/"il #bazar del mercato#", /*german*/"im #Basar des Marktplatzes#"},
    });

    hintTable[MARKET_SHOOTING_GALLERY] = HintText::Region({
                     // obscure text
                     Text{"a #Slingshot Shooting Gallery#", /*french*/"le #jeu d'adresse de la place du marché#", /*spanish*/"el Tiro al Blanco con tirachinas", /*italian*/"la #vecchia sala del tirassegno#", /*german*/"in der #Schleuder-Schießbude#"},
    });

    hintTable[KAK_BAZAAR] = HintText::Region({
                     // obscure text
                     Text{"the #Kakariko Bazaar#", /*french*/"le #bazar de Cocorico#", /*spanish*/"el bazar de Kakariko", /*italian*/"il #bazar di Calbarico#", /*german*/"im #Basar von Kakariko#"},
    });

    hintTable[KAK_POTION_SHOP_FRONT] = HintText::Region({
                     // obscure text
                     Text{"the #Kakariko Potion Shop#", /*french*/"l'#apothicaire de Cocorico#", /*spanish*/"la tienda de pociones de Kakariko", /*italian*/"il #negozio di pozioni di Calbarico#", /*german*/"im #Magie-Laden von Kakariko#"},
    });

    hintTable[KAK_POTION_SHOP_BACK] = HintText::Region({
                     // obscure text
                     Text{"the #Kakariko Potion Shop#", /*french*/"l'#apothicaire de Cocorico#", /*spanish*/"la tienda de pociones de Kakariko", /*italian*/"il #negozio di pozioni di Calbarico#", /*german*/"im #Magie-Laden von Kakariko#"},
    });

    hintTable[KAK_SHOOTING_GALLERY] = HintText::Region({
                     // obscure text
                     Text{"a #Bow Shooting Gallery#", /*french*/"le #jeu d'adresse de Cocorico#", /*spanish*/"el Tiro al Blanco con arco", /*italian*/"la #nuova sala del tirassegno#", /*german*/"in der #Bogen-Schießbude#"},
    });

    hintTable[COLOSSUS_GREAT_FAIRY_FOUNTAIN] = HintText::Region({
                     // obscure text
                     Text{"a #Great Fairy Fountain#", /*french*/"la #grande fée du colosse#", /*spanish*/"una fuente de la Gran Hada", /*italian*/"la #fontana di una Fata radiosa#", /*german*/"in einer #Feen-Quelle#"},
    });

    hintTable[HC_GREAT_FAIRY_FOUNTAIN] = HintText::Region({
                     // obscure text
                     Text{"a #Great Fairy Fountain#", /*french*/"la #grande fée du château#", /*spanish*/"una fuente de la Gran Hada", /*italian*/"la #fontana di una Fata radiosa#", /*german*/"in einer #Feen-Quelle#"},
    });

    hintTable[OGC_GREAT_FAIRY_FOUNTAIN] = HintText::Region({
                     // obscure text
                     Text{"a #Great Fairy Fountain#", /*french*/"la #grande fée des ruines#", /*spanish*/"una fuente de la Gran Hada", /*italian*/"la #fontana di una Fata radiosa#", /*german*/"in einer #Feen-Quelle#"},
    });

    hintTable[DMC_GREAT_FAIRY_FOUNTAIN] = HintText::Region({
                     // obscure text
                     Text{"a #Great Fairy Fountain#", /*french*/"la #grande fée du volcan#", /*spanish*/"una fuente de la Gran Hada", /*italian*/"la #fontana di una Fata radiosa#", /*german*/"in einer #Feen-Quelle#"},
    });

    hintTable[DMT_GREAT_FAIRY_FOUNTAIN] = HintText::Region({
                     // obscure text
                     Text{"a #Great Fairy Fountain#", /*french*/"la #grande fée de la montagne#", /*spanish*/"una fuente de la Gran Hada", /*italian*/"la #fontana di una Fata radiosa#", /*german*/"in einer #Feen-Quelle#"},
    });

    hintTable[ZF_GREAT_FAIRY_FOUNTAIN] = HintText::Region({
                     // obscure text
                     Text{"a #Great Fairy Fountain#", /*french*/"la #grande fée de la fontaine#", /*spanish*/"una fuente de la Gran Hada", /*italian*/"la #fontana di una Fata radiosa#", /*german*/"in einer #Feen-Quelle#"},
    });

    hintTable[GRAVEYARD_SHIELD_GRAVE] = HintText::Region({
                     // obscure text
                     Text{"a #grave with a free chest#", /*french*/"le #tombeau avec un trésor#", /*spanish*/"la #tumba con un cofre#", /*italian*/"una #tomba con un forziere#", /*german*/"in einem #Grab mit einer Truhe#"},
    });

    hintTable[GRAVEYARD_HEART_PIECE_GRAVE] = HintText::Region({
                     // obscure text
                     Text{"a chest spawned by #Sun's Song#", /*french*/"le #tombeau avec un mort#", /*spanish*/"la #tumba de la Canción del Sol#", /*italian*/"una #tomba con uno zombie solitario#", /*german*/"in einem Grab mit #einem Zombie#"},
    });

    hintTable[GRAVEYARD_COMPOSERS_GRAVE] = HintText::Region({
                     // obscure text
                     Text{"the #Composers' Grave#", /*french*/"la #tombe royale#", /*spanish*/"el #Panteón Real#", /*italian*/"la #tomba della famiglia reale#", /*german*/"im #Königsgrab#"},
    });

    hintTable[GRAVEYARD_DAMPES_GRAVE] = HintText::Region({
                     // obscure text
                     Text{"Dampé's Grave", /*french*/"la #tombe d'Igor#", /*spanish*/"la #tumba de Dampé#", /*italian*/"la #tomba di Danpei#", /*german*/"im #Grab des Totengräbers#"},
    });

    hintTable[DMT_COW_GROTTO] = HintText::Region({
                     // obscure text
                     Text{"a solitary #Cow#", /*french*/"la #grotte avec une vache#", /*spanish*/"una #vaca# solitaria", /*italian*/"una #grotta con una mucca solitaria#", /*german*/"nahe einer wohlhabenden #Kuh#"},
    });

    hintTable[HC_STORMS_GROTTO] = HintText::Region({
                     // obscure text
                     Text{"a sandy grotto with #fragile walls#", /*french*/"la #grotte avec des murs fragiles#", /*spanish*/"la arenosa gruta de #frágiles paredes#", /*italian*/"una grotta sabbiosa con #pareti friabili#", /*german*/"in einem Erdloch mit #brüchigen Wänden#"},
    });

    hintTable[HF_TEKTITE_GROTTO] = HintText::Region({
                     // obscure text
                     Text{"a pool guarded by a #Tektite#", /*french*/"l'#étang sous-terrain avec un Araknon#", /*spanish*/"un charco custodiado por un #Tektite#", /*italian*/"una pozza protetta da un #Tektite#", /*german*/"in einem #unterirdischen Schwimmbecken#"},
    });

    hintTable[HF_NEAR_KAK_GROTTO] = HintText::Region({
                     // obscure text
                     Text{"a #Big Skulltula# guarding a Gold one", /*french*/"la #grotte d'araignées#", /*spanish*/"una #gran Skulltula# custodiando una dorada", /*italian*/"una grotta con #un ragno grande e uno dorato#", /*german*/"nahe #zwei unterirdischen Skulltulas#"},
    });

    hintTable[HF_COW_GROTTO] = HintText::Region({
                     // obscure text
                     Text{"a grotto full of #spider webs#", /*french*/"la #grotte couverte de toiles d'araignées#", /*spanish*/"una gruta llena de #telarañas#", /*italian*/"una #grotta piena di ragnatele#", /*german*/"in einem Erdloch voller #Spinnenweben#"},
    });

    hintTable[KAK_REDEAD_GROTTO] = HintText::Region({
                     // obscure text
                     Text{"#ReDeads# guarding a chest", /*french*/"le tombeau de #deux morts#", /*spanish*/"los #ReDeads# que custodian un cofre", /*italian*/"una #grotta con due zombie#", /*german*/"in einem Erdloch mit #zwei Zombies#"},
    });

    hintTable[SFM_WOLFOS_GROTTO] = HintText::Region({
                     // obscure text
                     Text{"#Wolfos# guarding a chest", /*french*/"la #grotte iridescente#", /*spanish*/"los #Wolfos# que custodian un cofre", /*italian*/"una #grotta con due lupi#", /*german*/"in einem Erdloch mit #zwei Wolfos#"},
    });

    hintTable[GV_OCTOROK_GROTTO] = HintText::Region({
                     // obscure text
                     Text{"an #Octorok# guarding a rich pool", /*french*/"un #étang sous-terrain avec un Octorok#", /*spanish*/"un #Octorok# que custodia un lujoso charco", /*italian*/"una pozza piena di soldi (e un #Octorok# di guardia)", /*german*/"nahe eines wohlhabenden #Octoroks#"},
    });

    hintTable[DEKU_THEATER] = HintText::Region({
                     // obscure text
                     Text{"the #Lost Woods Stage#", /*french*/"le #théâtre sylvestre#", /*spanish*/"el #escenario del Bosque Perdido#", /*italian*/"il #teatro verde#", /*german*/"auf der #Waldbühne#"},
    });

    hintTable[ZR_OPEN_GROTTO] = HintText::Region({
                     // obscure text
                     Text{"a #generic grotto#", /*french*/"une #grotte avec un trésor#", /*spanish*/"una #cueva genérica#", /*italian*/"una delle nove #grotte uguali#", /*german*/"in einem #gewöhnlichen Erdloch#"},
    });

    hintTable[DMC_UPPER_GROTTO] = HintText::Region({
                     // obscure text
                     Text{"a #generic grotto#", /*french*/"une #grotte avec un trésor#", /*spanish*/"una #cueva genérica#", /*italian*/"una delle nove #grotte uguali#", /*german*/"in einem #gewöhnlichen Erdloch#"},
    });

    hintTable[DMT_STORMS_GROTTO] = HintText::Region({
                     // obscure text
                     Text{"a #generic grotto#", /*french*/"une #grotte avec un trésor#", /*spanish*/"una #cueva genérica#", /*italian*/"una delle nove #grotte uguali#", /*german*/"in einem #gewöhnlichen Erdloch#"},
    });

    hintTable[KAK_OPEN_GROTTO] = HintText::Region({
                     // obscure text
                     Text{"a #generic grotto#", /*french*/"une #grotte avec un trésor#", /*spanish*/"una #cueva genérica#", /*italian*/"una delle nove #grotte uguali#", /*german*/"in einem #gewöhnlichen Erdloch#"},
    });

    hintTable[HF_NEAR_MARKET_GROTTO] = HintText::Region({
                     // obscure text
                     Text{"a #generic grotto#", /*french*/"une #grotte avec un trésor#", /*spanish*/"una #cueva genérica#", /*italian*/"una delle nove #grotte uguali#", /*german*/"in einem #gewöhnlichen Erdloch#"},
    });

    hintTable[HF_OPEN_GROTTO] = HintText::Region({
                     // obscure text
                     Text{"a #generic grotto#", /*french*/"une #grotte avec un trésor#", /*spanish*/"una #cueva genérica#", /*italian*/"una delle nove #grotte uguali#", /*german*/"in einem #gewöhnlichen Erdloch#"},
    });

    hintTable[HF_SOUTHEAST_GROTTO] = HintText::Region({
                     // obscure text
                     Text{"a #generic grotto#", /*french*/"une #grotte avec un trésor#", /*spanish*/"una #cueva genérica#", /*italian*/"una delle nove #grotte uguali#", /*german*/"in einem #gewöhnlichen Erdloch#"},
    });

    hintTable[KF_STORMS_GROTTO] = HintText::Region({
                     // obscure text
                     Text{"a #generic grotto#", /*french*/"une #grotte avec un trésor#", /*spanish*/"una #cueva genérica#", /*italian*/"una delle nove #grotte uguali#", /*german*/"in einem #gewöhnlichen Erdloch#"},
    });

    hintTable[LW_NEAR_SHORTCUTS_GROTTO] = HintText::Region({
                     // obscure text
                     Text{"a #generic grotto#", /*french*/"une #grotte avec un trésor#", /*spanish*/"una #cueva genérica#", /*italian*/"una delle nove #grotte uguali#", /*german*/"in einem #gewöhnlichen Erdloch#"},
    });

    hintTable[HF_INSIDE_FENCE_GROTTO] = HintText::Region({
                     // obscure text
                     Text{"a #single Upgrade Deku Scrub#", /*french*/"une #grotte avec une peste Mojo#", /*spanish*/"una cueva con un #solitario mercader deku#", /*italian*/"una grotta con un #cespuglio affari solitario#", /*german*/"in einem Erdloch mit #einem Deku-Händler#"},
    });

    hintTable[LW_SCRUBS_GROTTO] = HintText::Region({
                     // obscure text
                     Text{"#2 Deku Scrubs# including an Upgrade one", /*french*/"une #grotte avec deux pestes Mojo#", /*spanish*/"una cueva con #dos mercaderes deku#", /*italian*/"una grotta con #due cespugli affari messi al contrario#", /*german*/"in einem Erdloch mit #zwei Deku-Händlern#"},
    });

    hintTable[COLOSSUS_GROTTO] = HintText::Region({
                     // obscure text
                     Text{"2 Deku Scrubs", /*french*/"une #grotte avec deux pestes Mojo#", /*spanish*/"una cueva con #dos mercaderes deku#", /*italian*/"una grotta con #due cespugli affari#", /*german*/"in einem Erdloch mit #zwei Deku-Händlern#"},
    });

    hintTable[ZR_STORMS_GROTTO] = HintText::Region({
                     // obscure text
                     Text{"2 Deku Scrubs", /*french*/"une #grotte avec deux pestes Mojo#", /*spanish*/"una cueva con #dos mercaderes deku#", /*italian*/"una grotta con #due cespugli affari#", /*german*/"in einem Erdloch mit #zwei Deku-Händlern#"},
    });

    hintTable[SFM_STORMS_GROTTO] = HintText::Region({
                     // obscure text
                     Text{"2 Deku Scrubs", /*french*/"une #grotte avec deux pestes Mojo#", /*spanish*/"una cueva con #dos mercaderes deku#", /*italian*/"una grotta con #due cespugli affari#", /*german*/"in einem Erdloch mit #zwei Deku-Händlern#"},
    });

    hintTable[GV_STORMS_GROTTO] = HintText::Region({
                     // obscure text
                     Text{"2 Deku Scrubs", /*french*/"une #grotte avec deux pestes Mojo#", /*spanish*/"una cueva con #dos mercaderes deku#", /*italian*/"una grotta con #due cespugli affari#", /*german*/"in einem Erdloch mit #zwei Deku-Händlern#"},
    });

    hintTable[LH_GROTTO] = HintText::Region({
                     // obscure text
                     Text{"3 Deku Scrubs", /*french*/"une #grotte avec trois pestes Mojo#", /*spanish*/"una cueva con #tres mercaderes deku#", /*italian*/"una grotta con #tre cespugli affari#", /*german*/"in einem Erdloch mit #drei Deku-Händlern#"},
    });

    hintTable[DMC_HAMMER_GROTTO] = HintText::Region({
                     // obscure text
                     Text{"3 Deku Scrubs", /*french*/"une #grotte avec trois pestes Mojo#", /*spanish*/"una cueva con #tres mercaderes deku#", /*italian*/"una grotta con #tre cespugli affari#", /*german*/"in einem Erdloch mit #drei Deku-Händlern#"},
    });

    hintTable[GC_GROTTO] = HintText::Region({
                     // obscure text
                     Text{"3 Deku Scrubs", /*french*/"une #grotte avec trois pestes Mojo#", /*spanish*/"una cueva con #tres mercaderes deku#", /*italian*/"una grotta con #tre cespugli affari#", /*german*/"in einem Erdloch mit #drei Deku-Händlern#"},
    });

    hintTable[LLR_GROTTO] = HintText::Region({
                     // obscure text
                     Text{"3 Deku Scrubs", /*french*/"une #grotte avec trois pestes Mojo#", /*spanish*/"una cueva con #tres mercaderes deku#", /*italian*/"una grotta con #tre cespugli affari#", /*german*/"in einem Erdloch mit #drei Deku-Händlern#"},
    });

    hintTable[ZR_FAIRY_GROTTO] = HintText::Region({
                     // obscure text
                     Text{"a small #Fairy Fountain#", /*french*/"une #fontaine de fées#", /*spanish*/"una pequeña #fuente de hadas#", /*italian*/"una #fontana delle fate#", /*german*/"in einem #Feen-Brunnen#"},
    });

    hintTable[HF_FAIRY_GROTTO] = HintText::Region({
                     // obscure text
                     Text{"a small #Fairy Fountain#", /*french*/"une #fontaine de fées#", /*spanish*/"una pequeña #fuente de hadas#", /*italian*/"una #fontana delle fate#", /*german*/"in einem #Feen-Brunnen#"},
    });

    hintTable[SFM_FAIRY_GROTTO] = HintText::Region({
                     // obscure text
                     Text{"a small #Fairy Fountain#", /*french*/"une #fontaine de fées#", /*spanish*/"una pequeña #fuente de hadas#", /*italian*/"una #fontana delle fate#", /*german*/"in einem #Feen-Brunnen#"},
    });

    hintTable[ZD_STORMS_GROTTO] = HintText::Region({
                     // obscure text
                     Text{"a small #Fairy Fountain#", /*french*/"une #fontaine de fées#", /*spanish*/"una pequeña #fuente de hadas#", /*italian*/"una #fontana delle fate#", /*german*/"in einem #Feen-Brunnen#"},
    });

    hintTable[GF_STORMS_GROTTO] = HintText::Region({
                     // obscure text
                     Text{"a small #Fairy Fountain#", /*french*/"une #fontaine de fées#", /*spanish*/"una pequeña #fuente de hadas#", /*italian*/"una #fontana delle fate#", /*german*/"in einem #Feen-Brunnen#"},
    });

    /*--------------------------
    |      JUNK HINT TEXT      |
    ---------------------------*/

    hintTable[JUNK01] = HintText::Junk({
                     // obscure text
                     Text{"Remember to check your 3DS battery level and save often.", /*french*/"Surveillez votre batterie 3DS et sauvegardez souvent!", /*spanish*/"No te olvides de revisar la batería de la 3DS y guarda partida de vez en cuando.", /*italian*/"Ricorda di controllare la batteria del 3DS e di salvare spesso.", /*german*/"Denk daran, regelmäßig den Akku deines 3DS zu überprüfen und häufig zu #speichern#."},
    });

    hintTable[JUNK02] = HintText::Junk({
                     // obscure text
                     Text{"They say you must read the names of \"Special Deal\" shop items carefully.", /*french*/"Selon moi, les « Offres spéciales » sont parfois trompeuses... Lisez attentivement!", /*spanish*/"Según dicen, se debería prestar atención a los nombres de las ofertas especiales.", /*italian*/"Ho sentito dire che è bene prestare molta attenzione ai nomi delle offerte speciali.", /*german*/"Man erzählt sich, die Namen von \"Sonderangeboten\" sorgfältig zu lesen, wäre eine gute Idee."},
    });

    hintTable[JUNK03] = HintText::Junk({ // SFX: Zelda gasp
                     // obscure text
                     Text{"{563}"} + Text{"They say that Zelda is a poor leader.", /*french*/"Selon moi, Zelda ne ferait pas un bon monarque.", /*spanish*/"Según dicen, Zelda es mala líder.", /*italian*/"Ho sentito dire che Zelda non è brava a governare.", /*german*/"Man erzählt sich, Zelda sei eine schlechte Anführerin."},
    });

    hintTable[JUNK04] = HintText::Junk({
                     // obscure text
                     Text{"These hints can be quite useful. This is an exception.", /*french*/"Ces indices sont très utiles, à l'exception de celui-ci.", /*spanish*/"Las pistas suelen servir de ayuda. En cambio, esta no.", /*italian*/"Questi indizi sono molto utili. Io sono l'eccezione che conferma la regola.", /*german*/"Die Hinweise von uns Mythensteinen können echt nützlich sein. Dies ist eine Ausnahme."},
    });

    hintTable[JUNK05] = HintText::Junk({ // SFX: Lizalfos cry
                     // obscure text
                     Text{"{299}"} + Text{"They say that the Lizalfos in Dodongo's Cavern like to play in lava.", /*french*/"Selon moi, les Lézalfos de la caverne Dodongo aiment patauger dans la lave.", /*spanish*/"Según dicen, a los Lizalfos de la Cueva de los Dodongos les gusta jugar en la lava.", /*italian*/"Ho sentito dire che i Lizalfos nella caverna dei Dodongo adorano giocare nella lava.", /*german*/"Man erzählt sich, die Lizalfos in Dodongos Höhle würden gerne in Lava planschen."},
    });

    hintTable[JUNK06] = HintText::Junk({
                     // obscure text
                     Text{"They say that all the Zora drowned in Wind Waker.", /*french*/"Selon moi, les Zoras se sont noyés dans Wind Waker.", /*spanish*/"Según dicen, en Wind Waker todos los zora se ahogaron.", /*italian*/"Ho sentito dire che in Wind Waker tutti gli Zora sono annegati.", /*german*/"Man erzählt sich, in Wind Waker wären alle Zoras ertrunken."},
    });

    hintTable[JUNK07] = HintText::Junk({ // SFX: Goron waking up
                     // obscure text
                     Text{"{36C}"} + Text{"If Gorons eat rocks, does that mean I'm in danger?", /*french*/"Ne dis pas au Gorons que je suis ici. Ils mangent des roches, tu sais!", /*spanish*/"Si los Goron se tragan las piedras, ¿no me hace ser una especia vulnarable o algo así", /*italian*/"Ma se i Goron mangiano pietre... non è che sono in pericolo?", /*german*/"Da Goronen Steine essen... bedeutet das, dass ich in Gefahr bin?"},
    });

    hintTable[JUNK08] = HintText::Junk({// SFX: Ganondorf reflecting light ball
                     // obscure text
                     Text{"'Member when Ganon was a blue pig?^{43A}I 'member.", /*french*/"Dans mon temps, Ganon était un cochon bleu...^{43A}Pff! Les jeunes de nos jours, et leur Ganondorf!", /*spanish*/"¿T'acuerdas cuando Ganon era un cerdo azul?^{43A}Qué tiempos, chico.", /*italian*/"Mi ricordo i bei vecchi tempi, quando Ganon era un cinghiale blu.^{43A}Ah, i giovani d'oggi e il loro Ganondorf!", /*german*/"Weißte' noch als Ganon nur 'n blaues Schwein war?^{43A}Damals war alles besser, kein unnötiger Schnickschnack!"},
    });

    hintTable[JUNK09] = HintText::Junk({
                     // obscure text
                     Text{"One who does not have Triforce can't go in.", /*french*/"Ceux sans Triforce doivent rebrousser chemin.", /*spanish*/"Aquel que no porte la Trifuerza no podrá pasar.", /*italian*/"Coloro che non hanno la Triforza non potranno passare.", /*german*/"One who does not have Triforce can't go in.^Übersetzungen waren nicht immer von Priorität."},
    });

    hintTable[JUNK10] = HintText::Junk({
                     // obscure text
                     Text{"Save your future, end the Happy Mask Salesman.", /*french*/"Selon moi, tu t'éviteras des jours de malheur si tu vaincs le vendeur de masques...", /*spanish*/"Salva tu futuro, acaba con el dueño de La Máscara Feliz.", /*italian*/"Salva il tuo futuro! Fai fuori il venditore di maschere!", /*german*/"Rette deine Zukunft, stoppe den Maskenhändler solange du noch kannst."},
    });

    hintTable[JUNK11] = HintText::Junk({
                     // obscure text
                     Text{"Glitches are a pathway to many abilities some consider to be... Unnatural.", /*french*/"Les glitchs sont un moyen d'acquérir de nombreuses facultés considérées par certains comme... contraire à la nature.", /*spanish*/"Los glitches son el camino a muchas habilidades que varios consideran... nada natural.", /*italian*/"I glitch sono la via per acquistare molte capacità da alcuni ritenute ingiustamente non naturali.", /*german*/"Man erzählt sich, Glitches würden Fähigkeiten erlauben, die manch Einer als... unnatürlich bezeichnen würde."},
    });

    hintTable[JUNK12] = HintText::Junk({ // SFX: Ganondorf laugh
                     // obscure text
                     Text{"{437}"} + Text{"I'm stoned. Get it?", /*french*/"Allez, roche, papier, ciseau...&Roche.", /*spanish*/"Me he quedado de piedra. ¿Lo pillas?", /*italian*/"AH! Non mi spaventare così. Mi hai proprio pietrificato!", /*german*/"Ich bin stoned. Verstehste'?"},
    });

    hintTable[JUNK13] = HintText::Junk({ // SFX: Owl flutter
                     // obscure text
                     Text{"{396}"} + Text{"Hoot! Hoot! Would you like me to repeat that?", /*french*/"Hou hou! Veux-tu que je répète tout ça?", /*spanish*/"¡Buuu, buuu! ¿Te lo vuelvo a repetir?", /*italian*/"Uh uuh! Uh uuh! Vuoi che ti ripeta cos'ho appena detto?", /*german*/"Uhuuu! Uhu! Soll ich mich noch einmal wiederholen?"},
    });

    hintTable[JUNK14] = HintText::Junk({ // SFX: Goron sitting down
                     // obscure text
                     Text{"{36D}"} + Text{"Gorons are stupid. They eat rocks.", /*french*/"Les Gorons sont des vraies têtes dures.", /*spanish*/"Los Goron son tontos. Se comen las piedras.", /*italian*/"I Goron sono stupidi. Hanno proprio la testa dura come la roccia.", /*german*/"Goronen sind bescheuert. Sie essen Steine!"},
    });

    hintTable[JUNK15] = HintText::Junk({ // SFX: Ingo whips horse
                     // obscure text
                     Text{"{541}"} + Text{"They say that Lon Lon Ranch prospered under Ingo.", /*french*/"Selon moi, le ranch Lon Lon était plus prospère sous Ingo.", /*spanish*/"Según dicen, el Rancho Lon Lon prosperó gracias a Ingo.", /*italian*/"Ho sentito dire che la Fattoria Lon Lon è prosperata molto grazie a Ingo.", /*german*/"Man erzählt sich, die Lon Lon-Farm floriere seit Basil das Sagen hat."},
    });

    hintTable[JUNK16] = HintText::Junk({ // SFX: Get rupee
                     // obscure text
                     Text{"{488}"} + Text{"The single rupee is a unique item.", /*french*/"Nul objet n'est plus unique que le rubis vert.", /*spanish*/"La rupia de uno es un objeto singular.", /*italian*/"La singola rupia verde è un oggetto più unico che raro.", /*german*/"Der einzelne Rubin ist ein einzigartiger Gegenstand."},
    });

    hintTable[JUNK17] = HintText::Junk({
                     // obscure text
                     Text{"Without the Lens of Truth, the Treasure Chest Mini-Game is a 1 out of 32 chance.^Good luck!", /*french*/"Gagner la chasse aux trésors est 1 chance sur 32.^Bonne chance!", /*spanish*/"Sin la Lupa de la Verdad, ganarías 1/32 veces en el Cofre del Tesoro.^¡Buena suerte con ello!", /*italian*/"Senza la lente della verità, la probabilità di vincere il gioco della sala della fortuna è 1 su 32.^Buona fortuna!", /*german*/"Ohne das Auge der Wahrheit bei der Truhenlotterie zu gewinnen, ist eine Wahrscheinlichkeit von 1 zu 32.^Viel Glück!"},
    });

    hintTable[JUNK18] = HintText::Junk({
                     // obscure text
                     Text{"Use bombs wisely.", /*french*/"Utilise les bombes avec précaution.", /*spanish*/"No desperdicies las bombas.", /*italian*/"Non sprecare bombe.", /*german*/"Setze Bomben mit Bedacht ein."},
    });

    hintTable[JUNK19] = HintText::Junk({ // SFX: Volvagia hit with hammer
                     // obscure text
                     Text{"{342}"} + Text{"They say that Volvagia hates splinters.", /*french*/"Selon moi, Volvagia déteste les échardes.", /*spanish*/"Según dicen, Volvagia le teme a las astillas.", /*italian*/"Ho sentito dire che Varubaja odia le schegge.", /*german*/"Man erzählt sich, Volvagia habe eine Abneigung gegenüber Splittern."},
    });

    hintTable[JUNK20] = HintText::Junk({
                     // obscure text
                     Text{"They say that funky monkeys can be spotted on Friday.", /*french*/"Selon moi, des capucins coquins sortent le vendredi.", /*spanish*/"Según dicen, en los viernes puedes hallar monos marchosos.", /*italian*/"Ho sentito dire che di venerdì si possono vedere scimmie stravaganti.", /*german*/"Man erzählt sich, man könne flippige Affen jeden Freitag sichten."},
    });

    hintTable[JUNK21] = HintText::Junk({
                     // obscure text
                     Text{"I found you, faker!", /*french*/"Ah-ha! Je t'ai trouvé!", /*spanish*/"¡Ahí estás, impostor!", /*italian*/"Ti ho trovato, impostore!", /*german*/"Ich habe dich gefunden, Schwindler!"},
    });

    hintTable[JUNK22] = HintText::Junk({
                     // obscure text
                     Text{"They say the Groose is loose.", /*french*/"Selon moi, Hergo est le vrai héros.", /*spanish*/"Según dicen, Malton es un espanto.", /*italian*/"Ho sentito dire che Bado è proprio un baro!", /*german*/"Man erzählt sich, der Bado sei los."},
    });

    hintTable[JUNK23] = HintText::Junk({ // SFX: Cursor selection
                     // obscure text
                     Text{"{4D2}"} + Text{"They say that players who select the \"ON\" option for \"MOTION CONTROL\" are the real \"Zelda players!\"", /*french*/"Selon moi, ceux qui utilisent les contrôles gyroscopiques sont les VRAIS joueurs.", /*spanish*/"Según dicen, aquellos que juegan usando el control por movimiento son los verdaderos jugadores de Zelda.", /*italian*/"Ho sentito dire che solo coloro che impostano i sensori di movimento su \"Sì\" sono i veri giocatori di Zelda!", /*german*/"Man erzählt sich, Spieler die die \"Bewegungssteuerung\" aktivieren, wären die wahren \"Zelda-Spieler\"."},
    });

    hintTable[JUNK24] = HintText::Junk({ // SFX: Sheik falls after being thrown
                     // obscure text
                     Text{"{55D}"} + Text{"What happened to Sheik?", /*french*/"Donc... Qu'est-ce qui arrive avec Sheik?", /*spanish*/"¿Qué la habrá pasado a Sheik?", /*italian*/"Cosa sarà successo a Sheik?", /*german*/"Was ist wohl mit Shiek passiert?"},
    });

    hintTable[JUNK25] = HintText::Junk({ // SFX: Phantom Ganon laugh
                     // obscure text
                     Text{"{446}"} + Text{"L2P @.", /*french*/"Arrête de lire les indices et joue comme un grand, @.", /*spanish*/"Mira que eres novato, @.", /*italian*/"Sei proprio un novellino, @.", /*german*/"Lern einfach mal Spielen, @."},
    });

    hintTable[JUNK26] = HintText::Junk({
                     // obscure text
                     Text{"I've heard you can cheat at Sploosh Kaboom.", /*french*/"Selon moi, il y a une carte aux trésors à Mercantîle... Duh!", /*spanish*/"He oído por ahí que puedes hacer trampa en el Sploosh Kaboom.", /*italian*/"Si dice che si possa barare al gioco di \"Sploosh\" e \"Kaboom\".", /*german*/"Ich habe gehört, man könne bei Sploosh Kaboom schummeln."},
    });

    hintTable[JUNK27] = HintText::Junk({
                     // obscure text
                     Text{"I'm Lonk from Pennsylvania.", /*french*/"Je suis Lonk, le héros de Pennsylvanie!", /*spanish*/"Soy Lonk, de Pensilvania.", /*italian*/"Sono Lonk, dalla Pennsylvania.", /*german*/"Ich bin Lonk aus Pennsylvania."},
    });

    hintTable[JUNK28] = HintText::Junk({
                     // obscure text
                     Text{"I bet you'd like to have more bombs.", /*french*/"Je parie que tu veux plus de bombes.", /*spanish*/"Me apuesto a que quisieras tener más bombas.", /*italian*/"Scommetto ti piacerebbe avere più bombe, eh?", /*german*/"Möchtest du zur Strafe mehr Bomben tragen können?"},
    });

    hintTable[JUNK29] = HintText::Junk({
                     // obscure text
                     Text{"When all else fails, use Fire.", /*french*/"Quand rien ne marche, utilise le feu.", /*spanish*/"Cuando nada funcione, usa el fuego.", /*italian*/"Se nient'altro funziona, usa il fuoco.", /*german*/"Wenn nichts weiterhilft, nutze Feuer."},
    });

    hintTable[JUNK30] = HintText::Junk({
                     // obscure text
                     Text{"Here's a hint, @. Don't be bad.", /*french*/"Selon moi, la #Triforce# n'est pas dans le jeu... Duh!", /*spanish*/"Aquí tienes una pista, @: deja de ser manco.", /*italian*/"Eccoti un indizio, @: gioca meglio.", /*german*/"Hier ist ein Hinweis, @. Sei einfach nicht schlecht, das hat mir immer geholfen."},
    });

    hintTable[JUNK31] = HintText::Junk({ // SFX: Phantom Ganon laugh
                     // obscure text
                     Text{"{446}"} + Text{"Game Over. Return of Ganon.", /*french*/"Partie terminée. RETOUR DE GANON.", /*spanish*/"Fin de la partida. El regreso de Ganon.", /*italian*/"Game Over. Ritorno di Ganon.", /*german*/"Game Over. Ganons Rückkehr."},
    });

    hintTable[JUNK32] = HintText::Junk({
                     // obscure text
                     Text{"May the way of the Hero lead to the Triforce.", /*french*/"Que le chemin du héros te mène à la Triforce.", /*spanish*/"Puede que la senda del héroe te lleve hacia la Trifuerza.", /*italian*/"Che il cammino dell'eroe possa condurre alla Triforza!", /*german*/"Möge der Weg des Helden zum Triforce führen."},
    });

    hintTable[JUNK33] = HintText::Junk({
                     // obscure text
                     Text{"Can't find an item? Scan an Amiibo.", /*french*/"Tu cherches de quoi? Utilise un Amiibo!", /*spanish*/"¿No encuentras algo? Escanea un amiibo.", /*italian*/"Non riesci a trovare un oggetto? Scansiona un Amiibo!", /*german*/"Du kannst einen Gegenstand nicht finden? Scanne ein Amiibo!"},
    });

    hintTable[JUNK34] = HintText::Junk({
                     // obscure text
                     Text{"They say this game has just a few glitches.", /*french*/"Selon moi, ce jeu est complètement exempt de glitchs.", /*spanish*/"Dicen que este juego apenas tiene glitches.", /*italian*/"Ho sentito dire che di glitch questo gioco ne ha proprio pochi.", /*german*/"Man erzählt sich, dieses Spiel habe nur ein paar Glitches."},
    });

    hintTable[JUNK35] = HintText::Junk({ // SFX: Bombchu Bowling target hit
                     // obscure text
                     Text{"{22A}"} + Text{"BRRING BRRING This is Ulrira. Wrong number?", /*french*/"DRING DRING!! Pépé le Ramollo à l'appareil... Quoi? Faux numéro?", /*spanish*/"¡Ring! ¡Ring! Al habla Ulrira. ¿Me he equivocado de número?", /*italian*/"DRIIIN! DRIIIN! Pronto? Sono Ulrira. Hai sbagliato numero?", /*german*/"TUUUUT! TUUUUT! Ja? Hier Ulrira! Muss sich wohl verwählt haben."},
    });

    hintTable[JUNK36] = HintText::Junk({ // This text will be green
                     // obscure text
                     Text{"#Tingle Tingle Kooloo Limpah!#", /*french*/"#Tingle! Tingle! Kooloolin... Pah!#", /*spanish*/"#Tingle, Tingle, Kurulín... ¡PA!#", /*italian*/"#Tingle, Tingle!&Kururìn-PA!#", /*german*/"#Tingle, Tingle! Kuuluu-Limpah!#"},
    });

    hintTable[JUNK37] = HintText::Junk({
                     // obscure text
                     Text{"L is real 2401", /*french*/"L is real 2401", /*spanish*/"L es real 2401.", /*italian*/"L is real 2401", /*german*/"L is real 2401... Ein Mysterium."},
    });

    hintTable[JUNK38] = HintText::Junk({ // SFX: Ganondorf reflecting light ball
                     // obscure text
                     Text{"{43A}"} + Text{"They say that Ganondorf will appear in the next Mario Tennis.", /*french*/"Selon moi, Ganondorf sera la nouvelle recrue dans Mario Tennis.", /*spanish*/"Según dicen, Ganondorf estará en el próximo Mario Tennis.", /*italian*/"Ho sentito dire che Ganondorf apparirà nel prossimo Mario Tennis.", /*german*/"Man erzählt sich, Ganondorf werde im nächsten Mario Tennis vorkommen."},
    });

    hintTable[JUNK39] = HintText::Junk({ // SFX: Goron waking up
                     // obscure text
                     Text{"{36C}"} + Text{"Medigoron sells the earliest Breath of the Wild demo.", /*french*/"Selon moi, Medigoron vend une démo de #Breath of the Wild#.", /*spanish*/"Medigoron vende la primera demo del Breath of the Wild.", /*italian*/"Ho sentito dire che Medigoron vende la prima demo di Breath of the Wild.", /*german*/"Medigoron verkauft eine frühe Breath of the Wild Demo."},
    });

    hintTable[JUNK40] = HintText::Junk({
                     // obscure text
                     Text{"Can you move me? I don't get great service here.", /*french*/"Peux-tu me déplacer? J'ai pas une bonne réception ici.", /*spanish*/"¿Puedes llevarme a otro lado? Aquí nadie me presta atención.", /*italian*/"Potrebbe spostarmi? Non ricevo un grande servizio qui.", /*german*/"Kannst du mich etwas bewegen? Ich habe schlechten Empfang."},
    });

    hintTable[JUNK41] = HintText::Junk({
                     // obscure text
                     Text{"They say if you use Strength on the truck, you can find Mew.", /*french*/"Selon moi, #Mew# se trouve dessous le camion... Duh!", /*spanish*/"Según dicen, puedes hallar un Mew usando Fuerza contra el camión de Ciudad Carmín.", /*italian*/"Ho sentito dire che usando Forza sul camioncino, puoi trovare Mew.", /*german*/"Man erzählt sich, Mew wäre unter dem LKW bei der M.S. Anne zu finden. Man benötigt Stärke um ihn zu verschieben."},
    });

    hintTable[JUNK42] = HintText::Junk({ // SFX: Gossip stone growing
                     // obscure text
                     Text{"{240}"} + Text{"I'm a helpful hint Gossip Stone!^See, I'm helping.", /*french*/"Salut! Je suis une pierre de bons conseils!^Tiens, tu vois? J'aide bien, hein?", /*spanish*/"Soy una Piedra Sheikah muy útil.^¡Mira cómo te ayudo!", /*italian*/"Sono un'utile pietra del pettegolezzo!^Non vedi, ti sto aiutando!", /*german*/"Ich bin ein hilfreicher Mythenstein!^Siehste'? Ich bin hilfreich!"},
    });

    hintTable[JUNK43] = HintText::Junk({ // SFX: Zelda opens gate
                     // obscure text
                     Text{"{562}"} + Text{"Dear @, please come to the castle. I've baked a cake for you.&Yours truly, Princess Zelda.", /*french*/"Mon très cher @:&Viens vite au château, je t'ai préparé un délicieux gâteau...&À bientôt, Princesse Zelda", /*spanish*/"Querido @: Por favor, ven al castillo. He hecho una tarta para ti.&Sinceramente tuya: Princesa Zelda.", /*italian*/"Caro @, vieni al castello, ho preparato una torta per te.&Con affetto, la Principessa Zelda.", /*german*/"Lieber @!&Komm mich doch einmal im Schloss besuchen! Der Kuchen steht bereit!&In Freundschaft, Prinzessin Zelda."},
    });

    hintTable[JUNK44] = HintText::Junk({
                     // obscure text
                     Text{"They say all toasters toast toast.", /*french*/"Selon moi, les grille-pains grillent du pain.", /*spanish*/"Según dicen, todas las tostadoras tostan tostadas tostadas.", /*italian*/"Ho sentito dire che tutti i tostapane tostano pane.", /*german*/"Man erzählt sich, alle Toaster würden Toast toasten."},
    });

    hintTable[JUNK45] = HintText::Junk({
                     // obscure text
                     Text{"You thought it would be a useful hint, but it was me, junk hint!", /*french*/"Tu t'attendais à un bon indice... Mais c'était moi, un mauvais indice!", /*spanish*/"Je... Creeías que iba a ser una piedra de utilidad, ¡pero no, era yo, la piedra de la agonía!", /*italian*/"Pensavi che fossi un indizio utile, invece ero io, Dato Inutile Oltraggioso!", /*german*/"Du dachtest dies wäre ein nützlicher Hinweis. Doch hier bin ich, der Schrotthinweis!"},
    });

    hintTable[JUNK46] = HintText::Junk({ // SFX: Gossip stone growing
                     // obscure text
                     Text{"{240}"} + Text{"They say that quest guidance can be found at a talking rock.", /*french*/"Selon moi, des #indices# se trouvent auprès d'une pierre parlante... Duh!", /*spanish*/"Según dicen, puedes consultarle ayuda a rocas parlanchinas.", /*italian*/"Ho sentito dire che le pietre parlanti possono aiutare gli avventurieri.", /*german*/"Man erzählt sich, sprechende Steine würden dich bei deinem Abenteuer unterstützen."},
    });

    hintTable[JUNK47] = HintText::Junk({
                     // obscure text
                     Text{"They say that the final item you're looking for can be found somewhere in Hyrule.", /*french*/"Selon moi, le #dernier objet# se trouve quelque part dans Hyrule... Duh!", /*spanish*/"Según dicen, el último objeto que te falte puede estar en cualquier rincón de Hyrule.", /*italian*/"Ho sentito dire che quell'oggetto che stai cercando si trova ad Hyrule da qualche parte.", /*german*/"Man erzählt sich, der Gegenstand nachdem du gerade suchst, wäre irgendwo in Hyrule zu finden."},
    });

    Text tempMweepHint = Text{""};
    for (int i = 12; i > 0; i--) {
      tempMweepHint = tempMweepHint + "{565}" + Text{"Mweep.", /*french*/"Mwip.", /*spanish*/"Mweep.", /*italian*/"Mweep.", /*german*/"Miep."} + (i > 1 ? "^" : "");
    }
    hintTable[JUNK48] = HintText::Junk({ // SFX: Mweep
                     // obscure text
                     tempMweepHint,
    });

    hintTable[JUNK49] = HintText::Junk({ // SFX: Barinade's Bari killed
                     // obscure text
                     Text{"{3B4}"} + Text{"They say that Barinade fears Deku Nuts.", /*french*/"Selon moi, Barinade a la frousse des noix Mojo.", /*spanish*/"Según dicen, lo que más teme a Barinade son las nueces deku.", /*italian*/"Ho sentito dire che Cnidade teme le noci Deku.", /*german*/"Man erzählt sich, Barinade habe Angst vor Deku-Nüssen."},
    });

    hintTable[JUNK50] = HintText::Junk({ // SFX: Flare Dancer laugh
                     // obscure text
                     Text{"{3F1}"} + Text{"They say that Flare Dancers do not fear Goron-crafted blades.", /*french*/"Selon moi, le danse-flamme n'a pas peur des armes de Goron.", /*spanish*/"Según dicen, los Bailafuegos no le temen a las armas forjadas por Gorons.", /*italian*/"Ho sentito dire che i Fiammerini non temono le lame forgiate dai Goron.", /*german*/"Man erzählt sich, dass Flammenderwische keine Angst vor goronengeschmiedeten Klingen haben sollen."},
    });

    hintTable[JUNK51] = HintText::Junk({ // SFX: Morpha jumps on water
                     // obscure text
                     Text{"{367}"} + Text{"They say that Morpha is easily trapped in a corner.", /*french*/"Selon moi, Morpha est facilement coincé.", /*spanish*/"Según dicen, puedes atrapar a Morpha con facilidad en una esquina.", /*italian*/"Ho sentito dire che è facile intrappolare Morpha in un angolo.", /*german*/"Man erzählt sich, Morpha wäre leicht in einer Ecke festzuhalten."},
    });

    hintTable[JUNK52] = HintText::Junk({ // SFX: Bongo's hand hurt
                     // obscure text
                     Text{"{3DA}"} + Text{"They say that Bongo Bongo really hates the cold.", /*french*/"Selon moi, Bongo Bongo a facilement froid aux doigts.", /*spanish*/"Según dicen, Bongo Bongo odia a muerte el frío.", /*italian*/"Ho sentito dire che Bongo Bongo odia a morte il freddo.", /*german*/"Man erzählt sich, Bongo Bongo würde die Kälte wirklich verabscheuen."},
    });

    hintTable[JUNK53] = HintText::Junk({ // SFX: Sword put away
                     // obscure text
                     Text{"{0F4}"} + Text{"They say that your sword is most powerful when you put it away.", /*french*/"Selon moi, ton épée est à pleine puissance quand tu la rengaines.", /*spanish*/"Según dicen, tu espada se vuelve más poderosa si la guardas.", /*italian*/"Ho sentito dire che la spada è molto più potente quando è nel fodero.", /*german*/"Man erzählt sich, dein Schwert wäre am Mächtigsten, würde es in die Scheide zurückgesteckt."},
    });

    hintTable[JUNK54] = HintText::Junk({
                     // obscure text
                     Text{"They say that bombing the hole Volvagia last flew into can be rewarding.", /*french*/"Selon moi, le trou où se creuse Volvagia est vulnérable aux bombes.", /*spanish*/"Según dicen, trae buena suerte colocar una bomba en el último agujero de donde salió Volvagia.", /*italian*/"Ho sentito dire che porta bene buttare bombe sull'ultima buca in cui si è infilato Varubaja.", /*german*/"Man erzählt sich, das Loch indem Volvagia zuletzt verschwand, mit Bomben anzugreifen, könne lohnenswert sein."},
    });

    hintTable[JUNK55] = HintText::Junk({ // SFX: Deku nut flash
                     // obscure text
                     Text{"{11D}"} + Text{"They say that invisible ghosts can be exposed with Deku Nuts.", /*french*/"Selon moi, des fantômes invisibles apparaissent avec des noix Mojo.", /*spanish*/"Según dicen, puedes exponer a los espectros invisibles con nueces deku.", /*italian*/"Ho sentito dire che puoi far apparire i fantasmi invisibili usando noci Deku.", /*german*/"Man erzählt sich, unsichtbare Geister könnten mit Deku-Nüssen sichtbar gemacht werden."},
    });

    hintTable[JUNK56] = HintText::Junk({
                     // obscure text
                     Text{"They say that the real Phantom Ganon is bright and loud.", /*french*/"Selon moi, le vrai spectre de Ganon est clair et bruyant.", /*spanish*/"Según dicen, el verdadero Ganon Fantasma es brillante y ruidoso.", /*italian*/"Ho sentito dire che il vero Spettro Ganon è brillante e rumoroso.", /*german*/"Man erzählt sich, der echte Phantom-Ganon wäre hell und laut."},
    });

    hintTable[JUNK57] = HintText::Junk({
                     // obscure text
                     Text{"They say that walking backwards is very fast.", /*french*/"Selon moi, tu fais marche arrière très rapidement pour un héros.", /*spanish*/"Según dicen, es más rápido caminar hacia atrás.", /*italian*/"Ho sentito dire che camminando all'indietro si va molto veloci.", /*german*/"Man erzählt sich, rückwärts zu laufen wäre äußerst schnell."},
    });

    hintTable[JUNK58] = HintText::Junk({
                     // obscure text
                     Text{"They say that leaping above the Market entrance enriches most children.", /*french*/"Selon moi, les enfants riches se pavanent en haut du pont-levis.", /*spanish*/"Según dicen, saltar por las cadenas a la entrada de la plaza enriquece a muchos chiquillos.", /*italian*/"Ho sentito dire che saltare sopra il ponte levatoio rende i bambini ricchi.", /*german*/"Man erzählt sich, über dem Eingang des Marktes herumzuspringen, würde Kinder bereichern."},
    });

    hintTable[JUNK59] = HintText::Junk({ // SFX: Ingo lost race
                     // obscure text
                     Text{"{540}"} + Text{"They say Ingo is not very good at planning ahead.", /*french*/"Selon moi, Ingo ne fait pas un très bon geôlier.", /*spanish*/"Según dicen, a Ingo no se le da especialmente bien planificar con antelación.", /*italian*/"Ho sentito dire che Ingo non è bravo a fare piani.", /*german*/"Man erzählt sich, Basils Zukunftsplanung sei mangelhaft."},
    });

    hintTable[JUNK60] = HintText::Junk({ // SFX: Get small item from chest
                     // obscure text
                     Text{"{4B6}"} + Text{"You found a Spiritual Stone! By which I mean, I worship Nayru.", /*french*/"Vous avez trouvé une pierre spirituelle! En effet, je vénère la déesse Hylia.", /*spanish*/"¡Has encontrado una piedra espiritual! Es que le rindo culto a Nayru...", /*italian*/"Hai trovato una pietra spirituale! Sai com'è, io venero Nayru.", /*german*/"Du hast einen Heiligen Stein gefunden! Ich meine..., ich bin sozusagen ein Geistlicher da ich Nayru vergöttere."},
    });

    hintTable[JUNK61] = HintText::Junk({
                     // obscure text
                     Text{"They say that a flying strike with a Deku Stick is no stronger than a grounded one.", /*french*/"Selon moi, un coup de bâton sauté n'est pas meilleur qu'au sol.", /*spanish*/"Según dicen, los golpes aéreos con palos deku son tan fuertes como los normales.", /*italian*/"Ho sentito dire che un colpo aereo con un ramo Deku non è affatto più forte di uno normale.", /*german*/"Man erzählt sich, ein fliegender Streich mit Deku-Stäben, sei nicht stärker als ein bodenständiger."},
    });

    hintTable[JUNK62] = HintText::Junk({ // SFX: Zelda sigh
                     // obscure text
                     Text{"Open your eyes.^Open your eyes.^{554}Wake up, @.", /*french*/"Réveille-toi...^Réveille-toi.^{554}Ouvre les yeux, @.", /*spanish*/"Abre los ojos...^Abre los ojos...^{554}Despierta, @...", /*italian*/"Svegliati...^Svegliati...^{554}Apri gli occhi, @...", /*german*/"Öffne die Augen...^Öffne die Augen...^{554}Wach auf, @."},
    });

    hintTable[JUNK63] = HintText::Junk({
                     // obscure text
                     Text{"They say that the Nocturne of Shadow can bring you very close to Ganon.", /*french*/"Selon moi, le nocturne de l'ombre peut t'amener très près de Ganon.", /*spanish*/"Según dicen, el Nocturno de la sombra te puede acercar mucho a Ganon.", /*italian*/"Ho sentito dire che il Notturno delle ombre può portarti molto vicino a Ganon.", /*german*/"Man erzählt sich, die Nocturne des Schattens bringe dich in die Nähe von Ganon."},
    });

    hintTable[JUNK64] = HintText::Junk({
                     // obscure text
                     Text{"They say that Twinrova always casts the same spell the first three times.", /*french*/"Selon moi, Twinrova lance toujours les mêmes trois premiers sorts.", /*spanish*/"Según dicen, Birova siempre lanza el mismo hechizo las tres primeras veces.", /*italian*/"Ho sentito dire che Kotakoume spara sempre la stessa magia le prime tre volte.", /*german*/"Man erzählt sich, die ersten drei Zauber von Twinrova, würden immer dieselben sein."},
    });

    hintTable[JUNK65] = HintText::Junk({
                     // obscure text
                     Text{"They say that the nightly builds may be unstable.", /*french*/"Selon moi, les « nightly builds » peuvent être instables.", /*spanish*/"Según dicen, las últimas nightlies pueden llegar a ser algo inestables.", /*italian*/"Ho sentito dire che le versioni \"nightly\" potrebbero essere instabili.", /*german*/"Man erzählt sich, Nightly Builds könnten instabil sein."},
    });

    hintTable[JUNK66] = HintText::Junk({
                     // obscure text
                     Text{"You're playing a Randomizer. I'm randomized!^Here's a random number:  #4#.&Enjoy your Randomizer!", /*french*/"Tu joues à un randomizer. Je suis aléatoire!^Voici un nombre aléatoire: #4#.&Bonne partie!", /*spanish*/"¡Estás jugando un Randomizer! ¡Yo también estoy aleatorizada!^Aquí tienes un número aleatorio:  #8#.&¡Diviértete!", /*italian*/"Stai giocando a un Randomizer. Io sono randomizzata!^Eccoti un numero random:  #4#.&Buon divertimento!", /*german*/"Du spielst einen Randomizer. Ich wurde zufällig generiert!^Hier ist deine Zufallszahl: #4#.&Viel Spaß damit!"},
    });

    hintTable[JUNK67] = HintText::Junk({
                     // obscure text
                     Text{"They say Ganondorf's bolts can be reflected with glass or steel.", /*french*/"Selon moi, les éclairs de Ganon se reflètent sur l'acier et le verre.", /*spanish*/"Según dicen, puedes reflejar las esferas de energía de Ganondorf con cristal y acero.", /*italian*/"Ho sentito dire che i colpi magici di Ganondorf si riflettono sull'acciaio e sul vetro.", /*german*/"Man erzählt sich, Ganondorfs magische Attacken, könne man mit Glas oder Stahl zurückwerfen."},
    });

    hintTable[JUNK68] = HintText::Junk({
                     // obscure text
                     Text{"They say Ganon's tail is vulnerable to nuts, arrows, swords, explosives, hammers...^...sticks, seeds, boomerangs...^...rods, shovels, iron balls, angry bees...", /*french*/"Selon moi, la queue de Ganon est vulnérable aux noix, flèches, épées, bombes, marteaux...^...bâtons, graines, boomerangs...^...baguettes, pelles, boulets de fer, abeilles enragées...", /*spanish*/"Según dicen, la cola de Ganon es vulnerable a nueces, flechas, espadas, explosivos, martillos...^...palos, semillas, bumeráns...^...cetros, palas, bolas de hierro, abejas...", /*italian*/"Ho sentito dire che la coda di Ganon è vulnerabile a spade, frecce, martelli, esplosivi, noci...^...bastoni, semi, boomerang...^...bacchette, badili, palle di ferro, api irascibili...", /*german*/"Man erzählt sich, Ganons Schwanz sei anfällig gegenüber: Nüssen, Pfeilen, Schwertern,...^...Sprengstoffen, Hämmern, Stäben, Kernen, Bumerängen,...^...Zauberstäben, Schaufeln, Eisenkugeln, wütenden Bienen...^Was eigentlich nicht?"},
    });

    hintTable[JUNK69] = HintText::Junk({ // SFX: Gossip stone growing
                     // obscure text
                     Text{"{240}"} + Text{"They say that you're wasting time reading this hint, but I disagree. Talk to me again!", /*french*/"Selon moi... tu sais quoi? Parle-moi encore, et je te le dirai!", /*spanish*/"Según dicen, pierdes el tiempo en leer esta pista, pero no pienso igual. ¡Vuelve a hablarme, ya verás!", /*italian*/"Ho sentito dire che stai perdendo tempo a leggere questo messaggio, ma io non sono affatto d'accordo. Parlami di nuovo!", /*german*/"Man erzählt sich, deine Zeit wäre erfolgreich verschwendet worden, da du diesen Hinweis gelesen hast. Ich bin da anderer Meinung, bis zum nächsten Mal!"},
    });

    hintTable[JUNK70] = HintText::Junk({
                     // obscure text
                     Text{"They say Ganondorf knows where to find the instrument of his doom.", /*french*/"Selon moi, Ganondorf sait où il a caché son point faible.", /*spanish*/"Según dicen, Ganondorf sabe dónde hallar el instrumento de su perdición.", /*italian*/"Ho sentito dire che Ganondorf sa dove trovare lo strumento della sua sconfitta.", /*german*/"Man erzählt sich, Ganondorf wisse wo das Instrument seines Verderbens zu finden sei.^Warum er es sich nicht holt und verwahrt weiß niemand."},
    });

    hintTable[JUNK71] = HintText::Junk({
                     // obscure text
                     Text{"I heard @ is pretty good at Zelda.", /*french*/"Apparemment, @ est super bon à Zelda.", /*spanish*/"He oído que a @ se le dan muy bien los Zelda.", /*italian*/"Dicono che @ sia davvero bravo a Zelda.", /*german*/"Ich habe gehört @ sei ziemlich gut in Zelda Spielen."},
    });

    hintTable[JUNK72] = HintText::Junk({
                     // obscure text
                     Text{"Hi @, we've been trying to reach you about your car's extended warranty. ", /*french*/"Bonjour, @. Vous avez une voiture? Vous savez, nous offrons des assurances abordables...", /*spanish*/"Buenas, @. Le llamamos para ofrecerle un nuevo seguro de hogar que puede pagar en cómodos plazos, sin intereses ni comisiones.", /*italian*/"Congratulazioni @! Sei stato sorteggiato come vincitore di una Pleistescion 5! Clicca qui per ritirare il tuo premio: bombch.us/DR1b", /*german*/"Sehr geehrter @, wir haben versucht, dich wegen deiner Kfz-Versicherungsverlängerung zu erreichen."},
    });

    hintTable[JUNK73] = HintText::Junk({ // SFX: Equip Fire Arrow
                     // obscure text
                     Text{"{4C3}"} + Text{"They say that the best weapon against Iron Knuckles is item 176.", /*french*/"Selon moi, les hache-viandes sont vulnérables contre l'objet 176.", /*spanish*/"Según dicen, la mejor arma para enfrentarse a los Nudillos de hierro es el objeto 176.", /*italian*/"Ho sentito dire che l'arma più forte contro i guerrieri d'acciaio è l'oggetto 176.", /*german*/"Man erzählt sich, die beste Waffe gegen Eisenprinzen, sei Gegenstand Nummer 176"},
    });

    hintTable[JUNK74] = HintText::Junk({
                     // obscure text
                     Text{"They say that it's actually possible to beat the running man.", /*french*/"Selon moi, il est possible de battre le coureur.&Donc, tu prends ton arc, et...", /*spanish*/"Según dicen, con mucha perseverancia puedes ganarle al corredor con la capucha de conejo.", /*italian*/"Ho sentito dire che è veramente possibile vincere contro il corridore.", /*german*/"Man erzählt sich, es sei möglich den reisenden Rennläufer zu besiegen. ^Wirklich! Vertrau mir einfach."},
    });

    hintTable[JUNK75] = HintText::Junk({
                     // obscure text
                     Text{"They say that the stone-cold guardian of the Well is only present during work hours.", /*french*/"Selon moi, le gardien de pierre du puits quitte le soir pour aller se coucher.", /*spanish*/"Según dicen, la inmensa roca que bloquea el pozo solo trabaja en horas laborales.", /*italian*/"Ho sentito dire che il roccioso guardiano del pozzo è presente solo in orario lavorativo.", /*german*/"Man erzählt sich, das selbst der steinerne Wächter des Brunnens, sich an Arbeitszeiten halte."},
    });

    hintTable[JUNK76] = HintText::Junk({
                     // obscure text
                     Text{"They say this hint makes more sense in other languages.", /*french*/"Selon moi, ces indices auraient pu être mieux traduits... Duh!", /*spanish*/"Según dicen, esta pista revela algo de vital importancia si cambias el idioma del juego...", /*italian*/"Ho sentito dire che la traduzione italiana avrebbe potuto essere fatta meglio...", /*german*/"Man erzählt sich, dieser Hinweis mache mehr Sinn in anderen Sprachen."},
    });

    hintTable[JUNK77] = HintText::Junk({
                     // obscure text
                     Text{"BOK? No way.", /*french*/"BD'accord? Hors de question.", /*spanish*/"¿BVale? Ni hablar.", /*italian*/"BVa bene? Non ci penso nemmeno.", /*german*/"BOK? Niemals!"},
    });

    /*--------------------------
    |     DUNGEON HINT TEXT    |
    ---------------------------*/

    hintTable[DEKU_TREE] = HintText::DungeonName({
                     // obscure text
                     Text{"an ancient tree", /*french*/"le vieil arbre", /*spanish*/"un ancestral árbol", /*italian*/"un antico albero", /*german*/"in einem uralten Baum"},
                   }, {},
                     // clear text
                     Text{"Deku Tree", /*french*/"l'arbre Mojo", /*spanish*/"el Gran Árbol Deku", /*italian*/"il Grande Albero Deku", /*german*/"im Deku-Baum"}
    );

    hintTable[DODONGOS_CAVERN] = HintText::DungeonName({
                     // obscure text
                     Text{"an immense cavern", /*french*/"l'immense caverne", /*spanish*/"una descomunal cueva", /*italian*/"un'immensa caverna", /*german*/"in einer riesigen Höhle"},
                   }, {},
                     // clear text
                     Text{"Dodongo's Cavern", /*french*/"la caverne Dodongo", /*spanish*/"la Cueva de los Dodongos", /*italian*/"la caverna dei Dodongo", /*german*/"in Dodongos Höhle"}
    );

    hintTable[JABU_JABUS_BELLY] = HintText::DungeonName({
                     // obscure text
                     Text{"the belly of a deity", /*french*/"le ventre d'un gardien", /*spanish*/"la tripa de cierta deidad", /*italian*/"la pancia di una divinità", /*german*/"im Bauche einer Gottheit"},
                   }, {},
                     // clear text
                     Text{"Jabu-Jabu's Belly", /*french*/"le ventre de Jabu-Jabu", /*spanish*/"tripa de Jabu-Jabu", /*italian*/"la pancia di Jabu Jabu", /*german*/"in Jabu-Jabus Bauch"}
    );

    hintTable[FOREST_TEMPLE] = HintText::DungeonName({
                     // obscure text
                     Text{"a deep forest", /*french*/"la profonde forêt", /*spanish*/"las profundidades del bosque", /*italian*/"una fitta foresta", /*german*/"in dunklen Wäldern"},
                   }, {},
                     // clear text
                     Text{"Forest Temple", /*french*/"le temple de la forêt", /*spanish*/"el Templo del Bosque", /*italian*/"il Santuario della Foresta", /*german*/"im Waldtempel"}
    );

    hintTable[FIRE_TEMPLE] = HintText::DungeonName({
                     // obscure text
                     Text{"a high mountain", /*french*/"la grande montagne", /*spanish*/"una alta montaña", /*italian*/"la vetta di una montagna", /*german*/"auf hohem Berge"},
                   }, {},
                     // clear text
                     Text{"Fire Temple", /*french*/"le temple du feu", /*spanish*/"el Templo del Fuego", /*italian*/"il Santuario del Fuoco", /*german*/"im Feuertempel"}
    );

    hintTable[WATER_TEMPLE] = HintText::DungeonName({
                     // obscure text
                     Text{"a vast lake", /*french*/"le vaste lac", /*spanish*/"un lago inmenso", /*italian*/"l'acqua di un lago", /*german*/"im tiefen See"},
                   }, {},
                     // clear text
                     Text{"Water Temple", /*french*/"le temple de l'eau", /*spanish*/"el Templo del Agua", /*italian*/"il Santuario dell'Acqua", /*german*/"im Wassertempel"}
    );

    hintTable[SPIRIT_TEMPLE] = HintText::DungeonName({
                     // obscure text
                     Text{"the goddess of the sand", /*french*/"la déesse des sables", /*spanish*/"la diosa de las arenas", /*italian*/"la dea del deserto", /*german*/"innerhalb der Göttin des Sandes"},
                   }, {},
                     // clear text
                     Text{"Spirit Temple", /*french*/"le temple de l'esprit", /*spanish*/"el Templo del Espíritu", /*italian*/"il Santuario dello Spirito", /*german*/"im Geistertempel"}

    );

    hintTable[SHADOW_TEMPLE] = HintText::DungeonName({
                     // obscure text
                     Text{"the house of the dead", /*french*/"la maison des morts", /*spanish*/"la casa de la muerte", /*italian*/"la casa dei morti", /*german*/"an der Stätte des Todes"},
                   }, {},
                     // clear text
                     Text{"Shadow Temple", /*french*/"le temple de l'ombre", /*spanish*/"el Templo de las Sombras", /*italian*/"il Santuario dell'Ombra", /*german*/"im Schattentempel"}
    );

    hintTable[ICE_CAVERN] = HintText::DungeonName({
                     // obscure text
                     Text{"a frozen maze", /*french*/"le dédale glacé", /*spanish*/"un gélido laberinto", /*italian*/"un gelido dedalo", /*german*/"in einem gefrorenen Irrgarten"},
                   }, {},
                     // clear text
                     Text{"Ice Cavern", /*french*/"la caverne de glace", /*spanish*/"la caverna de hielo", /*italian*/"la caverna di ghiaccio", /*german*/"in der Eishöhle"}
    );

    hintTable[BOTTOM_OF_THE_WELL] = HintText::DungeonName({
                     // obscure text
                     Text{"a shadow's prison", /*french*/"la prison d'une ombre", /*spanish*/"la prisión de las sombras", /*italian*/"la prigione di uno spirito maligno", /*german*/"im Gefängnis eines Dämons"},
                   }, {},
                     // clear text
                     Text{"Bottom of the Well", /*french*/"le fonds du puits", /*spanish*/"el fondo del pozo", /*italian*/"il fondo del pozzo", /*german*/"auf dem Grund des Brunnens"}
    );

    hintTable[GERUDO_TRAINING_GROUNDS] = HintText::DungeonName({
                     // obscure text
                     Text{"the test of thieves", /*french*/"l'épreuve des voleurs", /*spanish*/"la prueba de las bandidas", /*italian*/"la prova dei ladri", /*german*/"beim Test der Diebe"},
                   }, {},
                     // clear text
                     Text{"Gerudo Training Grounds", /*french*/"le gymnase Gerudo", /*spanish*/"el Centro de Instrucción Gerudo", /*italian*/"la zona di addestramento Gerudo", /*german*/"in der Gerudo Trainingsarena"}
    );

    hintTable[GANONS_CASTLE] = HintText::DungeonName({
                     // obscure text
                     Text{"a conquered citadel", /*french*/"la citadelle assiégée", /*spanish*/"una conquistada ciudadela", /*italian*/"una cittadella caduta", /*german*/"in einer gefallenen Burg"},
                   }, {},
                     // clear text
                     Text{"Inside Ganon's Castle", /*french*/"l'intérieur du château de Ganon", /*spanish*/"el interior del Castillo de Ganon", /*italian*/"l'interno del castello di Ganon", /*german*/"in Ganons Schloss"}
    );

    /*--------------------------
    |      BOSS HINT TEXT      |
    ---------------------------*/

    hintTable[QUEEN_GOHMA] = HintText::Boss({
                     // obscure text
                     Text{"the #Parasitic Armored Arachnid# holds", /*french*/"le #monstre insectoïde géant# possède", /*spanish*/"el #arácnido parasitario acorazado# porta", /*italian*/"il #parassita corazzato# possiede", /*german*/"nahe dem #gepanzerten Spinnenparasiten#, |wäre|wären|"},
                   }, {},
                     // clear text
                     Text{"#Queen Gohma# holds", /*french*/"la #Reine Gohma# possède", /*spanish*/"la #Reina Goma# porta", /*italian*/"#Gohma# possiede", /*german*/"nahe der #Spinnenkönigin Gohma#, |wäre|wären|"}
    );

    hintTable[KING_DODONGO] = HintText::Boss({
                     // obscure text
                     Text{"the #Infernal Dinosaur# holds", /*french*/"le #dinosaure infernal# possède", /*spanish*/"el #dinosaurio infernal# porta", /*italian*/"il #dinosauro degli inferi# possiede", /*german*/"nahe dem #Infernosaurus#, |wäre|wären|"},
                   }, {},
                     // clear text
                     Text{"#King Dodongo# holds", /*french*/"le #Roi Dodongo# possède", /*spanish*/"el #Rey Dodongo# porta", /*italian*/"il #Mega Dodongo# possiede", /*german*/"nahe #King Dodongo#, |wäre|wären|"}
    );

    hintTable[BARINADE] = HintText::Boss({
                     // obscure text
                     Text{"the #Bio-Electric Anemone# holds", /*french*/"l'#anémone bioélectrique# possède", /*spanish*/"la #anémona bioeléctrica# porta", /*italian*/"l'#anemone bio-elettrico# possiede", /*german*/"nahe dem #elektroterrestrischen Biotentakel#, |wäre|wären|"},
                   }, {},
                     // clear text
                     Text{"#Barinade# holds", /*french*/"#Barinade# possède", /*spanish*/"#Barinade# porta", /*italian*/"#Cnidade# possiede", /*german*/"nahe #Barinade#, |wäre|wären|"}
    );

    hintTable[PHANTOM_GANON] = HintText::Boss({
                     // obscure text
                     Text{"the #Evil Spirit from Beyond# holds", /*french*/"l'#esprit maléfique de l'au-delà# possède", /*spanish*/"el #espíritu maligno de ultratumba# porta", /*italian*/"lo #spirito del male# possiede", /*german*/"nahe dem #reitenden Unheil#, |wäre|wären|"},
                   }, {},
                     // clear text
                     Text{"#Phantom Ganon# holds", /*french*/"#Ganon Spectral# possède", /*spanish*/"#Ganon Fantasma# porta", /*italian*/"#Spettro Ganon# possiede", /*german*/"nahe #Phantom-Ganon#, |wäre|wären|"}
    );

    hintTable[VOLVAGIA] = HintText::Boss({
                     // obscure text
                     Text{"the #Subterranean Lava Dragon# holds", /*french*/"le #dragon des profondeurs# possède", /*spanish*/"el #dragón de lava subterráneo# porta", /*italian*/"il #drago di magma# possiede", /*german*/"nahe dem #subterranen Lavadrachoiden#, |wäre|wären|"},
                   }, {},
                     // clear text
                     Text{"#Volvagia# holds", /*french*/"#Volvagia# possède", /*spanish*/"#Volvagia# porta", /*italian*/"#Varubaja# possiede", /*german*/"nahe #Volvagia#, |wäre|wären|"}
    );

    hintTable[MORPHA] = HintText::Boss({
                     // obscure text
                     Text{"the #Giant Aquatic Amoeba# holds", /*french*/"l'#amibe aquatique géante# possède", /*spanish*/"la #ameba acuática gigante# porta", /*italian*/"l'#ameba gigante# possiede", /*german*/"nahe dem #aquamöben Wassertentakel#, |wäre|wären|"},
                   }, {},
                     // clear text
                     Text{"#Morpha# holds", /*french*/"#Morpha# possède", /*spanish*/"#Morpha# porta", /*italian*/"#Morpha# possiede", /*german*/"nahe #Morpha#, |wäre|wären|"}
    );

    hintTable[BONGO_BONGO] = HintText::Boss({
                     // obscure text
                     Text{"the #Phantom Shadow Beast# holds", /*french*/"le #monstre de l'ombre# possède", /*spanish*/"la #alimaña oscura espectral# porta", /*italian*/"la #bestia delle tenebre# possiede", /*german*/"nahe der #bestialischen Schattenmonstrosität#, |wäre|wären|"},
                   }, {},
                     // clear text
                     Text{"#Bongo Bongo# holds", /*french*/"#Bongo Bongo# possède", /*spanish*/"#Bongo Bongo# porta", /*italian*/"#Bongo Bongo# possiede", /*german*/"nahe #Bongo Bongo#, |wäre|wären|"}
    );

    hintTable[TWINROVA] = HintText::Boss({
                     // obscure text
                     Text{"the #Sorceress Sisters# hold", /*french*/"#les sorcières jumelles# possède", /*spanish*/"las #hermanas hechiceras# portan", /*italian*/"le #sorelle megere# possiedono", /*german*/"nahe der #höllischen Hexenarmada#, |wäre|wären|"},
                   }, {},
                     // clear text
                     Text{"#Twinrova# holds", /*french*/"#Twinrova# possède", /*spanish*/"#Birova# porta", /*italian*/"#Duerova# possiede", /*german*/"nahe #Twinrova#, |wäre|wären|"}
    );
    //
    // [LINKS_POCKET_BOSS] = HintText::Boss({
    //                    // obscure text
    //                    Text{"#@'s pocket# rewards", /*french*/"#@ débute avec#", /*spanish*/"el #bolsillo de @# premia con", /*italian*/"la #tasca di @# premia con", /*german*/"in #@s Tasche#, |wäre|wären|"},
    //                  },
    //                    // clear text
    //                           Text{"#@ already has#", /*french*/"#@ a déjà#", /*spanish*/"el #bolsillo de @ ya tiene#", /*italian*/"#@ già possiede#", /*german*/"bereits in #@s Besitz#, |wäre|wären|"}
    // );

    /*--------------------------
    |     BRIDGE HINT TEXT     |
    ---------------------------*/

    hintTable[BRIDGE_OPEN_HINT] = HintText::Bridge({
                     // obscure text
                     Text{"The awakened ones will have #already&created a bridge# to the castle where&the evil dwells.",
                /*french*/"Les êtres de sagesse ont #déjà créé&un pont# vers le repaire du mal.",
               /*spanish*/"Los sabios #ya habrán creado un&puente #al castillo, de donde emana el mal.",
               /*italian*/"I Saggi avranno #già creato un ponte#&verso il castello dove risiede il male.",
                /*german*/"Die Weisen haben #bereits&eine Brücke zum Portal von&Ganons Schloss gelegt#..."},
    });

    hintTable[BRIDGE_VANILLA_HINT] = HintText::Bridge({
                     // obscure text
                     Text{"The awakened ones will await for the&Hero to collect the #Shadow and Spirit&Medallions# as well as the #Light Arrows#.",
                /*french*/"Les êtres de sagesse attendront le&héros muni des #médaillons de l'ombre&et l'esprit# et des #flèches de lumière#.",
               /*spanish*/"Los sabios aguardarán a que el héroe&obtenga tanto el #Medallón de las&Sombras y el del Espíritu# junto a la #flecha de luz#.",
               /*italian*/"I Saggi aspetteranno che l'Eroe&ottenga sia i #medaglioni dell'Ombra&e dello Spirito# che la #freccia di luce#.",
                /*german*/"Die Weisen werden darauf warten,&dass der Held das #Amulett des&Schattens, Amulett der Geister#&und die #Licht-Pfeile# sammelt."},
    });

    hintTable[BRIDGE_STONES_HINT] = HintText::Bridge({
                     // obscure text                                                  singular        plural
                     Text{"The awakened ones will await for the&Hero to collect #%d |Spiritual Stone|Spiritual Stones|#.",
                /*french*/"Les êtres de sagesse attendront le&héros muni de #%d |pierre spirituelle|pierres spirituelles|#.",
               /*spanish*/"Los sabios aguardarán a que el héroe&obtenga #%d |piedra espiritual|piedras espirituales|#.",
               /*italian*/"I Saggi aspetteranno che l'Eroe&ottenga #%d |pietra spirituale|pietre spirituali|#.",
                /*german*/"Die Weisen werden darauf&warten, dass der Held #%d&|Heiligen Stein|Heilige Steine|# sammelt."},
    });

    hintTable[BRIDGE_MEDALLIONS_HINT] = HintText::Bridge({
                     // obscure text                                                  singular  plural
                     Text{"The awakened ones will await for the&Hero to collect #%d |Medallion|Medallions|#.",
                /*french*/"Les êtres de sagesse attendront le&héros muni de #%d |médaillon|médaillons|#.",
               /*spanish*/"Los sabios aguardarán a que el héroe&obtenga #%d |medallón|medallones|#.",
               /*italian*/"I Saggi aspetteranno che l'Eroe&ottenga #%d |medaglione|medaglioni|#.",
                /*german*/"Die Weisen werden darauf&warten, dass der Held #%d&|Amulett|Amulette|# sammelt."},
    });

    hintTable[BRIDGE_REWARDS_HINT] = HintText::Bridge({
                     // obscure text                                                  singular                     plural
                     Text{"The awakened ones will await for the&Hero to collect #%d |Spiritual Stone&or Medallion|Spiritual Stones&and Medallions|#.",
                /*french*/"Les êtres de sagesse attendront le&héros muni de #%d |pierre spirituelle&ou médaillon|pierres spirituelles&et médaillons|#.",
               /*spanish*/"Los sabios aguardarán a que el héroe&obtenga #%d |piedra espiritual o medallón|piedras espirtuales y medallones|#.",
               /*italian*/"I Saggi aspetteranno che l'Eroe&ottenga #%d |pietra spirituale o medaglione|pietre spirituali o medaglioni|#.",
                /*german*/"Die Weisen werden darauf warten,&dass der Held #%d |Heiligen Stein&oder Amulett|Heilige Steine&oder Amulette|# sammelt."},
    });

    hintTable[BRIDGE_DUNGEONS_HINT] = HintText::Bridge({
                     // obscure text                                                  singular plural
                     Text{"The awakened ones will await for the&Hero to conquer #%d |Dungeon|Dungeons|#.",
                /*french*/"Les êtres de sagesse attendront la&conquête de #%d |donjon|donjons|#.",
               /*spanish*/"Los sabios aguardarán a que el héroe&complete #%d |mazmorra|mazmorras|#.",
               /*italian*/"I Saggi aspetteranno che l'Eroe&completi #%d dungeon#.",
                /*german*/"Die Weisen werden darauf&warten, dass der Held #%d&|Labyrinth|Labyrinthe|# abschließt."},
    });

    hintTable[BRIDGE_TOKENS_HINT] = HintText::Bridge({
                     // obscure text
                     Text{"The awakened ones will await for the&Hero to collect #%d |Gold Skulltula&Token|Gold Skulltula&Tokens|#.",
                /*french*/"Les êtres de sagesse attendront le&héros muni de #%d |symbole|symboles| de&Skulltula d'or#.",
               /*spanish*/"Los sabios aguardarán a que el héroe&obtenga #%d |símbolo|símbolos| de&skulltula dorada#.",
               /*italian*/"I Saggi aspetteranno che l'Eroe&ottenga #%d |teschio|teschi| d'oro#.",
                /*german*/"Die Weisen werden darauf&warten, dass der Held #%d&|Skulltula-Symbol|Skulltula-Symbole|# sammelt."},
    });

    hintTable[BRIDGE_HEARTS_HINT] = HintText::Bridge({
                     // obscure text
                     Text{"The awakened ones will await for the&Hero to collect #%d |Heart|Hearts|#.",
                /*french*/"Les êtres de sagesse attendront le&héros muni de #%d |cœur|cœurs|#.",
               /*spanish*/"Los sabios aguardarán a que el héroe&obtenga #%d |corazón|corazones|#.",
               /*italian*/"I Saggi aspetteranno che l'Eroe&ottenga #%d |cuore|cuori|#.",
                /*german*/"Die Weisen werden darauf&warten, dass der Held #%d&|Herz|Herzen|# sammelt."},
    });

    /*--------------------------
    | GANON BOSS KEY HINT TEXT |
    ---------------------------*/

    hintTable[GANON_BK_START_WITH_HINT] = HintText::GanonsBossKey({
                     // obscure text
                     Text{"And the #evil one#'s key will be #given from the start#.",
                /*french*/"Aussi, la clé du #Malin# sera #possession même du héros#.",
               /*spanish*/"Y obtendrás la llave del #señor del mal# desde el #inicio#.",
               /*italian*/"E la chiave del #re del male# sarà #in possesso dell'eroe#.",
                /*german*/"Und der #Schlüssel des Bösen#,&wird #von Anfang an, im&Besitz des Helden# sein."},
    });

    hintTable[GANON_BK_VANILLA_HINT] = HintText::GanonsBossKey({
                     // obscure text
                     Text{"And the #evil one#'s key will be kept in a big chest #inside its tower#.",
                /*french*/"Aussi, la clé du #Malin# sera encoffrée #dans sa tour#.",
               /*spanish*/"Y la llave del #señor del mal# aguardará en un gran cofre de #su torre#.",
               /*italian*/"E la chiave del #re del male# sarà chiusa in un grosso forziere nella #sua torre#.",
                /*german*/"Und der #Schlüssel des Bösen#,&wird in der großen Truhe #im&Teufelsturm# zu finden sein."},
    });

    hintTable[GANON_BK_OWN_DUNGEON_HINT] = HintText::GanonsBossKey({
                     // obscure text
                     Text{"And the #evil one#'s key will be hidden somewhere #inside its castle#.",
                /*french*/"Aussi, la clé du #Malin# sera cachée #dans son vaste château#.",
               /*spanish*/"Y la llave del #señor del mal# aguardará en #algún lugar de su castillo#.",
               /*italian*/"E la chiave del #re del male# sarà nascosta da qualche parte nel #suo castello#.",
                /*german*/"Und der #Schlüssel des Bösen#,&wird irgendwo #in Ganons&Schloss# zu finden sein."},
    });

    hintTable[GANON_BK_OVERWORLD_HINT] = HintText::GanonsBossKey({
                     // obscure text
                     Text{"And the #evil one#'s key will be hidden #outside of dungeons# in Hyrule.",
                /*french*/"Aussi, la clé du #Malin# se trouve #hors des donjons# d'Hyrule.",
               /*spanish*/"Y la llave del #señor del mal# aguardará #fuera de las mazmorras# de Hyrule.",
               /*italian*/"E la chiave del #re del male# sarà nascosta ad Hyrule #al di fuori dei dungeon#.",
                /*german*/"Und der #Schlüssel des Bösen#,&wird irgendwo #in Hyrule,&außerhalb von Labyrinthen#&zu finden sein."},
    });

    hintTable[GANON_BK_ANY_DUNGEON_HINT] = HintText::GanonsBossKey({
                     // obscure text
                     Text{"And the #evil one#'s key will be hidden #inside a dungeon# in Hyrule.",
                /*french*/"Aussi, la clé du #Malin# se trouve #dans un donjon# d'Hyrule.",
               /*spanish*/"Y la llave del #señor del mal# aguardará #en una mazmorra# de Hyrule.",
               /*italian*/"E la chiave del #re del male# sarà nascosta ad Hyrule #all'interno di un dungeon#.",
                /*german*/"Und der #Schlüssel des Bösen#,&wird irgendwo #in Hyrule,&innerhalb eines Labyrinths#&zu finden sein."},
    });

    hintTable[GANON_BK_ANYWHERE_HINT] = HintText::GanonsBossKey({
                     // obscure text
                     Text{"And the #evil one#'s key will be hidden somewhere #in Hyrule#.",
                /*french*/"Aussi, la clé du #Malin# se trouve quelque part #dans Hyrule#.",
               /*spanish*/"Y la llave del #señor del mal# aguardará en #cualquier lugar de Hyrule#.",
               /*italian*/"E la chiave del #re del male# sarà nascosta #da qualche parte ad Hyrule#.",
                /*german*/"Und der #Schlüssel des Bösen#,&wird irgendwo #in Hyrule#&zu finden sein."},
    });

    hintTable[GANON_BK_TRIFORCE_HINT] = HintText::GanonsBossKey({
                     // obscure text
                     Text{"And the #evil one#'s key will be given to the Hero once the #Triforce# is completed.",
                /*french*/"Aussi, la clé du #Malin# se révèlera une fois la #Triforce# assemblée.",
               /*spanish*/"Y el héroe recibirá la llave del #señor del mal# cuando haya completado la #Trifuerza#.",
               /*italian*/"E la chiave del #re del male# sarà ottenuta dall'Eroe completando la #Triforza#.",
                /*german*/"Und der #Schlüssel des Bösen#&wird verliehen, sobald das&#Triforce# vervollständigt wurde."},
    });

    /*--------------------------
    |      LACS HINT TEXT      |
    ---------------------------*/

    hintTable[LACS_VANILLA_HINT] = HintText::LACS({
                     // obscure text
                     Text{"And the #evil one#'s key will be&provided by Zelda once the #Shadow&and Spirit Medallions# are retrieved.",
                /*french*/"Aussi, Zelda crééra la clé du&#Malin# avec les #médaillons de&l'ombre et de l'esprit#.",
               /*spanish*/"Y Zelda entregará la llave&del #señor del mal# tras obtener&#el medallón de las sombras y del espíritu#.",
               /*italian*/"E la chiave del #re del male# sarà&ricevuta da Zelda dopo aver ottenuto&i #medaglioni dell'Ombra e dello Spirito#.",
                /*german*/"Und der #Schlüssel des Bösen# wird&von Zelda verliehen, sobald #die&Amulette des Schattens und&der Geister# geborgen wurden."},
    });

    hintTable[LACS_MEDALLIONS_HINT] = HintText::LACS({
                     // obscure text                                                     singular      plural
                     Text{"And the #evil one#'s key will be&provided by Zelda once #%d&|Medallion# is|Medallions# are| retrieved.",
                /*french*/"Aussi, Zelda crééra la clé du&#Malin# avec #%d |médaillon|médaillons|#.",
               /*spanish*/"Y Zelda entregará la llave&del #señor del mal# tras obtener&#%d |medallón|medallones|#.",
               /*italian*/"E la chiave del #re del male# sarà&ricevuta da Zelda dopo aver ottenuto&#%d |medaglione|medaglioni|#.",
                /*german*/"Und der #Schlüssel des Bösen# wird&von Zelda verliehen, sobald #%d&|Amulett# geborgen wurde|Amulette# geborgen wurden|."},
    });

    hintTable[LACS_STONES_HINT] = HintText::LACS({
                     // obscure text                                                     singular            plural
                     Text{"And the #evil one#'s key will be&provided by Zelda once #%d |Spiritual&Stone# is|Spiritual&Stones# are| retrieved.",
                /*french*/"Aussi, Zelda crééra la clé du&#Malin# avec #%d des |pierre&spirituelle|pierres&spirituelles|#.",
               /*spanish*/"Y Zelda entregará la llave&del #señor del mal# tras obtener&#%d |piedra espiritual|piedras espirituales|#.",
               /*italian*/"E la chiave del #re del male# sarà&ricevuta da Zelda dopo aver ottenuto&#%d |pietra spirituale|pietre spirituali|#.",
                /*german*/"Und der #Schlüssel des Bösen# wird&von Zelda verliehen, sobald #%d&|Heiliger Stein# geborgen wurde|Heilige Steine# geborgen wurden|."},
    });

    hintTable[LACS_REWARDS_HINT] = HintText::LACS({
                     // obscure text                                                     singular                         plural
                     Text{"And the #evil one#'s key will be&provided by Zelda once #%d |Spiritual&Stone or Medallion# is|Spiritual&Stones and Medallions# are| retrieved.",
                /*french*/"Aussi, Zelda crééra la clé du&#Malin# avec #%d |pierre spirituelle&et des médaillon|pierres spirituelles&et des médaillons|#.",
               /*spanish*/"Y Zelda entregará la llave&del #señor del mal# tras obtener&#%d |piedra espiritual o medallón|piedras espirituales o medallones|#.",
               /*italian*/"E la chiave del #re del male# sarà&ricevuta da Zelda dopo aver ottenuto&#%d |pietra spirituale o medaglione|pietre spirituali o medaglioni|#.",
                /*german*/"Und der #Schlüssel des Bösen# wird&von Zelda verliehen, sobald #%d&|Heiliger Stein oder Amulett#&geborgen wurde|Heilige Steine oder Amulette#&geborgen wurden|."},
    });

    hintTable[LACS_DUNGEONS_HINT] = HintText::LACS({
                     // obscure text                                                     singular    plural
                     Text{"And the #evil one#'s key will be&provided by Zelda once #%d |Dungeon#&is|Dungeons#&are| conquered.",
                /*french*/"Aussi, Zelda crééra la clé du&#Malin# une fois #%d |donjon conquéri|donjons conquéris|#.",
               /*spanish*/"Y Zelda entregará la llave&del #señor del mal# tras completar&#%d |mazmorra|mazmorras|#.",
               /*italian*/"E la chiave del #re del male# sarà&ricevuta da Zelda dopo aver&completato #%d dungeon#.",
                /*german*/"Und der #Schlüssel des Bösen# wird&von Zelda verliehen, sobald #%d&|Labyrinth# abgeschlossen wurde|Labyrinthe# abgeschlossen wurden|."},
    });

    hintTable[LACS_TOKENS_HINT] = HintText::LACS({
                     // obscure text                                                     singular                 plural
                     Text{"And the #evil one#'s key will be&provided by Zelda once #%d |Gold&Skulltula Token# is|Gold&Skulltula Tokens# are| retrieved.",
                /*french*/"Aussi, Zelda crééra la clé du&#Malin# avec #%d |symbole|symboles| de&Skulltula d'or#.",
               /*spanish*/"Y Zelda entregará la llave&del #señor del mal# tras obtener&#%d |símbolo|símbolos| de&skulltula dorada#.",
               /*italian*/"E la chiave del #re del male# sarà&ricevuta da Zelda dopo aver ottenuto&#%d |teschio|teschi| d'oro#.",
                /*german*/"Und der #Schlüssel des Bösen# wird&von Zelda verliehen, sobald #%d&|Skulltula-Symbol# gesammelt wurde|Skulltula-Symbole# gesammelt wurden|."},
    });

    hintTable[LACS_HEARTS_HINT] = HintText::LACS({
                     // obscure text                                                     singular  plural
                     Text{"And the #evil one#'s key will be&provided by Zelda once #%d |Heart#&is|Hearts#&are| retrieved.",
                /*french*/"Aussi, Zelda crééra la clé du&#Malin# avec #%d |cœur|cœurs|#.",
               /*spanish*/"Y Zelda entregará la llave&del #señor del mal# tras obtener&#%d |corazón|corazones|#.",
               /*italian*/"E la chiave del #re del male# sarà&ricevuta da Zelda dopo aver ottenuto&#%d |cuore|cuori|#.",
                /*german*/"Und der #Schlüssel des Bösen# wird&von Zelda verliehen, sobald #%d&|Herz# gesammelt wurde|Herzen# gesammelt wurden|."},
    });
    /*--------------------------
    |     TRIAL HINT TEXT      |
    ---------------------------*/

    hintTable[SIX_TRIALS] = HintText::Exclude({
                     // obscure text
                     Text{"#Ganon's Tower# is protected by a powerful barrier.",
                /*french*/"#la tour de Ganon# est protégée par une puissante barrière",
               /*spanish*/"la #torre de Ganon# está protegida por una poderosa barrera",
               /*italian*/"la #torre di Ganon# è protetta da una potente barriera.",
                /*german*/"der #Teufelsturm# sei von einer mächtigen Barriere geschützt."},
    });

    hintTable[ZERO_TRIALS] = HintText::Exclude({
                     // obscure text
                     Text{"Sheik dispelled the barrier around #Ganon's Tower#.",
                /*french*/"Sheik a dissipé la barrière autour de #la tour de Ganon#",
               /*spanish*/"Sheik disipó la barrera alrededor de la #torre de Ganon#.",
               /*italian*/"Sheik ha dissolto la barriera attorno alla #torre di Ganon#.",
                /*german*/"Shiek habe die Barriere um den #Teufelsturm# aufgelöst."},
    });

    hintTable[FOUR_TO_FIVE_TRIALS] = HintText::Exclude({
                     // obscure text
                     Text{" was dispelled by Sheik.",
                /*french*/" a été dissipée par Sheik.",
               /*spanish*/" se disipó gracias a Sheik.",
               /*italian*/" è stata dissolta da Sheik.",
                /*german*/" sei von Shiek aufgelöst worden."},
    });

    hintTable[ONE_TO_THREE_TRIALS] = HintText::Exclude({
                     // obscure text
                     Text{" protects Ganons Tower.",
                /*french*/" protège la tour de Ganon.",
               /*spanish*/" protege la torre de Ganon",
               /*italian*/" protegge la torre di Ganon.",
                /*german*/" schütze den Teufelsturm."},
    });

    /*--------------------------
    |        ALTAR TEXT        |
    ---------------------------*/

    hintTable[SPIRITUAL_STONE_TEXT_START] = HintText::Altar({
                     // obscure text
                     Text{"3 Spiritual Stones found in Hyrule...",
                /*french*/"Les trois pierres spirituelles cachées dans Hyrule...",
               /*spanish*/"Tres piedras espirituales halladas por Hyrule...",
               /*italian*/"Tre pietre spirituali si celano ad Hyrule...",
                /*german*/"Drei Heilige Steine, zu finden in Hyrule..."},
    });

    hintTable[CHILD_ALTAR_TEXT_END_DOTOPEN] = HintText::Altar({
                     // obscure text
                     Text{"Ye who may become a Hero...&The path to the future is open...",
                /*french*/"À celui qui a quête de devenir héros...&Le futur vous accueille béant...",
               /*spanish*/"Para aquel que se convierta en el héroe...&La puerta al futuro está a su disposición...",
               /*italian*/"O tu che diventerai un Eroe...&Il passaggio per il futuro è aperto...",
                /*german*/"Jener auf dem Weg des Helden...&Der Pfad zur Zukunft sei geöffnet..."},
    });

    hintTable[CHILD_ALTAR_TEXT_END_DOTCLOSED] = HintText::Altar({
                     // obscure text
                     Text{"Ye who may become a Hero...&Stand with the Ocarina and&play the Song of Time.",
                /*french*/"À celui qui a quête de devenir héros...&Portez l'Ocarina et jouez&le chant du temps.",
               /*spanish*/"Para aquel que se convierta en el héroe...&Tome la ocarina y entone&la Canción del Tiempo.",
               /*italian*/"O tu che diventerai un Eroe...&Prendi l'ocarina e suona&la Canzone del Tempo.",
                /*german*/"Jener auf dem Weg des Helden...&Nehme er seine Okarina zur Hand und&spiele hier die Hymne der Zeit."},
    });

    hintTable[CHILD_ALTAR_TEXT_END_DOTINTENDED] = HintText::Altar({
                     // obscure text
                     Text{"Ye who may become a Hero...&Offer the spiritual stones and&play the Song of Time.",
                /*french*/"À celui qui a quête de devenir héros...&Présentez les pierres spirituelles et&jouez le chant du temps.",
               /*spanish*/"Para aquel que se convierta en el héroe...&Tome las piedras espirituales y&entone la Canción del Tiempo.",
               /*italian*/"O tu che diventerai un Eroe...&Offri le tre pietre spirituali e&suona la Canzone del Tempo.",
                /*german*/"Jener mit den drei Heiligen Steinen&nehme seine Okarina zur Hand und&spiele hier die Hymne der Zeit."},
    });

    hintTable[ADULT_ALTAR_TEXT_START] = HintText::Altar({
                     // obscure text
                     Text{"When evil rules all, an awakening voice from the Sacred Realm will call those destined to be Sages, who dwell in the #five temples#.",
                /*french*/"Quand le mal aura triomphé, une voix du Saint Royaume appellera ceux cachés dans les #cinq temples#, destinés à être Sages.",
               /*spanish*/"Cuando el mal lo impregne todo, desde el Reino Sagrado surgirá una voz que hará despertar a los sabios que moran en los #cinco templos#.",
               /*italian*/"Quando il male regnerà sovrano, una voce proveniente dalla terra sacra riunirà i Saggi dei #cinque santuari#.",
                /*german*/"Beherrscht das Böse die Welt, weilen&jene Weisen, die von der Stimme des&Heiligen Reiches erweckt werden, noch&in den #fünf Tempeln#."},
    });

    hintTable[ADULT_ALTAR_TEXT_END] = HintText::Altar({
                     // obscure text
                     Text{"Together with the Hero of Time, the&awakened ones will bind the evil and&return the light of peace to the world...",
                /*french*/"Ensemble avec le Héros du Temps,&ces Sages emprisonneront le mal et&réinstaureront la lumière de paix dans&le monde...",
               /*spanish*/"Con el Héroe del Tiempo, aquellos&que despierten detendrán el mal y&volverán al mundo la luz de la paz...",
               /*italian*/"Insieme all'Eroe del Tempo, i Saggi sconfiggeranno il male e riporteranno&la luce sul mondo...",
                /*german*/"Zusammen mit dem Auserwählten wer-&den diese ihre Kräfte einsetzen, um&der Welt den Frieden wiederzugeben."},
    });

    /*--------------------------
    |   VALIDATION LINE TEXT   |
    ---------------------------*/

    hintTable[VALIDATION_LINE] = HintText::Validation({
                     // obscure text
                     Text{"Hmph... Since you made it this far, I'll let you know what glorious prize of Ganon's you likely missed out on in my tower.^Behold...^",
                /*french*/"Pah! Puisque tu t'es rendu ici, je te dirai quel trésor tu as manqué dans ma tour.^Et c'est...^",
               /*spanish*/"Mmm... Ya que has llegado hasta aquí, te diré qué preciado objeto de mi propiedad puedes haberte dejado en mi torre.^He aquí...^",
               /*italian*/"Bah! Visto che sei arrivato fin qui, ti rivelerò quale incredibile tesoro ti sei probabilmente perso nella mia torre...^Ammira...^ ",
                /*german*/"Hmpf... Da du es so weit geschafft hast, werde ich dir sagen, welch herrlichen Preis Ganons du dir entgehen lassen hast.^Erzittere vor... "},
    });

    /*--------------------------
    | LIGHT ARROW LOCATION TEXT|
    ---------------------------*/

    hintTable[LIGHT_ARROW_LOCATION_HINT] = HintText::LightArrow({
                     // obscure text
                     Text{"Ha ha ha... You'll never beat me by reflecting my lightning bolts and unleashing the arrows from ",
                /*french*/"Ha ha ha... Pauvre fou! Tu ne pourras jamais me vaincre sans les flèches que j'ai cachées dans ",
               /*spanish*/"Ja, ja, ja... Nunca me derrotarás reflejando mis esferas de energía y desplegando la flecha de luz de ",
               /*italian*/"Ah ah ah... Non mi sconfiggerai mai senza le frecce di luce! Sono ben nascoste in un posto chiamato ",
                /*german*/"Ha ha ha... Du wirst mich niemals besiegen, indem du meine Energiebälle zurückwirfst und mich dann mit Licht-Pfeilen beschießt!^Sie sind absolut sicher "},
    });

    hintTable[YOUR_POCKET] = HintText::Exclude({
                     // obscure text
                     Text{"your pocket", /*french*/"tes poches", /*spanish*/"tu bolsillo", /*italian*/"la tua tasca", /*german*/"in deiner Tasche"},
    });

    /*--------------------------
    |MASTER SWORD LOCATION TEXT|
    ---------------------------*/

    hintTable[MASTER_SWORD_LOCATION_HINT] = HintText::MasterSword({
                     // obscure text
                     Text{"And even if you do, you'll never find the legendary blade hidden in ",
                /*french*/"Et même si tu les trouves, tu ne touveras jamais l'épée de légende cachée dans ",
               /*spanish*/"E incluso si lo haces, nunca encontrarás la espada legendaria escondida en ",
               /*italian*/"E anche se le trovi, non saprai mai che il nascondiglio della spada leggendaria è ",
                /*german*/"Und selbst wenn doch, die legendäre Klinge wirst du niemals finden "},
    });

    /*--------------------------
    |      GANON LINE TEXT     |
    ---------------------------*/

    hintTable[GANON_LINE01] = HintText::GanonLine({
                     // obscure text
                     Text{"Oh! It's @.&I was expecting someone called Sheik. Do you know what happened to them?",
                /*french*/"Ah, c'est @.&J'attendais un certain Sheik. Tu sais ce qui lui est arrivé?",
               /*spanish*/"¡Oh! Pero si es @.&Estaba esperando a alguien llamado Sheik. ¿Sabes qué puede haberle pasado?",
               /*italian*/"Oh, sei @!&Stavo aspettando qualcuno di nome Sheik.&Per caso sai che fine ha fatto?",
                /*german*/"Oh, du bist es @.&Ich habe jemanden namens Shiek erwartet. Weißt du, was mit ihm passiert ist?"},
    });

    hintTable[GANON_LINE02] = HintText::GanonLine({
                     // obscure text
                     Text{"I knew I shouldn't have put the key on the other side of my door.",
                /*french*/"J'aurais dû garder la clé ici. Hélas...",
               /*spanish*/"Sabía que no tendría que haber dejado la llave al otro lado de la puerta.",
               /*italian*/"Sapevo che non avrei dovuto lasciare la chiave dall'altro lato della porta.",
                /*german*/"Ich wusste, ich hätte den Schlüssel nicht draußen liegen lassen sollen."},
    });

    hintTable[GANON_LINE03] = HintText::GanonLine({
                     // obscure text
                     Text{"Looks like it's time for a round of tennis.",
                /*french*/"C'est l'heure de jouer au tennis.",
               /*spanish*/"Parece que es hora de una pachanga de tenis.",
               /*italian*/"Pare sia ora di giocare a tennis.",
                /*german*/"Es scheint Zeit für eine Runde Tennis zu sein."},
    });

    hintTable[GANON_LINE04] = HintText::GanonLine({
                     // obscure text
                     Text{"You'll never deflect my bolts of energy with your sword, then shoot me with those Light Arrows you happen to have.",
                /*french*/"Ne perds pas ton temps à frapper mes éclairs d'énergie avec ton épée et me tirer avec tes flèches de Lumière!",
               /*spanish*/"Nunca reflejarás mis esferas de energía con tu espada, para después dispararme con las flechas de luz que tendrás.",
               /*italian*/"Non rifletterai mai i miei attacchi magici con quella spada, tantomeno mi colpirai con quelle frecce di luce che ti ritrovi!",
                /*german*/"Du wirst mich niemals besiegen, indem du meine Energiebälle zurückwirfst und mich dann mit Licht-Pfeilen beschießt!"},
    });

    hintTable[GANON_LINE05] = HintText::GanonLine({
                     // obscure text
                     Text{"Why did I leave my trident back in the desert?",
                /*french*/"Sale bêtise... Et j'ai oublié mon trident dans le désert!",
               /*spanish*/"Santa Hylia... ¿Por qué me habré dejado el tridente en el desierto?",
               /*italian*/"Accidenti... Mi sono scordato il tridente, è ancora al deserto!",
                /*german*/"Verdammt... Ich habe meinen Dreizack in der Wüste gelassen."},
    });

    hintTable[GANON_LINE06] = HintText::GanonLine({
                     // obscure text
                     Text{"Zelda is probably going to do something stupid, like send you back to your own timeline.^So this is quite meaningless. Do you really want to save this moron?",
                /*french*/"Même si je suis vaincu... Zelda te renverra dans ton ère, et je reviendrai conquérir!^Telle est la prophécie d'Hyrule Historia!",
               /*spanish*/"Seguro que Zelda trata de hacer alguna tontería, como enviarte de vuelta a tu línea temporal.^No tiene ningún sentido alguno. ¿De verdad quieres salvar a esa tonta?",
               /*italian*/"Zelda farà senz'altro qualche stupidaggine, tipo mandarti indietro nel tempo creando una divergenza temporale.^Sei sicuro di voler salvare questa tonta?",
                /*german*/"Zelda wird wahrscheinlich etwas Dummes tun, wie dich in deine eigene Zeit zurück zu schicken.^Ziemlich sinnlos! Willst du diesen Schwachkopf wirklich retten?"},
    });

    hintTable[GANON_LINE07] = HintText::GanonLine({
                     // obscure text
                     Text{"What about Zelda makes you think she'd be a better ruler than I?^I saved Lon Lon Ranch,&fed the hungry,&and my castle floats.",
                /*french*/"Zelda ne sera jamais un meilleur monarque que moi!^J'ai un château volant, mes sujets sont des belles amazones... et mes Moblins sont clairement plus puissants que jamais!",
               /*spanish*/"¿Qué te hace pensar que Zelda gobierna mejor que yo?^Yo he salvado el Rancho Lon Lon,&he alimentado a los hambrientos&y hasta hago que mi castillo flote.",
               /*italian*/"Cosa ti fa pensare che Zelda governerebbe meglio di me?^Ho salvato la Fattoria Lon Lon, ho dato da mangiare agli affamati, e ho un castello volante!",
                /*german*/"Was an Zelda bringt dich dazu zu denken, sie sei ein besserer Herrscher als ich?^Ich habe die Lon Lon-Farm gerettet,&den Hungrigen etwas zu Essen gegeben,&und mein Schloss schwebt!"},
    });

    hintTable[GANON_LINE08] = HintText::GanonLine({
                     // obscure text
                     Text{"I've learned this spell,&it's really neat,&I'll keep it later&for your treat!",
                /*french*/"Gamin, ton destin achève,&sous mon sort tu périras!&Cette partie ne fut pas brève,&et cette mort, tu subiras!",
               /*spanish*/"Veamos ahora que harás,&la batalla ha de comenzar,&te enviaré de una vez al más allá,&¿listo para afrontar la verdad?",
               /*italian*/"Sei giunto alla fine&della tua avventura,&se sei senza fatine&la tua morte è sicura!",
                /*german*/"Zelda weint, das arme Kind,&ihr Retter läuft herum wie blind!"},
    });

    hintTable[GANON_LINE09] = HintText::GanonLine({
                     // obscure text
                     Text{"Many tricks are up my sleeve,&to save yourself&you'd better leave!",
                /*french*/"Sale petit garnement,&tu fais erreur!&C'est maintenant que marque&ta dernière heure!",
               /*spanish*/"¿No osarás a mí enfrentarte?&Rimas aparte,&¡voy a matarte!",
               /*italian*/"Ci hai messo anche troppo&ad arrivare fin qua,&ora in un botto&vedrai l'aldilà!",
                /*german*/"Da hilft kein Flehen und kein Flennen,&bald wird dieses Weltlein brennen!"},
    });

    hintTable[GANON_LINE10] = HintText::GanonLine({
                     // obscure text
                     Text{"After what you did to Koholint Island, how can you call me the bad guy?",
                /*french*/"J'admire ce que tu as fait à l'Île Koholint... Toi et moi, nous devrions faire équipe!",
               /*spanish*/"Después de lo que le hiciste a la Isla Koholint, ¿cómo te atreves a llamarme malvado?",
               /*italian*/"Dopo quello che hai fatto all'Isola di Koholint, come puoi chiamarmi cattivo?",
                /*german*/"Nach allem was du auf Kokolint angerichtet hast, wie kannst du mich den Bösen nennen?"},
    });

    hintTable[GANON_LINE11] = HintText::GanonLine({
                     // obscure text
                     Text{"Today, let's begin down&'The Hero is Defeated' timeline.",
                /*french*/"Si tu me vaincs, Hyrule sera englouti... mais si tu meurs, on aura A Link to the Past, le meilleur opus de la série!",
               /*spanish*/"Hoy daremos lugar a la línea temporal del Héroe Derrotado.&¡Prepárate para el culmen de esta saga!",
               /*italian*/"Questo giorno segnerà l'inizio della linea temporale dell'Eroe Sconfitto.",
                /*german*/"Heute beginnen wir die&'Der Held wurde besiegt'-Zeitlinie."},
    });

    /*--------------------------
    |      SHEIK LINE TEXT     |
    ---------------------------*/

    hintTable[SHEIK_LIGHT_ARROW_LOCATION_HINT] = HintText::SheikLine({
                     // obscure text
                     Text{"I overheard Ganondorf say that he put #the Light Arrows# in ",
                /*french*/"J'ai entendu Ganondorf dire qu'il a caché #les flèches de lumière# dans ",
               /*spanish*/"Escuché a Ganondorf decir que pusó #las flechas de luz# en ",
               /*italian*/"Ho scoperto che Ganondorf ha nascosto #le frecce di luce# presso ",
                /*german*/"Ich habe mitbekommen, wie Ganondorf gesagt hat, dass er #die Lichtpfeile# "}, // + versteckt hat
    });

    hintTable[SHEIK_MASTER_SWORD_LOCATION_HINT] = HintText::SheikLine({
                     // obscure text
                     Text{"He also stole #the Master Sword# and hid it in ",
                /*french*/"Il aurait aussi volé #l'épée de légende#, qu'il aurait caché dans ",
               /*spanish*/"Él también robó #la Espada Maestra# y la escondió en ",
               /*italian*/"Ha anche rubato #la spada suprema#. L'ho sentito dire qualcosa riguardo ",
                /*german*/"Er hat außerdem #das Master-Schwert# gestohlen und "}, // + versteckt
    });

    hintTable[SHEIK_LINE01] = HintText::SheikLine({
                     // obscure text
                     Text{"@, I'll be waiting at Ganon's Castle once you have his #boss key#.",
                /*french*/"@, je t'attendrai au château de Ganon une fois que tu auras sa #clé d'or#.",
               /*spanish*/"@, te esperé en el Castillo de Ganon cuando hás obtenido su #llave de jefe#.",
               /*italian*/"@, ti aspetterò al castello di Ganon quando avrai ottenuto la sua #grande chiave#.",
                /*german*/"@, ich werde bei Ganons Schloss warten, sobald du seinen #Bossschlüssel# gefunden hast."},
    });

    hintTable[SHEIK_LINE02] = HintText::SheikLine({
                     // obscure text
                     Text{"It's time.",
                /*french*/"Le moment est venu.",
               /*spanish*/"Ya es la hora.",
               /*italian*/"È giunto il momento.",
                /*german*/"Es ist Zeit."},
    });

    hintTable[SHEIK_LINE03] = HintText::SheikLine({
                     // obscure text
                     Text{"Looks like you're ready.^Good luck.",
                /*french*/"On dirait que tu es prêt.^Je te souhaite bonne chance.",
               /*spanish*/"Parece que estás listo.^Buena suerte.",
               /*italian*/"Sembra che tu sia pronto.^Buona fortuna.",
                /*german*/"Scheint als wärst du bereit.^Viel Glück."},
    });

    /*--------------------------
    |      MERCHANTS' ITEMS     |
    ---------------------------*/

    hintTable[MEDIGORON_DIALOG] = HintText::MerchantsDialogs({
                     // obscure text
                     Text{"How about buying %s for #200 Rupees#?&"+TWO_WAY_CHOICE()+"#Buy&Don't buy#",
                /*french*/"Veux-tu acheter %s pour #200 rubis#?&"+TWO_WAY_CHOICE()+"#Acheter&Ne pas acheter#",
               /*spanish*/"¿Me compras %s por #200 rupias#?&"+TWO_WAY_CHOICE()+"#Comprar&No comprar#",
               /*italian*/"Che ne dici? Vuoi comprrrarrre %s per #200 rupie#?&"+TWO_WAY_CHOICE()+"#Sì&No#",
                /*german*/"Möchtest du %s für #200 Rubine# kaufen?&"+TWO_WAY_CHOICE()+"#Klar!&Nie im Leben!#"},
    });

    hintTable[CARPET_SALESMAN_DIALOG_FIRST] = HintText::MerchantsDialogs({
                     // obscure text
                     Text{"Welcome!^I am selling stuff, strange and rare, from&all over the world to everybody. Today's&special is...^"
                          "%s! Terrifying! I won't tell you what it is until I see the money...^How about #200 Rupees#?&&"+TWO_WAY_CHOICE()+"#Buy&Don't buy#",
                /*french*/"Bienvenue!^Je vends des objets rares et merveilleux du&monde entier. En spécial aujourd'hui...^"
                          "%s! Un concentré de puissance! Mais montre tes rubis avant que je te dise ce que c'est...^Disons #200 rubis#?&&"+TWO_WAY_CHOICE()+"#Acheter&Ne pas acheter#",
               /*spanish*/"¡Acércate!^Vendo productos extraños y difíciles de&encontrar... De todo el mundo a todo el&mundo. La oferta de hoy es...^"
                          "¡%s! ¡Terrorífico! No te revelaré su nombre hasta que vea el dinero...^#200 rupias#, ¿qué te parece?&&"+TWO_WAY_CHOICE()+"#Comprar&No comprar#",
               /*italian*/"Benvenuto!^Vendo merce strana e introvabile che&proviene da ogni parte del mondo.&Oggi il pezzo forte è...^"
                          "%s! Non ti dico di che si tratta finché non vedo la grana.^Hai #200 rupie#?&&"+TWO_WAY_CHOICE()+"#Tieni!&Veramente no...#",
                /*german*/"Willkommen!^Ich verkaufe hier seltsame,&seltene Sachen aus der ganzen Welt.^Mein heutiges Angebot...&"
                          "%s!&Furchterregend oder? Ich erzähle Euch mehr, wenn ich Geld sehe...^Wie wär's mit #200 Rubinen#?&&"+TWO_WAY_CHOICE()+"#Aber sicher!&Ich bin weg!#"},
    });

    hintTable[CARPET_SALESMAN_DIALOG_SECOND] = HintText::MerchantsDialogs({
                     // obscure text
                     Text{"Thank you very much!^What I'm selling is... "
                          "#%s!#^The mark that will lead you to the #Spirit&Temple# is the #flag on the "+IF_NOT_MQ()+"left"+MQ_ELSE()+"right"+MQ_END()+"# outside the shop. Be seeing you!",
                /*french*/"Merci beaucoup!^Cet objet extraordinaire est... "
                          "#%s!#^La marque qui te mènera au #Temple de l'esprit# est le #drapeau "+IF_NOT_MQ()+"gauche"+MQ_ELSE()+"droite"+MQ_END()+"# en sortant d'ici. À la prochaine!",
               /*spanish*/"¡Muchas gracias!^Lo que vendo es... "
                          "¡#%s!#^La marca que te guiará al #Templo del&Espíritu# es la #bandera que está a la&"+IF_NOT_MQ()+"izquierda"+MQ_ELSE()+"derecha"+MQ_END()+"# al salir de aquí. ¡Nos vemos!",
               /*italian*/"Grazie!^Hai appena comprato... "
                          "#%s!#^La direzione per il #Santuario dello Spirito# è indicata dalla #bandiera sulla "+IF_NOT_MQ()+"sinistra"+MQ_ELSE()+"destra"+MQ_END()+"# del negozio. A presto!",
                /*german*/"Vielen herzlichen Dank!&"
                          "#%s#! Toll oder?^Das Zeichen, welches Euch zum&#Geistertempel# führt, ist die #Flagge&zur "+IF_NOT_MQ()+"Linken"+MQ_ELSE()+"Rechten"+MQ_END()+"# außerhalb des Ladens.^Schaut mal wieder vorbei!"},
    });

    hintTable[GRANNY_DIALOG] = HintText::MerchantsDialogs({
                     // obscure text
                     Text{"! How about #100 Rupees#?&"+TWO_WAY_CHOICE()+"#Buy&Don't buy#",
                /*french*/"! Que dis-tu de #100 rubis#?&"+TWO_WAY_CHOICE()+"#Acheter&Ne pas acheter#",
               /*spanish*/". Vendo por #100 rupias#.&"+TWO_WAY_CHOICE()+"#Comprar&No comprar#",
               /*italian*/"! Che ne dici di #100 rupie#?&"+TWO_WAY_CHOICE()+"#Aggiudicato!&Non mi serve...#",
                /*german*/"! Sagen wir #100 Rubine#!&"+TWO_WAY_CHOICE()+"#Gerne!&Auf keinen Fall!#"},
    });

    /*----------------------------------
    |         DAMPÉ DIARY TEXT         |
    -----------------------------------*/

    hintTable[DAMPE_DIARY_HINT] = HintText::DampeHint({
                     // obscure text
                     Text{"Whoever reads this, please enter #%s#. I will let you have my stretching, shrinking #keepsake#.^I'm waiting for you.&--Dampé",
                /*french*/"Toi, le petit curieux qui lit ce journal, viens dans #%s#. Et peut-être auras-tu droit à mon précieux #trésor#.^Je t'attends...&--Igor",
               /*spanish*/"A quien lea estas palabras: Entra en #%s# y mi fantástico #tesoro# será para ti.^Te espero.&- Dampé",
               /*italian*/"Chiunque legga questo, visiti #%s#. Gli darò il mio #tesoro# BOING BOING.^Firmato: Danpei",
                /*german*/"Wer immer dies liest, der möge #%s# betreten. Ihm gebe ich meinen langen, kurzen #Schatz#^Ich warte! Boris"},
    });

    /*----------------------------------
    |     HOUSE OF SKULLTULA HINTS     |
    -----------------------------------*/

    hintTable[HOUSE_OF_SKULLTULA_HINT] = HintText::SkulltulaHints({
                     // obscure text
                     Text{"Yeaaarrgh! I'm cursed!! Please save me by destroying #%d Spiders of the Curse# and I will give you #%s#.",
                /*french*/"Beuaaaaark! Je suis maudit! Je t'en supplie, aide-moi en vainquant #%d araignées d'or# et je te donnerai #%s#.",
               /*spanish*/"¡Grrrrrr! ¡Estoy maldito! Por favor, sálvame destruyendo #%d Arañas de la Maldición# y yo te daría #%s#.",
               /*italian*/"Ahhhhhhhh! Questa maledizione è davvero terribile! Ti prego, salvami distruggendo #%d Aracnule d'oro# e ti darò #%s#.",
                /*german*/"Aarrrgh! Ich bin verflucht!^Bitte rette mich, indem du #%d Skulltulas# zerstörst und ich werde dir dafür #%s# geben!"},
    });
}
// clang-format on
s32 StonesRequiredBySettings() {
    s32 stones = 0;
    if (Settings::Bridge.Is(RAINBOWBRIDGE_STONES)) {
        stones = std::max<s32>({ stones, (s32)Settings::BridgeStoneCount.Value<u8>() });
    }
    if (Settings::Bridge.Is(RAINBOWBRIDGE_REWARDS)) {
        stones = std::max<s32>({ stones, (s32)Settings::BridgeRewardCount.Value<u8>() - 6 });
    }
    if ((Settings::Bridge.Is(RAINBOWBRIDGE_DUNGEONS)) && (Settings::ShuffleRewards.Is(REWARDSHUFFLE_END_OF_DUNGEON))) {
        stones = std::max<s32>({ stones, (s32)Settings::BridgeDungeonCount.Value<u8>() - 6 });
    }
    if (Settings::GanonsBossKey.Is(GANONSBOSSKEY_LACS_STONES)) {
        stones = std::max<s32>({ stones, (s32)Settings::LACSStoneCount.Value<u8>() });
    }
    if (Settings::GanonsBossKey.Is(GANONSBOSSKEY_LACS_REWARDS)) {
        stones = std::max<s32>({ stones, (s32)Settings::LACSRewardCount.Value<u8>() - 6 });
    }
    if (Settings::GanonsBossKey.Is(GANONSBOSSKEY_LACS_DUNGEONS)) {
        stones = std::max<s32>({ stones, (s32)Settings::LACSDungeonCount.Value<u8>() - 6 });
    }
    return stones;
}

s32 MedallionsRequiredBySettings() {
    s32 medallions = 0;
    if (Settings::Bridge.Is(RAINBOWBRIDGE_MEDALLIONS)) {
        medallions = std::max<s32>({ medallions, (s32)Settings::BridgeMedallionCount.Value<u8>() });
    }
    if (Settings::Bridge.Is(RAINBOWBRIDGE_REWARDS)) {
        medallions = std::max<s32>({ medallions, (s32)Settings::BridgeRewardCount.Value<u8>() - 3 });
    }
    if ((Settings::Bridge.Is(RAINBOWBRIDGE_DUNGEONS)) && (Settings::ShuffleRewards.Is(REWARDSHUFFLE_END_OF_DUNGEON))) {
        medallions = std::max<s32>({ medallions, (s32)Settings::BridgeDungeonCount.Value<u8>() - 3 });
    }
    if (Settings::GanonsBossKey.Is(GANONSBOSSKEY_LACS_MEDALLIONS)) {
        medallions = std::max<s32>({ medallions, (s32)Settings::LACSMedallionCount.Value<u8>() });
    }
    if (Settings::GanonsBossKey.Is(GANONSBOSSKEY_LACS_REWARDS)) {
        medallions = std::max<s32>({ medallions, (s32)Settings::LACSRewardCount.Value<u8>() - 3 });
    }
    if (Settings::GanonsBossKey.Is(GANONSBOSSKEY_LACS_DUNGEONS)) {
        medallions = std::max<s32>({ medallions, (s32)Settings::LACSDungeonCount.Value<u8>() - 3 });
    }
    return medallions;
}

s32 TokensRequiredBySettings() {
    s32 tokens = 0;
    if (Settings::Bridge.Is(RAINBOWBRIDGE_TOKENS)) {
        tokens = std::max<s32>({ tokens, (s32)Settings::BridgeTokenCount.Value<u8>() });
    }
    if (Settings::GanonsBossKey.Is(GANONSBOSSKEY_LACS_TOKENS)) {
        tokens = std::max<s32>({ tokens, (s32)Settings::LACSTokenCount.Value<u8>() });
    }
    return tokens;
}

std::array<ConditionalAlwaysHint, 9> conditionalAlwaysHints = {
    std::make_pair(MARKET_10_BIG_POES,
                   []() {
                       return Settings::BigPoeTargetCount.Value<u8>() >= 3;
                   }), // Remember, the option's value being 3 means 4 are required
    std::make_pair(DEKU_THEATER_MASK_OF_TRUTH, []() { return !Settings::CompleteMaskQuest; }),
    std::make_pair(SONG_FROM_OCARINA_OF_TIME, []() { return StonesRequiredBySettings() < 2; }),
    std::make_pair(HF_OCARINA_OF_TIME_ITEM, []() { return StonesRequiredBySettings() < 2; }),
    std::make_pair(SHEIK_IN_KAKARIKO, []() { return MedallionsRequiredBySettings() < 5; }),
    std::make_pair(DMT_TRADE_CLAIM_CHECK, []() { return false; }),
    std::make_pair(KAK_30_GOLD_SKULLTULA_REWARD, []() { return TokensRequiredBySettings() < 30; }),
    std::make_pair(KAK_40_GOLD_SKULLTULA_REWARD, []() { return TokensRequiredBySettings() < 40; }),
    std::make_pair(KAK_50_GOLD_SKULLTULA_REWARD, []() { return TokensRequiredBySettings() < 50; })
};

const HintText& Hint(const HintKey hintKey) {
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
