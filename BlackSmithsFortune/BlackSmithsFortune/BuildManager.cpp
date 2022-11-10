#include "BuildManager.h"

BuildManager::BuildManager() 
{

}

BuildManager::~BuildManager()
{
	delete m_gem;
	delete m_metal;
	delete m_weap;

	for (int i = 0; i < sizeof(m_temp); ++i)
	{
		delete m_temp[i];
	}
}

///////////////////////////////////////
//takes items from player then adds weapon to player or returns items
//true if player weapon list is not full
///////////////////////////////////////
bool BuildManager::MakeWeapon(Player* player) 
{
	if (player->WeaponListFull())
	{
		std::cout << "Not enogh space. Sell a weapon first.\n";
		m_input.Pause();
		return false;
	}

	m_gem = nullptr;
	m_metal = nullptr;
	m_weap = nullptr;
	m_temp[5] = { nullptr };

	return true;

}

///////////////////////////////////////////
//initialize weapon based on chosen type 
//true if metalCount > required metal
////////////////////////////////////////////
bool BuildManager::ChooseType(unsigned int metalCount) 
{

	system("cls");
	std::cout << "What to build?\n0. Dagger: 1 metal\n1. Sword: 2 metal\n2. Longsword: 3 metal\n3. Great Axe: 4 metal\n";
	int select = m_input.GetInput(3);
	//only allows types if player has enough metal
	switch (select)
	{
		case 0:
		{
				m_weap = new Weapon(Weapon::WeaponType::kDagger);
				m_weapType = "Dagger";
				break;
			
		}
		case 1:
		{
				m_weap = new Weapon(Weapon::WeaponType::kSword);
				m_weapType = "Sword";
				break;
			
		}
		case 2:
		{
				m_weap = new Weapon(Weapon::WeaponType::kLongsword);
				m_weapType = "Longsword";
				break;
			
		}
		case 3:
		{
				m_weap = new Weapon(Weapon::WeaponType::kAxe);
				m_weapType = "Great Axe";
				break;
			
		}
	}


	if (m_weap->GetReqMetal() > metalCount)
	{
		std::cout << "Not enough metal.\n";
		m_input.Pause();
		return false;
	}
	else
		return true;

}

//////////////////////////////////////////////
//takes metals from player and checks if they are the same type
//returns false if metals dont match
///////////////////////////////////////////
bool BuildManager::ChooseMetal(Player* player)
{
	unsigned int select;
	for (unsigned int i = 0; i < m_weap->GetReqMetal(); ++i)
	{
		system("cls");
		std::cout << "Choose metal. " << m_weapType << " needs " << m_weap->GetReqMetal() << " metals.\n";

		player->m_list.ShowInv(true);	
		select = m_input.GetInput(player->m_list.GetMetalCount() - 1);

		m_temp[i] = player->m_list.GetItem(true, select);  //get item using metal count of player
	


		if (m_temp[0]->m_name != m_temp[i]->m_name)
		{
			system("cls");
			std::cout << "All metals need to be the same.\n0. Reselect\n1. exit selection\n";
			if (m_input.GetInput(1) == 0)
			{
				player->m_list.AddItem(m_temp[i]);
				m_temp[i] = nullptr;
				--i;
			}
			else
			{
				return false;
			}

		}
		else
			player->m_list.SubItem(m_temp[i]);
	}

	m_metal = m_temp[0];
	return true;

}

///////////////////////////////////////////
//set stats of weapon based on given items
//returns false if player does not make weapon
////////////////////////////////////////////
bool BuildManager::Construct()
{
	system("cls");
	if (m_gem == nullptr)
		m_weap->SetStats(m_metal);
	else
		m_weap->SetStats(m_metal, m_gem);

	std::cout << "Build " << m_weap->GetName() << "?\n0. Yes\n1. No\n";
	if (m_input.GetInput(1) == 0)
	{
		unsigned int i = 0;
		int input = 0;
		float percent = 0;
		while (true)
		{
			percent = (((float)i / m_weap->GetBuildTime()) * 100);//make float to calculate
			system("cls");
			std::cout << "Tap 1 to build.\n";
			std::cout << (int)percent << " % \n";//convert to int for no decimal

			if (i == m_weap->GetBuildTime())
			{
				break;
			}

			input = m_input.Pause();

			if (input == 1)
				++i;
		}

		while (input != 0)
		{
			system("cls");
			std::cout << m_weap->GetName() << " added to inventory!\nPress 0 to continue.\n";
			input = m_input.GetInput(0);
		}
	}
	else
		return false;


	return true;

}

////////////////////////////////////////////
//returns items to player and delets incomplete weapon
///////////////////////////////////////
void BuildManager::Refund(Player* player)
{
	for (unsigned int i = 0; i < sizeof(m_temp); ++i)
	{
		if (m_temp[i] == nullptr)
			break;

		player->m_list.AddItem(m_temp[i]);
	}

	if (m_gem != nullptr)
		player->m_list.AddItem(m_gem);

	delete m_weap;
}

///////////////////////////////////
//takes chosen gem from player
////////////////////////////////////////
void BuildManager::ChooseGem(Player* player)
{
	system("cls");
	std::cout << "Add a gem?\n0. yes\n1. no";
	if (m_input.GetInput(1) == 0)
	{
		if (player->m_list.GetGemCount() == 0)
		{
			system("cls");
			std::cout << "You have no gems.\n";
			m_input.Pause();
		}
		else
		{
			system("cls");
			std::cout << "Select a gem.\n";
			//show player gems
			player->m_list.ShowInv(false);
			//get player selected gem
			m_gem = player->m_list.GetItem(false, m_input.GetInput(player->m_list.GetGemCount() - 1));
			player->m_list.SubItem(m_gem);
		}
	}
}

Weapon* BuildManager::GetWeapon()
{
	if (m_weap)
		return m_weap;
	else
		return nullptr;
}
