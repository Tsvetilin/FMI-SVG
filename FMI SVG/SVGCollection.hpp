#pragma once
#include "SVGShape.hpp"
#include "Circle.hpp"
#include "Rectangle.hpp"
#include "Line.hpp"

class SVGCollection {
	List<SVGShape*> shapes;
	String svgMetadata;

	SVGShape* clone(SVGShape* other) const;
	void copyFrom(const SVGCollection&);
	void free();

public:
	SVGCollection();
	SVGCollection(const SVGCollection&);
	SVGCollection& operator=(const SVGCollection&);
	~SVGCollection();

	bool loadDocument(const String& path);

	bool saveDocument(const String& path) const;

};

SVGCollection::SVGCollection() {}

SVGCollection::SVGCollection(const SVGCollection& other) {
	copyFrom(other);
}

SVGCollection& SVGCollection::operator=(const SVGCollection& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

SVGCollection::~SVGCollection() {
	free();
}

bool SVGCollection::loadDocument(const String& path) {

	return true;
}

bool SVGCollection::saveDocument(const String& path) const {
	return true;
}

SVGShape* SVGCollection::clone(SVGShape* other) const {
/*	if (Circle* circle = dynamic_cast<Circle*>(other)) {
		return new Circle(*circle);
	}
	else if(Rectangle * rect = dynamic_cast<Rectangle*>(other)) {
		return new Rectangle(*rect);
	}
	else if (Line* line = dynamic_cast<Line*>(other)) {
		return new Line(*line);
	}
	else {
		return nullptr;
	}*/
	return nullptr;
}

void SVGCollection::copyFrom(const SVGCollection& other) {
	svgMetadata = other.svgMetadata;
	shapes = List<SVGShape*>(other.shapes.getCount());
	for (size_t i = 0; i < other.shapes.getCount(); i++)
	{
		shapes.add(clone(other.shapes[i]));
	}
}

void SVGCollection::free() {
	for (size_t i = 0; i < shapes.getCount(); i++)
	{
		delete shapes[i];
	}
}