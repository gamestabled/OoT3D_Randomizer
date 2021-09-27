#ifndef _GFX_H_
#define _GFX_H_

#include "../include/draw.h"
#include "../include/input.h"
#include "3ds/extdata.h"
#include "savefile.h"

extern u32 pressed;
extern bool handledInput;

void Gfx_Init(void);
void Gfx_Update(void);

#endif //_GFX_H_
