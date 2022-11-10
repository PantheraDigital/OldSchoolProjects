
#include "LevelManager.h"
#include "EventManeger.h"//yes i just threw this in here 

LevelManager *LevelManager::m_instance = nullptr;//used for singleton
void BeginingText();
void Continue();

int main()
{

	EventManeger Begin;
	Begin.RegisterCallback(BeginingText);
	Begin.RegisterCallback(Continue);

	LevelManager* level = LevelManager::getInstance();
	int outcome;

	Begin.TriggerCallbacks();

	while (true)
	{
		outcome = level->Loop();
		
		if (outcome == -1)
		{
			system("CLS");
			std::cout << "you died\n";
			_getch();
			break;
		}
		else if (outcome == 1)
		{
			system("CLS");
			std::cout << "You escaped\n";
			_getch();
			break;
		}
		
	}

	return 0;
}


void BeginingText()
{
	std::cout << "Make it to the end marked by the 'E'.\nKeys,'K', open doors 'D'.\nDeadly spots 'X' will kill you\n";

}

void Continue()
{
	std::cout << "Press any key to play\n";
	_getch();
}