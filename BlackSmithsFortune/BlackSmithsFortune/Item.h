#pragma once
#include <string>

struct Item
{
	std::string m_name;	//item name
	std::string m_bonusName; // gem name add on
	unsigned int m_price; //purchase price
	int m_bonusPrice; //addition to weapon sell price
	int m_buildTime; // inputs to make weapon

	Item(std::string name, std::string name2, unsigned int price, int price2, int buildTime)
		:m_name(name)
		, m_bonusName(name2)
		, m_price(price)
		, m_bonusPrice(price2)
		, m_buildTime(buildTime)
	{};


};


