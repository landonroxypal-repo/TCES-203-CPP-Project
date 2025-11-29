/* 
    Author: Landon Wardle
    Filename: Motor.h
    Purpose: Header file for the motor class
*/

#ifndef MOTOR
#define MOTOR

#include <string>
#include "wiringPi.h"

/*
 * Motor
 * -----
 * Represents a single DC motor driven by an L298N driver.
 * In this simplified model we only track:
 *  - a human-readable name (e.g., "front-left")
 *  - current speed as a percentage in the range [-100, 100]
 *  - whether the motor is enabled
 *
 * Implementation details (e.g., GPIO pins, PWM signals) are HIDDEN.
 */

class Motor {
private:
    std::string name;
    int speedPercent;   // from -100 to +100
    bool enabled;

public:
    Motor();
    Motor(const std::string& motorName);

    void setSpeed(int newSpeedPercent);
    int getSpeed() const;

    void enable();
    void disable();
    bool isEnabled() const;

    std::string getName() const;
    std::string toString() const;
};

#endif