#include "random.hpp"

static bool init = false;
static std::mt19937_64 generator;

//Initialize with seed specified
void Random_Init(unsigned int seed) {
    init = true;
    generator = std::mt19937_64{seed};
}

//Returns a random integer in range [min, max-1]
unsigned int Random(int min, int max) {
    if (!init) {
        //No seed given, get a random number from device to seed
        std::random_device rd;
        std::mt19937_64 newgen(rd());
        generator = newgen;
        init = true;
    }
    std::uniform_int_distribution<> distribution(min, max-1);
    return distribution(generator);
}
