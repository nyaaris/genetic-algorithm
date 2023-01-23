#include "GeneticAlgorithm.hpp"

GeneticAlgorithm::GeneticAlgorithm(int popSize, int mutationChance, int crossingoverChance, KnapsackProblem* problemInstance) : 
	popSize(popSize), mutationChance(mutationChance), crossingoverChance(crossingoverChance), problem(problemInstance), bestFit(popSize)
{
	randEngine = std::default_random_engine(rd());
}


void GeneticAlgorithm::runAlgorithm(int iterationCount)
{
	generateStartingPopulation();
	for (int i = 0; i < iterationCount; i += 2)
	{
		geneticIteration(population1, population2);
		geneticIteration(population2, population1);
	}
}


void GeneticAlgorithm::generateStartingPopulation()
{
	population1 = std::vector<Individual>();
	population1.reserve(popSize);
	population2 = std::vector<Individual>(popSize);

	int genotypeSize = problem->getItemCount();
	for (int i = 0; i < popSize; i++)
		population1.push_back(Individual(genotypeSize, randEngine));
}

void GeneticAlgorithm::geneticIteration(std::vector<Individual>& parentPop, std::vector<Individual> newPop)
{
	createChildren();
}

