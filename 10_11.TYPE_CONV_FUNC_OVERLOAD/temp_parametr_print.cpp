#include <iostream>

template <int N>
void print()
{
  std::cout << N << '\n';
}

int main()
{
  print<5>();               // this would print 5 on a newline.
}
