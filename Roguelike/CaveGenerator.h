#ifndef CAVEGENERATOR_H
#define CAVEGENERATOR_H

#include "MapGenerator.h"

#include <queue>
#include <algorithm>

class CaveGenerator : public MapGenerator
{
public:
	//Overworld - Very open
	//Fill Percent = 42
	//Smoothing Iterations = 1

	//Mostly open with some windy paths connecting zones
	//Fill Percent = 45
	//Smoothing Iterations = 3

	//Lots of narrow passages with medium sized zones
	//Fill Percent = 47
	//Smoothing Iterations = 5

	CaveGenerator(int width, int height, int fillPercent = 45, int smoothingIterations = 3);
	~CaveGenerator();

private:
	//Chance for initial tiles to be wall
	int mFillPercent;
	int mSmoothingIterations;

	void FillMap();
	std::vector<Room> TrimMap();

	void BuildMap();
	void ConnectClosestRooms(std::vector<Room> allRooms, bool forceAccessibilityFromMainRoom = false);
	void CreatePassage(Room& roomA, Room& roomB, Point tileA, Point tileB);
	void CarveCircle(Point c, int r);

public:
	std::vector<int> GenerateMap(int seed);
};

#endif