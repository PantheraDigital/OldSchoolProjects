#include "AiMovement.h"

Vec2d* GoToTarget(Vec2d start, Vec2d target);
Vec2d* Stay(Vec2d start, Vec2d target);

AiMovement::AiMovement()
{
	//two forms of movment
	m_funcs[0] = Stay;
	m_funcs[1] = GoToTarget;

	MoveToTarget = m_funcs[0];
}

AiMovement::~AiMovement()
{
}

///////////////////////////////////
//set stated with int value of State enum
////////////////////////////////////////////
void AiMovement::SetState(State state)
{
	if(m_funcs[(int)(state)])
		MoveToTarget = m_funcs[(int)(state)];
}



/////////////////////////////////////////
//finds if x or y has a longer distance then moves to shorten gap
//////////////////////////////////////////
Vec2d* GoToTarget(Vec2d start, Vec2d target)
{
	int diffx = start.m_x - target.m_x;
	int diffy = start.m_y - target.m_y;
	
	if (diffx < 0)//prevents negative
		diffx *= -1;

	if (diffy < 0)
		diffy *= -1;


	Vec2d* move;

	if (diffx > diffy)
	{
		if (start.m_x > target.m_x)
			move = new Vec2d(-1, 0);
		else
			move = new Vec2d(1, 0);
	}
	else
	{
		if (start.m_y > target.m_y)
			move = new Vec2d(0, -1);
		else
			move = new Vec2d(0, 1);
	}

	return move;
}

///////////////////////////////////////
//dont move so add nothing
///////////////////////////////////
Vec2d* Stay(Vec2d start, Vec2d target)
{
	return new Vec2d(0, 0);
}
