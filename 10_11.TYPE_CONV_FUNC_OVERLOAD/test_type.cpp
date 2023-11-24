#include <iostream>
#include <typeinfo> // for typeid()

int main()
{
	int i{ 2 };
	double d{ 3.5 };
	std::cout << typeid(i + d).name() << ' ' << i + d << '\n'; // show us the type of i + d

	return 0;
}
