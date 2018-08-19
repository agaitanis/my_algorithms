#ifndef MAX_SUBARRAY_HPP
#define MAX_SUBARRAY_HPP

#include <vector>

struct MaxSubarrayResult {
	MaxSubarrayResult() : left(0), right(0), sum(0) {}
	MaxSubarrayResult(int left, int right, long long sum) : left(left), right(right), sum(sum) {}

	int	left;
	int	right;
	long long sum;
};

extern MaxSubarrayResult max_subarray_dynamic(const std::vector<int> &a);

extern void test_max_subarray();

#endif // MAX_SUBARRAY_HPP
