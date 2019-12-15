#include "Player.h"

Player::Player(int x, int y)
	: Entity(x, y, SPRITE_TILE_X, SPRITE_TILE_Y)
{
}

Player::Player(Point pos)
	: Player(pos.tileX, pos.tileY)
{
}

Player::~Player()
{
}
