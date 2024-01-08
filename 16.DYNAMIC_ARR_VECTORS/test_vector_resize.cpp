#include <vector>
#include <iostream>

int main()
{
    std::vector vec { 1, 2, 4 };
    std::cout << "the length is: " << vec.size() << '\n';

    vec.resize(5);
    std::cout << "the length is: " << vec.size() << '\n';

    for (auto i : vec)
        std::cout << i << ' ';
    std::cout << '\n';
}
