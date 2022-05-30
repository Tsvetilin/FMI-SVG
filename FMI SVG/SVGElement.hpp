#pragma once
#include "List.hpp"
#include <iostream>
#include "SVGStyleAttribute.hpp"
#include "SVGGeometryAttribute.hpp"

enum class ElementType {
	Unknown,
	Reactangle,
	Circle,
	Line,
};

class SVGElement {
protected:
	List<SVGAttribute*> attributes;
	String elementName;
	ElementType type;

	SVGAttribute* cloneAttribute(const SVGAttribute* other) {
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

	void copyFrom(const SVGElement& other) {
		elementName = other.elementName;
		type = other.type;
		attributes = List<SVGAttribute*>(other.attributes.getCount());
		for (size_t i = 0; i < other.attributes.getCount(); i++)
		{
			attributes.add(cloneAttribute(other.attributes[i]));
		}
	}

	void free() {
		for (size_t i = 0; i < attributes.getCount(); i++)
		{
			delete attributes[i];
		}
	}

	int getAttributeIndex(const String& name) const {
		for (size_t i = 0; i < attributes.getCount(); i++)
		{
			if (attributes[i]->getName() == name) {
				return i;
			}
		}

		return -1;
	}

	void parseSVGString(const String& svgString) {

	}

public:

	SVGElement() :type(ElementType::Unknown) {}

	SVGElement(ElementType type):type(type){
		//name = determineName(type);
	}

	SVGElement(const String& svgString) {
		parseSVGString(svgString);
	}

	SVGElement(const SVGElement& other) {
		copyFrom(other);
	}

	SVGElement& operator=(const SVGElement& other) {
		if (this != &other) {
			free();
			copyFrom(other);
		}

		return *this;
	}

	virtual ~SVGElement() {
		free();
	}

	ElementType getElementType() const {
		return type;
	}

	virtual bool setAttribute(const String& attributeName, const String& value) {
		int index = getAttributeIndex(attributeName);
		if (index == -1) {
			return false;
		}

		attributes[index]->setValue(value);
		return true;
	}

	virtual bool setAttribute(const String& attributeName, double value) {
		int index = getAttributeIndex(attributeName);
		if (index == -1) {
			return false;
		}

		attributes[index]->setValue(value);
		return true;
	}

	virtual bool addAttribute(const SVGAttribute& attribute) {
		// TODO: duplicate check
		attributes.add(cloneAttribute(&attribute));
		return true;
	}

	virtual bool containsAttribute(const String& attributeName)const {
		return getAttributeIndex(attributeName) != -1;
	}

	virtual SVGAttribute* getAttribute(const String& attributeName)const {
		int index = getAttributeIndex(attributeName);
		if (index == -1) {
			throw std::out_of_range("Attribute not found.");
			return nullptr;
		}

		return attributes[index];
	}

	virtual String getAttributeValue(const String& attributeName) const {
		return getAttribute(attributeName)->getValueAsString();
	}

	virtual void writeSVGTag(std::ostream& stream) const {
		stream << getSVGTag(stream);
	}

	virtual String getSVGTag(std::ostream& stream) const {
		String result = String("<") + elementName + " ";
		for (size_t i = 0; i < attributes.getCount(); i++)
		{
			result += attributes[i]->getAttribute() + " ";
		}

		result += ">";

		return std::move(result);
	}
};
/*
ElementType determineElementType(const String& str) {
	return ElementType::Unknown;
}

*/