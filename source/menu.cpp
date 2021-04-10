#include <3ds.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <time.h>

#include <cstring>
#include <algorithm>

#include "menu.hpp"
#include "patch.hpp"
#include "preset.hpp"
#include "settings.hpp"
#include "cosmetics.hpp"
#include "spoiler_log.hpp"

namespace {
  bool seedChanged;
  u8 mode;
  u8 subMode;
  u16 settingIdx;
  u16 itemIdx;
  u16 subItemIdx;
  u8 menuIdx;
  u8 presetIdx;
  u8 generateIdx;
  u16 settingBound;
  u8 menuBound;
  u8 presetBound;
  u16 pastSeedLength;
  MenuItem* currentMenuItem;
  MenuItem* currentSubMenuItem;
  Option* currentSetting;
  PrintConsole topScreen, bottomScreen;
  std::vector<std::string> presetEntries;
}

void PrintTopScreen() {
  consoleSelect(&topScreen);
  consoleClear();
  printf("\x1b[2;11H%sOcarina of Time 3D Randomizer%s", CYAN, RESET);
  printf("\x1b[3;18H%sv1.1%s", CYAN, RESET);
  printf("\x1b[4;10HA/B/D-pad: Navigate Menu\n");
  printf("            Select: Exit to Homebrew Menu\n");
  printf("                 Y: New Random Seed\n");
  printf("                 X: Input Custom Seed\n");
  printf("\x1b[11;7HCurrent Seed: %s", Settings::seed.c_str());
}

void MenuInit() {

  Settings::SetDefaultSettings();

  seedChanged = false;
  mode = MAIN_MENU;
  subMode = -1;
  menuIdx = 0;
  menuBound = 0;
  settingIdx = 0;
  itemIdx = 0;
  settingBound = 0;
  presetIdx = 0;
  presetBound = 0;
  generateIdx = 0;
  pastSeedLength = Settings::seed.length();
  currentMenuItem = Settings::mainMenu[menuIdx];
  currentSetting = Settings::mainMenu[menuIdx]->settingsList->at(settingIdx);
  Settings::ForceChange(0, currentSetting);

  srand(time(NULL));
  consoleInit(GFX_TOP,    &topScreen);
  consoleInit(GFX_BOTTOM, &bottomScreen);

  consoleSelect(&topScreen);

  if (!CreatePresetDirectories()) {
    printf("\x1b[20;5Failed to create preset directories.");
    printf("\x1b[21;5Loading presets might crash.");
  }

  //If cached presets exist, load them
  LoadCachedSettings();
  LoadCachedCosmetics();

  PrintTopScreen();

  consoleSelect(&bottomScreen);
  PrintMainMenu();

}

void MenuUpdate(u32 kDown) {

  consoleSelect(&bottomScreen);
  consoleClear();

  //Check for a main menu change
  if (kDown & KEY_A && mode == MAIN_MENU) {
    mode = currentMenuItem->mode;
    ModeChangeInit();
    kDown = 0;
  } else if ((kDown & KEY_B && mode != MAIN_MENU && subMode != SUB_MENU)) {
    consoleSelect(&topScreen);
    PrintTopScreen();
    mode = MAIN_MENU;
    currentMenuItem = Settings::mainMenu[menuIdx];
  }
  //Check for a sub menu change
  else if (kDown & KEY_A && mode == SUB_MENU) {
    mode = currentMenuItem->itemsList->at(itemIdx)->mode;
    subMode = SUB_MENU;
    ModeChangeInit();
    kDown = 0;
  } else if ((kDown & KEY_B && mode != MAIN_MENU)) {
    ClearDescription();
    mode = currentMenuItem->mode;
    subMode = -1;
    ModeChangeInit();
    kDown = 0;
  }

  if (mode != GENERATE_MODE) {

    //New Random Seed
    if (kDown & KEY_Y) {
      pastSeedLength = Settings::seed.length();
      Settings::seed = std::to_string(rand());
      seedChanged = true;
    }

    //Input Custom Seed
    if (kDown & KEY_X) {
      pastSeedLength = Settings::seed.length();
      Settings::seed = GetInput("Enter Seed");
      seedChanged = true;
    }

    //Reprint seed if it changed
    if (seedChanged) {
      std::string spaces = "";
      spaces.append(pastSeedLength, ' ');
      consoleSelect(&topScreen);
      printf("\x1b[11;21H%s", spaces.c_str());
      printf("\x1b[11;21H%s", Settings::seed.c_str());
      seedChanged = false;
    }
  }

  //Print current menu (if applicable)
  consoleSelect(&bottomScreen);
  if (mode == MAIN_MENU) {
    UpdateMainMenu(kDown);
    PrintMainMenu();
    ClearDescription();
  } else if (mode == OPTION_SUB_MENU) {
    UpdateOptionSubMenu(kDown);
    PrintOptionSubMenu();
  } else if (mode == LOAD_PRESET) {
    UpdatePresetsMenu(kDown);
    PrintPresetsMenu();
  } else if (mode == DELETE_PRESET) {
    UpdatePresetsMenu(kDown);
    PrintPresetsMenu();
  } else if (mode == GENERATE_MODE) {
    UpdateGenerateMenu(kDown);
    if (mode != POST_GENERATE) {
      PrintGenerateMenu();
    }
  } else if (mode == SUB_MENU) {
    UpdateSubMenu(kDown);
    PrintSubMenu();
  }
}

void ModeChangeInit() {
  if(subMode == SUB_MENU) {
    subItemIdx = itemIdx;
  }
  if (mode == OPTION_SUB_MENU) {
    settingIdx = 0;

    //loop through until we reach an unlocked setting
    while(currentMenuItem->settingsList->at(settingIdx)->IsLocked() || currentMenuItem->settingsList->at(settingIdx)->IsHidden()) {
      settingIdx++;
    }

    currentSetting = currentMenuItem->settingsList->at(settingIdx);

  } else if (mode == SUB_MENU) {
    itemIdx = subItemIdx;
    subItemIdx = 0;
    presetIdx = 0;
    currentSubMenuItem = currentMenuItem->itemsList->at(itemIdx);
  } else if (mode == SAVE_PRESET) {
    ClearDescription();
    if (SaveSpecifiedPreset(GetInput("Preset Name").substr(0, 19), OptionCategory::Setting)) {
      printf("\x1b[24;5HPreset Saved!");
      printf("\x1b[26;5HPress B to return to the preset menu.");
    } else {
      printf("\x1b[24;5HFailed to save preset.");
      printf("\x1b[26;5HPress B to return to the preset menu.");
    }

  } else if (mode == LOAD_PRESET || mode == DELETE_PRESET) {
    presetEntries = GetSettingsPresets();

  } else if (mode == GENERATE_MODE) {

  }

}

void UpdateMainMenu(u32 kDown) {
  if ((kDown & KEY_DUP) != 0) {
    menuIdx--;
  }

  if ((kDown & KEY_DDOWN) != 0) {
    menuIdx++;
  }

  // Bounds checking
  if (menuIdx == Settings::mainMenu.size()) {
    menuIdx = 0;
  } else if (menuIdx == 0xFF) {
    menuIdx = static_cast<u8>(Settings::mainMenu.size() - 1);
  }

  currentMenuItem = Settings::mainMenu[menuIdx];
}

void UpdateCustomCosmeticColors(u32 kDown) {
  if (kDown & KEY_A) {
    if (currentSetting->GetSelectedOptionText().substr(0, 8) == CUSTOM_COLOR_PREFIX) {
      std::string newColor = GetInput("Enter a 6 digit hex color").substr(0, 6);
      if (Cosmetics::ValidHexString(newColor)) {
        currentSetting->SetSelectedOptionText(Cosmetics::CustomColorOptionText(newColor));
      }
    }
  }
}

void UpdateOptionSubMenu(u32 kDown) {
  //loop through settings until an unlocked one is reached
  do {
    if ((kDown & KEY_DUP) != 0) {
      settingIdx--;
    }

    if ((kDown & KEY_DDOWN) != 0)  {
      settingIdx++;
    }

    // Bounds checking
    if (settingIdx == currentMenuItem->settingsList->size()) {
      settingIdx = 0;
    } else if (settingIdx == 0xFFFF) {
      settingIdx = static_cast<u16>(currentMenuItem->settingsList->size() - 1);
    }

    currentSetting = currentMenuItem->settingsList->at(settingIdx);
  } while (currentSetting->IsLocked() || currentSetting->IsHidden());

  if ((kDown & KEY_DRIGHT) != 0) {
    currentSetting->NextOptionIndex();
  }
  if ((kDown & KEY_DLEFT) != 0) {
    currentSetting->PrevOptionIndex();
  }

  // Bounds checking
  currentSetting->SanitizeSelectedOptionIndex();

  currentSetting->SetVariable();
  Settings::ForceChange(kDown, currentSetting);
  UpdateCustomCosmeticColors(kDown);
}

void UpdateSubMenu(u32 kDown) {
  if ((kDown & KEY_DUP) != 0) {
    itemIdx--;
  }

  if ((kDown & KEY_DDOWN) != 0)  {
    itemIdx++;
  }

  // Bounds checking
  if (itemIdx == currentMenuItem->itemsList->size()) {
    itemIdx = 0;
  } else if (itemIdx == 0xFFFF) {
    itemIdx = static_cast<u16>(currentMenuItem->itemsList->size() - 1);
  }

  currentSubMenuItem = currentMenuItem->itemsList->at(itemIdx);
}

void UpdatePresetsMenu(u32 kDown) {
  if ((kDown & KEY_DUP) != 0) {
    presetIdx--;
  }

  if ((kDown & KEY_DDOWN) != 0) {
    presetIdx++;
  }

  // Bounds checking
  if (presetIdx == presetEntries.size()) {
    presetIdx = 0;
  } else if (presetIdx == 0xFF) {
    presetIdx = static_cast<u8>(presetEntries.size() - 1);
  }

  consoleSelect(&topScreen);
  //clear any potential message
  ClearDescription();
  if ((kDown & KEY_A) != 0 && mode == LOAD_PRESET) {
    if (LoadPreset(presetEntries[presetIdx], OptionCategory::Setting)) {
      printf("\x1b[24;5HPreset Loaded!");
    } else {
      printf("\x1b[24;5HFailed to load preset.");
    }
  } else if ((kDown & KEY_A) != 0 && mode == DELETE_PRESET) {
    if (DeletePreset(presetEntries[presetIdx], OptionCategory::Setting)) {
      presetEntries.erase(presetEntries.begin() + presetIdx);
      if(presetIdx == presetEntries.size()) { //Catch when last preset is deleted
        presetIdx--;
      }
      printf("\x1b[24;5HPreset Deleted.");
    } else {
      printf("\x1b[24;5HFailed to delete preset.");
    }
  }
}

void UpdateGenerateMenu(u32 kDown) {
  if ((kDown & KEY_DDOWN) || (kDown & KEY_DUP)) {
    if (generateIdx) {
      generateIdx = 0;
    } else {
      generateIdx = 1;
    }
  }

  if ((kDown & KEY_A) != 0) {
    Settings::PlayOption = generateIdx;
    consoleSelect(&bottomScreen);
    consoleClear();
    GenerateRandomizer();
    //This is just a dummy mode to stop the prompt from appearing again
    mode = POST_GENERATE;
  }
}

void PrintMainMenu() {
  printf("\x1b[0;%dHMain Settings Menu", (BOTTOM_WIDTH/2) - 9);

  for (u8 i = 0; i < MAX_SETTINGS_ON_SCREEN; i++) {
    if (i + menuBound >= Settings::mainMenu.size()) break;

    MenuItem* menu = Settings::mainMenu[i + menuBound];

    u8 row = 3 + i;
    //make the current menu green
    if (menuIdx == i + menuBound) {
      printf("\x1b[%d;%dH%s>",  row,  2, GREEN);
      printf("\x1b[%d;%dH%s%s", row,  3, menu->name.c_str(), RESET);
    } else {
      printf("\x1b[%d;%dH%s",   row,  3, menu->name.c_str());
    }
  }
}

void PrintOptionSubMenu() {
  //bounds checking incase settings go off screen
  //this is complicated to account for hidden settings and there's probably a better way to do it
  u16 hiddenSettings = 0;
  u16 visibleSettings = 0;
  for (u16 i = settingBound; visibleSettings < MAX_SETTINGS_ON_SCREEN; i++) {
    if (i >= currentMenuItem->settingsList->size()) {
      break;
    }
    if (currentMenuItem->settingsList->at(i)->IsHidden()) {
      hiddenSettings++;
    } else {
      visibleSettings++;
    }
  }
  if (settingIdx >= settingBound + MAX_SETTINGS_ON_SCREEN + hiddenSettings) {
    settingBound = settingIdx;
    u8 offset = 0;
    //skip over hidden settings
    while (offset < MAX_SETTINGS_ON_SCREEN - 1) {
      settingBound--;
      if (settingBound == 0) {
        break;
      }
      offset += currentMenuItem->settingsList->at(settingBound)->IsHidden() ? 0 : 1;
    }
  } else if (settingIdx < settingBound)  {
    settingBound = settingIdx;
  }

  //print menu name
  printf("\x1b[0;%dH%s", (BOTTOM_WIDTH/2) - (currentMenuItem->name.length()/2), currentMenuItem->name.c_str());

  //keep count of hidden settings to not make blank spaces appear in the list
  hiddenSettings = 0;

  for (u8 i = 0; i - hiddenSettings < MAX_SETTINGS_ON_SCREEN; i++) {
    //break if there are no more settings to print
    if (i + settingBound >= currentMenuItem->settingsList->size()) break;

    Option* setting = currentMenuItem->settingsList->at(i + settingBound);

    u8 row = 3 + ((i - hiddenSettings) * 2);
    //make the current setting green
    if (settingIdx == i + settingBound) {
      printf("\x1b[%d;%dH%s>",   row,  1, GREEN);
      printf("\x1b[%d;%dH%s:",   row,  2, setting->GetName().data());
      printf("\x1b[%d;%dH%s%s",  row, 26, setting->GetSelectedOptionText().data(), RESET);
    //dim to make a locked setting grey
    } else if (setting->IsLocked()) {
      printf("\x1b[%d;%dH%s%s:", row,  2, DIM, setting->GetName().data());
      printf("\x1b[%d;%dH%s%s",  row, 26, setting->GetSelectedOptionText().data(), RESET);
    //don't display hidden settings
    } else if (setting->IsHidden()) {
      hiddenSettings++;
      continue;
    } else {
      printf("\x1b[%d;%dH%s:",   row,  2, setting->GetName().data());
      printf("\x1b[%d;%dH%s",    row, 26, setting->GetSelectedOptionText().data());
    }
  }

  PrintOptionDescrption();
}

void PrintSubMenu() {
  printf("\x1b[0;%dH%s Menu", (BOTTOM_WIDTH/2) - 9, currentMenuItem->name.c_str());

  for (u8 i = 0; i < MAX_SETTINGS_ON_SCREEN; i++) {
    if (i + menuBound >= currentMenuItem->itemsList->size()) break;

    u8 row = 3 + i;
    //make the current menu green
    if (itemIdx == i + menuBound) {
      printf("\x1b[%d;%dH%s>",  row,  2, GREEN);
      printf("\x1b[%d;%dH%s%s", row,  3, currentMenuItem->itemsList->at(i)->name.c_str(), RESET);
    } else {
      printf("\x1b[%d;%dH%s",   row,  3, currentMenuItem->itemsList->at(i)->name.c_str());
    }
  }
}

void PrintPresetsMenu() {
  consoleSelect(&bottomScreen);
  if (presetEntries.empty()) {
    printf("\x1b[10;4HNo Presets Detected!");
    printf("\x1b[12;4HPress B to return to the preset menu.");
    return;
  }

  if(mode == LOAD_PRESET) {
    printf("\x1b[0;%dHSelect a Preset to Load", (BOTTOM_WIDTH/2) - 7);
  } else if (mode == DELETE_PRESET) {
    printf("\x1b[0;%dHSelect a Preset to Delete", (BOTTOM_WIDTH/2) - 7);
  }

  for (u8 i = 0; i < MAX_SETTINGS_ON_SCREEN; i++) {
    if (i + presetBound >= presetEntries.size()) break;

    std::string preset = presetEntries[i];

    u8 row = 3 + (i * 2);
    //make the current preset green
    if (presetIdx == i + presetBound) {
      printf("\x1b[%d;%dH%s>",  row, 14, GREEN);
      printf("\x1b[%d;%dH%s%s", row, 15, preset.c_str(), RESET);
    } else {
      printf("\x1b[%d;%dH%s",   row, 15, preset.c_str());
    }
  }
}

void PrintGenerateMenu() {

  consoleSelect(&bottomScreen);

  printf("\x1b[3;%dHHow will you play?", (BOTTOM_WIDTH/2) - 8);
  std::vector<std::string> playOptions = {"3ds Console", "Citra Emulator"};

  for (u8 i = 0; i < playOptions.size(); i++) {

    std::string option = playOptions[i];
    u8 row = 6 + (i * 2);
    //make the current selection green
    if (generateIdx == i) {
      printf("\x1b[%d;%dH%s>",   row, 14, GREEN);
      printf("\x1b[%d;%dH%s%s",  row, 15, option.c_str(), RESET);
    } else {
      printf("\x1b[%d;%dH%s",    row, 15, option.c_str());
    }
  }
}

void ClearDescription() {
  consoleSelect(&topScreen);

  //clear the previous description
  std::string spaces = "";
  spaces.append(9 * TOP_WIDTH, ' ');
  printf("\x1b[22;0H%s", spaces.c_str());
}

void PrintOptionDescrption() {
  ClearDescription();
  std::string_view description = currentSetting->GetSelectedOptionDescription();

  printf("\x1b[22;0H%s", description.data());
}

void GenerateRandomizer() {

  consoleSelect(&topScreen);
  consoleClear();
  printf("\x1b[7;10HCaching Settings...");

  //After choosing to generate, cache chosen settings for later
  SaveCachedSettings();
  SaveCachedCosmetics();
  printf("Done");

  //if a blank seed was entered, make a random one
  if (Settings::seed.empty()) {
    Settings::seed = std::to_string(rand());
  } else if (Settings::seed.rfind("seed_testing_count", 0) == 0) {
    const int count = std::stoi(Settings::seed.substr(18), nullptr);
    Playthrough::Playthrough_Repeat(count);
    return;
  }

  //turn the settings into a string for hashing
  std::string settingsStr;
  for (MenuItem* menu : Settings::mainMenu) {
    //don't go through non-menus
    if (menu->mode != OPTION_SUB_MENU) {
      continue;
    }

    for (size_t i = 0; i < menu->settingsList->size(); i++) {
      Option* setting = menu->settingsList->at(i);
      if (setting->IsCategory(OptionCategory::Setting)) {
        settingsStr += setting->GetSelectedOptionText();
      }
    }
  }

  unsigned int finalHash = std::hash<std::string>{}(Settings::seed + settingsStr);

  int ret = Playthrough::Playthrough_Init(finalHash);
  if (ret < 0) {
    if(ret == -1) { //Failed to generate after 5 tries
      printf("\n\nFailed to generate after 5 tries.\nPress Select to exit or B to go back to the menu.\n");
      return;
    }
    else {
      printf("\n\nError %d with fill.\nPress Select to exit or B to go back to the menu.\n", ret);
      return;
    }
  }
  printf("\x1b[11;10HWriting Patch...");
  if (WritePatch()) {
    printf("Done");
    if (Settings::PlayOption == PATCH_CONSOLE) {
      printf("\x1b[13;10HQuit out using the home menu. Then\n");
      printf("\x1b[14;10Henable game patching and launch OoT3D!\n");
    } else if (Settings::PlayOption == PATCH_CITRA) {
      printf("\x1b[13;10HCopy code.ips and exheader.bin to the\n");
      printf("\x1b[14;10HOoT3D mods folder, then launch OoT3D!\n");
    }

    const auto& randomizerHash = GetRandomizerHash();
    printf("\x1b[16;10HHash:");
    for (size_t i = 0; i < randomizerHash.size(); i++) {
      printf("\x1b[%zu;11H- %s", i + 17, randomizerHash[i].c_str());
    }
  } else {
    printf("Failed\nPress Select to exit.\n");
  }
}

//opens up the 3ds software keyboard for getting user input
std::string GetInput(const char* hintText) {
  SwkbdState swkbd;
  char text[60];
  SwkbdButton button = SWKBD_BUTTON_NONE;

  swkbdInit(&swkbd, SWKBD_TYPE_WESTERN, 2, -1);
  swkbdSetValidation(&swkbd, SWKBD_NOTEMPTY_NOTBLANK, SWKBD_FILTER_AT | SWKBD_FILTER_PERCENT | SWKBD_FILTER_BACKSLASH | SWKBD_FILTER_PROFANITY, 2);
  swkbdSetFeatures(&swkbd, SWKBD_MULTILINE);
  swkbdSetHintText(&swkbd, hintText);
  swkbdSetButton(&swkbd, SWKBD_BUTTON_LEFT, "Cancel", false);

  button = swkbdInputText(&swkbd, text, sizeof(text));

  if (button == SWKBD_BUTTON_LEFT) {
    return "";
  }

  return std::string(text);
}
