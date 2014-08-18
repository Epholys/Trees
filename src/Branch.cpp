#include "Utility.hpp"
#include "Branch.hpp"



//------------------------------------------------------------------------------
bool Branch::Parameters::checkValidity() const
{
	return
		(minAngle <= maxAngle) &&
		(minNSubBranch <= maxNSubBranch) &&
		(minSubBranchScale <= maxSubBranchScale);
}

//------------------------------------------------------------------------------
// *** constructor: ***

Branch::Branch()
	: param_()
	, branch_()
	, children_()
{
}

Branch::Branch(const Parameters& param, sf::Vector2f size)
	: param_(param)
	, branch_(size)
	, children_()
{
	assert(param.checkValidity());

	setOrigin(size.x / 2.f, size.y);

	branch_.setFillColor(sf::Color::Red);
}


//------------------------------------------------------------------------------
// *** graphics: ***

void Branch::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	drawCurrent(target, states);

	for (const auto& e : children_)
	{
		e->draw(target, states);
	}
}

void Branch::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(branch_, states);
}


//------------------------------------------------------------------------------
// *** tree's functionnality: ***

void Branch::createChildren ()
{
	// `sub' = subBranch

	if (children_.empty())
	{
		unsigned int nSubBranch = randInt(param_.minNSubBranch-1, param_.maxNSubBranch+1);

		float interval = (param_.maxAngle - param_.minAngle) / nSubBranch;
		float minAngleNextSub = param_.minAngle;
		float maxAngleNextSub = minAngleNextSub + interval;
			
		for (std::size_t i=0; i<nSubBranch; ++i)
		{
			float subBranchScale = (randInt(param_.minSubBranchScale * 100 - 1,	
											param_.maxSubBranchScale * 100 + 1)
									/ 100.f);

			sf::Vector2f subSize = subBranchScale * branch_.getSize();

			Ptr subBranch (new Branch(param_, subSize));
			
			subBranch->move(branch_.getSize().x / 2.f, 0.f);

			float angle = randInt(minAngleNextSub-1, maxAngleNextSub+1);
			subBranch->rotate(angle);
			
			minAngleNextSub += interval;
			maxAngleNextSub += interval;
			
			children_.push_back(std::move(subBranch));
		}
	}
	else
	{
		for (auto& e : children_)
		{
			e


















->createChildren();
		}
	}
}
