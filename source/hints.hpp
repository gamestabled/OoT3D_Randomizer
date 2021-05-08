#pragma once

#include <3ds.h>
#include <string>
#include <vector>

#include "text.hpp"
#include "random.hpp"

const std::string NONE = "";

enum class HintType {
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
    explicit HintText(std::vector<Text> obscureText_, Text clearText_, HintType type_)
    : obscureText(std::move(obscureText_)),
      clearText(std::move(clearText_)),
      type(type_) {}

    static auto Item(std::vector<Text>&& obscureText, Text&& clearText = Text{NONE, NONE, NONE}) {
        return HintText{std::move(obscureText), std::move(clearText), HintType::Item};
    }

    static auto Always(std::vector<Text>&& obscureText, Text&& clearText = Text{NONE, NONE, NONE}) {
        return HintText{std::move(obscureText), std::move(clearText), HintType::Always};
    }

    static auto Sometimes(std::vector<Text>&& obscureText, Text&& clearText = Text{NONE, NONE, NONE}) {
        return HintText{std::move(obscureText), std::move(clearText), HintType::Sometimes};
    }

    static auto Exclude(std::vector<Text>&& obscureText, Text&& clearText = Text{NONE, NONE, NONE}) {
        return HintText{std::move(obscureText), std::move(clearText), HintType::Exclude};
    }

    static auto Entrance(std::vector<Text>&& obscureText, Text&& clearText = Text{NONE, NONE, NONE}) {
        return HintText{std::move(obscureText), std::move(clearText), HintType::Entrance};
    }

    static auto Region(std::vector<Text>&& obscureText, Text&& clearText = Text{NONE, NONE, NONE}) {
        return HintText{std::move(obscureText), std::move(clearText), HintType::Region};
    }

    static auto Junk(std::vector<Text>&& obscureText, Text&& clearText = Text{NONE, NONE, NONE}) {
        return HintText{std::move(obscureText), std::move(clearText), HintType::Junk};
    }

    static auto DungeonName(std::vector<Text>&& obscureText, Text&& clearText = Text{NONE, NONE, NONE}) {
        return HintText{std::move(obscureText), std::move(clearText), HintType::DungeonName};
    }

    static auto Boss(std::vector<Text>&& obscureText, Text&& clearText = Text{NONE, NONE, NONE}) {
        return HintText{std::move(obscureText), std::move(clearText), HintType::Boss};
    }

    static auto Bridge(std::vector<Text>&& obscureText, Text&& clearText = Text{NONE, NONE, NONE}) {
        return HintText{std::move(obscureText), std::move(clearText), HintType::Bridge};
    }

    static auto GanonsBossKey(std::vector<Text>&& obscureText, Text&& clearText = Text{NONE, NONE, NONE}) {
        return HintText{std::move(obscureText), std::move(clearText), HintType::GanonsBossKey};
    }

    static auto LACS(std::vector<Text>&& obscureText, Text&& clearText = Text{NONE, NONE, NONE}) {
        return HintText{std::move(obscureText), std::move(clearText), HintType::LACS};
    }

    static auto Altar(std::vector<Text>&& obscureText, Text&& clearText = Text{NONE, NONE, NONE}) {
        return HintText{std::move(obscureText), std::move(clearText), HintType::Altar};
    }

    static auto Validation(std::vector<Text>&& obscureText, Text&& clearText = Text{NONE, NONE, NONE}) {
        return HintText{std::move(obscureText), std::move(clearText), HintType::Validation};
    }

    static auto LightArrow(std::vector<Text>&& obscureText, Text&& clearText = Text{NONE, NONE, NONE}) {
        return HintText{std::move(obscureText), std::move(clearText), HintType::LightArrow};
    }

    static auto GanonLine(std::vector<Text>&& obscureText, Text&& clearText = Text{NONE, NONE, NONE}) {
        return HintText{std::move(obscureText), std::move(clearText), HintType::GanonLine};
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

    HintType GetType() const {
        return type;
    }

private:
    std::vector<Text> obscureText;
    Text clearText;
    HintType type;
};
