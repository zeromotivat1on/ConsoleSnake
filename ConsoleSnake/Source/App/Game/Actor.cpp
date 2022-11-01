#include "Actor.h"

Actor::Actor(const IntVector2& location, const CellType type) //
	: Cell(location, type)
{
}

void Actor::Reset() 
{
	Cell::Reset();
	CollidedCell.reset();
}

void Actor::Tick()
{
	CollisionTick();
}

void Actor::CollisionTick() {}
