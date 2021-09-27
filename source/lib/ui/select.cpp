#include <3ds.h>

#include "select.hpp"

#include "graphics.hpp"

namespace UI {

std::function<void(Button*)> optionButtonFunction(int i) {
    return [i](Button* button) {
        Select* select = dynamic_cast<Select*>(button->getParent());

        select->setCurrentOption(i);
    };
}

Select::Select(const std::vector<std::string> options_, int x_, int y_, int width_, int height_, int* affectedValue_) : Element(x_, y_), width(width_), height(height_), options(options_),
        mainButton("", x_, y_, width_, height_, SELECTED_COLOR, Select::toggleOpenFromPress),
        affectedValue(affectedValue_) {
    mainButton.setParent(this);
    if (options.size() == 0) {
        options.push_back("");
    }
    for (size_t i = 0; i < options.size(); i++) {
        optionButtons.push_back(Button(options[i], pos.x, pos.y + height * (1 + i), width, height, BACKGROUND_COLOR, optionButtonFunction(i)));
        optionButtons[i].setParent(this);
    }
    setCurrentOption(0);
}

void Select::setCurrentOption(size_t option) {
    currentOption = option;
    mainButton.setText(options[currentOption]);
    for (size_t i = 0; i < options.size(); i++) {
        if (i == currentOption) {
            optionButtons[i].setColor(SELECTED_COLOR);
        } else {
            optionButtons[i].setColor(BACKGROUND_COLOR);
        }
    }
}

void Select::open() {
    isOpen = true;
    if (openListener != nullptr) {
        openListener->signalOpen(this);
    }
}

void Select::close() {
    isOpen = false;
    if (openListener != nullptr) {
        openListener->signalClose(this);
    }
}

void Select::toggleOpen() {
    if (isOpen) {
        close();
    } else {
        open();
    }
}

void Select::toggleOpenFromPress(Button* button) {
    Select* select = dynamic_cast<Select*>(button->getParent());

    select->toggleOpen();
}

void Select::update(const touchPosition& touchPos) {
    mainButton.update(touchPos);
    if (isOpen) {
        for (auto& optionButton : optionButtons) {
            optionButton.update(touchPos);
        }
    }

    if (affectedValue) {
        *affectedValue = currentOption;
    }
}

void Select::draw() const {
    mainButton.draw();
    float triangleX = (float)pos.x + 0.8f * width;
    float triangleY = (float)pos.y + 0.33f * height;
    float triangleW = 0.1f * width;
    float triangleH = 0.33f * height;
    C2D_DrawTriangle(triangleX, triangleY, BACKGROUND_COLOR, triangleX + triangleW, triangleY, BACKGROUND_COLOR, triangleX + 0.5f * triangleW, triangleY + triangleH, BACKGROUND_COLOR, 0.5f);
    if (isOpen) {
        for (auto& optionButton : optionButtons) {
            optionButton.draw();
        }
    }
}
}
