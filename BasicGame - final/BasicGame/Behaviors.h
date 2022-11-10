#pragma once
#include <conio.h>

#include "Vec2.h"
//PawnBehavior declaired in Pawn.h

class UserMove : public PawnBehavior
{

public:
	UserMove()
		:PawnBehavior(g_kPlayer)
	{}

	Vec2 Input() override
	{
		char input = _getch();
		Vec2 result(0, 0);

		switch (input)
		{

		case 'w':
		{
			result = Vec2(0, -1);
			break;
		}

		case 'a':
		{
			result = Vec2(-1, 0);
			break;
		}

		case 's':
		{
			result = Vec2(0, 1);
			break;
		}

		case 'd':
		{
			result = Vec2(1, 0);
			break;
		}

		default:
			break;

		}

		return result;
	}

};

class RandomMove : public PawnBehavior
{

public:
	RandomMove()
		:PawnBehavior(g_kWonderAi)
	{}

	Vec2 Input() override
	{
		Vec2 result(0, 0);

		int input = rand() % 5;//0-3 move  4 stationary

		switch (input)
		{

		case 0:
		{
			result = Vec2(0, -1);
			break;
		}

		case 1:
		{
			result = Vec2(-1, 0);
			break;
		}

		case 2:
		{
			result = Vec2(0, 1);
			break;
		}

		case 3:
		{
			result = Vec2(1, 0);
			break;
		}

		default:
			break;

		}

		return result;
	}

};

class CircleMove : public PawnBehavior
{
private:
	int m_stage;

public:
	CircleMove()
		:PawnBehavior(g_kCircleAi)
		, m_stage(0)
	{}

	Vec2 Input() override
	{

		if (m_stage == 4)
			m_stage = 0;

		Vec2 result(0, 0);

		switch (m_stage)
		{

		case 0:
		{
			result = Vec2(0, -1);
			break;
		}

		case 1:
		{
			result = Vec2(-1, 0);
			break;
		}

		case 2:
		{
			result = Vec2(0, 1);
			break;
		}

		case 3:
		{
			result = Vec2(1, 0);
			break;
		}

		default:
			break;

		}

		++m_stage;
		return result;
	}

};

class ChaseMove : public PawnBehavior
{
private:
	Pawn const* m_pOwner;
	Pawn const* m_pTarget;

public:
	ChaseMove(Pawn* pOwner, Pawn* pTarget)
		:PawnBehavior(g_kChaseAi)
		, m_pOwner(pOwner)
		, m_pTarget(pTarget)
	{}

	Vec2 Input() override
	{
		if (m_pTarget->GetLocation() < m_pOwner->GetLocation())//above and/or left
		{
			Vec2 test = Vec2((int)(m_pOwner->GetLocation().m_x - m_pTarget->GetLocation().m_x), (int)(m_pOwner->GetLocation().m_y - m_pTarget->GetLocation().m_y));

			if (test.m_x < test.m_y)
			{
				return Vec2(0, -1);
			}
			else
			{
				return Vec2(-1, 0);
			}
		}
		else//below and/or right
		{
			Vec2 test = Vec2((int)(m_pTarget->GetLocation().m_x - m_pOwner->GetLocation().m_x), (int)(m_pTarget->GetLocation().m_y - m_pOwner->GetLocation().m_y));

			if (test.m_x < test.m_y)
			{
				return Vec2(0, 1);
			}
			else
			{
				return Vec2(1, 0);
			}
		}
	}

};
