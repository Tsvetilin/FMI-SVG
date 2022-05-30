#pragma once
#include "SVGAttribute.hpp"

class SVGStyleAttribute : public SVGAttribute {

public:
	SVGStyleAttribute(const String& name, const String& value) :SVGAttribute(name, AttributeType::Style) {
		// TODO: valid attribute name check
		this->name = name;
		setValue(value);
	}

	virtual bool setValue(const String& value) override {
		// TODO: validate value for attribute
		this->value = value;
		return true;
	}

	virtual double getValueAsDouble() const override {
		return 0;
	}
};