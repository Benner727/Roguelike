#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity
{
public:
	Player(Point pos);
	Player(int x = 0, int y = 0);
	~Player();

private:
	static const int SPRITE_TILE_X = 26;
	static const int SPRITE_TILE_Y = 0;

public:
};

#endif