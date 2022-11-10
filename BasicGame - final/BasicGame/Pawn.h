#pragma once
#include <iostream>

#include "Vec2.h"
#include "Pickup.h"

//base for pawn behaviors
class PawnBehavior
{
private:
	char m_disp;

public:
	PawnBehavior(char display)
		:m_disp(display)
	{}

	virtual Vec2 Input() = 0;
	char GetDisplay() const { return m_disp; }
};


//basic pawn class
//allows movment based on behavior, health managment, and stores items
class Pawn
{
private:
	Vec2 m_pos;

protected:
	int m_health, m_maxHP;
	Pickup* m_equipedWeapon;
	Pickup* m_equipedArmor;	

	Pawn(Vec2 pos, int health, int maxHP);

	PawnBehavior* m_pBehavior;

public:

	//char determins the ai stats and behavior
	static Pawn* RandAiFactory(Vec2 pos, Pawn* pTarget);
	static Pawn* AiFactory(Vec2 pos, Pawn* pTarget, char type);

	~Pawn();

	void SetPosition(Vec2 pos) { m_pos = pos; }

	// use input ptr to get desired direction
	virtual Vec2 GetNewPos();
	//returns current location
	Vec2 GetLocation() const;

	void TakeDamage(int damage);
	void AddHP(int amount);
	bool LowHealth() const;

	bool IsDead() const;

	virtual char GetDisplay() const { return m_pBehavior->GetDisplay(); }
	int GetAttack() const;

	bool HasArmor() const { return m_equipedArmor; }
};


//responsible for user
//allows picking up items and displaying stats
class User : public Pawn
{
private:
	unsigned int m_keys;

	Pickup* PickUpWeapon(Pickup* item);
	Pickup* PickUpArmor(Pickup* item);

public:

	User(Vec2 pos);
	~User();

	//returns true if pawn has keys 
	//removes keys if true
	bool TakeKeys(unsigned int keys);

	//print stats at location
	void PrintStats(int x, int y);

	//returns old item if one is stored already
	//handles items picked up
	virtual Pickup* PickUpItem(Pickup* item);
};



//ai class that will change movment if target is close
class SwitchAI : public Pawn
{
private:
	Pawn const* m_pTarget;
	bool m_agro;
	int m_viewDist;

	PawnBehavior* m_pDefaultState;

	//check distancd between target and self
	int GetDistance();

public:

	SwitchAI(Pawn* pTarget, Vec2 pos, int health, int maxHP, int viewDist, PawnBehavior* defaultState);
	SwitchAI(Pawn* pTarget, Vec2 pos, int health, int maxHP, int viewDist, PawnBehavior* defaultState, PawnBehavior* agroState);
	~SwitchAI();

	//changes input function if target is close
	Vec2 GetNewPos() override;
	char GetDisplay() const override;
};
