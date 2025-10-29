#include <sstream>
#include <iostream>
#include <string>
#include "GetCarInfo.h"

void HandleInfoCommand(const Car& car) {
	std::cout << "Engine: " << (car.IsTurnedOn() ? "on" : "off") << "\n";
	std::cout << "Direction: ";
	switch (car.GetDirection()) {
	case Car::Direction::FORWARD:
		std::cout << "forward";
		break;
	case Car::Direction::BACK:
		std::cout << "backward";
		break;
	case Car::Direction::STANDING_STILL:
		std::cout << "standing still";
		break;
	}
	std::cout << "\n";
	std::cout << "Speed: " << std::abs(car.GetSpeed()) << "\n";
	std::cout << "Gear: " << car.GetGear() << "\n";
}

void PrintError(const std::string& message) {
	std::cout << message << "\n";
}

