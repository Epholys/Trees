#ifndef BRANCH_HPP
#define BRANCH_HPP


#include <cassert>

#include "Node.hpp"

class Branch : public Node
{
public:
	typedef std::unique_ptr<Branch> Ptr;

	struct RandomParameters
	{
		RandomParameters();
		RandomParameters(const RandomParameters& param);
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
	Branch(const RandomParameters& param, sf::Vector2f size, const sf::Color& color);

private:
	void initializeGrowthFunctions();
	void growBranch();

	virtual	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	RandomParameters param_;
	
	sf::RectangleShape branch_;
};


#endif // BRANCH_HPP
