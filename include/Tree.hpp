#ifndef TREE_HPP
#define TREE_HPP


#include <array>

#include "RandomParameters.hpp"
#include "Branch.hpp"

class Tree : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
	typedef std::unique_ptr<Tree> Ptr;

public:
	Tree();
	Tree(unsigned int depth);
	Tree(unsigned int depth, sf::Vector2f position);

	void grow(Node::Type type);
	void grow(Node::Type type, RandomParameters::SPtr params);

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
	Branch::Ptr trunk_;
};


#endif // TREE_HPP
