#include "Player.h"


Player::Player(int startX, int startY)
	: xPosition(startX), yPosition(startY),
	mSprite(Sprite(PLAYER_POS_X, PLAYER_POS_Y, { 255, 255, 255 }))
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

void Player::Draw()
{
	mSprite.Draw(xPosition, yPosition);
}
