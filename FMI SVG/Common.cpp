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


String matchCmd(const String& input) {
	size_t startIndex = 0;

	while (input[startIndex] == ' ') {
		++startIndex;
	}

	size_t wordLength = 0;
	while (input[startIndex + wordLength] != ' ' && input[startIndex + wordLength] != '\0') {
		++wordLength;
	}

	return std::move(input.substr(startIndex, wordLength));
}

String skipCmd(const String& input) {

	size_t startIndex = 0;
	size_t wordLength = 0;
	while (input[startIndex] == ' ') {
		if (input[startIndex] == '\0') {
			return String();
		}
		++startIndex;
	}

	while (input[startIndex + wordLength] != ' ' && input[startIndex + wordLength] != '\0') {
		++wordLength;
	}

	return input.substr(startIndex + wordLength + 1, input.getLength() - startIndex - wordLength - 1);
}

String getQuotes(const String& input) {

	size_t startIndex = 0;
	size_t wordLength = 0;

	while (input[startIndex] != '"') {
		if (input[startIndex] == '\0') {
			return String();
		}
		++startIndex;
	}

	++startIndex;

	while (input[startIndex + wordLength] != '"' && input[startIndex + wordLength] != '\0') {
		++wordLength;
	}

	return input.substr(startIndex, wordLength);
}

String getLastArgument(const String& input) {
	size_t index = input.getLength() - 1;

	while (input[index] == ' ' && index >= 0) {
		--index;
	}

	while (input[index] != ' ' && index >= 0) {
		--index;
	}

	return input.substr(index, input.getLength() - index);
}

String getAfterQuotes(const String& input) {
	size_t index = 0;
	size_t quotesCount = 0;

	while (index < input.getLength()) {

		if (input[index] == '"') {
			++quotesCount;
		}

		if (quotesCount == 2) {
			break;
		}

		++index;
	}

	if (quotesCount != 2) {
		return String();
	}

	return input.substr(index + 2, input.getLength() - index - 2);
}