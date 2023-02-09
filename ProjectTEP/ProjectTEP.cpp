#include <iostream>
#include <vector>
#include "CKnapsackProblem.h"
#include "CGeneticAlgorithm.h"

int main() {
    srand(time(NULL));
    CProblem* problem = new CKnapsackProblem();
    if (problem->bReadFile("Params.txt")) {
        CGeneticAlgorithm CGA;
        // CProblem * problem, double popSize, double crossProb, double mutProb, int iterations
        if (CGA.bSetParameters(problem, 5, 0.6, 0.1, 35)){
            CGA.vStart();
            std::cout<<"Best sollution is ->" << problem->dGetSollution();
        }
    }
    delete problem;
}
