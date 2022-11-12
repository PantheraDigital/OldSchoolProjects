#pragma once
#include <vector>

#include "Object.h"
#include "ColManager.h"

class SDLWrap;


///////////////////
//store and update objects in level 
////////////////////////
class Layout
{
	std::vector <std::vector<Object*>> m_displayList;

	const int m_kTileSize;
	const short m_kMaxLayer;


	short GetLayerIndex(short layer);

public:

	Layout(ColManager* collisionManager);
	Layout();

	~Layout();

	//position is determind by tile index not pixel pos
	void AddTile(Object* disp, int posX, int posY, int layer);

	void Render(SDLWrap& renderer) const;

	void Update(double delta);
};