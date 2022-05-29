#pragma once
#include "Point.hpp"
#include "List.hpp"

class Shape
{
private:
	List<Point> points;

protected:
	const Point& getPoint(size_t index) const;
	Point& getPoint(size_t index);
	void setPoint(size_t index, int x, int y);

public:
	Shape(size_t pointsCount);

	size_t getPointsCount() const;

	virtual double getArea() const = 0;
	virtual double getPerimeter()  const = 0;
	virtual bool isPointIn(int x, int y) const = 0;
	virtual bool isPointIn(const Point& point) const;
	virtual bool isWithin(const Shape* other) const = 0;

	virtual void translate(int x, int y);

	virtual ~Shape() {}
};
