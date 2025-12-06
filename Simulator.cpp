/* 
    Authors: Landon Wardle and Robert Cromer
    Purpose: Implementation of the simulator class.
    Filename: Simulator.cpp
*/

#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <cmath>

#include "Car.h"
#include "Simulator.h"

// Size of the "map" shown in the console.
static const int DEFAULT_MAP_WIDTH  = 21;
static const int DEFAULT_MAP_HEIGHT = 21;

// Convert world coordinates (x, y) to map indices.
// We assume the world origin (0,0) is at the center of the map.
void Simulator::worldToMap(double x, double y, int& outRow, int& outCol)
{
    int centerRow = mapHeight / 2;
    int centerCol = mapWidth / 2;

    // y grows "up", rows grow "down", so row decreases when y increases.
    outRow = centerRow - static_cast<int>(std::round(y));
    outCol = centerCol + static_cast<int>(std::round(x));
}

Simulator::Simulator() {
    car = nullptr; // by default, we do not have a car!
    mapHeight = DEFAULT_MAP_HEIGHT;
    mapWidth = DEFAULT_MAP_WIDTH;
}

Simulator::~Simulator() {
    car = nullptr; // stop dangling pointer!
}

Simulator::Simulator(MecanumCar& newCar, int height, int width) {
    setCar(newCar);
    mapHeight = height;
    mapWidth = width;
}

void Simulator::setCar(MecanumCar& newCar) {
    car = &newCar;
}

MecanumCar Simulator::getCar() {
    return *car;
}

bool Simulator::hasCar() { // Checks if we have a car! VERY important function!
    return car != nullptr;
}

// Draw a simple ASCII map with the car at its current position.
void Simulator::drawMap()
{
    if (hasCar()) {
        MecanumCar currentCar = getCar();

        int carRow = 0;
        int carCol = 0;
        worldToMap(currentCar.getX(), currentCar.getY(), carRow, carCol);

        // Clear screen (simple portable trick).
        std::cout << "\x1B[2J\x1B[H";
        std::cout << currentCar.toString();

        std::cout << "\nMap Legend: C = car, . = empty\n\n";

        for (int row = 0; row < mapHeight; ++row) {
            for (int col = 0; col < mapWidth; ++col) {
                if (row == carRow && col == carCol) {
                    std::cout << 'C';
                } else {
                    std::cout << '.';
                }
            }
            std::cout << "\n";
        }

        std::cout << "\n";
    } else {
        std::cout << "No car set, cannot display map!";
    }
}