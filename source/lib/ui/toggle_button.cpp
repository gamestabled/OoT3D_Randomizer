#include "toggle_button.hpp"

#include "graphics.hpp"

namespace UI {

ToggleButton::ToggleButton(int x_, int y_, int width_, int height_) : Element(x_, y_), width(width_), height(height_),
        fullButton("", x_, y_, width_, height_, 0xFFBBBBBB, toggleFromPress),
        textBox("On", x_ + width_ - height_, y_, height_, height_, 0x00000000, nullptr) {
    fullButton.setParent(this);
}

void ToggleButton::toggle() {
    on = !on;
    displayText = false;
}

void ToggleButton::updateSlider() {
    if (on && (slidePercent < 1.0f)) {
        slidePercent += 0.1f;
        if (slidePercent > 0.95f) {
            slidePercent = 1.0f;
            circleColor = TOGGLE_GREEN;
            textBox.setText("On");
            textBox.setPosition(pos.x + width - height, pos.y);
            displayText = true;
        }
    } else if (!on && (slidePercent > 0.0f)) {
        slidePercent -= 0.1f;
        if (slidePercent < 0.05f) {
            slidePercent = 0.0f;
            circleColor = TOGGLE_RED;
            textBox.setText("Off");
            textBox.setPosition(pos.x, pos.y);
            displayText = true;
        }
    }
}

void ToggleButton::update(const touchPosition& touchPos) {
    fullButton.update(touchPos);
    updateSlider();
}

void ToggleButton::toggleFromPress(Button* button) {
    ToggleButton* toggleButton = dynamic_cast<ToggleButton*>(button->getParent());

    toggleButton->toggle();
}

void ToggleButton::draw() const {
    C2D_DrawRectSolid(pos.x + (height / 4), pos.y + (height / 3), 0.5f, width - (height / 2), height / 3, 0xFF222222);
    C2D_DrawCircleSolid(pos.x + (height / 2) + (slidePercent * (width - height)), pos.y + (height / 2), 0.5f, height / 2, circleColor);
    if (displayText) {
        textBox.draw();
    }
}
}
