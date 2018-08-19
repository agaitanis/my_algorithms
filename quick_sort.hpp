#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP

#include <vector>

extern void quick_sort(std::vector<int> &a);
extern void quick_sort_rand(std::vector<int> &a);
extern void quick_sort_rand_median3(std::vector<int> &a);

extern int partition_rand(std::vector<int> &a, int left, int right);

extern void test_quick_sort();

#endif // QUICK_SORT_HPP
