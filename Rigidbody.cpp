#include "Rigidbody.h"

#include "ColManager.h"
#include <iostream>

Rigidbody::Rigidbody(Object* owner, SDL_Rect transform, ColManager* manager, const char* name)
	:ColComp(owner, transform, manager, name)
{
	manager->AddCol(this);
}

Rigidbody::~Rigidbody()
{
}

bool Rigidbody::TryMove(Vec2d<int> deltaPos)
{
	if (m_pManager == nullptr)
	{
		//error
		return false;
	}

	//need to update to handle multiple colisions
	// just reports one and will allow passing through objects if using only col direction

	CollisonInfo colInfo = m_pManager->CheckColAndNotify(this, deltaPos);

	if (colInfo.m_didColide)
	{
		if (!colInfo.m_solid)
		{
			
			m_transform.x = deltaPos.m_x;
			m_transform.y = deltaPos.m_y;
			
			return true;
		}
		
	//	std::cout << "X: " << colInfo.m_colDir.m_x << " Y: " << colInfo.m_colDir.m_y << "||";

		return false;
	} 

	m_transform.x = deltaPos.m_x;
	m_transform.y = deltaPos.m_y;

	return true;
}
