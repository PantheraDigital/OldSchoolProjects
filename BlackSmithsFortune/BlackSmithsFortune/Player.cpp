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
	AddGold(5);//starting gold
}


Player::~Player()
{
	for (unsigned int i = 0; i < m_weaponList.size(); ++i)
	{
		delete m_weaponList[i];
	}
}


///////////////////////////////////
//display weapons' names and price
///////////////////////////////////
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

///////////////////////////////////////////
//remove weapon at index and return it
///////////////////////////////////////////
Weapon* Player::GiveWeap(unsigned int index)
{
	Weapon* temp = m_weaponList[index];

	if (index == 0)
		m_weaponList.erase(m_weaponList.begin());
	else
		m_weaponList.erase(m_weaponList.begin() + index - 1);

	return temp;
}

////////////////////////////////////////
//add weapon to player
/////////////////////////////////////////////
void Player::AddWeapon(Weapon* weapon)
{
	if (weapon)
		m_weaponList.push_back(weapon);
}

////////////////////////////////////
//add gold/ if gold becomes > 0, set to 0
///////////////////////////////////
void Player::AddGold(int x) 
{ 
	m_gold += x;

	if (m_gold < 0)
		m_gold = 0; 
}

void Player::RobPlayer()
{
	//set posibilities
	bool hasGem = m_list.GetGemCount() > 0 ? true : false;
	bool hasMetal = m_list.GetMetalCount() > 0 ? true : false;
	bool hasWeapon = m_weaponList.size() > 0 ? true : false;

	int choose;

	//loop until somthing is stollen
	while (hasMetal == true || hasGem == true || hasWeapon == true)
	{
		choose = rand() % 100;
		if (choose >= 50)
		{
			if (hasMetal == true)
			{
				StealMetal();
				hasMetal = false;
				hasGem = false;
				hasWeapon = false;
			}
		}
		else if (choose >= 20 && choose < 50)
		{
			if (hasGem == true)
			{
				StealGem();
				hasMetal = false;
				hasGem = false;
				hasWeapon = false;
			}
		}
		else
		{
			if (hasWeapon == true)
			{
				StealWeapon();
				hasMetal = false;
				hasGem = false;
				hasWeapon = false;
			}
		}
	}
}

bool Player::WeaponListFull()
{
	if (m_weaponList.size() > 10)
		return true;
	else
		return false;
}

void Player::StealMetal()
{
	int choose = rand() % m_list.GetMetalCount();
	m_list.SubItem(true, choose);
}

void Player::StealGem()
{
	int choose = rand() % m_list.GetGemCount();
	m_list.SubItem(false, choose);
}

void Player::StealWeapon()
{
	int choose = rand() % m_weaponList.size();
	m_list.SubItem(true, choose);
}