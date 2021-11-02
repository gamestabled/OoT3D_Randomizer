#include "main_rules_menu.hpp"
#include "../world.hpp"

MainRulesMenu::TopScreenElement::TopScreenElement() :
    UI::Element(0, 0),
    mainRulesTextbox("Main Rules", UI::SCREEN_TOP_WIDTH / 2 - 30, 10, UI::SCREEN_TOP_WIDTH, 0xFFFF00FF),
    settingDescriptionTextbox("", 20, 50, UI::SCREEN_TOP_WIDTH - 40, 0xFFFF00FF),
    optionDescriptionTextbox("", 20, 100, UI::SCREEN_TOP_WIDTH - 40, 0xFFFF00FF) {
}

void MainRulesMenu::TopScreenElement::draw() const {
    mainRulesTextbox.draw();
    settingDescriptionTextbox.draw();
    optionDescriptionTextbox.draw();
}

std::function<void(UI::Button*)> pressedButtonGen(size_t i) {
    return [i](UI::Button* button) {
        MainRulesMenu* menu = dynamic_cast<MainRulesMenu*>(button->getParent());

        menu->setCurrentButton(i);
    };
}

void MainRulesMenu::updateButtonDimensions(size_t pressedButtonIndex) {
    static const int buttonsXBegin = 59;
    static const int pressedButtonY = 197;
    static const int unpressedButtonY = 205;
    static const int pressedButtonWidth = 74;
    static const int pressedButtonHeight = 43;
    static const int unpressedButtonWidth = 56;
    static const int unpressedButtonHeight = 35;
    static const int spaceBetweenButtons = 2;

    int  xOffset = 0;

    for (size_t i = 0; i < buttons.size(); i++) {
        if (i == pressedButtonIndex) {
            buttons[i]->setPosition(buttonsXBegin + xOffset, pressedButtonY);
            buttons[i]->setSize(pressedButtonWidth, pressedButtonHeight);
            buttons[i]->setHovered();
            xOffset += (pressedButtonWidth + spaceBetweenButtons);
        } else {
            buttons[i]->setPosition(buttonsXBegin + xOffset, unpressedButtonY);
            buttons[i]->setSize(unpressedButtonWidth, unpressedButtonHeight);
            buttons[i]->unsetHovered();
            xOffset += (unpressedButtonWidth + spaceBetweenButtons);
        }
    }
}

void MainRulesMenu::setCurrentButton(size_t i) {
    currentButtonIndex = i;
    updateButtonDimensions(i);
}

MainRulesMenu::MainRulesMenu(int x, int y) : MenuScreen(x, y),
        // topScreenTextBox("howdy its the main rules menu", 60, 90, 30, 0xFFFF00FF),
        topScreenElement(),
        backButton("Back", 0, 204, 56, 36, UI::BACKGROUND_COLOR, [](Element*) { MenuStack::popMenuStack(); }),

        openButton("Open", 0, 0, 0, 0, UI::BACKGROUND_COLOR, nullptr),
        worldButton("World", 0, 0, 0, 0, UI::BACKGROUND_COLOR, nullptr),
        shuffleButton("Shuffle", 0, 0, 0, 0, UI::BACKGROUND_COLOR, nullptr),
        dungeonItemsButton("Dungeon", 0, 0, 0, 0, UI::BACKGROUND_COLOR, nullptr),

        mainSettings(&World::getWorld()->mainSettings),
        openSettingsGroupDisplay(12, 11, 280, 20, &mainSettings->openSettings),
        worldSettingsGroupDisplay(12, 11, 280, 20, &mainSettings->worldSettings),
        shuffleSettingsGroupDisplay(12, 11, 280, 20, &mainSettings->shuffleSettings),
        dungeonItemsSettingsGroupDisplay(12, 11, 280, 20, &mainSettings->dungeonSettings) {

    buttons.push_back(&openButton);
    buttons.push_back(&worldButton);
    buttons.push_back(&shuffleButton);
    buttons.push_back(&dungeonItemsButton);

    settingsGroupDisplays.push_back(&openSettingsGroupDisplay);
    settingsGroupDisplays.push_back(&worldSettingsGroupDisplay);
    settingsGroupDisplays.push_back(&shuffleSettingsGroupDisplay);
    settingsGroupDisplays.push_back(&dungeonItemsSettingsGroupDisplay);

    for (size_t i = 0; i < buttons.size(); i++) {
        buttons[i]->setParent(this);
        buttons[i]->setEvent(pressedButtonGen(i));
    }

    setCurrentButton(0);
}

void MainRulesMenu::draw() const {
    backButton.draw();
    
    for (auto button : buttons) {
        button->draw();
    }

    settingsGroupDisplays[currentButtonIndex]->draw();
}

void MainRulesMenu::update(const touchPosition& touchPos, u32 kDown, u32 kHeld) {
    if (kDown & KEY_B) {
        MenuStack::popMenuStack();
        return;
    }

    if (kDown & KEY_R) {
        currentButtonIndex++;
        if (currentButtonIndex >= (int)buttons.size()) {
            currentButtonIndex = 0;
        }
        updateButtonDimensions(currentButtonIndex);
    } else if (kDown & KEY_L) {
        currentButtonIndex--;
        if (currentButtonIndex < 0) {
            currentButtonIndex = buttons.size() - 1;
        }
        updateButtonDimensions(currentButtonIndex);
    }

    backButton.update(touchPos, kDown, kHeld);

    for (auto button : buttons) {
        button->update(touchPos, kDown, kHeld);
    }

    topScreenElement.settingDescriptionTextbox.setText(settingsGroupDisplays[currentButtonIndex]->getCurrentSettingDescription());
    topScreenElement.optionDescriptionTextbox.setText(settingsGroupDisplays[currentButtonIndex]->getCurrentOptionDescription());

    settingsGroupDisplays[currentButtonIndex]->update(touchPos, kDown, kHeld);
}
