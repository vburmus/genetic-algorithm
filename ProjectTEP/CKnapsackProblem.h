#pragma once
#include <vector>
#include <string>
#include "CProblem.h"

class CKnapsackItem{
private:
	double weight;
	double value;

public:
	CKnapsackItem(double dWeight, double dValue);

	double dGetValue() { return value; };
	double dGetWeight() { return weight; };
};

class CKnapsackProblem : public CProblem {
private :
	std::vector<CKnapsackItem*> pvItems;
	int iItemsAmount;
	double dCapacity;
	double dResult;
	double dSollution;

public:

	CKnapsackProblem(){}
	~CKnapsackProblem();

	bool bIsItemParameterValid(std::string& str);

	bool bReadFile(std::string sFileName);

	double dFit(std::vector<bool>* pvGenotype);
	int iGetItemsSize() { return iItemsAmount; }

	void vSetSollution(double sollution) { dSollution = sollution; }
	double dGetSollution() { return dSollution; }
	
};
