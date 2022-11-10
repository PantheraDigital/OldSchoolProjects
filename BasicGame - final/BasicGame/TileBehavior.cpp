#include "TileBehavior.h"

/////////////////////////
//if target is user and has enough keys disp and wall are changed to floor and false
///////////////////////////////////
void DoorTile::Activate(Pawn* target)
{
	User* user = dynamic_cast<User*>(target);

	if (user)
	{
		if (user->TakeKeys(m_locks))
		{
			m_disp = g_kFloor;
			m_wall = false;
		}
	}
}