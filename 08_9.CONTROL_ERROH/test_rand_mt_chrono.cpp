#include <iostream>
#include <random>
#include <chrono>

int main()
{
  std::mt19937 mt{ static_cast<std::mt19937::result_type> (std::chrono::steady_clock::now().time_since_epoch().count()) };
  std::uniform_int_distribution die6{1, 6};

  for (int count{ 1 }; count <= 50; ++count)
  {
    std::cout << die6(mt) << '\t';

    if (count % 10 == 0)
      std::cout << '\n';
  }
  return 0;
}
