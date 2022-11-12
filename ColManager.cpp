#include "ColManager.h"
#include "SDL.h"
#include "ColComp.h"

#include "Object.h"
#include "Display.h"

#include <iostream>

ColManager::ColManager()
{}
ColManager::~ColManager()
{}


void ColManager::AddCol(ColComp* pCol)
{
	if(pCol)
	{ 
		//make sure obj is not in already/pushback can make a copy use emplaceback
		if (std::find(m_activeCol.begin(), m_activeCol.end(), pCol) == m_activeCol.end())
			m_activeCol.emplace_back(pCol);
	}
}

void ColManager::RemoveCol(ColComp* pCol)
{
	if (pCol)
	{
		auto loc = std::find(m_activeCol.begin(), m_activeCol.end(), pCol);
		if (loc != m_activeCol.end())
		{
			m_activeCol.erase(loc, loc);
		}
	}
}

CollisonInfo ColManager::CheckColAndNotify(ColComp* pCol, Vec2d<int> newPos)
{
	CollisonInfo result;

	SDL_Rect colTransform = pCol->GetTransform();

	int left = newPos.m_x;
	int right = newPos.m_x + colTransform.w;

	int top = newPos.m_y;
	int bottom = newPos.m_y + colTransform.h;

	for (ColComp* pOtherCol : m_activeCol)
	{
		//dont check against self
		if (pCol == pOtherCol || pCol->GetColChannels() == Collision::Channels::kNone)
		{
			continue;
		}

		if (pCol->GetColChannels() & pOtherCol->GetColChannels())
		{ 
		
			SDL_Rect otherTransform = pOtherCol->GetTransform();

			int Oleft = otherTransform.x;
			int Oright = otherTransform.x + otherTransform.w;

			int Otop = otherTransform.y;
			int Obottom = otherTransform.y + otherTransform.h;

			bool xOverLap = left < Oright && right > Oleft;
			bool yOverlap = top < Obottom && bottom > Otop;

			if (xOverLap && yOverlap)
			{
				result.m_didColide = true;
				result.m_solid = pOtherCol->GetSolid();


				Vec2d<float> center((float)(left + (colTransform.w / 2)), (float)(bottom + (colTransform.h / 2)));
				Vec2d<float> otherCenter((float)(Oleft + (otherTransform.w / 2)), (float)(Otop + (otherTransform.h / 2)));

				Vec2d<float> vec = otherCenter - center;

				result.m_colDir.m_x = static_cast<float>(floor((vec.m_x / vec.GetMagnitude()) * 10.0 + 0.5) / 10.0);
				result.m_colDir.m_y = static_cast<float>(floor((vec.m_y / vec.GetMagnitude()) * 10.0 + 0.5) / 10.0);


				pCol->GetOwner()->OnCollision(pOtherCol);
				pOtherCol->GetOwner()->OnCollision(pCol);
			}
		}
	}


	return result;
}

std::vector<Display> ColManager::GetCollisions()
{
	std::vector<Display> result;

	for (ColComp* pCol : m_activeCol)
	{
		if (pCol->GetSolid())
			result.push_back(Display(pCol->GetTransform(), SDL_Color{ 255,0,0,50 }));
		else
			result.push_back(Display(pCol->GetTransform(), SDL_Color{ 0,0,255,50 }));
	}

	return result;
}