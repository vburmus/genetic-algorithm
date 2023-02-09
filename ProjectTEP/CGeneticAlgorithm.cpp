#pragma once
#include "CProblem.h"
#include "CIndividual.h"
#include "CGeneticAlgorithm.h"
#include <string>
#include <vector>
#include <iostream>


CGeneticAlgorithm::~CGeneticAlgorithm(){
	for (CIndividual* pIndividual : pvPopulation) 
		delete pIndividual;
}

bool CGeneticAlgorithm::bSetParameters(CProblem* problem, double popSize, double crossProb, double mutProb,int iterations){
	if (problem == nullptr || popSize <= 1 || crossProb < 0 || crossProb > 1 || mutProb < 0 || mutProb > 1 || iterations < 1) {
		return false;
	}
	pProblem = problem;
	dPopSize = popSize;
	dCrossProb = crossProb;
	dMutProb = mutProb ;
	iIterations = iterations;
	bestChild = new CIndividual(pProblem);
	return true;
}


CIndividual* CGeneticAlgorithm::pSelectParentForCrossing(){
	int parentCandidateIndex1 = iGetRandomIndividualIndex();
	int parentCandidateIndex2 = iGetRandomIndividualIndex();

	while (parentCandidateIndex1 == parentCandidateIndex2) {
		parentCandidateIndex1 = iGetRandomIndividualIndex();
		parentCandidateIndex2 = iGetRandomIndividualIndex();
	}	

	if (pvPopulation.at(parentCandidateIndex1)->dCheckFitness() > pvPopulation.at(parentCandidateIndex2)->dCheckFitness())
		return pvPopulation.at(parentCandidateIndex1);
	return pvPopulation.at(parentCandidateIndex2);
}

CIndividual* CGeneticAlgorithm::pSelectOtherForMutating(){
	return pvPopulation.at(iGetRandomIndividualIndex());
}

void CGeneticAlgorithm::vFindAndSetBestIndividual(){
	for (CIndividual* pIndividual : pvPopulation) {
		if (pIndividual->dCheckFitness() > bestChild->dCheckFitness())
			bestChild = new CIndividual(*pIndividual);
	}
}

void CGeneticAlgorithm::vIteration(){
	std::vector<CIndividual*> pvNewPopulation;

	while (pvNewPopulation.size() < dPopSize) {

		CIndividual* pFirstParent = pSelectParentForCrossing();
		CIndividual* pSecondParent = pSelectParentForCrossing();

		if (((float)rand() / RAND_MAX) < dCrossProb) {
			for (CIndividual* child : pFirstParent->vCross(pSecondParent))
				pvNewPopulation.push_back(child);
		} 
		else {
			CIndividual* pFirstParentCopy = new CIndividual(*pFirstParent);
			CIndividual* pSecondParentCopy = new CIndividual(*pSecondParent);

			pvNewPopulation.push_back(pFirstParentCopy);
			pvNewPopulation.push_back(pSecondParentCopy);
		}
	}
	 
	CIndividual* pOther = pSelectOtherForMutating();
	for (CIndividual* pIndividualFromPopulation : pvNewPopulation)
		pIndividualFromPopulation->vMutate(dMutProb,*pOther);
	
	
	for (CIndividual* pIndividual : pvPopulation) 
			delete pIndividual;
	pvPopulation.clear();

	pvPopulation = pvNewPopulation;


	vFindAndSetBestIndividual();
}

void CGeneticAlgorithm::vStart(){
	
	vMakeFirstPopulation();

	for (int i = 0; i < iIterations; i++) 
	
		vIteration();

	pProblem->vSetSollution(bestChild->dCheckFitness());
}

void CGeneticAlgorithm::vMakeFirstPopulation(){
	for (int i = 0; i < dPopSize; i++) {
		CIndividual* pIndividual = new CIndividual(pProblem);

		pIndividual->vSetRandomGenotype(pProblem->iGetItemsSize());
		pvPopulation.push_back(pIndividual);
		
	}
	vFindAndSetBestIndividual();
}
