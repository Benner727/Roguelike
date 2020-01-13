#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "Weapon.h"
#include "Armor.h"
#include "Equippable.h"
#include "Sprite.h"

class Equipment
{
public:
	Equipment();
	~Equipment();

private:
	static const int ITEM_SCALE = 4.f;
	const SDL_Color white = { 255, 255, 255, 255 };
	const std::tuple<int, int> DEFAULT_SLOT = std::make_tuple(23, 26);
	const std::tuple<int, int> SELECTED_SLOT = std::make_tuple(19, 24);

	bool mOpen = false;

	Equippable* mItems[(int)EquipmentSlot::TOTAL_SLOTS];
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