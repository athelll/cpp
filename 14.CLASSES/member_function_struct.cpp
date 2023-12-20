#include <iostream>

struct Date
{
  int day{};
  int month{};
  int year{};

  void print()
  {
    std::cout << day << '/' << month << '/' << year << '\n';
  }
};

int main()
{
  Date today { 12, 12, 2023 };
  ++today.day;
  today.print();

  return 0;
}
