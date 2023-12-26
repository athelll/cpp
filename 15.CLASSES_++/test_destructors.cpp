#include <iostream>

class Simple
{
private:
  int m_id {};

public:
  Simple(int id) : m_id { id } { std::cout << "constructed id: " << m_id << '\n'; }      // constructor.
  ~Simple() { std::cout << "destroyed id: " << m_id << '\n'; }                           // destructor.
  int getID() const { return m_id; }
};

int main()
{
  Simple simple1(1);
  {
    Simple simple2(2);
  } // simple2 is destoryed here.

  return 0;
}
