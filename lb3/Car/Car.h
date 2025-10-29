#pragma once 
#include <map>
//в реализацию
//const int MIN_GEAR = -1;
//const int MAX_GEAR = 5;

class Car 
{
public:
    Car() = default;
    enum class Direction 
    {
        FORWARD,
        BACK,
        STANDING_STILL
    };

    bool IsTurnedOn() const;
    Direction GetDirection() const;
    int GetGear() const;
    int GetSpeed() const;

    bool TurnOnEngine();
    bool TurnOffEngine();
    bool SetGear(int gear);
    bool SetSpeed(int speed);

private:
    bool isEngineOn{ false };
    int currGear{0};
    int currSpeed{0};
    //убрать
    //static const std::map<int, std::pair<int, int>> speedRanges;
};