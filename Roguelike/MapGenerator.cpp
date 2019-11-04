#include "MapGenerator.h"



MapGenerator::MapGenerator(int width, int height)
	: mRNG(0), mWidth(width), mHeight(height)
{

}


void MapGenerator::SeedRNG(int seed)
{
	mRNG = RNG(seed);
}

bool MapGenerator::InsideMap(int x, int y)
{
	return (x >= 0 && x < mWidth && y >= 0 && y < mHeight);
}

//Rules for cellular automaton
void MapGenerator::SmoothMap()
{
	for (int y = 0; y < mHeight; y++)
	{
		for (int x = 0; x < mWidth; x++)
		{
			if (SurroundingWallCount(x, y) > 4)
				mTiles[x + y * mWidth] = 1;
			else if (SurroundingWallCount(x, y) < 4)
				mTiles[x + y * mWidth] = 0;
		}
	}
}

int MapGenerator::SurroundingWallCount(int x, int y)
{
	int wallCount = 0;

	for (int neighborX = x - 1; neighborX <= x + 1; neighborX++)
	{
		for (int neighborY = y - 1; neighborY <= y + 1; neighborY++)
		{
			if (InsideMap(neighborX, neighborY))
			{
				if (x != neighborX || y != neighborY)
					wallCount += mTiles[neighborX + neighborY * mWidth];
			}
			else
				wallCount++;
		}
	}

	return wallCount;
}

std::vector<std::vector<Point>> MapGenerator::GetRegions(int tileType)
{
	std::vector<std::vector<Point>> regions;

	std::vector<int> tileFlags;
	for (int i = 0; i < mWidth * mHeight; i++)
		tileFlags.push_back(0);

	for (int y = 0; y < mHeight; y++)
	{
		for (int x = 0; x < mWidth; x++)
		{
			if (tileFlags[x + y * mWidth] == 0 && mTiles[x + y * mWidth] == tileType)
			{
				std::vector<Point> newRegion = GetRegionTiles(x, y);
				regions.push_back(newRegion);

				for (const auto& tile : newRegion)
					tileFlags[tile.tileX + tile.tileY * mWidth] = 1;
			}
		}
	}

	return regions;
}

//Flood fill algorithm
std::vector<Point> MapGenerator::GetRegionTiles(int startX, int startY)
{
	std::vector<Point> tiles;

	std::vector<int> tileFlags;
	for (int i = 0; i < mWidth * mHeight; i++)
		tileFlags.push_back(0);

	int tileType = mTiles[startX + startY * mWidth];

	std::queue<Point> queue;

	queue.push(Point(startX, startY));
	tileFlags[startX + startY * mWidth] = 1;

	while (queue.size() > 0)
	{
		Point tile = queue.front();
		queue.pop();

		tiles.push_back(tile);

		for (int x = tile.tileX - 1; x <= tile.tileX + 1; x++)
		{
			for (int y = tile.tileY - 1; y <= tile.tileY + 1; y++)
			{
				if (InsideMap(x, y) && (y == tile.tileY || x == tile.tileX))
				{
					if (tileFlags[x + y * mWidth] == 0 && mTiles[x + y * mWidth] == tileType)
					{
						queue.push(Point(x, y));
						tileFlags[x + y * mWidth] = 1;
					}
				}
			}
		}
	}

	return tiles;
}