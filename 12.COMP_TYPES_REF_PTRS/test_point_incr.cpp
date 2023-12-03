#include <iostream>

void someFcn(double* x)
{
  ++(*x);                   // this should increment the value passed by address in the callers scope
}

int main()
{
  double num{ 9.0 };
  someFcn(&num);
	std::cout << num << '\n';
}
