#include "CRectangle.h"

double CRectangle::GetArea() const
{
    return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
    return (m_width + m_height) * 2;
}

std::string  CRectangle::ToString() const
{
    return "Rectangle: Left top point(" + std::to_string(m_leftTop.GetX()) + ", "
         + std::to_string(m_leftTop.GetY()) + "), "
         + "width: " + std::to_string(m_width) + ", "
         + "height: " + std::to_string(m_height);
}

uint32_t CRectangle::GetOutlineColor() const 
{ 
    return m_outlineColor; 
}

uint32_t CRectangle::GetFillColor() const 
{ 
    return m_fillColor; 
}

CPoint CRectangle::GetLeftTop() const 
{ 
    return m_leftTop; 
}

CPoint CRectangle::GetRightBottom() const 
{
    return CPoint(m_leftTop.GetX() + m_width, m_leftTop.GetY() + m_height);
}

double CRectangle::GetWidth() const 
{
    return m_width; 
}

double CRectangle::GetHeight() const
{ 
    return m_height; 
}

void CRectangle::Draw(ICanvas& canvas) const
{
    std::vector<CPoint> points = 
    {
        m_leftTop,
        CPoint(m_leftTop.GetX() + m_width, m_leftTop.GetY()),
        CPoint(m_leftTop.GetX() + m_width, m_leftTop.GetY() + m_height),
        CPoint(m_leftTop.GetX(), m_leftTop.GetY() + m_height)
    };

    canvas.FillPolygon(points, m_fillColor);
    canvas.DrawLine(points[0], points[1], m_outlineColor);
    canvas.DrawLine(points[1], points[2], m_outlineColor);
    canvas.DrawLine(points[2], points[3], m_outlineColor);
    canvas.DrawLine(points[3], points[0], m_outlineColor);
}