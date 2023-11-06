#include <iostream>
#include <iomanip>

int main()
{
	double one_d { 100.0 - 99.99 };    // 0.01
	double two_d { 10.0 - 9.99 };      // 0.01

	bool is_equal = (one_d == two_d) ? true : false;
	std::cout << std::boolalpha << std::setprecision(17);
	std::cout << one_d << " is " << is_equal <<"ly equal to " << two_d << '\n';
}
