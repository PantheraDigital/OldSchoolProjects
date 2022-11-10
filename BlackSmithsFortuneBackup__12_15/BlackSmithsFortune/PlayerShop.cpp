#include "PlayerShop.h"



PlayerShop::PlayerShop(unsigned int customers)
	:m_totalCustomers(customers)
{
}


PlayerShop::~PlayerShop()
{
	for (unsigned int i = 0; i < m_sellList.size(); ++i)
	{
		delete m_sellList[i];
	}
}

unsigned int PlayerShop::GetOffer(unsigned int index)
{
	system("cls");
	unsigned int gold = 0;
	if (m_sellList[index]->m_offer == 0)
	{
		std::cout << "No offeres on this yet.\n";
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

		if (!m_sellList.empty())
		{
			for ( ; (i-foo) < m_sellList.size(); ++i)
			{
				std::cout << i << ". " << m_sellList[i - foo]->m_weap->GetName() << " price: g" << m_sellList[i - foo]->m_weap->GetValue();

				if (m_sellList[i - foo]->m_offer != 0)
					std::cout << "  offer: g" << m_sellList[i - foo]->m_offer << "\n";
			}
		}

		if (m_totalCustomers < 1)
			std::cout << "No more customers.\n";


		unsigned int input = m_input.GetInput(i);

		if (input == 0)
		{
			if (p->GetWeapTotal() > 0)
			{
				system("cls");
				p->ShowWeapons();
				input = m_input.GetInput(p->GetWeapTotal() - 1);
				AddWeapon(p->GiveWeap(input));
			}
			else
			{
				std::cout << "No weapons to sell\n";
				_getch();
			}
		}
		else if (input == 1)
		{
		}
		else if (input == 2)
		{
			return;
		}
		else
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
		m_sellList.erase(m_sellList.begin() + index - 1);
}

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
				int high = (int)(m_sellList[i]->m_weap->GetValue());

				int low = (int)(m_sellList[i]->m_weap->GetValue());
				low -= 30;
				if (low < 1)
					low = 1;

				int offer = (int)(rand() % (high + 30) + low);//chance to go bellow or above actual price

				m_sellList[i]->m_offer = offer;
				--m_totalCustomers;
			}
		}

	}

}