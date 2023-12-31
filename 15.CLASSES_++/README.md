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
static nmember variables are declared using the static keyword. they are shared by all objects of a class.
```cpp
#include <iostream>

struct Something
{
  static int value;
};

int Something::value { 1 };

int main()
{
  Something first {};
  Something second {};

  first.value = 2;

  std::cout << first.value << '\n';
  std::cout << second.value << '\n';

  return 0;
}
```

this results to both the first and second `Something` objects having the same value: 2.

Static members are not associated with class objects
----------------------------------------------------
they are not associated with class objects, they are just basically scoped global variables to be accessed using the class identifier as its namespace.
they exist even if no object is instantaiated: this makes sense since because they have static duration being `static` and all.

Defining and initializing static member variables
-------------------------------------------------
when we declare static member variables ina class its act like somewhat of a forward declaration, the compiler doesnt allocate memory for it yet it just becomes aware of its existence.
becuase `static member varibales` are essentilly global variables, you must explicitly define (and optionally initialize) the static member outside the class. in the global scope.

in the example code snippet above we did this via this line:
```cpp
int Something::value { 1 };               // defines the static member variable.
```
the above lines serves two functions: instantiates the static member variable (just like a global variable) then initializes it. if left unitialized the static member variables
are zero initialized by default.

Note
----
- static member variables are not subjected to access controls: you can define and initialize the value eben if its declared as private or protected in a class.
- if the class is placed in a header file (eg `something.h`), its static member definations are usually placed in the associated code file for the class (eg `something.cpp`)
- if the class is declared in a source file (`.cpp`) the static member variables is usually declared below it in the same file.
- do not define static member variables in a header file (just as global varibles, if they are include more than once you can end up with multiple definations and a possible compile error.)

Initialization of static member variables inside the class definition
---------------------------------------------------------------------
if a static member is a const integeral type: `char`, `bool`, `const enum` etc. the static variable can be initialized inside a class:
```cpp
class SomeShiz
{
public:
  static const int s_value { 4 };             // a static const integral type can be defined and initialized directly.
};
```
c++17 allows static member variables to be inline: they can be initialized inside class definations regardless whether they are constant or not:
```cpp
class Whatever
{
public:
  static inline int s_value { 3 };
};
```
this is the preferred method of declaring static member variables.

because `constexpr` members are implicitly inline they can be used to declare static member variable without using the `inline` keyword.
```cpp
#include <iostream>

class Whatever
{
public:
  static constexpr int s_value { 4 };
  static constexpr std::string_view s_string { "Hello" };
};
```

best practice
-------------
make your static members `inline` or `constexpr` so they can be initialized in your class defination.

An example of static member variables
-------------------------------------
we can use it to assign unique ids to every object spawned from the class.
```cpp

class Something
{
private:
  static inline int m_idGenerator { 0 };
  int m_id {};

public:
  Something() { m_id = ++m_idGenerator; }
  int getId() const { return m_id; }
};

int main()
{
  Something first{};
  Something second{};
  Something third{};

  std::cout << first.getID() << '\n';
  std::cout << second.getID() << '\n';
  std::cout << third.getID() << '\n';
  return 0;
}
```


Static member functions
=======================
member finctions can alos be made static the can be used as accessor for static member variables:
```cpp
class Something
{
private:
  static inline int m_value { 0 };

public:
  static int getValue() { return m_value; }
};

int main()
{
  std::cout << Something::getValue() << '\n';
}
```
since they are independent of the class they are declared in becasue of thier static nature they can be accessed without an instance of the class the belong to: just by using the class
as a namespace to access it.

Static member functions have no `*this` pointer
---------------------------------------------
- they are not attached to any object: they have no `this` pointer
- static member function can access other static members( variables or functions) but not non-static members

Another example
---------------
static member function can be defined outside the class declaration: this works the same way as normal member functions.
```cpp
#include <iostream>

class IDGenerator
{
private:
  static inline int s_nextId { 0 };

public:
  static int generateID();
};

int IDGenerator::generateID()
{
  return s_nextID++;
}

int main()
{
  for (int count{ 0 }; count <= 10; count++)
    std::cout << IDGenerator::generateID() << '\n';

  return 0;
}
```
this works as one should expect.

A word of warning about classes with all static members
-------------------------------------------------------
pure static classes are called monostates: they can be useul but come with downsides.
wo read this stuff at the site.

Pure static classes vs namespaces
----------------------------------
they are generally the same just classes posses access controls which namespaces do not.

C++ does not support static constructors
----------------------------------------
yup: but if you can directly initialize your members no constructor should be needed. thats why its recommended to qualify static member variables as `inline` or `constexpr`.
```cpp
#include <array>
#include <iostream>

struct myClass
{
  static inline std::array s_mychars { 'a', 'e', 'i', 'o', 'u' };
};

int main()
{
  std::cout << MyClass::s_mychars[3];
}
```

if initializing your static member variable requires executing some code there are many obtuse way of achieving this: one way that works for all variable members (not only static) is to usea function
to create an object fill it with data and return it to the caller:
```cpp
#include <array>
#include <iostream>

class MyClass
{
private:
  static std::array<char, 5> generate()
  {
    std::array<char, 5> arr;
    arr[0] = 'a';
    arr[1] = 'e';
    arr[2] = 'i';
    arr[3] = 'o';
    arr[4] = 'u';

    return arr;
  }

public:
  static inline std::array s_myArray { generate() };
};

int main()
{
  std::cout << MyClass::s_myArray[2] << '\n';
}
```


 Friend non-member functions
=============================
in cases where we want to give some sort of access to the private and protected members of a class to an outsider for some reasons, `friendship` is a nice solution to this
problem.

Friendship is magic
-------------------
when we declare a function (member or non member) or class a `friend` of another class the class being befriended has granted access to its private and protected members to its friend.
full access to be precise. friendship is always granted by the class to be accessed not the class that desires the access (that makes sense.)

for example if a display class was made the friend of a storage class the display class will be able to access members of the storage class to effectively display the storage
class mechanisms while remaining structurally seperate. `freindship is not affected by access controls.`

Friend non-member functions
---------------------------
an example:
```cpp
#include <iostream>

class Accumulator
{
private:
  int m_value {};

public:
  int add ( int value ) { m_value += value; }
  friend void print ( Accumulator& accumulator );
};

void print ( Accumulator& accumulator );
{
  std::cout << accumulator.m_value << '\n';         // because print is a friend is can access the private members of accumulator.
}
```

Defining a friend non-member inside a class
-------------------------------------------
friend non-member functions can also be declared inside a classes declaration using the `friend` keyword. they have no `*this` pointer and are treated as if they are
declared outside the class defination.
```cpp
#include <iostream>

class Accumulator
{
private:
  int m_value {};

public:
  int add ( int value ) { m_value += value; }
  friend void print ( const Accumulator& accumulator )      // not a member function.
  {
    std::cout << accumulator.m_value;
  };
};
```

Syntactically preferring a friend non-member function
-----------------------------------------------------
sometimes declaring non-member functions can be preferred to that of member functions:
```cpp
#include <iostream>

class Value
{
private:
  int m_value {};

public:
  explicit Value(int v): m_value { 7 } { }
  bool isEqualToMember ( const Value& v ) const ;
  friend bool isEqualToNonMember ( const Value& u, const Value& v );
};

bool Value::isEqualToMemeber (const Value& v) const
{
  return m_value == v.m_value;
}

bool isEqualToNonMember (const Value& u, const Value& v)
{
  return u.m_value == v.m_value;
}
```
so according to the shiz i just read the non-member functions  makes reading and knowning who owns what memeber easier and encourages a parallel modular structure
which sounds like a good thing to have.

Multiple friends
----------------
a function can be friends to more than one classes at the same time (like a `slut`)
``` cpp
#include <iostream>

// forward declaration of Humidity class becuase
// it would be referenced before its implemetation in the temperature class
class Humidity;

// class 1
class Temperature
{
private:
  int m_temp { 0 };

public:
  explicit Temperature (int temp) : m_temp { temp } {  }
  friend printWeather (const Temperature& temp, const Humidity& humid);
};

// class 2
class Humid
{
private:
  int m_humid { 0 };

public:
  explicit Humidity (int humid) : m_humid { humid } {  }
  friend printWeather (const Temperature& temp, const Humidity& humid);
};

void printWeather ( const Temperature& temp, const Humidity& humid )
{
  std::cout << "The temperature is " << temp.m_temp <<
       " and the humidity is " << humid.m_humidity << '\n';
}
```
Doesn’t friendship violate the principle of data hiding?
--------------------------------------------------------
1. A friend function should prefer to use the class interface over direct access whenever possible.
2. Prefer to implement a function as a non-friend when possible and reasonable.


Friend classes and friend member functions
==========================================
1. friendship is not reciprocal: just because you made a class your friend doesnt mean the class sees you as a friend, `damn`.
2. class friendship is not transitive: just because A is a friend of B and B is a friend of C, that doesnt mean A is a friend of C.
3. friendship is also not inherited: if A makes B a friend, classes derived from B do not implicitly become friends with A.

Friend member functions
-----------------------
instead of making an entire class a friend. we can make a single member function a friend. this is done similarly to making non-member function a friend, excpet the
name of the member function is used instead.

this can be done by trying something like this:
```cpp
#include <iostream>

class Display;    // forward declaration for display class

class Storage
{
private:
  int m_value {};
  double d_value {};

public:
  Storage(int nValue, double dValue)
    : m_nValue { nValue }, m_dValue { dValue }
  {
  }

  friend void Display::displayStorage(const Storage& storage);                      // this results to an error.
};

class Display
{
  //...
  void displayStorage(const Storage& storage)
	{
		if (m_displayIntFirst)
			std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
		else // display double first
			std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
	}
  //...
};
```
the above code will error out because in order to make a member function a friend the compiler has to see the full defination of the member function, a forward declaration
will not suffice. since the storage class havent seen the defination of the class it errors out.
this, fortunately, can be resolved by declaring and defining (or only just defining it) the class before the class that needs it member as a friend.
and alos declaring a forward declaration of the storage class because it becomes referenced by the display class now and due to the current order its has no reference of the Storage class
(this is fixed by the class forward declaration as stated before.)
```cpp
#include <iostream>

class Storage;            // forward declaration become this class becoems referenced in the firstly declared class the display class.

class Display
{
  //...
  void displayStorage(const Storage& storage);                       // this is were the Storage class is referenced: will have errored out but luckily a forward declaration exists.
  //...
};

class Storage
{
private:
  int m_value {};
  double d_value {};

public:
  Storage(int nValue, double dValue)
    : m_nValue { nValue }, m_dValue { dValue }
  {}

  friend void Display::displayStorage(const Storage& storage);                      // this is legal: no error.
};

void Display::displayStorage(const Storage& storage)  // we define the member function outside its class becaue friend member functions need thier full declaration to be seen.
{
  if (m_displayIntFirst)
    std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
  else
    std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
}
```


Ref qualifiers
==============
read this part yourself
