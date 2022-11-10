#include "Tile.h"
//#include "DisplayConsts.h" // in TileBehavior


TileFacFunc Tile::TileFac = TileFacFunc();


TileFacFunc::~TileFacFunc()
{
}

/////////////////////////////////////////
//check for tile
//if it exists, return it, else make one 
/////////////////////////////////////
std::shared_ptr<Tile> TileFacFunc::GetBasicTile(char tile)
{
	if (m_basicTiles.count(tile))
		return m_basicTiles.at(tile);
	else//make tile if one does not exists
	{
		std::shared_ptr<Tile> temp = nullptr;

		if (tile == g_kFloor)
			temp = std::shared_ptr<Tile>(new Tile(g_kFloor, false));

		if (tile == g_kWall)
			temp = std::shared_ptr<Tile>(new Tile(g_kWall, true));

		if (tile == g_kEmptyTile)
			temp = std::shared_ptr<Tile>(new Tile(g_kEmptyTile, true));

		if (tile == g_kEnd)
			temp = std::shared_ptr<Tile>(new Tile(g_kEnd, false));

		m_basicTiles.emplace(std::pair<char, std::shared_ptr<Tile>>(tile, temp));
		return temp;
	}
}

///////////////////////////////////
//return desired tile
//////////////////////////////////////
std::shared_ptr<Tile> TileFacFunc::operator()(char tile)
{

	if (tile == g_kFloor || tile == g_kWall || tile == g_kEmptyTile || tile == g_kEnd)
		return GetBasicTile(tile);

	if (tile == g_kSpikes)
		return std::shared_ptr<Tile>(new Tile(new Spikes(5)));

	if (tile == g_kDoor)
		return std::shared_ptr<Tile>(new Tile(new DoorTile(1)));

	if (tile == g_kSpikeTrap)
		return std::shared_ptr<SpikeTrap>(new SpikeTrap(3));

	return nullptr;
}



/*
Tile* Tile::TileFac(char disp)
{

	if (disp == g_kFloor)
		return new Tile(g_kFloor, false);

	if (disp == g_kWall)
		return new Tile(g_kWall, true);

	if (disp == g_kEmptyTile)
		return new Tile(g_kEmptyTile, true);

	if (disp == g_kEnd)
		return new Tile(g_kEnd, false);

	if (disp == g_kSpikes)
		return new Tile(new Spikes(5));

	if (disp == g_kDoor)
		return new Tile(new DoorTile(1));

	if (disp == g_kSpikeTrap)
		return new SpikeTrap(3);

	return nullptr;
}*/


////////////////////////////////////
//Spike trap functions
////////////////////////////////////////


SpikeTrap::SpikeTrap(int switchTime)
	:Tile(g_kFloor, false)
	, m_spike(false)
	, m_quickToggle(false)
	, m_timeSinceChange(0)
	, m_timeTillToggle(switchTime)
{
	if (m_timeTillToggle < 0)
		m_timeTillToggle = -1;

	if (m_timeTillToggle == 0)
		m_quickToggle = true;
}

SpikeTrap::SpikeTrap()
	:Tile(g_kFloor, false)
	, m_spike(false)
	, m_quickToggle(false)
	, m_timeSinceChange(0)
	, m_timeTillToggle(-1)
{}

/////////////////////////
//set behavior to spikes if not already
///////////////////////////////
void SpikeTrap::SetSpike()
{
	if (!m_spike)
	{
		delete m_pBehavior;
		m_pBehavior = new Spikes(5);
	}
}

/////////////////////////
//set behavior to floor if not already
///////////////////////////////
void SpikeTrap::SetFloor()
{
	if (m_spike)
	{
		delete m_pBehavior;
		m_pBehavior = new TileBehavior(g_kFloor, false);
	}
}

/////////////////////////
//switch between states
///////////////////////////////
void SpikeTrap::Toggle()
{
	if (!m_spike)
		SetSpike();

	if (m_spike)
		SetFloor();

	m_spike = !m_spike;
}

/////////////////////////
//determins if state needs to be switched 
///////////////////////////////
void SpikeTrap::Update()
{
	if (!m_quickToggle && m_timeTillToggle != -1)
	{
		++m_timeSinceChange;

		if (m_timeSinceChange % m_timeTillToggle == 0)
		{
			Toggle();
			m_timeSinceChange = 0;
		}
		return;
	}

	//switch every update or when time is met
	if (m_quickToggle)
	{
		Toggle();
		return;
	}
}

void SpikeTrap::Activate(Pawn* target)
{
	if (target && m_timeTillToggle == -1)
		SetSpike();

	m_pBehavior->Activate(target);
}

