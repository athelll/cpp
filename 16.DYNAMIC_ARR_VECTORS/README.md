Athell Felix Ikechukwu O. Dec 31, 2023,
Dynamic arrays: std::vector

Introduction to containers and arrays
=====================================
we be talking of vectors now.

The variable scalability challenge
----------------------------------
Due to the fact that we would eventually interact with large quantity of data in some scenerio, it can prove cumbersome handling them (due to thier leviathan sized nature) without falling victim to error.
c++ has a solution to the problem: `containers`

Containers
----------
think of containers as egg crates: they provide an easier, efficient and portable way of handling as many eggs as the crate is designed to hold.
containers in c++ exist with the same purpose as egg crates (in a way). they make it easier to manage (potentially) large collection of objects (called `elements`).
a `string` is a subtle example of containers in c++: they provide a collection of characters, which can be outputted as text.

The elements of a container are unnamed
---------------------------------------
while the container object itself has a name (else how would we refer to it?) its elements are unnamed: this is an `important` details of containers.
containers provide interfaces to enable access to the its elements.

The length of a container
-------------------------
teh number of elements in a container, in programming generally, is known as its `length`, or sometimes count.
```cpp
std::string name { "Athell" };
std::cout << name << " has " << name.length() << " characters.\n";    // here the length member function is used to return the length of the container: std::string name.
```

Container operations
--------------------
containiers should basically perform tasks:
1. create an container (empty or initialized)
2. access to elements
3. insert or removal of elements
4. get the number of elements in the container.
any other opertaions, that should be beneficial to the logic of the container.

Element types
-------------
in most programming languages containers are `homogenous`, meaning the elements of the container are required to have the same type.
some containers use a preser type for its elements: like with `std::string`  its elements are of type: `char`.

in c++ containers are usually made as class templates, to make it possible to have containers for any specified datatype and length: this makes it really convenient.

Introduction to arrays
----------------------
an array is a container data-type that stored its elements `contiguously` (meaning everly element is placed in adjacent memory location with no gaps).
allowing fast and direct access to any element.

c++ generally contain 3 primary array types:
1. C-styled array                 : known to behave strangely and are dangerous, wth did you expect? its from fucking C.
2. std::vector container class
3. std::array container class


Introduction to std::vector and list constructors
=================================================
here we be talking of `std::vectors`.

Introduction to std::vector
---------------------------
the `std::vector` is one of the containers in c++ library that implements an array. it is declared in the vector header as a class template, with a template parameter
that defines the type of its elements. therefore a `std::vector<int>` defines a container with elements of type `int`.
```cpp
#include <vector>

int main()
{
  std::vector<int> empty {};
}
```

Initializing a std::vector with a list of values
------------------------------------------------
most often we want to initialize our containerw with values: we can achieve this using list initialization and C++17 CTAD ( Class Template Argument Deduction )
```cpp
#include <vector>

int main()
{
  std::vector<int> arr_int { 1, 2, 3, 4 ,5 };         // explicit delcaraion of a container of int elements
  std::vetcor arr_char { 'a', 'b', 'c', 'f' };        // initializing and determining its type using CTAD.
}
```

List constructors and initializer lists
---------------------------------------
containers have a special constructor known as `list constructor`. it allows us to construct an instance of the container using an initializers list.
it does three things
1. ensures container has enough space to hold all the initialization values
2. sets the length of the container to the number of elements inputed
3. initializes the elemenst in sequntial order as listed in the list initializer.

Accessing array elements using the subscript operator (operator[])
------------------------------------------------------------------
just like in C: they are `zero based` tho.

an example:
```cpp
#include <iostream>
#include <vector>

int main()
{
  std::vector numbers { 1, 2, 3, 4, 5 };
  std::cout << "the first number is " << numbers[0] << '\n';                // `[x]` is the subscript operator with with x being the subscript: the index to be accessed.
  std::cout << "the second number is " << number[1] << '\n';
}
```

Subscript out of bounds
-----------------------
when indexing an array: the index selected must be a valid element in the array, its subscript limit is usually `N-1` where N is the size length of the array.
the `operator[]` does not perform any sort of bound checking: meaning passing in an invalid index will lead to UB.

Arrays are contiguous in memory
-------------------------------
one defining characteristics of arrays is that they are allocated contigously in memory: meaning they are located adjacent in memory with no gaps.
an example:
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector primes { 2, 3, 5, 7, 11 };
    std::cout << "an int of of size " << sizeof(int) << '\n';
    std::cout << &(prime[0]) << '\n'
    std::cout << &(prime[1]) << '\n'
    std::cout << &(prime[2]) << '\n'
}

```
the results on my system:
```bash
an int of of size 4
0x55e84ecf3eb0                                                      # if you look closely the addreess increment with 4 proving they are contigous.
0x55e84ecf3eb4
0x55e84ecf3eb8
```
arrays are one of the containers that allow `random access` meaing every element can be accessed directly with equal speed, regardless the length of the array.

Constructing a std::vector of a specific length
-----------------------------------------------
`std::vector` has an explicit ocnstructor `explicit std:vector<T>(int)` that takes in only one integer value to set the length std::vector when constructing.
an example:
```cpp
std::vector<int> data (10);                             // we just declared a vector of an immutable length: 10.
```
each of the elements are value-initialized and are therefore all initialized to zero.
this constructor must be called using `direct` intialization not `list`.

List constructors take precedence over other constructors
---------------------------------------------------------
yup read this in the site. moral lesson is: list constuctors take precedene to other conctructors and thats why initializing with direct initialization will only set the
length of an array and zero initialize its members and using list will not (it just provide the elements).

note:
```cpp
std::vector<int> num({ 10 });       // this is an alternative version of copy list init.tion so this will not construct for specified length.
```

Declaring vectors as a member of a class type
---------------------------------------------
due to the fac the direct initialization is not allowed for default memeber initializers: we cant do this to set the length of a vector:
```cpp
struct Foo
{
    std::vector<int> vec ( 10 );                // error due to stated above reason
};
```
but we can due this instead: creats an anonympus object and then use that to defaultly set the length of the vector via the copy constructor
```cpp
struct foo
{
    std::vector<int> vec { std::vector<int>(10) }
}
```

Const and constexpr std::vector
-------------------------------
they can be be made const and this makes their elements immutable: also they must be intialized:
```cpp
const std::vector<int> vec {1, 2, 3, 4};
vec[0] = 9;                                         // error they are immutable.
```
also normal std::vector elemenst are not allowed to be const: the must be mutable.
so doing something like this is prohibited.
```cpp
std::vector<const int> vec { 1, 2, 3, 4 };          // illegal: error: `<const int>` cant make the int const cause that will meke the elements immutable which is not allowed
                                                    // vectors.
```


std::vector and the unsigned length and subscript problem
=========================================================
read this section and reread the paper bjourne stroustrop wrote regarding the mistake of using `unsigned integers` for subscripting due to it
bound wrapping into garbage values because it relies on modular arithmetics

Paper: [why subscipts should be signed](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p1428r0.pdf)

A review: sign conversions are narrowing conversions, except when constexpr
----------------------------------------------------------------------------
`unsigned int` to `signed int` or the other way around are narrow conversions, which list initialization do not allow
but when made `constexpr` they allow them because the compiler would have to make sure the coversion is safer (at compiler time) otherwise halt the compilation
so narrow converting like declarations are allowed if the varaible to be narrowed is a `constexpr`.
```cpp
#include <iostream>

void foo(unsigned int)
{}

int main()
{
    constexpr int s { 5 };                 // now constexpr
    [[maybe_unused]] unsigned int u { s }; // ok: x is constexpr and can be converted safely, not a narrowing conversion
    foo(s);                                // ok: x is constexpr and can be converted safely, not a narrowing conversion

    return 0;
}

```
copy initialization do allow narrow conversions tho.
also: the non narrowing conversion of `constexpr int` to `constexpr std::size_t` is something we will use a lot. according to what i just read.

The length and indices of std::vector have type size_type
---------------------------------------------------------
yup. and `std::size_t` is an alias for an `unsigned long` or `unsigned long long`.
each of the STL container classes define a nested typedef of `size_type`, which is the alias for they type used for the containers length or (indices if supproted).
almost always the `size_type` is usually an alias for `std::size_t`, but it can be overidden (rarely done).

when accessing the `size_t` member of a conatainer class er must scope the class with its full template declararion
an example:
```cpp
std::vector<int>::size_type
```

Getting the length of a std::vector using the size() member function or std::size()
-----------------------------------------------------------------------------------
an example:
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> vec { 1, 2 , 3, 4, 5 };
    std::cout << "the size of vec is " << vec.size() << " used .size()\n";
    std::cout << "the size of vec is " << std::size(vec) << " used std::size()\n";
}
```
in c++ most containers have thier length member functions dub as size, except in strings and string_view that have both length and size.

note:
- favor using `std::size()` that constainers `.size` this is becuase it works on a broader set of containers like non-decayed c-styled arrays.

if we wasnt to use the `std::size()` or `.size` to initialize some variable with the size of a container, we might sometimes run into signed/unsigned conversion warnings or errors.
we can prevent this by `static_cast`ing to the type same with the variable to be stored into.
an example:
```cpp
#include <vector>

int main()
{
    std::vector<int> vec {1, 2, 3, 4, 5};
    int length { static_cast<int>( vec.size() ) };              // error free!
}
```

Getting the length of a std::vector using std::ssize() C++20
------------------------------------------------------------

