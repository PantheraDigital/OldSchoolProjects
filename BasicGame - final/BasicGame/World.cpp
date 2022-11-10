#include "World.h"

#include <fstream>

#include "DisplayConsts.h"
#include "DirectoryReader.h"


World* World::m_pInst = nullptr;

World* World::GetInstance()
{
	if (!m_pInst)
		m_pInst = new World();

	return m_pInst;
}

World::World()
	:m_levelDirect("..\\Levels\\")
	,m_pUser(new User(Vec2(0, 0)))
	,m_spawnTime(5)
{
	m_pUser->PickUpItem(Pickup::PickupFac("dagger"));

	//get level names 
	DirectoryReader directRead;
	directRead(m_levelDirect, m_levelNames);
}


World::~World()
{
	delete m_pInst;
	delete m_pUser;
}

void World::PrintIntro()
{
	std::cout << "Welcome to the dungeon. Try and get to the end, but beware of traps and enemies.\nEach floor's end is marked with a " << g_kEnd << "\nMove with W A S D\nPress enter to play";
}

//////////////////////////////////////////////////
//return level grid from file at m_levelDirect with levelName
//////////////////////////////////////////////////////
std::vector<std::vector<char>> World::Load(std::string levelName)
{
	std::fstream fileStream;
	fileStream.open((m_levelDirect + levelName), std::ios_base::in);

	if (!fileStream.is_open())
	{
		std::cout << "Loading Error" << std::endl;
		LevelGrid empty;
		return empty;
	}

	std::vector<std::string> loaded;
	std::string nextLine;

	while (!fileStream.eof())//load the layout
	{
		std::getline(fileStream, nextLine);
		loaded.push_back(nextLine.c_str());
	}

	LevelGrid result;
	//move loaded data to returnable data
	for (unsigned int i = 0; i < loaded.size(); ++i)
	{
		std::vector<char> col;
		result.push_back(col);

		for (unsigned int j = 0; j < loaded[i].size(); ++j)
		{
			result[i].push_back(loaded[i][j]);
		}
	}

	//close the file
	fileStream.close();
	return result;
}

////////////////////////////////////////
//load and play through each level until the user dies or escapes
///////////////////////////////////////////
void World::RunGame()
{
	PrintIntro();
	getchar();
	system("cls");

	for (int i = 0; i < m_levelNames.size(); ++i)//loop through levels
	{
		Level l(Load(m_levelNames[i]), m_spawnTime, m_pUser);//get current level

		l.Print();

		while (l.Update())//game loop
		{
			l.Print();
		}

		if (m_pUser->IsDead())
		{
			std::cout << "\n\nYou have died\nPress enter to exit";
			getchar();
			return;
		}
	}

	std::cout << "\n\nYou escaped!\nPress enter to exit";
	getchar();
}