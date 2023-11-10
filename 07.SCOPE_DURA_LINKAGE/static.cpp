#include <iostream>

void incrementAndPrint()
{
  static int s_value{ 1 };  // converted from automatic duration to static.
  ++s_value;
  std::cout << s_value << '\n';
} // unlike other non-static local variables s_value is not destroyed here, but becomes inaccessible as it goes out of scope.

int main()
{
  incrementAndPrint();
  incrementAndPrint();
  incrementAndPrint();
  incrementAndPrint();
}
