#include "Pawn.h"



Pawn::Pawn(char face, Vec2d* position)
	:m_face(face)
	,m_position(position)
{
}


Pawn::~Pawn()
{
	delete m_position;
}






///////////////////////////////////////
//returns desired direction to move
// x and y are 0-1
//////////////////////////////////////////
Vec2d* PlayerPawn::PredictMove()
{
	Vec2d* temp = new Vec2d(0, 0);

	char input = _getch();

	if (input == 'w')
	{
		--temp->m_y;
	}
	else if (input == 'a')
	{
		--temp->m_x;
	}
	else if (input == 's')
	{
		++temp->m_y;
	}
	else if (input == 'd')
	{
		++temp->m_x;
	}

	return temp;
}





/////////////////////////////////
//changes state based on distences from points
//returns movment
////////////////////////////////
Vec2d* Ai::PredictMove()
{

	if (m_target.m_x <= m_sightRange || m_target.m_y <= m_sightRange)//in sight
	{
		m_input.SetState(AiMovement::State::kTarget);
	}
	else
		m_input.SetState(AiMovement::State::kStay);

	if (ToFar())//range from spawn
	{
		m_target = *m_startPoint;//override target 
		m_input.SetState(AiMovement::State::kTarget);
	}

	return (m_input.MoveToTarget(*(GetPosition()), m_target));
}


///////////////////////////////////
//set target
///////////////////////////////
void Ai::SetTarget(Vec2d target)
{
	m_target = target;
}

/////////////////////////////////////
//true ai is further than move range from start point
///////////////////////////////////
bool Ai::ToFar()
{
	int diffx = GetPosition()->m_x - m_startPoint->m_x;
	int diffy = GetPosition()->m_y - m_startPoint->m_y;

	if (diffx < 0)
		diffx *= -1;

	if (diffy < 0)
		diffy *= -1;

	if (diffx > m_MoveRange || diffy > m_MoveRange)
		return true;

	return false;

}

////////////////////////////////////
//delete old spawn and replace it with given point
//////////////////////////////////////
void Ai::SetStartPoint(Vec2d* position)
{ 
	delete m_startPoint;
	m_startPoint = position; 
}

/////////////////////////////////////
//set current position to spawn point
///////////////////////////////
void Ai::SetPosToStart()
{
	SetPosition( *(GetStartPoint()) );
}