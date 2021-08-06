#pragma once

#include <3ds.h>
#include <array>
#include <string>
#include <vector>

#include "text.hpp"
#include "random.hpp"
#include "settings.hpp"

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
    using DistributionTable = std::array<HintDistributionSetting, static_cast<int>(HintType::MaxCount)>;

    u8 dungeonsWothLimit;
    u8 dungeonsBarrenLimit;
    bool namedItemsRequired;
    DistributionTable distTable;
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
    MerchantsDialogs,
};

class HintText {
public:
    HintText() = default;
    HintText(std::vector<Text> obscureText_, Text clearText_, HintCategory type_)
        : obscureText(std::move(obscureText_)),
          clearText(std::move(clearText_)),
          type(type_) {}

    static auto Item(std::vector<Text>&& obscureText, Text&& clearText = {}) {
        return HintText{std::move(obscureText), std::move(clearText), HintCategory::Item};
    }

    static auto Always(std::vector<Text>&& obscureText, Text&& clearText = {}) {
        return HintText{std::move(obscureText), std::move(clearText), HintCategory::Always};
    }

    static auto Sometimes(std::vector<Text>&& obscureText, Text&& clearText = {}) {
        return HintText{std::move(obscureText), std::move(clearText), HintCategory::Sometimes};
    }

    static auto Exclude(std::vector<Text>&& obscureText, Text&& clearText = {}) {
        return HintText{std::move(obscureText), std::move(clearText), HintCategory::Exclude};
    }

    static auto Entrance(std::vector<Text>&& obscureText, Text&& clearText = {}) {
        return HintText{std::move(obscureText), std::move(clearText), HintCategory::Entrance};
    }

    static auto Region(std::vector<Text>&& obscureText, Text&& clearText = {}) {
        return HintText{std::move(obscureText), std::move(clearText), HintCategory::Region};
    }

    static auto Junk(std::vector<Text>&& obscureText, Text&& clearText = {}) {
        return HintText{std::move(obscureText), std::move(clearText), HintCategory::Junk};
    }

    static auto DungeonName(std::vector<Text>&& obscureText, Text&& clearText = {}) {
        return HintText{std::move(obscureText), std::move(clearText), HintCategory::DungeonName};
    }

    static auto Boss(std::vector<Text>&& obscureText, Text&& clearText = {}) {
        return HintText{std::move(obscureText), std::move(clearText), HintCategory::Boss};
    }

    static auto Bridge(std::vector<Text>&& obscureText, Text&& clearText = {}) {
        return HintText{std::move(obscureText), std::move(clearText), HintCategory::Bridge};
    }

    static auto GanonsBossKey(std::vector<Text>&& obscureText, Text&& clearText = {}) {
        return HintText{std::move(obscureText), std::move(clearText), HintCategory::GanonsBossKey};
    }

    static auto LACS(std::vector<Text>&& obscureText, Text&& clearText = {}) {
        return HintText{std::move(obscureText), std::move(clearText), HintCategory::LACS};
    }

    static auto Altar(std::vector<Text>&& obscureText, Text&& clearText = {}) {
        return HintText{std::move(obscureText), std::move(clearText), HintCategory::Altar};
    }

    static auto Validation(std::vector<Text>&& obscureText, Text&& clearText = {}) {
        return HintText{std::move(obscureText), std::move(clearText), HintCategory::Validation};
    }

    static auto LightArrow(std::vector<Text>&& obscureText, Text&& clearText = {}) {
        return HintText{std::move(obscureText), std::move(clearText), HintCategory::LightArrow};
    }

    static auto GanonLine(std::vector<Text>&& obscureText, Text&& clearText = {}) {
        return HintText{std::move(obscureText), std::move(clearText), HintCategory::GanonLine};
    }

    static auto MerchantsDialogs(std::vector<Text>&& obscureText, Text&& clearText = {}) {
        return HintText{std::move(obscureText), std::move(clearText), HintCategory::MerchantsDialogs};
    }

    Text& GetObscure() {
        return RandomElement(obscureText);
    }

    const Text& GetObscure() const {
        return RandomElement(obscureText);
    }

    const Text& GetClear() const {
        if (clearText.GetEnglish().empty()) {
            return GetObscure();
        }
        return clearText;
    }

    const Text& GetText() const {
        if (Settings::ClearerHints) {
            return GetClear();
        }
        return GetObscure();
    }

    const Text GetTextCopy() const {
        if (Settings::ClearerHints) {
            return GetClear();
        }
        return GetObscure();
    }

    HintCategory GetType() const {
        return type;
    }

    bool operator==(const HintText& right) const {
        return obscureText == right.obscureText &&
               clearText == right.clearText;
    }
    bool operator!=(const HintText& right) const {
        return !operator==(right);
    }

private:
    std::vector<Text> obscureText = {};
    Text clearText;
    HintCategory type;
};

extern void CreateAllHints();
extern void CreateMerchantsHints();
