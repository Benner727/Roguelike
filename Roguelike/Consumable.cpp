#include "Consumable.h"



Consumable::Consumable(std::string name, Sprite sprite, ItemEffect effect)
	: Item(name, sprite, true, 1), mEffect(effect)
{
}


Consumable::~Consumable()
{
}
