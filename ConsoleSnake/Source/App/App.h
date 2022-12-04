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
	std::shared_ptr<AppComponent> MainMenu;
	std::shared_ptr<AppComponent> SnakeGame;

	AppState AppState = AppState::AS_MainMenu;

	// Interval between ticks.
	std::chrono::microseconds DeltaTime = std::chrono::microseconds(TICK_MS);

public:
	enum class AppState GetState() const { return AppState; }

	std::shared_ptr<AppComponent> GetMainMenu() const { return MainMenu; }
	std::shared_ptr<AppComponent> GetSnakeGame() const { return SnakeGame; }

public:
	// Start the application.
	void Start();

private:
	// App tick.
	void Tick();
};