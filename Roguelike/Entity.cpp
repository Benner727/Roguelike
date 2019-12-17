#include "Entity.h"



Entity::Entity(Point pos, Sprite sprite)
	: mPos(pos), mSprite(sprite)
{
	mName = "";

	mHealth = 100;
	mMaxHealth = 100;

	mStrength = 0;
	mIntellect = 0;
	mSpirit = 0;
	mStamina = 0;
	mDefense = 0;
	mResistance = 0;
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
