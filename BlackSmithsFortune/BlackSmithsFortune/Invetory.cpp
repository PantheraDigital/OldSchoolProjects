#include "Inventory.h"


Inventory::Inventory(bool isPlayer)
	:m_gemCount(0)
	,m_metalCount(0)
	,m_isPlayer(isPlayer)
{

}

Inventory::~Inventory()
{
	for (unsigned int i = 0; i < m_inv.size(); ++i)
	{
		delete m_inv[i];
	}
}

/////////////////////////////////////////////
//  shop shows price with name and build time
//  player shows name, build time, and bounus price
/////////////////////////////////////////////
void Inventory::ShowInv(bool metals)
{
	int j = 0;//used for count
	for (unsigned int i = 0; i < m_inv.size(); ++i)
	{
		if (metals)
		{
			if (m_inv[i]->m_bonusName == "")//metals have no bonus name
			{
				std::cout << j++;
				std::cout << ". " << m_inv[i]->m_name << ", craft time " << m_inv[i]->m_buildTime << ": g"; 
				if (m_isPlayer)
					std::cout << m_inv[i]->m_bonusPrice << "\n";
				else
					std::cout << m_inv[i]->m_price << "\n";
			}
		}
		else
		{
			if (m_inv[i]->m_bonusName != "")//gems have a bonus name
			{
				std::cout << j++;
				std::cout << ". " << m_inv[i]->m_name << ", craft time " << m_inv[i]->m_buildTime << ": g";
				if (m_isPlayer)
					std::cout << m_inv[i]->m_bonusPrice << "\n";
				else
					std::cout << m_inv[i]->m_price << "\n";
			}
		}
	}

}

/////////////////////////////////////////////////
//takes index and "if metal"
//returns pointer to item
//if no item, returns error item
////////////////////////////////////////////////
Item* Inventory::GetItem(bool metal, int pos)
{
	int j = 0;
	for (unsigned int i = 0; i < m_inv.size(); ++i)
	{
		if (metal)
		{
			if (m_inv[i]->m_bonusName == "")
			{
				if (j == pos)
					return m_inv[i];
				
				++j;
			}
		}
		else
		{
			if (m_inv[i]->m_bonusName != "")
			{
				if (j == pos)
					return m_inv[i];
				
				++j;
			}
		}
	}
	Item* er = new Item("Error", "", 0, 0, 0);
	return er;//error item
}

/////////////////////////////////
//adds item and increases total of item type
//////////////////////////////////////////////////
bool Inventory::AddItem(Item* item)
{
	if (item != nullptr)
	{
		if (item->m_bonusName == "")
		{
			if (m_metalCount >= 10)
			{
				std::cout << "Inventory Full\n";
				return false;
			}
			else
				++m_metalCount;
		}
		else
		{
			if (m_gemCount >= 10)
			{
				std::cout << "Inventory Full\n";
				return false;
			}
			else
				++m_gemCount;
		}

		m_inv.push_back(item);
	}

	return true;
}

//////////////////////////////
//remove item and decrements item type count
////////////////////////////////////////
void Inventory::SubItem(Item* item)
{
	for (unsigned int i = 0; i < m_inv.size(); ++i)
	{
		if (m_inv[i] == item)
		{
			m_inv.erase(m_inv.begin() + i);
			break;
		}
	}

	if (item->m_bonusName == "")
		--m_metalCount;
	else
		--m_gemCount;

}

/////////////////////////////////////////////
//removes item based on "is metal" and index
/////////////////////////////////////////////
void Inventory::SubItem(bool metal, int pos)
{
	int j = 0;
	for (unsigned int i = 0; i < m_inv.size(); ++i)
	{
		
		if (metal)
		{
			if (m_inv[i]->m_bonusName == "")
			{
				if (j == pos)
				{
					m_inv.erase(m_inv.begin() + i);
					--m_metalCount;
				}
				++j;
			}
		}
		else
		{
			if (m_inv[i]->m_bonusName != "")
			{
				if (j == pos)
				{
					m_inv.erase(m_inv.begin() + i);
					--m_gemCount;
				}
				++j;
			}
		}
	}
}


