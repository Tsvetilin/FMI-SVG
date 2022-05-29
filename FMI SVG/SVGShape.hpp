#pragma once
#include "Shape.hpp"
#include "SVGElement.hpp"

class SVGShape : public virtual Shape, public SVGElement {

public:
	SVGShape(const SVGElement& element, size_t pointsCount) :Shape(pointsCount), SVGElement(element) {

	}
};