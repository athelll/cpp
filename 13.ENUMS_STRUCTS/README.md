=    Felix Okoronkwo Dec. 7 2023    =
= Compound Types: Enums and Structs =

Introduction to program-defined (user-defined) types
====================================================

Introduction
------------
`user-defined` or `program defined` types are ty[rs implemented by we the programmer.
C++ has to types of `user-defined` compound types:
1) enumerated types (scoped and unscoped enumerations)
2) class types (structs, class and unions)

Defining program-defined types
------------------------------
just like types aliases, program defined types also need to be defined before they are used. an Example with structs:
```cpp
struct fraction
{
  int numerator   {};
  int denuminator {};
}

int main()
{
  fraction f{ 3, 4 };
}
```

the defination of a program-defined type is known as `type defination`.
type defiation does not allocate any memory its just a blueprint that tells the compiler how a fraction looks like.
Program defined types always end with a semicolon `;`

Naming program-defined types
----------------------------
by convention program defined types are named starting with capital letters and have no suffix.

Using program-defined types throughout a multi-file program
-----------------------------------------------------------
Every code hat uises a program defined type  needs to see its defination before its used. A forward declaration is not sufficient. this is so the compiler
knows the amount of memory to allocate for the types objects.

and because of this program defined types are usually declared in header files then are `#included` where needed.

Type definitions are partially exempt from the one-definition rule (ODR)
------------------------------------------------------------------------
types are partially exempt from the one-definition rule: a given type is allowed to be defined in multiple code files.


Unscoped enumerations
=====================

Introduction
------------
An Enumeration is a compound data types that its values are restricted to set of named symbolic constants (called `enumerators`).
they are of 2 types:
1) scoped enumeration
2) unscoped enumeration

Unscoped enumerations
---------------------
they are defined via the `enum` keyword.
and example of unsocped enumerators:
```cpp
enum Color
{
  red,        // enumerators are symbolic constants seperated by commas.
  green,
  blue,
};            // enum types defination must end with a semi-colon (as all compound data types)

int main()
{
  Color apple { red };
  Color shirt { green };
  Color sky   { blue };

  Color sock  { white };      // error: this is not an enumerator of Color.
}
```

By convention, the names of enumerated types start with a capital letter (as do all program-defined types).

Putting enumerations to use
---------------------------
sometimes function retunr status code to determine if a function executed succesfully or not or the state of the aftermath of the function, like so:
```cpp
int readFileContent()
{
  if(!openFile())
    return -1;
  if(!readFile())
    return -2;
  if(!parseFile)
  return -3;
}
```
although the above code works, it introduces a problem: magic numbers.
though this can fixed quickly by using `enumerations`.

like so:
```cpp
enum FileStatus
{
  fileSuccess,
  openingFailed,
  readingFailed,
  parsingFailed,
}

FileStatus processFile()
{
  if(!openFile())
    return openingFailed;
  if(!readFile())
    return readingFailed;
  if(!parseFailed())
    return parsingFailed;

  return fileSuccess;
}

// then the caller can test the result and perform an action
int main()
{
  if(processFile() == readingFailed)
  {
    // perform something
  }
  else
  {
    // do something else
  }
}
```

enumerated types can be put to good use in games to identify tyoes of items, monster or terrain types.
basically anything that is a small set of related objects:
```cpp
enum ItemType
{
  sword,
  torch,
  potion,
}

int main()
{
  ItemType holding{ torch };
}
```

because enumerations are small and inexpensive to copy, it is fine to pass (and return) them by value.

Note:
----
enumarotors can also be used as bit flags for bitset objects:
```cpp
#include <bitset>
#include <iostream>

namespace Flags
{
  enum State
  {
    isHungry,
    isSad,
    isMad,
    isHappy,
    isLaughing,
    isAsleep,
    isDead,
    isCrying,
  }
}

int main()
{
  std::bitset<8> me{};
  me.set(Flags::isHungry);
  me.set(Flags::isAsleep);

  std::cout << std::boolalpha;

  std::cout << "I am happy? " << me.test(Flags::isHappy) << '\n';
  std::cout << "I am laughing? " << me.test(Flags::isLaughing) << '\n';

  return 0;
}
```
unscoped enumarators implicity comvert to `integers` when needed (hope that explains the magic above): will be explained in detail later tho.

The scope of unscoped enumerations
----------------------------------
unsoped enumarations are named such because they place thier enumerators in the scope they where declared in therefore: if an unscoped enumaration is declared in the global scope
its enumerators belong to the global scope too.

due to the fact that enumartors eblong to the scoped of their enumarations this increases the chances of naming collisions drastically. so to prevent this
one enumarator name cant be used in another enumeration defination when both enumarations are declared in the same scope:
```cpp
enum Color
{
  red,
  blue,
  greem,
}

enum Feeling
{
  happy,
  hungry,
  blue,                   // identifier collision in the same scope: compile error
}
```

unscoped enumartors can be accessed using the scope operator (as in `Color::red`), but usually they arent accessed in this manner.

Avoiding enumerator naming collisions
-------------------------------------
1) One option is to prefix each enumerator with the name of the enumeration itself
2) A better option is to put the enumerated type inside something that provides a separate scope region, such as a namespace

Comparing against enumerators
-----------------------------
we can use the `==` or `!=` comparisons operators to compare if a value is the same as a speific enumerator or not.


Unscoped enumeration input and output
=====================================

when we assign enumarators to an enumaration each enumerator is basically assigned a value and by default the first enumerators is assigned the value `0` then the values of the
subsequents that follow are incremented.
```cpp
enum MyLife
{
  pain,                     // assigned the int value 0
  soorow,                   // assigned 1
  misery,                   // assigned 2
  shortt,                   // assigned 3
  unachieved,               // assigned 4
  hater,                    // assigned 5
};

int main()
{
  MyLife is { pain };       // assigned the value 0.
  return 0;
}
```

it is possible to define the value of an enumerator but keep in mind that following enumerators after the one you defined will be incremented by `1` until another explicitly defined
enumerator is found and then its following enumerators will be incremented (by one) from whatever value was explicitly set by the newly defined enumerator.
example:
```cpp
enum Names
{
  Felix      = -4,
  Ikechukwu,          // assigned value -3
  Okoronkwo,          // assigned value -2
  Hedwig     = 2,
  Adachukwu,          // assigned value  3
  Zuriel,             // assigned value  4
  Naomi,              // assigned value  5
};
```

Unscoped enumerations will implicitly convert to integral values
----------------------------------------------------------------
yes they do, if ypu need them to print their names you need a helper function to that for you:
```cpp
#include <iostream>
#include <string>

enum Color
{
  red,        // assigned 0
  blue,       // assigned 1
  green,      // assigned 2
};

constexpr std::string_view returnName( Color x )
{
  switch(x)
  {
    case red:     return "red";
    case blue:    return "blue";
    case green:   return "green";
    default:      return "???";
  }
}

int main()
{
  constexpr Color selected { blue };
  std::cout << "you just selected " << returnName(blue) << '\n';
  return 0;
}
```

Teaching operator<< how to print an enumerator
----------------------------------------------
this is done using operator overloading (will be explained later):
check the code named `overload_operator_<<.cpp` to see implementation.

Enumeration size and underlying type (base)
-------------------------------------------
the enumerators of an enumaraton are constant intgerals. the specific integral type used is known as the underlying type or base.
most of the times is an `int` but it can be specified if you need to store larger or smaller values:
```cpp
#include <cstdint>
#include <iostream>

enum Color: std::int8_t
{
  black,
  red,
  blue,
};

int main()
{
  Color c{black};
  std::cout << sizeof(c) << '\n';             // prints 1 byte
  return 0;
}
```

Integer to unscoped enumerator conversion
-----------------------------------------
while the compiler will implicitly convert enumerators to integeral types: it will not implictly convert integral types to enumerators.
```cpp
enum Pet // no specified base
{
  cat, // assigned 0
  dog, // assigned 1
  pig, // assigned 2
  whale, // assigned 3
};

int main()
{
  Pet my { 2 };     // compile error: does not implicitly convert.
  my = 3;           // compile error: will not convert
}
```

this can be fixed by converting the integral type to the enums type by using `static_cast<>()`
example:
```cpp
int main()
{
  Pet my { static_cast<Pet>(2) };
  my = static_cast<Pet>(3);           // pig has evolved into a whale.

  return 0;
}
```

in =<C++17 if an enum is based specified, it allows list initialization for objects of its type:
```cpp
enum Pet: int   // base specified.
{
  cat,
  dog,
  pig,
  whale,
};

int main
{
  Pet pet1{ 2 };      // okay this is legal: pig
  Pet pet2 = 2;       // compile error: illegal
  Pet pet3 (2);       // compile error: illegal

  pet1 = 3;           // compile error: illegal
}
```

Unscoped enumerator input
-------------------------
Because Pet is a program-defined type, the language doesn’t know how to input a Pet using std::cin
To work around this, we can read in an integer, and use static_cast to convert the integer to an enumerator of the appropriate enumerated type:
```cpp
#include <iostream>

enum Pet
{
  cat, // assigned 0
  dog, // assigned 1
  pig, // assigned 2
  whale, // assigned 3
};

int main()
{
  Pet selected;
  std::cout << "Select the pet you want (0=cat, 1=dog, 2=pig, 3=whale)";

  {
    int input{};
    std::cin >> input;
    selected = static_cast<Pet>(input);
  }
  return 0;
}
```

TeachinG the operator>> to take in enum types through operator overloading (ADVANCED)
-------------------------------------------------------------------------------------
```cpp
#include <iostream>

enum Pet
{
  cat, // assigned 0
  dog, // assigned 1
  pig, // assigned 2
  whale, // assigned 3
};

std::istream& operator>>(std::istream& in, Pet& x)
{
  int input{};
  in >> input; // input an integer

  x = static_cast<Pet>(input);
  return in;
}

int main()
{
  int input{};
  in >> input; // input an integer

  pet = static_cast<Pet>(input);
  return in;
}
```


Scoped enumerations (enum classes)
==================================

Scoped enumerations
-------------------
scoped enumeration work similar as thier unscoped counterparts but they posses 2 primary differences:
1) they are strongly typed (unlike unscoped enums) and will not implicilty evaluate to integral types when coerced
2) they are strongly scoped (the enumerators are only placed in the scope region of their enumeration).

to make scoped enumerations we use the keyword `enum class`
an example of its implementation:
```cpp
#include <iostream>

int main()
{
  enum class Color
  {
    red,
    green,
    blue,
  };

  enum class Fruit
  {
    banana,
    kiwi,
    apple,
  }

  Color color { Color::red };                         // enumerators cannot be accessed without specifying its scope.
  Fruit fruit { Fruit::kiwi };                        // same as above.

  if (color == fruit)                                 // does not compile: compiler has no way to compare color and fruit because they are strongly typed.
    std::cout << "color and fruit are equal\n";
  else
    std::cout << "color and fruit are not equal\n";
}
```

Scoped enumerations define their own scope regions
--------------------------------------------------
scoped enumerations place their emumarators in thier scope region and not the scope they are declared in (like unscoped enumeration).
in pother words scoped enumerations act like namespaced for thier enumerators. this built in namespacing helps reduce namespace pollution and potential identifier collisions.
to access a scoped enumerator we use it liek we are trying to access am object or variable in a namespace:
```cpp
#include <iostream>

int main()
{
  enum class Color
  {
    red,
    blue,
  };
  std::cout << red << '\n';                       // compile error: the compiler does not know what red is
  std::cout << Color::red << '\n';                // compile error: it recongnizes red know but cout doesnt not how to handle it (remember it does not implicitly convert)

  Color color { Color::blue };                    // this is legal.
  return 0;
}
```

Scoped enumerations don’t implicitly convert to integers
--------------------------------------------------------
they do not convert implicitly to ints in situations they should but they can be converted explicitly bv using the `static_cast<>()` function.
or the `std::to_underlying()` defined in the `<utility>` header: which converts enumerators to thier underlying type value.
```cpp
#include <iostream>
#include <utility>

int main()
{
  enum class Color
  {
    red,
    blue,
  };

  Color color { Color:blue };

  std::cout << color << '\n';                           // wont work because no implicit conversion to int
  std::cout << static_cast<int>(color) << '\n';         // this is legal because we introduced explicit conversion
  std::cout << std::to_underlying(color) << '\n';       // this is legal also: we are converting to the underlying type.
}
```

NOTE:
----
- Favor scoped enumerations over unscoped enumerations unless there’s a compelling reason to do otherwise.

Easing the conversion of scoped enumerators to integers (advanced)
------------------------------------------------------------------
this can be done overload the unary `operator+` to perform this action:
```cpp
#include <iostream>
#include <type_traits>

enum class Animals
{
  chicken,
  dog,
  cat,
  elephant,
  duck,
  snake,
  maxAnimals,
}

constexpr auto operator+(Animals a) noexcept
{
  return static_cast<std::to_underlying_type_<Animals>>(a);
}

int main()
{
  std::cout << +Animals::elephant << '\n';    // converts elephant tp integer using the operator+
}
```

Note:
----
- the `std::to_underlying()` belongs to the header `utility`: and what it does is convert enumerators to thier underlying types (as of what i know now)
- the `std::to_underlying_type<typename T>()`belongs to the `type_traits`: and what it does is extract the underlying type of an enumaration.

using enum statements
---------------------
this was introduced in c++20 it was used as a way to place all enumerators in a scoped enumeration in a desired scope: alloeing them to be accessed without a scope prefix.
example:
```cpp
#include <iostream>
#include <string_view>

enum class Color
{
  black,
  red,
  green,
};

constexpr std::string_view getColor(Color color)
{
  using enum Color; // bring all Color enumerators into current scope (C++20)
  // We can now access the enumerators of Color without using a Color:: prefix

  switch (color)
  {
  case black: return "black"; // note: black instead of Color::black
  case red:   return "red";
  case blue:  return "blue";
  default:    return "???";
  }
}

int main()
{
  Color shirt{ Color::blue };
  std::cout << "Your shirt is " << getColor(shirt) << '\n';
  return 0;
}
```


Introduction to structs, members, and member selection
======================================================
structs in C.
```cpp
struct Employee
{
  // below are the member variable of this struct.
  std::string name{};
  int id{};
  int age{};
  double wage{};
}

// they are acessed using the member selection operator. (the full-stop is the operator).
int main()
{
  Employee joe {};
  joe.name = "Joe";
  joe.age  = 32;

  return 0;
}
```


Struct aggregate initialization
===============================

Data members are not initialized by default.

What is an aggregate?
---------------------
an aggregate datatypes is a dataype that can contain mutiple data members. some aggregate allow memebers to be of different types (eg. structs), while others require
they be of the same type (eg. arrays).

Aggregate initialization of a struct
------------------------------------
there a re 2 primary forms of aggregate initialization of struct object in c++:
```cpp
struct Employee
{
  int id{};
  int age{};
  double wage{};
};

int main()
{
  Employee frank = { 0, 23, 60000.0 };      // copy-list initialiation
  Employee Ocean { 1, 21,  54000.0 };         // direct-list initialization
  return 0;
}
```

Missing initializers in an initializer list
-------------------------------------------
if an aggregate is initialized but the number of initialiation values is fewer than the number of members, then all remaining members will be value-initialized.
```cpp
struct Employee
{
  int id{};
  int age{};
  double wage{};
};

int main()
{
  Employee joe { 2, 28 };     // joe.wage will be value-initialized to 0.0
  return 0;
}
```

Const structs
-------------
read that part not that important

Designated initializers
-----------------------
when initializing a struct from a list of values, the initializers are applied to the members in order of declaration
and if not all the members were given a value it can lead to your members value shifted especially when the strict type defination is modified:
```cpp
struct Foo
{
  int a{};
  int b{};          // this was not included previously so the below initiliation was once: f.a=1, f.c=3
  int c{};
};

int main()
{
  Foo f {1, 3};     // f.a=1, f.b=3, f.c=0 : the values have been shifted (thats if you read the previous comment)
}
```

to fix this issue of initialization shifting after modification of the strict defination, c++20 introduced `designated initializers`.
`designated initializers` allow us to specify what member is about to be initialized. they must be initialized in the same order they are declared tho.
they can be used with wither list-brace initialiation style or just copy initialization:
```cpp
struct Foo
{
  int a{};
  int b{};
  int c{};
};

int main()
{
  Foo f1{ .a{ 1 }, .c{ 3 } };
  Foo f2{ .a=1, .c=3 };
  Foo f3{ .b{ 2 }, .a{ 1 } };                 // error (illegal): does not follow the order of declaration.
}
```

Best Practice:
--------------
++++++++++++++
When adding a new member to an aggregate, it’s safest to add it to the bottom of the definition list so the initializers for other members don’t shift.

Assignment with an initializer list and possiby designated initializers
-----------------------------------------------------------------------
when we want to upate many members in a struct we can use an initializers list:
```cpp
struct Employee
{
  int id {};
  int age {};
  double wage {};
};

int main()
{
  Employee joe { 1, 32, 50000.0 };
  joe = { joe.id, 33, 60000.0  };                 // joe got a raise and its his birthday: we updated this using assignmnet with an initializers list.

  // the above can also be done with designated initializers:
  joe = { .id=joe.id, .age=34, .wage=70000.0 };   // joe got another raise and ist his birthday again
  return 0;
}
```

Initializing a struct with another struct of the same type
----------------------------------------------------------
```cpp
#include <iostream>

struct Foo
{
  int a{};
  int b{};
  int c{};
};

int main()
{
  Foo foo { 1, 2, 3 };

  Foo x = foo;                  // copy initialization
  Foo y( foo );                 // direct initialization
  Foo z{ foo };                 // list initialization
}
```


Default member initialization
=============================
when declaraing and defining a struct we can declare their members with default values as part of thier defination:
```cpp
struct Something
{
  int x;                       // no initialization value (bad)
  int y {};                    // value-initialized by default
  int z { 2 };                 // explicit default value
};

int main()
{
  Something s;                 // s.x is unitialied, s.y is value initialized to 0, s.z is 2.
}
```

- Explicit initialization values take precedence over default values (obvi.)

Missing initializers in an initializer list when default values exist
---------------------------------------------------------------------
```cpp
struct Something
{
  int x,
  int y{},
  int z{ 2 };
};

int main()
{
  something s1{};           // since this was emptily list intialized: s1.x is value initialized (0), s1.y is value initialized (0), s1.z uses its default value (2)
}
```

In the above example the reason that `s1.x` is initialized despite having no initializer is because `s1` was declared with list initialization: therefore all its
members will be value initialized to `(0)` if they don't possess any default value.

Recap of struct initialization behaviours
-----------------------------------------
```cpp
struct Sonething
{
  int a;
  int b{};
  int c{ 2 };
};

int main()
{
  something s1;                       // no intializer: therefor s1.a not initialized, s1.b value initialized (0), s1.c uses default value
  something s2{ 5, 6, 7 };            // uses the list initializer to initialize the struct object members
  something s3{};                     // since initialized with an empty initializer: all members are value initialized to (0) except s3.c which uses its default value.
}
```


Always provide default values for your members
----------------------------------------------
always declare your struct members with default values or with an empty direct list initialization (this is because they would be value initialized to 0).
except theres a reason not to follow this path.


Passing and returning structs
=============================

Passing structs (by reference)
------------------------------
we can pass an entire struct to a fuction for its members to be accessed by that struct using a reference
they are usually passed using a const reference to avoid making copies.
```cpp
#include <iostream>

struct Employee
{
  int id{};
  int age{};
  double wage{};
};


std::ostream& operator<<(std::ostream& out, Employee& x)
{
  return out << "id:   " << x.id << '\n' << "age:  " << x.age << '\n' << "wage: " << x.wage;
}

void raise_employee(const Employee& x)
{
  x.wage += 10'000.0;
}

int main()
{
  Employee frank { 0, 21, 0.0 };
  raise_employee(frank);
  std::cout << frank << '\n';
}
```

Returning structs
=================

this is the strict well be returning:
```cpp
struct Point3d
{
  double x { 0.0 };
  double y { 0.0 };
  double z { 0.0 };
};
```

return syntax 1:
----------------
```cpp
Point3d getZeroPoint()
{
  Point3d temp { 0.0, 0.0, 0.0 };
  return temp;                          // here we created a struct object, initialized it and returned it
}
```

return syntax 2:
---------------
```cpp
Point3d getZeroPoint()
{
  return Point3d { 0.0, 0.0, 0.0 };     // here we returned an anonymous struct object with the values we want it to have list initialized.
}
```

return syntax 3:
----------------
```cpp
Point3d getZeroPoint()
{
  return { 0.0, 0.0, 0.0 };             // here we return the a list initializer of the values we want but because we are returning a `Point3d` type we dont need to
  //                                       specify it in the return type
}
```

return syntax 4:
----------------
```cpp
Point3d getZeroPoint()
{
  return {};                            // here we return an empty list initialzer which in return coerces the members or the anonymous Point3d object (that will be returned)
  //                                       to value initialize all its members to 0.0 or zero.
}
```


Struct miscellany
=================

in c++ structs (and classes) can have program defined types as members, there are 2 ways to do this,

Firstly:
```cpp
#include <iostream>

struct Employee
{
  int id {};
  int age {};
  double wage {};
};

struct Company
{
  int numberOfEmployees {};
  Employee CEO {};                                  // employee is a struct within the struct company
};

int main()
{
  Company myCompany { 10, { 0, 22, 100'000.0 } };   // nested list initialization to initialize employee CEO.
  std::cout << myCompany.CEO.wage << '\n';
}
```

Secondly:
```cpp
#include <iostream>

struct Company
{
  struct Employee             // accessed via Company::Employee
  {
    int id {};
    int age {};
    double wage {};
  };

  int numberOfEmployees {};
  Employee CEO {};            // Employee is a struct within the Company struct.
};

int main()
{
  Company myCompany { 7, { 0, 21, 1'000'000.0 } };   // nested list initialization to initialize employee CEO.
  std::cout << myCompany.CEO.wage << '\n';
}
```


Struct size and data structure alignment
----------------------------------------
read this part on the site

but what i do know is that the size of a struct will be at least the size of all the members declared in the struct (meaning it can be more: usually its more tho).
and the order of the declaration of the types that make up the struct also has an effect on the size too.


Member selection with pointers and references
=============================================
same as pointer with with structs in C and since references act as the objects itself we can just use the `operator.` instead of the `operator->` (as we would have
done if we where trying to access the member of a struct object through a pointer to that object).


Class templates
===============

this place looks long.
unlike functions type defination cannot be overloaded, the compiler sees this as an errorneous redclaration of the first defination.

Class templates
---------------
this is a solution to our above problem, it is declared the same way we declare templates for functions:
```cpp
#include <string>

template <typename T>
struct Pair
{
  T first  {};
  T second {};
};

int main()
{
  Pair<int>           p1 { 1, 2 };
  Pair<double>        p2 { 3.0, 4.0 };
  Pair<std::string>   p3 { "hello", "pain" };
}
```

the above code is translated (in its translated unit) into:
```cpp
#include <string>

template <typename T>
struct Pair;

template <>
struct Pair<int>
{
  int first {};
  int second {};
}

template <>
struct Pair<double>
{
  double first {};
  double second {};
}

template<>
struct Pair<std::string>
{
  std::string first {};
  std::string second {};
}

int main()
{
  //
}
```

Using our class template in a function
--------------------------------------

lest decleare an example with a max() function:
```cpp
#include <iostream>

template <typename T>
struct Pair
{
  T first   {};
  T second  {};
};

template <typename T>
constexpr T max(Pair<T> p)
{
  return (p.first > p.second ? p.first : p.second);
}

int main()
{
  Pair<int> p1 { 1, 2 };
  std::cout << max<int>(p1) << '\n';

  Pair<double> p2 { 3.0, 4.0 };
  std::cout << max<double>(p2) << '\n';
}
```

Note:
- Class templates can posses both template type and non-template type members
- Class templates can posses multiple template types
```cpp

template <typename T, typename U>
struct Pair
{
  T first;
  U second;
}

template <typename T, typename U>
void print( Pair<T, U> p )
{
  std::cout << '[' << p.first << ',' << p.second << ']' << '\n';
}
```

Note:
----
- to stick to simple template parameter names, such a T, U, N, as they are less likely to shadow a class type name.

std::pair
---------
because working with pairs is common in C++ and computing as a whole: the c++ stndard library contains a class template named `std::pair` located in the `<utility>`
header, that is defined identically to our own pair class template and allows multiple template types.

```cpp
#include <iostream>
#include <utility>

template <typename T, typename U>
void print(std::pair<T, U> p)
{
  std::cout << '[' << p.first << ", " << p.second << ']';
}

int main()
{
  std::pair<int, double> p1{ 1, 2.3 }; // a pair holding an int and a double
  std::pair<double, int> p2{ 4.5, 6 }; // a pair holding a double and an int
  std::pair<int, int> p3{ 7, 8 };      // a pair holding two ints

  print(p2);
}
```

Using class templates in multiple files
---------------------------------------
just like function templates, class templates are declared in header files to be declared wherever they are needed: template defination and type definations
are exempts of the One Defination Rule in c++.

```cpp: pair.h
#ifndef PAIR_H
#define PAIR_H

template <typename T>
struct Pair
{
  T first;
  T second;
};

template <typename T>
constexpr T max(Pair<T> p)
{
  return (p.first > p.second ? p.first : p.second);
}

// now they can be included wherever they are needed using the #include directive.
#endif
```


Class template argument deduction (CTAD) and deduction guides
=============================================================

when instantiating an object from a class template, the compiler can deduce the type from the objects initializer this is called Class template argument deduction,
or CTAD for short.
an example:
```cpp
#include <utility>

int main()
{
  std::pair<int, int> p1 { 1, 2 };
  std::pair           p2 { 3, 4 };                    // CTAD occured here.
}
```

CTAD is on;y peformed when `no` tempplate argument list is present.

Template argument deduction guides C++17
----------------------------------------
in most cases CTAD works right out of the box, but depending on your compiler and your vwrsion of c++ the compiler might need extra help in understanding how to deduce
class template types.
the code below does not compile in c++17:
```cpp
// define our own Pair type
template <typename T, typename U>
struct Pair
{
  T first{};
  U second{};
};

int main()
{
  Pair<int, int> p1{ 1, 2 };        // ok: we're explicitly specifying the template arguments
  Pair p2{ 1, 2 };                  // compile error in C++17

  return 0;
}
```

the error might be something like:
1) class template argument deduction failed
2) cannot deduce template arguments
3) No viable constructor or deduction guide

but this can be fixed using a `deduction guide`:
```cpp
template <typename T, typename U>
struct Pair
{
  T first{};
  U second{};
};

template <typename T, typename U>
Pair(T, U) -> Pair<T, U>;           // this is the deduction guide.

int main()
{
  Pair<int, int> p1{ 1, 2 };        // explicitly specify class template Pair<int, int> (C++11 onward)
  Pair p2{ 1, 2 };                  // CTAD used to deduce Pair<int, int> from the initializers (C++17)

  return 0;
}
```

NOTe:
-----
- `std::pair` and other STL class template types come with pre-defined deduction guides: this is why they dont error even in c++17
- C++20 added the abiloty for the compiler to automatically generate deduction types for aggregate class types, so our program defined veriosn of Pair should compiler
  without issue in c++20.

Type template parameters with default values
--------------------------------------------
```cpp

template <typename T=int, typename U=int>     // this is a default teemplate type paramter
struct Pair
{
  T first  {};
  U second {};
};

template <typename T, typename U>
Pair(U, V) -> Pair<U, V>;

int main()
{
  Pair<int, int> pi { 1, 2 };                 // explicit declaration of argument types
  Pair p2 { 1, 2 };                           // CTAD in action here
  Pair p3;                                    // default type are used Pair<int, int>
}
```

CTAD doesn’t work with non-static member initialization
-------------------------------------------------------
oMO GEE read this part again.


Alias templates
===============
```cpp
using head = Pair<int>
```

Alias templates must be defined in global scope
