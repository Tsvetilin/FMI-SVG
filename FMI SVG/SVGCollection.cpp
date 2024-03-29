#include "SVGCollection.hpp"

void SVGCollection::addShape(const SVGElement& element) {
	switch (element.getElementType())
	{
	case ElementType::Circle: shapes.add(new SVGCircle(element)); return;
	case ElementType::Reactangle: shapes.add(new SVGRectangle(element)); return;
	case ElementType::Line: shapes.add(new SVGLine(element));  return;
	default:return;
	}
}

bool SVGCollection::parseDocument(std::istream& input) {
	String str;
	String currentTag;
	bool isInSvg = false;
	bool hasCompletedTag = true;
	while (!input.eof()) {
		str = getline(input);
		while (str != "") {
			int startInd = str.indexOf('<');
			int endInd = str.indexOf('>');
			String current;
			// tag opens and closes here
			if (endInd != -1 && hasCompletedTag && startInd < endInd && startInd != -1) {
				hasCompletedTag = true;
				current = std::move(str.substr(startInd, endInd - startInd + 1));
				str = str.substr(endInd + 1, str.getLength() - endInd - 1);
			}
			// tag was opened before and closes here
			else if (endInd != -1 && !hasCompletedTag && (startInd > endInd || startInd == -1)) {
				hasCompletedTag = true;
				current = std::move(str.substr(0, endInd + 1));
				str = str.substr(endInd + 1, str.getLength() - endInd - 1);
			}
			// tag is opened here but not closed
			else if (endInd == -1 && startInd != -1 && hasCompletedTag) {
				hasCompletedTag = false;
				current = std::move(str.substr(startInd, str.getLength() - startInd));
				str = "";
			}
			//tag neither opens nor closes here
			else if (endInd == -1 && startInd == -1) {
				str = "";
				current = str;
			}
			else return false;

			if (isInSvg) {
				currentTag += current;

				if (currentTag == "</svg>") {
					return true;
				}
			}
			else {
				if (current == "<svg>") {
					isInSvg = true;
					continue;
				}

				svgMetadata += current + "\n";
			}

			if (isInSvg && hasCompletedTag) {
				SVGElement element(currentTag);
				if (element.getElementType() != ElementType::Unknown) {
					addShape(element);
				}
				currentTag = "";
			}
		}
	}

	return false;
}

SVGCollection::SVGCollection() :isLoaded(false) {}

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
	if (isLoaded) {
		return false;
	}

	std::ifstream file(path.c_str());

	if (!file.is_open()) {
		return false;
	}

	bool success = parseDocument(file);
	isLoaded = success;

	file.close();
	return success;
}

bool SVGCollection::saveDocument(const String& path) {
	if (!isLoaded) {
		return false;
	}

	std::ofstream file(path.c_str());

	if (!file.is_open()) {
		return false;
	}

	file << svgMetadata;
	file << "\n<svg>\n";
	for (size_t i = 0; i < shapes.getCount(); i++)
	{
		shapes[i]->writeSVGTag(file);
		file << "\n";
	}
	file << "</svg>\n";

	file.close();
	
	isLoaded = false;

	free();
	shapes.clear();
	svgMetadata = "";
	return !isLoaded;
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
	if (!isLoaded) {
		return false;
	}

	for (size_t i = 0; i < shapes.getCount(); i++)
	{
		shapes[i]->translate(x, y);
	}
	return true;
}

bool SVGCollection::translateSingle(double x, double y, size_t index) {
	if (!isLoaded) {
		return false;
	}

	if (index >= shapes.getCount()) {
		return false;
	}

	shapes[index]->translate(x, y);
	return true;
}

bool SVGCollection::erase(size_t index) {
	if (!isLoaded) {
		return false;
	}

	if (index >= shapes.getCount()) {
		return false;
	}

	delete shapes[index];
	shapes.removeAt(index);
	return true;
}

bool SVGCollection::createRectangle(double x, double y, double width, double height, const String& fill) {
	if (!isLoaded) {
		return false;
	}

	if (width < 0 || height < 0) {
		return false;
	}

	SVGRectangle* rectangle = new SVGRectangle(x, y, width, height);
	if (!rectangle->addAttribute(SVGStyleAttribute("fill", fill))) {
		delete rectangle;
		return false;
	}

	shapes.add(rectangle);
	return true;
}

bool SVGCollection::createCircle(double x, double y, double r, const String& fill) {
	if (!isLoaded) {
		return false;
	}

	if (r < 0) {
		return false;
	}

	SVGCircle* circle = new SVGCircle(x, y, r);
	if (!circle->addAttribute(SVGStyleAttribute("fill", fill))) {
		delete circle;
		return false;
	}

	shapes.add(circle);

	return true;
}

bool SVGCollection::createLine(double x1, double y1, double x2, double y2, const String& stroke) {
	if (!isLoaded) {
		return false;
	}

	SVGLine* line = new SVGLine(x1, y1, x2, y2);

	if (!line->addAttribute(SVGStyleAttribute("stroke", stroke))) {
		delete line;
		return false;
	}

	shapes.add(line);
	return true;
}

bool SVGCollection::printWithInRectangle(std::ostream& stream, double x, double y, double width, double height) {
	if (!isLoaded) {
		return false;
	}

	if (width < 0 || height < 0) {
		return false;
	}

	Rectangle rect = Rectangle(x, y, width, height);
	bool printed = false;
	for (size_t i = 0; i < shapes.getCount(); i++)
	{
		if (shapes[i]->isWithin(&rect)) {
			stream << (i + 1) << ". ";
			shapes[i]->print(stream);
			stream << std::endl;
			printed = true;
		}
	}

	if (!printed) {
		stream << "No shapes within the rectangle!" << std::endl;
	}

	return true;
}

bool SVGCollection::printWithInCircle(std::ostream& stream, double x, double y, double r) {
	if (!isLoaded) {
		return false;
	}

	if (r < 0) {
		return false;
	}

	bool printed = false;
	Circle circle = Circle(x, y, r);
	for (size_t i = 0; i < shapes.getCount(); i++)
	{
		if (shapes[i]->isWithin(&circle)) {
			stream << (i + 1) << ". ";
			shapes[i]->print(stream);
			stream << std::endl;
			printed = true;
		}
	}

	if (!printed) {
		stream << "No shapes within the circle!" << std::endl;
	}

	return true;
}

void SVGCollection::printPointIn(std::ostream& stream, double x, double y) {
	if (!isLoaded) {
		return;
	}

	bool printed = false;

	for (size_t i = 0; i < shapes.getCount(); i++)
	{
		if (shapes[i]->isPointIn(x, y)) {
			stream << (i + 1) << ". ";
			shapes[i]->print(stream);
			stream << std::endl;
			printed = true;
		}
	}

	if (!printed) {
		stream << "No shapes include the point specified!" << std::endl;
	}
}

void SVGCollection::printAreas(std::ostream& stream) const {
	if (!isLoaded) {
		return;
	}

	for (size_t i = 0; i < shapes.getCount(); i++)
	{
		stream << (i + 1) << ". ";
		stream << shapes[i]->getArea();
		stream << std::endl;
	}
}

void SVGCollection::printPerimeters(std::ostream& stream) const {
	if (!isLoaded) {
		return;
	}

	for (size_t i = 0; i < shapes.getCount(); i++)
	{
		stream << (i + 1) << ". ";
		stream << shapes[i]->getPerimeter();
		stream << std::endl;
	}
}

void SVGCollection::print(std::ostream& stream) const
{
	if (!isLoaded) {
		return;
	}

	for (size_t i = 0; i < shapes.getCount(); i++)
	{
		stream << (i + 1) << ". ";
		shapes[i]->print(stream);
		stream << std::endl;
	}
}
