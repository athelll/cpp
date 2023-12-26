Felix Ikechukwu O. Dec 23, 2023
More on Classes


The hidden “this” pointer and member function chaining
======================================================
The hidden this pointer
-----------------------
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

How is this set?
----------------
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

`this` always points to the object being operated on
--------------------------------------------------
yup and becasue this is a member function parameter not a mameber, it has no large impact on your object memory-wise.

Explicitly referencing this
---------------------------
sometimes developers use the `this->` syntax to disambigaute referencing member variables that share the same identifier with some other non-member variable.
```cpp
struct Something
{
  int data {};
  void setData(int data)
  {
    this ->data = data;             // fixes disambiguity.
  }
};
```

Returning `*this`
---------------
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

Resetting a class back to default state
---------------------------------------
this is done bu assigning the `this` pointer of an object to an empty list initiizer. this forces the this pointer to point ti newly created empty defaultly initiazlized or non-initialized object:
```cpp
void reset()
{
  *this = {};
}
```

------------------------------------------------------------------

Classes and header files
========================
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

Putting class definitions in a header file
------------------------------------------
read here

Doesn’t defining a class in a header file violate the one-definition rule if the header is #included more than once?
--------------------------------------------------------------------------------------------------------------------
no it doesnt it: Types are expempted from the ODR(ule). just use header guards.
functiond defiend inside a class declaration are implicitly inline which allows them tonbe included in multiple files without violating the ODR.

functions defined outside a class declaration are not implicitly inline. they can be made inline using the `inline` keyword.

Libraries
---------
read this again

----------------------------------------------------

Nested types (member types)
===========================

class tyoes can support another kind members: `nested types` also called `member types`. to create one simply declare athe nested type in the class
under the appropriate access specifier.
```cpp
#include <iostream>

class Fruit
{
public:
  enum Type
  {
    apple,
    cherry,
    banana,
  };

private:
  Type m_type {};
  int m_howManyEaten { 0 };

public:
  Fruit (Type type)
  : m_type { type }
  {}

  Type getType () { return m_type; }
  int get_how_many_eaten () { return m_howManyEaten; }
  bool isCherry () { return m_type == cherry; }
};

int main()
{
  Fruit apple { Fruit::apple };

  if (apple.getType == Fruit::apple)
    std::cout << "i am an apple\n";
  else
    std::cout << "im not an apple";

  return 0;
}
```

thins to note in the above code:
* the Nested tyoes declaration must be seen by the compiler before usage thats why its defined at the top of the class. (so it should usually be defined first in a class)
* nested tyoes follow normal access rules of classes thats why it was declared under the public accesser: to prevent being defaultly defined with the private accesser.
  cos its in a clss and thats what classes do.
* class types acts as scope region for nested types: like using a namespace.: so theres no need to declare them as `enum classes` (except your a masochist) they can be accessed now
  by non-members using the `Fruit::cherry` namespace syntax.

for nested enumerates types or generally nested class types the class they are defined in acts as a scope for them.

Nested typedefs and type aliases
--------------------------------
class types can also nest aliases and typdefs
```cpp
class Something
{
public:
  using intID = int;

private:
  intID m_id {};

public:
  Something (intID id) : m_id { id } {}
  intID getID() { return m_id; }
};

int main()
{
  Something light { 2 }
  Something::intID id { light.getID() };                    // we can aceess aliases and typedef from non-member regions using the scope selector operator
}
```

Nested classes and access to outer class members
------------------------------------------------
nestes classes in classes are possible but not commonly implemented, a fact about them is that the inner class cannot access the `this` pointer of the outer class
that makes sense of you think about it tho, so inner classes cannot directly access the members of the outer class: that is becuase the inner class can be instantiated
independently of the outer class and in such class there woould be no outer class member. what a conundrum, enigma? a mind boggling piece of rationale.

howeve nested classes can access private members of the outer class that are in scope : lets illustrate with an example:
```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
public:
  using intType = int;

  class Printer
  {
  public:
    void print (Employee e)
    {
      std::cout << e.name << " - " << e.wage << " - " << e.id << '\n';
    }
  };

private:
  intType m_id {};
  std::string m_name {}
  intType m_wage {};

public:
  Employee ( intType id, std::string_view name, intType wage )
  : m_id { id }
  , m_name { name }
  , m_wage { wage }
  {}
};

int main()
{
  Employee john { 0, "John", 20'000 }
  Employee::Printer p{};
  p.print( john );
  return 0;
}
```
nested types are usually declared as `iterators` in real world applications: in c++ the `std::string::iterator` object is implemeted as a nested class.

Nested types can’t be forward declared
--------------------------------------
thats a limitaion dont really care to think why tho.

---------------------------------------------------------------------

Introduction to destructors
===========================

lets say were making some sort of application that collects some data asd sends them to some network at once we might structure it something like this:
```cpp
class NetworkData
{
private:
  std::string m_serverName {};
  std::vector m_data {};

public:
  NetworkData(std::string_view name)
  : m_serverName { name }
  {}

  void addData(std::string_view data)
  {
    m_data.pushBack( data );
  }

  void sendData()
  {
    // creates connection to network
    // sends the data
    // closes connection and performs cleanup
  }
};

int main()
{
  NetworkData server { "www.Athell.ai" };
  server.addData("pings");
  server.addDate("logins");
  server.sendData();

  return 0;
}
```
although this works it has a potential probelem: it relies on sendData to be explicitly called for any data sending to occur. if not called the data might be lost
and not sent to the server and will be lost when the programs exits.

in order to curb this potential hazaerd from manidesting we use `Destructors`.

Destructors to the rescue
-------------------------
destructors are function that are called before an object is destroyed to carry out actions that the object must invariantly perform to be of valid state.
they only apply to non-aggregate class types

Destructor naming
-----------------
naming rules of destructors:
1. the most have the same name as the class but preceded by a tilde (`~`).
2. destructors cannot take arguments.
3. destructors have no retun type.

a class can only have a single destructor.
generally they should not be called explicitly (sepescially because they would stil be called automatically when the object is being destroyed)
Destructors may also safely call member function since an object is not destroyed until its desrtuctor has been called.

```cpp
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
```
result:
```bash
constructed id: 1
constructed id: 2
destroyed id: 2
destroyed id: 1
```
this shows that before an objest is called its destructors is called.

Note:
- static variables (including local and gloabals) are constructed at program startup and destroyed at program shutdown.

Improving the UserSettings program
----------------------------------
we'll make the destructor call the `sendData()` functions before the objects is destroyed:
```cpp
class NetworkData
{
private:
  std::string m_serverName {};
  std::vector m_data {};

public:
  NetworkData(std::string_view name)
  : m_serverName { name }
  {}

  ~NetworkData()
  {
    sendData();                     // makes sure all data is sent before the object is destroyed.
  }

  void addData(std::string_view data)
  {
    m_data.pushBack( data );
  }

  void sendData()
  {
    // creates connection to network
    // sends the data
    // closes connection and performs cleanup
  }
};

int main()
{
  NetworkData server { "www.Athell.ai" };
  server.addData("pings");
  server.addDate("logins");

  return 0;
}
```

An implicit destructor
----------------------
is a non-aggregate class type is declared with no user-defined destructor, the compiler will generate a destuctor with an empty body. this is an implicit destructor
and its effectively just a placeholder.

so only declare destructors if you need them: if not leave the destruction to the implicitly gernerated destructor.

A warning about the std::exit() function
----------------------------------------
they halt programs and may not allow objects destuctors to be called so be careful with them.

For advanced readers
--------------------
unhanlded exceptions may terminate programs which may not allow `stack unwinding` to occur: which might lead to destructors not being called.

-------------------------------------------------------------------------------------------------------------------------------------------

 Class templates with member functions
=======================================
yup lest dive into this shit:

Type template parameters in member functions
--------------------------------------------
```cpp
#include <ios>
#include <iostream>

template <typename T>
class Pair
{
private:
  T m_first {};
  T m_second {};

public:
  Pair( const T& first, const T& second )
  : m_first { first }, m_second { second }
  []

  bool isEqual (const Pair<T>& pair);
};

template <typename T>
bool Pair<T>::isEqual(const Pair<T>& pair)
{
  return m_first == pair.first and m_second == pair.second
}

int main()
{
  Pair p1 { 5, 6 };
  std::cout << std::boolalpha << "isEqual(5, 6) " << p1.isEqual( Pair { 5, 6 } ) << '\n';
  std::cout << std::boolalpha << "isEqual(5, 6) " << p1.isEqual( Pair { 5, 7 } ) << '\n';

  return 0;
}
```

things to note about the above snippet:
1. its not an aggregate, so we cant use aggregate initialization.
2. we make the paramaters of our construtcors a `const reference` becaue the arguments might be expenisve to copy so its safer this way.
3. when we declare member functions for the class we dont need to specify template definations: it implictlty uses the template defination of the class.
4. we dont need deduction guides for CTAD to work with non-aggregate clases. a matching constructor provides the compiler with the information it needs to deduce the template parameters 
   from the initializers.
5. now lets look at situation where we declare member functions outside the body of its class: here we have to reapply the template declaration so the compiler can know what T is 
   we also need to qualify the member function name with the fully templated nama of the class template.
  ```cpp
  template <typename T>
  bool Pair<T>::isEqual (const Pair<T>& p)
  {
    return m_first == p.first and m_second == p,second;
  }
  ```

-------------------------------------------------------

Static member variables
=======================
