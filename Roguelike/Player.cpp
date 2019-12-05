#include "Player.h"

Player::Player(int x, int y)
	: xPosition(x), yPosition(y),
	mSprite(Sprite(PLAYER_POS_X, PLAYER_POS_Y, { 255, 255, 255 }))
{
}

Player::Player(Point pos)
	: Player(pos.tileX, pos.tileY)
{
}

Player::~Player()
{
}

void Player::Move(int x, int y)
{
	xPosition = x;
	yPosition = y;
}

void Player::Move(Point pos)
{
	Move(pos.tileX, pos.tileY);
}

void Player::Draw()
{
	mSprite.Draw(xPosition, yPosition);
}