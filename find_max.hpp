#ifndef FIND_MAX_HPP
#define FIND_MAX_HPP

#include <vector>
#include <utility>

extern int find_max(const std::vector<int> &a);
extern int find_max_randomized(const std::vector<int> &a);
extern int find_max_best_guess(const std::vector<int> &a);
extern std::pair<int, int> find_min_max(const std::vector<int> &a, int *min, int *max);

extern void test_find_max();
extern void test_find_min_max();

#endif // FIND_MAX_HPP
