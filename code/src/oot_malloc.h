#ifndef _OOT_MALLOC_H_
#define _OOT_MALLOC_H_

#include "3ds/types.h"
#include "z3D/z3D.h"

typedef void* (*SystemArena_Malloc_proc)(u32 size);
#define SystemArena_Malloc ((SystemArena_Malloc_proc)GAME_ADDR(0x35010C))

typedef void (*SystemArena_Free_proc)(void* ptr);
#define SystemArena_Free ((SystemArena_Free_proc)GAME_ADDR(0x34FC6C))

#endif //_OOT_MALLOC_H_
