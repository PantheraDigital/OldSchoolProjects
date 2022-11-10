#pragma once
#include <conio.h>

#include "Vec2d.h"
#include "AiMovement.h"


//////////////////////////////////////
//used as base for movable characters in map
/////////////////////////////////////
class Pawn
{
	char m_face;

	Vec2d* m_position;

public:

	Pawn(char face, Vec2d* position);
	~Pawn();



	void SetPosition(Vec2d pos) { *m_position = pos; }
	Vec2d* GetPosition() { return m_position; }

	char GetFace() { return m_face; }
	//adds given move to curent location
	void Move(Vec2d* increment) { *m_position += increment; }
	//check before setting position 
	virtual Vec2d* PredictMove() = 0;

};


//represents player in map screen
class PlayerPawn : public Pawn
{


public:
	PlayerPawn(Vec2d* position) :Pawn('P', position) {}

	Vec2d* PredictMove();
};




//seems to not respond properly to state change or target changes
//does not return to spawn point unless position is set
class Ai : public Pawn
{
	AiMovement m_input;
	Vec2d m_target;//move to
	Vec2d* m_startPoint;//spawn
	int m_MoveRange;//distance from start point
	int m_sightRange;//activation range

	bool ToFar();

public:
	Ai(Vec2d* position) 
		:Pawn('A', position)
		, m_startPoint(new Vec2d(*position))
		, m_target(*position) 
		,m_sightRange(4)
		,m_MoveRange(6)
	{
	}

	Vec2d* PredictMove();

	void SetStartPoint(Vec2d* position);
	void SetPosToStart();
	Vec2d* GetStartPoint() { return m_startPoint; }

	void SetTarget(Vec2d target);

	int GetSightRange() { return m_sightRange; }
	int GetMoveRange() { return m_MoveRange; }
};