#include <iostream>

unsigned int LCG16()
{
  static int s_state{ 5323 };

  // generate the next state by introducing overflows in the computaions to make it seem more random
  s_state = 8253729 * s_state + 2396403;
  return s_state % 32768;                   // added randomness.
}

int main()
{
  for (int count{ 1 }; count <= 100; ++count)
  {
    std::cout << LCG16() << '\t';

    if (count % 10)
      std::cout << '\n';
  }
  return 0;
}
