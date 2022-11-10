#pragma once
#include <vector>

#include "Weapon.h"
#include "IntInput.h"
#include "Player.h"

struct Listing
{
	Weapon* m_weap;
	unsigned int m_offer;

	Listing(Weapon* weap)
		:m_weap(weap)
		,m_offer(0)
	{}

};

class PlayerShop
{
	IntInput m_input;

	unsigned int m_totalCustomers;//possible customers in the area

	std::vector<Listing*> m_sellList;

	void UpdateOffers();

	void RemoveWeapon(unsigned int index);
	unsigned int GetOffer(unsigned int index);

	void AddWeapon(Weapon* weap);/////////////////

public:
	PlayerShop(unsigned int customers);
	~PlayerShop();

	void SetCustomers(unsigned int num) { m_totalCustomers = num; }

	void ShopMenu(Player* p);//display weapons for sale, option 0 is add wep, any non-listed key is wait/ wait rechecks for offers on weapons

};
