#include "LevelManager.h"

LevelManager* LevelManager::getInstance()
{
	if (m_instance == nullptr)
		m_instance = new LevelManager();

	return m_instance;
}

////////////////////////////////
//creates and adds levels and sets player start
/////////////////////////////////
LevelManager::LevelManager()
	:m_currentLv(0)
{
	m_LevelList.clear();

	//temp variables for the layouts in LevelList
	LevelLayout1 layout1; 
	LevelLayout2 layout2;
	LevelLayout3 layout3;
	LevelLayout4 layout4;

	//use layouts to creat a level
	m_LevelList.push_back(new Level(layout1.m_board));
	m_LevelList.push_back(new Level(layout2.m_board));
	m_LevelList.push_back(new Level(layout3.m_board));
	m_LevelList.push_back(new Level(layout4.m_board));

	//set player start
	m_player.SetPosition(1, 1);

}


///////////////////////////////
//deletes pointers
/////////////////////////////
LevelManager::~LevelManager()
{
	delete m_instance;
	for (unsigned int i = 0; i < m_LevelList.size(); ++i)
	{
		delete m_LevelList[i];
	}
}

/////////////////////////////////
//displays current level, player, players keys, and player lives
//////////////////////////////////
void LevelManager::DisplayLv(unsigned int level)
{
	if (level > m_LevelList.size() || level < 0)
		return;

	for (int y = 0; y < g_kLevelY; ++y)
	{
		for (int x = 0; x < g_kLevelX; ++x)
		{
			if (x == m_player.GetPosition().m_x && y == m_player.GetPosition().m_y)
				std::cout << 'P';
			else
			{
				if ((m_LevelList[level])->GetTile(x,y) != nullptr)
					std::cout << m_LevelList[level]->GetTile(x, y)->GetFace();
			}
		}
		std::cout << std::endl;
	}

	std::cout << std::endl << "Lives: " << m_player.GetLives() << std::endl << "Keys: " << m_player.GetKeys();
}

//////////////////////////////////////
//displays level, takes player input, checks if location is clear or if location has any keys
//returns 5 to continue, -1 lost, 1 win
/////////////////////////////////////
int LevelManager::Loop()
{
	system("CLS");
	DisplayLv(m_currentLv);

	
	Vec2D playerCoord = m_player.Input();
	Tile* tileCheck = m_LevelList[m_currentLv]->GetTile(playerCoord);
	
	if (playerCoord.m_x <= g_kLevelX && playerCoord.m_y <= g_kLevelY && playerCoord.m_x > -1 && playerCoord.m_y > -1)//boundries of maps
	{
		if (tileCheck->GetBlockPlayer() != true)//does tile block player
		{
			m_player.SetPosition(playerCoord);
			LevelChange(playerCoord);//only changes if coord is off map
		}

	}

	
	if (tileCheck->GetKillPlayer())//set player and m_tempTile back to respawn
	{
		m_player.SubLife();
		m_currentLv = 0;
		m_player.SetPosition(1, 1);
	}

	if (KeyCheck(m_player.GetPosition()))//check for keys to pickup
	{
		m_player.AddKey();
	}

	if (tileCheck->GetState() == Tile::State::k_door)//if tile is a door
	{
		if (m_player.GetKeys() > 0) //if player has keys
		{
			m_player.SubtractKey();
			m_LevelList[m_currentLv]->GetTile(playerCoord)->SetState(Tile::State::k_background);

			Vec2D doorcheck;
			doorcheck.m_x = 25;
			doorcheck.m_y = 11;

			if (playerCoord == doorcheck)//if player is on special door
			{
				TileSwitch();
			}
		}
	}

	if (tileCheck->GetEnd())
		return 1;

	if (m_player.GetLives() <= 0)
		return -1;


	return 5;

}

//////////////////////////////////////////////
//checks if given coords have a key
//takes away key if player is on it
///////////////////////////////////////////
bool LevelManager::KeyCheck(Vec2D coord)
{
	Vec2D invalidLocation;
	invalidLocation.m_x = -1;
	invalidLocation.m_y = -1;

	for (unsigned int i = 0; i < m_LevelList[m_currentLv]->GetKeyLocals().size(); ++i)
	{
		if (coord == m_LevelList[m_currentLv]->GetKeyLocals()[i])
		{
			m_LevelList[m_currentLv]->SetKeyLocation(i, invalidLocation);

			m_LevelList[m_currentLv]->GetTile(coord)->SetState(Tile::State::k_background);//set tile to normal background
			return true;
		}
	}

	return false;
}


/////////////////////////////////////////
//changes lv when player hits the edge and adjusts player position
///////////////////////////////////////
void LevelManager::LevelChange(Vec2D coord)
{
	if (m_currentLv == 0)
	{
		if (coord.m_x == g_kLevelX-1)
		{
			m_currentLv = 1;
			m_player.SetPosition(1, m_player.GetPosition().m_y);
		}
		else if (coord.m_y == g_kLevelY-1)
		{
			m_currentLv = 2;
			m_player.SetPosition(m_player.GetPosition().m_x, 1);
		}


	}

	if (m_currentLv == 1)
	{
		if (coord.m_x == 0)
		{
			m_currentLv = 2;
			m_player.SetPosition(g_kLevelX-2, m_player.GetPosition().m_y);
		}
		else if (coord.m_y == g_kLevelY-1)
		{
			m_currentLv = 3;
			m_player.SetPosition(m_player.GetPosition().m_x, 1);
		}

	}

	if (m_currentLv == 2)
	{
		if (coord.m_x == g_kLevelX-1)
		{
			m_currentLv = 3;
			m_player.SetPosition(1, m_player.GetPosition().m_y);

		}
		else if (coord.m_y == 0)
		{
			m_currentLv = 0;
			m_player.SetPosition(m_player.GetPosition().m_x, g_kLevelY-2);
		}
	}

	if (m_currentLv == 3)
	{
		if (coord.m_x == 0)
		{
			m_currentLv = 2;
			m_player.SetPosition(g_kLevelX-2, m_player.GetPosition().m_y);
		}
		else if (coord.m_y == 0)
		{
			m_currentLv = 1;
			m_player.SetPosition(m_player.GetPosition().m_x, g_kLevelY-2);
		}

	}
}


////////////////////////////////////////
//shanges face of spicific death tiles in lv 1
///////////////////////////////////////
void LevelManager::TileSwitch()
{
	m_LevelList[0]->GetTile(26, 6)->SetFace(' ');
	m_LevelList[0]->GetTile(26, 9)->SetFace(' ');
	m_LevelList[0]->GetTile(26, 10)->SetFace(' ');
	m_LevelList[0]->GetTile(25, 9)->SetFace(' ');
	m_LevelList[0]->GetTile(23, 8)->SetFace(' ');
}