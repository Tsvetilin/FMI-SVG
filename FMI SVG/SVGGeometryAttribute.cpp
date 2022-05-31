#include "SVGGeometryAttribute.hpp"

SVGGeometryAttribute::SVGGeometryAttribute(const String& name, const String& value) :SVGAttribute(name, AttributeType::Geometry) {
	this->name = name;
	setValue(value);
}

bool SVGGeometryAttribute::setValue(double v) {
	// TODO: proper measurement handle
	parsedField = v;
	value = doubleToString(v);
	return true;
}

bool SVGGeometryAttribute::setValue(const String& v) {
	// TODO: proper measurement handle
	parsedField = parseToDouble(v);
	value = v;
	return true;
}

double SVGGeometryAttribute::getValueAsDouble() const {
	return parsedField;
}

void SVGGeometryAttribute::writeAttribute(std::ostream& stream) const {
	stream << name << "=\"" << parsedField << "\"";
}