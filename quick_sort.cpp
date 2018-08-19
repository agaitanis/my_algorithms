#include <iostream>
#include <vector>
#include <climits>
#include <cassert>

#include "quick_sort.hpp"
#include "my_tools.hpp"

using namespace std;

static int partition(vector<int> &a, int left, int right)
{
	int x = a[right];
	int i = left-1;

	for (int j = left; j <= right-1; j++) {
		if (a[j] <= x) {
			i++;
			swap(a[i], a[j]);
		}
	}

	swap(a[i+1], a[right]);

	return i+1;
}

static void quick_sort_rec(vector<int> &a, int left, int right)
{
	if (left >= right) return;

	int pivot = partition(a, left, right);
	quick_sort_rec(a, left, pivot-1);
	quick_sort_rec(a, pivot+1, right);
}

void quick_sort(vector<int> &a)
{
	ScopedClock cl(__FUNCTION__);
	return quick_sort_rec(a, 0, (int)a.size()-1);
}

int partition_rand(vector<int> &a, int left, int right)
{
	int i = rand_int(left, right);

	swap(a[i], a[right]);

	return partition(a, left, right);
}

static void quick_sort_rand_tail_rec(vector<int> &a, int left, int right)
{
	while (left < right) {
		int pivot = partition_rand(a, left, right);
		quick_sort_rand_tail_rec(a, left, pivot-1);
		left = pivot+1;
	}
}

void quick_sort_rand(vector<int> &a)
{
	ScopedClock cl(__FUNCTION__);
	return quick_sort_rand_tail_rec(a, 0, (int)a.size()-1);
}

static int partition_rand_median3(vector<int> &a, int left, int right)
{
	int i1 = rand_int(left, right);
	int i2 = rand_int(left, right);
	int i3 = rand_int(left, right);
	int i;

	if ((a[i2] <= a[i1] && a[i1] <= a[i3]) || (a[i3] <= a[i1] && a[i1] <= a[i2])) {
		i = i1;
	} else if ((a[i1] <= a[i2] && a[i2] <= a[i3]) || (a[i3] <= a[i2] && a[i2] <= a[i1])) {
		i = i2;
	} else {
		i = i3;
	}

	swap(a[i], a[right]);

	return partition(a, left, right);
}

static void quick_sort_rand_tail_rec_median3(vector<int> &a, int left, int right)
{
	while (left < right) {
		int pivot = partition_rand_median3(a, left, right);
		quick_sort_rand_tail_rec_median3(a, left, pivot-1);
		left = pivot+1;
	}
}

void quick_sort_rand_median3(vector<int> &a)
{
	ScopedClock cl(__FUNCTION__);
	return quick_sort_rand_tail_rec_median3(a, 0, (int)a.size()-1);
}

void test_quick_sort()
{
	for (int i = 0; i < 1000; i++) {
		int     n = rand_int(1, 1000000);
		vector<int> a(n);

		for (int j = 0; j < n; j++) {
			a[j] = rand_int(1, 1000000);
		}

		quick_sort_rand_median3(a);

		for (int j = 1; j < n; j++) {
			assert(a[j] >= a[j-1]);
		}
	}
}

