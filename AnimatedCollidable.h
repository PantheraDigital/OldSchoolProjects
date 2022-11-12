#pragma once

#include "Object.h"
#include "Rigidbody.h"
#include "AnimatedObj.h"


class AnimatedCollidable : public Object
{
	AnimatedObj m_anim;
	ColComp* m_col;

	Vec2d<int> m_colOffset;

public:

	AnimatedCollidable(AnimComp animation, ColComp* collision);
	AnimatedCollidable(AnimComp animation);
	~AnimatedCollidable();


	void Update(double delta) override;

	Display GetDisplay() const;

	virtual void Render(SDLWrap& renderer) const override;

	SDL_Rect GetTransform() const;

	void PlaySequence(const char* sequenceName);
	void PlaySequence(int sequenceIndex);

	void SetAnimation(AnimComp animation);

	void Pause(bool pause);

	virtual void SetPos(int x, int y) override;

	virtual void OnCollision(ColComp* pOtherCol) override;

	void SetCollisionType(ColComp* collison);

	bool TryMove(Vec2d<int> deltaPos);

	void SetFlip(SDL_RendererFlip flip);

	void SetCollisionOffset(Vec2d<int> offset);

};

