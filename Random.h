//
// Created by dlopes7 on 11/13/2022.
//

#ifndef CITRIX_COUNTERS_RANDOM_H
#define CITRIX_COUNTERS_RANDOM_H

#include <random>

class Random {

    public:
        // Constructor
        Random();

        // Destructor
        ~Random();

        // Methods
        static int getInt(int min, int max);

    private:
        static std::random_device random_device; // create object for seeding
        static std::mt19937 engine; // create engine and seed it


};


#endif //CITRIX_COUNTERS_RANDOM_H
