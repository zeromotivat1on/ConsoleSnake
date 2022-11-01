#include "Map.h"
#include "Food.h"
#include "Snake.h"
#include "Helpers.h"

Map::Map(const IntVector2& size) //
	: Size(size), Height(size.Y), Width(size.X)
{
	InitializeMap();
}

void Map::Reset() 
{
	ResetMapBlueprint();
	PlayerSnake.reset();
	Actors.clear();
}

void Map::InitializeMap()
{
	MapBlueprint = MapType(Height);

	for (int y = 0; y < Height; ++y)
	{
		MapBlueprint[y] = std::vector<char>(Width);

		for (int x = 0; x < Width; ++x)
		{
			char cell = InitMapCellTexture(IntVector2(x, y));

			FreeCells += (cell == (char)CellType::CT_Wall) ? 0 : 1;

			MapBlueprint[y][x] = cell;
		}
	}

	DefaultMapBlueprint = MapBlueprint;
}

char Map::InitMapCellTexture(const IntVector2& location) const
{
	return ShouldBeWall(location) ? (char)CellType::CT_Wall : (char)CellType::CT_Empty;
}

bool Map::IsWall(const IntVector2& location) const
{
	return MapBlueprint[location.Y][location.X] == (char)CellType::CT_Wall;
}

bool Map::IsOutOfBounds(const IntVector2& location) const
{
	return !IntVector2::WithinRange(location, 0, Width - 1, 0, Height - 1);
}

bool Map::ShouldBeWall(const IntVector2& location) const
{
	return location.X == 0			  //
		   || location.Y == 0		  //
		   || location.X == Width - 1 //
		   || location.Y == Height - 1;
}

void Map::BlueprintActors()
{
	for (const auto& actor : Actors)
	{
		const IntVector2 location = actor->GetLocation();

		if (IsOutOfBounds(location)) continue;

		MapBlueprint[location.Y][location.X] = actor->GetTexture();
	}
}

void Map::BlueprintSnake()
{
	Snake* snake = PlayerSnake.get();
	for (const auto& bodyPart : snake->GetBody())
	{
		SnakeBodyCell* bodyPartCell = bodyPart.get();
		MapBlueprint[bodyPartCell->GetY()][bodyPartCell->GetX()] = bodyPartCell->GetTexture();
	}
}

void Map::Render()
{
	ResetMapBlueprint();
	BlueprintSnake();
	BlueprintActors();
	Print();
}

void Map::Print()
{
	for (int y = 0; y < Height; ++y)
	{
		for (int x = 0; x < Width; ++x)
		{
			std::cout << MapBlueprint[y][x]; //
		}

		std::cout << '\n';
	}
}

bool Map::DrawMapCellTexture(const IntVector2& location, const char texture)
{
	if (IsOutOfBounds(location)) return false;

	MapBlueprint[location.Y][location.X] = texture;

	return true;
}

bool Map::AddActor(std::unique_ptr<Actor>& actor)
{
	if (IsOutOfBounds(actor.get()->GetLocation())) return false;

	Actors.emplace_back(std::move(actor));

	return true;
}

bool Map::AddActor(std::unique_ptr<Actor>&& actor) 
{
	if (IsOutOfBounds(actor.get()->GetLocation())) return false;

	Actors.emplace_back(std::move(actor));

	return true;
}

bool Map::AddActor(const IntVector2& location, const CellType type)
{
	if (IsOutOfBounds(location)) return false;

	Actors.emplace_back(std::make_unique<Actor>(location, type));

	return true;
}

bool Map::RemoveActorByLocation(const IntVector2& location)
{
	if (IsOutOfBounds(location)) return false;

	auto removeIt = Actors.begin();
	for (auto it = Actors.begin(); it != Actors.end(); ++it)
	{
		auto& actor = *it;
		if (actor->GetLocation() == location) removeIt = it;
	}

	if (!(*removeIt)) return false;

	Actors.erase(removeIt);
	return true;
}
