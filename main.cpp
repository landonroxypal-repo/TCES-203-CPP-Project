#include <iostream>
#include <limits>

#include "Car.h"
#include "Simulator.h"

const int EXIT_CHOICE = 0;

void printMenu();
double getChangeValue();
int getChoice();

void printDivider() { // not public! Temporary function for formatting purposes
    std::cout << "-----------------------------------------\n";
}

int main() {
    Simulator* sim = nullptr;

    MecanumCar car;

    #if !defined(USING_PI) && !defined(MOCK)
        sim = new Simulator(car, 31, 31);
    #endif

    int choice = -1, value;
    do {
        printMenu();
        choice = getChoice();
        
        if (choice >= 1 && choice <= 6){
            value = getChangeValue();
        }

        switch(choice){
            case 1:
                car.applyCommand(MovementCommand::MoveForward, value);
                break;
            case 2: 
                car.applyCommand(MovementCommand::MoveBackward, value);
                break;
            case 3: 
                car.applyCommand(MovementCommand::StrafeLeft, value);
                break;
            case 4: 
                car.applyCommand(MovementCommand::StrafeRight, value);
                break;
            case 5:
                car.applyCommand(MovementCommand::RotateLeft, value);
                break;
            case 6:
                car.applyCommand(MovementCommand::RotateRight, value);
                break;
            case 7:
                car.applyCommand(MovementCommand::Stop);
                break;
            case 8:
                if (car.cameraEnabled()) {
                    car.cameraOff();
                } else car.cameraOn();
                break;
            case 9:
                std::cout << car.toString();
                break;
            default:
                std::cout << "Invalid command\n";
                break;
            case EXIT_CHOICE: 
                std::cout << "Goodbye!\n";
        }
        
        if (sim != nullptr && choice != EXIT_CHOICE && choice != 9) {
            sim->drawMap();
        }
    } while (choice != EXIT_CHOICE);

    if (sim != nullptr) {
        delete sim;
        sim = nullptr;
    }

    return 0;
}

void printMenu(){
    std::cout << "==Control Menu:==\n\t1 - Move foward\n\t2 - Move backward\n\t3 - Strafe left\n\t4 - Strafe right"
              << "\n\t5 - Rotate left\n\t6 - Rotate right\n\t7 - stop\n\t8 - Toggle camera\n\t9 - Display car\n\t0 - exit\n";
}


// TODO: fix input verification  
double getChangeValue() {
    double value;
    std::cout << "Enter value: ";
    std::cin >> value; // TEMP CODE FOR SIM TESTING!
    
    /*
    while (!(std::cin >> value) || value < 0){
        std::cout << "Invalid value. Enter a int from 0 to 7: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the buffer
    }
        */
    
    return value;
}

int getChoice() {
    char value;
    std::cout << "Enter option: ";
    std::cin >> value;
    
    return value - '0';
}

