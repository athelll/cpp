#include <bitset>
#include <iostream>

std::bitset<4> rotl(std::bitset<4> bits)
{
	const std::bitset<4> rotate{ bits | std::bitset<4> { 0b0111 } };

	bits <<= 1;

	if (rotate == std::bitset<4> { 0b1111 } )
		bits |= std::bitset<4> { 0b0001 };

	return bits;
}

int main()
{
	std::bitset<4> bits1{ 0b0001 };
	std::cout << rotl(bits1) << '\n';

	std::bitset<4> bits2{ 0b1001 };
	std::cout << rotl(bits2) << '\n';

	return 0;
}
