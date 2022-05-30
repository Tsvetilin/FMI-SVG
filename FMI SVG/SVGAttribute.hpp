#pragma once
#include "String.hpp"
#include "Common.hpp"

enum class AttributeType {
	Unknown,
	Geometry,
	Style,
};

class SVGAttribute {
private:
	AttributeType type;

protected:
	String name;
	String value;

public:
	SVGAttribute(const String& name, AttributeType type) :type(type) {
		this->name = name;
	}

	virtual bool setValue(const String& v) = 0;

	virtual bool setValue(double v) {
		setValue(String(v));
		return true;
	}

	String getName() const {
		return name;
	}

	AttributeType getType()const {
		return type;
	}

	String getValueAsString() const {
		return value;
	}

	virtual double getValueAsDouble() const {
		return parseToDouble(value);
	}

	virtual void writeAttribute(std::ostream& stream) const {
		stream << getAttribute();
	}

	virtual String getAttribute() const {
		return name + "=\"" + value + "\"";
	}
};

/*
AttributeType determineAttributeType(const String& str) {
	return AttributeType::Unknown;
}
*/