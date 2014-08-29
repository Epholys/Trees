#include "Tree.hpp"


//------------------------------------------------------------------------------
// *** initiaize default parameters: ***
namespace
{
	RandomBranchParameters defaultRandBranchParams = initDefaultBranchParams();
	RandomLeafParameters defaultRandLeafParams = initDefaultLeafParams();
}

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
	, randomParams_()
{
	randomParams_[Node::Branch] =
		std::make_shared<RandomBranchParameters>(defaultRandBranchParams);
	randomParams_[Node::Leaf] =
		std::make_shared<RandomLeafParameters>(defaultRandLeafParams);

	Branch::Ptr trunk(new Branch(sf::Vector2f(20,200),
								 sf::Color(101, 40, 0)));
	trunk_ = std::move(trunk);

	setPosition(position);

	for (std::size_t i=0; i<depth; ++i)
	{
		trunk_->createChildren(Node::Branch, randomParams_[Node::Branch]);
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
	
	grow(type, randomParams_[type]);
}


void Tree::grow(Node::Type type, RandomParameters::SharedPtr params)
{
	trunk_->createChildren(type, std::move(params));
}
