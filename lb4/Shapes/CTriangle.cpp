#include "CTriangle.h"
#include <cmath>

double CTriangle::GetArea() const 
{
    return 0.5 * std::abs(
        (m_vertex1.GetX() * (m_vertex2.GetY() - m_vertex3.GetY()))
        + (m_vertex2.GetX() * (m_vertex3.GetY() - m_vertex1.GetY()))
        + (m_vertex3.GetX() * (m_vertex1.GetY() - m_vertex2.GetY()))
    );
}

double CTriangle::GetPerimeter() const 
{
    double a = Distance(m_vertex1, m_vertex2);
    double b = Distance(m_vertex2, m_vertex3);
    double c = Distance(m_vertex3, m_vertex1);
    double sum = a + b + c;
    return sum;
}

double CTriangle::Distance(const CPoint& a, const CPoint& b) 
{
    double dx = a.GetX() - b.GetX();
    double dy = a.GetY() - b.GetY();
    double gipotenuze = sqrt(dx * dx + dy * dy);
    return gipotenuze;
}

std::string CTriangle::ToString() const 
{
    return  "Triangle: Point1(" + std::to_string(m_vertex1.GetX()) + ", "
        + std::to_string(m_vertex1.GetY()) + "); Point2("
        + std::to_string(m_vertex2.GetX()) + ", "
        + std::to_string(m_vertex2.GetY()) + "); Point3("
        + std::to_string(m_vertex3.GetX()) + ", "
        + std::to_string(m_vertex3.GetY()) + ")";
}

uint32_t CTriangle::GetOutlineColor() const { return m_outlineColor; }
uint32_t CTriangle::GetFillColor() const { return m_fillColor; }

CPoint CTriangle::GetVertex1() const { return m_vertex1; }
CPoint CTriangle::GetVertex2() const { return m_vertex2; }
CPoint CTriangle::GetVertex3() const { return m_vertex3; }

void CTriangle::Draw(ICanvas& canvas) const
{
    std::vector<CPoint> vertices = { m_vertex1, m_vertex2, m_vertex3 };
    canvas.FillPolygon(vertices, m_fillColor);

    canvas.DrawLine(m_vertex1, m_vertex2, m_outlineColor);
    canvas.DrawLine(m_vertex2, m_vertex3, m_outlineColor);
    canvas.DrawLine(m_vertex3, m_vertex1, m_outlineColor);
}