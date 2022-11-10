#include "PlayerShop.h"



PlayerShop::PlayerShop()
	:m_totalCustomers(0)
{
}


PlayerShop::~PlayerShop()
{
	for (unsigned int i = 0; i < m_sellList.size(); ++i)
	{
		delete m_sellList[i];
	}
}

//////////////////////////////////////////////
//checks if offer is greater than 0 on weapon at index
//if offer is accepted then RemoveWeapon() is called and offer is returned 
//else offer is set to 0 and 0 is returned
///////////////////////////////////////////////////
unsigned int PlayerShop::GetOffer(unsigned int index)
{
	system("cls");
	unsigned int gold = 0;
	if (m_sellList[index]->m_offer == 0)
	{
		std::cout << "No offeres on this yet.\n";
		m_input.Pause();
	}
	else
	{
		std::cout << "Accept g" << m_sellList[index]->m_offer << " for " << m_sellList[index]->m_weap->GetName() << "?\n0. yes\n1. no\n";
		if (m_input.GetInput(1) == 0)
		{
			gold += m_sellList[index]->m_offer;
			RemoveWeapon(index);
		}
		else
		{
			m_sellList[index]->m_offer = 0;
		}
	}

	return gold;

}

////////////////////////////////////////
//shows options allong with weapons for sale
//loops until player leaves
//UpdateOffers() at the begining of each loop
/////////////////////////////////////////
void PlayerShop::ShopMenu(Player* p)
{
	while (true)
	{
		unsigned int i = 3;
		unsigned int foo = i;
		unsigned int gold = 0;

		UpdateOffers();

		system("cls");
		std::cout << "0. add weapon\n1. wait\n2. leave\n";

		if (!m_sellList.empty())//if there are weapons for sale display them
		{
			for ( ; (i-foo) < m_sellList.size(); ++i)
			{
				std::cout << i << ". " << m_sellList[i - foo]->m_weap->GetName() << " price: g" << m_sellList[i - foo]->m_weap->GetValue();

				if (m_sellList[i - foo]->m_offer != 0)//if there is an offer on weapon show it
					std::cout << "  offer: g" << m_sellList[i - foo]->m_offer << "\n";
				else
					std::cout << std::endl;
			}
		}

		if (m_totalCustomers < 1)
			std::cout << "No more customers.\n";


		unsigned int input = m_input.GetInput(i);//player chooses option 

		if (input == 0)//add weapon
		{
			if (p->GetWeapTotal() > 0)
			{
				system("cls");
				if (CheckFull())
				{
					std::cout << "No more space. Sell somthing first.\n";
					m_input.Pause();
				}
				else
				{
					p->ShowWeapons();
					input = m_input.GetInput(p->GetWeapTotal() - 1);
					AddWeapon(p->GiveWeap(input));
				}
			}
			else
			{
				std::cout << "No weapons to sell\n";
				m_input.Pause();
			}
		}
		else if (input == 1)//wait
		{//do nothing, run through loop again
		}
		else if (input == 2)//leave
		{
			return;
		}
		else//handle offer on chosen weapon
		{
			if(i > 3)
				p->AddGold(GetOffer(input - foo));
		}


	}
}

void PlayerShop::AddWeapon(Weapon* weap)
{
	Listing* temp = new Listing(weap);
	m_sellList.push_back(temp);
}

void PlayerShop::RemoveWeapon(unsigned int index)
{
	if (index == 0)
		m_sellList.erase(m_sellList.begin());
	else
		m_sellList.erase(m_sellList.begin() + index);
}

////////////////////////////////////
//randomly assigns offer on weapon if any 
/////////////////////////////////////////
void PlayerShop::UpdateOffers()
{
	for (unsigned int i = 0; i < m_sellList.size(); ++i)
	{
		if (m_totalCustomers < 1)
			return;

		if (m_sellList[i]->m_offer == 0)
		{
			int chance = rand() % 100;
			if (chance > 90)//10%
			{
				int offer = 0;
				int base = (int)(m_sellList[i]->m_weap->GetValue());

				int low = (int)(m_sellList[i]->m_weap->GetValue());
				low -= 30;
				if (low < 1)
					low = 1;

				//chance of good offer
				chance = rand() % 100;
				if (chance > 75)//25% for above base price offer
					offer = (int)(rand() % (base + 30) + base);
				else
					offer = (int)(rand() % base + low);//chance to go bellow actual price

				m_sellList[i]->m_offer = offer;
				--m_totalCustomers;
			}
		}

	}

}


bool PlayerShop::CheckFull()
{
	if (m_sellList.size() > 7)
		return true;
	else
		return false;
}