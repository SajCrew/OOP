#pragma once
#include "Identifier.h"

class Variable : public Identifier 
{
public:
    Variable(const std::string& name);

    void SetValue(double val);

    double GetValue() const override;

    bool IsDefined() const override;

private:
    double _value = NAN;
    bool _defined;
};
