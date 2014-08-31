#ifndef BRANCH_HPP
#define BRANCH_HPP


#include <SFML/Graphics/Rect.hpp>

#include "Assertion.hpp"
#include "Node.hpp"
#include "Leaf.hpp"


class Branch : public Node
{
public:
	typedef std::unique_ptr<Branch> Ptr;

public:
	Branch();
	Branch(sf::Vector2f size, const sf::Color& color);

private:
	void initializeGrowthFunctions();
	void growBranch(RandomParameters::SPtr params);
	void growLeaves(RandomParameters::SPtr params);

	virtual	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::RectangleShape branch_;
};


#endif // BRANCH_HPP
