#pragma once

#include "Vec2D.h"
#include "LevelList.h"
#include "TileFactory.h"
#include <vector>

class Level
{
	std::vector<Tile*> m_board;
	std::vector<Vec2D> m_keyList;//key locations
	void SetBoard(LevelLayout layout);//used to initalize m_board based on LevelLayout

public:
	Level(LevelLayout layout);
	~Level();

	std::vector<Vec2D> GetKeyLocals() { return m_keyList; }
	void SetKeyLocation(int element, Vec2D vec);

	char GetFace(int x, int y) { return m_board[x + (g_kLevelX*y)]->GetFace(); }
	bool GetBlockPlayer(int x, int y) { return m_board[x + (g_kLevelX*y)]->GetBlockPlayer(); }

	Tile* GetTile(int x, int y) { return m_board[x + (g_kLevelX*y)]; }
	Tile* GetTile(Vec2D coord) { return m_board[coord.m_x + (g_kLevelX*coord.m_y)]; }

	bool CheckForKey(Vec2D coord);

};



