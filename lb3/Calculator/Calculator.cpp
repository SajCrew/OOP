#include "Validation.h"
#include "calculator.h"
#include "command.h"
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <cctype>
#include <iostream>

using namespace std;


bool Calculator::VariableExist(const std::string& name) const 
{
    return variables.count(name);
}


bool Calculator::FunctionExist(const std::string& name) const
{
    return functions.count(name);
}


void Calculator::AddVariable(const std::string& name)
{
    variables[name] = std::make_unique<Variable>(name);
}


void Calculator::SetVariableValue(const std::string& name, double value)
{
    if (!variables.count(name)) 
    {
        variables[name] = std::make_unique<Variable>(name);
    }
    variables[name]->SetValue(value);
}


double Calculator::GetIdentifierValue(const std::string& name) const 
{
    if (variables.count(name)) 
    {
        return variables.at(name)->GetValue();
    }
    if (functions.count(name)) 
    {
        return functions.at(name)->GetValue();
    }
    throw std::runtime_error("Name does not exist");
}


void Calculator::AddFunction(const std::string& name, std::unique_ptr<Function> func) 
{
    functions[name] = std::move(func);
}

const Identifier* Calculator::GetIdentifierPtr(const std::string& name) const 
{
    if (variables.count(name)) 
    {
        return variables.at(name).get();
    }
    if (functions.count(name)) 
    {
        return functions.at(name).get();
    }
    throw std::runtime_error("Name does not exist");
}


class PrintCommand : public Command 
{
    string name;
public:
    PrintCommand(const string& name) : name(name) {}
    void Execute(Calculator& calc) override 
    {
        calc.PrintIdentifier(name);
    }
};


class PrintVarsCommand : public Command 
{
public:
    void Execute(Calculator& calc) override 
    {
        calc.PrintVariables();
    }
};


class PrintFnsCommand : public Command 
{
public:
    void Execute(Calculator& calc) override 
    {
        calc.PrintFunctions();
    }
};


void Calculator::ProcessCommand(const string& command) 
{
    try 
    {
        auto cmd = ParseCommand(command);
        if (cmd) cmd->Execute(*this);
    }
    catch (const exception& e) 
    {
        cout << e.what() << endl;
        throw;
    }
}


unique_ptr<Command> Calculator::ParseCommand(const string& command)
{
    istringstream iss(command);
    string cmd;
    iss >> cmd;

    if (cmd == "var")
    {
        string name;
        iss >> name;
        Trim(name);
        if (name.empty())
            throw runtime_error("Empty identifier name");
        return make_unique<VarCommand>(name);
    }
    else if (cmd == "let")
    {
        string token, name, value;
        getline(iss, token);
        size_t eq_pos = token.find('=');

        if (eq_pos == string::npos)
            throw runtime_error("Invalid usage");

        name = token.substr(0, eq_pos);
        value = token.substr(eq_pos + 1);
        Trim(name);
        Trim(value);

        if (name.empty() || value.empty())
            throw runtime_error("Invalid usage");

        bool isNumber = OpIsNumber(value);
        return make_unique<LetCommand>(name, value, isNumber);
    }
    else if (cmd == "fn")
    {
        string token, name, expr;
        getline(iss, token);
        size_t eq_pos = token.find('=');   

        if (eq_pos == string::npos)
            throw runtime_error("Invalid usage: missing '='");

        name = token.substr(0, eq_pos);
        expr = token.substr(eq_pos + 1);
        Trim(name);
        Trim(expr);

        if (name.empty() || expr.empty())
            throw runtime_error("Invalid usage");

        //�������� �������� ������ ���������
        size_t opPos = expr.find_first_of("+-*/");
        if (opPos != string::npos && opPos > 0 && opPos < expr.length() - 1)
        {
            string op1 = expr.substr(0, opPos);
            string op2 = expr.substr(opPos + 1);
            Trim(op1);
            Trim(op2);
            expr = op1 + " " + expr[opPos] + " " + op2;
        }

        return make_unique<FnCommand>(name, expr);
    }
    else if (cmd == "print")
    {
        string name;
        getline(iss, name);
        Trim(name);
        if (name.empty()) throw runtime_error("Invalid usage");
        return make_unique<PrintCommand>(name);
    }
    else if (cmd == "printvars")
    {
        return make_unique<PrintVarsCommand>();
    }
    else if (cmd == "printfns")
    {
        return make_unique<PrintFnsCommand>();
    }
    else
    {
        throw runtime_error("Unknown command");
    }
}



void Calculator::PrintIdentifier(const string& name) const 
{
    double value = NAN;

    if (variables.count(name)) 
    {
        value = variables.at(name)->GetValue();
    }
    else 
        if (functions.count(name)) 
        {
            value = functions.at(name)->GetValue();
        }
        else 
        {
            throw runtime_error("Name does not exist");
        }

    if (isnan(value)) 
    {
        cout << "nan" << endl;
    }
    else 
    {
        cout << fixed << setprecision(2) << value << endl;
    }
}

void Calculator::PrintVariables() const 
{
    vector<pair<string, double>> vars;
    for (const auto& [name, var] : variables) 
    {
        vars.emplace_back(name, var->GetValue());
    }

    sort(vars.begin(), vars.end());

    for (const auto& [name, value] : vars) 
    {
        cout << name << ":";
        if (isnan(value)) 
        {
            cout << "nan";
        }
        else 
        {
            cout << fixed << setprecision(2) << value;
        }
        cout << endl;
    }
}

void Calculator::PrintFunctions() const 
{
    vector<pair<string, double>> fns;
    for (const auto& [name, fn] : functions) 
    {
        fns.emplace_back(name, fn->GetValue());
    }

    sort(fns.begin(), fns.end());

    for (const auto& [name, value] : fns) 
    {
        cout << name << ":";
        if (isnan(value)) 
        {
            cout << "nan";
        }
        else 
        {
            cout << fixed << setprecision(2) << value;
        }
        cout << endl;
    }
}