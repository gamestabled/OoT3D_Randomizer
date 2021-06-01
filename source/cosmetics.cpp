#include "cosmetics.hpp"
#include "random.hpp"
#include <sstream>
#include <3ds.h>

namespace Cosmetics {

  bool ValidHexString(std::string_view hexStr) {
    return hexStr.find_first_not_of("0123456789ABCDEFabcdef") == std::string_view::npos;
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

  //Generate random hex color
  std::string RandomColor() {
    std::ostringstream color;
    color << std::hex << (rand() % 0x1000000); //use default rand to not interfere with main settings
    return color.str();
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
  const std::vector<std::string> gauntletOptions = {
    std::string(RANDOM_CHOICE_STR),
    std::string(RANDOM_COLOR_STR),
    std::string(CUSTOM_COLOR_STR),
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
  const std::array<std::string_view, 31> tunicColors = {
    "1E691B", //Kokiri Green
    "641400", //Goron Red
    "003C64", //Zora Blue
    "303030", //Black
    "F0F0FF", //White
    "139ED8", //Azure Blue
    "13E9D8", //Vivid Cyan
    "F87C6D", //Light Red
    "FF00FF", //Fuchsia
    "953080", //Purple
    "400040", //Majora Purple
    "6441A5", //Twitch Purple
    "8A2BE2", //Purple Heart
    "FF1493", //Persian Rose
    "E0D860", //Dirty Yellow
    "F86CF8", //Blush Pink
    "FF69B4", //Hot Pink
    "FF90B3", //Rose Pink
    "E07940", //Orange
    "A0A0B0", //Gray
    "D8B060", //Gold
    "D0F0FF", //Silver
    "C0A0A0", //Beige
    "30D0B0", //Teal
    "830303", //Blood Red
    "FE4B03", //Blood Orange
    "400090", //Royal Blue
    "5090E0", //Sonic Blue
    "00D000", //NES Green
    "002518", //Dark Green
    "508CF0", //Lumen
  };
  const std::vector<std::string> tunicOptions = {
    std::string(RANDOM_CHOICE_STR),
    std::string(RANDOM_COLOR_STR),
    std::string(CUSTOM_COLOR_STR),
    "Kokiri Green",
    "Goron Red",
    "Zora Blue",    
    "Black",
    "White",
    "Azure Blue",
    "Vivid Cyan",
    "Light Red",
    "Fuchsia",
    "Purple",
    "Majora Purple",
    "Twitch Purple",
    "Purple Heart",
    "Persian Rose",
    "Dirty Yellow",
    "Blush Pink",
    "Hot Pink",
    "Rose Pink",
    "Orange",
    "Gray",
    "Gold",
    "Silver",
    "Beige",
    "Teal",
    "Blood Red",
    "Blood Orange",
    "Royal Blue",
    "Sonic Blue",
    "NES Green",
    "Dark Green",
    "Lumen",
  };
  const std::vector<std::string_view> cosmeticDescriptions = {
    RANDOM_CHOICE_DESC,
    RANDOM_COLOR_DESC,
    CUSTOM_COLOR_DESC,
    "This will only affect the color on Link's model.",
  };

} //namespace Cosmetics
