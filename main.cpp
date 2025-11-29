#include <iostream>
#include "Car.h"

void printDivider() // not public! Temporary function for formatting purposes
{
    std::cout << "-----------------------------------------\n";
}

int main() {
    MecanumCar funAwesomeCar;

    std::cout << funAwesomeCar.toString();

    return 0;
}