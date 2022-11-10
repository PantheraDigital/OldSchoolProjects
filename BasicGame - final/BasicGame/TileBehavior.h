#pragma once
#include "Pawn.h"
#include "DisplayConsts.h"

class TileBehavior
{
protected:
	char m_disp;
	bool m_wall;

public:
	TileBehavior(char disp, bool isWall)
		:m_disp(disp)
		, m_wall(isWall)
	{}

	char GetDisplay() const { return m_disp; }
	bool IsAWall() const { return m_wall; }
	virtual void Update() {};
	virtual void Activate(Pawn* target) {};
};

class Spikes : public TileBehavior
{
private:
	int m_damage;

public:
	Spikes(int damage)
		:TileBehavior(g_kSpikes, false)
		,m_damage(damage)
	{}

	void Activate(Pawn* target) override { target->TakeDamage(m_damage); }
};

class DoorTile : public TileBehavior
{
private:
	int m_locks;
public:
	DoorTile(int locks)
		:TileBehavior(g_kDoor, true)
		, m_locks(locks)
	{}

	void Activate(Pawn* target) override;
};