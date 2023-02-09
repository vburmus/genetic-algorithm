#pragma once 
#include<string>
#include <vector>
class CProblem {
public:
	virtual double dFit(std::vector<bool>* genotype) = 0;
	virtual bool bReadFile(std::string sFileName) = 0;
	virtual int iGetItemsSize() = 0;
	virtual void vSetSollution(double solution) = 0;
	virtual double dGetSollution() = 0;
};