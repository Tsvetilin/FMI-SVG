#pragma once
#include "App.hpp"
#include "SVGCollection.hpp"

class SVGSystem : public App<SVGCollection> {
	SVGCollection* collection;

	void printManual(std::ostream& outputStream);

public:
	SVGSystem();
	virtual void Run(SVGCollection& object, std::ostream& outputStream, std::istream& inputSteam) override;
};


void SVGSystem::printManual(std::ostream& outputStream) {

}

SVGSystem::SVGSystem() :collection(nullptr) {}

void SVGSystem::Run(SVGCollection& object, std::ostream& outputStream, std::istream& inputSteam) {
	collection = &object;

	printManual(outputStream);

	String input;
	String cmd;
	String path;
	while (true) {
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
		else if (cmd == "craete") {
			input = std::move(skipCmd("input"));
			String shape = matchCmd(input);

			if (shape == "rectangle") {
				input = std::move(skipCmd("input"));
				double x = parseToDouble(matchCmd(input));

				input = std::move(skipCmd("input"));
				double y = parseToDouble(matchCmd(input));

				input = std::move(skipCmd("input"));
				double width = parseToDouble(matchCmd(input));

				input = std::move(skipCmd("input"));
				double height = parseToDouble(matchCmd(input));

				input = std::move(skipCmd("input"));

				if (!collection->createRectangle(x, y, width, height, input)) {
					outputStream << "Error creating rectangle! Invalid arguments or permissions denied!" << std::endl;
					return;
				}
			}
			else if (shape == "line") {
				input = std::move(skipCmd("input"));
				double x1 = parseToDouble(matchCmd(input));

				input = std::move(skipCmd("input"));
				double y1 = parseToDouble(matchCmd(input));

				input = std::move(skipCmd("input"));
				double x2 = parseToDouble(matchCmd(input));

				input = std::move(skipCmd("input"));
				double y2 = parseToDouble(matchCmd(input));

				input = std::move(skipCmd("input"));

				if (!collection->createLine(x1, y1, x2, y2, input)) {
					outputStream << "Error creating rectangle! Invalid arguments or permissions denied!" << std::endl;
					return;
				}
			}
			else if (shape == "circle") {
				input = std::move(skipCmd("input"));
				double x = parseToDouble(matchCmd(input));

				input = std::move(skipCmd("input"));
				double y = parseToDouble(matchCmd(input));

				input = std::move(skipCmd("input"));
				double r = parseToDouble(matchCmd(input));

				input = std::move(skipCmd("input"));

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
		else if (cmd == "within") {
			input = std::move(skipCmd("input"));
			String shape = matchCmd(input);

			if (shape == "rectangle") {
				input = std::move(skipCmd("input"));
				double x = parseToDouble(matchCmd(input));

				input = std::move(skipCmd("input"));
				double y = parseToDouble(matchCmd(input));

				input = std::move(skipCmd("input"));
				double width = parseToDouble(matchCmd(input));

				input = std::move(skipCmd("input"));
				double height = parseToDouble(matchCmd(input));

				if (!collection->printWithInRectangle(outputStream, x, y, width, height)) {
					outputStream << "Invalid arguments or permissions denied!" << std::endl;
					return;
				}
			}
			else if (shape == "circle") {
				input = std::move(skipCmd("input"));
				double x = parseToDouble(matchCmd(input));

				input = std::move(skipCmd("input"));
				double y = parseToDouble(matchCmd(input));

				input = std::move(skipCmd("input"));
				double r = parseToDouble(matchCmd(input));

				if (!collection->printWithInCircle(outputStream, x, y, r)) {
					outputStream << "Invalid arguments or permissions denied!" << std::endl;
					return;
				}
			}
		}
		else if (cmd == "pointin") {
			input = std::move(skipCmd("input"));
			double x = parseToDouble(matchCmd(input));

			input = std::move(skipCmd("input"));
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

		}
		else if (cmd == "save") {
			if (collection->saveDocument(path)) {
				outputStream << "Successfully saved file!" << std::endl;
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
	}

	collection = nullptr;
}