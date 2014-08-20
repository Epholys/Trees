#ifndef TREE_HPP
#define TREE_HPP


#include "Branch.hpp"

class Tree : public sf::Transformable, public sf::Drawable
{
public:
	Tree();
	Tree(unsigned int depth);
	Tree(unsigned int depth, sf::Vector2f position);

	void grow(Node::Type type);

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
	Branch::Ptr trunk_;
};


#endif // TREE_HPP
