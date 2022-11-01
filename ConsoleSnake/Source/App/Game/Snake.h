#pragma once

#include "Core.h"
#include "Game/Actor.h"

// Snake body part with size equal to 1 map cell.
// Also stores its location before snake movement for convenience.
class SnakeBodyCell : public Actor
{
public:
	SnakeBodyCell(const IntVector2& location, const CellType type = CellType::CT_SnakeBody) //
		: Actor(location, type)
	{
	}

	SnakeBodyCell(SnakeBodyCell&& other) { *this = std::move(other); }
	SnakeBodyCell(SnakeBodyCell*&& other) { *this = std::move(*other); }
	virtual ~SnakeBodyCell() = default;

protected:
	// Location before movement.
	IntVector2 PrevLocation = IntVector2::ZeroVector;

public:
	IntVector2 GetPrevLocation() const { return PrevLocation; }
	void SetPrevLocation(const IntVector2& prevLocation) { PrevLocation = prevLocation; }

public:
	SnakeBodyCell& operator=(SnakeBodyCell&& other)
	{
		if (this != &other)
		{
			Location = other.Location;
			Type = other.Type;
			Texture = other.Texture;
			PrevLocation = other.PrevLocation;
			CollidedCell = std::move(other.CollidedCell);

			other.CollidedCell.release();
		}

		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const SnakeBodyCell* bodyCell)
	{
		os << "Location: " << bodyCell->Location << " PrevLocation: " << bodyCell->PrevLocation << '\n';
		return os;
	}
};

class Snake : public Actor
{
public:
	Snake(const IntVector2& location);
	virtual ~Snake() = default;

	// Reset snake data.
	virtual void Reset() override;

protected:
	// Store snake location that was obtained during construction.
	IntVector2 InitialLocaiton = IntVector2::ZeroVector;

	// Movement direction.
	IntVector2 Velocity = IntVector2::ZeroVector;

	// Snake body length.
	int Length = 0;

	// The body of this snake.
	std::vector<std::unique_ptr<SnakeBodyCell>> Body;

	// Is the snake dead?
	// Hit the wall or its own body.
	bool IsDead = false;

public:
	IntVector2 GetVelocity() const { return Velocity; }
	void SetVelocity(const IntVector2& velocity) { Velocity = velocity; }

	int GetLength() const { return Length; }

	std::vector<std::unique_ptr<SnakeBodyCell>>& GetBody() { return Body; }

	bool GetIsDead() const { return IsDead; }

public:
	virtual void Tick() override;

	/**
	 * Is the snake should be dead during collision with specific cell?
	 * @param collidedCellType - cell type with which snake collided.
	 */
	bool ShouldBeDead(CellType collidedCellType)
	{
		return collidedCellType == CellType::CT_Wall || collidedCellType == CellType::CT_SnakeBody;
	}

protected:
	// Try to move the snake in Velocity direction.
	void MovementTick();

	// Validate snake position.
	virtual void CollisionTick() override;

	/**
	 * Grow snake by 1 body cell.
	 * @param location - position of new snake body cell.
	 * @param type - cell type of new snake body.
	 */
	void Grow(const IntVector2& location, const CellType type = CellType::CT_SnakeBody);
};