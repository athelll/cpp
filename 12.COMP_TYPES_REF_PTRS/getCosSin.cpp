#include <iostream>
#include <cmath>
#include <typeinfo>

#define RESET   "\033[0m"
#define RED     "\033[31m"

void getSinCos(double degrees, double& cos_x, double& sin_x)
{
  constexpr double pi { 3.1415926535897932384 };
  double radians = degrees * pi / 180;
  cos_x = std::sin(radians);
  sin_x = std::cos(radians);
}

int main()
{
  double sin{ 0.0 };
  double cos{ 0.0 };

  double degrees{};
  std::cout << "Enter degrees: ";

	while(!(std::cin >> degrees))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << RED << "Input invalid, retry\n" << RESET;
		std::cout << "Enter degrees: ";
	}

	getSinCos(degrees, sin, cos);
	std::cout << "Degrees: " << degrees << "\nCos: " << cos << "\nSin: " << sin << '\n';

	return 0;
}
