#include <iostream>
#include <vector>
#include <climits>
#include <cassert>

#include "merge_sort.hpp"
#include "my_tools.hpp"

using namespace std;

static void merge(vector<int> &a, int begin, int mid, int end)
{
	vector<int> b(mid - begin + 1);
	vector<int> c(end - mid + 1);
	int	i, j;

	for (i = 0; i < mid - begin; i++) {
		b[i] = a[i + begin];
	}
	b[i] = INT_MAX;

	for (i = 0; i < end - mid; i++) {
		c[i] = a[i + mid];
	}
	c[i] = INT_MAX;

	i = j = 0;
	for (int k = begin; k < end; k++) {
		if (b[i] < c[j]) {
			a[k] = b[i++];
		} else {
			a[k] = c[j++];
		}
	}
}

static void merge_sort_recursive(vector<int> &a, int begin, int end)
{
	if (begin >= end - 1) return;

	int mid = (begin + end)/2;

	merge_sort_recursive(a, begin, mid);
	merge_sort_recursive(a, mid, end);
	merge(a, begin, mid, end);
}

void merge_sort(vector<int> &a)
{
	ScopedClock cl(__FUNCTION__);
	return merge_sort_recursive(a, 0, a.size());
}

void test_merge_sort()
{
	for (int i = 0; i < 1000; i++) {
		int	n = rand_int(1, 1000000);
		vector<int> a(n);

		for (int j = 0; j < n; j++) {
			a[j] = rand_int(1, 1000000);
		}

		merge_sort(a);

		for (int j = 1; j < n; j++) {
			assert(a[j] >= a[j-1]);
		}
	}
}

