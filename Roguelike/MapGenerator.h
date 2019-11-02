#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include "Room.h"
#include "RNG.h"

class MapGenerator
{
public:
	MapGenerator(int width, int height) 
		: mRNG(0), mWidth(width), mHeight(height) {}
	virtual ~MapGenerator() {}

protected:
	int mWidth;
	int mHeight;
	RNG mRNG;

	std::vector<int> mTiles;

	void SeedRNG(int seed)
	{
		mRNG = RNG(seed);
	}

public:
	virtual std::vector<int> GenerateMap(int seed) = 0;
};

#endif