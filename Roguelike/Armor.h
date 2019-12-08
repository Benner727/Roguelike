#ifndef ARMOR_H
#define ARMOR_H

#include "Equippable.h"

class Armor : public Equippable
{
public:
	Armor(std::string name, Sprite sprite, EquipmentSlot slot, ItemQuality quality, int tier, int strength, int agility, int intellect, int spirit, int stamina, int defense, int resistance)
		: Equippable(name, sprite, slot, quality, tier, strength, agility, intellect, spirit, stamina), mDefense(defense), mResistance(resistance)
	{

	}

	~Armor() {}

private:
	int mDefense;
	int mResistance;

public:
	int Defense() const { return mDefense; }
	int Resistance() const { return mResistance; }
};

#endif