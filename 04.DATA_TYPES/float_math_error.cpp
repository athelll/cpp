#include <iomanip>
#include <iostream>

int main()
{
	std::cout << std::setprecision(17);
	double x { 1.0 };
	std::cout << x << '\n';
	double y { 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 };
	std::cout << y << '\n';
}
