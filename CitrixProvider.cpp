//
// Created by dlopes7 on 11/13/2022.
//

#include "CitrixProvider.h"
#include "Random.h"
#include <iostream>
#include <thread>


CitrixProvider::CitrixProvider() {

    auto status = CounterInitialize(nullptr, nullptr, nullptr, nullptr);
    if (status != ERROR_SUCCESS) {
        std::cout << "CounterInitialize failed with status " << status << std::endl;
    }
}

CitrixProvider::~CitrixProvider() {
    CounterCleanup();
}


void CitrixProvider::createICASessionInstance(const std::string &name) {

    if (instances.size() >= CITRIX_ICA_SESSION_MAX_INSTANCES) {
        std::cout << "Max instances reached, cannot create instance " << name << std::endl;
        return;
    }
    // call runICASessionInstance in a new thread
    std::thread t(&CitrixProvider::runICASessionInstance, this, name);
    t.detach();

}
void CitrixProvider::runICASessionInstance(const std::string &name) {
    auto instance = new ICASessionInstance(name);
    instances.push_back(instance);

    int duration = Random::getInt(MIN_ICA_SESSION_INSTANCE_DURATION, MAX_ICA_SESSION_INSTANCE_DURATION);

    // Start a new thread to run the instance
    std::thread t(&ICASessionInstance::run, instance, duration);
    t.join();

    instances.erase(std::remove(instances.begin(), instances.end(), instance), instances.end());
    // Delete the instance
    delete instance;

}
