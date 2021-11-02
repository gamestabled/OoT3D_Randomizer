#pragma once

#include "../lib/ui.hpp"
#include "nav_bar_menu.hpp"
#include "main_rules_menu.hpp"
#include "generate_menu.hpp"
#include "menu_screen.hpp"

class MainMenu : public MenuScreen {
public:
    MainMenu(int x, int y);

    void update(const touchPosition& touchPos, u32 kDown, u32 kHeld) override;
    void draw() const override;

    UI::Element* getTopScreenElement() override {
        return &topScreenTextBox;
    }

private:
    const int xIndent = 20;
    const int yIndent = 20;
    const int buttonWidth = 140;
    const int buttonHeight = 50;

    std::function<void(UI::Button*)> setMenuScreenGen(MenuScreen* subMenu) {
        return [subMenu](UI::Button* button) {
            MenuStack::pushToMenuStack(subMenu);
        };
    }

    void addSubMenuOtion(UI::Button* button, MenuScreen* subMenu);

    UI::Textbox topScreenTextBox;

    MainRulesMenu mainRulesMenu;
    GenerateMenu generateMenu;

    UI::Button MainRulesButton;
    UI::Button DetailedLogicButton;
    UI::Button StartingInventoryButton;
    UI::Button otherButton;
    UI::Button cosmeticsButton;
    UI::Button presetsButton;
    std::vector<UI::Button*> buttons;

    UI::Button generateButton;

    int hoveredButton = -1;
};
