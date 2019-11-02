#include "Room.h"



Room::Room()
{
	mRoomSize = 0;
	mIsAccessibleFromMainRoom = false;
	mIsMainRoom = false;
}

Room::Room(std::vector<Point> roomTiles, std::vector<int> map, int mapWidth)
{
	mTiles = roomTiles;
	mRoomSize = mTiles.size();
	mIsAccessibleFromMainRoom = false;
	mIsMainRoom = false;

	for (auto& tile : mTiles)
	{
		for (int x = tile.tileX - 1; x <= tile.tileX + 1; x++)
		{
			for (int y = tile.tileY - 1; y <= tile.tileY + 1; y++)
			{
				if (x == tile.tileX || y == tile.tileY)
				{
					if (map[x + y * mapWidth] == 1)
						mEdgeTiles.push_back(Point(x, y));
				}
			}
		}
	}
}

Room::~Room()
{
}


bool Room::IsConnected(Room otherRoom)
{
	return std::find(mConnectedRooms.begin(), mConnectedRooms.end(), otherRoom) != mConnectedRooms.end();
}

void Room::SetAccessibleFromMainRoom()
{
	if (!mIsAccessibleFromMainRoom)
		mIsAccessibleFromMainRoom = true;

	for (auto& connectedRoom : mConnectedRooms)
		connectedRoom.mIsAccessibleFromMainRoom = true;
}

void Room::ConnectRooms(Room& roomA, Room& roomB)
{
	if (roomA.mIsAccessibleFromMainRoom)
		roomB.SetAccessibleFromMainRoom();
	else if (roomB.mIsAccessibleFromMainRoom)
		roomA.SetAccessibleFromMainRoom();

	roomA.mConnectedRooms.push_back(roomB);
	roomB.mConnectedRooms.push_back(roomA);
}

bool operator ==(const Room& leftRoom, const Room& rightRoom)
{
	return leftRoom.mTiles == rightRoom.mTiles;
}