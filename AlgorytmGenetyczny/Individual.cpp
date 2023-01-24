#include "Individual.hpp"


Individual::Individual(size_t genotypeSize) : binaryGenotype(genotypeSize, 0)
{
	fitnessStored = false;
}

Individual::Individual(size_t genotypeSize, std::default_random_engine& randEngine) : binaryGenotype(genotypeSize, 0)
{
	fitnessStored = false;
	genRandomGenotype(randEngine);
}


void Individual::genRandomGenotype(std::default_random_engine& randEngine)
{
	fitnessStored = false;
	std::uniform_int_distribution<int> distr(1, ratioOf0+ratioOf1);
	for (int i = 0; i < binaryGenotype.size(); i++)
		binaryGenotype[i] = distr(randEngine) <= ratioOf1 ? 1 : 0;
}

void Individual::mutate(int mutationChance, std::default_random_engine& randEngine)
{
	fitnessStored = false;
	std::uniform_int_distribution<int> distr(1, 1000);
	for (int i = 0; i < binaryGenotype.size(); i++)
	{
		if (distr(randEngine) <= mutationChance)
			binaryGenotype[i] = binaryGenotype[i] ? 0 : 1;
	}
}

std::pair<std::vector<short>, std::vector<short>> Individual::crossover(const Individual& other, std::default_random_engine& randEngine, int crossingoverChance) const
{
	std::pair<std::vector<short>, std::vector<short>> result = std::make_pair(binaryGenotype, other.binaryGenotype);
	if (std::uniform_int_distribution<int>(1, 1000)(randEngine) <= crossingoverChance)
	{
		int cuttingPoint = std::uniform_int_distribution<int>(0, binaryGenotype.size()-2)(randEngine);
		for (int i = cuttingPoint + 1; i < binaryGenotype.size(); i++)
		{
			result.first[i] = other.binaryGenotype[i];
			result.second[i] = binaryGenotype[i];
		}
	}
	return result;
}

int Individual::getFitness(const KnapsackProblem& problem)
{
	if (!fitnessStored)
	{
		fitness = problem.getSolutionValue(binaryGenotype);
		fitnessStored = true;
	}
	return fitness;
}

void Individual::setGenotype(const std::vector<short>& newGenotype)
{ 
	binaryGenotype = newGenotype;
	fitnessStored = false;
}

std::string Individual::toString(const KnapsackProblem& problem)
{
	std::string result = "Fitness = " + std::to_string(getFitness(problem)) + '\n';
	result += "Genotype\n";
	for (short gene : binaryGenotype)
		result += std::to_string(gene) + ' ';
	return result;
}