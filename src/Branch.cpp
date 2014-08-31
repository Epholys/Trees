#include "Utility.hpp"
#include "Branch.hpp"


//------------------------------------------------------------------------------
// *** constructor: ***

Branch::Branch()
	: Node()
	, branch_()
{
}

Branch::Branch(sf::Vector2f size, const sf::Color& color)
	: Node()
	, branch_(size)
{
	setOrigin(size.x / 2.f, size.y);

	branch_.setFillColor(color);

	initializeGrowthFunctions();
}


//------------------------------------------------------------------------------
// *** growth functions: ***

void Branch::initializeGrowthFunctions()
{
	using namespace std::placeholders;

	growthFunctions_[Node::Branch] = std::bind(&Branch::growBranch, this, _1);
	growthFunctions_[Node::Leaf] = std::bind(&Branch::growLeaves, this, _1);
}

void Branch::growBranch(RandomParameters::SPtr params)
{
	assert(std::dynamic_pointer_cast<RandomBranchParameters>(params) != nullptr);
	RandomBranchParameters randParams =
		*(std::dynamic_pointer_cast<RandomBranchParameters>(params));
	assert(randParams.checkValidity());
	params.reset();
	

	unsigned int nSubBranch = randInt(randParams.minNSubBranch-1, randParams.maxNSubBranch+1);

	float interval = (randParams.maxAngle - randParams.minAngle) / nSubBranch;
	float minAngleNextSub = randParams.minAngle;
	float maxAngleNextSub = minAngleNextSub + interval;
			
	for(unsigned int i=0; i<nSubBranch; ++i)
	{
		// Determine the size of the next subbranch
		float subBranchScale = (randInt(randParams.minSubBranchScale * 100 - 1,	
										randParams.maxSubBranchScale * 100 + 1)
								/ 100.f);
		sf::Vector2f subSize = subBranchScale * branch_.getSize();

		// Determine the color of the next subbranch
		sf::Color color = branch_.getFillColor();
		sf::Color subColor (color.r + randInt(-3,3),
							color.g + randInt(-3,3),
							color.b);

		Ptr subBranch (new Branch(subSize, subColor));
			
		subBranch->move(branch_.getSize().x / 2.f, 0.f);

		float angle = randInt(minAngleNextSub-1, maxAngleNextSub+1);
		subBranch->rotate(angle);

		minAngleNextSub += interval;
		maxAngleNextSub += interval;
			
		children_.push_back(std::move(subBranch));
	}	
}

void Branch::growLeaves(RandomParameters::SPtr params)
{
	assert(std::dynamic_pointer_cast<RandomLeafParameters>(params) != nullptr);
	RandomLeafParameters randParams =
		*(std::dynamic_pointer_cast<RandomLeafParameters>(params));
	assert(randParams.checkValidity());
	params.reset();


	const float PI = 3.141592653589793f;

	unsigned int nLeaves = randInt(randParams.minNLeaves-1, randParams.maxNLeaves+1);

	float radAngle = 2.f * PI / nLeaves;
	sf::FloatRect branchBounds = branch_.getLocalBounds();
	sf::Vector2f center (branchBounds.left + branchBounds.width / 2.f,
						 branchBounds.top + branchBounds.height / 2.f);

	float distanceFromCenter = branch_.getSize().y / 2.f;

	float radius = branch_.getSize().x;

	for(float angle = 0; angle < 2 * PI; angle += radAngle)
	{
		Leaf::Ptr leaf (new ::Leaf(radius, sf::Color::Green));

		leaf->move(center.x + distanceFromCenter * std::cos(angle),
				   center.y + distanceFromCenter * std::sin(angle));
		leaf->move(-radius / 2.f, -radius / 2.f);

		children_.push_back(std::move(leaf));
	}
}

//------------------------------------------------------------------------------
// *** graphics: ***

void Branch::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(branch_, states);
}
