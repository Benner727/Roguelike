#ifndef DUNGEONGENERATOR_H
#define DUNGEONGENERATOR_H

#include "MapGenerator.h"

#include <queue>

class DungeonGenerator : public MapGenerator
{
public:
	//Smooth map true for snake like rooms connected by bridges
	//Smooth map false for rectangular rooms connected by hallways

	DungeonGenerator(int width, int height, bool smoothMap = false);
	~DungeonGenerator();

private:
	static const int MIN_ROOM_LENGTH = 7;
	static const int MAX_ROOM_LENGTH = 15;
	
	static const int MAX_ROOM_NUM = 25;
	static const int ROOM_PLACE_ATTEMPTS = 500;

	bool mSmoothMap;

	std::vector<Room> mRooms;

	void CreateRoom();

	bool CanPlace(int cornerX, int cornerY, int width, int height);

	void BuildMap();
	void CreatePassage(Room& roomA, Room& roomB, Point tileA, Point tileB);

public:
	std::vector<int> GenerateMap(int seed);
};

#endif