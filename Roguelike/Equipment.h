#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "Weapon.h"
#include "Armor.h"
#include "Equippable.h"
#include "MathHelper.h"
#include "Sprite.h"

class Equipment
{
public:
	Equipment();
	~Equipment();

private:
	static const int ITEM_SCALE = 4;
	const SDL_Color white = { 255, 255, 255, 255 };
	const Point DEFAULT_SLOT = Point(23, 26);
	const Point SELECTED_SLOT = Point(19, 24);

	bool mOpen = false;

	Equippable* mItems[(int)EquipmentSlot::TOTAL_SLOTS];
	Sprite mSlotDefault;
	Sprite mSlotSelected;

	void _DrawEquippedItems();

public:
	void Equip(Equippable* item);
	Equippable* Unequip(EquipmentSlot slot);

	Equippable* GetSlot(EquipmentSlot slot);

	int Damage() const;
	int Strength() const;
	int Agility() const;
	int Intellect() const;
	int Spirit() const;
	int Stamina() const;
	int Defense() const;
	int Resistance() const;

	void Toggle() { mOpen = !mOpen; }
	void Draw();
};

#endif