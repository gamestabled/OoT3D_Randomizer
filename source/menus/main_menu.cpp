#include "main_menu.hpp"
#include "generate_menu.hpp"

MainMenu::MainMenu(int x, int y) : MenuScreen(x, y),
        topScreenTextBox("Main menu! OoT3DR baybe! putting a whole bunch of crap in here so i can test the text wrapping! yyyyyyyyyy oqnwoiwn", 30, 30, 200, 0xFFFFFFFF),
        mainRulesMenu(pos.x, pos.y),
        generateMenu(pos.x, pos.y),

        MainRulesButton("Main", xIndent, yIndent, buttonWidth, buttonHeight, UI::BACKGROUND_COLOR, setMenuScreenGen(&mainRulesMenu)),
        DetailedLogicButton("Logic", xIndent + buttonWidth, yIndent, buttonWidth, buttonHeight, UI::BACKGROUND_COLOR, nullptr),
        StartingInventoryButton("Inventory", xIndent, yIndent + buttonHeight, buttonWidth, buttonHeight, UI::BACKGROUND_COLOR, nullptr),
        otherButton("Other", xIndent + buttonWidth, yIndent + buttonHeight, buttonWidth, buttonHeight, UI::BACKGROUND_COLOR, nullptr),
        cosmeticsButton("Cosmetics", xIndent, yIndent + 2 * buttonHeight, buttonWidth, buttonHeight, UI::BACKGROUND_COLOR, nullptr),
        presetsButton("Presets", xIndent + buttonWidth, yIndent + 2 * buttonHeight, buttonWidth, buttonHeight, UI::BACKGROUND_COLOR, nullptr),

        generateButton("Generate Seed", 10, yIndent + 3 * buttonHeight, 300, buttonHeight, UI::BACKGROUND_COLOR, setMenuScreenGen(&generateMenu)) {

    buttons.push_back(&MainRulesButton);
    buttons.push_back(&DetailedLogicButton);
    buttons.push_back(&StartingInventoryButton);
    buttons.push_back(&otherButton);
    buttons.push_back(&cosmeticsButton);
    buttons.push_back(&presetsButton);

    buttons.push_back(&generateButton);
}

void MainMenu::draw() const {
    for (auto button : buttons) {
        button->draw();
    }
}

void MainMenu::update(const touchPosition& touchPos, u32 kDown, u32 kHeld) {
    if ((hoveredButton < 0) && (kDown & (KEY_DOWN | KEY_UP | KEY_LEFT | KEY_RIGHT))) {
        hoveredButton = 0;
    } else {
        if (kDown & KEY_DOWN) {
            hoveredButton += 2;
        } else if (kDown & KEY_UP) {
            hoveredButton -= 2;
        } else if (kDown & KEY_RIGHT) {
            hoveredButton += 1;
        } else if (kDown & KEY_LEFT) {
            hoveredButton -= 1;
        }

        if (hoveredButton < 0) {
            hoveredButton = 0;
        } else if (hoveredButton >= (int)buttons.size()) {
            hoveredButton = buttons.size() - 1;
        }
    }

    for (int i = 0; i < (int)buttons.size(); i++) {
        if (i == hoveredButton) {
            buttons[i]->setHovered();
        } else {
            buttons[i]->unsetHovered();
        }
        buttons[i]->update(touchPos, kDown, kHeld);
    }
}
