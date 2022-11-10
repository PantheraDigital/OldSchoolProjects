#pragma once
#include <vector>

#include "Tile.h"
#include "Pawn.h"

//controlls all tiles in game
class Grid
{
	std::vector<std::vector<std::shared_ptr<Tile>>> m_grid;

public:
	Grid(int x, int y);
	Grid(std::vector<std::vector<char>> grid);//used for loading created levels
	~Grid();

	//return the display of the tile at location
	char GetDisplay(int x, int y) const;
	//find if tile at location is a wall
	bool IsWall(int x, int y) const;

	//gets the total size of grid using the number of elements 
	int GetSize() const;

	int GetHeight() const { return (int)m_grid.size(); }
	int GetWidth(int row) const { return (int)m_grid[row].size(); }

	void ActivateTile(int x, int y, Pawn* target);
	void Update();
};

