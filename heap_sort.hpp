#ifndef HEAP_SORT_HPP
#define HEAP_SORT_HPP

#include <vector>

extern void heap_sort(std::vector<int> &a);

extern void build_max_heap(std::vector<int> &a);
extern void max_heap_insert(std::vector<int> &a, int key);
extern int heap_pop_max(std::vector<int> &a);
extern int heap_max(const std::vector<int> &a);

extern void test_heap_sort();

#endif // HEAP_SORT_HPP
