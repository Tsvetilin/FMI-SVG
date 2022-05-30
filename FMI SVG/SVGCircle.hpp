#pragma once
#include "SVGShape.hpp"
#include "Circle.hpp"

class SVGCircle : public virtual Circle , public virtual SVGShape
{
public:
	SVGCircle(const SVGElement& element);
	SVGCircle(double x, double y, double r);
	virtual void translate(double x, double y);
	virtual void print(std::ostream& stream) const override;
};
