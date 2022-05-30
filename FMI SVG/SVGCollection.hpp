#pragma once
#include "SVGShape.hpp"
#include "SVGCircle.hpp"
#include "SVGRectangle.hpp"
#include "SVGLine.hpp"

class SVGCollection : IPrintable {
	List<SVGShape*> shapes;
	String svgMetadata;

	SVGShape* clone(SVGShape* other) const;
	void copyFrom(const SVGCollection&);
	void free();

	void parseDocument(std::ostream& input);

public:
	SVGCollection();
	SVGCollection(const SVGCollection&);
	SVGCollection& operator=(const SVGCollection&);
	~SVGCollection();

	bool loadDocument(const String& path);
	bool saveDocument(const String& path) const;

	bool translateAll(double x, double y);
	bool translateSingle(double x, double y, size_t index);
	bool erase(size_t index);
	bool createRectangle(double x, double y, double width, double height, const String& fill);
	bool createCircle(double x, double y, double r, const String& fill);
	bool createLine(double x1, double y1, double x2, double y2, const String& stroke);

	bool printWithInRectangle(std::ostream& stream, double x, double y, double width, double height);
	bool printWithInCircle(std::ostream& stream, double x, double y, double r);
	bool printPointIn(std::ostream& stream, double x, double y);

	void printAreas(std::ostream& stream) const;
	void printPerimeters(std::ostream& stream) const;
	virtual void print(std::ostream& stream) const override;

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
	if (SVGCircle* circle = dynamic_cast<SVGCircle*>(other)) {
		return new SVGCircle(*circle);
	}
	else if (SVGRectangle* rect = dynamic_cast<SVGRectangle*>(other)) {
		return new SVGRectangle(*rect);
	}
	else if (SVGLine* line = dynamic_cast<SVGLine*>(other)) {
		return new SVGLine(*line);
	}
	else {
		return nullptr;
	}
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

bool SVGCollection::translateAll(double x, double y) {
	for (size_t i = 0; i < shapes.getCount(); i++)
	{
		shapes[i]->translate(x, y);
	}
	return true;
}

bool SVGCollection::translateSingle(double x, double y, size_t index) {
	if (index >= shapes.getCount()) {
		return false;
	}

	shapes[index]->translate(x, y);
	return true;
}

bool SVGCollection::erase(size_t index) {
	if (index >= shapes.getCount()) {
		return false;
	}

	delete shapes[index];
	shapes.removeAt(index);
	return true;
}

bool SVGCollection::createRectangle(double x, double y, double width, double height, const String& fill) {
	SVGRectangle* rectangle = new SVGRectangle(x, y, width, height);
	rectangle->addAttribute(SVGStyleAttribute("fill", fill));
	shapes.add(rectangle);
}

bool SVGCollection::createCircle(double x, double y, double r, const String& fill) {
	SVGCircle* circle = new SVGCircle(x, y, r);
	circle->addAttribute(SVGStyleAttribute("fill", fill));
	shapes.add(circle);
}

bool SVGCollection::createLine(double x1, double y1, double x2, double y2, const String& stroke) {
	SVGLine* line = new SVGLine(x1, y1, x2, y2);
	line->addAttribute(SVGStyleAttribute("stroke", stroke));
	shapes.add(line);
}

bool SVGCollection::printWithInRectangle(std::ostream& stream, double x, double y, double width, double height) {
	Shape* rect = new Rectangle(x, y, width, height);
	for (size_t i = 0; i < shapes.getCount(); i++)
	{
		if (shapes[i]->isWithin(rect)) {
			shapes[i]->print(stream);
		}
	}
}

bool SVGCollection::printWithInCircle(std::ostream& stream, double x, double y, double r) {
	Shape* circle = new Circle(x, y, r);
	for (size_t i = 0; i < shapes.getCount(); i++)
	{
		if (shapes[i]->isWithin(circle)) {
			shapes[i]->print(stream);
		}
	}
}

bool SVGCollection::printPointIn(std::ostream& stream, double x, double y) {
	for (size_t i = 0; i < shapes.getCount(); i++)
	{
		if (shapes[i]->isPointIn(x, y)) {
			shapes[i]->print(stream);
		}
	}
}

void SVGCollection::printAreas(std::ostream& stream) const;
void SVGCollection::printPerimeters(std::ostream& stream) const;

void SVGCollection::print(std::ostream& stream) const
{
	for (size_t i = 0; i < shapes.getCount(); i++)
	{
		stream << (i + 1) << ". ";
		shapes[i]->print(stream);
		stream << std::endl;
	}
}
