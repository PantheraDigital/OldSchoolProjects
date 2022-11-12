#include "Game.h"
#include "GameplayStateMachine.h"



//additions:
//
//
//

int main(int argc, char** argv)
{

	Game game;

	GameplayStateMachine gameInstance(&game);

	game.Initialize(&gameInstance);

	game.RunGameLoop();
	game.Deinitialize();

	return 0;
}