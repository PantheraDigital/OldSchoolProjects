#include "Pickup.h"

#include "DisplayConsts.h"

Pickup::Pickup(Type pickupType, std::string name, int value, char disp)
	:m_name(name)
	, m_value(value)
	, m_disp(disp)
	, m_type(pickupType)
{
}


Pickup::~Pickup()
{
}

///////////////////////////
//hp will give a potion
//wep will give a random weapon
//weapon names give that weapon
//////////////////////////////
Pickup* Pickup::PickupFac(std::string name)
{
	if (name == "hp")
		return new Pickup(Type::k_HP, "hp", 5, g_kHealth);


	if (name == "armor")
		return new Pickup(Type::k_Armor, "Armor", 2, g_kArmor);


	if (name == "key")
		return new Pickup(Type::k_Key, "key", 1, g_kKey);


	if (name == "dagger")
		return new Pickup(Type::k_Weapon, "Dagger", 6, g_kWeapon);

	if (name == "sword")
		return new Pickup(Type::k_Weapon, "Sword", 8, g_kWeapon);

	if (name == "long")
		return new Pickup(Type::k_Weapon, "Long Sword", 10, g_kWeapon);



	return nullptr;
}

Pickup* Pickup::PickupFac(char name)
{
	if (name == g_kHealth)
		return PickupFac("hp");

	if (name == g_kArmor)
		return PickupFac("armor");

	if (name == g_kKey)
		return PickupFac("key");


	//random wepon
	if (name == g_kWeapon)
	{
		int select = rand() % 3;

		switch (select)
		{
		case 0:
			return PickupFac("sword");

		case 1:
			return PickupFac("dagger");

		case 2:
			return PickupFac("long");


		default:
			return PickupFac("sword");
		}
	}
		
	return nullptr;
}

