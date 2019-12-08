#ifndef ITEMBUILDER_H
#define ITEMBUILDER_H

#include "Weapon.h"
#include "Armor.h"
#include "RNG.h"

class ItemBuilder
{
public:
	ItemBuilder();
	~ItemBuilder();

private:
	RNG mRNG;

	ItemQuality RollQuality();
	EquipmentSlot RollSlot(bool includeWeapon);
	int RollStat(int tier, ItemQuality quality);
	int RollDamage(int tier);
	int RollArmorValue(int tier);

public:
	Weapon* GetRandomWeapon(int tier);
	Armor* GetRandomArmor(int tier);
	Equippable* GetRandomEquippable(int tier);
};

#endif