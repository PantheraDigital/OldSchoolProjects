#include "ParticleObject.h"

#include "SDLWrap.h"

ParticalObj::ParticalObj(ParticleEmit* particleEmiter, ColComp* collision)
	:m_pCol(collision)
	,m_pParticles(particleEmiter)
{
}

ParticalObj::~ParticalObj()
{
	delete m_pCol;
	delete m_pParticles;
}


void ParticalObj::SetEmiter(ParticleEmit* particleEmiter)
{
	if (!particleEmiter)
		return;

	if (m_pParticles)
	{
		delete m_pParticles;
		m_pParticles = nullptr;
	}
	m_pParticles = particleEmiter;
}

void ParticalObj::SetCollision(ColComp* collision)
{
	if (!collision)
		return;

	if (m_pCol)
	{
		delete m_pCol;
		m_pCol = nullptr;
	}
	m_pCol = collision;
}

Display ParticalObj::GetDisplay() const
{
	return Display();
}

void ParticalObj::Render(SDLWrap& renderer) const
{
	renderer.AddToDisplay(m_pParticles->GetParticals());
}

void ParticalObj::Update(double delta)
{
	m_pParticles->Update(delta);
}

void ParticalObj::SetPos(int x, int y)
{
	m_pCol->SetPos(Vec2d<int>(x, y));
	Vec2d<int> centerPos;
	centerPos.m_x = m_pCol->GetTransform().x + (m_pCol->GetTransform().w / 2);
	centerPos.m_y = m_pCol->GetTransform().y + (m_pCol->GetTransform().h / 2);

	m_pParticles->SetCenter(centerPos);
}

void ParticalObj::OnCollision(ColComp* pOtherCol)
{
	m_pCol->Overlap(pOtherCol);
}
