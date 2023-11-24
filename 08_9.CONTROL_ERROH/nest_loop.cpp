#include <iostream>

int main()
{
	int x{ 5 };

	while (x != 0)
	{
		int y{ x };
		while (y != 0)
			std::cout << y-- << " ";

		std::cout << '\n';
		--x;
	}
}
