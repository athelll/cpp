#include <iostream>

int main()
{
	int outer{ 1 };

	while (outer <= 5)
	{
		int inner{ 5 - outer };
		while(inner > 0)
			std::cout << (--inner, ' ');

		int number_to_print{ outer };
		while(number_to_print > 0)
			std::cout << number_to_print-- << ' ';

		std::cout << '\n';
		++outer;
	}
}
