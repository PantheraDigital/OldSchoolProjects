#pragma once
#include "Object.h"
#include "ParticalEmit.h"
#include "Trigger.h"


class ParticalObj : public Object
{
	ParticleEmit* m_pParticles;
	ColComp* m_pCol;

public:

	ParticalObj(ParticleEmit* particleEmiter, ColComp* collision);
	~ParticalObj();

	void SetEmiter(ParticleEmit* particleEmiter);
	void SetCollision(ColComp* collision);

	virtual Display GetDisplay() const override;

	virtual void Render(SDLWrap& renderer) const override;

	virtual void Update(double delta) override;

	virtual void SetPos(int x, int y) override;

	virtual void OnCollision(ColComp* pOtherCol) override;
};