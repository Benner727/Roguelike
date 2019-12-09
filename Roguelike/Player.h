#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity
{
public:
	Player(int x = 0, int y = 0);
	Player(Point pos);
	~Player();

private:
	static const int PLAYER_POS_X = 26;
	static const int PLAYER_POS_Y = 0;

public:
};

#endif