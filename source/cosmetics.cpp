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
  const std::array<std::string_view, 28> tunicColors = {
    "168A0E", //Kokiri Green
    "96000E", //Goron Red
    "002A8E", //Zora Blue
    "202020", //Black
    "FFFFFF", //White
    "FF4A0A", //Orange
    "86FF23", //Yellow
    "0094B0", //Cyan
    "362076", //Indigo
    "7B0080", //Purple
    "F04F7D", //Pink
    "323232", //Dark Gray
    "E44B4B", //Salmon
    "5A1A20", //Wine Red
    "7E705B", //Beige
    "583923", //Brown
    "72602B", //Sand
    "6b7E5D", //Tea Green
    "3C5800", //Dark Green
    "6CFFF8", //Powder Blue
    "005A4B", //Teal
    "0259FF", //Sky Blue
    "33405E", //Faded Blue
    "635AD2", //Lavender
    "9C1B4B", //Magenta
    "52314F", //Mauve
    "505A59", //Silver
    "F16F16", //Gold
  };

  //Generate random hex color
  std::string RandomColor() {
    std::ostringstream color;
    color << std::hex << (rand() % 0x1000000); //use default rand to not interfere with main settings
    return color.str();
  }
} //namespace Cosmetics
