Felix Ikechukwu O. Dec 23, 2023
More on Classes


## The hidden “this” pointer and member function chaining

### The hidden this pointer

inside every member function, the keyword is a const pointer that holds the address of the current implicit object.
we dont mention it implciitlt but to prove its there we can prove it with:
```cpp

class Simple
{
private:
  int m_id {};
public:
  Simple(int id)
  : id { m_num }
  {}

  int getID() { return m_id; }
  void setID(int id) { m_id = id; }
  void print() { std::cout << this->m_id; }
};

int main()
{
  Simple simple{ 1 };
  simple.setID( 2 );
  simple.print();                                             // this prints 2.
}
```

note:
```cpp
  void print() { std::cout << m_id; };                          // implicit use of this
  void print() { std::cout << this->m_id; };                    // explicit use of this.
```

### How is this set?

lets examine the function call:
```cpp
simple.setId(2);
//although it looks like it takes in one argument it actually takes in 2, when compiled the compiler re-writes it as:
Simple::setId($simple, 2);
// note that this is now a standard function call, with the implicit object address passed in also as an argument, but this is just half of the answer bacuase:
// since the function call is also modified that means the calling function has to be also modified to accept the function call.
// so the original member function goes from:
void setID(int id) { m_id = id; }
// to:
void setID(Simple* const this, int id) { this->m_id = id; }
```

the good news of this is that this process happens automatically by the compiler so we dont need to explicitely state this.
all `non-static` member functions have a `this` const pointer that points to its implicit object.

### `this` always points to the object being operated on

yup and becasue this is a member function parameter not a mameber, it has no large impact on your object memory-wise.

### Explicitly referencing this

sometimes developers use the `this->` syntax to disambigaute referencing member variables that share the same identifier with some other non-member variable.
{{{cpp
struct Something
{
  int data {};
  void setData(int data)
  {
    this ->data = data;             // fixes disambiguity.
  }
};
}}}

### Returning `*this`

sometimes it can be helpful to have member function return the `this` pointer (address of the implicit object): this allows mwmber function to be "chained" together,
so several member functions can be called on the same object in single expression.

a common example of this is usimg `std::cout`:
```cpp
std::cout << "Hello " << name;
```
what the compiler does is that it reformates the code as so:
```cpp
(std::cout << "Hello ") << name;
```
what happens above is that the parathesized substatement is evaluated first the the `this` pointer pointing to the std::cout object is returned by the `<<`operator
and the next input arguments is taken and the same happens. this way we only need to specify `std::cout` once, the `<<`operator does the chaining for us.
each call to `<<`operator retuns the `std::cout` object for the next input to be fed into it and be printed.

we can achieve function chaining in classe by returning the `*this` pointer, example:
```cpp
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
  MathInt new {};
  new.add(2).sub(1).mul(3);
  std::cout << new << '\n';
}
```

### Resetting a class back to default state

this is done bu assigning the `this` pointer of an object to an empty list initiizer. this forces the this pointer to point ti newly created empty defaultly initiazlized or non-initialized object:
```cpp
void reset()
{
  *this = {};
}
```


## Classes and header files

due to how exponentially large classes declaration and implementaions can get: it can get quite compliciated managing classes. to fix this issue
C++ allows us to seperate the `declaration` and `implementation` of classes by defining member functions outside of the class definitaion and placing the prototype designs in the class:
```cpp
#include <iostream>

class Date
{
private:
  int m_year {};
  int m_month {};
  int m_day {};

public:
  Date(int Year, int month, int day);
  void print() const;

  int getyear() const { return m_year; }
  int getmonth() const { return m_year; }
  int getday() const { return m_year; }
};

Date::Date(int year, int month, int day)
  : m_year { year }
  , m_month { month }
  , m_day { day }
{}

Date::print() const
{
  std::cout << "Date(" << m_year << ", " << m_month << ", " << m_day << ")\n";
}

int main()
{
  const Date today { 2023, 12, 23 };
  today.print()
}
```

things to note:
1. member functions with trivial implementation, can be defined inside a class
2. member functions with complex or multi-line implementaion should be defiend out the class preferrably in a seperate source file

### Putting class definitions in a header file

read here

### Doesn’t defining a class in a header file violate the one-definition rule if the header is #included more than once?

no it doesnt it: Types are expempted from the ODR(ule). just use header guards.
functiond defiend inside a class declaration are implicitly inline which allows them tonbe included in multiple files without violating the ODR.

functions defined outside a class declaration are not implicitly inline. they can be made inline using the `inline` keyword.

### Libraries

read this again


## Nested types (member types)


