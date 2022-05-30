#include "SVGCircle.hpp"

SVGCircle::SVGCircle(double x, double y, double r) :SVGShape(1, ElementType::Circle), Shape(1) {
	createCircle(x, y, r);

	setAttribute("cx", x);
	setAttribute("cy", y);
	setAttribute("r", r);
}

SVGCircle::SVGCircle(const SVGElement& element) : SVGShape(element, 1), Shape(1)
{
	double x = getAttribute("cx")->getValueAsDouble();
	double y = getAttribute("cy")->getValueAsDouble();
	double r = getAttribute("r")->getValueAsDouble();

	createCircle(x, y, r);
}

void SVGCircle::translate(double x, double y) {
	getPoint(0).translate(x, y);
	setAttribute("cx", getPoint(0).getX());
	setAttribute("cy", getPoint(0).getY());
}

void SVGCircle::print(std::ostream& stream) const {
	stream << "line " << getPoint(0).getX() << " " << getPoint(0).getY() << " " << radius << " ";

	for (size_t i = 0; i < attributes.getCount(); i++)
	{
		if (attributes[i]->getType() == AttributeType::Style) {
			attributes[i]->writeAttribute(stream);
			stream << " ";
		}
	}
}