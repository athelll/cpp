#include <iostream>
#include <iomanip>

int main()
{
	float f { 1.23456789 };
	std::cout << std::setprecision(9);
	std::cout << f << '\n';
	return 0;
}
