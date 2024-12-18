#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <fstream>
#include <vector>

using namespace std;

double energy = 0;
int hour = 0;
int minute = 0;
int day = 0;

struct Tile {
    string type;
};

vector<vector<Tile>> world(1, vector<Tile>(2));

void timeProcessor();
void save();
void load();
void energyGenerator();
void displayWorld();

int main() {
    load();
    world[0][0].type = "land";
    world[0][1].type = "water";
    thread timeThread(timeProcessor);
    thread energyThread(energyGenerator);

    while (true) {
        {
            cout << "Energy: " << energy << "\n";
            cout << "Day: " << day << ", " << hour << ":" << minute << "\n";
            displayWorld();
            this_thread::sleep_for(chrono::seconds(1));
        }
        save();
    }

    timeThread.join();
    energyThread.join();

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

void energyGenerator() {
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(100));
        energy += 0.1;
    }
}

void save() {
    ofstream file("Zimulatorero.SAVE");
    if (file.is_open()) {
        file << "Days: " << day << "\n";
        file << "Hours: " << hour << "\n";
        file << "Minutes: " << minute << "\n";
        file << "Energy: " << energy << "\n";
        file.close();
    } else {
        cerr << "Error: Unable to save data.\n";
    }
}

void load() {
    ifstream file("Zimulatorero.SAVE");
    if (file.is_open()) {
        string label;
        file >> label >> day;
        file >> label >> hour;
        file >> label >> minute;
        file >> label >> energy;
        file.close();
    } else {
        cerr << "Warning: Save file not found. Starting fresh.\n";
    }
}

void displayWorld() {
    cout << "World: ";
    for (const auto& row : world) {
        for (const auto& tile : row) {
            cout << tile.type << " ";
        }
    }
    cout << endl;
}

