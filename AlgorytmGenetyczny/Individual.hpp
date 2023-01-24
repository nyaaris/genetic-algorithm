#pragma once
#include <vector>
#include <random>
#include <string>
#include "KnapsackProblem.hpp"

const int ratioOf1 = 1, ratioOf0 = 7;


class Individual {
private:
	std::vector<short> binaryGenotype;
	bool fitnessStored;
	int fitness;

public:

	Individual(size_t genotypeSize);
	Individual(size_t genotypeSize, std::default_random_engine& randEngine);


	void genRandomGenotype(std::default_random_engine& randEngine);
	void mutate(int mutationChance, std::default_random_engine& randEngine);
	std::pair<std::vector<short>, std::vector<short>> crossover(const Individual& other, std::default_random_engine& randEngine, int crossingoverChance) const;

	int getFitness(const KnapsackProblem& problem);
	const std::vector<short>& getGenotype() const { return binaryGenotype; }
	void setGenotype(const std::vector<short>& newGenotype);

	std::string toString(const KnapsackProblem& problem);
};