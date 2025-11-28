#include <iostream>
#include <wiringPi.h>
#include <unistd.h>

// Note: Based on macros from wiringPi, 
// LOW = 0
// OUTPUT = 1
// HIGH = 1;

const int MotorOne = 14;

void setupPins() {
	if (wiringPiSetupGpio() == -1) {
		std::cerr << "Failed to initialize wiringPi\n";
		exit(1);
	}	
	
	pinMode(MotorOne, OUTPUT);
	
	digitalWrite(MotorOne, LOW);
}

int main() {
	std::cout << "Harlow Wrld\n";
	setupPins();
	
	digitalWrite(MotorOne, HIGH);
	sleep(2);
	
	digitalWrite(MotorOne, LOW);
	
	return 0;
}
