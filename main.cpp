#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <fstream>

using namespace std;

int hour = 0;
int minute = 0;
int day = 0;
int current_minute = minute;
void timeProcessor();
void save();
void load();

int main() {
    load();
    thread timeThread(timeProcessor);
    while (true) {
    	if(minute != current_minute){
        cout << "Day: " << day << ", " << hour << ":" 
             << setw(2) << setfill('0') << minute << "\n";
        this_thread::sleep_for(chrono::milliseconds(500));
        save();
        current_minute = minute;
    }
    }

    timeThread.join();
    return 0;
}

void timeProcessor() {
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(833));
        minute += 1;
        if (minute >= 60) {
            hour += 1;
            minute = 0;
        }
        if (hour >= 24) {
            day += 1;
            hour = 0;
        }
    }
}

void save() {
    ofstream file("Zimulatorero.SAVE");
    if (file.is_open()) {
        file << "Days: " << day << "\n";
        file << "Hours: " << hour << "\n";
        file << "Minutes: " << minute << "\n";
        file.close();
    }
}

void load() {
    ifstream file("Zimulatorero.SAVE");
    if (file.is_open()) {
        string label;
        file >> label >> day;
        file >> label >> hour;
        file >> label >> minute;
        file.close();
    }
}

