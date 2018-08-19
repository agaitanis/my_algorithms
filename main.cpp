#include <cstdio>
#include <iostream>
#include <vector>

#include "combination.hpp"

int main()
{
	std::vector<std::vector<int> > combos = combination(5, 3);

	for (size_t i = 0; i < combos.size(); i++) {
		for (size_t j = 0; j < combos[i].size(); j++) {
			std::cout << combos[i][j] << " ";
		}
		std::cout << std::endl;
	}

	return 0;
}

