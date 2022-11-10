#pragma once

#include <map>

#include "Grid.h"
#include "Pawn.h"
#include "Pickup.h"
#include "DrawFunction.h"

//displays game and tracks positions of user and monsters
//also contains and manages spawn points and pickups
class Level
{
private:
	//pointer to the person playing
	User* m_pUser;

	std::vector<Pawn*> m_pMonsters;
	std::vector<Vec2> m_spawnPoints;

	std::map<Vec2, Pickup*, Vec2MapSort> m_PickupList;

	//2d vector of Tile*
	Grid m_grid;

	int m_turn;
	int m_spawnTime;

	//print function
	Draw m_draw;


	//returns if printed
	bool PrintPawn(Vec2 pos);
	void PrintItem(Vec2 pos);

	void UpdateAI();
	bool UpdateUser();

	//checks for monsters at location
	//returns monster found or nullptr
	Pawn* MonsterCheck(Vec2 pos) const;
	//returns pointer to pickup if one is at position
	Pickup* GetItem(Vec2 pos) ;

	bool InRange(Vec2 pos) const;
	void EraseMonster(Pawn* monster);
	//spawn a single monster at a random spawn point
	//will not spawn if spawn point is covered
	void SpawnMonster();

public:

	Level(std::vector<std::vector<char>> grid, int spawnTime, User* pUser);

	~Level();

	void SetUser(User* pUser);

	bool Update();
	void Print();

};

