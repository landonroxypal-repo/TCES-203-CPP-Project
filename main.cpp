#include <iostream>
#include <limits>

#include "Car.h"

void printMenu();
double getChangeValue();
int getChoice();

void printDivider() // not public! Temporary function for formatting purposes
{
    std::cout << "-----------------------------------------\n";
}

int main() {
    MecanumCar car;


    int choice = 30, value;
    do{
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
                if(car.cameraEnabled()){
                    car.cameraOff();
                }else car.cameraOn();
                break;
            default:
                std::cout << "Invalid command\n";
                break;
            case 9: 
                std::cout << "Goodbye!\n";
        }
    }while (choice != 9);

    return 0;
}

void printMenu(){
    std::cout << "Control Menu:\n\t1 - Move foward\n\t2 - Move backward\n\t3 - Strafe left\n\t4 - Strafe right"
              << "\n\t5 - Rotate left\n\t6 - Rotate right\n\t7 - stop\n\t8 - Toggle camera\n\t9 - exit\n";
}


// TODO: fix input verification
double getChangeValue(){
    double value;
    std::cout << "Enter option: ";
    
    /*
    while (!(std::cin >> value) || value < 0){
        std::cout << "Invalid value. Enter a int from 0 to 7: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the buffer
    }
        */
    
    return value;
}


int getChoice(){
    char value;
    std::cout << "Enter value: ";
    std::cin >> value;
    
    
    return value - '0';
}