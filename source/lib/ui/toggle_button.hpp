#pragma once

#include <3ds.h>
#include <string>

#include "element.hpp"
#include "button.hpp"

namespace UI {

class ToggleButton : public Element {
public:
    ToggleButton(int x, int y, int width, int height);

    bool isOn() const {
        return on;
    }

    void toggle();
    void updateSlider();

    void update(const touchPosition& touchPos) override;
    void draw() const override;

private:
    static const uint32_t TOGGLE_GREEN = 0xFF00CC00;
    static const uint32_t TOGGLE_RED = 0xFF0000CC;

    static void toggleFromPress(Button*);

    const int width;
    const int height;

    Button fullButton;
    Button textBox;
    float slidePercent = 1.0f;
    uint32_t circleColor = TOGGLE_GREEN;
    bool on = true;
    bool displayText = true;
};
} // namespace UI
