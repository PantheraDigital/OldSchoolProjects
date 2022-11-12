#pragma once
#include <functional>

#include "ColComp.h"


class Trigger : public ColComp
{
	std::function<void(ColComp*)> m_pCallback;

public:
	Trigger(Object* owner, SDL_Rect transform, ColManager* manager, const char* name, std::function<void(ColComp*)> callback);
	Trigger();
	~Trigger();


	virtual bool TryMove(Vec2d<int> deltaPos) override;

	virtual bool GetSolid() const override;

	virtual void Overlap(ColComp* otherCollision) override;

	void SetCallback(std::function<void(ColComp*)> callback) { m_pCallback = callback; }

};
