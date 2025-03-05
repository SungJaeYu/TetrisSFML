#include <iostream>
#include "Game.h"


int main()
{
	// Init srand
	std::srand(static_cast<unsigned>(time(NULL)));

	Game game;

	while (game.isRunning())
	{
		game.update();

		game.render();
	}
}