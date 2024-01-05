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
