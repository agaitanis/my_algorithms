#include <iostream>
#include <vector>
#include <algorithm>

#include "combination.hpp"

std::vector<std::vector<int> > combination(int n, int k)
{
	std::vector<bool> bitmask(k, true);
	std::vector<std::vector<int> > combos;

	bitmask.insert(bitmask.end(), n - k, false);

	do {
		combos.push_back(std::vector<int>());

		for (int i = 0; i < n; i++) {
			if (bitmask[i]) {
				combos.back().push_back(i);
			}
		}
	} while (std::prev_permutation(bitmask.begin(), bitmask.end()));

	return combos;
}

