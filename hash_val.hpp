#ifndef HASH_VAL_HPP
#define HASH_VAL_HPP

#include <tr1/functional>

template <typename T>
inline void hash_combine(std::size_t &seed, const T &val)
{
	seed ^= std::tr1::hash<T>()(val) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

template <typename T>
inline void hash_val(std::size_t &seed, const T &val)
{
	hash_combine(seed, val);
}

struct PairHash {
	template <class T1, class T2>
	std::size_t operator()(const std::pair<T1, T2> &pair) const
	{
		std::size_t hash = 0;

		hash_combine(hash, pair.first);
		hash_combine(hash, pair.second);

		return hash;
	}
};

#endif // HASH_VAL_HPP
