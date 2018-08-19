#ifndef KAHAN_HPP
#define KAHAN_HPP

template <typename Iterator> typename Iterator::value_type kahan_sum(Iterator begin, Iterator end)
{
	typedef typename Iterator::value_type Real;
	Real	s = 0;
	Real	c = 0;

	for (Iterator it = begin; it != end; ++it) {
		Real	x = *it;
		Real	y = x - c;
		Real	t = s + y;

		c = (t - s) - y;
		s = t;
	}

	return s;
}

template <typename Container> typename Container::value_type kahan_sum(const Container &c)
{
	return kahan_sum(c.begin(), c.end());
}

#endif // KAHAN_HPP
