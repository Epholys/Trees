#ifndef BRANCH_HPP
#define BRANCH_HPP


#include <cassert>
#include <memory>
#include <vector>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Branch : public sf::Transformable, public sf::Drawable
{
public:
	typedef std::unique_ptr<Branch> Ptr;

	struct Parameters
	{
		bool checkValidity() const;

		float minAngle;
		float maxAngle;
		unsigned int minNSubBranch;
		unsigned int maxNSubBranch;
		float minSubBranchScale;
		float maxSubBranchScale;
	};

public:
	Branch();
	Branch(const Parameters& param, sf::Vector2f size, const sf::Color& color);

	void createChildren();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	virtual	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	Parameters param_;
	
	sf::RectangleShape branch_;

	std::vector<Ptr> children_;
};


#endif // BRANCH_HPP
