#pragma once

#include "Core.h"
#include "Game/Game.h"
#include "Menu/MainMenu.h"

struct SnakeGameParams
{
	IntVector2 mapSize = IntVector2::ZeroVector;
	IntVector2 snakeInitialLocation = IntVector2::ZeroVector;
};

// Base class for this console-application.
class App final
{
public:
	App() = default;
	App(const SnakeGameParams& snakeGameParams);

private:
	std::unique_ptr<AppComponent> MainMenu;
	std::unique_ptr<AppComponent> SnakeGame;

	AppState AppState = AppState::AS_MainMenu;

public:
	// Interval between ticks.
	std::chrono::microseconds DeltaTime = std::chrono::microseconds(TICK_MS);

public:
	// Start the application.
	void Start();

private:
	// App tick.
	void Tick();
};