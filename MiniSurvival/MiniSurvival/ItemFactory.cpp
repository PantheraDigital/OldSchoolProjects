#include "ItemFactory.h"
#include "Item.h"


//////////////////////////////////
// assigns rarity based on number range
//returns enum Scale
/////////////////////////////////
ItemFactory::Scale ItemFactory::CheckRarity(int num)
{
	Scale temp;
	if (num <= 15)
	{
		temp = Scale::kBad;
	}
	else if (num <= 25 && num > 15)
	{
		temp = Scale::kNorm;
	}
	else if (num <= 50 && num > 25)
	{
		temp = Scale::kGood;
	}
	else if (num <= 60 && num > 50)
	{
		temp = Scale::kRare;
	}
	return temp;
}


/////////////////////////////////
//uses a rand num to decide what item to make
//then uses MakeFood, MakeWater, or MakeHealth
// returns item*
/////////////////////////////////
Item * ItemFactory::MakeItem()
{
	switch (RandNum(1, 3))
	{
		case 1:
		{
			return MakeFood();
			break;
		}
		case 2:
		{
			return MakeWater();
			break;
		}
		case 3:
		{
			return MakeHealth();
			break;
		}
	}
	return MakeWater();
}

/////////////////////////////////
//calls a func to make an item with the given stat
//returns item*
/////////////////////////////////
Item * ItemFactory::MakeItem(Item::Stat stat)
{
	switch (stat)
	{
		case Item::Stat::kFood:
		{
			return MakeFood();
			break;
		}
		case Item::Stat::kWater:
		{
			return MakeWater();
			break;
		}
		case Item::Stat::kHealth:
		{
			return MakeHealth();
			break;
		}
		default:
		{
			break;
		}
	}
	return MakeWater();
}

/////////////////////////////////
//assembles food with NameGen(), Scale, and Item Stat
//returns finished item*
/////////////////////////////////
Item * ItemFactory::MakeFood()
{
	int temp = RandNum(1, 60);
	std::string name;

	if (CheckRarity(temp) == Scale::kBad)
	{
		name = NameGen(Scale::kBad, Item::Stat::kFood);
	}
	else if (CheckRarity(temp) == Scale::kNorm)
	{
		name = NameGen(Scale::kNorm, Item::Stat::kFood);
	}
	else if (CheckRarity(temp) == Scale::kGood)
	{
		name = NameGen(Scale::kGood, Item::Stat::kFood);
	}
	else if (CheckRarity(temp) == Scale::kRare)
	{
		name = NameGen(Scale::kRare, Item::Stat::kFood);
	}
	else
		return new Item("ERROR: MakeFood", 0, Item::Stat::kFood);

	return new Item(name, temp, Item::Stat::kFood);
}

/////////////////////////////////
//assembles water with NameGen(), Scale, and Item Stat
//returns finished item*
/////////////////////////////////
Item * ItemFactory::MakeWater()
{
	int temp = RandNum(1, 60);
	std::string name;

	if (CheckRarity(temp) == Scale::kBad)
	{
		name = NameGen(Scale::kBad, Item::Stat::kWater);
	}
	else if (CheckRarity(temp) == Scale::kNorm)
	{
		name = NameGen(Scale::kNorm, Item::Stat::kWater);
	}
	else if (CheckRarity(temp) == Scale::kGood)
	{
		name = NameGen(Scale::kGood, Item::Stat::kWater);
	}
	else if (CheckRarity(temp) == Scale::kRare)
	{
		name = NameGen(Scale::kRare, Item::Stat::kWater);
	}
	else
		return new Item("ERROR: MakeWater", 0, Item::Stat::kWater);

	return new Item(name, temp, Item::Stat::kWater);
}

/////////////////////////////////
//assembles health with NameGen(), Scale, and Item Stat
//returns finished item*
/////////////////////////////////
Item * ItemFactory::MakeHealth()
{
	int temp = RandNum(1, 60);
	std::string name;

	if (CheckRarity(temp) == Scale::kBad)
	{
		name = NameGen(Scale::kBad, Item::Stat::kHealth);
	}
	else if (CheckRarity(temp) == Scale::kNorm)
	{
		name = NameGen(Scale::kNorm, Item::Stat::kHealth);
	}
	else if (CheckRarity(temp) == Scale::kGood)
	{
		name = NameGen(Scale::kGood, Item::Stat::kHealth);
	}
	else if (CheckRarity(temp) == Scale::kRare)
	{
		name = NameGen(Scale::kRare, Item::Stat::kHealth);
	}
	else
		return new Item("ERROR: MakeHealth", 0, Item::Stat::kHealth);

	return new Item(name, temp, Item::Stat::kHealth);
}

/////////////////////////////////
//generates a name using Scale and Item Stat
//returns string
/////////////////////////////////
std::string ItemFactory::NameGen(Scale rarity, Item::Stat stat)
{
	std::string name;

	switch (rarity)
	{
	case Scale::kBad:
	{
		int i = (rand() % 5) + 1;
		switch (i)
		{
		case 1:
		{
			name = "Old ";
			break;
		}
		case 2:
		{
			name = "Stale ";
			break;
		}
		case 3:
		{
			name = "Rotten ";
			break;
		}
		case 4:
		{
			name = "Gross ";
			break;
		}
		case 5:
		{
			name = "Moldy ";
			break;
		}
		}
		break;
	}
	case Scale::kNorm:
	{
		break;
	}
	case Scale::kGood:
	{
		int i = (rand() % 4) + 1;
		switch (i)
		{
		case 1:
		{
			name = "Mediocre ";
			break;
		}
		case 2:
		{
			name = "Tasty ";
			break;
		}
		case 3:
		{
			name = "Adequate ";
			break;
		}
		case 4:
		{
			name = "Regular ";
			break;
		}
		}
		break;
	}
	case Scale::kRare:
	{
		switch (rand() % 3 + 1)
		{
		case 1:
		{
			name = "Perfect ";
			break;
		}
		case 2:
		{
			name = "Fresh ";
			break;
		}
		case 3:
		{
			name = "Pristine ";
			break;
		}
		}
		break;
	}
	}

	switch (stat)
	{
		case Item::Stat::kFood:
		{
			name += FoodName();
			break;
		}
		case Item::Stat::kWater:
		{
			name += WaterName();
			break;
		}
		case Item::Stat::kHealth:
		{
			name += HealthName();
			break;
		}
	}

	return name;
}

/////////////////////////////////
//creates a food based name using rand nums
/////////////////////////////////
std::string ItemFactory::FoodName()
{
	std::string name;
	int container = (rand() % 4) + 1;
	switch (container)
	{
		case 1:
		{
			name = "Can of ";
			break;
		}
		case 2:
		{
			name = "Box of ";
			break;
		}
		case 3:
		{
			name = "Bag of ";
			break;
		}
		case 4:
		{
			name = "Jar of ";
			break;
		}
	}
	int food = (rand() % 5) + 1;
	switch (food)
	{
		case 1:
		{
			name += "Chips";
			break;
		}
		case 2:
		{
			name += "Jerky";
			break;
		}
		case 3:
		{
			name += "Apples";
			break;
		}
		case 4:
		{
			name += "Bread";
			break;
		}
		case 5:
		{
			name += "Unknown Meat";
			break;
		}
	}

	return name;
}

/////////////////////////////////
//creates a water based name using rand nums
/////////////////////////////////
std::string ItemFactory::WaterName()
{
	std::string name;
	int container = (rand() % 3) + 1;
	switch (container)
	{
		case 1:
		{
			name = "Bottle of ";
			break;
		}
		case 2:
		{
			name = "Can of ";
			break;
		}
		case 3:
		{
			name = "Jar of ";
			break;
		}
	}

	int water = (rand() % 3) + 1;
	switch (water)
	{
		case 1:
		{
			name += "Water";
			break;
		}
		case 2:
		{
			name += "Soda";
			break;
		}
		case 3:
		{
			name += "Purple Liquid";
			break;
		}
	}

	return name;
}

/////////////////////////////////
//creates a health based name using rand nums
/////////////////////////////////
std::string ItemFactory::HealthName()
{
	std::string name;
	switch (rand() % 3 + 1)
	{
		case 1:
		{
			name = "Box of ";
			break;
		}
		case 2:
		{
			name = "Tube of ";
			break;
		}
		case 3:
		{
			name = "Pack of ";
			break;
		}
	}

	switch (rand() % 4 + 1)
	{
		case 1:
		{
			name += "Healing Gell";
			break;
		}
		case 2:
		{
			name += "Band Aids";
			break;
		}
		case 3:
		{
			name += "Duct Tape";
			break;
		}
		case 4:
		{
			name += "Gauze";
			break;
		}
	}

	return name;
}