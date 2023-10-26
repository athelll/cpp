#include <cstdint>
#include <iostream>

int main()
{
	std::cout << "Enter a number between 10 and 127: ";
	std::int8_t number{};
	std::cin >> number;

	std::cout << "you inputed " << static_cast<int> (number) << '\n';
	return 0;
}
