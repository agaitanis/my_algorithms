#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cassert>

#include "max_subarray.hpp"
#include "my_tools.hpp"

using namespace std;

static void print_res(const char *s, const vector<int> &a, const MaxSubarrayResult &res)
{
	cout << s << ": ";
	for (int i = res.left; i <= res.right; i++) {
		cout << a[i] << " ";
	}
	cout << ", sum = " << res.sum << endl;
}

static MaxSubarrayResult max_subarray_brute(const vector<int> &a)
{
	ScopedClock cl(__FUNCTION__);
	MaxSubarrayResult res(0, 0, a[0]);

	for (int i = 0; i < (int)a.size(); i++) {
		long long sum = 0;

		for (int j = i; j < (int)a.size(); j++) {
			sum += a[j];
			if (sum > res.sum) {
				res.sum = sum;
				res.left = i;
				res.right = j;
			}
		}
	}

	return res;
}

static MaxSubarrayResult max_subarray_sides(const vector<int> &a, int left, int mid, int right)
{
	int	best_left = mid;
	int	best_right = mid + 1;
	long long max_sum_left = a[mid];
	long long max_sum_right = a[mid + 1];
	long long sum;

	sum = 0;
	for (int i = mid; i >= left; i--) {
		sum += a[i];
		if (sum > max_sum_left) {
			max_sum_left = sum;
			best_left = i;
		}
	}

	sum = 0;
	for (int i = mid + 1; i <= right; i++) {
		sum += a[i];
		if (sum > max_sum_right) {
			max_sum_right = sum;
			best_right = i;
		}
	}

	return MaxSubarrayResult(best_left, best_right, max_sum_left + max_sum_right);
}

static MaxSubarrayResult max_subarray_divide_recursive(const vector<int> &a, int left, int right)
{
	if (left >= right) return MaxSubarrayResult(left, right, a[left]);

	int	mid = (left + right)/2;

	MaxSubarrayResult res1 = max_subarray_divide_recursive(a, left, mid);
	MaxSubarrayResult res2 = max_subarray_divide_recursive(a, mid + 1, right);
	MaxSubarrayResult res3 = max_subarray_sides(a, left, mid, right);

	if (res1.sum >= res2.sum && res1.sum >= res3.sum) {
		return res1;
	} else if (res2.sum >= res1.sum && res2.sum >= res3.sum) {
		return res2;
	} else {
		return res3;
	}
}

static MaxSubarrayResult max_subarray_divide(const vector<int> &a)
{
	ScopedClock cl(__FUNCTION__);

	return max_subarray_divide_recursive(a, 0, (int)a.size()-1);
}

MaxSubarrayResult max_subarray_dynamic(const vector<int> &a)
/* Kadane algorithm */
{
	ScopedClock cl(__FUNCTION__);
	long long max_so_far = a[0];
	long long max_sum = a[0];
	int candidate_left = 0;
	int left = 0;
	int right = 0;

	for (int i = 1; i < (int)a.size(); i++) {
		if (max_so_far < 0) { // a[i] > a[i] + max_so_far
			max_so_far = a[i];
			candidate_left = i;
		} else {
			max_so_far = a[i] + max_so_far;
		}

		if (max_so_far > max_sum) {
			max_sum = max_so_far;
			right = i;
			left = candidate_left;
		}
	}

	return MaxSubarrayResult(left, right, max_sum);
}

void test_max_subarray()
{
	for (int i = 0; i < 100; i++) {
		int	n = rand() % 10000 + 1;
		vector<int> a(n);

		for (int j = 0; j < n; j++) {
			a[j] = rand() % 200 - 100;
		}

		MaxSubarrayResult res1 = max_subarray_brute(a);
		MaxSubarrayResult res2 = max_subarray_divide(a);
		MaxSubarrayResult res3 = max_subarray_dynamic(a);

		if (res1.sum != res2.sum) {
			print_res("brute", a, res1);
			print_res("divide", a, res2);
			assert(0);
		}
		if (res1.sum != res3.sum) {
			print_res("brute", a, res1);
			print_res("dynamic", a, res3);
			assert(0);
		}
	}
}

