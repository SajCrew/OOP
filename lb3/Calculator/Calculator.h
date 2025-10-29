#pragma once
#include "Command_abstract.h"
#include "variable.h"
#include "function.h"
#include <map>
#include <string>
#include <stdexcept>
#include <memory>
#include <vector>
#include <algorithm>

//вынести класс command в отдел файл 
class Calculator
{
public:
    void ProcessCommand(const std::string& command);
 /*   Variable* getVariable(const std::string& name) const;
    Function* getFunction(const std::string& name) const;*/

    //методы с большой буквы
    void PrintIdentifier(const std::string& name) const;
    void PrintVariables() const;
    void PrintFunctions() const;

    bool VariableExist(const std::string& name) const;
    bool FunctionExist(const std::string& name) const;
    void AddVariable(const std::string& name);
    void SetVariableValue(const std::string& name, double value);
    double GetIdentifierValue(const std::string& name) const;
    void AddFunction(const std::string& name, std::unique_ptr<Function> func);
    const Identifier* GetIdentifierPtr(const std::string& name) const;

private:
    std::unique_ptr<Command> ParseCommand(const std::string& command);
    std::map<std::string, std::unique_ptr<Variable>> variables;
    std::map<std::string, std::unique_ptr<Function>> functions;
    //убрать friend классы
};

