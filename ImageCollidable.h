#pragma once

#include "Object.h"
#include "ColComp.h"
#include "ImageObj.h"


class ImageCollidable : public Object
{
	ImageObj m_image;
	ColComp* m_col;

public:

	ImageCollidable(Display display, ColComp* collision);
	ImageCollidable(Display display);
	~ImageCollidable();

	virtual Display GetDisplay() const;

	virtual void Render(SDLWrap& renderer) const override;

	void SetDisplay(Display newDisplay);

	virtual void SetPos(int x, int y) override;

	virtual void OnCollision(ColComp* pOtherCol) override;

	void SetCollisionType(ColComp* collison);

	bool TryMove(Vec2d<int> deltaPos);

	void SetFlip(SDL_RendererFlip flip);

};