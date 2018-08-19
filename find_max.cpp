#include <cstdio>
#include <iostream>
#include <vector>
#include <climits>
#include <cassert>
#include <utility>

#include "find_max.hpp"
#include "my_tools.hpp"

using namespace std;

int find_max(const vector<int> &a)
/* Number of assignments:
 * Best case: O(1)
 * Worst case: O(n)
 * Average case: O(ln(n)), if input is random, but who knows?
 */
{
	size_t assignments = 0;
	size_t comparisons = 0;
	size_t n = a.size();
	int max = -INT_MAX;

	for (size_t i = 0; i < n; i++) {
		comparisons++;
		if (a[i] > max) {
			max = a[i];
			assignments++;
		}
	}

	printf("comparisons = %ld\n", comparisons); // alex
	printf("assignments = %ld\n", assignments); // alex

	return max;
}

static vector<int> create_random_permutation(const vector<int> &a)
/* Produces a uniform random permutation
 */
{
	vector<int> b = a;
	size_t n = b.size();

	for (size_t i = 0; i < n; i++) {
		swap(b[i], b[rand_int(i, n-1)]);
	}

	return b;
}

int find_max_randomized(const vector<int> &a)
/* Expected number of assignments: O(ln(n))
 * because we force random input
 */
{
	return find_max(create_random_permutation(a));
}

static int find_max_best_guess_core(const vector<int> &a)
/* Use the minimum number of comparisons,
 * while maximizing the probability of finding the maximum.
 */
{
	const double e = 2.71828182845904524;
	size_t n = a.size();
	size_t k = n/e;
	int max = -INT_MAX;
	size_t assignments = 0;
	size_t comparisons = 0;

	for (size_t i = 0; i < k; i++) {
		comparisons++;
		if (a[i] > max) {
			max = a[i];
			assignments++;
		}
	}

	for (size_t i = k; i < n; i++) {
		comparisons++;
		if (a[i] > max) {
			max = a[i];
			assignments++;
			break;
		}
	}

	printf("comparisons = %ld\n", comparisons); // alex
	printf("assignments = %ld\n", assignments); // alex

	return max;
}

int find_max_best_guess(const vector<int> &a)
{
	return find_max_best_guess_core(create_random_permutation(a));
}

void test_find_max()
{
	vector<int> a;
	for (int i = 0; i < 100; i++) {
		a.push_back(i);
	}

	printf("find_max:\n"); // alex
	printf("max = %d\n", find_max(a)); // alex
	printf("\n"); // alex

	printf("find_max_randomized:\n"); // alex
	printf("max = %d\n", find_max_randomized(a)); // alex
	printf("\n"); // alex

	printf("find_max_best_guess:\n"); // alex
	printf("max = %d\n", find_max_best_guess(a)); // alex
	printf("\n"); // alex
}

static pair<int, int> find_min_max_simple(const vector<int> &a)
/* Find min and max with 2*n comparisons
 */
{
	if (a.empty()) return make_pair(0, 0);

	int min = a[0];
	int max = a[0];

	for (size_t i = 0; i < a.size(); i++) {
		if (a[i] < min) min = a[i];
		if (a[i] > max) max = a[i];
	}

	return make_pair(min, max);
}

pair<int, int> find_min_max_fewer_comparisons(const vector<int> &a)
/* Find min and max with 1.5*n comparisons
 * This is slower than find_min_max_simple() due to optimizations
 */
{
	if (a.empty()) return make_pair(0, 0);

	size_t i_start;
	int min;
	int max;

	if (a.size() % 2 == 0) {
		if (a[0] < a[1]) {
			min = a[0];
			max = a[1];
		} else {
			min = a[1];
			max = a[0];
		}
		i_start = 2;
	} else {
		min = a[0];
		max = a[0];
		i_start = 1;
	}

	for (size_t i = i_start; i < a.size(); i+=2) {
		if (a[i] < a[i+1]) {
			if (a[i] < min) min = a[i];
			if (a[i+1] > max) max = a[i+1];
		} else {
			if (a[i+1] < min) min = a[i+1];
			if (a[i] > max) max = a[i];
		}
	}

	return make_pair(min, max);
}

void test_find_min_max()
{
	for (int i = 0; i < 10000; i++) {
		int n = rand_int(1, 1000000);
		vector<int> a(n);
		for (int i = 0; i < n; i++) {
			a[i] = rand_int(-1000, 1000);
		}

		pair<int, int> min_max1 = find_min_max_simple(a);
		pair<int, int> min_max2 = find_min_max_fewer_comparisons(a);

		assert(min_max1 == min_max2);
	}
}

