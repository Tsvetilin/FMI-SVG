#include "SVGElement.hpp"

String SVGElement::determineName(ElementType type) const {
	if (type == ElementType::Reactangle) {
		return rectangleName;
	}
	else if (type == ElementType::Circle) {
		return circleName;
	}
	else if (type == ElementType::Line) {
		return lineName;
	}

	return "";
}

ElementType SVGElement::determineElementType(const String& str)const {
	if (str == circleName) {
		return ElementType::Circle;
	}
	else if (str == lineName) {
		return ElementType::Line;
	}
	else if (str == rectangleName) {
		return ElementType::Reactangle;
	}

	return ElementType::Unknown;
}

SVGAttribute* SVGElement::cloneAttribute(const SVGAttribute* other) const {
	if (const SVGGeometryAttribute* attr = dynamic_cast<const SVGGeometryAttribute*>(other)) {
		return new SVGGeometryAttribute(*attr);
	}
	else if (const SVGStyleAttribute* attr = dynamic_cast<const SVGStyleAttribute*>(other)) {
		return new SVGStyleAttribute(*attr);
	}
	else {
		return nullptr;
	}
}

void SVGElement::copyFrom(const SVGElement& other) {
	elementName = other.elementName;
	type = other.type;
	attributes = List<SVGAttribute*>(other.attributes.getCount());
	for (size_t i = 0; i < other.attributes.getCount(); i++)
	{
		attributes.add(cloneAttribute(other.attributes[i]));
	}
}

void SVGElement::free() {
	for (size_t i = 0; i < attributes.getCount(); i++)
	{
		delete attributes[i];
	}
}

int SVGElement::getAttributeIndex(const String& name) const {
	for (size_t i = 0; i < attributes.getCount(); i++)
	{
		if (attributes[i]->getName() == name) {
			return i;
		}
	}

	return -1;
}

void SVGElement::parseSVGString(const String& svgString) {
	String str = svgString.substr(1, svgString.getLength() - 1);

	elementName = std::move(matchCmd(str));
	type = determineElementType(elementName);

	if (type == ElementType::Unknown) {
		return;
	}

	str = std::move(skipCmd(str));
	while (str.indexOf('"') != -1) {
		addAttribute(getToEqualSign(str), getQuotes(str));
		str = std::move(getAfterQuotes(str));
	}
}

void SVGElement::addAttribute(const String& name, const String& value) {
	if (geometryAttributesList.contains(name)) {
		attributes.add(new SVGGeometryAttribute(name, value));
	}
	else {
		attributes.add(new SVGStyleAttribute(name, value));
	}
}

void SVGElement::addAttribute(const String& name, double value) {
	if (geometryAttributesList.contains(name)) {
		attributes.add(new SVGGeometryAttribute(name, ""));
	}
	else {
		attributes.add(new SVGStyleAttribute(name, ""));
	}

	setAttribute(name, value);
}

SVGElement::SVGElement() :type(ElementType::Unknown) {}

SVGElement::SVGElement(ElementType type) : type(type) {
	elementName = determineName(type);
}

SVGElement::SVGElement(const String& svgString) {
	parseSVGString(svgString);
}

SVGElement::SVGElement(const SVGElement& other) {
	copyFrom(other);
}

SVGElement& SVGElement::operator=(const SVGElement& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

SVGElement::~SVGElement() {
	free();
}

ElementType SVGElement::getElementType() const {
	return type;
}

bool SVGElement::setAttribute(const String& attributeName, const String& value) {
	int index = getAttributeIndex(attributeName);
	if (index == -1) {
		return false;
	}

	attributes[index]->setValue(value);
	return true;
}

bool SVGElement::setAttribute(const String& attributeName, double value) {
	int index = getAttributeIndex(attributeName);
	if (index == -1) {
		return false;
	}

	attributes[index]->setValue(value);
	return true;
}

bool SVGElement::addAttribute(const SVGAttribute& attribute) {
	// TODO: duplicate check
	attributes.add(cloneAttribute(&attribute));
	return true;
}

bool SVGElement::containsAttribute(const String& attributeName)const {
	return getAttributeIndex(attributeName) != -1;
}

SVGAttribute* SVGElement::getAttribute(const String& attributeName)const {
	int index = getAttributeIndex(attributeName);
	if (index == -1) {
		throw std::out_of_range("Attribute not found.");
		return nullptr;
	}

	return attributes[index];
}

String SVGElement::getAttributeValue(const String& attributeName) const {
	return getAttribute(attributeName)->getValueAsString();
}

void SVGElement::writeSVGTag(std::ostream& stream) const {
	stream << getSVGTag(stream);
}

String SVGElement::getSVGTag(std::ostream& stream) const {
	String result = String("<") + elementName + " ";
	for (size_t i = 0; i < attributes.getCount(); i++)
	{
		result += attributes[i]->getAttribute() + " ";
	}

	result += "/>";

	return std::move(result);
}