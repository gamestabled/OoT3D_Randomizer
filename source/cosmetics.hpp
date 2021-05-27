#pragma once

#include <array>
#include <string>
#include <vector>

namespace Cosmetics {
  constexpr std::string_view RANDOM_CHOICE_STR = "Random Choice";
  constexpr std::string_view RANDOM_COLOR_STR  = "Random Color";
  constexpr std::string_view CUSTOM_COLOR_STR  = "Custom #FFFFFF";
  constexpr std::string_view CUSTOM_COLOR_PREFIX = "Custom #";

  constexpr std::string_view RANDOM_CHOICE_DESC = "A random color from the list of colors will be\nchosen.";
  constexpr std::string_view RANDOM_COLOR_DESC  = "A completely random color will be chosen.";
  constexpr std::string_view CUSTOM_COLOR_DESC  = "Press A and type in a custom 6 digit hex color.";

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

  extern const std::array<std::string_view, 13> gauntletColors;
  extern const std::array<std::string_view, 31> tunicColors;

  bool ValidHexString(std::string_view hexStr);
  Color_RGB HexStrToColorRGB(const std::string& hexStr);
  std::string CustomColorOptionText(std::string_view color);
  std::string GetCustomColor(std::string_view str);
  std::string RandomColor();
} //namespace Cosmetics
