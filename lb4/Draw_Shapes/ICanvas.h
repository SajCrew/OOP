#pragma once
#include "../Shapes/CPoint.h"
#include <vector>
#include <cstdint>
class ICanvas 
{
public:
    virtual ~ICanvas() = default;

    virtual void DrawLine(CPoint from, CPoint to, uint32_t color) = 0;
    virtual void FillPolygon(const std::vector<CPoint>& points, uint32_t fillColor) = 0;
    virtual void DrawCircle(CPoint center, double radius, uint32_t color) = 0;
    virtual void FillCircle(CPoint center, double radius, uint32_t fillColor) = 0;
};

