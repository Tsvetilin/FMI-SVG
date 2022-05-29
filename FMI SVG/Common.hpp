#pragma once
#include "String.hpp"

const char TO_UPPER_TRANSFORM = -'a' + 'A';
const char TO_LOWER_TRANSFORM = -'A' + 'a';

const size_t DOUBLE_STRING_PRECISION = 1000;

bool isLowercaseLetter(char c);
bool isUppercaseLetter(char c);
bool isLetter(char c);
bool isDigit(char c);
bool isAlphaNumericSymbol(char c);

size_t parseToUInt(const String& input);
double parseToDouble(const String& str);
String doubleToString(double d);

int charToInt(char c);
char digitToChar(size_t c);

size_t getNumberDigitsCount(size_t num);

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

