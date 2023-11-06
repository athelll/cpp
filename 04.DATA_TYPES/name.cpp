#include <iostream>
#include <string>
#include <string_view>


std::string get_name(int count)
{
	std::string name {};
	std::cout << "Enter the name of person #" << count << ": ";
	std::getline(std::cin >> std::ws, name);
	return name;
}

int get_age(std::string_view name)
{
	int age{};
	std::cout << "Enter the age of " << name << ": ";
	std::cin >> age;
	return age;
}

inline void print_result(std::string_view old, std::string_view young, int yage, int oage)
{
	std::cout << old << " (age " << oage << ')' << " is older than " << young << " (age " << yage << ")." << '\n';
}

int main()
{
	const std::string name1{ get_name(1) };
	const int age1 { get_age(name1) };

	const std::string name2{ get_name(2) };
	const int age2{ get_age(name2) };

	if (age1 > age2)
		print_result(name1, name2, age2, age1);
	else
		print_result(name2, name1, age1, age2);
}
