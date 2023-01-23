#pragma once
#include <string>
#include <vector>
#include <random>

const int minCapacity = 1200, maxCapacity = 2200;
const int minItemValue = 295, maxItemValue = 1003;
const int minItemSize = 20, maxItemSize = 36;
const int minListSize = 72, maxListSize = 98;

class KnapsackProblem {
private:
	struct Item
	{
		int value, size;
		Item(int VALUE, int SIZE) : value(VALUE), size(SIZE){}
	};

	int knapsackCapacity;
	std::vector<Item> itemList;

public:
	KnapsackProblem() = default;
	KnapsackProblem(const std::string& path);
	void readFromFile(const std::string& path);
	void saveToFile(const std::string& path);
	void generateNewProblem(std::default_random_engine& engine);
	int getSolutionValue(const std::vector<short>& genotype) const;
	int getItemCount() const { return itemList.size(); }
};

