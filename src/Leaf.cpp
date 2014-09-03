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

bool Leaf::isOutOfView(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::View view = target.getView();
	sf::Vector2f center = view.getCenter();
	sf::Vector2f size = view.getSize();
	sf::FloatRect viewRect (center.x - size.x / 2.f,
							center.y - size.y / 2.f,
							size.x,
							size.y);
	sf::FloatRect rect = leaf_.getGlobalBounds();
	rect = states.transform.transformRect(rect);

	return !rect.intersects(viewRect);
}
