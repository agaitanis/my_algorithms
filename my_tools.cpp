#include <cstdlib>

#include "my_tools.hpp"

using namespace std;

int rand_int(int min, int max)
{
	return min + rand() % (max - min + 1);
}

double rand_double(double min, double max)
{
	return min + (max*rand())/(double)RAND_MAX;
}
