#pragma once

#include <string>
#include <iostream>

class Item
{
public:

	enum class Stat
	{
		kFood,
		kWater,
		kHealth
	};

	Item(std::string name, int replaenish, Stat stat)
		:m_name(name)
		,m_replenish(replaenish)
		,m_stat(stat)
	{}

	~Item() = default;

	std::string GetName() const
	{
		return m_name;
	}

	int GetReplenish() const
	{
		return m_replenish;
	}

	void Display()
	{
		std::cout << GetName() << " : " << GetStat() << " + " << GetReplenish() << " \n";
	}

	//didnt like this defined outside of class scope
	std::string GetStat()
	{
		std::string stat;
	
		switch (m_stat)
		{
			case Stat::kFood:
			{
				stat = "Food";
				break;
			}
			case Stat::kWater:
			{
				stat = "Water";
				break;
			}
			case Stat::kHealth:
			{
				stat = "Health";
				break;
			}
		}
		return stat;
	} 

private:
	std::string m_name;
	int m_replenish;
	Stat m_stat;
};


