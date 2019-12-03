#include "LevelGenerator.h"



LevelGenerator::LevelGenerator(int width, int height)
	: MapGenerator(width, height)
{
}


LevelGenerator::~LevelGenerator()
{
}

void LevelGenerator::GenerateRect()
{
	Prefab room;

	int width = mRNG.RandomNumber(MIN_ROOM_SIZE, MAX_ROOM_SIZE);
	int height = mRNG.RandomNumber(MIN_ROOM_SIZE, MAX_ROOM_SIZE);

	int xPos = mRNG.RandomNumber(1, mWidth - width - 1);
	int yPos = mRNG.RandomNumber(1, mHeight - height - 1);

	room.tiles = std::vector<int>(width * height, 1);
	room.width = width;
	room.height = height;

	for (int y = 1; y < height - 1; y++)
		for (int x = 1; x < width - 1; x++)
			room.tiles[x + y * width] = 0;

	if (CanPlace(room, xPos, yPos))
	{
		int x = 0, y = 0;
		for (int realY = yPos; realY < yPos + room.height; realY++)
		{
			for (int realX = xPos; realX < xPos + room.width; realX++)
			{
				if (room.tiles[x + y * room.width] == 0)
					mTiles[realX + realY * mWidth] = 0;
				x++;
			}
			y++;
			x = 0;
		}
	}
}

void LevelGenerator::GenerateCross()
{
	Prefab room;

	int width = mRNG.RandomNumber(MIN_ROOM_SIZE, MAX_ROOM_SIZE);
	int height = mRNG.RandomNumber(MIN_ROOM_SIZE, MAX_ROOM_SIZE);

	int xPos = mRNG.RandomNumber(1, mWidth - width - 1);
	int yPos = mRNG.RandomNumber(1, mHeight - height - 1);

	room.tiles = std::vector<int>(width * height, -1);
	room.width = width;
	room.height = height;

	for (int y = 0; y < height; y++)
	{
		for (int x = width / 3; x < width * 2 / 3; x++)
		{
			if (x == width / 3 || y == 0 || x == width * 2 / 3 - 1 || y == height - 1)
				room.tiles[x + y * width] = 1;
			else
				room.tiles[x + y * width] = 0;
		}
	}

	for (int y = height / 3; y < height * 2 / 3; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if ((x == 0 || y == height / 3 || x == width - 1 || y == height * 2 / 3 - 1) && room.tiles[x + y * width] != 0)
				room.tiles[x + y * width] = 1;
			else
				room.tiles[x + y * width] = 0;
		}
	}

	if (CanPlace(room, xPos, yPos))
	{
		int x = 0, y = 0;
		for (int realY = yPos; realY < yPos + room.height; realY++)
		{
			for (int realX = xPos; realX < xPos + room.width; realX++)
			{
				if (room.tiles[x + y * room.width] == 0)
					mTiles[realX + realY * mWidth] = 0;
				x++;
			}
			y++;
			x = 0;
		}
	}
}

bool LevelGenerator::CanPlace(Prefab room, int xPos, int yPos)
{
	int x = 0, y = 0;
	for (int realY = yPos; realY < yPos + room.height; realY++)
	{
		for (int realX = xPos; realX < xPos + room.width; realX++)
		{
			if ((room.tiles[x + y * room.width] == 0 && mTiles[realX + realY * mWidth] == 0) ||
				(room.tiles[x + y * room.width] == 1 &&mTiles[realX + realY * mWidth] == 0))
				return false;
			x++;
		}
		y++;
		x = 0;
	}

	return true;
}

std::vector<int> LevelGenerator::GenerateMap(int seed)
{
	SeedRNG(seed);

	mTiles.clear();

	for (int i = 0; i < mWidth * mHeight; i++)
		mTiles.push_back(1);

	for (int i = 0; i < 30; i++)
		GenerateCross();

	return mTiles;
}
