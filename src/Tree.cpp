#include "Tree.hpp"


//------------------------------------------------------------------------------
// *** initialize default parameters: ***
namespace
{
	std::array<RandomParameters::SPtr, Node::TypeCount> randomParams
	{ std::make_shared<RandomBranchParameters>(initDefaultBranchParams()),
      std::make_shared<RandomLeafParameters>(initDefaultLeafParams()) };
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
{

	Branch::Ptr trunk(new Branch(sf::Vector2f(20,200),
								 sf::Color(101, 40, 0)));
	trunk_ = std::move(trunk);

	setPosition(position);

	for (std::size_t i=0; i<depth; ++i)
	{
		RandomBranchParameters::SPtr param =
			std::dynamic_pointer_cast<RandomBranchParameters>
			(randomParams[Node::Branch]);

		trunk_->createChildren(Node::Branch, param);
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
	
	grow(type, randomParams[type]);
}


void Tree::grow(Node::Type type, RandomParameters::SPtr params)
{
	trunk_->createChildren(type, std::move(params));
}
