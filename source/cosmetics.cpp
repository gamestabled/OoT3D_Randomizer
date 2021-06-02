#include "cosmetics.hpp"
#include "random.hpp"
#include <sstream>
#include <3ds.h>

namespace Cosmetics {

  bool ValidHexString(std::string_view hexStr) {
    return hexStr.find_first_not_of("0123456789ABCDEFabcdef") == std::string_view::npos && hexStr.length() == 6;
  }

  Color_RGB HexStrToColorRGB(const std::string& hexStr) {
    u32 hex = std::stoi(hexStr, nullptr, 16);

    return Color_RGB{
      .r = ((hex & 0xFF0000) >> 16) / 255.0f,
      .g = ((hex & 0x00FF00) >> 8)  / 255.0f,
      .b = (hex & 0x0000FF) / 255.0f,
      .a = 1.0f,
    };
  }

  std::string CustomColorOptionText(std::string_view color) {
    return std::string(CUSTOM_COLOR_STR.substr(0, CUSTOM_COLOR_STR.length() - 6)).append(color);
  }

  std::string GetCustomColor(const std::string& str) {
    return str.substr(str.length() - 6);
  }

  const std::array<std::string_view, 13> gauntletColors = {
    "FFFFFF", //Silver
    "FECF0F", //Gold
    "000006", //Black
    "025918", //Green
    "06025A", //Blue
    "600602", //Bronze
    "FF0000", //Red
    "025DB0", //Sky Blue
    "FA6A90", //Pink
    "FF00FF", //Magenta
    "D83A00", //Orange
    "5B8A06", //Lime
    "800080", //Purple
  };
  const std::array<std::string_view, 31> tunicColors = {
    "1E691B", //Kokiri Green
    "FF0000", //Goron Red
    "1818FF", //Zora Blue
    "303030", //Black
    "FFFFFF", //White
    "139ED8", //Azure Blue
    "13E9D8", //Vivid Cyan
    "FF3333", //Light Red
    "FF0044", //Fuchsia
    "FF00FF", //Purple
    "400040", //Majora Purple
    "641E7F", //Twitch Purple
    "FF0033", //Magenta
    "953080", //Violet
    "E9144A", //Persian Rose
    "E5DA32", //Dirty Yellow
    "F23BF2", //Blush Pink
    "FF2994", //Hot Pink
    "DB557F", //Rose Pink
    "FF3E00", //Orange
    "484848", //Gray
    "FF7B00", //Yellow
    "56E4FF", //Silver
    "FF794E", //Beige
    "00CA65", //Teal
    "400000", //Blood Red
    "FF2F00", //Blood Orange
    "000070", //Royal Blue
    "00D000", //NES Green
    "002518", //Dark Green
    "0F50BC", //Lumen
  };

  //Generate random hex color
  std::string RandomColor() {
    std::ostringstream color;
    color << std::hex << (rand() % 0x1000000); //use default rand to not interfere with main settings
    return color.str();
  }
} //namespace Cosmetics
