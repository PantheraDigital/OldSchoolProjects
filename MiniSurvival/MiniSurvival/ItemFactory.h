#pragma once
#include "Item.h"

class ItemFactory
{
	int RandNum(int min, int max)
	{
		return (rand() % max) + min;
	};

	Item * MakeFood();
	Item * MakeWater();
	Item * MakeHealth();

	enum class Scale
	{
		kRare,	
		kNorm,	
		kGood,	
		kBad	
	};

	Scale CheckRarity(int num);
	std::string NameGen(Scale rarity, Item::Stat stat);
	std::string FoodName();
	std::string WaterName();
	std::string HealthName();

public:
	Item * MakeItem();
	Item * MakeItem(Item::Stat stat);
};
