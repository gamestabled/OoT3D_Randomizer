#pragma once

#include <vector>
#include <string>
#include <array>

const std::string RANDOM_CHOICE_STR = "Random Choice";
const std::string RANDOM_COLOR_STR  = "Random Color";
const std::string CUSTOM_COLOR_STR  = "Custom #FFFFFF";
                                             /*--------------------------------------------------*/
const std::string RANDOM_CHOICE_DESC = "A random color from the list of colors will be\nchosen";
const std::string RANDOM_COLOR_DESC  = "A completely random color will be chosen";
const std::string CUSTOM_COLOR_DESC  = "Press A and type in a custom 6 digit hex color.";

typedef enum {
  RANDOM_CHOICE,
  RANDOM_COLOR,
  CUSTOM_COLOR,
  NON_COLOR_COUNT,
} CosmeticSettings;

typedef struct {
  float r;
  float g;
  float b;
  float a;
} Color_RGB;

namespace Cosmetics {

  extern bool ValidHexString(std::string hexStr);
  extern Color_RGB HexStrToColorRGB(std::string hexStr);
  extern std::string CustomColorOptionText(std::string color);
  extern std::string GetCustomColor(std::string str);
  extern std::string RandomColor();

  extern const std::array<std::string, 13> gauntletColors;
  extern std::vector<std::string> gauntletOptions;
  extern std::vector<std::string_view> gauntletDescriptions;
} //namespace Cosmetics
