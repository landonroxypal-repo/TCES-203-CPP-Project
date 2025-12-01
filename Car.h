#ifndef CAR
#define CAR

#include <iostream>
#include "Motor.h"
#include <vector>

/*
 * PiCamera
 * --------
 * Represents a very simple Pi Camera module.
 * We only track whether it is streaming or not.
 */
class PiCamera {
private:
    bool streaming;

public:
    PiCamera();

    void startStream();
    void stopStream();
    void captureFrame(double x, double y);
    bool isStreaming() const;
};

// The car we have does not actually have the camera, so I am not sure if we will use this class actively

// Enumerated type for high-level movement commands.
enum class MovementCommand {
    MoveForward,
    MoveBackward,
    StrafeLeft,
    StrafeRight,
    RotateLeft,
    RotateRight,
    Stop
};

/*
 * MecanumCar
 * ----------
 * This class models a 4-wheel Mecanum car using object composition:
 *
 *  - four Motor objects (front-left, front-right, rear-left, rear-right)
 *  - one PiCamera object
 *
 * It also stores the car pose in a 2D space used by the visualization GUI:
 *
 *  - x, y: Cartesian coordinates in "map units"
 *  - headingDeg: orientation in degrees, where 0 means "facing up" on the map.
 */
class MecanumCar {
private:
    Motor frontLeft;
    Motor frontRight;
    Motor rearLeft;
    Motor rearRight;
    PiCamera camera;

    double x;           // current x position
    double y;           // current y position
    double headingDeg;  // current heading in degrees [0, 360)

    void updatePose(double dx, double dy, double dThetaDeg);

public:
    MecanumCar();

    void moveForward(double distance);
    void moveBackward(double distance);
    void strafeLeft(double distance);
    void strafeRight(double distance);
    void rotateLeft(double angleDeg);
    void rotateRight(double angleDeg);

    void stopAllMotors();

    void cameraOn();
    void cameraOff();

    double getX() const;
    double getY() const;
    double getHeadingDeg() const;

    Motor getFrontLeftMotor() const;
    Motor getFrontRightMotor() const;
    Motor getRearLeftMotor() const;
    Motor getRearRightMotor() const;

    void applyCommand(MovementCommand cmd, double value);

    std::string toString() const;

    std::vector<Motor> getMotors() const;
};

#endif