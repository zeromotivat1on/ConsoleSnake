#pragma once

#include "Core.h"
#include "Game/Cell.h"
#include "Game/Map.h"

class Snake;

// Top layer of snake-game logic.
class Game final
{
public:
	Game() = default;
	Game(const IntVector2& mapSize, const IntVector2& snakeInitialLocation);
	~Game() = default;

private:
	// Game map with actors.
	std::unique_ptr<Map> GameMap = nullptr;

	// Snake under players control.
	std::shared_ptr<Snake> PlayerSnake = nullptr;

	// Snake game state.
	GameState GameState = GameState::GS_Play;

public:
	Map* GetMap() const { return GameMap.get(); }

	enum class GameState GetGameState() const { return GameState; }

	// Get app state that corresponds to game state.
	AppState GetCorrespondingAppState() const;

private:
#pragma region GameTick

	// Tick exactly while playing the game.
	void GameTick();

	// Update and display game map with its actors.
	void RenderGameMap();

	// Handle player input during game.
	void ConsumeGameInput();

	// Tick all actors on map.
	void TickActors();

	// Validate snake collision.
	void CheckSnakeCollision();

	// Check game over conditions.
	void CheckEndGame();

	// Add actor to map actors array.
	bool AddActorToMap(const IntVector2& location, const CellType type = CellType::CT_Empty);

	// Generate food at random place on map.
	bool GenerateFoodOnMap();

#pragma endregion GameTick

#pragma region GameOverTick

	// Tick exactly while "Game Over" screen.
	void GameOverTick();

	// Update and display "Game Over" screen.
	void RenderGameOverScreen();

	// Handle player input during game over.
	void ConsumeGameOverInput();

	// Reset game data.
	void Reset();

#pragma endregion GameOverTick

public:
	// Perfrom game tick.
	void Tick();

	// Start the game loop.
	void Start();
};