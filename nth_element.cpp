#include <vector>
#include <cassert>

#include "nth_element.hpp"
#include "my_tools.hpp"
#include "quick_sort.hpp"

using namespace std;

static int nth_element_rand_rec(vector<int> &a, int left, int right, int i)
{
	if (left >= right) return a[left];

	int pivot = partition_rand(a, left, right);
	int k = pivot - left + 1;

	if (i == k) {
		return a[pivot];
	} else if (i < k) {
		return nth_element_rand_rec(a, left, pivot-1, i);
	} else {
		return nth_element_rand_rec(a, pivot+1, right, i-k);
	}
}

int nth_element_rand(vector<int> &a, int i)
{
	return nth_element_rand_rec(a, 0, (int)a.size()-1, i);
}

void test_nth_element_rand()
{
	for (int i = 0; i < 1000; i++) {
		int n = rand_int(1, 1000);
		vector<int> a(n);

		for (int j = 0; j < n; j++) {
			a[j] = rand_int(-1000, 1000);
		}

		int k = rand_int(1, n);
		int b = nth_element_rand(a, k);

		for (int j = 0; j < k; j++) {
			assert(a[j] <= b);
		}
		for (int j = k+1; j < n; j++) {
			assert(a[j] >= b);
		}
	}
}
