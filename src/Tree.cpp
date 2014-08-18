#include "Tree.hpp"


//------------------------------------------------------------------------------
// *** constructors: ***

Tree::Tree()
	: Tree(5)
{
}

Tree::Tree(unsigned int depth)
	: Tree(depth, sf::Vector2f(0,0))
{
}


Tree::Tree(unsigned int depth, sf::Vector2f position)
	: trunk_ ()
{
	Branch::Parameters param;
	param.minAngle = -65.f;
	param.maxAngle = 65.f;
	param.minNSubBranch = 3;
	param.maxNSubBranch = 5;
	param.minSubBranchScale = 0.50f;
	param.maxSubBranchScale = 0.80f;

	trunk_ = Branch(param, sf::Vector2f(10,100), sf::Color(101, 40, 0));

	setPosition(position);

	for (std::size_t i=0; i<depth; ++i)
	{
		trunk_.createChildren();
	}
}


//------------------------------------------------------------------------------
// *** sf::Drawable's virtual function: ***
void Tree::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform = getTransform();

	target.draw(trunk_, states);
}


//------------------------------------------------------------------------------

void Tree::grow()
{
	trunk_.createChildren();
}
