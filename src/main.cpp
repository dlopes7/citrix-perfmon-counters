#define NOWINBASEINTERLOCK

#include "CitrixProvider.cpp"
#include <iostream>
#include <conio.h>

using namespace std;


int main() {
    // Create a new CitrixProvider
    CitrixProvider provider;


    cout << "Press any key to exit" << endl;
    auto instance_counter = 0;
    while (!_kbhit()) {
        instance_counter++;
        auto instance_name = "Instance " + to_string(instance_counter);
        provider.createICASessionInstance(instance_name);
        Sleep(1000);
    }


    return 0;
}


