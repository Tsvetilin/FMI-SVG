#pragma once
#include <cmath>

class Point
{
	double x;
	double y;

public:
	Point() :x(0), y(0) {}
	Point(double x, double y) :x(x), y(y) {}

	double distanceTo(const Point& other) const
	{
		return distanceTo(other.x, other.y);
	}

	double distanceTo(double x, double y) const
	{
		double dx = this->x - x;
		double dy = this->y - y;

		return sqrt(dx * dx + dy * dy);
	}

	void translate(double dx, double dy) {
		x += dx;
		y += dy;
	}

	void set(double x, double y) {
		this->x = x;
		this->y = y;
	}

	double getX()const {
		return x;
	}

	double getY()const {
		return y;
	}
};