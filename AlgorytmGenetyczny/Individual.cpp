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
	std::uniform_int_distribution<short> booleanDistr = std::uniform_int_distribution<short>(0, 1);
	for (int i = 0; i < binaryGenotype.size(); i++)
		binaryGenotype[i] = booleanDistr(randEngine);
}

int Individual::getFitness(const KnapsackProblem& problem)
{
	return problem.getSolutionValue(binaryGenotype);
}