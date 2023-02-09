#include<iostream>
#include "CIndividual.h"


CIndividual::CIndividual(CProblem* problem) {
	pProblem = problem;
	pvGenotype = new std::vector<bool>;
	dFitness = 0;
	bIsActualFitness = false;
}

CIndividual::CIndividual(CIndividual& individual) {
	pProblem = individual.pProblem;

	pvGenotype = new std::vector<bool>;
	for (int i = 0; i < individual.pvGenotype->size();i++) {
		pvGenotype->push_back(individual.pvGenotype->at(i));
	}

	dFitness = individual.dFitness;
	bIsActualFitness = true;
}

CIndividual::~CIndividual() {
	delete pvGenotype;
}

double CIndividual::dCheckFitness() {
	if (!bIsActualFitness) {
		dFitness = pProblem->dFit(pvGenotype);
		bIsActualFitness = true;
	}
	return dFitness;
}

void CIndividual::vSetRandomGenotype(int iSize) {
	for (int i = 0; i < iSize; i++) 
		pvGenotype->push_back(rand()%2);
}

std::vector<CIndividual*> CIndividual::vCross(CIndividual* pSecondParent) {

	CIndividual* pFirstChild = new CIndividual(pProblem);
	CIndividual* pSecondChild = new CIndividual(pProblem);

	int iSeparateIndex = rand() % 3 + 1;

	for (int i = 0; i < iSeparateIndex; i++) {
		pFirstChild->pvGenotype->push_back(pvGenotype->at(i));
		pSecondChild->pvGenotype->push_back(pSecondParent->pvGenotype->at(i));
	}

	for (int i = iSeparateIndex; i < pvGenotype->size(); i++) {
		pFirstChild->pvGenotype->push_back(pSecondParent->pvGenotype->at(i));
		pSecondChild->pvGenotype->push_back(pvGenotype->at(i));
	}

	
	std::vector<CIndividual*> pvChildren;
	pvChildren.push_back(pFirstChild);
	pvChildren.push_back(pSecondChild);

	return pvChildren;
}

void CIndividual::vMutate(double mutProb,CIndividual& pOther) {
	for (int i = 0; i < pvGenotype->size();i++) {
		if (pvGenotype->at(i) != pOther.pvGenotype->at(i)) {
			if (((float)rand() / RAND_MAX) < mutProb)
				pvGenotype->at(i) = !pvGenotype->at(i);
		}
	}
}
void CIndividual::vPrint()
{
	std::cout << std::endl;
	std::cout << "_______________" << std::endl;
	std::cout <<"genotype" << std::endl;
	for (bool gen : *pvGenotype) {
		std::cout << gen << "  ";
	}
	std::cout << std::endl;
	std::cout << "fitness = " << dCheckFitness();
}

