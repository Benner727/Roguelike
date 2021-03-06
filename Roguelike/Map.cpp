#include "Map.h"

#include "InputHandler.h"

#include "MonsterBuilder.h"

Map::Map(int width, int height)
	: mWidth(width), mHeight(height)
{
	//mMapGenerator = new CaveGenerator(mWidth, mHeight);
	mMapGenerator = new DungeonGenerator(mWidth, mHeight);

	GenerateNewMap();
}


Map::~Map()
{
	delete mMapGenerator;
}

std::vector<int> Map::GenerateDijkstraMap(int sourceX, int sourceY)
{
	std::vector<Point> tiles;

	std::vector<int> tileFlags;
	for (int i = 0; i < mWidth * mHeight; i++)
		tileFlags.push_back(-1);

	std::queue<Point> queue;
	int distance = 0;

	queue.push(Point(sourceX, sourceY));
	tileFlags[sourceX + sourceY * mWidth] = distance;

	while (queue.size() > 0)
	{
		Point tile = queue.front();
		queue.pop();

		tiles.push_back(tile);

		distance++;

		for (int x = tile.tileX - 1; x <= tile.tileX + 1; x++)
		{
			for (int y = tile.tileY - 1; y <= tile.tileY + 1; y++)
			{
				if (x >= 0 && x < mWidth && y >= 0 && y < mHeight)
				{
					if (tileFlags[x + y * mWidth] == -1 && mTiles[x + y * mWidth].walkable)
					{
						queue.push(Point(x, y));
						tileFlags[x + y * mWidth] = distance;
					}
				}
			}
		}
	}

	return tileFlags;
}

const bool Map::Walkable(int x, int y)
{
	//Coordinates are inside map and tile is floor
	return (x >= 0 && x < mWidth && y >= 0 && y < mHeight) && mTiles[x + y * mWidth].walkable;
}

void Map::GenerateNewMap()
{
	mSeed = time(NULL);
	std::cout << mSeed << std::endl;
	
	mTiles.clear();
	for (auto& tileId : mMapGenerator->GenerateMap(mSeed))
	{
		if (tileId == 0)
			mTiles.push_back(Tile(tileId, false, true));
		else
			mTiles.push_back(Tile(tileId, true, false));
	}
}

void Map::Draw()
{
	static Sprite wallVisible(8, 5, { 216, 208, 192 });
	static Sprite floorVisible(8, 5, { 192, 121, 88 });
	static Sprite wallExplored(8, 5, { 91, 68, 78 });
	static Sprite floorExplored(8, 5, { 89, 56, 64 });

	static Sprite startTile(8, 5, { 0, 255, 0 });
	static Sprite endTile(8, 5, { 255, 0, 0 });

	for (int y = 0; y < mHeight; y++)
	{
		for (int x = 0; x < mWidth; x++)
		{
			if (mTiles[x + y * mWidth].visible)
			{
				mTiles[x + y * mWidth].explored = true;

				if (mTiles[x + y * mWidth].tileId == 1)
				{
					wallVisible.Draw(x, y);
				}
				else if (mTiles[x + y * mWidth].tileId == 0)
				{
					floorVisible.Draw(x, y);
				}
			}
			else if (mTiles[x + y * mWidth].explored)
			{
				if (mTiles[x + y * mWidth].tileId == 1)
				{
					wallExplored.Draw(x, y);
				}
				else
				{
					floorExplored.Draw(x, y);
				}
			}
		}
	}

	startTile.Draw(mMapGenerator->GetStart().tileX, mMapGenerator->GetStart().tileY);
	endTile.Draw(mMapGenerator->GetEnd().tileX, mMapGenerator->GetEnd().tileY);
}