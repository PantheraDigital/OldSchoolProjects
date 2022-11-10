#pragma once
#include "Level.h"

//singlton that tracks user status
//loads and runs each level
class World
{
private:
	typedef std::vector<std::string> StringVec;
	typedef std::vector<std::vector<char>> LevelGrid;

	static World* m_pInst;
	World();

	std::string m_levelDirect;//location of levels
	StringVec m_levelNames;//level names to load listed in order

	int m_spawnTime;//time till monster spaws

	User* m_pUser;


	std::vector<std::vector<char>> Load(std::string levelName);//load level

	void PrintIntro();

public:

	static World* GetInstance();
	~World();

	void RunGame();//game loop

};

