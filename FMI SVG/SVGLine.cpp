#include "SVGLine.hpp"

SVGLine::SVGLine(double x1, double y1, double x2, double y2) :SVGShape(2, ElementType::Line), Shape(2) {
	createLine(x1, y1, x2, y2);
}

SVGLine::SVGLine(const SVGElement& element) : SVGShape(element, 2), Shape(2)
{
	double x1 = getAttribute("x1")->getValueAsDouble();
	double x2 = getAttribute("x2")->getValueAsDouble();
	double y1 = getAttribute("y1")->getValueAsDouble();
	double y2 = getAttribute("y2")->getValueAsDouble();

	createLine(x1, y1, x2, y2);
}

void SVGLine::translate(double x, double y) {
	Line::translate(x, y);

	setAttribute("x1", getPoint(0).getX());
	setAttribute("x2", getPoint(1).getX());
	setAttribute("y1", getPoint(0).getY());
	setAttribute("y2", getPoint(1).getY());
}

void SVGLine::print(std::ostream& stream) const {
	stream << "line " << getPoint(0).getX() << " " << getPoint(0).getY() << " " <<
		getPoint(1).getX() << " " << getPoint(1).getY() << " ";

	for (size_t i = 0; i < attributes.getCount(); i++)
	{
		if (attributes[i]->getType() == AttributeType::Style) {
			attributes[i]->writeAttribute(stream);
			stream << " ";

		}
	}
}
