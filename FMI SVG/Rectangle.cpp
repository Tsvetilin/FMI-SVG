#include "Rectangle.hpp"

void Rectangle::createRectangle(double x, double y, double width, double height) {
	setPoint(0, x, y);
	setPoint(1, x + width, y);
	setPoint(2, x + width, y - height);
	setPoint(3, x, y - height);
}

Rectangle::Rectangle() : Shape(4) {}

Rectangle::Rectangle(double x, double y, double width, double height) : Shape(4)
{
	createRectangle(x, y, width, height);
}

double Rectangle::getArea() const {
	double width = getPoint(0).distanceTo(getPoint(1));
	double height = getPoint(0).distanceTo(getPoint(3));
	return  width * height;
}

double Rectangle::getPerimeter()  const {
	double width = getPoint(0).distanceTo(getPoint(1));
	double height = getPoint(0).distanceTo(getPoint(3));
	return  2 * (width + height);
}

bool Rectangle::isPointIn(double x, double y) const {
	return x >= getPoint(0).getX() && x <= getPoint(1).getX() &&
		y <= getPoint(0).getY() && y >= getPoint(3).getY();
}

bool Rectangle::isWithin(const Shape* other) const {
	for (size_t i = 0; i < getPointsCount(); i++)
	{
		if (!other->isPointIn(getPoint(i))) {
			return false;
		}
	}

	return true;
}