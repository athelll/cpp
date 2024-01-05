#include <iostream>
#include <vector>

template <typename T>
void printReverse(const std::vector<T>& arr)
{
    for (typename std::vector<T>::size_type index{ arr.size() - 1 }; index >= 0; --index) // index is unsigned
    {
        std::cout << arr[index] << ' ';
    }

    std::cout << '\n';
}

int main()
{
    std::vector arr{ 4, 6, 7, 3, 8, 2, 1, 9 };

    printReverse(arr);

    return 0;
}
