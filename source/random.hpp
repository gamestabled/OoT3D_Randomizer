#pragma once
#include <stdlib.h>
#include <random>

static bool init = false;
static unsigned int state;

void Random_Init(unsigned int seed) {
    state = 0;
    init = true;
    srand(seed);
}

unsigned int Random() {
    if (!init) {
        state = 0;
        init = true;
    }
    state = rand();
    return state;
}
