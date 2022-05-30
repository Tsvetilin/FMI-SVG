#pragma once
#include "Line.hpp"
#include "SVGShape.hpp"

class SVGLine : public virtual Line, public virtual SVGShape
{
public:
	SVGLine(double x1, double y1, double x2, double y2);
	SVGLine(const SVGElement& element);
	virtual void translate(double x, double y) override;
	virtual void print(std::ostream& stream) const override;
};
