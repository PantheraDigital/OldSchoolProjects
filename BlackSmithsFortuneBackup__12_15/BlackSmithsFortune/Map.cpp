#include "Map.h"

Map* Map::m_instance = nullptr;



Map::Map()
{
	MapSetUp();
}


Map::~Map()
{
	delete m_instance;
}


Map* Map::getInstance()
{
	if (!m_instance)
	{
		m_instance = new Map();
	}

	return m_instance;
}

void Map::MapSetUp()
{
	LevelLayout m_layout;
	bool block = false;

	for (int y = 0; y < m_layout.m_LevelY; ++y)
	{
		for (int x = 0; x < m_layout.m_LevelX; ++x)
		{
			if (m_layout.m_level[y][x] == g_kWall)
				block = true;
			else
				block = false;

			m_map[y].push_back(new Tile(m_layout.m_level[y][x], block));
		}
	}
}

std::unique_ptr<LocationList> Map::GetShopLocations()//should need this/ just check face insted of storing location/ uless ussing color
{
	std::unique_ptr<LocationList> list = std::make_unique<LocationList>();//unique so that it gets deleted when done but can leav this func
	Vec2d loc;
	for (unsigned int y = 0; y < m_map.size(); ++y)
	{
		for (unsigned int x = 0; x < m_map[y].size(); ++x)
		{
			if (m_map[y][x]->m_face == g_kTown)
			{
				loc.x = x;
				loc.y = y;
				list->m_loc.push_back(loc);
			}

		}
	}

	return list;
}

std::unique_ptr<LocationList> Map::GetAiSpawnPoints()//may need to go through all code and replace pointers 
{
	std::unique_ptr<LocationList> list = std::make_unique<LocationList>();//unique so that it gets deleted when done but can leav this func
	Vec2d loc;
	for (unsigned int y = 0; y < m_map.size(); ++y)
	{
		for (unsigned int x = 0; x < m_map[y].size(); ++x)
		{
			if (m_map[y][x]->m_face == g_kAi)
			{
				loc.x = x;
				loc.y = y;
				list->m_loc.push_back(loc);
			}

		}
	}

	return list;
}