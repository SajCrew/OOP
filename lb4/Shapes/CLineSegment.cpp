#include "CLineSegment.h"
using namespace std;

double CLineSegment::GetArea() const 
{
    return 0.0; 
}

double CLineSegment::GetPerimeter() const
{
    return hypot(m_end.GetX() - m_start.GetX(), m_end.GetY() - m_start.GetY());
}

std::string CLineSegment::ToString() const 
{
    return "LineSegment: Point1(" + std::to_string(m_start.GetX()) + ", "
        + std::to_string(m_start.GetY()) + "), Point2(" 
        + std::to_string(m_end.GetX()) + ", "
        + std::to_string(m_end.GetY()); + ")";
}

uint32_t CLineSegment::GetOutlineColor() const 
{ 
    return m_outlineColor; 
}

CPoint CLineSegment::GetStartPoint() const 
{ 
    return m_start; 
}

CPoint CLineSegment::GetEndPoint() const
{
    return m_end;
}

void CLineSegment::Draw(ICanvas& canvas) const 
{
    canvas.DrawLine(m_start, m_end, m_outlineColor);
}