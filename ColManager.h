#pragma once
#include <vector>

#include "Vec2d.h"

class ColComp;
class Display;

//info sent to colComp that colides with another
struct CollisonInfo
{
	bool m_didColide;
	bool m_solid;
	Vec2d<float> m_colDir;

	CollisonInfo()
		:m_didColide(false)
		,m_solid(false)
	{}
};


class ColManager
{
	std::vector<ColComp*> m_activeCol;

public:
	ColManager();
	~ColManager();

	void AddCol(ColComp* pCol);

	void RemoveCol(ColComp* pCol);

	CollisonInfo CheckColAndNotify(ColComp* pCol, Vec2d<int> newPos);

	std::vector<Display> GetCollisions();
};

