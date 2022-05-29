#pragma once
#include "Rectangle.hpp"
#include "SVGElement.hpp"


class SVGRectangle : public virtual Rectangle, public virtual SVGShape
{
public:
	SVGRectangle(const SVGElement& element);
	virtual void translate(int x, int y) override;
};