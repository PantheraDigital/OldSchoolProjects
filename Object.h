#pragma once
#include "SDL.h"

class Display;
class ColComp;
class SDLWrap;


class Object
{

public:
	virtual ~Object() {};

	virtual Display GetDisplay() const = 0;

	virtual void Render(SDLWrap& renderer) const = 0;

	virtual void Update(double delta) {}

	virtual void SetPos(int x, int y) {}

	virtual void OnCollision(ColComp* pOtherCol) {}

	virtual void HandleEvent(SDL_Event* pEvent) {}

};

