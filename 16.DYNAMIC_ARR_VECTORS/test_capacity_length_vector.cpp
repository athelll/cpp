#include <vector>
#include <iostream>

template <typename T>
constexpr void operator+(const std::vector<T>& array) noexcept
{
	for (auto i : array)
		std::cout << i << ' ';
	std::cout << '\n';
	std::cout << "Capacity: " << array.capacity() << '\n' << "Length: " << array.size() << "\n\n";
}

int main()
{
	std::vector nums { 1, 3, 5 };
	+nums;

	nums.resize(6); +nums;
	nums.resize(2); +nums;
	nums.resize(3); +nums;
	nums.resize(9); +nums;
	nums.resize(3); +nums;
}
