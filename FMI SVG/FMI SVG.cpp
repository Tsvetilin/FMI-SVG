#include <iostream>
#include "Circle.hpp"
#include "SVGRectangle.hpp"

int main()
{
    SVGElement* shape1 = new SVGRectangle(SVGElement(""));
    Shape* shape2 = new Circle(SVGElement(""));
    

    SVGShape* asd1 = dynamic_cast<SVGShape*>(shape1);
    SVGShape* asd2 = dynamic_cast<SVGShape*>(shape2);

    std::cout << asd1 << std::endl;
    std::cout << asd2 << std::endl;

    SVGElement* s1 = new SVGRectangle(SVGElement(""));
    Shape* s2 = new SVGRectangle(SVGElement(""));
    SVGShape* s3 = new SVGRectangle(SVGElement(""));
    std::cout << s1 << std::endl;
    std::cout << s2 << std::endl;
    std::cout << s3 << std::endl;
    s3->translate(1, 1);


    std::cout << "Hello World!\n";
}