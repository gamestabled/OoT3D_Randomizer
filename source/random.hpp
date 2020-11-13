#pragma once

static bool init = false;
static unsigned int state;

void Random_Init(unsigned int seed) {
    state = seed;
    init = true;
}

unsigned int Random() {
    if (!init) {
        state = 0;
        init = true;
    }
    state *= 3;
    state += 17; //TODO make this way more random looking
    return state;
}