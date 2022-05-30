#include "SVGRectangle.hpp"

SVGRectangle::SVGRectangle(double x, double y, double width, double heigth) :
	SVGShape(4, ElementType::Reactangle), Shape(4) {
	createRectangle(x, y, width, heigth);
	setAttribute("x", getPoint(0).getX());
	setAttribute("y", getPoint(0).getY());
	setAttribute("width", width);
	setAttribute("heigth", heigth);
}

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


void SVGRectangle::print(std::ostream& stream) const {
	stream << "rectangle " << getPoint(0).getX() << " " << getPoint(0).getX() << " " <<
		getAttribute("width")->getValueAsDouble() << " " << getAttribute("heigth")->getValueAsDouble() << " ";

	for (size_t i = 0; i < attributes.getCount(); i++)
	{
		if (attributes[i]->getType() == AttributeType::Style) {
			attributes[i]->writeAttribute(stream);
			stream << " ";

		}
	}
}