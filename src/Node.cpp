#include "Node.hpp"



//------------------------------------------------------------------------------
// *** constructor: ***

Node::Node()
	: children_()
	, growthFunctions_()
{
}


//------------------------------------------------------------------------------
// *** public virtual functions: ***

void Node::createChildren(Type type)
{
	if (children_.empty())
	{
		auto it = growthFunctions_.find(type);
		if (it != growthFunctions_.end())
		{
			it->second();
		}
	}
	else
	{
		for (auto& elem : children_)
		{
			elem->createChildren(type);
		}
	}
}


//------------------------------------------------------------------------------
// *** graphics: ***

void Node::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	drawCurrent(target, states);

	for (const auto& e : children_)
	{
		e->draw(target, states);
	}
}

void Node::drawCurrent(sf::RenderTarget&, sf::RenderStates) const
{
}
