#include "ParticalEmit.h"

#include "RNG.h"


ParticleEmit::ParticleEmit(ParticleEmit::ParticleInfo info, ParticleEmit::UpdateType behavior, Object* owner, bool startOn)
	:m_numParticles(0)
	, m_rad(0)
	, m_pParticles(nullptr)
	, m_updateType(behavior)
	, m_initialized(false)
	, m_pulse(false)
	, m_pOwner(owner)
	, m_on(startOn)
{
	//set base values
	m_center = info.m_center;
	m_rad = info.m_rad;
	m_numParticles = info.m_numParticles;
	m_speed = info.m_speed;

	m_pParticles = new Particle[m_numParticles]();

	//set particals
	for (int i = 0; i < m_numParticles; ++i)
	{
		m_pParticles[i].m_color = info.m_color;
		ResetParticle(m_pParticles[i]);
	}
}


ParticleEmit::~ParticleEmit()
{
	delete[] m_pParticles;
	m_pParticles = nullptr;
}

////////////////////////////////
//updates particle info based on UpdateType
//	pulse uses Timer to toggle partical reset
//	single burst hades particals when out of m_rad
////////////////////////////////////
void ParticleEmit::Update(double delta)
{
	//initialize on first call
	if (!m_initialized)
	{
		m_pulse = false;

		//set timer if pulse
		if (m_updateType == UpdateType::kPulse)
			m_timer.Set(3, Timer::UpdateType::kPulse, [&m_pulse = m_pulse]()mutable {m_pulse = !m_pulse; });
	}
	m_initialized = true;

	m_center.m_x = m_pOwner->GetDisplay().GetTransform().x;
	m_center.m_y = m_pOwner->GetDisplay().GetTransform().y;

	float sqrdRad = m_rad * m_rad;

	m_timer.Update();

	//update particles
	for (int i = 0; i < m_numParticles; ++i)
	{
		if (!m_on)
		{
			HideParticle(m_pParticles[i]);
		}
		else
		{
			Vec2d<float> vel = m_pParticles[i].m_vel;
			vel.m_x *= static_cast<float>(delta * 10.0f);
			vel.m_y *= static_cast<float>(delta * 10.0f);

			m_pParticles[i].m_posOffset += vel;

			//keep partical in radius
			if (m_pParticles[i].m_posOffset.GetSquaredMagnitude() > sqrdRad)
			{
				if (m_updateType == UpdateType::kConstant)
				{
					ResetParticle(m_pParticles[i]);
				}
				else if (m_updateType == UpdateType::kPulse)
				{
					if (m_pulse)
					{
						ResetParticle(m_pParticles[i]);
					}
					else
						HideParticle(m_pParticles[i]);

				}
				else if (m_updateType == UpdateType::kSingleBurst)
				{
					HideParticle(m_pParticles[i]);
				}
			}
		}

	}

	m_pulse = false;
}

////////////////////////
//creates an vector of Displays representing particals
/////////////////////////////
std::vector<Display> ParticleEmit::GetParticals() const
{
	std::vector<Display> list;
	for (int i = 0; i < m_numParticles; ++i)
	{
		Particle& particle = m_pParticles[i];
		Vec2d<float>& pos = particle.m_posOffset;

		SDL_Rect particalTrans;
		particalTrans.x = m_center.m_x + static_cast<int>(pos.m_x);
		particalTrans.y = m_center.m_y + static_cast<int>(pos.m_y);
		particalTrans.w = 5;
		particalTrans.h = 5;
		Display temp(particalTrans, m_pParticles[i].m_color);

		list.push_back(temp);
	}

	return list;
}

/////////////////////////
//randomly set target particle velocity, speed, and alpha
/////////////////////////////
void ParticleEmit::ResetParticle(Particle& target)
{
	RNG rng(-100, 100);
	float velX = static_cast<float>(rng.Generate() / 100);
	float velY = static_cast<float>(rng.Generate() / 100);

	rng.SetRange(static_cast<int>(m_speed * 0.45f), static_cast<int>(m_speed));//range of speeds

	//set velocity
	target.m_vel = (Vec2d<float>(velX, velY).GetNorm()) * static_cast<float>(rng.Generate());

	//set alpha
	rng.SetRange(10, 255);
	target.m_color.a = rng.Generate();

	//set position offset
	target.m_posOffset = {};
}

///////////////////////////////
//set particles out of radius, zero velocity, and zero alpha
////////////////////////////////
void ParticleEmit::HideParticle(Particle& target)
{
	target.m_color.a = 0;
	target.m_vel = {};
	target.m_posOffset = Vec2d<float>(m_rad + 5, m_rad + 5);
}

void ParticleEmit::SetUpdateType(ParticleEmit::UpdateType behavior)
{
	m_updateType = behavior;
}

void ParticleEmit::SetOnOff(bool on)
{
	m_on = on;
}