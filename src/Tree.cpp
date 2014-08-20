#include "Tree.hpp"


//------------------------------------------------------------------------------
// *** constructors: ***

Tree::Tree()
	: Tree(0)
{
}

Tree::Tree(unsigned int depth)
	: Tree(depth, sf::Vector2f(0,0))
{
}


Tree::Tree(unsigned int depth, sf::Vector2f position)
	: trunk_ (nullptr)
{
	RandomParameters param;
	param.minAngle = -65.f;
	param.maxAngle = 65.f;
	param.minNSubBranch = 3;
	param.maxNSubBranch = 5;
	param.minSubBranchScale = 0.50f;
	param.maxSubBranchScale = 0.80f;

	Branch::Ptr trunk(new Branch(param, sf::Vector2f(10,100), sf::Color(101, 40, 0)));
	trunk_ = std::move(trunk);

	setPosition(position);

	for (std::size_t i=0; i<depth; ++i)
	{
		trunk_->createChildren(Node::Branch);
	}
}


//------------------------------------------------------------------------------
// *** sf::Drawable's virtual function: ***
void Tree::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform = getTransform();

	target.draw(*trunk_, states);
}


//------------------------------------------------------------------------------

void Tree::grow(Node::Type type)
{
	trunk_->createChildren(type);
}
