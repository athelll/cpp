#include <cstdint>
#include <iostream>

int main()
{
	[[maybe_unused]] constexpr std::uint8_t mask0{ 0b0000'0001 };  // represents bit 0
	[[maybe_unused]] constexpr std::uint8_t mask1{ 0b0000'0010 };  // represents bit 1
	[[maybe_unused]] constexpr std::uint8_t mask2{ 0b0000'0100 };  // represents bit 2
	[[maybe_unused]] constexpr std::uint8_t mask3{ 0b0000'1000 };  // represents bit 3
	[[maybe_unused]] constexpr std::uint8_t mask4{ 0b0001'0000 };  // represents bit 4
	[[maybe_unused]] constexpr std::uint8_t mask5{ 0b0010'0000 };  // represents bit 5
	[[maybe_unused]] constexpr std::uint8_t mask6{ 0b0100'0000 };  // represents bit 6
	[[maybe_unused]] constexpr std::uint8_t mask7{ 0b1000'0000 };  // represents bit 7

	std::uint8_t flags{ 0b0000'0101 };

	std::cout << "bit 2 is " << (static_cast<bool>(flags & mask2) ? "on" : "off") << '\n';
	flags &= ~mask2;      // turns off bit 2.
	std::cout << "bit 2 is " << (static_cast<bool>(flags & mask2) ? "on" : "off") << '\n';
}
