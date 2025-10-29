#define CATCH_CONFIG_MAIN
#include "../Car_tests/catch.hpp"
#include "../Car/CarController.h"

#include <sstream>
#include <string>

TEST_CASE("Car's basic functions") {

    Car car;
    SECTION("Turn on Engine") {
        car.TurnOnEngine();
        REQUIRE(car.IsTurnedOn());
        REQUIRE(car.GetDirection() == Car::Direction::STANDING_STILL);
        REQUIRE(car.GetSpeed() == 0);
        REQUIRE(car.GetGear() == 0);
    }

    SECTION("Gear 1 + speed 15") {
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(15);
        REQUIRE(car.IsTurnedOn());
        REQUIRE(car.GetDirection() == Car::Direction::FORWARD);
        REQUIRE(car.GetSpeed() == 15);
        REQUIRE(car.GetGear() == 1);
    }

    SECTION("Speed braking on neutral") {
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(30);
        car.SetGear(0);
        car.SetSpeed(10);
        REQUIRE(car.IsTurnedOn());
        REQUIRE(car.GetDirection() == Car::Direction::FORWARD);
        REQUIRE(car.GetSpeed() == 10);
        REQUIRE(car.GetGear() == 0);
    }

    SECTION("Ride, slow down and stop") {
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(30);
        car.SetGear(0);
        car.SetSpeed(0);
        car.TurnOffEngine();
        REQUIRE(!car.IsTurnedOn());
        REQUIRE(car.GetDirection() == Car::Direction::STANDING_STILL);
        REQUIRE(car.GetSpeed() == 0);
        REQUIRE(car.GetGear() == 0);
    }

    SECTION("Reverse ride") {
        car.TurnOnEngine();
        car.SetGear(-1);
        car.SetSpeed(10);
        REQUIRE(car.GetDirection() == Car::Direction::BACK);
        car.SetGear(0);
        REQUIRE(car.GetDirection() == Car::Direction::BACK);
        car.SetSpeed(0);
        REQUIRE(car.GetDirection() == Car::Direction::STANDING_STILL);
    }

    SECTION("Change direction after stop") {
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(30);
        car.SetSpeed(0);
        car.SetGear(-1);
        REQUIRE(car.GetDirection() == Car::Direction::STANDING_STILL);
    }
}

TEST_CASE("Wrong scenarios")
{
    Car car;

    SECTION("Switch gear (Current speed out of new gear's range)") {
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(30);
        REQUIRE_THROWS_WITH(car.SetGear(2), ErrorMessages::SET_GEAR_FAIL4);
    }

    SECTION("Switch on speed out off gear's range") {
        car.TurnOnEngine();
        car.SetGear(1);
        REQUIRE_THROWS_WITH(car.SetSpeed(40), ErrorMessages::SET_SPEED_FAIL3);
    }

    SECTION("EngineOff while moving") {
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(30);
        REQUIRE_THROWS_WITH(car.TurnOffEngine(), ErrorMessages::ENGINE_OFF_FAIL);
    }

    SECTION("Switch gear on -1 during non-zero gear") {
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(30);      
        REQUIRE_THROWS_WITH(car.SetGear(-1), ErrorMessages::SET_GEAR_FAIL2);
    }

    //тест на езду назад на нейт передаче, сохр direction
    SECTION("Ride back on zero-gear (must be saved Direction)") {
        car.TurnOnEngine();
        car.SetGear(-1);
        car.SetSpeed(10);
        REQUIRE(car.GetDirection() == Car::Direction::BACK);
    }

    //добавить пограничные тесты (gear), speed

    SECTION("Edge gear case") {
        car.TurnOnEngine();
   
        // Попытка переключиться на несуществующую передачу
        REQUIRE_THROWS_WITH(car.SetGear(6), ErrorMessages::INVALID_GEAR);
        REQUIRE_THROWS_WITH(car.SetGear(-2), ErrorMessages::INVALID_GEAR);
    }

    SECTION("Edge speed case") {
        car.TurnOnEngine();
        // Максимальная скорость на высшей передаче
        car.SetGear(5);
        car.SetSpeed(150);
        REQUIRE_THROWS_WITH(car.SetSpeed(151), ErrorMessages::SET_GEAR_FAIL4);
    }

    //проверить гранич значения +1 и -1 для кажд передачи

    SECTION("Right edge speed case for gear 2") {
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(30);
        car.SetGear(2);
        car.SetSpeed(50);
        REQUIRE(car.GetSpeed() == 50);
    }

    SECTION("Right edge speed case for gear 3") {
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(30);
        car.SetGear(3);
        car.SetSpeed(60);
        REQUIRE(car.GetSpeed() == 60);
    }

    SECTION("Right edge speed case for gear 4") {
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(30);
        car.SetGear(3);
        car.SetSpeed(60);
        car.SetGear(4);
        car.SetSpeed(90);
        REQUIRE(car.GetSpeed() == 90);
    }

    SECTION("Right edge gear case for speed = 30") {
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(30);
        car.SetGear(3);
        car.SetSpeed(60);     
        REQUIRE_THROWS_WITH(car.SetGear(2), ErrorMessages::SET_GEAR_FAIL4);
    }
}


