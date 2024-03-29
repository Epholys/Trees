#include "RandomParameters.hpp"


//-----------------------------------------------------------------------------

bool RandomBranchParameters::checkValidity() const
{
	return
		(minAngle >= -180.f) && (maxAngle <= 180.f) && (minAngle <= maxAngle) &&
		(minNSubBranch > 0) && (minNSubBranch <= maxNSubBranch) &&
		(minSubBranchScale > 0.f) && (minSubBranchScale <= maxSubBranchScale);
}

bool RandomLeafParameters::checkValidity() const
{
	return (minNLeaves > 0) && (minNLeaves <= maxNLeaves);
}


//------------------------------------------------------------------------------

RandomBranchParameters initDefaultBranchParams()
{
	RandomBranchParameters param;
	param.minAngle = -65.f;
	param.maxAngle = 65.f;
	param.minNSubBranch = 3;
	param.maxNSubBranch = 5;
	param.minSubBranchScale = 0.50f;
	param.maxSubBranchScale = 0.80f;
	return param;
}

RandomLeafParameters initDefaultLeafParams()
{
	RandomLeafParameters param;
	param.minNLeaves = 8;
	param.maxNLeaves = 8;
	return param;
}


