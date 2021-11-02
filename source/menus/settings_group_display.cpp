#include "settings_group_display.hpp"

void SettingDisplay::onChangeButtonPress(UI::Button* button) {
    SettingDisplay* parent = dynamic_cast<SettingDisplay*>(button->getParent());

    parent->setting->setNextOption();
    parent->refreshOptionText();

    parent->onNameButtonPress(button);
}

void SettingDisplay::onNameButtonPress(UI::Button* button) {
    SettingDisplay* parent = dynamic_cast<SettingDisplay*>(button->getParent());
    SettingsGroupDisplay* groupDisplay = dynamic_cast<SettingsGroupDisplay*>(parent->getParent());

    groupDisplay->makeSettingDisplayHovered(parent);
}

void SettingDisplay::refreshOptionText() {
    changeOptionButton.setText(setting->getCurrentOptionName());
}

SettingDisplay::SettingDisplay(int x_, int y_, int width_, int height_, Setting* setting_, int settingIndex_) :
        UI::Element(x_, y_, width_, height_), setting(setting_),
        nameButton(setting_->getName(), x_, y_, 194, 20, UI::BACKGROUND_COLOR, onNameButtonPress, true),
        changeOptionButton(setting_->getCurrentOptionName(), x_ + 194, y_, 86, 20, UI::BACKGROUND_COLOR, onChangeButtonPress),
        settingIndex(settingIndex_) {
    nameButton.setParent(this);
    changeOptionButton.setParent(this);
}

void SettingDisplay::update(const touchPosition& touchPos, u32 kDown, u32 kHeld) {
    if (hovered) {
        changeOptionButton.setHovered();
    } else {
        changeOptionButton.unsetHovered();
    }

    nameButton.setPosition(pos.x, pos.y);
    changeOptionButton.setPosition(pos.x + 194, pos.y);

    if (hovered) {
        if (kDown & KEY_RIGHT) {
            setting->setNextOption();
            refreshOptionText();
        } else if (kDown & KEY_LEFT) {
            setting->setPreviousOption();
            refreshOptionText();
        }
    }

    nameButton.update(touchPos);
    changeOptionButton.update(touchPos);
}

void SettingDisplay::draw() const {
    nameButton.draw();
    changeOptionButton.draw();
}

SettingsGroupDisplay::SettingsGroupDisplay(int x_, int y_, int width_, int height_, SettingsGroup* settingsGroup_) :
        UI::Element(x_, y_, width_, height_), settingsGroup(settingsGroup_),
        scrollbar(307, 0, 13, UI::SCREEN_BOT_HEIGHT, settingsGroup_->size(), numSettingsToDisplay) {
    for (size_t i = 0; i < settingsGroup_->size(); i++) {
        settingDisplays.push_back(new SettingDisplay(x_, y_ + (i * 22), width_, height_, settingsGroup_->at(i), i));
        settingDisplays[i]->setParent(this);
    }

    scrollbar.setScrollBarSize(numSettingsNotHidden(), numSettingsToDisplay);
}

SettingsGroupDisplay::~SettingsGroupDisplay() {
    for (auto& setting : settingDisplays) {
        delete setting;
        setting = nullptr;
    }
}

int SettingsGroupDisplay::numSettingsNotHidden() {
    int count = 0;
    for (auto settingDisplay : settingDisplays) {
        if (!settingDisplay->setting->isHidden()) {
            count++;
        }
    }
    return count;
}

void SettingsGroupDisplay::updateSettingDisplayPositions() {
    if (hoveredSetting < 0) {
        return;
    }

    if (hoveredSetting < indexAtTopOfScreen) {
        indexAtTopOfScreen = hoveredSetting;
    } else if (hoveredSetting > indexAtBottomOfScreen) {
        indexAtTopOfScreen++;
        while (settingDisplays[indexAtTopOfScreen]->setting->isHidden()) {
            indexAtTopOfScreen++;
        }
    }

    int numSettingsShown = 0;

    for (int i = indexAtTopOfScreen; i < (int)settingDisplays.size() && numSettingsShown < numSettingsToDisplay; i++) {
        if (!settingDisplays[i]->setting->isHidden()) {
            settingDisplays[i]->setPosition(pos.x, pos.y + (numSettingsShown * 22));
            numSettingsShown++;
            indexAtBottomOfScreen = i;
        }
    }

    scrollbar.setScrollBarSize(numSettingsNotHidden(), numSettingsToDisplay);
    scrollbar.setScrollPercent((float)indexAtTopOfScreen / (float) (numSettingsNotHidden() - numSettingsToDisplay));
}

void SettingsGroupDisplay::makeSettingDisplayHovered(SettingDisplay* settingDisplay) {
    hoveredSetting = settingDisplay->settingIndex;
}

std::string& SettingsGroupDisplay::getCurrentSettingDescription() const {
    return settingDisplays[hoveredSetting]->setting->getDescription();
}

std::string& SettingsGroupDisplay::getCurrentOptionDescription() const {
    return settingDisplays[hoveredSetting]->setting->getCurrentOptionDescription();
}

void SettingsGroupDisplay::update(const touchPosition& touchPos, u32 kDown, u32 kHeld) {
    if (kDown & KEY_DOWN) {
        do {
            hoveredSetting++;
            if (hoveredSetting >= (int)settingDisplays.size()) {
                hoveredSetting = 0;
            }
        } while (settingDisplays[hoveredSetting]->setting->isHidden());
    } else if (kDown & KEY_UP) {
        do {
            hoveredSetting--;
            if (hoveredSetting < 0) {
                hoveredSetting = settingDisplays.size() - 1;
            }
        }
        while (settingDisplays[hoveredSetting]->setting->isHidden());
    }

    updateSettingDisplayPositions();

    int numSettingsShown = 0;

    for (int i = indexAtTopOfScreen; i < (int)settingDisplays.size() && numSettingsShown < numSettingsToDisplay; i++) {
        if (i == hoveredSetting) {
            settingDisplays[i]->setHovered();
        } else {
            settingDisplays[i]->unsetHovered();
        }

        if (!settingDisplays[i]->setting->isHidden()) {
            settingDisplays[i]->update(touchPos, kDown, kHeld);
            numSettingsShown++;
            indexAtBottomOfScreen = i;
        }
    }

    scrollbar.update(touchPos);
}

void SettingsGroupDisplay::draw() const {
    int numSettingsShown = 0;

    for (int i = indexAtTopOfScreen; i < (int)settingDisplays.size() && numSettingsShown < numSettingsToDisplay; i++) {
        if (!settingDisplays[i]->setting->isHidden()) {
            settingDisplays[i]->draw();
            numSettingsShown++;
        }
    }
    scrollbar.draw();
}
