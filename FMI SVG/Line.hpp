#pragma once
#include "SVGShape.hpp"
#include "Common.hpp"

class Line : public virtual Shape
{
protected:
	void createLine(double x1, double x2, double y1, double y2);
public:
	Line();
	Line(double x1, double x2, double y1, double y2);
	virtual double getArea() const override;
	virtual double getPerimeter()  const override;
	virtual bool isPointIn(double x, double y) const override;
	virtual bool isWithin(const Shape* other) const override;
};
