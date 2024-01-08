#include <iostream>
#include <vector>

template <typename T>
bool isValueInArray(std::vector<T>& array , const T& value)
{
	for (const auto& element : array)
		if (element == value) return true;
	return false;
}

int main()
{
	using namespace std::literals;
	std::vector names { "Alex"sv, "Betty"sv, "Caroline"sv, "Dave"sv, "Emily"sv, "Fred"sv, "Greg"sv, "Holly"sv };
	std::string name {};

	std::cout << "input name to search: "; std::cin >> name;
	if (isValueInArray(names, static_cast<std::string_view>(name)))
		std::cout << name << " was found.\n";
	else
		std::cout << name << " was not found.\n";
}
