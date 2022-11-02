#pragma once

#include "Core.h"
#include "Game/Cell.h"

class Actor;
class Snake;

class Map
{
public:
	using MapType = std::vector<std::vector<char>>;

public:
	Map() = default;
	Map(const IntVector2& size);
	virtual ~Map() = default;

	// Reset map to restart the game.
	virtual void Reset();

protected:
	IntVector2 Size = IntVector2::ZeroVector;
	int Width = 0;
	int Height = 0;

	// Non-collidable map cells.
	int FreeCells = 0;

	// 2d array of chars representing map.
	MapType MapBlueprint;

	// Map blueprint right after initialization.
	MapType DefaultMapBlueprint;

	// Snake controlled by player.
	std::shared_ptr<Snake> PlayerSnake;

	// Actors that are currently on map.
	std::vector<std::shared_ptr<Actor>> Actors;

public:
	IntVector2 GetSize() const { return Size; }
	int GetWidth() const { return Width; }
	int GetHeight() const { return Height; }

	// Get non-collidable map cells.
	int GetFreeCells() const { return FreeCells; };

	MapType& GetMapBlueprint() { return MapBlueprint; }

	void SetPlayerSnake(std::shared_ptr<Snake>& snake) { PlayerSnake = snake; }

	// Get reference to actors on map.
	auto& GetActors() { return Actors; }

	// Is a cell at given location a wall?
	// Check is using cell type.
	bool IsWall(const IntVector2& location) const;

	// Is a cell at given location is out of bounds?
	bool IsOutOfBounds(const IntVector2& location) const;

	// Is a cell at given location exactly inside map?
	bool IsInsideMap(const IntVector2& location) const;

protected:
	// Create map cells with appropriate types and textures.
	void InitializeMap();

	/**
	 * Initialize a map cell texture with given location for this map.
	 * Used during map blueprint initialization.
	 * @return char - map cell texture.
	 */
	char InitMapCellTexture(const IntVector2& location) const;

	// Is a cell at given location should be a wall?
	// Used during map blueprint initialization.
	bool ShouldBeWall(const IntVector2& location) const;

	// Add actors to map blueprint.
	void BlueprintActors();

	// Add player snake to map blueprint.
	void BlueprintSnake();

public:
	// Draw map to console.
	void Render();

	// Reset map to its state right after initialization.
	void ResetMapBlueprint() { MapBlueprint = DefaultMapBlueprint; }

	// Prints the map to the console.
	void Print();

	/**
	 * Update map cell texture at given location.
	 * @return true - success of map cell update.
	 * @return false - failure of map cell update.
	 */
	bool DrawMapCellTexture(const IntVector2& location, const char texture);

	/**
	 * Add actor to this map.
	 * @return true - success of actor addition.
	 * @return false - failure of actor addition.
	 */
	bool AddActor(std::shared_ptr<Actor> actor);
	bool AddActor(const IntVector2& location, const CellType type = CellType::CT_Empty);

	/**
	 * Remove actor from this map by location.
	 * @return true - success of actor remove.
	 * @return false - failure of actor remove.
	 */
	bool RemoveActorByLocation(const IntVector2& location);

	// Retreive actor from map by its location.
	// @return std::shared_ptr<Actor> - found actor.
	// @return nullptr - no actor with given location on map.
	std::shared_ptr<Actor> GetActorByLocation(const IntVector2& location);
};
