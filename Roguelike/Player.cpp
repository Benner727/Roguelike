#include "Player.h"



Player::Player(Point pos)
	: Entity(pos, Sprite(SPRITE_TILE_X, SPRITE_TILE_Y, { 255, 255, 255 }))
{
}

Player::Player(int x, int y)
	: Player(Point(x, y))
{
}

Player::~Player()
{
}
