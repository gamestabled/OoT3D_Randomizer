/*
 *   This file is part of Luma3DS
 *   Copyright (C) 2016-2019 Aurora Wright, TuxSH
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

#include "3ds/svc.h"
#include "3ds/result.h"
#include "csvc.h"

// For accessing physmem uncached (and directly)
#define PA_PTR(addr) (void*)((u32)(addr) | 1 << 31)

#ifndef PA_FROM_VA_PTR
    #define PA_FROM_VA_PTR(addr) PA_PTR(svcConvertVAToPA((const void*)(addr), false))
#endif

#define REG32(addr) (*(vu32*)(PA_PTR(addr)))

static inline u32 makeARMBranch(const void* src, const void* dst, bool link) // the macros for those are ugly and buggy
{
    u32 instrBase = link ? 0xEB000000 : 0xEA000000;
    u32 off       = (u32)((const u8*)dst -
                    ((const u8*)src + 8)); // the PC is always two instructions ahead of the one being executed

    return instrBase | ((off >> 2) & 0xFFFFFF);
}

static inline void* decodeARMBranch(const void* src) {
    u32 instr = *(const u32*)src;
    s32 off   = (instr & 0xFFFFFF) << 2;
    off       = (off << 6) >> 6; // sign extend

    return (void*)((const u8*)src + 8 + off);
}

Result OpenProcessByName(const char* name, Handle* h);
