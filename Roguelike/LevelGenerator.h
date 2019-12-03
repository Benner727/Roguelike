#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H

#include "MapGenerator.h"

struct Prefab {
	std::vector<int> tiles;
	int width;
	int height;
};

class LevelGenerator : public MapGenerator
{
public:
	LevelGenerator(int width, int height);
	~LevelGenerator();

private:
	static const int MIN_ROOM_SIZE = 6;
	static const int MAX_ROOM_SIZE = 12;

	void CreatePassage(Room& roomA, Room& roomB, Point tileA, Point tileB) {}

	void GenerateRect();
	void GenerateCross();

	bool CanPlace(Prefab room, int xPos, int yPos);

public:
	std::vector<int> GenerateMap(int seed);
};

#endif