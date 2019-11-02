#ifndef MAP_H
#define MAP_H

#include "Text.h"
#include "CaveGenerator.h"

class Map
{
public:
	Map(int width, int height);
	~Map();

private:
	int mWidth;
	int mHeight;

	int mSeed;

	std::vector<int> mTiles;

	MapGenerator* mMapGenerator;

public:
	int GetSeed() { return mSeed; }

	bool Walkable(int x, int y);

	void Update();
	void Draw();
};

#endif