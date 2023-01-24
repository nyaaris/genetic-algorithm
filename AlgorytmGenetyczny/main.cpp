#include "GeneticAlgorithm.hpp"
#include <iostream>

const std::string easyProblem = "C:/IST1/_3sem/TEP/easy_10_60_52.txt";
const std::string largeProblem = "C:/IST1/_3sem/TEP/large_100_1514.txt";
const std::string myProblem = "C:/IST1/_3sem/TEP/knapsack1.txt";

void outputTestKnapsack(const std::string& path, std::default_random_engine& randEngine)
{
	KnapsackProblem testKnapsack;
	testKnapsack.generateNewProblem(randEngine);
	testKnapsack.saveToFile(path);
}

void solveProblem(const std::string& path, int popSize, int mutChance, int crossChance, int iterations)
{
	KnapsackProblem knapsack(path);
	SmartPtr<GeneticAlgorithm> ga(new GeneticAlgorithm(popSize, mutChance, crossChance, knapsack));
	ga->runAlgorithm(iterations);
	std::cout << ga->getResults().toString(knapsack);
}


int main()
{
	std::random_device rd;
	std::default_random_engine randEngine(rd());
	//outputTestKnapsack(myProblem, randEngine);

	solveProblem(easyProblem, 27, 150, 100, 13);

	return 0;
}