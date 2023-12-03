#include <iostream>

int& max(int& x, int& y)
{
  return (x > y ? x : y);
}

int main()
{
  int a{ 2 };
  int b{ 5 };

  max(a, b) = 10;
  std::cout << a << ' ' << b << '\n';
  return 0;
}
