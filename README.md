<!--
  GitHub project README for the C++ Mecanum Car Driver.
  Drop this in the repo root as README.md.
-->

<div align="center">

# C++ Mecanum Car Driver

### Authors: Landon Wardle and Robert Cromer
### December, 2025

A C++ driver for a Mecanum car built on a Raspberry Pi B with L298N motor drivers.
Runnable on real hardware, against a mock Pi, or in a built-in console simulator.

<!-- Badge row — these render as little pills on GitHub -->
![Language](https://img.shields.io/badge/language-C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)

![Standard](https://img.shields.io/badge/standard-C++11-blue?style=for-the-badge)

![Focus](https://img.shields.io/badge/focus-embedded%20systems-2b6cb0?style=for-the-badge)

</div>

---

## Table of Contents

1. [Compilation](#compilation)
2. [Build Modes](#build-modes)
3. [Controls](#controls)
4. [Classes and Files](#classes-and-files)
5. [Hardware Wiring](#hardware-wiring)
6. [Simulator](#simulator)
7. [Test Scenarios](#test-scenarios)
8. [Car Test Videos](#car-test-videos)

---

# Compilation

Compile from the directory containing `main.cpp` with the GNU C++ Compiler (`g++`).
There are several options available that can be chosen between with a preprocessor macro;
pick the option below that matches the environment the code will execute in. 

**Raspberry Pi B**: drives physical GPIO pins.

```bash
g++ -DUSING_PI=1 -std=c++11 main.cpp Car.cpp Motor.cpp Simulator.cpp -lwiringPi -o TCES203Proj2
./TCES203Proj2
```

**Mock Raspberry Pi**: exercises the Pi code paths against a `wiringPi.h` mock file.

```bash
g++ -DMOCK=1 -std=c++11 main.cpp Car.cpp Motor.cpp wiringPi.cpp Simulator.cpp -o TCES203Proj2
./TCES203Proj2
```

**Console Simulation**: no Pi, draws an ASCII map of the car.

```bash
g++ -std=c++11 main.cpp Car.cpp Motor.cpp Simulator.cpp -o TCES203Proj2
./TCES203Proj2
```

> [!WARNING]
> Compilation **will fail on a Raspberry Pi B** if the `wiringPi.h` header is not installed.

> [!NOTE]
> Source file names are case-sensitive on the Pi's Linux filesystem: use `Motor.cpp`
> (capital `M`) and link with `-lwiringPi` (capital `P`).

# Build Modes

| Mode | Macro | WiringPi source | GPIO driven | ASCII map |
|:-----|:------|:----------------|:------------:|:----------:|
| Raspberry Pi | `USING_PI=1` | system `<wiringPi.h>` | ✅ | ❌ |
| Mock Pi | `MOCK=1` | local `"wiringPi.h"` + `wiringPi.cpp` | mocked | ❌ |
| Simulation | *(none)* | none | ❌ | ✅ |

> [!NOTE]
> Only **Simulation** mode constructs the ASCII map in the terminal and prompts for a movement
> value after each command. Otherwise, it is assumed real commands are being recieved.

# Controls

The driver presents this menu in a loop until you choose to exit for all modes:

| Option | Action |
|:------:|:-------|
| `1` | Move forward |
| `2` | Move backward |
| `3` | Strafe left |
| `4` | Strafe right |
| `5` | Rotate left |
| `6` | Rotate right |
| `7` | Stop (halt all motors) |
| `8` | Toggle camera stream on/off |
| `9` | Sort a list of entered command numbers (selection sort) |
| `0` | Exit |

> [!NOTE]
> In Simulation mode, movement options (`1`–`6`) prompt for a distance or angle value.

# Classes and Files

### Files

| File | Responsibility |
|:-----|:---------------|
| `main.cpp` | Entry point. Builds the car and the simulator, then runs the menu loop. |
| `Car.h` / `Car.cpp` | The `MecanumCar` class. Integrates four motors into one controllable unit. |
| `Motor.h` / `Motor.cpp` | The `Motor` class. The most basic unit of the car, wrapping a single L298N-driven motor. |
| `Simulator.h` / `Simulator.cpp` | The `Simulator` class. Renders the car's pose on an ASCII grid. |

### Classes

| Class | Responsibility |
|:------|:---------------|
| `Motor` | Holds a name, signed speed percentage, and two GPIO pins. Clamps speed to `[-100, 100]` and drives the pins through WiringPi. |
| `MecanumCar` | Top-level class. Tracks the car's position `(x, y, heading)`, and dispatches `MovementCommand`s to the four motors. |
| `Simulator` | Holds a pointer to a `MecanumCar` plus a map size. Converts world coordinates to grid cells, and draws the map while tracking the car. |

# Hardware Wiring

There are two **L298N** drivers. One drives the front pair of wheels, and the other drives
the back pair. The GPIO pins assigned in
`MecanumCar`'s constructor are:

| Wheel | Forward Pin | Backward Pin |
|:------|:-----------:|:------------:|
| Front Left | 26 | 19 |
| Front Right | 27 | 17 |
| Rear Left | 24 | 23 |
| Rear Right | 21 | 20 |

L298N Documentation can be found [here](https://www.handsontec.com/dataspecs/L298N%20Motor%20Driver.pdf).

> [!NOTE]
> The cars were not wired for PWM, so `Motor::setSpeed()` uses the sign of the speed
> and then selects a direction where the pins are driven fully `HIGH`/`LOW`.

# Simulator

The simulator renders the car as a `C` on an ASCII grid where `.` means empty.
Because the simulator exposes the same control interface as the physical car, movement logic
can be validated on screen and carried straight over to hardware without changes.

# Test Scenarios

> [!NOTE]
> All scenarios were tested in Simulation mode.

<details>
<summary><b>Scenario 1: Forward/back, then diagonal forward/back</b></summary>

<br>

**Commands Run:**

| Cmd # | Description |
|:-----:|:------------|
| 1 | Move forward 5 units |
| 2 | Move backward 5 units |
| 6 | Rotate right 45 degrees |
| 1 | Move forward 5 units |
| 2 | Move backward 5 units |

**Expectation:**
The car should move forward, then back. It should then rotate 45 degrees and move forward diagonally and backward diagonally.

**Observation (simulator output):**
The car moved forward and then backward 5 units each, resetting to its initial position. It then rotated 45 degrees and moved diagonally forward and backward 5 units.

</details>

<details>
<summary><b>Scenario 2: Square loop via strafing</b></summary>

<br>

**Commands Run:**

| Cmd # | Description |
|:-----:|:------------|
| 1 | Move forward 5 units |
| 3 | Strafe left 5 units |
| 2 | Move backward 5 units |
| 4 | Strafe right 5 units |
| 7 | Stop |

**Expectation:**
The car should finish its path right where it started, tracing a small square loop, then force-stop all motors.

**Observation (simulator output):**
The car behaved as expected, moving forward, left, backward, and right by 5 units each to return to its starting location, then force-stopping all motors.

</details>

<details>
<summary><b>Scenario 3: Square loop via rotation</b></summary>

<br>

**Commands Run:**

| Cmd # | Description |
|:-----:|:------------|
| 1 | Move forward 5 units |
| 6 | Rotate right 90 degrees |
| 1 | Move forward 5 units |
| 6 | Rotate right 90 degrees |
| 1 | Move forward 5 units |
| 6 | Rotate right 90 degrees |
| 1 | Move forward 5 units |
| 6 | Rotate right 90 degrees |
| 7 | Stop |

**Expectation:**
Same end result as Scenario 2, but the car rotates itself rather than strafing.

**Observation (simulator output):**
The car's path matched the same end result as Scenario 2, and all motors stopped at the end of the operation as expected.

</details>

# Car Test Videos

| Video | Link |
|:------|:-----|
| Brief test | https://youtu.be/XIbji8G7Wj8 |
| Lab Lap | https://youtu.be/ZOZdYSiABNk |

<!--
# Project Reflection
The most challenging part was writing the code to clear the cin buffer when we enter invalid input.
We kept getting infinite loops when incorrect input was typed into the command line.
The other hard part was figuring out how to get different parts of the code to compile based on what we want the code to do.
We also had trouble trying to figure out how to make the code interface with the raspberry pi;
especially since external influences kept making it so that the raspberry pi was not able to run the code because it was improperly wired.
Still, these issues did cause us to learn more about how to deal with similar problems.
For example, we used the cin.fail() method to fix the infinite loop method instead of putting a cin expression inside of the conditional for the while loop.
We also learned how to use the documentation for the Raspberry Pi and its motors to ensure that the hardware is not fried by too much wattage.
Looking through this documentation also helped us to code the raspberry pi's pin outputs to run the motors.
We also learned how to predefine macros and write code that uses these macros to determine when different lines of code need to be ran.
For example, the commands for the pi will cause the compiler to throw errors on any device but a raspberry pi, so we created a defined a macro so that we can control the situations in which the commands are compiled.
In terms of what we learned about software engineering, it would be the power of abstraction.
The code designed for this project is capable of running in multiple scenarios (i.e. with a simulation, with a simulated pi, or with a physical car in a lab environment) because the implementation details for the motors in particular are hidden.
The code is able to upscale very nicely to many different use cases without any modification to the internal structure under the hood.
Rather, to switch between these three use cases all that has to happen is the motors recognize the case and choose to use wiring pi code or not.
The car and the camera classes have no control over this occurring and do not know if it happened or not, which allows them to function independently of what the motors are doing so long as the motors are able to be driven by outside code.
-->