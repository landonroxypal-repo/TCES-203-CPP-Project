The code in this folder operates a car in c++ for a raspberry pi.

# Compilation

To compile and run our project, please run this command in the terminal with the current directory set 
to where the main.cpp file is located.


If on a Raspberry Pi B:
g++ -DUSING_PI=1 -std=c++11 main.cpp Car.cpp motor.cpp -lwiringpi -o TCES203Proj2
./TCES203Proj2

Note: The above compilation command WILL fail if you do not have a Raspberry Pi B with the wiringPi.h header file installed!

If simulating a mock Raspberry Pi B in an IDE:
g++ -DMOCK_PI=1 -std=c++11 main.cpp Car.cpp motor.cpp wiringPi.cpp -o TCES203Proj2
./TCES203Proj2

Otherwise (simulation mode):
g++ -std=c++11 main.cpp Car.cpp motor.cpp -o TCES203Proj2
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
 - Simulator.h: A simulator class that does something [NOT IMPLEMENTED YET!!!!!!!!]
 - Simulator.cpp: [NOT IMPLEMENTED YET!!!!!!!]

# Simulator

NOT IMPLEMENTED YET!!

# Test Scenarios

Scenarios:
 - Scenario 1:

    Commands Run:
        Command 1
        Command 2
        Command 3

    Expectation:
        Car won't explode!

    Observation (simulator output):
        Car in fact did not explode :D

 - Scenario 2:

     Commands Run:
        Command 1
        Command 2
        Command 3

    Expectation:
        Car won't explode!

    Observation (simulator output):
        Car in fact did not explode :D

 - Scenario 3:

     Commands Run:
        Command 1
        Command 2
        Command 3

    Expectation:
        Car won't explode!

    Observation (simulator output):
        Car in fact did not explode :D

# Reflection Paragraph
    - What was the most challenging part?
    - What did you learn about C++ and software design from this project?