#include "labelled_toggle_option.hpp"

#include "graphics.hpp"

namespace UI {

LabelledToggleOption::LabelledToggleOption(const std::string& text_, int x_, int y_, int width_, int height_, bool* option_) : Element(x_, y_), width(width_), height(height_), text(text_),
        fullButton("", x_, y_, width_, height_, BACKGROUND_COLOR, LabelledToggleOption::toggleFromPress),
        toggleButton(x_ + width_ - (width / 4) - 14, y_ + (height_ / 6), width_ / 4, height_ * (2.0f / 3.0f)),
        option(option_) {
    fullButton.setParent(this);
}

void LabelledToggleOption::toggle() {
    toggleButton.toggle();
    if (option) {
        *option = toggleButton.isOn();
    }
}

void LabelledToggleOption::update(const touchPosition& touchPos) {
    fullButton.update(touchPos);
    toggleButton.updateSlider();
    if (option) {
        *option = toggleButton.isOn();
    }
}

void LabelledToggleOption::toggleFromPress(Button* button) {
    LabelledToggleOption* labelledToggleOption = dynamic_cast<LabelledToggleOption*>(button->getParent());

    labelledToggleOption->toggle();
}

void LabelledToggleOption::draw() const {
    fullButton.draw();
    toggleButton.draw();
    Graphics::drawText(text, pos.x + 14, pos.y + (height / 2) - 7, GFX_DEPTH_DEFAULT, 0.5f, 0xFF000000);
}
}
