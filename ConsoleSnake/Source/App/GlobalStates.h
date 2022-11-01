#pragma once

// States for the main App class.
enum class AppState : uint8_t
{
	// Player in main menu.
	AS_MainMenu = 0,

	// Playing the snake game.
	AS_Game = 1,

	// Exit the app.
	AS_Shutdown = 2,
};

// States for the app MainMenu class.
enum class MainMenuState : uint8_t
{
	// Idle in main menu.
	MMS_Idle = 0,

	// Start play game cycle.
	MMS_StartPlay = 1,

	// Exit the app.
	MMS_Shutdown = 2,
};

// States for the app Game class.
enum class GameState : uint8_t
{
	// Play game cycle.
	GS_Play = 0,

	// Game over screen (right after player snake death).
	GS_Over = 1,

	// Exit from the game cycle.
	GS_Shutdown = 2,
};