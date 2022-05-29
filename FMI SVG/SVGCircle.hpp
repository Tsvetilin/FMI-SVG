#pragma once
#include "SVGShape.hpp"
#include "Circle.hpp"

class SVGCircle : public virtual Circle , public virtual SVGShape
{
public:
	SVGCircle(const SVGElement& element);
	virtual void translate(int x, int y);
};
