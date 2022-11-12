#pragma once
#include <SDL.h>
#include "Vec2d.h"

///////////////////
//input handeler for player
/////////////////////
class PlayerController
{
	Vec2d<float> m_direction;
//	SDL_Event m_input;///

	const Uint8* m_pKeystates;

public:

	PlayerController();

//	void Update(SDL_Event& input) { m_input = input; }///

	Vec2d<float> GetDirection();
	bool ShiftDown();
};