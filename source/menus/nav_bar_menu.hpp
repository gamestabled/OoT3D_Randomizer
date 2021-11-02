#pragma once

#include "../lib/ui.hpp"

class NavBarMenu : public UI::Element {
public:
    NavBarMenu(int x, int y) : UI::Element(x, y) {}

    void setNavBarDimensions(int buttonsPerRow);

    void setCurrentChoice(int i) {
        for (auto button : buttons) {
            button->setColor(UI::BACKGROUND_COLOR);
        }
        currentChoice = i;
        buttons[i]->setColor(0xFFCC0000);
    }

    void addNavBarOption(UI::Button* navButton, UI::Element* element) {
        buttons.push_back(navButton);
        navButton->setParent(this);
        navButton->setEvent(setCurrentChoiceGen(buttons.size() - 1));

        elements.push_back(element);
        element->setParent(this);
    }

    void update(const touchPosition& touchPos) override;
    void draw() const override;

    int getNavBarHeight() const {
        return topBarButtonHeight;
    }

private:
    std::function<void(UI::Button*)> setCurrentChoiceGen(int i) {
        return [i](UI::Button* button) {
            NavBarMenu* navBarMenu = dynamic_cast<NavBarMenu*>(button->getParent());

            navBarMenu->setCurrentChoice(i);
        };
    }

    const int topBarWidthInset = 10;
    int topBarButtonsPerRow = 3;
    int topBarButtonWidth = 100;
    int topBarButtonHeight = 20;

    std::vector<UI::Button*> buttons;
    std::vector<UI::Element*> elements;
    int currentChoice = 0;

};
