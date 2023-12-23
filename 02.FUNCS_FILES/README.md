Functions and Files in Cpp,
Felix Okoronkwo | 10/10/23

Introduction to functions
=========================
A function is a reusable sequence of statements designed to accomplish a task.

syntax of basic function in cpp:
```cpp
  returnType functionName()
  {
    //statemants go here
    return returnType
  }
```

Basic Function usage code snippet
---------------------------------
```cpp
  int returnNumberDoubled (int num)
  {
    return (num * 2);
  }

  int main ()
  {
    int num {};
    std::cout << "Input Number: " << "\n";
    std::cin >> num;
    int num = returnNumberDoubled( num );
    std::cout << "Double is " << num << "\n";
    return 0;
  }
```

Note
----
- `main()` function will implicitly return 0 if no return value was declared even though
  its structure clearly should return a value
- `main()` function only return `int`, doesnt even allow void like C
- void functions do not need return statements.
- void function cannot be used where a value is needed.
- when a function is called the values is copied into the parameters using copy initialization
  and the parameters are created and utilized just as variables

Intro to Local Scope
--------------------
- variables defined inside a function c=bogy are callaed local variables
- Function paramaters are also local vairables

Why Use Functions
-----------------
Functions are important for some reasons, it helps develop modular, DRY and resusable code

Reasons why functions are important:
- Organization
- Reusability
- Testing
- Extensibility
- Abstraction

Forward Declaration
===================
This is the process of telling the compiler that a function already exist before
imlementing the function itself

```cpp

  int add(int a, int b);

  int main()
  {
    int sum { add(4, 5) };
    std::cout << sum << std::endl;
    return 0;
  }

  int add (int a, int b)
  { return a + b; }

```

Why Forward Declaration
------------------------
- it tells the compiler the existene of a function that may exist in another file in which
  reordering is not possible
- it helps to define functions in order-agnostic manners, maximizing code organization.
- it resolves circular dependencies: like 2 functions that both depend on each other in
  the code file, one must com before the order logically, forward declaration resolves a ny issues of function identifier not found.

One Defination Rule (ODR)
-------------------------
- Within a given file,  Objects functions and variables can should only have one defination
- Within a given program,  Objects functions and variables can should only have one defination
- Types, templates, inline functions, and inline variables are allowed to have identical definitions in different files.

Naming collisions and an introduction to namespaces
---------------------------------------------------

Naming Collision occur when:
- 2 or more functiosn or global variables occur in different files, This resolves to linking error when linking occurs.
- 2 or more identically named functions or global variables are introduced in the same file, a compiler error is thrown.

What is a namespace
-------------------
A namespace is a region that allows you to declare names into it for the purpose of disambiguation

Note:
- a name declare into a namespace whont be ambiguated with another name declared in another scope
- within a namespacse all names must be unique to prevent naming collisions
- Namespaces are used to group related identifiers in a larger project to prevent name collisons
  with other identifiers

Global Namespaces
-----------------

In c++ any variables not declared in a class, function or namespace is said to be part of an
implicitlty defined namespace known as the globale namespac or global scope.

Note:
- only declaration and defination exixt in the global namespace, this should be avoided
- meaning other statements like for instance, conditional expressions or executable statements
  cannot be placed in the global namespace.

std Namespace
-------------
namespaces can be used in 2 ways:

* explicity:
```cpp
  #include <iostream>

  int main(){
    std::cout << "explicit namespace"; // cout is used with the std namespace
  }
```

* implicitly stating to use a namespace:
```cpp
  #include <iostream>

  using namespace std;                 // this implicity tells the compiler to use this namespace

  int main()
  {
    cout << "implicit namespace";      // no need to use the `::` symbol
  }
```

using directive
---------------
In implicit namespace usage the `using directive` statemnet is used to declare the namsepace
to be used.
It allows us to access namespaces without their namespace prefix and the `scope resolution symbol`,

Note:
- implicit namespace declaration is not advised due to naming collisions that can occur when
  accessing a variable, object or function with is original identifier directly without a
  namespace
- avoid using `using-directives` at the top of your code or in header files, it violates the
  whole reason why namespaces were added in the first place.

Introduction to the Pre-Processor
=================================
The preprocessing is the first stage of all stages that leads to an executable after writing
a program

stages of code compilation:
- preprocessing
- compiling
- assembling
- linkage
- executable

What the preprocessor does:
- strips all comments from the code file
- ensures each code files end with a new line
- processes preprocessor directives (`#include`, macros, `#ifndef`, etc.)
- converts code files to a `translation unit`, which is what is fed to the compiler for
  compilation.

Translation
-----------
Preprocessing, compiling and linking all together is known as translation.

Preprocessor Directive
----------------------
When the preprocessor scans through a source code, it usually scan top to bottom looking for
preprocessor directives

Preprocessor Directives are just instructions that start with the `#` symbol and end with a new-line
it tells the preprocessor to perform some text manipulation to the source code

Keep in mind that the preprocessor does not undertand c++ syntax, preprocessors use their own syntax
for text manipulation and preprocessing tasks. which *SOMETIMES* resemble c++ syntax.

Common preprocessor directives in cpp
-------------------------------------
- `#include`: used to include the contents of a file in another code, it is used to add dependencies to
  cpp code files.
- `#define`: it used to create macros, macros are rules that define how input text is converted to
  replacement output text.


Macros
------
ways to create macros:
1. Object-like macros with substitution text:
```cpp
  #define MY_NAME "Felix"

  int main()
  {
    std::cout << MY_NAME << "\n";         // the MY_NAME macro is replaced with "Felix"
  }
```

2. Object-like macros without substitution text:
```cpp
  #define NOTHING

  int main()
  {
    std::cout << NOTHING << "\n";          // the NOTHING macro is replaced with nothing
  }
```

3. Conditional compilation: conditional compilation macros allows you to define under what circumstances
  what should and should not compile.
```cpp
  #include <iostream>

  #define PRINT_MOM

  int main()
  {
  #ifdef PRINT_MOM
    std::cout << PRINT_MOM << "\n";        // this will compile because PRINT_MOM is defined.
  #endif

  #ifdef PRINT_DAD
    std::cout << PRINT_DAD << "\n";        // this will not compile because PRINT_DAD is not defined.
  #endif

  #ifndef PRINT_ME
    std::cout << PRINT_ME << "\n";         // this will compile because PRINT_ME is not defined.
  #endif

  #if 0
    std::cout << "Bob\n";                  // nothing in the if 0 block compiles.
    std::cout << "Steve\n";
  #endif

  #if 1
    std::cout << "Steve\n";                // the if 1 macro block always compile
  #endif

  return 0;
  }
```

Note:
- Object luke macros do not affect other preprocessor directives they only do code substitution
  for normal code.
- Macros and preprocessor directives have no concept of scope.

Header Files
============
Header files allow us to put declarations in one location and then import them wherever we need them.
This can save a lot of typing in multi-file programs.

header guards
-------------
there are two convetinonal ways of header guarding

1. traditional method: responsibility of gaurding is left for the develper to handle
```cpp
  // this is a header file
  #ifndef HEADER_NAME
  #define HEADER_NAME

  // header contnt goes here

  #endif
```

2. using `#prama once` directive: the compiler has the reponsivility to header guard. not the dev.
```cpp
  // this is a header file
  #pragma once
  // content goes here
```
