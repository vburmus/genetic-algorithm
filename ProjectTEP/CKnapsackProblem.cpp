#include <vector>
#include <iostream>
#include "CProblem.h"
#include "CKnapsackProblem.h"
#include <fstream> 
using std::cout;
using std::endl;


CKnapsackItem::CKnapsackItem(double dWeight, double dValue) {
	weight = dWeight;
	value = dValue;
}

CKnapsackProblem::~CKnapsackProblem() {
	for (CKnapsackItem* pItem : pvItems) 
		delete pItem;
}

bool CKnapsackProblem::bIsItemParameterValid(std::string& str) {
	for (char const& c : str) {
		if (std::isdigit(c) == 0)
			return false;
	}

	if (std::stoi(str) <= 0)
		return false;
	return true;
}

bool CKnapsackProblem::bReadFile(std::string fileName) {
	std::ifstream file(fileName);

	if (!file.is_open())
		return false;

	std::string sLine;
	getline(file,sLine);
	dCapacity = std::stoi(sLine.substr(10, sLine.length()));
	
	getline(file, sLine);
	
	double dWeight;
	double dValue;
	int iNumberOfItem = 0;
	 
	while (!file.eof()) {

		getline(file, sLine, ',');
		if (!bIsItemParameterValid(sLine))
			return false;
		dWeight = std::stoi(sLine);
		
		getline(file, sLine,'\n');
		if (!bIsItemParameterValid(sLine))
			return false;
		dValue = std::stoi(sLine);

		iNumberOfItem++;
		CKnapsackItem* item = new CKnapsackItem(dWeight, dValue);
		pvItems.push_back(item);
	}
	iItemsAmount = pvItems.size();
	file.close();
	return true;

}

double CKnapsackProblem::dFit(std::vector<bool>* pvGenotype) {
	double dValue = 0;
	double dWeight = 0;
	for (int i = 0; i < pvGenotype->size();i++) {
		if (pvGenotype->at(i)) {
			dValue += pvItems.at(i)->dGetValue();
			dWeight += pvItems.at(i)->dGetWeight();;
		}
	}
	if(dWeight > dCapacity)
		return 0;
	return dValue;
}
