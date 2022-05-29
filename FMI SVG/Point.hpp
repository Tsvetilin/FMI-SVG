#pragma once
#include <cmath>

class Point
{
	int x;
	int y;

public:
	Point() :x(0), y(0) {}
	Point(int x, int y) :x(x), y(y) {}

	double distanceTo(const Point& other) const
	{
		return distanceTo(other.x, other.y);
	}

	double distanceTo(int x, int y) const
	{
		int dx = this->x - x;
		int dy = this->y - y;

		return sqrt(dx * dx + dy * dy);
	}

	void translate(int dx, int dy) {
		x += dx;
		y += dy;
	}

	void set(int x, int y) {
		this->x = x;
		this->y = y;
	}

	int getX()const {
		return x;
	}

	int getY()const {
		return y;
	}
};