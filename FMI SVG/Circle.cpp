#include "Circle.hpp"

void Circle::createCircle(double x, double y, double r) {
	radius = r;
	setPoint(0, x, y);
}

Circle::Circle() :Shape(1),radius(0) {}

Circle::Circle(double x, double y, double r) : Shape(1)
{
	createCircle(x, y, r);
}

double Circle::getArea() const {
	return  PI * radius * radius;
}

double Circle::getPerimeter()  const {
	return 2 * PI * radius;
}

bool Circle::isPointIn(double x, double y) const {
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

void Circle::translate(double x, double y) {
	getPoint(0).translate(x, y);
}