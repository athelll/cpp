#include <iostream>

void nullify(int*& refptr)
{
  refptr = nullptr;
}

int main()
{
  int x{ 5 };
  int* ptr{ &x };

  std::cout << "ptr is " << (ptr ? "not-null" : "null") << '\n';
  nullify(ptr);
  std::cout << "ptr is " << (ptr ? "not-null" : "null") << '\n';
}
