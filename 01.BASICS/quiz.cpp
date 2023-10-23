#include <iostream>
#include <limits>

int main()
{
	int x { 5 };

	while (1)
	{
		std::cout << x << " This is the number before\n";
		std::cout << "Enter a number: "; // ask user for a number
		std::cin >> x; // get number from keyboard and store it in variable x
		std::cout << "You entered " << x << '\n';

		//clearing buffer
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard the input buffer
	}
	return 0;
}
