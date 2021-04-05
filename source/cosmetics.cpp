#include "cosmetics.hpp"
#include "random.hpp"
#include <sstream>
#include <3ds.h>

namespace Cosmetics {

  bool ValidHexString(std::string hexStr) {
    return hexStr.find_first_not_of("0123456789ABCDEFabcdef") == std::string::npos;
  }

  Color_RGB HexStrToColorRGB(std::string hexStr) {
    u32 hex = std::stoi(hexStr, nullptr, 16);

    return Color_RGB{
      .r = ((hex & 0xFF0000) >> 16) / 255.0f,
      .g = ((hex & 0x00FF00) >> 8)  / 255.0f,
      .b = (hex & 0x0000FF) / 255.0f,
      .a = 1.0f,
    };
  }

  std::string CustomColorOptionText(std::string color) {
    return CUSTOM_COLOR_STR.substr(0, CUSTOM_COLOR_STR.length() - 6) + color;
  }

  std::string GetCustomColor(std::string str) {
    return str.substr(str.length() - 6);
  }

  //Generate random hex color
  std::string RandomColor() {
    std::stringstream color;
    color << std::hex << (rand() % 0x1000000); //use default rand to not interfere with main settings
    return color.str();
  }

  const std::array<std::string, 13> gauntletColors = {
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
  std::vector<std::string> gauntletOptions = {
    RANDOM_CHOICE_STR,
    RANDOM_COLOR_STR,
    CUSTOM_COLOR_STR,
    "Silver",
    "Gold",
    "Black",
    "Green",
    "Blue",
    "Bronze",
    "Red",
    "Sky Blue",
    "Pink",
    "Magenta",
    "Orange",
    "Lime",
    "Purple",
  };
  std::vector<std::string_view> cosmeticDescriptions = {
    RANDOM_CHOICE_DESC,
    RANDOM_COLOR_DESC,
    CUSTOM_COLOR_DESC,
    "",
  };

} //namespace Cosmetics
