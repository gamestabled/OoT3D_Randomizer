#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>

#include "cmeta_interpreter.hpp"

static const std::string CMETAKEY_BANKS    = "banks";
static const std::string CMETAKEY_CHFLAGS  = "chFlags";
static const std::string CMETAKEY_VOLUME   = "volume";
static const std::string CMETAKEY_CATEGORY = "category";

CMetaInterpreter::CMetaInterpreter(std::string path) : banks{ 7, 7, 7, 7 }, channelFlags(-1), volume(0x7F) {
    // Set banks to Orchestra by default
    // Enable all channel flags by default
    // 100% volume (assumed, as it's unsigned) by default

    std::fstream f(path);
    std::string f_out;
    while (std::getline(f, f_out)) {
        std::stringstream ss(f_out);
        std::string key;
        std::string value;
        std::getline(ss, key, '=');
        std::getline(ss, value, '=');

        // Removes leading and trailing spaces, tabs, and newline characters
        const auto sanitizeInput = [](std::string& str) {
            std::replace(str.begin(), str.end(), '\t', ' ');
            str.erase(0, str.find_first_not_of(' '));
            str.erase(str.find_last_not_of(' ') + 1);
            while (str.back() == '\n' || str.back() == '\r') {
                str.pop_back();
            }
        };

        sanitizeInput(key);
        sanitizeInput(value);

        const auto getIntFromValue = [](std::string value) {
            if (value.length() > 2) {
                // Hexadecimal
                if (value[0] == '0' && value[1] == 'x') {
                    return std::stoi(value, nullptr, 16);
                }
                // Binary
                else if (value[0] == '0' && value[1] == 'b') {
                    value.erase(0, 2);
                    return std::stoi(value, nullptr, 2);
                }
            }
            // Percentage, decimal (Should only be used for volume)
            if (value.back() == '%') {
                value.pop_back();
                return std::min(0xFF, (int)(0xFF * (std::stoi(value) / 200.0f)));
            }
            // Decimal
            return std::stoi(value);
        };

        if (key == CMETAKEY_BANKS) {
            // Effectively treat all non-alphanumerical symbols as separators
            for (size_t i = 0; i < value.length(); i++) {
                if (!isalnum(value.at(i))) {
                    value.at(i) = ' ';
                }
            }
            std::stringstream bs(value);
            u8 i = 0;
            std::string bs_out;
            while (std::getline(bs, bs_out, ' ')) {
                // Two spaces in a row gives an empty token; skip them
                if (bs_out.empty()) {
                    continue;
                }
                // At most four banks can be set
                if (i >= 4) {
                    break;
                }
                banks.at(i) = getIntFromValue(bs_out);
                i++;
            }
        } else if (key == CMETAKEY_CHFLAGS) {
            channelFlags = getIntFromValue(value);
        } else if (key == CMETAKEY_VOLUME) {
            volume = getIntFromValue(value);
        } else if (key == CMETAKEY_CATEGORY) {
            category = value;
            if (category.front() == '!') {
                category.erase(0, category.find_first_not_of('!'));
            }
        }
    }

    f.close();
}

CMetaInterpreter::~CMetaInterpreter() = default;

const std::array<u32, 4>& CMetaInterpreter::GetBanks() {
    return banks;
}

u16 CMetaInterpreter::GetChannelFlags() {
    return channelFlags;
}

u8 CMetaInterpreter::GetVolume() {
    return volume;
}

const std::string& CMetaInterpreter::GetCategory() {
    return category;
}
