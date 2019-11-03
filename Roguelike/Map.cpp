#include "Map.h"

#include "InputHandler.h"

Map::Map(int width, int height)
	: mWidth(width), mHeight(height)
{
	mMapGenerator = new CaveGenerator(mWidth, mHeight);
	//mMapGenerator = new DungeonGenerator(mWidth, mHeight);

	mSeed = time(NULL);
	for (auto& tileId : mMapGenerator->GenerateMap(mSeed))
	{
		if (tileId == 0)
			mTiles.push_back(Tile(tileId, false, true));
		else
			mTiles.push_back(Tile(tileId, true, false));
	}
	std::cout << mSeed << std::endl;
}


Map::~Map()
{
	delete mMapGenerator;
}

bool Map::Walkable(int x, int y)
{
	//Coordinates are inside map and tile is floor
	return (x >= 0 && x < mWidth && y >= 0 && y < mHeight) && mTiles[x + y * mWidth].walkable;
}

void Map::Update()
{
	if (InputHandler::Instance().KeyPressed(SDL_SCANCODE_SPACE))
	{
		mSeed = time(NULL);
		for (auto& tileId : mMapGenerator->GenerateMap(mSeed))
		{
			if (tileId == 0)
				mTiles.push_back(Tile(tileId, false, true));
			else
				mTiles.push_back(Tile(tileId, true, false));
		}
		std::cout << mSeed << std::endl;
	}
}

void Map::Draw()
{
	static Sprite wallVisible(8, 5, { 216, 208, 192 });
	static Sprite floorVisible(8, 5, { 192, 121, 88 });
	static Sprite wallExplored(8, 5, { 91, 68, 78 });
	static Sprite floorExplored(8, 5, { 89, 56, 64 });

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
				else
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
}