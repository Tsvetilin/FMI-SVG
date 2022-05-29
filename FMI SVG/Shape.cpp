#include "Shape.hpp"

Point& Shape::getPoint(size_t index) {
	return points[index];
}

const Point& Shape::getPoint(size_t index) const {
	return points[index];
}

void Shape::setPoint(size_t index, int x, int y) {
	if (index < points.getCount()) {
		points[index].set(x, y);
	}
}

Shape::Shape(size_t pointsCount) :points(pointsCount) {
	for (size_t i = 0; i < pointsCount; i++)
	{
		points.add(Point());
	}
}

void Shape::translate(int x, int y) {
	for (size_t i = 0; i < points.getCount(); i++)
	{
		points[i].translate(x, y);
	}
}

size_t Shape::getPointsCount() const {
	return points.getCount();
}

bool Shape::isPointIn(const Point& point) const {
	return isPointIn(point.getX(), point.getY());
}