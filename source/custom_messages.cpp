#include "custom_messages.hpp"
#include "patch_symbols_USA.hpp"
#include "patch_symbols_EUR.hpp"
#include "debug.hpp"
#include "shops.hpp"
#include "../code/src/message.h"
#include "settings.hpp"
#include "../code/src/icetrap.h"

#include <array>
#include <set>
#include <sstream>
#include <map>

#include <unistd.h>

namespace CustomMessages {

using namespace std::literals::string_literals;

class MessageEntryComp {
  public:
    bool operator()(const MessageEntry& lhs, const MessageEntry& rhs) const {
        return lhs.id < rhs.id;
    }
};

constexpr std::array EnglishDungeonNames = {
    "Deku Tree",     "Dodongo's Cavern",        "Jabu Jabu's Belly", "Forest Temple",      "Fire Temple",
    "Water Temple",  "Spirit Temple",           "Shadow Temple",     "Bottom of the Well", "Ice Cavern",
    "Ganon's Tower", "Gerudo Training Grounds", "Gerudo Fortress",   "Ganon's Castle",
};

constexpr std::array FrenchDungeonNames = {
    "vénérable arbre Mojo",
    "caverne Dodongo",
    "ventre de Jabu-Jabu",
    "temple de la forêt",
    "temple du feu",
    "temple de l'eau",
    "temple de l'esprit",
    "temple de l'ombre",
    "puits",
    "caverne de glace",
    "",
    "gymnase Gerudo",
    "forteresse Gerudo",
    "château de Ganon",
};

// clang-format off
constexpr std::array FrenchDungeonArticles = {
    "du ",
    "de la ",
    "du ",
    "du ",
    "du ",
    "du ",
    "du ",
    "du ",
    "du ",
    "de la ",
    "",
    "du ",
    "de la ",
    "du ",
};
// clang-format on

constexpr std::array SpanishDungeonNames = {
    "Gran Árbol Deku", "Cueva de los Dodongos",        "Tripa de Jabu-Jabu",    "Templo del Bosque", "Templo del Fuego",
    "Templo del Agua", "Templo del Espíritu",          "Templo de las Sombras", "Fondo del pozo",    "Caverna de hielo",
    "Torre de Ganon",  "Centro de Instrucción Gerudo", "Fortaleza Gerudo",      "Castillo de Ganon",
};

// clang-format off
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
    "de la",
    "del",
    "de la",
    "del",
};
// clang-format on

constexpr std::array ItalianDungeonNames = {
    "Grande Albero Deku",  "caverna dei Dodongo",  "pancia di Jabu Jabu",     "Santuario della Foresta",
    "Santuario del Fuoco", "Santuario dell'Acqua", "Santuario dello Spirito", "Santuario dell'Ombra",
    "fondo del pozzo",     "caverna di ghiaccio",  "torre di Ganon",          "zona di addestramento Gerudo",
    "fortezza Gerudo",     "castello di Ganon",
};

// clang-format off
constexpr std::array ItalianDungeonArticles = {
    "del",
    "della",
    "della",
    "del",
    "del",
    "del",
    "del",
    "del",
    "del",
    "della",
    "della",
    "della",
    "della",
    "del",
};
// clang-format on

constexpr std::array GermanDungeonNames = {
    "Deku-Baum",    "Dodongos Höhle",        "Jabu Jabus Bauch", "Waldtempel",         "Feuertempel",
    "Wassertempel", "Geistertempel",         "Schattentempel",   "Grund des Brunnens", "Eishöhle",
    "Teufelsturm",  "Gerudo Trainingsarena", "Diebesversteck",   "Ganons Schloss",
};

constexpr std::array GermanDungeonArticles = {
    "des ", "von ", "von ", "des ", "des ", "des ", "des ", "des ", "vom ", "der ", "des ", "der ", "des ", "von ",
};

constexpr std::array GermanDungeonGenitiv = {
    "es ", " ", " ", "s ", "s ", "s ", "s ", "s ", " ", " ", "s", " ", "s ", " ",
};

constexpr std::array DungeonColors = {
    QM_GREEN, QM_RED,  QM_BLUE,  QM_GREEN, QM_RED,    QM_BLUE,   QM_YELLOW,
    QM_PINK,  QM_PINK, QM_LBLUE, QM_BLACK, QM_YELLOW, QM_YELLOW, QM_RED,
};

std::set<MessageEntry, MessageEntryComp> messageEntries;
std::vector<MessageEntry> arrangedMessageEntries;
std::stringstream messageData;
std::string arrangedMessageData;

// textBoxType and textBoxPosition are defined here: https://wiki.cloudmodding.com/oot/Text_Format#Message_Id
void CreateMessage(u32 textId, u32 unk_04, u32 textBoxType, u32 textBoxPosition, std::string NAEnglishText,
                   std::string NAFrenchText, std::string NASpanishText, std::string EUREnglishText,
                   std::string EURFrenchText, std::string EURSpanishText, std::string EURItalianText,
                   std::string EURGermanText) {
#ifdef ENABLE_DEBUG
    static std::vector<u32> usedTextIds;
    if (messageEntries.empty()) {
        usedTextIds.clear();
    }
    if (std::find(usedTextIds.begin(), usedTextIds.end(), textId) != usedTextIds.end()) {
        CitraPrint("Multiple custom messages use text id " + std::to_string(textId));
        printf("\x1b[31m\x1b[9;10H!!Text ID error!!         \x1b[37m");
    } else {
        usedTextIds.push_back(textId);
    }
#endif
    MessageEntry newEntry = { textId, unk_04, textBoxType, textBoxPosition, { 0 } };

    if (Settings::Region == REGION_NA) {
        while ((NAEnglishText.size() % 4) != 0) {
            NAEnglishText += "\0"s;
        }
        messageData.seekg(0, messageData.end);
        newEntry.info[ENGLISH_U].offset = (char*)((int)messageData.tellg()) + RCUSTOMMESSAGES_USA_ADDR;
        newEntry.info[ENGLISH_U].length = NAEnglishText.size();
        messageData << NAEnglishText;

        while ((NAFrenchText.size() % 4) != 0) {
            NAFrenchText += "\0"s;
        }
        messageData.seekg(0, messageData.end);
        newEntry.info[FRENCH_U].offset = (char*)((int)messageData.tellg()) + RCUSTOMMESSAGES_USA_ADDR;
        newEntry.info[FRENCH_U].length = NAFrenchText.size();
        messageData << NAFrenchText;

        while ((NASpanishText.size() % 4) != 0) {
            NASpanishText += "\0"s;
        }
        messageData.seekg(0, messageData.end);
        newEntry.info[SPANISH_U].offset = (char*)((int)messageData.tellg()) + RCUSTOMMESSAGES_USA_ADDR;
        newEntry.info[SPANISH_U].length = NASpanishText.size();
        messageData << NASpanishText;
    } else if (Settings::Region == REGION_EUR) {
        while ((EUREnglishText.size() % 4) != 0) {
            EUREnglishText += "\0"s;
        }
        messageData.seekg(0, messageData.end);
        newEntry.info[ENGLISH_E].offset = (char*)((int)messageData.tellg()) + RCUSTOMMESSAGES_EUR_ADDR;
        newEntry.info[ENGLISH_E].length = EUREnglishText.size();
        messageData << EUREnglishText;

        while ((EURFrenchText.size() % 4) != 0) {
            EURFrenchText += "\0"s;
        }
        messageData.seekg(0, messageData.end);
        newEntry.info[FRENCH_E].offset = (char*)((int)messageData.tellg()) + RCUSTOMMESSAGES_EUR_ADDR;
        newEntry.info[FRENCH_E].length = EURFrenchText.size();
        messageData << EURFrenchText;

        while ((EURSpanishText.size() % 4) != 0) {
            EURSpanishText += "\0"s;
        }
        messageData.seekg(0, messageData.end);
        newEntry.info[SPANISH_E].offset = (char*)((int)messageData.tellg()) + RCUSTOMMESSAGES_EUR_ADDR;
        newEntry.info[SPANISH_E].length = EURSpanishText.size();
        messageData << EURSpanishText;

        while ((EURItalianText.size() % 4) != 0) {
            EURItalianText += "\0"s;
        }
        messageData.seekg(0, messageData.end);
        newEntry.info[ITALIAN_E].offset = (char*)((int)messageData.tellg()) + RCUSTOMMESSAGES_EUR_ADDR;
        newEntry.info[ITALIAN_E].length = EURItalianText.size();
        messageData << EURItalianText;

        while ((EURGermanText.size() % 4) != 0) {
            EURGermanText += "\0"s;
        }
        messageData.seekg(0, messageData.end);
        newEntry.info[GERMAN_E].offset = (char*)((int)messageData.tellg()) + RCUSTOMMESSAGES_EUR_ADDR;
        newEntry.info[GERMAN_E].length = EURGermanText.size();
        messageData << EURGermanText;
    }

    messageEntries.insert(newEntry);
}

void CreateMessage(u32 textId, u32 unk_04, u32 textBoxType, u32 textBoxPosition, std::string englishText,
                   std::string frenchText, std::string spanishText, std::string italianText, std::string germanText) {
    CreateMessage(textId, unk_04, textBoxType, textBoxPosition, englishText, frenchText, spanishText, englishText,
                  frenchText, spanishText, italianText, germanText);
}

void CreateMessageFromTextObject(u32 textId, u32 unk_04, u32 textBoxType, u32 textBoxPosition, const Text& text) {
    CreateMessage(textId, unk_04, textBoxType, textBoxPosition, text.GetNAEnglish(), text.GetNAFrench(),
                  text.GetNASpanish(), text.GetEUREnglish(), text.GetEURFrench(), text.GetEURSpanish(),
                  text.GetEURItalian(), text.GetEURGerman());
}

u32 NumMessages() {
    return messageEntries.size();
}

std::pair<const char*, u32> RawMessageEntryData() {
    arrangedMessageEntries.assign(messageEntries.begin(), messageEntries.end());
    const char* data = (const char*)arrangedMessageEntries.data();
    u32 size         = arrangedMessageEntries.size() * sizeof(MessageEntry);
    return { data, size };
}

std::pair<const char*, u32> RawMessageData() {
    arrangedMessageData = messageData.str();
    const char* data    = arrangedMessageData.data();
    u32 size            = arrangedMessageData.size();
    return { data, size };
}

void CreateAlwaysIncludedMessages() {
    // Bombchu (10) Purchase Prompt
    CreateMessage(
        0x8C, 0, 2, 3,
        INSTANT_TEXT_ON() + "Bombchu (10): 99 Rupees" + INSTANT_TEXT_OFF() + NEWLINE() + NEWLINE() + TWO_WAY_CHOICE() +
            COLOR(QM_GREEN) + "Buy" + NEWLINE() + "Don't buy" + COLOR(QM_WHITE) + MESSAGE_END(),
        INSTANT_TEXT_ON() + "Bombchus (10): 99 rubis" + INSTANT_TEXT_OFF() + NEWLINE() + NEWLINE() + TWO_WAY_CHOICE() +
            COLOR(QM_GREEN) + "Acheter" + NEWLINE() + "Ne pas acheter" + COLOR(QM_WHITE) + MESSAGE_END(),
        INSTANT_TEXT_ON() + "Bombchus (10): 99 rupias" + INSTANT_TEXT_OFF() + NEWLINE() + NEWLINE() + TWO_WAY_CHOICE() +
            COLOR(QM_GREEN) + "Comprar" + NEWLINE() + "No comprar" + COLOR(QM_WHITE) + MESSAGE_END(),
        INSTANT_TEXT_ON() + "10 radiomine - 99 rupie" + INSTANT_TEXT_OFF() + NEWLINE() + NEWLINE() + TWO_WAY_CHOICE() +
            COLOR(QM_GREEN) + "Compra" + NEWLINE() + "Non comprare" + COLOR(QM_WHITE) + MESSAGE_END(),
        INSTANT_TEXT_ON() + "Krabbelminen (10 Stück): 99 Rubine" + INSTANT_TEXT_OFF() + NEWLINE() + NEWLINE() +
            TWO_WAY_CHOICE() + COLOR(QM_GREEN) + "Kaufen!" + NEWLINE() + "Nicht kaufen!" + COLOR(QM_WHITE) +
            MESSAGE_END());
    // Gold Skulltula Tokens (there are two text IDs the game uses)
    for (const u32 textId : { 0xB4, 0xB5 }) {
        CreateMessage(textId, 0, 2, 3,
                      INSTANT_TEXT_ON() + "You destroyed a " + COLOR(QM_RED) + "Gold Skulltula" + COLOR(QM_WHITE) +
                          ". You got a" + NEWLINE() + "token proving you destroyed it!" + NEWLINE() + NEWLINE() +
                          "You have " + COLOR(QM_RED) + SKULLTULAS_DESTROYED() + COLOR(QM_WHITE) + " tokens!" +
                          INSTANT_TEXT_OFF() + MESSAGE_END(),
                      INSTANT_TEXT_ON() + "Vous venez de détruire une " + COLOR(QM_RED) + "Skulltula d'or" +
                          COLOR(QM_WHITE) + "!" + NEWLINE() + "Ce symbole prouve votre prouesse!" + NEWLINE() +
                          NEWLINE() + "Vous avez " + COLOR(QM_RED) + SKULLTULAS_DESTROYED() + COLOR(QM_WHITE) +
                          " jetons!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
                      INSTANT_TEXT_ON() + "¡Has eliminado una " + COLOR(QM_RED) + "skulltula dorada" + COLOR(QM_WHITE) +
                          " y has" + NEWLINE() + "conseguido un símbolo para probarlo!" + NEWLINE() + NEWLINE() +
                          "¡Tienes " + COLOR(QM_RED) + SKULLTULAS_DESTROYED() + COLOR(QM_WHITE) + " símbolos!" +
                          INSTANT_TEXT_OFF() + MESSAGE_END(),
                      INSTANT_TEXT_ON() + "Hai eliminato un'" + COLOR(QM_RED) + "Aracnula d'oro" + COLOR(QM_WHITE) +
                          "." + NEWLINE() + "Il teschio d'oro attesta la tua impresa!" + NEWLINE() + NEWLINE() +
                          "Hai " + COLOR(QM_RED) + SKULLTULAS_DESTROYED() + COLOR(QM_WHITE) + " teschi!" +
                          INSTANT_TEXT_OFF() + MESSAGE_END(),
                      INSTANT_TEXT_ON() + "Du hast eine " + COLOR(QM_RED) + "Goldene Skulltula " + COLOR(QM_WHITE) +
                          "zerstört." + NEWLINE() + "Du erhältst dafür ein Skulltula-Symbol" + NEWLINE() +
                          "als Beweis! Du besitzt nun " + COLOR(QM_RED) + SKULLTULAS_DESTROYED() + COLOR(QM_WHITE) +
                          " Symbole!" + INSTANT_TEXT_OFF() + MESSAGE_END());
    }

    // Bombchu (10) Description
    CreateMessage(
        0xBC, 0, 2, 3,
        INSTANT_TEXT_ON() + COLOR(QM_RED) + "Bombchu (10): 99 Rupees" + NEWLINE() + COLOR(QM_WHITE) +
            "These look like toy mice, but they're" + NEWLINE() + "actually self-propelled time bombs!" +
            INSTANT_TEXT_OFF() + SHOP_MESSAGE_BOX() + MESSAGE_END(),
        INSTANT_TEXT_ON() + COLOR(QM_RED) + "Bombchus (10): 99 rubis" + NEWLINE() + COLOR(QM_WHITE) +
            "Profilée comme une souris mécanique, il" + NEWLINE() + "s'agit en fait d'une bombe à retardement" +
            NEWLINE() + "autopropulsée!" + INSTANT_TEXT_OFF() + SHOP_MESSAGE_BOX() + MESSAGE_END(),
        INSTANT_TEXT_ON() + COLOR(QM_RED) + "Bombchus (10): 99 rupias" + NEWLINE() + COLOR(QM_WHITE) +
            "Aunque parezcan ratoncitos de juguete," + NEWLINE() + "¡son bombas de relojería autopropulsadas!" +
            INSTANT_TEXT_OFF() + SHOP_MESSAGE_BOX() + MESSAGE_END(),
        INSTANT_TEXT_ON() + COLOR(QM_RED) + "10 radiomine - 99 rupie" + NEWLINE() + COLOR(QM_WHITE) +
            "Assomigliano a un topolino," + NEWLINE() + "ma in realtà sono bombe a" + NEWLINE() +
            "orologeria autoguidate!" + INSTANT_TEXT_OFF() + SHOP_MESSAGE_BOX() + MESSAGE_END(),
        INSTANT_TEXT_ON() + COLOR(QM_RED) + "Krabbelminen (10 Stück): 99 Rubine" + NEWLINE() + COLOR(QM_WHITE) +
            "Sieht aus wie eine Spielzeugmaus," + NEWLINE() + "ist aber eine selbstgesteuerte Zeitbombe!" +
            INSTANT_TEXT_OFF() + SHOP_MESSAGE_BOX() + MESSAGE_END());
    // Boss Keys
    for (u32 bossKey = 0; bossKey <= (DUNGEON_SHADOW_TEMPLE - DUNGEON_FOREST_TEMPLE); bossKey++) {
        u32 dungeon = DUNGEON_FOREST_TEMPLE + bossKey;
        CreateMessage(
            0x9D4 + bossKey, 0, 2, 3,
            UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_BOSS) + INSTANT_TEXT_ON() + "You got the " +
                COLOR(DungeonColors[dungeon]) + EnglishDungeonNames[dungeon] + NEWLINE() + "Boss Key" +
                COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
            UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_BOSS) + INSTANT_TEXT_ON() + "Vous trouvez la " +
                COLOR(DungeonColors[dungeon]) + "clé d'or " + NEWLINE() + FrenchDungeonArticles[dungeon] + " " +
                FrenchDungeonNames[dungeon] + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
            UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_BOSS) + INSTANT_TEXT_ON() + "¡Tienes la " +
                COLOR(DungeonColors[dungeon]) + "gran llave " + SpanishDungeonArticles[dungeon] + NEWLINE() +
                SpanishDungeonNames[dungeon] + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
            UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_BOSS) + INSTANT_TEXT_ON() + "Hai ottenuto la " +
                COLOR(DungeonColors[dungeon]) + "grande chiave " + ItalianDungeonArticles[dungeon] + NEWLINE() +
                ItalianDungeonNames[dungeon] + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
            UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_BOSS) + INSTANT_TEXT_ON() + "Du hast den " +
                COLOR(DungeonColors[dungeon]) + "Master-Schlüssel " + COLOR(QM_WHITE) + GermanDungeonArticles[dungeon] +
                NEWLINE() + COLOR(DungeonColors[dungeon]) + GermanDungeonNames[dungeon] +
                GermanDungeonGenitiv[dungeon] + COLOR(QM_WHITE) + "erhalten!" + INSTANT_TEXT_OFF() + MESSAGE_END());
    }
    CreateMessage(
        0x9D9, 0, 2, 3,
        UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_BOSS) + INSTANT_TEXT_ON() + "You got the " +
            COLOR(DungeonColors[DUNGEON_INSIDE_GANONS_CASTLE]) + EnglishDungeonNames[DUNGEON_INSIDE_GANONS_CASTLE] +
            NEWLINE() + "Boss Key" + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
        UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_BOSS) + INSTANT_TEXT_ON() + "Vous trouvez la " +
            COLOR(DungeonColors[DUNGEON_INSIDE_GANONS_CASTLE]) + "clé d'or " + NEWLINE() +
            FrenchDungeonArticles[DUNGEON_INSIDE_GANONS_CASTLE] + " " +
            FrenchDungeonNames[DUNGEON_INSIDE_GANONS_CASTLE] + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() +
            MESSAGE_END(),
        UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_BOSS) + INSTANT_TEXT_ON() + "¡Tienes la " +
            COLOR(DungeonColors[DUNGEON_INSIDE_GANONS_CASTLE]) + "gran llave " +
            SpanishDungeonArticles[DUNGEON_INSIDE_GANONS_CASTLE] + NEWLINE() +
            SpanishDungeonNames[DUNGEON_INSIDE_GANONS_CASTLE] + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() +
            MESSAGE_END(),
        UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_BOSS) + INSTANT_TEXT_ON() + "Hai ottenuto la " +
            COLOR(DungeonColors[DUNGEON_INSIDE_GANONS_CASTLE]) + "grande chiave " +
            ItalianDungeonArticles[DUNGEON_INSIDE_GANONS_CASTLE] + NEWLINE() +
            ItalianDungeonNames[DUNGEON_INSIDE_GANONS_CASTLE] + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() +
            MESSAGE_END(),
        UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_BOSS) + INSTANT_TEXT_ON() + "Du hast den " +
            COLOR(DungeonColors[DUNGEON_INSIDE_GANONS_CASTLE]) + "Master-Schlüssel " + COLOR(QM_WHITE) +
            GermanDungeonArticles[DUNGEON_INSIDE_GANONS_CASTLE] + NEWLINE() +
            COLOR(DungeonColors[DUNGEON_INSIDE_GANONS_CASTLE]) + GermanDungeonNames[DUNGEON_INSIDE_GANONS_CASTLE] +
            GermanDungeonGenitiv[DUNGEON_INSIDE_GANONS_CASTLE] + COLOR(QM_WHITE) + "erhalten!" + INSTANT_TEXT_OFF() +
            MESSAGE_END());
    // Compasses
    //   Moved to Hints::CreateCompassAndGearMenuHints

    // Maps
    for (u32 dungeon = DUNGEON_DEKU_TREE; dungeon <= DUNGEON_ICE_CAVERN; dungeon++) {
        CreateMessage(0x9E4 + dungeon, 0, 2, 3,
                      UNSKIPPABLE() + ITEM_OBTAINED(ITEM_DUNGEON_MAP) + INSTANT_TEXT_ON() + "You got the " +
                          COLOR(DungeonColors[dungeon]) + EnglishDungeonNames[dungeon] + NEWLINE() + "Map" +
                          COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
                      UNSKIPPABLE() + ITEM_OBTAINED(ITEM_DUNGEON_MAP) + INSTANT_TEXT_ON() + "Vous trouvez la " +
                          COLOR(DungeonColors[dungeon]) + "carte " + NEWLINE() + FrenchDungeonArticles[dungeon] +
                          FrenchDungeonNames[dungeon] + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
                      UNSKIPPABLE() + ITEM_OBTAINED(ITEM_DUNGEON_MAP) + INSTANT_TEXT_ON() + "¡Has obtenido el " +
                          COLOR(DungeonColors[dungeon]) + "mapa " + SpanishDungeonArticles[dungeon] + NEWLINE() +
                          SpanishDungeonNames[dungeon] + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
                      UNSKIPPABLE() + ITEM_OBTAINED(ITEM_DUNGEON_MAP) + INSTANT_TEXT_ON() + "Hai ottenuto la " +
                          COLOR(DungeonColors[dungeon]) + "mappa " + ItalianDungeonArticles[dungeon] + NEWLINE() +
                          ItalianDungeonNames[dungeon] + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
                      UNSKIPPABLE() + ITEM_OBTAINED(ITEM_DUNGEON_MAP) + INSTANT_TEXT_ON() + "Du hast die " +
                          COLOR(DungeonColors[dungeon]) + "Labyrinth-Karte " + COLOR(QM_WHITE) +
                          GermanDungeonArticles[dungeon] + NEWLINE() + COLOR(DungeonColors[dungeon]) +
                          GermanDungeonNames[dungeon] + GermanDungeonGenitiv[dungeon] + COLOR(QM_WHITE) + "erhalten!" +
                          INSTANT_TEXT_OFF() + MESSAGE_END());
    }
    // Small Keys
    for (u32 smallKey = 0; smallKey <= (DUNGEON_BOTTOM_OF_THE_WELL - DUNGEON_FOREST_TEMPLE); smallKey++) {
        u32 dungeon = DUNGEON_FOREST_TEMPLE + smallKey;
        CreateMessage(
            0x9EE + smallKey, 0, 2, 3,
            UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_SMALL) + INSTANT_TEXT_ON() + "You got a " +
                COLOR(DungeonColors[dungeon]) + EnglishDungeonNames[dungeon] + NEWLINE() + "Small Key" +
                COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
            UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_SMALL) + INSTANT_TEXT_ON() + "Vous trouvez une " +
                COLOR(DungeonColors[dungeon]) + "petite clé" + NEWLINE() + FrenchDungeonArticles[dungeon] +
                FrenchDungeonNames[dungeon] + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
            UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_SMALL) + INSTANT_TEXT_ON() + "¡Has obtenido una " +
                COLOR(DungeonColors[dungeon]) + "llave pequeña " + SpanishDungeonArticles[dungeon] + NEWLINE() +
                SpanishDungeonNames[dungeon] + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
            UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_SMALL) + INSTANT_TEXT_ON() + "Hai ottenuto una " +
                COLOR(DungeonColors[dungeon]) + "piccola chiave " + ItalianDungeonArticles[dungeon] + NEWLINE() +
                ItalianDungeonNames[dungeon] + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
            UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_SMALL) + INSTANT_TEXT_ON() + "Du hast einen " +
                COLOR(DungeonColors[dungeon]) + "kleinen Schlüssel " + COLOR(QM_WHITE) +
                GermanDungeonArticles[dungeon] + NEWLINE() + COLOR(DungeonColors[dungeon]) +
                GermanDungeonNames[dungeon] + GermanDungeonGenitiv[dungeon] + COLOR(QM_WHITE) + "erhalten!" +
                INSTANT_TEXT_OFF() + MESSAGE_END());
    }
    for (u32 smallKey = 0; smallKey <= (DUNGEON_INSIDE_GANONS_CASTLE - DUNGEON_GERUDO_TRAINING_GROUNDS); smallKey++) {
        u32 dungeon = DUNGEON_GERUDO_TRAINING_GROUNDS + smallKey;
        CreateMessage(
            0x9F4 + smallKey, 0, 2, 3,
            UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_SMALL) + INSTANT_TEXT_ON() + "You got a " +
                COLOR(DungeonColors[dungeon]) + EnglishDungeonNames[dungeon] + NEWLINE() + "Small Key" +
                COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
            UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_SMALL) + INSTANT_TEXT_ON() + "Vous trouvez une " +
                COLOR(DungeonColors[dungeon]) + "petite clé" + NEWLINE() + FrenchDungeonArticles[dungeon] +
                FrenchDungeonNames[dungeon] + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
            UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_SMALL) + INSTANT_TEXT_ON() + "¡Has obtenido una " +
                COLOR(DungeonColors[dungeon]) + "llave pequeña " + SpanishDungeonArticles[dungeon] + NEWLINE() +
                SpanishDungeonNames[dungeon] + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
            UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_SMALL) + INSTANT_TEXT_ON() + "Hai ottenuto una " +
                COLOR(DungeonColors[dungeon]) + "piccola chiave " + ItalianDungeonArticles[dungeon] + NEWLINE() +
                ItalianDungeonNames[dungeon] + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
            UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_SMALL) + INSTANT_TEXT_ON() + "Du hast einen " +
                COLOR(DungeonColors[dungeon]) + "kleinen Schlüssel " + COLOR(QM_WHITE) +
                GermanDungeonArticles[dungeon] + NEWLINE() + COLOR(DungeonColors[dungeon]) +
                GermanDungeonNames[dungeon] + GermanDungeonGenitiv[dungeon] + COLOR(QM_WHITE) + "erhalten!" +
                INSTANT_TEXT_OFF() + MESSAGE_END());
    }
    // Key Rings
    for (u32 smallKey = 0; smallKey <= (DUNGEON_BOTTOM_OF_THE_WELL - DUNGEON_FOREST_TEMPLE); smallKey++) {
        u32 dungeon = DUNGEON_FOREST_TEMPLE + smallKey;
        CreateMessage(
            0x9300 + smallKey, 0, 2, 3,
            UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_SMALL) + INSTANT_TEXT_ON() + "You got a " +
                COLOR(DungeonColors[dungeon]) + EnglishDungeonNames[dungeon] + NEWLINE() + "Key Ring" +
                COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
            UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_SMALL) + INSTANT_TEXT_ON() + "Vous trouvez un " +
                COLOR(DungeonColors[dungeon]) + "trousseau" + NEWLINE() + FrenchDungeonArticles[dungeon] +
                FrenchDungeonNames[dungeon] + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
            UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_SMALL) + INSTANT_TEXT_ON() + "¡Has obtenido un " +
                COLOR(DungeonColors[dungeon]) + "llavero " + SpanishDungeonArticles[dungeon] + NEWLINE() +
                SpanishDungeonNames[dungeon] + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
            UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_SMALL) + INSTANT_TEXT_ON() + "Hai ottenuto il " +
                COLOR(DungeonColors[dungeon]) + "mazzo di chiavi " + ItalianDungeonArticles[dungeon] + NEWLINE() +
                ItalianDungeonNames[dungeon] + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
            UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_SMALL) + INSTANT_TEXT_ON() + "Du hast den " +
                COLOR(DungeonColors[dungeon]) + "Schlüsselbund " + COLOR(QM_WHITE) + GermanDungeonArticles[dungeon] +
                NEWLINE() + COLOR(DungeonColors[dungeon]) + GermanDungeonNames[dungeon] +
                GermanDungeonGenitiv[dungeon] + COLOR(QM_WHITE) + "erhalten!" + INSTANT_TEXT_OFF() + MESSAGE_END());
    }
    for (u32 smallKey = 0; smallKey <= (DUNGEON_INSIDE_GANONS_CASTLE - DUNGEON_GERUDO_TRAINING_GROUNDS); smallKey++) {
        u32 dungeon = DUNGEON_GERUDO_TRAINING_GROUNDS + smallKey;
        CreateMessage(
            0x9306 + smallKey, 0, 2, 3,
            UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_SMALL) + INSTANT_TEXT_ON() + "You got a " +
                COLOR(DungeonColors[dungeon]) + EnglishDungeonNames[dungeon] + NEWLINE() + "Key Ring" +
                COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
            UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_SMALL) + INSTANT_TEXT_ON() + "Vous trouvez un " +
                COLOR(DungeonColors[dungeon]) + "trousseau" + NEWLINE() + FrenchDungeonArticles[dungeon] +
                FrenchDungeonNames[dungeon] + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
            UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_SMALL) + INSTANT_TEXT_ON() + "¡Has obtenido un " +
                COLOR(DungeonColors[dungeon]) + "llavero " + SpanishDungeonArticles[dungeon] + NEWLINE() +
                SpanishDungeonNames[dungeon] + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
            UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_SMALL) + INSTANT_TEXT_ON() + "Hai ottenuto il " +
                COLOR(DungeonColors[dungeon]) + "mazzo di chiavi " + ItalianDungeonArticles[dungeon] + NEWLINE() +
                ItalianDungeonNames[dungeon] + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
            UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_SMALL) + INSTANT_TEXT_ON() + "Du hast den " +
                COLOR(DungeonColors[dungeon]) + "Schlüsselbund " + COLOR(QM_WHITE) + GermanDungeonArticles[dungeon] +
                NEWLINE() + COLOR(DungeonColors[dungeon]) + GermanDungeonNames[dungeon] +
                GermanDungeonGenitiv[dungeon] + COLOR(QM_WHITE) + "erhalten!" + INSTANT_TEXT_OFF() + MESSAGE_END());
    }
    // Master Sword
    CreateMessage(0x9309, 0, 2, 3,
                  UNSKIPPABLE() + ITEM_OBTAINED(ITEM_SWORD_MASTER) + INSTANT_TEXT_ON() + "You got the " +
                      COLOR(QM_RED) + "Master Sword" + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + NEWLINE() +
                      "This sacred blade is the only weapon" + NEWLINE() + "capable of defeating the " +
                      COLOR(QM_GREEN) + "Evil King" + COLOR(QM_WHITE) + "!" + MESSAGE_END(),
                  UNSKIPPABLE() + ITEM_OBTAINED(ITEM_SWORD_MASTER) + INSTANT_TEXT_ON() + "Vous obtenez l'" +
                      COLOR(QM_RED) + "épée de légende" + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + NEWLINE() +
                      "Cette lame sacrée est l'unique" + NEWLINE() + "arme capable de vaincre le" + NEWLINE() +
                      COLOR(QM_GREEN) + "seigneur du Malin" + COLOR(QM_WHITE) + "!" + MESSAGE_END(),
                  UNSKIPPABLE() + ITEM_OBTAINED(ITEM_SWORD_MASTER) + INSTANT_TEXT_ON() + "¡Has obtenido la " +
                      COLOR(QM_RED) + "Espada Maestra" + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + NEWLINE() +
                      "¡Esta espada sagrada es la única arma" + NEWLINE() + "capaz de derrotar al " + COLOR(QM_GREEN) +
                      "Rey Malvado" + COLOR(QM_WHITE) + "!" + MESSAGE_END(),
                  UNSKIPPABLE() + ITEM_OBTAINED(ITEM_SWORD_MASTER) + INSTANT_TEXT_ON() + "Hai ottenuto la " +
                      COLOR(QM_RED) + "spada suprema" + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + NEWLINE() +
                      "Questa spada sacra è l'unica arma" + NEWLINE() + "in grado di sconfiggere il " +
                      COLOR(QM_GREEN) + "re del male" + COLOR(QM_WHITE) + "!" + MESSAGE_END(),
                  UNSKIPPABLE() + ITEM_OBTAINED(ITEM_SWORD_MASTER) + INSTANT_TEXT_ON() + "Das " + COLOR(QM_RED) +
                      "Master-Schwert" + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + NEWLINE() +
                      "Nur diese heilige Klinge ist dazu" + NEWLINE() + "in der Lage, den " + COLOR(QM_GREEN) +
                      "Großmeister des" + NEWLINE() + "Bösen " + COLOR(QM_WHITE) + "zu bezwingen!" + MESSAGE_END());
    // Tycoon's Wallet
    CreateMessage(0x09F7, 0, 2, 3,
                  UNSKIPPABLE() + ITEM_OBTAINED(ITEM_WALLET_GIANT) + INSTANT_TEXT_ON() + "You got a " + COLOR(QM_RED) +
                      "Tycoon's Wallet" + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + NEWLINE() +
                      "It's gigantic! Now you can carry" + NEWLINE() + "up to " + COLOR(QM_YELLOW) + "999 " +
                      COLOR(QM_WHITE) + COLOR(QM_YELLOW) + "Rupees" + COLOR(QM_WHITE) + "!" + MESSAGE_END(),
                  UNSKIPPABLE() + ITEM_OBTAINED(ITEM_WALLET_GIANT) + INSTANT_TEXT_ON() + "Vous obtenez la " +
                      COLOR(QM_RED) + "bourse de star" + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + NEWLINE() +
                      "Elle peut contenir jusqu'à " + COLOR(QM_YELLOW) + "999 " + COLOR(QM_WHITE) + COLOR(QM_YELLOW) +
                      "rubis" + COLOR(QM_WHITE) + "!" + NEWLINE() + "C'est gigantesque!" + MESSAGE_END(),
                  UNSKIPPABLE() + ITEM_OBTAINED(ITEM_WALLET_GIANT) + INSTANT_TEXT_ON() + "¡Has conseguido una " +
                      COLOR(QM_RED) + "bolsa para ricachones" + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + NEWLINE() +
                      "¡Qué descomunal! Ya puedes llevar" + NEWLINE() + "hasta " + COLOR(QM_YELLOW) + "999 " +
                      COLOR(QM_WHITE) + COLOR(QM_YELLOW) + "rupias" + COLOR(QM_WHITE) + "!" + MESSAGE_END(),
                  UNSKIPPABLE() + ITEM_OBTAINED(ITEM_WALLET_GIANT) + INSTANT_TEXT_ON() + "Hai ottenuto il " +
                      COLOR(QM_RED) + "portarupie di lusso" + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + NEWLINE() +
                      "È colossale! Ora potrai portare" + NEWLINE() + "fino a " + COLOR(QM_YELLOW) + "999 " +
                      COLOR(QM_WHITE) + COLOR(QM_YELLOW) + "rupie" + COLOR(QM_WHITE) + "!" + MESSAGE_END(),
                  UNSKIPPABLE() + ITEM_OBTAINED(ITEM_WALLET_GIANT) + INSTANT_TEXT_ON() + "Die " + COLOR(QM_RED) +
                      "Tycoon-Börse" + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + NEWLINE() +
                      "Sie ist gigantisch! Jetzt kannst" + NEWLINE() + "du bis zu " + COLOR(QM_YELLOW) + "999 " +
                      COLOR(QM_WHITE) + COLOR(QM_YELLOW) + "Rubine " + COLOR(QM_WHITE) + "tragen!" + MESSAGE_END());
    // Saria's Song Default Hint
    CreateMessage(
        0x0A00, 0, 2, 3,
        UNSKIPPABLE() + "Have you tried talking to the gossip" + NEWLINE() + "stones around Hyrule? They might have" +
            NEWLINE() + "some good advice... Hee hee!" + WAIT_FOR_INPUT() +
            "If you learn something from the gossip stones," + NEWLINE() + "I will remember it!" + EVENT_TRIGGER() +
            MESSAGE_END(),
        UNSKIPPABLE() + "As-tu parlé aux pierres à potins" + NEWLINE() + "dans Hyrule? Elles sont de bons conseils..." +
            NEWLINE() + "Hi hi!" + WAIT_FOR_INPUT() + "Si elles te révèlent quelque chose," + NEWLINE() +
            "je m'en souviendrai!" + EVENT_TRIGGER() + MESSAGE_END(),
        UNSKIPPABLE() + "¿Has probado a consultarle a las" + NEWLINE() +
            "piedras chismosas esparcidas por Hyrule? Puede" + NEWLINE() +
            "que sean de ayuda a tu empresa... ¡Ji, ji!" + WAIT_FOR_INPUT() +
            "¡Puedo recordarte todo lo que aprendas de ellas," + NEWLINE() + "si así lo deseas!" + EVENT_TRIGGER() +
            MESSAGE_END(),
        UNSKIPPABLE() + "Hai provato a parlare alle pietre" + NEWLINE() + "del pettegolezzo in giro per Hyrule?" +
            NEWLINE() + "Potrebbero darti qualche buon consiglio..." + WAIT_FOR_INPUT() +
            "Mi ricorderò tutto ciò che ti diranno, quindi" + NEWLINE() + "chiamami se vuoi ascoltarle di nuovo!" +
            EVENT_TRIGGER() + MESSAGE_END(),
        UNSKIPPABLE() + "Hast du schon mit den Mythensteinen," + NEWLINE() + "die in ganz Hyrule verteilt sind," +
            NEWLINE() + "gesprochen? Sie könnten dir nützliche" + NEWLINE() + "Hinweise geben... Hi hi!" +
            WAIT_FOR_INPUT() + "Wenn du etwas Hilfreiches von ihnen" + NEWLINE() +
            "erfährst und es vergessen solltest," + NEWLINE() + "frag mich nur. Ich kann mir so etwas" + NEWLINE() +
            "ziemlich gut merken!" + EVENT_TRIGGER() + MESSAGE_END());
    // Poe Collector (when enough has been sold)
    CreateMessage(
        0x70F8, 0, 0, 0,
        UNSKIPPABLE() + "Wait a minute! WOW!" + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() +
            "You have earned enough points!" + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() +
            "Young man, you are a genuine " + COLOR(QM_RED) + "ghost hunter" + COLOR(QM_WHITE) + "!" +
            WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() + "Is that what you expected me to say?" + NEWLINE() +
            "Heh heh heh!" + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() +
            "Because of you, I have extra inventory of" + NEWLINE() + COLOR(QM_RED) + "Big Poes" + COLOR(QM_WHITE) +
            ", so this will be the last time I can" + NEWLINE() + "buy one of these ghosts." + WAIT_FOR_INPUT() +
            NEWLINE() + UNSKIPPABLE() + "You're thinking about what I promised would" + NEWLINE() +
            "happen when you earned enough points." + NEWLINE() + "Heh heh." + WAIT_FOR_INPUT() + NEWLINE() +
            UNSKIPPABLE() + "Don't worry. I didn't forget. Just take this." + MESSAGE_END(),
        UNSKIPPABLE() + "Ooooh! WHOA!" + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() +
            "Tu as obtenu suffisamment de points!" + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() +
            "Tu es un véritable " + COLOR(QM_RED) + "chasseur de fantômes" + COLOR(QM_WHITE) + "!" + WAIT_FOR_INPUT() +
            NEWLINE() + UNSKIPPABLE() + "Il est content, hein?" + NEWLINE() + "Il est content le monsieur?" +
            NEWLINE() + "Hé hé hé!" + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() + "Grâce à toi, mon stock d'" +
            COLOR(QM_RED) + "Âmes" + COLOR(QM_WHITE) + " est plein!" + NEWLINE() +
            "C'est donc la dernière fois que nous" + NEWLINE() + "faisons affaire." + WAIT_FOR_INPUT() + NEWLINE() +
            UNSKIPPABLE() + "Je sais, je sais..." + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() +
            "Nous avions passé un pacte..." + NEWLINE() + "Tu as eu tes points et je t'en félicite..." + NEWLINE() +
            "Hé hé hé!" + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() + "Alors prends donc ceci, mon bon ami!" +
            MESSAGE_END(),
        UNSKIPPABLE() + "¡Un momento! ¡OYE!" + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() +
            "¡Has conseguido los puntos suficientes!" + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() +
            "¡Jovencito, eres un auténtico " + COLOR(QM_RED) + "cazador de" + NEWLINE() + "fantasmas" +
            COLOR(QM_WHITE) + "!" + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() +
            "¿Era eso lo que esperabas que dijera?" + NEWLINE() + "¡Je, je je!" + WAIT_FOR_INPUT() + NEWLINE() +
            UNSKIPPABLE() + "Gracias a ti, ya tengo la cantidad necesaria" + NEWLINE() + "de " + COLOR(QM_RED) +
            "grandes poes" + COLOR(QM_WHITE) + ", así que esta será la" + NEWLINE() +
            "última vez que te compre unos de ese tipo." + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() +
            "¿Recuerdas lo que te dije que ocurriría" + NEWLINE() + "cuando tuvieses suficientes puntos?" + NEWLINE() +
            "Je, je, je." + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() + "Tranquilo, que no se me ha olvidado." +
            NEWLINE() + "Toma esto." + MESSAGE_END(),
        UNSKIPPABLE() + "Aspetta un attimo, bello mio!" + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() +
            "Hai ottenuto abbastanza punti!" + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() +
            "Bello mio, sei un vero " + COLOR(QM_RED) + "acchiappaspettri" + COLOR(QM_WHITE) + "!" + WAIT_FOR_INPUT() +
            NEWLINE() + UNSKIPPABLE() + "Grazie a te, ora ho una bella scorta" + NEWLINE() +
            "di Grandi Poo e non devo comprare" + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() +
            "altri fantasmi di questo tipo." + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() +
            "So a cosa stai pensando, bello mio..." + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() +
            "Ti stai chiedendo dov'è la tua" + NEWLINE() + "sorpresa ora che hai raggiunto" + NEWLINE() +
            "i punti necessari... Non me sono" + NEWLINE() + "dimenticato. Tieni, prendi!" + MESSAGE_END(),
        UNSKIPPABLE() + "Oh! WOW!" + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() + "Du hast jetzt " + COLOR(QM_RED) +
            "ausreichend Punkte" + COLOR(QM_WHITE) + "!" + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() +
            "Du bist ja der geborene " + COLOR(QM_RED) + "Geisterjäger" + COLOR(QM_WHITE) + "!" + WAIT_FOR_INPUT() +
            NEWLINE() + UNSKIPPABLE() + "Du erwartest noch etwas von mir?" + NEWLINE() + "Was denn? Hehehe..." +
            WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() + "Dank dir ist mein Bestand an " + COLOR(QM_RED) + "Nacht-" +
            NEWLINE() + "schwärmern " + COLOR(QM_WHITE) + "enorm gestiegen... Dies" + NEWLINE() +
            "ist der letzte, den ich dir abnehme." + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() +
            "Ach, du wartest auf das, was ich dir für ein" + NEWLINE() + "volles Punkte-Konto versprochen habe?" +
            NEWLINE() + "Hehehe..." + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() +
            "Na, da will ich mal nicht so sein..." + NEWLINE() + "Nimm das hier!" + MESSAGE_END());
    // Ice Trap
    CreateMessage(0x9002, 0, 2, 3,
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + COLOR(QM_RED) + "FOOL!" + COLOR(QM_WHITE) +
                      INSTANT_TEXT_OFF() + MESSAGE_END(),
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + COLOR(QM_RED) + "IDIOT!" + COLOR(QM_WHITE) +
                      INSTANT_TEXT_OFF() + MESSAGE_END(),
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + COLOR(QM_RED) + "¡TONTO!" + COLOR(QM_WHITE) +
                      INSTANT_TEXT_OFF() + MESSAGE_END(),
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + COLOR(QM_RED) + "STOLTO!" + COLOR(QM_WHITE) +
                      INSTANT_TEXT_OFF() + MESSAGE_END(),
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + COLOR(QM_RED) + "NARR!" + COLOR(QM_WHITE) +
                      INSTANT_TEXT_OFF() + MESSAGE_END());
    // Curse Traps
    u32 curseIdxOffset = 0;
    CreateMessage(CURSETRAP_TEXT_BASE_INDEX + curseIdxOffset++, 0, 2, 3,
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "You've been " + COLOR(QM_RED) + "cursed" +
                      COLOR(QM_WHITE) + "!" + NEWLINE() + CENTER_TEXT() + "You can't use your shield!" +
                      INSTANT_TEXT_OFF() + CLOSE_AFTER(120) + MESSAGE_END(),
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "Un " + COLOR(QM_RED) + "sort" + COLOR(QM_WHITE) +
                      " vous a été jeté!" + NEWLINE() + CENTER_TEXT() + "Vous ne pouvez pas utiliser votre bouclier" +
                      INSTANT_TEXT_OFF() + CLOSE_AFTER(120) + MESSAGE_END(),
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "¡Has sido " + COLOR(QM_RED) + "hechizado" +
                      COLOR(QM_WHITE) + "!" + NEWLINE() + CENTER_TEXT() + "¡No puedes usar tu escudo!" +
                      INSTANT_TEXT_OFF() + CLOSE_AFTER(120) + MESSAGE_END(),
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "Sei caduto vittima di una " + COLOR(QM_RED) +
                      "maledizione" + COLOR(QM_WHITE) + "!" + NEWLINE() + CENTER_TEXT() + "Non puoi usare lo scudo!" +
                      INSTANT_TEXT_OFF() + CLOSE_AFTER(120) + MESSAGE_END(),
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "Du wurdest " + COLOR(QM_RED) + "verflucht" +
                      COLOR(QM_WHITE) + "!" + NEWLINE() + CENTER_TEXT() +
                      "Du kannst deinen Schild nicht mehr benutzen!" + INSTANT_TEXT_OFF() + CLOSE_AFTER(120) +
                      MESSAGE_END());
    CreateMessage(
        CURSETRAP_TEXT_BASE_INDEX + curseIdxOffset++, 0, 2, 3,
        UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "You've been " + COLOR(QM_RED) + "cursed" +
            COLOR(QM_WHITE) + "!" + NEWLINE() + CENTER_TEXT() + "Your sword " + COLOR(QM_RED) + "can't hit" +
            COLOR(QM_WHITE) + " anything!" + INSTANT_TEXT_OFF() + CLOSE_AFTER(120) + MESSAGE_END(),
        UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "Un " + COLOR(QM_RED) + "sort" + COLOR(QM_WHITE) +
            " vous a été jeté!" + NEWLINE() + CENTER_TEXT() + "Votre épée " + COLOR(QM_RED) + "ne peut rien toucher" +
            COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + CLOSE_AFTER(120) + MESSAGE_END(),
        UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "¡Has sido " + COLOR(QM_RED) + "hechizado" +
            COLOR(QM_WHITE) + "!" + NEWLINE() + CENTER_TEXT() + "¡Tu espada " + COLOR(QM_RED) + "no puede golpear" +
            COLOR(QM_WHITE) + " nada!" + INSTANT_TEXT_OFF() + CLOSE_AFTER(120) + MESSAGE_END(),
        UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "Sei caduto vittima di una " + COLOR(QM_RED) +
            "maledizione" + COLOR(QM_WHITE) + "!" + NEWLINE() + CENTER_TEXT() + "La tua spada " + COLOR(QM_RED) +
            "non può colpire" + COLOR(QM_WHITE) + " nulla!" + INSTANT_TEXT_OFF() + CLOSE_AFTER(120) + MESSAGE_END(),
        UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "Du wurdest " + COLOR(QM_RED) + "verflucht" +
            COLOR(QM_WHITE) + "!" + NEWLINE() + CENTER_TEXT() + "Dein Schwert " + COLOR(QM_RED) + "verfehlt" +
            COLOR(QM_WHITE) + " absolut alles!" + INSTANT_TEXT_OFF() + CLOSE_AFTER(120) + MESSAGE_END());
    CreateMessage(CURSETRAP_TEXT_BASE_INDEX + curseIdxOffset++, 0, 2, 3,
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "You've been " + COLOR(QM_RED) + "cursed" +
                      COLOR(QM_WHITE) + "!" + NEWLINE() + CENTER_TEXT() + "You are " + COLOR(QM_RED) + "confused" +
                      COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + CLOSE_AFTER(120) + MESSAGE_END(),
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "Un " + COLOR(QM_RED) + "sort" + COLOR(QM_WHITE) +
                      " vous a été jeté!" + NEWLINE() + CENTER_TEXT() + "Vous êtes " + COLOR(QM_RED) + "confus" +
                      COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + CLOSE_AFTER(120) + MESSAGE_END(),
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "¡Has sido " + COLOR(QM_RED) + "hechizado" +
                      COLOR(QM_WHITE) + "!" + NEWLINE() + CENTER_TEXT() + "¡Estás " + COLOR(QM_RED) + "confundido" +
                      COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + CLOSE_AFTER(120) + MESSAGE_END(),
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "Sei caduto vittima di una " + COLOR(QM_RED) +
                      "maledizione" + COLOR(QM_WHITE) + "!" + NEWLINE() + CENTER_TEXT() + "Sei " + COLOR(QM_RED) +
                      "confuso" + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + CLOSE_AFTER(120) + MESSAGE_END(),
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "Du wurdest " + COLOR(QM_RED) + "verflucht" +
                      COLOR(QM_WHITE) + "!" + NEWLINE() + CENTER_TEXT() + "Du bist " + COLOR(QM_RED) + "verwirrt" +
                      COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + CLOSE_AFTER(120) + MESSAGE_END());
    CreateMessage(CURSETRAP_TEXT_BASE_INDEX + curseIdxOffset++, 0, 2, 3,
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "You've been " + COLOR(QM_RED) + "cursed" +
                      COLOR(QM_WHITE) + "!" + NEWLINE() + CENTER_TEXT() + "Terrain is " + COLOR(QM_RED) + "invisible" +
                      COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + CLOSE_AFTER(120) + MESSAGE_END(),
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "Un " + COLOR(QM_RED) + "sort" + COLOR(QM_WHITE) +
                      " vous a été jeté!" + NEWLINE() + CENTER_TEXT() + "Le terrain est " + COLOR(QM_RED) +
                      "invisible" + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + CLOSE_AFTER(120) + MESSAGE_END(),
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "¡Has sido " + COLOR(QM_RED) + "hechizado" +
                      COLOR(QM_WHITE) + "!" + NEWLINE() + CENTER_TEXT() + "¡El terreno es " + COLOR(QM_RED) +
                      "invisible" + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + CLOSE_AFTER(120) + MESSAGE_END(),
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "Sei caduto vittima di una " + COLOR(QM_RED) +
                      "maledizione" + COLOR(QM_WHITE) + "!" + NEWLINE() + CENTER_TEXT() + "Il terreno è " +
                      COLOR(QM_RED) + "invisibile" + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + CLOSE_AFTER(120) +
                      MESSAGE_END(),
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "Du wurdest " + COLOR(QM_RED) + "verflucht" +
                      COLOR(QM_WHITE) + "!" + NEWLINE() + CENTER_TEXT() + "Die Umgebung ist " + COLOR(QM_RED) +
                      "unsichtbar" + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + CLOSE_AFTER(120) + MESSAGE_END());
    CreateMessage(CURSETRAP_TEXT_BASE_INDEX + curseIdxOffset++, 0, 2, 3,
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "You've been " + COLOR(QM_RED) + "cursed" +
                      COLOR(QM_WHITE) + "!" + NEWLINE() + CENTER_TEXT() + "You are feeling " + COLOR(QM_RED) +
                      "sluggish" + COLOR(QM_WHITE) + "..." + INSTANT_TEXT_OFF() + CLOSE_AFTER(120) + MESSAGE_END(),
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "Un " + COLOR(QM_RED) + "sort" + COLOR(QM_WHITE) +
                      " vous a été jeté!" + NEWLINE() + CENTER_TEXT() + "Vous vous sentez " + COLOR(QM_RED) +
                      "léthargique" + COLOR(QM_WHITE) + "..." + INSTANT_TEXT_OFF() + CLOSE_AFTER(120) + MESSAGE_END(),
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "¡Has sido " + COLOR(QM_RED) + "hechizado" +
                      COLOR(QM_WHITE) + "!" + NEWLINE() + CENTER_TEXT() + "Te sientes " + COLOR(QM_RED) + "lento" +
                      COLOR(QM_WHITE) + "..." + INSTANT_TEXT_OFF() + CLOSE_AFTER(120) + MESSAGE_END(),
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "Sei caduto vittima di una " + COLOR(QM_RED) +
                      "maledizione" + COLOR(QM_WHITE) + "!" + NEWLINE() + CENTER_TEXT() + "Ti senti un po' " +
                      COLOR(QM_RED) + "fiacco" + COLOR(QM_WHITE) + "..." + INSTANT_TEXT_OFF() + CLOSE_AFTER(120) +
                      MESSAGE_END(),
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "Du wurdest " + COLOR(QM_RED) + "verflucht" +
                      COLOR(QM_WHITE) + "!" + NEWLINE() + CENTER_TEXT() + "Du fühlst dich " + COLOR(QM_RED) + "träge" +
                      COLOR(QM_WHITE) + "..." + INSTANT_TEXT_OFF() + CLOSE_AFTER(120) + MESSAGE_END());
    CreateMessage(CURSETRAP_TEXT_BASE_INDEX + curseIdxOffset++, 0, 2, 3,
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "You've been " + COLOR(QM_RED) + "cursed" +
                      COLOR(QM_WHITE) + "!" + NEWLINE() + CENTER_TEXT() + "The world is " + COLOR(QM_RED) + "crooked" +
                      COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + CLOSE_AFTER(120) + MESSAGE_END(),
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "Un " + COLOR(QM_RED) + "sort" + COLOR(QM_WHITE) +
                      " vous a été jeté!" + NEWLINE() + CENTER_TEXT() + "Le monde est " + COLOR(QM_RED) + "penché" +
                      COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + CLOSE_AFTER(120) + MESSAGE_END(),
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "¡Has sido " + COLOR(QM_RED) + "hechizado" +
                      COLOR(QM_WHITE) + "!" + NEWLINE() + CENTER_TEXT() + "¡El mundo está " + COLOR(QM_RED) +
                      "torcido" + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + CLOSE_AFTER(120) + MESSAGE_END(),
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "Sei caduto vittima di una " + COLOR(QM_RED) +
                      "maledizione" + COLOR(QM_WHITE) + "!" + NEWLINE() + CENTER_TEXT() + "Il mondo si è " +
                      COLOR(QM_RED) + "inclinato" + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + CLOSE_AFTER(120) +
                      MESSAGE_END(),
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "Du wurdest " + COLOR(QM_RED) + "verflucht" +
                      COLOR(QM_WHITE) + "!" + NEWLINE() + CENTER_TEXT() + "Die Welt wurde " + COLOR(QM_RED) +
                      "gedreht" + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + CLOSE_AFTER(120) + MESSAGE_END());
    CreateMessage(
        CURSETRAP_TEXT_BASE_INDEX + curseIdxOffset++, 0, 2, 3,
        UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "You've been " + COLOR(QM_RED) + "cursed" +
            COLOR(QM_WHITE) + "!" + NEWLINE() + CENTER_TEXT() + "The camera is " + COLOR(QM_RED) + "unstable" +
            COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + CLOSE_AFTER(120) + MESSAGE_END(),
        UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "Un " + COLOR(QM_RED) + "sort" + COLOR(QM_WHITE) +
            " vous a été jeté!" + NEWLINE() + CENTER_TEXT() + "La caméra est " + COLOR(QM_RED) + "instable" +
            COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + CLOSE_AFTER(120) + MESSAGE_END(),
        UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "¡Has sido " + COLOR(QM_RED) + "hechizado" +
            COLOR(QM_WHITE) + "!" + NEWLINE() + CENTER_TEXT() + "¡La cámara está " + COLOR(QM_RED) + "inestable" +
            COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + CLOSE_AFTER(120) + MESSAGE_END(),
        UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "Sei caduto vittima di una " + COLOR(QM_RED) +
            "maledizione" + COLOR(QM_WHITE) + "!" + NEWLINE() + CENTER_TEXT() + "La visuale è " + COLOR(QM_RED) +
            "impazzita" + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + CLOSE_AFTER(120) + MESSAGE_END(),
        UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "Du wurdest " + COLOR(QM_RED) + "verflucht" +
            COLOR(QM_WHITE) + "!" + NEWLINE() + CENTER_TEXT() + "Die Kameraperspektive " + COLOR(QM_RED) +
            "ändert sich stetig" + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() + CLOSE_AFTER(120) + MESSAGE_END());

    // Business Scrubs
    // The less significant byte represents the price of the item
    for (u32 price = 0; price <= 95; price += 5) {
        CreateMessage(
            0x9000 + price, 0, 0, 0,
            INSTANT_TEXT_ON() + "I'll sell you something good for " + COLOR(QM_RED) + std::to_string(price) +
                " Rupees" + COLOR(QM_WHITE) + "!" + NEWLINE() + NEWLINE() + TWO_WAY_CHOICE() + COLOR(QM_GREEN) + "OK" +
                NEWLINE() + "No way" + COLOR(QM_WHITE) + INSTANT_TEXT_OFF() + MESSAGE_END(),
            INSTANT_TEXT_ON() + "Je te vends un truc super pour " + COLOR(QM_RED) + std::to_string(price) + " Rubis" +
                COLOR(QM_WHITE) + "!" + NEWLINE() + NEWLINE() + TWO_WAY_CHOICE() + COLOR(QM_GREEN) + "D'accord" +
                NEWLINE() + "Hors de question" + COLOR(QM_WHITE) + INSTANT_TEXT_OFF() + MESSAGE_END(),
            INSTANT_TEXT_ON() + "¡Te puedo vender algo bueno por " + COLOR(QM_RED) + std::to_string(price) + " rupias" +
                COLOR(QM_WHITE) + "!" + NEWLINE() + NEWLINE() + TWO_WAY_CHOICE() + COLOR(QM_GREEN) + "Vale" +
                NEWLINE() + "Ni hablar" + COLOR(QM_WHITE) + INSTANT_TEXT_OFF() + MESSAGE_END(),
            INSTANT_TEXT_ON() + "Ti venderò una bella cosa per " + COLOR(QM_RED) + std::to_string(price) + " rupie" +
                COLOR(QM_WHITE) + "!" + NEWLINE() + NEWLINE() + TWO_WAY_CHOICE() + COLOR(QM_GREEN) + "Va bene" +
                NEWLINE() + "Non ci penso nemmeno" + COLOR(QM_WHITE) + INSTANT_TEXT_OFF() + MESSAGE_END(),
            INSTANT_TEXT_ON() + "Ich verkaufe dir etwas Tolles für " + COLOR(QM_RED) + std::to_string(price) +
                " Rubine" + COLOR(QM_WHITE) + "!" + NEWLINE() + NEWLINE() + TWO_WAY_CHOICE() + COLOR(QM_GREEN) +
                "Her damit!" + NEWLINE() + "Niemals!" + COLOR(QM_WHITE) + INSTANT_TEXT_OFF() + MESSAGE_END());
    }
    // Poe Collector
    // The last digit represent the number of poes needed to collect
    for (u32 poes = 1; poes <= 10; poes++) {
        CreateMessage(
            0x9080 + poes, 0, 0, 0,
            UNSKIPPABLE() + "Oh, you brought a Poe today!" + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() + "Hmmmm!" +
                WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() + "Very interesting! This is a " + COLOR(QM_RED) +
                "Big Poe" + COLOR(QM_WHITE) + "!" + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() + "I'll buy it for " +
                COLOR(QM_RED) + "50 Rupees" + COLOR(QM_WHITE) + "." + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() +
                "On top of that, I'll put " + COLOR(QM_RED) + "100 points " + COLOR(QM_WHITE) + "on" + NEWLINE() +
                "your card." + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() + "If you earn " + COLOR(QM_RED) +
                std::to_string(poes * 100) + " points" + COLOR(QM_WHITE) + ", you'll be a" + NEWLINE() +
                "happy man! Heh heh." + MESSAGE_END(),

            UNSKIPPABLE() + "Oh! Tu as apporté un fantôme!" + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() + "Hmmmm!" +
                WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() + "Magnifique!" + NEWLINE() + "C'est une " +
                COLOR(QM_RED) + "Âme" + COLOR(QM_WHITE) + "!" + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() +
                "Je t'en donne " + COLOR(QM_RED) + "50 Rubis" + COLOR(QM_WHITE) + "." + WAIT_FOR_INPUT() + NEWLINE() +
                UNSKIPPABLE() + "Et en plus, j'inscris " + COLOR(QM_RED) + "100 points " + COLOR(QM_WHITE) + NEWLINE() +
                "sur ta carte." + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() + "Obtiens " + COLOR(QM_RED) +
                std::to_string(poes * 100) + " points" + COLOR(QM_WHITE) + " et tu ne" + NEWLINE() +
                "seras pas déçu..." + NEWLINE() + "Hé hé hé." + MESSAGE_END(),

            UNSKIPPABLE() + "¡Vaya! ¡Traes un poe!" + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() + "¡Mmm! ¿A ver?" +
                WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() + "¡Qué interesante! ¡Es un " + COLOR(QM_RED) +
                "gran poe" + COLOR(QM_WHITE) + "!" + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() + "Te daré " +
                COLOR(QM_RED) + "50 rupias " + COLOR(QM_WHITE) + "por él." + WAIT_FOR_INPUT() + NEWLINE() +
                UNSKIPPABLE() + "Y además agregaré " + COLOR(QM_RED) + "100 puntos " + COLOR(QM_WHITE) + "a tu" +
                NEWLINE() + "tarjeta." + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() + "¡Si llegas a " +
                COLOR(QM_RED) + std::to_string(poes * 100) + " puntos" + COLOR(QM_WHITE) + ", serás muy feliz!" +
                NEWLINE() + "Je, je, je..." + MESSAGE_END(),

            UNSKIPPABLE() + "Eccoti bello mio! Hai un Poo per me?" + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() +
                "Sì???" + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() + "Fantasmagorico! Questo è un " +
                COLOR(QM_RED) + "Grande Poo" + COLOR(QM_WHITE) + "!" + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() +
                "Ti do " + COLOR(QM_RED) + "50 Rupie" + COLOR(QM_WHITE) + "." + WAIT_FOR_INPUT() + NEWLINE() +
                UNSKIPPABLE() + "E aggiungo anche " + COLOR(QM_RED) + "100 punti " + COLOR(QM_WHITE) + "sulla tua" +
                NEWLINE() + "tessera! Sì, sono molto generoso!" + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() +
                "Se arrivi a " + COLOR(QM_RED) + std::to_string(poes * 100) + " punti" + COLOR(QM_WHITE) +
                ", ti aspetta" + NEWLINE() + "una sorpresa stupenda!" + MESSAGE_END(),

            UNSKIPPABLE() + "Oh, du bringst mir etwas!" + WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() + "Nun..." +
                WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() + "Erstaunlich!" + NEWLINE() + "Das ist ja ein " +
                COLOR(QM_RED) + "Nachtschwärmer" + COLOR(QM_WHITE) + "!" + WAIT_FOR_INPUT() + NEWLINE() +
                UNSKIPPABLE() + "Dafür bekommst du " + COLOR(QM_RED) + "50 Rubine" + COLOR(QM_WHITE) + "!" +
                WAIT_FOR_INPUT() + NEWLINE() + UNSKIPPABLE() + "Obendrein hast du nun " + COLOR(QM_RED) +
                "100 Punkte " + COLOR(QM_WHITE) + NEWLINE() + "auf dem Nachtschwärmer-Konto gut." + WAIT_FOR_INPUT() +
                NEWLINE() + UNSKIPPABLE() + "Hast du " + COLOR(QM_RED) + std::to_string(poes * 100) + " Punkte" +
                COLOR(QM_WHITE) + ", gesammelt, dann" + NEWLINE() + "wartet eine geniale Belohnung! Hehehe..." +
                MESSAGE_END());
    }

    // Talon (this is to prevent accidentally skipping Malon in HC)
    CreateMessage(
        0x9100, 0, 2, 0,
        UNSKIPPABLE() + "You should go talk to my daughter Malon," + NEWLINE() + "she has an item for you." +
            NEWLINE() + SET_SPEED(3) + "........." + SET_SPEED(0) + WAIT_FOR_INPUT() +
            "I have to think about some stuff now," + NEWLINE() + "please don't distract me." + MESSAGE_END(),
        UNSKIPPABLE() + "Zzzz... Muh... Malon..." + NEWLINE() + "Parler avec... Malon..." + NEWLINE() + SET_SPEED(3) +
            "........." + SET_SPEED(0) + WAIT_FOR_INPUT() + "Si fatigué..." + NEWLINE() + "Quelle vie..." +
            MESSAGE_END(),
        UNSKIPPABLE() + "Habla con Malon, tiene algo que darte..." + SET_SPEED(3) + "........." + SET_SPEED(0) +
            MESSAGE_END(),
        UNSKIPPABLE() + "Dovresti andare a parlare a mia figlia" + NEWLINE() + "Malon, ha un oggetto per te." +
            NEWLINE() + SET_SPEED(3) + "........." + SET_SPEED(0) + WAIT_FOR_INPUT() +
            "Ora devo pensare a delle cose serie," + NEWLINE() + "non distrarmi per favore." + MESSAGE_END(),
        UNSKIPPABLE() + "Du solltest mit meiner Tochter Malon" + NEWLINE() + "sprechen, sie hat etwas für dich." +
            NEWLINE() + SET_SPEED(3) + "........." + SET_SPEED(0) + WAIT_FOR_INPUT() +
            "Ich muss über etwas nachdenken," + NEWLINE() + "bitte störe mich nicht weiter." + MESSAGE_END());

    // Bow Shooting Gallery reminder
    CreateMessage(0x9140, 0, 0, 0,
                  UNSKIPPABLE() + "Come back when you have your own bow" + NEWLINE() + "and you'll get a " +
                      COLOR(QM_RED) + "different prize" + COLOR(QM_WHITE) + "!" + CLOSE_AFTER(255) + MESSAGE_END(),
                  UNSKIPPABLE() + "J'aurai " + COLOR(QM_RED) + "une autre récompense" + COLOR(QM_WHITE) + " pour toi" +
                      NEWLINE() + "lorsque tu auras ton propre arc." + CLOSE_AFTER(255) + MESSAGE_END(),
                  UNSKIPPABLE() + "Si regresas cuando tienes tu propio arco," + NEWLINE() + "recibirás " +
                      COLOR(QM_RED) + "otro premio" + COLOR(QM_WHITE) + "." + CLOSE_AFTER(255) + MESSAGE_END(),
                  UNSKIPPABLE() + "Torna quando avrai un tuo arco personale" + NEWLINE() + "e riceverai un " +
                      COLOR(QM_RED) + "altro premio" + COLOR(QM_WHITE) + "!" + CLOSE_AFTER(255) + MESSAGE_END(),
                  UNSKIPPABLE() + "Komm wieder sobald du deinen eigenen Bogen" + NEWLINE() + "hast, um einen " +
                      COLOR(QM_RED) + "speziellen Preis" + COLOR(QM_WHITE) + " zu erhalten!" + CLOSE_AFTER(255) +
                      MESSAGE_END());

    // Shopsanity items
    // 64 textboxes, 2 for each of 32 potential shopsanity items
    for (u32 shopitems = 0; shopitems < NonShopItems.size(); shopitems++) {
        Text name         = NonShopItems[shopitems].Name;
        std::string price = std::to_string(NonShopItems[shopitems].Price);
        // Prevent names from being too long and overflowing textbox
        Text priceSeparator = Text{
            name.NAenglish.length() <= 30 ? ": " : NEWLINE() + "                                        ",
            name.NAfrench.length() <= 30 ? ": " : NEWLINE() + "                                        ",
            name.NAspanish.length() <= 30 ? ": " : NEWLINE() + "                                        ",
            name.EURitalian.length() <= 30 ? " - " : NEWLINE() + "                                        ",
            name.EURgerman.length() <= 30 ? ": " : NEWLINE() + "                                        ",
        };
        Text newlinesAfterPrice = Text{
            name.NAenglish.length() <= 30 ? NEWLINE() + NEWLINE() : NEWLINE(),
            name.NAfrench.length() <= 30 ? NEWLINE() + NEWLINE() : NEWLINE(),
            name.NAspanish.length() <= 30 ? NEWLINE() + NEWLINE() : NEWLINE(),
            name.EURitalian.length() <= 30 ? NEWLINE() + NEWLINE() : NEWLINE(),
            name.EURgerman.length() <= 30 ? NEWLINE() + NEWLINE() : NEWLINE(),
        };
        // Message to display when hovering over the item
        if (NonShopItems[shopitems].Repurchaseable) { // Different checkbox for repurchaseable items
            CreateMessage(0x9200 + shopitems * 2, 0, 0, 0,
                          INSTANT_TEXT_ON() + COLOR(QM_RED) + name.GetNAEnglish() + priceSeparator.GetNAEnglish() +
                              price + " Rupees" + NEWLINE() + COLOR(QM_WHITE) + "Special deal!" + NEWLINE() +
                              "Buy as many as you want!" + SHOP_MESSAGE_BOX() + MESSAGE_END(),
                          INSTANT_TEXT_ON() + COLOR(QM_RED) + name.GetNAFrench() + priceSeparator.GetNAFrench() +
                              price + " rubis" + NEWLINE() + COLOR(QM_WHITE) + "Offre spéciale!" + NEWLINE() +
                              "Achetez-en à volonté!" + SHOP_MESSAGE_BOX() + MESSAGE_END(),
                          INSTANT_TEXT_ON() + COLOR(QM_RED) + name.GetNASpanish() + priceSeparator.GetNASpanish() +
                              price + " rupias" + NEWLINE() + COLOR(QM_WHITE) + "¡Oferta especial!" + NEWLINE() +
                              "¡Compra todo lo que quieras!" + SHOP_MESSAGE_BOX() + MESSAGE_END(),
                          INSTANT_TEXT_ON() + COLOR(QM_RED) + name.GetEURItalian() + priceSeparator.GetEURItalian() +
                              price + " rupie" + NEWLINE() + COLOR(QM_WHITE) + "Offerta speciale!" + NEWLINE() +
                              "Compratene a volontà!" + SHOP_MESSAGE_BOX() + MESSAGE_END(),
                          INSTANT_TEXT_ON() + COLOR(QM_RED) + name.GetEURGerman() + priceSeparator.GetEURGerman() +
                              price + " Rubine" + NEWLINE() + COLOR(QM_WHITE) + "Sonderangebot!" + NEWLINE() +
                              "Kauft so viel ihr wollt!" + SHOP_MESSAGE_BOX() + MESSAGE_END());
        } else { // Normal textbox
            CreateMessage(0x9200 + shopitems * 2, 0, 0, 0,
                          INSTANT_TEXT_ON() + COLOR(QM_RED) + name.GetNAEnglish() + priceSeparator.GetNAEnglish() +
                              price + " Rupees" + NEWLINE() + COLOR(QM_WHITE) + "Special deal! ONE LEFT!" + NEWLINE() +
                              "Get it while it lasts!" + SHOP_MESSAGE_BOX() + MESSAGE_END(),
                          INSTANT_TEXT_ON() + COLOR(QM_RED) + name.GetNAFrench() + priceSeparator.GetNAFrench() +
                              price + " rubis" + NEWLINE() + COLOR(QM_WHITE) + "Offre spéciale! DERNIER EN STOCK!" +
                              NEWLINE() + "Faites vite!" + SHOP_MESSAGE_BOX() + MESSAGE_END(),
                          INSTANT_TEXT_ON() + COLOR(QM_RED) + name.GetNASpanish() + priceSeparator.GetNASpanish() +
                              price + " rupias" + NEWLINE() + COLOR(QM_WHITE) +
                              "¡Oferta especial! ¡SOLO QUEDA UNA UNIDAD!" + NEWLINE() +
                              "¡Hazte con ella antes de que se agote!" + SHOP_MESSAGE_BOX() + MESSAGE_END(),
                          INSTANT_TEXT_ON() + COLOR(QM_RED) + name.GetEURItalian() + priceSeparator.GetEURItalian() +
                              price + " rupie" + NEWLINE() + COLOR(QM_WHITE) + "Offerta speciale! ULTIMO PEZZO!" +
                              NEWLINE() + "Affrettatevi ad aquistarlo!" + SHOP_MESSAGE_BOX() + MESSAGE_END(),
                          INSTANT_TEXT_ON() + COLOR(QM_RED) + name.GetEURGerman() + priceSeparator.GetEURGerman() +
                              price + " Rubine" + NEWLINE() + COLOR(QM_WHITE) + "Sonderangebot! NUR EINS AUF LAGER!" +
                              NEWLINE() + "Schlagt zu solange ihr noch könnt!" + SHOP_MESSAGE_BOX() + MESSAGE_END());
        }
        // Message to display when going to buy the item
        CreateMessage(
            0x9200 + shopitems * 2 + 1, 0, 0, 0,
            INSTANT_TEXT_ON() + name.GetNAEnglish() + priceSeparator.GetNAEnglish() + price + " Rupees" +
                INSTANT_TEXT_OFF() + newlinesAfterPrice.GetNAEnglish() + TWO_WAY_CHOICE() + COLOR(QM_GREEN) + "Buy" +
                NEWLINE() + "Don't buy" + COLOR(QM_WHITE) + INSTANT_TEXT_OFF() + MESSAGE_END(),
            INSTANT_TEXT_ON() + name.GetNAFrench() + priceSeparator.GetNAFrench() + price + " rubis" +
                INSTANT_TEXT_OFF() + newlinesAfterPrice.GetNAFrench() + TWO_WAY_CHOICE() + COLOR(QM_GREEN) + "Acheter" +
                NEWLINE() + "Ne pas acheter" + COLOR(QM_WHITE) + INSTANT_TEXT_OFF() + MESSAGE_END(),
            INSTANT_TEXT_ON() + name.GetNASpanish() + priceSeparator.GetNASpanish() + price + " rupias" +
                INSTANT_TEXT_OFF() + newlinesAfterPrice.GetNASpanish() + TWO_WAY_CHOICE() + COLOR(QM_GREEN) +
                "Comprar" + NEWLINE() + "No comprar" + COLOR(QM_WHITE) + INSTANT_TEXT_OFF() + MESSAGE_END(),
            INSTANT_TEXT_ON() + name.GetEURItalian() + priceSeparator.GetEURItalian() + price + " rupie" +
                INSTANT_TEXT_OFF() + newlinesAfterPrice.GetEURItalian() + TWO_WAY_CHOICE() + COLOR(QM_GREEN) +
                "Compra" + NEWLINE() + "Non comprare" + COLOR(QM_WHITE) + INSTANT_TEXT_OFF() + MESSAGE_END(),
            INSTANT_TEXT_ON() + name.GetEURGerman() + priceSeparator.GetEURGerman() + price + " Rubine" +
                INSTANT_TEXT_OFF() + newlinesAfterPrice.GetEURGerman() + TWO_WAY_CHOICE() + COLOR(QM_GREEN) +
                "Kaufen!" + NEWLINE() + "Nicht kaufen!" + COLOR(QM_WHITE) + INSTANT_TEXT_OFF() + MESSAGE_END());
    }
    // easter egg
    CreateMessage(0x96F, 0, 2, 2,
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "Oh hey, you watched all the credits!" +
                      NEWLINE() + CENTER_TEXT() + "Here's a prize for your patience." + NEWLINE() + CENTER_TEXT() +
                      "Unlocking MQ and saving..." + NEWLINE() + NEWLINE() + CENTER_TEXT() + COLOR(QM_RED) +
                      "Do not remove the Game Card" + NEWLINE() + CENTER_TEXT() + "or turn the power off." +
                      INSTANT_TEXT_OFF() + MESSAGE_END(),
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "The Legend of Zelda Ocarina of Time 3D" +
                      NEWLINE() + CENTER_TEXT() + "Master Quest va être déverrouillé." + NEWLINE() + CENTER_TEXT() +
                      "Sauvegarde... Veuillez patienter." + NEWLINE() + NEWLINE() + CENTER_TEXT() + COLOR(QM_RED) +
                      "N'éteignez pas la console et" + NEWLINE() + CENTER_TEXT() + "ne retirez pas la carte de jeu" +
                      INSTANT_TEXT_OFF() + MESSAGE_END(),
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "Desbloqueando The Legend of Zelda" + NEWLINE() +
                      CENTER_TEXT() + "Ocarina of Time 3D Master Quest." + NEWLINE() + CENTER_TEXT() +
                      "Guardando. Espera un momento..." + NEWLINE() + NEWLINE() + CENTER_TEXT() + COLOR(QM_RED) +
                      "No saques la tarjeta de juego" + NEWLINE() + CENTER_TEXT() + "ni apagues la consola." +
                      INSTANT_TEXT_OFF() + MESSAGE_END(),
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "Oh, hai guardato i crediti fino alla fine!" +
                      NEWLINE() + CENTER_TEXT() + "Ecco un premio per la tua pazienza." + NEWLINE() + CENTER_TEXT() +
                      "Sblocco MQ e salvataggio in corso..." + NEWLINE() + NEWLINE() + CENTER_TEXT() + COLOR(QM_RED) +
                      "Non estrarre la scheda di gioco" + NEWLINE() + CENTER_TEXT() + "e non spegnere la console." +
                      INSTANT_TEXT_OFF() + MESSAGE_END(),
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "Oh, du hast dir den ganzen Abspann angeschaut!" +
                      NEWLINE() + CENTER_TEXT() + "Hier ist eine Belohnung für deine Geduld." + NEWLINE() +
                      CENTER_TEXT() + "Master Quest wird freigeschaltet..." + NEWLINE() + NEWLINE() + CENTER_TEXT() +
                      COLOR(QM_RED) + "Bitte entferne nicht die Karte und" + NEWLINE() + CENTER_TEXT() +
                      "schalte das System nicht aus." + INSTANT_TEXT_OFF() + MESSAGE_END());
    CreateMessage(0x970, 0, 2, 3,
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "Master Quest doesn't affect the Randomizer," +
                      NEWLINE() + CENTER_TEXT() + "so you can use 3 more save slots now." + NEWLINE() + NEWLINE() +
                      CENTER_TEXT() + "Thanks for playing!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "Vous pouvez désormais jouer à" + NEWLINE() +
                      CENTER_TEXT() + "The Legend of Zelda Ocarina of Time 3D" + NEWLINE() + CENTER_TEXT() +
                      "Master Quest!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "¡Ya puedes jugar The Legend of Zelda" +
                      NEWLINE() + CENTER_TEXT() + "Ocarina of Time 3D Master Quest!" + INSTANT_TEXT_OFF() +
                      MESSAGE_END(),
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "Il Randomizer non cambierà in Master Quest," +
                      NEWLINE() + CENTER_TEXT() + "perciò ora puoi usare altri 3 file." + NEWLINE() + NEWLINE() +
                      CENTER_TEXT() + "Grazie per aver giocato!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "Master Quest beeinflusst den Randomizer" +
                      NEWLINE() + CENTER_TEXT() + "nicht, dir stehen von jetzt an nur 3" + NEWLINE() + CENTER_TEXT() +
                      "weitere Speicherstände zur Verfügung." + NEWLINE() + NEWLINE() + CENTER_TEXT() +
                      "Danke fürs Spielen!" + INSTANT_TEXT_OFF() + MESSAGE_END());

    // Messages for the new Lake Hylia switch
    CreateMessage(0x346, 0, 1, 3,
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "Water level control system." + NEWLINE() +
                      CENTER_TEXT() + "Keep away!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "Contrôle du niveau d'eau." + NEWLINE() +
                      CENTER_TEXT() + "Ne pas toucher!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "Control del nivel del agua." + NEWLINE() +
                      CENTER_TEXT() + "¡No te acerques!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "Controllo del livello dell'acqua." + NEWLINE() +
                      CENTER_TEXT() + "Non toccare!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
                  UNSKIPPABLE() + INSTANT_TEXT_ON() + CENTER_TEXT() + "Wasserstand Kontrollsystem" + NEWLINE() +
                      CENTER_TEXT() + "Finger weg!" + INSTANT_TEXT_OFF() + MESSAGE_END());
    CreateMessage(
        0x1B3, 0, 0, 3,
        UNSKIPPABLE() + "This switch is rustier than you think." + WAIT_FOR_INPUT() +
            "Something must be wrong with the pipe" + NEWLINE() + "system in the Water Temple." + MESSAGE_END(),
        UNSKIPPABLE() + "Cet interrupteur est très rouillé." + WAIT_FOR_INPUT() + "Quelque chose ne va pas avec" +
            NEWLINE() + "la tuyauterie du Temple de l'Eau." + MESSAGE_END(),
        UNSKIPPABLE() + "El interruptor está más oxidado de lo que" + NEWLINE() + "aparenta." + WAIT_FOR_INPUT() +
            "Algo debe andar mal en el sistema de" + NEWLINE() + "cañerías del Templo del Agua." + MESSAGE_END(),
        UNSKIPPABLE() + "Questo interruttore è più arrugginito di" + NEWLINE() + "quanto sembri." + WAIT_FOR_INPUT() +
            "Deve esserci qualche problema nelle" + NEWLINE() + "tubature del Santuario dell'Acqua." + MESSAGE_END(),
        UNSKIPPABLE() + "Dieser Schalter scheint rostiger zu sein" + NEWLINE() + "als er aussieht." + WAIT_FOR_INPUT() +
            "Etwas muss mit dem Leitungssystem" + NEWLINE() + "im Wassertempel nicht stimmen." + MESSAGE_END());

    // Treasure chest shop keys. If they're not randomized leave the base game text
    if (Settings::ShuffleChestMinigame.Is(SHUFFLECHESTMINIGAME_SINGLE_KEYS)) {
        CreateMessage(0x0F3, 0, 2, 3,
                      UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_SMALL) + INSTANT_TEXT_ON() + "You got a " + COLOR(QM_RED) +
                          "Treasure Chest Shop" + NEWLINE() + "Small Key" + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF() +
                          MESSAGE_END(),
                      UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_SMALL) + INSTANT_TEXT_ON() + "Vous trouvez une " +
                          COLOR(QM_RED) + "petite clé" + NEWLINE() + "de la chasse aux trésors" + COLOR(QM_WHITE) +
                          "!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
                      UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_SMALL) + INSTANT_TEXT_ON() + "¡Has obtenido una " +
                          COLOR(QM_RED) + "llave pequeña del" + NEWLINE() + "Cofre del Tesoro" + COLOR(QM_WHITE) + "!" +
                          INSTANT_TEXT_OFF() + MESSAGE_END(),
                      UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_SMALL) + INSTANT_TEXT_ON() + "Hai ottenuto una " +
                          COLOR(QM_RED) + "piccola chiave della" + NEWLINE() + "sala della fortuna" + COLOR(QM_WHITE) +
                          "!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
                      UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_SMALL) + INSTANT_TEXT_ON() + "Du hast einen " +
                          COLOR(QM_RED) + "kleinen Schlüssel " + COLOR(QM_WHITE) + "der" + NEWLINE() + COLOR(QM_RED) +
                          "Truhenlotterie " + COLOR(QM_WHITE) + "erhalten!" + INSTANT_TEXT_OFF() + MESSAGE_END());
    } else if (Settings::ShuffleChestMinigame.Is(SHUFFLECHESTMINIGAME_PACK)) {
        CreateMessage(0x0F3, 0, 2, 3,
                      UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_SMALL) + INSTANT_TEXT_ON() + "You got all 6 " +
                          COLOR(QM_RED) + "Treasure Chest Shop" + NEWLINE() + "Small Keys" + COLOR(QM_WHITE) + "!" +
                          INSTANT_TEXT_OFF() + MESSAGE_END(),
                      UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_SMALL) + INSTANT_TEXT_ON() + "Vous trouvez les " +
                          COLOR(QM_RED) + "petites clés" + NEWLINE() + "de la chasse aux trésors" + COLOR(QM_WHITE) +
                          "!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
                      UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_SMALL) + INSTANT_TEXT_ON() + "¡Has obtenido todas las 6 " +
                          COLOR(QM_RED) + "llaves" + NEWLINE() + "pequeñas del Cofre del Tesoro" + COLOR(QM_WHITE) +
                          "!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
                      UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_SMALL) + INSTANT_TEXT_ON() + "Hai ottenuto tutte e 6 le " +
                          COLOR(QM_RED) + "piccole" + NEWLINE() + "chiavi della sala della fortuna" + COLOR(QM_WHITE) +
                          "!" + INSTANT_TEXT_OFF() + MESSAGE_END(),
                      UNSKIPPABLE() + ITEM_OBTAINED(ITEM_KEY_SMALL) + INSTANT_TEXT_ON() + "Du hast das " +
                          COLOR(QM_RED) + "Schlüsselbund " + COLOR(QM_WHITE) + "der" + NEWLINE() + COLOR(QM_RED) +
                          "Truhenlotterie " + COLOR(QM_WHITE) + "erhalten!" + INSTANT_TEXT_OFF() + MESSAGE_END());
    }

    // Ruto picking up the dungeon reward
    {
        u8 itemColor;
        switch (Location(BARINADE)->GetPlacedItem().GetHintKey()) {
            case KOKIRI_EMERALD:
            case FOREST_MEDALLION:
                itemColor = QM_GREEN;
                break;
            case ZORA_SAPPHIRE:
            case WATER_MEDALLION:
                itemColor = QM_BLUE;
                break;
            case SHADOW_MEDALLION:
                itemColor = QM_PINK;
                break;
            case LIGHT_MEDALLION:
            case SPIRIT_MEDALLION:
            case GOLD_SKULLTULA_TOKEN:
                itemColor = QM_YELLOW;
                break;
            default:
                itemColor = QM_RED;
                break;
        }

        Text rutoDialog = Text{ "Princess Ruto got #", "La princesse Ruto a trouvé #", "¡La princesa Ruto tiene #",
                                "La Principessa Ruto ha recuperato #", "Prinzessin Ruto hat #" } +
                          Location(BARINADE)->GetPlacedItem().GetHint().GetClear() +
                          Text{ "#!^But why Princess Ruto?", "#!^Mais pourquoi la princesse Ruto?",
                                "#!^Tú te quedas con las ganas...", "#...", "#!^Aber warum Prinzessin Ruto?" };

        rutoDialog.Replace("$", ""); // Plural marker
        CreateMessageFromTextObject(0x4050, 0, 2, 3, AddColorsAndFormat(rutoDialog, { itemColor }));
    }

    // Triforce Piece
    {
        Text triforceMsg =
            Text{ /*english*/ "You found a piece of the #Triforce#!&You have #" + TRIFORCE_PIECE_COUNT() + "#!",
                  /*french */ "",
                  /*spanish*/ "",
                  /*italian*/ "Hai ottenuto un frammento della #Triforza#!&Ne hai #" + TRIFORCE_PIECE_COUNT() + "#!",
                  /*german */ "" };
        CreateMessageFromTextObject(0x9003, 0, 2, 3, AddColorsAndFormat(triforceMsg, { QM_RED, QM_RED }));
    }
}

std::vector<Text> CreateBaseCompassTexts() {
    std::vector<Text> compassTexts = {};
    for (u32 dungeon = DUNGEON_DEKU_TREE; dungeon <= DUNGEON_ICE_CAVERN; dungeon++) {
        compassTexts.push_back(Text{
            UNSKIPPABLE() + ITEM_OBTAINED(ITEM_COMPASS) + INSTANT_TEXT_ON() + "You got the " +
                COLOR(DungeonColors[dungeon]) + EnglishDungeonNames[dungeon] + NEWLINE() + "Compass" + COLOR(QM_WHITE) +
                "!" + INSTANT_TEXT_OFF(),
            UNSKIPPABLE() + ITEM_OBTAINED(ITEM_COMPASS) + INSTANT_TEXT_ON() + "Vous trouvez la " +
                COLOR(DungeonColors[dungeon]) + "boussole " + NEWLINE() + FrenchDungeonArticles[dungeon] +
                FrenchDungeonNames[dungeon] + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF(),
            UNSKIPPABLE() + ITEM_OBTAINED(ITEM_COMPASS) + INSTANT_TEXT_ON() + "¡Tienes la " +
                COLOR(DungeonColors[dungeon]) + "brújula " + SpanishDungeonArticles[dungeon] + NEWLINE() +
                SpanishDungeonNames[dungeon] + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF(),
            UNSKIPPABLE() + ITEM_OBTAINED(ITEM_COMPASS) + INSTANT_TEXT_ON() + "Hai ottenuto la " +
                COLOR(DungeonColors[dungeon]) + "bussola " + ItalianDungeonArticles[dungeon] + NEWLINE() +
                ItalianDungeonNames[dungeon] + COLOR(QM_WHITE) + "!" + INSTANT_TEXT_OFF(),
            UNSKIPPABLE() + ITEM_OBTAINED(ITEM_COMPASS) + INSTANT_TEXT_ON() + "Du hast den " +
                COLOR(DungeonColors[dungeon]) + "Kompass " + COLOR(QM_WHITE) + GermanDungeonArticles[dungeon] +
                NEWLINE() + COLOR(DungeonColors[dungeon]) + GermanDungeonNames[dungeon] +
                GermanDungeonGenitiv[dungeon] + COLOR(QM_WHITE) + "erhalten!" + INSTANT_TEXT_OFF(),
        });
    }
    return compassTexts;
}

// Width of all used characters in pixels when displayed in-game. Each number
// is actually the pixel width of each character plus one since the game puts
// one pixel of space between each character in a textbox.
// Used to nicely format messages
static std::map<std::string, int> pixelWidthTable = {
    { " ", 4 },  { "!", 3 },  { "\"", 5 },     { "#", 9 },  { "$", 9 },  { "%", 11 }, { "&", 9 },  { "\'", 4 },
    { "(", 5 },  { ")", 5 },  { "*", 6 },      { "+", 8 },  { ",", 4 },  { "-", 6 },  { ".", 3 },  { "/", 6 },
    { "0", 8 },  { "1", 4 },  { "2", 8 },      { "3", 8 },  { "4", 8 },  { "5", 8 },  { "6", 8 },  { "7", 8 },
    { "8", 8 },  { "9", 8 },  { ":", 3 },      { ";", 3 },  { "<", 8 },  { "=", 9 },  { ">", 8 },  { "?", 7 },
    { "@", 11 }, { "A", 11 }, { "B", 9 },      { "C", 10 }, { "D", 9 },  { "E", 8 },  { "F", 8 },  { "G", 10 },
    { "H", 9 },  { "I", 3 },  { "J", 8 },      { "K", 9 },  { "L", 7 },  { "M", 11 }, { "N", 9 },  { "O", 11 },
    { "P", 9 },  { "Q", 11 }, { "R", 9 },      { "S", 9 },  { "T", 9 },  { "U", 9 },  { "V", 10 }, { "W", 12 },
    { "X", 9 },  { "Y", 10 }, { "Z", 9 },      { "[", 5 },  { "\\", 6 }, { "]", 5 },  { "^", 7 },  { "_", 8 },
    { "`", 4 },  { "a", 8 },  { "b", 8 },      { "c", 8 },  { "d", 8 },  { "e", 8 },  { "f", 5 },  { "g", 8 },
    { "h", 7 },  { "i", 3 },  { "j", 4 },      { "k", 7 },  { "l", 3 },  { "m", 10 }, { "n", 7 },  { "o", 9 },
    { "p", 8 },  { "q", 8 },  { "r", 5 },      { "s", 7 },  { "t", 5 },  { "u", 7 },  { "v", 8 },  { "w", 9 },
    { "x", 8 },  { "y", 8 },  { "z", 8 },      { "{", 5 },  { "¦", 3 },  { "}", 5 },  { "¡", 5 },  { "¢", 7 },
    { "£", 8 },  { "¤", 7 },  { "¥", 8 },      { "|", 3 },  { "§", 12 }, { "¨", 12 }, { "©", 10 }, { "ª", 5 },
    { "«", 8 },  { "¬", 7 },  { "\u00AD", 6 }, { "®", 10 }, { "¯", 5 },  { "°", 12 }, { "±", 12 }, { "²", 5 },
    { "³", 5 },  { "µ", 6 },  { "¶", 8 },      { "·", 4 },  { "¹", 4 },  { "º", 5 },  { "»", 9 },  { "¼", 9 },
    { "½", 9 },  { "¾", 10 }, { "¿", 7 },      { "À", 11 }, { "Á", 11 }, { "Â", 11 }, { "Ã", 11 }, { "Ä", 11 },
    { "Å", 11 }, { "Æ", 12 }, { "Ç", 10 },     { "È", 8 },  { "É", 8 },  { "Ê", 8 },  { "Ë", 8 },  { "Ì", 5 },
    { "Í", 5 },  { "Î", 5 },  { "Ï", 5 },      { "Ð", 10 }, { "Ñ", 9 },  { "Ò", 11 }, { "Ó", 11 }, { "Ô", 11 },
    { "Õ", 11 }, { "Ö", 11 }, { "×", 9 },      { "Ø", 11 }, { "Ù", 9 },  { "Ú", 9 },  { "Û", 9 },  { "Ü", 9 },
    { "Ý", 10 }, { "Þ", 8 },  { "ß", 8 },      { "à", 8 },  { "á", 8 },  { "â", 8 },  { "ã", 8 },  { "ä", 8 },
    { "å", 8 },  { "æ", 11 }, { "ç", 8 },      { "è", 8 },  { "é", 8 },  { "ê", 8 },  { "ë", 8 },  { "ì", 5 },
    { "í", 5 },  { "î", 5 },  { "ï", 5 },      { "ð", 9 },  { "ñ", 7 },  { "ò", 9 },  { "ó", 9 },  { "ô", 9 },
    { "õ", 9 },  { "ö", 9 },  { "÷", 11 },     { "ø", 9 },  { "ù", 7 },  { "ú", 7 },  { "û", 7 },  { "ü", 7 },
    { "ý", 8 },  { "þ", 8 },  { "ÿ", 8 },      { "Œ", 11 }, { "œ", 11 }, { "„", 5 },  { "”", 5 },  { "€", 10 },
    { "Ÿ", 10 },
};

// Takes a string and the position of the last calculated newline.
// Calculates the maximum number of characters that could satisfy
// next line in the string from the last calculated newline.
static size_t NextLineLength(std::string* textStr, size_t lastNewline) {
    constexpr size_t maxLinePixelWidth = 287;

    size_t totalPixelWidth = 0;
    size_t currentPos      = lastNewline;

    // Looping through the string from the lastNewline until the total
    // width of counted characters exceeds the maximum pixels in a line
    size_t nextPosJump = 0;
    while (totalPixelWidth < maxLinePixelWidth && currentPos < textStr->length()) {
        // Skip over control codes
        if (textStr->at(currentPos) == '\x7F') {
            if (IsAnyOf(textStr->at(currentPos + 1), '\x02', '\x06', '\x08', '\x0A', '\x0F', '\x10', '\x1D')) {
                nextPosJump = 3;
            } else if (textStr->at(currentPos + 1) == '\x03') {
                nextPosJump = 4;
            } else if (textStr->at(currentPos + 1) == '\x1A') {
                nextPosJump = 6;
            } else if (textStr->at(currentPos + 1) == '\x0E') {
                nextPosJump = 7;
            } else if (textStr->at(currentPos + 1) == '\x0B') {
                nextPosJump = 2;
                // Assume worst case for player name 12 * 8 (widest character * longest name length)
                totalPixelWidth += 96;
            } else {
                nextPosJump = 2;
            }
        } else {
            // Some characters are only one byte while others are two bytes
            // So check both possibilities when checking for a character
            if (pixelWidthTable.count(textStr->substr(currentPos, 1))) {
                totalPixelWidth += pixelWidthTable[textStr->substr(currentPos, 1)];
                nextPosJump = 1;
            } else if (pixelWidthTable.count(textStr->substr(currentPos, 2))) {
                totalPixelWidth += pixelWidthTable[textStr->substr(currentPos, 2)];
                nextPosJump = 2;
            } else {
                CitraPrint("Table does not contain " + textStr->substr(currentPos, 1) + "/" +
                           textStr->substr(currentPos, 2));
                CitraPrint("Full string: " + *textStr);
                nextPosJump = 1;
            }
        }

        currentPos += nextPosJump;
    }

    // return the total number of characters we looped through
    if (totalPixelWidth > maxLinePixelWidth && textStr->at(currentPos - nextPosJump) != ' ') {
        return currentPos - lastNewline - nextPosJump;
    } else {
        return currentPos - lastNewline;
    }
}

Text AddColorsAndFormat(Text text, const std::vector<u8>& colors /*= {}*/) {

    // for each language
    for (std::string* textStr : { &text.NAenglish, &text.NAfrench, &text.NAspanish, &text.EURenglish, &text.EURfrench,
                                  &text.EURspanish, &text.EURitalian, &text.EURgerman }) {

        // insert playername
        size_t atSymbol = textStr->find('@');
        while (atSymbol != std::string::npos) {
            textStr->replace(atSymbol, 1, PLAYER_NAME());
            atSymbol = textStr->find('@');
        }

        // add colors
        for (auto color : colors) {
            size_t firstHashtag = textStr->find('#');
            if (firstHashtag != std::string::npos) {
                textStr->replace(firstHashtag, 1, COLOR(color));
                size_t secondHashtag = textStr->find('#');
                if (secondHashtag == std::string::npos) {
                    CitraPrint("ERROR: Couldn't find second '#' in " + (*textStr));
                } else {
                    textStr->replace(secondHashtag, 1, COLOR(QM_WHITE));
                }
            }
        }

        // add SFX
        size_t brace = textStr->find('{');
        while (brace != std::string::npos) {
            std::string sfxString = textStr->substr(brace + 1, brace + 3);
            u16 sfxNumber         = stoi(sfxString, nullptr, 16);
            textStr->replace(brace, 5, PLAY_SFX(sfxNumber));
            brace = textStr->find('{');
        }

        // insert newlines either manually or when encountering a '&'
        size_t lastNewline = 0;
        size_t lineLength  = NextLineLength(textStr, lastNewline);
        while (lastNewline + lineLength < textStr->length()) {
            size_t carrot     = textStr->find('^', lastNewline);
            size_t ampersand  = textStr->find('&', lastNewline);
            size_t lastSpace  = textStr->rfind(' ', lastNewline + lineLength);
            size_t lastPeriod = textStr->rfind('.', lastNewline + lineLength);
            // replace '&' first if it's within the newline range
            if (ampersand < lastNewline + lineLength) {
                textStr->replace(ampersand, 1, NEWLINE());
                lastNewline = ampersand + NEWLINE().length();
                // or move the lastNewline cursor to the next line if a '^' is encountered
            } else if (carrot < lastNewline + lineLength) {
                lastNewline = carrot + 1;
                // some lines need to be split but don't have spaces, look for periods instead
            } else if (lastSpace == std::string::npos) {
                textStr->replace(lastPeriod, 1, "." + NEWLINE());
                lastNewline = lastPeriod + NEWLINE().length() + 1;
            } else {
                textStr->replace(lastSpace, 1, NEWLINE());
                lastNewline = lastSpace + NEWLINE().length();
            }
            lineLength = NextLineLength(textStr, lastNewline);
        }
        // clean up any remaining '&' characters
        size_t ampersand = textStr->find('&');
        while (ampersand != std::string::npos) {
            textStr->replace(ampersand, 1, NEWLINE());
            ampersand = textStr->find('&');
        }

        // insert box break
        size_t carrotSymbol = textStr->find('^');
        while (carrotSymbol != std::string::npos) {
            textStr->replace(carrotSymbol, 1, INSTANT_TEXT_OFF() + WAIT_FOR_INPUT() + INSTANT_TEXT_ON());
            carrotSymbol = textStr->find('^');
        }

        // If there's a two-way choice and only 1 newline before it in the same text box, add another one
        size_t choice = textStr->find(TWO_WAY_CHOICE());
        if (choice != std::string::npos) {
            size_t newLinesCount = 0;
            size_t lastBoxBreak  = textStr->rfind(WAIT_FOR_INPUT(), choice);
            lastNewline          = choice;

            if (lastBoxBreak == std::string::npos) {
                lastBoxBreak = 0;
            }

            while ((lastNewline != std::string::npos)) {
                lastNewline = textStr->rfind(NEWLINE(), lastNewline - 1);
                if (lastNewline != std::string::npos && lastNewline > lastBoxBreak) {
                    newLinesCount++;
                } else {
                    break;
                }
            }

            if (newLinesCount <= 1) {
                textStr->replace(choice, TWO_WAY_CHOICE().length(), NEWLINE() + TWO_WAY_CHOICE());
            }
        }
    }
    return Text{ "" } + UNSKIPPABLE() + INSTANT_TEXT_ON() + text + INSTANT_TEXT_OFF() + MESSAGE_END();
}

void ClearMessages() {
    messageEntries.clear();
    arrangedMessageEntries.clear();
    messageData.str("");
    arrangedMessageData = "";
}

std::string MESSAGE_END() {
    return "\x7F\x00"s;
}
std::string WAIT_FOR_INPUT() {
    return "\x7F\x01"s;
}
std::string HORIZONTAL_SPACE(u8 x) {
    return "\x7F\x02"s + char(x);
}
std::string GO_TO(u16 x) {
    return "\x7F\x03"s + char(x >> 8) + char(x & 0x00FF);
}
std::string INSTANT_TEXT_ON() {
    return "\x7F\x04"s;
}
std::string INSTANT_TEXT_OFF() {
    return "\x7F\x05"s;
}
std::string SHOP_MESSAGE_BOX() {
    return "\x7F\x06\x00"s;
}
std::string EVENT_TRIGGER() {
    return "\x7F\x07"s;
}
std::string DELAY_FRAMES(u8 x) {
    return "\x7F\x08"s + char(x);
}
std::string CLOSE_AFTER(u8 x) {
    return "\x7F\x0A"s + char(x);
}
std::string PLAYER_NAME() {
    return "\x7F\x0B"s;
}
std::string PLAY_OCARINA() {
    return "\x7F\x0C"s;
}
std::string PLAY_SFX(u16 x) {
    return "\x7F\x0E\x00\x01\x00"s + char(x >> 8) + char(x & 0x00FF);
}
std::string ITEM_OBTAINED(u8 x) {
    return "\x7F\x0F"s + char(x);
}
std::string SET_SPEED(u8 x) {
    return "\x7F\x10"s + char(x);
}
std::string SKULLTULAS_DESTROYED() {
    return "\x7F\x15"s;
}
std::string CURRENT_TIME() {
    return "\x7F\x17"s;
}
std::string UNSKIPPABLE() {
    return "\x7F\x19"s;
}
std::string TWO_WAY_CHOICE() {
    return "\x7F\x1A\xFF\xFF\xFF\xFF"s;
}
std::string NEWLINE() {
    return "\x7F\x1C"s;
}
std::string COLOR(u8 x) {
    return "\x7F\x1D"s + char(x);
}
std::string CENTER_TEXT() {
    return "\x7F\x1E"s;
}
std::string IF_NOT_MQ() {
    return "\x7F\x29"s;
}
std::string MQ_ELSE() {
    return "\x7F\x2A"s;
}
std::string MQ_END() {
    return "\x7F\x2B"s;
}
std::string TRIFORCE_PIECE_COUNT() {
    return "\x7F\x30"s;
}
} // namespace CustomMessages
