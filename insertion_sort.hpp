#ifndef INSERTION_SORT_HPP
#define INSERTION_SORT_HPP

#include <vector>

template <class T>
extern void insertion_sort(std::vector<T> &a)
{
	for (int j = 1; j < a.size(); j++) {
		T key;
		int i;

		key = a[j];
		i = j - 1;
		while (i >= 0 && a[i] > key) {
			a[i+1] = a[i];
			i--;
		}
		a[i+1] = key;
	}
}

#endif // INSERTION_SORT_HPP
