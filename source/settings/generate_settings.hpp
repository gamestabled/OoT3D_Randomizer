#pragma once

#include <string>

class GenerateSettings {
public:
    GenerateSettings();

    void update();

    enum class PlayOption {
        DSConsole,
        Citra,
    };

    PlayOption playOption = PlayOption::DSConsole;
    std::string seed;
};
