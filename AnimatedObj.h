#pragma once
#include "Object.h"
#include "AnimComp.h"


class AnimatedObj : public Object
{
	AnimComp m_anim;

	std::vector<const char*> m_sequences;

public:
	AnimatedObj(AnimComp Animation);
	~AnimatedObj();


	Display GetDisplay() const;

	void Render(SDLWrap& renderer) const override;

	void Update(double delta) override;

	void SetPos(int x, int y) override;

	void SetSequence(const char* sequenceName);
	void SetSequence(int sequenceIndex);

	void Pause(bool pause);

	void SetAnimation(AnimComp animation) { m_anim = animation; }

	void SetFlip(SDL_RendererFlip flip);
};

