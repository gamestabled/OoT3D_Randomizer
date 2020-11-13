#ifndef _RHEAP_H_
#define _RHEAP_H_

#include "z3D/z3D.h"

#define ARR_SIZE(a) (sizeof(a) / sizeof(a[0]))

void rHeap_Init(void);
void* rHeap_Alloc(u32 bytes);

#endif //_RHEAP_H_
