#define NOWINBASEINTERLOCK

#include <windows.h>
#include "citrix_counters.h"
#include <iostream>
#include <conio.h>
auto cleanup() {
    CounterCleanup();
}

int main() {

    // First we must initialize the counter provider
    auto status = CounterInitialize(nullptr, nullptr, nullptr, nullptr);
    if (status != ERROR_SUCCESS) {
        std::cout << "CounterInitialize failed with status " << status << std::endl;
        cleanup();
        return (int)status;
    }

    // Then, create an instance to hold metrics
    auto instance = PerfCreateInstance(CitrixCountersProvider, & IcaSessionGuid, L"Instance 1", 0);
    if (instance == nullptr) {
        std::cout << "Failed to create instance" << std::endl;
        status = GetLastError();
        cleanup();
        return (int)status;

    }

    // This is pretty cool, we can pass a reference to a variable and the counter will be updated
    // automatically with the value of this variable
    ULONG counter_value = 50;
    status = PerfSetCounterRefValue(CitrixCountersProvider, instance, LatencyLastRecorded, &counter_value);
    if (status != ERROR_SUCCESS) {
        std::cout << "Failed to set counter value with status " << status << std::endl;
    }

    // Increment counter_value every second until the user presses any key
    while (!_kbhit()) {
        Sleep(1000);
        counter_value++;
        std::cout << "Setting counter value to " << counter_value << std::endl;
    }

    cleanup();
    return (int)status;
}


