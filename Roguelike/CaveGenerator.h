#ifndef CAVEGENERATOR_H
#define CAVEGENERATOR_H

#include "MapGenerator.h"

#include <queue>
#include <algorithm>

class CaveGenerator : public MapGenerator
{
public:
	CaveGenerator(int width, int height, int fillPercent = 45);
	~CaveGenerator();

private:
	static const int SMOOTHING_ITERATIONS = 3;

	//Chance for initial tiles to be wall
	int mFillPercent;

	void FillMap();
	void SmoothMap();
	int SurroundingWallCount(int x, int y);

	std::vector<Room> TrimMap();
	std::vector<Point> GetRegionTiles(int startX, int startY);
	std::vector<std::vector<Point>> GetRegions(int tileType);

	void BuildMap();
	void ConnectClosestRooms(std::vector<Room> allRooms, bool forceAccessibilityFromMainRoom = false);
	void CreatePassage(Room& roomA, Room& roomB, Point tileA, Point tileB);
	void CarveCircle(Point c, int r);

	bool InsideMap(int x, int y);

public:
	std::vector<int> GenerateMap(int seed);
};

#endif