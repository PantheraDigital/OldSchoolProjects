#pragma once

#include "Level.h"
#include "Player.h"
#include <iostream>
#include <stdlib.h>

class LevelManager
{
	//singlton
	static LevelManager* m_instance;
	LevelManager();

	Player m_player;

	std::vector<Level*> m_LevelList;
	int m_currentLv;
	
	void DisplayLv(unsigned int level);
	void LevelChange(Vec2D coord);

	bool KeyCheck(Vec2D coord);//true if a key has the same coords
	void TileSwitch();

public:

	static LevelManager* getInstance();
	~LevelManager();

	int Loop();


};

