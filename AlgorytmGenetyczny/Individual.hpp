#pragma once
#include <vector>
#include <random>
#include "KnapsackProblem.hpp"


class Individual {
private:
	std::vector<short> binaryGenotype;
	bool fitnessStored;
	int fitness;

public:

	Individual(size_t genotypeSize);
	Individual(size_t genotypeSize, std::default_random_engine& randEngine);


	void genRandomGenotype(std::default_random_engine& randEngine);

	int getFitness(const KnapsackProblem& problem);
};