#include "Pawn.h"

#include <iostream>

#include "SDLWrap.h"
#include "Rigidbody.h"
#include "AnimationLoader.h"


Pawn::Pawn(ColManager* colManager)
	: m_vel()
	, m_spawn(Vec2d<int>(3,3))
	, m_runSpeed(100.0f)
	, m_speedMod(1.0f)
	, m_hasMoved(false)
	, m_dead(false)
{
	AnimationLoader animLoad;
	std::optional<AnimComp> anim = animLoad.Load("adventurer  ");////need to rework constructors of anim and col so they are not dependent like this

	if (anim.has_value())
	{
		SDL_Rect colTrans = anim.value().GetDisp().GetTransform();
		colTrans.h = colTrans.h - 5;
		colTrans.w = colTrans.w - 14;

		Rigidbody* col = new Rigidbody(this, colTrans, colManager, "player");
		col->SetChannels(Collision::Channels::kAll);

		m_pawn = new AnimatedCollidable(anim.value(), col);
		m_pawn->SetCollisionOffset(Vec2d<int>(7, 5));
	}
	else
	{
		std::cout << "faild to set player anim" << std::endl;
		delete m_pawn;
		delete m_particles;
		return;
	}

	ParticleEmit::ParticleInfo parInfo;
	parInfo.m_center.m_x = m_pawn->GetTransform().x;
	parInfo.m_center.m_y = m_pawn->GetTransform().y;
	parInfo.m_color = SDL_Color{ 255,140,0,255 };
	parInfo.m_numParticles = 20;
	parInfo.m_rad = 30;
	parInfo.m_speed = 10;

	m_particles = new ParticleEmit(parInfo, ParticleEmit::UpdateType::kConstant, this, true);
	
}

Pawn::~Pawn()
{
	delete m_pawn;
	delete m_particles;
}


void Pawn::Update(double delta)
{
	if (!m_dead)
	{
		//handle movement and set pos
		if (TryMove(delta))
		{
			m_hasMoved = true;
		}
	}
	else
	{
		m_pawn->PlaySequence("die");

//		if (m_controller.ShiftDown())
//		{
//			Spawn();
//		}

	}

	m_particles->Update(delta);
	UpdateAnim(m_vel);
	m_pawn->Update(delta);
}

void Pawn::Render(SDLWrap& renderer) const
{
	renderer.AddToDisplay(GetDisplay());
	renderer.AddToDisplay(m_particles->GetParticals(), 1);
}

Display Pawn::GetDisplay() const
{
	return m_pawn->GetDisplay();
}

void Pawn::SetPos(Vec2d<int> pos)
{
	SetPos(pos.m_x, pos.m_y);
}
void Pawn::SetPos(int x, int y)
{
	m_hasMoved = true;
	m_pawn->SetPos(x, y);
}

float Pawn::GetSpeed()
{
	if (m_controller.ShiftDown())
	{
		m_speedMod = 2.5f;
	}
	else
	{
		m_speedMod = 1.0f;
	}


	return m_runSpeed * m_speedMod;
}

//////////////////////////
//gets a vector from m_controller() to determin future movement
//normalized vector is used with maxSpeed to determin direction then multiplied by delta to find actual location
////////////////////////////////
bool Pawn::TryMove(double delta)
{
	//track location with precision
	static Vec2d<float> temp = Vec2d<float>(static_cast<float>(m_pawn->GetTransform().x) ,static_cast<float>(m_pawn->GetTransform().y));

	Vec2d<int> result(m_pawn->GetTransform().x, m_pawn->GetTransform().y);
	Vec2d<float> dir = m_controller.GetDirection();

	//if player moved last update, reset 
	if (!m_hasMoved)
	{
		temp = Vec2d<float>(static_cast<float>(m_pawn->GetTransform().x), static_cast<float>(m_pawn->GetTransform().y));
	}

	//update velocity with gravity
/*	Vec2d<float> force;
	force.m_y +=  9.8;
	force.m_x += dir.m_x * GetSpeed();

	force.m_y = force.m_y / 10;
	force.m_x = force.m_x / 10;

	m_vel += force;// *static_cast<float>(delta);
	*/

	m_vel = dir * GetSpeed();

	//update precise location
	temp += m_vel * static_cast<float>(delta);

	//if precise location reaches an int, update result
	if (temp.m_x >= 1.0f || temp.m_x <= -1.0f)
	{
		result.m_x = static_cast<int>(temp.m_x);
	}

	if (temp.m_y >= 1.0f || temp.m_y <= -1.0f)
	{
		result.m_y = static_cast<int>(temp.m_y);
	}


	m_hasMoved = false;
	return m_pawn->TryMove(result);
}

void Pawn::UpdateAnim(Vec2d<float> vel)
{
	if (m_dead)
	{
		m_pawn->PlaySequence("die");
		return;
	}

	bool y = false;
	bool x = false;

	if (vel.m_y > 0 || vel.m_y < 0)
		y = true;

	if (vel.m_x > 0 || vel.m_x < 0)
		x = true;

/*
	"idle", 0, 3);///
	"jump", 14, 17);///
	"flip", 18, 21);///
	"fall", 22, 23);///
	"crouchWalk", 4, 7);///
	"walk", 8, 13);///
	"ledgeHold", 29, 32);///
	"ledgeClimb", 33, 37);///
	"swordOutIdle", 38, 41);///
	"slashUp", 42, 48);///
	"slashDown", 49, 52);///
	"spinSlash", 53, 58);///
	"unknown", 59, 62);///
	"die", 63, 68);///
	"unshieth", 69, 72);///
	"shieth", 73, 76);///
	"wallSlide", 79, 80);///
	"climb", 81, 84);///

	"slide", 24, 27);//
	"dash?", 77, 78);//


	"punch", 85, 92);///
	"punchUp", 93, 95);///
	"dashSlash", 96, 99);///
	"slashUpAir", 99, 102);///
	"downCut", 102, 105);///



	"stillSlash", 106, 108);///


*/

	if (!x && !y)
	{
		//idle
		m_pawn->PlaySequence("idle");
		return;
	}

	m_pawn->Pause(false);
	if (y || (x && y))
	{
		if (vel.m_y >= 1)
			m_pawn->PlaySequence("fall");
			//m_pawn->PlaySequence("walkDown");

		if (vel.m_y <= -1)
			m_pawn->PlaySequence("climb");
			//m_pawn->PlaySequence("walkUp");


	}
	else
	{
		if (vel.m_x <= -1)
		{
			m_pawn->SetFlip(SDL_FLIP_HORIZONTAL);
			//m_pawn->PlaySequence("walkLeft");
			m_pawn->PlaySequence("walk");
		}


		if (vel.m_x >= 1)
		{
			m_pawn->SetFlip(SDL_FLIP_NONE);
			//m_pawn->PlaySequence("walkRight");
			m_pawn->PlaySequence("walk");
		}



		//m_pawn->PlaySequence("walk");
	}
}

void Pawn::Kill()
{
	m_dead = true;
}

void Pawn::Spawn()
{
	m_dead = false;
	SetPos(m_spawn);
}