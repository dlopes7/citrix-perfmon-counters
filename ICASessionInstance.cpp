//
// Created by dlopes7 on 11/13/2022.
//

#include "ICASessionInstance.h"
#include "Random.h"
#include <iostream>
#include <thread>

ICASessionInstance::ICASessionInstance(const std::string& name) {
    this->name = name;
    this->counter_latency_last_recorded = Random::getInt(MIN_ICA_SESSION_LATENCY, MAX_ICA_SESSION_LATENCY);
    this->counter_latency_average = 0;
    this->latency_count = 0;
    this->latency_sum = 0;
    this->counter_input_session_bandwidth = 0;
    this->counter_output_session_bandwidth = 0;


    // convert name to PCWSTR
    std::wstring w_name(name.begin(), name.end());
    PCWSTR w_name_ptr = w_name.c_str();


    this->instance = PerfCreateInstance(CitrixICA, &ICASessionGuid, w_name_ptr, 0);
    if (this->instance == nullptr) {
        auto status = GetLastError();
        std::cout << "Failed to create instance with status " << status << std::endl;
    }

    // Use PerfSetCounterRefValue to set the counter references to the instance variables
    auto status = PerfSetCounterRefValue(CitrixICA, this->instance, LatencyLastRecorded, &this->counter_latency_last_recorded);
    if (status != ERROR_SUCCESS) {
        std::cout << "Failed to set counter value with status " << status << std::endl;
    }
    status = PerfSetCounterRefValue(CitrixICA, this->instance, LatencySessionAverage, &this->counter_latency_average);
    if (status != ERROR_SUCCESS) {
        std::cout << "Failed to set counter value with status " << status << std::endl;
    }
    status = PerfSetCounterRefValue(CitrixICA, this->instance, InputSessionBandwidth, &this->counter_input_session_bandwidth);
    if (status != ERROR_SUCCESS) {
        std::cout << "Failed to set counter value with status " << status << std::endl;
    }
    status = PerfSetCounterRefValue(CitrixICA, this->instance, OutputSessionBandwidth, &this->counter_output_session_bandwidth);
    if (status != ERROR_SUCCESS) {
        std::cout << "Failed to set counter value with status " << status << std::endl;
    }

}

ICASessionInstance::~ICASessionInstance() {

    // Attempt to delete the perfmon instance
    std::cout << "Deleting " << this->name << std::endl;
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
        this->counter_latency_last_recorded = Random::getInt(MIN_ICA_SESSION_LATENCY, MAX_ICA_SESSION_LATENCY);

        // Calculate the average
        this->latency_sum += this->counter_latency_last_recorded;
        this->latency_count++;
        this->counter_latency_average = this->latency_sum / this->latency_count;

        this->counter_input_session_bandwidth = Random::getInt(MIN_ICA_SESSION_BANDWIDTH, MAX_ICA_SESSION_BANDWIDTH);
        this->counter_output_session_bandwidth = Random::getInt(MIN_ICA_SESSION_BANDWIDTH, MAX_ICA_SESSION_BANDWIDTH);


        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    std::cout << "Exiting instance " << this->name << std::endl;
}