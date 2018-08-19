#include <iostream>
#include <vector>
#include <climits>
#include <cassert>
#include <cmath>

#include "radix_sort.hpp"
#include "my_tools.hpp"

using namespace std;

static int digit_of(int a, int digit)
{
	int ret = 0;

	for (int i = 0; i < digit; i++) {
		ret = a % 10;
		a /= 10;
	}

	return ret;
}

static void counting_sort_digit(vector<int> &a, int digit)
{
	int n = a.size();
	int k = 10;
	vector<int> b(n);
	vector<int> c(k, 0);

	for (int i = 0; i < n; i++) {
		c[digit_of(a[i], digit)]++;
	}

	for (int i = 1; i < k; i++) {
		c[i] += c[i-1];
	}

	for (int i = n-1; i >= 0; i--) {
		b[c[digit_of(a[i], digit)]-1] = a[i];
		c[digit_of(a[i], digit)]--;
	}

	a = b;
}

void radix_sort(vector<int> &a, int d)
{
	for (int i = 1; i <= d; i++) {
		counting_sort_digit(a, i);
	}
}

void test_radix_sort()
{
	for (int i = 0; i < 1000; i++) {
		int	d = 3;
		int	n = rand_int(1, 10);
		vector<int> a(n);

		for (int j = 0; j < n; j++) {
			a[j] = rand_int(0, pow(10, d));
		}

		print_vec("unsorted: ", a);
		radix_sort(a, d);
		print_vec("sorted: ", a);
		printf("\n"); // alex

		for (int j = 1; j < n; j++) {
			assert(a[j] >= a[j-1]);
		}
	}
}

