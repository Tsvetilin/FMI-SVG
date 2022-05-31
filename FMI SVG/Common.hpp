#pragma once
#include "String.hpp"
#include "List.hpp"

const String circleName("circle");
const String rectangleName("rect");
const String lineName("line");

const String xName("x");
const String yName("y");
const String x1Name("x1");
const String y1Name("x1");
const String x2Name("x2");
const String y2Name("y2");
const String cxName("cx");
const String cyName("cy");
const String rName("r");
const String widthName("width");
const String heightName("height");

const String geometryAttributes[]{ xName,yName,x1Name,y1Name,x2Name,y2Name,cxName,cyName, rName, widthName, heightName };
const List<String> geometryAttributesList(geometryAttributes, sizeof(geometryAttributes) / sizeof(geometryAttributes[0]));


const char TO_UPPER_TRANSFORM = -'a' + 'A';
const char TO_LOWER_TRANSFORM = -'A' + 'a';

const size_t DOUBLE_STRING_PRECISION = 1000;

bool isLowercaseLetter(char c);
bool isUppercaseLetter(char c);
bool isLetter(char c);
bool isDigit(char c);
bool isAlphaNumericSymbol(char c);

size_t parseToUInt(const String& input);
double parseToDouble(String str);
String doubleToString(double d);

int charToInt(char c);
char digitToChar(size_t c);

size_t getNumberDigitsCount(size_t num);

String matchCmd(const String& input);
String skipCmd(const String& input);
String getToEqualSign(const String& input);
String getQuotes(const String& input);
String getAfterQuotes(const String& input);
String getLastArgument(const String& input);

template<typename T>
void swap(T& first, T& second) {
	T temp = first;
	first = second;
	second = temp;
}

template<typename T>
T min(const T& first, const T& second) {
	return first < second ? first : second;
}

template<typename T>
T max(const T& first, const T& second) {
	return first > second ? first : second;
}

template<typename T>
void serializePrimitive(std::ostream& o, const T& data) {
	o.write((const char*)&data, sizeof(data));
}

template<typename T>
void deserializePrimitive(std::istream& i, const T& data) {
	i.read((char*)&data, sizeof(data));
}

