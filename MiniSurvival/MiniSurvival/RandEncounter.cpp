#include "RandEncounter.h"



RandEncounter::RandEncounter()
{
	m_encounter.push_back(Encounters("You are ambushed on your way to look for food.", 20, 0, 2));
	m_encounter.push_back(Encounters("Along the broken road you walk down you find a stash of goods.", 0, 4, 1));
	m_encounter.push_back(Encounters("A wild pack off dogs chase you.", 10, 0, 3));
	m_encounter.push_back(Encounters("You came accross a pack of food in a market that is falling appart. You quickly see that the food was booby trapped", 15, 2, 1));
}


RandEncounter::~RandEncounter()
{
}


bool RandEncounter::RandEncountCheck()
{
	int chance = (rand() % 100) + 1;
	//30% chance?
	if (chance <= 30)
		return true;
	else
		return false;
}