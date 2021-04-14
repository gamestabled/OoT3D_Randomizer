#include "custom_messages.hpp"
#include "patch_symbols.hpp"

#include <array>

namespace CustomMessages {

constexpr std::array EnglishDungeonNames = {
    "Deku Tree",
    "Dodongo's Cavern",
    "Jabu Jabu's Belly",
    "Forest Temple",
    "Fire Temple",
    "Water Temple",
    "Spirit Temple",
    "Shadow Temple",
    "Bottom of the Well",
    "Ice Cavern",
    "Ganon's Tower",
    "Gerudo Training Grounds",
    "Gerudo Fortress",
    "Ganon's Castle",
};

constexpr std::array FrenchDungeonNames = {
    "Arbre Mojo",
    "Caverne Dodongo",
    "Ventre de Jabu-Jabu",
    "Temple de la Forêt",
    "Temple du Feu",
    "Temple de l'Eau",
    "Temple de l'Esprit",
    "Temple de l'Ombre",
    "Puits",
    "Caverne de glace",
    "",
    "Gymnase Gerudo",
    "Forteresse Gerudo",
    "Château de Ganon",
};

constexpr std::array FrenchDungeonArticles = {
    "de l'",
    "de la",
    "du",
    "du",
    "du",
    "du",
    "du",
    "du",
    "du",
    "de la",
    "",
    "du",
    "de la",
    "du",
};

constexpr std::array SpanishDungeonNames = {
    "Gran Árbol Deku",
    "Cueva de los Dodongos",
    "Barriga de Jabu-Jabu",
    "Templo del Bosque",
    "Templo de Fuego",
    "Templo del Agua",
    "Templo del Espíritu",
    "Templo de las Sombras",
    "Fondo del Pozo",
    "Caverna de hielo",
    "",
    "Centro de Instrucción Gerudo",
    "Fortaleza Gerudo",
    "Castillo de Ganon",
};

constexpr std::array SpanishDungeonArticles = {
    "del",
    "de la",
    "de la",
    "del",
    "del",
    "del",
    "del",
    "del",
    "del",
    "de la",
    "",
    "del",
    "de la",
    "del",
};

constexpr std::array DungeonColors = {
    CustomMessages::QM_GREEN,
    CustomMessages::QM_RED,
    CustomMessages::QM_BLUE,
    CustomMessages::QM_GREEN,
    CustomMessages::QM_RED,
    CustomMessages::QM_BLUE,
    CustomMessages::QM_YELLOW,
    CustomMessages::QM_PINK,
    CustomMessages::QM_PINK,
    CustomMessages::QM_LBLUE,
    CustomMessages::QM_BLACK,
    CustomMessages::QM_YELLOW,
    CustomMessages::QM_YELLOW,
    CustomMessages::QM_RED,
};

    std::set<MessageEntry, MessageEntryComp> messageEntries;
    std::vector<MessageEntry> arrangedMessageEntries;
    std::stringstream messageData;
    std::string arrangedMessageData;

    void CreateMessage(u32 textId, u32 unk_04, u32 unk_08, u32 unk_0C,
        std::string englishText, std::string frenchText, std::string spanishText) {
            MessageEntry newEntry = { textId, unk_04, unk_08, unk_0C, { 0 } };

            while ((englishText.size() % 4) != 0) englishText += "\0"s;
            messageData.seekg(0, messageData.end);
            newEntry.info[ENGLISH_U].offset = (char*)((int)messageData.tellg()) + RCUSTOMMESSAGES_ADDR;
            newEntry.info[ENGLISH_U].length = englishText.size();
            messageData << englishText;

            while ((frenchText.size() % 4) != 0) frenchText += "\0"s;
            messageData.seekg(0, messageData.end);
            newEntry.info[FRENCH_U].offset = (char*)((int)messageData.tellg()) + RCUSTOMMESSAGES_ADDR;
            newEntry.info[FRENCH_U].length = frenchText.size();
            messageData << frenchText;

            while ((spanishText.size() % 4) != 0) spanishText += "\0"s;
            messageData.seekg(0, messageData.end);
            newEntry.info[SPANISH_U].offset = (char*)((int)messageData.tellg()) + RCUSTOMMESSAGES_ADDR;
            newEntry.info[SPANISH_U].length = spanishText.size();
            messageData << spanishText;

            messageEntries.insert(newEntry);
    }

    u32 NumMessages(void) {
        return messageEntries.size();
    }

    std::pair<const char*, u32> RawMessageEntryData(void) {
        arrangedMessageEntries.assign(messageEntries.begin(), messageEntries.end());
        const char* data = (const char*)arrangedMessageEntries.data();
        u32 size = arrangedMessageEntries.size() * sizeof(MessageEntry);
        return { data, size };
    }

    std::pair<const char*, u32> RawMessageData(void) {
        arrangedMessageData = messageData.str();
        const char* data = arrangedMessageData.data();
        u32 size = arrangedMessageData.size();
        return { data, size };
    }

    void CreateAlwaysIncludedMessages(void) {
        // Bombchu (10) Purchase Prompt
        CreateMessage(0x8C, 0, 2, 3,
            INSTANT_TEXT_ON()+"Bombchu (10): 99 Rupees"+INSTANT_TEXT_OFF()+NEWLINE()+NEWLINE()+TWO_WAY_CHOICE()+COLOR(QM_GREEN)+"Buy"+NEWLINE()+"Don't buy"+COLOR(QM_WHITE)+MESSAGE_END(),
            INSTANT_TEXT_ON()+"Bombchus (10): 99 rubis"+INSTANT_TEXT_OFF()+NEWLINE()+NEWLINE()+TWO_WAY_CHOICE()+COLOR(QM_GREEN)+"Acheter"+NEWLINE()+"Ne pas acheter"+COLOR(QM_WHITE)+MESSAGE_END(),
            INSTANT_TEXT_ON()+"Bombchus (10): 99 rupias"+INSTANT_TEXT_OFF()+NEWLINE()+NEWLINE()+TWO_WAY_CHOICE()+COLOR(QM_GREEN)+"Comprar"+NEWLINE()+"No comprar"+COLOR(QM_WHITE)+MESSAGE_END());
        //Gold Skulltula Tokens
        CreateMessage(0xB4, 0, 2, 3,
            INSTANT_TEXT_ON()+"You destroyed a "+COLOR(QM_RED)+"Gold Skulltula"+COLOR(QM_WHITE)+". You got a"+NEWLINE()+"token proving you destroyed it!"+NEWLINE()+NEWLINE()+"You have "+COLOR(QM_RED)+SKULLTULAS_DESTROYED()+COLOR(QM_WHITE)+" tokens!"+INSTANT_TEXT_OFF()+MESSAGE_END(),
            INSTANT_TEXT_ON()+"Vous venez de détruire une "+COLOR(QM_RED)+"Skulltula dorée"+COLOR(QM_WHITE)+"!"+NEWLINE()+"Ce jeton prouve votre prouesse!"+NEWLINE()+NEWLINE()+"Vous avez "+COLOR(QM_RED)+SKULLTULAS_DESTROYED()+COLOR(QM_WHITE)+" jetons!"+INSTANT_TEXT_OFF()+MESSAGE_END(),
            INSTANT_TEXT_ON()+"¡Has eliminado una "+COLOR(QM_RED)+"skulltula dorada"+COLOR(QM_WHITE)+" y has"+NEWLINE()+"conseguido un símbolo para probarlo!"+NEWLINE()+NEWLINE()+"¡Tienes "+COLOR(QM_RED)+SKULLTULAS_DESTROYED()+COLOR(QM_WHITE)+" símbolos!"+INSTANT_TEXT_OFF()+MESSAGE_END());
        //Bombchu (10) Description
        CreateMessage(0xBC, 0, 2, 3,
            INSTANT_TEXT_ON()+COLOR(QM_RED)+"Bombchu (10): 99 Rupees"+NEWLINE()+COLOR(QM_WHITE)+"These look like toy mice, but they're"+NEWLINE()+"actually self-propelled time bombs!"+INSTANT_TEXT_OFF()+SHOP_MESSAGE_BOX()+MESSAGE_END(),
            INSTANT_TEXT_ON()+COLOR(QM_RED)+"Bombchus (10): 99 rubis"+NEWLINE()+COLOR(QM_WHITE)+"Profilée comme une souris mécanique, il"+NEWLINE()+"s'agit en fait d'une bombe à retardement"+NEWLINE()+"autopropulsée!"+INSTANT_TEXT_OFF()+SHOP_MESSAGE_BOX()+MESSAGE_END(),
            INSTANT_TEXT_ON()+COLOR(QM_RED)+"Bombchus (10): 99 rupias"+NEWLINE()+COLOR(QM_WHITE)+"Aunque parezcan ratoncitos de juguete,"+NEWLINE()+"¡son bombas de tiempo autopropulsadas!"+INSTANT_TEXT_OFF()+SHOP_MESSAGE_BOX()+MESSAGE_END());
        //Boss Keys
        for (u32 bossKey = 0; bossKey <= (DUNGEON_SHADOW_TEMPLE - DUNGEON_FOREST_TEMPLE); bossKey++) {
            u32 dungeon = DUNGEON_FOREST_TEMPLE + bossKey;
            CreateMessage(0x9D4 + bossKey, 0, 2, 3,
                UNSKIPPABLE()+ITEM_OBTAINED(ITEM_KEY_BOSS)+INSTANT_TEXT_ON()+"You got the "+COLOR(DungeonColors[dungeon])+EnglishDungeonNames[dungeon]+NEWLINE()+"Boss Key"+COLOR(QM_WHITE)+"!"+INSTANT_TEXT_OFF()+MESSAGE_END(),
                UNSKIPPABLE()+ITEM_OBTAINED(ITEM_KEY_BOSS)+INSTANT_TEXT_ON()+"Vous trouvez la "+COLOR(DungeonColors[dungeon])+"grande clé du boss "+NEWLINE()+FrenchDungeonArticles[dungeon]+FrenchDungeonNames[dungeon]+COLOR(QM_WHITE)+"!"+INSTANT_TEXT_OFF()+MESSAGE_END(),
                UNSKIPPABLE()+ITEM_OBTAINED(ITEM_KEY_BOSS)+INSTANT_TEXT_ON()+"¡Tienes la "+COLOR(DungeonColors[dungeon])+"gran llave "+SpanishDungeonArticles[dungeon]+NEWLINE()+SpanishDungeonNames[dungeon]+COLOR(QM_WHITE)+"!"+INSTANT_TEXT_OFF()+MESSAGE_END());
        }
        CreateMessage(0x9D9, 0, 2, 3,
            UNSKIPPABLE()+ITEM_OBTAINED(ITEM_KEY_BOSS)+INSTANT_TEXT_ON()+"You got the "+COLOR(DungeonColors[DUNGEON_GANONS_CASTLE_FIRST_PART])+EnglishDungeonNames[DUNGEON_GANONS_CASTLE_FIRST_PART]+NEWLINE()+"Boss Key"+COLOR(QM_WHITE)+"!"+INSTANT_TEXT_OFF()+MESSAGE_END(),
            UNSKIPPABLE()+ITEM_OBTAINED(ITEM_KEY_BOSS)+INSTANT_TEXT_ON()+"Vous trouvez la "+COLOR(DungeonColors[DUNGEON_GANONS_CASTLE_FIRST_PART])+"grande clé du boss "+NEWLINE()+FrenchDungeonArticles[DUNGEON_GANONS_CASTLE_FIRST_PART]+FrenchDungeonNames[DUNGEON_GANONS_CASTLE_FIRST_PART]+COLOR(QM_WHITE)+"!"+INSTANT_TEXT_OFF()+MESSAGE_END(),
            UNSKIPPABLE()+ITEM_OBTAINED(ITEM_KEY_BOSS)+INSTANT_TEXT_ON()+"¡Tienes la "+COLOR(DungeonColors[DUNGEON_GANONS_CASTLE_FIRST_PART])+"gran llave "+SpanishDungeonArticles[DUNGEON_GANONS_CASTLE_FIRST_PART]+NEWLINE()+SpanishDungeonNames[DUNGEON_GANONS_CASTLE_FIRST_PART]+COLOR(QM_WHITE)+"!"+INSTANT_TEXT_OFF()+MESSAGE_END());
        //Compasses
        for (u32 dungeon = DUNGEON_DEKU_TREE; dungeon <= DUNGEON_ICE_CAVERN; dungeon++) {
            CreateMessage(0x9DA + dungeon, 0, 2, 3,
                UNSKIPPABLE()+ITEM_OBTAINED(ITEM_COMPASS)+INSTANT_TEXT_ON()+"You got the "+COLOR(DungeonColors[dungeon])+EnglishDungeonNames[dungeon]+NEWLINE()+"Compass"+COLOR(QM_WHITE)+"!"+INSTANT_TEXT_OFF()+MESSAGE_END(),
                UNSKIPPABLE()+ITEM_OBTAINED(ITEM_COMPASS)+INSTANT_TEXT_ON()+"Vous trouvez la "+COLOR(DungeonColors[dungeon])+"boussole "+NEWLINE()+FrenchDungeonArticles[dungeon]+FrenchDungeonNames[dungeon]+COLOR(QM_WHITE)+"!"+INSTANT_TEXT_OFF()+MESSAGE_END(),
                UNSKIPPABLE()+ITEM_OBTAINED(ITEM_COMPASS)+INSTANT_TEXT_ON()+"¡Tienes la "+COLOR(DungeonColors[dungeon])+"brújula "+SpanishDungeonArticles[dungeon]+NEWLINE()+SpanishDungeonNames[dungeon]+COLOR(QM_WHITE)+"!"+INSTANT_TEXT_OFF()+MESSAGE_END());
        }
        //Maps
        for (u32 dungeon = DUNGEON_DEKU_TREE; dungeon <= DUNGEON_ICE_CAVERN; dungeon++) {
            CreateMessage(0x9E4 + dungeon, 0, 2, 3,
                UNSKIPPABLE()+ITEM_OBTAINED(ITEM_DUNGEON_MAP)+INSTANT_TEXT_ON()+"You got the "+COLOR(DungeonColors[dungeon])+EnglishDungeonNames[dungeon]+NEWLINE()+"Map"+COLOR(QM_WHITE)+"!"+INSTANT_TEXT_OFF()+MESSAGE_END(),
                UNSKIPPABLE()+ITEM_OBTAINED(ITEM_DUNGEON_MAP)+INSTANT_TEXT_ON()+"Vous trouvez la "+COLOR(DungeonColors[dungeon])+"carte "+NEWLINE()+FrenchDungeonArticles[dungeon]+FrenchDungeonNames[dungeon]+COLOR(QM_WHITE)+"!"+INSTANT_TEXT_OFF()+MESSAGE_END(),
                UNSKIPPABLE()+ITEM_OBTAINED(ITEM_DUNGEON_MAP)+INSTANT_TEXT_ON()+"¡Tienes la "+COLOR(DungeonColors[dungeon])+"mapa "+SpanishDungeonArticles[dungeon]+NEWLINE()+SpanishDungeonNames[dungeon]+COLOR(QM_WHITE)+"!"+INSTANT_TEXT_OFF()+MESSAGE_END());
        }
        //Small Keys
        for (u32 smallKey = 0; smallKey <= (DUNGEON_BOTTOM_OF_THE_WELL - DUNGEON_FOREST_TEMPLE); smallKey++) {
            u32 dungeon = DUNGEON_FOREST_TEMPLE + smallKey;
            CreateMessage(0x9EE + smallKey, 0, 2, 3,
                UNSKIPPABLE()+ITEM_OBTAINED(ITEM_KEY_SMALL)+INSTANT_TEXT_ON()+"You got a "+COLOR(DungeonColors[dungeon])+EnglishDungeonNames[dungeon]+NEWLINE()+"Small Key"+COLOR(QM_WHITE)+"!"+INSTANT_TEXT_OFF()+MESSAGE_END(),
                UNSKIPPABLE()+ITEM_OBTAINED(ITEM_KEY_SMALL)+INSTANT_TEXT_ON()+"Vous trouvez une "+COLOR(DungeonColors[dungeon])+"petite clé"+NEWLINE()+FrenchDungeonArticles[dungeon]+FrenchDungeonNames[dungeon]+COLOR(QM_WHITE)+"!"+INSTANT_TEXT_OFF()+MESSAGE_END(),
                UNSKIPPABLE()+ITEM_OBTAINED(ITEM_KEY_SMALL)+INSTANT_TEXT_ON()+"¡Es una "+COLOR(DungeonColors[dungeon])+"llave pequeña "+SpanishDungeonArticles[dungeon]+NEWLINE()+SpanishDungeonNames[dungeon]+COLOR(QM_WHITE)+"!"+INSTANT_TEXT_OFF()+MESSAGE_END());
        }
        for (u32 smallKey = 0; smallKey <= (DUNGEON_GANONS_CASTLE_FIRST_PART - DUNGEON_GERUDO_TRAINING_GROUNDS); smallKey++) {
            u32 dungeon = DUNGEON_GERUDO_TRAINING_GROUNDS + smallKey;
            CreateMessage(0x9F4 + smallKey, 0, 2, 3,
                UNSKIPPABLE()+ITEM_OBTAINED(ITEM_KEY_SMALL)+INSTANT_TEXT_ON()+"You got a "+COLOR(DungeonColors[dungeon])+EnglishDungeonNames[dungeon]+NEWLINE()+"Small Key"+COLOR(QM_WHITE)+"!"+INSTANT_TEXT_OFF()+MESSAGE_END(),
                UNSKIPPABLE()+ITEM_OBTAINED(ITEM_KEY_SMALL)+INSTANT_TEXT_ON()+"Vous trouvez une "+COLOR(DungeonColors[dungeon])+"petite clé"+NEWLINE()+FrenchDungeonArticles[dungeon]+FrenchDungeonNames[dungeon]+COLOR(QM_WHITE)+"!"+INSTANT_TEXT_OFF()+MESSAGE_END(),
                UNSKIPPABLE()+ITEM_OBTAINED(ITEM_KEY_SMALL)+INSTANT_TEXT_ON()+"¡Es una "+COLOR(DungeonColors[dungeon])+"llave pequeña "+SpanishDungeonArticles[dungeon]+NEWLINE()+SpanishDungeonNames[dungeon]+COLOR(QM_WHITE)+"!"+INSTANT_TEXT_OFF()+MESSAGE_END());
        }
        //Poe Collector (when enough has been sold)
        CreateMessage(0x70F8, 0, 0, 0,
            UNSKIPPABLE()+"Wait a minute! WOW!"+WAIT_FOR_INPUT()+NEWLINE()+UNSKIPPABLE()+"You have earned enough points!"+WAIT_FOR_INPUT()+NEWLINE()+UNSKIPPABLE()+"Young man, you are a genuine "+COLOR(QM_RED)+"ghost hunter"+COLOR(QM_WHITE)+"!"+WAIT_FOR_INPUT()+NEWLINE()+UNSKIPPABLE()
                +"Is that what you expected me to say?"+NEWLINE()+"Heh heh heh!"+WAIT_FOR_INPUT()+NEWLINE()+UNSKIPPABLE()+"Because of you, I have extra inventory of"+NEWLINE()+COLOR(QM_RED)+"Big Poes"+COLOR(QM_WHITE)+", so this will be the last time I can"+NEWLINE()
                +"buy one of these ghosts."+WAIT_FOR_INPUT()+NEWLINE()+UNSKIPPABLE()+"You're thinking about what I promised would"+NEWLINE()+"happen when you earned enough points."+NEWLINE()+"Heh heh."+WAIT_FOR_INPUT()+NEWLINE()+UNSKIPPABLE()
                +"Don't worry. I didn't forget. Just take this."+MESSAGE_END(),
            UNSKIPPABLE()+"Attends une minute! HOU LA LA!"+WAIT_FOR_INPUT()+NEWLINE()+UNSKIPPABLE()+"Tu as gagné suffisamment de points!"+WAIT_FOR_INPUT()+NEWLINE()+UNSKIPPABLE()+"Jeune homme, tu es un véritable "+COLOR(QM_RED)+"chasseur de fantômes"+COLOR(QM_WHITE)+"!"+WAIT_FOR_INPUT()+NEWLINE()+UNSKIPPABLE()
                +"C'est ce que tu attendais de moi ?"+NEWLINE()+"Heh heh heh!"+WAIT_FOR_INPUT()+NEWLINE()+UNSKIPPABLE()+"Grâce à toi, j'ai un stock supplémentaire de"+NEWLINE()+COLOR(QM_RED)+"grand esprits"+COLOR(QM_WHITE)+", donc ce sera la dernière fois que je peux"+NEWLINE()
                +"achetez un de ces esprits."+WAIT_FOR_INPUT()+NEWLINE()+UNSKIPPABLE()+"Tu penses à ce que j'ai promis"+NEWLINE()+"lorsque tu as gagné suffisamment de points."+NEWLINE()+"Heh heh."+WAIT_FOR_INPUT()+NEWLINE()+UNSKIPPABLE()
                +"Ne t'inquiète pas. Je n'ai pas oublié. Prends ça."+MESSAGE_END(),
            UNSKIPPABLE()+"¡Un momento! ¡OYE!"+WAIT_FOR_INPUT()+NEWLINE()+UNSKIPPABLE()+"¡Has ganado suficientes puntos!"+WAIT_FOR_INPUT()+NEWLINE()+UNSKIPPABLE()+"¡Amigo, eres un auténtico "+COLOR(QM_RED)+"cazador de"+NEWLINE()+"fantasmas"+COLOR(QM_WHITE)+"!"+WAIT_FOR_INPUT()+NEWLINE()+UNSKIPPABLE()
                +"¿Es eso lo que esperabas que dijera?"+NEWLINE()+"¡Je, je je!"+WAIT_FOR_INPUT()+NEWLINE()+UNSKIPPABLE()+"Gracias a ti, tengo existencias de sobra"+NEWLINE()+"de "+COLOR(QM_RED)+"grandes poes"+COLOR(QM_WHITE)+", así que esta será la"+NEWLINE()
                +"última vez que te compre uno de ese tipo."+WAIT_FOR_INPUT()+NEWLINE()+UNSKIPPABLE()+"¿Recuerdas lo que te dije que ocurriría"+NEWLINE()+"cuando tuvieses suficientes puntos?"+NEWLINE()+"Je, je, je."+WAIT_FOR_INPUT()+NEWLINE()+UNSKIPPABLE()
                +"Tranquilo, que no se me ha olvidado."+NEWLINE()+"Toma esto."+MESSAGE_END());
        //Ice Trap
        CreateMessage(0x9002, 0, 2, 3,
            UNSKIPPABLE()+INSTANT_TEXT_ON()+CENTER_TEXT()+COLOR(QM_RED)+"FOOL!"+COLOR(QM_WHITE)+INSTANT_TEXT_OFF()+MESSAGE_END(),
            UNSKIPPABLE()+INSTANT_TEXT_ON()+CENTER_TEXT()+COLOR(QM_RED)+"IDIOT!"+COLOR(QM_WHITE)+INSTANT_TEXT_OFF()+MESSAGE_END(),
            UNSKIPPABLE()+INSTANT_TEXT_ON()+CENTER_TEXT()+COLOR(QM_RED)+"¡TONTO!"+COLOR(QM_WHITE)+INSTANT_TEXT_OFF()+MESSAGE_END());
        //Business Scrubs
        //The less significant byte represents the price of the item
        for (u32 price = 5; price <= 95; price += 5) {
            CreateMessage(0x9000 + price, 0, 0, 0,
                INSTANT_TEXT_ON()+"I'll sell you something good for "+COLOR(QM_RED)+std::to_string(price)+" Rupees"+COLOR(QM_WHITE)+"!"+NEWLINE()+NEWLINE()+"\x7F\x1A\xFF\xFF"+COLOR(QM_GREEN)+"OK"+NEWLINE()+"No way"+COLOR(QM_WHITE)+INSTANT_TEXT_OFF()+MESSAGE_END(),
                INSTANT_TEXT_ON()+"Je te vendrai quelque chose de bien pour "+NEWLINE()+COLOR(QM_RED)+std::to_string(price)+" Rubis"+COLOR(QM_WHITE)+"!"+NEWLINE()+NEWLINE()+"\x7F\x1A\xFF\xFF"+COLOR(QM_GREEN)+"D'accord"+NEWLINE()+"Hors de question"+COLOR(QM_WHITE)+INSTANT_TEXT_OFF()+MESSAGE_END(),
                INSTANT_TEXT_ON()+"¡Te vendo algo bueno por "+COLOR(QM_RED)+std::to_string(price)+" rupias"+COLOR(QM_WHITE)+"!"+NEWLINE()+NEWLINE()+"\x7F\x1A\xFF\xFF"+COLOR(QM_GREEN)+"Bueno"+NEWLINE()+"Ni loco"+COLOR(QM_WHITE)+INSTANT_TEXT_OFF()+MESSAGE_END());
        }
        //Poe Collector
        //The last digit represent the number of poes needed to collect
        for (u32 poes = 1; poes <= 10; poes++) {
            CreateMessage(0x9080 + poes, 0, 0, 0,
                UNSKIPPABLE()+"Oh, you brought a Poe today!"+WAIT_FOR_INPUT()+NEWLINE()+UNSKIPPABLE()+"Hmmmm!"+WAIT_FOR_INPUT()+NEWLINE()+UNSKIPPABLE()+"Very interesting! This is a "+COLOR(QM_RED)+"Big Poe"+COLOR(QM_WHITE)+"!"+WAIT_FOR_INPUT()+NEWLINE()+UNSKIPPABLE()
                    +"I'll buy it for "+COLOR(QM_RED)+"50 Rupees"+COLOR(QM_WHITE)+"."+WAIT_FOR_INPUT()+NEWLINE()+UNSKIPPABLE()+"On top of that, I'll put "+COLOR(QM_RED)+"100 points "+COLOR(QM_WHITE)+"on"+NEWLINE()+"your card."+WAIT_FOR_INPUT()+NEWLINE()+UNSKIPPABLE()
                    +"If you earn "+COLOR(QM_RED)+std::to_string(poes * 100)+" points"+COLOR(QM_WHITE)+", you'll be a"+NEWLINE()+"happy man! Heh heh."+MESSAGE_END(),

                UNSKIPPABLE()+"Oh, tu as amené un esprit aujourd'hui!"+WAIT_FOR_INPUT()+NEWLINE()+UNSKIPPABLE()+"Hmmmm!"+WAIT_FOR_INPUT()+NEWLINE()+UNSKIPPABLE()+"Très intéressant! C'est un "+COLOR(QM_RED)+"Grand esprit"+COLOR(QM_WHITE)+"!"+WAIT_FOR_INPUT()+NEWLINE()+UNSKIPPABLE()
                    +"Je te l'achète pour "+COLOR(QM_RED)+"50 Rubis"+COLOR(QM_WHITE)+"."+WAIT_FOR_INPUT()+NEWLINE()+UNSKIPPABLE()+"En plus de ça, je vais mettre "+COLOR(QM_RED)+"100 points "+COLOR(QM_WHITE)+"sur"+NEWLINE()+"ta carte."+WAIT_FOR_INPUT()+NEWLINE()+UNSKIPPABLE()
                    +"Si tu gagnes "+COLOR(QM_RED)+std::to_string(poes * 100)+" points"+COLOR(QM_WHITE)+", tu seras un"+NEWLINE()+"homme heureux! Heh heh."+MESSAGE_END(),

                UNSKIPPABLE()+"¡Vaya! ¡Traes un poe!"+WAIT_FOR_INPUT()+NEWLINE()+UNSKIPPABLE()+"¡Mmm! ¿A ver?"+WAIT_FOR_INPUT()+NEWLINE()+UNSKIPPABLE()+"¡Qué interesante! ¡Es un "+COLOR(QM_RED)+"gran poe"+COLOR(QM_WHITE)+"!"+WAIT_FOR_INPUT()+NEWLINE()+UNSKIPPABLE()
                    +"Te daré "+COLOR(QM_RED)+"50 rupias "+COLOR(QM_WHITE)+"por él."+WAIT_FOR_INPUT()+NEWLINE()+UNSKIPPABLE()+"Y además agregaré "+COLOR(QM_RED)+"100 puntos "+COLOR(QM_WHITE)+"en tu"+NEWLINE()+"tarjeta."+WAIT_FOR_INPUT()+NEWLINE()+UNSKIPPABLE()
                    +"¡Si llegas a "+COLOR(QM_RED)+std::to_string(poes * 100)+" puntos"+COLOR(QM_WHITE)+", serás muy feliz!"+NEWLINE()+"Je, je, je..."+MESSAGE_END());
        }
    }

    const std::string MESSAGE_END()          { return  "\x7F\x00"s; }
    const std::string WAIT_FOR_INPUT()       { return  "\x7F\x01"s; }
    const std::string HORIZONTAL_SPACE(u8 x) { return  "\x7F\x02"s + char(x); }
    const std::string INSTANT_TEXT_ON()      { return  "\x7F\x04"s; }
    const std::string INSTANT_TEXT_OFF()     { return  "\x7F\x05"s; }
    const std::string SHOP_MESSAGE_BOX()     { return  "\x7F\x06\x00"s; }
    const std::string EVENT_TRIGGER()        { return  "\x7F\x07"s; }
    const std::string DELAY_FRAMES(u8 x)     { return  "\x7F\x08"s + char(x); }
    const std::string CLOSE_AFTER(u8 x)      { return  "\x7F\x0A"s + char(x); }
    const std::string PLAYER_NAME()          { return  "\x7F\x0B"s; }
    const std::string PLAY_OCARINA()         { return  "\x7F\x0C"s; }
    const std::string ITEM_OBTAINED(u8 x)    { return  "\x7F\x0F"s + char(x); }
    const std::string SET_SPEED(u8 x)        { return  "\x7F\x10"s + char(x); }
    const std::string SKULLTULAS_DESTROYED() { return  "\x7F\x15"s; }
    const std::string CURRENT_TIME()         { return  "\x7F\x17"s; }
    const std::string UNSKIPPABLE()          { return  "\x7F\x19"s; }
    const std::string TWO_WAY_CHOICE()       { return  "\x7F\x1A\xFF\xFF\xFF\xFF"s; }
    const std::string NEWLINE()              { return  "\x7F\x1C"s; }
    const std::string COLOR(u8 x)            { return  "\x7F\x1D"s + char(x); }
    const std::string CENTER_TEXT()          { return  "\x7F\x1E"s; }
}
