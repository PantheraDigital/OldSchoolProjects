#pragma once
#include <vector>
#include <memory>

#include "LevelLayout.h"
#include "Tile.h"

struct Vec2d
{
	int x;
	int y;
};

struct LocationList
{
	std::vector<Vec2d> m_loc;
};



class Map
{
	Map();
	~Map();

	static Map* m_instance;

	std::vector<std::vector<Tile*>> m_map;
	LevelLayout* m_layout;

	void MapSetUp();

public:

	static Map* getInstance();
	char GetFace(unsigned int x, unsigned int y);

	std::unique_ptr<LocationList> GetShopLocations();
	std::unique_ptr<LocationList> GetAiSpawnPoints();

};

//will use another class that takes care of ai and player 