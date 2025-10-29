#pragma once
#include <string>
#include "../Draw_Shapes/ICanvas.h"
using namespace std;
class IShape
{
public:
	virtual ~IShape() = default;
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual string ToString() const = 0;
	virtual uint32_t GetOutlineColor() const = 0;
    virtual void Draw(ICanvas& canvas) const = 0;
};