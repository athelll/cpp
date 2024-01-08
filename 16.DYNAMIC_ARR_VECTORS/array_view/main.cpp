#include <iostream>
#include <vector>
#include "array_view.h"

int main()
{
		std::vector array { 1, 2, 3, 4, 5, 6 };
		s_array_view sv_array { array };

		for (auto index { sv_array.ssize()-1 }; index >= 0; --index)
				std::cout << sv_array[index] << ' ';
		std::cout << '\n';
}
