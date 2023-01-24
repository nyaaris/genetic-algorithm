#include "KnapsackProblem.hpp"
#include <fstream>

KnapsackProblem::KnapsackProblem(const std::string& path)
{
	readFromFile(path);
}

void KnapsackProblem::readFromFile(const std::string& path)
{
	std::ifstream fin = std::ifstream(path);
	int listSize;
	fin.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fin >> listSize >> knapsackCapacity;
	if (knapsackCapacity <= 0 || listSize <= 0)
		throw std::invalid_argument("Non-positive number found in file " + path);
	itemList = std::vector<Item>(listSize, Item(0, 0));
	for (int i = 0; i < listSize; i++)
	{
		Item& item = itemList[i];
		fin >> item.value >> item.size;
		if (item.value <= 0 || item.size <= 0)
			throw std::invalid_argument("Non-positive number found in file " + path);
	}
	fin.close();
}

void KnapsackProblem::saveToFile(const std::string& path)
{
	std::ofstream fout = std::ofstream(path);
	fout << itemList.size() << ' ' << knapsackCapacity << '\n';
	for (Item item : itemList)
	{
		fout << item.value << ' ' << item.size << '\n';
	}
	fout.close();
}

void KnapsackProblem::generateNewProblem(std::default_random_engine& randEngine)
{
	knapsackCapacity = std::uniform_int_distribution<int>(minCapacity, maxCapacity)(randEngine);
	std::uniform_int_distribution<int> valDistrib = std::uniform_int_distribution<int>(minItemValue, maxItemValue);
	std::uniform_int_distribution<int> sizeDistrib = std::uniform_int_distribution<int>(minItemSize, maxItemSize);

	int desiredListSize = std::uniform_int_distribution<int>(minListSize, maxListSize)(randEngine);
	itemList.clear();
	itemList.reserve(desiredListSize);
	for (int i = 0; i < desiredListSize; i++)
	{
		itemList.push_back(Item(valDistrib(randEngine), sizeDistrib(randEngine)));
	}
}

int KnapsackProblem::getSolutionValue(const std::vector<short>& genotype) const
{
	int value = 0, size = 0;
	if (itemList.size() != genotype.size())
		throw std::invalid_argument("Genotype length doesn't match item list");

	for (int i = 0; i < genotype.size(); i++)
	{
		value += genotype[i] * itemList[i].value;
		size += genotype[i] * itemList[i].size;
	}

	return size > knapsackCapacity ? 0 : value;
}