#pragma once
#include "Item.h"
#include <vector>


//////////////////////////////
//stores all items available
////////////////////////////////
struct ItemList
{	
	std::vector<Item*> m_list;

	ItemList()
	{
		//name, bounus name, price, bounus price, build time
		m_list.push_back(new Item("Copper", "", 5, 8, 5));
		m_list.push_back(new Item("Bronze", "", 15, 17, 15));
		m_list.push_back(new Item("Iron", "", 35, 40, 35));
		m_list.push_back(new Item("Steel", "", 60, 75, 60));
		m_list.push_back(new Item("Titanium", "", 140, 200, 100));

		m_list.push_back(new Item("Gem of flames", " of flames", 50, 75, 10));
		m_list.push_back(new Item("Gem of storms", " of storms", 100, 150, 20));
		m_list.push_back(new Item("Gem of the mage", " of arcane", 150, 200, 25));
		m_list.push_back(new Item("Gem of strengthening", " of the unbreakable", 200, 300, 50));
		m_list.push_back(new Item("Gem of speed crafting", " of the poorly made", 10, -10, -20));

	}

};
