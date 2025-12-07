/* 
    Authors: Landon Wardle and Robert Cromer
    Purpose: Entry point of the project.
    Filename: main.cpp
*/

#include <iostream>
#include <limits>

#include "Car.h"
#include "Simulator.h"

const int EXIT_CHOICE = 0;

//TODO: NEED LOTS OF INPUT VERIFICATION!!

void printMenu();
double getChangeValue();
int getChoice();
void selectionSort(int array[], int size);
void swap(int array[], int a, int b);

void printDivider() { // not public! Temporary function for formatting purposes
    std::cout << "-----------------------------------------\n";
}

int main() {
    Simulator* sim = nullptr;

    MecanumCar car;

    #if !defined(USING_PI) && !defined(MOCK)
        sim = new Simulator(car, 31, 31);
    #endif

    int choice = -1, value = 0;
    do {
        printMenu();
        choice = getChoice();
        
        if (sim != nullptr && choice >= 1 && choice <= 6) {
            value = getChangeValue(); // This code will not trigger in the case of working w/ the real car!
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
            case 9: {
                int cmdnum = 0;
                std::cout << "Enter the number of commands to sort: ";
                std::cin >> cmdnum;

                int cmds[cmdnum];

                for (int index = 0; index < cmdnum; index++) {
                    cmds[index] = getChoice();
                }

                selectionSort(cmds, cmdnum);

                std::cout << "Your commands in sorted order are: ";
                for (int &val : cmds) {
                    std::cout << val << ' ';
                }
                std::cout << std::endl;

                break;
            }
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

void swap(int array[], int a, int b) {
    int temp = array[a];

    array[a] = array[b];
    array[b] = temp;
}

void selectionSort(int array[], int size) {
    int left = 0;
    int right = 0;
    // using two pointer approach for sorting

    for (left = 0; left < size - 1; left++) {
        int smallestCmd = array[left];
        int smallestIndex = left;

        for (right = left + 1; right < size; right++) {
            if (array[right] < smallestCmd) {
                smallestCmd = array[right];
                smallestIndex = right;
            }
        }

        swap(array, left, smallestIndex);
    }
}

void printMenu(){
    std::cout << "==Control Menu:==\n\t1 - Move foward\n\t2 - Move backward\n\t3 - Strafe left\n\t4 - Strafe right"
              << "\n\t5 - Rotate left\n\t6 - Rotate right\n\t7 - Stop\n\t8 - Toggle camera\n\t9 - Sort Commands\n\t0 - Exit\n";
}

// TODO: fix input verification  
double getChangeValue() {
    double value;
    std::cout << "Enter value: ";
    std::cin >> value; // TEMP CODE FOR SIM TESTING!
    
    while (std::cin.fail()){
        std::cout << "Invalid value. Enter a value greater than 9: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the buffer
        std::cin >> value;
    }
    
    return value;
}

int getChoice() {
    int value;
    std::cout << "Enter option: ";
    std::cin >> value;

    while (std::cin.fail() || !(value >= 0 && value <= 9)){
        std::cout << "Invalid value. Enter a int from 0 to 9: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the buffer

        std::cin >> value;
    }
    
    return value;
}

