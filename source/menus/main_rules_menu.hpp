#pragma once

#include "../lib/ui.hpp"
#include "nav_bar_menu.hpp"
#include "menu_screen.hpp"
#include "settings_group_display.hpp"
#include "../settings/main_settings.hpp"

class MainRulesMenu : public MenuScreen {
public:
    MainRulesMenu(int x, int y);

    void update(const touchPosition& touchPos, u32 kDown, u32 kHeld) override;
    void draw() const override;

    void setCurrentButton(size_t pressedButtonIndex);

    UI::Element* getTopScreenElement() {
        return &topScreenElement;
    }

    class TopScreenElement : public UI::Element {
    public:
        friend MainRulesMenu;
        TopScreenElement();

        void draw() const override;
    private:
        UI::Textbox mainRulesTextbox;
        UI::Textbox settingDescriptionTextbox;
        UI::Textbox optionDescriptionTextbox;
    };

private:
    void updateButtonDimensions(size_t pressedButtonIndex);

    // UI::Textbox topScreenTextBox;
    TopScreenElement topScreenElement;

    UI::Button backButton;

    UI::Button openButton;
    UI::Button worldButton;
    UI::Button shuffleButton;
    UI::Button dungeonItemsButton;

    std::vector<UI::Button*> buttons;
    int currentButtonIndex;

    MainSettings* mainSettings;
    SettingsGroupDisplay openSettingsGroupDisplay;
    SettingsGroupDisplay worldSettingsGroupDisplay;
    SettingsGroupDisplay shuffleSettingsGroupDisplay;
    SettingsGroupDisplay dungeonItemsSettingsGroupDisplay;

    std::vector<SettingsGroupDisplay*> settingsGroupDisplays;
};
