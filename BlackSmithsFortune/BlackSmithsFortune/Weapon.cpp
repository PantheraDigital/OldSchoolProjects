#include "Weapon.h"


Weapon::Weapon(WeaponType type)
	:m_buildTime(0)
	,m_value(0)
{	
	switch (type)//sets base stats based on type
	{
		case WeaponType::kDagger:
		{
			m_name = " Dagger";
			m_reqMetal = 1;

			break;
		}
		case WeaponType::kSword:
		{
			m_name = " Sword";
			m_reqMetal = 2;

			break;
		}
		case WeaponType::kLongsword:
		{
			m_name = " Longsword";
			m_reqMetal = 3;
			break;
		}
		case WeaponType::kAxe:
		{
			m_name = " Great Axe";
			m_reqMetal = 4;
			break;
		}
	}
}

/////////////////////////////////////
//sets name, build time, and value based on given metal
///////////////////////////////////////
void Weapon::SetStats(Item* metal)
{
	m_name.insert(0, metal->m_name);
	m_buildTime = (metal->m_buildTime * m_reqMetal);
	m_value = (metal->m_bonusPrice * m_reqMetal);

}

////////////////////////////////////////////////
//sets stats based on given metal and gem
/////////////////////////////////////////
void Weapon::SetStats(Item* metal, Item* gem)
{
	SetStats(metal);
	m_buildTime += gem->m_buildTime;
	m_name += gem->m_bonusName;
	m_value += gem->m_bonusPrice;

	if (m_buildTime <= 1)
		m_buildTime = 2;
}