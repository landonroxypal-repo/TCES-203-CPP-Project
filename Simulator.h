#ifndef SIMULATOR
#define SIMULATOR

#include "Car.h"

class Simulator {
    private:
        MecanumCar* car;
        int mapHeight;
        int mapWidth;
        void worldToMap(double x, double y, int& outRow, int& outCol);

    public:
        Simulator();
        Simulator(MecanumCar& newCar, int height, int width); 
        ~Simulator();

        MecanumCar getCar();
        void setCar(MecanumCar& newCar);
        bool hasCar();
        void drawMap();
};

#endif