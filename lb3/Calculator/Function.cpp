#include "Function.h"
#include <stdexcept>
#include <cmath>

Function::Function(const std::string& name, const Identifier* op1, const Identifier* op2, char op)
    : Identifier(name), operand1(op1), operand2(op2),
    operation(op), isUnary(false) 
{
    if (op != '+' && op != '-' && op != '*' && op != '/') 
    {
        throw std::runtime_error("Invalid operation");
    }
}

double Function::GetValue() const 
{
    if (isUnary) 
    {
        return operand1->GetValue();
    }

    if ((!operand1->IsDefined()) || (!operand2->IsDefined())) 
    {       
        return NAN;
    }

    double x = operand1->GetValue();
    double y = operand2->GetValue();

    switch (operation) 
    {
        case '+': 
            return x + y;
        case '-': 
            return x - y;
        case '*': 
            return x * y;
        case '/':
            if (y == 0) 
                return NAN;
            else
                return x / y;
        default: return NAN;
    }
}

bool Function::IsDefined() const 
{
    if (isUnary) 
    {
        return operand1->IsDefined();
    }

    if ((!operand1->IsDefined()) || (!operand2->IsDefined())) 
    {
        return false;
    }

    //деление на ноль
    if ((operation == '/') && (operand2->GetValue() == 0)) 
    {
        return false;
    }

    return true;
}