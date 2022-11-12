#include "ImageCollidable.h"

#include "Trigger.h"
#include "SDLWrap.h"



ImageCollidable::ImageCollidable(Display display, ColComp* collision)
	:m_image(display)
	,m_col(collision)
{
}

ImageCollidable::ImageCollidable(Display display)
	: m_image(display)
	, m_col(new Trigger())
{}

ImageCollidable::~ImageCollidable()
{
	delete m_col;
}


Display ImageCollidable::GetDisplay() const
{
	return m_image.GetDisplay();
}

void ImageCollidable::Render(SDLWrap& renderer) const
{
	renderer.AddToDisplay(GetDisplay());
}

void ImageCollidable::SetDisplay(Display newDisplay)
{ 
	m_image.SetDisplay(newDisplay); 

	Vec2d<int> pos(m_image.GetDisplay().GetTransform().x, m_image.GetDisplay().GetTransform().y);
	m_col->SetPos(pos);
}

void ImageCollidable::SetPos(int x, int y)
{
	m_image.SetPos(x, y);
	m_col->SetPos(Vec2d<int>(x, y));
}

void ImageCollidable::OnCollision(ColComp* pOtherCol)
{
	m_col->Overlap(pOtherCol);
}

void ImageCollidable::SetCollisionType(ColComp* collison)
{
	Vec2d<int> pos(m_image.GetDisplay().GetTransform().x, m_image.GetDisplay().GetTransform().y);
	collison->SetPos(pos);

	if (m_col)
		delete m_col;

	m_col = collison;
}

bool ImageCollidable::TryMove(Vec2d<int> deltaPos)
{
	bool result = m_col->TryMove(deltaPos);

	m_image.SetPos(m_col->GetTransform().x, m_col->GetTransform().y);

	return result;
}

void ImageCollidable::SetFlip(SDL_RendererFlip flip)
{
	m_image.SetFlip(flip);
}