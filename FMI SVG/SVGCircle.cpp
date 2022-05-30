#include "SVGCircle.hpp"

SVGCircle::SVGCircle(const SVGElement& element) : SVGShape(element, 1), Shape(1)
{
	double cx = getAttribute("cx")->getValueAsDouble();
	double cy = getAttribute("cy")->getValueAsDouble();
	radius = getAttribute("r")->getValueAsDouble();

	setPoint(0, cx, cy);
}

void SVGCircle::translate(int x, int y) {
	getPoint(0).translate(x, y);
	setAttribute("x", getPoint(0).getX());
	setAttribute("y", getPoint(0).getY());
}