#include <string.h>
#include "gfx_options.h"

#define BORDER_WIDTH 2
#define CHOICE_COLUMN 240
#define DESCRIPTION_ROW 184

typedef struct {
    char name[30];
    char alternatives[8][16];
    char description[256];
    s8* optionPointer;
} Option;

s8 selectedOption;
Option options[2];

void InitOptions(void) {
    // BGM
    strcpy(options[0].name, "Music");
    strcpy(options[0].alternatives[0], "Off");
    strcpy(options[0].alternatives[1], "On");
    strcpy(options[0].description, "Toggles the music.\nTakes effect once music is switched.");
    options[0].optionPointer = &gExtSaveData.option_EnableBGM;

    // SFX
    strcpy(options[1].name, "Sound Effects");
    strcpy(options[1].alternatives[0], "Off");
    strcpy(options[1].alternatives[1], "On");
    strcpy(options[1].description, "Toggles the sound effects.");
    options[1].optionPointer = &gExtSaveData.option_EnableSFX;
}

void Gfx_DrawOptions(void) {
    Draw_DrawString(10, 16, COLOR_TITLE, "Options");

    // Options
    for (u8 i = 0; i < sizeof(options) / sizeof(Option); i++) {
        Draw_DrawString(10, 16 + SPACING_Y + SPACING_Y * i, (i == selectedOption) ? COLOR_GREEN : COLOR_WHITE, options[i].name);
        Draw_DrawString(CHOICE_COLUMN, 16 + SPACING_Y + SPACING_Y * i, (i == selectedOption) ? COLOR_GREEN : COLOR_WHITE, options[i].alternatives[*options[i].optionPointer]);
    }

    // Description
    Draw_DrawRect(10 - BORDER_WIDTH, DESCRIPTION_ROW - BORDER_WIDTH, SCREEN_BOT_WIDTH - 20 + BORDER_WIDTH * 2, SPACING_Y * 3 + BORDER_WIDTH * 2, COLOR_WHITE);
    Draw_DrawRect(10, DESCRIPTION_ROW, SCREEN_BOT_WIDTH - 20, SPACING_Y * 3, COLOR_BLACK);
    Draw_DrawString(10, DESCRIPTION_ROW, COLOR_WHITE, options[selectedOption].description);
}

void NextOption(const Option* option_) {
    do {
        *option_->optionPointer += 1;
        if (*option_->optionPointer > (s8)(sizeof(option_->alternatives) / sizeof(option_->alternatives[0])) - 1) {
            *option_->optionPointer = 0;
        }
    } while (strlen(option_->alternatives[*option_->optionPointer]) == 0);
}

void PrevOption(const Option* option_) {
    do {
        *option_->optionPointer -= 1;
        if (*option_->optionPointer < 0) {
            *option_->optionPointer = (s8)(sizeof(option_->alternatives) / sizeof(option_->alternatives[0])) - 1;
        }
    } while (strlen(option_->alternatives[*option_->optionPointer]) == 0);
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
        selectedOption = 0;
    } else if (selectedOption > (s8)(sizeof(options) / sizeof(Option)) - 1) {
        selectedOption = (s8)(sizeof(options) / sizeof(Option)) - 1;
    }

    if (pressed & BUTTON_RIGHT) {
        NextOption(&options[selectedOption]);
        handledInput = true;
    } else if (pressed & BUTTON_LEFT) {
        PrevOption(&options[selectedOption]);
        handledInput = true;
    }
}
