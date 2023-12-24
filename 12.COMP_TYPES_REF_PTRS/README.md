NOv 24, 2023 Felix Okoronkwo,
Compound Types: References and Pointers

Compound data types
===================

this are datatypes that can be constructed from fundamental data types(or other compound data types)

C++ supports the following compound types:
1) Functions
2) Arrays
3) Pointer Types:
  * Pointer to object
  * pointer to function
4) Pointer to member types:
  * Pointer to data member
  * pointer to member function
5) Reference Values:
  * L-value references
  * R-value references
6) Enumerated types:
  * Unscoped enumerations
  * Scoped numerations
7) Class Types:
  * Structs
  * Classes
  * Unions


Value categories (lvalues and rvalues)
======================================

Besides producing side-effects, expressions can do on more thing: evaluate to objects or functions.

Properties of an expression
---------------------------
to determine how an expression should evaluate and where they can be used an exoression posses to attributes: a `value` and `type` category.

the type of an expression results from the type of the value, object or function that results from its evaluation.
note that type of an expresson must be determinable at compile time or else tyoe checking and tyoe deduction will not work.
However the value can be determined at runtime (or compile in the case of constexpr expressions.)

The value category of an expression
-----------------------------------

consider this code:
```cpp
int main()
{
  int x{ 8 };
  x = 8;                    // this is fine
  8 = x;                    // error.
}
```

int the above example we can see that its fine assigning an int value to the variable `x` but why can we assign `x` to an int literal? how does the
compiler know what assignement is right? this is were the `value category` or expressions comes in play.

the `value category` of an expression checks if an expression evaluates to a function, value or object of some sort.
peior to c++11 there were only 2 possible value categories:
1) lvalues
2) rvlues

in c++11, three additional value categories where added:
1) glvalue
2) prvalue
3) xvalue
this was all to support a new feature called `move semantics`.

Lvalue and rvalue expressions
-----------------------------------------------
lvalues
-------
an lvalue (or `left value` or `locator value`) is a value that evaluates to an identifiable object, function or bitfield.

the term `idenity` is used loosely in c++, for clarification: an identity makes an entity differerntiable from other similar entities.
an entity with an identity can be referred to with an identfier, reference or pointer and typically have an lifetime longer than that of a single expression.

lvalues come in 2 subtypes: `modifiable` and `non-modifiable` lvalues(consts and constexprs).

rvalues
-------
rvalues also known as right values is an expression that is not an lvalue. Commonly ssen rvalues include literals (except C-style strings which ar lvalues)
and the return value of function and operators that return by value.
Rvalues arent identifiable (meaning they hav to be used immediately) and are only used in the scope of the expression they are used.

```cpp
int return5()
{
  return 5;
}

int main()
{
  int x{ 5 };                             // 5                    is an rvalue
  const double d{ 1.2 };                  // 1.2                  is an rvalue

  int y { x };                            // x                    is a modifiable lvalue
  const double e { d };                   // x                    is a non-modifiable lvalue
  int z { return5() };                    // return5()            is an rvalue expression.

  int w { x + 1 };                        // x+1                  is an rvalue
  int q { static_cast<int>(d) };          // static_cast<int>(d)  evaluates to an rvalue: casts to not modify the object they work on.

  return 0;
}
```

and this is why we cant `8 = x` in pur previous example, for clarity: the `=` operator requires the left operand to be a modifiable lvalue and the right an rvalue expression.

Tip on determining if a value is an lvalue or rvalue
----------------------------------------------------
the `&`operator compiles if used beside an lvalue and does not with an rvalue;:
```cpp

int foo()
{
  return 6;
}
int main()
{
  int x{6};
  &x;                       // compiles:                 lvalue expression
  &6;                       // does not compile:         rvalue expression
  &foo();                   // does not compile:         rvalue expression
}
```

Lvalue to rvalue conversion
---------------------------
lvalues implicilty converts to rvalues thats why they can be used where rvalues can be used:
```cpp
int x{ 7 };
int y{ 5 };

y = x;                    // this is fine because of lvalues implicit comversion to rvalues: in this case x was converted.
x = x + 1;                // also valid due to the reason above.
```

A rule of thumb to identify lvalue and rvalue expressions
---------------------------------------------------------
- lvalue expressions evaluates to an identfiable object that persists beyond the lifetime of the expression
- rvalues expressions evaluates to anonymous literals that their lifetime ends at the end of the expression


LVALUE REFERENCES
=================

In C++ a reference is an alias for an existing object. A reference is essentially identical to the object being referenced.
that mean we can use refernces to read and modify objects being referneced.

you can also create refernece to functions.

modern c++ contains 2 types of refernces:
1) lvalue references
2) rvalue references

Lvalue reference types
----------------------
an lvalue reference is a refernence that acts as an alias for an existing lvalue such as a variable.

to declare an lvalue reference type use an ampersand in its decleration:
```cpp
int             // normal int type
int&            // a reference to an int object
double&         // a reference to a double object
```

Lvalue reference variables
--------------------------
one thing we can do with lvalue refernces is to create an `lvalue refernce variable`: a variable that acts as a reference to an lvalue object.
```cpp
int main()
{
  int x{ 9 };
  int& ref{ x };                // lvalue reference variable: reference to the lvalue x.
}
```

Modifying values through an lvalue reference
--------------------------------------------
we use refernces just as we use the variables we refernece them with:
```cpp
#include <iostream>

int main()
{
  int x{ 9 };
  int& ref{ x };

  std::cout << ref << '\n';                   // prints 9
  ref = 10;
  std::cout << x << '\n';                     // prints 10
  x = 11;
  std::cout << ref << '\n';
}
```

Initialization of lvalue references
-----------------------------------
much like constants, references must be initialized.
```cpp
int main()
{
  int& invalidRef;                          // error: references must be initialized.

  int x{ 5 };
  int& ref{ x };                            // this is legal.

  const int seven{ 7 };
  int invalidRef{ seven }                   // references cannot bind to a non-modifiable value.
}
```

when a refernces is initialized with an object or function we say its bound to that object or function: this process is known as `reference binding`
the object or function being referenced is sometimes called the `referrent`.

Lvalue refernces must be bound to a modifiable lvalue.
referecnces cant be bound to non-modifiable l or rvalues because well be able to modify them through the references and therefore destroying the `const` nature
of unmodifiable lvalues (or rvalues).

refernces only refernces objects of the same type as itself (there are exceptions tho).
lvlaue refernces to void are illegal(what would be the point?).

```cpp
int main()
{
  int x{ 5 };
  int& ref{ x };                // okay: same type

  double y{ 8.2 };
  int& invalidRef{ y };         // ilegall: can't bind to an object with differnt type.
}
```

References can’t be reseated (changed to refer to another object)
-----------------------------------------------------------------
once an references is binded to an object it cant be reseated: meaning that it cant be changed to references another object.
```cpp
#include <iostream>

int main()
{
  int x { 5 };
  int y { 7 };

  int& ref { x };

  ref = y;                  // legal: but some might expect ref to bind to x as its new reference, but it doesn not. it assignes the value of x to y.
}
```

Lvalue reference scope and duration
-----------------------------------
reference follow the same scoping and duration that normal variables do:

References and referents have independent lifetimes
---------------------------------------------------
they both have independent lifetimes meaning:
1) A refernces can be desrtoyed before its referent.
2) An object being referenced can be destroyed before its reference.

```cpp
int main()
{
  int x{ 8 };

  {
    int& ref{ x };
    ++ref;
  } // ref dies here and x is oblivous.

  std::cout << x << '\n';
} // x dies here.
```

Dangling references
-------------------
when an object is destroyed before its reference, it yields a `dangling reference`: that is a reference that is binded to a non existent object.
Accessing a dangling reference leads to undefined behaviour.

they are fairly easy to avoid tho: will be discussed later.

References aren’t objects
-------------------------
its not an object homie.


Lvalue references to const
==========================

Introduction
------------
we can make lvalue references bind to a non-modifiable lvalue by declaring the reference with the const keyword:
```cpp
const int x{ 9 };
const int& ref { x };                 // lvalue reference to a const: legal with the const keyword.
```

sine they are binded to const they can only be used to access not modify.

Initializing an lvalue reference to const with a modifiable lvalue
------------------------------------------------------------------
when we do this since the ref is declared to be constant we can only access the modifiable lvalue: we cannot modify the lvalue via its const reference
the lvalue tho is still modifiable with its own identifier.

Initializing an lvalue reference to const with an rvalue
--------------------------------------------------------
when this happens an anonymous object is created (initialized with the rvalue) and its accessible with the ref.
Temporary objects have no scope because they have no identifier (and scope is a property of identfiers).

but the thing is thet references outlive the lifteime of temporary objects ans subject the temporary objects they are binded to inherit the same lifespan the
references themselves have (which is `block scope` with `automatic duration`)

```cpp
int main()
{
  const int& ref{ 5 };                // anonymous object binded to const reference ref. lifrtime extended to match ref.
  // do stuff with ref here
  return 0;
} // anonymous object with value 5 and ref dies here.
```

note:
- lvalue references can only bind to modifiable lvalues
- const lvalue references csn bind, modifiable lvalues, non-modifiable lvalues and rvalues. makes them more flexible.

Constexpr lvalue references
---------------------------
when applied to a reference, constexpr alloes refereces to be used in constant expressions.
they do have a limitation tho: they can `only` be binded to objects with static duration(either globals or static locals).
this is because static objects address in memory are known by the compiler at compile time so it can access it at compile time.

they cannot be binded to local variables because their addresses are not known until the function they are scoped in is called, which the local variables are then
instantiated to have addresses.
```cpp
int g_x{ 5 };

int main()
{
  [[maybe_unused]] constexpr int& ref1 { g_x };   // okay: global variables are static in nature

  static int s_x{ 10 };
  [[maybe_unused]] constexpr int& ref2 { s_x };   // okay: s_x is a static local variable.

  int x{ 15 };
  [[maybe_unused]] constexpr int& ref3 { x };     // illegal: x is not static.
}
```

when defining a constexpr reference to a static const variable we need to apply both the constexpr and const keywords to the variable:
```cpp
static const int s_cx { 10 };
[[maybe_unused]] constexpr const int& ref { s_cx };
```

Pass by lvalue reference
========================

wen calling function passing in arguments to the function for the values to be copied, modified and returned can be expensive, especially when the modification
and return is to modify a variable that belonged to the callers scope.

this issue is addressed easily with addresses.

Normal function calls
---------------------
now consider a case where we want to call a function to modify a value in the callers scope we mught do something like this with normal argument passing:
```cpp
#include <iostream>

void plusOne(int x)
{
  x++;                      // 2) x is incremented but not that of the callers: they are independent
} // 3) x dies here with its change

int main()
{
  int x { 1 };
  plusOne(x);               // 1) the value in variable x is copied into int x of plus one: both are now independent variables with the same value
  std::cout << x << '\n';   // 4) no change to x: x remains the same
}
```

due to function calls having parrallel scopes (independent scopes), we cannot ordinarily pass a value in one function to another and expect the function
to modify the passed in variable from its caller in its scope (scope of the called function).

in actually what we are doing is just copying values from one function to another with the constraint that the copied argument is independent from that of the initial
one (from the caller function) despite both having the same value, which is kinda wasteful if you think about it

an int vairable in the main function occupying 8 bytes passed it into the plusOne funtction as a parameter, the plusOne function creates a seperate int variable of its own,
and copies the value of the initial variable passed into it. after initializing its own int variable with the value of the initial int passed in, it has no business with its
callers int anymmore and leaves it alone.

now we have 2 int variables: one int in the plusOne and another in the main and both of them having the same value making a total of 16bytes of memory.
which is inefficient and wasteful since both have the same value and one could just be used for any computations we wanted to execute.

one of the solution to this problem is: `pass by reference`.

Pass by reference
-----------------
with pass with reference we can just use one object modify or utilize it another functions scope and have the modifed effect reflect in in the callers function scope.
this prevenets us form making expensive copies.

inexpesive argument passing:
```cpp
#include <iostream>
#include <string>

void printValue(std::string& y)
{
  std::cout << y << '\n';
} // y is destroyed

int main()
{
  std::string x { "Hello Cuck Suckers!" };
  printValue( x );                              // inexpensive because x is passes into a reference so no duplication occurs.
}
```

modified argument reflecting in callers function:
```cpp
#include <iostream>

int plusOne(int& x)
{
  ++y;                      // modifies the object that y is referencing which is main() x.
}

int main()
{
  int x { 0 };

  std::cout << x << '\n';
  plusOne(x);
  //x has been modified.
  std::cout << x << '\n';
}
```

Pass by reference can only accept modifiable lvalue arguments
-------------------------------------------------------------
Because a reference to a non-const value can only bind to a modifiable lvalue. so no const or literals.


Pass by const lvalue reference
==============================

a reference to a const can bind to any type of value, lvalues (modifiable and non), rvalues and literals. making it more favourable ot use than its counterpart.
Passing by const reference offers the same primary benefit as pass by reference (avoiding making a copy of the argument), and the function cant change the value
being referenced.

this is not allowed:
```cpp
void addOne(const int& ref)
{
  ++ref; // not allowed: ref is const
}
```

NOTE:
----
Favor passing by const reference over passing by non-const reference unless you have a specific reason to do otherwise
(e.g. the function needs to change the value of an argument).

When to pass by (const) reference
---------------------------------
1) class types are usually passed by const reference instead of by value to avoid making an expensive copy of the argument.
2) pass fundamental types by value, and class (or struct) types by const reference.
3) Prefer pass by value for objects that are cheap to copy, and pass by const reference for objects that are expensive to copy.
   If you’re not sure whether an object is cheap or expensive to copy, favor pass by const reference.

NOTE:
----
- pass by refrence is generally slower than passing by value but in cases where the object being passed is expensive to copy use it.
- An object is cheap to copy if it uses 2 or fewer “words” of memory (where a “word” is approximated by the size of a memory address)
  and it has no setup costs.

The cost of pass by value vs pass by reference
----------------------------------------------
thus us a helper macro that tells if a datatype is cheap to copy:
```cpp
#include <iostream>

#define isSmall(T) (sizeof(T) <= 2*sizeof(void *))  // this is the helper macro

struct S
{
  double a;
  double b;
  double c;
}

int main()
{
  std::cout << std::boolalpha;
  std::cout << isSmall(int);            // yes: favoue pass by value
  std::cout << isSmall(double);         // yes: favour pass by value
  std::cout << isSmall(S);              //  no: favour const referencing.
}
```

For function parameters, prefer std::string_view over const std::string& in most cases
--------------------------------------------------------------------------------------
this is because `std::string_view` can handle a wider variety of string inputs ans its less expensive.


Introduction to pointers
========================

- in C++: normal pointers (pointers inherited from C) are known as dumb pointers

Pointer initialization
----------------------
```cpp
int main()
{
  int x{ 5 };

  int* ptr;         // unitialized pointer holds garbage address
  int* ptr_1{};     // a null pointer
  int* ptr_1{ &x }; // initialized pointer pointing to x.
}
```

pointers can only point to types that are the same with the type they are.
pointers cant be initialized with literal values or addresses-like-values they will be treated as ints or other fundamental types
and not an address.

Pointers and assignment
-----------------------
we can use the assignement operator on pointers for 2 uses:
1) To change the value of the address that the pointer is pointing to.
2) to change the value being pointed at (by assigning the dereference operator)

```cpp
int x{ 6 };
int y{ 7 };
int* ptr{ &x };                 // pointer initialized to point to x
ptr = &y;                       // pointer now points to y
*ptr = 10                       // pointer has now changed the value stored in y by dereferencing.
```

Similarities and differences of pointers and references
-------------------------------------------------------
1) References must be initialized; Pointers on the other hand dont have to be initialized ( but they should )
2) References cannot be reaseted; pointers can
3) References are usually safe (except when dangling); pointers are inerently dangerous
4) References are not objects; pointers are
5) References must always be bound to an object, pointers can point to nothing.

6) THey are bothe used for accessing and modifying an object.

The address-of operator returns a pointer
-----------------------------------------
the address operator is mistaken to return a hexadecimal address but in actuality what happens is that the address is converted to a pointer housing that address
and that is what is returned back.
```cpp
#include <iostream>
#include <typeinfo>

int main()
{
  int x{ 4 };
  std::cout << typeid(&x).name() << '\n';   // this prints `Pi` or `int *` deending on your compiler
  return 0;
}
```

The size of pointers
--------------------
the size of a pointer depends on the architecture the executable is being compiled on: since pointers are just memory addresss they take up the word length
that the arcitecture itself uses to process, store and refer to data. If you're on a 64 bit machine, processing data in memory 64 bits at a time, it will make sense that the
size of memory address the architecture refers to are 64bits is size: thus making the size of pointers 64bits in size also.

same rationale with 32 bits systems.

the size of a pointer is constant depsite the type it points to because in essence a pointer is merely just an address and the number of bits needed to access a memory address
is constant.

Dangling pointers
-----------------
A dangling pointer is a pointer holding the address of an object that is no longer valid. Dereferncing a dangling pointer will lead to UB or maybe a seg fault.


Null pointers
=============

beides objects address theres one additional value pointers can hold and that is a `null value`. a null value (or simply null) is a value that means something has no value.
when a pointer is holding a null value it means that the pointer is pointing to nothing. easiste way ot create a null pointer is using value initialization:
```cpp
int main()
{
  int* ptr{};             // null pointer, its holds no address
  return 0;
}
```

value initialize your pointer it be null unless initualizing them with a valid address.

The nullptr keyword
-------------------
the `nullptr` keyword represents a noil pointer literal. we use it to explicitly initialize a null pointer.
```cpp
int main()
{
  int* ptr { nullptr };     // null pointer
  int x { 5 };
  int* ptr2 { &x };         // another pointer: not null
  ptr2 = nullptr;           // now null

  someFunc(nullptr);        // we can also use the nullptr for arguments that require a pointer.
  return 0;
}
```

Dereferencing a null pointer results in undefined behavior
----------------------------------------------------------
dereferncing a null pointer leads to UB that should crash the program (usually with a seg fault): you can try it with this snippet:
```cpp
#include <iostream>

int main()
{
  int* ptr{};
  std::cout << "crashe-" << *ptr << '\n'
}
```

Checking for null pointers
--------------------------
1) method 1: explicitly compare with the nullptr literal keyword.

```cpp
int* ptr{};

if (ptr == nullptr)
  // do stuff
else
  // okay its not null so do stuff
```

2) method 2: null pointers evaluate to false so placing them in a conditional like that should evaluate to tell you if its null or not.

```cpp
int* ptr{};

if (ptr)
  // its null do something
else
  // its not null do another thing
```

Legacy null pointer literals: 0 and NULL
----------------------------------------
0 and `NULL` are used in legacy code to initialize null pointers:
```cpp
int main()
{
  int* ptr { NULL };           // this is a null pointer: not advisable tho
  int* ptr2;                   // unitiaized: holds garbage address
  ptr2 = 0;                    // now a null pointer: not advisable
}
```

NOTE:
----
on modern arcitectures the address is used to represent a null pointerL this constraint was not created by c++ (it was done by computer designers)
so it may not be consistent on all architectures (they might be uding other values ot represent null pointers).

both 0 and `NULL` should be avoided in c++L use nullptr instead this will be explained later.

Favor references over pointers whenever possible
------------------------------------------------
This is because references are safer than pointers (which can be extremely dangerous when dangling).


Pointers and const
==================

prevously we initilizie pointers to address to mutable objects what of const non-mutable objects?:
```cpp
int main()
{
  const int x{ 5 };
  int* ptr{ &x };                   // error.
}
```

we would expect thus to works but it doesnt because we can assigne the address of a `const int` to a pointer that points to `int`: becuae logically we should
be able to defer and manipulate what `int` we are pointing to but thats not that case, because we arent pointing to an `int` we are pointing to a `const int`
which is not the same and violates the constness of the varibale.

to fix this we use the const keyword before the `int` to declare a pointer to a `const int` not just `int`:
```cpp
int main()
{
  const int x{ 5 };
  const int* ptr{ &x };              // legal
}
```

this applies to any datatype.

Const pointers
--------------

in the above examples although made pointers to `const int` we didnt declare that they cant point to other `const ints`: this is because we simply decared a pointer that
should legally point to any `const int` object, therefore it can be resaeted and point to as many objects as it can as long as the object is of type `const int`

to declare a pointer that cannot point to a differnt object after initialized we need to declare a `const pointer` to do this we use the const keyword after the
asterisks in the pointers declaration:
```cpp
int main()
{
  int x{ 5 };
  int* const ptr{ &x };             // now ptr cannot be assigned to another address: a const pointer.
}
```

although since, in this example, the datatype it points to is a non-const int, it can be derefernced and have its value changed.

Const pointer to a const value
------------------------------
they point to const datatypes and cannot be resaeted:
```cpp
const int x { 8 }
const int* const ptr { &x };        // example of a const pointer to a const value of type int.
```

Pass by address
---------------
c++ provides another method of passing in arguments that isnt by reference or by value: and this is passing by `address`.
```cpp
#include <iostream>

void someFcn(double* x)
{
  ++(*x);                   // this should increment the value passed by address in the callers scope
}

int main()
{
  double num{ 9.0 };
  someFcn(&num);
}
```

passing arguments by address prevents object duplication which saves memory footprint in a program: because we use pointers to refer to the objects
we can also derefernce the object and modify its value. like in the example above.

Pass by address does not make a copy of the object being pointed to
-------------------------------------------------------------------
passing by address does not make a copy of the object being passed as an argurment as stated above it simply derefernces the original object
thereby reducing memory footprint.

Null checking
-------------
obeserving this simple program one mighy not even recongnize a fault in its design:
```cpp
#include <iostream>

void print(int* ptr)
{
	std::cout << *ptr << '\n';
}

int main()
{
	int x{ 5 };
	print(&x);

	int* myPtr {};
	print(myPtr);

	return 0;
}
```

thsi progran will only print 5 and then crash: this is because we didnt `null check`: null checking is a precaution we impleent to make sure a pointer isnt `wild`
or `null` (simply its to check if a pointer is not null). we can edit the above code with null checking into:
```cpp
void print(int *ptr)
{
  // null check here: at the entry of the function
  if(!ptr)
    return;
  //else
  std::cout << *ptr << '\n';
}

int main()
{
  int x{ 5 };
	print(&x);

	int* myPtr {};
	print(myPtr);

	return 0;
}
```

this way before the function executes its checked to prevent seg fault.

we can also use the `assert()` function macro to assert if the the pointer is null and halt:
```cpp
void someFcn(int* ptr)
{
  assert(ptr);
  // continue with shit here if it doesnt assert out here: if in debug mode

  if(!ptr)
    return; // precaution action incase not in debug mode.(production mode)
}
```

Prefer pass by (const) reference
--------------------------------
reasons why passing by `const reference` is preferred to that of passing by address via pointers:
1) they accept both rvalues and lvalues so its more flexible
2) has a normal feel when used unlike with pointers that need to be derefernced with an additional symbol to be used (which sometimes cause confusion to new developers).

Rule of Thumb:
-------------
use pass with reference when you can and use pass with address when you must.

```cpp
#include <iostream>

void passByValue(int a)
{
  std::cout << a << '\n';
}

void passByReference(int& b)
{
  std::cout << b << '\n';
}

void passByAddress(int* c)
{
  std::cout << *c << '\n'
}

int main()
{
  passByValue(5);       // legal but makes a copy:                                            inefficient
  passByReference(5);   // legal, refers to the same int literal 5, no memory duplication:    efficient
  passByAddress(5);     // illegal: cant pass in rvalues into pointers                        should have been effeicent but impossible.
}
```


Pass by address (part 2)
========================

Pass by address for “optional” arguments
----------------------------------------
one of the reasons that passing in address are for optional arguments, example:
```cpp
#include <iostream>

void greet(std::string* name=nullptr)
{
  std::cout << "Hello";
  std::cout << (name ? *name : "guest") << '\n';
}

int main()
{
  greet();                      // this is legal and takes the user as "guest"
  std::string name { "Felix" };
  greet(&name);                 // also works with a passed in string name (treating this argument as optional)
  return 0;
}
```

this could also be achieved by function overloading:
```cpp
void greet(std::string_view name)
{
  std::cout << "Hello" << name << '\n';
}

void greet()
{
  greet("Guest");
}


int main()
{
  greet(); // we don't know who the user is yet

  std::string joe{ "Joe" };
  greet(joe); // we know the user is joe

  return 0;
}
```

Changing what a pointer parameter points at
-------------------------------------------
we can achieve this by using double pointers that takes in the address of a pointer as an argument and from dereference it but this is C-isque, in C++
this can be acieved by using a refeence to a pointer.

Pass by address… by reference?
------------------------------
this is simply done by placing an ampersand symbol after the pointer type decaration as follows:
```cpp
void nullify(int*& refptr)
{
  refptr = nullptr;
}

int main()
{
  int x{ 5 };
  int* ptr{ &x };

  std::cout << "ptr is " << (ptr ? "not-null" : "null") << '\n';
  nullify(ptr);
  std::cout << "ptr is " << (ptr ? "not-null" : "null") << '\n';
}
```

Why using 0 or NULL is no longer preferred (optional)
-----------------------------------------------------
the literal 0 can be interpreted as either a `int literal` or a `null pointer literal`. In certain cases it can be ambiguous of which one we intend to use.

The defination of the macro NULL is not defined by the language standard. it can be defined as `0, 0L, ((void *) 0)`, or something else.
this ambiguity can be fixed by using `nullptr`

std::nullptr_t (optional)
-------------------------
if `nullptr` is not of type int, it is of type `std::nullptr_t` in the `<cstddef>` header and it can only hold one value: `nullptr`
while it might seem slly: its useful in situation where we want the only argument a function accepts be the `nullptr` literal.
```cpp
#include <cstddef>
#include <iostream>

void print(std::nullptr_t)
{
  std::cout << "in print(std::nullptr_t)\n";
}

void print(int*)
{
  std::cout << "in print(int*)\n";
}

int main()
{
  print(nullptr);           // calls function: void print (std::nullptr_t)

  int x{ 5 };
  print(&x);                // calls function: int print (int*)
}
```


Return by reference and return by address
=========================================

- The object being returned by reference must exist after the function returns
- Don’t return non-const local static variables by reference
- Assigning/initializing a normal variable with a returned reference makes a copy
- It’s okay to return reference parameters by reference
- It’s okay to return by const reference an rvalue passed by const reference
- when a non const reference is returend from a function the caller can use the reference to modify the referent:
```cpp
#include <iostream>

int& max(int& x, int& y)
{
  return (x > y ? x : y);
}

int main()
{
  int a{ 2 };
  int b{ 5 };

  max(a, b) = 10;
  std::cout << a << ' ' << b << '\n';
  return 0;
}
```

Return by address
-----------------
i known this i know C.
but return by reference should be preferred to that of return by address


In and out parameters
=====================

In parameters
-------------
they are mostly used for recieving inputs from the caller.

Out parameters
--------------
they are function parameters (usualu const references or pointer arguments) that the function operates on with the aim of modifying the objects value: which in
returns acts as an output for the caller.

this provides a way for the function to return data back to its caller in scenarios where using its return will not be sufficient for some reason.
exmple:
```cpp
#include <cmath>
#include <iostream>

void getSinCos(double degrees, double& cos_x, double& sin_x)
{
  constexpr double pi { 3.1415926535897932384 };
  double radians = degrees * pi / 180;
  cos_x = std::sin(radians);
  sin_x = std::cos(radians);
}

int main()
{
  double sin{ 0.0 };
  double cos{ 0.0 };

  double degrees{};
  std::cout << "Enter degrees: ";
  std::cin >> degrees;

  getSinCos(degrees, sin, cos);

  std::cout << "Degrees: " << degrees << "\nCos: " << cos << "\nSin: " << sin << '\n';
}
```

When to pass by non-const reference
-----------------------------------
if your going to use oaoss by referene to prevent making a copy of an argument: prefer passing by `const` reference excpet solid reason not to.
like:
1) First, use pass by non-const reference when a parameter is an in-out-parameter.
2) use pass by non-const reference when a function would otherwise return an object by value to the caller


Type deduction with pointers, references, and const
===================================================

things that type deduction drops:
1) const and constexpr qualifiers
2) and `REFRENCES`

example:
```cpp
std:string& getStringRef()
{
  //
}

int main()
{
  auto ref{ getStringRef() };         // evaluates into std::string and drope the reference attribute.
}
```

just like the const and constexpr they can be reapplied:
```cpp
std::string& getRef()
{
//
}

int main()
{
  auto& ref{ getRef };              // evaluates to std::string&
}
```

Top-level const and low-level const
-----------------------------------
a `top-level const` qualifier that applies to the object itself.
when it applies to the type its a low-level.

```cpp
// top-level const
const int  a;                          // applies to the object so it top-level
int* const b;                          // applies to the object also so its top-level.

// low-level const
const int& ref;                        // applies to the object being refrenced so low-level
const int* ptr;                        // applies to the object being pointed to so low-level also.

// both types of const.
const int* const both;                 // both low and high level const itssss MEGA level!
```

Type deduction and const references
-----------------------------------
first the reference attribute is dropped and then any top-level const is dropped from the result.
```cpp
#include <string>

const std::string& getConstRef()
{
  //
}

int main()
{
  auto ref1{ getConstRef };               // refenceis dropped first, then any top level const: leaving std::string.
}
```

if they are needed thye should be reapplied.

NOte:
----
when you want a const reference, reapply the const qualifie even where uts nit strictly necassary to make your intentions clear

What about constexpr references?
--------------------------------
they work the same way as const references

Type deduction and pointers
---------------------------
unike references, tyoe deduction does not drop pointers.
```cpp
#include <string>
std::string* getPtr();

int main()
{
  auto ref{ getPtr() };               // deduces to type std::string*
  // we can also use the * symbol to make our intentions clearer
  auto* re_2 { getPtr() };            // std::string*
}
```

The difference between auto and auto*
-------------------------------------
the difference between them is that with `auto*` what happens is that the value is first type evaluated normally, let say the arguments was `s"Hello"`,
it sowuld evaluate sto type: `std::string`. After that the pointer symbol is reaplplied. makinf it a `pointer to x type`
where `x` is a datatype

there can be some isseus with `autu*` decalrations and one of them is illustrated below:
```cpp
#include <string>

std:string* getPtr();     // some function that returns a pointer

int main()
{
  auto ptr1  ( *getPtr() );                 // here a pointer is returned whic is then dereferenced leading auto to evaluate to std::string
  auto* ptr1 ( *getPtr() );                 // here a pointer is returnd which is derefed to yeilding an std::string then the pointer attribute is applied
  // making it evalue=ste to std::string* which cannot hold an std::string therefore compile error.
}
```

the auto keywrod also drop reference attributes: if they are needed they have to be reapplied.

Type deduction and const pointers Optional
------------------------------------------
ltes look and examine the code below:
```cpp
#include <string>

std::string* getPtr();

int main()
{
  const auto  ptr_1 { getPtr() };     // evaluates to std::string* const
  auto const  ptr_2 { getPtr() };     // evaluates to std::string* const

  const auto* ptr_3 { getPtr() };     // evaluates to const std::string*
  auto* const ptr_4 { getPtr() };     // evaluates to std::string* const
}
```

in the above code we see the only arragement where auto is evaluated as: `const std::string*` is the format: `const auto*`.
the rest the pattern of arrngement is not followed and they are evaluated to `std::string* const`.

NOTE:
-----
```cpp
#include <string>

int main()
{
  std::string s{};
  const std::string* ptr { &s };

  auto ptr1{ ptr };  // const std::string*
  auto* ptr2{ ptr }; // const std::string*

  auto const ptr3{ ptr };  // const std::string* const
  const auto ptr4{ ptr };  // const std::string* const

  auto* const ptr5{ ptr }; // const std::string* const
  const auto* ptr6{ ptr }; // const std::string*

  const auto const ptr7{ ptr };  // error: const qualifer can not be applied twice
  const auto* const ptr8{ ptr }; // const std::string* const

  return 0;
}
```

