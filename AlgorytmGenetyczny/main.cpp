#include "GeneticAlgorithm.hpp"
#include <iostream>

const std::string easyProblem = "easy_10_60_52.txt";
const std::string largeProblem = "large_100_1514.txt";

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

	int populationSize = 27, mutationChance = 150, crossoverChance = 100, iterations = 13;
	solveProblem(easyProblem, populationSize, mutationChance, crossoverChance, iterations);

	return 0;
}