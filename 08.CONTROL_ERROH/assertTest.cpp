#include <cassert>
#include <cmath>
#include <iostream>

double groundHitTime(double initialHeight, double gravity)
{
  assert( (gravity > 0.0) && "Gravity can't be negative: unethical." );

  if (gravity == 0.0)
    return 0.0;
  return std::sqrt((2.0 * initialHeight) / gravity);
}

int main()
{
  double height{ 7.90e3 };

  std::cout << "ball is at height: " << height << " touching ground in " << groundHitTime(height, -9.8) << "secs\n";
}
