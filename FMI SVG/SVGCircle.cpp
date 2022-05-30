#include "SVGCircle.hpp"

SVGCircle::SVGCircle(double x, double y, double r) :SVGShape(1, ElementType::Circle), Shape(1) {
	createCircle(x, y, r);

	addAttribute(cxName, x);
	addAttribute(cyName, y);
	addAttribute(rName, r);
}

SVGCircle::SVGCircle(const SVGElement& element) : SVGShape(element, 1), Shape(1)
{
	double x = getAttribute(cxName)->getValueAsDouble();
	double y = getAttribute(cyName)->getValueAsDouble();
	double r = getAttribute(rName)->getValueAsDouble();

	createCircle(x, y, r);
}

void SVGCircle::translate(double x, double y) {
	getPoint(0).translate(x, y);
	setAttribute(cxName, getPoint(0).getX());
	setAttribute(cyName, getPoint(0).getY());
}

void SVGCircle::print(std::ostream& stream) const {
	stream << "circle " << getPoint(0).getX() << " " << getPoint(0).getY() << " " << radius << " ";

	for (size_t i = 0; i < attributes.getCount(); i++)
	{
		if (attributes[i]->getType() == AttributeType::Style) {
			attributes[i]->writeAttribute(stream);
			stream << " ";
		}
	}
}