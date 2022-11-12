#pragma once
#include <SDL.h>

#include "Vec2d.h"
#include "Controllers.h"
#include "AnimatedCollidable.h"
#include "ParticalEmit.h"


///////////////////////////////////////////
//controlled by user input
////////////////////////////////////////
class Pawn : public Object
{
	AnimatedCollidable* m_pawn;
	ParticleEmit* m_particles;

	PlayerController m_controller;
	
	Vec2d<float> m_vel;

	Vec2d<int> m_spawn;

	float m_speedMod;
	const float m_runSpeed;//fastest pawn cam move

	bool m_hasMoved;//if pos can be updated/ internally updated

	bool m_dead;


	float GetSpeed();
	void UpdateAnim(Vec2d<float> vel);//change animation based on velocity
	bool TryMove(double delta);

public:

	Pawn(ColManager* colManager);
	~Pawn();


	void SetController(PlayerController controller) { m_controller = controller; }
	
	//does nothing
	void OnCollision(ColComp* pOtherCol) override {};

	//will update player pos
	void Update(double delta) override;

	//update all getDisplay functions so they give themselves to SDLwrap
	void Render(SDLWrap& renderer) const override;

	void SetPos(Vec2d<int> pos);
	void SetPos(int x, int y) override;

	void Kill();
	void Spawn();

	void SetSpawn(Vec2d<int> newSpawn) { m_spawn = newSpawn; }

	Display GetDisplay() const override;

	void SetSpeedMod(float speedMod) { m_speedMod = speedMod; }
};
