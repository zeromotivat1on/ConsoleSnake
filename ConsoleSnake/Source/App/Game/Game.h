#pragma once

#include "Core.h"
#include "App/AppComponent.h"
#include "Game/Map/Map.h"
#include "Game/Food/Food.h"
#include "Game/Snake/Snake.h"
#include "Game/Abstractions/Cell.h"

// Top layer of snake-game logic.
class Game final : public AppComponent
{
public:
	Game() = default;
	Game(std::unique_ptr<Map> map, std::unique_ptr<Snake> snake);
	Game(const IntVector2& mapSize, const IntVector2& snakeInitialLocation);
	~Game();

private:
	// Game map with actors.
	std::unique_ptr<Map> GameMap = nullptr;

	// Snake under player control.
	std::shared_ptr<Snake> PlayerSnake = nullptr;

	// Snake game state.
	GameState GameState = GameState::GS_Play;

	// Player score can be increased by eating fruit.
	int PlayerScore = 0;

	// Offset for additional game info (score etc.)
	// that is placed to right to the game map.
	int SecondScreenOffsetX = 0;

	// Threads.
	std::vector<std::thread> Workers;

	// Atomic fields for timer on separate thread;

	std::atomic_int Seconds = 0;
	std::atomic_int Minutes = 0;
	std::atomic_int Hours = 0;

public:
	enum class GameState GetGameState() const { return GameState; }

	// Get app state that corresponds to game state.
	AppState GetCorrespondingAppState() const;

private:
#pragma region GameTick

	// Tick exactly while playing the game.
	void GameTick();

	// Update and display game map with its actors.
	void RenderGameMap();

	// Update and display second screen (score etc.).
	void RenderSecondScreen();

	// Handle player input during game.
	void ConsumeGameInput();

	// Tick all actors on map.
	void TickActors();

	// Validate snake collision.
	void CheckSnakeCollision();

	// Check game over conditions.
	// Set GameOver state if conditions are met.
	// @return true - game in GameOver state.
	// @return false - game NOT in GameOver state.
	bool CheckEndGame();

	// Add actor to map actors array.
	template <typename T> //
	bool AddActorToMap(const IntVector2& location, const CellType type = CellType::CT_Empty)
	{
		static_assert(std::is_base_of<Actor, T>::value, "T is not of type Actor");
		return GameMap->AddActor(std::make_unique<T>(location, type));
	}

	// Generate food at random place on map.
	template <typename T = Food> //
	bool GenerateFoodOnMap()
	{
		static_assert(std::is_base_of<Food, T>::value, "T is not of type Food");

		IntVector2 foodLocation = Food::GenerateLocation(GameMap->GetSize());

		// Get rid of situations when food doesn't spawn on empty cell.
		// Warning: with snake grow, amount of iterations will increase (on average).

		// Add 1 to player snake as at this moment we don't know
		// that snake has increased, but it definetly will.
		bool mapHasSpaceToSpawnFood = PlayerSnake->GetLength() + 1 < GameMap->GetFreeCells();

		// While food not on empty cell and map has space to spawn food - retry to spawn new food.
		while (GameMap->GetMapCellTexture(foodLocation) != (char)CellType::CT_Empty && mapHasSpaceToSpawnFood)
		{
			foodLocation = Food::GenerateLocation(GameMap->GetSize()); //

			std::stringstream sstream;
			sstream << "Generated food location: " << foodLocation << " Game map size: " << GameMap->GetSize();
			sstream << "Snake length + 1: " << PlayerSnake->GetLength() + 1 << "Map free cells: " << GameMap->GetFreeCells();
			ConsoleRenderer::RenderVertically(sstream, IntVector2(10, 10));
		}

		return AddActorToMap<T>(foodLocation, CellType::CT_Food);
	}

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

	// Render simple timer on second screen.
	void RenderTimer();

public:
	// Perfrom game tick.
	void Tick();

	// Start the game loop.
	void Start();
};