#include "CaveGenerator.h"

#include <iostream>

CaveGenerator::CaveGenerator(int width, int height, int fillPercent, int smoothingIterations)
	: MapGenerator(width, height), mFillPercent(fillPercent), mSmoothingIterations(smoothingIterations)
{
}


CaveGenerator::~CaveGenerator()
{
}


std::vector<int> CaveGenerator::GenerateMap(int seed)
{
	SeedRNG(seed);

	mTiles.clear();
	FillMap();

	for (int i = 0; i < mSmoothingIterations; i++)
		SmoothMap();

	BuildMap();

	for (int y = 0; y < mHeight; y++)
	{
		for (int x = 0; x < mWidth; x++)
		{
			if (x == 0 || y == 0 || x == mWidth - 1 || y == mHeight - 1)
				mTiles[x + y * mWidth] = 1;
		}
	}

	if (GetRegions(0).size() > 1)
		std::cout << "Error" << std::endl;

	return mTiles;
}

//Fil map in randomly with tiles
void CaveGenerator::FillMap()
{
	for (int y = 0; y < mHeight; y++)
	{
		for (int x = 0; x < mWidth; x++)
		{
			if (x == 0 || x == mWidth - 1 ||
				y == 0 || y == mHeight - 1)
				mTiles.push_back(1);
			else
			{
				if (mRNG.RandomNumber(0, 100) < mFillPercent)
					mTiles.push_back(1);
				else
					mTiles.push_back(0);
			}
		}
	}
}

void CaveGenerator::BuildMap()
{
	std::vector<Room> survivingRooms = TrimMap();

	std::sort(survivingRooms.begin(), survivingRooms.end());
	survivingRooms.back().SetAsMainRoom();
	survivingRooms.back().SetAccessibleFromMainRoom();

	ConnectClosestRooms(survivingRooms);
}

//Remove small sections of floors/walls based off of threshold set
std::vector<Room> CaveGenerator::TrimMap()
{
	static int wallThresholdSize = 10;
	std::vector<std::vector<Point>> wallRegions = GetRegions(1);

	for (std::vector<Point> wallRegion : wallRegions)
	{
		if (wallRegion.size() < wallThresholdSize)
		{
			for (auto& tile : wallRegion)
				mTiles[tile.tileX + tile.tileY * mWidth] = 0;
		}
	}

	static int roomThresholdSize = 10;
	std::vector<std::vector<Point>> roomRegions = GetRegions(0);

	std::vector<Room> survivingRooms;
	for (std::vector<Point> roomRegion : roomRegions)
	{
		if (roomRegion.size() < roomThresholdSize)
		{
			for (auto& tile : roomRegion)
				mTiles[tile.tileX + tile.tileY * mWidth] = 1;
		}
		else
		{
			survivingRooms.push_back(Room(roomRegion, mTiles, mWidth));
		}
	}

	return survivingRooms;
}

//If we are not forcing accessibility from main room then only connect the closest rooms together
//Otherwise connect room to closest room that is accessible from main room
void CaveGenerator::ConnectClosestRooms(std::vector<Room> allRooms, bool forceAccessibilityFromMainRoom)
{
	std::vector<Room*> roomVecA;
	std::vector<Room*> roomVecB;

	if (forceAccessibilityFromMainRoom)
	{
		for (auto& room : allRooms)
		{
			if (room.AccessibleFromMainRoom())
				roomVecB.push_back(&room);
			else
				roomVecA.push_back(&room);
		}
	}
	else
	{
		for (auto& room : allRooms)
		{
			roomVecA.push_back(&room);
			roomVecB.push_back(&room);
		}
	}

	int bestDistance = 0;
	Point bestTileA;
	Point bestTileB;
	Room* bestRoomA = nullptr;
	Room* bestRoomB = nullptr;
	bool possibleConnectionFound = false;

	for (auto& roomA : roomVecA)
	{
		if (!forceAccessibilityFromMainRoom)
		{
			possibleConnectionFound = false;
			if (roomA->HasConnectedRooms())
				continue;
		}

		for (auto& roomB : roomVecB)
		{
			if (roomA == roomB || roomA->IsConnected(*roomB))
				continue;

			for (int tileIndexA = 0; tileIndexA < roomA->GetEdgeTiles().size(); tileIndexA++)
			{
				for (int tileIndexB = 0; tileIndexB < roomB->GetEdgeTiles().size(); tileIndexB++)
				{
					Point tileA = roomA->GetEdgeTiles()[tileIndexA];
					Point tileB = roomB->GetEdgeTiles()[tileIndexB];
					int distanceBetweenRooms = powf(tileA.tileX - tileB.tileX, 2.0f) + powf(tileA.tileY - tileB.tileY, 2.0f);

					if (distanceBetweenRooms < bestDistance || !possibleConnectionFound)
					{
						bestDistance = distanceBetweenRooms;
						possibleConnectionFound = true;
						bestTileA = tileA;
						bestTileB = tileB;
						bestRoomA = roomA;
						bestRoomB = roomB;
					}
				}
			}
		}

		if (possibleConnectionFound && !forceAccessibilityFromMainRoom)
		{
			CreatePassage(*bestRoomA, *bestRoomB, bestTileA, bestTileB);
		}
	}

	if (possibleConnectionFound && forceAccessibilityFromMainRoom)
	{
		CreatePassage(*bestRoomA, *bestRoomB, bestTileA, bestTileB);
		ConnectClosestRooms(allRooms, true);
	}

	if (!forceAccessibilityFromMainRoom)
	{
		ConnectClosestRooms(allRooms, true);
	}
}

void CaveGenerator::CreatePassage(Room& roomA, Room& roomB, Point tileA, Point tileB)
{
	Room::ConnectRooms(roomA, roomB);

	std::vector<Point> line = GetLine(tileA, tileB);

	for (auto& c : line)
		CarveCircle(c, 3);

	CarveCircle(tileA, 3);
	CarveCircle(tileB, 3);
}

void CaveGenerator::CarveCircle(Point c, int r)
{
	for (int x = -r; x <= r; x++)
	{
		for (int y = -r; y <= r; y++)
		{
			if (x * x + y * y <= r * r)
			{
				int realX = c.tileX + x;
				int realY = c.tileY + y;

				if (InsideMap(realX, realY))
					mTiles[realX + realY * mWidth] = 0;
			}
		}
	}
}