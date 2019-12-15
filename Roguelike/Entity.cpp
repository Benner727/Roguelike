#include "Entity.h"



Entity::Entity(Point pos, Sprite sprite)
	: mPos(pos), mSprite(sprite)
{
}

Entity::~Entity()
{
}

void Entity::Move(int x, int y)
{
	mPos.tileX = x;
	mPos.tileY = y;
}

void Entity::Move(Point pos)
{
	Move(pos.tileX, pos.tileY);
}

void Entity::Draw()
{
	mSprite.Draw(mPos.tileX, mPos.tileY);
}
