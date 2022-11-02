#pragma once

#include <iostream>

/**
 * Two - dimensional vector that stores integer points.
 * Note: it is made specifically for snake-console-game,
 * and it has specific coordinate system.
 */
struct IntVector2
{
public:
	int X;
	int Y;

public:
	IntVector2()
	{
		X = 0;
		Y = 0;
	}

	IntVector2(int x, int y) : X(x), Y(y) {}

	IntVector2(int a) : X(a), Y(a) {}

public:
	static const IntVector2 ZeroVector;

	/**
	 * Take a note that vectores direct as we (human beings) perceive,
	 * but vector coordinates corresponds to console coordinate system,
	 * with which the game map coincides.
	 */

	static const IntVector2 UpVector;
	static const IntVector2 LeftVector;
	static const IntVector2 DownVector;
	static const IntVector2 RightVector;

public:
	bool operator==(const IntVector2& other) const { return X == other.X && Y == other.Y; }

	bool operator!=(const IntVector2& other) const { return X != other.X || Y != other.Y; }

	IntVector2 operator+(const IntVector2& other) const { return IntVector2(X + other.X, Y + other.Y); }

	IntVector2 operator-(const IntVector2& other) const { return IntVector2(X - other.X, Y - other.Y); }

	IntVector2 operator+=(const IntVector2& other)
	{
		X += other.X;
		Y += other.Y;
		return *this;
	}

	IntVector2 operator-=(const IntVector2& other)
	{
		X -= other.X;
		Y -= other.Y;
		return *this;
	}

	IntVector2 operator-() const { return IntVector2(-X, -Y); }

	friend std::ostream& operator<<(std::ostream& os, const IntVector2& vector)
	{
		os << '(' << vector.X << ", " << vector.Y << ')';
		return os;
	}

public:
	bool IsZero() { return *this == ZeroVector; }

public:
	static bool WithinRange(const IntVector2& vec, int xlower, int xupper, int ylower, int yupper, bool exclusive = true)
	{
		if (exclusive) return (vec.X > xlower && vec.X < xupper) && (vec.Y > ylower && vec.Y < yupper);
		return (vec.X >= xlower && vec.X <= xupper) && (vec.Y >= ylower && vec.Y <= yupper);
	}
};
