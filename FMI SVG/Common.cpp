#include "Common.hpp"

bool isLowercaseLetter(char c) {
	return c >= 'a' && c <= 'z';
}

bool isUppercaseLetter(char c) {
	return c >= 'A' && c <= 'Z';
}

bool isLetter(char c) {
	return isLowercaseLetter(c) || isUppercaseLetter(c);
}

bool isDigit(char c) {
	return c >= '0' && c <= '9';
}

bool isAlphaNumericSymbol(char c) {
	return isLetter(c) || isDigit(c);
}

int charToInt(char c) {
	return (c - '0');
}

char digitToChar(size_t c) {
	return (char)('0' + c);
}

size_t getNumberDigitsCount(size_t num) {
	if (num == 0) {
		return 1;
	}

	size_t digits = 0;
	while (num != 0) {
		++digits;
		num /= 10;
	}

	return digits;
}

size_t parseToUInt(const String& input) {
	size_t index = 0;
	size_t result = 0;

	while (input[index] == ' ') {
		if (input[index] == '\0') {
			return 0;
		}
		++index;
	}

	while (isDigit(input[index])) {
		result *= 10;
		result += input[index] - '0';
		++index;
	}

	if (input[index] != ' ' && input[index] != '\0') {
		return 0;
	}

	return result;
}

double parseToDouble(const String& str) {
	int dotInd = str.indexOf('.');
	if (dotInd == -1) {
		return parseToUInt(str);
	}

	size_t intPart = parseToUInt(str.substr(0, dotInd));
	size_t floatingPart = parseToUInt(str.substr(dotInd + 1, str.getLength() - dotInd - 1));
	size_t floatingLength = getNumberDigitsCount(floatingPart);

	return (double)floatingPart / pow(10, floatingLength) + intPart;
}

String doubleToString(double d) {
	if (d <= 0) {
		return "0";
	}

	size_t intPart = (size_t)d;
	d -= intPart;
	d *= DOUBLE_STRING_PRECISION;
	size_t doublePart = (size_t)d;

	return String(intPart).concat(".").concat(String(doublePart));
}
