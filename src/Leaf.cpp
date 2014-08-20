#include "Leaf.hpp"


//------------------------------------------------------------------------------
// *** constructor: ***
Leaf::Leaf()
	: param_()
	, leaf_()
{
}

Leaf::Leaf(const Branch::RandomParameters& param, float radius, const sf::Color& color)
	: param_(param)
	, leaf_(radius)
{
	assert(param.checkValidity());

	setOrigin(size.x / 2.f, size.y / 2.f);

	leaf_.setFillColor(color);
}


//------------------------------------------------------------------------------
// *** graphics: ***

void Leaf::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(leaf_, states);
}
