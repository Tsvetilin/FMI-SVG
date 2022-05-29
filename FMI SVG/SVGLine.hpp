#include "Line.hpp"
#include "SVGShape.hpp"

class SVGLine : public virtual Line, public virtual SVGShape
{
public:
	SVGLine(const SVGElement& element);
	virtual void translate(int x, int y) override;
};

SVGLine::SVGLine(const SVGElement& element) :SVGShape(element, 2), Line(), Shape(2)
{
	double x1 = getAttribute("x1")->getValueAsDouble();
	double x2 = getAttribute("x2")->getValueAsDouble();
	double y1 = getAttribute("y1")->getValueAsDouble();
	double y2 = getAttribute("y2")->getValueAsDouble();

	setPoint(0, x1, y1);
	setPoint(0, x2, y2);
}

void SVGLine::translate(int x, int y) {
	getPoint(0).translate(x, y);
	getPoint(1).translate(x, y);

	setAttribute("x1", getPoint(0).getX());
	setAttribute("x2", getPoint(1).getX());
	setAttribute("y1", getPoint(0).getY());
	setAttribute("y2", getPoint(1).getY());
}