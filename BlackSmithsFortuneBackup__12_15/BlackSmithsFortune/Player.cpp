#include "Player.h"


void PlayerInventory::FillInv() //player starting materials/ 3 copper
{
	ItemList tempList;
	AddItem(tempList.m_list[0]);
	AddItem(tempList.m_list[0]);
	AddItem(tempList.m_list[0]);
}





Player::Player()
{
}


Player::~Player()
{
	for (unsigned int i = 0; i < m_weaponList.size(); ++i)
	{
		delete m_weaponList[i];
	}
}



void Player::ShowWeapons()
{
	if (!m_weaponList.empty())
	{
		std::cout << "\nWeapons: \n";
		for (unsigned int i = 0; i < m_weaponList.size(); ++i)
		{
			std::cout << i << ". " << m_weaponList[i]->GetName() << ": g" << m_weaponList[i]->GetValue() << "\n";;
		}
	}
}

Weapon* Player::GiveWeap(unsigned int index)
{
	Weapon* temp = m_weaponList[index];

	if (index == 0)
		m_weaponList.erase(m_weaponList.begin());
	else
		m_weaponList.erase(m_weaponList.begin() + index - 1);

	return temp;
}