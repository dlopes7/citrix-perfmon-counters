//
// Created by dlopes7 on 11/13/2022.
//

#include <iostream>
#include <thread>
#include <windows.h>
#include <vector>
#include "citrix_counters.h"
#include "ICASessionInstance.cpp"

static const int CITRIX_ICA_SESSION_MAX_INSTANCES = 5;
static const int MIN_ICA_SESSION_INSTANCE_DURATION = 120;
static const int MAX_ICA_SESSION_INSTANCE_DURATION = 300;


class CitrixProvider {
public:
    // Constructor
    CitrixProvider() {

        auto status = CounterInitialize();
        if (status != ERROR_SUCCESS) {
            std::cout << "CounterInitialize failed with status " << status << std::endl;
        }
    }

    // Destructor
    ~CitrixProvider() {
        CounterCleanup();
    }

    void createICASessionInstance(const std::string &name) {

        if (instances.size() >= CITRIX_ICA_SESSION_MAX_INSTANCES) {
            std::cout << "Max instances reached, cannot create " << name << std::endl;
            return;
        }
        // call runICASessionInstance in a new thread
        std::thread t(&CitrixProvider::runICASessionInstance, this, name);
        t.detach();

    }


private:
    // vector of current instances
    std::vector<ICASessionInstance*> instances;

    void runICASessionInstance(const std::string &name) {
        auto instance = new ICASessionInstance(name);
        instances.push_back(instance);

        int duration = Random::getInt(MIN_ICA_SESSION_INSTANCE_DURATION, MAX_ICA_SESSION_INSTANCE_DURATION);

        // Start a new thread to run the instance
        std::thread t(&ICASessionInstance::run, instance, duration);
        t.join();

        instances.erase(std::remove(instances.begin(), instances.end(), instance), instances.end());
        delete instance;

    }
};
