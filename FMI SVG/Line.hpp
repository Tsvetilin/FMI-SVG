#pragma once
#include "SVGShape.hpp"
#include "Common.hpp"

class Line : public virtual Shape
{
public:
	Line();
	Line(double x1, double x2, double y1, double y2);
	virtual double getArea() const override;
	virtual double getPerimeter()  const override;
	virtual bool isPointIn(int x, int y) const override;
	virtual bool isWithin(const Shape* other) const override;

	virtual void translate(int x, int y) override;
};

Line::Line():Shape(2){}

Line::Line(double x1, double x2, double y1, double y2) : Shape(2)
{/*
	double x1 = getAttribute("x1")->getValueAsDouble();
	double x2 = getAttribute("x2")->getValueAsDouble();
	double y1 = getAttribute("y1")->getValueAsDouble();
	double y2 = getAttribute("y2")->getValueAsDouble();
	*/
	setPoint(0, x1, y1);
	setPoint(0, x2, y2);
}

double Line::getArea() const {
	return  0;
}

double Line::getPerimeter()  const {
	return getPoint(0).distanceTo(getPoint(1));
}

bool Line::isPointIn(int x, int y) const {
	double a = getPoint(0).getY() - getPoint(1).getY();
	double b = getPoint(1).getX() - getPoint(0).getX();
	double c = getPoint(0).getX() * getPoint(1).getY() - getPoint(1).getX() * getPoint(0).getY();

	return a * x + b * y + c == 0 &&
		x >= min(getPoint(0).getX(), getPoint(1).getX()) && x <= max(getPoint(0).getX(), getPoint(1).getX()) &&
		y >= min(getPoint(0).getY(), getPoint(1).getY()) && y <= max(getPoint(0).getY(), getPoint(1).getY());
}

bool Line::isWithin(const Shape* other) const {
	return other->isPointIn(getPoint(0)) &&
		other->isPointIn(getPoint(1));
}

void Line::translate(int x, int y) {
	getPoint(0).translate(x, y);
	getPoint(1).translate(x, y);
	/*
	setAttribute("x1", getPoint(0).getX());
	setAttribute("x2", getPoint(1).getX());
	setAttribute("y1", getPoint(0).getY());
	setAttribute("y2", getPoint(1).getY());*/
}