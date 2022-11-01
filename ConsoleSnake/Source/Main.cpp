// Memory leaks detection
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "App.h"

/**
 * Quick reminder for coordinate system in this game.
 *		(left)	-	<- X ->	   +	(right)
 *		(up)	-	<- Y ->    +	(down)
 */

static const int MapWidth = 60;
static const int MapHeight = 25;
static IntVector2 MapSize = IntVector2(MapWidth, MapHeight);
static IntVector2 SnakeInitialLocation = IntVector2((int)(MapWidth * 0.5), (int)(MapHeight * 0.5));
static SnakeGameParams SnakeGameParameters{MapSize, SnakeInitialLocation};

int main()
{
	// Memory leaks detection
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// For food random spawn.
	srand((uint16_t)time(0));

	App snakeGameApp(SnakeGameParameters);
	snakeGameApp.Start();

	return 0;
}
