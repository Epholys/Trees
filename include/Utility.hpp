#ifndef UTILITY_HPP
#define UTILITY_HPP


#include <random>
#include <sstream>
#include <string>

int randInt (int minExclusive, int maxExclusive);

template<typename T>
std::string toString(const T& var)
{
	std::stringstream ss;
	ss << var;
	return ss.str();
}

#endif // UTILITY_HPP
