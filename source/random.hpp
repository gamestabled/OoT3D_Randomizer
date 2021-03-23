#pragma once

#include <array>
#include <cstdlib>
#include <random>

void Random_Init(unsigned int seed);
unsigned int Random(int min, int max);

//Get a random element from a vector or array
template <typename T>
T RandomElement(std::vector<T> &vector, bool erase) {
    int idx = Random(0, vector.size());
    T selected = vector[idx];
    if(erase) {
        vector.erase(vector.begin() + idx);
    }
    return selected;
}
template <typename T, std::size_t size>
T RandomElement(std::array<T, size> arr) {
    return arr[Random(0, arr.size())];
}

//Shuffle items within a vector or array
template <typename T>
void Shuffle(std::vector<T> &vector) {
    for (uint i = 0; i + 1 < vector.size(); i++)
    {
        std::swap(vector[i], vector[Random(i, vector.size())]);
    }
}
template <typename T, std::size_t size>
void Shuffle(std::array<T, size> &arr) {
    for (std::size_t i = 0; i + 1 < arr.size(); i++)
    {
        std::swap(arr[i], arr[Random(i, arr.size())]);
    }
}
