#pragma once
#include "SVGAttribute.hpp"
#include "Common.hpp"

class SVGGeometryAttribute : public SVGAttribute {
	double parsedField;

public:
	SVGGeometryAttribute(const String& name, const String& value) :SVGAttribute(name, AttributeType::Geometry) {
		this->name = name;
		setValue(value);
	}

	virtual bool setValue(double v) override{
		// TODO: proper measurement handle
		parsedField = v;
		value = doubleToString(v);
		return true;
	}

	virtual bool setValue(const String& v) override {
		// TODO: proper measurement handle
		parsedField = parseToDouble(v);
		value = v;
		return true;
	}

	virtual double getValueAsDouble() const override {
		return parsedField;
	}

	virtual void writeAttribute(std::ostream& stream) const {
		stream << name << "=\"" << parsedField << "\"";
	}
};