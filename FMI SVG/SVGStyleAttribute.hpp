#pragma once
#include "SVGAttribute.hpp"

class SVGStyleAttribute : public SVGAttribute {

public:
	SVGStyleAttribute(const String& name, const String& value);
	virtual bool setValue(const String& value) override;
	virtual double getValueAsDouble() const override;
};