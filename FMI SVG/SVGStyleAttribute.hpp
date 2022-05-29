#pragma once
#include "SVGAttribute.hpp"

class SVGStyleAttribute : public SVGAttribute {

public:
	SVGStyleAttribute(const String& name, const String& value) :SVGAttribute(name, AttributeType::Style) {
		this->name = name;
	}

	virtual bool setValue(const String& value) override {
		this->value = value;
		return true;
	}

	virtual double getValueAsDouble() const override {
		return 0;
	}
};