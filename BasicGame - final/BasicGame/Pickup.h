#pragma once
#include <string>
class Pickup
{
public:
	static Pickup* PickupFac(char name);
	static Pickup* PickupFac(std::string name);

	~Pickup();

	enum class Type
	{
		k_Weapon
		,k_HP
		,k_Armor
		,k_Key
	};

	//for finding item type and displaying name
	std::string GetName() const { return m_name; }

	//value of item effect
	int GetValue() const { return m_value; }

	//what to display on level
	char GetDisplay() const { return m_disp; }

	Type GetType() { return m_type; }

protected:
	Pickup(Type pickupType, std::string name, int value, char disp);

private:
	std::string m_name; //invintory name
	char m_disp;		//shown in level
	int m_value;		//value of effect
	Type m_type;		//item type
};

