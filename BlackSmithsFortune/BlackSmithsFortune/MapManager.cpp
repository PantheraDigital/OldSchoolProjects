#include "MapManager.h"


/////////////////////////////////////
//stores ai and town info from m_map
////////////////////////////////////////
MapManager::MapManager()
	:m_robbed(false)
{
	delete m_player;
	m_player = new PlayerPawn(m_map->GetPlayerSpawn());

	LocationList* tempList = m_map->GetAiSpawnPoints();

	for (unsigned int i = 0; i < tempList->m_loc.size(); ++i)
	{
		m_aiList.push_back(new Ai(tempList->m_loc[i]));
	}

	m_townList = m_map->GetShopLocations();
}


MapManager::~MapManager()
{
	delete m_player;

	for (unsigned int i = 0; i < m_aiList.size(); ++i)
	{
		delete m_aiList[i];
	}

}

////////////////////////////////////////
//print map to screen
////////////////////////////////////
void MapManager::DisplayMap()
{
	system("cls");
	for (unsigned int y = 0; y < m_map->GetSizeY(); ++y)
	{
		for (unsigned int x = 0; x < m_map->GetSizeX(); ++x)
		{
			if (ShowAiAtLoc(Vec2d(x, y)))
			{
			}
			else if (m_player->GetPosition() == Vec2d(x, y))
				std::cout << m_player->GetFace();
			else
				std::cout << m_map->GetFace(x, y);

		}
		std::cout << '\n';
	}
	std::cout << "WASD to move. Avoid " << g_kAi << ". Go to a new town, " << g_kTown << std::endl;
}

//////////////////////////////////
//updates player position and ai positions
////////////////////////////////////
bool MapManager::PlayerRobbed()
{	
	//check for player and ai overlap
	for (unsigned int i = 0; i < m_aiList.size(); ++i)
	{
		if (*(m_aiList[i]->GetPosition()) == *(m_player->GetPosition()))
		{
			return true;
			std::cout << "Somthing was stollen!\n";
		}

	}

	return false;
}

//////////////////////////////////////
//loops through ai list and prints them to screen if at given position
//returns true if ai at position
/////////////////////////////////////
bool MapManager::ShowAiAtLoc(Vec2d position)
{
	for (unsigned int i = 0; i < m_aiList.size(); ++i)
	{
		if (*(m_aiList[i]->GetPosition()) == position)
		{
			std::cout << m_aiList[i]->GetFace();
			return true;
		}
	}
	return false;
}

/////////////////////////////////
//returns population of town at player location
//-1 if no town
//////////////////////////////////////
int MapManager::GetTownPop()
{
	if (m_map->GetFace(m_player->GetPosition()) == g_kTown)
	{
		Vec2d temp(*(m_player->GetPosition()));
		if (m_currentTown.first != temp)
		{
			m_currentTown.first = temp;
			m_currentTown.second = m_townList.at(temp);
			return m_currentTown.second;
		}
		else
			return m_currentTown.second;
	}
	
	return -1;
}

/////////////////////////////////
//loop throgh ai list updating positions
///////////////////////////////////////////
void MapManager::UpdateAi()
{
	if (m_aiList.empty())
		return;


	Vec2d* temp = new Vec2d(0,0);

	for (unsigned int i = 0; i < m_aiList.size(); ++i)
	{
		m_aiList[i]->SetTarget(m_player->GetPosition());

		temp = m_aiList[i]->PredictMove();

		if (AiColisoinCheck(*temp + *(m_aiList[i]->GetPosition())) == false)
			m_aiList[i]->Move(temp);

	}
	
	delete temp;
}

///////////////////////////////////
//move player based on input
///////////////////////////////////////
void MapManager::UpdatePlayer()
{
	Vec2d* tempP;
	tempP = m_player->PredictMove();//get desired direction

	if (m_map->GetBlock(*(m_player->GetPosition()) + *tempP) == false)//check and set
		m_player->Move(tempP);

	delete tempP;
}

/////////////////////////////////////
//checks if given position is player, blocked, or town
//true if blocked or town, false if player or not blocked
///////////////////////////////////////
bool MapManager::AiColisoinCheck(Vec2d position)
{
	if (m_player->GetPosition() == position)
	{
		
		return false;
	}


	if (m_map->GetBlock(position))
		return true;

	if (m_map->IsTown(position))
		return true;
	

	return false;
}

////////////////////////////
//place ai back to starting positions
//////////////////////////////
void MapManager::ResetAi()
{
	for (unsigned int i = 0; i < m_aiList.size(); ++i)
	{
		m_aiList[i]->SetPosToStart();
	}
}
