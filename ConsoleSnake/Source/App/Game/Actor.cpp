#include "Actor.h"

Actor::Actor(const IntVector2& location, const CellType type) //
	: Cell(location, type)
{
}

Actor::Actor(Actor&& other)
{
	*this = std::move(other);
}

Actor::Actor(Actor*&& other)
{
	*this = std::move(*other);
}

void Actor::Reset() 
{
	Cell::Reset();
	CollidedCell.reset();
}

Actor& Actor::operator=(Actor&& other)
{
	if (this != &other)
	{
		Location = other.Location;
		Type = other.Type;
		Texture = other.Texture;
		CollidedCell = std::move(other.CollidedCell);

		other.CollidedCell.release();
	}

	return *this;
}

void Actor::CollisionTick() {}

void Actor::Tick()
{
	CollisionTick();
}
