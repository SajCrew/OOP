#pragma once
#include "IShape.h"
#include "CPoint.h"
class CLineSegment : public IShape
{
public:
	CLineSegment(const CPoint& start, const CPoint& end, uint32_t color)
		: m_start(start), m_end(end), m_outlineColor(color) {}
	double GetArea() const override;
	double GetPerimeter() const override;
	string ToString() const override;
	uint32_t GetOutlineColor() const override;
	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;
	void Draw(ICanvas& canvas) const override;
private:
	CPoint m_start;
	CPoint m_end;
	uint32_t m_outlineColor;
};