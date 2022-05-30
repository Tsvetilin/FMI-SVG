#include "SVGRectangle.hpp"

SVGRectangle::SVGRectangle(double x, double y, double width, double height) :
	SVGShape(4, ElementType::Reactangle), Shape(4) {
	createRectangle(x, y, width, height);
	addAttribute(xName, getPoint(0).getX());
	addAttribute(yName, getPoint(0).getY());
	addAttribute(widthName, width);
	addAttribute(heightName, height);
}

SVGRectangle::SVGRectangle(const SVGElement& element) : SVGShape(element, 4), Shape(4)
{
	double x = getAttribute(xName)->getValueAsDouble();
	double y = getAttribute(yName)->getValueAsDouble();
	double width = getAttribute(widthName)->getValueAsDouble();
	double height = getAttribute(heightName)->getValueAsDouble();
	createRectangle(x, y, width, height);
}

void SVGRectangle::translate(double x, double y) {
	Rectangle::translate(x, y);
	setAttribute(xName, getPoint(0).getX());
	setAttribute(yName, getPoint(0).getY());
}


void SVGRectangle::print(std::ostream& stream) const {
	stream << "rectangle " << getPoint(0).getX() << " " << getPoint(0).getY() << " " <<
		getAttribute(widthName)->getValueAsDouble() << " " << getAttribute(heightName)->getValueAsDouble() << " ";

	for (size_t i = 0; i < attributes.getCount(); i++)
	{
		if (attributes[i]->getType() == AttributeType::Style) {
			attributes[i]->writeAttribute(stream);
			stream << " ";

		}
	}
}