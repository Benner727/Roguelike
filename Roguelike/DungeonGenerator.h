#ifndef DUNGEONGENERATOR_H
#define DUNGEONGENERATOR_H

#include "MapGenerator.h"

#include <queue>

class DungeonGenerator : public MapGenerator
{
public:
	DungeonGenerator(int width, int height, bool smoothMap = false);
	~DungeonGenerator();

private:
	static const int MAX_ROOM_LENGTH = 12;
	static const int MIN_ROOM_LENGTH = 5;

	bool mSmoothMap;

	void CreateRoom();

	void BuildMap();
	void ConnectClosestRooms(std::vector<Room> allRooms, bool forceAccessibilityFromMainRoom = false);
	void CreatePassage(Room& roomA, Room& roomB, Point tileA, Point tileB);

public:
	std::vector<int> GenerateMap(int seed);
};

#endif