#pragma once
#include "ISolidShape.h"
#include "CPoint.h"

class CCircle : public ISolidShape 
{
public:
    CCircle(const CPoint& center, double radius, uint32_t outline, uint32_t fill)
        : m_center(center), m_radius(radius), m_outlineColor(outline), m_fillColor(fill) {}
    double GetArea() const override;
    double GetPerimeter() const override;
    string ToString() const override;
    uint32_t GetOutlineColor() const override;
    uint32_t GetFillColor() const override;
    CPoint GetCenter() const;
    double GetRadius() const;
    void Draw(ICanvas& canvas) const override;

private:
    CPoint m_center {0.0, 0.0};
    double m_radius; 
    uint32_t m_outlineColor;
    uint32_t m_fillColor;
    //outlinecolor и fillcolor вынести в отельный базовый класс
};