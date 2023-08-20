::: {#BASICS SYNTAXES IN C++}
# [BASICS SYNTAXES IN C++](#BASICS%20SYNTAXES%20IN%20C++) {#BASICS SYNTAXES IN C++ .header}
:::

[]{#BASICS SYNTAXES IN C++-Author}**Author**: Felix Okoronkwo\
[]{#BASICS SYNTAXES IN C++-Date}**Date**: \[19/8/23\]\
[]{#BASICS SYNTAXES IN C++-Description}**Description**: This section
will be about the basic operations in c++\

::: {#BASICS SYNTAXES IN C++-[[STATEMENTS]]}
### [](#BASICS%20SYNTAXES%20IN%20C++-%5B%5BSTATEMENTS%5D%5D)[STATEMENTS](STATEMENTS.html) {#[[STATEMENTS]] .header}
:::

defination :
:   this is the smallest independent unit of computaion in c++

``` {cpp=""}
  // statement in cpp
  std::cout << "Hello, World!" << std::endl;
```

most (but not all) statements in c++ end with a semicolon `;`.

::: {#BASICS SYNTAXES IN C++-[[FUNCTION AND MAIN FUNCTION]]}
### [](#BASICS%20SYNTAXES%20IN%20C++-%5B%5BFUNCTION%20AND%20MAIN%20FUNCTION%5D%5D)[FUNCTION AND MAIN FUNCTION](FUNCTION%20AND%20MAIN%20FUNCTION.html) {#[[FUNCTION AND MAIN FUNCTION]] .header}
:::

defination :
:   this is a collection of statements that are executed in order
    sequentially top to bottom.

Every c++ program must have a main function which is the entry point of
the program. the name of the function is always
[]{#BASICS SYNTAXES IN C++-[[FUNCTION AND MAIN FUNCTION]]-main}**main**.
function perform specific jobs.

``` {cpp=""}
  #include <iostream>             // preprocessor directive

  int main ()                     // main function
  {
    std::cout << "text";          // statement
    return 0;                     // return statement.
  }
```

::: {#BASICS SYNTAXES IN C++-[[COMMENTS]]}
### [](#BASICS%20SYNTAXES%20IN%20C++-%5B%5BCOMMENTS%5D%5D)[COMMENTS](COMMENTS.html) {#[[COMMENTS]] .header}
:::

Single line :
:   `// this is a single line comment`

Multiline :
:   `/** multiline comment ** /`

::: {#BASICS SYNTAXES IN C++-[[OBJECTS AND VARIABLES]]}
### [](#BASICS%20SYNTAXES%20IN%20C++-%5B%5BOBJECTS%20AND%20VARIABLES%5D%5D)[OBJECTS AND VARIABLES](OBJECTS%20AND%20VARIABLES.html) {#[[OBJECTS AND VARIABLES]] .header}
:::

C++ access memory for data manipulation through objects

[]{#BASICS SYNTAXES IN C++-[[OBJECTS AND VARIABLES]]-Object}**Object** :
:   Region of storage usually memory that can store data or a value and
    has other associated properties.

Objects can be named or anonymous. A named object is known as a
[]{#BASICS SYNTAXES IN C++-[[OBJECTS AND VARIABLES]]-variable}**variable**
and its name its known as an
[]{#BASICS SYNTAXES IN C++-[[OBJECTS AND VARIABLES]]-identifier}**identifier**

::: {#BASICS SYNTAXES IN C++-[[VARIABLE INSTANTIATION, DEFINATION, TYPES, ASSIGNMENT AND ASSIGNMENT]]}
### [](#BASICS%20SYNTAXES%20IN%20C++-%5B%5BVARIABLE%20INSTANTIATION,%20DEFINATION,%20TYPES,%20ASSIGNMENT%20AND%20ASSIGNMENT%5D%5D)[VARIABLE INSTANTIATION, DEFINATION, TYPES, ASSIGNMENT AND ASSIGNMENT](VARIABLE%20INSTANTIATION,%20DEFINATION,%20TYPES,%20ASSIGNMENT%20AND%20ASSIGNMENT.html) {#[[VARIABLE INSTANTIATION, DEFINATION, TYPES, ASSIGNMENT AND ASSIGNMENT]] .header}
:::

c++ is statically typed programing languaage and this means just like in
C a variable\'s type must be stated whenever defining a variable/object

``` {cpp=""}
  int a, b;
  double index;
  int c; double h;             // correct but not best practice
```

[]{#BASICS SYNTAXES IN C++-[[VARIABLE INSTANTIATION, DEFINATION, TYPES, ASSIGNMENT AND ASSIGNMENT]]-Instantiation}**Instantiation**:
at runtime programs are instatiated this is when objects and variables
are created and assigned a memory address for future manipulation or
access. variables must be instantiated bfoere the can be used to store
values. an instatiated object is called an
[]{#BASICS SYNTAXES IN C++-[[VARIABLE INSTANTIATION, DEFINATION, TYPES, ASSIGNMENT AND ASSIGNMENT]]-Instance}**Instance**.

[]{#BASICS SYNTAXES IN C++-[[VARIABLE INSTANTIATION, DEFINATION, TYPES, ASSIGNMENT AND ASSIGNMENT]]-Datatypes}**Datatypes**:
datatypes of an obkject or variable must be known at compile time and
variables onl stored the data of the same datatype as the variable
itself, as stated above
([]{#BASICS SYNTAXES IN C++-[[VARIABLE INSTANTIATION, DEFINATION, TYPES, ASSIGNMENT AND ASSIGNMENT]]-statically-typed}**statically-typed**).

[]{#BASICS SYNTAXES IN C++-[[VARIABLE INSTANTIATION, DEFINATION, TYPES, ASSIGNMENT AND ASSIGNMENT]]-Varible structure}**Varible
structure**: variables possess an
[]{#BASICS SYNTAXES IN C++-[[VARIABLE INSTANTIATION, DEFINATION, TYPES, ASSIGNMENT AND ASSIGNMENT]]-identifier}**identifier**,
[]{#BASICS SYNTAXES IN C++-[[VARIABLE INSTANTIATION, DEFINATION, TYPES, ASSIGNMENT AND ASSIGNMENT]]-type}**type**
and
[]{#BASICS SYNTAXES IN C++-[[VARIABLE INSTANTIATION, DEFINATION, TYPES, ASSIGNMENT AND ASSIGNMENT]]-value}**value**.

[]{#BASICS SYNTAXES IN C++-[[VARIABLE INSTANTIATION, DEFINATION, TYPES, ASSIGNMENT AND ASSIGNMENT]]-Variable declaration}**Variable
declaration**: telling the compiler that a variable exists without
allocating memory for it.

[]{#BASICS SYNTAXES IN C++-[[VARIABLE INSTANTIATION, DEFINATION, TYPES, ASSIGNMENT AND ASSIGNMENT]]-Variable defination}**Variable
defination**: telling the compiler that a variable exists and allocating
memory for it.

[]{#BASICS SYNTAXES IN C++-[[VARIABLE INSTANTIATION, DEFINATION, TYPES, ASSIGNMENT AND ASSIGNMENT]]-Variable assignment}**Variable
assignment**: cassigning a value for a variable to hold in its storsge
after defination.

``` {cpp=""}
  extern int declared;
  int defined;
  defined = 0;                //assigned.
  defined = 69;               // re-assignment to 69
```
