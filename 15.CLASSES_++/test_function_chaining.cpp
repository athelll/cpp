#include <iostream>

class MathInt
{
private:
  int m_value {};

public:
  MathInt& add(int value) { m_value += value; return *this; }
  MathInt& sub(int value) { m_value -= value; return *this; }
  MathInt& mul(int value) { m_value *= value; return *this; }

  int getValue() { return m_value; }
};

int main()
{
  MathInt x {};
  x.add(2).sub(1).mul(3).sub(2);
  std::cout << x.getValue() << '\n';
}

