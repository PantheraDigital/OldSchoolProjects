#pragma once
#include <vector>
#include "Item.h"

class Player
{
	int m_health, m_food, m_water, m_energy, m_daysSurv, m_maxInvSpace;
	std::vector<Item*> m_inventory;

	
	bool Dehydrated();
	bool Starving();
	bool Fatigue();

public:
	Player();
	~Player();

	bool CharInput();
	int NumInput(int options);

	bool InvFull();
	bool InvEmpt();
	int InvSize();

	void EndDay();
	bool DeathCheck();

	void DepleatEnergy(int lv);
	void SubEnergy(int amount);
	void Damage(int dam);

	void GiveItem(Item* found);
	void UseItem(int item);

	void ShowStats();
	void ShowInventory();

	int GetDay() { return m_daysSurv; }
	int GetEnergy() { return m_energy; }
};

