#ifndef LEAF_HPP
#define LEAF_HPP


#include <SFML/Graphics/CircleShape.hpp>

#include "Node.hpp"

class Leaf : public Node
{
public:
	typedef std::unique_ptr<Leaf> Ptr;

public:
	Leaf();
	Leaf(float radius, const sf::Color& color);

private:
	virtual	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual bool isOutOfView(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::CircleShape leaf_;
};


#endif // LEAF_HPP
