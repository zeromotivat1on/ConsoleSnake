#include "App/App.h"

#if SDEBUG
// Memory leaks detection
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

/**
 * Quick reminder for coordinate system in this game.
 *		(left)	-	<- X ->	   +	(right)
 *		(up)	-	<- Y ->    +	(down)
 */

static IntVector2 MapSize = IntVector2(MAP_WIDTH, MAP_HEIGHT);

#if SDEBUG
static IntVector2 SnakeInitialLocation = IntVector2((int)(4), (int)(4));
#else
static IntVector2 SnakeInitialLocation = IntVector2((int)(MAP_WIDTH * 0.5), (int)(MAP_HEIGHT * 0.5));
#endif

static SnakeGameParams SnakeGameParameters{MapSize, SnakeInitialLocation};

int main()
{
#if SDEBUG
	// Memory leaks detection
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	// Set seed for food random spawn.
	auto now = std::chrono::high_resolution_clock::now();
	srand((uint16_t)now.time_since_epoch().count());

	App snakeGameApp(SnakeGameParameters);
	snakeGameApp.Start();

	return 0;
}
