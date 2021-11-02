#include "generate_menu.hpp"
#include "../world.hpp"

GenerateMenu::TopScreenElement::TopScreenElement() :
    UI::Element(0, 0),
    mainText("Select your play method", UI::SCREEN_TOP_WIDTH / 2 - 70, 10, UI::SCREEN_TOP_WIDTH, 0xFFFF00FF),
    seedText("Current Seed: ", UI::SCREEN_TOP_WIDTH / 2 - 70, 100, UI::SCREEN_TOP_WIDTH, 0xFFFFFFFF) {
}

void GenerateMenu::TopScreenElement::draw() const {
    mainText.draw();
    seedText.draw();
}

void GenerateMenu::onClick3DSButton(UI::Button* button) {
    World::getWorld()->generateSettings.playOption = GenerateSettings::PlayOption::DSConsole;
}

void GenerateMenu::onClickCitraButton(UI::Button* button) {
    World::getWorld()->generateSettings.playOption = GenerateSettings::PlayOption::Citra;
}

void GenerateMenu::setSeed(const std::string& seed) {
    World::getWorld()->generateSettings.seed = seed;
    topScreenElement.seedText.setText("Current Seed: " + seed);
}

void GenerateMenu::onClickCustomSeedButton(UI::Button* button) {
    GenerateMenu* parent = dynamic_cast<GenerateMenu*>(button->getParent());

    parent->setSeed(UI::Util::getInput("Enter Seed"));
}

void GenerateMenu::onClickRandomSeedButton(UI::Button* button) {
    GenerateMenu* parent = dynamic_cast<GenerateMenu*>(button->getParent());

    parent->setSeed(std::to_string(rand()));
}

GenerateMenu::GenerateMenu(int x, int y) : MenuScreen(x, y),
        topScreenElement(),
        backButton("Back", 0, 204, 56, 36, UI::BACKGROUND_COLOR, [](Element*) { MenuStack::popMenuStack(); }),
        dsButton("3DS Console", 10, 10, 145, 184, UI::BACKGROUND_COLOR, onClick3DSButton),
        citraButton("Citra", 165, 10, 145, 184, UI::BACKGROUND_COLOR, onClickCitraButton),
        customSeedButton("Custom Seed", 61, 204, 127, 36, UI::BACKGROUND_COLOR, onClickCustomSeedButton),
        randomSeedButton("Random Seed", 193, 204, 127, 36, UI::BACKGROUND_COLOR, onClickRandomSeedButton) {
    dsButton.setParent(this);
    citraButton.setParent(this);
    customSeedButton.setParent(this);
    randomSeedButton.setParent(this);
}

void GenerateMenu::draw() const {
    backButton.draw();
    dsButton.draw();
    citraButton.draw();
    customSeedButton.draw();
    randomSeedButton.draw();
}

void GenerateMenu::update(const touchPosition& touchPos, u32 kDown, u32 kHeld) {
    if (kDown & KEY_B) {
        MenuStack::popMenuStack();
        return;
    }

    backButton.update(touchPos, kDown, kHeld);
    dsButton.update(touchPos);
    citraButton.update(touchPos);
    customSeedButton.update(touchPos);
    randomSeedButton.update(touchPos);
}
