#include <vector>
#include <iostream>
#include <string>

struct Foo
{
    std::string a {};
    int b {};
};

int main()
{
    std::vector<Foo> stack {};

    Foo f { "a", 2 };
    // when the element to be pushed already exists push_back and emplace_back are basically the same.
    stack.push_back( f );
    stack.emplace_back( f );

    // but when a temporary object is to be pushed emplace_back() is more efficient because:
    // unlike push_back that relies on copy semamntics to create a new vector and pushes that onto the stack
    stack.push_back( {"a", 3} );
    // emplace_back takes the parameters of the elemnets to be pushes onto the stack uses that and initializes the elemnt and pushes that ontop the stack
    // without copy semantics.
    stack.emplace_back("a", 2);
};
