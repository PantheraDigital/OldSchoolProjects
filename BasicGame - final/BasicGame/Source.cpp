#include <time.h>

#include "World.h"
#include "LevelMaker.h"




int main()
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);

	srand((unsigned int)time(nullptr));//seed

	LevelMaker lev;
	lev.RunLevelEditor();

	system("cls");

	World* game = World::GetInstance();

	game->RunGame();


	return 0;
}