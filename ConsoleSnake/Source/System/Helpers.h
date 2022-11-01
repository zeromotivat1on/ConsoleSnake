/**
 * File with helper functions for various purposes.
 */

#pragma once

#include "Cell.h"

namespace SHelpers
{

static CellType GetCellType(char c) 
{
	switch (c)
	{
	case (char)CellType::CT_Empty:
		return CellType::CT_Empty;

	case (char)CellType::CT_Wall:
		return CellType::CT_Wall;

	case (char)CellType::CT_SnakeHead:
		return CellType::CT_SnakeHead;

	case (char)CellType::CT_SnakeBody:
		return CellType::CT_SnakeBody;

	case (char)CellType::CT_Food:
		return CellType::CT_Food;
	}
}

}