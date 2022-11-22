#include <string.h>
#include "gfx_options.h"
#include "gfx.h"
#include "savefile.h"
#include "draw.h"
#include "input.h"
#include "common.h"

#define BORDER_WIDTH 2
#define CHOICE_COLUMN 220
#define DESCRIPTION_ROW 184
#define OPTIONS_COUNT 5

typedef struct {
    char name[30];
    char alternatives[8][16];
    char description[256];
    s8* optionPointer;
} Option;

s8 selectedOption;
Option options[OPTIONS_COUNT];

void InitOptions(void) {
    // BGM
    strcpy(options[0].name, "Play Music");
    strcpy(options[0].alternatives[0], "Off");
    strcpy(options[0].alternatives[1], "On");
    strcpy(options[0].description, "Toggles the music.\nTakes effect once music is switched.");
    options[0].optionPointer = &gExtSaveData.option_EnableBGM;

    // SFX
    strcpy(options[1].name, "Play Sound Effects");
    strcpy(options[1].alternatives[0], "Off");
    strcpy(options[1].alternatives[1], "On");
    strcpy(options[1].description, "Toggles the sound effects.");
    options[1].optionPointer = &gExtSaveData.option_EnableSFX;

    // Silence Navi
    strcpy(options[2].name, "Silence Navi");
    strcpy(options[2].alternatives[0], "Off");
    strcpy(options[2].alternatives[1], "On");
    strcpy(options[2].description, "Prevents Navi from alerting you about advice.");
    options[2].optionPointer = &gExtSaveData.option_SilenceNavi;

    // Ignore Mask Reaction
    strcpy(options[3].name, "Ignore Mask Reaction");
    strcpy(options[3].alternatives[0], "Off");
    strcpy(options[3].alternatives[1], "On");
    strcpy(options[3].description,
           "Causes NPCs to respond normally when wearing\nmasks. Does not apply to trade quest dialogues.");
    options[3].optionPointer = &gExtSaveData.option_IgnoreMaskReaction;

    // Skip Song Replays
    strcpy(options[4].name, "Skip Song Replays");
    strcpy(options[4].alternatives[0], "Don't Skip");
    strcpy(options[4].alternatives[1], "Skip (No SFX)");
    strcpy(options[4].alternatives[2], "Skip (Keep SFX)");
    strcpy(options[4].description, "Toggle skipping the automatic replay after\nyou play a song.");
    options[4].optionPointer = &gExtSaveData.option_SkipSongReplays;
}

void Gfx_DrawOptions(void) {
    Draw_DrawString(10, 16, COLOR_TITLE, "Options");

    // Options
    for (u8 i = 0; i < ARRAY_SIZE(options); i++) {
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
    if (pressed & BUTTON_DOWN) {
        selectedOption++;
        handledInput = true;
    } else if (pressed & BUTTON_UP) {
        selectedOption--;
        handledInput = true;
    }

    if (selectedOption < 0) {
        selectedOption = ARRAY_SIZE(options) - 1;
    } else if (selectedOption > ARRAY_SIZE(options) - 1) {
        selectedOption = 0;
    }

    if (pressed & BUTTON_RIGHT) {
        NextOption(&options[selectedOption]);
        handledInput = true;
    } else if (pressed & BUTTON_LEFT) {
        PrevOption(&options[selectedOption]);
        handledInput = true;
    }
}
