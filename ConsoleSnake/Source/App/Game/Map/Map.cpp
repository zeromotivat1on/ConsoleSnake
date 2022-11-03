#include "Map.h"
#include "Game/Snake/Snake.h"
#include "Game/Food/Food.h"

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
	return !IntVector2::WithinRange(location, 0, Width - 1, 0, Height - 1, true);
}

bool Map::IsInsideMap(const IntVector2& location) const
{
	return IntVector2::WithinRange(location, 0, Width - 1, 0, Height - 1);
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
	if (!snake) return;

	for (const auto& bodyPart : snake->GetBody())
	{
		const SnakeBodyCell* bodyPartCell = bodyPart.get();
		int bodyPartY = bodyPartCell->GetY();
		int bodyPartX = bodyPartCell->GetX();

		if (IsOutOfBounds(IntVector2(bodyPartX, bodyPartY))) continue;

		MapBlueprint[bodyPartY][bodyPartX] = bodyPartCell->GetTexture();
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
	std::stringstream mapStream;

	for (int y = 0; y < Height; ++y)
	{
		for (int x = 0; x < Width; ++x)
		{
			mapStream << MapBlueprint[y][x]; //
		}

		mapStream << '\n';
	}

	ConsoleRenderer::RenderVertically(mapStream, IntVector2::ZeroVector);
}

bool Map::AddActor(std::shared_ptr<Actor> actor)
{
	if (!IsInsideMap(actor.get()->GetLocation())) return false;

	Actors.emplace_back(actor);

	return true;
}

bool Map::AddActor(const IntVector2& location, const CellType type)
{
	if (!IsInsideMap(location)) return false;

	Actors.emplace_back(std::make_shared<Actor>(location, type));

	return true;
}

bool Map::RemoveActorByLocation(const IntVector2& location)
{
	if (!IsInsideMap(location)) return false;

	auto removeIt = std::find_if(Actors.begin(), Actors.end(), //
		[&location](std::shared_ptr<Actor>& actor)			   //
		{													   //
			return location == actor.get()->GetLocation();	   //
		}													   //
	);

	if (!(*removeIt)) return false;

	Actors.erase(removeIt);
	return true;
}

std::shared_ptr<Actor> Map::GetActorByLocation(const IntVector2& location)
{
	auto it = std::find_if(Actors.begin(), Actors.end(),   //
		[&location](std::shared_ptr<Actor>& actor)		   //
		{												   //
			return location == actor.get()->GetLocation(); //
		}												   //
	);

	return *it;
}
