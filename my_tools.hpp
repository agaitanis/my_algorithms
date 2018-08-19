#include <iostream>
#include <cstdio>
#include <ctime>
#include <string>
#include <vector>

class ScopedClock {
	public:
		ScopedClock(const char *str) : m_t(clock()), m_str(str) {}

		~ScopedClock()
		{
			printf("%s: %f sec\n", m_str.c_str(), double(clock()-m_t)/CLOCKS_PER_SEC);
		}

	private:
		clock_t		m_t;
		std::string	m_str;
};

template <class T>
void print_vec(const char *s, const std::vector<T> &a)
{
	std::cout << s;
	for (int i = 0; i < a.size(); i++) {
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
}

struct DeleteObject {
	template <class T> void operator()(T *p)
	{
		delete p;
	}
};

extern int rand_int(int min, int right);
extern double rand_double(double min, double right);
