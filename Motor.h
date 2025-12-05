/* 
    Author: Landon Wardle
    Filename: Motor.h
    Purpose: Header file for the motor class
*/

#ifndef MOTOR
#define MOTOR

#include <string>

const int DEFAULT_SPEED = 100;

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
    int forwardPin;
    int backwardPin;
public:
    Motor();
    Motor(const std::string& motorName);
    Motor(const std::string& motorName, int backPin, int forPin);

    void setSpeed(int newSpeedPercent);
    int getSpeed() const;

    void disable();
    bool isEnabled() const;

    std::string getName() const;
    std::string toString() const;

    void setForwardPin(int fowardPin);
    void setBackwardPin(int backwardPin);
};

#endif