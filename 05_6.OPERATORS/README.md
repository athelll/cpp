= Operators =
= Felix Okoronkwo Nov 1 =

 Relational operators and floating point comparisons 
=========================================================================
- Comparison computations with floating points cannnot trusted, especially when the values being compared are calculated and almost
  identical
```cpp
  #include <iostream>
  #include <iomanip>

  int main()
  {
    double one_d { 100.0 - 99.99 };    // 0.01
    double two_d { 10.0 - 9.99 };      // 0.01

    bool is_equal = (one_d == two_d) ? true : false;
    std::cout << std::boolalpha << std::setprecision(17);
    std::cout << one_d << " is " << is_equal <<"ly equal to " << two_d << '\n';
  }
```

- the above snippet should evaluate incorrectly, mathematically. but it doesn't.
- comparson with floats are okay when cpmparing low-presiscion floating point literals to the same literal value of
  the same type, example.
```cpp
  int main()
  {
    constexpr double gravity { 9.8 };

    if (gravity == 9.8)                                 // this will evaluate to true
      std::cout << "we are on earth" << '\n';
  }
```

exponent operator
-----------------------------------------------
exponent is done in cpp with the `std::pow(base, exponent)` function in the `<cmath>` header,
due to the rounding error nature of floats `std::pow` is not usually accurate even when passing integers in as arguments.
To fix this is better you use and implement your own function.

the beloe function does exponentiation using the `exponentiation by squaring algorithm`:
```cpp
  #include <cassert>                                                  // for assert
  #include <cstdint>                                                  // for std::int64_t
  #include <iostream>

  // NOTE: exp must be non-negative
  // NOTE: does not perform range/overflow checking, use with caution
  constexpr std::int64_t powint(std::int64_t base, int exp)
  {
    assert(exp >= 0 && "powint: exp parameter has negative value");

    // Handle 0 case
    if (base == 0)
      return (exp == 0) ? 1 : 0;

    std::int64_t result{ 1 };
    while (exp > 0)
    {
      if (exp & 1)                                                     // if exp is odd
        result *= base;
      exp /= 2;
      base *= base;
    }
    return result;
  }
```

The above version does not check for overflows, the below one does:

```cpp
#include <cassert>
#include <cstdint> // for std::int64_t
#include <iostream>
#include <limits>

/**
 * A safer (but slower) version of powint() that checks for overflow
 * note: exp must be non-negative
 * Returns std::numeric_limits<std::int64_t>::max() if overflow occurs
 */

constexpr std::int64_t powint_safe(std::int64_t base, int exp)
{
  assert(exp >= 0 && "powint_safe: exp parameter has negative value");

  // Handle 0 case
  if (base == 0)
    return (exp == 0) ? 1 : 0;

  std::int64_t result { 1 };

  // To make the range checks easier, we'll ensure base is positive
  // We'll flip the result at the end if needed
  bool negativeResult{ false };

  if (base < 0)
  {
    base = -base;
    negativeResult = (exp & 1);
  }

  while (exp > 0)
  {
    if (exp & 1)
    {
      // Check if result will overflow when multiplied by base
      if (result > std::numeric_limits<std::int64_t>::max() / base)
      {
        std::cerr << "powint_safe(): result overflowed\n";
        return std::numeric_limits<std::int64_t>::max();
      }
      result *= base;
    }

    exp /= 2;

    // If we're done, get out here
    if (exp <= 0)
      break;

    // The following only needs to execute if we're going to iterate again

    // Check if base will overflow when multiplied by base
    if (base > std::numeric_limits<std::int64_t>::max() / base)
    {
      std::cerr << "powint_safe(): base overflowed\n";
      return std::numeric_limits<std::int64_t>::max();
    }

    base *= base;
  }

  if (negativeResult)
    return -result;

  return result;
}
```

commma operator
-----------------------------------------------
the comma operators allows us to declare multiple expressions wherever a single statement is allowed. its evalauates the left operand
then the right one and return the value of the right one to the statement that declared it.

Example:
```cpp
  int main()
  {
    int x{ 3 };
    int y{ 4 };
    int comma_result{};

    comma_result = (++x, ++y);                    // comma_result evaluates to 5 the pre-increment of the second operand, y.
  }
```

Comparing floating point numbers (advanced reading)
-----------------------------------------------
Custom function where you define your absolute range itself (epsilon) and `Donald Knuth` algorithm (deals with relative epsilon)

```cpp
  #include <cmath>
  #include <algorithm>

  // custom, most beginner c++ alternative
  double approxEqual(double num1, double num2, double absEpsilon)
  { return std::abs(num1 - num2) <= absEpsilon; }

  // Donald Knuth Algorithm for float equality comaprison
  double knuthEstimate(double a, double b, double relEpsilon)
  { return std::abs(a - b) <= (std::max(std::abs(a), std::abs(b)) * relEpsilon) }

```

- knuths algorithm instead of epsilon being an arbirary number you can pick, it becomes a relative number to a and b
- the issue with knuth algo is that it breaks down when the difference between the values being compared significantly approaches
  zero to solve this, both the absolute Epsilon and relative epsilon functions (Knuths own), needs to be merged into one
  so:
    1) it can handle numbers significantly approaching to zero with absolute epsilons like `1e-12`
    2) if that fails, falls back to knuths approach to resolve it.


```cpp
  bool approximatelyEqualAbsRel(double a, double b, double absEpsilon, double relEpsilon)
  {
    // Check if the numbers are really close -- needed when comparing numbers near zero.
    if (std::abs(a - b) <= absEpsilon)
      return true;

    // Otherwise fall back to Knuth's algorithm
    return knuthEstimate(a, b, relEpsilon);
 }
```

- when using the abive algorithm using aboslute epsilon `1e-12` and relative epsilon `1e-8`, should be okay for most cases:
```cpp
  constexpr double relEps { 1e-8 };
  constexpr double absEps { 1e-12 };
```

when making the float comparison function `constexpr` and using it in a `constexpr` context (storing the result of the comaprison
in a `constexpr variable`).
We might run into an issue that the variable should only store `constexpr` values. This is because in a version update of c++ `std::abs`
was made a `non-constexpr` function, therby making any dependecny on it non-compile-time.

This is easily fixed by by implementing our on absolute function.


 Logical operators 
=========================================================================
| Operator                               | Symbol | Symbolic Name |
|----------------------------------------|--------|---------------|
| Logical NOT                            |   !    | not           |
| Logical AND                            |   &&   | and           |
| Logical OR                             |   ||   | or            |
| Logical XOR (mimic for only booleans)  |   !=   |               |

Short Circuit evaluation
-----------------------------------------------
When the AND logical operand is used: it evaluates the left operand first, if it evaluates to `true` the next operand is then evaluated to
get the resultant of the boolean operation. if the the left operand evaluating to `true` is not the case, the whole and operation short-circuits
and returns `false`, without even evaluating the right operand.

```cpp
  int x { 7 };
  int y { 1 };

  if (x == 1 && ++y == 2)
    // do something
```

in the above snippet the if block would evaluate immediately to false because the left operand is false. and it does this without even
evaluating the right operand (incrementing the y object), so in this case, because of the short-circuit nature of the AND operator, the right
operand is never evaluated (which might be something the programmer has envisioned must happen). so keep this in mind felix.

Logical XOR (!=)
-----------------------------------------------
| x     | y     | result |
| true  | true  | false  |
| true  | false | true   |
| false | true  | true   |
| false | false | false  |

Logical XOR only evaluates to true when one of the operands is the negation of the other. This is the only condition for a truthy result.
therefore logical XOR `true` and `true` is false.

To perform logical XOR on non-boolean objects static cast can be used to cast them to boolean:
```cpp
  if (static_cast<bool>(a) != static_cast<bool>(b) != static_cast<bool>(c)) // a XOR b XOR c, for types that can be converted to bool
    // do shit
```

this can alos be achieved useing the double negation operand to convert to bool`!!`:
```cpp
  if (!!a != !!b != !!c != !!d)
    // do shit
```

using the alternate name of logical operators
-----------------------------------------------
```cpp
  std::cout << !a && (b || c);
  std::cout << not a and (b or c);
  // both are the same and evaluate to the same boolean
```

