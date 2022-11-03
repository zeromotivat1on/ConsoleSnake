#include "Snake.h"

Snake::Snake(const IntVector2& location) : Actor(location, CellType::CT_SnakeHead)
{
	InitialLocaiton = location;

	// Snake head.
	Grow(location, CellType::CT_SnakeHead);

#if SDEBUG
	for (int i = 1; i < 10; ++i) { Grow(IntVector2(location.X, location.Y + i)); }
#endif
}

void Snake::Reset()
{
	Actor::Reset();

	Location = InitialLocaiton;
	Velocity = IntVector2::ZeroVector;
	IsDead = false;
	Length = 0;

	Body.clear();

	Grow(Location, CellType::CT_SnakeHead);

#if SDEBUG
	for (int i = 1; i < 10; ++i) { Grow(IntVector2(Location.X, Location.Y + i)); }
#endif
}

void Snake::Tick()
{
	MovementTick();
	CollisionTick();
}

void Snake::MovementTick()
{
	if (Velocity.IsZero()) return;

	const IntVector2 prevHeadLocation = Location;
	const IntVector2 movedHeadLocation = Location + Velocity;

	// Check to not let the player to kill snake just while moving at opposite direction.
	// Simply invert snake velocity.
	if (Length > 1 && movedHeadLocation == Body[1]->GetLocation()) Velocity = -Velocity;

	Location += Velocity;

	// Snake head.
	Body[0]->SetLocation(Location);
	Body[0]->SetPrevLocation(prevHeadLocation);

	for (int i = 0; i < Length - 1; ++i)
	{
		const IntVector2 prevBodyCellPrevLocation = Body[i]->GetPrevLocation();
		const IntVector2 bodyCellLocation = Body[i + 1]->GetLocation();

		Body[i + 1]->SetLocation(prevBodyCellPrevLocation);
		Body[i + 1]->SetPrevLocation(bodyCellLocation);
	}
}

void Snake::CollisionTick()
{
	if (!CollidedCell) return;

	const CellType collidedCellType = CollidedCell.get()->GetType();

	switch (collidedCellType)
	{
	case CellType::CT_Food:
	{
		// Reset collided cell.
		CollidedCell->Reset();

		const SnakeBodyCell* lastBodyCell = Body[Length - 1].get();
		Grow(lastBodyCell->GetPrevLocation());

		break;
	}

	case CellType::CT_Wall:
	case CellType::CT_SnakeBody:
		Velocity = IntVector2::ZeroVector;
		IsDead = true;
		break;

	default:
		break;
	}
}

void Snake::Grow(const IntVector2& location, const CellType type)
{
	Body.emplace_back(std::make_unique<SnakeBodyCell>(location, type));
	Length++;
}