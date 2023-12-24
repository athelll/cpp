= Type Conversion and Function Overloading =
= Nov 21st 2023, Felix Okoronkwo =

Implicit type conversion
=========================================================================
the value of an objects is stored as sequences of bits:
the integer `3` might be stored as integer as     : `0000 0000 0000 0000 0000 0000 0000 0011`
and double `3.0` stored as                        : `0100 0000 0100 0000 0000 0000 0000 0000`

when we do something like this:
```cpp
double x{ 3 };
```

what happens here is that the integer is implicitly converted to the double `3.0` to enable the double object hold the value 3 in terms it can understand.

note that when i say `convert` i dont mean the integer literal is literally converted to a double literal `3.0` what happens the the literal is taken as input
to produce a converted version of itself and that is what is returned, its more like a copy but with edits that retains the same value in another format.

<!--NOTE: Conversions do not change the value or type being converted. Instead, a new value with the desired type is created as a result of the conversion.-->

implicit type conversion is also known as `automatic type conversion` or `coercion`. it is perform automatically by the compiler when a type is needed and the
provided type doesnt not match but can be converted.


Floating-point and integral promotion
=========================================================================
the number of bits a data-type uses is known as its width. wider uses more bits, narrower: less.

most datatypes widths are ledt for the compiler adn system architectire to decide thier sizes because they will most like agree on a width that is efficient
for them to process. for example a 32 bit processor is designed to preocess 32 bits of data effienctly and easily than any other size, this is why the `std:size_t`
data-type has a width of whatever is eaiser for your processor to process (if the size_t is used to count object in memory wouldnt it make sense to make its size
the default processing width that the architecture itself uses to count and process things?).

now in the case that we are to proocess something of narrower width (like a character of size 8bits) with a 32 (or 64) bit machine; how is this acheived?

to address this challenge c++ was inbuilt with a concpet known as `numeric pormootion`: what this does is that it takes a norrow widthed data-type and
promotes it into a wider data-type like an `int` or `double` that can be processed efficiently.

all numeric promotions are `value preserving`: meaning the the converted value will always be equal to the source value (just with a different type).
value preseving conversions are said to be `safe conversions`.

because promotions are `safe`, the compiler will use it freely when needed.

Numeric promotion categories
-----------------------------------------------
they are divided into 2: `integral promotions` and `floating point promotions`.

Floating point promotions
-----------------------------------------------
suing the float promotion rules a float can be promoted to a double when needed.
meaning that we can write a function that takes a double and call it with either a double or float.

```cpp
#include <iostream>

void printDouble(double d)
{
  std::cout << d << '\n';
}

int main()
{
  printDouble(5.0);       // no conversion needed
  printDouble(6.0f);      // float is promoted to double.
}
```

integral promotion
-----------------------------------------------
this is more complicated than floating point promotion.

1) signed char or signed short can be converted to int.
2) unsigned char, char8_t, and unsigned short can be converted to int if int can hold the entire range of the type, or unsigned int otherwise.
3) If char is signed by default, it follows the signed char conversion rules above. If it is unsigned by default, it follows the unsigned char conversion rules above.
4) bool can be converted to int, with false becoming 0 and true becoming 1.

<!--
-  NOTE: numeric promotion is the conversion of a narrower data-types to a wider data-type and still retain its exact value,
-        numeric conversion and numeric promotion are not the same.
-->


 Numeric conversions 
=========================================================================
c++ supports another type of numeric type conversion and that is `numeric conversion`

there are 5 basic types of numeric conversions:
1) Converting an integral type to any other integral type (excluding integral promotions)
2) Converting a floating point type to any other floating point type (excluding floating point promotions)
3) Converting a floating point type to any integral type
4) Converting an integral type to any floating point type
5) Converting an integral type or a floating point type to a bool


note the the differnces bectween numeric pormotion and conversion is that:
- promotion   : less wide datatype to wider datatype with no data lost.
- conversion  : conversion form one datatype to another, regardless if some data has to be lost.

Safe and potentially unsafe conversions
-----------------------------------------------
1) Value-preserving conversions are safe numeric conversions where the destination type can precisely represent all the values in the source type.
2) Reinterpretive conversions are potentially unsafe numeric conversions where the result may be outside the range of the source type.
   Signed/unsigned conversions fall into this category.

example of Reinterpretive conversion: converting signed int to unisgned:
```cpp
int main()
{
  int n1{ 5 };
  unsigned int u1{ n1 };  // okay: value is preserved.

  int n2{ -5 };
  unsigned u2{ n2 };      // problematic: this would wrap at the limit of unsigned ints and produced a larger value;
}
```

values converted using reinterpretive conversion can be converted back to their source type, resulting in the initial value (even if it overlowed and produced a value
out of the range of the source type):
```cpp
int main()
{
  int n1 = static_cast<int>(static_cast<unsigned int>(-5));  // convert -t to unigned int and then back.
  std::cout << n1 << '\n';                                   // prints -5.

  return 0;
}
```

3) Lossy conversions are potentially unsafe numeric conversions where some data may be lost during the conversion.
   this usually occurs when we try to convert a datatype to a narrowly width'ed datatype (compared to the type to be converted).


 Narrowing conversions, list initialization, and constexpr initializers 
=========================================================================
numeric conversions are potentially unsafe numeric conversions: they occure when we try to convert a dataype to another that is incapable to hold all the data
of the source value.

The following conversions are defined to be narrowing:
 1) From a floating point type to an integral type.
 2) From a floating point type to a narrower or lesser ranked floating point type, unless the value being converted is constexpr and is in range
    of the destination type (even if the destination type doesn’t have the precision to store all the significant digits of the number).
 3) From an integral to a floating point type, unless the value being converted is constexpr and whose value can be stored exactly in the destination type.
 4) From an integral type to another integral type that cannot represent all values of the original type, unless the value being converted is constexpr
    and whose value can be stored exactly in the destination type. This covers both wider to narrower integral conversions, as well as integral sign conversions
    (signed to unsigned, or vice-versa).

- If you need to perform a narrowing conversion, use static_cast to convert it into an explicit conversion.

Brace initialization disallows narrowing conversions
-----------------------------------------------
Narrowing conversion is not allowed in brace initialization: this is why its the most preferred meothod of initialization (this constraint promotes writing safer code).
if it needs to be done the `static_cast` keyword should be used to convert to the correct type.

Some constexpr conversions aren’t considered narrowing
-----------------------------------------------
this is because constepxr values are evaluated at compile time and replaces contexts that depend on that constexpr with the constexpr evaluation, which is not necessarily
type narrowing except the evaluation is a type that the destination datatype cannot fully represent. (Not even sure about this logic but this is what i understand so far)

List initialization with constexpr initializers
-----------------------------------------------
read this section.

 Arithmetic conversions 
=========================================================================
read here: [[www.learncpp.com/cpp-tutorial/arithmetic-conversions]] not worth noting down.

NOte:
- `typeid( object ).name()` return a string of the objects type. it belongs to the `<typeinfo>` header.


Signed and unsigned issues
-----------------------------------------------
if we examine this code:
```cpp
#include <iostream>
#include <typeinfo>

int main()
{
  std::cout << typeif(5u - 10).name() << ' ' << 5u - 10 << '\n';

  return 0;
}
```

the ouptut is:
`unsigned int 4294967291`

this is because due to the fact that unsigned int has a higher precedence than int the whole expression would evaluate to an unsigned int
and `5 - 10 = -5` which is a value that an undigned int cannot represent so the wraps around the limits is its data-type (unsigned int) and
returns a large number (in this case `4294967291`).

this behavour of unsigned int and signed ints in calaculations can lead to unexpected results.
and this is why we should avoid using signed and unsigned int with an operator that requires the operand to be of the same type.

Explicit type conversion (casting) and static_cast
-----------------------------------------------
Type casting: C++ supports 5 different types of casts:
1) C-style casts            (very powerful should be avoided in c++)
2) static casts             (less powerful but safe, perfoms compile-time type checking to allow valid conversions: should always be favoured)
3) const casts
4) dynamic casts
5) reinterpret casts

read this: [[www.learncpp.com/cpp-tutorial/explicit-type-conversion-casting-and-static-cast]]


 Typedefs and type aliases 
=========================================================================
in C++ the `using` keyword is what is use to create type aliases for an existing data-type:
```cpp
using Distance = double;
// once a type alias is defined it can be used wherever a type is needed:
Distance milesToDestination{ 3.4 };
```

naming type aliases
-----------------------------------------------
start them with capital letters.

Type aliases are not distinct types
-----------------------------------------------
they do not create distinct new types they only create a new idenitifier that can be used to refer to an existing datatype.

type aliases are not type safe.

The scope of a type alias
-----------------------------------------------
beacuse type aliases are hust identifiers they follow the same scoping principles with normal variable identifiers.

Typedefs
-----------------------------------------------
an older way for type aliases inherited from C

```cpp
typedef long Miles;
using Miles = long;     //both are identical
```

the `using` keyworded type alias should be favoured to use rather than `typedefs`
example:

```cpp
typedef int (*someFcn)(double, char);
using someFcn = int(*) (double, char);
// all same shiz.
```

Using type aliases for platform independent coding
-----------------------------------------------
on of the primary use is to hide platform specific details. on some platforms int is 2 bytes and some 4 bytes, so we use type aliases
to create adjusted aliases for types to enable writing plarform specific and non-dangerous code.

```cpp
#ifdef INT_2_BYTES
using int8_t    = char;
using int16_t   = int;
using int32_t   = long;
#else
using int8_t    = char;
using int16_t   = short;
using int32_t   = int;
#endif
```

in architectures that theier ints are only 2 bytes the `INT_2_BYTES` macro is defines the the compiler/preporcessor settings.

fixed width integers tyoes are just type aliases defined in some header: that why in some machines an `std::int8_t` are treated as characters.
```cpp
#include <iostream>
#include <cstdint>

int main()
{
  std::cout << std::int8_t{ 97 } << '\n';

  return 0;
}
```

this is because `int8_t` is likely a tyodef for `signed char`


Benefits of useing a type alias
-----------------------------------------------
1) Using type aliases to make complex types easier to read
2) Using type aliases to document the meaning of a value
3) Using type aliases for easier code maintenance: allowing you to change the underlying type of an object without having to update
   lots of hardcoded types


Downsides of type aliases
-----------------------------------------------
it introduces new ideniftiers that make theyr original underlying types hard to figure out. we should use type aliases judicously: when they provide
clear benefits of code readablity and maintainance.


 Type deduction for objects using the auto keyword 
=========================================================================
int this code below there is a present redundancy lurking:
```cpp
double d{ 5.0 };
```

above we defined a variable d initilailzed with the same type as its varible d.
because we want the variable and the initializer to have the same type we are providing the sametype information twice
thay is the redundancy.

Type deduction for initialized variables
-----------------------------------------------
`type deduction` ot `type infernece` is a feature that allows the compiler to deduce the type of an object from the the objects initializer's type.
to use tyoe deduction we ise the `auto` keyword.
```cpp
int main()
{
  auto a{ 5.0 };      // variable a evaluates to the type: double.
  auto b{ 1 + 6};     // evaluates to the type int.
  auto c{ 'h' };      // evaluates to the tyoe char.

  return 0;
}
```

type deducton will not work for objects with empty initializers or no initializers at all:
```cpp
auto x;             // tyoe cannot be inferred.
auto y{ };          // also cannot be inferred.
```

Type deduction drops const / constexpr qualifiers
-----------------------------------------------
```cpp
int main()
{
  const int x{ 5 };
  auto y{ x };        // initialixed the value 5 and type will be inferred as int: const qualifier dropped.
}
```

if you want if to deduce into a const ot constexpr you must supply the qualifer yourself with the auto keyword.
```cpp
int main()
{
  const x{ 5 };
  auto y{ x };              // const is dropped: inferred as type int.
  constexpr auto z{ y };    // const qualifer is dropped but since defined with constexpr: type is deduced as constexpr int.
}
```

Type deduction for string literals
-----------------------------------------------
by default they are duduced as type `(const *char)`.

if you want the auto keyworded string literal initialized object to have a type: `std::string` or `std:string_view` you'll need to impose a literal suffix.
`s` for string and `sv` string view,
```cpp
int main()
{
  auto x{ "Project 2025"s };                 // this evaualtes to the std::string type        prefix: s
  auto x{ "Project 2025 must happen"sv };    // this evaualtes to the std::string_view type   prefix: sv
}
```

with autos tyoe deduction: there are no unintended performance-impacting conversions:
```cpp
std::string_view getString();   // some function that returns a std::string_view

std::string s1 { getString() }; // bad: expensive conversion from std::string_view to std::string (assuming you didn't want this)
auto s2 { getString() };        // good: no conversion required
```

- Use type deduction for your variables, unless you need to commit to a specific type.


 Type deduction for functions 
=========================================================================
- the auto keyword in functions enable the function return the evaluated type of the return statement.
- all the return statemenst inf the function should all evaluate to the same type ot the compiler throws an error.
- aany functions that use the auto keyword must be fully defined before where they are needed in the file scope to be used (any forward declaration will not suffice):
```cpp

auto smFcn();

int main()
{
  std::cout << smFcn() << '\n';       // smFcn() call will through an error it needs to be fully defined before usage.
}

auto smFcn()
{
  return 9.0;
}
```

error message:
`error C3779: 'smFcn': a function that returns 'auto' cannot be used before it is defined.`

- Favor explicit return types over function return type deduction for normal functions.

Trailing return type syntax
-----------------------------------------------
it can be used to define function with `trailing return syntax`. where the return type is specified after te rest of the function prototype.
```cpp
auto add(int x, int y) -> int
{
  return (x, y);
}

// the above is euqivalent to writing:
int add(int x, int y)
{
  return x + y;
}
```

in this case auto does not perform any return type deduction, its just uses as a semantic style to write `trailing return syntax`

Note:
- Type deduction can’t be used for function parameter types


 Introduction to function overloading 
=========================================================================
function overloading allows to create to functions with same identifiers but with differnt parameter types in the case we want the a specific function
to work or more than one type.
Functions can be overloaded so long as each overloaded function can be differentiated by the compiler.
If an overloaded function can not be differentiated, a compile error will result.

example pf cuntion overload:
```cpp
#include <iostream>

int add(int x, int y)
{
  return x + y;
}

double add(double x, double y)
{
  return x + y;
}

int main()
{
  std::cout << add(1, 4) << '\n';           // calls int add(int, int)
  std::cout << add(7.9, 5.0) << '\n';       // calls double add(double, double) : add function also works for double types
}
```

Making it compile
-----------------------------------------------
what need to be true for a program with overloaded functio to compile:
1) Each overloaded function has to be differentiated from the others, will be discussed in-depth later.
2) Each call to an overloaded function has to resolve to an overloaded function, will be discussed in-depth later.


 Function overload differentiation 
=========================================================================
How overloaded functions are differentiated
-----------------------------------------------
| Function property    | Used for differentiation |                                            Notes                                             |
|:--------------------:|:------------------------:|:--------------------------------------------------------------------------------------------:|
| Number of parameters | yes                      |                                                                                              |
| Type of parameters   | yes                      | Excludes typedefs, type aliases, and const qualifier on value parameters. Includes ellipses. |
|     Return type      | no                       |                                                                                              |

a functions type signature or simply signature are parts of the function header that is used for differntiation of the function.

- The process of matching function calls to a specific overloaded function is called overload resolution.
- Matches made by applying numeric promotions take precedence over any matches made by applying numeric conversions.

read this shit up: [[www.learncpp.com/cpp-tutorial/function-overload-resolution-and-ambiguous-matches]]

overloaded functions in which the arguments passed into the parameters of the function call are to be numerically converted (not promoted)
to inevitably match more than one overloads will result to a compiler error due to ambiguity. note that the criteria for this condition is that
numerical conversions should be the only factor in play when resolving the overloaded function. if other factors are in play like number of parameters or so
the overloaded function might resolve successfully without throwing a compile error.

- Matches made by applying numeric promotions take precedence over any matches made by applying numeric conversions.

Resolving ambiguous matches
-----------------------------------------------
1) Often, the best way is simply to define a new overloaded function that takes parameters of exactly the type you are trying to call the function with.
2) explicitly cast the ambiguous argument(s) to match the type of the function you want to call.
3) If your argument is a literal, you can use the literal suffix to ensure your literal is interpreted as the correct type


 Deleting functions 
=========================================================================
in some cases its possible to write functions that do not behave as desired when certain values are given as arguments.

in those cases we can use the `= delete` operator to halt the program if those functions are used with those certain argumens:
```cpp
#include <iostream>

void printInt(int a)
{
  std::cout << a << '\n';
}

void printInt(char) = delete;     // call to this will halt
void printInt(bool) = delete;     // call to this will halt

int main()
{
  printInt(10);                   // okay
  printInt('a');                  // compile error
  printInt(true);                 // compile error
}
```

- Although you can delete a non-overloaded function, there typically is no reason to, as that function wouldn’t be called in the first place

<!--
-   NOTE: wasted my damn time on this useless topic.
-->


 Default arguments 
=========================================================================
- this used to give functions a default preset of paramter value or values.
- it only done with copy initialization syntax `int x = 9`, and not brace or list inititilizations (wont work)
- it should be defined in header files
- a function that has been giving defualt values cannot be redefined with new default values.
- if a parameter inf a function defination is given a default value all paramters to its right should also posses default values.
- you can declare more than one default values in a functions defination.
- functions with default values can be overloaded.

syntax:
```cpp
// normal
void add(int x, int y=9, int z=10)
{
  return x + y + z;                   // y and z default values are used when no values are giving to them with a function call
}

void sub(int x=10, int z)             // errorneous: all paramters to the right of a default values must alos have default values
{
  //divide shit
}

// header forward declarations:
#ifndef DEF_H
#define DEF_H

void mod(int a, double z=3.091);
// with this the function can be defined in another file.
#endif
```

- If the function has a forward declaration (especially one in a header file), put the default argument there. Otherwise,
  put the default argument in the function definition.

Default arguments and function overloading
-----------------------------------------------
defualt argumented functions can be overloaded:
```cpp

void doShiz(std::string s)
{
}

void doShiz(char=' ')
{
}

int main()
{
  doShiz("HELLO PICKLE RIIIIICCCKKKK!");    // called with doShiz(std::string)
  doShiz('a');                              // called with doShiz(char) uses the provided char value
  doShiz();                                 // called with doShiz(char) with its default value. equavalent to doShiz(' ');
}
```


 Function templates 
=========================================================================
function templates allow us to write functions that can be used with one than more types.
it allows us to write fuctiosnthat its type is nit known until its called.

C++ supports 3 different kinds of template parameters:
1) type template paramters (where the template paramter reoresent the type)
2) non-type template parameter (where the template parameter represntes a constexpr value)
3) template template parameters (where the template paramter represents a template)

A function template is a template used to create one or more overloaded functions. each with a different set of actual types. when we create function templates
we use placeholder types for any paramter type return type or types used in the function body.


decalraing function templates
-----------------------------------------------
in this ill be writing a function template for a max function:

1) first we covert the return tyoes and variable types of the function into the placaholder type in thus case its T:
```cpp
T max(T x, T y)
{
  return (x > y) ? x : y;
}
```

but this is just a normal function with type T, to decalre it as a template function:
1) we use the template parameter declaration with our placeholder type being `T`:
```cpp
template <typename T>                   // template parameter declaration.
T max(T x, T y)                         // function template declaration for max<T>
{
  return (x > y) ? x : y;
}
```

analyzing step 2:
1) we use the `template` kleyword telling the compiler that we are declaraing a template.
2) nextr spacify all the template parameter types in the `<>` brackets. we use the keyword `typename` or `class` followed by the placeholder type identifier (eg. `T`)
3) no differnce in using the `class` or `tyoename` keyword just a convention depending on your mileage


 Function template instantiation 
=========================================================================
Using a function template
-----------------------------------------------
function templates are not actually functions they have only one job: to generate functions (that are to be compiled)

with this function template:
```cpp
template <typename T>
T add(T x, T y)
{
  return x + y;
}
```

to use it we write:
```cpp
add<actual_type>(arg1, arg2);
```

THe process of creating function with actual types from function templates is known as: `function template instantiation`.
```cpp
max<int>(2, 1);           // this statement yields a function template instantiation of max<int>() and calls the function instance with the arguments.
```

Process of function instantiation from templates
-----------------------------------------------
initaial code:
```cpp
#include <iostream>

template <typename T>
T plusOne(T number)
{
  return number + 1;
}

int main()
{
  std::cout << plusOne<int>(30); << '\n';
  std::cout << plusOne<double>(3.9); << '\n';
  std::cout << plusOne<int>(20); << '\n';
}
```

due to the call of the function with differnet types the function templates generates functions to handle all calls in the translation unit:
```cpp
// translated unit for compilation
#include <iostream>

//------------generated instantiated functions------------!
template <typename T>
T plusOne(T number);

// int version
template <>
int plusOne<int>(int number)
{
  return number + 1;
}

// double version
template <>
double plusOne<double>(double number)
{
  return number + 1;
}
//--------end of generated instantiated functions----------!

int main()
{
  std::cout << plusOne<int>(30); << '\n';
  std::cout << plusOne<double>(3.9); << '\n';
  std::cout << plusOne<int>(20); << '\n';
}
```

so any call with to the template function will call the matching generated functions.

Template argument deduction
-----------------------------------------------
while using template functions we dont have explicitly state the type we intend to generate to use, THis is due to templates possessing a feature
known as `template argument deduction`.

so instead of calling `plusOne<int>(30)` we can just: `plusOne(30)`. this is because template function calls can deduce the type to generate for
with the arguments passed into it.

we can do any of this:
```cpp
plusOne<>(9);
plusOne(9);             // preferred.
```

Note thats is a template function is overloaded by non-template function, if theres a cal to the function without the `<>` brackets it would call the non-overloaded function.

example:
```cpp

template <typename Z>
Z returnArg(Z y)
{
  return y;
}

int returnArg(int y)
{
  return y;
}

int main()
{
  std::cout << returnArg<int>(1);     // calls genereted function instance from template/
  std::cout << returnArg<>(1);        // does the same as above (type deduced by template from argument)
  std::cout << returnArg(1);          // calls non-template overload function.
}
```

Function templates with non-template parameters
-----------------------------------------------
template function ncan take both template paramters and non template parameters.
example:
```cpp
template <typename Z>
Z someFcn(Z, double)
{
  return 5;
}
```

Instantiated functions may not always compile
-----------------------------------------------
if an instatiated function spawned from a template function is used with the wrong paraamter types or used in ways that its doesnt make sense semantically
it would likely not compile or lead to UB.

consider this code
```cpp
#include <iostream>

template <typename X>
X plusOne(X y)
{
  return y + 1;
}

int main()
{
  std::cout << plusOne(9) << '\n';
  std::cout << plusOnes(s"Hello fucks") << '\n';
}
```

its quite obvious that the function template should only be semantically correct for paramters that allow arithemetic operations on them like addition.
but on the second statement in the main function block, we used the template function to generate an instance that "should" work with type `std::string`
but it wont because you cant add numbers to a string types.

the above template function will evaluate to this (for the string function call) in its translation unit:
```cpp
template <typename X>
X plusOne(X y);

template <>
std::string plusOne<std::string>(std::string y)
{
  return y + 1;                                       // y is a string and cannot perform numeric addition so compile error.
}
```

Using function templates in multiple files
-----------------------------------------------
function templates cannot be used in another file as lone as they files translation unit cannot see the full declaration of the function template.
THis can be resolved by defining the function template in header files and including them where needed.

remember that template functions are not normal functions (they technically arent even functions) that posses extrenal linkage and can be accesed wherever
just with simple forward declaration.

forward declaration will not suffice for function templates.

function templates arent fuunctions. They are templates that functions are spawned from.

```cpp

// add.h
#ifndef ADD_H
#define ADD_H

template <typename T>
T addOne(T x)
{
  return x + 1;
}

// main.cpp
#include "add.h"

int main()
{
  addOne(7);
  return 0;
}
#endif
```

why function templates do not violate ODR
-----------------------------------------------
fucntion templates generate function instances in file scopes they are included in and called into. but they fo not violate ODR because the generated
instances for the translation unit of every file scope they were called and needed in are all inline.

so they all refer to one defination as inline objects do. Making it full proof from the One Defination Rule (ODR).


 Non-type template parameters 
=========================================================================
a non type template parameter are template parameters with a fixed type that serves as a placeholder for a constexpr value passed in as a template argument.

a non type template parameter can be any of the following types:
1) an integral type
2) an enumeration type
3) std::nullptr_t
4) a floating point type
5) a pointer or reference to an object
6) a pointer or reference to a function
7) a pointer or refernce to a member function
8) a literal class type.

an example of non-type template can be seen with the `std::bitset` object. we use a non-type template to specify how many bits we want to store.


Defining our own non-type template parameters
-----------------------------------------------
heres an example of a function that uses a non type template paramter:
```cpp
#include <iostream>

template <int N>
void print()
{
  std::cout << N << '\n';
}

int main()
{
  print<5>();               // this would print 5 on a newline.
}
```

when the compiler sees the call to the print function that uses the non type template paramter, we a function that should look like this will be instantiated:
```cpp
template <>
void print<5>()
{
  std::cout << 5 << '\n';
}
```

conventions:
- just as `T` is used as the name for type template parameters use `N` as the name for non-type parameters.

What are non-type template parameters useful for?
-----------------------------------------------
As of c++20 function parameters cannot be constexpr. this is true for normal function too.

non-type template functiion can be used to sneakishly place constexpr values as arguments in functions. so they can be used in contexts that require constant expressions.

for example examining the function below:
```cpp
#include <cassert>
#include <cmath>
#include <iostream>

double getSqrt(double d)
{
  assert(d >= 0 && "this function must be used to a positive number");

  return std::sqrt(d);
}

int main()
{
  std::cout << getSqrt(5.0) << '\n';
  std::cout << getSqrt(-5.0) << '\n';
}
```

the above code the function call with the `-5` argument will be asserted an runtime and the program will be halted, which is okay
but what of cases that we need the function to assert at compile-time and halt if the argument passed in does not meet our expectations?
we could use the `static_assert()` function that asserts at compile time but the issue with this is that it needs to be used with a constexpr value
and in a constant context which normal function parameters cannot satisfy.

this is where non-type template functions comes in: because they are designed to take in constexpr values we can use the `static_assert()` function
to assert in compile time which will happen as the template function makes a new instance of itselfs to be used (at comile time mind you)
and due to the fact that `static_assert()` evaluates at compile time it will assert the constexpr value passed into it and halt the compilation
if it does not meet the requirements.

so we can do this to allow compile time assertion:
```cpp
#include <iostream>
#include <cmath>

template <double N>
double getSqrt()
{
  static_assert(N >= 0 && "This function only takes in positive inputs");

  return std::sqrt(N);        // strangely, std::sqrt isn't a constexpr function (until C++26)
}
```

which would evaluate to this in its translation unit and halt at compile time because it asserts to false:
```cpp
template <>
double getSqrt<-5>()
{
  static_assert(-5 >= 0 && "This function only takes in positive inputs");  // evalutes to false and throws compile error

  return std::sqrt(-5);                                                     // does not compile.
}
```

NOte:
- non-type template paramters implicitlty convert arguments types (when neceassery and if possible) in order to work:
  this is done either by:
  1) integral promoton
  2) intgeral conversions
  3) user defined functions (in a class or something)
  4) and so on.

Type deduction for non-type template parameters using auto
-----------------------------------------------
as of C++17, non-type template parameters may use auto to have the compiler deduce the non-type template parameter from the template argument:
```cpp
#include <iostream>

template <auto N>
void print()
{
  std::cout << N << '\n';
}
```

 EEENNNNNNNNNNNNNNNNNNNNNNNNNDD! 
=========================================================================

