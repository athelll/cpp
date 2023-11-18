#include <iostream>
#include <limits>

inline void ignoreExtra()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

double getDouble()
{
  double x{};

  while(true)
  {
    std::cout << "Enter decimal number ";
    std::cin >> x;
    if (!std::cin)
    {
      std::cin.clear();
      ignoreExtra();
			std::cout << "only input numbers bitch\n";
    }
    else
    {
      ignoreExtra();
      return x;
    }
  }
}

int main()
{
	 double shit{ getDouble() };
	 std::cout << "you chose " << shit << '\n';
}
