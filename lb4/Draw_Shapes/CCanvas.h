#pragma once
#include "ICanvas.h"
#include "C:\Soft\SFML-2.6.1\include\SFML\Graphics.hpp"

class CCanvas : public ICanvas 
{
public:

    CCanvas(sf::RenderWindow& window) : m_window(window) {}

    void DrawLine(CPoint from, CPoint to, uint32_t color) override;
  

    void FillPolygon(const std::vector<CPoint>& points, uint32_t fillColor) override;
  

    void DrawCircle(CPoint center, double radius, uint32_t color) override;
    

    void FillCircle(CPoint center, double radius, uint32_t fillColor) override;
    
private:
    sf::RenderWindow& m_window;
};