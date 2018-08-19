#include <iostream>
#include <vector>
#include <climits>
#include <cassert>

#include "counting_sort.hpp"
#include "my_tools.hpp"

using namespace std;

void counting_sort(vector<int> &a, int k)
{
	int n = a.size();
	vector<int> b(n);
	vector<int> c(k, 0);

	for (int i = 0; i < n; i++) {
		c[a[i]]++;
	}

	for (int i = 1; i < k; i++) {
		c[i] += c[i-1];
	}

	for (int i = n-1; i >= 0; i--) {
		b[c[a[i]]-1] = a[i];
		c[a[i]]--;
	}

	a = b;
}

void test_counting_sort()
{
	for (int i = 0; i < 1000; i++) {
		int	k = 10;
		int	n = rand_int(1, 10);
		vector<int> a(n);

		for (int j = 0; j < n; j++) {
			a[j] = rand_int(0, k-1);
		}

		print_vec("unsorted: ", a);
		counting_sort(a, k);
		print_vec("sorted: ", a);
		printf("\n"); // alex

		for (int j = 1; j < n; j++) {
			assert(a[j] >= a[j-1]);
		}
	}
}

