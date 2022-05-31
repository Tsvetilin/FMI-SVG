#pragma once
#include "App.hpp"
#include "SVGCollection.hpp"

class SVGSystem : public App<SVGCollection> {
	SVGCollection* collection;

	void printManual(std::ostream& outputStream) const;
	void createShape(String& input, std::ostream& outputStream, std::istream& inputSteam);
	void translate(String& input, std::ostream& outputStream, std::istream& inputSteam);
	void within(String& input, std::ostream& outputStream, std::istream& inputSteam)const;

public:
	SVGSystem();
	virtual void Run(SVGCollection& object, std::ostream& outputStream, std::istream& inputSteam) override;
};
