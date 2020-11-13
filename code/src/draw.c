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
#include <string.h>
#include <z3D/z3D.h>

static u8* FRAMEBUFFER[6];

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

void Draw_DrawCharacter(u32 posX, u32 posY, u32 color, char character)
{
    volatile u8 *const fb0 = (volatile u8 *const)FRAMEBUFFER[0];
    volatile u8 *const fb1 = (volatile u8 *const)FRAMEBUFFER[1];

    for(s32 y = 0; y < 10; y++)
    {
        const char charPos = ascii_font[character * 10 + y];

        for(s32 x = 6; x >= 1; x--)
        {
            const u32 screenPos = (posX * SCREEN_BOT_HEIGHT + (SCREEN_BOT_HEIGHT - y - posY - 1)) + (5 - x) * SCREEN_BOT_HEIGHT;
            const u32 pixelColor = ((charPos >> x) & 1) ? color : COLOR_BLACK;

            fb0[screenPos * 3] = (pixelColor) & 0xFF;
            fb0[screenPos * 3 + 1] = (pixelColor >> 8) & 0xFF;
            fb0[screenPos * 3 + 2] = (pixelColor >> 16) & 0xFF;
            fb1[screenPos * 3] = (pixelColor) & 0xFF;
            fb1[screenPos * 3 + 1] = (pixelColor >> 8) & 0xFF;
            fb1[screenPos * 3 + 2] = (pixelColor >> 16) & 0xFF;
        }
    }
}

void Draw_DrawCharacterTop(u32 posX, u32 posY, u32 color, char character)
{
    volatile u8 *const fb2 = (volatile u8 *const)FRAMEBUFFER[2];
    volatile u8 *const fb3 = (volatile u8 *const)FRAMEBUFFER[3];
    volatile u8 *const fb4 = (volatile u8 *const)FRAMEBUFFER[4];
    volatile u8 *const fb5 = (volatile u8 *const)FRAMEBUFFER[5];

    for(s32 y = 0; y < 10; y++)
    {
        const char charPos = ascii_font[character * 10 + y];

        for(s32 x = 6; x >= 1; x--)
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

                Draw_DrawCharacter(posX + line_i * SPACING_X, posY, color, string[i]);

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
    memset(FRAMEBUFFER[0], value, FB_BOTTOM_SIZE);
    memset(FRAMEBUFFER[1], value, FB_BOTTOM_SIZE);
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

void Draw_FlushFramebuffer(void)
{
    svcFlushProcessDataCache(CUR_PROCESS_HANDLE, FRAMEBUFFER[0], FB_BOTTOM_SIZE);
    svcFlushProcessDataCache(CUR_PROCESS_HANDLE, FRAMEBUFFER[1], FB_BOTTOM_SIZE);
}

void Draw_FlushFramebufferTop(void)
{
    svcFlushProcessDataCache(CUR_PROCESS_HANDLE, FRAMEBUFFER[2], FB_TOP_SIZE);
    svcFlushProcessDataCache(CUR_PROCESS_HANDLE, FRAMEBUFFER[3], FB_TOP_SIZE);
    svcFlushProcessDataCache(CUR_PROCESS_HANDLE, FRAMEBUFFER[4], FB_TOP_SIZE);
    svcFlushProcessDataCache(CUR_PROCESS_HANDLE, FRAMEBUFFER[5], FB_TOP_SIZE);
}