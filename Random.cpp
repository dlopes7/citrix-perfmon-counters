//
// Created by dlopes7 on 11/13/2022.
//

#include <random>

static std::random_device random_device = std::random_device();
static std::mt19937 engine  = std::mt19937(random_device());

class Random {

public:

    // Methods
    static int getInt(int min, int max) {
        auto dist = std::uniform_int_distribution<>(min, max);
        auto random_number = dist(engine); // finally get a pseudo-random integer number
        return random_number;
    }

};

