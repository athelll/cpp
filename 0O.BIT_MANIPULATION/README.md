= Bit Manipulation =
= Felix Okoronkwo Nov 2, 2023 =


 Bit flags and bit manipulation via std::bitset 
=========================================================================
When the individual bits of an object are used as boolean values, the bits are known as `bit flags`.

declaring bit flags
```cpp
  #include <bitset>

  std::bitset<8> mybitset {};
```

<!--NOTE: Bit Manipulation is one of the times you should unambigiously use unsigned integers -->

Manipulating bits via std::bitset
-----------------------------------------------
`std::bitset` provides 4 key functions useful for perfroming bit manipulation.
1) test()     : allows us to query wether a bit is 0 or 1
2) set()      : allows us to turn a bit on (will do nothing if bit is already on)
3) reset()    : allows us to turn a bit off (will do nothing if bit is already off).
4) flip()     : allows us to flip a bit number from 1 to 0 and vice versa

Example:
```cpp
  #include <bitset>
  #include <iostream>

  int main()
  {
    std::bitset<8> myBits { 0b0000'0101 };
    myBits.set(3);        // 0000 1101
    myBits.flip(4);       // 0001 1101
    myBits.reset(4);      // 0000 1101

    std::cout << "all the bits are: " << myBits << '\n';
    std::cout << "bit 3 has the value " << myBits.test(3) << '\n';
    std::cout << "bit 4 has the value " << myBits.test(4) << '\n';
  }
```

Giving our bits names can help make our code more readable:
```cpp
  #include <bitset>
  #include <iostream>

  int main()
  {
    [[maybe_unused]] constexpr int isMoving       { 0 };
    [[maybe_unused]] constexpr int isAlive        { 1 };
    [[maybe_unused]] constexpr int isEating       { 2 };
    [[maybe_unused]] constexpr int isExcreting    { 3 };
    [[maybe_unused]] constexpr int isReproducing  { 4 };
    [[maybe_unused]] constexpr int isAsleep       { 5 };
    [[maybe_unused]] constexpr int isGrowing      { 6 };
    [[maybe_unused]] constexpr int isDead         { 7 };

    std::bitset organism { 0b0000'0000 };
    organism.set(isAlive);
    organism.set(isMoving);
    organism.set(isReproducing);

    std::cout << "organisms bit state " << organism << '\n';
    std::cout << "organsim mortal state: " << organism.test(isDead) << '\n';

    return 0;
  }
```

The size of std::bitset
-----------------------------------------------
std::bitset wasnt designed for memory optimization, it was designed for efficiency and speed, so the size is the number of bits needed to hold
the bits, rounded to the neareset `sizeof(size_t)`, which is 4 bytes on 32-bit machines and 8 bytes on the 64-bit machine.

querying bitset
-----------------------------------------------
1) size()   : returns the number of bits in the bitset.
2) count()  : returns the number of bits in a bitset that are set to true.
3) all()    : returns a boolean indicating if all bits are true.
4) any()    : returns a boolean indicating if any bits are set to true.
5) none()   : returns a boolean indicating whether no bits are set to true.


 Bitwise operators 
=========================================================================
| Operator    | Symbol | Form   |             Operation              |
|-------------|--------|--------|------------------------------------|
| left shift  | <<     | x << y | all bits in x shifted left y bits  |
| right shift | >>     | x >> y | all bits in x shifted right y bits |
| bitwise NOT | ~      | ~x     | all bits in x shifted right y bits |
| bitwise AND | &      | x & y  |  each bit in x AND each bit in y   |
| bitwise OR  | |      | x | y  |  each bit in x AND each bit in y   |
| bitwise XOR | ^      | x ^ y  |  each bit in x XOR each bit in y   |


<!--NOTE: Avoid using bitwise operators with signed operands -->


 Bit manipulation with bitwise operators and bit masks 
=========================================================================
In order to manipualte individual bits (turning them off and on) bitwise erators do not know how to do this,
so this is achieved with `bit masks`.

A bit mask is a predefined set of bits that determines which bit would be manipulated in subsequent bit operations.

Defining bit mask
-----------------------------------------------
Bit Masks can be defined bu declaring an array of off bits and setting the bit in mind to be manipulated to on.

```cpp
 #include <cstdint>

 // c++14 >=
 constexpr std::uint8_t mask0{ 0b0000'0001 };  // represents bit 0
 constexpr std::uint8_t mask1{ 0b0000'0010 };  // represents bit 1
 constexpr std::uint8_t mask2{ 0b0000'0100 };  // represents bit 2
 constexpr std::uint8_t mask3{ 0b0000'1000 };  // represents bit 3
 constexpr std::uint8_t mask4{ 0b0001'0000 };  // represents bit 4
 constexpr std::uint8_t mask5{ 0b0010'0000 };  // represents bit 5
 constexpr std::uint8_t mask6{ 0b0100'0000 };  // represents bit 6
 constexpr std::uint8_t mask7{ 0b1000'0000 };  // represents bit 7

// c++11 <= (does not support binary literals)
constexpr std::uint8_t mask0{ 0x01 };  // hex for 0000 0001
constexpr std::uint8_t mask1{ 0x02 };  // hex for 0000 0010
constexpr std::uint8_t mask2{ 0x04 };  // hex for 0000 0100
constexpr std::uint8_t mask3{ 0x08 };  // hex for 0000 1000
constexpr std::uint8_t mask4{ 0x10 };  // hex for 0001 0000
constexpr std::uint8_t mask5{ 0x20 };  // hex for 0010 0000
constexpr std::uint8_t mask6{ 0x40 };  // hex for 0100 0000
constexpr std::uint8_t mask7{ 0x80 };  // hex for 1000 0000

//easier method using left shift
constexpr std::uint8_t mask0{ 1 << 0 };  // 0000 0001
constexpr std::uint8_t mask1{ 1 << 1 };  // 0000 0010
constexpr std::uint8_t mask2{ 1 << 2 };  // 0000 0100
constexpr std::uint8_t mask3{ 1 << 3 };  // 0000 1000
constexpr std::uint8_t mask4{ 1 << 4 };  // 0001 0000
constexpr std::uint8_t mask5{ 1 << 5 };  // 0010 0000
constexpr std::uint8_t mask6{ 1 << 6 };  // 0100 0000
constexpr std::uint8_t mask7{ 1 << 7 };  // 1000 0000
```

Testing to see if a bit is on or not
-----------------------------------------------
```cpp
  #include <cstdint>
  #include <iostream>

  int main()
  {
    [[maybe_unused]] constexpr std::uint8_t mask0{ 0b0000'0001 };  // represents bit 0
    [[maybe_unused]] constexpr std::uint8_t mask1{ 0b0000'0010 };  // represents bit 1
    [[maybe_unused]] constexpr std::uint8_t mask2{ 0b0000'0100 };  // represents bit 2
    [[maybe_unused]] constexpr std::uint8_t mask3{ 0b0000'1000 };  // represents bit 3
    [[maybe_unused]] constexpr std::uint8_t mask4{ 0b0001'0000 };  // represents bit 4
    [[maybe_unused]] constexpr std::uint8_t mask5{ 0b0010'0000 };  // represents bit 5
    [[maybe_unsued]] constexpr std::uint8_t mask6{ 0b0100'0000 };  // represents bit 6
    [[maybe_unused]] constexpr std::uint8_t mask7{ 0b1000'0000 };  // represents bit 7

    std::uint8_t flag { 0b0000'0101 };
    std::cout << "bit 0 is " << (static_cast<bool>(flag & mask0) ? "on" : "off") << '\n';
    std::cout << "bit 1 is " << (static_cast<bool>(flag & mask1) ? "on" : "off") << '\n';

    return 0;
  }
```

Setting a bit
-----------------------------------------------
```cpp
  #include <cstdint>
  #include <iostream>

  int main()
  {
    [[maybe_unused]] constexpr std::uint8_t mask0{ 0b0000'0001 };  // represents bit 0
    [[maybe_unused]] constexpr std::uint8_t mask1{ 0b0000'0010 };  // represents bit 1
    [[maybe_unused]] constexpr std::uint8_t mask2{ 0b0000'0100 };  // represents bit 2
    [[maybe_unused]] constexpr std::uint8_t mask3{ 0b0000'1000 };  // represents bit 3
    [[maybe_unused]] constexpr std::uint8_t mask4{ 0b0001'0000 };  // represents bit 4
    [[maybe_unused]] constexpr std::uint8_t mask5{ 0b0010'0000 };  // represents bit 5
    [[maybe_unsued]] constexpr std::uint8_t mask6{ 0b0100'0000 };  // represents bit 6
    [[maybe_unused]] constexpr std::uint8_t mask7{ 0b1000'0000 };  // represents bit 7

    std::uint8_t flags { 0b0000'0101 };

    flags |= mask1;                 // turns bit one on.
    flags |= (mask4 | mask5);       // multiple bit on-ing (turns bit 4 and 5 on)
  }
```

Turning on multiple bits:
```cpp
  flags |= (mask6 | mask7);
```

Resetting a bit
-----------------------------------------------
```cpp
  #include <cstdint>
  #include <iostream>

  int main()
  {
    [[maybe_unused]] constexpr std::uint8_t mask0{ 0b0000'0001 };  // represents bit 0
    [[maybe_unused]] constexpr std::uint8_t mask1{ 0b0000'0010 };  // represents bit 1
    [[maybe_unused]] constexpr std::uint8_t mask2{ 0b0000'0100 };  // represents bit 2
    [[maybe_unused]] constexpr std::uint8_t mask3{ 0b0000'1000 };  // represents bit 3
    [[maybe_unused]] constexpr std::uint8_t mask4{ 0b0001'0000 };  // represents bit 4
    [[maybe_unused]] constexpr std::uint8_t mask5{ 0b0010'0000 };  // represents bit 5
    [[maybe_unused]] constexpr std::uint8_t mask6{ 0b0100'0000 };  // represents bit 6
    [[maybe_unused]] constexpr std::uint8_t mask7{ 0b1000'0000 };  // represents bit 7

    std::uint8_t flags{ 0b0000'0101 };

    std::cout << "bit 2 is " << (static_cast<bool>(flags & mask2) ? "on" : "off") << '\n';
    flags &= ~mask2;      // turns off bit 2.
    std::cout << "bit 2 is " << (static_cast<bool>(flags & mask2) ? "on" : "off") << '\n';
  }
```

turing of multiple bits:
```cpp
  flags &= ~(mask2 | mask3);
```

<!--NOTE:-->
Because the type of mask2 is smaller than int, operator~ causes operand mask2 to undergo integral promotion to type int.
Then the compiler complains that we’re trying to use operator&= where the left operand is unsigned and the right operand is signed.

If this is the case, try the following:
```cpp
  flags &= static_cast<std::uint8_t>(~mask2);
```

Flipping a bit
-----------------------------------------------
This is done with the bitwise XOR operator.

```cpp
#include <cstdint>
#include <iostream>

int main()
{
    [[maybe_unused]] constexpr std::uint8_t mask0{ 0b0000'0001 }; // represents bit 0
    [[maybe_unused]] constexpr std::uint8_t mask1{ 0b0000'0010 }; // represents bit 1
    [[maybe_unused]] constexpr std::uint8_t mask2{ 0b0000'0100 }; // represents bit 2
    [[maybe_unused]] constexpr std::uint8_t mask3{ 0b0000'1000 }; // represents bit 3
    [[maybe_unused]] constexpr std::uint8_t mask4{ 0b0001'0000 }; // represents bit 4
    [[maybe_unused]] constexpr std::uint8_t mask5{ 0b0010'0000 }; // represents bit 5
    [[maybe_unused]] constexpr std::uint8_t mask6{ 0b0100'0000 }; // represents bit 6
    [[maybe_unused]] constexpr std::uint8_t mask7{ 0b1000'0000 }; // represents bit 7

    std::uint8_t flags{ 0b0000'0101 }; // 8 bits in size means room for 8 flags
    std::cout << "bit 2 is " << (static_cast<bool>(flags & mask2) ? "on" : "off") << '\n';
    flags ^= mask2;
    std::cout << "bit 2 is " << (static_cast<bool>(flags & mask2) ? "on" : "off") << '\n';
    flags ^= mask2;
    std::cout << "bit 2 is " << (static_cast<bool>(flags & mask2) ? "on" : "off") << '\n';

    return 0;
}
```


flipping mulitples bits simultaneoulsy:
```cpp
  flags ^= (mask4 | mask5);
```

Bit masks and std::bitset
-----------------------------------------------
<!--NOTE: excerpt from the site-->

std::bitset supports the full set of bitwise operators. So even though it’s easier to use the functions (test, set, reset, and flip)
to modify individual bits, you can use bitwise operators and bit masks if you want.

Why would you want to? The functions only allow you to modify individual bits.
The bitwise operators allow you to modify multiple bits at once.

<!--NOTE: why do these statements do the same thing? -->
```cpp
  myflags &= ~(option1 | option2);
  myflags &= ~option1 & ~option2;
```

This is because DeMorgans law says that to distribute a `NOT`, ORs are flipped to ANDs and vice versa.


 Converting integers between binary and decimal representation 
=========================================================================
<!--TODO: COME BACK TO THIS-->
www.learncpp.com/cpp-tutorial/converting-integers-between-binary-and-decimal-representation/
-----------------------------------------------

