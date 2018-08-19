#include <iostream>
#include <vector>
#include <cassert>

#include "disjoint_set.hpp"

using namespace std;

DisjointSet::DisjointSet(int n) :
	parent(n),
	ht(n),
	sz(n)
{
	for (int i = 0; i < n; i++) {
		parent[i] = i;
		ht[i] = 0;
		sz[i] = 1;
	}
}

int DisjointSet::get_size(int i)
{
	return sz[i];
}

int DisjointSet::find(int i)
{
	if (i != parent[i]) {
		parent[i] = find(parent[i]);
	}
	return parent[i];
}

void DisjointSet::merge(int i, int j)
{
	int i_id = find(i);
	int j_id = find(j);

	if (i_id == j_id) return;

	if (ht[i_id] > ht[j_id]) {
		parent[j_id] = i_id;
		sz[i_id] += sz[j_id];
	} else {
		parent[i_id] = j_id;
		if (ht[i_id] == ht[j_id]) {
			ht[j_id]++;
		}
		sz[j_id] += sz[i_id];
	}
}

