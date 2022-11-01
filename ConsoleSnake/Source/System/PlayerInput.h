#pragma once

#include "stdint.h"

// Player input while game loop.
enum class GameInput : uint8_t
{
	GI_SUp = 'w',	 // w
	GI_SLeft = 'a',	 // a
	GI_SDown = 's',	 // s
	GI_SRight = 'd', // d
};

enum class MainMenuInput : uint8_t
{
	MMI_Play = 'p', // p
	MMI_Exit = 27,	// esc
};

enum class GameOverInput : uint8_t
{
	// Restart the game. (r)
	GOI_Restart = 'r',

	// End the game. Go to main menu. (esc)
	GOI_End = 27,
};