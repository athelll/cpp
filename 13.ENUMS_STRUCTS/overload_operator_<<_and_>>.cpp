#include <iostream>
#include "ioswitch.h"

#ifdef OUT_STREAM
enum Pain
{
	sharp,
	nonending,
	infinite,
};

std::ostream& operator<<(std::ostream& out, Pain x)
{
	switch( x )
	{
		case sharp:      return out << "Sharp";
		case nonending:  return out << "Non Ending";
		case infinite:   return out << "Infinite";
		default:         return out << "real";
	}
}

int main()
{
	Pain selected{ sharp };
	std::cout << "your pain is " << selected << '\n';
	return 0;
}
#endif

#ifdef IN_STREAM
enum Pet
{
	cat,
	dog,
	pig,
	whale,
};

std::istream& operator>> (std::istream& in, Pet& pet)
{
	int input{};
	in >> input; // input an integer

	pet = static_cast<Pet>(input);
	return in;
}

int main()
{
	std::cout << "Enter a pet (0=cat, 1=dog, 2=pig, 3=whale): ";

	Pet pet{};
	std::cin >> pet;
	std::cout << pet << '\n';

	return 0;
}
#endif
