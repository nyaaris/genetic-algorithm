#include "GeneticAlgorithm.hpp"

GeneticAlgorithm::GeneticAlgorithm(int popSize, int mutationChance, int crossingoverChance, KnapsackProblem& problemInstance) : 
	popSize(popSize), mutationChance(mutationChance), crossingoverChance(crossingoverChance), problem(problemInstance),
	randEngine(rd()), bestFit(problemInstance.getItemCount(), randEngine)
{}


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
	population2 = std::vector<Individual>(popSize, Individual(problem.getItemCount()));

	int genotypeSize = problem.getItemCount();
	for (int i = 0; i < popSize; i++)
		population1.push_back(Individual(genotypeSize, randEngine));
}

void GeneticAlgorithm::geneticIteration(std::vector<Individual>& parentPop, std::vector<Individual>& newPop)
{
	newPopulation(parentPop, newPop);
	mutatePopulation(newPop);
	for (Individual& candidate : newPop)
	{
		if (candidate.getFitness(problem) > bestFit.getFitness(problem))
			bestFit.setGenotype(candidate.getGenotype());
	}
}

void GeneticAlgorithm::newPopulation(std::vector<Individual>& parentPop, std::vector<Individual>& newPop)
{
	int mother1Index, mother2Index;
	std::uniform_int_distribution<int> parentIndices(0, popSize-1);
	int childrenMade = 0;
	while (childrenMade < popSize)
	{
		int a = parentIndices(randEngine), b = parentIndices(randEngine);
		mother1Index = parentPop[a].getFitness(problem) >= parentPop[b].getFitness(problem) ? a : b;
		a = parentIndices(randEngine); b = parentIndices(randEngine);
		mother2Index = parentPop[a].getFitness(problem) >= parentPop[b].getFitness(problem) ? a : b;
		std::pair<std::vector<short>, std::vector<short>> children = parentPop[mother1Index].crossover(parentPop[mother2Index], randEngine, crossingoverChance);
		newPop[childrenMade].setGenotype(children.first);
		if (++childrenMade < popSize)
			newPop[childrenMade].setGenotype(children.second);
	}
}

void GeneticAlgorithm::mutatePopulation(std::vector<Individual>& population)
{
	for (Individual& individual : population)
		individual.mutate(mutationChance, randEngine);
}

