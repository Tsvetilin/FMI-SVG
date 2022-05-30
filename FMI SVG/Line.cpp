#include "Line.hpp"

void Line::createLine(double x1, double x2, double y1, double y2) {
	setPoint(0, x1, y1);
	setPoint(0, x2, y2);
}

Line::Line() :Shape(2) {}

Line::Line(double x1, double x2, double y1, double y2) : Shape(2)
{
	createLine(x1, y1, x2, y2);
}

double Line::getArea() const {
	return  0;
}

double Line::getPerimeter()  const {
	return getPoint(0).distanceTo(getPoint(1));
}

bool Line::isPointIn(double x, double y) const {
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

void Line::translate(double x, double y) {
	getPoint(0).translate(x, y);
	getPoint(1).translate(x, y);
}