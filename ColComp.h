#pragma once
#include <Windows.h>
#include <winnt.h>

#include "SDL.h"
#include "Vec2d.h"


class Object;
class ColManager;

namespace Collision
{
	enum Channels
	{
		kNone = 0
		,kAll = -1
		,kOne = 0x01
		,kTwo = 0x02
		,kThree = 0x04
		,kFour = 0x08
		,kFive = 0x10
		,kSix = 0x20
		,kSeven = 0x40
		,kEight = 0x80
	};
	DEFINE_ENUM_FLAG_OPERATORS(Channels);
}


class ColComp
{

protected:
	Object* m_pOwner;
	ColManager* m_pManager;

	SDL_Rect m_transform;//hitbox

	const char* m_name;

	unsigned char m_colChannels;//bit flags for colision chanels to check against

public:



	ColComp(Object* owner, SDL_Rect transform, ColManager* manager, const char* name);
	ColComp();
	virtual ~ColComp() {}


	Object* GetOwner() const { return m_pOwner; }

	SDL_Rect GetTransform() const { return m_transform; }

	void SetSize(int w, int h);

	void SetPos(Vec2d<int> pos);

	const char* GetName() const { return m_name; }

	void SetChannels(Collision::Channels collChannels) { m_colChannels = collChannels; }
	unsigned char GetColChannels() const { return m_colChannels; }

	//attempt to move colider by given amount
	//if move causes colissions objs are notified
	//returns if move was successfull with no colissions
	virtual bool TryMove(Vec2d<int> deltaPos) = 0;

	virtual bool GetSolid() const = 0;

	//called while colliding
	virtual void Overlap(ColComp* otherCollision) {}

	
};

