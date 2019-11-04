#include "DungeonGenerator.h"



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

	for (int y = yPos; y < yPos + height; y++)
	{
		for (int x = xPos; x < xPos + width; x++)
		{
			mTiles[x + y * mWidth] = 0;
		}
	}
}

void DungeonGenerator::BuildMap()
{
	std::vector<Room> survivingRooms;
	std::vector<std::vector<Point>> roomRegions = GetRegions(0);

	for (std::vector<Point> roomRegion : roomRegions)
		survivingRooms.push_back(Room(roomRegion, mTiles, mWidth));

	std::sort(survivingRooms.begin(), survivingRooms.end());
	survivingRooms.back().SetAsMainRoom();
	survivingRooms.back().SetAccessibleFromMainRoom();

	ConnectClosestRooms(survivingRooms);
}

void DungeonGenerator::ConnectClosestRooms(std::vector<Room> allRooms, bool forceAccessibilityFromMainRoom)
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

	for (int i = 0; i < mWidth * mHeight; i++)
		mTiles.push_back(1);

	for (int i = 0; i < 20; i++)
		CreateRoom();

	if (mSmoothMap)
	{
		SmoothMap();
	}

	BuildMap();

	return mTiles;
}