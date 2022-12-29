#include "random.hpp"

#include <random>

static bool init = false;
static std::mt19937_64 generator;
static std::mt19937_64 generator_C;

// Initialize with seed specified
void Random_Init(uint32_t seed) {
    init        = true;
    generator   = std::mt19937_64{ seed };
    generator_C = std::mt19937_64{ seed };
}

// Returns a random integer in range [min, max-1]
uint32_t Random(int min, int max, bool forCosmetic /*= false*/) {
    if (!init) {
        // No seed given, get a random number from device to seed
        const auto seed = static_cast<uint32_t>(std::random_device{}());
        Random_Init(seed);
    }
    std::uniform_int_distribution<uint32_t> distribution(min, max - 1);
    if (forCosmetic) {
        return distribution(generator_C);
    }
    return distribution(generator);
}

// Returns a random floating point number in [0.0, 1.0]
double RandomDouble(bool forCosmetic /*= false*/) {
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    if (forCosmetic) {
        return distribution(generator_C);
    }
    return distribution(generator);
}
