#include "Trigger.h"

#include "ColManager.h"


Trigger::Trigger(Object* owner, SDL_Rect transform, ColManager* manager, const char* name, std::function<void(ColComp*)> callback)
	:ColComp(owner, transform, manager, name)
	,m_pCallback(callback)
{
	manager->AddCol(this);
}

Trigger::Trigger()
	:ColComp()
	, m_pCallback(nullptr)
{}

Trigger::~Trigger()
{}


bool Trigger::TryMove(Vec2d<int> deltaPos)
{
	if (m_pManager == nullptr)
	{
		//error
		return false;
	}

	CollisonInfo colInfo = m_pManager->CheckColAndNotify(this, deltaPos);


	if (colInfo.m_didColide)
	{

	}

	m_transform.x = deltaPos.m_x;
	m_transform.y = deltaPos.m_y;

	return true;
}

bool Trigger::GetSolid() const
{
	return false;
}

void Trigger::Overlap(ColComp* otherCollision)
{ 
	if (m_pCallback && otherCollision)
		m_pCallback(otherCollision);
}