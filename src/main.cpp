#include "provider.cpp"
#include <iostream>
#include <conio.h>

int main() {
    // Create a new CitrixProvider
    auto provider = CitrixProvider();


    std::cout << "Press any key to exit" << std::endl;
    auto instance_counter = 0;
    while (!_kbhit()) {
        instance_counter++;
        auto instance_name = "Instance " + std::to_string(instance_counter % 5 + 1);
        provider.createICASessionInstance(instance_name);
        Sleep(1000);
    }


    return 0;
}


