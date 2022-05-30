#pragma once
#include "SVGShape.hpp"
#include "SVGCircle.hpp"
#include "SVGRectangle.hpp"
#include "SVGLine.hpp"
#include <fstream>

class SVGCollection : IPrintable {
	List<SVGShape*> shapes;
	String svgMetadata;

	bool isLoaded;

	void addShape(const SVGElement& element);
	SVGShape* clone(SVGShape* other) const;
	void copyFrom(const SVGCollection&);
	void free();

	bool parseDocument(std::istream& input);

public:
	SVGCollection();
	SVGCollection(const SVGCollection&);
	SVGCollection& operator=(const SVGCollection&);
	~SVGCollection();

	bool loadDocument(const String& path);
	bool saveDocument(const String& path);

	bool translateAll(double x, double y);
	bool translateSingle(double x, double y, size_t index);
	bool erase(size_t index);
	bool createRectangle(double x, double y, double width, double height, const String& fill);
	bool createCircle(double x, double y, double r, const String& fill);
	bool createLine(double x1, double y1, double x2, double y2, const String& stroke);

	bool printWithInRectangle(std::ostream& stream, double x, double y, double width, double height);
	bool printWithInCircle(std::ostream& stream, double x, double y, double r);
	void printPointIn(std::ostream& stream, double x, double y);

	void printAreas(std::ostream& stream) const;
	void printPerimeters(std::ostream& stream) const;
	virtual void print(std::ostream& stream) const override;

};
