#include "command.h"
#include "calculator.h"
#include <stdexcept>
#include <sstream>
#include "Validation.h"

using namespace std;

void VarCommand::Execute(Calculator& calc) 
{
    if (calc.VariableExist(_name)) //проверку в калькулятор
    {
        throw runtime_error("Name already exists");
    }
    calc.AddVariable(_name);
}

void LetCommand::Execute(Calculator& calc)
{
    if (!IsValidIdentifier(_name) || calc.FunctionExist(_name)) 
    {
        throw runtime_error("Invalid usage");
    }

    //<идент1> = <число>
    if (_isNumber) 
    {
        try 
        {
            double value = std::stod(_valueStr);
            calc.SetVariableValue(_name, value);
        }
        catch (...) 
        {
            throw runtime_error("Invalid usage");
        }
    }
    //<идент1> = <идент2>
    else 
    {
        if (!IsValidIdentifier(_valueStr)) 
        {
            throw runtime_error("Invalid usage");
        }

        try 
        {
            double value = calc.GetIdentifierValue(_valueStr);
            calc.SetVariableValue(_name, value);
        }
        catch (const std::runtime_error&) 
        {
            throw runtime_error("Name does not exist");
        }
    }
}

void FnCommand::DetectingFunction(std::istringstream& iss, char operation,
    std::string& op1, std::string& op2, Calculator& calc) 
{
    if (iss >> operation) 
    {
        // Бинарная операция
        iss >> op2;
        try 
        {
            const Identifier* id1 = calc.GetIdentifierPtr(op1);
            const Identifier* id2 = calc.GetIdentifierPtr(op2);
            calc.AddFunction(_name, std::make_unique<Function>(_name, id1, id2, operation));
        }
        catch (const std::runtime_error&) 
        {
            throw std::runtime_error("Name does not exist");
        }
    }
    else 
    {
        // Унарная операция
        try 
        {
            const Identifier* id = calc.GetIdentifierPtr(op1);
            calc.AddFunction(_name, std::make_unique<Function>(_name, id));
        }
        catch (const std::runtime_error&)
        {
            throw std::runtime_error("Name does not exist");
        }
    }
}

void FnCommand::Execute(Calculator& calc) 
{
    if (!IsValidIdentifier(_name) || calc.VariableExist(_name) || calc.FunctionExist(_name)) 
    {
        throw std::runtime_error("Invalid usage");
    }

    std::string op1, op2;
    char operation = '0';
    std::istringstream iss(_expr);

    iss >> op1;
    if (!IsValidIdentifier(op1)) 
    {
        throw std::runtime_error("Invalid usage");
    }

    DetectingFunction(iss, operation, op1, op2, calc);
}
