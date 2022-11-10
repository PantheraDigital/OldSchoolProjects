#include "LevelMaker.h"

#include <conio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#define NOMINMAX

#include "DisplayConsts.h"
#include "DirectoryReader.h"

#include "DrawFunction.h"

typedef std::vector<std::string> stringVec;



LevelMaker::LevelMaker()
	:m_x(0)
	,m_y(0)
	,m_autoSet(false)
	,m_autoChar(g_kEmptyTile)
	,m_levelName("No Level")
	, m_slearScreen(false)
{
}


LevelMaker::~LevelMaker()
{
}

///////////////////////////////////////
//let user make and edit levels
//loops until user chooses to play
/////////////////////////////////////////
void LevelMaker::RunLevelEditor()
{
	bool loop = true;
	while (loop)
	{
		system("cls");
		std::cout << "0. Make Level  1. Edit Level  2. Play\n";
		int select = IntInput(2);

		switch (select)
		{
			case 0:
			{
				std::cout << "Level width: ";
				int x = IntInput(75);
				std::cout << "Level hight: ";
				int y = IntInput(20);

				MakeLevel(x, y);
				break;
			}

			case 1:
			{
				DirectoryReader reader;
				std::cout << "\nChoose level to edit\n0. quit select\n";
				//list saved level file names/ lookup how to get file name and display
				stringVec v;
				reader("..\\Levels", v);

				for (int i = 0; i < v.size(); ++i)
				{
					if (v[i] == "." || v[i] == "..")
					{
						v.erase(v.begin() + i);
						--i;
					}
					else
						std::cout << i+1 << ". " << v[i] << std::endl;
				}

				//select level with num

				int index = IntInput((int)v.size());

				if (index == 0)
					break;

				//load into m_levelGrid
				Load(v[index - 1]);

				EditLevel();

				break;
			}

			case 2:
				loop = false;

			default:
				break;
		}	
	}
}

////////////////////////////////
//changes selected position if in grid
//calls SetTile() if ' ' input
//////////////////////////////
Vec2 LevelMaker::Input()
{
	char input = _getch();

	switch (input)
	{

	case 'w':
	{
		return Vec2(0, -1);
	}

	case 'a':
	{
		return Vec2(-1, 0);
	}

	case 's':
	{
		return Vec2(0, 1);
	}

	case 'd':
	{
		return Vec2(1, 0);
	}

	case ' ':
	{
		SetTile();
		m_slearScreen = false;
		return Vec2(0, 0);
	}

	case 'q':
	{
		return Vec2(-1, -1);
	}

	case 'e':
	{
		m_autoSet = !m_autoSet;
		return Vec2(0, 0);
	}

	default:
		return Vec2(0, 0);

	}
}

/////////////////////////////////
//retuns selection between 0 and max
////////////////////////////////////
int LevelMaker::IntInput(int max)
{
	bool valid = true;
	int input;

	if (max > 9)
	{
		while (valid)
		{
			std::cin >> input;

			if (std::cin.fail() || input > max || input < 0)
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Not allowed";
			}
			else
				valid = false;
		}
	}
	else
	{
		while (valid)
		{
			input = _getch() - '0';

			if (input > max || input < 0)
			{
				std::cout << "input out of range";
			}
			else
				valid = false;
		}
	}


	return input;
}

////////////////////////////////
//returns if location is within the max range
//////////////////////////////////
bool LevelMaker::IsInRange(int x, int y) const
{
	if (x >= 0 && y >= 0)
	{
		if (x <= 75 && y <= 20)//max range 
		{
			return true;
		}
	}

	return false;
}

//////////////////////////
//sets the selected tile to a chosen option
////////////////////////////////
void LevelMaker::SetTile()
{
	std::cout << "input desired object";
	char input = _getch();

	if (IsValidInput(input))
	{
		m_level[m_y][m_x] = input;
		m_autoChar = input;
	}

}

//////////////////////////////
//true if input matches any global display constants
///////////////////////////
bool LevelMaker::IsValidInput(char input) const
{
	if (input == g_kCircleAi || input == g_kFloor || input == g_kEmptyTile || input == g_kWall || input == g_kEnd || input == g_kDoor || input == g_kSpikes || input == g_kSpikeTrap || input == g_kMonSpawn 
		|| input == g_kPlayer || input == g_kWonderAi || input == g_kChaseAi 
		|| input == g_kHealth || input == g_kWeapon || input == g_kArmor || input == g_kKey)
		return true;

	return false;
}

///////////////////////////////////
//show all placable game objects
/////////////////////////////////////
void LevelMaker::DisplayInfo() const
{
	system("cls");
	//show options and controlls
	std::cout << "Player: " << g_kPlayer << "   Circle Ai: " << g_kCircleAi << "   Wondering Ai: " << g_kWonderAi << "   Charger Ai: " << g_kChaseAi << "   Monster Spawn: " << g_kMonSpawn;
	std::cout << "\nRandom Weapon: " << g_kWeapon << "   Armor: " << g_kArmor << "   HP potion: " << g_kHealth << "   Key: " << g_kKey;
	std::cout << "\nFloor: " << g_kFloor << "   Wall: " << g_kWall << "   Empty: '" << g_kEmptyTile << "'   End: " << g_kEnd << "   Spikes: " << g_kSpikes << "   Spike Trap: " << g_kSpikeTrap << "   Door: " << g_kDoor << "\n";

	std::cout << "\nLevel: " << m_levelName << "\n\n";
}
////////////////////////////////
//print stored level
///////////////////////////////
void LevelMaker::Display()
{
	Draw print;

	if (!m_slearScreen)
	{
		DisplayInfo();
		m_slearScreen = true;
	}


	print("WASD - move   q - exit & save   space - edit tile   e - auto set: ", 0, 6);
	if (m_autoSet)
		print('1');
	else
		print('0');
	std::cout << std::endl;

	//show grid
	for (unsigned int i = 0; i < m_level.size(); ++i)
	{
		for (unsigned int j = 0; j < m_level[i].size(); ++j)
		{
			if (i == m_y && j == m_x)
				print('_', j, i+7);
			else
				print(m_level[i][j], j, i+7);
		}
		std::cout << std::endl;
	}
}

//////////////////////////////
//create level, give name, store it in m_level, save
/////////////////////////////////
void LevelMaker::MakeLevel(int x, int y)
{
	//create
	LevelGrid newLevel;
	for (int i = 0; i < y; ++i)
	{
		std::vector<char> col;
		newLevel.push_back(col);

		for (int j = 0; j < x; ++j)
		{
			newLevel[i].push_back(g_kFloor);
		}
	}

	//name 
	if (!m_levelName.empty())
		m_levelName.clear();

	bool loop = true;

	do
	{
		std::cout << "Input level name: ";

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, m_levelName, '\n');

		std::size_t check = m_levelName.find_first_of("/:*?|<>\\\"");//  \ / : * ? " | < > are not allowed

		if (check != std::string::npos)//if the name contains any of the symbols
		{
			std::cin.clear();
			std::cout << "Bad name: ";
			std::cout << m_levelName[check] << "\n";//show bad symbol
		}
		else
		{
			loop = false;
		}

	} while (loop);

	//store
	m_level = newLevel;

	//save
	Save(m_levelName + ".lvl");
}

///////////////////////////
//edit stored level
/////////////////////////////
void LevelMaker::EditLevel()
{	
	if (m_level.empty())
	{
		//make a 1 tile grid or display "no level loaded"
		std::cout << "No Level";
	}
	else
	{
		LevelGrid originalLevel = m_level;
		m_x = 0;
		m_y = 0;

		Display();

		bool valid = true;
		while (valid)
		{
			valid = Update();
			Display();
		}

		std::cout << "Save changes? 0. no  1. yes\n";

		if (IntInput(1) == 1)//save new version
			Save(m_levelName);
		else
			m_level = originalLevel;//restore old version

		m_slearScreen = false;
	}
}

/////////////////////////
//update selected space
///////////////////////////
bool LevelMaker::Update()
{
	Vec2 inpt = Input();
	Vec2 result = inpt + Vec2(m_x, m_y);

	if (inpt == Vec2(-1, -1))//quit
		return false;


	//if (result >= Vec2(0, 0))
	if (IsInRange(result.m_x, result.m_y))
	{
		//if selected position is off the grid
		AddTile(result.m_x, result.m_y);//add tiles to location

		if (m_autoSet)
			m_level[result.m_y][result.m_x] = m_autoChar;

		//move
		m_x = result.m_x;
		m_y = result.m_y;
	}

	return true;
}

//////////////////////////////////
//expands grid out to location
//////////////////////////////
void LevelMaker::AddTile(unsigned int x, unsigned int y)
{
	//add a new row if needed
	if (y > m_level.size() - 1)
	{
		std::vector<char> row;
		m_level.push_back(row);

		//fill new row up to selected position
		for (unsigned int i = 0; i <= x; ++i)
			m_level[y].push_back(g_kEmptyTile);

		m_level[y][x] = g_kFloor;//set locaation of selection to floor
	}

	//if the location is furthur than 1 tile blank tiles will fill the gap
	if (x > m_level[y].size())
	{
		for (unsigned int i = (unsigned int)m_level[y].size() - 1; i < x ; ++i)
			m_level[y].push_back(g_kEmptyTile);//fill gap

		m_level[y][x] = g_kFloor;//set locaation of selection to floor
	}
	
	if (x > m_level[y].size() -1)
		m_level[y].push_back(g_kFloor);
}

/////////////////////////////
//save the level to file
////////////////////////////////
void LevelMaker::Save(std::string levelName)
{
	// 1. open the file
	std::fstream fileStream;
	fileStream.open("..\\Levels\\" + levelName, std::ios_base::out | std::ios_base::trunc);//write over any already existing file here

	// 2. make sure the file opened
	if (!fileStream.is_open())
	{
		std::cout << "Error opening file." << std::endl;
		return;
	}

	// 3. process the file

	for (unsigned int i = 0; i < m_level.size(); ++i)
	{
		for (unsigned int j = 0; j < m_level[i].size(); ++j)
		{
			fileStream.write(&(m_level[i][j]), sizeof(char));//contents
		}
		fileStream.write("\n", sizeof(char));//line break
	}

	// 4. close the file
	fileStream.close();
}

/////////////////////////////
//load and store level
/////////////////////////////////
void LevelMaker::Load(std::string levelName)
{
	std::fstream fileStream;
	fileStream.open(("..\\Levels\\" + levelName), std::ios_base::in);
	
	if (!fileStream.is_open())
	{
		std::cout << "Loading Error" << std::endl;
		m_levelName = "No Level";
		LevelGrid empty;
		m_level = empty;
		return;
	}

	if (!m_level.empty())
		m_level.clear();

	m_levelName = levelName;

	std::vector<std::string> loaded;
	std::string nextLine;

	while (!fileStream.eof())//load the layout
	{
		std::getline(fileStream, nextLine);
		loaded.push_back(nextLine.c_str());
	}

	//move loaded data to returnable data
	for (unsigned int i = 0; i < loaded.size() - 1; ++i)
	{
		std::vector<char> col;
		m_level.push_back(col);

		for (unsigned int j = 0; j < loaded[i].size(); ++j)
		{
			m_level[i].push_back(loaded[i][j]);
		}
	}
	
	//close the file
	fileStream.close();
}