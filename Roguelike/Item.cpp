#include "Item.h"



Item::Item(std::string name, Sprite sprite, bool stackable, int amount)
	: mName(name), mSprite(sprite), mStackable(stackable), mAmount(amount)
{
}


Item::~Item()
{
}

void Item::Draw(int x, int y)
{
	mSprite.Draw(x, y);
}
