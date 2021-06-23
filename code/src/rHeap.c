#include "rHeap.h"
#include <stddef.h>

#include "z3D/z3D.h"

char rHeap[sizeof(Actor) + 16]; // TODO: Increase if needed
void* rHeap_Next = NULL;

void rHeap_Init(void) {
    rHeap_Next = &rHeap[0];
}

void* rHeap_Alloc(u32 bytes) {
    u32 rem = bytes % 16;
    if (rem)
        bytes += 16 - rem;

    void* result = rHeap_Next;
    rHeap_Next = (char*)rHeap_Next + bytes;
    return result;
}
