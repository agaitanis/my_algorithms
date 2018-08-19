#include <iostream>
#include <vector>
#include <climits>
#include <cassert>
#include <cmath>

#include "bucket_sort.hpp"
#include "insertion_sort.hpp"
#include "my_tools.hpp"

using namespace std;

void bucket_sort(vector<double> &a)
{
	int n = a.size();
	vector<vector<double> > b(n);

	for (int i = 0; i < n; i++) {
		b[n*a[i]].push_back(a[i]);
	}

	for (int i = 0; i < (int)b.size(); i++) {
		insertion_sort(b[i]);
	}

	int cnt = 0;
	for (int i = 0; i < (int)b.size(); i++) {
		for (int j = 0; j < (int)b[i].size(); j++) {
			a[cnt++] = b[i][j];
		}
	}
}

void bucket_sort2(vector<double> &a)
{
	int n = a.size();
	vector<vector<double> > b(n);

	for (int i = 0; i < n; i++) {
		b[n*a[i]].push_back(a[i]);
	}

	int cnt = 0;
	for (int i = 0; i < (int)b.size(); i++) {
		for (int j = 0; j < (int)b[i].size(); j++) {
			a[cnt++] = b[i][j];
		}
	}

	insertion_sort(a);
}

void test_bucket_sort()
{
	for (int i = 0; i < 100; i++) {
		int	n = rand_int(1, 100000);
		printf("n = %d\n", n); // alex
		vector<double> a(n);

		for (int j = 0; j < n; j++) {
			a[j] = rand_double(0, 0.999);
		}

		vector<double> b = a;

		bucket_sort(a);
		bucket_sort2(b);

		for (int j = 1; j < n; j++) {
			assert(a[j] >= a[j-1]);
			assert(b[j] >= b[j-1]);
		}
		printf("\n"); // alex
	}
}

