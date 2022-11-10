#include "Days.h"
#include "conio.h"


Days::Days()
{
}


Days::~Days()
{
}

////////////////////////
//fills screen with blank lines
//didnt want to use system()
////////////////////////
void Days::FakeClrScrn()
{
	for (int i = 0; i < 70; ++i)
	{
		std::cout << "\n";
	}
}

////////////////////////
//title screen
//true to continue game
//false to quit
////////////////////////
bool Days::Intro()
{
	std::cout << "The world has experienced another pluage and you are one of the remaining survivors. You will need balance out scavenging and staying safly at your home.\n";
	std::cout << "Now remember you can only last 3 days without water and 5 without food.\nDont get too low on food or water or you will wear down faster. Now watch your back you never know whats out there.\n Ready to survive? \n";
	if (User.CharInput() == false)
	{
		End();
		return false;
	}
	else
	{
		FakeClrScrn();
		return true;
	}
}

////////////////////////
//true to continue loop false if player died
////////////////////////
bool Days::PlayerHome()
{
		FakeClrScrn();
		switch (RandNum(1, 3))
		{
		case 1:
		{
			std::cout << "Back at your hide out you look over your stock: \n" << std::endl;
			break;
		}
		case 2:
		{
			std::cout << "Hiden in your shelter you go over what you have: \n" << std::endl;
			break;
		}
		case 3:
		{
			std::cout << "Safe were your home is you think about what you have: \n" << std::endl;
			break;
		}
		}

		
		User.ShowStats();
		User.ShowInventory();

		int tempInput = 1;
		while (tempInput == 1)
		{
			std::cout << "Would you like to 1: use an item or 2: go to sleep \n";
			tempInput = User.NumInput(2);

			if (tempInput == 1)
			{
				if (User.InvEmpt() == true)
				{
					std::cout << "You have nothing to use \n";
				}
				else
				{
					FakeClrScrn();
					std::cout << "Pick an item: \n";
					User.ShowInventory();
					User.UseItem(User.NumInput(User.InvSize() - 1));
					FakeClrScrn();
					User.ShowStats();
					User.ShowInventory();
				}

			}
		}

		if (User.DeathCheck() == false)
		{
			User.SubEnergy(-50);
			User.EndDay();
			FakeClrScrn();
			Plan();
			return true;
		}
		else
		{
			End();
			return false;
		}
}

////////////////////////
//player decides from do nothing, get items, or use item
////////////////////////
void Days::Plan()
{
		bool valid = true;
		while (valid == true)
		{
			std::cout << "It's day " << User.GetDay() << " and you now plan what you will do \n";
			std::cout << "1. Stay in and " << RrndAct() << "\n2. Explore and serch for food. -30 energy \n3. Use an item be for deciding \n";

			int temp = User.NumInput(3);
			switch (temp)
			{
			case 1:
			{
				PlayerHome();
				valid = false;
				break;
			}
			case 2:
			{
				if (User.GetEnergy() >= 30)
					Explore();
				else
				{
					std::cout << "You dont have enough energy. Rest up first. \n";
					valid = false;
				}
				break;
			}
			case 3:
			{
				if (User.InvEmpt() == true)
				{
					std::cout << "You have nothing to use \n";
				}
				else
				{
					FakeClrScrn();
					std::cout << "Pick an item: \n";
					User.ShowInventory();
					User.UseItem(User.NumInput(User.InvSize()));
				}

				break;
			}
			}
		} 
}

////////////////////////
//returns string of random action
////////////////////////
std::string Days::RrndAct()
{
	switch (RandNum(1, 4))
	{
	case 1:
	{
		return "play cards";
		break;
	}
	case 2:
	{
		return "search for a book to read";
		break;
	}
	case 3:
	{
		return "sleep";
		break;
	}
	case 4:
	{
		return "do somthing useless";
		break;
	}
	}
	return " ERROR: Cant find act ";
}

////////////////////////
//gives player random items
////////////////////////
void Days::Explore()
{
	bool valid = true;
	while (valid)
	{
		if (RandEncount() == true)
		{
			FakeClrScrn();
			std::cout << "Continue exploring?\n";
			if (User.CharInput())
			{
				valid = true;
			}
			else
				valid = false;
		}
		else
		{
			FakeClrScrn();
			std::cout << Event.GetEvent() << std::endl;
			User.SubEnergy(30);
			Reward(2);

			if (User.InvFull())
			{
				std::cout << "\n With your inventory now full you head back. \n";
				_getch();
				PlayerHome();
			}

			if (User.GetEnergy() > 10)
			{
				std::cout << "\n Keep exploring?\nYou have " << User.GetEnergy() << " energy left. \n";

				if (User.CharInput())
				{
					valid = true;
				}
				else
					valid = false;
			}
			else
			{
				std::cout << "You are now too tired to continue searching so you head back \n";
				_getch();
				valid = false;
			}
		}

	}

	PlayerHome();
}

////////////////////////
//death screen
//does nothing
////////////////////////
void Days::End()
{
	FakeClrScrn();
	std::cout << "                            You died                            ";
	_getch();
}

////////////////////////
//true if rand encounter happens
//effects player stats diferently based on the Encounters struct
////////////////////////
bool Days::RandEncount()
{
	
	if (Encount.RandEncountCheck() == true)
	{
		std::vector<Item*> temp;
		Encounters TempEncount(Encount.GetEncounter());

		std::cout << TempEncount.m_words << "\n";

		if (TempEncount.m_damage > 0)
			std::cout << "You took " << TempEncount.m_damage << " damage.\n";
		User.Damage(TempEncount.m_damage);

		std::cout << "You have " << User.GetEnergy() << " energy left.\n";
		User.DepleatEnergy(TempEncount.m_energyLv);

		if (TempEncount.m_maxRewards > 0)
			Reward(TempEncount.m_maxRewards);
		
		return true;
	}
	else
		return false;

}

////////////////////////
//displays and rewards player a random amount using the argument as max
////////////////////////
void Days::Reward(int max)
{
	std::vector<Item*> temp;

	for (int i = 0; i < RandNum(1, max); ++i)
		temp.push_back(ItemFac.MakeItem());

	for (unsigned int i = 0; i < temp.size(); ++i)
	{
		temp[i]->Display();
	}
	for (unsigned int n = 0; n < temp.size(); ++n)
	{
		User.GiveItem(temp[n]);
	}
	temp.clear();
}