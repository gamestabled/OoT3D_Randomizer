#pragma once

#include <3ds.h>
#include <string>

#include "element.hpp"
#include "button.hpp"
#include "toggle_button.hpp"

namespace UI {

class LabelledToggleOption : public Element {
public:
    LabelledToggleOption(const std::string& text, int x, int y, int width, int height, bool* option);

    bool isOn() const {
        return toggleButton.isOn();
    }

    void toggle();

    void update(const touchPosition& touchPos) override;
    void draw() const override;

private:
    static const uint32_t BACKGROUND_COLOR = 0xFFCCCCCC;

    static void toggleFromPress(Button*);

    const int width;
    const int height;

    std::string text;
    Button fullButton;
    ToggleButton toggleButton;
    bool* option;
};
} // namespace UI
