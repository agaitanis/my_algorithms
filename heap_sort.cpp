#include <iostream>
#include <vector>
#include <climits>
#include <cassert>

#include "heap_sort.hpp"
#include "my_tools.hpp"

using namespace std;

static int get_parent(int i)
{
	return (i-1)/2;
}

static int left_child(int i)
{
	return 2*i+1;
}

static int right_child(int i)
{
	return 2*i+2;
}

static void max_heapify(vector<int> &a, int i, int heap_size)
{
	int	left = left_child(i);
	int	right = right_child(i);
	int	i_max = i;

	if (left < heap_size && a[left] > a[i_max]) {
		i_max = left;
	}
	if (right < heap_size && a[right] > a[i_max]) {
		i_max = right;
	}
	if (i != i_max) {
		swap(a[i], a[i_max]);
		max_heapify(a, i_max, heap_size);
	}
}

static void max_heapify(vector<int> &a, int i)
{
	return max_heapify(a, i, a.size());
}

void build_max_heap(vector<int> &a)
{
	for (int i = (int)a.size()/2-1; i >= 0; i--) {
		max_heapify(a, i);
	}
}

int heap_max(const vector<int> &a)
{
	return a[0];
}

int heap_pop_max(vector<int> &a)
{
	if (a.empty()) {
		assert(0);
		return 0;
	}

	int max = a[0];

	a[0] = a.back();
	a.pop_back();

	max_heapify(a, 0);

	return max;
}

static void heap_increase_key(vector<int> &a, int i, int key)
{
	if (key < a[i]) {
		assert(0);
		return;
	}

	a[i] = key;

	int parent = get_parent(i);

	while (i > 0 && a[parent] < a[i]) {
		swap(a[i], a[parent]);
		i = parent;
		parent = get_parent(i);
	}
}

void max_heap_insert(vector<int> &a, int key)
{
	a.push_back(-INT_MAX);
	heap_increase_key(a, (int)a.size()-1, key);
}

void heap_sort(vector<int> &a)
{
	ScopedClock cl(__FUNCTION__);

	build_max_heap(a);

	for (int i = (int)a.size()-1; i >= 1; i--) {
		swap(a[0], a[i]);
		max_heapify(a, 0, i);
	}
}

void test_heap_sort()
{
	for (int i = 0; i < 100; i++) {
		int	n = rand_int(1, 100000);
		vector<int> a(n);

		for (int j = 0; j < n; j++) {
			a[j] = rand_int(1, 1000);
		}

		heap_sort(a);

		for (int j = 1; j < n; j++) {
			if (a[j] < a[j-1]) {
				print_vec("sorted: ", a);
				assert(0);
			}
		}
	}
}

