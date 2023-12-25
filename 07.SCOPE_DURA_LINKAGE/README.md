 Scope, Duration, and Linkage 
 Felix Okoronkwo Nov 6, 2023 

 Compound statements (blocks) 
===============================
- A compound statement (also known as a block or block statement), is a group of zero or more statements that the compiler
  treats as if a single statement.
- blocks can be nested
- blocks are used to execute multiple statements conditionally, this is usually accomplished with `if statements`
- The C++ standard says that C++ compilers should support 256 levels of nesting (what the fuck!?)

 User-defined namespaces and the scope resolution operator 
============================================================
Beacuse the identifiers of objects can potentially collide with similar identifiers in the same scope, this leads to a
linear increase in identifiers and an exponential increase in naming collisions, this is why namespaces are important.
Because they solve this problem.

Defining your own namespaces
----------------------------
namsepaces created by we the developer are known as `user-defined namespaces` and they are accomplished with the `namespace` keyword.

```cpp
namespace Namespaceidentifier
{
  // content of namespace here.
}
```

- Historically namespaces are not capitalized. but its recommended to start namsepaces identifiers with capital letters.
- Namespaces are can be either defined inside the global scope or inside another namespace.

```cpp
  namespace Foo
  {
    int print_and_return_20()
    {
      std::cout << "This would return 20, v1.0";
      return 20;
    }
  }

  namespace Goo
  {
    int print_and_return_20()
    {
      std::cout << "This would return 20, v2.0";
      return 20;
    }
  }

  int main()
  {
    constexpr twenty { Goo:print_and_return_20() };
  }
```

Accessing a namespace with the scope resolution operator (::)
-------------------------------------------------------------
- The scope resoltion operator allows us to explicitly select what namespace wo want to access an object or function from
- when the scope operator is used with no namespace identifier, the global namespace is used.

```cpp
#include <iostream>

void print()
{
  std::cout << "this is from the global namespace" << '\n';
}

namespace Foo
{
  void print()
  {
    std::cout << "this is from the Foo namespace" << '\n';
  }
}

int main()
{
  ::print();            // this would call print from the global namespace.
  Foo:print();          // this would call print from the Foo namespace.
}
```

Identifier resolution from within a namespace
---------------------------------------------
if an identifer inside a namespace is used and no scope was declared: the namespace would first search for the identifier
within itself, if not found, it searches the namespace it is contained in (usually the global namespace).

Example:

```cpp
#include <iostream>

void print()
{
  std::cout << "There" << '\n';
}

namespace Foo
{
  void print()
  {
    std::cout << "Hello ";
  }

  void print_hellothere()
  {
    print();                          // Foo:print() is called
    ::print();                        // global scope print() is called.
  }
}

int main()
{
  Foo:print_hellothere();
}
```

Forward declaration of content in namespaces
--------------------------------------------
- for function identifers inside a namespace, their forward declaration also, needs to be included in that namespace.

add.h
```cpp
#ifndef ADD_H
#define ADD_H

namespace BasicMath
{
  int add(int x, int y);            // forward declaration of add function
  constexpr double gravity { 9.8 };
}

#endif
```

add.cpp
```cpp
#include "add.h"

namespace BasicMath
{
  int add(int x, int y)             // define function add inside namespace BasicMath
  {
    return x + y;
  }
}
```

main.cpp
```cpp
#include "add.h"
#include <iostream>

int main()
{
  std::cout << BasicMath::add(7, 8) } << '\n';
  std::cout << "Gravity is " << BasicMath::gravity << '\n';
  return 0;
}
```

- extra identifiers can be added to a namespace with subsequent declarations.

Multiple namespace blocks are allowed
-------------------------------------
its legal to declare multilpe namespace blocks (wether across multiple files or multiple locations within the same file).
All declaration within the namespace are considered part of the namespace.

```python
#  WARN: DO NOT ADD FUNCTIONALITY TO THE std NAMESPACE.
```

Nested namespaces and aliases
-----------------------------
namespaces can be nested inside other namespaces and can be aliased, For example:

```cpp
#include <iostream>

namespace Foo
{
  namespace Goo
  {
    int add(int x, int y)
    {
      return x + y;
    }
  }
}

int main()
{
  namespace AddShit = Foo::Goo;
  std::cout << AddShit(5, 6) << '\n';
}
```

namespaces cam also be nested with this syntax:
```cpp
  namespace Foo::Goo    // this is a namespace inside the Foo namespace (c++17 style)
  {
    // content here.
  }
```

- namespace alisase allows us shorten long (possible nested) namespace syyntaxes ino shorter identifers.
- and namespace aliasea allows us to easilt pint an identfer to a different namespace for a required functionality
  (usually the namespace identifers migrated to and from, working with the identifier is a hassle because of its lengthy nature.)

When you should use namespaces
------------------------------
- When you write a library or code that you want to distribute to others, always place your code inside a namespace.
- In applications, namespaces can be used to separate application-specific code from code that might be reusable later


Local variables
================
nothing much here, they are block scope limited and have no linkage, meaning they must be unique in any scope they
are spawned into.


 Global Variables 
===================
They are declared outside function bodies.

- Globale varibales have `file scope`, meaning they can be used wny where in the file they are declared and goes out of scope
  at the end of the file

Global variables have static duration
-------------------------------------
they are created when the program start and are destroyed when the program ends, this is known as *static Duration*

Naming Global variables
-----------------------
By convention some developers prefix non const global variables with "g" or "g_" to declare that they are global.

Global variable initialization
------------------------------
unlike local varables which are unitialized by default, statc variables (like global variables) are zero initialized by default.

Constant global variables
-------------------------
Just like local varables, global variables can be constant. As with all constants global varables must be initilazed.

```cpp
#include <iostream>

// this is the global scope.

const g_x;                // error: const variables must be initialized
constexpr g_y;            // error: constexpr vars. must be initialized.

const g_z { 1 };          // valid
constexpr g_w { 2 };      // valid
```

- the use of non-constant global variables should be avoided.


 Variable shadowing (name hiding) 
===================================
Read that shit yourself: [[www.learncpp.com/cpp-tutorial/variable-shadowing-name-hiding]]

NOTE:
- computations would always prefer to associate with variables in their scope even if such variables share the same identifier
  with another objects out of thier scope (maybe global scope).
- the above is done through name hiding and it should be generally avoided.

```python
# WARN: FOR GCC, G++ USERS (like myself :3)
# GCC and Clang support the flag -Wshadow that will generate warnings if a variable is shadowed.
# There are several subvariants of this flag (-Wshadow=global, -Wshadow=local, and -Wshadow=compatible-local)
```


 Internal linkage 
===================
Global functions and function identifiers can either have internal or external linkages.
Internal linkages would be discuseed in this section.

An identifier with an internal linkafge can be seen and used in a single translation unit. an its not accessible
by other translation units because it has no linkage (not exposed to the linker).

Global variables with internal linkage
--------------------------------------
const and constexpr variables implicitly posess internal linkage. but that no the case for non-cont global variables.
to make a non-const global variables internally linked, the `static` keyword is used.

```cpp
#include <iostream>

static int g_x {};        // changed from external linkage to internal by the static keyword.
const int g_y {};         // constant globals have internal linkage be defaulr
constexpr int g_z {};     // constant gloabls have internal linkage by default.

int main()
{
  std::cout << g_x << ' ' << g_y << ' ' << g_z << '\n';
  return 0;
}

```

- the use of `static` is an example of a `storage class specifier`. which sets teh linkage and storage duration of an identifier.
  commoonly used specifiers include are `static`, `extern` and `mutable`.

Functions with internal linkage
-------------------------------
Beacuse linkage is a property of identifiers not variables, function identifiers also posess linkage property.
Function by defalut posess `external linkage`. and can be set to `internal linkage` using the `static` keyword.

Example:

```cpp: add.cpp
[[maybe_unused]] static int add(int x, int y)
{
  return x + y;
}
```


```cpp: main.cpp
#include <iostream>

static int add(int x, int y);   // forward declaration of add function

int main()
{
  std::cout << "7 + 6 is " << add(7, 7) << '\n';
  return 0;
}
```

The above program wont work becasue the add function has internal linkage that goes out of scope at the end of its file.
so it wont even link because add function is not accessible outside the `add.cpp`.

Things to note:
- despite the One Defination Rule, objects sharing the same identifers with internal linkages in different files, are independent
  of each other and do not violate the ODR.
- in modern c++ the static keyword is falling out of favour for granting internal linkages, the `unamed namespaces`, also does
  this with extra functionalities, like granting a wider type of identifiers internal linkage (type identifiers), they are better
  suited for giving internal linkages than static keywords and would be discussed later.

Why bother giving identifiers internal linkage?
-----------------------------------------------
reeeeadd bitch: [[www.learncpp.com/cpp-tutorial/internal-linkage]]
check the section in the link with the same name as this section.


 External linkage and variable forward declarations 
=====================================================
An identifer with external linkage can be seen and used both in the file where it was declared and in other code files,
via forward declaration. identifers with external linkages are truly global and can be used anywhere in a program.

Functions have external linkage by default
------------------------------------------
In order to call a function decfined in another file you must place a `forward declaration` for the function in the file
you wish to call the function. the forward declaration tells the compiler about the existence of the function so the linker
can link and execute the function with subsequent calls of the function in the file.

if the function to be called, which resides in another file, was internally linked: the linker wont be able to link the function
definations when the function is called and this would result to a linker error.

Global variabes with external linkage
-------------------------------------
Non-const global variables are externally linked by default (meaning they are external adn can be used any where in the codebase),
but const global variabla are not and can be made external using the `extern` keyword.

```cpp
int g_x { 2 };                    // non-constant variables are external by default, compiler: using extern on them? ignored.

extern const int g_y { 3 };       // extern makes const globals external
extern constexpr int g_z { 7 };   // extern makes constexpr globals external. this is uselss tho, would be explained later.
```

Variable forward declarations via the extern keyword
----------------------------------------------------
To actually use an external global variable defined in another file, a forward declaration must be declared
(just like with functions). for vairables forward declaraion is done `using the extern keyword with no initialization value`.

EXAMPLE
```cpp a.cpp:
int g_x { 4 };
extern const int g_y { 7 };
```

```cpp main.cpp:
#include <iostream>

extern int g_x;               // forward declaration of g_x defined in a.cpp
extern const int g_y;         // forward declaration of g_y defined in a.cpp

int main()
{
  std::cout << g_x << ' ' << g_y << '\n';
  return 0;
}
```

this shows that the extern keyword has differnt meaning in different context, it can be use to make a const global variable
externally linked and it can also serve as a forward delcaration for externally linked defined in another file const and non-const
variables.

<!--
  1)  WARN: If you want to define an uninitialized non-const global variable, do not use the extern keyword,
      otherwise C++ will think you’re trying to make a forward declaration for the variable.
  2)  WARN: Although constexpr variables can be given external linkage via the extern keyword, they can not be forward declared,
      so there is no value in giving them external linkage.
-->

Function dont need the `extern` keyword for forward declaration, but variables do need them to differentiate from declared varibales
with no initilization values.

```cpp
// non contant
int g_x;                  // non-cont externally linked global (zero initialized)
extern int g_x;           // forward declaration (uses the extern keyword with no init'zer)

//contant
extern const g_y { 7 };   // const externally linked global (must be initialized with extern).
extern const g_y;         // forward declaration (not initialized with extern).
```

<!--
    NOTE: Global variables can have either internal or external linkage, via the static and extern keywords respectively.
-->


 Why (non-const) global variables are evil 
============================================
read: [[/www.learncpp.com/cpp-tutorial/why-non-const-global-variables-are-evil]]

- Use local variables instead of global variables whenever possible.
- and avoid non-const global variables.
- Dynamic initialization of global variables causes a lot of problems in C++. Avoid dynamic initialization
  whenever possible.

So what are very good reasons to use non-const global variables?
----------------------------------------------------------------
read the section: [[www.learncpp.com/cpp-tutorial/why-non-const-global-variables-are-evil]]

Protecting yourself from global destruction
-------------------------------------------
read the section: [[www.learncpp.com/cpp-tutorial/why-non-const-global-variables-are-evil]]

non const variables are dangerous because they can be cahnaged any where in the program without the developer  being aware
therefore possibly leading to unprecedented execution.

and it can make debugging frustrating: imagine a situation where a global non-const variable is altered by numerous functions
and a bug was sprung forth due to the variable, debugging would be terryfying especially if the non-cont global variable is now
(God forbid this) externally linked.

Global variables also make program less modular and flexible. most modular function are function in which all data needed by that
to run is passed into te function as arguments. dependency on a standalone function that isnot passed into the function (like a
global varable) makes the function less modular.

example: in this function gravity was made a global function and was uilized in a function
```cpp
#include <cmath>

constexpr double gravity { 9.8 };

int maxVHeight(double initV)
{
  return std::pow(initV, 2) / (gravity * 2);
}
```

in the above sceneario this function is only accurate for motion on our planet earth, what about jupiter? or any other
wacky planet or scenario where it's a fact that the gravitational accelaration will not be 9.8 ? monolithism.

To fix ths and make the function more modular we can make the gravity to be a passed in as an argument to the function.

```cpp
#include <cmath>
#include <iostream>

constexpr double maxVHeight(double initV, double gravity)
{
  return std::pow(initV, 2) / (gravity * 2);
}

int main()
{
  constexpr int initV { 15 };
  constexpr double maxHeightMoon { maxVHeight(initV, 1.625) };
  constexpr double maxHeightEarth { maxVHeight(initV, 9.8) };

  std::cout << "The maximum height of a ball thrown in the moon at an initial velocity of 15m/s is " << maxHeightMoon << "m \n";
  std::cout << "While that of the earth is " << maxHeightEarth << "m \n";
}
```

the above aproach is more modular and reusable, because we can calculate the same propertie for any planet just bt passing in its
gravitaional acceleration constant.

Best Practices
--------------
1) instead of this :
```cpp
constexpr double gravity { 9.8 };

int main()
{
  // do stuff
}

```

do this:

```cpp
namespace constants
{
  constexpr double gravity { 9.8 };
}

int main()
{
  // do stuff
}

```

2) instead of allowing direct access externally to the global variable, its better to encapsulate it in such a way that the
   variable is onky accessible in its file scope, and provde a helper functon to access the variable when needed, since function by
   default are externlly linked.

```cpp: so instead of this:
namespace constants
{
  extern const double gravity{ 9.8 };
}
```

```cpp: do this:
namespace constants
{
  const double gravity{ 9.8 };              // has internal linkage
}

double getGravity()                            // has external linkage and acts as an access function.
{
  return constants::gravity;
}
```

3) third scenario was highlighted in the [[Protecting yourself from global destruction]] section, where it was also handled.


 Sharing global constants across multiple files (using inline variables) 
==========================================================================
Global constants as internal variables
--------------------------------------
inside a header file create a header file in the header file, create an namespace and include the constants  in the namespace,
make sure te varibles are `constexpr`.

```cpp: constants.h
#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace constants
{
  constexpr double pi { 3.14159 };
  constexpr double avogadro { 6.0221413e23 };
  constexpr double myGravity { 9.2 };           // gravity is lighter in this planet

  // then where needed include this and use
}
#endif
```

due tto the fact that constexpr variables are internally linked, each file scope that this header file is included into gets unique copies
of the constants that do not depend on eachother dure to no linkage.

Global constants as external variables
--------------------------------------
While the above approach is simple, it offers an issue, due to all the constants being independennt of each other (beacuse internally linked)
and are duplicated with every header include to be used only in thier file scope, ths leads to a lot of duplication of
constant objects that hold the same value. which can lead to lengthy build times if to be recompiled for some value change and if the
constants are large in size and cant be optimized, this utilizes a lot of memory.

the solution to thsis is convertng the variables to external variables with thier forward declaration. like so:

```cpp constants.cpp:
#include "constants.h"

namespace constants
{
  // the actual external global variables
  extern const double pi { 3.14159 };
  extern const double avogadro { 6.0221413e23 };
  extern const double myGravity { 9.2 };
}
```

```cpp constants.h:
#ifndef CONST_H
#define CONST_H

namespace constants
{
  // thier forward declarations
  extern const double pi;
  extern const double avagadro;
  extern const double myGravity;
}

#endif
```

then to use in code:

```cpp
#include <constants.h>
#include <iostream>

int main()
{
  std::cout << "Circumference of a 3cm radius circle is " << constants:pi * 3 * 2 << "cm \n";
  return 0;
}

```

However there are a couple of downsides to this approach: Firstly, the comple-time constants are only regarded as compile time constants
in the file they are defined in (constants.cpp), in other files whats seen is their forwarard declarations which are resolved by the linker
at run-time to execute the function, so in the file they are defined the operate as compile time variables but in other files they are
runtime and  because of this they cannot be used in another file where compile-time variable is needed, like in `constexprs`.

Global constants as inline variables C++17
------------------------------------------
The inline variables solves the problems of the above fore-mention approaches. since the term inline has evolved in c++ to mean
"multiple defination are allowed", but doesnt violate the ODR rule, becuase inlines operates as a substitution paradigm in c++.

the linker consolidates all inline defination into a single variable defination, meaning even if you have 20 inline variables with the
same definations the linker only picks one as the canonical variable, allowing you to define the variable 20 times but saving you 19
objects worth of memory of the other definations because they all refer to that one canonical object in memory.

inline variables primarily have 2 restrictions:
1) all defination must be the same (or else UB)
2) the inline variable defination (not the forward declaration) must be present in any file that uses the variable.

```cpp: constants.h
#ifndef CONST_H
#define CONST_H

namespace constants
{
  inline constexpr double pi{ 3.14 };         // inline constexpr: can be use in constexpr contexts.
  inline constexpr double avagadro{ 6.0221413e23 };
  inline constexpr double myGravity{ 9.2 };
}

#endif
```

we can include the header in whatever file we might need them in but this varibale would be instantiated once and shared across all files.

<!--
    NOTE: BEST PRACTICE:
    If you need global constants and your compiler is C++17 capable, prefer defining inline constexpr global variables in a header file.
-->


 Static local variables 
=========================
The `static` keyword on a local variable is used to change the variables duration from `automatic` to `static`: therefore the variable
exists throughout the programs lifespan adn is destroyes at the end of the program.

and the implication of this is such variables will still retain their value even after going out of scope but will not be accessible until
in scope again.

application of static local varibales:
```cpp
#include <iostream>

void incrementAndPrint()
{
  static int s_value{ 1 };  // converted from automatic duration to static.
  ++s_value;
  std::cout << s_value << '\n';
} // unlike other non-static local variables s_value is not destroyed here, but becomes inaccessible as it goes out of scope.

int main()
{
  incrementAndPrint();
  incrementAndPrint();
  incrementAndPrint();
  incrementAndPrint();
}

```

- Static local variables that have no initializer or a non-constexpr initializer are zero-initialized at program start
- Just like we use “g_” to prefix global variables, it’s common to use “s_” to prefix static (static duration) local variables.
- Avoid static local variables unless the variable never needs to be reset.

 Using declarations and using directives 
==========================================
A qualified name is a name that includes an associated scope
An unqualified name is a name that does not include a scoping qualifier

Using-declarations
------------------
the using declaration alows us to use an unqualified name(with no scope) as an alias to a qualified name.
it helps to reduce repitition in code of the namespace scope an object belongs to, when trying to access the object.

```cpp
#include <iostream>

int main()
{
  using std::cout;
  cout << "Hello Incels\n";    // `std:` is not needed.
}
```

- Although this method is less explicit than using the std:: prefix, it’s generally considered safe and acceptable
  (when used inside a function).

Using-directives
----------------
a using directive imports all names from a namespace into the scope the using directive was declared.
```cpp
#include <ipstream>

int main()
{
  using namespace std;

  cout << "Hello red poeple\n"; // unqualified identfier cout now epresents std::cout since declaring the using directive on std
  return 0;
}
```

Problems with using-directives (a.k.a. why you should avoid “using namespace std;”)
-----------------------------------------------------------------------------------
due to the fact that using directives import all names from a namespace including names youll likely nevver use, the
probabilty of a naming collison occuring skyrockets (especially if you import the std namespace).

when this naming collison occurs due to imported namespaces names clashing with user-defined variables name or even other imported namespaces
names, an `ambiguity error` arises.

Note that when the compiler executes function calls if there are multiple declaration of that function with the same identifer in the same scope the compiler
picks the best fit (likely one that the call to that functon does not need type convrsions to pass the arguments into the functions parameters and other
optimization tasks like that), especially if one of the functions belong to some namespace and was imported into te calling scope. This behaviour can
(sometimes) lead to unexpected results.

exmaple:
```cpp foolib.h: this is some librarys header
#ifndef FOOLIB_H
#define FOOLIB_H

namespace foo
{
  int someFcn(int)
  {
    return 3;
  }
}

#endif
```

```cpp: main.cpp:
#include <fooblib.h>  // imported with angled brackets because its a third party library

int someFcn(double)
{
  return 1:
}

int main()
{
  using namespace foo;
  double return_1 { someFcn(0) };  // note we are using an int literal as an argument instead of a double (0.0)
}
```

Now in this code the developer might be exoecting the `someFcn()` function call to return 1 as defined in his own userdeined function but it doesnt.
this is because after using and importing the names in the `foo` namespace a naming collison occured and note that the `someFcn` declaration in foo
allows an int to be taken as an argument unlike the userdefind one that takes a double (which would lead to type conversion), the compiler notices this
and picks the best fit function for the function call, which in this case is the version from the third party library.

This little experiment shows that the compiler picks the best fit function for a call if there are more than one declared functions with clashing
identifers. THis could be easily avoided though by calling the `someFcn` using its qualified name with its namespace scope and scope operator, explicitly.

calling it with:
```cpp
  foo:someFcn();  // third library version
  someFcn();      // user defined version
```

would have pinpointed which function we wanted to call.

- Finally, the lack of explicit scope prefixes make it harder for a reader to tell what functions are part of a library and what’s part of your program.

The scope of using-declarations and using-directives
----------------------------------------------------
they are blocked scoped, its imported names exist in the scope of the block they are called and expired as we leave that block.

Cancelling or replacing a using-statement
-----------------------------------------
one definde cant be canclelled or replaced but its scipe can be limited with blocks.

```cpp
int main()
{
  {
    using namespace foo;
    // call foo stuff here
  } // foo goes out of scope here

  {
    using namespace goo;
    // calls goo stuff here
  } // goo goes out of scope here

  //  normal scope without any of goos or foos names imported but objects residing here likely altered by computations that occured
  //  in foo and goos block.
}
```

Of course, all of this headache can be avoided by explicitly using the scope resolution operator (::) in the first place.

- Prefer explicit namespaces over using-statements. Avoid using-directives whenever possible. Using-declarations are okay to use inside blocks.

Unnamed and inline namespaces
-----------------------------
unamed namespaces or anonymous namespaces are namespaces declared without a name, they are use to grant identifiers internal linkage,
just like he static keyword, and can be called without the scope operator.

```cpp
#include <iostream>

namespace
{
  void doSomething()
  {
    std::cout << "something is being done\n";
  }
}

int main()
{
  doSomething();
}
```

it is usually used when we have alot of identifiers we want internally linked. instead of using the static keywords numerously.
unamed namespaces are accessible from their parent scope.

Inline namespaces
-----------------
inline namespaces are usually for version controlling and adding new functionality without affecting backwards compatibility by
making old functions obselete (by reformatting them). They dont affect linkage.

```cpp
#include <iostream>

inline namespace V1
{
  void doSomething()
  {
    std::cout << "V1\n";
  }
}

namespace V2
{
  void doSomething()
  {
    std::cout << "V2\n";
  }
}

int main()
{
  V1::doSomething(); // calls the V1 version of doSomething()
  V2::doSomething(); // calls the V2 version of doSomething()

  doSomething();     // calls the inline version of doSomething() (which is V1)

  return 0;
}
```

now if this was an exisiting program functionlities that depended on the V1 can still be acessed without any issues, and newer functionality
can be added byt useing the V2 namespace, because V1 was made inline any call to the `doSomething()` function would refer to V1 even without
explicitly stating the namespace scope it belongs to.

inline namespaces add a sort of version controlling to c++, allowing backward compatibility to legacy codebase and adding new functionlities
which can share the same identifier with identifiers in the legacy codebase  (had the same functionality but not updated) but act independently.

the namespace marlked inlinr wpuld be the default namespace referred to when the scope operator is not used.

Mixing inline and unnamed namespaces 
-------------------------------------
either by nesting or full-out conjoined declaration: they are used to grant both internal linkage and version controlling.

