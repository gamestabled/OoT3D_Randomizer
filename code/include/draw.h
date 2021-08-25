/*
*   This file is a modified part of Luma3DS
*   Copyright (C) 2016-2019 Aurora Wright, TuxSH
*   Modified 2020 Gamestabled
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*   Additional Terms 7.b and 7.c of GPLv3 apply to this file:
*       * Requiring preservation of specified reasonable legal notices or
*         author attributions in that material or in the Appropriate Legal
*         Notices displayed by works containing it.
*       * Prohibiting misrepresentation of the origin of that material,
*         or requiring that modified versions of such material be marked in
*         reasonable ways as different from the original version.
*/

#pragma once

#include "3ds/types.h"
#include "3ds/gfx.h"

#define FB_BOTTOM_VRAM_ADDR         ((void *)0x1F48F000) // cached
#define FB_BOTTOM_VRAM_PA           0x1848F000
#define FB_BOTTOM_SIZE              (320 * 240 * 3)
#define FB_TOP_SIZE                 (400 * 240 * 3)

#define SCREEN_BOT_WIDTH  320
#define SCREEN_BOT_HEIGHT 240

#define SCREEN_TOP_WIDTH  400
#define SCREEN_TOP_HEIGHT 240

#define SPACING_Y 11
#define SPACING_X 6

#define SPACING_SMALL_Y 9
#define SPACING_SMALL_X 6

#define COLOR_TITLE RGB8(0x33, 0x33, 0xFF)
#define COLOR_WHITE RGB8(0xFF, 0xFF, 0xFF)
#define COLOR_RED   RGB8(0xFF, 0x00, 0x00)
#define COLOR_GREEN RGB8(0x00, 0xFF, 0x00)
#define COLOR_BLACK RGB8(0x00, 0x00, 0x00)

#define DRAW_MAX_FORMATTED_STRING_SIZE  512

void Draw_Lock(void);
void Draw_Unlock(void);

void Draw_DrawRect(u32 posX, u32 posY, u32 width, u32 height, u32 color);
void Draw_DrawCharacter(u32 posX, u32 posY, u32 color, char character);
u32 Draw_DrawString(u32 posX, u32 posY, u32 color, const char *string);
u32 Draw_DrawString_Small(u32 posX, u32 posY, u32 color, const char *string);
u32 Draw_DrawFormattedString(u32 posX, u32 posY, u32 color, const char *fmt, ...);
u32 Draw_DrawFormattedString_Small(u32 posX, u32 posY, u32 color, const char *fmt, ...);

void Draw_DrawCharacterTop(u32 posX, u32 posY, u32 color, char character);
u32 Draw_DrawStringTop(u32 posX, u32 posY, u32 color, const char *string);
u32 Draw_DrawFormattedStringTop(u32 posX, u32 posY, u32 color, const char *fmt, ...);

void Draw_FillFramebuffer(u32 value);
void Draw_ClearFramebuffer(void);
void Draw_SetupFramebuffer(void);
void Draw_FillBackbuffer(u32 value);
void Draw_ClearBackbuffer(void);
void Draw_CopyBackBuffer(void);
void Draw_FlushFramebuffer(void);
void Draw_FlushFramebufferTop(void);
