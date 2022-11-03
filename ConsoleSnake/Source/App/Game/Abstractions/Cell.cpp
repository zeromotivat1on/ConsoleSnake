#include "Cell.h"

Cell::Cell(const IntVector2& location, const CellType type) //
	: Location(location), Type(type), Texture((char)type)
{
}

void Cell::Reset()
{
	Location = IntVector2::ZeroVector;
	Type = CellType::CT_Empty;
	Texture = (char)CellType::CT_Empty;
}
