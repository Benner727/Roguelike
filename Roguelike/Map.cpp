#include "Map.h"

#include "InputHandler.h"

Map::Map(int width, int height)
	: mWidth(width), mHeight(height)
{
	mMapGenerator = new CaveGenerator(mWidth, mHeight);

	mSeed = time(NULL);
	mTiles = mMapGenerator->GenerateMap(mSeed);
	std::cout << mSeed << std::endl;
}


Map::~Map()
{
	delete mMapGenerator;
}

void Map::Update()
{
	if (InputHandler::Instance().KeyPressed(SDL_SCANCODE_SPACE))
	{
		mSeed = time(NULL);
		mTiles = mMapGenerator->GenerateMap(mSeed);
		std::cout << mSeed << std::endl;
	}
}

void Map::Draw()
{
	static Sprite wall(8, 5, { 155, 155, 155 });
	static Sprite floor(8, 5, { 0, 0, 0 });

	for (int y = 0; y < mHeight; y++)
	{
		for (int x = 0; x < mWidth; x++)
		{
			if (mTiles[x + y * mWidth] == 1)
			{
				wall.Draw(x, y);
			}
			else
			{
				floor.Draw(x, y);
			}
		}
	}
}