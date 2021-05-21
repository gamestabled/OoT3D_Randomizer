#pragma once

#include <string>

class Text {
public:
    Text() = default;
    Text(std::string english_, std::string french_, std::string spanish_)
      : english(std::move(english_)),
        french(std::move(french_)),
        spanish(std::move(spanish_)) {}

    std::string GetEnglish() const {
        return english;
    }

    std::string GetFrench() const {
        if (french.length() > 0) {
            return french;
        }
        return english;
    }

    std::string GetSpanish() const {
        if (spanish.length() > 0) {
            return spanish;
        }
        return english;
    }

    Text operator+ (const Text& right) const {
        return Text{english + right.GetEnglish(), french + right.GetFrench(), spanish + right.GetSpanish()};
    }

    Text operator+ (const std::string& right) const {
        return Text{english + right, french + right, spanish + right};
    }

    bool operator==(const Text& right) const {
        return english == right.english;
    }

    bool operator!=(const Text& right) const {
        return !operator==(right);
    }

    std::string english;
    std::string french;
    std::string spanish;
};
