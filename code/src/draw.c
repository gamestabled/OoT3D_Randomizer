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

// #include "fmt.h"
#include "lib/printf.h"
#include "draw.h"
#include "utils.h"
#include "3ds/svc.h"
#include "3ds/synchronization.h"
#include "fonts/ascii_font.h"
#include "fonts/ascii_font_small.h"
#include "icons.h"
#include <string.h>
#include <z3D/z3D.h>

static u8* FRAMEBUFFER[6];
static u8 backBufferBtm[FB_BOTTOM_SIZE];
static u32 frontBufferIdx_btm = 0;

void Draw_PreSwapBuffers(Draw_Display display)
{
    if (display == DISPLAY_1 || display == DISPLAY_BOTH)
    {
        frontBufferIdx_btm++;
        frontBufferIdx_btm %= 2;
    }
}

static RecursiveLock lock;

void Draw_Lock(void)
{
    static bool lockInitialized = false;
    if(!lockInitialized)
    {
        RecursiveLock_Init(&lock);
        lockInitialized = true;
    }

    RecursiveLock_Lock(&lock);
}

void Draw_Unlock(void)
{
    RecursiveLock_Unlock(&lock);
}

void Draw_DrawIcon(u32 posX, u32 posY, u32 color, Draw_IconType icon)
{
    // Skip drawing entirely if we're off-screen
    if (posX >= SCREEN_BOT_WIDTH) { return; }
    if (posY >= SCREEN_BOT_HEIGHT) { return; }

    u8 sizeX = ICON_WIDTH;
    u8 sizeY = ICON_HEIGHT;

    // Clamp size to screen bounds
    if (posX + sizeX > SCREEN_BOT_WIDTH) { sizeX = SCREEN_BOT_WIDTH - posX; }
    if (posY + sizeY > SCREEN_BOT_HEIGHT) { sizeY = SCREEN_BOT_HEIGHT - posY; }
    const u8 sizeXMinusOne = ICON_WIDTH - 1;

    const unsigned char *glyph = rIcons[icon];

    for(s32 y = 0; y < sizeY; y++)
    {
        const unsigned char glyphRow = glyph[y];
        const u32 screenPosY = (posX * SCREEN_BOT_HEIGHT) + (SCREEN_BOT_HEIGHT - y - posY - 1);

        for(s32 x = 0; x < sizeX; x++)
        {
            const u32 shift = sizeXMinusOne - x;
            const u32 screenPos = (screenPosY + x * SCREEN_BOT_HEIGHT) * 3;
            const u32 pixelColor = ((glyphRow >> shift) & 1) ? color : COLOR_BLACK;

            backBufferBtm[screenPos]        = (pixelColor) & 0xFF;
            backBufferBtm[screenPos + 1]    = (pixelColor >> 8) & 0xFF;
            backBufferBtm[screenPos + 2]    = (pixelColor >> 16) & 0xFF;
        }
    }
}

void Draw_DrawRect(u32 posX, u32 posY, u32 width, u32 height, u32 color)
{
    // Skip drawing entirely if we're off-screen
    if (posX >= SCREEN_BOT_WIDTH) { return; }
    if (posY >= SCREEN_BOT_HEIGHT) { return; }

    // Clamp size to screen bounds
    if (posX + width > SCREEN_BOT_WIDTH) { width = SCREEN_BOT_WIDTH - posX; }
    if (posY + height > SCREEN_BOT_HEIGHT) { height = SCREEN_BOT_HEIGHT - posY; }

    for(u32 y = 0; y < height; y++)
    {
        const u32 screenPosY = (posX * SCREEN_BOT_HEIGHT) + (SCREEN_BOT_HEIGHT - y - posY - 1);
        for(u32 x = 0; x < width; x++)
        {
            const u32 screenPos = (screenPosY + x * SCREEN_BOT_HEIGHT) * 3;

            backBufferBtm[screenPos]        = (color) & 0xFF;
            backBufferBtm[screenPos + 1]    = (color >> 8) & 0xFF;
            backBufferBtm[screenPos + 2]    = (color >> 16) & 0xFF;
        }
    }
}

void Draw_DrawCharacter_Impl(u32 posX, u32 posY, u32 color, char character, const unsigned char *font, u8 sizeX, u8 sizeY)
{
    const u32 shiftBase = sizeX - 1 + (8 - sizeX); // If sizeX is smaller than 8, we must shift further left

    for(u32 y = 0; y < sizeY; y++)
    {
        const unsigned char charPos = font[character * sizeY + y];
        const u32 screenPosY = (posX * SCREEN_BOT_HEIGHT) + (SCREEN_BOT_HEIGHT - y - posY - 1);

        for(u32 x = 0; x < sizeX; x++)
        {
            const u32 shift = shiftBase - x;
            const u32 screenPos = (screenPosY + x * SCREEN_BOT_HEIGHT) * 3;
            const u32 pixelColor = ((charPos >> shift) & 1) ? color : COLOR_BLACK;

            backBufferBtm[screenPos]        = (pixelColor) & 0xFF;
            backBufferBtm[screenPos + 1]    = (pixelColor >> 8) & 0xFF;
            backBufferBtm[screenPos + 2]    = (pixelColor >> 16) & 0xFF;
        }
    }
}

void Draw_DrawCharacter(u32 posX, u32 posY, u32 color, char character)
{
    Draw_DrawCharacter_Impl(posX, posY, color, character, ascii_font, FONT_WIDTH, FONT_HEIGHT);
}

void Draw_DrawCharacterTop(u32 posX, u32 posY, u32 color, char character)
{
    volatile u8 *const fb2 = (volatile u8 *const)FRAMEBUFFER[2];
    volatile u8 *const fb3 = (volatile u8 *const)FRAMEBUFFER[3];
    volatile u8 *const fb4 = (volatile u8 *const)FRAMEBUFFER[4];
    volatile u8 *const fb5 = (volatile u8 *const)FRAMEBUFFER[5];

    for(u32 y = 0; y < 10; y++)
    {
        const char charPos = ascii_font[character * 10 + y];

        for(u32 x = 6; x >= 1; x--)
        {
            const u32 screenPos = (posX * SCREEN_TOP_HEIGHT + (SCREEN_TOP_HEIGHT - y - posY - 1)) + (5 - x) * SCREEN_TOP_HEIGHT;
            const u32 pixelColor = ((charPos >> x) & 1) ? color : COLOR_BLACK;

            fb2[screenPos * 3] = (pixelColor) & 0xFF;
            fb2[screenPos * 3 + 1] = (pixelColor >> 8) & 0xFF;
            fb2[screenPos * 3 + 2] = (pixelColor >> 16) & 0xFF;
            fb3[screenPos * 3] = (pixelColor) & 0xFF;
            fb3[screenPos * 3 + 1] = (pixelColor >> 8) & 0xFF;
            fb3[screenPos * 3 + 2] = (pixelColor >> 16) & 0xFF;
            fb4[screenPos * 3] = (pixelColor) & 0xFF;
            fb4[screenPos * 3 + 1] = (pixelColor >> 8) & 0xFF;
            fb4[screenPos * 3 + 2] = (pixelColor >> 16) & 0xFF;
            fb5[screenPos * 3] = (pixelColor) & 0xFF;
            fb5[screenPos * 3 + 1] = (pixelColor >> 8) & 0xFF;
            fb5[screenPos * 3 + 2] = (pixelColor >> 16) & 0xFF;
        }
    }
}

u32 Draw_DrawString(u32 posX, u32 posY, u32 color, const char *string)
{
    for(u32 i = 0, line_i = 0; i < strlen(string); i++)
        switch(string[i])
        {
            case '\n':
                posY += SPACING_Y;
                line_i = 0;
                break;

            case '\t':
                line_i += 2;
                break;

            default:
                //Make sure we never get out of the screen
                if(line_i >= ((SCREEN_BOT_WIDTH) - posX) / SPACING_X)
                {
                    posY += SPACING_Y;
                    line_i = 1; //Little offset so we know the same string continues
                    if(string[i] == ' ') break; //Spaces at the start look weird
                }

                Draw_DrawCharacter_Impl(posX + line_i * SPACING_X, posY, color, string[i], ascii_font, FONT_WIDTH, FONT_HEIGHT);

                line_i++;
                break;
        }

    return posY;
}

u32 Draw_DrawString_Small(u32 posX, u32 posY, u32 color, const char *string)
{
    for(u32 i = 0, line_i = 0; i < strlen(string); i++)
        switch(string[i])
        {
            case '\n':
                posY += SPACING_SMALL_Y;
                line_i = 0;
                break;

            case '\t':
                line_i += 2;
                break;

            default:
                //Make sure we never get out of the screen
                if(line_i >= ((SCREEN_BOT_WIDTH) - posX) / SPACING_SMALL_X)
                {
                    posY += SPACING_SMALL_Y;
                    line_i = 1; //Little offset so we know the same string continues
                    if(string[i] == ' ') break; //Spaces at the start look weird
                }

                Draw_DrawCharacter_Impl(posX + line_i * SPACING_SMALL_X, posY, color, string[i], ascii_font_small, FONT_WIDTH_SMALL, FONT_HEIGHT_SMALL);

                line_i++;
                break;
        }

    return posY;
}

u32 Draw_DrawStringTop(u32 posX, u32 posY, u32 color, const char *string)
{
    for(u32 i = 0, line_i = 0; i < strlen(string); i++)
        switch(string[i])
        {
            case '\n':
                posY += SPACING_Y;
                line_i = 0;
                break;

            case '\t':
                line_i += 2;
                break;

            default:
                //Make sure we never get out of the screen
                if(line_i >= ((SCREEN_TOP_WIDTH) - posX) / SPACING_X)
                {
                    posY += SPACING_Y;
                    line_i = 1; //Little offset so we know the same string continues
                    if(string[i] == ' ') break; //Spaces at the start look weird
                }

                Draw_DrawCharacterTop(posX + line_i * SPACING_X, posY, color, string[i]);

                line_i++;
                break;
        }

    return posY;
}

u32 Draw_DrawFormattedString(u32 posX, u32 posY, u32 color, const char *fmt, ...)
{
    char buf[DRAW_MAX_FORMATTED_STRING_SIZE + 1];
    va_list args;
    va_start(args, fmt);
    // vsprintf(buf, fmt, args);
    vsnprintf_(buf, DRAW_MAX_FORMATTED_STRING_SIZE, fmt, args);
    va_end(args);

    return Draw_DrawString(posX, posY, color, buf);
}

u32 Draw_DrawFormattedString_Small(u32 posX, u32 posY, u32 color, const char *fmt, ...)
{
    char buf[DRAW_MAX_FORMATTED_STRING_SIZE + 1];
    va_list args;
    va_start(args, fmt);
    // vsprintf(buf, fmt, args);
    vsnprintf_(buf, DRAW_MAX_FORMATTED_STRING_SIZE, fmt, args);
    va_end(args);

    return Draw_DrawString_Small(posX, posY, color, buf);
}

u32 Draw_DrawFormattedStringTop(u32 posX, u32 posY, u32 color, const char *fmt, ...)
{
    char buf[DRAW_MAX_FORMATTED_STRING_SIZE + 1];
    va_list args;
    va_start(args, fmt);
    // vsprintf(buf, fmt, args);
    vsnprintf_(buf, DRAW_MAX_FORMATTED_STRING_SIZE, fmt, args);
    va_end(args);

    return Draw_DrawStringTop(posX, posY, color, buf);
}

void Draw_FillFramebuffer(u32 value)
{
    memset(FRAMEBUFFER[frontBufferIdx_btm], value, FB_BOTTOM_SIZE);
}

void Draw_ClearFramebuffer(void)
{
    Draw_FillFramebuffer(0);
}

void Draw_SetupFramebuffer(void)
{
    FRAMEBUFFER[0] = (u8*)Z3D_BOTTOM_SCREEN_1;
    FRAMEBUFFER[1] = (u8*)Z3D_BOTTOM_SCREEN_2;
    FRAMEBUFFER[2] = (u8*)Z3D_TOP_SCREEN_LEFT_1;
    FRAMEBUFFER[3] = (u8*)Z3D_TOP_SCREEN_LEFT_2;
    FRAMEBUFFER[4] = (u8*)Z3D_TOP_SCREEN_RIGHT_1;
    FRAMEBUFFER[5] = (u8*)Z3D_TOP_SCREEN_RIGHT_2;
}

void Draw_FillBackbuffer(u32 value)
{
    memset(backBufferBtm, value, FB_BOTTOM_SIZE);
}

void Draw_ClearBackbuffer(void)
{
    Draw_FillBackbuffer(0);
}

void Draw_CopyBackBuffer(void)
{
    memcpy(FRAMEBUFFER[frontBufferIdx_btm], backBufferBtm, FB_BOTTOM_SIZE);
}

void Draw_FlushFramebuffer(void)
{
    svcFlushProcessDataCache(CUR_PROCESS_HANDLE, FRAMEBUFFER[frontBufferIdx_btm], FB_BOTTOM_SIZE);
}

void Draw_FlushFramebufferTop(void)
{
    svcFlushProcessDataCache(CUR_PROCESS_HANDLE, FRAMEBUFFER[2], FB_TOP_SIZE);
    svcFlushProcessDataCache(CUR_PROCESS_HANDLE, FRAMEBUFFER[3], FB_TOP_SIZE);
    svcFlushProcessDataCache(CUR_PROCESS_HANDLE, FRAMEBUFFER[4], FB_TOP_SIZE);
    svcFlushProcessDataCache(CUR_PROCESS_HANDLE, FRAMEBUFFER[5], FB_TOP_SIZE);
}