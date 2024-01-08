#include <iostream>
#include <vector>
//#include <ranges>   // c++20
#include <string_view>

using string_view = std::string_view;

std::vector<string_view> reverseSV (std::vector<string_view>& array)
{
	std::vector<string_view> reversed{};
	using Index = std::ptrdiff_t;

	for (Index index {static_cast<Index>(array.size())}; index >=0; --index)
		reversed.push_back(array[static_cast<std::size_t>(index)]);
	return reversed;
}

int main()
{
    using namespace std::literals;
    std::vector words{ "Alex"sv, "Bobby"sv, "Chad"sv, "Dave"sv };

    for (const auto& word : reverseSV(words))
        std::cout << word << ' ' ;
		std::cout << '\n';
}
