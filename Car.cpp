#include "Car.h"
#include <string>
#include <math.h>
#include <sstream>

#include <iostream> // only for the camera

// -----------------------
// PiCamera implementation
// -----------------------

PiCamera::PiCamera()
{
    streaming = false;
}

void PiCamera::startStream()
{
    streaming = true;
}

void PiCamera::stopStream()
{
    streaming = false;
}

bool PiCamera::isStreaming() const
{
    return streaming;
}

void PiCamera::captureFrame(double x, double y) 
{
    // BAD OOP PRACTICE WOOOO!!!!!

    std::cout << "Camera capturing frame at (" << x << "," << y << ")";
}


// ------------------------
// MecanumCar implementation
// ------------------------

//TODO: The code below may have to be changed on how it constructs the motors because we need pin information!

MecanumCar::MecanumCar() 
{
   frontLeft = Motor("front-left");
   frontRight = Motor("front-right");
   rearLeft = Motor("rear-left");
   rearRight = Motor("rear-right");
   x = 0.0;
   y = 0.0;
   headingDeg = 0.0;

   // Note: Camera not present because C++ constructs it by default!
}

void MecanumCar::updatePose(double dx, double dy, double dThetaDeg)
{
    x += dx;
    y += dy;
    headingDeg += dThetaDeg;

    headingDeg = std::fmod(headingDeg, 360.0f);
}

void MecanumCar::moveForward(double distance)
{
    updatePose(0, distance, 0);

    frontLeft.setSpeed(50);
    frontRight.setSpeed(50);
    rearLeft.setSpeed(50);
    rearRight.setSpeed(50);
}

void MecanumCar::moveBackward(double distance)
{
    updatePose(0, -distance, 0);

    frontLeft.setSpeed(-50);
    frontRight.setSpeed(-50);
    rearLeft.setSpeed(-50);
    rearRight.setSpeed(-50);
}

void MecanumCar::strafeLeft(double distance)
{
    updatePose(-distance, 0, 0);

    frontLeft.setSpeed(-50);
    frontRight.setSpeed(50);
    rearLeft.setSpeed(50);
    rearRight.setSpeed(-50);
}

void MecanumCar::strafeRight(double distance)
{
    updatePose(distance, 0, 0);

    frontLeft.setSpeed(50);
    frontRight.setSpeed(-50);
    rearLeft.setSpeed(-50);
    rearRight.setSpeed(50);
}

void MecanumCar::rotateLeft(double angleDeg)
{
    updatePose(0, 0, angleDeg);

    frontLeft.setSpeed(-50);
    frontRight.setSpeed(50);
    rearLeft.setSpeed(-50);
    rearRight.setSpeed(50);
}

void MecanumCar::rotateRight(double angleDeg)
{
    updatePose(0, 0, -angleDeg);

    frontLeft.setSpeed(50);
    frontRight.setSpeed(-50);
    rearLeft.setSpeed(50);
    rearRight.setSpeed(-50);
}

void MecanumCar::stopAllMotors()
{
    frontLeft.setSpeed(0);
    frontRight.setSpeed(0);
    rearLeft.setSpeed(0);
    rearRight.setSpeed(0);
}

void MecanumCar::cameraOn()
{
    camera.startStream();
}

void MecanumCar::cameraOff()
{
    camera.stopStream();
}

double MecanumCar::getX() const
{
    return x;
}

double MecanumCar::getY() const
{
    return y;
}

double MecanumCar::getHeadingDeg() const
{
    return headingDeg;
}

Motor MecanumCar::getFrontLeftMotor() const
{
    return frontLeft;
}

Motor MecanumCar::getFrontRightMotor() const
{
    return frontRight;
}

Motor MecanumCar::getRearLeftMotor() const
{
    return rearLeft;
}

Motor MecanumCar::getRearRightMotor() const
{
    return rearRight;
}

void MecanumCar::applyCommand(MovementCommand cmd, double value = 0) //Added a default value so stop can be called w/o needing to pass in a double
{
    // Note: no curly braces requried because no new variables are defined in any of the switch cases!

    switch(cmd) {
        case MovementCommand::MoveForward:
            moveForward(value);
            break;
        case MovementCommand::MoveBackward:
            moveBackward(value);
            break;
        case MovementCommand::RotateLeft:
            rotateLeft(value);
            break;
        case MovementCommand::RotateRight:
            rotateRight(value);
            break;
        case MovementCommand::StrafeLeft:
            strafeLeft(value);
            break;
        case MovementCommand::StrafeRight:
            strafeRight(value);
            break;
        case MovementCommand::Stop:
            stopAllMotors();
            break;    
    }
}

std::vector<Motor> MecanumCar::getMotors() const
{
    std::vector<Motor> motors = {
        getFrontLeftMotor(),
         getFrontRightMotor(), 
         getRearLeftMotor(), 
         getRearRightMotor()
    };

    return motors;
}

std::string getDivider()
{
    return "-----------------------------------------\n";
}

std::string MecanumCar::toString() const
{
    std::stringstream ss;
    ss << "Car:\n" << getDivider();
    ss << "Position = (" << x << "," <<y << ")\n";
    ss << "Heading = " << headingDeg << static_cast<char>(248) << "\n";
    ss << "Camera State = " << (camera.isStreaming() ? "On" : "Off") << "\n";

    ss << "Motors:\n" << getDivider();

    for (Motor motor : getMotors()) {
        ss << motor.toString();
        ss << getDivider();
    }

    return ss.str();
}