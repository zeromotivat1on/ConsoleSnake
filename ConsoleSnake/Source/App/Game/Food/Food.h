#pragma once

#include "Core.h"
#include "Game/Abstractions/Actor.h"

// Base food actor that disappears after collision with player snake.
// Stores score value to add to player total score.
class Food : public Actor
{
public:
	Food() = default;
	Food(const IntVector2& location, const CellType type = CellType::CT_Food);
	virtual ~Food() = default;

private:
	// Score to add after player snake ate the food.
	int Score = 0;

public:
	virtual int GetScore() const { return Score; }
	virtual void SetScore(int score) { Score = score; }

public:
	// Generate food random location to place on map.
	// @param upper - upper bounds for random position.
	static IntVector2 GenerateLocation(const IntVector2& upper);
};
