#pragma once
#include "Inventory.h"
#include "Weapon.h"


class PlayerInventory : public Inventory
{
	void FillInv();
public:
	PlayerInventory() :Inventory(true) { FillInv(); }
	
};



class Player
{
	unsigned int m_gold;

	std::vector<Weapon*> m_weaponList;

public:
	Player();
	~Player();

	PlayerInventory m_list;

	void AddWeapon(Weapon* weapon) { m_weaponList.push_back(weapon); }
	Weapon* GiveWeap(unsigned int index);

	void ShowWeapons();
	unsigned int GetWeapTotal() { return m_weaponList.size(); }

	void AddGold(unsigned int x) { m_gold += x; }
	unsigned int GetGold() { return m_gold; }


};

