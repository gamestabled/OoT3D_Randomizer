#ifndef _LD_SYMBOLS_H_
#define _LD_SYMBOLS_H_

#include "3ds/types.h"

/*
 * Code size can only be known at link time, so the linker will need a way to
 * calculate it and insert the value in the compiled code.
 * This variable is fake and will not be allocated. Its symbol is defined in the
 * linker script as the total size of the code sections, so that the C code can
 * use that value through the variable's address.
 */
extern char _LD_TEXT_SIZE;
#define NEWCODE_SIZE ((u32)&_LD_TEXT_SIZE)

extern char _LD_TEXT_START;
#define NEWCODE_OFFSET ((u32)&_LD_TEXT_START)

#endif //_LD_SYMBOLS_H_
