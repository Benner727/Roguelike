#ifndef WEAPON_H

#include "Equippable.h"

enum class WeaponType { melee, ranged, magic };

class Weapon : public Equippable
{
public:
	Weapon(std::string name, Sprite sprite, ItemQuality quality, int tier, int strength, int agility, int intellect, int spirit, int stamina, int damage, WeaponType type, int range, bool twoHanded = false)
		: Equippable(name, sprite, EquipmentSlot::weapon, quality, tier, strength, agility, intellect, spirit, stamina), mDamage(damage), mType(type), mRange(range), mTwoHanded(twoHanded)
	{

	}

	~Weapon() {}

private:
	int mDamage;
	WeaponType mType;
	int mRange;
	bool mTwoHanded;

public:
	int Damage() const { return mDamage; }
	WeaponType Type() const { return mType; }
	int Range() const { return mRange; }
	bool TwoHanded() const { return mTwoHanded; }
};

#endif