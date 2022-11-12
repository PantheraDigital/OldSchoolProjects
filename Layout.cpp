#include "Layout.h"

#include "ImageLoader.h"
#include "AnimatedObj.h"

#include "SDLWrap.h"


Layout::Layout()
	:m_kTileSize(16)
	, m_kMaxLayer(10)
{

}


Layout::Layout(ColManager* collisionManager)
	:m_kTileSize(16)
	,m_kMaxLayer(10)
{
}

Layout::~Layout()
{
	for (int i = 0; i < m_displayList.size(); ++i)
	{
		for (int j = 0; j < m_displayList[i].size(); ++j)
		{
			delete m_displayList[i][j];
		}
	}
}


short Layout::GetLayerIndex(short layer)
{
	if (layer + 1 > m_kMaxLayer)
		layer = m_kMaxLayer;

	if (layer + 1 > (int)m_displayList.size())
	{
		for (int i = 0; i <= ((layer + 1) - (int)m_displayList.size()); ++i)
		{
			std::vector<Object*> row;
			m_displayList.push_back(row);
		}
	}

	return layer;
}


void Layout::AddTile(Object* disp, int posX, int posY, int layer)
{
	disp->SetPos((m_kTileSize * posX + 1), (m_kTileSize * posY + 1));
	
	layer = GetLayerIndex(layer);
	m_displayList[layer].push_back(disp);
}

void Layout::Render(SDLWrap& renderer) const
{
	for (unsigned int i = 0; i < m_displayList.size(); ++i)
	{
		for (unsigned int j = 0; j < m_displayList[i].size(); ++j)
		{
			renderer.AddToDisplay(m_displayList[i][j]->GetDisplay(), i);
		}
	}
}

void Layout::Update(double delta)
{
	for (int i = 0; i < m_displayList.size(); ++i)
	{
		for (int j = 0; j < m_displayList[i].size(); ++j)
		{
			m_displayList[i][j]->Update(delta);
		}
	}
}




/*
save format

tile number : constructor info ; display layer /

00:1,2;0/2,2;1/3,2;1/
01:4,4;5,4;



*/