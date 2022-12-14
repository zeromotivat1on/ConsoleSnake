#include "Food.h"

Food::Food(const IntVector2& location, const CellType type) //
	: Actor(location, type), Score(10)
{
}

IntVector2 Food::GenerateLocation(const IntVector2& upper)
{
	// Generate food inside map.
	int randX = (rand() % (upper.X - 2)) + 1;
	int randY = (rand() % (upper.Y - 2)) + 1;

	return IntVector2(randX, randY);
}