#include <cmath>
#include <iostream>

constexpr double maxVHeight(double initV, double gravity)
{
  return std::pow(initV, 2) / (gravity * 2);
}

int main()
{
  constexpr int initV { 15 };
  constexpr double maxHeightMoon { maxVHeight(initV, 1.625) };
  constexpr double maxHeightEarth { maxVHeight(initV, 9.8) };

  std::cout << "The maximum height of a ball thrown in the moon at an initial velocity of 15m/s is " << maxHeightMoon << "m \n";
  std::cout << "While that of the earth is " << maxHeightEarth << "m \n";
}
