#include <iostream>
#include "SVGCollection.hpp"
#include "SVGSystem.hpp"

int main()
{
	SVGCollection collection;
	SVGSystem system;

	system.Run(collection, std::cout, std::cin);

	return 0;
}