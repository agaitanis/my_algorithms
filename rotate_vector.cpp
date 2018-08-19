#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

#include "rotate_vector.hpp"


using namespace std;


void rotate_vector_left(vector<int> &a, int rotations)
{
	int	n = (int)a.size();
	int	k = rotations % n;

	reverse(a.begin(), a.begin() + k);
	reverse(a.begin() + k, a.end());
	reverse(a.begin(), a.end());
}

void rotate_vector_right(vector<int> &a, int rotations)
{
	int	n = (int)a.size();
	int	k = rotations % n;

	reverse(a.begin() + n-k, a.end());
	reverse(a.begin(), a.begin() + n-k);
	reverse(a.begin(), a.end());
}

