#include "Rectangle.hpp"


void Rectangle::createRectangle(double x, double y, double width, double heigth) {
	setPoint(0, x, y);
	setPoint(1, x + width, y);
	setPoint(2, x + width, y + heigth);
	setPoint(3, x, y + heigth);
}

Rectangle::Rectangle() : Shape(4) {}

Rectangle::Rectangle(double x, double y, double width, double heigth) : Shape(4)
{
	createRectangle(x, y, width, heigth);
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

bool Rectangle::isPointIn(int x, int y) const {
	return x >= getPoint(0).getX() && x <= getPoint(1).getX() &&
		y >= getPoint(0).getY() && y <= getPoint(3).getY();
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

void Rectangle::translate(int x, int y) {
	for (size_t i = 0; i < getPointsCount(); i++)
	{
		getPoint(i).translate(x, y);
	}
}