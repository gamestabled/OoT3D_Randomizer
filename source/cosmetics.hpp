#pragma once

#include <array>
#include <string>
#include <vector>

namespace Cosmetics {
  const std::string RANDOM_CHOICE_STR = "Random Choice";
  const std::string RANDOM_COLOR_STR  = "Random Color";
  const std::string CUSTOM_COLOR_STR  = "Custom #FFFFFF";
  const std::string CUSTOM_COLOR_PREFIX = "Custom #";
                                        /*--------------------------------------------------*/
  const std::string RANDOM_CHOICE_DESC = "A random color from the list of colors will be\nchosen.";
  const std::string RANDOM_COLOR_DESC  = "A completely random color will be chosen.";
  const std::string CUSTOM_COLOR_DESC  = "Press A and type in a custom 6 digit hex color.";

  enum CosmeticSettings {
    RANDOM_CHOICE,
    RANDOM_COLOR,
    CUSTOM_COLOR,
    NON_COLOR_COUNT,
  };

  struct Color_RGB {
    float r;
    float g;
    float b;
    float a;
  };

  extern const std::array<std::string, 13> gauntletColors;
  extern std::vector<std::string> gauntletOptions;
  extern std::vector<std::string_view> cosmeticDescriptions;

  bool ValidHexString(std::string hexStr);
  Color_RGB HexStrToColorRGB(std::string hexStr);
  std::string CustomColorOptionText(std::string color);
  std::string GetCustomColor(std::string str);
  std::string RandomColor();
} //namespace Cosmetics
