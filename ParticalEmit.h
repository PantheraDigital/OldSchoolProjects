#pragma once
#include "Vec2d.h"
#include "Display.h"
#include "Timer.h"
#include "Object.h"

#include <SDL.h>
#include <vector>

////////////////////////
//manages a group of particles
//////////////////
class ParticleEmit
{
public:
	//update behavior
	enum class UpdateType
	{
		kSingleBurst
		,kConstant
		,kPulse
	};

	struct Particle
	{
		Vec2d<float> m_posOffset;
		Vec2d<float> m_vel;
		SDL_Color m_color;
	};

	//constructo info for particles
	struct ParticleInfo
	{
		int m_numParticles;
		float m_rad;
		Vec2d<int> m_center;
		float m_speed;
		SDL_Color m_color;
	};

private:
	Object* m_pOwner;

	//used in update func
	Timer m_timer;
	bool m_initialized;
	bool m_pulse;
	//

	bool m_on;

	int m_numParticles;
	float m_rad;
	Particle* m_pParticles;
	Vec2d<int> m_center;
	float m_speed;
	UpdateType m_updateType;


	void ResetParticle(Particle& target);
	void HideParticle(Particle& target);

public:
	ParticleEmit(ParticleEmit::ParticleInfo info, ParticleEmit::UpdateType behavior, Object* owner, bool startOn);
	~ParticleEmit();


	void Update(double delta);

	std::vector<Display> GetParticals() const;

	void SetUpdateType(ParticleEmit::UpdateType behavior);
	void SetOnOff(bool on);
	void SetCenter(Vec2d<int> pos) { m_center = pos; }
};

