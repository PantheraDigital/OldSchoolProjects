#pragma once
#include "ItemFactory.h"
#include "Item.h"
#include "DayEvents.h"
#include "Player.h"
#include "RandEncounter.h"



class Days
{
	RandEncounter Encount;
	ItemFactory ItemFac;
	DayEvents Event;
	Player User;

	int RandNum(int min, int max)
	{
		return (rand() % max) + min;
	}

	void FakeClrScrn();
	bool RandEncount();

	void Reward(int max);

	void Plan();
	void Explore();
	void End();

	std::string RrndAct();

public:
	Days();
	~Days();

	bool Intro();
	bool PlayerHome();

};

