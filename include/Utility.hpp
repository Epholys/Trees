#ifndef UTILITY_HPP
#define UTILITY_HPP


#include <random>
#include <sstream>
#include <string>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Text.hpp>

int randInt (int minExclusive, int maxExclusive);

void centerOrigin(sf::Text& text);

template<typename T>
std::string toString(const T& var)
{
	std::stringstream ss;
	ss << var;
	return ss.str();
}


#endif // UTILITY_HPP
