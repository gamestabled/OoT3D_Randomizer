#pragma once

#include <3ds.h>
#include <string>
#include <vector>

#include "text.hpp"
#include "random.hpp"
#include "settings.hpp"

const std::string NONE = "";

enum class HintType {
  Trial,
  Always,
  Woth, //Way of the Hero
  Barren,
  Entrance,
  Sometimes,
  Random,
  Item,
  Song,
  Overworld,
  Dungeon,
  Junk,
  NamedItem,
  MaxCount,
};

struct HintDistributionSetting {
  HintType type;
  u8 order;
  size_t weight;
  u8 fixed;
  u8 copies;
};

struct HintSetting {
  u8 dungeonsWothLimit;
  u8 dungeonsBarrenLimit;
  bool namedItemsRequired;
  HintDistributionSetting distTable[static_cast<int>(HintType::MaxCount)];
};

const HintSetting uselessHints = {
  .dungeonsWothLimit = 2,
  .dungeonsBarrenLimit = 1,
  .namedItemsRequired = false,
  .distTable = {
    {.type = HintType::Trial,     .order =  1, .weight =  0, .fixed = 0, .copies = 0},
    {.type = HintType::Always,    .order =  2, .weight =  0, .fixed = 0, .copies = 0},
    {.type = HintType::Woth,      .order =  3, .weight =  0, .fixed = 0, .copies = 0},
    {.type = HintType::Barren,    .order =  4, .weight =  0, .fixed = 0, .copies = 0},
    {.type = HintType::Entrance,  .order =  5, .weight =  0, .fixed = 0, .copies = 0},
    {.type = HintType::Sometimes, .order =  6, .weight =  0, .fixed = 0, .copies = 0},
    {.type = HintType::Random,    .order =  7, .weight =  0, .fixed = 0, .copies = 0},
    {.type = HintType::Item,      .order =  8, .weight =  0, .fixed = 0, .copies = 0},
    {.type = HintType::Song,      .order =  9, .weight =  0, .fixed = 0, .copies = 0},
    {.type = HintType::Overworld, .order = 10, .weight =  0, .fixed = 0, .copies = 0},
    {.type = HintType::Dungeon,   .order = 11, .weight =  0, .fixed = 0, .copies = 0},
    {.type = HintType::Junk,      .order = 12, .weight = 99, .fixed = 0, .copies = 0},
    {.type = HintType::NamedItem, .order = 13, .weight =  0, .fixed = 0, .copies = 0},
  },
};

const HintSetting balancedHints = {
  .dungeonsWothLimit = 2,
  .dungeonsBarrenLimit = 1,
  .namedItemsRequired = true,
  .distTable = {
    {.type = HintType::Trial,     .order =  1, .weight =  0, .fixed = 0, .copies = 1},
    {.type = HintType::Always,    .order =  2, .weight =  0, .fixed = 0, .copies = 1},
    {.type = HintType::Woth,      .order =  3, .weight =  7, .fixed = 0, .copies = 1},
    {.type = HintType::Barren,    .order =  4, .weight =  4, .fixed = 0, .copies = 1},
    {.type = HintType::Entrance,  .order =  5, .weight =  6, .fixed = 0, .copies = 1},
    {.type = HintType::Sometimes, .order =  6, .weight =  0, .fixed = 0, .copies = 1},
    {.type = HintType::Random,    .order =  7, .weight = 12, .fixed = 0, .copies = 1},
    {.type = HintType::Item,      .order =  8, .weight = 10, .fixed = 0, .copies = 1},
    {.type = HintType::Song,      .order =  9, .weight =  2, .fixed = 0, .copies = 1},
    {.type = HintType::Overworld, .order = 10, .weight =  4, .fixed = 0, .copies = 1},
    {.type = HintType::Dungeon,   .order = 11, .weight =  3, .fixed = 0, .copies = 1},
    {.type = HintType::Junk,      .order = 12, .weight =  6, .fixed = 0, .copies = 1},
    {.type = HintType::NamedItem, .order = 13, .weight =  0, .fixed = 0, .copies = 1},
  },
};

const HintSetting strongHints = {
  .dungeonsWothLimit = 2,
  .dungeonsBarrenLimit = 1,
  .namedItemsRequired = true,
  .distTable = {
    {.type = HintType::Trial,     .order =  1, .weight =  0, .fixed = 0, .copies = 1},
    {.type = HintType::Always,    .order =  2, .weight =  0, .fixed = 0, .copies = 2},
    {.type = HintType::Woth,      .order =  3, .weight = 12, .fixed = 0, .copies = 2},
    {.type = HintType::Barren,    .order =  4, .weight = 12, .fixed = 0, .copies = 1},
    {.type = HintType::Entrance,  .order =  5, .weight =  4, .fixed = 0, .copies = 1},
    {.type = HintType::Sometimes, .order =  6, .weight =  0, .fixed = 0, .copies = 1},
    {.type = HintType::Random,    .order =  7, .weight =  8, .fixed = 0, .copies = 1},
    {.type = HintType::Item,      .order =  8, .weight =  8, .fixed = 0, .copies = 1},
    {.type = HintType::Song,      .order =  9, .weight =  4, .fixed = 0, .copies = 1},
    {.type = HintType::Overworld, .order = 10, .weight =  6, .fixed = 0, .copies = 1},
    {.type = HintType::Dungeon,   .order = 11, .weight =  6, .fixed = 0, .copies = 1},
    {.type = HintType::Junk,      .order = 12, .weight =  0, .fixed = 0, .copies = 1},
    {.type = HintType::NamedItem, .order = 13, .weight =  0, .fixed = 0, .copies = 1},
  },
};

const HintSetting veryStrongHints = {
  .dungeonsWothLimit = 40,
  .dungeonsBarrenLimit = 40,
  .namedItemsRequired = true,
  .distTable = {
    {.type = HintType::Trial,     .order =  1, .weight =  0, .fixed = 0, .copies = 1},
    {.type = HintType::Always,    .order =  2, .weight =  0, .fixed = 0, .copies = 2},
    {.type = HintType::Woth,      .order =  3, .weight = 15, .fixed = 0, .copies = 2},
    {.type = HintType::Barren,    .order =  4, .weight = 15, .fixed = 0, .copies = 1},
    {.type = HintType::Entrance,  .order =  5, .weight = 10, .fixed = 0, .copies = 1},
    {.type = HintType::Sometimes, .order =  6, .weight =  0, .fixed = 0, .copies = 1},
    {.type = HintType::Random,    .order =  7, .weight =  0, .fixed = 0, .copies = 1},
    {.type = HintType::Item,      .order =  8, .weight =  5, .fixed = 0, .copies = 1},
    {.type = HintType::Song,      .order =  9, .weight =  2, .fixed = 0, .copies = 1},
    {.type = HintType::Overworld, .order = 10, .weight =  7, .fixed = 0, .copies = 1},
    {.type = HintType::Dungeon,   .order = 11, .weight =  7, .fixed = 0, .copies = 1},
    {.type = HintType::Junk,      .order = 12, .weight =  0, .fixed = 0, .copies = 1},
    {.type = HintType::NamedItem, .order = 13, .weight =  0, .fixed = 0, .copies = 1},
  },
};

const std::array<HintSetting, 4> hintSettingTable = {
  uselessHints,
  balancedHints,
  strongHints,
  veryStrongHints,
};

enum class HintCategory {
  Item,
  Always,
  Sometimes,
  Exclude,
  Entrance,
  Region,
  Junk,
  DungeonName,
  Boss,
  Bridge,
  GanonsBossKey,
  LACS,
  Altar,
  Validation,
  LightArrow,
  GanonLine,
};

class HintText {
public:
    explicit HintText(std::vector<Text> obscureText_, Text clearText_, HintCategory type_)
    : obscureText(std::move(obscureText_)),
      clearText(std::move(clearText_)),
      type(type_) {}

    static auto Item(std::vector<Text>&& obscureText, Text&& clearText = Text{NONE, NONE, NONE}) {
        return HintText{std::move(obscureText), std::move(clearText), HintCategory::Item};
    }

    static auto Always(std::vector<Text>&& obscureText, Text&& clearText = Text{NONE, NONE, NONE}) {
        return HintText{std::move(obscureText), std::move(clearText), HintCategory::Always};
    }

    static auto Sometimes(std::vector<Text>&& obscureText, Text&& clearText = Text{NONE, NONE, NONE}) {
        return HintText{std::move(obscureText), std::move(clearText), HintCategory::Sometimes};
    }

    static auto Exclude(std::vector<Text>&& obscureText, Text&& clearText = Text{NONE, NONE, NONE}) {
        return HintText{std::move(obscureText), std::move(clearText), HintCategory::Exclude};
    }

    static auto Entrance(std::vector<Text>&& obscureText, Text&& clearText = Text{NONE, NONE, NONE}) {
        return HintText{std::move(obscureText), std::move(clearText), HintCategory::Entrance};
    }

    static auto Region(std::vector<Text>&& obscureText, Text&& clearText = Text{NONE, NONE, NONE}) {
        return HintText{std::move(obscureText), std::move(clearText), HintCategory::Region};
    }

    static auto Junk(std::vector<Text>&& obscureText, Text&& clearText = Text{NONE, NONE, NONE}) {
        return HintText{std::move(obscureText), std::move(clearText), HintCategory::Junk};
    }

    static auto DungeonName(std::vector<Text>&& obscureText, Text&& clearText = Text{NONE, NONE, NONE}) {
        return HintText{std::move(obscureText), std::move(clearText), HintCategory::DungeonName};
    }

    static auto Boss(std::vector<Text>&& obscureText, Text&& clearText = Text{NONE, NONE, NONE}) {
        return HintText{std::move(obscureText), std::move(clearText), HintCategory::Boss};
    }

    static auto Bridge(std::vector<Text>&& obscureText, Text&& clearText = Text{NONE, NONE, NONE}) {
        return HintText{std::move(obscureText), std::move(clearText), HintCategory::Bridge};
    }

    static auto GanonsBossKey(std::vector<Text>&& obscureText, Text&& clearText = Text{NONE, NONE, NONE}) {
        return HintText{std::move(obscureText), std::move(clearText), HintCategory::GanonsBossKey};
    }

    static auto LACS(std::vector<Text>&& obscureText, Text&& clearText = Text{NONE, NONE, NONE}) {
        return HintText{std::move(obscureText), std::move(clearText), HintCategory::LACS};
    }

    static auto Altar(std::vector<Text>&& obscureText, Text&& clearText = Text{NONE, NONE, NONE}) {
        return HintText{std::move(obscureText), std::move(clearText), HintCategory::Altar};
    }

    static auto Validation(std::vector<Text>&& obscureText, Text&& clearText = Text{NONE, NONE, NONE}) {
        return HintText{std::move(obscureText), std::move(clearText), HintCategory::Validation};
    }

    static auto LightArrow(std::vector<Text>&& obscureText, Text&& clearText = Text{NONE, NONE, NONE}) {
        return HintText{std::move(obscureText), std::move(clearText), HintCategory::LightArrow};
    }

    static auto GanonLine(std::vector<Text>&& obscureText, Text&& clearText = Text{NONE, NONE, NONE}) {
        return HintText{std::move(obscureText), std::move(clearText), HintCategory::GanonLine};
    }

    Text GetObscure() {
        return RandomElement(obscureText, false);
    }

    Text GetClear() {
        if (clearText.GetEnglish() == NONE) {
            return GetObscure();
        }
        return clearText;
    }

    Text GetText() {
        if (Settings::ClearerHints) {
            return GetClear();
        }
        return GetObscure();
    }

    HintCategory GetType() const {
        return type;
    }

    bool operator==(const HintText& right) const {
        if (obscureText.size() != right.obscureText.size()) {
          return false;
        }
        for (size_t i = 0; i < obscureText.size(); i++) {
          if (obscureText[i] != right.obscureText[i]) {
            return false;
          }
        }

        return clearText == right.clearText;
    }

private:
    std::vector<Text> obscureText;
    Text clearText;
    HintCategory type;
};

extern void CreateAllHints();
