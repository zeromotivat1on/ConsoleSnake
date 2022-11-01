#pragma once

#include "Core.h"
#include "Game/Cell.h"

// Game object that have location, texture, type, can tick and collide.
class Actor : public Cell
{
public:
	Actor() = default;
	Actor(const IntVector2& location, const CellType type = CellType::CT_Empty);
	virtual ~Actor() = default;

	virtual void Reset() override;

protected:
	// Cell with which the actor collided.
	std::unique_ptr<Cell> CollidedCell;

public:
	void SetCollidedCell(std::unique_ptr<Cell>& collidedCell) { CollidedCell = std::move(collidedCell); }

protected:
	// Validate actor position through collision detection.
	virtual void CollisionTick();

public:
	// Called during game cycle.
	virtual void Tick();
};
