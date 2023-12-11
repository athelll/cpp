#include <iostream>

struct Employee
{
  int id{};
  int age{};
  double wage{};
};

std::ostream& operator<<(std::ostream& out, const Employee& x)
{ return out << "id:   " << x.id << '\n' << "age:  " << x.age << '\n' << "wage: " << x.wage << '\n'; }

void raise_employee(Employee& x)
{ x.wage += 10'000.0; }

int main()
{
  Employee frank { 0, 21, 0.0 };

  std::cout << frank;
  std::cout << '\n' << ( raise_employee(frank), frank );
}
