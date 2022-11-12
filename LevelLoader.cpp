#include "LevelLoader.h"

#include "ImageObj.h"
#include "ImageCollidable.h"
#include "AnimatedObj.h"
#include "ParticleObject.h"

#include "ImageLoader.h"

#include "Rigidbody.h"

#include "TileLoader.h"
#include "TriggerFunctions.h"
#include "ParticalEmit.h"

//this is not done well just fast

void LevelLoader::Load(Layout& layout, unsigned int level, ColManager* collisionManager, Pawn* player)
{
	ImageLoader* imLoader = ImageLoader::GetInst();
	TileLoader tileLoad;

	ImageObj* Image;
	AnimatedObj* AnimObj;


	Image = new ImageObj(Display(imLoader->GetImage("CloudsBack"), false));
	layout.AddTile(Image, 0, 0, 0);
	Image = new ImageObj(Display(imLoader->GetImage("CloudsFront"), false));
	layout.AddTile(Image, 0, 0, 0);
	Image = new ImageObj(Display(imLoader->GetImage("BGBack"), false));
	layout.AddTile(Image, 0, 0, 0);
	Image = new ImageObj(Display(imLoader->GetImage("BGFront"), false));
	layout.AddTile(Image, 0, 0, 0);
	
	//screen x 39, y 29

	for (int i = 0; i < 30; ++i)
	{
		for (int k = 0; k < 40; ++k)
		{
			if (i == 0)
			{
				layout.AddTile(tileLoad.LoadTile(20, collisionManager), k, i, 1);
			}
			else if (i == 28)
			{
				if (k == 0)
					layout.AddTile(tileLoad.LoadTile(12, collisionManager), k, i, 1);
				else if (k == 39)
					layout.AddTile(tileLoad.LoadTile(10, collisionManager), k, i, 1);
				else
					layout.AddTile(tileLoad.LoadTile(42, collisionManager, KillPlayer(player)), k, i, 1);
			}
			else if (i == 29)
			{
				layout.AddTile(tileLoad.LoadTile(1, collisionManager), k, i, 1);
			}
			else if (k == 0)
				layout.AddTile(tileLoad.LoadTile(12, collisionManager), k, i, 1);
			else if (k == 39)
				layout.AddTile(tileLoad.LoadTile(10, collisionManager), k, i, 1);

		}

	}

	ParticalObj* pickup = new ParticalObj(nullptr, nullptr);

	ParticleEmit::ParticleInfo parInfo;
	parInfo.m_color = SDL_Color{ 255,140,0,255 };
	parInfo.m_numParticles = 20;
	parInfo.m_rad = 30;
	parInfo.m_speed = 10;
	
	/*
	Trigger* pickupTrigger = new Trigger(pickup, SDL_Rect{ 64,64,64,64 }, collisionManager, "pickup", PlayerSpeedBoost(player));
	
	ParticleEmit* pickupDisp = new ParticleEmit(parInfo, ParticleEmit::UpdateType::kPulse, pickup, true);
	pickup->SetCollision(pickupTrigger);
	pickup->SetEmiter(pickupDisp);

	layout.AddTile(pickup, 20, 20, 2);*/

	pickup = nullptr;
//	pickupTrigger = nullptr;
//	pickupDisp = nullptr;

	imLoader = nullptr;
	Image = nullptr;
	AnimObj = nullptr;

}