#pragma once
#include <vector>
#include <map>

#include "LevelLayout.h"
#include "Tile.h"
#include "Vec2d.h"


/////////////////////////////////
//used to store a list of vec2d*
///////////////////////////////////
struct LocationList
{

	std::vector<Vec2d*> m_loc;

	~LocationList()
	{
		for (unsigned int i = 0; i < m_loc.size(); ++i)
		{
			delete m_loc[i];
		}
	}
};


///////////////////////////////////////////
//singleton
//interface for map
/////////////////////////////////////////
class Map
{
	Map();
	~Map();

	static Map* m_instance;
	const LevelLayout m_layout;

	std::vector<std::vector<Tile*>> m_map;

	Vec2d* m_playerStart;

	void MapSetUp();


public:

	static Map* GetInstance();

	char GetFace(unsigned int x, unsigned int y) { return m_map[y][x]->m_face; }
	char GetFace(Vec2d position) { return m_map[position.m_y][position.m_x]->m_face; }

	//returns if tile blocks movment
	bool GetBlock(Vec2d position) { return m_map[position.m_y][position.m_x]->m_blockPlayer; }
	//if tile is a town
	bool IsTown(Vec2d position) { return (m_map[position.m_y][position.m_x]->m_face == g_kTown); }

	unsigned int GetSizeY() { return m_map.size(); }
	unsigned int GetSizeX() { return m_map[0].size(); }

	std::map<Vec2d, int> GetShopLocations();
	LocationList* GetAiSpawnPoints();

	Vec2d* GetPlayerSpawn() { return m_playerStart; }
	void SetPlayerSpawn(Vec2d* position);

};
