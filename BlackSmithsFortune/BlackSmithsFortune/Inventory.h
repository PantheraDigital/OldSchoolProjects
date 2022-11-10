#pragma once
#include <iostream>

#include "Item.h"
#include "ItemList.h"

//base for player and shop inventories
struct Inventory
{
	Inventory(bool isPlayer);
	~Inventory();

	virtual void FillInv() = 0;

	Item* GetItem(bool metal, int pos);

	bool AddItem(Item* item);

	void SubItem(Item* item);
	void SubItem(bool metal, int pos);

	void ShowInv(bool metals);

	unsigned int GetMetalCount() { return m_metalCount; }
	unsigned int GetGemCount() { return m_gemCount; }

private:
	std::vector<Item*> m_inv;

	unsigned int m_metalCount;
	unsigned int m_gemCount;
	bool m_isPlayer;
};
