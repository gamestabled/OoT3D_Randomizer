#ifndef _OOT_MALLOC_H_
#define _OOT_MALLOC_H_

#include "3ds/types.h"

typedef void* (*SystemArena_Malloc_proc)(u32 size);
#define SystemArena_Malloc_addr 0x35010C
#define SystemArena_Malloc ((SystemArena_Malloc_proc)SystemArena_Malloc_addr)

typedef void (*SystemArena_Free_proc)(void* ptr);
#define SystemArena_Free_addr 0x34FC6C
#define SystemArena_Free ((SystemArena_Free_proc)SystemArena_Free_addr)

#endif //_OOT_MALLOC_H_
