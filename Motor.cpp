/* 
    Author: Landon Wardle
    Filename: Motor.h
    Purpose: Header file for the motor class
*/

#include "Motor.h"
#include <string>
#include <sstream>

#ifdef USING_PI // flag to determine if we use wiring pi or not, used w/ pre-processor cmd to set
    #include <wiringPi.h>
#endif

#ifdef MOCK // flag to determine if we use the mock version of wiring pi or not, used w/ pre-processor cmd to set
   #include "wiringPi.h"
#endif

// --------------------
// Motor implementation
// --------------------

Motor::Motor()
{
    name = "unnamed";
    speedPercent = 0;
    enabled = false;
    forwardPin = 0;
    backwardPin = 0;
}

Motor::Motor(const std::string& motorName, int backPin, int forPin)
{
    name = motorName;
    speedPercent = 0;
    enabled = false;

    forwardPin = backPin;
    backwardPin = forPin;

    #ifdef __WIRING_PI_H__
        pinMode(backwardPin, OUTPUT);
        pinMode(forwardPin, OUTPUT);
    #endif
}

Motor::Motor(const std::string& motorName)
{
    name = motorName;
    speedPercent = 0;
    enabled = false;
}

void Motor::setSpeed(int newSpeedPercent)
{
    if (newSpeedPercent < -100) {
        newSpeedPercent = -100;
    } else if (newSpeedPercent > 100) {
        newSpeedPercent = 100;
    }

    speedPercent = newSpeedPercent;

    // The cars were NOT wired with PWM enabled, so we had to opt for the below approach instead:

    #ifdef __WIRING_PI_H__
        if (newSpeedPercent > 0) {
            digitalWrite(forwardPin, HIGH);
            digitalWrite(backwardPin, LOW);
        } else if (newSpeedPercent < 0) {
            digitalWrite(forwardPin, LOW);
            digitalWrite(backwardPin, HIGH);
        } else {
            digitalWrite(forwardPin, LOW);
            digitalWrite(backwardPin, LOW);
        }
    #endif
}

int Motor::getSpeed() const
{
    return speedPercent;
}

void Motor::disable()
{
    setSpeed(0);
}

bool Motor::isEnabled() const
{
    return getSpeed() != 0;
}

std::string Motor::getName() const
{
    return name;
}

std::string Motor::toString() const // Can you tell I like java yet?
{
    std::stringstream ss;

    ss << "Name = " << name << "\n";
    ss << "Speed = " << speedPercent << "% \n";
    ss << "Enabled = " << (enabled ? "true" : "false") << "\n";

    return ss.str();
}