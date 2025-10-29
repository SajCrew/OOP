#pragma once
#include "CPoint.h"
#include "ISolidShape.h"
class CTriangle : public ISolidShape
{
public:
	CTriangle(const CPoint& v1, const CPoint& v2, const CPoint& v3, uint32_t outline, uint32_t fill)
		: m_vertex1(v1), m_vertex2(v2), m_vertex3(v3), m_outlineColor(outline), m_fillColor(fill) {}
	double GetArea() const override;
	double GetPerimeter() const override;
	string ToString() const override;
	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;	
	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const ;
	void Draw(ICanvas& canvas) const override;
private:
	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
	static double Distance(const CPoint& a, const CPoint& b);
};