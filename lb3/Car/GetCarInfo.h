#include "Car.h"
#include <string>
#include <stdexcept>
#pragma once
namespace ErrorMessages 
{
	const std::string ENGINE_OFF_FAIL = "Car must be stopped and in neutral gear";
	const std::string SET_GEAR_FAIL1 = "Cannot set gear while engine is off";
	const std::string SET_GEAR_FAIL2 = "Cannot reverse while moving";
	const std::string SET_GEAR_FAIL3 = "Can not switch -1:gear while moving";
	const std::string SET_GEAR_FAIL4 = "Gear is out of speed range";
	const std::string INVALID_GEAR = "Invalid gear";
	const std::string INVALID_GEAR_COMMAND = "Invalid command argument";
	const std::string SET_SPEED_FAIL1 = "Cannot set speed while engine is off";
	const std::string SET_SPEED_FAIL2 = "Cannot accelerate on neutral";
	const std::string SET_SPEED_FAIL3 = "Speed is out of gear range";
	const std::string NEGATIVE_SPEED_FAIL = "Speed cannot be negative";
	const std::string INVALID_SET_SPEED_ARG = "Invalid set speed command argument";
	const std::string INVALID_COMMAND_ARG = "Invalid command argument";
	const std::string UNKNOWN_COMMAND = "Unknown command";
}

void HandleInfoCommand(const Car& car);
void PrintError(const std::string& message);