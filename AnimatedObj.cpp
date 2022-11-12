#include "AnimatedObj.h"

#include <algorithm>
#include "SDLWrap.h"


AnimatedObj::AnimatedObj(AnimComp Animation)
	:m_anim(Animation)
{
	m_sequences = Animation.GetSequences();
	m_anim.PlayAnim(m_sequences[0]);
}

AnimatedObj::~AnimatedObj()
{
}


Display AnimatedObj::GetDisplay() const
{
	return m_anim.GetDisp();
}

void AnimatedObj::Render(SDLWrap& renderer) const
{
	renderer.AddToDisplay(GetDisplay());
}

void AnimatedObj::Update(double delta)
{
	m_anim.Update(delta);
}

void AnimatedObj::SetPos(int x, int y)
{
	m_anim.SetPos(x, y);
}

void AnimatedObj::SetSequence(const char* sequenceName)
{
	if (std::find(m_sequences.begin(), m_sequences.end(), sequenceName) != m_sequences.end())
		m_anim.PlayAnim(sequenceName);
}
void AnimatedObj::SetSequence(int sequenceIndex)
{
	if (sequenceIndex < m_sequences.size())
		m_anim.PlayAnim(m_sequences[sequenceIndex]);
}

void AnimatedObj::Pause(bool pause)
{
	m_anim.Pause(pause);
}

void AnimatedObj::SetFlip(SDL_RendererFlip flip)
{
	m_anim.SetAnimFlip(flip);
}