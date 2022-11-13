//
// Created by dlopes7 on 11/13/2022.
//

#include "ICASessionInstance.h"
#include "Random.h"
#include <iostream>
#include <thread>

ICASessionInstance::ICASessionInstance(const std::string& name) {
    this->name = name;
    this->latency_last_recorded = 0;  // TODO - Should be a random value

    // convert name to PCWSTR
    std::wstring w_name(name.begin(), name.end());
    PCWSTR w_name_ptr = w_name.c_str();


    this->instance = PerfCreateInstance(CitrixICA, &ICASessionGuid, w_name_ptr, 0);
    if (this->instance == nullptr) {
        auto status = GetLastError();
        std::cout << "Failed to create instance with status " << status << std::endl;
    }

    // Use PerfSetCounterRefValue to set the counter references to the instance variables
    auto status = PerfSetCounterRefValue(CitrixICA, this->instance, LatencyLastRecorded, &this->latency_last_recorded);
    if (status != ERROR_SUCCESS) {
        std::cout << "Failed to set counter value with status " << status << std::endl;
    }
}

ICASessionInstance::~ICASessionInstance() {

    // Attempt to delete the perfmon instance
    std::cout << "Deleting perfmon instance" << std::endl;
    auto status = PerfDeleteInstance(CitrixICA, instance);
    if (status != ERROR_SUCCESS) {
        std::cout << "Failed to delete perfmon instance with status " << status << std::endl;
    }

}

void ICASessionInstance::run(int ticks) {
    std::cout << "Running instance '" << this->name << "' for " << ticks << " ticks" << std::endl;
    int execution_count = 0;
    while (execution_count < ticks) {
        execution_count++;

        // Update all counters every second
        this->latency_last_recorded = Random::getInt(5, 30);

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    std::cout << "Exiting instance " << this->name << std::endl;
}