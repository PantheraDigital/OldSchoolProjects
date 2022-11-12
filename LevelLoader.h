#pragma once

#include "Layout.h"
#include "Pawn.h"

class LevelLoader
{
	//expand so that this loads from file

public:

	static void Load(Layout& layout, unsigned int level, ColManager* collisionManager, Pawn* player);
};

