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
it us a function that returns the length of a container as a large signed integeral type (usually `std::ptrdiff_t`), its usesd as a signed conterpart of `std::size_typr`
if we want to uses this as a method for assigning the length of a container to an `int` we have some options:

* first: using the `static_cast` to prevent narrow conversions:
```cpp
std::vecttor num { 1, 2, 3, 4 };
int length { static_cast<int>( std::ssize(num) ) };
```
* or we can use the auto keyword to deduce the type of the length to be returned by the intgeral type:
```cpp
std::vecttor num { 1, 2, 3, 4 };
auto length { std::ssize(num) };
```

Accessing array elements using operator[] does no bounds checking
-----------------------------------------------------------------
yeah it doesnt if indexing for an out of bound index, UB can occur.

Accessing array elements using the at() member function does runtime bounds checking
------------------------------------------------------------------------------------
yeah if performs bpund checking at runtime so if an out of bound index is requested using the `at()` member function it halts the program at runtime.
an exmaple:
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector vec { 1,2 ,3, 4, 5 };
    std::cout << vec.at(4);                                                 // this is fine. still in bound.
    std::cout << vec.at(8);                                                 // terminates program at runtime: not in bounds.
}   
```
when the `.at()` member function tries to acces an out of bound indec it throws an `std::out_of_range` error and terminates the program.
becuae of its runtime evaluation nature its slower than `operator[]` indexing but more safer.

Indexing std::vector with a constexpr signed int
------------------------------------------------
we can do this tp enable the compiler convert the constexpr signed int to a std::size_t withput it being a narrow conversion.
an example:
```cpp
std::vector<int> num { 1, 2, 3, 4 };
std::cout << num[2];

constexpr int index { 3 };
std::cout << num[ index ];      // not a narrow conversion.
```
dont get the use of this but okay.

Indexing std::vector with a non-constexpr value
-----------------------------------------------
the subscripts used to index an array can be non const.
an example:
```cpp
std::vector num { 1, 2, 3, 4 };
std::size_t index { 2 };

std::cout << num[index];                    // operator[] requires an index of type std::size_t so no narrow conversion required.
```
whn our subscripts are non-constexpr signed integer we run into some issues.
an example:
```cpp
std::vector num { 1, 2, 4, 5 };
int index { 3 };
std::cout << num[index];                        // hers a problem occurs: narrow conversion (implicilty converted signed int to std::size_t).
```
this might raise some warnings (not errors) if warning flags where set, this can be quite annoying.
we can prevent this by always:
1. `static_cast`ing our subcripts when not of the right type which is `std::size_t`
2. or just always using the `std::size_t` as the type of subsripts whenever.


Passing and returning std::vector, and an introduction to move semantics
========================================================================

the `std::vector` element type is part of the type information of the object. so when we declare `std:vectors` as parameter ina function.
we declare them with thier full template declaraion. amd becuase vectors can be quite expensive to copy we pass the as references.
an example:
```cpp
#include <iostream>
#include <vector>

voud passByRef(std::vector<int>& arr)               // we must explicitly specify the <int>.
{
    std::cout << arr[0] << '\n';
}

int main()
{
    std::vector vec { 1, 2, 3, 4, 5 };
    passByRef(vec);
    retunr 0;
}
```
Passing std::vector of different element types
----------------------------------------------
vbebcuae the passByRef function only takes in vectors of element type `int` we cannot pass in another vectors of a different element type.

in c++17+ this can be bypassed tho using CTAD (class template argument deduction)
an exmaple:
```cpp
#include <iostream>
#include <vector>

voud passByRef(const std::vector& arr)               // no need to specify the <int> to allow CTAD work.
{
    std::cout << arr[0] << '\n';
}

int main()
{
    std::vector prime { 1, 2, 3, 4, 5 };
    passByRef(prime);                           //  CTAD uses its argument to infer that te vector should be of type std::vector<int>
}
```

we can alos make the function a template function instead of reling on CTAD:
an exmaple:
```cpp
#include <iostream>
#include <vector>

template <typename T>
void passByRef(const std::vector<T>& arr)
{
    std::cout << array[0];
}
```

Passing a std::vector using a generic template or abbreviated function template
-------------------------------------------------------------------------------
pass

Asserting on array length
-------------------------
when we try acces an index thats out of bounds of a vector it leads to UB.
so we can asser on the size first: if logically acceptable we can proceed.

Returning a std::vector
-----------------------
when we need to pass in a vector into function we pass it as a cont reference just not to make a copy.
but for some god dammed reason its okay to return it by value.

Introduction to move semantics
------------------------------
when inaitializing or assigning a value to an object copies value from another object we say its operating with `copy semantics`
sometimes when we intialize `some` objects with another objects of the same datatype instead of we accomplishing out goal with `copy semantics` the compiler performs
`move semantics` instead.

this is when instead of copying the data from an object to intialize another object, we move the data of the initializing object to the one to be initialized (`move semantics`)
there are 2 criterias for this to occur:
1. the datatype must support move semantics
2. the object to be intialized must be initrialized with another object of the same datatype thats an `rvalue`.

not many datatypes support, `std::vector` and `std::string` support move semantics tho.

an example of move semantics in c++:
```cpp
#include <vector>

std::vector generateVec()
{
    std::vector vec { 1, 2, 3, 4, 5 };
    return vec;
}

int main()
{
    std::vector vec { generateVec() };          // here move semantics occur becuase firstly std::vector supports it and
                                                // secondly its being intialized with an rvalue object returned by the generateVec() function.
}
```

We can return move-capable types like std::vector by value
----------------------------------------------------------
Because of std::vector supports move semantics we can return by value without worrying about object duplication.
making retunr by value extreemely inexpensive for this types.


Arrays and loops
================
an example:
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector scores {23, 455, 65, 76, 23};
    std::size_t length { std::size(scores) };

    int average { 0 };
    for (std::size_t index { 0 }; index < length; ++index)
        average += scores[index];
    average /= static_cast<int>( std::size(scores) );

    std::cout << "average score is " << average << '\n';
    return 0;
}
```
accessing the elements of a container in some order is known as `traversal` or `iterating through`.

Templates, arrays, and loops unlock scalability
-----------------------------------------------
an example:
```cpp
#include <iostream>
#include <vector>

template <typename T>
T average(const std::vector<T>& array)
{
    std::size_t len { array.size() };

    T average { 0 };
    for (std::size_t index { 0 }; index < len; ++index)
        average += array[index];
    average /= static_cast<int>(len);

    return average;
}

int main()
{
    std::vector class1 { 84, 92, 76, 81, 56 };
    std::cout << "The class 1 average is: " << calculateAverage(class1) << '\n';

    std::vector class2 { 93.2, 88.6, 64.2, 81.0 };
    std::cout << "The class 2 average is: " << calculateAverage(class2) << '\n';

    return 0;
}
```

Arrays and off-by-one errors
----------------------------
fuck this shi


Arrays, loops, and sign challenge solutions
===========================================
we all know that container subscript, index and length type are `std::size_t` which is an unsigned integeral.
because of the unstable nature of unsigned types when interacting with negative values: this can pose some issues like so:
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector vec { 1, 2, 3, 4, 5 };

    for (std::size_t index { vec.size() -1 }; index >= 0; --index)
        std::cout << vec[index] << ' ';
}
```
firstly it iterates an prints the vector elements in reversal as expected then after (and at) the iteration where index becomes -1 undefined behaviour occurs.
this is due to the bound wrapping action unsigneds take when interacting with negative values. because it bounds to some very large garbage value whenever
`index` should be negative the loop never ends (due to its `index >= 0` condition) and prints garbage values infinitely until the program crashes.

athough there are a some ways to fix this issue. using `signed` integral type can easily fix this but it itself has its own downsides.
an example:
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector vec { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    for (int index {static_cast<int>( vec.size()-1 )}; index >= 0; --len)
        std::cout << vec[static_cast<std::size_t>(index)] << ' ';
}
```
in this snippet although its works the cluttering of code is crazy: which reduces readablity. although the cluttering is not that severe in this example it becomes
really much in lerger code. so yeah `unsigned` compromises execution safety when interacting with negaative but `signed` creates a lot of clutter.
so what can we do?

Leave signed/unsigned conversion warnings off
---------------------------------------------
makes debuginng easier and prevents being drowned with a buttload of warnings.

Using an unsigned loop variable
-------------------------------
some developers prefer using this paradigm but we have to careful to prevent running into signed/unisgned mismatches when doing so.

1. using the `size_type` of conatiners (usually its just an alias of `std::size_t` which is just an unsigned long (long)) 
    an example:
    ```cpp
    std::vector arr { 1, 2, 3, 4, 5 };

    for (std:vector<int>)::size_type index { 0 }; index < arr.size(); ++arr)
        std::cout << arr[index];

    ```
    however using `size_type` has some downsides: its nested so clutters code and when used in a function template, because it becomes a nested
    dependent type (due to being used in a template function that takes in template parameter to genereta the the type of vector container thus making
    it dependent) we have to prefix the `typename` keyword when declaring it. you have to use the prefix `typename` whenver declaring a dependent type
    an example:
    ```cpp
    #include <iostream>
    #include <vector>

    template <typename T>
    void printArray(std::vector<T>& arr)
    {
        for (typename std::vector<T>::size_type index { 0 }; index < arr.size(); ++index)
            std::cout << arr[index];
    }
    
    int main()
    {
        printArray( std::vector {1, 3, 4, 5, 6, 7} );
    }
    ```
    any name that depends on a type containing a template paramater is called a `dependent name`.
    and they must be prefixed with the `typename` keyword.
    
    sometimes soem developers use alias to make loops easier to read.
    an example:
    ```cpp
    using arrayi = std::vector<int>;
    for (array1::size_type index { 0 }; index < arr.size(); ++index)
    ```

2. We can also tell the compiler to return the type of the container using the `decltype` keyword, whih returns the type of its parameter.
    an example:
    ```cpp
    for (decltype(arr)::size_type index { 0 }; index < arr.size(); ++index)
    ```
    however if arr is a reference the above doesnt work so we have to remove the reference: and to do that we:
    ```cpp
    template <typename T>
    void printArray(std::vector<int>& arr)
    {
        for ( typename std::remove_reference_t<decltype(arr)>::size_type index {0}; index < arr.size(); ++index )
            std::cout << arr[index];
    }
    ```
    undortunately this is neither concise or easy to remeber so most times programmers just use `std::size_t` becasue most of the times
    containers `size_type` are usually aliases of `std::size_t`.

Using a signed loop variable
----------------------------

