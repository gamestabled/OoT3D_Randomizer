#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <filesystem>
#include <cstring>
#include <time.h>
#include <3ds.h>
#include "menu.hpp"
#include "patch.hpp"
#include "settings.hpp"
#include "spoiler_log.hpp"
namespace fs = std::filesystem;

namespace {
  bool seedChanged;
  u8 mode;
  u16 settingIdx;
  u8 menuIdx;
  u8 presetIdx;
  u8 generateIdx;
  u16 settingBound;
  u8 menuBound;
  u8 presetBound;
  u16 pastSeedLength;
  MenuItem* currentMenuItem;
  Option* currentSetting;
  PrintConsole topScreen, bottomScreen;
  std::vector<std::string> presetEntries;
}

void PrintTopScreen() {
  consoleSelect(&topScreen);
  consoleClear();
  printf("\x1b[1;10HOoT3D Randomizer testing!\n");
  printf("\x1b[3;1HA/B/D-pad: Navigate Menu\n");
  printf("   Select: Exit to Homebrew Menu\n");
  printf("        Y: New Random Seed\n");
  printf("        X: Input Custom Seed\n");
  printf("\x1b[10;5HCurrent Seed: %s", Settings::seed.c_str());
}

void MenuInit() {

  //Call to fill in the Excluded Locations menu (from item_location.hpp)
  AddExcludedOptions();

  seedChanged = false;
  mode = MAIN_MENU;
  menuIdx = 0;
  menuBound = 0;
  settingIdx = 0;
  settingBound = 0;
  presetIdx = 0;
  presetBound = 0;
  generateIdx = 0;
  pastSeedLength = Settings::seed.length();
  currentMenuItem = Settings::mainMenu[menuIdx];
  currentSetting = Settings::mainMenu[menuIdx]->settingsList->at(settingIdx);

  srand(time(NULL));
  consoleInit(GFX_TOP,    &topScreen);
  consoleInit(GFX_BOTTOM, &bottomScreen);

  consoleSelect(&topScreen);
  PrintTopScreen();

  if (!CreatePresetDirectories()) {
    printf("\x1b[20;5Failed to create preset directories.");
    printf("\x1b[21;5Loading presets might crash.");
  }

  consoleSelect(&bottomScreen);
  PrintMainMenu();

}

void MenuUpdate(u32 kDown) {

	consoleSelect(&bottomScreen);
	consoleClear();

	//Check for a menu change
	if (kDown & KEY_A && mode == MAIN_MENU) {
    mode = currentMenuItem->mode;
    ModeChangeInit();
    kDown = 0;
	} else if ((kDown & KEY_B && mode != MAIN_MENU)) {

    consoleSelect(&topScreen);
    PrintTopScreen();
		mode = MAIN_MENU;
		currentMenuItem = Settings::mainMenu[menuIdx];
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
      printf("\x1b[10;19H%s", spaces.c_str());
      printf("\x1b[10;19H%s", Settings::seed.c_str());
      seedChanged = false;
    }
  }

	//Print current menu (if applicable)
	consoleSelect(&bottomScreen);
	if (mode == MAIN_MENU) {
		UpdateMainMenu(kDown);
		PrintMainMenu();
    ClearDescription();
	} else if (mode == SUB_MENU) {
		UpdateSubMenu(kDown);
		PrintSubMenu();
	} else if (mode == LOAD_PRESET) {
    UpdatePresetsMenu(kDown);
    PrintPresetsMenu();
  } else if (mode == GENERATE_MODE) {
    UpdateGenerateMenu(kDown);
    if (mode != POST_GENERATE) {
      PrintGenerateMenu();
    }
  }
}

void ModeChangeInit() {
  if (mode == SUB_MENU) {
    settingIdx = 0;
    currentSetting = currentMenuItem->settingsList->at(settingIdx);

  } else if (mode == SAVE_PRESET) {
    if (SaveSettingsPreset()) {
      printf("\x1b[10;5HPreset Saved!");
      printf("\x1b[12;5HPress B to return to the main menu.");
    } else {
      printf("\x1b[10;5HFailed to save preset.");
      printf("\x1b[12;5HPress B to return to the main menu.");
    }

  } else if (mode == LOAD_PRESET) {
    GetPresets();

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

void UpdateSubMenu(u32 kDown) {
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

  if ((kDown & KEY_DRIGHT) != 0) {
    currentSetting->NextOptionIndex();
  }
  if ((kDown & KEY_DLEFT) != 0) {
    currentSetting->PrevOptionIndex();
  }

  // Bounds checking
  currentSetting->SanitizeSelectedOptionIndex();

  //Set toggle for all tricks
  if (((kDown & KEY_DRIGHT) != 0 || (kDown & KEY_DLEFT) != 0) && currentSetting->GetName() == "All Tricks")  {
    for (u16 i = 0; i < Settings::detailedLogicOptions.size(); i++) {
      Settings::detailedLogicOptions[i]->SetSelectedIndex(currentSetting->GetSelectedOptionIndex());
    }
  }
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

  if ((kDown & KEY_A) != 0) {
    consoleSelect(&topScreen);
    if (LoadPreset(presetEntries[presetIdx])) {
      printf("\x1b[24;5HPreset Loaded!");
    } else {
      printf("\x1b[24;5HFailed to load preset.");
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
			printf("\x1b[%d;%dH\x1b[32m>", row,  2);
			printf("\x1b[%d;%dH%s\x1b[0m", row,  3, menu->name.c_str());
		} else {
			printf("\x1b[%d;%dH%s\x1b[0m", row,  3, menu->name.c_str());
		}
	}
}

void PrintSubMenu() {
	//bounds checking incase settings go off screen
	if (settingIdx >= settingBound + MAX_SETTINGS_ON_SCREEN) {
		settingBound = settingIdx - (MAX_SETTINGS_ON_SCREEN - 1);
	} else if (settingIdx < settingBound)  {
		settingBound = settingIdx;
	}

	//print menu name
	printf("\x1b[0;%dH%s", (BOTTOM_WIDTH/2) - (currentMenuItem->name.length()/2), currentMenuItem->name.c_str());

	for (u8 i = 0; i < MAX_SETTINGS_ON_SCREEN; i++) {
    //break if there are no more settings to print
		if (i + settingBound >= currentMenuItem->settingsList->size()) break;

		Option* setting = currentMenuItem->settingsList->at(i + settingBound);

		u8 row = 3 + (i * 2);
    //make the current setting green
		if (settingIdx == i + settingBound) {
			printf("\x1b[%d;%dH\x1b[32m>", row,  1);
			printf("\x1b[%d;%dH%s:",       row,  2, setting->GetName().data());
			printf("\x1b[%d;%dH%s\x1b[0m", row, 26, setting->GetSelectedOption().data());
		} else {
			printf("\x1b[%d;%dH%s:",       row,  2, setting->GetName().data());
			printf("\x1b[%d;%dH%s",        row, 26, setting->GetSelectedOption().data());
		}

		setting->SetVariable();
	}

  PrintOptionDescrption();
}

void PrintPresetsMenu() {
  consoleSelect(&bottomScreen);
  if (presetEntries.empty()) {
    printf("\x1b[10;5HNo Presets Detected!");
    printf("\x1b[12;5HPress B to return to the main menu.");
    return;
  }

  printf("\x1b[0;%dHSelect a Preset", (BOTTOM_WIDTH/2) - 7);

	for (u8 i = 0; i < MAX_SETTINGS_ON_SCREEN; i++) {
		if (i + presetBound >= presetEntries.size()) break;

		std::string preset = presetEntries[i];

    u8 row = 3 + (i * 2);
    //make the current preset green
		if (presetIdx == i + presetBound) {
			printf("\x1b[%d;%dH\x1b[32m>", row, 14);
			printf("\x1b[%d;%dH%s\x1b[0m", row, 15, preset.c_str());
		} else {
			printf("\x1b[%d;%dH%s\x1b[0m", row, 15, preset.c_str());
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
    //make the current preset green
		if (generateIdx == i) {
			printf("\x1b[%d;%dH\x1b[32m>", row, 14);
			printf("\x1b[%d;%dH%s\x1b[0m", row, 15, option.c_str());
		} else {
			printf("\x1b[%d;%dH%s\x1b[0m", row, 15, option.c_str());
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

//Creates preset directories if they don't exist
bool CreatePresetDirectories() {
  Result res;
  FS_Archive sdmcArchive;

  // Open SD archive
  if (!R_SUCCEEDED(res = FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, "")))) {
    return false;
  }

  //Create the 3ds directory if it doesn't exist
  FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, "/3ds"), FS_ATTRIBUTE_DIRECTORY);
  //Create the presets directory if it doesn't exist
  FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, "/3ds/presets"), FS_ATTRIBUTE_DIRECTORY);
  //Create the oot3d directory if it doesn't exist
  FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, "/3ds/presets/oot3d"), FS_ATTRIBUTE_DIRECTORY);

  // Close SD archive
  FSUSER_CloseArchive(sdmcArchive);
  return true;
}

//Gets the preset filenames
void GetPresets() {
  presetEntries = {};
  for (const auto & entry : fs::directory_iterator("/3ds/presets/oot3d")) {
    presetEntries.push_back(entry.path().stem().string());
  }
}

//Load the selected preset
bool LoadPreset(std::string presetName) {
  //clear any potential 'failed to load preset' message on previous attempt
  ClearDescription();

  Result res;
  FS_Archive sdmcArchive = 0;
  Handle presetFile;
  u32 bytesRead = 0;
  u32 totalRW = 0;

  std::string filepath = "/3ds/presets/oot3d/" + presetName + ".bin";

  // Open SD archive
  if (!R_SUCCEEDED(res = FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, "")))) {
    printf("\x1b[22;5HFailed to load SD Archive.");
    return false;
  }

  // Open preset file
  if (!R_SUCCEEDED(res = FSUSER_OpenFile(&presetFile, sdmcArchive, fsMakePath(PATH_ASCII, filepath.c_str()), FS_OPEN_WRITE | FS_OPEN_CREATE, 0))) {
    printf("\x1b[22;5HFailed to open preset file %s.", filepath.c_str());
    return false;
  }

  //Read ctx size
  size_t ctxSize;
  if (!R_SUCCEEDED(res = FSFILE_Read(presetFile, &bytesRead, totalRW, &ctxSize, sizeof(ctxSize)))) {
    printf("\x1b[22;5HFailed to read preset size.");
    return false;
  }
  totalRW += bytesRead;

  //If the sizes don't match, then the preset is incompatible (there's probably a better way to do this)
  if (ctxSize != sizeof(SettingsContext)) {
    consoleSelect(&topScreen);
    printf("\x1b[22;5HPreset not compatible with current randomizer.");
    return false;
  }

  //Read preset SettingsContext
  SettingsContext ctx;
  if (!R_SUCCEEDED(res = FSFILE_Read(presetFile, &bytesRead, totalRW, &ctx, sizeof(ctx)))) {
    return false;
  }

  FSFILE_Close(presetFile);
  FSUSER_CloseArchive(sdmcArchive);

  Settings::FillSettings(ctx);
  return true;
}

//Saves the new preset to a file
bool SaveSettingsPreset() {

  std::string presetName = (GetInput("Preset Name")).substr(0, 19);
  //don't save if the user cancelled
  if (presetName == "") {
    return false;
  }

  Result res;
  FS_Archive sdmcArchive = 0;
  Handle presetFile;
  u32 bytesWritten = 0;
  u32 totalRW = 0;

  std::string presetsFilepath = "/3ds/presets/oot3d/";
  std::string filepath = presetsFilepath + presetName + ".bin";

  SettingsContext ctx = Settings::FillContext();

  // Open SD archive
  if (!R_SUCCEEDED(res = FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, "")))) {
    return false;
  }

  // Open preset file
  if (!R_SUCCEEDED(res = FSUSER_OpenFile(&presetFile, sdmcArchive, fsMakePath(PATH_ASCII, filepath.c_str()), FS_OPEN_WRITE | FS_OPEN_CREATE, 0))) {
    return false;
  }

  // Write struct size to preset file
  totalRW = 0;
  size_t ctxSize = sizeof(ctx);
  if (!R_SUCCEEDED(res = FSFILE_Write(presetFile, &bytesWritten, totalRW, &ctxSize, sizeof(ctxSize), FS_WRITE_FLUSH))) {
    return false;
  }
  totalRW += bytesWritten;

  // Write struct to preset file
  if (!R_SUCCEEDED(res = FSFILE_Write(presetFile, &bytesWritten, totalRW, &ctx, sizeof(ctx), FS_WRITE_FLUSH))) {
    return false;
  }
  totalRW += bytesWritten;

  FSFILE_Close(presetFile);
  FSUSER_CloseArchive(sdmcArchive);

  return true;
}

void GenerateRandomizer() {

  consoleSelect(&topScreen);
  consoleClear();

  //if a blank seed was entered, make a random one
  if (Settings::seed == "") {
    Settings::seed = std::to_string(rand());
  } else if (Settings::seed.rfind("seed_testing_count", 0) == 0) {
    int count = std::stoi(Settings::seed.substr(18, std::string::npos), nullptr);
    Playthrough::Playthrough_Repeat(count);
    return;
  }

  //turn the settings into a string for hashing
  SettingsContext ctx = Settings::FillContext();
  ctx.mirrorWorld = 0; //Mirror World shouldn't affect the seed
  const void* ctxPtr = &ctx;
  std::string settingsStr(sizeof(ctx), 'A');
  std::memcpy(settingsStr.data(), ctxPtr, sizeof(ctx));

  unsigned int finalHash = std::hash<std::string>{}(Settings::seed + settingsStr);

	int ret = Playthrough::Playthrough_Init(finalHash);
	if (ret < 0) {
		printf("Error %d with fill. Press Select to exit.\n", ret);
		return;
	}
  printf("\x1b[11;10HWriting Patch...");
	if (WritePatch()) {
		printf("Done");
    printf("\x1b[13;10HQuit out using the home menu. Then\n");
    printf("\x1b[14;10Henable game patching and launch OoT3D!\n");

    printf("\x1b[16;10HHash:");
    for (u8 i = 0; i < randomizerHash.size(); i++) {
      printf("\x1b[%d;11H- %s", i + 17, randomizerHash[i].c_str());
    }
	} else {
		printf("Failed\nPress Select to exit.\n");
	}
}

//opens up the 3ds software keyboard for getting user input
std::string GetInput(const char* hintText) {
  SwkbdState swkbd;
  char seed[60];
  SwkbdButton button = SWKBD_BUTTON_NONE;

  swkbdInit(&swkbd, SWKBD_TYPE_WESTERN, 2, -1);
	swkbdSetValidation(&swkbd, SWKBD_NOTEMPTY_NOTBLANK, SWKBD_FILTER_AT | SWKBD_FILTER_PERCENT | SWKBD_FILTER_BACKSLASH | SWKBD_FILTER_PROFANITY, 2);
	swkbdSetFeatures(&swkbd, SWKBD_MULTILINE);
	swkbdSetHintText(&swkbd, hintText);
  swkbdSetButton(&swkbd, SWKBD_BUTTON_LEFT, "Cancel", false);

  button = swkbdInputText(&swkbd, seed, sizeof(seed));

  if (button == SWKBD_BUTTON_LEFT) {
    return "";
  }

  return std::string(seed);
}
