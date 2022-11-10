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

	void StealMetal();
	void StealGem();
	void StealWeapon();

public:
	Player();
	~Player();

	PlayerInventory m_list;

	void AddWeapon(Weapon* weapon);
	Weapon* GiveWeap(unsigned int index);

	void ShowWeapons();
	unsigned int GetWeapTotal() { return m_weaponList.size(); }

	void AddGold(int x);
	unsigned int GetGold() { return m_gold; }

	void RobPlayer();

	bool WeaponListFull();
};

