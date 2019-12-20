#ifndef MAP_H
#define MAP_H

#include "Text.h"
#include "CaveGenerator.h"
#include "DungeonGenerator.h"
#include "LevelGenerator.h"

struct Tile {
	int tileId;
	bool opaque;
	bool walkable;
	bool visible;
	bool explored;

	Tile(int _tileId, bool _opaque, bool _walkable)
	{
		tileId = _tileId;
		opaque = _opaque;
		walkable = _walkable;
		visible = false;
		explored = false;
	}
};

class Map
{
public:
	Map(int width, int height);
	~Map();

private:
	int mWidth;
	int mHeight;

	int mSeed;

	std::vector<Tile> mTiles;

	MapGenerator* mMapGenerator;

	std::vector<int> GenerateDijkstraMap(int sourceX, int sourceY);

public:
	const int GetSeed() { return mSeed; }

	const int Width() { return mWidth; }
	const int Height() { return mHeight; }

	const bool Walkable(int x, int y);
	const bool Opaque(int x, int y) { return mTiles[x + y * mWidth].opaque; }
	
	void SetVisible(int x, int y, bool visible) { mTiles[x + y * mWidth].visible = visible; }

	std::vector<Tile> Tiles() const { return mTiles; }
	Point StartPos() const { return mMapGenerator->GetStart(); }
	Point EndPos() const { return mMapGenerator->GetEnd(); }
	std::vector<Point> SpawnPoints() const { return mMapGenerator->PossibleSpawns(); }

	void GenerateNewMap();

	void Draw();
};

#endif