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

void Player::Move(const SDL_Scancode& scanCode)
{
	switch (scanCode)
	{
		case SDL_SCANCODE_A:
			Move(xPosition - 1, yPosition);
			break;
		case SDL_SCANCODE_D:
			Move(xPosition + 1, yPosition);
			break;
		case SDL_SCANCODE_S:
			Move(xPosition, yPosition + 1);
			break;
		case SDL_SCANCODE_W:
			Move(xPosition, yPosition - 1);
			break;
	}
}
