#pragma once
#include<vector>
#include "CIndividual.h"
#include "CProblem.h"
class CGeneticAlgorithm {
private:
	CProblem* pProblem;
	double dPopSize;
	double dCrossProb;
	double dMutProb;
	int iIterations;
	
	std::vector<CIndividual*> pvPopulation;
	CIndividual* bestChild;
public:
	CGeneticAlgorithm() {}
	~CGeneticAlgorithm();
	bool bSetParameters(CProblem* cProblem, double dPopSize, double dCrossProb, double dMutProb,int iIterations);
	int iGetRandomIndividualIndex() { return rand() % pvPopulation.size(); }
	
	CIndividual* pSelectParentForCrossing();
	CIndividual* pSelectOtherForMutating();
	
	void vFindAndSetBestIndividual();

	void vIteration();
	void vStart();
	void vMakeFirstPopulation();
};