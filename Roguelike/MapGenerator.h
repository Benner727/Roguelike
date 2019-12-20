#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include "Room.h"
#include "RNG.h"

#include <queue>

class MapGenerator
{
public:
	MapGenerator(int width, int height);
	virtual ~MapGenerator() {}

private:
	static const int SAFE_ZONE = 14;

protected:
	int mWidth;
	int mHeight;
	RNG mRNG;

	Point mStart;
	Point mEnd;

	std::vector<Point> mSpawnPoints;

	std::vector<int> mTiles;

	void SeedRNG(int seed);

	bool InsideMap(int x, int y);

	void SmoothMap();
	int SurroundingWallCount(int x, int y);

	std::vector<Point> GetRegionTiles(int startX, int startY);
	std::vector<std::vector<Point>> GetRegions(int tileType);

	void ConnectClosestRooms(std::vector<Room> allRooms, bool forceAccessibilityFromMainRoom = false);
	virtual void CreatePassage(Room& roomA, Room& roomB, Point tileA, Point tileB) = 0;

	void CreateEntryPoints();

public:
	Point GetStart() const { return mStart; }
	Point GetEnd() const { return mEnd; }

	std::vector<Point> PossibleSpawns() const { return mSpawnPoints; }

	virtual std::vector<int> GenerateMap(int seed) = 0;
};

#endif