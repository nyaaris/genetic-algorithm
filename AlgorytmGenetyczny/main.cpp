#include "GeneticAlgorithm.hpp"

void outputTestKnapsack(const std::string& path, std::default_random_engine& randEngine)
{
	KnapsackProblem testKnapsack;
	testKnapsack.generateNewProblem(randEngine);
	testKnapsack.saveToFile(path);
}



int main()
{
	std::random_device rd;
	std::default_random_engine randEngine(rd());
	//outputTestKnapsack("C:/IST1/_3sem/TEP/knapsack2.kp", randEngine);

	return 0;
}