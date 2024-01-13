#include <vector>
#include <iostream>

void printStack(const std::vector<int>& stack)
{
    if (stack.empty())
        std::cout << "Empty";
    else
        for (auto element : stack) std::cout << element << ' ';

    std::cout << "\tCapacity: " << stack.capacity() << " Length: " << stack.size() << '\n';
}

int main()
{
    std::vector<int> stack{};
    	printStack(stack);

	stack.push_back(1);
	printStack(stack);

	stack.push_back(2);
	printStack(stack);

	stack.push_back(3);
	printStack(stack);

	std::cout << "Top: " << stack.back() << '\n'; // back() returns the last element

	stack.pop_back(); // pop_back() pops an element off the stack
	printStack(stack);

	stack.pop_back();
	printStack(stack);

	stack.pop_back();
	printStack(stack);
}
