#include "SVGStyleAttribute.hpp"

SVGStyleAttribute::SVGStyleAttribute(const String& name, const String& value) :SVGAttribute(name, AttributeType::Style) {
	// TODO: valid attribute name check
	this->name = name;
	setValue(value);
}

bool SVGStyleAttribute::setValue(const String& value) {
	// TODO: validate value for attribute
	this->value = value;
	return true;
}

double SVGStyleAttribute::getValueAsDouble() const {
	return 0;
}