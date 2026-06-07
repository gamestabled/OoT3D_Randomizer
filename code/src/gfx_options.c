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

typedef struct {
    s8* optionPointer;
    char* name;
    char* description;
    char** alternatives;
    u8 alternativesCount;
    Bool hidden;
} Option;

// clang-format off
#define OPTION(_optionId, _name, _description, ...) {            \
    .optionPointer     = &gExtSaveData.options[_optionId],       \
    .name              = _name,                                  \
    .description       = _description,                           \
    .alternatives      = (char*[]){ __VA_ARGS__ },               \
    .alternativesCount = ARRAY_SIZE(((char*[]){ __VA_ARGS__ })), \
    .hidden            = 0,                                      \
}
// clang-format on

Option options[] = {
    OPTION(OPTION_ENABLEBGM, "Play Music",                             //
           "Toggles the music.\nTakes effect once music is switched.", //
           "Off", "On"),
    OPTION(OPTION_ENABLESFX, "Play Sound Effects", //
           "Toggles the sound effects.",           //
           "Off", "On"),
    OPTION(OPTION_NAVINOTIFICATIONS, "Navi Notifications",      //
           "Determines the frequency of Navi's notifications.", //
           "Silenced", "Normal", "Constant"),
    OPTION(OPTION_IGNOREMASKREACTION, "Ignore Mask Reaction",
           "Causes NPCs to respond normally when wearing\nmasks. Does not apply to trade quest dialogues.", //
           "Off", "On"),
    OPTION(OPTION_SKIPSONGREPLAYS, "Skip Song Replays",
           "Toggle skipping the automatic replay after\nyou play a song.", //
           "Don't Skip", "Skip (No SFX)", "Skip (Keep SFX)"),
    OPTION(OPTION_FREECAMCONTROL, "Free Camera Control",
           "Change the input directions of the free camera.\n\nThis feature is not available on old 3DS systems.",
           "Normal", "Invert Y-Axis", "Invert X-Axis", "Invert Both"),
};
s8 selectedOption;

void InitOptions(void) {
    if (!gSettingsContext.freeCamera) {
        options[OPTION_FREECAMCONTROL].hidden = TRUE;
    }
}

void Gfx_DrawOptions(void) {
    Draw_DrawString(10, 16, COLOR_TITLE, "Options");

    // Options
    u32 offY = 0;
    for (u8 i = 0; i < ARRAY_SIZE(options); i++) {
        if (options[i].hidden) {
            continue;
        }
        Draw_DrawString(10, 16 + SPACING_Y + offY, (i == selectedOption) ? COLOR_GREEN : COLOR_WHITE, options[i].name);
        Draw_DrawString(CHOICE_COLUMN, 16 + SPACING_Y + offY, (i == selectedOption) ? COLOR_GREEN : COLOR_WHITE,
                        options[i].alternatives[*options[i].optionPointer]);
        offY += SPACING_Y;
    }

    // Description
    Draw_DrawRect(10 - BORDER_WIDTH, DESCRIPTION_ROW - BORDER_WIDTH, SCREEN_BOT_WIDTH - 20 + BORDER_WIDTH * 2,
                  SPACING_Y * 3 + BORDER_WIDTH * 2, COLOR_WHITE);
    Draw_DrawRect(10, DESCRIPTION_ROW, SCREEN_BOT_WIDTH - 20, SPACING_Y * 3, COLOR_BLACK);
    Draw_DrawString(10, DESCRIPTION_ROW, COLOR_WHITE, options[selectedOption].description);
}

static void Scroll(s8* const var, const s8 valCount, const s8 scrollAmount) {
    const s8 min = 0;
    const s8 max = valCount - 1;

    *var += scrollAmount;

    while ((*var > max) || (*var < min)) {
        s64 offset = 1 + max - min;
        if (*var > max) {
            *var -= offset;
        } else {
            *var += offset;
        }
    }
}

void Gfx_OptionsUpdate(void) {
    if (pressed & (PAD_DOWN | PAD_UP)) {
        s8 scrollAmount = pressed & PAD_DOWN ? +1 : -1;
        do {
            Scroll(&selectedOption, ARRAY_SIZE(options), scrollAmount);
        } while (options[selectedOption].hidden);
        handledInput = true;
    } else if (pressed & (PAD_RIGHT | PAD_LEFT)) {
        s8 scrollAmount = pressed & PAD_RIGHT ? +1 : -1;
        Scroll(options[selectedOption].optionPointer, options[selectedOption].alternativesCount, scrollAmount);
        handledInput = true;
    }
}
