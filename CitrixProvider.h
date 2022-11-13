//
// Created by dlopes7 on 11/13/2022.
//

#ifndef CITRIX_COUNTERS_CITRIXPROVIDER_H
#define CITRIX_COUNTERS_CITRIXPROVIDER_H

#include <windows.h>
#include <vector>
#include "citrix_counters.h"
#include "ICASessionInstance.h"

static const int CITRIX_ICA_SESSION_MAX_INSTANCES = 5;
static const int MIN_ICA_SESSION_INSTANCE_DURATION = 120;
static const int MAX_ICA_SESSION_INSTANCE_DURATION = 300;


class CitrixProvider {
    public:
        // Constructor
        CitrixProvider();

        // Destructor
        ~CitrixProvider();

        void createICASessionInstance(const std::string &name);


    private:
        // vector of current instances
        std::vector<ICASessionInstance*> instances;
        void runICASessionInstance(const std::string &name);
};


#endif //CITRIX_COUNTERS_CITRIXPROVIDER_H
