#pragma once
#include <iostream>

template<class T>
class App {
public:
	virtual void Run(T& object, std::ostream& outputStream, std::istream& inputSteam) = 0;
};