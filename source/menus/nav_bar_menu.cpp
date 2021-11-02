#include "nav_bar_menu.hpp"

void NavBarMenu::draw() const {
    for (auto button : buttons) {
        button->draw();
    }
    elements[currentChoice]->draw();
}

void NavBarMenu::update(const touchPosition& touchPos) {
    for (auto button : buttons) {
        button->update(touchPos);
    }
    elements[currentChoice]->update(touchPos);
}

void NavBarMenu::setNavBarDimensions(int buttonsPerRow) {
    topBarButtonsPerRow = buttonsPerRow;
    topBarButtonWidth = (UI::SCREEN_BOT_WIDTH - (2 * topBarWidthInset)) / buttonsPerRow;
    for (size_t i = 0; i < buttons.size(); i++) {
        buttons[i]->setPosition(pos.x + topBarWidthInset + topBarButtonWidth * (i % buttonsPerRow), pos.y + topBarButtonHeight * (i / buttonsPerRow));
        buttons[i]->setSize(topBarButtonWidth, topBarButtonHeight);
    }
}
