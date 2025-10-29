#pragma once
#include <string>
#include <cmath>

class Identifier 
{
/*protected:
    std::string name; *///закрытый доступ(для наследников) //убрать

public:
    Identifier(const std::string& name) : name(name) {}
    virtual ~Identifier() = default;

    std::string GetName() const { return name; } //общий доступ (для всех)
    virtual double GetValue() const = 0;
    virtual bool IsDefined() const = 0;
private:
    std::string name; //название с m_
};