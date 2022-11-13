//
// Created by dlopes7 on 11/13/2022.
//

#include <random>

static std::random_device random_device = std::random_device();
static std::mt19937 engine = std::mt19937(random_device());

/**
 * @brief Get a random integer between min and max
 * @param min Minimum value (inclusive)
 * @param max Maximum value (inclusive)
 * @return Random integer between min and max
 */
static int getRandomInt(int min, int max) {
    auto dist = std::uniform_int_distribution<>(min, max);
    auto random_number = dist(engine);
    return random_number;
}

