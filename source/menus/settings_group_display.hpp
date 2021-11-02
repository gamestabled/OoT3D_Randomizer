#pragma once

#include "../lib/ui.hpp"
#include "../settings/setting.hpp"

class SettingsGroupDisplay;

class SettingDisplay : public UI::Element {
public:
    friend SettingsGroupDisplay;

    SettingDisplay(int x, int y, int width, int height, Setting* setting, int settingIndex);

    void update(const touchPosition& touchPos, u32 kDown, u32 kHeld) override;
    void draw() const override;

    static void onChangeButtonPress(UI::Button* button);
    static void onNameButtonPress(UI::Button* button);

    void setHovered() {
        hovered = true;
    }

    void unsetHovered() {
        hovered = false;
    }
private:
    void refreshOptionText();

    Setting* setting;
    UI::Button nameButton;
    UI::Button changeOptionButton;

    int settingIndex;
    bool hovered = false;
};

class SettingsGroupDisplay : public UI::Element {
public:
    SettingsGroupDisplay(int x, int y, int width, int height, SettingsGroup* settingsGroup);
    ~SettingsGroupDisplay();

    void update(const touchPosition& touchPos, u32 kDown, u32 kHeld) override;
    void draw() const override;

    void makeSettingDisplayHovered(SettingDisplay* settingDisplay);
    std::string& getCurrentSettingDescription() const;
    std::string& getCurrentOptionDescription() const;

private:
    int numSettingsNotHidden();
    void updateSettingDisplayPositions();

    static const int numSettingsToDisplay = 8;

    SettingsGroup* settingsGroup;
    std::vector<SettingDisplay*> settingDisplays;

    UI::Scrollbar scrollbar;

    int indexAtTopOfScreen = 0;
    int indexAtBottomOfScreen = 0;
    int hoveredSetting = 0;
};
