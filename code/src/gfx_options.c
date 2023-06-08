#include <string.h>
#include "gfx_options.h"
#include "gfx.h"
#include "savefile.h"
#include "draw.h"
#include "input.h"
#include "common.h"
#include "settings.h"

#define BORDER_WIDTH 2
#define CHOICE_COLUMN 220
#define DESCRIPTION_ROW 184
#define OPTIONS_COUNT 6

typedef struct {
    char name[30];
    char alternatives[8][16];
    char description[256];
    s8* optionPointer;
} Option;

s8 selectedOption;
Option options[OPTIONS_COUNT];

void InitOptions(void) {
    u8 opNum  = 0;
    u8 altNum = 0;

    // BGM
    altNum = 0;
    strcpy(options[opNum].name, "Play Music");
    strcpy(options[opNum].alternatives[altNum++], "Off");
    strcpy(options[opNum].alternatives[altNum++], "On");
    strcpy(options[opNum].description, "Toggles the music.\nTakes effect once music is switched.");
    options[opNum++].optionPointer = &gExtSaveData.option_EnableBGM;

    // SFX
    altNum = 0;
    strcpy(options[opNum].name, "Play Sound Effects");
    strcpy(options[opNum].alternatives[altNum++], "Off");
    strcpy(options[opNum].alternatives[altNum++], "On");
    strcpy(options[opNum].description, "Toggles the sound effects.");
    options[opNum++].optionPointer = &gExtSaveData.option_EnableSFX;

    // Silence Navi
    altNum = 0;
    strcpy(options[opNum].name, "Navi Notifications");
    strcpy(options[opNum].alternatives[altNum++], "Silenced");
    strcpy(options[opNum].alternatives[altNum++], "Normal");
    strcpy(options[opNum].alternatives[altNum++], "Constant");
    strcpy(options[opNum].description, "Determines the frequency of Navi's notifications.");
    options[opNum++].optionPointer = &gExtSaveData.option_NaviNotifications;

    // Ignore Mask Reaction
    altNum = 0;
    strcpy(options[opNum].name, "Ignore Mask Reaction");
    strcpy(options[opNum].alternatives[altNum++], "Off");
    strcpy(options[opNum].alternatives[altNum++], "On");
    strcpy(options[opNum].description,
           "Causes NPCs to respond normally when wearing\nmasks. Does not apply to trade quest dialogues.");
    options[opNum++].optionPointer = &gExtSaveData.option_IgnoreMaskReaction;

    // Skip Song Replays
    altNum = 0;
    strcpy(options[opNum].name, "Skip Song Replays");
    strcpy(options[opNum].alternatives[altNum++], "Don't Skip");
    strcpy(options[opNum].alternatives[altNum++], "Skip (No SFX)");
    strcpy(options[opNum].alternatives[altNum++], "Skip (Keep SFX)");
    strcpy(options[opNum].description, "Toggle skipping the automatic replay after\nyou play a song.");
    options[opNum++].optionPointer = &gExtSaveData.option_SkipSongReplays;

    // Free Camera Control
    if (gSettingsContext.freeCamera) {
        altNum = 0;
        strcpy(options[opNum].name, "Free Camera Control");
        strcpy(options[opNum].alternatives[altNum++], "Normal");
        strcpy(options[opNum].alternatives[altNum++], "Invert Y-Axis");
        strcpy(options[opNum].alternatives[altNum++], "Invert X-Axis");
        strcpy(options[opNum].alternatives[altNum++], "Invert Both");
        strcpy(options[opNum].description,
               "Change the input directions of the free camera.\n\nThis feature is not available on old 3DS systems.");
        options[opNum++].optionPointer = &gExtSaveData.option_FreeCamControl;
    }
}

void Gfx_DrawOptions(void) {
    Draw_DrawString(10, 16, COLOR_TITLE, "Options");

    // Options
    for (u8 i = 0; i < ARRAY_SIZE(options); i++) {
        if (strlen(options[i].name) == 0) {
            break;
        }
        Draw_DrawString(10, 16 + SPACING_Y + SPACING_Y * i, (i == selectedOption) ? COLOR_GREEN : COLOR_WHITE,
                        options[i].name);
        Draw_DrawString(CHOICE_COLUMN, 16 + SPACING_Y + SPACING_Y * i,
                        (i == selectedOption) ? COLOR_GREEN : COLOR_WHITE,
                        options[i].alternatives[*options[i].optionPointer]);
    }

    // Description
    Draw_DrawRect(10 - BORDER_WIDTH, DESCRIPTION_ROW - BORDER_WIDTH, SCREEN_BOT_WIDTH - 20 + BORDER_WIDTH * 2,
                  SPACING_Y * 3 + BORDER_WIDTH * 2, COLOR_WHITE);
    Draw_DrawRect(10, DESCRIPTION_ROW, SCREEN_BOT_WIDTH - 20, SPACING_Y * 3, COLOR_BLACK);
    Draw_DrawString(10, DESCRIPTION_ROW, COLOR_WHITE, options[selectedOption].description);
}

void NextOption(const Option* option) {
    do {
        (*option->optionPointer)++;
        if (*option->optionPointer > ARRAY_SIZE(option->alternatives) - 1) {
            *option->optionPointer = 0;
        }
    } while (strlen(option->alternatives[*option->optionPointer]) == 0);
}

void PrevOption(const Option* option) {
    do {
        (*option->optionPointer)--;
        if (*option->optionPointer < 0) {
            *option->optionPointer = ARRAY_SIZE(option->alternatives) - 1;
        }
    } while (strlen(option->alternatives[*option->optionPointer]) == 0);
}

void Gfx_OptionsUpdate(void) {
    if (pressed & (BUTTON_DOWN | CPAD_DOWN)) {
        do {
            selectedOption++;
            if (selectedOption > ARRAY_SIZE(options) - 1) {
                selectedOption = 0;
            }
        } while (strlen(options[selectedOption].name) == 0);
        handledInput = true;
    } else if (pressed & (BUTTON_UP | CPAD_UP)) {
        do {
            selectedOption--;
            if (selectedOption < 0) {
                selectedOption = ARRAY_SIZE(options) - 1;
            }
        } while (strlen(options[selectedOption].name) == 0);
        handledInput = true;
    }

    if (pressed & (BUTTON_RIGHT | CPAD_RIGHT)) {
        NextOption(&options[selectedOption]);
        handledInput = true;
    } else if (pressed & (BUTTON_LEFT | CPAD_LEFT)) {
        PrevOption(&options[selectedOption]);
        handledInput = true;
    }
}
