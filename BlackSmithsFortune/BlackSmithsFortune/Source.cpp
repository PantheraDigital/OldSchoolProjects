//tested in windows sdk version 10.0.15063.0
#include <time.h>

#include "Player.h"
#include "Shop.h"
#include "BuildManager.h"
#include "PlayerShop.h"
#include "MapManager.h"

//used for comunication between Traveling and main
struct Info
{
	int m_pop;
	bool m_rob;

	Info() 
		:m_pop(-1)
		,m_rob(false)
	{}
};

////////////////////////////////
//wraps up the duties of MapManager in proper order
///////////////////////////////////
class Traveling
{
	MapManager m_map;

	Info m_result;

public: 
	Traveling()
	{}

	~Traveling() {}

	void UpdateMap();
	Info Proccess();
	void SetPop(int pop) { m_map.SetPopOfCurrentCity(pop); }
};

void Traveling::UpdateMap()
{
	if(m_result.m_pop > 0)
		m_map.ResetAi();

	m_map.UpdateAi();
	m_map.UpdatePlayer();

	if (m_map.PlayerRobbed())
		m_result.m_rob = true;
	else
		m_result.m_rob = false;

	m_result.m_pop = m_map.GetTownPop();
	
}

Info Traveling::Proccess()
{
	m_map.DisplayMap();
	return m_result;
}





int main()
{
	Player* p = new Player();
	Shop sh;
	BuildManager b;
	PlayerShop ps;
	Traveling tr;
	IntInput input;

	srand((unsigned int)time(NULL));

	std::cout << "Creaft weapons to sell. Materials can be bought in shops using gold. Gems enhance weapons in different ways. Travel to new cities for more customers, but beware of thieves.\n";
	input.Pause();
	system("cls");

	bool first = true;//start in map first
	unsigned int select;//used for input

	while (true)
	{

		if (!first)//go straight to map if first loop
		{
			system("cls");
			std::cout << "0. Stats\n1. Shops\n2. Forge weapon\n3. Sell Weapons\n4. Travel\n";
			select = input.GetInput(5);
		}
		else
			select = 4;



		if (select == 0)//player inv
		{
			system("cls");
			std::cout << "Gold: " << p->GetGold() << "\n";
			std::cout << "Metals:\n";
			p->m_list.ShowInv(true);
			std::cout << "\nGems:\n";
			p->m_list.ShowInv(false);
			p->ShowWeapons();

			input.Pause();
		}
		else if (select == 1)//shops
		{
			Item* temp = nullptr;
			temp = sh.BuyItem(p->GetGold());
			if (temp)
			{
				if (p->m_list.AddItem(temp))
					p->AddGold(temp->m_price * -1);
				else
					input.Pause();
			}
		}
		else if (select == 2)//craft
		{
			bool keepGoing;
			keepGoing = b.MakeWeapon(p);
			if (keepGoing)
				keepGoing = b.ChooseType(p->m_list.GetMetalCount());

			if (keepGoing)
				keepGoing = b.ChooseMetal(p);

			if (keepGoing)
				b.ChooseGem(p);

			if (keepGoing)
				keepGoing = b.Construct();

			if (!keepGoing)
				b.Refund(p);
			else
				p->AddWeapon(b.GetWeapon());

		}
		else if (select == 3)//sell
		{
			ps.ShopMenu(p);
			tr.SetPop(ps.GetTotalCustomers());//update population

		}
		else if (select == 4)//travel
		{
			Info result;
			while (result.m_pop == -1)
			{				
				result = tr.Proccess();
				tr.UpdateMap();

				if (result.m_rob)
					p->RobPlayer();


			}
			ps.SetCustomers(result.m_pop);
		}

		
		
		first = false;//no longer first loop
	}

	delete p;

	return 0;
}
