#pragma once
#include <iostream>
#include <map>

#include "Map.h"
#include "Pawn.h"

//////////////////////////////
//in charge of collisions, pawns, and towns
///////////////////////////////
class MapManager
{
	Map* m_map = Map::GetInstance();

	PlayerPawn* m_player;

	std::pair<Vec2d, int> m_currentTown;//town most recently visited by player

	std::vector<Ai*> m_aiList;
	std::map<Vec2d, int> m_townList;//position,population

	bool m_robbed;

	bool ShowAiAtLoc(Vec2d position);//need system to check all predict movments for collision then set locations 

	bool AiColisoinCheck(Vec2d position);


public:

	MapManager();
	~MapManager();

	void ResetAi();

	bool PlayerRobbed();

	void UpdateAi();
	void UpdatePlayer();

	void DisplayMap();

	int GetTownPop();//returns -1 if no town
	void SetPopOfCurrentCity(int population) { m_currentTown.second = population; }
};

