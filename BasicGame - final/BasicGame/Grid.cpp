#include "Grid.h"

#include <iostream>

#include "DisplayConsts.h"

////////////////////////////
//fill the grid based on size passed in
////////////////////////
Grid::Grid(int x, int y)
{
	for (int i = 0; i < y; ++i)
	{
		std::vector<std::shared_ptr<Tile>> col;
		m_grid.push_back(col);

		for (int j = 0; j < x; ++j)
		{
			m_grid[i].push_back(Tile::TileFac(g_kFloor));
		}
	}
}

Grid::Grid(std::vector<std::vector<char>> grid)
{
	for (unsigned int i = 0; i < grid.size(); ++i)
	{
		std::vector<std::shared_ptr<Tile>> col;
		m_grid.push_back(col);

		for (unsigned int j = 0; j < grid[i].size(); ++j)
		{
			std::shared_ptr<Tile> temp = Tile::TileFac(grid[i][j]);
			if (temp)
				m_grid[i].push_back(temp);
			else//if there is no tile for that char make a floor
				m_grid[i].push_back(Tile::TileFac(g_kFloor));
		}
	}
}


Grid::~Grid()
{
	for (unsigned int i = 0; i < m_grid.size(); ++i)
	{
		for (unsigned int j = 0; j < m_grid[i].size(); ++j)
		{
			m_grid[i][j].reset();
		}
		m_grid[i].clear();
	}
	m_grid.clear();
}


char Grid::GetDisplay(int x, int y) const
{
	if (x < GetWidth(y) && y < GetHeight() - 1)//if tile is in the grid
		if (m_grid[y][x])//if the tile is not a nullptr
			return m_grid[y][x]->GetDisplay();

	return '\n';
}

bool Grid::IsWall(int x, int y) const
{
	if (x < GetWidth(y) && y < GetHeight())//if tile is in the grid
		if (m_grid[y][x])//if the tile is not a nullptr
			return m_grid[y][x]->IsAWall();

	return true;//default to true
}

int Grid::GetSize() const
{
	int size = 0;
	
	if (m_grid.empty())
		return size;

	for (unsigned int i = 0; i < m_grid.size(); ++i)
		size += (int)(m_grid.size() * m_grid[i].size());

	return size;
}

void Grid::ActivateTile(int x, int y, Pawn* target)
{
	m_grid[y][x]->Activate(target);
}

///////////////////////////////////
//update all tiles
////////////////////////////////////////
void Grid::Update()
{
	for (unsigned int i = 0; i < m_grid.size(); ++i)
	{
		for (unsigned int j = 0; j < m_grid[i].size(); ++j)
		{
			m_grid[i][j]->Update();
		}
	}
}