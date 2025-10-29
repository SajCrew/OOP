#pragma once
#include "CPoint.h"
#include "ISolidShape.h"
class CRectangle : public ISolidShape
{
public:
    CRectangle(const CPoint& leftTop, double width, double height,
        uint32_t outline, uint32_t fill)
        : m_leftTop(leftTop), m_width(width), m_height(height),
        m_outlineColor(outline), m_fillColor(fill) {}

    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;
    uint32_t GetOutlineColor() const override;
    uint32_t GetFillColor() const override;
    CPoint GetLeftTop() const;
    CPoint GetRightBottom() const;
    double GetWidth() const;
    double GetHeight() const;
    void Draw(ICanvas& canvas) const override;
private:
    double m_width;
    double m_height;
    CPoint m_leftTop;
    uint32_t m_outlineColor;
    uint32_t m_fillColor;
};