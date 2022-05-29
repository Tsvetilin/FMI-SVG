#pragma once
#include "SVGShape.hpp"

class Rectangle : public virtual Shape
{
protected:
	void createRectangle(double x, double y, double width, double heigth);

public:
	Rectangle();
	Rectangle(double x, double y, double width, double heigth);
	virtual double getArea() const override;
	virtual double getPerimeter()  const override;
	virtual bool isPointIn(int x, int y) const override;
	virtual bool isWithin(const Shape* other) const override;

	virtual void translate(int x, int y);
};