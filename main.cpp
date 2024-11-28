#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>

int main() {
    int hour = 0;
    int minute = 0;

    while (true) {
    
        std::this_thread::sleep_for(std::chrono::milliseconds(833));
        minute += 1;

        if (minute >= 60) {
            hour += 1;
            minute = 0;
        }

        std::cout << "Time: " << hour << ":" 
                  << std::setw(2) << std::setfill('0') << minute << "\n";
    }

    return 0;
}
