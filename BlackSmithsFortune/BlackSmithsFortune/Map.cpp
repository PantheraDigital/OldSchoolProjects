#include "Map.h"

Map* Map::m_instance = nullptr;



Map::Map()
	:m_playerStart(new Vec2d(-1,-1))//start at invalid location
{
	MapSetUp();
}


Map::~Map()//lasts till end of program
{
}


Map* Map::GetInstance()
{
	if (!m_instance)
	{
		m_instance = new Map();
	}

	return m_instance;
}

///////////////////////////////////////////
//reads from mapLayout to make map and set up player spawn point and ai start points
/////////////////////////////////////////////
void Map::MapSetUp()
{
	bool block = false;

	for (int y = 0; y < m_layout.m_LevelY; ++y)
	{
		m_map.push_back(std::vector<Tile*>());
		for (int x = 0; x < m_layout.m_LevelX; ++x)
		{
			if (m_layout.m_level[y][x] == g_kWall)
				block = true;
			else
				block = false;

			if (m_layout.m_level[y][x] == g_kAi || m_layout.m_level[y][x] == g_kPlayer)
				m_map[y].push_back(new Tile(g_kGround, false));
			else
				m_map[y].push_back(new Tile(m_layout.m_level[y][x], block));

			if (m_layout.m_level[y][x] == g_kPlayer)
				SetPlayerSpawn(new Vec2d(x, y));
		}
	}
}

////////////////////////////////////////////
//returns list of towns and populations
/////////////////////////////////////////////////
std::map<Vec2d, int> Map::GetShopLocations()
{
	std::map<Vec2d, int> list;
	int townCount = 0;
	for (int y = 0; y < m_layout.m_LevelY; ++y)
	{
		for (int x = 0; x < m_layout.m_LevelX; ++x)
		{
			if (m_layout.m_level[y][x] == g_kTown)
			{
				list.insert(std::pair<Vec2d, int>(Vec2d(x, y), m_layout.m_townPop[townCount]));
				++townCount;
			}
		}
	}

	return list;
}

///////////////////////////////////////////
//returns list of Ai spawnpoints
////////////////////////////////////////////////
LocationList* Map::GetAiSpawnPoints()
{
	LocationList* list = new LocationList();
	
	for (int y = 0; y < m_layout.m_LevelY; ++y)
	{
		for (int x = 0; x < m_layout.m_LevelX; ++x)
		{
			if (m_layout.m_level[y][x] == g_kAi)
			{
				list->m_loc.push_back(new Vec2d(x, y));
			}

		}
	}

	return list;
}

////////////////////////////////////////////
//set player spawn
////////////////////////////////////////////
void Map::SetPlayerSpawn(Vec2d* position)
{
	delete m_playerStart;
	m_playerStart = position;
}