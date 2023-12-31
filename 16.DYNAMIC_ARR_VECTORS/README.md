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

