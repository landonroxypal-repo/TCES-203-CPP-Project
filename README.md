The code in this folder operates a car in c++ for a raspberry pi.

Authors: Landon Wardle and Robert Cromer

# Compilation

To compile and run our project, please run this command in the terminal with the current directory set 
to where the main.cpp file is located.


If on a Raspberry Pi B:
    g++ -DUSING_PI=1 -std=c++11 main.cpp Car.cpp motor.cpp Simulator.cpp -lwiringpi -o TCES203Proj2
    ./TCES203Proj2

    Note: The above compilation command WILL fail if you do not have a Raspberry Pi B with the wiringPi.h header file installed!

If simulating a mock Raspberry Pi B in an IDE:
    g++ -DMOCK=1 -std=c++11 main.cpp Car.cpp motor.cpp wiringPi.cpp Simulator.cpp -o TCES203Proj2
    ./TCES203Proj2

Otherwise (simulation mode):
    g++ -std=c++11 main.cpp Car.cpp Motor.cpp Simulator.cpp -o TCES203Proj2
    ./TCES203Proj2

(Note that the compilation command is TWO lines, if it is pasted in as one line the compiler will return 1 and fail to run the code.)

# Classes and Files

Files:
 - main.cpp: The entry point of the program. Responsible for initializing the car class and simulator to provide the user with text-based input.
 - Car.h: A Mecanum Car class that sits at the topmost level of the program. It is responsible for integrating Motors and the Pi Camera
   into a single unit that can be controlled easily from function calls. 
 - Car.cpp: The implementation of the Car class defined in the header file Car.h.
 - Motor.h: A single motor connected from a L289N motor driver module to the Raspberry PI. Most basic unit of the car; can be 
   set to rotate at a specific speed or shut down quickly.
 - Motor.cpp: The implementation of the Motor class defined in Motor.h.
 - Simulator.h: A small simulation class that takes in a Mecanum car and a grid size to simulate where the car is in physical space.
 - Simulator.cpp: The implementation of the simulation class defined in Simulator.h.

# Simulator

The simulator is automatically toggled on or off for the program given the compilation.

The simulator displays the car within a grid and uses basic trignometry to simulate the car's movement within an ideal lab with no obstacles. The simulator has the same interface as driving the real car so that testing can be quickly done in the simulation then carried out to a real-world car without hurdle.

# Test Scenarios

Scenarios:
    Note that all scenarios were tested in the simulation mode.

 - Scenario 1:

    Commands Run:
        1 - Move forward 5 units
        2 - Move backward 5 units
        3 - Rotate Right 45 degrees
        1 - Move forward 5 units
        2 - Move backward 5 units

    Expectation:
        The car should move forward, then back. It should then rotate 45 degrees and move forward diagonally and backward diagonally.

    Observation (simulator output):
        The car moved forward and then backwards 5 units each, resetting to its initial position. Then it rotated 45 degrees and then diagonally moved forward and backward 5 units.

 - Scenario 2:

     Commands Run:
        1 - Move forward 5 units
        3 - Strafe left 5 units
        2 - Move backward 5 units
        4 - Strafe right 5 units
        7 - Stop

    Expectation:
        The car should finish traversing its path right where it started with a small square loop, then force stop all motors.

    Observation (simulator output):
        The car behaved as expected. It traversed a path where it moved forward 5 units, moved left 5 units, backward 5 units, and right 5 units to ultimately end up in the location it started. The car also force stopped all motors as expected.

 - Scenario 3:

     Commands Run:
        1 - Move forward 5 units
        6 - Rotate right 90 degrees
        1 - Move forward 5 units
        6 - Rotate right 90 degrees
        1 - Move forward 5 units
        6 - Rotate right 90 degrees
        1 - Move forward 5 units
        6 - Rotate right 90 degrees
        7 - Stop

    Expectation:
        Car should do the exact same as scenario 2, but now it is rotating itself rather than strafing.

    Observation (simulator output):
        The car's behavior matches the same end result as scenario 2, which is what was expected. The motors also all stop at the end of the operation as expected too.

# Reflection Paragraph
    - What was the most challenging part?
    - What did you learn about C++ and software design from this project?