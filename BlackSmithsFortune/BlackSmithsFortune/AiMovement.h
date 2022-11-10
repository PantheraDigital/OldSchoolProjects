#pragma once
#include <array>
#include "Vec2d.h"

typedef Vec2d* (*Move)(Vec2d,Vec2d);//func pointer for movement

class AiMovement
{
	std::array<Move, 2> m_funcs;
public:

	enum State
	{
		kStay
		,kTarget
	};

	AiMovement();
	~AiMovement();

	void SetState(State state);

	Move MoveToTarget;
};

