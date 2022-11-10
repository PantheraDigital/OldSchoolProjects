#include "Level.h"


Level::Level(LevelLayout layout)
{
	SetBoard(layout);
}


Level::~Level()
{

}

//////////////////////////////////////////////
//creates Tiles based on LevelLayout and stores them
////////////////////////////////////////////////
void Level::SetBoard(LevelLayout layout)
{
	TileFactory fac;
	for (int y = 0; y < g_kLevelY; ++y)
	{
		for (int x = 0; x < g_kLevelX; ++x)
		{
			if (layout[y][x] != 'K' && layout[y][x] != '/0')//if not key and not null terminator
				m_board.push_back((fac.MakeTile(layout[y][x])));
			else
			{
				Vec2D coord;
				coord.m_x = x;
				coord.m_y = y;

				m_board.push_back((fac.MakeTile(layout[y][x])));
				m_keyList.push_back(coord);
			}

		}
	}

}

/////////////////////////////////////
//check if a key is stored at a location
///////////////////////////////////
bool Level::CheckForKey(Vec2D coord)
{
	for (unsigned int i = 0; i < m_keyList.size(); ++i)
	{
		if (coord == m_keyList[i])
			return true;
	}
	return false;
}


void Level::SetKeyLocation(int element, Vec2D vec)
{
	m_keyList[element].m_x = vec.m_x;
	m_keyList[element].m_y = vec.m_y;
}
