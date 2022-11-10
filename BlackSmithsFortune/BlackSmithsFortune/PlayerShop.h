#pragma once
#include <vector>

#include "Weapon.h"
#include "IntInput.h"
#include "Player.h"

//weapon for sale and offer
struct Listing
{
	Weapon* m_weap;
	unsigned int m_offer;

	Listing(Weapon* weap)
		:m_weap(weap)
		,m_offer(0)
	{}

};

////////////////////////////////////////////
//manages items player put up for sale
///////////////////////////////////////
class PlayerShop
{
	IntInput m_input;

	unsigned int m_totalCustomers;//possible customers in the area

	std::vector<Listing*> m_sellList;

	void UpdateOffers();

	void RemoveWeapon(unsigned int index);
	unsigned int GetOffer(unsigned int index);

	void AddWeapon(Weapon* weap);
	bool CheckFull();

public:
	PlayerShop();
	~PlayerShop();

	void SetCustomers(unsigned int num) { m_totalCustomers = num; }
	unsigned int GetTotalCustomers() { return m_totalCustomers; }

	void ShopMenu(Player* p);//loops till player leaves

};
