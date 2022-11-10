#include "Shop.h"


void ShopInventory::FillInv()//fills from item list 
{
	ItemList list;
	
	for (unsigned int i = 0; i < list.m_list.size(); ++i)
		AddItem(list.m_list[i]);
}




Shop::Shop()
{

}


void Shop::ShowItems(bool metals)
{
	m_list.ShowInv(metals);
}

//////////////////////////////////////////
//returns chosen item
//if nothing is picked returns nullptr
///////////////////////////////////////
Item* Shop::BuyItem(unsigned int pGold)
{
	system("cls");
	Item* temp = nullptr;
	std::cout << "0. Metal Shop\n1. Gem Shop\n";

	int select = m_input.GetInput(1);
	system("cls");

	if (select == 0)//metal
	{
		std::cout << "What do you want?\n";
		ShowItems(true);
		std::cout << "\nYou have: " << pGold << " gold.\n";

		select = m_input.GetInput(m_list.GetMetalCount() - 1);
		temp = m_list.GetItem(true, select);
	}
	else//gem
	{
		std::cout << "What would you like to buy?\n";
		ShowItems(false);
		std::cout << "\nYou have: " << pGold << " gold.\n";

		select = m_input.GetInput(m_list.GetGemCount() - 1);
		temp = m_list.GetItem(false, select);
	}


	if (pGold < temp->m_price)
	{
		std::cout << "Not enough gold.\n";
		m_input.Pause();
		return nullptr;
	}
	else
	{
		return temp;
	}
}