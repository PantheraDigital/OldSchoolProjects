#include "AnimatedCollidable.h"

#include "SDLWrap.h"


AnimatedCollidable::AnimatedCollidable(AnimComp animation, ColComp* collision)
	:m_anim(animation)
	,m_col(collision)
{}

AnimatedCollidable::AnimatedCollidable(AnimComp animation)
	:m_anim(animation)
	,m_col(new Rigidbody(this, m_anim.GetDisplay().GetTransform(), nullptr, "animCol"))
{}

AnimatedCollidable::~AnimatedCollidable()
{
	delete m_col;
}


Display AnimatedCollidable::GetDisplay() const
{
	return m_anim.GetDisplay();
}

void AnimatedCollidable::Render(SDLWrap& renderer) const
{
	renderer.AddToDisplay(GetDisplay());
}

SDL_Rect AnimatedCollidable::GetTransform() const
{
	return m_col->GetTransform();
}

void AnimatedCollidable::Update(double delta)
{
	m_anim.Update(delta);
	m_anim.SetPos(m_col->GetTransform().x - m_colOffset.m_x, m_col->GetTransform().y - m_colOffset.m_y);
}

void AnimatedCollidable::PlaySequence(const char* sequenceName)
{
	m_anim.SetSequence(sequenceName);
}
void AnimatedCollidable::PlaySequence(int sequenceIndex)
{
	m_anim.SetSequence(sequenceIndex);
}

void AnimatedCollidable::SetAnimation(AnimComp animation)
{
	m_anim.SetAnimation(animation);
}

void AnimatedCollidable::Pause(bool pause)
{
	m_anim.Pause(pause);
}

void AnimatedCollidable::SetPos(int x, int y)
{
	m_col->SetPos(Vec2d<int>(x, y));
	m_anim.SetPos(m_col->GetTransform().x - m_colOffset.m_x, m_col->GetTransform().y - m_colOffset.m_y);
}

void AnimatedCollidable::OnCollision(ColComp* pOtherCol)
{
	m_col->Overlap(pOtherCol);
}

void AnimatedCollidable::SetCollisionType(ColComp* collison)
{
	Vec2d<int> pos((m_anim.GetDisplay().GetTransform().x + m_colOffset.m_x), (m_anim.GetDisplay().GetTransform().y + m_colOffset.m_y));
	collison->SetPos(pos);

	if (m_col)
		delete m_col;

	m_col = collison;
}

bool AnimatedCollidable::TryMove(Vec2d<int> deltaPos)
{
	bool result = m_col->TryMove(deltaPos);

	m_anim.SetPos(m_col->GetTransform().x - m_colOffset.m_x, m_col->GetTransform().y - m_colOffset.m_y);

	return result;
}

void AnimatedCollidable::SetFlip(SDL_RendererFlip flip)
{
	m_anim.SetFlip(flip);
}

void AnimatedCollidable::SetCollisionOffset(Vec2d<int> offset)
{
	m_colOffset = offset;

	m_col->SetPos( Vec2d<int>((m_anim.GetDisplay().GetTransform().x + m_colOffset.m_x), (m_anim.GetDisplay().GetTransform().y + m_colOffset.m_y)) );
}