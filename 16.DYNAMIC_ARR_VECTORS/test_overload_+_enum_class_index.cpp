#include <vector>
#include <iostream>

enum class StudentNames // now an enum class
{
    kenny, // 0
    kyle, // 1
    stan, // 2
    butters, // 3
    cartman, // 4
    max_students // 5
};

constexpr auto operator+(StudentNames a) noexcept {
    return static_cast<std::underlying_type_t<StudentNames>>(a);
}

int main()
{
    std::vector<int> students (+StudentNames::max_students);

    students[static_cast<size_t>(StudentNames::stan)] = 33;
    std::cout << +StudentNames::max_students << '\n';
}
