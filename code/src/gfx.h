#ifndef _GFX_H_
#define _GFX_H_

#include "3ds/types.h"

extern u32 pressed;
extern bool handledInput;

void Gfx_Init(void);
void Gfx_Update(void);

#endif //_GFX_H_
