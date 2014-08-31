#include <ctime>

#include "Utility.hpp"


//------------------------------------------------------------------------------

namespace
{
	std::default_random_engine createRandomEngine()
	{
		auto seed = static_cast<unsigned long>(std::time(nullptr));
		return std::default_random_engine(seed);
	}

	auto RandomEngine = createRandomEngine();
}


int randInt (int minExclusive, int maxExclusive)
{
	std::uniform_int_distribution<> dist (minExclusive+1, maxExclusive-1);

	return dist(RandomEngine);
}


//------------------------------------------------------------------------------

void centerOrigin(sf::Text& text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}
