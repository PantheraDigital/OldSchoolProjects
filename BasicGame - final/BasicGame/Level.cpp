#include "Level.h"

#include "DisplayConsts.h"


///////////////////////////////
//create level from given layout
//////////////////////////////////
Level::Level(std::vector<std::vector<char>> grid, int spawnTime, User* pUser)
	:m_turn(0)
	,m_spawnTime(spawnTime)
	,m_grid(grid)
{
	SetUser(pUser);

	//loop through and make objects based on char
	for (unsigned int i = 0; i < grid.size(); ++i)
	{
		for (unsigned int j = 0; j < grid[i].size(); ++j)
		{
			if (grid[i][j] == g_kPlayer)//player
				m_pUser->SetPosition(Vec2(j, i));
			else if (grid[i][j] == g_kCircleAi || grid[i][j] == g_kWonderAi || grid[i][j] == g_kChaseAi)//AI
				m_pMonsters.push_back(Pawn::AiFactory(Vec2(j, i),m_pUser, grid[i][j]));
			else if (grid[i][j] == g_kMonSpawn)//spawns
				m_spawnPoints.push_back(Vec2(j, i));
			else if (grid[i][j] == g_kHealth || grid[i][j] == g_kWeapon || grid[i][j] == g_kArmor || grid[i][j] == g_kKey)//items
				m_PickupList.insert(std::pair<Vec2, Pickup*>(Vec2(j, i), Pickup::PickupFac(grid[i][j])));
		}
	}

	//set player to first tile if no spawn
	if (!m_pUser)
		m_pUser->SetPosition(Vec2(0, 0));
}



Level::~Level()
{
	for (unsigned int i = 0; i < m_pMonsters.size(); ++i)
	{
		delete m_pMonsters[i];
	}

	for (std::map<Vec2, Pickup*>::iterator iterator = m_PickupList.begin(); iterator != m_PickupList.end(); ++iterator)
	{
		delete iterator->second;
	}

	m_PickupList.clear();
	m_pMonsters.clear();
}

////////////////////////////////
//loop through and update ai stats and pos
///////////////////////////////
void Level::UpdateAI()
{
	for (unsigned int i = 0; i < m_pMonsters.size(); ++i)
	{
		Vec2 monPos = m_pMonsters[i]->GetNewPos();
		if (InRange(monPos))
		{
			m_grid.ActivateTile(monPos.m_x, monPos.m_y, m_pMonsters[i]);

			if (!m_grid.IsWall(monPos.m_x, monPos.m_y))
			{
				if (m_pUser->GetLocation() == monPos)
				{
					m_pUser->TakeDamage(m_pMonsters[i]->GetAttack());//attack
					m_pMonsters[i]->TakeDamage(m_pUser->GetAttack());
				}
				else if (MonsterCheck(monPos))//dont move into another monster
				{

				}
				else
					m_pMonsters[i]->SetPosition(monPos);//move
			}
		}
	}
}

////////////////////////////////
//update user position and stats
//return true if player hit the exit
/////////////////////////////////
bool Level::UpdateUser()
{
	Vec2 userPos = m_pUser->GetNewPos();
	//if player wants to move somewere in range of grid and is not a wall
	if (InRange(userPos))
	{
		m_grid.ActivateTile(userPos.m_x, userPos.m_y, m_pUser);

		if (!m_grid.IsWall(userPos.m_x, userPos.m_y))
		{
			Pawn* target = MonsterCheck(userPos);
			//if there is a monster there
			if (target)
			{
				target->TakeDamage(m_pUser->GetAttack());//attack
				m_pUser->TakeDamage(target->GetAttack());

				if (target->IsDead())
					EraseMonster(target);
			}
			else
				m_pUser->SetPosition(userPos);//move user

			//pick up item if any
			if (!m_PickupList.empty())
			{
				Pickup* tempItem = m_pUser->PickUpItem(GetItem(userPos));//nullptr if no item to drop

				//drop old item at user last location
				if (tempItem)
					m_PickupList.insert(std::pair<Vec2, Pickup*>(m_pUser->GetLocation(), tempItem));
			}

			//check if player got to exit
			if (m_grid.GetDisplay(userPos.m_x, userPos.m_y) == g_kEnd)
				return true;
		}
	}

	return false;
}

////////////////////////////////
//update positions of playeres and their hp
//false if player died or exited level
////////////////////////////////////
bool Level::Update()
{
	//update tiles
	m_grid.Update();

	if (UpdateUser())//check if user hit the exit
		return false;

	UpdateAI();

	if (!m_spawnPoints.empty())
		if (m_turn % m_spawnTime == 0)//if turn is divisable by spawn time then spawn a monster
			SpawnMonster();

	++m_turn;

	if (m_pUser->IsDead())
		return false;
	else
		return true;
}

/////////////////////////////////
//displays the grid with the players and user stats above
/////////////////////////////////
void Level::Print() 
{
	int x = 0;
	int y = 0;

	for (y; y < m_grid.GetHeight(); ++y)
	{
		for (x; x < m_grid.GetWidth(y); ++x)
		{
			Vec2 location(x, y);//location to display

			if (PrintPawn(location))//prints monster 
			{ }
			else if (m_PickupList.count(location))//print if there is an element at location
			{
				PrintItem(location);
			}
			else
				m_draw(m_grid.GetDisplay(x, y), x, y);

		}
		x = 0;
	}

	//display turn, user hp, weapon
	m_draw("Turn: ", 0, y + 1);
	m_draw(m_turn, 6, y + 1);
	m_pUser->PrintStats(0, y + 2);
}

////////////////////////////////
//checks if a pawn is at position
//if a pawn is there print and return true else false
///////////////////////////////
bool Level::PrintPawn(Vec2 pos) 
{
	Pawn* temp = nullptr;

	if (m_pUser->GetLocation() == pos)
		temp = m_pUser;
	else
		temp = MonsterCheck(pos);

	if (temp)
	{
		if (temp->LowHealth())
			m_draw(temp->GetDisplay(), pos.m_x, pos.m_y, LIGHTRED);
		else if (temp->HasArmor())
			m_draw(temp->GetDisplay(), pos.m_x, pos.m_y, WHITE);
		else
			m_draw(temp->GetDisplay(), pos.m_x, pos.m_y);

		return true;
	}

	return false;
}

/////////////////////////////
//return pointer to monster at position
//or nullptr if none
////////////////////////////
Pawn* Level::MonsterCheck(Vec2 pos) const
{
	for (unsigned int i = 0; i < m_pMonsters.size(); ++i)
	{
		if (m_pMonsters[i]->GetLocation() == pos)
		{
			return m_pMonsters[i];
		}
	}

	return nullptr;
}

///////////////////////////
//display item at location
//////////////////////////////
void Level::PrintItem(Vec2 pos)
{
	if (!m_PickupList.empty())
	{
		//check if element exists
		if (m_PickupList.count(pos))
		{
			m_draw(m_PickupList.at(pos)->GetDisplay(), pos.m_x, pos.m_y);

			//highlight important items
			if (m_pUser->LowHealth())
			{
				if (m_PickupList.at(pos)->GetDisplay() == g_kHealth)
					m_draw(m_PickupList.at(pos)->GetDisplay(), pos.m_x, pos.m_y, LIGHTGREEN);
			}
			
			if (m_PickupList.at(pos)->GetDisplay() == g_kWeapon)
			{
				if (m_pUser->GetAttack() < m_PickupList.at(pos)->GetValue())
					m_draw(m_PickupList.at(pos)->GetDisplay(), pos.m_x, pos.m_y, WHITE);
				else if (m_pUser->GetAttack() > m_PickupList.at(pos)->GetValue())
					m_draw(m_PickupList.at(pos)->GetDisplay(), pos.m_x, pos.m_y, DARKGREY);
			}
		}
	}
}

////////////////////////////
//return pointer to pickup and removes it
//or nullptr if none
////////////////////////////////
Pickup* Level::GetItem(Vec2 pos)
{
	//make iterator
	std::map<Vec2, Pickup*>::iterator it;
	it = m_PickupList.find(pos);

	//if there is no item with that key
	if (it == m_PickupList.end())
		return nullptr;
	
	Pickup* temp = it->second;
	m_PickupList.erase(it);
	return temp;
}

//////////////////////////////////////
//check if position is in grid
////////////////////////////////
bool Level::InRange(Vec2 pos) const
{
	if (pos >= Vec2(0, 0))
	{
		if (pos.m_x <= m_grid.GetWidth(pos.m_y) - 1 && pos.m_y <= m_grid.GetHeight() - 2)
			return true;
	}

	return false;
}

////////////////////////////
//get rid of monster
///////////////////////////////
void Level::EraseMonster(Pawn* monster)
{
	for (unsigned int i = 0; i < m_pMonsters.size(); ++i)
	{
		if (m_pMonsters[i] == monster)
		{
			delete m_pMonsters[i];
			m_pMonsters.erase(m_pMonsters.begin() + i);
		}
	}
}

///////////////////////////
//randomly chooses a monster and spawn point to add a monster
//will not use covered spawn points
/////////////////////////////////
void Level::SpawnMonster()
{
	bool valid = false;
	unsigned int resets = 0;

	while (!valid)
	{
		if (resets >= m_spawnPoints.size())
			valid = true; //dont spawn if all spots are covered

		int spawnIndex = rand() % m_spawnPoints.size();//randomly choose a spawn point
		Vec2 pos(m_spawnPoints[spawnIndex]);

		if (m_pUser->GetLocation() == pos || MonsterCheck(pos))
		{
			//get new position if spawn is covered
			++resets;
		}
		else
		{
			m_pMonsters.push_back(Pawn::RandAiFactory(pos, m_pUser));
			valid = true;
		}

	}
}

///////////////////////////
//replace old user with new one
////////////////////////////
void Level::SetUser(User* pUser)
{
	User* temp = nullptr;

	if (pUser)
	{
		if (m_pUser)//if user exhists
			temp = m_pUser;

		m_pUser = pUser;

		if (temp)//set new useres location to old user location
			m_pUser->SetPosition(temp->GetLocation());
	}
}