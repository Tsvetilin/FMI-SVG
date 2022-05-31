#pragma once
#include "SVGAttribute.hpp"
#include "Common.hpp"

class SVGGeometryAttribute : public SVGAttribute {
	double parsedField;

public:
	SVGGeometryAttribute(const String& name, const String& value);
	virtual bool setValue(double v) override;
	virtual bool setValue(const String& v) override;
	virtual double getValueAsDouble() const override;
	virtual void writeAttribute(std::ostream& stream) const;
};