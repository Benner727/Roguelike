#include "DungeonGenerator.h"

#include <iostream>

DungeonGenerator::DungeonGenerator(int width, int height, bool smoothMap)
	: MapGenerator(width, height), mSmoothMap(smoothMap)
{
}


DungeonGenerator::~DungeonGenerator()
{
}

void DungeonGenerator::CreateRoom()
{
	int width = mRNG.RandomNumber(MIN_ROOM_LENGTH, MAX_ROOM_LENGTH);
	int height = mRNG.RandomNumber(MIN_ROOM_LENGTH, MAX_ROOM_LENGTH);

	int xPos = mRNG.RandomNumber(1, mWidth - width - 1);
	int yPos = mRNG.RandomNumber(1, mHeight - height - 1);

	std::vector<Point> roomTiles;

	if (CanPlace(xPos, yPos, width, height))
	{
		for (int y = yPos; y < yPos + height; y++)
		{
			for (int x = xPos; x < xPos + width; x++)
			{
				mTiles[x + y * mWidth] = 0;
				
				roomTiles.push_back(Point(x, y));
			}
		}

		mRooms.push_back(Room(roomTiles, mTiles, mWidth));
	}
}

bool DungeonGenerator::CanPlace(int cornerX, int cornerY, int width, int height)
{
	for (int y = cornerY - 1; y <= cornerY + height; y++)
	{
		for (int x = cornerX - 1; x <= cornerX + width; x++)
		{
			if (mTiles[x + y * mWidth] == 0)
				return false;
		}
	}

	return true;
}

void DungeonGenerator::BuildMap()
{
	std::vector<Room> survivingRooms;
	std::vector<std::vector<Point>> roomRegions = GetRegions(0);

	for (std::vector<Point> roomRegion : roomRegions)
		survivingRooms.push_back(Room(roomRegion, mTiles, mWidth));

	//mRooms = survivingRooms;

	std::sort(survivingRooms.begin(), survivingRooms.end());
	survivingRooms.back().SetAsMainRoom();
	survivingRooms.back().SetAccessibleFromMainRoom();

	ConnectClosestRooms(survivingRooms);
}

void DungeonGenerator::CreatePassage(Room& roomA, Room& roomB, Point tileA, Point tileB)
{
	Room::ConnectRooms(roomA, roomB);

	int start = tileA.tileX, end = tileB.tileX;

	if (tileA.tileX > tileB.tileX)
	{
		start = tileB.tileX;
		end = tileA.tileX;

		for (int x = start; x <= end; x++)
		{
			if (mTiles[x + tileA.tileY * mWidth] == 1)
				mTiles[x + tileA.tileY * mWidth] = 0;
		}
	}
	else
	{
		for (int x = start; x <= end; x++)
		{
			if (mTiles[x + tileB.tileY * mWidth] == 1)
				mTiles[x + tileB.tileY * mWidth] = 0;
		}
	}

	int x = start;
	start = tileA.tileY, end = tileB.tileY;

	if (tileA.tileY > tileB.tileY)
	{
		start = tileB.tileY;
		end = tileA.tileY;

		for (int y = start; y <= end; y++)
		{
			if (mTiles[x + y * mWidth] == 1)
				mTiles[x + y * mWidth] = 0;
		}
	}
	else
	{
		for (int y = start; y <= end; y++)
		{
			if (mTiles[x + y * mWidth] == 1)
				mTiles[x + y * mWidth] = 0;
		}
	}
}

std::vector<int> DungeonGenerator::GenerateMap(int seed)
{
	SeedRNG(seed);

	mTiles.clear();
	mRooms.clear();

	for (int i = 0; i < mWidth * mHeight; i++)
		mTiles.push_back(1);

	for (int i = 0; i < ROOM_PLACE_ATTEMPTS; i++)
	{
		CreateRoom();

		if (mRooms.size() >= MAX_ROOM_NUM)
			break;
	}

	if (mSmoothMap)
	{
		SmoothMap();
	}

	BuildMap();
	CreateEntryPoints();

	/*
	for (auto& room : mRooms)
	{
		std::vector<Point> entrances;
		for (auto& tile : room.GetEdgeTiles())
		{
			if (mTiles[tile.tileX + tile.tileY * mWidth] == 0)
				entrances.push_back(tile);
		}
	}
	*/

	if (GetRegions(0).size() > 1)
		std::cout << "Error" << std::endl;

	return mTiles;
}