#include "TileFactory.h"

/////////////////////////////////////////
//uses char to return wanted Tile
///////////////////////////////////////////
Tile* TileFactory::MakeTile(char type)
{
	if (type == 'W')
		return new Tile(Tile::State::k_wall);
	else if (type == ' ')
		return new Tile(Tile::State::k_background);
	else if (type == 'X')
		return new Tile(Tile::State::k_deadly);
	else if (type == 'D')
		return new Tile(Tile::State::k_door);
	else if (type == 'E')
		return new Tile(Tile::State::k_end);
	else
		return new Tile(type);

}


