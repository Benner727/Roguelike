#include "Entity.h"

Entity::Entity(int x, int y, int spriteX, int spriteY)
	: xPosition(x), yPosition(y),
	mSprite(Sprite(spriteX, spriteY, { 255, 255, 255 }))
{
}

Entity::Entity(Point pos)
	: Entity(pos.tileX, pos.tileY)
{
}

Entity::~Entity()
{
}

void Entity::Move(int x, int y)
{
	xPosition = x;
	yPosition = y;
}

void Entity::Move(Point pos)
{
	Move(pos.tileX, pos.tileY);
}

void Entity::Draw()
{
	mSprite.Draw(xPosition, yPosition);
}
