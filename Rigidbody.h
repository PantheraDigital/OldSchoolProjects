#pragma once

#include "ColComp.h"


class Rigidbody : public ColComp
{

public:

	Rigidbody(Object* owner, SDL_Rect transform, ColManager* manager, const char* name);
	~Rigidbody();

	virtual bool GetSolid() const override { return true; }

	virtual bool TryMove(Vec2d<int> deltaPos) override;
};