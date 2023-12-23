#include <iostream>
#include <algorithm>

class Foo
{
private:
  int m_one {};
  int m_two {};
public:
  Foo(int x, int y) : m_two { std::max(x, y) }, m_one { m_two }
  {
  }
  void print() const
  {
    std::cout << "Foo(" << m_one << ", " << m_two << ")\n";
  }
};

int main()
{
  Foo foo { 5, 6 };
  foo.print();
}
