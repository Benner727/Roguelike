#ifndef EQUIPPABLE_H
#define EQUIPPABLE_H

#include "Item.h"

enum class EquipmentSlot { weapon, shield, head, chest, legs, gloves, boots, cloak, amulet, ring, TOTAL_SLOTS };
enum class ItemQuality {poor, common, uncommon, rare, epic, legendary };

class Equippable : public Item
{
public:
	Equippable(std::string name, Sprite sprite, EquipmentSlot slot, ItemQuality quality, int tier, int strength, int agility, int intellect, int spirit, int stamina);
	~Equippable();

private:
	EquipmentSlot mSlot;
	ItemQuality mQuality;
	int mTier;

	int mStrength;
	int mAgility;
	int mIntellect;
	int mSpirit;
	int mStamina;

public:
	EquipmentSlot Slot() const { return mSlot; }
	ItemQuality Quality() const { return mQuality; }
	int Tier() const { return mTier; }

	int Strength() const { return mStrength; }
	int Agility() const { return mAgility; }
	int Intellect() const { return mIntellect; }
	int Spirit() const { return mSpirit; }
	int Stamina() const { return mStamina; }
};

#endif