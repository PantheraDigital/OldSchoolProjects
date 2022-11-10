#pragma once

#include "Item.h"

///////////////////////////////////
//uses items to set stats other than type
//////////////////////////////////
class Weapon
{
public:
	enum class WeaponType
	{
		kDagger,
		kSword,
		kLongsword,
		kAxe
	};

	Weapon(WeaponType type);

	unsigned int GetBuildTime() { return m_buildTime; }
	double GetValue() { return m_value; }
	unsigned int GetReqMetal() { return m_reqMetal; }
	std::string GetName() { return m_name; }

	void SetStats(Item* metal);
	void SetStats(Item* metal, Item* gem);

private:

	double m_value;
	unsigned int m_reqMetal;
	unsigned int m_buildTime;
	std::string m_name;

};
