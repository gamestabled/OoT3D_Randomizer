#include "utils.hpp"

std::string SanitizedString(std::string s) {
    // Remove line breaks
    s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());

    // Remove consecutive spaces
    while (s.find("  ") != std::string::npos) {
        s.erase(s.find("  "), 1);
    }

    return s;
}
