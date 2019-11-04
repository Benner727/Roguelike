#ifndef ROOM_H
#define ROOM_H

#include "MathHelper.h"

class Room 
{
public:
	Room();
	Room(std::vector<Point> roomTiles, std::vector<int> map, int mapWidth);

	~Room();

private:
	std::vector<Point> mTiles;
	std::vector<Point> mEdgeTiles;
	std::vector<Room>  mConnectedRooms;
	int mRoomSize;
	bool mIsAccessibleFromMainRoom;
	bool mIsMainRoom;

public:
	std::vector<Point> GetTiles() { return mTiles; }
	std::vector<Point> GetEdgeTiles() { return mEdgeTiles; }
	int Size() { return mRoomSize; }
	bool AccessibleFromMainRoom() { return mIsAccessibleFromMainRoom; }
	bool MainRoom() { return mIsMainRoom; }
	bool HasConnectedRooms() { return mConnectedRooms.size() > 0; }
	bool IsConnected(const Room& otherRoom);

	void SetAsMainRoom() { mIsMainRoom = true; }
	void SetAccessibleFromMainRoom();

	static void ConnectRooms(Room& roomA, Room& roomB);

	inline bool operator <(const Room& otherRoom)
	{
		return this->mRoomSize < otherRoom.mRoomSize;
	}

	friend bool operator ==(const Room& leftRoom, const Room& RightRoom);
};

#endif