#pragma once
#include <vector>

#include "Vec2.h"

//internally store a level to edit
//can load, save, and create levels
class LevelMaker
{
private:
	typedef std::vector<std::vector<char>> LevelGrid;

	LevelGrid m_level;
	std::string m_levelName;

	unsigned int m_x, m_y;

	bool m_autoSet;
	char m_autoChar;

	bool m_slearScreen;

	//moves selected space
	Vec2 Input();
	int IntInput(int max);

	//returns if the position is within the range of the game
	bool IsInRange(int x, int y) const;

	//returns true if input matches any displayConstants
	bool IsValidInput(char input) const;
	//changes char at selected space using user input
	void SetTile();
	//expands level if position is greater than 0,0 and off grid
	void AddTile(unsigned int x, unsigned int y);

	//show stored level
	void DisplayInfo() const;
	void Display();
	//update selected tile in stored level
	bool Update();

	//create level, name, and save
	void MakeLevel(int x, int y);
	//edit stored level
	void EditLevel();

	//return loaded level
	void Load(std::string levelName);
	//save the level
	void Save(std::string levelName);

public:

	LevelMaker();
	~LevelMaker();

	void RunLevelEditor();
};