/* 
    Author: Landon Wardle
    Filename: Motor.h
    Purpose: Header file for the motor class
*/

#include "Motor.h"
#include <string>
#include <sstream>

// --------------------
// Motor implementation
// --------------------

Motor::Motor()
{
    name = "unnamed";
    speedPercent = 0;
    enabled = false;
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

    // TODO: For the future this code will handle actually wiring into the Pi itself and turning motors
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

std::string Motor::toString() const
{
    std::stringstream ss;

    ss << "Name = " << name << "\n";
    ss << "Speed = " << speedPercent << "% \n";
    ss << "Enabled = " << (enabled ? "true" : "false") << "\n";

    return ss.str();
}