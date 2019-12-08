#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include "Item.h"

enum class ItemEffect { none };

class Consumable : public Item
{
public:
	Consumable(std::string name, Sprite sprite, ItemEffect effect);
	~Consumable();

private:
	ItemEffect mEffect;

public:
	ItemEffect Effect() const { return mEffect; }
};

#endif