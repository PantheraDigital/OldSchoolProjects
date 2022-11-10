#pragma once
#include "IntInput.h"
#include "Player.h"
#include "Inventory.h"




class ShopInventory : public Inventory
{
private:
	void FillInv();

public:
	ShopInventory() :Inventory(false) { FillInv(); }
};


class Shop
{
	ShopInventory m_list;
	IntInput m_input;

	void ShowItems(bool metals);

public:
	Shop();
	~Shop() {}

	Item* BuyItem(unsigned int pGold);

};
