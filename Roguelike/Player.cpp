#include "Player.h"

Player::Player()
	: xPosition(0), yPosition(0),
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

void Player::MoveLeft()
{
	Move(xPosition - 1, yPosition);
}

void Player::MoveRight()
{
	Move(xPosition + 1, yPosition);
}

void Player::MoveUp()
{
	Move(xPosition, yPosition - 1);
}

void Player::MoveDown()
{
	Move(xPosition, yPosition + 1);
}
