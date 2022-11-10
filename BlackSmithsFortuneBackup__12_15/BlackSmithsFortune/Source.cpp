
#include <time.h>

#include "Player.h"
#include "Shop.h"
#include "BuildManager.h"
#include "PlayerShop.h"

//tested in windows sdk version 10.0.15063.0

//work on map and ai

int main()
{
	srand((unsigned int)time(NULL));
	std::cout << "Creaft weapons to sell. Materials can be bought in shops using gold. Gems enhance weapons in different ways.\n";
	_getch();
	system("cls");

	Player* p = new Player();
	Shop sh;
	BuildManager b;
	PlayerShop ps(5);
	IntInput input;

	while (true)
	{
		system("cls");
		std::cout << "0. Stats\n1. Shops\n2. Forge weapon\n";
		unsigned int select = input.GetInput(3);


		if (select == 0)//player inv
		{
			system("cls");
			std::cout << "Gold: " << p->GetGold() << "\n";
			std::cout << "Metals:\n";
			p->m_list.ShowInv(true);
			std::cout << "\nGems:\n";
			p->m_list.ShowInv(false);
			p->ShowWeapons();

			_getch();
		}
		else if (select == 1)//shops
		{
			Item* temp = nullptr;
			temp = sh.BuyItem(p->GetGold());
			if (temp)
			{
				p->AddGold(temp->m_price * -1);
				p->m_list.AddItem(temp);
			}
		}
		else if (select == 2)//craft
			b.MakeWeapon(p);
		else if (select == 3)//sell
			ps.ShopMenu(p);
		
		
		
	}

	return 0;
}

