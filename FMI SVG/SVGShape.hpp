#pragma once
#include "Shape.hpp"
#include "SVGElement.hpp"

class SVGShape : public virtual Shape, public SVGElement, public virtual IPrintable {

public:
	SVGShape(const SVGElement& element, size_t pointsCount) :Shape(pointsCount), SVGElement(element) {

	}

	SVGShape(size_t pointsCount, ElementType type) :Shape(pointsCount), SVGElement(type) {

	}

	virtual ~SVGShape(){}
};