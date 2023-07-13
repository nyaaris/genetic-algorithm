#pragma once
#include "Individual.hpp"
#include "KnapsackProblem.hpp"
#include "SmartPtr.hpp"
#include <vector>
#include <random>


class GeneticAlgorithm {
private:
	int popSize, mutationChance, crossingoverChance; // mutationChance, crossingoverChance expressed in 1/1000
	KnapsackProblem problem;
	std::vector<Individual> population1, population2;
	Individual bestFit;

	std::random_device rd;
	std::default_random_engine randEngine;

public:
	GeneticAlgorithm(int popSize, int mutationChance, int crossingoverChance, KnapsackProblem& problemInstance);

	void runAlgorithm(int iterationCount);
	Individual getResults() { return bestFit; }

private:
	void generateStartingPopulation();
	void geneticIteration(std::vector<Individual>& parentPop, std::vector<Individual>& newPop);
	void newPopulation(std::vector<Individual>& parentPop, std::vector<Individual>& newPop);
	void mutatePopulation(std::vector<Individual>& population);
};
