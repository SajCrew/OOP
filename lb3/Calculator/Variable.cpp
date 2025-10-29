#include "Variable.h"

Variable::Variable(const std::string& name)
    : Identifier(name), 
    _defined(false) {}

void Variable::SetValue(double val) 
{
    _value = val;
    _defined = true;
}

double Variable::GetValue() const 
{
    return _value;
}

bool Variable::IsDefined() const 
{
    return _defined;
}