#include "GetCarInfo.h"
#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>

//не использовать process inp. команды подавать напрямую машине
void CarInteractive(Car& car) 
{
    std::string line;
    while (std::getline(std::cin, line)) 
    {
        //разбить на подфункции
        std::istringstream iss(line);
        std::string command;
        iss >> command;

        if (command.empty()) continue;

        try 
        {
            std::string arg;
            int value = 0; 

            if (command == "SetGear" || command == "SetSpeed") 
            {
                if (!(iss >> arg)) 
                {
                    PrintError(ErrorMessages::INVALID_COMMAND_ARG);
                    continue;
                }

                try 
                {
                    value = std::stoi(arg);
                }
                catch (const std::invalid_argument&) 
                {
                    PrintError(command == "SetGear"
                        ? ErrorMessages::INVALID_GEAR_COMMAND
                        : ErrorMessages::INVALID_SET_SPEED_ARG);
                    continue;
                }
                catch (const std::out_of_range&) 
                {
                    PrintError("Argument value is out of range");
                    continue;
                }
            }

            //сделать класс контроллер с мапой для команд
            if (command == "Info") 
            {
                HandleInfoCommand(car);
            }
            else if (command == "EngineOn") 
            {
                car.TurnOnEngine();
            }
            else if (command == "EngineOff") 
            {
                car.TurnOffEngine();
            }
            else if (command == "SetGear") 
            {
                car.SetGear(value);
            }
            else if (command == "SetSpeed") 
            {
                car.SetSpeed(value);
            }
            else 
            {
                PrintError(ErrorMessages::UNKNOWN_COMMAND);
            }
        }
        catch (const std::runtime_error& e) 
        {
            PrintError(e.what());
        }
        catch (const std::exception& e) 
        {
            PrintError(std::string("System error: ") + e.what());
        }
    }
}