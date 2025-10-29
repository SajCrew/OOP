#pragma once
#include "calculator.h"

class VarCommand : public Command
{
public:
    VarCommand(const std::string& name) : _name(name) {}
    void Execute(Calculator& calc) override;
private:
    std::string _name;
};

class LetCommand : public Command
{
public:
    LetCommand(const std::string& name, const std::string& valueStr, bool isNumber)
        : _name(name), _valueStr(valueStr), _isNumber(isNumber) {}
    void Execute(Calculator& calc) override;
private:
    std::string _name;
    std::string _valueStr;
    bool _isNumber;
};

class FnCommand : public Command
{
public:
    FnCommand(const std::string& name, const std::string& expr) : _name(name), _expr(expr) {}  
    void Execute(Calculator& calc) override;
private:
    void DetectingFunction(std::istringstream& iss, char operation, std::string& op1, std::string& op2, Calculator& calc);
    std::string _name;
    std::string _expr; 
};