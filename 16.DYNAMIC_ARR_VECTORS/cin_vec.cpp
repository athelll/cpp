#include <iostream>
#include <vector>

int main()
{
	std::vector<int> vec (3);

	std::cout << "please input three numbers: ";
	std::cin >> vec[0] >> vec[1] >> vec[2];
	std::cout << "the sum is " << vec[0] + vec[1] + vec[2] << '\n';
	std::cout << "the mutiplication is " << vec[0] * vec[1] * vec[2] << '\n';
}
