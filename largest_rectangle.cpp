#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>

#include "largest_rectangle.hpp"

using namespace std;

struct Building {
	Building(int from, int to, int h) : from(from), to(to), h(h) {}

	int from;
	int to;
	int h;
};

void test_largest_rectangle()
{
	int n;
	cin >> n;
	stack<Building> s;
	long max_area = 0;
	int prev_h = 0;

	s.push(Building(0, 0, 0));

	for (int i = 0; i <= n; i++) {
		int h = 0;

		if (i < n) cin >> h;

		if (h > prev_h) {
			s.push(Building(i, i + 1, h));
		} else if (h < prev_h) {
			while (!s.empty()) {
				Building &b = s.top();

				if (b.h > h) {
					long area = (i - b.from)*b.h;

					max_area = max(max_area, area);
					s.pop();
				} else if (b.h < h) {
					s.push(Building(b.to, i + 1, h));
					break;
				} else {
					b.to = i + 1;
					break;
				}
			}
		}

		prev_h = h;
	}

	cout << max_area << endl;
}

