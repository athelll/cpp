#include "random.h"

int main()
{
  for(int count{ 1 }; count <= 40; ++count)
  {
    std::cout << Random::get(1, 20) << '\t';

    if (count % 10 == 0)
      std::cout << '\n';
  }
	return 0;
}
