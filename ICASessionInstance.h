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

static const int MIN_ICA_SESSION_BANDWIDTH = 60;
static const int MAX_ICA_SESSION_BANDWIDTH = 200;

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
        unsigned long counter_latency_last_recorded;
        unsigned long counter_latency_average;
        unsigned long counter_input_session_bandwidth;
        unsigned long counter_output_session_bandwidth;

        // Used to calculate the counters
        unsigned long latency_count;
        unsigned long latency_sum;


};


#endif //CITRIX_COUNTERS_ICASESSIONINSTANCE_H
