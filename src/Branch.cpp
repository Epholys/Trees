#include "Utility.hpp"
#include "Branch.hpp"


//-----------------------------------------------------------------------------

bool Branch::RandomParameters::checkValidity() const
{
	return
		(minAngle <= maxAngle) &&
		(minNSubBranch <= maxNSubBranch) &&
		(minSubBranchScale <= maxSubBranchScale);
}


//------------------------------------------------------------------------------
// *** constructor: ***

Branch::Branch()
	: Node()
	, param_()
	, branch_()
{
}

Branch::Branch(const RandomParameters& param, sf::Vector2f size, const sf::Color& color)
	: Node()
	, param_(param)
	, branch_(size)
{
	assert(param.checkValidity());

	setOrigin(size.x / 2.f, size.y);

	branch_.setFillColor(color);

	initializeGrowthFunctions();
}


//------------------------------------------------------------------------------
// *** growth functions: ***

void Branch::initializeGrowthFunctions()
{
	using namespace std::placeholders;

	growthFunctions_[Node::Branch] = std::bind(&Branch::growBranch, this);
	growthFunctions_[Node::Leaf] = std::bind(&Branch::growLeaves, this);
}

void Branch::growBranch()
{
	unsigned int nSubBranch = randInt(param_.minNSubBranch-1, param_.maxNSubBranch+1);

	float interval = (param_.maxAngle - param_.minAngle) / nSubBranch;
	float minAngleNextSub = param_.minAngle;
	float maxAngleNextSub = minAngleNextSub + interval;
			
	for(unsigned int i=0; i<nSubBranch; ++i)
	{
		// Determine the size of the next subbranch
		float subBranchScale = (randInt(param_.minSubBranchScale * 100 - 1,	
										param_.maxSubBranchScale * 100 + 1)
								/ 100.f);
		sf::Vector2f subSize = subBranchScale * branch_.getSize();

		// Determine the color of the next subbranch
		sf::Color color = branch_.getFillColor();
		sf::Color subColor (color.r + randInt(-3,3),
							color.g + randInt(-3,3),
							color.b);

		Ptr subBranch (new Branch(param_, subSize, subColor));
			
		subBranch->move(branch_.getSize().x / 2.f, 0.f);

		float angle = randInt(minAngleNextSub-1, maxAngleNextSub+1);
		subBranch->rotate(angle);

		minAngleNextSub += interval;
		maxAngleNextSub += interval;
			
		children_.push_back(std::move(subBranch));
	}	
}

void Branch::growLeaves()
{
	const float PI = 3.141592653589793f;

	unsigned int nLeaves = 8;

	float radAngle = 2.f * PI / nLeaves;
	sf::FloatRect branchBounds = branch_.getLocalBounds();
	sf::Vector2f center (branchBounds.left + branchBounds.width / 2.f,
						 branchBounds.top + branchBounds.height / 2.f);

	float distanceFromCenter = branch_.getSize().y * 3.f / 4.f;

	float radius = branch_.getSize().x;

	for(float angle = 0; angle < 2 * PI; angle += radAngle)
	{
	   	Leaf::Ptr leaf (new Leaf(param_, radius, sf::Color::Green));

		leaf->move(center.x + distanceFromCenter * std::cos(angle),
				   center.y + distanceFromCenter * std::sin(angle));

		children_.push_back(std::move(leaf));
	}
}

//------------------------------------------------------------------------------
// *** graphics: ***

void Branch::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(branch_, states);
}
