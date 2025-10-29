#include "CCircle.h"

const double PI = 3.14;

double CCircle::GetArea() const 
{ 
    return PI * (m_radius * m_radius); 
}

double CCircle::GetPerimeter() const 
{ 
    return 2 * PI * m_radius; 
}

std::string CCircle::ToString() const 
{
    return "Circle: Center(" + std::to_string(m_center.GetX())
        + ", " + std::to_string(m_center.GetY()) + "), Radius = " + std::to_string(m_radius);
}

uint32_t CCircle::GetOutlineColor() const 
{ 
    return m_outlineColor; 
}

uint32_t CCircle::GetFillColor() const 
{ 
    return m_fillColor; 
}

CPoint CCircle::GetCenter() const 
{ 
    return m_center; 
}

double CCircle::GetRadius() const 
{ 
    return m_radius; 
}

void CCircle::Draw(ICanvas& canvas) const 
{
    canvas.FillCircle(m_center, m_radius, m_fillColor);
    canvas.DrawCircle(m_center, m_radius, m_outlineColor);
}