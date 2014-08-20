#include "Leaf.hpp"


//------------------------------------------------------------------------------
// *** constructor: ***
Leaf::Leaf()
	: leaf_()
{
}

Leaf::Leaf(float radius, const sf::Color& color)
	: leaf_(radius)
{
	setOrigin(radius / 2.f, radius / 2.f);

	leaf_.setFillColor(color);
}


//------------------------------------------------------------------------------
// *** graphics: ***

void Leaf::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(leaf_, states);
}
