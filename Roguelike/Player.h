#ifndef PLAYER_H
#define PLAYER_H

#include "Sprite.h"

class Player
{
public:
	Player();
	~Player();

private:
	static const int PLAYER_POS_X = 26;
	static const int PLAYER_POS_Y = 0;

	int xPosition;
	int yPosition;

	Sprite mSprite;

	void Move(int x, int y);

public:
	const int GetXPos() { return xPosition; }
	const int GetYPos() { return yPosition; }

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

	void Draw();
};

#endif