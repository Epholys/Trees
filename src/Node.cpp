#include "Node.hpp"



//------------------------------------------------------------------------------
// *** constructor & destructor: ***

Node::Node()
	: children_()
	, growthFunctions_()
{
}


Node::~Node()
{
}


//------------------------------------------------------------------------------
// *** public virtual functions: ***

void Node::createChildren(Type type, RandomParameters::SPtr params)
{
	if (children_.empty())
	{
		auto it = growthFunctions_.find(type);
		if (it != growthFunctions_.end())
		{
			it->second(std::move(params));
		}
	}
	else
	{
		for (auto& elem : children_)
		{
			elem->createChildren(type, params);
		}
	}
}


//------------------------------------------------------------------------------
// *** graphics: ***

void Node::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	if(!isOutOfView(target, states))
	{
		drawCurrent(target, states);
	}

	for (const auto& e : children_)
	{
		e->draw(target, states);
	}
}

void Node::drawCurrent(sf::RenderTarget&, sf::RenderStates) const
{
}
