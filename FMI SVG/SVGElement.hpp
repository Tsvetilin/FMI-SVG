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

	String determineName(ElementType type)const;
	ElementType determineElementType(const String& str)const;
	SVGAttribute* cloneAttribute(const SVGAttribute* other)const;
	void copyFrom(const SVGElement& other);
	void free();
	int getAttributeIndex(const String& name) const;
	void parseSVGString(const String& svgString);
	void addAttribute(const String& name, const String& value);
	void addAttribute(const String& name, double value);

public:

	SVGElement();
	SVGElement(ElementType type);
	SVGElement(const String& svgString);
	SVGElement(const SVGElement& other);
	SVGElement& operator=(const SVGElement& other);
	virtual ~SVGElement();

	ElementType getElementType() const;
	virtual bool setAttribute(const String& attributeName, const String& value);
	virtual bool setAttribute(const String& attributeName, double value);
	virtual bool addAttribute(const SVGAttribute& attribute);
	virtual bool containsAttribute(const String& attributeName)const;
	virtual SVGAttribute* getAttribute(const String& attributeName)const;
	virtual String getAttributeValue(const String& attributeName) const;
	virtual void writeSVGTag(std::ostream& stream) const;
	virtual String getSVGTag(std::ostream& stream) const;
};