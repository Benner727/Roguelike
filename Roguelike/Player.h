#ifndef PLAYER_H
#define PLAYER_H

#include "Sprite.h"

class Player
{
public:
	Player(int startX, int startY);
	~Player();

private:
	static const int PLAYER_POS_X = 26;
	static const int PLAYER_POS_Y = 0;

	int xPosition;
	int yPosition;

	Sprite mSprite;



public:
	const int GetXPos() { return xPosition; }
	const int GetYPos() { return yPosition; }

	void Move(int x, int y);
	void Draw();
};

#endif