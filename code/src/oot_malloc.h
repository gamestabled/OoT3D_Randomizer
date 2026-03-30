#ifndef _OOT_MALLOC_H_
#define _OOT_MALLOC_H_

#include "3ds/types.h"
#include "z3D/z3D.h"

void* SystemArena_Malloc(u32 size);
void SystemArena_Free(void* ptr);

#endif //_OOT_MALLOC_H_
