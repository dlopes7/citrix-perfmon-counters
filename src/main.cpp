#include "provider.cpp"
#include <iostream>
#include <conio.h>

int main() {
    // Create a new CitrixProvider
    CitrixProvider provider;


    std::cout << "Press any key to exit" << std::endl;
    auto instance_counter = 0;
    while (!_kbhit()) {
        instance_counter++;
        auto instance_name = "Instance " + std::to_string(instance_counter);
        provider.createICASessionInstance(instance_name);
        Sleep(1000);
    }


    return 0;
}


