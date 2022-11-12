#include "ColComp.h"


ColComp::ColComp(Object* owner, SDL_Rect transform, ColManager* manager, const char* name)
	:m_pOwner(owner)
	,m_transform(transform)
	,m_pManager(manager)
	,m_name(name)
	,m_colChannels(0x00)
{
}

ColComp::ColComp()
	:m_pOwner(nullptr)
	, m_transform({ 0,0,0,0 })
	, m_pManager(nullptr)
	, m_name("uninitiatedCollisionComp")
	, m_colChannels(0x00)
{
}


void ColComp::SetSize(int w, int h)
{
	m_transform.h = h;
	m_transform.w = w;
}

void ColComp::SetPos(Vec2d<int> pos)
{
	m_transform.x = pos.m_x;
	m_transform.y = pos.m_y;
}

