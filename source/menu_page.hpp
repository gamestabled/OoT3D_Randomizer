#pragma once

#include <string>
#include <vector>

#include "lib/ui.hpp"

class MenuOption : public UI::Element {
public:
    MenuOption() : UI::Element(40, 40), button("test", 40, 40, 100, 50, 0xFF00CCCC, nullptr) {}

    void hide() {
        hidden = true;
    }

    void unhide() {
        hidden = false;
    }

    bool isHidden() {
        return hidden;
    }

    void update(const touchPosition& touchPos) override {
        button.update(touchPos);
    }

    void draw() const override {
        button.draw();
    }

private:
    bool hidden = false;
    UI::Button button;
};

class MenuPage : public UI::Element {
public:
    MenuPage(const std::string& title_) : UI::Element(0, 0), titleButton(title_, 0, 0, 320, 30, 0, nullptr) {}

    void addOption(MenuOption* option) {
        options.push_back(option);
    }

    void update(const touchPosition& touchPos) override {
        for (auto option : options) {
            if (!option->isHidden()) {
                option->update(touchPos);
            }
        }
    }

    void draw() const override {
        titleButton.draw();
        for (auto option : options) {
            if (!option->isHidden()) {
                option->draw();
            }
        }
    }

private:
    int selectedIndex;
    UI::Button titleButton;
    std::vector<MenuOption*> options;
};
