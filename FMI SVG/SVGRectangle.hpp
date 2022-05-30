#pragma once
#include "Rectangle.hpp"
#include "SVGElement.hpp"


class SVGRectangle : public virtual Rectangle, public virtual SVGShape
{
public:
	SVGRectangle(const SVGElement& element);
	SVGRectangle(double x, double y, double width, double height);
	virtual void translate(double x, double y) override;
	virtual void print(std::ostream& stream) const override;
};