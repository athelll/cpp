#include <iostream>
#include <vector>
#include <limits>

int main()
{
    std::vector<int> stack {};

    while (true)
    {
        std::cout << "input a number (-1 to stop) ";
        int x {};
        std::cin >> x;

        if (!std::cin)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (x == -1)
						break;

        stack.emplace_back(x);

    }

    std::cout << "your list is: \n";
	
    for (const auto x : stack)
        std::cout << x << ' ';
		std::cout << '\n';
}
