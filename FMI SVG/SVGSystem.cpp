#include "SVGSystem.hpp"

const String rectangleDisplayName("rectangle");
const String circleDisplayName("circle");
const String lineDisplayName("line");

const String verticalAttributeName("vertical");
const String horizontalAttributeName("horizontal");

void SVGSystem::printManual(std::ostream& outputStream)  const {
	outputStream << "Available commands: " << std::endl <<
		"open <file name>" << std::endl <<
		"craete <shape type: rectangle / line / circle> <shape attributes>" << std::endl <<
		"erase <shape id>" << std::endl <<
		"print" << std::endl <<
		"within <rectangle / circle> <shape attributes>" << std::endl <<
		"pointin <x> <y> <shape id>" << std::endl <<
		"translate horizontal=\"<x>\" vertical=\"<y>\"" << std::endl <<
		"areas" << std::endl <<
		"perimeters" << std::endl <<
		"save" << std::endl <<
		"exit" << std::endl;
}

void SVGSystem::createShape(String& input, std::ostream& outputStream, std::istream& inputSteam) {
	input = std::move(skipCmd(input));
	String shape = matchCmd(input);

	if (shape == rectangleDisplayName) {
		input = std::move(skipCmd(input));
		double x = parseToDouble(matchCmd(input));

		input = std::move(skipCmd(input));
		double y = parseToDouble(matchCmd(input));

		input = std::move(skipCmd(input));
		double width = parseToDouble(matchCmd(input));

		input = std::move(skipCmd(input));
		double height = parseToDouble(matchCmd(input));

		input = std::move(skipCmd(input));

		if (!collection->createRectangle(x, y, width, height, input)) {
			outputStream << "Error creating rectangle! Invalid arguments or permissions denied!" << std::endl;
			return;
		}
	}
	else if (shape == lineDisplayName) {
		input = std::move(skipCmd(input));
		double x1 = parseToDouble(matchCmd(input));

		input = std::move(skipCmd(input));
		double y1 = parseToDouble(matchCmd(input));

		input = std::move(skipCmd(input));
		double x2 = parseToDouble(matchCmd(input));

		input = std::move(skipCmd(input));
		double y2 = parseToDouble(matchCmd(input));

		input = std::move(skipCmd(input));

		if (!collection->createLine(x1, y1, x2, y2, input)) {
			outputStream << "Error creating rectangle! Invalid arguments or permissions denied!" << std::endl;
			return;
		}
	}
	else if (shape == circleDisplayName) {
		input = std::move(skipCmd(input));
		double x = parseToDouble(matchCmd(input));

		input = std::move(skipCmd(input));
		double y = parseToDouble(matchCmd(input));

		input = std::move(skipCmd(input));
		double r = parseToDouble(matchCmd(input));

		input = std::move(skipCmd(input));

		if (!collection->createCircle(x, y, r, input)) {
			outputStream << "Error creating rectangle! Invalid arguments or permissions denied!" << std::endl;
			return;
		}
	}
	else {
		outputStream << "Shape not supported!" << std::endl;
		return;
	}

	outputStream << "Shape created successfully!" << std::endl;
}
void SVGSystem::translate(String& input, std::ostream& outputStream, std::istream& inputSteam) {
	input = std::move(skipCmd(input));

	double x = 0, y = 0;

	String type = getToEqualSign(input);
	double temp = parseToDouble(getQuotes(input));
	if (type == verticalAttributeName) {
		y = temp;
	}
	else if (type == horizontalAttributeName) {
		x = temp;
	}
	input = std::move(skipCmd(input));

	type = getToEqualSign(input);
	temp = parseToDouble(getQuotes(input));
	if (type == verticalAttributeName) {
		y = temp;
	}
	else if (type == horizontalAttributeName) {
		x = temp;
	}

	input = std::move(skipCmd(input));
	size_t index = parseToUInt(input);

	if (index == 0) {
		if (!collection->translateAll(x, y)) {
			outputStream << "Error translating all figures!" << std::endl;
		}
		else {
			outputStream << "All figures translated!" << std::endl;
		}
	}
	else {
		if (!collection->translateSingle(x, y, index - 1)) {
			outputStream << "Error translating figure! Invalid index!" << std::endl;
		}
		else {
			outputStream << "Figure translated successfully!" << std::endl;
		}
	}
}

void SVGSystem::within(String& input, std::ostream& outputStream, std::istream& inputSteam) const {
	input = std::move(skipCmd(input));
	String shape = matchCmd(input);

	if (shape == rectangleDisplayName) {
		input = std::move(skipCmd(input));
		double x = parseToDouble(matchCmd(input));

		input = std::move(skipCmd(input));
		double y = parseToDouble(matchCmd(input));

		input = std::move(skipCmd(input));
		double width = parseToDouble(matchCmd(input));

		input = std::move(skipCmd(input));
		double height = parseToDouble(matchCmd(input));

		if (!collection->printWithInRectangle(outputStream, x, y, width, height)) {
			outputStream << "Invalid arguments or permissions denied!" << std::endl;
			return;
		}
	}
	else if (shape == circleDisplayName) {
		input = std::move(skipCmd(input));
		double x = parseToDouble(matchCmd(input));

		input = std::move(skipCmd(input));
		double y = parseToDouble(matchCmd(input));

		input = std::move(skipCmd(input));
		double r = parseToDouble(matchCmd(input));

		if (!collection->printWithInCircle(outputStream, x, y, r)) {
			outputStream << "Invalid arguments or permissions denied!" << std::endl;
			return;
		}
	}
}

SVGSystem::SVGSystem() :collection(nullptr) {}

void SVGSystem::Run(SVGCollection& object, std::ostream& outputStream, std::istream& inputSteam) {
	collection = &object;

	printManual(outputStream);

	String input;
	String cmd;
	String path;
	while (true) {
		outputStream << "> ";
		input = std::move(getline(inputSteam));
		cmd = std::move(matchCmd(input));

		if (cmd == "open") {
			path = std::move(skipCmd(input));
			if (collection->loadDocument(path)) {
				outputStream << "Successfully loaded file!" << std::endl;
			}
			else {
				outputStream << "Error loading file! Either missing or invalid svg file!" << std::endl;
			}
		}
		else if (cmd == "print") {
			collection->print(outputStream);
		}
		else if (cmd == "create") {
			createShape(input, outputStream, inputSteam);
		}
		else if (cmd == "within") {
			within(input, outputStream, inputSteam);
		}
		else if (cmd == "pointin") {
			input = std::move(skipCmd(input));
			double x = parseToDouble(matchCmd(input));

			input = std::move(skipCmd(input));
			double y = parseToDouble(matchCmd(input));

			collection->printPointIn(outputStream, x, y);
		}
		else if (cmd == "erase") {
			size_t ind = parseToUInt(skipCmd(input));
			if (ind != 0 && collection->erase(ind - 1)) {
				outputStream << "Successfully erased figure!" << std::endl;
			}
			else {
				outputStream << "No figure with the index specified!" << std::endl;
			}
		}
		else if (cmd == "translate") {
			translate(input, outputStream, inputSteam);

		}
		else if (cmd == "save") {
			if (collection->saveDocument(path)) {
				outputStream << "Successfully saved shanges to " << path << "!" << std::endl;
			}
			else {
				outputStream << "Error saving file! Permissions denied!" << std::endl;
			}
		}
		else if (cmd == "exit") {
			return;
		}
		else if (cmd == "areas") {
			collection->printAreas(outputStream);
		}
		else if (cmd == "perimeters") {
			collection->printPerimeters(outputStream);
		}
		else {
			outputStream << "Invalid cmd!" << std::endl;
		}
	}

	collection = nullptr;
}