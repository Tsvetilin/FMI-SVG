#include "Circle.hpp"

Circle::Circle() :Shape(1),radius(0) {}

Circle::Circle(double x, double y, double r) : Shape(1)
{
	radius = r;
	setPoint(0, x, y);
}

double Circle::getArea() const {
	return  PI * radius * radius;
}

double Circle::getPerimeter()  const {
	return 2 * PI * radius;
}

bool Circle::isPointIn(int x, int y) const {
	return getPoint(0).distanceTo(x, y) < radius;

}

bool Circle::isWithin(const Shape* other) const {
	double centerX = getPoint(0).getX();
	double centerY = getPoint(0).getY();

	return other->isPointIn(centerX + radius, centerY) &&
		other->isPointIn(centerX - radius, centerY) &&
		other->isPointIn(centerX, centerY + radius) &&
		other->isPointIn(centerX, centerY - radius);
}

void Circle::translate(int x, int y) {
	getPoint(0).translate(x, y);
}