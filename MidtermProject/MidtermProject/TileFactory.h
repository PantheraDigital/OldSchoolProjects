#pragma once
#include "Tile.h"

class TileFactory//fac
{


public:
	TileFactory()
	{}


	Tile* MakeTile(char type);

};



