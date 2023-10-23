#include <cstddef>
#include <iostream>

int main()
{
	int size { sizeof(std::size_t) };
	std::cout << "This is a " << size * 8 << " bits machine\n";

	double scientific_notation { 3e7 };
	std::cout << scientific_notation << "\n";
}
