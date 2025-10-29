#include <map>
#include "GetCarInfo.h"

const int MIN_GEAR = -1;
const int MAX_GEAR = 5;

//сделать глобальной константой 
const std::map<int, std::pair<int, int>> speedRanges = 
{
	{-1, {0, 20}},
	{0, {0, 150}},
	{1, {0, 30}},
	{2, {20, 50}},
	{3, {30, 60}},
	{4, {40, 90}},
	{5, {50, 150}}
};

//сделать конструктор в Car.h
//Car::Car() : isEngineOn(false), currGear(0), currSpeed(0) {} //именование через _

bool Car::IsTurnedOn() const
	{
		return isEngineOn;
	}

	Car::Direction Car::GetDirection() const
	{
		if (currSpeed == 0)
		{
			return Direction::STANDING_STILL;
		}
		else
			if ((currGear != -1) && (currSpeed > 0))
				return Direction::FORWARD; //0 или >
			else
				return Direction::BACK;

	}

int Car::GetGear() const
	{
		return currGear;
	}

int Car::GetSpeed() const
	{
		return currSpeed;
	}

bool Car::TurnOnEngine()
	{
		if (!isEngineOn)
		{
			isEngineOn = true;
			currGear = 0;
			currSpeed = 0;
		}
		return true;
	}

bool Car::TurnOffEngine()
{
	if (currGear == 0 && currSpeed == 0)
	{
		isEngineOn = false;
		return true;
	}
	throw std::runtime_error(ErrorMessages::ENGINE_OFF_FAIL);
}

bool Car::SetGear(int gear)
{
	if (gear < MIN_GEAR || gear > MAX_GEAR)
	{
		throw std::runtime_error(ErrorMessages::INVALID_GEAR);
	}

	if (!isEngineOn)
	{
		if (gear != 0)
		{
			throw std::runtime_error(ErrorMessages::SET_GEAR_FAIL1);
		}
		return true;
	}

	if (gear == currGear)
	{
		return true;
	}

	const auto& range = speedRanges.at(gear);
	int minSpeed = range.first;
	int maxSpeed = range.second;

	if (gear == -1)
	{
		if (currSpeed != 0)
		{
			throw std::runtime_error(ErrorMessages::SET_GEAR_FAIL2);
		}
	}

	if (currGear == -1 && gear != 0 && currSpeed != 0)
	{
		throw std::runtime_error(ErrorMessages::SET_GEAR_FAIL2);
	}

	if (gear != 0 && (currSpeed < minSpeed || currSpeed > maxSpeed))
	{
		throw std::runtime_error(ErrorMessages::SET_GEAR_FAIL4);
	}

	currGear = gear;
	return true;
}

bool Car::SetSpeed(int speed)
{
	if (speed < 0)
	{
		throw std::runtime_error(ErrorMessages::NEGATIVE_SPEED_FAIL);
	}

	if (!isEngineOn)
	{
		throw std::runtime_error(ErrorMessages::SET_SPEED_FAIL1);
	}

	if (currGear == 0)
	{
		if (speed > std::abs(currSpeed))
		{
			throw std::runtime_error(ErrorMessages::SET_SPEED_FAIL2);
		}
		currSpeed = (GetDirection() == Direction::BACK) ? -speed : speed;
		return true;
	}

	const auto& range = speedRanges.at(currGear);
	if (speed < range.first || speed > range.second)
	{
		throw std::runtime_error(ErrorMessages::SET_SPEED_FAIL3);
	}

	currSpeed = (currGear == -1) ? -speed : speed;
	return true;
}