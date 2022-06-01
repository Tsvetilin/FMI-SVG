#pragma once
#include "Shape.hpp"
const double PI = 3.14159265359;

class Circle : public virtual Shape
{
protected:
	double radius;
	void createCircle(double x, double y, double r);

public:
	Circle();
	Circle(double x, double y, double r);
	virtual double getArea() const override;
	virtual double getPerimeter()  const override;
	virtual bool isPointIn(double x, double y) const override;
	virtual bool isWithin(const Shape* other) const override;
};
