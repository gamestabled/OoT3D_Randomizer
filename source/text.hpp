#pragma once

#include <3ds.h>
#include <string>

class Text {
public:
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

private:
    std::string english;
    std::string french;
    std::string spanish;
};
