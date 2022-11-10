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

void BuildManager::MakeWeapon(Player* player) 
{
	m_gem = nullptr;
	m_metal = nullptr;
	m_weap = nullptr;
	m_temp[3] = { nullptr };

	bool quit = false;


	ChooseType(player->m_list.GetMetalCount());

	if (m_weap == nullptr)
	{
		std::cout << "Not enough metal.\n";
		_getch();
		return;
	}


	quit = ChooseMetal(player);


	if (!quit)
	{
		system("cls");
		std::cout << "Add a gem?\n0. yes\n1. no";
		if (m_input.GetInput(1) == 0)
		{
			if (player->m_list.GetGemCount() == 0)
			{
				system("cls");
				std::cout << "You have no gems.\n";
				_getch();
			}
			else
			{
				system("cls");
				std::cout << "Select a gem.\n";
				player->m_list.ShowInv(false);
				m_gem = player->m_list.GetItem(false, m_input.GetInput(player->m_list.GetGemCount()-1));
			}
		}
	}


	if (!quit)
		quit = Construct();

	if (!quit)
		player->AddWeapon(m_weap);
	else
		Refund(player);

}

void BuildManager::ChooseType(unsigned int metalCount) 
{
	system("cls");
	std::cout << "What to build?\n0. Sword: 2 metal\n1. Longsword: 3 metal\n2. Great Axe: 4 metal\n";
	int select = m_input.GetInput(2);

	switch (select)
	{
		case 0:
		{
			if (metalCount >= 2)
			{
				m_weap = new Weapon(Weapon::WeaponType::kSword);
				m_weapType = "Sword";
				break;
			}
		}
		case 1:
		{
			if (metalCount >= 3)
			{
				m_weap = new Weapon(Weapon::WeaponType::kLongsword);
				m_weapType = "Longsword";
				break;
			}
		}
		case 2:
		{
			if (metalCount >= 4)
			{
				m_weap = new Weapon(Weapon::WeaponType::kAxe);
				m_weapType = "Great Axe";
				break;
			}
		}
	}

}

bool BuildManager::ChooseMetal(Player* player)
{
	for (unsigned int i = 0; i < m_weap->GetReqMetal(); ++i)
	{
		system("cls");


		std::cout << "Choose metal. " << m_weapType << " needs " << m_weap->GetReqMetal() << " metals.\n";
		player->m_list.ShowInv(true);
		m_temp[i] = player->m_list.GetItem(true, m_input.GetInput(player->m_list.GetMetalCount()-1));//get item using metal count of player


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
				return true;
			}

		}
		else
			player->m_list.SubItem(m_temp[i]);
	}

	m_metal = m_temp[0];
	return false;

}


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

			input = _getch() - '0';

			if (input == 1)
				++i;
		}

		while (input != 0)
		{
			system("cls");
			std::cout << m_weap->GetName() << " added to inventory!\nPress 0 to continue.\n";
			input = _getch() - '0';
		}
	}
	else
		return true;


	return false;

}

void BuildManager::Refund(Player* player)//add
{
	for (unsigned int i = 0; i < 3; ++i)
	{
		if (m_temp[i] == nullptr)
			break;

		player->m_list.AddItem(m_temp[i]);
	}

	if (m_gem != nullptr)
		player->m_list.AddItem(m_gem);
}