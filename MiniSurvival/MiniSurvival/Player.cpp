#include "Player.h"
#include "conio.h"

#include <iostream>



Player::Player()
	:m_health(100),
	m_food(100),
	m_water(100),
	m_energy(100),
	m_daysSurv(0),
	m_maxInvSpace(9)
{
}

Player::~Player()
{
	m_inventory.clear();
}

void Player::SubEnergy(int amount)
{
	m_energy -= (amount);

	if (m_energy > 100)
		m_energy = 100;

	if (m_energy < -10)
		m_energy = -10;
}

////////////////////////
//takes in level of activity and subtracts energy
////////////////////////
void Player::DepleatEnergy(int lv)
{
	switch (lv)
	{
		case 1:
		{
			if (Fatigue())
				m_energy -= 20;
			else
				m_energy -= 10;
			break;
		}
		case 2:
		{
			if (Fatigue())
				m_energy -= 40;
			else
				m_energy -= 20;
			break;
		}
		case 3:
		{
			if (Fatigue())
				m_energy -= 80;
			else
				m_energy -= 40;
			break;
		}
	}
}

////////////////////////
//adds item* to player
////////////////////////
void Player::GiveItem(Item* found)
{
	if (m_inventory.size() > m_maxInvSpace)
	{
		std::cout << "Inventory full. Max items: 10 \n" << std::endl;
	}
	else
	m_inventory.push_back(found);
}

////////////////////////
//damages player
////////////////////////
void Player::Damage(int dam)
{
	m_health -= dam;
}

////////////////////////
//adjuststs player stats based on item picked
//takes in item index location
////////////////////////
void Player::UseItem(int item)
{
	bool valid = false;
	while (valid == false)
	{
		if (item > m_inventory.size())
		{
			std::cout << "No item \n";
		}
		else
		{
			std::cout << "Use " << m_inventory[item]->GetName() << "?\n";

			if (CharInput() == true)
			{
					std::string use = m_inventory[item]->GetStat();
				if (use == "Health")
					m_health += m_inventory[item]->GetReplenish();
				else if (use == "Food")
					m_food += m_inventory[item]->GetReplenish();
				else
					m_water += m_inventory[item]->GetReplenish();

				if (m_health > 110)
					m_health = 110;

				if (m_food > 110)
					m_food = 110;

				if (m_water > 110)
					m_water = 110;

				m_inventory.erase(m_inventory.begin() + (item));
			}
		}
		valid = true;
	}
}

////////////////////////
//displayes and numbers player items
////////////////////////
void Player::ShowInventory()
{
	if (m_inventory.size() > 0)
	{
		for (unsigned int i = 0; i < m_inventory.size(); ++i)
		{
			std::cout << i << ". ";
			m_inventory[i]->Display();
		}
	}
	else
		std::cout << "Your inventory is empty. \n";
}

////////////////////////
//displays player stats : health, days, water, food, energy
////////////////////////
void Player::ShowStats()
{
	std::cout << "Days survived: " << m_daysSurv << "\n" << " Health: " << m_health << "\n" << " Water: " << m_water << "\n" << " Hunger: " << m_food << "\n" << " Energy: " << m_energy << "\n\n";
}

////////////////////////
//subtracts from water and food then increments daysSurv
////////////////////////
void Player::EndDay()
{
	if (Starving())
		m_food -= 20 * 2;
	else
		m_food -= 20;

	if (Dehydrated())
		m_water -= 34 * 2;
	else
		m_water -= 34;

	if (m_water < -10)
		m_water = -10;

	if (m_food < -10)
		m_food = -10;


		++m_daysSurv;
}

////////////////////////
//returns false if alive and true if dead
////////////////////////
bool Player::DeathCheck()
{
	if (m_health <= 0)
		return true;
	else if (m_water < 0)
		return true;
	else if (m_food < 0)
		return true;
	else
		return false;
}

////////////////////////
//true if food is low
////////////////////////
bool Player::Starving()
{
	if (m_food <= 30)
		return true;
	else
		return false;
}

////////////////////////
//true if water is low
////////////////////////
bool Player::Dehydrated()
{
	if (m_water <= 30)
		return true;
	else
		return false;
}

////////////////////////
//true if starving or dehydreated
////////////////////////
bool Player::Fatigue()
{
	if (Dehydrated() || Starving())
		return true;
	else
		return false;
}

////////////////////////
//true if y and false if n
////////////////////////
bool Player::CharInput()
{
	char input = 'o'; 
	bool valid = false;

	while (valid == false)
	{
		input = _getch();
		if (input != 'y' && input != 'Y' && input != 'n' && input != 'N')
		{
			std::cout << "Pleas use 'y' or 'n' \n" << std::endl;
		}
		else
			valid = true;
	}

	if (input == 'y' || input == 'Y')
		return true;
	else if ((input == 'n' || input == 'N'))
		return false;

	return false;
}

////////////////////////
//int input restricted to amount of options given
////////////////////////
int Player::NumInput(int options)
{
	bool valid = false;
	int input;
	while (valid == false)
	{
		input = _getch() - '0';
		if (input > options)
		{
			std::cout << "Number to high." << std::endl;
		}
		else if (input < 0)
		{
			std::cout << "Number to low." << std::endl;
		}
		else
			valid = true;
	}
	return input;
}

////////////////////////
//true if inventory is full
////////////////////////
bool Player::InvFull()
{
	if (m_inventory.size() >= m_maxInvSpace)
		return true;
	else
		return false;
}

////////////////////////
//true if inventory is empty
////////////////////////
bool Player::InvEmpt()
{
	if (m_inventory.size() <= 0)
		return true;
	else
		return false;
}

////////////////////////
// inventory vector size
////////////////////////
int Player::InvSize()
{
	return m_inventory.size();
}
