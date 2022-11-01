#pragma once

#include "Math/SMath.h"

// Cell type with default textures.
enum class CellType : uint8_t
{
	CT_Empty = ' ',
	CT_Wall = '#',
	CT_SnakeHead = '0',
	CT_SnakeBody = 'o',
	CT_Food = '@'
};

// Base class for game objects that have texture, type and location in world.
class Cell
{
public:
	Cell() = default;
	Cell(const IntVector2& location, const CellType type = CellType::CT_Empty);
	virtual ~Cell() = default;

	// Reset cell data.
	virtual void Reset();

protected:
	// Current cell location.
	IntVector2 Location = IntVector2::ZeroVector;

	// Current cell type.
	CellType Type = CellType::CT_Empty;

	// Console view (character representation) of the cell.
	char Texture = ' ';

public:
	IntVector2 GetLocation() const { return Location; }
	int GetX() const { return Location.X; }
	int GetY() const { return Location.Y; }

	void SetLocation(const IntVector2& vec) { Location = vec; }

	CellType GetType() const { return Type; }
	void SetType(CellType type) { Type = type; }

	char GetTexture() const { return Texture; }
	void SetTexture(char texture) { Texture = texture; }

public:
	Cell& operator=(Cell&& other);

	bool operator==(const Cell& other) { return Location == other.Location && Type == other.Type && Texture == other.Texture; }
	bool operator==(const Cell* other) { return Location == other->Location && Type == other->Type && Texture == other->Texture; }

	friend std::ostream& operator<<(std::ostream& os, const Cell* cell)
	{
		os << (*cell).Texture;
		return os;
	}
};
