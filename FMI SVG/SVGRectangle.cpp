#include "SVGRectangle.hpp"

SVGRectangle::SVGRectangle(const SVGElement& element) : SVGShape(element, 4), Shape(4)
{
	double x = getAttribute("x")->getValueAsDouble();
	double y = getAttribute("y")->getValueAsDouble();
	double width = getAttribute("width")->getValueAsDouble();
	double heigth = getAttribute("heigth")->getValueAsDouble();
	createRectangle(x, y, width, heigth);
}

void SVGRectangle::translate(int x, int y) {
	Rectangle::translate(x, y);
	setAttribute("x", getPoint(0).getX());
	setAttribute("y", getPoint(0).getY());
}