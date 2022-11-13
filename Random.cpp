//
// Created by dlopes7 on 11/13/2022.
//

#include "Random.h"

std::random_device Random::random_device = std::random_device();
std::mt19937 Random::engine = std::mt19937(Random::random_device());

Random::Random() = default;
Random::~Random() = default;

int Random::getInt(int min, int max) {
    auto dist = std::uniform_int_distribution<>(min, max);
    auto random_number = dist(Random::engine); // finally get a pseudo-random integer number
    return random_number;
}
