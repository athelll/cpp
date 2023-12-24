= Control Flow and Error Handling =
= Felix Okoronkwo, Nov 12, 2023 =

 Control flow introduction 
=========================================================================
if statements
-----------------------------------------------
syntax:
```cpp

// syntax 1
if (condition)
  execution_statement;

// syntax 2
if (condition)
  true_statement;
else
  false_statement;

//syntax 3
if (condition)
  true_statement_edgecase1;
else if (consition_2)
  true_statement_edgecase2;
else
  false_statement;

// all this can be used with brackets.

```

- prevent the dangling else problem and reduce ambiguity by using brackests when declaring if blocks.

Null statements
-----------------------------------------------
A null statement is an expression statement that consists of only a semicolon, they do nothing

```cpp
  if (x > 6)
    ;           // this is a null statemnet.
```

if null statemnt are used carelessy hey can lead to problems:
```cpp
if (nuclearCodesActivated());
  blowUpTheWorld();
```

on close inspection of the code above its seen that theres a semicolon directly at the end of the if statemnt declaration which can
be interpreted as:
```cpp
if (nuclearCodesActivated())
  ;                               // null statement
blowUpTheWorld();
```

in this case the function `blowUpTheWorld()` is always executed. (probably not what the developer,or you even, wanted)

Constexpr if statements
-----------------------------------------------
its wasteful to compare constant variables with if/else statemnets because, dure to the fact their are constant they would always
execute one side of the consitional and leave the other never to be executed.

so `constexpr conditionals` where introduced in c++17, they are used to compare constant expressions and optimize to only compile the boolean
evaluated statement corresponding to the result of the constant expression conditional.

example:
```cpp
int main()
{
  constexpr double gravity{ 9.8 };

  if constexpr (gravity == 9.8)
    std::cout << "we are on earth\n";
  else
    std::cout << "on some other planet\n";
}
```

this code would be optimized to only be compiled into:
```cpp
int main()
{
  std::cout << "we are on earth\n";
}
```

Switch statement basics
-----------------------------------------------
sntax:
```cpp

int main()
{
  int x { randomGenerator( int limit { 10 } ) };

  switch (x)
  {
    case 1:
      // execute for value 1
      break;
    case 2:
      // execute fro value 2
      break;
    case 3:
      // execute fro value 3
      break;
    default:
      // execute if no matches were made for the above labels.
      break;
  }
}
```

- the `break` keyword can be ised to terminalte immediately from a switch statement.
- Prefer switch statements over if-else chains when there is a choice.
- sstes of statements in a witch stament should end ithe a `return` or break statement.

Switch fallthrough and scoping
-----------------------------------------------
the presence of another case label in a switch statemnt after a previous label was matches is not a terminating condition in a switc state-
ment, swtch statemnst tend to execute other case labels that follow after a matched case label, this is known as Fallthrough.

And this is why its advised to have a `return` or `break` statement in the body of all case labels in a switch statement.

The Fallthrough attribute
-----------------------------------------------
the fall through attrubute was intriduced in c++ to notify the compiler that the developer intend on allowing a fallthrough
occur when used in conjuction with a `null statemnet` in a switch statement. this prevents the compiler from throwing any warnings and
allows a fallthrough occur.
```cpp

#include <iostream>

int main()
{
  switch(2)
  {
    case 1:
      std::cout << 1 << '\n';
      break;
    case 2:
      std::cout << 2 << '\n'; // execution begins here
      [[fallthrough]];        // intentional fallthrough -- semicolon to indicate null statement
    case 3:
      std::cout << 5 << '\n'; // this also executes.
      break;
  }

  return 0;
}

```

Sequential case labels
-----------------------------------------------
when coparing the equality of a variable with differnt values this can be done with an OR if statemnt like so:
```cpp
  bool isVowel(char c)
  {
    return ( c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' );
  }
```

this evaluates correctly but the problem is that c has to be evaulated multiple times leading to extra computations.
this can be solved with a switch statemnet as so:
```cpp
  bool isVowel(char c)
  {
    switch(c)
    {
      case 'a':
      case 'e':
      case 'i':
      case 'o':
      case 'u':
        return true;
      default:
        return false;
    }
  }
```

this is more efficient, readable, memory friendly and less computations are needed because the value of c is only evaluated once and
compared with each of the switch labels, unlike the equality comparaison operator, which evaluates its operands each time invoked.

This is not considered fallthrough behavior, so use of comments or `[[fallthrough]]` is not needed here.

Switch case scoping
-----------------------------------------------
the content of case labels are not implicitly scoped (like in the case of single statement if statements), so the contents of each labels
belong to the scope of the main switch statement that they belong to.

```cpp
switch (1)
{
  case 1:     // does not create an implicit block
    foo();    // this is part of the switch scope, not an implicit block to case 1
    break;    // this is part of the switch scope, not an implicit block to case 1
  default:
    std::cout << "default case\n";
    break;
}
```

Variable declaration and initialization inside case statements
-----------------------------------------------
you can declare or define a variable in a switch statement but not initialize, whether before or after case labels.

```cpp
switch (1)
{
  int a;          // okay perfectly legal
  int b{ 7 };    // illegal not allowed

  case 1:
    int c;        // okay legal - bad practice tho.
    c = 8;        // legal - assignment is allowed.
    break;

  case 2:
    int d{ 4 };   // illegal - initialization not allowed.
    c = 2;        // allowed c was defined before.
    break;

  case 3:
    break;
}
```

Reasons why initiaization is illegal in switch statements:
-----------------------------------------------
due to the fact that variables initilization occur at runtime and the value to be initilized with must be known and switch statments start
execution from the first matched case (making it that whatever in the previous case labels are not executed) imagine that initilization
was declared in one of those previous label cases, initialization will not occur. Because of this c++ only allows initialization occur in
the last default label case becuase it must always execute.

If a case needs to define and/or initialize a new variable, the best practice is to do so inside an explicit block underneath the case statement:

```cpp
switch (1)
{
  case 1:
  {
    int x{4};               // variables can be initialized in a block.
    std::cout << x << '\n';
    break;
  }
  default:
    std:cout << "default case\n";
    break;
}
```

- If defining variables used in a case statement, do so in a block inside the case.


 Goto statements 
=========================================================================
goto statements are uncoditional jumps that move the execution to another part in the code. It's unconditional because it will always
execute when called.

it should be avoide cos its leads to spaghetti code. Avoid goto statements (unless the alternatives are significantly worse for code readability).

syntax:
```cpp
#include <iostream>
#include <cmath>

int main()
{
  double x{};
tryAgain:          // this is a statement label that can be gone to
  std::cout << "Enter a non-negative number: ";
  std::cin >> x;

  if (x < 0.0)
    goto tryAgain; // this is the goto statement

  std::cout << "The square root of " << x << " is " << std::sqrt(x) << '\n';
  return 0;
}
```


 Introduction to loops and while statements 
=========================================================================
- Integral loop variables should be signed


 Do while statements 
=========================================================================
this are while statements in which the statements contained in them exexutes at least one and continues re-executing if the conditional (its evaluating)
evaluates to true.

syntax:
```cpp
do
  statements;                 // can be a singular or compound statement,
while ( conditional );
```

while loops are to be favoured over them if given an equal stance to be implemented.


 For statements 
=========================================================================
syntax:
```cpp

for (init_expression, condition, end_expression)
  statements;

```

init_expression   : this is used for variable declaration that will be utilized in the loop and destroyed after the loop is done (loop scoped), it only executes once.
condition         : this is the conditional to be tested within every loop to continue the loop execution of evaluating to true.
end_expression    : this is the expression that is executes at the end of every iteration, it is usually used to modify the init_expression variables to conttibuter to the
                    logic of thr loop (decremnting or incrementing counting varibales spawned from the init_expression, etc.)


infintie for loop:
```cpp
for (;;)
  statements;
```

For loops with multiple counters
-----------------------------------------------
For loops also work with multiple counters.
syntax:
```cpp
#include <iostream>

int main
{
  for (int x{ 0 }, y{ 10 }; x > 10; ++x, --y)
    std::cout << x << ' ' << y << '\n';

  return 0;
}
```

- This is about the only place in C++ where defining multiple variables in the same statement,
  and use of the comma operator is considered an acceptable practice.

Breaks and Continues
-----------------------------------------------
- Use break and continue when they simplify your loop logic.
- Use early returns when they simplify your function’s logic.


 Halts (exiting your program early) 
=========================================================================
read [[www.learncpp.com/cpp-tutorial/halts-exiting-your-program-early/]]

- `std::exit()`: makes sure your program terminates mormally (doesnt mean the program can't return an error code, or perfrom wrongly).
  this functon does not cleanup local varibales and such calling it explicitly (by default at the end of avery main function it is called), is
  not advised. it does clear up static durated variables, file cleanups and returns control back to the OS tho. but doesn not cleanup up local variblaes and
  dynamiclly allocated data.

- `std:atexit()`: this function does the same as the `std::exit()` function but it akllows us to pass in a cleanup function as a parameter, in case you want the
  termination of a program to always perform some optimization and cleanup tasks before finally terminating. . In this context, cleanup means things like closing
  database or network connections, deallocating any memory you have allocated, writing information to a log file, etc…

  the function to be passed into `atexit()` must take no parameters and have no return value. you can register multiple cleanup function they are called in
  reverse order.

- `std::quick_exit()`: this halt function terminaltes the program noramlly but doesnot cleanupt static varibales incase multithreading is in play and
  some threads depend on a static variable, this prevents the threads from crashing or being error prone.

- `std::abort()`: this cause your program to terminate abnormally, does not do any cleanup.

- `std::terminate()`: its usually called in conjuction with exceptions (would be explained in details later).

- Only use a halt if there is no safe way to return normally from the main function. If you haven’t disabled exceptions, prefer using exceptions
  for handling errors safely.


 Introduction to testing your code 
=========================================================================
Testing a small part of your code to ensure that unit of code is working is known as unit testing.

Preserving your tests
-----------------------------------------------
when we write test and come to the conclusion that it was suffucent in testing what was to be tested. its ideal to preserve thoes
test instead of wiping them off after they validate our code (in case of adding new features to our existing code and wanting to make
sure no ripple effect that might break the code occured, this is why we preserve them). this can be done by movng the tests to a function.

example:
```cpp
#include <iostream>

bool isLowerVowel(char c)
{
  switch(c)
  {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
      return true;
    default:
      return false;
  }
}

int testVowelFunc()
{
  if (!isLowerVowel('a')) return 1;
  if (isLowerVowel('q')) return 2;

  return 0;
}

int main()
{
  return 0;
}
```

 Handling Errors in c++ 
=========================================================================
Fatal errors
-----------------------------------------------
if an error is so bad that the porgram cannot continye to runas long as this error has occured this is known as a fatal error or a non-recoverable error.
IN such cases its best to just terminate the program, if your in main() you easily terminate using a return non-zero-code status but if not ( like you in some
deep nested subfunction) a halt statement can be used. (such as `std::exit()`)

example:
```cpp
double doDiviison(int x, int y)
{
  if (y == 0)
  {
    std::cout << "ERROR: Can't divide by zero\n";
    std::exit(1);
  }
  return static_cast<double>(x) / y;
}
```

Exceptions
-----------------------------------------------
will be covered later.


 std::cin and handling invalid input 
=========================================================================
A program that handles error cases well is said to be robust.

types of invalid text inputs
-----------------------------------------------
- inout extraction succeeds but input is uselss to the prgram
- input extraction succed but the user inputes additional data into the buffer
- input extraction fails (inouttung 'q' into a numerical variable)
- input extraction succeeds but the user overflows a numeric value.

handling the above situations
-----------------------------------------------
1) write code that only runs with the needed input to be compared with to work: like using a switch statement if its a finite number if expected input to execute if
   theres a match between the label cases and the input.
2) the `std::cin.ignore(characters_count_to_ignore, delimeter)` function is pretty useful to clear the buffer to ensure nothing is stored after using it.
  to use the maximum amount of characters to be ignored we can use the `std::numeric_limits`, to get the max number a bufferstream can store and use that to clear
  the buffer after usage.

example:
```cpp
#include <limits>
#include <iostream>

#define OPTIMIZED 1
void ignoreExtra()
{
#ifdef OPTIMIZED
  // clears the buffer completely (uses the maximum character limit of the input stream buffer) after an extraction
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
#else
  // clears the first 100 characters in the buffer, not effective because if more than 100 characters afe in the buffer UB can occur.
  std.cin.ignore(100, '\n');  // also introduces a magic number.
#endif
}

int main()
{
  char char_one{};
  char char_two{};

  std::cin >> char_one;
  ignoreExtra();
  std::cin >> char_two;
  ignoreExtra();
}
```

the `std::cin.ignore()` function works by clearing the secified count of characters until within the specified delemiter, the clears the dekimeter to

3) when a bad input to an unmatching typed variable variable was extracted with the `std::cin` or an overflow was caused with ustilizing the `std::cin`
   it can enetr a state known as failure mode: when in failure mode subsequent calls fro extraction in frin the cin buffer is ignored but the bad input
   that caused the failure mode is stil stored in the buffer, luckily we can detect this and switch from failure mode to normal mode as follows:

```cpp
if (std::cin.fail())
{
  std::cin.clear();
  ignoreExtra();
}
```
all this can be added to ensure that on the venture that cin enters failure mode it can be handled:
```cpp
double getDouble()
{
  double x{};

  while(true)
  {
    std::cout << "Enter decimal number ";
    std::cin >> x;
    if (!std::cin)
    {
      std::cin.clear();
      ignoreExtra();
    }
    else
    {
      ignoreExtra();
      return x;
    }
  }
}
```

4) if the cin buffer was closed due to encountering a fatal input that leads to something far worse that failure mode, it closes itself,
   one of the events that can trigger this is trying to store a value that can lead to an overflow. this can be resolved by:
```cpp
// previous code that handles input
  if (!std::cin)
  {
    if (std::cin.eof())   // this checks if thebuffer is closed, if yes terminates the program normally.
      exit(0);

    std::cin.clear();     // places the cin buffer back into normal mode.
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // removes errorneous input.
  }
// code continuation
```


 Assert and static_assert 
=========================================================================
preconditions - this are conditrions tat must be true before a computation can occur
invariant     - this are condition that must be true while a specific computation occurs.
postcondition - this are condition that must be true after a compution has ran.

ultimately they all exist to ensure that the program executes correctly.

Assertions
-----------------------------------------------
c++ offers a shortcut for performing if condition iuput assesments to ensure correct state of variables for a computation to execute.
this is done using c++ `assertions`

An assertion is a boolean exoressions that will always be true unless theres a bug in the program, if the asertion evaluates to true nothing happens
if not the program is terminated (via  `std::abort()`) and an error message is printed with info about the termination and (possibly) its cause.

runtime assertions
-----------------------------------------------
the runtime assertions are implemented via the assert preprocessore macro in the `<cassert>` header

```cpp
#include <cassert>
#include <cmath>
#include <iostream>

double groundHitTime(double initialHeight, double gravity)
{
  assert(gravity > 0.0);

  if (gravity == 0.0)
    return 0.0;

  return std::sqrt((2.0 * initialHeight) / gravity);
}

int main()
{
  double height{ 7.90e3 };

  std::cout << "ball is as height: " << height << " touching ground in " << goundHitTime(height, 9.8) << "secs\n";
}
```

theres a trick to add descpritive messages with the assert macro:

as we know that all objects or variables if evaluated as booleans will evaluate to true,
as long as an object or variable does not numerically evaluate to 0 (false), it will always be true (even strings),
meaning if a string was used as a conditional for an expected boolean return: it would return true.

therfore:
```cpp
assert( (gravity < 0) && "the height cannot be negative, its nonsensical" );
```

if the first conditional returns true nothing happens and the program continues. But if not: the string
would be added to the asserts error message.
and with that descriptive messages can be added to asserts.

- use assertion to documanet cases that should be logically impossible

NDEBUG
-----------------------------------------------
using assertion come with a minute performance cost,  so assertions sould never be used in production code.
the `NDEBUG` macro was implemented to disable assertions if defined. meaning that if assertions where used in your code they can be diabled
by defining this macro.

- note that the `assert` macro wen usesd terminates the program with the `abort()` halt function meaning the program is termionated immmediately 
  and leaves no time for cleanup or closing databases or stuffs like that, meaning that `asset` should only be used when there wpuld be no consequences if the
  program abruptly shuts down.

static_assert
-----------------------------------------------
the `static_assert` is used to perform compile-time assertions meaning its shlould be used in compile time contexts. unlike that assert macro
thats defined in the `<cassert>` header `static_assert` is a keyword so no header needs to be included.

syntax:
```cpp
static_assert(boolean_condition, diagnostic_message);
```

is the condition is not true the diagnostic_message is printed

notes about `static_assert`:
- it must be used with, by and in the context of constant espressions.
- static assertion can be placed anywhere in the code files.
- it is not compiled in release builds.
- <= c++17 makes placing a diagnostic message optional unlike in previous versions wher it was a must.


 Introduction to random number generation 
=========================================================================
An algorthim is a finite sequence of instructions that can be used to solve a problem or complete a task.

an algorithm is known to be `stateful` if it retains some kind of information within succesive calls.
A `stateless` algorithm does not store any information as its being used (must be given all the information it needs to work).

an algorithm is known to be determinstic if for a given input it would always produce he same output sequence.

Pseudo-random number generators (PRNGs)
-----------------------------------------------
a PRNGs is an algorithm that generates a sequence of numbers that mimics the sequence of randomness.

simple PRNG algo implemetation:
```cpp
unsigned int LCG16()
{
  static int s_state{ 5323 };

  // generate the next state by introducing overflows in the computaions to make it seem more random

  s_state = 8253729 * s_state + 2396403;
  return s_state % 32768;                   // added randomness.
}

int main()
{
  for (int count{ 1 }; count <= 100; ++count)
  {
    std::cout << LCG16() << '\t';

    if (count % 10)
      std::count << '\n';
  }
  return 0;
}
```

this algorithm is a very bad random generator. should not be used. because at critcial (or maybe obvious) examination its deterministic.

when a PRNG is initiated a value or list of values is used to insantiate he PRNG they are known as `random seeds or seeds` for short.
when a value is used to initate a seed its known as a `seeded PRNG`.

most PRNGs that produce quality results are usually seeded with values of 16 bits (if not more).

the size of the seed can be samller than the state of the PRNGs if this happens the PRNGs is known to be `underseeded`.

What makes a good PRNG?
-----------------------------------------------
- the PRNGs shokd generate numbers with approx. almost the same probabilty. this is known as `distribution uniformity`
- the method that the next number is generated in the sequence should not be predictable.
- a good PRNG should have a good dimensional distrubution of numbers. meaning it should be able to generate odd, even, large, small etc. numbers at random.
- A good PRNGs should have a high period for oys seeds. A period is the length of sequences before a PRNGs starts to repeat.
- The PRNG should be efficient

Randomization in C++
-----------------------------------------------
the randomization capabilities in c++ are acessed with the `<random>` header of the standard library, there are 6 PRNGs families
available for use since c++20

read this for more info on the `<random>` header content: [[https://www.learncpp.com/cpp-tutorial/introduction-to-random-number-generation/#random]]

the most preferred PRNGs that is used where non-predictability isnt extremmely crucial is the mersenne twister.
its downside is that its later sequences can be predicted after examining its first 624 generated numbers. making it a no go for applications
that require non-predictability.

if your writing an application where non-prefictability is required your better off using a thid party library like:
1) The Xoshiro family and Wyrand for non-cryptographic PRNGs.
2) The Chacha family for cryptographic (non-predictable) PRNGs.

Mersenne twister
-----------------------------------------------
it belongs to the `<random>` header and it consists of 2 types:
1) mt19974      : generates 32 bits unsigned integers.
2) mt19974_64   : generates 64 bits unsigned integers.

using tehr mersenne twister is straight forward:
```cpp
#include <random>
#include <iostream>

int main()
{
  std::mt19974 mt{};                  // instantiate on 32-bit mersenne twister object

  for(int i{ 1 }; i <= 50; ++1)
  {
    std::cout << mt() << '\t';        // genreate a random number

    if (i % 5 == 0)
      std::cout << '\n';
  }
  return 0;
}
```

it might be odd calling a variable as a function in the above code but the `mt()` syntax is a short form of calling `mt.operator()`, for this random object types
the `operator()` function returns the next pseudo randomly generated sequence of the function being called. it more of a shorthand convention designed with
this random genreating types in the `<random>` header.

adding uniform distibution limits to the mersenne twister
-----------------------------------------------
usually a 32 but mersenne twister will generate numbers from 0 to 4,294,967,295, but we dont always want numbers of that large of a range and sometimes
requre a limit. this limit is added using a uniform distribution. PRNGs on theirn own cant add uniformly distibuted limits so their outputs are placed in functiona that can.

this is done by using the random libraries random number distribution.

random number distributions convert the the output of a PRNGs to a specified number distribution.
there are a lot of random number distributions use for statistial analysis but theres one useful for normal random distibutions:
in this case we can use the `uniform distibution` what it does is that it takes in two numbers, and produces outputs between numbers x and y (x and y inclusive)
all with equal probability.

theres a program that uses the uniform distribution to simulate the roll of 6 sided dice:

```cpp
#include <random>
#include <iostream>

int main()
{
  std::mt19974 mt{};
  std::uniform_int_distribution die{1, 6};    // uniform distributor for numbers 1 - 6 (1 and 6 inclusive)

  for(int count{1}; count <= 40; ++count)
  {
    std::cout << die(mt) << '\t';

    if (count % 10 == 0)
      std::cout << '\n';
  }
  return 0;
}
```

on subsequent calls to the compiled executable of this code, it will be noticed that subsequent calls generate the same "random" numbers which is not very random-isque.
to fix we need to seed the misernne twister with a random input on each call to create pseudo-random-num-generating functions. Since we cant just compute a random action
, we are in a kind of catch 22, but we can introduce changing variables to emulate the feel of randomness. luckily the pseudo-random-number generators do
not actually need a random seeds to spawn differnt outputs what it needs precisely is a changing seed with every call can be achieved using some attributes of our system like:
1) the systems clock
2) or the systems random device (/dev/random on linux, at least i think thats a linux random device)

Seeding with the system clock
-----------------------------------------------
the system clock can be used as changing seed whem instatiating a misernne twister, but the units of time measuremnet must be very small, messured in ticks;
how this works is that some function in the `<chrono>` header retrieves the time exuded after the earliest time recorded. ticks are really small
like in nano-seconds or milli-seconds: they are then used as seed to instantiate the PRNGs. the reason they are so small is to prevent being seeded with the same seed
after successive calls to the PRNG has been made with little time differences.

example:
```cpp
#include <isotream>
#include <random>
#include <chrono>

int main()
{
  std::mt19937 mt{ static_cast<std::mt19937::result_type> (std::chrono::steady_clock::now().time_since_epoch().count()) };
  std::uniform_int_distribution die6{1, 6};

  for (int count{ 1 }; count <= 50; ++count)
  {
    std::count << die6(mt) << '\t';

    if (count % 10 == 0)
      std::cout << '\n';
  }
  return 0;
}
```

the above program gives us access to the clock using the `<chrono>` header and it allows us to seed the mt using the current time on our system.

the downside of this approach is that if the succesive calls are called almost immediateley with no or incredibly minute time discrepancies, it might yield the same result
which can be a problem for statistical computations and models but not for normal random computations.
but for programs that require high quality, independent results, this method of seeding may be insufficient.

<!--BUG: ALL MY FUCKING NOTES FROM HERE ARE GONE FUVK! -->

any how ill just continue.

Random numbers across multiple functions or files (Random.h)
-----------------------------------------------
this is done with namespaces and inline variables in the header file.
read up the details heres ince the notes where lost: [[http://www.learncpp.com/cpp-tutorial/generating-random-numbers-using-mersenne-twister/#RandomH]]

```cpp
#ifndef RAND_H
#define RAND_H

#include <chrono>
#include <random>
#include <iostream>

// create namespace that PRNG will be acessed from
namespace Random
{
  // create seed generator
  inline std::mt19937 generateSeed()
  {
    std::random_device rd{};
    std::seed_seq ss{
      static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()),
      rd(), rd(), rd(), rd(), rd(), rd(), rd()
    };
    return std::mt19937{ ss };
  }

  // create static single global PRNG
  inline std::mt19937 mt{ generateSeed() };

  // create get function to get random numbers with limits
  inline int get(int min, int max)
  {
    return uniform_int_distribution{min, max}(mt);
  }

  // template version of get function for arguments that are not types int, where T is the type.
	template <typename T>
	T get(T min, T max)
	{
		return std::uniform_int_distribution<T>{min, max}(mt);
	}

  // template version that converts arguments of differnt type (min and max diff. types) to one type and return in the converted type.
	template <typename R, typename S, typename T>
	R get(S min, T max)
	{
		return get<R>(static_cast<R>(min), static_cast<R>(max));
	}
}

#endif
```

ussage:
```cpp
#include "random.h"

int main()
{
  for(int count{ 1 }; count <= 40; ++count)
  {
    std::cout << random::get(1, 20) << '\t';
    if (count % 10)
      std::cout << '\n';
  }
}
```

