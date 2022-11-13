//
// Created by dlopes7 on 11/13/2022.
//

#ifndef CITRIX_COUNTERS_ICASESSIONINSTANCE_H
#define CITRIX_COUNTERS_ICASESSIONINSTANCE_H

#include <windows.h>
#include <string>
#include "citrix_counters.h"

static const int MIN_ICA_SESSION_LATENCY = 5;
static const int MAX_ICA_SESSION_LATENCY = 30;

class ICASessionInstance {

    public:
        // Constructor
        explicit ICASessionInstance(const std::string &name);

        // Destructor
        ~ICASessionInstance();

        void run(int ticks);

    private:
        // Reference to the perfmon instance
        // This needs to be deleted when this is destroyed
        PPERF_COUNTERSET_INSTANCE instance;

        // Attributes
        std::string name;

        // Perfmon counters
        unsigned long latency_last_recorded;

};


#endif //CITRIX_COUNTERS_ICASESSIONINSTANCE_H
