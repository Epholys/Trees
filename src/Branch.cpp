#include "Utility.hpp"
#include "Branch.hpp"




//-----------------------------------------------------------------------------
Branch::RandomParameters::RandomParameters()
	: minAngle(0)
	, maxAngle(1)
	, minNSubBranch(0)
	, maxNSubBranch(1)
	, minSubBranchScale(0)
	, maxSubBranchScale(1)
{
}

Branch::RandomParameters::RandomParameters(const RandomParameters& param)
	: minAngle(param.minAngle)
	, maxAngle(param.maxAngle)
	, minNSubBranch(param.minNSubBranch)
	, maxNSubBranch(param.maxNSubBranch)
	, minSubBranchScale(param.minSubBranchScale)
	, maxSubBranchScale(param.maxSubBranchScale)
{
}

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

	growthFunctions_.emplace(Node::Branch,
		[this] ()
		{ 
			this->growBranch();
		});
}

void Branch::growBranch()
{
	unsigned int nSubBranch = randInt(param_.minNSubBranch-1, param_.maxNSubBranch+1);

	float interval = (param_.maxAngle - param_.minAngle) / nSubBranch;
	float minAngleNextSub = param_.minAngle;
	float maxAngleNextSub = minAngleNextSub + interval;
			
	for (std::size_t i=0; i<nSubBranch; ++i)
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

//------------------------------------------------------------------------------
// *** graphics: ***

void Branch::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(branch_, states);
}
