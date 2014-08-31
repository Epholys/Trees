#ifndef RANDOM_PARAMETERS_HPP
#define RANDOM_PARAMETERS_HPP


#include <memory>

struct RandomParameters
{
	typedef std::shared_ptr<RandomParameters> SPtr;
	
	virtual bool checkValidity() const {return false;};
};

struct RandomBranchParameters : public RandomParameters
{

	typedef std::shared_ptr<RandomBranchParameters> SPtr;

	virtual bool checkValidity() const;

	float minAngle;
	float maxAngle;
	unsigned int minNSubBranch;
	unsigned int maxNSubBranch;
	float minSubBranchScale;
	float maxSubBranchScale;
};

struct RandomLeafParameters : public RandomParameters
{
	typedef std::shared_ptr<RandomLeafParameters> SPtr;

	virtual bool checkValidity() const;

	unsigned int minNLeaves;
	unsigned int maxNLeaves;
};


RandomBranchParameters initDefaultBranchParams();
RandomLeafParameters initDefaultLeafParams();


#endif
