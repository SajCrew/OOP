#pragma once
#include <string>
#include <cmath>

class Identifier 
{
/*protected:
    std::string name; *///�������� ������(��� �����������) //������

public:
    Identifier(const std::string& name) : name(name) {}
    virtual ~Identifier() = default;

    std::string GetName() const { return name; } //����� ������ (��� ����)
    virtual double GetValue() const = 0;
    virtual bool IsDefined() const = 0;
private:
    std::string name; //�������� � m_
};