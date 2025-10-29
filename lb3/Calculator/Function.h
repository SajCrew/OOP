#pragma once
#include "identifier.h"
#include <memory>

class Function : public Identifier {

public:
    Function(const std::string& name, const Identifier* op1)
        : Identifier(name), operand1(op1), operand2(nullptr),
        operation(0), isUnary(true) {}
     
    Function(const std::string& name, const Identifier* op1, const Identifier* op2, char op);

    double GetValue() const override;

    bool IsDefined() const override;

private:
    const Identifier* operand1;
    char operation;
    const Identifier* operand2;
    bool isUnary;
};
