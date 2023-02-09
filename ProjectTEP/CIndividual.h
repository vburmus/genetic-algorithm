#pragma once
#include "CProblem.h"
#include<vector>
class CIndividual {
private:
	CProblem* pProblem;
	std::vector<bool>* pvGenotype;
	double dFitness;
	bool bIsActualFitness;
public:
	CIndividual(CProblem* pProblem);
	CIndividual(CIndividual& individual);
	~CIndividual();

	double dCheckFitness();
	void vSetRandomGenotype(int iSize);

	std::vector<CIndividual*> vCross(CIndividual* pSecondParent);
	void vMutate(double mutProb,CIndividual& pOther);

	void vPrint();
};