#pragma once
#include "TileBehavior.h"

#include <map>
#include <memory>

class Tile
{
	friend class TileFacFunc;

protected:
	TileBehavior* m_pBehavior;

	Tile(char disp, bool isWall)
	{
		m_pBehavior = new TileBehavior(disp, isWall);
	}

	Tile(TileBehavior* behavior)
		:m_pBehavior(behavior)
	{}

public:
	static TileFacFunc TileFac;

	~Tile()
	{
		delete m_pBehavior;
	}

	char GetDisplay() const { return m_pBehavior->GetDisplay(); }
	bool IsAWall() const { return m_pBehavior->IsAWall(); }

	virtual void Update() { m_pBehavior->Update(); }
	virtual void Activate(Pawn* target) { m_pBehavior->Activate(target); }

	void SetBehavior(TileBehavior* behavior)
	{
		if (m_pBehavior)
			delete m_pBehavior;

		m_pBehavior = behavior;
	}
};

///////////////////////////////////
//functor factory for tiles
//////////////////////////////////
class TileFacFunc
{
private:
	//store tiles that never change
	std::map<char, std::shared_ptr<Tile>> m_basicTiles;

	//return pointer to basic tile if one already exists
	std::shared_ptr<Tile> GetBasicTile(char tile);

public:
	~TileFacFunc();

	std::shared_ptr<Tile> operator()(char tile);
};


class SpikeTrap : public Tile
{
	friend TileFacFunc;

private:
	bool m_spike;
	bool m_quickToggle;
	int m_timeTillToggle;
	int m_timeSinceChange;

	void SetSpike();
	void SetFloor();
	void Toggle();

protected:
	SpikeTrap(int switchTime);
	SpikeTrap();

public:
	void Update() override;
	void Activate(Pawn* target) override;
};
