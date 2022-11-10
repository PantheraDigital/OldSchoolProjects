#pragma once
#include "Player.h"
#include "IntInput.h"

//1 choose wep type
//2 item select
//3 tap

class BuildManager
{
	IntInput m_input;

	Item* m_metal;
	Item* m_gem;
	Item* m_temp[3];

	Weapon* m_weap;
	std::string m_weapType;


	void ChooseType(unsigned int metalCount);
	bool ChooseMetal(Player* player);

	bool Construct();
	void Refund(Player* player);

public:

	BuildManager();
	~BuildManager();

	void MakeWeapon(Player* player);

};
