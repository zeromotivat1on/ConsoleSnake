// Memory leaks detection
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "App/App.h"

/**
 * Quick reminder for coordinate system in this game.
 *		(left)	-	<- X ->	   +	(right)
 *		(up)	-	<- Y ->    +	(down)
 */

static IntVector2 MapSize = IntVector2(MAP_WIDTH, MAP_HEIGHT);

static IntVector2 SnakeInitialLocation = IntVector2((int)(MAP_WIDTH * 0.5), (int)(MAP_HEIGHT * 0.5));

static SnakeGameParams SnakeGameParameters{MapSize, SnakeInitialLocation};

int main()
{
	// Memory leaks detection
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Set seed for food random spawn.
	auto now = std::chrono::high_resolution_clock::now();
	srand((uint16_t)now.time_since_epoch().count());

	App snakeGameApp(SnakeGameParameters);
	snakeGameApp.Start();

	return 0;
}
