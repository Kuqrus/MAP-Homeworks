#include <iostream>

#include "Shapes.h"

int main()
{	
	std::vector<int> x{ 10,40 };
	std::vector<int> y{ 20,50 };
	std::vector<int> z{ 30,15 };

	Square s(x, y);
	std::cout << s.GetSquare() << std::endl;
	s.Scale(2);
	std::cout << s.GetSquare() << std::endl;
	s.ScaleX(2);
	s.ScaleY(2);
	std::cout << s.GetSquare() << std::endl;

	Circle c(5, 2, 2.2);
	std::cout << c.GetSquare() << std::endl;

}