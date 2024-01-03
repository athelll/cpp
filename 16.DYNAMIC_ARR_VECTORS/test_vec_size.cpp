#include <iostream>
#include <vector>

int main()
{
    std::vector<int> vec { 1, 2 , 3, 4, 5 };
    std::cout << "the size of vec is " << vec.size() << " used .size()\n";
    std::cout << "the size of vec is " << std::size(vec) << " used std::size()\n";
}
