#include "CCanvas.h"

void CCanvas::DrawLine(CPoint from, CPoint to, uint32_t color)
{
    sf::Vertex line[] =
    {
        sf::Vertex(
            sf::Vector2f((float)from.GetX(), (float)from.GetY()),
            sf::Color(color)
        ),
        sf::Vertex(
            sf::Vector2f((float)to.GetX(), (float)to.GetY()),
            sf::Color(color)
        )
    };

    line[0].color = sf::Color(color);
    m_window.draw(line, 2, sf::Lines);
}

void CCanvas::FillPolygon(const std::vector<CPoint>& points, uint32_t fillColor)
{
    sf::ConvexShape polygon;
    polygon.setPointCount(points.size());
    polygon.setFillColor(sf::Color(fillColor));

    for (size_t i = 0; i < points.size(); ++i)
    {
        polygon.setPoint(i, sf::Vector2f(
            (float)points[i].GetX(),
            (float)points[i].GetY()));
    }
    m_window.draw(polygon);
}

void CCanvas::DrawCircle(CPoint center, double radius, uint32_t color)
{
    sf::CircleShape circle((float)radius);
    circle.setPosition((float)(center.GetX() - radius), (float)(center.GetY() - radius));
    circle.setOutlineColor(sf::Color(color));
    circle.setOutlineThickness(1);
    circle.setFillColor(sf::Color(0, 0, 0, 0));
    m_window.draw(circle);
}

void CCanvas::FillCircle(CPoint center, double radius, uint32_t fillColor) 
{
    sf::CircleShape circle((float)radius);
    circle.setPosition((float)(center.GetX() - radius), (float)(center.GetY() - radius));
    circle.setFillColor(sf::Color(fillColor));
    m_window.draw(circle);
}